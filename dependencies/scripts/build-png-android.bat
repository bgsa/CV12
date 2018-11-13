@echo off 

IF "%NDK_HOME%"=="" goto NDK_HOME_NOT_DEFINED

SET BUILD_TYPE="Release"
SET API_LEVEL=%1
SET ABI=%2
SET CPP_STL=%3
SET OUTPUT_DIR=%4
SET CPP_VERSION=11
SET VERBOSE_MODE=OFF

SET TEMP_DIR="output"
IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%
mkdir %TEMP_DIR%
cd %TEMP_DIR%

call cmake ..\..\libpng16\                                                  ^
	-DCMAKE_SYSTEM_NAME=Android                                             ^
	-DCMAKE_SYSTEM_VERSION=%API_LEVEL%                                      ^
	-DCMAKE_BUILD_TYPE=%BUILD_TYPE%                                         ^
	-DCMAKE_ANDROID_ARCH_ABI=%ABI%                                          ^
	-DCMAKE_ANDROID_STL_TYPE=%CPP_STL%	                                    ^
	-DCMAKE_TOOLCHAIN_FILE="%NDK_HOME%/build/cmake/android.toolchain.cmake" ^
	-DANDROID_NDK="%NDK_HOME%"                                              ^
	-DANDROID_NATIVE_API_LEVEL=%API_LEVEL%                                  ^
	-DANDROID_STL=%CPP_STL%                                                 ^
	-DANDROID_TOOLCHAIN=clang                                               ^
	-DANDROID_ABI=%ABI%                                                     ^
	-DBUILD_SHARED_LIBS:BOOL=ON                                             ^
	-DCMAKE_CXX_STANDARD=%CPP_VERSION%                                      ^
	-DCMAKE_CXX_STANDARD_REQUIRED:BOOL=ON                                   ^
	-DCMAKE_VERBOSE_MAKEFILE:BOOL=%VERBOSE_MODE%                            ^
	-G "MinGW Makefiles"


call cmake --build .

xcopy "libpng.so" %OUTPUT_DIR%   /Y /Q /I

cd ..

goto END


:NDK_HOME_NOT_DEFINED
echo NDK_HOME undefined!!
goto END

:END

IF EXIST %TEMP_DIR% rmdir /S /Q %TEMP_DIR%