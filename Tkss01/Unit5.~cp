//---------------------------------------------------------------------------
//
//  Unit5.cpp
//    【出荷検査システム－検査測定】
//    素材検査項目フォーム（TForm5クラス）のメンバ関数の定義
//
//  作成者
//    田村　敦司
//
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit3.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NumberEdit"
#pragma resource "*.dfm"
TForm5 *Form5;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
        : TForm(Owner)
{
}

//---------------------------------------------------------------------------
//
//  概要
//    OnCreateイベント	：Form5を作成したときに発生します。
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
void __fastcall TForm5::FormCreate(TObject *Sender)
{

	int				i, k;
    TStringGrid*	sg;

    for( i=1; i<=6; i++ ){
    	switch( i ){
        	case 1:	sg = dynamic_cast<TStringGrid*>(SGr_List1);
            		break;
        	case 2:	sg = dynamic_cast<TStringGrid*>(SGr_List2);
            		break;
        	case 3:	sg = dynamic_cast<TStringGrid*>(SGr_List3);
            		break;
        	case 4:	sg = dynamic_cast<TStringGrid*>(SGr_List4);
            		break;
        	case 5:	sg = dynamic_cast<TStringGrid*>(SGr_List5);
            		break;
        	case 6:	sg = dynamic_cast<TStringGrid*>(SGr_List6);
            		break;
        }

		// タイトルをセット
		sg->ColCount = 23;
		sg->Cells[0][0] = " NO";
		sg->Cells[1][0] = "測定項目";
		sg->Cells[2][0] = "測定機器";
		sg->Cells[3][0] = "単位";
		sg->Cells[4][0] = "規格";
		sg->Cells[5][0] = "n数";
		sg->ColWidths[0] = 25;
		sg->ColWidths[1] = 160;
		sg->ColWidths[2] = 140;
		sg->ColWidths[3] = 60;
		sg->ColWidths[4] = 140;
		sg->ColWidths[5] = 25;
	    for( k=6; k<sg->ColCount; k++ ){
			sg->ColWidths[k] = 0;
        }
    }

    // コントロールの再配置
    Pnl_KIKAKU_KIJYUN->Left = Pnl_KIKAKU_HANI->Left;

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
void __fastcall TForm5::FormActivate(TObject *Sender)
{

	int			i, k;
	AnsiString	sBuf;
	AnsiString	sWhereIN;
    AnsiString	sDTKSHIN;
    bool blnHoge=true;


    sWhereIN = "";

	// 素材用品番で指定された品番を取得しタブを設定します
    Form5->Tag = 1;
    Rdo_SOZAI_SELECT1->Checked = true;
    Rdo_SOZAI_SELECT2->Checked = true;
    Rdo_SOZAI_SELECT3->Checked = true;
    Rdo_SOZAI_SELECT4->Checked = true;
    Rdo_SOZAI_SELECT5->Checked = true;
    Rdo_SOZAI_SELECT6->Checked = true;
    PgCtr_List->ActivePage = TabSheet1;
    for( i=1; i<=Form3->Lbx_DTKSHIN_SZ->Items->Count; i++ ) {
        sBuf = Form3->Lbx_DTKSHIN_SZ->Items->Strings[i-1];
		if( i == 1 ){
        				TabSheet1->Caption = sBuf;
						TabSheet1->TabVisible = true;
		}
        if( i == 2 ){
        				TabSheet2->Caption = sBuf;
						TabSheet2->TabVisible = true;
		}
        if( i == 3 ){
        				TabSheet3->Caption = sBuf;
						TabSheet3->TabVisible = true;
		}
        if( i == 4 ){
        				TabSheet4->Caption = sBuf;
						TabSheet4->TabVisible = true;
		}
        if( i == 5 ){
        				TabSheet5->Caption = sBuf;
						TabSheet5->TabVisible = true;
		}if( i == 6 ){
        				TabSheet6->Caption = sBuf;
						TabSheet6->TabVisible = true;
        }
        if( sWhereIN != "")	sWhereIN = sWhereIN + ", ";
	    sWhereIN = sWhereIN + "'" + sBuf + "'";
    }
    // 利用しないタブを隠します
    for( i=Form3->Lbx_DTKSHIN_SZ->Items->Count + 1; i<=6; i++ ) {
		if( i == 1 )	TabSheet1->TabVisible = false;
		if( i == 2 )	TabSheet2->TabVisible = false;
		if( i == 3 )	TabSheet3->TabVisible = false;
		if( i == 4 )	TabSheet4->TabVisible = false;
		if( i == 5 )	TabSheet5->TabVisible = false;
		if( i == 6 )	TabSheet6->TabVisible = false;
    }
    Form5->Tag = 0;


    //----------------------------------------------
    // 素材製品規格マスター検索

	// Initial Query
	Form3->Query1->Close();
	Form3->Query1->SQL->Clear();

	// 問合せ実行（素材製品規格マスター）
	sBuf  = "SELECT *";
    sBuf += " FROM KM02";
    sBuf += " WHERE DTKSHIN IN( " + sWhereIN + ")";
    sBuf += " AND REVCNT=0";
    sBuf += " ORDER BY DTKSHIN";

	Form3->Query1->SQL->Add(sBuf);
	Form3->Query1->Open();
	Form3->Query1->Active = true;

    if( !Form3->Query1->Eof ){

        // メモリ確保数を取得
		iKSM13_DATA_SEL_Cnt = Form3->Query1->RecordCount * 20;

    	// メモリ確保
    	hMemKSM13_DATA_SEL = GlobalAlloc( GHND, sizeof(struct KSM13_DATA) * iKSM13_DATA_SEL_Cnt );
    	if( hMemKSM13_DATA_SEL == NULL ){
        	Beep();
    		MessageDlg("メモリ領域を確保できません。(01)", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        	return;
    	}
    	pKSM13_DATA_SEL = (struct KSM13_DATA *)GlobalLock(hMemKSM13_DATA_SEL);
    	if( hMemKSM13_DATA_SEL == NULL ){
        	Beep();
    		MessageDlg("メモリ領域を確保できません。(02)", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        	return;
	    }
    }

    i = 0;
	while( !Form3->Query1->Eof ){

       	if( VarIsNull(Form3->Query1->FieldValues["DTKSHIN"]) ){
			sDTKSHIN = "";
		} else{
			sDTKSHIN = Form3->Query1->FieldValues["DTKSHIN"];			// 代表得意先品番
		}

        // リード線長さ
		sBuf = Form3->Query1->FieldValues["SK_LD_LNG"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// 代表得意先品番
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// 項目NO
            sBuf = "11";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// 表示順
            sBuf = "リード線長さ";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// 測定項目（日本語）
            sBuf = "L/W Length";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// 測定項目（英語）
            sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// 測定機器NO
            sBuf = "ノギス";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// 測定機器名称
            sBuf = "mm";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// 単位
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// 規格タイプ
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// 規格種類
            sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// 規格小数点以下桁数
			sBuf = Form3->Query1->FieldValues["LD_LNG_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// 規格値１
			sBuf = Form3->Query1->FieldValues["LD_LNG_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// 規格値２
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// 規格値３
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// 規格文字
			sBuf = Form3->Query1->FieldValues["SK_LD_LNG"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// 測定指示n数
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// 値表現
            sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// 測定値小数点以下桁数
			i++;
        }

        // ブラシ幅（コンミ：内径）
		sBuf = Form3->Query1->FieldValues["SK_BURASI"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// 代表得意先品番
            if( AnsiString(Form3->Query1->FieldValues["KEIJKBN"]) != "5" ){
            	sBuf = "2";
				strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// 項目NO
                sBuf = "12";
				strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// 表示順
            	sBuf = "ブラシ幅";
				strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// 測定項目（日本語）
            	sBuf = "Brush Width";
				strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// 測定項目（英語）
            } else {
            	sBuf = "3";
				strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// 項目NO
				sBuf = "14";
				strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// 表示順
            	sBuf = "内径";
				strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// 測定項目（日本語）
            	sBuf = "";
				strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// 測定項目（英語）
            }
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// 測定機器NO
            sBuf = "マイクロメータ";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// 測定機器名称
            sBuf = "mm";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// 単位
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// 規格タイプ
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// 規格種類
            sBuf = "3";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// 規格小数点以下桁数
			sBuf = Form3->Query1->FieldValues["BURASI_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// 規格値１
			sBuf = Form3->Query1->FieldValues["BURASI_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// 規格値２
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// 規格値３
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// 規格文字
			sBuf = Form3->Query1->FieldValues["SK_BURASI"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// 測定指示n数
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// 値表現
            sBuf = "3";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// 測定値小数点以下桁数
			i++;
        }

        // ブラシ幅縦押し（コンミ：外径）
		sBuf = Form3->Query1->FieldValues["SK_BURASIT"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// 代表得意先品番
            if( AnsiString(Form3->Query1->FieldValues["KEIJKBN"]) != "5" ){
            	sBuf = "4";
				strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// 項目NO
				sBuf = "13";
				strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// 表示順
            	sBuf = "ブラシ幅 (縦押し)";
				strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// 測定項目（日本語）
            	sBuf = "Brush Width A";
				strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// 測定項目（英語）
            } else {
            	sBuf = "5";
				strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// 項目NO
				sBuf = "15";
				strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// 表示順
            	sBuf = "外径";
				strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// 測定項目（日本語）
            	sBuf = "";
				strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// 測定項目（英語）
            }
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// 測定機器NO
            sBuf = "マイクロメータ";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// 測定機器名称
            sBuf = "mm";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// 単位
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// 規格タイプ
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// 規格種類
            sBuf = "3";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// 規格小数点以下桁数
			sBuf = Form3->Query1->FieldValues["BURASIT_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// 規格値１
			sBuf = Form3->Query1->FieldValues["BURASIT_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// 規格値２
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// 規格値３
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// 規格文字
			sBuf = Form3->Query1->FieldValues["SK_BURASIT"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// 測定指示n数
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// 値表現
            sBuf = "3";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// 測定値小数点以下桁数
			i++;
        }

        // 見掛比重
		sBuf = Form3->Query1->FieldValues["SK_BOTAI"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// 代表得意先品番
            sBuf = "6";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// 項目NO
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// 表示順
           	sBuf = "見掛比重";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// 測定項目（日本語）
           	sBuf = "Apparent Density";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// 測定項目（英語）
            sBuf = "3";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// 測定機器NO
            sBuf = "マイクロメータ､天秤";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// 測定機器名称
            sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// 単位
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// 規格タイプ
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// 規格種類
            sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// 規格小数点以下桁数
			sBuf = Form3->Query1->FieldValues["BOTAI_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// 規格値１
			sBuf = Form3->Query1->FieldValues["BOTAI_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// 規格値２
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// 規格値３
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// 規格文字
			sBuf = Form3->Query1->FieldValues["SK_BOTAI"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// 測定指示n数
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// 値表現
            sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// 測定値小数点以下桁数
			i++;
        }

        // リード線取付強度
		sBuf = Form3->Query1->FieldValues["SK_LD_HP"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// 代表得意先品番
            sBuf = "7";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// 項目NO
			sBuf = "10";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// 表示順
           	sBuf = "リード線取付強度";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// 測定項目（日本語）
           	sBuf = "Pull Strength";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// 測定項目（英語）
            sBuf = "5";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// 測定機器NO
            sBuf = "材料試験機";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// 測定機器名称
			sBuf = Form3->Query1->FieldValues["LD_HP_TAN"];
            switch( sBuf.ToIntDef(1) ){
            	case 1:	sBuf = "kgf";	break;
                case 2:	sBuf = "N"	;	break;
                case 3:	sBuf = "MPa";	break;
            }
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// 単位
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// 規格タイプ
            sBuf = "3";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// 規格種類
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// 規格小数点以下桁数
			sBuf = Form3->Query1->FieldValues["LD_HP_KYO"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// 規格値１
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// 規格値２
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// 規格値３
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// 規格文字
			sBuf = Form3->Query1->FieldValues["SK_LD_HP"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// 測定指示n数
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// 値表現
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// 測定値小数点以下桁数
			i++;
        }

        // リード線取付抵抗
		sBuf = Form3->Query1->FieldValues["SK_LD_TR"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// 代表得意先品番
            sBuf = "8";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// 項目NO
			sBuf = "9";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// 表示順
           	sBuf = "リード線取付抵抗";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// 測定項目（日本語）
           	sBuf = "Connection Drop";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// 測定項目（英語）
            sBuf = "12";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// 測定機器NO
            sBuf = "リード線取付抵抗測定機";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// 測定機器名称
            sBuf = "mV/" + Form3->Query1->FieldValues["LD_TR_DENR"] + "A";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// 単位
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// 規格タイプ
            sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// 規格種類
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// 規格小数点以下桁数
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// 規格値１
			sBuf = Form3->Query1->FieldValues["LD_TR_DENA"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// 規格値２
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// 規格値３
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// 規格文字
			sBuf = Form3->Query1->FieldValues["SK_LD_TR"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// 測定指示n数
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// 値表現
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// 測定値小数点以下桁数
			i++;
        }

        // 抵抗率
		sBuf = Form3->Query1->FieldValues["SK_KOYU"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// 代表得意先品番
            sBuf = "9";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// 項目NO
			sBuf = "6";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// 表示順
           	sBuf = "抵抗率";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// 測定項目（日本語）
           	sBuf = "Specific Resistance";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// 測定項目（英語）
            sBuf = "11";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// 測定機器NO
            sBuf = "抵抗率測定機";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// 測定機器名称
            sBuf = "μΩ･cm";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// 単位
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// 規格タイプ
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// 規格種類
            sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// 規格小数点以下桁数
			sBuf = Form3->Query1->FieldValues["KOYU_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// 規格値１
			sBuf = Form3->Query1->FieldValues["KOYU_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// 規格値２
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// 規格値３
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// 規格文字
			sBuf = Form3->Query1->FieldValues["SK_KOYU"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// 測定指示n数
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// 値表現
            sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// 測定値小数点以下桁数
			i++;
        }

        // 曲げ強さ
		sBuf = Form3->Query1->FieldValues["SK_MAGE"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// 代表得意先品番
            sBuf = "10";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// 項目NO
			sBuf = "7";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// 表示順
           	sBuf = "曲げ強さ";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// 測定項目（日本語）
           	sBuf = "Transverse Strength";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// 測定項目（英語）
            sBuf = "5";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// 測定機器NO
            sBuf = "材料試験機";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// 測定機器名称
			sBuf = Form3->Query1->FieldValues["MAGE_TAN"];
            switch( sBuf.ToIntDef(1) ){
            	case 1:	sBuf = "kgf/c㎡";	break;
                case 2:	sBuf = "N/c㎡"	;	break;
                case 3:	sBuf = "MPa"	;	break;
                case 4:	sBuf = "N/m㎡"	;	break;
            }
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// 単位
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// 規格タイプ
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// 規格種類
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// 規格小数点以下桁数
			sBuf = Form3->Query1->FieldValues["MAGE_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// 規格値１
			sBuf = Form3->Query1->FieldValues["MAGE_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// 規格値２
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// 規格値３
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// 規格文字
			sBuf = Form3->Query1->FieldValues["SK_MAGE"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// 測定指示n数
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// 値表現
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// 測定値小数点以下桁数
			i++;
        }

        // 曲げ強さ（現物）
		sBuf = Form3->Query1->FieldValues["SK_MAGEG"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// 代表得意先品番
            sBuf = "11";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// 項目NO
			sBuf = "8";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// 表示順
           	sBuf = "曲げ強さ (現物)";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// 測定項目（日本語）
           	sBuf = "Transverse Strength(Genuine)";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// 測定項目（英語）
            sBuf = "5";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// 測定機器NO
            sBuf = "材料試験機";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// 測定機器名称
			sBuf = Form3->Query1->FieldValues["MAGE_TAN"];
            switch( sBuf.ToIntDef(1) ){
            	case 1:	sBuf = "kgf/c㎡";	break;
                case 2:	sBuf = "N/c㎡"	;	break;
                case 3:	sBuf = "MPa"	;	break;
                case 4:	sBuf = "N/m㎡"	;	break;
            }
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// 単位
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// 規格タイプ
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// 規格種類
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// 規格小数点以下桁数
			sBuf = Form3->Query1->FieldValues["MAGEG_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// 規格値１
			sBuf = Form3->Query1->FieldValues["MAGEG_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// 規格値２
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// 規格値３
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// 規格文字
			sBuf = Form3->Query1->FieldValues["SK_MAGEG"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// 測定指示n数
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// 値表現
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// 測定値小数点以下桁数
			i++;
        }

        // 硬度ＨｓＣ（圧面）
		sBuf = Form3->Query1->FieldValues["SK_HSC_A"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// 代表得意先品番
            sBuf = "12";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// 項目NO
			sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// 表示順
           	sBuf = "硬度 (HsC 圧面)";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// 測定項目（日本語）
           	sBuf = "Hardness(HsC P)";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// 測定項目（英語）
            sBuf = "9";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// 測定機器NO
            sBuf = "ショア硬度計Ｃ型";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// 測定機器名称
            sBuf = "HsC";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// 単位
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// 規格タイプ
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// 規格種類
            sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// 規格小数点以下桁数
			sBuf = Form3->Query1->FieldValues["HSC_A_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// 規格値１
			sBuf = Form3->Query1->FieldValues["HSC_A_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// 規格値２
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// 規格値３
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// 規格文字
			sBuf = Form3->Query1->FieldValues["SK_HSC_A"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// 測定指示n数
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// 値表現
            sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// 測定値小数点以下桁数
			i++;
        }

        // 硬度ＨｓＣ（側面）
		sBuf = Form3->Query1->FieldValues["SK_HSC_S"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// 代表得意先品番
            sBuf = "13";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// 項目NO
			sBuf = "3";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// 表示順
           	sBuf = "硬度 (HsC 側面)";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// 測定項目（日本語）
           	sBuf = "Hardness(HsC S)";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// 測定項目（英語）
            sBuf = "9";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// 測定機器NO
            sBuf = "ショア硬度計Ｃ型";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// 測定機器名称
            sBuf = "HsC";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// 単位
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// 規格タイプ
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// 規格種類
            sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// 規格小数点以下桁数
			sBuf = Form3->Query1->FieldValues["HSC_S_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// 規格値１
			sBuf = Form3->Query1->FieldValues["HSC_S_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// 規格値２
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// 規格値３
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// 規格文字
			sBuf = Form3->Query1->FieldValues["SK_HSC_S"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// 測定指示n数
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// 値表現
            sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// 測定値小数点以下桁数
			i++;
        }


        // 硬度ＨｓＤ（圧面）
		sBuf = Form3->Query1->FieldValues["SK_HSD_A"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// 代表得意先品番
            sBuf = "14";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// 項目NO
			sBuf = "4";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// 表示順
           	sBuf = "硬度 (HsD 圧面)";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// 測定項目（日本語）
           	sBuf = "Hardness(HsD P)";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// 測定項目（英語）
            sBuf = "10";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// 測定機器NO
            sBuf = "ショア硬度計Ｄ型";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// 測定機器名称
            sBuf = "HsD";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// 単位
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// 規格タイプ
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// 規格種類
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// 規格小数点以下桁数
			sBuf = Form3->Query1->FieldValues["HSD_A_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// 規格値１
			sBuf = Form3->Query1->FieldValues["HSD_A_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// 規格値２
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// 規格値３
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// 規格文字
			sBuf = Form3->Query1->FieldValues["SK_HSD_A"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// 測定指示n数
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// 値表現
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// 測定値小数点以下桁数
			i++;
        }

        // 硬度ＨｓＤ（側面）
		sBuf = Form3->Query1->FieldValues["SK_HSD_S"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// 代表得意先品番
            sBuf = "15";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// 項目NO
			sBuf = "5";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// 表示順
           	sBuf = "硬度 (HsD 側面)";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// 測定項目（日本語）
           	sBuf = "Hardness(HsD S)";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// 測定項目（英語）
            sBuf = "10";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// 測定機器NO
            sBuf = "ショア硬度計Ｄ型";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// 測定機器名称
            sBuf = "HsD";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// 単位
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// 規格タイプ
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// 規格種類
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// 規格小数点以下桁数
			sBuf = Form3->Query1->FieldValues["HSD_S_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// 規格値１
			sBuf = Form3->Query1->FieldValues["HSD_S_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// 規格値２
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// 規格値３
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// 規格文字
			sBuf = Form3->Query1->FieldValues["SK_HSD_S"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// 測定指示n数
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// 値表現
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// 測定値小数点以下桁数
			i++;
        }

        // 座屈
		sBuf = Form3->Query1->FieldValues["SK_ZAKUT"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// 代表得意先品番
            sBuf = "16";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// 項目NO
			sBuf = "16";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// 表示順
           	sBuf = "座屈";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// 測定項目（日本語）
           	sBuf = "Crackforce";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// 測定項目（英語）
            sBuf = "5";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// 測定機器NO
            sBuf = "材料試験機";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// 測定機器名称
            sBuf = "N";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// 単位
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// 規格タイプ
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// 規格種類
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// 規格小数点以下桁数
			sBuf = Form3->Query1->FieldValues["ZAKUT_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// 規格値１
			sBuf = Form3->Query1->FieldValues["ZAKUT_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// 規格値２
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// 規格値３
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// 規格文字
			sBuf = Form3->Query1->FieldValues["SK_ZAKUT"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// 測定指示n数
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// 値表現
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// 測定値小数点以下桁数
			i++;
        }

        // ヒストグラム
		sBuf = Form3->Query1->FieldValues["HIST_SOKUT"];
        if( sBuf.ToIntDef(0) > 0 ){
            // ブラシ厚さ（min、max）
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// 代表得意先品番
            sBuf = "17";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// 項目NO
			sBuf = "17";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// 表示順
           	sBuf = "ブラシ厚さ";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// 測定項目（日本語）
           	sBuf = "Brush Thickness";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// 測定項目（英語）
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// 測定機器NO
            sBuf = "マイクロメータ";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// 測定機器名称
            sBuf = "mm";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// 単位
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// 規格タイプ
            sBuf = Form3->Query1->FieldValues["HIST_KIKAK"];
            switch( sBuf.ToIntDef(1) ){
            	case 1:	sBuf = "1";		break;		// 両側規格
                case 2:	sBuf = "3";		break;		// 下限規格
                case 3:	sBuf = "2";		break;		// 上限規格
            }
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// 規格種類
            sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// 規格小数点以下桁数
			sBuf = Form3->Query1->FieldValues["HIST_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// 規格値１
			sBuf = Form3->Query1->FieldValues["HIST_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// 規格値２
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// 規格値３
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// 規格文字
			sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// 測定指示n数
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// 値表現
            sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// 測定値小数点以下桁数
			i++;

            // ブラシ厚さ（Cp、Cpk）
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// 代表得意先品番
            sBuf = "18";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// 項目NO
			sBuf = "18";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// 表示順
           	sBuf = "ブラシ厚さ";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// 測定項目（日本語）
           	sBuf = "Brush Thickness";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// 測定項目（英語）
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// 測定機器NO
            sBuf = "マイクロメータ";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// 測定機器名称
            sBuf = "Cpk";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// 単位
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// 規格タイプ
          	sBuf = "3";
            strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// 規格種類
            sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// 規格小数点以下桁数
			sBuf = "1.33";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// 規格値１
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// 規格値２
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// 規格値３
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// 規格文字
			sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// 測定指示n数
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// 値表現
            sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// 測定値小数点以下桁数
			i++;
        }

		// カーソルを次にセットする
		Form3->Query1->Next();

	}

    // 再度検査項目数を設定します
    iKSM13_DATA_SEL_Cnt = i;

    // 表示順でソートを行ないます
	for( i = 0; i < iKSM13_DATA_SEL_Cnt - 1; i++ ){
	   	for( k = i + 1; k < iKSM13_DATA_SEL_Cnt; k++ ) {
	        if( AnsiString(pKSM13_DATA_SEL[i].ORDER_NO).ToIntDef(0) > AnsiString(pKSM13_DATA_SEL[k].ORDER_NO).ToIntDef(0) ){

				strcpy( tmpKSM13_DATA.KOMK_NM	, pKSM13_DATA_SEL[i].KOMK_NM	);  // 測定項目
				strcpy( tmpKSM13_DATA.KIKI_NM	, pKSM13_DATA_SEL[i].KIKI_NM	);  // 測定機器名称
				strcpy( tmpKSM13_DATA.TANI		, pKSM13_DATA_SEL[i].TANI		);  // 単位
				strcpy( tmpKSM13_DATA.SOKU_SU	, pKSM13_DATA_SEL[i].SOKU_SU	);  // 測定指示n数
				strcpy( tmpKSM13_DATA.DTKSHIN	, pKSM13_DATA_SEL[i].DTKSHIN	);	// 代表得意先品番（素材検査の製品規格マスター検索の時利用）
				strcpy( tmpKSM13_DATA.KOMK_NO	, pKSM13_DATA_SEL[i].KOMK_NO	);	// 項目NO
				strcpy( tmpKSM13_DATA.ORDER_NO	, pKSM13_DATA_SEL[i].ORDER_NO	);	// 表示順
				strcpy( tmpKSM13_DATA.KOMK_ENG	, pKSM13_DATA_SEL[i].KOMK_ENG	);	// 測定項目名称（英語）
				strcpy( tmpKSM13_DATA.KIKI_NO	, pKSM13_DATA_SEL[i].KIKI_NO	);	// 測定機器NO
				strcpy( tmpKSM13_DATA.KIKA_TYPE	, pKSM13_DATA_SEL[i].KIKA_TYPE	);	// 規格タイプ
				strcpy( tmpKSM13_DATA.KIKA_KIND	, pKSM13_DATA_SEL[i].KIKA_KIND	);	// 規格種類
				strcpy( tmpKSM13_DATA.KIKA_DECI	, pKSM13_DATA_SEL[i].KIKA_DECI	);	// 規格小数点以下桁数
				strcpy( tmpKSM13_DATA.KIKA_NUM1	, pKSM13_DATA_SEL[i].KIKA_NUM1	);	// 規格値１
				strcpy( tmpKSM13_DATA.KIKA_NUM2	, pKSM13_DATA_SEL[i].KIKA_NUM2	);	// 規格値２
				strcpy( tmpKSM13_DATA.KIKA_NUM3	, pKSM13_DATA_SEL[i].KIKA_NUM3	);	// 規格値３
				strcpy( tmpKSM13_DATA.KIKA_STR	, pKSM13_DATA_SEL[i].KIKA_STR	);	// 規格値文字
				strcpy( tmpKSM13_DATA.SOKU_FLG	, pKSM13_DATA_SEL[i].SOKU_FLG	);	// 測定項目の有無
				strcpy( tmpKSM13_DATA.TOKU_FLG	, pKSM13_DATA_SEL[i].TOKU_FLG	);	// 特別項目の有無
				strcpy( tmpKSM13_DATA.KIKA_PRT	, pKSM13_DATA_SEL[i].KIKA_PRT	);	// 上限下限値の印刷
				strcpy( tmpKSM13_DATA.VALUE_TYPE, pKSM13_DATA_SEL[i].VALUE_TYPE	);	// 測定値表現
				strcpy( tmpKSM13_DATA.VALUE_DECI, pKSM13_DATA_SEL[i].VALUE_DECI	);	// 測定値小数点以下桁数

				strcpy( pKSM13_DATA_SEL[i].KOMK_NM		, pKSM13_DATA_SEL[k].KOMK_NM	);  // 測定項目
				strcpy( pKSM13_DATA_SEL[i].KIKI_NM		, pKSM13_DATA_SEL[k].KIKI_NM	);  // 測定機器名称
				strcpy( pKSM13_DATA_SEL[i].TANI			, pKSM13_DATA_SEL[k].TANI		);  // 単位
				strcpy( pKSM13_DATA_SEL[i].SOKU_SU		, pKSM13_DATA_SEL[k].SOKU_SU	);  // 測定指示n数
				strcpy( pKSM13_DATA_SEL[i].DTKSHIN		, pKSM13_DATA_SEL[k].DTKSHIN	);	// 代表得意先品番（素材検査の製品規格マスター検索の時利用）
				strcpy( pKSM13_DATA_SEL[i].KOMK_NO		, pKSM13_DATA_SEL[k].KOMK_NO	);	// 項目NO
				strcpy( pKSM13_DATA_SEL[i].ORDER_NO		, pKSM13_DATA_SEL[k].ORDER_NO	);	// 表示順
				strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		, pKSM13_DATA_SEL[k].KOMK_ENG	);	// 測定項目名称（英語）
				strcpy( pKSM13_DATA_SEL[i].KIKI_NO		, pKSM13_DATA_SEL[k].KIKI_NO	);	// 測定機器NO
				strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	, pKSM13_DATA_SEL[k].KIKA_TYPE	);	// 規格タイプ
				strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	, pKSM13_DATA_SEL[k].KIKA_KIND	);	// 規格種類
				strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	, pKSM13_DATA_SEL[k].KIKA_DECI	);	// 規格小数点以下桁数
				strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	, pKSM13_DATA_SEL[k].KIKA_NUM1	);	// 規格値１
				strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	, pKSM13_DATA_SEL[k].KIKA_NUM2	);	// 規格値２
				strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	, pKSM13_DATA_SEL[k].KIKA_NUM3	);	// 規格値３
				strcpy( pKSM13_DATA_SEL[i].KIKA_STR		, pKSM13_DATA_SEL[k].KIKA_STR	);	// 規格値文字
				strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		, pKSM13_DATA_SEL[k].SOKU_FLG	);	// 測定項目の有無
				strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		, pKSM13_DATA_SEL[k].TOKU_FLG	);	// 特別項目の有無
				strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		, pKSM13_DATA_SEL[k].KIKA_PRT	);	// 上限下限値の印刷
				strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	, pKSM13_DATA_SEL[k].VALUE_TYPE	);	// 測定値表現
				strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	, pKSM13_DATA_SEL[k].VALUE_DECI	);	// 測定値小数点以下桁数

				strcpy( pKSM13_DATA_SEL[k].KOMK_NM		, tmpKSM13_DATA.KOMK_NM		);  // 測定項目
				strcpy( pKSM13_DATA_SEL[k].KIKI_NM		, tmpKSM13_DATA.KIKI_NM		);  // 測定機器名称
				strcpy( pKSM13_DATA_SEL[k].TANI			, tmpKSM13_DATA.TANI		);  // 単位
				strcpy( pKSM13_DATA_SEL[k].SOKU_SU		, tmpKSM13_DATA.SOKU_SU		);  // 測定指示n数
				strcpy( pKSM13_DATA_SEL[k].DTKSHIN		, tmpKSM13_DATA.DTKSHIN		);	// 代表得意先品番（素材検査の製品規格マスター検索の時利用）
				strcpy( pKSM13_DATA_SEL[k].KOMK_NO		, tmpKSM13_DATA.KOMK_NO		);	// 項目NO
				strcpy( pKSM13_DATA_SEL[k].ORDER_NO		, tmpKSM13_DATA.ORDER_NO	);	// 表示順
				strcpy( pKSM13_DATA_SEL[k].KOMK_ENG		, tmpKSM13_DATA.KOMK_ENG	);	// 測定項目名称（英語）
				strcpy( pKSM13_DATA_SEL[k].KIKI_NO		, tmpKSM13_DATA.KIKI_NO	 	);	// 測定機器NO
				strcpy( pKSM13_DATA_SEL[k].KIKA_TYPE	, tmpKSM13_DATA.KIKA_TYPE	);	// 規格タイプ
				strcpy( pKSM13_DATA_SEL[k].KIKA_KIND	, tmpKSM13_DATA.KIKA_KIND	);	// 規格種類
				strcpy( pKSM13_DATA_SEL[k].KIKA_DECI	, tmpKSM13_DATA.KIKA_DECI	);	// 規格小数点以下桁数
				strcpy( pKSM13_DATA_SEL[k].KIKA_NUM1	, tmpKSM13_DATA.KIKA_NUM1	);	// 規格値１
				strcpy( pKSM13_DATA_SEL[k].KIKA_NUM2	, tmpKSM13_DATA.KIKA_NUM2	);	// 規格値２
				strcpy( pKSM13_DATA_SEL[k].KIKA_NUM3	, tmpKSM13_DATA.KIKA_NUM3	);	// 規格値３
				strcpy( pKSM13_DATA_SEL[k].KIKA_STR		, tmpKSM13_DATA.KIKA_STR	);	// 規格値文字
				strcpy( pKSM13_DATA_SEL[k].SOKU_FLG		, tmpKSM13_DATA.SOKU_FLG	);	// 測定項目の有無
				strcpy( pKSM13_DATA_SEL[k].TOKU_FLG		, tmpKSM13_DATA.TOKU_FLG	);	// 特別項目の有無
				strcpy( pKSM13_DATA_SEL[k].KIKA_PRT		, tmpKSM13_DATA.KIKA_PRT	);	// 上限下限値の印刷
				strcpy( pKSM13_DATA_SEL[k].VALUE_TYPE	, tmpKSM13_DATA.VALUE_TYPE	);	// 測定値表現
				strcpy( pKSM13_DATA_SEL[k].VALUE_DECI	, tmpKSM13_DATA.VALUE_DECI	);	// 測定値小数点以下桁数
            }
		}
    }


	// StringGridにデータを表示します。
    for( i=1; i<=Form3->Lbx_DTKSHIN_SZ->Items->Count; i++ ) {
		if( i == 1 )	DispSGr_List(TabSheet1,1);
		if( i == 2 )	DispSGr_List(TabSheet2,1);
		if( i == 3 )	DispSGr_List(TabSheet3,1);
		if( i == 4 )	DispSGr_List(TabSheet4,1);
		if( i == 5 )	DispSGr_List(TabSheet5,1);
		if( i == 6 )	DispSGr_List(TabSheet6,1);
    }

    //１行目を自動選択します
    SGr_ListSelectCell( SGr_List1, 1, 1, blnHoge);
    SGr_ListClick( SGr_List1 );


    //----------------------------------------------
    // 素材測定項目全マスター検索

	// Initial Query
	Form3->Query1->Close();
	Form3->Query1->SQL->Clear();

	// 問合せ実行（素材測定項目マスター）
	//sBuf = "SELECT * FROM KSM13 ORDER BY ORDER_NO";
	sBuf  = "SELECT KOMK_NO, ORDER_NO, KOMK_NM, KOMK_ENG, KOMK_SUB, KOMK_SUB_ENG,";
    sBuf +=       " KIKI_NO, KIKI_NM, TANI, KIKA_TYPE, KIKA_KIND, KIKA_DECI, KIKA_NUM1,";
    sBuf +=       " KIKA_NUM2, KIKA_NUM3, KIKA_STR, KIKA_SUB1, KIKA_SUB2, KIKA_SUB3,";
    sBuf +=       " SOKU_SU, SOKU_FLG, TOKU_FLG, KIKA_PRT, VALUE_TYPE, VALUE_DECI";
    sBuf += " FROM KSM13";
    sBuf += " ORDER BY ORDER_NO";

	Form3->Query1->SQL->Add(sBuf);
	Form3->Query1->Open();
	Form3->Query1->Active = true;

    if( !Form3->Query1->Eof ){

        // メモリ確保数を取得
		iKSM13_DATA_ALL_Cnt = Form3->Query1->RecordCount;

    	// メモリ確保
    	hMemKSM13_DATA_ALL = GlobalAlloc( GHND, sizeof(struct KSM13_DATA) * iKSM13_DATA_ALL_Cnt );
    	if( hMemKSM13_DATA_ALL == NULL ){
        	Beep();
    		MessageDlg("メモリ領域を確保できません。(01)", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        	return;
    	}
    	pKSM13_DATA_ALL = (struct KSM13_DATA *)GlobalLock(hMemKSM13_DATA_ALL);
    	if( hMemKSM13_DATA_ALL == NULL ){
        	Beep();
    		MessageDlg("メモリ領域を確保できません。(02)", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        	return;
	    }
    }

    i = 0;
	while( !Form3->Query1->Eof ){

		// メモリにデータをセットします。
		sBuf = "";
		strcpy( pKSM13_DATA_ALL[i].DTKSHIN		,sBuf.c_str() );	// 代表得意先品番

		sBuf = Form3->Query1->FieldValues["KOMK_NO"];
		strcpy( pKSM13_DATA_ALL[i].KOMK_NO		,sBuf.c_str() );	// 項目NO

		sBuf = Form3->Query1->FieldValues["ORDER_NO"];
		strcpy( pKSM13_DATA_ALL[i].ORDER_NO		,sBuf.c_str() );	// 表示順

        if( VarIsNull(Form3->Query1->FieldValues["KOMK_NM"]) ){
			sBuf = "";
		} else{
			sBuf = Form3->Query1->FieldValues["KOMK_NM"];
		}
		strcpy( pKSM13_DATA_ALL[i].KOMK_NM		,sBuf.c_str() );	// 測定項目（日本語）

        if( VarIsNull(Form3->Query1->FieldValues["KOMK_ENG"]) ){
			sBuf = "";
		} else{
			sBuf = Form3->Query1->FieldValues["KOMK_ENG"];
        }
		strcpy( pKSM13_DATA_ALL[i].KOMK_ENG		,sBuf.c_str() );	// 測定項目（英語）

		sBuf = Form3->Query1->FieldValues["KIKI_NO"];
		strcpy( pKSM13_DATA_ALL[i].KIKI_NO		,sBuf.c_str() );	// 測定機器NO

        if( VarIsNull(Form3->Query1->FieldValues["KIKI_NM"]) ){
			sBuf = "";
		} else{
			sBuf = Form3->Query1->FieldValues["KIKI_NM"];
        }
		strcpy( pKSM13_DATA_ALL[i].KIKI_NM		,sBuf.c_str() );	// 測定機器名称

        if( VarIsNull(Form3->Query1->FieldValues["TANI"]) ){
			sBuf = "";
		} else{
			sBuf = Form3->Query1->FieldValues["TANI"];
        }
		strcpy( pKSM13_DATA_ALL[i].TANI		,sBuf.c_str() );		// 単位

		sBuf = Form3->Query1->FieldValues["KIKA_TYPE"];
		strcpy( pKSM13_DATA_ALL[i].KIKA_TYPE	,sBuf.c_str() );	// 規格タイプ

		sBuf = Form3->Query1->FieldValues["KIKA_KIND"];
		strcpy( pKSM13_DATA_ALL[i].KIKA_KIND	,sBuf.c_str() );	// 規格種類

		sBuf = Form3->Query1->FieldValues["KIKA_DECI"];
		strcpy( pKSM13_DATA_ALL[i].KIKA_DECI	,sBuf.c_str() );	// 規格小数点以下桁数

		sBuf = Form3->Query1->FieldValues["KIKA_NUM1"];
		strcpy( pKSM13_DATA_ALL[i].KIKA_NUM1	,sBuf.c_str() );	// 規格値１

		sBuf = Form3->Query1->FieldValues["KIKA_NUM2"];
		strcpy( pKSM13_DATA_ALL[i].KIKA_NUM2	,sBuf.c_str() );	// 規格値２

		sBuf = Form3->Query1->FieldValues["KIKA_NUM3"];
		strcpy( pKSM13_DATA_ALL[i].KIKA_NUM3	,sBuf.c_str() );	// 規格値３

        if( VarIsNull(Form3->Query1->FieldValues["KIKA_STR"]) ){
			sBuf = "";
		} else{
			sBuf = Form3->Query1->FieldValues["KIKA_STR"];
        }
		strcpy( pKSM13_DATA_ALL[i].KIKA_STR		,sBuf.c_str() );	// 規格文字

		sBuf = Form3->Query1->FieldValues["SOKU_SU"];
		strcpy( pKSM13_DATA_ALL[i].SOKU_SU		,sBuf.c_str() );	// 測定指示n数

		sBuf = Form3->Query1->FieldValues["SOKU_FLG"];
		strcpy( pKSM13_DATA_ALL[i].SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無

		sBuf = Form3->Query1->FieldValues["TOKU_FLG"];
		strcpy( pKSM13_DATA_ALL[i].TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無

		sBuf = Form3->Query1->FieldValues["KIKA_PRT"];
		strcpy( pKSM13_DATA_ALL[i].KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷

		sBuf = Form3->Query1->FieldValues["VALUE_TYPE"];
		strcpy( pKSM13_DATA_ALL[i].VALUE_TYPE	,sBuf.c_str() );	// 値表現

		sBuf = Form3->Query1->FieldValues["VALUE_DECI"];
		strcpy( pKSM13_DATA_ALL[i].VALUE_DECI	,sBuf.c_str() );	// 測定値小数点以下桁数

		// カーソルを次にセットする
		Form3->Query1->Next();

		i += 1;
	}

    // 2003/10/23 A.Tamura サブ名称を自動設定する処理を追加します
    SetSubName(PgCtr_List->ActivePage->Caption);

}

//---------------------------------------------------------------------------
//
//  概要
//    OnCloseQueryイベント：Close メソッドが呼び出されたときまたはユーザーが
//          フォームのシステムメニューで［閉じる］を選択したときに発生します。
//
//  機能説明
//    メモリの開放を行ないます。
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
void __fastcall TForm5::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    // メモリの開放
    if( hMemKSM13_DATA_SEL ){
        GlobalUnlock( hMemKSM13_DATA_SEL );
        GlobalFree( hMemKSM13_DATA_SEL );
    }
    if( hMemKSM13_DATA_ALL ){
        GlobalUnlock( hMemKSM13_DATA_ALL );
        GlobalFree( hMemKSM13_DATA_ALL );
    }

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
void __fastcall TForm5::BtnF02Click(TObject *Sender)
{

    if( PgCtr_List->ActivePage->Name == "TabSheet1" ){
		if(SGr_List1->Row > 1){
			SGr_List1->Row -= 1;
			SGr_List1->SetFocus();
		}
    } else if( PgCtr_List->ActivePage->Name == "TabSheet2" ){
		if(SGr_List2->Row > 1){
			SGr_List2->Row -= 1;
			SGr_List2->SetFocus();
		}
    } else if( PgCtr_List->ActivePage->Name == "TabSheet3" ){
		if(SGr_List3->Row > 1){
			SGr_List3->Row -= 1;
			SGr_List3->SetFocus();
		}
    } else if( PgCtr_List->ActivePage->Name == "TabSheet4" ){
		if(SGr_List4->Row > 1){
			SGr_List4->Row -= 1;
			SGr_List4->SetFocus();
		}
    } else if( PgCtr_List->ActivePage->Name == "TabSheet5" ){
		if(SGr_List5->Row > 1){
			SGr_List5->Row -= 1;
			SGr_List5->SetFocus();
		}
    } else if( PgCtr_List->ActivePage->Name == "TabSheet6" ){
		if(SGr_List6->Row > 1){
			SGr_List6->Row -= 1;
			SGr_List6->SetFocus();
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
void __fastcall TForm5::BtnF03Click(TObject *Sender)
{

    if( PgCtr_List->ActivePage->Name == "TabSheet1" ){
		if( (SGr_List1->RowCount-1) > SGr_List1->Row ){
			SGr_List1->Row += 1;
			SGr_List1->SetFocus();
		}
    } else if( PgCtr_List->ActivePage->Name == "TabSheet2" ){
		if( (SGr_List2->RowCount-1) > SGr_List2->Row ){
			SGr_List2->Row += 1;
			SGr_List2->SetFocus();
		}
    } else if( PgCtr_List->ActivePage->Name == "TabSheet3" ){
		if( (SGr_List3->RowCount-1) > SGr_List3->Row ){
			SGr_List3->Row += 1;
			SGr_List3->SetFocus();
		}
    } else if( PgCtr_List->ActivePage->Name == "TabSheet4" ){
		if( (SGr_List4->RowCount-1) > SGr_List4->Row ){
			SGr_List4->Row += 1;
			SGr_List4->SetFocus();
		}
    } else if( PgCtr_List->ActivePage->Name == "TabSheet5" ){
		if( (SGr_List5->RowCount-1) > SGr_List5->Row ){
			SGr_List5->Row += 1;
			SGr_List5->SetFocus();
		}
    } else if( PgCtr_List->ActivePage->Name == "TabSheet6" ){
		if( (SGr_List6->RowCount-1) > SGr_List6->Row ){
			SGr_List6->Row += 1;
			SGr_List6->SetFocus();
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
void __fastcall TForm5::BtnF08F09Click(TObject *Sender)
{

    int				i;
    int				iSKB_NO;
    AnsiString		sDTKSHIN;
    AnsiString		sBuf;
    TButton*		bt = dynamic_cast<TButton*>(Sender);
    TStringGrid*	sg;


    iSKB_NO = 1;
	if( PgCtr_List->ActivePage->Name == "TabSheet1" ){
    	sDTKSHIN = TabSheet1->Caption;
    	sg = dynamic_cast<TStringGrid*>(SGr_List1);
    } else if( PgCtr_List->ActivePage->Name == "TabSheet2" ){
    	sDTKSHIN = TabSheet2->Caption;
    	sg = dynamic_cast<TStringGrid*>(SGr_List2);
    } else if( PgCtr_List->ActivePage->Name == "TabSheet3" ){
    	sDTKSHIN = TabSheet3->Caption;
    	sg = dynamic_cast<TStringGrid*>(SGr_List3);
    } else if( PgCtr_List->ActivePage->Name == "TabSheet4" ){
    	sDTKSHIN = TabSheet4->Caption;
    	sg = dynamic_cast<TStringGrid*>(SGr_List4);
    } else if( PgCtr_List->ActivePage->Name == "TabSheet5" ){
    	sDTKSHIN = TabSheet5->Caption;
    	sg = dynamic_cast<TStringGrid*>(SGr_List5);
    } else if( PgCtr_List->ActivePage->Name == "TabSheet6" ){
    	sDTKSHIN = TabSheet6->Caption;
    	sg = dynamic_cast<TStringGrid*>(SGr_List6);
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
            sBuf = sDTKSHIN;
			strcpy( Form3->tmpKSM02_DATA.HINBAN_SK		,sBuf.c_str() );	// 品番
			sBuf = sg->Cells[7][i];
			strcpy( Form3->tmpKSM02_DATA.KOMK_NO		,sBuf.c_str() );	// 項目NO
			sBuf = sg->Cells[1][i];
			strcpy( Form3->tmpKSM02_DATA.KOMK_NM		,sBuf.c_str() );	// 測定項目名称（日本語）
			sBuf = sg->Cells[9][i];
			strcpy( Form3->tmpKSM02_DATA.KOMK_ENG		,sBuf.c_str() );	// 測定項目名称（英語）
			sBuf = Edt_SKTKMK_JPN_SUB->Text;
			strcpy( Form3->tmpKSM02_DATA.KOMK_SUB		,sBuf.c_str() );	// 測定項目サブ名称（日本語）
			sBuf = Edt_SKTKMK_ENG_SUB->Text;
			strcpy( Form3->tmpKSM02_DATA.KOMK_SUB_ENG	,sBuf.c_str() );	// 測定項目サブ名称（英語）
			sBuf = sg->Cells[10][i];
			strcpy( Form3->tmpKSM02_DATA.KIKI_NO		,sBuf.c_str() );	// 測定機器NO
			sBuf = sg->Cells[2][i];
			strcpy( Form3->tmpKSM02_DATA.KIKI_NM		,sBuf.c_str() );	// 測定機器名称
			sBuf = sg->Cells[3][i];
			strcpy( Form3->tmpKSM02_DATA.TANI			,sBuf.c_str() );	// 単位
			sBuf = sg->Cells[11][i];
			strcpy( Form3->tmpKSM02_DATA.KIKA_TYPE		,sBuf.c_str() );	// 規格タイプ
			sBuf = sg->Cells[12][i];
			strcpy( Form3->tmpKSM02_DATA.KIKA_KIND		,sBuf.c_str() );	// 規格種類
			sBuf = sg->Cells[13][i];
			strcpy( Form3->tmpKSM02_DATA.KIKA_DECI		,sBuf.c_str() );	// 規格小数点以下桁数
			sBuf = sg->Cells[14][i];
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM1		,sBuf.c_str() );	// 規格値１
			sBuf = sg->Cells[15][i];
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM2		,sBuf.c_str() );	// 規格値２
			sBuf = sg->Cells[16][i];
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM3		,sBuf.c_str() );	// 規格値３
			sBuf = sg->Cells[17][i];
			strcpy( Form3->tmpKSM02_DATA.KIKA_STR		,sBuf.c_str() );	// 規格値文字
			sBuf = sg->Cells[5][i];
			strcpy( Form3->tmpKSM02_DATA.SOKU_SU		,sBuf.c_str() );	// 測定指示n数
			sBuf = sg->Cells[18][i];
			strcpy( Form3->tmpKSM02_DATA.SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
			sBuf = sg->Cells[19][i];
			strcpy( Form3->tmpKSM02_DATA.TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
			sBuf = sg->Cells[20][i];
			strcpy( Form3->tmpKSM02_DATA.KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
			sBuf = sg->Cells[21][i];
			strcpy( Form3->tmpKSM02_DATA.VALUE_TYPE		,sBuf.c_str() );	// 測定値表現
			sBuf = sg->Cells[22][i];
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
        sBuf = sDTKSHIN;
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
void __fastcall TForm5::BtnF12Click(TObject *Sender)
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
void __fastcall TForm5::FormKeyDown(TObject *Sender, WORD &Key,
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
void __fastcall TForm5::Pnl_ListResize(TObject *Sender)
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
void __fastcall TForm5::Rdo_KIKAKU_SHITEI_HANIClick(TObject *Sender)
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
void __fastcall TForm5::Rdo_KIKAKU_SHITEI_KIJYUNClick(TObject *Sender)
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
void __fastcall TForm5::Rdo_KIKAKU_SHITEI_MOJIClick(TObject *Sender)
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
void __fastcall TForm5::Rdo_KIKAKU_SYURUI_MINMAXClick(TObject *Sender)
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
void __fastcall TForm5::Rdo_KIKAKU_SYURUI_MAXClick(TObject *Sender)
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
void __fastcall TForm5::Rdo_KIKAKU_SYURUI_MINClick(TObject *Sender)
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
//    ページコントロールによるタブの切替
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
void __fastcall TForm5::PgCtr_ListChange(TObject *Sender)
{
    bool blnHoge=true;
	TPageControl *pPC = (TPageControl *)Sender;

	Pnl_HINBAN->Caption = pPC->ActivePage->Caption;

    // 2003/10/23 A.Tamura サブ名称を自動設定する処理を追加します
    SetSubName(pPC->ActivePage->Caption);

    if( PgCtr_List->ActivePage->Name == "TabSheet1" ){
		if( Rdo_SOZAI_SELECT1->Checked == true ){
			DispSGr_List(TabSheet1,1);
		} else {
			DispSGr_List(TabSheet1,2);
		}
    	SGr_ListSelectCell( SGr_List1, 1, SGr_List1->Row, blnHoge);
	    SGr_ListClick( SGr_List1 );

    } else if( PgCtr_List->ActivePage->Name == "TabSheet2" ){
		if( Rdo_SOZAI_SELECT2->Checked == true ){
			DispSGr_List(TabSheet2,1);
		} else {
			DispSGr_List(TabSheet2,2);
		}
    	SGr_ListSelectCell( SGr_List2, 1, SGr_List2->Row, blnHoge);
	    SGr_ListClick( SGr_List2 );

    } else if( PgCtr_List->ActivePage->Name == "TabSheet3" ){
		if( Rdo_SOZAI_SELECT3->Checked == true ){
			DispSGr_List(TabSheet3,1);
		} else {
			DispSGr_List(TabSheet3,2);
		}
    	SGr_ListSelectCell( SGr_List3, 1, SGr_List3->Row, blnHoge);
	    SGr_ListClick( SGr_List3 );

    } else if( PgCtr_List->ActivePage->Name == "TabSheet4" ){
		if( Rdo_SOZAI_SELECT4->Checked == true ){
			DispSGr_List(TabSheet4,1);
		} else {
			DispSGr_List(TabSheet4,2);
		}
    	SGr_ListSelectCell( SGr_List4, 1, SGr_List4->Row, blnHoge);
	    SGr_ListClick( SGr_List4 );

    } else if( PgCtr_List->ActivePage->Name == "TabSheet5" ){
		if( Rdo_SOZAI_SELECT5->Checked == true ){
			DispSGr_List(TabSheet5,1);
		} else {
			DispSGr_List(TabSheet5,2);
		}
    	SGr_ListSelectCell( SGr_List5, 1, SGr_List5->Row, blnHoge);
	    SGr_ListClick( SGr_List5 );

    } else if( PgCtr_List->ActivePage->Name == "TabSheet6" ){
		if( Rdo_SOZAI_SELECT6->Checked == true ){
			DispSGr_List(TabSheet6,1);
		} else {
			DispSGr_List(TabSheet6,2);
		}
    	SGr_ListSelectCell( SGr_List6, 1, SGr_List6->Row, blnHoge);
	    SGr_ListClick( SGr_List6 );

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
void __fastcall TForm5::Rdo_VALUE_NORMALClick(TObject *Sender)
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
void __fastcall TForm5::Rdo_VALUE_KAKUDOClick(TObject *Sender)
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
void __fastcall TForm5::Rdo_VALUE_OKClick(TObject *Sender)
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
void __fastcall TForm5::Rdo_VALUE_TEXTClick(TObject *Sender)
{
    Nmb_VALUE_DOUBLE->Enabled     = false;
    Nmb_VALUE_DOUBLE->Font->Color = clGray;

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：指定されたTabSheetのグリッドに該当データを表示
//
//  機能説明
//    指定されたTabSheetのグリッドに該当データを表示(StringGrid)します
//
//  パラメタ説明
//    TTabSheet *ts		：対象のTabSheet
//    int	type		：1 = 素材検査の製品規格マスターで指定されている測定項目から選択
//                        2 = 素材検査の測定項目一覧から選択
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm5::DispSGr_List(TTabSheet *ts, int	type)
{

    int             i;
    int				iDATA_Cnt;
    int				iRow;
    AnsiString		sDTKSHIN;
    AnsiString		sBuf;
    TStringGrid*	sg;


    // FormActive中は処理中止
    if( Form5->Tag == 1 ) return;


    // 表示するStringGridを取得します
	if( ts->Name == "TabSheet1" ){
    	sDTKSHIN = ts->Caption;
    	sg = dynamic_cast<TStringGrid*>(SGr_List1);
    } else if( ts->Name == "TabSheet2" ){
    	sDTKSHIN = ts->Caption;
    	sg = dynamic_cast<TStringGrid*>(SGr_List2);
    } else if( ts->Name == "TabSheet3" ){
    	sDTKSHIN = ts->Caption;
    	sg = dynamic_cast<TStringGrid*>(SGr_List3);
    } else if( ts->Name == "TabSheet4" ){
    	sDTKSHIN = ts->Caption;
    	sg = dynamic_cast<TStringGrid*>(SGr_List4);
    } else if( ts->Name == "TabSheet5" ){
    	sDTKSHIN = ts->Caption;
    	sg = dynamic_cast<TStringGrid*>(SGr_List5);
    } else if( ts->Name == "TabSheet6" ){
    	sDTKSHIN = ts->Caption;
    	sg = dynamic_cast<TStringGrid*>(SGr_List6);
    }

    if( type == 1 ){
        // 素材検査の製品規格マスターで指定されている測定項目から選択
    	iDATA_Cnt = iKSM13_DATA_SEL_Cnt;
    } else {
		// 素材検査の測定項目一覧から選択
    	iDATA_Cnt = iKSM13_DATA_ALL_Cnt;
    }

    // データの表示
	iRow = 1;
	for( i=0; i<iDATA_Cnt; i++ ){

    	if( type == 1 ){
        	// 素材検査の製品規格マスターで指定されている測定項目から選択
			// エラー　memcpy( (char *)tmpKSM13_DATA, (char *)pKSM13_DATA_SEL[i], sizeof(tmpKSM13_DATA) );
			strcpy( tmpKSM13_DATA.KOMK_NM	, pKSM13_DATA_SEL[i].KOMK_NM	);  // 測定項目
			strcpy( tmpKSM13_DATA.KIKI_NM	, pKSM13_DATA_SEL[i].KIKI_NM	);  // 測定機器名称
			strcpy( tmpKSM13_DATA.TANI		, pKSM13_DATA_SEL[i].TANI		);  // 単位
			strcpy( tmpKSM13_DATA.SOKU_SU	, pKSM13_DATA_SEL[i].SOKU_SU	);  // 測定指示n数
			strcpy( tmpKSM13_DATA.DTKSHIN	, pKSM13_DATA_SEL[i].DTKSHIN	);	// 代表得意先品番（素材検査の製品規格マスター検索の時利用）
			strcpy( tmpKSM13_DATA.KOMK_NO	, pKSM13_DATA_SEL[i].KOMK_NO	);	// 項目NO
			strcpy( tmpKSM13_DATA.ORDER_NO	, pKSM13_DATA_SEL[i].ORDER_NO	);	// 表示順
			strcpy( tmpKSM13_DATA.KOMK_ENG	, pKSM13_DATA_SEL[i].KOMK_ENG	);	// 測定項目名称（英語）
			strcpy( tmpKSM13_DATA.KIKI_NO	, pKSM13_DATA_SEL[i].KIKI_NO	);	// 測定機器NO
			strcpy( tmpKSM13_DATA.KIKA_TYPE	, pKSM13_DATA_SEL[i].KIKA_TYPE	);	// 規格タイプ
			strcpy( tmpKSM13_DATA.KIKA_KIND	, pKSM13_DATA_SEL[i].KIKA_KIND	);	// 規格種類
			strcpy( tmpKSM13_DATA.KIKA_DECI	, pKSM13_DATA_SEL[i].KIKA_DECI	);	// 規格小数点以下桁数
			strcpy( tmpKSM13_DATA.KIKA_NUM1	, pKSM13_DATA_SEL[i].KIKA_NUM1	);	// 規格値１
			strcpy( tmpKSM13_DATA.KIKA_NUM2	, pKSM13_DATA_SEL[i].KIKA_NUM2	);	// 規格値２
			strcpy( tmpKSM13_DATA.KIKA_NUM3	, pKSM13_DATA_SEL[i].KIKA_NUM3	);	// 規格値３
			strcpy( tmpKSM13_DATA.KIKA_STR	, pKSM13_DATA_SEL[i].KIKA_STR	);	// 規格値文字
			strcpy( tmpKSM13_DATA.SOKU_FLG	, pKSM13_DATA_SEL[i].SOKU_FLG	);	// 測定項目の有無
			strcpy( tmpKSM13_DATA.TOKU_FLG	, pKSM13_DATA_SEL[i].TOKU_FLG	);	// 特別項目の有無
			strcpy( tmpKSM13_DATA.KIKA_PRT	, pKSM13_DATA_SEL[i].KIKA_PRT	);	// 上限下限値の印刷
			strcpy( tmpKSM13_DATA.VALUE_TYPE, pKSM13_DATA_SEL[i].VALUE_TYPE	);	// 測定値表現
			strcpy( tmpKSM13_DATA.VALUE_DECI, pKSM13_DATA_SEL[i].VALUE_DECI	);	// 測定値小数点以下桁数
    	} else {
			// 素材検査の測定項目一覧から選択
			// エラー　memcpy( (char *)tmpKSM13_DATA, (char *)pKSM13_DATA_ALL[i], sizeof(tmpKSM13_DATA) );
			strcpy( tmpKSM13_DATA.KOMK_NM	, pKSM13_DATA_ALL[i].KOMK_NM	);  // 測定項目
			strcpy( tmpKSM13_DATA.KIKI_NM	, pKSM13_DATA_ALL[i].KIKI_NM	);  // 測定機器名称
			strcpy( tmpKSM13_DATA.TANI		, pKSM13_DATA_ALL[i].TANI		);  // 単位
			strcpy( tmpKSM13_DATA.SOKU_SU	, pKSM13_DATA_ALL[i].SOKU_SU	);  // 測定指示n数
			strcpy( tmpKSM13_DATA.DTKSHIN	, pKSM13_DATA_ALL[i].DTKSHIN	);	// 代表得意先品番（素材検査の製品規格マスター検索の時利用）
			strcpy( tmpKSM13_DATA.KOMK_NO	, pKSM13_DATA_ALL[i].KOMK_NO	);	// 項目NO
			strcpy( tmpKSM13_DATA.ORDER_NO	, pKSM13_DATA_ALL[i].ORDER_NO	);	// 表示順
			strcpy( tmpKSM13_DATA.KOMK_ENG	, pKSM13_DATA_ALL[i].KOMK_ENG	);	// 測定項目名称（英語）
			strcpy( tmpKSM13_DATA.KIKI_NO	, pKSM13_DATA_ALL[i].KIKI_NO	);	// 測定機器NO
			strcpy( tmpKSM13_DATA.KIKA_TYPE	, pKSM13_DATA_ALL[i].KIKA_TYPE	);	// 規格タイプ
			strcpy( tmpKSM13_DATA.KIKA_KIND	, pKSM13_DATA_ALL[i].KIKA_KIND	);	// 規格種類
			strcpy( tmpKSM13_DATA.KIKA_DECI	, pKSM13_DATA_ALL[i].KIKA_DECI	);	// 規格小数点以下桁数
			strcpy( tmpKSM13_DATA.KIKA_NUM1	, pKSM13_DATA_ALL[i].KIKA_NUM1	);	// 規格値１
			strcpy( tmpKSM13_DATA.KIKA_NUM2	, pKSM13_DATA_ALL[i].KIKA_NUM2	);	// 規格値２
			strcpy( tmpKSM13_DATA.KIKA_NUM3	, pKSM13_DATA_ALL[i].KIKA_NUM3	);	// 規格値３
			strcpy( tmpKSM13_DATA.KIKA_STR	, pKSM13_DATA_ALL[i].KIKA_STR	);	// 規格値文字
			strcpy( tmpKSM13_DATA.SOKU_FLG	, pKSM13_DATA_ALL[i].SOKU_FLG	);	// 測定項目の有無
			strcpy( tmpKSM13_DATA.TOKU_FLG	, pKSM13_DATA_ALL[i].TOKU_FLG	);	// 特別項目の有無
			strcpy( tmpKSM13_DATA.KIKA_PRT	, pKSM13_DATA_ALL[i].KIKA_PRT	);	// 上限下限値の印刷
			strcpy( tmpKSM13_DATA.VALUE_TYPE, pKSM13_DATA_ALL[i].VALUE_TYPE	);	// 測定値表現
			strcpy( tmpKSM13_DATA.VALUE_DECI, pKSM13_DATA_ALL[i].VALUE_DECI	);	// 測定値小数点以下桁数
    	}

        // 不要なデータはSkipします
    	if( type == 1 ){
            if( sDTKSHIN != AnsiString(tmpKSM13_DATA.DTKSHIN) )	continue;
        }

    	// グリッドの最大行数が超えていないかチェックする
		if( iRow >= sg->RowCount ){
			sg->RowCount = iRow + 1;
		}

		// グリッドにデータをセットします。
		sBuf = iRow ;
		sg->Cells[0][iRow] = AnsiString::StringOfChar(' ', 3-sBuf.Length()) + sBuf;    //No
        sg->Cells[1][iRow] = tmpKSM13_DATA.KOMK_NM		;   // 測定項目
		sg->Cells[2][iRow] = tmpKSM13_DATA.KIKI_NM		;   // 測定機器名称
		sg->Cells[3][iRow] = tmpKSM13_DATA.TANI			;   // 単位
		sg->Cells[4][iRow] = ""							;   // 規格　※再描画する為に必要です。
		sg->Cells[5][iRow] = tmpKSM13_DATA.SOKU_SU		;   // 測定指示n数
		sg->Cells[6][iRow] = tmpKSM13_DATA.DTKSHIN		;	// 代表得意先品番（素材検査の製品規格マスター検索の時利用）
		sg->Cells[7][iRow] = tmpKSM13_DATA.KOMK_NO		;	// 項目NO
		sg->Cells[8][iRow] = tmpKSM13_DATA.ORDER_NO		;	// 表示順
		sg->Cells[9][iRow] = tmpKSM13_DATA.KOMK_ENG		;	// 測定項目名称（英語）
		sg->Cells[10][iRow] = tmpKSM13_DATA.KIKI_NO		;	// 測定機器NO
		sg->Cells[11][iRow] = tmpKSM13_DATA.KIKA_TYPE	;	// 規格タイプ
		sg->Cells[12][iRow] = tmpKSM13_DATA.KIKA_KIND	;	// 規格種類
		sg->Cells[13][iRow] = tmpKSM13_DATA.KIKA_DECI	;	// 規格小数点以下桁数
		sg->Cells[14][iRow] = tmpKSM13_DATA.KIKA_NUM1	;	// 規格値１
		sg->Cells[15][iRow] = tmpKSM13_DATA.KIKA_NUM2	;	// 規格値２
		sg->Cells[16][iRow] = tmpKSM13_DATA.KIKA_NUM3	;	// 規格値３
		sg->Cells[17][iRow] = tmpKSM13_DATA.KIKA_STR	;	// 規格値文字
		sg->Cells[18][iRow] = tmpKSM13_DATA.SOKU_FLG	;	// 測定項目の有無
		sg->Cells[19][iRow] = tmpKSM13_DATA.TOKU_FLG	;	// 特別項目の有無
		sg->Cells[20][iRow] = tmpKSM13_DATA.KIKA_PRT	;	// 上限下限値の印刷
		sg->Cells[21][iRow] = tmpKSM13_DATA.VALUE_TYPE	;	// 測定値表現
		sg->Cells[22][iRow] = tmpKSM13_DATA.VALUE_DECI	;	// 測定値小数点以下桁数

		iRow++;
    }

    // 最後の行は空白行とします
    sg->RowCount = iRow + 1;
	for( i=0; i<sg->ColCount; i++ ){
		sg->Cells[i][iRow] = "";
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
void __fastcall TForm5::SGr_ListClick(TObject *Sender)
{
    TStringGrid* sg = dynamic_cast<TStringGrid*>(Sender);

   	iRowSelTop    = sg->Selection.Top;
   	iRowSelBottom = sg->Selection.Bottom;

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
void __fastcall TForm5::SGr_ListDrawCell(TObject *Sender, int ACol,
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

   if( ARow > 0 && ACol == 4 ){

        // 規格タイプ毎の表示
        switch( sg->Cells[11][ARow].ToIntDef(0) ){
            case 1: // 範囲指定

                    // 小数点以下桁数のフォーマット文字列
            		sprintf(c1,"%0");
            		sprintf(c2,"1.%df",sg->Cells[13][ARow].ToIntDef(0) );
            		strcat(c1,c2);

			        switch( sg->Cells[12][ARow].ToIntDef(0) ){
            			case 1: // 上限下限両方
                                sValue = sg->Cells[14][ARow];
                                //2003.05.08 E.Takase Add↓
			                    sprintf(cFormatBuf, c1, Form1->ConvDoubleDefD(sValue,0.0) );
                                //2003.05.08 E.Takase Add↑
			        			//2003.05.08 E.Takase Add コメント↓
			                    //sprintf(cFormatBuf, c1, sValue.ToDouble() );
                                //2003.05.08 E.Takase Add コメント↑
                     			sBuf = cFormatBuf;
                     			sBuf +=  "～";
                                sValue = sg->Cells[15][ARow];
                                //2003.05.08 E.Takase Add↓
                     			sprintf(cFormatBuf, c1,  Form1->ConvDoubleDefD(sValue,0.0) );
                                //2003.05.08 E.Takase Add↑
			        			//2003.05.08 E.Takase Add コメント↓
                     			//sprintf(cFormatBuf, c1, sValue.ToDouble() );
                                //2003.05.08 E.Takase Add コメント↑
                     			sBuf += cFormatBuf ;
			            		break;

            			case 2: // 上限のみ
                                sValue = sg->Cells[15][ARow];
                                //2003.05.08 E.Takase Add↓
                     			sprintf(cFormatBuf, c1,  Form1->ConvDoubleDefD(sValue,0.0) );
                                //2003.05.08 E.Takase Add↑
			        			//2003.05.08 E.Takase Add コメント↓
                     			//sprintf(cFormatBuf, c1, sValue.ToDouble() );
                                //2003.05.08 E.Takase Add コメント↑
                     			sBuf = cFormatBuf ;
                     			sBuf += "以下";
			            		break;
            			case 3: // 下限のみ
                                sValue = sg->Cells[14][ARow];
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
            		sprintf(c2,"1.%df",sg->Cells[13][ARow].ToIntDef(0) );
            		strcat(c1,c2);

                    sValue = sg->Cells[14][ARow];
                    //2003.05.08 E.Takase Add↓
                    sprintf(cFormatBuf, c1,  Form1->ConvDoubleDefD(sValue,0.0) );
                    //2003.05.08 E.Takase Add↑
			        //2003.05.08 E.Takase Add コメント↓
                    //sprintf(cFormatBuf, c1, sValue.ToDouble() );
                    //2003.05.08 E.Takase Add コメント↑
                    sBuf = cFormatBuf ;
        			sg->Canvas->TextOut( r.left +  0, r.top + 0, sBuf );
                    iPos = sBuf.Length() * 8;

        			// フォント（小）の設定
        			Form3->OrgFont = SelectObject( sg->Canvas->Handle, Form3->MyFont );

			        switch( sg->Cells[12][ARow].ToIntDef(0) ){
            			case 1: // 上限下限両方
                    			sValue = sg->Cells[15][ARow];
                                //2003.05.08 E.Takase Add↓
                    			sprintf(cFormatBuf, c1, Form1->ConvDoubleDefD(sValue,0.0) );
                                //2003.05.08 E.Takase Add↑
			        			//2003.05.08 E.Takase Add コメント↓
                    			//sprintf(cFormatBuf, c1, sValue.ToDouble() );
                               	//2003.05.08 E.Takase Add コメント↑
			                    sBuf = cFormatBuf;
                                if( sBuf.SubString(1,1) != "-" ) sBuf.Insert("+",1);
                                sg->Canvas->TextOut( r.left + iPos, r.top - 2, sBuf );
                     			sValue = sg->Cells[16][ARow];
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
			                    sValue = sg->Cells[15][ARow];
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
                     			sValue = sg->Cells[16][ARow];
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
                    }

        			// 元のフォントに戻します
        			SelectObject( sg->Canvas->Handle, Form3->OrgFont );

                    break;

        	case 3: // 文字
					DrawText(sg->Canvas->Handle,sg->Cells[17][ARow].c_str(),-1,&r,0); //左寄せ
                    break;
        }

   } else if( ARow > 0 && ACol == 5 ){
        // ｎ数
		DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,DT_RIGHT); //右寄せ

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
void __fastcall TForm5::SGr_ListKeyPress(TObject *Sender, char &Key)
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
void __fastcall TForm5::SGr_ListSelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{

    int			i, k;
    AnsiString	sBuf;
	TStringGrid *sg = (TStringGrid *)Sender;


    if(ARow == 0) ARow = 1;

    // 品番
    if( PgCtr_List->ActivePage->Name == "TabSheet1" ){
    	sBuf = TabSheet1->Caption;
    } else if( PgCtr_List->ActivePage->Name == "TabSheet2" ){
    	sBuf = TabSheet2->Caption;
    } else if( PgCtr_List->ActivePage->Name == "TabSheet3" ){
    	sBuf = TabSheet3->Caption;
    } else if( PgCtr_List->ActivePage->Name == "TabSheet4" ){
    	sBuf = TabSheet4->Caption;
    } else if( PgCtr_List->ActivePage->Name == "TabSheet5" ){
    	sBuf = TabSheet5->Caption;
    } else if( PgCtr_List->ActivePage->Name == "TabSheet6" ){
    	sBuf = TabSheet6->Caption;
    }
    Pnl_HINBAN->Caption = sBuf;

    // 測定NO
    Edt_SKTKMK_JPN->Tag = sg->Cells[7][ARow].ToIntDef(0);

    // 測定項目（日本語）
    Edt_SKTKMK_JPN->Text = sg->Cells[1][ARow];

    // 項目名（英語）
    Edt_SKTKMK_ENG->Text = sg->Cells[9][ARow];

    // 測定機器
    k = sg->Cells[10][ARow].ToIntDef(-1);
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
    Cmb_TANI->Text = sg->Cells[3][ARow];

	// 測定項目としての扱い
    switch( sg->Cells[18][ARow].ToIntDef(-1) ){
		case 0: Rdo_SKTKMK_OFF->Checked = true;
				break;
		case 1:
        default:Rdo_SKTKMK_ON->Checked = true;
          		break;
   	}

	// 特別項目としての扱い
    switch( sg->Cells[19][ARow].ToIntDef(-1) ){
		case 1: Rdo_TKBKMK_ON->Checked = true;
				break;
		case 0:
        default:Rdo_TKBKMK_OFF->Checked = true;
          		break;
   	}

	// 規格（指定方法）
    switch( sg->Cells[11][ARow].ToIntDef(-1) ){
		case 3: Rdo_KIKAKU_SHITEI_MOJI->Checked = true;
				break;
		case 2: Rdo_KIKAKU_SHITEI_KIJYUN->Checked = true;
				break;
		case 1:
        default:Rdo_KIKAKU_SHITEI_HANI->Checked = true;
          		break;
   	}

	// 規格（種類）
    switch( sg->Cells[12][ARow].ToIntDef(-1) ){
		case 3: Rdo_KIKAKU_SYURUI_MIN->Checked = true;
				break;
		case 2: Rdo_KIKAKU_SYURUI_MAX->Checked = true;
				break;
		case 1:
        default:Rdo_KIKAKU_SYURUI_MINMAX->Checked = true;
          		break;
   	}

	// 規格（上限下限値の印刷）
    switch( sg->Cells[20][ARow].ToIntDef(-1) ){
		case 0: Rdo_MANMIN_PRT_OFF->Checked = true;
				break;
		case 1:
        default:Rdo_MANMIN_PRT_ON->Checked = true;
          		break;
   	}

	// 規格（小数点以下桁数）
    Nmb_KIKAKU_DOUBLE->Text = IntToStr(sg->Cells[13][ARow].ToIntDef(0));

	// 規格値（範囲指定）
    Nmb_KIKAKU_HANI_MIN->FPos = sg->Cells[13][ARow].ToIntDef(0);
    Nmb_KIKAKU_HANI_MAX->FPos = sg->Cells[13][ARow].ToIntDef(0);
    Nmb_KIKAKU_HANI_MIN->Text = sg->Cells[14][ARow];
    if( sg->Cells[11][ARow].ToIntDef(-1) == 1 ){
	    Nmb_KIKAKU_HANI_MAX->Text = sg->Cells[15][ARow];
    }
    else {
	    Nmb_KIKAKU_HANI_MAX->Text = "0";
    }

	// 規格値（基準値指定）
    Nmb_KIKAKU_KIJYUN_MID->FPos = sg->Cells[13][ARow].ToIntDef(0);
    Nmb_KIKAKU_KIJYUN_MAX->FPos = sg->Cells[13][ARow].ToIntDef(0);
    Nmb_KIKAKU_KIJYUN_MIN->FPos = sg->Cells[13][ARow].ToIntDef(0);
    Nmb_KIKAKU_KIJYUN_MID->Text = sg->Cells[14][ARow];
    if( sg->Cells[11][ARow].ToIntDef(-1) == 2 ){
    	Nmb_KIKAKU_KIJYUN_MAX->Text = sg->Cells[15][ARow];
    	Nmb_KIKAKU_KIJYUN_MIN->Text = sg->Cells[16][ARow];
    }
    else {
    	Nmb_KIKAKU_KIJYUN_MAX->Text = "0";
    	Nmb_KIKAKU_KIJYUN_MIN->Text = "0";
    }

	// 規格値（文字指定）
    Edt_KIKAKU_STRING->Text = sg->Cells[27][ARow];

	// 測定値（値表現）
    switch( sg->Cells[21][ARow].ToIntDef(-1) ){
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
    Nmb_VALUE_DOUBLE->Text = IntToStr(sg->Cells[22][ARow].ToIntDef(0));

	// 測定値（抜取ｎ数）
    Nmb_N->Text = IntToStr(sg->Cells[5][ARow].ToIntDef(2));

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：素材検査の測定項目表示対象をクリックしたときに発生します。
//
//  機能説明
//    「素材検査の製品規格マスターで指定されている測定項目から選択」
//    「素材検査の測定項目一覧から選択」
//    のラジオボタンを切り替えたときにStringGridの表示内容を入れ替えます
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
void __fastcall TForm5::Rdo_SOZAI_Click(TObject *Sender)
{
    bool blnHoge=true;
	TRadioButton	*rdo = (TRadioButton *)Sender;

    if( PgCtr_List->ActivePage->Name == "TabSheet1" ){
		if( rdo->Name == "Rdo_SOZAI_SELECT1" ){
			DispSGr_List(TabSheet1,1);
		} else if( rdo->Name == "Rdo_SOZAI_ALL1" ){
			DispSGr_List(TabSheet1,2);
		}
    	SGr_ListSelectCell( SGr_List1, 1, 1, blnHoge);
	    SGr_ListClick( SGr_List1 );

    } else if( PgCtr_List->ActivePage->Name == "TabSheet2" ){
		if( rdo->Name == "Rdo_SOZAI_SELECT2" ){
			DispSGr_List(TabSheet2,1);
		} else if( rdo->Name == "Rdo_SOZAI_ALL2" ){
			DispSGr_List(TabSheet2,2);
		}
    	SGr_ListSelectCell( SGr_List2, 1, 1, blnHoge);
	    SGr_ListClick( SGr_List2 );

    } else if( PgCtr_List->ActivePage->Name == "TabSheet3" ){
		if( rdo->Name == "Rdo_SOZAI_SELECT3" ){
			DispSGr_List(TabSheet3,1);
		} else if( rdo->Name == "Rdo_SOZAI_ALL3" ){
			DispSGr_List(TabSheet3,2);
		}
    	SGr_ListSelectCell( SGr_List3, 1, 1, blnHoge);
	    SGr_ListClick( SGr_List3 );

    } else if( PgCtr_List->ActivePage->Name == "TabSheet4" ){
		if( rdo->Name == "Rdo_SOZAI_SELECT4" ){
			DispSGr_List(TabSheet4,1);
		} else if( rdo->Name == "Rdo_SOZAI_ALL4" ){
			DispSGr_List(TabSheet4,2);
		}
    	SGr_ListSelectCell( SGr_List4, 1, 1, blnHoge);
	    SGr_ListClick( SGr_List4 );

    } else if( PgCtr_List->ActivePage->Name == "TabSheet5" ){
		if( rdo->Name == "Rdo_SOZAI_SELECT5" ){
			DispSGr_List(TabSheet5,1);
		} else if( rdo->Name == "Rdo_SOZAI_ALL5" ){
			DispSGr_List(TabSheet5,2);
		}
    	SGr_ListSelectCell( SGr_List5, 1, 1, blnHoge);
	    SGr_ListClick( SGr_List5 );

    } else if( PgCtr_List->ActivePage->Name == "TabSheet6" ){
		if( rdo->Name == "Rdo_SOZAI_SELECT6" ){
			DispSGr_List(TabSheet6,1);
		} else if( rdo->Name == "Rdo_SOZAI_ALL6" ){
			DispSGr_List(TabSheet6,2);
		}
    	SGr_ListSelectCell( SGr_List6, 1, 1, blnHoge);
	    SGr_ListClick( SGr_List6 );

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
void __fastcall TForm5::Edt_ALLChange(TObject *Sender)
{
	Form3->Edt_ALLChange( Sender );
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
void __fastcall TForm5::Nmb_KIKAKU_DOUBLEExit(TObject *Sender)
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
//    自作関数			：指定された素材用品番からサブ名称をセットします
//
//  機能説明
//    指定された素材用品番から空白を探し出し、空白以降の文字を
//    サブ名称としてセットします
//
//  パラメタ説明
//    AnsiString sHINBAN：素材用品番
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm5::SetSubName( AnsiString sHINBAN )
{
    AnsiString	sBuf;
    int			i;

    sBuf = sHINBAN;
    sBuf = sBuf.Trim();
    i = sBuf.AnsiPos(" ");
    if( i > 0 && i < sBuf.Length() ){
        sBuf = sBuf.SubString( i+1, sBuf.Length()-i );
    	Edt_SKTKMK_JPN_SUB->Text = sBuf;
        Edt_SKTKMK_ENG_SUB->Text = sBuf;
    }

}



