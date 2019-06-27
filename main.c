#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>


int ang=0, angulo=0, andar=0, gira=0, x=0, y=0;

void bicoFoguete(){
    glColor3f(0.0f,1.0f,0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-6.0f, 6.0f);
        glVertex2f( 0.0f,18.0f);
        glVertex2f( 6.0f, 6.0f);
    glEnd();    
}

void corpoFoguete(){
    glColor3f(0.0f,0.0f,1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-6.0f,  6.0f);
        glVertex2f( 6.0f,  6.0f);
        glVertex2f( 6.0f,-18.0f);
        glVertex2f(-6.0f,-18.0f);
    glEnd();
}

void asaEsquerdaFoguete(){
    glColor3f(1.0f,0.0f,0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f( -6.0f, -6.0f);
        glVertex2f( -6.0f,-18.0f);
        glVertex2f(-12.0f,-18.0f);
    glEnd();        
}

void asaDireitaFoguete(){
    glColor3f(1.0f,0.0f,0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f( 6.0f, -6.0f);
        glVertex2f( 6.0f,-18.0f);
        glVertex2f(12.0f,-18.0f);
    glEnd();   
}

void desenhaFoguete(){
    glPushMatrix();
        bicoFoguete();
        corpoFoguete();
        asaEsquerdaFoguete();
        asaDireitaFoguete();
    glEnd();
}

void Desenha(void){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    glTranslatef(x, y, 0.0f);
    glRotatef(gira, 0.0f, 0.0f, 1.0f);
    desenhaFoguete();
    glFlush();
}

void Inicializa(void){
    glClearColor(0.0f,0.0f,0.0f,1.0f);
}

void teclado(unsigned char tecla, int x, int y){
    switch(tecla){
        case 27:
            exit(0);
        case 'a':
            glutFullScreen();
            break;
        case 's':
            glutReshapeWindow(300,300);
            glutPositionWindow(100,100);
            break;
        case 13:
            if(andar) andar--; else andar++;
            break;
        default:;
    }
}

void teclasEspeciais(int tecla, int x, int y){
    switch(tecla){
            break;
        case GLUT_KEY_LEFT:
            ang=90;
            break;
        case GLUT_KEY_RIGHT:
            ang=270;
            break;
        case GLUT_KEY_UP:
            ang=0;
            break;
        case GLUT_KEY_DOWN:
            ang=180;
            break;
    }
}

void gerenciaBotaoMaouse(int button, int state, int x, int y){
    if(state == GLUT_DOWN){
        if(button == 0){
            switch(ang){
                case 0: ang=90; break;
                case 90: ang=180; break;
                case 180: ang=270; break;
                case 270: ang=0; break;
            }
        }            
        if(button == 2){
            switch(ang){
                case 0: ang=270; break;
                case 90: ang=0; break;
                case 180: ang=90; break;
                case 270: ang=180; break;
            }
        }
    }

}

void AlteraTamanhoJanela(GLsizei w, GLsizei h){
    if(h==0) h=1;

    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(w<=h)
        gluOrtho2D(-50.0f, 50.0f, -50.0f*h/w, 50.0f*h/w);
    else
        gluOrtho2D(-50.0f*w/h, 50.0f*w/h, -50.0f, 50.0f);
}

void timer(int value){
    if(ang==gira)
        if(andar){
            if(ang==0){if(y<50) y++;}
            if(ang==180){if(y>-50) y--;}
            if(ang==90){if(x>-50) x--;}
            if(ang==270){if(x<50) x++;}
        }

    if(ang>gira) gira++;
    if(ang<gira) gira--;

    glutPostRedisplay();   
    glutTimerFunc(33,timer,value);
}

void main(int argc, char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Foguete");
    Inicializa();
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(teclasEspeciais);
    glutMouseFunc(gerenciaBotaoMaouse);
    glutTimerFunc(33,timer,1);
    glutMainLoop();
}