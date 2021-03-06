//---------------------------------------------------------------------------
//
//  Unit1.cpp
//    【出荷検査システム−レポート出力】
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
//    各変数を初期設定します
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

	char 		CDPath[256];

    // データベース初期化
    Database1->Open();

    // StringList初期化
	sLots		= new TStringList;
	sHins		= new TStringList;
    sDtkshins	= new TStringList;
	sTITLE_JPN	= new TStringList;
	sTITLE_ENG	= new TStringList;

    //2003.05.26 E.Takase Add ↓
	sCRSF_KSD11_SKTYMDMin	= new TStringList;  	//ロット毎の日付最小値
	sCRSF_KSD11_SKTYMDStr	= new TStringList;  	//ロット毎の日付をカンマ区切りで
	sCRSF_KSD11_UPDCHR		= new TStringList;     	//ロット毎の代表更新者(CSV出力時に使用)
	sCRSF_KSD11_SKTYMD		= new TStringList;     	//ロット毎の日付(CSV出力時に使用)
    //2003.05.26 E.Takase Add ↑

    //カレントディレクトリの取得
    strcpy(CDPath, "X:\\");	/* 値を返す形式: X:\ で文字列を満たす */
    CDPath[0] = 'A' + getdisk();	/* X を現在のドライブ名に置き換える */
    getcurdir(0, CDPath+3);	/* 文字列部分の残りにカレントディレクトリを追加 */

    // 印刷指示用ワークファイル名を決定します
    strcpy(sRepData1,CDPath);
    strcpy(sRepData2,CDPath);
    strcpy(sRepData3,CDPath);
    strcpy(sRepData4,CDPath);
    strcpy(sRepData5_1,CDPath);
    strcpy(sRepData5_2,CDPath);
    strcpy(sRepData5_3,CDPath);
	strcpy(sRepData6_1,CDPath);
 	strcpy(sRepData6_2,CDPath);
	strcpy(sRepData6_3,CDPath);
    strcat(sRepData1,   "\\Reports\\RepData1.csv");
    strcat(sRepData2,   "\\Reports\\RepData2.csv");
    strcat(sRepData3,   "\\Reports\\RepData3.csv");
    strcat(sRepData4,   "\\Reports\\RepData4.csv");
    strcat(sRepData5_1, "\\Reports\\RepData5_1.csv");
    strcat(sRepData5_2, "\\Reports\\RepData5_2.csv");
    strcat(sRepData5_3, "\\Reports\\RepData5_3.csv");
	strcat(sRepData6_1, "\\Reports\\RepData6_1.csv");
	strcat(sRepData6_2, "\\Reports\\RepData6_2.csv");
	strcat(sRepData6_3, "\\Reports\\RepData6_3.csv");

    // 印刷用エクセルファイル名を決定します
    strcpy(sRepExcel1,CDPath);
    strcpy(sRepExcel2,CDPath);
    strcpy(sRepExcel3,CDPath);
    strcpy(sRepExcel4,CDPath);
    strcpy(sRepExcel5,CDPath);
    strcpy(sRepExcel6,CDPath);
    //20170419 Y.Onishi 旧Ver検査成績書の出力に対応
    strcpy(sRepExcel7,CDPath);
    
    strcat(sRepExcel1, "\\Reports\\検査成績書.xls");
    strcat(sRepExcel2, "\\Reports\\検査成績書(月別).xls");
    strcat(sRepExcel3, "\\Reports\\材料証明書.xls");
    strcat(sRepExcel4, "\\Reports\\材料証明書（月別）.xls");
    strcat(sRepExcel5, "\\Reports\\検査結果時系列管理表.xls");
    strcat(sRepExcel6, "\\Reports\\検査経歴票.xls");
    //20170419 Y.Onishi 旧Ver検査成績書の出力に対応
    strcat(sRepExcel7, "\\Reports\\検査成績書_new.xls");

	AnsiString sDATE, sYY, sMM, sDD;                                  //onishi 検索日付初期化
    int iYY;
    sDATE = FormatDateTime("yyyymmdd",Date()).c_str();
    sYY = sDATE.SubString(1,4);
    iYY = sYY.ToInt() - 3;                                            //onishi 3年前から
    sYY = AnsiString().sprintf("%d",iYY);
    sMM = sDATE.SubString(5,2);
    sDD = sDATE.SubString(7,2);
    sDATE = sYY + sMM + sDD;
    Edt_SEIKAN_YMD->Text = sDATE;
}

//---------------------------------------------------------------------------
//
//  概要
//    OnActivateイベント	：フォームがアクティブになったときに発生します。
//
//  機能説明
//    初期状態で必要な検索処理を行ないます
//    【検査成績書タイトル項目マスターの検索】
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
    int			iRow;
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
    Clb1_CHK_TITLE->Clear();
    Clb2_CHK_TITLE->Clear();
    Clb3_CHK_TITLE->Clear();
    Clb4_CHK_TITLE->Clear();
    sTITLE_JPN->Clear();
    sTITLE_ENG->Clear();
    while( !Query1->Eof ){

        // タイトル名をチェックリストボックスに追加
        sBuf  = Query1->FieldValues["KMK_NM_JPN"];
        sTITLE_JPN->Add(sBuf);
        if( !VarIsNull(Query1->FieldValues["KMK_NM_ENG"]) ){
        	sBuf += "(" + AnsiString(Query1->FieldValues["KMK_NM_ENG"]) + ")";
        	sTITLE_ENG->Add(Query1->FieldValues["KMK_NM_ENG"]);
        }
        else {
        	sTITLE_ENG->Add("");
        }
        Clb1_CHK_TITLE->Items->Add(sBuf);
        Clb2_CHK_TITLE->Items->Add(sBuf);
        Clb3_CHK_TITLE->Items->Add(sBuf);
        Clb4_CHK_TITLE->Items->Add(sBuf);

        // タイトル項目Noを記憶（配列番号は、チェックリストボックスのItemインデックス）
        iTITLE[iRow] = Query1->FieldValues["KMK_NO"];
        iRow++;

        // カーソルを次にセットする
        Query1->Next();
    }

}

//---------------------------------------------------------------------------
//
//  概要
//    OnCloseQueryイベント：Close メソッドが呼び出されたときまたはユーザーが
//          フォームのシステムメニューで［閉じる］を選択したときに発生します。
//
//  機能説明
//    開放処理を行ないます。
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

    //2003/10/22 E.Takase
    //ワークテーブルを初期化
    bool bRtn = KSDDeleteData();

	// データベース接続を開放します
    Query1->Close();
    Query2->Close();
    Query3->Close();
    Q_CRSub_KSD01->Close();
    Q_CRSub_KSD11->Close();
    Q_CRSub_KSD02->Close();
    Q_CRSub_KSD12->Close();
    Q_CRSub_KSD03->Close();
    Q_CRSub_TANSYA->Close();

	Database1->Close();

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ１：一覧検索」ボタンを押した時の処理
//
//  機能説明
//    一覧検索フォーム（Form2）を表示します。
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

    ////////////////////
    // 一覧検索
    Form2->ShowModal();

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ２：前項」ボタンを押した時の処理
//
//  機能説明
//    [Shift]+[TAB]キーコードのイベントを発生させます。
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
//    [TAB]キーコードのイベントを発生させます。
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

	keybd_event(VK_TAB,0,0,0);
	keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);

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
//    OnClickイベント	：「Ｆ７：内容確認」ボタンを押した時の処理
//
//  機能説明
//    「出力内容確認」ボタンを押します。
//    指定された印刷条件により詳細情報の検索処理を開始します
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
	if( !BtnF07->Enabled ) return;

    Btn1_OUT_CHECKClick(Sender);

    return;
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ９：Excel印刷」ボタンを押した時の処理
//
//  機能説明
//    指定された印刷条件によりレポート作成処理を開始します
//    印刷指示CSVファイル作成→Excel起動→印刷→Excel終了
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
	if( !BtnF09->Enabled )    return;

    // レポート作成処理開始
    CreateReport(0);

	return;
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ１０：Excel出力」ボタンを押した時の処理
//
//  機能説明
//    指定された印刷条件によりレポート作成処理を開始します
//    印刷指示CSVファイル作成→Excel起動
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
	if( !BtnF10->Enabled )    return;

    // レポート作成処理開始
    CreateReport(1);

	return;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ１２：戻る」ボタンを押した時の処理
