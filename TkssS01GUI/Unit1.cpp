//---------------------------------------------------------------------------
//
//  Unit1.cpp
//    【出荷検査システム−自動整理登録処理】
//    メインフォーム（TForm1クラス）のメンバ関数の定義
//
//  作成者
//    高瀬　恵利
//
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"



//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;      

//データ検索結果格納
structKSD29 KSD29;      // 素材測定実績データ前回取り込み日時
structKSD21 KSD21;      // 出荷 素材測定実績データ
structKSD22 KSD22;      // 出荷 素材測定実績明細データ
structKSD23 KSD23;      // 出荷 素材測定実績例外データ
structKD_1  KD_1;       // 検査 素材測定データ

structFixStr FixStr[18]; // 各素材の固定文字列
int FixStrNum;           // 素材の種類

AnsiString MEMOStr[18];  // 各測定値の備考
AnsiString sBufSQL;      // バッファ SQL文

//素材測定実績データ（KSD21）の
//更新回数・素材測定更新に必要なキーを保存
TStrings *sDTKSHIN;    	 // 得意先品番
TStrings *sLOTNO; 		 // ロットNO
TStrings *sHINBAN; 		 // 自社品番
int isDTKSHINNum;        // データ数

AnsiString sExecDate;    // 処理実行日
AnsiString sStartTime;   // 処理実行時間


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}

/*----------------------------------------------------------------------------*/
//
//  概要
//    OnTimerイベント	：Interval プロパティで指定した時間が経過すると発生します。
//
//  機能説明
//    5秒カウントダウン後（中止可能）、自動整理登録処理を開始します
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
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::Tmr_CountDownTimer(TObject *Sender)
{
    Tmr_CountDown->Tag = Tmr_CountDown->Tag - 1;
    if( Tmr_CountDown->Tag <= 0 ){
        Tmr_CountDown->Enabled = false;
        Btn_Exit->Visible = false;

		// 自動整理登録処理開始
        Main();

    } else{
		Lbl_2->Caption = "開始まで " + IntToStr(Tmr_CountDown->Tag) + "秒";
    }
}

/*----------------------------------------------------------------------------*/
//
//  概要
//    OnCreateイベント	：Form1を作成したときに発生します。
//
//  機能説明
//    自動整理登録処理を開始します。
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
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::FormCreate(TObject *Sender)
{

    if( sCOMMAND.AnsiCompareIC( "/DIRECT" ) == 0 ){
        // メインメニューからユーザーが起動した時は、
        // 即座に処理を開始します

		// 自動整理登録処理開始
        Main();

    } else {
        // パソコン起動時又は、指定時間に自動実行する時は、
        // カウントダウン後（中止可能）、処理を開始します
		Lbl_1->Caption = "中間検査DBから出荷検査DBへの移行を開始します。";
		Lbl_2->Caption = "開始まで 5秒";
    	Tmr_CountDown->Tag = 5;
        Tmr_CountDown->Enabled = true;
    }
}

/*----------------------------------------------------------------------------*/
//
//  概要
//    OnClickイベント	：ボタン（終了）を押した時の処理
//
//  機能説明
//    プログラムを終了します
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
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::Btn_ExitClick(TObject *Sender)
{
    Close();
}

