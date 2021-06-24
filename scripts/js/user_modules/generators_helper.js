const { getFiles } = require('./files_helper');
const { readFileSync } = require('fs');

const SKIP_FILE_DECORATOR = 'GENERATOR_SKIP_THIS_FILE';
const GUARD_PREFIX = 'CLUSEK_RT_';

function checkIfIsSerializable(data, requiredFileDecorator) {
  return data.includes(requiredFileDecorator) && !data.includes(SKIP_FILE_DECORATOR);
}

function generateGuardName(namespace) {
  return GUARD_PREFIX + namespace.toUpperCase() + '_H'
}

async function itereateThroughCompatibleFiles(searchPath, requiredFileDecorator, callback) {
  for await (const filePath of getFiles(searchPath)) {
    if (filePath.toLowerCase().endsWith('.h')) {
      const readFileData = readFileSync(filePath);

      if (checkIfIsSerializable(readFileData, requiredFileDecorator)) {
        callback(filePath, readFileData);
      }
    }
  }
}

module.exports = { checkIfIsSerializable, generateGuardName, itereateThroughCompatibleFiles }