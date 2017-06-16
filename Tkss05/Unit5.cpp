//---------------------------------------------------------------------------
//
//  Unit5.cpp
//    【出荷検査システム－製品規格マスター】
//    一覧検索フォーム（TForm5クラス）のメンバ関数の定義
//
//  作成者
//    田村　敦司
//
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
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
void __fastcall TForm5::BtnF03Click(TObject *Sender)
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
void __fastcall TForm5::BtnF04Click(TObject *Sender)
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
void __fastcall TForm5::FormActivate(TObject *Sender)
{

     int i;
     int iRow;
     AnsiString sBuf;

     SGr1->Tag = 0;    // 選択フラグOFF

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     SGr1->Row = 1;     // 選択行の初期化

     switch( Form1->BtnF01->Tag ){

        // 検索部　得意先コードにフォーカスが有る場合
        case 1:

            // 問合せ実行
            sBuf = "select DISTINCT DTKSCOD, DTKSNAM from KSM01";
            i = 0;
            if( Form1->Edt_COD1->Text != "" ){
                // 得意先コード
                sBuf = sBuf + " where DTKSCOD like '";
                sBuf = sBuf + Form1->Edt_COD1->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->Edt_COD2->Text != "" ){
                // 得意先品番
                if( i == 1 ){   // 得意先コードの条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先コードの条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " DTKSHIN like '";
                sBuf = sBuf + Form1->Edt_COD2->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->Edt_COD3->Text != "" ){
                // 自社品番
                if( i == 1 ){   // 得意先コードの条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先コードの条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " HINBAN like '";
                sBuf = sBuf + Form1->Edt_COD3->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->Edt_COD4->Text != "" ){
                // 材質名称
                if( i == 1 ){   // 得意先の条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先の条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " ZISNAM like '";
                sBuf = sBuf + Form1->Edt_COD4->Text ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY DTKSCOD";

            // タイトルをセット
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "得意先コード";
            SGr1->Cells[2][0] = "得意先名称";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 80;
            SGr1->ColWidths[2] = 400;
            break;

        // 検索部　得意先品番にフォーカスが有る場合
        case 2:

            // 問合せ実行
            sBuf = "select DISTINCT DTKSHIN, HINBAN, ZISNAM from KSM01";
            i = 0;
            if( Form1->Edt_COD1->Text != "" ){
                // 得意先コード
                sBuf = sBuf + " where DTKSCOD like '";
                sBuf = sBuf + Form1->Edt_COD1->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->Edt_COD2->Text != "" ){
                // 得意先品番
                if( i == 1 ){   // 得意先コードの条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先コードの条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " DTKSHIN like '";
                sBuf = sBuf + Form1->Edt_COD2->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->Edt_COD3->Text != "" ){
                // 自社品番
                if( i == 1 ){   // 得意先コードの条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先コードの条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " HINBAN like '";
                sBuf = sBuf + Form1->Edt_COD3->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->Edt_COD4->Text != "" ){
                // 材質名称
                if( i == 1 ){   // 得意先の条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先の条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " ZISNAM like '";
                sBuf = sBuf + Form1->Edt_COD4->Text ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY DTKSHIN";

            // タイトルをセット
            SGr1->ColCount = 4;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "得意先品番";
            SGr1->Cells[2][0] = "自社品番";
            SGr1->Cells[3][0] = "材質名称";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 180;
            SGr1->ColWidths[3] = 180;
            break;

        // 検索部　自社品番にフォーカスが有る場合
        case 3:

            // 問合せ実行
            sBuf = "select DISTINCT HINBAN from KSM01";
            i = 0;
            if( Form1->Edt_COD1->Text != "" ){
                // 得意先コード
                sBuf = sBuf + " where DTKSCOD like '";
                sBuf = sBuf + Form1->Edt_COD1->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->Edt_COD2->Text != "" ){
                // 得意先品番
                if( i == 1 ){   // 得意先コードの条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先コードの条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " DTKSHIN like '";
                sBuf = sBuf + Form1->Edt_COD2->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->Edt_COD3->Text != "" ){
                // 自社品番
                if( i == 1 ){   // 得意先コードの条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先コードの条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " HINBAN like '";
                sBuf = sBuf + Form1->Edt_COD3->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->Edt_COD4->Text != "" ){
                // 材質名称
                if( i == 1 ){   // 得意先の条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先の条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " ZISNAM like '";
                sBuf = sBuf + Form1->Edt_COD4->Text ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY HINBAN";

            // タイトルをセット
            SGr1->ColCount = 2;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "自社品番";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            break;

        // 検索部　材質名称にフォーカスが有る場合
        case 4:

            // 問合せ実行
            sBuf = "select DISTINCT ZISNAM from KSM01";
            i = 0;
            if( Form1->Edt_COD1->Text != "" ){
                // 得意先コード
                sBuf = sBuf + " where DTKSCOD like '";
                sBuf = sBuf + Form1->Edt_COD1->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->Edt_COD2->Text != "" ){
                // 得意先品番
                if( i == 1 ){   // 得意先コードの条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先コードの条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " DTKSHIN like '";
                sBuf = sBuf + Form1->Edt_COD2->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->Edt_COD3->Text != "" ){
                // 自社品番
                if( i == 1 ){   // 得意先品番の条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先品番の条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " HINBAN like '";
                sBuf = sBuf + Form1->Edt_COD3->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->Edt_COD4->Text != "" ){
                // 材質名称
                if( i == 1 ){   // 得意先の条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先の条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " ZISNAM like '";
                sBuf = sBuf + Form1->Edt_COD4->Text ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY ZISNAM";

            // タイトルをセット
            SGr1->ColCount = 2;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "材質名称";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            break;

        // 詳細部　得意先コード、得意先名称にフォーカスが有る場合
        case 5:
        case 6:

            // 問合せ実行
            sBuf = "select DISTINCT TRSCOD, TRSNAM from SM16S where TKSKBN=1";
            if( Trim(Form1->Edt_DTKSCOD->Text) != "" ){
                // 得意先コード
                sBuf = sBuf + " and TRSCOD like '";
                sBuf = sBuf + Form1->Edt_DTKSCOD->Text ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY TRSCOD";

            // タイトルをセット
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "得意先コード";
            SGr1->Cells[2][0] = "得意先名称";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 100;
            SGr1->ColWidths[2] = 400;
            break;

        // 詳細部　得意先品番にフォーカスが有る場合
        case 7:
            // 問合せ実行
            sBuf = "select DISTINCT SD21S.DTKSHIN, SD21S.DTKSCOD, SM16S.TRSNAM, SD21S.HINBAN, SD21S.ZISNAM, SD21S.HINNAM";
            sBuf = sBuf + " from SD21S";
            sBuf = sBuf + " LEFT JOIN SM16S ON SD21S.DTKSCOD = SM16S.TRSCOD";
            //sBuf = sBuf + " where length(ltrim(rtrim(DTKSHIN)))>0";
            if( Trim(Form1->Edt_DTKSHIN->Text) != "" ){
                // 得意先品番
                sBuf = sBuf + " where SD21S.DTKSHIN like '";
                sBuf = sBuf + Form1->Edt_DTKSHIN->Text ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY SD21S.DTKSHIN";

            // タイトルをセット
            SGr1->ColCount = 7;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "得意先品番";
            SGr1->Cells[2][0] = "";
            SGr1->Cells[3][0] = "得意先名称";
            SGr1->Cells[4][0] = "自社品番";
            SGr1->Cells[5][0] = "品　種";
            SGr1->Cells[6][0] = "品　名";
            SGr1->ColWidths[0] = 36;
            SGr1->ColWidths[1] = 120;
            SGr1->ColWidths[2] = 0;
            SGr1->ColWidths[3] = 100;
            SGr1->ColWidths[4] = 90;
            SGr1->ColWidths[5] = 90;
            SGr1->ColWidths[6] = 100;
            break;

        // 詳細部　自社品番にフォーカスが有る場合
        case 8:

            // 問合せ実行
            sBuf = "select DISTINCT DTKSHIN, HINBAN from SD21S where length(ltrim(rtrim(DTKSHIN)))>0";
            if( Trim(Form1->Edt_HINBAN->Text) != "" ){
                // 自社品番
                sBuf = sBuf + " and HINBAN like '";
                sBuf = sBuf + Form1->Edt_HINBAN->Text ;
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

        // 詳細部　材質名称（品種）にフォーカスが有る場合
        case 9:

            // 問合せ実行
            sBuf = "select DISTINCT ZISNAM, ZISCOD from KM03";
            if( Trim(Form1->Edt_ZISNAM->Text) != "" ){
                // 材質名称
                sBuf = sBuf + " where ZISNAM like '";
                sBuf = sBuf + Form1->Edt_ZISNAM->Text ;
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

        // 詳細部　品名にフォーカスが有る場合
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

        // 素材用品番の「指定」ボタンにフォーカスが有る場合
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
    }

    Query1->SQL->Add(sBuf);
    Query1->Open();
    Query1->Active = true;

    iRow = 0;
    while( !Query1->Eof ){

        if( !VarIsNull(Query1->Fields->Fields[0]->AsString) ){
        	if( Trim(AnsiString(Query1->Fields->Fields[0]->AsString)) == "" ){
        		// カーソルを次にセットする
        		Query1->Next();
        		continue;
            }
        }
        else {
        	// カーソルを次にセットする
        	Query1->Next();
        	continue;
        }

        iRow += 1;

        // グリッドの最大行数が超えていないかチェックする
        if( iRow >= SGr1->RowCount ){
            SGr1->RowCount = iRow;
        }

        // グリッドにデータをセットします。

        // NO
        sBuf = iRow;
        SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;

        // データ
        for( i=1; i<SGr1->ColCount; i++){
            sBuf = Query1->Fields->Fields[i-1]->AsString;
            if( Form1->BtnF01->Tag == 11 && i == 3 ){
            	// 日付フォーマットに変換
                sBuf.Insert("/",5);
                sBuf.Insert("/",8);
            }
            if( Form1->BtnF01->Tag == 11 && i == 4 ){
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
    }
    SGr1->Row = 1;
    SGr1->SetFocus();
    SGr1Click( SGr1 );

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
void __fastcall TForm5::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    int			i;
    AnsiString	sBuf;


    if( !fFind )   return;

    // 選択フラグONの時
    if( SGr1->Tag ){

        switch( Form1->BtnF01->Tag ){

            // 検索部　得意先コードにフォーカスが有る場合
            case 1:
                Form1->Edt_COD1->Text = SGr1->Cells[1][SGr1->Row];      // 得意先コード
                Form1->Edt_COD1->SetFocus();
                Form1->Edt_COD1->SelectAll();
                break;

            // 検索部　得意先品番にフォーカスが有る場合
            case 2:
                Form1->Edt_COD2->Text = SGr1->Cells[1][SGr1->Row];      // 得意先品番
                Form1->Edt_COD3->Text = SGr1->Cells[2][SGr1->Row];      // 自社品番
                Form1->Edt_COD4->Text = SGr1->Cells[3][SGr1->Row];      // 材質名称
                Form1->Edt_COD2->SetFocus();
                Form1->Edt_COD2->SelectAll();
                break;

            // 検索部　自社品番にフォーカスが有る場合
            case 3:
                Form1->Edt_COD3->Text = SGr1->Cells[1][SGr1->Row];      // 自社品番
                Form1->Edt_COD3->SetFocus();
                Form1->Edt_COD3->SelectAll();
                break;

            // 検索部　材質名称にフォーカスが有る場合
            case 4:
                Form1->Edt_COD4->Text = SGr1->Cells[1][SGr1->Row];      // 材質名称
                Form1->Edt_COD4->SetFocus();
                Form1->Edt_COD4->SelectAll();
                break;

            // 詳細部　得意先コード、得意先名称にフォーカスが有る場合
            case 5:
            case 6:
                Form1->Edt_DTKSCOD->Text = SGr1->Cells[1][SGr1->Row];      // 得意先コード
                Form1->Edt_DTKSNAM->Text = SGr1->Cells[2][SGr1->Row];      // 得意先名称
                if( Form1->BtnF01->Tag == 5 ){
                    Form1->Edt_DTKSCOD->SetFocus();
                    Form1->Edt_DTKSCOD->SelectAll();
                }
                if( Form1->BtnF01->Tag == 6 ){
                    Form1->Edt_DTKSNAM->SetFocus();
                    Form1->Edt_DTKSNAM->SelectAll();
                }
                break;

            // 詳細部　得意先品番にフォーカスが有る場合
            // 詳細部　自社品番にフォーカスが有る場合
            case 7:
                Form1->Edt_DTKSHIN->Text = SGr1->Cells[1][SGr1->Row];      // 得意先品番
                Form1->Edt_DTKSCOD->Text = SGr1->Cells[2][SGr1->Row];      // 得意先コード
                Form1->Edt_DTKSNAM->Text = SGr1->Cells[3][SGr1->Row];      // 得意先名称
                Form1->Edt_HINBAN->Text  = SGr1->Cells[4][SGr1->Row];      // 自社品番
                Form1->Edt_ZISNAM->Text  = SGr1->Cells[5][SGr1->Row];      // 品種
                Form1->Edt_HINMEI->Text  = SGr1->Cells[6][SGr1->Row];      // 品名
                Form1->Edt_DTKSHIN->SetFocus();
                Form1->Edt_DTKSHIN->SelectAll();
                break;

            case 8:
                Form1->Edt_DTKSHIN->Text = SGr1->Cells[1][SGr1->Row];      // 得意先品番
                Form1->Edt_HINBAN->Text  = SGr1->Cells[2][SGr1->Row];      // 自社品番
                Form1->Edt_HINBAN->SetFocus();
                Form1->Edt_HINBAN->SelectAll();
                break;

            // 詳細部　材質名称（品種）にフォーカスが有る場合
            case 9:
                Form1->Edt_ZISNAM->Text = SGr1->Cells[1][SGr1->Row];      // 材質名称
                Form1->Edt_ZISNAM->SetFocus();
                Form1->Edt_ZISNAM->SelectAll();
                break;

            // 詳細部　品名にフォーカスが有る場合
            case 10:
                Form1->Edt_HINMEI->Text = SGr1->Cells[1][SGr1->Row];      // 品名
                Form1->Edt_HINMEI->SetFocus();
                Form1->Edt_HINMEI->SelectAll();
                break;

            // 詳細部　素材用品番にフォーカスが有る場合
            case 11:
    	        for( i=iRowSelTop; i<=iRowSelBottom; i++ ) {
                	sBuf = SGr1->Cells[1][i];
                    if( sBuf.Trim() != "" )	{
                	    if( Form1->Lbx_DTKSHIN_SZ->Items->Count >= 6 )	break;
                	    Form1->Lbx_DTKSHIN_SZ->Items->Add(sBuf);
                    }
                }
                Form1->Lbx_DTKSHIN_SZ->ItemIndex = Form1->Lbx_DTKSHIN_SZ->Items->Count - 1;
                Form1->Lbx_DTKSHIN_SZ->Selected[Form1->Lbx_DTKSHIN_SZ->ItemIndex-1] = true;
                Form1->Btn_DTKSHIN_SZ_ADD->SetFocus();

                // データ変更フラグの設定
                Form1->DataChange = 1;
                break;
        }
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
void __fastcall TForm5::SGr1Click(TObject *Sender)
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
void __fastcall TForm5::SGr1DblClick(TObject *Sender)
{
	BtnF04Click(BtnF04);
}


