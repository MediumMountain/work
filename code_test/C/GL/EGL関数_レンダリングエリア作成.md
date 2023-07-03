# EGL関数　レンダリングエリア作成

## eglCreateWindowSurface
```
EGLSurface eglCreateWindowSurface(	EGLDisplay display,
 	EGLConfig config,
 	NativeWindowType native_window,
 	EGLint const * attrib_list);
```

- ネイティブのディスプレイマネージャへの接続
- 事前に作成された、EGLConfig,windowを必要とする。（displayも）


```
eglCreateWindowSurface は、画面上の EGL ウィンドウ サーフェスを作成し、そのハンドルを返します。   
eglCreateWindowSurface の動作は、表示が属することを許可されるプラットフォームのセットと、native_window の実際のタイプが実装固有であることを除いて、eglCreatePlatformWindowSurface の動作と同じです。  
```