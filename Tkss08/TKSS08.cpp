//---------------------------------------------------------------------------
//
//  TKSS08.cpp
//    【出荷検査システム－ハンディーターミナルメンテナンス】
//    WinMain関数の定義
//
//  作成者
//    田村　敦司
//
//---------------------------------------------------------------------------
#include <vcl.h>
#include "Unit1.h"

#pragma hdrstop
USERES("TKSS08.res");
USEFORM("Unit1.cpp", Form1);
USEUNIT("StdComm32.cpp");
//---------------------------------------------------------------------------
HANDLE mx;

//---------------------------------------------------------------------------
//
//  概要
//    WinMain 関数		：Windowsアプリケーションのメインエントリポイントです。
//
//  機能説明
//    プログラムの２重起動をチェックします。
//    各フォームを作成します。
//    アプリケーションを実行します。
//
//  パラメタ説明
//    HINSTANCE(1)		：アプリケーションのインスタンスハンドル
//    HINSTANCE(2)		：このアプリケーションの前のインスタンスのハンドル
//    LPSTR				：ヌルで終わるコマンドライン文字列を指すポインタ
//    int				：アプリケーションウィンドウの表示指定用整数
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR Arg, int)
{
	mx = CreateMutex(NULL,true,"ID_TKSS08");
    if( GetLastError() ){
    	// 作成失敗
        ShowMessage("このプログラムは既に起動されています。");
        exit(-1);
    }

    try {
         Application->Initialize();
         Application->CreateForm(__classid(TForm1), &Form1);
         Form1->sCOMMAND = Arg;

         Application->Run();
    }
    catch (Exception &exception) {
         Application->ShowException(&exception);
    }

    // 最後の return 0 の前に追加
    ReleaseMutex(mx);

    return 0;
}
//---------------------------------------------------------------------------
