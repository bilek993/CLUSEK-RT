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

function generateOutputFileData(namespace) {
  view = {
    namespace: namespace,
    guardName: GUARD_PREFIX + namespace.toUpperCase() + '_H',
    deserializers: {objectName: 'ConfigData'},
    serializers: {objectName: 'ConfigData'},
  };

  template = readFileSync(__dirname + TEMPLATE_HEADER_PATH).toString();

  return mustache.render(template, view);
}

function generateOutputFile(namespace, outputDir) {
  console.log('Generating output file...');

  let path = standarizePath(outputDir) + STANDARIZED_SPLIT_CHARACTER + namespace + '.h';
  let data = generateOutputFileData(namespace);

  writeFileSync(path, data);

  console.log("Generated new file`" + path + "`!");
}

(async () => {
    console.log('Starting serializer generator...');

    const serializerPath = process.argv[2];
    const serializerNamespace = process.argv[3];
    const searchPath = process.argv[4];

    for await (const filePath of getFiles(searchPath)) {
      if (filePath.toLowerCase().endsWith('.h')) {
          let readFileData = readFileSync(filePath);

          if (checkIfIsSerializable(readFileData)) {
            console.log("Found compatible object at '" + filePath + "'...");
          }
      }
    }

    generateOutputFile(serializerNamespace, serializerPath);

    console.log('Finishing serializer generator...');
  })();
  