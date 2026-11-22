// Draws the flag measurement circuit of one weight-4 stabilizer, in the exact op0..op9 order of scalar.c.
// Z-type (k<3): data -> q7 CNOTs, flag q8 (|+>, X-basis) -> q7.  X-type (k>=3): control/target swapped.
export function drawCircuit(el, k) {
  const H = [120, 102, 85];
  const qs = [0, 1, 2, 3, 4, 5, 6].filter(j => (H[k % 3] >> j) & 1);
  const zType = k < 3;
  const rows = [...qs.map(q => 'q' + q), 'q7', 'q8'];
  const Y = i => 28 + i * 30 + (i >= 4 ? 12 : 0);
  const X = op => 92 + op * 54;
  const W = X(9) + 50, Hh = Y(5) + 52;
  let s = `<svg class="circuit" viewBox="0 0 ${W} ${Hh}" role="img" aria-label="穩定子 ${(zType ? 'Z' : 'X') + (k % 3 + 1)} 的旗標量測電路">`;
  rows.forEach((r, i) => {
    s += `<text x="8" y="${Y(i) + 4}">${r}${i === 4 ? ' 症狀' : i === 5 ? ' 旗標' : ''}</text>`;
    s += `<line class="wire" x1="${i >= 4 ? X(0) - 18 : 70}" y1="${Y(i)}" x2="${i >= 4 ? X(i === 4 ? 8 : 9) + 16 : W - 10}" y2="${Y(i)}"/>`;
  });
  const box = (op, i, txt) => s += `<rect class="gate" x="${X(op) - 17}" y="${Y(i) - 11}" width="34" height="22" rx="3"/><text x="${X(op)}" y="${Y(i) + 4}" text-anchor="middle">${txt}</text>`;
  const cnot = (op, c, t, flag) => {
    const cls = flag ? 'flag' : 'wire';
    s += `<line class="${cls}" x1="${X(op)}" y1="${Y(c)}" x2="${X(op)}" y2="${Y(t) + (Y(t) > Y(c) ? 8 : -8)}"/>`;
    s += `<circle class="${flag ? 'flagdot' : 'dot'}" cx="${X(op)}" cy="${Y(c)}" r="4"/>`;
    s += `<circle class="${flag ? 'flag' : 'gate'}" cx="${X(op)}" cy="${Y(t)}" r="8" style="fill:var(--panel)"/>`;
    s += `<line class="${flag ? 'flag' : 'wire'}" x1="${X(op) - 8}" y1="${Y(t)}" x2="${X(op) + 8}" y2="${Y(t)}" style="stroke:${flag ? '' : 'var(--ink)'}"/>`;
    s += `<line class="${flag ? 'flag' : 'wire'}" x1="${X(op)}" y1="${Y(t) - 8}" x2="${X(op)}" y2="${Y(t) + 8}" style="stroke:${flag ? '' : 'var(--ink)'}"/>`;
  };
  box(0, 4, zType ? '|0⟩' : '|+⟩');
  box(1, 5, zType ? '|+⟩' : '|0⟩');
  const dataOps = { 2: 0, 4: 1, 5: 2, 7: 3 };
  for (let op = 2; op <= 7; op++) {
    if (op === 3 || op === 6) zType ? cnot(op, 5, 4, true) : cnot(op, 4, 5, true);
    else zType ? cnot(op, dataOps[op], 4, false) : cnot(op, 4, dataOps[op], false);
  }
  box(8, 4, zType ? 'M_Z' : 'M_X');
  box(9, 5, zType ? 'M_X' : 'M_Z');
  for (let op = 0; op <= 9; op++) s += `<text class="lbl" x="${X(op)}" y="${Hh - 8}" text-anchor="middle">op${op}</text>`;
  s += '</svg>';
  el.innerHTML = s;
}
