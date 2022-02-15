・概要
8*8*8のLEDキューブの試作品のプログラム。
PIC1で8ビットパラレル転送したデータを、
PIC2とトランジスタを用いて64段階で切り替えてダイナミック点灯を行い、
512個のLEDを同時点灯させる。
試作ではPIC1の出力先には7セグLEDを用いる。

・実際の動作のYoutube動画
https://www.youtube.com/watch?v=OBrBBq2SaM8

・ファイルの構成
LED_cube.h		このプロジェクトのヘッダファイル
LED_cube_master.c	PIC1のプログラム
LED_cube_controller.c	PIC2のプログラム
LED_data.c		テスト用のデータとプロジェクト内で使う関数
myfunction.c		普段使用している自分用の関数

・仕様
PIC18F23K20を使用。
LEDの表示データはchar[8][8]の構造体。

PIC1：PWMで自身とPIC2に同期するためのクロックを発信。
　　　PWMの立ち上がりエッジでPORTAから8ビットのデータを出力。
　　　タイマ割込みでLED表示データのパターンを変更。
　　　今後Raspberry Pi3とシリアル通信をする予定。

PIC2：PIC1から送られてきたPWMの立ち上がりエッジで同期を取って、
　　　トランジスタに出力して、LEDが点灯する列と段を切り替える。

PWM周期:約80nsec(ダイナミック点灯一周約5msec)
LEDのデューティー比:最大1.56%
