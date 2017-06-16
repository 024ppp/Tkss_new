//---------------------------------------------------------------------------
//
//  Unit1.cpp
//    【出荷検査システム－備考事前登録】
//    メインフォーム（TForm1クラス）のメンバ関数の定義
//
//  作成者
//    市川　和弘
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
KSD91_DATA Tmp_KSD91;             //選択した備考データ

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
    SGr_List->ColCount = 12;
    SGr_List->RowCount = 2;
	SGr_List->ColWidths[0] = 45;
	SGr_List->ColWidths[1] = 150;
	SGr_List->ColWidths[2] = 70;
	SGr_List->ColWidths[3] = 490;
	SGr_List->ColWidths[4] = 80;
	SGr_List->ColWidths[5] = 70;
	SGr_List->ColWidths[6] = 0;
	SGr_List->ColWidths[7] = 0;
	SGr_List->ColWidths[8] = 0;
	SGr_List->ColWidths[9] = 0;
	SGr_List->ColWidths[10] = 0;
	SGr_List->ColWidths[11] = 80;

	SGr_List->Cells[0][0] = " NO";
	SGr_List->Cells[1][0] = "品　番";
	SGr_List->Cells[2][0] = "ロット";
	SGr_List->Cells[3][0] = "備　考";
	SGr_List->Cells[4][0] = "更新日";
	SGr_List->Cells[5][0] = "更新者";
	SGr_List->Cells[6][0] = "更新者(担当者コード)";
	SGr_List->Cells[7][0] = "登録日";
	SGr_List->Cells[8][0] = "登録時間";
	SGr_List->Cells[9][0] = "変更時間";
	SGr_List->Cells[10][0] = "更新回数";
	SGr_List->Cells[11][0] = "自社品番";

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

    NotFound = true;

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
//    AnsiString str	：コマンドライン文字列
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
//    一覧検索画面（Form5）を表示します
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
//    指定された得意先品番、ロットNOの情報を元に検索処理を開始します
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
        //Ｅｄｉｔをクリアー
        EdtHIN->Text = "";
        EdtLOT->Text = "";
        EdtSETHIN->Text = "";
        EdtSETLOT->Text = "";
        EdtSETBAN->Text = "";
        EdtMAXBAN->Text = "";
        EdtSETMEMO->Text = "";
        // ステータスメッセージ
        SBr1->Panels->Items[0]->Text = "得意先品番が製品規格マスタに登録されていません";
        SBr1->Update();
        EdtHIN->SetFocus();
     	// ボタンの初期化
     	BtnF01->Enabled = false;
     	BtnF02->Enabled = false;
     	BtnF03->Enabled = false;
     	BtnF04->Enabled = false;
     	BtnF05->Enabled = true;
     	BtnF06->Enabled = false;
     	BtnF07->Enabled = true;
     	BtnF08->Enabled = true;
     	BtnF09->Enabled = false;
     	BtnF10->Enabled = false;
