#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600
#define POSITION_X 300
#define POSITION_Y 100

#define BACKGROUND_R 0.5
#define BACKGROUND_G 0.5
#define BACKGROUND_B 0.5

#define MARGIN_V 50
#define MARGIN_H 100

#define LINE_V1 300
#define LINE_V2 500
#define LINE_H1 390
#define LINE_H2 210

#define OFFSET 5

float x, y;

int casa[3][3] =  {{0,0,0}
                  ,{0,0,0}
                  ,{0,0,0}};

int posX[3][3] =  {{200, 200, 200}
                  ,{400, 400, 400}
                  ,{600, 600, 600}};

int posY[3][3] =  {{HEIGHT - 120, HEIGHT - 300, HEIGHT - 480}
                  ,{HEIGHT - 120, HEIGHT - 300, HEIGHT - 480}
                  ,{HEIGHT - 120, HEIGHT - 300, HEIGHT - 480}};

int jogador = 1, vencedor = 0;
int placarJ1 = 0, placarJ2 = 0;
char sPlacarJ1[3], sPlacarJ2[3];
bool restart = false;
bool velha = false;
int checaVelha = 0;

int checaVitoria();
void mouse (int, int, int, int);
void desenha(void);
void trocaJogador();
void renderTrofeu();
void DesenhaTextoStroke(void *font, char *string);
void placar();
void drawCircle( GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides );
void drawX(int);

int main (int argc, char* argv[]){

    printf("\nJOGO DA VELHA | Console: \n\n");

    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(POSITION_X, POSITION_Y);
    glutCreateWindow("Joga da Velha 1.0 - AndreFPaiva");

    glClearColor(BACKGROUND_R, BACKGROUND_G, BACKGROUND_B, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutMouseFunc(mouse);
    glutDisplayFunc(desenha);
    glutMainLoop();

    return (0);
}

void trocaJogador(){
    if (jogador == 1)jogador = 2;
    else if (jogador == 2) jogador = 1;
}

void mouse (int button, int state, int mouseX, int mouseY){

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){

        if (!vencedor){
            ////// LINHA 0
            if (mouseX > 100 && mouseX < 296 && mouseY > 47 && mouseY < 200){
                if (!casa[0][0]){
                    casa[0][0] = jogador;
                    printf("*** jogador %d na casa 0,0\n",jogador);
                    trocaJogador();
                }
            }
            if (mouseX > 308 && mouseX < 497 && mouseY > 49 && mouseY < 201){
                if (!casa[1][0]){
                    casa[1][0] = jogador;
                    printf("*** jogador %d na casa 1,0\n",jogador);
                    trocaJogador();
                }
            }
            if (mouseX > 511 && mouseX < 699 && mouseY > 52 && mouseY < 202){
                if (!casa[2][0]){
                    casa[2][0] = jogador;
                    printf("*** jogador %d na casa 2,0\n",jogador);
                    trocaJogador();
                }
            }
            ///// LINHA 1
            if (mouseX > 100 && mouseX < 297 && mouseY > 213 && mouseY < 382){
                if (!casa[0][1]){
                    casa[0][1] = jogador;
                    printf("*** jogador %d na casa 0,1\n",jogador);
                    trocaJogador();
                }
            }
            if (mouseX > 309 && mouseX < 498 && mouseY > 213 && mouseY < 381){
                if (!casa[1][1]){
                    casa[1][1] = jogador;
                    printf("*** jogador %d na casa 1,1\n",jogador);
                    trocaJogador();
                }
            }
            if (mouseX > 506 && mouseX < 698 && mouseY > 212 && mouseY < 383){
                if (!casa[2][1]){
                    casa[2][1] = jogador;
                    printf("*** jogador %d na casa 2,1\n",jogador);
                    trocaJogador();
                }
            }
            ////// LINHA 2
            if (mouseX > 100 && mouseX < 296 && mouseY > 392 && mouseY < 550){
                if (!casa[0][2]){
                    casa[0][2] = jogador;
                    printf("*** jogador %d na casa 0,2\n",jogador);
                    trocaJogador();
                }
            }
            if (mouseX > 307 && mouseX < 497 && mouseY > 393 && mouseY < 547){
                if (!casa[1][2]){
                    casa[1][2] = jogador;
                    printf("*** jogador %d na casa 1,2\n",jogador);
                    trocaJogador();
                }
            }
            if (mouseX > 507 && mouseX < 694 && mouseY > 392 && mouseY < 545){
                if (!casa[2][2]){
                    casa[2][2] = jogador;
                    printf("*** jogador %d na casa 2,2\n",jogador);
                    trocaJogador();
                }
            }
            checaVitoria();
        }
        if (restart){
            for (int i=0; i < 3; i++){
                for (int j=0; j < 3; j++){
                    casa[i][j] = 0;
                }
            }
            vencedor = 0;
            jogador = 1;
            restart = false;
            velha = false;
        }
    }

    glutPostRedisplay();
}


