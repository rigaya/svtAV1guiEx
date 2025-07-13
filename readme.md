
# 拡張 SVT-AV1 出力(GUI) Ex  
by rigaya  

拡張 SVT-AV1 出力(GUI) Ex (svtAV1guiEx) は、[SVT-AV1](https://gitlab.com/AOMediaCodec/SVT-AV1)を使用してエンコードを行うAviutlの出力プラグインです。

## ダウンロード & 更新履歴
[こちら＞＞](https://github.com/rigaya/svtAV1guiEx/releases)

## 想定動作環境
Windows 10/11 (x64)  
Aviutl 1.00 以降 推奨

x86(32bit)環境では動作しません。

## svtAV1guiEx 使用にあたっての注意事項
無保証です。自己責任で使用してください。  
拡張 SVT-AV1 出力(GUI) Exを使用したことによる、いかなる損害・トラブルについても責任を負いません。  

## svtAV1guiEx の AviUtl2 への導入・更新

> [!IMPORTANT]
> AviUtl(無印) 向けには、後述の[AviUtl (無印) への導入・更新](#svtAV1guiEx-の-aviutl-無印-への導入・更新)をご覧ください。

### ダウンロード

まず、AviUtl**2**_svtAV1guiEx_x.xx_install.exe を[こちら](https://github.com/rigaya/svtAV1guiEx/releases)からダウンロードします。

### AviUtl2 への導入・更新

ダウンロードしたexeファイルをダブルクリックして開きます。

![exeのダブルクリック](./data/svtAV1guiEx_1_29_install_aviutl2_01.png)

インストールしますか? とでたら [はい] をクリックします。

![インストールしますか](./data/svtAV1guiEx_1_29_install_aviutl2_02.png)

自動的にアーカイブが展開され、インストールが開始されます。

![exeのダブルクリック](./data/svtAV1guiEx_1_29_install_aviutl2_03.png)

svtAV1guiExの動作に必要な追加モジュール(VC runtime)の導入が追加で必要な環境では、ユーザーアカウント制御画面が表示されます。
その場合は、 [はい] をクリックします。
_環境によっては準備が不要な場合があり、その場合は表示されません。_

<img src="./data/svtAV1guiEx_1_29_install_aviutl2_04.png" width="360px">

下記のような画面になり、「svtAV1guiEx を使用する準備が完了しました。」と出れば終了です。
ウィンドウを閉じ、AviUtl2を起動してsvtAV1guiExが追加されているか確認してください。

![インストール完了](./data/svtAV1guiEx_1_29_install_aviutl2_05.png)


## svtAV1guiEx の Aviutl (無印) への導入・更新

### ダウンロード

まず、svtAV1guiExを[こちら](https://github.com/rigaya/svtAV1guiEx/releases)からダウンロードします。

### 導入・更新

ダウンロードしたzipファイルをダブルクリックして開きます。中身はこんな感じです。

![zipファイルの中身](./data/svtAV1guiEx_1_00_install_02.png)

中身をすべてAviutlフォルダにコピーします。

> [!IMPORTANT]
> Aviutl2では、
> - exe_filesフォルダをAviutlフォルダの中に、
> - ```plugins```フォルダの**中身**を全て```C:\ProgramData\aviutl2\Plugin```の中に
>
> それぞれコピーしてください。

![中身のコピー](./data/svtAV1guiEx_1_00_install_03.png)

更新時には、下記のように上書きするか聞いてくることがあります。

その場合には「ファイルを置き換える」を選択して上書きしてください。

![上書き](./data/svtAV1guiEx_1_00_install_04.png)
  
  
  
このあとAviutlをダブルクリックして起動してください。

初回起動時に必要に応じて下の図のようにsvtAV1guiExの使用準備をするというメッセージが出ます。環境によっては準備が不要な場合があり、その場合は表示されません。

OKをクリックすると使用準備が開始されます。

![初回起動時](./data/svtAV1guiEx_1_00_install_05.png)
  
  
  
下の図のように、「この不明な発行元からのアプリがデバイスに変更を加えることを許可しますか?」というメッセージが表示されますので、「はい」をクリックしてください。

![UAC](./data/svtAV1guiEx_1_00_install_06.png)
  
  
  
下の図のようなウィンドウが表示され、svtAV1guiExの使用に必要なモジュールがインストールされます。

エラーなくインストールが完了すると下記のように表示されますので、右上の[x]ボタンでウィンドウを閉じてください。

![auo_setup](./data/svtAV1guiEx_1_00_install_11.png)

これで使用準備は完了です。

### 確認

svtAV1guiExがAviutlに認識されているか確認します。

Aviutlの [その他] > [出力プラグイン情報]を選択します。

![出力プラグイン情報](./data/svtAV1guiEx_1_00_install_07.png)


svtAV1guiEx 1.xxが表示されていれば成功です。

![確認](./data/svtAV1guiEx_1_00_install_09.png)


### エンコード
[ ファイル ] > [ プラグイン出力 ] > [ 拡張 SVT-AV1 出力 (GUI) Ex ] を選択し、出力ファイル名を入力して、「保存」をクリックしてください。

![プラグイン出力](./data/svtAV1guiEx_1_00_install_14.png)

エンコードが開始されます。

![エンコード](./data/svtAV1guiEx_1_00_install_10.png)

エンコードが完了するまで待ちます。お疲れ様でした。


## 手順通り導入してもAviutlの出力プラグイン情報に表示されない場合

- 下記ファイルがコピー先のAviutlフォルダ内に存在するか確認してみてください。
  最低限下記ファイルが導入には必須です。まれにウイルス対策ソフト等により、削除されている場合があります。

  - Aviutlフォルダ
    - exe_files [フォルダ]
      - auo_setup(.exe)
      - auo_setup(.ini)
      - check_dotnet(.dll)
      - check_vc(.dll)
      - VC_redist.x86(.exe)

    - plugins [フォルダ]
      - auo_setup.auf
      - svtAV1guiEx.auo
      - svtAV1guiEx(.ini)
  
  - 上記ファイルが存在しない場合
    再度exe_filesフォルダとpluginsフォルダのコピーを行ってみてください。
    それでもファイルが消えてしまう場合は、ウイルス対策ソフトによってファイル削除がされていないかご確認ください。
    
  - 上記ファイルが存在するのにsvtAV1guiExが認識されない場合
    まずAviutlを終了したうえで、exe_filesフォルダ内のVC_redist.x86(.exe)をダブルクリックで実行してください。その後、再度Aviutlを起動し、再度確認してみてください。

## 多言語対応

現在、日本語、英語、中国語の切り替えに対応しています。

中国語については、Aviutlの中国語対応をされているNsyw様に翻訳いただきました。メッセージ量の多い中、ご対応いただき、ありがとうございました！

他の言語については、svtAV1guiEx.auoと同じフォルダに下記2ファイルを置くことで、新たな言語を追加できます。

| ファイル名 | 翻訳元 |
|:---        |:---   |
| svtAV1guiEx.<2文字の言語コード>.lng | svtAV1guiEx.ja.lng |
| svtAV1guiEx.<2文字の言語コード>.ini | svtAV1guiEx.ja.ini |

いずれもUTF-8で保存してください。


## iniファイルによる拡張
svtAV1guiEx.iniを書き換えることにより、音声エンコーダやmuxerのコマンドラインを変更できます。また音声エンコーダを追加することもできます。

デフォルトの設定では不十分だと思った場合は、iniファイルの音声やmuxerのコマンドラインを調整してみてください。

## svtAV1guiEx の Aviutl からの削除

svtAV1guiEx の Aviutl から削除するには、"plugins" フォルダ内の下記ファイルとフォルダを削除してください。

- [フォルダ] svtAV1guiEx_stg
- [ファイル] svtAV1guiEx.auo
- [ファイル] svtAV1guiEx.conf (存在する場合のみ)
- [ファイル] svtAV1guiEx(.ini)
- [ファイル] auo_setup.auf

![削除](./data/svtAV1guiEx_1_00_uninstall_01.png)


## ソースコードについて
- MITライセンスです。

### ソースの構成
VCビルド  
文字コード: UTF-8-BOM  
改行: CRLF  
インデント: 空白x4  
