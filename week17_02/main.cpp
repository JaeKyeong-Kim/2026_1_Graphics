#if defined(__APPLE__)      // macOS에서 GLUT 헤더 포함
#include <GLUT/glut.h>
#else                       // 그 외 환경에서 GLUT 헤더 포함
#include <GL/glut.h>
#endif

#include <cmath>            // sin, cos 사용

#define GL_PI 3.14159265f   // 원을 만들 때 사용할 PI 값

int gWindow = 0;            // GLUT 창 번호 저장
GLfloat xRot = 0.0f;        // x축 회전 각도
GLfloat yRot = 0.0f;        // y축 회전 각도
GLfloat xTran = 0.0f;       // x축 이동량
GLfloat yTran = 0.0f;       // y축 이동량
bool bCull = true;          // 컬링 사용 여부

void SetupRC(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 배경색을 흰색으로 설정
    glShadeModel(GL_FLAT);                // 단색 셰이딩 사용
    glFrontFace(GL_CCW);                  // 반시계 방향을 앞면으로 설정
    glCullFace(GL_BACK);                  // 뒷면을 제거 대상으로 설정
                                           // 위 두 줄은 현재 코드 의도를 명확히 적어둔 것임
                                           // 둘 다 OpenGL 기본값과 같아서, "작동만" 기준이면 생략 가능함
}

void Keyboard(unsigned char key, int x, int y)
{
    if (key == 'a' || key == 'A')         // a 입력 시 왼쪽으로 이동
        xTran -= 2.0f;
    else if (key == 'd' || key == 'D')    // d 입력 시 오른쪽으로 이동
        xTran += 2.0f;
    else if (key == 'w' || key == 'W')    // w 입력 시 위로 이동
        yTran += 2.0f;
    else if (key == 'x' || key == 'X')    // x 입력 시 아래로 이동
        yTran -= 2.0f;

    glutPostRedisplay();                  // 화면을 다시 그림
}

void SpecialKeyboard(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)               // 위 화살표 입력 시 x축 음의 방향 회전
        xRot -= 2.0f;
    else if (key == GLUT_KEY_DOWN)        // 아래 화살표 입력 시 x축 양의 방향 회전
        xRot += 2.0f;
    else if (key == GLUT_KEY_LEFT)        // 왼쪽 화살표 입력 시 y축 음의 방향 회전
        yRot -= 2.0f;
    else if (key == GLUT_KEY_RIGHT)       // 오른쪽 화살표 입력 시 y축 양의 방향 회전
        yRot += 2.0f;

    if (xRot > 360.0f)                    // x축 회전 각도가 360도를 넘으면 다시 줄임
        xRot -= 360.0f;
    if (xRot < 0.0f)                      // x축 회전 각도가 0보다 작아지면 다시 더함
        xRot += 360.0f;
    if (yRot > 360.0f)                    // y축 회전 각도가 360도를 넘으면 다시 줄임
        yRot -= 360.0f;
    if (yRot < 0.0f)                      // y축 회전 각도가 0보다 작아지면 다시 더함
        yRot += 360.0f;

    glutPostRedisplay();                  // 화면을 다시 그림
}

void DrawTriangleFan(bool isBackFace)
{
    const int triangleCount = 32;         // 원을 나눌 삼각형 개수
    const float radius = 50.0f;           // 반지름

    glBegin(GL_TRIANGLE_FAN);             // triangle fan 시작
        if (isBackFace)                   // 뒷면 팬이면 중심색을 노란색으로 설정
            glColor3f(1.0f, 1.0f, 0.0f);
        else                              // 앞면 팬이면 중심색을 파란색으로 설정
            glColor3f(0.0f, 0.0f, 1.0f);

        glVertex3f(0.0f, 0.0f, 0.0f);     // fan의 중심점

        for (int i = 0; i <= triangleCount; ++i) // 바깥쪽 꼭짓점을 순서대로 그림
        {
            if (isBackFace)               // 뒷면 팬의 색상 패턴
            {
                if (i % 2 == 0)           // 짝수 조각은 자홍색
                    glColor3f(1.0f, 0.0f, 1.0f);
                else                      // 홀수 조각은 하늘색
                    glColor3f(0.0f, 1.0f, 1.0f);
            }
            else                          // 앞면 팬의 색상 패턴
            {
                if (i == 1)               // 시작 조각은 파란색 유지
                    glColor3f(0.0f, 0.0f, 1.0f);
                else if (i % 2 == 0)      // 짝수 조각은 빨간색
                    glColor3f(1.0f, 0.0f, 0.0f);
                else                      // 홀수 조각은 초록색
                    glColor3f(0.0f, 1.0f, 0.0f);
            }

            float theta = 2.0f * GL_PI * i / triangleCount; // 현재 꼭짓점 각도 계산
            if (isBackFace)                                  // 뒷면 팬이면 각도를 반대로 돌려 winding 뒤집기
                theta = -theta;

            float xPos = radius * std::cos(theta);          // x좌표 계산
            float yPos = radius * std::sin(theta);          // y좌표 계산
            glVertex3f(xPos, yPos, 0.0f);                   // 바깥쪽 꼭짓점 추가
        }
    glEnd();                                // triangle fan 종료
}

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);           // 색상 버퍼 초기화

    glMatrixMode(GL_MODELVIEW);             // 모델뷰 행렬 모드로 전환
    glLoadIdentity();                       // 모델뷰 행렬 초기화

    glPushMatrix();                         // 현재 행렬 상태 저장
        glRotatef(xRot, 1.0f, 0.0f, 0.0f);  // x축 회전 적용
        glRotatef(yRot, 0.0f, 1.0f, 0.0f);  // y축 회전 적용
        glTranslatef(xTran, yTran, 0.0f);   // x, y 이동 적용

        if (bCull)                          // 컬링을 사용하는 경우
        {
            glEnable(GL_CULL_FACE);         // 앞면/뒷면 판별 기능 활성화
            DrawTriangleFan(false);         // 앞면 방향으로 fan 한 번 그림
            DrawTriangleFan(true);          // 뒷면 방향으로 fan 한 번 더 그림
                                           // false/true는 테스트용 분기가 아니라
                                           // winding이 서로 반대인 두 면을 각각 그리기 위한 구분값임
        }
        else                                // 컬링을 사용하지 않는 경우
        {
            glDisable(GL_CULL_FACE);        // 앞면/뒷면 판별 기능 비활성화
            DrawTriangleFan(false);         // fan 하나만 그림
                                           // 현재 bCull를 true로만 쓸 거면 이 else 블록은 없어도 됨
                                           // 이 블록은 컬링 on/off 비교 실험용으로 남겨둔 것임
        }
    glPopMatrix();                          // 저장했던 행렬 상태 복원

    glutSwapBuffers();                      // 더블 버퍼 화면 교체
}

