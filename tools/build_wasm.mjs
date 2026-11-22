// Build ftec/assets/ftec.wasm from ftec/src/*.c with the YoWASP Clang/LLD toolchain
// (LLVM compiled to WebAssembly, so no native compiler is needed).
//
//   npm i @yowasp/clang            (in any folder; set YOWASP_CLANG to that node_modules path if needed)
//   node tools/build_wasm.mjs
//
// The build is freestanding: no libc, two tiny stand-in headers in ftec/src/wasm_include.
import { readFileSync, writeFileSync } from 'node:fs';
import { createHash } from 'node:crypto';
import { fileURLToPath, pathToFileURL } from 'node:url';
import path from 'node:path';

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), '..');
const src = path.join(root, 'ftec', 'src');
const mod = process.env.YOWASP_CLANG
  ? pathToFileURL(path.join(process.env.YOWASP_CLANG, '@yowasp', 'clang', 'gen', 'bundle.js')).href
  : '@yowasp/clang';
const { runClang } = await import(mod);

const read = f => readFileSync(path.join(src, f));
const files = {
  'ftec_wasm.c': read('ftec_wasm.c'),
  'scalar.c': read('scalar.c'),
  'legacy.c': read('legacy.c'),
  'inc': { 'stdio.h': read('wasm_include/stdio.h'), 'stdlib.h': read('wasm_include/stdlib.h') },
};
const sha = b => createHash('sha256').update(b).digest('hex');
const args = ['clang', '--target=wasm32', '-O2', '-nostdlib', '-ffreestanding', '-Iinc',
  '-Wno-everything', '-Wl,--no-entry', '-Wl,--export-memory', '-o', 'ftec.wasm', 'ftec_wasm.c'];
const out = await runClang(args, files);
const wasm = out['ftec.wasm'];
writeFileSync(path.join(root, 'ftec', 'assets', 'ftec.wasm'), wasm);
const info = {
  built: new Date().toISOString(),
  toolchain: '@yowasp/clang (LLVM/Clang for wasm32)',
  command: args.join(' '),
  inputs: { 'scalar.c': sha(files['scalar.c']), 'legacy.c': sha(files['legacy.c']), 'ftec_wasm.c': sha(files['ftec_wasm.c']) },
  wasmSHA256: sha(wasm), wasmBytes: wasm.length,
};
writeFileSync(path.join(root, 'ftec', 'data', 'wasm_build.json'), JSON.stringify(info, null, 2) + '\n');
console.log(info);
