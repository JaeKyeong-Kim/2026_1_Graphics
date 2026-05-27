#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include <iostream>
#include <stdio.h>

GLfloat gPointSizeRange[2] = {1.0f, 64.0f};
GLfloat gPointSizeStep = 0.0001f;

void RenderScene(void)
{
    std::cout << "RenderScene" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);

    const GLfloat radius = 80.0f;
    const GLfloat maxAngle = 1080.0f; // 360 * 3: 원이 3번 회전
    const GLfloat zStart = -120.0f;
    const GLfloat zEnd = 120.0f;
    const GLfloat pi = 3.14f;
    const int total = 360;

    // 조회한 하드웨어 지원 범위를 그대로 사용한다.
    GLfloat visualMinSize = gPointSizeRange[0];
    GLfloat visualMaxSize = gPointSizeRange[1];
    if (visualMaxSize < visualMinSize)
        visualMaxSize = visualMinSize;

    const GLfloat growthPower = 1.0f; // 1보다 크면 증가가 더 완만해진다.

    for (int i = 0; i < total; ++i)
    {
        const GLfloat angle = (maxAngle * i) / static_cast<GLfloat>(total);
        const GLfloat rad = angle * pi / 180.0f;

        const GLfloat x = std::cos(rad) * radius;
        const GLfloat y = std::sin(rad) * radius;
        const GLfloat z = zStart + (zEnd - zStart) * i / static_cast<GLfloat>(total);

        const GLfloat t = static_cast<GLfloat>(i) / static_cast<GLfloat>(total - 1);
        GLfloat size = visualMinSize + (visualMaxSize - visualMinSize) * std::pow(t, growthPower);

        // 지원 step 단위에 맞춰 점 크기를 양자화한다.
        if (gPointSizeStep > 0.0f)
            size = visualMinSize + std::floor((size - visualMinSize) / gPointSizeStep) * gPointSizeStep;
        if (size > visualMaxSize)
            size = visualMaxSize;

        glPointSize(size);
        glColor3f(1.0f, 0.0f, 0.0f);

        glBegin(GL_POINTS);
        glVertex3f(x, y, z);
        glEnd();
    }

    glPopMatrix();
    glutSwapBuffers();
}

// 이 부분이 원본 정답. 이 스타일로 작성하는 것 새로운 폴더 하나 만들어서 연습해보자. 이거 기반으로 만들어달라고 하고 이거도 설명 정리하기
// glgetfloatv(gl_point_ize_range, sizes);
// glgetfloatv(gl_point_ize_granualarity, &step);
// z = -50.0f;
// for (angle=0.0f, angle<=(2.0f*gl_pi * 3.0f; angle +- 0.1f)){
//     x=50.0f * cos(angle);
//     y=50.0f * sin(angle);
//     glpointsize(cursize);

//     glBegin(GL_POINTS);
//     glVertex3f(x, y, z);
//     glEnd();

//     z += 0.5f;
//     cursize += step;
// }

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

    // 시스템(하드웨어/드라이버)에서 지원하는 점 크기 범위와 step 단위를 조회
    glGetFloatv(GL_POINT_SIZE_RANGE, gPointSizeRange);
    glGetFloatv(GL_POINT_SIZE_GRANULARITY, &gPointSizeStep);

    std::cout << "GL_POINT_SIZE_RANGE: [" << gPointSizeRange[0] << ", " << gPointSizeRange[1] << "]" << std::endl;
    std::cout << "GL_POINT_SIZE_GRANULARITY: " << gPointSizeStep << std::endl;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("week08_01");

    SetupRC();
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    glutMainLoop();
}

