# GL関数

## glCreateShader	
```
GLuint glCreateShader(	GLenum shaderType);
```

- シェーダオブジェクトの作成
- 作成するシェーダの種類を指定します。 次のいずれかである必要があります。
	1. GL_COMPUTE_SHADER, 
	1. GL_VERTEX_SHADER, 
	1. GL_TESS_CONTROL_SHADER, 
	1. GL_TESS_EVALUATION_SHADER, 
	1. GL_GEOMETRY_SHADER,
	1. GL_FRAGMENT_SHADER.

```
glCreateShader は空のシェーダ オブジェクトを作成し、それを参照できるゼロ以外の値を返します。 シェーダ オブジェクトは、シェーダを定義するソース コード文字列を維持するために使用されます。 shaderType は作成されるシェーダのタイプを示します。 5 種類のシェーダがサポートされています。 GL_COMPUTE_SHADER タイプのシェーダーは、プログラマブル コンピューティング プロセッサ上で実行することを目的としたシェーダーです。 GL_VERTEX_SHADER タイプのシェーダは、プログラマブル頂点プロセッサ上で実行することを目的としたシェーダです。 GL_TESS_CONTROL_SHADER タイプのシェーダーは、制御ステージのプログラマブル テッセレーション プロセッサ上で実行することを目的としたシェーダーです。 GL_TESS_EVALUATION_SHADER タイプのシェーダーは、評価段階でプログラマブル テッセレーション プロセッサ上で実行することを目的としたシェーダーです。 GL_GEOMETRY_SHADER タイプのシェーダは、プログラマブル ジオメトリ プロセッサ上で実行することを目的としたシェーダです。 GL_FRAGMENT_SHADER タイプのシェーダは、プログラマブル フラグメント プロセッサ上で実行することを目的としたシェーダです。


バッファーオブジェクトやテクスチャオブジェクトと同様に、シェーダーオブジェクトの名前空間は、サーバー側が同じアドレス空間でコンテキストを共有している限り、コンテキストのセット全体で共有できます。 名前空間がコンテキスト全体で共有される場合、関連するオブジェクトとそれらに付随するデータも共有されます。

アプリケーションは、オブジェクトが異なる実行スレッドからアクセスされたときに、全ての API 呼び出しを同期呼び出しに変換する責任があります。

GL_COMPUTE_SHADER は、GLバージョンが4.3以上の場合にのみ使用できます。
```

## glCreateProgram

## glShaderSource	
```
void glShaderSource(	GLuint shader,
 	GLsizei count,
 	const GLchar **string,
 	const GLint *length);
```

- シェーダソースの指定


```
glShaderSource は、シェーダー内のソース コードを、string で指定された文字列の配列内のソース コードに設定します。 以前にシェーダー オブジェクトに保存されていたソース コードは完全に置き換えられます。 配列内の文字列の数は count で指定されます。 長さが NULL の場合、各文字列は NULL で終了しているとみなされます。 length が NULL 以外の値の場合、string の対応する各要素の文字列長を含む配列を指します。 長さ配列の各要素には、対応する文字列の長さ (NULL 文字は文字列長の一部としてカウントされません)、または文字列が NULL で終了していることを示す 0 未満の値が含まれる場合があります。 現時点では、ソース コード文字列のスキャンや解析は行われません。 それらは指定されたシェーダ オブジェクトにコピーされるだけです。

ノート
OpenGL は、glShaderSource が呼び出されたときにシェーダー ソース コード文字列をコピーするため、アプリケーションは関数が返された直後にソース コード文字列のコピーを解放する可能性があります。

エラー
GL_INVALID_VALUE は、シェーダが OpenGL によって生成された値ではない場合に生成されます。

GL_INVALID_OPERATION は、シェーダがシェーダ オブジェクトでない場合に生成されます。

count が 0 未満の場合、GL_INVALID_VALUE が生成されます
```

- 2023/07/05
	- glGetShaderivがGL_FALSE
		- 懸念点
		1. shaderの書き方
			- テストプログラムはC++、実機用ソースはC++ソースだけど中身はCの記述(extern C)
		1. 第4引数がNULL
			- lengthにするべき？もしくは行末が正しくない？


