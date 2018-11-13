@echo off 

SET BUILD_TYPE=Release
SET OUTPUT_DIR=../../../lib/x86/%BUILD_TYPE%/

SET TEMP_DIR="output"
IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%
mkdir %TEMP_DIR%
cd %TEMP_DIR%

echo Generating Freetype Release x86 Shared Lib ...

call cmake ..\..\freetype                              ^
	-DCMAKE_BUILD_TYPE=%BUILD_TYPE%                    ^
	-DBUILD_SHARED_LIBS:BOOL=ON                        ^
	-DWIN32:BOOL=ON                                    ^
	-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=%OUTPUT_DIR%      ^
	-DCMAKE_C_FLAGS=-m32                               ^
	-DCMAKE_CXX_FLAGS=-m32                             ^
	-G "MinGW Makefiles"

call cmake --build  .

rename libfreetype.dll freetype.dll
xcopy freetype.dll "..\..\..\lib\x86\%BUILD_TYPE%\" /Y /R
cd ..\

echo Generating Freetype Debug x86 Shared Lib ...

SET BUILD_TYPE=Debug
SET OUTPUT_DIR=../../../lib/x86/%BUILD_TYPE%/
IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%
mkdir %TEMP_DIR%
cd %TEMP_DIR%

echo Generating Freetype Debug x86 Shared Lib ...

call cmake ..\..\freetype                              ^
	-DCMAKE_BUILD_TYPE=%BUILD_TYPE%                    ^
	-DBUILD_SHARED_LIBS:BOOL=ON                        ^
	-DWIN32:BOOL=ON                                    ^
	-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=%OUTPUT_DIR%      ^
	-DCMAKE_C_FLAGS=-m32                               ^
	-DCMAKE_CXX_FLAGS=-m32                             ^
	-G "MinGW Makefiles"

call cmake --build  .

rename libfreetyped.dll freetype.dll
xcopy freetype.dll "..\..\..\lib\x86\%BUILD_TYPE%\" /Y /R
cd ..\

SET BUILD_TYPE=Release
SET OUTPUT_DIR=../../../lib/x86/%BUILD_TYPE%/
IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%
mkdir %TEMP_DIR%
cd %TEMP_DIR%

echo Generating Freetype %BUILD_TYPE% x86 Static Lib ...

call cmake ..\..\freetype                              ^
	-DBUILD_SHARED_LIBS:BOOL=OFF                       ^
 	-DWIN32:BOOL=ON                                    ^
 	-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=%OUTPUT_DIR%      ^
 	-G "Visual Studio 15 2017"

call cmake --build  . --config %BUILD_TYPE%

cd %BUILD_TYPE%
xcopy freetype.lib "..\..\..\..\lib\x86\%BUILD_TYPE%\" /Y /R
cd ..\

call cmake --build  . --config Debug

cd Debug
rename freetyped.lib freetype.lib
xcopy freetype.lib "..\..\..\..\lib\x86\Debug\" /Y /R
cd ..\freetype.dir\Debug
xcopy freetype.pdb "..\..\..\..\..\lib\x86\Debug\" /Y /R
cd ..\..\..\

rem IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%
rem mkdir %TEMP_DIR%
rem cd %TEMP_DIR%

rem echo Generating Freetype x64 Shared Lib ...

rem call cmake ..\..\freetype                              ^
rem 	-DGLM_DYNAMIC_LIBRARY_ENABLE:BOOL=ON               ^
rem 	-DGLM_TEST_ENABLE_CXX_11:BOOL=ON                   ^
rem 	-DWIN32:BOOL=ON                                    ^
rem 	-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=%OUTPUT_DIR%      ^
rem 	-G "Visual Studio 15 2017 Win64"

rem call cmake --build  . --config Release

rem cd glm\Release
rem rename glm_shared.dll glm.dll
rem xcopy glm.dll "..\..\..\..\..\lib\x64\Release\" /Y /R
rem cd ..\..\

rem call cmake --build  . --config Debug

rem cd glm\Debug
rem rename glm_shared.dll glm.dll
rem rename glm_shared.pdb glm.pdb
rem xcopy glm.dll "..\..\..\..\..\lib\x64\Debug\" /Y /R
rem xcopy glm.pdb "..\..\..\..\..\lib\x64\Debug\" /Y /R
rem cd ..\..\..\

rem IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%
rem mkdir %TEMP_DIR%
rem cd %TEMP_DIR%

rem echo Generating x64 Static Lib ...

rem call cmake ..\..\freetype                                   ^
rem 	-DGLM_STATIC_LIBRARY_ENABLE:BOOL=ON                ^
rem 	-DGLM_TEST_ENABLE_CXX_11:BOOL=ON                   ^
rem 	-DWIN32:BOOL=ON                                    ^
rem 	-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=%OUTPUT_DIR%      ^
rem 	-G "Visual Studio 15 2017 Win64"

rem call cmake --build  . --config Release

rem cd glm\Release
rem rename glm_static.lib glm.lib
rem xcopy glm.lib "..\..\..\..\..\lib\x64\Release\" /Y /R
rem cd ..\..\

rem call cmake --build  . --config Debug

rem cd glm\Debug
rem rename glm_static.lib glm.lib
rem rename glm_static.pdb glm.pdb
rem xcopy glm.lib "..\..\..\..\..\lib\x64\Debug\" /Y /R
rem rem xcopy glm.pdb "..\..\..\..\..\lib\x64\Debug\" /Y /R
rem cd ..\..\..\

rem IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%
