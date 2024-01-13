add_library(Eigen INTERFACE)
target_include_directories(Eigen INTERFACE ./)
target_compile_features(Eigen INTERFACE cxx_std_17)