# VBO（VBO＝Vertex Buffer Object）
- VBOは描画に必要な頂点情報（頂点座標、色、法線、テクスチャ座標など）を格納するバッファ
- VBOは以下のような手順で設定を行う。
    1. glGenBuffers関数でVBO作成→glBindBuffer関数でbind
    1. glBufferData関数で作成したVBOにデータを格納
    1. glVertexAttribPointer関数でVBOをどのlayoutにするかを設定



## glGenBuffers	
- バッファオブジェクトを作成
- n 個の頂点バッファオブジェクトを作成し, そのオブジェクト名 (整数値で表される識別子) を buffers に指定された配列の要素に格納

```
void glGenBuffers(GLsizei n, GLuint *buffers)
/*例：
GLuint vbo;
glGenBuffers(1, &vbo);
*/
```



## glBindBuffer	
- バッファオブジェクトをシェーダのデータとして指定
- bufferにしていされたVBOをtargetにbind

```
void glBindBuffer(GLenum target, GLuint buffer)
//例：glBindBuffer(GL_ARRAY_BUFFER, vbo);
```


|値	|説明|
|:------:|:-------:|  
|GL_ARRAY_BUFFER|	普通は大体これにしておけば良い。VBOに頂点情報（座標、色など）が格納されている時に使う。|glDrawArrays()関数で描画する時に使用|
|GL_ELEMENT_ARRAY_BUFFER|	GL_ARRAY_BUFFERはglDrawArrays()関数を使う時に使用するのに対し、glDrawlements()関数で描画するときに使用|
|GL_TEXTURE_BUFFER|	テクスチャデータを格納|
|GL_UNIFORM_BUFFER|	Uniformデータを格納|
|GL_COPY_READ_BUFFER|	Buffer copy source|
|GL_COPY_WRITE_BUFFER|	Buffer copy destination|
|GL_PIXEL_PACK_BUFFER|	ピクセルデータをPBOへ転送|
|GL_PIXEL_UNPACK_BUFFER|	Pixel read target|
|GL_TRANSFORM_FEEDBACK_BUFFER|	Transform feedback buffer|
|||  


## glBufferData	
- VBOのバッファにデータを格納

```
void glBufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage)
//例：glBufferData(GL_ARRAY_BUFFER, sizeof (GLfloat) * 2 * vertices, position, GL_STATIC_DRAW);
```

## glVertexAttribPointer
- VBOを頂点シェーダで利用するための準備


# VAO（Vertex Array Object）
- VBOをまとめるディスクリプタ―（Descriptor）。「ディスクリプタ―」とは、「GPUに送ったデータをシェーダーで使用するための仕様書」のようなもの

- VAOには、2つの機能がある。
1. バッファオブジェクトの属性をまとめる機能
　複数のVBOの頂点属性(位置/色/法線など)を一つのVAOへまとめる役割をもつ。頂点属性だけでなくインデックスバッファや、インダイレクトバッファ等のバッファオブジェクトもまとめることができる。
2. シェーダー側への橋渡しであるインターフェイス的な機能
　シェーダー側でC++側で生成した頂点データの処理を行うとき、どれが頂点の位置で色で法線なのかわかる必要がある。VAOはこれを解決する橋渡し的な機能を持っている。

## glGenVertexArrays

```
void glGenVertexArrays(GLsizei n, GLuint *arrays)
/* 例：
GLuint vao;
glGenVertexArrays(1, &vao);
*/
```

## glBindVertexArray

```
void glBindVertexArray(GLuint array)
//例：glBindVertexArray(vao);
```



# 描画手順
1. 頂点データを準備
1. VBOに頂点データを格納
1. VAOにVBOをまとめる
1. シェーダーを適用し、ドローコールで描画