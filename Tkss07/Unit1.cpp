//---------------------------------------------------------------------------
//
//  Unit1.cpp
//    【出荷検査システム－検査成績書用タイトル項目マスター】
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
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NumberEdit"
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

    // 検索中フォームを表示します
    Form2 = new TForm2(this);
	Form2->Show();
	Form2->Refresh();

    // データベース初期化
    Database1->Open();

	SGr_List->ColWidths[0] = 30;		// NO
	SGr_List->ColWidths[1] = 200;       // 項目（日本語）
	SGr_List->ColWidths[2] = 200;       // 項目（英語）
	SGr_List->ColWidths[3] = 493;       // 見た目が不恰好なのでブランク列を作成
	SGr_List->ColWidths[4] = 0;         // 更新日
	SGr_List->ColWidths[5] = 0;         // 更新者
	SGr_List->ColWidths[6] = 0;         // 更新者（コード）
	SGr_List->ColWidths[7] = 0;         // 登録日
	SGr_List->ColWidths[8] = 0;         // 登録時間
	SGr_List->ColWidths[9] = 0;         // 更新時間
	SGr_List->ColWidths[10] = 0;        // 更新回数
	SGr_List->ColWidths[11] = 0;        // 修正･削除不可フラグ
	SGr_List->ColWidths[12] = 0;        // 項目No
	SGr_List->ColWidths[13] = 0;        // 表示順
	SGr_List->ColWidths[14] = 0;        // 更新フラグ（並び替えが生じた時もこのフラグがONになります。）
    									//           保存時このフラグがONのものをUpdateします。
/*  デバッグ用
	SGr_List->ColWidths[3] = 0;       	 // 見た目が不恰好なのでブランク列を作成
	SGr_List->ColWidths[4] = 70;         // 更新日
	SGr_List->ColWidths[5] = 50;         // 更新者
	SGr_List->ColWidths[6] = 50;         // 更新者（コード）
	SGr_List->ColWidths[7] = 70;         // 登録日
	SGr_List->ColWidths[8] = 70;         // 登録時間
	SGr_List->ColWidths[9] = 70;         // 更新時間
	SGr_List->ColWidths[10] = 20;        // 更新回数
	SGr_List->ColWidths[11] = 20;        // 修正･削除不可フラグ
	SGr_List->ColWidths[12] = 20;        // 項目No
	SGr_List->ColWidths[13] = 20;        // 表示順
	SGr_List->ColWidths[14] = 20;        // 更新フラグ（並び替えが生じた時もこのフラグがONになります。）
    									 //           保存時このフラグがONのものをUpdateします。
*/

	SGr_List->Cells[0][0] = " NO";
	SGr_List->Cells[1][0] = "項目(日本語)";
	SGr_List->Cells[2][0] = "項目(English)";

}

