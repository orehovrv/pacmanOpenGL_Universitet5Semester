#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glut.h>

#include "OBJMODEL.h"
#include "LOGICS.h"

void newPacDir(char);

OBJMODEL maze;
OBJMODEL pacman[13];

OBJMODEL ghost[5];
OBJMODEL money;
OBJMODEL cherry;

char * wayPacmanModel[13] = {"C:\\OBJ\\low\\pacman00.obj",
                             "C:\\OBJ\\low\\pacman01.obj",
                             "C:\\OBJ\\low\\pacman02.obj",
                             "C:\\OBJ\\low\\pacman03.obj",
                             "C:\\OBJ\\low\\pacman04.obj",
                             "C:\\OBJ\\low\\pacman05.obj",
                             "C:\\OBJ\\low\\pacman06.obj",
                             "C:\\OBJ\\low\\pacman07.obj",
                             "C:\\OBJ\\low\\pacman08.obj",
                             "C:\\OBJ\\low\\pacman09.obj",
                             "C:\\OBJ\\low\\pacman10.obj",
                             "C:\\OBJ\\low\\pacman11.obj",
                             "C:\\OBJ\\low\\pacman12.obj"};

LOGICS *logics = NULL;
char new_dir, flagOffset;
int i, j;
float angle = 0, newAngle, angleMoney = 0, offsetAngle = 45;
float pacX = 37.5, pacY = 37.5;

