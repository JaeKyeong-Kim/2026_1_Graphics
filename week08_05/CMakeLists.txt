# week08_05: 가로 선 10개, 상->하로 갈수록 얇아짐
add_executable(week08_05 main.cpp)

target_link_libraries(week08_05
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)
