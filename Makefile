buildGCC:
	cmake -S . -B build -DCMAKE_CXX_COMPILER=g++
	cmake --build build -- -j$(shell nproc)

buildClang:
	cmake -S . -B build -DCMAKE_CXX_COMPILER=clang++
	cmake --build build -- -j$(shell nproc)

clean:
	rm -rf ./build

buildForceGCC: clean buildGCC

buildForceClang: clean buildClang

installDependencies:
	sudo apt install     libxrandr-dev     libxcursor-dev     libxi-dev     libudev-dev     libfreetype-dev     libflac-dev     libvorbis-dev     libgl1-mesa-dev     libegl1-mesa-dev     libfreetype-dev

run:
	./build/bin/Heroes3App

runValgrind:
	valgrind --log-file="valgrind-$(shell date +%Y-%m-%d_%H-%M-%S).log" ./build/bin/Heroes3App

count:
	@cloc --exclude-dir=build,docs .
document:
	@doxygen Doxyfile