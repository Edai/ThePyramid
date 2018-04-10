//
// Created by edai on 20/03/18.
//

#include <Engine.hpp>

GraphicalCore* GraphicalCore::instance = nullptr;

void GraphicalCore::Init()
{
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
}

void menu(int value)
{
    if (value == 1)
        Engine::Instance()->nb_lines++;
    else
        Engine::Instance()->nb_lines--;
    glutPostRedisplay();
}

void createMenu(void){
    glutCreateMenu(menu);
    glutAddMenuEntry("Add layer", 1);
    glutAddMenuEntry("Remove layer", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
float deltaAngle = 0.0f;
int xOrigin = -1;
int yOrigin = -1;

void mouseButton(int button, int state, int x, int y) {

    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {

        // when the button is released
        if (state == GLUT_UP) {
            Engine::angleY += deltaAngle;
            xOrigin = -1;
        }
        else  {// state = GLUT_DOWN
            xOrigin = x;
            yOrigin = y;
        }
    }
}

void mouseMove(int x, int y)
{
    Engine::angleX = (x - xOrigin) * 0.25f;
    Engine::angleY = (y - yOrigin)  * 0.25f;
}

bool GraphicalCore::Run(int ac, char **av, Options *options)
{
    glutInit(&ac, av);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH) ;
    glutInitWindowPosition(0,0);
    glutInitWindowSize(options->width, options->height);
    glutCreateWindow(options->window_name.c_str());
    Init();
    glutIdleFunc(Engine::_Update);
    glutReshapeFunc(GraphicalCore::Reshape);
    glutSpecialFunc(GraphicalCore::_SpecialKeyHandle);
    glutKeyboardFunc(GraphicalCore::_KeyboardHandle);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    createMenu();
    glutMainLoop();
    return (true);
}

void GraphicalCore::UpdateGl()
{
    glutSwapBuffers();
    glutPostRedisplay();
}

void GraphicalCore::KeyboardHandle(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
            glutLeaveMainLoop();
            break;
        case ' ':
            Engine::angleX = 0;
            Engine::angleY = 0;
            Engine::angleZ = 0;
            break;
        default:
            return;
    }
}

void GraphicalCore::SpecialKeyHandle(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            if (Engine::Instance()->nb_lines < 128)
            Engine::Instance()->nb_lines += 1.0f;
            break;
        case GLUT_KEY_DOWN:
            if (Engine::Instance()->nb_lines > 0)
                Engine::Instance()->nb_lines -= 1.0f;
            break;
        case GLUT_KEY_LEFT:
            break;
        case GLUT_KEY_RIGHT:
            break;
        default:
            break;
    }
}

void GraphicalCore::Reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 0.0, 5000.0);
    glMatrixMode(GL_MODELVIEW);
}

GraphicalCore::GraphicalCore() = default;

GraphicalCore::~GraphicalCore() = default;