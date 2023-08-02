
# EGL
- OpenGL ESのようなレンダリングAPI群とネイティブウィンドウシステムとのインタフェース
    - OpenGL ESの実装にEGLは必須ではない。
    - どのインタフェースがサポートされているのかは、使用しているプラットフォームベンダのドキュメントを参照


- パワーマネジメント、１つのプロセス内での複数のレンダリングコンテキストのサポート、１つのプロセス内でのレンダリングコンテキスト間でのオブジェクトの共有などの機能も提供

# ウィンドウシステムとの通信(eglGetDisplay)
- グルーレイヤ


# (eglInitialize)

# ウィンドウ作成

# レンダリングコンテキスト作成

# コンテキストをカレントにする




main
window作成
egl初期化関数
eglGetDisplay
eglInitialize
eglChooseConfig
eglCreateWindowSurface
eglCreateContext
eglMakeCurrent
シェーダ作成
LoadShader関数
glCreateShader
glShaderSource
glCompileShader
glGetShaderiv(確認用)
glCreateProgram
glAttachShader(vertex)
glAttachShader(fragment)
glLinkProgram
glGetProgramiv(確認用)
glDeleteProgram
glDeleteShader(vertex)
glDeleteShader(fragment)
バッファ作成
1.glGenBuffers(vertex buffer)
2.glBindBuffer(vertex buffer)
3.glBufferData(vertex buffer)
4.glGenBuffers(index buffer)
5.glBindBuffer(index buffer)
6.glBufferData(index buffer)
描画準備
メインループ
ビューポート指定
glViewport
バッファクリア
glClear
その他
glUniformXXXX
描画
glUseProgram
glBindBuffer(vbo)
glBindBuffer(ibo)
glEnableVertexAttribArray(position)
glEnableVertexAttribArray(Tex)
glVertexAttribPointer(position)
glVertexAttribPointer(Tex)
glEnableVertexAttribArray
glDrawElements(またはglDrawArray)
eglSwapBuffers


## REFERENCE
EGLフロー  
https://www.qoosky.io/techs/93ef003749