## glCompileShader	
```
void glCompileShader(	GLuint shader);
```

- コンパイルするシェーダーオブジェクトを指定(shader)

```
glCompileShader は、 shader に指定されたシェーダーオブジェクトに保存されているソースコード文字列をコンパイルします。

コンパイルステータスは、シェーダーオブジェクトの状態の一部として保存されます。 この値は、シェーダーにエラーが無くコンパイルされ使用準備ができている場合は GL_TRUE、それ以外は GL_FALSE に設定されます。 これは、glGetShader を引数 shader と GL_COMPILE_STATUS を使用して呼び出すことで照会できます。

シェーダーのコンパイルは、OpenGL Shading Language Specificationで指定されているいくつかの理由で失敗する可能性があります。 コンパイル成功の可否に依らず、glGetShaderInfoLog を呼び出すことでシェーダーオブジェクトの情報ログからコンパイルに関する情報を取得できます。

ERROR
GL_INVALID_VALUE は、シェーダが OpenGL によって生成された値ではない場合に生成されます。
GL_INVALID_OPERATION は、シェーダがシェーダ オブジェクトでない場合に生成されます。
```

## glGetShaderInfoLog	

```
void glGetShaderInfoLog(	GLuint shader,
 	GLsizei maxLength,
 	GLsizei *length,
 	GLchar *infoLog);
```
- シェーダのコンパイルエラーログを取得

```
shader
情報ログを照会するシェーダーオブジェクトを指定します

maxLength
返される情報ログを保存するための文字バッファのサイズを指定します。

length
infoLog に返される文字列の長さを返します（nullターミネーターを除く）。

infoLog
情報ログを返すために使用される文字の配列を指定します。

glGetShaderInfoLog は、指定されたシェーダーオブジェクトの情報ログを返します。 シェーダーオブジェクトの情報ログは、シェーダーのコンパイル時に更新されます。 返される文字列はnull終端になっています。

glGetShaderInfoLog は、最大で maxLength 文字まで、可能な限り多くの情報ログを infoLog に返します。 null終端文字を除く実際に返される文字数は、length で指定されます。 返される文字列の長さが不要な場合は、引数 length に NULL を渡すことができます。 返された情報ログを保存するために必要なバッファーサイズは、glGetShader を GL_INFO_LOG_LENGTH で呼び出すことで取得できます。

シェーダーオブジェクトの情報ログは、診断メッセージ、警告メッセージ、および最後のコンパイル操作に関するその他の情報を含む文字列です。 シェーダーオブジェクトが作成されると、その情報ログは長さ0の文字列になります。

Notes
シェーダーオブジェクトの情報ログは、コンパイルプロセスに関する情報を伝達するためのOpenGL実装者の主要なメカニズムです。 従って、情報ログはコンパイルが成功した場合でも開発プロセス中にアプリケーション開発者に役立ちます。 アプリケーション開発者は、異なるOpenGL実装が同一の情報ログを生成することを期待すべきではありません。

ERROR
GL_INVALID_VALUE は、シェーダが OpenGL によって生成された値ではない場合に生成されます。
GL_INVALID_OPERATION は、シェーダがシェーダ オブジェクトでない場合に生成されます。
maxLength が 0 未満の場合、GL_INVALID_VALUE が生成されます。

```

これを書くと、このように
```
"warning C7502: OpenGL does not allow type suffix 'f' on constant literals
0(8) : warning C7503: OpenGL does not allow C-style casts
0(8) : warning C7503: OpenGL does not allow C-style casts
0(8) : warning C7503: OpenGL does not allow C-style casts
0(12) : warning C7011: implicit cast from "float" to "vec4"
0(13) : error C0000: syntax error, unexpected '}', expecting ',' or ';' at token "}"
0(4) : error C1068: too much data in type constructor"
```
何行目がエラーなのか教えてくれる。  
https://qiita.com/jasmingirl@github/items/135a58ff27e3c934d15c


