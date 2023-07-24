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



## REFERENCE

https://gist.github.com/gyohk/abf13dbcb5be750b3b021752b280ccd3