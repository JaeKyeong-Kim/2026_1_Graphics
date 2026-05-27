add_executable(week16_01 main.cpp)

target_link_libraries(week16_01
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)
