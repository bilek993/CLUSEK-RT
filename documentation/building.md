## Building from sources

Building CLUSEK-RT from the source code is the proper way of working with this game engine. Please, be aware that building from source will take some time and requires programming knowledge and experience with working with the terminal. 

Before proceeding please check if you are meeting requirements from [the requirements chapter](./requirements.md). That sections in details describe what is needed to build and use this engine.

### Clonning

We need to acquire a project before we will be able to build it. This project uses not only pure git but also LFS (for storing binary data) and submodules (for C++ dependencies). We need to download it all and to do that we can use this command:

```
git clone --recurse-submodules git@github.com:bilek993/CLUSEK-RT.git
```

That command should download the project with everything needed from this repository. With the latest git, we do not need to provide special flags to download binary LFS data, because it's just done by default. Thank you git team!

If you downloaded this repository without submodules, then you can download them manually by typing in the terminal:

```
git submodule init
git submodule update
```

### Acquiring script dependencies

This project uses dedicated scripts written in JavaScript for a better development experience. Those scripts can be downloaded from the external dependencies using the `npm` tool.

We need to start by opening the terminal and changing the directory to the main scripts folder. If you are already in the main project folder then you can just type:

```
cd ./scripts/js/
```

Next install all dependencies like this:

```
npm install
```

### Building on Linux

If you are working on Windows, then you can skip this section.

Linux is a terminal oriented operating system. In this documentation, I'm going to assume that you are using a terminal too. If you don't like this terminal approach, then you can easily apply knowledge from this section with GUI tools like the IDE of your choice.

Let's begin by creating a directory for storing toolchain data that is used to build this project. Let's name this directory `cmake-build` and  navigate to that directory by typing in the terminal this:

```
mkdir cmake-build
cd cmake-build
```

Next, ask CMake to prepare our project. If we don't provide build type into the CMake (`cmake ..`), then it will be prepared for debugging purposes only. Let's prepare the project in release mode:

```
cmake -DCMAKE_BUILD_TYPE=Release ..
```

If it finished with success then just call Make like this:

```
make
```

That's all! You are ready to use the CLUSEK-RT engine on Linux! If you get any error when calling `cmake` or `make` then you are probably missing building tools or an important library. You can download them using a package manager tool (like apt). For more information, I recommend [the requirements section](./requirements.md).

### Building on Windows

If you are working on Linux, then you can skip this section.

On the Windows operating system, most people use a different workflow than on Linux. Where on Linux terminal is first-class citizen, on Windows most people use UI. That is why I'm going to focus on building this project using UI. If you want to use a terminal, then you're a power-user and you will be able to do this on your own based on this UI approach.

There are two ways: use directly CMake or IDE. Let's start with the CMake approach.

Open CMake (cmake-gui). Click "Browse source" and select the CLUSEK-RT folder. Next select where to build the project. I recommend copying the path from the previous step and adding "/build" at the end. Now you need to click the "Configure" button and in the new window select tools that you are going to be using (for example Visual Studio 15 2017) and finish the process. After that click "Generate" and "Open Project" and you are done!

<p align="center">
<img src="./images/cmake_gui_windows.png">
</p>

There's also a second approach without that. You can use modern IDE like for example CLion or Visual Studio and select "Open CMake project" and just select the folder. That way it should work like a charm without generating a project with CMake (cmake-gui) tool.

That's all, you're ready to use CLUSEK-RT. Each approach should result in a successful building project without errors.
