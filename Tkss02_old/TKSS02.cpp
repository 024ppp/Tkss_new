//---------------------------------------------------------------------------
//
//  TKSS02.cpp
//    【出荷検査システム－レポート出力】
//    WinMain関数の定義
//
//  作成者
//    田村　敦司
//
//---------------------------------------------------------------------------
#include <vcl.h>
#include "Unit1.h"

#pragma hdrstop
USERES("TKSS02.res");
USEFORM("Unit1.cpp", Form1);
USEFORM("Unit2.cpp", Form2);
USEUNIT("Unit3.cpp");
USEUNIT("Unit4.cpp");
USEUNIT("Unit5.cpp");
//---------------------------------------------------------------------------
AnsiString str;
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
	mx = CreateMutex(NULL,true,"ID_TKSS02");
    if( GetLastError() ){
    	// 作成失敗
        ShowMessage("このプログラムは既に起動されています。");
        exit(-1);
    }

	try	{
		Application->Initialize();
		Application->CreateForm(__classid(TForm1), &Form1);
		Application->CreateForm(__classid(TForm2), &Form2);
		str = Arg;
        Form1->ExtractCode_Report(str);
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
