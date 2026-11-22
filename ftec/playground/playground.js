import { loadFtec, pauliString, describeInput, stabName, twoQubitPauli } from '../assets/ftec-core.js';

const $ = id => document.getElementById(id);
const tick = () => new Promise(r => setTimeout(r, 0));
const hex = buf => [...new Uint8Array(buf)].map(b => b.toString(16).padStart(2, '0')).join('');
const fmt = n => n.toLocaleString('en-US');

const CHECKS = [
  ['hash', '模型雜湊一致', '瀏覽器下載的 scalar.c 的 SHA-256，等於每筆 CPAchecker 紀錄的 modelSHA256，也等於這份 WASM 的建置輸入。'],
  ['pauli', '16,384 個資料 Pauli', 'scalar.c 的 sy、member、residual(·,0)、residual(·,1) 與 legacy.c 的暴力列舉逐一相同。'],
  ['equiv', '1,714 個配置：與獨立實作相同', '最終錯誤 E、r、s、輪數、分支、每輪歷史與 decoder 輸出都和 legacy.c 相同。'],
  ['budget', '預算 r+s ≤ 1', '每個合法配置都在 t=1 預算內。'],
  ['obs', '修正只由觀測決定', '每個執行實際使用的 ec 都等於 correction(n,b,h₀..h₇)。對應證明鏈步驟 4。'],
  ['residual', '殘餘界限 wt_min(C·E) ≤ s', '對應證明鏈步驟 1（CPAchecker 的 181 區）。以 scalar.c 與 legacy.c 各算一次。'],
  ['lemmas', '有限域引理', 'budget_relaxation（x,z,r,s）、residual_signature（16,384 個 Pauli）、signature_pair（4,096² 對殘餘）全部窮舉。'],
  ['pairs', 'pair 條件（直接檢查）', '所有觀測相同的執行對 (f₁,f₂)：σ(E₁E₂)=0 ⟹ E₁E₂ ∈ S。這是定理本身。'],
];

let F, ev, build, modelOK = false;
const state = {};
function renderChecks() {
  $('checks').innerHTML = CHECKS.map(([id, t, d]) => {
    const s = state[id] || { cls: '', icon: '·', r: '' };
    return `<li class="${s.cls}"><span class="ic">${s.icon}</span><span><span class="t">${t}</span><br><span class="d">${d}</span></span><span class="r">${s.r}</span></li>`;
  }).join('');
}
const set = (id, cls, r) => { state[id] = { cls, icon: { ok: '✓', bad: '✗', na: '!', run: '…' }[cls] || '·', r }; renderChecks(); };
const progress = f => { $('bar').style.width = (f * 100).toFixed(1) + '%'; };

async function boot() {
  renderChecks();
  const [wasmBuf, model, evJ, buildJ] = await Promise.all([
    fetch('../assets/ftec.wasm').then(r => r.arrayBuffer()),
    fetch('../src/scalar.c').then(r => r.arrayBuffer()),
    fetch('../data/evidence.json').then(r => r.json()),
    fetch('../data/wasm_build.json').then(r => r.json()),
  ]);
  ev = evJ; build = buildJ;
  F = await loadFtec(wasmBuf);
  $('wasm-size').textContent = `${(wasmBuf.byteLength / 1024).toFixed(1)} KB`;
  const mh = hex(await crypto.subtle.digest('SHA-256', model));
  const wh = hex(await crypto.subtle.digest('SHA-256', wasmBuf));
  const allRec = ev.partitions.every(p => p.modelSHA256 === mh) && ev.lemmas.filter(l => l.name.indexOf('bitprecise') < 0).every(l => l.modelSHA256 === mh);
  modelOK = mh === ev.modelSHA256 && allRec && build.inputs['scalar.c'] === mh && build.wasmSHA256 === wh;
  set('hash', modelOK ? 'ok' : 'bad', mh.slice(0, 12) + '…');
  $('build').innerHTML = `WASM 建置：${build.toolchain}，${build.built.slice(0, 10)}。<br>wasm SHA-256 <code style="font-size:.7rem;word-break:break-all">${wh}</code>`;
  $('go').disabled = false; $('go').textContent = '開始窮舉檢查';
  $('x-go').disabled = $('x-rand').disabled = false;
  explorerRun();
}

