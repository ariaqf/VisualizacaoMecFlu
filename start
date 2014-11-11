
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
    Point p ((double) x, (double) y);
    points.push_back (p);

    triang.push_back (p);
    glutPostRedisplay ();
}

void init ()
{
    double x, y;
    srand(time(NULL));
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
