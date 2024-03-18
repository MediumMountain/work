# ラムダ式【=>】
```C#
var ret = list.Select( n => 0 < n );
```

## デリゲート(delegate)
関数を変数のように扱う為のもの

- イベントハンドラ的な使い方  
    delegate の宣言
    ```C#
    public delegate void ProgressHandler(int percentage);
    ```
    プロパティの作成
    ```C#
    public event ProgressHandler Progress;
    ```
    セット
    ```C#
    var test = new TestProcess();
    test.Progress += TestProgressHandler1;     //delegateにセット
    test.Progress += TestProgressHandler2;     //delegateにセット
    test.Run();
    ```
    Run()内で↓のようにゲットして、セットしたものを呼び出す。
    ```C#
    Progress(percentage);
    ```

    - デリゲートにメソッドをセットするには「+=」演算子
    - セットしたメソッドを外すのは「-=」演算子

- コールバック的な使い方  
    宣言
    ```C#
    public delegate bool TestDelegate(int obj);
    ```
    コールバックとして呼び出したい関数を引数に
    ```C#
    var result = list.Select(TestFunc);

    public bool TestFunc(int n)
    {
        if (0 < n)
            return true;
        else
            return false;
    }
    ```
    delegateを使ってコールバック
    ```C#
    public TestList Select(TestDelegate func)
    {
        var list = new TestList();
        foreach (var obj in this)
        {
            if (func(obj))
            {
                list.Add(obj);
            }
        }
        return list;
    }
    ```

    ☆上の例は条件に合う項目だけを抜き出すSelectメソッド。この「条件に合う」という部分にdelegateを使って外に出す事で、様々な条件に対応できる汎用的なメソッドになる。

- 定義済みdelegate（FuncとAction  
戻り値を持つ delegate が Func  
戻り値を持たない delagete が Action

Func
```C#
public delegate TResult Func<out TResult>();
public delegate TResult Func<in T1, out TResult>(T1 arg1);
public delegate TResult Func<in T1, in T2, out TResult>(T1 arg1, T2 arg2);
public delegate TResult Func<in T1, in T2, in T3, out TResult>(T1 arg1, T2 arg2, T3 arg3);
```
Action
```C#
public delegate void Action();
public delegate void Action<in T1>(T1 arg1);
public delegate void Action<in T1, in T2>(T1 arg1, T2 arg2);
public delegate void Action<in T1, in T2, in T3>(T1 arg1, T2 arg2, T3 arg3);
```

## 匿名メソッド  
- 汎用的なコードが作りやすいdelegateを更に使いやすくしたもの  
- メソッドの中にメソッドを作る

コールバック的な使い方の例と同様の動作を↓のように記述できる。
```C#
    public hoge()
    {
        InitializeComponent();
 
        var list = new TestList();
        list.Add(0);
        list.Add(1);
        list.Add(2);
 
        var result = list.Select(
            delegate(int n)
            {
                if (0 < n)
                    return true;
                else
                    return false;
            });
    }
```
Selectの引数に直接メソッドを書き込んでいる。
一度だけなので条件のコールバック的部分に名前はない　→　匿名


## ラムダ式
匿名メソッドを簡略化して記述したもの  

```C#
var result = list.Select(
    (n) =>
    {
        return 0 < n;
    });
```
n の型は型推論によって省略されている。  
また、`{}`　の中身が一行の場合、`{}` も `return`も省略する事ができる。  
さらにdelegateの引数が１つだけの場合は n の`()`も省略できる。

```C#
var result = list.Select(n => 0 < n);
```


## REFERENCE

[C#のデリゲート (delegate) って何？](https://araramistudio.jimdo.com/2019/04/03/c-%E3%81%AE%E3%83%87%E3%83%AA%E3%82%B2%E3%83%BC%E3%83%88-delegate-%E3%81%A3%E3%81%A6%E4%BD%95/)  
[C#のデリゲートお手軽にする匿名メソッド](https://araramistudio.jimdo.com/2019/04/03/c-%E3%81%AE%E3%83%87%E3%83%AA%E3%82%B2%E3%83%BC%E3%83%88%E3%81%8A%E6%89%8B%E8%BB%BD%E3%81%AB%E3%81%99%E3%82%8B%E5%8C%BF%E5%90%8D%E3%83%A1%E3%82%BD%E3%83%83%E3%83%89/)  
[C#のラムダ式【=>】って何？](https://araramistudio.jimdo.com/2017/12/19/c-%E3%81%AE%E3%83%A9%E3%83%A0%E3%83%80%E5%BC%8F-%E3%81%A3%E3%81%A6%E4%BD%95/)