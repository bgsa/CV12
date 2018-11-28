rm -rf build
mkdir build
cd build
cmake ..
cmake --build .
cd ..
cp -R ./resources ./build/
cd build
./PixelEffectLinuxApp 1
