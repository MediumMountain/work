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
    Window xwindow = XCreateSimpleWindow(xdisplay, DefaultRootWindow(xdisplay), 100, 100, 960, 540,
                                         1, BlackPixel(xdisplay, 0), WhitePixel(xdisplay, 0));

    XMapWindow(xdisplay, xwindow);

    int size = LoadFile("./num256.bmp");

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

int LoadFile(char *filename)
{
  FILE *fp;
  long fsize;
  int n_read = 0;

  /* テクスチャ画像の読み込み */
  if ((fp = fopen(filename, "rb")) != NULL) {
    //ファイルヘッダ分、シークする。
    fseek(fp, 54L, SEEK_SET);

    //動的にファイルサイズを取得できるようにする。
    // n_read = fread(texture, 1, sizeof texture, fp);
    // n_read = fread(texture, 1, 262198, fp);
    // n_read = fread(texture, 1, 66614, fp);
    n_read = fread(texture, 1, 196662, fp);
    
    fclose(fp);
  }

  return n_read;
}


int initializeEGL(Display *xdisp, Window &xwindow, EGLDisplay &display, EGLContext &context, EGLSurface &surface)
{
    display = eglGetDisplay(static_cast<EGLNativeDisplayType>(xdisp));
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

    surface = eglCreateWindowSurface(display, config, xwindow, nullptr);

    EGLint ctxattr[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
    context = eglCreateContext(display, config, EGL_NO_CONTEXT, ctxattr);
    eglMakeCurrent(display, surface, surface, context);

    return 0;
}

void mainloop(Display *xdisplay, EGLDisplay display, EGLSurface surface)
{
	const char* vshader =
		"#version 300 es\n"
		"layout(location = 0) in vec3 position;\n"
		"layout(location = 1) in vec2 vuv;\n"
        "out vec2 Flag_uv;\n"
		"void main(void) {\n"
            "Flag_uv  = vuv;\n"
			"gl_Position = vec4(position, 1.0f);\n"
		"}\n";


	const char* fshader =
		"#version 300 es\n"
        "precision mediump float;"
        "in vec2 Flag_uv;\n"
		"out vec4 outFragmentColor;\n"
        "uniform sampler2D Texture;\n"
		"void main() {\n"
            "outFragmentColor = texture2D( Texture, Flag_uv );\n"
		"}\n";


	GLfloat points[] = {
                    -0.5f, 0.5f, 0.0f, 
				    -0.5f, -0.5f, 0.0f, 
				    0.5f, 0.5f,  0.0f,
				    0.5f, 0.5f, 0.0f

                // 0.3f, 0.8f, 0.0f,//四角形2つ目
    			// 0.5f, -0.3f, 0.0f,
	    		// -0.7f, 0.5f, 0.0f,
		    	// -0.2f, -0.2f, 0.0f
                };


	GLfloat colors[] = { 0.5f, 0.0f, 0.3f,
				 0.5f, 0.8f, 0.0f,
				 1.0f, 0.0f, 1.0f,
				 1.0f, 0.8f, 1.0f,

                0.5f, 0.0f, 1.0f,//四角形2つ目
                0.5f, 0.3f, 0.5f,
                1.0f, 0.0f, 1.0f,
                0.2f, 0.1f, 1.0f };

    GLfloat vertex_uv[] = { 
                0.0f, 1.0f,
                0.0f, 0.0f,
                1.0f, 0.0f,
                1.0f, 1.0f,
                };

    // GLfloat vertex_uv[] = { 1.0f, 0.0f,
    //           1.0f, 1.0f,
    //           0.0f, 1.0f,
    //           0.0f, 0.0f,
    //           };                

    GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

    GLuint program = createProgram(vshader, fshader);

    // GLint gvPositionHandle_1 = glGetAttribLocation(program, "vPosition");
    // GLint gvPositionHandle_2 = glGetAttribLocation(program, "aColor");

    // std::cout << "gvPositionHandle_1 = " << gvPositionHandle_1 << std::endl;
    // std::cout << "gvPositionHandle_2 = " << gvPositionHandle_2 << std::endl;

    GLuint vao, vertex_vbo, texture_vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// 頂点座標のVBOを作成	
	glGenBuffers(1, &vertex_vbo); //バッファを作成
	glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo); //以下よりvertex_vboでバインドされているバッファが処理される
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW); //実データを格納

	glGenBuffers(1, &texture_vbo); //バッファを作成
	glBindBuffer(GL_ARRAY_BUFFER, texture_vbo); //以下よりvertex_vboでバインドされているバッファが処理される
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_uv), vertex_uv, GL_STATIC_DRAW); //実データを格納


    // Use tightly packed data
    glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );

    // Generate a texture object
    glGenTextures ( 1, &textureId );

    // Bind the texture object
    glBindTexture ( GL_TEXTURE_2D, textureId );

    // Set the filtering mode
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, TEXWIDTH, TEXHEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);


    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);

    int degree = 0;
    while (true)
    {
        XPending(xdisplay);

        glClearColor(0.25f, 0.25f, 0.5f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glUseProgram(program);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

        // glBindVertexArray(vao);

        // glDrawArrays(GL_TRIANGLES, 0, 3);

        // Bind the texture
        glActiveTexture ( GL_TEXTURE0 );
        glBindTexture ( GL_TEXTURE_2D, textureId );

        // glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        // glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
        // glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );

        eglSwapBuffers(display, surface);
        // degree = (degree + 1) % 360;

        // glViewport(20,20,480,270);
        //x : 画面左下から数えたXピクセル座標
        //y : 画面左下から数えたYピクセル座標
        //width : Viewport の幅ピクセル数
        //height : Viewport の高さピクセル数

        usleep(1000);
    }
    deleteShaderProgram(program);
}



GLuint createProgram(const char *vshader, const char *fshader)
{
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vshader);
    std::cout << "vshader = " << vshader << std::endl;
    GLuint fragShader = loadShader(GL_FRAGMENT_SHADER, fshader);
    std::cout << "fshader = " << fshader << std::endl;
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

