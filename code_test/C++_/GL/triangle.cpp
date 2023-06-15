/* ------------------------------------------------------------------
 * triangel.c, Raspberry Pi, Open GL ES2 Sample
 * http://www.mztn.org/rpi/rpi11.html
 * 2012/10/04
 * Copyright (C) 2012, Jun Mizutani All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted.
 * ------------------------------------------------------------------ */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <stdio.h>
#include <math.h>

typedef struct {
  EGLNativeWindowType  nativeWin;
  EGLDisplay  display;
  EGLContext  context;
  EGLSurface  surface;
  EGLint      majorVersion;
  EGLint      minorVersion;
  int         width;
  int         height;
} ScreenSettings;

const char vShaderSrc[] =
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

const char fShaderSrc[] =
  "precision mediump float;\n"\
  "varying   vec2  vTex;\n"
  "void main()        \n"
  "{                  \n"
  "  gl_FragColor = vec4(vTex.y, vTex.x, 0.5, 1.0);\n"
  "}                  \n";

typedef struct {
    float m[16];
} Mat4;

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
ScreenSettings  g_sc;

GLuint g_vbo;
GLuint g_ibo;
GLuint g_program;

Display *xdisplay;
Window xwindow;

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

/*
EGLBoolean WinCreate(ScreenSettings *sc)
{
  uint32_t success = 0;
  uint32_t width;
  uint32_t height;
  VC_RECT_T dst_rect;
  VC_RECT_T src_rect;
  DISPMANX_ELEMENT_HANDLE_T dispman_element;
  DISPMANX_DISPLAY_HANDLE_T dispman_display;
  DISPMANX_UPDATE_HANDLE_T dispman_update;
  static EGL_DISPMANX_WINDOW_T nativewindow;
  VC_DISPMANX_ALPHA_T alpha = {DISPMANX_FLAGS_ALPHA_FIXED_ALL_PIXELS, 255, 0};

  success = graphics_get_display_size(0, &width, &height);
  if (success < 0) return EGL_FALSE;

  sc->width = width;
  sc->height = height;

  vc_dispmanx_rect_set(&dst_rect, 0, 0, sc->width, sc->height);
  vc_dispmanx_rect_set(&src_rect, 0, 0, sc->width << 16, sc->height << 16);

  dispman_display = vc_dispmanx_display_open(0);
  dispman_update = vc_dispmanx_update_start(0);
  dispman_element = vc_dispmanx_element_add(dispman_update, dispman_display,
     0, &dst_rect, 0, &src_rect, DISPMANX_PROTECTION_NONE, &alpha, 0, 0);
  vc_dispmanx_update_submit_sync(dispman_update);
  nativewindow.element = dispman_element;
  nativewindow.width = width;
  nativewindow.height = height;
  sc->nativeWin = &nativewindow;
  return EGL_TRUE;
}
*/

