# error集

## 'texture2D':undeclared identifier 
- glCompileShaderがエラーになってしまう。glGetShaderInfoLog をしてエラーの原因を調べると上記エラー原因を指摘される。
- 環境によっては同じGLSLバージョンでも動作する関数が異なるようである。

    - 解決方法としては「texture2D」を「texture」に置き換えること。
    https://stackoverflow.com/questions/52665406/error-010-invalid-call-of-undeclared-identifier-texture2d?noredirect=1&lq=1