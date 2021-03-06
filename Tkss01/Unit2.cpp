//---------------------------------------------------------------------------
//
//  Unit2.cpp
//    【出荷検査システム−検査測定】
//    一覧検索フォーム（TForm2クラス）のメンバ関数の定義
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
#include "Unit8.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
extern AnsiString sMEMO_NAME;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
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
void __fastcall TForm2::BtnF02Click(TObject *Sender)
{
   if(SGr1->Row > 1){
        SGr1->Row -= 1;
        SGr1->SetFocus();
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
void __fastcall TForm2::BtnF03Click(TObject *Sender)
{
    if( (SGr1->RowCount-1) > SGr1->Row ){
        SGr1->Row += 1;
        SGr1->SetFocus();
    }
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ４：選択」ボタンを押した時の処理
//
//  機能説明
//    選択フラグをONにしてフォームのCloseをコールします
//    （CloseQuery内で選択データ取得処理を行なう）
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
void __fastcall TForm2::BtnF04Click(TObject *Sender)
{
     SGr1->Tag = 1;    // 選択フラグON
     Close();
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ１２：戻る」ボタンを押した時の処理
//
//  機能説明
//    フォームのCloseをコールします
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
void __fastcall TForm2::BtnF12Click(TObject *Sender)
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
void __fastcall TForm2::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     switch(Key)
     {
         case VK_F2:  BtnF02Click(Sender);    break;
         case VK_F3:  BtnF03Click(Sender);    break;
         case VK_F4:  BtnF04Click(Sender);    break;
         case VK_F12: BtnF12Click(Sender);    break;
         case VK_RETURN:
              SGr1->Tag = 1;    // 選択フラグON
              Close();
              break;
     }

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：StringGridを選択した時に発生します。
//
//  機能説明
//    選択（範囲選択）されたTopとBottomを記憶します
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
void __fastcall TForm2::SGr1Click(TObject *Sender)
{
   	iRowSelTop    = SGr1->Selection.Top;
   	iRowSelBottom = SGr1->Selection.Bottom;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnDblClickイベント：StringGridで左ボタンをダブルクリックしたときに発生します。
//
//  機能説明
//    「Ｆ４：選択」ボタンをコールします
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
void __fastcall TForm2::SGr1DblClick(TObject *Sender)
{
	BtnF04Click(BtnF04);
}

//---------------------------------------------------------------------------
//
//  概要
//    OnActivateイベント	：フォームがアクティブになったときに発生します。
//
//  機能説明
//    初期状態で必要な検索処理を行ないます
//    【一覧データの検索処理】
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

     int i;
     int iRow,iCol;
     AnsiString sBuf;
     AnsiString wLOTNO;
     AnsiString wLOTYY;

     SGr1->Tag = 0;    // 選択フラグOFF

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     SGr1->Row = 1;     // 選択行の初期化

     switch( Form2->Tag ){

        // ［測定画面］検索部　代表得意先品番にフォーカスが有る場合
        case 1:

            // 問合せ実行
            sBuf  = "select DTKSHIN, HINBAN, ZISNAM, HINMEI from KSM01";
            sBuf += " where REVCNT = 0";
            if( Form1->Cmb_DTKSHIN->Text.Trim() != "" ){
                // 得意先品番
                sBuf += " and DTKSHIN like '" + Form1->Cmb_DTKSHIN->Text + "%'";
            }
            sBuf += " ORDER BY DTKSHIN";

            // タイトルをセット
            SGr1->ColCount = 5;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "得意先品番";
            SGr1->Cells[2][0] = "自社品番";
            SGr1->Cells[3][0] = "品　種";
            SGr1->Cells[4][0] = "品　名";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 166;
            SGr1->ColWidths[2] = 110;
            SGr1->ColWidths[3] = 110;
            SGr1->ColWidths[4] = 110;
            break;

        // ［測定画面］検索部　ロットNOにフォーカスが有る場合
        case 2:

            // 問合せ実行
            sBuf  = "select KSM01.DTKSHIN, SD21S.LOTBNG, SD21S.HINBAN, SD21S.KOKBNG from KSM01";
            sBuf += " inner join SD21S on KSM01.DTKSHIN = SD21S.DTKSHIN";
            sBuf += " where KSM01.REVCNT = 0";
            if( Form1->Cmb_DTKSHIN->Text.Trim() != "" ){
                // 得意先品番
                sBuf += " and KSM01.DTKSHIN like '" + Form1->Cmb_DTKSHIN->Text + "%'";
            }
            sBuf += " and length(ltrim(rtrim(SD21S.LOTBNG))) > 0";
            sBuf += " and SD21S.DENYMD >= '" + Form1->Edt_SEIKAN_YMD->Text + "'";
            sBuf += " order by KSM01.DTKSHIN, SD21S.HINBAN ,SUBSTR(SD21S.LOTBNG,2)";

            // タイトルをセット
            SGr1->ColCount = 5;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "得意先品番";
            SGr1->Cells[2][0] = "ロットNO";
            SGr1->Cells[3][0] = "自社品番";
            SGr1->Cells[4][0] = "工管番号";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 110;
            SGr1->ColWidths[3] = 100;
            SGr1->ColWidths[4] = 100;
            break;

        // ［ロット割当画面］StringGrid部　履歴ロットにフォーカスが有る場合
        case 3:

            iCol = Form8->SGr_vRIRE_SYUKA->Col;
            iRow = Form8->SGr_vRIRE_SYUKA->Row;

            // 問合せ実行
            sBuf  = "select DTKSHIN, LOTNO, HINBAN from KSD21";
            if( Trim(Form8->SGr_vRIRE_SYUKA->Cells[0][Form8->SGr_vRIRE_SYUKA->Row]) != "" ){
            	sBuf += " where DTKSHIN = '";
            	sBuf += Trim(Form8->SGr_vRIRE_SYUKA->Cells[0][Form8->SGr_vRIRE_SYUKA->Row]);
				sBuf += "'";
                sBuf += " and LOTNO like '" + Trim(Form8->SGr_vRIRE_SYUKA->Cells[iCol][iRow]) + "%'";
            }
            sBuf += " ORDER BY DTKSHIN, SUBSTR(LOTNO,2)";

            // タイトルをセット
            SGr1->ColCount = 4;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "得意先品番";
            SGr1->Cells[2][0] = "ロットNO";
            SGr1->Cells[3][0] = "自社品番";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 180;
            SGr1->ColWidths[3] = 180;
            break;

        // ［ロット割当画面］StringGrid部　測定ロットにフォーカスが有る場合
        case 4:

            iCol = Form8->SGr_vSOKU_SYUKA->Col;
            iRow = Form8->SGr_vSOKU_SYUKA->Row;

            // 問合せ実行
            sBuf  = "select DTKSHIN, LOTNO, HINBAN from KSD21";
            if( Trim(Form8->SGr_vRIRE_SYUKA->Cells[0][Form8->SGr_vSOKU_SYUKA->Row]) != "" ){
            	sBuf += " where DTKSHIN = '";
            	sBuf += Trim(Form8->SGr_vRIRE_SYUKA->Cells[0][Form8->SGr_vSOKU_SYUKA->Row]);
				sBuf += "'";
                sBuf += " and LOTNO like '" + Trim(Form8->SGr_vSOKU_SYUKA->Cells[iCol][iRow]) + "%'";
            }
            sBuf += " ORDER BY DTKSHIN, SUBSTR(LOTNO,2)";

            // タイトルをセット
            SGr1->ColCount = 4;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "得意先品番";
            SGr1->Cells[2][0] = "ロットNO";
            SGr1->Cells[3][0] = "自社品番";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 180;
            SGr1->ColWidths[3] = 180;
            break;

        // ［項目編集画面］詳細部　得意先コード、得意先名称にフォーカスが有る場合
        case 5:
        case 6:

            // 問合せ実行
            sBuf = "select DISTINCT TRSCOD, TRSNAM from SM16S where TKSKBN=1";
            if( Form3->Edt_DTKSCOD->Text.Trim() != "" ){
                // 得意先コード
                sBuf += " and TRSCOD like '" + Form3->Edt_DTKSCOD->Text + "%'";
            }
            sBuf += " ORDER BY TRSCOD";

            // タイトルをセット
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "得意先コード";
            SGr1->Cells[2][0] = "得意先名称";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 100;
            SGr1->ColWidths[2] = 400;
            break;

        // ［項目編集画面］詳細部　得意先品番にフォーカスが有る場合
        // ［項目編集画面］詳細部　自社品番にフォーカスが有る場合
        case 7:
        case 8:

            // 問合せ実行
            sBuf = "select DISTINCT DTKSHIN, HINBAN from SD21S where length(ltrim(rtrim(DTKSHIN)))>0";
            if( Trim(Form3->Edt_DTKSCOD->Text) != "" ){
                // 得意先コード
                sBuf = sBuf + " and DTKSCOD like '";
                sBuf = sBuf + Form3->Edt_DTKSCOD->Text ;
                sBuf = sBuf + "%'";
            }
            if( Trim(Form3->Edt_DTKSHIN->Text) != "" ){
                // 得意先品番
                sBuf = sBuf + " and DTKSHIN like '";
                sBuf = sBuf + Form3->Edt_DTKSHIN->Text ;
                sBuf = sBuf + "%'";
            }
            if( Trim(Form3->Edt_HINBAN->Text) != "" ){
                // 自社品番
                sBuf = sBuf + " and HINBAN like '";
                sBuf = sBuf + Form3->Edt_HINBAN->Text ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY DTKSHIN";

            // タイトルをセット
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "得意先品番";
            SGr1->Cells[2][0] = "自社品番";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 180;
            break;

        // ［項目編集画面］詳細部　材質名称（品種）にフォーカスが有る場合
        case 9:

            // 問合せ実行
            sBuf = "select DISTINCT ZISNAM, ZISCOD from KM03";
            if( Trim(Form3->Edt_ZISNAM->Text) != "" ){
                // 材質名称
                sBuf = sBuf + " where ZISNAM like '";
                sBuf = sBuf + Form3->Edt_ZISNAM->Text ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY ZISNAM";

            // タイトルをセット
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "材質名称";
            SGr1->Cells[2][0] = "材質コード";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 180;
            break;

        // ［項目編集画面］詳細部　品名にフォーカスが有る場合
        case 10:

            // 問合せ実行
            sBuf = "select DISTINCT HINNAM from SD21S where length(ltrim(rtrim(DTKSHIN)))>0";
            sBuf = sBuf + " ORDER BY HINNAM";

            // タイトルをセット
            SGr1->ColCount = 2;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "品名";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 400;
            break;

        // ［項目編集画面］詳細部　素材用品番の「指定」ボタンにフォーカスが有る場合
        case 11:

            // 問合せ実行
    		sBuf = "select DISTINCT DTKSHIN, min(DTKSNAM) AS DTKSNAM_MIN,";
    		sBuf = sBuf + " max(SKTYMD) AS SKTYMD_MAN, count(LOTNO) AS LOTNO_CNT ";
    		sBuf = sBuf + "from KSD21 group by DTKSHIN order by DTKSHIN";

            // タイトルをセット
            SGr1->ColCount = 5;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "素材測定済品番";
            SGr1->Cells[2][0] = "代表得意先名";
            SGr1->Cells[3][0] = "最終測定日";
            SGr1->Cells[4][0] = "測定ﾛｯﾄ数";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 180;
            SGr1->ColWidths[3] = 70;
            SGr1->ColWidths[4] = 60;
            break;
            //  [備考欄］にフォーカスがある場合
        case 12:
            sBuf  = "SELECT MEMO from KSM91";
            sBuf += " ORDER BY MEMO_NO";
            // タイトルをセット
            SGr1->ColCount = 2;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "備　考";
            SGr1->ColWidths[0] = 36;
            SGr1->ColWidths[1] = 500;
            break;
    }

    Query1->SQL->Add(sBuf);
    Query1->Open();
    Query1->Active = true;

    iRow = 0;
    while( !Query1->Eof ){

        iRow += 1;

        // グリッドの最大行数が超えていないかチェックする
        if( iRow >= SGr1->RowCount ){
            SGr1->RowCount = iRow;
        }

        // グリッドにデータをセットします。

        // NO
        sBuf = iRow;
        if( sBuf.Length() > 5 )	sBuf = sBuf.SubString( sBuf.Length() - 4, 5 );
        SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;

        // データ
        for( i=1; i<SGr1->ColCount; i++){
            sBuf = Query1->Fields->Fields[i-1]->AsString;
            if( Form2->Tag == 11 && i == 3 ){
            	// 日付フォーマットに変換
                sBuf.Insert("/",5);
                sBuf.Insert("/",8);
            }
            if( Form2->Tag == 11 && i == 4 ){
                // 数値右寄せ
                sBuf = AnsiString::StringOfChar(' ', 7-sBuf.Length()) + sBuf;
            }

            SGr1->Cells[i][iRow] = sBuf;
        }

        // カーソルを次にセットする
        Query1->Next();
    }

    SGr1->RowCount = iRow + 1 ;

    fFind = true;
    if( iRow == 0 ){
        fFind = false;
        SGr1->RowCount = 2;
        SGr1->FixedRows = 1;
        // 検索結果該当なしの場合
        for( i=1; i<SGr1->ColCount; i++){
            SGr1->Cells[i][1] = "該当無し";
        }
        iRow = 1;
    }
    if( Form2->Tag == 2 ){
    	SGr1->Row = iRow;
    } else {
    	SGr1->Row = 1;
    }
    SGr1->SetFocus();

  	iRowSelTop    = SGr1->Row;
   	iRowSelBottom = SGr1->Row;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnCloseQueryイベント：Close メソッドが呼び出されたときまたはユーザーが
//          フォームのシステムメニューで［閉じる］を選択したときに発生します。
//
//  機能説明
//    選択フラグONの時、選択したデータをします
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
void __fastcall TForm2::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    int			i;
    int			iCol,iRow;
    int         iNum;
    AnsiString	sBuf;


    if( !fFind )   return;

    // 選択フラグONの時
    if( SGr1->Tag ){

        switch( Form2->Tag ){

            // ［測定画面］検索部　代表得意先品番にフォーカスが有る場合
            case 1:
                Form1->Cmb_DTKSHIN->Items->Clear();
                Form1->Cmb_DTKSHIN->Text = SGr1->Cells[1][SGr1->Row];
                Form1->Cmb_DTKSHIN->SetFocus();
                Form1->Cmb_DTKSHIN->SelectAll();
                break;

            // ［測定画面］検索部　ロットNOにフォーカスが有る場合
            case 2:
                if( SGr1->Cells[1][iRowSelTop] != SGr1->Cells[1][iRowSelBottom] ){
					MessageDlg("異なる得意先品番同士は指定できません。", mtWarning,
								TMsgDlgButtons() << mbOK , 0);
                    CanClose = false;
                	return;
                }
                Form1->Cmb_DTKSHIN->Text = SGr1->Cells[1][iRowSelTop];
                if( iRowSelTop != iRowSelBottom ){
                    sBuf = "";
	    	        for( i=iRowSelTop; i<=iRowSelBottom; i++ ) {
    	            	if( SGr1->Cells[2][i].Trim() != "" )	{
                            if( sBuf.Length() > 0 )	sBuf = sBuf + ",";
                        	sBuf = sBuf + SGr1->Cells[2][i].Trim();
                    	}
                	}
                    Form1->Edt_LOTNO->Text = sBuf;
                	//Form1->Edt_LOTNO->Text = SGr1->Cells[2][iRowSelTop] + "-" + SGr1->Cells[2][iRowSelBottom];
                } else {
                	Form1->Edt_LOTNO->Text = SGr1->Cells[2][SGr1->Row];
                }
                Form1->Edt_LOTNO->SetFocus();
                Form1->Edt_LOTNO->SelectAll();
                break;

            // ［ロット割当画面］StringGrid部　履歴ロットにフォーカスが有る場合
            case 3:
                iCol = Form8->SGr_vRIRE_SYUKA->Col;
                iRow = Form8->SGr_vRIRE_SYUKA->Row;
                Form8->SGr_vRIRE_SYUKA->Cells[iCol][iRow] = SGr1->Cells[2][SGr1->Row];
                Form8->SGr_vRIRE_HINBAN->Cells[iCol][iRow] = SGr1->Cells[3][SGr1->Row];
                Form8->SGr_vRIRE_SYUKA->SetFocus();
                break;

            // ［ロット割当画面］StringGrid部　測定ロットにフォーカスが有る場合
            case 4:
                iCol = Form8->SGr_vSOKU_SYUKA->Col;
                iRow = Form8->SGr_vSOKU_SYUKA->Row;
                Form8->SGr_vSOKU_SYUKA->Cells[iCol][iRow] = SGr1->Cells[2][SGr1->Row];
                Form8->SGr_vSOKU_HINBAN->Cells[iCol][iRow] = SGr1->Cells[3][SGr1->Row];
                Form8->SGr_vSOKU_SYUKA->SetFocus();
                break;

            // ［項目編集画面］詳細部　得意先コード、得意先名称にフォーカスが有る場合
            case 5:
            case 6:
                Form3->Edt_DTKSCOD->Text = SGr1->Cells[1][SGr1->Row];      // 得意先コード
                Form3->Edt_DTKSNAM->Text = SGr1->Cells[2][SGr1->Row];      // 得意先名称
                if( Form3->BtnF01->Tag == 5 ){
                    Form3->Edt_DTKSCOD->SetFocus();
                    Form3->Edt_DTKSCOD->SelectAll();
                }
                if( Form3->BtnF01->Tag == 6 ){
                    Form3->Edt_DTKSNAM->SetFocus();
                    Form3->Edt_DTKSNAM->SelectAll();
                }
                break;

            // ［項目編集画面］詳細部　得意先品番にフォーカスが有る場合
            // ［項目編集画面］詳細部　自社品番にフォーカスが有る場合
            case 7:
            case 8:
                Form3->Edt_DTKSHIN->Text = SGr1->Cells[1][SGr1->Row];      // 得意先品番
                Form3->Edt_HINBAN->Text  = SGr1->Cells[2][SGr1->Row];      // 自社品番
                if( Form3->BtnF01->Tag == 7 ){
                    Form3->Edt_DTKSHIN->SetFocus();
                    Form3->Edt_DTKSHIN->SelectAll();
                }
                if( Form3->BtnF01->Tag == 8 ){
                    Form3->Edt_HINBAN->SetFocus();
                    Form3->Edt_HINBAN->SelectAll();
                }
                break;

            // ［項目編集画面］詳細部　材質名称（品種）にフォーカスが有る場合
            case 9:
                Form3->Edt_ZISNAM->Text = SGr1->Cells[1][SGr1->Row];      // 材質名称
                Form3->Edt_ZISNAM->SetFocus();
                Form3->Edt_ZISNAM->SelectAll();
                break;

            // ［項目編集画面］詳細部　品名にフォーカスが有る場合
            case 10:
                Form3->Edt_HINMEI->Text = SGr1->Cells[1][SGr1->Row];      // 品名
                Form3->Edt_HINMEI->SetFocus();
                Form3->Edt_HINMEI->SelectAll();
                break;

            // ［項目編集画面］詳細部　素材用品番にフォーカスが有る場合
            case 11:
    	        for( i=iRowSelTop; i<=iRowSelBottom; i++ ) {
                	sBuf = SGr1->Cells[1][i];
                    if( sBuf.Trim() != "" )	{
                	    if( Form3->Lbx_DTKSHIN_SZ->Items->Count >= 6 )	break;
                	    Form3->Lbx_DTKSHIN_SZ->Items->Add(sBuf);
                    }
                }
                Form3->Lbx_DTKSHIN_SZ->ItemIndex = Form3->Lbx_DTKSHIN_SZ->Items->Count - 1;
                Form3->Lbx_DTKSHIN_SZ->Selected[Form3->Lbx_DTKSHIN_SZ->ItemIndex-1] = true;
                Form3->Btn_DTKSHIN_SZ_ADD->SetFocus();

                // データ変更フラグの設定
                Form3->DataChange = 1;
                break;
            //  [備考欄] にフォーカスがある場合
            case 12:
                iNum = sMEMO_NAME.SubString(15,sMEMO_NAME.Length()-14).ToIntDef(0);
                if(sMEMO_NAME.SubString(5,5) == "vRIRE" )
                {
                   Form1->Mem_vRIRE_MEMO[iNum]->Lines->Add(SGr1->Cells[1][SGr1->Row]);
                }
                else
                {
                   Form1->Mem_vSOKU_MEMO[iNum]->Lines->Add(SGr1->Cells[1][SGr1->Row]);
                }
                //Form1->ADD_MEMO->Text += '\n' + SGr1->Cells[1][SGr1->Row];
                //Form1->EdtSETMEMO->Text = SGr1->Cells[1][SGr1->Row];	// 備考
                //Form1->EdtSETMEMO->SetFocus();
                //Form1->EdtSETMEMO->SelectAll();
                break;
        }
    }
}



