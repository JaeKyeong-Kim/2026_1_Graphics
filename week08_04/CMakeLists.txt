# week08_04: 세로 선 10개, 좌->우로 갈수록 두꺼워짐
add_executable(week08_04 main.cpp)

target_link_libraries(week08_04
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)
