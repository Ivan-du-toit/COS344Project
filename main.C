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

	/*ShaderManager* passShader = new ShaderManager();
	passShader->addShader("shaders/pass/fragment.glsl", GL_FRAGMENT_SHADER)
		->addShader("shaders/pass/vertex.glsl", GL_VERTEX_SHADER)
		->linkShaders();*/

	/*ShaderManager* tShader = new ShaderManager();
	gauroudShader->addShader("shaders/geometry/fragment.glsl", GL_FRAGMENT_SHADER)
		->addShader("shaders/geometry/vertex.glsl", GL_VERTEX_SHADER)
		->addShader("shaders/geometry/TCS.glsl", GL_TESS_CONTROL_SHADER)
		->addShader("shaders/geometry/tes.glsl", GL_TESS_EVALUATION_SHADER)
		->linkShaders();*/
	ShaderManager* sShader = new ShaderManager();
	sShader->addShader("shaders/simple/fragment.glsl", GL_FRAGMENT_SHADER)
		->addShader("shaders/simple/vertex.glsl", GL_VERTEX_SHADER)
		->linkShaders();

	phongShader = new ShaderManager();
	phongShader->addShader("shaders/phong.fragment.glsl", GL_FRAGMENT_SHADER)
		->addShader("shaders/phong.vertex.glsl", GL_VERTEX_SHADER)
		->addShader("shaders/phong.TCS.glsl", GL_TESS_CONTROL_SHADER)
		->addShader("shaders/phong.tes.glsl", GL_TESS_EVALUATION_SHADER)
		->linkShaders();

	models = std::vector<Model*>();
	models.push_back(new Sphere(phongShader, new Cube(phongShader)));
	models[0]->translate(glm::vec3(1.0f, -0.85f, 0.0f));

	models.push_back(new Sphere(phongShader, new Cube(phongShader)));
	models[1]->translate(glm::vec3(-1.0f, -0.85f, 0.0f));

	models.push_back(new Sphere(phongShader, new Cube(phongShader)));
	models[2]->translate(glm::vec3(0.0f, 0.85f, 0.0f));

	models.push_back(new VAOModel(sShader, new Quad(sShader)));
	models[3]->scale(glm::vec3(5, 0, 5));
	ExitOnGLError("Model messed up");
	cam = new Camera(sShader, CurrentWidth, CurrentHeight);
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

	for (int i=0; i<models.size(); i++) {
		cam->updateView(models[i]->getShader());
		models[i]->draw();
	}
	
	glutSwapBuffers();
	glutPostRedisplay();
}

void cleanup() {
	for (int i=0; i<models.size(); i++)
		delete models[i];
	//delete models;
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

	glutTimerFunc(1000/ANIMATIONS_PER_SECOND, TimerFunction, 1);
}