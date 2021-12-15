# robosys_devicedriver
ロボットシステム学＿課題①

＜使用したもの＞
・ブレッドボード
・LED（緑、青）
・ジャンパー線

＜プログラムの内容>
echo 0 > /dev/myled0 (両方のLEDが消灯)
echo 1 > /dev/myled0 (緑のLEDのみが点灯)
echo 2 > /dev/myled0 (青のLEDのみが消灯)
echo 3 > /dev/myled0 (両方のLEDがゆっくり点滅)
echo 4 > /dev/myled0 (両方のLEDが素早く点滅)

また、上記の操作を行った際、AA(アスキーアート)がログに表示されるおまけ機能付き。
dmesg で確認できる。