//     	BtnF11->Enabled = true;
     	BtnF12->Enabled = true;
        NotFound = true;
        return;

     }

     iRow = Form1->SGr_List->RowCount - 1;
     // 最下行をクリアー
     for( i = 0; i < Form1->SGr_List->ColCount; i++) {
         Form1->SGr_List->Cells[i][iRow]  = "";
     }

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
     NotFound = false;

     BtnF01->Enabled = false;
     Form1->SGr_ListSelectCell( Sender, 1, 0, true);
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ８：新規登録」ボタンを押した時の処理
//
//  機能説明
//    画面下に入力された項目をテーブル（KSD91）に登録します
//    上StringGridに一行追加します
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
void __fastcall TForm1::BtnF08Click(TObject *Sender)
{
    AnsiString sBuf;
    AnsiString sYMD;
    int i;
    if( !BtnF08->Enabled )    return;

    if(KSD91_Serch02())
    {
    //Tmp_KSD91初期化
       Tmp_KSD91_SYOKIKA();
     // データをバッファに格納します。
        if(EdtSETHIN->Text.IsEmpty())
        {
            MessageDlg("品番を入力してください。", mtWarning
                                    ,TMsgDlgButtons() << mbOK, 0);
            return;
        }
        else if(EdtSETLOT->Text.IsEmpty())
        {
            MessageDlg("ロットＮＯを入力してください。", mtWarning
                                    ,TMsgDlgButtons() << mbOK, 0);
            return;
        }
        else if(EdtSETMEMO->Text.IsEmpty())
        {
            MessageDlg("備考を入力してください。", mtWarning
                                    ,TMsgDlgButtons() << mbOK, 0);
            return;
        }

        // ステータスメッセージ
        SBr1->Panels->Items[0]->Text = "新規登録中です．．．しばらくお待ち下さい。";
        SBr1->Update();
        //得意先品番
        Tmp_KSD91.DTKSHIN = EdtSETHIN->Text;
        //ロット
        Tmp_KSD91.LOTNO = EdtSETLOT->Text;
        //備考
        Tmp_KSD91.MEMO = EdtSETMEMO->Text;
        // 登録日
        Tmp_KSD91.ADDYMD = FormatDateTime("yyyymmdd",Date());
        // 登録時間
        Tmp_KSD91.ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());
        // 更新日
        Tmp_KSD91.UPDYMD = FormatDateTime("yyyymmdd",Date());
        // 更新時間
        Tmp_KSD91.UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());
        // 更新者
        Tmp_KSD91.UPDCHR = USER_COD;
        // 更新回数
        Tmp_KSD91.UPDCNT = 0;
        //品番
        Tmp_KSD91.HINBAN = EdtSETBAN->Text;

        //AddData
        if( AddData() == False )
        {
            return;
        }
        //新規データをSGr_Listに表示
        // グリッドにデータをセットします。
        sBuf = SGr_List->RowCount-1;
        SGr_List->Cells[0][SGr_List->RowCount - 1] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;    //No

        sBuf = Tmp_KSD91.DTKSHIN;
        SGr_List->Cells[1][SGr_List->RowCount - 1] = sBuf;   //得意先品番

        sBuf = Tmp_KSD91.LOTNO;
        SGr_List->Cells[2][SGr_List->RowCount - 1] = sBuf;   //ロットNo

        sBuf = Tmp_KSD91.MEMO;
        SGr_List->Cells[3][SGr_List->RowCount - 1] = sBuf;   //備考

        sBuf = Tmp_KSD91.UPDYMD;
        sBuf = sBuf.Insert("/",5);
        sBuf = sBuf.Insert("/",8);
        SGr_List->Cells[4][SGr_List->RowCount - 1] = sBuf;   //更新日

        sBuf = Tmp_KSD91.UPDCHR;
        SGr_List->Cells[6][SGr_List->RowCount - 1] = sBuf;   //更新者(担当者コード)

        sBuf = USER_NAM;
        SGr_List->Cells[5][SGr_List->RowCount - 1] = sBuf;   //更新者

        sBuf = Tmp_KSD91.ADDYMD;
        SGr_List->Cells[7][SGr_List->RowCount - 1] = sBuf;   //登録日

        sBuf = Tmp_KSD91.ADDTIM;
        SGr_List->Cells[8][SGr_List->RowCount - 1] = sBuf;   //登録時間

        sBuf = Tmp_KSD91.UPDTIM;
        SGr_List->Cells[9][SGr_List->RowCount - 1] = sBuf;   //更新時間

        sBuf = Tmp_KSD91.UPDCNT;
        SGr_List->Cells[10][SGr_List->RowCount - 1] = sBuf;   //更新回数

        sBuf = Tmp_KSD91.HINBAN;
        SGr_List->Cells[11][SGr_List->RowCount - 1] = sBuf;   //自社品番

        // 一行増やす
        SGr_List->RowCount = SGr_List->RowCount + 1;


        // 最下行をクリアー
        for( i = 0; i < SGr_List->ColCount; i++)
        {
             SGr_List->Cells[i][SGr_List->RowCount-1]  = "";
        }

        // 新しい行を選択
        SGr_List->Row = SGr_List->RowCount - 1;

        SGr_List->SetFocus();

        SBr1->Panels->Items[0]->Text = "";
        SBr1->Update();

        // データを変更したフラグ
        DataSave = true;
        BtnF11->Enabled = true;
        SGr_ListSelectCell(Sender,1,SGr_List->RowCount-1,true);
     }
     else
     {
         MessageDlg("既に登録されているので、新規登録は出来ません。", mtWarning,
                TMsgDlgButtons() << mbOK , 0);
     }
     // ボタンの初期化
     BtnF01->Enabled = false;
     if(Form1->SGr_List->RowCount > 2)
     {
        BtnF02->Enabled = true;
        BtnF03->Enabled = true;
     }
     BtnF04->Enabled = false;
     BtnF05->Enabled = true;
     BtnF06->Enabled = false;
     BtnF07->Enabled = true;
     BtnF08->Enabled = true;
     if(Form1->SGr_List->RowCount > 2)
     {
        BtnF09->Enabled = true;
        BtnF10->Enabled = true;
     }
