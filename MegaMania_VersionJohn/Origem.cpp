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

float energy_x = 0.0;

// incremento em variaveis.
int flag = 0;
int flag1 = 0;
char plac[20];
int qtd_vidas = 0;
int qtdnavesRestantes = 10;
int color = 0;
int inicio_jogo = 0;
int animanavinimiga = 0;
int animameioNavInimiga = rand() % 2;
int  chao_y = -170;
int atira = 0;
int placar = 0;
int MovNavPlayer_X = 0;
int MovNavPlayer_Y = 0;
BOOLEAN gameover = false;
BOOLEAN energy_full = false;

float Tiro_XNavInimiga[10] = { 0 };
BOOLEAN nav_vida_ativa[5] = { true };
BOOLEAN nav_ativa[10] = { true };
int navinimigoX1[10] = { 0 };
int navinimigoX2[10] = { 0 };
int navinimigoY[10] = { 0 };
int TiroPlayerY = 0;
float rotacao = 1;
float xStep = 4;
float yStep = 8;
int ladodir = 0;
int Movball = rand() % 2;

int MovCPU = rand() % 2;


void DesenhaTexto(const char *string, int x, int y, void *fonte);
void input_callback(int key, int x, int y);
void Quadp();
void LogoIF();
void desenhaMensagem(char msg[20]);
void desenhaCampoVida();
void desenhaNaveVida(int valor);
void desenhaNaveInimigo_NIVEL1(int valor);
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






	if (tecla == ' ' && atira == 0)
	{
		atira = 1;
		tiro_x = MovNavPlayer_X;

		sndPlaySound(TEXT("Tiro.wav"), SND_ASYNC);
		
		printf("\n o valor de atira e %i\n", atira);



		printf("\n ESPACO\n", atira);

	}

	glutPostRedisplay();
}

