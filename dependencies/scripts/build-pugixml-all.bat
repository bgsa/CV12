@echo off 

SET API_LEVEL="24"
SET STL="c++_shared"

call build-pugixml-windows.bat

call build-pugixml-android.bat %API_LEVEL% "armeabi"     %STL% "./../../../lib/android/armeabi"    

call build-pugixml-android.bat %API_LEVEL% "armeabi-v7a" %STL% "./../../../lib/android/armeabi-v7a"

call build-pugixml-android.bat %API_LEVEL% "arm64-v8a"   %STL% "./../../../lib/android/arm64-v8a"  

call build-pugixml-android.bat %API_LEVEL% "x86"         %STL% "./../../../lib/android/x86"        

call build-pugixml-android.bat %API_LEVEL% "x86_64"      %STL% "./../../../lib/android/x86_64"     