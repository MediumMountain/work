#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <iostream>
#include <unistd.h>
#include <math.h>
#include <algorithm>
#define degree2radian(degree) ((degree * M_PI) / 180.0F)


#define TEXHEIGHT   256
#define TEXWIDTH    256
GLubyte texture[TEXHEIGHT][TEXWIDTH][3];

// typedef const char GLbyte;

// Handle to a program object
GLuint programObject;
GLuint program;
GLuint g_vbo;
GLuint g_ibo;
// Attribute locations
GLint  positionLoc;
GLint  texCoordLoc;
// Sampler location
GLint samplerLoc;
// Texture handle
GLuint textureId;


int LoadFile(char *filename);
GLuint CreateSimpleTexture2D();
void destroyEGL(EGLDisplay &display, EGLContext &context, EGLSurface &surface);
int initializeEGL(Display *xdisp, Window &xwindow, EGLDisplay &display, EGLContext &context, EGLSurface &surface);
void init();
void createBuffer();
void Draw();
void mainloop(Display *xdisplay, EGLDisplay display, EGLSurface surface);
GLuint loadShader(GLenum shaderType, const char *source);
GLuint createProgram(const char *vshader, const char *fshader);
void deleteShaderProgram(GLuint shaderProgram);


//g++ EGL_test.cpp -o EGL_test -lX11 -lEGL -lGL

int main()
{
    Display *xdisplay = XOpenDisplay(nullptr);
    if (xdisplay == nullptr)
    {
        std::cerr << "Error XOpenDisplay." << std::endl;
        exit(EXIT_FAILURE);
    }

    Window xwindow = XCreateSimpleWindow(xdisplay, DefaultRootWindow(xdisplay), 100, 100, 960, 540,
                                         1, BlackPixel(xdisplay, 0), WhitePixel(xdisplay, 0));

    XMapWindow(xdisplay, xwindow);

    EGLDisplay display = nullptr;
    EGLContext context = nullptr;
    EGLSurface surface = nullptr;
    if (initializeEGL(xdisplay, xwindow, display, context, surface) < 0)
    {
        std::cerr << "Error initializeEGL." << std::endl;
        exit(EXIT_FAILURE);
    }

    mainloop(xdisplay, display, surface);

    destroyEGL(display, context, surface);
    XDestroyWindow(xdisplay, xwindow);
    XCloseDisplay(xdisplay);

    return 0;
}


