//---------------------------------------------------------------------------
//
//  Unit2.cpp
//    【出荷検査システム－メインメニュー】
//    パスワード入力フォーム（TForm2クラス）のメンバ関数の定義
//
//  作成者
//    高瀬　恵利
//
//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdlib.h>

#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include <DBTables.hpp>
#include <winbase.h>
#include <shellapi.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}

//---------------------------------------------------------------------------
//
//  概要
//    OnKeyDownイベント	：ユーザーが任意のキーを押すと発生します
//
//  機能説明
//    矢印キー、Enterキーを判定し次の動作を行ないます
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    WORD &Key			：キーコード
//    TShiftState Shift	：[Shift]，[Alt]，[Ctrl]キーを判定します
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm2::FormKeyDown(TObject *Sender, WORD &Key,
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
//
//  概要
//    OnClickイベント	：キャンセルボタンを押した時の処理
//
//  機能説明
//    パスワード入力画面を閉じます
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm2::CancleClick(TObject *Sender)
{
    Close();
    Form1->SetFocus();
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：ＯＫボタンを押した時の処理
//
//  機能説明
//    パスワードＯＫならプログラムを起動します
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm2::OkClick(TObject *Sender)
{
    int PassFlag;

    //ユーザー名、パスワードのチェック
    PassFlag = PasswordCheck();
    PGMStart(PassFlag);

}


//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：ＯＫボタンを押した時の後処理
//
//  機能説明
//    プログラムの起動や、エラーメッセージを表示します
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm2::PGMStart(int PassFlag)
{
    bool retDLL;
    char curpass[MAX_PATH];
    AnsiString str;
    SHELLEXECUTEINFO sei;


    switch(PassFlag){
        case 0:

            // 起動するプログラムへ引き渡す引数の作成
            strcpy(curpass , Form1->StartPATH);
            strcat(curpass, "\\");
            str = IntToStr(Form1->USER_COD) + "," + Form1->USER_NAM + "," + Form1->BUMO_COD + "," + Form1->BUMO_NAM;
            if( Form1->sDEBUG.Trim() != "" )	str = str + "," + Form1->sDEBUG.Trim() + ",";
            // 収録データプログラム起動
    	    ZeroMemory( &sei, sizeof(sei) );
    	    sei.cbSize = sizeof(sei);
    	    sei.fMask = SEE_MASK_NOCLOSEPROCESS;
    	    sei.hwnd = Form1->Handle;
    	    sei.lpVerb = "open";
    	    sei.lpFile = Form1->StartFileName;
    	    sei.nShow = SW_SHOWNORMAL;
            sei.lpDirectory = curpass;
           	sei.lpParameters = str.c_str();
	        retDLL = ShellExecuteEx(&sei);
           	Close();
            Form1->SetFocus();
            break;

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

        default :
            break;

     }
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：パスワードのチェック
//
//  機能説明
//    入力されたユーザコードとパスワードのチェックを行ないます
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
int __fastcall TForm2::PasswordCheck()
{
     AnsiString sBuf;

     //ユーザー名検索

     if ( Edit1->Text.IsEmpty() ) return(1);

	 Form1->USER_COD = 0;
	 Form1->USER_NAM = "";
	 Form1->BUMO_COD = "";
	 Form1->BUMO_NAM = "";

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ実行
     sBuf = "SELECT TANSYA, TANNAM, SZKBSY FROM SM12S WHERE  TANSYA = ";
     sBuf += Edit1->Text;

     Query1->SQL->Add(sBuf);
     Query1->Open();
     Query1->Active = true;

     if ( Query1->Bof == true && Query1->Eof ) {
     //検索結果 ０件
        return(2);
     }

     Form1->USER_COD = StrToInt(Query1->FieldValues["TANSYA"]);
     Form1->USER_NAM = Query1->FieldValues["TANNAM"];
     Form1->BUMO_COD = Query1->FieldValues["SZKBSY"];

     //部署名検索
     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     sBuf = "SELECT BSYCOD, BSYNAM FROM SM13S WHERE BSYCOD = '";
     sBuf += Form1->BUMO_COD + "'";

     Query1->SQL->Add(sBuf);
     Query1->Open();
     Query1->Active = true;

     if ( Query1->Bof == true && Query1->Eof ) {
     //検索結果 ０件
         Form1->BUMO_NAM = "";
     } else {
         Form1->BUMO_NAM = Query1->FieldValues["BSYNAM"];
     }

     //パスワードの検索
     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     sBuf = "SELECT USRID, PASSWD FROM KM11 WHERE USRID = ";
     sBuf = sBuf + IntToStr(Form1->USER_COD);
     sBuf = sBuf + " and ukoymd<='" + FormatDateTime("yyyymmdd",Date()) +"'";   // 有効年月日の判断を追加

     Query1->SQL->Add(sBuf);
     Query1->Open();
     Query1->Active = true;

     if ( Query1->Bof == true && Query1->Eof ) {
     //検索結果 ０件
        return(4);
     }
     //パスワードの比較
     if ( MaskEdit1->Text != Query1->FieldValues["PASSWD"] ) {
        //パスワード間違っている
        return(3);
     }
     return(0);
}

//---------------------------------------------------------------------------
//
//  概要
//    OnActivateイベント	：フォームがアクティブになったときに発生します。
//
//  機能説明
//    最初のフォーカス設定を行ないます
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm2::FormActivate(TObject *Sender)
{
     Edit1->SetFocus();
}

//---------------------------------------------------------------------------
//
//  概要
//    OnCreateイベント	：Form2を作成したときに発生します。
//
//  機能説明
//    データベースを初期化します。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    フォームが作成されるときイベントが以下の順序で発生します。
//    OnCreate→OnShow→OnActivate→OnPaint
//
//---------------------------------------------------------------------------
void __fastcall TForm2::FormCreate(TObject *Sender)
{
    Database1->Open();
}


//---------------------------------------------------------------------------
//
//  概要
//    OnKeyPressイベント：単一の文字キーを押したときに発生します。
//
//  機能説明
//    RETURNコードをクリアーします
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    char &Key			：キーコード
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm2::FormKeyPress(TObject *Sender, char &Key)
{
     switch(Key){
         // 前項
         case VK_RETURN:
                Key = 0;
                break;
     }

}


