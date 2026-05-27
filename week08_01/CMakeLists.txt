# week08_01: week07_01 기반
add_executable(week08_01 main.cpp)

target_link_libraries(week08_01
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)
