#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <stdio.h>
#include <math.h>

#define TEXHEIGHT   256
#define TEXWIDTH    256
GLubyte texture[TEXHEIGHT][TEXWIDTH][3];


typedef struct {
    float m[16];
} Mat4;

// GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
GLushort indices[] = { 0, 1, 2 };

typedef struct {
  GLint   aPosition;
  GLint   aTex;
  GLint   uVpMatrix;
  GLint   uModelMatrix;
  Mat4    VpMatrix;
} ShaderParams;

typedef struct {
    GLfloat x, y, z;
    GLfloat u, v;
} VertexType;

VertexType vObj[] = {
  {.x = -0.5f, .y = -0.5f, .z = 0.0f, .u = 0.0f, .v = 1.0f},
  {.x =  0.5f, .y = -0.5f, .z = 0.0f, .u = 1.0f, .v = 1.0f},
  {.x =  0.0f, .y =  0.5f, .z = 0.0f, .u = 0.5f, .v = 0.0f},
};

unsigned short iObj[] = {
  0, 1, 2
};

ShaderParams    g_sp;
// ScreenSettings  g_sc;

GLuint g_vbo;
GLuint g_ibo;
GLuint g_program;

// typedef const char GLbyte;

// Handle to a program object
GLuint programObject;
GLuint program;

// Attribute locations
GLint  positionLoc;
GLint  texCoordLoc;
// Sampler location
GLint samplerLoc;
// Texture handle
GLuint textureId;

Display *xdisplay;
Window xwindow;

void X_init();
int LoadFile(char *filename);
GLuint CreateSimpleTexture2D();
void destroyEGL(EGLDisplay &display, EGLContext &context, EGLSurface &surface);
int initializeEGL(Display *xdisp, Window &xwindow, EGLDisplay &display, EGLContext &context, EGLSurface &surface);
void init();
void Draw();
void mainloop(Display *xdisplay, EGLDisplay display, EGLSurface surface);
GLuint loadShader(GLenum shaderType, const char *source);
GLuint createProgram(const char *vshader, const char *fshader);
void createBuffer();
void deleteShaderProgram(GLuint shaderProgram);


//g++ EGL_test.cpp -o EGL_test -lX11 -lEGL -lGL

int main()
{
    //Xwindow
    X_init();

    //画像読み込み
      char path[] = "./num256.bmp";
    // LoadFile(path);

    EGLDisplay display = nullptr;
    EGLContext context = nullptr;
    EGLSurface surface = nullptr;
    if (initializeEGL(xdisplay, xwindow, display, context, surface) < 0)
    {
        std::cerr << "Error initializeEGL." << std::endl;
        exit(EXIT_FAILURE);
    }

    createBuffer();

    mainloop(xdisplay, display, surface);

    destroyEGL(display, context, surface);
    XDestroyWindow(xdisplay, xwindow);
    XCloseDisplay(xdisplay);

    return 0;
}

void X_init()
{
    xdisplay = XOpenDisplay(nullptr);
    if (xdisplay == nullptr)
    {
        std::cerr << "Error XOpenDisplay." << std::endl;
        exit(EXIT_FAILURE);
    }

    xwindow = XCreateSimpleWindow(xdisplay, DefaultRootWindow(xdisplay), 100, 100, 960, 540,
                                         1, BlackPixel(xdisplay, 0), WhitePixel(xdisplay, 0));

    XMapWindow(xdisplay, xwindow);
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

    printf("LoadFile %d \n", n_read);

  return n_read;
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

    // EGLint attr[] = {EGL_BUFFER_SIZE, 16, EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_NONE};
      EGLint attr[] = {
    EGL_RED_SIZE,       8,
    EGL_GREEN_SIZE,     8,
    EGL_BLUE_SIZE,      8,
    EGL_ALPHA_SIZE,     8,
    EGL_DEPTH_SIZE,     24,
    EGL_NONE
  };
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
    init();

    while (true)
    {
        XPending(xdisplay);
        
        Draw();

        eglSwapBuffers(display, surface);
        usleep(1000);
    }
    deleteShaderProgram(program);
}

