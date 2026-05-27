# week13_01: main variant with comments
add_executable(week13_01 main.cpp)

target_link_libraries(week13_01
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)