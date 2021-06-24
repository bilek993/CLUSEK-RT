const SKIP_FILE_DECORATOR = 'GENERATOR_SKIP_THIS_FILE';
const GUARD_PREFIX = 'CLUSEK_RT_';

function checkIfIsSerializable(data, requiredFileDecorator) {
  return data.includes(requiredFileDecorator) && !data.includes(SKIP_FILE_DECORATOR);
}

function generateGuardName(namespace) {
    return GUARD_PREFIX + namespace.toUpperCase() + '_H'
}

module.exports = { checkIfIsSerializable, generateGuardName }