void init()
{
   const char vShaderStr[] =  
  "attribute vec3 aPosition;\n"
  "attribute vec2 aTex;\n"
  "varying   vec2 vTex;\n"
  "uniform   mat4 uVpMatrix;\n"
  "uniform   mat4 uModelMatrix;\n"
  "\n"
  "void main(void) {\n"
  "  vTex = aTex;\n"
  "  gl_Position = uVpMatrix * uModelMatrix * vec4(aPosition, 1.0);\n"
  "}\n";
   
   const char fShaderStr[] =  
  "precision mediump float;\n"\
  "varying   vec2  vTex;\n"
  "void main()        \n"
  "{                  \n"
  "  gl_FragColor = vec4(vTex.y, vTex.x, 0.5, 1.0);\n"
  "}                  \n";

    program = createProgram(vShaderStr, fShaderStr);
    glUseProgram(program);

    positionLoc = glGetAttribLocation ( program, "a_position" );
    texCoordLoc = glGetAttribLocation ( program, "a_texCoord" );

    samplerLoc = glGetUniformLocation ( program, "s_texture" );

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

    // Load the texture
    // glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, 3, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels );
    glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, TEXWIDTH, TEXHEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
    glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
    
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

void createBuffer()
{
  glGenBuffers(1, &g_vbo);
  // vertex buffer
  glBindBuffer(GL_ARRAY_BUFFER, g_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vObj), vObj, GL_STATIC_DRAW);

  // index buffer
  glGenBuffers(1, &g_ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(iObj), iObj, GL_STATIC_DRAW);
}


/*
void Draw ()
{
//    GLfloat vVertices[] = { -1.0f,  1.0f, 0.0f,  // Position 0
//                             0.0f,  1.0f,        // TexCoord 0 
//                            -1.0f, -1.0f, 0.0f,  // Position 1
//                             0.0f,  0.0f,        // TexCoord 1
//                             1.0f, -1.0f, 0.0f,  // Position 2
//                             1.0f,  0.0f,        // TexCoord 2
//                             1.0f,  1.0f, 0.0f,  // Position 3
//                             1.0f,  1.0f         // TexCoord 3
//                          };

   GLfloat vVertices[] = { -0.8f,  0.8f, 0.0f,  // Position 0
                            0.0f,  1.0f,        // TexCoord 0 
                           -0.8f, -0.8f, 0.0f,  // Position 1
                            0.0f,  0.0f,        // TexCoord 1
                            0.8f, -0.8f, 0.0f,  // Position 2
                            1.0f,  0.0f,        // TexCoord 2
                            0.8f,  0.8f, 0.0f,  // Position 3
                            1.0f,  1.0f         // TexCoord 3
                         };

   GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
   
   // Clear the color buffer
   glClear ( GL_COLOR_BUFFER_BIT );

   // Use the program object
   glUseProgram ( program );

   // Load the vertex position
   glVertexAttribPointer ( positionLoc, 3, GL_FLOAT, 
                           GL_FALSE, 5 * sizeof(GLfloat), vVertices );
   // Load the texture coordinate
   glVertexAttribPointer ( texCoordLoc, 2, GL_FLOAT,
                           GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3] );

   glEnableVertexAttribArray ( positionLoc );
   glEnableVertexAttribArray ( texCoordLoc );

   // Bind the texture
   glActiveTexture ( GL_TEXTURE0 );
   glBindTexture ( GL_TEXTURE_2D, textureId );

//    // Set the sampler texture unit to 0
//    glUniform1i ( samplerLoc, 0 );

    glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );
    // glDrawArrays(GL_TRIANGLES, 0, 3);
}
*/
void Draw ()
{
  glUseProgram(g_program);
  glBindBuffer(GL_ARRAY_BUFFER, g_vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_ibo);
  glEnableVertexAttribArray(g_sp.aPosition);
  glEnableVertexAttribArray(g_sp.aTex);
  glVertexAttribPointer(g_sp.aPosition, 3, GL_FLOAT, GL_FALSE, 20, (void*)0);
  glVertexAttribPointer(g_sp.aTex, 2, GL_FLOAT, GL_FALSE, 20, (void*)12);
  glEnableVertexAttribArray(0);
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
}

