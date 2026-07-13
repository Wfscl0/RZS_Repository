import type esbuild from 'esbuild';

export default {
  entryPoints: { index: './src/index' },
  entryNames: '[name]',
  assetNames: '[name]',
  bundle: true,
  minify: false,
  outdir: './dist/',
  platform: 'browser',
  format: 'iife',
  globalName: 'edaEsbuildExportName',
  treeShaking: true,
  ignoreAnnotations: true,
} satisfies Parameters<(typeof esbuild)['build']>[0];
