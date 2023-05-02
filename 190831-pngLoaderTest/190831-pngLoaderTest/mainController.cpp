#include "stdafx.h"
#include "mainController.h"


mainController::mainController()
{
	printf("mainController init\n");

	srand(time(NULL));

	for (int i = 0; i < 4; i++)
	{
		add[i] = 0.01 + (rand() % 100)*0.0005;
		tempRadian[i] = 0.0;
	}
}


mainController::~mainController()
{
}






void mainController::setup_openGL(HWND mainWindow)
{
	printf("SETUP OPENGL\n");

	opengl_initializer_obj = new OpenGLInitializerClass();
	shader_loader_obj = new shaderLoaderClass();

	window_manager_obj = new WindowManagerClass();

	// create glWindow
	HWND glWindow = window_manager_obj->create_nomenu_window(L"glWindow", L"glwindow"); // 0, nomenu window, 1. borderless window, 2 panel window
	window_manager_obj->set_window_position(glWindow, 600, 100);
	window_manager_obj->set_window_size(glWindow, 640, 480);
	window_manager_obj->set_window_level(glWindow, 1); // 0 bottom, 1 top, 2 topmost


	// create dummy window
	HWND dummyWnd = window_manager_obj->create_borderless_window(L"dummy");
	window_manager_obj->set_window_position(dummyWnd, 0, 0);
	window_manager_obj->set_window_size(dummyWnd, 10, 10);
	window_manager_obj->set_window_level(dummyWnd, 1);

	// init opengl
	opengl_initializer_obj->init_OpenGL_functions(dummyWnd, glWindow);
	window_manager_obj->close_window(dummyWnd);
	opengl_initializer_obj->set_OpenGL_status();




	// setup shader
	shader_loader_obj->loadShaderSource_And_CompileShader("simpleVS.txt", 0, &SIMPLE_VS);
	shader_loader_obj->loadShaderSource_And_CompileShader("simpleFS.txt", 2, &SIMPLE_FS);
	shader_loader_obj->createProgram_And_AttachShader(&SIMPLE_PRG, &SIMPLE_VS, NULL, &SIMPLE_FS);

	shader_loader_obj->getUniformLocation(&SIMPLE_PRG, &UNF_SIMPLE_texIndex, "texIndex");





	// VAO VBO
	GLfloat initData[4][4];
	for (int i = 0; i < 4; i++)
	{
		initData[i][0] = 0.0;
		initData[i][1] = 0.0;
		initData[i][2] = 0.0;
		initData[i][3] = 0.0;
	}

	glGenVertexArrays(1, &VAO_name);
	glGenBuffers(2, VBO_name);

	glBindVertexArray(VAO_name);
	
	// set enabled vertex attrib array
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// init VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO_name[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 4, initData, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_name[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 4, initData, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);




	// create texture
	glGenSamplers(1, &Sampler_name);
	glSamplerParameteri(Sampler_name, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(Sampler_name, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(Sampler_name, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glSamplerParameteri(Sampler_name, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLint tempNum;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &tempNum);

	for (int i = 0; i < tempNum; i++)
	{
		glBindSampler(i, Sampler_name);
	}





	// get image data
	bitmaploader_obj = new bitmapLoaderClass();
	//bitmaploader_obj->get_BGRA_bitmapInformation("24bit.bmp");
	bitmaploader_obj->load_bitmap_from_path("24bit.bmp");







	//PNG_obj = new PNG_LoaderClass();
	//PNG_obj->load_png_from_path("png24.png");
	//PNG_obj->load_png_from_path("buki/buki_105.png");

	//pngloader_obj = new pngLoaderClass();
	//bool isSuccess = pngloader_obj->load_png24_from_path("png24.png");
	//bool isSuccess = pngloader_obj->load_png24_from_path("buki/buki_133.png");


	png24_obj = new png24LoaderClass();
	//bool yn = png24_obj->load_png24_from_path("png24.png");
	bool yn = png24_obj->load_png24_from_path("buki/buki_105.png");


	glGenTextures(1, &TEX_name);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TEX_name);
	
	/*
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		bitmaploader_obj->BMP_width,
		bitmaploader_obj->BMP_height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		bitmaploader_obj->BMP_dataPtr);
	*/
	
	
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		png24_obj->PNG_width,
		png24_obj->PNG_height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		png24_obj->PNG_dataPtr);
		
}



void mainController::draw()
{
	//printf("draw\n");

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, 640, 480);

	glUseProgram(SIMPLE_PRG);
	glUniform1i(UNF_SIMPLE_texIndex, 0);

	GLfloat vert[4][4];
	GLfloat texc[4][4];
	float sincos[4][2];

	for (int i = 0; i < 4; i++)
	{
		vert[i][2] = 0.0;	vert[i][3] = 1.0;
		texc[i][2] = 0.0;	texc[i][3] = 0.0;

		tempRadian[i] += add[i];
		if (tempRadian[i] > 6.2831853)
		{
			tempRadian[i] -= 6.2831853;
		}

		sincos[i][0] = cos(tempRadian[i])*0.05;
		sincos[i][1] = sin(tempRadian[i])*0.05;
	}

	float tempSize = 0.9;

	vert[0][0] = -tempSize;	vert[0][1] = tempSize;
	vert[1][0] = -tempSize;	vert[1][1] = -tempSize;
	vert[2][0] = tempSize;	vert[2][1] = tempSize;
	vert[3][0] = tempSize;	vert[3][1] = -tempSize;

	vert[0][0] += sincos[0][0];	vert[0][1] += sincos[0][1];
	vert[1][0] += sincos[1][0];	vert[1][1] += sincos[1][1];
	vert[2][0] += sincos[2][0];	vert[2][1] += sincos[2][1];
	vert[3][0] += sincos[3][0];	vert[3][1] += sincos[3][1];



	texc[0][0] = 0.0;	texc[0][1] = 0.0;
	texc[1][0] = 0.0;	texc[1][1] = 1.0;
	texc[2][0] = 1.0;	texc[2][1] = 0.0;
	texc[3][0] = 1.0;	texc[3][1] = 1.0;


	glBindVertexArray(VAO_name);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_name[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 4 * 4, vert);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_name[1]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 4 * 4, texc);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray(0);

	SwapBuffers(opengl_initializer_obj->OpenGL_HDC);

}
