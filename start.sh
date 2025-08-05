sudo apt install     libxrandr-dev     libxcursor-dev     libxi-dev     libudev-dev     libfreetype-dev     libflac-dev     libvorbis-dev     libgl1-mesa-dev     libegl1-mesa-dev     libfreetype-dev
mkdir build
cd build
cmake ..
cmake --build .
cd ..
cd ..
./build/bin/Heroes3App