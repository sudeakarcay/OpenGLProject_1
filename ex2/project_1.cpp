/*********
   CTIS164 - Homework 1
----------
STUDENT : Sude Akarcay
SECTION : 004
HOMEWORK: 1
----------
PROBLEMS:
----------
ADDITIONAL FEATURES:

 1.The user can change the background type. The program starts with the day mode. However, when the user press n or N keys, the mode changes and night mode is displayed.
 2.There are two clouds and their speed are different from each other. Besides, the user can change the speed of the clouds (increase/decrease).
 3.Clouds have a speciality. While they are moving, their colors change.
 4.The user can stop or start the movement of the ship by pressing space bar when the mode is auto.
 5.The user can control the size of the sun (enlarge / shrink ).
 6. Day mode's and night mode's backgrounds and designs are different. Besides, The sun starts to rise when the user opens the program for the first time,
 and the moon starts to rise when the night mode is switched on, but only when it is first opened.

  **********/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 600

#define TIMER_PERIOD  16 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

  //to activate auto mode
  // to activate manuel mode by pressing F1

 /* Global Variables for Template File */
bool up = false, down = false, right = false, left = false, daymod = true, mode = true;
int  winWidth, winHeight, click = 0, xship, yship, xcloud1, ycloud1, xcloud2, ycloud2, cloud1status = 1, cloud2status = 1, ysmoke, sunmove = 140, sunstatus = 1, moonstatus = 1, moonmove,
way, speedOfClouds = 0, radiusOfsun;

// current Window width and height
bool ship1 = false;
bool timer = true;

#define START 0
int xpos = -1;
int r, g, b;
int appstate = START;
bool inStartButton = false;

//
// to draw circle, center at (x,y)
// radius r
//
void circle(int x, int y, int r)
{
#define PI 3.1415
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
    float angle;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void print(int x, int y, const char* string, void* font)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void* font, const char* string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}




//
// To display onto window using OpenGL commands
//



void sky() {



    glColor3ub(135, 206, 250);
    glBegin(GL_QUADS);
    glVertex2f(-500, 50);
    glVertex2f(-500, 300);
    glVertex2f(500, 300);
    glVertex2f(500, 50);
    glEnd();



    glColor3ub(160, 82, 45);

    glBegin(GL_TRIANGLES);
    glVertex2f(-500, 50);
    glVertex2f(-380, 150);
    glVertex2f(-250, 50);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(-300, 50);
    glVertex2f(-130, 130);
    glVertex2f(100, 50);
    glEnd();



    glBegin(GL_TRIANGLES);
    glVertex2f(-30, 50);
    glVertex2f(160, 160);
    glVertex2f(390, 50);
    glEnd();




    glBegin(GL_TRIANGLES);
    glVertex2f(300, 50);
    glVertex2f(380, 100);
    glVertex2f(500, 50);
    glEnd();





}

void sea()
{




    glColor3ub(0, 191, 255);
    glBegin(GL_QUADS);
    glVertex2f(-500, 50);
    glVertex2f(-500, -300);
    glVertex2f(500, -300);
    glVertex2f(500, 50);
    glEnd();



}

void sun()

{

    glColor3f(1, 1, 0);
    circle(0, sunmove - 30, radiusOfsun + 50);

}


void cloud1()
{
    glColor3ub(xcloud1 + 191, xcloud1 + 62, xcloud1 + 255);
    circle(xcloud1 - 450, 200, 30);
    circle(xcloud1 - 400, 220, 40);
    circle(xcloud1 - 400, 200, 40);
    circle(xcloud1 - 350, 200, 30);
    //smile face on cloud
    glColor3f(0, 0, 0);
    circle(xcloud1 - 420, 230, 5);
    circle(xcloud1 - 380, 230, 5);
    glColor3ub(xcloud1 + 250, xcloud1 + 128, 114);
    circle(xcloud1 - 440, 210, 8);
    circle(xcloud1 - 360, 210, 8);




}

