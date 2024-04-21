# r7kamura/qmk_firmware

Corne V4 (a.k.a. crkbd rev4) で薙刀式という日本語入力方式を実現するための、QMKファームウェア用のリポジトリです。

## ファイル構造

以下のリポジトリに含まれるファイルを利用しています。

- https://github.com/qmk/qmk_firmware
- https://github.com/foostan/kbd_firmware
- https://github.com/eswai/qmk_firmware

具体的な構造は以下の通りです。

### qmk/qmk_firmware

ベースのファイル構造は、qmk/qmk_firmwareをforkしたものになっています。

### foostan/kbd_firmware

foostan/kbd_firmwareで公開されている新しいcrkbd向けの実装を、crkbd_2ndという名称のキーボードとして、qmk/qmk_firmwareのkeyboards以下に加えています。

### eswai/qmk_firmware

eswai/qmk_firmwareで公開されているcrkbd rev1-3向けのnaginata_v15 keymapを、crkbd rev4で利用できるよう改変した上で、crkbd_2ndのkeymapとして加えています。また、自身の用途向けにキーマップを幾つか調整しています。

## コンパイル方法

以下のコマンドでコンパイルする想定です。

```
qmk compile -kb crkbd_2nd/rev4/standard -km naginata_v15
```
