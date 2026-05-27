# week08_02: week08_03 개선안에서 점 렌더링만 사용 (선 연결 제외)
add_executable(week08_02 main.cpp)

target_link_libraries(week08_02
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)
