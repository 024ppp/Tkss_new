//---------------------------------------------------------------------------
//
//  TKSS08.cpp
//    �y�o�׌����V�X�e���|�n���f�B�[�^�[�~�i�������e�i���X�z
//    WinMain�֐��̒�`
//
//  �쐬��
//    �c���@�֎i
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
	mx = CreateMutex(NULL,true,"ID_TKSS08");
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