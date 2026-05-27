# week03: week02 기반 기본 셋업
add_executable(week03 main.cpp)

target_link_libraries(week03
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)