//
//  機能説明
//    メインフォームをCloseします
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
//    OnClickイベント	：「出力内容の確認」ボタンを押した時の処理
//
//  機能説明
//    各レポートタブの選択状態を判断します
//    指定された印刷条件により詳細情報の検索します
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
void __fastcall TForm1::Btn1_OUT_CHECKClick(TObject *Sender)
{

    int				i;
    int				iType;
    bool			iSEL_SZ;
    bool			iSEL_SK;
    int				iSEL_TK;	// 2004/09/24 A.Tamura 「無効」を追加
    bool			iSEL_ZR;
    AnsiString		sBuf, sBuf2;
    TEdit*			edt_DTKSHIN;
    TEdit*			edt_LOTNO;
    TMaskEdit*		edt_DATE1;
    TMaskEdit*		edt_DATE2;
    TEdit*			edt_CUSTOM;
    TTabSheet*		tst_LOTNO;
    TCheckListBox*	clb_TITLE;
    TCheckListBox*	clb_LOTNO;
    TRadioButton*	rdo_X_ON;
    TRadioButton*	rdo_X_OFF;
    //20161214 Y.Onishi
    //Cp,Cpk出力に対応
    TRadioButton*	rdo_X_CP;


    // 戻り値初期化
	ret_Btn1_OUT_CHECKClick = true;

	if( PgCtr_REPORT->ActivePage->Name == "TabSheet1" ){
        //----------------------------------------------
        // 検査成績書
        iNowTab = 1;

        iType = 1;

    	edt_DTKSHIN	= dynamic_cast<TEdit*>(Edt1_WHR_DTKSHIN);
    	edt_LOTNO	= dynamic_cast<TEdit*>(Edt1_WHR_LOTNO);
        edt_CUSTOM	= dynamic_cast<TEdit*>(Edt1_CHK_CUSTOMER);
        tst_LOTNO	= dynamic_cast<TTabSheet*>(PgCtr1_tst01);
        clb_TITLE	= dynamic_cast<TCheckListBox*>(Clb1_CHK_TITLE);
        rdo_X_ON	= dynamic_cast<TRadioButton*>(Rdo1_CHK_X_ON);
        rdo_X_OFF	= dynamic_cast<TRadioButton*>(Rdo1_CHK_X_OFF);
        //20161214 Y.Onishi
        //Cp,Cpk出力に対応
        rdo_X_CP	= dynamic_cast<TRadioButton*>(Rdo1_CHK_X_CP);

		// 選択オプションの状態を取得します
		if( Rdo1_WHR_SOZAI_ON->Checked == true )	iSEL_SZ = true;
		else										iSEL_SZ = false;
		if( Rdo1_WHR_SYUKA_ON->Checked == true )	iSEL_SK = true;
		else										iSEL_SK = false;
		if( Rdo1_WHR_TOKUBETSU_ON->Checked == true )		iSEL_TK =  1;	// する
		else if( Rdo1_WHR_TOKUBETSU_OFF->Checked == true )	iSEL_TK =  0;   // しない
		else												iSEL_TK = -1;   // 無効
		if( Rdo1_WHR_ZAIRYOU_ON->Checked == true )	iSEL_ZR = true;
		else										iSEL_ZR = false;

    }
    else if( PgCtr_REPORT->ActivePage->Name == "TabSheet2" ){
        //----------------------------------------------
        // 検査成績書（月別）
        iNowTab = 2;

        if( Rdo2_WHR_TYPE1->Checked == true ){
        	// 品番・ロットによる検索
        	iType = 1;

    		edt_DTKSHIN	= dynamic_cast<TEdit*>(Edt2_WHR_DTKSHIN1);
    		edt_LOTNO	= dynamic_cast<TEdit*>(Edt2_WHR_LOTNO1);
        } else {
        	// 品番・出荷日による検索
        	iType = 2;

    		edt_DTKSHIN	= dynamic_cast<TEdit*>(Edt2_WHR_DTKSHIN2);
    		edt_DATE1	= dynamic_cast<TMaskEdit*>(Edt2_WHR_SYUKADATE1);
    		edt_DATE2	= dynamic_cast<TMaskEdit*>(Edt2_WHR_SYUKADATE2);
        }

        edt_CUSTOM	= dynamic_cast<TEdit*>(Edt2_CHK_CUSTOMER);
        clb_LOTNO	= dynamic_cast<TCheckListBox*>(Clb2_CHK_LOT);
        clb_TITLE	= dynamic_cast<TCheckListBox*>(Clb2_CHK_TITLE);
        rdo_X_ON	= dynamic_cast<TRadioButton*>(Rdo2_CHK_X_ON);
        rdo_X_OFF	= dynamic_cast<TRadioButton*>(Rdo2_CHK_X_OFF);

		// 選択オプションの状態を取得します
		if( Rdo2_WHR_SOZAI_ON->Checked == true )	iSEL_SZ = true;
		else										iSEL_SZ = false;
		if( Rdo2_WHR_SYUKA_ON->Checked == true )	iSEL_SK = true;
		else										iSEL_SK = false;
		if( Rdo2_WHR_TOKUBETSU_ON->Checked == true )		iSEL_TK =  1;	// する
		else if( Rdo2_WHR_TOKUBETSU_OFF->Checked == true )	iSEL_TK =  0;   // しない
		else												iSEL_TK = -1;   // 無効
		if( Rdo2_WHR_ZAIRYOU_ON->Checked == true )	iSEL_ZR = true;
		else										iSEL_ZR = false;

    }
    else if( PgCtr_REPORT->ActivePage->Name == "TabSheet3" ){
        //----------------------------------------------
        // 材料証明書
        iNowTab = 3;

        iType = 1;

    	edt_DTKSHIN	= dynamic_cast<TEdit*>(Edt3_WHR_DTKSHIN);
    	edt_LOTNO	= dynamic_cast<TEdit*>(Edt3_WHR_LOTNO);
        edt_CUSTOM	= dynamic_cast<TEdit*>(Edt3_CHK_CUSTOMER);
        tst_LOTNO	= dynamic_cast<TTabSheet*>(PgCtr3_tst01);
        clb_TITLE	= dynamic_cast<TCheckListBox*>(Clb3_CHK_TITLE);
        rdo_X_ON	= dynamic_cast<TRadioButton*>(Rdo3_CHK_X_ON);
        rdo_X_OFF	= dynamic_cast<TRadioButton*>(Rdo3_CHK_X_OFF);

		// 選択オプションの状態を取得します
		if( Rdo3_WHR_SOZAI_ON->Checked == true )	iSEL_SZ = true;
		else										iSEL_SZ = false;
		if( Rdo3_WHR_SYUKA_ON->Checked == true )	iSEL_SK = true;
		else										iSEL_SK = false;
		if( Rdo3_WHR_TOKUBETSU_ON->Checked == true )		iSEL_TK =  1;	// する
		else if( Rdo3_WHR_TOKUBETSU_OFF->Checked == true )	iSEL_TK =  0;   // しない
		else												iSEL_TK = -1;   // 無効
		if( Rdo3_WHR_ZAIRYOU_ON->Checked == true )	iSEL_ZR = true;
		else										iSEL_ZR = false;

    }
    else if( PgCtr_REPORT->ActivePage->Name == "TabSheet4" ){
        //----------------------------------------------
        // 材料証明書（月別）
        iNowTab = 4;

        if( Rdo4_WHR_TYPE1->Checked == true ){
        	// 品番・ロットによる検索
        	iType = 1;

    		edt_DTKSHIN	= dynamic_cast<TEdit*>(Edt4_WHR_DTKSHIN1);
    		edt_LOTNO	= dynamic_cast<TEdit*>(Edt4_WHR_LOTNO1);
        } else {
        	// 品番・出荷日による検索
        	iType = 2;

    		edt_DTKSHIN	= dynamic_cast<TEdit*>(Edt4_WHR_DTKSHIN2);
    		edt_DATE1	= dynamic_cast<TMaskEdit*>(Edt4_WHR_SYUKADATE1);
    		edt_DATE2	= dynamic_cast<TMaskEdit*>(Edt4_WHR_SYUKADATE2);
        }

        edt_CUSTOM	= dynamic_cast<TEdit*>(Edt4_CHK_CUSTOMER);
        clb_LOTNO	= dynamic_cast<TCheckListBox*>(Clb4_CHK_LOT);
        clb_TITLE	= dynamic_cast<TCheckListBox*>(Clb4_CHK_TITLE);
        rdo_X_ON	= dynamic_cast<TRadioButton*>(Rdo4_CHK_X_ON);
        rdo_X_OFF	= dynamic_cast<TRadioButton*>(Rdo4_CHK_X_OFF);

		// 選択オプションの状態を取得します
		if( Rdo4_WHR_SOZAI_ON->Checked == true )	iSEL_SZ = true;
		else										iSEL_SZ = false;
		if( Rdo4_WHR_SYUKA_ON->Checked == true )	iSEL_SK = true;
		else										iSEL_SK = false;
		if( Rdo4_WHR_TOKUBETSU_ON->Checked == true )		iSEL_TK =  1;	// する
		else if( Rdo4_WHR_TOKUBETSU_OFF->Checked == true )	iSEL_TK =  0;   // しない
		else												iSEL_TK = -1;   // 無効
		if( Rdo4_WHR_ZAIRYOU_ON->Checked == true )	iSEL_ZR = true;
		else										iSEL_ZR = false;

    }
    else if( PgCtr_REPORT->ActivePage->Name == "TabSheet5" ){
        //----------------------------------------------
        // 検査結果時系列管理表
        iNowTab = 5;

        if( Rdo5_WHR_TYPE1->Checked == true ){
        	// 品番・ロットによる検索
        	iType = 1;

    		edt_DTKSHIN	= dynamic_cast<TEdit*>(Edt5_WHR_DTKSHIN1);
    		edt_LOTNO	= dynamic_cast<TEdit*>(Edt5_WHR_LOTNO);
        } else {
        	// 品番・出荷日による検索
        	iType = 2;

    		edt_DTKSHIN	= dynamic_cast<TEdit*>(Edt5_WHR_DTKSHIN1);
    		edt_DATE1	= dynamic_cast<TMaskEdit*>(Edt5_WHR_SYUKADATE1);
    		edt_DATE2	= dynamic_cast<TMaskEdit*>(Edt5_WHR_SYUKADATE2);
        }

        edt_CUSTOM	= dynamic_cast<TEdit*>(Edt5_CHK_CUSTOMER);
        clb_LOTNO	= dynamic_cast<TCheckListBox*>(Clb5_CHK_LOT);

		// 選択オプションの状態を取得します
		if( Rdo5_WHR_SOZAI_ON->Checked == true )	iSEL_SZ = true;
		else										iSEL_SZ = false;
		if( Rdo5_WHR_SYUKA_ON->Checked == true )	iSEL_SK = true;
		else										iSEL_SK = false;
		if( Rdo5_WHR_TOKUBETSU_ON->Checked == true )		iSEL_TK =  1;	// する
		else if( Rdo5_WHR_TOKUBETSU_OFF->Checked == true )	iSEL_TK =  0;   // しない
		else												iSEL_TK = -1;   // 無効
		if( Rdo5_WHR_ZAIRYOU_ON->Checked == true )	iSEL_ZR = true;
		else										iSEL_ZR = false;

    }
    else if( PgCtr_REPORT->ActivePage->Name == "TabSheet6" ){
        //----------------------------------------------
        // 検査経歴票
        iNowTab = 6;

        if( Rdo6_WHR_TYPE1->Checked == true ){
            //2003/08/28 E.Takase
        	//// 品番・ロットによる検索
        	//iType = 1;
        	// 品番・ロットによる検索(未測定のロット出力)
        	iType = 4;

    		edt_DTKSHIN	= dynamic_cast<TEdit*>(Edt6_WHR_DTKSHIN1);
    		edt_LOTNO	= dynamic_cast<TEdit*>(Edt6_WHR_LOTNO1);
        } else {
        	// 検査日による検索
        	iType = 3;

    		edt_DATE1	= dynamic_cast<TMaskEdit*>(Edt6_WHR_KENSADATE1);
    		edt_DATE2	= dynamic_cast<TMaskEdit*>(Edt6_WHR_KENSADATE2);
        }

        clb_LOTNO	= dynamic_cast<TCheckListBox*>(Clb6_CHK_LOT);

		// 選択オプションの状態を取得します
		if( Rdo6_WHR_SOZAI_ON->Checked == true )	iSEL_SZ = true;
		else										iSEL_SZ = false;
		if( Rdo6_WHR_SYUKA_ON->Checked == true )	iSEL_SK = true;
		else										iSEL_SK = false;
		if( Rdo6_WHR_TOKUBETSU_ON->Checked == true )		iSEL_TK =  1;	// する
		else if( Rdo6_WHR_TOKUBETSU_OFF->Checked == true )	iSEL_TK =  0;   // しない
		else												iSEL_TK = -1;   // 無効
		if( Rdo6_WHR_ZAIRYOU_ON->Checked == true )	iSEL_ZR = true;
		else										iSEL_ZR = false;

    }

	// 指定された品番・ロットNoが測定済みかどうか判断します。
   	// 指定された品番・日付（出荷日・検査日）が測定済みかどうか判断します。
	if( Get_DTKSHIN_LOT( iType, edt_DTKSHIN, edt_LOTNO,
              edt_DATE1, edt_DATE2, iSEL_SZ, iSEL_SK, iSEL_TK, iSEL_ZR) == false){
    	// 戻り値初期化
		ret_Btn1_OUT_CHECKClick = false;
   		return;
   	}

    // 1個目のロットTabSheetを作成します
    if( sLots->Count >= 1 ){

        // 出力ロットTabSheetの一枚目にロット番号を表示します
		if( PgCtr_REPORT->ActivePage->Name == "TabSheet1" ||
        	PgCtr_REPORT->ActivePage->Name == "TabSheet3" ){
        	// 検査成績書
            // 材料証明書

    		tst_LOTNO->Caption = sLots->Strings[0];
        }

        // 出力対象のロットを選択状態で表示します
        //2003/08/28 E.Takase
		//if( PgCtr_REPORT->ActivePage->Name == "TabSheet2" ||
        //	PgCtr_REPORT->ActivePage->Name == "TabSheet4" ||
        //	PgCtr_REPORT->ActivePage->Name == "TabSheet5" ||
        //    ( PgCtr_REPORT->ActivePage->Name == "TabSheet6" && iType == 1 ) ){
		if( PgCtr_REPORT->ActivePage->Name == "TabSheet2" ||
        	PgCtr_REPORT->ActivePage->Name == "TabSheet4" ||
        	PgCtr_REPORT->ActivePage->Name == "TabSheet5" ||
            ( PgCtr_REPORT->ActivePage->Name == "TabSheet6" && ( iType == 1 || iType == 4 )) ){
        	// 検査成績書（月別）
            // 材料証明書（月別）
            // 検査結果時系列管理表

			clb_LOTNO->Clear();
			for( i = 0; i < sLots->Count; i++){
			    clb_LOTNO->Items->Add(sLots->Strings[i]);
				clb_LOTNO->Checked[clb_LOTNO->Items->Count-1] = true;
            }
        }

        // 出力対象のロットを選択状態で表示します
		if( PgCtr_REPORT->ActivePage->Name == "TabSheet6" && iType == 3 ){
        	// 検査経歴票

			clb_LOTNO->Clear();
			for( i = 0; i < sDtkshins->Count; i++){
                sBuf2 = sDtkshins->Strings[i];
                sBuf  = sBuf2 + AnsiString::StringOfChar(' ', 20-sBuf2.Length());
                sBuf2 = sLots->Strings[i];
                sBuf  = sBuf + " " + sBuf2 + AnsiString::StringOfChar(' ',  6-sBuf2.Length());
			    clb_LOTNO->Items->Add( sBuf );
				clb_LOTNO->Checked[clb_LOTNO->Items->Count-1] = true;
            }
    		// 戻り値初期化
			ret_Btn1_OUT_CHECKClick = false;
        	return;
        }


        Query1->FindFirst();
		if(Query1->Eof == false) {

            // 社名(Customer)を表示します
			if( PgCtr_REPORT->ActivePage->Name == "TabSheet1" ||
	        	PgCtr_REPORT->ActivePage->Name == "TabSheet2" ||
	        	PgCtr_REPORT->ActivePage->Name == "TabSheet3" ||
	        	PgCtr_REPORT->ActivePage->Name == "TabSheet4" ||
	        	PgCtr_REPORT->ActivePage->Name == "TabSheet5" ){
	        	// 検査成績書
                // 検査成績書（月別）
                // 材料証明書
                // 材料証明書（月別）
                // 検査結果時系列管理表

				if( !VarIsNull(Query1->FieldValues["DTKSNAM"]) ){
					edt_CUSTOM->Text = AnsiString(Query1->FieldValues["DTKSNAM"]);
				}
	            else {
					edt_CUSTOM->Text = "";
	    		}
            }

			// 検査成績書タイトル部出力項目
			if( PgCtr_REPORT->ActivePage->Name == "TabSheet1" ||
	        	PgCtr_REPORT->ActivePage->Name == "TabSheet2" ||
	        	PgCtr_REPORT->ActivePage->Name == "TabSheet3" ||
	        	PgCtr_REPORT->ActivePage->Name == "TabSheet4" ){
	        	// 検査成績書
                // 検査成績書（月別）
                // 材料証明書
                // 材料証明書（月別）

				for( i = 0; i < iTITLE_Cnt; i++){
					if( iTITLE[i] == AnsiString(Query1->FieldValues["OUT_TITLE1"]).ToIntDef(-1)
					 || iTITLE[i] == AnsiString(Query1->FieldValues["OUT_TITLE2"]).ToIntDef(-1)
					 || iTITLE[i] == AnsiString(Query1->FieldValues["OUT_TITLE3"]).ToIntDef(-1)
					 || iTITLE[i] == AnsiString(Query1->FieldValues["OUT_TITLE4"]).ToIntDef(-1)
					 || iTITLE[i] == AnsiString(Query1->FieldValues["OUT_TITLE5"]).ToIntDef(-1)
					 || iTITLE[i] == AnsiString(Query1->FieldValues["OUT_TITLE6"]).ToIntDef(-1)
					 || iTITLE[i] == AnsiString(Query1->FieldValues["OUT_TITLE7"]).ToIntDef(-1)
					 || iTITLE[i] == AnsiString(Query1->FieldValues["OUT_TITLE8"]).ToIntDef(-1) ){
						if( iTITLE[i] == 4 &&
                        	(PgCtr_REPORT->ActivePage->Name == "TabSheet2" ||
	        				 PgCtr_REPORT->ActivePage->Name == "TabSheet4" ) ){
                			// 検査成績書（月別）
                			// 材料証明書（月別）の時は、「ロットNo」を選択することはありえない。
                        	clb_TITLE->Checked[i] = false;
						}
                        else {
                        	clb_TITLE->Checked[i] = true;
                    	}
					}
					else {
						clb_TITLE->Checked[i] = false;
					}
				}
			}

            // Xの出力
			if( PgCtr_REPORT->ActivePage->Name == "TabSheet1" ||
	        	PgCtr_REPORT->ActivePage->Name == "TabSheet2" ||
	        	PgCtr_REPORT->ActivePage->Name == "TabSheet3" ||
	        	PgCtr_REPORT->ActivePage->Name == "TabSheet4" ){
	        	// 検査成績書
                // 検査成績書（月別）
                // 材料証明書
                // 材料証明書（月別）

				if( AnsiString(Query1->FieldValues["X_OUT"]).ToIntDef(0) == 1 ){
	            	rdo_X_ON->Checked = true;
	            }
	            else {
	            	rdo_X_OFF->Checked = true;
	            }
			}

            //2003.05.16 E.Takase ↓
            //品名・品種の出力
            Edt6_CHK_HINMEI->Text = "";
            Edt6_CHK_HINSYU->Text = "";
			if( PgCtr_REPORT->ActivePage->Name == "TabSheet6") {
				if ( Rdo6_WHR_TYPE1->Checked == true ){
					//得意先品番・ロット指定の場合
					if( !VarIsNull(Query1->FieldValues["HINMEI"]) ){
						Edt6_CHK_HINMEI->Text = AnsiString(Query1->FieldValues["HINMEI"]);
					}
	            	else {
						Edt6_CHK_HINMEI->Text = "";
	    			}
					if( !VarIsNull(Query1->FieldValues["ZISNAM"]) ){
						Edt6_CHK_HINSYU->Text = AnsiString(Query1->FieldValues["ZISNAM"]);
					}
	            	else {
						Edt6_CHK_HINSYU->Text = "";
	    			}
                }
            }

            //2003.05.16 E.Takase ↑
		}
	}

    // ロット毎のタイトル部出力項目を更新します
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet1" ){
      	// 検査成績書
        Btn_CHK_TITLEREFClick(Btn1_CHK_TITLEREF);

	}
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet2" ){
      	// 検査成績書（月別）
        Btn_CHK_TITLEREFClick(Btn2_CHK_TITLEREF);

	}
    if( PgCtr_REPORT->ActivePage->Name == "TabSheet3" ){
        // 材料証明書
        Btn_CHK_TITLEREFClick(Btn3_CHK_TITLEREF);

    }
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet4" ){
      	// 材料証明書（月別）
        Btn_CHK_TITLEREFClick(Btn4_CHK_TITLEREF);

	}

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「指定ロットNo別のタイトル部内容更新↓」ボタンを押した時の処理
//
//  機能説明
//    指定されたタイトル部出力情報によりタイトル項目を設定します
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
void __fastcall TForm1::Btn_CHK_TITLEREFClick(TObject *Sender)
{

    int			i, k, m;
    int			iMax;
    bool		iJapanese;
    AnsiString	sBuf, sBuf2, sBuf3;
    AnsiString	sDTKSHIN, sLOTNO;
	AnsiString	sTabSheetNM;

    TButton*		btn	= dynamic_cast<TButton*>(Sender);
    TPanel*			pnl_LOT1[9];
    TEdit*			edt_LOT1[8];
    TPageControl*	pct_LOT;
    TRadioButton*	rdo_LOT[3];
    TPanel*			pnl_DUMMY;
    TEdit*			edt_DUMMY;
    TRadioButton*	rdo_DUMMY;
    TCheckListBox*	clb_TITLE;


    if( btn->Name == "Btn1_CHK_TITLEREF" ){
        //---------------------------------
    	// 検査成績書

        if( iNowTab != 1 ){
			MessageDlg("先に「出力内容の確認」ボタンを押して下さい。", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
    		// 戻り値初期化
			ret_Btn1_OUT_CHECKClick = false;
        	return;
        }

        sDTKSHIN = Edt1_WHR_DTKSHIN->Text;
        sLOTNO   = PgCtr1_tst01->Caption;

        if( Rdo1_WHR_FORMAT_JPN->Checked == true )	iJapanese = true;
        else                                        iJapanese = false;

        iMax		= 8;

	    clb_TITLE	= dynamic_cast<TCheckListBox*>(Clb1_CHK_TITLE);

    	pnl_LOT1[0] = dynamic_cast<TPanel*>(PgCtr1_tst1_Pnl1);
    	pnl_LOT1[1] = dynamic_cast<TPanel*>(PgCtr1_tst1_Pnl2);
    	pnl_LOT1[2] = dynamic_cast<TPanel*>(PgCtr1_tst1_Pnl3);
    	pnl_LOT1[3] = dynamic_cast<TPanel*>(PgCtr1_tst1_Pnl4);
    	pnl_LOT1[4] = dynamic_cast<TPanel*>(PgCtr1_tst1_Pnl5);
    	pnl_LOT1[5] = dynamic_cast<TPanel*>(PgCtr1_tst1_Pnl6);
    	pnl_LOT1[6] = dynamic_cast<TPanel*>(PgCtr1_tst1_Pnl7);
    	pnl_LOT1[7] = dynamic_cast<TPanel*>(PgCtr1_tst1_Pnl8);
    	pnl_LOT1[8] = dynamic_cast<TPanel*>(PgCtr1_tst1_Pnl9);

    	edt_LOT1[0] = dynamic_cast<TEdit*>(PgCtr1_tst1_Edt1);
    	edt_LOT1[1] = dynamic_cast<TEdit*>(PgCtr1_tst1_Edt2);
    	edt_LOT1[2] = dynamic_cast<TEdit*>(PgCtr1_tst1_Edt3);
    	edt_LOT1[3] = dynamic_cast<TEdit*>(PgCtr1_tst1_Edt4);
    	edt_LOT1[4] = dynamic_cast<TEdit*>(PgCtr1_tst1_Edt5);
    	edt_LOT1[5] = dynamic_cast<TEdit*>(PgCtr1_tst1_Edt6);
    	edt_LOT1[6] = dynamic_cast<TEdit*>(PgCtr1_tst1_Edt7);
    	edt_LOT1[7] = dynamic_cast<TEdit*>(PgCtr1_tst1_Edt8);

        pct_LOT     = dynamic_cast<TPageControl*>(PgCtr1_LOT);

        sTabSheetNM = "PgCtr1_tst";

    	rdo_LOT[0] = dynamic_cast<TRadioButton*>(PgCtr1_tst1_LOT4);
    	rdo_LOT[1] = dynamic_cast<TRadioButton*>(PgCtr1_tst1_LOT5);
    	rdo_LOT[2] = dynamic_cast<TRadioButton*>(PgCtr1_tst1_LOT6);

    } else if( btn->Name == "Btn2_CHK_TITLEREF" ){
        //---------------------------------
    	// 検査成績書（月別）

        if( iNowTab != 2 ){
			MessageDlg("先に「出力内容の確認」ボタンを押して下さい。", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
    		// 戻り値初期化
			ret_Btn1_OUT_CHECKClick = false;
        	return;
        }

		k = 0;
		for( i = 0; i < iTITLE_Cnt; i++){
			if( Clb2_CHK_TITLE->Checked[i] == true ){
				k++;
			}
		}
        if( k > 6 ){
			MessageDlg("タイトル部出力情報が６つ以上選択されています。\n選択し直して下さい。", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
    		// 戻り値初期化
			ret_Btn1_OUT_CHECKClick = false;
        	return;
        }

        if( Rdo2_WHR_TYPE1->Checked == true ){
        	sDTKSHIN = Edt2_WHR_DTKSHIN1->Text;
        } else {
        	sDTKSHIN = Edt2_WHR_DTKSHIN2->Text;
        }
        if( sLots->Count <= 0 )	return;
        sLOTNO   = sLots->Strings[0];

        if( Rdo2_WHR_FORMAT_JPN->Checked == true )	iJapanese = true;
        else                                        iJapanese = false;

        iMax		= 6;

	    clb_TITLE	= dynamic_cast<TCheckListBox*>(Clb2_CHK_TITLE);

    	pnl_LOT1[0] = dynamic_cast<TPanel*>(PgCtr2_tst1_Pnl1);
    	pnl_LOT1[1] = dynamic_cast<TPanel*>(PgCtr2_tst1_Pnl2);
    	pnl_LOT1[2] = dynamic_cast<TPanel*>(PgCtr2_tst1_Pnl3);
    	pnl_LOT1[3] = dynamic_cast<TPanel*>(PgCtr2_tst1_Pnl4);
    	pnl_LOT1[4] = dynamic_cast<TPanel*>(PgCtr2_tst1_Pnl5);
    	pnl_LOT1[5] = dynamic_cast<TPanel*>(PgCtr2_tst1_Pnl6);
    	pnl_LOT1[8] = dynamic_cast<TPanel*>(PgCtr2_tst1_Pnl9);

    	edt_LOT1[0] = dynamic_cast<TEdit*>(PgCtr2_tst1_Edt1);
    	edt_LOT1[1] = dynamic_cast<TEdit*>(PgCtr2_tst1_Edt2);
    	edt_LOT1[2] = dynamic_cast<TEdit*>(PgCtr2_tst1_Edt3);
    	edt_LOT1[3] = dynamic_cast<TEdit*>(PgCtr2_tst1_Edt4);
    	edt_LOT1[4] = dynamic_cast<TEdit*>(PgCtr2_tst1_Edt5);
    	edt_LOT1[5] = dynamic_cast<TEdit*>(PgCtr2_tst1_Edt6);


    	rdo_LOT[0] = dynamic_cast<TRadioButton*>(PgCtr2_tst1_LOT4);
    	rdo_LOT[1] = dynamic_cast<TRadioButton*>(PgCtr2_tst1_LOT5);
    	rdo_LOT[2] = dynamic_cast<TRadioButton*>(PgCtr2_tst1_LOT6);

    } else if( btn->Name == "Btn3_CHK_TITLEREF" ){
        //---------------------------------
    	// 材料証明書

        if( iNowTab != 3 ){
			MessageDlg("先に「出力内容の確認」ボタンを押して下さい。", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
    		// 戻り値初期化
			ret_Btn1_OUT_CHECKClick = false;
        	return;
        }

        sDTKSHIN    = Edt3_WHR_DTKSHIN->Text;
        sLOTNO      = PgCtr3_tst01->Caption;

        if( Rdo3_WHR_FORMAT_JPN->Checked == true )	iJapanese = true;
        else                                        iJapanese = false;

        iMax		= 8;

	    clb_TITLE	= dynamic_cast<TCheckListBox*>(Clb3_CHK_TITLE);

    	pnl_LOT1[0] = dynamic_cast<TPanel*>(PgCtr3_tst1_Pnl1);
    	pnl_LOT1[1] = dynamic_cast<TPanel*>(PgCtr3_tst1_Pnl2);
    	pnl_LOT1[2] = dynamic_cast<TPanel*>(PgCtr3_tst1_Pnl3);
    	pnl_LOT1[3] = dynamic_cast<TPanel*>(PgCtr3_tst1_Pnl4);
    	pnl_LOT1[4] = dynamic_cast<TPanel*>(PgCtr3_tst1_Pnl5);
    	pnl_LOT1[5] = dynamic_cast<TPanel*>(PgCtr3_tst1_Pnl6);
    	pnl_LOT1[6] = dynamic_cast<TPanel*>(PgCtr3_tst1_Pnl7);
    	pnl_LOT1[7] = dynamic_cast<TPanel*>(PgCtr3_tst1_Pnl8);
    	pnl_LOT1[8] = dynamic_cast<TPanel*>(PgCtr3_tst1_Pnl9);

    	edt_LOT1[0] = dynamic_cast<TEdit*>(PgCtr3_tst1_Edt1);
    	edt_LOT1[1] = dynamic_cast<TEdit*>(PgCtr3_tst1_Edt2);
    	edt_LOT1[2] = dynamic_cast<TEdit*>(PgCtr3_tst1_Edt3);
    	edt_LOT1[3] = dynamic_cast<TEdit*>(PgCtr3_tst1_Edt4);
    	edt_LOT1[4] = dynamic_cast<TEdit*>(PgCtr3_tst1_Edt5);
    	edt_LOT1[5] = dynamic_cast<TEdit*>(PgCtr3_tst1_Edt6);
    	edt_LOT1[6] = dynamic_cast<TEdit*>(PgCtr3_tst1_Edt7);
    	edt_LOT1[7] = dynamic_cast<TEdit*>(PgCtr3_tst1_Edt8);

        pct_LOT     = dynamic_cast<TPageControl*>(PgCtr3_LOT);

        sTabSheetNM = "PgCtr3_tst";

    	rdo_LOT[0] = dynamic_cast<TRadioButton*>(PgCtr3_tst1_LOT4);
    	rdo_LOT[1] = dynamic_cast<TRadioButton*>(PgCtr3_tst1_LOT5);
    	rdo_LOT[2] = dynamic_cast<TRadioButton*>(PgCtr3_tst1_LOT6);

    } else if( btn->Name == "Btn4_CHK_TITLEREF" ){
        //---------------------------------
    	// 材料証明書（月別）

        if( iNowTab != 4 ){
			MessageDlg("先に「出力内容の確認」ボタンを押して下さい。", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
    		// 戻り値初期化
			ret_Btn1_OUT_CHECKClick = false;
        	return;
        }

		k = 0;
		for( i = 0; i < iTITLE_Cnt; i++){
			if( Clb4_CHK_TITLE->Checked[i] == true ){
				k++;
			}
		}
        if( k > 6 ){
			MessageDlg("タイトル部出力情報が６つ以上選択されています。\n選択し直して下さい。", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
    		// 戻り値初期化
			ret_Btn1_OUT_CHECKClick = false;
        	return;
        }

        if( Rdo4_WHR_TYPE1->Checked == true ){
        	sDTKSHIN = Edt4_WHR_DTKSHIN1->Text;
        } else {
        	sDTKSHIN = Edt4_WHR_DTKSHIN2->Text;
        }
        if( sLots->Count <= 0 )	return;
        sLOTNO   = sLots->Strings[0];

        if( Rdo4_WHR_FORMAT_JPN->Checked == true )	iJapanese = true;
        else                                        iJapanese = false;

        iMax		= 6;

	    clb_TITLE	= dynamic_cast<TCheckListBox*>(Clb4_CHK_TITLE);

    	pnl_LOT1[0] = dynamic_cast<TPanel*>(PgCtr4_tst1_Pnl1);
    	pnl_LOT1[1] = dynamic_cast<TPanel*>(PgCtr4_tst1_Pnl2);
    	pnl_LOT1[2] = dynamic_cast<TPanel*>(PgCtr4_tst1_Pnl3);
    	pnl_LOT1[3] = dynamic_cast<TPanel*>(PgCtr4_tst1_Pnl4);
    	pnl_LOT1[4] = dynamic_cast<TPanel*>(PgCtr4_tst1_Pnl5);
    	pnl_LOT1[5] = dynamic_cast<TPanel*>(PgCtr4_tst1_Pnl6);
    	pnl_LOT1[8] = dynamic_cast<TPanel*>(PgCtr4_tst1_Pnl9);

    	edt_LOT1[0] = dynamic_cast<TEdit*>(PgCtr4_tst1_Edt1);
    	edt_LOT1[1] = dynamic_cast<TEdit*>(PgCtr4_tst1_Edt2);
    	edt_LOT1[2] = dynamic_cast<TEdit*>(PgCtr4_tst1_Edt3);
    	edt_LOT1[3] = dynamic_cast<TEdit*>(PgCtr4_tst1_Edt4);
    	edt_LOT1[4] = dynamic_cast<TEdit*>(PgCtr4_tst1_Edt5);
    	edt_LOT1[5] = dynamic_cast<TEdit*>(PgCtr4_tst1_Edt6);


    	rdo_LOT[0] = dynamic_cast<TRadioButton*>(PgCtr4_tst1_LOT4);
    	rdo_LOT[1] = dynamic_cast<TRadioButton*>(PgCtr4_tst1_LOT5);
    	rdo_LOT[2] = dynamic_cast<TRadioButton*>(PgCtr4_tst1_LOT6);

    } else {

   		// 戻り値初期化
		ret_Btn1_OUT_CHECKClick = false;
    	return;
    }

    // ロットNO用のパネルを隠します
    pnl_LOT1[8]->Visible = false;

    // タイトル項目番号をリセットします
    for( i = 0; i < iMax; i++){
        edt_LOT1[i]->Tag     = 0;
        edt_LOT1[i]->Text    = "";
        edt_LOT1[i]->Visible = true;
    }

    k = 0;
    for( i = 0; i < iTITLE_Cnt; i++){
        if( clb_TITLE->Checked[i] == true ){
            sBuf = sTITLE_JPN->Strings[i];

            pnl_LOT1[k]->Caption	= sBuf;
            edt_LOT1[k]->Tag		= iTITLE[i];
            if( iTITLE[i] == 4 ){
                // ロットNOの場合
                edt_LOT1[k]->Visible	= false;
                pnl_LOT1[8]->Top		= edt_LOT1[k]->Top;
                pnl_LOT1[8]->Left		= edt_LOT1[k]->Left;
                pnl_LOT1[8]->Height		= edt_LOT1[k]->Height;
                pnl_LOT1[8]->Width		= edt_LOT1[k]->Width;
                pnl_LOT1[8]->Visible	= true;
            }
            else {
                edt_LOT1[k]->Visible	= true;
                edt_LOT1[k]->Text		= GetTitleData(sDTKSHIN, sLOTNO, iTITLE[i], iJapanese);
            }

            k++;

            if( k >= iMax ) break;
        }
    }

    // タイトル項目が８個又は６個に満たない時は、名称をクリアーします
    for( i = k; i < iMax; i++){
        pnl_LOT1[i]->Caption = "";
    }

    // 検査成績書（月別）、材料証明書（月別）はここで処理終わり。
    if( btn->Name == "Btn2_CHK_TITLEREF" ||
        btn->Name == "Btn4_CHK_TITLEREF" ){
    	return;
    }

    // 前回作成したTabSheetを削除します
    for( i = 2; i <= pct_LOT->Tag; i++){
        if( btn->Name == "Btn1_CHK_TITLEREF" ){
    		delete PgCtr1_tst[i];
        } else {
    		delete PgCtr3_tst[i];
        }

    }

    // 2個目以降のロットTabSheetを作成します
    for( i = 2; i <= sLots->Count; i++){

		sBuf = IntToStr(i);

        // タブシートの作成
        if( btn->Name == "Btn1_CHK_TITLEREF" ){
			PgCtr1_tst[i]				= new TTabSheet(pct_LOT);
    		PgCtr1_tst[i]->Name			= sTabSheetNM + AnsiString::StringOfChar('0', 2-sBuf.Length()) + sBuf;
        	PgCtr1_tst[i]->Parent		= pct_LOT;
			PgCtr1_tst[i]->PageControl	= pct_LOT;
        	PgCtr1_tst[i]->Caption		= sLots->Strings[i-1];
			PgCtr1_tst[i]->TabVisible	= true;
        } else {
			PgCtr3_tst[i]				= new TTabSheet(pct_LOT);
    		PgCtr3_tst[i]->Name			= sTabSheetNM + AnsiString::StringOfChar('0', 2-sBuf.Length()) + sBuf;
        	PgCtr3_tst[i]->Parent		= pct_LOT;
			PgCtr3_tst[i]->PageControl	= pct_LOT;
        	PgCtr3_tst[i]->Caption		= sLots->Strings[i-1];
			PgCtr3_tst[i]->TabVisible	= true;
        }


	    for( k = 0; k <= 8; k++){
			sBuf2 = IntToStr(k);

			// ラベルの作成
        	if( btn->Name == "Btn1_CHK_TITLEREF" ){
        		PgCtr1_tst_Pnl[i][k]			= new TPanel(PgCtr1_tst[i]);
            	PgCtr1_tst_Pnl[i][k]->Name		= sTabSheetNM	+ AnsiString::StringOfChar('0', 2-sBuf.Length()) + sBuf +
            									  "_Pnl"		+ AnsiString::StringOfChar('0', 2-sBuf2.Length()) + sBuf2;
            	PgCtr1_tst_Pnl[i][k]->Parent	= PgCtr1_tst[i];
	            pnl_DUMMY = dynamic_cast<TPanel*>(PgCtr1_tst_Pnl[i][k]);
            } else {
        		PgCtr3_tst_Pnl[i][k]			= new TPanel(PgCtr3_tst[i]);
            	PgCtr3_tst_Pnl[i][k]->Name		= sTabSheetNM	+ AnsiString::StringOfChar('0', 2-sBuf.Length()) + sBuf +
            									  "_Pnl"		+ AnsiString::StringOfChar('0', 2-sBuf2.Length()) + sBuf2;
            	PgCtr3_tst_Pnl[i][k]->Parent	= PgCtr3_tst[i];
	            pnl_DUMMY = dynamic_cast<TPanel*>(PgCtr3_tst_Pnl[i][k]);
            }
           	pnl_DUMMY->Caption		= pnl_LOT1[k]->Caption;
           	pnl_DUMMY->Top			= pnl_LOT1[k]->Top;
           	pnl_DUMMY->Left			= pnl_LOT1[k]->Left;
           	pnl_DUMMY->Height		= pnl_LOT1[k]->Height;
           	pnl_DUMMY->Width		= pnl_LOT1[k]->Width;
           	pnl_DUMMY->Enabled		= pnl_LOT1[k]->Enabled;
           	pnl_DUMMY->Font			= pnl_LOT1[k]->Font;
           	pnl_DUMMY->Color		= pnl_LOT1[k]->Color;
           	pnl_DUMMY->BevelInner	= pnl_LOT1[k]->BevelInner;
           	pnl_DUMMY->BevelOuter	= pnl_LOT1[k]->BevelOuter;
           	pnl_DUMMY->Visible		= pnl_LOT1[k]->Visible;

			// テキストボックスの作成
            if( k < 8 ){
        		if( btn->Name == "Btn1_CHK_TITLEREF" ){
        			PgCtr1_tst_Edt[i][k]			= new TEdit(PgCtr1_tst[i]);
            		PgCtr1_tst_Edt[i][k]->Name		= sTabSheetNM	+ AnsiString::StringOfChar('0', 2-sBuf.Length()) + sBuf +
            										  "_Edt"		+ AnsiString::StringOfChar('0', 2-sBuf2.Length()) + sBuf2;
            		PgCtr1_tst_Edt[i][k]->Parent	= PgCtr1_tst[i];
            		PgCtr1_tst_Edt[i][k]->OnEnter	= FormEnter;
            		PgCtr1_tst_Edt[i][k]->OnKeyDown	= FormKeyDown;
            		PgCtr1_tst_Edt[i][k]->OnKeyPress= FormKeyPress;
            		PgCtr1_tst_Edt[i][k]->OnChange	= Edt_ALLChange;
                    PgCtr1_tst_Edt[i][k]->OnExit	= Edt_iTITLE5_Exit;
                    edt_DUMMY = dynamic_cast<TEdit*>(PgCtr1_tst_Edt[i][k]);
                	sLOTNO = PgCtr1_tst[i]->Caption;
            	} else {
        			PgCtr3_tst_Edt[i][k]			= new TEdit(PgCtr3_tst[i]);
            		PgCtr3_tst_Edt[i][k]->Name		= sTabSheetNM	+ AnsiString::StringOfChar('0', 2-sBuf.Length()) + sBuf +
            										  "_Edt"		+ AnsiString::StringOfChar('0', 2-sBuf2.Length()) + sBuf2;
            		PgCtr3_tst_Edt[i][k]->Parent	= PgCtr3_tst[i];
            		PgCtr3_tst_Edt[i][k]->OnEnter	= FormEnter;
            		PgCtr3_tst_Edt[i][k]->OnKeyDown	= FormKeyDown;
            		PgCtr3_tst_Edt[i][k]->OnKeyPress= FormKeyPress;
            		PgCtr3_tst_Edt[i][k]->OnChange	= Edt_ALLChange;
                    PgCtr3_tst_Edt[i][k]->OnExit	= Edt_iTITLE5_Exit;
                    edt_DUMMY = dynamic_cast<TEdit*>(PgCtr3_tst_Edt[i][k]);
                	sLOTNO = PgCtr3_tst[i]->Caption;
                }
                edt_DUMMY->Top		= edt_LOT1[k]->Top;
                edt_DUMMY->Left		= edt_LOT1[k]->Left;
                edt_DUMMY->Height	= edt_LOT1[k]->Height;
                edt_DUMMY->Width	= edt_LOT1[k]->Width;
                edt_DUMMY->Enabled	= edt_LOT1[k]->Enabled;
                edt_DUMMY->Font		= edt_LOT1[k]->Font;
                edt_DUMMY->Visible	= edt_LOT1[k]->Visible;
           	    edt_DUMMY->Tag		= edt_LOT1[k]->Tag;
                edt_DUMMY->Text		= GetTitleData(sDTKSHIN, sLOTNO, edt_LOT1[k]->Tag, iJapanese);
            }
            else {

                // ロットNo選択用オプションボックスの作成
				for( m = 0; m < 3; m++){
       	        	if( btn->Name == "Btn1_CHK_TITLEREF" ){
						PgCtr1_tst_LOT[i][m]			= new TRadioButton(PgCtr1_tst_Pnl[i][k]);
						PgCtr1_tst_LOT[i][m]->Name		= sTabSheetNM	+ AnsiString::StringOfChar('0', 2-sBuf.Length())
														  + sBuf + "_LOT" + IntToStr(m+4);
						PgCtr1_tst_LOT[i][m]->Parent	= PgCtr1_tst_Pnl[i][k];
						rdo_DUMMY = dynamic_cast<TRadioButton*>(PgCtr1_tst_LOT[i][m]);
                	} else {
						PgCtr3_tst_LOT[i][m]			= new TRadioButton(PgCtr3_tst_Pnl[i][k]);
						PgCtr3_tst_LOT[i][m]->Name		= sTabSheetNM	+ AnsiString::StringOfChar('0', 2-sBuf.Length())
														  + sBuf + "_LOT" + IntToStr(m+4);
						PgCtr3_tst_LOT[i][m]->Parent	= PgCtr3_tst_Pnl[i][k];
						rdo_DUMMY = dynamic_cast<TRadioButton*>(PgCtr3_tst_LOT[i][m]);
                    }
					rdo_DUMMY->Caption	= rdo_LOT[m]->Caption;
               		rdo_DUMMY->Top		= rdo_LOT[m]->Top;
               		rdo_DUMMY->Left		= rdo_LOT[m]->Left;
               		rdo_DUMMY->Height	= rdo_LOT[m]->Height;
               		rdo_DUMMY->Width	= rdo_LOT[m]->Width;
               		rdo_DUMMY->Enabled	= rdo_LOT[m]->Enabled;
               		rdo_DUMMY->Font		= rdo_LOT[m]->Font;
               		rdo_DUMMY->Color	= rdo_LOT[m]->Color;
               		rdo_DUMMY->Checked	= rdo_LOT[m]->Checked;
				}

            }

        }

    }

    // 動的作成したTabSheetの個数を格納します
    pct_LOT->Tag = sLots->Count;

	return;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「表示中の内容を他のロットに反映↓」ボタンを押した時の処理
//
//  機能説明
//    表示されたロット毎のタイトル部出力情報に対して
//    表示されているロットのタイトル部出力情報を
//    他のロットのタイトル部出力情報にコピーします
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
void __fastcall TForm1::Btn1_CHK_TITLECOPYClick(TObject *Sender)
{

    int			i, k;
	int			iPageNo;
    int			iNotCopyNo;
    AnsiString  sBuf[8];
    bool		iBuf[3];

    TButton* 		btn = dynamic_cast<TButton*>(Sender);
    iNotCopyNo = -1;

    if( btn->Name == "Btn1_CHK_TITLECOPY" ){
        //---------------------------------
    	// 検査成績書

        if( iNowTab != 1 ){
			MessageDlg("先に「出力内容の確認」ボタンを押して下さい。", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
        	return;
        }

        // 複写元の値を格納します
        iPageNo = PgCtr1_LOT->ActivePage->PageIndex;
        if( iPageNo == 0 ){
        	sBuf[0] = PgCtr1_tst1_Edt1->Text;
        	sBuf[1] = PgCtr1_tst1_Edt2->Text;
        	sBuf[2] = PgCtr1_tst1_Edt3->Text;
        	sBuf[3] = PgCtr1_tst1_Edt4->Text;
        	sBuf[4] = PgCtr1_tst1_Edt5->Text;
        	sBuf[5] = PgCtr1_tst1_Edt6->Text;
        	sBuf[6] = PgCtr1_tst1_Edt7->Text;
        	sBuf[7] = PgCtr1_tst1_Edt8->Text;
            iBuf[0] = PgCtr1_tst1_LOT4->Checked;
            iBuf[1] = PgCtr1_tst1_LOT5->Checked;
            iBuf[2] = PgCtr1_tst1_LOT6->Checked;
            if( PgCtr1_tst1_Edt1->Tag == 6 )	iNotCopyNo = 0;
            if( PgCtr1_tst1_Edt2->Tag == 6 )	iNotCopyNo = 1;
            if( PgCtr1_tst1_Edt3->Tag == 6 )	iNotCopyNo = 2;
            if( PgCtr1_tst1_Edt4->Tag == 6 )	iNotCopyNo = 3;
            if( PgCtr1_tst1_Edt5->Tag == 6 )	iNotCopyNo = 4;
            if( PgCtr1_tst1_Edt6->Tag == 6 )	iNotCopyNo = 5;
            if( PgCtr1_tst1_Edt7->Tag == 6 )	iNotCopyNo = 6;
            if( PgCtr1_tst1_Edt8->Tag == 6 )	iNotCopyNo = 7;
        } else {
            for( i = 0; i < 8; i++ ){
        		sBuf[i] = PgCtr1_tst_Edt[iPageNo+1][i]->Text;
            	if( PgCtr1_tst_Edt[iPageNo+1][i]->Tag == 6 )	iNotCopyNo = i;
            }
            for( i = 0; i < 3; i++ ){
        		iBuf[i] = PgCtr1_tst_LOT[iPageNo+1][i]->Checked;
            }
        }

        // 複写先へコピーを開始します
        for( k = 0; k < PgCtr1_LOT->PageCount; k++ ){
            if( k == iPageNo )	continue;
        	if( k == 0 ){
            	if( iNotCopyNo != 0 )	PgCtr1_tst1_Edt1->Text = sBuf[0];
        		if( iNotCopyNo != 1 )	PgCtr1_tst1_Edt2->Text = sBuf[1];
        		if( iNotCopyNo != 2 )	PgCtr1_tst1_Edt3->Text = sBuf[2];
        		if( iNotCopyNo != 3 )	PgCtr1_tst1_Edt4->Text = sBuf[3];
        		if( iNotCopyNo != 4 )	PgCtr1_tst1_Edt5->Text = sBuf[4];
        		if( iNotCopyNo != 5 )	PgCtr1_tst1_Edt6->Text = sBuf[5];
        		if( iNotCopyNo != 6 )	PgCtr1_tst1_Edt7->Text = sBuf[6];
        		if( iNotCopyNo != 7 )	PgCtr1_tst1_Edt8->Text = sBuf[7];
        		PgCtr1_tst1_LOT4->Checked = iBuf[0];
        		PgCtr1_tst1_LOT5->Checked = iBuf[1];
        		PgCtr1_tst1_LOT6->Checked = iBuf[2];
        	} else {
            	for( i = 0; i < 8; i++ ){
        			if( iNotCopyNo != i )	PgCtr1_tst_Edt[k+1][i]->Text = sBuf[i];
            	}
            	for( i = 0; i < 3; i++ ){
        			PgCtr1_tst_LOT[k+1][i]->Checked	= iBuf[i];
            	}
        	}
        }

    }

    if( btn->Name == "Btn3_CHK_TITLECOPY" ){
        //---------------------------------
    	// 材料証明書

        if( iNowTab != 3 ){
			MessageDlg("先に「出力内容の確認」ボタンを押して下さい。", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
        	return;
        }

        // 複写元の値を格納します
        iPageNo = PgCtr3_LOT->ActivePage->PageIndex;
        if( iPageNo == 0 ){
        	sBuf[0] = PgCtr3_tst1_Edt1->Text;
        	sBuf[1] = PgCtr3_tst1_Edt2->Text;
        	sBuf[2] = PgCtr3_tst1_Edt3->Text;
        	sBuf[3] = PgCtr3_tst1_Edt4->Text;
        	sBuf[4] = PgCtr3_tst1_Edt5->Text;
        	sBuf[5] = PgCtr3_tst1_Edt6->Text;
        	sBuf[6] = PgCtr3_tst1_Edt7->Text;
        	sBuf[7] = PgCtr3_tst1_Edt8->Text;
            iBuf[0] = PgCtr3_tst1_LOT4->Checked;
            iBuf[1] = PgCtr3_tst1_LOT5->Checked;
            iBuf[2] = PgCtr3_tst1_LOT6->Checked;
            if( PgCtr3_tst1_Edt1->Tag == 6 )	iNotCopyNo = 0;
            if( PgCtr3_tst1_Edt2->Tag == 6 )	iNotCopyNo = 1;
            if( PgCtr3_tst1_Edt3->Tag == 6 )	iNotCopyNo = 2;
            if( PgCtr3_tst1_Edt4->Tag == 6 )	iNotCopyNo = 3;
            if( PgCtr3_tst1_Edt5->Tag == 6 )	iNotCopyNo = 4;
            if( PgCtr3_tst1_Edt6->Tag == 6 )	iNotCopyNo = 5;
            if( PgCtr3_tst1_Edt7->Tag == 6 )	iNotCopyNo = 6;
            if( PgCtr3_tst1_Edt8->Tag == 6 )	iNotCopyNo = 7;
        } else {
            for( i = 0; i < 8; i++ ){
                sBuf[i] = PgCtr3_tst_Edt[iPageNo+1][i]->Text;
        		if( PgCtr3_tst_Edt[iPageNo+1][i]->Tag == 6 )	iNotCopyNo = i;
            }
            for( i = 0; i < 3; i++ ){
        		iBuf[i] = PgCtr3_tst_LOT[iPageNo+1][i]->Checked;
            }
        }

        // 複写先へコピーを開始します
        for( k = 0; k < PgCtr3_LOT->PageCount; k++ ){
            if( k == iPageNo )	continue;
        	if( k == 0 ){
        		if( iNotCopyNo != 0 )	PgCtr3_tst1_Edt1->Text = sBuf[0];
        		if( iNotCopyNo != 1 )	PgCtr3_tst1_Edt2->Text = sBuf[1];
        		if( iNotCopyNo != 2 )	PgCtr3_tst1_Edt3->Text = sBuf[2];
        		if( iNotCopyNo != 3 )	PgCtr3_tst1_Edt4->Text = sBuf[3];
        		if( iNotCopyNo != 4 )	PgCtr3_tst1_Edt5->Text = sBuf[4];
        		if( iNotCopyNo != 5 )	PgCtr3_tst1_Edt6->Text = sBuf[5];
        		if( iNotCopyNo != 6 )	PgCtr3_tst1_Edt7->Text = sBuf[6];
        		if( iNotCopyNo != 7 )	PgCtr3_tst1_Edt8->Text = sBuf[7];
        		PgCtr3_tst1_LOT4->Checked	= iBuf[0];
        		PgCtr3_tst1_LOT5->Checked	= iBuf[1];
        		PgCtr3_tst1_LOT6->Checked	= iBuf[2];
        	} else {
            	for( i = 0; i < 8; i++ ){
        			if( iNotCopyNo != i )	PgCtr3_tst_Edt[k+1][i]->Text = sBuf[i];
            	}
            	for( i = 0; i < 3; i++ ){
        			PgCtr3_tst_LOT[k+1][i]->Checked	= iBuf[i];
            	}
        	}
        }

    }

}

//---------------------------------------------------------------------------
//
//  概要
//    OnExitイベント	：入力フォーカスがコントロールから別のコントロールへ移ったときに発生
//
//  機能説明
//    納入数のために、千単位で,を自動設定します
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
void __fastcall TForm1::Edt_iTITLE5_Exit(TObject *Sender)
{
    AnsiString	sBuf;
    int			i;
    TEdit* 		edt = dynamic_cast<TEdit*>(Sender);

    if( edt->Tag != 5 )	return;

    sBuf = "";

    for( i = 1; i <= edt->Text.Length() ; i++){
		if( strcspn( edt->Text.SubString(i,1).c_str(), "-0123456789" ) != 0 ) {
        } else{
            sBuf = sBuf + edt->Text.SubString(i,1);
        }
    }

    edt->Text = FormatFloat("#,##0", (double)sBuf.ToIntDef(0));

}

//---------------------------------------------------------------------------
//
//  概要
//    OnKeyDownイベント	：ユーザーが任意のキーを押すと発生します
//
//  機能説明
//    ファンクションキーによりボタンを選択します
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
     switch(Key) {
         case VK_F1:  BtnF01Click(BtnF01);		break;
         case VK_F2:  BtnF02Click(BtnF02);		break;
         case VK_F3:  BtnF03Click(BtnF03);		break;
         case VK_F5:  BtnF05Click(BtnF05);		break;
         case VK_F7:  BtnF07Click(BtnF07);		break;
         case VK_F9:  BtnF09Click(BtnF09);		break;
         case VK_F10: BtnF10Click(BtnF10);		break;
         case VK_F12: BtnF12Click(BtnF12);		break;
         case VK_RETURN:
                    if( Memo1_CHK_REMARK->Focused() ||
                    	Memo2_CHK_REMARK->Focused() ||
                    	Memo3_CHK_REMARK->Focused() ||
                    	Memo4_CHK_REMARK->Focused() ){
                    	break;
                    }
               		keybd_event(VK_TAB,0,0,0);
                	keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
     }

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「印刷条件の指定」ラジオボタンを押した時の処理
//
//  機能説明
//    選択されたラジオボタンを判断し、
//    対象となるラベル、テキストボックスの有効／無効を設定します
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
void __fastcall TForm1::Rdo2_WHR_TYPE1Click(TObject *Sender)
{

    TRadioButton* rdo = dynamic_cast<TRadioButton*>(Sender);

    // 検査成績書（月別）
    if( rdo->Name == "Rdo2_WHR_TYPE1" && rdo->Checked == true ){
        // ON
        Pnl2_WHR_DTKSHIN1->Color	= (TColor)0x00FEE7BA;
        Pnl2_WHR_LOTNO1->Color		= (TColor)0x00FEE7BA;
        Edt2_WHR_DTKSHIN1->Color	= (TColor)clWindow;
        Edt2_WHR_LOTNO1->Color		= (TColor)clWindow;
        Edt2_WHR_DTKSHIN1->Enabled	= true;
        Edt2_WHR_LOTNO1->Enabled	= true;
        // OFF
        Pnl2_WHR_DTKSHIN2->Color	= (TColor)clSilver;
        Pnl2_WHR_SYUKADATE->Color	= (TColor)clSilver;
        Edt2_WHR_DTKSHIN2->Color	= (TColor)clSilver;
        Edt2_WHR_SYUKADATE1->Color	= (TColor)clSilver;
        Edt2_WHR_SYUKADATE2->Color	= (TColor)clSilver;
        Edt2_WHR_DTKSHIN2->Enabled	= false;
        Edt2_WHR_SYUKADATE1->Enabled= false;
        Edt2_WHR_SYUKADATE2->Enabled= false;
    }
    if( rdo->Name == "Rdo2_WHR_TYPE2" && rdo->Checked == true ){
        // OFF
        Pnl2_WHR_DTKSHIN1->Color	= (TColor)clSilver;
        Pnl2_WHR_LOTNO1->Color		= (TColor)clSilver;
        Edt2_WHR_DTKSHIN1->Color	= (TColor)clSilver;
        Edt2_WHR_LOTNO1->Color		= (TColor)clSilver;
        Edt2_WHR_DTKSHIN1->Enabled	= false;
        Edt2_WHR_LOTNO1->Enabled	= false;
        // ON
        Pnl2_WHR_DTKSHIN2->Color	= (TColor)0x00FEE7BA;
        Pnl2_WHR_SYUKADATE->Color	= (TColor)0x00FEE7BA;
        Edt2_WHR_DTKSHIN2->Color	= (TColor)clWindow;
        Edt2_WHR_SYUKADATE1->Color	= (TColor)clWindow;
        Edt2_WHR_SYUKADATE2->Color	= (TColor)clWindow;
        Edt2_WHR_DTKSHIN2->Enabled	= true;
        Edt2_WHR_SYUKADATE1->Enabled= true;
        Edt2_WHR_SYUKADATE2->Enabled= true;
    }

    // 検査成績書（月別）
    if( rdo->Name == "Rdo4_WHR_TYPE1" && rdo->Checked == true ){
        // ON
        Pnl4_WHR_DTKSHIN1->Color	= (TColor)0x00FEE7BA;
        Pnl4_WHR_LOTNO1->Color		= (TColor)0x00FEE7BA;
        Edt4_WHR_DTKSHIN1->Color	= (TColor)clWindow;
        Edt4_WHR_LOTNO1->Color		= (TColor)clWindow;
        Edt4_WHR_DTKSHIN1->Enabled	= true;
        Edt4_WHR_LOTNO1->Enabled	= true;
        // OFF
        Pnl4_WHR_DTKSHIN2->Color	= (TColor)clSilver;
        Pnl4_WHR_SYUKADATE->Color	= (TColor)clSilver;
        Edt4_WHR_DTKSHIN2->Color	= (TColor)clSilver;
        Edt4_WHR_SYUKADATE1->Color	= (TColor)clSilver;
        Edt4_WHR_SYUKADATE2->Color	= (TColor)clSilver;
        Edt4_WHR_DTKSHIN2->Enabled	= false;
        Edt4_WHR_SYUKADATE1->Enabled= false;
        Edt4_WHR_SYUKADATE2->Enabled= false;
    }
    if( rdo->Name == "Rdo4_WHR_TYPE2" && rdo->Checked == true ){
        // OFF
        Pnl4_WHR_DTKSHIN1->Color	= (TColor)clSilver;
        Pnl4_WHR_LOTNO1->Color		= (TColor)clSilver;
        Edt4_WHR_DTKSHIN1->Color	= (TColor)clSilver;
        Edt4_WHR_LOTNO1->Color		= (TColor)clSilver;
        Edt4_WHR_DTKSHIN1->Enabled	= false;
        Edt4_WHR_LOTNO1->Enabled	= false;
        // ON
        Pnl4_WHR_DTKSHIN2->Color	= (TColor)0x00FEE7BA;
        Pnl4_WHR_SYUKADATE->Color	= (TColor)0x00FEE7BA;
        Edt4_WHR_DTKSHIN2->Color	= (TColor)clWindow;
        Edt4_WHR_SYUKADATE1->Color	= (TColor)clWindow;
        Edt4_WHR_SYUKADATE2->Color	= (TColor)clWindow;
        Edt4_WHR_DTKSHIN2->Enabled	= true;
        Edt4_WHR_SYUKADATE1->Enabled= true;
        Edt4_WHR_SYUKADATE2->Enabled= true;
    }


    // 時系列管理表
    if( rdo->Name == "Rdo5_WHR_TYPE1" && rdo->Checked == true ){
        // ON
        Pnl5_WHR_LOTNO->Color		= (TColor)0x00FEE7BA;
        Edt5_WHR_LOTNO->Color		= (TColor)clWindow;
        Edt5_WHR_LOTNO->Enabled	= true;
        // OFF
        Pnl5_WHR_SYUKADATE->Color	= (TColor)clSilver;
        Edt5_WHR_SYUKADATE1->Color	= (TColor)clSilver;
        Edt5_WHR_SYUKADATE2->Color	= (TColor)clSilver;
        Edt5_WHR_SYUKADATE1->Enabled= false;
        Edt5_WHR_SYUKADATE2->Enabled= false;
    }
    if( rdo->Name == "Rdo5_WHR_TYPE2" && rdo->Checked == true ){
        // OFF
        Pnl5_WHR_LOTNO->Color		= (TColor)clSilver;
        Edt5_WHR_LOTNO->Color		= (TColor)clSilver;
        Edt5_WHR_LOTNO->Enabled	= false;
        // ON
        Pnl5_WHR_SYUKADATE->Color	= (TColor)0x00FEE7BA;
        Edt5_WHR_SYUKADATE1->Color	= (TColor)clWindow;
        Edt5_WHR_SYUKADATE2->Color	= (TColor)clWindow;
        Edt5_WHR_SYUKADATE1->Enabled= true;
        Edt5_WHR_SYUKADATE2->Enabled= true;
    }


    // 検査経歴票
    if( rdo->Name == "Rdo6_WHR_TYPE1" && rdo->Checked == true ){
        // ON
        Pnl6_WHR_DTKSHIN1->Color	= (TColor)0x00FEE7BA;
        Pnl6_WHR_LOTNO1->Color		= (TColor)0x00FEE7BA;
        Edt6_WHR_DTKSHIN1->Color	= (TColor)clWindow;
        Edt6_WHR_LOTNO1->Color		= (TColor)clWindow;
        Edt6_WHR_DTKSHIN1->Enabled	= true;
        Edt6_WHR_LOTNO1->Enabled	= true;
        // OFF
        Pnl6_WHR_KENSADATE->Color	= (TColor)clSilver;
        Edt6_WHR_KENSADATE1->Color	= (TColor)clSilver;
        Edt6_WHR_KENSADATE2->Color	= (TColor)clSilver;
        Edt6_WHR_KENSADATE1->Enabled= false;
        Edt6_WHR_KENSADATE2->Enabled= false;
        // ON
        Pnl6_CHK_HINMEI->Color		= (TColor)0x00FEE7BA;
        Pnl6_CHK_HINSYU->Color		= (TColor)0x00FEE7BA;
        Pnl6_CHK_KOUMOKU->Color		= (TColor)0x00FEE7BA;
        Edt6_CHK_HINMEI->Color		= (TColor)clWindow;
        Edt6_CHK_HINSYU->Color		= (TColor)clWindow;
        Clb6_CHK_KOUMOKU->Color		= (TColor)clWindow;
        Edt6_CHK_HINMEI->Enabled	= true;
        Edt6_CHK_HINSYU->Enabled	= true;
        Clb6_CHK_KOUMOKU->Enabled	= true;

		Pnl6_LOTNO_OUT->Caption		= "出力対象のロット";
    }
    if( rdo->Name == "Rdo6_WHR_TYPE2" && rdo->Checked == true ){
        // OFF
        Pnl6_WHR_DTKSHIN1->Color	= (TColor)clSilver;
        Pnl6_WHR_LOTNO1->Color		= (TColor)clSilver;
        Edt6_WHR_DTKSHIN1->Color	= (TColor)clSilver;
        Edt6_WHR_LOTNO1->Color		= (TColor)clSilver;
        Edt6_WHR_DTKSHIN1->Enabled	= false;
        Edt6_WHR_LOTNO1->Enabled	= false;
        // ON
        Pnl6_WHR_KENSADATE->Color	= (TColor)0x00FEE7BA;
        Edt6_WHR_KENSADATE1->Color	= (TColor)clWindow;
        Edt6_WHR_KENSADATE2->Color	= (TColor)clWindow;
        Edt6_WHR_KENSADATE1->Enabled= true;
        Edt6_WHR_KENSADATE2->Enabled= true;
        // OFF
        Pnl6_CHK_HINMEI->Color		= (TColor)clSilver;
        Pnl6_CHK_HINSYU->Color		= (TColor)clSilver;
        Pnl6_CHK_KOUMOKU->Color		= (TColor)clSilver;
        Edt6_CHK_HINMEI->Color		= (TColor)clSilver;
        Edt6_CHK_HINSYU->Color		= (TColor)clSilver;
        Clb6_CHK_KOUMOKU->Color		= (TColor)clSilver;
        Edt6_CHK_HINMEI->Enabled	= false;
        Edt6_CHK_HINSYU->Enabled	= false;
        Clb6_CHK_KOUMOKU->Enabled	= false;

		Pnl6_LOTNO_OUT->Caption		= "出力対象の品番･ﾛｯﾄ";
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
void __fastcall TForm1::Clb_CHK_TITLEClickCheck(TObject *Sender)
{

    int		i, k;
    int		iMax;
    TCheckListBox*	clb = dynamic_cast<TCheckListBox*>(Sender);

    if( clb->Name == "Clb2_CHK_TITLE" || clb->Name == "Clb4_CHK_TITLE" ){
        // 検査成績書（月別）
        // 材料証明書（月別）
    	iMax = 8;
    } else {
        // 検査成績書
        // 材料証明書
    	iMax = 8;
    }

    k = 0;
    for( i = 0; i < iTITLE_Cnt; i++){
        if( clb->Checked[i] == true ){
            k++;
        }
    }

    if( k > iMax ){
    	clb->Checked[clb->ItemIndex] = false;
    } else {
        // データ変更フラグの設定
        // DataChange = 1;
    }

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：指定条件での検索処理
//
//  機能説明
//    指定された品番・ロットNo
//    指定された品番・日付（出荷日又は検査日）
//    指定された検査日
//    が測定済みかどうか判断します。
//    検索された測定済みロットが有った場合、測定項目一覧を作成します
//
//  パラメタ説明
//    int		iType	：1 = 品番・ロットによる検索
//                        2 = 品番・出荷日による検索
//                        3 = 検査日による検索
//                        4 = 品番・ロットによる検索(未測定のロット出力)//2003.08.28 E.Takase
//    TEdit		*edtA	：代表得意先品番が指定されているTEdit
//    TEdit		*edtB	：ロットNOが指定されているTEdit
//    TMaskEdit	*edtC	：日付範囲（開始）
//    TMaskEdit	*edtD	：日付範囲（終了）
//    bool		iSEL_SZ	：素材検査項目の出力（true=する/false=しない）
//    bool		iSEL_SK	：出荷検査項目の出力（true=する/false=しない）
//    int		iSEL_TK	：特別出力項目の出力（true=する/false=しない）
//    bool		iSEL_ZR	：材料証明項目の出力（true=する/false=しない）
//
//  戻り値
//    bool				：true=検索成功、false=検索失敗
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::Get_DTKSHIN_LOT(int iType, TEdit *edtA, TEdit *edtB,
					TMaskEdit *edtC, TMaskEdit *edtD, bool iSEL_SZ, bool iSEL_SK, int iSEL_TK, bool iSEL_ZR)
{

	int			i1,iCount/*,iOldCol*/;
	int			iCnt,iCnt2;
	AnsiString	sDTKSHIN;
	AnsiString	sLot;
    AnsiString	sDate1, sDate2;
	AnsiString	sLot1,sLot2,sCmpStr,sBuf,sAllLot;
	bool		bKikanF[100];
	AnsiString	sRots[100];

    //2003/08/28 E.Takase
    //if( iType == 1 || iType == 2 ){
    if( iType == 1 || iType == 2  || iType == 4 ){
    	sDTKSHIN	= edtA->Text;

		// 品番入力チェック
		if( sDTKSHIN.Length() == 0 || sDTKSHIN.Trim() == "" ){
			MessageDlg("得意先品番の指定が正しくありません。", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
			edtA->SetFocus();
			return( false );
    	}
	}


    //2003/08/28 E.Takase
    //if( iType == 1 ){
    if( iType == 1 || iType == 4 ){
        //----------------------------------------
        // 品番・ロットでの検索を実行します

		sLot = edtB->Text;

		// ロット入力チェック
		if( sLot.Length() == 0 || sLot.Trim() == "" ){
			MessageDlg("ロットの指定が正しくありません。", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
			edtB->SetFocus();
			return( false );
		}

//2003/12/02 E.Takase
/*
		// 入力ロットに禁則文字がないか
		for( i1=1; i1<=sLot.Length(); i1++) {
			if( strcspn(sLot.SubString(i1,1).c_str(),"0123456789xyzXYZ -,")!=0) {
				MessageDlg("ロット入力が正しくありません。", mtWarning,
							TMsgDlgButtons() << mbOK , 0);
				edtB->SetFocus();
				return( false );
				//break;
			}
		}

		// 正しい数字かの確認
		for( i1=1; i1<=sLot.Length(); i1++) {
			if( strcspn(sLot.SubString(i1,1).c_str(),"0123456789")==0) {
			iCount = 1;
				i1++;
				while(strcspn(sLot.SubString(i1,1).c_str(),"0123456789")==0) {
					iCount++;
					i1++;
					if(i1 > sLot.Length()) break;
				}
				if(iCount < 3 || iCount > 6) {
					MessageDlg("ロット入力が正しくありません。", mtWarning,
								TMsgDlgButtons() << mbOK , 0);
					edtB->SetFocus();
					return( false );
				}
			}
		}

		//文字入力の確認(X,Y,Z)
		for( i1=1; i1<=sLot.Length(); i1++) {
			if( strcspn(sLot.SubString(i1,1).c_str(),"XYZxyz")==0) {
				iCount = 0;
				i1++;
				while(strcspn(sLot.SubString(i1,1).c_str(),"0123456789")==0) {
					iCount++;
					i1++;
					if(i1 > sLot.Length()) break;
				}
				if(iCount < 3 || iCount > 5) {
					MessageDlg("ロット入力が正しくありません。", mtWarning,
								TMsgDlgButtons() << mbOK , 0);
					edtB->SetFocus();
					return( false );
				}
			}
		}

		//間接子の妥当性確認
		for( i1=1; i1<=sLot.Length(); i1++) {
			if( strcspn(sLot.SubString(i1,1).c_str(),"-,")==0) {
				i1++;
				while(1) {
					if(strcspn(sLot.SubString(i1,1).c_str(),"0123456789XYZxyz")==0) {
						i1++;
						break;
					}
					if(strcspn(sLot.SubString(i1,1).c_str(),",-")==0) {
						MessageDlg("ロット入力が正しくありません。", mtWarning,
									TMsgDlgButtons() << mbOK , 0);
						edtB->SetFocus();
						return( false );
					}
					i1++;
					if(i1 > sLot.Length()) break;
				}
			}
		}

*/
//2003/12/02 E.Takase

		//ロットの切り出し（個別入力、区間入力対応すること）
		//数字の切り出し
		//ロット毎の読み出し（sLots[]へ代入)
		iCnt = 0;
		for( i1=1; i1<=sLot.Length(); i1++) {
			if( strcspn(sLot.SubString(i1,1).c_str(),"0123456789XYZxyz")==0) {
				iCount = 1;
				i1++;
				while(strcspn(sLot.SubString(i1,1).c_str(),"-, ")!=0) {
					i1++;
					iCount ++;
					if(i1 > sLot.Length()) break;
				}
				sRots[iCnt]=sLot.SubString(i1-iCount,iCount);
				iCnt ++;
				if( iCnt > 99 ) {                                             //onishi99
					MessageDlg("ロット指定範囲が多すぎます。", mtWarning,
								TMsgDlgButtons() << mbOK , 0);
					edtB->SetFocus();
					return( false );
				}
			}
		}

		//ロット属性（範囲OR個別）フラグ印加
		iCnt2 = 0;
		for( i1=1; i1<=sLot.Length(); i1++) {
			while( strcspn(sLot.SubString(i1,1).c_str(),"0123456789XYZxyz")==0
				&& (i1 < sLot.Length()) ) {
				i1+=sRots[iCnt2].Length();
				bKikanF[iCnt2]=false;
				while( strcspn(sLot.SubString(i1,1).c_str(),"0123456789XYZxyz")!=0
					&& (i1 < sLot.Length()) ) {
					if(strcspn(sLot.SubString(i1,1).c_str(),"-")==0) {
						bKikanF[iCnt2] = true;
						break;
					}
					i1++;
				}
				iCnt2++;
			}
		}
		iCnt2 -= 1;
		bKikanF[iCnt2] = false;

        // ロット文字列の長さを判断し以降の検索処理、ソート処理で使われます
        iLOT_LENGTH = sRots[0].Length();

		// KSD01測定実績データチェック用のロット文字列を作成します
		//iOldCol = 0;
		sAllLot = "";
		for(i1=0;i1<=iCnt2;i1++) {
			if( bKikanF[i1] == true ) {
				// 区間（範囲指定）で処理
				sLot1 = sRots[i1];
				sLot2 = sRots[i1+1];

				// 指定した開始ロットと終了ロットの測定済みロットリストを取得します。
				// 月をまたぐロットの範囲指定に対応（['LOTNO1','LOTNO2',]と戻ります）
                //2003/09/09 E.Takase
                if(iType == 4 ){
                	sAllLot += GetLotList2( sDTKSHIN, sLot1, sLot2 );
                } else {
                	sAllLot += GetLotList( sDTKSHIN, sLot1, sLot2 );
                }

                /* 旧コード（月をまたぐロットNoに未対応）
				sLot1 = sRots[i1].SubString(2,sRots[i1].Length()-1);
				sLot2 = sRots[i1+1].SubString(2,sRots[i1+1].Length()-1);
				for(iOldCol=sLot1.ToInt();iOldCol < sLot2.ToInt();iOldCol++) {
					sBuf = iOldCol;
					sAllLot += "'"+sRots[i1].SubString(1,1) + AnsiString::StringOfChar('0', sLot1.Length()-sBuf.Length()) + sBuf + "'";
					sAllLot += ",";
				}
                */
                i1++;
			}
			else {
				// 個別（カンマ区切り）で処理
				sAllLot += "'"+sRots[ i1 ]+"'";
				sAllLot += ",";
			}

		}

		// 最後の,を削除します
		sAllLot = sAllLot.SubString(1,sAllLot.Length()-1);

    } else {
        //------------------------------------------------------
        // 品番・日付（出荷日又は検査日）での検索を実行します

		sDate1 = DelSEPA(edtC->Text);
		sDate2 = DelSEPA(edtD->Text);

		// 日付入力チェック
		if( sDate1 < "19900101" || sDate1 > "21000101" ){
			MessageDlg("日付の指定が正しくありません。", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
			edtC->SetFocus();
			return( false );
		}
		if( sDate2 < "19900101" || sDate2 > "21000101" ){
			MessageDlg("日付の指定が正しくありません。", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
			edtD->SetFocus();
			return( false );
		}
		if( sDate2 < sDate1 ){
			MessageDlg("日付の指定が正しくありません。", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
			edtD->SetFocus();
			return( false );
		}

        // 対象ロットをロット順で検索します
        if( iType == 2 ){
			// 出荷日

        	// 指定品番のロットの長さを調べます
			sBuf = "SELECT LOTBNG FROM SD21S";
			sBuf += " WHERE DTKSHIN ='" + sDTKSHIN + "'";
			Query3->Close();
			Query3->SQL->Clear();
			Query3->SQL->Add(sBuf);
			Query3->Open();
			Query3->Active = true;
            sBuf = "12345";
			if(Query3->Eof == false) {
	    	    sBuf = Query3->FieldValues["LOTBNG"];
			}
			Query3->Close();
        	// ロット文字列の長さを判断し以降の検索処理、ソート処理で使われます
        	iLOT_LENGTH = sBuf.Length();

            // 2003/09/18 A.Tamura 出荷日の取得をSD15,SD16に変更
            /*
			sBuf = "SELECT LOTBNG FROM SD21S";
			sBuf += " WHERE DTKSHIN ='" + sDTKSHIN + "'";
			sBuf += " AND ESYUYMD >= '" + sDate1 + "'";
			sBuf += " AND ESYUYMD <= '" + sDate2 + "'";
            if( iLOT_LENGTH == 5 ){
        		sBuf += " ORDER BY SUBSTR(LOTBNG,2)";
        	} else {
        		sBuf += " ORDER BY LOTBNG";
            }
            */

/* 2005.09.26 Y.Sano 削除
			sBuf = "SELECT LOTBNG FROM SD15S RIGHT JOIN SD16S ON SD15S.JSKBNG = SD16S.JSKBNG";
			sBuf += " WHERE SD16S.TKSHIN='" + sDTKSHIN + "'";
			sBuf += " GROUP BY SD16S.LOTBNG";
			sBuf += " HAVING Min(SD15S.TSUYMD)>='" + sDate1 + "'";
			sBuf += " And Min(SD15S.TSUYMD)<='" + sDate2 + "'";


            if( iLOT_LENGTH == 5 ){
        		sBuf += " ORDER BY SUBSTR(LOTBNG,2)";
        	} else {
        		sBuf += " ORDER BY LOTBNG";
            }
*/
/*    2005.09.26 Y.Sano 検証用テスト  */
			sBuf = "SELECT LOTBNG FROM SD15S_16S ";
			sBuf += " WHERE TKSHIN='" + sDTKSHIN + "'";
			sBuf += " and TSUYMD_MIN>='" + sDate1 + "'";
			sBuf += " And TSUYMD_MIN<='" + sDate2 + "'";
            if( iLOT_LENGTH == 5 ){
        		sBuf += " ORDER BY SUBSTR(LOTBNG,2)";
        	} else {
        		sBuf += " ORDER BY LOTBNG";
            }

        } else {
			// 検査日

        	// ロット文字列の長さを判断し以降の検索処理、ソート処理で使われます
            iLOT_LENGTH == 5;		// 判断処理が困難な為、固定で5桁と仮定します

			sBuf = "SELECT DTKSHIN, LOTNO, HINBAN FROM KSD01";
            /*
			sBuf += " WHERE (SKTYMD >= '" + sDate1 + "'";
			sBuf += " AND SKTYMD <= '" + sDate2 + "')";
			sBuf += " OR (SKTYMD_PRT >= '" + sDate1 + "'";
			sBuf += " AND SKTYMD_PRT <= '" + sDate2 + "')";
            */
			sBuf += " WHERE SKTYMD_PRT >= '" + sDate1 + "'";
			sBuf += " AND SKTYMD_PRT <= '" + sDate2 + "'";
			sBuf += " ORDER BY DTKSHIN, HINBAN, SUBSTR(LOTNO,2)";
        }

		// Initial Query
		Query3->Close();
		Query3->SQL->Clear();
		Query3->SQL->Add(sBuf);
		Query3->Open();
		Query3->Active = true;

       	if( iType == 2 ){
			// 出荷日
			sAllLot = "";
			while(Query3->Eof == false) {
	        	sBuf = Query3->FieldValues["LOTBNG"];
	            if( sAllLot != "" )	sAllLot += ",";
    	        sAllLot += "'" + sBuf + "'";
				Query3->Next();
			}
			Query3->Close();

        } else {
			// 検査日
            sDtkshins->Clear();
			sLots->Clear();
			sHins->Clear();
            i1 = 0;
			while(Query3->Eof == false) {
				sDtkshins->Add( AnsiString(Query3->FieldValues["DTKSHIN"]) );
				sLots->Add( AnsiString(Query3->FieldValues["LOTNO"]) );
				sHins->Add( AnsiString(Query3->FieldValues["HINBAN"]) );
				Query3->Next();
            	i1++;
			}
			Query3->Close();

            if( i1 == 0 ){
				MessageDlg("指定された品番・ロットが見つかりません。", mtWarning,
							TMsgDlgButtons() << mbOK , 0);
				edtD->SetFocus();
				return( false );
        	}
        }

	}

    // 「検査日のみ検索」の処理以外指定ロットの存在チェックと測定項目の追加設定処理を行ないます
    if( iType != 3 ){

    	//2003/08/28 E.Takase
    	if(iType == 4 ){
            // 指定されたロットでKSD01測定実績及びKSD21素材測定実績データを取得しワークテーブルを作成します
            if( KSDCreateData(sDTKSHIN, sAllLot) == false ) {
				MessageDlg("データの作成に失敗しました。", mtWarning,
							TMsgDlgButtons() << mbOK , 0);
				edtA->SetFocus();
				return( false );
            }
    		// 指定されたロットをKSD01測定実績データ,KSD21素材測定実績データでチェックします
			if( KSD01GetLot2(sDTKSHIN, sAllLot) == false ) {
				MessageDlg("指定された品番・ロットが見つかりません。", mtWarning,
							TMsgDlgButtons() << mbOK , 0);
				edtA->SetFocus();
				return( false );
    		}

    		// 指定された品番・ロットの測定項目をKSD02測定実績データ,KSD22素材測定実績データから全て取得します
    		if( KSD02GetKOMOKU2(sDTKSHIN, sAllLot, iSEL_SZ, iSEL_SK, iSEL_TK, iSEL_ZR) == false ) {
				MessageDlg("指定された品番・ロットの測定項目が見つかりません。", mtWarning,
							TMsgDlgButtons() << mbOK , 0);
				edtA->SetFocus();
				return( false );
    		}

        } else {
    		// 指定されたロットをKSD01測定実績データでチェックします
			if( KSD01GetLot(sDTKSHIN, sAllLot) == false ) {
				MessageDlg("指定された品番・ロットが見つかりません。", mtWarning,
							TMsgDlgButtons() << mbOK , 0);
				edtA->SetFocus();
				return( false );
    		}

    		// 指定された品番・ロットの測定項目をKSD02測定実績データから全て取得します
    		if( KSD02GetKOMOKU(sDTKSHIN, sAllLot, iSEL_SZ, iSEL_SK, iSEL_TK, iSEL_ZR) == false ) {
				MessageDlg("指定された品番・ロットの測定項目が見つかりません。", mtWarning,
							TMsgDlgButtons() << mbOK , 0);
				edtA->SetFocus();
				return( false );
    		}
    	}

    }

    return( true );

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：指定された範囲指定のロットNOの有効ロットNOを問い合わせます
//
//  機能説明
//    指定した開始ロットと終了ロットの測定済みロットリストを取得します。
//    月をまたぐロットの範囲指定に対応しています
//
//  パラメタ説明
//    AnsiString sDTKSHIN：代表得意先品番
//    AnsiString sLOT_S	：開始ロットNO
//    AnsiString sLOT_E	：終了ロットNO
//
//  戻り値
//    AnsiString		：カンマで区切られたロットNOリストの文字列をかえします
//                        ['LOTNO1','LOTNO2',]と戻ります
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::GetLotList(AnsiString sDTKSHIN, AnsiString sLOT_S, AnsiString sLOT_E)
{
	AnsiString sBuf;
	AnsiString sRet;

	if( sLOT_S.Trim() == "" || sLOT_E.Trim() == "" ) return( "" );

	sBuf = "SELECT LOTNO FROM KSD01";
	sBuf += " WHERE DTKSHIN = '" + sDTKSHIN + "'";

    if( iLOT_LENGTH == 5 ){
	    // 国内ロット（5桁）に対応
    	sBuf += " AND SUBSTR(LOTNO,2) >= '" + sLOT_S.SubString(2,5) + "'";
	    sBuf += " AND SUBSTR(LOTNO,2) <= '" + sLOT_E.SubString(2,5) + "'";
        sBuf += " AND SKTYMD >= '" + Edt_SEIKAN_YMD->Text + "'";      //onishi
	    sBuf += " ORDER BY SUBSTR(LOTNO,2)";
	} else {
	    // 海外ロット（6桁）に対応
    	sBuf += " AND LOTNO >= '" + sLOT_S + "'";
	    sBuf += " AND LOTNO <= '" + sLOT_E + "'";
        sBuf += " AND SKTYMD >= '" + Edt_SEIKAN_YMD->Text + "'";      //onishi
	    sBuf += " ORDER BY LOTNO";
	}

	// Initial Query
	Query3->Close();
	Query3->SQL->Clear();
	Query3->SQL->Add(sBuf);
	Query3->Open();
	Query3->Active = true;
    sRet = "";
	while(Query3->Eof == false) {

        if( !VarIsNull(Query3->FieldValues["LOTNO"]) ){
        	sRet += "'" + AnsiString(Query3->FieldValues["LOTNO"]) + "',";
        }

		Query3->Next();
	}
	Query3->Close();

	return( sRet );

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：指定されたロットNOリストの有効ロットNOを問い合わせます
//
//  機能説明
//    指定したロットNOリストが測定済みロットかどうかを取得します。
//
//  パラメタ説明
//    AnsiString sDTKSHIN：代表得意先品番
//    AnsiString sLOT	：ロットNOリスト（カンマ区切り）
//    (OUT)
//    StringList sLots	：有効なロットNOリスト（StringList）
//
//  戻り値
//    bool				：true=対象ロットあり、false=対象ロットなし
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::KSD01GetLot(AnsiString sDTKSHIN, AnsiString sLOT)
{
	AnsiString sBuf;
	bool bRet;
	int iCol;

	if( sLOT.Trim() == "" ) return( false );

	iCol = 0;
	sBuf = "SELECT * FROM KSD01";
	sBuf += " WHERE DTKSHIN = '" + sDTKSHIN + "'";
	sBuf += " AND   SKTYMD >= '" + Edt_SEIKAN_YMD->Text + "'";      //onishi
	sBuf += " AND   LOTNO IN (" + sLOT + ")";
    if( iLOT_LENGTH == 5 ){
		sBuf += " ORDER BY SUBSTR(LOTNO,2)";
    } else {
		sBuf += " ORDER BY LOTNO";
    }

    bRet = false;
    sLots->Clear();
    sHins->Clear();

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();
	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;
	while(Query1->Eof == false) {

        if( iCol >= 99 ){                                                     //onishi99
			MessageDlg("一度に扱えるロット数(最大99件)を超えました。\n以降のロットは対象外になります。",
            			mtWarning, TMsgDlgButtons() << mbOK , 0);
        	break;
        }

        if( !VarIsNull(Query1->FieldValues["LOTNO"]) ){
        	sLots->Add( AnsiString(Query1->FieldValues["LOTNO"]) );
        	sHins->Add( AnsiString(Query1->FieldValues["HINBAN"]) );
        }

		Query1->Next();
		iCol++;
	}

	if( iCol > 0 ) bRet = true;

	return( bRet );
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：有効な測定項目の検索
//
//  機能説明
//    指定した品番・ロット・検索条件から有効な測定項目をKSD02データから取得し
//    検査項目にチェックを付けます
//
//  パラメタ説明
//    AnsiString sDTKSHIN：代表得意先品番
//    AnsiString sLOT	：ロットNOリスト（カンマ区切り）
//    bool		iSEL_SZ	：素材検査項目の出力（true=する/false=しない）
//    bool		iSEL_SK	：出荷検査項目の出力（true=する/false=しない）
//    int		iSEL_TK	：特別出力項目の出力（true=する/false=しない）
//    bool		iSEL_ZR	：材料証明項目の出力（true=する/false=しない）
//
//  戻り値
//    bool				：true=検索成功、false=検索失敗
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::KSD02GetKOMOKU(AnsiString sDTKSHIN, AnsiString sLOT,
                             bool iSEL_SZ, bool iSEL_SK, int iSEL_TK, bool iSEL_ZR)
{
	int				i, k, iCol;
	bool			bRet;
	AnsiString		sBuf;
    int				iSKB_NO;
    int				iTOKU_FLG;
    TCheckListBox*	clb;


	iCol = 0;
	sBuf = "SELECT * FROM KSD02";
	sBuf += " WHERE DTKSHIN ='" + sDTKSHIN + "'";
	sBuf += " AND   SKTYMD >= '" + Edt_SEIKAN_YMD->Text + "'";      //onishi
	sBuf += " AND   LOTNO IN (" + sLOT + ")";
	sBuf += " ORDER BY ORDER_NO";
	//sBuf += " ORDER BY SUBSTR(LOTNO,2), ORDER_NO";

    bRet = false;


	if( PgCtr_REPORT->ActivePage->Name == "TabSheet1" ){
        // 検査成績書
    	clb = dynamic_cast<TCheckListBox*>(Clb1_CHK_KOUMOKU);
    }
    else if( PgCtr_REPORT->ActivePage->Name == "TabSheet2" ){
        // 検査成績書（月別）
    	clb = dynamic_cast<TCheckListBox*>(Clb2_CHK_KOUMOKU);
    }
    else if( PgCtr_REPORT->ActivePage->Name == "TabSheet3" ){
        // 材料証明書
    	clb = dynamic_cast<TCheckListBox*>(Clb3_CHK_KOUMOKU);
    }
    else if( PgCtr_REPORT->ActivePage->Name == "TabSheet4" ){
        // 材料証明書（月別）
    	clb = dynamic_cast<TCheckListBox*>(Clb4_CHK_KOUMOKU);
    }
    else if( PgCtr_REPORT->ActivePage->Name == "TabSheet5" ){
        // 検査結果時系列管理表
    	clb = dynamic_cast<TCheckListBox*>(Clb5_CHK_KOUMOKU);
    }
    else if( PgCtr_REPORT->ActivePage->Name == "TabSheet6" ){
        // 検査経歴票
    	clb = dynamic_cast<TCheckListBox*>(Clb6_CHK_KOUMOKU);
    }

    clb->Clear();

	// Initial Query
	Query2->Close();
	Query2->SQL->Clear();
	Query2->SQL->Add(sBuf);
	Query2->Open();
	Query2->Active = true;
	while(Query2->Eof == false) {

        // 測定項目として出力します。
        iSKB_NO = AnsiString(Query2->FieldValues["SKB_NO"]).ToIntDef(9);
        if( iSKB_NO != 9 ){
            sBuf = "";
        	if( !VarIsNull(Query2->FieldValues["KOMK_NM"]) ){
        		sBuf = Query2->FieldValues["KOMK_NM"];
            }
        	if( !VarIsNull(Query2->FieldValues["KOMK_SUB"]) ){
        		sBuf = sBuf + " " + Query2->FieldValues["KOMK_SUB"];
            }
            // 2003/10/21 A.Tamura [単位]も含めて選択条件に入れる。
        	if( !VarIsNull(Query2->FieldValues["TANI"]) ){
        		sBuf = sBuf + " " + Query2->FieldValues["TANI"];
            }
            if( sBuf != "" ){

		        iTOKU_FLG = AnsiString(Query2->FieldValues["TOKU_FLG"]).ToIntDef(0);

                // 未登録の測定項目が有った場合だけ、追加します
                k = 0;
				for( i = 0; i < clb->Items->Count; i++){
					if( clb->Items->Strings[i] == sBuf ){
						k = 1;
                        break;
                    }
                }
                if( k == 0 ){

                	// 新しい測定項目を追加します
			        clb->Items->Add(sBuf);

                	// 素材検査項目で素材検査項目を選択する時はチェックON
                    if( iSKB_NO == 1 ){
                    	if( iSEL_SZ == true ){
							clb->Checked[clb->Items->Count-1] = true;
                    	} else {
                        	clb->Checked[clb->Items->Count-1] = false;
                    	}
                    }

                	// 出荷検査項目で出荷検査項目を選択する時はチェックON
                    if( iSKB_NO == 2 ){
                    	if( iSEL_SK == true ){
							clb->Checked[clb->Items->Count-1] = true;
                    	} else {
                        	clb->Checked[clb->Items->Count-1] = false;
                    	}
                    }

                	// 特別検査項目で特別検査項目を選択する時はチェックON
                    if( iTOKU_FLG == 1 ){
                    	if( iSEL_TK == 1 ){
                        	// 「する」
							clb->Checked[clb->Items->Count-1] = true;
                    	} else if( iSEL_TK == 0 ){
                        	// 「しない」
                        	clb->Checked[clb->Items->Count-1] = false;
                    	} else {
                        	// 「無効」
                    	}
                    }

                	// 材料証明項目で材料証明項目を選択する時はチェックON
                    if( iSKB_NO == 3 ){
                    	if( iSEL_ZR == true ){
							clb->Checked[clb->Items->Count-1] = true;
                    	} else {
                        	clb->Checked[clb->Items->Count-1] = false;
                    	}
                    }
				}
            }

        }

		Query2->Next();
		iCol++;
	}

	//Query1->Close();
    if( iCol > 0 ) bRet = true;

	return( bRet );
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：タイトル情報のデータを検索します
//
//  機能説明
//    指定された品番・ロットのタイトル情報項目データを取得します
//
//  パラメタ説明
//    AnsiString sDTKSHIN：代表得意先品番
//    AnsiString sLOT	 ：ロットNOリスト（カンマ区切り）
//    int		 iTileNo ：タイトル項目NO
//                         1:品番、2:品種、3:発行日、4:ロットNo
//                         5:納入数、6:測定日、7:品名、8:注文No 10:出荷日
//    bool		 iJapanese：true=日本語フォーマット、false=英語フォーマット
//
//  戻り値
//    AnsiString		：取得した文字列
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::GetTitleData(AnsiString sDTKSHIN, AnsiString sLOT, int iTileNo, bool iJapanese)
{

	AnsiString	sBuf;
	AnsiString	sSQL;


    sBuf = "";


    // 1:品番
    if( iTileNo == 1 ){
    	sBuf = sDTKSHIN;
    }

    // 3:発行日
    if( iTileNo == 3 ){
    	sBuf = FormatDateTime("yyyy/mm/dd",Date());
        if( iJapanese == false ){
        	sBuf = ToDateEnglish(sBuf);
        }
    }

    // 4:ロットNo
    // 桁数指定なので何も返さない

    // 5:納入数
    if( iTileNo == 5 ){
		sSQL = "SELECT SIJISU FROM SD21S";
		sSQL += " WHERE DTKSHIN ='" + sDTKSHIN + "'";
		sSQL += " AND LOTBNG = '" + sLOT + "'";

		// Initial Query
		Query3->Close();
		Query3->SQL->Clear();
		Query3->SQL->Add(sSQL);
		Query3->Open();
		Query3->Active = true;
		if(Query3->Eof == false) {
        	//sBuf = AnsiString(Query3->FieldValues["SIJISU"]).ToIntDef(0);
            sBuf = FormatFloat("#,##0", (double)AnsiString(Query3->FieldValues["SIJISU"]).ToIntDef(0));
		}
		Query3->Close();
    }

    // 8:注文No
    // 取得しない。（仕様打合せ会議で取得しないことで決定した）

    // 2:品種、6:測定日、7:品名
    if( iTileNo == 2 || iTileNo == 6 || iTileNo == 7 ){
	    Query1->FindFirst();
		while(Query1->Eof == false) {

	        // 同じ品番・ロットのデータを探します
	        if( Query1->FieldValues["DTKSHIN"] == sDTKSHIN &&
	            Query1->FieldValues["LOTNO"] == sLOT ){
                // 2:品種
                if( iTileNo == 2 ){
                    if( !VarIsNull(Query1->FieldValues["ZISNAM"]) ){
                		sBuf = Query1->FieldValues["ZISNAM"];
                    }
                }
                // 6:測定日
                if( iTileNo == 6 ){
		        	if( !VarIsNull(Query1->FieldValues["SKTYMD_PRT"]) ){
                        if( AnsiString(Query1->FieldValues["SKTYMD_PRT"]).Trim() != "" ){
							sBuf = Query1->FieldValues["SKTYMD_PRT"];
							sBuf = sBuf.Insert("/",5);
							sBuf = sBuf.Insert("/",8);
					        if( iJapanese == false ){
					        	sBuf = ToDateEnglish(sBuf);
					        }
                    	}
                    }
                }
                // 7:品名
                if( iTileNo == 7 ){
		        	if( !VarIsNull(Query1->FieldValues["HINMEI"]) ){
                		sBuf = Query1->FieldValues["HINMEI"];
                    }
                }

                break;
	        }

			Query1->Next();
		}
	}

    //2004.06.09 E.Takase ADD
    // 10:出荷日
    if( iTileNo == 10 ){
    	sBuf = FormatDateTime("yyyy/mm/dd",Date());
        if( iJapanese == false ){
        	sBuf = ToDateEnglish(sBuf);
        }
    }

	return( sBuf );

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：レポート作成処理を開始します
//
//  機能説明
//    指定された出力情報から印刷指示ファイル(CSV)を作成し、Excelを起動します
//
//  パラメタ説明
//    int iAutoType		：出力形式
//                        0=印刷指示CSVファイル作成→Excel起動→印刷→Excel終了
//                        1=印刷指示CSVファイル作成→Excel起動
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::CreateReport(int iAutoType)
{

    int			i, k, m, p;
    int			iEnglish;
    int			iX_OUT;
    int			iSKB_NO;
    int			iBLANK;
    int			iLOT_KETA;
	AnsiString	sBuf;
	AnsiString	sDTKSHIN;
	AnsiString	sLOTNO;
	AnsiString	sBuf1,sBuf2,sBuf3,sBuf4,sBuf5,sBuf6,sBuf7,sBuf8;
    double		dVal1, dVal2, dVal3;

    int			iBuf;
	AnsiString	sReSOKU_SU;
	AnsiString	sReKIKA_PRT;
	AnsiString	sReVALUE_TYPE;
	AnsiString	sReVALUE_DECI;
    int			iReDISP_VAL_SU;
	AnsiString	sReDISP_VAL_SU;
	AnsiString	sReDISP_VAL_AVE;
	AnsiString	sReDISP_VAL_MAX;
	AnsiString	sReDISP_VAL_MIN;
	AnsiString	sReDISP_OK;
	TStrings	*sReDISP_VAL;
	sReDISP_VAL	= new TStringList;

    FILE		*stream;

    bool        retDLL;
	char 		path[256];

    bool		bOKFlag;	//Excel起動フラグ

    bOKFlag = false;

    //--------------------------------------------------------------------------------------------
    // 検査成績書指示ファイルの作成
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet1" ){

    	    // 出力内容の確認が押されていない場合は、自動実行します
    	    if( iNowTab != 1 ){
			Btn1_OUT_CHECKClick(Btn1_OUT_CHECK);
			if( ret_Btn1_OUT_CHECKClick == false ) return;
            }

    	if( (stream = fopen( sRepData1, "w+" )) != NULL ){
    		// 正常にファイルをオープンできた場合

			// [印刷の形式(0=印刷して自動終了/1=Excel終了しない、印刷なし）],
            // [品番],
            // [社名],
            // [出力形式(0=日本語/1=英語)],
            // [Xの出力(0=しない/1=する)]
            if( Rdo1_WHR_FORMAT_JPN->Checked == true )		iEnglish = 0;
            else											iEnglish = 1;
            if( Rdo1_CHK_X_ON->Checked == true )			iX_OUT = 1;
            //20161214 Y.Onishi
            //Cp,Cpk出力に対応
            else if( Rdo1_CHK_X_CP->Checked == true )			iX_OUT = 2;
            else											iX_OUT = 0;
			fprintf( stream,"%d,%s,\"%s\",%d,%d\n",
            								iAutoType,
											Edt1_WHR_DTKSHIN->Text.c_str(),
											Edt1_CHK_CUSTOMER->Text.c_str(),
                                            iEnglish,
                                            iX_OUT );

            // [タイトル部1],[タイトル部2],[タイトル部3],[...4],[...5],[...6],[...7],[タイトル部8]
            // (日本語)
            k = 0;
    		for( i = 0; i < iTITLE_Cnt; i++){
        		if( Clb1_CHK_TITLE->Checked[i] == true ){
            		sBuf = sTITLE_JPN->Strings[i];
                    if( k == 0 )	fprintf( stream, "\"%s\"", sBuf.c_str() );
                    else        	fprintf( stream,",\"%s\"", sBuf.c_str() );
                    k++;
                }
            }
    		for( i = k; i < 8; i++){
                fprintf( stream,"," );
            }
            fprintf( stream,"\n" );

            // [タイトル部1],[タイトル部2],[タイトル部3],[...4],[...5],[...6],[...7],[タイトル部8]
            // (英語)
            k = 0;
    		for( i = 0; i < iTITLE_Cnt; i++){
        		if( Clb1_CHK_TITLE->Checked[i] == true ){
            		sBuf = sTITLE_ENG->Strings[i];
                    if( k == 0 )	fprintf( stream, "\"%s\"", sBuf.c_str() );
                    else        	fprintf( stream,",\"%s\"", sBuf.c_str() );
                    k++;
                }
            }
    		for( i = k; i < 8; i++){
                fprintf( stream,"," );
            }
            fprintf( stream,"\n" );

            // 備考（改行コードを[CR+LF]に変換します）
            sBuf = "";
    		for( i = 0; i < Memo1_CHK_REMARK->Lines->Count; i++){
            	sBuf = sBuf + Memo1_CHK_REMARK->Lines->Strings[i];
            	sBuf = sBuf + "[CR+LF]";
            }
			fprintf( stream,"%s\n", sBuf.c_str() );

            // ロット数
			fprintf( stream,"%d\n", PgCtr1_LOT->Tag );

          	// [ロットNo1],[タイトル部1],[タイトル部2],[タイトル部3],[...4],[...5],[...6],[...7],[タイトル部8]
            // 指定ロット数分出力します
    		for( i = 0; i < PgCtr1_LOT->Tag; i++){

                if( i == 0 ){
                	// 1ロット目
					sLOTNO = PgCtr1_tst01->Caption.Trim();

                    if( PgCtr1_tst1_Edt1->Tag == 4 )	sBuf1 = GetTitleLotNo( i );
                    else								sBuf1 = PgCtr1_tst1_Edt1->Text;
                    if( PgCtr1_tst1_Edt2->Tag == 4 )	sBuf2 = GetTitleLotNo( i );
                    else								sBuf2 = PgCtr1_tst1_Edt2->Text;
                    if( PgCtr1_tst1_Edt3->Tag == 4 )	sBuf3 = GetTitleLotNo( i );
                    else								sBuf3 = PgCtr1_tst1_Edt3->Text;
                    if( PgCtr1_tst1_Edt4->Tag == 4 )	sBuf4 = GetTitleLotNo( i );
                    else								sBuf4 = PgCtr1_tst1_Edt4->Text;
                    if( PgCtr1_tst1_Edt5->Tag == 4 )	sBuf5 = GetTitleLotNo( i );
                    else								sBuf5 = PgCtr1_tst1_Edt5->Text;
                    if( PgCtr1_tst1_Edt6->Tag == 4 )	sBuf6 = GetTitleLotNo( i );
                    else								sBuf6 = PgCtr1_tst1_Edt6->Text;
                    if( PgCtr1_tst1_Edt7->Tag == 4 )	sBuf7 = GetTitleLotNo( i );
                    else								sBuf7 = PgCtr1_tst1_Edt7->Text;
                    if( PgCtr1_tst1_Edt8->Tag == 4 )	sBuf8 = GetTitleLotNo( i );
                    else								sBuf8 = PgCtr1_tst1_Edt8->Text;
                }
                else {
                	// 2ロット目以降
					sLOTNO = PgCtr1_tst[i+1]->Caption.Trim();

                   	if( PgCtr1_tst1_Edt1->Tag == 4 )	sBuf1 = GetTitleLotNo( i+1 );
                   	else								sBuf1 = PgCtr1_tst_Edt[i+1][0]->Text;
                   	if( PgCtr1_tst1_Edt2->Tag == 4 )	sBuf2 = GetTitleLotNo( i+1 );
                   	else								sBuf2 = PgCtr1_tst_Edt[i+1][1]->Text;
                   	if( PgCtr1_tst1_Edt3->Tag == 4 )	sBuf3 = GetTitleLotNo( i+1 );
                   	else								sBuf3 = PgCtr1_tst_Edt[i+1][2]->Text;
                   	if( PgCtr1_tst1_Edt4->Tag == 4 )	sBuf4 = GetTitleLotNo( i+1 );
                   	else								sBuf4 = PgCtr1_tst_Edt[i+1][3]->Text;
                   	if( PgCtr1_tst1_Edt5->Tag == 4 )	sBuf5 = GetTitleLotNo( i+1 );
                   	else								sBuf5 = PgCtr1_tst_Edt[i+1][4]->Text;
                   	if( PgCtr1_tst1_Edt6->Tag == 4 )	sBuf6 = GetTitleLotNo( i+1 );
                   	else								sBuf6 = PgCtr1_tst_Edt[i+1][5]->Text;
                   	if( PgCtr1_tst1_Edt7->Tag == 4 )	sBuf7 = GetTitleLotNo( i+1 );
                   	else								sBuf7 = PgCtr1_tst_Edt[i+1][6]->Text;
                   	if( PgCtr1_tst1_Edt8->Tag == 4 )	sBuf8 = GetTitleLotNo( i+1 );
                   	else								sBuf8 = PgCtr1_tst_Edt[i+1][7]->Text;
                }

				fprintf( stream,"%s,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\n",
                												sLOTNO.c_str(),
																sBuf1.c_str(),
																sBuf2.c_str(),
																sBuf3.c_str(),
																sBuf4.c_str(),
																sBuf5.c_str(),
																sBuf6.c_str(),
																sBuf7.c_str(),
																sBuf8.c_str());
            }

            // 区切り
			fprintf( stream,"@@@出力項目@@@\n" );

          	// [ロットNo1],[タイトル部1],[タイトル部2],[タイトル部3],[...4],[...5],[...6],[...7],[タイトル部8]
            // 指定ロット数分出力します
    		for( i = 0; i < PgCtr1_LOT->Tag; i++){

				if( i == 0 ){
					sLOTNO = PgCtr1_tst01->Caption.Trim();
				}
				else {
					sLOTNO = PgCtr1_tst[i+1]->Caption.Trim();
				}

				Query2->FindFirst();
				while(Query2->Eof == false) {

					sBuf = Query2->FieldValues["LOTNO"];

                    // 該当のロットＮｏを処理します
                    if( sLOTNO == sBuf ){

						// 測定項目として出力します。
						iSKB_NO = AnsiString(Query2->FieldValues["SKB_NO"]).ToIntDef(9);
						if( iSKB_NO != 9 ){

							sBuf = "";
							if( !VarIsNull(Query2->FieldValues["KOMK_NM"]) ){
								sBuf = Query2->FieldValues["KOMK_NM"];
							}
							if( !VarIsNull(Query2->FieldValues["KOMK_SUB"]) ){
								sBuf = sBuf + " " + Query2->FieldValues["KOMK_SUB"];
							}
							// 2003/10/21 A.Tamura [単位]も含めて選択条件に入れる。
							if( !VarIsNull(Query2->FieldValues["TANI"]) ){
								sBuf = sBuf + " " + Query2->FieldValues["TANI"];
							}
							if( sBuf != "" ){

								// 選択されている項目だけ出力対象と判断します
                                k = 0;
								for( m = 0; m < Clb1_CHK_KOUMOKU->Items->Count; m++){
									if( Clb1_CHK_KOUMOKU->Items->Strings[m] == sBuf ){
                                        if( Clb1_CHK_KOUMOKU->Checked[m] == true ){
											k = 1;
										}
                                        break;
									}
								}
								if( k == 1 ){
									// 出力項目（測定項目行）を書き込みます
                                    bOKFlag = true;	//2003/07/22 E.Takase
									fprintf( stream, "%s,%d,",
                                    	                sLOTNO.c_str(),
                                                        iSKB_NO );
                                    fprintf( stream, "\"%s\",\"%s\",\"%s\",\"%s\",%d,%s,%s,",
                                    					Null_S(Query2->FieldValues["KOMK_NM"]).c_str(),
                                                        Null_S(Query2->FieldValues["KOMK_ENG"]).c_str(),
                                                        Null_S(Query2->FieldValues["KOMK_SUB"]).c_str(),
                                                        Null_S(Query2->FieldValues["KOMK_SUB_ENG"]).c_str(),
                                                        AnsiString(Query2->FieldValues["KIKI_NO"]).ToIntDef(0),
                                                        Null_S(Query2->FieldValues["KIKI_NM"]).c_str(),
                                                        Null_S(Query2->FieldValues["TANI"]).c_str() );
                                    dVal1 = Query2->FieldValues["KIKA_NUM1"];
                                    dVal2 = Query2->FieldValues["KIKA_NUM2"];
                                    dVal3 = Query2->FieldValues["KIKA_NUM3"];
                                    fprintf( stream, "%d,%d,%d,%f,%f,%f,%s,",
                                    					AnsiString(Query2->FieldValues["KIKA_TYPE"]).ToIntDef(1),
                                    					AnsiString(Query2->FieldValues["KIKA_KIND"]).ToIntDef(1),
                                    					AnsiString(Query2->FieldValues["KIKA_DECI"]).ToIntDef(0),
                                    					dVal1,
                                    					dVal2,
                                    					dVal3,
                                                        Null_S(Query2->FieldValues["KIKA_STR"]).c_str() );

                                    fprintf( stream, "%d,%d,%d,",
                                      					AnsiString(Query2->FieldValues["KIKA_PRT"]).ToIntDef(0),
                                       					AnsiString(Query2->FieldValues["VALUE_TYPE"]).ToIntDef(0),
                                       					AnsiString(Query2->FieldValues["VALUE_DECI"]).ToIntDef(0) );

                                    // 測定項目の有無			2003/08/28 A.Tamura
                                    if( Query2->FieldValues["SOKU_FLG"] == 0 ){
                                    	// 「測定しない」の時

                                        //2003/10/22 E.Takase 検索条件に単位追加
				                  		//iBuf = GetBeforeLotVal(
                                        //			Null_S(Query2->FieldValues["DTKSHIN"]),
                                        //            Null_S(Query2->FieldValues["LOTNO"]),
					                	//            Null_S(Query2->FieldValues["KOMK_NM"]),
                                    	//			Null_S(Query2->FieldValues["KOMK_SUB"]),
                                    	//			Null_S(Query2->FieldValues["HINBAN_SK"]),
                                    	//			atoi(Null_S(Query2->FieldValues["KIKI_NO"]).c_str()),
                                    	//			atoi(Null_S(Query2->FieldValues["KOMK_NO"]).c_str()),
                                		//			&sReSOKU_SU, &sReKIKA_PRT, &sReVALUE_TYPE,
                                    	//			&sReVALUE_DECI, &sReDISP_VAL_SU, &sReDISP_VAL_AVE,
                                    	//			&sReDISP_VAL_MAX, &sReDISP_VAL_MIN, &sReDISP_OK, sReDISP_VAL );
				                  		iBuf = GetBeforeLotVal(
                                        			Null_S(Query2->FieldValues["DTKSHIN"]),
                                                    Null_S(Query2->FieldValues["LOTNO"]),
					                	            Null_S(Query2->FieldValues["KOMK_NM"]),
                                    				Null_S(Query2->FieldValues["KOMK_SUB"]),
                                    				Null_S(Query2->FieldValues["HINBAN_SK"]),
                                    				atoi(Null_S(Query2->FieldValues["KIKI_NO"]).c_str()),
                                    				atoi(Null_S(Query2->FieldValues["KOMK_NO"]).c_str()),
                                    				Null_S(Query2->FieldValues["TANI"]),
                                					&sReSOKU_SU, &sReKIKA_PRT, &sReVALUE_TYPE,
                                    				&sReVALUE_DECI, &sReDISP_VAL_SU, &sReDISP_VAL_AVE,
                                    				&sReDISP_VAL_MAX, &sReDISP_VAL_MIN, &sReDISP_OK, sReDISP_VAL );
                                    	iReDISP_VAL_SU = sReDISP_VAL_SU.ToIntDef(0);
                                        // 2003/11/5 A.Tamura 履歴の該当ロットが見つからない時、DISP_VAL_SUは、出力ロットのSOKU_SUをします
                                        if( iBuf < 0 ){
                                        	sReDISP_VAL_SU = AnsiString(Query2->FieldValues["SOKU_SU"]);
                                        	iReDISP_VAL_SU = 0;
                                        }

										// 測定数、平均値
                                        fprintf( stream, "%s,%s", sReDISP_VAL_SU, sReDISP_VAL_AVE );

                                        // 測定値1〜の値設定
										for( m = 0; m < iReDISP_VAL_SU; m++){
 										    fprintf( stream, ",%s", sReDISP_VAL->Strings[m].c_str() );
                                        }

                                        // 測定値が10に満たない場合は空白を設定
										for( m = iReDISP_VAL_SU; m < 10; m++){
 										    fprintf( stream, ",%s", " " );
                                        }

                                    }
                                    else {
                                    	// 「測定する」の時

										// 測定数、平均値
                                        dVal1 = Query2->FieldValues["DISP_VAL_AVE"];
                                        fprintf( stream, "%d,%f,",
                                        					AnsiString(Query2->FieldValues["DISP_VAL_SU"]).ToIntDef(0),
                                                            dVal1 );

                                        // 測定値1〜10の値設定
                                        fprintf( stream, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
                                        					Null_S(Query2->FieldValues["DISP_VAL01"]).c_str(),
                                        					Null_S(Query2->FieldValues["DISP_VAL02"]).c_str(),
                                        					Null_S(Query2->FieldValues["DISP_VAL03"]).c_str(),
                                        					Null_S(Query2->FieldValues["DISP_VAL04"]).c_str(),
                                        					Null_S(Query2->FieldValues["DISP_VAL05"]).c_str(),
                                        					Null_S(Query2->FieldValues["DISP_VAL06"]).c_str(),
                                        					Null_S(Query2->FieldValues["DISP_VAL07"]).c_str(),
                                        					Null_S(Query2->FieldValues["DISP_VAL08"]).c_str(),
                                        					Null_S(Query2->FieldValues["DISP_VAL09"]).c_str(),
                                        					Null_S(Query2->FieldValues["DISP_VAL10"]).c_str() );

                                        // 測定値11〜の値設定
                                        if( AnsiString(Query2->FieldValues["DISP_VAL_SU"]).ToIntDef(0) > 10 ){
											sBuf = "SELECT * FROM KSD03";
											sBuf += " WHERE DTKSHIN ='" + Edt1_WHR_DTKSHIN->Text + "'";
											sBuf += " AND LOTNO = '" + sLOTNO + "'";
											sBuf += " AND UNQ_NO = " + AnsiString(Query2->FieldValues["UNQ_NO"]);
											sBuf += " ORDER BY SOKU_NO";

											// Initial Query
											Query3->Close();
											Query3->SQL->Clear();
											Query3->SQL->Add(sBuf);
											Query3->Open();
											Query3->Active = true;
 	 										while(Query3->Eof == false) {
			                                    fprintf( stream, ",%s",
                                                			Null_S(Query3->FieldValues["DISP_VAL"]).c_str() );
  	  											Query3->Next();
  	  										}
                                        }

                                    }

                                    fprintf( stream, "\n" );
                             	}
							}
						}
                        else {
							// 出力項目（空白行）を書き込みます
							fprintf( stream, "%s,%d,,,,,,,,,,,,,,,,,,,,0,0,,,,,,,,,,\n",
                            					sLOTNO.c_str(),	iSKB_NO);
                        }
					}
					Query2->Next();
				}
        	}
		}

	    // ファイルを閉じる
    	fclose(stream);

    }


    //--------------------------------------------------------------------------------------------
    // 検査成績書（月別）指示ファイルの作成
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet2" ){

    	// 出力内容の確認が押されていない場合は、自動実行します
    	if( iNowTab != 2 ){
			Btn1_OUT_CHECKClick(Btn2_OUT_CHECK);
			if( ret_Btn1_OUT_CHECKClick == false ) return;
    	}

    	if( (stream = fopen( sRepData2, "w+" )) != NULL ){
    		// 正常にファイルをオープンできた場合

			// [印刷の形式(0=印刷して自動終了/1=Excel終了しない、印刷なし）],
            // [品番],
            // [社名],
            // [納入月],
            // [出力形式(0=日本語/1=英語)],
            // [Xの出力(0=しない/1=する)]
            // [一行空けて出力(0=しない/1=する)]
            // [ロットＮｏの桁(4or5or6)]
            if( Rdo2_WHR_FORMAT_JPN->Checked == true )		iEnglish = 0;
            else											iEnglish = 1;
            if( Rdo2_CHK_X_ON->Checked == true )			iX_OUT = 1;
            else											iX_OUT = 0;
            if( Rdo2_WHR_BLANK_ON->Checked == true )		iBLANK = 1;
            else											iBLANK = 0;
            if( Rdo2_WHR_TYPE1->Checked == true )			sDTKSHIN = Edt2_WHR_DTKSHIN1->Text;
            else											sDTKSHIN = Edt2_WHR_DTKSHIN2->Text;
            if( Rdo2_LOT_KETA4->Checked == true ){			iLOT_KETA = 4;
            } else if( Rdo2_LOT_KETA5->Checked == true ){   iLOT_KETA = 5;
            } else {                                        iLOT_KETA = 6;
            }
			fprintf( stream,"%d,%s,\"%s\",\"%s\",%d,%d,%d,%d\n",
            								iAutoType,
											sDTKSHIN.c_str(),
											Edt2_CHK_CUSTOMER->Text.c_str(),
                                            Edt2_TITLE_MONTH->Text.c_str(),
                                            iEnglish,
                                            iX_OUT,
                                            iBLANK,
                                            iLOT_KETA );

            // [タイトル部1],[タイトル部2],[タイトル部3],[...4],[...5],[タイトル部6]
            // (日本語)
            k = 0;
    		for( i = 0; i < iTITLE_Cnt; i++){
        		if( Clb2_CHK_TITLE->Checked[i] == true ){
            		sBuf = sTITLE_JPN->Strings[i];
                    if( k == 0 )	fprintf( stream, "\"%s\"", sBuf.c_str() );
                    else        	fprintf( stream,",\"%s\"", sBuf.c_str() );
                    k++;
                }
            }
    		for( i = k; i < 6; i++){
                fprintf( stream,"," );
            }
            fprintf( stream,"\n" );

            // [タイトル部1],[タイトル部2],[タイトル部3],[...4],[...5],[タイトル部6]
            // (英語)
            k = 0;
    		for( i = 0; i < iTITLE_Cnt; i++){
        		if( Clb2_CHK_TITLE->Checked[i] == true ){
            		sBuf = sTITLE_ENG->Strings[i];
                    if( k == 0 )	fprintf( stream, "\"%s\"", sBuf.c_str() );
                    else        	fprintf( stream,",\"%s\"", sBuf.c_str() );
                    k++;
                }
            }
    		for( i = k; i < 6; i++){
                fprintf( stream,"," );
            }
            fprintf( stream,"\n" );

          	// [タイトル部1],[タイトル部2],[タイトル部3],[...4],[...5],[タイトル部6]
            if( PgCtr2_tst1_Edt1->Tag == 4 )	sBuf1 = "";
            else								sBuf1 = PgCtr2_tst1_Edt1->Text;
            if( PgCtr2_tst1_Edt2->Tag == 4 )	sBuf2 = "";
            else								sBuf2 = PgCtr2_tst1_Edt2->Text;
            if( PgCtr2_tst1_Edt3->Tag == 4 )	sBuf3 = "";
            else								sBuf3 = PgCtr2_tst1_Edt3->Text;
            if( PgCtr2_tst1_Edt4->Tag == 4 )	sBuf4 = "";
            else								sBuf4 = PgCtr2_tst1_Edt4->Text;
            if( PgCtr2_tst1_Edt5->Tag == 4 )	sBuf5 = "";
            else								sBuf5 = PgCtr2_tst1_Edt5->Text;
            if( PgCtr2_tst1_Edt6->Tag == 4 )	sBuf6 = "";
            else								sBuf6 = PgCtr2_tst1_Edt6->Text;
			fprintf( stream,"\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\n",
            										sBuf1.c_str(),
												    sBuf2.c_str(),
												    sBuf3.c_str(),
												    sBuf4.c_str(),
												    sBuf5.c_str(),
												    sBuf6.c_str());

            // 備考（改行コードを[CR+LF]に変換します）
            sBuf = "";
    		for( i = 0; i < Memo2_CHK_REMARK->Lines->Count; i++){
            	sBuf = sBuf + Memo2_CHK_REMARK->Lines->Strings[i];
            	sBuf = sBuf + "[CR+LF]";
            }
			fprintf( stream,"%s\n", sBuf.c_str() );

            // ロット数
            k = 0;
    		for( i = 0; i < Clb2_CHK_LOT->Items->Count; i++){
        		if( Clb2_CHK_LOT->Checked[i] == true )	k++;
            }
			fprintf( stream,"%d\n", k );

            // 区切り
			fprintf( stream,"@@@出力項目@@@\n" );

			// 指定ロット数分出力します
			for( i = 0; i < Clb2_CHK_LOT->Items->Count; i++){
				if( Clb2_CHK_LOT->Checked[i] == true ){

					// 出力対象のロットを取得します
					sLOTNO = Clb2_CHK_LOT->Items->Strings[i];

					// 選択されている項目だけ出力対象と判断します
					for( m = 0; m < Clb2_CHK_KOUMOKU->Items->Count; m++){
						if( Clb2_CHK_KOUMOKU->Checked[m] == true ){

							// 2003/10/21 A.Tamura
							// 対象ロットの出力したい測定項目が対象ロットに無かった場合、他のロットに有るはずの測定項目から
							// 測定項目名、規格などを取得し、ダミー行（CSV）を出力する為のループ
							// このループが２回目の時は、それに該当する
							for( k = 0; k < 2; k++ ){
								
								Query2->FindFirst();
								while(Query2->Eof == false) {

									sBuf = Query2->FieldValues["LOTNO"];

									// 該当のロットＮｏを処理します
									// 2003/10/21 A.Tamura このループが２回目の時は、ダミー行（CSV）を出力処理
									if( sLOTNO == sBuf || k == 1 ){

										// 測定項目として出力します。
										iSKB_NO = AnsiString(Query2->FieldValues["SKB_NO"]).ToIntDef(9);
										if( iSKB_NO != 9 ){

											// 対象レコードの測定項目を取得します。
											sBuf = "";
											if( !VarIsNull(Query2->FieldValues["KOMK_NM"]) ){
												sBuf = Query2->FieldValues["KOMK_NM"];
											}
											if( !VarIsNull(Query2->FieldValues["KOMK_SUB"]) ){
												sBuf = sBuf + " " + Query2->FieldValues["KOMK_SUB"];
											}
											// 2003/10/21 A.Tamura [単位]も含めて選択条件に入れる。
											if( !VarIsNull(Query2->FieldValues["TANI"]) ){
												sBuf = sBuf + " " + Query2->FieldValues["TANI"];
											}
											if( sBuf != "" ){
												// 対象レコードが選択されている測定項目と同じかどうか判断します。
												if( Clb2_CHK_KOUMOKU->Items->Strings[m] == sBuf ){
													
													// 該当レコードあり
													if( k == 0 )	k = 2;

													// 出力項目（測定項目行）を書き込みます
													bOKFlag = true;	//2003/07/22 E.Takase
													fprintf( stream, "%s,%d,",
																		sLOTNO.c_str(),
																		iSKB_NO );
													fprintf( stream, "\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",",
																		Null_S(Query2->FieldValues["KOMK_NM"]).c_str(),
																		Null_S(Query2->FieldValues["KOMK_ENG"]).c_str(),
																		Null_S(Query2->FieldValues["KOMK_SUB"]).c_str(),
																		Null_S(Query2->FieldValues["KOMK_SUB_ENG"]).c_str(),
																		AnsiString(Query2->FieldValues["KIKI_NO"]).ToIntDef(0),
																		Null_S(Query2->FieldValues["KIKI_NM"]).c_str(),
																		Null_S(Query2->FieldValues["TANI"]).c_str() );
													dVal1 = Query2->FieldValues["KIKA_NUM1"];
													dVal2 = Query2->FieldValues["KIKA_NUM2"];
													dVal3 = Query2->FieldValues["KIKA_NUM3"];
													if( iSKB_NO == 2 && AnsiString(Query2->FieldValues["KOMK_NO"]).ToIntDef(0) == 1 ){
														sBuf = " ";
													}
													else {
														sBuf = Null_S(Query2->FieldValues["KIKA_STR"]).c_str();
													}
													fprintf( stream, "%d,%d,%d,%f,%f,%f,%s,",
																		AnsiString(Query2->FieldValues["KIKA_TYPE"]).ToIntDef(1),
																		AnsiString(Query2->FieldValues["KIKA_KIND"]).ToIntDef(1),
																		AnsiString(Query2->FieldValues["KIKA_DECI"]).ToIntDef(0),
																		dVal1,
																		dVal2,
																		dVal3,
																		sBuf );

													fprintf( stream, "%d,%d,%d,",
																		AnsiString(Query2->FieldValues["KIKA_PRT"]).ToIntDef(0),
																		AnsiString(Query2->FieldValues["VALUE_TYPE"]).ToIntDef(0),
																		AnsiString(Query2->FieldValues["VALUE_DECI"]).ToIntDef(0) );

													// 測定項目の有無			2003/08/28 A.Tamura
													// 2003/10/21 A.Tamura このループが２回目の時は、ダミー行（CSV）を出力処理
													if( Query2->FieldValues["SOKU_FLG"] == 0 || k == 1 ){
														// 「測定しない」の時

                                                        // 前ロットから同じ値を引継ぎ（取得）します
                                                        //2003/10/22 E.Takase 検索条件に単位追加
														//iBuf = GetBeforeLotVal(
														//			Null_S(Query2->FieldValues["DTKSHIN"]),
														//			sLOTNO,
														//			Null_S(Query2->FieldValues["KOMK_NM"]),
														//			Null_S(Query2->FieldValues["KOMK_SUB"]),
														//			Null_S(Query2->FieldValues["HINBAN_SK"]),
														//			atoi(Null_S(Query2->FieldValues["KIKI_NO"]).c_str()),
														//			atoi(Null_S(Query2->FieldValues["KOMK_NO"]).c_str()),
														//			&sReSOKU_SU, &sReKIKA_PRT, &sReVALUE_TYPE,
														//			&sReVALUE_DECI, &sReDISP_VAL_SU, &sReDISP_VAL_AVE,
														//			&sReDISP_VAL_MAX, &sReDISP_VAL_MIN, &sReDISP_OK, sReDISP_VAL );
														iBuf = GetBeforeLotVal(
																	Null_S(Query2->FieldValues["DTKSHIN"]),
																	sLOTNO,
																	Null_S(Query2->FieldValues["KOMK_NM"]),
																	Null_S(Query2->FieldValues["KOMK_SUB"]),
																	Null_S(Query2->FieldValues["HINBAN_SK"]),
																	atoi(Null_S(Query2->FieldValues["KIKI_NO"]).c_str()),
																	atoi(Null_S(Query2->FieldValues["KOMK_NO"]).c_str()),
																	Null_S(Query2->FieldValues["TANI"]),
																	&sReSOKU_SU, &sReKIKA_PRT, &sReVALUE_TYPE,
																	&sReVALUE_DECI, &sReDISP_VAL_SU, &sReDISP_VAL_AVE,
																	&sReDISP_VAL_MAX, &sReDISP_VAL_MIN, &sReDISP_OK, sReDISP_VAL );
														iReDISP_VAL_SU = sReDISP_VAL_SU.ToIntDef(0);
                                                        // 2003/11/5 A.Tamura 履歴の該当ロットが見つからない時、DISP_VAL_SUは、出力ロットのSOKU_SUをします
                                                        if( iBuf < 0 ){
                                                        	sReDISP_VAL_SU = AnsiString(Query2->FieldValues["SOKU_SU"]);
                                                        	iReDISP_VAL_SU = 0;
                                                        }

														// 測定数、平均値、最大値、最小値
                                                        //2003/11/26 E.Takase
														//fprintf( stream, "%s,%s,%s,%s,",
														fprintf( stream, "%s,%s,%s,%s",
																			sReDISP_VAL_SU,
																			sReDISP_VAL_AVE,
																			sReDISP_VAL_MAX,
																			sReDISP_VAL_MIN);

														// 測定値1〜の値設定
														for( p = 0; p < iReDISP_VAL_SU; p++){
															fprintf( stream, ",%s", sReDISP_VAL->Strings[p].c_str() );
														}

														// 測定値が10に満たない場合は空白を設定
														for( p = iReDISP_VAL_SU; p < 10; p++){
															fprintf( stream, ",%s", " " );
														}

													}
													else {
														// 「測定する」の時

														// 測定数、平均値、最大値、最小値
														dVal1 = Query2->FieldValues["DISP_VAL_AVE"];
														dVal2 = Query2->FieldValues["DISP_VAL_MAX"];
														dVal3 = Query2->FieldValues["DISP_VAL_MIN"];
														fprintf( stream, "%d,%f,%f,%f,",
																			AnsiString(Query2->FieldValues["DISP_VAL_SU"]).ToIntDef(0),
																			dVal1,
																			dVal2,
																			dVal3 );

														// 測定値1〜10の値設定
														fprintf( stream, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
																			Null_S(Query2->FieldValues["DISP_VAL01"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL02"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL03"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL04"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL05"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL06"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL07"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL08"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL09"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL10"]).c_str() );

														// 測定値11〜の値設定
														if( AnsiString(Query2->FieldValues["DISP_VAL_SU"]).ToIntDef(0) > 10 ){
															sBuf = "SELECT * FROM KSD03";
															sBuf += " WHERE DTKSHIN ='" + sDTKSHIN + "'";
															sBuf += " AND LOTNO = '" + sLOTNO + "'";
															sBuf += " AND UNQ_NO = " + AnsiString(Query2->FieldValues["UNQ_NO"]);
															sBuf += " ORDER BY SOKU_NO";

															// Initial Query
															Query3->Close();
															Query3->SQL->Clear();
															Query3->SQL->Add(sBuf);
															Query3->Open();
															Query3->Active = true;
															while(Query3->Eof == false) {
																fprintf( stream, ",%s",
																			Null_S(Query3->FieldValues["DISP_VAL"]).c_str() );
																Query3->Next();
															}
														}
													}
													fprintf( stream, "\n" );
													
													break;
												}
											}
										}
									}
									Query2->Next();
									
								}	// While
							}
						}
					}	// for m end
				}
			}	// for i end
		}

	    // ファイルを閉じる
    	fclose(stream);

    }


    //--------------------------------------------------------------------------------------------
    // 材料証明書指示ファイルの作成
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet3" ){

    	// 出力内容の確認が押されていない場合は、自動実行します
    	if( iNowTab != 3 ){
			Btn1_OUT_CHECKClick(Btn3_OUT_CHECK);
			if( ret_Btn1_OUT_CHECKClick == false ) return;
    	}

    	if( (stream = fopen( sRepData3, "w+" )) != NULL ){
    		// 正常にファイルをオープンできた場合

			// [印刷の形式(0=印刷して自動終了/1=Excel終了しない、印刷なし）],
            // [品番],
            // [社名],
            // [出力形式(0=日本語/1=英語)],
            // [Xの出力(0=しない/1=する)]
            if( Rdo3_WHR_FORMAT_JPN->Checked == true )		iEnglish = 0;
            else											iEnglish = 1;
            if( Rdo3_CHK_X_ON->Checked == true )			iX_OUT = 1;
            else											iX_OUT = 0;
			fprintf( stream,"%d,%s,\"%s\",%d,%d\n",
            								iAutoType,
											Edt3_WHR_DTKSHIN->Text.c_str(),
											Edt3_CHK_CUSTOMER->Text.c_str(),
                                            iEnglish,
                                            iX_OUT );

            // [タイトル部1],[タイトル部2],[タイトル部3],[...4],[...5],[...6],[...7],[タイトル部8]
            // (日本語)
            k = 0;
    		for( i = 0; i < iTITLE_Cnt; i++){
        		if( Clb3_CHK_TITLE->Checked[i] == true ){
            		sBuf = sTITLE_JPN->Strings[i];
                    if( k == 0 )	fprintf( stream, "\"%s\"", sBuf.c_str() );
                    else        	fprintf( stream,",\"%s\"", sBuf.c_str() );
                    k++;
                }
            }
    		for( i = k; i < 8; i++){
                fprintf( stream,"," );
            }
            fprintf( stream,"\n" );

            // [タイトル部1],[タイトル部2],[タイトル部3],[...4],[...5],[...6],[...7],[タイトル部8]
            // (英語)
            k = 0;
    		for( i = 0; i < iTITLE_Cnt; i++){
        		if( Clb3_CHK_TITLE->Checked[i] == true ){
            		sBuf = sTITLE_ENG->Strings[i];
                    if( k == 0 )	fprintf( stream, "\"%s\"", sBuf.c_str() );
                    else        	fprintf( stream,",\"%s\"", sBuf.c_str() );
                    k++;
                }
            }
    		for( i = k; i < 8; i++){
                fprintf( stream,"," );
            }
            fprintf( stream,"\n" );

            // 備考（改行コードを[CR+LF]に変換します）
            sBuf = "";
    		for( i = 0; i < Memo3_CHK_REMARK->Lines->Count; i++){
            	sBuf = sBuf + Memo3_CHK_REMARK->Lines->Strings[i];
            	sBuf = sBuf + "[CR+LF]";
            }
			fprintf( stream,"%s\n", sBuf.c_str() );

            // ロット数
			fprintf( stream,"%d\n", PgCtr3_LOT->Tag );

          	// [ロットNo1],[タイトル部1],[タイトル部2],[タイトル部3],[...4],[...5],[...6],[...7],[タイトル部8]
            // 指定ロット数分出力します
    		for( i = 0; i < PgCtr3_LOT->Tag; i++){

                if( i == 0 ){
                	// 1ロット目
					sLOTNO = PgCtr3_tst01->Caption.Trim();

                    if( PgCtr3_tst1_Edt1->Tag == 4 )	sBuf1 = GetTitleLotNo( i );
                    else								sBuf1 = PgCtr3_tst1_Edt1->Text;
                    if( PgCtr3_tst1_Edt2->Tag == 4 )	sBuf2 = GetTitleLotNo( i );
                    else								sBuf2 = PgCtr3_tst1_Edt2->Text;
                    if( PgCtr3_tst1_Edt3->Tag == 4 )	sBuf3 = GetTitleLotNo( i );
                    else								sBuf3 = PgCtr3_tst1_Edt3->Text;
                    if( PgCtr3_tst1_Edt4->Tag == 4 )	sBuf4 = GetTitleLotNo( i );
                    else								sBuf4 = PgCtr3_tst1_Edt4->Text;
                    if( PgCtr3_tst1_Edt5->Tag == 4 )	sBuf5 = GetTitleLotNo( i );
                    else								sBuf5 = PgCtr3_tst1_Edt5->Text;
                    if( PgCtr3_tst1_Edt6->Tag == 4 )	sBuf6 = GetTitleLotNo( i );
                    else								sBuf6 = PgCtr3_tst1_Edt6->Text;
                    if( PgCtr3_tst1_Edt7->Tag == 4 )	sBuf7 = GetTitleLotNo( i );
                    else								sBuf7 = PgCtr3_tst1_Edt7->Text;
                    if( PgCtr3_tst1_Edt8->Tag == 4 )	sBuf8 = GetTitleLotNo( i );
                    else								sBuf8 = PgCtr3_tst1_Edt8->Text;
                }
                else {
                	// 2ロット目以降
					sLOTNO = PgCtr3_tst[i+1]->Caption.Trim();

                   	if( PgCtr3_tst1_Edt1->Tag == 4 )	sBuf1 = GetTitleLotNo( i+1 );
                   	else								sBuf1 = PgCtr3_tst_Edt[i+1][0]->Text;
                   	if( PgCtr3_tst1_Edt2->Tag == 4 )	sBuf2 = GetTitleLotNo( i+1 );
                   	else								sBuf2 = PgCtr3_tst_Edt[i+1][1]->Text;
                   	if( PgCtr3_tst1_Edt3->Tag == 4 )	sBuf3 = GetTitleLotNo( i+1 );
                   	else								sBuf3 = PgCtr3_tst_Edt[i+1][2]->Text;
                   	if( PgCtr3_tst1_Edt4->Tag == 4 )	sBuf4 = GetTitleLotNo( i+1 );
                   	else								sBuf4 = PgCtr3_tst_Edt[i+1][3]->Text;
                   	if( PgCtr3_tst1_Edt5->Tag == 4 )	sBuf5 = GetTitleLotNo( i+1 );
                   	else								sBuf5 = PgCtr3_tst_Edt[i+1][4]->Text;
                   	if( PgCtr3_tst1_Edt6->Tag == 4 )	sBuf6 = GetTitleLotNo( i+1 );
                   	else								sBuf6 = PgCtr3_tst_Edt[i+1][5]->Text;
                   	if( PgCtr3_tst1_Edt7->Tag == 4 )	sBuf7 = GetTitleLotNo( i+1 );
                   	else								sBuf7 = PgCtr3_tst_Edt[i+1][6]->Text;
                   	if( PgCtr3_tst1_Edt8->Tag == 4 )	sBuf8 = GetTitleLotNo( i+1 );
                   	else								sBuf8 = PgCtr3_tst_Edt[i+1][7]->Text;
                }

				fprintf( stream,"%s,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\n",
                												sLOTNO.c_str(),
																sBuf1.c_str(),
																sBuf2.c_str(),
																sBuf3.c_str(),
																sBuf4.c_str(),
																sBuf5.c_str(),
																sBuf6.c_str(),
																sBuf7.c_str(),
																sBuf8.c_str());
            }

            // 区切り
			fprintf( stream,"@@@出力項目@@@\n" );

          	// [ロットNo1],[タイトル部1],[タイトル部2],[タイトル部3],[...4],[...5],[...6],[...7],[タイトル部8]
            // 指定ロット数分出力します
    		for( i = 0; i < PgCtr3_LOT->Tag; i++){

				if( i == 0 ){
					sLOTNO = PgCtr3_tst01->Caption.Trim();
				}
				else {
					sLOTNO = PgCtr3_tst[i+1]->Caption.Trim();
				}

				Query2->FindFirst();
				while(Query2->Eof == false) {

					sBuf = Query2->FieldValues["LOTNO"];

                    // 該当のロットＮｏを処理します
                    if( sLOTNO == sBuf ){

						// 測定項目として出力します。
						iSKB_NO = AnsiString(Query2->FieldValues["SKB_NO"]).ToIntDef(9);
						if( iSKB_NO != 9 ){

							sBuf = "";
							if( !VarIsNull(Query2->FieldValues["KOMK_NM"]) ){
								sBuf = Query2->FieldValues["KOMK_NM"];
							}
							if( !VarIsNull(Query2->FieldValues["KOMK_SUB"]) ){
								sBuf = sBuf + " " + Query2->FieldValues["KOMK_SUB"];
							}
							// 2003/10/21 A.Tamura [単位]も含めて選択条件に入れる。
							if( !VarIsNull(Query2->FieldValues["TANI"]) ){
								sBuf = sBuf + " " + Query2->FieldValues["TANI"];
							}
							if( sBuf != "" ){

								// 選択されている項目だけ出力対象と判断します
                                k = 0;
								for( m = 0; m < Clb3_CHK_KOUMOKU->Items->Count; m++){
									if( Clb3_CHK_KOUMOKU->Items->Strings[m] == sBuf ){
                                        if( Clb3_CHK_KOUMOKU->Checked[m] == true ){
											k = 1;
										}
                                        break;
									}
								}
								if( k == 1 ){
									// 出力項目（測定項目行）を書き込みます
                                    bOKFlag = true;	//2003/07/22 E.Takase
									fprintf( stream, "%s,%d,",
                                    	                sLOTNO.c_str(),
                                                        iSKB_NO );
                                    fprintf( stream, "\"%s\",\"%s\",\"%s\",\"%s\",%d,%s,%s,",
                                    					Null_S(Query2->FieldValues["KOMK_NM"]).c_str(),
                                                        Null_S(Query2->FieldValues["KOMK_ENG"]).c_str(),
                                                        Null_S(Query2->FieldValues["KOMK_SUB"]).c_str(),
                                                        Null_S(Query2->FieldValues["KOMK_SUB_ENG"]).c_str(),
                                                        AnsiString(Query2->FieldValues["KIKI_NO"]).ToIntDef(0),
                                                        Null_S(Query2->FieldValues["KIKI_NM"]).c_str(),
                                                        Null_S(Query2->FieldValues["TANI"]).c_str() );
                                    dVal1 = Query2->FieldValues["KIKA_NUM1"];
                                    dVal2 = Query2->FieldValues["KIKA_NUM2"];
                                    dVal3 = Query2->FieldValues["KIKA_NUM3"];
                                    fprintf( stream, "%d,%d,%d,%f,%f,%f,%s,",
                                    					AnsiString(Query2->FieldValues["KIKA_TYPE"]).ToIntDef(1),
                                    					AnsiString(Query2->FieldValues["KIKA_KIND"]).ToIntDef(1),
                                    					AnsiString(Query2->FieldValues["KIKA_DECI"]).ToIntDef(0),
                                    					dVal1,
                                    					dVal2,
                                    					dVal3,
                                                        Null_S(Query2->FieldValues["KIKA_STR"]).c_str() );

                                    fprintf( stream, "%d,%d,%d,",
                                       					AnsiString(Query2->FieldValues["KIKA_PRT"]).ToIntDef(0),
                                       					AnsiString(Query2->FieldValues["VALUE_TYPE"]).ToIntDef(0),
                                       					AnsiString(Query2->FieldValues["VALUE_DECI"]).ToIntDef(0) );

                                    // 測定項目の有無			2003/08/28 A.Tamura
                                    if( Query2->FieldValues["SOKU_FLG"] == 0 ){
                                    	// 「測定しない」の時

                                        //2003/10/22 E.Takase 検索条件に単位追加
				                  		//iBuf = GetBeforeLotVal(
                                        //			Null_S(Query2->FieldValues["DTKSHIN"]),
                                        //            Null_S(Query2->FieldValues["LOTNO"]),
					                	//            Null_S(Query2->FieldValues["KOMK_NM"]),
                                    	//			Null_S(Query2->FieldValues["KOMK_SUB"]),
                                    	//			Null_S(Query2->FieldValues["HINBAN_SK"]),
                                    	//			atoi(Null_S(Query2->FieldValues["KIKI_NO"]).c_str()),
                                    	//			atoi(Null_S(Query2->FieldValues["KOMK_NO"]).c_str()),
                                		//			&sReSOKU_SU, &sReKIKA_PRT, &sReVALUE_TYPE,
                                    	//			&sReVALUE_DECI, &sReDISP_VAL_SU, &sReDISP_VAL_AVE,
                                    	//			&sReDISP_VAL_MAX, &sReDISP_VAL_MIN, &sReDISP_OK, sReDISP_VAL );
				                  		iBuf = GetBeforeLotVal(
                                        			Null_S(Query2->FieldValues["DTKSHIN"]),
                                                    Null_S(Query2->FieldValues["LOTNO"]),
					                	            Null_S(Query2->FieldValues["KOMK_NM"]),
                                    				Null_S(Query2->FieldValues["KOMK_SUB"]),
                                    				Null_S(Query2->FieldValues["HINBAN_SK"]),
                                    				atoi(Null_S(Query2->FieldValues["KIKI_NO"]).c_str()),
                                    				atoi(Null_S(Query2->FieldValues["KOMK_NO"]).c_str()),
					                	            Null_S(Query2->FieldValues["TANI"]),
                                					&sReSOKU_SU, &sReKIKA_PRT, &sReVALUE_TYPE,
                                    				&sReVALUE_DECI, &sReDISP_VAL_SU, &sReDISP_VAL_AVE,
                                    				&sReDISP_VAL_MAX, &sReDISP_VAL_MIN, &sReDISP_OK, sReDISP_VAL );
                                    	iReDISP_VAL_SU = sReDISP_VAL_SU.ToIntDef(0);
                                        // 2003/11/5 A.Tamura 履歴の該当ロットが見つからない時、DISP_VAL_SUは、出力ロットのSOKU_SUをします
                                        if( iBuf < 0 ){
                                       		sReDISP_VAL_SU = AnsiString(Query2->FieldValues["SOKU_SU"]);
                                        	iReDISP_VAL_SU = 0;
                                        }

										// 測定数、平均値
                                        fprintf( stream, "%s,%s", sReDISP_VAL_SU, sReDISP_VAL_AVE );

                                        // 測定値1〜の値設定
										for( m = 0; m < iReDISP_VAL_SU; m++){
 										    fprintf( stream, ",%s", sReDISP_VAL->Strings[m].c_str() );
                                        }

                                        // 測定値が10に満たない場合は空白を設定
										for( m = iReDISP_VAL_SU; m < 10; m++){
 										    fprintf( stream, ",%s", " " );
                                        }

                                    }
                                    else {
                                    	// 「測定する」の時

										// 測定数、平均値
                                    	dVal1 = Query2->FieldValues["DISP_VAL_AVE"];
                                        fprintf( stream, "%d,%f,",
                                    					AnsiString(Query2->FieldValues["DISP_VAL_SU"]).ToIntDef(0),
                                    					dVal1 );

                                		// 測定値1〜10の値設定
		                                fprintf( stream, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
                                        				Null_S(Query2->FieldValues["DISP_VAL01"]).c_str(),
                                        				Null_S(Query2->FieldValues["DISP_VAL02"]).c_str(),
                                        				Null_S(Query2->FieldValues["DISP_VAL03"]).c_str(),
                                        				Null_S(Query2->FieldValues["DISP_VAL04"]).c_str(),
                                        				Null_S(Query2->FieldValues["DISP_VAL05"]).c_str(),
                                        				Null_S(Query2->FieldValues["DISP_VAL06"]).c_str(),
                                        				Null_S(Query2->FieldValues["DISP_VAL07"]).c_str(),
                                        				Null_S(Query2->FieldValues["DISP_VAL08"]).c_str(),
                                        				Null_S(Query2->FieldValues["DISP_VAL09"]).c_str(),
                                        				Null_S(Query2->FieldValues["DISP_VAL10"]).c_str() );

                                        // 測定値11〜の値設定
                                        if( AnsiString(Query2->FieldValues["DISP_VAL_SU"]).ToIntDef(0) > 10 ){
											sBuf = "SELECT * FROM KSD03";
											sBuf += " WHERE DTKSHIN ='" + Edt3_WHR_DTKSHIN->Text + "'";
											sBuf += " AND LOTNO = '" + sLOTNO + "'";
											sBuf += " AND UNQ_NO = " + AnsiString(Query2->FieldValues["UNQ_NO"]);
											sBuf += " ORDER BY SOKU_NO";

											// Initial Query
											Query3->Close();
											Query3->SQL->Clear();
											Query3->SQL->Add(sBuf);
											Query3->Open();
											Query3->Active = true;
 	 										while(Query3->Eof == false) {
			                                    fprintf( stream, ",%s",
                                                			Null_S(Query3->FieldValues["DISP_VAL"]).c_str() );
  	  											Query3->Next();
  	  										}
                                        }
                                    }

                                    fprintf( stream, "\n" );
                             	}
							}
						}
                        else {
							// 出力項目（空白行）を書き込みます
							fprintf( stream, "%s,%d,,,,,,,,,,,,,,,,,,,,0,0,,,,,,,,,,\n",
                            					sLOTNO.c_str(),	iSKB_NO);
                        }
					}
					Query2->Next();
				}
        	}
		}

	    // ファイルを閉じる
    	fclose(stream);

    }

    //--------------------------------------------------------------------------------------------
    // 材料証明書（月別）指示ファイルの作成
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet4" ){

    	// 出力内容の確認が押されていない場合は、自動実行します
    	if( iNowTab != 4 ){
			Btn1_OUT_CHECKClick(Btn4_OUT_CHECK);
			if( ret_Btn1_OUT_CHECKClick == false ) return;
    	}

    	if( (stream = fopen( sRepData4, "w+" )) != NULL ){
    		// 正常にファイルをオープンできた場合

			// [印刷の形式(0=印刷して自動終了/1=Excel終了しない、印刷なし）],
            // [品番],
            // [社名],
            // [納入月],
            // [出力形式(0=日本語/1=英語)],
            // [Xの出力(0=しない/1=する)]
            // [一行空けて出力(0=しない/1=する)]
            // [ロットＮｏの桁(4or5or6)]
            if( Rdo4_WHR_FORMAT_JPN->Checked == true )		iEnglish = 0;
            else											iEnglish = 1;
            if( Rdo4_CHK_X_ON->Checked == true )			iX_OUT = 1;
            else											iX_OUT = 0;
            if( Rdo4_WHR_BLANK_ON->Checked == true )		iBLANK = 1;
            else											iBLANK = 0;
            if( Rdo4_WHR_TYPE1->Checked == true )			sDTKSHIN = Edt4_WHR_DTKSHIN1->Text;
            else											sDTKSHIN = Edt4_WHR_DTKSHIN2->Text;
            if( Rdo4_LOT_KETA4->Checked == true ){			iLOT_KETA = 4;
            } else if( Rdo4_LOT_KETA5->Checked == true ){   iLOT_KETA = 5;
            } else {                                        iLOT_KETA = 6;
            }

			fprintf( stream,"%d,%s,\"%s\",\"%s\",%d,%d,%d,%d\n",
            								iAutoType,
											sDTKSHIN.c_str(),
											Edt4_CHK_CUSTOMER->Text.c_str(),
                                            Edt4_TITLE_MONTH->Text.c_str(),
                                            iEnglish,
                                            iX_OUT,
                                            iBLANK,
                                            iLOT_KETA );

            // [タイトル部1],[タイトル部2],[タイトル部3],[...4],[...5],[タイトル部6]
            // (日本語)
            k = 0;
    		for( i = 0; i < iTITLE_Cnt; i++){
        		if( Clb4_CHK_TITLE->Checked[i] == true ){
            		sBuf = sTITLE_JPN->Strings[i];
                    if( k == 0 )	fprintf( stream, "\"%s\"", sBuf.c_str() );
                    else        	fprintf( stream,",\"%s\"", sBuf.c_str() );
                    k++;
                }
            }
    		for( i = k; i < 6; i++){
                fprintf( stream,"," );
            }
            fprintf( stream,"\n" );

            // [タイトル部1],[タイトル部2],[タイトル部3],[...4],[...5],[タイトル部6]
            // (英語)
            k = 0;
    		for( i = 0; i < iTITLE_Cnt; i++){
        		if( Clb4_CHK_TITLE->Checked[i] == true ){
            		sBuf = sTITLE_ENG->Strings[i];
                    if( k == 0 )	fprintf( stream, "\"%s\"", sBuf.c_str() );
                    else        	fprintf( stream,",\"%s\"", sBuf.c_str() );
                    k++;
                }
            }
    		for( i = k; i < 6; i++){
                fprintf( stream,"," );
            }
            fprintf( stream,"\n" );

          	// [タイトル部1],[タイトル部2],[タイトル部3],[...4],[...5],[タイトル部6]
            if( PgCtr4_tst1_Edt1->Tag == 4 )	sBuf1 = "";
            else								sBuf1 = PgCtr4_tst1_Edt1->Text;
            if( PgCtr4_tst1_Edt2->Tag == 4 )	sBuf2 = "";
            else								sBuf2 = PgCtr4_tst1_Edt2->Text;
            if( PgCtr4_tst1_Edt3->Tag == 4 )	sBuf3 = "";
            else								sBuf3 = PgCtr4_tst1_Edt3->Text;
            if( PgCtr4_tst1_Edt4->Tag == 4 )	sBuf4 = "";
            else								sBuf4 = PgCtr4_tst1_Edt4->Text;
            if( PgCtr4_tst1_Edt5->Tag == 4 )	sBuf5 = "";
            else								sBuf5 = PgCtr4_tst1_Edt5->Text;
            if( PgCtr4_tst1_Edt6->Tag == 4 )	sBuf6 = "";
            else								sBuf6 = PgCtr4_tst1_Edt6->Text;
			fprintf( stream,"\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\n",
            										sBuf1.c_str(),
												    sBuf2.c_str(),
												    sBuf3.c_str(),
												    sBuf4.c_str(),
												    sBuf5.c_str(),
												    sBuf6.c_str());

            // 備考（改行コードを[CR+LF]に変換します）
            sBuf = "";
    		for( i = 0; i < Memo4_CHK_REMARK->Lines->Count; i++){
            	sBuf = sBuf + Memo4_CHK_REMARK->Lines->Strings[i];
            	sBuf = sBuf + "[CR+LF]";
            }
			fprintf( stream,"%s\n", sBuf.c_str() );

            // ロット数
            k = 0;
    		for( i = 0; i < Clb4_CHK_LOT->Items->Count; i++){
        		if( Clb4_CHK_LOT->Checked[i] == true )	k++;
            }
			fprintf( stream,"%d\n", k );

            // 区切り
			fprintf( stream,"@@@出力項目@@@\n" );

			// 指定ロット数分出力します
			for( i = 0; i < Clb2_CHK_LOT->Items->Count; i++){
				if( Clb2_CHK_LOT->Checked[i] == true ){

					// 出力対象のロットを取得します
					sLOTNO = Clb2_CHK_LOT->Items->Strings[i];

					// 選択されている項目だけ出力対象と判断します
					for( m = 0; m < Clb2_CHK_KOUMOKU->Items->Count; m++){
						if( Clb2_CHK_KOUMOKU->Checked[m] == true ){

							// 2003/10/21 A.Tamura
							// 対象ロットの出力したい測定項目が対象ロットに無かった場合、他のロットに有るはずの測定項目から
							// 測定項目名、規格などを取得し、ダミー行（CSV）を出力する為のループ
							// このループが２回目の時は、それに該当する
							for( k = 0; k < 2; k++ ){
								
								Query2->FindFirst();
								while(Query2->Eof == false) {

									sBuf = Query2->FieldValues["LOTNO"];

									// 該当のロットＮｏを処理します
									// 2003/10/21 A.Tamura このループが２回目の時は、ダミー行（CSV）を出力処理
									if( sLOTNO == sBuf || k == 1 ){

										// 測定項目として出力します。
										iSKB_NO = AnsiString(Query2->FieldValues["SKB_NO"]).ToIntDef(9);
										if( iSKB_NO != 9 ){

											// 対象レコードの測定項目を取得します。
											sBuf = "";
											if( !VarIsNull(Query2->FieldValues["KOMK_NM"]) ){
												sBuf = Query2->FieldValues["KOMK_NM"];
											}
											if( !VarIsNull(Query2->FieldValues["KOMK_SUB"]) ){
												sBuf = sBuf + " " + Query2->FieldValues["KOMK_SUB"];
											}
											// 2003/10/21 A.Tamura [単位]も含めて選択条件に入れる。
											if( !VarIsNull(Query2->FieldValues["TANI"]) ){
												sBuf = sBuf + " " + Query2->FieldValues["TANI"];
											}
											if( sBuf != "" ){
												// 対象レコードが選択されている測定項目と同じかどうか判断します。
												if( Clb2_CHK_KOUMOKU->Items->Strings[m] == sBuf ){
													
													// 該当レコードあり
													if( k == 0 )	k = 2;

													// 出力項目（測定項目行）を書き込みます
													bOKFlag = true;	//2003/07/22 E.Takase
													fprintf( stream, "%s,%d,",
																		sLOTNO.c_str(),
																		iSKB_NO );
													fprintf( stream, "\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",",
																		Null_S(Query2->FieldValues["KOMK_NM"]).c_str(),
																		Null_S(Query2->FieldValues["KOMK_ENG"]).c_str(),
																		Null_S(Query2->FieldValues["KOMK_SUB"]).c_str(),
																		Null_S(Query2->FieldValues["KOMK_SUB_ENG"]).c_str(),
																		AnsiString(Query2->FieldValues["KIKI_NO"]).ToIntDef(0),
																		Null_S(Query2->FieldValues["KIKI_NM"]).c_str(),
																		Null_S(Query2->FieldValues["TANI"]).c_str() );
													dVal1 = Query2->FieldValues["KIKA_NUM1"];
													dVal2 = Query2->FieldValues["KIKA_NUM2"];
													dVal3 = Query2->FieldValues["KIKA_NUM3"];
													if( iSKB_NO == 2 && AnsiString(Query2->FieldValues["KOMK_NO"]).ToIntDef(0) == 1 ){
														sBuf = " ";
													}
													else {
														sBuf = Null_S(Query2->FieldValues["KIKA_STR"]).c_str();
													}
													fprintf( stream, "%d,%d,%d,%f,%f,%f,%s,",
																		AnsiString(Query2->FieldValues["KIKA_TYPE"]).ToIntDef(1),
																		AnsiString(Query2->FieldValues["KIKA_KIND"]).ToIntDef(1),
																		AnsiString(Query2->FieldValues["KIKA_DECI"]).ToIntDef(0),
																		dVal1,
																		dVal2,
																		dVal3,
																		sBuf );

													fprintf( stream, "%d,%d,%d,",
																		AnsiString(Query2->FieldValues["KIKA_PRT"]).ToIntDef(0),
																		AnsiString(Query2->FieldValues["VALUE_TYPE"]).ToIntDef(0),
																		AnsiString(Query2->FieldValues["VALUE_DECI"]).ToIntDef(0) );

													// 測定項目の有無			2003/08/28 A.Tamura
													// 2003/10/21 A.Tamura このループが２回目の時は、ダミー行（CSV）を出力処理
													if( Query2->FieldValues["SOKU_FLG"] == 0 || k == 1 ){
														// 「測定しない」の時

                                                        // 前ロットから同じ値を引継ぎ（取得）します
                                                        //2003/10/22 E.Takase 検索条件に単位追加
														//iBuf = GetBeforeLotVal(
														//			Null_S(Query2->FieldValues["DTKSHIN"]),
														//			sLOTNO,
														//			Null_S(Query2->FieldValues["KOMK_NM"]),
														//			Null_S(Query2->FieldValues["KOMK_SUB"]),
														//			Null_S(Query2->FieldValues["HINBAN_SK"]),
														///			atoi(Null_S(Query2->FieldValues["KIKI_NO"]).c_str()),
														//			atoi(Null_S(Query2->FieldValues["KOMK_NO"]).c_str()),
														//			&sReSOKU_SU, &sReKIKA_PRT, &sReVALUE_TYPE,
														//	 		&sReVALUE_DECI, &sReDISP_VAL_SU, &sReDISP_VAL_AVE,
														//			&sReDISP_VAL_MAX, &sReDISP_VAL_MIN, &sReDISP_OK, sReDISP_VAL );
														iBuf = GetBeforeLotVal(
																	Null_S(Query2->FieldValues["DTKSHIN"]),
																	sLOTNO,
																	Null_S(Query2->FieldValues["KOMK_NM"]),
																	Null_S(Query2->FieldValues["KOMK_SUB"]),
																	Null_S(Query2->FieldValues["HINBAN_SK"]),
																	atoi(Null_S(Query2->FieldValues["KIKI_NO"]).c_str()),
																	atoi(Null_S(Query2->FieldValues["KOMK_NO"]).c_str()),
																	Null_S(Query2->FieldValues["TANI"]),
																	&sReSOKU_SU, &sReKIKA_PRT, &sReVALUE_TYPE,
																	&sReVALUE_DECI, &sReDISP_VAL_SU, &sReDISP_VAL_AVE,
																	&sReDISP_VAL_MAX, &sReDISP_VAL_MIN, &sReDISP_OK, sReDISP_VAL );
														iReDISP_VAL_SU = sReDISP_VAL_SU.ToIntDef(0);
                                                        // 2003/11/5 A.Tamura 履歴の該当ロットが見つからない時、DISP_VAL_SUは、出力ロットのSOKU_SUをします
                                                        if( iBuf < 0 ){
                                                        	sReDISP_VAL_SU = AnsiString(Query2->FieldValues["SOKU_SU"]);
                                                        	iReDISP_VAL_SU = 0;
                                                        }

														// 測定数、平均値、最大値、最小値
                                                        //2003/11/26 E.Takase
														//fprintf( stream, "%s,%s,%s,%s,",
														fprintf( stream, "%s,%s,%s,%s",
																			sReDISP_VAL_SU,
                                                                            sReDISP_VAL_AVE,
																			sReDISP_VAL_MAX,
																			sReDISP_VAL_MIN);

														// 測定値1〜の値設定
														for( p = 0; p < iReDISP_VAL_SU; p++){
															fprintf( stream, ",%s", sReDISP_VAL->Strings[p].c_str() );
														}

														// 測定値が10に満たない場合は空白を設定
														for( p = iReDISP_VAL_SU; p < 10; p++){
															fprintf( stream, ",%s", " " );
														}

													}
													else {
														// 「測定する」の時

														// 測定数、平均値、最大値、最小値
														dVal1 = Query2->FieldValues["DISP_VAL_AVE"];
														dVal2 = Query2->FieldValues["DISP_VAL_MAX"];
														dVal3 = Query2->FieldValues["DISP_VAL_MIN"];
														fprintf( stream, "%d,%f,%f,%f,",
																			AnsiString(Query2->FieldValues["DISP_VAL_SU"]).ToIntDef(0),
																			dVal1,
																			dVal2,
																			dVal3 );

														// 測定値1〜10の値設定
														fprintf( stream, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
																			Null_S(Query2->FieldValues["DISP_VAL01"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL02"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL03"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL04"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL05"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL06"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL07"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL08"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL09"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL10"]).c_str() );

														// 測定値11〜の値設定
														if( AnsiString(Query2->FieldValues["DISP_VAL_SU"]).ToIntDef(0) > 10 ){
															sBuf = "SELECT * FROM KSD03";
															sBuf += " WHERE DTKSHIN ='" + sDTKSHIN + "'";
															sBuf += " AND LOTNO = '" + sLOTNO + "'";
															sBuf += " AND UNQ_NO = " + AnsiString(Query2->FieldValues["UNQ_NO"]);
															sBuf += " ORDER BY SOKU_NO";

															// Initial Query
															Query3->Close();
															Query3->SQL->Clear();
															Query3->SQL->Add(sBuf);
															Query3->Open();
															Query3->Active = true;
															while(Query3->Eof == false) {
																fprintf( stream, ",%s",
																			Null_S(Query3->FieldValues["DISP_VAL"]).c_str() );
																Query3->Next();
															}
														}
													}
													fprintf( stream, "\n" );
													
													break;
												}
											}
										}
									}
									Query2->Next();
									
								}	// While
							}
						}
					}	// for m end
				}
			}	// for i end

		}

	    // ファイルを閉じる
    	fclose(stream);

    }

	//--------------------------------------------------------------------------------------------
	//2003.04.23 Takase
	// 検査結果時系列管理票データのファイルの作成
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet5" ){
    	// 出力内容の確認が押されていない場合は、自動実行します
    	if( iNowTab != 5 ){
			Btn1_OUT_CHECKClick(Btn5_OUT_CHECK);
			if( ret_Btn1_OUT_CHECKClick == false ) return;
    	}
        //2003/08/27 E.Takase
        //ロットNOの桁数を指定
        if ( Rdo5_LOT_KETA4->Checked == true ) {
        	iLOTNO_OUT_Length = 4;
        } else {
        	if ( Rdo5_LOT_KETA5->Checked == true ) {
        		iLOTNO_OUT_Length = 5;
        	} else {
        		iLOTNO_OUT_Length = 6;
        	}
        }
	    bOKFlag = CreateReportSub5(iAutoType);
	}

	//--------------------------------------------------------------------------------------------
	//2003.04.23 Takase
	//検査経歴表データのファイルの作成
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet6" ){
    	// 出力内容の確認が押されていない場合は、自動実行します
    	if( iNowTab != 6 ){
			Btn1_OUT_CHECKClick(Btn6_OUT_CHECK);
			if( ret_Btn1_OUT_CHECKClick == false ) return;
    	}
        //2003/08/27 E.Takase
        //ロットNOの桁数を指定
		iLOTNO_OUT_Length = 6;
	    bOKFlag = CreateReportSub6(iAutoType);
	}

    //2003/07/22 E.Takase
    if ( bOKFlag == false ) {
    	ShowMessage("検索結果0件でした。");
     	return;
    }

	//--------------------------------------------------------------------------------------------
	//2003.04.30 Takase
    //Excel起動
    //--------------------------------------------------------------------------------------------
    // 検査成績書指示 Excel起動
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet1" ){
	    // ファイルを更新用に開く
            //20170419 Y.Onishi 旧Ver検査成績書の出力に対応
            //strcpy(path,sRepExcel1);
            if (iX_OUT == 2) {
               //Cp,Cpkの出力選択時は新Verにて出力
               strcpy(path,sRepExcel7);
            }
            else {
               strcpy(path,sRepExcel1);
            }

	    retDLL = ShellExecute(NULL, "open", path, "", "", SW_HIDE);
	}

    //--------------------------------------------------------------------------------------------
    // 検査成績書（月別） Excel起動
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet2" ){
	    strcpy(path,sRepExcel2);
	    retDLL = ShellExecute(NULL, "open", path, "", "", SW_HIDE);
	}

    //--------------------------------------------------------------------------------------------
    // 材料証明書指示 Excel起動
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet3" ){
	    strcpy(path,sRepExcel3);
	    retDLL = ShellExecute(NULL, "open", path, "", "", SW_HIDE);
	}

    //--------------------------------------------------------------------------------------------
    // 材料証明書（月別） Excel起動
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet4" ){
	    strcpy(path,sRepExcel4);
	    retDLL = ShellExecute(NULL, "open", path, "", "", SW_HIDE);
	}


    //--------------------------------------------------------------------------------------------
    // 検査結果時系列管理票 Excel起動
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet5" ){
	    strcpy(path,sRepExcel5);
	    retDLL = ShellExecute(NULL, "open", path, "", "", SW_HIDE);
	}

	//--------------------------------------------------------------------------------------------
	//検査経歴表データのファイルの作成
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet6" ){
	    strcpy(path,sRepExcel6);
	    retDLL = ShellExecute(NULL, "open", path, "", "", SW_HIDE);
	}

	//--------------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------------

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：桁数調整後のロットNOを返します
//
//  機能説明
//    指定したロットのタブ内で選択されているロットの桁数指定を考慮したロットNoを返します
//
//  パラメタ説明
//    int iTabSheetNo	：対象のシートNO
//
//  戻り値
//    AnsiString		：桁数調整後のロットNO
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::GetTitleLotNo(int iTabSheetNo)
{

    int				iLen, iPos;
    AnsiString		sBuf;
    TTabSheet*		tst_LOTNO;
    TRadioButton*	rdo_LOT4;
    TRadioButton*	rdo_LOT5;


    if( PgCtr_REPORT->ActivePage->Name == "TabSheet1" ||
    	PgCtr_REPORT->ActivePage->Name == "TabSheet3" ){
		// 検査成績書
		// 材料証明書	のみ対象（処理続行）とします
    } else {
        sBuf = "";
    	return( sBuf );
    }


    if( iTabSheetNo == 0 ){

		if( PgCtr_REPORT->ActivePage->Name == "TabSheet1" ){
	        // 検査成績書
	        tst_LOTNO	= dynamic_cast<TTabSheet*>(PgCtr1_tst01);
	    	rdo_LOT4	= dynamic_cast<TRadioButton*>(PgCtr1_tst1_LOT4);
	    	rdo_LOT5	= dynamic_cast<TRadioButton*>(PgCtr1_tst1_LOT5);
		}
        else {
        	// 材料証明書
	        tst_LOTNO	= dynamic_cast<TTabSheet*>(PgCtr3_tst01);
	    	rdo_LOT4	= dynamic_cast<TRadioButton*>(PgCtr3_tst1_LOT4);
	    	rdo_LOT5	= dynamic_cast<TRadioButton*>(PgCtr3_tst1_LOT5);
	    }

		sBuf = tst_LOTNO->Caption.Trim();
        if( rdo_LOT4->Checked == true ){
        	// 右から４桁利用
	        iLen = sBuf.Length();
            iPos = iLen - 4;
            if( iPos > 0 ){
            	sBuf = sBuf.SubString( iPos + 1, 4 );
        	}
        }
        if( rdo_LOT5->Checked == true ){
        	// 右から５桁利用
	        iLen = sBuf.Length();
            iPos = iLen - 5;
            if( iPos > 0 ){
            	sBuf = sBuf.SubString( iPos + 1, 5 );
        	}
        }
        // フル６桁出力なので何もしなくてＯＫ
        //if( PgCtr1_tst1_LOT6->Checked == true ){
        //	// 右から６桁利用
        //
        //}
    } else{

		if( PgCtr_REPORT->ActivePage->Name == "TabSheet1" ){
	        // 検査成績書
	        tst_LOTNO	= dynamic_cast<TTabSheet*>(PgCtr1_tst[iTabSheetNo]);
	    	rdo_LOT4	= dynamic_cast<TRadioButton*>(PgCtr1_tst_LOT[iTabSheetNo][0]);
	    	rdo_LOT5	= dynamic_cast<TRadioButton*>(PgCtr1_tst_LOT[iTabSheetNo][1]);
		}
        else {
        	// 材料証明書
	        tst_LOTNO	= dynamic_cast<TTabSheet*>(PgCtr3_tst[iTabSheetNo]);
	    	rdo_LOT4	= dynamic_cast<TRadioButton*>(PgCtr3_tst_LOT[iTabSheetNo][0]);
	    	rdo_LOT5	= dynamic_cast<TRadioButton*>(PgCtr3_tst_LOT[iTabSheetNo][1]);
	    }

        sBuf = tst_LOTNO->Caption.Trim();
        if( rdo_LOT4->Checked == true ){
        	// 右から４桁利用
	        iLen = sBuf.Length();
            iPos = iLen - 4;
            if( iPos > 0 ){
            	sBuf = sBuf.SubString( iPos + 1, 4 );
        	}
        }
        if( rdo_LOT5->Checked == true ){
        	// 右から５桁利用
	        iLen = sBuf.Length();
            iPos = iLen - 5;
            if( iPos > 0 ){
            	sBuf = sBuf.SubString( iPos + 1, 5 );
        	}
        }
        // フル６桁出力なので何もしなくてＯＫ
        //if( PgCtr1_tst_LOT[iTabSheetNo+1][2]->Checked == true ){
        //	// 右から６桁利用
        //
        //}
    }

    return( sBuf );

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：Variant型のNULLをブランクに変換します
//
//  機能説明
//    Variant型の値がNullならAnsiString型のブランクを返します。
//    Null出ないときはAnsiString型の文字列をそのまま返します。
//
//  パラメタ説明
//    int iTabSheetNo	：対象のシートNO
//
//  戻り値
//    AnsiString		：桁数調整後のロットNO
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::Null_S(Variant &vBuf)
{
	AnsiString sBuf;

	if ( vBuf.IsNull() ) {
		sBuf = " ";
	} else {
		sBuf = VarToStr(vBuf);
	}
    if ( Trim(sBuf) == "" ) {
        sBuf = " ";
    }
	return ( sBuf );

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
void __fastcall TForm1::ExtractCode_Report(AnsiString str)
{
    int i,n1,m,strlen;

    //初期化
    USER_COD = 0;
    USER_NAM = "";
    BUMO_COD = "";
    BUMO_NAM = "";
    AUTO_DTKSHIN = "";
    AUTO_LOTNO = "";

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
                    case 5:
                    //得意先品番
                        AUTO_DTKSHIN = str.SubString(n1,i - n1);
                    //ロットNo
                        AUTO_LOTNO = str.SubString(i + 1, strlen - i);
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

    if( AUTO_DTKSHIN != "" ){
    	Edt1_WHR_DTKSHIN->Text	= AUTO_DTKSHIN;
    	Edt2_WHR_DTKSHIN1->Text	= AUTO_DTKSHIN;
    	Edt2_WHR_DTKSHIN2->Text	= AUTO_DTKSHIN;
    	Edt3_WHR_DTKSHIN->Text	= AUTO_DTKSHIN;
    	Edt4_WHR_DTKSHIN1->Text	= AUTO_DTKSHIN;
    	Edt4_WHR_DTKSHIN2->Text	= AUTO_DTKSHIN;
    	Edt5_WHR_DTKSHIN1->Text	= AUTO_DTKSHIN;
    	Edt6_WHR_DTKSHIN1->Text	= AUTO_DTKSHIN;
    }
    if( AUTO_LOTNO != "" ){
    	Edt1_WHR_LOTNO->Text	= AUTO_LOTNO;
    	Edt2_WHR_LOTNO1->Text	= AUTO_LOTNO;
    	Edt3_WHR_LOTNO->Text	= AUTO_LOTNO;
    	Edt4_WHR_LOTNO1->Text	= AUTO_LOTNO;
    	Edt5_WHR_LOTNO->Text	= AUTO_LOTNO;
    	Edt6_WHR_LOTNO1->Text	= AUTO_LOTNO;
    }

}

//---------------------------------------------------------------------------
//
//  概要
//    OnEnterイベント	：各コントロールがフォーカス取得したとき
//
//  機能説明
//    「F1：一覧検索」ボタンの有効／無効を設定します
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
    if( BtnF01->Focused() )		return;

    // 「検査成績書」得意先品番にフォーカスが有る場合
    if( Edt1_WHR_DTKSHIN->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 1;
        return;
    }

    // 「検査成績書」ロットにフォーカスが有る場合
    if( Edt1_WHR_LOTNO->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 2;
        return;
    }

    // 「検査成績書」社名にフォーカスが有る場合
    if( Edt1_CHK_CUSTOMER->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        if( Rdo1_WHR_FORMAT_JPN->Checked )	BtnF01->Tag = 21;
        else                                BtnF01->Tag = 22;
        return;
    }

    // 「検査成績書(月別)」得意先品番（上）にフォーカスが有る場合
    if( Edt2_WHR_DTKSHIN1->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 3;
        return;
    }

    // 「検査成績書(月別)」ロットにフォーカスが有る場合
    if( Edt2_WHR_LOTNO1->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 4;
        return;
    }

    // 「検査成績書(月別)」得意先品番（下）にフォーカスが有る場合
    if( Edt2_WHR_DTKSHIN2->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 5;
        return;
    }

    // 「検査成績書(月別)」出荷日（自）にフォーカスが有る場合
    if( Edt2_WHR_SYUKADATE1->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 6;
        return;
    }

    // 「検査成績書(月別)」出荷日（至）にフォーカスが有る場合
    if( Edt2_WHR_SYUKADATE2->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 7;
        return;
    }

    // 「検査成績書(月別)」社名にフォーカスが有る場合
    if( Edt2_CHK_CUSTOMER->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        if( Rdo2_WHR_FORMAT_JPN->Checked )	BtnF01->Tag = 23;
        else                                BtnF01->Tag = 24;
        return;
    }

    // 「材料証明書」得意先品番にフォーカスが有る場合
    if( Edt3_WHR_DTKSHIN->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 8;
        return;
    }

    // 「材料証明書」ロットにフォーカスが有る場合
    if( Edt3_WHR_LOTNO->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 9;
        return;
    }

    // 「材料証明書」社名にフォーカスが有る場合
    if( Edt3_CHK_CUSTOMER->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        if( Rdo3_WHR_FORMAT_JPN->Checked )	BtnF01->Tag = 25;
        else                                BtnF01->Tag = 26;
        return;
    }

    // 「材料証明書(月別)」得意先品番（上）にフォーカスが有る場合
    if( Edt4_WHR_DTKSHIN1->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 10;
        return;
    }

    // 「材料証明書(月別)」ロットにフォーカスが有る場合
    if( Edt4_WHR_LOTNO1->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 11;
        return;
    }

    // 「材料証明書(月別)」得意先品番（下）にフォーカスが有る場合
    if( Edt4_WHR_DTKSHIN2->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 12;
        return;
    }

    // 「材料証明書(月別)」出荷日（自）にフォーカスが有る場合
    if( Edt4_WHR_SYUKADATE1->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 13;
        return;
    }

    // 「材料証明書(月別)」出荷日（至）にフォーカスが有る場合
    if( Edt4_WHR_SYUKADATE2->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 14;
        return;
    }

    // 「材料証明書(月別)」社名にフォーカスが有る場合
    if( Edt4_CHK_CUSTOMER->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        if( Rdo4_WHR_FORMAT_JPN->Checked )	BtnF01->Tag = 27;
        else                                BtnF01->Tag = 28;
        return;
    }

    // 「検査結果時系列管理表」得意先品番にフォーカスが有る場合
    if( Edt5_WHR_DTKSHIN1->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 15;
        return;
    }

    // 「検査結果時系列管理表」ロットにフォーカスが有る場合
    if( Edt5_WHR_LOTNO->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 16;
        return;
    }

    // 「検査結果時系列管理表」出荷日（自）にフォーカスが有る場合
    if( Edt5_WHR_SYUKADATE1->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 31;
        return;
    }

    // 「検査結果時系列管理表」出荷日（至）にフォーカスが有る場合
    if( Edt5_WHR_SYUKADATE2->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 32;
        return;
    }

    // 「検査結果時系列管理表」社名（日本語）にフォーカスが有る場合
    if( Edt5_CHK_CUSTOMER->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 29;
        return;
    }

    // 「検査結果時系列管理表」社名（英語）にフォーカスが有る場合
    if( Edt5_CHK_CUSTOMER2->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 30;
        return;
    }

    // 「検査経歴票」得意先品番（上）にフォーカスが有る場合
    if( Edt6_WHR_DTKSHIN1->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 17;
        return;
    }

    // 「検査経歴票」ロットにフォーカスが有る場合
    if( Edt6_WHR_LOTNO1->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 18;
        return;
    }

    // 「検査経歴票」検査日（自）にフォーカスが有る場合
    if( Edt6_WHR_KENSADATE1->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 19;
        return;
    }

    // 「検査経歴票」検査日（至）にフォーカスが有る場合
    if( Edt6_WHR_KENSADATE2->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 20;
        return;
    }

    // 「F1：一覧検索」ボタンを使えないようにする
    BtnF01->Enabled = false;
    BtnF01->Tag = 0;


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
void __fastcall TForm1::FormKeyPress(TObject *Sender, char &Key)
{
    if( Key == VK_RETURN )   Key = 0;
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
//    半角カンマはレポート出力時にエラーが発生するので全角
//    のカンマに変換します
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Edt_ALLChange2(TObject *Sender)
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

    // 半角カンマはレポート出力時にエラーが発生する
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
//    自作関数			：日付文字の/を削除します
//
//  機能説明
//    日付文字の/を削除します
//
//  パラメタ説明
//    AnsiString sYMD	：日付書式の文字列
//
//  戻り値
//    AnsiString          処理後の文字列
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::DelSEPA( AnsiString sYMD )
{
  int        iPos;
  AnsiString sRet;

  sRet = sYMD ;
  while( ( iPos = sRet.AnsiPos("/")) != 0 ){
      sRet.Delete(iPos, 1) ;

  }
  return ( sRet );

}


//---------------------------------------------------------------------------
//
//  概要
//    自作関数			："YYYY/MM/DD"形式の日付を"Jan DD.YYYY"形式の日付に変換します
//
//  機能説明
//    "YYYY/MM/DD"形式の日付を"Mmm DD.YYYY"形式の日付に変換します
//
//  パラメタ説明
//    AnsiString sYMD	：日付書式の文字列
//
//  戻り値
//    AnsiString          処理後の文字列
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::ToDateEnglish(AnsiString sDate)
{
	AnsiString	sYear;
    AnsiString	sMonth;
    AnsiString	sDay;

    AnsiString	sRet;


    sYear = sDate.SubString(1,4);
    sMonth = sDate.SubString(6,2);
    sDay = sDate.SubString(9,2);

    sRet = "";
    switch(sMonth.ToIntDef(0)){
        case 1:  sRet = "Jan";
        		 break;
        case 2:  sRet = "Feb";
        		 break;
        case 3:  sRet = "Mar";
        		 break;
        case 4:  sRet = "Apr";
        		 break;
        case 5:  sRet = "May";
        		 break;
        case 6:  sRet = "Jun";
        		 break;
        case 7:  sRet = "Jul";
        		 break;
        case 8:  sRet = "Aug";
        		 break;
        case 9:  sRet = "Sep";
        		 break;
        case 10: sRet = "Oct";
        		 break;
        case 11: sRet = "Nov";
        		 break;
        case 12: sRet = "Dec";
        		 break;
    	default: return( sDate );
    }

    sRet = sRet + " " + sDay + "." + sYear;

    return( sRet );
}








