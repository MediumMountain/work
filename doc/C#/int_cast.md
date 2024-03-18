# INT型への変換（キャスト)

```C#
  int i = 0;
  double d1 = 1.4, d2 = 1.5, d3 = 2.4, d4 = 2.5, d5 = 3;
  
  // ①カッコ演算子
  i = (int)d1;    // 結果は1
  i = (int)d2;    // 結果は1
  i = (int)d3;    // 結果は2
  i = (int)d4;    // 結果は2
  
  // ②Parseメソッド
  i = int.Parse(d1);    // 結果エラー
  i = int.Parse(d5);    // 結果は3
  i = int.Parse(null);  // 結果エラー
  
  // ③Convert.ToInt32メソッド
  i = Convert.ToInt32(d1);    // 結果は1
  i = Convert.ToInt32(d2);    // 結果は2
  i = Convert.ToInt32(d3);    // 結果は2
  i = Convert.ToInt32(d4);    // 結果は2
  i = Convert.ToInt32(null);  // 結果は0
```


【カッコ演算子】　少数以下は切り捨て。コードの見た目はシンプルで良い。

【Parseメソッド】　少数点以下が0でないものは変換不可。引数のミスはエラーとなる。

【Convert.ToInt32メソッド】　四捨五入はある程度考慮され「直近の偶数になる」。引数のミスはゼロが返される。  


# .NETで割り算の結果を整数にしたいとき
C#でおもむろに
int a = 3/2;
なんてやるとaの結果は1になります。
つまりは切り捨てです。

切り上げや四捨五入をしたいときはこう？なんかめんどくさい・・・  
```C#
int a = Convert.ToInt32(Math.Ceiling((double)3/2));
```
Math関数
- Floor :切り捨て
- Ceiling:切り上げ
- Round :銀行丸め（パラメータにより四捨五入）



Reference  
http://7fblog.blog.fc2.com/blog-entry-389.html
https://qiita.com/noixip/items/592f9435b8fea6d70fff