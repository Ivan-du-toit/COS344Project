#include "main.h"

int main(int argc, char* argv[]) {
	Initialize(argc, argv);

	glutMainLoop();

	exit(EXIT_SUCCESS);
}

void Initialize(int argc, char* argv[]) {
	GLenum GlewInitResult;

	InitWindow(argc, argv);
	
	glewExperimental = GL_TRUE;
	GlewInitResult = glewInit();

	if (GLEW_OK != GlewInitResult) {
		fprintf(stderr,	"ERROR: %s\n", glewGetErrorString(GlewInitResult));
		exit(EXIT_FAILURE);
	}
	
	fprintf(stdout, "INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));

	glGetError();
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	ExitOnGLError("ERROR: Could not set OpenGL depth testing options");

	glEnable(GL_CULL_FACE);
	ExitOnGLError("ERROR: Could not set OpenGL culling options");

	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	ExitOnGLError("ERROR: Could not set OpenGL blending options");

	glEnable(GL_MULTISAMPLE);
	ExitOnGLError("ERROR: Could not set OpenGL MS");
	GLint  iMultiSample = 0;
	GLint  iNumSamples = 0;
	glGetIntegerv(GL_SAMPLE_BUFFERS, &iMultiSample);
	glGetIntegerv(GL_SAMPLES, &iNumSamples);
	ExitOnGLError("ERROR: Could not set OpenGL AA");
	printf("MultiSampling: %d, Number of Samples: %d\n", iMultiSample, iNumSamples);

	//glEnable(GLUT_MULTISAMPLE);
	//ExitOnGLError("ERROR: Could not set OpenGL Multisampling");
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	/*ShaderManager* passShader = new ShaderManager();
	passShader->addShader("shaders/pass/fragment.glsl", GL_FRAGMENT_SHADER)
		->addShader("shaders/pass/vertex.glsl", GL_VERTEX_SHADER)
		->linkShaders();*/

	ShaderManager* geomShader = new ShaderManager();
	geomShader->addShader("shaders/geometry/fragment.glsl", GL_FRAGMENT_SHADER)
		->addShader("shaders/geometry/vertex.glsl", GL_VERTEX_SHADER)
		//->addShader("shaders/geometry/geometry.glsl", GL_GEOMETRY_SHADER)
		//->addShader("shaders/geometry/TCS.glsl", GL_TESS_CONTROL_SHADER)
		//->addShader("shaders/geometry/tes.glsl", GL_TESS_EVALUATION_SHADER)
		->linkShaders();

	ShaderManager* sShader = new ShaderManager();
	sShader->addShader("shaders/simple/fragment.glsl", GL_FRAGMENT_SHADER)
		->addShader("shaders/simple/vertex.glsl", GL_VERTEX_SHADER)
		->linkShaders();

	ShaderManager* skyshader = new ShaderManager();
	skyshader->addShader("shaders/skybox/fragment.glsl", GL_FRAGMENT_SHADER)
		->addShader("shaders/skybox/vertex.glsl", GL_VERTEX_SHADER)
		->linkShaders();

	phongShader = new ShaderManager();
	phongShader->addShader("shaders/phong/fragment.glsl", GL_FRAGMENT_SHADER)
		->addShader("shaders/phong/vertex.glsl", GL_VERTEX_SHADER)
		->addShader("shaders/phong/TCS.glsl", GL_TESS_CONTROL_SHADER)
		->addShader("shaders/phong/tes.glsl", GL_TESS_EVALUATION_SHADER)
		->linkShaders();

	models = std::vector<Model*>();
	models.push_back(new Sphere(phongShader, new Cube(phongShader)));
	models[0]->translate(glm::vec3(3.0f, 2.0f, 0.0f));

	models.push_back(new Terrain(geomShader, new MultiQuad(geomShader, 500)));
	//models[models.size()-1]->scale(glm::vec3(1, 0, 1));
	models[models.size()-1]->translate(glm::vec3(-250.0f, -2.0f, -250.0f));
	
	models.push_back(new VAOModel(sShader, new ObjLoader(sShader, "meshes/monkey.obj")));
	models[models.size()-1]->translate(glm::vec3(0.0f, 2.0f, 0.0f));
	
	skybox = new Skybox(skyshader, new ObjLoader(skyshader, "meshes/cube2.obj"));
	skybox->scale(glm::vec3(50, 50, 50));

	ExitOnGLError("Model messed up");
	
	cam = new Camera(sShader, CurrentWidth, CurrentHeight, camStart, glm::vec3(0.0f));
	light = new Light(sShader, CurrentWidth, CurrentHeight, glm::vec3(3.0f), glm::vec3(0.0f));
}

void InitWindow(int argc, char* argv[]) {
	glutInit(&argc, argv);
	
	glutInitContextVersion(4, 2);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	
	glutInitWindowSize(CurrentWidth, CurrentHeight);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);

	WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);

	if(WindowHandle < 1) {
		fprintf(stderr, "ERROR: Could not create a new rendering window.\n");
		exit(EXIT_FAILURE);
	}
	glutReshapeFunc(ResizeFunction);
	glutDisplayFunc(RenderFunction);
	glutIdleFunc(IdleFunction);
	//glutKeyboardFunc(keyboard);
	glutTimerFunc(0, TimerFunction, 0);
	glutCloseFunc(cleanup);

	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutPassiveMotionFunc(mouseMove);
}

