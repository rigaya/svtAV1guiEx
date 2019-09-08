
# 拡張 SVT-AV1 出力(GUI) Ex  
by rigaya

拡張 SVT-AV1 出力(GUI) Ex (svtAV1guiEx) は、[SVT-AV1](https://github.com/OpenVisualCloud/SVT-AV1)を使用してエンコードを行うAviutlの出力プラグインです。

## ダウンロード & 更新履歴
[rigayaの日記兼メモ帳＞＞](http://rigaya34589.blog135.fc2.com/blog-category-5.html)

## 基本動作環境
Windows 7, 8.1, 10 (x64)  
Aviutl 1.00 以降 推奨

x86(32bit)環境では動作しません。

## svtAV1guiExの使用方法
同梱のSvtAv1EncApp.exeとともに、[mp4box](https://gpac.wp.imt.fr/downloads/)/[mkvmerge](https://mkvtoolnix.download/downloads.html#windows)、さらに追加で音声エンコーダが必要です。

## svtAV1guiEx 使用にあたっての注意事項
無保証です。自己責任で使用してください。  
拡張 SVT-AV1 出力(GUI) Exを使用したことによる、いかなる損害・トラブルについても責任を負いません。  

## iniファイルによる拡張
svtAV1guiEx.iniを書き換えることにより、音声エンコーダやmuxerのコマンドラインを変更できます。また音声エンコーダを追加することもできます。

デフォルトの設定では不十分だと思った場合は、iniファイルの音声やmuxerのコマンドラインを調整してみてください。


## ソースコードについて
- MITライセンスです。

### ソースの構成
VCビルド  
文字コード: UTF-8-BOM  
改行: CRLF  
インデント: 空白x4  