void desenha(void){

    glutReshapeWindow(WIDTH,HEIGHT);

    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(100);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (casa[i][j] == 1) glColor3f( 1.0, 1.0, 0.4);
            if (casa[i][j] == 2) glColor3f( 1.0, 0.3, 0.4);
            if (casa[i][j] != 0){
                x = posX[i][j];
                y = posY[i][j];

                if (casa[i][j] == 1) drawCircle(x, y, 0, 40, 50);
                else drawX(35);
            }
        }
    }

    //desenho do tabuleiro
    glColor3f( 0.2, 0.3, 0.4);
    glBegin(GL_POLYGON);
        glVertex2i(LINE_V1, MARGIN_V);
        glVertex2i(LINE_V1, HEIGHT-MARGIN_V);
        glVertex2i(LINE_V1+OFFSET, HEIGHT-MARGIN_V);
        glVertex2i(LINE_V1+OFFSET, MARGIN_V);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2i(LINE_V2, MARGIN_V);
        glVertex2i(LINE_V2, HEIGHT-MARGIN_V);
        glVertex2i(LINE_V2+OFFSET, HEIGHT-MARGIN_V);
        glVertex2i(LINE_V2+OFFSET, MARGIN_V);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2i(MARGIN_H, LINE_H1);
        glVertex2i(WIDTH-MARGIN_H, LINE_H1);
        glVertex2i(WIDTH-MARGIN_H, LINE_H1+OFFSET);
        glVertex2i(MARGIN_H, LINE_H1+OFFSET);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2i(MARGIN_H, LINE_H2);
        glVertex2i(WIDTH-MARGIN_H, LINE_H2);
        glVertex2i(WIDTH-MARGIN_H, LINE_H2+OFFSET);
        glVertex2i(MARGIN_H, LINE_H2+OFFSET);
    glEnd();

    // fim do desenho do tabuleiro

    // titulo do jogo
    glColor3f( 0.129, 0.149, 0.250);
    glBegin(GL_POLYGON);
        glVertex2i(0, 600);
        glVertex2i(800, 600);
        glVertex2i(800, 560);
        glVertex2i(0, 560);
    glEnd();

    glColor3f( 1, 0.8, 0.039);
    glPushMatrix();
    glTranslatef(20,570,0);
    glScalef(.2, .2, 0);
    glLineWidth(2);
    DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Jogo da Velha");
    glPopMatrix();

    placar();

    if (vencedor) renderTrofeu();
    if (velha) renderTrofeu();

    glFlush();

}

void placar(){
    if (jogador == 1 && !vencedor){
        glColor3f( 1, 1, 1);
        glPushMatrix();
        glTranslatef(600,570,0);
        glScalef(.15, .15, 0);
        glLineWidth(2);
        DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Vez do jogador 1");
        glPopMatrix();

    } else if (jogador == 2 && !vencedor){
        glColor3f( 1, 1, 1);
        glPushMatrix();
        glTranslatef(600,570,0);
        glScalef(.15, .15, 0);
        glLineWidth(2);
        DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Vez do jogador 2");
        glPopMatrix();
    } else if (vencedor){
        glColor3f( 1, 1, 1);
        glPushMatrix();
        glTranslatef(600,570,0);
        glScalef(.15, .15, 0);
        glLineWidth(2);
        if (vencedor == 1)
            DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Jogador 1 GANHOU");
        else if (vencedor == 2)
            DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Jogador 2 GANHOU");
        glPopMatrix();
    }

    itoa(placarJ1, sPlacarJ1, 10);
    itoa(placarJ2, sPlacarJ2, 10);

    glColor3f( 1, 1, 1);
    glPushMatrix();
    glTranslatef(400,570,0);
    glScalef(.15, .15, 0);
    glLineWidth(2);
    DesenhaTextoStroke(GLUT_STROKE_ROMAN,"x");
    glPopMatrix();

    glPushMatrix();
    glColor3f( 1.0, 1.0, 0.4);
    glTranslatef(370,570,0);
    glScalef(.15, .15, 0);
    DesenhaTextoStroke(GLUT_STROKE_ROMAN, sPlacarJ1);
    glPopMatrix();

    glPushMatrix();
    glColor3f( 1.0, 0.3, 0.4);
    glTranslatef(425,570,0);
    glScalef(.15, .15, 0);
    DesenhaTextoStroke(GLUT_STROKE_ROMAN, sPlacarJ2);
    glPopMatrix();
}

