const { getFiles } = require('./user_modules/files_helper');
const { handleExecErrors } = require('./user_modules/exec_helper');
const { unlinkSync } = require('fs');
const { exec } = require('child_process');

const path = require('path');

const SUPPORTED_EXTENSTION = [
    '.vert',
    '.frag',
    '.tesc',
    '.tese',
    '.geom',
    '.comp',
];

(async () => {
    console.log('Starting shaders compiler...');

    const glslcPath = process.argv[2];
    const inputDirPath = process.argv[3];
    const outputDirPath = process.argv[4];

    console.log('Cleaning up old compiled shaders...');
    for await (const outputFilePath of getFiles(outputDirPath)) {
        unlinkSync(outputFilePath);
    }

    for await (const inputFilePath of getFiles(inputDirPath)) {
        if (SUPPORTED_EXTENSTION.some((extenstion) => extenstion == path.extname(inputFilePath).toLocaleLowerCase())) {
            const outputFilePath = path.join(outputDirPath, (path.basename(inputFilePath, path.extname(inputFilePath)) + '.spv'));

            console.log(`Compiling shader '${path.basename(inputFilePath)}' as '${path.basename(outputFilePath)}'...`);

            exec(`${glslcPath} ${inputFilePath} -o ${outputFilePath} --target-env=vulkan1.2`, handleExecErrors);
        }
    }

    console.log('Finishing shaders compiler...');
})();