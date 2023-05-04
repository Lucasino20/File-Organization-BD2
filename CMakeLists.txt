find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(<tu_ejecutable> ${Boost_LIBRARIES})