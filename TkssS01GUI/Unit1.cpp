//---------------------------------------------------------------------------
//
//  Unit1.cpp
//    �y�o�׌����V�X�e���|���������o�^�����z
//    ���C���t�H�[���iTForm1�N���X�j�̃����o�֐��̒�`
//
//  �쐬��
//    �����@�b��
//
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"



//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;      

//�f�[�^�������ʊi�[
structKSD29 KSD29;      // �f�ޑ�����уf�[�^�O���荞�ݓ���
structKSD21 KSD21;      // �o�� �f�ޑ�����уf�[�^
structKSD22 KSD22;      // �o�� �f�ޑ�����і��׃f�[�^
structKSD23 KSD23;      // �o�� �f�ޑ�����ї�O�f�[�^
structKD_1  KD_1;       // ���� �f�ޑ���f�[�^

structFixStr FixStr[18]; // �e�f�ނ̌Œ蕶����
int FixStrNum;           // �f�ނ̎��

AnsiString MEMOStr[18];  // �e����l�̔��l
AnsiString sBufSQL;      // �o�b�t�@ SQL��

//�f�ޑ�����уf�[�^�iKSD21�j��
//�X�V�񐔁E�f�ޑ���X�V�ɕK�v�ȃL�[��ۑ�
TStrings *sDTKSHIN;    	 // ���Ӑ�i��
TStrings *sLOTNO; 		 // ���b�gNO
TStrings *sHINBAN; 		 // ���Еi��
int isDTKSHINNum;        // �f�[�^��

AnsiString sExecDate;    // �������s��
AnsiString sStartTime;   // �������s����


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}

/*----------------------------------------------------------------------------*/
//
//  �T�v
//    OnTimer�C�x���g	�FInterval �v���p�e�B�Ŏw�肵�����Ԃ��o�߂���Ɣ������܂��B
//
//  �@�\����
//    5�b�J�E���g�_�E����i���~�\�j�A���������o�^�������J�n���܂�
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::Tmr_CountDownTimer(TObject *Sender)
{
    Tmr_CountDown->Tag = Tmr_CountDown->Tag - 1;
    if( Tmr_CountDown->Tag <= 0 ){
        Tmr_CountDown->Enabled = false;
        Btn_Exit->Visible = false;

		// ���������o�^�����J�n
        Main();

    } else{
		Lbl_2->Caption = "�J�n�܂� " + IntToStr(Tmr_CountDown->Tag) + "�b";
    }
}

/*----------------------------------------------------------------------------*/
//
//  �T�v
//    OnCreate�C�x���g	�FForm1���쐬�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    ���������o�^�������J�n���܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �t�H�[�����쐬�����Ƃ��C�x���g���ȉ��̏����Ŕ������܂��B
//    OnCreate��OnShow��OnActivate��OnPaint
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::FormCreate(TObject *Sender)
{

    if( sCOMMAND.AnsiCompareIC( "/DIRECT" ) == 0 ){
        // ���C�����j���[���烆�[�U�[���N���������́A
        // �����ɏ������J�n���܂�

		// ���������o�^�����J�n
        Main();

    } else {
        // �p�\�R���N�������́A�w�莞�ԂɎ������s���鎞�́A
        // �J�E���g�_�E����i���~�\�j�A�������J�n���܂�
		Lbl_1->Caption = "���Ԍ���DB����o�׌���DB�ւ̈ڍs���J�n���܂��B";
		Lbl_2->Caption = "�J�n�܂� 5�b";
    	Tmr_CountDown->Tag = 5;
        Tmr_CountDown->Enabled = true;
    }
}

/*----------------------------------------------------------------------------*/
//
//  �T�v
//    OnClick�C�x���g	�F�{�^���i�I���j�����������̏���
//
//  �@�\����
//    �v���O�������I�����܂�
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::Btn_ExitClick(TObject *Sender)
{
    Close();
}

