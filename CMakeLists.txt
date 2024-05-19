cmake_minimum_required (VERSION 3.8)

project(LuaTest)

set(TARGET_NAME NPCReader)
add_subdirectory(external/lua-5.4.6)

# Add source to this project's executable.
add_executable(${TARGET_NAME} 
"main.cpp" 
"NPCManager.h" 
 
"LuaWrapper.h" 
"LuaWrapper.cpp"
)

target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)
target_compile_options(${TARGET_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

target_link_libraries(${TARGET_NAME} lualib)


 add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
   COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_SOURCE_DIR}/luaScripts" "${CMAKE_BINARY_DIR}/luaScripts"
 )