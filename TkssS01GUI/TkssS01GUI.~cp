//---------------------------------------------------------------------------
#include <vcl.h>
#include "Unit1.h"

#pragma hdrstop
USERES("TkssS01GUI.res");
USEFORM("Unit1.cpp", Form1);
USEFILE("Main.h");
USEUNIT("Unit2.cpp");
USEUNIT("Unit3.cpp");
//---------------------------------------------------------------------------
HANDLE mx;

//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR Arg, int)
{
	mx = CreateMutex(NULL,true,"ID_TkssS01GUI");
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
