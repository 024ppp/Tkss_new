//---------------------------------------------------------------------------
//
//  Unit2.cpp
//    【出荷検査システム−レポート出力】
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
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------



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

     int		i;
     int		iRow;
     int        iDateNo;
     AnsiString	sBuf;
	 AnsiString	sDTKSHIN_KEY;


     SGr1->Tag = 0;    // 選択フラグOFF

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     SGr1->Row = 1;     // 選択行の初期化


     // ダミーデータのタイトルをセット
     SGr1->ColCount = 5;
     SGr1->Cells[0][0] = "   N O";
     SGr1->Cells[1][0] = "得意先品番";
     SGr1->Cells[2][0] = "自社品番";
     SGr1->Cells[3][0] = "品　種";
     SGr1->Cells[4][0] = "ロットNo";
     SGr1->ColWidths[0] = 55;
     SGr1->ColWidths[1] = 180;
     SGr1->ColWidths[2] = 160;
     SGr1->ColWidths[3] = 100;
     SGr1->ColWidths[4] = 80;


     switch( Form1->BtnF01->Tag ){

        // 「検査成績書」にフォーカスが有る場合
        case 1:
        case 2:
        	sDTKSHIN_KEY = Form1->Edt1_WHR_DTKSHIN->Text;
            break;
        // 「検査成績書（月別）上」にフォーカスが有る場合
        case 3:
        case 4:
        	sDTKSHIN_KEY = Form1->Edt2_WHR_DTKSHIN1->Text;
            break;
        // 「検査成績書（月別）下」にフォーカスが有る場合
        case 5:
        case 6:
        case 7:
        	sDTKSHIN_KEY = Form1->Edt2_WHR_DTKSHIN2->Text;
            break;
        // 「材料証明書」にフォーカスが有る場合
        case 8:
        case 9:
        	sDTKSHIN_KEY = Form1->Edt3_WHR_DTKSHIN->Text;
            break;
        // 「材料証明書（月別）上」にフォーカスが有る場合
        case 10:
        case 11:
        	sDTKSHIN_KEY = Form1->Edt4_WHR_DTKSHIN1->Text;
            break;
        // 「材料証明書（月別）下」にフォーカスが有る場合
        case 12:
        case 13:
        case 14:
        	sDTKSHIN_KEY = Form1->Edt4_WHR_DTKSHIN2->Text;
            break;
        // 「検査結果時系列管理表」にフォーカスが有る場合
        case 15:
        case 16:
        case 31:
        case 32:
        	sDTKSHIN_KEY = Form1->Edt5_WHR_DTKSHIN1->Text;
            break;
        // 「検査経歴票上」にフォーカスが有る場合
        case 17:
        case 18:
        	sDTKSHIN_KEY = Form1->Edt6_WHR_DTKSHIN1->Text;
            break;
	 }

     switch( Form1->BtnF01->Tag ){

        // 得意先品番　にフォーカスが有る場合
        case 1:
        case 3:
        case 5:
        case 8:
        case 10:
        case 12:
        case 15:

            // 問合せ実行
            sBuf  = "select DISTINCT DTKSHIN, ";
            sBuf +=        "Count(LOTNO) AS LOTNO_CNT, ";
            sBuf +=        "Max(SKTYMD) AS SKTYMD_MAX ";
            sBuf += "from KSD01 ";
            if( sDTKSHIN_KEY.Trim() != "" ){
                // 得意先品番
                sBuf = sBuf + " where DTKSHIN like '";
                sBuf = sBuf + sDTKSHIN_KEY.Trim() ;
                sBuf = sBuf + "%'";
            }
            sBuf += "group by DTKSHIN ";
            sBuf += "order by DTKSHIN";

            // タイトルをセット
            SGr1->ColCount = 4;
            SGr1->Cells[0][0] = "   N O";
            SGr1->Cells[1][0] = "測定済み得意先品番";
            SGr1->Cells[2][0] = "測定LOT数";
            SGr1->Cells[3][0] = "最終測定日";
            SGr1->ColWidths[0] = 55;
            SGr1->ColWidths[1] = 200;
            SGr1->ColWidths[2] = 80;
            SGr1->ColWidths[3] = 90;
            iDateNo = 3;
            break;

        //2003/08/27 E.Takase
        //測定してないロットも出力できるようにする
        //→生産管理システムから検索する
        case 17:


            // 問合せ実行
            sBuf  = "select DISTINCT SD21S.DTKSHIN  AS DTKSHIN,  ";
            sBuf +=        "Count(SD21S.LOTBNG) AS LOTNO_CNT, ";
            sBuf +=        "Max(KSD01.SKTYMD) AS SKTYMD_MAX ";
            sBuf += "from SD21S, KSD01  ";
            sBuf += "where KSD01.LOTNO(+) = SD21S.LOTBNG  ";
            sBuf += "and KSD01.DTKSHIN(+) = SD21S.DTKSHIN  ";
            if( sDTKSHIN_KEY.Trim() != "" ){
                // 得意先品番
                sBuf = sBuf + " and SD21S.DTKSHIN like '";
                sBuf = sBuf + sDTKSHIN_KEY.Trim() ;
                sBuf = sBuf + "%'";
            }
            sBuf += "group by SD21S.DTKSHIN ";
            sBuf += "order by SD21S.DTKSHIN";

            // タイトルをセット
            SGr1->ColCount = 4;
            SGr1->Cells[0][0] = "   N O";
            SGr1->Cells[1][0] = "測定済み得意先品番";
            SGr1->Cells[2][0] = "測定LOT数";
            SGr1->Cells[3][0] = "最終測定日";
            SGr1->ColWidths[0] = 55;
            SGr1->ColWidths[1] = 200;
            SGr1->ColWidths[2] = 80;
            SGr1->ColWidths[3] = 90;
            iDateNo = 3;
            break;

        // ロットＮｏにフォーカスが有る場合
        case 2:
        case 4:
        case 9:
        case 11:
        case 16:

            // 問合せ実行
            sBuf = "select DTKSHIN, LOTNO, HINBAN, SKTYMD from KSD01 ";
            //if( sDTKSHIN_KEY.Trim() != "" ){
                // 得意先品番
                sBuf += "where DTKSHIN like '";
                sBuf += sDTKSHIN_KEY.Trim();
                sBuf += "%' ";
            //}
            sBuf += " AND  SKTYMD >= '" + Form1->Edt_SEIKAN_YMD->Text + "'";      //onishi
            sBuf += "order by DTKSHIN, HINBAN, substr(LOTNO,2)";

            // タイトルをセット
            SGr1->ColCount = 5;
            SGr1->Cells[0][0] = "   N O";
            SGr1->Cells[1][0] = "測定済み得意先品番";
            SGr1->Cells[2][0] = "測定済みLOTNO";
            SGr1->Cells[3][0] = "自社品番";
            SGr1->Cells[4][0] = "測定日";
            SGr1->ColWidths[0] = 55;
            SGr1->ColWidths[1] = 150;
            SGr1->ColWidths[2] = 100;
            SGr1->ColWidths[3] = 100;
            SGr1->ColWidths[4] = 90;
            iDateNo = 4;
            break;


        //2003/08/27 E.Takase
        //測定してないロットも出力できるようにする
        //→生産管理システムから検索する
        case 18:

            // 問合せ実行
            sBuf  = "select DISTINCT SD21S.DTKSHIN  AS DTKSHIN,  ";
            sBuf +=        "SD21S.LOTBNG AS LOTNO_CNT, ";
            sBuf +=        "KSD01.SKTYMD AS SKTYMD_MAX ";
            sBuf += "from SD21S, KSD01  ";
            sBuf += "where KSD01.LOTNO(+) = SD21S.LOTBNG  ";
            sBuf += "and KSD01.DTKSHIN(+) = SD21S.DTKSHIN  ";
            if( sDTKSHIN_KEY.Trim() != "" ){
                // 得意先品番
                sBuf = sBuf + " and SD21S.DTKSHIN like '";
                sBuf = sBuf + sDTKSHIN_KEY.Trim() ;
                sBuf = sBuf + "%'";
            }
            sBuf += "order by SD21S.DTKSHIN, substr(SD21S.LOTBNG,2)";

            // タイトルをセット
            SGr1->ColCount = 4;
            SGr1->Cells[0][0] = "   N O";
            SGr1->Cells[1][0] = "測定済み得意先品番";
            SGr1->Cells[2][0] = "測定済みLOTNO";
            SGr1->Cells[3][0] = "測定日";
            SGr1->ColWidths[0] = 55;
            SGr1->ColWidths[1] = 200;
            SGr1->ColWidths[2] = 100;
            SGr1->ColWidths[3] = 90;
            iDateNo = 3;
            break;

        // 出荷日にフォーカスが有る場合
        case 6:
        case 7:
        case 13:
        case 14:
        case 31:
        case 32:

            // 問合せ実行
            sBuf  = "select DTKSHIN, LOTBNG, ESYUYMD from SD21S ";
            sBuf += "where ESYUYMD != '00000000' ";
            if( sDTKSHIN_KEY.Trim() != "" ){
                // 得意先品番
                sBuf += "and DTKSHIN like '";
                sBuf += sDTKSHIN_KEY.Trim();
                sBuf += "%' ";
            }
            sBuf += " AND  ESYUYMD >= '" + Form1->Edt_SEIKAN_YMD->Text + "'";      //onishi
            sBuf += "order by DTKSHIN, ESYUYMD, substr(LOTBNG,2)";

            // タイトルをセット
            SGr1->ColCount = 4;
            SGr1->Cells[0][0] = "   N O";
            SGr1->Cells[1][0] = "出荷済み得意先品番";
            SGr1->Cells[2][0] = "出荷済みLOTNO";
            SGr1->Cells[3][0] = "出荷日";
            SGr1->ColWidths[0] = 55;
            SGr1->ColWidths[1] = 200;
            SGr1->ColWidths[2] = 100;
            SGr1->ColWidths[3] = 90;
            iDateNo = 3;
            break;

        // 検査日にフォーカスが有る場合
        case 19:
        case 20:

            // 問合せ実行
            sBuf  = "select DISTINCT SKTYMD_PRT from KSD01 ";
            sBuf += "where SKTYMD_PRT >= '00000000' and SKTYMD_PRT <= '99999999' ";
            sBuf += "order by SKTYMD_PRT";

            // タイトルをセット
            SGr1->ColCount = 2;
            SGr1->Cells[0][0] = "   N O";
            SGr1->Cells[1][0] = "検査日";
            SGr1->ColWidths[0] = 55;
            SGr1->ColWidths[1] = 100;
            iDateNo = 1;
            break;

        // レポート用社名（日本語）にフォーカスが有る場合
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:

            // 問合せ実行
            sBuf  = "select CORP_NAME from KSM93 ";
            if( Form1->BtnF01->Tag == 21 ||
                Form1->BtnF01->Tag == 23 ||
                Form1->BtnF01->Tag == 25 ||
                Form1->BtnF01->Tag == 27 ||
                Form1->BtnF01->Tag == 29 ){
            	sBuf += "where ENG_FLG = 0 ";
            } else {
            	sBuf += "where ENG_FLG = 1 ";
            }
            sBuf += "order by ORDER_NO";

            // タイトルをセット
            SGr1->ColCount = 2;
            SGr1->Cells[0][0] = "   N O";
            if( Form1->BtnF01->Tag == 21 ||
                Form1->BtnF01->Tag == 23 ||
                Form1->BtnF01->Tag == 25 ||
                Form1->BtnF01->Tag == 27 ||
                Form1->BtnF01->Tag == 29 ){
            	SGr1->Cells[1][0] = "社名（日本語）";
            } else {
            	SGr1->Cells[1][0] = "社名（英語）";
            }
            SGr1->ColWidths[0] = 55;
            SGr1->ColWidths[1] = 400;
            iDateNo = 0;
            break;
        // その他
        default:
            Close();
            return;
            break;
    }

    Query1->SQL->Add(sBuf);
    ClpBrd = Clipboard();
    ClpBrd->Open();
    ClpBrd->SetTextBuf(sBuf.c_str());
    ClpBrd->Close();
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
        SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 8-sBuf.Length()) + sBuf;

        // データ
        for( i=1; i<SGr1->ColCount; i++){
            sBuf = Query1->Fields->Fields[i-1]->AsString;
            if( i == iDateNo ){
            	// 日付フォーマットを整えます
                //2003/08/27 E.Takase 日付 空白のときは そのまま
                if ( sBuf.Trim() != "" ) {
					sBuf = sBuf.Insert("/",5);
					sBuf = sBuf.Insert("/",8);
                }
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
    SGr1->SetFocus();

	if( Form1->BtnF01->Tag == 19 || Form1->BtnF01->Tag == 20 ){
    	SGr1->Row = SGr1->RowCount - 1;		// 最後の行を選択
    } else {
    	SGr1->Row = 1;                  	// 最初の行を選択
    }
  	iRowSelTop    = SGr1->Row;
   	iRowSelBottom = SGr1->Row;

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
	AnsiString sBuf1;
	AnsiString sBuf2;

    if( !fFind )   return;

    // 選択フラグONの時
    if( SGr1->Tag ){

        // 範囲指定時のエラーチェック
        switch( Form1->BtnF01->Tag ){
        	// ロットＮｏにフォーカス
            case 2:
        	case 4:
        	case 9:
        	case 11:
        	case 16:
        	case 18:
                if( SGr1->Cells[1][iRowSelTop] != SGr1->Cells[1][iRowSelBottom] ){
					MessageDlg("異なる得意先品番同士は指定できません。", mtWarning,
								TMsgDlgButtons() << mbOK , 0);
                    CanClose = false;
                	return;
                }
                if( SGr1->Cells[2][iRowSelTop] != SGr1->Cells[2][iRowSelBottom] ){
                    int	i;
                    sBuf1 = "";
	    	        for( i=iRowSelTop; i<=iRowSelBottom; i++ ) {
    	            	if( SGr1->Cells[2][i].Trim() != "" )	{
                            if( sBuf1.Length() > 0 )	sBuf1 = sBuf1 + ",";
                        	sBuf1 = sBuf1 + SGr1->Cells[2][i].Trim();
                    	}
                	}
                } else {
                    sBuf1 = SGr1->Cells[2][iRowSelTop];
                }
                break;

        	// 出荷日にフォーカスが有る場合
        	case 6:
        	case 7:
        	case 13:
        	case 14:
        	case 31:
        	case 32:
                if( SGr1->Cells[1][iRowSelTop] != SGr1->Cells[1][iRowSelBottom] ){
					MessageDlg("異なる得意先品番同士は指定できません。", mtWarning,
								TMsgDlgButtons() << mbOK , 0);
                    CanClose = false;
                	return;
                }
                sBuf1	= SGr1->Cells[3][iRowSelTop];		// 範囲選択（開始）
                sBuf2	= SGr1->Cells[3][iRowSelBottom];	// 範囲選択（終了）
                break;

        	// 検査日にフォーカスが有る場合
        	case 19:
        	case 20:
                sBuf1	= SGr1->Cells[1][iRowSelTop];		// 範囲選択（開始）
                sBuf2	= SGr1->Cells[1][iRowSelBottom];	// 範囲選択（終了）
				break;
        }

        // 指定したデータをフィールドにセットします
        switch( Form1->BtnF01->Tag ){

            case 1:		// 「検査成績書」得意先品番にフォーカスが有る場合
                Form1->Edt1_WHR_DTKSHIN->Text = SGr1->Cells[1][SGr1->Row];
                break;

            case 2:		// 「検査成績書」ロットにフォーカスが有る場合
                Form1->Edt1_WHR_DTKSHIN->Text = SGr1->Cells[1][SGr1->Row];
               	Form1->Edt1_WHR_LOTNO->Text = sBuf1;
                break;

            case 3:		// 「検査成績書(月別)」得意先品番（上）にフォーカスが有る場合
                Form1->Edt2_WHR_DTKSHIN1->Text = SGr1->Cells[1][SGr1->Row];
                break;

            case 4:		// 「検査成績書(月別)」ロットにフォーカスが有る場合
                Form1->Edt2_WHR_DTKSHIN1->Text = SGr1->Cells[1][SGr1->Row];
               	Form1->Edt2_WHR_LOTNO1->Text = sBuf1;
                break;

            case 5:		// 「検査成績書(月別)」得意先品番（下）にフォーカスが有る場合
                Form1->Edt2_WHR_DTKSHIN2->Text = SGr1->Cells[1][SGr1->Row];
                break;

            case 6:		// 「検査成績書(月別)」出荷日（自）にフォーカスが有る場合
            case 7:		// 「検査成績書(月別)」出荷日（至）にフォーカスが有る場合
                Form1->Edt2_WHR_DTKSHIN2->Text = SGr1->Cells[1][SGr1->Row];
                if( sBuf1 == sBuf2 ){
                	if( Form1->BtnF01->Tag == 6 )	Form1->Edt2_WHR_SYUKADATE1->Text = sBuf1;
                	if( Form1->BtnF01->Tag == 7 )	Form1->Edt2_WHR_SYUKADATE2->Text = sBuf1;
                } else {
                	Form1->Edt2_WHR_SYUKADATE1->Text = sBuf1;
                	Form1->Edt2_WHR_SYUKADATE2->Text = sBuf2;
                }
                break;

            case 8:		// 「材料証明書」得意先品番にフォーカスが有る場合
                Form1->Edt3_WHR_DTKSHIN->Text = SGr1->Cells[1][SGr1->Row];
                break;

            case 9:		// 「材料証明書」ロットにフォーカスが有る場合
                Form1->Edt3_WHR_DTKSHIN->Text = SGr1->Cells[1][SGr1->Row];
               	Form1->Edt3_WHR_LOTNO->Text = sBuf1;
                break;

            case 10:	// 「材料証明書(月別)」得意先品番（上）にフォーカスが有る場合
                Form1->Edt4_WHR_DTKSHIN1->Text = SGr1->Cells[1][SGr1->Row];
                break;

            case 11:	// 「材料証明書(月別)」ロットにフォーカスが有る場合
                Form1->Edt4_WHR_DTKSHIN1->Text = SGr1->Cells[1][SGr1->Row];
               	Form1->Edt4_WHR_LOTNO1->Text = sBuf1;
                break;

            case 12:	// 「材料証明書(月別)」得意先品番（下）にフォーカスが有る場合
                Form1->Edt4_WHR_DTKSHIN2->Text = SGr1->Cells[1][SGr1->Row];
                break;

            case 13:	// 「材料証明書(月別)」出荷日（自）にフォーカスが有る場合
            case 14:	// 「材料証明書(月別)」出荷日（至）にフォーカスが有る場合
                Form1->Edt4_WHR_DTKSHIN2->Text = SGr1->Cells[1][SGr1->Row];
                if( sBuf1 == sBuf2 ){
                	if( Form1->BtnF01->Tag == 13 )	Form1->Edt4_WHR_SYUKADATE1->Text = sBuf1;
                	if( Form1->BtnF01->Tag == 14 )	Form1->Edt4_WHR_SYUKADATE2->Text = sBuf1;
                } else {
                	Form1->Edt4_WHR_SYUKADATE1->Text = sBuf1;
                	Form1->Edt4_WHR_SYUKADATE2->Text = sBuf2;
                }
                break;

            case 15:	// 「検査結果時系列管理表」得意先品番にフォーカスが有る場合
                Form1->Edt5_WHR_DTKSHIN1->Text = SGr1->Cells[1][SGr1->Row];
                break;

            case 16:	// 「検査結果時系列管理表」ロットにフォーカスが有る場合
                Form1->Edt5_WHR_DTKSHIN1->Text = SGr1->Cells[1][SGr1->Row];
               	Form1->Edt5_WHR_LOTNO->Text = sBuf1;
                break;

            case 17:	// 「検査経歴票」得意先品番（上）にフォーカスが有る場合
                Form1->Edt6_WHR_DTKSHIN1->Text = SGr1->Cells[1][SGr1->Row];
                break;

            case 18:	// 「検査経歴票」ロットにフォーカスが有る場合
                Form1->Edt6_WHR_DTKSHIN1->Text = SGr1->Cells[1][SGr1->Row];
               	Form1->Edt6_WHR_LOTNO1->Text = sBuf1;
                break;

            case 19:	// 「検査経歴票」検査日（自）にフォーカスが有る場合
            case 20:	// 「検査経歴票」検査日（至）にフォーカスが有る場合
                if( sBuf1 == sBuf2 ){
                	if( Form1->BtnF01->Tag == 19 )	Form1->Edt6_WHR_KENSADATE1->Text = sBuf1;
                	if( Form1->BtnF01->Tag == 20 )	Form1->Edt6_WHR_KENSADATE2->Text = sBuf1;
                } else {
                	Form1->Edt6_WHR_KENSADATE1->Text = sBuf1;
                	Form1->Edt6_WHR_KENSADATE2->Text = sBuf2;
                }
                break;

        	case 21:	// 「検査成績書」社名にフォーカスが有る場合
        	case 22:
                Form1->Edt1_CHK_CUSTOMER->Text = SGr1->Cells[1][SGr1->Row];
                break;

        	case 23:  	// 「検査成績書(月別)」社名にフォーカスが有る場合
        	case 24:
                Form1->Edt2_CHK_CUSTOMER->Text = SGr1->Cells[1][SGr1->Row];
                break;

        	case 25:    // 「材料証明書」社名にフォーカスが有る場合
        	case 26:
                Form1->Edt3_CHK_CUSTOMER->Text = SGr1->Cells[1][SGr1->Row];
                break;

        	case 27:    // 「材料証明書(月別)」社名にフォーカスが有る場合
        	case 28:
                Form1->Edt4_CHK_CUSTOMER->Text = SGr1->Cells[1][SGr1->Row];
                break;

        	case 29:    // 「検査結果時系列管理表」社名（日本語）にフォーカスが有る場合
                Form1->Edt5_CHK_CUSTOMER->Text = SGr1->Cells[1][SGr1->Row];
                break;

        	case 30:    // 「検査結果時系列管理表」社名（英語）にフォーカスが有る場合
                Form1->Edt5_CHK_CUSTOMER2->Text = SGr1->Cells[1][SGr1->Row];
                break;

            case 31:	// 「検査結果時系列管理表」出荷日（自）にフォーカスが有る場合
            case 32:	// 「検査結果時系列管理表」出荷日（至）にフォーカスが有る場合
                Form1->Edt5_WHR_DTKSHIN1->Text = SGr1->Cells[1][SGr1->Row];
                if( sBuf1 == sBuf2 ){
                	if( Form1->BtnF01->Tag == 31 )	Form1->Edt5_WHR_SYUKADATE1->Text = sBuf1;
                	if( Form1->BtnF01->Tag == 32 )	Form1->Edt5_WHR_SYUKADATE2->Text = sBuf1;
                } else {
                	Form1->Edt5_WHR_SYUKADATE1->Text = sBuf1;
                	Form1->Edt5_WHR_SYUKADATE2->Text = sBuf2;
                }
                break;
        }

    }

}



