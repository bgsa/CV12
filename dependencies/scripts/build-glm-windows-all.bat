@echo off 

SET TEMP_DIR=output
SET INCLUDE_DIR=%cd%/../../include
IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%
mkdir %TEMP_DIR%
cd %TEMP_DIR%

SET BUILD_TYPE=Release
echo Generating GLM x86 %BUILD_TYPE% Shared Lib ...

call cmake ..\..\glm                                     ^
	-DCMAKE_BUILD_TYPE=%BUILD_TYPE%                      ^
	-DGLM_DYNAMIC_LIBRARY_ENABLE:BOOL=ON                 ^
	-DGLM_TEST_ENABLE_CXX_11:BOOL=ON                     ^
	-DWIN32:BOOL=ON                                      ^
	-DCMAKE_INSTALL_INCLUDEDIR=%INCLUDE_DIR%             ^
 	-DCMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD:BOOL=OFF ^
	-G "Visual Studio 15 2017"

rem Generate with errors, althouth it copy headers files to include folder correctly
call cmake --build  . --config %BUILD_TYPE% --target install

call cmake --build  . --config %BUILD_TYPE% 

cd glm\%BUILD_TYPE%
rename glm_shared.dll glm.dll
xcopy glm.dll "..\..\..\..\..\lib\x86\%BUILD_TYPE%\" /Y /R
cd ..\..\

SET BUILD_TYPE=Debug
call cmake --build  . --config %BUILD_TYPE%

cd glm\%BUILD_TYPE%
rename glm_shared.dll glm.dll
rename glm_shared.pdb glm.pdb
xcopy glm.dll "..\..\..\..\..\lib\x86\%BUILD_TYPE%\" /Y /R
xcopy glm.pdb "..\..\..\..\..\lib\x86\%BUILD_TYPE%\" /Y /R
cd ..\..\..\

IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%
mkdir %TEMP_DIR%
cd %TEMP_DIR%

SET BUILD_TYPE=Release
echo Generating GLM x86 %BUILD_TYPE% Static Lib ...

call cmake ..\..\glm                                   ^
	-DCMAKE_BUILD_TYPE=%BUILD_TYPE%                    ^
	-DGLM_STATIC_LIBRARY_ENABLE:BOOL=ON                ^
	-DGLM_TEST_ENABLE_CXX_11:BOOL=ON                   ^
	-DWIN32:BOOL=ON                                    ^
	-G "Visual Studio 15 2017"

call cmake --build  . --config %BUILD_TYPE%

cd glm\%BUILD_TYPE%
rename glm_static.lib glm.lib
xcopy glm.lib "..\..\..\..\..\lib\x86\%BUILD_TYPE%\" /Y /R
cd ..\..\

SET BUILD_TYPE=Debug
call cmake --build  . --config %BUILD_TYPE%

cd glm\%BUILD_TYPE%
rename glm_static.lib glm.lib
rename glm_static.pdb glm.pdb
xcopy glm.lib "..\..\..\..\..\lib\x86\%BUILD_TYPE%\" /Y /R
rem xcopy glm.pdb "..\..\..\..\..\lib\x86\%BUILD_TYPE%\" /Y /R
cd ..\..\..\

IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%
mkdir %TEMP_DIR%
cd %TEMP_DIR%

SET BUILD_TYPE=Release
echo Generating GLM x64 %BUILD_TYPE% Shared Lib ...

call cmake ..\..\glm                                   ^
	-DCMAKE_BUILD_TYPE=%BUILD_TYPE%                    ^
	-DGLM_DYNAMIC_LIBRARY_ENABLE:BOOL=ON               ^
	-DGLM_TEST_ENABLE_CXX_11:BOOL=ON                   ^
	-DWIN32:BOOL=ON                                    ^
	-G "Visual Studio 15 2017 Win64"

call cmake --build  . --config %BUILD_TYPE%

cd glm\%BUILD_TYPE%
rename glm_shared.dll glm.dll
xcopy glm.dll "..\..\..\..\..\lib\x64\%BUILD_TYPE%\" /Y /R
cd ..\..\

SET BUILD_TYPE=Debug
call cmake --build  . --config %BUILD_TYPE%

cd glm\%BUILD_TYPE%
rename glm_shared.dll glm.dll
rename glm_shared.pdb glm.pdb
xcopy glm.dll "..\..\..\..\..\lib\x64\%BUILD_TYPE%\" /Y /R
xcopy glm.pdb "..\..\..\..\..\lib\x64\%BUILD_TYPE%\" /Y /R
cd ..\..\..\

IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%
mkdir %TEMP_DIR%
cd %TEMP_DIR%

SET BUILD_TYPE=Release
echo Generating GLM x64 %BUILD_TYPE% Static Lib ...

call cmake ..\..\glm                                   ^
	-DCMAKE_BUILD_TYPE=%BUILD_TYPE%                    ^
	-DGLM_STATIC_LIBRARY_ENABLE:BOOL=ON                ^
	-DGLM_TEST_ENABLE_CXX_11:BOOL=ON                   ^
	-DWIN32:BOOL=ON                                    ^
	-G "Visual Studio 15 2017 Win64"

call cmake --build  . --config %BUILD_TYPE%

cd glm\%BUILD_TYPE%
rename glm_static.lib glm.lib
xcopy glm.lib "..\..\..\..\..\lib\x64\%BUILD_TYPE%\" /Y /R
cd ..\..\

SET BUILD_TYPE=Debug
call cmake --build  . --config %BUILD_TYPE%

cd glm\%BUILD_TYPE%
rename glm_static.lib glm.lib
rename glm_static.pdb glm.pdb
xcopy glm.lib "..\..\..\..\..\lib\x64\%BUILD_TYPE%\" /Y /R
rem xcopy glm.pdb "..\..\..\..\..\lib\x64\%BUILD_TYPE%\" /Y /R
cd ..\..\..\

IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%


:END