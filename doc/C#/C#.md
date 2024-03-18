# C#

# .NET
さまざまな種類のアプリをビルドするための無料のオープンソース開発プラットフォーム  
クロス プラットフォーム

- .NET Core
クロスプラットフォームでの動作環境  
    - windowsのみの環境は .NET Framework 




## 実行モデル?
共通言語ランタイム (CLR) と呼ばれるランタイム環境では、.NET アプリによってマネージド コードが実行されます。

CLR?  
.NET CLR は、Windows、macOS、Linux のサポートを含むクロスプラットフォーム ランタイムです。 CLR は、メモリの割り当てと管理を行います。 CLR は、アプリの実行だけでなく、Just-In-Time (JIT) コンパイラを使用してコードを生成してコンパイルする仮想マシンでもあります。

詳細については、「[共通言語ランタイム (CLR) の概要](https://docs.microsoft.com/ja-jp/dotnet/standard/clr)」を参照してください。


## 中間言語(IL)
JAVAのようにハードウェア（OS）に依存しない命令セットにコンパイルされる。  
IL = Intermediate Language




# ファイル構成

[C# ソリューションの基本的なファイル構成について](https://effect.hatenablog.com/entry/2018/08/07/031313)


■ .vs　　‥　suoファイル（ユーザーごとのオプションファイル）がある  
■ test　　‥　プログラムを構成する色んなファイルが詰まっている  
test.sln　‥　ソリューションファイル（ダブルクリックでプロジェクトが開く）  


■ bin　‥　コンパイル時に実行ファイルが出力される  
■ obj　‥　コンパイル時にコンパイルに必要なファイルが生成される？  
■ Properties　‥　リソースファイルなどが含まれる  
App.config　‥　アプリケーション設定ファイル  
Form1.cs　‥　フォームの挙動を記述していくC#ファイル
Form1.Designer.cs　‥　フォームの外観が自動で記述されていく  
Program.cs　‥　メイン関数（Form1.csを生成して実行する記述がある）  
test.csproj　‥　プロジェクトの設定ファイル？  


# コマンド
ビルド＆ラン  
dotnet run

仕組み


# 書式指定
.NET では、ToString メソッドや、string.Format 静的メソッドなどに対して、書式を与えることで、数値の表示の仕方を変えることができる  

- ToString メソッド
書式をToStringの引数として渡す
```C#
var n = 1980;
Console.WriteLine(n.ToString("d")); // 1980
Console.WriteLine(n.ToString("x")); // 7bc
 
var x = 0.12;
Console.WriteLine(x.ToString("f")); // 0.12
Console.WriteLine(x.ToString("e")); // 1.200000e-001
```
- 複合書式（string.Format）  
第一引数が書式、下例のように第二引数以降の何番目のインデックスをどのような書式で表示するかを指定できる。

    ```C#
    var x = 7;
    var y = 13;
    var line = string.Format("{0} × {1} = {2}", x, y, x * y);
    Console.WriteLine(line); // 7 × 13 = 91
    ```  
    インデックスに続けて、,（コンマ）で区切って幅を指定することもできる。この時、正の数を指定すると右詰め、負の数を指定すると左詰めになる。
    ```C#
    Console.WriteLine("({0,-5}) ({1,5})", 1, 1); // (1    ) (    1)
    ```
    また、インデックスに続けて、: （コロン）で区切って、個別の書式（＝ ToString メソッドに渡す書式）を指定できる。
    ```C#
    Console.WriteLine("{0:x}, {1:c}", 123, 123); // 7b, \123
    //↑ "{0}, {1}", 123.ToString("x"), 123.ToString("c") と同じ扱い
    ```


[文字列の書式設定](https://ufcpp.net/study/dotnet/bcl_format.html)  
[C#のstring.Formatで桁数や書式を指定する](C#のstring.Formatで桁数や書式を指定する)  
[文字列補間による値の整形](https://qiita.com/laughter/items/b49e5bc1b18ea370b94d)