## glGetShaderiv  
```
void glGetShaderiv(	GLuint shader,
 	GLenum pname,
 	GLint *params);
```
- シェーダの情報を取得


```
glGetShaderiv は、特定のシェーダ オブジェクトのパラメータの値を params で返します。 次のパラメータが定義されています。

GL_SHADER_TYPE
params は、シェーダが頂点シェーダ オブジェクトの場合は GL_VERTEX_SHADER を返し、シェーダがフラグメント シェーダ オブジェクトの場合は GL_FRAGMENT_SHADER を返します。

GL_DELETE_STATUS
params は、シェーダに現在削除のフラグが立てられている場合は GL_TRUE を返し、それ以外の場合は GL_FALSE を返します。

GL_COMPILE_STATUS
シェーダ コンパイラをサポートする実装の場合、params は、シェーダの最後のコンパイル操作が成功した場合は GL_TRUE を返し、それ以外の場合は GL_FALSE を返します。

GL_INFO_LOG_LENGTH
シェーダ コンパイラをサポートする実装の場合、params は、null 終了文字を含むシェーダの情報ログの文字数 (つまり、情報ログを格納するために必要な文字バッファのサイズ) を返します。 シェーダに情報ログがない場合は、値 0 が返されます。

GL_SHADER_SOURCE_LENGTH
シェーダ コンパイラをサポートする実装の場合、params は、null 終端文字を含む、シェーダのシェーダ ソースを構成するソース文字列の連結の長さを返します。 (つまり、シェーダ ソースを保存するために必要なキャラクタ バッファのサイズ)。 ソースコードが存在しない場合は0を返します。

NOTE
シェーダー コンパイラのサポートはオプションであるため、使用前に引数 GL_SHADER_COMPILER を指定して glGet を呼び出してクエリする必要があります。 glShaderSource、glCompileShader、glGetShaderPrecisionFormat、および glReleaseShaderCompiler はそれぞれ、GL_COMPILE_STATUS、GL_INFO_LOG_LENGTH、および GL_SHADER_SOURCE_LENGTH の glGetShaderiv クエリと同様に、シェーダ コンパイラをサポートしない実装で GL_INVALID_OPERATION を生成します。 このような実装では、代わりに、コンパイル済みのシェーダー バイナリを提供するための glShaderBinary の代替手段が提供されます。

エラーが発生した場合、params の内容は変更されません。

ERROR
pname が受け入れられる値ではない場合、GL_INVALID_ENUM が生成されます。
GL_INVALID_VALUE は、シェーダが OpenGL によって生成された値ではない場合に生成されます。
pname が GL_COMPILE_STATUS、GL_INFO_LOG_LENGTH、または GL_SHADER_SOURCE_LENGTH の場合、GL_INVALID_OPERATION が生成されますが、シェーダー コンパイラはサポートされていません。
GL_INVALID_OPERATION は、シェーダがシェーダ オブジェクトを参照していない場合に生成されます。

```


## glDeleteShader
```
void glDeleteShader(	GLuint shader);
```
- シェーダオブジェクトの削除

glDeleteShader はメモリを解放し、shader で指定されたシェーダ オブジェクトに関連付けられた名前を無効にします。 このコマンドは、glCreateShader への呼び出しの効果を効果的に元に戻します。

削除するシェーダ オブジェクトがプログラム オブジェクトにアタッチされている場合、そのシェーダ オブジェクトには削除のフラグが立てられますが、どのレンダリング コンテキストでもプログラム オブジェクトにアタッチされなくなるまでは削除されません（つまり、シェーダ オブジェクトは、どのレンダリング コンテキストからも切り離される必要があります. 削除される前に添付されていた場所はどこでも削除されます）。 シェーダの値 0 は黙って無視されます。

オブジェクトに削除のフラグが立てられているかどうかを確認するには、引数 shader と GL_DELETE_STATUS を指定して glGetShader を呼び出します。



glCreateProgram	プログラムオブジェクトの作成 ●

## glAttachShader
```
void glAttachShader(	GLuint program, GLuint shader);
```
- プログラムにシェーダを登録