void ResizeFunction(int Width, int Height) {
	CurrentWidth = Width;
	CurrentHeight = Height;

	cam->updatePerspective(Width, Height);

	/*delete depthBuffer;
	depthBuffer = new DepthBuffer(Width, Height);
	depthBuffer->unbind();*/
	if (colourBuffer)
		delete colourBuffer;
	colourBuffer = new ColourFrameBuffer(Width*2, Height*2);
	colourBuffer->unbind();
}

void RenderFunction(void) {
	++FrameCount;

	/*glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	depthBuffer->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glCullFace(GL_FRONT);

	for (int i=0; i<models.size(); i++) {
		cam->updateView(models[i]->getShader());
		models[i]->draw();
	}

	glFlush();

	if (printScreen) {
		depthBuffer->write();
		printScreen = false;
	}
	glCullFace(GL_BACK);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	depthBuffer->unbind();
	*/
	//colourBuffer->bind();
	//cam->updatePerspective(CurrentWidth*2, CurrentHeight*2);
	//for (int i=0; i<2;i++) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		cam->updateView(skybox->getShader());
		glUseProgram(skybox->getShader()->getShaderID());
		glUniform1i(skybox->getShader()->getUniformLocation("fog"), hasFog);
		ExitOnGLError("Failed");
		glUseProgram(0);
		skybox->setAbsolutePosition(cam->getTranslation());
		skybox->draw();

		for (int i=0; i<models.size(); i++) {
			ShaderManager* shader = models[i]->getShader();
			cam->updateView(shader);
			if (shader->hasUniform("fog")) {
				glUseProgram(shader->getShaderID());
				glUniform1i(shader->getUniformLocation("fog"), hasFog);
				glUseProgram(0);
			}
			models[i]->draw();
		}

		if (printScreen) {
			//if (i==0)
				//colourBuffer->write();
			//screenShot();
			printScreen = false;
		}
		glFlush();
		colourBuffer->unbind();
		cam->updatePerspective(CurrentWidth, CurrentHeight);
	//}

	glutSwapBuffers();
	glutPostRedisplay();
}

void screenShot() {
	const GLsizei DATA_SIZE = CurrentWidth * CurrentHeight * (GLsizei)sizeof(GL_UNSIGNED_BYTE) * (GLsizei)3;
	GLubyte* data = new GLubyte[(unsigned)DATA_SIZE];

	glReadPixels(0, 0, CurrentWidth, CurrentHeight, GL_RGBA, GL_UNSIGNED_BYTE, data);

	unsigned char* RGBdata = new unsigned char[(unsigned)CurrentWidth * CurrentHeight* sizeof(unsigned char) * 4];
	GLuint index = 0;
	GLuint lineWidth = CurrentWidth*4;
	GLuint max = CurrentWidth * CurrentHeight * 4;
	GLuint offset = lineWidth;
	for (GLsizei y = 0; y < CurrentHeight; y++)
	{
		for (GLsizei x = 0; x < CurrentWidth; x++)
		{
			RGBdata[max - offset + index] = data[index];
			RGBdata[max - offset + index+1] = data[index+1];
			RGBdata[max - offset + index+2] = data[index+2];
			RGBdata[max - offset + index+3] = data[index+3];
			index += 4;
		}
		offset += lineWidth*2;
	}

	//Encode the image
	unsigned error = lodepng_encode32_file("screenShot.png", RGBdata, CurrentWidth, CurrentHeight);

	//if there's an error, display it
	if(error) printf("error %u: %s\n", error, lodepng_error_text(error));
}

