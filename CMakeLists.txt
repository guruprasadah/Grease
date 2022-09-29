cmake_minimum_required( VERSION 3.10 )
set( CMAKE_CXX_STANDARD 20 )

project( "Grease Engine Dev" )
add_subdirectory( Engine )

add_grease_project( "Sandbox" "Sandbox" )
