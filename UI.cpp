#include "UI.h"
#include <functional>
void UI::uiInit(int argc, char** argv)
{
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1920, 1080);

}

 static void timerFunction(int value)
{
    
    glutPostRedisplay();  
    glutTimerFunc(3,timerFunction, 1);  

}

 static void display1()
{

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(10);


    glBegin(GL_POINTS);

    glColor3f(0, 0, 0);
    //for (int i = 0; i < ; i++)
    //for(auto elm : particles)
    //{


    //    glVertex2f(-0.99, 0.99);

    //}
   
    glEnd();

    glutSwapBuffers();

}


 /*
 static std::function<void(int)> timer_bounce;
 auto timer = [](int ms) {
     timer_bounce(ms);
 };
 timer_bounce = [&](int ms) {
     glutTimerFunc(ms, timer, ms);
     glutPostRedisplay();
 };
 glutTimerFunc(33, timer, 33);
 */

void UI::uiShow()
{

    glutCreateWindow("Проба");

    static std::function<void()> display_bounce;
    static std::function<void()> timer_bounce;

    auto display = []() {
        display_bounce();
    };

    auto timerFunction = [](int value) {
        timer_bounce();
    };

    display_bounce = [&]() {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPointSize(10);


        glBegin(GL_POINTS);

        glColor3f(0, 0, 0);
        //for (int i = 0; i < ; i++)
        for(auto it = particles->begin();it != particles->end();++it)
        {

            float x = (static_cast<float>(it->getX()) - Consts::xMax / 2) / (Consts::xMax / 2);
            float y = (static_cast<float>(it->getY()) - Consts::yMax / 2) / (Consts::yMax / 2);
            glVertex2f(x,y);

        }

        glEnd();

        glutSwapBuffers();

    };

    timer_bounce = [&]() {

        for (auto it = particles->begin(); it != particles->end(); ++it)
        {
            it->update_xy();

        }

        glutPostRedisplay();
        glutTimerFunc(3, timerFunction, 1);
    };

    glutDisplayFunc(display);

    glutTimerFunc(3, timerFunction, 1);

    glutMainLoop();

}
