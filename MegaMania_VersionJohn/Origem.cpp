// animação
////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
#include <locale.h>
#include <sstream>
#include <Windows.h>
#include <MMSystem.h>

using namespace std;

#define janela_altura 800
#define janela_largura 800
// variaveis que armazenam a translacao no quadro
float tx = 0.0;
float ty = 0.0;

float tiro_x = 0.0;
float tiro_y = 0.0;
// incremento em variaveis.
char plac[20];

int color = 0;
int inicio_jogo = 0;
int animanavinimiga = 0;
int animameioNavInimiga = rand() % 2;
int  chao_y = -170;
int atira=0;
int placar=0;
int MovNavPlayer_X = 0;
int MovNavPlayer_Y = 0;
BOOLEAN gameover = false;


BOOLEAN nav_ativa[10] = { true };
int navinimigoX1[10] = { 0 };
int navinimigoX2[10] = { 0 };
int navinimigoY[10] = { 0 };
int TiroPlayerY = 0;
float rotacao = 1;
float xStep = 4;
float yStep = 4;
int ladodir = 0;
int Movball = rand() % 2;

int MovCPU = rand() % 2;


void DesenhaTexto(const char *string, int x, int y, void *fonte);
void input_callback(int key, int x, int y);
void Quadp();
void LogoIF();
void desenhaMensagem(char msg[20]);
void desenhaNaveInimigo_NIVEL1();
void ColocarNaves_NIVEL1();
void paredesExternas();
void display(void);
void tela(GLsizei w, GLsizei h);
void animacao(int valor);
void desenhaTiro();
void keyboard(unsigned char tecla, int x, int y);
void desenhaNavePlayer();

int main(int argc, char** argv)
{


	glutInit(&argc, argv); // suporte a janelas
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// PADRAO DE CORES


	glutInitWindowSize(janela_largura, janela_altura); // tamanho da janela
	glutInitWindowPosition(100, 100); // posicao que surge a janela
	glutCreateWindow("Megamania"); // cria janela


								  //glutFullScreen();
	glutReshapeFunc(tela); // configura a tela
	glutSpecialFunc(input_callback);//chama teclado
	glutDisplayFunc(display);
	glutKeyboardFunc(&keyboard); // chama teclado
	
	if (gameover == false) {
		glutTimerFunc(15, animacao, 1);

	}

	glutMainLoop(); // redesenhar
	return(0);
}


void keyboard(unsigned char tecla, int x, int y)
{
	printf("\ntecla %c\n", tecla);
	printf("\n\nDigite 1 para esquerda, 2 para direita: ");
	printf("\ntecla %c\n", tecla);
	printf("\no mouse estava em %d x %d\n", x, y);



	

	if (tecla == '1')
	{

		atira = 0;

		printf("\n o valor de atira e %i\n", atira);

	}

	if (tecla == ' ' && atira == 0)
	{
		atira = 1;
		tiro_x = MovNavPlayer_X;

		printf("\n o valor de atira e %i\n", atira);

		

		printf("\n ESPACO\n", atira);

	}
	
	glutPostRedisplay();
}

void animacao(int valor) {


	if (inicio_jogo == 0) {

		inicio_jogo = 1;

		for (int i = 0; i < 10; i++) {

			nav_ativa[i] = { true };

		}
	}



	if (animanavinimiga == 670) {

		animanavinimiga = -670;
	}
	else {
		animanavinimiga += 1;
	}

	printf("\n valor de animiga eh %i \n", animanavinimiga);


	if (animameioNavInimiga == 1) {
		animameioNavInimiga = 0;
	}
	else {
		animameioNavInimiga = 1;
	}

	if (tiro_y >= 390) {
		tiro_y = 0;
		atira = 0;
	}
	else if (tiro_y < 390 && atira == 1) {
		tiro_y += yStep;
	}

	printf("\n o valor de tiro y eh %2.f\n", tiro_y);

	glutPostRedisplay();
	glutTimerFunc(7, animacao, 1);


}
void input_callback(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		if (MovNavPlayer_Y == 220) {
			MovNavPlayer_Y = MovNavPlayer_Y;
			
		}
		else {

			MovNavPlayer_Y = MovNavPlayer_Y + 10;
		}



		printf("\n MovNavPlayer_Y igual a e %i\n", MovNavPlayer_Y);

		break;
	case GLUT_KEY_DOWN:

		if (MovNavPlayer_Y == -170) {
			MovNavPlayer_Y = MovNavPlayer_Y;
		}
		else {


			MovNavPlayer_Y = MovNavPlayer_Y - 10;
		}

		printf("\n MovNavPlayer_Y igual a e %i\n", MovNavPlayer_Y);
		break;
	case GLUT_KEY_LEFT:

		if (MovNavPlayer_X == -310) {
			MovNavPlayer_X = MovNavPlayer_X;
		}
		else {


			MovNavPlayer_X = MovNavPlayer_X - 10;
		}

		printf("\n MovNavPlayer_X igual a e %i\n", MovNavPlayer_X);
		break;
	case GLUT_KEY_RIGHT:

		if (MovNavPlayer_X == 310) {
			MovNavPlayer_X = MovNavPlayer_X;
		}
		else {


			MovNavPlayer_X = MovNavPlayer_X + 10;
		}

		printf("\n MovNavPlayer_X igual a e %i\n", MovNavPlayer_X);
		break;


	}




	glutPostRedisplay();
}


