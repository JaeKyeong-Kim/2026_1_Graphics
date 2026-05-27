#if defined(__APPLE__)                              // macOS 환경이면 Apple GLUT 헤더를 사용한다.
#include <GLUT/glut.h>                              // macOS 기본 GLUT 프레임워크 헤더를 포함한다.
#else                                               // macOS가 아닌 환경(리눅스/윈도우 등) 분기다.
#include <GL/glut.h>                                // 일반 GLUT 헤더를 포함한다.
#endif                                              // 플랫폼 분기 전처리를 종료한다.

#include <iostream>                                 // 콘솔 로그 출력(std::cout)에 사용한다.
#include <stdio.h>                                  // C 표준 입출력 헤더(기존 코드 유지)다.

// 장면 렌더링 함수: 화면에 실제로 도형을 그리는 콜백 함수다.
void RenderScene(void)                              // GLUT가 화면 갱신 시 호출하는 디스플레이 콜백이다.
{                                                   // RenderScene 함수 시작.
    std::cout << "RenderScene" << std::endl;       // 렌더 함수 호출 여부를 콘솔에서 확인한다.
    glClear(GL_COLOR_BUFFER_BIT);                   // 현재 배경색으로 화면(컬러 버퍼)을 지운다.

    glViewport(0, 0, 500, 500);                     // 렌더링 결과를 그릴 화면 영역을 (x=0,y=0,w=500,h=500)로 설정한다.
                                                     // 기존 주석(정리): "포트 설정, 역할 확인"

    glColor3f(1.0f, 0.0f, 0.0f);                    // 이후 그릴 도형의 현재 색상을 빨간색(RGB=1,0,0)으로 설정한다.
                                                     // 기존 주석: 아래의 도형을 빨간색으로 그리기
    // glRectf(-0.5f, -0.5f, 0.5f, 0.5f);           // 큰 사각형 예시(기존 주석/코드 보존).
    // 기존 주석(정리): 왼쪽 아래(-0.5,-0.5), 오른쪽 위(0.5,0.5).
    glRectf(-0.25f, -0.25f, 0.25f, 0.25f);          // NDC 기준 중심(0,0)에 한 변 길이 0.5인 사각형을 그린다.
                                                     // 기존 주석(정리): 창 기준 1/4 크기 느낌의 사각형 표현.

    glutSwapBuffers();                              // 더블 버퍼링에서 back buffer를 화면(front)으로 교체한다.
}                                                   // RenderScene 함수 종료.

void SetupRC(void)                                  // 렌더링 초기 상태(Rendering Context)를 설정하는 함수다.
{                                                   // SetupRC 함수 시작.
    std::cout << "SetupRC" << std::endl;           // 초기화 함수 호출 여부를 콘솔에 기록한다.
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);          // 배경색을 RGBA=(0,0,1,1), 즉 파란색으로 설정한다.
                                                     // 기존 주석: 배경용 RGB값 설정
}                                                   // SetupRC 함수 종료.

int main(int argc, char** argv)                     // 프로그램 시작점이다.
{                                                   // main 함수 시작.
    glutInit(&argc, argv);                          // GLUT 내부 상태를 초기화하고 인자를 처리한다.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);    // 더블 버퍼링 + RGB 컬러 모드로 창을 설정한다.
    glutInitWindowSize(500, 500);                   // 창의 초기 크기를 500x500(정사각형)으로 설정한다.
                                                     // 기존 주석(정리): 가로/세로를 같게 두면 화면 비율 해석이 직관적이다.
    glutInitWindowPosition(100, 100);               // 창의 초기 위치를 화면 좌표 (100,100)으로 설정한다.
    glutCreateWindow("simple");                    // 제목이 "simple"인 GLUT 창과 OpenGL 컨텍스트를 생성한다.

    SetupRC();                                       // 배경색 등 렌더링 초기 상태를 설정한다.
    glutDisplayFunc(RenderScene);                    // 디스플레이 콜백으로 RenderScene을 등록한다.

    glutMainLoop();                                  // 이벤트/렌더 루프를 시작하고 프로그램 제어를 GLUT에 넘긴다.

}                                                   // main 함수 종료.

/* [week02 시험 요약]
 * - glViewport는 NDC 결과를 실제 픽셀 영역으로 매핑한다.
 * - glColor3f는 상태값이며 이후 도형(glRectf)에 적용된다.
 * - clear -> draw -> swap 순서를 유지해야 출력이 안정적이다.
 */
