add_executable(week13_03 main.cpp)

target_link_libraries(week13_03
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)
