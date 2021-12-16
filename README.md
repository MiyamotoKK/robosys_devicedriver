# robosys_devicedriver
ロボットシステム学＿課題①


## 必要品 
・ブレッドボード  
・LED（緑、青）   
・ジャンパー線 

## 回路図
![Ras_回路図](https://user-images.githubusercontent.com/92069729/146303528-2a21658b-0b55-47b8-bfe1-9d1e155a2af1.png)

## Usage

### <インストール>
このリポジトリをクローン,myledに移動したうえで以下を実行。  
```  
make  
sudo insmod myled.ko  
sudo chmod 666 /dev/myled0  
```
### <実行方法>
```
echo 0 > /dev/myled0  (両方のLEDが消灯)  
echo 1 > /dev/myled0  (緑のLEDのみが点灯)   
echo 2 > /dev/myled0  (青のLEDのみが消灯)   
echo 3 > /dev/myled0  (両方のLEDがゆっくり点滅)  
echo 4 > /dev/myled0  (両方のLEDが素早く点滅) 
```
また、上記の操作を行った際、以下のAA(アスキーアート)がログに表示されるおまけ機能付き。
dmesg で確認できる。   
∧＿∧   
( ´･ω･) みなさん、お茶が入りましたよ・・・・。  
( つ旦O   
と＿)＿) 

### <アンインストール>
```  
sudo rmmod myled
```
## 動作の様子
https://www.youtube.com/watch?v=an93UusaRtA
