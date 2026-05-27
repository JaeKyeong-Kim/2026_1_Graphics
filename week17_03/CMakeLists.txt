add_executable(week17_03 main.cpp)

target_link_libraries(week17_03
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)
