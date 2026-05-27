#if defined(__APPLE__)                              // macOS 환경이면 Apple GLUT 헤더를 사용한다.
#include <GLUT/glut.h>                              // macOS 기본 GLUT 프레임워크 헤더를 포함한다.
#else                                               // macOS가 아닌 환경 분기다.
#include <GL/glut.h>                                // 일반 GLUT 헤더를 포함한다.
#endif

#include <iostream>                                 // 콘솔 로그 출력에 사용한다.
#include <stdio.h>                                  // 기존 코드 흐름을 유지하기 위한 C 표준 헤더다.


void RenderScene(void)
{
    std::cout << "RenderScene" << std::endl;      
    glClear(GL_COLOR_BUFFER_BIT);                  

    glViewport(250, 250, 250, 250); // 우상단(1사분면) 영역 중심에 오도록 viewport 설정. 뷰포트의 원점은 창의 왼쪽 아래(0,0)이다. 따라서 (250,250)부터 폭 250, 높이 250 영역이 우상단에 배치된다.

    glColor3f(1.0f, 0.0f, 0.0f);                   
    glRectf(-0.25f, 0.25f, 0.25f, -0.25f);

    glutSwapBuffers();                           
}

// 렌더링 컨텍스트 초기 설정 함수다.
void SetupRC(void)
{
    std::cout << "SetupRC" << std::endl;           
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);          

    glMatrixMode(GL_PROJECTION);                   
    glLoadIdentity();                               
    glOrtho(-1, 1, -1, 1, -1, 1);                  

    glMatrixMode(GL_MODELVIEW);                    
    glLoadIdentity();                         
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);                          // GLUT 시스템을 초기화한다.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);    // 더블 버퍼링 + RGB 모드로 창을 생성한다.
    glutInitWindowSize(500, 500);                   // 창 크기를 500x500으로 설정한다.
    glutInitWindowPosition(500, 500);               // 창의 초기 위치를 설정한다.
    glutCreateWindow("week05_01");                  // 창 제목을 week05_01으로 지정한다.

    SetupRC();                                      // 배경색, 투영 좌표계 등 초기 상태를 설정한다.
    glutDisplayFunc(RenderScene);                   // 디스플레이 콜백으로 RenderScene을 등록한다.

    glutMainLoop();                                 // 이벤트 루프를 시작한다.
}

/*
===============================================================================
  [week05_01 요약]
===============================================================================
1. glRectf(-0.25f, 0.25f, 0.25f, -0.25f) 자체는 정사각형이다.
2. glOrtho(-1, 1, -1, 1, -1, 1) 에서 이 도형은 viewport 기준 가로 1/4, 세로 1/4를 차지한다.
3. viewport를 (250, 250, 250, 250)으로 잡아 우상단(1사분면)에 배치했다.
4. glRectf는 viewport 내부 기준으로 중앙에 그려지므로 1사분면의 가운데에 보인다.
5. viewport 좌표의 원점은 창의 왼쪽 아래 (0,0)이다.
===============================================================================
*/

/* [week05_01 Notes 보강]
 * - viewport 시작점(250,250)은 창 좌하단 원점 기준 오프셋 좌표다.
 */
