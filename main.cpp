#include <GL/glut.h>
#include <cstdlib>
#

#include "cell.h"
#include "convective.h"

int width = 1200;
int height = 640;
int enterVelocity = 80;
int rowNum = 0;
int columnNum = 0;
int cellSize = 2;
double gravity = 10;
double deltaT = 1;
double scale = 0.01;
bool stop = false;
int t = 0;
bool bug = false;
Cell** m_grid;

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    int w = columnNum;
    int h = rowNum;
    /// Draw points
    double duu =0;
    double duv =0;
    double cellSize1 = cellSize/scale;
    bool debug = false;
    if(!stop){
        for(int i = h-3; i >= 2; i--) {
            for(int j = 2; j < w-3; j++) {
                debug = false;
                if(!m_grid[i][j].isVoid) {
                    if(m_grid[i][j].hasLiquid){
                        if(false) {
                            std::cout << i << " " << j << std::endl;
                            std::cout << m_grid[i][j].leftSpeed << std::endl;
                            debug = true;
                        }
                        duu = DUU(m_grid[i][j-2].leftSpeed,m_grid[i][j-1].leftSpeed,m_grid[i][j].leftSpeed,
                            m_grid[i][j+1].leftSpeed,m_grid[i][j+2].leftSpeed, cellSize1, cellSize1, cellSize1
                            , cellSize1, 1, m_grid[i][j].isBorder);
                        duv = DUV(m_grid[i-2][j].leftSpeed, m_grid[i-1][j].leftSpeed, m_grid[i][j].leftSpeed,
                                    m_grid[i+1][j].leftSpeed, m_grid[i+2][j].leftSpeed, m_grid[i][j].speed_x, m_grid[i+1][j].speed_x,
                                    cellSize1, cellSize1, cellSize1, cellSize1, cellSize1, 1, m_grid[i][j].isBorder, debug);/**/
                        if(false) {
                            std::cout << m_grid[i-2][j].leftSpeed << " " << m_grid[i][j-1].leftSpeed << " " << m_grid[i][j].leftSpeed << " " << m_grid[i+1][j].leftSpeed << " " << m_grid[i+2][j].leftSpeed << " " << m_grid[i][j].speed_x << " " << m_grid[i+1][j].speed_x << std::endl;
                            std::cout << duu << " " << duv << std::endl;
                        }
                        //std::cout << duv << std::endl;
                        //m_grid[i][j].leftSpeed -= (duu + duv)*deltaT;

                        duu = DUU(m_grid[i][j-2].rightSpeed,m_grid[i][j-1].rightSpeed,m_grid[i][j].rightSpeed,
                            m_grid[i][j+1].rightSpeed,m_grid[i][j+2].rightSpeed, cellSize1, cellSize1, cellSize1
                            , cellSize1, 1, m_grid[i][j].isBorder);
                        duv = DUV(m_grid[i-2][j].rightSpeed, m_grid[i-1][j].rightSpeed, m_grid[i][j].rightSpeed,
                                    m_grid[i+1][j].rightSpeed, m_grid[i+2][j].rightSpeed, m_grid[i][j].speed_x, m_grid[i+1][j].speed_x,
                                    cellSize1, cellSize1, cellSize1, cellSize1, cellSize1, 1, m_grid[i][j].isBorder);/**/
                        m_grid[i][j].rightSpeed -= (duu + duv)*deltaT;
                    
                        duu = DUU(m_grid[i-2][j].bottomSpeed,m_grid[i-1][j].bottomSpeed,m_grid[i][j].bottomSpeed,
                                m_grid[i+1][j].bottomSpeed,m_grid[i+2][j].bottomSpeed, cellSize1, cellSize1, cellSize1
                                , cellSize1, 1, m_grid[i][j].isBorder);
                        duv = DUV(m_grid[i][j-2].bottomSpeed,m_grid[i][j-1].bottomSpeed,m_grid[i][j].bottomSpeed,
                                m_grid[i][j+1].bottomSpeed,m_grid[i][j+2].bottomSpeed, m_grid[i][j].speed_y, m_grid[i][j-1].speed_y,
                                cellSize1, cellSize1, cellSize1, cellSize1, cellSize1, 1, m_grid[i][j].isBorder);/**/
                        m_grid[i][j].bottomSpeed -=  (duu + duv)*deltaT;

                        duu = DUU(m_grid[i-2][j].topSpeed,m_grid[i-1][j].topSpeed,m_grid[i][j].topSpeed,
                                m_grid[i+1][j].topSpeed,m_grid[i+2][j].topSpeed, cellSize1, cellSize1, cellSize1
                                , cellSize1, 1, m_grid[i][j].isBorder);
                        duv = DUV(m_grid[i][j-2].topSpeed,m_grid[i][j-1].topSpeed,m_grid[i][j].topSpeed,
                                m_grid[i][j+1].topSpeed,m_grid[i][j+2].topSpeed, m_grid[i][j].speed_y, m_grid[i][j-1].speed_y,
                                cellSize1, cellSize1, cellSize1, cellSize1, cellSize1, 1, m_grid[i][j].isBorder);/**/
                        //m_grid[i][j].topSpeed -=  (duu + duv)*deltaT;
                    //    std::cout << duu << " " << duv << std::endl;
                        if(j==2&&(i<2+3*height/(4*cellSize))&&(i>2+height/(4*cellSize))) {
                            m_grid[i][j].leftSpeed = enterVelocity;
                            m_grid[i][j].rightSpeed = enterVelocity;    
                        }
                        if(m_grid[i][j].leftSpeed < 0) {
                            //std::cout << i << " " << j << std::endl;
                            //std::cout << m_grid[i][j].leftSpeed << std::endl;
                        }
                        m_grid[i][j].updateSpeed();

                    }
                }
            }
        }
        for(int i = h-3; i >= 3; i--) {
            for(int j = 2; j < w-3; j++) {
                if(m_grid[i][j].hasLiquid&(j>2)) {
                    m_grid[i][j].bottomSpeed -=  (gravity)*deltaT;
                    m_grid[i+1][j].topSpeed -=  (gravity)*deltaT;
                }
                if((m_grid[i][j-1].rightSpeed != 0)||(m_grid[i-1][j].bottomSpeed != 0))
                        m_grid[i][j].hasLiquid = true;
            }
        }
    }
    for(int i = 2; i < h-2; i++) {
        for(int j= 2; j < w-2; j++) {
            int J = j-2;
            int I = i-2;
            glPointSize(1);
            glColor3f (1.0, 0, 0);
            glBegin(GL_POINTS);
            //    glVertex2f ((J)  *cellSize  + cellSize/2, (I)  *cellSize  + cellSize/2);
            glEnd();
            glColor3f (1.0, 1.0, 1.0);
            if(m_grid[i][j].hasLiquid) {
//                std::cout << i << " " << j << std::endl;
//                std::cout << m_grid[i][j].leftSpeed << " " << m_grid[i][j].bottomSpeed << " " << m_grid[i][j].topSpeed << " " << m_grid[i][j].rightSpeed << std::endl;
            }
            glBegin(GL_LINES);
                glVertex2f ((J)  *cellSize + cellSize/2, (I)  *cellSize + cellSize/2);
                glVertex2f ((J)  *cellSize + cellSize/2 + m_grid[i][j].speed_x*scale*5, 
                            (I)  *cellSize + cellSize/2 - m_grid[i][j].speed_y*scale*5);
            glEnd();
            if((m_grid[i][j].hasLiquid && (i>=h-3))||(m_grid[i][j].hasLiquid && (j>=w-3)))
                stop = true;
        }
    }
    std::cout << "Stop: " << stop << std::endl;
    t++;
    /// Finish
    glutSwapBuffers ();
}

