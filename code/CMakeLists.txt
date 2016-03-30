#Déclaration du projet
project(demoFrug)
cmake_minimum_required(VERSION 3.0)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wsign-conversion -Wlogical-op -Wdouble-promotion -g -std=c++14 -Ofast ")
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} " )


#Déclaration de l'exécutable
file(GLOB_RECURSE mesFichiers  ./src/*.cpp)
add_executable(
        demoFrug
        ${mesFichiers}
)



target_link_libraries (demoFrug ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (demoFrug ${cvc4_library})
target_link_libraries (demoFrug gmp)
target_link_libraries (demoFrug lapack)