//     BtnF11->Enabled = true;
     BtnF12->Enabled = true;
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ９：修正」ボタンを押した時の処理
//
//  機能説明
//    上StringGridで選択されたデータに対して画面下に入力された項目に更新します
//    テーブル（KSD91）を更新します
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
    AnsiString sBuf;
    AnsiString sYMD;

    if(KSD91_Serch02()==true)
    {
     MessageDlg("修正元がありません。品番とロットを確認してください。", mtWarning,
                TMsgDlgButtons() << mbOK , 0);
     return;
    }

    // ステータスメッセージ
    SBr1->Panels->Items[0]->Text = "修正中です．．．しばらくお待ち下さい。";
    SBr1->Update();


    // データをバッファに格納します。
    if(EdtSETHIN->Text.IsEmpty()) {
        MessageDlg("品番を入力してください。", mtWarning
                                ,TMsgDlgButtons() << mbOK, 0);
        return;
	}
    else if(EdtSETLOT->Text.IsEmpty()) {
        MessageDlg("ロットＮＯを入力してください。", mtWarning
                                ,TMsgDlgButtons() << mbOK, 0);
        return;
    }
    else if(EdtSETMEMO->Text.IsEmpty()) {
        MessageDlg("備考を入力してください。", mtWarning
                                ,TMsgDlgButtons() << mbOK, 0);
        return;
    }

    //得意先品番
    Tmp_KSD91.DTKSHIN = EdtSETHIN->Text;
    //ロット
    Tmp_KSD91.LOTNO = EdtSETLOT->Text;
    //備考
    Tmp_KSD91.MEMO = EdtSETMEMO->Text;
    // 登録日
    Tmp_KSD91.ADDYMD = SGr_List->Cells[7][ROWPOINT]  ;
    // 登録時間
    Tmp_KSD91.ADDTIM = SGr_List->Cells[8][ROWPOINT]  ;
    // 更新日
    //20160804 修正時は更新日の自動取得をやめ、コントロールの値を使用する
    //Tmp_KSD91.UPDYMD = FormatDateTime("yyyymmdd",Date());
    Tmp_KSD91.UPDYMD = DelSEPA(EdtUPDYMD->Text);
    // 更新時間
    Tmp_KSD91.UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());
    // 更新者
    Tmp_KSD91.UPDCHR = USER_COD;

    // 更新回数
    if( SGr_List->Cells[10][SGr_List->Row] == "" ){
        Tmp_KSD91.UPDCNT  = 0;
    }
    else{
       Tmp_KSD91.UPDCNT  = StrToInt(SGr_List->Cells[10][SGr_List->Row]);
       Tmp_KSD91.UPDCNT += 1 ;                  // 更新回数
    }
    //自社品番
    Tmp_KSD91.HINBAN = EdtSETBAN->Text;

    if( CollectData() == False ){
       return;
    }
    // データを変更したフラグ
    DataSave = true;
    BtnF11->Enabled = true;

    // グリッドにデータをセットします。
    sBuf = SGr_List->RowCount;
//    SGr_List->Cells[0][SGr_List->RowCount - 1] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;    //No
//    SGr_List->Cells[0][ ROWPOINT ] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;    //No

    sBuf = Tmp_KSD91.DTKSHIN;
//    SGr_List->Cells[1][SGr_List->RowCount - 1] = sBuf;   //得意先品番
    SGr_List->Cells[1][ROWPOINT] = sBuf;   //得意先品番

    sBuf = Tmp_KSD91.LOTNO;
//    SGr_List->Cells[2][SGr_List->RowCount - 1] = sBuf;   //ロットNo
    SGr_List->Cells[2][ROWPOINT] = sBuf;   //ロットNo

    sBuf = Tmp_KSD91.MEMO;
