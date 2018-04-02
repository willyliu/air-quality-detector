<!--
$theme: gaia
template: invert
-->
<!-- $size: 16:9 -->

物聯網初步 -
如何土砲一個空氣品質偵測器
================
---
我的物聯網經驗
* Raspberry Pi - 積灰塵
* Raspberry Pi 2 - 積灰塵
* KKLinx - Raspberry Pi 2 B
	* Pi 太強大而且太貴，不好玩，所以再尋找別的選項
* ESP8266 from Jeremy
	* 便當價就可以上網，但開發相對不便
* Arduino
	* 有 IDE，開發便利
---
為什麼要學物聯網？
* 跟現實世界結合
	* 譬如：目前所在位置氣溫幾度？
	* 手機/PC 受限於內建感測器
* 專屬功能性
	* 不可能買台 PC 專門顯示空氣品質
* 熱門
* 簡單好學
---
為什麼是空氣品質偵測器？
* 去年(2017)年底開發時詢問老婆
* 列出各種感測器，發現空氣品質最實用
* 用其他感測器也可以，原理類似
* 重點是學習如何跟別的元件溝通
---
物聯網架構
* 如果(條件成立)則(做什麼事)
* 輸入 -> 邏輯 -> 輸出
  
實例
* 感測器 -> CPU -> 螢幕
* 小便斗：紅外線感測器 -> CPU -> 電磁閥
* 火警警報器：煙霧偵測器 -> CPU -> 蜂鳴器
* CPU (邏輯)部分就是寫寫程式

重點
* 如何從感測器得到資料
* 如何輸出
---
空氣品質偵測器
-
材料
* Arduino Uno
* 麵包板
* 杜邦線若干條
* 空氣品質感測器 PMSA003
* OLED 螢幕，驅動晶片 SH1106

軟體
* Arduino IDE

---
Arduino 接腳圖
![接腳圖](https://makerpro.cc/wp-content/uploads/2016/07/2016071101.jpg)
[圖片來源](https://makerpro.cc/2016/07/learning-interfaces-about-uart-i2c-spi/)

---
麵包板
![麵包板](http://www.codedata.com.tw/wp-content/uploads/2016/08/swz_06_008-1024x744.png)
[圖片來源](http://www.codedata.com.tw/java/swz-06/)

---
讀取空氣品質數據
-
接線
* 使用 UART (Universal Asynchronous Receiver/Transmitter) 序列埠與感測器通訊
	* RS232 也是 UART 的一種
	* 使用事先約定好的傳輸速率
	* 傳送端 TX 接到接受端 RX
	* 也就是感測器 TX <-> Arduino RX	
* 感測器接電，5V & GND 接到 Arduino 的 5V & GND
---
讀取空氣品質數據 - 2 
-
軟體
* 電腦也是用 UART 跟 Arduino 溝通
	* Arduino 連結電腦時，相當於接著 RX & TX
	* 因此，電腦寫入程式時，要把 Arduino RX 接腳斷開
	* 否則會寫入失敗
* Serial port 可以讀取或寫入，對應到 RX 或 TX 接腳
	* Arduino 從 serial port 讀取感測器送來的數值
	* Arduino 再用 serial port 寫入，這樣電腦就可以收到
	* 資料流向：PMSA003 -> Arduino -> Mac
---
讀取空氣品質數據 - Live Demo
* 軟體架構 - setup & loop
* 上傳程式
* 執行序列埠監控視窗，設定 baud rate 9600bps
---
螢幕輸出
-
接線
* 使用 I2C (Inter-Integrated Circuit) 與螢幕通訊
	* 兩條訊號線: 資料線 (SDA, Serial Data Line) 及時脈線 (SCL, Serial Clock Line)
	* OLED SCK <-> Arduino SCL
	* OLED SDA <-> Arduino SDA
* 當然，OLED 也要接 5V & GND 到 Arduio 5V & GND
---
軟體
* 執行程式庫管理員，搜尋 SH1106，找到並安裝 U8g2
* 使用 U8g2 來顯示畫面
---
螢幕輸出 - Live Demo
* 初始化
* 輸出
---
顯示空氣品質
-

* 取得 PM2.5 濃度數據
	* 根據 [PMSA003 spec](http://www.icshopping.com.tw/368030200334/PMSA003.pdf) 找到 sync bytes
	* 讀取整包數據
	* (Optional) 檢查 checksum
	* 取得 PM2.5 濃度
* 顯示 PM2.5 濃度數據
---
顯示空氣品質 - Live Demo

---
附註
* 購買電子零件各家的價差不小，送貨速度也差別很大，請多比較
* 入門可以先買有點貴的 [Arduino 套餐](https://24h.pchome.com.tw/books/prod/DJAA2V-A9006XED1)，5xx 元
* Arduino 有很多種板子，可以先買 Uno 試玩，然後買相容版即可，不用買義大利原廠版
* PMSA003 優點是準確（大陸廠商做的），缺點是價格頗高，7~8xx
* 如果不要求準確性，可以買 sharp 的空氣品質偵測器，便宜不少，但是很不準，價格 3xx
* 市面上的空氣品質偵測器都要 2xxx 元