void makeUnit(Mat4 *m)
{
  std::memset(m, 0, sizeof(Mat4));
  m->m[0] = m->m[5] = m->m[10]= m->m[15] = 1.0f;
}

void makeProjectionMatrix(Mat4 *m, float n, float f, float hfov, float r)
{
  float w = 1.0f / tan(hfov * 0.5f * M_PI / 180);
  float h = w * r;
  float q = 1.0f / (f - n);

  m->m[0] = w;
  m->m[5] = h;
  m->m[10]= -(f + n) * q;
  m->m[11]= -1.0f;
  m->m[14]= -2.0f * f * n * q;
  m->m[1] = m->m[2] = m->m[3] = m->m[4]  = m->m[6]  = m->m[7]
          = m->m[8] = m->m[9] = m->m[12] = m->m[13] = m->m[15] = 0.0f;
}

void setPosition(Mat4 *m, float x, float y, float z)
{
  m->m[12] = x;
  m->m[13] = y;
  m->m[14] = z;
}

void setRotationX(Mat4 *m, float degree)
{
  float rad = ((float)degree * M_PI / 180.0);
  m->m[ 5] = cos(rad);
  m->m[ 9] = - sin(rad);
  m->m[ 6] = sin(rad);
  m->m[10] = cos(rad);
}

void mulMatrix(Mat4 *r, Mat4 *a, Mat4 *b)
{
  float a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15;
  float b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13, b14, b15;

  a0 =a->m[ 0]; a1 =a->m[ 1]; a2 =a->m[ 2]; a3 =a->m[ 3];
  a4 =a->m[ 4]; a5 =a->m[ 5]; a6 =a->m[ 6]; a7 =a->m[ 7];
  a8 =a->m[ 8]; a9 =a->m[ 9]; a10=a->m[10]; a11=a->m[11];
  a12=a->m[12]; a13=a->m[13]; a14=a->m[14]; a15=a->m[15];
  b0 =b->m[ 0]; b1 =b->m[ 1]; b2 =b->m[ 2]; b3 =b->m[ 3];
  b4 =b->m[ 4]; b5 =b->m[ 5]; b6 =b->m[ 6]; b7 =b->m[ 7];
  b8 =b->m[ 8]; b9 =b->m[ 9]; b10=b->m[10]; b11=b->m[11];
  b12=b->m[12]; b13=b->m[13]; b14=b->m[14]; b15=b->m[15];

  r->m[ 0] = a0 * b0 + a4 * b1 +  a8 * b2 + a12 * b3;
  r->m[ 1] = a1 * b0 + a5 * b1 +  a9 * b2 + a13 * b3;
  r->m[ 2] = a2 * b0 + a6 * b1 + a10 * b2 + a14 * b3;
  r->m[ 3] = a3 * b0 + a7 * b1 + a11 * b2 + a15 * b3;
  r->m[ 4] = a0 * b4 + a4 * b5 +  a8 * b6 + a12 * b7;
  r->m[ 5] = a1 * b4 + a5 * b5 +  a9 * b6 + a13 * b7;
  r->m[ 6] = a2 * b4 + a6 * b5 + a10 * b6 + a14 * b7;
  r->m[ 7] = a3 * b4 + a7 * b5 + a11 * b6 + a15 * b7;
  r->m[ 8] = a0 * b8 + a4 * b9 +  a8 * b10+ a12 * b11;
  r->m[ 9] = a1 * b8 + a5 * b9 +  a9 * b10+ a13 * b11;
  r->m[10] = a2 * b8 + a6 * b9 + a10 * b10+ a14 * b11;
  r->m[11] = a3 * b8 + a7 * b9 + a11 * b10+ a15 * b11;
  r->m[12] = a0 * b12+ a4 * b13+  a8 * b14+ a12 * b15;
  r->m[13] = a1 * b12+ a5 * b13+  a9 * b14+ a13 * b15;
  r->m[14] = a2 * b12+ a6 * b13+ a10 * b14+ a14 * b15;
  r->m[15] = a3 * b12+ a7 * b13+ a11 * b14+ a15 * b15;
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

