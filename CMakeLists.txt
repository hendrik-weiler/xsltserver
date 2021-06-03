cmake_minimum_required(VERSION 3.19)
project(xsltserver)

set(CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/bin/www)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/www DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)

file(GLOB pages ${CMAKE_CURRENT_SOURCE_DIR}/src/page/**/*.cpp)
file(GLOB pages_first ${CMAKE_CURRENT_SOURCE_DIR}/src/page/*.cpp)

add_executable(xsltserver
        src/app/Request.cpp
        src/app/Routing.cpp
        src/app/Cookie.cpp
        src/app/XSLTransformer.cpp
        src/app/Tools.cpp
        src/app/Data.cpp
        ${pages}
        ${pages_first}
        src/routes.cpp
        main.cpp
        )

target_link_libraries(xsltserver ${CONAN_LIBS})