完全なシェーダ プログラムを作成するには、リンクされるもののリストを指定する方法が必要です。 プログラム オブジェクトはこのメカニズムを提供します。 プログラム オブジェクト内で相互にリンクされるシェーダーは、まずそのプログラム オブジェクトにアタッチする必要があります。 glAttachShader は、shader で指定されたシェーダ オブジェクトを、program で指定されたプログラム オブジェクトにアタッチします。 これは、プログラム上で実行されるリンク操作にシェーダーが含まれることを示します。

シェーダ オブジェクトに対して実行できるすべての操作は、シェーダ オブジェクトがプログラム オブジェクトにアタッチされているかどうかに関係なく有効です。 ソース コードがシェーダ オブジェクトにロードされる前、またはシェーダ オブジェクトがコンパイルされる前に、シェーダ オブジェクトをプログラム オブジェクトにアタッチすることができます。 それぞれに完全なシェーダーの一部が含まれる可能性があるため、同じタイプの複数のシェーダー オブジェクトをアタッチすることが許可されます。 シェーダ オブジェクトを複数のプログラム オブジェクトにアタッチすることもできます。 プログラム オブジェクトにアタッチされているシェーダ オブジェクトが削除されると、削除のフラグが立てられ、glDetachShader が呼び出されて、アタッチされているすべてのプログラム オブジェクトからシェーダ オブジェクトがデタッチされるまで、削除は行われません。


glGetAttachedShaders は、プログラムにアタッチされたシェーダ オブジェクトの名前を返します。 プログラムにアタッチされているシェーダ オブジェクトの名前は、シェーダで返されます。 シェーダに書き込まれたシェーダ名の実際の数が count で返されます。 プログラムにシェーダ オブジェクトがアタッチされていない場合、count は 0 に設定されます。シェーダで返されるシェーダ名の最大数は、maxCount で指定されます。

実際に返される名前の数が必要ない場合 (たとえば、glGetProgram を呼び出して取得したばかりの場合)、count に NULL 値を渡すことができます。 プログラムにシェーダ オブジェクトがアタッチされていない場合、count には 0 の値が返されます。 アタッチされたシェーダの実際の数は、値 GL_ATTACHED_SHADERS を指定して glGetProgram を呼び出すことで取得できます。


## glLinkProgram
```
void glLinkProgram(	GLuint program);
```

- シェーダをプログラムにリンク

glLinkProgram は、program で指定されたプログラム オブジェクトをリンクします。 GL_VERTEX_SHADER タイプのシェーダ オブジェクトがプログラムにアタッチされている場合、それらはプログラマブル頂点プロセッサ上で実行される実行可能ファイルの作成に使用されます。 GL_GEOMETRY_SHADER タイプのシェーダ オブジェクトがプログラムにアタッチされている場合、それらはプログラマブル ジオメトリ プロセッサ上で実行される実行可能ファイルの作成に使用されます。 GL_FRAGMENT_SHADER タイプのシェーダ オブジェクトがプログラムにアタッチされている場合、それらはプログラマブル フラグメント プロセッサ上で実行される実行可能ファイルの作成に使用されます。

リンク操作のステータスは、プログラム オブジェクトの状態の一部として保存されます。 プログラム オブジェクトがエラーなくリンクされ、使用できる状態になっている場合、この値は GL_TRUE に設定され、それ以外の場合は GL_FALSE に設定されます。 引数プログラムと GL_LINK_STATUS を指定して glGetProgram を呼び出すことでクエリできます。

リンク操作が成功すると、プログラムに属するすべてのアクティブなユーザー定義のユニフォーム変数が 0 に初期化され、プログラム オブジェクトのアクティブなユニフォーム変数のそれぞれに、glGetUniformLocation を呼び出すことでクエリできる場所が割り当てられます。 また、汎用頂点属性インデックスにバインドされていないアクティブなユーザー定義属性変数は、この時点で汎用頂点属性インデックスにバインドされます。

https://registry.khronos.org/OpenGL-Refpages/gl4/html/glLinkProgram.xhtml


## glGetProgramiv
```
void glGetProgramiv( GLuint program, GLenum pname, GLint *params);
```
- プログラムの情報を取得

