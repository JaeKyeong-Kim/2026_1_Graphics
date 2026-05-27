#if defined(__APPLE__)                              // macOS 환경이면 Apple GLUT 헤더를 사용한다.
#include <GLUT/glut.h>                              // macOS 기본 GLUT 프레임워크 헤더를 포함한다.
#else                                               // macOS가 아닌 환경 분기다.
#include <GL/glut.h>                                // 일반 GLUT 헤더를 포함한다.
#endif

#include <iostream>                                 // 콘솔 로그 출력에 사용한다.
#include <stdio.h>                                  // 기존 코드 흐름을 유지하기 위한 C 표준 헤더다.

// 장면 렌더링 함수: 설정된 투영 좌표계 기준으로 실제 도형을 그린다.
void RenderScene(void)
{
    std::cout << "RenderScene" << std::endl;       // 디스플레이 콜백 호출 여부를 콘솔에 남긴다.
    glClear(GL_COLOR_BUFFER_BIT);                   // 현재 clear color(파란색)로 화면 버퍼를 지운다.

    // 뷰포트는 "그린 결과를 창의 어느 픽셀 영역에 보여줄지"를 정한다.
    // 여기서는 창 전체(500x500)를 그대로 렌더링 영역으로 사용한다.
    glViewport(0, 0, 500, 500);

    glColor3f(1.0f, 0.0f, 0.0f);                    // 이후 도형의 현재 색상을 빨간색으로 설정한다.

    // 숫자 좌표로 직접 배치한 버전이다.
    // 비율로 보면 left = 0.50f * w
    // 비율로 보면 bottom = 0.50f * w
    // 비율로 보면 right = 0.75f * w
    // 비율로 보면 top = 0.75f * w
    glRectf(250.0f, 250.0f, 375.0f, 375.0f); // f 안붙여도 되지만, float로 명시적으로 표현하는 것이 좋다. (왼쪽 아래 (250,250), 오른쪽 위 (375,375))

    glutSwapBuffers();                              // 더블 버퍼링 결과를 실제 화면에 표시한다.
}

// 렌더링 컨텍스트 초기 설정 함수다.
void SetupRC(void)
{
    std::cout << "SetupRC" << std::endl;           // 초기화 함수 호출 여부를 콘솔에 남긴다.
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);          // 배경색을 파란색으로 지정한다.

    // 투영 행렬 설정 시작: "어떤 좌표계를 사용할지" 정의하는 부분이다.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();                               // 기존 투영 행렬 상태를 초기화한다.

    // 직교 투영 좌표계 설정
    // left=0, right=500, bottom=0, top=500 이므로
    // 창의 실제 픽셀 크기와 거의 같은 감각으로 2D 좌표를 직접 사용할 수 있다.
    // 원점은 화면 왼쪽 아래이고, x/y 모두 0~500 범위를 사용한다.
    glOrtho(0, 500, 0, 500, -1, 1);

    // 이후 도형 그리기는 모델뷰 행렬 기준으로 진행하도록 모드를 되돌린다.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();                               // 모델뷰 행렬도 깨끗한 상태로 초기화한다.
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);                          // GLUT 시스템을 초기화한다.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);    // 더블 버퍼링 + RGB 모드로 창을 생성한다.
    glutInitWindowSize(500, 500);                   // 창 크기를 500x500으로 설정한다.
    glutInitWindowPosition(500, 500);               // 창의 초기 위치를 설정한다.
    glutCreateWindow("week04_02");                  // 창 제목을 week04_02로 지정한다.

    SetupRC();                                      // 배경색, 투영 좌표계 등 초기 상태를 설정한다.
    glutDisplayFunc(RenderScene);                   // 디스플레이 콜백으로 RenderScene을 등록한다.

    glutMainLoop();                                 // 이벤트 루프를 시작한다.
}

/*
===============================================================================
  [week04_02 요약]
===============================================================================
1. week04와 동일하게 파란 배경 + 빨간 사각형을 그린다.
2. 차이점은 설명을 보강해서 "왜 좌하단에 사각형이 보이는지"를 코드 안에서 바로 읽을 수 있게 한 것이다.
3. 전체 화면을 4x4 격자로 보면 한 칸 크기는 500/4 = 125다.
4. 2행 3열 칸에 정사각형을 두기 위해 glRectf(250, 250, 375, 375)로 설정했다.
5. 배경은 파란색, 사각형은 빨간색으로 유지된다.
===============================================================================
*/

/* [week04_02 Notes 보강]
 * - 좌표를 절대값이 아닌 비율(예: 0.5w~0.75w)로 해석하면 응용 문제가 쉬워진다.
 */
