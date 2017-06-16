//---------------------------------------------------------------------------
#ifndef Unit5H
#define Unit5H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
//---------------------------------------------------------------------------
class TForm5 : public TForm
{
__published:	// IDE �Ǘ��̃R���|�[�l���g
    TTabControl *TabControl1;
    TPanel *Panel12;
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
    TStringGrid *SGr1;
	TQuery *Query1;
    void __fastcall BtnF12Click(TObject *Sender);
    void __fastcall BtnF04Click(TObject *Sender);
    void __fastcall BtnF02Click(TObject *Sender);
    void __fastcall BtnF03Click(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall SGr1Click(TObject *Sender);
	void __fastcall SGr1DblClick(TObject *Sender);
private:	// ���[�U�[�錾
   	int	iRowSelTop;
   	int	iRowSelBottom;
public:		// ���[�U�[�錾
    bool fFind;
    __fastcall TForm5(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm5 *Form5;
//---------------------------------------------------------------------------
#endif
