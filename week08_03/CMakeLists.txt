# week08_03: week08_01 기반, 원본 정답 스타일 + LINE_STRIP 연결
add_executable(week08_03 main.cpp)

target_link_libraries(week08_03
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)
