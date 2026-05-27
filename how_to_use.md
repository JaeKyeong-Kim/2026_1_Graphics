# 2025_1_Graphics — 사용 방법

## 환경 정보

| 항목 | 내용 |
|---|---|
| OpenGL 버전 | 4.1 (macOS 최대) |
| 빌드 시스템 | CMake |
| 컴파일러 | AppleClang |
| 주요 라이브러리 | GLFW, GLEW, GLM |

> macOS는 OpenGL 4.1이 최대이지만, 학부 수업 및 LearnOpenGL 튜토리얼은 3.3 기준이므로 문제없음.

---

## 프로젝트 구조

```
2025_1_Graphics/
├── CMakeLists.txt       # 빌드 설정
├── how_to_use.md        # 이 파일
├── src/
│   └── main.cpp         # 실제 코드 작성 위치
└── build/
    └── Graphics         # 컴파일된 실행 파일
```

---

## 개발 사이클

### 1. 코드 작성
`src/main.cpp` 을 VS Code에서 열어 수정한다.  
과제마다 `src/` 아래에 파일을 추가하거나 서브폴더로 나눠도 됨 (CMake가 자동 포함).

### 2. 빌드
```bash
cd ~/Desktop/2025_1_Graphics/build
cmake --build .
```
- 변경된 파일만 재컴파일하므로 매번 빨리 끝남
- 최초 1회만 `cmake ..` 필요 (이미 완료됨)

### 3. 실행
```bash
./Graphics
```

### 반복
```
코드 수정 (VS Code) → cmake --build . → ./Graphics → 결과 확인 → 반복
```

---

## 팁

- VS Code 내장 터미널(`Ctrl + \``)을 사용하면 편집기와 터미널을 전환 없이 한 화면에서 작업 가능
- 빌드 에러는 터미널 출력에서 파일명과 줄 번호로 바로 확인 가능
- `src/` 아래 `.cpp` 파일을 추가하면 `CMakeLists.txt` 수정 없이 자동으로 빌드에 포함됨
