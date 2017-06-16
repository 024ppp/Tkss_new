//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <CheckLst.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <stdio.h>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE �Ǘ��̃R���|�[�l���g
	TPanel *Panel9;
	TButton *BtnF01;
	TButton *BtnF02;
	TButton *BtnF03;
	TButton *BtnF04;
	TButton *BtnF05;
	TButton *BtnF06;
	TButton *BtnF07;
	TButton *BtnF08;
	TButton *BtnF09;
	TButton *BtnF10;
	TButton *BtnF11;
	TButton *BtnF12;
	TStatusBar *SBr1;
	TPanel *Panel170;
	TPanel *Panel5;
	TPanel *Panel2;
	TEdit *Edt_COD1;
	TPanel *Panel3;
	TPanel *Panel24;
	TEdit *Edt_COD2;
	TPanel *Panel23;
	TEdit *Edt_COD3;
	TPanel *Panel16;
	TEdit *Edt_COD4;
	TPanel *Panel4;
	TCheckBox *Cbx_RIREKI;
	TPanel *Panel12;
	TPanel *Pnl_List;
	TStringGrid *SGr_List;
	TPanel *Panel14;
	TPanel *Pnl_SOKUT;
	TStringGrid *SGr_SOKUT;
	TPanel *Pnl_DETIALES_TOP;
	TPanel *Pnl01;
	TEdit *Edt_DTKSCOD;
	TEdit *Edt_DTKSNAM;
	TPanel *Pnl03;
	TEdit *Edt_DTKSHIN;
	TPanel *Panel28;
	TListBox *Lbx_DTKSHIN_SZ;
	TPanel *Pnl04;
	TEdit *Edt_HINBAN;
	TPanel *Pnl05;
	TEdit *Edt_ZISNAM;
	TPanel *Panel34;
	TLabel *Label2;
	TPanel *Panel17;
	TEdit *Edt_HINMEI;
	TPanel *PnlADDYMD1;
	TPanel *PnlADDYMD2;
	TPanel *PnlUPDCNT1;
	TPanel *PnlUPDCNT2;
	TPanel *PnlREVCNT1;
	TPanel *PnlREVCNT2;
	TPanel *PnlUPDYMD2;
	TPanel *PnlUPDCHR1;
	TPanel *PnlUPDYMD1;
	TPanel *PnlUPDCHR2;
	TSplitter *Splitter1;
	TPanel *Panel13;
	TPanel *Panel15;
	TPanel *Panel18;
	TPanel *Panel20;
	TPanel *Panel21;
	TBitBtn *Btn_ADD_SZ;
	TBitBtn *Btn_ADD_SK;
	TBitBtn *Btn_ADD_SP;
	TBitBtn *Btn_UP;
	TBitBtn *Btn_DOWN;
	TBitBtn *Btn_DEL;
	TPanel *Panel26;
	TBitBtn *Btn_EDIT;
        TPanel *Panel27;
	TPanel *Pnl_SOKUTEI_NUM;
	TCheckListBox *Clb_OUT_TITLE;
	TLabel *Label3;
	TLabel *Label4;
	TPanel *Panel19;
	TPanel *Panel25;
	TPanel *Panel30;
	TLabel *Label1;
	TRadioButton *Rdo_XOUT_ON;
	TRadioButton *Rdo_XOUT_OFF;
	TShape *Shape1;
    TPanel *Panel31;
	TPanel *Pnl_LOT_LINK_SZ;
	TRadioButton *Rdo_LOT_LINK_SZ_ON;
	TRadioButton *Rdo_LOT_LINK_SZ_OFF;
	TPanel *Panel6;
	TPanel *PnlBumCode;
	TPanel *PnlBumName;
	TPanel *Panel1;
	TPanel *PnlTanCode;
	TPanel *PnlTanName;
	TDatabase *Database1;
	TQuery *Query1;
	TPanel *Panel7;
	TEdit *Edt_MEMO;
	TButton *Btn_DTKSHIN_SZ_ADD;
	TButton *Btn_DTKSHIN_SZ_DEL;
	TQuery *Query2;
	void __fastcall Pnl_ListResize(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Pnl_SOKUTResize(TObject *Sender);
	void __fastcall Btn_ADD_SKClick(TObject *Sender);
	void __fastcall Btn_ADD_SZClick(TObject *Sender);
    void __fastcall Btn_EDITClick(TObject *Sender);
    void __fastcall SGr_SOKUTDblClick(TObject *Sender);
	void __fastcall FormEnter(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall BtnF01Click(TObject *Sender);
	void __fastcall BtnF02Click(TObject *Sender);
	void __fastcall BtnF03Click(TObject *Sender);
	void __fastcall BtnF05Click(TObject *Sender);
	void __fastcall BtnF07Click(TObject *Sender);
	void __fastcall BtnF08Click(TObject *Sender);
	void __fastcall BtnF09Click(TObject *Sender);
	void __fastcall BtnF10Click(TObject *Sender);
	void __fastcall BtnF11Click(TObject *Sender);
	void __fastcall BtnF12Click(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall Edt_ALLChange_Base(TObject *Sender);
	void __fastcall Edt_ALLChange(TObject *Sender);
	void __fastcall SGr_ListSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall SGr_ListDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
	void __fastcall Btn_DTKSHIN_SZ_DELClick(TObject *Sender);
	void __fastcall Btn_DTKSHIN_SZ_ADDClick(TObject *Sender);
	void __fastcall Clb_OUT_TITLEClickCheck(TObject *Sender);
	void __fastcall SGr_SOKUTDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
	void __fastcall Btn_UPClick(TObject *Sender);
	void __fastcall Btn_DOWNClick(TObject *Sender);
	void __fastcall SGr_SOKUTClick(TObject *Sender);
	void __fastcall SGr_ListKeyPress(TObject *Sender, char &Key);
	void __fastcall SGr_SOKUTRowMoved(TObject *Sender, int FromIndex,
          int ToIndex);
	void __fastcall Btn_ADD_SPClick(TObject *Sender);
	void __fastcall Btn_DELClick(TObject *Sender);
	void __fastcall Rdo_AllClick(TObject *Sender);
	void __fastcall Edt_ALLChange_DTKSHIN(TObject *Sender);
	//void __fastcall SGr_ListDblClick(TObject *Sender);

private:	// ���[�U�[�錾

	int     USER_COD;
	String  USER_NAM;
	String  BUMO_COD;
	String  BUMO_NAM;

    // �������я��^�C�g�����ڃ}�X�^�[�̌������������m��
    int		*iTITLE;
    int		iTITLE_Cnt;
    HANDLE  hMemTITLE;

    //int  iSOKUT_UNQ_NO_MAX;
    int		iRowSelTop;
    int		iRowSelBottom;

    // �u�ۑ��v�t���O(false=�ۑ��ϖ��̓f�[�^�ҏW�����Atrue=�ۑ�����)
    bool	DataSave;

	// ���i�K�i�}�X�^�[
	struct KSM01_DATA {
		char	DTKSHIN[21];		// ���Ӑ�i��
		char	REVCNT[4];			// �����ԍ�
		char	HINBAN[21];			// ���Еi��
		char	DTKSCOD[6];			// ���Ӑ�R�[�h
		char	DTKSNAM[51];		// ���Ӑ於��
		char	ZISNAM[21];			// �ގ����́i�i��j
		char	HINMEI[61];			// �i��
		char	DTKSHIN1_SZ[21];	// �f�ޗp���Ӑ�i��1
		char	DTKSHIN2_SZ[21];	// �f�ޗp���Ӑ�i��2
		char	DTKSHIN3_SZ[21];	// �f�ޗp���Ӑ�i��3
		char	DTKSHIN4_SZ[21];	// �f�ޗp���Ӑ�i��4
		char	DTKSHIN5_SZ[21];	// �f�ޗp���Ӑ�i��5
		char	DTKSHIN6_SZ[21];	// �f�ޗp���Ӑ�i��6
		char	LOT_LINK_SZ[2];		// �f�ޗp���b�g�̃����N
		char	SOKUTEI_NUM[3];		// ���荀�ڐ�
		char	OUT_TITLE1[5];		// ���я��^�C�g���o�͍���1
		char	OUT_TITLE2[5];		// ���я��^�C�g���o�͍���2
		char	OUT_TITLE3[5];		// ���я��^�C�g���o�͍���3
		char	OUT_TITLE4[5];		// ���я��^�C�g���o�͍���4
		char	OUT_TITLE5[5];		// ���я��^�C�g���o�͍���5
		char	OUT_TITLE6[5];		// ���я��^�C�g���o�͍���6
		char	OUT_TITLE7[5];		// ���я��^�C�g���o�͍���7
		char	OUT_TITLE8[5];		// ���я��^�C�g���o�͍���8
		char	X_OUT[2];			// �w�̏o��
		char	MEMO[129];			// ���l
		char	ADDYMD[9];			// �o�^��
		char	ADDTIM[5];			// �o�^����
		char	UPDYMD[9];			// �ύX��
		char	UPDTIM[5];			// �ύX����
		char   	UPDCHR[7];			// �X�V�ҁi�R�[�h�j
        char    UPDNAM[51];			// �X�V�ҁi���́j
		char	UPDCNT[4];			// �X�V��
	} tmpKSM01_DATA;

    void __fastcall InitEdt(bool status);
	void __fastcall SGr_ListLinePaste( int iPstIndex );
	void __fastcall SetDTKSHIN_SZ( AnsiString sDTKSHIN );
    void __fastcall SetDTKSNAM( AnsiString sDTKSCOD );
    bool __fastcall AddData( int iUpd );
    bool __fastcall AddData_Details( int iUpd );
	void __fastcall UpdKaiteiNo( AnsiString sDTKSHIN );
    bool __fastcall DelData( bool *iRIREKI_DEL );
	void __fastcall SGr_ListDblClick( int ARow );

public:		// ���[�U�[�錾

    // ����@�퍀�ڃ}�X�^�[�̌������������m��
    int		*iKIKI;
    int		iKIKI_Cnt;
    HANDLE  hMemKIKI;

    // �t�H���g�֘A
    HANDLE  OrgFont, MyFont;
    LOGFONT LogFont;

    // �f�[�^���ύX���ꂽ���ǂ����̃t���O(0=�X�V�ϖ��̓f�[�^�ύX�����A1=�X�V����)
    int		DataChange;

	// ���i�K�i���׃}�X�^�[
	struct KSM02_DATA {
		char	DTKSHIN[21];		// ��\���Ӑ�i��
		char	REVCNT[5];			// �����ԍ�
		char	UNQ_NO[5];			// ����NO
		char	ORDER_NO[5];		// �\����
		char	SKB_NO[2];			// ����NO
		char	HINBAN_SK[21];		// �i��
		char	KOMK_NO[5];			// ����NO
		char	KOMK_NM[41];		// ���荀�ږ��́i���{��j
		char	KOMK_ENG[41];		// ���荀�ږ��́i�p��j
		char	KOMK_SUB[21];		// ���荀�ڃT�u���́i���{��j
		char	KOMK_SUB_ENG[21];	// ���荀�ڃT�u���́i�p��j
		char	KIKI_NO[3];			// ����@��NO
		char	KIKI_NM[41];		// ����@�햼��
		char    TANI[21];			// �P��
		char    KIKA_TYPE[2];		// �K�i�^�C�v
		char    KIKA_KIND[2];		// �K�i���
		char    KIKA_DECI[2];		// �K�i�����_�ȉ�����
		char    KIKA_NUM1[13];		// �K�i�l�P
		char    KIKA_NUM2[13];		// �K�i�l�Q
		char    KIKA_NUM3[13];		// �K�i�l�R
		char    KIKA_STR[41];		// �K�i�l����
		char    KIKA_SUB1[21];		// �K�i�l�T�u�P
		char    KIKA_SUB2[21];		// �K�i�l�T�u�Q
		char    KIKA_SUB3[21];		// �K�i�l�T�u�R
		char    SOKU_SU[3];			// ����w��n��
		char    SOKU_FLG[2];		// ���荀�ڂ̗L��
		char    TOKU_FLG[2];		// ���ʍ��ڂ̗L��
		char    KIKA_PRT[2];		// ��������l�̈��
		char    VALUE_TYPE[2];		// ����l�\��
		char    VALUE_DECI[2];		// ����l�����_�ȉ�����
	} tmpKSM02_DATA;

    KSM02_DATA	*cpyKSM02_DATA;		// ���荀�ڃR�s�[�p�o�b�t�@
    HANDLE		hMemCpyKSM02_DATA;	// ���荀�ڃR�s�[�p�o�b�t�@�̃������n���h��
    int			iCntCpyKSM02_DATA;	// ���荀�ڃR�s�[�p�o�b�t�@�̐�

	__fastcall TForm1(TComponent* Owner);

    void __fastcall Ins_SGr_SOKUT(int iRow);
    void __fastcall RowExchange(int FromIndex, int ToIndex);
	AnsiString __fastcall SGr_SOKUT_GridLineCopy(int iCpyIndex);
	void __fastcall SGr_SOKUT_GridLinePaste(int iPstIndex, AnsiString sUpdFlg, bool iOrderNo_UP);
    void __fastcall ExtractCode(AnsiString str);

	bool __fastcall SGr_SOKUT_GridMultiLineCopy();
	bool __fastcall SGr_SOKUT_GridMultiLinePaste();

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
