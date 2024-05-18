cmake_minimum_required (VERSION 3.8)

project(LuaTest)

add_subdirectory(external/lua-5.4.6)

# Add source to this project's executable.
add_executable(NPCReader "main.cpp")
target_link_libraries(NPCReader lualib)

target_compile_features(NPCReader PRIVATE cxx_std_20)
target_compile_options(NPCReader PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)