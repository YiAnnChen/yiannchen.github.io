// Draws the flag measurement circuit of one weight-4 stabilizer, in the exact op0..op9 order of scalar.c,
// on all 7 data wires so it is visible which data qubits each stabilizer touches.
// Z-type (k<3): data -> q7 CNOTs, flag q8 (|+>, X-basis) -> q7.  X-type (k>=3): control/target swapped.
// Every stabilizer uses the same schedule (data, flag, data, data, flag, data); only the data qubits differ.
export function drawCircuit(el, k) {
  const H = [120, 102, 85];
  const qs = [0, 1, 2, 3, 4, 5, 6].filter(j => (H[k % 3] >> j) & 1);
  const zType = k < 3;
  const SYN = 7, FLAG = 8; // row indices
  const Y = i => 24 + i * 26 + (i >= SYN ? 14 : 0);
  const X = op => 100 + op * 54;
  const W = X(9) + 50, Hh = Y(FLAG) + 46;
  let s = `<svg class="circuit" viewBox="0 0 ${W} ${Hh}" role="img" aria-label="穩定子 ${(zType ? 'Z' : 'X') + (k % 3 + 1)} 的旗標量測電路，作用在 q${qs.join('、q')}">`;
  for (let i = 0; i <= FLAG; i++) {
    const used = i >= SYN || qs.includes(i);
    const label = i < SYN ? 'q' + i : i === SYN ? 'q7 症狀' : 'q8 旗標';
    s += `<text x="8" y="${Y(i) + 4}" style="${used ? 'fill:var(--ink);font-weight:700' : 'opacity:.45'}">${label}</text>`;
    const x1 = i >= SYN ? X(0) - 18 : 74, x2 = i >= SYN ? X(i === SYN ? 8 : 9) + 16 : W - 10;
    s += `<line class="wire" x1="${x1}" y1="${Y(i)}" x2="${x2}" y2="${Y(i)}" style="${used ? '' : 'opacity:.3;stroke-dasharray:3 3'}"/>`;
  }
  const box = (op, i, txt) => s += `<rect class="gate" x="${X(op) - 17}" y="${Y(i) - 11}" width="34" height="22" rx="3"/><text x="${X(op)}" y="${Y(i) + 4}" text-anchor="middle">${txt}</text>`;
  const cnot = (op, c, t, flag) => {
    const cls = flag ? 'flag' : 'wire', ink = flag ? '' : 'stroke:var(--ink)';
    s += `<line class="${cls}" x1="${X(op)}" y1="${Y(c)}" x2="${X(op)}" y2="${Y(t) + (Y(t) > Y(c) ? 8 : -8)}" style="${ink}"/>`;
    s += `<circle class="${flag ? 'flagdot' : 'dot'}" cx="${X(op)}" cy="${Y(c)}" r="4"/>`;
    s += `<circle class="${flag ? 'flag' : 'gate'}" cx="${X(op)}" cy="${Y(t)}" r="8" style="fill:var(--panel)"/>`;
    s += `<line class="${cls}" x1="${X(op) - 8}" y1="${Y(t)}" x2="${X(op) + 8}" y2="${Y(t)}" style="${ink}"/>`;
    s += `<line class="${cls}" x1="${X(op)}" y1="${Y(t) - 8}" x2="${X(op)}" y2="${Y(t) + 8}" style="${ink}"/>`;
  };
  box(0, SYN, zType ? '|0⟩' : '|+⟩');
  box(1, FLAG, zType ? '|+⟩' : '|0⟩');
  const dataOps = { 2: qs[0], 4: qs[1], 5: qs[2], 7: qs[3] };
  for (let op = 2; op <= 7; op++) {
    if (op === 3 || op === 6) zType ? cnot(op, FLAG, SYN, true) : cnot(op, SYN, FLAG, true);
    else zType ? cnot(op, dataOps[op], SYN, false) : cnot(op, SYN, dataOps[op], false);
  }
  box(8, SYN, zType ? 'M_Z' : 'M_X');
  box(9, FLAG, zType ? 'M_X' : 'M_Z');
  for (let op = 0; op <= 9; op++) s += `<text class="lbl" x="${X(op)}" y="${Hh - 8}" text-anchor="middle">op${op}</text>`;
  s += '</svg>';
  el.innerHTML = s + `<p class="note" style="margin:.2rem 0 0">${(zType ? 'Z' : 'X') + (k % 3 + 1)} 作用在 <strong>q${qs.join('、q')}</strong>（H 的第 ${k % 3 + 1} 列 = ${H[k % 3]}）。</p>`;
}
