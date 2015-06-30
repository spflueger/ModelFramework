cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall")

set(INCLUDE_DIRECTORIES
  ./
  $ENV{ROOT_INCLUDE_DIR}
  $ENV{BOOST_ROOT}/include
)
include_directories(${INCLUDE_DIRECTORIES})


set(LINK_DIRECTORIES
  $ENV{ROOT_LIBRARY_DIR}
  $ENV{BOOST_ROOT}/lib
)
link_directories(${LINK_DIRECTORIES})
set(LINK_LIBS Core Hist Gpad Graf gsl gslcblas boost_thread boost_filesystem boost_system)


file(GLOB_RECURSE SRCS ./*.cxx)

add_library(Model SHARED ${SRCS})

target_link_libraries(Model ${LINK_LIBS})