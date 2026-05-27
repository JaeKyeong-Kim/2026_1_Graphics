# week12_01: main variant with comments
add_executable(week12_01 main.cpp)

target_link_libraries(week12_01
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)
