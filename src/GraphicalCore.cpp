//
// Created by edai on 20/03/18.
//

#include <Engine.hpp>

GraphicalCore* GraphicalCore::instance = nullptr;
int GraphicalCore::xOrigin = -1;
int GraphicalCore::yOrigin = -1;

void GraphicalCore::Init()
{
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
}

void GraphicalCore::menu(int value)
{
    if (value == 1 && Engine::Instance()->nb_lines < 128)
        Engine::Instance()->nb_lines += 1.0f;
    else if (value == 2 && Engine::Instance()->nb_lines > 0)
        Engine::Instance()->nb_lines -= 1.0f;
    else if (value == 3)
        Engine::Instance()->ReloadColors();
    glutPostRedisplay();
}

void GraphicalCore::createMenu(void){
    glutCreateMenu(GraphicalCore::menu);
    glutAddMenuEntry("Add layer", 1);
    glutAddMenuEntry("Remove layer", 2);
    glutAddMenuEntry("Change all layers colors", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void GraphicalCore::mouseButton(int button, int state, int x, int y) {

    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {

        // when the button is released
        if (state == GLUT_UP) {
            xOrigin = -1;
            yOrigin = -1;
        }
        else  {// state = GLUT_DOWN
            xOrigin = x;
            yOrigin = y;
        }
    }
}

void GraphicalCore::mouseMove(int x, int y)
{
    Engine::angleY = (x - xOrigin) * 0.25f;
    Engine::angleX = (y - yOrigin) * 0.25f;
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
        case 'r':
            Engine::angleX = 0;
            Engine::angleY = 0;
            Engine::angleZ = 0;
            break;
        case ' ':
            Engine::Instance()->ReloadColors();
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