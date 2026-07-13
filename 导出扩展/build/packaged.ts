import path from 'node:path';
import fs from 'fs-extra';
import ignore from 'ignore';
import JSZip from 'jszip';

import extensionConfig from '../extension.json';

async function main(): Promise<void> {
  const projectRoot = path.resolve(__dirname, '..');
  const outputDirectory = path.join(__dirname, 'dist');
  const ignoreRules = (await fs.readFile(path.join(projectRoot, '.edaignore'), 'utf8'))
    .split(/\r?\n/u)
    .map((line) => line.trim())
    .filter(Boolean);
  const filter = ignore().add(ignoreRules);
  const entries = await fs.readdir(projectRoot, { recursive: true, encoding: 'utf8' });
  const files = filter
    .filter(entries.map((entry) => entry.replaceAll('\\', '/')))
    .filter((entry) => fs.statSync(path.join(projectRoot, entry)).isFile());

  const archive = new JSZip();
  for (const file of files) {
    archive.file(file, await fs.readFile(path.join(projectRoot, file)));
  }

  await fs.ensureDir(outputDirectory);
  const outputPath = path.join(
    outputDirectory,
    `${extensionConfig.name}_v${extensionConfig.version}.eext`,
  );
  const buffer = await archive.generateAsync({
    type: 'nodebuffer',
    compression: 'DEFLATE',
    compressionOptions: { level: 9 },
  });
  await fs.writeFile(outputPath, buffer);
  process.stdout.write(`${outputPath}\n`);
}

void main();
