# ESP8266_ATP3011_Server
---
ESP8266とATP3011を使った音声合成出力<br>
<br>
このスケッチをコンパイルするには、Arduino用 音声合成LSIライブラリが必要です。<br>
以下のURLからライブラリをダウンロードしてインストールして下さい。<br>
<http://blog-yama.a-quest.com/?eid=970151>
<br>
スケッチのssidとpasswordは、自分の環境に合わせて書き換えてください。
<br>
ESPr One(Arduino Uno同一形状 ESP-WROOM-02開発ボード)とAquesTalkプロトシールドの組み合わせで動作確認しました。<br>
* ESPr One <https://www.switch-science.com/catalog/2620/><br>
* AquesTalkプロトシールド <https://www.switch-science.com/catalog/1373/><br>


音声出力のサンプル<br>
XXX.XXX.XXX.XXXの部分はESP8266のIPアドレスに書き換えてください。<br>
`http://XXX.XXX.XXX.XXX/speech?say=korewa/ <ALPHA VAL=ATP3011>no/ te'_sutode_su.`<br>
`http://XXX.XXX.XXX.XXX/speech?say=ketayomi <NUMK VAL=12344567>de_su.`<br>

