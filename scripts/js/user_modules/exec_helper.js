function handleExecErrors(error, stdout, stderr) {
    if (error) {
        console.error(error);
        return;
    }

    console.error(stderr);
}

module.exports = { handleExecErrors }