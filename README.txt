
sudo apt-get install cmake
sudo apt-get install xorg-dev
sudo apt-get install libglfw3
sudo apt-get install libglfw3-dev
sudo apt-get install libglew-dev
sudo apt-get install libpng-dev
sudo apt-get install libfreetype6-dev


Obs.: fazer dos2unix no arquivo dllmain.cpp

Baixar o projeto

cd ${PROJECT_DIR}
mkdir build
cd build
cmake ..
cmake --build .
./PixelEffect