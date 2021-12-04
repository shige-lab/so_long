# push_swap
# for 42tokyo
2次元の簡易的なゲームを制作しています。
まだ製作中でコード整理や変数関数の名前も仮の状態なので参考程度に見て頂けると助かります。


# 流れ
・mapの情報を受け取りそのmapが有効であるかを確認する(mapのルールは後に記載)。

・map有効である場合はそのデータをもとにウィンドウ上にmapのイメージを表示する。無効である場合はそこでプログラムを終了する。

・mapによって指定されたプレイヤーのスタート位置からゲームが始まる。

・プレイヤーを動かしマップ上にある収集物を全て集め、出口へだどり着くとゲームクリアとなる。


# 使用可能関数
open, close, read, write,
printf, malloc, free, perror,
strerror, exit
• All functions of the MinilibX


# 実行環境
linuxのみ

# 使い方

実行ファイル名 so_long(makeで作成可能)

第2引数にマップ情報の入ったファイル指定し、so_longを実行することでゲームを開始できる。

例: ./so_long map/sample.ber

WSADで上下左右の移動が可能

esc keyで終了

# マップルール(課題文引用)
◦ The map must be composed of only 5 possible characters: 0 for an empty
space, 1 for a wall, C for a collectible, E for map exit and P for the player’s
starting position.

This is a simple valid map:

1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111

◦ The map must be closed/surrounded by walls, if not the program must return
an error.

◦ Map must have at least one exit, one collectible, and one starting position.

◦ You don’t need to check if there’s a valid path in the map.

◦ The map must be rectangular.

◦ You must be able to parse any kind of map, as long as it respects the rules of
the map.