// Export the raw CPAchecker run records of the compositional proof for the in-browser composer.
//   node tools/build_records.js <path to the proof folder>
// For each of the 181 partitions and 9 lemma/control cases it keeps result.json (local paths
// replaced by <CPA_ROOT> / <RUN_DIR>) plus every "Verification result" line of console.txt.
// The analysed input.i is not shipped: the browser rebuilds it from the harness and scalar.c
// and checks it against the recorded inputSHA256, exactly as compose.js checks input.i.
const fs = require('fs'), path = require('path'), crypto = require('crypto');
const ev = path.resolve(process.argv[2] || '../ftec_compositional_v4_1');
const out = path.join(__dirname, '..', 'ftec', 'data', 'records.json');
const sha = s => crypto.createHash('sha256').update(s).digest('hex');
const read = f => fs.readFileSync(f, 'utf8').replace(/^﻿/, '');
const manifest = JSON.parse(read(path.join(ev, 'manifest.json')));
const cases = JSON.parse(read(path.join(ev, 'cases.json')));

function record(dir) {
  const r = JSON.parse(read(path.join(dir, 'result.json')));
  const log = read(path.join(dir, 'console.txt'));
  const input = read(path.join(dir, 'input.i'));
  if (sha(input) !== r.inputSHA256) throw Error('input.i hash mismatch in ' + dir);
  const runDir = path.resolve(dir);
  const redact = a => a.split(r.cpaRoot).join('<CPA_ROOT>').split(runDir).join('<RUN_DIR>');
  const rec = { ...r, cpaRoot: '<CPA_ROOT>', command: r.command.map(redact) };
  rec.finalResults = [...log.matchAll(/Verification result: (TRUE|FALSE|UNKNOWN)\b[^\r\n]*/g)].map(m => m[0]);
  if (JSON.stringify(rec).includes('Users')) throw Error('unredacted path in ' + dir);
  return rec;
}
const data = { residual: {}, cases: {} };
for (const d of manifest.partitions) data.residual[d.id] = record(path.join(ev, 'results', 'residual', d.id));
for (const name of Object.keys(cases)) data.cases[name] = record(path.join(ev, 'results', name));
fs.writeFileSync(out, JSON.stringify(data) + '\n');
console.log(`wrote ${out}: ${Object.keys(data.residual).length} partition + ${Object.keys(data.cases).length} case records, ${fs.statSync(out).size} bytes`);
