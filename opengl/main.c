#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define ROZ_X 100
#define ROZ_Y 100
#include <time.h>

// do kostki
GLint vertices[8][3] = {
        {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
        {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};

GLint vertices2[8][3] = {
        {0, 1, 0}, {0, 1, 2}, {0, 3, 0}, {0, 3, 2},
        {2, 1, 0}, {2, 1, 2}, {2, 3, 0}, {2, 3, 2}};

GLint vertices3[8][3] = {
        {0, 3, 0}, {0, 3, 3}, {0, 6, 0}, {0, 6, 3},
        {3, 3, 0}, {3, 3, 3}, {3, 6, 0}, {3, 6, 3}};

GLint faces[6][4] = {
        {1, 5, 7, 3}, {5, 4, 6, 7}, {4, 0, 2, 6},
        {3, 7, 6, 2}, {0, 1, 3, 2}, {0, 4, 5, 1}};



GLfloat KAT=0, PI=3.14, PX=-ROZ_X/2, PY=-2, PZ=-ROZ_Y/2;
static double powierz[ROZ_X][ROZ_Y] = {0};

double min(double num1, double num2)
{
    return (num1 > num2 ) ? num2 : num1;
}

void inicjuj(void){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // macierz jednostkowa
    gluPerspective(45,1,1,100); //ustawia perspektywę, po kolei kąt, szerokość/wysokość ekranu, odległość obserwatora od obrazu i  punktu od obrazu
    glEnable(GL_DEPTH_TEST); // obiekty w tyle są rysowane za obiektami z przodu
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
}


void rysuj_powierzchnie(void){
    glLoadIdentity();
    glRotatef(-KAT,0,1,0); // obrót o kąt względem y
    glTranslatef(PX,PY,PZ); // przesunięcie o px py pz
    glClearColor(1,1,1,1); // czyszczenie sceny
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // wyzerowanie bufora koloru i głębokości
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); // wyświetla przód i tył obiektu, powierzchnia wypełniona
    glColor3f(0,0,0);
    glEnable(GL_TEXTURE_2D); //
    glBegin(GL_QUADS);
    for (int x=0; x<ROZ_X-1; x++){
        for (int y=0; y<ROZ_Y-1; y++){
            glTexCoord2f(0,0);glVertex3f(x, powierz[x][y], y);
            glTexCoord2f(0,1);glVertex3f(x, powierz[x][y+1], y+1);
            glTexCoord2f(1,1);glVertex3f(x+1, powierz[x+1][y+1], y+1);
            glTexCoord2f(1,0);glVertex3f(x+1, powierz[x+1][y], y);
        }
    }
    glEnd();
    //glBindTexture(GL_TEXTURE_2D, 0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glDisable(GL_TEXTURE_2D);
    // tworzy kostki
    glBegin(GL_QUADS);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            //glColor3fv((GLfloat*)&vertexColors[faces[i][j]]);
            glColor3f(0.6, 1.0, 0.0); glVertex3iv((GLint*)&vertices[faces[i][j]]);
        }
    }
    glEnd();
    glBegin(GL_QUADS);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            //glColor3fv((GLfloat*)&vertexColors[faces[i][j]]);
            glColor3f(0.4, 1.0, 1.0); glVertex3iv((GLint*)&vertices2[faces[i][j]]);
        }
    }
    glEnd();

    glBegin(GL_QUADS);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            //glColor3fv((GLfloat*)&vertexColors[faces[i][j]]);
            glColor3f(0.96, 0.59, 0.86); glVertex3iv((GLint*)&vertices3[faces[i][j]]);
        }
    }
    glEnd();


    // tworzy czworościany
    for (int p=10; p<ROZ_X-1; p+=ROZ_X/10){
        glBegin(GL_TRIANGLE_STRIP);
        glColor3f(1, 1, 1); glVertex3f(p, powierz[p][p]+2, p);
        glColor3f(1, 0, 0); glVertex3f(-1+p, powierz[-1+p][1+p], 1+p);
        glColor3f(0, 1, 0); glVertex3f(1+p, powierz[1+p][1+p], 1+p);
        glColor3f(0, 0, 1); glVertex3f(p, powierz[p][-1+p], -1.4+p);
        glColor3f(1, 1, 1); glVertex3f(p, powierz[p][p]+2, p);
        glColor3f(1, 0, 0); glVertex3f(-1+p, powierz[-1+p][1+p], 1+p);
        glEnd();
    }


    glFlush();
    glutSwapBuffers(); // przełączenie buforów, ten w którym było rysowane staje się widoczny
}




// poruszanie się
void special(int key, int a, int b) {
    switch (key) {
        case GLUT_KEY_LEFT: KAT+=4; if (KAT>360) KAT-=360; break;
        case GLUT_KEY_RIGHT: KAT-=4; if (KAT<0) KAT+=360; break;
        case GLUT_KEY_UP: PX += sin(PI*KAT/180); PZ += cos(PI*KAT/180); PY = -powierz[(int)-PX][(int)-PZ]-2; break;
        case GLUT_KEY_DOWN: PX -= sin(PI*KAT/180); PZ -= cos(PI*KAT/180); PY = -powierz[(int)-PX][(int)-PZ]-2; break;
    }
    glutPostRedisplay(); // odśwież wyświetlanie
}



void gora(int px, int py, int r1, int r2, int wys){
    int i,j;
    for (i=-r1/2;i<r1/2;i++){
        for (j=-r1/2;j<r1/2;j++) {
            if (2 * sqrt(i * i + j * j) < r1) {
                powierz[(i + px + ROZ_X) % ROZ_X][(j + py + ROZ_Y) % ROZ_Y] += min(wys, (r1 - 2 * sqrt(i * i + j * j)) *
                                                                                        wys / (r1 - r2));
            }
        }

    }
}


void figura(int px, int py, int r){
    int i, j;
    for (i=-r/2; i<r/2; i++){
        for (j=-r/2; j<r/2; j++){
            powierz[(i+px+ROZ_X)%ROZ_X][(j+py+ROZ_Y)%ROZ_Y] += r/2;
        }
    }
}


void inicjuj_plansze(int liczba_gor, int max_promien, int max_wys){
    int zarodek;
    time_t tt;
    zarodek = time(&tt);
    srand(zarodek);
    int a,r1,r2,px,py,wys;
    for (a=0;a<liczba_gor;a++){
        r1=rand()%max_promien;
        r2=r1/2;
        wys=rand()%max_wys;
        px=rand()%ROZ_X;
        py=rand()%ROZ_Y;
        gora(px, py, r1, r2, wys);
    }

}


void inicjuj_teksture(char nazwa[]){
    unsigned int texture;
    glGenTextures(1, &texture);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("sand.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("Failed to load texture");
    }
    stbi_image_free(data);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Desert");
    glutSpecialFunc(special); // tutaj ma byc special
    inicjuj();
    inicjuj_teksture("fine-sand.bmp");
    inicjuj_plansze(100,30,3);

    glutDisplayFunc(rysuj_powierzchnie);
    glutMainLoop();
}
