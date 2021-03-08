## Scripts

Scripts are dedicated tools written in JavaScript. With those tools, developers can speed-up development time and automate tedious tasks. All tools are developed for ease of use and described bellow with usage examples. Please note that some tools are used in the building process and called not by the developer, but from the C++ toolchain.

### generate_ascii_text.js

This tool can be used to generate good looking comments or logs that are easy to find. Example usage:

```
node .\generate_ascii_text.js 'CLUSEK-RT`
```

That comand will result in output:

```
 _  _____  _      _   _  _____  _____  _   __        ______  _____  _
( )/  __ \| |    | | | |/  ___||  ___|| | / /        | ___ \|_   _|( )
|/ | /  \/| |    | | | |\ `--. | |__  | |/ /  ______ | |_/ /  | |   \|
   | |    | |    | | | | `--. \|  __| |    \ |______||    /   | |
   | \__/\| |____| |_| |/\__/ /| |___ | |\  \        | |\ \   | |
    \____/\_____/ \___/ \____/ \____/ \_| \_/        \_| \_|  \_/
```