void DesenhaTextoStroke(void *font, char *string)
{
// Exibe caractere a caractere
while(*string)
glutStrokeCharacter(GLUT_STROKE_ROMAN,*string++);
}

int checaVitoria(){

    // diagonais
    if (casa[0][0] == casa[1][1] &&
        casa[1][1] == casa[2][2] &&
        casa[2][2] == casa[0][0] && casa[0][0] != 0){
        vencedor = casa[0][0];
        printf("\n\n***\n***Jogador %d ganhou\n\n", vencedor);
    }
    if (casa[0][1] == casa[1][1] &&
        casa[1][1] == casa[2][1] &&
        casa[2][1] == casa[0][1] && casa[0][1] != 0){
        vencedor = casa[0][1];
        printf("\n\n***\n***Jogador %d ganhou\n\n", vencedor);
    }
    if (casa[0][2] == casa[1][1] &&
        casa[1][1] == casa[2][0] &&
        casa[2][0] == casa[0][2] && casa[0][2] != 0){
        vencedor = casa[0][2];
        printf("\n\n***\n***Jogador %d ganhou\n\n", vencedor);
    }
    // horizontais
    if (casa[0][0] == casa[0][1] &&
        casa[0][1] == casa[0][2] &&
        casa[0][2] == casa[0][0] && casa[0][0] != 0){
        vencedor = casa[0][0];
        printf("\n\n***\n***Jogador %d ganhou\n\n", vencedor);
    }
    if (casa[1][0] == casa[1][1] &&
        casa[1][1] == casa[1][2] &&
        casa[1][2] == casa[1][0] && casa[1][0] != 0){
        vencedor = casa[1][0];
        printf("\n\n***\n***Jogador %d ganhou\n\n", vencedor);
    }
    if (casa[2][0] == casa[2][1] &&
        casa[2][1] == casa[2][2] &&
        casa[2][2] == casa[2][0] && casa[2][0] != 0){
        vencedor = casa[2][0];
        printf("\n\n***\n***Jogador %d ganhou\n\n", vencedor);
    }
    // verticais
    if (casa[0][0] == casa[1][0] &&
        casa[1][0] == casa[2][0] &&
        casa[2][0] == casa[0][0] && casa[0][0] != 0){
        vencedor = casa[0][0];
        printf("\n\n***\n***Jogador %d ganhou\n\n", vencedor);
    }
    if (casa[0][1] == casa[1][1] &&
        casa[1][1] == casa[2][1] &&
        casa[2][1] == casa[0][1] && casa[0][1] != 0){
        vencedor = casa[0][1];
        printf("\n\n***\n***Jogador %d ganhou\n\n", vencedor);
    }
    if (casa[0][2] == casa[1][2] &&
        casa[1][2] == casa[2][2] &&
        casa[2][2] == casa[0][2] && casa[0][2] != 0){
        vencedor = casa[0][2];
        printf("\n\n***\n***Jogador %d ganhou\n\n", vencedor);
    }
    if (vencedor == 1) placarJ1++;
    if (vencedor == 2) placarJ2++;
    for (int i=0; i<3; i++){
        for (int j = 0; j<3; j++){
            if (casa[i][j] != 0){
                checaVelha++;
                if (checaVelha == 9 && !vencedor) velha = true;

            }
        }
    }
    printf("\nJogada nº %d:\n", checaVelha);
    checaVelha = 0;

    return vencedor;
}

