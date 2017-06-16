//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "NumberEdit.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck は、定義されたコンポーネントが純粋仮想関数を含む
// 抽象クラスではないことを確認するために定義されています。
//

static inline void ValidCtrCheck(TNumberEdit *)
{
    new TNumberEdit(NULL);
}
//---------------------------------------------------------------------------
__fastcall TNumberEdit::TNumberEdit(TComponent* Owner)
        : TEdit(Owner)
{
    MaxLength = 1;
    FPos = 0;
}
//---------------------------------------------------------------------------
namespace Numberedit
{
        void __fastcall PACKAGE Register()
        {
                 TComponentClass classes[1] = {__classid(TNumberEdit)};
                 RegisterComponents("Samples", classes, 0);
        }
}
//---------------------------------------------------------------------------


void __fastcall TNumberEdit::SetValue(long double Value)
{
    FValue = Value;
//    sType = "%." + IntToStr(FFPos);
/*
    if( FComma ){
        sType = sType + "n";
        TEdit::Text = Format(sType, ARRAYOFCONST(((long double)FValue)) );
    } else {
        sType = sType + "f";
        TEdit::Text = Format(sType, ARRAYOFCONST(((long double)FValue)) );
    }
    if( FYen ){
        TEdit::Text = "\\" + TEdit::Text;
    }
*/
//    sType = sType + "f";
//    TEdit::Text = Format(sType, ARRAYOFCONST(((long double)FValue)) );
}

void __fastcall TNumberEdit::SetText(AnsiString Text)
{
    char *endptr;
    long double Val1;
    Val1 = _strtold(Text.c_str(), &endptr);
    FValue = Val1;
    sType = "%." + IntToStr(FFPos)+ "f";
    TEdit::SetTextBuf(Format(sType, ARRAYOFCONST(((long double)FValue))).c_str());
}

/*
void __fastcall TNumberEdit::SetComma(bool Flag)
{
    FComma = Flag;
    Value = Value;
}

void __fastcall TNumberEdit::SetYen(bool Flag)
{
    FYen = Flag;
    Value = Value;
}
*/

void __fastcall TNumberEdit::SetFPos(int FPos)
{
    if( FPos >= FMaxLength ){
        MessageDlg("MaxLengthより小さい値をセットしてください",mtError,TMsgDlgButtons() << mrOk, 0);
        FFPos = FMaxLength-1;
    }
    else{
        FFPos = FPos;
    }
    FValue = FValue;
}

AnsiString __fastcall TNumberEdit::GetText(void)
{
    return TEdit::Text;
}

void __fastcall TNumberEdit::CreateParams(Controls::TCreateParams &Params)
{
    TEdit::CreateParams(Params);
    Params.Style |= ES_RIGHT | ES_MULTILINE;
    ImeMode = imDisable;
}

int __fastcall TNumberEdit::SetMaxLength(int MaxLength)
{
    if( MaxLength <= 0 ){
        MessageDlg("１以上の整数をセットしてください",mtError,TMsgDlgButtons() << mrOk, 0);
        FMaxLength = 1;
    }
    else{
        FMaxLength = MaxLength;
    }
    return FMaxLength;
}

void __fastcall TNumberEdit::KeyPress(char &Key)
{
    if( Key == VK_BACK || Key == VK_UP || Key == VK_DOWN )    return;

    if( Key == VK_RETURN ) {
        Key = 0;
        return;
    }
    else if( Key!='-' && Key!='.' && Key>='!' && (Key<'0' || Key>'9') ) Key = 0;
    if( FPos == 0 && Key == '.' ) Key = 0;
    if( FPos == 0 && TEdit::SelLength == 0 && TEdit::Text.Length() >= FMaxLength ) Key = 0;
    if( Key == 0 ) return;
    if( FPos > 0 ){
        if( TEdit::Text.AnsiPos(".") > 0 ){
            // カンマが既に有り
            if( Key == '.' ) Key = 0;
        }
        if( TEdit::SelLength == 0 && TEdit::Text.Length() >= (FMaxLength+1) ){
            Key = 0;
        }
    }
    TEdit::KeyPress(Key);
}

/*
void __fastcall KeyDown(Word &Key, Classes::TShiftState Shift)
{
    TEdit::KeyDown( Key, Shift);
}
*/

void __fastcall TNumberEdit::DoEnter()
{
    //TEdit::Text = DelCommaYen(TEdit::Text);
    TEdit::SelectAll();
    TEdit::DoEnter();
}

void __fastcall TNumberEdit::DoExit()
{

    char *endptr;
    long double Val1;
    //TEdit::Text = DelCommaYen(TEdit::Text);

    Val1 = _strtold(TEdit::Text.c_str(), &endptr);
    if( pow10(FMaxLength-FPos) <= Val1 ){
       Val1 = Val1 - (Val1 - (pow10(FMaxLength-FPos) - 1));
    }
    sType = "%." + IntToStr(FFPos)+ "f";

    if( TEdit::Text.AnsiCompare(Format(sType, ARRAYOFCONST(((long double)Val1))).c_str()) ){
        TEdit::SetTextBuf(Format(sType, ARRAYOFCONST(((long double)Val1))).c_str());
    }
    FValue = Val1;

    TEdit::DoExit();
}


void __fastcall TNumberEdit::Change()
{
    char *endptr;
    long double Val1;

    Val1 = _strtold(TEdit::Text.c_str(), &endptr);
    if( pow10(FMaxLength-FPos) <= Val1 ){
       Val1 = Val1 - (Val1 - (pow10(FMaxLength-FPos) - 1));
       sType = "%." + IntToStr(FFPos)+ "f";
       TEdit::SetTextBuf(Format(sType, ARRAYOFCONST(((long double)Val1))).c_str());
    }
    FValue = Val1;
    TEdit::Change();
}

/*
AnsiString __fastcall TNumberEdit::DelCommaYen(AnsiString s)
{
    AnsiString out;

    out = "";
    for( int i=0; i<s.Length(); i++){
       if( s.SubString(i+1,1) != '\\' && s.SubString(i+1,1) != ',' ){
          out += s.SubString(i+1,1);
       }
    }
    return out;
}
*/
