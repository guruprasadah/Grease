project( "Grease Engine Core" )
file( GLOB_RECURSE EngineSrcs Source/*.cpp )
add_library( GreaseCore STATIC ${EngineSrcs} )
target_include_directories( GreaseCore PUBLIC Include )