STANDARIZED_SPLIT_CHARACTER = '\\';
STANDARIZED_NEW_LINE_CHARACTER = '\n';

function standarizePath(path) {
    return path.replace(/\//g, STANDARIZED_SPLIT_CHARACTER);
}

module.exports = { STANDARIZED_SPLIT_CHARACTER, STANDARIZED_NEW_LINE_CHARACTER, standarizePath }