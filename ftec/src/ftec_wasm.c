/* Browser playground harness for the fixed FTEC protocol (Steane [[7,1,3]], t=1, r+s<=1).
 *
 * Built freestanding for wasm32 (no libc); see tools/build_wasm.mjs.
 * It includes, byte for byte unchanged:
 *   scalar.c  - the v4_1 model that every CPAchecker run analysed (SHA-256 40dc06b2...)
 *   legacy.c  - the v2 independent struct/loop implementation (same one native_compare uses)
 * and re-does, by plain enumeration, what native_check/native_compare_v4_1.c does, plus
 * exhaustive checks of the finite-domain lemmas and of the pair property itself.
 *
 * Nothing here is an input to the CPAchecker proof; it is a second, independent check
 * that runs in the reader's browser.
 */
#define FTEC_NATIVE 1
#define parity old_parity
#define syndrome old_syndrome
#define correction legacy_correction /* scalar.c defines correction() */
#include "legacy.c"
#undef parity
#undef syndrome
#undef correction
#include "scalar.c"

#define EXPORT(name) __attribute__((export_name(#name)))
__attribute__((import_module("env"), import_name("report")))
void js_report(int source, int code);

/* clang may lower struct zero-initialisation to memset/memcpy calls. */
void *memset(void *d, int c, unsigned long n) {
  unsigned char *p = d; while (n--) *p++ = (unsigned char)c; return d; }
void *memcpy(void *d, const void *s, unsigned long n) {
  unsigned char *p = d; const unsigned char *q = s; while (n--) *p++ = *q++; return d; }

unsigned __VERIFIER_nondet_uint(void) { return 0u; }
/* A failed check() inside scalar.c: tell the page, then trap (JS sees a RuntimeError). */
void __VERIFIER_error(void) { js_report(1, 0); __builtin_trap(); }
/* A failed require() inside legacy.c: report its error id; legacy.c then calls abort(). */
void ftec_legacy_error(int code) { js_report(2, code); }

#define NCFG 1714u
static Input cfg[NCFG];
static unsigned ncfg;
/* Per-configuration results of the last check_config() sweep. */
static unsigned o_n[NCFG], o_b[NCFG], o_h[NCFG][8], o_ex[NCFG], o_ez[NCFG], o_c[NCFG], o_s[NCFG];

/* Enumerate the legal input domain in the same order as native_compare / partitions.js. */
EXPORT(init) unsigned init(void) {
  unsigned q, a, rr, k, op, p; Input f = {0};
  ncfg = 0; cfg[ncfg++] = f;
  f.mode = 1;
  for (q = 0; q < 7; q++) for (a = 1; a <= 3; a++) { f.q = q; f.a = a; cfg[ncfg++] = f; }
  f.mode = 2; f.q = 0; f.a = 0;
  for (rr = 1; rr <= 3; rr++) for (k = 0; k < 6; k++) for (op = 0; op < 10; op++)
    for (p = 1; p <= (op >= 2 && op <= 7 ? 15u : 1u); p++) {
      f.round = rr; f.k = k; f.op = op; f.p = p; cfg[ncfg++] = f; }
  return ncfg;
}
static unsigned inp[7];
EXPORT(config_input) unsigned *config_input(unsigned i) {
  Input f = cfg[i];
  inp[0] = f.mode; inp[1] = f.q; inp[2] = f.a; inp[3] = f.round; inp[4] = f.k; inp[5] = f.op; inp[6] = f.p;
  return inp;
}

/* 16,384 data Paulis: scalar.c helpers vs legacy.c brute force. Returns #mismatches in [lo,hi). */
EXPORT(check_paulis) unsigned check_paulis(unsigned lo, unsigned hi) {
  unsigned i, bad = 0;
  for (i = lo; i < hi; i++) {
    unsigned x = i >> 7, z = i & 127u; Pauli e = {x, z};
    if (sy(x, z) != old_syndrome(e)) bad++;
    if (member(x, z) != in_stabilizer(e)) bad++;
    if (residual(x, z, 0) != (min_weight(e) == 0)) bad++;
    if (residual(x, z, 1) != (min_weight(e) <= 1)) bad++;
  }
  return bad;
}

