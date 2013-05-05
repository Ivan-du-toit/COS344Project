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
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	phongShader = new ShaderManager();
	phongShader->addShader("shaders/phong.fragment.glsl", GL_FRAGMENT_SHADER)
		->addShader("shaders/phong.vertex.glsl", GL_VERTEX_SHADER)
		->addShader("shaders/phong.TCS.glsl", GL_TESS_CONTROL_SHADER)
		->addShader("shaders/phong.tes.glsl", GL_TESS_EVALUATION_SHADER)
		->linkShaders();
	
	flatShader = new ShaderManager();
	flatShader->addShader("shaders/flat.fragment.glsl", GL_FRAGMENT_SHADER)
		->addShader("shaders/flat.vertex.glsl", GL_VERTEX_SHADER)
		->addShader("shaders/flat.TCS.glsl", GL_TESS_CONTROL_SHADER)
		->addShader("shaders/flat.tes.glsl", GL_TESS_EVALUATION_SHADER)
		->linkShaders();

	gauroudShader = new ShaderManager();
	gauroudShader->addShader("shaders/gauroud.fragment.glsl", GL_FRAGMENT_SHADER)
		->addShader("shaders/gauroud.vertex.glsl", GL_VERTEX_SHADER)
		->addShader("shaders/gauroud.TCS.glsl", GL_TESS_CONTROL_SHADER)
		->addShader("shaders/gauroud.tes.glsl", GL_TESS_EVALUATION_SHADER)
		->linkShaders();

	models = new Model*[NUMBER_OF_MODELS];
	models[0] = new Sphere(flatShader, new Cube(flatShader));
	models[0]->translate(glm::vec3(1.0f, -0.85f, 0.0f));

	models[1] = new Sphere(gauroudShader, new Cube(gauroudShader));
	models[1]->translate(glm::vec3(-1.0f, -0.85f, 0.0f));

	models[2] = new Sphere(phongShader, new Cube(phongShader));
	models[2]->translate(glm::vec3(0.0f, 0.85f, 0.0f));
	
	//LoadedMesh* test = new LoadedMesh("meshes/cube.obj", phongShader);
	models[3] = new Sphere(phongShader, new LoadedMesh("meshes/cube.obj", phongShader));
	cam = new Camera(phongShader, CurrentWidth, CurrentHeight);
}

void InitWindow(int argc, char* argv[]) {
	glutInit(&argc, argv);
	
	glutInitContextVersion(4, 2);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	
	glutInitWindowSize(CurrentWidth, CurrentHeight);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);

	if(WindowHandle < 1) {
		fprintf(stderr, "ERROR: Could not create a new rendering window.\n");
		exit(EXIT_FAILURE);
	}
	glutReshapeFunc(ResizeFunction);
	glutDisplayFunc(RenderFunction);
	glutIdleFunc(IdleFunction);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(0, TimerFunction, 0);
	glutCloseFunc(cleanup);
}

void ResizeFunction(int Width, int Height) {
	cam->updatePerspective(Width, Height);
}

void RenderFunction(void) {
	++FrameCount;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i=0; i<NUMBER_OF_MODELS; i++) {
		cam->updateView(models[i]->getShader());
		models[i]->draw();
	}
	
	glutSwapBuffers();
	glutPostRedisplay();
}

void cleanup() {
	for (int i=0; i<NUMBER_OF_MODELS; i++)
		delete models[i];
	delete models;
	delete cam;
	delete flatShader;
	delete phongShader;
	delete gauroudShader;
	printf("bye\n");
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 27: glutDestroyWindow (WindowHandle); exit(EXIT_SUCCESS); break;
		case '1': 
			models[0]->setShader(flatShader);
			models[1]->setShader(gauroudShader);
			models[2]->setShader(phongShader);
		break;
		case '2': 
			models[0]->setShader(flatShader);
			models[1]->setShader(flatShader);
			models[2]->setShader(flatShader);
		break;
		case '3': 
			models[0]->setShader(gauroudShader);
			models[1]->setShader(gauroudShader);
			models[2]->setShader(gauroudShader);
		break;
		case '4': 
			models[0]->setShader(phongShader);
			models[1]->setShader(phongShader);
			models[2]->setShader(phongShader);
		break;
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
		for (int i=0; i<NUMBER_OF_MODELS; i++) {
			models[i]->rotate(glm::vec3(0.0f, 2.0f, 0));
		}
	}
}

void TimerFunction(int Value) {
	calcFPS(Value);
	
	doAnimation();

	glutTimerFunc(1000/ANIMATIONS_PER_SECOND, TimerFunction, 1);
}