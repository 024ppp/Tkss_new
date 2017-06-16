//---------------------------------------------------------------------------
//
//  Unit2.cpp
//    【出荷検査システム−測定データ削除】
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
         case VK_RETURN:
         case VK_F4:  BtnF04Click(Sender);    break;
         case VK_F12: BtnF12Click(Sender);    break;
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

    int i;
    int iRow;
    AnsiString sBuf;

    SGr1->Tag = 0;    // 選択フラグOFF

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    SGr1->Row = 1;     // 選択行の初期化

	//フォーカスの位置によりSQLと画面表示の変更
    switch( Form1->BtnF01->Tag )
    {
        case 1:
            sBuf  = "SELECT DISTINCT DTKSHIN, HINBAN, ZISNAM, HINMEI FROM KSD01";
            sBuf += " WHERE DTKSHIN LIKE '" + Form1->EdtHIN->Text + "%'";
            sBuf += " ORDER BY DTKSHIN";
            // タイトルをセット
            SGr1->ColCount = 5;
            SGr1->Cells[0][0] = "  N O";
            SGr1->Cells[1][0] = "得意先品番";
            SGr1->Cells[2][0] = "自社品番";
            SGr1->Cells[3][0] = "品　種";
            SGr1->Cells[4][0] = "品　名";
            SGr1->ColWidths[0] = 43;
            SGr1->ColWidths[1] = 163;
            SGr1->ColWidths[2] = 110;
            SGr1->ColWidths[3] = 110;
            SGr1->ColWidths[4] = 110;
            break;

        case 2:
            sBuf  = "SELECT DTKSHIN, LOTNO FROM KSD01";
            sBuf += " WHERE DTKSHIN LIKE '" + Form1->EdtHIN->Text + "%'";
            sBuf += " AND LOTNO LIKE '" + Form1->EdtLOT->Text + "%'";
            sBuf += " ORDER BY DTKSHIN, SUBSTR(LOTNO,2)";
            // タイトルをセット
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = "  N O";
            SGr1->Cells[1][0] = "得意先品番";
            SGr1->Cells[2][0] = "ロットNo";
            SGr1->ColWidths[0] = 43;
            SGr1->ColWidths[1] = 200;
            SGr1->ColWidths[2] = 100;
            break;

    }

    //問い合せ文実行
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
        if( sBuf.Length() > 6 )	sBuf = sBuf.SubString( sBuf.Length() - 5, 6 );
        SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 6-sBuf.Length()) + sBuf;

        // データ
        for( i=1; i<SGr1->ColCount; i++){
            sBuf = Query1->Fields->Fields[i-1]->AsString;
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

    if( !fFind )   return;

    // 選択フラグONの時
    if( SGr1->Tag ){

        switch( Form1->BtnF01->Tag ){

            // 検索部　代表得意先品番にフォーカスが有る場合
            case 1:
                Form1->EdtHIN->Text = SGr1->Cells[1][SGr1->Row];      	// 得意先品番
                Form1->EdtHIN->SetFocus();
                Form1->EdtHIN->SelectAll();
                break;

            // 検索部　ロットNOにフォーカスが有る場合
            case 2:
                Form1->EdtHIN->Text = SGr1->Cells[1][SGr1->Row];      	// 得意先品番
                Form1->EdtLOT->Text = SGr1->Cells[2][SGr1->Row];      	// ロットNO
                Form1->EdtLOT->SetFocus();
                Form1->EdtLOT->SelectAll();
                break;

        }
    }

}

