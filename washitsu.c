#include <stdlib.h>
#include <GL/glut.h>

#include "draw/draw.h"
#include "utility/utility.h"

GLfloat light0pos[] = { 5.0, 5.0, 5.0, 1.0 };

GLfloat red[]   = { 0.8, 0.2, 0.2, 1.0 };   // 赤
GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };   // 緑
GLfloat blue[]  = { 0.2, 0.2, 0.8, 1.0 };   // 青
GLfloat gray[]  = { 0.8, 0.8, 0.8, 1.0 };   // グレー
GLfloat tatamiFrame[]  = { 0.000, 0.431, 0.329, 1.0 };  // 畳の縁
GLfloat tatamiGround[] = { 0.765, 0.847, 0.145, 1.0 };  // 畳
GLfloat wood[] = { 0.588, 0.314, 0.212, 1.0 };          // 木材

GLdouble ex = 0.0, ey = 1.5, ez = 3.5;  // 視点の位置

// アイドル時に実行される関数
void idle(void) {
    glutPostRedisplay();
}

// ウィンドウの描画イベントハンドラ
void display(void) {
    int i, j;

    // ウィンドウを塗りつぶす
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    // 視点位置と視線方向を設定
    gluLookAt(ex, ey, ez, ex, ey, ez - 3.0, 0.0, 1.0, 0.0);

    // 光源の位置設定
    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
    
    // 畳の縁を描画
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, tatamiFrame);
    plateXZ(-4.0, 0.0, -4.0, 8.0, 8.0);

    // 畳を描画
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, tatamiGround);
    plateXZ( 2.1, 0.01, -2.0, 1.8, 4.0);
    plateXZ( 0.0, 0.01, -3.9, 4.0, 1.8);
    plateXZ( 0.0, 0.01,  2.1, 4.0, 1.8);
    plateXZ(-2.0, 0.01, -1.9, 4.0, 1.8);
    plateXZ(-2.0, 0.01,  0.1, 4.0, 1.8);
    plateXZ(-3.9, 0.01, -2.0, 1.8, 4.0);
    plateXZ(-4.0, 0.01, -3.9, 4.0, 1.8);
    plateXZ(-4.0, 0.01,  2.1, 4.0, 1.8);

    // 床の間を描画
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, wood);
    cube(-4.0, 0.0, -5.0, 4.0, 0.3, 1.0);   // 床
    cube(-4.1, 0.0, -4.1, 0.2, 3.0, 0.2);   // 柱
    cube(-0.1, 0.0, -4.1, 0.2, 3.0, 0.2);   // 柱

    // バッファを交換
    glutSwapBuffers();
}

// ウィンドウのリサイズイベントハンドラ
void resize(int w, int h) {
    // ウィンドウ全体をビューポートにする
    glViewport(0, 0, w, h);

    // 透視変換行列の設定
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, (double)w / (double)h, 1.0, 100.0);

    // モデルビュー変換行列の設定
    glMatrixMode(GL_MODELVIEW);
}

// キーボードイベントハンドラ
void keyboard(unsigned char key, int x, int y) {
    float step = 0.1;

    switch (key) {
        case 'q':
        case 'Q':
        case '\033':    // ESC
            exit(0);
        case 'w':
            ez -= step;
            break;
        case 's':
            ez += step;
            break;
        case 'a':
            ex -= step;
            break;
        case 'd':
            ex += step;
            break; 
        default:
            break;
    }

    // 描画
    glutPostRedisplay();
}

// 初期化処理を行う関数
void init(void) {
    // 乱数を初期化
    initRand();

    // ウィンドウを塗りつぶす色の設定
    glClearColor(0.000, 0.482, 0.733, 1.0);
    // デプスバッファ
    glEnable(GL_DEPTH_TEST);
    // カリング
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    // ライティング
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

int main(int argc, char *argv[]) {
    // ウィンドウのサイズを指定
    glutInitWindowSize(640, 480);
    // GLUT および OpenGL 環境の初期化
    glutInit(&argc, argv);
    // ディスプレイの表示モードを RGBA に設定し、ダブルバッファリングを有効にする
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    // ウィンドウの生成・設定
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);   // 描画イベントハンドラ
    glutReshapeFunc(resize);    // リサイズイベントハンドラ
    glutKeyboardFunc(keyboard); // キーボードイベントハンドラ
    // 初期化処理
    init();
    // イベントループの開始
    glutMainLoop();

    return 0;
}