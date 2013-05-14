#ifndef UTILS_H
#define UTILS_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <time.h>
#include <png.h>

void ExitOnGLError(const char* error_message);
unsigned char* loadTexturePNG(const char* filename, int& width, int& height);
void loadTexture();
#endif