const { resolve } = require('path');
const { readdir } = require('fs').promises;
const { readFileSync, writeFileSync } = require('fs');

async function* getFiles(dir) {
  const dirents = await readdir(dir, { withFileTypes: true });
  for (const dirent of dirents) {
    const res = resolve(dir, dirent.name);
    if (dirent.isDirectory()) {
      yield* getFiles(res);
    } else {
      yield res;
    }
  }
}

(async () => {
    console.log('Starting formatter...');

    const searchPath = process.argv[2] ?? '.';

    for await (const filePath of getFiles(searchPath)) {
      if (filePath.toLowerCase().endsWith('.json')) {
          console.log("Formatting '" + filePath + ' file...');

          let data = readFileSync(filePath);
          let formattedData = JSON.stringify(JSON.parse(data), null, 3);
          writeFileSync(filePath, formattedData);
      }
    }
  })()
  