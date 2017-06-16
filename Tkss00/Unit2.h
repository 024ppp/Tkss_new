//---------------------------------------------------------------------------
#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE �Ǘ��̃R���|�[�l���g
    TEdit *Edit1;
    TLabel *Label1;
    TLabel *Label2;
    TMaskEdit *MaskEdit1;
    TButton *Button1;
    TButton *Button2;
    TQuery *Query1;
    TDatabase *Database1;
    void __fastcall CancleClick(TObject *Sender);
    void __fastcall OkClick(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormKeyPress(TObject *Sender, char &Key);
private:	// ���[�U�[�錾
    int __fastcall PasswordCheck();

public:		// ���[�U�[�錾
    __fastcall TForm2(TComponent* Owner);
    void __fastcall PGMStart(int PassFlag);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
