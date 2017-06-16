//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdlib.h>

#pragma hdrstop

#include "Unit1.h"
#include "Unit9.h"
#include <DBTables.hpp>
#include <winbase.h>
#include <shellapi.h>

//ユーザー情報
/*
extern int     USER_COD;
extern String  USER_NAM;
extern String  BUMO_COD;
extern String  BUMO_NAM;
*/
extern int KikiType;               // 機器番号PC1,2,3,4
extern int PGNo;

extern char PC12FileName[MAX_PATH];
extern char PC34FileName[MAX_PATH];


int ExeFlag = 0;

int     OLDUSER_COD;
String  OLDUSER_NAM;
String  OLDBUMO_COD;
String  OLDBUMO_NAM;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm9 *Form9;
//---------------------------------------------------------------------------
__fastcall TForm9::TForm9(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//フォームキーダウン時
void __fastcall TForm9::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     switch(Key){
         // 前項
         case VK_UP:
         case VK_LEFT:
                if( Edit1->Focused() && Edit1->SelStart == 0 && Edit1->SelLength == 0 ){
                    Button2->SetFocus();
                    break;
                }
                if( MaskEdit1->Focused() && MaskEdit1->SelStart == 0 && MaskEdit1->SelLength == 0 ){
                    Edit1->SetFocus();
                    break;
                }
                if( Button1->Focused() ) {
                    MaskEdit1->SetFocus();
                    break;
                }
                if( Button2->Focused() ) {
                    Button1->SetFocus();
                    break;
                }
                break;
         // 次項
         case VK_DOWN:
         case VK_RIGHT:
                if( Edit1->Focused() && Edit1->SelStart == Edit1->Text.Length() && Edit1->SelLength == 0 ){
                    MaskEdit1->SetFocus();
                    break;
                }
                if( MaskEdit1->Focused() && MaskEdit1->SelStart == MaskEdit1->Text.Length() && MaskEdit1->SelLength == 0 ){
                    Button1->SetFocus();
                    break;
                }
                if( Button1->Focused() ) {
                    Button2->SetFocus();
                    break;
                }
                if( Button2->Focused() ) {
                    Edit1->SetFocus();
                    break;
                }
                break;

         case VK_RETURN:
                if( Edit1->Focused() ) {
                    MaskEdit1->SetFocus();
                    break;
                }
                if( MaskEdit1->Focused() ) {
                    //Button1->SetFocus();
                    OkClick(Sender);
                    break;
                }
                if( Button1->Focused() ) {
                    OkClick(Sender);
                    break;
                }
                if( Button2->Focused() ) {
                    CancleClick(Sender);
                    break;
                }

                break;
        case VK_ESCAPE:
                CancleClick(Sender);
                break;
        default:
                break;
     }

}
//---------------------------------------------------------------------------
//キャンセル
void __fastcall TForm9::CancleClick(TObject *Sender)
{
    //ShowMessage("CancleClick");
    Close();
    Form1->SetFocus();
}
//---------------------------------------------------------------------------
//パスワードＯＫなら プログラムを起動
void __fastcall TForm9::OkClick(TObject *Sender)
{
    int PassFlag;

	//今のユーザー情報を退避させる
	OLDUSER_COD = Form1->USER_COD;
	OLDUSER_NAM = Form1->USER_NAM;
	OLDBUMO_COD = Form1->BUMO_COD;
	OLDBUMO_NAM = Form1->BUMO_NAM;
    //ユーザー名、パスワードのチェック
    PassFlag = PasswordCheck();
	switch(PassFlag)
	{
    case 1:
    	ShowMessage("ユーザ名を入力してください");
        Edit1->SetFocus();
        break;

    case 2:
    	ShowMessage("ユーザ名が間違っています");
        Edit1->SetFocus();
        break;

    case 3:
    	ShowMessage("パスワードが間違っています");
        MaskEdit1->SetFocus();
        break;

    case 4:
    	ShowMessage("パスワードが登録されていません");
        MaskEdit1->SetFocus();
        break;
	default:
		break;
    }
	switch(PassFlag)
	{
    case 1:
    case 2:
    case 3:
    case 4:
		//前回のユーザー情報を復帰
		Form1->USER_COD = OLDUSER_COD;
		Form1->USER_NAM = OLDUSER_NAM;
		Form1->BUMO_COD = OLDBUMO_COD;
		Form1->BUMO_NAM = OLDBUMO_NAM;
        break;
	default:
    	// 初期化表示
    	Form1->PnlBumCode->Caption = Form1->BUMO_COD;
    	Form1->PnlBumName->Caption = Form1->BUMO_NAM;
    	Form1->PnlTanCode->Caption = IntToStr(Form1->USER_COD);
    	Form1->PnlTanName->Caption = Form1->USER_NAM;
		Close();
	}
}