void cleanup() {
	for (int i=0; i<models.size(); i++)
		delete models[i];
	delete cam;
	delete phongShader;
	printf("bye\n");
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 27: glutDestroyWindow (WindowHandle); exit(EXIT_SUCCESS); break;
		case ' ': animate = !animate; break; 
		default :printf("%c was pressed\n", key);
	}
	if (x==y){
	  ;
	}
}

void mouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		switch (button) {
			case GLUT_LEFT_BUTTON: printf("Left mouse button pressed\n"); break;
			case GLUT_MIDDLE_BUTTON: printf("Middle button pressed\n"); break;
			default: printf("Rigth button pressed\n"); break;
		}
		printf("Mouse Co-ordinates x:%i, y:%i\n", x, y);
	}
}


void keyUp(unsigned char key, int x, int y) {
	switch (key) {
		case 'w': 
		case 's': cam->setVelocity(cam->getVelocity() * glm::vec3(0, 1, 1)); break;
		case 'a': 
		case 'd': cam->setVelocity(cam->getVelocity() * glm::vec3(1, 1, 0)); break;
		case 'W': if (wireFrameMode) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); wireFrameMode = !wireFrameMode; break;
		case ' ': printScreen = true; break;
		case 'f': hasFog = !hasFog; printf("wtf\n"); break;
		
	}
}

void keyDown(unsigned char key, int x, int y) {
	switch (key) {
		case 27: exit(EXIT_SUCCESS); break;
		case 'w': cam->setVelocity(cam->getVelocity()*glm::vec3(0, 1, 1) + glm::vec3(cameraSpeed, 0, 0)); break;
		case 's': cam->setVelocity(cam->getVelocity()*glm::vec3(0, 1, 1) + glm::vec3(-cameraSpeed, 0, 0));  break;
		case 'a': cam->setVelocity(cam->getVelocity()*glm::vec3(1, 1, 0) + glm::vec3(0, 0, cameraSpeed));  break;
		case 'd': cam->setVelocity(cam->getVelocity()*glm::vec3(1, 1, 0) + glm::vec3(0, 0, -cameraSpeed)); break;
		case 'p': 
			//printf("Eye: %f, %f, %f\n", eye.x, eye.y, eye.z); 
			//printf("At: %f, %f, %f\n", at.x, at.y, at.z); 
			//printf("Direction: %f, %f, %f\n", direction.x, direction.y, direction.z); 
			//direction = glm::normalize(direction);
			//printf("Direction: %f, %f, %f\n", direction.x, direction.y, direction.z); 
		break;
		case ' ': captureMouse = !captureMouse; break;
		//case 'f': hasFog = !hasFog; break;
		case 'z': {
			cam->setAbsolutePosition(camStart);
			cam->setLookAt(glm::vec3(0.0f));
		} break;
		default :printf("%c was pressed\n", key);
	}
}

void mouseMove(int x, int y) {

	int centerX = CurrentWidth/2;
	int centerY = CurrentHeight/2;
	int deltaX = centerX - x;
	int deltaY = centerY - y;
	if (x != centerX || y != centerY) {
		cam->rotate(deltaX, deltaY);
		glutWarpPointer(centerX, centerY);
	}
}

void IdleFunction(void) {
	glutPostRedisplay();
}

void calcFPS(int Value) {
	if (0 != Value) {
		char* TempString = (char*) malloc(512 + strlen(WINDOW_TITLE_PREFIX));

		sprintf(TempString, "%s: %d Frames Per Second @ %d x %d", WINDOW_TITLE_PREFIX, FrameCount * ANIMATIONS_PER_SECOND, CurrentWidth, CurrentHeight);

		glutSetWindowTitle(TempString);
		free(TempString);
	}
	FrameCount = 0;
}

void doAnimation() {
	if (animate) {
		for (int i=0; i<models.size(); i++) {
			models[i]->rotate(glm::vec3(0.0f, 2.0f, 0));
		}
	}
}

void TimerFunction(int Value) {
	calcFPS(Value);
	
	doAnimation();
	cam->tick();

	glutTimerFunc(1000/ANIMATIONS_PER_SECOND, TimerFunction, 1);
}

