// In-browser port of the proof combiner (compose.js / analysis.js of the proof folder).
// It re-checks every proof obligation from the published files; it never runs CPAchecker.
// load(path) -> Promise<string> (path relative to ftec/), sha256(string) -> Promise<hex>.

export const REQUIRED_OPTIONS = ['cpa.loopbound.maxLoopIterations=128', 'cpa.predicate.encodeBitvectorAs=BITVECTOR'];
const CORRECTION_LINE = 'check(ec==correction(en,eb,eh0,eh1,eh2,eh3,eh4,eh5,eh6,eh7));';
const INCLUDE = '#include "scalar.c"';

// Same rules as commandIssues() in analysis.js.
export function commandIssues(command) {
  if (!Array.isArray(command) || !command.every(a => typeof a === 'string')) return ['命令列缺失'];
  const out = [];
  if (command.filter(a => a === '--config').length !== 1) out.push('--config 必須恰好出現一次');
  const ci = command.indexOf('--config');
  if (ci < 0 || !/(^|[\\/])config[\\/]bmc\.properties$/.test(command[ci + 1] || '')) out.push('設定檔不是 config/bmc.properties');
  const ti = command.indexOf('--timelimit');
  if (ti < 0 || !/^\d+s$/.test(command[ti + 1] || '')) out.push('缺少時間上限');
  const opts = []; command.forEach((a, i) => { if (a === '--option') opts.push(command[i + 1] || ''); });
  for (const req of REQUIRED_OPTIONS) {
    if (!opts.includes(req)) out.push('缺少選項 ' + req);
    const k = req.split('=')[0];
    if (opts.filter(o => o.split('=')[0].trim() === k).length > 1) out.push('選項 ' + k + ' 重複設定');
  }
  if (command.some(a => /bmc\.boundingAssertions\s*=\s*false/i.test(a))) out.push('關閉了 bounding assertions');
  return out;
}

// Tamper scenarios, mirroring test_compose.js: each must turn the conclusion into INCOMPLETE.
export const TAMPERS = {
  none: '不修改',
  dropPartition: '刪掉一區（r2_k3_op4）的 CPAchecker 紀錄',
  disableBounding: '把一區紀錄的設定改成關閉 bounding assertions',
  editHarness: '改動一區驗證程式的一個字',
  editModel: '在 scalar.c 結尾多加一個空白',
  controlTrue: '把一個對照組的結果改成 TRUE',
};

