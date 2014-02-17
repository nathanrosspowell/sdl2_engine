wget "https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.12.tar.gz"
tar -xvzf SDL2_ttf-2.0.12.tar.gz
pushd SDL2_ttf-2.0.12
./configure
make
sudo make install