void reshape (int wid, int hgt)
{
    glViewport(0,0,width=wid,height=hgt);
    glMatrixMode (GL_PROJECTION_MATRIX);
    glLoadIdentity ();
    gluOrtho2D (0, width, height, 0);
}

void mouse (int button, int state, int x, int y)
{
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;
    glutPostRedisplay ();
}

void init ()
{
    int w = width/cellSize + 4;
    int h = height/cellSize + 4;
    rowNum = h;
    columnNum = w;
    m_grid = new Cell*[h];
    for(int i = 0; i < h; i++) {
        m_grid[i] = new Cell[w];
        for(int j = 0; j < w; j++) {
            m_grid[i][j].leftSpeed = 0;
            m_grid[i][j].rightSpeed = 0;
            m_grid[i][j].topSpeed = 0;
            m_grid[i][j].bottomSpeed = 0;
            if((i < 2)||(j < 2)||(i > w-2)||(j > w-2)){
                m_grid[i][j].isVoid = true;
            }
            else if((i == 2)||(j == 2)||(i == w-2)||(j == w-2)){
                m_grid[i][j].isBorder = true;
            }
            if(((j<2)&&((i<2+3*height/(4*cellSize))&&(i>2+height/(4*cellSize))))) {
//            if((j<=2)&&((i>10)&&(i<15))) {
                m_grid[i][j].leftSpeed = enterVelocity;
                m_grid[i][j].rightSpeed = enterVelocity;
                m_grid[i][j].hasLiquid = true;
            }
            m_grid[i][j].updateSpeed();
        }
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (width, height);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("test");
    glutDisplayFunc(display);
    glutMouseFunc (mouse);
    glutReshapeFunc (reshape);
    init();
    glutMainLoop();
    return 0;
}
