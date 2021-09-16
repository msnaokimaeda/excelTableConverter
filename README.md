# excelTableConverter
A5M2で出力されたテーブルをmd形式のテーブルに変換する

# HoWToUse
1.A5M2の「テーブル定義書作成」で作成されたExcelファイルのカラム情報等のテーブルを任意のテキストファイルにコピーして保存。
2.先ほど保存したテキストファイルをexcelTableConverter.exeにドラッグ＆ドロップすると、テキストファイルの下の行にmd形式のテーブルが出力される

# Notice
* Windows1064bitで動作確認済み(32bitもプログラム実行時にRAXをEAXにしてくれるとかするかも)
* どでかいテーブルをmd形式に変えたい場合は接頭辞がMAX_の定数を変える
