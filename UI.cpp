#include "UI.h"
#include <functional>
#include <vector>

static double myRound (double val)
{

    if (val > 0)
    {
        return val + 0.5;
    }
    else
    {
        return val - 0.5;
    }

}


static double velocityCalc(double d1, double d2, double m1, double m2)
{

    double result;
    result = ((m1 - m2) * d1 + 2 * m2 * d2) / (m1 + m2);
    return result;

}

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
    glutInitWindowSize(1200, 800);

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

    bool bound1 = (x <= Consts::xMin);
    bool bound2 = (y >= Consts::yMin && y <= Consts::y1 && x >= Consts::x1 && x <= Consts::x2);
    bool bound3 = (y >= Consts::y2 && y <= Consts::yMax && x >= Consts::x1 && x <= Consts::x2);
    bool bound4 = (x >= Consts::xMax);

    return (bound1 || bound2 || bound3  || bound4);
   
}

bool UI::checkBoundY(int x, int y)
{
    //bool area1 = (x >= Consts::xMin && x < Consts::x1 && y > Consts::yMin && y < Consts::yMax);
    //bool area2 = (x >= Consts::x1 && x <= Consts::x2 && y > Consts::y1 && y < Consts::y2);
    //bool area3 = (x >= Consts::x2 && x < Consts::xMax && y > Consts::yMin && y < Consts::yMax);

    bool bound1 = (x >= Consts::xMin && x <= Consts::x1 && y >= Consts::yMax);
    bool bound2 = (x >= Consts::xMin && x <= Consts::x1 && y <= Consts::yMin);
    bool bound3 = (x >= Consts::x1 && x <= Consts::x2 && y >= Consts::y2);
    bool bound4 = (x >= Consts::x1 && x <= Consts::x2 && y <= Consts::y1);
    bool bound5 = (x >= Consts::x2 && x <= Consts::xMax && y >= Consts::yMax);
    bool bound6 = (x >= Consts::x2 && x <= Consts::xMax && y <= Consts::yMin);

    return (bound1 || bound2 || bound3 || bound4 || bound5 || bound6);

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

        
        //for (int i = 0; i < ; i++)
        for(auto it = particles->begin();it != particles->end();++it)
        {
            glColor3f(it->getColor().r/255, it->getColor().g/255, it->getColor().b/255);

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
            //it->update_xy();

            if (checkBoundX(it->getX() + it->getDx(), it->getY()))
            {
                it->setDx(it->getDx() * -1);
                
            }

            else if (checkBoundY(it->getX(), it->getY() + it->getDy()))
            {
                it->setDy(it->getDy() * -1);     
            }

            it->update_xy();
            

        }

        int dXnew1;
        int dYnew1;

        int dXnew2;
        int dYnew2;

        int test;

        for (auto it1 = particles->begin(); it1 != std::prev(particles->end()); ++it1)
        {

            for (auto it2 = std::next(it1); it2 != std::prev(particles->end()); ++it2)
            {
                if (it1->getX() == it2->getX() && it1->getY() == it2->getY()) 
                {
                  
                    dXnew1 = round( velocityCalc(it1->getDx(), it2->getDx(), it1->getWeight(), it2->getWeight() ));
                    dYnew1 = round( velocityCalc(it1->getDy(), it2->getDy(), it1->getWeight(), it2->getWeight() ));
                    dXnew2 = round( velocityCalc(it2->getDx(), it1->getDx(), it2->getWeight(), it1->getWeight() ));
                    dYnew2 = round( velocityCalc(it2->getDy(), it1->getDy(), it2->getWeight(), it1->getWeight() ));

                    if (dXnew1 == 0 || dYnew1 == 0 || dXnew2 == 0 || dYnew2 == 0)
                    {
                        test = 1;
                    }

                    it1->setDx(dXnew1);
                    it1->setDy(dYnew1);

                    it2->setDx(dXnew2);
                    it2->setDy(dYnew2);

                }
            }
        }

        glutPostRedisplay();
        glutTimerFunc(3, timerFunction, 1);

    };

    glutDisplayFunc(display);

    glutTimerFunc(3, timerFunction, 1);

    glutMainLoop();

}
