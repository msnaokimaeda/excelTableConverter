#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD 256
#define MAX_ROW 50
#define MAX_COLUMN 7

#define VB 0x7C

#define HT 0x09
#define SPACE 0x20
#define CR 0x0D
#define LF 0x0A
#define TERMINALCHAR 0x0

int main(int argc, char *argv[]){
    // argv[1] = "sample.txt";
    // argc = 2;
    // ドロップされたファイルがない場合は終了
    if (argc < 2) return 0;

    // ドロップされたファイルのパス
    char* pAbsolutePath = argv[1];
    FILE* fp = fopen(pAbsolutePath, "r+");

    // ファイル読み込み失敗時
    if(fp == NULL){
        fclose(fp);
        return 0;
    };

    // 入力値を"|"ありのテーブル形式に変換
    char str[MAX_WORD];
    char* pOutPut[MAX_ROW];
    int row = 0;
    while(fgets(str, MAX_WORD, fp) != NULL) {
        int inputindex = 0;
        int outputIndex = 0;

        // 一行分のメモリを確保
        char* outPutStr = (char*)calloc(MAX_WORD,sizeof(char));
        if (outPutStr == NULL) return 0;

        // 最初だけ"| "を入れておく
        outPutStr[outputIndex++] = VB;
        int cntVB = 0;
        outPutStr[outputIndex++] = SPACE;

        // 前回の文字
        int prevChar = 0;

        while(1){
            // 1バイト文読み取り
            char strHex = str[inputindex];

            // 改行 or NULL文字で終了
            if(strHex == CR || strHex == LF || strHex == TERMINALCHAR){
                // 未入力カラムがある場合、その分だけ"  |"を入れる
                if(cntVB < MAX_COLUMN+1){
                    outPutStr[outputIndex++] = SPACE;
                    outPutStr[outputIndex++] = VB;
                    cntVB++;

                    int rest = MAX_COLUMN - cntVB;
                    while(rest){
                        outPutStr[outputIndex++] = SPACE;
                        outPutStr[outputIndex++] = SPACE;
                        outPutStr[outputIndex++] = VB;
                        rest--;
                    }
                }
                break;
            }

            if(strHex == HT){
                if(prevChar != SPACE){
                    // 前回がタブか文字の場合
                    outPutStr[outputIndex++] = SPACE;
                    outPutStr[outputIndex++] = VB;
                    cntVB++;
                    outPutStr[outputIndex++] = SPACE;
                }
                prevChar = HT;
            }else{
                outPutStr[outputIndex++] = strHex;
                prevChar = strHex;
            }
            inputindex++;
        }
        pOutPut[row] = outPutStr;
        row++;
	}

    // 結果の書き込み
    for(int i=0;i<=row-1;i++){
        fprintf(fp,"%s","\n");
        if(i==0){
            fprintf(fp,"%s","| # | 論理名 | 物理名 | データ型 | 必須 | デフォルト | コメント |");
            fprintf(fp,"%s","\n");
            fprintf(fp,"%s","|:--:|:--:|:--:|:--:|:--:|:--:|:--:|");
            fprintf(fp,"%s","\n");
        }
        fprintf(fp,"%s", pOutPut[i]);
        free(pOutPut[i]);
    }

    fclose(fp);

    return 0;
}