async function runAll() {
  const mode = +document.querySelector('input[name=mode]:checked').value;
  $('go').disabled = true; $('verdict').innerHTML = ''; $('cex').innerHTML = '';
  for (const [id] of CHECKS) if (id !== 'hash') delete state[id];
  renderChecks();
  const t0 = performance.now();
  // 1. Paulis, in chunks so the bar moves.
  set('pauli', 'run', '');
  let bad = 0;
  for (let lo = 0; lo < 16384; lo += 2048) { bad += F.checkPaulis(lo, lo + 2048); progress(0.1 * (lo + 2048) / 16384); await tick(); }
  set('pauli', bad ? 'bad' : 'ok', bad ? `${bad} 處不符` : '16,384 / 16,384');
  // 2. Configurations.
  ['equiv', 'budget', 'obs', 'residual'].forEach(id => set(id, 'run', ''));
  const cnt = { equiv: 0, budget: 0, obs: 0, residual: 0 }, resFail = [];
  for (let i = 0; i < F.count; i++) {
    const fl = F.checkConfig(i, mode === 1 ? 1 : 0);
    if (fl & 31) cnt.equiv++;
    if (fl & 64) cnt.budget++;
    if (fl & 32) cnt.obs++;
    if (fl & 384) { cnt.residual++; resFail.push(i); }
    if (i % 200 === 0) { progress(0.1 + 0.3 * i / F.count); await tick(); }
  }
  set('equiv', cnt.equiv ? 'bad' : 'ok', cnt.equiv ? `${cnt.equiv} 個不符` : '1,714 / 1,714');
  set('budget', cnt.budget ? 'bad' : 'ok', cnt.budget ? `${cnt.budget} 個越界` : '1,714 / 1,714');
  set('obs', cnt.obs ? 'bad' : 'ok', cnt.obs ? `${cnt.obs} 個不符` : '1,714 / 1,714');
  set('residual', cnt.residual ? 'na' : 'ok', cnt.residual ? `${cnt.residual} 個失敗` : '1,714 / 1,714');
  // 3. Lemmas.
  set('lemmas', 'run', ''); progress(0.45); await tick();
  const lb = F.lemmaBudget(), ls = F.lemmaSignature(); progress(0.55); await tick();
  const lp = F.lemmaSignaturePair();
  const lemOK = lb === 0 && ls === 0 && lp === 0;
  set('lemmas', lemOK ? 'ok' : 'bad', lemOK ? '3 / 3' : `違反 ${lb}/${ls}/${lp}`);
  progress(0.8); await tick();
  // 4. Pairs.
  set('pairs', 'run', '');
  const pr = F.checkPairs(mode === 2 ? 1 : 0);
  set('pairs', pr.bad ? 'bad' : 'ok', pr.bad ? `${fmt(pr.bad)} 對反例` : `${fmt(pr.pairs)} 對，0 反例`);
  progress(1);
  $('timing').textContent = `完成，用時 ${((performance.now() - t0) / 1000).toFixed(2)} 秒`;
  verdict(mode, { modelOK, pauli: bad === 0, ...cnt, lemOK, pr, resFail });
  $('go').disabled = false; $('go').textContent = '再跑一次';
}