void cloud2()
{

    glColor3ub(xcloud2 + 255, xcloud2 + 20, xcloud2 + 147);
    circle(xcloud2 + 450, 180, 30);
    circle(xcloud2 + 400, 200, 40);
    circle(xcloud2 + 400, 180, 40);
    circle(xcloud2 + 350, 180, 30);
    //smile face on cloud
    glColor3f(0, 0, 0);
    circle(xcloud2 + 420, 210, 5);
    circle(xcloud2 + 380, 210, 5);
    glColor3ub(xcloud2 + 250, xcloud2 + 128, 114);
    circle(xcloud2 + 440, 190, 8);
    circle(xcloud2 + 360, 190, 8);
}


void ship()
{

    //body part of ship

    glColor3ub(205, 55, 0);
    glBegin(GL_POLYGON);
    glVertex2f(xship - 230, yship - 100);
    glColor3ub(255, 99, 71);
    glVertex2f(xship - 270, yship - 10);
    glColor3ub(255, 160, 122);
    glVertex2f(xship + 270, yship - 10);
    glColor3ub(255, 127, 0);
    glVertex2f(xship + 230, yship - 100);
    glEnd();

    //bottom of ship

    glColor3ub(238, 154, 0);
    glBegin(GL_POLYGON);
    glVertex2f(xship - 230, yship - 100);
    glVertex2f(xship - 245, yship - 70);
    glVertex2f(xship + 245, yship - 70);
    glVertex2f(xship + 230, yship - 100);
    glEnd();

    // body window

    glColor3ub(242, 242, 242);
    glBegin(GL_QUADS);
    glVertex2f(xship - 160, yship - 20);
    glVertex2f(xship - 160, yship - 60);
    glVertex2f(xship - 120, yship - 60);
    glVertex2f(xship - 120, yship - 20);
    glEnd();


    glBegin(GL_QUADS);
    glVertex2f(xship - 20, yship - 20);
    glVertex2f(xship - 20, yship - 60);
    glVertex2f(xship + 20, yship - 60);
    glVertex2f(xship + 20, yship - 20);
    glEnd();


    glBegin(GL_QUADS);
    glVertex2f(xship + 120, yship - 20);
    glVertex2f(xship + 120, yship - 60);
    glVertex2f(xship + 160, yship - 60);
    glVertex2f(xship + 160, yship - 20);
    glEnd();

    //middle part



    glColor3ub(255, 69, 0);
    glBegin(GL_QUADS);
    glVertex2f(xship - 270, yship - 10);
    glVertex2f(xship - 270, yship + 10);
    glVertex2f(xship + 270, yship + 10);
    glVertex2f(xship + 270, yship - 10);
    glEnd();





    glColor3ub(255, 106, 106);
    glBegin(GL_QUADS);
    glVertex2f(xship - 230, yship + 50);
    glVertex2f(xship - 230, yship + 10);
    glVertex2f(xship + 230, yship + 10);
    glVertex2f(xship + 230, yship + 50);
    glColor3ub(0, 0, 128);




    //chimney1

    glVertex2f(xship - 160, yship + 50);
    glVertex2f(xship - 160, yship + 150);
    glVertex2f(xship - 100, yship + 150);
    glVertex2f(xship - 100, yship + 50);

    //chimney2

    glVertex2f(xship - 30, yship + 50);
    glVertex2f(xship - 30, yship + 150);
    glVertex2f(xship + 30, yship + 150);
    glVertex2f(xship + 30, yship + 50);

    //chimney3

    glVertex2f(xship + 100, yship + 50);
    glVertex2f(xship + 100, yship + 150);
    glVertex2f(xship + 160, yship + 150);
    glVertex2f(xship + 160, yship + 50);
    glEnd();

    //smoke1

    glLineWidth(3);
    glColor3ub(99, 99, 99);
    glBegin(GL_LINES);
    glVertex2f(xship - 140, yship + 160);
    glVertex2f(xship - 140, yship + 190);

    glVertex2f(xship - 130, yship + 180);
    glVertex2f(xship - 130, yship + 210);

    glVertex2f(xship - 120, yship + 160);
    glVertex2f(xship - 120, yship + 190);

    //smoke2

    glVertex2f(xship - 10, yship + 160);
    glVertex2f(xship - 10, yship + 190);

    glVertex2f(xship + 0, yship + 180);
    glVertex2f(xship + 0, yship + 210);

    glVertex2f(xship + 10, yship + 160);
    glVertex2f(xship + 10, yship + 190);


    //smoke3

    glVertex2f(xship + 120, yship + 160);
    glVertex2f(xship + 120, yship + 190);

    glVertex2f(xship + 130, yship + 180);
    glVertex2f(xship + 130, yship + 210);

    glVertex2f(xship + 140, yship + 160);
    glVertex2f(xship + 140, yship + 190);


    glEnd();

    glColor3ub(104, 34, 139);
    glBegin(GL_POLYGON);
    glVertex2f(xship - 215, yship + 50);
    glVertex2f(xship + 215, yship + 50);
    glVertex2f(xship + 200, yship + 90);
    glVertex2f(xship - 215, yship + 90);
    glEnd();

    //window

    glColor3ub(242, 242, 242);
    glBegin(GL_POLYGON);
    glVertex2f(xship + 150, yship + 60);
    glVertex2f(xship + 210, yship + 60);
    glVertex2f(xship + 204, yship + 80);
    glVertex2f(xship + 150, yship + 80);
    glEnd();

    //middle window

    glColor3ub(242, 242, 242);
    circle(xship - 140, yship + 30, 20);
    circle(xship + 0, yship + 30, 20);
    circle(xship + 140, yship + 30, 20);


}


