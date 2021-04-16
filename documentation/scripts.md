## Scripts

Scripts are dedicated tools written in JavaScript. With those tools, developers can speed-up development time and automate tedious tasks. All tools are developed for ease of use and described bellow with usage examples. Please note that some tools are used in the building process and called not by the developer, but from the C++ toolchain.

### generate_ascii_text.js

This tool can be used to generate good looking comments or logs that are easy to find. Example usage:

```
node ./generate_ascii_text.js 'CLUSEK-RT`
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

### format_json_files.js

This tool has been designed to format JSON files into the standardized form described [here](./resources_standards.md). This tool can be used manually, but it's also connected to the build process and called automatically.  Manual usage example:

```
node ./format_json_files.js ../../bin/
```

### generate_serializers.js

This tool has been designed to generate serializers due to a lack of reflection mechanism in C++. This tool can be used manually, but it's also connected to the build process and called automatically. Manual usage example:

```
node ./generate_serializers.js ./engine/generated/ ObjectSerializers ./engine/
```

### redistribute_engine.js

This script has been designed to deliver the final version of CLUSEK to the end-users and to help game developers ship their games with ease. This tool may look redundant due to CPack that is delivered with CMake, but due to problems with CPack, I decided to design this small tool. This tool has 1 required parameter (path to bin folder) and two optional parameters (version and project name). This script is called automatically when building a project in the Release mode. Manual usage example:

```
node .\redistribute_engine.js ..\..\bin\ 1.2.3 VK_RT
```