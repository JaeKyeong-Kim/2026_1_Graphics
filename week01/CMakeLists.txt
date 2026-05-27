# week01: 파란색 배경 테스트
add_executable(week01 main.cpp)

target_link_libraries(week01
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)
