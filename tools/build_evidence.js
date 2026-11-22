// Collect the stored CPAchecker evidence of ftec_compositional_v4_1 into ftec/data/evidence.json.
//   node tools/build_evidence.js <path to ftec_compositional_v4_1>
// Local absolute paths in recorded command lines are replaced by <CPA_ROOT> / <RUN_DIR>.
const fs = require('fs'), path = require('path'), crypto = require('crypto');
const ev = path.resolve(process.argv[2] || '../ftec_compositional_v4_1');
const out = path.join(__dirname, '..', 'ftec', 'data', 'evidence.json');
const sha = b => crypto.createHash('sha256').update(b).digest('hex');
const readJSON = f => JSON.parse(fs.readFileSync(f, 'utf8'));
const manifest = readJSON(path.join(ev, 'manifest.json'));
const composition = readJSON(path.join(ev, 'COMPOSITION.json'));
const cases = readJSON(path.join(ev, 'cases.json'));
const model = fs.readFileSync(path.join(ev, 'scalar.c'));

function record(dir) {
  const r = readJSON(path.join(dir, 'result.json'));
  const console_ = fs.readFileSync(path.join(dir, 'console.txt'), 'utf8');
  const input = fs.readFileSync(path.join(dir, 'input.i'));
  const cpu = /CPU time for analysis:\s+([\d.]+)s/.exec(console_);
  const verdict = /Verification result: ([^\r\n]*)/.exec(console_);
  const opts = [];
  for (let i = 0; i < r.command.length; i++) if (r.command[i] === '--option') opts.push(r.command[i + 1]);
  const config = r.command[r.command.indexOf('--config') + 1].replace(r.cpaRoot, '<CPA_ROOT>');
  return {
    status: r.status, elapsedSeconds: r.elapsedSeconds, analysisCPUSeconds: cpu ? +cpu[1] : null,
    started: r.started, timeLimitSeconds: r.seconds,
    modelSHA256: r.modelSHA256, sourceSHA256: r.sourceSHA256, inputSHA256: r.inputSHA256,
    inputHashMatches: sha(input) === r.inputSHA256,
    config, options: opts.filter(o => !o.startsWith('output.')),
    verdictLine: verdict ? verdict[1] : null,
  };
}
const partitions = manifest.partitions.map(d => {
  const key = `residual/${d.id}.c`;
  const rec = record(path.join(ev, 'results', 'residual', d.id));
  const src = fs.readFileSync(path.join(ev, key));
  return { ...d, ...rec, sourceHashMatches: sha(src) === manifest.files[key] && rec.sourceSHA256 === manifest.files[key] };
});
const lemmas = Object.entries(cases).map(([name, c]) => {
  const rec = record(path.join(ev, 'results', name));
  const src = fs.readFileSync(path.join(ev, name + '.c'));
  return { name, role: c.role, expected: c.expected, ...rec, sourceHashMatches: sha(src) === rec.sourceSHA256,
    asExpected: rec.status === c.expected };
});
const first = partitions[0];
const data = {
  generated: new Date().toISOString(),
  tool: 'CPAchecker 4.2.2 (self-reports "unknown version"), Java 21.0.12.1, MathSAT5 5.6.11',
  modelSHA256: sha(model),
  composition: { conclusion: composition.conclusion, method: composition.method, issues: composition.issues,
    steps: composition.steps, commonCorrection: composition.commonCorrection, directPairRuns: composition.directPairRuns },
  analysis: { config: first.config, options: first.options },
  coverage: manifest.coverage, correctionLine: manifest.correctionLine,
  partitions, lemmas,
};
const allTrue = partitions.every(p => p.status === 'TRUE' && p.modelSHA256 === data.modelSHA256 && p.inputHashMatches && p.sourceHashMatches);
const allLemmas = lemmas.every(l => l.asExpected && l.inputHashMatches && l.sourceHashMatches);
if (!allTrue || !allLemmas || partitions.length !== 181) throw Error('evidence does not check out');
fs.writeFileSync(out, JSON.stringify(data, null, 1) + '\n');
console.log(`wrote ${out}: ${partitions.length} partitions TRUE, ${lemmas.length} lemma/control cases as expected`);
