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
    	// �쐬���s
        ShowMessage("���̃v���O�����͊��ɋN������Ă��܂��B");
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

    // �Ō�� return 0 �̑O�ɒǉ�
    ReleaseMutex(mx);

    return 0;
}
//---------------------------------------------------------------------------
