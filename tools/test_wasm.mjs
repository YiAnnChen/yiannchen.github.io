// Runs every playground check against ftec/assets/ftec.wasm in Node and asserts the expected outcomes.
import { readFileSync } from 'node:fs';
import { fileURLToPath } from 'node:url';
import path from 'node:path';
import { loadFtec, EQUIV_MASK, RESIDUAL_MASK, describeInput } from '../ftec/assets/ftec-core.js';

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), '..');
const F = await loadFtec(readFileSync(path.join(root, 'ftec', 'assets', 'ftec.wasm')));
let failed = 0;
const expect = (name, ok, detail = '') => { console.log(`${ok ? 'PASS' : 'FAIL'} ${name} ${detail}`); if (!ok) failed++; };

expect('domain size', F.count === 1714, F.count);
expect('flag table size', F.flagTableSize === 288, F.flagTableSize);
expect('16384 Paulis', F.checkPaulis(0, 16384) === 0);
for (const [mut, label] of [[0, 'protocol'], [1, 'control A']]) {
  let eq = 0, res = 0; const resIds = [];
  for (let i = 0; i < F.count; i++) {
    const fl = F.checkConfig(i, mut);
    if (fl & EQUIV_MASK) eq++;
    if (fl & RESIDUAL_MASK) { res++; if (resIds.length < 3) resIds.push(describeInput(F.input(i))); }
  }
  if (mut === 0) {
    expect(`${label}: equivalence`, eq === 0, eq);
    expect(`${label}: residual`, res === 0, res);
    const p = F.checkPairs(0);
    expect(`${label}: pairs`, p.bad === 0, JSON.stringify(p));
    const pc = F.checkPairs(1);
    expect('control B: coarse observation finds counterexample', pc.bad > 0, JSON.stringify(pc) +
      (pc.first ? ' ' + pc.first.map(i => describeInput(F.input(i))).join(' | ') : ''));
  } else {
    expect(`${label}: residual fails`, res > 0, `${res} e.g. ${resIds.join('; ')}`);
    const p = F.checkPairs(0);
    expect(`${label}: pairs still hold`, p.bad === 0, JSON.stringify(p));
  }
}
expect('lemma budget_relaxation', F.lemmaBudget() === 0);
expect('lemma residual_signature', F.lemmaSignature() === 0);
let t = Date.now();
expect('lemma signature_pair', F.lemmaSignaturePair() === 0, `${Date.now() - t} ms`);
const r = F.explore(2, 0, 0, 1, 0, 2, 3);
expect('explore', r && r.residualOk, JSON.stringify(r));
expect('explore invalid', F.explore(2, 0, 0, 4, 0, 0, 1) === null);
expect('no traps reported', F.reports.length === 0, JSON.stringify(F.reports));
console.log(failed ? `${failed} FAILED` : 'ALL PASS');
process.exit(failed ? 1 : 0);
