wget "https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.0.tar.gz"
tar -xvzf SDL2_mixer-2.0.0.tar.gz
pushd SDL2_mixer-2.0.0
./configure
make
sudo make install