function verdict(mode, r) {
  const implOK = r.modelOK && r.pauli && !r.equiv && !r.budget && !r.obs;
  const comp = !r.residual && r.lemOK;
  let html = '';
  if (!implOK) html += box('bad', '實作檢查失敗', '模型雜湊或與獨立實作的比對不一致，以下結論不可採信。');
  if (mode === 2) html += box('na', '組合式證明不適用於這個假設', '對照 B 只改變 pair 條件裡「觀測相同」的定義，殘餘檢查仍使用原本看完整歷史的 decoder。證明鏈步驟 4（同觀測 → 同修正）依賴完整觀測，所以這裡只看下一格的直接 pair 檢查。');
  else html += comp
    ? box('ok', '組合式證明適用', '殘餘界限在全部 1,714 個配置成立，三條有限域引理窮舉無反例；搭配 common_correction（只能由 CPAchecker 證明），證明鏈的前提全部成立。')
    : box('na', '組合式證明不適用', `殘餘界限在 ${r.residual} 個配置不成立，所以證明鏈步驟 1 的前提不成立。<strong>這不等於協定錯誤</strong>，pair 條件需要另外判斷（見下一格）。`);
  if (r.pr.bad === 0) {
    html += box('ok', 'pair 條件：TRUE（窮舉）', `${fmt(r.pr.pairs)} 對觀測相同的執行（含 f₁=f₂）全部滿足 σ(E₁E₂)=0 ⟹ E₁E₂ ∈ S。` +
      (mode === 1 ? '對照 A 改的是修正，而 pair 條件只看修正前的錯誤與觀測，所以仍然成立，這正是兩者必須分開回報的原因。' : ''));
  } else {
    html += box('bad', mode === 2 ? 'pair 條件：FALSE（觀測只保留最後一輪）' : 'pair 條件：FALSE',
      mode === 2 ? `找到 ${fmt(r.pr.bad)} 對反例：最後一輪紀錄相同，但錯誤差異是邏輯算子。任何只看最後一輪的 decoder 都不可能同時修好這兩個執行，所以旗標分支需要完整歷史。` : `找到 ${fmt(r.pr.bad)} 對反例。`);
  }
  $('verdict').innerHTML = html;
  if (r.pr.first) showPair(r.pr.first, mode === 2);
  else if (r.resFail.length) showResidualFail(r.resFail);
}
const box = (cls, t, d) => `<div class="verdict ${cls}"><b>${t}</b>${d}</div>`;

function obsRow(o) {
  return o.h.slice(0, o.n).map((w, i) => `<tr><td>h${i}</td><td class="bits">${bits(w & 63, 6)}</td><td class="bits">${bits(w >> 6, 6)}</td></tr>`).join('');
}
function bits(v, n) {
  let s = '';
  for (let k = 0; k < n; k++) s += (v >> k) & 1 ? '<span class="on">1</span>' : '0';
  return s;
}
function run(i) { const f = F.input(i); return { f, o: F.explore(f.mode, f.q, f.a, f.round, f.k, f.op, f.p) }; }
function showPair([i, j], coarse) {
  const a = run(i), b = run(j);
  const dx = a.o.ex ^ b.o.ex, dz = a.o.ez ^ b.o.ez;
  const col = (r, name) => `<div><h3>${name}：${describeInput(r.f)}</h3>
    <p class="mono" style="font-size:.85rem;margin:.2rem 0">E = ${pauliString(r.o.ex, r.o.ez)} · ${r.o.branch ? '旗標' : '一般'}分支 · n=${r.o.n}</p>
    <table class="hist"><tr><th></th><th>症狀 k0..k5</th><th>旗標 k0..k5</th></tr>${obsRow(r.o)}</table></div>`;
  $('cex').innerHTML = `<h3 style="margin-top:1.2rem">第一個反例</h3>
    <div style="display:grid;grid-template-columns:1fr 1fr;gap:1rem">${col(a, 'f₁')}${col(b, 'f₂')}</div>
    <p>${coarse ? '兩者的分支與<strong>最後一輪</strong>紀錄相同（較早的歷史不同）。' : ''}差異 D = E₁E₂ = <code>${pauliString(dx, dz)}</code>，症狀為零但不在穩定子群內，是邏輯算子。</p>`;
}
function showResidualFail(ids) {
  const rows = ids.slice(0, 8).map(i => { const { f, o } = run(i); return `<tr><td>${describeInput(f)}</td><td class="mono">${pauliString(o.ex, o.ez)}</td><td>${o.branch ? '旗標' : '一般'}</td></tr>`; }).join('');
  $('cex').innerHTML = `<h3 style="margin-top:1.2rem">殘餘界限失敗的配置（前 ${Math.min(8, ids.length)} 個，共 ${ids.length}）</h3>
    <table><tr><th>配置</th><th>修正前 E</th><th>分支</th></tr>${rows}</table>
    <p class="note">修正被改成恆等，所以殘餘 C·E 就是 E 本身；s=0 的初始錯誤要求殘餘為零，因此失敗。</p>`;
}

