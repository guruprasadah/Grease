project( Glad )

add_library( GLAD STATIC Source/glad.c )
target_include_directories( GLAD PUBLIC Include )