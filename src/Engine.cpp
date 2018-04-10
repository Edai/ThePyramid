//
// Created by edai on 20/03/18.
//

#include <sstream>
#include <random>
#include "Engine.hpp"

// http://www.songho.ca/opengl/gl_displaylist.html

Engine *Engine::instance = nullptr;

Engine::~Engine() = default;

void Engine::InitLights()
{
    GLfloat light_ambient[] = {0.10, 0.1, 0.10, 1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {0.0, 0.0, -10.0, 1.0};
    GLfloat mat_diffuse[] = {0.9, 0.9, 0.9, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {120.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}

void Engine::InitTextures()
{
    std::vector<std::string> *names = new std::vector<std::string>({TEXTURES_NAMES});
    textures = new std::vector<GLuint>();
    for (auto &s : *names)
        textures->push_back(SOIL_load_OGL_texture(s.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA));
    glBindTexture(GL_TEXTURE_2D, (*textures)[0]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_ADD);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_ADD);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

Engine::Engine()
{
    InitTextures();
    InitLights();
    InitDisplayList();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
    nb_lines = 5;
}

void Engine::LoadDisplayList(int nb)
{
    for (int i = 0; i < nb; i++)
    {
        glPushMatrix();
        glTranslatef(0.165f * (float)i, 0.0f, 0.0f);
        glCallList((*indexes)[0]);
        glPopMatrix();
    }
}
GLUquadric* cylinder = gluNewQuadric();

void Engine::LoadConeCylinder()
{
    glPushMatrix();
    gluQuadricDrawStyle(cylinder, GLU_FILL);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, (*textures)[0]);
    gluQuadricTexture(cylinder, GL_TRUE);
    gluQuadricNormals(cylinder, GLU_SMOOTH);
    gluCylinder(cylinder, 0.08f, 0.08f, 0.25f, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(cylinder, 0.08f, 0.0f, 0.25f, 50, 50);
    glPopMatrix();
}

void Engine::InitDisplayList()
{
    static std::random_device rd;
    static std::mt19937 e(rd());
    static std::uniform_real_distribution<> dist(0.0f, 1.0f);

    indexes = new std::vector<GLuint>();
    colors = new std::vector<GLfloat>();
    GLuint n = glGenLists(NB_LIST);
    glNewList(n, GL_COMPILE);
    LoadConeCylinder();
    glEndList();
    indexes->push_back(n);
    for (int i = 1; i < NB_LIST; i++)
    {
        colors->push_back(dist(e));
        colors->push_back(dist(e));
        colors->push_back(dist(e));
        glNewList(n + i, GL_COMPILE);
        LoadDisplayList(i);
        glEndList();
        indexes->push_back(n + i);
    }
}

void Engine::InitUpdate()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);
    glLoadIdentity();
}

void Engine::EndUpdate()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_TEXTURE_2D);
}

void Engine::Update()
{
    glLoadIdentity();
    gluLookAt(0, -0.3f, -0.5f, 0, 0, -1, 0, 1, 0);
    //glRotatef(50.5f, 0.0f, 1.0f, 0.0f);
    for (int i = 0; i < nb_lines; i++)
    {
        glColor4f((*colors)[i * 3], (*colors)[i * 3  + 1], (*colors)[i * 3 + 2], 1.0f);
        glCallList((*indexes)[i + 1]);
        glTranslatef(0.5f * -0.17f, -0.05f, -0.15f);
    }
}

void Engine::PrintInformation()
{
}