/*
===============================================================================
[week08_01 동작 상세 정리 - 새로 추가된 함수/로직 중심]
===============================================================================

1) 이 코드가 보여주는 최종 결과
- 검은 배경 위에 3바퀴 도는 3D 나선형 점열(helix)을 그린다.
- 점 색상은 빨간색으로 고정한다.
- 점 크기는 시작점에서 끝점으로 갈수록 "점진적으로" 커지게 만든다.

2) 새로 중요한 전역 변수
- GLfloat gPointSizeRange[2]
    : 시스템이 지원하는 점 크기 최소/최대값을 저장한다.
    : gPointSizeRange[0] = 최소, gPointSizeRange[1] = 최대
- GLfloat gPointSizeStep
    : 점 크기가 실제로 증가/감소할 수 있는 단위(step, granularity)를 저장한다.

3) SetupRC()에서 새로 사용한 함수
- glGetFloatv(GL_POINT_SIZE_RANGE, gPointSizeRange)
    : 하드웨어가 허용하는 점 크기 범위를 조회한다.
- glGetFloatv(GL_POINT_SIZE_GRANULARITY, &gPointSizeStep)
    : 점 크기 변경 가능한 최소 단위를 조회한다.

의미:
- 우리가 glPointSize(원하는 값)를 호출해도,
    실제 적용은 "지원 범위"와 "지원 step" 규칙에 맞춰진다.
- 그래서 조회 후 그 값에 맞춰 size를 계산해야 예측 가능한 결과를 얻는다.

4) RenderScene()의 핵심 흐름
- glClear(): 이전 프레임 지움
- glMatrixMode(GL_MODELVIEW), glLoadIdentity(): 모델뷰 초기화
- glPushMatrix() 후 glRotatef(45, x축), glRotatef(45, y축)
    : 나선을 비스듬한 시점으로 보이게 만든다.
- for 루프에서 angle/rad를 계산하고
    x = cos(rad) * radius
    y = sin(rad) * radius
    z = zStart ~ zEnd 선형 증가
    로 나선 좌표를 만든다.

5) 점 크기 증가 로직(새 핵심)
- 진행도 t:
    t = i / (total - 1)
    (0에서 시작해서 1로 끝남)
- 기본 증가식:
    size = visualMin + (visualMax - visualMin) * pow(t, growthPower)

여기서 growthPower = 1.0의 의미:
- 선형 증가(시작부터 끝까지 일정한 비율로 커짐)
- 참고: 1보다 크게 주면 초반 완만/후반 가속 형태가 된다.

6) 양자화(quantization) 처리 이유
- if (gPointSizeStep > 0.0f)
        size = visualMin + floor((size - visualMin) / step) * step;

의미:
- 하드웨어가 허용하는 크기 단계에 맞춰 size를 내려맞춘다.
- 예: step이 0.5면 3.2는 3.0으로 맞춰 적용
- 이렇게 해야 실제 드라이버 적용값과 코드 의도가 일치한다.

7) visualMin/visualMax를 따로 두는 이유
- glGetFloatv로 조회한 최소/최대 지원 범위를 변수에 담아 계산식에 직접 사용하기 위해서다.
- 즉, 임의 상수(예: [2,10])가 아니라 드라이버가 알려준 실제 범위를 그대로 따른다.

8) ChangeSize() 역할
- glViewport(0,0,w,h): 실제 창 크기와 렌더 영역 동기화
- aspectRatio = w/h 계산 후 glOrtho 범위 보정:
    창 비율이 바뀌어도 화면 왜곡을 줄여준다.
- near/far를 -300~300으로 둬서 z축으로 이동하는 나선이 잘리지 않게 한다.

9) 한 줄 결론
- week08_01은 "삼각함수 기반 3D 나선 좌표 + 하드웨어 점 크기 속성 조회(glGetFloatv)
    + step 단위 양자화 + 완만한 성장 곡선(pow)"을 결합한 점진적 점크기 렌더링 예제다.
===============================================================================
*/

/* [week08_01 Notes 보강]
 * - D9/10 핵심: 점 크기 문제는 glPointSize + glGetFloatv(RANGE/GRANULARITY) 조합으로 설명한다.
 */
