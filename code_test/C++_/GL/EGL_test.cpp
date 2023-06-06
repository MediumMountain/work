#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <iostream>
#include <unistd.h>
#include <unistd.h>

typedef struct { int w, h; } Size;
#define MAXSIZE  1024 * 1024 * 4
static unsigned char g_bmpbuffer[MAXSIZE];

int LoadFile(char *filename, void *buffer);
int initializeEGL(Display *xdisp, Window &xwindow, EGLDisplay &display, EGLContext &context, EGLSurface &surface);

int LoadFile(char *filename, void *buffer)
{
  FILE *fp;
  long fsize;
  int n_read = 0;

  fp = fopen(filename, "rb");
  if (fp > 0) {
    // 先にファイルサイズを確認
    fseek(fp, 0L, SEEK_END);
    fsize = ftell(fp);
    if (fsize >= MAXSIZE) {
      fclose(fp);
      return -1;
    }
    // ファイルを先頭からすべて読み込む
    fseek(fp, 0L, SEEK_SET);
    n_read = fread((void *)buffer, 1, fsize, fp);
    fclose(fp);
    return n_read;
  }
  return -1;
}


int main()
{
    //画像読み込み
    char path[] = "./IMG.jpg";
    int size = LoadFile(path, g_bmpbuffer);
    printf("LoadFile %d \n", size);

    //初期化
    Display *xdisplay = XOpenDisplay(nullptr);
    if (xdisplay == nullptr)
    {
        std::cerr << "Error XOpenDisplay." << std::endl;
        exit(EXIT_FAILURE);
    }

    Window xwindow = XCreateSimpleWindow(xdisplay, DefaultRootWindow(xdisplay), 100, 100, 640, 480,
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

    //メインループ
    // mainloop(xdisplay, display, surface);

    // destroyEGL(display, context, surface);
    // XDestroyWindow(xdisplay, xwindow);
    // XCloseDisplay(xdisplay);

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