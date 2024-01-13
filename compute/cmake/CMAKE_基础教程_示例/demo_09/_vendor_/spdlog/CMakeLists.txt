add_library(Spdlog INTERFACE)
target_include_directories(Spdlog INTERFACE ./)
target_compile_features(Spdlog INTERFACE cxx_std_17)