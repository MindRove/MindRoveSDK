
# MindRove SDK


The following board is integrated: 
> MINDROVE_WIFI_BOARD

## Installation 
### Python 

    pip install mindrove

This will install the `mindrove` package and you can access it ( examples are provided under the /examples/python folder )

### C# 
To start using the MindRove specific C# library, 
- Step 1. - in your C# project in Visual Studio Solution Explorer `right click on References -> Add Reference -> Browse (left panel ) -> Click Browse ( near Ok button ) -> select win64/cs-bin/mindrove.dll`
- Step 2. -  copy the dlls from win64/lib to the folder where your .exe was generated. 

For a more comfortable usage, recommended to use **post-build event**s ( change %MINDROVESDK_LIB% with your path to the MindRoveSDK repository/win64/lib ) : 

    for /r "%MINDROVESDK_LIB%" %%f in (*.dll) do @xcopy "%%f" "$(TargetDir)" /Y

## Get started!
For using the SDK we provided the binaries for x64 win systems in win64/ and for linux in linux/ folder

To get started, we provided a C# code as a standalone example and the same code integrated into Unity. You can find these examples under the examples/ folder. 

## Further documentation
For further custom functionalities and ***MindRove specific*** documentation please visit our [docs](https://docs.mindrove.com). 

## Contribute
For any bugs or if the rest of the platform binaries are needed, please make an issue.

