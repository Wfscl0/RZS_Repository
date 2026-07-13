import process from 'node:process';
import esbuild from 'esbuild';

import common from './esbuild.common';

async function main(): Promise<void> {
  const context = await esbuild.context(common);
  await context.rebuild();
  await context.dispose();
  process.exit(0);
}

void main();
