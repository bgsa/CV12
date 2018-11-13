@echo off 

SET OUTPUT_DIR=..\..\..\..\lib
SET ZLIB_DIR=../zlib-dependency
SET TEMP_DIR="output"
IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%
mkdir %TEMP_DIR%
cd %TEMP_DIR%

echo Generating DEPENDENCY ZLIB x86 Shared and Static Lib ...
call cmake ../../zlib                                       ^
 	-DWIN32:BOOL=ON                                         ^
 	-DCMAKE_C_STANDARD:STRING=11                            ^
  	-DCMAKE_CXX_STANDARD:STRING=11                          ^
  	-DCMAKE_CXX_STANDARD_REQUIRED:BOOL=ON                   ^
  	-DCMAKE_INSTALL_PREFIX=%ZLIB_DIR%                       ^
 	-DCMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD:BOOL=ON     ^
 	-G "Visual Studio 15 2017"
	
call cmake --build  . --target install --config Release


cd ..\
IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%
mkdir %TEMP_DIR%
cd %TEMP_DIR%

SET BUILD_TYPE=Debug
echo Generating PNG x86 %BUILD_TYPE% Shared and Static Lib ...

call cmake ..\..\libpng16\                                           ^
	-DWIN32:BOOL=ON                                                  ^
	-DPNG_SHARED:BOOL=ON                                             ^
 	-DPNG_STATIC:BOOL=ON                                             ^
	-DCMAKE_C_STANDARD:STRING=11                                     ^
	-DCMAKE_CXX_STANDARD:STRING=11                                   ^
	-DCMAKE_CXX_STANDARD_REQUIRED:BOOL=ON                            ^
	-DPNG_BUILD_ZLIB:BOOL=OFF                                        ^
	-DZLIB_INCLUDE_DIR:PATH="C:\Users\Bruno\source\repos\PixelEffect\dependencies\scripts\zlib-dependency\include"                        ^
   	-DZLIB_LIBRARY:FILEPATH="%ZLIB_DIR%/lib/zlib"       ^
	-G "Visual Studio 15 2017"
	
call cmake --build  . --config %BUILD_TYPE%

cd %BUILD_TYPE%
rem rename libpng16d.dll libpng16.dll
rem rename libpng16d.pdb libpng16.pdb
rem rename libpng16d.lib libpng16.lib
xcopy libpng16.dll "%OUTPUT_DIR%\x86\%BUILD_TYPE%\" /Y /R
xcopy libpng16.pdb "%OUTPUT_DIR%\x86\%BUILD_TYPE%\" /Y /R
xcopy libpng16.lib "%OUTPUT_DIR%\x86\%BUILD_TYPE%\" /Y /R
cd ..\

SET BUILD_TYPE=Release
echo Generating PNG x86 %BUILD_TYPE% Shared and Static Lib ...

call cmake --build  . --config %BUILD_TYPE%

cd %BUILD_TYPE%
xcopy libpng16.dll "%OUTPUT_DIR%\x86\%BUILD_TYPE%\" /Y /R
xcopy libpng16.lib "%OUTPUT_DIR%\x86\%BUILD_TYPE%\" /Y /R
cd ..\

rmdir /S /Q "%ZLIB_DIR%"
cd ..\
IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%