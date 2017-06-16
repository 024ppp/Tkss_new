//---------------------------------------------------------------------------
//
//  UnitDataAccess.cpp
//    【出荷検査システム－備考事前登録】
//    メインフォームフォーム（ＤＢアクセス関連）（TForm1クラス）のメンバ関数の定義
//
//  作成者
//    市川　和弘
//
//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "UnitDataAccess.h"
#include "unit1.h"
#include "Unit2.h"
extern KSD91_DATA Tmp_KSD91;             // 選択した備考データ
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：KSD91構造体の初期化を行ないます
//
//  機能説明
//    KSD91構造体の初期化を行ないます
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
void  __fastcall TForm1::Tmp_KSD91_SYOKIKA(void)
{
	//Tmp_KSD91初期化
	Tmp_KSD91.KENSA_YMD	= "";		// 検査年月日
	Tmp_KSD91.DTKSHIN	= "";		// 得意先品番
	Tmp_KSD91.HINBAN	= "";		// 自社品番
	Tmp_KSD91.LOTNO		= "";		// ロットNo
	Tmp_KSD91.ADDYMD	= "";		// 登録日
	Tmp_KSD91.ADDTIM	= "";		// 登録時間
	Tmp_KSD91.UPDYMD	= "";		// 変更日
	Tmp_KSD91.UPDTIM	= "";		// 変更時間
	Tmp_KSD91.UPDCHR	= 0;		// 更新者
	Tmp_KSD91.UPDCNT	= 0;		// 更新回数
    Tmp_KSD91.MEMO      = "";       // 備考
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：テーブルKSD91へデータの登録を行ないます
//
//  機能説明
//    テーブルKSD91へデータの登録を行ないます
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    true = 成功、false = 失敗
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
     sBuf = "select * from KSD91";
     sBuf +=" WHERE DTKSHIN='" + Tmp_KSD91.DTKSHIN + "'";          // 得意先品番
     sBuf +=" AND   HINBAN ='" + Tmp_KSD91.HINBAN + "'";           // 自社品番
     sBuf +=" AND   LOTNO  ='" + Tmp_KSD91.LOTNO + "'";            // LOTNO
     sBuf +=" AND   MEMO   ='" + Tmp_KSD91.MEMO + "'";        	   // 備考
     sBuf +=" AND   ADDYMD ='" + Tmp_KSD91.ADDYMD + "'";           // 登録日
     sBuf +=" AND   ADDTIM ='" + Tmp_KSD91.ADDTIM + "'";           // 登録時間
     sBuf +=" AND   UPDYMD ='" + Tmp_KSD91.UPDYMD + "'";           // 更新日
     sBuf +=" AND   UPDTIM ='" + Tmp_KSD91.UPDTIM + "'";           // 更新時間
     sBuf +=" AND   UPDCHR ='" + IntToStr(Tmp_KSD91.UPDCHR) + "'"; // 更新担当者
     sBuf +=" AND   UPDCNT ='" + IntToStr(Tmp_KSD91.UPDCNT) + "'"; // 更新回数

     Query1->SQL->Add(sBuf);

     // 問い合せ文の実行
     try
     {
        Query1->Open();
        Query1->Active = true;

        if( !(Query1->Eof == True &&  Query1->Bof == True) ){
            SBr1->Panels->Items[0]->Text = "既に登録されています。";
            SBr1->Update();
            return(False);
        }
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }


     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ文作成
     sBuf = "insert into KSD91(";
     sBuf += " DTKSHIN, HINBAN, LOTNO, MEMO, ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT";
     sBuf += " )";

     sBuf += " VALUES('";
     sBuf += Tmp_KSD91.DTKSHIN			+ "','";	//	得意先品番
     sBuf += Tmp_KSD91.HINBAN		    + "','";	//	自社品番
     sBuf += Tmp_KSD91.LOTNO 		    + "','";	//	ロットNO
     sBuf += Tmp_KSD91.MEMO			    + "','";	//	備考
     sBuf += Tmp_KSD91.ADDYMD			+ "','";	//	登録日
     sBuf += Tmp_KSD91.ADDTIM		    + "','";	//	登録時間
     sBuf += Tmp_KSD91.UPDYMD			+ "','";	//	登録日
     sBuf += Tmp_KSD91.UPDTIM			+ "',";		//	登録時間
     sBuf += IntToStr(Tmp_KSD91.UPDCHR)	+ ",";		//	更新者
     sBuf += IntToStr(Tmp_KSD91.UPDCNT)  ;			//	更新回数
     sBuf += ")";

     Query1->SQL->Add(sBuf);

     // 問い合せ文の実行
     try
     {
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }

     return(True);

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：テーブルKSD91のレコードを更新します
//
//  機能説明
//    テーブルKSD91のレコードを更新します
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    true = 成功、false = 失敗
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::CollectData()
{
     AnsiString sBuf;

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ文作成
     sBuf = "update KSD91 set ";
	 sBuf +=	"DTKSHIN='"	+ Tmp_KSD91.DTKSHIN + "', "	;    //	得意先品番
	 sBuf +=	"HINBAN ='"	+ Tmp_KSD91.HINBAN  + "', "	;    //	自社品番
	 sBuf +=	"LOTNO  ='"	+ Tmp_KSD91.LOTNO   + "', "	;    //	ロットNO
	 sBuf +=	"MEMO   ='"	+ Tmp_KSD91.MEMO	+ "', "	;    //	備考
	 sBuf +=	"ADDYMD ='"	+ Tmp_KSD91.ADDYMD  + "', "	;    //	登録日
	 sBuf +=	"ADDTIM ='"	+ Tmp_KSD91.ADDTIM  + "', "	;    //	登録時間
	 sBuf +=	"UPDYMD ='"	+ Tmp_KSD91.UPDYMD  + "', "	;    //	更新日
	 sBuf +=	"UPDTIM ='"	+ Tmp_KSD91.UPDTIM  + "', "	;    //	更新時間
	 sBuf +=	"UPDCHR ="	+ IntToStr(Tmp_KSD91.UPDCHR) + ", "	; // 更新者
	 sBuf +=	"UPDCNT ="	+ IntToStr(Tmp_KSD91.UPDCNT) + " "	; // 更新回数

     sBuf += "WHERE DTKSHIN='" + Tmp_KSD91.DTKSHIN + "'";
     sBuf += " AND  HINBAN ='" + Tmp_KSD91.HINBAN + "'";
     sBuf += " AND  LOTNO  ='" + Tmp_KSD91.LOTNO + "'";

     Query1->SQL->Add(sBuf);

     // 問い合せ文の実行
     try
     {
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }

     return(True);

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：テーブルKSD91のレコードを削除します
//
//  機能説明
//    テーブルKSD91のレコードを削除します
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    true = 成功、false = 失敗
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
     sBuf = "select * from KSD91 ";
     sBuf +=" WHERE DTKSHIN='" + Tmp_KSD91.DTKSHIN + "'";        // 得意先品番
     sBuf +=" AND   HINBAN ='" + Tmp_KSD91.HINBAN  + "'";        // 自社品番
     sBuf +=" AND   LOTNO  ='" + Tmp_KSD91.LOTNO   + "'";        // LOTNO

     Query1->SQL->Add(sBuf);

     // 問い合せ文の実行
     try
     {
        Query1->Open();
        Query1->Active = true;

        if( Query1->Eof == True &&  Query1->Bof == True )
        {
            SBr1->Panels->Items[0]->Text = "該当のデータが見つかりません。削除できませんでした。";
            SBr1->Update();
            return(False);
        }
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ文作成
     sBuf = "DELETE from KSD91";
     sBuf +=" WHERE DTKSHIN='" + Tmp_KSD91.DTKSHIN + "'";      	// DTKSHIN
     sBuf +=" AND HINBAN='" + Tmp_KSD91.HINBAN + "'";      		// HINBAN
     sBuf +=" AND LOTNO='" + Tmp_KSD91.LOTNO + "'";      		// LOTNO


     Query1->SQL->Add(sBuf);

     // 問い合せ文の実行
     try
     {
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     return(True);

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：テーブルKSD91のレコード検索処理を開始します
//
//  機能説明
//    テーブルKSD91のレコード検索処理を開始します
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    1 = 成功、0 = 失敗
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
int __fastcall TForm1::MAIN_Serch01(void)
{
    // 新しいトランザクションを開始
    if( Database1->InTransaction == false )
    {
        Database1->StartTransaction();
        DataSave = false;
    }

    if ( KSD91_Serch01() == 0)
    {
       return(0);
    }
    return(1);
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：テーブルKSD91のレコードを検索します
//
//  機能説明
//    テーブルKSD91のレコードを検索します
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    1 = 成功、0 = 失敗
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
int __fastcall TForm1::KSD91_Serch01(void)
{
	int iRow;
	AnsiString sBuf;
	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();
	Query3->Close();
	Query3->SQL->Clear();

	// 問合せ実行
	// 検索方法①
	sBuf = "SELECT KSD91.DTKSHIN, KSD91.LOTNO, KSD91.MEMO, KSD91.UPDYMD, KSD91.UPDCHR,";
    sBuf += " KSD91.ADDYMD, KSD91.ADDTIM, KSD91.UPDTIM, KSD91.UPDCNT, SM12S.TANNAM, KSD91.HINBAN";
    sBuf += " FROM KSD91";
    sBuf += " LEFT JOIN SM12S ON KSD91.UPDCHR = SM12S.TANSYA";

	//sBuf += " WHERE KSD91.DTKSHIN LIKE '" + Form1->EdtHIN->Text + "%'";
	//sBuf += " AND   KSD91.LOTNO   LIKE '" + Form1->EdtLOT->Text + "%'";
	sBuf += " WHERE KSD91.DTKSHIN = '" + Form1->EdtHIN->Text + "'";
	sBuf += " AND   KSD91.LOTNO   LIKE '" + Form1->EdtLOT->Text + "%'";
	sBuf += " ORDER BY KSD91.DTKSHIN, KSD91.HINBAN, SUBSTR(KSD91.LOTNO,2)";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	if ( Query1->Bof == true && Query1->Eof ) {
		//検索結果 ０件
		return(0);
	}
	iRow = 1;

	while( !Query1->Eof ){

		// グリッドの最大行数が超えていないかチェックする
		if( iRow >= SGr_List->RowCount ){
			SGr_List->RowCount = iRow + 1;
		}

		// グリッドにデータをセットします。
		sBuf = iRow ;
		SGr_List->Cells[0][iRow] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;    //No
		sBuf = iRow + 1;

		sBuf = Form1->Query1->FieldValues["DTKSHIN"];
		SGr_List->Cells[1][iRow] = sBuf;   //得意先品番

		sBuf = Form1->Query1->FieldValues["LOTNO"];
		SGr_List->Cells[2][iRow] = sBuf;   //ロットNO

        if( VarIsNull(Form1->Query1->FieldValues["MEMO"]) ){
			sBuf = "";
		} else{
			sBuf = Form1->Query1->FieldValues["MEMO"];
		}
		SGr_List->Cells[3][iRow] =  sBuf;   //備考

        if( VarIsNull(Form1->Query1->FieldValues["UPDYMD"]) ){
			sBuf = "";
		} else{
			sBuf = Form1->Query1->FieldValues["UPDYMD"];
		}
        sBuf = sBuf.Insert("/",5);
        sBuf = sBuf.Insert("/",8);
        SGr_List->Cells[4][iRow] = sBuf;   //変更日

		sBuf = Form1->Query1->FieldValues["UPDCHR"];
		SGr_List->Cells[6][iRow] = sBuf;   //更新者(担当者コード)

        if( VarIsNull(Form1->Query1->FieldValues["TANNAM"]) ){
			sBuf = "";
		} else{
			sBuf = Form1->Query1->FieldValues["TANNAM"];
		}
		SGr_List->Cells[5][iRow] = sBuf;   //更新者(担当者名)

        if( VarIsNull(Form1->Query1->FieldValues["ADDYMD"]) ){
			sBuf = "";
		} else{
			sBuf = Form1->Query1->FieldValues["ADDYMD"];
		}
		SGr_List->Cells[7][iRow] = sBuf;   //登録日

        if( VarIsNull(Form1->Query1->FieldValues["ADDTIM"]) ){
			sBuf = "";
		} else{
			sBuf = Form1->Query1->FieldValues["ADDTIM"];
		}
		SGr_List->Cells[8][iRow] =  sBuf;   //登録時間

        if( VarIsNull(Form1->Query1->FieldValues["UPDTIM"]) ){
			sBuf = "";
		} else{
			sBuf = Form1->Query1->FieldValues["UPDTIM"];
		}
		SGr_List->Cells[9][iRow] = sBuf;   //更新時間

		sBuf = Form1->Query1->FieldValues["UPDCNT"];
		SGr_List->Cells[10][iRow] = sBuf;   //更新回数

        if( VarIsNull(Form1->Query1->FieldValues["HINBAN"]) ){
			sBuf = "";
		} else{
			sBuf = Form1->Query1->FieldValues["HINBAN"];
		}
		SGr_List->Cells[11][iRow] = sBuf;   //自社品番

		// カーソルを次にセットする
		Query1->Next();

		iRow += 1;
	}

    SGr_List->RowCount = iRow + 1;
    SGr_List->Cells[0][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[1][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[2][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[3][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[4][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[5][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[6][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[7][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[8][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[9][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[10][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[11][SGr_List->RowCount - 1 ] = "";

	// 最新の自社品番
	sBuf = "SELECT MAX(HINBAN) HINBAN FROM SD21S";
	sBuf += " WHERE DTKSHIN = '" + Form1->EdtHIN->Text + "'";

	Query3->SQL->Add(sBuf);
	Query3->Open();
	Query3->Active = true;

	if ( !Query3->Eof ) {
        if( VarIsNull(Form1->Query3->FieldValues["HINBAN"]) ){
			sBuf = "";
		} else{
			sBuf = Form1->Query3->FieldValues["HINBAN"];
		}
        Form1->EdtMAXBAN->Text = sBuf;   //自社品番
	}

	return(1);
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：テーブルKSD91のレコードをチェックします
//
//  機能説明
//    テーブルKSD91に指定されたレコードが存在するかどうかチェックします
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    1 = 成功、0 = 失敗
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
//  KSD91から２重登録の確認
bool __fastcall TForm1::KSD91_Serch02(void)
{
	AnsiString sBuf;
	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	sBuf = "SELECT DTKSHIN,LOTNO FROM KSD91";
	sBuf += " WHERE DTKSHIN ='" + Form1->EdtSETHIN->Text + "'";
	sBuf += " AND   HINBAN  ='" + Form1->EdtSETBAN->Text + "'";
	sBuf += " AND   LOTNO   ='" + Form1->EdtSETLOT->Text + "'";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	if ( Query1->Eof == false ){
		return(false);
	}
    else {
        return(true);
    }
}