//---------------------------------------------------------------------------
//
//  概要
//    OnActivateイベント	：フォームがアクティブになったときに発生します。
//
//  機能説明
//    初期表示に必要なデータを検索します
//    検索中画面(Form2)を閉じます
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

	int iRow;
	AnsiString sBuf;

   	// 新しいトランザクションを開始
    if( Database1->InTransaction == false )
    {
        Database1->StartTransaction();
        DataSave = false;
    }

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// 問合せ実行
	sBuf = "SELECT * FROM KSM21 ORDER BY ORDER_NO";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	iRow = 1;
    iKMK_NO_MAX = 0;

	while( !Query1->Eof ){

		// グリッドの最大行数が超えていないかチェックする
		if( iRow >= SGr_List->RowCount ){
			SGr_List->RowCount = iRow + 1;
		}

		// グリッドにデータをセットします。
		sBuf = iRow ;
		SGr_List->Cells[0][iRow] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;    //No
		sBuf = iRow + 1;

        if( VarIsNull(Query1->FieldValues["KMK_NM_JPN"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["KMK_NM_JPN"];
		}
        SGr_List->Cells[1][iRow] = sBuf;   //項目（日本語）

        if( VarIsNull(Query1->FieldValues["KMK_NM_ENG"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["KMK_NM_ENG"];
        }
        SGr_List->Cells[2][iRow] = sBuf;   //項目（日本語）

		sBuf = Query1->FieldValues["UPDYMD"];
        sBuf = sBuf.Insert("/",5);
        sBuf = sBuf.Insert("/",8);
        SGr_List->Cells[4][iRow] = sBuf;   //変更日

		sBuf = Query1->FieldValues["UPDCHR"];
		SGr_List->Cells[6][iRow] = sBuf;   //更新者(担当者コード)
        sBuf = GetTANNAM(sBuf);
		SGr_List->Cells[5][iRow] = sBuf;   //更新者

		sBuf = Query1->FieldValues["ADDYMD"];
		SGr_List->Cells[7][iRow] = sBuf;   //登録日

		sBuf = Query1->FieldValues["ADDTIM"];
		SGr_List->Cells[8][iRow] =  sBuf;  //登録時間

		sBuf = Query1->FieldValues["UPDTIM"];
		SGr_List->Cells[9][iRow] = sBuf;   //更新時間

		sBuf = Query1->FieldValues["UPDCNT"];
		SGr_List->Cells[10][iRow] = sBuf;  //更新回数

		sBuf = Query1->FieldValues["NOUPD_FLG"];
		SGr_List->Cells[11][iRow] = sBuf;  //修正･削除不可フラグ

		sBuf = Query1->FieldValues["KMK_NO"];
		SGr_List->Cells[12][iRow] = sBuf;  //項目No

        // 最大の項目NOを取得します
	    if( StrToInt(sBuf) > iKMK_NO_MAX ){
        	iKMK_NO_MAX = StrToInt(sBuf);
        }

		sBuf = Query1->FieldValues["ORDER_NO"];
		SGr_List->Cells[13][iRow] = sBuf;  //表示順

		SGr_List->Cells[14][iRow] = "0";   //更新フラグ

		// カーソルを次にセットする
		Query1->Next();

		iRow += 1;
	}

    // データ件数を表示します
    sBuf = iRow-1;
    LblListCnt->Caption = "件数：" + AnsiString::StringOfChar(' ', 3-sBuf.Length()) + sBuf;


    SGr_List->RowCount = iRow + 1;
    SGr_List->Cells[0][iRow] = "";
    SGr_List->Cells[1][iRow] = "";
    SGr_List->Cells[2][iRow] = "";
    SGr_List->Cells[3][iRow] = "";
    SGr_List->Cells[4][iRow] = "";
    SGr_List->Cells[5][iRow] = "";
    SGr_List->Cells[6][iRow] = "";
    SGr_List->Cells[7][iRow] = "";
    SGr_List->Cells[8][iRow] = "";
    SGr_List->Cells[9][iRow] = "";
    SGr_List->Cells[10][iRow] = "";
    SGr_List->Cells[11][iRow] = "";
    SGr_List->Cells[12][iRow] = "";
    SGr_List->Cells[13][iRow] = "";
    SGr_List->Cells[14][iRow] = "";


    //１行目を自動選択します
    SGr_ListSelectCell( SGr_List, 1, 0, true);
	SGr_ListClick( SGr_List );

	Form2->Close();
	Form2->Refresh();
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
    if(SGr_List->Row > 1)
    {
        SGr_List->Row -= 1;
        SGr_List->SetFocus();
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
    if( (SGr_List->RowCount-1) > SGr_List->Row )
    {
        SGr_List->Row += 1;
        SGr_List->SetFocus();
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
    if( !BtnF05->Enabled )    return;

    // ステータスメッセージ
    SBr1->Panels->Items[0]->Text = "画面印刷中です... しばらくお待ちください。";
    SBr1->Update();

    Form1->Print();

    // ステータスメッセージ
    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ８：新規登録」ボタンを押した時の処理
//
//  機能説明
//    画面下に入力された項目をテーブル（KSM21）に登録します
//    StringGridに一行追加します
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
    AnsiString sBuf;
    int i;
    int nRet;
    

    if( !BtnF08->Enabled )    return;

    // 入力データのチェック
    if(EdtKMK_NM_JPN->Text.IsEmpty()){
        MessageDlg("項目名を入力してください。", mtWarning
                              ,TMsgDlgButtons() << mbOK, 0);
        return;
    }

    // データ変更が行なわれていない時
    if( EdtKMK_NM_JPN->Text == sEdtKMK_NM_JPN_Old &&
        EdtKMK_NM_ENG->Text == sEdtKMK_NM_ENG_Old ){
        nRet = MessageDlg("同じデータが登録されますがよろしいですか?", mtConfirmation,
               TMsgDlgButtons() << mbYes << mbNo, 0);
        if(nRet == mrNo ) {
            return;
        }
    }

    // ステータスメッセージ
    SBr1->Panels->Items[0]->Text = "新規登録中です．．．しばらくお待ち下さい。";
    SBr1->Update();

    // 最大項目NOを+1します
    iKMK_NO_MAX++ ;

    sBuf = IntToStr(iKMK_NO_MAX);
    strcpy( tmpKSM21_DATA.KMK_NO		,sBuf.c_str() );		// 項目NO
    sBuf = IntToStr(SGr_List->RowCount);
    strcpy( tmpKSM21_DATA.ORDER_NO		,sBuf.c_str() );		// 表示順
    sBuf = EdtKMK_NM_JPN->Text;
    strcpy( tmpKSM21_DATA.KMK_NM_JPN	,sBuf.c_str() );		// 項目名（日本語）
    sBuf = EdtKMK_NM_ENG->Text;
    strcpy( tmpKSM21_DATA.KMK_NM_ENG	,sBuf.c_str() );		// 項目名（英語）
    sBuf = "0";
    strcpy( tmpKSM21_DATA.NOUPD_FLG		,sBuf.c_str() );		// 修正･削除不可能項目
    sBuf = FormatDateTime("yyyymmdd",Date());
    strcpy( tmpKSM21_DATA.ADDYMD		,sBuf.c_str() );		// 登録日
    strcpy( tmpKSM21_DATA.UPDYMD		,sBuf.c_str() );		// 変更日
    sBuf = FormatDateTime("hhmm",TDateTime::CurrentTime());
    strcpy( tmpKSM21_DATA.ADDTIM		,sBuf.c_str() );		// 登録時間
    strcpy( tmpKSM21_DATA.UPDTIM		,sBuf.c_str() );		// 変更時間
    sBuf = IntToStr(USER_COD);
    strcpy( tmpKSM21_DATA.UPDCHR		,sBuf.c_str() );		// 更新者
    sBuf = "0";
    strcpy( tmpKSM21_DATA.UPDCNT		,sBuf.c_str() );		// 更新回数

    //AddData
    if( AddData() == False ){
		return;
    }

    //新規データをSGr_Listに表示
    // グリッドにデータをセットします。
    sBuf = SGr_List->RowCount-1;
    SGr_List->Cells[0][SGr_List->RowCount - 1] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;    //No

    sBuf = tmpKSM21_DATA.KMK_NM_JPN;
	SGr_List->Cells[1][SGr_List->RowCount - 1] = sBuf;   //項目（日本語）

    sBuf = tmpKSM21_DATA.KMK_NM_ENG;
	SGr_List->Cells[2][SGr_List->RowCount - 1] = sBuf;   //項目（日本語）

	sBuf = tmpKSM21_DATA.UPDYMD;
    sBuf = sBuf.Insert("/",5);
    sBuf = sBuf.Insert("/",8);
    SGr_List->Cells[4][SGr_List->RowCount - 1] = sBuf;   //変更日

	sBuf = tmpKSM21_DATA.UPDCHR;
	SGr_List->Cells[6][SGr_List->RowCount - 1] = sBuf;   //更新者(担当者コード)
    sBuf = GetTANNAM(sBuf);
	SGr_List->Cells[5][SGr_List->RowCount - 1] = sBuf;   //更新者

	sBuf = tmpKSM21_DATA.ADDYMD;
	SGr_List->Cells[7][SGr_List->RowCount - 1] = sBuf;   //登録日

	sBuf = tmpKSM21_DATA.ADDTIM;
	SGr_List->Cells[8][SGr_List->RowCount - 1] =  sBuf;  //登録時間

	sBuf = tmpKSM21_DATA.UPDTIM;
	SGr_List->Cells[9][SGr_List->RowCount - 1] = sBuf;   //更新時間

	sBuf = tmpKSM21_DATA.UPDCNT;
	SGr_List->Cells[10][SGr_List->RowCount - 1] = sBuf;  //更新回数

	sBuf = tmpKSM21_DATA.NOUPD_FLG;
	SGr_List->Cells[11][SGr_List->RowCount - 1] = sBuf;  //修正･削除不可フラグ

	sBuf = tmpKSM21_DATA.KMK_NO;
	SGr_List->Cells[12][SGr_List->RowCount - 1] = sBuf;  //項目No

	sBuf = tmpKSM21_DATA.ORDER_NO;
	SGr_List->Cells[13][SGr_List->RowCount - 1] = sBuf;  //表示順

	SGr_List->Cells[14][SGr_List->RowCount - 1] = "0";   //更新フラグ

    // 一行増やす
    SGr_List->RowCount = SGr_List->RowCount + 1;

    // 最下行をクリアー
    for( i = 0; i < SGr_List->ColCount; i++) {
		SGr_List->Cells[i][SGr_List->RowCount-1]  = "";
    }

    // 新しい行を選択
    SGr_List->Row = SGr_List->RowCount - 1;

    SGr_List->SetFocus();

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

    // データを変更したフラグ
    DataSave = true;
    SGr_ListSelectCell(Sender,1,SGr_List->RowCount-1,true);

    // ボタンの初期化
    BtnF01->Enabled = false;
    BtnF02->Enabled = true;
    BtnF03->Enabled = true;
    BtnF04->Enabled = false;
    BtnF05->Enabled = true;
    BtnF06->Enabled = false;
    BtnF07->Enabled = false;
    BtnF08->Enabled = true;
    BtnF09->Enabled = true;
    BtnF10->Enabled = true;
    BtnF11->Enabled = true;
    BtnF12->Enabled = true;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ９：修正」ボタンを押した時の処理
//
//  機能説明
//    StringGridで選択されたデータに対して画面下に入力された項目に更新します
//    テーブル（KSM21）を更新します
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

    AnsiString sBuf;

    if( !BtnF09->Enabled )    return;

    if( PnlUPDYMD->Tag == -1){
    	MessageDlg("修正元がありません。データを選択してください。", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        return;
    }

    // 入力データのチェック
    if(EdtKMK_NM_JPN->Text.IsEmpty()){
        MessageDlg("項目名を入力してください。", mtWarning
                              ,TMsgDlgButtons() << mbOK, 0);
        return;
    }

    // ステータスメッセージ
    SBr1->Panels->Items[0]->Text = "修正中です．．．しばらくお待ち下さい。";
    SBr1->Update();


    // データをバッファに格納します。
    sBuf = IntToStr(PnlUPDYMD->Tag);
    strcpy( tmpKSM21_DATA.KMK_NO		,sBuf.c_str() );		// 項目NO
    sBuf = IntToStr(SGr_List->RowCount);
    strcpy( tmpKSM21_DATA.ORDER_NO		,sBuf.c_str() );		// 表示順
    sBuf = EdtKMK_NM_JPN->Text;
    strcpy( tmpKSM21_DATA.KMK_NM_JPN	,sBuf.c_str() );		// 項目名（日本語）
    sBuf = EdtKMK_NM_ENG->Text;
    strcpy( tmpKSM21_DATA.KMK_NM_ENG	,sBuf.c_str() );		// 項目名（英語）
    sBuf = FormatDateTime("yyyymmdd",Date());
    strcpy( tmpKSM21_DATA.UPDYMD		,sBuf.c_str() );		// 変更日
    sBuf = FormatDateTime("hhmm",TDateTime::CurrentTime());
    strcpy( tmpKSM21_DATA.UPDTIM		,sBuf.c_str() );		// 変更時間
    sBuf = IntToStr(USER_COD);
    strcpy( tmpKSM21_DATA.UPDCHR		,sBuf.c_str() );		// 更新者
    sBuf = IntToStr(PnlUPDCHR->Tag + 1);
    strcpy( tmpKSM21_DATA.UPDCNT		,sBuf.c_str() );		// 更新回数

    //UpdData
    if( UpdData() == False ){
		return;
    }

    //修正データをSGr_Listに表示
    // グリッドにデータをセットします。

    sBuf = tmpKSM21_DATA.KMK_NM_JPN;
	SGr_List->Cells[1][ROWPOINT] = sBuf;   //項目（日本語）

    sBuf = tmpKSM21_DATA.KMK_NM_ENG;
	SGr_List->Cells[2][ROWPOINT] = sBuf;   //項目（英語）

	sBuf = tmpKSM21_DATA.UPDYMD;
    sBuf = sBuf.Insert("/",5);
    sBuf = sBuf.Insert("/",8);
    SGr_List->Cells[4][ROWPOINT] = sBuf;   //変更日

	sBuf = tmpKSM21_DATA.UPDCHR;
	SGr_List->Cells[6][ROWPOINT] = sBuf;   //更新者(担当者コード)
    sBuf = GetTANNAM(sBuf);
	SGr_List->Cells[5][ROWPOINT] = sBuf;   //更新者

	sBuf = tmpKSM21_DATA.UPDTIM;
	SGr_List->Cells[9][ROWPOINT] = sBuf;   //更新時間

	sBuf = tmpKSM21_DATA.UPDCNT;
	SGr_List->Cells[10][ROWPOINT] = sBuf;  //更新回数

    SGr_List->SetFocus();

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

    // データを変更したフラグ
    DataSave = true;
    SGr_ListSelectCell(Sender,1,ROWPOINT,true);

    // ボタンの初期化
    BtnF01->Enabled = false;
    BtnF02->Enabled = true;
    BtnF03->Enabled = true;
    BtnF04->Enabled = false;
    BtnF05->Enabled = true;
    BtnF06->Enabled = false;
    BtnF07->Enabled = false;
    BtnF08->Enabled = true;
    BtnF09->Enabled = true;
    BtnF10->Enabled = true;
    BtnF11->Enabled = true;
    BtnF12->Enabled = true;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ１０：削除」ボタンを押した時の処理
//
//  機能説明
//    StringGridで選択されたデータを削除します
//    テーブル（KSM21）のレコードを削除します
//    StringGridの選択行も削除します
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
    int			i;
    AnsiString	sBuf;

    if( !BtnF10->Enabled )    return;

    if( PnlUPDYMD->Tag == -1){
        // ステータスメッセージ
    	MessageDlg("削除対象ではありません。", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        return;
    }

    // ステータスメッセージ
    SBr1->Panels->Items[0]->Text = "削除中です．．．しばらくお待ち下さい。";
    SBr1->Update();

    // データをバッファに格納します。
    sBuf = IntToStr(PnlUPDYMD->Tag);
    strcpy( tmpKSM21_DATA.KMK_NO		,sBuf.c_str() );		// 項目NO

    // DelData
    if( DelData() == False ){
        return;
    }

    for( i = SGr_List->Row; i < (SGr_List->RowCount - 1); i++) {
        // グリッドの一行を削除します。
        SGr_List->Cells[1][i] = SGr_List->Cells[1][i+1];
        SGr_List->Cells[2][i] = SGr_List->Cells[2][i+1];
        SGr_List->Cells[3][i] = SGr_List->Cells[3][i+1];
        SGr_List->Cells[4][i] = SGr_List->Cells[4][i+1];
        SGr_List->Cells[5][i] = SGr_List->Cells[5][i+1];
        SGr_List->Cells[6][i] = SGr_List->Cells[6][i+1];
        SGr_List->Cells[7][i] = SGr_List->Cells[7][i+1];
        SGr_List->Cells[8][i] = SGr_List->Cells[8][i+1];
        SGr_List->Cells[9][i] = SGr_List->Cells[9][i+1];
        SGr_List->Cells[10][i] = SGr_List->Cells[10][i+1];
        SGr_List->Cells[11][i] = SGr_List->Cells[11][i+1];
        SGr_List->Cells[12][i] = SGr_List->Cells[12][i+1];
        SGr_List->Cells[13][i] = SGr_List->Cells[13][i+1];
        SGr_List->Cells[14][i] = SGr_List->Cells[14][i+1];
    }

    // 一行減らす
    SGr_List->RowCount = SGr_List->RowCount - 1;
    SGr_List->Cells[1][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[2][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[3][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[4][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[5][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[6][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[7][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[8][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[9][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[10][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[11][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[12][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[13][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[14][SGr_List->RowCount - 1] = "";

    // 新しい行を選択
    if( SGr_List->RowCount == SGr_List->Row){
        SGr_List->Row = SGr_List->Row - 1;
    }
    else {
        SGr_List->Row = SGr_List->Row;
    }

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();
    SGr_ListSelectCell(Sender,1,SGr_List->Row,true);

    // データを変更したフラグ
    DataSave = true;

    // ボタン状態の変更
    BtnF01->Enabled = false;
    BtnF02->Enabled = true;
    BtnF03->Enabled = true;
    BtnF04->Enabled = false;
    BtnF05->Enabled = true;
    BtnF06->Enabled = false;
    BtnF07->Enabled = false;
    BtnF08->Enabled = true;
    BtnF09->Enabled = true;
    BtnF10->Enabled = true;
    BtnF11->Enabled = true;
    BtnF12->Enabled = true;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ１１：保存」ボタンを押した時の処理
//
//  機能説明
//    更新の有ったデータを確定（Commit）します
//    表示順が変更された項目も更新しなおします
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
    int		i;

    // ステータスメッセージ
    SBr1->Panels->Items[0]->Text = "保存中です．．．しばらくお待ち下さい。";
    SBr1->Update();

    // 変更，挿入，削除を永続的に保存し，現在のトランザクションを終了
    if( Database1->InTransaction == True ){
        Database1->Commit();

    	// 並び替えられた表示順を保存します。
    	for( i = 1; i < SGr_List->RowCount; i++) {
    		if( SGr_List->Cells[14][i] == "1" ){
                UpdData_ORDER_NO(SGr_List->Cells[12][i],SGr_List->Cells[13][i]);
        	}
    	}

        // 新しいトランザクションを開始
        Database1->StartTransaction();
    }

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

    // データを変更したフラグ
    DataSave = false;
    BtnF11->Enabled = false;
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ１２：終了」ボタンを押した時の処理
//
//  機能説明
//    更新されているかどうか確認し、
//    更新されている場合は「Ｆ１１：保存」を呼び出し
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
     int nRet;
     if( DataSave == true )
     {
         nRet = MessageDlg("編集されています。保存しますか?", mtConfirmation,
                TMsgDlgButtons() << mbYes << mbCancel << mbNo, 0);
         if(nRet == mrYes )
         {
              BtnF11Click(Sender);
              Close();
         }
         else if(nRet == mrCancel)
         {
         }
         else
         {
              DataSave = false;
              Close();
         }
     }
     else
     {
         Close();
     }
}

//---------------------------------------------------------------------------
//
//  概要
//    OnCloseQueryイベント：Close メソッドが呼び出されたときまたはユーザーが
//          フォームのシステムメニューで［閉じる］を選択したときに発生します。
//
//  機能説明
//    更新したデータが未保存の場合、保存するかしないかを確認します。
//    保存する場合は、データを確定(Commit)します。
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
    Query2->Close();

	Database1->Close();
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：データを追加します。
//
//  機能説明
//    「Ｆ８：新規登録」時のデータ追加（KSM21）処理
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    bool				：true = 成功、false = 失敗
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::AddData()
{
    AnsiString sBuf;

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // 問合せ文作成
    sBuf = "insert into KSM21(";
    sBuf += " KMK_NO, ORDER_NO, KMK_NM_JPN, KMK_NM_ENG, NOUPD_FLG, ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT";
    sBuf += " )";

    sBuf += " VALUES(";
    sBuf += AnsiString(tmpKSM21_DATA.KMK_NO) 		+  "," ;	//項目NO
    sBuf += AnsiString(tmpKSM21_DATA.ORDER_NO)		+  ",'";	//表示順
    sBuf += AnsiString(tmpKSM21_DATA.KMK_NM_JPN)	+ "','";	//項目名（日本語）
    sBuf += AnsiString(tmpKSM21_DATA.KMK_NM_ENG)	+ "'," ;	//項目名（英語）
    sBuf += AnsiString(tmpKSM21_DATA.NOUPD_FLG)		+  ",'";	//修正・削除不可フラグ
    sBuf += AnsiString(tmpKSM21_DATA.ADDYMD)		+ "','";	//登録日
    sBuf += AnsiString(tmpKSM21_DATA.ADDTIM)		+ "','";	//登録時間
    sBuf += Trim(AnsiString(tmpKSM21_DATA.UPDYMD))	+ "','";	//更新日
    sBuf += AnsiString(tmpKSM21_DATA.UPDTIM)		+ "'," ;	//更新時間
    sBuf += AnsiString(tmpKSM21_DATA.UPDCHR)		+  "," ;	//更新者
    sBuf += AnsiString(tmpKSM21_DATA.UPDCNT)		+  ")" ;	//更新回数

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
//    自作関数			：データを修正します。
//
//  機能説明
//    「Ｆ９：修正」時のデータ更新（KSM21）処理
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    bool				：true = 成功、false = 失敗
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::UpdData()
{
    AnsiString sBuf;

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // 問合せ文作成
    sBuf  = "update KSM21 set";
    sBuf += " KMK_NM_JPN='"	+ AnsiString(tmpKSM21_DATA.KMK_NM_JPN)	+ "',";	//項目名（日本語）
    sBuf += " KMK_NM_ENG='"	+ AnsiString(tmpKSM21_DATA.KMK_NM_ENG)	+ "',";	//項目名（英語）
    sBuf += " UPDYMD='"		+ Trim(AnsiString(tmpKSM21_DATA.UPDYMD))+ "',";	//更新日
    sBuf += " UPDTIM='"		+ AnsiString(tmpKSM21_DATA.UPDTIM)		+ "',";	//更新時間
    sBuf += " UPDCHR="		+ AnsiString(tmpKSM21_DATA.UPDCHR)		+  ",";	//更新者
    sBuf += " UPDCNT="		+ AnsiString(tmpKSM21_DATA.UPDCNT)			  ;	//更新回数
    sBuf += " WHERE KMK_NO="+ AnsiString(tmpKSM21_DATA.KMK_NO)			  ; //項目NO

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
//    自作関数			：データを修正します。（表示順のみ）
//
//  機能説明
//    「Ｆ１１：保存」時の表示順更新（KSM21）処理
//
//  パラメタ説明
//    AnsiString sKMK_NO：修正対象の項目NO
//    AnsiString sORDER_NO：新しい表示順NO
//
//  戻り値
//    bool				：true = 成功、false = 失敗
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::UpdData_ORDER_NO(AnsiString sKMK_NO, AnsiString sORDER_NO)
{
    AnsiString sBuf;

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // 問合せ文作成
    sBuf  = "update KSM21 set";
    sBuf += " ORDER_NO="		+ Trim(sORDER_NO)	  ;	//表示順
    sBuf += " WHERE KMK_NO="	+ Trim(sKMK_NO)		  ; //項目NO

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
//    自作関数			：データを削除します。
//
//  機能説明
//    「Ｆ１０：削除」時のデータ削除（KSM21）処理
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    bool				：true = 成功、false = 失敗
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::DelData()
{
    AnsiString sBuf;

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // 問合せ文作成
    sBuf = "select * from KSM21 ";
    sBuf += " WHERE KMK_NO="+ AnsiString(tmpKSM21_DATA.KMK_NO)  ; //項目NO

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

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // 問合せ文作成
    sBuf = "DELETE from KSM21";
    sBuf += " WHERE KMK_NO="+ AnsiString(tmpKSM21_DATA.KMK_NO)		  ; //項目NO

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
//    OnResizeイベント	：コントロールのサイズが変更された直後に発生します。
//
//  機能説明
//    Panelのサイズに合わせてStringGridのサイズも変更します
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
    iBMarg = 6;

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
//    OnClickイベント	：「上へ移動」ボタンを押した時の処理
//
//  機能説明
//    StringGridで選択された行を1つ上の行と入れ替えます。
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
void __fastcall TForm1::BtnListUpClick(TObject *Sender)
{
    int			i;
	int			iChgRow1;
	int			iChgRow2;
	int			iChgRow3;
	TGridRect	myRect;
    AnsiString	sBuf;


    iChgRow1 = SGr_List->Selection.Top;
    iChgRow2 = SGr_List->Selection.Top - 1;
    iChgRow3 = SGr_List->Selection.Bottom;

    if( iChgRow1 <= 1) return;
    if( iChgRow1 >= SGr_List->RowCount - 1) return;

    if( iChgRow3 >= SGr_List->RowCount - 1)
    	iChgRow3 = SGr_List->Selection.Bottom = SGr_List->RowCount - 2;

    // ※表示順は入れ替えせずにその他の項目を入れ替え、更新フラグ(Cells[14])をONにします。

    // 入れ替え先のデータをバックアップ
    sBuf = SGr_List->Cells[12][iChgRow2];
    strcpy( tmpKSM21_DATA.KMK_NO		,sBuf.c_str() );		// 項目NO
    //sBuf = SGr_List->Cells[13][iChgRow2];
    //strcpy( tmpKSM21_DATA.ORDER_NO		,sBuf.c_str() );		// 表示順
    sBuf = SGr_List->Cells[1][iChgRow2];
    strcpy( tmpKSM21_DATA.KMK_NM_JPN	,sBuf.c_str() );		// 項目名（日本語）
    sBuf = SGr_List->Cells[2][iChgRow2];
    strcpy( tmpKSM21_DATA.KMK_NM_ENG	,sBuf.c_str() );		// 項目名（英語）
    sBuf = SGr_List->Cells[11][iChgRow2];
    strcpy( tmpKSM21_DATA.NOUPD_FLG		,sBuf.c_str() );		// 修正･削除不可能項目
    sBuf = SGr_List->Cells[7][iChgRow2];
    strcpy( tmpKSM21_DATA.ADDYMD		,sBuf.c_str() );		// 登録日
    sBuf = SGr_List->Cells[8][iChgRow2];
    strcpy( tmpKSM21_DATA.ADDTIM		,sBuf.c_str() );		// 登録時間
    sBuf = SGr_List->Cells[4][iChgRow2];
    strcpy( tmpKSM21_DATA.UPDYMD		,sBuf.c_str() );		// 変更日
    sBuf = SGr_List->Cells[9][iChgRow2];
    strcpy( tmpKSM21_DATA.UPDTIM		,sBuf.c_str() );		// 変更時間
    sBuf = SGr_List->Cells[5][iChgRow2];
    strcpy( tmpKSM21_DATA.UPDNAM		,sBuf.c_str() );		// 更新者（名称）
    sBuf = SGr_List->Cells[6][iChgRow2];
    strcpy( tmpKSM21_DATA.UPDCHR		,sBuf.c_str() );		// 更新者（コード）
    sBuf = SGr_List->Cells[10][iChgRow2];
    strcpy( tmpKSM21_DATA.UPDCNT		,sBuf.c_str() );		// 更新回数

	// 上下を入れ替えます
    for( i=iChgRow2; i<iChgRow3 ; i++ ) {
    	SGr_List->Cells[1][i] = SGr_List->Cells[1][i + 1];
    	SGr_List->Cells[2][i] = SGr_List->Cells[2][i + 1];
    	SGr_List->Cells[3][i] = SGr_List->Cells[3][i + 1];
    	SGr_List->Cells[4][i] = SGr_List->Cells[4][i + 1];
    	SGr_List->Cells[5][i] = SGr_List->Cells[5][i + 1];
    	SGr_List->Cells[6][i] = SGr_List->Cells[6][i + 1];
    	SGr_List->Cells[7][i] = SGr_List->Cells[7][i + 1];
    	SGr_List->Cells[8][i] = SGr_List->Cells[8][i + 1];
    	SGr_List->Cells[9][i] = SGr_List->Cells[9][i + 1];
    	SGr_List->Cells[10][i] = SGr_List->Cells[10][i + 1];
    	SGr_List->Cells[11][i] = SGr_List->Cells[11][i + 1];
    	SGr_List->Cells[12][i] = SGr_List->Cells[12][i + 1];
    	//SGr_List->Cells[13][iChgRow2] = SGr_List->Cells[13][i + 1];
		SGr_List->Cells[14][i] = "1";
    }

    // バックアップしたデータを戻します
	SGr_List->Cells[12][iChgRow3] = tmpKSM21_DATA.KMK_NO	;	// 項目NO
	//SGr_List->Cells[13][iChgRow3] = tmpKSM21_DATA.ORDER_NO	;	// 表示順
	SGr_List->Cells[1][iChgRow3]  = tmpKSM21_DATA.KMK_NM_JPN;	// 項目名（日本語）
	SGr_List->Cells[2][iChgRow3]  = tmpKSM21_DATA.KMK_NM_ENG;	// 項目名（英語）
	SGr_List->Cells[11][iChgRow3] = tmpKSM21_DATA.NOUPD_FLG	;	// 修正･削除不可能項目
	SGr_List->Cells[7][iChgRow3]  = tmpKSM21_DATA.ADDYMD	;	// 登録日
	SGr_List->Cells[8][iChgRow3]  = tmpKSM21_DATA.ADDTIM	;	// 登録時間
	SGr_List->Cells[4][iChgRow3]  = tmpKSM21_DATA.UPDYMD	;	// 変更日
	SGr_List->Cells[9][iChgRow3]  = tmpKSM21_DATA.UPDTIM	;	// 変更時間
	SGr_List->Cells[6][iChgRow3]  = tmpKSM21_DATA.UPDCHR	;	// 更新者（コード）
	SGr_List->Cells[5][iChgRow3]  = tmpKSM21_DATA.UPDNAM	;	// 更新者（名称）
	SGr_List->Cells[10][iChgRow3] = tmpKSM21_DATA.UPDCNT	;	// 更新回数
	SGr_List->Cells[14][iChgRow3] = "1";

    // 選択カーソルも同時に上に移動します
    SGr_List->Row--;
	myRect.Left		= SGr_List->Selection.Left;
	myRect.Top		= iChgRow1 - 1;
	myRect.Right	= SGr_List->Selection.Right;
	myRect.Bottom	= iChgRow3 - 1;
    SGr_List->Selection	= myRect;
    SGr_ListSelectCell(Sender,1,SGr_List->Row,true);

    // データを変更したフラグ
    DataSave = true;
    BtnF11->Enabled = true;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「下へ移動」ボタンを押した時の処理
//
//  機能説明
//    StringGridで選択された行を1つ下の行と入れ替えます。
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
void __fastcall TForm1::BtnListDownClick(TObject *Sender)
{
    int			i;
	int			iChgRow1;
	int			iChgRow2;
	int			iChgRow3;
	TGridRect	myRect;
    AnsiString	sBuf;


    iChgRow1 = SGr_List->Selection.Top;
    iChgRow2 = SGr_List->Selection.Bottom + 1;
    iChgRow3 = SGr_List->Selection.Bottom;

    if( iChgRow2 >= SGr_List->RowCount - 1) return;

    // ※表示順は入れ替えせずにその他の項目を入れ替え、更新フラグ(Cells[14])をONにします。

    // 入れ替え先のデータをバックアップ
    sBuf = SGr_List->Cells[12][iChgRow2];
    strcpy( tmpKSM21_DATA.KMK_NO		,sBuf.c_str() );		// 項目NO
    //sBuf = SGr_List->Cells[13][iChgRow2];
    //strcpy( tmpKSM21_DATA.ORDER_NO		,sBuf.c_str() );		// 表示順
    sBuf = SGr_List->Cells[1][iChgRow2];
    strcpy( tmpKSM21_DATA.KMK_NM_JPN	,sBuf.c_str() );		// 項目名（日本語）
    sBuf = SGr_List->Cells[2][iChgRow2];
    strcpy( tmpKSM21_DATA.KMK_NM_ENG	,sBuf.c_str() );		// 項目名（英語）
    sBuf = SGr_List->Cells[11][iChgRow2];
    strcpy( tmpKSM21_DATA.NOUPD_FLG		,sBuf.c_str() );		// 修正･削除不可能項目
    sBuf = SGr_List->Cells[7][iChgRow2];
    strcpy( tmpKSM21_DATA.ADDYMD		,sBuf.c_str() );		// 登録日
    sBuf = SGr_List->Cells[8][iChgRow2];
    strcpy( tmpKSM21_DATA.ADDTIM		,sBuf.c_str() );		// 登録時間
    sBuf = SGr_List->Cells[4][iChgRow2];
    strcpy( tmpKSM21_DATA.UPDYMD		,sBuf.c_str() );		// 変更日
    sBuf = SGr_List->Cells[9][iChgRow2];
    strcpy( tmpKSM21_DATA.UPDTIM		,sBuf.c_str() );		// 変更時間
    sBuf = SGr_List->Cells[5][iChgRow2];
    strcpy( tmpKSM21_DATA.UPDNAM		,sBuf.c_str() );		// 更新者（名称）
    sBuf = SGr_List->Cells[6][iChgRow2];
    strcpy( tmpKSM21_DATA.UPDCHR		,sBuf.c_str() );		// 更新者（コード）
    sBuf = SGr_List->Cells[10][iChgRow2];
    strcpy( tmpKSM21_DATA.UPDCNT		,sBuf.c_str() );		// 更新回数

	// 上下を入れ替えます
    for( i=iChgRow2; i>iChgRow1 ; i-- ) {
    	SGr_List->Cells[1][i] = SGr_List->Cells[1][i - 1];
    	SGr_List->Cells[2][i] = SGr_List->Cells[2][i - 1];
    	SGr_List->Cells[3][i] = SGr_List->Cells[3][i - 1];
    	SGr_List->Cells[4][i] = SGr_List->Cells[4][i - 1];
    	SGr_List->Cells[5][i] = SGr_List->Cells[5][i - 1];
    	SGr_List->Cells[6][i] = SGr_List->Cells[6][i - 1];
    	SGr_List->Cells[7][i] = SGr_List->Cells[7][i - 1];
    	SGr_List->Cells[8][i] = SGr_List->Cells[8][i - 1];
    	SGr_List->Cells[9][i] = SGr_List->Cells[9][i - 1];
    	SGr_List->Cells[10][i] = SGr_List->Cells[10][i - 1];
    	SGr_List->Cells[11][i] = SGr_List->Cells[11][i - 1];
    	SGr_List->Cells[12][i] = SGr_List->Cells[12][i - 1];
    	//SGr_List->Cells[13][iChgRow2] = SGr_List->Cells[13][i - 1];
		SGr_List->Cells[14][i] = "1";
    }

    // 上下を入れ替えます。
	SGr_List->Cells[12][iChgRow1] = tmpKSM21_DATA.KMK_NO	;	// 項目NO
	//SGr_List->Cells[13][iChgRow1] = tmpKSM21_DATA.ORDER_NO	;	// 表示順
	SGr_List->Cells[1][iChgRow1]  = tmpKSM21_DATA.KMK_NM_JPN;	// 項目名（日本語）
	SGr_List->Cells[2][iChgRow1]  = tmpKSM21_DATA.KMK_NM_ENG;	// 項目名（英語）
	SGr_List->Cells[11][iChgRow1] = tmpKSM21_DATA.NOUPD_FLG	;	// 修正･削除不可能項目
	SGr_List->Cells[7][iChgRow1]  = tmpKSM21_DATA.ADDYMD	;	// 登録日
	SGr_List->Cells[8][iChgRow1]  = tmpKSM21_DATA.ADDTIM	;	// 登録時間
	SGr_List->Cells[4][iChgRow1]  = tmpKSM21_DATA.UPDYMD	;	// 変更日
	SGr_List->Cells[9][iChgRow1]  = tmpKSM21_DATA.UPDTIM	;	// 変更時間
	SGr_List->Cells[6][iChgRow1]  = tmpKSM21_DATA.UPDCHR	;	// 更新者（コード）
	SGr_List->Cells[5][iChgRow1]  = tmpKSM21_DATA.UPDNAM	;	// 更新者（名称）
	SGr_List->Cells[10][iChgRow1] = tmpKSM21_DATA.UPDCNT	;	// 更新回数
    SGr_List->Cells[14][iChgRow1] = "1";

    // 選択カーソルも同時に下に移動します
    SGr_List->Row++;
	myRect.Left		= SGr_List->Selection.Left;
	myRect.Top		= iChgRow1 + 1;
	myRect.Right	= SGr_List->Selection.Right;
	myRect.Bottom	= iChgRow3 + 1;
    SGr_List->Selection	= myRect;
    SGr_ListSelectCell(Sender,1,SGr_List->Row,true);

    // データを変更したフラグ
    DataSave = true;
    BtnF11->Enabled = true;

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
void __fastcall TForm1::SGr_ListClick(TObject *Sender)
{
    iRowSelTop    = SGr_List->Selection.Top;
    iRowSelBottom = SGr_List->Selection.Bottom;
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
void __fastcall TForm1::SGr_ListRowMoved(TObject *Sender, int FromIndex,
      int ToIndex)
{

    int         i;
    int			k;
    int			m;
	int			CopyCnt;
    int			iStart;
    int			iEnd;
    int			iSkip;
    HANDLE  	hMemCopy;
    AnsiString  sBuf;
    KSM21_DATA  *pKSM21_DATA;
	TGridRect	myRect;


    // 範囲選択したものと実際に移動処理された行の指定位置が異なる時は、エラー
    if( FromIndex < iRowSelTop || FromIndex > iRowSelBottom ){
        RowExchange(FromIndex,ToIndex);
        // エラーメッセージ
    	MessageDlg("選択範囲が正しくありません。", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	return;
    }

    // 範囲選択した移動先が、その範囲選択内への移動の時は、エラー
    if( ToIndex >= iRowSelTop && ToIndex <= iRowSelBottom ){
        RowExchange(FromIndex,ToIndex);
        // エラーメッセージ
    	MessageDlg("移動先が正しくありません。", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	return;
    }

    // 最下行の下へ移動の時は、エラー
    if( ToIndex >= SGr_List->RowCount - 1 ){
        RowExchange(FromIndex,ToIndex);
        // エラーメッセージ
    	MessageDlg("移動先が正しくありません。", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	return;
    }

    // 範囲選択したものに最下行を含む時は、エラー
    if( SGr_List->RowCount - 1 <= iRowSelBottom ){
        RowExchange(FromIndex,ToIndex);
        // エラーメッセージ
    	MessageDlg("選択範囲が正しくありません。", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	return;
    }

    if( FromIndex < ToIndex ){
        iStart = iRowSelTop;
        iEnd   = ToIndex;

		// 表示順を入れ替えます
    	sBuf = SGr_List->Cells[13][ToIndex];
		for( i = ToIndex; i > FromIndex; i-- ){
			SGr_List->Cells[13][i] = SGr_List->Cells[13][i-1];
    	}
    	SGr_List->Cells[13][FromIndex] = sBuf;
    }
    else {
        iStart = ToIndex;
        iEnd   = iRowSelBottom;

		// 表示順を入れ替えます
        sBuf = SGr_List->Cells[13][ToIndex];
		for( i = ToIndex; i < FromIndex; i++ ){
			SGr_List->Cells[13][i] = SGr_List->Cells[13][i+1];
    	}
    	SGr_List->Cells[13][FromIndex] = sBuf;
    }

	// 行Noを元に戻します
	for( i = iStart; i <= iEnd; i++ ){
		sBuf = i ;
		if( i < SGr_List->RowCount - 1 ){
			SGr_List->Cells[0][i] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;
   	    	SGr_List->Cells[14][i] = "1";						// 更新フラグON
		}
        else{
			SGr_List->Cells[0][i] = "";
   	    	SGr_List->Cells[14][i] = "";
        }
    }

    // コピーの個数を確保します
    CopyCnt = iRowSelBottom - iRowSelTop;

    // メモリの確保
    hMemCopy = GlobalAlloc( GHND, sizeof(struct KSM21_DATA) * CopyCnt );
    if( hMemCopy == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        SBr1->Update();
        Beep();
        return;
    }
    pKSM21_DATA = (struct KSM21_DATA *)GlobalLock(hMemCopy);
    if( hMemCopy == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        SBr1->Update();
        Beep();
        return;
    }

    if( FromIndex < ToIndex ){

	    // 選択されている範囲をメモリに格納します
    	for( i=iRowSelTop, k=0; i<iRowSelBottom; i++, k++ ) {
    		sBuf = SGr_List->Cells[12][i];
    		strcpy( pKSM21_DATA[k].KMK_NO		,sBuf.c_str() );		// 項目NO
    		//sBuf = SGr_List->Cells[13][i];
    		//strcpy( pKSM21_DATA[k].ORDER_NO		,sBuf.c_str() );		// 表示順
    		sBuf = SGr_List->Cells[1][i];
    		strcpy( pKSM21_DATA[k].KMK_NM_JPN	,sBuf.c_str() );		// 項目名（日本語）
    		sBuf = SGr_List->Cells[2][i];
    		strcpy( pKSM21_DATA[k].KMK_NM_ENG	,sBuf.c_str() );		// 項目名（英語）
    		sBuf = SGr_List->Cells[11][i];
    		strcpy( pKSM21_DATA[k].NOUPD_FLG	,sBuf.c_str() );		// 修正･削除不可能項目
			sBuf = SGr_List->Cells[7][i];
    		strcpy( pKSM21_DATA[k].ADDYMD		,sBuf.c_str() );		// 登録日
    		sBuf = SGr_List->Cells[8][i];
    		strcpy( pKSM21_DATA[k].ADDTIM		,sBuf.c_str() );		// 登録時間
    		sBuf = SGr_List->Cells[4][i];
    		strcpy( pKSM21_DATA[k].UPDYMD		,sBuf.c_str() );		// 変更日
    		sBuf = SGr_List->Cells[9][i];
    		strcpy( pKSM21_DATA[k].UPDTIM		,sBuf.c_str() );		// 変更時間
    		sBuf = SGr_List->Cells[6][i];
    		strcpy( pKSM21_DATA[k].UPDCHR		,sBuf.c_str() );		// 更新者（コード）
    		sBuf = SGr_List->Cells[5][i];
    		strcpy( pKSM21_DATA[k].UPDNAM		,sBuf.c_str() );		// 更新者（名称）
    		sBuf = SGr_List->Cells[10][i];
    		strcpy( pKSM21_DATA[k].UPDCNT		,sBuf.c_str() );		// 更新回数
    	}

		// 複数選択内容を移動します
		for( i = iRowSelBottom; i <= ToIndex; i++ ){
			SGr_List->Cells[1][i-CopyCnt] = SGr_List->Cells[1][i];
			SGr_List->Cells[2][i-CopyCnt] = SGr_List->Cells[2][i];
			SGr_List->Cells[3][i-CopyCnt] = SGr_List->Cells[3][i];
			SGr_List->Cells[4][i-CopyCnt] = SGr_List->Cells[4][i];
			SGr_List->Cells[5][i-CopyCnt] = SGr_List->Cells[5][i];
			SGr_List->Cells[6][i-CopyCnt] = SGr_List->Cells[6][i];
			SGr_List->Cells[7][i-CopyCnt] = SGr_List->Cells[7][i];
			SGr_List->Cells[8][i-CopyCnt] = SGr_List->Cells[8][i];
			SGr_List->Cells[9][i-CopyCnt] = SGr_List->Cells[9][i];
			SGr_List->Cells[10][i-CopyCnt] = SGr_List->Cells[10][i];
			SGr_List->Cells[11][i-CopyCnt] = SGr_List->Cells[11][i];
			SGr_List->Cells[12][i-CopyCnt] = SGr_List->Cells[12][i];
			//SGr_List->Cells[13][i-CopyCnt] = SGr_List->Cells[13][i];
			SGr_List->Cells[14][i-CopyCnt] = SGr_List->Cells[14][i];
    	}

        // 自動移動された行を正しい位置に移動します。
        iSkip = FromIndex - iRowSelTop;
        if( iSkip != 0 ){
			SGr_List->Cells[1][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[1][ToIndex];
			SGr_List->Cells[2][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[2][ToIndex];
			SGr_List->Cells[3][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[3][ToIndex];
			SGr_List->Cells[4][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[4][ToIndex];
			SGr_List->Cells[5][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[5][ToIndex];
			SGr_List->Cells[6][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[6][ToIndex];
			SGr_List->Cells[7][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[7][ToIndex];
			SGr_List->Cells[8][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[8][ToIndex];
			SGr_List->Cells[9][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[9][ToIndex];
			SGr_List->Cells[10][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[10][ToIndex];
			SGr_List->Cells[11][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[11][ToIndex];
			SGr_List->Cells[12][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[12][ToIndex];
			//SGr_List->Cells[13][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[13][ToIndex];
			SGr_List->Cells[14][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[14][ToIndex];
        }

		// メモリに格納した内容を戻します
        i = ToIndex - CopyCnt;
		for( k = 0, m = 0; k <= CopyCnt; k++ ){
            if( k != iSkip ){
            	SGr_List->Cells[12][i+k] = pKSM21_DATA[m].KMK_NO		;		// 項目NO
    			//SGr_List->Cells[13][i+k] = pKSM21_DATA[m].ORDER_NO		;		// 表示順
    			SGr_List->Cells[1][i+k]  = pKSM21_DATA[m].KMK_NM_JPN	;		// 項目名（日本語）
    			SGr_List->Cells[2][i+k]  = pKSM21_DATA[m].KMK_NM_ENG	;		// 項目名（英語）
    			SGr_List->Cells[11][i+k] = pKSM21_DATA[m].NOUPD_FLG		;		// 修正･削除不可能項目
				SGr_List->Cells[7][i+k]  = pKSM21_DATA[m].ADDYMD		;		// 登録日
    			SGr_List->Cells[8][i+k]  = pKSM21_DATA[m].ADDTIM		;		// 登録時間
    			SGr_List->Cells[4][i+k]  = pKSM21_DATA[m].UPDYMD		;		// 変更日
    			SGr_List->Cells[9][i+k]  = pKSM21_DATA[m].UPDTIM		;		// 変更時間
    			SGr_List->Cells[6][i+k]  = pKSM21_DATA[m].UPDCHR		;		// 更新者（コード）
    			SGr_List->Cells[5][i+k]  = pKSM21_DATA[m].UPDNAM		;		// 更新者（名称）
    			SGr_List->Cells[10][i+k] = pKSM21_DATA[m].UPDCNT		;		// 更新回数
            	SGr_List->Cells[14][i+k] = "1"							;
				m++;
        	}
        }

    	// 移動先の行を選択範囲を決定します
		myRect.Left		= SGr_List->Selection.Left;
		myRect.Top		= ToIndex - CopyCnt;
		myRect.Right	= SGr_List->Selection.Right;
		myRect.Bottom	= myRect.Top + CopyCnt;
    }
    else {

	    // 選択されている範囲をメモリに格納します
    	for( i=iRowSelTop+1, k=0; i<=iRowSelBottom; i++, k++ ) {
    		sBuf = SGr_List->Cells[12][i];
    		strcpy( pKSM21_DATA[k].KMK_NO		,sBuf.c_str() );		// 項目NO
    		//sBuf = SGr_List->Cells[13][i];
    		//strcpy( pKSM21_DATA[k].ORDER_NO		,sBuf.c_str() );		// 表示順
    		sBuf = SGr_List->Cells[1][i];
    		strcpy( pKSM21_DATA[k].KMK_NM_JPN	,sBuf.c_str() );		// 項目名（日本語）
    		sBuf = SGr_List->Cells[2][i];
    		strcpy( pKSM21_DATA[k].KMK_NM_ENG	,sBuf.c_str() );		// 項目名（英語）
    		sBuf = SGr_List->Cells[11][i];
    		strcpy( pKSM21_DATA[k].NOUPD_FLG	,sBuf.c_str() );		// 修正･削除不可能項目
			sBuf = SGr_List->Cells[7][i];
    		strcpy( pKSM21_DATA[k].ADDYMD		,sBuf.c_str() );		// 登録日
    		sBuf = SGr_List->Cells[8][i];
    		strcpy( pKSM21_DATA[k].ADDTIM		,sBuf.c_str() );		// 登録時間
    		sBuf = SGr_List->Cells[4][i];
    		strcpy( pKSM21_DATA[k].UPDYMD		,sBuf.c_str() );		// 変更日
    		sBuf = SGr_List->Cells[9][i];
    		strcpy( pKSM21_DATA[k].UPDTIM		,sBuf.c_str() );		// 変更時間
    		sBuf = SGr_List->Cells[6][i];
    		strcpy( pKSM21_DATA[k].UPDCHR		,sBuf.c_str() );		// 更新者（コード）
    		sBuf = SGr_List->Cells[5][i];
    		strcpy( pKSM21_DATA[k].UPDNAM		,sBuf.c_str() );		// 更新者（名称）
    		sBuf = SGr_List->Cells[10][i];
    		strcpy( pKSM21_DATA[k].UPDCNT		,sBuf.c_str() );		// 更新回数
    	}

		// 複数選択内容を移動します
		for( i = iRowSelTop; i >= ToIndex; i-- ){
			SGr_List->Cells[1][i+CopyCnt] = SGr_List->Cells[1][i];
			SGr_List->Cells[2][i+CopyCnt] = SGr_List->Cells[2][i];
			SGr_List->Cells[3][i+CopyCnt] = SGr_List->Cells[3][i];
			SGr_List->Cells[4][i+CopyCnt] = SGr_List->Cells[4][i];
			SGr_List->Cells[5][i+CopyCnt] = SGr_List->Cells[5][i];
			SGr_List->Cells[6][i+CopyCnt] = SGr_List->Cells[6][i];
			SGr_List->Cells[7][i+CopyCnt] = SGr_List->Cells[7][i];
			SGr_List->Cells[8][i+CopyCnt] = SGr_List->Cells[8][i];
			SGr_List->Cells[9][i+CopyCnt] = SGr_List->Cells[9][i];
			SGr_List->Cells[10][i+CopyCnt] = SGr_List->Cells[10][i];
			SGr_List->Cells[11][i+CopyCnt] = SGr_List->Cells[11][i];
			SGr_List->Cells[12][i+CopyCnt] = SGr_List->Cells[12][i];
			//SGr_List->Cells[13][i+CopyCnt] = SGr_List->Cells[13][i];
			SGr_List->Cells[14][i+CopyCnt] = SGr_List->Cells[14][i];
    	}

        // 自動移動された行を正しい位置に移動します。
        iSkip = FromIndex - iRowSelTop;
        if( iSkip != 0 ){
			SGr_List->Cells[1][ToIndex+iSkip] = SGr_List->Cells[1][ToIndex];
			SGr_List->Cells[2][ToIndex+iSkip] = SGr_List->Cells[2][ToIndex];
			SGr_List->Cells[3][ToIndex+iSkip] = SGr_List->Cells[3][ToIndex];
			SGr_List->Cells[4][ToIndex+iSkip] = SGr_List->Cells[4][ToIndex];
			SGr_List->Cells[5][ToIndex+iSkip] = SGr_List->Cells[5][ToIndex];
			SGr_List->Cells[6][ToIndex+iSkip] = SGr_List->Cells[6][ToIndex];
			SGr_List->Cells[7][ToIndex+iSkip] = SGr_List->Cells[7][ToIndex];
			SGr_List->Cells[8][ToIndex+iSkip] = SGr_List->Cells[8][ToIndex];
			SGr_List->Cells[9][ToIndex+iSkip] = SGr_List->Cells[9][ToIndex];
			SGr_List->Cells[10][ToIndex+iSkip] = SGr_List->Cells[10][ToIndex];
			SGr_List->Cells[11][ToIndex+iSkip] = SGr_List->Cells[11][ToIndex];
			SGr_List->Cells[12][ToIndex+iSkip] = SGr_List->Cells[12][ToIndex];
			//SGr_List->Cells[13][ToIndex+iSkip] = SGr_List->Cells[13][ToIndex];
			SGr_List->Cells[14][ToIndex+iSkip] = SGr_List->Cells[14][ToIndex];
        }

		// メモリに格納した内容を戻します
        i = ToIndex;
		for( k = 0, m = 0; k <= CopyCnt; k++ ){
            if( k != iSkip ){
            	SGr_List->Cells[12][i+k] = pKSM21_DATA[m].KMK_NO		;		// 項目NO
    			//SGr_List->Cells[13][i+k] = pKSM21_DATA[m].ORDER_NO		;		// 表示順
    			SGr_List->Cells[1][i+k]  = pKSM21_DATA[m].KMK_NM_JPN	;		// 項目名（日本語）
    			SGr_List->Cells[2][i+k]  = pKSM21_DATA[m].KMK_NM_ENG	;		// 項目名（英語）
    			SGr_List->Cells[11][i+k] = pKSM21_DATA[m].NOUPD_FLG		;		// 修正･削除不可能項目
				SGr_List->Cells[7][i+k]  = pKSM21_DATA[m].ADDYMD		;		// 登録日
    			SGr_List->Cells[8][i+k]  = pKSM21_DATA[m].ADDTIM		;		// 登録時間
    			SGr_List->Cells[4][i+k]  = pKSM21_DATA[m].UPDYMD		;		// 変更日
    			SGr_List->Cells[9][i+k]  = pKSM21_DATA[m].UPDTIM		;		// 変更時間
    			SGr_List->Cells[6][i+k]  = pKSM21_DATA[m].UPDCHR		;		// 更新者（コード）
    			SGr_List->Cells[5][i+k]  = pKSM21_DATA[m].UPDNAM		;		// 更新者（名称）
    			SGr_List->Cells[10][i+k] = pKSM21_DATA[m].UPDCNT		;		// 更新回数
            	SGr_List->Cells[14][i+k] = "1"							;
				m++;
        	}
        }

    	// 移動先の行を選択範囲を決定します
		myRect.Left		= SGr_List->Selection.Left;
		myRect.Top		= ToIndex;
		myRect.Right	= SGr_List->Selection.Right;
		myRect.Bottom	= ToIndex + CopyCnt;
    }

    // メモリの開放
    if( hMemCopy ){
        GlobalUnlock( hMemCopy );
        GlobalFree( hMemCopy );
    }


    // 移動先の行を選択します
    SGr_List->Row   = myRect.Top;
    SGr_List->Selection	= myRect;
    SGr_ListSelectCell(Sender,1,SGr_List->Row,true);

    iRowSelTop    = SGr_List->Selection.Top;
    iRowSelBottom = SGr_List->Selection.Bottom;

    // データを変更したフラグ
    DataSave = true;
    BtnF11->Enabled = true;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnSelectCellイベント：StringGridのセルが選択される前に発生します。
//
//  機能説明
//    StringGridで選択されたら、画面下部のTextBoxにセットします
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

    if(ARow == 0) ARow = 1;
    ROWPOINT = ARow;

    // 項目名（日本語）
    if ( Trim(SGr_List->Cells[1][ARow]) == "" ){
        EdtKMK_NM_JPN->Text = "";
    }
    else{
        EdtKMK_NM_JPN->Text = SGr_List->Cells[1][ARow];
    }

    // 項目名（英語）
    if ( Trim(SGr_List->Cells[2][ARow]) == "" ){
        EdtKMK_NM_ENG->Text = "";
    }
    else{
        EdtKMK_NM_ENG->Text = SGr_List->Cells[2][ARow];
    }

    // 更新日
    PnlUPDYMD->Caption = SGr_List->Cells[4][ARow];

    // 更新者
    PnlUPDCHR->Caption = SGr_List->Cells[5][ARow];

    // 修正･削除の為に「項目No」を記憶します。
    if( SGr_List->Cells[12][ARow] == "" ){
        PnlUPDYMD->Tag = -1;
    }
    else {
        PnlUPDYMD->Tag = StrToInt(SGr_List->Cells[12][ARow]);
    }

    // 更新回数を記憶します。
    if( SGr_List->Cells[10][ARow] == "" ){
    	PnlUPDCHR->Tag = -1;
    }
    else {
    	PnlUPDCHR->Tag = StrToInt(SGr_List->Cells[10][ARow]);
    }

    // 更新・削除不可能項目の場合、修正・削除ボタンを利用不可にします。
    if( SGr_List->Cells[11][ARow] == 1 || PnlUPDYMD->Tag == -1 ){
		BtnF09->Enabled = false;
		BtnF10->Enabled = false;
        /* 新規登録させたいのでEditの利用不可はやめる
        EdtKMK_NM_JPN->ReadOnly = true;
        EdtKMK_NM_ENG->ReadOnly = true;
		EdtKMK_NM_JPN->Font->Color = clRed;
		EdtKMK_NM_ENG->Font->Color = clRed;
    	*/
    }
    else{
		BtnF09->Enabled = true;
		BtnF10->Enabled = true;
        /* 新規登録させたいのでEditの利用不可はやめる
        EdtKMK_NM_JPN->ReadOnly = false;
        EdtKMK_NM_ENG->ReadOnly = false;
		EdtKMK_NM_JPN->Font->Color = clWindowText;
		EdtKMK_NM_ENG->Font->Color = clWindowText;
		*/
    }

    // 修正前の値を保存します
    sEdtKMK_NM_JPN_Old = EdtKMK_NM_JPN->Text;
    sEdtKMK_NM_ENG_Old = EdtKMK_NM_ENG->Text;

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
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    AnsiString sBuf;
    // ステータスメッセージ
    if(SBr1->Panels->Items[0]->Text != ""){
        SBr1->Panels->Items[0]->Text = "";
        SBr1->Update();
    }

     switch(Key)
     {
         //case VK_F1:  BtnF01Click(Sender);    Key = 0; break;
         case VK_F2:  BtnF02Click(Sender);    Key = 0; break;
         case VK_F3:  BtnF03Click(Sender);    Key = 0; break;
         case VK_F5:  BtnF05Click(Sender);    Key = 0; break;
         //case VK_F7:  BtnF07Click(Sender);    Key = 0; break;
         case VK_F8:  BtnF08Click(Sender);    Key = 0; break;
         case VK_F9:  BtnF09Click(Sender);    Key = 0; break;
         case VK_F10: BtnF10Click(Sender);    Key = 0; break;
         case VK_F11: BtnF11Click(Sender);    Key = 0; break;
         case VK_F12: BtnF12Click(Sender);    Key = 0; break;

         // Enter
         case VK_RETURN:
                if( EdtKMK_NM_JPN->Focused() || SGr_List->Focused() ){
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                // 詳細部
                if( EdtKMK_NM_ENG->Focused() ){
                    BtnF08->SetFocus();
                    break;
                }
                break;

     }

}

//---------------------------------------------------------------------------
//
//  概要
//    OnDrawCellイベント：グリッド内のセルを描画する必要があるときに発生します。
//
//  機能説明
//    グリッド内のセル描画をコントロールします
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

   RECT r=RECT(Rect);

   //固定セルの背景色をセット
   if(State.Contains(gdFixed))
       SGr_List->Canvas->Brush->Color= SGr_List->FixedColor;
   //フォーカスのあるセルの背景色をセット
//   else if(State.Contains(gdFocused))
//       SGr1->Canvas->Brush->Color= SGr1->Options.Contains(goDrawFocusSelected)? clHighlight: SGr1->Color;
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
//       SGr1->Canvas->Font->Color= SGr1->Options.Contains(goDrawFocusSelected)? clHighlightText: SGr1->Font->Color;
//       //フォーカス枠を描く
//       DrawFocusRect(SGr1->Canvas->Handle,&r);
	   //選択されているセルの文字色をセット
       //if(State.Contains(gdSelected))

       //修正・削除不可能データの場合の文字色をセット
       if( ACol > 0 && SGr_List->Cells[11][ARow].ToIntDef(0) > 0 )
           SGr_List->Canvas->Font->Color = clRed;
       else
           SGr_List->Canvas->Font->Color= clHighlightText;
   }
   //選択されているセルの文字色をセット
   else if(State.Contains(gdSelected))
       if( ACol > 0 && SGr_List->Cells[11][ARow].ToIntDef(0) > 0 )
           SGr_List->Canvas->Font->Color = clRed;
       else
           SGr_List->Canvas->Font->Color= clHighlightText;
   //修正・削除不可能データの場合の文字色をセット
   else if( ACol > 0 && SGr_List->Cells[11][ARow].ToIntDef(0) > 0 )
       SGr_List->Canvas->Font->Color = clRed;
   //普通のセルの文字色をセット
   else
       SGr_List->Canvas->Font->Color= SGr_List->Font->Color;

   //テキスト表示領域の設定
   InflateRect(&r,-2,-2);

   //テキストの表示
   DrawText(SGr_List->Canvas->Handle,SGr_List->Cells[ACol][ARow].c_str(),-1,&r,0); //左寄せ

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
void __fastcall TForm1::RowExchange(int FromIndex, int ToIndex)
{
    int			i;
	TGridRect	myRect;
    AnsiString	sBuf;
    AnsiString	sLineNo;

    // 入れ替え先のデータをバックアップ
    sLineNo = SGr_List->Cells[0][ToIndex];						// 行番号
    sBuf = SGr_List->Cells[12][ToIndex];
    strcpy( tmpKSM21_DATA.KMK_NO		,sBuf.c_str() );		// 項目NO
    sBuf = SGr_List->Cells[13][ToIndex];
    strcpy( tmpKSM21_DATA.ORDER_NO		,sBuf.c_str() );		// 表示順
    sBuf = SGr_List->Cells[1][ToIndex];
    strcpy( tmpKSM21_DATA.KMK_NM_JPN	,sBuf.c_str() );		// 項目名（日本語）
    sBuf = SGr_List->Cells[2][ToIndex];
    strcpy( tmpKSM21_DATA.KMK_NM_ENG	,sBuf.c_str() );		// 項目名（英語）
    sBuf = SGr_List->Cells[11][ToIndex];
    strcpy( tmpKSM21_DATA.NOUPD_FLG		,sBuf.c_str() );		// 修正･削除不可能項目
    sBuf = SGr_List->Cells[7][ToIndex];
    strcpy( tmpKSM21_DATA.ADDYMD		,sBuf.c_str() );		// 登録日
    sBuf = SGr_List->Cells[8][ToIndex];
    strcpy( tmpKSM21_DATA.ADDTIM		,sBuf.c_str() );		// 登録時間
    sBuf = SGr_List->Cells[4][ToIndex];
    strcpy( tmpKSM21_DATA.UPDYMD		,sBuf.c_str() );		// 変更日
    sBuf = SGr_List->Cells[9][ToIndex];
    strcpy( tmpKSM21_DATA.UPDTIM		,sBuf.c_str() );		// 変更時間
    sBuf = SGr_List->Cells[6][ToIndex];
    strcpy( tmpKSM21_DATA.UPDCHR		,sBuf.c_str() );		// 更新者（コード）
    sBuf = SGr_List->Cells[5][ToIndex];
    strcpy( tmpKSM21_DATA.UPDNAM		,sBuf.c_str() );		// 更新者（名称）
    sBuf = SGr_List->Cells[10][ToIndex];
    strcpy( tmpKSM21_DATA.UPDCNT		,sBuf.c_str() );		// 更新回数
    sBuf = SGr_List->Cells[14][ToIndex];                        // 変更フラグ

    if( ToIndex > FromIndex ){
		// 上下を入れ替えます
    	for( i=ToIndex; i>FromIndex; i-- ) {
    		SGr_List->Cells[0][i] = SGr_List->Cells[0][i-1];
    		SGr_List->Cells[1][i] = SGr_List->Cells[1][i-1];
    		SGr_List->Cells[2][i] = SGr_List->Cells[2][i-1];
    		SGr_List->Cells[3][i] = SGr_List->Cells[3][i-1];
    		SGr_List->Cells[4][i] = SGr_List->Cells[4][i-1];
    		SGr_List->Cells[5][i] = SGr_List->Cells[5][i-1];
    		SGr_List->Cells[6][i] = SGr_List->Cells[6][i-1];
    		SGr_List->Cells[7][i] = SGr_List->Cells[7][i-1];
    		SGr_List->Cells[8][i] = SGr_List->Cells[8][i-1];
    		SGr_List->Cells[9][i] = SGr_List->Cells[9][i-1];
    		SGr_List->Cells[10][i] = SGr_List->Cells[10][i-1];
    		SGr_List->Cells[11][i] = SGr_List->Cells[11][i-1];
    		SGr_List->Cells[12][i] = SGr_List->Cells[12][i-1];
    		SGr_List->Cells[13][i] = SGr_List->Cells[13][i-1];
			SGr_List->Cells[14][i] = SGr_List->Cells[14][i-1];
    	}
    }
    else{
		// 上下を入れ替えます
    	for( i=ToIndex; i<FromIndex; i++ ) {
    		SGr_List->Cells[0][i] = SGr_List->Cells[0][i+1];
    		SGr_List->Cells[1][i] = SGr_List->Cells[1][i+1];
    		SGr_List->Cells[2][i] = SGr_List->Cells[2][i+1];
    		SGr_List->Cells[3][i] = SGr_List->Cells[3][i+1];
    		SGr_List->Cells[4][i] = SGr_List->Cells[4][i+1];
    		SGr_List->Cells[5][i] = SGr_List->Cells[5][i+1];
    		SGr_List->Cells[6][i] = SGr_List->Cells[6][i+1];
    		SGr_List->Cells[7][i] = SGr_List->Cells[7][i+1];
    		SGr_List->Cells[8][i] = SGr_List->Cells[8][i+1];
    		SGr_List->Cells[9][i] = SGr_List->Cells[9][i+1];
    		SGr_List->Cells[10][i] = SGr_List->Cells[10][i+1];
    		SGr_List->Cells[11][i] = SGr_List->Cells[11][i+1];
    		SGr_List->Cells[12][i] = SGr_List->Cells[12][i+1];
    		SGr_List->Cells[13][i] = SGr_List->Cells[13][i+1];
			SGr_List->Cells[14][i] = SGr_List->Cells[14][i+1];
    	}
    }

    // バックアップしたデータを元にもどします。
    SGr_List->Cells[0][FromIndex]  = sLineNo					;	// 行番号
	SGr_List->Cells[12][FromIndex] = tmpKSM21_DATA.KMK_NO		;	// 項目NO
	SGr_List->Cells[13][FromIndex] = tmpKSM21_DATA.ORDER_NO		;	// 表示順
	SGr_List->Cells[1][FromIndex]  = tmpKSM21_DATA.KMK_NM_JPN	;	// 項目名（日本語）
	SGr_List->Cells[2][FromIndex]  = tmpKSM21_DATA.KMK_NM_ENG	;	// 項目名（英語）
	SGr_List->Cells[11][FromIndex] = tmpKSM21_DATA.NOUPD_FLG	;	// 修正･削除不可能項目
	SGr_List->Cells[7][FromIndex]  = tmpKSM21_DATA.ADDYMD		;	// 登録日
	SGr_List->Cells[8][FromIndex]  = tmpKSM21_DATA.ADDTIM		;	// 登録時間
	SGr_List->Cells[4][FromIndex]  = tmpKSM21_DATA.UPDYMD		;	// 変更日
	SGr_List->Cells[9][FromIndex]  = tmpKSM21_DATA.UPDTIM		;	// 変更時間
	SGr_List->Cells[6][FromIndex]  = tmpKSM21_DATA.UPDCHR		;	// 更新者（コード）
	SGr_List->Cells[5][FromIndex]  = tmpKSM21_DATA.UPDNAM		;	// 更新者（名称）
	SGr_List->Cells[10][FromIndex] = tmpKSM21_DATA.UPDCNT		;	// 更新回数
    SGr_List->Cells[14][FromIndex] = sBuf						;	// 変更フラグ

    // 選択し直します
    //SGr_List->Row	= iRowSelTop;
	myRect.Left		= SGr_List->Selection.Left;
	myRect.Top		= iRowSelTop;
	myRect.Right	= SGr_List->Selection.Right;
	myRect.Bottom	= iRowSelBottom;
    SGr_List->Selection	= myRect;
    //SGr_ListSelectCell(Sender,1,SGr_List->Row,true);

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
//    AnsiString str	：対象のシートNO
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
//    自作関数			：担当者コードから担当者名を検索する
//
//  機能説明
//    担当者コードから担当者名を検索する
//
//  パラメタ説明
//    AnsiString strTANSYA：呼び出し元のVCLオブジェクト
//
//  戻り値
//    AnsiString		：検索した担当者名
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::GetTANNAM(AnsiString strTANSYA)
{

    AnsiString sBuf;

    if( strTANSYA == "0" ){
    	return "管理者";
    }

    // Initial Query
    Query2->Close();
    Query2->SQL->Clear();

    // 問合せ文作成
	sBuf = "SELECT TANNAM FROM SM12S";
	sBuf += " WHERE TANSYA=" + strTANSYA;

    Query2->SQL->Add(sBuf);
    Query2->Open();
    Query2->Active = true;

    if ( Query2->Bof == true && Query2->Eof == true)
    {
       return strTANSYA;
		//return " ";
    }
    else
    {
        Query2->First();
        sBuf = Form1->Query2->FieldValues["TANNAM"];
        return sBuf;
    }
}

//---------------------------------------------------------------------------
//
//  概要
//    OnChangeイベント	：編集コントロールのテキストに変更が加えられたときに発生します。
//
//  機能説明
//    入力文字(シングルコーテーション)のチェックを行ないます。
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
}

