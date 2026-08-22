# AVR Dx/Ex Unbricker

## 概要

AVR Dx/Exシリーズ用の7.5V系高電圧(HV)プログラミングに対応したUPDI (Unified Program and Debug Interface)書き込み装置です。(ATtinyシリーズの12V系HVプログラミングには対応していません。)  
意図的あるいは事故によりUPDIピンの設定を変更してしまい、通常のUPDI書き込み装置で書き込みができなくなってしまったデバイスに対し、HVパルス(7.5V)を注入することで、再度書き込みができるようにします。

[秋月電子](https://akizukidenshi.com/)の[CH9102F USBシリアル変換モジュールキット Type-C (AE-CH9102F-TYPEC-BO)](https://akizukidenshi.com/catalog/g/g129505/)、または一般的な6pinのシリアルモジュールを接続して使用します。

UPDI部分の回路は[SerialUPDI](https://github.com/SpenceKonde/AVR-Guidance/blob/master/UPDI/jtag2updi.md)に従っています。


## 使用したソフトウェア

* KiCad 10.0
* Arduino IDE 2.3.10
  - [DxCore](https://github.com/SpenceKonde/DxCore) 1.5.11
  - [megaTinyCore](https://github.com/SpenceKonde/megaTinyCore) 2.6.11


## 回路図

[![schema](https://raw.githubusercontent.com/k-takata/PCB_avr_dx_unbricker/master/images/schema.png)](https://raw.githubusercontent.com/k-takata/PCB_avr_dx_unbricker/master/images/schema.pdf)


## 基板パターン図

![PCB pattern](https://raw.githubusercontent.com/k-takata/PCB_avr_dx_unbricker/master/images/pcb-pattern.png)


## 部品表

| Reference |個数|値    | 説明 |
|-----------|----|------|------|
|C1,C2      |   2|0.1μF| |
|C3,C4      |   2|1μF  |チャージポンプ用 (\*1) |
|D1,D3,D4,D8|   1|[BAT43](https://akizukidenshi.com/catalog/g/g113907/) |適当なショットキーバリアダイオード |
|D2         |   1|LED   |φ5mm |
|D5         |   1|[1N4737A](https://www.sengoku.co.jp/mod/sgk_cart/detail.php?code=EEHD-0FMV)|7.5Vツェナーダイオード (\*2) |
|D6         |   1|      |ツェナーダイオード (\*2) |
|D7         |   1|      |ツェナーダイオード (\*2) |
|J1         |   1|      |L型ピンソケット 2x4 (\*3)、AE-CH9102F-TYPEC-BO接続用 |
|J2         |   1|      |ピンヘッダー 1x6、TTLシリアル入力接続用 |
|J3         |   1|      |ピンソケット 1x4、UPDI接続用|
|J4         |   1|      |[L型ピンソケット 1x6](https://akizukidenshi.com/catalog/g/g109862/)、TTLシリアル出力接続用|
|J5         |   1|      |ピンヘッダー 1x3、RTS/DTR切り替え用|
|J6         |   1|      |ピンヘッダー 1x3、書き込み先切り替え用|
|Q1         |   1|[BSS138](https://akizukidenshi.com/catalog/g/g104232/)|Nch MOSFET|
|Q2         |   1|[BSS84](https://akizukidenshi.com/catalog/g/g104269/) |Pch MOSFET|
|R1         |   1|470Ω |黄紫茶金、1/4Wサイズ|
|R2         |   1|4.7kΩ|黄紫赤金、1/4Wサイズ、LEDに合わせて値は適宜調整|
|R3         |   1|4.7kΩ|黄紫赤金、1/4Wサイズ|
|R4,R6      |   2|10kΩ |茶黒橙金、1/4Wサイズ|
|R5         |   1|100kΩ|茶黒黄金、1/4Wサイズ|
|SW1,SW2    |   2|[SS-12D00G3](https://akizukidenshi.com/catalog/g/g115707/)|スライドスイッチ 1回路2接点 基板用|
|SW3        |   1|      |プッシュスイッチ|
|U1         |   1|[AVR64DD28-I/SP](https://akizukidenshi.com/catalog/g/g118314/)|(\*4)|
|U2         |   1|[ATtiny402-SS](https://akizukidenshi.com/catalog/g/g130009/)|(\*4)(\*5)|
|U3         |   1|[TJ7660](https://akizukidenshi.com/catalog/g/g112017/)|ICL7660互換品|

(\*1) データシートでは10μFが推奨されているが、電流はほとんど使用しないので、1μFで十分。  
(\*2) D5を単独で使用するか、D6 + D7の組み合わせで使用する。TP1の電圧が7.5V (Vdd+2.0V以上、8.5V以下)になるようにする。例えば、3.0V + 5.1Vなどの組み合わせでもよいだろう。  
(\*3) 例えば、[L型ピンソケット 2x6](https://akizukidenshi.com/catalog/g/g116795/) (1個分)や[L型ピンソケット 2x15](https://akizukidenshi.com/catalog/g/g113419/) (3個分)などを加工して使用する。  
(\*4) U1またはU2のどちらか1つを使用する。  
(\*5) U2を使用する場合は、ATtiny402を直接載せるか、[SOP8変換基板](https://akizukidenshi.com/catalog/g/g105154)を介して載せるかのどちらかを選択する。  


## UPDI HVプログラミングについて

UPDI (Unified Program and Debug Interface)は、比較的新しいAVRで使われる書き込み方式です。

UPDIには専用のピンを使用しますが、UPDIピンはfuseの設定でGPIOピンに変更することも可能です。しかし、UPDIを無効化してしまうと、次回UPDIで書き込みを行うには特殊な方法でUPDIを有効化する必要があります。そのための方法が高電圧(HV)プログラミングです。

HVプログラミングには2種類あり、1つはATtinyシリーズで使用されている、UPDIピンに12Vのパルスを与える方式で、もう1つはAVR Dx/Exシリーズで使用されている、RESETピンに7.5Vのパルスを与える方式です。

1. ATtinyシリーズ:  
   パワーオンリセット(POR)から8.8ms以内にUPDIピンに12Vパルスを与える。  
   PORから時間内にパルスを与えなければ、ピンの機能と干渉する可能性がある。
2. AVR Dx/Exシリーズ:  
   RESETピンに7.5Vパルスを与えてから65ms以内にNVMPROGキーを送出する。  
   時間内にNVMPROGキーの送出まで終わらなければ、自動的にリセットが掛かる。  
   ATtinyとは異なり、独立したRESETピンが存在し、出力として使用することはできないので、PORからHVパルスまでの時間的制約はない。

AVR Dx/Ex Unbrickerは、AVR Dx/ExシリーズのHVプログラミングのみに対応しており、7.5VパルスとNVMPROGキーの送出を行うようになっています。

**参考資料:**

* [ATtiny202/204/402/404/406 Data Sheet](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATtiny202-204-402-404-406-DataSheet-DS40002318A.pdf) [PDF]  
  "30. UPDI - Unified Program and Debug Interface" や "33. Electrical Characteristics" (33.18. UPDI Timing) などを参照。
* [AVR64DD32/28 Datasheet](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/AVR64DD32-28-Complete-DataSheet-DS40002315.pdf) [PDF]  
  "34. UPDI - Unified Program and Debug Interface" や "36. Electrical Characteristics" (36.18. UPDI) などを参照。


## 動作確認済みデバイス

* AVR64DD28


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

RESETピンからは7.5Vのパルスが出力されますので、接続先はそのことを考慮した回路になっている必要があります。

J4は、一般的な6pinのTTLシリアルコネクターとなっています。J1接続時、J4の6番ピンの機能はJ5にジャンパーピンを挿すことでRTSかDTRのどちらかを選択できます。(J2接続時、J4の6番ピンはJ2の6番ピンと直結されるため、その機能は使用しているシリアルモジュール次第となります。)

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

ファームウェアをU1またはU2に書き込むには、スイッチやコネクター類は以下のように設定、あるいは接続します。

|部品 | 設定・接続     |
|-----|----------------|
|U1/U2| どちらかを搭載 |
| SW1 | **UPDI**       |
| SW2 | 任意           |
|J1/J2| どちらかを接続 |
| J3  | 未接続         |
| J4  | 未接続         |
| J5  | 任意           |
| J6  | **FW**         |

Arduino IDEで、srcディレクトリ内のスケッチを開きます。  
U1/U2のどちらを搭載したかに合わせて、ボードとChipを適切に選択します。

|部品| ボード                                  | Chip      |
|----|-----------------------------------------|-----------|
| U1 | DxCore → AVR DD-series (no bootloader) | AVR64DD28 |
| U2 | megaTinyCore → ATtiny412/402/212/202   | ATtiny402 |

書き込み装置をSerialUPDIに設定して書き込みを行えばファームウェアが書き込まれます。


### UPDI書き込み

#### 通常モード

スイッチやコネクター類は以下のように設定、あるいは接続します。

|部品 | 設定・接続       |
|-----|------------------|
| SW1 | **UPDI**         |
| SW2 | 通常はON         |
|J1/J2| どちらかを接続   |
| J3  | ターゲットを接続 |
| J4  | 通常は未接続     |
| J5  | 任意             |
| J6  | **Target**       |

SW2は通常はONにしますが、ターゲットに別経路から電源が供給されている場合はOFFにします。  
J4は通常は未接続にしますが、接続されていても問題はありません。

Arduino IDEから、書き込み装置をSerialUPDIに設定すれば書き込みができます。


#### HVプログラミング

スイッチやコネクター類は以下のように設定、あるいは接続します。

|部品 | 設定・接続       |
|-----|------------------|
| SW1 | **UPDI**         |
| SW2 | 通常はON         |
|J1/J2| どちらかを接続   |
| J3  | ターゲットを接続 |
| J4  | 未接続           |
| J5  | 任意             |
| J6  | **Target**       |

SW2は通常はONにしますが、ターゲットに別経路から電源が供給されている場合はOFFにします。  
J3は、ターゲットの回路がHVに対応していれば問題ありませんが、チップ単体で接続する方が安全でしょう。  
J4は未接続にしておくことを推奨します。

接続した状態で、STARTボタンを押すと、7.5VパルスとNVMPROGキーの送出が行われ、UPDIが有効化されます。そのあとで通常と同様の手順でArduino IDEから書き込み操作を行えば書き込みができるはずです。


### シリアル通信

スイッチやコネクター類は以下のように設定、あるいは接続します。

|部品 | 設定・接続       |
|-----|------------------|
| SW1 | **Serial**       |
| SW2 | 通常はON         |
|J1/J2| どちらかを接続   |
| J3  | 通常は未接続     |
| J4  | ターゲットを接続 |
| J5  | 用途に応じて選択 |
| J6  | 任意             |

J3は通常は未接続にしますが、接続されていても問題はありません。  
J1接続時、J4の6番ピンの機能はJ5にジャンパーピンを挿すことでRTSかDTRのどちらかを選択できます。


## 完成品

[![完成品](https://raw.githubusercontent.com/k-takata/PCB_avr_dx_unbricker/master/images/unbricker-thumb.jpg)](https://raw.githubusercontent.com/k-takata/PCB_avr_dx_unbricker/master/images/unbricker.jpg)


## License

CC0


## 参考プロジェクト

UPDI HVプログラミングに対応したプロジェクトや参考情報へのリンクです。

### ATtiny専用

12V系HVプログラミングに対応したプロジェクトはかなりたくさんあります。以下はその一部です。（ただし、POR後、規定時間内にHVパルスを与えるようになっているものはあまり多くありません。）

* [todopapa/UPDI_HV_WRITER-w-RESET: This is a new AVR ATTINY series UPDI programmer with HV pulse injection avility on power on reset timing.](https://github.com/todopapa/UPDI_HV_WRITER-w-RESET)
* [DIY Arduino Nano HV UPDI Programmer - Electronics-Lab](https://www.electronics-lab.com/diy-arduino-nano-hv-updi-programmer/)
* [UPDI HVP のための 12V を得る方法の試行 | シャポログ](https://blog.shapoco.net/2025/0308-updi-hvp-with-ae-ch340e/)
* [Dlloydev/Updi-Key: This DIY open source hardware connects inline with any UPDI programmer to provide a HV UPDI programming solution for tinyAVR® 0/1/2 series MCUs. Compatible with UPDI programmers that operate with jtag2updi, avrdude, pyupdi, MPLAB X IDE, MPLAB X IPE, PlatformIO and Arduino IDE using any target voltage from 3 to 5V.](https://github.com/Dlloydev/Updi-Key)
* [Create a 12V version of microUPDI · Issue #3 · MCUdude/microUPDI](https://github.com/MCUdude/microUPDI/issues/3)

### ATtiny / ARV Dx/Ex 両対応

* [\[MULTIX UPDI4AVR Programmer\] modernAVR世代専用HV対応プログラム書込器 | 朝日薫 / K.Sato](https://askn37.github.io/product/UPDI4AVR/)