void animacao(int valor) {

	
	if (energy_x < 450 && energy_full == false) {
		energy_x += 2;

	}
	if (energy_x == 8) {
		sndPlaySound(TEXT("EncheBarraVida.wav"), SND_ASYNC);
	}
	if (energy_x >= 450 && energy_full == false) {
		energy_x = 450;
		energy_full = true;
	
	}
	if (energy_full == true && energy_x >0) {
		energy_x -= 0.2;
	}
	if (energy_full == true && energy_x <=0) {
		energy_x = 0;
		qtd_vidas= qtd_vidas-1;
		printf("%d", qtd_vidas);
		
		energy_full = false;
	}
	if (qtd_vidas == 0 && energy_x == 0) {
		qtd_vidas = qtd_vidas - 1;
		
		
		
	}

	if (qtd_vidas == -2 && energy_x == 0 ) {
		gameover = true;

	}
	


	if (inicio_jogo == 0) {
		
		inicio_jogo = 1;
		qtd_vidas = 3;
		

		for (int i = 0; i < 10; i++) {
			
			nav_ativa[i] = { true };
			if (i < 3) {

				nav_vida_ativa[i] = { true };
			}
			else if (i >= 3 && i < 5) {
				nav_vida_ativa[i] = { false };
			}
		}
	}



	if (animanavinimiga >= 1000) {

		animanavinimiga = -670;
	}
	else {
		animanavinimiga += 3;
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

	if (flag > 0) {
		system("pause");
	}

	if (flag1 > 0) {
		system("pause");
	}


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
	sndPlaySound(TEXT("EncheBarraVida.wav"), SND_ASYNC);


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


void desenhaNaveInimigo_NIVEL1(int valor) {

	glPushMatrix();
	if (nav_ativa[valor] == false) {

		glColor3f(0, 0, 0);
	}
	else {

		glColor3f(1, 0, 1);
	}
	glTranslatef(-300, 115, 0);

	glBegin(GL_QUADS);
	glVertex2f((-10), 3);
	glVertex2f((-10), -3);
	glVertex2f((30), -3);
	glVertex2f((30), 3);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	if (nav_ativa[valor] == false) {

		glColor3f(0, 0, 0);
	}
	else {

		glColor3f(1, 0, 1);
	}
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
	if (nav_ativa[valor] == false) {

		glColor3f(0, 0, 0);
	}
	else {

		glColor3f(1, 0, 1);
	}
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
	if (nav_ativa[valor] == false) {

		glColor3f(0, 0, 0);
	}
	else {

		glColor3f(1, 0, 1);
	}
	glTranslatef(-300, 85, 0);

	glBegin(GL_QUADS);
	glVertex2f((-10), 3);
	glVertex2f((-10), -3);
	glVertex2f((30), -3);
	glVertex2f((30), 3);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	if (nav_ativa[valor] == false) {

		glColor3f(0, 0, 0);
	}
	else {

		glColor3f(1, 0, 1);
	}
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

void ColocarNaves_NIVEL1() {

	int mov = 0;
	int posx1 = 0;
	int posx2 = 0;
	int mediaX = 0;
	for (int i = 0; i < 10; i++) {


		if (i < 5) {
			glPushMatrix();
			glTranslatef((animanavinimiga + 100 + mov), 0, 0);
			desenhaNaveInimigo_NIVEL1(i);
			glPopMatrix();

			posx1 = (animanavinimiga + 100 + mov) + (-310) - 5;
			navinimigoX1[i] = { posx1 };

			posx2 = (animanavinimiga + 100 + mov) + (-270) + 5;
			navinimigoX2[i] = { posx2 };

			mediaX = navinimigoX1[i] + navinimigoX2[i] / 2;
			Tiro_XNavInimiga[i] = mediaX;

			mov += 100;
		}
		else if (i >= 5) {
			mov -= 100;
			glPushMatrix();
			glTranslatef(animanavinimiga + mov, 100, 0);
			desenhaNaveInimigo_NIVEL1(i);
			glPopMatrix();

			posx1 = (animanavinimiga + mov) + (-310) - 5;
			navinimigoX1[i] = { posx1 };

			posx2 = (animanavinimiga + mov) + (-270) + 5;
			navinimigoX2[i] = { posx2 };

		}
	}
}


void desenhaCampoVida() {

	glBegin(GL_QUADS);
	glColor3f(0.83, 0.83, 0.83); // cor ->Azul aço
	glVertex2f(-350, -370);
	glVertex2f(350, -370);
	glVertex2f(350, -260);
	glVertex2f(-350, -260);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(1, 0, 0); // cor ->Azul aço
	glVertex2f(-150, -300);
	glVertex2f(300, -300);
	glVertex2f(300, -280);
	glVertex2f(-150, -280);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(1, 1, 0); // cor ->Azul aço
	glVertex2f(-150, -300);
	glVertex2f(-150 + energy_x, -300);
	glVertex2f(-150 + energy_x, -280);
	glVertex2f(-150, -280);
	glEnd();
	glColor3f(1, 1, 0);
	DesenhaTexto("ENERGY", -250, -295, GLUT_BITMAP_HELVETICA_18);
	
	int mv=0;
	for (int i = 0; i < qtd_vidas; i++) {


			glPushMatrix();
			glTranslatef(-100 + mv, -330, 0);
			desenhaNaveVida(i);
			glPopMatrix();
		
			mv += 50;
	}
	
}
void desenhar()
{


	glLoadIdentity();
	glTranslatef((janela_largura) / 2, (janela_altura) / 2, 0);


	glColor3f(0, 0, 0); // cor ->Azul aço

	DesenhaTexto("Campus Videira -SC ", -300, 285, GLUT_BITMAP_HELVETICA_18);


	DesenhaTexto("John Victor, Kayc Prado ", 130, 285, GLUT_BITMAP_HELVETICA_18);


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


	glPushMatrix();
	//desenha nave

	glTranslatef(0, chao_y, 0);

	desenhaNavePlayer();
	glPopMatrix();

	if (gameover == true) {

		desenhaMensagem("Game over");
		flag++;
		
		
	}

	if (qtdnavesRestantes == 0) {

		
		desenhaMensagem("YOU WIN");
		flag1++;
	}
	else {

		ColocarNaves_NIVEL1();
	}


	if (atira == 1) {

		glPushMatrix();
		glTranslatef(0, chao_y, 0);

		desenhaTiro();

		
		glPopMatrix();

		
	}

	LogoIF();
	paredesExternas();

	desenhaCampoVida();
	glutPostRedisplay();

}
void desenhaTiroInimigo(int valor) {

	if (valor < 5) {
		glLineWidth(4);
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_LINES);
		glVertex2f(Tiro_XNavInimiga[valor], 0.0 + 240);
		glVertex2f(Tiro_XNavInimiga[valor], 15 + 240);
		glEnd();
	}
	else if (valor >= 5) {
		glLineWidth(4);
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_LINES);
		glVertex2f(Tiro_XNavInimiga[valor], 0.0 + 340);
		glVertex2f(Tiro_XNavInimiga[valor], 15 + 340);
		glEnd();
	}
	


}

void desenhaTiro() {

	glLineWidth(4);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(tiro_x, 0.0 + tiro_y);
	glVertex2f(tiro_x, 15 + tiro_y);
	glEnd();



	if (tiro_y >= 340) {
		//system("pause");
	}
	//1
	if ((nav_ativa[0] == true && tiro_x  > navinimigoX1[0] && tiro_x < navinimigoX2[0] && tiro_y >= 236 && tiro_y<400)) {

		nav_ativa[0] = false;
		placar += 1;
		tiro_y = 400;
		qtdnavesRestantes--;
		sndPlaySound(TEXT("MataInimigo.wav"), SND_ASYNC);
	}
	//2 
	else if ((nav_ativa[1] == true && tiro_x  > navinimigoX1[1] && tiro_x < navinimigoX2[1] && tiro_y >= 236 && tiro_y<400)) {

		nav_ativa[1] = false;
		placar += 1;
		tiro_y = 400;
		qtdnavesRestantes--;
		sndPlaySound(TEXT("MataInimigo.wav"), SND_ASYNC);
	}
	//3
	else if ((nav_ativa[2] == true && tiro_x  > navinimigoX1[2] && tiro_x < navinimigoX2[2] && tiro_y >= 236 && tiro_y<400)) {

		nav_ativa[2] = false;
		placar += 1;
		tiro_y = 400;
		qtdnavesRestantes--;
		sndPlaySound(TEXT("MataInimigo.wav"), SND_ASYNC);
	}
	//4
	else if ((nav_ativa[3] == true && tiro_x  > navinimigoX1[3] && tiro_x < navinimigoX2[3] && tiro_y >= 236 && tiro_y<400)) {

		nav_ativa[3] = false;
		placar += 1;
		tiro_y = 400;
		qtdnavesRestantes--;
		sndPlaySound(TEXT("MataInimigo.wav"), SND_ASYNC);
	}
	//5
	else if ((nav_ativa[4] == true && tiro_x  > navinimigoX1[4] && tiro_x < navinimigoX2[4] && tiro_y >= 340 && tiro_y<400)) {

		nav_ativa[4] = false;
		placar += 1;
		tiro_y = 400;
		qtdnavesRestantes--;
		sndPlaySound(TEXT("MataInimigo.wav"), SND_ASYNC);
	}
	//6
	else if ((nav_ativa[5] == true && tiro_x  > navinimigoX1[5] && tiro_x < navinimigoX2[5] && tiro_y >= 340 && tiro_y<400)) {

		nav_ativa[5] = false;
		placar += 1;
		tiro_y = 400;
		qtdnavesRestantes--;
		sndPlaySound(TEXT("MataInimigo.wav"), SND_ASYNC);
	}
	//7
	else if ((nav_ativa[6] == true && tiro_x  > navinimigoX1[6] && tiro_x < navinimigoX2[6] && tiro_y >= 340 && tiro_y<400)) {

		nav_ativa[6] = false;
		placar += 1;
		tiro_y = 400;
		qtdnavesRestantes--;
		sndPlaySound(TEXT("MataInimigo.wav"), SND_ASYNC);
	}
	//8
	else if ((nav_ativa[7] == true && tiro_x  > navinimigoX1[7] && tiro_x < navinimigoX2[7] && tiro_y >= 340 && tiro_y<400)) {

		nav_ativa[7] = false;
		placar += 1;
		tiro_y = 400;
		qtdnavesRestantes--;
		sndPlaySound(TEXT("MataInimigo.wav"), SND_ASYNC);
	}
	//9
	else if ((nav_ativa[8] == true && tiro_x  > navinimigoX1[8] && tiro_x < navinimigoX2[8] && tiro_y >= 340 && tiro_y<400)) {

		nav_ativa[8] = false;
		placar += 1;
		tiro_y = 400;
		qtdnavesRestantes--;
		sndPlaySound(TEXT("MataInimigo.wav"), SND_ASYNC);
	}
	//10
	else if ((nav_ativa[9] == true && tiro_x  > navinimigoX1[9] && tiro_x < navinimigoX2[9] && tiro_y >= 340 && tiro_y<400)) {

		nav_ativa[9] = false;
		placar += 1;
		tiro_y = 400;
		qtdnavesRestantes--;
		sndPlaySound(TEXT("MataInimigo.wav"), SND_ASYNC);
	}


}

void desenhaNaveVida(int valor) {

	glBegin(GL_QUADS);
	if (nav_vida_ativa[valor] == true) {
		glColor3f(0, 0, 1);
	}
	else {
		glColor3f(0.83, 0.83, 0.83);
	}
	 // cor ->Azul aço
	glVertex2f((4.5), (-4.5));
	glVertex2f((4.5), (4.5));
	glVertex2f((-4.5), (4.5));
	glVertex2f((-4.5), (-4.5));
	glEnd();

	glBegin(GL_QUADS);
	if (nav_vida_ativa[valor] == true) {
		glColor3f(0, 0, 1);
	}
	else {
		glColor3f(0.83, 0.83, 0.83);
	}
	glVertex2f((2.5 ), (-7));
	glVertex2f((-1 ), (-7));
	glVertex2f((-1 ), (8));
	glVertex2f((2.5), (8));
	glEnd();

	glBegin(GL_QUADS);
	if (nav_vida_ativa[valor] == true) {
		glColor3f(0, 0, 1);
	}
	else {
		glColor3f(0.83, 0.83, 0.83);
	}
	glVertex2f(4.5, -1.5);
	glVertex2f((-26), -1.5);
	glVertex2f((-26), 1.5);
	glVertex2f((4.5), 1.5);
	glEnd();

	glBegin(GL_QUADS);
	if (nav_vida_ativa[valor] == true) {
		glColor3f(0, 0, 1);
	}
	else {
		glColor3f(0.83, 0.83, 0.83);
	}
	glVertex2f((-15 ), -5);
	glVertex2f((-20.5), -5);
	glVertex2f(-20.5, 5);
	glVertex2f(-15, 5);
	glEnd();

	glBegin(GL_QUADS);
	if (nav_vida_ativa[valor] == true) {
		glColor3f(0, 0, 1);
	}
	else {
		glColor3f(0.83, 0.83, 0.83);
	}
	glVertex2f((-23 ), (-10));
	glVertex2f((-20.5 ), (-10));
	glVertex2f((-20.5), (-5));
	glVertex2f((-23 ), (-5));
	glEnd();

	glBegin(GL_QUADS);
	if (nav_vida_ativa[valor] == true) {
		glColor3f(0, 0, 1);
	}
	else {
		glColor3f(0.83, 0.83, 0.83);
	}
	glVertex2f((-23), (10));
	glVertex2f((-20.5), (10));
	glVertex2f((-20.5), (5));
	glVertex2f((-23), (5));
	glEnd();

	glBegin(GL_QUADS);
	if (nav_vida_ativa[valor] == true) {
		glColor3f(0, 0, 1);
	}
	else {
		glColor3f(0.83, 0.83, 0.83);
	}
	glVertex2f((-10 ), (10));
	glVertex2f((-30 ), (10));
	glVertex2f((-30 ), (13));
	glVertex2f((-10 ), (13));
	glEnd();

	glBegin(GL_QUADS);
	if (nav_vida_ativa[valor] == true) {
		glColor3f(0, 0, 1);
	}
	else {
		glColor3f(0.83, 0.83, 0.83);
	}
	glVertex2f((-10), (-10));
	glVertex2f((-30), (-10));
	glVertex2f((-30), (-13));
	glVertex2f((-10), (-13));
	glEnd();
}

void desenhaNavePlayer() {
	glBegin(GL_QUADS);
	glColor3f(0, 0, 1); // cor ->Azul aço
	glVertex2f((-9 + MovNavPlayer_X), (9));
	glVertex2f((-9 + MovNavPlayer_X), (-9));
	glVertex2f((9 + MovNavPlayer_X), (-9));
	glVertex2f((9 + MovNavPlayer_X), (9));
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 1); // cor ->Azul aço
	glVertex2f((-15 + MovNavPlayer_X), (5));
	glVertex2f((-15 + MovNavPlayer_X), (-2));
	glVertex2f((16 + MovNavPlayer_X), (-2));
	glVertex2f((16 + MovNavPlayer_X), (5));
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 1); // cor ->Azul aço
	glVertex2f((-3 + MovNavPlayer_X), 9);
	glVertex2f((-3 + MovNavPlayer_X), -52);
	glVertex2f((3 + MovNavPlayer_X), -52);
	glVertex2f((3 + MovNavPlayer_X), 9);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 1); // cor ->Azul aço
	glVertex2f((-10 + MovNavPlayer_X), -30);
	glVertex2f((-10 + MovNavPlayer_X), -41);
	glVertex2f((10 + MovNavPlayer_X), -41);
	glVertex2f((10 + MovNavPlayer_X), -30);
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
	glVertex2f((-20 + MovNavPlayer_X), (-20));
	glVertex2f((-20 + MovNavPlayer_X), (-60));
	glVertex2f((-26 + MovNavPlayer_X), (-60));
	glVertex2f((-26 + MovNavPlayer_X), (-20));
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
	if (color == 0) {


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