/*----------------------------------------------------------------------------*/
//
//  概要
//    自作関数			：自動整理登録処理開始
//
//  機能説明
//    中間検査DBから出荷検査DBへデータを移行します。
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
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::Main()
{

	int iRtn;
	AnsiString sRtn;
	AnsiString sMsg;

	TDateTime dtNow;    	//現在の日時
	WORD Y,M,D,H,N,S,MS;   	//現在の日時を各成分にセット
	AnsiString sNowDate;
	AnsiString sNowTime;

	Lbl_1->Caption = "中間検査DBから出荷検査DBへ移行しています。";
	Lbl_2->Caption = "しばらくお待ちください。";
    ListLog->Clear();
    Form1->Refresh();

	//TStrings初期化
	sDTKSHIN	= new TStringList;    	//得意先品番
	sLOTNO		= new TStringList; 		//ロットNO
	sHINBAN		= new TStringList; 		//自社品番


	//前回実行日時取得
	iRtn = GetKSD29("1");
    if( iRtn < 0 ){
        // データ取得失敗
        KSD29.UPDYMD = "19900101";
	    KSD29.UPDTIM = "0400";
    }

    // データ取得成功
    sExecDate = KSD29.UPDYMD;
	sStartTime = KSD29.UPDTIM;

	//現在の時刻を取得
	dtNow = Now( );
	DecodeDate(dtNow,Y,M,D);
	DecodeTime(dtNow,H,N,S,MS);
	sNowDate = "";
	sNowDate += FormatFloat("0000",Y);
	sNowDate += FormatFloat("00",M);
	sNowDate += FormatFloat("00",D);
	sNowTime = "";
	sNowTime += FormatFloat("00",H);
	sNowTime += FormatFloat("00",N);

    sMsg = "自動整理登録サービスの開始（" + sExecDate + sStartTime + "）";
    ListLog->Items->Add(sMsg);

	//自動整理登録実行
	iRtn = AutoEntry();
	sMsg = "自動整理登録実行 " + IntToStr(iRtn) + "件更新しました（" + sNowDate + sNowTime + "）";
    ListLog->Items->Add(sMsg);

	//実行日付更新
	sExecDate = sNowDate;
	sRtn = SetKSD29("1",sExecDate);


	Lbl_1->Caption = "中間検査DBから出荷検査DBへ移行が終了しました。";
	Lbl_2->Caption = " ";
    Form1->Refresh();

    Close();
}

/*----------------------------------------------------------------------------*/
//
//  概要
//    自作関数				：素材測定実績データ前回取り込み日時データ取得
//
//  機能説明
//    KSD29から前回取り込み日時を取得します。
//
//  パラメタ説明
//    AnsiString strFUNC_ID	：ファンクションＩＤ（KSD29検索条件）
//
//  戻り値
//    int					：0=検索成功 -1=検索失敗
//
//  備考
//    なし。
//
/*----------------------------------------------------------------------------*/
int __fastcall TForm1::GetKSD29(AnsiString strFUNC_ID)
{
	AnsiString sBuf;

	//素材測定実績データ前回取り込み日時データ取得
	KSD29.FUNC_ID = strFUNC_ID;
	KSD29.UPDYMD = "";
	KSD29.UPDTIM = "";

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// 問合せ実行
	sBuf = "SELECT FUNC_ID, UPDYMD, UPDTIM FROM KSD29 WHERE  FUNC_ID = ";
	sBuf += KSD29.FUNC_ID;

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	if ( Query1->Bof && Query1->Eof ) {
	//検索結果 ０件
		return(-1);
	}
	KSD29.UPDYMD = Query1->FieldValues["UPDYMD"];
	KSD29.UPDTIM = Query1->FieldValues["UPDTIM"];


	return(0);
}
/*----------------------------------------------------------------------------*/
//
//  概要
//    自作関数				：素材測定実績データ取り込み日時セット
//
//  機能説明
//    KSD29に取り込み日時をセットします。
//
//  パラメタ説明
//    AnsiString strFUNC_ID	：ファンクションＩＤ（KSD29検索条件）
//    AnsiString strUPDYMD	：セットする更新日
//
//  戻り値
//    AnsiString			：""=更新成功 エラーメッセージ=更新失敗
//
//  備考
//    なし。
//
/*----------------------------------------------------------------------------*/
AnsiString __fastcall TForm1::SetKSD29(AnsiString strFUNC_ID,AnsiString strUPDYMD)
{
	AnsiString sBufSQL;

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// 問合せ文作成
	sBufSQL = "update KSD29 set ";
	sBufSQL += "UPDYMD='" + strUPDYMD + "'"	;

	sBufSQL += " WHERE  FUNC_ID = ";
	sBufSQL += strFUNC_ID;

	Query1->SQL->Add(sBufSQL);

	// 問い合せ文の実行
	try
	{
		Query1->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		return(e.Message);
	}
	catch(Exception& e)
	{
		return(e.Message);
	}

	return("");


}
//---------------------------------------------------------------------------



