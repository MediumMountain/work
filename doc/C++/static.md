# static修飾子
- staticがつけられた変数は静的領域に確保される。

- 「static」は静的という意味で「dynamic（動的）」の対義語である。
- 下記の様に変数宣言または関数宣言時に「static」を付加することで、付加された変数または関数が静的であることを宣言する。

```
    static int var;
    static int func() { return 0; }

```

同じプロジェクトに含まれる複数のファイルに、同じ関数名・引数の関数があると、リンク時にエラーになる。


## staticメンバ変数  

次のPeapleクラスはstaticメンバ変数numを持ちます。
また、コンストラクタが呼ばれた時にnumを+1し、デストラクタが呼ばれた時、numを-1しています。

```
//myClass.hpp
#include <stdio.h>
#include <iostream>
using namespace std;

class Peaple{
private:
    string str;
    static int num;
public:
    //コンスラクタ
    Peaple(const string& newName):str(newName) {num++;}
    //デストラクタ
    ~ Peaple(){num--;}
    //メンバ関数1
    void ret_Peaple_num(void);
};


```

メンバ関数の実装は次の通り。メンバ関数のret_Peaple_numはstaticメンバ変数 numの値を返すプログラムになっています。
ここで、クラスを定義したhppファイルと対応するcppファイルにおいて、☆でstaticメンバ変数の実体を作っておくことを忘れないようにしてください。


もし、書き忘れたらUndefined symbols for architecture x86_64:(Clangでは)というエラーがでてコンパイルが通りません。(また、staticは不要なのでそこにも注意してください)

```
//myClass.cpp
int Peaple::num = 0; ☆//Undefined symbols for architecture x86_64:
void Peaple::ret_Peaple_num(void){
    cout << num <<endl;
}
```

```
//main.cpp
#include <iostream>
#include "myClass.hpp"

int main(int argc, const char * argv[]) {

    Peaple A("ペトロフ");
    Peaple B("ジダン");
    Peaple C("キアヌ");
    A.ret_Peaple_num();//3と表示される。

    Peaple *D = new Peaple("キャスカ");
    A.ret_Peaple_num();//4と表示される。
    delete(D);

    A.ret_Peaple_num();//3と表示される。

    return 0;
}
```
このプログラムにおいて、staticメンバ変数numはPeapleクラスの全てのインスタンスでその値を共有できる。  


このmain関数を実行すると、Peapleクラスのメンバ変数numの値を表しているはずです。
numはコンストラクタが呼ばれた時、すなわち、Peapleクラスのインスタンスが生成された時に、+1されるのでしたね。このことを加味して実行結果を見るとnumの値は、Peapleクラスのインスタンスを3つ(A,B,C)を生成した後に3、インスタンスDを生成した後に4、さらにDをdeleteした後に3(デストラクタが呼ばれてnum--されている)と変化していることが分かると思います。すなわち、numは現在生成されているPeapleクラスの数を示しているのです。この結果からも、staticメンバ変数numがインスタンス毎に確保されているのではなく、インスタンス間で共有されていることが分かります。


## staticメンバ変数の仕組み
staticメンバ変数は、何故インスタンス間で共有されているのでしょうか。
それは、staticメンバ変数はインスタンス毎に確保されるのはなく、クラスにつき1つ静的領域に確保されるからです。 
すなわち、各インスタンスのstaticメンバ変数は静的領域に確保されたも1つのものを指していることになります。



staticにはメンバ関数を静的領域に確保し、インスタンス内で共有できるようにする効果があります。また、メンバ関数をstaticメンバ関数にすることで、そのメンバ関数はstaticメンバ変数以外を取扱えなくなります。少し不便な気もしますが、逆に言えばstaticメンバ変数以外のメンバ変数を取り扱わないという関数の挙動を事前に読み手に伝えることができるのでコードの可読性の向上に繋がる効果もある。

個人的な見解ですが、グローバル変数を使ったプログラムはどこでその変数が操作されているか特定することが困難です。もし、自分があるクラスのインスタンス間でのみ共有するつもりでグローバル変数を使用したつもりでも、他のプログラマがそのグローバル変数を書き換えてしまいプログラムの挙動がおかしくなる・・・なんてことも考えらえます 。そんな時に、staticメンバ変数を使えば、このような事故も防げます。

このように、staticメンバ変数はインスタンス間という特定の範囲のメンバ変数を共有できるので、生成されたインスタンスの数を管理する時とかには非常に便利です。


## REFERENCE

C++ 修飾子についての忘備録  
https://qiita.com/omuRice/items/3c40e8dde19e276ccacf  


C++ static 修飾子 入門  
http://vivi.dyndns.org/tech/cpp/static.html  

