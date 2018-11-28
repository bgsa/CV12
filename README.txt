
# Requisitos / Dependencias
sudo apt-get install git
sudo apt-get install cmake
sudo apt-get install xorg-dev
sudo apt-get install libglfw3
sudo apt-get install libglfw3-dev
sudo apt-get install libglew-dev
sudo apt-get install libpng-dev

# Baixar o projeto:
git clone https://github.com/bgsa/CV12.git

# Compilar e executar o projeto
cd CV12
./build.sh

# Neste momento o projeto irá compilar e executar o trabalho 1

# Para executar o trabalho 1 ou 2, deve utilizar o ultimo parametro
./build/PixelEffectLinux 1
./build/PixelEffectLinux 2

# Obs.: No trabalho 1, configurar os 4 pontos começando do canto esquerdo inferior em sentido horário
