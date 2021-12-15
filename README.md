# robosys_devicedriver
ロボットシステム学＿課題①


## Requirements  
・ブレッドボード  
・LED（緑、青）   
・ジャンパー線 


## Usage
echo 0 > /dev/myled0  (両方のLEDが消灯)  
echo 1 > /dev/myled0  (緑のLEDのみが点灯)   
echo 2 > /dev/myled0  (青のLEDのみが消灯)   
echo 3 > /dev/myled0  (両方のLEDがゆっくり点滅)  
echo 4 > /dev/myled0  (両方のLEDが素早く点滅) 

また、上記の操作を行った際、以下のAA(アスキーアート)がログに表示されるおまけ機能付き。
dmesg で確認できる。   
∧＿∧   
( ´･ω･) みなさん、お茶が入りましたよ・・・・。  
( つ旦O   
と＿)＿) 

## 動作の様子
