# Cmake
- CmakeLists.txtにビルド用の設定を記述することで複数の異なるビルドシステム用の設定ファイルの生成を自動で行ってくれる。
- out-of-sourceビルドを基本としており、ソースと異なるディレクトリないでビルドすることが推奨されている。


## インストール
```
sudo apt install cmake
```


## 想定されるディレクトリ構成
```
project1/
  |- test1.h
  |- test1.cpp
  |- CMakeLists.txt
  |- build/ （ビルド用のディレクトリ）
```


## CMakeLists.txt の設定
- ビルド対象のディレクトリーに CMakeLists.txt を配置することで cmake コマンドが対象だと認識してくれるようになる。

- 最低限必要な設定は以下  


```
cmake_minimum_required(VERSION 3.1)
add_executable(cmake_test test1.cpp)
target_link_libraries
```


- cmake_minimum_required()
  - 1行目ではこのプロジェクトで必要とするCMakeのバージョンを指定
  - CMakeLists.txt に記載されている内容を実行するにあたって必要な CMake のバージョンを明示する




- add_executable()
  - ターゲット名が生成する実行ファイルの名前に相当
  - 依存ファイルにはビルドに必要なソースファイルなどを指定
  - 実行ファイル名と、そのビルドに必要な c / cpp ファイルの指定
  - ヘッダーファイルはここに指定しなくても、更新すると勝手に認識してリビルド対象にしてくれる


- target_link_libraries
  - リンクするライブラリーの指定
  - gcc に -lfoo と指定していた場合、 foo とだけ書く



- target_include_directories
  - インクルードディレクトリの設定

### 最低げんではない？

- project(cmake_test_1 CXX)
  - プロジェクト名を指定


- find_package


  ## make用のMakefileを生成
  - buildディレクトリに移動したあとでcmakeを実行

  




# 基本的なビルド方法
```
$ mkdir build
$ cd build
$ cmake ..　
$ make #ライブラリのビルド
$ make examples #ライブラリを利用したサンプルをビルドしてバイナリを生成する
```



# make(Makefile)
- CやC++のコンパイルをコマンドひとつで自動化できる
- プログラムのビルド作業を自動化するツール。コンパイル、リンク、インストール等のルールを記述したテキストファイル (makefile) に従って、これらの作業を自動的に行う。



## Makefileのメリット
- コマンドを自由に作れる（こういうルールでビルドしたい、を自由に定義可能）
- 変更差分だけコンパイルし直すことができ、時間短縮できる
- チーム開発する際、Makefileを共有すれば全員でコンパイルルールを統一できる
- 基本構造はシンプルなので、自分のテンプレートを一度作れば様々なプログラムに流用できる


## Makefileの基本構造
- Makefileの中で用いる変数(マクロ)の設定
- ルールの設定



## ビルド対象の分割
- 複数のビルド対象がある場合、ひとつの CMakeLists.txt でアレコレやろうとするとこんがらがるので、ディレクトリーを切ってわける。

```
/path/to/your/project/
CMakeLists.txt
commandA/
CMakeLists.txt
src/
commandB/
CMakeLists.txt
src/
```

- トップの CMakeLists.txt で add_subdirectory を使って下のディレクトリーをビルド対象に加える。

```
# add_subdirectory でビルド対象追加
cmake_minimum_required(VERSION 2.8)

add_subdirectory(commandA)
add_subdirectory(commandB)
```



# REFERENCE
Cmake
https://qiita.com/Hiroya_W/items/049bfb4c6ad3dfe6ff0c
https://izadori.net/cmake_1/



make
https://qiita.com/mizcii/items/cfbd2aa17f6b7517c37f



Ｃ言語のビルド  
https://postd.cc/how-to-c-in-2016-1/