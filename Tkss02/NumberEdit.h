//---------------------------------------------------------------------------
#ifndef NumberEditH
#define NumberEditH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
class PACKAGE TNumberEdit : public TEdit
{
private:
    long double FValue;
//    bool FComma, FYen;
    int FFPos;
    AnsiString sType;
    int FMaxLength;
    void __fastcall SetValue(long double Value);
    void __fastcall SetText(AnsiString Text);
//    void __fastcall SetComma(bool Flag);
//    void __fastcall SetYen(bool Flag);
    void __fastcall SetFPos(int FPos);
    AnsiString __fastcall GetText(void);
//    AnsiString __fastcall DelCommaYen(AnsiString s);
    int __fastcall SetMaxLength(int MaxLength);
protected:
    void __fastcall CreateParams(Controls::TCreateParams &Params);
    void __fastcall KeyPress(char &Key);
    //void __fastcall KeyDown(Word &Key, Classes::TShiftState Shift);
    void __fastcall DoEnter();
    void __fastcall DoExit();
    void __fastcall Change();
public:
    __fastcall TNumberEdit(TComponent* Owner);
__published:
    __property long double Value = {read=FValue, write=FValue, default=0};
//    __property bool Comma = {read=FComma, write=SetComma};
//    __property bool Yen = {read=FYen, write=SetYen};
    __property int FPos = {read=FFPos, write=SetFPos};
    __property AnsiString Text = {read=GetText, write=SetText};
    __property int MaxLength = {read=FMaxLength, write=SetMaxLength, default=1};
};
//---------------------------------------------------------------------------
#endif
