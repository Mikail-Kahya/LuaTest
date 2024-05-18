cmake_minimum_required (VERSION 3.8)

project(LuaTest)

# with help of Matias Devred
set(lua_SOURCE_DIR external/lua-5.4.6)
file(GLOB LUA_SRC_FILES ${lua_SOURCE_DIR}/src/*.c) # find source files
add_library(lualib STATIC ${LUA_SRC_FILES}) # create library
target_include_directories(lualib PUBLIC ${lua_SOURCE_DIR}/src) # add include dir

# Add source to this project's executable.
add_executable(NPCReader "main.cpp")
target_link_libraries(NPCReader lualib)

target_compile_features(NPCReader PRIVATE cxx_std_20)
target_compile_options(NPCReader PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)