void desenhaMensagem(const char msg[20]) {

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1); // cor ->Azul aço
	glVertex2f((-313), 30);
	glVertex2f((-313), -25);
	glVertex2f((313), -25);
	glVertex2f((313), 30);
	glEnd();

	glColor3f(0, 0, 0); // cor ->Azul aço
	DesenhaTexto(msg, -48, 0, GLUT_BITMAP_HELVETICA_18);


}

void Quadp() {
	glBegin(GL_QUADS);
	glVertex2f((-3), 3);
	glVertex2f((-3), -3);
	glVertex2f((3), -3);
	glVertex2f((3), 3);
	glEnd();
}

void LogoIF() {



	glPushMatrix();
	glColor3f(1, 0, 0);

	glTranslatef(-338, 304, 0);
	glPointSize(6.0);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glVertex2f(3, -3);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(-335, 293, 0);
	Quadp();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(-335, 286, 0);
	Quadp();
	glPopMatrix();


	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(-335, 279, 0);
	Quadp();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(-328, 300, 0);
	Quadp();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(-328, 293, 0);
	Quadp();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(-328, 286, 0);
	Quadp();
	glPopMatrix();


	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(-328, 279, 0);
	Quadp();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(-321, 300, 0);
	Quadp();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(-321, 286, 0);
	Quadp();
	glPopMatrix();

}

void desenhaNaveInimigo_NIVEL1(){
	
	glPushMatrix();
	glColor3f(1, 0, 1);
	glTranslatef(-300, 115, 0);

	glBegin(GL_QUADS);
	glVertex2f((-10), 3);
	glVertex2f((-10), -3);
	glVertex2f((30), -3);
	glVertex2f((30), 3);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 1);
	glTranslatef(-300, 110, 0);

	glBegin(GL_QUADS);
	glVertex2f((-20), 3);
	glVertex2f((-20), -3);
	glVertex2f((40), -3);
	glVertex2f((40), 3);
	glEnd();

	glPopMatrix();

	//MEIO NAV
	glPushMatrix();
	glColor3f(1, 0, 1);
	glTranslatef(-300, 100, 0);

	glBegin(GL_QUADS);
	glVertex2f((-20), 3);
	glVertex2f((-20), -3);
	glVertex2f((40), -3);
	glVertex2f((40), 3);
	glEnd();

	glPopMatrix();

	if (animameioNavInimiga == 0) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslatef(-300, 100, 0);

		glBegin(GL_QUADS);
		glVertex2f((-20), 3);
		glVertex2f((-20), -3);
		glVertex2f((-10), -3);
		glVertex2f((-10), 3);
		glEnd();

		glPopMatrix();

		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslatef(-280, 100, 0);

		glBegin(GL_QUADS);
		glVertex2f((-20), 3);
		glVertex2f((-20), -3);
		glVertex2f((-10), -3);
		glVertex2f((-10), 3);
		glEnd();

		glPopMatrix();

		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslatef(-260, 100, 0);

		glBegin(GL_QUADS);
		glVertex2f((-20), 3);
		glVertex2f((-20), -3);
		glVertex2f((-10), -3);
		glVertex2f((-10), 3);
		glEnd();

		glPopMatrix();
	}

	if (animameioNavInimiga == 1) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslatef(-290, 100, 0);

		glBegin(GL_QUADS);
		glVertex2f((-20), 3);
		glVertex2f((-20), -3);
		glVertex2f((-10), -3);
		glVertex2f((-10), 3);
		glEnd();

		glPopMatrix();

		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslatef(-270, 100, 0);

		glBegin(GL_QUADS);
		glVertex2f((-20), 3);
		glVertex2f((-20), -3);
		glVertex2f((-10), -3);
		glVertex2f((-10), 3);
		glEnd();

		glPopMatrix();

		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslatef(-250, 100, 0);

		glBegin(GL_QUADS);
		glVertex2f((-20), 3);
		glVertex2f((-20), -3);
		glVertex2f((-10), -3);
		glVertex2f((-10), 3);
		glEnd();

		glPopMatrix();
	}

	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslatef(-300, 85, 0);

	glBegin(GL_QUADS);
	glVertex2f((-10), 3);
	glVertex2f((-10), -3);
	glVertex2f((30), -3);
	glVertex2f((30), 3);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 1);
	glTranslatef(-300, 90, 0);

	glBegin(GL_QUADS);
	glVertex2f((-20), 3);
	glVertex2f((-20), -3);
	glVertex2f((40), -3);
	glVertex2f((40), 3);
	glEnd();

	glPopMatrix();



}