void ChangeSize(GLsizei w, GLsizei h)
{
    GLint wSize = 100;                      // 기본 월드 크기
    GLfloat aspectRatio;                    // 화면 비율 저장 변수

    if (h == 0)                             // 0으로 나누는 상황 방지
        h = 1;

    glViewport(0, 0, w, h);                 // 실제 그릴 화면 영역 설정

    glMatrixMode(GL_PROJECTION);            // 투영 행렬 모드로 전환
    glLoadIdentity();                       // 투영 행렬 초기화

    aspectRatio = (GLfloat)w / (GLfloat)h;  // 가로세로 비율 계산
    if (w <= h)                             // 세로가 더 긴 창이면
        glOrtho(-wSize, wSize, -wSize / aspectRatio, wSize / aspectRatio, -100.0, 100.0); // 세로 비율 보정
    else                                    // 가로가 더 긴 창이면
        glOrtho(-wSize * aspectRatio, wSize * aspectRatio, -wSize, wSize, -100.0, 100.0); // 가로 비율 보정

    glMatrixMode(GL_MODELVIEW);             // 다시 모델뷰 행렬 모드로 전환
    glLoadIdentity();                       // 모델뷰 행렬 초기화

    glutPostRedisplay();                    // 창 크기 변경 후 다시 그림
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);                  // GLUT 초기화
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // 더블 버퍼와 RGB 모드 사용
    glutInitWindowSize(500, 500);           // 창 크기 설정
    glutInitWindowPosition(400, 400);       // 창 시작 위치 설정
    gWindow = glutCreateWindow("week17_02"); // 창 생성

    SetupRC();                              // 초기 렌더링 상태 설정
    glutDisplayFunc(RenderScene);           // 화면 그리기 함수 등록
    glutReshapeFunc(ChangeSize);            // 창 크기 변경 함수 등록
    glutKeyboardFunc(Keyboard);             // 일반 키보드 입력 함수 등록
    glutSpecialFunc(SpecialKeyboard);       // 특수 키 입력 함수 등록

    glutMainLoop();                         // GLUT 이벤트 루프 시작
    return 0;                               // 프로그램 종료
}

/* [week17_02 정리]
 * - bCull는 컬링 기능을 켤지 말지를 정하는 스위치다.
 * - glEnable(GL_CULL_FACE)를 켜면 OpenGL이 꼭짓점 winding을 보고 앞면/뒷면을 구분한다.
 * - DrawTriangleFan(false)는 앞면 방향으로 정의된 fan이다.
 * - DrawTriangleFan(true)는 각도를 반대로 계산해서 winding을 뒤집은 fan이다.
 * - 그래서 컬링이 켜진 상태에서 fan을 두 번 그리면, 한 번은 앞면 색이 보이고 다른 한 번은 뒷면 색이 보이게 된다.
 * - 현재 else는 비교 실험용이다. bCull를 항상 true로 쓸 거면 else는 없어도 된다.
 * - SetupRC의 glFrontFace(GL_CCW), glCullFace(GL_BACK)도 현재는 기본값과 같아서 생략 가능하다.
 * - 하지만 수업/시험용 코드에서는 "왜 이렇게 보이는지"를 명확히 보여주기 위해 적어두는 편이 더 낫다.
 * - 즉 현재 코드에서 불필요하다고 볼 수 있는 부분은 "else 블록"과 "기본값을 다시 적는 두 줄"이다.
 * - 다만 둘 다 완전히 쓸모없는 코드는 아니고, 비교 설명과 의도 명시를 위해 남겨둔 것이다.
 */
