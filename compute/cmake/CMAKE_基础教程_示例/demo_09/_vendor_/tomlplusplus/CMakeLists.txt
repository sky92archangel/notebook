add_library(Tomlpp INTERFACE)
target_include_directories(Tomlpp INTERFACE ./)
target_compile_features(Tomlpp INTERFACE cxx_std_17)