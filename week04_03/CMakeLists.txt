# week04_03: week04_02 기반 viewport 왜곡 실습
add_executable(week04_03 main.cpp)

target_link_libraries(week04_03
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)
