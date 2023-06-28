# EGL関数　サーフェスのコンフィグレーション

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
- "EGLに"指定したEGLConfigと一致するものを選択させる。
    - 属性のリスト※を与える必要がある。

```
eglChooseConfig は、attrib_list で指定された属性に一致するすべての EGL フレーム バッファー構成のリストを configs で返します。 返された EGLConfig は、EGL フレーム バッファー構成を必要とする任意の EGL 関数で使用できます。

configs が NULL でない場合、最大 config_size の configs が configs が指す配列に返されます。 実際に返される構成の数は *num_config に返されます。

configs が NULL の場合、configs では構成は返されません。 代わりに、attrib_list に一致する構成の合計数が *num_config で返されます。 この場合、config_size は無視されます。 この形式の eglChooseConfig は、一致するフレーム バッファ構成の数を決定するために使用され、その後、他のすべてのパラメータを変更せずに eglChooseConfig への別の呼び出しに渡す EGLConfig の配列を割り当てます。

ブール属性を含む attrib_list 内のすべての属性の直後に、対応する必要な値が続きます。 リストは EGL_NONE で終了します。 属性が attrib_list で指定されていない場合は、デフォルト値 (以下を参照) が使用されます (属性は暗黙的に指定されていると言われます)。 たとえば、EGL_DEPTH_SIZE が指定されていない場合は、ゼロとみなされます。 一部の属性では、デフォルトは EGL_DONT_CARE であり、この属性には任意の値を使用できることを意味するため、属性はチェックされません。

属性は、属性固有の方法で照合されます。 EGL_LEVEL などの一部の属性は、指定された値と正確に一致する必要があります。 EGL_RED_SIZE などのその他の値は、指定された最小値以上である必要があります。 すべての属性に一致する EGL フレーム バッファー構成が複数見つかった場合は、「最良の」一致基準に従ってソートされた構成のリストが返されます。 各属性の一致基準と正確な並べ替え順序は以下で定義されます。

ビットマスク属性 EGL_CONFORMANT、EGL_RENDERABLE_TYPE、および EGL_SURFACE_TYPE の場合、照合時にマスクのゼロ以外のビットのみが考慮されます。 指定されたビットマスク属性値内のゼロのビットは、結果として得られる構成の属性値内で 0 または 1 のいずれかになります。

attrib_list に表示される可能性のある属性、その説明、および許可される値は次のとおりです。※
```



## eglgetconfigattrib 
```
EGLBoolean eglGetConfigAttrib(	EGLDisplay display, EGLConfig config, EGLint attribute, EGLint * value);
```

- EGLCinfigに関連づけられた属性を問い合わせる

- config の属性の値を値として返す。
- 指定された属性に一致する EGL フレーム バッファー構成のリストを返す。



## ※config 属性

EGL_ALPHA_SIZE
Returns the number of bits of alpha stored in the color buffer.

EGL_ALPHA_MASK_SIZE
Returns the number of bits in the alpha mask buffer.

EGL_BIND_TO_TEXTURE_RGB
Returns EGL_TRUE if color buffers can be bound to an RGB texture, EGL_FALSE otherwise.

EGL_BIND_TO_TEXTURE_RGBA
Returns EGL_TRUE if color buffers can be bound to an RGBA texture, EGL_FALSE otherwise.

EGL_BLUE_SIZE
Returns the number of bits of blue stored in the color buffer.

EGL_BUFFER_SIZE
Returns the depth of the color buffer. It is the sum of EGL_RED_SIZE, EGL_GREEN_SIZE, EGL_BLUE_SIZE, and EGL_ALPHA_SIZE.

EGL_COLOR_BUFFER_TYPE
Returns the color buffer type. Possible types are EGL_RGB_BUFFER and EGL_LUMINANCE_BUFFER.

EGL_CONFIG_CAVEAT
Returns the caveats for the frame buffer configuration. Possible caveat values are EGL_NONE, EGL_SLOW_CONFIG, and EGL_NON_CONFORMANT.

EGL_CONFIG_ID
Returns the ID of the frame buffer configuration.

EGL_CONFORMANT
Returns a bitmask indicating which client API contexts created with respect to this config are conformant.

EGL_DEPTH_SIZE
Returns the number of bits in the depth buffer.

EGL_GREEN_SIZE
Returns the number of bits of green stored in the color buffer.

EGL_LEVEL
Returns the frame buffer level. Level zero is the default frame buffer. Positive levels correspond to frame buffers that overlay the default buffer and negative levels correspond to frame buffers that underlay the default buffer.

EGL_LUMINANCE_SIZE
Returns the number of bits of luminance stored in the luminance buffer.

EGL_MAX_PBUFFER_WIDTH
Returns the maximum width of a pixel buffer surface in pixels.

EGL_MAX_PBUFFER_HEIGHT
Returns the maximum height of a pixel buffer surface in pixels.

EGL_MAX_PBUFFER_PIXELS
Returns the maximum size of a pixel buffer surface in pixels.

EGL_MAX_SWAP_INTERVAL
Returns the maximum value that can be passed to eglSwapInterval.

EGL_MIN_SWAP_INTERVAL
Returns the minimum value that can be passed to eglSwapInterval.

EGL_NATIVE_RENDERABLE
Returns EGL_TRUE if native rendering APIs can render into the surface, EGL_FALSE otherwise.

EGL_NATIVE_VISUAL_ID
Returns the ID of the associated native visual.

EGL_NATIVE_VISUAL_TYPE
Returns the type of the associated native visual.

EGL_RED_SIZE
Returns the number of bits of red stored in the color buffer.

EGL_RENDERABLE_TYPE
Returns a bitmask indicating the types of supported client API contexts.

EGL_SAMPLE_BUFFERS
Returns the number of multisample buffers.

EGL_SAMPLES
Returns the number of samples per pixel.

EGL_STENCIL_SIZE
Returns the number of bits in the stencil buffer.

EGL_SURFACE_TYPE
Returns a bitmask indicating the types of supported EGL surfaces.

EGL_TRANSPARENT_TYPE
Returns the type of supported transparency. Possible transparency values are: EGL_NONE, and EGL_TRANSPARENT_RGB.

EGL_TRANSPARENT_RED_VALUE
Returns the transparent red value.

EGL_TRANSPARENT_GREEN_VALUE
Returns the transparent green value.

EGL_TRANSPARENT_BLUE_VALUE
Returns the transparent blue value.



## Errors
EGL_FALSE is returned on failure, EGL_TRUE otherwise. value is not modified when EGL_FALSE is returned.

EGL_BAD_DISPLAY is generated if display is not an EGL display connection.

EGL_NOT_INITIALIZED is generated if display has not been initialized.

EGL_BAD_CONFIG is generated if config is not an EGL frame buffer configuration.

EGL_BAD_ATTRIBUTE is generated if attribute is not a valid frame buffer configuration attribute.