//---------------------------------------------------------------------------
//パスワードのチェック
int __fastcall TForm9::PasswordCheck()
{
     AnsiString sBuf;

     //ユーザー名検索

     if ( Edit1->Text.IsEmpty() ) return(1);

     // Initial Query
     QueryUser->Close();
     QueryUser->SQL->Clear();

     // 問合せ実行(担当者コード)
     sBuf = "SELECT TANSYA, TANNAM, SZKBSY FROM SM12S WHERE TANSYA = ";
     sBuf += Edit1->Text;

     QueryUser->SQL->Add(sBuf);
     QueryUser->Open();
     QueryUser->Active = true;

     //担当者コード無いよ
     if ( QueryUser->Bof == true && QueryUser->Eof ) {
     //検索結果 ０件
        return(2);
     }


     Form1->USER_COD = StrToInt(QueryUser->FieldValues["TANSYA"]);
     Form1->USER_NAM = QueryUser->FieldValues["TANNAM"];
     Form1->BUMO_COD = QueryUser->FieldValues["SZKBSY"];


     //部署名検索
     // Initial Query
     QueryUser->Close();
     QueryUser->SQL->Clear();

     sBuf = "SELECT BSYCOD, BSYNAM FROM SM13S WHERE BSYCOD = '";

     sBuf += Form1->BUMO_COD + "'";


     QueryUser->SQL->Add(sBuf);
     QueryUser->Open();
     QueryUser->Active = true;

     if ( QueryUser->Bof == true && QueryUser->Eof ) {
     //検索結果 ０件
         Form1->BUMO_NAM = "";
     } else {
         Form1->BUMO_NAM = QueryUser->FieldValues["BSYNAM"];
     }

     //パスワードの検索
     // Initial Query
     QueryUser->Close();
     QueryUser->SQL->Clear();


     sBuf = "SELECT USRID, PASSWD FROM KM11 WHERE USRID = ";
     sBuf = sBuf + IntToStr(Form1->USER_COD);
     sBuf = sBuf + " and ukoymd<='" + FormatDateTime("yyyymmdd",Date()) +"'";   // 有効年月日の判断を追加

     QueryUser->SQL->Add(sBuf);
     QueryUser->Open();
     QueryUser->Active = true;

     if ( QueryUser->Bof == true && QueryUser->Eof ) {
     //検索結果 ０件
        return(4);
     }
     //パスワードの比較
     if ( MaskEdit1->Text != QueryUser->FieldValues["PASSWD"] ) {
        //パスワード間違っている
        return(3);
     }
     return(0);
}

//---------------------------------------------------------------------------
//フォームアクティブ時
void __fastcall TForm9::FormActivate(TObject *Sender)
{
    // 2003/05/13 A.Tamura追加
    MaskEdit1->Text = "01";
    Edit1->SetFocus();

}
//---------------------------------------------------------------------------
//フォーム作成時
void __fastcall TForm9::FormCreate(TObject *Sender)
{
    //Database1->Open();

}
//---------------------------------------------------------------------------




void __fastcall TForm9::FormKeyPress(TObject *Sender, char &Key)
{
     switch(Key){
         // 前項
         case VK_RETURN:
                Key = 0;
                break;
     }

}
//---------------------------------------------------------------------------

