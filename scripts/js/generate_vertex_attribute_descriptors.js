const { generateGuardName, itereateThroughCompatibleFiles } = require('./user_modules/generators_helper');
const { readFileSync, writeFileSync } = require('fs');
const mustache = require('mustache');
const path = require('path');

const TEMPLATE_HEADER_PATH = '/templates/VertexAttributeDescriptorsTemplate.h';
const SERIALIZER_FILE_DECORATOR = 'VERTEX_STRUCTURE';

function generateOutputFileData(namespace, vertexStructures) {
  const view = {
    namespace: namespace,
    guardName: generateGuardName(namespace),
    vertexStructures: vertexStructures,
  };

  const template = readFileSync(__dirname + TEMPLATE_HEADER_PATH).toString();

  return mustache.render(template, view);
}

function generateOutputFile(namespace, outputDir, vertexStructures) {
  console.log('Generating output file...');

  const pathToOutputFile = path.join(outputDir, (namespace + '.h'));
  const data = generateOutputFileData(namespace, vertexStructures);

  writeFileSync(pathToOutputFile, data);

  console.log("Generated new file`" + pathToOutputFile + "`!");
}

function generateObjectData(readData, vertexDescriptorsPath, pathToVertexStructure) {
  const structName = readData.toString().match(/VERTEX_STRUCTURE\s*\(\s*(\w+)\s*\)/)[1];
  const includePath = path.relative(vertexDescriptorsPath, pathToVertexStructure);

  const vertexAttributesRegex = /GENERATE_ATTRIBUTE\s*\(\s*(\w+)\s*\,\s*(\d+)\s*,\s*(\d+)\s*,\s*(\w+)\s*\)/g;

  let match, vertexAttributes = [];
  while (match = vertexAttributesRegex.exec(readData.toString())) {
    vertexAttributes.push({name: match[1], binding: match[2], location: match[3], format: match[4]});
  }

  return {
    structName: structName,
    includePath: includePath,
    vertexAttributes: vertexAttributes,
  };
}

(async () => {
  console.log('Starting vertex data generator...');

  const vertexDescriptorsPath = process.argv[2];
  const vertexDescriptorsNamespace = process.argv[3];
  const searchPath = process.argv[4];

  let vertexStructures = [];

  await itereateThroughCompatibleFiles(searchPath, SERIALIZER_FILE_DECORATOR, (filePath, readFileData) => {
    const vertexData = generateObjectData(readFileData, vertexDescriptorsPath, filePath);
    vertexStructures.push(vertexData);
  });

  generateOutputFile(vertexDescriptorsNamespace, vertexDescriptorsPath, vertexStructures);

  console.log('Finishing vertex data generator...');
})();
  