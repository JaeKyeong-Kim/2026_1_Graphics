# week05_02: week05_01 기반, reshape 콜백으로 창 크기 변화 대응
add_executable(week05_02 main.cpp)

target_link_libraries(week05_02
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)
