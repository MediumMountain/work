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



## eglCreatePlatformWindowSurface
```
EGLSurface eglCreatePlatformWindowSurface(	EGLDisplay display,
 	EGLConfig config,
 	void * native_window,
 	EGLAttrib const * attrib_list);
```

```
eglCreatePlatformWindowSurface は、画面上の EGL ウィンドウ サーフェスを作成し、そのハンドルを返します。 互換性のある EGLConfig で作成された任意の EGL コンテキストを使用して、このサーフェスにレンダリングできます。

eglCreatePlatformWindowSurface がウィンドウ サーフェスの作成に失敗した場合は、EGL_NO_SURFACE が返されます。

ative_window は、display と同じプラットフォームに属している必要があり、EGL は、返された EGLSurface が同じプラットフォームに属していると見なします。 ディスプレイが属するプラットフォームを定義する EGL 拡張機能は、native_window パラメーターの要件も定義します。

表面属性は、EGL_NONE で終わる属性と値のペアのリストとして指定されます。 受け入れられる属性は次のとおりです。

EGL_GL_COLORSPACE
サーフェスにレンダリングするときに OpenGL および OpenGL ES によって使用されるカラー スペースを指定します。 その値が EGL_GL_COLORSPACE_SRGB の場合、非線形で知覚的に均一な色空間が想定され、対応する GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 値は GL_SRGB になります。 その値が EGL_GL_COLORSPACE_LINEAR の場合、対応する GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 値が GL_LINEAR である線形色空間が想定されます。 EGL_GL_COLORSPACE のデフォルト値は EGL_GL_COLORSPACE_LINEAR です。

EGL_GL_COLORSPACE 属性は、sRGB フレームバッファをサポートする OpenGL および OpenGL ES コンテキストによってのみ使用されることに注意してください。 EGL 自体は複数の色空間モデルを区別しません。 詳細については、OpenGL 4.6 および OpenGL ES 3.2 仕様の「sRGB 変換」セクションを参照してください。

EGL_RENDER_BUFFER
クライアント API をウィンドウにレンダリングするためにどのバッファを使用するかを指定します。 その値が EGL_SINGLE_BUFFER の場合、クライアント API は表示されているウィンドウに直接レンダリングする必要があります。 その値が EGL_BACK_BUFFER の場合、クライアント API はバック バッファーにレンダリングされる必要があります。 EGL_RENDER_BUFFER のデフォルト値は EGL_BACK_BUFFER です。

クライアント API は、要求されたレンダリング バッファーを尊重できない場合があります。 コンテキストによってレンダリングされる実際のバッファを決定するには、eglQueryContext を呼び出します。

EGL_VG_ALPHA_FORMAT
サーフェスにレンダリングするときに OpenVG によってアルファ値がどのように解釈されるかを指定します。 その値が EGL_VG_ALPHA_FORMAT_NONPRE の場合、アルファ値は事前乗算されません。 その値が EGL_VG_ALPHA_FORMAT_PRE の場合、アルファ値は事前に乗算されます。 EGL_VG_ALPHA_FORMAT のデフォルト値は EGL_VG_ALPHA_FORMAT_NONPRE です。

EGL_VG_COLORSPACE
サーフェスにレンダリングするときに OpenVG によって使用される色空間を指定します。 その値が EGL_VG_COLORSPACE_sRGB の場合、VG_s* 形式の対応する VGImageFormat を使用して、非線形で知覚的に均一な色空間が想定されます。 その値が EGL_VG_COLORSPACE_LINEAR の場合、VG_l* 形式の対応する VGImageFormat を持つ線形色空間が想定されます。 EGL_VG_COLORSPACE のデフォルト値は EGL_VG_COLORSPACE_sRGB です。

構成に関して作成された EGL レンダリング コンテキストは、サーフェスへのレンダリングに使用できます。 eglMakeCurrent を使用して、EGL レンダリング コンテキストをサーフェスにアタッチします。

eglQuerySurface を使用して構成の ID を取得します。

eglDestroySurface を使用してサーフェスを破棄します。

```
