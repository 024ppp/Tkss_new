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
// k.k start
#include <fstream>
#include "StdComm32.h"

using namespace std;
// k.k end
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE 管理のコンポーネント
	TLabel *Lbl_1;
	TLabel *Lbl_2;
    TProgressBar *ProgressBar;
	TTimer *Tmr_CountDown;
	TButton *Btn_Exit;
	TDatabase *Database1;
	TQuery *Query1;
	void __fastcall Tmr_CountDownTimer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Btn_ExitClick(TObject *Sender);
private:	// ユーザー宣言
	void __fastcall Main();

    // k.k start
    AnsiString fn;
    fstream fs;						// 入出力ファイルストリーム
    int iComPort;					// ポート
    time_t sTime;                   // タイムアウトチェック用
    // end
public:		// ユーザー宣言

    AnsiString	sCOMMAND;

    // k.k start
    AnsiString DataReceive();
	AnsiString CreatBCC(AnsiString asStr);
    // end

    __fastcall TForm1(TComponent* Owner);
    int DataDownLoad();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