GL_DELETE_STATUS
params は、プログラムに現在削除のフラグが立てられている場合は GL_TRUE を返し、それ以外の場合は GL_FALSE を返します。

GL_LINK_STATUS
params は、プログラム上の最後のリンク操作が成功した場合は GL_TRUE を返し、それ以外の場合は GL_FALSE を返します。

GL_VALIDATE_STATUS
params は、プログラムに対する最後の検証操作が成功した場合は GL_TRUE を返し、それ以外の場合は GL_FALSE を返します。

GL_INFO_LOG_LENGTH
params は、ヌル終了文字を含むプログラムの情報ログの文字数 (つまり、情報ログを格納するために必要な文字バッファのサイズ) を返します。 プログラムに情報ログがない場合は、値 0 が返されます。

GL_ATTACHED_SHADERS
params は、プログラムにアタッチされているシェーダ オブジェクトの数を返します。

GL_ACTIVE_ATTRIBUTES
params は、プログラムのアクティブな属性変数の数を返します。

GL_ACTIVE_ATTRIBUTE_MAX_LENGTH
params は、ヌル終了文字を含むプログラムの最長のアクティブな属性名の長さ (つまり、最長の属性名を格納するために必要な文字バッファのサイズ) を返します。 アクティブな属性が存在しない場合は、0 が返されます。

GL_ACTIVE_UNIFORMS
params は、プログラムのアクティブなユニフォーム変数の数を返します。

GL_ACTIVE_UNIFORM_MAX_LENGTH
params は、ヌル終了文字を含む、プログラムの最も長いアクティブなユニフォーム変数名の長さ (つまり、最長のユニフォーム変数名を格納するために必要な文字バッファーのサイズ) を返します。 アクティブなユニフォーム変数が存在しない場合は、0 が返されます。


glGetProgramInfoLog	プログラムのリンクエラーログを取得 ●
## glDeleteProgram	
```
void glDeleteProgram( GLuint program);
```

- プログラムオブジェクトの削除

glDeleteProgram はメモリを解放し、program で指定されたプログラムオブジェクトに関連付けられた名前を無効にします。 このコマンドは、glCreateProgram の呼び出しの効果を効果的に取り消します。

プログラムオブジェクトがカレントの描画状態の一部として使用されている場合、削除のフラグが立てられますが、レンダリングコンテキストのカレントの状態の一部でなくなるまで削除されません。 削除するプログラムオブジェクトにシェーダーオブジェクトがアタッチされている場合、それらのシェーダーオブジェクトは自動的にデタッチされますが、glDeleteShader の以前の呼び出しによって削除フラグが既に設定されていない限り削除されません。 プログラムの値 0 は、静かに無視されます。

プログラムオブジェクトに削除のフラグが設定されているかどうかを判断するには、glGetProgram の引数に program と GL_DELETE_STATUS を指定して呼び出します。


## glGetAttribLocation	
```
GLint glGetAttribLocation( GLuint program, const GLchar *name);
```

- シェーダのアトリビュート(attribute)変数の位置を取得
	- シェーダ自体の準備が終わったら、シェーダにデータを渡す準備をする。
	- 頂点シェーダに記述したattribute変数（attr_pos）はアプリ側から操作を行う際に、「変数名」を直接利用せず、 attribute location という ID を利用する。

```
extension->attr_pos = glGetAttribLocation(extension->shader_program, *attr_pos);
    assert(extension->attr_pos >= 0);
```

- 以下リファレンス

