const fs = require('fs');
const path = require('path');
const archiver = require('archiver');

function addDataDirectory(archive, binPath, projectName) {
    archive.directory(binPath + '/data/', projectName + '/data/');
}

function addExecutableFile(archive, binPath, projectName) {
    let inputFileName = process.platform == 'win32' ? 'CLUSEK-RT.exe' : 'CLUSEK-RT';
    let outputFileName = projectName + (process.platform == 'win32' ? '.exe' : '');

    archive.file(binPath + '/' + inputFileName, { prefix: projectName, name: outputFileName });
}

function tryPack() {
    console.log('Preparing CLUSEK-RT to redistribution...');

    if (process.argv.length < 3) {
        console.error('\x1b[31m%s\x1b[0m', 'Failed! Path to bin folder not provided!');
        return;
    }

    const binPath = process.argv[2];
    const projectVersion = process.argv[3] ?? '1.0.0';
    const projectName = process.argv[4] ?? 'CLUSEK-RT';

    const output = fs.createWriteStream(projectName + '-' + projectVersion + '-' + process.platform + '.zip');
    const archive = archiver('zip', {
        zlib: { level: 9 }
    });

    archive.on('warning', (err) => console.log(err));
    archive.on('error', (err) => { throw err });
    output.on('close', () => console.log('Finished with saving ' + archive.pointer() + ' total bytes.'));

    archive.pipe(output);

    addDataDirectory(archive, binPath, projectName);
    addExecutableFile(archive, binPath, projectName);

    archive.finalize();
}

tryPack();