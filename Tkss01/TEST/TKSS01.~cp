//---------------------------------------------------------------------------
#include <vcl.h>
#include "Unit1.h"

#pragma hdrstop
#define WM_COM1   WM_USER + 4010  // COM1 要求データ送信メッセージ
#define WM_COM2   WM_USER + 4011  // COM2 要求データ送信メッセージ

USERES("Tkss01.res");
USEFORM("Unit1.cpp", Form1);
USEFORM("Unit2.cpp", Form2);
USEFORM("Unit3.cpp", Form3);
USEFORM("Unit4.cpp", Form4);
USEFORM("Unit5.cpp", Form5);
USEFORM("Unit6.cpp", Form6);
USEFORM("Unit7.cpp", Form7);
USEFORM("Unit8.cpp", Form8);
USEFORM("Unit9.cpp", Form9);
USEUNIT("UnitDataAccess.cpp");
USEUNIT("Thread.cpp");
USEFILE("Tkss01.h");
USEUNIT("StdComm32.cpp");
USEUNIT("CommThread.cpp");
USEUNIT("DrawGlaph.cpp");
USEUNIT("HTComm.cpp");
USEUNIT("UnitLot.cpp");
USEUNIT("ThreadSozaiMain.cpp");
USEUNIT("ThreadSozaiRire.cpp");
USEUNIT("ThreadSozaiSyka.cpp");
USEFORM("Unit10.cpp", Form10);
USEFORM("Unit12.cpp", Form12);
//---------------------------------------------------------------------------
AnsiString str;
HANDLE mx;

//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR Arg, int)
{
	mx = CreateMutex(NULL,true,"ID_TKSS01");
    if( GetLastError() ){
    	// 作成失敗
        ShowMessage("このプログラムは既に起動されています。");
        return -1;
    }

	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TForm1), &Form1);
         Application->CreateForm(__classid(TForm2), &Form2);
         Application->CreateForm(__classid(TForm3), &Form3);
         Application->CreateForm(__classid(TForm4), &Form4);
         Application->CreateForm(__classid(TForm5), &Form5);
         Application->CreateForm(__classid(TForm6), &Form6);
         Application->CreateForm(__classid(TForm7), &Form7);
         Application->CreateForm(__classid(TForm8), &Form8);
         Application->CreateForm(__classid(TForm9), &Form9);
         Application->CreateForm(__classid(TForm10), &Form10);
         Application->CreateForm(__classid(TForm12), &Form12);
         str = Arg;
        Form1->ExtractCode(str);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------




