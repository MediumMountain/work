# ThetaS + KVS（Windows）のメモ

# やること
1. ThetaSからの映像をパノラマ化する。
1. gst-launch-1.0コマンドでライブストリーミング
1. KVSでメディア表示する


# Ubuntu PC

## 現状の問題点
- ThetaS=v4l2srcをsinkまで持ってくるパイプラインが作成できていない。



# Windows
## 検討中の手法
- パノラマ化にTheta UVC Blenderを利用
- windows用のgstreamerを使用し、↑を通した後の映像をresourceとする。

## 現状の問題点
- winのgstreamerでThetaSが検出できない



## libuvc




# KVS



# REFERENCE
THETA
https://theta360.com/ja/about/theta/s.html


libuvcのインストールと使用方法
https://qiita.com/okubo999/items/85de1556a51c363bda24
