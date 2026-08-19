# AVR Dx/Ex Unbricker

## 概要

AVR Dx/Exシリーズ用の高電圧プログラミングに対応したUPDI (Unified Program and Debug Interface)書き込み装置です。(ATtinyシリーズの高電圧プログラミングには対応していません。)

[秋月電子](https://akizukidenshi.com/)の[CH9102F USBシリアル変換モジュールキット Type-C (AE-CH9102F-TYPEC-BO)](https://akizukidenshi.com/catalog/g/g129505/)、または一般的な6pinのシリアルモジュールを接続して使用します。

スイッチ1つで、UPDIによる書き込みモードと、シリアル通信モードを切り替えることができます。

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
|D1         |   1|[11EQS03L](https://akizukidenshi.com/catalog/g/g108997/)|適当なショットキーバリアダイオード |
|J1         |   1|      |L型ピンソケット 2x4 (\*1)、AE-CH9102F-TYPEC-BO接続用 |
|J2         |   1|      |ピンソケット 1x4、UPDI接続用|
|J3         |   1|      |[L型ピンソケット 1x6](https://akizukidenshi.com/catalog/g/g109862/)、TTL Serial接続用|
|J4         |   1|      |ピンヘッダー 1x3、RTS/DTR切り替え用|
|R1         |   1|470Ω |黄紫茶金、1/6Wサイズ(または1/4Wサイズ)|
|SW1,SW2    |   2|[SS-12D00G3](https://akizukidenshi.com/catalog/g/g115707/)|スライドスイッチ 1回路2接点 基板用|

(\*1) 例えば、[L型ピンソケット 2x6](https://akizukidenshi.com/catalog/g/g116795/)を加工して使用する。


## 使用方法

J1をAE-CH9102F-TYPEC-BOと接続します。AE-CH9102F-TYPEC-BOには付属のピンヘッダーではなく、L型ピンヘッダー 2x4を基板表面側に取り付けておきます。

J2は、[AVR Programming Adapter](https://www.microchip.com/en-us/development-tool/AC31S18A)と同じUPDI v2コネクターとなっています。
ただし、1番ピンのRESETは未接続です。(高電圧プログラミングには対応していません。)

| Pin | 機能       | 色 |
|-----|------------|----|
|   1 | RESET (NC) | 白 |
|   2 | VDD (5V)   | 赤 |
|   3 | GND        | 黒 |
|   4 | UPDI       | 緑 |

J3は、一般的な6pinのTTLシリアルコネクターとなっています。6番ピンはJ4にジャンパーピンを挿すことでRTSかDTRのどちらかを選択できます。

| Pin | 機能       | 色 |
|-----|------------|----|
|   1 | GND        | 黒 |
|   2 | CTS        | 茶 |
|   3 | VDD (5V)   | 赤 |
|   4 | TxD        | 橙 |
|   5 | RxD        | 黄 |
|   6 | RTS / DTR  | 緑 |

SW1は、UPDIモードとシリアル通信モードの切り替えスイッチです。シルクのUPDIの側に倒すとUPDIモード、Dataの側に倒すとシリアル通信モードです。

SW2は、本アダプターから5Vを供給するかどうかを選択します。シルクのONの側に倒すと5Vを供給し、OFFの側に倒すと供給しません。マイコンに対して別の経路で電源を供給済みの場合はOFFにしてください。


## 完成品

T.B.D.
<!--
[![完成品](https://raw.githubusercontent.com/k-takata/PCB_avr_dx_unbricker/master/images/unbricker-thumb.jpg)](https://raw.githubusercontent.com/k-takata/PCB_avr_dx_unbricker/master/images/unbricker.jpg)
-->

## License

CC0
