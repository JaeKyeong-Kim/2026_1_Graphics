add_executable(week15_02 main.cpp)

target_link_libraries(week15_02
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)
