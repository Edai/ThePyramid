//
// Created by edai on 20/03/18.
//

#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "GraphicalCore.hpp"
#include <glm/glm.hpp>
#include <list>
#include <array>
#include <vector>

#define NB_LIST 128
#define TEXTURES_NAMES "../texture.jpg"

class Engine
{
public:
    Engine();
    ~Engine();

    static void _Update()
    {
        Instance()->InitUpdate();
        Instance()->Update();
        Instance()->EndUpdate();
        GraphicalCore::UpdateGl();
    }

    static GLUquadric* cylinder;
    static GLfloat angleX;
    static GLfloat angleY;
    static GLfloat angleZ;
    GLuint nb_lines;
    std::vector<GLuint> *indexes;
    std::vector<GLuint> *textures;
    std::vector<GLfloat> *colors;

private:
    void InitUpdate();
    void EndUpdate();
    void Update();
    void InitTextures();
    void InitLights();
    void InitDisplayList();
    void PrintInformation();
    void RenderBitmapString(float x, float y, void *font, std::string s);
    void LoadDisplayList(int i);
    void LoadConeCylinder();

#pragma SINGLETON
private:
    static Engine* instance;

public:
    static Engine* Instance()
    {
        if (instance == nullptr)
        {
            instance = new Engine();
        }
        return instance;
    }

#pragma END SINGLETON

    void ReloadColors();
};


#endif //ENGINE_HPP
