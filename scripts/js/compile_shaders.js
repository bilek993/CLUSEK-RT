(async () => {
    console.log('Starting shaders compiler...');

    const glslcPath = process.argv[2];
    const inputDirPath = process.argv[3];
    const outputDirPath = process.argv[4];

    console.log(glslcPath); // TODO: Remove this
    console.log(inputDirPath); // TODO: Remove this
    console.log(outputDirPath); // TODO: Remove this

    console.log('Finishing shaders compiler...');
})();