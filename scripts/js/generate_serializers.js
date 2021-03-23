const { getFiles } = require('./user_modules/files_helper');
const { standarizePath, STANDARIZED_SPLIT_CHARACTER } = require('./user_modules/standarization');
const { readFileSync, writeFileSync } = require('fs');
const mustache = require('mustache');
const path = require('path');

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

function generateObjectData(readData, pathToSerializer, pathToSerializedObject) {
  const objectName = readData.toString().match(/SERIALIZE_OBJECT\s*\(\s*(\w+)\s*\)/)[1];
  const includeObjectPath = path.relative(pathToSerializer, pathToSerializedObject);

  const serializableFieldsRegex = /SERIALIZE_FIELD\s*\(\s*(\w+)\s*\,\s*([a-zA-Z0-9:]+)\s*\)/g;

  let match, serializableFields = [];
  while (match = serializableFieldsRegex.exec(readData.toString())) {
    serializableFields.push({field: match[1], type: match[2]});
  }

  return {
    objectName: objectName,
    includeObjectPath: includeObjectPath,
    serializableFields: serializableFields,
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

        const objectData = generateObjectData(readFileData, serializerPath, filePath);
        serializableObjectsData.push(objectData);
      }
    }
  }

  generateOutputFile(serializerNamespace, serializerPath, serializableObjectsData);

  console.log('Finishing serializer generator...');
})();
