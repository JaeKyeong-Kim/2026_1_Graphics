# week03_test_01: week03 기반 기본 셋업
add_executable(week03_test_01 main.cpp)

target_link_libraries(week03_test_01
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)