static void resize(int width, int height) {
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1, 1, 1, 3000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void display(void) {
    static float x, y, offsetX, offsetY;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1, 0, 0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    offsetX = sin(M_PI / 180 * angle) * 100;
    offsetY = cos(M_PI / 180 * angle) * 100;

    switch(flagOffset) {
        case 1: angle++; break;
        case 2: angle--; break;
    }

    if(angle == newAngle) flagOffset = 0;
    else if(angle >= 360) angle = 0;
    else if(angle < 0) angle = 360;

    pacX = logics->pacman.get_point().x + 0.5;
    pacY = logics->pacman.get_point().y + 0.5;

    glLoadIdentity();
    gluLookAt(pacX + offsetX, pacY + offsetY, 100, pacX, pacY, 37.5, 0, 0, 1);
    //gluLookAt(262.5, 0, 1100, 262.5, 312.5, 37.5, 0, 0, 1);

    glPushMatrix();
        glTranslatef(pacX, pacY, 37.5);

        switch(logics->pacman.get_dir()) {
            case 0:
                newAngle = 0 + offsetAngle;
                glRotated(270, 0, 0, 1);
                break;
            case 1:
                newAngle = 270 + offsetAngle;
                break;
            case 2:
                newAngle = 180 + offsetAngle;
                glRotated(90, 0, 0, 1);
                break;
            case 3:
                newAngle = 90 + offsetAngle;
                glRotated(180, 0, 0, 1);
                break;
        }

        pacman[logics->pacman.get_mouth()].draw();
    glPopMatrix();

    for(i = 0; i < 4; i++) {
        x = logics->enemy[i].get_point().x + 0.5;
        y = logics->enemy[i].get_point().y + 0.5;

        glPushMatrix();
            glTranslatef(x, y, 37.5);

            switch(logics->enemy[i].get_dir()) {
                case 0:
                    glRotated(270, 0, 0, 1);
                    break;
                case 1:
                    break;
                case 2:
                    glRotated(90, 0, 0, 1);
                    break;
                case 3:
                    glRotated(180, 0, 0, 1);
                    break;
            }

            if(logics->enemy[i].get_type()) ghost[i+1].draw();
            else ghost[0].draw();
        glPopMatrix();
    }

    angleMoney++;
    if(angleMoney >= 360) angleMoney = 0;

    for(float i = 0; i < logics->maze.get_size().x; i++)
        for(float j = 0; j < logics->maze.get_size().y; j++) {
            if(logics->maze.check_value(i, j) == 1) {
                glPushMatrix();
                    glTranslatef(j * 25 + 12.5, i * 25 + 12.5, 32.5);
                    glRotated(angleMoney, 0, 0, 1);
                    money.draw();
                glPopMatrix();
            }
            if(logics->maze.check_value(i, j) == 4) {
                glPushMatrix();
                    glTranslatef(j * 25 + 12.5, i * 25 + 12.5, 32.5);
                    cherry.draw();
                glPopMatrix();
            }
        }

    glPushMatrix();
        maze.draw();
    glPopMatrix();

    if(logics->pacman.center() && !logics->maze.check_wall(logics->pacman.get_point(), new_dir)) {
        switch(logics->pacman.get_dir()) {
            case 0:
                switch(new_dir) {
                    case 1: flagOffset = 2; break;
                    case 2: flagOffset = 1; break;
                    case 3: flagOffset = 1; break;
                }
                break;

            case 1:
                switch(new_dir) {
                    case 0: flagOffset = 1; break;
                    case 2: flagOffset = 2; break;
                    case 3: flagOffset = 1; break;
                }
                break;

            case 2:
                switch(new_dir) {
                    case 0: flagOffset = 1; break;
                    case 1: flagOffset = 1; break;
                    case 3: flagOffset = 2; break;
                }
                break;

            case 3:
                switch(new_dir) {
                    case 0: flagOffset = 2; break;
                    case 1: flagOffset = 1; break;
                    case 2: flagOffset = 1; break;
                }
                break;
        }
        logics->pacman.set_dir(new_dir);
    }

    logics->eat();
    logics->die_pacman();
    logics->step();

    if(logics->regim == 0) {
        printf("=====================================\n");
        printf("You dead\n");
        printf("Your score: %d\n", logics->pacman.get_score());
        printf("=====================================\n\n");

        if(logics) delete logics;
        logics = new LOGICS();
        logics->gen("C:\\OBJ\\level.bin");
        new_dir = logics->pacman.get_dir();

        switch(logics->pacman.get_dir()) {
            case 0:
                angle = 0 + offsetAngle;
                break;
            case 1:
                angle = 270 + offsetAngle;
                break;
            case 2:
                angle = 180 + offsetAngle;
                break;
            case 3:
                angle = 90 + offsetAngle;
                break;
        }

        flagOffset = 0;
    }

    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y) {
    switch (key) {
        case 27 :
        case 'q':
            printf("Press 'esc' or 'q' for end game\n");
            exit(0);
            break;

        case 'w': newPacDir('w'); break;
        case 'd': newPacDir('d'); break;
        case 's': newPacDir('s'); break;
        case 'a': newPacDir('a'); break;
    }

    glutPostRedisplay();
}

static void idle(void) {
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition((1920 - 800) / 2, (1080 - 600) / 2);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Orekhov Ruslan I596 Pacman");

    maze.load("C:\\OBJ\\maze.obj", 'm');

    for(i = 0; i < 13; i++)
        pacman[i].load(wayPacmanModel[i], 't');

    ghost[0].load("C:\\OBJ\\low\\ghost.obj", 'y');
    ghost[1].load("C:\\OBJ\\low\\ghost.obj", 'u');
    ghost[2].load("C:\\OBJ\\low\\ghost.obj", 'i');
    ghost[3].load("C:\\OBJ\\low\\ghost.obj", 'o');
    ghost[4].load("C:\\OBJ\\low\\ghost.obj", 'p');

    money.load("C:\\OBJ\\money.obj", 'n');
    cherry.load("C:\\OBJ\\cherry.obj", 'c');

    if(logics) delete logics;
    logics = new LOGICS();
    logics->gen("C:\\OBJ\\level.bin");
    new_dir = logics->pacman.get_dir();

    switch(logics->pacman.get_dir()) {
        case 0:
            angle = 0 + offsetAngle;
            break;
        case 1:
            angle = 270 + offsetAngle;
            break;
        case 2:
            angle = 180 + offsetAngle;
            break;
        case 3:
            angle = 90 + offsetAngle;
            break;
    }

    flagOffset = 0;

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(0.6, 0.851, 0.918, 0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    const GLfloat light_ambient[]  = {0.3f, 0.3f, 0.3f, 1.0f};
    const GLfloat light_position[] = {262.5, 337.5, 500.0f, 0.0f};

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glutMainLoop();

    return EXIT_SUCCESS;
}

void newPacDir(char dir) {
    switch(logics->pacman.get_dir()) {
        case 0:
            switch(dir) {
                case 'w': new_dir = 0; break;
                case 'd': new_dir = 3; break;
                case 's': new_dir = 2; break;
                case 'a': new_dir = 1; break;
            }
            break;

        case 1:
            switch(dir) {
                case 'w': new_dir = 1; break;
                case 'd': new_dir = 0; break;
                case 's': new_dir = 3; break;
                case 'a': new_dir = 2; break;
            }
            break;

        case 2:
            switch(dir) {
                case 'w': new_dir = 2; break;
                case 'd': new_dir = 1; break;
                case 's': new_dir = 0; break;
                case 'a': new_dir = 3; break;
            }
            break;

        case 3:
            switch(dir) {
                case 'w': new_dir = 3; break;
                case 'd': new_dir = 2; break;
                case 's': new_dir = 1; break;
                case 'a': new_dir = 0; break;
            }
            break;
    }
}