/* Failure bits returned by check_config(). */
#define F_E       1u   /* final data error E differs from legacy */
#define F_RS      2u   /* fault counters r,s differ */
#define F_NB      4u   /* round count / branch differ */
#define F_HIST    8u   /* syndrome+flag history differs */
#define F_COR    16u   /* scalar correction differs from legacy decoder */
#define F_OBS    32u   /* ec != correction(observation) */
#define F_BUDGET 64u   /* r+s > 1 */
#define F_RES   128u   /* residual(C E, s) fails (scalar.c) */
#define F_RESL  256u   /* min_weight(C E) <= s fails (legacy.c) */

/* mutation: 0 = protocol as verified; 1 = control A (normal-branch correction replaced by identity). */
EXPORT(check_config) unsigned check_config(unsigned i, unsigned mutation) {
  Input f = cfg[i]; Result b = run_model(f); Pauli c = legacy_correction(&b);
  unsigned fl = 0, j, cor; Pauli cc;
  run(f.mode, f.q, f.a, f.round, f.k, f.op, f.p);
  unsigned hh[8] = {eh0, eh1, eh2, eh3, eh4, eh5, eh6, eh7};
  if (!(ex == b.e.x && ez == b.e.z)) fl |= F_E;
  if (!(er == b.r && es == b.s)) fl |= F_RS;
  if (!(en == b.n && eb == b.branch)) fl |= F_NB;
  for (j = 0; j < 8; j++) if (hh[j] != b.history[j]) fl |= F_HIST;
  if (!((ec & 127u) == c.x && (ec >> 7) == c.z)) fl |= F_COR;
  if (ec != correction(en, eb, eh0, eh1, eh2, eh3, eh4, eh5, eh6, eh7)) fl |= F_OBS;
  if (!(er <= 1u && es <= 1u && er + es <= 1u)) fl |= F_BUDGET;
  cor = ec;
  if (mutation == 1u && eb == 0u) cor = 0u;
  if (!residual(ex ^ (cor & 127u), ez ^ (cor >> 7), es)) fl |= F_RES;
  cc.x = cor & 127u; cc.z = cor >> 7;
  if (!(min_weight(multiply(cc, b.e)) <= b.s)) fl |= F_RESL;
  o_n[i] = en; o_b[i] = eb; o_ex[i] = ex; o_ez[i] = ez; o_c[i] = cor; o_s[i] = es;
  for (j = 0; j < 8; j++) o_h[i][j] = hh[j];
  return fl;
}

/* Exhaustive finite-domain versions of three CPAchecker lemmas. Return #violations. */
EXPORT(lemma_budget_relaxation) unsigned lemma_budget_relaxation(void) {
  unsigned x, z, r, s, bad = 0;
  for (x = 0; x < 128; x++) for (z = 0; z < 128; z++)
    for (r = 0; r <= 1; r++) for (s = 0; s <= 1; s++) {
      if (r + s > 1u) continue;
      if (!residual(x, z, s)) continue;
      if (!residual(x, z, 1u)) bad++;
    }
  return bad;
}
EXPORT(lemma_residual_signature) unsigned lemma_residual_signature(void) {
  unsigned x, z, v, bad = 0;
  for (x = 0; x < 128; x++) for (z = 0; z < 128; z++) {
    v = sy(x, z);
    if (!residual(x, z, 1u)) continue;
    if (parity(x) != ((v & 7u) != 0u)) bad++;
    if (parity(z) != ((v >> 3) != 0u)) bad++;
  }
  return bad;
}
/* signature_pair: A_i = C E_i. Since E1^E2 = A1^A2 for every common C, enumerating all
 * (A1,A2) pairs that satisfy the signature premise covers every (E1,E2,C). */
