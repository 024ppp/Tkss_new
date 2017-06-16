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
__published:	// IDE �Ǘ��̃R���|�[�l���g
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
private:	// ���[�U�[�錾
	void __fastcall Main();

    // k.k start
    AnsiString fn;
    fstream fs;						// ���o�̓t�@�C���X�g���[��
    int iComPort;					// �|�[�g
    time_t sTime;                   // �^�C���A�E�g�`�F�b�N�p
    // end
public:		// ���[�U�[�錾

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