EGLBoolean SurfaceCreate(ScreenSettings *sc)
{
  EGLint attrib[] = {
    EGL_RED_SIZE,       8,
    EGL_GREEN_SIZE,     8,
    EGL_BLUE_SIZE,      8,
    EGL_ALPHA_SIZE,     8,
    EGL_DEPTH_SIZE,     24,
    EGL_NONE
  };
  EGLint context[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
  EGLint numConfigs;
  EGLConfig config;

  sc->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  if (sc->display == EGL_NO_DISPLAY) return EGL_FALSE;
  if (!eglInitialize(sc->display, &sc->majorVersion, &sc->minorVersion))
    return EGL_FALSE;
  if (!eglChooseConfig(sc->display, attrib, &config, 1, &numConfigs))
    return EGL_FALSE;
  sc->surface = eglCreateWindowSurface(sc->display, config, sc->nativeWin, NULL);
  if (sc->surface == EGL_NO_SURFACE) return EGL_FALSE;
  sc->context = eglCreateContext(sc->display, config, EGL_NO_CONTEXT, context);
  if (sc->context == EGL_NO_CONTEXT) return EGL_FALSE;
  if (!eglMakeCurrent(sc->display, sc->surface, sc->surface, sc->context))
      return EGL_FALSE;
  return EGL_TRUE;
}

GLuint LoadShader(GLenum type, const char *shaderSource)
{
  GLuint shader;
  GLint compiled;

  shader = glCreateShader(type);
  if (shader == 0) return 0;

  glShaderSource(shader, 1, &shaderSource, NULL);
  glCompileShader(shader);

  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
  if (!compiled) { // compile error
    GLint infoLen = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
    // if (infoLen > 0) {
    //   char* infoLog = malloc(sizeof(char) * infoLen);
    //   glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
    //   printf("Error compiling shader:\n%s\n", infoLog);
    //   free(infoLog);
    // }
    glDeleteShader(shader);
    return 0;
  }
  return shader;
}

int InitShaders(GLuint *program, char const *vShSrc, char const *fShSrc)
{
  GLuint vShader;
  GLuint fShader;
  GLint  linked;
  GLuint prog;

  vShader = LoadShader(GL_VERTEX_SHADER, vShSrc);
  fShader = LoadShader(GL_FRAGMENT_SHADER, fShSrc);

  prog = glCreateProgram();
  if (prog == 0) return 0;

  glAttachShader(prog, vShader);
  glAttachShader(prog, fShader);
  glLinkProgram(prog);
  glGetProgramiv (prog, GL_LINK_STATUS, &linked);
  if (!linked) { // error
    GLint infoLen = 0;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &infoLen);
    // if (infoLen > 0) {
    //   char* infoLog = malloc(sizeof(char) * infoLen);
    //   glGetProgramInfoLog(prog, infoLen, NULL, infoLog);
    //   printf("Error linking program:\n%s\n", infoLog);
    //   free ( infoLog );
    // }
    glDeleteProgram (prog);
    return GL_FALSE;
  }
  glDeleteShader(vShader);
  glDeleteShader(fShader);

  *program = prog;
  return GL_TRUE;
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
  memset(m, 0, sizeof(Mat4));
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

int main ( int argc, char *argv[] )
{
  unsigned int frames = 0;
  int   res;
  Mat4  viewMat;
  Mat4  rotMat;
  Mat4  modelMat;
  float aspect;

  // bcm_host_init();
  // res = WinCreate(&g_sc);

  X_init();

  XPending(xdisplay);

  if (!res) return 0;
  res = SurfaceCreate(&g_sc);
  if (!res) return 0;
  res = InitShaders(&g_program, vShaderSrc, fShaderSrc);
  if (!res) return 0;

  createBuffer();

  glUseProgram(g_program);
  g_sp.aPosition = glGetAttribLocation(g_program, "aPosition");
  g_sp.aTex = glGetAttribLocation(g_program, "aTex");
  g_sp.uVpMatrix = glGetUniformLocation(g_program, "uVpMatrix");
  g_sp.uModelMatrix = glGetUniformLocation(g_program, "uModelMatrix");

  aspect = (float)g_sc.width / (float)g_sc.height;
  makeProjectionMatrix(&g_sp.VpMatrix, 1, 1000, 53, aspect);
  makeUnit(&viewMat);
  setPosition(&viewMat, 0, 0, -2);
  mulMatrix(&g_sp.VpMatrix, &g_sp.VpMatrix, &viewMat);
  glUniformMatrix4fv(g_sp.uVpMatrix, 1, GL_FALSE, g_sp.VpMatrix.m);

  makeUnit(&modelMat);
  glUniformMatrix4fv(g_sp.uModelMatrix, 1, GL_FALSE, modelMat.m);

  makeUnit(&rotMat);
  setRotationX(&rotMat, 0.5); /* 30 degree/sec */

  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0f, 0.2f, 0.4f, 1.0f);

  /* 1200frame / 60fps = 20sec */
  while(frames < 1200) {
    // glViewport(0, 0, g_sc.width, g_sc.height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* X Rotation */
    mulMatrix(&modelMat, &modelMat, &rotMat);
    glUniformMatrix4fv(g_sp.uModelMatrix, 1, GL_FALSE, modelMat.m);

    Draw();
    eglSwapBuffers(g_sc.display, g_sc.surface);
    frames++;
  }
  return 0;
}
