//---------------------------------------------------------------------------
//
//  Unit1.cpp
//    【出荷検査システム－製品規格マスター】
//    メインフォーム（TForm1クラス）のメンバ関数の定義
//
//  作成者
//    田村　敦司
//
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
//
//  概要
//    OnCreateイベント	：Form1を作成したときに発生します。
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
void __fastcall TForm1::FormCreate(TObject *Sender)
{

    // データベース初期化
    Database1->Open();

	// グリッドの初期化（上）
	SGr_List->ColWidths[0] = 33;
	SGr_List->ColWidths[1] = 45;
	SGr_List->ColWidths[2] = 180;
	SGr_List->ColWidths[3] = 173;
	SGr_List->ColWidths[4] = 130;
	SGr_List->ColWidths[5] = 130;
	SGr_List->ColWidths[6] = 150;
	SGr_List->ColWidths[7] = 31;
	SGr_List->ColWidths[8] = 80;
	SGr_List->ColWidths[9] = 31;
	SGr_List->ColWidths[10] = 0;
	SGr_List->ColWidths[11] = 0;
	SGr_List->ColWidths[12] = 0;
	SGr_List->ColWidths[13] = 0;
	SGr_List->ColWidths[14] = 0;
	SGr_List->ColWidths[15] = 0;
	SGr_List->ColWidths[16] = 0;
	SGr_List->ColWidths[17] = 0;
	SGr_List->ColWidths[18] = 0;
	SGr_List->ColWidths[19] = 0;
	SGr_List->ColWidths[20] = 0;
	SGr_List->ColWidths[20] = 0;
	SGr_List->ColWidths[21] = 0;
	SGr_List->ColWidths[22] = 0;
	SGr_List->ColWidths[23] = 0;
	SGr_List->ColWidths[24] = 0;
	SGr_List->ColWidths[25] = 0;
	SGr_List->ColWidths[26] = 0;
	SGr_List->ColWidths[27] = 0;
	SGr_List->ColWidths[28] = 0;
	SGr_List->ColWidths[29] = 0;
	SGr_List->ColWidths[30] = 0;
	SGr_List->ColWidths[31] = 0;
	SGr_List->ColWidths[32] = 0;

	SGr_List->Cells[0][0] = " NO";
	SGr_List->Cells[1][0] = "得意先";
	SGr_List->Cells[2][0] = "得意先品番";
	SGr_List->Cells[3][0] = "素材用品番";
	SGr_List->Cells[4][0] = "自社品番";
	SGr_List->Cells[5][0] = "品　種";
	SGr_List->Cells[6][0] = "品　名";
	SGr_List->Cells[7][0] = "項数";
	SGr_List->Cells[8][0] = "登録日";
	SGr_List->Cells[9][0] = "改訂";

	// グリッドの初期化（下）
	SGr_SOKUT->ColWidths[0] = 18;
	SGr_SOKUT->ColWidths[1] = 130;
	SGr_SOKUT->ColWidths[2] = 175;
	SGr_SOKUT->ColWidths[3] = 45;
	SGr_SOKUT->ColWidths[4] = 105;
	SGr_SOKUT->ColWidths[5] = 60;
	SGr_SOKUT->ColWidths[6] = 140;
	SGr_SOKUT->ColWidths[7] = 25;
	SGr_SOKUT->ColWidths[8] = 55;
	SGr_SOKUT->ColWidths[9] = 102;
	SGr_SOKUT->ColWidths[10]= 30;
	SGr_SOKUT->ColWidths[11]= 30;
	SGr_SOKUT->ColWidths[12]= 0;
	SGr_SOKUT->ColWidths[13]= 0;
	SGr_SOKUT->ColWidths[14]= 0;
	SGr_SOKUT->ColWidths[15]= 0;
	SGr_SOKUT->ColWidths[16]= 0;
	SGr_SOKUT->ColWidths[17]= 0;
	SGr_SOKUT->ColWidths[18]= 0;
	SGr_SOKUT->ColWidths[19]= 0;
	SGr_SOKUT->ColWidths[20]= 0;
	SGr_SOKUT->ColWidths[20]= 0;
	SGr_SOKUT->ColWidths[21]= 0;
	SGr_SOKUT->ColWidths[22]= 0;
	SGr_SOKUT->ColWidths[23]= 0;
	SGr_SOKUT->ColWidths[24]= 0;
	SGr_SOKUT->ColWidths[25]= 0;
	SGr_SOKUT->ColWidths[26]= 0;
	SGr_SOKUT->ColWidths[27]= 0;
	SGr_SOKUT->ColWidths[28]= 0;
	SGr_SOKUT->ColWidths[29]= 0;
	SGr_SOKUT->ColWidths[30]= 0;
    /* デバッグ時のGridサイズ
    int		i;
    for( i=1; i<=30; i++ ){
		SGr_SOKUT->ColWidths[i]= 30;
    }
    SGr_SOKUT->Options << goColSizing;
    */

	SGr_SOKUT->Cells[0][0] = "NO";
	SGr_SOKUT->Cells[1][0] = "品　番";
	SGr_SOKUT->Cells[2][0] = "測定項目";
	SGr_SOKUT->Cells[3][0] = "SB名称";      // 素材から２品番（２層）選択する必要があるので必要です。
	SGr_SOKUT->Cells[4][0] = "名称(English)";
	SGr_SOKUT->Cells[5][0] = "単位";
	SGr_SOKUT->Cells[6][0] = "規　格";
	SGr_SOKUT->Cells[7][0] = "n数";
	SGr_SOKUT->Cells[8][0] = "値表現";
	SGr_SOKUT->Cells[9][0] = "測定機器";
	SGr_SOKUT->Cells[10][0]= "測定";
	SGr_SOKUT->Cells[11][0]= "特別";

    // Grid用フォントの作成
    LogFont.lfHeight = 10;
    LogFont.lfWidth = 0;
    LogFont.lfEscapement = 0;
    LogFont.lfOrientation = 0;
    LogFont.lfWeight = FW_NORMAL;
    LogFont.lfItalic = 0;
    LogFont.lfUnderline = 0;
    LogFont.lfStrikeOut = 0;
    LogFont.lfCharSet = SHIFTJIS_CHARSET;
    LogFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
    LogFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    LogFont.lfQuality = DEFAULT_QUALITY;
    LogFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
    strcpy( LogFont.lfFaceName, "ＭＳ ゴシック" );
    MyFont = CreateFontIndirect( &LogFont );

    // データ変更フラグの初期化
    DataChange = 0;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnActivateイベント	：フォームがアクティブになったときに発生します。
//
//  機能説明
//    初期表示に必要なデータを検索します
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
void __fastcall TForm1::FormActivate(TObject *Sender)
{

    int		iRow;
    AnsiString	sBuf;

    //----------------------------------------------
    // 検査成績書タイトル部出力情報の検索

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // 問合せ実行（検査成績書タイトル項目マスターの件数取得）
    sBuf = "SELECT COUNT(*) AS TITLE_NUM FROM KSM21";

    Query1->SQL->Add(sBuf);
    Query1->Open();
    Query1->Active = true;

    if( !Query1->Eof ){
        iTITLE_Cnt = Query1->FieldValues["TITLE_NUM"];
    }
    else {
        iTITLE_Cnt = 50;
    }

    // メモリの確保（検査成績書タイトル項目マスターの件数分）
    hMemTITLE = GlobalAlloc( GHND, sizeof(int) * iTITLE_Cnt );
    if( hMemTITLE == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        SBr1->Update();
        Beep();
        return;
    }
    iTITLE = (int *)GlobalLock(hMemTITLE);
    if( hMemTITLE == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        SBr1->Update();
        Beep();
        return;
    }

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // 問合せ実行（検査成績書タイトル項目マスター）
    sBuf = "SELECT KMK_NO, KMK_NM_JPN, KMK_NM_ENG FROM KSM21 ORDER BY ORDER_NO";

    Query1->SQL->Add(sBuf);
    Query1->Open();
    Query1->Active = true;

    iRow = 0;
    Clb_OUT_TITLE->Clear();
    while( !Query1->Eof ){

        // タイトル名をチェックリストボックスに追加
        sBuf  = Query1->FieldValues["KMK_NM_JPN"];
        if( !VarIsNull(Query1->FieldValues["KMK_NM_ENG"]) ){
        	sBuf += "(" + AnsiString(Query1->FieldValues["KMK_NM_ENG"]) + ")";
        }
        Clb_OUT_TITLE->Items->Add(sBuf);

        // タイトル項目Noを記憶（配列番号は、チェックリストボックスのItemインデックス）
        iTITLE[iRow] = Query1->FieldValues["KMK_NO"];
        iRow++;

        // カーソルを次にセットする
        Query1->Next();
    }


    //----------------------------------------------
    // 測定機器項目マスターの検索

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// 問合せ実行（測定機器項目マスターの件数取得）
	sBuf = "SELECT COUNT(*) AS KIKI_NUM FROM KSM14";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	if( !Query1->Eof ){
        iKIKI_Cnt = Query1->FieldValues["KIKI_NUM"];
    }
    else {
        iKIKI_Cnt = 50;
    }

    // メモリの確保（測定機器項目マスターの件数分）
    hMemKIKI = GlobalAlloc( GHND, sizeof(int) * iKIKI_Cnt );
    if( hMemKIKI == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        SBr1->Update();
        Beep();
        return;
    }
    iKIKI = (int *)GlobalLock(hMemKIKI);
    if( hMemKIKI == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        SBr1->Update();
        Beep();
        return;
    }

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// 問合せ実行（測定機器項目マスター）
	sBuf = "SELECT KIKI_NO, KIKI_NM FROM KSM14 ORDER BY ORDER_NO";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

    iRow = 0;
    Form2->Cmb_SKTKIKI->Clear();
    Form3->Cmb_SKTKIKI->Clear();
    Form4->Cmb_SKTKIKI->Clear();
	while( !Query1->Eof ){

        // 機器名をコンボボックスに追加
		sBuf = Query1->FieldValues["KIKI_NM"];
        Form2->Cmb_SKTKIKI->Items->Add(sBuf);
        Form3->Cmb_SKTKIKI->Items->Add(sBuf);
        Form4->Cmb_SKTKIKI->Items->Add(sBuf);

        // 機器Noを記憶（配列番号は、コンボボックスのItemインデックス）
        iKIKI[iRow] = Query1->FieldValues["KIKI_NO"];
        iRow++;

		// カーソルを次にセットする
		Query1->Next();
    }


    //----------------------------------------------
    // 単位マスターの検索

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// 問合せ実行（単位マスター）
	sBuf = "SELECT TANI FROM KSM92 ORDER BY ORDER_NO";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

    Form2->Cmb_TANI->Clear();
    Form3->Cmb_TANI->Clear();
    Form4->Cmb_TANI->Clear();
	while( !Query1->Eof ){

        // 機器名をコンボボックスに追加
		sBuf = Query1->FieldValues["TANI"];
        Form2->Cmb_TANI->Items->Add(sBuf);
        Form3->Cmb_TANI->Items->Add(sBuf);
        Form4->Cmb_TANI->Items->Add(sBuf);

		// カーソルを次にセットする
		Query1->Next();
    }


    // データ保存フラグを初期化
    DataSave = false;

    // 最初の一行目を選択します
    SGr_ListSelectCell( SGr_List, 1, 1, true );

    Edt_COD2->SetFocus();
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「出荷追加」ボタンを押した時の処理
//
//  機能説明
//    出荷検査測定項目選択画面の表示
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
void __fastcall TForm1::Btn_ADD_SKClick(TObject *Sender)
{

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

    // 出荷検査測定項目選択画面の表示
    Form2->ShowModal();
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「出荷追加」ボタンを押した時の処理
//
//  機能説明
//    素材検査測定項目選択画面の表示
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
void __fastcall TForm1::Btn_ADD_SZClick(TObject *Sender)
{

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

    // 素材検査測定項目選択画面の表示
    if( Lbx_DTKSHIN_SZ->Items->Count > 0 ){
    	Form3->ShowModal();
	}
    else {
    	MessageDlg("素材用品番が指定されていません。", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	Btn_DTKSHIN_SZ_ADD->SetFocus();
    }
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「編集」ボタンを押した時の処理
//
//  機能説明
//    選択された検査測定項目に対して編集画面を表示します
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
void __fastcall TForm1::Btn_EDITClick(TObject *Sender)
{
	TGridRect	myRect;


    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

	// 複数選択される場合があるので、１行選択として選択しなおします
    myRect.Left				= SGr_SOKUT->Selection.Left;
	myRect.Top				= iRowSelTop;
	myRect.Right			= SGr_SOKUT->Selection.Right;
	myRect.Bottom			= iRowSelTop;
    SGr_SOKUT->Selection	= myRect;
	SGr_SOKUT->Row = iRowSelTop;
	SGr_SOKUT->SetFocus();
    SGr_SOKUTClick( SGr_SOKUT );

    // 編集対象の行かチェックします。（Space行は処理中止）
    if( SGr_SOKUT->Cells[15][SGr_SOKUT->Row].ToIntDef(9) == 9 ){
        SBr1->Panels->Items[0]->Text = "編集できません。";
        SBr1->Update();
        return;
    }

    // 測定項目編集画面の表示
    Form4->ShowModal();
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：下StringGridでマウスの左ボタンをダブルクリックしたときに発生します。
//
//  機能説明
//    「編集」ボタン処理を呼び出します
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
void __fastcall TForm1::SGr_SOKUTDblClick(TObject *Sender)
{

    // 履歴が最新のもののみ実行する
    if( SGr_List->Cells[9][SGr_List->Row].ToIntDef(0) == 0 ) {

    	// 測定項目編集画面の表示
    	Btn_EDITClick( Btn_EDIT );
    }

}

//---------------------------------------------------------------------------
//
//  概要
//    OnResizeイベント	：コントロールのサイズが変更された直後に発生します。
//
//  機能説明
//    Panelのサイズに合わせて上StringGridのサイズも変更します
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
void __fastcall TForm1::Pnl_ListResize(TObject *Sender)
{
    int iBMarg;

    // 親ラベルから見た各コントロールの下端余白
    iBMarg = 5;

    // 検索リスト
	if( SGr_List->Top < Pnl_List->Height &&
        Pnl_List->Height - SGr_List->Top - iBMarg > 0 ){
		SGr_List->Height = Pnl_List->Height - SGr_List->Top - iBMarg;
	} else{
		SGr_List->Height = 0;
	}

}

//---------------------------------------------------------------------------
//
//  概要
//    OnResizeイベント	：コントロールのサイズが変更された直後に発生します。
//
//  機能説明
//    Panelのサイズに合わせて下StringGridのサイズも変更します
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
void __fastcall TForm1::Pnl_SOKUTResize(TObject *Sender)
{
    int iBMarg;

    // 親ラベルから見た各コントロールの下端余白
    iBMarg = 2;


    // 検索リスト
	if( SGr_SOKUT->Top < Pnl_SOKUT->Height &&
        Pnl_SOKUT->Height - SGr_SOKUT->Top - iBMarg > 0 ){
		SGr_SOKUT->Height = Pnl_SOKUT->Height - SGr_SOKUT->Top - iBMarg;
	} else{
		SGr_SOKUT->Height = 0;
	}

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ１：一覧検索」ボタンを押した時の処理
//
//  機能説明
//    一覧検索画面（Form5）を表示します
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
void __fastcall TForm1::BtnF01Click(TObject *Sender)
{
    if( !BtnF01->Enabled )    return;
    // 一覧検索画面の表示
    Form5->ShowModal();
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ２：前項」ボタンを押した時の処理
//
//  機能説明
//    選択行を1つ上に移動します
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
void __fastcall TForm1::BtnF02Click(TObject *Sender)
{
    if( !BtnF02->Enabled )    return;

    // 画面上StringGrid
    if( SGr_List->Focused() ){
	    if( SGr_List->Row > 0 ){
    	    SGr_List->Row -= 1;
    	    SGr_List->SetFocus();
    	}
    }

    // 画面下StringGrid
    if( SGr_SOKUT->Focused() ){
	    if( SGr_SOKUT->Row > 0 ){
    	    SGr_SOKUT->Row -= 1;
    	    SGr_SOKUT->SetFocus();
    	}
    }
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ３：次項」ボタンを押した時の処理
//
//  機能説明
//    選択行を1つ下に移動します
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
void __fastcall TForm1::BtnF03Click(TObject *Sender)
{
    if( !BtnF03->Enabled )    return;

    // 画面上StringGrid
    if( ( SGr_List->RowCount - 1 ) > SGr_List->Row ){
        SGr_List->Row += 1;
        SGr_List->SetFocus();
    }

    // 画面下StringGrid
    if( ( SGr_SOKUT->RowCount - 1 ) > SGr_SOKUT->Row ){
        SGr_SOKUT->Row += 1;
        SGr_SOKUT->SetFocus();
    }
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ５：画面印刷」ボタンを押した時の処理
//
//  機能説明
//    メインフォームを印刷します。
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
void __fastcall TForm1::BtnF05Click(TObject *Sender)
{
	if( !BtnF05->Enabled ) return;

    ////////////////////
    // 画面印刷
	Form1->Print();

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ７：検索」ボタンを押した時の処理
//
//  機能説明
//    指定された得意先品番、自社品番などの情報を元に検索処理を開始します
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
void __fastcall TForm1::BtnF07Click(TObject *Sender)
{
    int i;
    int cnt;
    int iRow;
    AnsiString sBuf;

    if( !BtnF07->Enabled )    return;

    // データ選択変更前にデータ変更フラグのチェックを行ないます。
    if( DataChange > 0 ){
        sBuf  = "データが変更されています。変更内容を破棄しますか？";
        sBuf += "\n[は　い] 変更内容を破棄します。（変更前のデータに戻ります）";
        sBuf += "\n[いいえ] 変更処理を続行します。（[F8:新規登録]又は[F9:修正]で変更内容を確定してください。）";
		if( MessageDlg( sBuf, mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo ){
			// 新しい選択を取りやめます
			return;
		}
        DataChange = 0;
	}

     // データを変更したかどうかのフラグチェック
     if( DataSave ){
         switch( MessageDlg( "データが編集されています。\n保存しますか？",
                            mtConfirmation, mbYesNoCancel, 0) ){
             // 「Yes」      保存
             case mrYes:
	             BtnF11Click(Sender);
                 break;
             // 「No」       変更を破棄
             case mrNo:
                 if( Database1->InTransaction == True )  Database1->Rollback();
                 break;
             // 「Cancel」   キャンセル
             case mrCancel:
                 return;
         }
     }
     else{
         if( Database1->InTransaction == True )  Database1->Rollback();
     }

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "検索中です．．．しばらくお待ち下さい。";
     SBr1->Update();


     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ実行
     sBuf  = "select KSM01.DTKSHIN, KSM01.REVCNT, KSM01.HINBAN, KSM01.DTKSCOD,";
     sBuf += " KSM01.DTKSNAM, KSM01.ZISNAM, KSM01.HINMEI,";
     sBuf += " KSM01.DTKSHIN1_SZ, KSM01.DTKSHIN2_SZ, KSM01.DTKSHIN3_SZ,";
     sBuf += " KSM01.DTKSHIN4_SZ, KSM01.DTKSHIN5_SZ, KSM01.DTKSHIN6_SZ,";
     sBuf += " KSM01.LOT_LINK_SZ, KSM01.SOKUTEI_NUM,";
     sBuf += " KSM01.OUT_TITLE1, KSM01.OUT_TITLE2, KSM01.OUT_TITLE3,";
     sBuf += " KSM01.OUT_TITLE4, KSM01.OUT_TITLE5, KSM01.OUT_TITLE6,";
     sBuf += " KSM01.OUT_TITLE7, KSM01.OUT_TITLE8,";
     sBuf += " KSM01.X_OUT, KSM01.MEMO,";
     sBuf += " KSM01.ADDYMD, KSM01.ADDTIM, KSM01.UPDYMD,";
     sBuf += " KSM01.UPDTIM, KSM01.UPDCHR, KSM01.UPDCNT, SM12S.TANNAM";
     sBuf += " FROM KSM01 LEFT JOIN SM12S ON KSM01.UPDCHR = SM12S.TANSYA";

     if( Edt_COD1->Text != "" || Edt_COD2->Text != "" || Edt_COD3->Text != "" || Edt_COD4->Text != "" ){
         sBuf += " where";
         cnt = 0;
         if( Edt_COD1->Text != "" ){
             // 得意先コード
             sBuf += " DTKSCOD like '";
             sBuf += Edt_COD1->Text ;
             sBuf += "%'";
             cnt += 1;
         }
         if( Edt_COD2->Text != "" ){
             // 得意先品番
             if( cnt >= 1 ) sBuf += " and";
             sBuf += " DTKSHIN like '";
             sBuf += Edt_COD2->Text ;
             sBuf += "%'";
             cnt += 1;
         }
         if( Edt_COD3->Text != "" ){
             // 自社品番
             if( cnt >= 1 ) sBuf += " and";
             sBuf += " HINBAN like '";
             sBuf += Edt_COD3->Text ;
             sBuf += "%'";
             cnt += 1;
         }
         if( Edt_COD4->Text != "" ){
             // 材質名称
             if( cnt >= 1 ) sBuf += " and";
             sBuf += " ZISNAM like '";
             sBuf += Edt_COD4->Text ;
             sBuf += "%'";
             cnt += 1;
         }
         //履歴を表示するか？
         if ( Cbx_RIREKI->Checked == false) {
            if( cnt >= 1 ) sBuf += " and";
            sBuf += " REVCNT = 0";
         }

     } else {

         //履歴を表示するか？
         if ( Cbx_RIREKI->Checked == false) {
            sBuf += " where";
            sBuf += " REVCNT = 0";
         }

     }


     sBuf = sBuf + " order by DTKSCOD, DTKSHIN, REVCNT";
     Query1->SQL->Add(sBuf);
     Query1->Open();
     Query1->Active = true;

     SGr_List->Tag = 1;

     iRow = 1;
     while( !Query1->Eof ){

          // グリッドの最大行数が超えていないかチェックする
          if( iRow >= SGr_List->RowCount ){
              SGr_List->RowCount = iRow + 1;
          }

          // グリッドにデータをセットします。

          // NO
          sBuf = iRow ;
          SGr_List->Cells[0][iRow] = AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;
          sBuf = iRow + 1;

          // 得意先コード
          if( VarIsNull(Query1->FieldValues["DTKSCOD"]) ){
		      sBuf = "";
          } else{
              sBuf = Query1->FieldValues["DTKSCOD"];
          }
          SGr_List->Cells[1][iRow] = sBuf;

          // 得意先品番
          sBuf = Query1->FieldValues["DTKSHIN"];
          SGr_List->Cells[2][iRow] = sBuf;

          // 素材用品番１
          if( VarIsNull(Query1->FieldValues["DTKSHIN1_SZ"]) ){
		      sBuf = "";
          } else{
              sBuf = Query1->FieldValues["DTKSHIN1_SZ"];
          }
          SGr_List->Cells[3][iRow] = sBuf;

          // 自社品番
          if( VarIsNull(Query1->FieldValues["HINBAN"]) ){
		      sBuf = "";
          } else{
              sBuf = Query1->FieldValues["HINBAN"];
          }
          SGr_List->Cells[4][iRow] = sBuf;

          // 品種
          if( VarIsNull(Query1->FieldValues["ZISNAM"]) ){
		      sBuf = "";
          } else{
              sBuf = Query1->FieldValues["ZISNAM"];
          }
          SGr_List->Cells[5][iRow] = sBuf;

          // 品名
          if( VarIsNull(Query1->FieldValues["HINMEI"]) ){
		      sBuf = "";
          } else{
              sBuf = Query1->FieldValues["HINMEI"];
          }
          SGr_List->Cells[6][iRow] = sBuf;

          // 項目数
          if( VarIsNull(Query1->FieldValues["SOKUTEI_NUM"]) ){
		      sBuf = "";
          } else{
              sBuf = Query1->FieldValues["SOKUTEI_NUM"];
          }
          SGr_List->Cells[7][iRow] = sBuf;

          // 登録日
          if( VarIsNull(Query1->FieldValues["ADDYMD"]) ){
		      sBuf = "";
          } else{
              sBuf = Query1->FieldValues["ADDYMD"];
          }
          SGr_List->Cells[8][iRow] = sBuf;

          // 改訂
          sBuf = Query1->FieldValues["REVCNT"];
          SGr_List->Cells[9][iRow] = sBuf;

          // 得意先名称
          if( VarIsNull(Query1->FieldValues["DTKSNAM"]) ){
		      sBuf = "";
          } else{
              sBuf = Query1->FieldValues["DTKSNAM"];
          }
          SGr_List->Cells[10][iRow] = sBuf;

          // 素材用品番２
          if( VarIsNull(Query1->FieldValues["DTKSHIN2_SZ"]) ){
		      sBuf = "";
          } else{
              sBuf = Query1->FieldValues["DTKSHIN2_SZ"];
          }
          SGr_List->Cells[11][iRow] = sBuf;

          // 素材用品番３
          if( VarIsNull(Query1->FieldValues["DTKSHIN3_SZ"]) ){
		      sBuf = "";
          } else{
              sBuf = Query1->FieldValues["DTKSHIN3_SZ"];
          }
          SGr_List->Cells[12][iRow] = sBuf;

          // 素材用品番４
          if( VarIsNull(Query1->FieldValues["DTKSHIN4_SZ"]) ){
		      sBuf = "";
          } else{
              sBuf = Query1->FieldValues["DTKSHIN4_SZ"];
          }
          SGr_List->Cells[13][iRow] = sBuf;

          // 素材用品番５
          if( VarIsNull(Query1->FieldValues["DTKSHIN5_SZ"]) ){
		      sBuf = "";
          } else{
              sBuf = Query1->FieldValues["DTKSHIN5_SZ"];
          }
          SGr_List->Cells[14][iRow] = sBuf;

          // 素材用品番６
          if( VarIsNull(Query1->FieldValues["DTKSHIN6_SZ"]) ){
		      sBuf = "";
          } else{
              sBuf = Query1->FieldValues["DTKSHIN6_SZ"];
          }
          SGr_List->Cells[15][iRow] = sBuf;

          // 素材用ロットのリンク
          sBuf = Query1->FieldValues["LOT_LINK_SZ"];
          SGr_List->Cells[16][iRow] = sBuf;

          // 成績書タイトル出力項目１
          sBuf = Query1->FieldValues["OUT_TITLE1"];
          SGr_List->Cells[17][iRow] = sBuf;

          // 成績書タイトル出力項目２
          sBuf = Query1->FieldValues["OUT_TITLE2"];
          SGr_List->Cells[18][iRow] = sBuf;

          // 成績書タイトル出力項目３
          sBuf = Query1->FieldValues["OUT_TITLE3"];
          SGr_List->Cells[19][iRow] = sBuf;

          // 成績書タイトル出力項目４
          sBuf = Query1->FieldValues["OUT_TITLE4"];
          SGr_List->Cells[20][iRow] = sBuf;

          // 成績書タイトル出力項目５
          sBuf = Query1->FieldValues["OUT_TITLE5"];
          SGr_List->Cells[21][iRow] = sBuf;

          // 成績書タイトル出力項目６
          sBuf = Query1->FieldValues["OUT_TITLE6"];
          SGr_List->Cells[22][iRow] = sBuf;

          // 成績書タイトル出力項目７
          sBuf = Query1->FieldValues["OUT_TITLE7"];
          SGr_List->Cells[23][iRow] = sBuf;

          // 成績書タイトル出力項目８
          sBuf = Query1->FieldValues["OUT_TITLE8"];
          SGr_List->Cells[24][iRow] = sBuf;

          // Ｘの出力
          sBuf = Query1->FieldValues["X_OUT"];
          SGr_List->Cells[25][iRow] = sBuf;

          // 備考
          if( VarIsNull(Query1->FieldValues["MEMO"]) ){
		      sBuf = "";
          } else{
              sBuf = Query1->FieldValues["MEMO"];
          }
          SGr_List->Cells[26][iRow] = sBuf;

          // 更新日
          if( VarIsNull(Query1->FieldValues["UPDYMD"]) ){
		      sBuf = "";
          } else{
              sBuf = Query1->FieldValues["UPDYMD"];
          }
          SGr_List->Cells[27][iRow] = sBuf;

          //登録時間
          sBuf = Query1->FieldValues["ADDTIM"];
          SGr_List->Cells[28][iRow] =  sBuf;

          //更新時間
          sBuf = Query1->FieldValues["UPDTIM"];
          SGr_List->Cells[29][iRow] = sBuf;

          //更新回数
          sBuf = Query1->FieldValues["UPDCNT"];
          SGr_List->Cells[30][iRow] = sBuf;

          //更新者コード
          sBuf = Query1->FieldValues["UPDCHR"];
          SGr_List->Cells[31][iRow] = sBuf;

          //更新者
          if( VarIsNull(Query1->FieldValues["TANNAM"]) ){
              sBuf = "";
          } else{
              sBuf = Query1->FieldValues["TANNAM"];
          }
          SGr_List->Cells[32][iRow] = sBuf;

          // カーソルを次にセットする
          Query1->Next();

          iRow += 1;
     }

     SGr_List->Tag = 0;

     // 最下行をクリアー
     SGr_List->RowCount = iRow + 1;
     for( i = 0; i < SGr_List->ColCount; i++) {
         SGr_List->Cells[i][iRow]  = "";
     }

     // グリッドを選択
     //SGr_List->Row = 1;
     SGr_ListSelectCell( SGr_List, 1, 1, true );
     SGr_List->SetFocus();

     // 新しいトランザクションを開始
     if( Database1->InTransaction == false ){
         Database1->StartTransaction();
         DataSave = false;
     }

     // ボタンの初期化
     BtnF01->Enabled = false;

     // ステータスメッセージ
     sBuf = FormatFloat( "検索結果 0件です。", iRow - 1 );
     SBr1->Panels->Items[0]->Text = sBuf;
     SBr1->Update();

     // 履歴検索の状況を保存します
     if( Cbx_RIREKI->Checked == true ){
         Cbx_RIREKI->Tag = 1;
     }
     else{
         Cbx_RIREKI->Tag = 0;
     }

    // データ変更フラグの初期化
    DataChange = 0;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ８：新規登録」ボタンを押した時の処理
//
//  機能説明
//    画面下に入力された項目をテーブル（KSM01,KSM02）に登録します
//    上StringGridに一行追加します
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
void __fastcall TForm1::BtnF08Click(TObject *Sender)
{
     int		i, k, m;
     int		iRow;
     AnsiString sBuf;

     if( !BtnF08->Enabled )    return;

     if( Edt_DTKSHIN->Text == "" ){
        // ステータスメッセージ
        Beep();
		MessageDlg("必須項目を入力して下さい。", mtWarning,
			TMsgDlgButtons() << mbOK , 0);
        //SBr1->Panels->Items[0]->Text = "必須項目を入力して下さい。";
        //SBr1->Update();
        //Beep();
        return;
     }


	 // StringGrid内に登録された測定項目の規格値のチェックを行ないます
     m = 0;
     for( i = 1; i < SGr_SOKUT->RowCount - 1; i++) {
     	k = SGr_SOKUT->Cells[15][i].ToIntDef(-1);
		if( k == 1 || k == 2 || k == 3 ){
            m++ ;
			// 1:素材検査項目、2:出荷検査項目、3:材料証明項目の場合は、チェック対象です。
			k = SGr_SOKUT->Cells[18][i].ToIntDef(-1);
			if( k == 1 ){
				// 1:範囲指定の場合は、チェック対象です。
				k = SGr_SOKUT->Cells[19][i].ToIntDef(-1);
				if( k == 1 ){
					// 1:上限下限両方の場合は、チェック対象です。

                    double	Val1, Val2;
					try {
						Val1 = SGr_SOKUT->Cells[21][i].ToDouble();
						Val2 = SGr_SOKUT->Cells[22][i].ToDouble();
					} catch(EConvertError& e) {
						Val1 = 0;
						Val2 = 0;
					} catch(Exception& e) {
						Val1 = 0;
						Val2 = 0;
					}
					if( Val1 >= Val2 ){
                    	// 規格の範囲指定が不正な場合は、エラーとします
						Beep();
                        SGr_SOKUT->Row = i;
						MessageDlg("規格の範囲指定が正しくありません。", mtWarning,
							TMsgDlgButtons() << mbOK , 0);
						//SBr1->Panels->Items[0]->Text = "規格の範囲指定が正しくありません。";
						//SBr1->Update();
						//Beep();
						return;
					}
				}
        	}

            // 2003/06/02 A.Tamura
			// n数が0以下（不正）な場合は、エラーとします
			if( SGr_SOKUT->Cells[7][i].ToIntDef(0) < 1 ){
				Beep();
                SGr_SOKUT->Row = i;
				MessageDlg("ｎ数は、1以上を指定して下さい。", mtWarning,
					TMsgDlgButtons() << mbOK , 0);
				return;
            }
		}
	 }
	 if( m == 0 ){
       	 // 測定項目がない時は、エラーとします
		 Beep();
		 MessageDlg("測定項目を指定して下さい。", mtWarning,
			 TMsgDlgButtons() << mbOK , 0);
		 return;
	 }

     // 測定項目の重複が無いかどうかチェックします
     for( i = 1; i < SGr_SOKUT->RowCount - 1; i++) {
     	k = SGr_SOKUT->Cells[15][i].ToIntDef(-1);
		if( k == 1 || k == 2 || k == 3 ){
            for( m = 1; m < SGr_SOKUT->RowCount - 1; m++) {
               // 比較するのもが同じ時は、次の項目へ
               if( m == i ) continue;
     	       k = SGr_SOKUT->Cells[15][m].ToIntDef(-1);
		       if( k == 1 || k == 2 || k == 3 ){

                   // 測定区分NOが1とそれ以外の時は別項目として扱います
     	           if( (SGr_SOKUT->Cells[15][i].Trim() == "1" &&
                        SGr_SOKUT->Cells[15][m].Trim() != "1" ) ||
                       (SGr_SOKUT->Cells[15][i].Trim() != "1" &&
                        SGr_SOKUT->Cells[15][m].Trim() == "1" ) ){
                       continue;
                   }

                   // 品番or素材用品番			→ 使用しない 2002/10/23 A.Tamura
                   // 測定項目名称（日本語）
                   // 測定項目サブ名称（日本語）
                   // 項目NO					→ 使用しない 2002/10/20 A.Tamura
                   // 測定機器NO				→ 使用しない 2002/10/20 A.Tamura
                   // 単位						← 追加します 2002/10/20 A.Tamura
                   // が同じものは登録できないようにします
     	           if( //SGr_SOKUT->Cells[ 1][i].Trim() == SGr_SOKUT->Cells[ 1][m].Trim() &&
                       SGr_SOKUT->Cells[ 2][i].Trim() == SGr_SOKUT->Cells[ 2][m].Trim() &&
                       SGr_SOKUT->Cells[ 3][i].Trim() == SGr_SOKUT->Cells[ 3][m].Trim() &&
                       //SGr_SOKUT->Cells[12][i].Trim() == SGr_SOKUT->Cells[12][m].Trim() &&
                       //SGr_SOKUT->Cells[17][i].Trim() == SGr_SOKUT->Cells[17][m].Trim() ){
                       SGr_SOKUT->Cells[ 5][i].Trim() == SGr_SOKUT->Cells[ 5][m].Trim() ){
					   Beep();
                       SGr_SOKUT->Row = m;
					   MessageDlg("測定項目が重複しています。変更して下さい。", mtWarning,
					       TMsgDlgButtons() << mbOK , 0);
                       return;
                   }
               }
            }
        }
     }

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "新規登録中です．．．しばらくお待ち下さい。";
     SBr1->Update();

     // データをバッファに格納します。
     sBuf = Edt_DTKSHIN->Text;
     if( sBuf == "" )  sBuf = " ";
     strcpy( tmpKSM01_DATA.DTKSHIN		,sBuf.c_str() );		// 得意先品番
     sBuf = "0";
     strcpy( tmpKSM01_DATA.REVCNT		,sBuf.c_str() );		// 改訂番号
     sBuf = Edt_HINBAN->Text;
     if( sBuf == "" )  sBuf = " ";
     strcpy( tmpKSM01_DATA.HINBAN		,sBuf.c_str() );		// 自社品番
     sBuf = Edt_DTKSCOD->Text;
     if( sBuf == "" )  sBuf = " ";
     strcpy( tmpKSM01_DATA.DTKSCOD		,sBuf.c_str() );		// 得意先コード
     sBuf = Edt_DTKSNAM->Text;
     if( sBuf == "" )  sBuf = " ";
     strcpy( tmpKSM01_DATA.DTKSNAM		,sBuf.c_str() );		// 得意先名称
     sBuf = Edt_ZISNAM->Text;
     if( sBuf == "" )  sBuf = " ";
     strcpy( tmpKSM01_DATA.ZISNAM		,sBuf.c_str() );		// 材質名称（品種）
     sBuf = Edt_HINMEI->Text;
     if( sBuf == "" )  sBuf = " ";
     strcpy( tmpKSM01_DATA.HINMEI		,sBuf.c_str() );		// 品名
     sBuf = " ";
     strcpy( tmpKSM01_DATA.DTKSHIN1_SZ	,sBuf.c_str() );		// 素材用得意先品番１
     strcpy( tmpKSM01_DATA.DTKSHIN2_SZ	,sBuf.c_str() );		// 素材用得意先品番２
     strcpy( tmpKSM01_DATA.DTKSHIN3_SZ	,sBuf.c_str() );		// 素材用得意先品番３
     strcpy( tmpKSM01_DATA.DTKSHIN4_SZ	,sBuf.c_str() );		// 素材用得意先品番４
     strcpy( tmpKSM01_DATA.DTKSHIN5_SZ	,sBuf.c_str() );		// 素材用得意先品番５
     strcpy( tmpKSM01_DATA.DTKSHIN6_SZ	,sBuf.c_str() );		// 素材用得意先品番６
     for( i = 0; i < Lbx_DTKSHIN_SZ->Items->Count; i++ ){
         sBuf = Lbx_DTKSHIN_SZ->Items->Strings[i];
         if( sBuf == "" )  sBuf = " ";
         if( i == 0 )  strcpy( tmpKSM01_DATA.DTKSHIN1_SZ	,sBuf.c_str() );		// 素材用得意先品番１
         if( i == 1 )  strcpy( tmpKSM01_DATA.DTKSHIN2_SZ	,sBuf.c_str() );		// 素材用得意先品番２
         if( i == 2 )  strcpy( tmpKSM01_DATA.DTKSHIN3_SZ	,sBuf.c_str() );		// 素材用得意先品番３
         if( i == 3 )  strcpy( tmpKSM01_DATA.DTKSHIN4_SZ	,sBuf.c_str() );		// 素材用得意先品番４
         if( i == 4 )  strcpy( tmpKSM01_DATA.DTKSHIN5_SZ	,sBuf.c_str() );		// 素材用得意先品番５
         if( i == 5 )  strcpy( tmpKSM01_DATA.DTKSHIN6_SZ	,sBuf.c_str() );		// 素材用得意先品番６
     }
     if( Rdo_LOT_LINK_SZ_ON->Checked )		sBuf = "1";
     else									sBuf = "0";
     strcpy( tmpKSM01_DATA.LOT_LINK_SZ	,sBuf.c_str() );		// 素材用ロットのリンク
     sBuf = Pnl_SOKUTEI_NUM->Caption.Trim();
     if( sBuf == "" )  sBuf = " ";
     strcpy( tmpKSM01_DATA.SOKUTEI_NUM	,sBuf.c_str() );		// 測定項目数
     sBuf = "0";
     strcpy( tmpKSM01_DATA.OUT_TITLE1	,sBuf.c_str() );		// 成績書タイトル出力項目1
     strcpy( tmpKSM01_DATA.OUT_TITLE2	,sBuf.c_str() );		// 成績書タイトル出力項目2
     strcpy( tmpKSM01_DATA.OUT_TITLE3	,sBuf.c_str() );		// 成績書タイトル出力項目3
     strcpy( tmpKSM01_DATA.OUT_TITLE4	,sBuf.c_str() );		// 成績書タイトル出力項目4
     strcpy( tmpKSM01_DATA.OUT_TITLE5	,sBuf.c_str() );		// 成績書タイトル出力項目5
     strcpy( tmpKSM01_DATA.OUT_TITLE6	,sBuf.c_str() );		// 成績書タイトル出力項目6
     strcpy( tmpKSM01_DATA.OUT_TITLE7	,sBuf.c_str() );		// 成績書タイトル出力項目7
     strcpy( tmpKSM01_DATA.OUT_TITLE8	,sBuf.c_str() );		// 成績書タイトル出力項目8
     k = 0;
     for( i = 0; i < iTITLE_Cnt; i++){
         if( Clb_OUT_TITLE->Checked[i] == true ){
             sBuf = IntToStr(iTITLE[i]);
             if( k == 0 )  strcpy( tmpKSM01_DATA.OUT_TITLE1	,sBuf.c_str() );	// 成績書タイトル出力項目1
             if( k == 1 )  strcpy( tmpKSM01_DATA.OUT_TITLE2	,sBuf.c_str() );	// 成績書タイトル出力項目2
             if( k == 2 )  strcpy( tmpKSM01_DATA.OUT_TITLE3	,sBuf.c_str() );	// 成績書タイトル出力項目3
             if( k == 3 )  strcpy( tmpKSM01_DATA.OUT_TITLE4	,sBuf.c_str() );	// 成績書タイトル出力項目4
             if( k == 4 )  strcpy( tmpKSM01_DATA.OUT_TITLE5	,sBuf.c_str() );	// 成績書タイトル出力項目5
             if( k == 5 )  strcpy( tmpKSM01_DATA.OUT_TITLE6	,sBuf.c_str() );	// 成績書タイトル出力項目6
             if( k == 6 )  strcpy( tmpKSM01_DATA.OUT_TITLE7	,sBuf.c_str() );	// 成績書タイトル出力項目7
             if( k == 7 )  strcpy( tmpKSM01_DATA.OUT_TITLE8	,sBuf.c_str() );	// 成績書タイトル出力項目8
             k++;
         }
     }
     if( Rdo_XOUT_ON->Checked )		sBuf = "1";
     else							sBuf = "0";
     strcpy( tmpKSM01_DATA.X_OUT		,sBuf.c_str() );		// Ｘの出力
     sBuf = Edt_MEMO->Text;
     if( sBuf == "" )  sBuf = " ";
     strcpy( tmpKSM01_DATA.MEMO			,sBuf.c_str() );		// 備考
     sBuf = FormatDateTime("yyyymmdd",Date());
     strcpy( tmpKSM01_DATA.ADDYMD		,sBuf.c_str() );		// 登録日
     strcpy( tmpKSM01_DATA.UPDYMD		,sBuf.c_str() );		// 変更日
     sBuf = FormatDateTime("hhmm",TDateTime::CurrentTime());
     strcpy( tmpKSM01_DATA.ADDTIM		,sBuf.c_str() );		// 登録時間
     strcpy( tmpKSM01_DATA.UPDTIM		,sBuf.c_str() );		// 変更時間
     sBuf = IntToStr(USER_COD);
     strcpy( tmpKSM01_DATA.UPDCHR		,sBuf.c_str() );		// 更新者（コード）
     sBuf = USER_NAM;
     strcpy( tmpKSM01_DATA.UPDNAM		,sBuf.c_str() );		// 更新者（名称）
     sBuf = "0";
     strcpy( tmpKSM01_DATA.UPDCNT		,sBuf.c_str() );		// 更新回数

     // AddData(KSM01)
     if( AddData(0) == False ){
        return;
     }

     // AddData(KSM02)
     if( AddData_Details(0) == False ){
        return;
     }

     // 新規登録する行番号を設定します
     iRow = SGr_List->RowCount - 1;

     // 一行増やす
     SGr_List->RowCount = SGr_List->RowCount + 1;

     // 行Noを付ける
     sBuf = IntToStr(SGr_List->RowCount-2);
     SGr_List->Cells[0][SGr_List->RowCount-2] = AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;
     // 最下行をクリアー
     for( k = 0; k < SGr_List->ColCount; k++) {
         SGr_List->Cells[k][SGr_List->RowCount-1] = "";
     }

     // 新規データ行以下の行をずらします
     for( i = SGr_List->RowCount - 2; i > iRow; i--) {
         for( k = 1; k < SGr_List->ColCount; k++) {
             SGr_List->Cells[k][i] = SGr_List->Cells[k][i-1];
         }
     }

	 // 新規データをSGr_Listに表示
     // グリッドにデータをセットします。
     SGr_ListLinePaste( iRow );

     // データ変更フラグの初期化
     DataChange = 0;

     // 新しい行を選択
     SGr_List->Row = iRow;
     SGr_List->SetFocus();
     SGr_ListSelectCell(SGr_List,1,iRow,true);

     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     // データを変更したフラグ
     DataSave = true;

     // ボタンの初期化
     BtnF11->Enabled = true;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ９：修正」ボタンを押した時の処理
//
//  機能説明
//    上StringGridで選択されたデータに対して画面下に入力された項目に更新します
//    テーブル（KSM01,KSM02）を更新します
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
void __fastcall TForm1::BtnF09Click(TObject *Sender)
{
     int		i, k, m;
     int		iRow;
     AnsiString sBuf;

     if( !BtnF09->Enabled )    return;

     if( SGr_List->Cells[2][SGr_List->Row] == "" ){
        // ステータスメッセージ
        Beep();
		MessageDlg("修正対象ではありません。", mtWarning,
			TMsgDlgButtons() << mbOK , 0);
        //SBr1->Panels->Items[0]->Text = "修正対象ではありません。";
        //SBr1->Update();
        //Beep();
        return;
     }

	 // StringGrid内に登録された測定項目の規格値のチェックを行ないます
     m = 0;
     for( i = 1; i < SGr_SOKUT->RowCount - 1; i++) {
     	k = SGr_SOKUT->Cells[15][i].ToIntDef(-1);
		if( k == 1 || k == 2 || k == 3 ){
            m++;
			// 1:素材検査項目、2:出荷検査項目、3:材料証明項目の場合は、チェック対象です。
			k = SGr_SOKUT->Cells[18][i].ToIntDef(-1);
			if( k == 1 ){
				// 1:範囲指定の場合は、チェック対象です。
				k = SGr_SOKUT->Cells[19][i].ToIntDef(-1);
				if( k == 1 ){
					// 1:上限下限両方の場合は、チェック対象です。

                    double	Val1, Val2;
					try {
						Val1 = SGr_SOKUT->Cells[21][i].ToDouble();
						Val2 = SGr_SOKUT->Cells[22][i].ToDouble();
					} catch(EConvertError& e) {
						Val1 = 0;
						Val2 = 0;
					} catch(Exception& e) {
						Val1 = 0;
						Val2 = 0;
					}
					if( Val1 >= Val2 ){
                    	// 規格の範囲指定が不正な場合は、エラーとします
						Beep();
                        SGr_SOKUT->Row = i;
						MessageDlg("規格の範囲指定が正しくありません。", mtWarning,
							TMsgDlgButtons() << mbOK , 0);
						return;
					}
				}
        	}
            // 2003/06/02 A.Tamura
			// n数が0以下（不正）な場合は、エラーとします
			if( SGr_SOKUT->Cells[7][i].ToIntDef(0) < 1 ){
				Beep();
                SGr_SOKUT->Row = i;
				MessageDlg("ｎ数は、1以上を指定して下さい。", mtWarning,
					TMsgDlgButtons() << mbOK , 0);
				return;
            }
		}
	 }
	 if( m == 0 ){
       	 // 測定項目がない時は、エラーとします
		 Beep();
		 MessageDlg("測定項目を指定して下さい。", mtWarning,
			 TMsgDlgButtons() << mbOK , 0);
		 return;
	 }

     // 測定項目の重複が無いかどうかチェックします
     for( i = 1; i < SGr_SOKUT->RowCount - 1; i++) {
     	k = SGr_SOKUT->Cells[15][i].ToIntDef(-1);
		if( k == 1 || k == 2 || k == 3 ){
            for( m = 1; m < SGr_SOKUT->RowCount - 1; m++) {
               // 比較するのもが同じ時は、次の項目へ
               if( m == i ) continue;
     	       k = SGr_SOKUT->Cells[15][m].ToIntDef(-1);
		       if( k == 1 || k == 2 || k == 3 ){
                   // 測定区分NOが1とそれ以外の時は別項目として扱います
     	           if( (SGr_SOKUT->Cells[15][i].Trim() == "1" &&
                        SGr_SOKUT->Cells[15][m].Trim() != "1" ) ||
                       (SGr_SOKUT->Cells[15][i].Trim() != "1" &&
                        SGr_SOKUT->Cells[15][m].Trim() == "1" ) ){
                       continue;
                   }

                   // 品番or素材用品番			→ 使用しない 2002/10/23 A.Tamura
                   // 測定項目名称（日本語）
                   // 測定項目サブ名称（日本語）
                   // 項目NO					→ 使用しない 2002/10/20 A.Tamura
                   // 測定機器NO				→ 使用しない 2002/10/20 A.Tamura
                   // 単位						← 追加します 2002/10/20 A.Tamura
                   // が同じものは登録できないようにします
     	           if( //SGr_SOKUT->Cells[ 1][i].Trim() == SGr_SOKUT->Cells[ 1][m].Trim() &&
                       SGr_SOKUT->Cells[ 2][i].Trim() == SGr_SOKUT->Cells[ 2][m].Trim() &&
                       SGr_SOKUT->Cells[ 3][i].Trim() == SGr_SOKUT->Cells[ 3][m].Trim() &&
                       //SGr_SOKUT->Cells[12][i].Trim() == SGr_SOKUT->Cells[12][m].Trim() &&
                       //SGr_SOKUT->Cells[17][i].Trim() == SGr_SOKUT->Cells[17][m].Trim() ){
                       SGr_SOKUT->Cells[ 5][i].Trim() == SGr_SOKUT->Cells[ 5][m].Trim() ){
					   Beep();
                       SGr_SOKUT->Row = m;
					   MessageDlg("測定項目が重複しています。変更して下さい。", mtWarning,
					       TMsgDlgButtons() << mbOK , 0);
                       return;
                   }
               }
            }
        }
     }

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "修正中です．．．しばらくお待ち下さい。";
     SBr1->Update();

     // データをバッファに格納します。
     sBuf = Edt_DTKSHIN->Text;
     if( sBuf == "" )  sBuf = " ";
     strcpy( tmpKSM01_DATA.DTKSHIN		,sBuf.c_str() );		// 得意先品番
     sBuf = "0";
     strcpy( tmpKSM01_DATA.REVCNT		,sBuf.c_str() );		// 改訂番号
     sBuf = Edt_HINBAN->Text;
     if( sBuf == "" )  sBuf = " ";
     strcpy( tmpKSM01_DATA.HINBAN		,sBuf.c_str() );		// 自社品番
     sBuf = Edt_DTKSCOD->Text;
     if( sBuf == "" )  sBuf = " ";
     strcpy( tmpKSM01_DATA.DTKSCOD		,sBuf.c_str() );		// 得意先コード
     sBuf = Edt_DTKSNAM->Text;
     if( sBuf == "" )  sBuf = " ";
     strcpy( tmpKSM01_DATA.DTKSNAM		,sBuf.c_str() );		// 得意先名称
     sBuf = Edt_ZISNAM->Text;
     if( sBuf == "" )  sBuf = " ";
     strcpy( tmpKSM01_DATA.ZISNAM		,sBuf.c_str() );		// 材質名称（品種）
     sBuf = Edt_HINMEI->Text;
     if( sBuf == "" )  sBuf = " ";
     strcpy( tmpKSM01_DATA.HINMEI		,sBuf.c_str() );		// 品名
     sBuf = " ";
     strcpy( tmpKSM01_DATA.DTKSHIN1_SZ	,sBuf.c_str() );		// 素材用得意先品番１
     strcpy( tmpKSM01_DATA.DTKSHIN2_SZ	,sBuf.c_str() );		// 素材用得意先品番２
     strcpy( tmpKSM01_DATA.DTKSHIN3_SZ	,sBuf.c_str() );		// 素材用得意先品番３
     strcpy( tmpKSM01_DATA.DTKSHIN4_SZ	,sBuf.c_str() );		// 素材用得意先品番４
     strcpy( tmpKSM01_DATA.DTKSHIN5_SZ	,sBuf.c_str() );		// 素材用得意先品番５
     strcpy( tmpKSM01_DATA.DTKSHIN6_SZ	,sBuf.c_str() );		// 素材用得意先品番６
     for( i = 0; i < Lbx_DTKSHIN_SZ->Items->Count; i++ ){
         sBuf = Lbx_DTKSHIN_SZ->Items->Strings[i];
         if( sBuf == "" )  sBuf = " ";
         if( i == 0 )  strcpy( tmpKSM01_DATA.DTKSHIN1_SZ	,sBuf.c_str() );		// 素材用得意先品番１
         if( i == 1 )  strcpy( tmpKSM01_DATA.DTKSHIN2_SZ	,sBuf.c_str() );		// 素材用得意先品番２
         if( i == 2 )  strcpy( tmpKSM01_DATA.DTKSHIN3_SZ	,sBuf.c_str() );		// 素材用得意先品番３
         if( i == 3 )  strcpy( tmpKSM01_DATA.DTKSHIN4_SZ	,sBuf.c_str() );		// 素材用得意先品番４
         if( i == 4 )  strcpy( tmpKSM01_DATA.DTKSHIN5_SZ	,sBuf.c_str() );		// 素材用得意先品番５
         if( i == 5 )  strcpy( tmpKSM01_DATA.DTKSHIN6_SZ	,sBuf.c_str() );		// 素材用得意先品番６
     }
     if( Rdo_LOT_LINK_SZ_ON->Checked )		sBuf = "1";
     else									sBuf = "0";
     strcpy( tmpKSM01_DATA.LOT_LINK_SZ	,sBuf.c_str() );		// 素材用ロットのリンク
     sBuf = Pnl_SOKUTEI_NUM->Caption.Trim();
     if( sBuf == "" )  sBuf = " ";
     strcpy( tmpKSM01_DATA.SOKUTEI_NUM	,sBuf.c_str() );		// 測定項目数
     sBuf = "0";
     strcpy( tmpKSM01_DATA.OUT_TITLE1	,sBuf.c_str() );		// 成績書タイトル出力項目1
     strcpy( tmpKSM01_DATA.OUT_TITLE2	,sBuf.c_str() );		// 成績書タイトル出力項目2
     strcpy( tmpKSM01_DATA.OUT_TITLE3	,sBuf.c_str() );		// 成績書タイトル出力項目3
     strcpy( tmpKSM01_DATA.OUT_TITLE4	,sBuf.c_str() );		// 成績書タイトル出力項目4
     strcpy( tmpKSM01_DATA.OUT_TITLE5	,sBuf.c_str() );		// 成績書タイトル出力項目5
     strcpy( tmpKSM01_DATA.OUT_TITLE6	,sBuf.c_str() );		// 成績書タイトル出力項目6
     strcpy( tmpKSM01_DATA.OUT_TITLE7	,sBuf.c_str() );		// 成績書タイトル出力項目7
     strcpy( tmpKSM01_DATA.OUT_TITLE8	,sBuf.c_str() );		// 成績書タイトル出力項目8
     k = 0;
     for( i = 0; i < iTITLE_Cnt; i++){
         if( Clb_OUT_TITLE->Checked[i] == true ){
             sBuf = IntToStr(iTITLE[i]);
             if( k == 0 )  strcpy( tmpKSM01_DATA.OUT_TITLE1	,sBuf.c_str() );	// 成績書タイトル出力項目1
             if( k == 1 )  strcpy( tmpKSM01_DATA.OUT_TITLE2	,sBuf.c_str() );	// 成績書タイトル出力項目2
             if( k == 2 )  strcpy( tmpKSM01_DATA.OUT_TITLE3	,sBuf.c_str() );	// 成績書タイトル出力項目3
             if( k == 3 )  strcpy( tmpKSM01_DATA.OUT_TITLE4	,sBuf.c_str() );	// 成績書タイトル出力項目4
             if( k == 4 )  strcpy( tmpKSM01_DATA.OUT_TITLE5	,sBuf.c_str() );	// 成績書タイトル出力項目5
             if( k == 5 )  strcpy( tmpKSM01_DATA.OUT_TITLE6	,sBuf.c_str() );	// 成績書タイトル出力項目6
             if( k == 6 )  strcpy( tmpKSM01_DATA.OUT_TITLE7	,sBuf.c_str() );	// 成績書タイトル出力項目7
             if( k == 7 )  strcpy( tmpKSM01_DATA.OUT_TITLE8	,sBuf.c_str() );	// 成績書タイトル出力項目8
             k++;
         }
     }
     if( Rdo_XOUT_ON->Checked )		sBuf = "1";
     else							sBuf = "0";
     strcpy( tmpKSM01_DATA.X_OUT		,sBuf.c_str() );		// Ｘの出力
     sBuf = Edt_MEMO->Text;
     if( sBuf == "" )  sBuf = " ";
     strcpy( tmpKSM01_DATA.MEMO			,sBuf.c_str() );		// 備考
     sBuf = FormatDateTime("yyyymmdd",Date());
     strcpy( tmpKSM01_DATA.ADDYMD		,sBuf.c_str() );		// 登録日
     strcpy( tmpKSM01_DATA.UPDYMD		,sBuf.c_str() );		// 変更日
     sBuf = FormatDateTime("hhmm",TDateTime::CurrentTime());
     strcpy( tmpKSM01_DATA.ADDTIM		,sBuf.c_str() );		// 登録時間
     strcpy( tmpKSM01_DATA.UPDTIM		,sBuf.c_str() );		// 変更時間
     sBuf = IntToStr(USER_COD);
     strcpy( tmpKSM01_DATA.UPDCHR		,sBuf.c_str() );		// 更新者（コード）
     sBuf = USER_NAM;
     strcpy( tmpKSM01_DATA.UPDNAM		,sBuf.c_str() );		// 更新者（名称）
     sBuf = IntToStr(StrToIntDef(PnlUPDCNT2->Caption, -1) + 1);
     strcpy( tmpKSM01_DATA.UPDCNT		,sBuf.c_str() );		// 更新回数

     // 修正元得意先品番の改訂番号更新
     UpdKaiteiNo(Edt_DTKSHIN->Text);

     // AddData(KSM01)
     if( AddData(1) == False ){
         return;
     }

     // AddData(KSM02)
     if( AddData_Details(1) == False ){
        return;
     }

     // 改訂データを最新にする（データの挿入）
     if ( Cbx_RIREKI->Tag == 1 ) {
         // 最新版を新しい行として追加します

         iRow = SGr_List->Row;

         // 一行増やす
         SGr_List->RowCount = SGr_List->RowCount + 1;

         // 行Noを付ける
         sBuf = IntToStr(SGr_List->RowCount-2);
         SGr_List->Cells[0][SGr_List->RowCount-2] = AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;
         // 最下行をクリアー
         for( k = 0; k < SGr_List->ColCount; k++) {
             SGr_List->Cells[k][SGr_List->RowCount-1] = "";
         }

         // 新規データ行以下の行をずらします
         for( i = SGr_List->RowCount - 2; i > iRow; i--) {
             for( k = 1; k < SGr_List->ColCount; k++) {
                 if( k == 9 && Edt_DTKSHIN->Text == SGr_List->Cells[2][i-1] ){
                     // 同じ得意先品番の時は、履歴となる分の改訂番号を＋１します
                     if( StrToIntDef(SGr_List->Cells[k][i-1],-1) == 0 ){
                         // 前回の最新データの場合、更新日を今日の日付に設定します
                     	 SGr_List->Cells[27][i-1] = FormatDateTime("yyyymmdd",Date());
                     }
                     SGr_List->Cells[k][i] = IntToStr( StrToIntDef(SGr_List->Cells[k][i-1],-1) + 1);
                 }
                 else {
                     SGr_List->Cells[k][i] = SGr_List->Cells[k][i-1];
                 }
             }
         }

         // 新規データをSGr_Listに表示
         // グリッドにデータをセットします。
         SGr_ListLinePaste( iRow );

     }
     else {
         // 修正元データを最新版として更新します

         iRow = SGr_List->Row;

	     // 新規データをSGr_Listに表示
         // グリッドにデータをセットします。
         SGr_ListLinePaste( iRow );
     }


     // データ変更フラグの初期化
     DataChange = 0;

     // 新しい行を選択
     SGr_List->Row = iRow;
     SGr_List->SetFocus();
     SGr_ListSelectCell(SGr_List,1,iRow,true);

     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     // データを変更したフラグ
     DataSave = true;

     // ボタンの初期化
     BtnF11->Enabled = true;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ１０：削除」ボタンを押した時の処理
//
//  機能説明
//    上StringGridで選択されたデータを削除します
//    テーブル（KSM01,KSM02）のレコードを削除します
//    上StringGridの選択行も削除します
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
void __fastcall TForm1::BtnF10Click(TObject *Sender)
{
     int		i, k, m;
     AnsiString sBuf;
     bool		iRIREKI_DEL;

     if( !BtnF10->Enabled )    return;

     if( SGr_List->Cells[1][SGr_List->Row] == "" ){
        // ステータスメッセージ
        Beep();
		MessageDlg("削除対象ではありません。", mtWarning,
			TMsgDlgButtons() << mbOK , 0);
        //SBr1->Panels->Items[0]->Text = "削除対象ではありません。";
        //SBr1->Update();
        //Beep();
        return;
     }

     if( MessageDlg( "指定した得意先品番を削除します。よろしいですか？",
         mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo ){
        return;
     }

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "削除中です．．．しばらくお待ち下さい。";
     SBr1->Update();

     // データをバッファに格納します。
     sBuf = SGr_List->Cells[2][SGr_List->Row];
     strcpy( tmpKSM01_DATA.DTKSHIN		,sBuf.c_str() );		// 得意先品番
     sBuf = SGr_List->Cells[9][SGr_List->Row];
     strcpy( tmpKSM01_DATA.REVCNT		,sBuf.c_str() );		// 改訂番号

     // DelData
     if( DelData( &iRIREKI_DEL ) == False ){
        return;
     }

     if( iRIREKI_DEL ){
     	 // 同じ得意先品番の履歴データも削除した場合

         // 削除する行の数を数えます
         m = 0;
         for( i = SGr_List->Row; i < (SGr_List->RowCount - 1); i++) {
             if( SGr_List->Cells[2][SGr_List->Row] == SGr_List->Cells[2][i] ){
             	m++;
             }
         }
     }
     else {
     	 // 同じ得意先品番の履歴データは削除していない場合
         m = 1;
     }

     // 削除する行分だけ上へ移動します
     for( i = SGr_List->Row; i < (SGr_List->RowCount - m); i++) {
         for( k = 1; k < SGr_List->ColCount; k++) {
             SGr_List->Cells[k][i] = SGr_List->Cells[k][i+m];
         }
     }

     // 行を減らす
     SGr_List->RowCount = SGr_List->RowCount - m;

     // 最下行をクリアー
     for( k = 0; k < SGr_List->ColCount; k++) {
         SGr_List->Cells[k][SGr_List->RowCount - 1] = "";
     }

     // 新しい行を選択
     if( SGr_List->RowCount == SGr_List->Row)    SGr_List->Row = SGr_List->Row - 1;
     else                                        SGr_List->Row = SGr_List->Row;
     SGr_List->SetFocus();
     SGr_ListSelectCell(SGr_List,1,SGr_List->Row,true);

     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     // データを変更したフラグ
     DataSave = true;

     // ボタンの初期化
     BtnF11->Enabled = true;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ１１：保存」ボタンを押した時の処理
//
//  機能説明
//    更新の有ったデータを確定（Commit）します
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
void __fastcall TForm1::BtnF11Click(TObject *Sender)
{

     if( !BtnF11->Enabled )    return;

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "保存中です．．．しばらくお待ち下さい。";
     SBr1->Update();

     // 変更，挿入，削除を永続的に保存し，現在のトランザクションを終了
     if( Database1->InTransaction == True ){
         Database1->Commit();
         // 新しいトランザクションを開始
         Database1->StartTransaction();
     }
     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     // データを変更したフラグ
     DataSave = false;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ１２：終了」ボタンを押した時の処理
//
//  機能説明
//    メインフォームのCloseをコールします
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
void __fastcall TForm1::BtnF12Click(TObject *Sender)
{
     if( !BtnF12->Enabled )    return;
     Close();
}

//---------------------------------------------------------------------------
//
//  概要
//    OnCloseQueryイベント：Close メソッドが呼び出されたときまたはユーザーが
//          フォームのシステムメニューで［閉じる］を選択したときに発生します。
//
//  機能説明
//    更新したデータが未保存の場合、保存するかしないかを確認します。
//    保存する場合は、「Ｆ１１：保存」ボタン処理をコールしデータを保存します。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    bool &CanClose	：true  = そのままフォームを閉じます
//                        false = フォームCloseをキャンセルします
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    // データを変更したかどうかのフラグチェック
    if( DataSave ){
        switch( MessageDlg( "データが編集されています。\n保存しますか？",
                           mtConfirmation, mbYesNoCancel, 0) ){
            // 「Yes」      保存
            case mrYes:
	            BtnF11Click(Sender);
                break;
            // 「No」       変更を破棄
            case mrNo:
                if( Database1->InTransaction == True )  Database1->Rollback();
                break;
            // 「Cancel」   キャンセル
            case mrCancel:
                CanClose = false;
                return;
        }
    }
    else{
        if( Database1->InTransaction == True )  Database1->Rollback();
    }

	// データベース接続を開放します
    Query1->Close();

	Database1->Close();

    // メモリの開放
    if( hMemTITLE ){
        GlobalUnlock( hMemTITLE );
        GlobalFree( hMemTITLE );
    }
    if( hMemKIKI ){
        GlobalUnlock( hMemKIKI );
        GlobalFree( hMemKIKI );
    }

    // Grid用フォントの開放
    DeleteObject( MyFont );

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：データを追加（KSM01）します。
//
//  機能説明
//    「Ｆ８：新規登録」、「Ｆ９：修正」時のデータ追加（KSM01）処理
//
//  パラメタ説明
//    int iUpd			：0 = 新規登録時
//                        1 = 修正時
//
//  戻り値
//    bool				：true = 成功、false = 失敗
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::AddData( int iUpd )
{
    AnsiString sBuf;

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // 問合せ文作成
    sBuf  = "select DTKSHIN from KSM01";
    sBuf += " where DTKSHIN='" + AnsiString(tmpKSM01_DATA.DTKSHIN) + "'";	// 得意先品番
    sBuf += " and REVCNT=" + AnsiString(tmpKSM01_DATA.REVCNT);				// 改訂番号

    Query1->SQL->Add(sBuf);

    // 問い合せ文の実行
    try {
        Query1->Open();
        Query1->Active = true;

        if( !(Query1->Eof == True && Query1->Bof == True) ){
            if( iUpd == 0 ){
            	//SBr1->Panels->Items[0]->Text = "既に登録されています。　新規登録処理は中断されました。";
				MessageDlg("既に登録されています。　新規登録処理は中断されました。", mtWarning,
					TMsgDlgButtons() << mbOK , 0);
            } else {
				//SBr1->Panels->Items[0]->Text = "既に登録されています。　修正処理は中断されました。";
				MessageDlg("既に登録されています。　修正処理は中断されました。", mtWarning,
					TMsgDlgButtons() << mbOK , 0);
            }
            SBr1->Panels->Items[0]->Text = "";
            SBr1->Update();
            Beep();
            return(False);
        }
    }
    catch(EDatabaseError& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        Beep();
        return(False);
    }
    catch(Exception& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        Beep();
        return(False);
    }

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // 問合せ文作成
    sBuf = "insert into KSM01(";
    sBuf += " DTKSHIN, REVCNT, HINBAN, DTKSCOD, DTKSNAM, ZISNAM, HINMEI,";
    sBuf += " DTKSHIN1_SZ, DTKSHIN2_SZ, DTKSHIN3_SZ, DTKSHIN4_SZ, DTKSHIN5_SZ,";
    sBuf += " DTKSHIN6_SZ, LOT_LINK_SZ, SOKUTEI_NUM,";
    sBuf += " OUT_TITLE1, OUT_TITLE2, OUT_TITLE3, OUT_TITLE4,";
    sBuf += " OUT_TITLE5, OUT_TITLE6, OUT_TITLE7, OUT_TITLE8,";
    sBuf += " X_OUT, MEMO, ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT )";

    sBuf += " VALUES( '";
	sBuf += AnsiString(tmpKSM01_DATA.DTKSHIN)		+ "'," ;	// 得意先品番
	sBuf += AnsiString(tmpKSM01_DATA.REVCNT)		+  ",'";	// 改訂番号
	sBuf += AnsiString(tmpKSM01_DATA.HINBAN)		+ "','";	// 自社品番
	sBuf += AnsiString(tmpKSM01_DATA.DTKSCOD)		+ "','";	// 得意先コード
	sBuf += AnsiString(tmpKSM01_DATA.DTKSNAM)		+ "','";	// 得意先名称
	sBuf += AnsiString(tmpKSM01_DATA.ZISNAM)		+ "','";	// 材質名称（品種）
	sBuf += AnsiString(tmpKSM01_DATA.HINMEI)		+ "','";	// 品名
	sBuf += AnsiString(tmpKSM01_DATA.DTKSHIN1_SZ)	+ "','";	// 素材用得意先品番1
	sBuf += AnsiString(tmpKSM01_DATA.DTKSHIN2_SZ)	+ "','";	// 素材用得意先品番2
	sBuf += AnsiString(tmpKSM01_DATA.DTKSHIN3_SZ)	+ "','";	// 素材用得意先品番3
	sBuf += AnsiString(tmpKSM01_DATA.DTKSHIN4_SZ)	+ "','";	// 素材用得意先品番4
	sBuf += AnsiString(tmpKSM01_DATA.DTKSHIN5_SZ)	+ "','";	// 素材用得意先品番5
	sBuf += AnsiString(tmpKSM01_DATA.DTKSHIN6_SZ)	+ "'," ;	// 素材用得意先品番6
	sBuf += AnsiString(tmpKSM01_DATA.LOT_LINK_SZ)	+  "," ;	// 素材用ロットのリンク
	sBuf += AnsiString(tmpKSM01_DATA.SOKUTEI_NUM)	+  "," ;	// 測定項目数
	sBuf += AnsiString(tmpKSM01_DATA.OUT_TITLE1)	+  "," ;	// 成績書タイトル出力項目1
	sBuf += AnsiString(tmpKSM01_DATA.OUT_TITLE2)	+  "," ;	// 成績書タイトル出力項目2
	sBuf += AnsiString(tmpKSM01_DATA.OUT_TITLE3)	+  "," ;	// 成績書タイトル出力項目3
	sBuf += AnsiString(tmpKSM01_DATA.OUT_TITLE4)	+  "," ;	// 成績書タイトル出力項目4
	sBuf += AnsiString(tmpKSM01_DATA.OUT_TITLE5)	+  "," ;	// 成績書タイトル出力項目5
	sBuf += AnsiString(tmpKSM01_DATA.OUT_TITLE6)	+  "," ;	// 成績書タイトル出力項目6
	sBuf += AnsiString(tmpKSM01_DATA.OUT_TITLE7)	+  "," ;	// 成績書タイトル出力項目7
	sBuf += AnsiString(tmpKSM01_DATA.OUT_TITLE8)	+  "," ;	// 成績書タイトル出力項目8
	sBuf += AnsiString(tmpKSM01_DATA.X_OUT)			+  ",'";	// Ｘの出力
	sBuf += AnsiString(tmpKSM01_DATA.MEMO)			+ "','";	// 備考
	sBuf += AnsiString(tmpKSM01_DATA.ADDYMD)		+ "','";	// 登録日
	sBuf += AnsiString(tmpKSM01_DATA.ADDTIM)		+ "','";	// 登録時間
	sBuf += AnsiString(tmpKSM01_DATA.UPDYMD)		+ "','";	// 変更日
	sBuf += AnsiString(tmpKSM01_DATA.UPDTIM)		+ "'," ;	// 変更時間
	sBuf += AnsiString(tmpKSM01_DATA.UPDCHR)		+  "," ;	// 更新者（コード）
	sBuf += AnsiString(tmpKSM01_DATA.UPDCNT)		+  ")" ;	// 更新回数

    Query1->SQL->Add(sBuf);

    // 問い合せ文の実行
    try {
        Query1->ExecSQL();
    }
    catch(EDatabaseError& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        Beep();
        return(False);
    }
    catch(Exception& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        Beep();
        return(False);
    }

    return(True);

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：データを追加（KSM02）します。
//
//  機能説明
//    「Ｆ８：新規登録」、「Ｆ９：修正」時のデータ追加（KSM02）処理
//
//  パラメタ説明
//    int iUpd			：0 = 新規登録時
//                        1 = 修正時
//
//  戻り値
//    bool				：true = 成功、false = 失敗
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::AddData_Details( int iUpd )
{
    int			i;
    AnsiString	sBuf;


    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // 問合せ文作成
    sBuf  = "select DTKSHIN from KSM02";
    sBuf += " where DTKSHIN='" + AnsiString(tmpKSM01_DATA.DTKSHIN) + "'";	// 得意先品番
    sBuf += " and REVCNT=" + AnsiString(tmpKSM01_DATA.REVCNT);				// 改訂番号

    Query1->SQL->Add(sBuf);

    // 問い合せ文の実行
    try {
        Query1->Open();
        Query1->Active = true;

        if( !(Query1->Eof == True && Query1->Bof == True) ){

            //if( iUpd == 0 ){
            //	SBr1->Panels->Items[0]->Text = "既に登録されています。　新規登録処理は中断されました。";
            //} else {
            //	SBr1->Panels->Items[0]->Text = "既に登録されています。　修正処理は中断されました。";
            //}
            //SBr1->Update();
            //Beep();
            //return(False);

            // 既存データがKSM01にある場合は、削除します

			// Initial Query
			Query1->Close();
			Query1->SQL->Clear();

			// 問合せ文作成
			sBuf = "DELETE from KSM02";
			sBuf += " where DTKSHIN='" + AnsiString(tmpKSM01_DATA.DTKSHIN)	+ "'"	;	// 得意先品番
			sBuf += " and REVCNT=" + AnsiString(tmpKSM01_DATA.REVCNT)				;	// 改訂番号

			Query1->SQL->Add(sBuf);

			// 問い合せ文の実行
			try {
				Query1->ExecSQL();
			}
			catch(EDatabaseError& e) {
				SBr1->Panels->Items[0]->Text = e.Message;
				SBr1->Update();
				return(False);
			}
			catch(Exception& e) {
				SBr1->Panels->Items[0]->Text = e.Message;
				SBr1->Update();
				return(False);
			}

        }
    }
    catch(EDatabaseError& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        Beep();
        return(False);
    }
    catch(Exception& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        Beep();
        return(False);
    }


   	// StringGrid内のデータを全て登録します
    for( i = 1; i < SGr_SOKUT->RowCount - 1; i++) {
        if( SGr_SOKUT->Cells[15][i].ToIntDef(-1) >= 0 ){

        	// StringGridからKSM02構造体に値をコピーします
			strcpy( tmpKSM02_DATA.DTKSHIN		,tmpKSM01_DATA.DTKSHIN );	// 代表得意先品番
			strcpy( tmpKSM02_DATA.REVCNT		,tmpKSM01_DATA.REVCNT );	// 改訂番号
			sBuf = SGr_SOKUT->Cells[13][i];
			strcpy( tmpKSM02_DATA.UNQ_NO		,sBuf.c_str() );	// 明細NO
			sBuf = SGr_SOKUT->Cells[14][i];
			strcpy( tmpKSM02_DATA.ORDER_NO		,sBuf.c_str() );	// 表示順
			sBuf = SGr_SOKUT->Cells[15][i];
			strcpy( tmpKSM02_DATA.SKB_NO		,sBuf.c_str() );	// 識別NO
			sBuf = SGr_SOKUT->Cells[1][i];
			strcpy( tmpKSM02_DATA.HINBAN_SK		,sBuf.c_str() );	// 品番
			sBuf = SGr_SOKUT->Cells[12][i];
			strcpy( tmpKSM02_DATA.KOMK_NO		,sBuf.c_str() );	// 項目NO
			sBuf = SGr_SOKUT->Cells[2][i];
			strcpy( tmpKSM02_DATA.KOMK_NM		,sBuf.c_str() );	// 測定項目名称（日本語）
			sBuf = SGr_SOKUT->Cells[4][i];
			strcpy( tmpKSM02_DATA.KOMK_ENG		,sBuf.c_str() );	// 測定項目名称（英語）
			sBuf = SGr_SOKUT->Cells[3][i].Trim();
			strcpy( tmpKSM02_DATA.KOMK_SUB		,sBuf.c_str() );	// 測定項目サブ名称（日本語）
			sBuf = SGr_SOKUT->Cells[16][i].Trim();
			strcpy( tmpKSM02_DATA.KOMK_SUB_ENG	,sBuf.c_str() );	// 測定項目サブ名称（英語）
			sBuf = SGr_SOKUT->Cells[17][i];
			strcpy( tmpKSM02_DATA.KIKI_NO		,sBuf.c_str() );	// 測定機器NO
			sBuf = SGr_SOKUT->Cells[9][i];
			strcpy( tmpKSM02_DATA.KIKI_NM		,sBuf.c_str() );	// 測定機器名称
			sBuf = SGr_SOKUT->Cells[5][i];
			strcpy( tmpKSM02_DATA.TANI			,sBuf.c_str() );	// 単位
			sBuf = SGr_SOKUT->Cells[18][i];
			strcpy( tmpKSM02_DATA.KIKA_TYPE		,sBuf.c_str() );	// 規格タイプ
			sBuf = SGr_SOKUT->Cells[19][i];
			strcpy( tmpKSM02_DATA.KIKA_KIND		,sBuf.c_str() );	// 規格種類
			sBuf = SGr_SOKUT->Cells[20][i];
			strcpy( tmpKSM02_DATA.KIKA_DECI		,sBuf.c_str() );	// 規格小数点以下桁数
			sBuf = SGr_SOKUT->Cells[21][i];
			strcpy( tmpKSM02_DATA.KIKA_NUM1		,sBuf.c_str() );	// 規格値１
			sBuf = SGr_SOKUT->Cells[22][i];
			strcpy( tmpKSM02_DATA.KIKA_NUM2		,sBuf.c_str() );	// 規格値２
			sBuf = SGr_SOKUT->Cells[23][i];
			strcpy( tmpKSM02_DATA.KIKA_NUM3		,sBuf.c_str() );	// 規格値３
			sBuf = SGr_SOKUT->Cells[24][i];
			strcpy( tmpKSM02_DATA.KIKA_STR		,sBuf.c_str() );	// 規格値文字
			sBuf = SGr_SOKUT->Cells[25][i];
			strcpy( tmpKSM02_DATA.KIKA_SUB1		,sBuf.c_str() );	// 規格値サブ１
			sBuf = SGr_SOKUT->Cells[26][i];
			strcpy( tmpKSM02_DATA.KIKA_SUB2		,sBuf.c_str() );	// 規格値サブ２
			sBuf = SGr_SOKUT->Cells[27][i];
			strcpy( tmpKSM02_DATA.KIKA_SUB3		,sBuf.c_str() );	// 規格値サブ３
			sBuf = SGr_SOKUT->Cells[7][i];
			strcpy( tmpKSM02_DATA.SOKU_SU		,sBuf.c_str() );	// 測定指示n数
			sBuf = SGr_SOKUT->Cells[10][i];
			strcpy( tmpKSM02_DATA.SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
			sBuf = SGr_SOKUT->Cells[11][i];
			strcpy( tmpKSM02_DATA.TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
			sBuf = SGr_SOKUT->Cells[28][i];
			strcpy( tmpKSM02_DATA.KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
			sBuf = SGr_SOKUT->Cells[8][i];
			strcpy( tmpKSM02_DATA.VALUE_TYPE	,sBuf.c_str() );	// 測定値表現
			sBuf = SGr_SOKUT->Cells[29][i];
			strcpy( tmpKSM02_DATA.VALUE_DECI	,sBuf.c_str() );	// 測定値小数点以下桁数



			// Initial Query
			Query1->Close();
			Query1->SQL->Clear();

			// 問合せ実行（製品規格明細マスター）
			sBuf  = "insert into KSM02(";
			sBuf += " DTKSHIN, REVCNT, UNQ_NO, ORDER_NO, SKB_NO, HINBAN_SK,";
			sBuf += " KOMK_NO, KOMK_NM, KOMK_ENG, KOMK_SUB, KOMK_SUB_ENG,";
			sBuf += " KIKI_NO, KIKI_NM, TANI, KIKA_TYPE, KIKA_KIND,";
			sBuf += " KIKA_DECI, KIKA_NUM1, KIKA_NUM2, KIKA_NUM3,";
			sBuf += " KIKA_STR, KIKA_SUB1, KIKA_SUB2, KIKA_SUB3,";
			sBuf += " SOKU_SU, SOKU_FLG, TOKU_FLG, KIKA_PRT,";
			sBuf += " VALUE_TYPE, VALUE_DECI )";

			sBuf += " VALUES( '";
			sBuf += AnsiString(tmpKSM02_DATA.DTKSHIN)		+ "'," ;	// 代表得意先品番
			sBuf += AnsiString(tmpKSM02_DATA.REVCNT)		+  "," ;	// 改訂番号
			sBuf += AnsiString(tmpKSM02_DATA.UNQ_NO)		+  "," ;	// 明細NO
			sBuf += AnsiString(tmpKSM02_DATA.ORDER_NO)		+  "," ;	// 表示順
			sBuf += AnsiString(tmpKSM02_DATA.SKB_NO)		+  ",'";	// 識別NO
			sBuf += AnsiString(tmpKSM02_DATA.HINBAN_SK)		+ "'," ;	// 品番
			sBuf += AnsiString(tmpKSM02_DATA.KOMK_NO)		+  ",'";	// 項目NO
			sBuf += AnsiString(tmpKSM02_DATA.KOMK_NM)		+ "','";	// 測定項目名称（日本語）
			sBuf += AnsiString(tmpKSM02_DATA.KOMK_ENG)		+ "','";	// 測定項目名称（英語）
			sBuf += AnsiString(tmpKSM02_DATA.KOMK_SUB)		+ "','";	// 測定項目サブ名称（日本語）
			sBuf += AnsiString(tmpKSM02_DATA.KOMK_SUB_ENG)	+ "'," ;	// 測定項目サブ名称（英語）
			sBuf += AnsiString(tmpKSM02_DATA.KIKI_NO)		+  ",'";	// 測定機器NO
			sBuf += AnsiString(tmpKSM02_DATA.KIKI_NM)		+ "','";	// 測定機器名称
			sBuf += AnsiString(tmpKSM02_DATA.TANI)			+ "'," ;	// 単位
			sBuf += AnsiString(tmpKSM02_DATA.KIKA_TYPE)		+  "," ;	// 規格タイプ
			sBuf += AnsiString(tmpKSM02_DATA.KIKA_KIND)		+  "," ;	// 規格種類
			sBuf += AnsiString(tmpKSM02_DATA.KIKA_DECI)		+  "," ;	// 規格小数点以下桁数
			sBuf += AnsiString(tmpKSM02_DATA.KIKA_NUM1)		+  "," ;	// 規格値１
			sBuf += AnsiString(tmpKSM02_DATA.KIKA_NUM2)		+  "," ;	// 規格値２
			sBuf += AnsiString(tmpKSM02_DATA.KIKA_NUM3)		+  ",'";	// 規格値３
			sBuf += AnsiString(tmpKSM02_DATA.KIKA_STR)		+ "','";	// 規格値文字
			sBuf += AnsiString(tmpKSM02_DATA.KIKA_SUB1)		+ "','";	// 規格値サブ１
			sBuf += AnsiString(tmpKSM02_DATA.KIKA_SUB2)		+ "','";	// 規格値サブ２
			sBuf += AnsiString(tmpKSM02_DATA.KIKA_SUB3)		+ "'," ;	// 規格値サブ３
			sBuf += AnsiString(tmpKSM02_DATA.SOKU_SU)		+  "," ;	// 測定指示n数
			sBuf += AnsiString(tmpKSM02_DATA.SOKU_FLG)		+  "," ;	// 測定項目の有無
			sBuf += AnsiString(tmpKSM02_DATA.TOKU_FLG)		+  "," ;	// 特別項目の有無
			sBuf += AnsiString(tmpKSM02_DATA.KIKA_PRT)		+  "," ;	// 上限下限値の印刷
			sBuf += AnsiString(tmpKSM02_DATA.VALUE_TYPE)	+  "," ;	// 測定値表現
			sBuf += AnsiString(tmpKSM02_DATA.VALUE_DECI)	+  ")" ;	// 測定値小数点以下桁数

			Query1->SQL->Add(sBuf);
	
			// 問い合せ文の実行
			try {
				Query1->ExecSQL();
			}
			catch(EDatabaseError& e) {
				SBr1->Panels->Items[0]->Text = e.Message;
				SBr1->Update();
				Beep();
				return(False);
			}
			catch(Exception& e) {
				SBr1->Panels->Items[0]->Text = e.Message;
				SBr1->Update();
				Beep();
				return(False);
			}

    	}
	}

    return(True);

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：既存レコードの改訂番号を更新します。
//
//  機能説明
//    既存レコード（KSM01,KSM02）の改訂番号を更新（＋１）する。
//    改訂番号0のデータは更新日も更新
//
//  パラメタ説明
//    AnsiString sDTKSHIN：更新対象の代表得意先品番
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::UpdKaiteiNo( AnsiString sDTKSHIN )
{
    int iREVCNT;
    AnsiString sBuf;
    AnsiString sUpdBuf;

    //*** KSM01のレコード更新
    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // 問合せ実行
    sBuf = "SELECT REVCNT FROM KSM01 ";
    sBuf = sBuf + "WHERE DTKSHIN='" + sDTKSHIN + "'";
    sBuf = sBuf + "ORDER BY REVCNT DESC";

    Query1->SQL->Add(sBuf);
    Query1->Open();
    Query1->Active = true;
    while( !Query1->Eof ){
        iREVCNT = Query1->Fields->Fields[0]->AsInteger;

        //改訂番号 更新
        sUpdBuf = " UPDATE KSM01 SET REVCNT = " + IntToStr( iREVCNT + 1 ) ;
        if ( iREVCNT == 0 ) {
            sUpdBuf = sUpdBuf + ", UPDYMD = '" + FormatDateTime("yyyymmdd",Date()) + "'";
            sUpdBuf = sUpdBuf + ", UPDTIM = '" + FormatDateTime("hhmm",TDateTime::CurrentTime()) + "'";
        }
        sUpdBuf = sUpdBuf + " WHERE DTKSHIN = '" + sDTKSHIN + "'";
        sUpdBuf = sUpdBuf + " AND REVCNT = " + IntToStr( iREVCNT ) ;

        // Initial Query
        Query2->Close();
        Query2->SQL->Clear();

	    Query2->SQL->Add(sUpdBuf);

	    // 問い合せ文の実行
	    try {
	        Query2->ExecSQL();
	    }
	    catch(EDatabaseError& e) {
	        SBr1->Panels->Items[0]->Text = e.Message;
	        SBr1->Update();
	        Beep();
	    }
	    catch(Exception& e) {
	        SBr1->Panels->Items[0]->Text = e.Message;
	        SBr1->Update();
	        Beep();
	    }

        // カーソルを次にセットする
        Query1->Next();
    }


    //*** KSM02のレコード更新
    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // 問合せ実行
    sBuf = "SELECT REVCNT FROM KSM02 ";
    sBuf = sBuf + "WHERE DTKSHIN='" + sDTKSHIN + "'";
    sBuf = sBuf + "ORDER BY REVCNT DESC";

    Query1->SQL->Add(sBuf);
    Query1->Open();
    Query1->Active = true;
    while( !Query1->Eof ){
        iREVCNT = Query1->Fields->Fields[0]->AsInteger;

        //改訂番号 更新
        sUpdBuf = " UPDATE KSM02 SET REVCNT = " + IntToStr( iREVCNT + 1 ) ;
        sUpdBuf = sUpdBuf + " WHERE DTKSHIN = '" + sDTKSHIN + "'";
        sUpdBuf = sUpdBuf + " AND REVCNT = " + IntToStr( iREVCNT );

        // Initial Query
        Query2->Close();
        Query2->SQL->Clear();

	    Query2->SQL->Add(sUpdBuf);

	    // 問い合せ文の実行
	    try {
	        Query2->ExecSQL();
	    }
	    catch(EDatabaseError& e) {
	        SBr1->Panels->Items[0]->Text = e.Message;
	        SBr1->Update();
	        Beep();
	    }
	    catch(Exception& e) {
	        SBr1->Panels->Items[0]->Text = e.Message;
	        SBr1->Update();
	        Beep();
	    }

        // カーソルを次にセットする
        Query1->Next();
    }
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：データを削除します。
//
//  機能説明
//    「Ｆ１０：削除」時のデータ削除（KSM01,KSM02）処理
//
//  パラメタ説明
//    bool *iRIREKI_DEL	：履歴データも削除するかどうかのフラグ
//
//  戻り値
//    bool				：true = 成功、false = 失敗
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::DelData(bool *iRIREKI_DEL)
{

	// bool		iRIREKI_DEL;
    AnsiString	sBuf;


    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // 削除対象レコードがあるかどうか確認します
    sBuf = "select * from KSM01";
    sBuf += " where DTKSHIN='" + AnsiString(tmpKSM01_DATA.DTKSHIN)	+ "'"	;	// 得意先品番
	sBuf += " and REVCNT=" + AnsiString(tmpKSM01_DATA.REVCNT)				;	// 改訂番号

    Query1->SQL->Add(sBuf);

    // 問い合せ文の実行
    try {
        Query1->Open();
        Query1->Active = true;
        if( Query1->Eof == True &&  Query1->Bof == True ) {
            SBr1->Panels->Items[0]->Text = "該当のデータが見つかりません。削除できませんでした。";
            SBr1->Update();
            return(False);
        }
    }
    catch(EDatabaseError& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }
    catch(Exception& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }


    // 最新の得意先品番が削除される時は、同じ得意先品番の履歴データも削除するか問い合わせします。
    *iRIREKI_DEL = false;
    if( AnsiString(tmpKSM01_DATA.REVCNT) == "0" ){

        // Initial Query
        Query1->Close();
        Query1->SQL->Clear();

        // 問合せ文作成
        sBuf = "select count(*) as DTKSHIN_CNT from KSM01";
        sBuf += " where DTKSHIN='" + AnsiString(tmpKSM01_DATA.DTKSHIN)	+ "'"	;	// 得意先品番

        Query1->SQL->Add(sBuf);

        // 問い合せ文の実行
        try {
            Query1->Open();
            Query1->Active = true;
            if( !Query1->Eof ){
                if( Query1->FieldValues["DTKSHIN_CNT"] > 0 ){
                    // 2004/1/23 A.Tamura 履歴は強制的に削除する様に変更
                    /*
                    if( MessageDlg( "指定した得意先品番の履歴データも削除しますか？",
                           mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes ){
                        *iRIREKI_DEL = true;
                    }
                    */
                    *iRIREKI_DEL = true;
				}
            }
        }
        catch(EDatabaseError& e) {
            SBr1->Panels->Items[0]->Text = e.Message;
            SBr1->Update();
            return(False);
        }
        catch(Exception& e) {
            SBr1->Panels->Items[0]->Text = e.Message;
            SBr1->Update();
            return(False);
        }

	}


    //*** KSM01からレコードの削除
    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // 問合せ文作成
    sBuf = "DELETE from KSM01";
    sBuf += " where DTKSHIN='" + AnsiString(tmpKSM01_DATA.DTKSHIN)	+ "'"	;	// 得意先品番
    if( *iRIREKI_DEL == false ){
		sBuf += " and REVCNT=" + AnsiString(tmpKSM01_DATA.REVCNT)			;	// 改訂番号
    }

    Query1->SQL->Add(sBuf);

    // 問い合せ文の実行
    try {
        Query1->ExecSQL();
    }
    catch(EDatabaseError& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }
    catch(Exception& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }


    //*** KSM02からレコードの削除
    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // 問合せ文作成
    sBuf = "DELETE from KSM02";
    sBuf += " where DTKSHIN='" + AnsiString(tmpKSM01_DATA.DTKSHIN)	+ "'"	;	// 得意先品番
    if( *iRIREKI_DEL == false ){
		sBuf += " and REVCNT=" + AnsiString(tmpKSM01_DATA.REVCNT)			;	// 改訂番号
    }

    Query1->SQL->Add(sBuf);

    // 問い合せ文の実行
    try {
        Query1->ExecSQL();
    }
    catch(EDatabaseError& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }
    catch(Exception& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }

    return(True);

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：バッファに保存されたStringGridデータをStringGridの指定行に復元します
//
//  機能説明
//    バッファに保存されたStringGridデータをStringGridの指定行に復元します
//
//  パラメタ説明
//    int iPstIndex		：復元する行NO
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_ListLinePaste( int iPstIndex )
{

	SGr_List->Cells[1][iPstIndex] = tmpKSM01_DATA.DTKSCOD;			// 得意先コード
	SGr_List->Cells[2][iPstIndex] = tmpKSM01_DATA.DTKSHIN;			// 得意先品番
	SGr_List->Cells[3][iPstIndex] = tmpKSM01_DATA.DTKSHIN1_SZ;		// 素材用得意先品番1
	SGr_List->Cells[4][iPstIndex] = tmpKSM01_DATA.HINBAN;			// 自社品番
	SGr_List->Cells[5][iPstIndex] = tmpKSM01_DATA.ZISNAM;			// 材質名称（品種）
	SGr_List->Cells[6][iPstIndex] = tmpKSM01_DATA.HINMEI;			// 品名
	SGr_List->Cells[7][iPstIndex] = tmpKSM01_DATA.SOKUTEI_NUM;		// 測定項目数
	SGr_List->Cells[8][iPstIndex] = tmpKSM01_DATA.ADDYMD;			// 登録日
	SGr_List->Cells[9][iPstIndex] = tmpKSM01_DATA.REVCNT;			// 改訂番号
	SGr_List->Cells[10][iPstIndex] = tmpKSM01_DATA.DTKSNAM;			// 得意先名称
	SGr_List->Cells[11][iPstIndex] = tmpKSM01_DATA.DTKSHIN2_SZ;		// 素材用得意先品番2
	SGr_List->Cells[12][iPstIndex] = tmpKSM01_DATA.DTKSHIN3_SZ;		// 素材用得意先品番3
	SGr_List->Cells[13][iPstIndex] = tmpKSM01_DATA.DTKSHIN4_SZ;		// 素材用得意先品番4
	SGr_List->Cells[14][iPstIndex] = tmpKSM01_DATA.DTKSHIN5_SZ;		// 素材用得意先品番5
	SGr_List->Cells[15][iPstIndex] = tmpKSM01_DATA.DTKSHIN6_SZ;		// 素材用得意先品番6
	SGr_List->Cells[16][iPstIndex] = tmpKSM01_DATA.LOT_LINK_SZ;		// 素材用ロットのリンク
	SGr_List->Cells[17][iPstIndex] = tmpKSM01_DATA.OUT_TITLE1;		// 成績書タイトル出力項目1
	SGr_List->Cells[18][iPstIndex] = tmpKSM01_DATA.OUT_TITLE2;		// 成績書タイトル出力項目2
	SGr_List->Cells[19][iPstIndex] = tmpKSM01_DATA.OUT_TITLE3;		// 成績書タイトル出力項目3
	SGr_List->Cells[20][iPstIndex] = tmpKSM01_DATA.OUT_TITLE4;		// 成績書タイトル出力項目4
	SGr_List->Cells[21][iPstIndex] = tmpKSM01_DATA.OUT_TITLE5;		// 成績書タイトル出力項目5
	SGr_List->Cells[22][iPstIndex] = tmpKSM01_DATA.OUT_TITLE6;		// 成績書タイトル出力項目6
	SGr_List->Cells[23][iPstIndex] = tmpKSM01_DATA.OUT_TITLE7;		// 成績書タイトル出力項目7
	SGr_List->Cells[24][iPstIndex] = tmpKSM01_DATA.OUT_TITLE8;		// 成績書タイトル出力項目8
	SGr_List->Cells[25][iPstIndex] = tmpKSM01_DATA.X_OUT;			// Ｘの出力
	SGr_List->Cells[26][iPstIndex] = tmpKSM01_DATA.MEMO;			// 備考
	SGr_List->Cells[27][iPstIndex] = tmpKSM01_DATA.UPDYMD;			// 変更日
	SGr_List->Cells[28][iPstIndex] = tmpKSM01_DATA.ADDTIM;			// 登録時間
	SGr_List->Cells[29][iPstIndex] = tmpKSM01_DATA.UPDTIM;			// 変更時間
	SGr_List->Cells[30][iPstIndex] = tmpKSM01_DATA.UPDCNT;			// 更新回数
	SGr_List->Cells[31][iPstIndex] = tmpKSM01_DATA.UPDCHR;			// 更新者（コード）
	SGr_List->Cells[32][iPstIndex] = tmpKSM01_DATA.UPDNAM;			// 更新者（名称）

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：コマンドライン引数を分離（部署名、ユーザ名など）
//
//  機能説明
//    プログラム起動時のコマンドライン引数を分離し変数に設定します。
//    ユーザコード、ユーザ名、部署コード、部署名を抽出します
//
//  パラメタ説明
//    AnsiString str	：コマンドライン文字列
//
//  戻り値
//    なし。
//
//  備考
//    プログラム起動時に使用
//
//---------------------------------------------------------------------------
void __fastcall TForm1::ExtractCode(AnsiString str)
{
    int i,n1,m,strlen;

    //初期化
    USER_COD = 0;
    USER_NAM = "";
    BUMO_COD = "";
    BUMO_NAM = "";

    strlen = str.Length();
    n1 = m = 1;

    for ( i = 1; i <= strlen; i++ ) {
        //区切り記号","の検索
        if ( str.SubString(i,1) == "," ) {
            if ( n1 < i ) {
            //n1=iの時は文字列NULL
                switch(m){
                //変数に文字列代入
                    case 1:
                    //USER_COD
                        USER_COD = StrToInt(str.SubString(n1,i - n1));
                        break;
                    case 2:
                    //USER_NAM
                        USER_NAM = str.SubString(n1,i - n1);
                        break;
                    case 3:
                    //BUMO_COD
                        BUMO_COD = str.SubString(n1,i - n1);
                        break;
                    case 4:
                    //BUMO_NAM
                        BUMO_NAM = str.SubString(n1,i - n1);
                        break;
                    default:
                        break;
                }

            }
            //次の文字列開始位置
            n1 = i + 1;
            m++;

        }
    }
    if ( m <= 4 ) {
        //BUMO_NAM
        BUMO_NAM = str.SubString(n1,strlen - n1 + 1);
    }

    // 初期化表示
    PnlBumCode->Caption = BUMO_COD;
    PnlBumName->Caption = BUMO_NAM;
    PnlTanCode->Caption = IntToStr(USER_COD);
    PnlTanName->Caption = USER_NAM;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnChangeイベント	：編集コントロールのテキストに変更が加えられたときに発生します。
//
//  機能説明
//    入力文字(シングルコーテーション、半角カンマ)のチェックを行ないます。
//    入力文字のチェック前の変更フラグを設定します。
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
void __fastcall TForm1::Edt_ALLChange_Base(TObject *Sender)
{

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

	Edt_ALLChange( Sender );

    // データ変更フラグの設定
    DataChange = 1;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnChangeイベント	：編集コントロールのテキストに変更が加えられたときに発生します。
//
//  機能説明
//    入力文字(シングルコーテーション、半角カンマ)のチェックを行ないます。
//    入力文字のチェック前の変更フラグを設定します。（得意先品番用）
//    下StringGridの得意先品番も同時に更新します。
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
void __fastcall TForm1::Edt_ALLChange_DTKSHIN(TObject *Sender)
{
	int			i, k;
    AnsiString	sBuf;
    TEdit* edt = dynamic_cast<TEdit*>(Sender);


    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

	Edt_ALLChange( Sender );

    // データ変更フラグの設定
    DataChange = 1;

   	// StringGrid内の出荷検査項目、材料証明項目の品番を同時に変更します
    sBuf = edt->Text;
    for( i = 1; i < SGr_SOKUT->RowCount - 1; i++) {
        k = SGr_SOKUT->Cells[15][i].ToIntDef(-1);
        if( k == 2 || k == 3 ){
	        SGr_SOKUT->Cells[1][i] = sBuf;   // 品番
    	}
	}

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
void __fastcall TForm1::Edt_ALLChange(TObject *Sender)
{

    int			i;
    AnsiString	sBuf;
    TEdit* edt = dynamic_cast<TEdit*>(Sender);


    sBuf = edt->Text;

    // シングルコーテーションはＤＢ登録時にエラーが発生する
    // ので全角のシングルコーテーションに変換します
    i = sBuf.AnsiPos("'");
    if( i > 0 ){
        sBuf.Delete( i, 1);
        if( edt->MaxLength >= sBuf.Length() + 2 ){
        	sBuf.Insert("’",i);
    	}
        edt->Text = sBuf;
        edt->SelStart = i + 1;
    }

    // 半角カンマはＤＢ登録時にエラーが発生する
    // ので全角のカンマに変換します
    i = sBuf.AnsiPos(",");
    if( i > 0 ){
        sBuf.Delete( i, 1);
        if( edt->MaxLength >= sBuf.Length() + 2 ){
        	sBuf.Insert("，",i);
    	}
        edt->Text = sBuf;
        edt->SelStart = i + 1;
    }
}

//---------------------------------------------------------------------------
//
//  概要
//    OnEnterイベント	：各コントロールがフォーカスを取得した時
//
//  機能説明
//    フォーカス状態を判断し、「Ｆ１：一覧検索」ボタンの有効／無効を切り替えます
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
void __fastcall TForm1::FormEnter(TObject *Sender)
{
    if( SGr_List->Tag == 1 )	return;
    if( BtnF01->Focused() )		return;

    // 検索部　得意先コードにフォーカスが有る場合
    if( Edt_COD1->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 1;
        return;
    }

    // 検索部　得意先品番にフォーカスが有る場合
    if( Edt_COD2->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 2;
        return;
    }

    // 検索部　自社品番にフォーカスが有る場合
    if( Edt_COD3->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 3;
        return;
    }

    // 検索部　材質名称にフォーカスが有る場合
    if( Edt_COD4->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 4;
        return;
    }

    // 詳細部　得意先コードにフォーカスが有る場合
    if( Edt_DTKSCOD->Focused() && Edt_DTKSCOD->ReadOnly == false ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 5;
        return;
    }

    // 詳細部　得意先名称にフォーカスが有る場合
    if( Edt_DTKSNAM->Focused() && Edt_DTKSNAM->ReadOnly == false  ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 6;
        return;
    }

    // 詳細部　得意先品番にフォーカスが有る場合
    if( Edt_DTKSHIN->Focused() && Edt_DTKSHIN->ReadOnly == false  ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 7;
        return;
    }

    // 詳細部　自社品番にフォーカスが有る場合
    if( Edt_HINBAN->Focused() && Edt_HINBAN->ReadOnly == false  ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 8;
        return;
    }

    // 詳細部　材質名称にフォーカスが有る場合
    if( Edt_ZISNAM->Focused() && Edt_ZISNAM->ReadOnly == false  ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 9;
        return;
    }

    // 詳細部　品名にフォーカスが有る場合
    if( Edt_HINMEI->Focused() && Edt_HINMEI->ReadOnly == false  ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 10;
        return;
    }

    // 詳細部　素材用品番「リストボックス」「選択」「削除」ボタンにフォーカスが有る場合
    if( Lbx_DTKSHIN_SZ->Focused() ||
        Btn_DTKSHIN_SZ_ADD->Focused() ||
        Btn_DTKSHIN_SZ_DEL->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 11;
        return;
    }

    // 「F1：一覧検索」ボタンを使えないようにする
    BtnF01->Enabled = false;
    BtnF01->Tag = 0;


}

//---------------------------------------------------------------------------
//
//  概要
//    OnKeyDownイベント	：ユーザーが任意のキーを押すと発生します
//
//  機能説明
//    ファンクションキー、矢印キー、Enterキーによりボタンを選択します
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
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{

     // ステータスメッセージ
     if(SBr1->Panels->Items[0]->Text != ""){
        SBr1->Panels->Items[0]->Text = "";
        SBr1->Update();
     }

     switch(Key){
         case VK_F1:  BtnF01Click(Sender);    break;
         case VK_F2:  BtnF02Click(Sender);    break;
         case VK_F3:  BtnF03Click(Sender);    break;
         case VK_F5:  BtnF05Click(Sender);    break;
         case VK_F7:
                      // 検索部にフォーカスがある場合は、検索実行
                      if( Edt_COD1->Focused() || Edt_COD2->Focused() || Edt_COD3->Focused() || Edt_COD4->Focused() || Cbx_RIREKI->Focused() ){
                          BtnF07Click(Sender);
                      }
                      // 検索部以外にフォーカスがある場合は、検索部にセットフォーカス
                      else{
                          Edt_COD1->SetFocus();
                      }
                      break;
         case VK_F8:  BtnF08Click(Sender);    break;
         case VK_F9:  BtnF09Click(Sender);    break;
         case VK_F10: BtnF10Click(Sender);
                      Key = 0;
                      break;
         case VK_F11: BtnF11Click(Sender);    break;
         case VK_F12: BtnF12Click(Sender);    break;

         // 前項
         case VK_UP:
         case VK_LEFT:
                // 検索部
                if( Edt_COD2->Focused() || Edt_COD3->Focused() || Edt_COD4->Focused() ){
                    TEdit *Edt = (TEdit *)Sender;
                    if( Edt->SelStart == 0 && Edt->SelLength == 0 ){
                        keybd_event(VK_SHIFT,0,0,0);
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                        keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
                        break;
                    }
                }
                if( Edt_COD1->Focused() && Edt_COD1->SelStart == 0 && Edt_COD1->SelLength == 0 ){
                    if(Edt_COD4->Enabled){
                        Edt_COD4->SetFocus();
                    }
                    else{
                        keybd_event(VK_SHIFT,0,0,0);
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                        keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
                    }
                    break;
                }
                break;


         // 次項
         case VK_DOWN:
         case VK_RIGHT:
                // 検索部
                if( Edt_COD1->Focused() || Edt_COD2->Focused() || Edt_COD3->Focused() ){
                    TEdit *Edt = (TEdit *)Sender;
                    if( Edt->SelStart == Edt->Text.Length() && Edt->SelLength == 0 ){
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                        break;
                    }
                }
                if( Edt_COD4->Focused() && Edt_COD4->SelStart == Edt_COD4->Text.Length() && Edt_COD4->SelLength == 0 ){
                    if(Edt_COD1->Enabled){
                        Edt_COD1->SetFocus();
                    }
                    else{
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    }
                    break;
                }
                break;


         // Enter
         case VK_RETURN:
                // 検索部
                if( Edt_COD1->Focused() || Edt_COD2->Focused() || Edt_COD3->Focused() ){
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if( Edt_COD4->Focused() ){
                    BtnF07Click(Sender);    break;
                }
                // 詳細部
                if( Edt_DTKSHIN->Focused() ){
                    SetDTKSHIN_SZ( Edt_DTKSHIN->Text );
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                	break;
                }
                if( Edt_DTKSCOD->Focused() ){
                    SetDTKSNAM( Edt_DTKSCOD->Text );
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                	break;
                }
                if( Edt_DTKSCOD->Focused() ||
                	Edt_DTKSNAM->Focused() ||
                    Lbx_DTKSHIN_SZ->Focused() ||
                    Rdo_LOT_LINK_SZ_ON->Focused() ||
                    Rdo_LOT_LINK_SZ_OFF->Focused() ||
                    Edt_HINBAN->Focused() ||
                    Edt_ZISNAM->Focused() ||
                    Edt_HINMEI->Focused() ||
                    Edt_MEMO->Focused() ||
                    Clb_OUT_TITLE->Focused() ||
                    Rdo_XOUT_ON->Focused() ||
                    Rdo_XOUT_OFF->Focused() ){
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if( SGr_List->Focused() ){
                    Edt_DTKSCOD->SetFocus();
                	break;
				}
                if( SGr_SOKUT->Focused() ){
                	// 履歴が最新のもののみ実行
					if( SGr_List->Cells[9][SGr_List->Row].ToIntDef(0) == 0 ) {
					    // 測定項目編集画面の表示
					    Form4->ShowModal();
	                	break;
					}
				}
                break;


         // [c]キー
         case 67:
				// [Ctrl]キーを押した時 ＆ 測定項目一覧にフォーカスがある時　
				if( Shift.Contains(ssCtrl) && SGr_SOKUT->Focused() ){
                	// 行のコピー
                    if( SGr_SOKUT_GridMultiLineCopy() ){
						SBr1->Panels->Items[0]->Text = "行をコピーしました。";
                		SBr1->Update();
                    }
				}
                break;


         // [v]キー
         case 86:
				// [Ctrl]キーを押した時 ＆ 測定項目一覧にフォーカスがある時　
				if( Shift.Contains(ssCtrl) && SGr_SOKUT->Focused() ){
                	// 履歴が最新のもののみ実行
					if( SGr_List->Cells[9][SGr_List->Row].ToIntDef(0) == 0 ) {
	                	// 行の貼り付け
	                    if( SGr_SOKUT_GridMultiLinePaste() ){
	                		SBr1->Panels->Items[0]->Text = "行を貼り付けました。";
	                		SBr1->Update();
	                    }
					}
				}
                break;


         // Delete
         case VK_DELETE:
				// 測定項目一覧にフォーカスがある時　

               	// 履歴が最新のもののみ実行
				if( SGr_List->Cells[9][SGr_List->Row].ToIntDef(0) == 0 ) {
					if( SGr_SOKUT->Focused() ){
	                	Btn_DELClick(Sender);
	                }
                }
	            break;

     }

}

//---------------------------------------------------------------------------
//
//  概要
//    OnKeyPressイベント：単一の文字キーを押したときに発生します。
//
//  機能説明
//    RETURNコードをクリアーします
//    ビープ音ならさないようにする
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
void __fastcall TForm1::FormKeyPress(TObject *Sender, char &Key)
{
    if( Key == VK_RETURN )   Key = 0;
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：ラジオボタンをクリックしたときに発生します。
//
//  機能説明
//    入力文字のチェック前の変更フラグを設定します。
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
void __fastcall TForm1::Rdo_AllClick(TObject *Sender)
{

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

	// データ変更フラグの設定
    DataChange = 1;
}

//---------------------------------------------------------------------------
//
//  概要
//    OnSelectCellイベント：StringGridのセルが選択される前に発生します。
//
//  機能説明
//    StringGridで選択されたら、画面下部に詳細内容をセットします
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int ACol			：選択する列の位置
//    int ARow			：選択する行の位置
//    bool &CanSelect	：選択を許すかどうかのフラグ
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_ListSelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{

    int			i;
    AnsiString	sBuf;

    // データ選択変更前にデータ変更フラグのチェックを行ないます。
    if( DataChange > 0 ){
        sBuf  = "データが変更されています。変更内容を破棄しますか？";
        sBuf += "\n[は　い] 変更内容を破棄します。（変更前のデータに戻ります）";
        sBuf += "\n[いいえ] 変更処理を続行します。（[F8:新規登録]又は[F9:修正]で変更内容を確定してください。）";
		if( MessageDlg( sBuf, mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo ){
			// 新しい選択を取りやめます
			CanSelect = false;
			return;
		}
	}

    if(ARow == 0) ARow = 1;

    // 得意先コード
    Edt_DTKSCOD->Text = SGr_List->Cells[1][ARow];

    // 得意先名称
    Edt_DTKSNAM->Text = SGr_List->Cells[10][ARow];

    // 得意先品番
    Edt_DTKSHIN->Text = SGr_List->Cells[2][ARow];

    // 素材用得意先品番
    Lbx_DTKSHIN_SZ->Clear();
    sBuf = SGr_List->Cells[3][ARow];
    if( sBuf.Trim() != "" )	Lbx_DTKSHIN_SZ->Items->Add(sBuf);
    sBuf = SGr_List->Cells[11][ARow];
    if( sBuf.Trim() != "" )	Lbx_DTKSHIN_SZ->Items->Add(sBuf);
    sBuf = SGr_List->Cells[12][ARow];
    if( sBuf.Trim() != "" )	Lbx_DTKSHIN_SZ->Items->Add(sBuf);
    sBuf = SGr_List->Cells[13][ARow];
    if( sBuf.Trim() != "" )	Lbx_DTKSHIN_SZ->Items->Add(sBuf);
    sBuf = SGr_List->Cells[14][ARow];
    if( sBuf.Trim() != "" )	Lbx_DTKSHIN_SZ->Items->Add(sBuf);
    sBuf = SGr_List->Cells[15][ARow];
    if( sBuf.Trim() != "" )	Lbx_DTKSHIN_SZ->Items->Add(sBuf);

	// 素材用ロットのリンク
    switch( SGr_List->Cells[16][ARow].ToIntDef(-1) ){
		case 0: Rdo_LOT_LINK_SZ_OFF->Checked = true;
				break;
		case 1:
        default:Rdo_LOT_LINK_SZ_ON->Checked = true;
          		break;
   	}

    // 自社品番
    Edt_HINBAN->Text = SGr_List->Cells[4][ARow];

    // 品種
    Edt_ZISNAM->Text = SGr_List->Cells[5][ARow];

    // 品名
    Edt_HINMEI->Text = SGr_List->Cells[6][ARow];

    // 項目数
    sBuf = SGr_List->Cells[7][ARow];
    Pnl_SOKUTEI_NUM->Caption = AnsiString::StringOfChar(' ', 3-sBuf.Length()) + sBuf;

    // 備考
    Edt_MEMO->Text = SGr_List->Cells[26][ARow];

    // 検査成績書タイトル部出力項目
    for( i = 0; i < iTITLE_Cnt; i++){
        if( iTITLE[i] == SGr_List->Cells[17][ARow].ToIntDef(-1)
         || iTITLE[i] == SGr_List->Cells[18][ARow].ToIntDef(-1)
         || iTITLE[i] == SGr_List->Cells[19][ARow].ToIntDef(-1)
         || iTITLE[i] == SGr_List->Cells[20][ARow].ToIntDef(-1)
         || iTITLE[i] == SGr_List->Cells[21][ARow].ToIntDef(-1)
         || iTITLE[i] == SGr_List->Cells[22][ARow].ToIntDef(-1)
         || iTITLE[i] == SGr_List->Cells[23][ARow].ToIntDef(-1)
         || iTITLE[i] == SGr_List->Cells[24][ARow].ToIntDef(-1) ){
            Clb_OUT_TITLE->Checked[i] = true;
        }
        else {
            Clb_OUT_TITLE->Checked[i] = false;
        }
    }


	// Ｘの出力
    switch( SGr_List->Cells[25][ARow].ToIntDef(-1) ){
		case 1: Rdo_XOUT_ON->Checked = true;
				break;
		case 0:
        default:Rdo_XOUT_OFF->Checked = true;
          		break;
   	}

    // 登録日
    sBuf = SGr_List->Cells[8][ARow];
    if( sBuf.Trim() != "" ){
        sBuf = sBuf.Insert("/",5);
        sBuf = sBuf.Insert("/",8);
        PnlADDYMD2->Caption = sBuf;
    }
    else PnlADDYMD2->Caption = "";

    // 変更日
    sBuf = SGr_List->Cells[27][ARow];
    if( sBuf.Trim() != "" ){
        sBuf = sBuf.Insert("/",5);
        sBuf = sBuf.Insert("/",8);
        PnlUPDYMD2->Caption = sBuf;
    }
    else PnlUPDYMD2->Caption = "";

    // 更新回数
    sBuf = SGr_List->Cells[30][ARow];
    PnlUPDCNT2->Caption = AnsiString::StringOfChar(' ', 3-sBuf.Length()) + sBuf;

    // 改訂番号
    sBuf = SGr_List->Cells[9][ARow];
    PnlREVCNT2->Caption = AnsiString::StringOfChar(' ', 3-sBuf.Length()) + sBuf;

    // 更新者コード
    if( SGr_List->Cells[31][ARow] == "" ){
    	PnlUPDCHR2->Tag = -1;
    }
    else {
    	PnlUPDCHR2->Tag = StrToInt(SGr_List->Cells[31][ARow]);
    }

    // 更新者
    sBuf = SGr_List->Cells[32][ARow];
    PnlUPDCHR2->Caption = sBuf;

    // 履歴データの場合は項目編集できないようにする
    if( SGr_List->Cells[9][ARow].ToIntDef(0) == 0 ) {   // 改訂番号
        InitEdt(true);
    }
    else {
        InitEdt(false);
    }

	// 明細部を検索表示します
    SGr_ListDblClick( ARow );


    // コピーデータの初期化
    iCntCpyKSM02_DATA = 0;
    // メモリの開放
    if( hMemCpyKSM02_DATA ){
        GlobalUnlock( hMemCpyKSM02_DATA );
        GlobalFree( hMemCpyKSM02_DATA );
    }

    // データ変更フラグの初期化
    DataChange = 0;

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：画面下の各コントロールを使用可能／不可能にする
//
//  機能説明
//    最新データの場合は項目編集できるようにする
//    履歴データの場合は項目編集できないようにする
//
//  パラメタ説明
//    bool status		：true = 有効、false = 無効
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::InitEdt(bool status)
{
    TColor cFontColor;

    if ( status ) {
        //使用可能
        cFontColor			= clWindowText;
    } else {
        //使用不可
        cFontColor			= clGray;
    }
	Pnl_DETIALES_TOP->Enabled		= status;
    // 2003/08/06 A.Tamura 改訂版データ（編集不可能）でもスクロールできるようにする為
	//Pnl_SOKUT->Enabled				= status;
    Btn_DTKSHIN_SZ_ADD->Enabled		= status;
    Btn_DTKSHIN_SZ_DEL->Enabled		= status;

    Btn_ADD_SZ->Enabled				= status;
    Btn_ADD_SK->Enabled				= status;
    Btn_ADD_SP->Enabled				= status;
    Btn_EDIT->Enabled				= status;
    Btn_UP->Enabled					= status;
    Btn_DOWN->Enabled				= status;
    Btn_DEL->Enabled				= status;
    Lbx_DTKSHIN_SZ->Enabled			= true;
    SGr_SOKUT->Enabled				= true;

	Edt_DTKSCOD->Font->Color		= cFontColor;
	Edt_DTKSNAM->Font->Color		= cFontColor;
	Edt_DTKSHIN->Font->Color		= cFontColor;
	Lbx_DTKSHIN_SZ->Font->Color		= cFontColor;
	Rdo_LOT_LINK_SZ_ON->Font->Color	= cFontColor;
	Rdo_LOT_LINK_SZ_OFF->Font->Color= cFontColor;
	Edt_HINBAN->Font->Color			= cFontColor;
	Edt_ZISNAM->Font->Color			= cFontColor;
	Edt_HINMEI->Font->Color			= cFontColor;
	Edt_MEMO->Font->Color			= cFontColor;
	Clb_OUT_TITLE->Font->Color		= cFontColor;
	Rdo_XOUT_ON->Font->Color		= cFontColor;
	Rdo_XOUT_OFF->Font->Color		= cFontColor;
    Pnl_SOKUTEI_NUM->Font->Color	= cFontColor;
    PnlADDYMD2->Font->Color			= cFontColor;
    PnlUPDYMD2->Font->Color			= cFontColor;
    PnlUPDCHR2->Font->Color			= cFontColor;
    PnlUPDCNT2->Font->Color			= cFontColor;
    PnlREVCNT2->Font->Color			= cFontColor;
   	SGr_SOKUT->Font->Color			= cFontColor;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnDrawCellイベント：グリッド内（上）のセルを描画する必要があるときに発生します。
//
//  機能説明
//    グリッド内（上）のセル描画をコントロールします
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int ACol			：選択する列の位置
//    int ARow			：選択する行の位置
//    TRect &Rect		：描画セルの左上隅と右下隅の座標
//    TGridDrawState State：描画セルの状態
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_ListDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{

   AnsiString	sBuf;

   RECT r=RECT(Rect);

   //固定セルの背景色をセット
   if(State.Contains(gdFixed))
       SGr_List->Canvas->Brush->Color= SGr_List->FixedColor;
   //フォーカスのあるセルの背景色をセット
//   else if(State.Contains(gdFocused))
//       SGr_Listr1->Canvas->Brush->Color= SGr_Listr1->Options.Contains(goDrawFocusSelected)? clHighlight: SGr_Listr1->Color;
   //選択されているセルの背景色をセット
   else if(State.Contains(gdSelected))
       SGr_List->Canvas->Brush->Color= clHighlight;
   //普通のセルの背景色をセット
   else
       SGr_List->Canvas->Brush->Color= SGr_List->Color;

   //背景色で消去
   SGr_List->Canvas->FillRect(Rect);

   //固定セルの立体枠を描く
   if(SGr_List->Ctl3D&&State.Contains(gdFixed))
       DrawEdge(SGr_List->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);

   //フォーカスのあるセルの文字色をセット
   if(State.Contains(gdFocused)){
//       SGr_Listr1->Canvas->Font->Color= SGr_Listr1->Options.Contains(goDrawFocusSelected)? clHighlightText: SGr_Listr1->Font->Color;
//       //フォーカス枠を描く
//       DrawFocusRect(SGr_Listr1->Canvas->Handle,&r);
	   //選択されているセルの文字色をセット
       //if(State.Contains(gdSelected))

       SGr_List->Canvas->Font->Color= clHighlightText;
   }
   //選択されているセルの文字色をセット
   else if(State.Contains(gdSelected))
       SGr_List->Canvas->Font->Color= clHighlightText;
   //過去の履歴データの場合の文字色をセット
   else if( ACol > 0 && SGr_List->Cells[9][ARow].ToIntDef(0) > 0 )
       SGr_List->Canvas->Font->Color = clSilver;
   //普通のセルの文字色をセット
   else
       SGr_List->Canvas->Font->Color= SGr_List->Font->Color;

   //テキスト表示領域の設定
   InflateRect(&r,-2,-2);

   if( ARow > 0 && ACol == 3 ){
        // 素材用品番
        if( SGr_List->Cells[3][ARow].Trim() != "" ){
            sBuf = SGr_List->Cells[3][ARow];
		}
        if( SGr_List->Cells[11][ARow].Trim() != "" ){
            sBuf = sBuf + "，" + SGr_List->Cells[11][ARow];
		}
        if( SGr_List->Cells[12][ARow].Trim() != "" ){
            sBuf = sBuf + "，" + SGr_List->Cells[12][ARow];
		}
        if( SGr_List->Cells[13][ARow].Trim() != "" ){
            sBuf = sBuf + "，" + SGr_List->Cells[13][ARow];
		}
        if( SGr_List->Cells[14][ARow].Trim() != "" ){
            sBuf = sBuf + "，" + SGr_List->Cells[14][ARow];
		}
        if( SGr_List->Cells[15][ARow].Trim() != "" ){
            sBuf = sBuf + "，" + SGr_List->Cells[15][ARow];
		}
        DrawText(SGr_List->Canvas->Handle,sBuf.c_str(),-1,&r,0); //左寄せ

   } else if( ARow > 0 && ACol == 7 ){
        // 項目数
		DrawText(SGr_List->Canvas->Handle,SGr_List->Cells[ACol][ARow].c_str(),-1,&r,DT_RIGHT); //右寄せ

   } else if( ARow > 0 && ACol == 8 ){
        // 更新日
        sBuf = SGr_List->Cells[ACol][ARow];
        if( sBuf.Length() == 8 ){
        	sBuf.Insert("/",5);
       		sBuf.Insert("/",8);
   			DrawText(SGr_List->Canvas->Handle,sBuf.c_str(),-1,&r,0); //左寄せ
        }

   } else{
		//テキストの表示
		DrawText(SGr_List->Canvas->Handle,SGr_List->Cells[ACol][ARow].c_str(),-1,&r,0); //左寄せ
		//DrawText(SGr_List->Canvas->Handle,SGr_List->Cells[ACol][ARow].c_str(),-1,&r,DT_RIGHT); //右寄せ
		//DrawText(SGr_List->Canvas->Handle,SGr_List->Cells[ACol][ARow].c_str(),-1,&r,DT_CENTER); //中央寄せ（水平）
		//DrawText(SGr_List->Canvas->Handle,SGr_List->Cells[ACol][ARow].c_str(),-1,&r,DT_VCENTER|DT_SINGLELINE); //中央寄せ（垂直）
		//DrawText(SGr_List->Canvas->Handle,SGr_List->Cells[ACol][ARow].c_str(),-1,&r,DT_BOTTOM|DT_SINGLELINE); //下寄せ
		//DrawText(SGr_List->Canvas->Handle,SGr_List->Cells[ACol][ARow].c_str(),-1,&r,DT_CENTER|DT_VCENTER|DT_SINGLELINE); //水平･垂直とも中央寄せ
		//DrawText(SGr_List->Canvas->Handle,SGr_List->Cells[ACol][ARow].c_str(),-1,&r,DT_WORDBREAK); //複数行表示
   }

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：素材用品番の「指定」ボタンを押した時に発生します
//
//  機能説明
//    素材用品番を一覧検索画面から選択指定します
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
void __fastcall TForm1::Btn_DTKSHIN_SZ_ADDClick(TObject *Sender)
{
	BtnF01->Enabled = true;
    BtnF01->Tag = 11;
    BtnF01Click( BtnF01 );
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：素材用品番の「削除」ボタンを押した時に発生します
//
//  機能説明
//    素材用品番一覧で選択されている項目を削除します
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
void __fastcall TForm1::Btn_DTKSHIN_SZ_DELClick(TObject *Sender)
{
    int		i, k;
    int		iCnt;
    bool    fFind;


    fFind = false;

	// 削除しようとする素材用品番が既に登録済みかどうかチェックします
	for( i = Lbx_DTKSHIN_SZ->Items->Count - 1; i >= 0; i-- ){
		if( Lbx_DTKSHIN_SZ->Selected[i] ){
			for( k = 1; k < SGr_SOKUT->RowCount - 1; k++ ){
            	if( SGr_SOKUT->Cells[15][k].ToIntDef(2) == 1 && Lbx_DTKSHIN_SZ->Items->Strings[i] == SGr_SOKUT->Cells[1][k] ){
					fFind = true;
                    break;
                }
        	}
			if(	fFind ) break;
		}
	}

	// 削除しようとする素材用品番が既に登録されていた場合
	if( fFind ){
		if( MessageDlg( "登録済みの素材用測定項目も削除されます。よろしいですか？",
        	mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo ){
        	return;
        }

        // 指定された登録済みの素材用測定項目を削除します
		for( i = Lbx_DTKSHIN_SZ->Items->Count - 1; i >= 0; i-- ){
			if( Lbx_DTKSHIN_SZ->Selected[i] ){
				for( k = SGr_SOKUT->RowCount - 2; k >= 1 ; k-- ){
	            	if( SGr_SOKUT->Cells[15][k].ToIntDef(2) == 1
                        && Lbx_DTKSHIN_SZ->Items->Strings[i] == SGr_SOKUT->Cells[1][k] ){

                        // 削除処理
                        SGr_SOKUT->Row	= k;
                        iRowSelTop		= k;
                        iRowSelBottom	= k;
                    	Btn_DELClick(Btn_DEL);
	                }
	        	}
			}
		}
	}

    iCnt = Lbx_DTKSHIN_SZ->Items->Count;

    // 素材用品番を削除します
	for( i = Lbx_DTKSHIN_SZ->Items->Count - 1; i >= 0; i-- ){
    	if( Lbx_DTKSHIN_SZ->Selected[i] ){
        	Lbx_DTKSHIN_SZ->Items->Delete(i);
        }
    }
    if( Lbx_DTKSHIN_SZ->Items->Count >= 1 ){
    	Lbx_DTKSHIN_SZ->Selected[Lbx_DTKSHIN_SZ->Items->Count - 1] = true;
    }

    if( iCnt != Lbx_DTKSHIN_SZ->Items->Count ){
    	// データ変更フラグの設定
    	DataChange = 1;
    }

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：指定された得意先品番から素材用品番を検索、追加します。
//
//  機能説明
//    出荷用品番指定後、Enterキーでこのコードが実行されます
//    出荷用品番と同じ素材用品番があれば素材用品番一覧に追加します
//
//  パラメタ説明
//    AnsiString sDTKSHIN：得意先品番
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SetDTKSHIN_SZ( AnsiString sDTKSHIN )
{
    int			i, k, m;
    AnsiString	sBuf, sList;


    // 指定文字が無ければ処理を中断します
    if( sDTKSHIN.Trim() == "" )		return;

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // 問合せ実行
    sBuf  = "select DISTINCT DTKSHIN from KSD21";
    sBuf += " where DTKSHIN like '" + sDTKSHIN + "%'";
    sBuf += " order by DTKSHIN";

    Query1->SQL->Add(sBuf);

    // 問い合せ文の実行
    try
    {
        Query1->Open();
        Query1->Active = true;

        if( Query1->Eof == True &&  Query1->Bof == True ){
            // 検索結果無し
            SBr1->Panels->Items[0]->Text = "該当の素材用品番が見つかりません。";
            SBr1->Update();
            Beep();
            return;
        }
        else{
            // 検索結果有り

            sList = "";
            while( !Query1->Eof ){

                if( VarIsNull(Query1->FieldValues["DTKSHIN"]) ){
		            sBuf = "";
                } else{
                    sBuf = Query1->FieldValues["DTKSHIN"];
                }
                if( sBuf.Trim() != "" )	{
                    if( sList != "" )	sList = sList + ",";
                    sList = sList + sBuf;
                }
                // カーソルを次にセットする
                Query1->Next();
            }

            // 既に素材品番が見つかった時だけメッセージを出します
            m = 0;
			for( i = Lbx_DTKSHIN_SZ->Items->Count - 1; i >= 0; i-- ){
				for( k = SGr_SOKUT->RowCount - 2; k >= 1 ; k-- ){
	            	if( SGr_SOKUT->Cells[15][k].ToIntDef(2) == 1
                        && Lbx_DTKSHIN_SZ->Items->Strings[i] == SGr_SOKUT->Cells[1][k] ){
                        sBuf  = "素材用品番を自動検索しました。[" + sList + "]\n";
                        sBuf += "素材用品番にセットしてよろしいですか？（登録済みの素材用測定項目は削除されます。）";
						if( MessageDlg( sBuf, mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo ){
        					return;
        				}
                        m = 1;
                    	break;
	                }
	        	}
                if( m == 1 ) break;
			}

        	// 指定された登録済みの素材用測定項目を削除します
			for( i = Lbx_DTKSHIN_SZ->Items->Count - 1; i >= 0; i-- ){
				for( k = SGr_SOKUT->RowCount - 2; k >= 1 ; k-- ){
	            	if( SGr_SOKUT->Cells[15][k].ToIntDef(2) == 1
                        && Lbx_DTKSHIN_SZ->Items->Strings[i] == SGr_SOKUT->Cells[1][k] ){

                        // 削除処理
                        SGr_SOKUT->Row	= k;
                        iRowSelTop		= k;
                        iRowSelBottom	= k;
                    	Btn_DELClick(Btn_DEL);
	                }
	        	}
			}

            Lbx_DTKSHIN_SZ->Clear();
            Query1->First();
            while( !Query1->Eof ){

                if( VarIsNull(Query1->FieldValues["DTKSHIN"]) ){
		            sBuf = "";
                } else{
                    sBuf = Query1->FieldValues["DTKSHIN"];
                }
                if( sBuf.Trim() != "" )	{
                	Lbx_DTKSHIN_SZ->Items->Add(sBuf);
                	if( Lbx_DTKSHIN_SZ->Items->Count >= 6 )	break;
                }
                // カーソルを次にセットする
                Query1->Next();
            }
            return;
        }
    }
    catch(EDatabaseError& e)
    {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        Beep();
        return;
    }
    catch(Exception& e)
    {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        Beep();
        return;
    }

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：指定された得意先コードから得意先名称を検索、追加します。
//
//  機能説明
//    得意先コード指定後、Enterキーでこのコードが実行されます
//    該当する得意先コードがあれば得意先名称を設定します
//
//  パラメタ説明
//    AnsiString sDTKSCOD：得意先コード
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SetDTKSNAM( AnsiString sDTKSCOD )
{
    AnsiString	sBuf;


    // 指定文字が無ければ処理を中断します
    if( sDTKSCOD.Trim() == "" )		return;

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // 問合せ実行
    sBuf = "select TRSNAM from SM16S where TKSKBN=1";
    sBuf = sBuf + " and TRSCOD = '" + sDTKSCOD + "'";

    Query1->SQL->Add(sBuf);

    // 問い合せ文の実行
    try
    {
        Query1->Open();
        Query1->Active = true;

        if( Query1->Eof == True &&  Query1->Bof == True ){
            // 検索結果無し
            SBr1->Panels->Items[0]->Text = "該当の得意先名称が見つかりません。";
            SBr1->Update();
            Beep();
            return;
        }
        else{
            // 検索結果有り
            Edt_DTKSNAM->Text = Query1->FieldValues["TRSNAM"];
            return;
        }
    }
    catch(EDatabaseError& e)
    {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        Beep();
        return;
    }
    catch(Exception& e)
    {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        Beep();
        return;
    }

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「タイトル部出力情報」
//    ユーザーが項目のチェックボックスを選択または選択解除したときに発生します。
//
//  機能説明
//    タイトル部出力情報の項目選択数を制限します。
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
void __fastcall TForm1::Clb_OUT_TITLEClickCheck(TObject *Sender)
{
    int		i, k;

    k = 0;
    for( i = 0; i < iTITLE_Cnt; i++){
        if( Clb_OUT_TITLE->Checked[i] == true ){
            k++;
        }
    }

    if( k > 8 ){
    	Clb_OUT_TITLE->Checked[Clb_OUT_TITLE->ItemIndex] = false;
    } else {
        // データ変更フラグの設定
        DataChange = 1;
    }

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数		：上StringGridの選択により下StringGrid検索＆表示
//
//  機能説明
//    StringGridで選択されたら、画面下部に詳細内容をセットします
//
//  パラメタ説明
//    int ARow		：選択する行の位置
//
//  戻り値
//    なし。
//
//  備考
//    昔は、DblClickイベントとして使っていましたが、現在は、OnSelectCellイベント
//    からこの関数がコールされています。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_ListDblClick( int ARow )
{

	int			i, iRow;
	AnsiString	sBuf;

	iRow = 1;

    //----------------------------------------------
    // 測定項目マスター検索
    if( SGr_List->Cells[2][ARow] != "" && SGr_List->Cells[9][ARow] != "" ){

		// Initial Query
		Query1->Close();
		Query1->SQL->Clear();
	
		// 問合せ実行（製品規格明細マスター）
		sBuf  = "SELECT UNQ_NO, ORDER_NO, SKB_NO, HINBAN_SK,";
	    sBuf +=       " KOMK_NO, KOMK_NM, KOMK_ENG, KOMK_SUB,";
	    sBuf +=       " KOMK_SUB_ENG, KIKI_NO, KIKI_NM, TANI, KIKA_TYPE,";
	    sBuf +=       " KIKA_KIND, KIKA_DECI, KIKA_NUM1, KIKA_NUM2,";
	    sBuf +=       " KIKA_NUM3, KIKA_STR, KIKA_SUB1, KIKA_SUB2,";
	    sBuf +=       " KIKA_SUB3, SOKU_SU, SOKU_FLG, TOKU_FLG,";
	    sBuf +=       " KIKA_PRT, VALUE_TYPE, VALUE_DECI";
	    sBuf += " FROM KSM02";
	    // 得意先品番
	    sBuf += " WHERE DTKSHIN='" + SGr_List->Cells[2][ARow] + "'";
	    // 改訂番号
	    sBuf += " AND REVCNT=" + SGr_List->Cells[9][ARow];
	    sBuf += " ORDER BY ORDER_NO";
	
		Query1->SQL->Add(sBuf);
		Query1->Open();
		Query1->Active = true;
	
	    //iSOKUT_UNQ_NO_MAX = 0;
	
		while( !Query1->Eof ){
	
			// グリッドの最大行数が超えていないかチェックする
			if( iRow >= SGr_SOKUT->RowCount ){
				SGr_SOKUT->RowCount = iRow + 1;
			}
	
			// グリッドにデータをセットします。
			sBuf = iRow ;
			SGr_SOKUT->Cells[0][iRow] = AnsiString::StringOfChar(' ', 2-sBuf.Length()) + sBuf;    //No
			sBuf = iRow + 1;
	
	        if( VarIsNull(Query1->FieldValues["HINBAN_SK"]) ){
				sBuf = "";
			} else{
				sBuf = Query1->FieldValues["HINBAN_SK"];
			}
	        SGr_SOKUT->Cells[1][iRow] = sBuf;   // 品番

	        if( VarIsNull(Query1->FieldValues["KOMK_NM"]) ){
				sBuf = "";
			} else{
				sBuf = Query1->FieldValues["KOMK_NM"];
			}
	        SGr_SOKUT->Cells[2][iRow] = sBuf;   // 測定項目（日本語）
	
	        if( VarIsNull(Query1->FieldValues["KOMK_SUB"]) ){
				sBuf = "";
			} else{
				sBuf = Query1->FieldValues["KOMK_SUB"];
			}
	        SGr_SOKUT->Cells[3][iRow] = sBuf;   // 測定項目サブ名称（日本語）
	
	        if( VarIsNull(Query1->FieldValues["KOMK_ENG"]) ){
				sBuf = "";
			} else{
				sBuf = Query1->FieldValues["KOMK_ENG"];
	        }
	        SGr_SOKUT->Cells[4][iRow] = sBuf;   //測定項目（英語）
	
	        if( VarIsNull(Query1->FieldValues["TANI"]) ){
				sBuf = "";
			} else{
				sBuf = Query1->FieldValues["TANI"];
	        }
			SGr_SOKUT->Cells[5][iRow] = sBuf;   //単位
	
			SGr_SOKUT->Cells[6][iRow] = "";     //規格（基本）   ※再描画する為に必要です。
	
			sBuf = Query1->FieldValues["SOKU_SU"];
			SGr_SOKUT->Cells[7][iRow] = sBuf;   //ｎ数（基本）
	
			sBuf = Query1->FieldValues["VALUE_TYPE"];
			SGr_SOKUT->Cells[8][iRow] = sBuf;   //値表現
	
	        if( VarIsNull(Query1->FieldValues["KIKI_NM"]) ){
				sBuf = "";
			} else{
				sBuf = Query1->FieldValues["KIKI_NM"];
	        }
			SGr_SOKUT->Cells[9][iRow] = sBuf;   //測定機器名称
	
			sBuf = Query1->FieldValues["SOKU_FLG"];
			SGr_SOKUT->Cells[10][iRow] = sBuf;   //測定項目の有無
	
			sBuf = Query1->FieldValues["TOKU_FLG"];
			SGr_SOKUT->Cells[11][iRow] = sBuf;   //特別項目の有無
	
			sBuf = Query1->FieldValues["KOMK_NO"];
			SGr_SOKUT->Cells[12][iRow] = sBuf;   //項目NO
	
			sBuf = Query1->FieldValues["UNQ_NO"];
			SGr_SOKUT->Cells[13][iRow] = sBuf;   //明細NO
	        // 最大の項目NOを取得します
		    //if( StrToInt(sBuf) > iSOKUT_UNQ_NO_MAX ){
	        //	iSOKUT_UNQ_NO_MAX = StrToInt(sBuf);
	        //}
	
			sBuf = Query1->FieldValues["ORDER_NO"];
			SGr_SOKUT->Cells[14][iRow] = sBuf;   //表示順
	
			sBuf = Query1->FieldValues["SKB_NO"];
			SGr_SOKUT->Cells[15][iRow] = sBuf;   //識別NO
	
	        if( VarIsNull(Query1->FieldValues["KOMK_SUB_ENG"]) ){
				sBuf = "";
			} else{
				sBuf = Query1->FieldValues["KOMK_SUB_ENG"];
	        }
			SGr_SOKUT->Cells[16][iRow] = sBuf;   //測定項目サブ名称（英語）
	
			sBuf = Query1->FieldValues["KIKI_NO"];
			SGr_SOKUT->Cells[17][iRow] = sBuf;   //測定機器NO
	
			sBuf = Query1->FieldValues["KIKA_TYPE"];
			SGr_SOKUT->Cells[18][iRow] = sBuf;   //規格タイプ
	
			sBuf = Query1->FieldValues["KIKA_KIND"];
			SGr_SOKUT->Cells[19][iRow] = sBuf;   //規格種類
	
			sBuf = Query1->FieldValues["KIKA_DECI"];
			SGr_SOKUT->Cells[20][iRow] = sBuf;   //規格小数点以下桁数
	
			sBuf = Query1->FieldValues["KIKA_NUM1"];
			SGr_SOKUT->Cells[21][iRow] = sBuf;   //規格値１
	
			sBuf = Query1->FieldValues["KIKA_NUM2"];
			SGr_SOKUT->Cells[22][iRow] = sBuf;   //規格値２
	
			sBuf = Query1->FieldValues["KIKA_NUM3"];
			SGr_SOKUT->Cells[23][iRow] = sBuf;   //規格値３
	
	        if( VarIsNull(Query1->FieldValues["KIKA_STR"]) ){
				sBuf = "";
			} else{
				sBuf = Query1->FieldValues["KIKA_STR"];
	        }
			SGr_SOKUT->Cells[24][iRow] = sBuf;   //規格文字
	
	        if( VarIsNull(Query1->FieldValues["KIKA_SUB1"]) ){
				sBuf = "";
			} else{
				sBuf = Query1->FieldValues["KIKA_SUB1"];
	        }
			SGr_SOKUT->Cells[25][iRow] = sBuf;   //規格値サブ１
	
	        if( VarIsNull(Query1->FieldValues["KIKA_SUB2"]) ){
				sBuf = "";
			} else{
				sBuf = Query1->FieldValues["KIKA_SUB2"];
	        }
			SGr_SOKUT->Cells[26][iRow] = sBuf;   //規格値サブ２
	
	        if( VarIsNull(Query1->FieldValues["KIKA_SUB3"]) ){
				sBuf = "";
			} else{
				sBuf = Query1->FieldValues["KIKA_SUB3"];
	        }
			SGr_SOKUT->Cells[27][iRow] = sBuf;   //規格値サブ３
	
			sBuf = Query1->FieldValues["KIKA_PRT"];
			SGr_SOKUT->Cells[28][iRow] = sBuf;   //上限下限値の印刷
		
			sBuf = Query1->FieldValues["VALUE_DECI"];
			SGr_SOKUT->Cells[29][iRow] = sBuf;   //測定値小数点以下桁数
	
			SGr_SOKUT->Cells[30][iRow] = "0";    //更新フラグ
	
			// カーソルを次にセットする
			Query1->Next();
	
			iRow += 1;
		}
	}

    // 最下行をクリアー
    SGr_SOKUT->RowCount = iRow + 1;
    for( i = 0; i < SGr_SOKUT->ColCount; i++) {
        SGr_SOKUT->Cells[i][iRow] = "";
    }

    //１行目を自動選択します
    //SGr_SOKUTSelectCell( SGr_SOKUT, 1, 1, true);
    //SGr_SOKUTClick( SGr_SOKUT );

}

//---------------------------------------------------------------------------
//
//  概要
//    OnDrawCellイベント：グリッド内（下）のセルを描画する必要があるときに発生します。
//
//  機能説明
//    グリッド内（下）のセル描画をコントロールします
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int ACol			：選択する列の位置
//    int ARow			：選択する行の位置
//    TRect &Rect		：描画セルの左上隅と右下隅の座標
//    TGridDrawState State：描画セルの状態
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_SOKUTDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{

   AnsiString	sBuf, sValue;
   char 		cFormatBuf[20], c1[20], c2[10];
   long			iPos;

   RECT r=RECT(Rect);

   //固定セルの背景色をセット
   if(State.Contains(gdFixed))
       SGr_SOKUT->Canvas->Brush->Color= SGr_SOKUT->FixedColor;
   //フォーカスのあるセルの背景色をセット
//   else if(State.Contains(gdFocused))
//       SGr_SOKUTr1->Canvas->Brush->Color= SGr_SOKUTr1->Options.Contains(goDrawFocusSelected)? clHighlight: SGr_SOKUTr1->Color;
   //選択されているセルの背景色をセット
   else if(State.Contains(gdSelected))
       SGr_SOKUT->Canvas->Brush->Color= clHighlight;
   //普通のセルの背景色をセット
   else {
       if( ARow > 0 ){
           switch( SGr_SOKUT->Cells[15][ARow].ToIntDef(9) ){
               case 1: // 素材検査項目
                       SGr_SOKUT->Canvas->Brush->Color = (TColor)0x00D2FFFF;
                       break;
               case 2: // 出荷検査項目
                       SGr_SOKUT->Canvas->Brush->Color = (TColor)0x00FFEEDD;
                       break;
               case 3: // 材料証明項目
                       SGr_SOKUT->Canvas->Brush->Color = (TColor)0x00FFE1FD;
                       break;
               case 9: // スペース
               default:
                       SGr_SOKUT->Canvas->Brush->Color = SGr_SOKUT->Color;
                       break;
           }
       }
   }
   //背景色で消去
   SGr_SOKUT->Canvas->FillRect(Rect);

   //固定セルの立体枠を描く
   if(SGr_SOKUT->Ctl3D&&State.Contains(gdFixed))
       DrawEdge(SGr_SOKUT->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);

   //フォーカスのあるセルの文字色をセット
   if(State.Contains(gdFocused)){
//       SGr_SOKUTr1->Canvas->Font->Color= SGr_SOKUTr1->Options.Contains(goDrawFocusSelected)? clHighlightText: SGr_SOKUTr1->Font->Color;
//       //フォーカス枠を描く
//       DrawFocusRect(SGr_SOKUTr1->Canvas->Handle,&r);
	   //選択されているセルの文字色をセット
       //if(State.Contains(gdSelected))

       SGr_SOKUT->Canvas->Font->Color= clHighlightText;
   }
   //選択されているセルの文字色をセット
   else if(State.Contains(gdSelected))
       SGr_SOKUT->Canvas->Font->Color= clHighlightText;
   //普通のセルの文字色をセット
   else
       SGr_SOKUT->Canvas->Font->Color= SGr_SOKUT->Font->Color;

   //テキスト表示領域の設定
   InflateRect(&r,-2,-2);

   if( ARow > 0 && ACol == 6 ){

        // 規格タイプ毎の表示
        switch( SGr_SOKUT->Cells[18][ARow].ToIntDef(0) ){
            case 1: // 範囲指定

                    // 小数点以下桁数のフォーマット文字列
            		sprintf(c1,"%0");
            		sprintf(c2,"1.%df",SGr_SOKUT->Cells[20][ARow].ToIntDef(0) );
            		strcat(c1,c2);

			        switch( SGr_SOKUT->Cells[19][ARow].ToIntDef(0) ){
            			case 1: // 上限下限両方
                                sValue = SGr_SOKUT->Cells[21][ARow];
			                    sprintf(cFormatBuf, c1, sValue.ToDouble() );
                     			sBuf = cFormatBuf;
                     			sBuf +=  "～";
                                sValue = SGr_SOKUT->Cells[22][ARow];
                     			sprintf(cFormatBuf, c1, sValue.ToDouble() );
                     			sBuf += cFormatBuf ;
                                double	Val1, Val2;
								try {
									Val1 = SGr_SOKUT->Cells[21][ARow].ToDouble();
									Val2 = SGr_SOKUT->Cells[22][ARow].ToDouble();
								} catch(EConvertError& e) {
                                	Val1 = 0;
                                	Val2 = 0;
								} catch(Exception& e) {
                                	Val1 = 0;
                                	Val2 = 0;
								}
								if( Val1 >= Val2 ){
                                    // 規格の範囲指定が不正な場合は、赤色で表示します
									SGr_SOKUT->Canvas->Font->Color= clRed;
								}
			            		break;

            			case 2: // 上限のみ
                                sValue = SGr_SOKUT->Cells[22][ARow];
                     			sprintf(cFormatBuf, c1, sValue.ToDouble() );
                     			sBuf = cFormatBuf ;
                     			sBuf += "以下";
			            		break;
            			case 3: // 下限のみ
                                sValue = SGr_SOKUT->Cells[21][ARow];
                     			sprintf(cFormatBuf, c1, sValue.ToDouble() );
                     			sBuf = cFormatBuf ;
                     			sBuf += "以上";
			            		break;
                    }
					DrawText(SGr_SOKUT->Canvas->Handle,sBuf.c_str(),-1,&r,0); //左寄せ
            		break;

            case 2: // 基準値指定

                    // 小数点以下桁数のフォーマット文字列
            		sprintf(c1,"%0");
            		sprintf(c2,"1.%df",SGr_SOKUT->Cells[20][ARow].ToIntDef(0) );
            		strcat(c1,c2);

                    sValue = SGr_SOKUT->Cells[21][ARow];
                    sprintf(cFormatBuf, c1, sValue.ToDouble() );
                    sBuf = cFormatBuf ;
        			SGr_SOKUT->Canvas->TextOut( r.left +  0, r.top + 0, sBuf );
                    iPos = sBuf.Length() * 8;

        			// フォント（小）の設定
        			OrgFont = SelectObject( SGr_SOKUT->Canvas->Handle, MyFont );

			        switch( SGr_SOKUT->Cells[19][ARow].ToIntDef(0) ){
            			case 1: // 上限下限両方
                    			sValue = SGr_SOKUT->Cells[22][ARow];
                    			sprintf(cFormatBuf, c1, sValue.ToDouble() );
			                    sBuf = cFormatBuf;
                                if( sBuf.SubString(1,1) != "-" ) sBuf.Insert("+",1);
                                SGr_SOKUT->Canvas->TextOut( r.left + iPos, r.top - 2, sBuf );
                     			sValue = SGr_SOKUT->Cells[23][ARow];
                    			sprintf(cFormatBuf, c1, sValue.ToDouble() );
			                    sBuf = cFormatBuf ;
                                if( sBuf.SubString(1,1) != "-" ) sBuf.Insert("+",1);
        						SGr_SOKUT->Canvas->TextOut( r.left + iPos, r.top + 7, sBuf );
			            		break;

            			case 2: // 上限のみ
			                    sValue = SGr_SOKUT->Cells[22][ARow];
                    			sprintf(cFormatBuf, c1, sValue.ToDouble() );
			                    sBuf = cFormatBuf;
                                if( sBuf.SubString(1,1) != "-" ) sBuf.Insert("+",1);
			        			SGr_SOKUT->Canvas->TextOut( r.left + iPos, r.top - 2, sBuf );
			            		break;
            			case 3: // 下限のみ
                     			sValue = SGr_SOKUT->Cells[23][ARow];
                    			sprintf(cFormatBuf, c1, sValue.ToDouble() );
			                    sBuf = cFormatBuf ;
                                if( sBuf.SubString(1,1) != "-" ) sBuf.Insert("+",1);
        						SGr_SOKUT->Canvas->TextOut( r.left + iPos, r.top + 7, sBuf );
			            		break;
                    }

        			// 元のフォントに戻します
        			SelectObject( SGr_SOKUT->Canvas->Handle, OrgFont );

                    break;

        	case 3: // 文字
					DrawText(SGr_SOKUT->Canvas->Handle,SGr_SOKUT->Cells[24][ARow].c_str(),-1,&r,0); //左寄せ
                    break;
        }

   } else if( ARow > 0 && ACol == 7 ){
        // ｎ数
        if( SGr_SOKUT->Cells[15][ARow].ToIntDef(0) != 9 ){
            // 2003/06/02 A.Tamura
			if( SGr_SOKUT->Cells[ACol][ARow].ToIntDef(0) < 1 ){
				// n数が0以下（不正）な場合は、赤色で表示します
				SGr_SOKUT->Canvas->Font->Color= clRed;
            }
		    DrawText(SGr_SOKUT->Canvas->Handle,SGr_SOKUT->Cells[ACol][ARow].c_str(),-1,&r,DT_RIGHT); //右寄せ
        }

   } else if( ARow > 0 && ACol == 8 ){
        // 値表現
        if( SGr_SOKUT->Cells[15][ARow].ToIntDef(0) != 9 ){
            switch( SGr_SOKUT->Cells[ACol][ARow].ToIntDef(-1) ){
   	   			case 0: // 整数・小数(99.99)
                        if( SGr_SOKUT->Cells[29][ARow].ToIntDef(0) > 0 ){
                        	sBuf = "9." + AnsiString::StringOfChar('9', SGr_SOKUT->Cells[29][ARow].ToIntDef(0));
                		} else{
                        	sBuf = "9";
                        }
                        DrawText(SGr_SOKUT->Canvas->Handle,sBuf.c_str(),-1,&r,0); //左寄せ
                		break;
   	   			case 1: // 角度(99゜99')
                        if( SGr_SOKUT->Cells[29][ARow].ToIntDef(0) > 0 ){
		                    sBuf = "9°" + AnsiString::StringOfChar('9', SGr_SOKUT->Cells[29][ARow].ToIntDef(0)) + "'";
                		} else{
                        	sBuf = "9°";
                        }
                		DrawText(SGr_SOKUT->Canvas->Handle,sBuf.c_str(),-1,&r,0); //左寄せ
                		break;
   	   			case 2: // 良(OK)／否(NG)
                		DrawText(SGr_SOKUT->Canvas->Handle,"良/否",-1,&r,0); //左寄せ
                		break;
   	   			case 3: // 文字
                		DrawText(SGr_SOKUT->Canvas->Handle,"文字",-1,&r,0); //左寄せ
                		break;
           	}
        }

   } else if( ARow > 0 && (ACol == 10 || ACol == 11) ){
        // 測定項目の有無、特別項目の有無
        if( SGr_SOKUT->Cells[15][ARow].ToIntDef(0) != 9 ){
            switch( SGr_SOKUT->Cells[ACol][ARow].ToIntDef(-1) ){
   		    	case 0: DrawText(SGr_SOKUT->Canvas->Handle,"無",-1,&r,DT_CENTER); //中央寄せ（水平）
                		break;
       			case 1: DrawText(SGr_SOKUT->Canvas->Handle,"有",-1,&r,DT_CENTER); //中央寄せ（水平）
                		break;
            }
       	}

   } else{
		//テキストの表示
		DrawText(SGr_SOKUT->Canvas->Handle,SGr_SOKUT->Cells[ACol][ARow].c_str(),-1,&r,0); //左寄せ
		//DrawText(SGr_SOKUT->Canvas->Handle,SGr_SOKUT->Cells[ACol][ARow].c_str(),-1,&r,DT_RIGHT); //右寄せ
		//DrawText(SGr_SOKUT->Canvas->Handle,SGr_SOKUT->Cells[ACol][ARow].c_str(),-1,&r,DT_CENTER); //中央寄せ（水平）
		//DrawText(SGr_SOKUT->Canvas->Handle,SGr_SOKUT->Cells[ACol][ARow].c_str(),-1,&r,DT_VCENTER|DT_SINGLELINE); //中央寄せ（垂直）
		//DrawText(SGr_SOKUT->Canvas->Handle,SGr_SOKUT->Cells[ACol][ARow].c_str(),-1,&r,DT_BOTTOM|DT_SINGLELINE); //下寄せ
		//DrawText(SGr_SOKUT->Canvas->Handle,SGr_SOKUT->Cells[ACol][ARow].c_str(),-1,&r,DT_CENTER|DT_VCENTER|DT_SINGLELINE); //水平･垂直とも中央寄せ
		//DrawText(SGr_SOKUT->Canvas->Handle,SGr_SOKUT->Cells[ACol][ARow].c_str(),-1,&r,DT_WORDBREAK); //複数行表示
   }

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「上へ移動」ボタンを押した時の処理
//
//  機能説明
//    StringGrid（下）で選択された行を1つ上の行と入れ替えます。
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
void __fastcall TForm1::Btn_UPClick(TObject *Sender)
{
    int			i, k;
	int			iChgRow1;
	int			iChgRow2;
	int			iChgRow3;
	TGridRect	myRect;
    AnsiString	sBuf;


    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

    iChgRow1 = SGr_SOKUT->Selection.Top;
    iChgRow2 = SGr_SOKUT->Selection.Top - 1;
    iChgRow3 = SGr_SOKUT->Selection.Bottom;

    if( iChgRow1 <= 1) return;
    if( iChgRow1 >= SGr_SOKUT->RowCount - 1) return;

    if( iChgRow3 >= SGr_SOKUT->RowCount - 1)
    	iChgRow3 = SGr_SOKUT->Selection.Bottom = SGr_SOKUT->RowCount - 2;

    // ※表示順Cells[14]は入れ替えせずにその他の項目を入れ替え、更新フラグ(Cells[30])をONにします。

    // 入れ替え先のデータをバックアップ
	sBuf = SGr_SOKUT_GridLineCopy( iChgRow2 );

	// 上下を入れ替えます
    for( i = iChgRow2; i < iChgRow3; i++ ) {
    	for( k = 1; k < SGr_SOKUT->ColCount; k++ ) {
            if( k == 14 ){
                // 表示順は、入れ替えしない
    			// SGr_SOKUT->Cells[k][i] = SGr_SOKUT->Cells[k][i + 1];
            } else if( k == 30 ){
                // 更新フラグの設定
				SGr_SOKUT->Cells[k][i] = "1";
        	} else {
				SGr_SOKUT->Cells[k][i] = SGr_SOKUT->Cells[k][i + 1];
            }
		}
    }

    // バックアップしたデータを戻します（表示順は戻さない）
	SGr_SOKUT_GridLinePaste( iChgRow3, "1", false );

    // 選択カーソルも同時に上に移動します
    SGr_SOKUT->Row--;
	myRect.Left		= SGr_SOKUT->Selection.Left;
	myRect.Top		= iChgRow1 - 1;
	myRect.Right	= SGr_SOKUT->Selection.Right;
	myRect.Bottom	= iChgRow3 - 1;
    SGr_SOKUT->Selection	= myRect;
    //SGr_SOKUTSelectCell(SGr_SOKUT,1,SGr_SOKUT->Row,true);

    // データを変更したフラグ
    DataSave = true;
    BtnF11->Enabled = true;

    // データ変更フラグの設定
    DataChange = 1;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「下へ移動」ボタンを押した時の処理
//
//  機能説明
//    StringGrid（下）で選択された行を1つ下の行と入れ替えます。
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
void __fastcall TForm1::Btn_DOWNClick(TObject *Sender)
{
    int			i, k;
	int			iChgRow1;
	int			iChgRow2;
	int			iChgRow3;
	TGridRect	myRect;
    AnsiString	sBuf;


    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

    iChgRow1 = SGr_SOKUT->Selection.Top;
    iChgRow2 = SGr_SOKUT->Selection.Bottom + 1;
    iChgRow3 = SGr_SOKUT->Selection.Bottom;

    if( iChgRow2 >= SGr_SOKUT->RowCount - 1) return;

    // ※表示順Cells[14]は入れ替えせずにその他の項目を入れ替え、更新フラグ(Cells[30])をONにします。

    // 入れ替え先のデータをバックアップ
	sBuf = SGr_SOKUT_GridLineCopy( iChgRow2 );

	// 上下を入れ替えます
    for( i=iChgRow2; i>iChgRow1 ; i-- ) {
    	for( k = 1; k < SGr_SOKUT->ColCount; k++ ) {
            if( k == 14 ){
                // 表示順は、入れ替えしない
    			// SGr_SOKUT->Cells[k][i] = SGr_SOKUT->Cells[k][i - 1];
            } else if( k == 30 ){
                // 更新フラグの設定
				SGr_SOKUT->Cells[k][i] = "1";
        	} else {
				SGr_SOKUT->Cells[k][i] = SGr_SOKUT->Cells[k][i - 1];
            }
		}
    }

    // バックアップしたデータを戻します（表示順は戻さない）
	SGr_SOKUT_GridLinePaste( iChgRow1, "1", false );

    // 選択カーソルも同時に下に移動します
    SGr_SOKUT->Row++;
	myRect.Left		= SGr_SOKUT->Selection.Left;
	myRect.Top		= iChgRow1 + 1;
	myRect.Right	= SGr_SOKUT->Selection.Right;
	myRect.Bottom	= iChgRow3 + 1;
    SGr_SOKUT->Selection	= myRect;
    //SGr_SOKUTSelectCell(SGr_SOKUT,1,SGr_SOKUT->Row,true);

    // データを変更したフラグ
    DataSave = true;
    BtnF11->Enabled = true;

    // データ変更フラグの設定
    DataChange = 1;

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：StringGridの指定行をバッファに保存します
//
//  機能説明
//    StringGrid（下）の指定行をバッファに保存します
//
//  パラメタ説明
//    int iCpyIndex		：複写する行NO
//
//  戻り値
//    AnsiString		：更新フラグ（複写した行が更新済みかどうか）
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::SGr_SOKUT_GridLineCopy( int iCpyIndex)
{
	AnsiString sBuf;

	//strcpy( tmpKSM02_DATA.DTKSHIN		,sBuf.c_str() );	// 代表得意先品番
	//strcpy( tmpKSM02_DATA.REVCNT		,sBuf.c_str() );	// 改訂番号
	sBuf = SGr_SOKUT->Cells[13][iCpyIndex];
	strcpy( tmpKSM02_DATA.UNQ_NO		,sBuf.c_str() );	// 明細NO
	sBuf = SGr_SOKUT->Cells[14][iCpyIndex];
	strcpy( tmpKSM02_DATA.ORDER_NO		,sBuf.c_str() );	// 表示順
	sBuf = SGr_SOKUT->Cells[15][iCpyIndex];
	strcpy( tmpKSM02_DATA.SKB_NO		,sBuf.c_str() );	// 識別NO
	sBuf = SGr_SOKUT->Cells[1][iCpyIndex];
	strcpy( tmpKSM02_DATA.HINBAN_SK		,sBuf.c_str() );	// 品番
	sBuf = SGr_SOKUT->Cells[12][iCpyIndex];
	strcpy( tmpKSM02_DATA.KOMK_NO		,sBuf.c_str() );	// 項目NO
	sBuf = SGr_SOKUT->Cells[2][iCpyIndex];
	strcpy( tmpKSM02_DATA.KOMK_NM		,sBuf.c_str() );	// 測定項目名称（日本語）
	sBuf = SGr_SOKUT->Cells[4][iCpyIndex];
	strcpy( tmpKSM02_DATA.KOMK_ENG		,sBuf.c_str() );	// 測定項目名称（英語）
	sBuf = SGr_SOKUT->Cells[3][iCpyIndex];
	strcpy( tmpKSM02_DATA.KOMK_SUB		,sBuf.c_str() );	// 測定項目サブ名称（日本語）
	sBuf = SGr_SOKUT->Cells[16][iCpyIndex];
	strcpy( tmpKSM02_DATA.KOMK_SUB_ENG	,sBuf.c_str() );	// 測定項目サブ名称（英語）
	sBuf = SGr_SOKUT->Cells[17][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKI_NO		,sBuf.c_str() );	// 測定機器NO
	sBuf = SGr_SOKUT->Cells[9][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKI_NM		,sBuf.c_str() );	// 測定機器名称
	sBuf = SGr_SOKUT->Cells[5][iCpyIndex];
	strcpy( tmpKSM02_DATA.TANI			,sBuf.c_str() );	// 単位
	sBuf = SGr_SOKUT->Cells[18][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKA_TYPE		,sBuf.c_str() );	// 規格タイプ
	sBuf = SGr_SOKUT->Cells[19][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKA_KIND		,sBuf.c_str() );	// 規格種類
	sBuf = SGr_SOKUT->Cells[20][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKA_DECI		,sBuf.c_str() );	// 規格小数点以下桁数
	sBuf = SGr_SOKUT->Cells[21][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKA_NUM1		,sBuf.c_str() );	// 規格値１
	sBuf = SGr_SOKUT->Cells[22][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKA_NUM2		,sBuf.c_str() );	// 規格値２
	sBuf = SGr_SOKUT->Cells[23][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKA_NUM3		,sBuf.c_str() );	// 規格値３
	sBuf = SGr_SOKUT->Cells[24][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKA_STR		,sBuf.c_str() );	// 規格値文字
	sBuf = SGr_SOKUT->Cells[25][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKA_SUB1		,sBuf.c_str() );	// 規格値サブ１
	sBuf = SGr_SOKUT->Cells[26][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKA_SUB2		,sBuf.c_str() );	// 規格値サブ２
	sBuf = SGr_SOKUT->Cells[27][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKA_SUB3		,sBuf.c_str() );	// 規格値サブ３
	sBuf = SGr_SOKUT->Cells[7][iCpyIndex];
	strcpy( tmpKSM02_DATA.SOKU_SU		,sBuf.c_str() );	// 測定指示n数
	sBuf = SGr_SOKUT->Cells[10][iCpyIndex];
	strcpy( tmpKSM02_DATA.SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
	sBuf = SGr_SOKUT->Cells[11][iCpyIndex];
	strcpy( tmpKSM02_DATA.TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
	sBuf = SGr_SOKUT->Cells[28][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
	sBuf = SGr_SOKUT->Cells[8][iCpyIndex];
	strcpy( tmpKSM02_DATA.VALUE_TYPE	,sBuf.c_str() );	// 測定値表現
	sBuf = SGr_SOKUT->Cells[29][iCpyIndex];
	strcpy( tmpKSM02_DATA.VALUE_DECI	,sBuf.c_str() );	// 測定値小数点以下桁数
	sBuf = SGr_SOKUT->Cells[30][iCpyIndex];					//更新フラグ

	return sBuf;	// 更新フラグ
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：バッファに保存されたStringGridデータをStringGridの指定行に復元します
//
//  機能説明
//    バッファに保存されたStringGrid（下）データをStringGridの指定行に復元します
//
//  パラメタ説明
//    int iPstIndex		：復元する行NO
//    AnsiString sUpdFlg：復元する行に設定する更新フラグ
//    bool iOrderNo_UP	：表示順も入れ替えるかどうか
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_SOKUT_GridLinePaste( int iPstIndex, AnsiString sUpdFlg, bool iOrderNo_UP )
{

	//									tmpKSM02_DATA.DTKSHIN		;	// 代表得意先品番
	//									tmpKSM02_DATA.REVCNT		;	// 改訂番号
	SGr_SOKUT->Cells[1][iPstIndex]	=	tmpKSM02_DATA.HINBAN_SK		;	// 品番
	SGr_SOKUT->Cells[2][iPstIndex]	=	tmpKSM02_DATA.KOMK_NM		;	// 測定項目名称（日本語）
	SGr_SOKUT->Cells[3][iPstIndex]	=	tmpKSM02_DATA.KOMK_SUB		;	// 測定項目サブ名称（日本語）
	SGr_SOKUT->Cells[4][iPstIndex]	=	tmpKSM02_DATA.KOMK_ENG		;	// 測定項目名称（英語）
	SGr_SOKUT->Cells[5][iPstIndex]	=	tmpKSM02_DATA.TANI			;	// 単位
	SGr_SOKUT->Cells[6][iPstIndex]	=	""							;	// 規格　※再描画する為に必要です。
	SGr_SOKUT->Cells[7][iPstIndex]	=	tmpKSM02_DATA.SOKU_SU		;	// 測定指示n数
	SGr_SOKUT->Cells[8][iPstIndex]	=	tmpKSM02_DATA.VALUE_TYPE	;	// 測定値表現
	SGr_SOKUT->Cells[9][iPstIndex]	=	tmpKSM02_DATA.KIKI_NM		;	// 測定機器名称
	SGr_SOKUT->Cells[10][iPstIndex]	=	tmpKSM02_DATA.SOKU_FLG		;	// 測定項目の有無
	SGr_SOKUT->Cells[11][iPstIndex]	=	tmpKSM02_DATA.TOKU_FLG		;	// 特別項目の有無
	SGr_SOKUT->Cells[12][iPstIndex]	=	tmpKSM02_DATA.KOMK_NO		;	// 項目NO
	SGr_SOKUT->Cells[13][iPstIndex]	=	tmpKSM02_DATA.UNQ_NO		;	// 明細NO
    if( iOrderNo_UP ){
		SGr_SOKUT->Cells[14][iPstIndex]	=	tmpKSM02_DATA.ORDER_NO	;	// 表示順
    }
	SGr_SOKUT->Cells[15][iPstIndex]	=	tmpKSM02_DATA.SKB_NO		;	// 識別NO
	SGr_SOKUT->Cells[16][iPstIndex]	=	tmpKSM02_DATA.KOMK_SUB_ENG	;	// 測定項目サブ名称（英語）
	SGr_SOKUT->Cells[17][iPstIndex]	=	tmpKSM02_DATA.KIKI_NO		;	// 測定機器NO
	SGr_SOKUT->Cells[18][iPstIndex]	=	tmpKSM02_DATA.KIKA_TYPE		;	// 規格タイプ
	SGr_SOKUT->Cells[19][iPstIndex]	=	tmpKSM02_DATA.KIKA_KIND		;	// 規格種類
	SGr_SOKUT->Cells[20][iPstIndex]	=	tmpKSM02_DATA.KIKA_DECI		;	// 規格小数点以下桁数
	SGr_SOKUT->Cells[21][iPstIndex]	=	tmpKSM02_DATA.KIKA_NUM1		;	// 規格値１
	SGr_SOKUT->Cells[22][iPstIndex]	=	tmpKSM02_DATA.KIKA_NUM2		;	// 規格値２
	SGr_SOKUT->Cells[23][iPstIndex]	=	tmpKSM02_DATA.KIKA_NUM3		;	// 規格値３
	SGr_SOKUT->Cells[24][iPstIndex]	=	tmpKSM02_DATA.KIKA_STR		;	// 規格値文字
	SGr_SOKUT->Cells[25][iPstIndex]	=	tmpKSM02_DATA.KIKA_SUB1		;	// 規格値サブ１
	SGr_SOKUT->Cells[26][iPstIndex]	=	tmpKSM02_DATA.KIKA_SUB2		;	// 規格値サブ２
	SGr_SOKUT->Cells[27][iPstIndex]	=	tmpKSM02_DATA.KIKA_SUB3		;	// 規格値サブ３
	SGr_SOKUT->Cells[28][iPstIndex]	=	tmpKSM02_DATA.KIKA_PRT		;	// 上限下限値の印刷
	SGr_SOKUT->Cells[29][iPstIndex]	=	tmpKSM02_DATA.VALUE_DECI	;	// 測定値小数点以下桁数
    if( sUpdFlg != "" ){
		SGr_SOKUT->Cells[30][iPstIndex] = sUpdFlg				   	;	//更新フラグの設定
    }

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：StringGridを選択した時に発生します。
//
//  機能説明
//    選択（範囲選択）されたTopとBottomを記憶します（SGr_ListRowMovedで利用される）
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
void __fastcall TForm1::SGr_SOKUTClick(TObject *Sender)
{
   	iRowSelTop    = SGr_SOKUT->Selection.Top;
   	iRowSelBottom = SGr_SOKUT->Selection.Bottom;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnKeyPressイベント：StringGridでキーを押したときに発生します。
//
//  機能説明
//    矢印キーによりボタンを選択します
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
void __fastcall TForm1::SGr_ListKeyPress(TObject *Sender, char &Key)
{
     switch(Key)
     {
         // 前項
         case VK_UP:
         case VK_LEFT:  BtnF02Click(Sender);    break;

         // 次項
         case VK_DOWN:
         case VK_RIGHT: BtnF03Click(Sender);    break;

     }

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：StringGridの行の位置が変更された直後に発生します。
//
//  機能説明
//    StringGridで行が移動された（ドラッグ）時の複数行対応処理
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int FromIndex		：移動元の行位置
//    int ToIndex		：移動先の行位置
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_SOKUTRowMoved(TObject *Sender, int FromIndex,
      int ToIndex)
{

    int         i, k, m;
	int			CopyCnt;
    int			iStart;
    int			iEnd;
    int			iSkip;
    HANDLE  	hMemCopy;
    AnsiString  sBuf;
    KSM02_DATA  *pKSM02_DATA;
	TGridRect	myRect;


    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

    // 範囲選択したものと実際に移動処理された行の指定位置が異なる時は、エラー
    if( FromIndex < iRowSelTop || FromIndex > iRowSelBottom ){
        RowExchange( FromIndex,ToIndex);
        // エラーメッセージ
    	MessageDlg("選択範囲が正しくありません。", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	return;
    }

    // 範囲選択した移動先が、その範囲選択内への移動の時は、エラー
    if( ToIndex >= iRowSelTop && ToIndex <= iRowSelBottom ){
        RowExchange( FromIndex,ToIndex);
        // エラーメッセージ
    	MessageDlg("移動先が正しくありません。", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	return;
    }

    // 最下行の下へ移動の時は、エラー
    if( ToIndex >= SGr_SOKUT->RowCount - 1 ){
        RowExchange( FromIndex,ToIndex);
        // エラーメッセージ
    	MessageDlg("移動先が正しくありません。", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	return;
    }

    // 範囲選択したものに最下行を含む時は、エラー
    if( SGr_SOKUT->RowCount - 1 <= iRowSelBottom ){
        RowExchange( FromIndex,ToIndex);
        // エラーメッセージ
    	MessageDlg("選択範囲が正しくありません。", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	return;
    }

    if( FromIndex < ToIndex ){
        iStart = iRowSelTop;
        iEnd   = ToIndex;

		// 表示順を入れ替えます
    	sBuf = SGr_SOKUT->Cells[14][ToIndex];
		for( i = ToIndex; i > FromIndex; i-- ){
			SGr_SOKUT->Cells[14][i] = SGr_SOKUT->Cells[14][i-1];
    	}
    	SGr_SOKUT->Cells[14][FromIndex] = sBuf;
    }
    else {
        iStart = ToIndex;
        iEnd   = iRowSelBottom;

		// 表示順を入れ替えます
        sBuf = SGr_SOKUT->Cells[14][ToIndex];
		for( i = ToIndex; i < FromIndex; i++ ){
			SGr_SOKUT->Cells[14][i] = SGr_SOKUT->Cells[14][i+1];
    	}
    	SGr_SOKUT->Cells[14][FromIndex] = sBuf;
    }

	// 行Noを元に戻します
	for( i = iStart; i <= iEnd; i++ ){
		sBuf = i ;
		if( i < SGr_SOKUT->RowCount - 1 ){
			SGr_SOKUT->Cells[0][i] = AnsiString::StringOfChar(' ', 2-sBuf.Length()) + sBuf;
   	    	SGr_SOKUT->Cells[30][i] = "1";						// 更新フラグON
		}
        else{
			SGr_SOKUT->Cells[0][i] = "";
   	    	SGr_SOKUT->Cells[30][i] = "";
        }
    }

    // コピーの個数を確保します
    CopyCnt = iRowSelBottom - iRowSelTop;

    // メモリの確保
    hMemCopy = GlobalAlloc( GHND, sizeof(struct KSM02_DATA) * CopyCnt );
    if( hMemCopy == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        SBr1->Update();
        Beep();
        return;
    }
    pKSM02_DATA = (struct KSM02_DATA *)GlobalLock(hMemCopy);
    if( hMemCopy == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        SBr1->Update();
        Beep();
        return;
    }

    if( FromIndex < ToIndex ){

	    // 選択されている範囲をメモリに格納します
    	for( i=iRowSelTop, k=0; i<iRowSelBottom; i++, k++ ) {
			//strcpy( pKSM02_DATA[k].DTKSHIN	,sBuf.c_str() );	// 代表得意先品番
			//strcpy( pKSM02_DATA[k].REVCNT		,sBuf.c_str() );	// 改訂番号
			sBuf = SGr_SOKUT->Cells[13][i];
			strcpy( pKSM02_DATA[k].UNQ_NO		,sBuf.c_str() );	// 明細NO
			sBuf = SGr_SOKUT->Cells[14][i];
			strcpy( pKSM02_DATA[k].ORDER_NO		,sBuf.c_str() );	// 表示順
			sBuf = SGr_SOKUT->Cells[15][i];
			strcpy( pKSM02_DATA[k].SKB_NO		,sBuf.c_str() );	// 識別NO
			sBuf = SGr_SOKUT->Cells[1][i];
			strcpy( pKSM02_DATA[k].HINBAN_SK	,sBuf.c_str() );	// 品番
			sBuf = SGr_SOKUT->Cells[12][i];
			strcpy( pKSM02_DATA[k].KOMK_NO		,sBuf.c_str() );	// 項目NO
			sBuf = SGr_SOKUT->Cells[2][i];
			strcpy( pKSM02_DATA[k].KOMK_NM		,sBuf.c_str() );	// 測定項目名称（日本語）
			sBuf = SGr_SOKUT->Cells[4][i];
			strcpy( pKSM02_DATA[k].KOMK_ENG		,sBuf.c_str() );	// 測定項目名称（英語）
			sBuf = SGr_SOKUT->Cells[3][i];
			strcpy( pKSM02_DATA[k].KOMK_SUB		,sBuf.c_str() );	// 測定項目サブ名称（日本語）
			sBuf = SGr_SOKUT->Cells[16][i];
			strcpy( pKSM02_DATA[k].KOMK_SUB_ENG	,sBuf.c_str() );	// 測定項目サブ名称（英語）
			sBuf = SGr_SOKUT->Cells[17][i];
			strcpy( pKSM02_DATA[k].KIKI_NO		,sBuf.c_str() );	// 測定機器NO
			sBuf = SGr_SOKUT->Cells[9][i];
			strcpy( pKSM02_DATA[k].KIKI_NM		,sBuf.c_str() );	// 測定機器名称
			sBuf = SGr_SOKUT->Cells[5][i];
			strcpy( pKSM02_DATA[k].TANI			,sBuf.c_str() );	// 単位
			sBuf = SGr_SOKUT->Cells[18][i];
			strcpy( pKSM02_DATA[k].KIKA_TYPE	,sBuf.c_str() );	// 規格タイプ
			sBuf = SGr_SOKUT->Cells[19][i];
			strcpy( pKSM02_DATA[k].KIKA_KIND	,sBuf.c_str() );	// 規格種類
			sBuf = SGr_SOKUT->Cells[20][i];
			strcpy( pKSM02_DATA[k].KIKA_DECI	,sBuf.c_str() );	// 規格小数点以下桁数
			sBuf = SGr_SOKUT->Cells[21][i];
			strcpy( pKSM02_DATA[k].KIKA_NUM1	,sBuf.c_str() );	// 規格値１
			sBuf = SGr_SOKUT->Cells[22][i];
			strcpy( pKSM02_DATA[k].KIKA_NUM2	,sBuf.c_str() );	// 規格値２
			sBuf = SGr_SOKUT->Cells[23][i];
			strcpy( pKSM02_DATA[k].KIKA_NUM3	,sBuf.c_str() );	// 規格値３
			sBuf = SGr_SOKUT->Cells[24][i];
			strcpy( pKSM02_DATA[k].KIKA_STR		,sBuf.c_str() );	// 規格値文字
			sBuf = SGr_SOKUT->Cells[25][i];
			strcpy( pKSM02_DATA[k].KIKA_SUB1	,sBuf.c_str() );	// 規格値サブ１
			sBuf = SGr_SOKUT->Cells[26][i];
			strcpy( pKSM02_DATA[k].KIKA_SUB2	,sBuf.c_str() );	// 規格値サブ２
			sBuf = SGr_SOKUT->Cells[27][i];
			strcpy( pKSM02_DATA[k].KIKA_SUB3	,sBuf.c_str() );	// 規格値サブ３
			sBuf = SGr_SOKUT->Cells[7][i];
			strcpy( pKSM02_DATA[k].SOKU_SU		,sBuf.c_str() );	// 測定指示n数
			sBuf = SGr_SOKUT->Cells[10][i];
			strcpy( pKSM02_DATA[k].SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
			sBuf = SGr_SOKUT->Cells[11][i];
			strcpy( pKSM02_DATA[k].TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
			sBuf = SGr_SOKUT->Cells[28][i];
			strcpy( pKSM02_DATA[k].KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
			sBuf = SGr_SOKUT->Cells[8][i];
			strcpy( pKSM02_DATA[k].VALUE_TYPE	,sBuf.c_str() );	// 測定値表現
			sBuf = SGr_SOKUT->Cells[29][i];
			strcpy( pKSM02_DATA[k].VALUE_DECI	,sBuf.c_str() );	// 測定値小数点以下桁数
    	}

		// 複数選択内容を移動します
		for( i = iRowSelBottom; i <= ToIndex; i++ ){
	    	for( k = 1; k < SGr_SOKUT->ColCount; k++ ) {
	            if( k == 14 ){
	                // 表示順は、入れ替えしない
	    			// SGr_SOKUT->Cells[k][i-CopyCnt] = SGr_SOKUT->Cells[k][i];
	        	} else {
					SGr_SOKUT->Cells[k][i-CopyCnt] = SGr_SOKUT->Cells[k][i];
	            }
			}
    	}

        // 自動移動された行を正しい位置に移動します。
        iSkip = FromIndex - iRowSelTop;
        if( iSkip != 0 ){
	    	for( k = 1; k < SGr_SOKUT->ColCount; k++ ) {
	            if( k == 14 ){
	                // 表示順は、入れ替えしない
	    			// SGr_SOKUT->Cells[k][ToIndex-CopyCnt+iSkip] = SGr_SOKUT->Cells[k][ToIndex];
	        	} else {
					SGr_SOKUT->Cells[k][ToIndex-CopyCnt+iSkip] = SGr_SOKUT->Cells[k][ToIndex];
	            }
			}
        }

		// メモリに格納した内容を戻します
        i = ToIndex - CopyCnt;
		for( k = 0, m = 0; k <= CopyCnt; k++ ){
            if( k != iSkip ){
				//								pKSM02_DATA[m].DTKSHIN		;	// 代表得意先品番
				//								pKSM02_DATA[m].REVCNT		;	// 改訂番号
				SGr_SOKUT->Cells[1][i+k]	=	pKSM02_DATA[m].HINBAN_SK	;	// 品番
				SGr_SOKUT->Cells[2][i+k]	=	pKSM02_DATA[m].KOMK_NM		;	// 測定項目名称（日本語）
				SGr_SOKUT->Cells[3][i+k]	=	pKSM02_DATA[m].KOMK_SUB		;	// 測定項目サブ名称（日本語）
				SGr_SOKUT->Cells[4][i+k]	=	pKSM02_DATA[m].KOMK_ENG		;	// 測定項目名称（英語）
				SGr_SOKUT->Cells[5][i+k]	=	pKSM02_DATA[m].TANI			;	// 単位
				SGr_SOKUT->Cells[6][i+k]	=	""							;	// 規格　※再描画する為に必要です。
				SGr_SOKUT->Cells[7][i+k]	=	pKSM02_DATA[m].SOKU_SU		;	// 測定指示n数
				SGr_SOKUT->Cells[8][i+k]	=	pKSM02_DATA[m].VALUE_TYPE	;	// 測定値表現
				SGr_SOKUT->Cells[9][i+k]	=	pKSM02_DATA[m].KIKI_NM		;	// 測定機器名称
				SGr_SOKUT->Cells[10][i+k]	=	pKSM02_DATA[m].SOKU_FLG		;	// 測定項目の有無
				SGr_SOKUT->Cells[11][i+k]	=	pKSM02_DATA[m].TOKU_FLG		;	// 特別項目の有無
				SGr_SOKUT->Cells[12][i+k]	=	pKSM02_DATA[m].KOMK_NO		;	// 項目NO
				SGr_SOKUT->Cells[13][i+k]	=	pKSM02_DATA[m].UNQ_NO		;	// 明細NO
				//SGr_SOKUT->Cells[14][i+k]	=	pKSM02_DATA[m].ORDER_NO		;	// 表示順
				SGr_SOKUT->Cells[15][i+k]	=	pKSM02_DATA[m].SKB_NO		;	// 識別NO
				SGr_SOKUT->Cells[16][i+k]	=	pKSM02_DATA[m].KOMK_SUB_ENG	;	// 測定項目サブ名称（英語）
				SGr_SOKUT->Cells[17][i+k]	=	pKSM02_DATA[m].KIKI_NO		;	// 測定機器NO
				SGr_SOKUT->Cells[18][i+k]	=	pKSM02_DATA[m].KIKA_TYPE	;	// 規格タイプ
				SGr_SOKUT->Cells[19][i+k]	=	pKSM02_DATA[m].KIKA_KIND	;	// 規格種類
				SGr_SOKUT->Cells[20][i+k]	=	pKSM02_DATA[m].KIKA_DECI	;	// 規格小数点以下桁数
				SGr_SOKUT->Cells[21][i+k]	=	pKSM02_DATA[m].KIKA_NUM1	;	// 規格値１
				SGr_SOKUT->Cells[22][i+k]	=	pKSM02_DATA[m].KIKA_NUM2	;	// 規格値２
				SGr_SOKUT->Cells[23][i+k]	=	pKSM02_DATA[m].KIKA_NUM3	;	// 規格値３
				SGr_SOKUT->Cells[24][i+k]	=	pKSM02_DATA[m].KIKA_STR		;	// 規格値文字
				SGr_SOKUT->Cells[25][i+k]	=	pKSM02_DATA[m].KIKA_SUB1	;	// 規格値サブ１
				SGr_SOKUT->Cells[26][i+k]	=	pKSM02_DATA[m].KIKA_SUB2	;	// 規格値サブ２
				SGr_SOKUT->Cells[27][i+k]	=	pKSM02_DATA[m].KIKA_SUB3	;	// 規格値サブ３
				SGr_SOKUT->Cells[28][i+k]	=	pKSM02_DATA[m].KIKA_PRT		;	// 上限下限値の印刷
				SGr_SOKUT->Cells[29][i+k]	=	pKSM02_DATA[m].VALUE_DECI	;	// 測定値小数点以下桁数
				SGr_SOKUT->Cells[30][i+k]	=	"1"							;	//更新フラグの設定
				m++;
        	}
        }

    	// 移動先の行を選択範囲を決定します
		myRect.Left		= SGr_SOKUT->Selection.Left;
		myRect.Top		= ToIndex - CopyCnt;
		myRect.Right	= SGr_SOKUT->Selection.Right;
		myRect.Bottom	= myRect.Top + CopyCnt;
    }
    else {

	    // 選択されている範囲をメモリに格納します
    	for( i=iRowSelTop+1, k=0; i<=iRowSelBottom; i++, k++ ) {
			//strcpy( pKSM02_DATA[k].DTKSHIN	,sBuf.c_str() );	// 代表得意先品番
			//strcpy( pKSM02_DATA[k].REVCNT		,sBuf.c_str() );	// 改訂番号
			sBuf = SGr_SOKUT->Cells[13][i];
			strcpy( pKSM02_DATA[k].UNQ_NO		,sBuf.c_str() );	// 明細NO
			sBuf = SGr_SOKUT->Cells[14][i];
			strcpy( pKSM02_DATA[k].ORDER_NO		,sBuf.c_str() );	// 表示順
			sBuf = SGr_SOKUT->Cells[15][i];
			strcpy( pKSM02_DATA[k].SKB_NO		,sBuf.c_str() );	// 識別NO
			sBuf = SGr_SOKUT->Cells[1][i];
			strcpy( pKSM02_DATA[k].HINBAN_SK	,sBuf.c_str() );	// 品番
			sBuf = SGr_SOKUT->Cells[12][i];
			strcpy( pKSM02_DATA[k].KOMK_NO		,sBuf.c_str() );	// 項目NO
			sBuf = SGr_SOKUT->Cells[2][i];
			strcpy( pKSM02_DATA[k].KOMK_NM		,sBuf.c_str() );	// 測定項目名称（日本語）
			sBuf = SGr_SOKUT->Cells[4][i];
			strcpy( pKSM02_DATA[k].KOMK_ENG		,sBuf.c_str() );	// 測定項目名称（英語）
			sBuf = SGr_SOKUT->Cells[3][i];
			strcpy( pKSM02_DATA[k].KOMK_SUB		,sBuf.c_str() );	// 測定項目サブ名称（日本語）
			sBuf = SGr_SOKUT->Cells[16][i];
			strcpy( pKSM02_DATA[k].KOMK_SUB_ENG	,sBuf.c_str() );	// 測定項目サブ名称（英語）
			sBuf = SGr_SOKUT->Cells[17][i];
			strcpy( pKSM02_DATA[k].KIKI_NO		,sBuf.c_str() );	// 測定機器NO
			sBuf = SGr_SOKUT->Cells[9][i];
			strcpy( pKSM02_DATA[k].KIKI_NM		,sBuf.c_str() );	// 測定機器名称
			sBuf = SGr_SOKUT->Cells[5][i];
			strcpy( pKSM02_DATA[k].TANI			,sBuf.c_str() );	// 単位
			sBuf = SGr_SOKUT->Cells[18][i];
			strcpy( pKSM02_DATA[k].KIKA_TYPE	,sBuf.c_str() );	// 規格タイプ
			sBuf = SGr_SOKUT->Cells[19][i];
			strcpy( pKSM02_DATA[k].KIKA_KIND	,sBuf.c_str() );	// 規格種類
			sBuf = SGr_SOKUT->Cells[20][i];
			strcpy( pKSM02_DATA[k].KIKA_DECI	,sBuf.c_str() );	// 規格小数点以下桁数
			sBuf = SGr_SOKUT->Cells[21][i];
			strcpy( pKSM02_DATA[k].KIKA_NUM1	,sBuf.c_str() );	// 規格値１
			sBuf = SGr_SOKUT->Cells[22][i];
			strcpy( pKSM02_DATA[k].KIKA_NUM2	,sBuf.c_str() );	// 規格値２
			sBuf = SGr_SOKUT->Cells[23][i];
			strcpy( pKSM02_DATA[k].KIKA_NUM3	,sBuf.c_str() );	// 規格値３
			sBuf = SGr_SOKUT->Cells[24][i];
			strcpy( pKSM02_DATA[k].KIKA_STR		,sBuf.c_str() );	// 規格値文字
			sBuf = SGr_SOKUT->Cells[25][i];
			strcpy( pKSM02_DATA[k].KIKA_SUB1	,sBuf.c_str() );	// 規格値サブ１
			sBuf = SGr_SOKUT->Cells[26][i];
			strcpy( pKSM02_DATA[k].KIKA_SUB2	,sBuf.c_str() );	// 規格値サブ２
			sBuf = SGr_SOKUT->Cells[27][i];
			strcpy( pKSM02_DATA[k].KIKA_SUB3	,sBuf.c_str() );	// 規格値サブ３
			sBuf = SGr_SOKUT->Cells[7][i];
			strcpy( pKSM02_DATA[k].SOKU_SU		,sBuf.c_str() );	// 測定指示n数
			sBuf = SGr_SOKUT->Cells[10][i];
			strcpy( pKSM02_DATA[k].SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
			sBuf = SGr_SOKUT->Cells[11][i];
			strcpy( pKSM02_DATA[k].TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
			sBuf = SGr_SOKUT->Cells[28][i];
			strcpy( pKSM02_DATA[k].KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
			sBuf = SGr_SOKUT->Cells[8][i];
			strcpy( pKSM02_DATA[k].VALUE_TYPE	,sBuf.c_str() );	// 測定値表現
			sBuf = SGr_SOKUT->Cells[29][i];
			strcpy( pKSM02_DATA[k].VALUE_DECI	,sBuf.c_str() );	// 測定値小数点以下桁数
    	}

		// 複数選択内容を移動します
		for( i = iRowSelTop; i >= ToIndex; i-- ){
	    	for( k = 1; k < SGr_SOKUT->ColCount; k++ ) {
	            if( k == 14 ){
	                // 表示順は、入れ替えしない
	    			// SGr_SOKUT->Cells[k][i+CopyCnt] = SGr_SOKUT->Cells[k][i];
	        	} else {
					SGr_SOKUT->Cells[k][i+CopyCnt] = SGr_SOKUT->Cells[k][i];
	            }
			}
    	}

        // 自動移動された行を正しい位置に移動します。
        iSkip = FromIndex - iRowSelTop;
        if( iSkip != 0 ){
	    	for( k = 1; k < SGr_SOKUT->ColCount; k++ ) {
	            if( k == 14 ){
	                // 表示順は、入れ替えしない
	    			// SGr_SOKUT->Cells[k][ToIndex+iSkip] = SGr_SOKUT->Cells[k][ToIndex];
	        	} else {
					SGr_SOKUT->Cells[k][ToIndex+iSkip] = SGr_SOKUT->Cells[k][ToIndex];
	            }
			}
        }

		// メモリに格納した内容を戻します
        i = ToIndex;
		for( k = 0, m = 0; k <= CopyCnt; k++ ){
            if( k != iSkip ){
				//								pKSM02_DATA[m].DTKSHIN		;	// 代表得意先品番
				//								pKSM02_DATA[m].REVCNT		;	// 改訂番号
				SGr_SOKUT->Cells[1][i+k]	=	pKSM02_DATA[m].HINBAN_SK	;	// 品番
				SGr_SOKUT->Cells[2][i+k]	=	pKSM02_DATA[m].KOMK_NM		;	// 測定項目名称（日本語）
				SGr_SOKUT->Cells[3][i+k]	=	pKSM02_DATA[m].KOMK_SUB		;	// 測定項目サブ名称（日本語）
				SGr_SOKUT->Cells[4][i+k]	=	pKSM02_DATA[m].KOMK_ENG		;	// 測定項目名称（英語）
				SGr_SOKUT->Cells[5][i+k]	=	pKSM02_DATA[m].TANI			;	// 単位
				SGr_SOKUT->Cells[6][i+k]	=	""							;	// 規格　※再描画する為に必要です。
				SGr_SOKUT->Cells[7][i+k]	=	pKSM02_DATA[m].SOKU_SU		;	// 測定指示n数
				SGr_SOKUT->Cells[8][i+k]	=	pKSM02_DATA[m].VALUE_TYPE	;	// 測定値表現
				SGr_SOKUT->Cells[9][i+k]	=	pKSM02_DATA[m].KIKI_NM		;	// 測定機器名称
				SGr_SOKUT->Cells[10][i+k]	=	pKSM02_DATA[m].SOKU_FLG		;	// 測定項目の有無
				SGr_SOKUT->Cells[11][i+k]	=	pKSM02_DATA[m].TOKU_FLG		;	// 特別項目の有無
				SGr_SOKUT->Cells[12][i+k]	=	pKSM02_DATA[m].KOMK_NO		;	// 項目NO
				SGr_SOKUT->Cells[13][i+k]	=	pKSM02_DATA[m].UNQ_NO		;	// 明細NO
				//SGr_SOKUT->Cells[14][i+k]	=	pKSM02_DATA[m].ORDER_NO		;	// 表示順
				SGr_SOKUT->Cells[15][i+k]	=	pKSM02_DATA[m].SKB_NO		;	// 識別NO
				SGr_SOKUT->Cells[16][i+k]	=	pKSM02_DATA[m].KOMK_SUB_ENG	;	// 測定項目サブ名称（英語）
				SGr_SOKUT->Cells[17][i+k]	=	pKSM02_DATA[m].KIKI_NO		;	// 測定機器NO
				SGr_SOKUT->Cells[18][i+k]	=	pKSM02_DATA[m].KIKA_TYPE	;	// 規格タイプ
				SGr_SOKUT->Cells[19][i+k]	=	pKSM02_DATA[m].KIKA_KIND	;	// 規格種類
				SGr_SOKUT->Cells[20][i+k]	=	pKSM02_DATA[m].KIKA_DECI	;	// 規格小数点以下桁数
				SGr_SOKUT->Cells[21][i+k]	=	pKSM02_DATA[m].KIKA_NUM1	;	// 規格値１
				SGr_SOKUT->Cells[22][i+k]	=	pKSM02_DATA[m].KIKA_NUM2	;	// 規格値２
				SGr_SOKUT->Cells[23][i+k]	=	pKSM02_DATA[m].KIKA_NUM3	;	// 規格値３
				SGr_SOKUT->Cells[24][i+k]	=	pKSM02_DATA[m].KIKA_STR		;	// 規格値文字
				SGr_SOKUT->Cells[25][i+k]	=	pKSM02_DATA[m].KIKA_SUB1	;	// 規格値サブ１
				SGr_SOKUT->Cells[26][i+k]	=	pKSM02_DATA[m].KIKA_SUB2	;	// 規格値サブ２
				SGr_SOKUT->Cells[27][i+k]	=	pKSM02_DATA[m].KIKA_SUB3	;	// 規格値サブ３
				SGr_SOKUT->Cells[28][i+k]	=	pKSM02_DATA[m].KIKA_PRT		;	// 上限下限値の印刷
				SGr_SOKUT->Cells[29][i+k]	=	pKSM02_DATA[m].VALUE_DECI	;	// 測定値小数点以下桁数
				SGr_SOKUT->Cells[30][i+k]	=	"1"							;	//更新フラグの設定
				m++;
        	}
        }

    	// 移動先の行を選択範囲を決定します
		myRect.Left		= SGr_SOKUT->Selection.Left;
		myRect.Top		= ToIndex;
		myRect.Right	= SGr_SOKUT->Selection.Right;
		myRect.Bottom	= ToIndex + CopyCnt;
    }

    // メモリの開放
    if( hMemCopy ){
        GlobalUnlock( hMemCopy );
        GlobalFree( hMemCopy );
    }


    // 移動先の行を選択します
    SGr_SOKUT->Row   		= myRect.Top;
    SGr_SOKUT->Selection	= myRect;
    //SGr_ListSelectCell(Sender,1,SGr_SOKUT->Row,true);

    iRowSelTop    = SGr_SOKUT->Selection.Top;
    iRowSelBottom = SGr_SOKUT->Selection.Bottom;

    // データを変更したフラグ
    DataSave = true;
    BtnF11->Enabled = true;

    // データ変更フラグの設定
    DataChange = 1;

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：一行だけ行の入れ替え処理を行ないます。
//
//  機能説明
//    指定した行同士の入れ替え処理を行ないます
//
//  パラメタ説明
//    int FromIndex		：移動元の行位置
//    int ToIndex		：移動先の行位置
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::RowExchange( int FromIndex, int ToIndex)
{
    int			i, k;
	TGridRect	myRect;
    AnsiString	sBuf;
    AnsiString	sLineNo;


    // 入れ替え先のデータをバックアップ
    sLineNo = SGr_SOKUT->Cells[0][ToIndex];						//行番号
	sBuf = SGr_SOKUT_GridLineCopy( ToIndex );

    if( ToIndex > FromIndex ){
		// 上下を入れ替えます
    	for( i=ToIndex; i>FromIndex; i-- ) {
	    	for( k = 0; k < SGr_SOKUT->ColCount; k++ ) {
				SGr_SOKUT->Cells[k][i] = SGr_SOKUT->Cells[k][i-1];
			}
    	}
    }
    else{
		// 上下を入れ替えます
    	for( i=ToIndex; i<FromIndex; i++ ) {
	    	for( k = 0; k < SGr_SOKUT->ColCount; k++ ) {
				SGr_SOKUT->Cells[k][i] = SGr_SOKUT->Cells[k][i+1];
			}
    	}
    }

    // バックアップしたデータを戻します（表示順も戻します）
    SGr_SOKUT->Cells[0][FromIndex] = sLineNo						;	//行番号
	SGr_SOKUT_GridLinePaste( FromIndex, sBuf, true );


    // 選択し直します
    //SGr_List->Row	= iRowSelTop;
	myRect.Left		= SGr_SOKUT->Selection.Left;
	myRect.Top		= iRowSelTop;
	myRect.Right	= SGr_SOKUT->Selection.Right;
	myRect.Bottom	= iRowSelBottom;
    SGr_SOKUT->Selection	= myRect;
    //SGr_ListSelectCell(Sender,1,SGr_SOKUT->Row,true);

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：StringGrid（下）にデータを追加します
//
//  機能説明
//    StringGrid（下）にKSM02構造体のデータを指定した行No(iRow)に追加します
//
//  パラメタ説明
//    int iRow			：追加先の位置
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Ins_SGr_SOKUT(int iRow)
{

    int			i, k;
    int			iSOKUT_UNQ_NO_MAX;
    int			iSOKUT_ORDER_NO_MAX;
    AnsiString	sBuf;


    // 最大登録件数のチェック
    if( SGr_SOKUT->RowCount - 2 >= 99 ){
        MessageDlg( "最大測定項目99件を超えています。登録できません。",
                    mtWarning	, TMsgDlgButtons() << mbOK, 0);
    	return;
    }

    // 一行増やす
	SGr_SOKUT->RowCount = SGr_SOKUT->RowCount + 1;

    // 行Noを付ける
	sBuf = IntToStr(SGr_SOKUT->RowCount-2);
	SGr_SOKUT->Cells[0][SGr_SOKUT->RowCount-2] = AnsiString::StringOfChar(' ', 2-sBuf.Length()) + sBuf;
    Pnl_SOKUTEI_NUM->Caption = sBuf;		// 項目数の更新

    // 最下行をクリアー
	for( k = 0; k < SGr_SOKUT->ColCount; k++) {
		SGr_SOKUT->Cells[k][SGr_SOKUT->RowCount-1] = "";
	}

    // 新しく追加する行の「明細NO」と「表示順」を決定します
    iSOKUT_UNQ_NO_MAX = 0;
    iSOKUT_ORDER_NO_MAX = 0;
    for( i = 1; i < SGr_SOKUT->RowCount - 1; i++ ){
   	    // 最大の明細NOを取得します
        sBuf = SGr_SOKUT->Cells[13][i];
   	    if( sBuf.ToIntDef(0) > iSOKUT_UNQ_NO_MAX ){
   	        iSOKUT_UNQ_NO_MAX = sBuf.ToIntDef(0);
   	    }
   	    // 最大の表示順を取得します
        sBuf = Form1->SGr_SOKUT->Cells[14][i];
   	    if( sBuf.ToIntDef(0) > iSOKUT_ORDER_NO_MAX ){
   	        iSOKUT_ORDER_NO_MAX = sBuf.ToIntDef(0);
   	    }
    }

    // 「明細NO」を決定します
    iSOKUT_UNQ_NO_MAX++;
    sBuf = IntToStr(iSOKUT_UNQ_NO_MAX);
	strcpy( tmpKSM02_DATA.UNQ_NO, sBuf.c_str() );

    // 「表示順」の決定と、追加行以下のデータを移動します
    if( iRow >= SGr_SOKUT->RowCount - 2 ){
        // 追加するデータが最下行の時

        // 「表示順」を決定します
        iSOKUT_ORDER_NO_MAX++;
        sBuf = IntToStr(iSOKUT_ORDER_NO_MAX);
	    strcpy( tmpKSM02_DATA.ORDER_NO, sBuf.c_str() );

    }
    else {
        // 追加するデータが既存データ途中への挿入の時

        // 「表示順」を決定します
        k = SGr_SOKUT->Cells[14][iRow].ToIntDef(0);
        sBuf = k;
	    strcpy( tmpKSM02_DATA.ORDER_NO, sBuf.c_str() );

        // 追加データの表示順より同じか大きい物を表示順＋１します
	    for( i = 1; i < SGr_SOKUT->RowCount - 1; i++) {
            if( SGr_SOKUT->Cells[14][i].ToIntDef(0) >= k ){
			    SGr_SOKUT->Cells[14][i] = IntToStr(SGr_SOKUT->Cells[14][i].ToIntDef(0) + 1);
			    SGr_SOKUT->Cells[30][i] = "1";		// 更新フラグもON
    	    }
	    }

        // 新規データ行以下の行をずらします
	    for( i = SGr_SOKUT->RowCount - 2; i > iRow; i--) {
		    for( k = 1; k < SGr_SOKUT->ColCount; k++) {
			    SGr_SOKUT->Cells[k][i] = SGr_SOKUT->Cells[k][i-1];
    	    }
	    }

    }

    // バックアップしたデータを戻します（表示順も戻します）
	SGr_SOKUT_GridLinePaste( iRow, "1", true );

    SGr_SOKUT->Row = iRow;

    // データ変更フラグの設定
    DataChange = 1;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Space追加」ボタンを押した時の処理
//
//  機能説明
//    StringGrid（下）で選択された行にSpace（空白行）を挿入します
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
void __fastcall TForm1::Btn_ADD_SPClick(TObject *Sender)
{

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

	AnsiString	sBuf;

	// 「スペース」データの作成
    sBuf = Edt_DTKSHIN->Text;
	strcpy( tmpKSM02_DATA.DTKSHIN		,sBuf.c_str() );	// 代表得意先品番
    sBuf = "0";
	strcpy( tmpKSM02_DATA.REVCNT		,sBuf.c_str() );	// 改訂番号
    //sBuf = iSOKUT_UNQ_NO_MAX++ ;
	//strcpy( tmpKSM02_DATA.UNQ_NO		,sBuf.c_str() );	// 明細NO
    //sBuf = iSOKUT_ORDER_NO_MAX++ ;
	//strcpy( tmpKSM02_DATA.ORDER_NO	,sBuf.c_str() );	// 表示順
    sBuf = "9";
	strcpy( tmpKSM02_DATA.SKB_NO		,sBuf.c_str() );	// 識別NO
    sBuf = " ";
	strcpy( tmpKSM02_DATA.HINBAN_SK		,sBuf.c_str() );	// 品番
	sBuf = "0";
	strcpy( tmpKSM02_DATA.KOMK_NO		,sBuf.c_str() );	// 項目NO
    sBuf = " ";
	strcpy( tmpKSM02_DATA.KOMK_NM		,sBuf.c_str() );	// 測定項目名称（日本語）
    sBuf = " ";
	strcpy( tmpKSM02_DATA.KOMK_ENG		,sBuf.c_str() );	// 測定項目名称（英語）
	sBuf = "";
	strcpy( tmpKSM02_DATA.KOMK_SUB		,sBuf.c_str() );	// 測定項目サブ名称（日本語）
	sBuf = "";
	strcpy( tmpKSM02_DATA.KOMK_SUB_ENG	,sBuf.c_str() );	// 測定項目サブ名称（英語）
    sBuf = "0";
	strcpy( tmpKSM02_DATA.KIKI_NO		,sBuf.c_str() );	// 測定機器NO
    sBuf = " ";
	strcpy( tmpKSM02_DATA.KIKI_NM		,sBuf.c_str() );	// 測定機器名称
    sBuf = " ";
	strcpy( tmpKSM02_DATA.TANI			,sBuf.c_str() );	// 単位
    sBuf = "0";
	strcpy( tmpKSM02_DATA.KIKA_TYPE		,sBuf.c_str() );	// 規格タイプ
    sBuf = "0";
	strcpy( tmpKSM02_DATA.KIKA_KIND		,sBuf.c_str() );	// 規格種類
    sBuf = "0";
	strcpy( tmpKSM02_DATA.KIKA_DECI		,sBuf.c_str() );	// 規格小数点以下桁数
    sBuf = "0";
	strcpy( tmpKSM02_DATA.KIKA_NUM1		,sBuf.c_str() );	// 規格値１
    sBuf = "0";
	strcpy( tmpKSM02_DATA.KIKA_NUM2		,sBuf.c_str() );	// 規格値２
    sBuf = "0";
	strcpy( tmpKSM02_DATA.KIKA_NUM3		,sBuf.c_str() );	// 規格値３
    sBuf = " ";
	strcpy( tmpKSM02_DATA.KIKA_STR		,sBuf.c_str() );	// 規格値文字
    sBuf = "0";
	strcpy( tmpKSM02_DATA.SOKU_SU		,sBuf.c_str() );	// 測定指示n数
    sBuf = "0";
	strcpy( tmpKSM02_DATA.SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
    sBuf = "0";
	strcpy( tmpKSM02_DATA.TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
    sBuf = "0";
	strcpy( tmpKSM02_DATA.KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
    sBuf = "0";
	strcpy( tmpKSM02_DATA.VALUE_TYPE	,sBuf.c_str() );	// 測定値表現
    sBuf = "0";
	strcpy( tmpKSM02_DATA.VALUE_DECI	,sBuf.c_str() );	// 測定値小数点以下桁数

    // 空白を挿入します
    Ins_SGr_SOKUT(SGr_SOKUT->Row);

	// 新しい行を選択
	SGr_SOKUT->SetFocus();
    SGr_SOKUTClick( SGr_SOKUT );

    // データ変更フラグの設定
    DataChange = 1;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「削除」ボタンを押した時の処理
//
//  機能説明
//    StringGrid（下）で選択された行を削除します
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
void __fastcall TForm1::Btn_DELClick(TObject *Sender)
{

    int			i, k;
    int			iDelCnt;
    AnsiString	sBuf;
	int			iChgRow1;
	int			iChgRow3;

    iChgRow1 = SGr_SOKUT->Selection.Top;
    iChgRow3 = SGr_SOKUT->Selection.Bottom;

    if( SGr_SOKUT->RowCount <= 2) return;
    if( iChgRow1 == SGr_SOKUT->RowCount - 1) return;

    if( iChgRow3 >= SGr_SOKUT->RowCount - 1)
    	iChgRow3 = SGr_SOKUT->Selection.Bottom = SGr_SOKUT->RowCount - 2;

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

    // 削除する個数を計算します
    iDelCnt = (iChgRow3 - iChgRow1) + 1;

    // 追加データの表示順より同じか大きい物を表示順－１します
	for( i = 1; i < SGr_SOKUT->RowCount - 1; i++) {
        if( SGr_SOKUT->Cells[14][i].ToIntDef(0) >= SGr_SOKUT->Cells[14][iChgRow1].ToIntDef(0) ){
			SGr_SOKUT->Cells[14][i] = IntToStr(SGr_SOKUT->Cells[14][i].ToIntDef(-1) - iDelCnt);
			SGr_SOKUT->Cells[30][i] = "1";		// 更新フラグもON
    	}
	}

    // 削除行以下の行を1つ上にずらします
	for( i = iChgRow1; i < (SGr_SOKUT->RowCount - iDelCnt); i++) {
		for( k = 1; k < SGr_SOKUT->ColCount; k++) {
			SGr_SOKUT->Cells[k][i] = SGr_SOKUT->Cells[k][i+iDelCnt];
    	}
	}

	// 一行減らす
	SGr_SOKUT->RowCount = SGr_SOKUT->RowCount - iDelCnt;
	// 最下行をクリアー
	for( k = 0; k < SGr_SOKUT->ColCount; k++) {
		SGr_SOKUT->Cells[k][SGr_SOKUT->RowCount - 1] = "";
	}

	// 新しい行を選択
	SGr_SOKUT->SetFocus();
    SGr_SOKUTClick( SGr_SOKUT );

    // データ件数を表示します
	sBuf = IntToStr(SGr_SOKUT->RowCount-2);
    Pnl_SOKUTEI_NUM->Caption = sBuf;		// 項目数の更新

    // データ変更フラグの設定
    DataChange = 1;

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：StringGrid（下）のデータをコピーします（複数行対応）
//
//  機能説明
//    StringGrid（下）の測定項目データをcpyKSM02_DATAにコピーします
//    測定項目StringGridで[Ctrl]+[C]を押した時の測定項目データのコピー処理
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    bool				：true  = コピー成功
//						　false = コピー失敗
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::SGr_SOKUT_GridMultiLineCopy()
{

    int         i;
    int			cnt;
    AnsiString  sBuf;


    // 範囲選択したものに最下行を含む時は、エラー又は-1
    if( SGr_SOKUT->RowCount - 1 <= iRowSelBottom ){
        if( iRowSelTop > (iRowSelBottom - 1) ){
        	// エラーメッセージ
    		MessageDlg("コピー対象の行ではありません。", mtWarning,
        	            TMsgDlgButtons() << mbOK , 0);
    		return(false);
        }
        iRowSelBottom = iRowSelBottom - 1;
    }

    // コピーの個数を確保します
    iCntCpyKSM02_DATA = iRowSelBottom - iRowSelTop + 1;

    if( iCntCpyKSM02_DATA == 0 )	return(false);

    // メモリの確保
    if( hMemCpyKSM02_DATA ){
        GlobalUnlock( hMemCpyKSM02_DATA );
        GlobalFree( hMemCpyKSM02_DATA );
    }
    hMemCpyKSM02_DATA = GlobalAlloc( GHND, sizeof(struct KSM02_DATA) * iCntCpyKSM02_DATA );
    if( hMemCpyKSM02_DATA == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        SBr1->Update();
        Beep();
        return(false);
    }
    cpyKSM02_DATA = (struct KSM02_DATA *)GlobalLock(hMemCpyKSM02_DATA);
    if( hMemCpyKSM02_DATA == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        SBr1->Update();
        Beep();
        return(false);
    }

    // 選択されている範囲をメモリに格納します
    for( i=iRowSelTop, cnt=0; i<=iRowSelBottom; i++, cnt++ ) {
		//strcpy( cpyKSM02_DATA[cnt].DTKSHIN	,sBuf.c_str() );	// 代表得意先品番
		//strcpy( cpyKSM02_DATA[cnt].REVCNT		,sBuf.c_str() );	// 改訂番号
		sBuf = SGr_SOKUT->Cells[13][i];
		strcpy( cpyKSM02_DATA[cnt].UNQ_NO		,sBuf.c_str() );	// 明細NO
		sBuf = SGr_SOKUT->Cells[14][i];
		strcpy( cpyKSM02_DATA[cnt].ORDER_NO		,sBuf.c_str() );	// 表示順
		sBuf = SGr_SOKUT->Cells[15][i];
		strcpy( cpyKSM02_DATA[cnt].SKB_NO		,sBuf.c_str() );	// 識別NO
		sBuf = SGr_SOKUT->Cells[1][i];
		strcpy( cpyKSM02_DATA[cnt].HINBAN_SK	,sBuf.c_str() );	// 品番
		sBuf = SGr_SOKUT->Cells[12][i];
		strcpy( cpyKSM02_DATA[cnt].KOMK_NO		,sBuf.c_str() );	// 項目NO
		sBuf = SGr_SOKUT->Cells[2][i];
		strcpy( cpyKSM02_DATA[cnt].KOMK_NM		,sBuf.c_str() );	// 測定項目名称（日本語）
		sBuf = SGr_SOKUT->Cells[4][i];
		strcpy( cpyKSM02_DATA[cnt].KOMK_ENG		,sBuf.c_str() );	// 測定項目名称（英語）
		sBuf = SGr_SOKUT->Cells[3][i];
		strcpy( cpyKSM02_DATA[cnt].KOMK_SUB		,sBuf.c_str() );	// 測定項目サブ名称（日本語）
		sBuf = SGr_SOKUT->Cells[16][i];
		strcpy( cpyKSM02_DATA[cnt].KOMK_SUB_ENG	,sBuf.c_str() );	// 測定項目サブ名称（英語）
		sBuf = SGr_SOKUT->Cells[17][i];
		strcpy( cpyKSM02_DATA[cnt].KIKI_NO		,sBuf.c_str() );	// 測定機器NO
		sBuf = SGr_SOKUT->Cells[9][i];
		strcpy( cpyKSM02_DATA[cnt].KIKI_NM		,sBuf.c_str() );	// 測定機器名称
		sBuf = SGr_SOKUT->Cells[5][i];
		strcpy( cpyKSM02_DATA[cnt].TANI			,sBuf.c_str() );	// 単位
		sBuf = SGr_SOKUT->Cells[18][i];
		strcpy( cpyKSM02_DATA[cnt].KIKA_TYPE	,sBuf.c_str() );	// 規格タイプ
		sBuf = SGr_SOKUT->Cells[19][i];
		strcpy( cpyKSM02_DATA[cnt].KIKA_KIND	,sBuf.c_str() );	// 規格種類
		sBuf = SGr_SOKUT->Cells[20][i];
		strcpy( cpyKSM02_DATA[cnt].KIKA_DECI	,sBuf.c_str() );	// 規格小数点以下桁数
		sBuf = SGr_SOKUT->Cells[21][i];
		strcpy( cpyKSM02_DATA[cnt].KIKA_NUM1	,sBuf.c_str() );	// 規格値１
		sBuf = SGr_SOKUT->Cells[22][i];
		strcpy( cpyKSM02_DATA[cnt].KIKA_NUM2	,sBuf.c_str() );	// 規格値２
		sBuf = SGr_SOKUT->Cells[23][i];
		strcpy( cpyKSM02_DATA[cnt].KIKA_NUM3	,sBuf.c_str() );	// 規格値３
		sBuf = SGr_SOKUT->Cells[24][i];
		strcpy( cpyKSM02_DATA[cnt].KIKA_STR		,sBuf.c_str() );	// 規格値文字
		sBuf = SGr_SOKUT->Cells[25][i];
		strcpy( cpyKSM02_DATA[cnt].KIKA_SUB1	,sBuf.c_str() );	// 規格値サブ１
		sBuf = SGr_SOKUT->Cells[26][i];
		strcpy( cpyKSM02_DATA[cnt].KIKA_SUB2	,sBuf.c_str() );	// 規格値サブ２
		sBuf = SGr_SOKUT->Cells[27][i];
		strcpy( cpyKSM02_DATA[cnt].KIKA_SUB3	,sBuf.c_str() );	// 規格値サブ３
		sBuf = SGr_SOKUT->Cells[7][i];
		strcpy( cpyKSM02_DATA[cnt].SOKU_SU		,sBuf.c_str() );	// 測定指示n数
		sBuf = SGr_SOKUT->Cells[10][i];
		strcpy( cpyKSM02_DATA[cnt].SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
		sBuf = SGr_SOKUT->Cells[11][i];
		strcpy( cpyKSM02_DATA[cnt].TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
		sBuf = SGr_SOKUT->Cells[28][i];
		strcpy( cpyKSM02_DATA[cnt].KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
		sBuf = SGr_SOKUT->Cells[8][i];
		strcpy( cpyKSM02_DATA[cnt].VALUE_TYPE	,sBuf.c_str() );	// 測定値表現
		sBuf = SGr_SOKUT->Cells[29][i];
		strcpy( cpyKSM02_DATA[cnt].VALUE_DECI	,sBuf.c_str() );	// 測定値小数点以下桁数
    }

    return(true);
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：コピーされたデータをStringGrid（下）に貼り付けます（複数行対応）
//
//  機能説明
//    cpyKSM02_DATAにコピーされた測定項目データをStringGrid（下）に貼り付けます
//    測定項目StringGridで[Ctrl]+[V]を押した時の測定項目データの貼り付け処理
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    bool				：true  = 貼り付け成功
//						　false = 貼り付け失敗
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::SGr_SOKUT_GridMultiLinePaste()
{
	int	cnt;

    if( iCntCpyKSM02_DATA == 0 )	return(false);

	for( cnt=0; cnt<iCntCpyKSM02_DATA; cnt++ ) {
		strcpy( tmpKSM02_DATA.DTKSHIN		, cpyKSM02_DATA[cnt].DTKSHIN		);	// 代表得意先品番
		strcpy( tmpKSM02_DATA.REVCNT		, cpyKSM02_DATA[cnt].REVCNT			);	// 改訂番号
		//strcpy( tmpKSM02_DATA.UNQ_NO		, cpyKSM02_DATA[cnt].UNQ_NO			);	// 明細NO
		//strcpy( tmpKSM02_DATA.ORDER_NO	, cpyKSM02_DATA[cnt].ORDER_NO		);	// 表示順
		strcpy( tmpKSM02_DATA.SKB_NO		, cpyKSM02_DATA[cnt].SKB_NO			);	// 識別NO
		strcpy( tmpKSM02_DATA.HINBAN_SK		, cpyKSM02_DATA[cnt].HINBAN_SK		);	// 品番
		strcpy( tmpKSM02_DATA.KOMK_NO		, cpyKSM02_DATA[cnt].KOMK_NO		);	// 項目NO
		strcpy( tmpKSM02_DATA.KOMK_NM		, cpyKSM02_DATA[cnt].KOMK_NM		);	// 測定項目名称（日本語）
		strcpy( tmpKSM02_DATA.KOMK_ENG		, cpyKSM02_DATA[cnt].KOMK_ENG		);	// 測定項目名称（英語）
		strcpy( tmpKSM02_DATA.KOMK_SUB		, cpyKSM02_DATA[cnt].KOMK_SUB		);	// 測定項目サブ名称（日本語）
		strcpy( tmpKSM02_DATA.KOMK_SUB_ENG	, cpyKSM02_DATA[cnt].KOMK_SUB_ENG	);	// 測定項目サブ名称（英語）
		strcpy( tmpKSM02_DATA.KIKI_NO		, cpyKSM02_DATA[cnt].KIKI_NO		);	// 測定機器NO
		strcpy( tmpKSM02_DATA.KIKI_NM		, cpyKSM02_DATA[cnt].KIKI_NM		);	// 測定機器名称
		strcpy( tmpKSM02_DATA.TANI			, cpyKSM02_DATA[cnt].TANI			);	// 単位
		strcpy( tmpKSM02_DATA.KIKA_TYPE		, cpyKSM02_DATA[cnt].KIKA_TYPE		);	// 規格タイプ
		strcpy( tmpKSM02_DATA.KIKA_KIND		, cpyKSM02_DATA[cnt].KIKA_KIND		);	// 規格種類
		strcpy( tmpKSM02_DATA.KIKA_DECI		, cpyKSM02_DATA[cnt].KIKA_DECI		);	// 規格小数点以下桁数
		strcpy( tmpKSM02_DATA.KIKA_NUM1		, cpyKSM02_DATA[cnt].KIKA_NUM1		);	// 規格値１
		strcpy( tmpKSM02_DATA.KIKA_NUM2		, cpyKSM02_DATA[cnt].KIKA_NUM2		);	// 規格値２
		strcpy( tmpKSM02_DATA.KIKA_NUM3		, cpyKSM02_DATA[cnt].KIKA_NUM3		);	// 規格値３
		strcpy( tmpKSM02_DATA.KIKA_STR		, cpyKSM02_DATA[cnt].KIKA_STR		);	// 規格値文字
		strcpy( tmpKSM02_DATA.SOKU_SU		, cpyKSM02_DATA[cnt].SOKU_SU		);	// 測定指示n数
		strcpy( tmpKSM02_DATA.SOKU_FLG		, cpyKSM02_DATA[cnt].SOKU_FLG		);	// 測定項目の有無
		strcpy( tmpKSM02_DATA.TOKU_FLG		, cpyKSM02_DATA[cnt].TOKU_FLG		);	// 特別項目の有無
		strcpy( tmpKSM02_DATA.KIKA_PRT		, cpyKSM02_DATA[cnt].KIKA_PRT		);	// 上限下限値の印刷
		strcpy( tmpKSM02_DATA.VALUE_TYPE	, cpyKSM02_DATA[cnt].VALUE_TYPE		);	// 測定値表現
		strcpy( tmpKSM02_DATA.VALUE_DECI	, cpyKSM02_DATA[cnt].VALUE_DECI		);	// 測定値小数点以下桁数

		// 測定データを追加します
		Ins_SGr_SOKUT(SGr_SOKUT->Row);
		SGr_SOKUT->Row = SGr_SOKUT->Row + 1;
	}

    return(true);
}
