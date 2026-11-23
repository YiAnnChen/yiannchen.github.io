// Runs the in-browser composer in Node: the real evidence must give PROVED_BY_COMPOSITION and
// every tamper scenario must give INCOMPLETE.
import { readFile } from 'node:fs/promises';
import { createHash } from 'node:crypto';
import { fileURLToPath } from 'node:url';
import path from 'node:path';
import { compose, TAMPERS } from '../ftec/assets/compose.js';

const base = path.resolve(path.dirname(fileURLToPath(import.meta.url)), '..', 'ftec');
const load = async p => (await readFile(path.join(base, p), 'utf8')).replace(/^﻿/, '');
const sha256 = async s => createHash('sha256').update(s).digest('hex');
let failed = 0;
for (const t of Object.keys(TAMPERS)) {
  const r = await compose({ load, sha256, tamper: t });
  const want = t === 'none' ? 'PROVED_BY_COMPOSITION' : 'INCOMPLETE';
  const ok = r.conclusion === want;
  if (!ok) failed++;
  console.log(`${ok ? 'PASS' : 'FAIL'} ${t}: ${r.conclusion} ${r.issues.slice(0, 2).join(' | ')}`);
}
console.log(failed ? `${failed} FAILED` : 'ALL PASS');
process.exit(failed ? 1 : 0);
