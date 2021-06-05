const art = require('ascii-art');

const DEFAULT_FONT = 'Doom';

if (process.argv.length < 3) {
    console.error('\x1b[31m%s\x1b[0m', 'Failed!');
    console.error('\x1b[31m%s\x1b[0m', 'Please provide correct parameters!!!');

    console.log();

    console.log('Example usages:');
    console.log("node .\\generate_ascii_text.js 'CLUSEK-RT'");
    console.log("node .\\generate_ascii_text.js 'CLUSEK-RT' '#'");
    console.log("node .\\generate_ascii_text.js 'CLUSEK-RT' 'print(''' ''');'");
    return;
}

const inputString = process.argv[2].replace(' ', '   ');
const opening = process.argv[3] ?? '';
const closing = process.argv[4] ?? '';

art.font(inputString, DEFAULT_FONT, function (error, rendered) {
    let splittedText = rendered.split('\n');
    splittedText.forEach((value) => {
        if (value.trim().length != 0) {
            console.log(opening + value + closing);
        }
    });
});
