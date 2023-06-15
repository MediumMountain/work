# ウィンドウシステムとの通信(eglGetDisplay)
- グルーレイヤ


# (eglInitialize)

# ウィンドウ作成

# レンダリングコンテキスト作成

# コンテキストをカレントにする




# 関数

## eglGetProcAddress

```
void (* eglGetProcAddress(	char const * procname))(void);
```

- eglGetProcAddress は、procname で指定されたクライアント API または EGL 関数のアドレスを返します。 
- procname は、NULL で終了する文字列である必要があります。 
- 返されるポインタは、対応する API または拡張仕様の関数の定義に一致する関数ポインタにキャストされる必要があります。 
- 戻り値 NULL は、特定の関数が実装に存在しないことを示します。

- NULL 以外の戻り値は、拡張関数が実行時に実際にサポートされることを保証しません。 
- クライアントは、OpenGL および OpenGL ES 拡張機能の glGetString(GL_EXTENSIONS) などの対応するクエリも作成する必要があります。 
- vgGetString(VG_EXTENSIONS) OpenVG 拡張機能の場合。 eglQueryString(display, EGL_EXTENSIONS); または、非拡張関数の EGL またはクライアント API バージョンを照会して、関数が EGL または特定のクライアント API コンテキストでサポートされているかどうかを判別します。

- eglGetProcAddress によって返されるクライアント API 関数ポインターは、表示および現在バインドされているクライアント API コンテキストとは独立しており、関数をサポートする任意のクライアント API コンテキストによって使用できます。

- eglGetProcAddress は、実装によってサポートされるすべての EGL およびクライアント API 関数 (それらの関数が拡張であるかどうか、および現在のクライアント API コンテキストによってサポートされるかどうか) について照会できます。

- eglGetProcAddress でクエリ可能な関数の場合、実装では、それらの関数を実装するオブジェクト ライブラリから静的にそれらの関数をエクスポートすることも選択できます。 
- ただし、ポータブル クライアントはこの動作に依存できません。