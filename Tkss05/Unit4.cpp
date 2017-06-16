//---------------------------------------------------------------------------
//
//  Unit4.cpp
//    【出荷検査システム－製品規格マスター】
//    測定項目編集フォーム（TForm4クラス）のメンバ関数の定義
//
//  作成者
//    田村　敦司
//
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NumberEdit"
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
        : TForm(Owner)
{
}

//---------------------------------------------------------------------------
//
//  概要
//    OnCreateイベント	：Form4を作成したときに発生します。
//
//  機能説明
//    初期画面の状態を設定します。
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
void __fastcall TForm4::FormCreate(TObject *Sender)
{
    Pnl_KIKAKU_KIJYUN->Left = Pnl_KIKAKU_HANI->Left;
}

//---------------------------------------------------------------------------
//
//  概要
//    OnActivateイベント	：フォームがアクティブになったときに発生します。
//
//  機能説明
//    初期表示に必要なデータを設定します
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
void __fastcall TForm4::FormActivate(TObject *Sender)
{

    int			i, k;
    AnsiString	sBuf;


    // 品番
	Pnl_HINBAN->Caption = Form1->SGr_SOKUT->Cells[1][Form1->SGr_SOKUT->Row];

    // 測定項目（日本語）
    Edt_SKTKMK_JPN->Text = Form1->SGr_SOKUT->Cells[2][Form1->SGr_SOKUT->Row];

    // 項目名（英語）
    Edt_SKTKMK_ENG->Text = Form1->SGr_SOKUT->Cells[4][Form1->SGr_SOKUT->Row];

    // 測定項目サブ名称（日本語）
    Edt_SKTKMK_JPN_SUB->Text = Form1->SGr_SOKUT->Cells[3][Form1->SGr_SOKUT->Row];

    // 測定項目サブ名称（英語）
    Edt_SKTKMK_ENG_SUB->Text = Form1->SGr_SOKUT->Cells[16][Form1->SGr_SOKUT->Row];

    // 測定機器
    k = Form1->SGr_SOKUT->Cells[17][Form1->SGr_SOKUT->Row].ToIntDef(-1);
    if( k == -1 ){
	    Cmb_SKTKIKI->ItemIndex = 0;
    }
    else {
    	for( i = 0; i < Form1->iKIKI_Cnt; i++){
    		if( Form1->iKIKI[i] == k ){
			    Cmb_SKTKIKI->ItemIndex = i;
            	break;
        	}
    	}
    }

    // 単位
    Cmb_TANI->Text = Form1->SGr_SOKUT->Cells[5][Form1->SGr_SOKUT->Row];

	// 測定項目としての扱い
    switch( Form1->SGr_SOKUT->Cells[10][Form1->SGr_SOKUT->Row].ToIntDef(-1) ){
		case 0: Rdo_SKTKMK_OFF->Checked = true;
				break;
		case 1:
        default:Rdo_SKTKMK_ON->Checked = true;
          		break;
   	}

	// 特別項目としての扱い
    switch( Form1->SGr_SOKUT->Cells[11][Form1->SGr_SOKUT->Row].ToIntDef(-1) ){
		case 1: Rdo_TKBKMK_ON->Checked = true;
				break;
		case 0:
        default:Rdo_TKBKMK_OFF->Checked = true;
          		break;
   	}

	// 規格（指定方法）
    switch( Form1->SGr_SOKUT->Cells[18][Form1->SGr_SOKUT->Row].ToIntDef(-1) ){
		case 3: Rdo_KIKAKU_SHITEI_MOJI->Checked = true;
                Rdo_KIKAKU_SHITEI_MOJIClick( Rdo_KIKAKU_SHITEI_MOJI );
				break;
		case 2: Rdo_KIKAKU_SHITEI_KIJYUN->Checked = true;
                Rdo_KIKAKU_SHITEI_KIJYUNClick( Rdo_KIKAKU_SHITEI_KIJYUN );
				break;
		case 1:
        default:Rdo_KIKAKU_SHITEI_HANI->Checked = true;
                Rdo_KIKAKU_SHITEI_HANIClick( Rdo_KIKAKU_SHITEI_HANI );
          		break;
   	}

	// 規格（種類）
    switch( Form1->SGr_SOKUT->Cells[19][Form1->SGr_SOKUT->Row].ToIntDef(-1) ){
		case 3: Rdo_KIKAKU_SYURUI_MIN->Checked = true;
        		Rdo_KIKAKU_SYURUI_MINClick( Rdo_KIKAKU_SYURUI_MIN );
				break;
		case 2: Rdo_KIKAKU_SYURUI_MAX->Checked = true;
        		Rdo_KIKAKU_SYURUI_MAXClick( Rdo_KIKAKU_SYURUI_MAX );
				break;
		case 1:
        default:Rdo_KIKAKU_SYURUI_MINMAX->Checked = true;
        		Rdo_KIKAKU_SYURUI_MINMAXClick( Rdo_KIKAKU_SYURUI_MINMAX );
          		break;
   	}

	// 規格（上限下限値の印刷）
    switch( Form1->SGr_SOKUT->Cells[28][Form1->SGr_SOKUT->Row].ToIntDef(-1) ){
		case 0: Rdo_MANMIN_PRT_OFF->Checked = true;
				break;
		case 1:
        default:Rdo_MANMIN_PRT_ON->Checked = true;
          		break;
   	}

	// 規格（小数点以下桁数）
    Nmb_KIKAKU_DOUBLE->Text = IntToStr(Form1->SGr_SOKUT->Cells[20][Form1->SGr_SOKUT->Row].ToIntDef(0));

	// 規格値（範囲指定）
    Nmb_KIKAKU_HANI_MIN->FPos = Form1->SGr_SOKUT->Cells[20][Form1->SGr_SOKUT->Row].ToIntDef(0);
    Nmb_KIKAKU_HANI_MAX->FPos = Form1->SGr_SOKUT->Cells[20][Form1->SGr_SOKUT->Row].ToIntDef(0);
    Nmb_KIKAKU_HANI_MIN->Text = Form1->SGr_SOKUT->Cells[21][Form1->SGr_SOKUT->Row];
    if( Form1->SGr_SOKUT->Cells[18][Form1->SGr_SOKUT->Row].ToIntDef(-1) == 1 ){
	    Nmb_KIKAKU_HANI_MAX->Text = Form1->SGr_SOKUT->Cells[22][Form1->SGr_SOKUT->Row];
    }
    else {
	    Nmb_KIKAKU_HANI_MAX->Text = "0";
    }

	// 規格値（基準値指定）
    Nmb_KIKAKU_KIJYUN_MID->FPos = Form1->SGr_SOKUT->Cells[20][Form1->SGr_SOKUT->Row].ToIntDef(0);
    Nmb_KIKAKU_KIJYUN_MAX->FPos = Form1->SGr_SOKUT->Cells[20][Form1->SGr_SOKUT->Row].ToIntDef(0);
    Nmb_KIKAKU_KIJYUN_MIN->FPos = Form1->SGr_SOKUT->Cells[20][Form1->SGr_SOKUT->Row].ToIntDef(0);
    Nmb_KIKAKU_KIJYUN_MID->Text = Form1->SGr_SOKUT->Cells[21][Form1->SGr_SOKUT->Row];
    if( Form1->SGr_SOKUT->Cells[18][Form1->SGr_SOKUT->Row].ToIntDef(-1) == 2 ){
    	Nmb_KIKAKU_KIJYUN_MAX->Text = Form1->SGr_SOKUT->Cells[22][Form1->SGr_SOKUT->Row];
    	Nmb_KIKAKU_KIJYUN_MIN->Text = Form1->SGr_SOKUT->Cells[23][Form1->SGr_SOKUT->Row];
    }
    else {
    	Nmb_KIKAKU_KIJYUN_MAX->Text = "0";
    	Nmb_KIKAKU_KIJYUN_MIN->Text = "0";
    }

	// 規格値（文字指定）
    Edt_KIKAKU_STRING->Text = Form1->SGr_SOKUT->Cells[24][Form1->SGr_SOKUT->Row];

	// 測定値（値表現）
    switch( Form1->SGr_SOKUT->Cells[8][Form1->SGr_SOKUT->Row].ToIntDef(-1) ){
		case 3: Rdo_VALUE_TEXT->Checked = true;
				break;
		case 2: Rdo_VALUE_OK->Checked = true;
				break;
		case 1: Rdo_VALUE_KAKUDO->Checked = true;
				break;
		case 0:
        default:Rdo_VALUE_NORMAL->Checked = true;
          		break;
   	}

	// 測定値（小数点以下桁数）
    Nmb_VALUE_DOUBLE->Text = IntToStr(Form1->SGr_SOKUT->Cells[29][Form1->SGr_SOKUT->Row].ToIntDef(0));

	// 測定値（抜取ｎ数）
    Nmb_N->Text = IntToStr(Form1->SGr_SOKUT->Cells[7][Form1->SGr_SOKUT->Row].ToIntDef(2));

    // ラベルの色を設定します
    SetColor(Form1->SGr_SOKUT->Cells[15][Form1->SGr_SOKUT->Row].ToIntDef(2));

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ２：前項」ボタンを押した時の処理
//
//  機能説明
//    フォーカスを1つ前に移動します
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
void __fastcall TForm4::BtnF02Click(TObject *Sender)
{
	keybd_event(VK_SHIFT,0,0,0);
	keybd_event(VK_TAB,0,0,0);
	keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
	keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ３：次項」ボタンを押した時の処理
//
//  機能説明
//    フォーカスを1つ次に移動します
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
void __fastcall TForm4::BtnF03Click(TObject *Sender)
{
	keybd_event(VK_TAB,0,0,0);
	keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ８：設定」ボタンを押した時の処理
//
//  機能説明
//    修正した内容をメインフォームの測定項目Gridに設定します。
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
void __fastcall TForm4::BtnF08Click(TObject *Sender)
{

    AnsiString		sBuf;


    // 入力データのチェック
    if(Edt_SKTKMK_JPN->Text.IsEmpty()){
        MessageDlg("測定項目名を入力してください。", mtWarning
                          ,TMsgDlgButtons() << mbOK, 0);
        Edt_SKTKMK_JPN->SetFocus();
        return;
    }
    if( Rdo_KIKAKU_SHITEI_HANI->Checked && Rdo_KIKAKU_SYURUI_MINMAX->Checked ) {
        if( Nmb_KIKAKU_HANI_MIN->Text.ToIntDef(0) >
            Nmb_KIKAKU_HANI_MAX->Text.ToIntDef(0) ){
            MessageDlg("規格の範囲指定が正しくありません。", mtWarning
                              ,TMsgDlgButtons() << mbOK, 0);
            Nmb_KIKAKU_HANI_MIN->SetFocus();
            return;
        }
    }

    sBuf = Form1->Edt_DTKSHIN->Text;
	strcpy( Form1->tmpKSM02_DATA.DTKSHIN		,sBuf.c_str() );	// 代表得意先品番
    sBuf = "0";
	strcpy( Form1->tmpKSM02_DATA.REVCNT			,sBuf.c_str() );	// 改訂番号
    sBuf = Form1->SGr_SOKUT->Cells[13][Form1->SGr_SOKUT->Row];
	strcpy( Form1->tmpKSM02_DATA.UNQ_NO			,sBuf.c_str() );	// 明細NO
    sBuf = Form1->SGr_SOKUT->Cells[14][Form1->SGr_SOKUT->Row];
	strcpy( Form1->tmpKSM02_DATA.ORDER_NO		,sBuf.c_str() );	// 表示順
    sBuf = Form1->SGr_SOKUT->Cells[15][Form1->SGr_SOKUT->Row];
	strcpy( Form1->tmpKSM02_DATA.SKB_NO			,sBuf.c_str() );	// 識別NO
    sBuf = Pnl_HINBAN->Caption;
	strcpy( Form1->tmpKSM02_DATA.HINBAN_SK		,sBuf.c_str() );	// 品番
	sBuf = Form1->SGr_SOKUT->Cells[12][Form1->SGr_SOKUT->Row];
	strcpy( Form1->tmpKSM02_DATA.KOMK_NO		,sBuf.c_str() );	// 項目NO
	sBuf = Edt_SKTKMK_JPN->Text;
	strcpy( Form1->tmpKSM02_DATA.KOMK_NM		,sBuf.c_str() );	// 測定項目名称（日本語）
	sBuf = Edt_SKTKMK_ENG->Text;
	strcpy( Form1->tmpKSM02_DATA.KOMK_ENG		,sBuf.c_str() );	// 測定項目名称（英語）
	sBuf = Edt_SKTKMK_JPN_SUB->Text;
	strcpy( Form1->tmpKSM02_DATA.KOMK_SUB		,sBuf.c_str() );	// 測定項目サブ名称（日本語）
	sBuf = Edt_SKTKMK_ENG_SUB->Text;
	strcpy( Form1->tmpKSM02_DATA.KOMK_SUB_ENG	,sBuf.c_str() );	// 測定項目サブ名称（英語）
	sBuf = IntToStr(Form1->iKIKI[Cmb_SKTKIKI->ItemIndex]);
	strcpy( Form1->tmpKSM02_DATA.KIKI_NO		,sBuf.c_str() );	// 測定機器NO
	sBuf = Cmb_SKTKIKI->Text;
	strcpy( Form1->tmpKSM02_DATA.KIKI_NM		,sBuf.c_str() );	// 測定機器名称
	sBuf = Cmb_TANI->Text;
	strcpy( Form1->tmpKSM02_DATA.TANI			,sBuf.c_str() );	// 単位

    if( Rdo_KIKAKU_SHITEI_HANI->Checked ) {
		sBuf = Nmb_KIKAKU_HANI_MIN->Text;
		strcpy( Form1->tmpKSM02_DATA.KIKA_NUM1		,sBuf.c_str() );	// 規格値１
		sBuf = Nmb_KIKAKU_HANI_MAX->Text;
		strcpy( Form1->tmpKSM02_DATA.KIKA_NUM2		,sBuf.c_str() );	// 規格値２
		sBuf = "0";
		strcpy( Form1->tmpKSM02_DATA.KIKA_NUM3		,sBuf.c_str() );	// 規格値３
		sBuf = "";
		strcpy( Form1->tmpKSM02_DATA.KIKA_STR		,sBuf.c_str() );	// 規格値文字
		sBuf = "1";
    } else if( Rdo_KIKAKU_SHITEI_KIJYUN->Checked ) {
		sBuf = Nmb_KIKAKU_KIJYUN_MID->Text;
		strcpy( Form1->tmpKSM02_DATA.KIKA_NUM1		,sBuf.c_str() );	// 規格値１
		sBuf = Nmb_KIKAKU_KIJYUN_MAX->Text;
		strcpy( Form1->tmpKSM02_DATA.KIKA_NUM2		,sBuf.c_str() );	// 規格値２
		sBuf = Nmb_KIKAKU_KIJYUN_MIN->Text;
		strcpy( Form1->tmpKSM02_DATA.KIKA_NUM3		,sBuf.c_str() );	// 規格値３
		sBuf = "";
		strcpy( Form1->tmpKSM02_DATA.KIKA_STR		,sBuf.c_str() );	// 規格値文字
		sBuf = "2";
	} else {
		sBuf = "0";
		strcpy( Form1->tmpKSM02_DATA.KIKA_NUM1		,sBuf.c_str() );	// 規格値１
		strcpy( Form1->tmpKSM02_DATA.KIKA_NUM2		,sBuf.c_str() );	// 規格値２
		strcpy( Form1->tmpKSM02_DATA.KIKA_NUM3		,sBuf.c_str() );	// 規格値３
		sBuf = Edt_KIKAKU_STRING->Text;
		strcpy( Form1->tmpKSM02_DATA.KIKA_STR		,sBuf.c_str() );	// 規格値文字
		sBuf = "3";
    }
	strcpy( Form1->tmpKSM02_DATA.KIKA_TYPE		,sBuf.c_str() );	// 規格タイプ
    if( Rdo_KIKAKU_SYURUI_MINMAX->Checked )			sBuf = "1";
	else if( Rdo_KIKAKU_SYURUI_MAX->Checked )		sBuf = "2";
    else											sBuf = "3";
    strcpy( Form1->tmpKSM02_DATA.KIKA_KIND		,sBuf.c_str() );	// 規格種類
    sBuf = Nmb_KIKAKU_DOUBLE->Text;
	strcpy( Form1->tmpKSM02_DATA.KIKA_DECI		,sBuf.c_str() );	// 規格小数点以下桁数
    sBuf = Nmb_N->Text;
	strcpy( Form1->tmpKSM02_DATA.SOKU_SU		,sBuf.c_str() );	// 測定指示n数
    if( Rdo_SKTKMK_ON->Checked )			sBuf = "1";
	else									sBuf = "0";
	strcpy( Form1->tmpKSM02_DATA.SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
	if( Rdo_TKBKMK_ON->Checked )			sBuf = "1";
	else									sBuf = "0";
	strcpy( Form1->tmpKSM02_DATA.TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
	if( Rdo_MANMIN_PRT_ON->Checked )		sBuf = "1";
	else									sBuf = "0";
	strcpy( Form1->tmpKSM02_DATA.KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
	if( Rdo_VALUE_NORMAL->Checked )			sBuf = "0";
	else if( Rdo_VALUE_KAKUDO->Checked )	sBuf = "1";
	else if( Rdo_VALUE_OK->Checked )		sBuf = "2";
	else									sBuf = "3";
	strcpy( Form1->tmpKSM02_DATA.VALUE_TYPE		,sBuf.c_str() );	// 測定値表現
	sBuf = Nmb_VALUE_DOUBLE->Text;
	strcpy( Form1->tmpKSM02_DATA.VALUE_DECI		,sBuf.c_str() );	// 測定値小数点以下桁数


    // 修正後の値を元の画面に設定します
    Form1->SGr_SOKUT_GridLinePaste( Form1->SGr_SOKUT->Row, "1", true );

    // データ変更フラグの設定
    Form1->DataChange = 1;

    // 戻る
    BtnF12Click( BtnF12 );

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ１２：戻る」ボタンを押した時の処理
//
//  機能説明
//    このフォームを閉じます
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
void __fastcall TForm4::BtnF12Click(TObject *Sender)
{
    Close();

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：規格の指定方法「範囲指定」クリックしたときに発生します。
//
//  機能説明
//    関連するコントロールの有効／無効を制御します
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
void __fastcall TForm4::Rdo_KIKAKU_SHITEI_HANIClick(TObject *Sender)
{
    Pnl_KIKAKU_HANI->Visible   = true;
    Pnl_KIKAKU_KIJYUN->Visible = false;
    Pnl_KIKAKU_MOJI->Visible   = false;
    Pnl_SYURUI->Enabled        = true;
	Pnl_MANMIN_PRT->Enabled    = false;
    Nmb_KIKAKU_DOUBLE->Enabled = true;
    //Pnl_VALUE->Enabled         = true;
    Rdo_KIKAKU_SYURUI_MINMAX->Font->Color = clBlack;
    Rdo_KIKAKU_SYURUI_MAX->Font->Color    = clBlack;
    Rdo_KIKAKU_SYURUI_MIN->Font->Color    = clBlack;
	Rdo_MANMIN_PRT_ON->Font->Color        = clGray;
	Rdo_MANMIN_PRT_OFF->Font->Color       = clGray;
	Nmb_KIKAKU_DOUBLE->Font->Color        = clBlack;
    //Rdo_VALUE_NORMAL->Font->Color         = clBlack;
    //Rdo_VALUE_KAKUDO->Font->Color         = clBlack;
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：規格の指定方法「基準指定」クリックしたときに発生します。
//
//  機能説明
//    関連するコントロールの有効／無効を制御します
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
void __fastcall TForm4::Rdo_KIKAKU_SHITEI_KIJYUNClick(TObject *Sender)
{
    Pnl_KIKAKU_HANI->Visible   = false;
    Pnl_KIKAKU_KIJYUN->Visible = true;
    Pnl_KIKAKU_MOJI->Visible   = false;
    Pnl_SYURUI->Enabled        = true;
	Pnl_MANMIN_PRT->Enabled    = true;
    Nmb_KIKAKU_DOUBLE->Enabled = true;
    //Pnl_VALUE->Enabled         = true;
    Rdo_KIKAKU_SYURUI_MINMAX->Font->Color = clBlack;
    Rdo_KIKAKU_SYURUI_MAX->Font->Color    = clBlack;
    Rdo_KIKAKU_SYURUI_MIN->Font->Color    = clBlack;
	Rdo_MANMIN_PRT_ON->Font->Color        = clBlack;
	Rdo_MANMIN_PRT_OFF->Font->Color       = clBlack;
	Nmb_KIKAKU_DOUBLE->Font->Color        = clBlack;
    //Rdo_VALUE_NORMAL->Font->Color         = clBlack;
    //Rdo_VALUE_KAKUDO->Font->Color         = clBlack;
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：規格の指定方法「文字指定」クリックしたときに発生します。
//
//  機能説明
//    関連するコントロールの有効／無効を制御します
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
void __fastcall TForm4::Rdo_KIKAKU_SHITEI_MOJIClick(TObject *Sender)
{
    Pnl_KIKAKU_HANI->Visible   = false;
    Pnl_KIKAKU_KIJYUN->Visible = false;
    Pnl_KIKAKU_MOJI->Visible   = true;
    Pnl_SYURUI->Enabled        = false;
	Pnl_MANMIN_PRT->Enabled    = false;
    Nmb_KIKAKU_DOUBLE->Enabled = false;
    //Pnl_VALUE->Enabled         = false;
    Rdo_KIKAKU_SYURUI_MINMAX->Font->Color = clGray;
    Rdo_KIKAKU_SYURUI_MAX->Font->Color    = clGray;
    Rdo_KIKAKU_SYURUI_MIN->Font->Color    = clGray;
	Rdo_MANMIN_PRT_ON->Font->Color        = clGray;
	Rdo_MANMIN_PRT_OFF->Font->Color       = clGray;
	Nmb_KIKAKU_DOUBLE->Font->Color        = clGray;
    //Rdo_VALUE_NORMAL->Font->Color         = clGray;
    //Rdo_VALUE_KAKUDO->Font->Color         = clGray;
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：規格の種類「上限下限両方」クリックしたときに発生します。
//
//  機能説明
//    関連するコントロールの有効／無効を制御します
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
void __fastcall TForm4::Rdo_KIKAKU_SYURUI_MINMAXClick(TObject *Sender)
{
    Nmb_KIKAKU_HANI_MIN->Enabled	= true;
    Nmb_KIKAKU_HANI_MAX->Enabled	= true;
    Nmb_KIKAKU_KIJYUN_MIN->Enabled	= true;
    Nmb_KIKAKU_KIJYUN_MAX->Enabled	= true;
    Nmb_KIKAKU_HANI_MIN->Color		= clWindow;
    Nmb_KIKAKU_HANI_MAX->Color		= clWindow;
    Nmb_KIKAKU_KIJYUN_MIN->Color	= clWindow;
    Nmb_KIKAKU_KIJYUN_MAX->Color	= clWindow;
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：規格の種類「上限のみ」クリックしたときに発生します。
//
//  機能説明
//    関連するコントロールの有効／無効を制御します
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
void __fastcall TForm4::Rdo_KIKAKU_SYURUI_MAXClick(TObject *Sender)
{
    Nmb_KIKAKU_HANI_MIN->Enabled	= false;
    Nmb_KIKAKU_HANI_MAX->Enabled	= true;
    Nmb_KIKAKU_KIJYUN_MIN->Enabled	= false;
    Nmb_KIKAKU_KIJYUN_MAX->Enabled	= true;
    Nmb_KIKAKU_HANI_MIN->Color		= clBtnFace;
    Nmb_KIKAKU_HANI_MAX->Color		= clWindow;
    Nmb_KIKAKU_KIJYUN_MIN->Color	= clBtnFace;
    Nmb_KIKAKU_KIJYUN_MAX->Color	= clWindow;
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：規格の種類「下限のみ」クリックしたときに発生します。
//
//  機能説明
//    関連するコントロールの有効／無効を制御します
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
void __fastcall TForm4::Rdo_KIKAKU_SYURUI_MINClick(TObject *Sender)
{
    Nmb_KIKAKU_HANI_MIN->Enabled	= true;
    Nmb_KIKAKU_HANI_MAX->Enabled	= false;
    Nmb_KIKAKU_KIJYUN_MIN->Enabled	= true;
    Nmb_KIKAKU_KIJYUN_MAX->Enabled	= false;
    Nmb_KIKAKU_HANI_MIN->Color		= clWindow;
    Nmb_KIKAKU_HANI_MAX->Color		= clBtnFace;
    Nmb_KIKAKU_KIJYUN_MIN->Color	= clWindow;
    Nmb_KIKAKU_KIJYUN_MAX->Color	= clBtnFace;
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：測定値の値表現「整数」クリックしたときに発生します。
//
//  機能説明
//    関連するコントロールの有効／無効を制御します
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
void __fastcall TForm4::Rdo_VALUE_NORMALClick(TObject *Sender)
{
    Nmb_VALUE_DOUBLE->Enabled     = true;
    Nmb_VALUE_DOUBLE->Font->Color = clBlack;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：測定値の値表現「角度」クリックしたときに発生します。
//
//  機能説明
//    関連するコントロールの有効／無効を制御します
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
void __fastcall TForm4::Rdo_VALUE_KAKUDOClick(TObject *Sender)
{
    Nmb_VALUE_DOUBLE->Enabled     = true;
    Nmb_VALUE_DOUBLE->Font->Color = clBlack;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：測定値の値表現「良/否」クリックしたときに発生します。
//
//  機能説明
//    関連するコントロールの有効／無効を制御します
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
void __fastcall TForm4::Rdo_VALUE_OKClick(TObject *Sender)
{
    Nmb_VALUE_DOUBLE->Enabled     = false;
    Nmb_VALUE_DOUBLE->Font->Color = clGray;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：測定値の値表現「文字」クリックしたときに発生します。
//
//  機能説明
//    関連するコントロールの有効／無効を制御します
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
void __fastcall TForm4::Rdo_VALUE_TEXTClick(TObject *Sender)
{
    Nmb_VALUE_DOUBLE->Enabled     = false;
    Nmb_VALUE_DOUBLE->Font->Color = clGray;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnKeyDownイベント	：ユーザーが任意のキーを押すと発生します
//
//  機能説明
//    ファンクションキー、Enterキーによりボタンを選択します
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
void __fastcall TForm4::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     switch(Key)
     {
         case VK_F2:  BtnF02Click(BtnF02);		break;
         case VK_F3:  BtnF03Click(BtnF03);		break;
         case VK_F8:  BtnF08Click(BtnF08);		break;
         case VK_F12: BtnF12Click(Sender);		break;
         case VK_RETURN:
                // Enter
                if( Nmb_N->Focused() ){
                    BtnF08->SetFocus();
                    break;
                }
                else {
                	keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }

     }

}

//---------------------------------------------------------------------------
//
//  概要
//    OnExitイベント	：入力フォーカスが別のコントロールへ移ったときに発生します。
//
//  機能説明
//    規格の小数点以下桁数と測定値の小数点以下桁数に同じ値を設定します。
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
void __fastcall TForm4::Nmb_KIKAKU_DOUBLEExit(TObject *Sender)
{

	TNumberEdit *ne = (TNumberEdit *)Sender;

    // 値の範囲チェックを行ないます
    if( ne->Value > 5 || ne->Value < 0 ){
    	MessageDlg("小数点以下桁数の指定範囲は、0～5以内です。", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        if( ne->Value > 5 ){
            if( ne->Name == "Nmb_KIKAKU_DOUBLE" ){
        		Nmb_KIKAKU_DOUBLE->Text = "5";
			}
        	else {
        		Nmb_VALUE_DOUBLE->Text = "5";
        	}
        }
        else {
            if( ne->Name == "Nmb_KIKAKU_DOUBLE" ){
        		Nmb_KIKAKU_DOUBLE->Text = "0";
			}
        	else {
        		Nmb_VALUE_DOUBLE->Text = "0";
        	}
        }
    }

    // 「規格値」値を変更したら「測定値」の値を同じ値に変更します
    if( ne->Name == "Nmb_KIKAKU_DOUBLE" ){
    	AnsiString	sBuf;

        // 「測定値」の小数点以下桁数は＋１します。
        sBuf = Nmb_KIKAKU_DOUBLE->Text;
        if( sBuf.ToIntDef(0) >= 0 && sBuf.ToIntDef(0) < 5 ){
        	sBuf = AnsiString(sBuf.ToIntDef(0) + 1);
        }
		Nmb_VALUE_DOUBLE->Text = sBuf;

		Nmb_KIKAKU_HANI_MIN->FPos = Nmb_KIKAKU_DOUBLE->Value;
		Nmb_KIKAKU_HANI_MAX->FPos = Nmb_KIKAKU_DOUBLE->Value;
		Nmb_KIKAKU_KIJYUN_MAX->FPos = Nmb_KIKAKU_DOUBLE->Value;
		Nmb_KIKAKU_KIJYUN_MID->FPos = Nmb_KIKAKU_DOUBLE->Value;
		Nmb_KIKAKU_KIJYUN_MIN->FPos = Nmb_KIKAKU_DOUBLE->Value;
    	Nmb_KIKAKU_HANI_MIN->Text = Nmb_KIKAKU_HANI_MIN->Text;
    	Nmb_KIKAKU_HANI_MAX->Text = Nmb_KIKAKU_HANI_MAX->Text;
    	Nmb_KIKAKU_KIJYUN_MAX->Text = Nmb_KIKAKU_KIJYUN_MAX->Text;
    	Nmb_KIKAKU_KIJYUN_MID->Text = Nmb_KIKAKU_KIJYUN_MID->Text;
    	Nmb_KIKAKU_KIJYUN_MIN->Text = Nmb_KIKAKU_KIJYUN_MIN->Text;
    }

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：ラベルの色を設定します。
//
//  機能説明
//    ラベルの色を設定します。
//
//  パラメタ説明
//    int iSKB_NO		：識別NO
//                        1 = 素材検査項目（黄色）
//                        2 = 出荷検査項目（水色）
//                        3 = 材料証明項目（紫色）
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm4::SetColor( int iSKB_NO )
{

	TColor		iColor;

    switch( iSKB_NO ){
    	case 1: // 素材検査項目
        		iColor = (TColor)0x00D2FFFF;
                break;
        case 2: // 出荷検査項目
        		iColor = (TColor)0x00FFEEDD;
                break;

        case 3: // 材料証明項目
        		iColor = (TColor)0x00FFE1FD;
                break;
    }

    //色変更
	Pnl_t01->Color = iColor;
	Pnl_t02->Color = iColor;
	Pnl_t03->Color = iColor;
	Pnl_t04->Color = iColor;
	Pnl_t05->Color = iColor;
	Pnl_t06->Color = iColor;
	Pnl_t07->Color = iColor;
	Pnl_t08->Color = iColor;
	Pnl_t09->Color = iColor;
	Pnl_t10->Color = iColor;
	Pnl_t11->Color = iColor;
	Pnl_t12->Color = iColor;
	Pnl_t13->Color = iColor;
	Pnl_t14->Color = iColor;
	Pnl_t15->Color = iColor;
	Pnl_t16->Color = iColor;
	Pnl_t17->Color = iColor;
	Pnl_t18->Color = iColor;
	Pnl_t19->Color = iColor;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnChangeイベント	：編集コントロールのテキストに変更が加えられたときに発生します。
//
//  機能説明
//    入力文字(シングルコーテーション、半角カンマ)のチェックを行ないます。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    シングルコーテーションはＤＢ登録時にエラーが発生する
//    ので全角のシングルコーテーションに変換します
//
//---------------------------------------------------------------------------
void __fastcall TForm4::Edt_ALLChange(TObject *Sender)
{
	Form1->Edt_ALLChange( Sender );
}


