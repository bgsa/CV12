@echo off 

SET OUTPUT_DIR=..\..\..\..\lib

SET TEMP_DIR="output"
IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%
mkdir %TEMP_DIR%
cd %TEMP_DIR%

SET BUILD_TYPE=Debug
echo Generating MathPP x86 %BUILD_TYPE% Shared Lib ...

call cmake ..\..\MathPP                               ^
	-DBUILD_SHARED_LIBS:BOOL=ON                       ^
	-DCMAKE_CXX_STANDARD=11                           ^
	-DCMAKE_CXX_STANDARD_REQUIRED=ON                  ^
	-DPLATAFORM:STRING="WINDOWS"                      ^
	-G "Visual Studio 15 2017"

call cmake --build  . --config %BUILD_TYPE%

cd %BUILD_TYPE%
xcopy MathPP.dll %OUTPUT_DIR%\x86\%BUILD_TYPE% /Y /R
xcopy MathPP.pdb %OUTPUT_DIR%\x86\%BUILD_TYPE% /Y /R
cd ..

SET BUILD_TYPE=Release
echo Generating MathPP x86 %BUILD_TYPE% Shared Lib ...

call cmake --build  . --config %BUILD_TYPE%

cd %BUILD_TYPE%
xcopy MathPP.dll %OUTPUT_DIR%\x86\%BUILD_TYPE% /Y /R
cd ..

IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%
mkdir %TEMP_DIR%
cd %TEMP_DIR%

SET BUILD_TYPE=Debug
echo Generating MathPP x86 %BUILD_TYPE% Static Lib ...

call cmake ..\..\MathPP                               ^
	-DBUILD_SHARED_LIBS:BOOL=OFF                      ^
	-DCMAKE_CXX_STANDARD=11                           ^
	-DCMAKE_CXX_STANDARD_REQUIRED=ON                  ^
	-DPLATAFORM:STRING="WINDOWS"                      ^
	-G "Visual Studio 15 2017"

call cmake --build  . --config %BUILD_TYPE%

cd %BUILD_TYPE%
xcopy MathPP.lib %OUTPUT_DIR%\x86\%BUILD_TYPE% /Y /R
xcopy MathPP.pdb %OUTPUT_DIR%\x86\%BUILD_TYPE% /Y /R
cd ..

SET BUILD_TYPE=Release
echo Generating MathPP x86 %BUILD_TYPE% Static Lib ...

call cmake --build  . --config %BUILD_TYPE%

cd %BUILD_TYPE%
xcopy MathPP.lib %OUTPUT_DIR%\x86\%BUILD_TYPE% /Y /R
cd ..
	
cd ..
IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%

:END