void moon()
{

    glColor3f(1, 1, 1);
    circle(400, moonmove - 60, 80);
    glColor3f(0, 0, 0);
    circle(370, moonmove - 30, 4);
    circle(430, moonmove - 30, 4);

    glBegin(GL_LINES);
    glVertex2f(350, moonmove - 70);
    glVertex2f(450, moonmove - 70);
    glEnd();

}

void star()
{

    glColor3ub(255, 215, 0);
    glBegin(GL_POLYGON);

    glVertex2d(140, 170);
    glVertex2d(180, 180);
    glVertex2d(140, 190);
    glVertex2d(130, 230);
    glVertex2d(120, 190);
    glVertex2d(80, 180);
    glVertex2d(120, 170);
    glVertex2d(130, 130);
    glEnd();


    glColor3ub(205, 92, 92);
    glBegin(GL_POLYGON);
    glVertex2d(-140, 170);
    glVertex2d(-180, 180);
    glVertex2d(-140, 190);
    glVertex2d(-130, 230);
    glVertex2d(-120, 190);
    glVertex2d(-80, 180);
    glVertex2d(-120, 170);
    glVertex2d(-130, 130);
    glEnd();

    glColor3ub(240, 128, 128);
    glBegin(GL_POLYGON);
    glVertex2d(-420, 170);
    glVertex2d(-460, 180);
    glVertex2d(-420, 190);
    glVertex2d(-410, 230);
    glVertex2d(-400, 190);
    glVertex2d(-360, 180);
    glVertex2d(-400, 170);
    glVertex2d(-410, 130);
    glEnd();

    glColor3ub(255, 20, 147);
    glBegin(GL_POLYGON);
    glVertex2d(-280, 220);
    glVertex2d(-320, 230);
    glVertex2d(-280, 240);
    glVertex2d(-270, 280);
    glVertex2d(-260, 240);
    glVertex2d(-220, 230);
    glVertex2d(-260, 220);
    glVertex2d(-270, 180);
    glEnd();


    glColor3ub(16, 78, 139);
    glBegin(GL_POLYGON);
    glVertex2d(-280, 100);
    glVertex2d(-320, 110);
    glVertex2d(-280, 120);
    glVertex2d(-270, 160);
    glVertex2d(-260, 120);
    glVertex2d(-220, 110);
    glVertex2d(-260, 100);
    glVertex2d(-270, 60);
    glEnd();


    glColor3ub(187, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2d(280, 220);
    glVertex2d(320, 230);
    glVertex2d(280, 240);
    glVertex2d(270, 280);
    glVertex2d(260, 240);
    glVertex2d(220, 230);
    glVertex2d(260, 220);
    glVertex2d(270, 180);
    glEnd();

    glColor3ub(127, 255, 212);
    glBegin(GL_POLYGON);
    glVertex2d(280, 100);
    glVertex2d(320, 110);
    glVertex2d(280, 120);
    glVertex2d(270, 160);
    glVertex2d(260, 120);
    glVertex2d(220, 110);
    glVertex2d(260, 100);
    glVertex2d(270, 60);
    glEnd();


    glColor3ub(202, 255, 112);
    glBegin(GL_POLYGON);
    glVertex2d(0, 220);
    glVertex2d(-40, 230);
    glVertex2d(0, 240);
    glVertex2d(10, 280);
    glVertex2d(20, 240);
    glVertex2d(60, 230);
    glVertex2d(20, 220);
    glVertex2d(10, 180);
    glEnd();


    glColor3ub(138, 43, 226);
    glBegin(GL_POLYGON);
    glVertex2d(0, 100);
    glVertex2d(-40, 110);
    glVertex2d(0, 120);
    glVertex2d(10, 160);
    glVertex2d(20, 120);
    glVertex2d(60, 110);
    glVertex2d(20, 100);
    glVertex2d(10, 60);
    glEnd();


}



void display() {
    //
    // clear window to black
    //
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);





    if (daymod == true) {

        //call the functions which is displayed on the day mode 


        sea();
        sky();
        sun();
        cloud1();
        cloud2();



        glColor3f(0, 0, 0); //black
        vprint(-480, 280, GLUT_BITMAP_8_BY_13, "NIGHT MOD IS OFF");  //to show which mode is on
        glColor3ub(255, 48, 48);
        vprint(400, 280, GLUT_BITMAP_8_BY_13, "SUDE AKARCAY");
       

        glColor3f(0, 0, 0);

        switch (way)

        {
        case 0:

            vprint(-480, 240, GLUT_BITMAP_8_BY_13, "DIRECTION: Not Set");

            break;

        case 1:

            vprint(-480, 240, GLUT_BITMAP_8_BY_13, "DIRECTION: Up");
            break;

        case 2:

            vprint(-480, 240, GLUT_BITMAP_8_BY_13, "DIRECTION: Down");
            break;
        case 3:

            vprint(-480, 240, GLUT_BITMAP_8_BY_13, "DIRECTION: Left");

            break;

        case 4:

            vprint(-480, 240, GLUT_BITMAP_8_BY_13, "DIRECTION: Right");

            break;


        }



        if (click == 0)
        {

            glColor3f(1, 0, 0);
            vprint((winWidth / 2) - 650, -30, GLUT_BITMAP_8_BY_13, "< CLICK TO SEE THE COOLEST SHIP EVER >");


        }


        if (click > 0)  // when the user click on the screen it will display the ship

        {

            if (mode == true)
            {
                glColor3f(0, 0, 0);  //black
                vprint(-480, 260, GLUT_BITMAP_8_BY_13, "MANUAL MODE IS ON");  //to show which mode is on

            }

            else
            {
                glColor3f(0, 0, 0); //black
                vprint(-480, 260, GLUT_BITMAP_8_BY_13, "AUTO MODE IS ON");  //to show which mode is on
            }


            ship();

        }



        glColor3f(0, 0, 0);  //black

        vprint((winWidth / 2) - 430, -(winHeight / 2) + 35, GLUT_BITMAP_8_BY_13, "e,E / s,S : enlarge / shrink the sun");
        vprint((winWidth / 2) - 430, -(winHeight / 2) + 20, GLUT_BITMAP_8_BY_13, "Space bar : stop / start the ship");
        vprint((winWidth / 2) - 430, -(winHeight / 2) + 50, GLUT_BITMAP_8_BY_13, "n,N : display night mode / back to day mode");
        vprint((winWidth / 2) - 430, -(winHeight / 2) + 65, GLUT_BITMAP_8_BY_13, "F1: switch mode (manual/auto)");
        vprint((winWidth / 2) - 430, -(winHeight / 2) + 80, GLUT_BITMAP_8_BY_13, "Arrow keys: to control the ship");
        vprint((winWidth / 2) - 430, -(winHeight / 2) + 5, GLUT_BITMAP_8_BY_13, "y,Y/m,M : press to increase/decrease speed of clouds");



    }


    if (daymod == false) {


        //call the functions which is displayed on the night mode


        glColor3f(0, 0, 0);
        glBegin(GL_QUADS);
        glVertex2f(-500, -10);
        glVertex2f(-500, 300);
        glVertex2f(500, 300);
        glVertex2f(500, -10);
        glEnd();
        moon();
        star();



        glColor3f(1, 1, 1);

        vprint(-480, 280, GLUT_BITMAP_8_BY_13, "NIGHT MOD IS ON");  // to show which mode is on

        switch (way)

        {
        case 0:

            vprint(-480, 240, GLUT_BITMAP_8_BY_13, "DIRECTION: Not Set");

            break;

        case 1:

            vprint(-480, 240, GLUT_BITMAP_8_BY_13, "DIRECTION: Up");
            break;

        case 2:

            vprint(-480, 240, GLUT_BITMAP_8_BY_13, "DIRECTION: Down");
            break;
        case 3:

            vprint(-480, 240, GLUT_BITMAP_8_BY_13, "DIRECTION: Left");

            break;

        case 4:

            vprint(-480, 240, GLUT_BITMAP_8_BY_13, "DIRECTION: Right");

            break;


        }


        glColor3ub(39, 64, 139);

        glBegin(GL_QUADS);
        glVertex2f(-500, 50);
        glVertex2f(-500, -300);
        glVertex2f(500, -300);
        glVertex2f(500, 50);
        glEnd();


        if (click >= 1)

        {

            if (mode == true)

            {
                glColor3f(1, 1, 1);  //white
                vprint(-480, 260, GLUT_BITMAP_8_BY_13, "MANUAL MODE IS ON");  // to show which mode is on

            }

            else

            {
                glColor3f(1, 1, 1);   //white
                vprint(-480, 260, GLUT_BITMAP_8_BY_13, "AUTO MODE IS ON");  // to show which mode is on
            }

            ship();

        }




        // show the directive to the user

        glColor3f(1, 1, 1);  //white

        vprint((winWidth / 2) - 430, -(winHeight / 2) + 35, GLUT_BITMAP_8_BY_13, "e,E / s,S : enlarge / shrink the cloud");
        vprint((winWidth / 2) - 430, -(winHeight / 2) + 20, GLUT_BITMAP_8_BY_13, "Space bar : stop / start the ship");
        vprint((winWidth / 2) - 430, -(winHeight / 2) + 50, GLUT_BITMAP_8_BY_13, "n,N : display night mode / back to day mode");
        vprint((winWidth / 2) - 430, -(winHeight / 2) + 65, GLUT_BITMAP_8_BY_13, "F1 : switch mode (manual/auto)");
        vprint((winWidth / 2) - 430, -(winHeight / 2) + 80, GLUT_BITMAP_8_BY_13, "Arrow keys: to control the ship");
        vprint((winWidth / 2) - 430, -(winHeight / 2) + 5, GLUT_BITMAP_8_BY_13, "y,Y / m,M : increase/decrase the speed of clouds ");

    }



    glutSwapBuffers();
}

