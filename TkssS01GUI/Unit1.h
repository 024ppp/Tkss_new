//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <Mask.hpp>
#include <stdio.h>
#include <dir.h>

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE 管理のコンポーネント
	TLabel *Lbl_1;
	TLabel *Lbl_2;
    TProgressBar *ProgressBar;
	TTimer *Tmr_CountDown;
	TButton *Btn_Exit;
	TQuery *Query1;
	TDatabase *Database1;
	TQuery *Q_KSD21;
	TQuery *Q_KSD22;
	TQuery *Q_KSD23;
	TQuery *Q_KD_1;
	TQuery *Q_KD_2;
	TListBox *ListLog;
	TLabel *Lbl_3;
	void __fastcall Tmr_CountDownTimer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Btn_ExitClick(TObject *Sender);
private:	// ユーザー宣言
	void __fastcall Main();

public:		// ユーザー宣言

    AnsiString	sCOMMAND;

    __fastcall TForm1(TComponent* Owner);
    int DataDownLoad();

	int __fastcall AutoEntry();
    int __fastcall GetKSD29(AnsiString strFUNC_ID);
    AnsiString __fastcall SetKSD29(AnsiString strFUNC_ID,AnsiString strUPDYMD);
    int __fastcall GetDTKS(void);
	AnsiString __fastcall GetKEIJYO_KBN(void);
	void __fastcall FormatFixStr(void);

	void __fastcall FormatKSD21(int iNo);
	void __fastcall FormatKSD22(int iNo);
	void __fastcall FormatKSD23(int iNo);

	int __fastcall GetKD_1(int iNo);
	int __fastcall SrchKD_1(int iNo);
	int __fastcall SrchKD_2(int iNo);
	int __fastcall SrchKSD21(int iNo);
	int __fastcall SrchKSD22(int iNo);
	int __fastcall SrchKSD23(int iNo);

	void __fastcall SetKD_1(int iNo);
	void __fastcall SetKD_2(int iNo);
	void __fastcall SetKSD21(int iNo);
	void __fastcall SetKSD22(int iNo);

	void __fastcall CalcKD_1(int iNo);

	//データベース更新関係（Unit2）
	AnsiString __fastcall AddDataKSD21(void);
	AnsiString __fastcall UpdDataKSD21(void);

	AnsiString __fastcall AddDataKSD22(void);
	AnsiString __fastcall UpdDataKSD22(void);

	AnsiString __fastcall AddDataKSD23(int iPos);
	AnsiString __fastcall DelDataKSD23(void);

	AnsiString __fastcall UpdDataKSD21_UPDCNT(AnsiString swDTKSHIN,AnsiString swLOTNO);

	AnsiString __fastcall Null_S(Variant &vBuf);
	AnsiString __fastcall InsMEMO(AnsiString strM, int iNo, AnsiString strA);

	void __fastcall WriteErrLog(AnsiString sErrLog,  AnsiString sePrg,
								AnsiString seDTKSHIN,AnsiString seLOTNO);//ログを出力


};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
