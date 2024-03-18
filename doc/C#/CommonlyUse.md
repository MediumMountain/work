# よく使うやつ

## Write(String, Object[])
public static void Write (string format, params object?[]? arg);
- format    String : 複合書式設定文字列
- arg   Object[] : format を使用して書き込むオブジェクトの配列


コンソールへの出力
```
foreach (int i in numbers2D)
{
    System.Console.Write("{0} ", i);
}
```


