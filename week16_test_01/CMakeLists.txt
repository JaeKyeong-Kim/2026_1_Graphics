add_executable(week16_test_01 main.cpp)

target_link_libraries(week16_test_01
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)
