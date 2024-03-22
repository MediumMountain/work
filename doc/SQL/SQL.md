# SQLとは
データベースを操作する言語 または　データベース問い合わせ言語  

## 役割分け

- テーブルの操作であるDDL(Data Define Language)  
    - CREATE - 新しいテーブルを作成する。  
    - DROP - 既に存在するテーブルを削除する。

- データの操作であるDML(Data Manipulation Language)  
    - SELECT - データを取得・検索する
    - INSERT - データを挿入・登録する)
    - UPDATE - データを更新する
    - DELETE - データを削除する

- データベースの権限を扱うDCL(Data Control Language)  
    - GRANT - 特定のデータベース利用者に特定の作業を行う権限を与える
    - REVOKE - 特定のデータベース利用者から既に与えた権限を剥奪する



# RDBMS
データを「キー」によって関連付けられたテーブルという個別のストレージに分割して管理

# クライアントサーバモデル



# MySQL
oracleが開発してサポートするオープンソースのSQLリレーショナルデータベース管理システム

# MariaDB
オープンソースのMySQLをベースに作成されたもの  
MySQLからのシームレスな置換が可能（相互運用）、パフォーマンスの向上




## 使用例（microsoft SQL server Management）
- 1000件だす  
    ```sql
    /****** SSMS の SelectTopNRows コマンドのスクリプト  ******/  
    SELECT TOP (1000) [Id]
        ,[LineKey]
        ,[Date]
        ,[CurrentStatus]
        ,[CurrentStatusTime]
        ,[TotalCurrentStatusTime]
        ,[ErrorCode]
        ,[Category]
        ,[LaneNo]
        ,[BalanceWaitTime]
        ,[MaintenanceError]
    FROM [ProNaviDB].[M#202107200700].[LineUtilActualFI]
    ORDER BY DATE DESC;
    ```
- not in  
    ```sql
    SELECT Date,CurrentStatus,CurrentStatusTime,ErrorCode
    FROM M#202107201000.LineUtilActualFI
    WHERE CurrentStatus NOT IN (100,200,201)
    ORDER BY DATE DESC;
    ```

