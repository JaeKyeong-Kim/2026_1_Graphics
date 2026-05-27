cmake_minimum_required(VERSION 3.16)
project(Graphics)

set(CMAKE_CXX_STANDARD 17)

# Homebrew prefix (Apple Silicon / Intel 모두 대응)
set(HOMEBREW_PREFIX /opt/homebrew)

# 공통 include 경로 (모든 주차에서 사용)
include_directories(
    ${HOMEBREW_PREFIX}/opt/glfw/include
    ${HOMEBREW_PREFIX}/opt/glew/include
    ${HOMEBREW_PREFIX}/opt/glm/include
)

# 공통 library 경로
link_directories(
    ${HOMEBREW_PREFIX}/opt/glfw/lib
    ${HOMEBREW_PREFIX}/opt/glew/lib
)

# OpenGL 패키지 탐색
find_package(OpenGL REQUIRED)

# ── 주차별 서브디렉토리 ──────────────────────────────────────────
add_subdirectory(week01)  # 다음 주차 추가 시 주석 해제
add_subdirectory(week02)
add_subdirectory(week03)
add_subdirectory(week03_test_01)
add_subdirectory(week04)
add_subdirectory(week04_02)
add_subdirectory(week04_03)
add_subdirectory(week05_01)
add_subdirectory(week05_02)
add_subdirectory(week06_01)
add_subdirectory(week06_02)
add_subdirectory(week06_03)
add_subdirectory(week06_04)
add_subdirectory(week07_01)
add_subdirectory(week08_01)
add_subdirectory(week08_02)
add_subdirectory(week08_03)
add_subdirectory(week08_04)
add_subdirectory(week08_05)
add_subdirectory(week09_01)
add_subdirectory(week09_02)
add_subdirectory(week10_01)
add_subdirectory(week11_01)
add_subdirectory(week11_test_01)
add_subdirectory(week11_test_02)
add_subdirectory(week12_01)
add_subdirectory(week12_test_01)
add_subdirectory(week13_01)
add_subdirectory(week13_test_01)
add_subdirectory(week13_02)
add_subdirectory(week13_03)
add_subdirectory(week14_01)
add_subdirectory(week14_test_01)
add_subdirectory(week14_test_02)
add_subdirectory(week15_01)
add_subdirectory(week15_02)
add_subdirectory(week16_01)
add_subdirectory(week16_test_01)
add_subdirectory(week17_01)
add_subdirectory(week17_02)
add_subdirectory(week17_03)
add_subdirectory(week17_test_01)
add_subdirectory(week18_test_01)
add_subdirectory(week18_test_02)