//    SGr_List->Cells[3][SGr_List->RowCount - 1] = sBuf;   //備考
    SGr_List->Cells[3][ROWPOINT] = sBuf;   //備考

    sBuf = Tmp_KSD91.UPDYMD;
//    SGr_List->Cells[4][SGr_List->RowCount - 1] = sBuf;   //更新日
    sBuf = sBuf.Insert("/",5);
    sBuf = sBuf.Insert("/",8);
    SGr_List->Cells[4][ROWPOINT] = sBuf;   //更新日

    sBuf = Tmp_KSD91.UPDCHR;
//    SGr_List->Cells[5][SGr_List->RowCount - 1] = sBuf;   //更新者
    SGr_List->Cells[6][ROWPOINT] = sBuf;   //更新者(担当者コード)

    sBuf = USER_NAM;
    SGr_List->Cells[5][ROWPOINT] = sBuf;   //更新者

    sBuf = Tmp_KSD91.ADDYMD;
    SGr_List->Cells[7][ROWPOINT] = sBuf;   //ロットNo

    sBuf = Tmp_KSD91.ADDTIM;
    SGr_List->Cells[8][ROWPOINT] = sBuf;   //備考

    sBuf = Tmp_KSD91.UPDTIM;
    SGr_List->Cells[9][ROWPOINT] = sBuf;   //更新日

    sBuf = Tmp_KSD91.UPDCNT;
    SGr_List->Cells[10][ROWPOINT] = sBuf;   //更新者

    sBuf = Tmp_KSD91.HINBAN;
    SGr_List->Cells[11][ROWPOINT] = sBuf;   //自社品番

    SGr_List->SetFocus();

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();
    SGr_ListSelectCell(Sender,1,ROWPOINT,true);

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ１０：削除」ボタンを押した時の処理
//
//  機能説明
//    上StringGridで選択されたデータを削除します
//    テーブル（KSD91）のレコードを削除します
//    上StringGridの選択行も削除します
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
    int i;

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

    // データをバッファに格納します。
    //得意先品番
    Tmp_KSD91.DTKSHIN  = SGr_List->Cells[1][ROWPOINT];
    //ロット
    Tmp_KSD91.LOTNO  = SGr_List->Cells[2][ROWPOINT];
    //備考
    Tmp_KSD91.MEMO  = SGr_List->Cells[3][ROWPOINT];
    //更新日
    Tmp_KSD91.UPDYMD  = SGr_List->Cells[4][ROWPOINT];
    //更新者
//     Tmp_KSD91.UPDCHR  = SGr_List->Cells[6][ROWPOINT];
    //登録日
    Tmp_KSD91.ADDYMD  = SGr_List->Cells[7][ROWPOINT];
    //登録時間
    Tmp_KSD91.ADDTIM  = SGr_List->Cells[8][ROWPOINT];
    //更新時間
    Tmp_KSD91.UPDTIM  = SGr_List->Cells[9][ROWPOINT];
    //更新回数
