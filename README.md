# usbrh-hidapi
============

## これはなに？
Strawberry Linux Co., Ltd. の USBRH から温度と湿度の値を取得します。
標準的なLinux環境において、ユーザランドで動作するプログラムです。
hidapi を使い、簡潔に書かれています。

## usbrh ( https://github.com/m24o8l/usbrh ) との違いは？
確信はないですが、湿度の計算に間違いがあるようで、スペックシート ( http://www.farnell.com/datasheets/317085.pdf ) の通りに直しました。
具体的には t1-25 ではなく、tc-25 のようです。

usbrh は libusb の古いAPIを使っているため、冗長な記述になっています。
このコードは libusb よりも高水準な hidapi を使い簡潔に書かれているため、バグが少ない可能性が高いです。

usbrh を手元の環境で実行すると、2回目以降でエラーになり、使えませんでした。エラーメッセージによれば、libusb の API の使い方の問題があるようでした。

## 謝辞
生データから温度・湿度の計算に関して usbrh ( https://github.com/m24o8l/usbrh )  を参考にさせていただきました。

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
