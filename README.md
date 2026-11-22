# yiannchen.github.io

GitHub Pages site. Current project:

- **`ftec/`**: FTEC-verify v1, the compositional correctness proof of the fixed flag FTEC protocol
  (Steane [[7,1,3]], t=1, r+s≤1), with the stored CPAchecker evidence and a WebAssembly Playground
  that exhaustively re-checks the same model in the browser.

## Layout

| Path | What |
|---|---|
| `ftec/index.html` | overview, protocol, proof chain, evidence grid, formats, limits |
| `ftec/playground/` | WASM exhaustive checks + single-run explorer |
| `ftec/src/` | `scalar.c` (v4_1 model, byte-identical), `legacy.c` (v2 reference), lemma and partition sources, `ftec_wasm.c` harness |
| `ftec/data/evidence.json` | 181 partition + 9 lemma/control CPAchecker records (local paths redacted) |
| `ftec/assets/ftec.wasm` | built from `ftec/src` by `tools/build_wasm.mjs` |
| `tools/` | `build_wasm.mjs`, `test_wasm.mjs`, `build_evidence.js` |

## Rebuild

```sh
npm i @yowasp/clang                                   # LLVM/Clang compiled to WebAssembly
node tools/build_wasm.mjs                             # set YOWASP_CLANG=<node_modules dir> if installed elsewhere
node tools/test_wasm.mjs                              # all playground checks in Node
node tools/build_evidence.js <path to ftec_compositional_v4_1>
```

`.gitattributes` disables line-ending conversion so that the served `scalar.c` keeps the SHA-256
recorded in every CPAchecker result.
