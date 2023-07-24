# YUVフォーマット

## YUV
- 色情報の表現形式の一つで、輝度信号（Y）と、輝度信号と青色成分の差（U）、輝度信号と赤色成分の差（V）の3つの組み合わせで色を表現する方式。
- また、そのような形式で表される色空間。

- 人間の目が色の変化よりも明るさの変化に敏感な性質を利用して、輝度情報により多くの情報量を割り当てることで、少ない画質の劣化で高いデータ圧縮率を得ることができる。
    - 人間の目をうまく欺いて、データの容量を削減するための圧縮フォーマット
    - RGBで1pixelを表すと、R, G, B で8bitずつ、計24bit必要だが、YUVでは 輝度信号(白黒) と 色差信号 に分割し、色差信号 の情報量を減らす(ダウンサンプリングする)ことで伝送効率等を良くする。

- テレビ放送の映像信号や、JPEG、MPEGなどの画像・映像データ圧縮に用いられる。コンピュータのディスプレイに表示するにはRGB形式による表現に変換する必要がある。


## REFERENCE

YUVフォーマットの違い  
https://qiita.com/Yossy_Hal/items/8e0b9676698ba552c210  

YUVフォーマット  
https://hk.interaction-lab.org/firewire/yuv.html  


YCbCrとクロマサブサンプリング  
https://videotech.densan-labs.net/articles/2017/08/28/yuv444-422-420.html  

RGB データと YUV データについて  
https://www.eizo.co.jp/products/tech/files/2010/WP10-009.pdf  


OpenGL関連

【GLSL】YUV色空間とHSV色空間  
https://blog.narumium.net/2020/05/31/%E3%80%90glsl%E3%80%91yuv%E8%89%B2%E7%A9%BA%E9%96%93%E3%81%A8hsv%E8%89%B2%E7%A9%BA%E9%96%93/  

