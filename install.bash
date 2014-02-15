wget "http://www.libsdl.org/release/SDL2-2.0.1.tar.gz"
tar -xvzf SDL2-2.0.1.tar.gz
pushd SDL2-2.0.1
./configure
make
sudo make install
sudo apt-get install checkinstall
sudo checkinstall 
