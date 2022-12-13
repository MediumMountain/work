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


