const { getFiles } = require('./user_modules/files_helper');
const { standarizePath, STANDARIZED_SPLIT_CHARACTER } = require('./user_modules/standarization');
const { readFileSync, writeFileSync } = require('fs');
const mustache = require('mustache');

const TEMPLATE_HEADER_PATH = '/templates/ConfigGeneratorTemplate.h';
const SKIP_FILE_DECORATOR = 'GENERATOR_SKIP_THIS_FILE';
const CONFIG_FILE_DECORATOR = 'CONFIG_OBJECT';

function checkIfIsConfigFile(data) {
  return data.includes(CONFIG_FILE_DECORATOR) && !data.includes(SKIP_FILE_DECORATOR);
}

function generateData(data) {
  template = readFileSync(__dirname + TEMPLATE_HEADER_PATH).toString();
  view = {};

  return mustache.render(template, view);
}

function generateOutputPath(filePath, generatorPath) {
  let standarizedFilePath = standarizePath(filePath);
  let splittedStandarizedFilePath = standarizedFilePath.split(STANDARIZED_SPLIT_CHARACTER);
  
  let standarizedGeneratorPath = standarizePath(generatorPath);

  return standarizedGeneratorPath + splittedStandarizedFilePath[splittedStandarizedFilePath.length - 1];
}

(async () => {
    console.log('Starting config generator...');

    const generatorPath = process.argv[2];
    const searchPath = process.argv[3];

    for await (const filePath of getFiles(searchPath)) {
      if (filePath.toLowerCase().endsWith('.h')) {
          let data = readFileSync(filePath);

          if (checkIfIsConfigFile(data)) {
              console.log("Found config file at path '" + filePath + "'...");

              let generatedData = generateData(data);
              let generatedPath = generateOutputPath(filePath, generatorPath);

              writeFileSync(generatedPath, generatedData);

              console.log("Generated new file '" + generatedPath + "' with parser!");
          }
      }
    }

    console.log('Finishing config generator...');
  })();
  