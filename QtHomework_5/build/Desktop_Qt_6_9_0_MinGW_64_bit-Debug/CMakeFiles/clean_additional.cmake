# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\qthomework_05_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\qthomework_05_autogen.dir\\ParseCache.txt"
  "qthomework_05_autogen"
  )
endif()
