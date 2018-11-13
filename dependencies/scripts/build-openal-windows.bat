@echo off 

SET OUTPUT_DIR=..\..\..\..\lib
SET TEMP_DIR="output"
IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%
mkdir %TEMP_DIR%
cd %TEMP_DIR%

SET BUILD_TYPE=Debug
echo Generating OpenAL x86 %BUILD_TYPE% Static Lib ...

call cmake ..\..\OpenAL                               ^
	-DBUILD_SHARED_LIBS:BOOL=OFF                      ^
	-DLIBTYPE:STRING=STATIC                           ^
	-DCMAKE_BUILD_TYPE=%BUILD_TYPE%                   ^
	-DWIN32:BOOL=ON                                   ^
	-G "Visual Studio 15 2017"

call cmake --build  . --config %BUILD_TYPE%

cd %BUILD_TYPE%

xcopy OpenAL32.lib "%OUTPUT_DIR%\x86\%BUILD_TYPE%\" /Y /R
cd ..\OpenAL.dir\%BUILD_TYPE%
xcopy OpenAL.pdb "..\%OUTPUT_DIR%\x86\%BUILD_TYPE%\" /Y /R

cd ..\..\

SET BUILD_TYPE=Release
echo Generating Assimp x86 %BUILD_TYPE% Static Lib ...

call cmake --build  . --config %BUILD_TYPE%

cd %BUILD_TYPE%

xcopy OpenAL32.lib "%OUTPUT_DIR%\x86\%BUILD_TYPE%\" /Y /R

cd ..\

SET BUILD_TYPE=Debug
echo Generating OpenAL x86 %BUILD_TYPE% Shared Lib ...

call cmake ..\..\OpenAL                               ^
	-DBUILD_SHARED_LIBS:BOOL=ON                       ^
	-DLIBTYPE:STRING=SHARED                           ^
	-DCMAKE_BUILD_TYPE=%BUILD_TYPE%                   ^
	-DWIN32:BOOL=ON                                   ^
	-G "Visual Studio 15 2017"

call cmake --build  . --config %BUILD_TYPE%

cd %BUILD_TYPE%

xcopy OpenAL32.dll "%OUTPUT_DIR%\x86\%BUILD_TYPE%\" /Y /R

cd ..\

SET BUILD_TYPE=Release
echo Generating Assimp x86 %BUILD_TYPE% Shared Lib ...

call cmake --build  . --config %BUILD_TYPE%

cd %BUILD_TYPE%

xcopy OpenAL32.dll "%OUTPUT_DIR%\x86\%BUILD_TYPE%\" /Y /R

cd ..\

IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%