void paredesExternas() {

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0); // cor ->Azul aço
	glVertex2f(-350, 250);
	glVertex2f(-342, 250);
	glVertex2f(-342, -250);
	glVertex2f(-350, -250);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.94f, 1.0f, 1.0f); // cor ->Azul aço
	glVertex2f(-350, 250);
	glVertex2f(-400, 250);
	glVertex2f(-400, -250);
	glVertex2f(-350, -250);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(0, 0, 0); // cor ->Azul aço
	glVertex2f(350, 250);
	glVertex2f(340, 250);
	glVertex2f(340, -250);
	glVertex2f(350, -250);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.94f, 1.0f, 1.0f); // cor ->Azul aço
	glVertex2f(350, 250);
	glVertex2f(400, 250);
	glVertex2f(400, -250);
	glVertex2f(350, -250);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0); // cor ->Azul aço
	glVertex2f(-350, 250);
	glVertex2f(-340, 250);
	glVertex2f(-340, -250);
	glVertex2f(-350, -250);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 1.0); // cor ->branco
	glVertex2f(-340, 240);
	glVertex2f(340, 240);
	glVertex2f(340, -240);
	glVertex2f(-340, -240);
	glEnd();


}

void ColocarNaves_NIVEL1(){

	int mov = 0;
	int posx1 = 0;
	int posx2 = 0;
for (int i = 0; i < 10; i++) {


	if (i < 5 && nav_ativa[i] == true) {
		glPushMatrix();
		glTranslatef((animanavinimiga + 100 + mov), 0, 0);
		desenhaNaveInimigo_NIVEL1();
		glPopMatrix();

		posx1 = (animanavinimiga + 100 + mov) + (-310)-5;
		navinimigoX1[i] = { posx1 };

		posx2 = (animanavinimiga + 100 + mov) + (-270)+5;
		navinimigoX2[i] = { posx2 };

		mov += 100;
	}
	else if (i>=5  && nav_ativa[i] == true){
		mov -= 100;
		glPushMatrix();
		glTranslatef(animanavinimiga + mov, 100, 0);
		desenhaNaveInimigo_NIVEL1();
		glPopMatrix();

		posx1 = (animanavinimiga + mov) + (-310) - 5;
		navinimigoX1[i] = { posx1 };

		posx2 = (animanavinimiga + mov) + (-270) + 5;
		navinimigoX2[i] = { posx2 };
		
	}
}
}
void desenhar()
{


	glLoadIdentity();
	glTranslatef((janela_largura) / 2, (janela_altura) / 2, 0);


	glColor3f(0, 0, 0); // cor ->Azul aço

	DesenhaTexto("Campus Videira -SC ", -300, 285, GLUT_BITMAP_HELVETICA_18);


	DesenhaTexto("JOHN VICTOR GOMES ", 130, 285, GLUT_BITMAP_HELVETICA_18);

	placar = 2;
	sprintf_s(plac, "%d", placar);

	DesenhaTexto("Placar: ", 180, 315, GLUT_BITMAP_HELVETICA_18);
	DesenhaTexto(plac, 260, 315, GLUT_BITMAP_HELVETICA_18);


	glPushMatrix();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0); // cor ->Azul aço
	glVertex2f(-350, 250);
	glVertex2f(350, 250);
	glVertex2f(350, -250);
	glVertex2f(-350, -250);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 1.0); // cor ->branco
	glVertex2f(-340, 240);
	glVertex2f(340, 240);
	glVertex2f(340, -240);
	glVertex2f(-340, -240);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0.27, 0.51, 0.71); // cor ->Azul aço
	glVertex2f(-340, 310);
	glVertex2f(340, 310);
	glEnd();

	glPopMatrix();
	LogoIF();

	glPushMatrix();
	//desenha nave

	glTranslatef(0, chao_y, 0);

	desenhaNavePlayer();
	glPopMatrix();


	ColocarNaves_NIVEL1();

	glColor3f(1, 0, 0);
	

	glBegin(GL_QUADS);
	glVertex2f((navinimigoX1[1]), 88);
	glVertex2f((navinimigoX1[1]), 82);
	glVertex2f((navinimigoX2[1]), 82);
	glVertex2f((navinimigoX2[1]), 88);
	glEnd();

	//desenhaMensagem("Game Over");
	
	if (atira == 1) {

		glPushMatrix();
		glTranslatef(0, chao_y, 0);

		desenhaTiro();
		glPopMatrix();
	}


	paredesExternas();


	glutPostRedisplay();

}
void desenhaTiro() {

	glLineWidth(4);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(tiro_x, 0.0 + tiro_y);
	glVertex2f(tiro_x, 15 + tiro_y );
	glEnd();

	for (int i = 0; i < 10; i++) {

		if (tiro_y >= 240) {
			//system("pause");
		}

		if (tiro_x+ != 0 && tiro_x+ <= navinimigoX1[i] && tiro_x >= navinimigoX1[i]) {
			
			
			color = 1;
		}

		printf("\n TIROy -> %2.f\n", tiro_y);
		printf("\n TIRO NA NAVE \n");

		printf("\n -------------- \n");

		printf("\n\n");
		printf("SE %2.f > %d  &&  %2.f < %d", tiro_x+ animanavinimiga, navinimigoX1[i], tiro_x+ animanavinimiga, navinimigoX2[i]);
		//nav_ativa[i] = { true };

	}
}

