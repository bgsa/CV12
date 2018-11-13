@echo off 

SET OUTPUT_DIR=..\..\..\..\..\lib
SET TEMP_DIR="output"
IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%
mkdir %TEMP_DIR%
cd %TEMP_DIR%

SET BUILD_TYPE=Debug
echo Generating Assimp x86 %BUILD_TYPE% Static and Shared Lib ...

call cmake ..\..\assimp                               ^
	-DBUILD_SHARED_LIBS:BOOL=ON                       ^
	-DCMAKE_BUILD_TYPE=%BUILD_TYPE%                   ^
	-DWIN32:BOOL=ON                                   ^
	-DENABLE_BOOST_WORKAROUND:BOOL=ON                 ^
	-G "Visual Studio 15 2017"

call cmake --build  . --config %BUILD_TYPE%

cd code\%BUILD_TYPE%

xcopy assimp-vc140-mtd.dll "%OUTPUT_DIR%\x86\%BUILD_TYPE%\" /Y /R
xcopy assimp-vc140-mtd.lib "%OUTPUT_DIR%\x86\%BUILD_TYPE%\" /Y /R
xcopy assimp-vc140-mtd.pdb "%OUTPUT_DIR%\x86\%BUILD_TYPE%\" /Y /R

cd ..\..\

SET BUILD_TYPE=Release
echo Generating Assimp x86 %BUILD_TYPE% Static and Shared Lib ...
call cmake --build  . --config %BUILD_TYPE%

cd code\%BUILD_TYPE%

xcopy assimp-vc140-mt.dll "%OUTPUT_DIR%\x86\%BUILD_TYPE%\" /Y /R
xcopy assimp-vc140-mt.lib "%OUTPUT_DIR%\x86\%BUILD_TYPE%\" /Y /R

cd ..\..\..\
IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%