/* ---------- single-run explorer ---------- */
const OPS = ['op0 準備 q7', 'op1 準備 q8', 'op2 CNOT 1', 'op3 CNOT 2（旗標）', 'op4 CNOT 3', 'op5 CNOT 4', 'op6 CNOT 5（旗標）', 'op7 CNOT 6', 'op8 量測 q7', 'op9 量測 q8'];
function fillExplorer() {
  $('x-q').innerHTML = [...Array(7)].map((_, q) => `<option>${q}</option>`).join('');
  $('x-k').innerHTML = [...Array(6)].map((_, k) => `<option value="${k}">${stabName(k)}</option>`).join('');
  $('x-op').innerHTML = OPS.map((o, i) => `<option value="${i}">${o}</option>`).join('');
  $('x-op').value = '2';
  fillP();
  syncMode();
}
function fillP() {
  const op = +$('x-op').value;
  $('x-p').innerHTML = op >= 2 && op <= 7
    ? [...Array(15)].map((_, i) => `<option value="${i + 1}">${twoQubitPauli(i + 1)}（control·target）</option>`).join('')
    : '<option value="1">翻轉</option>';
}
function syncMode() {
  const m = +$('x-mode').value;
  document.querySelectorAll('.m1').forEach(e => e.style.display = m === 1 ? '' : 'none');
  document.querySelectorAll('.m2').forEach(e => e.style.display = m === 2 ? '' : 'none');
}
function explorerRun() {
  const m = +$('x-mode').value;
  const f = { mode: m, q: +$('x-q').value, a: +$('x-a').value, round: +$('x-r').value, k: +$('x-k').value, op: +$('x-op').value, p: +$('x-p').value };
  const o = F.explore(f.mode, f.q, f.a, f.round, f.k, f.op, f.p);
  if (!o) { $('x-out').innerHTML = '<p class="note">不是合法配置。</p>'; return; }
  const cx = o.ec & 127, cz = o.ec >> 7;
  const agree = cx === o.legacyCx && cz === o.legacyCz;
  $('x-out').innerHTML = `
    <p style="margin:.6rem 0 .3rem"><strong>${describeInput(f)}</strong> → ${o.branch ? '<span class="tag na">旗標分支</span>' : '<span class="tag">一般分支</span>'}，共 ${o.n} 輪</p>
    <table class="hist"><tr><th>輪</th><th>症狀 k0..k5（Z1 Z2 Z3 X1 X2 X3）</th><th>旗標 k0..k5</th></tr>${obsRow(o)}</table>
    <table>
      <tr><td>修正前資料錯誤 E</td><td class="mono">${pauliString(o.ex, o.ez)}</td></tr>
      <tr><td>decoder 修正 C</td><td class="mono">${pauliString(cx, cz)} ${agree ? '<span class="tag ok">legacy 相同</span>' : '<span class="tag bad">legacy 不同</span>'}</td></tr>
      <tr><td>殘餘 C·E</td><td class="mono">${pauliString(o.resX, o.resZ)}</td></tr>
      <tr><td>預算</td><td class="mono">r=${o.r}, s=${o.s}</td></tr>
      <tr><td>wt_min(C·E) ≤ s</td><td>${o.residualOk ? '<span class="tag ok">成立</span>' : '<span class="tag bad">不成立</span>'}</td></tr>
    </table>`;
}
function explorerRandom() {
  const i = Math.floor(Math.random() * F.count), f = F.input(i);
  $('x-mode').value = f.mode; syncMode();
  if (f.mode === 1) { $('x-q').value = f.q; $('x-a').value = f.a; }
  if (f.mode === 2) { $('x-r').value = f.round; $('x-k').value = f.k; $('x-op').value = f.op; fillP(); $('x-p').value = f.p; }
  explorerRun();
}

$('go').addEventListener('click', runAll);
$('x-mode').addEventListener('change', () => { syncMode(); explorerRun(); });
$('x-op').addEventListener('change', () => { fillP(); explorerRun(); });
['x-q', 'x-a', 'x-r', 'x-k', 'x-p'].forEach(id => $(id).addEventListener('change', explorerRun));
$('x-go').addEventListener('click', explorerRun);
$('x-rand').addEventListener('click', explorerRandom);
fillExplorer();
boot().catch(e => { $('go').textContent = '載入失敗'; $('verdict').innerHTML = box('bad', '載入失敗', String(e)); });