export async function compose({ load, sha256, tamper = 'none', onProgress = () => {} }) {
  const issues = [];
  const steps = [];
  const step = (key, ok, detail) => steps.push({ key, ok, detail });
  const [model0, manifestT, casesT, recordsT] = await Promise.all(
    ['src/scalar.c', 'src/manifest.json', 'src/cases.json', 'data/records.json'].map(load));
  const manifest = JSON.parse(manifestT), CASES = JSON.parse(casesT), records = JSON.parse(recordsT);
  let model = model0;
  if (tamper === 'editModel') model += ' ';
  if (tamper === 'dropPartition') delete records.residual.r2_k3_op4;
  if (tamper === 'disableBounding') records.residual.r1_k1_op5.command.push('--option', 'bmc.boundingAssertions=false');
  if (tamper === 'controlTrue') { const c = records.cases.pair_bridge_broken; c.status = 'TRUE'; c.finalResults = ['Verification result: TRUE.']; }
  const modelHash = await sha256(model);

  // 1. The model the evidence talks about is the published scalar.c.
  const modelOK = manifest.modelSHA256 === modelHash;
  if (!modelOK) issues.push('證據記錄的模型指紋與 scalar.c 不同');
  step('model', modelOK, modelHash.slice(0, 12) + '…');

  // 2. Independent recomputation of the input domain and partition coverage.
  const domain = [{ m: 0 }];
  for (let q = 0; q < 7; q++) for (let a = 1; a <= 3; a++) domain.push({ m: 1, q, a });
  for (let r = 1; r <= 3; r++) for (let k = 0; k < 6; k++) for (let op = 0; op < 10; op++)
    for (let p = 1; p <= (op >= 2 && op <= 7 ? 15 : 1); p++) domain.push({ m: 2, r, k, op, p });
  const matches = (d, i) => d.kind === 'initial' ? i.m <= 1 : d.kind === 'circuit' && i.m === 2 && d.round === i.r && d.k === i.k && d.op === i.op && i.p >= 1 && i.p <= d.count;
  const ps = manifest.partitions || [];
  const coverage = ps.length === 181 && new Set(ps.map(d => d.id)).size === 181 &&
    domain.every(i => ps.filter(d => matches(d, i)).length === 1) && ps.every(d => domain.filter(i => matches(d, i)).length === d.count);
  if (!coverage) issues.push('181 區沒有剛好覆蓋全部輸入');
  step('coverage', coverage, `${domain.length} 種輸入 · ${ps.length} 區`);

  async function verify(rec, source, expectedStatus, expectedModel) {
    if (!rec) throw Error('找不到 CPAchecker 紀錄');
    const finals = (rec.finalResults || []).map(l => /Verification result: (TRUE|FALSE|UNKNOWN)\b/.exec(l)?.[1]);
    if (rec.status !== expectedStatus || rec.exitCode !== 0 || finals.length !== 1 || finals[0] !== expectedStatus)
      throw Error(`結果不符（預期 ${expectedStatus}，紀錄 ${rec.status}）`);
    if (rec.modelSHA256 !== expectedModel || rec.sourceSHA256 !== await sha256(source)) throw Error('程式或模型指紋不符');
    const expected = expectedModel == null ? source : source.replace(INCLUDE, () => model);
    if (rec.inputSHA256 !== await sha256(expected)) throw Error('CPAchecker 實際分析的程式與預期不同');
    const ci = commandIssues(rec.command);
    if (ci.length) throw Error('分析設定不合格：' + ci.join('；'));
  }

  // 3. Every partition: harness unchanged, contains the observation check, TRUE with the right settings.
  let okParts = 0, done = 0;
  const sources = await Promise.all(ps.map(d => load(`src/residual/${d.id}.c`).then(s => { onProgress(++done / (ps.length + 9)); return s; })));
  for (let i = 0; i < ps.length; i++) {
    const d = ps[i]; let source = sources[i];
    if (tamper === 'editHarness' && d.id === 'r3_k5_op9') source = source.replace('return 0; }', 'return 0;}');
    try {
      const key = `residual/${d.id}.c`;
      if (await sha256(source) !== manifest.files[key]) throw Error('驗證程式與分區清單的指紋不同');
      if (!source.includes(CORRECTION_LINE + '\n' + 'check(residual(')) throw Error('驗證程式缺少「修正只由觀測決定」的檢查');
      const rec = records.residual[d.id];
      await verify(rec, source, 'TRUE', modelHash);
      if (rec.id !== d.id || rec.task !== 'residual') throw Error('紀錄與分區對不上');
      okParts++;
    } catch (e) { issues.push(`${d.id}：${e.message}`); }
  }
  step('partitions', okParts === 181, `${okParts} / 181 區 TRUE 且核對通過`);

  // 4. Lemmas and controls.
  const lemmas = [];
  for (const [name, c] of Object.entries(CASES)) {
    try {
      const source = await load(`src/lemmas/${name}.c`); onProgress(++done / (ps.length + 9));
      if (c.includesModel !== source.includes(INCLUDE)) throw Error('include 狀態不符');
      const rec = records.cases[name];
      await verify(rec, source, c.expected, c.includesModel ? modelHash : null);
      if (rec.name !== name) throw Error('紀錄與案例對不上');
      lemmas.push({ name, role: c.role, expected: c.expected, ok: true });
    } catch (e) { lemmas.push({ name, role: c.role, expected: c.expected, ok: false }); issues.push(`${name}：${e.message}`); }
  }
  const lemOK = lemmas.filter(l => l.role === 'lemma');
  const ctlOK = lemmas.filter(l => l.role !== 'lemma');
  step('lemmas', lemOK.every(l => l.ok), `${lemOK.filter(l => l.ok).length} / ${lemOK.length} 條 TRUE`);
  step('controls', ctlOK.every(l => l.ok), `${ctlOK.filter(l => l.ok).length} / ${ctlOK.length} 個符合預期`);

  return { conclusion: issues.length ? 'INCOMPLETE' : 'PROVED_BY_COMPOSITION', steps, issues, lemmas, modelHash };
}