```
glGetAttribLocation は、program で指定された以前にリンクされたプログラム オブジェクトに対して、name で指定された属性変数を照会し、その属性変数にバインドされている汎用頂点属性のインデックスを返します。  
name が行列属性変数の場合、行列の最初の列のインデックスが返されます。  
指定された属性変数が指定されたプログラム オブジェクトのアクティブな属性ではない場合、または名前が予約された接頭辞 "gl_" で始まる場合、値 -1 が返されます。  

属性変数名と汎用属性インデックスの間の関連付けは、glBindAttribLocation を呼び出すことでいつでも指定できます。   
属性バインディングは、glLinkProgram が呼び出されるまで有効になりません。   
プログラム オブジェクトが正常にリンクされた後、属性変数のインデックス値は、次のリンク コマンドが発生するまで固定されたままになります。   
属性値は、リンクが成功した場合にのみ、リンク後に照会できます。   
glGetAttribLocation は、指定されたプログラム オブジェクトに対して最後に glLinkProgram が呼び出されたときに実際に有効になったバインディングを返します。   
最後のリンク操作以降に指定された属性バインディングは、glGetAttribLocation によって返されません。  
```


## glBindAttribLocation  
```
void glBindAttribLocation(GLuint program, GLuint index, const GLchar *name);
```
attribute 変数の index を指定します. program はシェーダプログラムの名前です. index に指定できる値は, 0 〜 MAX_VERTEX_ATTRIBS - 1 までです. MAX_VERTEX_ATTRIBS はハードウェアに依存した値で, 少なくとも 16 です. 実際の値は glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &n); として n に得ることができます. name は index を指定する attribute 変数の名前です.


## glGetUniformLocation  
```
GLint glGetUniformLocation(GLuint program, const GLchar* name)
```

- シェーダのユニフォーム変数の位置を取得
- Uniform変数のアクセスには、attributeと同じく Location を取得する必要がある。

	- program : location を取得するプログラムオブジェクト
	- name : location を取得する uniform 変数名


- 正常に取得できたら 0 以上、失敗した場合は -1 が返る。


## glUniform4f
```
void glUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
```

- 取得した location を利用して uniform 変数を書き換える方法は複数提供されている。ここでは、GLfloat型のデータを送信（アップロード）するコマンドを示す。
- GLfloat型変数を vec4 型 uniform 変数へアップロードする。
	- アップロード対象は、最後に glUseProgram コマンドによって使用中となっているプログラムオブジェクトになる。
- xyzw それぞれの引数は、RGBA の色情報として扱われる。


## glUniform4fv
```
void glUniform4fv(GLint location, GLsizei count, const GLfloat* v)
```

- 配列を介してXYZWの情報をアップロードする。vec4 の配列として定義したuniform変数へのアップロードにも利用できる。

	- location : アップロード対象の uniform 変数 location
	- count : アップロードするベクトル数、vの配列長は count * 4 以上が必要
	- v : アップロードするベクトル配列


## glUniform2f, glUniform2fv



## glVertexAttribPointer

```
void glVertexAttribPointer(	GLuint index,
 	GLint size,
 	GLenum type,
 	GLboolean normalized,
 	GLsizei stride,
 	const void * pointer);
 ```
 ```
void glVertexAttribIPointer(	GLuint index,
 	GLint size,
 	GLenum type,
 	GLsizei stride,
 	const void * pointer);
 ```
 ```
void glVertexAttribLPointer(	GLuint index,
 	GLint size,
 	GLenum type,
 	GLsizei stride,
 	const void * pointer);
```

- アトリビュート変数にバッファ内のオフセットを指定
- 頂点データは単なるメモリの塊であり、専用の型や構造はない。
- 1つの頂点にどのようなデータがあって、どんな型で格納されているかを、この関数で伝える。

	- index : 頂点データを関連付ける attribute location  
	- size : 頂点データの要素数  
	- type : 頂点データの型。GL_BYTE, GL_FLOAT など  
	- normalized : 正規化して渡す場合は GL_TRUE, そのまま渡す場合は GL_FALSE  
	- stride : 頂点の先頭位置ごとのオフセット、0指定可能  
	- ptr : 関連付ける頂点の先頭ポインタ  



