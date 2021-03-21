const { getFiles } = require('./user_modules/files_helper');
const { standarizePath, STANDARIZED_SPLIT_CHARACTER } = require('./user_modules/standarization');
const { readFileSync, writeFileSync } = require('fs');
const mustache = require('mustache');

const TEMPLATE_HEADER_PATH = '/templates/ConfigGeneratorTemplate.h';
const SKIP_FILE_DECORATOR = 'GENERATOR_SKIP_THIS_FILE';
const SERIALIZER_FILE_DECORATOR = 'SERIALIZE_OBJECT';
const GUARD_PREFIX = 'CLUSEK_RT_';

function checkIfIsSerializable(data) {
  return data.includes(SERIALIZER_FILE_DECORATOR) && !data.includes(SKIP_FILE_DECORATOR);
}

function generateOutputFileData(namespace, serializableObjectsData) {
  const view = {
    namespace: namespace,
    guardName: GUARD_PREFIX + namespace.toUpperCase() + '_H',
    serializableObjects: serializableObjectsData,
  };

  const template = readFileSync(__dirname + TEMPLATE_HEADER_PATH).toString();

  return mustache.render(template, view);
}

function generateOutputFile(namespace, outputDir, serializableObjectsData) {
  console.log('Generating output file...');

  const path = standarizePath(outputDir) + STANDARIZED_SPLIT_CHARACTER + namespace + '.h';
  const data = generateOutputFileData(namespace, serializableObjectsData);

  writeFileSync(path, data);

  console.log("Generated new file`" + path + "`!");
}

function generateObjectData(readData, filePath) {
  const objectName = readData.toString().match(/SERIALIZE_OBJECT\s*\(\s*(\w+)\s*\)/)[1];

  return {
    objectName: objectName,
    includeObjectPath: '..\\common\\ConfigData.h'
  };
}

(async () => {
  console.log('Starting serializer generator...');

  const serializerPath = process.argv[2];
  const serializerNamespace = process.argv[3];
  const searchPath = process.argv[4];

  let serializableObjectsData = [];

  for await (const filePath of getFiles(searchPath)) {
    if (filePath.toLowerCase().endsWith('.h')) {
      const readFileData = readFileSync(filePath);

      if (checkIfIsSerializable(readFileData)) {
        console.log("Found compatible object at '" + filePath + "'...");

        const objectData = generateObjectData(readFileData, filePath);
        serializableObjectsData.push(objectData);
      }
    }
  }

  generateOutputFile(serializerNamespace, serializerPath, serializableObjectsData);

  console.log('Finishing serializer generator...');
})();