void renderTrofeu(){


    if (!velha){
        glPointSize(50);

        int offsetSombra = 5;

        //sombra
        glColor3f( 0, 0, 0);
        glBegin(GL_POINTS);
            glVertex2i(338 + offsetSombra, 154 + offsetSombra);
            glVertex2i(388 + offsetSombra, 154 + offsetSombra);
            glVertex2i(389 + offsetSombra, 171 + offsetSombra);
            glVertex2i(414 + offsetSombra, 171 + offsetSombra);
            glVertex2i(414 + offsetSombra, 154 + offsetSombra);
            glVertex2i(401 + offsetSombra, 217 + offsetSombra);
            glVertex2i(401 + offsetSombra, 266 + offsetSombra);
            glVertex2i(370 + offsetSombra, 292 + offsetSombra);
            glVertex2i(335 + offsetSombra, 313 + offsetSombra);
            glVertex2i(311 + offsetSombra, 352 + offsetSombra);
            glVertex2i(291 + offsetSombra, 397 + offsetSombra);
            glVertex2i(291 + offsetSombra, 421 + offsetSombra);
            glVertex2i(338 + offsetSombra, 421 + offsetSombra);
            glVertex2i(386 + offsetSombra, 421 + offsetSombra);
            glVertex2i(419 + offsetSombra, 421 + offsetSombra);
            glVertex2i(467 + offsetSombra, 421 + offsetSombra);
            glVertex2i(515 + offsetSombra, 421 + offsetSombra);
            glVertex2i(514 + offsetSombra, 394 + offsetSombra);
            glVertex2i(493 + offsetSombra, 350 + offsetSombra);
            glVertex2i(468 + offsetSombra, 312 + offsetSombra);
            glVertex2i(433 + offsetSombra, 292 + offsetSombra);
            glVertex2i(464 + offsetSombra, 154 + offsetSombra);
        glEnd();

        if (vencedor == 1) glColor3f( 0.976, 0.698, 0.141);
        if (vencedor == 2) glColor3f( 0.921, 0, 0.352);

        // trofeu
        glBegin(GL_POINTS);
            glVertex2i(338, 154);
            glVertex2i(388, 154);
            glVertex2i(389, 171);
            glVertex2i(414, 171);
            glVertex2i(414, 154);
            glVertex2i(401, 217);
            glVertex2i(401, 266);
            glVertex2i(370, 292);
            glVertex2i(335, 313);
            glVertex2i(311, 352);
            glVertex2i(291, 397);
            glVertex2i(291, 421);
            glVertex2i(338, 421);
            glVertex2i(386, 421);
            glVertex2i(419, 421);
            glVertex2i(467, 421);
            glVertex2i(515, 421);
            glVertex2i(514, 394);
            glVertex2i(493, 350);
            glVertex2i(468, 312);
            glVertex2i(433, 292);
            glVertex2i(464, 154);
        glEnd();

        glColor3f( 1, 1, 1);
        glPushMatrix();
        glTranslatef(230,30,0);
        glScalef(.15, .15, 0);
        glLineWidth(2);
        DesenhaTextoStroke(GLUT_STROKE_ROMAN,"CLIQUE PARA JOGAR NOVAMENTE!");
        glPopMatrix();
        restart = true;
    }else{
        glColor3f( 1, 1, 1);
        glPushMatrix();
        glTranslatef(230,300,0);
        glScalef(.4, .4, 0);
        glLineWidth(4);
        DesenhaTextoStroke(GLUT_STROKE_ROMAN,"DEU VELHA!");
        glPopMatrix();
        restart = true;
    }




    glFlush();

}
void drawX(int tamanho){
    glLineWidth(10);
    glBegin(GL_LINES);
    glVertex2i(x-tamanho,y-tamanho);
    glVertex2i(x+tamanho,y+tamanho);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(x-tamanho,y+tamanho);
    glVertex2i(x+tamanho,y-tamanho);
    glEnd();
}
void drawCircle( GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides )
{
    int numberOfVertices = numberOfSides + 2;

    GLfloat twicePi = 2.0f * M_PI;

    GLfloat circleVerticesX[numberOfVertices];
    GLfloat circleVerticesY[numberOfVertices];
    GLfloat circleVerticesZ[numberOfVertices];

    circleVerticesX[0] = x;
    circleVerticesY[0] = y;
    circleVerticesZ[0] = z;

    for ( int i = 1; i < numberOfVertices; i++ )
    {
        circleVerticesX[i] = x + ( radius * cos( i *  twicePi / numberOfSides ) );
        circleVerticesY[i] = y + ( radius * sin( i * twicePi / numberOfSides ) );
        circleVerticesZ[i] = z;
    }

    GLfloat allCircleVertices[( numberOfVertices ) * 3];

    for ( int i = 0; i < numberOfVertices; i++ )
    {
        allCircleVertices[i * 3] = circleVerticesX[i];
        allCircleVertices[( i * 3 ) + 1] = circleVerticesY[i];
        allCircleVertices[( i * 3 ) + 2] = circleVerticesZ[i];
    }

    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, allCircleVertices );
    glDrawArrays( GL_TRIANGLE_FAN, 0, numberOfVertices);
    glDisableClientState( GL_VERTEX_ARRAY );
}
