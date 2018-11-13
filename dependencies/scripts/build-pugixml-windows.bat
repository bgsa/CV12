@echo off 

SET OUTPUT_DIR=..\..\..\..\lib
SET TEMP_DIR="output"
IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%
mkdir %TEMP_DIR%
cd %TEMP_DIR%

SET BUILD_TYPE=Debug
echo Generating pugixml x86 %BUILD_TYPE% Shared Lib ...

call cmake ..\..\pugixml                              ^
	-DBUILD_SHARED_LIBS:BOOL=ON                       ^
	-DCMAKE_BUILD_TYPE=%BUILD_TYPE%                   ^
	-DPLATAFORM:STRING="WINDOWS"                      ^
	-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=%OUTPUT_DIR%     ^
	-G "Visual Studio 15 2017"

call cmake --build  . --config %BUILD_TYPE%

cd %BUILD_TYPE%
xcopy pugixml.dll %OUTPUT_DIR%\x86\%BUILD_TYPE% /Y /R
xcopy pugixml.pdb %OUTPUT_DIR%\x86\%BUILD_TYPE% /Y /R
cd ..

SET BUILD_TYPE=Release
echo Generating pugixml x86 %BUILD_TYPE% Shared Lib ...

call cmake --build  . --config %BUILD_TYPE%

cd %BUILD_TYPE%
xcopy pugixml.dll %OUTPUT_DIR%\x86\%BUILD_TYPE% /Y /R
cd ..

cd ..
rmdir /S /Q %TEMP_DIR%
mkdir %TEMP_DIR%
cd %TEMP_DIR%

SET BUILD_TYPE=Debug
echo Generating pugixml x86 %BUILD_TYPE% Static Lib ...

call cmake ..\..\pugixml                              ^
	-DBUILD_SHARED_LIBS:BOOL=OFF                       ^
	-DCMAKE_BUILD_TYPE=%BUILD_TYPE%                   ^
	-DPLATAFORM:STRING="WINDOWS"                      ^
	-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=%OUTPUT_DIR%     ^
	-G "Visual Studio 15 2017"

call cmake --build  . --config %BUILD_TYPE%

cd "%BUILD_TYPE%"
xcopy pugixml.lib %OUTPUT_DIR%\x86\%BUILD_TYPE% /Y /R
cd ..

SET BUILD_TYPE=Release
echo Generating pugixml x86 %BUILD_TYPE% Static Lib ...

call cmake --build  . --config %BUILD_TYPE%

cd %BUILD_TYPE%
xcopy pugixml.lib %OUTPUT_DIR%\x86\%BUILD_TYPE% /Y /R
cd ..

cd ..
IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%