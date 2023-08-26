# GLSL バージョン

||                 GLSL|     shader 内の指定||  
|:------|:--------:|:--------:|:--------:|  
|OpenGL ES 2.0    |1.0      |#version 100||
|OpenGL 2.0       |1.1      |#version 110||
|OpenGL 2.1       |1.2      |#version 120||
|OpenGL 3.0       |1.3      |#version 130||
|OpenGL 3.1       |1.4      |#version 140||
|OpenGL 3.2       |1.5      |#version 150 |[core/compatibility]
|OpenGL ES 3.0    |3.0      |#version 300 es||
|OpenGL 3.3       |3.3      |#version 330 |[core/compatibility]
|OpenGL 4.0       |4.0      |#version 400 |[core/compatibility]
|OpenGL 4.1       |4.1      |#version 410 |[core/compatibility]
|OpenGL 4.2       |4.2      |#version 420 |[core/compatibility]
|OpenGL 4.3       |4.3      |#version 430 |[core/compatibility/es]


- インクルードするファイル、シェーダの記述内容に注意する。
1. OpenGL 2.0
```
    const char *vshader = R"(
        attribute vec4 vPosition;
        attribute vec2 a_texCoord;
        varying vec2 v_texCoord;
        uniform mediump mat4 mRotation;
        void main() {
            gl_Position = mRotation * vPosition;
            v_texCoord  = a_texCoord;
        }
    )";
```
1. OpenGL ES 3.0
```
	const char* vshader =
		"#version 300 es\n"
		"layout(location = 0) in vec3 position;\n"
		"layout(location = 1) in vec2 vuv;\n"
        "out vec2 Flag_uv;\n"
		"void main(void) {\n"
            "Flag_uv  = vuv;\n"
			"gl_Position = vec4(position, 1.0f);\n"
		"}\n";
```


# GLSL文法

## 変数

| 変数クラス |型 |   
|:------|:--------:| 
|スカラー	|float, int, bool	|
|浮動小数点ベクトル|float, vec2,3,4|
|整数ベクトル|	int, ivec2,3,4|
|ブール型ベクトル|bool, bvec2,3,4|
|行列|	mat2,3,4|



## attribute
- 頂点の属性を宣言する。attribute 変数は読込み専用で、頂点シェーダが実行されるときに OpenGL が自動的に値を代入する。（代入するとコンパイルエラーになる）


## mediump
- float は 4byte だが、毎秒数百万という頂点数を処理することにもなる OpenGL では、ほんの僅かな計算量の増加がクリティカルになる。

- そこで、GLSL ES では、処理精度の指定を強制している。


| 識別子 | 精度 | スピード | 目安 |  
|:------|:--------:|:-------:|-------:|  
|highp	|高	|低速	|絶対値が1.0以上|
|mediump|	中|	中速|	絶対値が1.0以下|
|lowp|	低|	高速|	絶対値が1.0以下で、分解能が低くても問題無い|



## main
- GLSLは、"void main()"関数から開始される。（エントリーポイント）
- main() は引数を受け取らず、欲しい情報は attribute 等によって受け取る。

- サンプルでは attr_pos で受け取った頂点の位置情報を gl_Position に代入している。
    - これは組込み変数で、頂点シェーダから位置情報を受け取るという役割を持つ。

- 頂点シェーダから受け取った gl_Position は、OpenGL に規定された処理が加えられ、後半のフラグメントシェーダの処理が始まる。

- 頂点シェーダは頂点の数だけ実行される。また gl_Position は main() が呼び出されるたびに初期化される。
    - なので、前回の描画結果が次の描画に影響を与えるということは一切ない。
    - そして、呼び出しはGPUの複数コア・複数スレッドによって 並列的に呼び出される。
    - GLSL ES の独特な記法と制約は、並列実行を効率よく行うためでもある。

## uniform 
- attribute変数は「頂点から情報を受け取る」方法でシェーダに情報を伝えていたが、フラグメントシェーダは attribute 変数を受け取ることはできない。
- フラグメントシェーダは、 uniform変数 を利用することで、アプリから情報を受け取ることができる。

- attribute変数が「頂点ごとの情報」であるのに対し、uniform変数は アプリが設定した値から一切変更されない という特徴がある。
- ピクセル色は低精度でもモバイルディスプレイの色情報を表現できるので、lowp で宣言している。


## varying キーワード
```
"varying lowp vec4 vary_color;"
```

