
[![MindroveLogo](https://mindrove.com/wp-content/uploads/2023/04/MindRove_logo_2023.svg)](https://mindrove.com)
# <p align="center">Official SDK</p>
## Supporting SyncBox features! For more information, please visit the [website](https://mindrove.com/syncbox/).

## Supported platforms

Windows

MacOS

Linux

Raspberry Pi ( ARM64 and ARM32 )

## Documentation
Please visit [docs.mindrove.com](https://docs.mindrove.com). 

## Installation 
### Python 

    pip install mindrove

This will install the `mindrove` package and you can access it ( examples are provided under the /examples/python folder )

### C# 
To start using the MindRove specific C# library, 
- Step 1. - in your C# project in Visual Studio Solution Explorer `right click on References -> Add Reference -> Browse (left panel ) -> Click Browse ( near Ok button ) -> select win/cs-bin/mindrove.dll`
- Step 2. -  copy the dlls from win/x64 to the folder where your .exe was generated. 

For a more comfortable usage, recommended to use **post-build event**s ( change %MINDROVESDK_LIB% with your path to the MindRoveSDK repository/win/x64 ) : 

    for /r "%MINDROVESDK_LIB%" %%f in (*.dll) do @xcopy "%%f" "$(TargetDir)" /Y

### C++ 
Check out the MindRove specific C++ library.

### MATLAB 
Check out the MindRove specific MATLAB library.

## Library structure 
- inc - header files  
- win - windows binaries 
    - x64 
    - x86
    - cs-bin
    - matlab 
- linux - linux binaries 
    - x64 
    - aarch64 - libraries for Raspberry Pi 
    - arm32 
- osx - os x binaries 

## Get started!
For using the SDK we provided the binaries for x64 win systems in win/x64 and for linux in linux/ folder

To get started, we provided a C# code as a standalone example. You can find these examples under the examples/ folder. 

## Contribute
For any bugs or if the rest of the platform binaries are needed, please make an issue.

