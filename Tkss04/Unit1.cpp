//---------------------------------------------------------------------------
//
//  Unit1.cpp
//    【出荷検査システム－測定データ削除】
//    メインフォーム（TForm1クラス）のメンバ関数の定義
//
//  作成者
//    田村　敦司
//
//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#pragma package(smart_init)
#pragma link "NumberEdit"
#pragma resource "*.dfm"

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
TForm1 *Form1;

int     USER_COD;
String  USER_NAM;
String  BUMO_COD;
String  BUMO_NAM;
bool    DataSave;

// メッセージ
AnsiString MSG_01 = "検索中です... しばらくお待ちください。" ;
AnsiString MSG_02 = "検索結果０件。" ;
AnsiString MSG_09 = "画面印刷中です... しばらくお待ちください。" ;

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
    Database1->Open();

	// グリッドの初期化
    SGr_List->ColCount = 13;
    SGr_List->RowCount = 2;
	SGr_List->ColWidths[ 0] = 55;
	SGr_List->ColWidths[ 1] = 160;
	SGr_List->ColWidths[ 2] = 60;
	SGr_List->ColWidths[ 3] = 140;
	SGr_List->ColWidths[ 4] = 120;
	SGr_List->ColWidths[ 5] = 120;
	SGr_List->ColWidths[ 6] = 160;
	SGr_List->ColWidths[ 7] = 45;
	SGr_List->ColWidths[ 8] = 60;
	SGr_List->ColWidths[ 9] = 60;
	SGr_List->ColWidths[10] = 80;
	SGr_List->ColWidths[11] = 80;
	SGr_List->ColWidths[12] = 80;

	SGr_List->Cells[ 0][0] = "  N O";
	SGr_List->Cells[ 1][0] = "品　番";
	SGr_List->Cells[ 2][0] = "ロットNO";
	SGr_List->Cells[ 3][0] = "自社品番";
	SGr_List->Cells[ 4][0] = "材　質";
	SGr_List->Cells[ 5][0] = "品　名";
	SGr_List->Cells[ 6][0] = "代表得意先名";
	SGr_List->Cells[ 7][0] = "項目数";
	SGr_List->Cells[ 8][0] = "素材判定";
	SGr_List->Cells[ 9][0] = "出荷判定";
	SGr_List->Cells[10][0] = "素材用測定日";
	SGr_List->Cells[11][0] = "出荷用測定日";
	SGr_List->Cells[12][0] = "代表更新者";


     // ボタンの初期化
     BtnF01->Enabled = false;    //カーソルが指定位置のときにTrue
     BtnF02->Enabled = false;
     BtnF03->Enabled = false;
     BtnF04->Enabled = false;
     BtnF05->Enabled = true;
     BtnF06->Enabled = false;
     BtnF07->Enabled = true;
     BtnF08->Enabled = true;
     BtnF09->Enabled = false;
     BtnF10->Enabled = false;
     BtnF11->Enabled = false;
     BtnF12->Enabled = true;

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
    //ユーザコード、ユーザ名、部署コード、部署名 抽出
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
     SBr1->Panels->Items[0]->Text = MSG_09;
     SBr1->Update();

     Form1->Print();

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ７：検索」ボタンを押した時の処理
//
//  機能説明
//    指定された得意先品番、ロットNOを元に検索処理を開始します
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
     int iRow,i;
     AnsiString sYMD;
     AnsiString sBuf;

     if( !BtnF07->Enabled )    return;

    // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = MSG_01;
     SBr1->Update();

     //SGr_List初期化
     Form1->SGr_List->RowCount = 2;      //最上行はコメント行
     iRow = Form1->SGr_List->RowCount;

     // 最上行をクリアー
     for( i = 0; i < Form1->SGr_List->ColCount; i++)
     {
         Form1->SGr_List->Cells[i][1]  = "";
     }

     // 最下行をクリアー
     for( i = 0; i < Form1->SGr_List->ColCount; i++)
     {
         Form1->SGr_List->Cells[i][iRow]  = "";
     }


     //トランザクション開始
     if ( MAIN_Serch01() == 0 )
     {
     	//検索結果 ０件
        // ステータスメッセージ
        Beep();
        SBr1->Panels->Items[0]->Text = "得意先品番が製品規格マスタに登録されていません";
        SBr1->Update();
        EdtHIN->SetFocus();
        return;
     }

     iRow = Form1->SGr_List->RowCount - 1;
     // 最下行をクリアー
     for( i = 0; i < Form1->SGr_List->ColCount; i++) {
         Form1->SGr_List->Cells[i][iRow]  = "";
     }

     // 選択行を選択しなおします。
	 SGr_ListClick(SGr_List);

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     Form1->SGr_List->SetFocus();


     // ボタン状態の変更
     BtnF02->Enabled = false;
     BtnF03->Enabled = false;
     BtnF09->Enabled = false;
     BtnF10->Enabled = false;

     if(Form1->SGr_List->RowCount  > 2)
     {
        BtnF02->Enabled = true;
        BtnF03->Enabled = true;
     }
     if(Form1->SGr_List->RowCount > 2)
     {
        BtnF09->Enabled = true;
        BtnF10->Enabled = true;
     }

     BtnF01->Enabled = false;
     SGr_List->Row = 1;
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ１０：削除」ボタンを押した時の処理
//
//  機能説明
//    選択した測定データ(KSD01,KSD02,KSD03,KSD11,KSD12)を削除します
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
    int i,k,m;
    int	iMovRow;

    if( !BtnF10->Enabled )    return;

    if( SGr_List->Cells[1][SGr_List->Row] == "" ){
        // ステータスメッセージ
        SBr1->Panels->Items[0]->Text = "削除対象ではありません。";
        SBr1->Update();
        SGr_List->SetFocus();
        return;
    }

    // ステータスメッセージ
    SBr1->Panels->Items[0]->Text = "削除中です．．．しばらくお待ち下さい。";
    SBr1->Update();

	// 選択されている範囲をメモリに格納します
    for( i=iRowSelTop; i<=iRowSelBottom; i++ ) {
    	if( SGr_List->Cells[1][i] != "" && SGr_List->Cells[2][i] != "" ){
                //20170406 Y.Onishi 「削除」実行時、自社品番を考慮
    		//if( DelData(SGr_List->Cells[1][i], SGr_List->Cells[2][i]) == False ){
    		if( DelData(SGr_List->Cells[1][i], SGr_List->Cells[2][i], SGr_List->Cells[3][i]) == False ){
	        	//return;
        	}
    	}
    }

    iMovRow = (iRowSelBottom - iRowSelTop) + 1;
  	if( SGr_List->Cells[1][iRowSelBottom] == "" && SGr_List->Cells[2][iRowSelBottom] == "" ){
    	if( iMovRow >= 2 )	iMovRow--;
    }

	// グリッドの行を一行上にコピーします。
    for( k = iRowSelTop; k < (SGr_List->RowCount - iMovRow); k++) {
       	for( m = 1; m <= 12; m++) {
           	SGr_List->Cells[m][k] = SGr_List->Cells[m][k+iMovRow];
       	}
    }
    SGr_List->Cells[0][k-1] = "";

    // 一行減らす
    SGr_List->RowCount = SGr_List->RowCount - iMovRow;

    // 新しい行を選択
    if( SGr_List->RowCount <= SGr_List->Row) {
        if( SGr_List->Row - iMovRow > 1 ){
        	SGr_List->Row = SGr_List->Row - iMovRow;
    	} else {
        	SGr_List->Row = 1;
        }
    }
    else {
        SGr_List->Row = SGr_List->Row;
    }

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

    // データを変更したフラグ
    DataSave = true;
    BtnF11->Enabled = true;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ１１：保存」ボタンを押した時の処理