//     Tmp_KSD91.UPDCNT  = SGr_List->Cells[10][ROWPOINT];
    //自社品番
    Tmp_KSD91.HINBAN  = SGr_List->Cells[11][ROWPOINT];


    // DelData
    if( DelData() == False ){
        return;
    }

    for( i = SGr_List->Row; i < (SGr_List->RowCount - 1); i++) {
        // グリッドの一行を削除します。
        SGr_List->Cells[1][i] = SGr_List->Cells[1][i+1];
        SGr_List->Cells[2][i] = SGr_List->Cells[2][i+1];
        SGr_List->Cells[3][i] = SGr_List->Cells[3][i+1];
        SGr_List->Cells[4][i] = SGr_List->Cells[4][i+1];
        SGr_List->Cells[5][i] = SGr_List->Cells[5][i+1];
        SGr_List->Cells[6][i] = SGr_List->Cells[6][i+1];
        SGr_List->Cells[7][i] = SGr_List->Cells[7][i+1];
        SGr_List->Cells[8][i] = SGr_List->Cells[8][i+1];
        SGr_List->Cells[9][i] = SGr_List->Cells[9][i+1];
        SGr_List->Cells[10][i] = SGr_List->Cells[10][i+1];
        SGr_List->Cells[11][i] = SGr_List->Cells[11][i+1];
    }

    // 一行減らす
    SGr_List->RowCount = SGr_List->RowCount - 1;

    // 新しい行を選択
    if( SGr_List->RowCount == SGr_List->Row) {
        SGr_List->Row = SGr_List->Row - 1;
    }
    else {
        SGr_List->Row = SGr_List->Row;
    }

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();
    SGr_ListSelectCell(Sender,1,SGr_List->Row,true);

    //SGr_List->SetFocus();

    // データを変更したフラグ
    DataSave = true;
    BtnF11->Enabled = true;

    // ボタン状態の変更
    BtnF02->Enabled = false;
    BtnF03->Enabled = false;
    BtnF09->Enabled = false;
    BtnF10->Enabled = false;

    if(Form1->SGr_List->RowCount > 2) {
        BtnF02->Enabled = true;
        BtnF03->Enabled = true;
    }
    if(Form1->SGr_List->RowCount > 2) {
        BtnF09->Enabled = true;
        BtnF10->Enabled = true;
    }
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ１１：保存」ボタンを押した時の処理
//
//  機能説明
//    更新の有ったデータを確定（Commit）します
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
    if( DataSave == true ) {
        nRet = MessageDlg("編集されています。保存しますか?", mtConfirmation,
               TMsgDlgButtons() << mbYes << mbCancel << mbNo, 0);
        if(nRet == mrYes ) {
            BtnF11Click(Sender);
            Close();
        }
        else if(nRet == mrCancel) {
        }
        else {
            DataSave = false;
            Close();
        }
    }
    else {
        Close();
    }
}

