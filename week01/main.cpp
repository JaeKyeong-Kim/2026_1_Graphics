#if defined(__APPLE__)                              // macOS 환경이면 Apple GLUT 헤더를 사용한다.
#include <GLUT/glut.h>                              // macOS 기본 GLUT 프레임워크 헤더를 포함한다.
#else                                               // macOS가 아닌 환경(리눅스/윈도우 등) 분기다.
#include <GL/glut.h>                                // 일반 GLUT 헤더를 포함한다.
#endif                                              // 플랫폼 분기 전처리를 종료한다.

#include <iostream>                                 // 콘솔 로그 출력(std::cout)에 사용한다.
#include <stdio.h>                                  // C 표준 입출력 헤더(기존 코드 유지)다.

// 장면 렌더링 함수: 화면에 실제로 그리는 콜백 함수다.
void RenderScene(void)                              // GLUT가 화면 갱신 시 호출하는 디스플레이 콜백이다.
{                                                   // RenderScene 함수 시작.
    std::cout << "RenderScene" << std::endl;       // 콜백 호출 여부를 콘솔에서 확인한다.

    glClear(GL_COLOR_BUFFER_BIT);                   // 현재 설정된 배경색으로 컬러 버퍼를 지운다.
                                                     // 기존 주석(수정): "현재 생상을 사용하여 화면을 지운다."

    // glFlush();                                   // 단일 버퍼링(GLUT_SINGLE)일 때 명령 전달에 사용한다.
    // 기존 주석(정리): glFlush()는 GLUT_SINGLE과 함께 쓰는 패턴.

    glutSwapBuffers();                              // 더블 버퍼링에서 back buffer를 화면(front)으로 교체한다.
                                                     // 기존 주석(정리): glFlush 대신 사용.
}                                                   // RenderScene 함수 종료.

void SetupRC(void)                                  // 렌더링 초기 상태(Rendering Context)를 설정하는 함수다.
{                                                   // SetupRC 함수 시작.
    std::cout << "SetupRC" << std::endl;           // 초기화 함수가 호출됐는지 콘솔 로그를 남긴다.
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);          // 배경색을 RGBA=(1,0,1,1), 즉 마젠타로 설정한다.
                                                     // 기존 주석: 배경용 RGB값 설정
}                                                   // SetupRC 함수 종료.

int main(int argc, char** argv)                     // 프로그램 시작점이다.
{                                                   // main 함수 시작.
    glutInit(&argc, argv);                          // GLUT 내부 상태를 초기화하고 커맨드라인 인자를 처리한다.

    // glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // 단일 버퍼링 모드 예시(기존 메모 유지).
    // 기존 주석(정리): GLUT_SINGLE + glFlush() 조합.

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);    // 더블 버퍼링 + RGB 컬러 모드로 창을 생성한다.
                                                     // 기존 주석(정리): 단일 버퍼링에서 더블 버퍼링으로 변경.

    glutInitWindowSize(640, 480);                   // 창의 초기 크기를 가로 640, 세로 480으로 설정한다.
    glutInitWindowPosition(100, 100);               // 창의 초기 화면 위치를 (100,100)으로 설정한다.
    glutCreateWindow("simple");                    // 제목이 "simple"인 GLUT 창과 OpenGL 컨텍스트를 생성한다.

    SetupRC();                                       // 배경색 등 초기 렌더 상태를 먼저 설정한다.
    glutDisplayFunc(RenderScene);                    // 디스플레이(그리기) 콜백으로 RenderScene을 등록한다.

    glutMainLoop();                                  // 이벤트/렌더 루프를 시작하고 반환하지 않는다.

}                                                   // main 함수 종료.

/* [week01 시험 요약]
 * - glClearColor(설정)와 glClear(실행)를 구분한다.
 * - 더블 버퍼링 기본 패턴: GLUT_DOUBLE + glutSwapBuffers().
 * - 단일 버퍼링 패턴은 GLUT_SINGLE + glFlush()로 비교해서 기억한다.
 */