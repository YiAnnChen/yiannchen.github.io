// Thin wrapper around ftec.wasm, shared by the playground page and tools/test_wasm.mjs.
export const FAIL_BITS = [
  [1, 'E', '最終資料錯誤 E 與 legacy 不同'],
  [2, 'r,s', '故障計數 r、s 不同'],
  [4, 'n,b', '輪數或分支不同'],
  [8, 'history', '症狀／旗標歷史不同'],
  [16, 'decoder', '修正 C 與 legacy decoder 不同'],
  [32, 'obs', 'ec ≠ correction(觀測)'],
  [64, 'budget', 'r+s > 1'],
  [128, 'residual', 'residual(C·E, s) 不成立（scalar.c）'],
  [256, 'residualL', 'min_wt(C·E) ≤ s 不成立（legacy.c）'],
];
export const EQUIV_MASK = 1 | 2 | 4 | 8 | 16 | 32 | 64;
export const RESIDUAL_MASK = 128 | 256;

export async function loadFtec(bytes) {
  const reports = [];
  const { instance } = await WebAssembly.instantiate(bytes, {
    env: { report: (source, code) => reports.push({ source, code }) },
  });
  const x = instance.exports;
  const u32 = (ptr, n) => Array.from(new Uint32Array(x.memory.buffer, ptr, n));
  const n = x.init();
  return {
    reports,
    count: n,
    flagTableSize: x.flag_table_size(),
    input(i) {
      const [mode, q, a, round, k, op, p] = u32(x.config_input(i), 7);
      return { mode, q, a, round, k, op, p };
    },
    checkPaulis: (lo, hi) => x.check_paulis(lo, hi),
    checkConfig: (i, mutation) => x.check_config(i, mutation),
    lemmaBudget: () => x.lemma_budget_relaxation(),
    lemmaSignature: () => x.lemma_residual_signature(),
    lemmaSignaturePair: () => x.lemma_signature_pair(),
    checkPairs(coarse) {
      const bad = x.check_pairs(coarse);
      const [pairs, i, j] = u32(x.pair_stats(), 4);
      return { bad, pairs, first: bad ? [i, j] : null };
    },
    explore(m, q, a, fr, fk, fo, fp) {
      const ptr = x.explore(m, q, a, fr, fk, fo, fp);
      if (!ptr) return null;
      const w = u32(ptr, 20);
      return { ex: w[0], ez: w[1], r: w[2], s: w[3], n: w[4], branch: w[5], ec: w[6],
        h: w.slice(7, 15), residualOk: !!w[15], legacyCx: w[16], legacyCz: w[17], resX: w[18], resZ: w[19] };
    },
  };
}

// Pauli (x,z) masks on 7 data qubits -> e.g. "X0 Z3 Y5" or "I".
export function pauliString(x, z, nq = 7) {
  const parts = [];
  for (let q = 0; q < nq; q++) {
    const a = (x >> q) & 1, b = (z >> q) & 1;
    if (a || b) parts.push((a && b ? 'Y' : a ? 'X' : 'Z') + q);
  }
  return parts.length ? parts.join(' ') : 'I';
}
export function describeInput(f) {
  if (f.mode === 0) return '無錯誤';
  if (f.mode === 1) return `初始 ${'XZY'[f.a - 1]}${f.q}`;
  const opName = f.op < 2 ? ['準備 q7', '準備 q8'][f.op] : f.op < 8 ? `CNOT${f.op - 1} 後 P=${twoQubitPauli(f.p)}` : ['量測 q7', '量測 q8'][f.op - 8];
  return `第 ${f.round} 輪 · 穩定子 ${stabName(f.k)} · ${opName}`;
}
export function stabName(k) { return (k < 3 ? 'Z' : 'X') + ((k % 3) + 1); }
// p in 1..15: low 2 bits act on control, high 2 bits on target (bit0 X, bit1 Z).
export function twoQubitPauli(p) {
  const one = v => ['I', 'X', 'Z', 'Y'][v];
  return one(p & 3) + one((p >> 2) & 3);
}
