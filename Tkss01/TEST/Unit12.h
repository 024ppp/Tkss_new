//---------------------------------------------------------------------------
#ifndef Unit12H
#define Unit12H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TForm12 : public TForm
{
__published:	// IDE �Ǘ��̃R���|�[�l���g
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TButton *ButtonOK;
    TButton *ButtonCancel;
    TRadioButton *Rdo_Button1;
    TRadioButton *Rdo_Button2;
    void __fastcall ButtonOKClick(TObject *Sender);
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall ButtonCancelClick(TObject *Sender);
    void __fastcall InfoClear(void);
    void __fastcall LOTNO1_SZ_Clear(void);
    void __fastcall Label4Click(TObject *Sender);
    void __fastcall Label2Click(TObject *Sender);
private:	// ���[�U�[�錾
public:		// ���[�U�[�錾
    __fastcall TForm12(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm12 *Form12;
//---------------------------------------------------------------------------
#endif