conan install . --output-folder=build --build=missing --profile:host=mygcc --profile:build=mygcc 

cd build
 
cmake .. -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE="conan_toolchain.cmake" -DCMAKE_BUILD_TYPE="Release"

cmake --build . --config Release

cd ../bin/Release
 