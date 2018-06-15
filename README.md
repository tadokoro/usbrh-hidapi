# usbrh-hidapi
============

## これはなに？
Strawberry Linux Co., Ltd. の USBRH から温度と湿度の値を取得します。
標準的なLinux環境において、ユーザランドで動作するプログラムです。
hidapi ( https://github.com/signal11/hidapi ) を使い、簡潔に書かれています。

## usbrh ( https://github.com/m24o8l/usbrh ) との違いは？
湿度の計算に間違いがあるようで、usbrh-hidapi はスペックシート ( http://www.farnell.com/datasheets/317085.pdf ) の通りに実装しました。
具体的には t1-25 ではなく、tc-25 のようです。

usbrh は libusb の古いAPIを使っているため、冗長な記述になっています。
usbrh-hidapi のコードは libusb よりも高水準な hidapi を使い簡潔に書かれているため、バグが少ない可能性が高いです。

usbrh を手元の環境で実行すると、2回目以降でエラーになり、使えませんでした。エラーメッセージによれば、libusb の API の使い方の問題があるようでした。

## USBRH driver for Linux ( http://green-rabbit.sakura.ne.jp/usbrh/ ) との違いは？
このドライバは、カーネルモジュールで実装されています。

一般的に、カーネルモジュールのエラーはカーネル全体をクラッシュさせる可能性があり、最大限避けるべきです。
ユーザランドで実現可能なことをカーネルで実装する必要はありません。

カーネル内は浮動小数点演算を避けるのが一般的であり、このドライバでは一定の数を掛けて整数に直して計算しています。
しかし、この手法では -2.8e-6 のような絶対値の小さな数字を扱う部分で誤差が大きくなってしまいます。

Linux kernelはAPIの変更が激しく、最新のLinuxカーネルで動作する保証がありません。

## 謝辞
生データから温度・湿度の計算に関して usbrh ( https://github.com/m24o8l/usbrh )  と USBRH driver for Linux ( http://green-rabbit.sakura.ne.jp/usbrh/ )  を参考にさせていただきました。

しかし、usbrh-hidapi はすべて自分で書いています。
 
## 動作を確認した環境
Debian 9

## コンパイル
     $ apt install -y libhidapi-dev pkg-config
     $ make
 
## 動作例
    $ sudo ./usbrh
    27.120000 64.897741

## LICENSE
see LICENSE file
