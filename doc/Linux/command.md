# Command
## topコマンド

- 得られる情報
    - システム全体の負荷
    - プロセス, CPU, メモリ, スワップの統計情報

```
$ top          # CPU使用率順にソート
$ top -a       # メモリ使用率順にソート
$ top -p [PID] # 特定のプロセスを監視
$ top -d1      # 1秒ごとに更新
```


## psコマンド
- プロセスの状況について確認できる。

```
# デーモンでない自分が実行したプロセスを表示
$ps
PID TTY          TIME CMD
2536 pts/0    00:00:00 bash
6999 pts/0    00:00:00 ps
```


# REFERENCE
![topコマンドの使い方](https://qiita.com/k0kubun/items/7368c323d90f24a00c2f)
![psコマンドで表示される内容について調べた](https://qiita.com/toshihirock/items/565fe71d778d3ee36b96)