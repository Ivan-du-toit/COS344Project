#ifndef MAIN_H
#define MAIN_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wconversion"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#pragma GCC diagnostic pop

#include <stdlib.h>
#include <stdio.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Utils.h"
#include "Model.h"
#include "Sphere.h"
#include "Camera.h"
#include "Cube.h"
#include "Quad.h"
#include "VAOModel.h"
#include "Texture.h"
#include "OBjloader.h"
#include "DepthBuffer.h"
#include "Light.h"
#include "Skybox.h"
#include "Terrain.h"

#include "lodepng.h"

#define WINDOW_TITLE_PREFIX "Assignment 3"

int CurrentWidth = 800,
	CurrentHeight = 600,
	WindowHandle = 0;

bool animate = false;
bool captureMouse = true;
bool wireFrameMode = false;
bool printScreen = false;

GLfloat cameraSpeed = 0.5f;

const int ANIMATIONS_PER_SECOND = 60;
unsigned FrameCount = 0;


glm::vec3 camStart = glm::vec3(0,3,5);

std::vector<Model*> models;
//Model** models;
ShaderManager* phongShader;
Camera* cam;
Light* light;
Model* skybox;

DepthBuffer* depthBuffer;

void Initialize(int, char*[]);
void InitWindow(int, char*[]);
void ResizeFunction(int, int);
void RenderFunction(void);
void TimerFunction(int);
void IdleFunction(void);
void cleanup(void);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void keyDown(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void mouseMove(int x, int y);

void calcFPS(int Value);
void doAnimation();
void screenShot();
#endif