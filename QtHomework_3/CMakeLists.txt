cmake_minimum_required(VERSION 3.16)

project(QtHomework_3 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)

add_executable(QtHomework_3
  main.cpp
)
target_link_libraries(QtHomework_3 Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(QtHomework_3 Qt${QT_VERSION_MAJOR}::Sql)
target_link_libraries(QtHomework_3 Qt${QT_VERSION_MAJOR}::Network)

include(GNUInstallDirs)
install(TARGETS QtHomework_3
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
