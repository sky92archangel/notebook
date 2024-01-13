

clang:
add   plugin clangd
set   text to  cmake-tools-kits.json
```
 {
    "name":"Clang 17.0.4 x86_64-pc-windows-msvc",
    "compilers":{
      "C":"C:\\_PRO\\Develop\\LLVM\\bin\\clang.exe",
      "CXX":"C:\\_PRO\\Develop\\LLVM\\bin\\clang++.exe"
    }
  },
```
select   Clang 17.0.4 x86_64-pc-windows-msvc
result files will appear in folder  ./build/

or

cmake -S . -B build-vs -G "Visual Studio 17 2022"
cmake --build ./build-vs/
sln file will appear at folder ./build-vs/

or

cmake -S . -B build-gc -G "MinGW Makefiles" 
cmake --build ./build-gc/
result file will appear at folder ./build-gc/
 
or

cmake -S . -B build-vs -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release
cmake --build ./build-vs/ --parallel 4
cmake --build ./build-vs/ --target install
sln file will appear at folder ./build-vs/
