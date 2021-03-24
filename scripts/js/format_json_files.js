const { getFiles } = require('./user_modules/files_helper');
const { readFileSync, writeFileSync } = require('fs');

const SEARCHED_EXTENSTION = '.json';

(async () => {
  console.log('Starting formatter...');

  const searchPath = process.argv[2] ?? '.';

  for await (const filePath of getFiles(searchPath)) {
    if (filePath.toLowerCase().endsWith(SEARCHED_EXTENSTION)) {
      console.log("Formatting '" + filePath + ' file...');

      let data = readFileSync(filePath);
      let formattedData = JSON.stringify(JSON.parse(data), null, 3);
      writeFileSync(filePath, formattedData);
    }
  }
})();
