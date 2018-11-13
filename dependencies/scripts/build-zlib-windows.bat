@echo off 

SET OUTPUT_DIR=..\..\..\..\lib
SET TEMP_DIR="output"
IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%
mkdir %TEMP_DIR%
cd %TEMP_DIR%

SET BUILD_TYPE=Debug
echo Generating ZLIB x86 %BUILD_TYPE% Shared and Static Lib ...

call cmake ../../zlib                                  ^
	-DWIN32:BOOL=ON                                    ^
	-DCMAKE_C_STANDARD:STRING=11                       ^
	-DCMAKE_CXX_STANDARD:STRING=11                     ^
	-DCMAKE_CXX_STANDARD_REQUIRED:BOOL=ON              ^
	-DCMAKE_INSTALL_PREFIX="C:/" ^
	-G "Visual Studio 15 2017"

call cmake --build  . --config %BUILD_TYPE%

cd %BUILD_TYPE%
rename zlibd.lib zlib.lib
rename zlibd.dll zlib.dll
rename zlibd.pdb zlib.pdb
xcopy zlib.dll "%OUTPUT_DIR%\x86\%BUILD_TYPE%\" /Y /R
xcopy zlib.pdb "%OUTPUT_DIR%\x86\%BUILD_TYPE%\" /Y /R
xcopy zlib.lib "%OUTPUT_DIR%\x86\%BUILD_TYPE%\" /Y /R
cd ..\


SET BUILD_TYPE=Release
echo Generating ZLIB x86 %BUILD_TYPE% Shared and Static Lib ...

call cmake --build  . --config %BUILD_TYPE%



cd %BUILD_TYPE%
xcopy zlib.dll "%OUTPUT_DIR%\x86\%BUILD_TYPE%\" /Y /R
xcopy zlib.lib "%OUTPUT_DIR%\x86\%BUILD_TYPE%\" /Y /R
cd ..\..\

rem IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%
mkdir %TEMP_DIR%
cd %TEMP_DIR%

SET BUILD_TYPE=Debug
echo Generating ZLIB x64 %BUILD_TYPE% Shared and Static Lib ...

call cmake ../../zlib                                  ^
	-DWIN32:BOOL=ON                                    ^
	-DCMAKE_C_STANDARD:STRING=11                       ^
	-DCMAKE_CXX_STANDARD:STRING=11                     ^
	-DCMAKE_CXX_STANDARD_REQUIRED:BOOL=ON              ^
	-G "Visual Studio 15 2017 Win64"

call cmake --build  . --config %BUILD_TYPE%

cd %BUILD_TYPE%
rename zlibd.lib zlib.lib
rename zlibd.dll zlib.dll
rename zlibd.pdb zlib.pdb
xcopy zlib.dll "%OUTPUT_DIR%\x64\%BUILD_TYPE%\" /Y /R
xcopy zlib.pdb "%OUTPUT_DIR%\x64\%BUILD_TYPE%\" /Y /R
xcopy zlib.lib "%OUTPUT_DIR%\x64\%BUILD_TYPE%\" /Y /R
cd ..\


SET BUILD_TYPE=Release
echo Generating ZLIB x64 %BUILD_TYPE% Shared and Static Lib ...

call cmake --build  . --config %BUILD_TYPE%

cd %BUILD_TYPE%
xcopy zlib.dll "%OUTPUT_DIR%\x64\%BUILD_TYPE%\" /Y /R
xcopy zlib.lib "%OUTPUT_DIR%\x64\%BUILD_TYPE%\" /Y /R
cd ..\..\
