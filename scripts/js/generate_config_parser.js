const { getFiles } = require('./user_modules/files_helper');
const { readFileSync, writeFileSync } = require('fs');

function checkIfIsConfigFile(data) {

}

function generateData(data) {

}

function generateOutputPath(path) {

}

(async () => {
    console.log('Starting config generator...');

    const generatorPath = process.argv[2];
    const searchPath = process.argv[3];

    for await (const filePath of getFiles(searchPath)) {
      if (filePath.toLowerCase().endsWith('.h')) {
          let data = readFileSync(filePath);

          if (checkIfIsConfigFile(data)) {
              let generatedData = generateData(data);
              let generatedPath = generateOutputPath(filePath);

              writeFileSync(generatedPath, generatedData);
          }
      }
    }
  })()
  