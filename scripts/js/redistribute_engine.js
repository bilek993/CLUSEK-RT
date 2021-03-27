const fs = require('fs');
const path = require('path');
const archiver = require('archiver');

console.log('Preparing CLUSEK-RT to redistribution...');

if (process.argv.length < 3) {
    console.error('\x1b[31m%s\x1b[0m', 'Failed! Path to bin folder not provided!');
    return;
}

const binPath = process.argv[2];
const projectVersion = process.argv[3] ?? '1.0.0';
const projectName = process.argv[4] ?? 'CLUSEK-RT';

const output = fs.createWriteStream(projectName + '-' + projectVersion + '.zip');
const archive = archiver('zip', {
    zlib: { level: 9 }
});

archive.on('warning', (err) => console.log(err));
archive.on('error', (err) => { throw err });
output.on('close', () => console.log('Finished with saving ' + archive.pointer() + ' total bytes.'));

archive.pipe(output);

archive.directory(binPath, projectName);

archive.finalize();