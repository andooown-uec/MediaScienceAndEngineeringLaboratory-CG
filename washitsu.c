#include <stdlib.h>
#include <GL/glut.h>

#include "draw/draw.h"
#include "utility/utility.h"

#define BUILDING_NUM 8  // 建物の 1 辺あたりの数

typedef struct {
    int colorIndex;     // 色
    double height;      // 高さ
} Building;

GLfloat light0pos[] = { 5.0, 3.0, 10.0, 1.0 };

GLfloat red[]   = { 0.8, 0.2, 0.2, 1.0 };   // 赤
GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };   // 緑
GLfloat blue[]  = { 0.2, 0.2, 0.8, 1.0 };   // 青
GLfloat gray[]  = { 0.8, 0.8, 0.8, 1.0 };   // グレー    

float posX = 0.0, posY = 1.0, posZ = 10.0;      // プレイヤーの位置
Building buildings[BUILDING_NUM][BUILDING_NUM]; // 建物

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
    gluLookAt(posX, posY, posZ, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0);

    // 光源の位置設定
    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
    
    // 建物を描画
    for (i = 0; i < BUILDING_NUM; i++) {
        for (j = 0; j < BUILDING_NUM; j++) {
            // 座標系を保存
            glPushMatrix();
            // 座標変換
            glTranslated(
                -BUILDING_NUM / 2 + (double)i + 0.05 + (int)(i / 2.0) * 0.5 - 0.75,
                0.0,
                -BUILDING_NUM / 2 + (double)j + 0.05 + (int)(j / 2.0) * 0.5 - 0.75);
            glScaled(0.9, buildings[i][j].height, 0.9);
            // 材質を設定
            switch (buildings[i][j].colorIndex) {
                case 0:
                    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
                    break;
                case 1:
                    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, green);
                    break;
                case 2:
                    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
                    break;                
            }
            // 描画
            cube();
            // 座標系を復元
            glPopMatrix();
        }
    }
    
    // 座標系を保存
    glPushMatrix();
    // 座標変換
    glTranslated(-7.5, 0.0, -7.5);
    glScaled(15.0, 1.0, 15.0);
    // 材質を設定
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, gray);
    // 地面を描画
    plate();
    // 座標系を復元
    glPopMatrix();

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
    gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);

    // モデルビュー変換行列の設定
    glMatrixMode(GL_MODELVIEW);
}

// マウスイベントハンドラ
void mouse(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                // アニメーションを開始する
                glutIdleFunc(idle);
            } else {
                // アニメーションを停止する
                glutIdleFunc(0);
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN) {
                // 1 ステップだけ進める
                glutPostRedisplay();
            }
            break;
        default:
            break;
    }
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
            posZ -= step;
            break;
        case 's':
            posZ += step;
            break;
        case 'a':
            posX -= step;
            break;
        case 'd':
            posX += step;
            break; 
        default:
            break;
    }

    // 描画
    glutPostRedisplay();
}

// 初期化処理を行う関数
void init(void) {
    int i, j;

    // 乱数を初期化
    initRand();

    // 建物の初期化
    for (i = 0; i < BUILDING_NUM; i++) {
        for (j = 0; j < BUILDING_NUM; j++) {
            // 色と高さを計算
            int colIndex = randRange(3);
            double hei = randRangef(0.7, 1.8);
            // 建物を生成
            Building b = { colIndex, hei };
            buildings[i][j] = b;
        }
    }

    // ウィンドウを塗りつぶす色の設定
    glClearColor(1.0, 1.0, 1.0, 1.0);
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
    glutMouseFunc(mouse);       // マウスイベントハンドラ
    glutKeyboardFunc(keyboard); // キーボードイベントハンドラ
    // 初期化処理
    init();
    // イベントループの開始
    glutMainLoop();

    return 0;
}