# Cmake
- CmakeLists.txtにビルド用の設定を記述することで複数の異なるビルドシステム用の設定ファイルの生成を自動で行ってくれる。
- out-of-sourceビルドを基本としており、ソースと異なるディレクトリないでビルドすることが推奨されている。


## 想定されるディレクトリ構成
```
project1/
  |- test1.h
  |- test1.cpp
  |- CMakeLists.txt
  |- build/ （ビルド用のディレクトリ）
```


## CMakeLists.txt の設定

```
cmake_minimum_required(VERSION 3.1)
project(cmake_test_1 CXX)
aadd_executable(cmake_test test1.cpp)
```


- cmake_minimum_required()
  - 1行目ではこのプロジェクトで必要とするCMakeのバージョンを指定

- project()
  - 2行目ではプロジェクト名を指定

- add_executable()
  - ターゲット名が生成する実行ファイルの名前に相当
  - 依存ファイルにはビルドに必要なソースファイルなどを指定


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


# REFERENCE
https://qiita.com/Hiroya_W/items/049bfb4c6ad3dfe6ff0c
https://izadori.net/cmake_1/