void desenhaNavePlayer() {
	glBegin(GL_QUADS);
	glColor3f(0, 0, 1); // cor ->Azul aço
	glVertex2f((-9 + MovNavPlayer_X), (9 ));
	glVertex2f((-9 + MovNavPlayer_X), (-9 ));
	glVertex2f((9 + MovNavPlayer_X), (-9 ));
	glVertex2f((9 + MovNavPlayer_X), (9 ));
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 1); // cor ->Azul aço
	glVertex2f((-15 + MovNavPlayer_X), (5 ));
	glVertex2f((-15 + MovNavPlayer_X), (-2 ));
	glVertex2f((16 + MovNavPlayer_X), (-2 ));
	glVertex2f((16 + MovNavPlayer_X), (5 ));
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 1); // cor ->Azul aço
	glVertex2f((-3 + MovNavPlayer_X), 9 );
	glVertex2f((-3 + MovNavPlayer_X), -52 );
	glVertex2f((3 + MovNavPlayer_X), -52 );
	glVertex2f((3 + MovNavPlayer_X), 9 );
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 1); // cor ->Azul aço
	glVertex2f((-10 + MovNavPlayer_X), -30 );
	glVertex2f((-10 + MovNavPlayer_X), -41 );
	glVertex2f((10 + MovNavPlayer_X), -41);
	glVertex2f((10 + MovNavPlayer_X), -30 );
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 1); // cor ->Azul aço
	glVertex2f((-20 + MovNavPlayer_X), (-46));
	glVertex2f((-20 + MovNavPlayer_X), (-41));
	glVertex2f((-10 + MovNavPlayer_X), (-41));
	glVertex2f((-10 + MovNavPlayer_X), (-46));
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 1); // cor ->Azul aço
	glVertex2f((20 + MovNavPlayer_X), (-46));
	glVertex2f((20 + MovNavPlayer_X), (-41));
	glVertex2f((10 + MovNavPlayer_X), (-41));
	glVertex2f((10 + MovNavPlayer_X), (-46));
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 1); // cor ->Azul aço
	glVertex2f((20 + MovNavPlayer_X), (-20));
	glVertex2f((20 + MovNavPlayer_X), (-60));
	glVertex2f((26 + MovNavPlayer_X), (-60));
	glVertex2f((26 + MovNavPlayer_X), (-20));
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 1); // cor ->Azul aço
	glVertex2f((-20 + MovNavPlayer_X), (-20 ));
	glVertex2f((-20 + MovNavPlayer_X), (-60 ));
	glVertex2f((-26 + MovNavPlayer_X), (-60 ));
	glVertex2f((-26 + MovNavPlayer_X), (-20 ));
	glEnd();



}



void DesenhaTexto(const char *string, int x, int y, void *fonte) {
	glPushMatrix();
	glRasterPos2f(x, y);
	while (*string) {
		glutBitmapCharacter(fonte, *string++);
	}
	glPopMatrix();
}
void display()
{
	glMatrixMode(GL_MODELVIEW); //coordenadas de desenho
	glLoadIdentity();
	if (color == 0){


		glClearColor(0.94f, 1.0f, 1.0f, 0.94f);
	}
	else {
		glClearColor(1.0f, 0.0f, 0.0f, 0.94f);

	}

	glClear(GL_COLOR_BUFFER_BIT); // EXECUTA LIMPESA
								  // Especificar o local aonde o desenho acontece: bem no centro da janela mais

								  //glTranslatef(janela_largura / 2, janela_altura/2, 0.0f);
	glViewport(0, 0, janela_largura, janela_altura);
	desenhar();

	glFlush(); // execute o desenho
}
void tela(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// cria a janela (esq, direita, embaixo, em cima)
	gluOrtho2D(0, janela_largura, 0, janela_altura);

	glMatrixMode(GL_MODELVIEW);

}

