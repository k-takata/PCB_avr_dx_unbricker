# AVR Dx/Ex Unbricker

## 概要

AVR Dx/Exシリーズ用の7.5V系高電圧プログラミングに対応したUPDI (Unified Program and Debug Interface)書き込み装置です。(ATtinyシリーズの12V系高電圧プログラミングには対応していません。)
UPDIピンの設定を変更してしまい、通常のUPDI書き込み装置で書き込みができなくなってしまったデバイスに対し、高電圧パルス(7.5V)を注入することで、再度書き込みができるようにします。

[秋月電子](https://akizukidenshi.com/)の[CH9102F USBシリアル変換モジュールキット Type-C (AE-CH9102F-TYPEC-BO)](https://akizukidenshi.com/catalog/g/g129505/)、または一般的な6pinのシリアルモジュールを接続して使用します。

UPDI部分の回路は[SerialUPDI](https://github.com/SpenceKonde/AVR-Guidance/blob/master/UPDI/jtag2updi.md)に従っています。


## 使用したソフトウェア

KiCad 10.0


## 回路図

[![schema](https://raw.githubusercontent.com/k-takata/PCB_avr_dx_unbricker/master/images/schema.png)](https://raw.githubusercontent.com/k-takata/PCB_avr_dx_unbricker/master/images/schema.pdf)


## 基板パターン図

![PCB pattern](https://raw.githubusercontent.com/k-takata/PCB_avr_dx_unbricker/master/images/pcb-pattern.png)


## 部品表

| Reference |個数|値    | 説明 |
|-----------|----|------|------|
|C1,C2      |   2|0.1μF| |
|C3,C4      |   2|1μF  | |
|D1,D3,D4,D8|   1|BAT43 |適当なショットキーバリアダイオード |
|D2         |   1|LED   |φ5mm |
|D5         |   1|7.5V  |ツェナーダイオード (\*1) |
|D6         |   1|      |ツェナーダイオード (\*1) |
|D7         |   1|      |ツェナーダイオード (\*1) |
|J1         |   1|      |L型ピンソケット 2x4 (\*2)、AE-CH9102F-TYPEC-BO接続用 |
|J2         |   1|      |ピンヘッダー 1x6、TTLシリアル入力接続用 |
|J3         |   1|      |ピンソケット 1x4、UPDI接続用|
|J4         |   1|      |[L型ピンソケット 1x6](https://akizukidenshi.com/catalog/g/g109862/)、TTLシリアル出力接続用|
|J5         |   1|      |ピンヘッダー 1x3、RTS/DTR切り替え用|
|J6         |   1|      |ピンヘッダー 1x3、書き込み先切り替え用|
|Q1         |   1|BSS138|Nch MOSFET|
|Q2         |   1|BSS84 |Pch MOSFET|
|R1         |   1|470Ω |黄紫茶金、1/4Wサイズ|
|R2,R3,R6   |   3|4.7kΩ|黄紫赤金、1/4Wサイズ|
|R4         |   1|10kΩ |茶黒橙金、1/4Wサイズ|
|R5         |   1|100kΩ|茶黒黄金、1/4Wサイズ|
|SW1,SW2    |   2|[SS-12D00G3](https://akizukidenshi.com/catalog/g/g115707/)|スライドスイッチ 1回路2接点 基板用|
|SW3        |   1|      |プッシュスイッチ|
|U1         |   1|AVR64DD28-I/SP|(\*3)|
|U2         |   1|ATtiny402-SS  |(\*3)(\*4)|
|U3         |   1|      |ICL7660互換品|

(\*1) D5を単独で使用するか、D6 + D7の組み合わせで使用する。TP1の電圧が7.5Vになるようにする。  
(\*2) 例えば、[L型ピンソケット 2x6](https://akizukidenshi.com/catalog/g/g116795/)を加工して使用する。  
(\*3) U1またはU2のどちらか1つを使用。  
(\*4) U2を使用する場合は、ATtiny402を直接載せるか、変換基板を介して載せるかのどちらかを選択する。  


## 使用方法

### 接続

J1をAE-CH9102F-TYPEC-BOと接続します。AE-CH9102F-TYPEC-BOには付属のピンヘッダーではなく、L型ピンヘッダー 2x4を基板表面側に取り付けておきます。
あるいは、J2に一般的な6pinのTTLシリアルモジュールを接続します。(J1とJ2は排他利用です。)

J3は、[AVR Programming Adapter](https://www.microchip.com/en-us/development-tool/AC31S18A)と同じUPDI v2コネクターとなっています。

| Pin | 機能       | 色 |
|-----|------------|----|
|   1 | RESET      | 白 |
|   2 | VDD (5V)   | 赤 |
|   3 | GND        | 黒 |
|   4 | UPDI       | 緑 |

J4は、一般的な6pinのTTLシリアルコネクターとなっています。J1使用時、6番ピンはJ5にジャンパーピンを挿すことでRTSかDTRのどちらかを選択できます。(J2使用時は、J2の6番ピンと直結されます。)

| Pin | 機能       | 色 |
|-----|------------|----|
|   1 | GND        | 黒 |
|   2 | CTS        | 茶 |
|   3 | VDD (5V)   | 赤 |
|   4 | TxD        | 橙 |
|   5 | RxD        | 黄 |
|   6 | RTS / DTR  | 緑 |

SW1は、UPDIモードとシリアル通信モードの切り替えスイッチです。シルクのUPDIの側に倒すとUPDIモード(J3使用)、Serialの側に倒すとシリアル通信モード(J4使用)です。

SW2は、本アダプターから5Vを供給するかどうかを選択します。シルクのONの側に倒すと5Vを供給し、OFFの側に倒すと供給しません。マイコンに対して別の経路で電源を供給済みの場合はOFFにしてください。


### ファームウェアの書き込み

T.B.D.


### UPDI

#### 通常モード

T.B.D.

#### 高電圧プログラミング

T.B.D.


## 完成品

T.B.D.
<!--
[![完成品](https://raw.githubusercontent.com/k-takata/PCB_avr_dx_unbricker/master/images/unbricker-thumb.jpg)](https://raw.githubusercontent.com/k-takata/PCB_avr_dx_unbricker/master/images/unbricker.jpg)
-->

## License

CC0
