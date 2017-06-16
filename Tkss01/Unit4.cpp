//---------------------------------------------------------------------------
//
//  Unit4.cpp
//    【出荷検査システム－検査測定】
//    出荷検査項目フォーム（TForm4クラス）のメンバ関数の定義
//
//  作成者
//    田村　敦司
//
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit3.h"
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

	// グリッドの初期化
	SGr_List->ColCount = 30;
	SGr_List->ColWidths[0] = 34;
	SGr_List->ColWidths[1] = 175;
	SGr_List->ColWidths[2] = 140;
	SGr_List->ColWidths[3] = 102;
	SGr_List->ColWidths[4] = 50;
	SGr_List->ColWidths[5] = 150;
	SGr_List->ColWidths[6] = 25;
	SGr_List->ColWidths[7] = 55;
	SGr_List->ColWidths[8] = 30;
	SGr_List->ColWidths[9] = 30;
	SGr_List->ColWidths[10] = 75;
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
	SGr_List->ColWidths[21] = 0;
	SGr_List->ColWidths[22] = 0;
	SGr_List->ColWidths[23] = 0;
	SGr_List->ColWidths[24] = 0;
	SGr_List->ColWidths[25] = 0;
	SGr_List->ColWidths[26] = 0;
	SGr_List->ColWidths[27] = 0;
	SGr_List->ColWidths[28] = 0;
	SGr_List->ColWidths[29] = 0;

	SGr_List->Cells[0][0] = "  NO";
	SGr_List->Cells[1][0] = "測定項目";
	SGr_List->Cells[2][0] = "測定項目(English)";
	SGr_List->Cells[3][0] = "測定機器";
	SGr_List->Cells[4][0] = "単位";
	SGr_List->Cells[5][0] = "規格(基本)";
	SGr_List->Cells[6][0] = "n数(基本)";
	SGr_List->Cells[7][0] = "値表現";
	SGr_List->Cells[8][0] = "測定";
	SGr_List->Cells[9][0] = "特別";
	SGr_List->Cells[10][0] = "更新日";
	SGr_List->Cells[11][0] = "更新者";

	SGr_List2->ColCount = 30;
	SGr_List2->ColWidths[0] = 34;
	SGr_List2->ColWidths[1] = 175;
	SGr_List2->ColWidths[2] = 140;
	SGr_List2->ColWidths[3] = 102;
	SGr_List2->ColWidths[4] = 50;
	SGr_List2->ColWidths[5] = 150;
	SGr_List2->ColWidths[6] = 25;
	SGr_List2->ColWidths[7] = 55;
	SGr_List2->ColWidths[8] = 30;
	SGr_List2->ColWidths[9] = 30;
	SGr_List2->ColWidths[10] = 75;
	SGr_List2->ColWidths[11] = 0;
	SGr_List2->ColWidths[12] = 0;
	SGr_List2->ColWidths[13] = 0;
	SGr_List2->ColWidths[14] = 0;
	SGr_List2->ColWidths[15] = 0;
	SGr_List2->ColWidths[16] = 0;
	SGr_List2->ColWidths[17] = 0;
	SGr_List2->ColWidths[18] = 0;
	SGr_List2->ColWidths[19] = 0;
	SGr_List2->ColWidths[20] = 0;
	SGr_List2->ColWidths[21] = 0;
	SGr_List2->ColWidths[22] = 0;
	SGr_List2->ColWidths[23] = 0;
	SGr_List2->ColWidths[24] = 0;
	SGr_List2->ColWidths[25] = 0;
	SGr_List2->ColWidths[26] = 0;
	SGr_List2->ColWidths[27] = 0;
	SGr_List2->ColWidths[28] = 0;
	SGr_List2->ColWidths[29] = 0;

	SGr_List2->Cells[0][0] = "  NO";
	SGr_List2->Cells[1][0] = "測定項目";
	SGr_List2->Cells[2][0] = "測定項目(English)";
	SGr_List2->Cells[3][0] = "測定機器";
	SGr_List2->Cells[4][0] = "単位";
	SGr_List2->Cells[5][0] = "規格(基本)";
	SGr_List2->Cells[6][0] = "n数(基本)";
	SGr_List2->Cells[7][0] = "値表現";
	SGr_List2->Cells[8][0] = "測定";
	SGr_List2->Cells[9][0] = "特別";
	SGr_List2->Cells[10][0] = "更新日";
	SGr_List2->Cells[11][0] = "更新者";

    // コントロールの再配置
    Pnl_KIKAKU_KIJYUN->Left = Pnl_KIKAKU_MOJI->Left;

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
void __fastcall TForm4::FormActivate(TObject *Sender)
{

	int			iRow;
	AnsiString	sBuf;


    Rdo_List1_Order1->Checked = true;
    Rdo_List2_Order1->Checked = true;
    PgCtr_List->ActivePage = TabSheet1;

    //----------------------------------------------
    // 測定項目マスター検索

	// Initial Query
	Form3->Query1->Close();
	Form3->Query1->SQL->Clear();

	// 問合せ実行（測定項目マスター）
	//sBuf = "SELECT * FROM KSM11 ORDER BY ORDER_NO";
	sBuf  = "SELECT KSM11.KOMK_NO, KSM11.ORDER_NO, KSM11.KOMK_NM,";
    sBuf +=       " KSM11.KOMK_ENG, KSM11.KOMK_SUB, KSM11.KOMK_SUB_ENG,";
    sBuf +=       " KSM11.KIKI_NO, KSM11.KIKI_NM, KSM11.TANI, KSM11.KIKA_TYPE,";
    sBuf +=       " KSM11.KIKA_KIND, KSM11.KIKA_DECI, KSM11.KIKA_NUM1,";
    sBuf +=       " KSM11.KIKA_NUM2, KSM11.KIKA_NUM3, KSM11.KIKA_STR,";
    sBuf +=       " KSM11.KIKA_SUB1, KSM11.KIKA_SUB2, KSM11.KIKA_SUB3,";
    sBuf +=       " KSM11.SOKU_SU, KSM11.SOKU_FLG, KSM11.TOKU_FLG,";
    sBuf +=       " KSM11.KIKA_PRT, KSM11.VALUE_TYPE, KSM11.VALUE_DECI,";
    sBuf +=       " KSM11.ADDYMD, KSM11.ADDTIM, KSM11.UPDYMD, KSM11.UPDTIM,";
    sBuf +=       " KSM11.UPDCHR, KSM11.UPDCNT, SM12S.TANNAM";
    sBuf += " FROM KSM11 LEFT JOIN SM12S ON KSM11.UPDCHR = SM12S.TANSYA";
    sBuf += " ORDER BY KSM11.ORDER_NO";

	Form3->Query1->SQL->Add(sBuf);
	Form3->Query1->Open();
	Form3->Query1->Active = true;

	iRow = 1;

	while( !Form3->Query1->Eof ){

		// グリッドの最大行数が超えていないかチェックする
		if( iRow >= SGr_List->RowCount ){
			SGr_List->RowCount = iRow + 1;
		}

		// グリッドにデータをセットします。
		sBuf = iRow ;
		SGr_List->Cells[0][iRow] = AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;    //No
		sBuf = iRow + 1;

        if( VarIsNull(Form3->Query1->FieldValues["KOMK_NM"]) ){
			sBuf = "";
		} else{
			sBuf = Form3->Query1->FieldValues["KOMK_NM"];
		}
        SGr_List->Cells[1][iRow] = sBuf;   //測定項目（日本語）

        if( VarIsNull(Form3->Query1->FieldValues["KOMK_ENG"]) ){
			sBuf = "";
		} else{
			sBuf = Form3->Query1->FieldValues["KOMK_ENG"];
        }
        SGr_List->Cells[2][iRow] = sBuf;   //測定項目（英語）

		sBuf = Form3->Query1->FieldValues["KIKI_NM"];
		SGr_List->Cells[3][iRow] = sBuf;   //測定機器名称

        if( VarIsNull(Form3->Query1->FieldValues["TANI"]) ){
			sBuf = "";
		} else{
			sBuf = Form3->Query1->FieldValues["TANI"];
        }
		SGr_List->Cells[4][iRow] = sBuf;   //単位

		SGr_List->Cells[5][iRow] = "";     //規格（基本）   ※再描画する為に必要です。

		sBuf = Form3->Query1->FieldValues["SOKU_SU"];
		SGr_List->Cells[6][iRow] = sBuf;   //ｎ数（基本）

		sBuf = Form3->Query1->FieldValues["VALUE_TYPE"];
		SGr_List->Cells[7][iRow] = sBuf;   //値表現

		sBuf = Form3->Query1->FieldValues["SOKU_FLG"];
		SGr_List->Cells[8][iRow] = sBuf;   //測定項目の有無

		sBuf = Form3->Query1->FieldValues["TOKU_FLG"];
		SGr_List->Cells[9][iRow] = sBuf;   //特別項目の有無

		sBuf = Form3->Query1->FieldValues["UPDYMD"];
        SGr_List->Cells[10][iRow] = sBuf;   //変更日

		sBuf = Form3->Query1->FieldValues["UPDCHR"];
		SGr_List->Cells[12][iRow] = sBuf;   //更新者(担当者コード)

        //sBuf = GetTANNAM(sBuf);
        if( VarIsNull(Form3->Query1->FieldValues["TANNAM"]) ){
			sBuf = "";
		} else{
			sBuf = Form3->Query1->FieldValues["TANNAM"];
        }
		SGr_List->Cells[11][iRow] = sBuf;   //更新者

		sBuf = Form3->Query1->FieldValues["KOMK_NO"];
		SGr_List->Cells[13][iRow] = sBuf;   //項目NO

		sBuf = Form3->Query1->FieldValues["ORDER_NO"];
		SGr_List->Cells[14][iRow] = sBuf;   //表示順

		sBuf = Form3->Query1->FieldValues["KIKI_NO"];
		SGr_List->Cells[15][iRow] = sBuf;   //測定機器NO

		sBuf = Form3->Query1->FieldValues["KIKA_TYPE"];
		SGr_List->Cells[16][iRow] = sBuf;   //規格タイプ

		sBuf = Form3->Query1->FieldValues["KIKA_KIND"];
		SGr_List->Cells[17][iRow] = sBuf;   //規格種類

		sBuf = Form3->Query1->FieldValues["KIKA_DECI"];
		SGr_List->Cells[18][iRow] = sBuf;   //規格小数点以下桁数

		sBuf = Form3->Query1->FieldValues["KIKA_NUM1"];
		SGr_List->Cells[19][iRow] = sBuf;   //規格値１

		sBuf = Form3->Query1->FieldValues["KIKA_NUM2"];
		SGr_List->Cells[20][iRow] = sBuf;   //規格値２

		sBuf = Form3->Query1->FieldValues["KIKA_NUM3"];
		SGr_List->Cells[21][iRow] = sBuf;   //規格値３

        if( VarIsNull(Form3->Query1->FieldValues["KIKA_STR"]) ){
			sBuf = "";
		} else{
			sBuf = Form3->Query1->FieldValues["KIKA_STR"];
        }
		SGr_List->Cells[22][iRow] = sBuf;   //規格文字

		sBuf = Form3->Query1->FieldValues["KIKA_PRT"];
		SGr_List->Cells[23][iRow] = sBuf;   //上限下限値の印刷

		sBuf = Form3->Query1->FieldValues["VALUE_DECI"];
		SGr_List->Cells[24][iRow] = sBuf;   //測定値小数点以下桁数

		sBuf = Form3->Query1->FieldValues["ADDYMD"];
		SGr_List->Cells[25][iRow] = sBuf;   //登録日

		sBuf = Form3->Query1->FieldValues["ADDTIM"];
		SGr_List->Cells[26][iRow] =  sBuf;  //登録時間

		sBuf = Form3->Query1->FieldValues["UPDTIM"];
		SGr_List->Cells[27][iRow] = sBuf;   //更新時間

		sBuf = Form3->Query1->FieldValues["UPDCNT"];
		SGr_List->Cells[28][iRow] = sBuf;   //更新回数

		SGr_List->Cells[29][iRow] = "0";    //更新フラグ

		// カーソルを次にセットする
		Form3->Query1->Next();

		iRow += 1;
	}

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
    SGr_List->Cells[15][iRow] = "";
    SGr_List->Cells[16][iRow] = "";
    SGr_List->Cells[17][iRow] = "";
    SGr_List->Cells[18][iRow] = "";
    SGr_List->Cells[19][iRow] = "";
    SGr_List->Cells[20][iRow] = "";
    SGr_List->Cells[21][iRow] = "";
    SGr_List->Cells[22][iRow] = "";
    SGr_List->Cells[23][iRow] = "";
    SGr_List->Cells[24][iRow] = "";
    SGr_List->Cells[25][iRow] = "";
    SGr_List->Cells[26][iRow] = "";
    SGr_List->Cells[27][iRow] = "";
    SGr_List->Cells[28][iRow] = "";
    SGr_List->Cells[29][iRow] = "";


    //----------------------------------------------
    // 材料証明項目マスター検索

	// Initial Query
	Form3->Query1->Close();
	Form3->Query1->SQL->Clear();

	// 問合せ実行（測定項目マスター）
	//sBuf = "SELECT * FROM KSM12 ORDER BY ORDER_NO";
	sBuf  = "SELECT KSM12.KOMK_NO, KSM12.ORDER_NO, KSM12.KOMK_NM,";
    sBuf +=       " KSM12.KOMK_ENG, KSM12.KOMK_SUB, KSM12.KOMK_SUB_ENG,";
    sBuf +=       " KSM12.KIKI_NO, KSM12.KIKI_NM, KSM12.TANI, KSM12.KIKA_TYPE,";
    sBuf +=       " KSM12.KIKA_KIND, KSM12.KIKA_DECI, KSM12.KIKA_NUM1,";
    sBuf +=       " KSM12.KIKA_NUM2, KSM12.KIKA_NUM3, KSM12.KIKA_STR,";
    sBuf +=       " KSM12.KIKA_SUB1, KSM12.KIKA_SUB2, KSM12.KIKA_SUB3,";
    sBuf +=       " KSM12.SOKU_SU, KSM12.SOKU_FLG, KSM12.TOKU_FLG,";
    sBuf +=       " KSM12.KIKA_PRT, KSM12.VALUE_TYPE, KSM12.VALUE_DECI,";
    sBuf +=       " KSM12.ADDYMD, KSM12.ADDTIM, KSM12.UPDYMD, KSM12.UPDTIM,";
    sBuf +=       " KSM12.UPDCHR, KSM12.UPDCNT, SM12S.TANNAM";
    sBuf += " FROM KSM12 LEFT JOIN SM12S ON KSM12.UPDCHR = SM12S.TANSYA";
    sBuf += " ORDER BY KSM12.ORDER_NO";

	Form3->Query1->SQL->Add(sBuf);
	Form3->Query1->Open();
	Form3->Query1->Active = true;

	iRow = 1;

	while( !Form3->Query1->Eof ){

		// グリッドの最大行数が超えていないかチェックする
		if( iRow >= SGr_List2->RowCount ){
			SGr_List2->RowCount = iRow + 1;
		}

		// グリッドにデータをセットします。
		sBuf = iRow ;
		SGr_List2->Cells[0][iRow] = AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;    //No
		sBuf = iRow + 1;

        if( VarIsNull(Form3->Query1->FieldValues["KOMK_NM"]) ){
			sBuf = "";
		} else{
			sBuf = Form3->Query1->FieldValues["KOMK_NM"];
		}
        SGr_List2->Cells[1][iRow] = sBuf;   //測定項目（日本語）

        if( VarIsNull(Form3->Query1->FieldValues["KOMK_ENG"]) ){
			sBuf = "";
		} else{
			sBuf = Form3->Query1->FieldValues["KOMK_ENG"];
        }
        SGr_List2->Cells[2][iRow] = sBuf;   //測定項目（英語）

		sBuf = Form3->Query1->FieldValues["KIKI_NM"];
		SGr_List2->Cells[3][iRow] = sBuf;   //測定機器名称

        if( VarIsNull(Form3->Query1->FieldValues["TANI"]) ){
			sBuf = "";
		} else{
			sBuf = Form3->Query1->FieldValues["TANI"];
		}
        SGr_List2->Cells[4][iRow] = sBuf;   //単位

		SGr_List2->Cells[5][iRow] = "";     //規格（基本）   ※再描画する為に必要です。

		sBuf = Form3->Query1->FieldValues["SOKU_SU"];
		SGr_List2->Cells[6][iRow] = sBuf;   //ｎ数（基本）

		sBuf = Form3->Query1->FieldValues["VALUE_TYPE"];
		SGr_List2->Cells[7][iRow] = sBuf;   //値表現

		sBuf = Form3->Query1->FieldValues["SOKU_FLG"];
		SGr_List2->Cells[8][iRow] = sBuf;   //測定項目の有無

		sBuf = Form3->Query1->FieldValues["TOKU_FLG"];
		SGr_List2->Cells[9][iRow] = sBuf;   //特別項目の有無

		sBuf = Form3->Query1->FieldValues["UPDYMD"];
        SGr_List2->Cells[10][iRow] = sBuf;   //変更日

		sBuf = Form3->Query1->FieldValues["UPDCHR"];
		SGr_List2->Cells[12][iRow] = sBuf;   //更新者(担当者コード)

        //sBuf = GetTANNAM(sBuf);
        if( VarIsNull(Form3->Query1->FieldValues["TANNAM"]) ){
			sBuf = "";
		} else{
			sBuf = Form3->Query1->FieldValues["TANNAM"];
        }
		SGr_List2->Cells[11][iRow] = sBuf;   //更新者

		sBuf = Form3->Query1->FieldValues["KOMK_NO"];
		SGr_List2->Cells[13][iRow] = sBuf;   //項目NO

		sBuf = Form3->Query1->FieldValues["ORDER_NO"];
		SGr_List2->Cells[14][iRow] = sBuf;   //表示順

		sBuf = Form3->Query1->FieldValues["KIKI_NO"];
		SGr_List2->Cells[15][iRow] = sBuf;   //測定機器NO

		sBuf = Form3->Query1->FieldValues["KIKA_TYPE"];
		SGr_List2->Cells[16][iRow] = sBuf;   //規格タイプ

		sBuf = Form3->Query1->FieldValues["KIKA_KIND"];
		SGr_List2->Cells[17][iRow] = sBuf;   //規格種類

		sBuf = Form3->Query1->FieldValues["KIKA_DECI"];
		SGr_List2->Cells[18][iRow] = sBuf;   //規格小数点以下桁数

		sBuf = Form3->Query1->FieldValues["KIKA_NUM1"];
		SGr_List2->Cells[19][iRow] = sBuf;   //規格値１

		sBuf = Form3->Query1->FieldValues["KIKA_NUM2"];
		SGr_List2->Cells[20][iRow] = sBuf;   //規格値２

		sBuf = Form3->Query1->FieldValues["KIKA_NUM3"];
		SGr_List2->Cells[21][iRow] = sBuf;   //規格値３

        if( VarIsNull(Form3->Query1->FieldValues["KIKA_STR"]) ){
			sBuf = "";
		} else{
			sBuf = Form3->Query1->FieldValues["KIKA_STR"];
		}
        SGr_List2->Cells[22][iRow] = sBuf;   //規格文字

		sBuf = Form3->Query1->FieldValues["KIKA_PRT"];
		SGr_List2->Cells[23][iRow] = sBuf;   //上限下限値の印刷

		sBuf = Form3->Query1->FieldValues["VALUE_DECI"];
		SGr_List2->Cells[24][iRow] = sBuf;   //測定値小数点以下桁数

		sBuf = Form3->Query1->FieldValues["ADDYMD"];
		SGr_List2->Cells[25][iRow] = sBuf;   //登録日

		sBuf = Form3->Query1->FieldValues["ADDTIM"];
		SGr_List2->Cells[26][iRow] =  sBuf;  //登録時間

		sBuf = Form3->Query1->FieldValues["UPDTIM"];
		SGr_List2->Cells[27][iRow] = sBuf;   //更新時間

		sBuf = Form3->Query1->FieldValues["UPDCNT"];
		SGr_List2->Cells[28][iRow] = sBuf;   //更新回数

		SGr_List2->Cells[29][iRow] = "0";    //更新フラグ

		// カーソルを次にセットする
		Form3->Query1->Next();

		iRow += 1;
	}

    SGr_List2->RowCount = iRow + 1;
    SGr_List2->Cells[0][iRow] = "";
    SGr_List2->Cells[1][iRow] = "";
    SGr_List2->Cells[2][iRow] = "";
    SGr_List2->Cells[3][iRow] = "";
    SGr_List2->Cells[4][iRow] = "";
    SGr_List2->Cells[5][iRow] = "";
    SGr_List2->Cells[6][iRow] = "";
    SGr_List2->Cells[7][iRow] = "";
    SGr_List2->Cells[8][iRow] = "";
    SGr_List2->Cells[9][iRow] = "";
    SGr_List2->Cells[10][iRow] = "";
    SGr_List2->Cells[11][iRow] = "";
    SGr_List2->Cells[12][iRow] = "";
    SGr_List2->Cells[13][iRow] = "";
    SGr_List2->Cells[14][iRow] = "";
    SGr_List2->Cells[15][iRow] = "";
    SGr_List2->Cells[16][iRow] = "";
    SGr_List2->Cells[17][iRow] = "";
    SGr_List2->Cells[18][iRow] = "";
    SGr_List2->Cells[19][iRow] = "";
    SGr_List2->Cells[20][iRow] = "";
    SGr_List2->Cells[21][iRow] = "";
    SGr_List2->Cells[22][iRow] = "";
    SGr_List2->Cells[23][iRow] = "";
    SGr_List2->Cells[24][iRow] = "";
    SGr_List2->Cells[25][iRow] = "";
    SGr_List2->Cells[26][iRow] = "";
    SGr_List2->Cells[27][iRow] = "";
    SGr_List2->Cells[28][iRow] = "";
    SGr_List2->Cells[29][iRow] = "";

    //１行目を自動選択します
    SGr_List->Row = 1;
    PgCtr_ListChange( PgCtr_List );

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
void __fastcall TForm4::BtnF02Click(TObject *Sender)
{

	if( PgCtr_List->ActivePage->Name == "TabSheet1" ){
    	if(SGr_List->Row > 1){
        	SGr_List->Row -= 1;
        	SGr_List->SetFocus();
    	}
	} else{
    	if(SGr_List2->Row > 1){
        	SGr_List2->Row -= 1;
        	SGr_List2->SetFocus();
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
void __fastcall TForm4::BtnF03Click(TObject *Sender)
{
	if( PgCtr_List->ActivePage->Name == "TabSheet1" ){
    	if( (SGr_List->RowCount-1) > SGr_List->Row ){
        	SGr_List->Row += 1;
        	SGr_List->SetFocus();
    	}
    } else{
    	if( (SGr_List2->RowCount-1) > SGr_List2->Row ){
        	SGr_List2->Row += 1;
        	SGr_List2->SetFocus();
    	}
    }
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ８：追加／Ｆ９：挿入」ボタンを押した時の処理
//
//  機能説明
//    複数選択した場合は、選択した行をメインフォームの測定項目Gridに追加又は挿入します。
//    1つ選択の場合は、画面下の項目内容をメインフォームの測定項目Gridに追加又は挿入します。
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
void __fastcall TForm4::BtnF08F09Click(TObject *Sender)
{

    int				i;
    int				iSKB_NO;
    AnsiString		sBuf;
    TButton*		bt = dynamic_cast<TButton*>(Sender);
    TStringGrid*	sg;


	if( PgCtr_List->ActivePage->Name == "TabSheet1" ){
        // 出荷検査測定用項目
    	sg = dynamic_cast<TStringGrid*>(SGr_List);
        iSKB_NO = 2;
    }
    else {
        // 材料証明用項目
    	sg = dynamic_cast<TStringGrid*>(SGr_List2);
        iSKB_NO = 3;
    }

    if( iRowSelTop != iRowSelBottom ){
        // 複数選択の時は、StringGridのデータを追加／挿入します
    	for( i=iRowSelTop; i<=iRowSelBottom; i++ ) {
            if( sg->Cells[0][i].Trim() == "" ) continue;

            sBuf = Form3->Edt_DTKSHIN->Text;
			strcpy( Form3->tmpKSM02_DATA.DTKSHIN		,sBuf.c_str() );	// 代表得意先品番
            sBuf = "0";
			strcpy( Form3->tmpKSM02_DATA.REVCNT			,sBuf.c_str() );	// 改訂番号
            //sBuf = iSOKUT_UNQ_NO_MAX++ ;
			//strcpy( Form3->tmpKSM02_DATA.UNQ_NO		,sBuf.c_str() );	// 明細NO
            //sBuf = iSOKUT_ORDER_NO_MAX++ ;
			//strcpy( Form3->tmpKSM02_DATA.ORDER_NO		,sBuf.c_str() );	// 表示順
            sBuf = iSKB_NO;
			strcpy( Form3->tmpKSM02_DATA.SKB_NO			,sBuf.c_str() );	// 識別NO
            sBuf = Form3->Edt_DTKSHIN->Text;
			strcpy( Form3->tmpKSM02_DATA.HINBAN_SK		,sBuf.c_str() );	// 品番
			sBuf = sg->Cells[13][i];
			strcpy( Form3->tmpKSM02_DATA.KOMK_NO		,sBuf.c_str() );	// 項目NO
			sBuf = sg->Cells[1][i];
			strcpy( Form3->tmpKSM02_DATA.KOMK_NM		,sBuf.c_str() );	// 測定項目名称（日本語）
			sBuf = sg->Cells[2][i];
			strcpy( Form3->tmpKSM02_DATA.KOMK_ENG		,sBuf.c_str() );	// 測定項目名称（英語）
			sBuf = " ";
			strcpy( Form3->tmpKSM02_DATA.KOMK_SUB		,sBuf.c_str() );	// 測定項目サブ名称（日本語）
			sBuf = " ";
			strcpy( Form3->tmpKSM02_DATA.KOMK_SUB_ENG	,sBuf.c_str() );	// 測定項目サブ名称（英語）
			sBuf = sg->Cells[15][i];
			strcpy( Form3->tmpKSM02_DATA.KIKI_NO		,sBuf.c_str() );	// 測定機器NO
			sBuf = sg->Cells[3][i];
			strcpy( Form3->tmpKSM02_DATA.KIKI_NM		,sBuf.c_str() );	// 測定機器名称
			sBuf = sg->Cells[4][i];
			strcpy( Form3->tmpKSM02_DATA.TANI			,sBuf.c_str() );	// 単位
			sBuf = sg->Cells[16][i];
			strcpy( Form3->tmpKSM02_DATA.KIKA_TYPE		,sBuf.c_str() );	// 規格タイプ
			sBuf = sg->Cells[17][i];
			strcpy( Form3->tmpKSM02_DATA.KIKA_KIND		,sBuf.c_str() );	// 規格種類
			sBuf = sg->Cells[18][i];
			strcpy( Form3->tmpKSM02_DATA.KIKA_DECI		,sBuf.c_str() );	// 規格小数点以下桁数
			sBuf = sg->Cells[19][i];
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM1		,sBuf.c_str() );	// 規格値１
			sBuf = sg->Cells[20][i];
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM2		,sBuf.c_str() );	// 規格値２
			sBuf = sg->Cells[21][i];
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM3		,sBuf.c_str() );	// 規格値３
			sBuf = sg->Cells[22][i];
			strcpy( Form3->tmpKSM02_DATA.KIKA_STR		,sBuf.c_str() );	// 規格値文字
			sBuf = sg->Cells[6][i];
			strcpy( Form3->tmpKSM02_DATA.SOKU_SU		,sBuf.c_str() );	// 測定指示n数
			sBuf = sg->Cells[8][i];
			strcpy( Form3->tmpKSM02_DATA.SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
			sBuf = sg->Cells[9][i];
			strcpy( Form3->tmpKSM02_DATA.TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
			sBuf = sg->Cells[23][i];
			strcpy( Form3->tmpKSM02_DATA.KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
			sBuf = sg->Cells[7][i];
			strcpy( Form3->tmpKSM02_DATA.VALUE_TYPE		,sBuf.c_str() );	// 測定値表現
			sBuf = sg->Cells[24][i];
			strcpy( Form3->tmpKSM02_DATA.VALUE_DECI		,sBuf.c_str() );	// 測定値小数点以下桁数

            // 測定データを追加／挿入します
            if( bt->Name == "BtnF08" ){
                // 「Ｆ８：追加」
                Form3->Ins_SGr_SOKUT(Form3->SGr_SOKUT->RowCount-1);
            }
            else {
                // 「Ｆ９：挿入」
                Form3->Ins_SGr_SOKUT(Form3->SGr_SOKUT->Row);
            	if( i != iRowSelBottom )	Form3->SGr_SOKUT->Row = Form3->SGr_SOKUT->Row + 1;
            }
    	}

    }
    else {
        // 一行選択の時は、画面下部のデータを追加／挿入します

        // 入力データのチェック
        if(Edt_SKTKMK_JPN->Text.IsEmpty()){
            MessageDlg("測定項目名を入力してください。", mtWarning
                              ,TMsgDlgButtons() << mbOK, 0);
            Edt_SKTKMK_JPN->SetFocus();
            return;
        }
        if( Rdo_KIKAKU_SHITEI_HANI->Checked ) {
            if( (Rdo_KIKAKU_SYURUI_MINMAX->Checked &&
                (Nmb_KIKAKU_HANI_MIN->Text.ToIntDef(0) >
                 Nmb_KIKAKU_HANI_MAX->Text.ToIntDef(0) )) ){
                MessageDlg("規格の範囲指定が正しくありません。", mtWarning
                                  ,TMsgDlgButtons() << mbOK, 0);
                Nmb_KIKAKU_HANI_MIN->SetFocus();
                return;
            }
        }

        sBuf = Form3->Edt_DTKSHIN->Text;
		strcpy( Form3->tmpKSM02_DATA.DTKSHIN		,sBuf.c_str() );	// 代表得意先品番
        sBuf = "0";
		strcpy( Form3->tmpKSM02_DATA.REVCNT			,sBuf.c_str() );	// 改訂番号
        //sBuf = iSOKUT_UNQ_NO_MAX++ ;
		//strcpy( Form3->tmpKSM02_DATA.UNQ_NO		,sBuf.c_str() );	// 明細NO
        //sBuf = iSOKUT_ORDER_NO_MAX++ ;
		//strcpy( Form3->tmpKSM02_DATA.ORDER_NO		,sBuf.c_str() );	// 表示順
        sBuf = iSKB_NO;
		strcpy( Form3->tmpKSM02_DATA.SKB_NO			,sBuf.c_str() );	// 識別NO
        sBuf = Form3->Edt_DTKSHIN->Text;
		strcpy( Form3->tmpKSM02_DATA.HINBAN_SK		,sBuf.c_str() );	// 品番
		sBuf = Edt_SKTKMK_JPN->Tag;
		strcpy( Form3->tmpKSM02_DATA.KOMK_NO		,sBuf.c_str() );	// 項目NO
		sBuf = Edt_SKTKMK_JPN->Text;
		strcpy( Form3->tmpKSM02_DATA.KOMK_NM		,sBuf.c_str() );	// 測定項目名称（日本語）
		sBuf = Edt_SKTKMK_ENG->Text;
		strcpy( Form3->tmpKSM02_DATA.KOMK_ENG		,sBuf.c_str() );	// 測定項目名称（英語）
		sBuf = Edt_SKTKMK_JPN_SUB->Text;
		strcpy( Form3->tmpKSM02_DATA.KOMK_SUB		,sBuf.c_str() );	// 測定項目サブ名称（日本語）
		sBuf = Edt_SKTKMK_ENG_SUB->Text;
		strcpy( Form3->tmpKSM02_DATA.KOMK_SUB_ENG	,sBuf.c_str() );	// 測定項目サブ名称（英語）
		sBuf = IntToStr(Form3->iKIKI[Cmb_SKTKIKI->ItemIndex]);
		strcpy( Form3->tmpKSM02_DATA.KIKI_NO		,sBuf.c_str() );	// 測定機器NO
		sBuf = Cmb_SKTKIKI->Text;
		strcpy( Form3->tmpKSM02_DATA.KIKI_NM		,sBuf.c_str() );	// 測定機器名称
		sBuf = Cmb_TANI->Text;
		strcpy( Form3->tmpKSM02_DATA.TANI			,sBuf.c_str() );	// 単位

        if( Rdo_KIKAKU_SHITEI_HANI->Checked ) {
			sBuf = Nmb_KIKAKU_HANI_MIN->Text;
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM1		,sBuf.c_str() );	// 規格値１
			sBuf = Nmb_KIKAKU_HANI_MAX->Text;
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM2		,sBuf.c_str() );	// 規格値２
			sBuf = "0";
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM3		,sBuf.c_str() );	// 規格値３
			sBuf = "";
			strcpy( Form3->tmpKSM02_DATA.KIKA_STR		,sBuf.c_str() );	// 規格値文字
			sBuf = "1";
        } else if( Rdo_KIKAKU_SHITEI_KIJYUN->Checked ) {
			sBuf = Nmb_KIKAKU_KIJYUN_MID->Text;
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM1		,sBuf.c_str() );	// 規格値１
			sBuf = Nmb_KIKAKU_KIJYUN_MAX->Text;
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM2		,sBuf.c_str() );	// 規格値２
			sBuf = Nmb_KIKAKU_KIJYUN_MIN->Text;
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM3		,sBuf.c_str() );	// 規格値３
			sBuf = "";
			strcpy( Form3->tmpKSM02_DATA.KIKA_STR		,sBuf.c_str() );	// 規格値文字
			sBuf = "2";
		} else {
			sBuf = "0";
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM1		,sBuf.c_str() );	// 規格値１
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM2		,sBuf.c_str() );	// 規格値２
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM3		,sBuf.c_str() );	// 規格値３
			sBuf = Edt_KIKAKU_STRING->Text;
			strcpy( Form3->tmpKSM02_DATA.KIKA_STR		,sBuf.c_str() );	// 規格値文字
			sBuf = "3";
        }
		strcpy( Form3->tmpKSM02_DATA.KIKA_TYPE		,sBuf.c_str() );	// 規格タイプ
        if( Rdo_KIKAKU_SYURUI_MINMAX->Checked )			sBuf = "1";
		else if( Rdo_KIKAKU_SYURUI_MAX->Checked )		sBuf = "2";
        else											sBuf = "3";
        strcpy( Form3->tmpKSM02_DATA.KIKA_KIND		,sBuf.c_str() );	// 規格種類
        sBuf = Nmb_KIKAKU_DOUBLE->Text;
		strcpy( Form3->tmpKSM02_DATA.KIKA_DECI		,sBuf.c_str() );	// 規格小数点以下桁数
        sBuf = Nmb_N->Text;
		strcpy( Form3->tmpKSM02_DATA.SOKU_SU		,sBuf.c_str() );	// 測定指示n数
        if( Rdo_SKTKMK_ON->Checked )			sBuf = "1";
		else									sBuf = "0";
		strcpy( Form3->tmpKSM02_DATA.SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
		if( Rdo_TKBKMK_ON->Checked )			sBuf = "1";
		else									sBuf = "0";
		strcpy( Form3->tmpKSM02_DATA.TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
		if( Rdo_MANMIN_PRT_ON->Checked )		sBuf = "1";
		else									sBuf = "0";
		strcpy( Form3->tmpKSM02_DATA.KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
		if( Rdo_VALUE_NORMAL->Checked )			sBuf = "0";
		else if( Rdo_VALUE_KAKUDO->Checked )	sBuf = "1";
		else if( Rdo_VALUE_OK->Checked )		sBuf = "2";
		else									sBuf = "3";
		strcpy( Form3->tmpKSM02_DATA.VALUE_TYPE		,sBuf.c_str() );	// 測定値表現
		sBuf = Nmb_VALUE_DOUBLE->Text;
		strcpy( Form3->tmpKSM02_DATA.VALUE_DECI		,sBuf.c_str() );	// 測定値小数点以下桁数

        // 測定データを追加／挿入します
        if( bt->Name == "BtnF08" ){
            // 「Ｆ８：追加」
            Form3->Ins_SGr_SOKUT(Form3->SGr_SOKUT->RowCount-1);
        }
        else {
            // 「Ｆ９：挿入」
            Form3->Ins_SGr_SOKUT(Form3->SGr_SOKUT->Row);
        }
    }

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
         case VK_F8:  BtnF08F09Click(BtnF08);	break;
         case VK_F9:  BtnF08F09Click(BtnF09);	break;
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
void __fastcall TForm4::Pnl_ListResize(TObject *Sender)
{
    int iBMarg;

    // 親ラベルから見た各コントロールの下端余白
    iBMarg = 6;


    // 検索リスト
	if( PgCtr_List->Top < Pnl_List->Height &&
        Pnl_List->Height - PgCtr_List->Top - iBMarg > 0 ){
		PgCtr_List->Height = Pnl_List->Height - PgCtr_List->Top - iBMarg;
	} else{
		PgCtr_List->Height = 0;
	}

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
//    OnChangeイベント	：新しいタブが選択されると発生します。
//
//  機能説明
//    ページコントロールによる「出荷検査測定項目」「材料証明項目」の切替
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
void __fastcall TForm4::PgCtr_ListChange(TObject *Sender)
{
    bool blnHoge=true;
	TPageControl *pPC = (TPageControl *)Sender;

	if( pPC->ActivePage->Name == "TabSheet1" ){
	    //行を自動選択します
    	SGr_ListSelectCell( SGr_List, 1, SGr_List->Row, blnHoge);
	    SGr_ListClick( SGr_List );

        //色変更
		Pnl_t02->Color = (TColor)0x00FFEEDD;
		Pnl_t03->Color = (TColor)0x00FFEEDD;
		Pnl_t04->Color = (TColor)0x00FFEEDD;
		Pnl_t05->Color = (TColor)0x00FFEEDD;
		Pnl_t06->Color = (TColor)0x00FFEEDD;
		Pnl_t07->Color = (TColor)0x00FFEEDD;
		Pnl_t08->Color = (TColor)0x00FFEEDD;
		Pnl_t09->Color = (TColor)0x00FFEEDD;
		Pnl_t10->Color = (TColor)0x00FFEEDD;
		Pnl_t11->Color = (TColor)0x00FFEEDD;
		Pnl_t12->Color = (TColor)0x00FFEEDD;
		Pnl_t13->Color = (TColor)0x00FFEEDD;
		Pnl_t14->Color = (TColor)0x00FFEEDD;
		Pnl_t15->Color = (TColor)0x00FFEEDD;
		Pnl_t16->Color = (TColor)0x00FFEEDD;
		Pnl_t17->Color = (TColor)0x00FFEEDD;
		Pnl_t18->Color = (TColor)0x00FFEEDD;
		Pnl_t19->Color = (TColor)0x00FFEEDD;
		Pnl_t20->Color = (TColor)0x00FFEEDD;
		Pnl_t21->Color = (TColor)0x00FFEEDD;
	} else{
	    //行を自動選択します
    	SGr_ListSelectCell( SGr_List2, 1, SGr_List2->Row, blnHoge);
	    SGr_ListClick( SGr_List2 );

        //色変更
    	Pnl_t02->Color = (TColor)0x00FFE1FD;
    	Pnl_t03->Color = (TColor)0x00FFE1FD;
    	Pnl_t04->Color = (TColor)0x00FFE1FD;
    	Pnl_t05->Color = (TColor)0x00FFE1FD;
    	Pnl_t06->Color = (TColor)0x00FFE1FD;
    	Pnl_t07->Color = (TColor)0x00FFE1FD;
    	Pnl_t08->Color = (TColor)0x00FFE1FD;
    	Pnl_t09->Color = (TColor)0x00FFE1FD;
    	Pnl_t10->Color = (TColor)0x00FFE1FD;
    	Pnl_t11->Color = (TColor)0x00FFE1FD;
    	Pnl_t12->Color = (TColor)0x00FFE1FD;
    	Pnl_t13->Color = (TColor)0x00FFE1FD;
    	Pnl_t14->Color = (TColor)0x00FFE1FD;
    	Pnl_t15->Color = (TColor)0x00FFE1FD;
		Pnl_t16->Color = (TColor)0x00FFE1FD;
		Pnl_t17->Color = (TColor)0x00FFE1FD;
		Pnl_t18->Color = (TColor)0x00FFE1FD;
		Pnl_t19->Color = (TColor)0x00FFE1FD;
		Pnl_t20->Color = (TColor)0x00FFE1FD;
		Pnl_t21->Color = (TColor)0x00FFE1FD;
	}

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
void __fastcall TForm4::SGr_ListDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{

   AnsiString	sBuf, sValue;
   char 		cFormatBuf[20], c1[20], c2[10];
   long			iPos;

   TStringGrid *sg = (TStringGrid *)Sender;

   RECT r=RECT(Rect);

   //固定セルの背景色をセット
   if(State.Contains(gdFixed))
       sg->Canvas->Brush->Color= sg->FixedColor;
   //フォーカスのあるセルの背景色をセット
//   else if(State.Contains(gdFocused))
//       SGr1->Canvas->Brush->Color= SGr1->Options.Contains(goDrawFocusSelected)? clHighlight: SGr1->Color;
   //選択されているセルの背景色をセット
   else if(State.Contains(gdSelected))
       sg->Canvas->Brush->Color= clHighlight;
   //普通のセルの背景色をセット
   else
       sg->Canvas->Brush->Color= sg->Color;

   //背景色で消去
   sg->Canvas->FillRect(Rect);

   //固定セルの立体枠を描く
   if(sg->Ctl3D&&State.Contains(gdFixed))
       DrawEdge(sg->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);

   //フォーカスのあるセルの文字色をセット
   if(State.Contains(gdFocused)){
//       SGr1->Canvas->Font->Color= SGr1->Options.Contains(goDrawFocusSelected)? clHighlightText: SGr1->Font->Color;
//       //フォーカス枠を描く
//       DrawFocusRect(SGr1->Canvas->Handle,&r);
	   //選択されているセルの文字色をセット
       //if(State.Contains(gdSelected))

       sg->Canvas->Font->Color= clHighlightText;
   }
   //選択されているセルの文字色をセット
   else if(State.Contains(gdSelected))
       sg->Canvas->Font->Color= clHighlightText;
   //普通のセルの文字色をセット
   else
       sg->Canvas->Font->Color= sg->Font->Color;

   //テキスト表示領域の設定
   InflateRect(&r,-2,-2);

   if( ARow > 0 && ACol == 5 ){

        // 規格タイプ毎の表示
        switch( sg->Cells[16][ARow].ToIntDef(0) ){
            case 1: // 範囲指定

                    // 小数点以下桁数のフォーマット文字列
            		sprintf(c1,"%0");
            		sprintf(c2,"1.%df",sg->Cells[18][ARow].ToIntDef(0) );
            		strcat(c1,c2);

			        switch( sg->Cells[17][ARow].ToIntDef(0) ){
            			case 1: // 上限下限両方
                                sValue = sg->Cells[19][ARow];
                                //2003.05.08 E.Takase Add↓
			                    sprintf(cFormatBuf, c1, Form1->ConvDoubleDefD(sValue,0.0) );
                                //2003.05.08 E.Takase Add↑
			        			//2003.05.08 E.Takase Add コメント↓
			                    //sprintf(cFormatBuf, c1, sValue.ToDouble() );
                                //2003.05.08 E.Takase Add コメント↑
                     			sBuf = cFormatBuf;
                     			sBuf +=  "～";
                                sValue = sg->Cells[20][ARow];
                                //2003.05.08 E.Takase Add↓
                     			sprintf(cFormatBuf, c1, Form1->ConvDoubleDefD(sValue,0.0) );
                                //2003.05.08 E.Takase Add↑
			        			//2003.05.08 E.Takase Add コメント↓
                     			//sprintf(cFormatBuf, c1, sValue.ToDouble() );
                                //2003.05.08 E.Takase Add コメント↑
                     			sBuf += cFormatBuf ;
			            		break;

            			case 2: // 上限のみ
                                sValue = sg->Cells[20][ARow];
                                //2003.05.08 E.Takase Add↓
                     			sprintf(cFormatBuf, c1, Form1->ConvDoubleDefD(sValue,0.0) );
                                //2003.05.08 E.Takase Add↑
			        			//2003.05.08 E.Takase Add コメント↓
                     			//sprintf(cFormatBuf, c1, sValue.ToDouble() );
                                //2003.05.08 E.Takase Add コメント↑
                     			sBuf = cFormatBuf ;
                     			sBuf += "以下";
			            		break;
            			case 3: // 下限のみ
                                sValue = sg->Cells[19][ARow];
                                //2003.05.08 E.Takase Add↓
                     			sprintf(cFormatBuf, c1, Form1->ConvDoubleDefD(sValue,0.0) );
                                //2003.05.08 E.Takase Add↑
			        			//2003.05.08 E.Takase Add コメント↓
                     			//sprintf(cFormatBuf, c1, sValue.ToDouble() );
                                //2003.05.08 E.Takase Add コメント↑
                     			sBuf = cFormatBuf ;
                     			sBuf += "以上";
			            		break;
                    }
					DrawText(sg->Canvas->Handle,sBuf.c_str(),-1,&r,0); //左寄せ
            		break;

            case 2: // 基準値指定

                    // 小数点以下桁数のフォーマット文字列
            		sprintf(c1,"%0");
            		sprintf(c2,"1.%df",sg->Cells[18][ARow].ToIntDef(0) );
            		strcat(c1,c2);

                    sValue = sg->Cells[19][ARow];
                    //2003.05.08 E.Takase Add↓
                    sprintf(cFormatBuf, c1, Form1->ConvDoubleDefD(sValue,0.0) );
                    //2003.05.08 E.Takase Add↑
			        //2003.05.08 E.Takase Add コメント↓
                    //sprintf(cFormatBuf, c1, sValue.ToDouble() );
                    //2003.05.08 E.Takase Add コメント↑
                    sBuf = cFormatBuf ;
        			sg->Canvas->TextOut( r.left +  0, r.top + 0, sBuf );
                    iPos = sBuf.Length() * 8;

        			// フォント（小）の設定
        			Form3->OrgFont = SelectObject( sg->Canvas->Handle, Form3->MyFont );

			        switch( sg->Cells[17][ARow].ToIntDef(0) ){
            			case 1: // 上限下限両方
                    			sValue = sg->Cells[20][ARow];
                                //2003.05.08 E.Takase Add↓
                    			sprintf(cFormatBuf, c1, Form1->ConvDoubleDefD(sValue,0.0) );
                                //2003.05.08 E.Takase Add↑
			        			//2003.05.08 E.Takase Add コメント↓
                    			//sprintf(cFormatBuf, c1, sValue.ToDouble() );
                                //2003.05.08 E.Takase Add コメント↑
			                    sBuf = cFormatBuf;
                                if( sBuf.SubString(1,1) != "-" ) sBuf.Insert("+",1);
                                sg->Canvas->TextOut( r.left + iPos, r.top - 2, sBuf );
                     			sValue = sg->Cells[21][ARow];
                                //2003.05.08 E.Takase Add↓
                    			sprintf(cFormatBuf, c1, Form1->ConvDoubleDefD(sValue,0.0) );
                                //2003.05.08 E.Takase Add↑
			        			//2003.05.08 E.Takase Add コメント↓
                    			//sprintf(cFormatBuf, c1, sValue.ToDouble() );
                                //2003.05.08 E.Takase Add コメント↑
			                    sBuf = cFormatBuf ;
                                if( sBuf.SubString(1,1) != "-" ) sBuf.Insert("+",1);
        						sg->Canvas->TextOut( r.left + iPos, r.top + 7, sBuf );
			            		break;

            			case 2: // 上限のみ
			                    sValue = sg->Cells[20][ARow];
                                //2003.05.08 E.Takase Add↓
                    			sprintf(cFormatBuf, c1, Form1->ConvDoubleDefD(sValue,0.0) );
                                //2003.05.08 E.Takase Add↑
			        			//2003.05.08 E.Takase Add コメント↓
                    			//sprintf(cFormatBuf, c1, sValue.ToDouble() );
                                //2003.05.08 E.Takase Add コメント↑
			                    sBuf = cFormatBuf;
                                if( sBuf.SubString(1,1) != "-" ) sBuf.Insert("+",1);
			        			sg->Canvas->TextOut( r.left + iPos, r.top - 2, sBuf );
			            		break;
            			case 3: // 下限のみ
                     			sValue = sg->Cells[21][ARow];
                                //2003.05.08 E.Takase Add↓
                    			sprintf(cFormatBuf, c1,  Form1->ConvDoubleDefD(sValue,0.0) );
                                //2003.05.08 E.Takase Add↑
			        			//2003.05.08 E.Takase Add コメント↓
                    			//sprintf(cFormatBuf, c1, sValue.ToDouble() );
                                //2003.05.08 E.Takase Add コメント↑
			                    sBuf = cFormatBuf ;
                                if( sBuf.SubString(1,1) != "-" ) sBuf.Insert("+",1);
        						sg->Canvas->TextOut( r.left + iPos, r.top + 7, sBuf );
			            		break;
                    }

        			// 元のフォントに戻します
        			SelectObject( sg->Canvas->Handle, Form3->OrgFont );

                    break;

        	case 3: // 文字
					DrawText(sg->Canvas->Handle,sg->Cells[22][ARow].c_str(),-1,&r,0); //左寄せ
                    break;
        }

   } else if( ARow > 0 && ACol == 6 ){
        // ｎ数
		DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,DT_RIGHT); //右寄せ

   } else if( ARow > 0 && ACol == 7 ){
        // 値表現
        switch( sg->Cells[ACol][ARow].ToIntDef(-1) ){
   			case 0: // 整数・小数(99.99)
                    if( sg->Cells[24][ARow].ToIntDef(0) > 0 ){
                    	sBuf = "9." + AnsiString::StringOfChar('9', sg->Cells[24][ARow].ToIntDef(0));
            		} else{
                    	sBuf = "9";
                    }
                    DrawText(sg->Canvas->Handle,sBuf.c_str(),-1,&r,0); //左寄せ
            		break;
   			case 1: // 角度(99゜99')
                    if( sg->Cells[24][ARow].ToIntDef(0) > 0 ){
	                    sBuf = "9°" + AnsiString::StringOfChar('9', sg->Cells[24][ARow].ToIntDef(0)) + "'";
            		} else{
                    	sBuf = "9°";
                    }
            		DrawText(sg->Canvas->Handle,sBuf.c_str(),-1,&r,0); //左寄せ
            		break;
   			case 2: // 良(OK)／否(NG)
            		DrawText(sg->Canvas->Handle,"良/否",-1,&r,0); //左寄せ
            		break;
   			case 3: // 文字
            		DrawText(sg->Canvas->Handle,"文字",-1,&r,0); //左寄せ
            		break;
       	}

   } else if( ARow > 0 && (ACol == 8 || ACol == 9) ){
        // 測定項目の有無、特別項目の有無
        switch( sg->Cells[ACol][ARow].ToIntDef(-1) ){
   			case 0: DrawText(sg->Canvas->Handle,"無",-1,&r,0); //左寄せ
            		break;
   			case 1: DrawText(sg->Canvas->Handle,"有",-1,&r,0); //左寄せ
            		break;
       	}

   } else if( ARow > 0 && ACol == 10 ){
        // 更新日
        sBuf = sg->Cells[10][ARow];
        if( sBuf.Length() == 8 ){
        	sBuf.Insert("/",5);
       		sBuf.Insert("/",8);
   			DrawText(sg->Canvas->Handle,sBuf.c_str(),-1,&r,0); //左寄せ
        }

   } else{
		//テキストの表示
		DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,0); //左寄せ
		//DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,DT_RIGHT); //右寄せ
		//DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,DT_CENTER); //中央寄せ（水平）
		//DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,DT_VCENTER|DT_SINGLELINE); //中央寄せ（垂直）
		//DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,DT_BOTTOM|DT_SINGLELINE); //下寄せ
		//DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,DT_CENTER|DT_VCENTER|DT_SINGLELINE); //水平･垂直とも中央寄せ
		//DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,DT_WORDBREAK); //複数行表示
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
void __fastcall TForm4::SGr_ListClick(TObject *Sender)
{
    TStringGrid* sg = dynamic_cast<TStringGrid*>(Sender);

   	iRowSelTop    = sg->Selection.Top;
   	iRowSelBottom = sg->Selection.Bottom;
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
void __fastcall TForm4::SGr_ListKeyPress(TObject *Sender, char &Key)
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
void __fastcall TForm4::SGr_ListSelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{

    int			i, k;
    AnsiString	sBuf;
	TStringGrid *sg = (TStringGrid *)Sender;


    if(ARow == 0) ARow = 1;

    // 測定NO
    Edt_SKTKMK_JPN->Tag = sg->Cells[13][ARow].ToIntDef(0);

    // 測定項目（日本語）
    Edt_SKTKMK_JPN->Text = sg->Cells[1][ARow];

    // 項目名（英語）
    Edt_SKTKMK_ENG->Text = sg->Cells[2][ARow];

    // 測定機器
    k = sg->Cells[15][ARow].ToIntDef(-1);
    if( k == -1 ){
	    Cmb_SKTKIKI->ItemIndex = 0;
    }
    else {
    	for( i = 0; i < Form3->iKIKI_Cnt; i++){
    		if( Form3->iKIKI[i] == k ){
			    Cmb_SKTKIKI->ItemIndex = i;
            	break;
        	}
    	}
    }

    // 単位
    Cmb_TANI->Text = sg->Cells[4][ARow];

	// 測定項目としての扱い
    switch( sg->Cells[8][ARow].ToIntDef(-1) ){
		case 0: Rdo_SKTKMK_OFF->Checked = true;
				break;
		case 1:
        default:Rdo_SKTKMK_ON->Checked = true;
          		break;
   	}

	// 特別項目としての扱い
    switch( sg->Cells[9][ARow].ToIntDef(-1) ){
		case 1: Rdo_TKBKMK_ON->Checked = true;
				break;
		case 0:
        default:Rdo_TKBKMK_OFF->Checked = true;
          		break;
   	}

	// 規格（指定方法）
    switch( sg->Cells[16][ARow].ToIntDef(-1) ){
		case 3: Rdo_KIKAKU_SHITEI_MOJI->Checked = true;
				break;
		case 2: Rdo_KIKAKU_SHITEI_KIJYUN->Checked = true;
				break;
		case 1:
        default:Rdo_KIKAKU_SHITEI_HANI->Checked = true;
          		break;
   	}

	// 規格（種類）
    switch( sg->Cells[17][ARow].ToIntDef(-1) ){
		case 3: Rdo_KIKAKU_SYURUI_MIN->Checked = true;
				break;
		case 2: Rdo_KIKAKU_SYURUI_MAX->Checked = true;
				break;
		case 1:
        default:Rdo_KIKAKU_SYURUI_MINMAX->Checked = true;
          		break;
   	}

	// 規格（上限下限値の印刷）
    switch( sg->Cells[23][ARow].ToIntDef(-1) ){
		case 0: Rdo_MANMIN_PRT_OFF->Checked = true;
				break;
		case 1:
        default:Rdo_MANMIN_PRT_ON->Checked = true;
          		break;
   	}

	// 規格（小数点以下桁数）
    Nmb_KIKAKU_DOUBLE->Text = IntToStr(sg->Cells[18][ARow].ToIntDef(0));

	// 規格値（範囲指定）
    Nmb_KIKAKU_HANI_MIN->FPos = sg->Cells[18][ARow].ToIntDef(0);
    Nmb_KIKAKU_HANI_MAX->FPos = sg->Cells[18][ARow].ToIntDef(0);
    Nmb_KIKAKU_HANI_MIN->Text = sg->Cells[19][ARow];
    if( sg->Cells[16][ARow].ToIntDef(-1) == 1 ){
	    Nmb_KIKAKU_HANI_MAX->Text = sg->Cells[20][ARow];
    }
    else {
	    Nmb_KIKAKU_HANI_MAX->Text = "0";
    }

	// 規格値（基準値指定）
    Nmb_KIKAKU_KIJYUN_MID->FPos = sg->Cells[18][ARow].ToIntDef(0);
    Nmb_KIKAKU_KIJYUN_MAX->FPos = sg->Cells[18][ARow].ToIntDef(0);
    Nmb_KIKAKU_KIJYUN_MIN->FPos = sg->Cells[18][ARow].ToIntDef(0);
    Nmb_KIKAKU_KIJYUN_MID->Text = sg->Cells[19][ARow];
    if( sg->Cells[16][ARow].ToIntDef(-1) == 2 ){
    	Nmb_KIKAKU_KIJYUN_MAX->Text = sg->Cells[20][ARow];
    	Nmb_KIKAKU_KIJYUN_MIN->Text = sg->Cells[21][ARow];
    }
    else {
    	Nmb_KIKAKU_KIJYUN_MAX->Text = "0";
    	Nmb_KIKAKU_KIJYUN_MIN->Text = "0";
    }

	// 規格値（文字指定）
    Edt_KIKAKU_STRING->Text = sg->Cells[22][ARow];

	// 測定値（値表現）
    switch( sg->Cells[7][ARow].ToIntDef(-1) ){
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
    Nmb_VALUE_DOUBLE->Text = IntToStr(sg->Cells[24][ARow].ToIntDef(0));

	// 測定値（抜取ｎ数）
    Nmb_N->Text = IntToStr(sg->Cells[6][ARow].ToIntDef(2));

    // 更新日
    sBuf = sg->Cells[10][ARow];
    if( sBuf.Length() == 8 ){
    	sBuf.Insert("/",5);
       	sBuf.Insert("/",8);
	   	PnlUPDYMD->Caption = sBuf;
    }
    else {
	   	PnlUPDYMD->Caption = "";
    }

    // 更新者
    PnlUPDCHR->Caption = sg->Cells[11][ARow];

    // 修正･削除の為に「項目No」を記憶します。
    if( sg->Cells[13][ARow] == "" ){
        PnlUPDYMD->Tag = -1;
    }
    else {
        PnlUPDYMD->Tag = StrToInt(sg->Cells[13][ARow]);
    }

    // 更新回数を記憶します。
    if( sg->Cells[28][ARow] == "" ){
    	PnlUPDCHR->Tag = -1;
    }
    else {
    	PnlUPDCHR->Tag = StrToInt(sg->Cells[28][ARow]);
    }

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：出荷検査用StringGridの表示順（３種類）をクリックしたときに発生します。
//
//  機能説明
//    出荷検査用StringGridの表示順を変更します
//      ・測定項目マスター順
//      ・測定項目名称順
//      ・測定機器・測定項目名称順
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
void __fastcall TForm4::Rdo_List1_OrderClick(TObject *Sender)
{
    int				i, k, m;
	AnsiString		sBuf;
	TRadioButton	*rdo = (TRadioButton *)Sender;
    bool blnHoge=true;

    if( rdo->Name == "Rdo_List1_Order1" ){
	    // 表示順でソートを行ないます
		for( i = 1; i < SGr_List->RowCount - 2; i++ ){
	    	for( k = i + 1; k < SGr_List->RowCount - 1; k++ ) {
	            if( SGr_List->Cells[14][i].ToIntDef(0) > SGr_List->Cells[14][k].ToIntDef(0) ){
                    sBuf = GridLineCopy( SGr_List, i);
					for( m = 1; m < SGr_List->ColCount; m++ ) {
						SGr_List->Cells[m][i] = SGr_List->Cells[m][k];
                    }
                    GridLinePaste( SGr_List, k, sBuf);
	            }
			}
    	}

	} else {
	    if( rdo->Name == "Rdo_List1_Order2" ){

		    // 測定項目順でソートを行ないます
			for( i = 1; i < SGr_List->RowCount - 2; i++ ){
		    	for( k = i + 1; k < SGr_List->RowCount - 1; k++ ) {
		            if( SGr_List->Cells[1][i] > SGr_List->Cells[1][k] ){
	                    sBuf = GridLineCopy( SGr_List, i);
						for( m = 1; m < SGr_List->ColCount; m++ ) {
							SGr_List->Cells[m][i] = SGr_List->Cells[m][k];
	                    }
	                    GridLinePaste( SGr_List, k, sBuf);
		            }
				}
	    	}
		} else {

		    // 測定機器・測定項目順でソートを行ないます
			for( i = 1; i < SGr_List->RowCount - 2; i++ ){
		    	for( k = i + 1; k < SGr_List->RowCount - 1; k++ ) {
		            if( SGr_List->Cells[15][i].ToIntDef(0) > SGr_List->Cells[15][k].ToIntDef(0) ){
	                    sBuf = GridLineCopy( SGr_List, i);
						for( m = 1; m < SGr_List->ColCount; m++ ) {
							SGr_List->Cells[m][i] = SGr_List->Cells[m][k];
	                    }
	                    GridLinePaste( SGr_List, k, sBuf);
		            } else {
		            	if( SGr_List->Cells[15][i] == SGr_List->Cells[15][k] &&
                        	SGr_List->Cells[1][i] > SGr_List->Cells[1][k] ){
	                    	sBuf = GridLineCopy( SGr_List, i);
							for( m = 1; m < SGr_List->ColCount; m++ ) {
								SGr_List->Cells[m][i] = SGr_List->Cells[m][k];
	                    	}
	                    	GridLinePaste( SGr_List, k, sBuf);
						}
                    }
				}
	    	}
        }
    }

	SGr_ListSelectCell( SGr_List, 1, SGr_List->Row, blnHoge);

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：材料証明用StringGridの表示順（３種類）をクリックしたときに発生します。
//
//  機能説明
//    材料証明用StringGridの表示順を変更します
//      ・測定項目マスター順
//      ・測定項目名称順
//      ・測定機器・測定項目名称順
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
void __fastcall TForm4::Rdo_List2_OrderClick(TObject *Sender)
{
    int				i, k, m;
	AnsiString		sBuf;
	TRadioButton	*rdo = (TRadioButton *)Sender;
    bool blnHoge=true;

    if( rdo->Name == "Rdo_List2_Order1" ){
	    // 表示順でソートを行ないます
		for( i = 1; i < SGr_List2->RowCount - 2; i++ ){
	    	for( k = i + 1; k < SGr_List2->RowCount - 1; k++ ) {
	            if( SGr_List2->Cells[14][i].ToIntDef(0) > SGr_List2->Cells[14][k].ToIntDef(0) ){
                    sBuf = GridLineCopy( SGr_List2, i);
					for( m = 1; m < SGr_List2->ColCount; m++ ) {
						SGr_List2->Cells[m][i] = SGr_List2->Cells[m][k];
                    }
                    GridLinePaste( SGr_List2, k, sBuf);
	            }
			}
    	}

	} else {
	    if( rdo->Name == "Rdo_List2_Order2" ){

		    // 測定項目順でソートを行ないます
			for( i = 1; i < SGr_List2->RowCount - 2; i++ ){
		    	for( k = i + 1; k < SGr_List2->RowCount - 1; k++ ) {
		            if( SGr_List2->Cells[1][i] > SGr_List2->Cells[1][k] ){
	                    sBuf = GridLineCopy( SGr_List2, i);
						for( m = 1; m < SGr_List2->ColCount; m++ ) {
							SGr_List2->Cells[m][i] = SGr_List2->Cells[m][k];
	                    }
	                    GridLinePaste( SGr_List2, k, sBuf);
		            }
				}
	    	}
		} else {

		    // 測定機器・測定項目順でソートを行ないます
			for( i = 1; i < SGr_List2->RowCount - 2; i++ ){
		    	for( k = i + 1; k < SGr_List2->RowCount - 1; k++ ) {
		            if( SGr_List2->Cells[15][i].ToIntDef(0) > SGr_List2->Cells[15][k].ToIntDef(0) ){
	                    sBuf = GridLineCopy( SGr_List2, i);
						for( m = 1; m < SGr_List2->ColCount; m++ ) {
							SGr_List2->Cells[m][i] = SGr_List2->Cells[m][k];
	                    }
	                    GridLinePaste( SGr_List2, k, sBuf);
		            } else {
		            	if( SGr_List2->Cells[15][i] == SGr_List2->Cells[15][k] &&
                        	SGr_List2->Cells[1][i] > SGr_List2->Cells[1][k] ){
	                    	sBuf = GridLineCopy( SGr_List2, i);
							for( m = 1; m < SGr_List2->ColCount; m++ ) {
								SGr_List2->Cells[m][i] = SGr_List2->Cells[m][k];
	                    	}
	                    	GridLinePaste( SGr_List2, k, sBuf);
						}
                    }
				}
	    	}
        }
    }
	SGr_ListSelectCell( SGr_List2, 1, SGr_List2->Row, blnHoge);

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：StringGridの指定行をバッファに保存します
//
//  機能説明
//    StringGridの指定行をバッファに保存します
//
//  パラメタ説明
//    TStringGrid* sg	：呼び出し元のTStringGridオブジェクト
//    int iCpyIndex		：複写する行NO
//
//  戻り値
//    AnsiString		：更新フラグ（複写した行が更新済みかどうか）
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm4::GridLineCopy( TStringGrid* sg, int iCpyIndex)
{
	AnsiString sBuf;

	sBuf = sg->Cells[1][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KOMK_NM	,sBuf.c_str() );	//測定項目（日本語）
	sBuf = sg->Cells[2][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KOMK_ENG	,sBuf.c_str() );	//測定項目（英語）
	sBuf = sg->Cells[3][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKI_NM	,sBuf.c_str() );	//測定機器名称
	sBuf = sg->Cells[4][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.TANI		,sBuf.c_str() );	//単位
	sBuf = sg->Cells[6][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.SOKU_SU	,sBuf.c_str() );	//ｎ数（基本）
	sBuf = sg->Cells[7][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.VALUE_TYPE	,sBuf.c_str() );	//値表現
	sBuf = sg->Cells[8][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.SOKU_FLG	,sBuf.c_str() );	//測定項目の有無
	sBuf = sg->Cells[9][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.TOKU_FLG	,sBuf.c_str() );	//特別項目の有無
	sBuf = sg->Cells[10][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.UPDYMD		,sBuf.c_str() );	//変更日
	sBuf = sg->Cells[12][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.UPDCHR		,sBuf.c_str() );	//更新者（担当者コード）
	sBuf = sg->Cells[11][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.UPDNAM		,sBuf.c_str() );	//更新者（名称）
	sBuf = sg->Cells[13][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KOMK_NO	,sBuf.c_str() );	//項目NO
	sBuf = sg->Cells[14][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.ORDER_NO	,sBuf.c_str() );	//表示順
	sBuf = sg->Cells[15][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKI_NO	,sBuf.c_str() );	//測定機器NO
	sBuf = sg->Cells[16][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKA_TYPE	,sBuf.c_str() );	//規格タイプ
	sBuf = sg->Cells[17][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKA_KIND	,sBuf.c_str() );	//規格種類
	sBuf = sg->Cells[18][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKA_DECI	,sBuf.c_str() );	//規格小数点以下桁数
	sBuf = sg->Cells[19][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKA_NUM1	,sBuf.c_str() );	//規格値１
	sBuf = sg->Cells[20][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKA_NUM2	,sBuf.c_str() );	//規格値２
	sBuf = sg->Cells[21][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKA_NUM3	,sBuf.c_str() );	//規格値３
	sBuf = sg->Cells[22][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKA_STR	,sBuf.c_str() );	//規格文字
	sBuf = sg->Cells[23][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKA_PRT	,sBuf.c_str() );	//上限下限値の印刷
	sBuf = sg->Cells[24][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.VALUE_DECI	,sBuf.c_str() );	//測定値小数点以下桁数
	sBuf = sg->Cells[25][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.ADDYMD		,sBuf.c_str() );	//登録日
	sBuf = sg->Cells[26][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.ADDTIM		,sBuf.c_str() );	//登録時間
	sBuf = sg->Cells[27][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.UPDTIM		,sBuf.c_str() );	//更新時間
	sBuf = sg->Cells[28][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.UPDCNT		,sBuf.c_str() );	//更新回数
	sBuf = sg->Cells[29][iCpyIndex];						//更新フラグ
	
	return sBuf;	// 更新フラグ
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
//    TStringGrid* sg	：呼び出し元のTStringGridオブジェクト
//    int iPstIndex		：復元する行NO
//    AnsiString sUpdFlg：復元する行に設定する更新フラグ
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm4::GridLinePaste( TStringGrid* sg, int iPstIndex, AnsiString sUpdFlg)
{

	sg->Cells[1][iPstIndex] = tmpKSM11_12_DATA.KOMK_NM		;	//測定項目（日本語）
	sg->Cells[2][iPstIndex] = tmpKSM11_12_DATA.KOMK_ENG		;	//測定項目（英語）
	sg->Cells[3][iPstIndex] = tmpKSM11_12_DATA.KIKI_NM		;	//測定機器名称
	sg->Cells[4][iPstIndex] = tmpKSM11_12_DATA.TANI			;	//単位
	sg->Cells[5][iPstIndex] = ""							;	//規格（基本）　※再描画する為に必要です。
	sg->Cells[6][iPstIndex] = tmpKSM11_12_DATA.SOKU_SU		;	//ｎ数（基本）
	sg->Cells[7][iPstIndex] = tmpKSM11_12_DATA.VALUE_TYPE	;	//値表現
	sg->Cells[8][iPstIndex] = tmpKSM11_12_DATA.SOKU_FLG		;	//測定項目の有無
	sg->Cells[9][iPstIndex] = tmpKSM11_12_DATA.TOKU_FLG		;	//特別項目の有無
	sg->Cells[10][iPstIndex] = tmpKSM11_12_DATA.UPDYMD		;	//変更日
	sg->Cells[11][iPstIndex] = tmpKSM11_12_DATA.UPDNAM		;	//更新者（名称）
	sg->Cells[12][iPstIndex] = tmpKSM11_12_DATA.UPDCHR		;	//更新者（担当者コード）
	sg->Cells[13][iPstIndex] = tmpKSM11_12_DATA.KOMK_NO		;	//項目NO
	sg->Cells[14][iPstIndex] = tmpKSM11_12_DATA.ORDER_NO	;	//表示順
	sg->Cells[15][iPstIndex] = tmpKSM11_12_DATA.KIKI_NO		;	//測定機器NO
	sg->Cells[16][iPstIndex] = tmpKSM11_12_DATA.KIKA_TYPE	;	//規格タイプ
	sg->Cells[17][iPstIndex] = tmpKSM11_12_DATA.KIKA_KIND	;	//規格種類
	sg->Cells[18][iPstIndex] = tmpKSM11_12_DATA.KIKA_DECI	;	//規格小数点以下桁数
	sg->Cells[19][iPstIndex] = tmpKSM11_12_DATA.KIKA_NUM1	;	//規格値１
	sg->Cells[20][iPstIndex] = tmpKSM11_12_DATA.KIKA_NUM2	;	//規格値２
	sg->Cells[21][iPstIndex] = tmpKSM11_12_DATA.KIKA_NUM3	;	//規格値３
	sg->Cells[22][iPstIndex] = tmpKSM11_12_DATA.KIKA_STR	;	//規格文字
	sg->Cells[23][iPstIndex] = tmpKSM11_12_DATA.KIKA_PRT	;	//上限下限値の印刷
	sg->Cells[24][iPstIndex] = tmpKSM11_12_DATA.VALUE_DECI	;	//測定値小数点以下桁数
	sg->Cells[25][iPstIndex] = tmpKSM11_12_DATA.ADDYMD		;	//登録日
	sg->Cells[26][iPstIndex] = tmpKSM11_12_DATA.ADDTIM		;	//登録時間
	sg->Cells[27][iPstIndex] = tmpKSM11_12_DATA.UPDTIM		;	//更新時間
	sg->Cells[28][iPstIndex] = tmpKSM11_12_DATA.UPDCNT		;	//更新回数
    if( sUpdFlg != "" ){
		sg->Cells[29][iPstIndex] = sUpdFlg				   	;	//更新フラグの設定
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
	Form3->Edt_ALLChange( Sender );
}

