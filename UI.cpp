#include "UI.h"
#include <functional>
#include <vector>

UI::UI(std::vector<Particle>& parts)
{
    particles = &parts;

    area.push_back({Consts::xMin,Consts:: yMin});
    area.push_back({ Consts::xMin,Consts::yMax });
    area.push_back({ Consts::x1,Consts::yMax });
    area.push_back({ Consts::x1,Consts::y2 });
    area.push_back({ Consts::x2,Consts::y2 });
    area.push_back({ Consts::x2,Consts::yMax });
    area.push_back({ Consts::xMax,Consts::yMax });
    area.push_back({ Consts::xMax,Consts::yMin });
    area.push_back({ Consts::x2,Consts::yMin });
    area.push_back({ Consts::x2,Consts::y1 });
    area.push_back({ Consts::x1,Consts::y1 });
    area.push_back({ Consts::x1,Consts::yMin });
}

void UI::uiInit(int argc, char** argv)
{
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1920, 1080);

}

void UI::drawArea()
{

    for (int i = 0; i < area.size() - 1; i++) 
    {
        float x1 = (static_cast<float>(area[i].x) - Consts::xMax / 2) / (Consts::xMax / 2);
        float y1 = (static_cast<float>(area[i].y) - Consts::yMax / 2) / (Consts::yMax / 2);
        float x2 = (static_cast<float>(area[i + 1].x) - Consts::xMax / 2) / (Consts::xMax / 2);
        float y2 = (static_cast<float>(area[i + 1].y) - Consts::yMax / 2) / (Consts::yMax / 2);

        glBegin(GL_LINES);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
        glEnd();
    }

};

bool UI::checkBoundX(int x, int y)
{
    //bool area1 = (y >= Consts::yMin && y < Consts::y1) && ((x >= Consts::xMin && x < Consts::x1) || (x > Consts::x2 && x < Consts::xMax));
    //bool area2 = (y < Consts::y2 && y > Consts::y1 && x >= Consts::xMin && x <= Consts::xMax);
    //bool area3 = (y >= Consts::y1 && y < Consts::yMax) && ((x >= Consts::xMin && x < Consts::x1) || (x > Consts::x2 && x < Consts::xMax));

    bool bound1 = (x < Consts::xMin);
    bool bound2 = (x > Consts::x1 && x < Consts::x2 && y < Consts::y1);
    bool bound3 = (x < Consts::x2&& x > Consts::x1 && y < Consts::y1);
    bool bound4 = (x > Consts::xMax);
    bool bound5 = (x > Consts::x1 && x < Consts::x1&& y > Consts::y2);
    bool bound6 = (x < Consts::x2&& x > Consts::x1 && y > Consts::y2);
    return (bound1 || bound2 || bound3 || bound4 || bound5 || bound6);
   
}

bool UI::checkBoundY(int x, int y)
{
    //bool area1 = (x >= Consts::xMin && x < Consts::x1 && y > Consts::yMin && y < Consts::yMax);
    //bool area2 = (x >= Consts::x1 && x <= Consts::x2 && y > Consts::y1 && y < Consts::y2);
    //bool area3 = (x >= Consts::x2 && x < Consts::xMax && y > Consts::yMin && y < Consts::yMax);

    bool bound1 = (y < Consts::yMin);
    bool bound2 = (y > Consts::yMax);
    bool bound3 = (y == Consts::y1 && x > Consts::x1 && x < Consts::x2);
    bool bound4 = (y == Consts::y2 && x > Consts::x1 && x < Consts::x2);

    return (bound1 || bound2 || bound3 || bound4);

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
        
        drawArea();
        
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

            if (checkBoundX(it->getX(),it->getY()))
            {
                it->setDx(it->getDx() * -1);
                
            }

            if (checkBoundY(it->getX(), it->getY()))
            {
                it->setDy(it->getDy() * -1);     
            }

            

        }

        glutPostRedisplay();
        glutTimerFunc(3, timerFunction, 1);

    };

    glutDisplayFunc(display);

    glutTimerFunc(3, timerFunction, 1);

    glutMainLoop();

}