- 以下リファレンス
```
glVertexAttribPointer、glVertexAttribIPointer、glVertexAttribLPointer は、描画時に使用するインデックス index(glGetAttribLocationで取得) の汎用頂点属性の配列の位置とデータ形式を指定します。 size は、属性ごとのコンポーネントの数を指定し、1、2、3、4、または GL_BGRA でなければなりません。 type は各コンポーネントのデータ型を指定し、stride は1つの属性から次の属性へのバイトストライドを指定します。これにより、頂点と属性を単一の配列にパックしたり、個別の配列に保存したりできます。

For glVertexAttribIPointer, only the integer types GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, GL_UNSIGNED_INT are accepted. Values are always left as integer values.

glVertexAttribPointer の場合、normalized に GL_TRUE が設定されていれば、整数形式で格納された値は、範囲[-1,1]（符号付きの場合）または[0,1]（符号なしの場合）の float に変換されます。 それ以外の場合、値は正規化せずに直接 float に変換されます。

glVertexAttribIPointer の場合、整数型である GL_BYTE、GL_UNSIGNED_BYTE、GL_SHORT、GL_UNSIGNED_SHORT、GL_INT、GL_UNSIGNED_INT のみが受け入れられます。 値は常に整数値のままです。

glVertexAttribLPointer は、64ビットの double で宣言されたシェーダー属性変数に関連付けられた汎用頂点属性配列の状態を指定します。 type は GL_DOUBLE でなければなりません。 index、size、および stride は、glVertexAttribPointer および>glVertexAttribIPointer の説明と同様に動作します。
```

## glClear
```
void glClear( GLbitfield mask);
```

- 画面消去

glClear は、ウィンドウのビットプレーン領域を、 glClearColor、glClearDepth、 glClearStencilによって以前選択された値を設定します。 glDrawBufferを使用して一度に複数のバッファーを選択すれば、複数のカラーバッファーを同時にクリアできます。

ピクセル所有権テスト、シザーテスト、ディザリング、バッファー書き込みマスクは、glClearの動作に影響を与えます。 シザーボックスは、クリアされた領域の境界を定めます。 アルファ関数、ブレンド関数、論理演算、ステンシル、テクスチャマッピング、深度バッファリングは、glClearによって無視されます。

glClearは、どのバッファをクリアするかを示すいくつかの値のビットごとのORである単一の引数を取ります。

値は下記のとおりです。

GL_COLOR_BUFFER_BIT
現在色の書き込みが有効になっているバッファを示します。

GL_DEPTH_BUFFER_BIT
深度バッファを示します。

GL_STENCIL_BUFFER_BIT
ステンシルバッファーを示します。

各バッファーがクリアされる値は、そのバッファーのクリア値の設定によって異なります。



## glClearColor
```
void glClearColor(	GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
```

- 画面消去時の色を指定

カラーバッファーをクリアーする際の赤 (red)、緑 (green)、青 (blue)、アルファの値を指定します。 初期値は全て 0 です。
glClearColor は glClear によってカラーバッファーをクリアーする際に 赤、 緑、 青、 アルファの各値を指定します。 glClearColor で指定された値は [0,1]
 の範囲にクランプされます。


# glEnableVertexAttribArray  
```
void glEnableVertexAttribArray(GLuint index)
```
- attribute変数には有効・無効状態があり、有効でなければ頂点データにアクセスすることができない。
- 頂点バッファを有効にする
- 「どのプログラムオブジェクトのattribute変数か」を指定する必要はなく、最後に glUseProgram コマンドで指定したオブジェクトの attribute 変数に対して効果を与える（ので、複数のプログラムオブジェクトがある場合は注意が必要）。



glUseProgram	描画に使用するプログラムを指定 ◎

glViewport	画面位置とサイズをピクセル単位で指定 ◎

glUniform1f	シェーダのユニフォーム変数に値を設定 ◎
glDrawElements	頂点インデックスを使って描画 




## REFERENCE
http://web.wakayama-u.ac.jp/~wuhy/GSS/02.html  
http://wisdom.sakura.ne.jp/system/opengl/index.html  
https://tokoik.github.io/opengl/libglut.html  

https://opengles-book.com/es2/index.html

OpenGLの使い方  
https://qiita.com/sugawara/items/800d81211d726aeb1412

OpenGL ES2.0 入門 基礎編  
https://qiita.com/kazoo/items/7d4550e18e128e1124b3

Raspberry Pi で OpenGL ES2  
https://www.mztn.org/
https://www.mztn.org/rpi/rpi07.html