/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�			�F���������o�^�����J�n
//
//  �@�\����
//    ���Ԍ���DB����o�׌���DB�փf�[�^���ڍs���܂��B
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::Main()
{

	int iRtn;
	AnsiString sRtn;
	AnsiString sMsg;

	TDateTime dtNow;    	//���݂̓���
	WORD Y,M,D,H,N,S,MS;   	//���݂̓������e�����ɃZ�b�g
	AnsiString sNowDate;
	AnsiString sNowTime;

	Lbl_1->Caption = "���Ԍ���DB����o�׌���DB�ֈڍs���Ă��܂��B";
	Lbl_2->Caption = "���΂炭���҂����������B";
    ListLog->Clear();
    Form1->Refresh();

	//TStrings������
	sDTKSHIN	= new TStringList;    	//���Ӑ�i��
	sLOTNO		= new TStringList; 		//���b�gNO
	sHINBAN		= new TStringList; 		//���Еi��


	//�O����s�����擾
	iRtn = GetKSD29("1");
    if( iRtn < 0 ){
        // �f�[�^�擾���s
        KSD29.UPDYMD = "19900101";
	    KSD29.UPDTIM = "0400";
    }

    // �f�[�^�擾����
    sExecDate = KSD29.UPDYMD;
	sStartTime = KSD29.UPDTIM;

	//���݂̎������擾
	dtNow = Now( );
	DecodeDate(dtNow,Y,M,D);
	DecodeTime(dtNow,H,N,S,MS);
	sNowDate = "";
	sNowDate += FormatFloat("0000",Y);
	sNowDate += FormatFloat("00",M);
	sNowDate += FormatFloat("00",D);
	sNowTime = "";
	sNowTime += FormatFloat("00",H);
	sNowTime += FormatFloat("00",N);

    sMsg = "���������o�^�T�[�r�X�̊J�n�i" + sExecDate + sStartTime + "�j";
    ListLog->Items->Add(sMsg);

	//���������o�^���s
	iRtn = AutoEntry();
	sMsg = "���������o�^���s " + IntToStr(iRtn) + "���X�V���܂����i" + sNowDate + sNowTime + "�j";
    ListLog->Items->Add(sMsg);

	//���s���t�X�V
	sExecDate = sNowDate;
	sRtn = SetKSD29("1",sExecDate);


	Lbl_1->Caption = "���Ԍ���DB����o�׌���DB�ֈڍs���I�����܂����B";
	Lbl_2->Caption = " ";
    Form1->Refresh();

    Close();
}

/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�f�ޑ�����уf�[�^�O���荞�ݓ����f�[�^�擾
//
//  �@�\����
//    KSD29����O���荞�ݓ������擾���܂��B
//
//  �p�����^����
//    AnsiString strFUNC_ID	�F�t�@���N�V�����h�c�iKSD29���������j
//
//  �߂�l
//    int					�F0=�������� -1=�������s
//
//  ���l
//    �Ȃ��B
//
/*----------------------------------------------------------------------------*/
int __fastcall TForm1::GetKSD29(AnsiString strFUNC_ID)
{
	AnsiString sBuf;

	//�f�ޑ�����уf�[�^�O���荞�ݓ����f�[�^�擾
	KSD29.FUNC_ID = strFUNC_ID;
	KSD29.UPDYMD = "";
	KSD29.UPDTIM = "";

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// �⍇�����s
	sBuf = "SELECT FUNC_ID, UPDYMD, UPDTIM FROM KSD29 WHERE  FUNC_ID = ";
	sBuf += KSD29.FUNC_ID;

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	if ( Query1->Bof && Query1->Eof ) {
	//�������� �O��
		return(-1);
	}
	KSD29.UPDYMD = Query1->FieldValues["UPDYMD"];
	KSD29.UPDTIM = Query1->FieldValues["UPDTIM"];


	return(0);
}
/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�f�ޑ�����уf�[�^��荞�ݓ����Z�b�g
//
//  �@�\����
//    KSD29�Ɏ�荞�ݓ������Z�b�g���܂��B
//
//  �p�����^����
//    AnsiString strFUNC_ID	�F�t�@���N�V�����h�c�iKSD29���������j
//    AnsiString strUPDYMD	�F�Z�b�g����X�V��
//
//  �߂�l
//    AnsiString			�F""=�X�V���� �G���[���b�Z�[�W=�X�V���s
//
//  ���l
//    �Ȃ��B
//
/*----------------------------------------------------------------------------*/
AnsiString __fastcall TForm1::SetKSD29(AnsiString strFUNC_ID,AnsiString strUPDYMD)
{
	AnsiString sBufSQL;

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// �⍇�����쐬
	sBufSQL = "update KSD29 set ";
	sBufSQL += "UPDYMD='" + strUPDYMD + "'"	;

	sBufSQL += " WHERE  FUNC_ID = ";
	sBufSQL += strFUNC_ID;

	Query1->SQL->Add(sBufSQL);

	// �₢�������̎��s
	try
	{
		Query1->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		return(e.Message);
	}
	catch(Exception& e)
	{
		return(e.Message);
	}

	return("");


}
//---------------------------------------------------------------------------