void update(int value) {

    glutPostRedisplay();

    glutTimerFunc(25, update, 0);

}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    if (key == 'n' || key == 'N')
    {

        daymod = !daymod;

    }


    if (key == ' ') {   // to start or stop the ship

        timer = !timer;


    }


    if (key == 'e' || key == 'E')
    {
        if (radiusOfsun <= winHeight / 25)
        {

            radiusOfsun += 1;

        }

    }

    if (key == 's' || key == 'S')
    {

        if (radiusOfsun >= winHeight / 100)
        {
            radiusOfsun -= 1;
        }


    }



    if (key == 'y' || key == 'Y')  // to increase the speed of the ship

    {
        speedOfClouds = 1;

    }

    if (key == 'm' || key == 'M')  //to  decrease the speed of the ship

    {

        speedOfClouds = 0;

    }


    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{


    switch (key) {

    case GLUT_KEY_UP: up = true;

        way = 1;

        if (yship + 300 < winHeight / 2)

            yship += 3;
        break;

    case GLUT_KEY_DOWN: down = true;

        way = 2;

        if (yship - 100 > -(winHeight / 2))

            yship -= 3;

        break;

    case GLUT_KEY_LEFT: left = true;

        way = 3;

        if (xship - 270 > (-winWidth / 2))

            xship -= 3;

        break;

    case GLUT_KEY_RIGHT: right = true;

        way = 4;

        if (xship + 270 < winWidth / 2)

            xship += 3;

        break;

    case GLUT_KEY_F1:

        mode = !mode;

        break;

    }





    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{

    switch (key)
    {

    case GLUT_KEY_UP: up = false; break;
    case GLUT_KEY_DOWN: down = false; break;
    case GLUT_KEY_LEFT: left = false; break;
    case GLUT_KEY_RIGHT: right = false; break;

    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick(int button, int stat, int x, int y)
{


    if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN) {

        click++;



        xship = (x - winWidth / 2);  // GLUT to OpenGL coordinate conversion



        yship = winHeight / 2 - y;

    }





    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // refresh window.
}

void onMoveDown(int x, int y) {
    // Write your codes here.


    // to refresh the window it calls display() function   
    glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function
    glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {

    glutTimerFunc(TIMER_PERIOD, onTimer, 0);

    if (mode == false && timer) {  // timer function is used to start or stop the ship and mode function is used to change mode (manual / auto)

        switch (way)

        {
        case 0:

            break;

        case 1:

            if (yship + 300 < winHeight / 2)

                yship += 3;
            else

                way = 2;

            break;

        case 2:

            if (yship - 100 > -(winHeight / 2))

                yship -= 3;

            else

                way = 1;

            break;

        case 3:

            if (xship - 270 > -(winWidth / 2))

                xship -= 3;

            else

                way = 4;

            break;

        case 4:

            if (xship + 270 < winWidth / 2)

                xship += 3;

            else

                way = 3;

            break;

        }
    }


    //cloud movement 

    if (cloud1status == 1)

        xcloud1 += 2;



    if (xcloud1 > 1000)

        xcloud1 -= 1000;


    if (cloud2status == 1)

        xcloud2 -= 3;


    if (xcloud2 < -1000)

        xcloud2 -= -1000;


    // sun movement

    if (sunstatus == 1 && sunmove <= winHeight / 2 - 60) {

        sunmove += 1;
    }


    // moon movement

    if (daymod == false) {

        if (moonstatus == 1 && moonmove <= winHeight / 2 - 60) {

            moonmove += 1;

        }

    }

    if (speedOfClouds == 1)

    {

        xcloud1 += 6;
        xcloud2 -= 7;

    }

    if (speedOfClouds == 0)

    {

        xcloud1 += 2;
        xcloud2 -= 3;

    }



    // to refresh the window it calls display() function
    glutPostRedisplay(); // display()

}
#endif

void Init() {

    // Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    //glutInitWindowPosition(100, 100);
    glutCreateWindow("Homework 1: The Ship at Sea");

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);

    //
    // keyboard registration
    //
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);

    //
    // mouse registration
    //
    glutMouseFunc(onClick);
    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);

    glutTimerFunc(25, update, 0);
#if  TIMER_ON == 1
    // timer event
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

    Init();

    glutMainLoop();
}