- varying 変数は、頂点シェーダからフラグメントシェーダへ値を渡す際に用いられる。
- 頂点シェーダが書き込んだ varying 変数はある特定の処理を施されてフラグメントシェーダに渡される。
- 両方で同じ型・同じ変数名で定義しなければならない。
- gl_Position などの組み込み変数は特定用途でしか利用できないが、varying変数は汎用的に値を受け渡すことができる。
- varyingという名の通り、渡される際に値が変化する。

### varying 変数の制限
- varying変数は定義できる変数の個数が非常に少ない。
- Nexus5 で、16 とか。glGetIntegerv(GL_MAX_VARYING_VECTORS, &num) で取得できる。超えたらコンパイル失敗。


### Version3.0以降
```
先述のとおり、GLSL ES 3.0 は、これまでの 1.0 と比較して大きくシェーダの記述の仕方が変わっています。
そのなかでも、特に従来の GLSL に慣れている人が戸惑うと思われるのが attribute と varying の廃止 だと思います。これは使おうと思えば使えるとかそういうことではなく「完全な廃止」です。つまり仮に記述したとしても、これは構文エラーになります。
GLSL ES 3.0 では、これらの代わりに in や out を使います。
これまでは頂点属性としての入力は attribute 修飾子付きの変数によって行なっていましたが、この attribute 修飾子の代わりに in 修飾子付きの変数を使います。これは要するに、シェーダに外部から入ってくるデータである、という意味で捉えればいいわけですね。
そしてこれと同様に、varying 修飾子付きの変数についても、頂点シェーダからフラグメントシェーダに出力する際には out を使い、フラグメントシェーダで入力として受け取る際には in を使うわけです。
これまでは attribute と varying というようにそれぞれ別々の名称になっていたものが、共通の in と out によって表現されるようになったわけです。
ただし、uniform 修飾子付きの変数についてはこれまでどおりの記述方法を用います。これだって入力じゃないか！ と思う人もいるかと思いますが、uniform 修飾子付きの変数には in や out といった修飾子は使えませんので、間違えないようにしましょう。
```


## ifキーワード
```
if (texture2D(tex_mask, vary_uv).r == 0.0) {
    discard;
}
```
- tex_mask のピクセルを読み取り r 要素をチェック。
- texture2D の戻り値は テクセルの色 であり、その型は vec4 であり、vec4 は xyzw のメンバを持つが、ここでは r でアクセスしている。
- OpenGL ES のベクトル型は、シェーダー記述を用意にするために様々な便宜が図られており、その一つが 要素名の別名アクセスになる。

vec4の場合、
- x, y, z, w （ベクトル要素）
- r, g, b, a （色アクセス向け別名）
- s, t, p, q （テクスチャアクセス向け別名）
- [0], [1], [2], [3] （配列アクセス向け別名）

なので、ここでは r でも x でも s や [0] でアクセスしても同じ要素を見ている。


## discard 命令
- GLSL ES の特殊鋼分の一つ。関数や式ではなく、discard: と記述するだけ。
- 上の例では「ピクセルの色が黒かった場合」に discard 命令を発行している。
- これは 描画されないピクセル であり、これが実行されると「このピクセルは不要である」ことが GPU に伝えられる。命令を受けた GPU はフラグメントシェーダの実行を中断し、そのピクセルの描画をキャンセルする。最終的にそのピクセルは描画されずに ポリゴンに穴を開ける ことができる。




## Shader記述時の注意点
- for文のループ回数を動的に出来ない。
- if文はあまり使わない方がいいらしい (処理負荷が高い) →　ifの分岐を避ける
    - 3項演算子
    - stepの用法

- 基本bit演算は使えない。将来のために予約はされている。拡張を使えば使える。
- 配列も基本的には使わない方がいい


### 行列は転置された状態になる
- 定義する上で行に見えるところはカラム（列）になる。　→　転置行列を定義している




## REFERENCE

https://gist.github.com/gyohk/abf13dbcb5be750b3b021752b280ccd3

GLSL : don't use "if"  
https://note.com/nobuhirosaijo/n/n606a3f5d8e89

【GLSL TIPS】行列の宣言と計算の注意点  
https://blog.narumium.net/2020/05/27/%e3%80%90glsl-tips%e3%80%91%e8%a1%8c%e5%88%97%e3%81%ae%e5%ae%a3%e8%a8%80%e3%81%a8%e8%a8%88%e7%ae%97%e3%81%ae%e6%b3%a8%e6%84%8f%e7%82%b9/