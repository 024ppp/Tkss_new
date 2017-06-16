//---------------------------------------------------------------------------
//
//  Unit1.cpp
//    �y�o�׌����V�X�e���|������ʁz
//    ���C���t�H�[���iTForm1�N���X�j�̃����o�֐��̒�`
//
//  �쐬��
//    �s��@�a�O
//
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit7.h"
#include "Unit8.h"
#include "Unit9.h"
#include "Unit10.h"
#include "Unit12.h"
#include "Thread.h"
#include "ThreadSozaiMain.h"
#include "CommThread.h"
#include "Tkss01.h"
#include "StdComm32.h"
#include <math.h>
//�R���p�C���I�v�V�����u�f�o�b�O�v�Ɓu�����[�X�v�I����Ԃɂ��K�v���s�v���ς��
//�R���p�C���̃o�O���H�H
//#include <windows.h>

// k.k
#include <vector>
using namespace std;
extern bool bLOTCHANGE;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "PERFGRAP"
#pragma link "NumberEdit"
#pragma resource "*.dfm"
TForm1 		*Form1;
// k.y 2003.05.17
//HANDLE		hInfoGlaph;
// k.y 2003.05.17
//extern 	GRAPH_DATA  *pInfoGlaph;
extern 	GRAPH_DATA  pInfoGlaph;
//KSM02_DATA 	*pInfoGlaph;
RSCOM 		RS232;
KIKAKU KIKAKU_MOJI;
bool bKASOU_MOVE;
extern int iPORT_NO;
int iDEBUG;
bool bHANTEI_DISP;
bool bCellWrite;        //�@�킩��̎�荞�ݎ��A�t���O�������I��ON�����邨�܂��Ȃ��B

//�Z�����
extern HANDLE hCELLINFO_SOKU_SYUKA;
extern HANDLE hCELLINFO_RIRE_SYUKA;
extern HANDLE hCELLINFO_SOKU_SOZAI;
extern HANDLE hCELLINFO_RIRE_SOZAI;
extern CELLINFO_DATA *pCELLINFO_SOKU_SYUKA;
extern CELLINFO_DATA *pCELLINFO_RIRE_SYUKA;
extern CELLINFO_DATA *pCELLINFO_SOKU_SOZAI;
extern CELLINFO_DATA *pCELLINFO_RIRE_SOZAI;
extern int iPnl_SOZAI_InsNoCnt;
extern int iPnl_SOZAI_InsNameCnt;
extern int iPnl_SOZAI_InsKikiNameCnt;
extern int iPnl_SOZAI_InsSubBaseCnt;

//���b�g���蓖�ā��j�r�c01
//���b�g���蓖��
extern HANDLE hSOKU_KSD01_DATA;
extern KSD01_DATA *pSOKU_KSD01_DATA;
extern HANDLE hRIRE_KSD01_DATA;
extern KSD01_DATA *pRIRE_KSD01_DATA;

// k.y 2003.05.17
//extern HANDLE		hOldInfoGlaph;

// k.y 2003.05.17
//extern GRAPH_DATA	*pOldInfoGlaph;
extern GRAPH_DATA	pOldInfoGlaph;

int iKikiCnt;
int iSOKU_MEMO_CNT;
int iRIRE_MEMO_CNT;

extern RSCOM RS232;
extern int iRIREKI_KOMKCNT;        	    //�����̍��ڐ�
int	iContCnt;               		    //�o�׌������ڐ�
//extern 	GRAPH_DATA	*pInfoGlaph;
int iSOZAI_DEL_OrCnt;                   //Or�\����
int iSOZAI_DEL_SokuCnt;                 //Or�\����
bool bNGPLOT;
bool bINPUTLOT_OK;					    //���̓��b�gOK�t���O_
bool bQUIT_FLG;
int iPlotCol,iPlotRow;
int     USER_COD;
String  USER_NAM;
String  BUMO_COD;
String  BUMO_NAM;
AnsiString  sMEMO_NAME;
bool bBUNKATU_RIRE[1000];
bool bBUNKATU_SOKU[1000];
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnCreate�C�x���g	�FForm1���쐬�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    ������ʂ̏�Ԃ�ݒ肵�܂��B
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
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{

    // A.T 2003/05/08
    //ThreadSupport = true;		// �X���b�h�Ή�����
    ThreadSupport = false;		// �X���b�h�Ή����Ȃ�

    // K.K
    sHT_LOT = new TStringList;
    sShiji_Data = new TStringList;
    Graph_Format();

    // �f�[�^�x�[�X������
    Database1->Open();


    //�V���A���|�[�g�������R�}���h
    TThread *FourThread = new CommThread( false );
    // �����l�ݒ�

    // ScrollBox�̃C�x���g�擾�p��`
    SaveSBx_Left_SOZAI_WndProc = SBx_Left_SOZAI->WindowProc;
    SBx_Left_SOZAI->WindowProc = SBx_Left_SOZAI_WndProc;
    SaveSBx_Left_SYUKA_WndProc = SBx_Left_SYUKA->WindowProc;
    SBx_Left_SYUKA->WindowProc = SBx_Left_SYUKA_WndProc;
    SaveSBx_vSOKU_MEMO_WndProc = SBx_vSOKU_MEMO->WindowProc;
    SBx_vSOKU_MEMO->WindowProc = SBx_vSOKU_MEMO_WndProc;
    SaveSBx_vRIRE_MEMO_WndProc = SBx_vRIRE_MEMO->WindowProc;
    SBx_vRIRE_MEMO->WindowProc = SBx_vRIRE_MEMO_WndProc;

    // ScrollBox�̈ړ��s�b�`���`
    SBx_Left_SOZAI->VertScrollBar->Smooth = false;
    SBx_Left_SYUKA->VertScrollBar->Smooth = false;
    SBx_Left_SOZAI->VertScrollBar->Increment = 25;
    SBx_Left_SYUKA->VertScrollBar->Increment = 25;
    SBx_vSOKU_MEMO->HorzScrollBar->Smooth = false;
    SBx_vSOKU_MEMO->HorzScrollBar->Increment = (TScrollBarInc)Mem_vSOKU_MEMOORG->Width;
    SBx_vRIRE_MEMO->HorzScrollBar->Smooth = false;
    SBx_vRIRE_MEMO->HorzScrollBar->Increment = (TScrollBarInc)Mem_vRIRE_MEMOORG->Width;
    // StringGrid�̂P��ڂ̕��������������܂��B�ړ��s�b�`���`
    SGr_tRIRE->ColWidths[0]       = SGr_tRIRE->ColWidths[0]       - 1;
    SGr_tRIRE_SOZAI->ColWidths[0] = SGr_tRIRE_SOZAI->ColWidths[0] - 1;
    SGr_tSOKU->ColWidths[0]       = SGr_tSOKU->ColWidths[0]       - 1;
    SGr_tSOKU_SOZAI->ColWidths[0] = SGr_tSOKU_SOZAI->ColWidths[0] - 1;
    SGr_tRIRE_SYUKA->ColWidths[0] = SGr_tRIRE_SYUKA->ColWidths[0] - 1;
    SGr_tSOKU_SYUKA->ColWidths[0] = SGr_tSOKU_SYUKA->ColWidths[0] - 1;

    // �X�v���b�^�[�ʒu�ύX�p�̏����ʒu��ݒ�
    Panel22->Tag 	= Panel22->Height;
    Panel14->Tag 	= Panel14->Width;
    Panel173->Tag 	= Panel173->Height;
    Pnl_skInfo->Tag	= Pnl_skInfo->Width;

    // ������Ԃł̕\���p�l������\���p�l����ݒ肵�܂��B
    Panel22->Height   = 0;		// �f�ތ����@��\��
    //Panel173->Height  = 0;	// ���l�@�@�@�@�\��
    Panel14->Width    = 0;		// ����l�@�@��\��
    //Pnl_skInfo->Width = 0;	// �O���t�@�@�@�\��

    Edt_RIRE_NUM->Height = 18;
    //���I�R���g���[���̏�����
    iPnl_InsNoCnt = 0;
    iPnl_InsNameCnt = 0;
    iPnl_InsKikiNameCnt = 0;
    iPnl_InsSubBaseCnt = 0;
    //���I�R���g���[���̏�����
    iPnl_SOZAI_InsNoCnt = 0;
    iPnl_SOZAI_InsNameCnt = 0;
    iPnl_SOZAI_InsKikiNameCnt = 0;
    iPnl_SOZAI_InsSubBaseCnt = 0;
    //���̑������l
    bCursolMove = false;
    PnlArrow->Caption ="��";
    bEnterMove = false;
    bKASOU_MOVE = false;
    bHANTEI_DISP = false;
    iOrCnt = 0;
    iPnl_InsKikiNameCnt = 0;
    iSokuSuu=0;
    iRecordCount = 0;
    iKikiCount = 0;
    iRIREKI_KOMKCNT = 0;
    iPnl_InsKikiNameCnt=0;
    iKikiCnt = 0;
    iContCnt = 0;
    iSOKU_MEMO_CNT = 0;
    iRIRE_MEMO_CNT = 0;
    bCellWrite = false;
    // StringList�̏�����	A.Tamura
    sRIREKI_LOT = new TStringList;
    //�O���t�C���t�H���[�V�����̏�����
    // �������̊J��
    memset(&pInfoGlaph,(int)NULL,sizeof(pInfoGlaph));
    bINPUTLOT_OK = false;					//���̓��b�gOK�t���O_
    bQUIT_FLG = false;
    bSOZAI_NASI = true;
    bNowLotF7 = false;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnShow�C�x���g	�F�t�H�[�����V���E�ɂȂ����Ƃ��ɔ������܂��B
//
//  �@�\����
//    ���C����ʂ̍ŏ��̃t�H�[�J�X���Z�b�g���܂�
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
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
    // �ŏ��̃t�H�[�J�X�Z�b�g
    Cmb_DTKSHIN->SetFocus();

}
//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�P�F�ꗗ�����v�{�^�������������̏���
//
//  �@�\����
//    �ꗗ������ʁiForm2�j��\�����܂�
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
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnF01Click(TObject *Sender)
{
    if( !BtnF01->Enabled ) return;
    if( !BtnF01->Tag ){
        ////////////////////
        // �ꗗ����
        Form2->ShowModal();
    }
    else{
        ////////////////////
        // �S���\���^��\��
        if( Panel22->Height   > 0 &&
            Panel173->Height  > 0 &&
            Panel14->Width    > 0 &&
            Pnl_skInfo->Width > 0 ){
            // �S�ĕ\�����ꂽ��Ԃ̎��A�S�Ĕ�\��
	        Panel22->Height   = 0;
	        Panel173->Height  = 0;
        	Panel14->Width    = 0;
        	Pnl_skInfo->Width = 0;
		} else{
            // �����ꂩ���\�����ꂽ��Ԃ̎��A�S�ĕ\��
            // �܂��́A�S�Ĕ�\���̏�Ԃ̎��A�S�ĕ\��
	        Panel22->Height   = Panel22->Tag;
	        Panel173->Height  = Panel173->Tag;
        	Panel14->Width    = Panel14->Tag;
        	Pnl_skInfo->Width = Pnl_skInfo->Tag;
		}
    }
}
//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�Q�F�O���v�{�^�������������̏���
//
//  �@�\����
//    CtrlOFF�F�A�N�e�B�u�Z���̈ʒu����O�Ɉړ����܂�
//    CtrlON �F�f�ޒl�\���^��\���؂�ւ�
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
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnF02Click(TObject *Sender)
{
    if( !BtnF02->Enabled ) return;
    if( !BtnF02->Tag ){

        //�O���ւ̈ړ�
        SGr_vSOKU_SYUKA->EditorMode = false;
		//GridSetPointMove(Sender, VK_F2);
        //Sender��VK_F2����EditBox���J���Ă��܂��ׁA�v���O��������VK_F13�Ƃ��Ĉ����Ă��܂�
		GridSetPointMove(Sender, VK_F13);
    }
    else{
        ////////////////////
        // �f�ޒl�\���^��\��
        if( Panel22->Height <= 0 )
	        Panel22->Height = Panel22->Tag;
		else
	        Panel22->Height = 0;

    }
}
//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�R�F�����v�{�^�������������̏���
//
//  �@�\����
//    CtrlOFF�F�A�N�e�B�u�Z���̈ʒu�����Ɉړ����܂�
//    CtrlON �F����l�\���^��\���؂�ւ�
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
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnF03Click(TObject *Sender)
{
    if( !BtnF03->Enabled ) return;
    if( !BtnF03->Tag ){
        ////////////////////
        // ����
		GridSetPointMove(Sender, VK_F3);


    }
    else{
        ////////////////////
        // ����l�\���^��\��
        if( Panel14->Width <= 0 )
        	Panel14->Width = Panel14->Tag;
		else
        	Panel14->Width = 0;
    }
}
//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�S�F�J�[�\�������v�{�^�������������̏���
//
//  �@�\����
//    CtrlOFF�F�J�[�\���������^���̐؂�ւ�
//    CtrlON �F�O���t�\���^��\���؂�ւ�
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
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnF04Click(TObject *Sender)
{
    if( !BtnF04->Enabled ) return;
    if( !BtnF04->Tag ){
        ////////////////////
        // �J�[�\������
        if(bCursolMove)
        {
            bCursolMove = false;
			PnlArrow->Caption ="��";
        }
        else
        {
            bCursolMove = true;
			PnlArrow->Caption ="��";
        }
    }
    else{
        ////////////////////
        // �O���t�\���^��\��
        if( Pnl_skInfo->Width <= 0 )
        	Pnl_skInfo->Width = Pnl_skInfo->Tag;
        else
        	Pnl_skInfo->Width = 0;
    }
}
//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�T�F�b�g�ؑցv�{�^�������������̏���
//
//  �@�\����
//    CtrlOFF�F�b�g�؂�ւ�
//    CtrlON �F���l���\���^��\���؂�ւ�
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
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnF05Click(TObject *Sender)
{
    unsigned short shtHoge=17;
    if( !BtnF05->Enabled ) return;
    if( !BtnF05->Tag ){
        ////////////////////
        // Ch�ؑ�
        //�ʃX���b�h�œ��삵�Ă���ʐM���W���[���Ƀ|�[�g�ԍ����w�����܂�(�O�`�R�j
		iPORT_NO ++;
		if( iPORT_NO> 4 ) iPORT_NO = 0;

    }
    else{
        ////////////////////
        // ���l���\���^��\��
        if( Panel173->Height <= 0 )
	        Panel173->Height = Panel173->Tag;
		else
	        Panel173->Height = 0;

    }
    TShiftState State;
    AllKeyUp(Sender,shtHoge,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�U�F�g�s�Ǎ��^���ڕҏW�v�{�^�������������̏���
//
//  �@�\����
//    CtrlOFF�F�n���f�B�[�^�[�~�i���ǂݍ���
//    CtrlON �F���ڕҏW��ʁiForm3�j��\�����܂�
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
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnF06Click(TObject *Sender)
{
    int rtn;
    int iCnt;
    int i;
    int j;
    int iCol;
    bool bHan;
    unsigned short shtHoge=17;
    vector<AnsiString> sBufHinban;
    vector<AnsiString> sBufLot;
    AnsiString sBuf;
    AnsiString sLot;
    TMsgDlgButtons MsgButton;

    if( !BtnF06->Enabled ) return;
    if( !BtnF06->Tag ){
        ////////////////////
        // �g�s�Ǎ�
        // k.k start
        // ������
        Cmb_DTKSHIN->Clear();
        sHT_LOT->Clear();
        sShiji_Data->Clear();
        // �w���f�[�^UPLOAD
        rtn = DataUpLoad();
        if (rtn < 0) {
            MessageDlg("�w���f�[�^�̎擾�Ɏ��s���܂����B", mtError, TMsgDlgButtons() << mbOK, 0);
            return;
        }
        iCnt = sShiji_Data->Count;
        // �i�ԁALOT�ɕ��� ansistrings
        for (i = 0; i < iCnt; i++) {
            // �i�Ԃ�LOT�ɕ���
            sBufLot.push_back(Trim(sShiji_Data->Strings[i].SubString(27,6)));  		// LOT
            sBufHinban.push_back(Trim(sShiji_Data->Strings[i].SubString(7,20)));    // �i��
        }
        // �\�[�g
        for (i = 0; i < iCnt-1;i++) {
            for (j = i + 1; j < iCnt;j++) {
                // j�v�f�̒l���������ꍇ
                if (sBufHinban[i] > sBufHinban[j]) {
                        // �i��
                        sBuf = sBufHinban[i];           // �o�b�t�@�ɕۑ�
                        sBufHinban[i] = sBufHinban[j];  // j�v�f��i�v�f�ɒu��
                        sBufHinban[j] = sBuf;           // j�v�f��i�v�f�ɒu��
                        // LOT
                        sBuf = sBufLot[i];              // �o�b�t�@�ɕۑ�
                        sBufLot[i] = sBufLot[j];        // j�v�f��i�v�f�ɒu��
                        sBufLot[j] = sBuf;              // j�v�f��i�v�f�ɒu��
                }
                // ���l�̏ꍇ
                if (sBufHinban[i] == sBufHinban[j]) {
                    // ���b�g�̃\�[�g
                    // ���b�g�̃T�C�Y���f
                    if (sBufLot[i].Length() == 5) {
                        // �T�o�C�g�̏ꍇ�A���S���Ń\�[�g
                        if (sBufLot[i].SubString(2, 4) > sBufLot[j].SubString(2, 4)) {
                            // LOT
                            sBuf = sBufLot[i];          // �o�b�t�@�ɕۑ�
                            sBufLot[i] = sBufLot[j];    // j�v�f��i�v�f�ɒu��
                            sBufLot[j] = sBuf;          // j�v�f��i�v�f�ɒu��
                        }
                    } else {
                        // �T�o�C�g�ȊO�̏ꍇ�A�S���Ń\�[�g
                        if (sBufLot[i] > sBufLot[j]) {
                            // LOT
                            sBuf = sBufLot[i];          // �o�b�t�@�ɕۑ�
                            sBufLot[i] = sBufLot[j];    // j�v�f��i�v�f�ɒu��
                            sBufLot[j] = sBuf;          // j�v�f��i�v�f�ɒu��
                        }
                    }
                }
            }
        }

        // �i�ԁALOT���X�g�쐬
        for (i = 0; i < iCnt; i++) {
            if ( i != 0) {
                // �P�O�̕i�ԂƓ����ꍇ�ALOT���J���}��؂�Ōq����
                if (sBufHinban[i] == sBuf) {
                    sLot += "," + sBufLot[i];
                // �i�Ԃ��ύX���ꂽ��A�R���{�{�b�N�X�A���X�g�{�b�N�X�Ɋi�[
                } else {
                    sHT_LOT->Add(sLot);
                    Cmb_DTKSHIN->Items->Add(sBuf);
                    sBuf = sBufHinban[i];
                    sLot = sBufLot[i];
                }
            } else {
                sBuf = sBufHinban[i];
                sLot = sBufLot[i];
            }
        }
        // �Ō�̔z�񕪂�ǉ�
        sHT_LOT->Add(sLot);
        Cmb_DTKSHIN->Items->Add(sBuf);
        // "1/x"��\��
        iCnt = sHT_LOT->Count;
        sBuf = "1/" + AnsiString(iCnt);
        Lab_Num->Caption = sBuf;
        // �擪��\��
        Cmb_DTKSHIN->Text = Cmb_DTKSHIN->Items->Strings[0];
        Edt_LOTNO->Text = sHT_LOT->Strings[0];
		//2003.05.09 E.Takase Add��
		sNowDTKSHIN = Cmb_DTKSHIN->Text;
		sNowLOTNO = Edt_LOTNO->Text;
		//2003.05.09 E.Takase Add��

    }
    else{
        ////////////////////
        // ���ڕҏW
	    TShiftState State;

        //�L���ȃ��b�g���͂����邩�𔻒f���܂�
	    if( !bINPUTLOT_OK )
		{
       		sBuf  = "�L���ȃ��b�g�����͂���Ă��Ȃ��׍��ڕҏW�͏o���܂���B";
			MsgButton << mbOK;
        	MessageDlg( sBuf, mtWarning	, MsgButton, 0);
    		//AllKeyUp( Sender,17,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
    		AllKeyUp( Sender ,shtHoge,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
        	return;
    	}
        // ���݃J�[�\���̗L��i�ԁE���b�g�̎w��
		//2003.05.09 E.Takase Add��
        Form3->sNOW_DTKSHIN	= sNowDTKSHIN;
		//2003.05.09 E.Takase Add��
		//2003.05.09 E.Takase Add �R�����g��
        //Form3->sNOW_DTKSHIN	= Cmb_DTKSHIN->Text;
		//2003.05.09 E.Takase Add �R�����g��
        //�ΏۂƂȂ郍�b�g���������Ă܂�
		switch(pInfoGlaph.GRID_NO)
		{
		case 1:
        	Form3->sNOW_LOTNO	= SGr_tSOKU->Cells[SGr_vSOKU_SYUKA->Col][0];
			break;
		case 2:
        	Form3->sNOW_LOTNO	= SGr_tRIRE->Cells[SGr_vRIRE_SYUKA->Col][0];
			break;
		case 3:
        	Form3->sNOW_LOTNO	= SGr_tSOKU->Cells[SGr_vSOKU_SOZAI->Col][0];
			break;
		case 4:
        	Form3->sNOW_LOTNO	= SGr_tRIRE->Cells[SGr_vRIRE_SOZAI->Col][0];
			break;
		}

        if( Form3->sNOW_LOTNO.Trim() == "" ){
			MessageDlg( "�Ώۃ��b�gNO��I�����ĉ������B", mtInformation, TMsgDlgButtons() << mbOK , 0);
    		//AllKeyUp(Sender,17,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
    		AllKeyUp( Sender  ,shtHoge,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
            return;
        }

    	// �m�F���b�Z�[�W
// �y���z�f�[�^���ҏW����Ă���ꍇ�����A�m�F���b�Z�[�W�̕\�����s�Ȃ�
        if( MessageDlg( "���ڕҏW���s�Ȃ��ɂ́A���݂̑���f�[�^��ۑ�����K�v������܂��B\n�ۑ����s�������𑱍s���܂��B��낵���ł����H",
            mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo ){
            //AllKeyUp(Sender,17,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
            AllKeyUp(Sender ,shtHoge,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
            return;
        }
/*
        //�A�b�v�f�[�g�t���O������ON���܂�
		if( hSOKU_KSD01_DATA)
		{
			for(iCol = 0; iCol<SGr_tSOKU->ColCount;iCol++)
			{
				pSOKU_KSD01_DATA[iCol].UPD_FLG = true;
				pSOKU_KSD01_DATA[iCol].SAVE_FLG = false;
			}
    	}

        //�A�b�v�f�[�g�t���O������ON���܂�
		if( hRIRE_KSD01_DATA && Form1->iRIRE_CNT != 0)
		{
			for(iCol = 0; iCol<SGr_tRIRE->ColCount;iCol++)
			{
				pRIRE_KSD01_DATA[iCol].UPD_FLG = true;
				pRIRE_KSD01_DATA[iCol].SAVE_FLG = false;
			}
		}
*/
        //�ΏۂƂȂ郍�b�g�̃A�b�v�f�[�g�t���O������ON���܂�
		switch(pInfoGlaph.GRID_NO)
		{
		case 1:
        	//Form3->sNOW_LOTNO	= SGr_tSOKU->Cells[SGr_vSOKU_SYUKA->Col][0];
            iCol = SGr_vSOKU_SYUKA->Col;
            pSOKU_KSD01_DATA[iCol].UPD_FLG = true;
            pSOKU_KSD01_DATA[iCol].SAVE_FLG = false;
			break;
		case 2:
        	//Form3->sNOW_LOTNO	= SGr_tRIRE->Cells[SGr_vRIRE_SYUKA->Col][0];
        	iCol = SGr_vRIRE_SYUKA->Col;
            pRIRE_KSD01_DATA[iCol].UPD_FLG = true;
            pRIRE_KSD01_DATA[iCol].SAVE_FLG = false;
			break;
		case 3:
        	//Form3->sNOW_LOTNO	= SGr_tSOKU->Cells[SGr_vSOKU_SOZAI->Col][0];
            iCol = SGr_vSOKU_SOZAI->Col;
            pSOKU_KSD01_DATA[iCol].UPD_FLG = true;
            pSOKU_KSD01_DATA[iCol].SAVE_FLG = false;
			break;
		case 4:
        	//Form3->sNOW_LOTNO	= SGr_tRIRE->Cells[SGr_vRIRE_SOZAI->Col][0];
        	iCol = SGr_vRIRE_SOZAI->Col;
            pRIRE_KSD01_DATA[iCol].UPD_FLG = true;
            pRIRE_KSD01_DATA[iCol].SAVE_FLG = false;
			break;
		}

        // 2003/10/30 A.Tamura �Ō�Ƀt�H�[�J�X�̗L�����Z�����ҏW���[�h�̎��A
        // �u�l�̕ۑ��v�Ɓu���菈���v���m���ɍs�Ȃ����߁ADrawCell���Ăяo���܂��B
		TGridDrawState DrawState;
    	AllGRID_DrawCell( SGr_vSOKU_SYUKA,
                             SGr_vSOKU_SYUKA->Col,
                             SGr_vSOKU_SYUKA->Row,
                             SGr_vSOKU_SYUKA->CellRect(SGr_vSOKU_SYUKA->Col, SGr_vSOKU_SYUKA->Row),
                             DrawState);
    	AllGRID_DrawCell( SGr_vRIRE_SYUKA,
                             SGr_vRIRE_SYUKA->Col,
                             SGr_vRIRE_SYUKA->Row,
                             SGr_vRIRE_SYUKA->CellRect(SGr_vRIRE_SYUKA->Col, SGr_vRIRE_SYUKA->Row),
                             DrawState);
    	AllGRID_DrawCell( SGr_vSOKU_SOZAI,
                             SGr_vSOKU_SOZAI->Col,
                             SGr_vSOKU_SOZAI->Row,
                             SGr_vSOKU_SOZAI->CellRect(SGr_vSOKU_SOZAI->Col, SGr_vSOKU_SOZAI->Row),
                             DrawState);
    	AllGRID_DrawCell( SGr_vRIRE_SOZAI,
                             SGr_vRIRE_SOZAI->Col,
                             SGr_vRIRE_SOZAI->Row,
                             SGr_vRIRE_SOZAI->CellRect(SGr_vRIRE_SOZAI->Col, SGr_vRIRE_SOZAI->Row),
                             DrawState);

        ALL_INSPECT();              //�S���b�g�̔�����s���܂�
        ADD_SPACE();                //KSD02�ɃX�y�[�X�s��ۑ����܂�
        bHan = Set_DB_SOKU();       //�o�ב���f�[�^��ۑ����܂�
        bHan = Set_DB_RIRE();       //�o�ח����f�[�^��ۑ����܂�
        bHan = Set_DB_SOKU_SOZAI(); //�f�ޑ���f�[�^��ۑ����܂�
        bHan = Set_DB_RIRE_SOZAI(); //�f�ޗ����f�[�^��ۑ����܂�

        //�ۑ����I�������̂Łu�A�b�v�f�[�g�t���O�ƕۑ��t���O�����������܂�
		if( hSOKU_KSD01_DATA)
		{
			for(iCol = 0; iCol<SGr_tSOKU->ColCount;iCol++)
			{
				pSOKU_KSD01_DATA[iCol].UPD_FLG = false;
				pSOKU_KSD01_DATA[iCol].SAVE_FLG = true;
			}
    	}

		if( hRIRE_KSD01_DATA && Form1->iRIRE_CNT != 0)
		{
			for(iCol = 0; iCol<SGr_tRIRE->ColCount;iCol++)
			{
				pRIRE_KSD01_DATA[iCol].UPD_FLG = false;
				pRIRE_KSD01_DATA[iCol].SAVE_FLG = true;
			}
		}

    	// ���ڕҏW��ʂ�\������O�̊m�F��ʂ�\�����܂�
        // ���ڕҏW��ʂ������\�����鍀�ڃf�[�^�̕\���������肵�܂�
        Form10->ShowModal();

        if( Form3->iFROM_DATA > 0 ){

        	// ���ڕҏW��ʂ̕\��
        	Form3->ShowModal();

//        	AllKeyUp(Sender,17,State);					// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B

        	// ���ڕҏW����Ă���ꍇ�A�ĕ\���������s�Ȃ��܂�
        	if( Form3->bDispRefresh ){

                // 2004/08/27 A.Tamura ���ڕҏW��̌����������Ɂu�ۑ����܂����H�v�ƕ����Ă���̂�
                //                     �ۑ��Ώۂ̃��b�g�����o�b�t�@�Ɏ�荞��ł���A�ۑ��t���O
                //                     �����������܂��B
                //                     ���̌�A�u�����v���u�o�b�t�@��߂��v���u�ۑ������v���s�Ȃ��B
				TStrings *sUPD_FLG_SOKU;
				TStrings *sUPD_FLG_RIRE;

                sUPD_FLG_SOKU = new TStringList;
                sUPD_FLG_RIRE = new TStringList;

        		// �A�b�v�f�[�g�t���O�ƕۑ��t���O���o�b�t�@�֊i�[�Ə��������܂�
				if( hSOKU_KSD01_DATA)
				{
					for(iCol = 0; iCol<SGr_tSOKU->ColCount;iCol++)
					{
                        // �o�b�t�@�֊i�[
                        if( pSOKU_KSD01_DATA[iCol].UPD_FLG ){
                        	sUPD_FLG_SOKU->Add("1");
                        } else {
                        	sUPD_FLG_SOKU->Add("0");
                        }
						pSOKU_KSD01_DATA[iCol].UPD_FLG = false;
						pSOKU_KSD01_DATA[iCol].SAVE_FLG = true;
					}
    			}

				if( hRIRE_KSD01_DATA && Form1->iRIRE_CNT != 0)
				{
					for(iCol = 0; iCol<SGr_tRIRE->ColCount;iCol++)
					{
                        // �o�b�t�@�֊i�[
                        if( pRIRE_KSD01_DATA[iCol].UPD_FLG ){
                        	sUPD_FLG_RIRE->Add("1");
                        } else {
                        	sUPD_FLG_RIRE->Add("0");
                        }
						pRIRE_KSD01_DATA[iCol].UPD_FLG = false;
						pRIRE_KSD01_DATA[iCol].SAVE_FLG = true;
					}
				}

				// ���̑������l��ݒ�
			    bCursolMove = false;
                PnlArrow->Caption ="��";
			    bEnterMove = false;
				bKASOU_MOVE = false;
				bHANTEI_DISP = false;

                // ��������
     			// AllKeyUp(Sender,17,State);		// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
     			AllKeyUp(Sender ,shtHoge,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
				BtnF07Click(BtnF07);

        		// �o�b�t�@�֊i�[�����A�b�v�f�[�g�t���O�����ɖ߂��܂��B
				if( hSOKU_KSD01_DATA)
				{
					for(iCol = 0; iCol<SGr_tSOKU->ColCount;iCol++)
					{
                        if( sUPD_FLG_SOKU->Strings[iCol] == "1" ){
							pSOKU_KSD01_DATA[iCol].UPD_FLG = true;
							pSOKU_KSD01_DATA[iCol].SAVE_FLG = false;
                        } else {
							pSOKU_KSD01_DATA[iCol].UPD_FLG = false;
							pSOKU_KSD01_DATA[iCol].SAVE_FLG = true;
                        }
					}
    			}

				if( hRIRE_KSD01_DATA && Form1->iRIRE_CNT != 0)
				{
					for(iCol = 0; iCol<SGr_tRIRE->ColCount;iCol++)
					{
                        if( sUPD_FLG_RIRE->Strings[iCol] == "1" ){
							pRIRE_KSD01_DATA[iCol].UPD_FLG = true;
							pRIRE_KSD01_DATA[iCol].SAVE_FLG = false;
                        } else {
							pRIRE_KSD01_DATA[iCol].UPD_FLG = false;
							pRIRE_KSD01_DATA[iCol].SAVE_FLG = true;
                        }
					}
				}

				delete sUPD_FLG_SOKU;
				delete sUPD_FLG_RIRE;

                // 2004/08/27 A.Tamura �s�No12,42�ɑΉ����邽�߁u���ڕҏW�v��ʏI�����
                //                     �u����v���قȂ�ꍇ����������̂őΏۂ̃��b�g��ۑ����܂��B
                //                     �ۑ��Ώۂ̃��b�g�ݒ�́AForm3�ōs�Ȃ��Ă��܂��B

        		// 2003/10/30 A.Tamura �Ō�Ƀt�H�[�J�X�̗L�����Z�����ҏW���[�h�̎��A
        		// �u�l�̕ۑ��v�Ɓu���菈���v���m���ɍs�Ȃ����߁ADrawCell���Ăяo���܂��B
    			AllGRID_DrawCell( SGr_vSOKU_SYUKA,
		                             SGr_vSOKU_SYUKA->Col,
		                             SGr_vSOKU_SYUKA->Row,
		                             SGr_vSOKU_SYUKA->CellRect(SGr_vSOKU_SYUKA->Col, SGr_vSOKU_SYUKA->Row),
		                             DrawState);
		    	AllGRID_DrawCell( SGr_vRIRE_SYUKA,
		                             SGr_vRIRE_SYUKA->Col,
		                             SGr_vRIRE_SYUKA->Row,
		                             SGr_vRIRE_SYUKA->CellRect(SGr_vRIRE_SYUKA->Col, SGr_vRIRE_SYUKA->Row),
		                             DrawState);
		    	AllGRID_DrawCell( SGr_vSOKU_SOZAI,
		                             SGr_vSOKU_SOZAI->Col,
		                             SGr_vSOKU_SOZAI->Row,
		                             SGr_vSOKU_SOZAI->CellRect(SGr_vSOKU_SOZAI->Col, SGr_vSOKU_SOZAI->Row),
		                             DrawState);
		    	AllGRID_DrawCell( SGr_vRIRE_SOZAI,
		                             SGr_vRIRE_SOZAI->Col,
		                             SGr_vRIRE_SOZAI->Row,
		                             SGr_vRIRE_SOZAI->CellRect(SGr_vRIRE_SOZAI->Col, SGr_vRIRE_SOZAI->Row),
		                             DrawState);

		        ALL_INSPECT();              //�S���b�g�̔�����s���܂�
		        ADD_SPACE();                //KSD02�ɃX�y�[�X�s��ۑ����܂�
		        bHan = Set_DB_SOKU();       //�o�ב���f�[�^��ۑ����܂�
		        bHan = Set_DB_RIRE();       //�o�ח����f�[�^��ۑ����܂�
		        bHan = Set_DB_SOKU_SOZAI(); //�f�ޑ���f�[�^��ۑ����܂�
		        bHan = Set_DB_RIRE_SOZAI(); //�f�ޗ����f�[�^��ۑ����܂�

        		// �ۑ����I�������̂ŃA�b�v�f�[�g�t���O�ƕۑ��t���O�����������܂�
				if( hSOKU_KSD01_DATA)
				{
					for(iCol = 0; iCol<SGr_tSOKU->ColCount;iCol++)
					{
						pSOKU_KSD01_DATA[iCol].UPD_FLG = false;
						pSOKU_KSD01_DATA[iCol].SAVE_FLG = true;
					}
    			}

				if( hRIRE_KSD01_DATA && Form1->iRIRE_CNT != 0)
				{
					for(iCol = 0; iCol<SGr_tRIRE->ColCount;iCol++)
					{
						pRIRE_KSD01_DATA[iCol].UPD_FLG = false;
						pRIRE_KSD01_DATA[iCol].SAVE_FLG = true;
					}
				}
        	}
        }

    }
    TShiftState State;
    AllKeyUp(Sender,shtHoge,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�V�F�����v�{�^�������������̏���
//
//  �@�\����
//    CtrlOFF�F���������s���܂�
//    CtrlON �F���b�g���蓖�ĉ�ʁiForm8�j��\�����܂�
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
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnF07Click(TObject *Sender)
{

    TRect r;
    AnsiString sBuf;
    MSG msg;
    TMsgDlgButtons MsgButton;
    int i1,iCol,iRow;
    TShiftState State;
    unsigned short shtHoge=17;

    if( !BtnF07->Enabled ) return;
    if( !BtnF07->Tag ){
        ////////////////////
        // ����
        //�����O����
        //�f�[�^�̍X�V�������������m�F���܂�
        if( UPDATE_CHECK())
        {
            //�f�[�^�̍X�V���������̂ōX�V���b�g���S�f�[�^�𑪒肵�������m�F���܂�
            if( !ALL_INSPECT())
            {
                sBuf  = "������̍��ڂ�����܂��B�ۑ����Č������܂����H";
                sBuf += "\n[�́@��] �����荀�ڂ���̂܂܁A�ۑ����Č������܂��B";
                sBuf += "\n[������] ���e��j�����Č������܂��B";
                sBuf += "\n[�L�����Z��] ���������̎������B";
                switch( MessageDlg( sBuf, mtWarning, mbYesNoCancel, 0) )
                {
                    // �uYes�v      �ۑ�
                    case mrYes:
                        bQUIT_FLG = true;
	                BtnF11Click(Sender);
                        break;
                    // �uNo�v       �ύX��j��
                    case mrNo:
                        break;
                    // �uCancel�v   �L�����Z��
                    case mrCancel:
                        return;
                }
            }
            else
	    {
    	        sBuf  = "�f�[�^���ύX����Ă��܂��B�ύX���e��ۑ����܂����H";
        	sBuf += "\n[�́@��] �ύX���e��ۑ����đ��s���܂��B";
            	sBuf += "\n[������] �ύX���e��j�����đ��s���܂��B";
		sBuf += "\n[�L�����Z��] ���������̎������B";
                switch( MessageDlg( sBuf, mtConfirmation, mbYesNoCancel, 0) )
                {
                // �uYes�v      �ۑ�
                case mrYes:
                    bQUIT_FLG = true;
    	             BtnF11Click(Sender);
                     break;
                 // �uNo�v       �ύX��j��
                case mrNo:
                     break;
                 // �uCancel�v   �L�����Z��
                case mrCancel:
                     return;
                }
            }
        }

        // 2003/06/02 A.Tamura
	PnlArrow->Caption ="��";

        bQUIT_FLG = false;;
        Graph_Format();
        bSOZAI_NASI = true;

	// 2003/06/02 A.Tamura
        Glaph_Init();

	//2003.05.14 A.Tamura Add��
	if( Trim(Cmb_DTKSHIN->Text).Length() == 0 ){
	    MessageDlg("��\���Ӑ�i�Ԃ��w�肳��Ă��܂���B", mtWarning,
	    TMsgDlgButtons() << mbOK , 0);
            return;
        }

	if( Trim(Edt_LOTNO->Text).Length()   == 0 ){
	    MessageDlg("���b�gNO���w�肳��Ă��܂���B", mtWarning,
	    TMsgDlgButtons() << mbOK , 0);
            return;
        }
	//2003.05.14 A.Tamura Add��

	//2003.05.09 E.Takase Add��
        //�O���[�o���ϐ��Ɍ����������Z�b�g
	sNowDTKSHIN	 = Cmb_DTKSHIN->Text;
	sNowLOTNO	 = Edt_LOTNO->Text;
	bNowSEIKANDATA	 = CHkSEIKANDATA->Checked;
	bNowRIRE	 = Chk_RIRE->Checked;
	iNowRIRE_NUM	 = Edt_RIRE_NUM->Text.ToIntDef(10);
	//2003.05.09 E.Takase Add��

        // �������t���OON
        bNowF7 = true;

        for(i1 = 0;i1<1000;i1++)
        {
            bBUNKATU_RIRE[i1] = false;
            bBUNKATU_SOKU[i1] = false;
        }

	// 2003/06/02 A.Tamura
        Glaph_Init();
        Graph_Format();

        //���i�K�i�}�X�^�[�����݂��邩�H
	bINPUTLOT_OK = Get_KSM01();
	if(!bINPUTLOT_OK){
	    // �������t���OOFF
	    bNowF7 = false;
	    MessageDlg("�w�肵���i�Ԃ͐��i�K�i�}�X�^�[�ɓo�^����Ă��܂���B", mtWarning,
	    TMsgDlgButtons() << mbOK , 0);
	    return;
	}
	else
	{
            //�O���b�h�̈ʒu�f�t�H���g�l�Z�b�g�i���̏�����ӂ�ƃO���b�h�C���f�b�N�X�G���[�Ɍ�������j
            SGr_vSOKU_SYUKA->Row = 0;
            SGr_vSOKU_SYUKA->Col = 0;
            SGr_vRIRE_SYUKA->Row = 0;
            SGr_vRIRE_SYUKA->Col = 0;
            SGr_vSOKU_SOZAI->Row = 0;
            SGr_vSOKU_SOZAI->Col = 0;
            SGr_vRIRE_SOZAI->Row = 0;
            SGr_vRIRE_SOZAI->Col = 0;

            // �E�p�l���֏ڍ׏��̕\��
            Pnl_skInfo_vDTKS  ->Caption = " " + AnsiString(pKSM01_DATA.DTKSNAM);
	    Pnl_skInfo_vHINBAN->Caption = " " + AnsiString(pKSM01_DATA.HINBAN);
	    Pnl_skInfo_vHINSYU->Caption = " " + AnsiString(pKSM01_DATA.ZISNAM);
	    Pnl_skInfo_vHINMEI->Caption = " " + AnsiString(pKSM01_DATA.HINMEI);
	}
	OldMIDASI->Visible = false;
	NewMIDASI->Visible = false;
        OldMIDASI->Parent = SBx_Left_SYUKA;
        NewMIDASI->Parent = SBx_Left_SYUKA;


        //�Z���C���t�H���[�V�������
	// �������̊J��
	if( hCELLINFO_SOKU_SYUKA ){
    	    GlobalUnlock( hCELLINFO_SOKU_SYUKA );
            GlobalFree( hCELLINFO_SOKU_SYUKA );
	}
        hCELLINFO_SOKU_SYUKA = NULL;
	// �������̊J��
	if( hCELLINFO_RIRE_SYUKA ){
            GlobalUnlock( hCELLINFO_RIRE_SYUKA );
	    GlobalFree( hCELLINFO_RIRE_SYUKA );
    	}
        hCELLINFO_RIRE_SYUKA = NULL;
	// �������̊J��
	if( hCELLINFO_SOKU_SOZAI ){
            GlobalUnlock( hCELLINFO_SOKU_SOZAI );
	    GlobalFree( hCELLINFO_SOKU_SOZAI );
    	}
        hCELLINFO_SOKU_SOZAI = NULL;
	// �������̊J��
	if( hCELLINFO_RIRE_SOZAI ){
            GlobalUnlock( hCELLINFO_RIRE_SOZAI );
	    GlobalFree( hCELLINFO_RIRE_SOZAI );
    	}
        hCELLINFO_RIRE_SOZAI = NULL;
	// �������̊J��
    	if( hSOKU_KSD01_DATA ){
    	    GlobalUnlock( hSOKU_KSD01_DATA );
	    GlobalFree( hSOKU_KSD01_DATA );
    	}
	hSOKU_KSD01_DATA = NULL;
        bNowLotF7 == false;


        //���̑������l
        bCursolMove = false;
        bEnterMove = false;
	bKASOU_MOVE = false;
	bHANTEI_DISP = false;
        bCellWrite = false;


        memset(&pOldInfoGlaph,(int)NULL,sizeof(pOldInfoGlaph));
	//�O���b�h�N���A
	for(iCol = 0; iCol<SGr_vSOKU_SYUKA->ColCount ; iCol++)
	{
	    for(iRow = 0; iRow<SGr_vSOKU_SYUKA->RowCount;iRow++)
	    {
	    	SGr_vSOKU_SYUKA->Cells[iCol][iRow] = "";
	    }
	}
	for(iCol = 0; iCol<SGr_vRIRE_SYUKA->ColCount ; iCol++)
	{
	    for(iRow = 0; iRow<SGr_vRIRE_SYUKA->RowCount;iRow++)
	    {
	    	SGr_vRIRE_SYUKA->Cells[iCol][iRow] = "";
	    }
	}
	for(iCol = 0; iCol<SGr_vSOKU_SOZAI->ColCount ; iCol++)
	{
	    for(iRow = 0; iRow<SGr_vSOKU_SOZAI->RowCount;iRow++)
	    {
	    	SGr_vSOKU_SOZAI->Cells[iCol][iRow] = "";
	    }
	}
	for(iCol = 0; iCol<SGr_vRIRE_SOZAI->ColCount ; iCol++)
	{
	    for(iRow = 0; iRow<SGr_vRIRE_SOZAI->RowCount;iRow++)
	    {
	    	SGr_vRIRE_SOZAI->Cells[iCol][iRow] = "";
	    }
	}
	for(iCol = 0;iCol < SGr_tSOKU->ColCount;iCol++)
	{
	    SGr_tSOKU->Cells[iCol][0] = "";
	    SGr_tSOKU_SOZAI->Cells[iCol][0] = "";
	    SGr_tSOKU_SYUKA->Cells[iCol][0] = "";
	}
	for(iCol = 0;iCol < SGr_tRIRE->ColCount;iCol++)
	{
	    SGr_tRIRE->Cells[iCol][0] = "";
	    SGr_tRIRE_SOZAI->Cells[iCol][0] = "";
	    SGr_tRIRE_SYUKA->Cells[iCol][0] = "";
	}

	// 2003/06/02 A.Tamura
        Glaph_Init();

        //�L�[�C�x���g�N���A
	while(PeekMessage(&msg,Form1->Handle,WM_KEYFIRST,WM_KEYLAST,PM_REMOVE));

        //���b�g�̎擾
        if( Set_Lot() )                                                 // onishi
        {
	    bINPUTLOT_OK = true;					//���̓��b�gOK�t���O_

    	    SGr_tRIRE->Refresh();
	    SGr_tSOKU->Refresh();

	    Get_KSM02();
            //�������b�g�̎擾
	    if(bNowRIRE == true)
            {
                Get_RIRELOT();
            }
            else
            {
                iRIRE_CNT = 0;                  //���𐔂�0�ł�
            }

            //�O���b�h�̏�����
	    SGr_vSOKU_SYUKA->RowCount = 1;
	    SGr_tSOKU_SYUKA->RowCount = 1;      //���t�\���O���b�h
	    SGr_vSOKU_SOZAI->RowCount = 1;
	    SGr_tSOKU_SOZAI->RowCount = 1;      //���t�\���O���b�h

            // �ʏ�̑����ʂɕύX
            SGr_vRIRE_SOZAI->Color = (TColor)0x00D2FFFF;
            SGr_vSOKU_SOZAI->Color = (TColor)0x00D2FFFF;
            SGr_vRIRE_SYUKA->Color = (TColor)0x00FFEEDD;
            SGr_vSOKU_SYUKA->Color = clWindow;
            SCREEN_SET();

            // �R���g���[���������I�ɕω�����ׁA�R�[�h�C�����K�v
            Mem_vRIRE_MEMOORG->Color = (TColor)0x00FFEEDD;
	    SBr1->Panels->Items[0]->Text = "�ʏ�̑����ʂł��B";
	    SBr1->Update();

            //����\������---------------------------------------------------------------------
            //���������R���g���[���̃������J��
            for(i1 = 0 ; i1 < iRIRE_MEMO_CNT ;i1++)
            {
            	delete Mem_vRIRE_MEMO[i1];
            }
            iRIRE_MEMO_CNT = 0;
	    SGr_vRIRE_SYUKA->ColCount = 1;
	    SGr_tRIRE_SYUKA->ColCount = 1;      //���t�\���O���b�h
	    SGr_vRIRE_SOZAI->ColCount = 1;
	    SGr_tRIRE_SOZAI->ColCount = 1;      //���t�\���O���b�h

            //�����O���b�h���̒���
	    if(bNowRIRE == true)
	    {
		SGr_tRIRE	->Visible   = true;
		SGr_vRIRE_SYUKA	->Visible   = true;
		SGr_tRIRE_SYUKA ->Visible   = true;     			//���t�\���O���b�h
		SGr_vRIRE_SOZAI	->Visible   = true;
		SGr_tRIRE_SOZAI ->Visible   = true;      			//���t�\���O���b�h
		SGr_vRIRE_SYUKA	->ColCount  = iRIRE_CNT;
		SGr_tRIRE_SYUKA ->ColCount  = iRIRE_CNT;			//���t�\���O���b�h
		SGr_vRIRE_SOZAI	->ColCount  = iRIRE_CNT;
		SGr_tRIRE_SOZAI ->ColCount  = iRIRE_CNT;			//���t�\���O���b�h
	    }
	    else
	    {
		SGr_tRIRE	->Visible   = False;
		SGr_vRIRE_SYUKA	->Visible   = False;
		SGr_tRIRE_SYUKA ->Visible   = False;				//���t�\���O���b�h
		SGr_vRIRE_SOZAI	->Visible   = False;
		SGr_tRIRE_SOZAI ->Visible   = False;				//���t�\���O���b�h
	    }
            //�O���t�C�j�V�����C�Y
	    //�O���t�C���t�H���[�V�����̏�����
	    // �������̊J��
            memset(&pInfoGlaph,(int)NULL,sizeof(pInfoGlaph));
            memset(&pOldInfoGlaph,(int)NULL,sizeof(pOldInfoGlaph));

            //�������[�`�����C������
	    Set_Ins_Disp();

            //�����\�`�F�b�N
            BUNKATU_CHECK();
        }
        else
        {
            //���I�R���g���[���̊J��
            DynamicCtrl_Free();
	    //�O���t�C���t�H���[�V�����̏�����
            //�O���t�̏�����
            Graph_Format();
            bINPUTLOT_OK = false;
            memset(&pInfoGlaph,(int)NULL,sizeof(pInfoGlaph));
	    bINPUTLOT_OK = false;					//���̓��b�gOK�t���O_
        }
    }
    else
    {
        //���b�g���蓖�ĉ��
        bool bTempLot;
        bTempLot = bLOT_LINK;
        Glaph_Init();

	if( !bINPUTLOT_OK )
	{
	    MsgButton << mbOK;
       	    sBuf  = "�L���ȃ��b�g�����͂���Ă��Ȃ��ׁA���b�g���蓖�Ă͏o���܂���B";
            MessageDlg( sBuf, mtWarning	, MsgButton, 0);
            //AllKeyUp(Sender,17,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
            AllKeyUp(Sender ,shtHoge,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
            return;
    	}
        if( bSOZAI_NASI )
        {
	    MsgButton << mbOK;
       	    sBuf  = "�f�ނ̎w��������f�[�^���Ȃ��ׁA���b�g���蓖�Ă͏o���܂���B";
            MessageDlg( sBuf, mtWarning	, MsgButton, 0);
            //AllKeyUp(Sender,17,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
            AllKeyUp(Sender ,shtHoge,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
            return;
        }
        if(bLOT_LINK == true)
        {
	    MsgButton << mbOK;
       	    sBuf  = "�f�ރf�[�^���S�ă��b�g�����N���s���Ă���̂ŁA���b�g���蓖�Ă͏o���܂���B";
            MessageDlg( sBuf, mtWarning	, MsgButton, 0);
            //AllKeyUp(Sender,17,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
            AllKeyUp(Sender ,shtHoge,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
            bLOT_LINK = bTempLot;
            return;
        }
        ////////////////////
        // ���b�g���蓖�ĉ�ʁ@�Ăяo��
	TShiftState State;
	OldMIDASI->Visible = false;
	NewMIDASI->Visible = false;
        OldMIDASI->Parent = SBx_Left_SYUKA;
        NewMIDASI->Parent = SBx_Left_SYUKA;
        memset(&pInfoGlaph,(int)NULL,sizeof(pInfoGlaph));
        memset(&pOldInfoGlaph,(int)NULL,sizeof(pOldInfoGlaph));

        // ���b�g���蓖��
        if(hCELLINFO_SOKU_SYUKA)
        {
            SGr_vSOKU_SYUKA->SetFocus();
            SGr_vSOKU_SYUKA->Col = 0;
            SGr_vSOKU_SYUKA->Row = 0;
        }
        Form8->ShowModal();

        // k.k 2003.05.17 ADD ----
	OldMIDASI->Visible = false;
	NewMIDASI->Visible = false;
        OldMIDASI->Parent = SBx_Left_SYUKA;
        NewMIDASI->Parent = SBx_Left_SYUKA;
        memset(&pInfoGlaph,(int)NULL,sizeof(pInfoGlaph));
        memset(&pOldInfoGlaph,(int)NULL,sizeof(pInfoGlaph));

        SOZAI_PROCESS();
        bLOTCHANGE = false;
        bNowLotF7 = false;
        // �����I���t���O
        Form1->bNowF7 = false;
        bLOT_LINK = bTempLot;
        //------------------------

        AllKeyUp(Sender ,shtHoge,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B

	//�O���t�C�j�V�����C�Y
        Glaph_Init();
        Graph_Format();
    }
}
//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�W�F�S���Ґؑցv�{�^�������������̏���
//
//  �@�\����
//    CtrlOFF:�S���Ґؑ։�ʁiForm9�j��\�����܂�
//    CtrlON :�����\��ʁiForm7�j��\�����܂�
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
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnF08Click(TObject *Sender)
{
	TShiftState State;
	TMsgDlgButtons MsgButton;
    AnsiString sBuf;
    unsigned short shtHoge=17;

	if( !BtnF08->Enabled ) return;
    if( !BtnF08->Tag ){
        ////////////////////
        // �S���Ґؑ�
        Form9->ShowModal();
        AllKeyUp(Sender,shtHoge,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
    }
    else{
	    if( !bINPUTLOT_OK )
		{
        	MsgButton << mbOK;
       		sBuf  = "�L���ȃ��b�g�����͂���Ă��Ȃ��ׁA�����\�͓��삵�܂���B";
        	MessageDlg( sBuf, mtWarning	, MsgButton , 0);
        	AllKeyUp(Sender,shtHoge,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
            return;
    	}
        if( iContCnt == 0)
		{
        	MsgButton << mbOK;
       		sBuf  = "�o�׍��ڂ��Ȃ��ׁA�����\�͓��삵�܂���B";
        	MessageDlg( sBuf, mtWarning	, MsgButton , 0);
        	AllKeyUp(Sender,shtHoge,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
            return;
    	}
        ////////////////////
        // �����[����
        Form7->ShowModal();
        AllKeyUp(Sender,shtHoge,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
        BUNKATU_CHECK();
    }

}
//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�X�F��ʈ���v�{�^�������������̏���
//
//  �@�\����
//    CtrlOFF:�\����ʂ�������܂�
//    CtrlON :�����ʁ^����l�ҏW��ʂ�؂�ւ��܂�
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
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnF09Click(TObject *Sender)
{
	TMsgDlgButtons MsgButton;
    AnsiString sBuf;

	if( !BtnF09->Enabled ) return;
    if( !BtnF09->Tag ){
        ////////////////////
        // ��ʈ�� �i���܂�Ɍ���͂������������ߊm�F���b�Z�[�W��ǉ����܂����j
        sBuf  = "��ʂ�������܂�����낵���ł����H";
        sBuf += "\n[�́@��] �\������Ă����ʂ�������܂��B";
        sBuf += "\n[�L�����Z��] ��ʈ���̎������B";
        MsgButton << mbYes << mbCancel;
        switch( MessageDlg( sBuf, mtConfirmation , MsgButton, 0) ){
        // �uYes�v      �ۑ�
        case mrYes:
            break;
        // �uCancel�v   �L�����Z��
        case mrCancel:
        return;
        }
	    Form1->Print();
    }
    else {
		////////////////////
        // ����p�l�ҏW
        if( SGr_vRIRE_SOZAI->Color == 0x00DDDDDD ){
            // �ʏ�̑����ʂɕύX
        	SGr_vRIRE_SOZAI->Color = (TColor)0x00D2FFFF;
        	SGr_vSOKU_SOZAI->Color = (TColor)0x00D2FFFF;
        	SGr_vRIRE_SYUKA->Color = (TColor)0x00FFEEDD;
        	SGr_vSOKU_SYUKA->Color = clWindow;
            SCREEN_SET();
			Mem_vRIRE_MEMOORG->Color = (TColor)0x00FFEEDD;

			SBr1->Panels->Items[0]->Text = "�ʏ�̑����ʂł��B";
        }
        else {
            // ����ҏW��ʂɕύX
        	SGr_vRIRE_SOZAI->Color = (TColor)0x00DDDDDD;
        	SGr_vSOKU_SOZAI->Color = (TColor)0x00DDDDDD;
        	SGr_vRIRE_SYUKA->Color = (TColor)0x00DDDDDD;
        	SGr_vSOKU_SYUKA->Color = (TColor)0x00DDDDDD;
			DISP_SCREEN_SET();
			Mem_vRIRE_MEMOORG->Color = (TColor)0x00DDDDDD;
			SBr1->Panels->Items[0]->Text = "����p�̕ҏW��ʂł��B";
		}
		SBr1->Update();
    }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�P�O�FExcel�o�́v�{�^�������������̏���
//
//  �@�\����
//    CtrlOFF:�\����ʂ�������܂�
//    CtrlON :����
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
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnF10Click(TObject *Sender)
{
	bool bHan;
    int iCol;
    AnsiString sBuf;
	TMsgDlgButtons MsgButton;
	TShiftState State;
    unsigned short shtHoge=17;
    bool        retDLL;

    if( BtnF10->Tag ){
        if( !bINPUTLOT_OK )
        {
    	    sBuf  = "�L���ȃ��b�g�����͂���Ă��Ȃ��׏o���܂���B";
            MsgButton << mbOK;
            MessageDlg( sBuf, mtWarning	, MsgButton, 0);
            AllKeyUp(Sender,shtHoge,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
            return;
        }
        else
        {
            Form12->ShowModal();
            AllKeyUp(Sender,shtHoge,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
            return;
        }
    }

    if( !bINPUTLOT_OK )
    {
    	sBuf  = "�L���ȃ��b�g�����͂���Ă��Ȃ��׍��ڂd���������o�͂͏o���܂���B";
        MsgButton << mbOK;
        MessageDlg( sBuf, mtWarning	, MsgButton, 0);
        AllKeyUp(Sender,shtHoge,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
        return;
    }
    if( !BtnF10->Enabled )    return;

    else
    {
        ////////////////////
        // �d���������o��


        if( UPDATE_CHECK())
        {
    	// �m�F���b�Z�[�W
// �y���z�f�[�^���ҏW����Ă���ꍇ�����A�m�F���b�Z�[�W�̕\�����s�Ȃ�
            if( MessageDlg( "�d���������o�͂��s�Ȃ��ɂ́A���݂̑���f�[�^��ۑ�����K�v������܂��B\n�ۑ����s�������𑱍s���܂��B��낵���ł����H",
                mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo ){
                AllKeyUp(Sender,shtHoge,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
                return;
            }

			// 2003/10/30 A.Tamura �Ō�Ƀt�H�[�J�X�̗L�����Z�����ҏW���[�h�̎��A
			// �u�l�̕ۑ��v�Ɓu���菈���v���m���ɍs�Ȃ����߁ADrawCell���Ăяo���܂��B
			TGridDrawState DrawState;
			AllGRID_DrawCell( SGr_vSOKU_SYUKA,
								 SGr_vSOKU_SYUKA->Col,
								 SGr_vSOKU_SYUKA->Row,
								 SGr_vSOKU_SYUKA->CellRect(SGr_vSOKU_SYUKA->Col, SGr_vSOKU_SYUKA->Row),
								 DrawState);
			AllGRID_DrawCell( SGr_vRIRE_SYUKA,
								 SGr_vRIRE_SYUKA->Col,
								 SGr_vRIRE_SYUKA->Row,
								 SGr_vRIRE_SYUKA->CellRect(SGr_vRIRE_SYUKA->Col, SGr_vRIRE_SYUKA->Row),
								 DrawState);
			AllGRID_DrawCell( SGr_vSOKU_SOZAI,
								 SGr_vSOKU_SOZAI->Col,
								 SGr_vSOKU_SOZAI->Row,
								 SGr_vSOKU_SOZAI->CellRect(SGr_vSOKU_SOZAI->Col, SGr_vSOKU_SOZAI->Row),
								 DrawState);
			AllGRID_DrawCell( SGr_vRIRE_SOZAI,
								 SGr_vRIRE_SOZAI->Col,
								 SGr_vRIRE_SOZAI->Row,
								 SGr_vRIRE_SOZAI->CellRect(SGr_vRIRE_SOZAI->Col, SGr_vRIRE_SOZAI->Row),
								 DrawState);

            ALL_INSPECT();              //�S���b�g�̔�����s���܂�
            ADD_SPACE();                //KSD02�ɃX�y�[�X�s��ۑ����܂�
            bHan = Set_DB_SOKU();
            bHan = Set_DB_RIRE();
            bHan = Set_DB_SOKU_SOZAI();
            bHan = Set_DB_RIRE_SOZAI();

//�ۑ����I�������̂Łu�A�b�v�f�[�g�t���O�ƕۑ��t���O�����������܂�
		    if( hSOKU_KSD01_DATA)
		    {
			    for(iCol = 0; iCol<SGr_tSOKU->ColCount;iCol++)
			    {
				    pSOKU_KSD01_DATA[iCol].UPD_FLG = false;
				    pSOKU_KSD01_DATA[iCol].SAVE_FLG = true;
    			}
        	}

		    if( hRIRE_KSD01_DATA)
		    {
			    for(iCol = 0; iCol<SGr_tRIRE->ColCount;iCol++)
    			{
	    			pRIRE_KSD01_DATA[iCol].UPD_FLG = false;
		    		pRIRE_KSD01_DATA[iCol].SAVE_FLG = true;
			    }
    		}
        }
    }
    // 2003/05/14 A.Tamura
    if( !BtnF10->Tag ){
		// TKSS02���N�����܂�
    	AnsiString	sPath = Application->ExeName;
    	AnsiString  sTKSS02;
    	AnsiString	sParam;
    	HWND		Hndl = Application->Handle;
    	int			iPos;

    	iPos = sPath.LastDelimiter("\\");
    	sTKSS02 = sPath.SubString(1,iPos) + "TKSS02.EXE";
    	sParam  = IntToStr(USER_COD) + "," + USER_NAM + "," + BUMO_COD + "," + BUMO_NAM;
		//2003.05.09 E.Takase Add��
    	sParam += "," + sNowDTKSHIN + "," + sNowLOTNO;
		//2003.05.09 E.Takase Add��
		//2003.05.09 E.Takase Add �R�����g��
    	//sParam += "," + Cmb_DTKSHIN->Text + "," + Edt_LOTNO->Text;
		//2003.05.09 E.Takase Add �R�����g��

    	retDLL = ShellExecute( Hndl, NULL, sTKSS02.c_str(), sParam.c_str(), NULL, SW_SHOWNORMAL );
    }
}
//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�P�Q�F�߂�v�{�^�������������̏���
//
//  �@�\����
//    CtrlOFF:���C�����j���[�ɖ߂�܂�
//    CtrlON :����
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
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnF12Click(TObject *Sender)
{
	TMsgDlgButtons mRet;
	AnsiString sBuf;
	TShiftState State;
    unsigned short shtHoge=17;
    if( !BtnF12->Enabled )
	{
        AllKeyUp(Sender,shtHoge,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
    	return;
    }
    Close();

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F����f�[�^�ɍX�V�����������𔻒f���܂��B
//
//  �@�\����
//    �f�[�^���Z�[�u����O�ɖ{�֐����Ăяo���A���b�Z�[�W�̃t���O�ɓK�p���܂��B
//
//  �p�����^����
//    �Ȃ��B
//
//
//  �߂�l
//    bool				�Ftrue = �X�V����Afalse = �X�V�Ȃ�
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::UPDATE_CHECK(void)
{
	int iCol;

	// 2004/09/13 A.Tamura �A�v���P�[�V�����G���[�ׁ̈Atry.. catch()���s�Ȃ��B
	try
	{
	    //KSD01�̃f�[�^��UPD_FLG��ǉ����X�V��True�A���X�V��False�Ƃ��܂����B
		if( hSOKU_KSD01_DATA)
		{
			for(iCol = 0; iCol<SGr_tSOKU->ColCount;iCol++)
			{
				if(pSOKU_KSD01_DATA[iCol].UPD_FLG == true)
				{
					return(true);
				}
			}
	    }

		if( hRIRE_KSD01_DATA && Form1->iRIRE_CNT != 0)
		{
			for(iCol = 0; iCol<SGr_tRIRE->ColCount;iCol++)
			{
				if(pRIRE_KSD01_DATA[iCol].UPD_FLG == true)
				{
					return(true);
				}
			}
		}
	}
	catch ( ... )
	{
		return( true );
	}

	return( false );
}

//---------------------------------------------------------------------------
// 	�e�R���g���[���̃T�C�Y��ύX���܂�
void __fastcall TForm1::Pnl_skInfoResize(TObject *Sender)
{
    int iRMarg;

    //
    // ���݂���������
    //
    // �X�v���b�^�[�̈ʒu�������ꍇ������̂ŁA�ʒu��ݒ肵�Ȃ����܂�
    if( Pnl_skInfo->Width <= Splitter1->MinSize )
    	Splitter1->Left  = Pnl_skInfo->Left + Pnl_skInfo->Width
                         - Splitter1->MinSize;
	else
    	Splitter1->Left  = Pnl_skInfo->Left - Splitter1->Width;

    // �e���x�����猩���e�R���g���[���̉E�[�]��
    iRMarg = 6;

    // �^�C�g��
	if( Pnl_skInfo_Title->Left < Pnl_skInfo->Width &&
        Pnl_skInfo->Width - Pnl_skInfo_Title->Left - iRMarg > 0 ){
		Pnl_skInfo_Title->Width = Pnl_skInfo->Width - Pnl_skInfo_Title->Left - iRMarg;
	} else{
		Pnl_skInfo_Title->Width = 0;
	}

    // ���Ӑ�i��
    if( Pnl_skInfo_vDTKS->Left < Pnl_skInfo->Width &&
		Pnl_skInfo->Width - Pnl_skInfo_vDTKS->Left - iRMarg > 0 ){
		Pnl_skInfo_vDTKS->Width = Pnl_skInfo->Width - Pnl_skInfo_vDTKS->Left - iRMarg;
        Pnl_skInfo_tDTKS->Width = Pnl_skInfo_vDTKS->Left - Pnl_skInfo_tDTKS->Left;
	} else{
		Pnl_skInfo_vDTKS->Width = 0;
	    if( Pnl_skInfo_tDTKS->Left < Pnl_skInfo->Width &&
			Pnl_skInfo->Width - Pnl_skInfo_tDTKS->Left - iRMarg > 0 ){
			Pnl_skInfo_tDTKS->Width = Pnl_skInfo->Width - Pnl_skInfo_tDTKS->Left - iRMarg;
		} else{
			Pnl_skInfo_tDTKS->Width = 0;
		}
	}

    // ���Еi�ԁ��i��
    if( Pnl_skInfo_vHINSYU->Left < Pnl_skInfo->Width &&
		Pnl_skInfo->Width - Pnl_skInfo_vHINSYU->Left - iRMarg > 0 ){
		Pnl_skInfo_vHINSYU->Width = Pnl_skInfo->Width - Pnl_skInfo_vHINSYU->Left - iRMarg;
        Pnl_skInfo_tHINSYU->Width = Pnl_skInfo_vHINSYU->Left - Pnl_skInfo_tHINSYU->Left;
		Pnl_skInfo_vHINBAN->Width = Pnl_skInfo_tHINSYU->Left - Pnl_skInfo_vHINBAN->Left;
   		Pnl_skInfo_tHINBAN->Width = Pnl_skInfo_vHINBAN->Left - Pnl_skInfo_tHINBAN->Left;
	} else{
		Pnl_skInfo_vHINSYU->Width = 0;
	    if( Pnl_skInfo_tHINSYU->Left < Pnl_skInfo->Width &&
			Pnl_skInfo->Width - Pnl_skInfo_tHINSYU->Left - iRMarg > 0 ){
			Pnl_skInfo_tHINSYU->Width = Pnl_skInfo->Width - Pnl_skInfo_tHINSYU->Left - iRMarg;
			Pnl_skInfo_vHINBAN->Width = Pnl_skInfo_tHINSYU->Left - Pnl_skInfo_vHINBAN->Left;
       		Pnl_skInfo_tHINBAN->Width = Pnl_skInfo_vHINBAN->Left - Pnl_skInfo_tHINBAN->Left;
		} else{
			Pnl_skInfo_tHINSYU->Width = 0;
    		if( Pnl_skInfo_vHINBAN->Left < Pnl_skInfo->Width &&
				Pnl_skInfo->Width - Pnl_skInfo_vHINBAN->Left - iRMarg > 0 ){
				Pnl_skInfo_vHINBAN->Width = Pnl_skInfo->Width - Pnl_skInfo_vHINBAN->Left - iRMarg;
        		Pnl_skInfo_tHINBAN->Width = Pnl_skInfo_vHINBAN->Left - Pnl_skInfo_tHINBAN->Left;
			} else{
				Pnl_skInfo_vHINBAN->Width = 0;
	    		if( Pnl_skInfo_tHINBAN->Left < Pnl_skInfo->Width &&
					Pnl_skInfo->Width - Pnl_skInfo_tHINBAN->Left - iRMarg > 0 ){
					Pnl_skInfo_tHINBAN->Width = Pnl_skInfo->Width - Pnl_skInfo_tHINBAN->Left - iRMarg;
				} else{
					Pnl_skInfo_tHINBAN->Width = 0;
				}
			}
		}
	}

    // �i��
    if( Pnl_skInfo_vHINMEI->Left < Pnl_skInfo->Width &&
		Pnl_skInfo->Width - Pnl_skInfo_vHINMEI->Left - iRMarg > 0 ){
		Pnl_skInfo_vHINMEI->Width = Pnl_skInfo->Width - Pnl_skInfo_vHINMEI->Left - iRMarg;
        Pnl_skInfo_tHINMEI->Width = Pnl_skInfo_vHINMEI->Left - Pnl_skInfo_tHINMEI->Left;
	} else{
		Pnl_skInfo_vHINMEI->Width = 0;
	    if( Pnl_skInfo_tHINMEI->Left < Pnl_skInfo->Width &&
			Pnl_skInfo->Width - Pnl_skInfo_tHINMEI->Left - iRMarg > 0 ){
			Pnl_skInfo_tHINMEI->Width = Pnl_skInfo->Width - Pnl_skInfo_tHINMEI->Left - iRMarg;
		} else{
			Pnl_skInfo_tHINMEI->Width = 0;
		}
	}

    // ���b�gNO�P������҂P
    if( Pnl_skInfo_vSOKUUSER1->Left < Pnl_skInfo->Width &&
		Pnl_skInfo->Width - Pnl_skInfo_vSOKUUSER1->Left - iRMarg > 0 ){
		Pnl_skInfo_vSOKUUSER1->Width = Pnl_skInfo->Width - Pnl_skInfo_vSOKUUSER1->Left - iRMarg;
        Pnl_skInfo_tSOKUUSER1->Width = Pnl_skInfo_vSOKUUSER1->Left - Pnl_skInfo_tSOKUUSER1->Left;
		Pnl_skInfo_vLOTBNG1->Width = Pnl_skInfo_tSOKUUSER1->Left - Pnl_skInfo_vLOTBNG1->Left;
   		Pnl_skInfo_tLOTBNG1->Width = Pnl_skInfo_vLOTBNG1->Left - Pnl_skInfo_tLOTBNG1->Left;
	} else{
		Pnl_skInfo_vSOKUUSER1->Width = 0;
	    if( Pnl_skInfo_tSOKUUSER1->Left < Pnl_skInfo->Width &&
			Pnl_skInfo->Width - Pnl_skInfo_tSOKUUSER1->Left - iRMarg > 0 ){
			Pnl_skInfo_tSOKUUSER1->Width = Pnl_skInfo->Width - Pnl_skInfo_tSOKUUSER1->Left - iRMarg;
			Pnl_skInfo_vLOTBNG1->Width = Pnl_skInfo_tSOKUUSER1->Left - Pnl_skInfo_vLOTBNG1->Left;
       		Pnl_skInfo_tLOTBNG1->Width = Pnl_skInfo_vLOTBNG1->Left - Pnl_skInfo_tLOTBNG1->Left;
		} else{
			Pnl_skInfo_tSOKUUSER1->Width = 0;
    		if( Pnl_skInfo_vLOTBNG1->Left < Pnl_skInfo->Width &&
				Pnl_skInfo->Width - Pnl_skInfo_vLOTBNG1->Left - iRMarg > 0 ){
				Pnl_skInfo_vLOTBNG1->Width = Pnl_skInfo->Width - Pnl_skInfo_vLOTBNG1->Left - iRMarg;
        		Pnl_skInfo_tLOTBNG1->Width = Pnl_skInfo_vLOTBNG1->Left - Pnl_skInfo_tLOTBNG1->Left;
			} else{
				Pnl_skInfo_vLOTBNG1->Width = 0;
	    		if( Pnl_skInfo_tLOTBNG1->Left < Pnl_skInfo->Width &&
					Pnl_skInfo->Width - Pnl_skInfo_tLOTBNG1->Left - iRMarg > 0 ){
					Pnl_skInfo_tLOTBNG1->Width = Pnl_skInfo->Width - Pnl_skInfo_tLOTBNG1->Left - iRMarg;
				} else{
					Pnl_skInfo_tLOTBNG1->Width = 0;
				}
			}
		}
	}

    // �������ڂP
    if( Pnl_skInfo_vKENSA1->Left < Pnl_skInfo->Width &&
		Pnl_skInfo->Width - Pnl_skInfo_vKENSA1->Left - iRMarg - 1 > 0 ){
		Pnl_skInfo_vKENSA1->Width = Pnl_skInfo->Width - Pnl_skInfo_vKENSA1->Left - iRMarg - 1;
        Pnl_skInfo_tKENSA1->Width = Pnl_skInfo_vKENSA1->Left - Pnl_skInfo_tKENSA1->Left;
	} else{
		Pnl_skInfo_vKENSA1->Width = 0;
	    if( Pnl_skInfo_tKENSA1->Left < Pnl_skInfo->Width &&
			Pnl_skInfo->Width - Pnl_skInfo_tKENSA1->Left - iRMarg - 1 > 0 ){
			Pnl_skInfo_tKENSA1->Width = Pnl_skInfo->Width - Pnl_skInfo_tKENSA1->Left - iRMarg - 1;
		} else{
			Pnl_skInfo_tKENSA1->Width = 0;
		}
	}

    // ����@��P
    if( Pnl_skInfo_vKIKI1->Left < Pnl_skInfo->Width &&
		Pnl_skInfo->Width - Pnl_skInfo_vKIKI1->Left - iRMarg - 1 > 0 ){
		Pnl_skInfo_vKIKI1->Width = Pnl_skInfo->Width - Pnl_skInfo_vKIKI1->Left - iRMarg - 1;
        Pnl_skInfo_tKIKI1->Width = Pnl_skInfo_vKIKI1->Left - Pnl_skInfo_tKIKI1->Left;
	} else{
		Pnl_skInfo_vKIKI1->Width = 0;
	    if( Pnl_skInfo_tKIKI1->Left < Pnl_skInfo->Width &&
			Pnl_skInfo->Width - Pnl_skInfo_tKIKI1->Left - iRMarg > 0 ){
			Pnl_skInfo_tKIKI1->Width = Pnl_skInfo->Width - Pnl_skInfo_tKIKI1->Left - iRMarg - 1;
		} else{
			Pnl_skInfo_tKIKI1->Width = 0;
		}
	}

    // �K�i�P
    if( Pnl_skInfo_vKIKAKU1->Left < Pnl_skInfo->Width &&
		Pnl_skInfo->Width - Pnl_skInfo_vKIKAKU1->Left - iRMarg - 1 > 0 ){
		Pnl_skInfo_vKIKAKU1->Width = Pnl_skInfo->Width - Pnl_skInfo_vKIKAKU1->Left - iRMarg - 1;
        Pnl_skInfo_tKIKAKU1->Width = Pnl_skInfo_vKIKAKU1->Left - Pnl_skInfo_tKIKAKU1->Left;
	} else{
		Pnl_skInfo_vKIKAKU1->Width = 0;
	    if( Pnl_skInfo_tKIKAKU1->Left < Pnl_skInfo->Width &&
			Pnl_skInfo->Width - Pnl_skInfo_tKIKAKU1->Left - iRMarg - 1 > 0 ){
			Pnl_skInfo_tKIKAKU1->Width = Pnl_skInfo->Width - Pnl_skInfo_tKIKAKU1->Left - iRMarg - 1;
		} else{
			Pnl_skInfo_tKIKAKU1->Width = 0;
		}
	}

    // ���藚�����H���\�͂P
	if( Pcl_skInfo_page1->Left < Pnl_skInfo->Width &&
        Pnl_skInfo->Width - Pcl_skInfo_page1->Left - iRMarg > 0 ){
		Pcl_skInfo_page1->Width = Pnl_skInfo->Width - Pcl_skInfo_page1->Left - iRMarg;
	} else{
		Pcl_skInfo_page1->Width = 0;
	}

    // ���b�gNO�Q������҂Q
    if( Pnl_skInfo_vSOKUUSER2->Left < Pnl_skInfo->Width &&
		Pnl_skInfo->Width - Pnl_skInfo_vSOKUUSER2->Left - iRMarg > 0 ){
		Pnl_skInfo_vSOKUUSER2->Width = Pnl_skInfo->Width - Pnl_skInfo_vSOKUUSER2->Left - iRMarg;
        Pnl_skInfo_tSOKUUSER2->Width = Pnl_skInfo_vSOKUUSER2->Left - Pnl_skInfo_tSOKUUSER2->Left;
		Pnl_skInfo_vLOTBNG2->Width = Pnl_skInfo_tSOKUUSER2->Left - Pnl_skInfo_vLOTBNG2->Left;
   		Pnl_skInfo_tLOTBNG2->Width = Pnl_skInfo_vLOTBNG2->Left - Pnl_skInfo_tLOTBNG2->Left;
	} else{
		Pnl_skInfo_vSOKUUSER2->Width = 0;
	    if( Pnl_skInfo_tSOKUUSER2->Left < Pnl_skInfo->Width &&
			Pnl_skInfo->Width - Pnl_skInfo_tSOKUUSER2->Left - iRMarg > 0 ){
			Pnl_skInfo_tSOKUUSER2->Width = Pnl_skInfo->Width - Pnl_skInfo_tSOKUUSER2->Left - iRMarg;
			Pnl_skInfo_vLOTBNG2->Width = Pnl_skInfo_tSOKUUSER2->Left - Pnl_skInfo_vLOTBNG2->Left;
       		Pnl_skInfo_tLOTBNG2->Width = Pnl_skInfo_vLOTBNG2->Left - Pnl_skInfo_tLOTBNG2->Left;
		} else{
			Pnl_skInfo_tSOKUUSER2->Width = 0;
    		if( Pnl_skInfo_vLOTBNG2->Left < Pnl_skInfo->Width &&
				Pnl_skInfo->Width - Pnl_skInfo_vLOTBNG2->Left - iRMarg > 0 ){
				Pnl_skInfo_vLOTBNG2->Width = Pnl_skInfo->Width - Pnl_skInfo_vLOTBNG2->Left - iRMarg;
        		Pnl_skInfo_tLOTBNG2->Width = Pnl_skInfo_vLOTBNG2->Left - Pnl_skInfo_tLOTBNG2->Left;
			} else{
				Pnl_skInfo_vLOTBNG2->Width = 0;
	    		if( Pnl_skInfo_tLOTBNG2->Left < Pnl_skInfo->Width &&
					Pnl_skInfo->Width - Pnl_skInfo_tLOTBNG2->Left - iRMarg > 0 ){
					Pnl_skInfo_tLOTBNG2->Width = Pnl_skInfo->Width - Pnl_skInfo_tLOTBNG2->Left - iRMarg;
				} else{
					Pnl_skInfo_tLOTBNG2->Width = 0;
				}
			}
		}
	}

    // �������ڂQ
    if( Pnl_skInfo_vKENSA2->Left < Pnl_skInfo->Width &&
		Pnl_skInfo->Width - Pnl_skInfo_vKENSA2->Left - iRMarg - 1 > 0 ){
		Pnl_skInfo_vKENSA2->Width = Pnl_skInfo->Width - Pnl_skInfo_vKENSA2->Left - iRMarg - 1;
        Pnl_skInfo_tKENSA2->Width = Pnl_skInfo_vKENSA2->Left - Pnl_skInfo_tKENSA2->Left;
	} else{
		Pnl_skInfo_vKENSA2->Width = 0;
	    if( Pnl_skInfo_tKENSA2->Left < Pnl_skInfo->Width &&
			Pnl_skInfo->Width - Pnl_skInfo_tKENSA2->Left - iRMarg - 1 > 0 ){
			Pnl_skInfo_tKENSA2->Width = Pnl_skInfo->Width - Pnl_skInfo_tKENSA2->Left - iRMarg - 1;
		} else{
			Pnl_skInfo_tKENSA2->Width = 0;
		}
	}

    // ����@��Q
    if( Pnl_skInfo_vKIKI2->Left < Pnl_skInfo->Width &&
		Pnl_skInfo->Width - Pnl_skInfo_vKIKI2->Left - iRMarg - 1 > 0 ){
		Pnl_skInfo_vKIKI2->Width = Pnl_skInfo->Width - Pnl_skInfo_vKIKI2->Left - iRMarg - 1;
        Pnl_skInfo_tKIKI2->Width = Pnl_skInfo_vKIKI2->Left - Pnl_skInfo_tKIKI2->Left;
	} else{
		Pnl_skInfo_vKIKI2->Width = 0;
	    if( Pnl_skInfo_tKIKI2->Left < Pnl_skInfo->Width &&
			Pnl_skInfo->Width - Pnl_skInfo_tKIKI2->Left - iRMarg - 1 > 0 ){
			Pnl_skInfo_tKIKI2->Width = Pnl_skInfo->Width - Pnl_skInfo_tKIKI2->Left - iRMarg - 1;
		} else{
			Pnl_skInfo_tKIKI2->Width = 0;
		}
	}

    // �K�i�Q
    if( Pnl_skInfo_vKIKAKU2->Left < Pnl_skInfo->Width &&
		Pnl_skInfo->Width - Pnl_skInfo_vKIKAKU2->Left - iRMarg - 1 > 0 ){
		Pnl_skInfo_vKIKAKU2->Width = Pnl_skInfo->Width - Pnl_skInfo_vKIKAKU2->Left - iRMarg - 1;
        Pnl_skInfo_tKIKAKU2->Width = Pnl_skInfo_vKIKAKU2->Left - Pnl_skInfo_tKIKAKU2->Left;
	} else{
		Pnl_skInfo_vKIKAKU2->Width = 0;
	    if( Pnl_skInfo_tKIKAKU2->Left < Pnl_skInfo->Width &&
			Pnl_skInfo->Width - Pnl_skInfo_tKIKAKU2->Left - iRMarg - 1 > 0 ){
			Pnl_skInfo_tKIKAKU2->Width = Pnl_skInfo->Width - Pnl_skInfo_tKIKAKU2->Left - iRMarg - 1;
		} else{
			Pnl_skInfo_tKIKAKU2->Width = 0;
		}
	}

    // ���藚�����H���\�͂Q
	if( Pcl_skInfo_page2->Left < Pnl_skInfo->Width &&
        Pnl_skInfo->Width - Pcl_skInfo_page2->Left - iRMarg > 0 ){
		Pcl_skInfo_page2->Width = Pnl_skInfo->Width - Pcl_skInfo_page2->Left - iRMarg;
	} else{
		Pcl_skInfo_page2->Width = 0;
	}

    // �J���[���C��
	if( Shp_ColorLine1->Left < Pnl_skInfo->Width &&
        Pnl_skInfo->Width - Shp_ColorLine1->Left - 4 > 0 ){
		Shp_ColorLine1->Width = Pnl_skInfo->Width - Shp_ColorLine1->Left - 4;
	} else{
		Shp_ColorLine1->Width = 0;
	}
	if( Shp_ColorLine2->Left < Pnl_skInfo->Width &&
        Pnl_skInfo->Width - Shp_ColorLine2->Left - 4 > 0 ){
		Shp_ColorLine2->Width = Pnl_skInfo->Width - Shp_ColorLine2->Left - 4;
	} else{
		Shp_ColorLine2->Width = 0;
	}

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Panel22Resize(TObject *Sender)
{
    // ���̃p�l���ƘA�g���ăT�C�Y�ύX���܂�
    Panel23->Height = Panel22->Height;
    Panel24->Height = Panel22->Height;
    // �X�v���b�^�[�̈ʒu�������ꍇ������̂ŁA�ʒu��ݒ肵�Ȃ����܂�
    if( Panel22->Height <= Splitter3->MinSize )
    	Splitter3->Top  = Splitter3->MinSize;
    else
    	Splitter3->Top  = Panel22->Height;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Panel23Resize(TObject *Sender)
{
    // ���̃p�l���ƘA�g���ăT�C�Y�ύX���܂�
    Panel22->Height = Panel23->Height;
    Panel24->Height = Panel23->Height;
    // �X�v���b�^�[�̈ʒu�������ꍇ������̂ŁA�ʒu��ݒ肵�Ȃ����܂�
    if( Panel23->Height <= Splitter4->MinSize )
	    Splitter4->Top  = Splitter4->MinSize;
    else
	    Splitter4->Top  = Panel23->Height;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Panel24Resize(TObject *Sender)
{
    // ���̃p�l���ƘA�g���ăT�C�Y�ύX���܂�
    Panel22->Height = Panel24->Height;
    Panel23->Height = Panel24->Height;
    // �X�v���b�^�[�̈ʒu�������ꍇ������̂ŁA�ʒu��ݒ肵�Ȃ����܂�
    if( Panel24->Height <= Splitter5->MinSize )
    	Splitter5->Top  = Splitter5->MinSize;
	else
    	Splitter5->Top  = Panel24->Height;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Panel173Resize(TObject *Sender)
{
    if( Panel173->Height >= (Mem_vRIRE_MEMOORG->Height + 18) )
	    Panel173->Height = Mem_vRIRE_MEMOORG->Height + 18;

    // ���̃p�l���ƘA�g���ăT�C�Y�ύX���܂�
    Panel174->Height = Panel173->Height;
    Panel175->Height = Panel173->Height;
    // �X�v���b�^�[�̈ʒu�������ꍇ������̂ŁA�ʒu��ݒ肵�Ȃ����܂�
    if( Panel173->Height <= Splitter6->MinSize )
    	Splitter6->Top  = Splitter6->MinSize;
	else
    	Splitter6->Top  = Panel173->Height;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Panel174Resize(TObject *Sender)
{
    if( Panel174->Height >= (Mem_vRIRE_MEMOORG->Height + 18) )
	    Panel174->Height = Mem_vRIRE_MEMOORG->Height + 18;

    // ���̃p�l���ƘA�g���ăT�C�Y�ύX���܂�
    Panel173->Height = Panel174->Height;
    Panel175->Height = Panel174->Height;
    // �X�v���b�^�[�̈ʒu�������ꍇ������̂ŁA�ʒu��ݒ肵�Ȃ����܂�
    if( Panel174->Height <= Splitter7->MinSize )
    	Splitter7->Top  = Splitter7->MinSize;
	else
    	Splitter7->Top  = Panel174->Height;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Panel175Resize(TObject *Sender)
{
    if( Panel175->Height >= (Mem_vRIRE_MEMOORG->Height + 18) )
	    Panel175->Height = Mem_vRIRE_MEMOORG->Height + 18;

    // ���̃p�l���ƘA�g���ăT�C�Y�ύX���܂�
    Panel173->Height = Panel175->Height;
    Panel174->Height = Panel175->Height;
    // �X�v���b�^�[�̈ʒu�������ꍇ������̂ŁA�ʒu��ݒ肵�Ȃ����܂�
    if( Panel175->Height <= Splitter8->MinSize )
    	Splitter8->Top  = Splitter8->MinSize;
	else
    	Splitter8->Top  = Panel175->Height;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Panel14Resize(TObject *Sender)
{
    //
    // ���݂���������
    //
    // �X�v���b�^�[�̈ʒu�������ꍇ������̂ŁA�ʒu��ݒ肵�Ȃ����܂�
    if( Panel14->Width <= Splitter2->MinSize )
    	Splitter2->Left  = Splitter2->MinSize;
	else
    	Splitter2->Left  = Panel14->Width;
}
//---------------------------------------------------------------------------
//
//  �T�v
//    OnKeyDown�C�x���g	�F�L�[���͂�����Ɣ������܂��B
//
//  �@�\����
//    �t�@���N�V�����L�[�̊e�������Ăяo���܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    WORD &Key			�F�L�[�R�[�h
//    TShiftState Shift	�F[Shift]�C[Alt]�C[Ctrl]�L�[�𔻒肵�܂�
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �e�Q�̓��͂�EditBox���J���O���b�h�ړ��̍ۍX�V�t���O���딻��
//    ����̂łe�Q���e�P�R�Ƃ��ď������s���܂��B
//
//---------------------------------------------------------------------------

void __fastcall TForm1::AllKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    bool blnHoge=true;
//    MSG msg;
    // [Ctrl]�L�[����������
    if( Shift.Contains(ssCtrl) ){
        BtnF01->Caption = "�S���\��";
        BtnF02->Caption = "�f�ޒl�\��";
        BtnF03->Caption = "����l�\��";
        BtnF04->Caption = "�O���t�\��";
        BtnF05->Caption = "���l���\��";
        BtnF06->Caption = "���ڕҏW";
        BtnF07->Caption = "�f�ރ��b�g";
        BtnF08->Caption = "�����[����";
        BtnF09->Caption = "����l�ҏW";
        BtnF10->Caption = "�f�ގ撼��";
        BtnF11->Caption = "";
        BtnF12->Caption = "";

        BtnF01->Enabled = true;
        BtnF02->Enabled = true;
        BtnF03->Enabled = true;
        BtnF04->Enabled = true;
        BtnF05->Enabled = true;
        BtnF06->Enabled = true;
        BtnF07->Enabled = true;
        BtnF08->Enabled = true;
        BtnF09->Enabled = true;
        BtnF10->Enabled = true;
        BtnF11->Enabled = false;
        BtnF12->Enabled = false;

        BtnF01->Tag = 1;
        BtnF02->Tag = 1;
        BtnF03->Tag = 1;
        BtnF04->Tag = 1;
        BtnF05->Tag = 1;
        BtnF06->Tag = 1;
        BtnF07->Tag = 1;
        BtnF08->Tag = 1;
        BtnF09->Tag = 1;
        BtnF10->Tag = 1;
        BtnF11->Tag = 1;
        BtnF12->Tag = 1;
    }
    switch(Key) {
        case VK_F1:  BtnF01Click(Sender);    break;
        case VK_F2:  Key = VK_F13;
                     Delete_InplaceEdit(Sender);		// �ҏW�E�B���h�E�𖳌��ɂ��܂�
                     BtnF02Click(Sender);
                     break;
        case VK_F3:  BtnF03Click(Sender);    break;
        case VK_F4:  BtnF04Click(Sender);    break;
        case VK_F5:  BtnF05Click(Sender);    break;
        case VK_F6:  BtnF06Click(Sender);    break;
        case VK_F7:  BtnF07Click(Sender);    break;
        case VK_F8:
    				 switch(pInfoGlaph.GRID_NO)
    				 {
	    			 case 1: AllGRID_SelectCell(SGr_vSOKU_SYUKA,SGr_vSOKU_SYUKA->Col,0,blnHoge);
							 break;
                     case 2: AllGRID_SelectCell(SGr_vRIRE_SYUKA,SGr_vRIRE_SYUKA->Col,0,blnHoge);
                     		 break;
	    			 case 3: AllGRID_SelectCell(SGr_vSOKU_SOZAI,SGr_vSOKU_SOZAI->Col,0,blnHoge);
							 break;
	    			 case 4: AllGRID_SelectCell(SGr_vRIRE_SOZAI,SGr_vRIRE_SOZAI->Col,0,blnHoge);
							 break;
					 }


        			 BtnF08Click(Sender);    break;
        case VK_F9:  BtnF09Click(Sender);    break;
        case VK_F10: BtnF10Click(Sender);
                     if( Shift.Contains(ssCtrl) ) Key = 0;
					 break;
        case VK_F11: BtnF11Click(Sender);    break;
        case VK_ESCAPE:
        case VK_F12: BtnF12Click(Sender);    break;

        // Enter
        case VK_RETURN:

                // ��\���Ӑ�i�ԂɃJ�[�\��������Ƃ�
        		if( Cmb_DTKSHIN->Focused() ){
                	Edt_LOTNO->SetFocus();
                	break;
                }

                // ���b�gNO�ȂǂɃJ�[�\��������Ƃ�
        		if( Edt_LOTNO->Focused()		||
                	CHkSEIKANDATA->Focused()	||
                    Chk_RIRE->Focused()			||
                    Edt_RIRE_NUM->Focused()		){
                    BtnF07Click(Sender);
                }
				break;

        case VK_LEFT:
        case VK_RIGHT:
                if( SGr_vRIRE_SOZAI->EditorMode	||
                	SGr_vSOKU_SOZAI->EditorMode	||
                	SGr_vRIRE_SYUKA->EditorMode	||
                    SGr_vSOKU_SYUKA->EditorMode ){
                    if( AnsiString(Sender->ClassName()) == "TStringGrid" ){

						TStringGrid		*Sgr = (TStringGrid *)Sender;

						// �L�����b�g�̈ʒu���擾
						// �ҏW�Z���iTInplaceEdit�j������
						TInplaceEdit *edit = NULL;
						int ComCount = Sgr->ComponentCount;  // �S�R���|�[�l���g��

						for( int i=0; i<ComCount; i++ ){
							TComponent *component = Sgr->Components[i];
                            AnsiString name = component->ClassName();
							if( name == "TInplaceEdit" ){
								edit = ( TInplaceEdit* )component;
								break;
							}
						}

						// �ҏW�Z���iTInplaceEdit�j�����݂���
						if( edit ){
                            if( Key == VK_LEFT && Sgr->Col > 0 ){
                            	if( edit->SelStart == 0 && edit->SelLength == 0 ){
                                	Sgr->Col = Sgr->Col - 1;
								}
                            }
                            if( Key == VK_RIGHT && Sgr->Col < (Sgr->ColCount - 1) ){
                            	if( edit->SelStart == edit->Text.Length() && edit->SelLength == 0 ){
                                	Sgr->Col = Sgr->Col + 1;
								}
                            }
						}
                    }
                }
				break;
        case VK_DELETE:
                if( AnsiString(Sender->ClassName()) == "TStringGrid" ){

					TStringGrid		*Sgr = (TStringGrid *)Sender;

					// �L�����b�g�̈ʒu���擾
					// �ҏW�Z���iTInplaceEdit�j������
					TInplaceEdit *edit = NULL;
					int ComCount = Sgr->ComponentCount;  // �S�R���|�[�l���g��
                    int bAllClear;
                    bAllClear = false;
					for( int i=0; i<ComCount; i++ ){
						TComponent *component = Sgr->Components[i];
                        AnsiString name = component->ClassName();
						if( name == "TInplaceEdit" ){
							edit = ( TInplaceEdit* )component;
                            if( !edit->Visible() ){
                            	edit = NULL;
                            }
							break;
						}
					}

                    // �ҏW�ł��Ȃ��Z���́A�폜���o���܂���
					if(Sender == SGr_vSOKU_SYUKA) {
						if((Sgr->Cells[Sgr->Col][Sgr->Row] == "�s�v" && bKASOU_MOVE == false)
							|| !hCELLINFO_SOKU_SYUKA) {
							break;
						}
						if( hCELLINFO_SOKU_SYUKA) {
							if( AnsiString(pCELLINFO_SOKU_SYUKA[Sgr->Col*Sgr->RowCount+Sgr->Row].RESULT) == "�s�v") {
								break;
							}
						}
					}
					if(Sender == SGr_vSOKU_SOZAI) {
						if((Sgr->Cells[Sgr->Col][Sgr->Row] == "�s�v" && bKASOU_MOVE == false)
							|| !hCELLINFO_SOKU_SOZAI) {
							break;
						}
						if( hCELLINFO_SOKU_SOZAI) {
							if( AnsiString(pCELLINFO_SOKU_SOZAI[Sgr->Col*Sgr->RowCount+Sgr->Row].RESULT) == "�s�v") {
								break;
							}
						}
					}
					if(Sender == SGr_vRIRE_SYUKA) {
						if((Sgr->Cells[Sgr->Col][Sgr->Row] == "�s�v" && bKASOU_MOVE == false)
							|| !hCELLINFO_RIRE_SYUKA) {
							break;
						}
						if( hCELLINFO_RIRE_SYUKA) {
							if( AnsiString(pCELLINFO_RIRE_SYUKA[Sgr->Col*Sgr->RowCount+Sgr->Row].RESULT) == "�s�v") {
								break;
							}
						}
					}
					if(Sender == SGr_vRIRE_SOZAI) {
						if((Sgr->Cells[Sgr->Col][Sgr->Row] == "�s�v" && bKASOU_MOVE == false)
							|| !hCELLINFO_RIRE_SOZAI) {
							break;
						}
						if( hCELLINFO_RIRE_SOZAI) {
							if( AnsiString(pCELLINFO_RIRE_SOZAI[Sgr->Col*Sgr->RowCount+Sgr->Row].RESULT) == "�s�v") {
								break;
							}
						}
					}
					if( Sgr->Row == 0 ) {
						break;
					}

					// �ҏW�Z���iTInplaceEdit�j�����݂��Ȃ�
                    if( !edit ){
                        Sgr->Cells[Sgr->Col][Sgr->Row] = "";
                        GRID_SetEditText(Sender,Sgr->Col, Sgr->Row, "");

                    }
                }
                if( Sender == SGr_vSOKU_SYUKA ) SGr_vSOKU_SYUKAKeyPress(Sender, VK_DELETE);
                if( Sender == SGr_vRIRE_SYUKA ) SGr_vRIRE_SYUKAKeyPress(Sender, VK_DELETE);
                if( Sender == SGr_vSOKU_SOZAI ) SGr_vSOKU_SOZAIKeyPress(Sender, VK_DELETE);
                if( Sender == SGr_vRIRE_SOZAI ) SGr_vRIRE_SOZAIKeyPress(Sender, VK_DELETE);
                break;
    }

	int iCol,iRow;
    //�O���^�����^Return�̓��͂͌㏈���Ƃ��ăO���b�h��Ƀt�H�[�J�X���Z�b�g���܂�
	if(Key == VK_F13 || Key == VK_F3 || Key == VK_RETURN)
    {
    	switch(pInfoGlaph.GRID_NO)
    	{
	    case 1:
    	    iCol = SGr_vSOKU_SYUKA->Col;
			iRow = SGr_vSOKU_SYUKA->Row;
			AllGRID_SelectCell(SGr_vSOKU_SYUKA,iCol,iRow,blnHoge);
			break;
	    case 2:
    	    iCol = SGr_vRIRE_SYUKA->Col;
			iRow = SGr_vRIRE_SYUKA->Row;
			AllGRID_SelectCell(SGr_vRIRE_SYUKA,iCol,iRow,blnHoge);
			break;
	    case 3:
    	    iCol = SGr_vSOKU_SOZAI->Col;
			iRow = SGr_vSOKU_SOZAI->Row;
			AllGRID_SelectCell(SGr_vSOKU_SOZAI,iCol,iRow,blnHoge);
			break;
	    case 4:
    	    iCol = SGr_vRIRE_SOZAI->Col;
			iRow = SGr_vRIRE_SOZAI->Row;
			AllGRID_SelectCell(SGr_vRIRE_SOZAI,iCol,iRow,blnHoge);
			break;
		}
	}
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnKeyUp�C�x���g	�F���[�U�[���C�ӂ̃L�[�𗣂��Ɣ������܂�
//
//  �@�\����
//    �t�@���N�V�����L�[�A���L�[�AEnter�L�[�ɂ��{�^����I�����܂�
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    WORD &Key			�F�L�[�R�[�h
//    TShiftState Shift	�F[Shift]�C[Alt]�C[Ctrl]�L�[�𔻒肵�܂�
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::AllKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
      if( Key == 17 ){
          BtnF01->Caption = "�ꗗ����";
          BtnF02->Caption = "�O��";
          BtnF03->Caption = "����";
          BtnF04->Caption = "���ٕ���";
          BtnF05->Caption = "Ch�ؑ�";
          BtnF06->Caption = "HT�Ǎ�";
          BtnF07->Caption = "����";
          BtnF08->Caption = "�S���Ґؑ�";
          BtnF09->Caption = "��ʈ��";
          BtnF10->Caption = "Excel�o��";
          BtnF11->Caption = "�ۑ�";
          BtnF12->Caption = "�߂�";

          // 2003/05/19 A.T
          //BtnF01->Enabled = true;
          FormEnter(Sender);

          BtnF02->Enabled = true;
          BtnF03->Enabled = true;
          BtnF04->Enabled = true;
          BtnF05->Enabled = true;
          BtnF06->Enabled = true;
          BtnF07->Enabled = true;
          BtnF08->Enabled = true;
          BtnF09->Enabled = true;
          BtnF10->Enabled = true;
          BtnF11->Enabled = true;
          BtnF12->Enabled = true;

          BtnF01->Tag = 0;
          BtnF02->Tag = 0;
          BtnF03->Tag = 0;
          BtnF04->Tag = 0;
          BtnF05->Tag = 0;
          BtnF06->Tag = 0;
          BtnF07->Tag = 0;
          BtnF08->Tag = 0;
          BtnF09->Tag = 0;
          BtnF10->Tag = 0;
          BtnF11->Tag = 0;
          BtnF12->Tag = 0;
      }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�ތ����p�X�N���[���{�b�N�X�̃X�N���[���C�x���g����
//
//  �@�\����
//    �X�N���[���{�b�N�X���X�N���[�������Ƃ��ׂ̃O���b�h�����킹�ăX�N���[�����܂�
//
//  �p�����^����
//    TMessage& msg		�FWindows ���b�Z�[�W�������܂��B
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SBx_Left_SOZAI_WndProc(TMessage& msg) {
    if (msg.Msg == WM_VSCROLL){
        int iPos;
        iPos = (int)(SBx_Left_SOZAI->VertScrollBar->Position / 25);
        SGr_vRIRE_SOZAI->TopRow = iPos;
        SGr_vSOKU_SOZAI->TopRow = iPos;
        if( SBx_Left_SOZAI->VertScrollBar->Position != (iPos * 25))
        	SBx_Left_SOZAI->VertScrollBar->Position = iPos * 25;
    }
    SaveSBx_Left_SOZAI_WndProc(msg);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�o�׌����p�X�N���[���{�b�N�X�̃X�N���[���C�x���g����
//
//  �@�\����
//    �X�N���[���{�b�N�X���X�N���[�������Ƃ��ׂ̃O���b�h�����킹�ăX�N���[�����܂�
//
//  �p�����^����
//    TMessage& msg		�FWindows ���b�Z�[�W�������܂��B
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SBx_Left_SYUKA_WndProc(TMessage& msg) {
    if (msg.Msg == WM_VSCROLL){
        int iPos;
        iPos = (int)(SBx_Left_SYUKA->VertScrollBar->Position / 25);
        SGr_vRIRE_SYUKA->TopRow = iPos;
        SGr_vSOKU_SYUKA->TopRow = iPos;
        if( SBx_Left_SYUKA->VertScrollBar->Position != (iPos * 25))
        	SBx_Left_SYUKA->VertScrollBar->Position = iPos * 25;
    }
    SaveSBx_Left_SYUKA_WndProc(msg);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F���l�i����j�p�X�N���[���{�b�N�X�̃X�N���[���C�x���g����
//
//  �@�\����
//    �X�N���[���{�b�N�X���X�N���[�������Ƃ���̃O���b�h�����킹�ăX�N���[�����܂�
//
//  �p�����^����
//    TMessage& msg		�FWindows ���b�Z�[�W�������܂��B
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SBx_vSOKU_MEMO_WndProc(TMessage& msg) {
    if (msg.Msg == WM_HSCROLL){
        int iPos;
        iPos = (int)(SBx_vSOKU_MEMO->HorzScrollBar->Position / Mem_vSOKU_MEMOORG->Width);
        SGr_vSOKU_SOZAI->LeftCol = iPos;
        SGr_vSOKU_SYUKA->LeftCol = iPos;
        if( SBx_vSOKU_MEMO->HorzScrollBar->Position != (iPos * (Mem_vSOKU_MEMOORG->Width + 1)))
        	SBx_vSOKU_MEMO->HorzScrollBar->Position = iPos * (Mem_vSOKU_MEMOORG->Width + 1);
    }
    SaveSBx_vSOKU_MEMO_WndProc(msg);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F���l�i�����j�p�X�N���[���{�b�N�X�̃X�N���[���C�x���g����
//
//  �@�\����
//    �X�N���[���{�b�N�X���X�N���[�������Ƃ���̃O���b�h�����킹�ăX�N���[�����܂�
//
//  �p�����^����
//    TMessage& msg		�FWindows ���b�Z�[�W�������܂��B
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SBx_vRIRE_MEMO_WndProc(TMessage& msg) {
    if (msg.Msg == WM_HSCROLL){
        int iPos;
        iPos = (int)(SBx_vRIRE_MEMO->HorzScrollBar->Position / Mem_vRIRE_MEMOORG->Width);
        SGr_vRIRE_SOZAI->LeftCol = iPos;
        SGr_vRIRE_SYUKA->LeftCol = iPos;
        if( SBx_vRIRE_MEMO->HorzScrollBar->Position != (iPos * (Mem_vRIRE_MEMOORG->Width + 1 )))
        	SBx_vRIRE_MEMO->HorzScrollBar->Position = iPos * (Mem_vRIRE_MEMOORG->Width + 1 );
    }
    SaveSBx_vRIRE_MEMO_WndProc(msg);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnTopLeftChange	�FTopRow �v���p�e�B�܂��� LeftCol �v���p�e�B���ύX���ꂽ����ɔ������܂��B
//
//  �@�\����
//    �f�ތ����i�����j�̃O���b�h���X�N���[�������Ƃ��ɍ������̃X�N���[���{�b�N�X��
//    ���킹�ăX�N���[�����܂�
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
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vRIRE_SOZAITopLeftChanged(TObject *Sender)
{
	//TRect Rectangle;
    int   i;
    int   iPos;


    // �X�N���[���o�[�̘A�g�ɂ���

    SGr_vSOKU_SOZAI->TopRow  = SGr_vRIRE_SOZAI->TopRow;
    SGr_vRIRE_SYUKA->LeftCol = SGr_vRIRE_SOZAI->LeftCol;
    SGr_tRIRE->LeftCol       = SGr_vRIRE_SOZAI->LeftCol;
    SGr_tRIRE_SOZAI->LeftCol = SGr_vRIRE_SOZAI->LeftCol;
    SGr_tRIRE_SYUKA->LeftCol = SGr_vRIRE_SOZAI->LeftCol;
	SBx_vRIRE_MEMO->HorzScrollBar->Position = SGr_vRIRE_SOZAI->LeftCol * (Mem_vRIRE_MEMOORG->Width + 1);
    iPos = 0;
    for( i=0; i<SGr_vRIRE_SOZAI->TopRow; i++){
    	iPos += (SGr_vRIRE_SOZAI->RowHeights[i] + 1);
    }
	SBx_Left_SOZAI->VertScrollBar->Position = iPos;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnTopLeftChange	�FTopRow �v���p�e�B�܂��� LeftCol �v���p�e�B���ύX���ꂽ����ɔ������܂��B
//
//  �@�\����
//    �f�ތ����i����j�̃O���b�h���X�N���[�������Ƃ��ɍ������̃X�N���[���{�b�N�X��
//    ���킹�ăX�N���[�����܂�
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
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vSOKU_SOZAITopLeftChanged(TObject *Sender)
{
    int   i;
    int   iPos;

    SGr_vRIRE_SOZAI->TopRow  = SGr_vSOKU_SOZAI->TopRow;  //�����Ɠ���ROW�ɂ���
    SGr_vSOKU_SYUKA->LeftCol = SGr_vSOKU_SOZAI->LeftCol;
    SGr_tSOKU->LeftCol       = SGr_vSOKU_SOZAI->LeftCol;
    SGr_tSOKU_SOZAI->LeftCol = SGr_vSOKU_SOZAI->LeftCol;
    SGr_tSOKU_SYUKA->LeftCol = SGr_vSOKU_SOZAI->LeftCol;
    SGr_tSOKU_SOZAI->LeftCol = SGr_vSOKU_SOZAI->LeftCol;
	SBx_vSOKU_MEMO->HorzScrollBar->Position = SGr_vSOKU_SOZAI->LeftCol * (Mem_vSOKU_MEMOORG->Width + 1);
    iPos = 0;
    for( i=0; i<SGr_vSOKU_SOZAI->TopRow; i++){
    	iPos += (SGr_vSOKU_SOZAI->RowHeights[i] + 1);
    }
	SBx_Left_SOZAI->VertScrollBar->Position = iPos;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnTopLeftChange	�FTopRow �v���p�e�B�܂��� LeftCol �v���p�e�B���ύX���ꂽ����ɔ������܂��B
//
//  �@�\����
//    �o�׌����i�����j�̃O���b�h���X�N���[�������Ƃ��ɍ������̃X�N���[���{�b�N�X��
//    ���킹�ăX�N���[�����܂�
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
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vRIRE_SYUKATopLeftChanged(TObject *Sender)
{
    int   i;
    int   iPos;

    SGr_vSOKU_SYUKA->TopRow  = SGr_vRIRE_SYUKA->TopRow;
    SGr_vRIRE_SOZAI->LeftCol = SGr_vRIRE_SYUKA->LeftCol;
    SGr_tRIRE->LeftCol       = SGr_vRIRE_SYUKA->LeftCol;
    SGr_tRIRE_SOZAI->LeftCol = SGr_vRIRE_SYUKA->LeftCol;
    SGr_tRIRE_SYUKA->LeftCol = SGr_vRIRE_SYUKA->LeftCol;
	SBx_vRIRE_MEMO->HorzScrollBar->Position = SGr_vRIRE_SYUKA->LeftCol * (Mem_vRIRE_MEMOORG->Width + 1);
    iPos = 0;
    for( i=0; i<SGr_vRIRE_SYUKA->TopRow; i++){
    	iPos += (SGr_vRIRE_SYUKA->RowHeights[i] + 1);
    }
	SBx_Left_SYUKA->VertScrollBar->Position = iPos;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnTopLeftChange	�FTopRow �v���p�e�B�܂��� LeftCol �v���p�e�B���ύX���ꂽ����ɔ������܂��B
//
//  �@�\����
//    �o�׌����i����j�̃O���b�h���X�N���[�������Ƃ��ɍ������̃X�N���[���{�b�N�X��
//    ���킹�ăX�N���[�����܂�
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
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vSOKU_SYUKATopLeftChanged(TObject *Sender)
{
    int   i;
    int   iPos;

    SGr_vRIRE_SYUKA->TopRow  = SGr_vSOKU_SYUKA->TopRow;
    SGr_vSOKU_SOZAI->LeftCol = SGr_vSOKU_SYUKA->LeftCol;          //Grid�\���J�n�ʒu�𑪒�o��Grid�Ɠ����ɂ���
    SGr_tSOKU->LeftCol       = SGr_vSOKU_SYUKA->LeftCol;          //Grid�\���J�n�ʒu�𑪒�o��Grid�Ɠ����ɂ���
    SGr_tSOKU_SOZAI->LeftCol = SGr_vSOKU_SYUKA->LeftCol;          //Grid�\���J�n�ʒu�𑪒�o��Grid�Ɠ����ɂ���
    SGr_tSOKU_SYUKA->LeftCol = SGr_vSOKU_SYUKA->LeftCol;          //Grid�\���J�n�ʒu�𑪒�o��Grid�Ɠ����ɂ���
	SBx_vSOKU_MEMO->HorzScrollBar->Position = SGr_vSOKU_SYUKA->LeftCol * (Mem_vSOKU_MEMOORG->Width + 1);
    iPos = 0;
    for( i=0; i<SGr_vSOKU_SYUKA->TopRow; i++){
    	iPos += (SGr_vSOKU_SYUKA->RowHeights[i] + 1);
    }
	SBx_Left_SYUKA->VertScrollBar->Position = iPos;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnCanResize       �F���[�U�[���X�v���b�^���}�E�X�ňړ����悤�Ƃ���Ɣ������܂��B
//
//  �@�\����
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
//---------------------------------------------------------------------------
void __fastcall TForm1::Splitter4CanResize(TObject *Sender, int &NewSize,
      bool &Accept)
{
          BtnF12->Tag = 0;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�FDrawCell��Z�[�u���Ɏg�p���郍�b�g���̔�����s���܂��B
//
//  �@�\����
//    ���b�g�̔��������������ɔ��f���܂��B
//    �|�P�F������A�O�F�n�j�A�P�F�m�f�A�Q�F�w������
//  �@�D��x�́@�����聄�m�f���n�j���w�������ł�
//
//  �p�����^����
//    TObject *Sender   �ΏۃZ��
//    int ACol          �ΏۃZ����Col�ʒu
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::GET_HANTEI(TObject *Sender, int ACol)
{
	int iGridTag;
    int iRow,iRowCount,i1;
    int iJudge,iDISP_JUDGE,iSOKU_JUDGE;
	AnsiString sBuf,sRESULT,sDISP_RESULT,sTEMP_RESULT;
	AnsiString sDECI;
	AnsiString sMAX,sMIN;
	bool bRtn;
	iGridTag = 0;
	iRowCount = 0;
	iJudge = 2;
	iRow = 0;
    sBuf ="";
                                                  
    //Sender���L�����𔻒f���܂�
 	if(Sender == SGr_vSOKU_SYUKA)
	{
        if(!hCELLINFO_SOKU_SYUKA) return;
 		iGridTag = 1;
        iRowCount = SGr_vSOKU_SYUKA->RowCount;
	}
 	if(Sender == SGr_vRIRE_SYUKA)
	{
        if(!hCELLINFO_RIRE_SYUKA) return;
 		iGridTag = 2;
       	iRowCount = SGr_vRIRE_SYUKA->RowCount;
	}
 	if(Sender == SGr_vSOKU_SOZAI)
	{
        if(!hCELLINFO_SOKU_SOZAI) return;
 		iGridTag = 3;
       	iRowCount = SGr_vSOKU_SOZAI->RowCount;
	}
 	if(Sender == SGr_vRIRE_SOZAI)
	{
        if(!hCELLINFO_RIRE_SYUKA) return;
    	iGridTag = 4;
       	iRowCount = SGr_vRIRE_SOZAI->RowCount;
	}
    //�I�����ꂽ�O���b�h�ɑ΂��Ĕ��菈�����s���܂��i�S�O���b�h�ɑ΂��ď����𕪂��Ă��܂����������e�͓����ł��j
	switch( iGridTag )
	{
    case 1:
		if(hCELLINFO_SOKU_SYUKA && hSOKU_KSD01_DATA)
		{
            //�����l�͑���w������
			iSOKU_JUDGE = 2;
			iDISP_JUDGE = 2;
            //0�s�ڂ͔���Ȃ̂�1�s�ڂ���l�𒲂ׂ�
			for( iRow = 1;iRow < iRowCount;iRow++)
			{
                if((AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].SOKU_FLG).ToIntDef(0) != 0 )
                //&& (AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].KOMK_NO).ToIntDef(0) != 0))
                && (pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].INS_ON != false))
                {
    				switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].VALUE_TYPE).ToIntDef(0))
	    			{
                    case 0:
			    	case 1:
   				    	sDECI = "0";
					    for(i1 = 0;i1 < AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].VALUE_DECI).ToIntDef(0);i1++)
    					{
                            if( sDECI.Length() == 1 ) sDECI += ".";
		    				sDECI +="0";
			    		}
				    	break;
                    default:
	    				break;
		    		}

    				switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].VALUE_TYPE).ToIntDef(0))
	    			{
		    		case 0:
                    case 1:
				    	sMAX = pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].MAX;
					    sMIN = pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].MIN;
                    	sRESULT = pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].RESULT;
	    				sTEMP_RESULT = sRESULT;
                    	bRtn = ConvDoubleDefS(sTEMP_RESULT,sDECI,sTEMP_RESULT,&sRESULT);
                        //�����ȓ��͖͂�������Ƃ��܂�
                        if(bRtn)
				    	{
					    	switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].KIKA_TYPE).ToIntDef(0))
                            {
    						case 1:
	    						switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].KIKA_KIND).ToIntDef(0))
                            	{
			    				case 1:
				    				if((sMIN.ToDouble() > sRESULT.ToDouble())
					    			|| (sMAX.ToDouble() < sRESULT.ToDouble()))
						    		{
							    		if(iSOKU_JUDGE != -1) iSOKU_JUDGE = 1;
								    }
                                    else if( iSOKU_JUDGE == 2 ) {
                                        iSOKU_JUDGE = 0;
                                    }
    								break;
	    						case 2:
		    						if( sRESULT.ToDouble() > sMAX.ToDouble())
			    					{
				    					if(iSOKU_JUDGE != -1) iSOKU_JUDGE = 1;
					    			}
                                    else if( iSOKU_JUDGE == 2 ) {
                                        iSOKU_JUDGE = 0;
                                    }
						    		break;
							    case 3:
								    if( sRESULT.ToDouble() < sMIN.ToDouble())
    								{
	    								if(iSOKU_JUDGE != -1) iSOKU_JUDGE = 1;
		    						}
                                    else if( iSOKU_JUDGE == 2 ) {
                                        iSOKU_JUDGE = 0;
                                    }
			    					break;
				    			}
                                break;
						    case 2:
    							if((sMIN.ToDouble() > sRESULT.ToDouble())
	    						|| (sMAX.ToDouble() < sRESULT.ToDouble()))
		    					{
			    					if(iSOKU_JUDGE != -1) iSOKU_JUDGE = 1;
				    			}
                                else if( iSOKU_JUDGE == 2 ) {
                                    iSOKU_JUDGE = 0;
                                }
                                break;
						    }
    					}
                        else
                        {
                            iSOKU_JUDGE = -1;           //�����������
                        }
                    	sDISP_RESULT = pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].DISP_RESULT;
	    				sTEMP_RESULT = sDISP_RESULT;
                    	bRtn = ConvDoubleDefS(sTEMP_RESULT,sDECI,sTEMP_RESULT,&sDISP_RESULT);
                        //�����ȓ��͖͂�������Ƃ��܂�
                        if(bRtn)
				    	{
					    	switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].KIKA_TYPE).ToIntDef(0))
                            {
    						case 1:
	    						switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].KIKA_KIND).ToIntDef(0))
                            	{
			    				case 1:
				    				if((sMIN.ToDouble() > sDISP_RESULT.ToDouble())
					    			|| (sMAX.ToDouble() < sDISP_RESULT.ToDouble()))
						    		{
							    		if(iDISP_JUDGE != -1) iDISP_JUDGE = 1;
								    }
                                    else if( iDISP_JUDGE == 2 ) {
                                        iDISP_JUDGE = 0;
                                    }
    								break;
	    						case 2:
		    						if( sDISP_RESULT.ToDouble() > sMAX.ToDouble())
			    					{
				    					if(iDISP_JUDGE != -1) iDISP_JUDGE = 1;
					    			}
                                    else if( iDISP_JUDGE == 2 ) {
                                        iDISP_JUDGE = 0;
                                    }
						    		break;
							    case 3:
								    if( sDISP_RESULT.ToDouble() < sMIN.ToDouble())
    								{
	    								if(iDISP_JUDGE != -1) iDISP_JUDGE = 1;
		    						}
                                    else if( iDISP_JUDGE == 2 ) {
                                        iDISP_JUDGE = 0;
                                    }
			    					break;
				    			}
                                break;
						    case 2:
							    if((sMIN.ToDouble() > sDISP_RESULT.ToDouble())
    							|| (sMAX.ToDouble() < sDISP_RESULT.ToDouble()))
	    						{
		    						if(iDISP_JUDGE != -1) iDISP_JUDGE = 1;
			    				}
                                else if( iDISP_JUDGE == 2 ) {
                                    iDISP_JUDGE = 0;
                                }
                                break;
					    	}
    					}
                        else
                        {
                            iDISP_JUDGE = -1;           //�����������
                        }
                        break;
		    		case 2: //�ǔ۔���ł�
                        if(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].RESULT).Trim().Length() != 0)
                        {
                    	    if((AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].RESULT).ToIntDef(0)) != 0)
				    	    {
					    	    if(iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
                            }
                            else if(iSOKU_JUDGE == 2 ){
                                iSOKU_JUDGE = 0;
                            }
    					}
                        else
                        {
                            iSOKU_JUDGE = -1;
                        }

                        if(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].DISP_RESULT).Trim().Length() != 0)
                        {
                    	    if((AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].DISP_RESULT).ToIntDef(0)) != 0)
				    	    {
					    	    if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
                            }
                            else if(iDISP_JUDGE == 2 ){
                                iDISP_JUDGE = 0;
                            }
    					}
                        else
                        {
                            iDISP_JUDGE = -1;
                        }
                        break;
                    case 3: //��������
                        if(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].RESULT).Trim().Length() ==0)
                        {
                            iSOKU_JUDGE = -1;
                        }
                        else if(iSOKU_JUDGE == 2 ){
                            iSOKU_JUDGE = 0;
                        }
                        if(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].DISP_RESULT).Trim().Length() ==0)
                        {
                            iDISP_JUDGE = -1;
                        }
                        else if(iDISP_JUDGE == 2 ){
                            iDISP_JUDGE = 0;
                        }
                        break;
    				default:
	    				break;
		    		}
                }
            }
            //���������������ɏ����܂�
            strcpy(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].SOKU_OK,AnsiString(iSOKU_JUDGE).c_str());
            strcpy(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].DISP_OK,AnsiString(iDISP_JUDGE).c_str());
            strcpy(pSOKU_KSD01_DATA[ACol].SYUKA_OK		,AnsiString(iSOKU_JUDGE).c_str());
        	strcpy(pSOKU_KSD01_DATA[ACol].SYUKA_OK_PRT	,AnsiString(iDISP_JUDGE).c_str());
		}
 		break;
    //�ȉ�Case�@2�A3�A4�̓Z���̈ʒu�ƑΏۂ̓���邪�Ⴄ�����ŏ������e�͓����ł�
    case 2:
        if(Form1->iRIRE_CNT == 0 ) return;
		if(hCELLINFO_RIRE_SYUKA && hRIRE_KSD01_DATA)
		{
			iSOKU_JUDGE = 2;
			iDISP_JUDGE = 2;
			for( iRow = 1;iRow < iRowCount;iRow++)		//0�s�ڂ͔���Ȃ̂�1����l�𒲂ׂ�
			{
                if((AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].SOKU_FLG).ToIntDef(0) != 0)
                //&& (AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].KOMK_NO).ToIntDef(0) != 0))
                && (pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].INS_ON != false))
                {
    				switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].VALUE_TYPE).ToIntDef(0))
	    			{
                    case 0:
			    	case 1:
   				    	sDECI = "0";
					    for(i1 = 0;i1 < AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].VALUE_DECI).ToIntDef(0);i1++)
    					{
                            if( sDECI.Length() == 1 ) sDECI += ".";
		    				sDECI +="0";
			    		}
				    	break;
                   default:
	    				break;
		    		}

    				switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].VALUE_TYPE).ToIntDef(0))
	    			{
		    		case 0:
                    case 1:
				    	sMAX = pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].MAX;
					    sMIN = pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].MIN;
                    	sRESULT = pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].RESULT;
	    				sTEMP_RESULT = sRESULT;
                    	bRtn = ConvDoubleDefS(sTEMP_RESULT,sDECI,sTEMP_RESULT,&sRESULT);
                        if(bRtn)
				    	{
					    	switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].KIKA_TYPE).ToIntDef(0))
                            {
    						case 1:
	    						switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].KIKA_KIND).ToIntDef(0))
                            	{
			    				case 1:
				    				if((sMIN.ToDouble() > sRESULT.ToDouble())
					    			|| (sMAX.ToDouble() < sRESULT.ToDouble()))
						    		{
							    		if(iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
								    }
                                    else if(iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
    								break;
	    						case 2:
		    						if( sRESULT.ToDouble() > sMAX.ToDouble())
			    					{
				    					if(iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
					    			}
                                    else if(iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
						    		break;
							    case 3:
    								if( sRESULT.ToDouble() < sMIN.ToDouble())
	    							{
		    							if(iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
			    					}
                                    else if(iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
				    				break;
					    		}
                                break;
    						case 2:
	    						if((sMIN.ToDouble() > sRESULT.ToDouble())
		    					|| (sMAX.ToDouble() < sRESULT.ToDouble()))
			    				{
				    				if(iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
					    		}
                                else if(iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
                                break;
    						}
	    				}
                        else
                        {
                            iSOKU_JUDGE = -1;
                        }
                    	sDISP_RESULT = pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].DISP_RESULT;
			    		sTEMP_RESULT = sDISP_RESULT;
                    	bRtn = ConvDoubleDefS(sTEMP_RESULT,sDECI,sTEMP_RESULT,&sDISP_RESULT);
                        if(bRtn)
    					{
	    					switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].KIKA_TYPE).ToIntDef(0))
                            {
			    			case 1:
				    			switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].KIKA_KIND).ToIntDef(0))
                            	{
						    	case 1:
							    	if((sMIN.ToDouble() > sDISP_RESULT.ToDouble())
								    || (sMAX.ToDouble() < sDISP_RESULT.ToDouble()))
    								{
	    								if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
		    						}
                                    else if(iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
			    					break;
				    			case 2:
					    			if( sDISP_RESULT.ToDouble() > sMAX.ToDouble())
						    		{
							    		if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
								    }
                                    else if(iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
    								break;
	    						case 3:
		    						if( sDISP_RESULT.ToDouble() < sMIN.ToDouble())
			    					{
				    					if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
					    			}
                                    else if(iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
						    		break;
							    }
                                break;
	    					case 2:
		    					if((sMIN.ToDouble() > sDISP_RESULT.ToDouble())
			    				|| (sMAX.ToDouble() < sDISP_RESULT.ToDouble()))
				    			{
					    			if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
						    	}
                                else if(iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
                                break;
    						}
                        }
                        else
                        {
                            iDISP_JUDGE = -1;
                        }
                        break;
			    	case 2:
                        if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].RESULT).Trim().Length() != 0)
                        {
                    	    if((AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].RESULT).ToIntDef(0)) != 0)
					        {
    						    if( iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
                            }
                            else if(iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
	    				}
                        else iSOKU_JUDGE = -1;

                        if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].DISP_RESULT).Trim().Length() != 0)
                        {
                    	    if((AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].DISP_RESULT).ToIntDef(0)) != 0)
			    		    {
				    		    if( iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
                            }
                            else if(iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
					    }
                        else iDISP_JUDGE = -1;
                        break;
                    case 3:                     //��������
                        if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].RESULT).Trim().Length() ==0)
                        {
                            iSOKU_JUDGE = -1;
                        }
                        if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].DISP_RESULT).Trim().Length() ==0)
                        {
                            iDISP_JUDGE = -1;
                        }
                        break;
	    			default:
		    			break;
			    	}
                }
			}
            strcpy(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].SOKU_OK,AnsiString(iSOKU_JUDGE).c_str());
            strcpy(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].DISP_OK,AnsiString(iDISP_JUDGE).c_str());
            strcpy(pRIRE_KSD01_DATA[ACol].SYUKA_OK		,AnsiString(iSOKU_JUDGE).c_str());
        	strcpy(pRIRE_KSD01_DATA[ACol].SYUKA_OK_PRT	,AnsiString(iDISP_JUDGE).c_str());
		}
 		break;
    case 3:
		if(hCELLINFO_SOKU_SOZAI && hSOKU_KSD01_DATA)
		{
			iSOKU_JUDGE = 2;
			iDISP_JUDGE = 2;
			for( iRow = 1;iRow < iRowCount;iRow++)		//0�s�ڂ͔���Ȃ̂�1����l�𒲂ׂ�
			{
                if((AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].SOKU_FLG).ToIntDef(0) != 0)
                //&& (AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].KOMK_NO).ToIntDef(0) != 0))
                && (pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].INS_ON != false))
                {
    				switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].VALUE_TYPE).ToIntDef(0))
	    			{
                    case 0:
			    	case 1:
   				    	sDECI = "0";
					    for(i1 = 0;i1 < AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].VALUE_DECI).ToIntDef(0);i1++)
    					{
                            if( sDECI.Length() == 1 ) sDECI += ".";
		    				sDECI +="0";
			    		}
				    	break;
                   default:
	    				break;
		    		}
    				switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].VALUE_TYPE).ToIntDef(0))
	    			{
		    		case 0:
                    case 1:
	    				sMAX = pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].MAX;
    	   				sMIN = pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].MIN;
                    	sRESULT = pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].RESULT;
	    				sTEMP_RESULT = sRESULT;
                    	bRtn = ConvDoubleDefS(sTEMP_RESULT,sDECI,sTEMP_RESULT,&sRESULT);
                        if(bRtn)
				    	{
					    	switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].KIKA_TYPE).ToIntDef(0))
                            {
    						case 1:
	    						switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].KIKA_KIND).ToIntDef(0))
                            	{
			    				case 1:
				    				if((sMIN.ToDouble() > sRESULT.ToDouble())
					    			|| (sMAX.ToDouble() < sRESULT.ToDouble()))
						    		{
							    		if(iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
								    }
                                    else if(iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
    								break;
	    						case 2:
		    						if( sRESULT.ToDouble() > sMAX.ToDouble())
			    					{
				    					if(iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
					    			}
                                    else if(iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
						    		break;
							    case 3:
    								if( sRESULT.ToDouble() < sMIN.ToDouble())
	    							{
		    							if(iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
			    					}
                                    else if(iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
				    				break;
					    		}
                                break;
    						case 2:
	    						if((sMIN.ToDouble() > sRESULT.ToDouble())
		    					|| (sMAX.ToDouble() < sRESULT.ToDouble()))
			    				{
				    				if(iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
					    		}
                                else if(iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
                                break;
    						}
	    				}
                        else
                        {
                            iSOKU_JUDGE = -1;
                        }
                    	sDISP_RESULT = pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].DISP_RESULT;
			    		sTEMP_RESULT = sDISP_RESULT;
                    	bRtn = ConvDoubleDefS(sTEMP_RESULT,sDECI,sTEMP_RESULT,&sDISP_RESULT);
                        if(bRtn)
    					{
	    					switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].KIKA_TYPE).ToIntDef(0))
                            {
			    			case 1:
				    			switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].KIKA_KIND).ToIntDef(0))
                            	{
						    	case 1:
							    	if((sMIN.ToDouble() > sDISP_RESULT.ToDouble())
								    || (sMAX.ToDouble() < sDISP_RESULT.ToDouble()))
    								{
	    								if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
		    						}
                                    else if( iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
			    					break;
				    			case 2:
					    			if( sDISP_RESULT.ToDouble() > sMAX.ToDouble())
						    		{
							    		if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
								    }
                                    else if( iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
    								break;
	    						case 3:
		    						if( sDISP_RESULT.ToDouble() < sMIN.ToDouble())
			    					{
				    					if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
					    			}
                                    else if( iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
						    		break;
							    }
                                break;
	    					case 2:
		    					if((sMIN.ToDouble() > sDISP_RESULT.ToDouble())
			    				|| (sMAX.ToDouble() < sDISP_RESULT.ToDouble()))
				    			{
					    			if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
						    	}
                                else if( iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
                                break;
    						}
	    				}
                        else
                        {
                            iDISP_JUDGE = -1;
                        }
                        break;
			    	case 2:
                        if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].RESULT).Trim().Length() != 0)
                        {
                    	    if((AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].RESULT).ToIntDef(0)) != 0)
					        {
    						    if(iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
	    				    }else if( iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
                        }
                        else
                        {
                            iSOKU_JUDGE = -1;
                        }

                    	if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].DISP_RESULT).Trim().Length() != 0)
                        {
                    	    if((AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].DISP_RESULT).ToIntDef(0)) != 0)
			    		    {
				    		    if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
                            } else if( iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;

					    }
                        else
                        {
                            iDISP_JUDGE = -1;
                        }
                        break;
                    case 3:                     //��������
                        if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].RESULT).Trim().Length() ==0)
                        {
                            iSOKU_JUDGE = -1;
                        }
                        if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].DISP_RESULT).Trim().Length() ==0)
                        {
                            iDISP_JUDGE = -1;
                        }
                        break;
	    			default:
		    			break;
			    	}
                }
			}
            strcpy(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].SOKU_OK,AnsiString(iSOKU_JUDGE).c_str());
            strcpy(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].DISP_OK,AnsiString(iDISP_JUDGE).c_str());
            strcpy(pSOKU_KSD01_DATA[ACol].SOZAI_OK		,AnsiString(iSOKU_JUDGE).c_str());
        	strcpy(pSOKU_KSD01_DATA[ACol].SOZAI_OK_PRT	,AnsiString(iDISP_JUDGE).c_str());
		}
 		break;
    case 4:
        if(Form1->iRIRE_CNT == 0 ) return;
		if(hCELLINFO_RIRE_SOZAI && hRIRE_KSD01_DATA)
		{
			iSOKU_JUDGE = 2;
			iDISP_JUDGE = 2;
			for( iRow = 1;iRow < iRowCount;iRow++)		//0�s�ڂ͔���Ȃ̂�1����l�𒲂ׂ�
			{
                if((AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].SOKU_FLG).ToIntDef(0)!= 0)
                //&& (AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].KOMK_NO).ToIntDef(0)!= 0))
                && (pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].INS_ON != false))
                {
    				switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].VALUE_TYPE).ToIntDef(0))
	    			{
                    case 0:
			    	case 1:
   				    	sDECI = "0";
					    for(i1 = 0;i1 < AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].VALUE_DECI).ToIntDef(0);i1++)
    					{
                            if( sDECI.Length() == 1 ) sDECI += ".";
		    				sDECI +="0";
			    		}
				    	break;
                   default:
	    				break;
		    		}
    				switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].VALUE_TYPE).ToIntDef(0))
	    			{
		    		case 0:
                    case 1:
				    	sMAX = pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].MAX;
					    sMIN = pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].MIN;
                    	sRESULT = pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].RESULT;
	    				sTEMP_RESULT = sRESULT;
                    	bRtn = ConvDoubleDefS(sTEMP_RESULT,sDECI,sTEMP_RESULT,&sRESULT);
                        if(bRtn)
				    	{
					    	switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].KIKA_TYPE).ToIntDef(0))
                            {
    						case 1:
	    						switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].KIKA_KIND).ToIntDef(0))
                            	{
			    				case 1:
				    				if((sMIN.ToDouble() > sRESULT.ToDouble())
					    			|| (sMAX.ToDouble() < sRESULT.ToDouble()))
						    		{
							    		if( iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
								    }
                                    else if ( iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
    								break;
	    						case 2:
		    						if( sRESULT.ToDouble() > sMAX.ToDouble())
			    					{
				    					if( iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
					    			}
                                    else if ( iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
						    		break;
							    case 3:
    								if( sRESULT.ToDouble() < sMIN.ToDouble())
	    							{
		    							if( iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
			    					}
                                    else if ( iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
				    				break;
					    		}
                                break;
    						case 2:
	    						if((sMIN.ToDouble() > sRESULT.ToDouble())
		    					|| (sMAX.ToDouble() < sRESULT.ToDouble()))
			    				{
				    				if( iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
					    		}
                                else if( iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
                                break;
    						}
	    				}
                        else
                        {
                            iSOKU_JUDGE = -1;
                        }
                    	sDISP_RESULT = pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].DISP_RESULT;
			    		sTEMP_RESULT = sDISP_RESULT;
                    	bRtn = ConvDoubleDefS(sTEMP_RESULT,sDECI,sTEMP_RESULT,&sDISP_RESULT);
                        if(bRtn)
    					{
	    					switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].KIKA_TYPE).ToIntDef(0))
                            {
			    			case 1:
				    			switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].KIKA_KIND).ToIntDef(0))
                            	{
						    	case 1:
							    	if((sMIN.ToDouble() > sDISP_RESULT.ToDouble())
								    || (sMAX.ToDouble() < sDISP_RESULT.ToDouble()))
    								{
	    								if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
		    						} else if(iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
			    					break;
				    			case 2:
					    			if( sDISP_RESULT.ToDouble() > sMAX.ToDouble())
						    		{
							    		if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
								    } else if(iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
    								break;
	    						case 3:
		    						if( sDISP_RESULT.ToDouble() < sMIN.ToDouble())
			    					{
				    					if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
					    			} else if(iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
						    		break;
							    }
                                break;
	    					case 2:
		    					if((sMIN.ToDouble() > sDISP_RESULT.ToDouble())
			    				|| (sMAX.ToDouble() < sDISP_RESULT.ToDouble()))
				    			{
					    			if(iDISP_JUDGE != -1) iDISP_JUDGE = 1;
						    	} else if(iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
                                break;
    						}
	    				}
                        else
                        {
                            iDISP_JUDGE = -1;
                        }
                        break;
			    	case 2:
                    	if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].RESULT).Trim().Length() != 0)
                        {
                    	    if((AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].RESULT).ToIntDef(0)) != 0)
					        {
						        if( iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
    					    }
                            else
                            {
                                if( iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
                            }
                        }
                        else
                        {
                            iSOKU_JUDGE = -1;
                        }
                    	if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].DISP_RESULT).Trim().Length() != 0)
                        {
                    	    if((AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].DISP_RESULT).ToIntDef(0)) != 0)
		    			    {
			    			    if( iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
                            }
                            else
                            {
                                if( iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
                            }
				    	}
                        else
                        {
                            iDISP_JUDGE = -1;
                        }
                        break;
                    case 3:                     //��������
                        if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].RESULT).Trim().Length() ==0)
                        {
                            iSOKU_JUDGE = -1;
                        }
                        if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].DISP_RESULT).Trim().Length() ==0)
                        {
                            iDISP_JUDGE = -1;
                        }
                        break;
    				default:
	    				break;
		    		}
                }
			}
            strcpy(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].SOKU_OK,AnsiString(iSOKU_JUDGE).c_str());
            strcpy(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].DISP_OK,AnsiString(iDISP_JUDGE).c_str());
            strcpy(pRIRE_KSD01_DATA[ACol].SOZAI_OK		,AnsiString(iSOKU_JUDGE).c_str());
        	strcpy(pRIRE_KSD01_DATA[ACol].SOZAI_OK_PRT	,AnsiString(iDISP_JUDGE).c_str());
		}
 		break;
	default:
		break;
	}
    //���ʂ���ʏ�ɔ��f���܂�
    if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD)
	{
		iJudge = iSOKU_JUDGE;
	}
    else
	{
		iJudge = iDISP_JUDGE;
	}
	switch( iJudge )
	{
    case -1:
        sBuf = "���蒆";
        break;
    case 0:
		sBuf = "OK";
		break;
	case 1:
		sBuf = "NG";
		break;
	case 2:
    default:
		sBuf = "";
		break;
	}
	bHANTEI_DISP = true;
	switch( iGridTag )
	{
    case 1:
		pCELLINFO_SOKU_SYUKA[ACol*iRowCount+0].JUDGE        = iSOKU_JUDGE;
		pCELLINFO_SOKU_SYUKA[ACol*iRowCount+0].DISP_JUDGE   = iDISP_JUDGE;
		SGr_vSOKU_SYUKA->Cells[ACol][0] = sBuf;
		break;
    case 2:
		pCELLINFO_RIRE_SYUKA[ACol*iRowCount+0].JUDGE        = iSOKU_JUDGE;
		pCELLINFO_RIRE_SYUKA[ACol*iRowCount+0].DISP_JUDGE   = iDISP_JUDGE;
		SGr_vRIRE_SYUKA->Cells[ACol][0] = sBuf;
		break;
    case 3:
		pCELLINFO_SOKU_SOZAI[ACol*iRowCount+0].JUDGE        = iSOKU_JUDGE;
		pCELLINFO_SOKU_SOZAI[ACol*iRowCount+0].DISP_JUDGE   = iDISP_JUDGE;
		SGr_vSOKU_SOZAI->Cells[ACol][0] = sBuf;
		break;
    case 4:
		pCELLINFO_RIRE_SOZAI[ACol*iRowCount+0].JUDGE        = iSOKU_JUDGE;
		pCELLINFO_RIRE_SOZAI[ACol*iRowCount+0].DISP_JUDGE   = iDISP_JUDGE;
		SGr_vRIRE_SOZAI->Cells[ACol][0] = sBuf;
		break;
    }
	bHANTEI_DISP = false;
}
//---------------------------------------------------------------------------
//
//  �T�v
//    OnDrawCell�C�x���g	�F�S�����O���b�h�̕`�揈�����s���܂��B
//
//  �@�\����
//    �\������Z�����w�����ꂽ�����A�`���ŕ\�����A�G���[���̔��f��F��ς��ĕ\�����܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol          �F�ΏۃZ���̃J�����ʒu
//    int ARow          �F�ΏۃZ���̂q�n�v�ʒu
//  �@TRect &Rect       �F�Z���̈ʒu���
//  �@TGridDrawState State  : �Z���̃X�e�[�^�X�i�t�H�[�J�X�̗L�����j
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �S�̃O���b�h�ɏ����͕�����Ă��܂����A�Q�ƃ������̈ʒu�Ȃǂ��Ⴄ�����œ��e�͓����ł��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::AllGRID_DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
	if(iDEBUG == 1) return;
	AnsiString asString,sBuf,sBuf2;
	RECT r=RECT(Rect);
	int i1;
	int iGridTag;
	AnsiString	sDeci1,sDeci2;
	double dMAX,dMIN;
	AnsiString sTemp;
	int iKIKA_KIND;			//1�F�㉺������A2�F�ȉ��A3�F�ȏ�
	bool bRtn;	 			//2003.05.08 E.Takase Add
	double dBuf;	 		//2003.05.08 E.Takase Add
	AnsiString sComp1,sComp2,sTempComp;	//�\���l�ƈ���l���r����o�b�t�@

    //�����������邩�𔻒f���܂�
	if(Sender == SGr_vSOKU_SYUKA)
	{
		iGridTag = 1;
		asString = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
		SGr_vSOKU_SYUKA->Canvas->Font->Size = 12;
		if(!hCELLINFO_SOKU_SYUKA) return;
	}
	if(Sender == SGr_vRIRE_SYUKA)
	{
		iGridTag = 2;
		asString = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
		SGr_vRIRE_SYUKA->Canvas->Font->Size = 12;
		if(!hCELLINFO_RIRE_SYUKA) return;
	}
	if(Sender == SGr_vSOKU_SOZAI)
	{
		iGridTag = 3;
		asString = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
		SGr_vSOKU_SOZAI->Canvas->Font->Size = 12;
		if(!hCELLINFO_SOKU_SOZAI) return;
	}
	if(Sender == SGr_vRIRE_SOZAI)
	{
		iGridTag = 4;
		asString = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
		SGr_vRIRE_SOZAI->Canvas->Font->Size = 12;
		if(!hCELLINFO_RIRE_SOZAI) return;
	}
	//�Œ�Z���̔w�i�F���Z�b�g
	if(State.Contains(gdFixed))
	{
	}
	else if(asString == "�s�v")
	{
		switch( iGridTag )
		{
		case 1:
			SGr_vSOKU_SYUKA->Canvas->Brush->Color= clGray;
			break;
		case 2:
			SGr_vRIRE_SYUKA->Canvas->Brush->Color= clGray;
			break;
		case 3:
			SGr_vSOKU_SOZAI->Canvas->Brush->Color= clGray;
			break;
		case 4:
			SGr_vRIRE_SOZAI->Canvas->Brush->Color= clGray;
			break;
		default:
			break;
		}
	}
	//�t�H�[�J�X�̂���Z���̔w�i�F���Z�b�g
	else if(State.Contains(gdFocused))
	{
		switch( iGridTag )
		{
		case 1:
			SGr_vSOKU_SYUKA->Canvas->Brush->Color= clHighlight;
			break;
		case 2:
			SGr_vRIRE_SYUKA->Canvas->Brush->Color= clHighlight;
			break;
		case 3:
			SGr_vSOKU_SOZAI->Canvas->Brush->Color= clHighlight;
			break;
		case 4:
			SGr_vRIRE_SOZAI->Canvas->Brush->Color= clHighlight;
			break;
		default:
			break;
		}
	}
	//���ʂ̃Z���̔w�i�F���Z�b�g
	else
	{
		switch( iGridTag )
		{
		case 1:
			SGr_vSOKU_SYUKA->Canvas->Brush->Color= SGr_vSOKU_SYUKA->Color;
			break;
		case 2:
			SGr_vRIRE_SYUKA->Canvas->Brush->Color= SGr_vRIRE_SYUKA->Color;
			break;
		case 3:
			SGr_vSOKU_SOZAI->Canvas->Brush->Color= SGr_vSOKU_SOZAI->Color;
			break;
		case 4:
			SGr_vRIRE_SOZAI->Canvas->Brush->Color= SGr_vRIRE_SOZAI->Color;
			break;
		default:
			break;
		}
	}
    if( ARow == 0 )
    {
    // �P�s�ڂ́A�u����v
        switch( iGridTag )
        {
        case 1:
            SGr_vSOKU_SYUKA->Canvas->Brush->Color= (TColor)0x00FFDCB9;
            break;
        case 2:
            SGr_vRIRE_SYUKA->Canvas->Brush->Color= (TColor)0x00FFDCB9;
            break;
        case 3:
            SGr_vSOKU_SOZAI->Canvas->Brush->Color= (TColor)0x0080FFFF;
            break;
        case 4:
            SGr_vRIRE_SOZAI->Canvas->Brush->Color= (TColor)0x0080FFFF;
            break;
        default:
            break;
        }
        switch( iGridTag )
        {
        case 1:
            if(asString == "NG" )
            {
                SGr_vSOKU_SYUKA->Canvas->Font->Color = clRed;
            }
            else
            {
                SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;
            }
            SGr_vSOKU_SYUKA->Canvas->FillRect(Rect);
            sBuf = asString;
            InflateRect(&r,-2,-2);
            DrawText(SGr_vSOKU_SYUKA->Canvas->Handle,sBuf.c_str(),-1,&r,DT_CENTER); //�����H
            break;
        case 2:
            if(asString == "NG" )
            {
                SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
            }
            else
            {
                SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
            }
            SGr_vRIRE_SYUKA->Canvas->FillRect(Rect);
            sBuf = asString;
            InflateRect(&r,-2,-2);
            DrawText(SGr_vRIRE_SYUKA->Canvas->Handle,sBuf.c_str(),-1,&r,DT_CENTER); //�����H
            break;
        case 3:
            if(asString == "NG" )
            {
                SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
            }
            else
            {
                SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
            }
            SGr_vSOKU_SOZAI->Canvas->FillRect(Rect);
            sBuf = asString;
            InflateRect(&r,-2,-2);
            DrawText(SGr_vSOKU_SOZAI->Canvas->Handle,sBuf.c_str(),-1,&r,DT_CENTER); //�����H
            break;
        case 4:
            if(asString == "NG" )
            {
                SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
            }
            else
            {
                SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
            }
            SGr_vRIRE_SOZAI->Canvas->FillRect(Rect);
            sBuf = asString;
            InflateRect(&r,-2,-2);
            DrawText(SGr_vRIRE_SOZAI->Canvas->Handle,sBuf.c_str(),-1,&r,DT_CENTER); //�����H
            break;
        default:
            break;
        }
        return;
    }
/////////////////////////////////////////////////////////////////////
//�ȉ��͑��荀�ڂ̕\���ɂ��ẴR�[�h�ł�
	switch( iGridTag )
	{
	case 1:
	//�z�񂪎��Ă��Ȃ��̂ŕ`��𒆎~���܂�
		if(!hCELLINFO_SOKU_SYUKA) return;
		break;
	case 2:
	//�z�񂪎��Ă��Ȃ��̂ŕ`��𒆎~���܂�
		if(!hCELLINFO_RIRE_SYUKA) return;
		break;
	case 3:
	//�z�񂪎��Ă��Ȃ��̂ŕ`��𒆎~���܂�
		if(!hCELLINFO_SOKU_SOZAI) return;
		break;
	case 4:
	//�z�񂪎��Ă��Ȃ��̂ŕ`��𒆎~���܂�
		if(!hCELLINFO_RIRE_SOZAI) return;
		break;
	}
	//���t�̕\�����s���܂�
    //�����ʂ��𒲂ׂ܂�
	if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD)
	{
        //�����ʂȂ̂ő����ʂ̑������\�����܂�
		switch( iGridTag )
		{
		case 1:
			if(!hSOKU_KSD01_DATA) break;
			sBuf 	= AnsiString(pSOKU_KSD01_DATA[ACol].SKTYMD);
			SGr_tSOKU_SYUKA->Cells[ACol][0] = sBuf;
			break;
		case 2:
			if(!hRIRE_KSD01_DATA) break;
			if(Form1->iRIRE_CNT == 0) break;                      
			//**** 2003/05/15�@���������₵���u�������ǂݍ��݃G���[�v���܂ɔ���
			sBuf	= AnsiString(pRIRE_KSD01_DATA[ACol].SKTYMD);
			SGr_tRIRE_SYUKA->Cells[ACol][0] = sBuf;
			break;
		case 3:

			if(!hSOKU_KSD01_DATA) break;
			sBuf	= AnsiString(pSOKU_KSD01_DATA[ACol].SKTYMD_SZ);
			SGr_tSOKU_SOZAI->Cells[ACol][0] = sBuf;
			break;
		case 4:
			//if(!hRIRE_KSD01_DATA) break;
			if(Form1->iRIRE_CNT == 0) break;
			sBuf	= AnsiString(pRIRE_KSD01_DATA[ACol].SKTYMD_SZ);
			SGr_tRIRE_SOZAI->Cells[ACol][0] = sBuf;
			break;
		}
	}
	else
	{
        //����ҏW��ʂȂ̂ň���p�̑������\�����܂�
		switch( iGridTag )
		{
		case 1:
			if(!hSOKU_KSD01_DATA) break;
			sBuf 	= AnsiString(pSOKU_KSD01_DATA[ACol].SKTYMD_PRT);
			SGr_tSOKU_SYUKA->Cells[ACol][0] = sBuf;
			break;
		case 2:
			if(!hRIRE_KSD01_DATA) break;
			sBuf	= AnsiString(pRIRE_KSD01_DATA[ACol].SKTYMD_PRT);
			SGr_tRIRE_SYUKA->Cells[ACol][0] = sBuf;
			break;
		case 3:
			if(!hSOKU_KSD01_DATA) break;
			sBuf	= AnsiString(pSOKU_KSD01_DATA[ACol].SKTYMD_SZ_PRT);
			SGr_tSOKU_SOZAI->Cells[ACol][0] = sBuf;
			break;
		case 4:
			if(!hRIRE_KSD01_DATA) break;
			sBuf	= AnsiString(pRIRE_KSD01_DATA[ACol].SKTYMD_SZ_PRT);
			SGr_tRIRE_SOZAI->Cells[ACol][0] = sBuf;
			break;
		}
	}

	switch( iGridTag )
	{
	//�o�ב�����
	case 1:
		if(!hCELLINFO_SOKU_SYUKA) return;
		// 2003/06/02 K.Yamada �ΏۃZ�����������́A�����𒆎~���܂�
		if( SGr_vSOKU_SYUKA->RowCount == 1 ) return;
	//�w�i�F�ŏ���
		SGr_vSOKU_SYUKA->Canvas->FillRect(Rect);
	//�Œ�Z���̗��̘g��`��
		if(SGr_vSOKU_SYUKA->Ctl3D&&State.Contains(gdFixed))
		{
			DrawEdge(SGr_vSOKU_SYUKA->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);
		}
	//�t�H�[�J�X�̂���Z���̕����F���Z�b�g
		if(State.Contains(gdFocused))
		{
			SGr_vSOKU_SYUKA->Canvas->Font->Color= clHighlightText;
			SGr_vSOKU_SYUKA->Canvas->Font->Color= clBlack;
		}
	//�I������Ă���Z���̕����F���Z�b�g
		else if(State.Contains(gdSelected))
		{
	//���ʂ̃Z���̕����F���Z�b�g
		}
		else
		{
			SGr_vSOKU_SYUKA->Canvas->Font->Color= SGr_vSOKU_SYUKA->Font->Color;
		}
		if(asString == "�s�v")
		{
			SGr_vSOKU_SYUKA->Canvas->Font->Color= clGray;
		}
		else
		{
			SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;
		}

		if(Form1->SGr_tSOKU->Cells[0][0]!="" && hCELLINFO_SOKU_SYUKA != NULL)
		{
            //�\������Ă����ʁi����^����p��ʁj�ɂ����͒l��������������o��
			if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
				sBuf = pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount + ARow].RESULT;
			}
			sBuf = pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount + ARow].DISP_RESULT;
			if( hCELLINFO_SOKU_SYUKA )
			{
            //���͂����l�̏ꍇ�A�K�i���Z�o����
				if((AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 1)
				|| (AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 2))
				{
					dMAX = pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].MAX;
					dMIN = pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].MIN;
				}
			}
		}
	//�ȏ�ȉ��̋K�i�̏ꍇ�΍�
		iKIKA_KIND = 1;		//�f�t�H���g�͏㉺���Ŕ���
		if(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].KIKA_TYPE) == 1)
		{
			if(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].KIKA_KIND) == 2)
			{
				iKIKA_KIND = 2;
			}
			else if(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].KIKA_KIND) == 3)
			{
				iKIKA_KIND = 3;
			}
		}

//�t�H�[�}�b�g����
		if(hCELLINFO_SOKU_SYUKA )
		{
            //�����񂪕s�v�Ȃ�̏����ł������͏������̂��̂��s�v�ł��i�s�v������Ō��Ȃ��Ȃ����ׁj
			if(asString == "�s�v"
			|| AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].RESULT) == "�s�v")
			{
				sBuf = "�s�v";
				//�Z�����͂��o�b�t�@�Ɏ�荞��
				strcpy(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].RESULT		,sBuf.c_str());
				strcpy(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].DISP_RESULT,sBuf.c_str());
				pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].JUDGE = 2;
			}
			else
			{
                //�����A�����A�p�x�̏ꍇ�̓t�H�[�}�b�g��������쐬���܂�
				switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:		//�����E����
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_SOKU_SYUKA[(ACol*SGr_vSOKU_SYUKA->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( sDeci1.Length() == 1 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 1:		//�p�x
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_SOKU_SYUKA[(ACol*SGr_vSOKU_SYUKA->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( sDeci1.Length() == 1 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 2:  	//�ǁE��
					break;
				default:	//����
					break;
				}
				SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;		//����p�F�����l��OK��
				switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:
                    //���͂��Ȃ���΃o�b�t�@����ɂ��܂�
					if(AnsiString(SGr_vSOKU_SYUKA->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}
                    //��������̔��莮���g���������͂ł��G���[���o���Ȃ��悤�ɂ��܂��B
					//2003.05.08 E.Takase Add��
					bRtn = ConvDoubleDefS(SGr_vSOKU_SYUKA->Cells[ACol][ARow],sDeci1,SGr_vSOKU_SYUKA->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add��
					//2003.05.08 E.Takase Add �R�����g��
					//try{
					//	sBuf = FormatFloat(sDeci1,SGr_vSOKU_SYUKA->Cells[ACol][ARow].ToDouble());
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
					//}
					//catch(...){
					//	sBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
					//}
					//2003.05.08 E.Takase Add �R�����g��

					//�Z�����͂��o�b�t�@�Ɏ�荞��
					if(hCELLINFO_SOKU_SYUKA)
					{
						//����p��ʈȊO
						if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_SOKU_SYUKA[ACol*Form1->SGr_vSOKU_SYUKA->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
					//�ǔ۔���
					//2003.05.08 E.Takase Add��
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
                        //�ȉ�����
						case 2:
							if( dBuf <= dMAX  )
							{
								SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vSOKU_SYUKA->Canvas->Font->Color = clRed;
							}
							break;
                        //�ȏ㔻��
						case 3:
							if( dBuf >= dMIN )
							{
								SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vSOKU_SYUKA->Canvas->Font->Color = clRed;
							}
							break;
                        //�͈͔���
						default:
                            /*
							if( ((float)dMAX >= (float)dBuf) &&
                            	((float)dBuf >= (float)dMIN) ) {
								SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;
							}
							else {
								SGr_vSOKU_SYUKA->Canvas->Font->Color = clRed;
							}
                            */
                            // 2003/10/06 A.Tamura �Ȃ����K�i���Ȃ̂ɋK�i�O�Ɣ��肳���̂�Double�^���Đݒ肵�܂��B
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();
                            if( dBuf <= dMAX && dBuf >= dMIN ){
                            	SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;
                            }
                            else {
                                SGr_vSOKU_SYUKA->Canvas->Font->Color = clRed;
                            }

						}

					} else {
						sBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
					}
					//2003.05.08 E.Takase Add��
					break;
				case 1:
					if(AnsiString(SGr_vSOKU_SYUKA->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}
					//2003.05.08 E.Takase Add��
					bRtn = ConvDoubleDefS(SGr_vSOKU_SYUKA->Cells[ACol][ARow],sDeci1,SGr_vSOKU_SYUKA->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add��
					//2003.05.08 E.Takase Add �R�����g��
					//try{
					//	sBuf = FormatFloat(sDeci1,SGr_vSOKU_SYUKA->Cells[ACol][ARow].ToDouble());
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
					//}
					//catch(...){
					//	sBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
					//}
					//2003.05.08 E.Takase Add �R�����g��

					//�ǔ۔���
					//2003.05.08 E.Takase Add��
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
                        //�ȉ�����
						case 2:
							if( dBuf <= dMAX )
							{
								SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vSOKU_SYUKA->Canvas->Font->Color = clRed;
							}
							break;
                        //�ȏ㔻��
						case 3:
							if( dBuf >= dMIN )
							{
								SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vSOKU_SYUKA->Canvas->Font->Color = clRed;
							}
							break;
                        //�͈͔���
						default:
                            // 2003/10/06 A.Tamura �Ȃ����K�i���Ȃ̂ɋK�i�O�Ɣ��肳���̂�Double�^���Đݒ肵�܂��B
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN)
							{
								SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vSOKU_SYUKA->Canvas->Font->Color = clRed;
							}
						}
					} else {
						if(hCELLINFO_SOKU_SYUKA)
						{
							sBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_SOKU_SYUKA[ACol*Form1->SGr_vSOKU_SYUKA->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
					//2003.05.08 E.Takase Add��

					//�Z�����͂��o�b�t�@�Ɏ�荞��
					if(hCELLINFO_SOKU_SYUKA)
					{
						//����p��ʂňȊO
						if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_SOKU_SYUKA[ACol*Form1->SGr_vSOKU_SYUKA->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
					if(sBuf.Trim().Length() != 0)
					{
						i1 = strcspn(sBuf.c_str(),".");
						sTemp = sBuf.SubString(1,i1);
						sTemp += "��";
						if(sBuf.SubString(i1+2,sBuf.Length() - i1).Length()!=0)
						{
							sTemp += sBuf.SubString(i1+2,sBuf.Length() - i1);
							sTemp += "'";
						}
						sBuf = sTemp;
					}
					break;
				case 2:
                    //�ǔ۔���
					sBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
					sBuf = sBuf.Trim();
					if( sBuf == 0 || sBuf == "��")
					{
						sBuf ="��";
					}
					else if( sBuf.Length() != 0)
					{
						sBuf = "��";
					}
                    //����p��ʈȊO
                    if(SGr_vSOKU_SYUKA->Color != 0x00DDDDDD){
                        sBuf = sBuf.SubString(1,14);
                        if( sBuf.Length() == 14 ){
                            if ( sBuf.ByteType( 14 ) == mbLeadByte ){
                                sBuf = sBuf.SubString(1,13);
                            }
                        }
					    if( sBuf == 0 || sBuf == "��")
					    {
                            strcpy(pCELLINFO_SOKU_SYUKA[ACol*Form1->SGr_vSOKU_SYUKA->RowCount+ARow].RESULT,"0");
                        }
                        else if( sBuf.Length() != 0 )
					    {
                            strcpy(pCELLINFO_SOKU_SYUKA[ACol*Form1->SGr_vSOKU_SYUKA->RowCount+ARow].RESULT,"1");
                        }
                        else
                        {
                            strcpy(pCELLINFO_SOKU_SYUKA[ACol*Form1->SGr_vSOKU_SYUKA->RowCount+ARow].RESULT,"");
                        }
                    }
					if( sBuf == "��" )
					{
						SGr_vSOKU_SYUKA->Canvas->Font->Color = clRed;
					}
					else
					{
						SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;
					}
					break;
				default:
                    //�����񔻒�
					sBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
					SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;
					//�Z�����͂��o�b�t�@�Ɏ�荞��
					if(hCELLINFO_SOKU_SYUKA)
					{
						//����p��ʂłȂ����
						if(SGr_vSOKU_SYUKA->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_SOKU_SYUKA[ACol*Form1->SGr_vSOKU_SYUKA->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
				}
			}
		}
		else
		{
			sBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
		}
    //�I�𒆂̓n�C���C�g�\��
   		if(State.Contains(gdFocused)
		&& SGr_vSOKU_SYUKA->Canvas->Font->Color != clRed
		&& SGr_vSOKU_SYUKA->Canvas->Font->Color != clGray)
		{
			SGr_vSOKU_SYUKA->Canvas->Font->Color= clHighlightText;
   		}
    //����ҏW��ʂ̓J���[��ύX����
		if(SGr_vSOKU_SYUKA->Color == 0x00DDDDDD)
		{
            //�\������ۂ̃J���[��ݒ肵�܂�
            //����p�J���[
            //�m�f�FclRed�A�n�j�FclBlack
            //����p�J���[
            //����p�ƈ���p�̒l�������ꍇ�F  �m�f�FclRed�A�n�j�FclBlack
            //����p�ƈ���p�̒l���Ⴄ�ꍇ�F�@�m�f�FclMaroon�A�n�j�FclBlue
			switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*Form1->SGr_vSOKU_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
			{
			case 0:
			case 1:
			case 2:
				try{
				sComp1 = AnsiString(pCELLINFO_SOKU_SYUKA[ACol*Form1->SGr_vSOKU_SYUKA->RowCount+ARow].RESULT);
				sComp2 = AnsiString(pCELLINFO_SOKU_SYUKA[ACol*Form1->SGr_vSOKU_SYUKA->RowCount+ARow].DISP_RESULT);
				sTempComp = sComp1;
				bRtn = ConvDoubleDefS(sTempComp,sDeci1,sTempComp,&sComp1);
				sTempComp = sComp2;
				bRtn = ConvDoubleDefS(sTempComp,sDeci1,sTempComp,&sComp2);
				if( sComp1 != sComp2)
				{
					if(SGr_vSOKU_SYUKA->Canvas->Font->Color == clRed)
					{
						SGr_vSOKU_SYUKA->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vSOKU_SYUKA->Canvas->Font->Color= clBlue;
					}
				}
				else
				{
					if(SGr_vSOKU_SYUKA->Canvas->Font->Color == clRed)
					{
 						SGr_vSOKU_SYUKA->Canvas->Font->Color= clRed;
					}
					else
					{
						SGr_vSOKU_SYUKA->Canvas->Font->Color= clGray;
					}
				}
				}
				catch(EConvertError& e){
					if(SGr_vSOKU_SYUKA->Canvas->Font->Color == clRed)
					{
						SGr_vSOKU_SYUKA->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vSOKU_SYUKA->Canvas->Font->Color= clBlue;
					}
				}
				catch(...){
					if(SGr_vSOKU_SYUKA->Canvas->Font->Color == clRed)
					{
						SGr_vSOKU_SYUKA->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vSOKU_SYUKA->Canvas->Font->Color= clBlue;
					}
				}
				break;
			default:
				if(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*Form1->SGr_vSOKU_SYUKA->RowCount+ARow].RESULT).Trim()
		 		!= AnsiString(pCELLINFO_SOKU_SYUKA[ACol*Form1->SGr_vSOKU_SYUKA->RowCount+ARow].DISP_RESULT).Trim())
				{
					if(SGr_vSOKU_SYUKA->Canvas->Font->Color == clRed)
					{
						SGr_vSOKU_SYUKA->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vSOKU_SYUKA->Canvas->Font->Color= clBlue;
					}
				}
				else
				{
					if(SGr_vSOKU_SYUKA->Canvas->Font->Color == clRed)
					{
 						SGr_vSOKU_SYUKA->Canvas->Font->Color= clRed;
					}
					else
					{
						SGr_vSOKU_SYUKA->Canvas->Font->Color= clGray;
					}
				}
				break;
			}
   			if(State.Contains(gdFocused))
			{
				SGr_vSOKU_SYUKA->Canvas->Font->Color= clHighlightText;
   			}
		}

        //���蒆�̃��b�g�͏��������Ȃ�
//		if( AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].KOMK_NO).ToIntDef(0) == 0
		if( pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].INS_ON == false
		||  AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].SOKU_FLG).ToIntDef(0) == 0)
		{
			SGr_vSOKU_SYUKA->Canvas->Font->Color= clGray;
			SGr_vSOKU_SYUKA->Canvas->Brush->Color= clGray;
		}
		SGr_vSOKU_SYUKA->Canvas->FillRect(Rect);
		InflateRect(&r,-2,-2);
    //�o�̓^�C�v�ɂ��t�H�[�}�b�g�ʒu����
		switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
		{
		case 0:		//�����E����
		case 1:		//�p�x
			DrawText(SGr_vSOKU_SYUKA->Canvas->Handle,sBuf.c_str(),-1,&r,DT_RIGHT); //�E��
			break;
		case 2:  	//�ǁE��
			DrawText(SGr_vSOKU_SYUKA->Canvas->Handle,sBuf.c_str(),-1,&r,DT_CENTER); //������
			break;
		default:	//����
			DrawText(SGr_vSOKU_SYUKA->Canvas->Handle,sBuf.c_str(),-1,&r,DT_LEFT); //����
			break;
		}
    //���݂͕s�v�ȏ����ł��i�S�z������R�����g�ɂ��܂��񂪁A�����đՂ��Ă����͖����ł�
    //�F�ɂ�锻��
		if(hCELLINFO_SOKU_SYUKA)
		{
			if(SGr_vSOKU_SYUKA->Color != 0x00DDDDDD)
			{
				switch(SGr_vSOKU_SYUKA->Canvas->Font->Color)
				{
				case clBlack:
					pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].JUDGE = 0;
					break;
				case clRed:
					pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].JUDGE = 1;
					break;
				default:
					pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].JUDGE = 2;
					break;
				}
			}
			else
			{
				switch(SGr_vSOKU_SYUKA->Canvas->Font->Color)
				{
				case clBlue:
				//�K�i���肪����܂�
					pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].JUDGE = 0;
					break;
				case clGray:
					pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].JUDGE = 0;
					break;
				case clRed:
					pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].JUDGE = 1;
					break;
				case clMaroon:
					pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].JUDGE = 1;
					break;
				default:
					pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].JUDGE = 2;
					break;
				}
			}
			if(sBuf.Trim().Length() == 0) pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].JUDGE = 2;
		}
		break;
    //�ȍ~Case2�A3�A4�i�o�׌��������A�f�ތ����o�ׁA�f�ތ��������j���������e�͓����ł�
   case 2:
		if(!hCELLINFO_RIRE_SYUKA) return;
		// 2003/06/02 K.Yamada �ΏۃZ�����������́A�����𒆎~���܂�
		if( SGr_vRIRE_SYUKA->RowCount == 1 ) return;
	//�w�i�F�ŏ���
		SGr_vRIRE_SYUKA->Canvas->FillRect(Rect);
	//�Œ�Z���̗��̘g��`��
		if(SGr_vRIRE_SYUKA->Ctl3D&&State.Contains(gdFixed))
		{
	   		DrawEdge(SGr_vRIRE_SYUKA->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);
   		}
   //�t�H�[�J�X�̂���Z���̕����F���Z�b�g
   		if(State.Contains(gdFocused))
		{
			SGr_vRIRE_SYUKA->Canvas->Font->Color= clHighlightText;
			SGr_vRIRE_SYUKA->Canvas->Font->Color= clBlack;
   		}
   //�I������Ă���Z���̕����F���Z�b�g
   		else if(State.Contains(gdSelected))
		{
   //���ʂ̃Z���̕����F���Z�b�g
   		}
   		else
		{
	   		SGr_vRIRE_SYUKA->Canvas->Font->Color= SGr_vRIRE_SYUKA->Font->Color;
   		}
		if(asString == "�s�v")
		{
			SGr_vRIRE_SYUKA->Canvas->Font->Color= clGray;
		}
		else
		{
			SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
		}

		if(Form1->SGr_tRIRE->Cells[0][0]!="" && hCELLINFO_RIRE_SYUKA != NULL)
		{
			if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
				sBuf = pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount + ARow].RESULT;
			}
			sBuf = pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount + ARow].DISP_RESULT;
			if( hCELLINFO_RIRE_SYUKA )
			{
//���͂����l�̏ꍇ�A�K�i���Z�o����
				if((AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 1)
				|| (AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 2))
				{
					dMAX = pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].MAX;
					dMIN = pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].MIN;
				}
			}
		}

	//�ȏ�ȉ��̋K�i�̏ꍇ�΍�
		iKIKA_KIND = 1;		//�f�t�H���g�͏㉺���Ŕ���
		if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].KIKA_TYPE) == 1)
		{
			if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].KIKA_KIND) == 2)
			{
				iKIKA_KIND = 2;
			}
			else if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].KIKA_KIND) == 3)
			{
				iKIKA_KIND = 3;
			}
		}
//�t�H�[�}�b�g����
		if(hCELLINFO_RIRE_SYUKA )
		{
			if(asString == "�s�v"
			|| AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].RESULT) == "�s�v")
			{
				sBuf = "�s�v";
				//�Z�����͂��o�b�t�@�Ɏ�荞��
				strcpy(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].RESULT		,sBuf.c_str());
				strcpy(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].DISP_RESULT,sBuf.c_str());
				pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].JUDGE = 2;
			}
			else
			{
				switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:		//�����E����
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_RIRE_SYUKA[(ACol*SGr_vRIRE_SYUKA->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( sDeci1.Length() == 1 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 1:		//�p�x
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_RIRE_SYUKA[(ACol*SGr_vRIRE_SYUKA->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( sDeci1.Length() == 1 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 2:  	//�ǁE��
					break;
				default:	//����
					break;
				}
				SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;		//����p�F�����l��OK��
				switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:
					if(AnsiString(SGr_vRIRE_SYUKA->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}
					//2003.05.08 E.Takase Add��
					bRtn = ConvDoubleDefS(SGr_vRIRE_SYUKA->Cells[ACol][ARow],sDeci1,SGr_vRIRE_SYUKA->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add��
					//2003.05.08 E.Takase Add �R�����g��
					//try{
					//	sBuf = FormatFloat(sDeci1,SGr_vRIRE_SYUKA->Cells[ACol][ARow].ToDouble());
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
					//}
					//catch(...){
					//	sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
					//}
					//2003.05.08 E.Takase Add �R�����g��
					//�Z�����͂��o�b�t�@�Ɏ�荞��
					if(hCELLINFO_RIRE_SYUKA)
					{
						//����p��ʂňȊO
						if(SGr_vRIRE_SYUKA->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
					//�ǔ۔���
					//2003.05.08 E.Takase Add��
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
						case 2:
							if( dBuf <= dMAX )
							{
								SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
							}
							break;
						case 3:
							if( dBuf >= dMIN )
							{
								SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
							}
							break;
						default:
                            // 2003/10/06 A.Tamura �Ȃ����K�i���Ȃ̂ɋK�i�O�Ɣ��肳���̂�Double�^���Đݒ肵�܂��B
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN)
							{
								SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
							}
						}
					} else {
						sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
					}
					//2003.05.08 E.Takase Add��
					//2003.05.08 E.Takase Add �R�����g��
					//try{
					//	switch( iKIKA_KIND )
					//	{
					//	case 2:
					//		if( sBuf.ToDouble() <= dMAX )
					//		{
					//			SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
					//		}
					//		break;
					//	case 3:
					//		if( sBuf.ToDouble() >= dMIN )
					//		{
					//			SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
					//		}
					//		break;
					//	default:
					//		if( sBuf.ToDouble() <= dMAX && sBuf.ToDouble() >= dMIN)
					//		{
					//			SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
					//		}
					//	}
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
					//}
					//catch(...){
					//	sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
					//}
					//2003.05.08 E.Takase Add �R�����g��
					break;
				case 1:
					if(AnsiString(SGr_vRIRE_SYUKA->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}

					//2003.05.08 E.Takase Add��
					bRtn = ConvDoubleDefS(SGr_vRIRE_SYUKA->Cells[ACol][ARow],sDeci1,SGr_vRIRE_SYUKA->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add��
					//2003.05.08 E.Takase Add �R�����g��
					//try{
					//	sBuf = FormatFloat(sDeci1,SGr_vRIRE_SYUKA->Cells[ACol][ARow].ToDouble());
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
					//}
					//catch(...){
					//	sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
					//}
					//2003.05.08 E.Takase Add �R�����g��
					//�ǔ۔���
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
						case 2:
							if( dBuf <= dMAX )
							{
								SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
							}
							break;
						case 3:
							if( dBuf >= dMIN )
							{
								SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
							}
							break;
						default:
                            // 2003/10/06 A.Tamura �Ȃ����K�i���Ȃ̂ɋK�i�O�Ɣ��肳���̂�Double�^���Đݒ肵�܂��B
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

                            // 2003/10/06 A.Tamura �Ȃ�ł���ȃR�[�h�Ȃ́H�@���ɂ��ǂ�
							// if( dBuf <= dMAX && sBuf.ToDouble() >= dMIN)
							if( dBuf <= dMAX && dBuf >= dMIN)
							{
								SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
							}
						}

					} else {
						sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
						if(hCELLINFO_RIRE_SYUKA)
						{
						//����p��ʂňȊO
							if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
								sBuf = sBuf.SubString(1,14);
								if( sBuf.Length() == 14 ){
									if ( sBuf.ByteType( 14 ) == mbLeadByte ){
										sBuf = sBuf.SubString(1,13);
									}
								}
								strcpy(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].RESULT,sBuf.c_str());
							}
						}
					}
					//2003.05.08 E.Takase Add��
					//2003.05.08 E.Takase Add �R�����g��
					//try{
					//	switch( iKIKA_KIND )
					//	{
					//	case 2:
					//		if( sBuf.ToDouble() <= dMAX )
					//		{
					//			SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
					//		}
					//		break;
					//	case 3:
					//		if( sBuf.ToDouble() >= dMIN )
					//		{
					//			SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
					//		}
					//		break;
					//	default:
					//		if( sBuf.ToDouble() <= dMAX && sBuf.ToDouble() >= dMIN)
					//		{
					//			SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
					//		}
					//	}
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
					//	if(hCELLINFO_RIRE_SYUKA)
					//	{
					//	//����p��ʂňȊO
					//		if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
					//			strcpy(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].RESULT,sBuf.c_str());
					//		}
					//	}
					//	break;
					//}
					//catch(...){
					//	sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
					//	if(hCELLINFO_RIRE_SYUKA)
					//	{
					//		//����p��ʂňȊO
					//		if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
					//			strcpy(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].RESULT,sBuf.c_str());
					//		}
					//	}
					//	break;
					//}
					//2003.05.08 E.Takase Add �R�����g��

					//�Z�����͂��o�b�t�@�Ɏ�荞��
					if(hCELLINFO_RIRE_SYUKA)
					{
						//����p��ʂňȊO
						if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
					if(sBuf.Trim().Length() != 0)
					{
						i1 = strcspn(sBuf.c_str(),".");
						sTemp = sBuf.SubString(1,i1);
						sTemp += "��";
						if(sBuf.SubString(i1+2,sBuf.Length() - i1).Length()!=0)
						{
							sTemp += sBuf.SubString(i1+2,sBuf.Length() - i1);
							sTemp += "'";
						}
						sBuf = sTemp;
					}
					break;
				case 2:
					sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
					sBuf = sBuf.Trim();
					if( sBuf == 0 || sBuf == "��")
					{
						sBuf ="��";
					}
					else if( sBuf.Length() != 0)
					{
						sBuf = "��";
					}
					if( sBuf == "��" )
					{
						SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
					}
					else
					{
						SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
					}
                    //����p��ʈȊO
                    if(SGr_vRIRE_SYUKA->Color != 0x00DDDDDD){
                        sBuf = sBuf.SubString(1,14);
                        if( sBuf.Length() == 14 ){
                            if ( sBuf.ByteType( 14 ) == mbLeadByte ){
                                sBuf = sBuf.SubString(1,13);
                            }
                        }
					    if( sBuf == 0 || sBuf == "��")
					    {
                            strcpy(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].RESULT,"0");
                        }
                        else if(sBuf.Length() != 0)
					    {
                            strcpy(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].RESULT,"1");
                        }
                        else
                        {
                            strcpy(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].RESULT,"");
                        }
                    }
					break;
				default:
					sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
					SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
					//�Z�����͂��o�b�t�@�Ɏ�荞��
					if(hCELLINFO_RIRE_SYUKA)
					{
						//����p��ʂňȊO
						if(SGr_vRIRE_SYUKA->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
				}
			}
		}
		else
		{
			sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
		}
		InflateRect(&r,-2,-2);
//�I�𒆂̓n�C���C�g�\��
   		if(State.Contains(gdFocused)
		&& SGr_vRIRE_SYUKA->Canvas->Font->Color != clRed
		&& SGr_vRIRE_SYUKA->Canvas->Font->Color != clGray)
		{
			SGr_vRIRE_SYUKA->Canvas->Font->Color= clHighlightText;
   		}
//����ҏW��ʂ̓J���[��ύX����
		if(SGr_vRIRE_SYUKA->Color == 0x00DDDDDD)
		{
			switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
			{
			case 0:
			case 1:
			case 2:
				try{
//				if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].RESULT).Trim().ToDouble()
//			 	!= AnsiString(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].DISP_RESULT).Trim().ToDouble())
				sComp1 = AnsiString(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].RESULT);
				sComp2 = AnsiString(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].DISP_RESULT);
				sTempComp = sComp1;
				bRtn = ConvDoubleDefS(sTempComp,sDeci1,sTempComp,&sComp1);
				sTempComp = sComp2;
				bRtn = ConvDoubleDefS(sTempComp,sDeci1,sTempComp,&sComp2);
				if( sComp1 != sComp2)
				{
					if(SGr_vRIRE_SYUKA->Canvas->Font->Color == clRed)
					{
						SGr_vRIRE_SYUKA->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vRIRE_SYUKA->Canvas->Font->Color= clBlue;
					}
				}
				else
				{
					if(SGr_vRIRE_SYUKA->Canvas->Font->Color == clRed)
					{
 						SGr_vRIRE_SYUKA->Canvas->Font->Color= clRed;
					}
					else
					{
						SGr_vRIRE_SYUKA->Canvas->Font->Color= clGray;
					}
				}
				}
				catch(EConvertError& e){
					if(SGr_vRIRE_SYUKA->Canvas->Font->Color == clRed)
					{
						SGr_vRIRE_SYUKA->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vRIRE_SYUKA->Canvas->Font->Color= clBlue;
					}
				}
				catch(...){
					if(SGr_vRIRE_SYUKA->Canvas->Font->Color == clRed)
					{
						SGr_vRIRE_SYUKA->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vRIRE_SYUKA->Canvas->Font->Color= clBlue;
					}
				}
				break;
			default:
				if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].RESULT).Trim()
			 	!= AnsiString(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].DISP_RESULT).Trim())
				{
					if(SGr_vRIRE_SYUKA->Canvas->Font->Color == clRed)
					{
						SGr_vRIRE_SYUKA->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vRIRE_SYUKA->Canvas->Font->Color= clBlue;
					}
				}
				else
				{
					if(SGr_vRIRE_SYUKA->Canvas->Font->Color == clRed)
					{
 						SGr_vRIRE_SYUKA->Canvas->Font->Color= clRed;
					}
					else
					{
						SGr_vRIRE_SYUKA->Canvas->Font->Color= clGray;
					}
				}
				break;
			}
		}
	//�s�v�����H
//		if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].KOMK_NO).ToIntDef(0) == 0
		if(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].INS_ON == false
		|| AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].SOKU_FLG).ToIntDef(0) == 0)
		{
			SGr_vRIRE_SYUKA->Canvas->Font->Color= clGray;
			SGr_vRIRE_SYUKA->Canvas->Brush->Color= clGray;
		}
//�o�̓^�C�v�ɂ��t�H�[�}�b�g�ʒu����
		SGr_vRIRE_SYUKA->Canvas->FillRect(Rect);
		InflateRect(&r,-2,-2);
		switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
		{
		case 0:		//�����E����
		case 1:		//�p�x
			DrawText(SGr_vRIRE_SYUKA->Canvas->Handle,sBuf.c_str(),-1,&r,DT_RIGHT); //�E��
			break;
		case 2:  	//�ǁE��
			DrawText(SGr_vRIRE_SYUKA->Canvas->Handle,sBuf.c_str(),-1,&r,DT_CENTER); //������
			break;
		default:	//����
			DrawText(SGr_vRIRE_SYUKA->Canvas->Handle,sBuf.c_str(),-1,&r,DT_LEFT); //����
			break;
		}
//�F�ɂ�锻��
		if(hCELLINFO_RIRE_SYUKA)
		{
			if(SGr_vRIRE_SYUKA->Color != 0x00DDDDDD)
			{
				switch(SGr_vRIRE_SYUKA->Canvas->Font->Color)
				{
				case clBlack:
					pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].JUDGE = 0;
					break;
				case clRed:
					pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].JUDGE = 1;
					break;
				default:
					pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].JUDGE = 2;
					break;
				}
			}
			else
			{
				switch(SGr_vRIRE_SYUKA->Canvas->Font->Color)
				{
				case clBlue:
				//�K�i���肪����܂�
					pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].JUDGE = 0;
					break;
				case clGray:
					pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].JUDGE = 0;
					break;
				case clRed:
					pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].JUDGE = 1;
					break;
				case clMaroon:
					pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].JUDGE = 1;
					break;
				default:
					pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].JUDGE = 2;
					break;
				}
			}
			if(sBuf.Trim() == 0) pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].JUDGE = 2;
		}
		break;
//����f�މ��
   case 3:
		if(!hCELLINFO_SOKU_SOZAI) return;
		// 2003/06/02 K.Yamada �ΏۃZ�����������́A�����𒆎~���܂�
		if( SGr_vSOKU_SOZAI->RowCount == 1 ) return;
	//�w�i�F�ŏ���
		SGr_vSOKU_SOZAI->Canvas->FillRect(Rect);
	//�Œ�Z���̗��̘g��`��
		if(SGr_vSOKU_SOZAI->Ctl3D&&State.Contains(gdFixed))
		{
	   		DrawEdge(SGr_vSOKU_SOZAI->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);
   		}
   //�t�H�[�J�X�̂���Z���̕����F���Z�b�g
   		if(State.Contains(gdFocused))
		{
			SGr_vSOKU_SOZAI->Canvas->Font->Color= clHighlightText;
			SGr_vSOKU_SOZAI->Canvas->Font->Color= clBlack;
   		}
   //�I������Ă���Z���̕����F���Z�b�g
   		else if(State.Contains(gdSelected))
		{
   //���ʂ̃Z���̕����F���Z�b�g
   		}
   		else
		{
	   		SGr_vSOKU_SOZAI->Canvas->Font->Color= SGr_vSOKU_SOZAI->Font->Color;
   		}
		if(asString == "�s�v")
		{
			SGr_vSOKU_SOZAI->Canvas->Font->Color= clGray;
		}
		else
		{
			SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
		}

		if(Form1->SGr_tSOKU->Cells[0][0]!="" && hCELLINFO_SOKU_SOZAI != NULL)
		{
			if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD){
				sBuf = pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount + ARow].RESULT;
			}
			sBuf = pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount + ARow].DISP_RESULT;
			if( hCELLINFO_SOKU_SOZAI )
			{
//���͂����l�̏ꍇ�A�K�i���Z�o����
				if((AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 1)
				|| (AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 2))
				{
					dMAX = pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].MAX;
					dMIN = pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].MIN;
				}
			}
		}
	//�ȏ�ȉ��̋K�i�̏ꍇ�΍�
		iKIKA_KIND = 1;		//�f�t�H���g�͏㉺���Ŕ���
		if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].KIKA_TYPE) == 1)
		{
			if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].KIKA_KIND) == 2)
			{
				iKIKA_KIND = 2;
			}
			else if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].KIKA_KIND) == 3)
			{
				iKIKA_KIND = 3;
			}
		}

//�t�H�[�}�b�g����
		if(hCELLINFO_SOKU_SOZAI )
		{
			if(asString == "�s�v"
			|| AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].RESULT) == "�s�v")
			{
				sBuf = "�s�v";
				//�Z�����͂��o�b�t�@�Ɏ�荞��
				strcpy(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].RESULT		,sBuf.c_str());
				strcpy(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].DISP_RESULT,sBuf.c_str());
				pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].JUDGE = 2;
			}
			else
			{
				switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:		//�����E����
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_SOKU_SOZAI[(ACol*SGr_vSOKU_SOZAI->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( i1 == 0 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 1:		//�p�x
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_SOKU_SOZAI[(ACol*SGr_vSOKU_SOZAI->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( i1 == 0 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 2:  	//�ǁE��
					break;
				default:	//����
					break;
				}
				SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;		//����p�F�����l��OK��
				switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:
					if(AnsiString(SGr_vSOKU_SOZAI->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}
					//2003.05.08 E.Takase Add��
					bRtn = ConvDoubleDefS(SGr_vSOKU_SOZAI->Cells[ACol][ARow],sDeci1,SGr_vSOKU_SOZAI->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add��
					//2003.05.08 E.Takase Add �R�����g��
					//try{
					//	sBuf = FormatFloat(sDeci1,SGr_vSOKU_SOZAI->Cells[ACol][ARow].ToDouble());
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
					//}
					//catch(...){
					//	sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
					//}
					//2003.05.08 E.Takase Add �R�����g��
					//�Z�����͂��o�b�t�@�Ɏ�荞��
					if(hCELLINFO_SOKU_SOZAI)
					{
						//����p��ʂňȊO
						if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
					//�ǔ۔���
					//2003.05.08 E.Takase Add��
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
						case 2:
							if( dBuf <= dMAX )
							{
								SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
							}
							break;
						case 3:
							if( dBuf >= dMIN )
							{
								SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
							}
							break;
						default:
                            // 2003/10/06 A.Tamura �Ȃ����K�i���Ȃ̂ɋK�i�O�Ɣ��肳���̂�Double�^���Đݒ肵�܂��B
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN)
							{
								SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
							}
						}
					} else {
						sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
					}
					//2003.05.08 E.Takase Add��
					//2003.05.08 E.Takase Add �R�����g��
					//try{
					//	switch( iKIKA_KIND )
					//	{
					//	case 2:
					//		if( sBuf.ToDouble() <= dMAX )
					//		{
					//			SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
					//		}
					//		break;
					//	case 3:
					//		if( sBuf.ToDouble() >= dMIN )
					//		{
					//			SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
					//		}
					//		break;
					//	default:
					//		if( sBuf.ToDouble() <= dMAX && sBuf.ToDouble() >= dMIN)
					//		{
					//			SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
					//		}
					//	}
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
					//}
					//catch(...){
					//	sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
					//}
					//2003.05.08 E.Takase Add �R�����g��
					break;
				case 1:
					if(AnsiString(SGr_vSOKU_SOZAI->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}
					//2003.05.08 E.Takase Add��
					bRtn = ConvDoubleDefS(SGr_vSOKU_SOZAI->Cells[ACol][ARow],sDeci1,SGr_vSOKU_SOZAI->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add��
					//2003.05.08 E.Takase Add �R�����g��
					//try{
					//	sBuf = FormatFloat(sDeci1,SGr_vSOKU_SOZAI->Cells[ACol][ARow].ToDouble());
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
					//}
					//catch(...){
					//	sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
					//}
					//2003.05.08 E.Takase Add �R�����g��

					//�ǔ۔���
					//2003.05.08 E.Takase Add��
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
						case 2:
							if( dBuf <= dMAX )
							{
								SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
							}
							break;
						case 3:
							if( dBuf >= dMIN )
							{
								SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
							}
							break;
						default:
                            // 2003/10/06 A.Tamura �Ȃ����K�i���Ȃ̂ɋK�i�O�Ɣ��肳���̂�Double�^���Đݒ肵�܂��B
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN)
							{
								SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
							}
						}
					} else {
						sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
						//����p��ʂňȊO
						if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
					//2003.05.08 E.Takase Add��
					//2003.05.08 E.Takase Add �R�����g��
					//try{
					//	switch( iKIKA_KIND )
					//	{
					//	case 2:
					//		if( sBuf.ToDouble() <= dMAX )
					//		{
					//			SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
					//		}
					//		break;
					//	case 3:
					//		if( sBuf.ToDouble() >= dMIN )
					//		{
					//			SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
					//		}
					//		break;
					//	default:
					//		if( sBuf.ToDouble() <= dMAX && sBuf.ToDouble() >= dMIN)
					//		{
					//			SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
					//		}
					//	}
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
					//	//����p��ʂňȊO
					//	if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD){
					//		strcpy(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
					//	}
					//	break;
					//}
					//catch(...){
					//	sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
					//	//����p��ʂňȊO
					//	if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD){
					//		strcpy(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
					//	}
					//	break;
					//}
					//2003.05.08 E.Takase Add �R�����g��

					//�Z�����͂��o�b�t�@�Ɏ�荞��
					if(hCELLINFO_SOKU_SOZAI)
					{
						//����p��ʂňȊO
						if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD){
							strcpy(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
					if(sBuf.Trim().Length() != 0)
					{
						i1 = strcspn(sBuf.c_str(),".");
						sTemp = sBuf.SubString(1,i1);
						sTemp += "��";
						if(sBuf.SubString(i1+2,sBuf.Length() - i1).Length()!=0)
						{
							sTemp += sBuf.SubString(i1+2,sBuf.Length() - i1);
							sTemp += "'";
						}
						sBuf = sTemp;
					}
					break;
				case 2:
					sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
					sBuf = sBuf.Trim();
					if( sBuf == 0 || sBuf == "��")
					{
						sBuf ="��";
					}
					else if( sBuf.Length() != 0)
					{
						sBuf = "��";
					}
					if( sBuf == "��" )
					{
						SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
					}
					else
					{
						SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
					}
                    //����p��ʈȊO
                    if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD){
                        sBuf = sBuf.SubString(1,14);
                        if( sBuf.Length() == 14 ){
                            if ( sBuf.ByteType( 14 ) == mbLeadByte ){
                                sBuf = sBuf.SubString(1,13);
                            }
                        }
					    if( sBuf == 0 || sBuf == "��")
					    {
                            strcpy(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].RESULT,"0");
                        }
                        else if(sBuf.Length() != 0)
					    {
                            strcpy(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].RESULT,"1");
                        }
                        else
					    {
                            strcpy(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].RESULT,"");
                        }
                    }
					break;
				default:
					sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
					SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
					//�Z�����͂��o�b�t�@�Ɏ�荞��
					if(hCELLINFO_SOKU_SOZAI)
					{
						//����p��ʂňȊO
						if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
				}
			}
		}
		else
		{
			sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
		}
		InflateRect(&r,-2,-2);
//�I�𒆂̓n�C���C�g�\��
   		if(State.Contains(gdFocused)
		&& SGr_vSOKU_SOZAI->Canvas->Font->Color != clRed
		&& SGr_vSOKU_SOZAI->Canvas->Font->Color != clGray)
		{
			SGr_vSOKU_SOZAI->Canvas->Font->Color= clHighlightText;
   		}
//����ҏW��ʂ̓J���[��ύX����
		if(SGr_vSOKU_SOZAI->Color == 0x00DDDDDD)
		{
			switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
			{
			case 0:
			case 1:
			case 2:
				try{
//				if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].RESULT).Trim().ToDouble()
//			 	!= AnsiString(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].DISP_RESULT).Trim().ToDouble())
				sComp1 = AnsiString(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].RESULT);
				sComp2 = AnsiString(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].DISP_RESULT);
				sTempComp = sComp1;
				bRtn = ConvDoubleDefS(sTempComp,sDeci1,sTempComp,&sComp1);
				sTempComp = sComp2;
				bRtn = ConvDoubleDefS(sTempComp,sDeci1,sTempComp,&sComp2);
				if( sComp1 != sComp2)
				{
					if(SGr_vSOKU_SOZAI->Canvas->Font->Color == clRed)
					{
						SGr_vSOKU_SOZAI->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vSOKU_SOZAI->Canvas->Font->Color= clBlue;
					}
				}
				else
				{
					if(SGr_vSOKU_SOZAI->Canvas->Font->Color == clRed)
					{
	 					SGr_vSOKU_SOZAI->Canvas->Font->Color= clRed;
					}
					else
					{
						SGr_vSOKU_SOZAI->Canvas->Font->Color= clGray;
					}
				}
				}
				catch(EConvertError& e){
					if(SGr_vSOKU_SOZAI->Canvas->Font->Color == clRed)
					{
						SGr_vSOKU_SOZAI->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vSOKU_SOZAI->Canvas->Font->Color= clBlue;
					}
				}
				catch(...){
					if(SGr_vSOKU_SOZAI->Canvas->Font->Color == clRed)
					{
						SGr_vSOKU_SOZAI->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vSOKU_SOZAI->Canvas->Font->Color= clBlue;
					}
				}
				break;
			default:
				if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].RESULT).Trim()
			 	!= AnsiString(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].DISP_RESULT).Trim())
				{
					if(SGr_vSOKU_SOZAI->Canvas->Font->Color == clRed)
					{
						SGr_vSOKU_SOZAI->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vSOKU_SOZAI->Canvas->Font->Color= clBlue;
					}
				}
				else
				{
					if(SGr_vSOKU_SOZAI->Canvas->Font->Color == clRed)
					{
	 					SGr_vSOKU_SOZAI->Canvas->Font->Color= clRed;
					}
					else
					{
						SGr_vSOKU_SOZAI->Canvas->Font->Color= clGray;
					}
				}
				break;
			}
		}
	//�s�v�����H
//		if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].KOMK_NO).ToIntDef(0) == 0
		if(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].INS_ON == false
		|| AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].SOKU_FLG).ToIntDef(0) == 0)
		{
			SGr_vSOKU_SOZAI->Canvas->Font->Color= clGray;
			SGr_vSOKU_SOZAI->Canvas->Brush->Color= clGray;
		}
		SGr_vSOKU_SOZAI->Canvas->FillRect(Rect);
		InflateRect(&r,-2,-2);
//�o�̓^�C�v�ɂ��t�H�[�}�b�g�ʒu����
		switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
		{
		case 0:		//�����E����
		case 1:		//�p�x
			DrawText(SGr_vSOKU_SOZAI->Canvas->Handle,sBuf.c_str(),-1,&r,DT_RIGHT); //�E��
			break;
		case 2:  	//�ǁE��
			DrawText(SGr_vSOKU_SOZAI->Canvas->Handle,sBuf.c_str(),-1,&r,DT_CENTER); //������
			break;
		default:	//����
			DrawText(SGr_vSOKU_SOZAI->Canvas->Handle,sBuf.c_str(),-1,&r,DT_LEFT); //����
			break;
		}
//�F�ɂ�锻��
		if(hCELLINFO_SOKU_SOZAI)
		{
			if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD)
			{
				switch(SGr_vSOKU_SOZAI->Canvas->Font->Color)
				{
				case clBlack:
					pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].JUDGE = 0;
					break;
				case clRed:
					pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].JUDGE = 1;
					break;
				default:
					pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].JUDGE = 2;
					break;
				}
			}
			else
			{
				switch(SGr_vSOKU_SOZAI->Canvas->Font->Color)
				{
				case clBlue:
				//�K�i���肪����܂�
					pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].JUDGE = 0;
					break;
				case clGray:
					pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].JUDGE = 0;
					break;
				case clRed:
					pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].JUDGE = 1;
					break;
				case clMaroon:
					pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].JUDGE = 1;
					break;
				default:
					pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].JUDGE = 2;
					break;
				}
	  		}
			if(sBuf.Trim() == 0) pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].JUDGE = 2;
		}
		break;
//����f�ރO���b�h
   case 4:
		if(!hCELLINFO_RIRE_SOZAI) return;
		// 2003/06/02 K.Yamada �ΏۃZ�����������́A�����𒆎~���܂�
		if( SGr_vRIRE_SOZAI->RowCount == 1 ) return;
	//�w�i�F�ŏ���
		SGr_vRIRE_SOZAI->Canvas->FillRect(Rect);
	//�Œ�Z���̗��̘g��`��
		if(SGr_vRIRE_SOZAI->Ctl3D&&State.Contains(gdFixed))
		{
	   		DrawEdge(SGr_vRIRE_SOZAI->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);
   		}
   //�t�H�[�J�X�̂���Z���̕����F���Z�b�g
   		if(State.Contains(gdFocused))
		{
			SGr_vRIRE_SOZAI->Canvas->Font->Color= clHighlightText;
			SGr_vRIRE_SOZAI->Canvas->Font->Color= clBlack;
   		}
   //�I������Ă���Z���̕����F���Z�b�g
   		else if(State.Contains(gdSelected))
		{
   //���ʂ̃Z���̕����F���Z�b�g
   		}
   		else
		{
	   		SGr_vRIRE_SOZAI->Canvas->Font->Color= SGr_vRIRE_SOZAI->Font->Color;
   		}
		if(asString == "�s�v")
		{
			SGr_vRIRE_SOZAI->Canvas->Font->Color= clGray;
		}
		else
		{
			SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
		}

		if(Form1->SGr_tRIRE->Cells[0][0]!="" && hCELLINFO_RIRE_SOZAI != NULL)
		{
			if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
				sBuf = pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount + ARow].RESULT;
			}
			sBuf = pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount + ARow].DISP_RESULT;
			if( hCELLINFO_RIRE_SOZAI )
			{
//���͂����l�̏ꍇ�A�K�i���Z�o����
				if((AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 1)
				|| (AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 2))
				{
					dMAX = pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].MAX;
					dMIN = pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].MIN;
				}
			}
		}
	//�ȏ�ȉ��̋K�i�̏ꍇ�΍�
		iKIKA_KIND = 1;		//�f�t�H���g�͏㉺���Ŕ���
		if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].KIKA_TYPE) == 1)
		{
			if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].KIKA_KIND) == 2)
			{
				iKIKA_KIND = 2;
			}
			else if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].KIKA_KIND) == 3)
			{
				iKIKA_KIND = 3;
			}
		}

//�t�H�[�}�b�g����
		if(hCELLINFO_RIRE_SOZAI )
		{
			if(asString == "�s�v"
			|| AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].RESULT) == "�s�v")
			{
				sBuf = "�s�v";
				//�Z�����͂��o�b�t�@�Ɏ�荞��
				strcpy(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].RESULT		,sBuf.c_str());
				strcpy(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].DISP_RESULT,sBuf.c_str());
				pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].JUDGE = 2;
			}
			else
			{
				switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:		//�����E����
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_RIRE_SOZAI[(ACol*SGr_vRIRE_SOZAI->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( sDeci1.Length() == 1 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 1:		//�p�x
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_RIRE_SOZAI[(ACol*SGr_vRIRE_SOZAI->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( sDeci1.Length() == 1 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 2:  	//�ǁE��
					break;
				default:	//����
					break;
				}
				SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;		//����p�F�����l��OK��
				switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:
					if(AnsiString(SGr_vRIRE_SOZAI->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}
					//2003.05.08 E.Takase Add��
					bRtn = ConvDoubleDefS(SGr_vRIRE_SOZAI->Cells[ACol][ARow],sDeci1,SGr_vRIRE_SOZAI->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add��
					//2003.05.08 E.Takase Add �R�����g��
					//try{
					//	sBuf = FormatFloat(sDeci1,SGr_vRIRE_SOZAI->Cells[ACol][ARow].ToDouble());
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
					//}
					//catch(...){
					//	sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
					//}
					//2003.05.08 E.Takase Add �R�����g��

					//�Z�����͂��o�b�t�@�Ɏ�荞��
					if(hCELLINFO_RIRE_SOZAI)
					{
						//����p��ʂňȊO
						if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
					//�ǔ۔���
					//2003.05.08 E.Takase Add��
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);

						switch( iKIKA_KIND )
						{
						case 2:
							if( dBuf <= dMAX )
							{
								SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
							}
							break;
						case 3:
							if( dBuf >= dMIN )
							{
								SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
							}
							break;
						default:
                            // 2003/10/06 A.Tamura �Ȃ����K�i���Ȃ̂ɋK�i�O�Ɣ��肳���̂�Double�^���Đݒ肵�܂��B
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN)
							{
								SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
							}
						}

					} else {
						sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
					}
					//2003.05.08 E.Takase Add��
					//2003.05.08 E.Takase Add �R�����g��
					//try{
					//	switch( iKIKA_KIND )
					//	{
					//	case 2:
					//		if( sBuf.ToDouble() <= dMAX )
					//		{
					//			SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
					//		}
					//		break;
					//	case 3:
					//		if( sBuf.ToDouble() >= dMIN )
					//		{
					//			SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
					//		}
					//		break;
					//	default:
					//		if( sBuf.ToDouble() <= dMAX && sBuf.ToDouble() >= dMIN)
					//		{
					//			SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
					//		}
					//	}
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
					//}
					//catch(...){
					//	sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
					//}
					//2003.05.08 E.Takase Add �R�����g��
					break;
				case 1:
					if(AnsiString(SGr_vRIRE_SOZAI->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}

					//2003.05.08 E.Takase Add��
					bRtn = ConvDoubleDefS(SGr_vRIRE_SOZAI->Cells[ACol][ARow],sDeci1,SGr_vRIRE_SOZAI->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add��
					//2003.05.08 E.Takase Add �R�����g��
					//try{
					//	sBuf = FormatFloat(sDeci1,SGr_vRIRE_SOZAI->Cells[ACol][ARow].ToDouble());
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
					//}
					//catch(...){
					//	sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
					//}
					//2003.05.08 E.Takase Add �R�����g��

					//�ǔ۔���
					//2003.05.08 E.Takase Add��
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
						case 2:
							if( dBuf <= dMAX )
							{
								SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
							}
							break;
						case 3:
							if( dBuf >= dMIN )
							{
								SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
							}
							break;
						default:
                            // 2003/10/06 A.Tamura �Ȃ����K�i���Ȃ̂ɋK�i�O�Ɣ��肳���̂�Double�^���Đݒ肵�܂��B
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN)
							{
								SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
							}
						}
					} else {
						sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
						//����p��ʂňȊO
						if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
					//2003.05.08 E.Takase Add��
					//2003.05.08 E.Takase Add �R�����g��
					//try{
					//	switch( iKIKA_KIND )
					//	{
					//	case 2:
					//		if( sBuf.ToDouble() <= dMAX )
					//		{
					//			SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
					//		}
					//		break;
					//	case 3:
					//		if( sBuf.ToDouble() >= dMIN )
					//		{
					//			SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
					//		}
					//		break;
					//	default:
					//		if( sBuf.ToDouble() <= dMAX && sBuf.ToDouble() >= dMIN)
					//		{
					//			SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
					//		}
					//	}
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
					//	//����p��ʂňȊO
					//	if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
					//		strcpy(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
					//	}
					//	break;
					//}
					//catch(...){
					//	sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
					//	//����p��ʂňȊO
					//	if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
					//		strcpy(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
					//	}
					//	break;
					//}
					//2003.05.08 E.Takase Add �R�����g��

					//�Z�����͂��o�b�t�@�Ɏ�荞��
					if(hCELLINFO_SOKU_SOZAI)
					{
						//����p��ʂňȊO
						if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
					if(sBuf.Trim().Length() != 0)
					{
						i1 = strcspn(sBuf.c_str(),".");
						sTemp = sBuf.SubString(1,i1);
						sTemp += "��";
						if(sBuf.SubString(i1+2,sBuf.Length() - i1).Length()!=0)
						{
							sTemp += sBuf.SubString(i1+2,sBuf.Length() - i1);
							sTemp += "'";
						}
						sBuf = sTemp;
					}
					break;
				case 2:
					sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
					sBuf = sBuf.Trim();
					if( sBuf == 0 || sBuf == "��")
					{
						sBuf ="��";
					}
					else if( sBuf.Length() != 0)
					{
						sBuf = "��";
					}
					if( sBuf == "��" )
					{
						SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
					}
					else
					{
						SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
					}
              //����p��ʈȊO
                    if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD)
                    {
                        sBuf = sBuf.SubString(1,14);
                        if( sBuf.Length() == 14 )
                        {
                            if ( sBuf.ByteType( 14 ) == mbLeadByte ){
                                sBuf = sBuf.SubString(1,13);
                            }
                        }
					    if( sBuf == 0 || sBuf == "��")
					    {
                            strcpy(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT,"0");
                        }
                        else if(sBuf.Length() != 0)
					    {
                            strcpy(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT,"1");
                        }
                        else
					    {
                            strcpy(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT,"");
                        }
                    }
                    break;
				default:
					sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
					SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
					//�Z�����͂��o�b�t�@�Ɏ�荞��
					if(hCELLINFO_RIRE_SOZAI)
					{
						//����p��ʂňȊO
						if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
				}
			}
		}
		else
		{
			sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
		}
		InflateRect(&r,-2,-2);
//�I�𒆂̓n�C���C�g�\��
   		if(State.Contains(gdFocused)
		&& SGr_vRIRE_SOZAI->Canvas->Font->Color != clRed
		&& SGr_vRIRE_SOZAI->Canvas->Font->Color != clGray)
		{
			SGr_vRIRE_SOZAI->Canvas->Font->Color= clHighlightText;
   		}
//����ҏW��ʂ̓J���[��ύX����
		if(SGr_vRIRE_SOZAI->Color == 0x00DDDDDD)
		{
			switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
			{
			case 0:
			case 1:
			case 2:
				try{
//				if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT).Trim()
//			 	!= AnsiString(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].DISP_RESULT).Trim())
				sComp1 = AnsiString(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT);
				sComp2 = AnsiString(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].DISP_RESULT);
				sTempComp = sComp1;
				bRtn = ConvDoubleDefS(sTempComp,sDeci1,sTempComp,&sComp1);
				sTempComp = sComp2;
				bRtn = ConvDoubleDefS(sTempComp,sDeci1,sTempComp,&sComp2);
				if( sComp1 != sComp2)
				{
					if(SGr_vRIRE_SOZAI->Canvas->Font->Color == clRed)
					{
						SGr_vRIRE_SOZAI->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vRIRE_SOZAI->Canvas->Font->Color= clBlue;
					}
				}
				else
				{
					if(SGr_vRIRE_SOZAI->Canvas->Font->Color == clRed)
					{
 						SGr_vRIRE_SOZAI->Canvas->Font->Color= clRed;
					}
					else
					{
						SGr_vRIRE_SOZAI->Canvas->Font->Color= clGray;
					}
				}
				}
				catch(EConvertError& e){
					if(SGr_vRIRE_SOZAI->Canvas->Font->Color == clRed)
					{
						SGr_vRIRE_SOZAI->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vRIRE_SOZAI->Canvas->Font->Color= clBlue;
					}
				}
				catch(...){
					if(SGr_vRIRE_SOZAI->Canvas->Font->Color == clRed)
					{
						SGr_vRIRE_SOZAI->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vRIRE_SOZAI->Canvas->Font->Color= clBlue;
					}
				}
				break;
			default:
				if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT).Trim()
			 	!= AnsiString(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].DISP_RESULT).Trim())
				{
					if(SGr_vRIRE_SOZAI->Canvas->Font->Color == clRed)
					{
						SGr_vRIRE_SOZAI->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vRIRE_SOZAI->Canvas->Font->Color= clBlue;
					}
				}
				else
				{
					if(SGr_vRIRE_SOZAI->Canvas->Font->Color == clRed)
					{
 						SGr_vRIRE_SOZAI->Canvas->Font->Color= clRed;
					}
					else
					{
						SGr_vRIRE_SOZAI->Canvas->Font->Color= clGray;
					}
				}
				break;
			}
		}
	//�s�v�����H
//		if( AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].KOMK_NO).ToIntDef(0) == 0
		if( pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].INS_ON == false
		|| AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].SOKU_FLG).ToIntDef(0) == 0)
		{
			SGr_vRIRE_SOZAI->Canvas->Font->Color= clGray;
			SGr_vRIRE_SOZAI->Canvas->Brush->Color= clGray;
		}
		SGr_vRIRE_SOZAI->Canvas->FillRect(Rect);
		InflateRect(&r,-2,-2);
//�o�̓^�C�v�ɂ��t�H�[�}�b�g�ʒu����
		switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
		{
		case 0:		//�����E����
		case 1:		//�p�x
			DrawText(SGr_vRIRE_SOZAI->Canvas->Handle,sBuf.c_str(),-1,&r,DT_RIGHT); //�E��
			break;
		case 2:  	//�ǁE��
			DrawText(SGr_vRIRE_SOZAI->Canvas->Handle,sBuf.c_str(),-1,&r,DT_CENTER); //������
			break;
		default:	//����
			DrawText(SGr_vRIRE_SOZAI->Canvas->Handle,sBuf.c_str(),-1,&r,DT_LEFT); //����
			break;
		}
//�F�ɂ�锻��
		if(hCELLINFO_RIRE_SOZAI)
		{
			if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD)
	   		{
		   		switch(SGr_vRIRE_SOZAI->Canvas->Font->Color)
				{
			   	case clBlack:
			  		pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].JUDGE = 0;
			 		break;
			   	case clRed:
			   		pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].JUDGE = 1;
		  			break;
		 		default:
					pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].JUDGE = 2;
			   		break;
	   			}
	 		}
			else
   			{
  				switch(SGr_vRIRE_SOZAI->Canvas->Font->Color)
				{
				case clBlue:
				//�K�i���肪����܂�
					pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].JUDGE = 0;
					break;
				case clGray:
					pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].JUDGE = 0;
					break;
				case clRed:
					pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].JUDGE = 1;
					break;
				case clMaroon:
					pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].JUDGE = 1;
					break;
				default:
					pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].JUDGE = 2;
					break;
				}
			}
			if(sBuf.Trim() == 0) pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].JUDGE = 2;
		}
		break;
	}
	GET_HANTEI(Sender, ACol);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnDrawCell�C�x���g	�F�f�ޗ����̓��t�`�掞�������܂��B
//
//  �@�\����
//    YYYY/MM/DD�`���œ��t��`�悵�܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol          �F�ΏۃZ���̃J�����ʒu
//    int ARow          �F�ΏۃZ���̂q�n�v�ʒu
//  �@TRect &Rect       �F�Z���̈ʒu���
//  �@TGridDrawState State  : �Z���̃X�e�[�^�X�i�t�H�[�J�X�̗L�����j
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tRIRE_SOZAIDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{

   RECT r=RECT(Rect);
	AnsiString sBuf,sBuf1;
	int i1;
	sBuf = SGr_tRIRE_SOZAI->Cells[ACol][0];

    sBuf1 ="";
    //�����ȕ����͕\���ΏƂ���O���܂�
    for(i1=1;i1<=sBuf.Length();i1++)
    {
       	if(strcspn(sBuf.SubString(i1,1).c_str(),"0123456789")==0)
        {
           	sBuf1 += sBuf.SubString(i1,1);
        }
    }
	if( sBuf1.Length() != 8)
	{
		sBuf = "";
	}
	else
	{
    	sBuf = sBuf1.SubString(1,4) + "/" + sBuf1.SubString(5,2) + "/" + sBuf1.SubString(7,2);
	}
   //�Œ�Z���̔w�i�F���Z�b�g
   if(State.Contains(gdFixed)){

   }
   //�t�H�[�J�X�̂���Z���̔w�i�F���Z�b�g
   else if(State.Contains(gdFocused)){
		SGr_tRIRE_SOZAI->Canvas->Brush->Color= clHighlight;
   }

   //���ʂ̃Z���̔w�i�F���Z�b�g
   else{
       SGr_tRIRE_SOZAI->Canvas->Brush->Color= SGr_tRIRE_SOZAI->Color;
   }
   //�w�i�F�ŏ���
   SGr_tRIRE_SOZAI->Canvas->FillRect(Rect);

   //�Œ�Z���̗��̘g��`��
   if(SGr_tRIRE_SOZAI->Ctl3D&&State.Contains(gdFixed)){
       DrawEdge(SGr_tRIRE_SOZAI->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);
   }
   //�t�H�[�J�X�̂���Z���̕����F���Z�b�g
   if(State.Contains(gdFocused)){
	   SGr_tRIRE_SOZAI->Canvas->Font->Color= clHighlightText;
   }
   else{
       SGr_tRIRE_SOZAI->Canvas->Font->Color= SGr_tRIRE_SOZAI->Font->Color;
   }

   //�e�L�X�g�\���̈�̐ݒ�
   InflateRect(&r,-2,-2);

   //�e�L�X�g�̕\��
   DrawText(SGr_tRIRE_SOZAI->Canvas->Handle,sBuf.c_str(),-1,&r,0); //�E��

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnDrawCell�C�x���g	�F�f�ޑ���̓��t�`�掞�������܂��B
//
//  �@�\����
//    YYYY/MM/DD�`���œ��t��`�悵�܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol          �F�ΏۃZ���̃J�����ʒu
//    int ARow          �F�ΏۃZ���̂q�n�v�ʒu
//  �@TRect &Rect       �F�Z���̈ʒu���
//  �@TGridDrawState State  : �Z���̃X�e�[�^�X�i�t�H�[�J�X�̗L�����j
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tSOKU_SOZAIDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
   	RECT r=RECT(Rect);
	AnsiString sBuf,sBuf1;
    int i1;
	sBuf = SGr_tSOKU_SOZAI->Cells[ACol][0];

   	sBuf1="";
    //�����ȕ����͕\���ΏƂ���O���܂�
    for(i1=1;i1<=sBuf.Length();i1++)
    {
    	if(strcspn(sBuf.SubString(i1,1).c_str(),"0123456789")==0)
        {
        	sBuf1 += sBuf.SubString(i1,1);
        }
	}
	if(sBuf1.Length() != 8)
	{
		sBuf ="";
	}
	else
	{
		sBuf = sBuf1.SubString(1,4) + "/" + sBuf1.SubString(5,2) + "/" + sBuf1.SubString(7,2);
	}
   //�Œ�Z���̔w�i�F���Z�b�g
   if(State.Contains(gdFixed)){

   }
   //�t�H�[�J�X�̂���Z���̔w�i�F���Z�b�g
   else if(State.Contains(gdFocused)){
		SGr_tSOKU_SOZAI->Canvas->Brush->Color= clHighlight;
   }
   //���ʂ̃Z���̔w�i�F���Z�b�g
   else{
       SGr_tSOKU_SOZAI->Canvas->Brush->Color= SGr_tSOKU_SOZAI->Color;
   }
   //�w�i�F�ŏ���
   SGr_tSOKU_SOZAI->Canvas->FillRect(Rect);

   //�Œ�Z���̗��̘g��`��
   if(SGr_tSOKU_SOZAI->Ctl3D&&State.Contains(gdFixed)){
       DrawEdge(SGr_tSOKU_SOZAI->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);
   }
   //�t�H�[�J�X�̂���Z���̕����F���Z�b�g
   if(State.Contains(gdFocused)){
	   SGr_tSOKU_SOZAI->Canvas->Font->Color= clHighlightText;
   //���ʂ̃Z���̕����F���Z�b�g
   }
   else{
       SGr_tSOKU_SOZAI->Canvas->Font->Color= SGr_tSOKU_SOZAI->Font->Color;
   }

   //�e�L�X�g�\���̈�̐ݒ�
   InflateRect(&r,-2,-2);

   //�e�L�X�g�̕\��
   DrawText(SGr_tSOKU_SOZAI->Canvas->Handle,sBuf.c_str(),-1,&r,0); //�E��
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnDrawCell�C�x���g	�F�o�ח����̓��t�`�掞�������܂��B
//
//  �@�\����
//    YYYY/MM/DD�`���œ��t��`�悵�܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol          �F�ΏۃZ���̃J�����ʒu
//    int ARow          �F�ΏۃZ���̂q�n�v�ʒu
//  �@TRect &Rect       �F�Z���̈ʒu���
//  �@TGridDrawState State  : �Z���̃X�e�[�^�X�i�t�H�[�J�X�̗L�����j
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tRIRE_SYUKADrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
   	RECT r=RECT(Rect);
	AnsiString sBuf,sBuf1;
	int i1;
	sBuf = SGr_tRIRE_SYUKA->Cells[ACol][0];

    sBuf1="";
    //�����ȊO�̕�����͕`��ΏƂ���O���܂�
    for(i1=1;i1<=sBuf.Length();i1++)
    {
    	if(strcspn(sBuf.SubString(i1,1).c_str(),"0123456789")==0)
        {
        	sBuf1 += sBuf.SubString(i1,1);
        }
	}
    if( sBuf1.Length() != 8)
	{
		sBuf = "";
	}
	else
	{
    	sBuf = sBuf1.SubString(1,4) + "/" + sBuf1.SubString(5,2) + "/" + sBuf1.SubString(7,2);
	}
   //�Œ�Z���̔w�i�F���Z�b�g
   if(State.Contains(gdFixed)){

   }
   //�t�H�[�J�X�̂���Z���̔w�i�F���Z�b�g
   else if(State.Contains(gdFocused)){
		SGr_tRIRE_SYUKA->Canvas->Brush->Color= clHighlight;
   }
   //���ʂ̃Z���̔w�i�F���Z�b�g
   else{
       SGr_tRIRE_SYUKA->Canvas->Brush->Color= SGr_tRIRE_SYUKA->Color;
   }
   //�w�i�F�ŏ���
   SGr_tRIRE_SYUKA->Canvas->FillRect(Rect);

   //�Œ�Z���̗��̘g��`��
   if(SGr_tRIRE_SYUKA->Ctl3D&&State.Contains(gdFixed)){
       DrawEdge(SGr_tRIRE_SYUKA->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);
   }
   //�t�H�[�J�X�̂���Z���̕����F���Z�b�g
   if(State.Contains(gdFocused)){
	   SGr_tRIRE_SYUKA->Canvas->Font->Color= clHighlightText;

   //���ʂ̃Z���̕����F���Z�b�g
   }
   else{
       SGr_tRIRE_SYUKA->Canvas->Font->Color= SGr_tRIRE_SYUKA->Font->Color;
   }

   //�e�L�X�g�\���̈�̐ݒ�
   InflateRect(&r,-2,-2);

   //�e�L�X�g�̕\��
   DrawText(SGr_tRIRE_SYUKA->Canvas->Handle,sBuf.c_str(),-1,&r,0); //�E��

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnDrawCell�C�x���g	�F�o�ב���̓��t�`�掞�������܂��B
//
//  �@�\����
//    YYYY/MM/DD�`���œ��t��`�悵�܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol          �F�ΏۃZ���̃J�����ʒu
//    int ARow          �F�ΏۃZ���̂q�n�v�ʒu
//  �@TRect &Rect       �F�Z���̈ʒu���
//  �@TGridDrawState State  : �Z���̃X�e�[�^�X�i�t�H�[�J�X�̗L�����j
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tSOKU_SYUKADrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
	RECT r=RECT(Rect);
	AnsiString sBuf,sBuf1;
	int i1;
	sBuf = SGr_tSOKU_SYUKA->Cells[ACol][0];

    sBuf1="";
    //�����ȊO�͕`��Ώۂ���O���܂�
    for(i1=1;i1<=sBuf.Length();i1++)
    {
    	if(strcspn(sBuf.SubString(i1,1).c_str(),"0123456789")==0)
        {
        	sBuf1 += sBuf.SubString(i1,1);
        }
	}
    if(sBuf1.Length() != 8 )
	{
		sBuf ="";
	}
	else
	{
		sBuf = sBuf1.SubString(1,4) + "/" + sBuf1.SubString(5,2) + "/" + sBuf1.SubString(7,2);
	}
   //�Œ�Z���̔w�i�F���Z�b�g
   if(State.Contains(gdFixed)){

   }
   //�t�H�[�J�X�̂���Z���̔w�i�F���Z�b�g
   else if(State.Contains(gdFocused)){
		SGr_tSOKU_SYUKA->Canvas->Brush->Color= clHighlight;
   }
   //���ʂ̃Z���̔w�i�F���Z�b�g
   else{
       SGr_tSOKU_SYUKA->Canvas->Brush->Color= SGr_tSOKU_SYUKA->Color;
   }
   //�w�i�F�ŏ���
   SGr_tSOKU_SYUKA->Canvas->FillRect(Rect);

   //�Œ�Z���̗��̘g��`��
   if(SGr_tSOKU_SYUKA->Ctl3D&&State.Contains(gdFixed)){
       DrawEdge(SGr_tSOKU_SYUKA->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);
   }
   //�t�H�[�J�X�̂���Z���̕����F���Z�b�g
   if(State.Contains(gdFocused)){
	   SGr_tSOKU_SYUKA->Canvas->Font->Color= clHighlightText;
   //���ʂ̃Z���̕����F���Z�b�g
   }
   else{
       SGr_tSOKU_SYUKA->Canvas->Font->Color= SGr_tSOKU_SYUKA->Font->Color;
   }

   //�e�L�X�g�\���̈�̐ݒ�
   InflateRect(&r,-2,-2);

   //�e�L�X�g�̕\��
   DrawText(SGr_tSOKU_SYUKA->Canvas->Handle,sBuf.c_str(),-1,&r,0); //�E��
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnExit�C�x���g	�F�f�ޗ����̓��t�`����I������Ƃ��ɔ������܂��B
//
//  �@�\����
//    YYYY/MM/DD�`���œ��t���ĕ`�悵�܂��B
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
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tRIRE_SOZAIExit(TObject *Sender)
{
    TGridDrawState State;

    // �t�H�[�J�X���������A�I����Ԃ̕����F������ɖ߂�Ȃ��ׁA
    // �ēx�A�ʏ�̃Z���Ƃ��čĕ`�悳���܂��B
    SGr_tRIRE_SOZAIDrawCell( Sender,
                             SGr_tRIRE_SOZAI->Col,
                             SGr_tRIRE_SOZAI->Row,
                             SGr_tRIRE_SOZAI->CellRect(SGr_tRIRE_SOZAI->Col, SGr_tRIRE_SOZAI->Row),
                             State);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnExit�C�x���g	�F�f�ޗ����̃f�[�^�`����I������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �f�[�^���ĕ`�悵�܂��B
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
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vRIRE_SOZAIExit(TObject *Sender)
{
    TGridDrawState State;

    // �t�H�[�J�X���������A�I����Ԃ̕����F������ɖ߂�Ȃ��ׁA
    // �ēx�A�ʏ�̃Z���Ƃ��čĕ`�悳���܂��B
    AllGRID_DrawCell( Sender,
                             SGr_vRIRE_SOZAI->Col,
                             SGr_vRIRE_SOZAI->Row,
                             SGr_vRIRE_SOZAI->CellRect(SGr_vRIRE_SOZAI->Col, SGr_vRIRE_SOZAI->Row),
                             State);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnExit�C�x���g	�F�f�ޑ���̃f�[�^�`����I������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �f�[�^���ĕ`�悵�܂��B
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
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vSOKU_SOZAIExit(TObject *Sender)
{
    TGridDrawState State;

    // �t�H�[�J�X���������A�I����Ԃ̕����F������ɖ߂�Ȃ��ׁA
    // �ēx�A�ʏ�̃Z���Ƃ��čĕ`�悳���܂��B
    AllGRID_DrawCell( Sender,
                             SGr_vSOKU_SOZAI->Col,
                             SGr_vSOKU_SOZAI->Row,
                             SGr_vSOKU_SOZAI->CellRect(SGr_vSOKU_SOZAI->Col, SGr_vSOKU_SOZAI->Row),
                             State);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnExit�C�x���g	�F�f�ޑ���̃f�[�^�`����I������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �f�[�^���ĕ`�悵�܂��B
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
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vRIRE_SYUKAExit(TObject *Sender)
{
    TGridDrawState State;

    // �t�H�[�J�X���������A�I����Ԃ̕����F������ɖ߂�Ȃ��ׁA
    // �ēx�A�ʏ�̃Z���Ƃ��čĕ`�悳���܂��B
    AllGRID_DrawCell( Sender,
                             SGr_vRIRE_SYUKA->Col,
                             SGr_vRIRE_SYUKA->Row,
                             SGr_vRIRE_SYUKA->CellRect(SGr_vRIRE_SYUKA->Col, SGr_vRIRE_SYUKA->Row),
                             State);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnExit�C�x���g	�F�o�ב���̃f�[�^�`����I������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �f�[�^���ĕ`�悵�܂��B
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
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vSOKU_SYUKAExit(TObject *Sender)
{
    TGridDrawState State;

    // �t�H�[�J�X���������A�I����Ԃ̕����F������ɖ߂�Ȃ��ׁA
    // �ēx�A�ʏ�̃Z���Ƃ��čĕ`�悳���܂��B
    AllGRID_DrawCell( Sender,
                             SGr_vSOKU_SYUKA->Col,
                             SGr_vSOKU_SYUKA->Row,
                             SGr_vSOKU_SYUKA->CellRect(SGr_vSOKU_SYUKA->Col, SGr_vSOKU_SYUKA->Row),
                             State);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnExit�C�x���g	�F�f�ޑ���̓��t�`����I������Ƃ��ɔ������܂��B
//
//  �@�\����
//    YYYY/MM/DD�`���œ��t���ĕ`�悵�܂��B
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tSOKU_SOZAIExit(TObject *Sender)
{
    TGridDrawState State;

    // �t�H�[�J�X���������A�I����Ԃ̕����F������ɖ߂�Ȃ��ׁA
    // �ēx�A�ʏ�̃Z���Ƃ��čĕ`�悳���܂��B
    SGr_tSOKU_SOZAIDrawCell( Sender,
                             SGr_tSOKU_SOZAI->Col,
                             SGr_tSOKU_SOZAI->Row,
                             SGr_tSOKU_SOZAI->CellRect(SGr_tSOKU_SOZAI->Col, SGr_tSOKU_SOZAI->Row),
                             State);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnExit�C�x���g	:�o�ח����̓��t�`����I������Ƃ��ɔ������܂��B
//
//  �@�\����
//    YYYY/MM/DD�`���œ��t���ĕ`�悵�܂��B
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tRIRE_SYUKAExit(TObject *Sender)
{
    TGridDrawState State;

    // �t�H�[�J�X���������A�I����Ԃ̕����F������ɖ߂�Ȃ��ׁA
    // �ēx�A�ʏ�̃Z���Ƃ��čĕ`�悳���܂��B
    SGr_tRIRE_SYUKADrawCell( Sender,
                             SGr_tRIRE_SYUKA->Col,
                             SGr_tRIRE_SYUKA->Row,
                             SGr_tRIRE_SYUKA->CellRect(SGr_tRIRE_SYUKA->Col, SGr_tRIRE_SYUKA->Row),
                             State);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnExit�C�x���g	:�o�ב���̓��t�`����I������Ƃ��ɔ������܂��B
//
//  �@�\����
//    YYYY/MM/DD�`���œ��t���ĕ`�悵�܂��B
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tSOKU_SYUKAExit(TObject *Sender)
{
    TGridDrawState State;

    // �t�H�[�J�X���������A�I����Ԃ̕����F������ɖ߂�Ȃ��ׁA
    // �ēx�A�ʏ�̃Z���Ƃ��čĕ`�悳���܂��B
    SGr_tSOKU_SYUKADrawCell( Sender,
                             SGr_tSOKU_SYUKA->Col,
                             SGr_tSOKU_SYUKA->Row,
                             SGr_tSOKU_SYUKA->CellRect(SGr_tSOKU_SYUKA->Col, SGr_tSOKU_SYUKA->Row),
                             State);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    �f�X�g���N�^�C�x���g	:�t�H�[�����������ォ�������Ƃ��ɔ������܂��B
//
//  �@�\����
//    ���I�R���g���[�����������܂��B
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
__fastcall TForm1::~TForm1()
{
    int i2;

    for(i2=0 ;i2<iPnl_InsKikiNameCnt;i2++)
    {
        delete Form1->Pnl_InsKikiName[i2];

    }

    for(i2=0 ;i2<iPnl_InsNoCnt;i2++)
    {
        delete Form1->Pnl_InsNo[i2];
    }

    for(i2=0 ;i2<iOrCnt;i2++)
    {
        delete Form1->Pnl_InsName[i2];
    }

    for(i2=0 ;i2<iOrCnt;i2++)
    {
        delete Form1->Pnl_SubBase[i2];
    }

    for(i2 = 0 ; i2 < iSOKU_MEMO_CNT ;i2++)
    {
    	delete Mem_vSOKU_MEMO[i2];
    }

    for(i2 = 0 ; i2 < iRIRE_MEMO_CNT ;i2++)
    {
    	delete Mem_vRIRE_MEMO[i2];
    }

	// �������̊J��
	if( hCELLINFO_SOKU_SYUKA ){
        GlobalUnlock( hCELLINFO_SOKU_SYUKA );
        hCELLINFO_SOKU_SYUKA = GlobalFree( hCELLINFO_SOKU_SYUKA );
    }
	// �������̊J��
	if( hCELLINFO_RIRE_SYUKA ){
        GlobalUnlock( hCELLINFO_RIRE_SYUKA );
        hCELLINFO_RIRE_SYUKA = GlobalFree( hCELLINFO_RIRE_SYUKA );
    }
	// �������̊J��
	if( hCELLINFO_SOKU_SOZAI ){
        GlobalUnlock( hCELLINFO_SOKU_SOZAI );
        hCELLINFO_SOKU_SOZAI = GlobalFree( hCELLINFO_SOKU_SOZAI );
    }
	// �������̊J��
	if( hCELLINFO_RIRE_SOZAI ){
        GlobalUnlock( hCELLINFO_RIRE_SOZAI );
        hCELLINFO_RIRE_SOZAI = GlobalFree( hCELLINFO_RIRE_SOZAI );
    }

/* k.y 2003.05.17
	// �������̊J��
	if( hInfoGlaph ){
        GlobalUnlock( hInfoGlaph );
        hInfoGlaph = GlobalFree( hInfoGlaph );
    }
*/

	//2003.05.08 E.Takase Add��
	delete sRIREKI_LOT;
    delete sHT_LOT;
    delete sShiji_Data;

	//for(i2=0;i2<iContCnt;i2++)
    //{
    //    delete Lab_KOMK_NM[i2];
    //    delete Lab_TANI[i2];
    //    delete Lab_KIKA[i2];
    //    delete Lab_UPKIKA[i2];
    //    delete Lab_LOKIKA[i2];
    //}
    //for(i2=0 ; i2 < iPnl_InsKikiNameCnt; i2++)
    //{
	//	delete Form1->Lab_KIKI_NM[i2];
    //}

/* k.y 2003.05.17
	// �������̊J��
	if(hInfoGlaph!=NULL){
		GlobalUnlock(hInfoGlaph);
		GlobalFree(hInfoGlaph);
	}
	if(hKSM01_DATA!=NULL){
		GlobalUnlock(hKSM01_DATA);
		GlobalFree(hKSM01_DATA);
	}
	if(hSYUKA_DATA!=NULL){
		GlobalUnlock(hSYUKA_DATA);
		GlobalFree(hSYUKA_DATA);
	}
	if(hRIREKI_DATA!=NULL){
		GlobalUnlock(hRIREKI_DATA);
		GlobalFree(hRIREKI_DATA);
	}
	if(hORDATA!=NULL){
		GlobalUnlock(hORDATA);
		GlobalFree(hORDATA);
	}
*/
	if(hSOKU_KSD01DATA!=NULL){
		GlobalUnlock(hSOKU_KSD01DATA);
		GlobalFree(hSOKU_KSD01DATA);
	}
	if(hSOKU_KSD01_DATA!=NULL){
		GlobalUnlock(hSOKU_KSD01_DATA);
		GlobalFree(hSOKU_KSD01_DATA);
	}
	if(hRIRE_KSD01DATA!=NULL){
		GlobalUnlock(hRIRE_KSD01DATA);
		GlobalFree(hRIRE_KSD01DATA);
	}
/* k.y 2003.05.17
	if(hSOZAI_OR_DATA!=NULL){
		GlobalUnlock(hSOZAI_OR_DATA);
		GlobalFree(hSOZAI_OR_DATA);
	}
*/
	if(hRIRE_KSD01_DATA!=NULL){
		GlobalUnlock(hRIRE_KSD01_DATA);
		GlobalFree(hRIRE_KSD01_DATA);
	}
	//2003.05.08 E.Takase Add��

	CommClose(1);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnSelectCell�C�x���g	�F�S�����O���b�h���̃Z����I������Ɣ������܂��B
//
//  �@�\����
//    �����Z���̑I���̋֎~��Z���̑I���Ŕ�������O���t�`��֐��̌Ăяo�����s���܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol          �F�ΏۃZ���̃J�����ʒu
//    int ARow          �F�ΏۃZ���̂q�n�v�ʒu
//  �@bool &CanSelect   �F�Z���̑I���A�L���^�������s���܂�
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::AllGRID_SelectCell(TObject *Sender,
      int ACol, int ARow, bool &CanSelect)
{
	int i1;
	int iGridTag,iRow;
	bool bNum;				//�K�i�����l�H�t���O

	AnsiString sBuf;
    //�������̓Z���̈ړ��ɐ������������Ȃ�
    if(bNowF7 == true) return;

	bNum = false;
 	if(Sender == SGr_vSOKU_SYUKA)
	{
    	SGr_vSOKU_SYUKA->Options << goEditing;

 		iGridTag=SGr_vSOKU_SYUKA->Tag;
/*
        if((Form1->SGr_vSOKU_SYUKA->Cells[ACol][ARow] == "�s�v" && bKASOU_MOVE == false)
			|| !hCELLINFO_SOKU_SYUKA)
        {
        	CanSelect = false;
            Delete_InplaceEdit(Sender);		// �ҏW�E�B���h�E�𖳌��ɂ��܂�
            return;
        }
*/
        //if(((	AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].KOMK_NO).ToIntDef(0) == 0)
/* 2005.09.29 Y.Sano Add start	*/
/* ��x���������Ă��Ȃ���ԂŃA�N�Z�X���ɂ�����	*/
/* �A�v���P�[�V�����G���[��������������			*/
/* NULL�����ǉ�����							*/
		if( pCELLINFO_RIRE_SOZAI == NULL ) return;
/* 2005.09.29 Y.Sano Add end	*/
        if(((	pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].INS_ON == false)
        ||(	AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].SOKU_FLG).ToIntDef(0) == 0))
         && bKASOU_MOVE == false)
        {
            Delete_InplaceEdit(Sender);		// �ҏW�E�B���h�E�𖳌��ɂ��܂�
        	CanSelect = false;
            return;
        }
		if( SGr_vSOKU_SYUKA->RowCount < 2 )
		{
        	CanSelect = false;
            Delete_InplaceEdit(Sender);		// �ҏW�E�B���h�E�𖳌��ɂ��܂�
            return;
		}
	}
 	if(Sender == SGr_vSOKU_SOZAI)
	{
    	SGr_vSOKU_SOZAI->Options << goEditing;

		iGridTag=SGr_vSOKU_SOZAI->Tag;
/*
        if((Form1->SGr_vSOKU_SOZAI->Cells[ACol][ARow] == "�s�v" && bKASOU_MOVE == false)
			|| !hCELLINFO_SOKU_SOZAI)
		{
            Delete_InplaceEdit(Sender);		// �ҏW�E�B���h�E�𖳌��ɂ��܂�
        	CanSelect = false;
            return;
        }
*/
        //if(((	AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].KOMK_NO).ToIntDef(0) == 0)
/* 2005.09.29 Y.Sano Add start	*/
/* ��x���������Ă��Ȃ���ԂŃA�N�Z�X���ɂ�����	*/
/* �A�v���P�[�V�����G���[��������������			*/
/* NULL�����ǉ�����							*/
        if( pCELLINFO_SOKU_SOZAI == NULL ) return;
/* 2005.09.29 Y.Sano Add end	*/
        if(((	pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].INS_ON == false)
        ||  (	AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].SOKU_FLG).ToIntDef(0) == 0 ))
        && bKASOU_MOVE == false)
        {
            Delete_InplaceEdit(Sender);		// �ҏW�E�B���h�E�𖳌��ɂ��܂�
        	CanSelect = false;
            return;
        }
		if( SGr_vSOKU_SOZAI->RowCount < 2 )
		{
        	CanSelect = false;
            Delete_InplaceEdit(Sender);		// �ҏW�E�B���h�E�𖳌��ɂ��܂�
            return;
		}
	}
 	if(Sender == SGr_vRIRE_SYUKA)
	{
    	SGr_vRIRE_SYUKA->Options << goEditing;

 		iGridTag=SGr_vRIRE_SYUKA->Tag;
/*
        if((Form1->SGr_vRIRE_SYUKA->Cells[ACol][ARow] == "�s�v" && bKASOU_MOVE == false)
			|| !hCELLINFO_RIRE_SYUKA)
        {
            Delete_InplaceEdit(Sender);		// �ҏW�E�B���h�E�𖳌��ɂ��܂�
        	CanSelect = false;
            return;
        }
*/
//        if(((	AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].KOMK_NO).ToIntDef(0) == 0)
/* 2005.09.29 Y.Sano Add start	*/
/* ��x���������Ă��Ȃ���ԂŃA�N�Z�X���ɂ�����	*/
/* �A�v���P�[�V�����G���[��������������			*/
/* NULL�����ǉ�����							*/
        if( pCELLINFO_RIRE_SYUKA == NULL ) return;
/* 2005.09.29 Y.Sano Add end	*/
        if(((	pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].INS_ON == false)
        ||  (	AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].SOKU_FLG).ToIntDef(0) == 0 ))
        && bKASOU_MOVE == false)
        {
            Delete_InplaceEdit(Sender);		// �ҏW�E�B���h�E�𖳌��ɂ��܂�
        	CanSelect = false;
            return;
        }
		if( SGr_vRIRE_SYUKA->RowCount < 2 )
		{
        	CanSelect = false;
            Delete_InplaceEdit(Sender);		// �ҏW�E�B���h�E�𖳌��ɂ��܂�
            return;
		}
	}
 	if(Sender == SGr_vRIRE_SOZAI)
	{
    	SGr_vRIRE_SOZAI->Options << goEditing;

 		iGridTag=SGr_vRIRE_SOZAI->Tag;
/*
        if((Form1->SGr_vRIRE_SOZAI->Cells[ACol][ARow] == "�s�v" && bKASOU_MOVE == false)
			|| !hCELLINFO_RIRE_SOZAI)
        {
            Delete_InplaceEdit(Sender);		// �ҏW�E�B���h�E�𖳌��ɂ��܂�
        	CanSelect = false;
            return;
        }
*/
//        if(((	AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].KOMK_NO).ToIntDef(0) == 0)
/* 2005.09.29 Y.Sano Add start	*/
/* ��x���������Ă��Ȃ���ԂŃA�N�Z�X���ɂ�����	*/
/* �A�v���P�[�V�����G���[��������������			*/
/* NULL�����ǉ�����							*/
		if( pCELLINFO_RIRE_SOZAI == NULL ) return;
/* 2005.09.29 Y.Sano Add end	*/
        if(((	pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].INS_ON == false)
        ||  (	AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].SOKU_FLG).ToIntDef(0) == 0 ))
        && bKASOU_MOVE == false)
        {
            Delete_InplaceEdit(Sender);		// �ҏW�E�B���h�E�𖳌��ɂ��܂�
        	CanSelect = false;
            return;
        }
		if( SGr_vRIRE_SOZAI->RowCount < 2 )
		{
        	CanSelect = false;
            Delete_InplaceEdit(Sender);		// �ҏW�E�B���h�E�𖳌��ɂ��܂�
            return;
		}
	}
	if( ARow == 0 )
//	if(ARow == 0 && bHANTEI_DISP == false)
    {
        Delete_InplaceEdit(Sender);		// �ҏW�E�B���h�E�𖳌��ɂ��܂�
		CanSelect = false;
		return;
    }

    CanSelect = true;
    //�O���t�`�悷��ۂ̃Z���̏������W���܂�
    i1 = Get_GRAPHSTART_Info(ARow,ACol,iGridTag);
    switch(iGridTag)
    {
	case 1:
		iRow = SGr_vSOKU_SYUKA->RowCount;
    	sBuf = pCELLINFO_SOKU_SYUKA[ACol*iRow+ARow].KIKI_NO;
		if (AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRow+ARow].VALUE_TYPE).ToIntDef(0) < 2 ) bNum = true;
        iRow_vSOKU_SYUKA = ARow;
        iCol_vSOKU_SYUKA = ACol;
        break;
	case 2:
		iRow = SGr_vRIRE_SYUKA->RowCount;
    	sBuf = pCELLINFO_RIRE_SYUKA[ACol*iRow+ARow].KIKI_NO;
		if (AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRow+ARow].VALUE_TYPE).ToIntDef(0) < 2 ) bNum = true;
        iRow_vRIRE_SYUKA = ARow;
        iCol_vRIRE_SYUKA = ACol;
        break;
	case 3:
		iRow = SGr_vSOKU_SOZAI->RowCount;
    	sBuf = pCELLINFO_SOKU_SOZAI[ACol*iRow+ARow].KIKI_NO;
		if (AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRow+ARow].VALUE_TYPE).ToIntDef(0) < 2 ) bNum = true;
        iRow_vSOKU_SOZAI = ARow;
        iCol_vSOKU_SOZAI = ACol;
        break;
	case 4:
		iRow = SGr_vRIRE_SOZAI->RowCount;
    	sBuf = pCELLINFO_RIRE_SOZAI[ACol*iRow+ARow].KIKI_NO;
		if (AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRow+ARow].VALUE_TYPE).ToIntDef(0) < 2 ) bNum = true;
        iRow_vRIRE_SOZAI = ARow;
        iCol_vRIRE_SOZAI = ACol;
        break;
    }
    if(bCellWrite == true ) return;
    //�O���t�`����J�n���܂�
    Get_GRAPHLOT(i1,ACol,iGridTag);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnKeyPress�C�x���g	�F�o�ב���Z����ŒP��̕����L�[���͂�����Ɣ������܂��B
//
//  �@�\����
//    �A�b�v�f�[�g�t���O�̍X�V�B
//    �����񒷂̊m�F
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    char &Key         : char�^�̃L�[�R�[�h
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vSOKU_SYUKAKeyPress(TObject *Sender, char &Key)
{
	int iRow,iCol,iRowCount;
    AnsiString sBuf,sDATE,sTIME;
//    MSG msg;

	iCol = SGr_vSOKU_SYUKA->Col;
	iRow = SGr_vSOKU_SYUKA->Row;
    iRowCount = SGr_vSOKU_SYUKA->RowCount;
    if(iRowCount < 2 ) return;
    sBuf = SGr_vSOKU_SYUKA->Cells[iCol][iRow];
//    strcpy(pCELLINFO_SOKU_SYUKA[iCol*SGr_vSOKU_SYUKA->RowCount +iRow].RESULT,sBuf.c_str());
	if( Key == VK_RETURN ) GridSetPointMove(Sender,Key);

    //�����񒷃`�F�b�N
    //2003.05.17 E.Takase Add��
    bool bRtn = ChkSize( hCELLINFO_SOKU_SYUKA, iCol*SGr_vSOKU_SYUKA->RowCount+iRow, sizeof(struct CELLINFO_DATA));
    if ( bRtn ) {
		int iVALUE_TYPE = AnsiString(pCELLINFO_SOKU_SYUKA[iCol*SGr_vSOKU_SYUKA->RowCount+iRow].VALUE_TYPE).ToIntDef(0);
        int iLenMAX = 14;
        if ( iVALUE_TYPE == 2 ) {
        	iLenMAX = 1;
        }
	    ChkInputData( sBuf, iVALUE_TYPE, Sender, Key, iLenMAX);
    }
    //RETURN�L�[�ȊO�iReturn�L�[�͖{�C�x���g�ɓ����Ă��邽�߃`�F�b�N���Ă��܂��j
	//2003.05.17 E.Takase Add��
    if(Key != VK_RETURN && bCellWrite == false)
    {
        //�A�b�v�f�[�g�t���O���͂��߂Ƃ��āA���t���̍X�V���s���܂�
        if( hSOKU_KSD01_DATA && hCELLINFO_SOKU_SYUKA )
        {
            pSOKU_KSD01_DATA[iCol].UPD_FLG = true;          //UPDATE�t���O�iRETURN KEY�ȊO�Ȃ�H�j
            if(SGr_vSOKU_SYUKA->Color != (TColor)0x00DDDDDD)   //�����ʂł͍X�V�ғ��̏��������͍s��Ȃ�
            {
            //��\�X�V�҂̏�������
                strcpy(pSOKU_KSD01_DATA[iCol].UPDCHR 	 ,AnsiString(Form1->USER_COD).c_str());
            //�X�V�҂̏�������(�Z�����j
                strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDCHR , AnsiString(Form1->USER_COD).c_str());
            //2003.05.17 E.Takase Add��
                strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDNAME , AnsiString(Form1->USER_NAM).c_str());
            //2003.05.17 E.Takase Add��
            //���t�̏�������(�Z�����j
                sDATE = FormatDateTime("yyyymmdd",Date());
                sTIME = FormatDateTime("hhmm",TDateTime::CurrentTime());
                strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDYMD,sDATE.c_str());
                strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDTIM,sTIME.c_str());
            //���o�^�Ȃ瑪����A�o�^�����X�V�i�V�K�j����
                if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].SKTYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].SKTYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].ADDYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].ADDYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].ADDTIM).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].ADDTIM,sTIME.c_str());
                }
            }
        }
    }
	iCol = SGr_vSOKU_SYUKA->Col;
	iRow = SGr_vSOKU_SYUKA->Row;
//	AllGRID_SelectCell(Sender,iCol,iRow, blnHoge);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�o�ב���O���b�h��ŊO���v���킩��̓��͂��󂯂܂�
//
//  �@�\����
//    �A�b�v�f�[�g�t���O�̍X�V�B
//    �����񒷂̊m�F
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
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vSOKU_SYUKAComPress(void)
{
	int iRow,iCol,iRowCount;
    AnsiString sBuf,sDATE,sTIME;

	iCol = SGr_vSOKU_SYUKA->Col;
	iRow = SGr_vSOKU_SYUKA->Row;
    iRowCount = SGr_vSOKU_SYUKA->RowCount;
    sBuf = SGr_vSOKU_SYUKA->Cells[iCol][iRow];
    if( hSOKU_KSD01_DATA && hCELLINFO_SOKU_SYUKA )
    {
        pSOKU_KSD01_DATA[iCol].UPD_FLG = true;          //UPDATE�t���O�iRETURN KEY�ȊO�Ȃ�H�j
        if(SGr_vSOKU_SYUKA->Color != (TColor)0x00DDDDDD)   //�����ʂł͍X�V�ғ��̏��������͍s��Ȃ�
        {
        //��\�X�V�҂̏�������
            strcpy(pSOKU_KSD01_DATA[iCol].UPDCHR 	 ,AnsiString(Form1->USER_COD).c_str());
        //�X�V�҂̏�������(�Z�����j
            strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDCHR , AnsiString(Form1->USER_COD).c_str());
        //2003.05.17 E.Takase Add��
            strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDNAME , AnsiString(Form1->USER_NAM).c_str());
        //2003.05.17 E.Takase Add��
        //���t�̏�������(�Z�����j
            sDATE = FormatDateTime("yyyymmdd",Date());
            sTIME = FormatDateTime("hhmm",TDateTime::CurrentTime());
            strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDYMD,sDATE.c_str());
            strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDTIM,sTIME.c_str());
        //���o�^�Ȃ瑪����A�o�^�����X�V�i�V�K�j����
            if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].SKTYMD).Trim().Length() == 0)
            {
                strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].SKTYMD,sDATE.c_str());
            }
            if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].ADDYMD).Trim().Length() == 0)
            {
                strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].ADDYMD,sDATE.c_str());
            }
            if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].ADDTIM).Trim().Length() == 0)
            {
                strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].ADDTIM,sTIME.c_str());
            }
        }
    }
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnKeyPress�C�x���g	�F�f�ޑ���Z����ŒP��̕����L�[���͂�����Ɣ������܂��B
//
//  �@�\����
//    �A�b�v�f�[�g�t���O�̍X�V�B
//    �����񒷂̊m�F
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    char &Key         : char�^�̃L�[�R�[�h
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vSOKU_SOZAIKeyPress(TObject *Sender, char &Key)
{
	int iRow,iCol,iRowCount;
    AnsiString sBuf,sDATE,sTIME;
    bool blnHoge=true;

	iCol = SGr_vSOKU_SOZAI->Col;
	iRow = SGr_vSOKU_SOZAI->Row;
	iRowCount = SGr_vSOKU_SOZAI->RowCount;
    if(iRowCount < 2 ) return;
    sBuf = SGr_vSOKU_SOZAI->Cells[iCol][iRow];
//    strcpy(pCELLINFO_SOKU_SOZAI[iCol*SGr_vSOKU_SOZAI->RowCount +iRow].RESULT,sBuf.c_str());
	if( Key == VK_RETURN ) GridSetPointMove(Sender,Key);

    //2003.05.17 E.Takase Add��
    bool bRtn = ChkSize( hCELLINFO_SOKU_SOZAI, iCol*SGr_vSOKU_SOZAI->RowCount+iRow, sizeof(struct CELLINFO_DATA));
    if ( bRtn ) {
		int iVALUE_TYPE = AnsiString(pCELLINFO_SOKU_SOZAI[iCol*SGr_vSOKU_SOZAI->RowCount+iRow].VALUE_TYPE).ToIntDef(0);
        int iLenMAX = 14;
        if ( iVALUE_TYPE == 2 ) {
        	iLenMAX = 1;
        }
	    ChkInputData( sBuf, iVALUE_TYPE, Sender, Key, iLenMAX);
    }
	//2003.05.17 E.Takase Add��

    if(Key != VK_RETURN && bCellWrite == false)
    {
        if( hSOKU_KSD01_DATA && hCELLINFO_SOKU_SOZAI)
        {
            pSOKU_KSD01_DATA[iCol].UPD_FLG = true;          //UPDATE�t���O�iRETURN KEY�ȊO�Ȃ�H�j
            if(SGr_vSOKU_SOZAI->Color != (TColor)0x00DDDDDD)   //�����ʂł͍X�V�ғ��̏��������͍s��Ȃ�
            {
            //��\�X�V�҂̏�������
                strcpy(pSOKU_KSD01_DATA[iCol].UPDCHR 	 ,AnsiString(Form1->USER_COD).c_str());
            //�X�V�҂̏�������(�Z�����j
                strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDCHR , AnsiString(Form1->USER_COD).c_str());
            //2003.05.17 E.Takase Add��
                strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDNAME , AnsiString(Form1->USER_NAM).c_str());
            //2003.05.17 E.Takase Add��
            //���t�̏�������(�Z�����j
                sDATE = FormatDateTime("yyyymmdd",Date());
                sTIME = FormatDateTime("hhmm",TDateTime::CurrentTime());
                strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDYMD,sDATE.c_str());
                strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDTIM,sTIME.c_str());
            //���o�^�Ȃ瑪����A�o�^�����X�V�i�V�K�j����
                if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].SKTYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].SKTYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].ADDYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].ADDYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].ADDTIM).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].ADDTIM,sTIME.c_str());
                }
            }
        }
    }
	iCol = SGr_vSOKU_SOZAI->Col;
	iRow = SGr_vSOKU_SOZAI->Row;
	AllGRID_SelectCell(Sender,iCol,iRow, blnHoge);
}
//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�ޑ���O���b�h��ŊO���v���킩��̓��͂��󂯂܂�
//
//  �@�\����
//    �A�b�v�f�[�g�t���O�̍X�V�B
//    �����񒷂̊m�F
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
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vSOKU_SOZAIComPress(void)
{
	int iRow,iCol,iRowCount;
    AnsiString sBuf,sDATE,sTIME;

	iCol = SGr_vSOKU_SOZAI->Col;
	iRow = SGr_vSOKU_SOZAI->Row;
	iRowCount = SGr_vSOKU_SOZAI->RowCount;
    sBuf = SGr_vSOKU_SOZAI->Cells[iCol][iRow];
//    strcpy(pCELLINFO_SOKU_SOZAI[iCol*SGr_vSOKU_SOZAI->RowCount +iRow].RESULT,sBuf.c_str());

        if( hSOKU_KSD01_DATA && hCELLINFO_SOKU_SOZAI)
        {
            pSOKU_KSD01_DATA[iCol].UPD_FLG = true;          //UPDATE�t���O�iRETURN KEY�ȊO�Ȃ�H�j
            if(SGr_vSOKU_SOZAI->Color != (TColor)0x00DDDDDD)   //�����ʂł͍X�V�ғ��̏��������͍s��Ȃ�
            {
            //��\�X�V�҂̏�������
                strcpy(pSOKU_KSD01_DATA[iCol].UPDCHR 	 ,AnsiString(Form1->USER_COD).c_str());
            //�X�V�҂̏�������(�Z�����j
                strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDCHR , AnsiString(Form1->USER_COD).c_str());
            //2003.05.17 E.Takase Add��
                strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDNAME , AnsiString(Form1->USER_NAM).c_str());
            //2003.05.17 E.Takase Add��
            //���t�̏�������(�Z�����j
                sDATE = FormatDateTime("yyyymmdd",Date());
                sTIME = FormatDateTime("hhmm",TDateTime::CurrentTime());
                strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDYMD,sDATE.c_str());
                strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDTIM,sTIME.c_str());
            //���o�^�Ȃ瑪����A�o�^�����X�V�i�V�K�j����
                if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].SKTYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].SKTYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].ADDYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].ADDYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].ADDTIM).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].ADDTIM,sTIME.c_str());
                }
            }
        }
}
//---------------------------------------------------------------------------
//
//  �T�v
//    OnKeyPress�C�x���g	�F���𑪒�Z����ŒP��̕����L�[���͂�����Ɣ������܂��B
//
//  �@�\����
//    �A�b�v�f�[�g�t���O�̍X�V�B
//    �����񒷂̊m�F
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    char &Key         : char�^�̃L�[�R�[�h
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vRIRE_SYUKAKeyPress(TObject *Sender, char &Key)
{
	int iRow,iCol,iRowCount;
    AnsiString sBuf,sDATE,sTIME;
    bool blnHoge=true;

    if(Form1->iRIRE_CNT == 0) return;
	iCol = SGr_vRIRE_SYUKA->Col;
	iRow = SGr_vRIRE_SYUKA->Row;
	iRowCount = SGr_vRIRE_SYUKA->RowCount;
    sBuf = SGr_vRIRE_SYUKA->Cells[iCol][iRow];
	if( Key == VK_RETURN ) GridSetPointMove(Sender,Key);

    //2003.05.17 E.Takase Add��
    bool bRtn = ChkSize( hCELLINFO_RIRE_SYUKA, iCol*SGr_vRIRE_SYUKA->RowCount+iRow, sizeof(struct CELLINFO_DATA));
    if ( bRtn ) {
		int iVALUE_TYPE = AnsiString(pCELLINFO_RIRE_SYUKA[iCol*SGr_vRIRE_SYUKA->RowCount+iRow].VALUE_TYPE).ToIntDef(0);
        int iLenMAX = 14;
        if ( iVALUE_TYPE == 2 ) {
        	iLenMAX = 1;
        }
	    ChkInputData( sBuf, iVALUE_TYPE, Sender, Key, iLenMAX);
    }
	//2003.05.17 E.Takase Add��

    if(Key != VK_RETURN && bCellWrite == false )
    {
        if( hRIRE_KSD01_DATA && hCELLINFO_RIRE_SYUKA)
        {
            pRIRE_KSD01_DATA[iCol].UPD_FLG = true;          //UPDATE�t���O�iRETURN KEY�ȊO�Ȃ�H�j
            if(SGr_vRIRE_SYUKA->Color != (TColor)0x00DDDDDD)   //�����ʂł͍X�V�ғ��̏��������͍s��Ȃ�
            {
            //��\�X�V�҂̏�������
                strcpy(pRIRE_KSD01_DATA[iCol].UPDCHR 	 ,AnsiString(Form1->USER_COD).c_str());
            //�X�V�҂̏�������(�Z�����j
                strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDCHR , AnsiString(Form1->USER_COD).c_str());
            //2003.05.17 E.Takase Add��
                strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDNAME , AnsiString(Form1->USER_NAM).c_str());
            //2003.05.17 E.Takase Add��
            //���t�̏�������(�Z�����j
                sDATE = FormatDateTime("yyyymmdd",Date());
                sTIME = FormatDateTime("hhmm",TDateTime::CurrentTime());
                strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDYMD,sDATE.c_str());
                strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDTIM,sTIME.c_str());
            //���o�^�Ȃ瑪����A�o�^�����X�V�i�V�K�j����
                if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].SKTYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].SKTYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].ADDYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].ADDYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].ADDTIM).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].ADDTIM,sTIME.c_str());
                }
            }       
        }
    }
	iCol = SGr_vRIRE_SYUKA->Col;
	iRow = SGr_vRIRE_SYUKA->Row;
	AllGRID_SelectCell(Sender,iCol,iRow, blnHoge);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�o�ח����O���b�h��ŊO���v���킩��̓��͂��󂯂܂�
//
//  �@�\����
//    �A�b�v�f�[�g�t���O�̍X�V�B
//    �����񒷂̊m�F
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
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vRIRE_SYUKAComPress(void)
{
	int iRow,iCol,iRowCount;
    AnsiString sBuf,sDATE,sTIME;

	iCol = SGr_vRIRE_SYUKA->Col;
	iRow = SGr_vRIRE_SYUKA->Row;
	iRowCount = SGr_vRIRE_SYUKA->RowCount;
    sBuf = SGr_vRIRE_SYUKA->Cells[iCol][iRow];

        if( hRIRE_KSD01_DATA && hCELLINFO_RIRE_SYUKA)
        {
            pRIRE_KSD01_DATA[iCol].UPD_FLG = true;          //UPDATE�t���O�iRETURN KEY�ȊO�Ȃ�H�j
            if(SGr_vRIRE_SYUKA->Color != (TColor)0x00DDDDDD)   //�����ʂł͍X�V�ғ��̏��������͍s��Ȃ�
            {
            //��\�X�V�҂̏�������
                strcpy(pRIRE_KSD01_DATA[iCol].UPDCHR 	 ,AnsiString(Form1->USER_COD).c_str());
            //�X�V�҂̏�������(�Z�����j
                strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDCHR , AnsiString(Form1->USER_COD).c_str());
            //2003.05.17 E.Takase Add��
                strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDNAME , AnsiString(Form1->USER_NAM).c_str());
            //2003.05.17 E.Takase Add��
            //���t�̏�������(�Z�����j
                sDATE = FormatDateTime("yyyymmdd",Date());
                sTIME = FormatDateTime("hhmm",TDateTime::CurrentTime());
                strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDYMD,sDATE.c_str());
                strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDTIM,sTIME.c_str());
            //���o�^�Ȃ瑪����A�o�^�����X�V�i�V�K�j����
                if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].SKTYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].SKTYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].ADDYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].ADDYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].ADDTIM).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].ADDTIM,sTIME.c_str());
                }
            }
        }
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnKeyPress�C�x���g	�F����f�ރZ����ŒP��̕����L�[���͂�����Ɣ������܂��B
//
//  �@�\����
//    �A�b�v�f�[�g�t���O�̍X�V�B
//    �����񒷂̊m�F
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    char &Key         : char�^�̃L�[�R�[�h
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vRIRE_SOZAIKeyPress(TObject *Sender, char &Key)
{
	int iRow,iCol,iRowCount;
    AnsiString sBuf,sTIME,sDATE;
    bool blnHoge=true;

    if(iRIRE_CNT == 0) return;
	iCol = SGr_vRIRE_SOZAI->Col;
	iRow = SGr_vRIRE_SOZAI->Row;
	iRowCount = SGr_vRIRE_SOZAI->RowCount;
    sBuf = SGr_vRIRE_SOZAI->Cells[iCol][iRow];
	if( Key == VK_RETURN ) GridSetPointMove(Sender,Key);

    //2003.05.17 E.Takase Add��
    bool bRtn = ChkSize( hCELLINFO_RIRE_SOZAI, iCol*SGr_vRIRE_SOZAI->RowCount+iRow, sizeof(struct CELLINFO_DATA));
    if ( bRtn ) {
		int iVALUE_TYPE = AnsiString(pCELLINFO_RIRE_SOZAI[iCol*SGr_vRIRE_SOZAI->RowCount+iRow].VALUE_TYPE).ToIntDef(0);
        int iLenMAX = 14;
        if ( iVALUE_TYPE == 2 ) {
        	iLenMAX = 1;
        }
	    ChkInputData( sBuf, iVALUE_TYPE, Sender, Key, iLenMAX);
    }
	//2003.05.17 E.Takase Add��

    if(Key != VK_RETURN && bCellWrite == false )
    {
        if( hRIRE_KSD01_DATA && hCELLINFO_RIRE_SOZAI)
        {
            pRIRE_KSD01_DATA[iCol].UPD_FLG = true;              //UPDATE�t���O�iRETURN KEY�ȊO�Ȃ�H�j
            if(SGr_vRIRE_SOZAI->Color != (TColor)0x00DDDDDD)    //�����ʂł͍X�V�ғ��̏��������͍s��Ȃ�
            {
            //��\�X�V�҂̏�������
                strcpy(pRIRE_KSD01_DATA[iCol].UPDCHR 	 ,AnsiString(Form1->USER_COD).c_str());
            //�X�V�҂̏�������(�Z�����j
                strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDCHR , AnsiString(Form1->USER_COD).c_str());
            //2003.05.17 E.Takase Add��
                strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDNAME , AnsiString(Form1->USER_NAM).c_str());
            //2003.05.17 E.Takase Add��
            //���t�̏�������(�Z�����j
                sDATE = FormatDateTime("yyyymmdd",Date());
                sTIME = FormatDateTime("hhmm",TDateTime::CurrentTime());
                strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDYMD,sDATE.c_str());
                strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDTIM,sTIME.c_str());
            //���o�^�Ȃ瑪����A�o�^�����X�V�i�V�K�j����
                if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].SKTYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].SKTYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].ADDYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].ADDYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].ADDTIM).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].ADDTIM,sTIME.c_str());
                }
            }
        }
    }
	iCol = SGr_vRIRE_SOZAI->Col;
	iRow = SGr_vRIRE_SOZAI->Row;
	AllGRID_SelectCell(Sender,iCol,iRow, blnHoge);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�ޗ����O���b�h��ŊO���v���킩��̓��͂��󂯂܂�
//
//  �@�\����
//    �A�b�v�f�[�g�t���O�̍X�V�B
//    �����񒷂̊m�F
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
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vRIRE_SOZAIComPress(void)
{
	int iRow,iCol,iRowCount;
    AnsiString sBuf,sTIME,sDATE;

	iCol = SGr_vRIRE_SOZAI->Col;
	iRow = SGr_vRIRE_SOZAI->Row;
	iRowCount = SGr_vRIRE_SOZAI->RowCount;
    sBuf = SGr_vRIRE_SOZAI->Cells[iCol][iRow];
        if( hRIRE_KSD01_DATA && hCELLINFO_RIRE_SOZAI)
        {
            pRIRE_KSD01_DATA[iCol].UPD_FLG = true;              //UPDATE�t���O�iRETURN KEY�ȊO�Ȃ�H�j
            if(SGr_vRIRE_SOZAI->Color != (TColor)0x00DDDDDD)    //�����ʂł͍X�V�ғ��̏��������͍s��Ȃ�
            {
            //��\�X�V�҂̏�������
                strcpy(pRIRE_KSD01_DATA[iCol].UPDCHR 	 ,AnsiString(Form1->USER_COD).c_str());
            //�X�V�҂̏�������(�Z�����j
                strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDCHR , AnsiString(Form1->USER_COD).c_str());
            //2003.05.17 E.Takase Add��
                strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDNAME , AnsiString(Form1->USER_NAM).c_str());
            //2003.05.17 E.Takase Add��
            //���t�̏�������(�Z�����j
                sDATE = FormatDateTime("yyyymmdd",Date());
                sTIME = FormatDateTime("hhmm",TDateTime::CurrentTime());
                strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDYMD,sDATE.c_str());
                strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDTIM,sTIME.c_str());
            //���o�^�Ȃ瑪����A�o�^�����X�V�i�V�K�j����
                if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].SKTYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].SKTYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].ADDYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].ADDYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].ADDTIM).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].ADDTIM,sTIME.c_str());
                }
            }
        }
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�[�^��ۑ�����ہA�e�X�̃��b�g�̑��肪�I�����Ă��邩�𒲂ׂ�
//
//  �@�\����
//  �@�S���b�g�ɑ΂��ă��b�g���̔�����s���܂�
//  �A�X�V���b�g���S������ς܂��Ă��邩�𒲂ׂ�B
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    true:�@�X�V���b�g�ɖ�����͊܂܂�Ă��Ȃ��B
//    false�F�@�X�V���b�g�ɖ������������B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::ALL_INSPECT(void)
{
	int iCol;
    int iColCount,iRowCount;
    bool bALL_INSPECT;

    // 2004/09/13 A.Tamura �A�v���P�[�V�����G���[�ׁ̈Atry.. catch()���s�Ȃ��B
	try
	{

	    bALL_INSPECT = true;

//�@�S���b�g�ɑ΂��ă��b�g���̔�����s���܂��B

	    if(hCELLINFO_SOKU_SYUKA)
	    {
	        iColCount = SGr_vSOKU_SYUKA->ColCount;
	        iRowCount = SGr_vSOKU_SYUKA->RowCount;
	        for(iCol = 0; iCol < iColCount; iCol++)
	        {
	            GET_HANTEI(SGr_vSOKU_SYUKA, iCol);
	            if((pCELLINFO_SOKU_SYUKA[iCol*iRowCount + 0].JUDGE      == -1)
	            || (pCELLINFO_SOKU_SYUKA[iCol*iRowCount + 0].DISP_JUDGE == -1))
	            {
	                bALL_INSPECT = false;
	            }
	        }
	    }

	    if(hCELLINFO_RIRE_SYUKA && Form1->iRIRE_CNT != 0 )
	    {
	        iColCount = SGr_vRIRE_SYUKA->ColCount;
	        iRowCount = SGr_vRIRE_SYUKA->RowCount;
	        for(iCol = 0; iCol < iColCount; iCol++)
	        {
	            GET_HANTEI(SGr_vRIRE_SYUKA, iCol);
	            if((pCELLINFO_RIRE_SYUKA[iCol*iRowCount + 0].JUDGE      == -1)
	            || (pCELLINFO_RIRE_SYUKA[iCol*iRowCount + 0].DISP_JUDGE == -1))
	            {
	                bALL_INSPECT = false;
	            }
	        }
	    }

	    if( hCELLINFO_SOKU_SOZAI )
	    {
	        iColCount = SGr_vSOKU_SOZAI->ColCount;
	        iRowCount = SGr_vSOKU_SOZAI->RowCount;
	        for(iCol = 0; iCol < iColCount; iCol++)
	        {
	            GET_HANTEI(SGr_vSOKU_SOZAI, iCol);
	            if((pCELLINFO_SOKU_SOZAI[iCol*iRowCount + 0].JUDGE      == -1)
	            || (pCELLINFO_SOKU_SOZAI[iCol*iRowCount + 0].DISP_JUDGE == -1))
	            {
	                bALL_INSPECT = false;
	            }
	        }
	    }

	    if(hCELLINFO_RIRE_SOZAI && Form1->iRIRE_CNT != 0)
	    {
	        iColCount = SGr_vRIRE_SOZAI->ColCount;
	        iRowCount = SGr_vRIRE_SOZAI->RowCount;
	        for(iCol = 0; iCol < iColCount; iCol++)
	        {
	            GET_HANTEI(SGr_vRIRE_SOZAI, iCol);
	            if((pCELLINFO_RIRE_SOZAI[iCol*iRowCount + 0].JUDGE      == -1)
	            || (pCELLINFO_RIRE_SOZAI[iCol*iRowCount + 0].DISP_JUDGE == -1))
	            {
	                bALL_INSPECT = false;
	            }
	        }
	    }
	//---------------------------------------------------------------------------
	//  �A�X�V���b�g���S������ς܂��Ă��邩�𒲂ׂ�B
	    bALL_INSPECT = true;

	    if(hCELLINFO_SOKU_SYUKA)
	    {
	        iColCount = SGr_vSOKU_SYUKA->ColCount;
	        iRowCount = SGr_vSOKU_SYUKA->RowCount;
	        for(iCol = 0; iCol < iColCount; iCol++)
	        {
	            if(pSOKU_KSD01_DATA[iCol].UPD_FLG == true)
	            {
	                if((pCELLINFO_SOKU_SYUKA[iCol*iRowCount + 0].JUDGE      == -1)
	                || (pCELLINFO_SOKU_SYUKA[iCol*iRowCount + 0].DISP_JUDGE == -1))
	                {
	                    bALL_INSPECT = false;
	                }
	            }
	        }
	    }

	    if(hCELLINFO_RIRE_SYUKA && Form1->iRIRE_CNT != 0 )
	    {
	        iColCount = SGr_vRIRE_SYUKA->ColCount;
	        iRowCount = SGr_vRIRE_SYUKA->RowCount;
	        for(iCol = 0; iCol < iColCount; iCol++)
	        {
	            if(pRIRE_KSD01_DATA[iCol].UPD_FLG == true)
	            {
	                if((pCELLINFO_RIRE_SYUKA[iCol*iRowCount + 0].JUDGE      == -1)
	                || (pCELLINFO_RIRE_SYUKA[iCol*iRowCount + 0].DISP_JUDGE == -1))
	                {
	                    bALL_INSPECT = false;
	                }
	            }
	        }
	    }

	    if( hCELLINFO_SOKU_SOZAI )
	    {
	        iColCount = SGr_vSOKU_SOZAI->ColCount;
	        iRowCount = SGr_vSOKU_SOZAI->RowCount;
	        for(iCol = 0; iCol < iColCount; iCol++)
	        {
	            if(pSOKU_KSD01_DATA[iCol].UPD_FLG == true)
	            {
	                if((pCELLINFO_SOKU_SOZAI[iCol*iRowCount + 0].JUDGE      == -1)
	                || (pCELLINFO_SOKU_SOZAI[iCol*iRowCount + 0].DISP_JUDGE == -1))
	                {
	                    bALL_INSPECT = false;
	                }
	            }
	        }
	    }

	    if(hCELLINFO_RIRE_SOZAI && Form1->iRIRE_CNT != 0)
	    {
	        iColCount = SGr_vRIRE_SOZAI->ColCount;
	        iRowCount = SGr_vRIRE_SOZAI->RowCount;
	        for(iCol = 0; iCol < iColCount; iCol++)
	        {
	            if(pRIRE_KSD01_DATA[iCol].UPD_FLG == true)
	            {
	                if((pCELLINFO_RIRE_SOZAI[iCol*iRowCount + 0].JUDGE      == -1)
	                || (pCELLINFO_RIRE_SOZAI[iCol*iRowCount + 0].DISP_JUDGE == -1))
	                {
	                    bALL_INSPECT = false;
	                }
	            }
	        }
	    }
	}
    catch ( ... )
    {
        return( false );
    }

	return( bALL_INSPECT );
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�P�P�F�ۑ��v�{�^�������������̏���
//
//  �@�\����
//    CtrlOFF:�X�V�f�[�^�̕ۑ����s���܂��B
//    CtrlON :����
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
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnF11Click(TObject *Sender)
{
    TShiftState State;
    int iCol;
    bool bHan;
    AnsiString sBuf;
    TMsgDlgButtons MsgButton;
    unsigned short shtHoge=17;


    if( !BtnF11->Enabled )    return;
    //���b�g���͔���
    if( !bINPUTLOT_OK )
    {
       	sBuf  = "�L���ȃ��b�g�����͂���Ă��Ȃ��וۑ��ł��܂���B";
		MsgButton << mbOK;
        MessageDlg( sBuf, mtWarning	, MsgButton, 0);
        return;
    }
    // 2003/05/14 A.Tamura
    if( !BtnF11->Tag )
    {
        // 2003/10/30 A.Tamura �Ō�Ƀt�H�[�J�X�̗L�����Z�����ҏW���[�h�̎��A
        // �u�l�̕ۑ��v�Ɓu���菈���v���m���ɍs�Ȃ����߁ADrawCell���Ăяo���܂��B
		TGridDrawState DrawState;
    	AllGRID_DrawCell( SGr_vSOKU_SYUKA, SGr_vSOKU_SYUKA->Col, SGr_vSOKU_SYUKA->Row, SGr_vSOKU_SYUKA->CellRect(SGr_vSOKU_SYUKA->Col, SGr_vSOKU_SYUKA->Row), DrawState);
    	AllGRID_DrawCell( SGr_vRIRE_SYUKA, SGr_vRIRE_SYUKA->Col, SGr_vRIRE_SYUKA->Row, SGr_vRIRE_SYUKA->CellRect(SGr_vRIRE_SYUKA->Col, SGr_vRIRE_SYUKA->Row), DrawState);
    	AllGRID_DrawCell( SGr_vSOKU_SOZAI, SGr_vSOKU_SOZAI->Col, SGr_vSOKU_SOZAI->Row, SGr_vSOKU_SOZAI->CellRect(SGr_vSOKU_SOZAI->Col, SGr_vSOKU_SOZAI->Row), DrawState);
    	AllGRID_DrawCell( SGr_vRIRE_SOZAI, SGr_vRIRE_SOZAI->Col, SGr_vRIRE_SOZAI->Row, SGr_vRIRE_SOZAI->CellRect(SGr_vRIRE_SOZAI->Col, SGr_vRIRE_SOZAI->Row), DrawState);

        //�����ʏI���������ƌ������邽�߂̃t���O�ł��B
        if( bQUIT_FLG == false )
        {
            //�X�V����Ă��邩
            if( UPDATE_CHECK())
            {
                //�X�V�f�[�^�̑��肪�S�ďI����Ă��邩�B
                if( !ALL_INSPECT())
                {
                    sBuf  = "������̍��ڂ��L��܂��B�ύX���e��ۑ����܂����B";
        	    sBuf += "\n[�́@��] �ύX���e��ۑ����đ��s���܂��B";
        	    sBuf += "\n[�L�����Z��] �ۑ������̎������B";
                    MsgButton << mbYes << mbCancel;
                    switch( MessageDlg( sBuf, mtWarning	, MsgButton, 0) ){
                        // �uYes�v      �ۑ�
                        case mrYes:
                             break;
                         // �uCancel�v   �L�����Z��
                        case mrCancel:
                             return;
             	    }
                }
            }
        }
        else
        {
            //�����ʏI�����̓��b�g�̔�����s���܂�
            ALL_INSPECT();
        }

        //�Z�����̕ۑ�
        ADD_SPACE();
    	bHan = Set_DB_SOKU();
    	bHan = Set_DB_RIRE();
    	bHan = Set_DB_SOKU_SOZAI();
    	bHan = Set_DB_RIRE_SOZAI();
        //�ۑ����I�������̂Łu�A�b�v�f�[�g�t���O�ƕۑ��t���O�����������܂�
	if( hSOKU_KSD01_DATA)
	{
	    for(iCol = 0; iCol<SGr_tSOKU->ColCount;iCol++)
	    {
		pSOKU_KSD01_DATA[iCol].UPD_FLG = false;
		pSOKU_KSD01_DATA[iCol].SAVE_FLG = true;
	    }
    	}

	if( hRIRE_KSD01_DATA)
	{
	    for(iCol = 0; iCol<SGr_tRIRE->ColCount;iCol++)
	    {
		pRIRE_KSD01_DATA[iCol].UPD_FLG = false;
		pRIRE_KSD01_DATA[iCol].SAVE_FLG = true;
	    }
	}
	AllKeyUp(Sender ,shtHoge,State);	// �t�@���N�V�����L�[�̏�Ԃ����ɖ߂��܂��B
    }
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�O���^�����^Enter�������ɃZ���𐳂����ʒu�ɒu���֐��ł�
//
//  �@�\����
//  �D�F�̕������������Z���őO���^�����ɂ����镔����T���܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    char Key          :�P�����̃R�[�h(VK_F13 or VK_F3 or VK_RETURN)
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::GridSetPointMove(TObject *Sender, char Key)
{
	int iRow,iCol,iX,iY,i1,i2; // ,fSts,iRoopCount,iTEMP_X,iTEMP_Y;
	int iORG_SOKU_SU,iRowTop,iORG_KOMK_NO,iORG_KIKI_NO;
	//int iNEW_KOMK_NO,iNEW_KIKI_NO,iNEW_SOKU_SU,iNEW_UNQ_NO;
	//int iORG_SKB_NO,iNEW_SKB_NO;
	int iTargetGrid;
	int iRowCount,iColCount;
    int iHANTEI;
	//bool bNEXTPOINT;
    //bool bKMOVE;
	bool bSTS;
	bool bFIRSTMOVE;
	//bNEXTPOINT = false;
    bKASOU_MOVE = false;
//�O���b�h�̏ꏊ�����߂�
	iTargetGrid = WhereGrid();
//�����ւ̈ړ�
    if(Key == VK_RETURN || Key == VK_F3)
    {
		switch(iTargetGrid)
		{
        case 1:
        	iRow = Form1->SGr_vSOKU_SYUKA->Row;
        	iCol = Form1->SGr_vSOKU_SYUKA->Col;
			iRowCount = Form1->SGr_vSOKU_SYUKA->RowCount;
			iColCount = Form1->SGr_vSOKU_SYUKA->ColCount;
        	if(SGr_tSOKU->Cells[iCol][0].Trim().Length() == 0) return;
            if(iRowCount < 2 ) return;
			break;
        case 2:
        	iRow = Form1->SGr_vRIRE_SYUKA->Row;
        	iCol = Form1->SGr_vRIRE_SYUKA->Col;
			iRowCount = Form1->SGr_vRIRE_SYUKA->RowCount;
			iColCount = Form1->SGr_vRIRE_SYUKA->ColCount;
        	if(SGr_tRIRE->Cells[iCol][0].Trim().Length() == 0) return;
            if(Form1->iRIRE_CNT == 0 || iRowCount < 2 ) return;
			break;
		case 3:
        	iRow = Form1->SGr_vSOKU_SOZAI->Row;
        	iCol = Form1->SGr_vSOKU_SOZAI->Col;
			iRowCount = Form1->SGr_vSOKU_SOZAI->RowCount;
			iColCount = Form1->SGr_vSOKU_SOZAI->ColCount;
        	if(SGr_tSOKU->Cells[iCol][0].Trim().Length() == 0) return;
            if(iRowCount < 2 ) return;
			break;
		case 4:
        	iRow = Form1->SGr_vRIRE_SOZAI->Row;
        	iCol = Form1->SGr_vRIRE_SOZAI->Col;
			iRowCount = Form1->SGr_vRIRE_SOZAI->RowCount;
			iColCount = Form1->SGr_vRIRE_SOZAI->ColCount;
        	if(SGr_tRIRE->Cells[iCol][0].Trim().Length() == 0) return;
            if(Form1->iRIRE_CNT == 0 || iRowCount < 2 ) return;
			break;
		default:
            return; //2003.05.15 M.HIRAI
		}
/////////////////
        //�ړ��̍ۂɔ��艹��炷 2003.06.19
        iHANTEI = CELL_HANTEI(Sender,iCol,iRow);
        switch(iHANTEI)
        {
        case 0:
            OK_BEEP(0);
            break;
        case 1:
            NG_BEEP(0);
            break;
        }
//////////////////
        if(!Form1->bCursolMove)
        {
	    //�������ւ̈ړ�
			iRowTop = Get_GRAPHSTART_Info(iRow,iCol,iTargetGrid) + 1;
    	    iY = iRow;
        	iX = iCol;
	        bSTS = false;
            bFIRSTMOVE = true;
			switch(iTargetGrid)
			{
	        case 1:
				//���ꍀ�ڐ����������������擾�i�ő吔�j
            	iORG_SOKU_SU = 0;
                if(hCELLINFO_RIRE_SYUKA)
                {
                    for(i1=0;i1<SGr_vRIRE_SYUKA->ColCount;i1++)
                    {
                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                        {
                    	    iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        }
				    }
                }
                if(hCELLINFO_SOKU_SYUKA)
                {
                    for(i1=0;i1<SGr_vSOKU_SYUKA->ColCount;i1++)
                    {
                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                        {
                    	    iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        }
				    }
                } 
		        while( !bSTS )
    		    {
        			for(iX = iX;iX < iColCount; iX++)
            		{
                        //���ꑪ�荀�ړ��ŗL���ȃZ�������邩���m�F���܂��B
            			for(iY = iY;iY < iRowTop+iORG_SOKU_SU; iY++)
	      	          	{
                            //�ړ��\�����Ƃ��Ė�������(KOMK_NO=0)�A���荀�ږ����ȊO
    	            		//if((AnsiString(pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].INS_ON != false)
                            && (AnsiString(pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
    	            	    {
								if(bFIRSTMOVE == false )
								{
            	        			bSTS= true;
                	        		break;
								}
								else
                                //�ŏ��Ɍ������ʒu�͊J�n�ʒu�Ɠ����Ȃ̂ŏ��O���܂��B
								{
									bFIRSTMOVE = false;
								}
                    		}
	                	}
    	            	if(bSTS) break;
        	        	iY = iRowTop;
            		}
                    //�ړ��\�ꏊ��������Ȃ������ꍇ�͎��̍��ڂ̃p�����[�^����肵�܂��B
	            	if(!bSTS)
    	        	{
        	    		iX = 0;
            	    	iY = iRowTop + iORG_SOKU_SU;	//���̍��ڂւ̈ړ�
						iRowTop = iY;
                		if(iY >= iRowCount )    //���ڂ�������Έ�ԏ�̍��ڂ��w���܂�
						{
							iY = 1;
							iRowTop = 1;
						}
		            	iORG_SOKU_SU = 0;
                        if(hCELLINFO_RIRE_SYUKA)
                        {
        		            for(i1=0;i1<SGr_vRIRE_SYUKA->ColCount;i1++)
                		    {
		                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
        		                {
                		    	    iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	    }
	                        }
                        }
                        if(hCELLINFO_SOKU_SYUKA)
                        {
    	                    for(i1=0;i1<SGr_vSOKU_SYUKA->ColCount;i1++)
        	                {
            	        	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                	            {
                    	    	    iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	    }
						    }
                        }
	          		}
	        	}
            	//Form1->SBr1->Panels->Items[0]->Text = AnsiString(iX) + "," + AnsiString(iY);
                //Form1->SBr1->Update();
				i2 = iX-1;
				if(SGr_vSOKU_SYUKA->RowCount <= iY
                || SGr_vSOKU_SYUKA->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE = true;
					while( 1 )
					{
                    	SGr_vSOKU_SYUKA->Row = iY;
                        SGr_vSOKU_SYUKA->Col = iX;
						if(SGr_vSOKU_SYUKA->Row == iY && SGr_vSOKU_SYUKA->Col == iX) break;
						for(i1=0;i1 < iRowCount ; i1++)
						{
        					SGr_vSOKU_SYUKA->Row = i1;
                    		SGr_vSOKU_SYUKA->Col = iX;
							if( SGr_vSOKU_SYUKA->Col == iX)
							{
    	                		SGr_vSOKU_SYUKA->Row = iY;
        	                    break;
							}
                	    }
						break;
					}
					bKASOU_MOVE = false;
				}
				break;
            //�ȉ��̓O���b�h�̈ʒu���Ⴄ�����œ����������s���܂��B
	        case 2:
				//���ꍀ�ڐ����������������擾�i�ő吔�j
            	iORG_SOKU_SU = 0;
                if(hCELLINFO_RIRE_SYUKA)
                {
                    for(i1=0;i1<SGr_vRIRE_SYUKA->ColCount;i1++)
                    {
                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                        {
                    	    iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        }
				    }
                }
                if(hCELLINFO_SOKU_SYUKA)
                {
                    for(i1=0;i1<SGr_vSOKU_SYUKA->ColCount;i1++)
                    {
                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                        {
                    	    iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        }
				    }
                }
		        while( !bSTS )
    		    {
        			for(iX = iX;iX < iColCount; iX++)
            		{
            			for(iY = iY;iY < iRowTop+iORG_SOKU_SU; iY++)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].RESULT) != "�s�v")
    	            		//if((AnsiString(pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].INS_ON != false)
                        //���荀�ږ���������ɒǉ�
                            && (AnsiString(pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
								if(bFIRSTMOVE == false )
								{
            	        			bSTS= true;
                	        		break;
								}
								else
								{
									bFIRSTMOVE = false;
								}
                    		}
	                	}
    	            	if(bSTS) break;
        	        	iY = iRowTop;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = 0;
            	    	iY = iRowTop + iORG_SOKU_SU;	//���̍��ڂւ̈ړ�
						iRowTop = iY;
                		if(iY >= iRowCount )    //���ڂ�������Έ�ԏ�̍��ڂ��w���܂�
						{
							iY = 1;
							iRowTop = 1;
						}
		            	iORG_SOKU_SU = 0;
                        if(hCELLINFO_RIRE_SYUKA)
                        {
        		            for(i1=0;i1<SGr_vRIRE_SYUKA->ColCount;i1++)
                		    {
		                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
        		                {
                		    	    iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	    }
	                        }
                        }
                        if(hCELLINFO_SOKU_SYUKA)
                        {
    	                    for(i1=0;i1<SGr_vSOKU_SYUKA->ColCount;i1++)
        	                {
            	        	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                	            {
                    	    	    iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	    }
						    }
                        }
	          		}
	        	}
            	//Form1->SBr1->Panels->Items[0]->Text = AnsiString(iX) + "," + AnsiString(iY);
                //Form1->SBr1->Update();
				i2 = iX-1;
				if(SGr_vRIRE_SYUKA->RowCount <= iY
                || SGr_vRIRE_SYUKA->ColCount <= iX)
                {
					break;
				}
				else
				{
					bKASOU_MOVE = true;
					while( 1 )
					{
                    	SGr_vRIRE_SYUKA->Row = iY;
                        SGr_vRIRE_SYUKA->Col = iX;
						if(SGr_vRIRE_SYUKA->Row == iY && SGr_vRIRE_SYUKA->Col == iX) break;
						for(i1=0;i1 < iRowCount ; i1++)
						{
        					SGr_vRIRE_SYUKA->Row = i1;
                    		SGr_vRIRE_SYUKA->Col = iX;
							if( SGr_vRIRE_SYUKA->Col == iX)
							{
        	            		SGr_vRIRE_SYUKA->Row = iY;
            	                break;
							}
                    	}
						break;
					}
					bKASOU_MOVE = false;
				}
				break;
	        case 3:
				//���ꍀ�ڐ����������������擾�i�ő吔�j
            	iORG_SOKU_SU = 0;
                if(hCELLINFO_RIRE_SOZAI)
                {
                    for(i1=0;i1<SGr_vRIRE_SOZAI->ColCount;i1++)
                    {
                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                        {
                    	    iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        }
				    }
                }
                if(hCELLINFO_SOKU_SOZAI)
                {
                    for(i1=0;i1<SGr_vSOKU_SOZAI->ColCount;i1++)
                    {
                    	if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                        {
                        	iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        }
				    }
                }
		        while( !bSTS )
    		    {
        			for(iX = iX;iX < iColCount; iX++)
            		{
            			for(iY = iY;iY < iRowTop+iORG_SOKU_SU; iY++)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].RESULT) != "�s�v")
    	            		//if((AnsiString(pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].INS_ON != false)
                        //���荀�ږ���������ɒǉ�
                            && (AnsiString(pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
								if(bFIRSTMOVE == false )
								{
            	        			bSTS= true;
                	        		break;
								}
								else
								{
									bFIRSTMOVE = false;
								}
                    		}
	                	}
    	            	if(bSTS) break;
        	        	iY = iRowTop;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = 0;
            	    	iY = iRowTop + iORG_SOKU_SU;	//���̍��ڂւ̈ړ�
						iRowTop = iY;
                		if(iY >= iRowCount )    //���ڂ�������Έ�ԏ�̍��ڂ��w���܂�
						{
							iY = 1;
							iRowTop = 1;
						}
		            	iORG_SOKU_SU = 0;
                        if(hCELLINFO_RIRE_SOZAI)
                        {
        		            for(i1=0;i1<SGr_vRIRE_SOZAI->ColCount;i1++)
                		    {
		                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
        		                {
                		    	    iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	    }
	                        }
                        }
                        if(hCELLINFO_SOKU_SOZAI)
                        {
    	                    for(i1=0;i1<SGr_vSOKU_SOZAI->ColCount;i1++)
        	                {
            	        	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                	            {
                    	    	    iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	    }
						    }
                        }
	          		}
	        	}
            	//Form1->SBr1->Panels->Items[0]->Text = AnsiString(iX) + "," + AnsiString(iY);
                //Form1->SBr1->Update();
				i2 = iX-1;
				if(SGr_vSOKU_SOZAI->RowCount <= iY
                || SGr_vSOKU_SOZAI->ColCount <= iX)
                {
					break;
				}
				else
                {
                	bKASOU_MOVE = true;
					while( 1 )
					{
                    	SGr_vSOKU_SOZAI->Row = iY;
                        SGr_vSOKU_SOZAI->Col = iX;
						if(SGr_vSOKU_SOZAI->Row == iY && SGr_vSOKU_SOZAI->Col == iX) break;
						for(i1=0;i1 < iRowCount ; i1++)
						{
        					SGr_vSOKU_SOZAI->Row = i1;
                    		SGr_vSOKU_SOZAI->Col = iX;
							if( SGr_vSOKU_SOZAI->Col == iX)
							{
    	                		SGr_vSOKU_SOZAI->Row = iY;
        	                    break;
							}
                	    }
						break;
					}
					bKASOU_MOVE = false;
				}
				break;
	        case 4:
			//���ꍀ�ڐ����������������擾�i�ő吔�j
            	iORG_SOKU_SU = 0;
                if( hCELLINFO_RIRE_SOZAI)
                {
                    for(i1=0;i1<SGr_vRIRE_SOZAI->ColCount;i1++)
                    {
                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                        {
                    	    iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        }
				    }
                }
                if( hCELLINFO_SOKU_SOZAI)
                {
                    for(i1=0;i1<SGr_vSOKU_SOZAI->ColCount;i1++)
                    {
                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                        {
                    	    iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        }
				    }
                }
		        while( !bSTS )
    		    {
        			for(iX = iX;iX < iColCount; iX++)
            		{
            			for(iY = iY;iY < iRowTop+iORG_SOKU_SU; iY++)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].RESULT) != "�s�v")
    	            		//if((AnsiString(pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].INS_ON != false)
                        //���荀�ږ���������ɒǉ�
                            && (AnsiString(pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
								if(bFIRSTMOVE == false )
								{
            	        			bSTS= true;
                	        		break;
								}
								else
								{
									bFIRSTMOVE = false;
								}
                    		}
	                	}
    	            	if(bSTS) break;
        	        	iY = iRowTop;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = 0;
            	    	iY = iRowTop + iORG_SOKU_SU;	//���̍��ڂւ̈ړ�
						iRowTop = iY;
                		if(iY >= iRowCount )    //���ڂ�������Έ�ԏ�̍��ڂ��w���܂�
						{
							iY = 1;
							iRowTop = 1;
						}
		            	iORG_SOKU_SU = 0;
                        if(hCELLINFO_RIRE_SOZAI)
                        {
        		            for(i1=0;i1<SGr_vRIRE_SOZAI->ColCount;i1++)
                		    {
		                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
        		                {
                		    	    iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	    }
	                        }
                        }
                        if(hCELLINFO_SOKU_SOZAI)
                        {
    	                    for(i1=0;i1<SGr_vSOKU_SOZAI->ColCount;i1++)
        	                {
            	        	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                	            {
                    	    	    iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	    }
						    }
                        }                      
	          		}
	        	}
            	//Form1->SBr1->Panels->Items[0]->Text = AnsiString(iX) + "," + AnsiString(iY);
                //Form1->SBr1->Update();
				i2 = iX-1;
				if(SGr_vRIRE_SOZAI->RowCount <= iY
                || SGr_vRIRE_SOZAI->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE =true;
					while( 1 )
					{
                    	SGr_vRIRE_SOZAI->Row = iY;
                        SGr_vRIRE_SOZAI->Col = iX;
						if(SGr_vRIRE_SOZAI->Row == iY && SGr_vRIRE_SOZAI->Col == iX) break;
						for(i1=0;i1 < iRowCount ; i1++)
						{
        					SGr_vRIRE_SOZAI->Row = i1;
                    		SGr_vRIRE_SOZAI->Col = iX;
							if( SGr_vRIRE_SOZAI->Col == iX)
							{
    	                		SGr_vRIRE_SOZAI->Row = iY;
        	                    break;
							}
                	    }
						break;
					}
					bKASOU_MOVE = false;
				}
				break;
			}
    	}
		else
		{
	//�c�����ւ̈ړ�
			iRowTop = Get_GRAPHSTART_Info(iRow,0,iTargetGrid);
    	    iORG_KOMK_NO = AnsiString(pInfoGlaph.KOMK_NO).ToIntDef(0);
        	iORG_KIKI_NO = AnsiString(pInfoGlaph.KIKI_NO).ToIntDef(0);
	        iORG_SOKU_SU = AnsiString(pInfoGlaph.SOKU_SU).ToIntDef(0);
    	    iY = iRow+1;
        	iX = iCol;
	        bSTS = false;
			switch(iTargetGrid)
			{
	        case 1:
		        while( !bSTS )
    		    {
        			for(iX = iX;iX < iColCount; iX++)
            		{
            			for(iY = iY;iY < iRowCount; iY++)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].RESULT) != "�s�v")
    	            		//if((AnsiString(pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].INS_ON != false)
                        //���荀�ږ���������ɒǉ�
                            && (AnsiString(pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
            	        		bSTS= true;
                	        	break;
                    		}
	                	}
						if( !bSTS ) iY = 1;
						if( bSTS ) break;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = 0;
            	    	iY = 1;
            		}
	        	}
				if(SGr_vSOKU_SYUKA->RowCount <= iY
                || SGr_vSOKU_SYUKA->ColCount <= iX)
                {
					break;
				}
				else
                {
					while( 1 )
					{
        				SGr_vSOKU_SYUKA->Col = iX;
        				SGr_vSOKU_SYUKA->Row = iY;
						if( SGr_vSOKU_SYUKA->Col == iX && SGr_vSOKU_SYUKA->Row == iY) break;
					}
				}
				break;
	        case 2:
		        while( !bSTS )
    		    {
        			for(iX = iX;iX < iColCount; iX++)
            		{
            			for(iY = iY;iY < iRowCount; iY++)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].RESULT) != "�s�v")
    	            		//if((AnsiString(pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].INS_ON != false)
                        //���荀�ږ���������ɒǉ�
                            && (AnsiString(pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
            	        		bSTS= true;
                	        	break;
                    		}
	                	}
						if( !bSTS ) iY = 1;
						if( bSTS ) break;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = 0;
            	    	iY = 1;
            		}
	        	}
				if(SGr_vRIRE_SYUKA->RowCount <= iY
                || SGr_vRIRE_SYUKA->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE = true;
					while( 1 )
					{
        				SGr_vRIRE_SYUKA->Col = iX;
        				SGr_vRIRE_SYUKA->Row = iY;
						if( SGr_vRIRE_SYUKA->Col == iX && SGr_vRIRE_SYUKA->Row == iY) break;
					}
					bKASOU_MOVE = false;
				}
				break;
	        case 3:
		        while( !bSTS )
    		    {
        			for(iX = iX;iX < iColCount; iX++)
            		{
            			for(iY = iY;iY < iRowCount; iY++)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].RESULT) != "�s�v")
    	            		//if((AnsiString(pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].INS_ON != false)
                        //���荀�ږ���������ɒǉ�
                            && (AnsiString(pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
            	        		bSTS= true;
                	        	break;
                    		}
	                	}
						if( !bSTS ) iY = 1;
						if( bSTS ) break;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = 0;
            	    	iY = 1;
            		}
	        	}
				if(SGr_vSOKU_SOZAI->RowCount <= iY
                || SGr_vSOKU_SOZAI->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE = true;
					while( 1 )
					{
        				SGr_vSOKU_SOZAI->Col = iX;
        				SGr_vSOKU_SOZAI->Row = iY;
						if( SGr_vSOKU_SOZAI->Col == iX && SGr_vSOKU_SOZAI->Row == iY) break;
					}
					bKASOU_MOVE = false;
				}
				break;
	        case 4:
		        while( !bSTS )
    		    {
        			for(iX = iX;iX < iColCount; iX++)
            		{
            			for(iY = iY;iY < iRowCount; iY++)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].RESULT) != "�s�v")
    	            		//if((AnsiString(pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].INS_ON != false)
                        //���荀�ږ���������ɒǉ�
                            && (AnsiString(pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
            	        		bSTS= true;
                	        	break;
                    		}
	                	}
						if( !bSTS ) iY = 1;
						if( bSTS ) break;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = 0;
            	    	iY = 1;
            		}
	        	}
				if(SGr_vRIRE_SOZAI->RowCount <= iY
                || SGr_vRIRE_SOZAI->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE = true;
					while( 1 )
					{
        				SGr_vRIRE_SOZAI->Col = iX;
        				SGr_vRIRE_SOZAI->Row = iY;
						if( SGr_vRIRE_SOZAI->Col == iX && SGr_vRIRE_SOZAI->Row == iY) break;
					}
					bKASOU_MOVE = false;
				}
				break;
    		}
    	}
    }
    //�e�Q�̏����ł�
    if(Key == VK_F13)
    {
    	switch(iTargetGrid)
		{
        case 1:
        	iRow = Form1->SGr_vSOKU_SYUKA->Row;
        	iCol = Form1->SGr_vSOKU_SYUKA->Col;
			iRowCount = Form1->SGr_vSOKU_SYUKA->RowCount;
			iColCount = Form1->SGr_vSOKU_SYUKA->ColCount;
        	if(SGr_tSOKU->Cells[iCol][0].Trim().Length() == 0) return;
            if(iRowCount < 2 ) return;
			break;
        case 2:
        	iRow = Form1->SGr_vRIRE_SYUKA->Row;
        	iCol = Form1->SGr_vRIRE_SYUKA->Col;
			iRowCount = Form1->SGr_vRIRE_SYUKA->RowCount;
			iColCount = Form1->SGr_vRIRE_SYUKA->ColCount;
        	if(SGr_tRIRE->Cells[iCol][0].Trim().Length() == 0) return;
            if(Form1->iRIRE_CNT == 0 || iRowCount < 2 ) return;
			break;
		case 3:
        	iRow = Form1->SGr_vSOKU_SOZAI->Row;
        	iCol = Form1->SGr_vSOKU_SOZAI->Col;
			iRowCount = Form1->SGr_vSOKU_SOZAI->RowCount;
			iColCount = Form1->SGr_vSOKU_SOZAI->ColCount;
        	if(SGr_tSOKU->Cells[iCol][0].Trim().Length() == 0) return;
            if(iRowCount < 2 ) return;
			break;
		case 4:
        	iRow = Form1->SGr_vRIRE_SOZAI->Row;
        	iCol = Form1->SGr_vRIRE_SOZAI->Col;
			iRowCount = Form1->SGr_vRIRE_SOZAI->RowCount;
			iColCount = Form1->SGr_vRIRE_SOZAI->ColCount;
        	if(SGr_tRIRE->Cells[iCol][0].Trim().Length() == 0) return;
            if(Form1->iRIRE_CNT == 0 || iRowCount < 2 ) return;
			break;
		default:
            return; //2003.05.15 M.HIRAI
		}
/////////////////
        //�ړ��̍ۂɔ��艹��炷 2003.06.19
        iHANTEI = CELL_HANTEI(Sender,iCol,iRow);
        switch(iHANTEI)
        {
        case 0:
            OK_BEEP(0);
            break;
        case 1:
            NG_BEEP(0);
            break;
        }
////////////////
        if(!Form1->bCursolMove)
        {
	//�������ւ̈ړ�
			iRowTop = Get_GRAPHSTART_Info(iRow,0,iTargetGrid)+1;
    	    iORG_KOMK_NO = AnsiString(pInfoGlaph.KOMK_NO).ToIntDef(0);
        	iORG_KIKI_NO = AnsiString(pInfoGlaph.KIKI_NO).ToIntDef(0);
	        iORG_SOKU_SU = AnsiString(pInfoGlaph.SOKU_SU).ToIntDef(0);
    	    iY = iRow;
        	iX = iCol;
	        bSTS = false;
			switch(iTargetGrid)
			{
	        case 1:
				//���ꍀ�ڐ����������������擾�i�ő吔�j
            	iORG_SOKU_SU = 0;
                if(Form1->iRIRE_CNT != 0)
                {
                    for(i1=0;i1<SGr_vRIRE_SYUKA->ColCount;i1++)
                    {
                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                        {
                    	    iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        }
				    }
                }
                for(i1=0;i1<SGr_vSOKU_SYUKA->ColCount;i1++)
                {
                	if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                    {
                    	iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                    }
				}
		        while( !bSTS )
    		    {
                    //���������ForNext�����Z���Ă��邱�ƈȊO�͂e�R�^Return�L�[�̓���Ɠ����ł��B
        			for(iX = iX;iX >= 0; iX--)
            		{
            			for(iY = iY;iY >= iRowTop; iY--)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].RESULT) != "�s�v")
    	            		//if((AnsiString(pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].INS_ON != false)
                        //���荀�ږ���������ɒǉ�
                            && (AnsiString(pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
								if(bFIRSTMOVE == false )
								{
            	        			bSTS= true;
                	        		break;
								}
								else
								{
									bFIRSTMOVE = false;
								}
                    		}
	                	}
    	            	if(bSTS) break;
        	        	iY = iRowTop+iORG_SOKU_SU-1;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = iColCount-1;
            	    	iY = iRowTop - 1;	//���̍��ڂւ̈ړ�
						iRowTop = Get_GRAPHSTART_Info(iY,0,iTargetGrid) + 1;
                		if(iY < 1 )    //���ڂ�������Έ�ԏ�̍��ڂ��w���܂�
						{
							iY = iRowCount-1;
							iRowTop = Get_GRAPHSTART_Info(iY,0,iTargetGrid) + 1;
						}
		            	iORG_SOKU_SU = 0;
                        if(Form1->iRIRE_CNT != 0)
                        {
        		            for(i1=0;i1<SGr_vRIRE_SYUKA->ColCount;i1++)
                		    {
		                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
        		                {
                		    	    iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	    }
	                        }
                        }
    	                for(i1=0;i1<SGr_vSOKU_SYUKA->ColCount;i1++)
        	            {
            	        	if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                	        {
                    	    	iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	}
						}
	          		}
	        	}
            	//Form1->SBr1->Panels->Items[0]->Text = AnsiString(iX) + "," + AnsiString(iY);
                //Form1->SBr1->Update();
				i2 = iX-1;
				if(SGr_vSOKU_SYUKA->RowCount <= iY
                || SGr_vSOKU_SYUKA->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE = true;
					while( 1 )
					{
						SGr_vSOKU_SYUKA->Row = iY;
						SGr_vSOKU_SYUKA->Col = iX;
						if(SGr_vSOKU_SYUKA->Col == iX && SGr_vSOKU_SYUKA->Row == iY) break;
						for(i1=0;i1 < iRowCount ; i1++)
						{
    	    				SGr_vSOKU_SYUKA->Row = i1;
        	            	SGr_vSOKU_SYUKA->Col = iX;
							if( SGr_vSOKU_SYUKA->Col == iX)
							{
                    			SGr_vSOKU_SYUKA->Row = iY;
                        	    break;
							}
    	                }
						break;
					}
					bKASOU_MOVE = false;
				}
				break;
	        case 2:
				//���ꍀ�ڐ����������������擾�i�ő吔�j
            	iORG_SOKU_SU = 0;
                for(i1=0;i1<SGr_vRIRE_SYUKA->ColCount;i1++)
                {
                	if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                    {
                    	iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                    }
				}
                for(i1=0;i1<SGr_vSOKU_SYUKA->ColCount;i1++)
                {
                	if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                    {
                    	iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                    }
				}
		        while( !bSTS )
    		    {
        			for(iX = iX;iX >= 0; iX--)
            		{
            			for(iY = iY;iY >= iRowTop; iY--)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].RESULT) != "�s�v")
    	            		//if((AnsiString(pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].INS_ON != false)
                        //���荀�ږ���������ɒǉ�
                            && (AnsiString(pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
								if(bFIRSTMOVE == false )
								{
            	        			bSTS= true;
                	        		break;
								}
								else
								{
									bFIRSTMOVE = false;
								}
                    		}
	                	}
    	            	if(bSTS) break;
        	        	iY = iRowTop+iORG_SOKU_SU-1;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = iColCount-1;
            	    	iY = iRowTop - 1;	//���̍��ڂւ̈ړ�
						iRowTop = Get_GRAPHSTART_Info(iY,0,iTargetGrid) + 1;
                		if(iY < 1 )    //���ڂ�������Έ�ԏ�̍��ڂ��w���܂�
						{
							iY = iRowCount-1;
							iRowTop = Get_GRAPHSTART_Info(iY,0,iTargetGrid) + 1;
						}
		            	iORG_SOKU_SU = 0;
        		        for(i1=0;i1<SGr_vRIRE_SYUKA->ColCount;i1++)
                		{
		                	if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
        		            {
                		    	iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	}
	                    }
    	                for(i1=0;i1<SGr_vSOKU_SYUKA->ColCount;i1++)
        	            {
            	        	if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                	        {
                    	    	iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	}
						}
	          		}
	        	}
            	//Form1->SBr1->Panels->Items[0]->Text = AnsiString(iX) + "," + AnsiString(iY);
                //Form1->SBr1->Update();
				i2 = iX-1;
				if(SGr_vRIRE_SYUKA->RowCount <= iY
                || SGr_vRIRE_SYUKA->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE = true;
					while( 1 )
					{
						SGr_vRIRE_SYUKA->Row = iY;
						SGr_vRIRE_SYUKA->Col = iX;
						if(SGr_vRIRE_SYUKA->Col == iX && SGr_vRIRE_SYUKA->Row == iY) break;
						for(i1=0;i1 < iRowCount ; i1++)
						{
    	    				SGr_vRIRE_SYUKA->Row = i1;
        	            	SGr_vRIRE_SYUKA->Col = iX;
							if( SGr_vRIRE_SYUKA->Col == iX)
							{
                    			SGr_vRIRE_SYUKA->Row = iY;
                        	    break;
							}
    	                }
						break;
					}
					bKASOU_MOVE = false;
				}
				break;
	        case 3:
				//���ꍀ�ڐ����������������擾�i�ő吔�j
            	iORG_SOKU_SU = 0;
                if(Form1->iRIRE_CNT != 0)
                {
                    for(i1=0;i1<SGr_vRIRE_SOZAI->ColCount;i1++)
                    {
                    	if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                        {
                        	iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        }
				    }
                }
                for(i1=0;i1<SGr_vSOKU_SOZAI->ColCount;i1++)
                {
                	if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                    {
                    	iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                    }
				}
		        while( !bSTS )
    		    {
        			for(iX = iX;iX >= 0; iX--)
            		{
            			for(iY = iY;iY >= iRowTop; iY--)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].RESULT) != "�s�v")
    	            		//if((AnsiString(pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].INS_ON != false)
                        //���荀�ږ���������ɒǉ�
                            && (AnsiString(pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
								if(bFIRSTMOVE == false )
								{
            	        			bSTS= true;
                	        		break;
								}
								else
								{
									bFIRSTMOVE = false;
								}
                    		}
	                	}
    	            	if(bSTS) break;
        	        	iY = iRowTop+iORG_SOKU_SU-1;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = iColCount-1;
            	    	iY = iRowTop - 1;	//���̍��ڂւ̈ړ�
						iRowTop = Get_GRAPHSTART_Info(iY,0,iTargetGrid) + 1;
                		if(iY < 1 )    //���ڂ�������Έ�ԏ�̍��ڂ��w���܂�
						{
							iY = iRowCount-1;
							iRowTop = Get_GRAPHSTART_Info(iY,0,iTargetGrid) + 1;
						}
		            	iORG_SOKU_SU = 0;
                        if(Form1->iRIRE_CNT != 0)
                        {
        		            for(i1=0;i1<SGr_vRIRE_SOZAI->ColCount;i1++)
                		    {
		                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
        		                {
                		    	    iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	    }
	                        }
                        }
    	                for(i1=0;i1<SGr_vSOKU_SOZAI->ColCount;i1++)
        	            {
            	        	if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                	        {
                    	    	iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	}
						}
	          		}
	        	}
            	//Form1->SBr1->Panels->Items[0]->Text = AnsiString(iX) + "," + AnsiString(iY);
                //Form1->SBr1->Update();
				i2 = iX-1;
				if(SGr_vSOKU_SOZAI->RowCount <= iY
                || SGr_vSOKU_SOZAI->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE = true;
					while( 1 )
					{
						SGr_vSOKU_SOZAI->Row = iY;
						SGr_vSOKU_SOZAI->Col = iX;
						if(SGr_vSOKU_SOZAI->Col == iX && SGr_vSOKU_SOZAI->Row == iY) break;
						for(i1=0;i1 < iRowCount ; i1++)
						{
    	    				SGr_vSOKU_SOZAI->Row = i1;
        	            	SGr_vSOKU_SOZAI->Col = iX;
							if( SGr_vSOKU_SOZAI->Col == iX)
							{
                    			SGr_vSOKU_SOZAI->Row = iY;
                            	break;
							}
	                    }
						break;
					}
					bKASOU_MOVE = false;
				}
				break;
	        case 4:
				//���ꍀ�ڐ����������������擾�i�ő吔�j
            	iORG_SOKU_SU = 0;
                for(i1=0;i1<SGr_vRIRE_SOZAI->ColCount;i1++)
                {
                	if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                    {
                    	iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                    }
				}
                for(i1=0;i1<SGr_vSOKU_SOZAI->ColCount;i1++)
                {
                	if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                    {
                    	iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                    }
				}
		        while( !bSTS )
    		    {
        			for(iX = iX;iX >= 0; iX--)
            		{
            			for(iY = iY;iY >= iRowTop; iY--)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].RESULT) != "�s�v")
    	            		//if((AnsiString(pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].INS_ON != false)
                        //���荀�ږ���������ɒǉ�
                            && (AnsiString(pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
								if(bFIRSTMOVE == false )
								{
            	        			bSTS= true;
                	        		break;
								}
								else
								{
									bFIRSTMOVE = false;
								}
                    		}
	                	}
    	            	if(bSTS) break;
        	        	iY = iRowTop+iORG_SOKU_SU-1;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = iColCount-1;
            	    	iY = iRowTop - 1;	//���̍��ڂւ̈ړ�
						iRowTop = Get_GRAPHSTART_Info(iY,0,iTargetGrid) + 1;
                		if(iY < 1 )    //���ڂ�������Έ�ԏ�̍��ڂ��w���܂�
						{
							iY = iRowCount-1;
							iRowTop = Get_GRAPHSTART_Info(iY,0,iTargetGrid) + 1;
						}
		            	iORG_SOKU_SU = 0;
        		        for(i1=0;i1<SGr_vRIRE_SOZAI->ColCount;i1++)
                		{
		                	if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
        		            {
                		    	iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	}
	                    }
    	                for(i1=0;i1<SGr_vSOKU_SOZAI->ColCount;i1++)
        	            {
            	        	if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                	        {
                    	    	iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	}
						}
	          		}
	        	}
            	//Form1->SBr1->Panels->Items[0]->Text = AnsiString(iX) + "," + AnsiString(iY);
                //Form1->SBr1->Update();
				i2 = iX-1;
				if(SGr_vRIRE_SOZAI->RowCount <= iY
                || SGr_vRIRE_SOZAI->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE = true;
					while( 1 )
					{
						SGr_vRIRE_SOZAI->Row = iY;
						SGr_vRIRE_SOZAI->Col = iX;
						if(SGr_vRIRE_SOZAI->Col == iX && SGr_vRIRE_SOZAI->Row == iY) break;
						for(i1=0;i1 < iRowCount ; i1++)
						{
    	    				SGr_vRIRE_SOZAI->Row = i1;
        	            	SGr_vRIRE_SOZAI->Col = iX;
							if( SGr_vRIRE_SOZAI->Col == iX)
							{
                    			SGr_vRIRE_SOZAI->Row = iY;
                        	    break;
							}
    	                }
						break;
					}
                    bKASOU_MOVE = false;
				}
				break;
			}
		}
		else
		{
	//�c�����ւ̈ړ�
			iRowTop = Get_GRAPHSTART_Info(iRow,0,iTargetGrid);
    	    iORG_KOMK_NO = AnsiString(pInfoGlaph.KOMK_NO).ToIntDef(0);
        	iORG_KIKI_NO = AnsiString(pInfoGlaph.KIKI_NO).ToIntDef(0);
	        iORG_SOKU_SU = AnsiString(pInfoGlaph.SOKU_SU).ToIntDef(0);
    	    iY = iRow-1;
        	iX = iCol;
	        bSTS = false;
			switch(iTargetGrid)
			{
	        case 1:
		        while( !bSTS )
    		    {
        			for(iX = iX;iX >= 0; iX--)
            		{
            			for(iY = iY;iY > 0; iY--)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].INS_ON != false)
                        //���荀�ږ���������ɒǉ�
                            && (AnsiString(pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
            	        		bSTS= true;
                	        	break;
                    		}
	                	}
						if( !bSTS ) iY = iRowCount-1;
						if( bSTS ) break;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = iColCount-1;
            	    	iY = iRowCount-1;
            		}
	        	}
				if(SGr_vSOKU_SYUKA->RowCount <= iY
                || SGr_vSOKU_SYUKA->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE = true;
					while( 1 )
					{
						SGr_vSOKU_SYUKA->Row = iY;
						SGr_vSOKU_SYUKA->Col = iX;
						if(SGr_vSOKU_SYUKA->Col == iX && SGr_vSOKU_SYUKA->Row == iY) break;
						for(i1=0;i1 < iRowCount ; i1++)
						{
    	    				SGr_vSOKU_SYUKA->Row = i1;
        	            	SGr_vSOKU_SYUKA->Col = iX;
							if( SGr_vSOKU_SYUKA->Col == iX)
							{
                    			SGr_vSOKU_SYUKA->Row = iY;
                        	    break;
							}
    	                }
						break;
					}
                    bKASOU_MOVE = false;
				}
                break;
	        case 2:
		        while( !bSTS )
    		    {
        			for(iX = iX;iX >= 0; iX--)
            		{
            			for(iY = iY;iY > 0 ; iY--)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].INS_ON != false)
                        //���荀�ږ���������ɒǉ�
                            && (AnsiString(pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
            	        		bSTS= true;
                	        	break;
                    		}                             
	                	}
						if( !bSTS ) iY = iRowCount-1;
						if( bSTS ) break;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = iColCount-1;
            	    	iY = iRowCount-1;
            		}
	        	}
				if(SGr_vRIRE_SYUKA->RowCount <= iY
                || SGr_vRIRE_SYUKA->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE = true;
					while( 1 )
					{
						SGr_vRIRE_SYUKA->Row = iY;
						SGr_vRIRE_SYUKA->Col = iX;
						if(SGr_vRIRE_SYUKA->Col == iX && SGr_vRIRE_SYUKA->Row == iY) break;
						for(i1=0;i1 < iRowCount ; i1++)
						{
    	    				SGr_vRIRE_SYUKA->Row = i1;
        	            	SGr_vRIRE_SYUKA->Col = iX;
							if( SGr_vRIRE_SYUKA->Col == iX)
							{
                    			SGr_vRIRE_SYUKA->Row = iY;
                        	    break;
							}
    	                }
						break;
					}
					bKASOU_MOVE = false;
				}
				break;
	        case 3:
		        while( !bSTS )
    		    {
        			for(iX = iX;iX >= 0; iX--)
            		{
            			for(iY = iY;iY > 0; iY--)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].INS_ON != false)
                        //���荀�ږ���������ɒǉ�
                            && (AnsiString(pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
            	        		bSTS= true;
                	        	break;
                    		}
	                	}
						if( !bSTS ) iY = iRowCount-1;
						if( bSTS ) break;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = iColCount - 1;
            	    	iY = iRowCount - 1;
            		}
	        	}
				if(SGr_vSOKU_SOZAI->RowCount <= iY
                || SGr_vSOKU_SOZAI->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE = true;
					while( 1 )
					{
						SGr_vSOKU_SOZAI->Row = iY;
						SGr_vSOKU_SOZAI->Col = iX;
						if(SGr_vSOKU_SOZAI->Col == iX && SGr_vSOKU_SOZAI->Row == iY) break;
						for(i1=0;i1 < iRowCount ; i1++)
						{
    	    				SGr_vSOKU_SOZAI->Row = i1;
        	            	SGr_vSOKU_SOZAI->Col = iX;
							if( SGr_vSOKU_SOZAI->Col == iX)
							{
                    			SGr_vSOKU_SOZAI->Row = iY;
                        	    break;
							}
    	                }
						break;
					}
					bKASOU_MOVE = false;
				}
				break;
	        case 4:
		        while( !bSTS )
    		    {
        			for(iX = iX;iX >= 0; iX--)
            		{
            			for(iY = iY;iY > 0; iY--)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].INS_ON != false)
                        //���荀�ږ���������ɒǉ�
                            && (AnsiString(pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
            	        		bSTS= true;
                	        	break;
                    		}
	                	}
						if( !bSTS ) iY = iRowCount-1;
						if( bSTS ) break;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = iColCount-1;
            	    	iY = iRowCount-1;
            		}
	        	}
				if(SGr_vRIRE_SOZAI->RowCount <= iY
                || SGr_vRIRE_SOZAI->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE = true;
					while( 1 )
					{
						SGr_vRIRE_SOZAI->Row = iY;
						SGr_vRIRE_SOZAI->Col = iX;
						if(SGr_vRIRE_SOZAI->Col == iX && SGr_vRIRE_SOZAI->Row == iY) break;
						for(i1=0;i1 < iRowCount ; i1++)
						{
    	    				SGr_vRIRE_SOZAI->Row = i1;
        	            	SGr_vRIRE_SOZAI->Col = iX;
							if( SGr_vRIRE_SOZAI->Col == iX)
							{
                    			SGr_vRIRE_SOZAI->Row = iY;
                        	    break;
							}
    	                }
						break;
					}
					bKASOU_MOVE = false;
				}
				break;
    		}
    	}
    }
    //2003.05.15�@M.HIRAI
    //�{�^���N���b�N���̑Ή��i�O���b�h�փt�H�[�J�X�ړ��j
	switch(iTargetGrid)
    {
    case 1:
    	Form1->SGr_vSOKU_SYUKA->SetFocus();
        break;
    case 2:
    	Form1->SGr_vRIRE_SYUKA->SetFocus();
        break;
    case 3:
    	Form1->SGr_vSOKU_SOZAI->SetFocus();
        break;
    case 4:
    	Form1->SGr_vRIRE_SOZAI->SetFocus();
        break;
    default:
    	break;
    }

    bKASOU_MOVE = false;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F����ҏW��ʂ�`�悵�܂��B
//
//  �@�\����
//    �Z���C���t�H�ɂ���RESULT�l�i���͒l�j��`�悵�܂��B
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
//---------------------------------------------------------------------------
void __fastcall TForm1::DISP_SCREEN_SET(void)
{
	int i1,i2;
	//����o�׃O���b�h
	if(hCELLINFO_SOKU_SYUKA)
	{
		for(i1 = 0; i1 < SGr_vSOKU_SYUKA->ColCount ;i1++)
		{
			for(i2 = 1;i2 < SGr_vSOKU_SYUKA->RowCount ; i2++)
			{
				SGr_vSOKU_SYUKA->Cells[i1][i2] = pCELLINFO_SOKU_SYUKA[i1*SGr_vSOKU_SYUKA->RowCount+i2].DISP_RESULT;
			}
        }
	}
	//�����o�׃O���b�h
	if(hCELLINFO_RIRE_SYUKA)
	{
		for(i1 = 0; i1 < SGr_vRIRE_SYUKA->ColCount ;i1++)
		{
			for(i2 = 1;i2 < SGr_vRIRE_SYUKA->RowCount ; i2++)
			{
				SGr_vRIRE_SYUKA->Cells[i1][i2] = pCELLINFO_RIRE_SYUKA[i1*SGr_vRIRE_SYUKA->RowCount+i2].DISP_RESULT;
			}
        }
	}
	//����f�ރO���b�h
	if(hCELLINFO_SOKU_SOZAI)
	{
		for(i1 = 0; i1 < SGr_vSOKU_SOZAI->ColCount ;i1++)
		{
			for(i2 = 1;i2 < SGr_vSOKU_SOZAI->RowCount ; i2++)
			{
				SGr_vSOKU_SOZAI->Cells[i1][i2] = pCELLINFO_SOKU_SOZAI[i1*SGr_vSOKU_SOZAI->RowCount+i2].DISP_RESULT;
			}
        }
	}
	//����o�׃O���b�h
	if(hCELLINFO_RIRE_SOZAI)
	{
		for(i1 = 0; i1 < SGr_vRIRE_SOZAI->ColCount ;i1++)
		{
			for(i2 = 1;i2 < SGr_vRIRE_SOZAI->RowCount ; i2++)
			{
				SGr_vRIRE_SOZAI->Cells[i1][i2] = pCELLINFO_RIRE_SOZAI[i1*SGr_vRIRE_SOZAI->RowCount+i2].DISP_RESULT;
			}
        }
	}
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�����ʂ�`�悵�܂��B
//
//  �@�\����
//    �Z���C���t�H�ɂ���RESULT�l�i���͒l�j��`�悵�܂��B
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
//---------------------------------------------------------------------------
void __fastcall TForm1::SCREEN_SET(void)
{
	int i1,i2;
	//����o�׃O���b�h
	if(hCELLINFO_SOKU_SYUKA)
	{
		for(i1 = 0; i1 < SGr_vSOKU_SYUKA->ColCount ;i1++)
		{
			for(i2 = 1;i2 < SGr_vSOKU_SYUKA->RowCount ; i2++)
			{
				SGr_vSOKU_SYUKA->Cells[i1][i2] = pCELLINFO_SOKU_SYUKA[i1*SGr_vSOKU_SYUKA->RowCount+i2].RESULT;
			}
        }
	}
	//�����o�׃O���b�h
	if(hCELLINFO_RIRE_SYUKA)
	{
		for(i1 = 0; i1 < SGr_vRIRE_SYUKA->ColCount ;i1++)
		{
			for(i2 = 1;i2 < SGr_vRIRE_SYUKA->RowCount ; i2++)
			{
				SGr_vRIRE_SYUKA->Cells[i1][i2] = pCELLINFO_RIRE_SYUKA[i1*SGr_vRIRE_SYUKA->RowCount+i2].RESULT;
			}
        }
	}
	//����f�ރO���b�h
	if(hCELLINFO_SOKU_SOZAI)
	{
		for(i1 = 0; i1 < SGr_vSOKU_SOZAI->ColCount ;i1++)
		{
			for(i2 = 1;i2 < SGr_vSOKU_SOZAI->RowCount ; i2++)
			{
				SGr_vSOKU_SOZAI->Cells[i1][i2] = pCELLINFO_SOKU_SOZAI[i1*SGr_vSOKU_SOZAI->RowCount+i2].RESULT;
			}
        }
	}
	//����o�׃O���b�h
	if(hCELLINFO_RIRE_SOZAI)
	{
		for(i1 = 0; i1 < SGr_vRIRE_SOZAI->ColCount ;i1++)
		{
			for(i2 = 1;i2 < SGr_vRIRE_SOZAI->RowCount ; i2++)
			{
				SGr_vRIRE_SOZAI->Cells[i1][i2] = pCELLINFO_RIRE_SOZAI[i1*SGr_vRIRE_SOZAI->RowCount+i2].RESULT;
			}
        }
	}
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�R�}���h���C�������𕪗��i�������A���[�U���Ȃǁj
//
//  �@�\����
//    �v���O�����N�����̃R�}���h���C�������𕪗����ϐ��ɐݒ肵�܂��B
//    ���[�U�R�[�h�A���[�U���A�����R�[�h�A�������A�f�o�b�O���[�h�𒊏o���܂�
//
//  �p�����^����
//    AnsiString str	�F�R�}���h���C��������
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �v���O�����N�����Ɏg�p
//
//---------------------------------------------------------------------------
void __fastcall TForm1::ExtractCode(AnsiString str)
{
    //���[�U�R�[�h�A���[�U���A�����R�[�h�A������ ���o
    int i,n1,m,strlen;

    //������
    USER_COD = 0;
    USER_NAM = "";
    BUMO_COD = "";
    BUMO_NAM = "";

    strlen = str.Length();
    n1 = m = 1;

    for ( i = 1; i <= strlen; i++ ) {
        //��؂�L��","�̌���
        if ( str.SubString(i,1) == "," ) {
            if ( n1 < i ) {
            //n1=i�̎��͕�����NULL
                switch(m){
                //�ϐ��ɕ�������
                    case 1:
                    //USER_COD
                        USER_COD = StrToInt(str.SubString(n1,i - n1));
                        break;
                    case 2:
                    //USER_NAM
                        USER_NAM = str.SubString(n1,i - n1);
                        break;
                    case 3:
                    //BUMO_COD
                        BUMO_COD = str.SubString(n1,i - n1);
                        break;
                    case 4:
                    //BUMO_NAM
                        BUMO_NAM = str.SubString(n1,i - n1);
                        break;
					case 5:
						iDEBUG = AnsiString(str.SubString(n1,i - n1)).ToIntDef(0);
                    default:
                        break;
                }

            }
            //���̕�����J�n�ʒu
            n1 = i + 1;
            m++;

        }
    }
    if ( m <= 4 ) {
        BUMO_NAM = str.SubString(n1,strlen - n1 + 1);
    }

    // �������\��
    PnlBumCode->Caption = BUMO_COD;
    PnlBumName->Caption = BUMO_NAM;
    PnlTanCode->Caption = IntToStr(USER_COD);
    PnlTanName->Caption = USER_NAM;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    SetEditText�C�x���g	�F�O���b�h��ŃZ���̓��͂��s����Ɣ������܂��B
//
//  �@�\����
//    ����p�̒l�̓��́B
//    �����񒷂̊m�F
//
//  �p�����^����
//    TObject *Sender	            �F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol                      �F�ΏۃZ���̃J�����ʒu
//    int ARow                      �F�ΏۃZ���̂q�n�v�ʒu
//  �@const AnsiString Value        �F�Z���̕�����
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::GRID_SetEditText(TObject *Sender,
      int ACol, int ARow, const AnsiString Value)
{
	int i1,iGrid;
	AnsiString sBuf,sDeci1;
    bool bRtn;

  	if(Sender == SGr_vSOKU_SYUKA) iGrid = 1;
 	if(Sender == SGr_vRIRE_SYUKA) iGrid = 2;
 	if(Sender == SGr_vSOKU_SOZAI) iGrid = 3;
 	if(Sender == SGr_vRIRE_SOZAI) iGrid = 4;

	switch( iGrid )
    {
    case 1:
		//�������[�`�F�b�N
		if( !hCELLINFO_SOKU_SYUKA ) return;
		switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
        {
        case 0:		//�����E����
        case 1:		//�p�x
        	sDeci1 = "0";
            for(i1 = 0;i1 < AnsiString(pCELLINFO_SOKU_SYUKA[(ACol*SGr_vSOKU_SYUKA->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
            {
            	if( sDeci1.Length() == 1 ) sDeci1 += ".";
                sDeci1 +="0";
            }
        //���͂��Ȃ���
        	if(AnsiString(Value).Length() == 0)
            {
            	sBuf =Value;
                break;
            }
        //���̓`�F�b�N
            //2003.05.08 E.Takase Add��
            bRtn = ConvDoubleDefS(Value,sDeci1,Value,&sBuf);
            //2003.05.08 E.Takase Add��
            break;
        case 2:  	//�ǁE��
        default:	//����
        	sBuf = Value;
            sBuf = sBuf.Trim();
            break;
        }
		sBuf = sBuf.SubString(1,14);
        if( sBuf.Length() == 14 ){
    		if ( sBuf.ByteType( 14 ) == mbLeadByte ){
				sBuf = sBuf.SubString(1,13);
            }
        }
        strcpy(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].DISP_RESULT,sBuf.c_str());

        if(SGr_vSOKU_SYUKA->Row == ARow && SGr_vSOKU_SYUKA->Col == ACol && bCellWrite == false)
        {
            Get_GRAPHLOT(Get_GRAPHSTART_Info(ARow,ACol,iGrid),ACol,iGrid);
        }
		break;

    case 2:
		//�������[�`�F�b�N
		if( !hCELLINFO_RIRE_SYUKA ) return;
		switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
        {
        case 0:		//�����E����
        case 1:		//�p�x
        	sDeci1 = "0";
            for(i1 = 0;i1 < AnsiString(pCELLINFO_RIRE_SYUKA[(ACol*SGr_vRIRE_SYUKA->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
            {
            	if( sDeci1.Length() == 1 ) sDeci1 += ".";
                sDeci1 +="0";
            }
        //���͂��Ȃ���
        	if(AnsiString(Value).Length() == 0)
            {
            	sBuf =Value;
                break;
            }
        //���̓`�F�b�N
            //2003.05.08 E.Takase Add��
            bRtn = ConvDoubleDefS(Value,sDeci1,Value,&sBuf);
            //2003.05.08 E.Takase Add��
            break;
        case 2:  	//�ǁE��
        default:	//����
        	sBuf = Value;
            sBuf = sBuf.Trim();
        	break;
        }

		sBuf = sBuf.SubString(1,14);
        if( sBuf.Length() == 14 ){
    		if ( sBuf.ByteType( 14 ) == mbLeadByte ){
				sBuf = sBuf.SubString(1,13);
            }
        }
        strcpy(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].DISP_RESULT,sBuf.c_str());

        if(SGr_vRIRE_SYUKA->Row == ARow && SGr_vRIRE_SYUKA->Col == ACol && bCellWrite == false)
        {
            Get_GRAPHLOT(Get_GRAPHSTART_Info(ARow,ACol,iGrid),ACol,iGrid);
        }
		break;

    case 3:
		//�������[�`�F�b�N
		if( !hCELLINFO_SOKU_SOZAI ) return;
		switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
        {
        case 0:		//�����E����
        case 1:		//�p�x
        	sDeci1 = "0";
            for(i1 = 0;i1 < AnsiString(pCELLINFO_SOKU_SOZAI[(ACol*SGr_vSOKU_SOZAI->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
            {
            	if( sDeci1.Length() == 1 ) sDeci1 += ".";
                sDeci1 +="0";
            }
        //���͂��Ȃ���
        	if(AnsiString(Value).Length() == 0)
            {
            	sBuf =Value;
                break;
            }
        //���̓`�F�b�N
            //2003.05.08 E.Takase Add��
            bRtn = ConvDoubleDefS(Value,sDeci1,Value,&sBuf);
            //2003.05.08 E.Takase Add��
            break;
        case 2:  	//�ǁE��
        default:	//����
        	sBuf = Value;
            sBuf = sBuf.Trim();
        	break;
        }
		sBuf = sBuf.SubString(1,14);
        if( sBuf.Length() == 14 ){
    		if ( sBuf.ByteType( 14 ) == mbLeadByte ){
				sBuf = sBuf.SubString(1,13);
            }
        }
        strcpy(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].DISP_RESULT,sBuf.c_str());

        if(SGr_vSOKU_SOZAI->Row == ARow && SGr_vSOKU_SOZAI->Col == ACol && bCellWrite == false)
        {
            Get_GRAPHLOT(Get_GRAPHSTART_Info(ARow,ACol,iGrid),ACol,iGrid);
        }
		break;

    case 4:
		//�������[�`�F�b�N
		if( !hCELLINFO_RIRE_SOZAI ) return;
		switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
        {
        case 0:		//�����E����
        case 1:		//�p�x
        	sDeci1 = "0";
            for(i1 = 0;i1 < AnsiString(pCELLINFO_RIRE_SOZAI[(ACol*SGr_vRIRE_SOZAI->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
            {
            	if( sDeci1.Length() == 1 ) sDeci1 += ".";
                sDeci1 +="0";
            }
        //���͂��Ȃ���
        	if(AnsiString(Value).Length() == 0)
            {
            	sBuf =Value;
                break;
            }
        //���̓`�F�b�N
            //2003.05.08 E.Takase Add��
            bRtn = ConvDoubleDefS(Value,sDeci1,Value,&sBuf);
            //2003.05.08 E.Takase Add��
            break;
        case 2:  	//�ǁE��
        default:	//����
        	sBuf = Value;
            sBuf = sBuf.Trim();
        	break;
        }
		sBuf = sBuf.SubString(1,14);
        if( sBuf.Length() == 14 ){
    		if ( sBuf.ByteType( 14 ) == mbLeadByte ){
				sBuf = sBuf.SubString(1,13);
            }
        }
        strcpy(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].DISP_RESULT,sBuf.c_str());

        if(SGr_vRIRE_SOZAI->Row == ARow && SGr_vRIRE_SOZAI->Col == ACol && bCellWrite == false)
        {
            Get_GRAPHLOT(Get_GRAPHSTART_Info(ARow,ACol,iGrid),ACol,iGrid);
        }
		break;

	}

}

//---------------------------------------------------------------------------
//
//  �T�v
//    FormEnter�C�x���g	�F�t�H�[���Ƀt�H�[�J�X�������������ɔ������܂��B
//
//  �@�\����
//    �ꗗ�����{�^���̗L���A���������肵�܂��B
//
//  �p�����^����
//    TObject *Sender	            �F�Ăяo������VCL�I�u�W�F�N�g
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::FormEnter(TObject *Sender)
{

    AnsiString	sBuf;
    TComponent	*cmp	= dynamic_cast<TComponent*>(Sender);

    if( BtnF01->Focused() )		return;

    sBuf = cmp->Name;

    // �������@��\���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
    if( Cmb_DTKSHIN->Focused() || sBuf == "Cmb_DTKSHIN" ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        Form2->Tag = 1;
        return;
    }

    // �������@���b�gNO�Ƀt�H�[�J�X���L��ꍇ
    if( Edt_LOTNO->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        Form2->Tag = 2;
        return;
    }

    if( Form2->Tag == 12 ){
        BtnF01->Enabled = true;
        Form2->Tag = 12;
        return;
    }

    // �uF1�F�ꗗ�����v�{�^�����g���Ȃ��悤�ɂ���
    BtnF01->Enabled = false;


}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�n�j���̃T�E���h��������܂��B
//
//  �@�\����
//    �����̂v�`�u�f�[�^������܂��B
//
//  �p�����^����
//    AnsiString str	�F�R�}���h���C��������
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �v���O�����N�����Ɏg�p
//
//---------------------------------------------------------------------------
void __fastcall TForm1::OK_BEEP(TObject *Sender)
{
	MdPlayer->FileName = "RS_OK.wav";
	MdPlayer->Open();
	MdPlayer->Play();
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�m�f���̃T�E���h��������܂��B
//
//  �@�\����
//    �����̂v�`�u�f�[�^������܂��B
//
//  �p�����^����
//    AnsiString str	�F�R�}���h���C��������
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �v���O�����N�����Ɏg�p
//
//---------------------------------------------------------------------------
void __fastcall TForm1::NG_BEEP(TObject *Sender)
{
	MdPlayer2->FileName = "RS_NG.wav";
	MdPlayer2->Open();
	MdPlayer2->Play();

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F���荀�ڕύX���̃T�E���h��������܂��B
//
//  �@�\����
//    �����̂v�`�u�f�[�^������܂��B
//
//  �p�����^����
//    AnsiString str	�F�R�}���h���C��������
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �v���O�����N�����Ɏg�p
//
//---------------------------------------------------------------------------
void __fastcall TForm1::KMCH_BEEP(TObject *Sender)
{
	MdPlayer3->FileName = "KM_Change.wav";
	MdPlayer3->Open();
	MdPlayer3->Play();

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�n���f�B�^�[�~�i������f�[�^��UPLOAD���܂��B
//
//  �@�\����
//    COM3��ʐM�|�[�g�Ƃ��A�n���f�B�[�^�[�~�i������f�[�^��UPLOAD���܂��B
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    -1                �F�ʐM�G���[
//     1                �F����I��
//
//  ���l
//    �Ö傳��쐬�֐�
//
//---------------------------------------------------------------------------
int TForm1::DataUpLoad()
{
    //TODO ���̉��ɃR�[�h��ǉ����Ă�������

	char tmp[64];
	int rtn;
    int nFlag;						// �����t���O�@
    AnsiString asBufData,asBuf;		// �|�[�g�o�b�t�@�p
	AnsiString sTmp1, sTmp2;
	time_t nowTime;


    nFlag = 0;
    while (1) {
		switch (nFlag) {
		case 0:
			nFlag = 10;
			break;
		case 10:
			// �ʐM�|�[�g�I�[�v��
			rtn = CommOpen("COM3","115200","N,8,1");
			if (rtn < 0) {
				MessageBox(NULL, "�ʐM�|�[�g�I�[�v���G���[", "�G���[", MB_ICONSTOP);
			}
			iComPort = rtn;
			nFlag = 200;
			break;
		case 200:
			// ��M
			sprintf(tmp, "%c%s%c", STX, "1A**", ETX);
	        /*
	        sprintf(tmp, "%c%s", STX, "1A");
			// BCC�`�F�b�N
			if (chkBCC->State == cbChecked) {
				sTmp1 = tmp;
				sTmp2 = CreatBCC(sTmp1);
				strcat(tmp, sTmp2.c_str());
			} else
				strcat(tmp, "**");
			//sprintf(tmp, "%s%c", tmp, ETX);
			tmp[5] = ETX;
			tmp[6] = '\0';
	        */
	        CommClear(iComPort);                       // �|�[�g�o�b�t�@�N���A
			CommWrite(iComPort, tmp);				   // �A�b�v���[�h�R�}���h���M
			time(&sTime);
			nFlag = 210;
			break;
		case 210:
			// �^�C���A�E�g�`�F�b�N
			time(&nowTime);
			if (nowTime - sTime > 1) {
                CommClose(iComPort);
				return (-1);
			}

			nFlag = 220;
			break;
		case 220:
			// �o�b�t�@��M
			asBufData = DataReceive();
            if (asBufData.IsEmpty() == true) {
                CommClose(iComPort);
                return (-1);
            }

			// ���M����
			if (asBufData.AnsiPos("\x06") > 0) {
				nFlag = 230;	// ACK��M
			} else {
                CommClose(iComPort);
                return (-1);	// NAK��M
            }
			break;
		case 230:
	        // �^�C���A�E�g�`�F�b�N
			time(&nowTime);
			if (nowTime - sTime > 1) {
                CommClose(iComPort);
				return (-1);
			}
			nFlag = 240;
			break;
		case 240:
			// �o�b�t�@��M�@
			asBufData = DataReceive();
            if (asBufData.IsEmpty() == true) {
                CommClose(iComPort);
                return (-1);
            }
			asBuf = asBufData.SubString(9,32);
			// �f�[�^������ꍇ�i�f�[�^�ԍ���"00000"�ȊO�j�͏o��
			// �f�[�^ID��4�o�C�g�ڂ���5�o�C�g���i"00001�`99999"�j
			if (asBufData.SubString(4,5) != "00000"){
                sShiji_Data->Add(asBuf);
			}
			nFlag = 250;
			break;
		case 250:
			// ACK���M
			sprintf(tmp, "%c%s%c%s%c", STX, "1R", ACK, "**", ETX);
	        /*
	        sprintf(tmp, "%c%s%c", STX, "1R", ACK);
			// BCC�`�F�b�N
			if (chkBCC->State == cbChecked) {
				sTmp1 = tmp;
				sTmp2 = CreatBCC(sTmp1);
				strcat(tmp, sTmp2.c_str());
			} else
				strcat(tmp, "**");
			//sprintf(tmp, "%s%c", tmp, ETX);
			tmp[6] = ETX;
			tmp[7] = '\0';
	        */
			CommClear(iComPort);		// �|�[�g�o�b�t�@�N���A
			CommWrite(iComPort, tmp);   // ���M
			// �f�[�^������΃o�b�t�@��M����J��Ԃ�
			if (asBufData.SubString(4,5) != "00000")
				nFlag = 240;
			else {
				nFlag = 999;
	        }
			break;
		case 999:
			// �ʐM�I��
			CommClose(iComPort);          // �|�[�g�N���[�Y
	        return(1);
		}
	}
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�[�^��M�����B
//
//  �@�\����
//    �n���f�B�[�^�[�~�i������P�o�C�g���Ƀf�[�^��ǂݎ��ETX�Ŕ�����B
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    ""                �F�ʐM�G���[
//    �i��or���b�g������F����I��
//
//  ���l
//    �Ö傳��쐬�֐�
//
//---------------------------------------------------------------------------
AnsiString TForm1::DataReceive()
{
	//TODO ���̉��ɃR�[�h��ǉ����Ă�������
	int iSW;
	char Buf[64];
	AnsiString asRet;
	AnsiString asRecBuf;
	time_t nowTime;

	iSW = 10;
	// ����t���[�ݒ� ON
	CommSetFlow(iComPort,1,1,1,1,1);
	while (1){
		// �^�C���A�E�g�`�F�b�N
		time(&nowTime);
		if (nowTime - sTime > 1) {
			MessageDlg("�ʐM���^�C���A�E�g�ɂȂ�܂����B", mtError, TMsgDlgButtons() << mbOK , 0);
			return "";
		}
		// �P�o�C�g���Ɏ擾
		CommReadNum(iComPort,Buf,1);
		switch (iSW){
		case 10:
			// �w�b�_��� STX�i0x02�j
			if (Buf[0] == STX) {
				asRecBuf = Buf[0];
				iSW++;
			}
			break;
		case 11:
			// ID���
			if (Buf[0] == '1' || Buf[0] == '2'){
				asRecBuf = asRecBuf + Buf[0];
				iSW++;
			}
			break;
		case 12:
			//  �敪���
			if (Buf[0] == 'A' || Buf[0] == 'D' || Buf[0] == 'R' ||
				Buf[0] == 'S' || Buf[0] == 'M'){
				asRecBuf = asRecBuf + Buf[0];
				iSW++;
			}
			break;
		case 13:
			// �t�b�^��� ETX�i0x03�j
			// �t�b�^�iETX�j�ɂȂ����珈���𔲂���@
			if (Buf[0] == ETX){
				asRecBuf = asRecBuf + Buf[0];
				iSW = 20;
				break;
			} else {
				// �f�[�^��
				asRecBuf = asRecBuf + Buf[0];
			}
			break;
//		case 14:
//			iSW = 20;
//			break;
		}
		if (iSW == 20) break;
	}
	// ����t���[�ݒ� OFF
	CommSetFlow(iComPort,0,0,0,0,0);
	return (asRecBuf);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnChange�C�x���g	�F�ҏW�̈�ɕ\�����ꂽ�e�L�X�g���ύX�����Ɣ������܂��B
//
//  �@�\����
//    ��\���Ӑ�i�Ԃ̓��͂�啶���ɕς���B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    ��������쐬�֐�
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Cmb_DTKSHINChange(TObject *Sender)
{
    int			i;
    int			iSelStart;
    AnsiString	sBuf;
    TComboBox* cmb = dynamic_cast<TComboBox*>(Sender);

    sBuf = cmb->Text;
    iSelStart = cmb->SelStart;
    
    if (cmb->ItemIndex >= 0) {
        // LOT��\��
        Edt_LOTNO->Text = sHT_LOT->Strings[cmb->ItemIndex];
        // �C���f�b�N�X�\��
        sBuf = AnsiString(cmb->ItemIndex + 1) + "/" + AnsiString(sHT_LOT->Count);
        Lab_Num->Caption = sBuf;
    }

    // �V���O���R�[�e�[�V�����͂c�a�o�^���ɃG���[����������
    // �̂őS�p�̃V���O���R�[�e�[�V�����ɕϊ����܂�
    i = sBuf.AnsiPos("'");
    if( i > 0 ){
        sBuf.Delete( i, 1);
        if( cmb->MaxLength == 0 || cmb->MaxLength >= sBuf.Length() + 2 ){
        	sBuf.Insert("�f",i);
    	}
        //cmb->Text = sBuf;
        //cmb->SelStart = i + 1;
        iSelStart = i + 1;
    }
    // 2003/9/10 A.Tamura
    //cmb->Text = sBuf.UpperCase();

    cmb->SelStart = iSelStart;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnTopLeftChanged �C�x���g	�FTopRow �v���p�e�B�܂��� LeftCol �v���p�e�B���ύX���ꂽ����ɔ������܂��B
//
//  �@�\����
//    �f�ށi�����j�Ƒ���StringGrid�̃X�N���[���A�g�����邽�߂̊֐��ł��B
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
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tRIRE_SOZAITopLeftChanged(TObject *Sender)
{

    // ����Grid�A�X�N���[���{�b�N�X�̘A�g
    SGr_vRIRE_SYUKA->LeftCol = SGr_tRIRE_SOZAI->LeftCol;
    SGr_tRIRE->LeftCol       = SGr_tRIRE_SOZAI->LeftCol;
    SGr_vRIRE_SOZAI->LeftCol = SGr_tRIRE_SOZAI->LeftCol;
    SGr_tRIRE_SYUKA->LeftCol = SGr_tRIRE_SOZAI->LeftCol;
	SBx_vRIRE_MEMO->HorzScrollBar->Position = SGr_tRIRE_SOZAI->LeftCol *  Mem_vRIRE_MEMOORG->Width;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnTopLeftChanged �C�x���g	�FTopRow �v���p�e�B�܂��� LeftCol �v���p�e�B���ύX���ꂽ����ɔ������܂��B
//
//  �@�\����
//    �o�ׁi�����j�Ƒ���StringGrid�̃X�N���[���A�g�����邽�߂̊֐��ł��B
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
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tRIRE_SYUKATopLeftChanged(TObject *Sender)
{

    // ����Grid�A�X�N���[���{�b�N�X�̘A�g
    SGr_vRIRE_SYUKA->LeftCol = SGr_tRIRE_SYUKA->LeftCol;
    SGr_tRIRE->LeftCol       = SGr_tRIRE_SYUKA->LeftCol;
    SGr_vRIRE_SOZAI->LeftCol = SGr_tRIRE_SYUKA->LeftCol;
    SGr_tRIRE_SOZAI->LeftCol = SGr_tRIRE_SYUKA->LeftCol;
	SBx_vRIRE_MEMO->HorzScrollBar->Position = SGr_tRIRE_SYUKA->LeftCol *  Mem_vRIRE_MEMOORG->Width;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnTopLeftChanged �C�x���g	�FTopRow �v���p�e�B�܂��� LeftCol �v���p�e�B���ύX���ꂽ����ɔ������܂��B
//
//  �@�\����
//    �f�ށi����j�Ƒ���StringGrid�̃X�N���[���A�g�����邽�߂̊֐��ł��B
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
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tSOKU_SOZAITopLeftChanged(TObject *Sender)
{

    // ����Grid�A�X�N���[���{�b�N�X�̘A�g
    SGr_vSOKU_SYUKA->LeftCol = SGr_tSOKU_SOZAI->LeftCol;
    SGr_tSOKU->LeftCol       = SGr_tSOKU_SOZAI->LeftCol;
    SGr_vSOKU_SOZAI->LeftCol = SGr_tSOKU_SOZAI->LeftCol;
    SGr_tSOKU_SYUKA->LeftCol = SGr_tSOKU_SOZAI->LeftCol;
	SBx_vSOKU_MEMO->HorzScrollBar->Position = SGr_tSOKU_SOZAI->LeftCol *  Mem_vSOKU_MEMOORG->Width;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnTopLeftChanged �C�x���g	�FTopRow �v���p�e�B�܂��� LeftCol �v���p�e�B���ύX���ꂽ����ɔ������܂��B
//
//  �@�\����
//    �o�ׁi����j�Ƒ���StringGrid�̃X�N���[���A�g�����邽�߂̊֐��ł��B
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
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tSOKU_SYUKATopLeftChanged(TObject *Sender)
{

    // ����Grid�A�X�N���[���{�b�N�X�̘A�g
    SGr_vSOKU_SYUKA->LeftCol = SGr_tSOKU_SYUKA->LeftCol;
    SGr_tSOKU->LeftCol       = SGr_tSOKU_SYUKA->LeftCol;
    SGr_vSOKU_SOZAI->LeftCol = SGr_tSOKU_SYUKA->LeftCol;
    SGr_tSOKU_SOZAI->LeftCol = SGr_tSOKU_SYUKA->LeftCol;
	SBx_vSOKU_MEMO->HorzScrollBar->Position = SGr_tSOKU_SYUKA->LeftCol *  Mem_vSOKU_MEMOORG->Width;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnGetEditText �C�x���g	�F�C���v���[�X�G�f�B�^���Z���̒l��v�������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �f�ށi����j�Z���̒l�v�����ɃZ���N�g�Z���𔭐����܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol          �F�ΏۃZ���̃J�����ʒu
//  �@int ARow          �F�ΏۃZ����ROW�ʒu
//  �@AnsiString &Value �F�Z���̕�����
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vSOKU_SOZAIGetEditText(TObject *Sender,
      int ACol, int ARow, AnsiString &Value)
{
	if( iRow_vSOKU_SOZAI == ARow &&
        iCol_vSOKU_SOZAI == ACol ){

        bool	CanSelect;
		AllGRID_SelectCell(	SGr_vSOKU_SOZAI,
        					ACol,
               	            ARow,
                   	        CanSelect);
    }
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnGetEditText �C�x���g	�F�C���v���[�X�G�f�B�^���Z���̒l��v�������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �o�ׁi����j�Z���̒l�v�����ɃZ���N�g�Z���𔭐����܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol          �F�ΏۃZ���̃J�����ʒu
//  �@int ARow          �F�ΏۃZ����ROW�ʒu
//  �@AnsiString &Value �F�Z���̕�����
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vSOKU_SYUKAGetEditText(TObject *Sender,
      int ACol, int ARow, AnsiString &Value)
{
	if( iRow_vSOKU_SYUKA == ARow &&
        iCol_vSOKU_SYUKA == ACol ){

        bool	CanSelect;
		AllGRID_SelectCell(	SGr_vSOKU_SYUKA,
        					ACol,
               	            ARow,
                   	        CanSelect);
    }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnGetEditText �C�x���g	�F�C���v���[�X�G�f�B�^���Z���̒l��v�������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �f�ށi�����j�Z���̒l�v�����ɃZ���N�g�Z���𔭐����܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol          �F�ΏۃZ���̃J�����ʒu
//  �@int ARow          �F�ΏۃZ����ROW�ʒu
//  �@AnsiString &Value �F�Z���̕�����
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vRIRE_SOZAIGetEditText(TObject *Sender,
      int ACol, int ARow, AnsiString &Value)
{
	if( iRow_vRIRE_SOZAI == ARow &&
        iCol_vRIRE_SOZAI == ACol ){

        bool	CanSelect;
		AllGRID_SelectCell(	SGr_vRIRE_SOZAI,
        					ACol,
               	            ARow,
                   	        CanSelect);
    }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnGetEditText �C�x���g	�F�C���v���[�X�G�f�B�^���Z���̒l��v�������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �o�ׁi�����j�Z���̒l�v�����ɃZ���N�g�Z���𔭐����܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol          �F�ΏۃZ���̃J�����ʒu
//  �@int ARow          �F�ΏۃZ����ROW�ʒu
//  �@AnsiString &Value �F�Z���̕�����
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vRIRE_SYUKAGetEditText(TObject *Sender,
      int ACol, int ARow, AnsiString &Value)
{
	if( iRow_vRIRE_SYUKA == ARow &&
        iCol_vRIRE_SYUKA == ACol ){

        bool	CanSelect;
		AllGRID_SelectCell(	SGr_vRIRE_SYUKA,
        					ACol,
               	            ARow,
                   	        CanSelect);
    }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnResize �C�x���g �F�X�N���[���{�b�N�X���T�C�Y�ύX�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    ������l���̃X�N���[���{�b�N�X���T�C�Y�ύX�����Ƃ��ɔ������܂��B
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
//---------------------------------------------------------------------------
void __fastcall TForm1::SBx_vSOKU_MEMOResize(TObject *Sender)
{
	if(SGr_tSOKU->Cells[0][0]!="" && !bNowF7 )
	{
        int	i1;
		for(i1 = 0 ; i1 < SGr_tSOKU->ColCount ;i1++)
		{
           	Mem_vSOKU_MEMO[i1]->Height	= SBx_vSOKU_MEMO->Height - 1;
    	}
	}
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnResize �C�x���g �F�X�N���[���{�b�N�X���T�C�Y�ύX�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    ������l���̃X�N���[���{�b�N�X���T�C�Y�ύX�����Ƃ��ɔ������܂��B
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
//---------------------------------------------------------------------------
void __fastcall TForm1::SBx_vRIRE_MEMOResize(TObject *Sender)
{
	if(SGr_tRIRE->Cells[0][0]!="" && !bNowF7 )
	{
        int	i1;
		for(i1 = 0 ; i1 < SGr_tRIRE->ColCount ;i1++)
		{
           	Mem_vRIRE_MEMO[i1]->Height	= SBx_vRIRE_MEMO->Height - 1;
    	}
	}

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐� �F������𐔒l�ɕϊ�����B
//
//  �@�\����
//    ������𐔒l�ɕϊ�����B�ϊ��G���[�̏ꍇ�̓f�t�H���g�l�i���l�^�j��Ԃ��܂��B
//
//  �p�����^����
//    AnsiString sTarget	�F�ϊ����镶����
//    double dValue         �F�f�t�H���g�l
//  �߂�l
//    �ϊ�������            �F�ϊ����ꂽ���l
//  �@�ϊ����s              �F�f�t�H���g�l
//
//  ���l
//****************************************************************************
//2003.05.08 E.Takase Add
//---------------------------------------------------------------------------
//������𐔒l�ɕϊ�����B�ϊ��G���[�̏ꍇ�̓f�t�H���g�l�i���l�^�j��Ԃ�
//****************************************************************************
//
//---------------------------------------------------------------------------
double __fastcall TForm1::ConvDoubleDefD(AnsiString sTarget, double dValue)
{
	AnsiString 	sBuf;
	AnsiString 	sTargetTrim;
	AnsiString 	sCheckStr;
	int 		iLength;
	int 		i;
	int 		n;
    double 		dRtnValue;

	try{
    	sCheckStr = "-+0123456789.";
    	dRtnValue = dValue;

    	sTargetTrim = Trim(sTarget);    //�O��̃X�y�[�X���Ȃ�
    	iLength = sTargetTrim.Length();

    	if ( sTargetTrim == "" ) {
    		return(dRtnValue);
    	}

    	//�����ȊO�̕������܂܂�Ă��邩�A1�������`�F�b�N���Ă���
    	for ( i = 1; i <= iLength; i++ ) {
    		//1�������`�F�b�N
   	    	sBuf = sTargetTrim.SubString(i,1);

			n = sCheckStr.AnsiPos(sBuf);

   	     	if ( n <= 0 ) {
   	    		//�����ȊO�̕������܂܂�Ă���̂Ńf�t�H���g�l��Ԃ�
        		return(dRtnValue);
       		}
    	}

    	//�s���I�h�i�����_�j��2�ȏ�܂܂�Ă�����f�t�H���g�l��Ԃ�
    	n = sTargetTrim.AnsiPos(".");
    	if ( n > 0 ) {
			sBuf = sTargetTrim.SubString(n+1,iLength-n);
        	n = sBuf.AnsiPos(".");
        	if ( n > 0 ) {
        		return(dRtnValue);
        	}
    	}

    	//�}�C�i�X��2�ȏ�܂܂�Ă�����f�t�H���g�l��Ԃ�
        //�}�C�i�X����ԍ��ɂȂ��ꍇ���f�t�H���g�l��Ԃ�
        //2003.06.16 E.Takase Add
        if ( sTargetTrim == "-" ) {
         	return(dRtnValue);
        }
    	n = sTargetTrim.AnsiPos("-");
    	if ( n > 0 ) {
            if ( n != 1 ) {
            	return(dRtnValue);
            } else {
				sBuf = sTargetTrim.SubString(n+1,iLength-n);
        		n = sBuf.AnsiPos("-");
        		if ( n > 0 ) {
        			return(dRtnValue);
        		}
        	}
    	}

    	//�v���X��2�ȏ�܂܂�Ă�����f�t�H���g�l��Ԃ�
        //�v���X����ԍ��ɂȂ��ꍇ���f�t�H���g�l��Ԃ�
        //2003.06.16 E.Takase Add
        if ( sTargetTrim == "+" ) {
         	return(dRtnValue);
        }
    	n = sTargetTrim.AnsiPos("+");
    	if ( n > 0 ) {
            if ( n != 1 ) {
            	return(dRtnValue);
            } else {
				sBuf = sTargetTrim.SubString(n+1,iLength-n);
        		n = sBuf.AnsiPos("+");
        		if ( n > 0 ) {
        			return(dRtnValue);
        		}
        	}
    	}

    	dRtnValue = sTarget.ToDouble();   //double�^�ɕϊ�
    	return(dRtnValue);

	}
	catch(EConvertError& e){
		return(dRtnValue);
	}
	catch(...){
		return(dRtnValue);
	}


}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐� �F������𐔒l�ɕϊ�����B
//
//  �@�\����
//    ������𐔒l�ɕϊ�����B�ϊ��G���[�̏ꍇ�̓f�t�H���g�l�i�����^�j��Ԃ��܂��B
//
//  �p�����^����
//    AnsiString sTarget	�F�ϊ����镶����
//    AnsiString sFormat    �F�ϊ�����t�H�[�}�b�g
//  �@AnsiString dValue     �F�f�t�H���g�l
//    AnsiString *sRtn      �F�ϊ����ꂽ������
//  �߂�l
//    true                  �F�ϊ�����
//  �@false                 �F�ϊ����s
//
//  ���l
//****************************************************************************
//2003.05.08 E.Takase Add
//---------------------------------------------------------------------------
//������𐔒l�ɕϊ�����B�ϊ��G���[�̏ꍇ�̓f�t�H���g�l�i�����^�j��Ԃ�
//****************************************************************************
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::ConvDoubleDefS(AnsiString sTarget, AnsiString sFormat, AnsiString dValue, AnsiString *sRtn)
{
	AnsiString 	sBuf;
	AnsiString 	sTargetTrim;
	AnsiString 	sCheckStr;
	int 		iLength;
	int 		i;
	int 		n;
    AnsiString 	sRtnValue;
	double 		dRtnValue;

	try{
	
		*sRtn =dValue;

    	sCheckStr = "-+0123456789.";
    	sRtnValue = dValue;
        dRtnValue = 0;

    	sTargetTrim = Trim(sTarget);    //�O��̃X�y�[�X���Ȃ�
    	iLength = sTargetTrim.Length();

    	if ( sTargetTrim == "" ) {
    		return(false);
    	}

    	//�����ȊO�̕������܂܂�Ă��邩�A1�������`�F�b�N���Ă���
    	for ( i = 1; i <= iLength; i++ ) {
    		//1�������`�F�b�N
   	    	sBuf = sTargetTrim.SubString(i,1);

			n = sCheckStr.AnsiPos(sBuf);

   	     	if ( n <= 0 ) {
   	    		//�����ȊO�̕������܂܂�Ă���̂Ńf�t�H���g�l��Ԃ�
        		return(false);
       		}
    	}

    	//�s���I�h�i�����_�j��2�ȏ�܂܂�Ă�����f�t�H���g�l��Ԃ�
    	n = sTargetTrim.AnsiPos(".");
    	if ( n > 0 ) {
			sBuf = sTargetTrim.SubString(n+1,iLength-n);
        	n = sBuf.AnsiPos(".");
        	if ( n > 0 ) {
        		return(false);
        	}
    	}

    	//�}�C�i�X��2�ȏ�܂܂�Ă�����f�t�H���g�l��Ԃ�
        //�}�C�i�X����ԍ��ɂȂ��ꍇ���f�t�H���g�l��Ԃ�
        //2003.06.16 E.Takase Add
        if ( sTargetTrim == "-" ) {
        	*sRtn ="0";
        	return(true);
        }
    	n = sTargetTrim.AnsiPos("-");
    	if ( n > 0 ) {
            if ( n != 1 ) {
            	return(false);
            } else {
				sBuf = sTargetTrim.SubString(n+1,iLength-n);
        		n = sBuf.AnsiPos("-");
        		if ( n > 0 ) {
        			return(false);
        		}
        	}
    	}

    	//�v���X��2�ȏ�܂܂�Ă�����f�t�H���g�l��Ԃ�
        //�v���X����ԍ��ɂȂ��ꍇ���f�t�H���g�l��Ԃ�
        //2003.06.16 E.Takase Add
        if ( sTargetTrim == "+" ) {
        	*sRtn ="0";
        	return(true);
        }
    	n = sTargetTrim.AnsiPos("+");
    	if ( n > 0 ) {
            if ( n != 1 ) {
            	return(false);
            } else {
				sBuf = sTargetTrim.SubString(n+1,iLength-n);
        		n = sBuf.AnsiPos("+");
        		if ( n > 0 ) {
        			return(false);
        		}
        	}
    	}

    	dRtnValue = sTarget.ToDouble();   //double�^�ɕϊ�
        if ( Trim(sFormat) != "" ) {
        	sRtnValue = FormatFloat(sFormat,dRtnValue);
        } else {
        	sRtnValue = FloatToStr(dRtnValue);
        }
        *sRtn =sRtnValue;
    	return(true);

	}
	catch(EConvertError& e){
		return(false);
	}
	catch(...){
		return(false);
	}


}


//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐� �FNull�Ȃ�u�����N��Ԃ��B
//
//  �@�\����
//    Null�Ȃ�u�����N��Ԃ��B
//
//  �p�����^����
//    Variant &vBuf	        �F???
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//      ���ݖ��g�p�B
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::Null_S(Variant &vBuf)
{
	AnsiString sBuf;

	if ( vBuf.IsNull() ) {
		sBuf = " ";
	} else {
		sBuf = VarToStr(vBuf);
	}
    if ( Trim(sBuf) == "" ) {
        sBuf = " ";
    }
	return ( sBuf );

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnSetEditText �C�x���g    �F���[�U�[���Z���̒l�̕ҏW�����������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �o�ׁi����j�̌������ɓ��͂��ꂽ�l��������B�i�J���[�ɂ���đ���p�ɂ����f����j
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol          �F�ΏۃZ���̃J�����ʒu
//  �@int ARow          �F�ΏۃZ����ROW�ʒu
//  �@AnsiString &Value �F�Z���̕�����
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tSOKU_SYUKASetEditText(TObject *Sender,
      int ACol, int ARow, const AnsiString Value)
{
	int i1;
	AnsiString sBuf;
	sBuf = "";
	if(pSOKU_KSD01_DATA)
	{
    	for(i1=1;i1<=Value.Length();i1++)
        {
            if(strcspn(Value.SubString(i1,1).c_str(),"0123456789")==0)
            {
		   		sBuf += Value.SubString(i1,1);
		  	}
        }
		if(sBuf.Length() == 8)
		{
			strcpy(pSOKU_KSD01_DATA[ACol].SKTYMD_PRT,sBuf.c_str());
   			if(SGr_vSOKU_SYUKA->Color != 0x00DDDDDD)		//�\���p�J���[
			{
				strcpy(pSOKU_KSD01_DATA[ACol].SKTYMD,sBuf.c_str());
			}
            pSOKU_KSD01_DATA[ACol].UPD_FLG = true;
		}
	}
	
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnSetEditText �C�x���g    �F���[�U�[���Z���̒l�̕ҏW�����������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �o�ׁi�����j�̌������ɓ��͂��ꂽ�l��������B�i�J���[�ɂ���đ���p�ɂ����f����j
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol          �F�ΏۃZ���̃J�����ʒu
//  �@int ARow          �F�ΏۃZ����ROW�ʒu
//  �@AnsiString &Value �F�Z���̕�����
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tRIRE_SYUKASetEditText(TObject *Sender,
      int ACol, int ARow, const AnsiString Value)
{
	int i1;
	AnsiString sBuf;
	sBuf = "";
	if(pRIRE_KSD01_DATA)
	{
    	for(i1=1;i1<=Value.Length();i1++)
        {
            if(strcspn(Value.SubString(i1,1).c_str(),"0123456789")==0)
            {
		   		sBuf += Value.SubString(i1,1);
		  	}
        }
		if(sBuf.Length() == 8)
		{
			strcpy(pRIRE_KSD01_DATA[ACol].SKTYMD_PRT,Value.c_str());
   			if(SGr_vRIRE_SYUKA->Color != 0x00DDDDDD)		//�\���p�J���[
			{
				strcpy(pRIRE_KSD01_DATA[ACol].SKTYMD,sBuf.c_str());
			}
		    if( hRIRE_KSD01_DATA && Form1->iRIRE_CNT != 0  )
		    {
				pRIRE_KSD01_DATA[ACol].UPD_FLG = true;
			}
		}
	}
	
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnSetEditText �C�x���g    �F���[�U�[���Z���̒l�̕ҏW�����������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �f�ށi����j�̌������ɓ��͂��ꂽ�l��������B�i�J���[�ɂ���đ���p�ɂ����f����j
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol          �F�ΏۃZ���̃J�����ʒu
//  �@int ARow          �F�ΏۃZ����ROW�ʒu
//  �@AnsiString &Value �F�Z���̕�����
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tSOKU_SOZAISetEditText(TObject *Sender,
      int ACol, int ARow, const AnsiString Value)
{
	int i1;
	AnsiString sBuf;
	sBuf = "";
	if(pSOKU_KSD01_DATA)
	{
    	for(i1=1;i1<=Value.Length();i1++)         
        {
            if(strcspn(Value.SubString(i1,1).c_str(),"0123456789")==0)
            {
		   		sBuf += Value.SubString(i1,1);
		  	}
        }
		if(sBuf.Length() == 8)
		{
			strcpy(pSOKU_KSD01_DATA[ACol].SKTYMD_SZ_PRT,Value.c_str());
   			if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD)		//�\���p�J���[
			{
				strcpy(pSOKU_KSD01_DATA[ACol].SKTYMD_SZ,sBuf.c_str());
			}
            pSOKU_KSD01_DATA[ACol].UPD_FLG = true;
		}
	}
	
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnSetEditText �C�x���g    �F���[�U�[���Z���̒l�̕ҏW�����������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �f�ށi�����j�̌������ɓ��͂��ꂽ�l��������B�i�J���[�ɂ���đ���p�ɂ����f����j
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol          �F�ΏۃZ���̃J�����ʒu
//  �@int ARow          �F�ΏۃZ����ROW�ʒu
//  �@AnsiString &Value �F�Z���̕�����
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tRIRE_SOZAISetEditText(TObject *Sender,
      int ACol, int ARow, const AnsiString Value)
{
	int i1;
	AnsiString sBuf;
	sBuf = "";
	if(pSOKU_KSD01_DATA)
	{
    	for(i1=1;i1<=Value.Length();i1++)
        {
            if(strcspn(Value.SubString(i1,1).c_str(),"0123456789")==0)
            {
		   		sBuf += Value.SubString(i1,1);
		  	}
        }
		if(sBuf.Length() == 8)
		{
			strcpy(pRIRE_KSD01_DATA[ACol].SKTYMD_SZ_PRT,Value.c_str());
   			if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD)		//�\���p�J���[
			{
				strcpy(pRIRE_KSD01_DATA[ACol].SKTYMD_SZ,sBuf.c_str());
			}
		    if( hRIRE_KSD01_DATA && Form1->iRIRE_CNT != 0  )
		    {
				pRIRE_KSD01_DATA[ACol].UPD_FLG = true;
			}
    	}
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SGr_vRIRE_SYUKADblClick(TObject *Sender)
{
    SBr1->Panels->Items[0]->Text = "DoubleClick()";
    SBr1->Update();
    Beep();
}

//---------------------------------------------------------------------------
// �ҏW�R���g���[���E�B���h�E��\�����܂���
// �y���Ӂz�F���̊֐����R�[������ƈȍ~�A�ҏW�R���g���[���E�B���h�E��
//           �\������܂���B
//           ����������ꍇ�́A���̏����ňȉ��̃R�[�h�ŕҏW�R���g���[��
//           �E�B���h�E���g�����Ԃɖ߂��ĉ������B
//           TStringGrid->Options << goEditing;
void __fastcall TForm1::Delete_InplaceEdit(TObject *Sender)
{
	if( AnsiString(Sender->ClassName()) == "TStringGrid" ){

		TStringGrid		*Sgr = (TStringGrid *)Sender;

		// �L�����b�g�̈ʒu���擾
		// �ҏW�Z���iTInplaceEdit�j������
		//int i;
		TInplaceEdit *edit = NULL;
		int ComCount = Sgr->ComponentCount;  // �S�R���|�[�l���g��

		for( int i=0; i<ComCount; i++ ){
			TComponent *component = Sgr->Components[i];
			AnsiString name = component->ClassName();
			if( name == "TInplaceEdit" ){
				edit = ( TInplaceEdit* )component;
                //edit->Hide();
                //edit->Invalidate();
                Sgr->Options >> goEditing;
				break;
			}
		}
	}

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�    �F���[�U�[�̓��͂ɑ΂��ėL���ȓ��͂�����Ă��邩���`�F�b�N���܂��B
//
//  �@�\����
//    ���[�U�[�̓��͂ɑ΂��ėL���ȓ��͂�����Ă��邩���`�F�b�N���܂��B
//
//  �p�����^����
//    AnsiString sBuf	�F�Z���̓���
//    int   iVALUE_TYPE �F����l�\���i0�F�����A�����@1�F�p�x�@2�F�ǔہ@3�F������j
//  �@TObject *Sender   �F�Ăяo������VCL�I�u�W�F�N�g
//    char &Key         �F���[�U�[�����������L�[
//  �@int iLenMAX       �F���͍ő啶����
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//2003.05.15 E.Takase Add ��
//
//---------------------------------------------------------------------------
void __fastcall TForm1::ChkInputData(AnsiString sBuf, int iVALUE_TYPE, TObject *Sender, char &Key, int iLenMAX)
{

	//int iVALUE_DECI;
	AnsiString sDeci1;
	AnsiString sBuf2;
	AnsiString sKey;
	AnsiString sBufChk;
    bool bRtn;

	TStringGrid	*Sgr = (TStringGrid *)Sender;
	//int 	i;
	TInplaceEdit *edit = NULL;
	int 	ComCount = Sgr->ComponentCount;  // �S�R���|�[�l���g��
	bool	fOK;


    //���l���͉��s����
    if( Key == VK_RETURN && iVALUE_TYPE != 9 )  {
    	return;
    }

    if( Key == VK_BACK || Key == VK_TAB )  {
    	return;
    }

    sKey = Key;
    sBufChk = sBuf + sKey;

    //�L���ȕ��������͂���Ă����當���̒����`�F�b�N
	// �L�����b�g�̈ʒu���擾
	// �ҏW�Z���iTInplaceEdit�j������
	fOK = false;
	for( int i=0; i<ComCount; i++ ){
		TComponent *component = Sgr->Components[i];
		AnsiString name = component->ClassName();
		if( name == "TInplaceEdit" ){
			edit = ( TInplaceEdit* )component;
	        //if( edit->SelStart == 0 && edit->SelLength == sBuf.Length()){
            if( edit->SelStart > 0 ){
                sBufChk = sBuf.SubString(1,edit->SelStart);
            }
            else {
             	sBufChk = "";
            }
            sBufChk = sBufChk + sKey;
            if( edit->SelStart + edit->SelLength < sBuf.Length() ){
              	sBufChk = sBufChk + sBuf.SubString(edit->SelStart + edit->SelLength + 1,
                                  sBuf.Length() - (edit->SelStart + edit->SelLength));
	        }
		}
	}

    //�L���ȕ����񂪃Z�b�g���ꂽ���`�F�b�N
	switch(iVALUE_TYPE)
	{
        case 0:	//�����E����
        case 1: //�p�x
			if ( Key == VK_SPACE ) {
	        	Key = '\0';
				return;
			}

			//�}�C�i�X�݂̂̏ꍇ �`�F�b�N���X�L�b�v
			if ( sBufChk == "-" ) {
				return;
			}

            sDeci1 = "";
    		//���l�`�F�b�N
    		bRtn = ConvDoubleDefS(sBufChk,sDeci1,sBufChk,&sBuf2);
			//���l�łȂ������ꍇ�A�Ō�ɓ��͂��ꂽ�������J�b�g
			if ( bRtn == false ) {
				Key = '\0';
				return;
			}
			break;

        case 2: //�ǁE��
			if ( Key == VK_SPACE ) {
	        	Key = '\0';
				return;
			}
            //0�E1�̂ݗL��
        	if ( sKey != "0" &&  sKey != "1" ) {
	        	Key = '\0';
				return;
        	}

			break;

        case 3: //����
			if ( Key == VK_SPACE ) {
	        	Key = '\0';
				return;
			}
/*
            sDeci1 = "";
    		//���l�`�F�b�N
    		bRtn = ConvDoubleDefS(sBufChk,sDeci1,sBufChk,&sBuf2);
			//���l�łȂ������ꍇ�A�Ō�ɓ��͂��ꂽ�������J�b�g
			if ( bRtn == false ) {
				Key = '\0';
				return;
			}
*/
            //���l�`�F�b�N�ł� "-"�A"+"�A"."��OK�����A���t�ł͗L���ł͂Ȃ��̂ŃJ�b�g
        	//if ( sKey == "-" || sKey == "+" || sKey == "." ) {
        	if ( sKey == "'" ) {
	        	Key = '\0';
				return;
        	}

			break;
        case 4: //���t
			if ( Key == VK_SPACE ) {
	        	Key = '\0';
				return;
			}

            sDeci1 = "";
    		//���l�`�F�b�N
    		bRtn = ConvDoubleDefS(sBufChk,sDeci1,sBufChk,&sBuf2);
			//���l�łȂ������ꍇ�A�Ō�ɓ��͂��ꂽ�������J�b�g
			if ( bRtn == false ) {
				Key = '\0';
				return;
			}

            //���l�`�F�b�N�ł� "-"�A"+"�A"."��OK�����A���t�ł͗L���ł͂Ȃ��̂ŃJ�b�g
        	if ( sKey == "-" || sKey == "+" || sKey == "." ) {
	        	Key = '\0';
				return;
        	}

			break;
		default:

			break;

	}

    //�L���ȕ��������͂���Ă����當���̒����`�F�b�N
	// �L�����b�g�̈ʒu���擾
	// �ҏW�Z���iTInplaceEdit�j������
	fOK = false;
	for( int i=0; i<ComCount; i++ ){
			TComponent *component = Sgr->Components[i];
			AnsiString name = component->ClassName();
			if( name == "TInplaceEdit" ){
				edit = ( TInplaceEdit* )component;
	            //if( edit->SelStart == 0 && edit->SelLength == sBuf.Length()){
	            if( edit->SelLength > 0){
	              	fOK = true;
	            }
			}
	}
	//�����`�F�b�N
	if ( fOK == false && sBufChk.Length() > iLenMAX ) {
		Key = '\0';
	}


}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�    �F������sMaster�Ɋ܂܂��sA����������sB�ɒu��������B
//
//  �@�\����
//    ������sMaster�Ɋ܂܂��sA����������sB�ɒu��������B
//
//  �p�����^����
//    AnsiString sMaster�F�Ώە�����
//    AnsiString sA     �F�ϊ�������������
//  �@AnsiString sB     �F�ϊ���̕�����
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//�@��������쐬 ��
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::ReplaceStrAtoB(AnsiString sMaster, AnsiString sA, AnsiString sB)
{
	int iLength;
    AnsiString sBuf;
    int iPos;

    sBuf = sMaster;
    iLength = sMaster.Length();

    if ( iLength <= 0 ) {
    	return ( sBuf );
    }

    while ( 1 ) {

    	iPos = sBuf.AnsiPos(sA);
        if ( iPos <= 0 ) {
        	break;
        }

        sBuf.Delete(iPos, sA.Length());
        sBuf.Insert(sB, iPos);


    }



    return ( sBuf );
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�    �F��������w�肳�ꂽ�����ŃJ�b�g�B
//
//  �@�\����
//    ��������w�肳�ꂽ�����ŃJ�b�g�B
//
//  �p�����^����
//    AnsiString sMaster�F�Ώە�����
//    int iLenMAX       �F�ő啶����
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//�@�c������쐬 ��
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::CutStrLenMAX(AnsiString sMaster,int iLenMAX)
{
    AnsiString sBuf;


	//sMaster�̍ő啶������iLenMAX
	if ( sMaster.Length() > iLenMAX ) {
		if ( sMaster.ByteType(iLenMAX) == mbLeadByte ) {
			sBuf = sMaster.SubString(1,iLenMAX-1);
		} else {
			sBuf = sMaster.SubString(1,iLenMAX);
		}
	} else {
    	sBuf = sMaster;
	}


    return ( sBuf );
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�    �F������̍Ō��1�������J�b�g�B
//
//  �@�\����
//    ������̍Ōオ2�o�C�g�������ƃJ�b�g���܂��B
//
//  �p�����^����
//    AnsiString sMaster�F�Ώە�����
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//�@�c������쐬 ��
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::CutStrEndChar(AnsiString sMaster)
{
	int iLength;
    AnsiString sBuf;

    iLength = sMaster.Length();

    if ( sMaster.ByteType(iLength-1) == mbLeadByte ) {
    	sBuf = sMaster.SubString(1,iLength-2);
    } else {
    	sBuf = sMaster.SubString(1,iLength-1);
    }

    return ( sBuf );

}
//---------------------------------------------------------------------------


//�w�肵���z���iPos�Ԗڂ̒l�̎擾�͉\���H
bool __fastcall TForm1::ChkSize(HANDLE hChk, int iPos, long lSize)
{
    //int iChkPos;


/*
    long lFlags = GlobalFlags( hChk );
    //�w�肳�ꂽ�O���[�o���n���h���͗L�����H
    if ( lFlags == GMEM_INVALID_HANDLE ) {
    	return ( false );
    }
*/
	WORD wSize  = (WORD)GlobalSize( hChk );
    //�z��̃T�C�Y�`�F�b�N
    if ( wSize <= 0 ) {
    	return ( false );
    }
/* �Ƃ肠���� �������m�ۂ��Ă���OK�ɂ��܂��B 2003.05.17
    //iPos�͔z��̗L���Ȉʒu���H
    iChkPos = wSize / lSize;
    if ( iChkPos <= iPos ) {
    	return ( false );
    }

*/
    return ( true );

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�    �F�O���t�̏��������s���܂��B
//
//  �@�\����
//    �O���t�̏��������s���܂��B
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//�@ �Ö傳��쐬 ��
//
//---------------------------------------------------------------------------
void TForm1::Graph_Format()
{
    //TODO ���̉��ɃR�[�h��ǉ����Ă�������
    int CharWidth;                                //Y�����W�l��`�悷�邽�߂̗]��
    int CharHeight;                               //X�����W�l��`�悷�邽�߂̗]��
    int FontHeight;
	int ImageW,ImageH;                            //�C���[�W�̍����A��
	int x,y,yst,i1,i;
	double dMaxMinHeight;
    TImage *glh;

	for ( i = 0; i < 2; i++ ){
	    if (i == 0) {
		    glh = ImgGlaphSYUKA;
	    } else {
		    glh = ImgGlaphSOZAI;
		}

		glh->Canvas->Pen->Color = clBlack;
		glh->Canvas->Pen->Style = (TPenStyle)bsSolid;
		glh->Canvas->Pen->Width = 1;       //���̑���
		glh->Canvas->Font->Size = 7;       //�����̃T�C�Y

		glh->Canvas->Brush->Color = clWhite;
		glh->Canvas->Rectangle(0,0,glh->Width,glh->Height);

		//�O���t�`��̍ۂɎg�p����萔�̐ݒ�
		CharWidth 	= glh->Canvas->Font->Height * 3;   //���[��Y���̊Ԃ̗]��
		CharHeight 	= glh->Canvas->Font->Height * 2;  //���[��X���̊Ԃ̗]��
		FontHeight 	= glh->Canvas->Font->Height;      //�����̍���
		ImageH = glh->Height - 2* CharHeight;
		ImageW = glh->Width - CharWidth;

		//�O���t�̕`��
		glh->Canvas->Brush->Color =clWhite;
		glh->Canvas->Pen->Color =clGray;

		//������C��
		glh->Canvas->Pen->Color = clGray;
		y = 1 * (glh->Height/9);
		glh->Canvas->Rectangle(1,y-1,glh->Width-1,y);

		//��������̊ԃ��C��
		yst = 1 * (glh->Height/9);
		x=( 7 * (glh->Height/9) );
		for(i1=1;i1<8;i1++)
		{
			if( i1 == 2 || i1 == 4 || i1 == 6 ) {
				glh->Canvas->Pen->Color = clGray;
			} else {
				glh->Canvas->Pen->Color = clSilver;
			}
			y = yst + ( i1 * (x/8) );
			glh->Canvas->Rectangle(1,y,glh->Width-1,y+1);
		}

		//�������C��
		glh->Canvas->Pen->Color = clGray;
		y = 8 * (glh->Height/9);
		glh->Canvas->Rectangle(1,y-1,glh->Width-1,y);

		//x�����C��
		glh->Canvas->Pen->Color = clGray;
		dMaxMinHeight = (glh->Height/9)*8 - (glh->Height/9);
		for(i1 = 0;i1 < 10;i1++)
		{
			x =	((ImageW) / 12) * (9-i1)+glh->Canvas->Font->Size+20;
			glh->Canvas->Rectangle(x+10,1,x+11,glh->Height-1);
		}
	}


}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�    �F���͕����̃`�F�b�N���s�Ȃ��A�L���ȕ������Ԃ��܂��B
//
//  �@�\����
//    ���͕����̃`�F�b�N���s�Ȃ��A�L���ȕ�����i�h�f�h�A�h�C�h�����j��Ԃ��܂��B
//
//  �p�����^����
//    AnsiString sTarget    �F���͕���
//    int iLenMAX           �F������ő咷
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//�@  �Ȃ��B ��
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::GetValidityData(AnsiString sTarget, int iLenMAX)
{
	AnsiString sBuf;

    sBuf = sTarget;

    // �V���O���R�[�e�[�V�����͂c�a�o�^���ɃG���[����������
    // �̂őS�p�̃V���O���R�[�e�[�V�����ɕϊ����܂�
    sBuf = ReplaceStrAtoB( sBuf, "'", "�f");

    // ���p�J���}�̓��|�[�g�o�͎��ɃG���[����������
    // �̂őS�p�̃J���}�ɕϊ����܂�
    sBuf = ReplaceStrAtoB( sBuf, ",", "�C");

	//�����`�F�b�N
    sBuf = CutStrLenMAX( sBuf, iLenMAX);

    return ( sBuf );


}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�    �F���l���̓��͕������`�F�b�N���܂��B
//
//  �@�\����
//    ���l���̕����񂪁A�L���ȕ����񂩁i�h�f�h�A�h�C�h�����j��Ԃ��܂��B
//  �@�܂��A���͂��ꂽ���b�g��UPDATE�t���O��true�ɂ��܂��B
//
//  �p�����^����
//    AnsiString sTarget    �F���͕���
//    int iLenMAX           �F������ő咷
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//�@  �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Mem_MEMOKeyPress(TObject *Sender, char &Key)
{
    AnsiString sBuf;
    AnsiString sNum;
    int iNum;
    TMemo* memoBuf = dynamic_cast<TMemo*>(Sender);
    sBuf = memoBuf->Text;

    int iLenMAX = 128;
	ChkInputData( sBuf, 9, Sender, Key, iLenMAX);
    sNum = memoBuf->Name;
    iNum = sNum.SubString(15,sNum.Length()-14).ToIntDef(0);
    if(sNum.SubString(5,5) == "vRIRE" )
    {
        pRIRE_KSD01_DATA[iNum].UPD_FLG = true;
    }
    else
    {
        pSOKU_KSD01_DATA[iNum].UPD_FLG = true;
    }
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�    �F���l���̓��͕������`�F�b�N���܂��B
//
//  �@�\����
//    ���l���̕����񂪁A�L���ȕ����񂩁i�h�f�h�A�h�C�h�����j��Ԃ��܂��B
//  �@�܂��A���͂��ꂽ���b�g��UPDATE�t���O��true�ɂ��܂��B
//
//  �p�����^����
//    AnsiString sTarget    �F���͕���
//    int iLenMAX           �F������ő咷
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//�@  �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Edt_LOTNOChange(TObject *Sender)
{
    int			i;
    int			iSelStart;
    AnsiString	sBuf;
    TEdit* edt = dynamic_cast<TEdit*>(Sender);


    sBuf = edt->Text;
    iSelStart = edt->SelStart;

    // �V���O���R�[�e�[�V�����͂c�a�o�^���ɃG���[����������
    // �̂őS�p�̃V���O���R�[�e�[�V�����ɕϊ����܂�
    i = sBuf.AnsiPos("'");
    if( i > 0 ){
        sBuf.Delete( i, 1);
        if( edt->MaxLength == 0 || edt->MaxLength >= sBuf.Length() + 2 ){
        	sBuf.Insert("�f",i);
    	}
        //edt->Text = sBuf;
        //edt->SelStart = i + 1;
       	iSelStart = i + 1;
    }
    edt->Text = sBuf.UpperCase();
    edt->SelStart = iSelStart;
}


//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�    �F���t���͂��`�F�b�N���܂��B
//
//  �@�\����
//    ���t���͂��`�F�b�N���܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    char &Key         �F���͂��ꂽ�����R�[�h
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//�@  �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tKeyPress(TObject *Sender, char &Key)
{
	int iRow,iCol;
    AnsiString sBuf;
	int iVALUE_TYPE;

	TStringGrid		*Sgr = (TStringGrid *)Sender;

	iCol = Sgr->Col;
	iRow = Sgr->Row;
    sBuf = Sgr->Cells[iCol][iRow];
    iVALUE_TYPE = 4;
	ChkInputData( sBuf, iVALUE_TYPE, Sender, Key, 8);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnCloseQuery �C�x���g �FClose ���\�b�h���Ăяo���ꂽ�Ƃ��C�܂��̓��[�U�[���t�H�[����
//                          �@�V�X�e�����j���[�Łm����n��I�������Ƃ��ɔ������܂��B
//
//  �@�\����
//    ���[�U�[���߂�{�^�����������C���t�H�[���̕���i�uX�v�{�^���j���������ɔ�������
//    ���b�Z�[�W���o�͂��܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    bool &CanClose    �F�t�H�[���̃N���[�Y���\���ǂ��������߂�_���^�ϐ�
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//�@  �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	TMsgDlgButtons mRet;
	AnsiString sBuf;
	TShiftState State;
	TMsgDlgButtons MsgButton;

    CanClose = true;

    if( UPDATE_CHECK())
    {
        if( !ALL_INSPECT())
        {
            sBuf  = "������̍��ڂ��L��܂��B�ۑ����ă��C�����j���[�ɖ߂�܂����H";
            sBuf += "\n[�́@��] �����荀�ڂ���̂܂܁A�ۑ����Ė߂�܂��B";
            sBuf += "\n[������] ���e��j�����Ė߂�܂��B";
            sBuf += "\n[�L�����Z��] �߂�܂���B";
            switch( MessageDlg( sBuf, mtWarning, mbYesNoCancel, 0) )
            {
            // �uYes�v      �ۑ�
            case mrYes:
                bQUIT_FLG = true;
            	BtnF11Click(Sender);
                CanClose = true;
                break;
            // �uNo�v       �ύX��j��
            case mrNo:
                CanClose = true;
            	break;
    	    // �uCancel�v   �L�����Z��
            case mrCancel:
                CanClose = false;
            	return;
             }
        }
        else
	    {
        	sBuf  = "�f�[�^���ύX����Ă��܂��B�ύX���e��ۑ����ă��C�����j���[�ɖ߂�܂����H";
            sBuf += "\n[�́@��] �ύX���e��ۑ����Ė߂�܂��B";
            sBuf += "\n[������] �ύX���e��j�����Ė߂�܂��B";
            sBuf += "\n[�L�����Z��] �߂�܂���B";
            switch( MessageDlg( sBuf, mtConfirmation, mbYesNoCancel, 0) )
            {
            // �uYes�v      �ۑ�                  
            case mrYes:
                bQUIT_FLG = true;
        	    BtnF11Click(Sender);
                CanClose = true;
                break;
            // �uNo�v       �ύX��j��
            case mrNo:
                CanClose = true;
            	break;
        	// �uCancel�v   �L�����Z��
            case mrCancel:
                CanClose = false;
        	    return;
             }
        }
    }                               
    else
    {
        // �m�F
        sBuf  = "���C�����j���[�ɖ߂�܂��B��낵���ł����H";
        sBuf += "\n[�́@��] ���C�����j���[�ɖ߂�܂��B";
        sBuf += "\n[�L�����Z��] �߂�܂���B";
        MsgButton << mbYes << mbCancel;
        switch( MessageDlg( sBuf, mtConfirmation , MsgButton, 0) ){
        // �uYes�v      �ۑ�
        case mrYes:
            break;
        // �uCancel�v   �L�����Z��
        case mrCancel:
            CanClose = false;
            return;
        }
    }
	CommClose(1);
	//2003.05.08 E.Takase Add��
	//2003.05.08 E.Takase Add �R�����g��
	//delete sRIREKI_LOT;
    //delete sHT_LOT;
    //delete sShiji_Data;
    //2003.05.08 E.Takase Add �R�����g��
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClose �C�x���g��    �F�t�H�[��������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �t�H�[�������ہA�����I�ɑSQuery��Close���ADataBase��Close���܂��B
//    ���b�Z�[�W���o�͂��܂��B
//
//  �p�����^����
//    TObject *Sender	        �F�Ăяo������VCL�I�u�W�F�N�g
//     TCloseAction &Action     �F�t�H�[�������ۂɕ���ǂ��������߂܂��B
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//�@  �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
    //2003.05.08 E.Takase Add��
	Query1->Close();
	Query2->Close();
	Query3->Close();
	Query4->Close();
	Query5->Close();
	Query6->Close();
	Query7->Close();
	Query8->Close();
	Query10->Close();
	QueryTANTO->Close();
	QueryTANTO2->Close();
	Database1->Close();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐��F    	�F���艹�����p�̔�����s���܂��B
//
//  �@�\����
//    �Z���̓��͒l�𔻒肵�܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol          �F�ΏۃZ���̃J�����ʒu
//    int ARow          �F�ΏۃZ���̂q�n�v�ʒu
//  �߂�l
//    ���茋�ʁi�O�F�n�j�A�P:�m�f�A�Q:�ȊO�i�󗓂Ȃǁj�j
//
//  ���l
//    �S�̃O���b�h�ɏ����͕�����Ă��܂����A�Q�ƃ������̈ʒu�Ȃǂ��Ⴄ�����œ��e�͓����ł��B
//
//---------------------------------------------------------------------------
int __fastcall TForm1::CELL_HANTEI(TObject *Sender,int ACol,int ARow)
{
	if(iDEBUG == 1) return(2);
	AnsiString asString,sBuf,sBuf2;
	int i1;
	int iGridTag;
	AnsiString	sDeci1,sDeci2;
	double dMAX,dMIN;
	AnsiString sTemp;
	int iKIKA_KIND;			//1�F�㉺������A2�F�ȉ��A3�F�ȏ�
	bool bRtn;	 			//2003.05.08 E.Takase Add
	double dBuf;	 		//2003.05.08 E.Takase Add
	AnsiString sComp1,sComp2,sTempComp;	//�\���l�ƈ���l���r����o�b�t�@
    int iHANTEI;

    //�����������邩�𔻒f���܂�
	if(Sender == SGr_vSOKU_SYUKA)
	{
		iGridTag = 1;
		asString = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
		SGr_vSOKU_SYUKA->Canvas->Font->Size = 12;
		if(!hCELLINFO_SOKU_SYUKA) return(2);
	}
	if(Sender == SGr_vRIRE_SYUKA)
	{
		iGridTag = 2;
		asString = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
		SGr_vRIRE_SYUKA->Canvas->Font->Size = 12;
		if(!hCELLINFO_RIRE_SYUKA) return(2);
	}
	if(Sender == SGr_vSOKU_SOZAI)
	{
		iGridTag = 3;
		asString = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
		SGr_vSOKU_SOZAI->Canvas->Font->Size = 12;
		if(!hCELLINFO_SOKU_SOZAI) return(2);
	}
	if(Sender == SGr_vRIRE_SOZAI)
	{
		iGridTag = 4;
		asString = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
		SGr_vRIRE_SOZAI->Canvas->Font->Size = 12;
		if(!hCELLINFO_RIRE_SOZAI) return(2);
	}
/////////////////////////////////////////////////////////////////////
//�ȉ��͑��荀�ڂ̕\���ɂ��ẴR�[�h�ł�
	switch( iGridTag )
	{
	case 1:
	//�z�񂪎��Ă��Ȃ��̂ŕ`��𒆎~���܂�
		if(!hCELLINFO_SOKU_SYUKA) return(2);
		break;
	case 2:
	//�z�񂪎��Ă��Ȃ��̂ŕ`��𒆎~���܂�
		if(!hCELLINFO_RIRE_SYUKA) return(2);
		break;
	case 3:
	//�z�񂪎��Ă��Ȃ��̂ŕ`��𒆎~���܂�
		if(!hCELLINFO_SOKU_SOZAI) return(2);
		break;
	case 4:
	//�z�񂪎��Ă��Ȃ��̂ŕ`��𒆎~���܂�
		if(!hCELLINFO_RIRE_SOZAI) return(2);
		break;
	}

	switch( iGridTag )
	{
	//�o�ב�����
	case 1:
		if(!hCELLINFO_SOKU_SYUKA) return(2);
		// 2003/06/02 K.Yamada �ΏۃZ�����������́A�����𒆎~���܂�
		if( SGr_vSOKU_SYUKA->RowCount == 1 ) return(2);

		if(Form1->SGr_tSOKU->Cells[0][0]!="" && hCELLINFO_SOKU_SYUKA != NULL)
		{
			if( hCELLINFO_SOKU_SYUKA )
			{
            //���͂����l�̏ꍇ�A�K�i���Z�o����
				if((AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 1)
				|| (AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 2))
				{
					dMAX = pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].MAX;
					dMIN = pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].MIN;
				}
			}
		}
	//�ȏ�ȉ��̋K�i�̏ꍇ�΍�
		iKIKA_KIND = 1;		//�f�t�H���g�͏㉺���Ŕ���
		if(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].KIKA_TYPE) == 1)
		{
			if(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].KIKA_KIND) == 2)
			{
				iKIKA_KIND = 2;
			}
			else if(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].KIKA_KIND) == 3)
			{
				iKIKA_KIND = 3;
			}
		}

//�t�H�[�}�b�g����
		if(hCELLINFO_SOKU_SYUKA )
		{
            //�����񂪕s�v�Ȃ�̏����ł������͏������̂��̂��s�v�ł��i�s�v������Ō��Ȃ��Ȃ����ׁj
			if(asString == "�s�v"
			|| AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].RESULT) == "�s�v")
			{
				sBuf = "�s�v";
				//�Z�����͂��o�b�t�@�Ɏ�荞��
				strcpy(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].RESULT		,sBuf.c_str());
				strcpy(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].DISP_RESULT,sBuf.c_str());
				pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].JUDGE = 2;
			}
			else
			{
                //�����A�����A�p�x�̏ꍇ�̓t�H�[�}�b�g��������쐬���܂�
				switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:		//�����E����
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_SOKU_SYUKA[(ACol*SGr_vSOKU_SYUKA->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( sDeci1.Length() == 1 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 1:		//�p�x
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_SOKU_SYUKA[(ACol*SGr_vSOKU_SYUKA->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( sDeci1.Length() == 1 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 2:  	//�ǁE��
					break;
				default:	//����
					break;
				}
				switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:
                    //���͂��Ȃ���΃o�b�t�@����ɂ��܂�
					if(AnsiString(SGr_vSOKU_SYUKA->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}
                    //��������̔��莮���g���������͂ł��G���[���o���Ȃ��悤�ɂ��܂��B
					//2003.05.08 E.Takase Add��
					bRtn = ConvDoubleDefS(SGr_vSOKU_SYUKA->Cells[ACol][ARow],sDeci1,SGr_vSOKU_SYUKA->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add��

					//�ǔ۔���
					//2003.05.08 E.Takase Add��
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
                        //�ȉ�����
						case 2:
							if( dBuf <= dMAX  )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
							break;
                        //�ȏ㔻��
						case 3:
							if( dBuf >= dMIN )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
							break;
                        //�͈͔���
						default:
                            // 2003/10/06 A.Tamura �Ȃ����K�i���Ȃ̂ɋK�i�O�Ɣ��肳���̂�Double�^���Đݒ肵�܂��B
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
						}

					} else {
                        iHANTEI = 2;
					}
					//2003.05.08 E.Takase Add��
					break;
				case 1:
					if(AnsiString(SGr_vSOKU_SYUKA->Cells[ACol][ARow]).Length() == 0)
					{
                        iHANTEI = 2;
					}
					//2003.05.08 E.Takase Add��
					bRtn = ConvDoubleDefS(SGr_vSOKU_SYUKA->Cells[ACol][ARow],sDeci1,SGr_vSOKU_SYUKA->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add��

					//�ǔ۔���
					//2003.05.08 E.Takase Add��
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
                        //�ȉ�����
						case 2:
							if( dBuf <= dMAX )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
							break;
                        //�ȏ㔻��
						case 3:
							if( dBuf >= dMIN )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
							break;
                        //�͈͔���
						default:
                            // 2003/10/06 A.Tamura �Ȃ����K�i���Ȃ̂ɋK�i�O�Ɣ��肳���̂�Double�^���Đݒ肵�܂��B
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN)
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
						}
					} else {
						iHANTEI = 2;
					}
					//2003.05.08 E.Takase Add��

					break;
				case 2:
                    //�ǔ۔���
                    iHANTEI = 2;
					sBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
					sBuf = sBuf.Trim();
					if( sBuf == 0 || sBuf == "��")
					{
                        iHANTEI = 0;
					}
					else if( sBuf.Length() != 0)
					{
                        iHANTEI = 1;
					}
					break;
				default:
                    //�����񔻒�
                    iHANTEI = 2;
					sBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
                    if(sBuf.Length() != 0 ) iHANTEI = 0;
				}
			}
		}
		break;
    //�ȍ~Case2�A3�A4�i�o�׌��������A�f�ތ����o�ׁA�f�ތ��������j���������e�͓����ł�
   case 2:
		if(!hCELLINFO_RIRE_SYUKA) return(2);
		// 2003/06/02 K.Yamada �ΏۃZ�����������́A�����𒆎~���܂�
		if( SGr_vRIRE_SYUKA->RowCount == 1 ) return(2);

		if(Form1->SGr_tRIRE->Cells[0][0]!="" && hCELLINFO_RIRE_SYUKA != NULL)
		{
			if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
				sBuf = pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount + ARow].RESULT;
			}
			sBuf = pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount + ARow].DISP_RESULT;
			if( hCELLINFO_RIRE_SYUKA )
			{
//���͂����l�̏ꍇ�A�K�i���Z�o����
				if((AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 1)
				|| (AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 2))
				{
					dMAX = pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].MAX;
					dMIN = pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].MIN;
				}
			}
		}

	//�ȏ�ȉ��̋K�i�̏ꍇ�΍�
		iKIKA_KIND = 1;		//�f�t�H���g�͏㉺���Ŕ���
		if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].KIKA_TYPE) == 1)
		{
			if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].KIKA_KIND) == 2)
			{
				iKIKA_KIND = 2;
			}
			else if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].KIKA_KIND) == 3)
			{
				iKIKA_KIND = 3;
			}
		}
//�t�H�[�}�b�g����
		if(hCELLINFO_RIRE_SYUKA )
		{
			if(asString == "�s�v"
			|| AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].RESULT) == "�s�v")
			{
				sBuf = "�s�v";
				//�Z�����͂��o�b�t�@�Ɏ�荞��
				strcpy(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].RESULT		,sBuf.c_str());
				strcpy(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].DISP_RESULT,sBuf.c_str());
				pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].JUDGE = 2;
			}
			else
			{
				switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:		//�����E����
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_RIRE_SYUKA[(ACol*SGr_vRIRE_SYUKA->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( sDeci1.Length() == 1 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 1:		//�p�x
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_RIRE_SYUKA[(ACol*SGr_vRIRE_SYUKA->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( sDeci1.Length() == 1 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 2:  	//�ǁE��
					break;
				default:	//����
					break;
				}
				switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:
					if(AnsiString(SGr_vRIRE_SYUKA->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}
					//2003.05.08 E.Takase Add��
					bRtn = ConvDoubleDefS(SGr_vRIRE_SYUKA->Cells[ACol][ARow],sDeci1,SGr_vRIRE_SYUKA->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add��
					//�ǔ۔���
					//2003.05.08 E.Takase Add��
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
						case 2:
							if( dBuf <= dMAX )
							{
                                iHANTEI = 0;
							}
							else
							{
                                iHANTEI = 1;
							}
							break;
						case 3:
							if( dBuf >= dMIN )
							{
                                iHANTEI = 0;
							}
							else
							{
                                iHANTEI = 1;
							}
							break;
						default:
                            // 2003/10/06 A.Tamura �Ȃ����K�i���Ȃ̂ɋK�i�O�Ɣ��肳���̂�Double�^���Đݒ肵�܂��B
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN)
							{
                                iHANTEI = 0;
							}
							else
							{
                                iHANTEI = 1;
							}
						}
					} else {
                        iHANTEI = 2;
					}
					//2003.05.08 E.Takase Add��
					break;
				case 1:
					if(AnsiString(SGr_vRIRE_SYUKA->Cells[ACol][ARow]).Length() == 0)
					{
                        iHANTEI = 2;
					}

					//2003.05.08 E.Takase Add��
					bRtn = ConvDoubleDefS(SGr_vRIRE_SYUKA->Cells[ACol][ARow],sDeci1,SGr_vRIRE_SYUKA->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add��
					//�ǔ۔���
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
						case 2:
							if( dBuf <= dMAX )
							{
                                iHANTEI = 0;
							}
							else
							{
                                iHANTEI = 1;
							}
							break;
						case 3:
							if( dBuf >= dMIN )
							{
                                iHANTEI = 0;
							}
							else
							{
                                iHANTEI = 1;
							}
							break;
						default:
                            // 2003/10/06 A.Tamura �Ȃ����K�i���Ȃ̂ɋK�i�O�Ɣ��肳���̂�Double�^���Đݒ肵�܂��B
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

                            // 2003/10/06 A.Tamura �Ȃ�ł���ȃR�[�h�Ȃ́H�@���ɂ��ǂ�
							//if( dBuf <= dMAX && sBuf.ToDouble() >= dMIN)
							if( dBuf <= dMAX && dBuf >= dMIN)
							{
                                iHANTEI = 0;
							}
							else
							{
                                iHANTEI = 1;
							}
						}

					} else {
                        iHANTEI = 2;
					}
					//2003.05.08 E.Takase Add��

					break;
				case 2:
                    iHANTEI = 2;
					sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
					sBuf = sBuf.Trim();
					if( sBuf == 0 || sBuf == "��")
					{
                                iHANTEI = 0;
					}
					else if( sBuf.Length() != 0)
					{
                                iHANTEI = 1;
					}
					break;
				default:
                    iHANTEI = 2;
					sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
                    if(sBuf.Length() != 0 ) iHANTEI = 0;
				}
			}
		}
		break;
//����f�މ��
   case 3:
		if(!hCELLINFO_SOKU_SOZAI) return(2);
		// 2003/06/02 K.Yamada �ΏۃZ�����������́A�����𒆎~���܂�
		if( SGr_vSOKU_SOZAI->RowCount == 1 ) return(2);
		if(Form1->SGr_tSOKU->Cells[0][0]!="" && hCELLINFO_SOKU_SOZAI != NULL)
		{
			if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD){
				sBuf = pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount + ARow].RESULT;
			}
			sBuf = pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount + ARow].DISP_RESULT;
			if( hCELLINFO_SOKU_SOZAI )
			{
//���͂����l�̏ꍇ�A�K�i���Z�o����
				if((AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 1)
				|| (AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 2))
				{
					dMAX = pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].MAX;
					dMIN = pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].MIN;
				}
			}
		}
	//�ȏ�ȉ��̋K�i�̏ꍇ�΍�
		iKIKA_KIND = 1;		//�f�t�H���g�͏㉺���Ŕ���
		if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].KIKA_TYPE) == 1)
		{
			if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].KIKA_KIND) == 2)
			{
				iKIKA_KIND = 2;
			}
			else if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].KIKA_KIND) == 3)
			{
				iKIKA_KIND = 3;
			}
		}

//�t�H�[�}�b�g����
		if(hCELLINFO_SOKU_SOZAI )
		{
			if(asString == "�s�v"
			|| AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].RESULT) == "�s�v")
			{
				sBuf = "�s�v";
				//�Z�����͂��o�b�t�@�Ɏ�荞��
				strcpy(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].RESULT		,sBuf.c_str());
				strcpy(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].DISP_RESULT,sBuf.c_str());
				pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].JUDGE = 2;
			}
			else
			{
				switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:		//�����E����
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_SOKU_SOZAI[(ACol*SGr_vSOKU_SOZAI->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( i1 == 0 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 1:		//�p�x
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_SOKU_SOZAI[(ACol*SGr_vSOKU_SOZAI->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( i1 == 0 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 2:  	//�ǁE��
					break;
				default:	//����
					break;
				}
				switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:
					if(AnsiString(SGr_vSOKU_SOZAI->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}
					//2003.05.08 E.Takase Add��
					bRtn = ConvDoubleDefS(SGr_vSOKU_SOZAI->Cells[ACol][ARow],sDeci1,SGr_vSOKU_SOZAI->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add��
					//�ǔ۔���
					//2003.05.08 E.Takase Add��
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
						case 2:
							if( dBuf <= dMAX )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
							break;
						case 3:
							if( dBuf >= dMIN )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
							break;
						default:
                            // 2003/10/06 A.Tamura �Ȃ����K�i���Ȃ̂ɋK�i�O�Ɣ��肳���̂�Double�^���Đݒ肵�܂��B
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN)
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
						}
					} else {
						iHANTEI = 2;
					}
					//2003.05.08 E.Takase Add��
					break;
				case 1:
					if(AnsiString(SGr_vSOKU_SOZAI->Cells[ACol][ARow]).Length() == 0)
					{
						iHANTEI = 2;
					}
					//2003.05.08 E.Takase Add��
					bRtn = ConvDoubleDefS(SGr_vSOKU_SOZAI->Cells[ACol][ARow],sDeci1,SGr_vSOKU_SOZAI->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add��
					//�ǔ۔���
					//2003.05.08 E.Takase Add��
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
						case 2:
							if( dBuf <= dMAX )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
							break;
						case 3:
							if( dBuf >= dMIN )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
							break;
						default:
                            // 2003/10/06 A.Tamura �Ȃ����K�i���Ȃ̂ɋK�i�O�Ɣ��肳���̂�Double�^���Đݒ肵�܂��B
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN)
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
						}
					} else {
                        iHANTEI = 2;
					}
					//2003.05.08 E.Takase Add��

					break;
				case 2:
                    iHANTEI = 2;
					sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
					sBuf = sBuf.Trim();
					if( sBuf == 0 || sBuf == "��")
					{
						iHANTEI = 0;
					}
					else if( sBuf.Length() != 0)
					{
						iHANTEI = 1;
					}
					break;
				default:
                    iHANTEI = 2;
					sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
                    if( sBuf.Length() != 0 ) iHANTEI = 0;
				}
			}
		}
		break;
//����f�ރO���b�h
   case 4:
		if(!hCELLINFO_RIRE_SOZAI) return(2);
		// 2003/06/02 K.Yamada �ΏۃZ�����������́A�����𒆎~���܂�
		if( SGr_vRIRE_SOZAI->RowCount == 1 ) return(2);

		if(Form1->SGr_tRIRE->Cells[0][0]!="" && hCELLINFO_RIRE_SOZAI != NULL)
		{
			if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
				sBuf = pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount + ARow].RESULT;
			}
			sBuf = pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount + ARow].DISP_RESULT;
			if( hCELLINFO_RIRE_SOZAI )
			{
//���͂����l�̏ꍇ�A�K�i���Z�o����
				if((AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 1)
				|| (AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 2))
				{
					dMAX = pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].MAX;
					dMIN = pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].MIN;
				}
			}
		}
	//�ȏ�ȉ��̋K�i�̏ꍇ�΍�
		iKIKA_KIND = 1;		//�f�t�H���g�͏㉺���Ŕ���
		if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].KIKA_TYPE) == 1)
		{
			if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].KIKA_KIND) == 2)
			{
				iKIKA_KIND = 2;
			}
			else if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].KIKA_KIND) == 3)
			{
				iKIKA_KIND = 3;
			}
		}

//�t�H�[�}�b�g����
		if(hCELLINFO_RIRE_SOZAI )
		{
			if(asString == "�s�v"
			|| AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].RESULT) == "�s�v")
			{
				sBuf = "�s�v";
				//�Z�����͂��o�b�t�@�Ɏ�荞��
				strcpy(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].RESULT		,sBuf.c_str());
				strcpy(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].DISP_RESULT,sBuf.c_str());
				pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].JUDGE = 2;
			}
			else
			{
				switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:		//�����E����
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_RIRE_SOZAI[(ACol*SGr_vRIRE_SOZAI->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( sDeci1.Length() == 1 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 1:		//�p�x
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_RIRE_SOZAI[(ACol*SGr_vRIRE_SOZAI->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( sDeci1.Length() == 1 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 2:  	//�ǁE��
					break;
				default:	//����
					break;
				}
				//SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;		//����p�F�����l��OK��
				switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:
					if(AnsiString(SGr_vRIRE_SOZAI->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}
					//2003.05.08 E.Takase Add��
					bRtn = ConvDoubleDefS(SGr_vRIRE_SOZAI->Cells[ACol][ARow],sDeci1,SGr_vRIRE_SOZAI->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add��

					//�Z�����͂��o�b�t�@�Ɏ�荞��
					if(hCELLINFO_RIRE_SOZAI)
					{
						//����p��ʂňȊO
						if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
					//�ǔ۔���
					//2003.05.08 E.Takase Add��
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);

						switch( iKIKA_KIND )
						{
						case 2:
							if( dBuf <= dMAX )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
							break;
						case 3:
							if( dBuf >= dMIN )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
							break;
						default:
                            // 2003/10/06 A.Tamura �Ȃ����K�i���Ȃ̂ɋK�i�O�Ɣ��肳���̂�Double�^���Đݒ肵�܂��B
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN)
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
						}

					} else {
						iHANTEI = 2;
					}
					//2003.05.08 E.Takase Add��
					break;
				case 1:
					if(AnsiString(SGr_vRIRE_SOZAI->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}

					//2003.05.08 E.Takase Add��
					bRtn = ConvDoubleDefS(SGr_vRIRE_SOZAI->Cells[ACol][ARow],sDeci1,SGr_vRIRE_SOZAI->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add��

					//�ǔ۔���
					//2003.05.08 E.Takase Add��
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
						case 2:
							if( dBuf <= dMAX )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
							break;
						case 3:
							if( dBuf >= dMIN )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
							break;
						default:
                            // 2003/10/06 A.Tamura �Ȃ����K�i���Ȃ̂ɋK�i�O�Ɣ��肳���̂�Double�^���Đݒ肵�܂��B
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN)
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
						}
					} else {
						iHANTEI = 2;
					}
					//2003.05.08 E.Takase Add��

					break;
				case 2:
                    iHANTEI = 2;
					sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
					sBuf = sBuf.Trim();
					if( sBuf == 0 || sBuf == "��")
					{
						iHANTEI = 0;
					}
					else if( sBuf.Length() != 0)
					{
						iHANTEI = 1;
					}
                    break;
				default:
					iHANTEI = 2;
					sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
                    if(sBuf.Length()!=0) iHANTEI = 0;
				}
			}
		}
	}
    return(iHANTEI);
}



//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�    �F���l���Ƀt�H�[�J�X�����������ꍇ�̏������s���܂��B
//
//  �@�\����
//    BtnF01 ���@�L���ɂ��܂��B�B
//    Form2->Tag �̒l��12�ɃZ�b�g���u�ꗗ�����v�{�^��������̏�����L���ɂ��܂��B
//
//  �p�����^����
//  �@TObject *Sender   �F�Ăяo������VCL�I�u�W�F�N�g(���I�R���g���[���iMEMO�j�j
//
//  �߂�l
//    AnsiString sMEMO_NAME �F�Ăяo����MEMO�̖��O
//
//  ���l
//�@  �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Mem_MEMOEnter(TObject *Sender)
{
    TMemo* memoBuf = dynamic_cast<TMemo*>(Sender);

    sMEMO_NAME = memoBuf->Name;
    Form2->Tag = 12;
    BtnF01->Enabled = true;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�    �F���l������t�H�[�J�X���O�ꂽ�ꍇ�̏������s���܂��B
//
//  �@�\����
//    BtnF01 ���@�����ɂ��܂��B�B
//    Form2->Tag �̒l��0�ɃZ�b�g���u�ꗗ�����v�{�^��������̏����𖳌��ɂ��܂��B
//
//  �p�����^����
//  �@TObject *Sender   �F�Ăяo������VCL�I�u�W�F�N�g(���I�R���g���[���iMEMO�j�j
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//�@  �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Mem_MEMOExit(TObject *Sender)
{
    Form2->Tag = 0;
    BtnF01->Enabled = false;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐��F�������b�g�ɕ����\�ő��肳�ꂽ���̂����邩�𒲂ׂ܂��B
//
//  �@�\����
//    �@���ꃍ�b�g�������\�ɂ���΃t���O��True�ɂ��čĕ`����s���܂��B
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::BUNKATU_CHECK(void)
{
	AnsiString sBuf,sLot;
	int iCol;
    int i1;
	AnsiString sSelectLot;
    bool bBUNKATUARI;

//�t���O�̏�����
    for(i1 = 0;i1<1000;i1++)
    {
        bBUNKATU_RIRE[i1] = false;
        bBUNKATU_SOKU[i1] = false;
    }
//sLot �Ɂ@�����\�ő��肷�郍�b�g�������A���������邩�𒲂ׂ�
//�����\�ߋ����т̃��[�h���z����
	sLot = "";
//�������̃��b�g�̓ǂݍ���
    for(iCol = 0; iCol < SGr_tRIRE->ColCount;iCol++)
    {
		if(SGr_tRIRE->Cells[iCol][0].Length() !=0)
		{
			sLot += "'" + SGr_tRIRE->Cells[iCol][0] + "',";
		}
	}
    for(iCol = 0; iCol < SGr_tSOKU->ColCount;iCol++)
    {
		if(SGr_tSOKU->Cells[iCol][0].Length() !=0)
		{
			sLot += "'" + SGr_tSOKU->Cells[iCol][0] + "',";
		}
	}
	sLot = sLot.SubString(1,sLot.Length()-1);

    //2003.05.12 E.Takase Add��
/* 2005.09.26 Y.Sano ���ؗp�폜
    sBuf  = "SELECT  KSD11.*, SM12S.TANNAM As UPDNAME ";*/
/* 2005.09.26 Y.Sano ���ؗp�ǉ�*/
    sBuf  = "SELECT  KSD11.LOTNO, SM12S.TANNAM As UPDNAME ";
    sBuf += " FROM KSD11 LEFT JOIN SM12S ON KSD11.UPDCHR = SM12S.TANSYA ";
    //2003.05.12 E.Takase Add��
    sBuf += " WHERE DTKSHIN ='" + sNowDTKSHIN + "'";
    if( sLot.Length() > 3 ) {
        sBuf += " AND LOTNO IN ("+ sLot + ")";
    }
    //2003.05.12 E.Takase Add��
    sBuf += " ORDER BY LOTNO,KSD11.UPDYMD,KSD11.UPDTIM";
    //2003.05.12 E.Takase Add��

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();
    Query1->SQL->Add(sBuf);
    Query1->Open();
    Query1->Active = true;

    while( Query1->Eof == false )
    {
        sSelectLot = Query1->FieldValues["LOTNO"];
        bBUNKATUARI = false;
        for(iCol = 0; iCol < SGr_tRIRE->ColCount;iCol++)
        {
            if(sSelectLot == SGr_tRIRE->Cells[iCol][0])
            {
                bBUNKATUARI = true;
                bBUNKATU_RIRE[iCol] = true;
                break;
            }
        }
        if(bBUNKATUARI == false )
        {
            for(iCol = 0; iCol < SGr_tSOKU->ColCount;iCol++)
            {
                if(sSelectLot == SGr_tSOKU->Cells[iCol][0])
                {
                    bBUNKATU_SOKU[iCol] = true;
                    break;
                }
            }
        }
        Query1->Next();
    }
    Query1->Close();
    for(iCol = 0; iCol < SGr_tRIRE->ColCount;iCol++)
    {
		if(SGr_tRIRE->Cells[iCol][0].Length() !=0)
		{
			SGr_tRIRE->Cells[iCol][0] =  SGr_tRIRE->Cells[iCol][0];
		}
	}
    for(iCol = 0; iCol < SGr_tSOKU->ColCount;iCol++)
    {
		if(SGr_tSOKU->Cells[iCol][0].Length() !=0)
		{
			SGr_tSOKU->Cells[iCol][0] = SGr_tSOKU->Cells[iCol][0];
		}
	}
    bBUNKATUARI = false;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    DrawCell�C�x���g	�F���胍�b�g�̃Z��������������Ɣ������܂��B
//
//  �@�\����
//    �����F�̕ύX�i�����clGreen or clBlack)�B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    int   ACol         : AnsiSting�̃J�����ʒu
//    int   ARow        :  AnsiSting��Row�ʒu(�P�s�Ȃ̂ŏ��0�j
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tSOKUDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
    AnsiString sBuf;
    TStringGrid* strGrid = dynamic_cast<TStringGrid*>(Sender);
	RECT r=RECT(Rect);

    sBuf ="       ";
    if(bBUNKATU_SOKU[ACol] == true ) {
        SGr_tSOKU->Canvas->Font->Color = clGreen;
        DrawText(SGr_tSOKU->Canvas->Handle,sBuf.c_str(),-1,&r,DT_LEFT); //����
    }
    else
    {
        SGr_tSOKU->Canvas->Font->Color = clBlack;
    }
    sBuf = strGrid->Cells[ACol][0];
    SGr_tSOKU->Canvas->FillRect(Rect);
    InflateRect(&r,-2,-2);
    DrawText(SGr_tSOKU->Canvas->Handle,sBuf.c_str(),-1,&r,DT_LEFT); //����
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//
//  �T�v
//    DrawCell�C�x���g	�F�������b�g�̃Z��������������Ɣ������܂��B
//
//  �@�\����
//    �����F�̕ύX�i�����clGreen or clBlack)�B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    int   ACol         : AnsiSting�̃J�����ʒu
//    int   ARow        :  AnsiSting��Row�ʒu(�P�s�Ȃ̂ŏ��0�j
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tRIREDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
    AnsiString sBuf;
    TStringGrid* strGrid = dynamic_cast<TStringGrid*>(Sender);
	RECT r=RECT(Rect);

    sBuf ="       ";
    if(bBUNKATU_RIRE[ACol] == true ) {
        SGr_tRIRE->Canvas->Font->Color = clGreen;
        DrawText(SGr_tRIRE->Canvas->Handle,sBuf.c_str(),-1,&r,DT_LEFT); //����
    }
    else
    {
        SGr_tRIRE->Canvas->Font->Color = clBlack;
    }
    sBuf = strGrid->Cells[ACol][0];
    SGr_tRIRE->Canvas->FillRect(Rect);
    InflateRect(&r,-2,-2);
    DrawText(SGr_tRIRE->Canvas->Handle,sBuf.c_str(),-1,&r,DT_LEFT); //����

}
//---------------------------------------------------------------------------
