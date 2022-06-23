# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/SudokuMFF_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/SudokuMFF_autogen.dir/ParseCache.txt"
  "SudokuMFF_autogen"
  )
endif()