static unsigned sigs[4096];
EXPORT(lemma_signature_pair) unsigned lemma_signature_pair(void) {
  unsigned x, z, v, n = 0, i, j, bad = 0, dx, dz;
  for (x = 0; x < 128; x++) for (z = 0; z < 128; z++) {
    v = sy(x, z);
    if (parity(x) == ((v & 7u) != 0u) && parity(z) == ((v >> 3) != 0u)) sigs[n++] = x | (z << 7);
  }
  if (n != 4096u) return 0xFFFFFFFFu;
  for (i = 0; i < n; i++) for (j = 0; j < n; j++) {
    dx = (sigs[i] ^ sigs[j]) & 127u; dz = (sigs[i] ^ sigs[j]) >> 7;
    if (!(sy(dx, dz) != 0u || member(dx, dz))) bad++;
  }
  return bad;
}

/* Direct pair property over every ordered pair of legal executions (requires a prior
 * check_config sweep). coarse=1 is control B: the observation keeps only the branch and the
 * LAST round's word, as if the decoder ignored the earlier history.
 * Returns #violations; pair_stats() gives #compared pairs and the first counterexample. */
static unsigned st[4];
static int same_obs(unsigned i, unsigned j, unsigned coarse) {
  unsigned k;
  if (o_b[i] != o_b[j]) return 0;
  if (coarse) return o_h[i][o_n[i] - 1u] == o_h[j][o_n[j] - 1u];
  if (o_n[i] != o_n[j]) return 0;
  for (k = 0; k < 8; k++) if (o_h[i][k] != o_h[j][k]) return 0;
  return 1;
}
EXPORT(check_pairs) unsigned check_pairs(unsigned coarse) {
  unsigned i, j, dx, dz, bad = 0, pairs = 0;
  st[1] = st[2] = 0xFFFFFFFFu;
  for (i = 0; i < ncfg; i++) for (j = 0; j < ncfg; j++) {
    if (!same_obs(i, j, coarse)) continue;
    pairs++;
    dx = o_ex[i] ^ o_ex[j]; dz = o_ez[i] ^ o_ez[j];
    if (!(sy(dx, dz) != 0u || member(dx, dz))) {
      if (!bad) { st[1] = i; st[2] = j; }
      bad++;
    }
  }
  st[0] = pairs; st[3] = bad;
  return bad;
}
EXPORT(pair_stats) unsigned *pair_stats(void) { return st; }

/* Single-run explorer. Returns a pointer to 20 words, or 0 if the input is not legal:
 * [0]ex [1]ez [2]r [3]s [4]n [5]branch [6]ec [7..14]h0..h7 [15]residual_ok
 * [16]legacy_cx [17]legacy_cz [18]residual_x [19]residual_z */
static unsigned out[20];
EXPORT(explore) unsigned *explore(unsigned m, unsigned q, unsigned a, unsigned fr, unsigned fk, unsigned fo, unsigned fp) {
  Input f = {0}; Result b; Pauli c;
  if (m == 0u) { q = a = fr = fk = fo = fp = 0u; }
  else if (m == 1u) { fr = fk = fo = fp = 0u; }
  else { q = a = 0u; }
  if (!valid(m, q, a, fr, fk, fo, fp)) return 0;
  f.mode = m; f.q = q; f.a = a; f.round = fr; f.k = fk; f.op = fo; f.p = fp;
  b = run_model(f); c = legacy_correction(&b);
  run(m, q, a, fr, fk, fo, fp);
  out[0] = ex; out[1] = ez; out[2] = er; out[3] = es; out[4] = en; out[5] = eb; out[6] = ec;
  out[7] = eh0; out[8] = eh1; out[9] = eh2; out[10] = eh3; out[11] = eh4; out[12] = eh5; out[13] = eh6; out[14] = eh7;
  out[15] = (unsigned)residual(ex ^ (ec & 127u), ez ^ (ec >> 7), es);
  out[16] = c.x; out[17] = c.z; out[18] = ex ^ (ec & 127u); out[19] = ez ^ (ec >> 7);
  return out;
}
EXPORT(flag_table_size) unsigned flag_table_size(void) { return FLAG_COUNT; }
