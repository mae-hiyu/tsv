# Reflect #
*Reflect* is a physically based spectral renderer.

## About ##
![cover](https://bitbucket.org/byzin/reflect/wiki/images/cover.jpg "CornelBox!")

## Requirements ##

### Tools and libraries ###

Required tools and libraries are following.

- C++ compiler  
    * **GCC** (version 4.8.0 or higher)  
    * **Clang** (version 3.2 or higher)  
* **CMake** (version 2.8.12.0 or higher)  
* **Qt** (version 5.1.0 or higher)  

### Setup ###

We need to add the Qt qmake path to **$PATH**.  
``% export PATH=${qmake_path}:$PATH``  
On OSX, qmake path is maybe ``${qt_root}/${qt_version}/clang_64/bin``  

In addition, on Windows (MSYS), we need to add Qt gcc path to **$PATH**.  
``% export PATH=${qt_root}/Tools/mingw48_32/bin:$PATH``  

### Environments ###

Currently, I tested in the following environments.  

* Windows7 + MinGW32 GCC 4.8 + Qt 5.2.0  
* OSX Mavericks + Clang 3.4 + Qt 5.2.0  
* Ubuntu 12.04 + GCC 4.8 + Qt 5.2.0  

## How to compile ##
First, we need to move the build directory.  
``% cd ${project_root}/build``

Next, we generate a Makefile using cmake.  
On OSX or Linux  
``% cmake -DCMAKE_BUILD_TYPE=Release ..``

On Windows (MSYS)  
``% cmake -G "MSYS Makefiles" -DCMAKE_BUILD_TYPE=Release ..``

If default compiler is old version, we can specify the compiler to build.  
``% CXX=${compiler_path} cmake ${options} ..``

Make *Reflect*  
``% make``

## How to use ##

Please see [Wiki](https://bitbucket.org/byzin/reflect/wiki/Home "Reflect wiki").
