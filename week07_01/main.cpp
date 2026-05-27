#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include <iostream>
#include <stdio.h>

void RenderScene(void)
{
    std::cout << "RenderScene" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat x, y, z, angle;
    glPushMatrix();
        glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
        glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
        glPointSize(4.0f);

        const GLfloat radius = 80.0f;
        const GLfloat maxAngle = 1080.0f; // 360 * 3: 원이 3번 회전
        const GLfloat zStart = -120.0f;
        const GLfloat zEnd = 120.0f;
        const GLfloat pi = 3.14f;

        
        for (int i = 0; i < 360; ++i)
        {
            angle = (maxAngle * i) / 360.0f;
            GLfloat rad = angle * pi / 180.0f;

            x = std::cos(rad) * radius;
            y = std::sin(rad) * radius;
            z = zStart + (zEnd - zStart) * i / 360.0f;

            // angle은 GLfloat라 % 연산이 불가하므로, 정수 인덱스 i로 시작점(0,120,240,360)을 판별한다.
            if (i % 120 == 0) { // if(fmodf(angle, all) <= 0.08f) 같은 방식으로도 판별 가능하지만, i로 판별하는 게 더 직관적이다. 이 방식에 대해 thrshold 하는 이유: discrete한 환경에서는 0으로 딱 나눈어 떨어지지 않는 경우 등을 상정해야 함, %연산은 실수부에서 제대로 작동하지 않을 수도 있기 때문이다.
                glPointSize(10.0f); // 점 크기는 이 안에서는 변경되지 않으므로, 색상만 바꿔서 시작점을 강조한다. 점 크기는 glBegin(GL_POINTS) 바깥에서 한 번만 설정해주면 된다.
                glColor3f(0.0f, 1.0f, 0.0f);

            }
            else{
                glPointSize(4.0f);
                glColor3f(1.0f, 0.0f, 0.0f);
            }

            glBegin(GL_POINTS);
            glVertex3f(x, y, z);
            glEnd();
        } 
      
        
    glPopMatrix();

    glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h)
{
    GLint wSize = 250;
    GLfloat aspectRatio;

    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    aspectRatio = (GLfloat)w / (GLfloat)h;
    if (w <= h)
        glOrtho(-wSize, wSize, -wSize / aspectRatio, wSize / aspectRatio, -300.0, 300.0);
    else
        glOrtho(-wSize * aspectRatio, wSize * aspectRatio, -wSize, wSize, -300.0, 300.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutPostRedisplay();
}

void SetupRC(void)
{
    std::cout << "SetupRC" << std::endl;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("week07_01");

    SetupRC();
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    glutMainLoop();
}

/*
===============================================================================
[week07_01 현재 코드 기준 설명]
===============================================================================

1) 이 코드가 화면에 보여주는 것
- 원을 3바퀴 도는 궤적과 z축 진행을 결합한 3D 점열(헬릭스)을 그린다.
- 각 회전의 시작점(0, 120, 240, 360)만 초록색과 더 큰 점 크기로 강조한다.

2) 전체 실행 흐름 (main 기준)
- glutInit / glutInitDisplayMode / glutInitWindowSize 로 창 초기화
- SetupRC(): 배경색(검은색) 같은 렌더링 기본 상태 설정
- glutDisplayFunc(RenderScene): 실제 그리기 함수 등록
- glutReshapeFunc(ChangeSize): 창 크기 변경 시 투영 재설정 함수 등록
- glutMainLoop(): 이벤트 루프 시작

3) RenderScene 핵심
- glClear(GL_COLOR_BUFFER_BIT): 이전 프레임 지우기
- glMatrixMode(GL_MODELVIEW), glLoadIdentity(): 모델뷰 행렬 초기화
- glPushMatrix() ~ glPopMatrix(): 현재 변환 상태를 보호한 채 회전/그리기 수행

4) 시점(비스듬히 보는 효과) 설정 부분
- glRotatef(45, 1,0,0): x축 기준 45도 회전
- glRotatef(45, 0,1,0): y축 기준 45도 회전
- 두 회전을 연속 적용하면 기본 정면 시점이 아닌 사선(입체감 있는) 시점으로 보인다.
- 즉, 카메라를 직접 옮긴 것이 아니라 모델뷰 변환으로 관측 방향이 바뀐 효과를 만든다.

5) 점 좌표 생성 로직
- maxAngle = 1080도(=360도 * 3회전)
- angle을 0~1080도로 선형 증가시키며 rad(라디안)로 변환
- x = cos(rad) * radius
- y = sin(rad) * radius
- z는 zStart(-120)에서 zEnd(120)까지 선형 증가
- 결과적으로 x,y는 원운동, z는 직선 이동 -> 3D 나선(helix) 형상

6) 시작점만 다른 색/크기로 보이는 이유
- 반복문 안에서 i % 120 == 0 인 경우만 시작점으로 본다.
- 시작점이면 glColor3f(0,1,0)과 glPointSize(10.0f)을 사용한다.
- 그 외 점은 glColor3f(1,0,0)과 glPointSize(4.0f)을 사용한다.
- 즉, 한 번의 루프 안에서 "조건에 따라 현재 점의 상태값"만 바꿔서 바로 그리는 방식이다.

7) ChangeSize(리사이즈 대응)
- glViewport(0,0,w,h): 창 전체를 렌더 영역으로 사용
- glOrtho(...)에서 aspectRatio(w/h) 보정으로 화면 비율 변화 대응
- near/far를 -300~300으로 설정해 z축 깊이 범위를 충분히 확보

8) 핵심 요약 한 줄
- "모델뷰 회전으로 시점을 비스듬히 만든 뒤, cos/sin 기반 원운동 + z축 이동 점열을 그리고,
  반복문 안의 조건으로 시작점만 더 큰 초록 점으로 강조한 코드"이다.
===============================================================================
*/

/* [week07_01 Notes 보강]
 * - D7/8 요구사항 핵심: 45도 x/y 회전으로 비스듬한 시점을 만들고,
 *   3회전 나선을 z축으로 이동시키는 구조를 설명할 수 있어야 한다.
 */
