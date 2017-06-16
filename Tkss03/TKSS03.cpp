//---------------------------------------------------------------------------
//
//  TKSS03.cpp
//    �y�o�׌����V�X�e���|���l���O�o�^�z
//    WinMain�֐��̒�`
//
//  �쐬��
//    �s��@�a�O
//
//---------------------------------------------------------------------------
#include <vcl.h>
#include "Unit1.h"

#pragma hdrstop
USERES("Tkss03.res");
USEFORM("Unit1.cpp", Form1);
USEFORM("Unit2.cpp", Form2);
USEFILE("Tkss03.h");
USEUNIT("UnitDataAccess.cpp");
//---------------------------------------------------------------------------
AnsiString str;

HANDLE mx;

//---------------------------------------------------------------------------
//
//  �T�v
//    WinMain �֐�		�FWindows�A�v���P�[�V�����̃��C���G���g���|�C���g�ł��B
//
//  �@�\����
//    �v���O�����̂Q�d�N�����`�F�b�N���܂��B
//    �e�t�H�[�����쐬���܂��B
//    �A�v���P�[�V���������s���܂��B
//
//  �p�����^����
//    HINSTANCE(1)		�F�A�v���P�[�V�����̃C���X�^���X�n���h��
//    HINSTANCE(2)		�F���̃A�v���P�[�V�����̑O�̃C���X�^���X�̃n���h��
//    LPSTR				�F�k���ŏI���R�}���h���C����������w���|�C���^
//    int				�F�A�v���P�[�V�����E�B���h�E�̕\���w��p����
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR Arg, int)
{
	mx = CreateMutex(NULL,true,"ID_TKSS03");
    if( GetLastError() ){
    	// �쐬���s
        ShowMessage("���̃v���O�����͊��ɋN������Ă��܂��B");
        exit(-1);
    }

    try {
        Application->Initialize();
        Application->CreateForm(__classid(TForm1), &Form1);
		Application->CreateForm(__classid(TForm2), &Form2);
		str = Arg;
        Form1->ExtractCode(str);

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







