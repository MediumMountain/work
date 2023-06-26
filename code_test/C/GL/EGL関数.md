# EGL関数

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



## eglGetConfigs 
```
EGLBoolean eglGetConfigs(	EGLDisplay display,
 	EGLConfig * configs,
 	EGLint config_size,
 	EGLint * num_config);
```
- ディスプレイのすべての EGL フレーム バッファー構成のリストを返す。
    - EGLConfigを返す。
- レンダリングサーフェスにどのようなタイプとコンフィグレーションがあるのかを特定する。
    1. 全てのサーフェスのコンフィグレーションを問い合わせて最適なものを（自分で）選択する。
    1. 必要条件を1組指定して合うものをEGLに推薦させる

### 使用方法  
1. configsにNULLを指定する方法
    - 成功すればEGL_TRUEが返り、numConfigsに使用できるEGLConfigの数を返す。

1. EGLConfig型配列を渡す方法
    - 第三引数に確保した配列のサイズを入れる。
    - 呼び出しが完了すると第四引数は変更されたconfigsのエントリ数に更新される。



```
eglGetConfigs は、指定されたディスプレイで使用できるすべての EGL フレーム バッファー構成のリストを返します。 リスト内の項目は、EGL フレーム バッファー構成を必要とする任意の EGL 関数で使用できます。
NULL として指定された場合、configs は値を返しません。 これは、すべてのフレーム バッファ構成の数だけをクエリする場合に便利です。
eglGetConfigAttrib を使用して、フレーム バッファ構成の個々の属性値を取得します。

エラー
失敗した場合は EGL_FALSE が返され、失敗した場合は EGL_TRUE が返されます。 EGL_FALSE が返された場合、configs と num_config は変更されません。
EGL_BAD_DISPLAY は、ディスプレイが EGL ディスプレイ接続でない場合に生成されます。
表示が初期化されていない場合は、EGL_NOT_INITIALIZED が生成されます。
num_config が NULL の場合、EGL_BAD_PARAMETER が生成されます。
```


## eglChooseConfig 

```
EGLBoolean eglChooseConfig(	EGLDisplay display,
 	EGLint const * attrib_list,
 	EGLConfig * configs,
 	EGLint config_size,
 	EGLint * num_config);
```

- 指定された属性に一致する EGL フレーム バッファー構成のリストを返す。

```
eglChooseConfig は、attrib_list で指定された属性に一致するすべての EGL フレーム バッファー構成のリストを configs で返します。 返された EGLConfig は、EGL フレーム バッファー構成を必要とする任意の EGL 関数で使用できます。

configs が NULL でない場合、最大 config_size の configs が configs が指す配列に返されます。 実際に返される構成の数は *num_config に返されます。

configs が NULL の場合、configs では構成は返されません。 代わりに、attrib_list に一致する構成の合計数が *num_config で返されます。 この場合、config_size は無視されます。 この形式の eglChooseConfig は、一致するフレーム バッファ構成の数を決定するために使用され、その後、他のすべてのパラメータを変更せずに eglChooseConfig への別の呼び出しに渡す EGLConfig の配列を割り当てます。

ブール属性を含む attrib_list 内のすべての属性の直後に、対応する必要な値が続きます。 リストは EGL_NONE で終了します。 属性が attrib_list で指定されていない場合は、デフォルト値 (以下を参照) が使用されます (属性は暗黙的に指定されていると言われます)。 たとえば、EGL_DEPTH_SIZE が指定されていない場合は、ゼロとみなされます。 一部の属性では、デフォルトは EGL_DONT_CARE であり、この属性には任意の値を使用できることを意味するため、属性はチェックされません。

属性は、属性固有の方法で照合されます。 EGL_LEVEL などの一部の属性は、指定された値と正確に一致する必要があります。 EGL_RED_SIZE などのその他の値は、指定された最小値以上である必要があります。 すべての属性に一致する EGL フレーム バッファー構成が複数見つかった場合は、「最良の」一致基準に従ってソートされた構成のリストが返されます。 各属性の一致基準と正確な並べ替え順序は以下で定義されます。

ビットマスク属性 EGL_CONFORMANT、EGL_RENDERABLE_TYPE、および EGL_SURFACE_TYPE の場合、照合時にマスクのゼロ以外のビットのみが考慮されます。 指定されたビットマスク属性値内のゼロのビットは、結果として得られる構成の属性値内で 0 または 1 のいずれかになります。

attrib_list に表示される可能性のある属性、その説明、および許可される値は次のとおりです。
```



## eglgetconfigattrib 
```
EGLBoolean eglGetConfigAttrib(	EGLDisplay display, EGLConfig config, EGLint attribute, EGLint * value);
```

- config の属性の値を値として返す。
- 指定された属性に一致する EGL フレーム バッファー構成のリストを返す。
