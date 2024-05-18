cmake_minimum_required (VERSION 3.8)

# with help of Matias Devred
file(GLOB LUA_SRC_FILES src/*.c) # find source files
add_library(lualib STATIC ${LUA_SRC_FILES}) # create library
target_include_directories(lualib PUBLIC src) # add include dir