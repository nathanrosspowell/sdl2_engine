wget "https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.0.tar.gz"
tar -xvzf SDL2_image-2.0.0.tar.gz
pushd SDL2_image-2.0.0
./configure
make
sudo make install

