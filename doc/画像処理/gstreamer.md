# マルチメディアフレームワークGStreamer
- GStreamerとは、マルチメディア系の処理をとっても簡単に実現するためのフレームワーク


## パイプラインアーキテクチャ
- sinkとsourceという入出力を持つエレメントをつなぎ合わせることで目的の機能を実現するパイプラインアーキテクチャを採用している。
- Pipeline architecture に従い、Element を組み合わせ、Pipeline を作ればコアな部分を完成させることができる。


```
source ! sink
```

- シェルで | を使ってコマンドの処理結果を渡していくように、 GStreamer では Element の処理結果を ! で次の Element に渡す。




- エレメントには一つ前のエレメントからメディアを受け取る口と、処理した後のメディアを送り出す口が存在する。
- 受け取る口をSink Padと呼び、送り出す口をSource Padと呼ぶ。
- それぞれのPadには、こういった形式のメディアを送り出しますよ、こういった形式のメディアを受け取りますよ、という決まりがあり、どういった形式を受け取るかはエレメントによって異なる。
- 各エレメントがどういった形式のメディアを送り出すのか、受付するのかはgst-inspect-1.0コマンドで調べることができる。





## 基本パッケージ
- libgstreamer1.0-0がGStreamer本体の基本ライブラリで、gstreamer1.0-toolsがコマンドラインで実行するためのgst-launch-1.0等を含んだ実行バイナリのパッケージ

```
$ sudo apt install libgstreamer1.0-0 gstreamer1.0-tools
```


## コマンド（ツール）

- 現在インストール済みで利用可能なエレメント一覧を表示する

```
gst-inspect-1.0
```


- テストビデオ信号の表示
    - カラーバーが表示される

```
gst-launch-1.0 videotestsrc ! autovideosink
```







## REFERENCE

What is GStreamer?
https://gstreamer.freedesktop.org/documentation/application-development/introduction/gstreamer.html?gi-language=c
https://gstreamer.freedesktop.org/documentation/application-development/introduction/?gi-language=c

https://qiita.com/kurun_pan/items/f7896d52c1a3fcc947b0

GStreaemer の便利ツールたち、の簡単な説明
https://qiita.com/tetsukuz/items/51fdb6122a40bdd45e46

パイプラインについて
https://qiita.com/saxxos/items/e5b452502ad9aca3c997



Youtubeで360度ライブストリーミングをしてライブVR体験をする方法
https://qiita.com/f-aoyama/items/80f418c39977dbb78f5c
https://qiita.com/alivelime/items/700e240ada5dc9deb928
https://qiita.com/tanigox/items/3614fa6302f5b2892e2f


RICOH THETA SのためのDualfisheyeからEquirectangularに変換を行うGstreamerプラグイン
https://qiita.com/Otama75/items/fa7587ea60523a6ef76e



関連ブログ
https://moitkfm.blogspot.com/
