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

static bool inRange(double C1, double C2,double range)
{
    return(C1 < C2 + range) && (C1 > C2 - range);
}

UI::UI(std::vector<Particle<double>>& parts, TextOutput& text)
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

    m_text = &text;
    


}

void UI::uiInit(int argc, char** argv)
{
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(Consts::WinWidth, Consts::WinHeight);

}

void UI::drawArea()
{

    glutReshapeWindow(Consts::WinWidth, Consts::WinHeight);

    for (int i = 0; i < area.size() - 1; i++) 
    {
        float x1 = (static_cast<float>(area[i].x) - Consts::xMax / 2) / (Consts::xMax / 2);
        float y1 = (static_cast<float>(area[i].y) - Consts::yMax / 2) / (Consts::yMax / 2);
        float x2 = (static_cast<float>(area[i + 1].x) - Consts::xMax / 2) / (Consts::xMax / 2);
        float y2 = (static_cast<float>(area[i + 1].y) - Consts::yMax / 2) / (Consts::yMax / 2);

        glBegin(GL_LINES);
        glColor3f(255, 0, 0);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
        glEnd();
    }

};



//GLUT_BITMAP_8_BY_13
//GLUT_BITMAP_9_BY_15
//GLUT_BITMAP_TIMES_ROMAN_10
//GLUT_BITMAP_TIMES_ROMAN_24
//GLUT_BITMAP_HELVETICA_10
//GLUT_BITMAP_HELVETICA_12
//GLUT_BITMAP_HELVETICA_18


void renderBitmapString(float x, float y, void* font, char* string)
{
    char* c;
    glColor3f(255, 0, 0);
    glRasterPos2f(x, y);
    
    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}



void UI::drawText()
{
   
    m_text->text[1].m_str = std::to_string(static_cast<int>(MiscFunc::SearchMaxV(particles) * 1000));
    m_text->text[3].m_str = std::to_string(static_cast<int>(MiscFunc::SearchMinV(particles) * 1000));
    m_text->text[5].m_str = std::to_string(static_cast<int>(MiscFunc::SearchAvgV(particles) * 1000));
    MiscFunc::histogram(particles);
    for (auto& elm : m_text->text)
    {

        renderBitmapString(elm.m_x, elm.m_y, GLUT_BITMAP_TIMES_ROMAN_24, const_cast<char*>(elm.m_str.c_str())); 
       
    }


    

}



bool UI::checkBoundX(double x, double y)
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

bool UI::checkBoundY(double x, double y)
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

    glutCreateWindow("Модель движения частиц газа");

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
        drawText();

        glPointSize(10);


        glBegin(GL_POINTS);

        
        //for (int i = 0; i < ; i++)
        for  (auto it = particles->begin();it != particles->end();++it)
        {
            glColor3f(it->getColor().r/255, it->getColor().g/255, it->getColor().b/255);

            float x = (static_cast<float>(it->getX()) - Consts::xMax / 2) / (Consts::xMax / 2);
            float y = (static_cast<float>(it->getY()) - Consts::yMax / 2) / (Consts::yMax / 2);
            glVertex2f(x,y);

        }

        glEnd();

        glutSwapBuffers();

    };

    double dXnew1;
    double dYnew1;

    double dXnew2;
    double dYnew2;

    int test;


    

    timer_bounce = [&]() {

        for (auto it1 = particles->begin(); it1 != std::prev(particles->end()); ++it1)
        {
                
            State inHit = State::outOfHit;

            for (auto it2 = std::next(it1); it2 != std::prev(particles->end()); ++it2)
            {
                double maxSize = it1->getSize() > it2->getSize() ? it1->getSize() : it2->getSize();
                bool bothInHit = it1->getState() == State::inHit && it2->getState() == State::inHit;
                bool bothNotInHit = it1->getState() == State::outOfHit && it2->getState() == State::outOfHit;
                
                if (inRange(it1->getX(), it2->getX(), it2->getSize() / 2) && inRange(it1->getY(), it2->getY(), it2->getSize() / 2))
                {

                    if (bothNotInHit)
                    {                   
                        dXnew1 = velocityCalc(it1->getDx(), it2->getDx(), it1->getWeight(), it2->getWeight());
                        dYnew1 = velocityCalc(it1->getDy(), it2->getDy(), it1->getWeight(), it2->getWeight());
                        dXnew2 = velocityCalc(it2->getDx(), it1->getDx(), it2->getWeight(), it1->getWeight());
                        dYnew2 = velocityCalc(it2->getDy(), it1->getDy(), it2->getWeight(), it1->getWeight());

                        it1->setDx(dXnew1);
                        it1->setDy(dYnew1);

                        it2->setDx(dXnew2);
                        it2->setDy(dYnew2);

                        it1->setState(State::inHit);
                        it2->setState(State::inHit);

                    }

                    inHit = State::inHit;

                }
            }

            it1->setState(inHit);

        }

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

        


        glutPostRedisplay();
        glutTimerFunc(3, timerFunction, 1);

    };

    glutDisplayFunc(display);
    
    glutTimerFunc(3, timerFunction, 1);
   

    glutMainLoop();

}
