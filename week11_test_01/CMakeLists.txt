# week11_test_01: test variant
add_executable(week11_test_01 main.cpp)

target_link_libraries(week11_test_01
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)