//
//  機能説明
//    更新データを確定(Commit)します
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
     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "保存中です．．．しばらくお待ち下さい。";
     SBr1->Update();

     // 変更，挿入，削除を永続的に保存し，現在のトランザクションを終了
     if( Database1->InTransaction == True ){
         Database1->Commit();
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
//    OnKeyDownイベント	：ユーザーが任意のキーを押すと発生します
//
//  機能説明
//    ファンクションキー、矢印キー、Enterキーによりボタンを選択します
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
         case VK_F1:  BtnF01Click(Sender);    Key = 0; break;
         case VK_F2:  BtnF02Click(Sender);    Key = 0; break;
         case VK_F3:  BtnF03Click(Sender);    Key = 0; break;
         case VK_F5:  BtnF05Click(Sender);    Key = 0; break;
         case VK_F7:  BtnF07Click(Sender);    Key = 0; break;
         case VK_F10: BtnF10Click(Sender);    Key = 0; break;
         case VK_F11: BtnF11Click(Sender);    Key = 0; break;
         case VK_F12: BtnF12Click(Sender);    Key = 0; break;


         // 前項
         case VK_UP:
         case VK_LEFT:
                if(EdtHIN->Focused() && EdtHIN->SelStart == 0 && EdtHIN->SelLength == 0){
                    BtnF01->Enabled = true;
                    break;
                }
                if(EdtLOT->Focused() && EdtLOT->SelStart == 0 && EdtLOT->SelLength == 0){
                    BtnF01->Enabled = true;
                    EdtHIN->SetFocus();
                    break;
                }
                break;

         // 次項
         case VK_DOWN:
         case VK_RIGHT:
                if(EdtHIN->Focused() && EdtHIN->SelStart == EdtHIN->Text.Length()  && EdtHIN->SelLength == 0){
                    BtnF01->Enabled = true;
                    //得意先品番から製品規格を求める
                    EdtLOT->SetFocus();
                    break;
                }
                if(EdtLOT->Focused() && EdtLOT->SelStart == EdtLOT->Text.Length()  && EdtLOT->SelLength == 0){
                    BtnF01->Enabled = true;
                    break;
                }

                break;


         // Enter
         case VK_RETURN:
                if( EdtHIN->Focused() || SGr_List->Focused() ){
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if( EdtLOT->Focused() ){
                    BtnF07Click(Sender);
                    break;
                }
                break;

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
     EdtKeyPress(Sender,Key);
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
                if( Database1->InTransaction == True )  Database1->Commit();
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
//    OnEnterイベント	：各コントロールがフォーカスを取得した時
//
//  機能説明
//    フォーカス状態を判断し、「Ｆ１：一覧検索」ボタンの有効／無効を切り替えます
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
void __fastcall TForm1::AllKeyEnter(TObject *Sender)
{
    if(EdtHIN->Focused()){
        BtnF01->Enabled = true;
        return;
    }

//    if(EdtLOT->Focused()){
//        BtnF01->Enabled = true;
//        return;
//    }

    BtnF01->Enabled = false;

}


//---------------------------------------------------------------------------
//
//  概要
//    OnKeyPressイベント：単一の文字キーを押したときに発生します。
//
//  機能説明
//    RETURNコードをクリアーします
//    ビープ音ならさないようにする
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
void __fastcall TForm1::EdtKeyPress(TObject *Sender, char &Key)
{
    switch(Key)
    {
        // リターン
        case VK_RETURN:
            Key = 0;
            break;
    }
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

    // Initial Query
    Form1->Query2->Close();
    Form1->Query2->SQL->Clear();

    // 問合せ文作成
	sBuf = "SELECT TANNAM FROM SM12S";
	sBuf += " WHERE TANSYA=" + strTANSYA;

    Form1->Query2->SQL->Add(sBuf);
    Form1->Query2->Open();
    Form1->Query2->Active = true;

    if ( Form1->Query2->Bof == true && Form1->Query2->Eof == true)
    {
       return strTANSYA;
		//return " ";
    }
    else
    {
        Form1->Query2->First();
        sBuf = Form1->Query2->FieldValues["TANNAM"];
        return sBuf;
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

    if( SGr_List->Tag == 1 )    return;
    if( BtnF01->Focused() )    return;


    // 得意先品番にフォーカスが有る場合
    if( EdtHIN->Focused() )
    {
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 1;
        return;
    }

    // ロットにフォーカスが有る場合
    if( EdtLOT->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 2;
        return;
    }

    // 「F1：一覧検索」ボタンを使えないようにする
    BtnF01->Enabled = false;
    BtnF01->Tag = 0;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnActivateイベント	：フォームがアクティブになったときに発生します。
//
//  機能説明
//    初期フォーカスの位置を設定します
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
	EdtHIN->SetFocus();
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

    // 半角カンマはＤＢ登録時にエラーが発生する
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
void __fastcall TForm1::SGr_ListClick(TObject *Sender)
{
    TStringGrid* sg = dynamic_cast<TStringGrid*>(Sender);

   	iRowSelTop    = sg->Selection.Top;
   	iRowSelBottom = sg->Selection.Bottom;
}