int initializeEGL(Display *xdisp, Window &xwindow, EGLDisplay &display, EGLContext &context, EGLSurface &surface)
{
    display = eglGetDisplay(static_cast<EGLNativeDisplayType>(xdisp));
    if (display == EGL_NO_DISPLAY)
    {
        std::cerr << "Error eglGetDisplay." << std::endl;
        return -1;
    }
    if (!eglInitialize(display, nullptr, nullptr))
    {
        std::cerr << "Error eglInitialize." << std::endl;
        return -1;
    }

    EGLint attr[] = {EGL_BUFFER_SIZE, 16, EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_NONE};
    EGLConfig config = nullptr;
    EGLint numConfigs = 0;
    if (!eglChooseConfig(display, attr, &config, 1, &numConfigs))
    {
        std::cerr << "Error eglChooseConfig." << std::endl;
        return -1;
    }

    if (numConfigs != 1)
    {
        std::cerr << "Error numConfigs." << std::endl;
        return -1;
    }

    surface = eglCreateWindowSurface(display, config, xwindow, nullptr);
    if (surface == EGL_NO_SURFACE)
    {
        std::cerr << "Error eglCreateWindowSurface. " << eglGetError() << std::endl;
        return -1;
    }

    EGLint ctxattr[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
    context = eglCreateContext(display, config, EGL_NO_CONTEXT, ctxattr);
    if (context == EGL_NO_CONTEXT)
    {
        std::cerr << "Error eglCreateContext. " << eglGetError() << std::endl;
        return -1;
    }
    eglMakeCurrent(display, surface, surface, context);

    return 0;
}

void mainloop(Display *xdisplay, EGLDisplay display, EGLSurface surface)
{
    // const char *vshader = R"(
    //     attribute vec4 vPosition;
    //     attribute vec3 vColor;
    //     void main() {
    //         gl_Position = vPosition;
    //     }
    // )";

    // const char *fshader = R"(
    //     precision mediump float;
    //     void main() {
    //         gl_FragColor = vec4(0.3, 0.8, 0.3, 1.0);
    //     }
    // )";

    const char* vshader = R"(
		#version 300\n
		layout(location = 0) in vec3 position;\n
		layout(location = 1) in vec3 color;\n
		out vec3 outColor;\n
		void main(void) {\n
			outColor = color;\n
			gl_Position = vec4(position, 1.0f);\n
		}
        )";


	const char* fshader = R"(
		#version 300\n
		in vec3 outColor; \n
		out vec4 outFragmentColor; \n
		void main(void) {\n
			outFragmentColor = vec4(outColor, 1.0f); \n
		}

        )";

	// GLfloat points[] = { 0.5f, 0.5f, 0.0f, 
	// 			 0.5f, -0.5f, 0.0f, 
	// 			-0.5f, 0.5f,  0.0f,
	// 			-0.5f, -0.5f, 0.0f};

	GLfloat points[] = { 1.0f, 1.0f, 0.0f, 
				 1.0f, -1.0f, 0.0f, 
				-1.0f, 1.0f,  0.0f,
				-1.0f, -1.0f, 0.0f};

	GLfloat colors[] = { 0.0f, 0.0f, 0.3f,
				 0.0f, 0.8f, 0.0f,
				 1.0f, 0.0f, 1.0f,
				 1.0f, 0.8f, 1.0f};


   GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

    printf("vshader = \n");
    printf("vshader = %s\n", vshader);

    std::cout << "vshader = " << std::endl;
    std::cout << "fshader = " << fshader << std::endl;

    GLuint program = createProgram(vshader, fshader);

    GLuint vao, vertex_vbo, color_vbo;


	// 頂点座標のVBOを作成	
	glGenBuffers(1, &vertex_vbo); //バッファを作成
	glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo); //以下よりvertex_vboでバインドされているバッファが処理される
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW); //実データを格納

	glGenBuffers(1, &color_vbo); //バッファを作成
	glBindBuffer(GL_ARRAY_BUFFER, color_vbo); //以下よりvertex_vboでバインドされているバッファが処理される
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW); //実データを格納

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);

    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);

    int degree = 0;
    while (true)
    {
        XPending(xdisplay);

        const GLfloat matrix[] = {
        static_cast<GLfloat>(cos(degree2radian(degree))), 0.0f, static_cast<GLfloat>(sin(degree2radian(degree))), 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        static_cast<GLfloat>(-sin(degree2radian(degree))), 0.0f, static_cast<GLfloat>(cos(degree2radian(degree))), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f};

        glClearColor(0.25f, 0.25f, 0.5f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glUseProgram(program);
        glBindVertexArray(vao);

        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        eglSwapBuffers(display, surface);
        degree = (degree + 1) % 360;
        usleep(1000);
    }
    deleteShaderProgram(program);
}



GLuint createProgram(const char *vshader, const char *fshader)
{
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vshader);
    GLuint fragShader = loadShader(GL_FRAGMENT_SHADER, fshader);
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
    GLint linkStatus = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if (linkStatus == GL_FALSE)
    {
        std::cerr << "Error glLinkProgram." << std::endl;
        exit(EXIT_FAILURE);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
    return program;
}

GLuint loadShader(GLenum shaderType, const char *source)
{
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    GLint compiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE)
    {
        std::cerr << "Error glCompileShader." << std::endl;
        exit(EXIT_FAILURE);
    }
    return shader;
}

void destroyEGL(EGLDisplay &display, EGLContext &context, EGLSurface &surface)
{
    eglDestroyContext(display, context);
    eglDestroySurface(display, surface);
    eglTerminate(display);
}

void deleteShaderProgram(GLuint shaderProgram)
{
    glDeleteProgram(shaderProgram);
}