//---------------------------------------------------------------------------
//
//  概要
//    OnSelectCellイベント：StringGridのセルが選択される前に発生します。
//
//  機能説明
//    StringGridで選択されたら、画面下部に詳細内容をセットします
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
void __fastcall TForm1::SGr_ListSelectCell(TObject *Sender, int ACol, int ARow,
      bool &CanSelect)
{
    if(ARow == 0) ARow = 1;
    ROWPOINT = ARow;

    //No
    //得意先品番
    if ( Trim(SGr_List->Cells[1][ARow]) == "" ) {
        EdtSETHIN->Text = "";
    }
    else {
        EdtSETHIN->Text = SGr_List->Cells[1][ARow];
    }

    //ロット
    if ( Trim(SGr_List->Cells[2][ARow]) == "" ) {
        EdtSETLOT->Text = "";
    }
    else {
        EdtSETLOT->Text = SGr_List->Cells[2][ARow];
    }

    //備考
    if ( Trim(SGr_List->Cells[3][ARow]) == "" ) {
        EdtSETMEMO->Text = "";
    }
    else {
        EdtSETMEMO->Text = SGr_List->Cells[3][ARow];
    }

    //更新日
    //20160804 更新日を編集可能に
    //PnlUPDYMD->Caption = SGr_List->Cells[4][ARow];
    EdtUPDYMD->Text = SGr_List->Cells[4][ARow];

    //更新者
    PnlUPDCHR->Caption = SGr_List->Cells[5][ARow];

    //自社品番
    if ( Trim(SGr_List->Cells[11][ARow]) == "" ) {
        EdtSETBAN->Text = "";
    }
    else {
        EdtSETBAN->Text = SGr_List->Cells[11][ARow];
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

    switch(Key) {
         case VK_F1:  BtnF01Click(Sender);    Key = 0; break;
         case VK_F2:  BtnF02Click(Sender);    Key = 0; break;
         case VK_F3:  BtnF03Click(Sender);    Key = 0; break;
         case VK_F5:  BtnF05Click(Sender);    Key = 0; break;
         case VK_F7:  BtnF07Click(Sender);    Key = 0; break;
         case VK_F8:  BtnF08Click(Sender);    Key = 0; break;
         case VK_F9:  BtnF09Click(Sender);    Key = 0; break;
         case VK_F10: BtnF10Click(Sender);    Key = 0; break;
         case VK_F11: BtnF11Click(Sender);    Key = 0; break;
         case VK_F12: BtnF12Click(Sender);    Key = 0; break;


         // 前項
         case VK_UP:
         case VK_LEFT:
                if(EdtHIN->Focused() && EdtHIN->SelStart == 0 && EdtHIN->SelLength == 0){
                    break;
                }
                if(EdtLOT->Focused() && EdtLOT->SelStart == 0 && EdtLOT->SelLength == 0){
                    EdtHIN->SetFocus();
                    break;
                }
                break;

         // 次項
         case VK_DOWN:
         case VK_RIGHT:
                if(EdtHIN->Focused() && EdtHIN->SelStart == EdtHIN->Text.Length()  && EdtHIN->SelLength == 0){
                    //得意先品番から製品規格を求める
                    EdtLOT->SetFocus();
                    break;
                }
                if(EdtLOT->Focused() && EdtLOT->SelStart == EdtLOT->Text.Length()  && EdtLOT->SelLength == 0){
                    break;
                }

                break;


         // Enter
         case VK_RETURN:
                if( EdtHIN->Focused() || EdtSETHIN->Focused() || EdtSETLOT->Focused() ||
                	SGr_List->Focused() ){
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if( EdtLOT->Focused() ){
                    BtnF07Click(Sender);
                    break;
                }
                // 詳細部
                if( EdtSETMEMO->Focused() ){
                    BtnF08->SetFocus();
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

         // Enter
//         case VK_RETURN:Cmb1->SetFocus();
//                        BtnF01->Enabled = false;      break;
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
//    保存する場合は、Commitをコールしデータを保存します。
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
void __fastcall TForm1::AllKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
/*
     if( Key == 17 ){
          BtnF01->Caption = "一覧検索";
          BtnF02->Caption = "前項";
          BtnF03->Caption = "次項";
          BtnF04->Caption = "";
          BtnF05->Caption = "画面印刷";
          BtnF06->Caption = "";
          BtnF07->Caption = "検索";
          BtnF08->Caption = "新規登録";
          BtnF09->Caption = "修正";
          BtnF10->Caption = "削除";
          BtnF11->Caption = "保存";
          BtnF12->Caption = "戻る";

          if( NotFound ){
              BtnF01->Enabled = true;
              BtnF02->Enabled = false;
              BtnF03->Enabled = false;
              BtnF04->Enabled = false;
              BtnF05->Enabled = true;
              BtnF06->Enabled = true;
              BtnF07->Enabled = true;
              BtnF08->Enabled = true;
              BtnF09->Enabled = false;
              BtnF10->Enabled = false;
              BtnF11->Enabled = false;
              BtnF12->Enabled = true;
          }
          else{
              BtnF01->Enabled = true;
              BtnF02->Enabled = true;
              BtnF03->Enabled = true;
              BtnF04->Enabled = true;
              BtnF05->Enabled = true;
              BtnF06->Enabled = true;
              BtnF07->Enabled = true;
              BtnF08->Enabled = true;
              BtnF09->Enabled = true;
              BtnF10->Enabled = true;
              BtnF11->Enabled = true;
              BtnF12->Enabled = true;
          }
          BtnF01->Tag = 0;
          BtnF02->Tag = 0;
          BtnF03->Tag = 0;
          BtnF04->Tag = 0;
          BtnF05->Tag = 0;
          BtnF06->Tag = 0;
          BtnF07->Tag = 0;
          BtnF08->Tag = 0;
          BtnF09->Tag = 0;
          BtnF10->Tag = 0;
          BtnF11->Tag = 0;
          BtnF12->Tag = 0;
      }
*/
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
    //ビープ音ならさないようにする
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
void __fastcall TForm1::FormEnter(TObject *Sender)
{

    if( SGr_List->Tag == 1 )    return;
    if( BtnF01->Focused() )    return;

    // 得意先品番にフォーカスが有る場合
    if( EdtHIN->Focused() ) {
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

    // 品番にフォーカスが有る場合
    if( EdtSETHIN->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 3;
        return;
    }

    // ロットにフォーカスが有る場合
    if( EdtSETLOT->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 4;
        return;
    }

    // 備考にフォーカスが有る場合
    if( EdtSETMEMO->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 5;
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
//    最初のフォーカスの位置をセットします
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
//    入力文字のチェック前の変更フラグを設定します。
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
//20160804 年月日区切り文字除去関数
AnsiString __fastcall TForm1::DelSEPA(AnsiString sYMD)
{
    int         iPos;
    AnsiString  sRet;

    sRet = sYMD;
    while( (iPos = sRet.AnsiPos("/")) != 0){
        sRet.Delete(iPos,1);
    }

    return( sRet );
}



