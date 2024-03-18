# 環境構築

1. .NET Core SDKをインストール  
https://dotnet.microsoft.com/download

1. 拡張のインストール  
![](https://qiita-user-contents.imgix.net/https%3A%2F%2Fqiita-image-store.s3.ap-northeast-1.amazonaws.com%2F0%2F782968%2Fd7bc0e67-fd0f-396f-efe7-e68e80f35163.png?ixlib=rb-4.0.0&auto=format&gif-q=60&q=75&w=1400&fit=max&s=1ea84719c3ef61be385583b67eacb2a4)

1. 開発
    - プロジェクト作成
    ```
    dotnet new console -o "SampleConsole"
    code SampleConsole
    ```
    - RUN
    ```
    dotnet run --project .\SampleConsole.csproj
    あるいは
    dotnet run
    ```





## 補足
VSCodeで「The .NET Core SDK cannot be located.」メッセージを抑止  
![](https://qiita-user-contents.imgix.net/https%3A%2F%2Fqiita-image-store.s3.ap-northeast-1.amazonaws.com%2F0%2F142879%2Fb382a2d5-f30c-8c89-88b3-509290ea6ab9.png?ixlib=rb-4.0.0&auto=format&gif-q=60&q=75&w=1400&fit=max&s=ea09e0f65f3f7bbd9feb3f7ba240508d)

![](https://qiita-user-contents.imgix.net/https%3A%2F%2Fqiita-image-store.s3.ap-northeast-1.amazonaws.com%2F0%2F142879%2F0704e5b5-e1f2-4637-c457-172bdae3c50a.png?ixlib=rb-4.0.0&auto=format&gif-q=60&q=75&w=1400&fit=max&s=bc06a09ef85a2e3751004c5f10d3b476)