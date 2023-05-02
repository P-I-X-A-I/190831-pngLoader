#pragma once

#include "OpenGLInitializerClass.h"
#include "shaderLoaderClass.h"

#include "WindowManagerClass.h"
#include "NotificationCenterClass.h"

#include "bitmapLoaderClass.h"
#include "png24LoaderClass.h"

#include "pngLoaderClass.h"
#include "PNG_LoaderClass.h"

class mainController
{
public:


	OpenGLInitializerClass* opengl_initializer_obj;
	shaderLoaderClass* shader_loader_obj;
	WindowManagerClass* window_manager_obj;
	bitmapLoaderClass* bitmaploader_obj;
	png24LoaderClass* png24_obj;
	pngLoaderClass* pngloader_obj;
	PNG_LoaderClass* PNG_obj;

	// shader
	GLuint SIMPLE_VS, SIMPLE_FS, SIMPLE_PRG;
	GLint UNF_SIMPLE_texIndex;

	// VAO, VBO
	GLuint VAO_name;
	GLuint VBO_name[2];

	// texture
	GLuint TEX_name;
	GLuint Sampler_name;


	// debug
	float tempRadian[4];
	float add[4];

	mainController();
	~mainController();

	void setup_openGL(HWND mainWindow);
	void draw();
};

