//---------------------------------------------------------------------------
//
//  Unit1.cpp
//    【出荷検査システム−検査画面】
//    メインフォーム（TForm1クラス）のメンバ関数の定義
//
//  作成者
//    市川　和弘
//
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit7.h"
#include "Unit8.h"
#include "Unit9.h"
#include "Unit10.h"
#include "Unit12.h"
#include "Thread.h"
#include "ThreadSozaiMain.h"
#include "CommThread.h"
#include "Tkss01.h"
#include "StdComm32.h"
#include <math.h>
//コンパイラオプション「デバッグ」と「リリース」選択状態により必要か不要か変わる
//コンパイラのバグか？？
//#include <windows.h>

// k.k
#include <vector>
using namespace std;
extern bool bLOTCHANGE;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "PERFGRAP"
#pragma link "NumberEdit"
#pragma resource "*.dfm"
TForm1 		*Form1;
// k.y 2003.05.17
//HANDLE		hInfoGlaph;
// k.y 2003.05.17
//extern 	GRAPH_DATA  *pInfoGlaph;
extern 	GRAPH_DATA  pInfoGlaph;
//KSM02_DATA 	*pInfoGlaph;
RSCOM 		RS232;
KIKAKU KIKAKU_MOJI;
bool bKASOU_MOVE;
extern int iPORT_NO;
int iDEBUG;
bool bHANTEI_DISP;
bool bCellWrite;        //機器からの取り込み時、フラグを強制的にONさせるおまじない。

//セル情報
extern HANDLE hCELLINFO_SOKU_SYUKA;
extern HANDLE hCELLINFO_RIRE_SYUKA;
extern HANDLE hCELLINFO_SOKU_SOZAI;
extern HANDLE hCELLINFO_RIRE_SOZAI;
extern CELLINFO_DATA *pCELLINFO_SOKU_SYUKA;
extern CELLINFO_DATA *pCELLINFO_RIRE_SYUKA;
extern CELLINFO_DATA *pCELLINFO_SOKU_SOZAI;
extern CELLINFO_DATA *pCELLINFO_RIRE_SOZAI;
extern int iPnl_SOZAI_InsNoCnt;
extern int iPnl_SOZAI_InsNameCnt;
extern int iPnl_SOZAI_InsKikiNameCnt;
extern int iPnl_SOZAI_InsSubBaseCnt;

//ロット割り当て＆ＫＳＤ01
//ロット割り当て
extern HANDLE hSOKU_KSD01_DATA;
extern KSD01_DATA *pSOKU_KSD01_DATA;
extern HANDLE hRIRE_KSD01_DATA;
extern KSD01_DATA *pRIRE_KSD01_DATA;

// k.y 2003.05.17
//extern HANDLE		hOldInfoGlaph;

// k.y 2003.05.17
//extern GRAPH_DATA	*pOldInfoGlaph;
extern GRAPH_DATA	pOldInfoGlaph;

int iKikiCnt;
int iSOKU_MEMO_CNT;
int iRIRE_MEMO_CNT;

extern RSCOM RS232;
extern int iRIREKI_KOMKCNT;        	    //履歴の項目数
int	iContCnt;               		    //出荷検査項目数
//extern 	GRAPH_DATA	*pInfoGlaph;
int iSOZAI_DEL_OrCnt;                   //Or表示数
int iSOZAI_DEL_SokuCnt;                 //Or表示数
bool bNGPLOT;
bool bINPUTLOT_OK;					    //入力ロットOKフラグ_
bool bQUIT_FLG;
int iPlotCol,iPlotRow;
int     USER_COD;
String  USER_NAM;
String  BUMO_COD;
String  BUMO_NAM;
AnsiString  sMEMO_NAME;
bool bBUNKATU_RIRE[1000];
bool bBUNKATU_SOKU[1000];
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

    // A.T 2003/05/08
    //ThreadSupport = true;		// スレッド対応する
    ThreadSupport = false;		// スレッド対応しない

    // K.K
    sHT_LOT = new TStringList;
    sShiji_Data = new TStringList;
    Graph_Format();

    // データベース初期化
    Database1->Open();


    //シリアルポート初期化コマンド
    TThread *FourThread = new CommThread( false );
    // 初期値設定

    // ScrollBoxのイベント取得用定義
    SaveSBx_Left_SOZAI_WndProc = SBx_Left_SOZAI->WindowProc;
    SBx_Left_SOZAI->WindowProc = SBx_Left_SOZAI_WndProc;
    SaveSBx_Left_SYUKA_WndProc = SBx_Left_SYUKA->WindowProc;
    SBx_Left_SYUKA->WindowProc = SBx_Left_SYUKA_WndProc;
    SaveSBx_vSOKU_MEMO_WndProc = SBx_vSOKU_MEMO->WindowProc;
    SBx_vSOKU_MEMO->WindowProc = SBx_vSOKU_MEMO_WndProc;
    SaveSBx_vRIRE_MEMO_WndProc = SBx_vRIRE_MEMO->WindowProc;
    SBx_vRIRE_MEMO->WindowProc = SBx_vRIRE_MEMO_WndProc;

    // ScrollBoxの移動ピッチを定義
    SBx_Left_SOZAI->VertScrollBar->Smooth = false;
    SBx_Left_SYUKA->VertScrollBar->Smooth = false;
    SBx_Left_SOZAI->VertScrollBar->Increment = 25;
    SBx_Left_SYUKA->VertScrollBar->Increment = 25;
    SBx_vSOKU_MEMO->HorzScrollBar->Smooth = false;
    SBx_vSOKU_MEMO->HorzScrollBar->Increment = (TScrollBarInc)Mem_vSOKU_MEMOORG->Width;
    SBx_vRIRE_MEMO->HorzScrollBar->Smooth = false;
    SBx_vRIRE_MEMO->HorzScrollBar->Increment = (TScrollBarInc)Mem_vRIRE_MEMOORG->Width;
    // StringGridの１列目の幅を少し調整します。移動ピッチを定義
    SGr_tRIRE->ColWidths[0]       = SGr_tRIRE->ColWidths[0]       - 1;
    SGr_tRIRE_SOZAI->ColWidths[0] = SGr_tRIRE_SOZAI->ColWidths[0] - 1;
    SGr_tSOKU->ColWidths[0]       = SGr_tSOKU->ColWidths[0]       - 1;
    SGr_tSOKU_SOZAI->ColWidths[0] = SGr_tSOKU_SOZAI->ColWidths[0] - 1;
    SGr_tRIRE_SYUKA->ColWidths[0] = SGr_tRIRE_SYUKA->ColWidths[0] - 1;
    SGr_tSOKU_SYUKA->ColWidths[0] = SGr_tSOKU_SYUKA->ColWidths[0] - 1;

    // スプリッター位置変更用の初期位置を設定
    Panel22->Tag 	= Panel22->Height;
    Panel14->Tag 	= Panel14->Width;
    Panel173->Tag 	= Panel173->Height;
    Pnl_skInfo->Tag	= Pnl_skInfo->Width;

    // 初期状態での表示パネル＆非表示パネルを設定します。
    Panel22->Height   = 0;		// 素材検査　非表示
    //Panel173->Height  = 0;	// 備考　　　　表示
    Panel14->Width    = 0;		// 履歴値　　非表示
    //Pnl_skInfo->Width = 0;	// グラフ　　　表示

    Edt_RIRE_NUM->Height = 18;
    //動的コントロールの初期化
    iPnl_InsNoCnt = 0;
    iPnl_InsNameCnt = 0;
    iPnl_InsKikiNameCnt = 0;
    iPnl_InsSubBaseCnt = 0;
    //動的コントロールの初期化
    iPnl_SOZAI_InsNoCnt = 0;
    iPnl_SOZAI_InsNameCnt = 0;
    iPnl_SOZAI_InsKikiNameCnt = 0;
    iPnl_SOZAI_InsSubBaseCnt = 0;
    //その他初期値
    bCursolMove = false;
    PnlArrow->Caption ="→";
    bEnterMove = false;
    bKASOU_MOVE = false;
    bHANTEI_DISP = false;
    iOrCnt = 0;
    iPnl_InsKikiNameCnt = 0;
    iSokuSuu=0;
    iRecordCount = 0;
    iKikiCount = 0;
    iRIREKI_KOMKCNT = 0;
    iPnl_InsKikiNameCnt=0;
    iKikiCnt = 0;
    iContCnt = 0;
    iSOKU_MEMO_CNT = 0;
    iRIRE_MEMO_CNT = 0;
    bCellWrite = false;
    // StringListの初期化	A.Tamura
    sRIREKI_LOT = new TStringList;
    //グラフインフォメーションの初期化
    // メモリの開放
    memset(&pInfoGlaph,(int)NULL,sizeof(pInfoGlaph));
    bINPUTLOT_OK = false;					//入力ロットOKフラグ_
    bQUIT_FLG = false;
    bSOZAI_NASI = true;
    bNowLotF7 = false;
}

//---------------------------------------------------------------------------
//
//  概要
//    OnShowイベント	：フォームがショウになったときに発生します。
//
//  機能説明
//    メイン画面の最初のフォーカスをセットします
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
void __fastcall TForm1::FormShow(TObject *Sender)
{
    // 最初のフォーカスセット
    Cmb_DTKSHIN->SetFocus();

}
//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ１：一覧検索」ボタンを押した時の処理
//
//  機能説明
//    一覧検索画面（Form2）を表示します
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
    if( !BtnF01->Enabled ) return;
    if( !BtnF01->Tag ){
        ////////////////////
        // 一覧検索
        Form2->ShowModal();
    }
    else{
        ////////////////////
        // 全情報表示／非表示
        if( Panel22->Height   > 0 &&
            Panel173->Height  > 0 &&
            Panel14->Width    > 0 &&
            Pnl_skInfo->Width > 0 ){
            // 全て表示された状態の時、全て非表示
	        Panel22->Height   = 0;
	        Panel173->Height  = 0;
        	Panel14->Width    = 0;
        	Pnl_skInfo->Width = 0;
		} else{
            // いずれかが表示された状態の時、全て表示
            // または、全て非表示の状態の時、全て表示
	        Panel22->Height   = Panel22->Tag;
	        Panel173->Height  = Panel173->Tag;
        	Panel14->Width    = Panel14->Tag;
        	Pnl_skInfo->Width = Pnl_skInfo->Tag;
		}
    }
}
//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ２：前項」ボタンを押した時の処理
//
//  機能説明
//    CtrlOFF：アクティブセルの位置を一つ前に移動します
//    CtrlON ：素材値表示／非表示切り替え
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
    if( !BtnF02->Enabled ) return;
    if( !BtnF02->Tag ){

        //前項への移動
        SGr_vSOKU_SYUKA->EditorMode = false;
		//GridSetPointMove(Sender, VK_F2);
        //SenderがVK_F2だとEditBoxが開いてしまう為、プログラム中はVK_F13として扱っています
		GridSetPointMove(Sender, VK_F13);
    }
    else{
        ////////////////////
        // 素材値表示／非表示
        if( Panel22->Height <= 0 )
	        Panel22->Height = Panel22->Tag;
		else
	        Panel22->Height = 0;

    }
}
//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ３：次項」ボタンを押した時の処理
//
//  機能説明
//    CtrlOFF：アクティブセルの位置を次に移動します
//    CtrlON ：履歴値表示／非表示切り替え
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
    if( !BtnF03->Enabled ) return;
    if( !BtnF03->Tag ){
        ////////////////////
        // 次項
		GridSetPointMove(Sender, VK_F3);


    }
    else{
        ////////////////////
        // 履歴値表示／非表示
        if( Panel14->Width <= 0 )
        	Panel14->Width = Panel14->Tag;
		else
        	Panel14->Width = 0;
    }
}
//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ４：カーソル方向」ボタンを押した時の処理
//
//  機能説明
//    CtrlOFF：カーソル方向→／↓の切り替え
//    CtrlON ：グラフ表示／非表示切り替え
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
void __fastcall TForm1::BtnF04Click(TObject *Sender)
{
    if( !BtnF04->Enabled ) return;
    if( !BtnF04->Tag ){
        ////////////////////
        // カーソル方向
        if(bCursolMove)
        {
            bCursolMove = false;
			PnlArrow->Caption ="→";
        }
        else
        {
            bCursolMove = true;
			PnlArrow->Caption ="↓";
        }
    }
    else{
        ////////////////////
        // グラフ表示／非表示
        if( Pnl_skInfo->Width <= 0 )
        	Pnl_skInfo->Width = Pnl_skInfo->Tag;
        else
        	Pnl_skInfo->Width = 0;
    }
}
//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ５：ＣＨ切替」ボタンを押した時の処理
//
//  機能説明
//    CtrlOFF：ＣＨ切り替え
//    CtrlON ：備考欄表示／非表示切り替え
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
    unsigned short shtHoge=17;
    if( !BtnF05->Enabled ) return;
    if( !BtnF05->Tag ){
        ////////////////////
        // Ch切替
        //別スレッドで動作している通信モジュールにポート番号を指示します(０〜３）
		iPORT_NO ++;
		if( iPORT_NO> 4 ) iPORT_NO = 0;

    }
    else{
        ////////////////////
        // 備考欄表示／非表示
        if( Panel173->Height <= 0 )
	        Panel173->Height = Panel173->Tag;
		else
	        Panel173->Height = 0;

    }
    TShiftState State;
    AllKeyUp(Sender,shtHoge,State);	// ファンクションキーの状態を元に戻します。
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ６：ＨＴ読込／項目編集」ボタンを押した時の処理
//
//  機能説明
//    CtrlOFF：ハンディーターミナル読み込み
//    CtrlON ：項目編集画面（Form3）を表示します
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
void __fastcall TForm1::BtnF06Click(TObject *Sender)
{
    int rtn;
    int iCnt;
    int i;
    int j;
    int iCol;
    bool bHan;
    unsigned short shtHoge=17;
    vector<AnsiString> sBufHinban;
    vector<AnsiString> sBufLot;
    AnsiString sBuf;
    AnsiString sLot;
    TMsgDlgButtons MsgButton;

    if( !BtnF06->Enabled ) return;
    if( !BtnF06->Tag ){
        ////////////////////
        // ＨＴ読込
        // k.k start
        // 初期化
        Cmb_DTKSHIN->Clear();
        sHT_LOT->Clear();
        sShiji_Data->Clear();
        // 指示データUPLOAD
        rtn = DataUpLoad();
        if (rtn < 0) {
            MessageDlg("指示データの取得に失敗しました。", mtError, TMsgDlgButtons() << mbOK, 0);
            return;
        }
        iCnt = sShiji_Data->Count;
        // 品番、LOTに分割 ansistrings
        for (i = 0; i < iCnt; i++) {
            // 品番とLOTに分割
            sBufLot.push_back(Trim(sShiji_Data->Strings[i].SubString(27,6)));  		// LOT
            sBufHinban.push_back(Trim(sShiji_Data->Strings[i].SubString(7,20)));    // 品番
        }
        // ソート
        for (i = 0; i < iCnt-1;i++) {
            for (j = i + 1; j < iCnt;j++) {
                // j要素の値が小さい場合
                if (sBufHinban[i] > sBufHinban[j]) {
                        // 品番
                        sBuf = sBufHinban[i];           // バッファに保存
                        sBufHinban[i] = sBufHinban[j];  // j要素をi要素に置換
                        sBufHinban[j] = sBuf;           // j要素をi要素に置換
                        // LOT
                        sBuf = sBufLot[i];              // バッファに保存
                        sBufLot[i] = sBufLot[j];        // j要素をi要素に置換
                        sBufLot[j] = sBuf;              // j要素をi要素に置換
                }
                // 同値の場合
                if (sBufHinban[i] == sBufHinban[j]) {
                    // ロットのソート
                    // ロットのサイズ判断
                    if (sBufLot[i].Length() == 5) {
                        // ５バイトの場合、下４桁でソート
                        if (sBufLot[i].SubString(2, 4) > sBufLot[j].SubString(2, 4)) {
                            // LOT
                            sBuf = sBufLot[i];          // バッファに保存
                            sBufLot[i] = sBufLot[j];    // j要素をi要素に置換
                            sBufLot[j] = sBuf;          // j要素をi要素に置換
                        }
                    } else {
                        // ５バイト以外の場合、全桁でソート
                        if (sBufLot[i] > sBufLot[j]) {
                            // LOT
                            sBuf = sBufLot[i];          // バッファに保存
                            sBufLot[i] = sBufLot[j];    // j要素をi要素に置換
                            sBufLot[j] = sBuf;          // j要素をi要素に置換
                        }
                    }
                }
            }
        }

        // 品番、LOTリスト作成
        for (i = 0; i < iCnt; i++) {
            if ( i != 0) {
                // １つ前の品番と同じ場合、LOTをカンマ区切りで繋げる
                if (sBufHinban[i] == sBuf) {
                    sLot += "," + sBufLot[i];
                // 品番が変更されたら、コンボボックス、リストボックスに格納
                } else {
                    sHT_LOT->Add(sLot);
                    Cmb_DTKSHIN->Items->Add(sBuf);
                    sBuf = sBufHinban[i];
                    sLot = sBufLot[i];
                }
            } else {
                sBuf = sBufHinban[i];
                sLot = sBufLot[i];
            }
        }
        // 最後の配列分を追加
        sHT_LOT->Add(sLot);
        Cmb_DTKSHIN->Items->Add(sBuf);
        // "1/x"を表示
        iCnt = sHT_LOT->Count;
        sBuf = "1/" + AnsiString(iCnt);
        Lab_Num->Caption = sBuf;
        // 先頭を表示
        Cmb_DTKSHIN->Text = Cmb_DTKSHIN->Items->Strings[0];
        Edt_LOTNO->Text = sHT_LOT->Strings[0];
		//2003.05.09 E.Takase Add↓
		sNowDTKSHIN = Cmb_DTKSHIN->Text;
		sNowLOTNO = Edt_LOTNO->Text;
		//2003.05.09 E.Takase Add↑

    }
    else{
        ////////////////////
        // 項目編集
	    TShiftState State;

        //有効なロット入力があるかを判断します
	    if( !bINPUTLOT_OK )
		{
       		sBuf  = "有効なロットが入力されていない為項目編集は出来ません。";
			MsgButton << mbOK;
        	MessageDlg( sBuf, mtWarning	, MsgButton, 0);
    		//AllKeyUp( Sender,17,State);	// ファンクションキーの状態を元に戻します。
    		AllKeyUp( Sender ,shtHoge,State);	// ファンクションキーの状態を元に戻します。
        	return;
    	}
        // 現在カーソルの有る品番・ロットの指定
		//2003.05.09 E.Takase Add↓
        Form3->sNOW_DTKSHIN	= sNowDTKSHIN;
		//2003.05.09 E.Takase Add↑
		//2003.05.09 E.Takase Add コメント↓
        //Form3->sNOW_DTKSHIN	= Cmb_DTKSHIN->Text;
		//2003.05.09 E.Takase Add コメント↑
        //対象となるロットを引き当てます
		switch(pInfoGlaph.GRID_NO)
		{
		case 1:
        	Form3->sNOW_LOTNO	= SGr_tSOKU->Cells[SGr_vSOKU_SYUKA->Col][0];
			break;
		case 2:
        	Form3->sNOW_LOTNO	= SGr_tRIRE->Cells[SGr_vRIRE_SYUKA->Col][0];
			break;
		case 3:
        	Form3->sNOW_LOTNO	= SGr_tSOKU->Cells[SGr_vSOKU_SOZAI->Col][0];
			break;
		case 4:
        	Form3->sNOW_LOTNO	= SGr_tRIRE->Cells[SGr_vRIRE_SOZAI->Col][0];
			break;
		}

        if( Form3->sNOW_LOTNO.Trim() == "" ){
			MessageDlg( "対象ロットNOを選択して下さい。", mtInformation, TMsgDlgButtons() << mbOK , 0);
    		//AllKeyUp(Sender,17,State);	// ファンクションキーの状態を元に戻します。
    		AllKeyUp( Sender  ,shtHoge,State);	// ファンクションキーの状態を元に戻します。
            return;
        }

    	// 確認メッセージ
// 【※】データが編集されている場合だけ、確認メッセージの表示を行なう
        if( MessageDlg( "項目編集を行なうには、現在の測定データを保存する必要があります。\n保存を行い処理を続行します。よろしいですか？",
            mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo ){
            //AllKeyUp(Sender,17,State);	// ファンクションキーの状態を元に戻します。
            AllKeyUp(Sender ,shtHoge,State);	// ファンクションキーの状態を元に戻します。
            return;
        }
/*
        //アップデートフラグを強制ONします
		if( hSOKU_KSD01_DATA)
		{
			for(iCol = 0; iCol<SGr_tSOKU->ColCount;iCol++)
			{
				pSOKU_KSD01_DATA[iCol].UPD_FLG = true;
				pSOKU_KSD01_DATA[iCol].SAVE_FLG = false;
			}
    	}

        //アップデートフラグを強制ONします
		if( hRIRE_KSD01_DATA && Form1->iRIRE_CNT != 0)
		{
			for(iCol = 0; iCol<SGr_tRIRE->ColCount;iCol++)
			{
				pRIRE_KSD01_DATA[iCol].UPD_FLG = true;
				pRIRE_KSD01_DATA[iCol].SAVE_FLG = false;
			}
		}
*/
        //対象となるロットのアップデートフラグを強制ONします
		switch(pInfoGlaph.GRID_NO)
		{
		case 1:
        	//Form3->sNOW_LOTNO	= SGr_tSOKU->Cells[SGr_vSOKU_SYUKA->Col][0];
            iCol = SGr_vSOKU_SYUKA->Col;
            pSOKU_KSD01_DATA[iCol].UPD_FLG = true;
            pSOKU_KSD01_DATA[iCol].SAVE_FLG = false;
			break;
		case 2:
        	//Form3->sNOW_LOTNO	= SGr_tRIRE->Cells[SGr_vRIRE_SYUKA->Col][0];
        	iCol = SGr_vRIRE_SYUKA->Col;
            pRIRE_KSD01_DATA[iCol].UPD_FLG = true;
            pRIRE_KSD01_DATA[iCol].SAVE_FLG = false;
			break;
		case 3:
        	//Form3->sNOW_LOTNO	= SGr_tSOKU->Cells[SGr_vSOKU_SOZAI->Col][0];
            iCol = SGr_vSOKU_SOZAI->Col;
            pSOKU_KSD01_DATA[iCol].UPD_FLG = true;
            pSOKU_KSD01_DATA[iCol].SAVE_FLG = false;
			break;
		case 4:
        	//Form3->sNOW_LOTNO	= SGr_tRIRE->Cells[SGr_vRIRE_SOZAI->Col][0];
        	iCol = SGr_vRIRE_SOZAI->Col;
            pRIRE_KSD01_DATA[iCol].UPD_FLG = true;
            pRIRE_KSD01_DATA[iCol].SAVE_FLG = false;
			break;
		}

        // 2003/10/30 A.Tamura 最後にフォーカスの有ったセルが編集モードの時、
        // 「値の保存」と「判定処理」を確実に行なうため、DrawCellを呼び出します。
		TGridDrawState DrawState;
    	AllGRID_DrawCell( SGr_vSOKU_SYUKA,
                             SGr_vSOKU_SYUKA->Col,
                             SGr_vSOKU_SYUKA->Row,
                             SGr_vSOKU_SYUKA->CellRect(SGr_vSOKU_SYUKA->Col, SGr_vSOKU_SYUKA->Row),
                             DrawState);
    	AllGRID_DrawCell( SGr_vRIRE_SYUKA,
                             SGr_vRIRE_SYUKA->Col,
                             SGr_vRIRE_SYUKA->Row,
                             SGr_vRIRE_SYUKA->CellRect(SGr_vRIRE_SYUKA->Col, SGr_vRIRE_SYUKA->Row),
                             DrawState);
    	AllGRID_DrawCell( SGr_vSOKU_SOZAI,
                             SGr_vSOKU_SOZAI->Col,
                             SGr_vSOKU_SOZAI->Row,
                             SGr_vSOKU_SOZAI->CellRect(SGr_vSOKU_SOZAI->Col, SGr_vSOKU_SOZAI->Row),
                             DrawState);
    	AllGRID_DrawCell( SGr_vRIRE_SOZAI,
                             SGr_vRIRE_SOZAI->Col,
                             SGr_vRIRE_SOZAI->Row,
                             SGr_vRIRE_SOZAI->CellRect(SGr_vRIRE_SOZAI->Col, SGr_vRIRE_SOZAI->Row),
                             DrawState);

        ALL_INSPECT();              //全ロットの判定を行います
        ADD_SPACE();                //KSD02にスペース行を保存します
        bHan = Set_DB_SOKU();       //出荷測定データを保存します
        bHan = Set_DB_RIRE();       //出荷履歴データを保存します
        bHan = Set_DB_SOKU_SOZAI(); //素材測定データを保存します
        bHan = Set_DB_RIRE_SOZAI(); //素材履歴データを保存します

        //保存が終了したので「アップデートフラグと保存フラグを初期化します
		if( hSOKU_KSD01_DATA)
		{
			for(iCol = 0; iCol<SGr_tSOKU->ColCount;iCol++)
			{
				pSOKU_KSD01_DATA[iCol].UPD_FLG = false;
				pSOKU_KSD01_DATA[iCol].SAVE_FLG = true;
			}
    	}

		if( hRIRE_KSD01_DATA && Form1->iRIRE_CNT != 0)
		{
			for(iCol = 0; iCol<SGr_tRIRE->ColCount;iCol++)
			{
				pRIRE_KSD01_DATA[iCol].UPD_FLG = false;
				pRIRE_KSD01_DATA[iCol].SAVE_FLG = true;
			}
		}

    	// 項目編集画面を表示する前の確認画面を表示します
        // 項目編集画面を初期表示する項目データの表示元を決定します
        Form10->ShowModal();

        if( Form3->iFROM_DATA > 0 ){

        	// 項目編集画面の表示
        	Form3->ShowModal();

//        	AllKeyUp(Sender,17,State);					// ファンクションキーの状態を元に戻します。

        	// 項目編集されている場合、再表示処理を行ないます
        	if( Form3->bDispRefresh ){

                // 2004/08/27 A.Tamura 項目編集後の検索処理時に「保存しますか？」と聞いてくるので
                //                     保存対象のロット情報をバッファに取り込んでから、保存フラグ
                //                     を初期化します。
                //                     その後、「検索」→「バッファを戻す」→「保存処理」を行なう。
				TStrings *sUPD_FLG_SOKU;
				TStrings *sUPD_FLG_RIRE;

                sUPD_FLG_SOKU = new TStringList;
                sUPD_FLG_RIRE = new TStringList;

        		// アップデートフラグと保存フラグをバッファへ格納と初期化します
				if( hSOKU_KSD01_DATA)
				{
					for(iCol = 0; iCol<SGr_tSOKU->ColCount;iCol++)
					{
                        // バッファへ格納
                        if( pSOKU_KSD01_DATA[iCol].UPD_FLG ){
                        	sUPD_FLG_SOKU->Add("1");
                        } else {
                        	sUPD_FLG_SOKU->Add("0");
                        }
						pSOKU_KSD01_DATA[iCol].UPD_FLG = false;
						pSOKU_KSD01_DATA[iCol].SAVE_FLG = true;
					}
    			}

				if( hRIRE_KSD01_DATA && Form1->iRIRE_CNT != 0)
				{
					for(iCol = 0; iCol<SGr_tRIRE->ColCount;iCol++)
					{
                        // バッファへ格納
                        if( pRIRE_KSD01_DATA[iCol].UPD_FLG ){
                        	sUPD_FLG_RIRE->Add("1");
                        } else {
                        	sUPD_FLG_RIRE->Add("0");
                        }
						pRIRE_KSD01_DATA[iCol].UPD_FLG = false;
						pRIRE_KSD01_DATA[iCol].SAVE_FLG = true;
					}
				}

				// その他初期値を設定
			    bCursolMove = false;
                PnlArrow->Caption ="→";
			    bEnterMove = false;
				bKASOU_MOVE = false;
				bHANTEI_DISP = false;

                // 検索処理
     			// AllKeyUp(Sender,17,State);		// ファンクションキーの状態を元に戻します。
     			AllKeyUp(Sender ,shtHoge,State);	// ファンクションキーの状態を元に戻します。
				BtnF07Click(BtnF07);

        		// バッファへ格納したアップデートフラグを元に戻します。
				if( hSOKU_KSD01_DATA)
				{
					for(iCol = 0; iCol<SGr_tSOKU->ColCount;iCol++)
					{
                        if( sUPD_FLG_SOKU->Strings[iCol] == "1" ){
							pSOKU_KSD01_DATA[iCol].UPD_FLG = true;
							pSOKU_KSD01_DATA[iCol].SAVE_FLG = false;
                        } else {
							pSOKU_KSD01_DATA[iCol].UPD_FLG = false;
							pSOKU_KSD01_DATA[iCol].SAVE_FLG = true;
                        }
					}
    			}

				if( hRIRE_KSD01_DATA && Form1->iRIRE_CNT != 0)
				{
					for(iCol = 0; iCol<SGr_tRIRE->ColCount;iCol++)
					{
                        if( sUPD_FLG_RIRE->Strings[iCol] == "1" ){
							pRIRE_KSD01_DATA[iCol].UPD_FLG = true;
							pRIRE_KSD01_DATA[iCol].SAVE_FLG = false;
                        } else {
							pRIRE_KSD01_DATA[iCol].UPD_FLG = false;
							pRIRE_KSD01_DATA[iCol].SAVE_FLG = true;
                        }
					}
				}

				delete sUPD_FLG_SOKU;
				delete sUPD_FLG_RIRE;

                // 2004/08/27 A.Tamura 不具合No12,42に対応するため「項目編集」画面終了後に
                //                     「判定」が異なる場合が発生するので対象のロットを保存します。
                //                     保存対象のロット設定は、Form3で行なっています。

        		// 2003/10/30 A.Tamura 最後にフォーカスの有ったセルが編集モードの時、
        		// 「値の保存」と「判定処理」を確実に行なうため、DrawCellを呼び出します。
    			AllGRID_DrawCell( SGr_vSOKU_SYUKA,
		                             SGr_vSOKU_SYUKA->Col,
		                             SGr_vSOKU_SYUKA->Row,
		                             SGr_vSOKU_SYUKA->CellRect(SGr_vSOKU_SYUKA->Col, SGr_vSOKU_SYUKA->Row),
		                             DrawState);
		    	AllGRID_DrawCell( SGr_vRIRE_SYUKA,
		                             SGr_vRIRE_SYUKA->Col,
		                             SGr_vRIRE_SYUKA->Row,
		                             SGr_vRIRE_SYUKA->CellRect(SGr_vRIRE_SYUKA->Col, SGr_vRIRE_SYUKA->Row),
		                             DrawState);
		    	AllGRID_DrawCell( SGr_vSOKU_SOZAI,
		                             SGr_vSOKU_SOZAI->Col,
		                             SGr_vSOKU_SOZAI->Row,
		                             SGr_vSOKU_SOZAI->CellRect(SGr_vSOKU_SOZAI->Col, SGr_vSOKU_SOZAI->Row),
		                             DrawState);
		    	AllGRID_DrawCell( SGr_vRIRE_SOZAI,
		                             SGr_vRIRE_SOZAI->Col,
		                             SGr_vRIRE_SOZAI->Row,
		                             SGr_vRIRE_SOZAI->CellRect(SGr_vRIRE_SOZAI->Col, SGr_vRIRE_SOZAI->Row),
		                             DrawState);

		        ALL_INSPECT();              //全ロットの判定を行います
		        ADD_SPACE();                //KSD02にスペース行を保存します
		        bHan = Set_DB_SOKU();       //出荷測定データを保存します
		        bHan = Set_DB_RIRE();       //出荷履歴データを保存します
		        bHan = Set_DB_SOKU_SOZAI(); //素材測定データを保存します
		        bHan = Set_DB_RIRE_SOZAI(); //素材履歴データを保存します

        		// 保存が終了したのでアップデートフラグと保存フラグを初期化します
				if( hSOKU_KSD01_DATA)
				{
					for(iCol = 0; iCol<SGr_tSOKU->ColCount;iCol++)
					{
						pSOKU_KSD01_DATA[iCol].UPD_FLG = false;
						pSOKU_KSD01_DATA[iCol].SAVE_FLG = true;
					}
    			}

				if( hRIRE_KSD01_DATA && Form1->iRIRE_CNT != 0)
				{
					for(iCol = 0; iCol<SGr_tRIRE->ColCount;iCol++)
					{
						pRIRE_KSD01_DATA[iCol].UPD_FLG = false;
						pRIRE_KSD01_DATA[iCol].SAVE_FLG = true;
					}
				}
        	}
        }

    }
    TShiftState State;
    AllKeyUp(Sender,shtHoge,State);	// ファンクションキーの状態を元に戻します。
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ７：検索」ボタンを押した時の処理
//
//  機能説明
//    CtrlOFF：検索を実行します
//    CtrlON ：ロット割り当て画面（Form8）を表示します
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

    TRect r;
    AnsiString sBuf;
    MSG msg;
    TMsgDlgButtons MsgButton;
    int i1,iCol,iRow;
    TShiftState State;
    unsigned short shtHoge=17;

    if( !BtnF07->Enabled ) return;
    if( !BtnF07->Tag ){
        ////////////////////
        // 検索
        //検索前処理
        //データの更新があったかを確認します
        if( UPDATE_CHECK())
        {
            //データの更新があったので更新ロットが全データを測定したかを確認します
            if( !ALL_INSPECT())
            {
                sBuf  = "未測定の項目があります。保存して検索しますか？";
                sBuf += "\n[は　い] 未測定項目ありのまま、保存して検索します。";
                sBuf += "\n[いいえ] 内容を破棄して検索します。";
                sBuf += "\n[キャンセル] 検索処理の取り消し。";
                switch( MessageDlg( sBuf, mtWarning, mbYesNoCancel, 0) )
                {
                    // 「Yes」      保存
                    case mrYes:
                        bQUIT_FLG = true;
	                BtnF11Click(Sender);
                        break;
                    // 「No」       変更を破棄
                    case mrNo:
                        break;
                    // 「Cancel」   キャンセル
                    case mrCancel:
                        return;
                }
            }
            else
	    {
    	        sBuf  = "データが変更されています。変更内容を保存しますか？";
        	sBuf += "\n[は　い] 変更内容を保存して続行します。";
            	sBuf += "\n[いいえ] 変更内容を破棄して続行します。";
		sBuf += "\n[キャンセル] 検索処理の取り消し。";
                switch( MessageDlg( sBuf, mtConfirmation, mbYesNoCancel, 0) )
                {
                // 「Yes」      保存
                case mrYes:
                    bQUIT_FLG = true;
    	             BtnF11Click(Sender);
                     break;
                 // 「No」       変更を破棄
                case mrNo:
                     break;
                 // 「Cancel」   キャンセル
                case mrCancel:
                     return;
                }
            }
        }

        // 2003/06/02 A.Tamura
	PnlArrow->Caption ="→";

        bQUIT_FLG = false;;
        Graph_Format();
        bSOZAI_NASI = true;

	// 2003/06/02 A.Tamura
        Glaph_Init();

	//2003.05.14 A.Tamura Add↓
	if( Trim(Cmb_DTKSHIN->Text).Length() == 0 ){
	    MessageDlg("代表得意先品番が指定されていません。", mtWarning,
	    TMsgDlgButtons() << mbOK , 0);
            return;
        }

	if( Trim(Edt_LOTNO->Text).Length()   == 0 ){
	    MessageDlg("ロットNOが指定されていません。", mtWarning,
	    TMsgDlgButtons() << mbOK , 0);
            return;
        }
	//2003.05.14 A.Tamura Add↑

	//2003.05.09 E.Takase Add↓
        //グローバル変数に検索条件をセット
	sNowDTKSHIN	 = Cmb_DTKSHIN->Text;
	sNowLOTNO	 = Edt_LOTNO->Text;
	bNowSEIKANDATA	 = CHkSEIKANDATA->Checked;
	bNowRIRE	 = Chk_RIRE->Checked;
	iNowRIRE_NUM	 = Edt_RIRE_NUM->Text.ToIntDef(10);
	//2003.05.09 E.Takase Add↑

        // 検索中フラグON
        bNowF7 = true;

        for(i1 = 0;i1<1000;i1++)
        {
            bBUNKATU_RIRE[i1] = false;
            bBUNKATU_SOKU[i1] = false;
        }

	// 2003/06/02 A.Tamura
        Glaph_Init();
        Graph_Format();

        //製品規格マスターが存在するか？
	bINPUTLOT_OK = Get_KSM01();
	if(!bINPUTLOT_OK){
	    // 検索中フラグOFF
	    bNowF7 = false;
	    MessageDlg("指定した品番は製品規格マスターに登録されていません。", mtWarning,
	    TMsgDlgButtons() << mbOK , 0);
	    return;
	}
	else
	{
            //グリッドの位置デフォルト値セット（この処理を怠るとグリッドインデックスエラーに見舞われる）
            SGr_vSOKU_SYUKA->Row = 0;
            SGr_vSOKU_SYUKA->Col = 0;
            SGr_vRIRE_SYUKA->Row = 0;
            SGr_vRIRE_SYUKA->Col = 0;
            SGr_vSOKU_SOZAI->Row = 0;
            SGr_vSOKU_SOZAI->Col = 0;
            SGr_vRIRE_SOZAI->Row = 0;
            SGr_vRIRE_SOZAI->Col = 0;

            // 右パネルへ詳細情報の表示
            Pnl_skInfo_vDTKS  ->Caption = " " + AnsiString(pKSM01_DATA.DTKSNAM);
	    Pnl_skInfo_vHINBAN->Caption = " " + AnsiString(pKSM01_DATA.HINBAN);
	    Pnl_skInfo_vHINSYU->Caption = " " + AnsiString(pKSM01_DATA.ZISNAM);
	    Pnl_skInfo_vHINMEI->Caption = " " + AnsiString(pKSM01_DATA.HINMEI);
	}
	OldMIDASI->Visible = false;
	NewMIDASI->Visible = false;
        OldMIDASI->Parent = SBx_Left_SYUKA;
        NewMIDASI->Parent = SBx_Left_SYUKA;


        //セルインフォメーション解放
	// メモリの開放
	if( hCELLINFO_SOKU_SYUKA ){
    	    GlobalUnlock( hCELLINFO_SOKU_SYUKA );
            GlobalFree( hCELLINFO_SOKU_SYUKA );
	}
        hCELLINFO_SOKU_SYUKA = NULL;
	// メモリの開放
	if( hCELLINFO_RIRE_SYUKA ){
            GlobalUnlock( hCELLINFO_RIRE_SYUKA );
	    GlobalFree( hCELLINFO_RIRE_SYUKA );
    	}
        hCELLINFO_RIRE_SYUKA = NULL;
	// メモリの開放
	if( hCELLINFO_SOKU_SOZAI ){
            GlobalUnlock( hCELLINFO_SOKU_SOZAI );
	    GlobalFree( hCELLINFO_SOKU_SOZAI );
    	}
        hCELLINFO_SOKU_SOZAI = NULL;
	// メモリの開放
	if( hCELLINFO_RIRE_SOZAI ){
            GlobalUnlock( hCELLINFO_RIRE_SOZAI );
	    GlobalFree( hCELLINFO_RIRE_SOZAI );
    	}
        hCELLINFO_RIRE_SOZAI = NULL;
	// メモリの開放
    	if( hSOKU_KSD01_DATA ){
    	    GlobalUnlock( hSOKU_KSD01_DATA );
	    GlobalFree( hSOKU_KSD01_DATA );
    	}
	hSOKU_KSD01_DATA = NULL;
        bNowLotF7 == false;


        //その他初期値
        bCursolMove = false;
        bEnterMove = false;
	bKASOU_MOVE = false;
	bHANTEI_DISP = false;
        bCellWrite = false;


        memset(&pOldInfoGlaph,(int)NULL,sizeof(pOldInfoGlaph));
	//グリッドクリア
	for(iCol = 0; iCol<SGr_vSOKU_SYUKA->ColCount ; iCol++)
	{
	    for(iRow = 0; iRow<SGr_vSOKU_SYUKA->RowCount;iRow++)
	    {
	    	SGr_vSOKU_SYUKA->Cells[iCol][iRow] = "";
	    }
	}
	for(iCol = 0; iCol<SGr_vRIRE_SYUKA->ColCount ; iCol++)
	{
	    for(iRow = 0; iRow<SGr_vRIRE_SYUKA->RowCount;iRow++)
	    {
	    	SGr_vRIRE_SYUKA->Cells[iCol][iRow] = "";
	    }
	}
	for(iCol = 0; iCol<SGr_vSOKU_SOZAI->ColCount ; iCol++)
	{
	    for(iRow = 0; iRow<SGr_vSOKU_SOZAI->RowCount;iRow++)
	    {
	    	SGr_vSOKU_SOZAI->Cells[iCol][iRow] = "";
	    }
	}
	for(iCol = 0; iCol<SGr_vRIRE_SOZAI->ColCount ; iCol++)
	{
	    for(iRow = 0; iRow<SGr_vRIRE_SOZAI->RowCount;iRow++)
	    {
	    	SGr_vRIRE_SOZAI->Cells[iCol][iRow] = "";
	    }
	}
	for(iCol = 0;iCol < SGr_tSOKU->ColCount;iCol++)
	{
	    SGr_tSOKU->Cells[iCol][0] = "";
	    SGr_tSOKU_SOZAI->Cells[iCol][0] = "";
	    SGr_tSOKU_SYUKA->Cells[iCol][0] = "";
	}
	for(iCol = 0;iCol < SGr_tRIRE->ColCount;iCol++)
	{
	    SGr_tRIRE->Cells[iCol][0] = "";
	    SGr_tRIRE_SOZAI->Cells[iCol][0] = "";
	    SGr_tRIRE_SYUKA->Cells[iCol][0] = "";
	}

	// 2003/06/02 A.Tamura
        Glaph_Init();

        //キーイベントクリア
	while(PeekMessage(&msg,Form1->Handle,WM_KEYFIRST,WM_KEYLAST,PM_REMOVE));

        //ロットの取得
        if( Set_Lot() )                                                 // onishi
        {
	    bINPUTLOT_OK = true;					//入力ロットOKフラグ_

    	    SGr_tRIRE->Refresh();
	    SGr_tSOKU->Refresh();

	    Get_KSM02();
            //履歴ロットの取得
	    if(bNowRIRE == true)
            {
                Get_RIRELOT();
            }
            else
            {
                iRIRE_CNT = 0;                  //履歴数は0です
            }

            //グリッドの初期化
	    SGr_vSOKU_SYUKA->RowCount = 1;
	    SGr_tSOKU_SYUKA->RowCount = 1;      //日付表示グリッド
	    SGr_vSOKU_SOZAI->RowCount = 1;
	    SGr_tSOKU_SOZAI->RowCount = 1;      //日付表示グリッド

            // 通常の測定画面に変更
            SGr_vRIRE_SOZAI->Color = (TColor)0x00D2FFFF;
            SGr_vSOKU_SOZAI->Color = (TColor)0x00D2FFFF;
            SGr_vRIRE_SYUKA->Color = (TColor)0x00FFEEDD;
            SGr_vSOKU_SYUKA->Color = clWindow;
            SCREEN_SET();

            // コントロール数が動的に変化する為、コード修正が必要
            Mem_vRIRE_MEMOORG->Color = (TColor)0x00FFEEDD;
	    SBr1->Panels->Items[0]->Text = "通常の測定画面です。";
	    SBr1->Update();

            //履歴表示準備---------------------------------------------------------------------
            //履歴メモコントロールのメモリ開放
            for(i1 = 0 ; i1 < iRIRE_MEMO_CNT ;i1++)
            {
            	delete Mem_vRIRE_MEMO[i1];
            }
            iRIRE_MEMO_CNT = 0;
	    SGr_vRIRE_SYUKA->ColCount = 1;
	    SGr_tRIRE_SYUKA->ColCount = 1;      //日付表示グリッド
	    SGr_vRIRE_SOZAI->ColCount = 1;
	    SGr_tRIRE_SOZAI->ColCount = 1;      //日付表示グリッド

            //履歴グリッド幅の調整
	    if(bNowRIRE == true)
	    {
		SGr_tRIRE	->Visible   = true;
		SGr_vRIRE_SYUKA	->Visible   = true;
		SGr_tRIRE_SYUKA ->Visible   = true;     			//日付表示グリッド
		SGr_vRIRE_SOZAI	->Visible   = true;
		SGr_tRIRE_SOZAI ->Visible   = true;      			//日付表示グリッド
		SGr_vRIRE_SYUKA	->ColCount  = iRIRE_CNT;
		SGr_tRIRE_SYUKA ->ColCount  = iRIRE_CNT;			//日付表示グリッド
		SGr_vRIRE_SOZAI	->ColCount  = iRIRE_CNT;
		SGr_tRIRE_SOZAI ->ColCount  = iRIRE_CNT;			//日付表示グリッド
	    }
	    else
	    {
		SGr_tRIRE	->Visible   = False;
		SGr_vRIRE_SYUKA	->Visible   = False;
		SGr_tRIRE_SYUKA ->Visible   = False;				//日付表示グリッド
		SGr_vRIRE_SOZAI	->Visible   = False;
		SGr_tRIRE_SOZAI ->Visible   = False;				//日付表示グリッド
	    }
            //グラフイニシャライズ
	    //グラフインフォメーションの初期化
	    // メモリの開放
            memset(&pInfoGlaph,(int)NULL,sizeof(pInfoGlaph));
            memset(&pOldInfoGlaph,(int)NULL,sizeof(pOldInfoGlaph));

            //検索ルーチンメイン処理
	    Set_Ins_Disp();

            //分割表チェック
            BUNKATU_CHECK();
        }
        else
        {
            //動的コントロールの開放
            DynamicCtrl_Free();
	    //グラフインフォメーションの初期化
            //グラフの初期化
            Graph_Format();
            bINPUTLOT_OK = false;
            memset(&pInfoGlaph,(int)NULL,sizeof(pInfoGlaph));
	    bINPUTLOT_OK = false;					//入力ロットOKフラグ_
        }
    }
    else
    {
        //ロット割り当て画面
        bool bTempLot;
        bTempLot = bLOT_LINK;
        Glaph_Init();

	if( !bINPUTLOT_OK )
	{
	    MsgButton << mbOK;
       	    sBuf  = "有効なロットが入力されていない為、ロット割り当ては出来ません。";
            MessageDlg( sBuf, mtWarning	, MsgButton, 0);
            //AllKeyUp(Sender,17,State);	// ファンクションキーの状態を元に戻します。
            AllKeyUp(Sender ,shtHoge,State);	// ファンクションキーの状態を元に戻します。
            return;
    	}
        if( bSOZAI_NASI )
        {
	    MsgButton << mbOK;
       	    sBuf  = "素材の指示があるデータがない為、ロット割り当ては出来ません。";
            MessageDlg( sBuf, mtWarning	, MsgButton, 0);
            //AllKeyUp(Sender,17,State);	// ファンクションキーの状態を元に戻します。
            AllKeyUp(Sender ,shtHoge,State);	// ファンクションキーの状態を元に戻します。
            return;
        }
        if(bLOT_LINK == true)
        {
	    MsgButton << mbOK;
       	    sBuf  = "素材データが全てロットリンクを行っているので、ロット割り当ては出来ません。";
            MessageDlg( sBuf, mtWarning	, MsgButton, 0);
            //AllKeyUp(Sender,17,State);	// ファンクションキーの状態を元に戻します。
            AllKeyUp(Sender ,shtHoge,State);	// ファンクションキーの状態を元に戻します。
            bLOT_LINK = bTempLot;
            return;
        }
        ////////////////////
        // ロット割り当て画面　呼び出し
	TShiftState State;
	OldMIDASI->Visible = false;
	NewMIDASI->Visible = false;
        OldMIDASI->Parent = SBx_Left_SYUKA;
        NewMIDASI->Parent = SBx_Left_SYUKA;
        memset(&pInfoGlaph,(int)NULL,sizeof(pInfoGlaph));
        memset(&pOldInfoGlaph,(int)NULL,sizeof(pOldInfoGlaph));

        // ロット割り当て
        if(hCELLINFO_SOKU_SYUKA)
        {
            SGr_vSOKU_SYUKA->SetFocus();
            SGr_vSOKU_SYUKA->Col = 0;
            SGr_vSOKU_SYUKA->Row = 0;
        }
        Form8->ShowModal();

        // k.k 2003.05.17 ADD ----
	OldMIDASI->Visible = false;
	NewMIDASI->Visible = false;
        OldMIDASI->Parent = SBx_Left_SYUKA;
        NewMIDASI->Parent = SBx_Left_SYUKA;
        memset(&pInfoGlaph,(int)NULL,sizeof(pInfoGlaph));
        memset(&pOldInfoGlaph,(int)NULL,sizeof(pInfoGlaph));

        SOZAI_PROCESS();
        bLOTCHANGE = false;
        bNowLotF7 = false;
        // 検索終了フラグ
        Form1->bNowF7 = false;
        bLOT_LINK = bTempLot;
        //------------------------

        AllKeyUp(Sender ,shtHoge,State);	// ファンクションキーの状態を元に戻します。

	//グラフイニシャライズ
        Glaph_Init();
        Graph_Format();
    }
}
//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ８：担当者切替」ボタンを押した時の処理
//
//  機能説明
//    CtrlOFF:担当者切替画面（Form9）を表示します
//    CtrlON :分割表画面（Form7）を表示します
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
	TShiftState State;
	TMsgDlgButtons MsgButton;
    AnsiString sBuf;
    unsigned short shtHoge=17;

	if( !BtnF08->Enabled ) return;
    if( !BtnF08->Tag ){
        ////////////////////
        // 担当者切替
        Form9->ShowModal();
        AllKeyUp(Sender,shtHoge,State);	// ファンクションキーの状態を元に戻します。
    }
    else{
	    if( !bINPUTLOT_OK )
		{
        	MsgButton << mbOK;
       		sBuf  = "有効なロットが入力されていない為、分割表は動作しません。";
        	MessageDlg( sBuf, mtWarning	, MsgButton , 0);
        	AllKeyUp(Sender,shtHoge,State);	// ファンクションキーの状態を元に戻します。
            return;
    	}
        if( iContCnt == 0)
		{
        	MsgButton << mbOK;
       		sBuf  = "出荷項目がない為、分割表は動作しません。";
        	MessageDlg( sBuf, mtWarning	, MsgButton , 0);
        	AllKeyUp(Sender,shtHoge,State);	// ファンクションキーの状態を元に戻します。
            return;
    	}
        ////////////////////
        // 分割票入力
        Form7->ShowModal();
        AllKeyUp(Sender,shtHoge,State);	// ファンクションキーの状態を元に戻します。
        BUNKATU_CHECK();
    }

}
//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ９：画面印刷」ボタンを押した時の処理
//
//  機能説明
//    CtrlOFF:表示画面を印刷します
//    CtrlON :測定画面／印刷値編集画面を切り替えます
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
	TMsgDlgButtons MsgButton;
    AnsiString sBuf;

	if( !BtnF09->Enabled ) return;
    if( !BtnF09->Tag ){
        ////////////////////
        // 画面印刷 （あまりに誤入力が多かったため確認メッセージを追加しました）
        sBuf  = "画面を印刷しますがよろしいですか？";
        sBuf += "\n[は　い] 表示されている画面を印刷します。";
        sBuf += "\n[キャンセル] 画面印刷の取り消し。";
        MsgButton << mbYes << mbCancel;
        switch( MessageDlg( sBuf, mtConfirmation , MsgButton, 0) ){
        // 「Yes」      保存
        case mrYes:
            break;
        // 「Cancel」   キャンセル
        case mrCancel:
        return;
        }
	    Form1->Print();
    }
    else {
		////////////////////
        // 印刷用値編集
        if( SGr_vRIRE_SOZAI->Color == 0x00DDDDDD ){
            // 通常の測定画面に変更
        	SGr_vRIRE_SOZAI->Color = (TColor)0x00D2FFFF;
        	SGr_vSOKU_SOZAI->Color = (TColor)0x00D2FFFF;
        	SGr_vRIRE_SYUKA->Color = (TColor)0x00FFEEDD;
        	SGr_vSOKU_SYUKA->Color = clWindow;
            SCREEN_SET();
			Mem_vRIRE_MEMOORG->Color = (TColor)0x00FFEEDD;

			SBr1->Panels->Items[0]->Text = "通常の測定画面です。";
        }
        else {
            // 印刷編集画面に変更
        	SGr_vRIRE_SOZAI->Color = (TColor)0x00DDDDDD;
        	SGr_vSOKU_SOZAI->Color = (TColor)0x00DDDDDD;
        	SGr_vRIRE_SYUKA->Color = (TColor)0x00DDDDDD;
        	SGr_vSOKU_SYUKA->Color = (TColor)0x00DDDDDD;
			DISP_SCREEN_SET();
			Mem_vRIRE_MEMOORG->Color = (TColor)0x00DDDDDD;
			SBr1->Panels->Items[0]->Text = "印刷用の編集画面です。";
		}
		SBr1->Update();
    }

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ１０：Excel出力」ボタンを押した時の処理
//
//  機能説明
//    CtrlOFF:表示画面を印刷します
//    CtrlON :無し
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
	bool bHan;
    int iCol;
    AnsiString sBuf;
	TMsgDlgButtons MsgButton;
	TShiftState State;
    unsigned short shtHoge=17;
    bool        retDLL;

    if( BtnF10->Tag ){
        if( !bINPUTLOT_OK )
        {
    	    sBuf  = "有効なロットが入力されていない為出来ません。";
            MsgButton << mbOK;
            MessageDlg( sBuf, mtWarning	, MsgButton, 0);
            AllKeyUp(Sender,shtHoge,State);	// ファンクションキーの状態を元に戻します。
            return;
        }
        else
        {
            Form12->ShowModal();
            AllKeyUp(Sender,shtHoge,State);	// ファンクションキーの状態を元に戻します。
            return;
        }
    }

    if( !bINPUTLOT_OK )
    {
    	sBuf  = "有効なロットが入力されていない為項目Ｅｘｃｅｌ出力は出来ません。";
        MsgButton << mbOK;
        MessageDlg( sBuf, mtWarning	, MsgButton, 0);
        AllKeyUp(Sender,shtHoge,State);	// ファンクションキーの状態を元に戻します。
        return;
    }
    if( !BtnF10->Enabled )    return;

    else
    {
        ////////////////////
        // Ｅｘｃｅｌ出力


        if( UPDATE_CHECK())
        {
    	// 確認メッセージ
// 【※】データが編集されている場合だけ、確認メッセージの表示を行なう
            if( MessageDlg( "Ｅｘｃｅｌ出力を行なうには、現在の測定データを保存する必要があります。\n保存を行い処理を続行します。よろしいですか？",
                mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo ){
                AllKeyUp(Sender,shtHoge,State);	// ファンクションキーの状態を元に戻します。
                return;
            }

			// 2003/10/30 A.Tamura 最後にフォーカスの有ったセルが編集モードの時、
			// 「値の保存」と「判定処理」を確実に行なうため、DrawCellを呼び出します。
			TGridDrawState DrawState;
			AllGRID_DrawCell( SGr_vSOKU_SYUKA,
								 SGr_vSOKU_SYUKA->Col,
								 SGr_vSOKU_SYUKA->Row,
								 SGr_vSOKU_SYUKA->CellRect(SGr_vSOKU_SYUKA->Col, SGr_vSOKU_SYUKA->Row),
								 DrawState);
			AllGRID_DrawCell( SGr_vRIRE_SYUKA,
								 SGr_vRIRE_SYUKA->Col,
								 SGr_vRIRE_SYUKA->Row,
								 SGr_vRIRE_SYUKA->CellRect(SGr_vRIRE_SYUKA->Col, SGr_vRIRE_SYUKA->Row),
								 DrawState);
			AllGRID_DrawCell( SGr_vSOKU_SOZAI,
								 SGr_vSOKU_SOZAI->Col,
								 SGr_vSOKU_SOZAI->Row,
								 SGr_vSOKU_SOZAI->CellRect(SGr_vSOKU_SOZAI->Col, SGr_vSOKU_SOZAI->Row),
								 DrawState);
			AllGRID_DrawCell( SGr_vRIRE_SOZAI,
								 SGr_vRIRE_SOZAI->Col,
								 SGr_vRIRE_SOZAI->Row,
								 SGr_vRIRE_SOZAI->CellRect(SGr_vRIRE_SOZAI->Col, SGr_vRIRE_SOZAI->Row),
								 DrawState);

            ALL_INSPECT();              //全ロットの判定を行います
            ADD_SPACE();                //KSD02にスペース行を保存します
            bHan = Set_DB_SOKU();
            bHan = Set_DB_RIRE();
            bHan = Set_DB_SOKU_SOZAI();
            bHan = Set_DB_RIRE_SOZAI();

//保存が終了したので「アップデートフラグと保存フラグを初期化します
		    if( hSOKU_KSD01_DATA)
		    {
			    for(iCol = 0; iCol<SGr_tSOKU->ColCount;iCol++)
			    {
				    pSOKU_KSD01_DATA[iCol].UPD_FLG = false;
				    pSOKU_KSD01_DATA[iCol].SAVE_FLG = true;
    			}
        	}

		    if( hRIRE_KSD01_DATA)
		    {
			    for(iCol = 0; iCol<SGr_tRIRE->ColCount;iCol++)
    			{
	    			pRIRE_KSD01_DATA[iCol].UPD_FLG = false;
		    		pRIRE_KSD01_DATA[iCol].SAVE_FLG = true;
			    }
    		}
        }
    }
    // 2003/05/14 A.Tamura
    if( !BtnF10->Tag ){
		// TKSS02を起動します
    	AnsiString	sPath = Application->ExeName;
    	AnsiString  sTKSS02;
    	AnsiString	sParam;
    	HWND		Hndl = Application->Handle;
    	int			iPos;

    	iPos = sPath.LastDelimiter("\\");
    	sTKSS02 = sPath.SubString(1,iPos) + "TKSS02.EXE";
    	sParam  = IntToStr(USER_COD) + "," + USER_NAM + "," + BUMO_COD + "," + BUMO_NAM;
		//2003.05.09 E.Takase Add↓
    	sParam += "," + sNowDTKSHIN + "," + sNowLOTNO;
		//2003.05.09 E.Takase Add↑
		//2003.05.09 E.Takase Add コメント↓
    	//sParam += "," + Cmb_DTKSHIN->Text + "," + Edt_LOTNO->Text;
		//2003.05.09 E.Takase Add コメント↑

    	retDLL = ShellExecute( Hndl, NULL, sTKSS02.c_str(), sParam.c_str(), NULL, SW_SHOWNORMAL );
    }
}
//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ１２：戻る」ボタンを押した時の処理
//
//  機能説明
//    CtrlOFF:メインメニューに戻ります
//    CtrlON :無し
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
	TMsgDlgButtons mRet;
	AnsiString sBuf;
	TShiftState State;
    unsigned short shtHoge=17;
    if( !BtnF12->Enabled )
	{
        AllKeyUp(Sender,shtHoge,State);	// ファンクションキーの状態を元に戻します。
    	return;
    }
    Close();

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：測定データに更新があったかを判断します。
//
//  機能説明
//    データをセーブする前に本関数を呼び出し、メッセージのフラグに適用します。
//
//  パラメタ説明
//    なし。
//
//
//  戻り値
//    bool				：true = 更新あり、false = 更新なし
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::UPDATE_CHECK(void)
{
	int iCol;

	// 2004/09/13 A.Tamura アプリケーションエラーの為、try.. catch()を行なう。
	try
	{
	    //KSD01のデータにUPD_FLGを追加し更新時True、未更新時Falseとしました。
		if( hSOKU_KSD01_DATA)
		{
			for(iCol = 0; iCol<SGr_tSOKU->ColCount;iCol++)
			{
				if(pSOKU_KSD01_DATA[iCol].UPD_FLG == true)
				{
					return(true);
				}
			}
	    }

		if( hRIRE_KSD01_DATA && Form1->iRIRE_CNT != 0)
		{
			for(iCol = 0; iCol<SGr_tRIRE->ColCount;iCol++)
			{
				if(pRIRE_KSD01_DATA[iCol].UPD_FLG == true)
				{
					return(true);
				}
			}
		}
	}
	catch ( ... )
	{
		return( true );
	}

	return( false );
}

//---------------------------------------------------------------------------
// 	各コントロールのサイズを変更します
void __fastcall TForm1::Pnl_skInfoResize(TObject *Sender)
{
    int iRMarg;

    //
    // 現在もおかしい
    //
    // スプリッターの位置がずれる場合があるので、位置を設定しなおします
    if( Pnl_skInfo->Width <= Splitter1->MinSize )
    	Splitter1->Left  = Pnl_skInfo->Left + Pnl_skInfo->Width
                         - Splitter1->MinSize;
	else
    	Splitter1->Left  = Pnl_skInfo->Left - Splitter1->Width;

    // 親ラベルから見た各コントロールの右端余白
    iRMarg = 6;

    // タイトル
	if( Pnl_skInfo_Title->Left < Pnl_skInfo->Width &&
        Pnl_skInfo->Width - Pnl_skInfo_Title->Left - iRMarg > 0 ){
		Pnl_skInfo_Title->Width = Pnl_skInfo->Width - Pnl_skInfo_Title->Left - iRMarg;
	} else{
		Pnl_skInfo_Title->Width = 0;
	}

    // 得意先品番
    if( Pnl_skInfo_vDTKS->Left < Pnl_skInfo->Width &&
		Pnl_skInfo->Width - Pnl_skInfo_vDTKS->Left - iRMarg > 0 ){
		Pnl_skInfo_vDTKS->Width = Pnl_skInfo->Width - Pnl_skInfo_vDTKS->Left - iRMarg;
        Pnl_skInfo_tDTKS->Width = Pnl_skInfo_vDTKS->Left - Pnl_skInfo_tDTKS->Left;
	} else{
		Pnl_skInfo_vDTKS->Width = 0;
	    if( Pnl_skInfo_tDTKS->Left < Pnl_skInfo->Width &&
			Pnl_skInfo->Width - Pnl_skInfo_tDTKS->Left - iRMarg > 0 ){
			Pnl_skInfo_tDTKS->Width = Pnl_skInfo->Width - Pnl_skInfo_tDTKS->Left - iRMarg;
		} else{
			Pnl_skInfo_tDTKS->Width = 0;
		}
	}

    // 自社品番＆品種
    if( Pnl_skInfo_vHINSYU->Left < Pnl_skInfo->Width &&
		Pnl_skInfo->Width - Pnl_skInfo_vHINSYU->Left - iRMarg > 0 ){
		Pnl_skInfo_vHINSYU->Width = Pnl_skInfo->Width - Pnl_skInfo_vHINSYU->Left - iRMarg;
        Pnl_skInfo_tHINSYU->Width = Pnl_skInfo_vHINSYU->Left - Pnl_skInfo_tHINSYU->Left;
		Pnl_skInfo_vHINBAN->Width = Pnl_skInfo_tHINSYU->Left - Pnl_skInfo_vHINBAN->Left;
   		Pnl_skInfo_tHINBAN->Width = Pnl_skInfo_vHINBAN->Left - Pnl_skInfo_tHINBAN->Left;
	} else{
		Pnl_skInfo_vHINSYU->Width = 0;
	    if( Pnl_skInfo_tHINSYU->Left < Pnl_skInfo->Width &&
			Pnl_skInfo->Width - Pnl_skInfo_tHINSYU->Left - iRMarg > 0 ){
			Pnl_skInfo_tHINSYU->Width = Pnl_skInfo->Width - Pnl_skInfo_tHINSYU->Left - iRMarg;
			Pnl_skInfo_vHINBAN->Width = Pnl_skInfo_tHINSYU->Left - Pnl_skInfo_vHINBAN->Left;
       		Pnl_skInfo_tHINBAN->Width = Pnl_skInfo_vHINBAN->Left - Pnl_skInfo_tHINBAN->Left;
		} else{
			Pnl_skInfo_tHINSYU->Width = 0;
    		if( Pnl_skInfo_vHINBAN->Left < Pnl_skInfo->Width &&
				Pnl_skInfo->Width - Pnl_skInfo_vHINBAN->Left - iRMarg > 0 ){
				Pnl_skInfo_vHINBAN->Width = Pnl_skInfo->Width - Pnl_skInfo_vHINBAN->Left - iRMarg;
        		Pnl_skInfo_tHINBAN->Width = Pnl_skInfo_vHINBAN->Left - Pnl_skInfo_tHINBAN->Left;
			} else{
				Pnl_skInfo_vHINBAN->Width = 0;
	    		if( Pnl_skInfo_tHINBAN->Left < Pnl_skInfo->Width &&
					Pnl_skInfo->Width - Pnl_skInfo_tHINBAN->Left - iRMarg > 0 ){
					Pnl_skInfo_tHINBAN->Width = Pnl_skInfo->Width - Pnl_skInfo_tHINBAN->Left - iRMarg;
				} else{
					Pnl_skInfo_tHINBAN->Width = 0;
				}
			}
		}
	}

    // 品名
    if( Pnl_skInfo_vHINMEI->Left < Pnl_skInfo->Width &&
		Pnl_skInfo->Width - Pnl_skInfo_vHINMEI->Left - iRMarg > 0 ){
		Pnl_skInfo_vHINMEI->Width = Pnl_skInfo->Width - Pnl_skInfo_vHINMEI->Left - iRMarg;
        Pnl_skInfo_tHINMEI->Width = Pnl_skInfo_vHINMEI->Left - Pnl_skInfo_tHINMEI->Left;
	} else{
		Pnl_skInfo_vHINMEI->Width = 0;
	    if( Pnl_skInfo_tHINMEI->Left < Pnl_skInfo->Width &&
			Pnl_skInfo->Width - Pnl_skInfo_tHINMEI->Left - iRMarg > 0 ){
			Pnl_skInfo_tHINMEI->Width = Pnl_skInfo->Width - Pnl_skInfo_tHINMEI->Left - iRMarg;
		} else{
			Pnl_skInfo_tHINMEI->Width = 0;
		}
	}

    // ロットNO１＆測定者１
    if( Pnl_skInfo_vSOKUUSER1->Left < Pnl_skInfo->Width &&
		Pnl_skInfo->Width - Pnl_skInfo_vSOKUUSER1->Left - iRMarg > 0 ){
		Pnl_skInfo_vSOKUUSER1->Width = Pnl_skInfo->Width - Pnl_skInfo_vSOKUUSER1->Left - iRMarg;
        Pnl_skInfo_tSOKUUSER1->Width = Pnl_skInfo_vSOKUUSER1->Left - Pnl_skInfo_tSOKUUSER1->Left;
		Pnl_skInfo_vLOTBNG1->Width = Pnl_skInfo_tSOKUUSER1->Left - Pnl_skInfo_vLOTBNG1->Left;
   		Pnl_skInfo_tLOTBNG1->Width = Pnl_skInfo_vLOTBNG1->Left - Pnl_skInfo_tLOTBNG1->Left;
	} else{
		Pnl_skInfo_vSOKUUSER1->Width = 0;
	    if( Pnl_skInfo_tSOKUUSER1->Left < Pnl_skInfo->Width &&
			Pnl_skInfo->Width - Pnl_skInfo_tSOKUUSER1->Left - iRMarg > 0 ){
			Pnl_skInfo_tSOKUUSER1->Width = Pnl_skInfo->Width - Pnl_skInfo_tSOKUUSER1->Left - iRMarg;
			Pnl_skInfo_vLOTBNG1->Width = Pnl_skInfo_tSOKUUSER1->Left - Pnl_skInfo_vLOTBNG1->Left;
       		Pnl_skInfo_tLOTBNG1->Width = Pnl_skInfo_vLOTBNG1->Left - Pnl_skInfo_tLOTBNG1->Left;
		} else{
			Pnl_skInfo_tSOKUUSER1->Width = 0;
    		if( Pnl_skInfo_vLOTBNG1->Left < Pnl_skInfo->Width &&
				Pnl_skInfo->Width - Pnl_skInfo_vLOTBNG1->Left - iRMarg > 0 ){
				Pnl_skInfo_vLOTBNG1->Width = Pnl_skInfo->Width - Pnl_skInfo_vLOTBNG1->Left - iRMarg;
        		Pnl_skInfo_tLOTBNG1->Width = Pnl_skInfo_vLOTBNG1->Left - Pnl_skInfo_tLOTBNG1->Left;
			} else{
				Pnl_skInfo_vLOTBNG1->Width = 0;
	    		if( Pnl_skInfo_tLOTBNG1->Left < Pnl_skInfo->Width &&
					Pnl_skInfo->Width - Pnl_skInfo_tLOTBNG1->Left - iRMarg > 0 ){
					Pnl_skInfo_tLOTBNG1->Width = Pnl_skInfo->Width - Pnl_skInfo_tLOTBNG1->Left - iRMarg;
				} else{
					Pnl_skInfo_tLOTBNG1->Width = 0;
				}
			}
		}
	}

    // 検査項目１
    if( Pnl_skInfo_vKENSA1->Left < Pnl_skInfo->Width &&
		Pnl_skInfo->Width - Pnl_skInfo_vKENSA1->Left - iRMarg - 1 > 0 ){
		Pnl_skInfo_vKENSA1->Width = Pnl_skInfo->Width - Pnl_skInfo_vKENSA1->Left - iRMarg - 1;
        Pnl_skInfo_tKENSA1->Width = Pnl_skInfo_vKENSA1->Left - Pnl_skInfo_tKENSA1->Left;
	} else{
		Pnl_skInfo_vKENSA1->Width = 0;
	    if( Pnl_skInfo_tKENSA1->Left < Pnl_skInfo->Width &&
			Pnl_skInfo->Width - Pnl_skInfo_tKENSA1->Left - iRMarg - 1 > 0 ){
			Pnl_skInfo_tKENSA1->Width = Pnl_skInfo->Width - Pnl_skInfo_tKENSA1->Left - iRMarg - 1;
		} else{
			Pnl_skInfo_tKENSA1->Width = 0;
		}
	}

    // 測定機器１
    if( Pnl_skInfo_vKIKI1->Left < Pnl_skInfo->Width &&
		Pnl_skInfo->Width - Pnl_skInfo_vKIKI1->Left - iRMarg - 1 > 0 ){
		Pnl_skInfo_vKIKI1->Width = Pnl_skInfo->Width - Pnl_skInfo_vKIKI1->Left - iRMarg - 1;
        Pnl_skInfo_tKIKI1->Width = Pnl_skInfo_vKIKI1->Left - Pnl_skInfo_tKIKI1->Left;
	} else{
		Pnl_skInfo_vKIKI1->Width = 0;
	    if( Pnl_skInfo_tKIKI1->Left < Pnl_skInfo->Width &&
			Pnl_skInfo->Width - Pnl_skInfo_tKIKI1->Left - iRMarg > 0 ){
			Pnl_skInfo_tKIKI1->Width = Pnl_skInfo->Width - Pnl_skInfo_tKIKI1->Left - iRMarg - 1;
		} else{
			Pnl_skInfo_tKIKI1->Width = 0;
		}
	}

    // 規格１
    if( Pnl_skInfo_vKIKAKU1->Left < Pnl_skInfo->Width &&
		Pnl_skInfo->Width - Pnl_skInfo_vKIKAKU1->Left - iRMarg - 1 > 0 ){
		Pnl_skInfo_vKIKAKU1->Width = Pnl_skInfo->Width - Pnl_skInfo_vKIKAKU1->Left - iRMarg - 1;
        Pnl_skInfo_tKIKAKU1->Width = Pnl_skInfo_vKIKAKU1->Left - Pnl_skInfo_tKIKAKU1->Left;
	} else{
		Pnl_skInfo_vKIKAKU1->Width = 0;
	    if( Pnl_skInfo_tKIKAKU1->Left < Pnl_skInfo->Width &&
			Pnl_skInfo->Width - Pnl_skInfo_tKIKAKU1->Left - iRMarg - 1 > 0 ){
			Pnl_skInfo_tKIKAKU1->Width = Pnl_skInfo->Width - Pnl_skInfo_tKIKAKU1->Left - iRMarg - 1;
		} else{
			Pnl_skInfo_tKIKAKU1->Width = 0;
		}
	}

    // 測定履歴＆工程能力１
	if( Pcl_skInfo_page1->Left < Pnl_skInfo->Width &&
        Pnl_skInfo->Width - Pcl_skInfo_page1->Left - iRMarg > 0 ){
		Pcl_skInfo_page1->Width = Pnl_skInfo->Width - Pcl_skInfo_page1->Left - iRMarg;
	} else{
		Pcl_skInfo_page1->Width = 0;
	}

    // ロットNO２＆測定者２
    if( Pnl_skInfo_vSOKUUSER2->Left < Pnl_skInfo->Width &&
		Pnl_skInfo->Width - Pnl_skInfo_vSOKUUSER2->Left - iRMarg > 0 ){
		Pnl_skInfo_vSOKUUSER2->Width = Pnl_skInfo->Width - Pnl_skInfo_vSOKUUSER2->Left - iRMarg;
        Pnl_skInfo_tSOKUUSER2->Width = Pnl_skInfo_vSOKUUSER2->Left - Pnl_skInfo_tSOKUUSER2->Left;
		Pnl_skInfo_vLOTBNG2->Width = Pnl_skInfo_tSOKUUSER2->Left - Pnl_skInfo_vLOTBNG2->Left;
   		Pnl_skInfo_tLOTBNG2->Width = Pnl_skInfo_vLOTBNG2->Left - Pnl_skInfo_tLOTBNG2->Left;
	} else{
		Pnl_skInfo_vSOKUUSER2->Width = 0;
	    if( Pnl_skInfo_tSOKUUSER2->Left < Pnl_skInfo->Width &&
			Pnl_skInfo->Width - Pnl_skInfo_tSOKUUSER2->Left - iRMarg > 0 ){
			Pnl_skInfo_tSOKUUSER2->Width = Pnl_skInfo->Width - Pnl_skInfo_tSOKUUSER2->Left - iRMarg;
			Pnl_skInfo_vLOTBNG2->Width = Pnl_skInfo_tSOKUUSER2->Left - Pnl_skInfo_vLOTBNG2->Left;
       		Pnl_skInfo_tLOTBNG2->Width = Pnl_skInfo_vLOTBNG2->Left - Pnl_skInfo_tLOTBNG2->Left;
		} else{
			Pnl_skInfo_tSOKUUSER2->Width = 0;
    		if( Pnl_skInfo_vLOTBNG2->Left < Pnl_skInfo->Width &&
				Pnl_skInfo->Width - Pnl_skInfo_vLOTBNG2->Left - iRMarg > 0 ){
				Pnl_skInfo_vLOTBNG2->Width = Pnl_skInfo->Width - Pnl_skInfo_vLOTBNG2->Left - iRMarg;
        		Pnl_skInfo_tLOTBNG2->Width = Pnl_skInfo_vLOTBNG2->Left - Pnl_skInfo_tLOTBNG2->Left;
			} else{
				Pnl_skInfo_vLOTBNG2->Width = 0;
	    		if( Pnl_skInfo_tLOTBNG2->Left < Pnl_skInfo->Width &&
					Pnl_skInfo->Width - Pnl_skInfo_tLOTBNG2->Left - iRMarg > 0 ){
					Pnl_skInfo_tLOTBNG2->Width = Pnl_skInfo->Width - Pnl_skInfo_tLOTBNG2->Left - iRMarg;
				} else{
					Pnl_skInfo_tLOTBNG2->Width = 0;
				}
			}
		}
	}

    // 検査項目２
    if( Pnl_skInfo_vKENSA2->Left < Pnl_skInfo->Width &&
		Pnl_skInfo->Width - Pnl_skInfo_vKENSA2->Left - iRMarg - 1 > 0 ){
		Pnl_skInfo_vKENSA2->Width = Pnl_skInfo->Width - Pnl_skInfo_vKENSA2->Left - iRMarg - 1;
        Pnl_skInfo_tKENSA2->Width = Pnl_skInfo_vKENSA2->Left - Pnl_skInfo_tKENSA2->Left;
	} else{
		Pnl_skInfo_vKENSA2->Width = 0;
	    if( Pnl_skInfo_tKENSA2->Left < Pnl_skInfo->Width &&
			Pnl_skInfo->Width - Pnl_skInfo_tKENSA2->Left - iRMarg - 1 > 0 ){
			Pnl_skInfo_tKENSA2->Width = Pnl_skInfo->Width - Pnl_skInfo_tKENSA2->Left - iRMarg - 1;
		} else{
			Pnl_skInfo_tKENSA2->Width = 0;
		}
	}

    // 測定機器２
    if( Pnl_skInfo_vKIKI2->Left < Pnl_skInfo->Width &&
		Pnl_skInfo->Width - Pnl_skInfo_vKIKI2->Left - iRMarg - 1 > 0 ){
		Pnl_skInfo_vKIKI2->Width = Pnl_skInfo->Width - Pnl_skInfo_vKIKI2->Left - iRMarg - 1;
        Pnl_skInfo_tKIKI2->Width = Pnl_skInfo_vKIKI2->Left - Pnl_skInfo_tKIKI2->Left;
	} else{
		Pnl_skInfo_vKIKI2->Width = 0;
	    if( Pnl_skInfo_tKIKI2->Left < Pnl_skInfo->Width &&
			Pnl_skInfo->Width - Pnl_skInfo_tKIKI2->Left - iRMarg - 1 > 0 ){
			Pnl_skInfo_tKIKI2->Width = Pnl_skInfo->Width - Pnl_skInfo_tKIKI2->Left - iRMarg - 1;
		} else{
			Pnl_skInfo_tKIKI2->Width = 0;
		}
	}

    // 規格２
    if( Pnl_skInfo_vKIKAKU2->Left < Pnl_skInfo->Width &&
		Pnl_skInfo->Width - Pnl_skInfo_vKIKAKU2->Left - iRMarg - 1 > 0 ){
		Pnl_skInfo_vKIKAKU2->Width = Pnl_skInfo->Width - Pnl_skInfo_vKIKAKU2->Left - iRMarg - 1;
        Pnl_skInfo_tKIKAKU2->Width = Pnl_skInfo_vKIKAKU2->Left - Pnl_skInfo_tKIKAKU2->Left;
	} else{
		Pnl_skInfo_vKIKAKU2->Width = 0;
	    if( Pnl_skInfo_tKIKAKU2->Left < Pnl_skInfo->Width &&
			Pnl_skInfo->Width - Pnl_skInfo_tKIKAKU2->Left - iRMarg - 1 > 0 ){
			Pnl_skInfo_tKIKAKU2->Width = Pnl_skInfo->Width - Pnl_skInfo_tKIKAKU2->Left - iRMarg - 1;
		} else{
			Pnl_skInfo_tKIKAKU2->Width = 0;
		}
	}

    // 測定履歴＆工程能力２
	if( Pcl_skInfo_page2->Left < Pnl_skInfo->Width &&
        Pnl_skInfo->Width - Pcl_skInfo_page2->Left - iRMarg > 0 ){
		Pcl_skInfo_page2->Width = Pnl_skInfo->Width - Pcl_skInfo_page2->Left - iRMarg;
	} else{
		Pcl_skInfo_page2->Width = 0;
	}

    // カラーライン
	if( Shp_ColorLine1->Left < Pnl_skInfo->Width &&
        Pnl_skInfo->Width - Shp_ColorLine1->Left - 4 > 0 ){
		Shp_ColorLine1->Width = Pnl_skInfo->Width - Shp_ColorLine1->Left - 4;
	} else{
		Shp_ColorLine1->Width = 0;
	}
	if( Shp_ColorLine2->Left < Pnl_skInfo->Width &&
        Pnl_skInfo->Width - Shp_ColorLine2->Left - 4 > 0 ){
		Shp_ColorLine2->Width = Pnl_skInfo->Width - Shp_ColorLine2->Left - 4;
	} else{
		Shp_ColorLine2->Width = 0;
	}

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Panel22Resize(TObject *Sender)
{
    // 他のパネルと連携してサイズ変更します
    Panel23->Height = Panel22->Height;
    Panel24->Height = Panel22->Height;
    // スプリッターの位置がずれる場合があるので、位置を設定しなおします
    if( Panel22->Height <= Splitter3->MinSize )
    	Splitter3->Top  = Splitter3->MinSize;
    else
    	Splitter3->Top  = Panel22->Height;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Panel23Resize(TObject *Sender)
{
    // 他のパネルと連携してサイズ変更します
    Panel22->Height = Panel23->Height;
    Panel24->Height = Panel23->Height;
    // スプリッターの位置がずれる場合があるので、位置を設定しなおします
    if( Panel23->Height <= Splitter4->MinSize )
	    Splitter4->Top  = Splitter4->MinSize;
    else
	    Splitter4->Top  = Panel23->Height;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Panel24Resize(TObject *Sender)
{
    // 他のパネルと連携してサイズ変更します
    Panel22->Height = Panel24->Height;
    Panel23->Height = Panel24->Height;
    // スプリッターの位置がずれる場合があるので、位置を設定しなおします
    if( Panel24->Height <= Splitter5->MinSize )
    	Splitter5->Top  = Splitter5->MinSize;
	else
    	Splitter5->Top  = Panel24->Height;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Panel173Resize(TObject *Sender)
{
    if( Panel173->Height >= (Mem_vRIRE_MEMOORG->Height + 18) )
	    Panel173->Height = Mem_vRIRE_MEMOORG->Height + 18;

    // 他のパネルと連携してサイズ変更します
    Panel174->Height = Panel173->Height;
    Panel175->Height = Panel173->Height;
    // スプリッターの位置がずれる場合があるので、位置を設定しなおします
    if( Panel173->Height <= Splitter6->MinSize )
    	Splitter6->Top  = Splitter6->MinSize;
	else
    	Splitter6->Top  = Panel173->Height;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Panel174Resize(TObject *Sender)
{
    if( Panel174->Height >= (Mem_vRIRE_MEMOORG->Height + 18) )
	    Panel174->Height = Mem_vRIRE_MEMOORG->Height + 18;

    // 他のパネルと連携してサイズ変更します
    Panel173->Height = Panel174->Height;
    Panel175->Height = Panel174->Height;
    // スプリッターの位置がずれる場合があるので、位置を設定しなおします
    if( Panel174->Height <= Splitter7->MinSize )
    	Splitter7->Top  = Splitter7->MinSize;
	else
    	Splitter7->Top  = Panel174->Height;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Panel175Resize(TObject *Sender)
{
    if( Panel175->Height >= (Mem_vRIRE_MEMOORG->Height + 18) )
	    Panel175->Height = Mem_vRIRE_MEMOORG->Height + 18;

    // 他のパネルと連携してサイズ変更します
    Panel173->Height = Panel175->Height;
    Panel174->Height = Panel175->Height;
    // スプリッターの位置がずれる場合があるので、位置を設定しなおします
    if( Panel175->Height <= Splitter8->MinSize )
    	Splitter8->Top  = Splitter8->MinSize;
	else
    	Splitter8->Top  = Panel175->Height;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Panel14Resize(TObject *Sender)
{
    //
    // 現在もおかしい
    //
    // スプリッターの位置がずれる場合があるので、位置を設定しなおします
    if( Panel14->Width <= Splitter2->MinSize )
    	Splitter2->Left  = Splitter2->MinSize;
	else
    	Splitter2->Left  = Panel14->Width;
}
//---------------------------------------------------------------------------
//
//  概要
//    OnKeyDownイベント	：キー入力があると発生します。
//
//  機能説明
//    ファンクションキーの各処理を呼び出します。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    WORD &Key			：キーコード
//    TShiftState Shift	：[Shift]，[Alt]，[Ctrl]キーを判定します
//  戻り値
//    なし。
//
//  備考
//    Ｆ２の入力はEditBoxが開きグリッド移動の際更新フラグが誤判定
//    するのでＦ２→Ｆ１３として処理を行います。
//
//---------------------------------------------------------------------------

void __fastcall TForm1::AllKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    bool blnHoge=true;
//    MSG msg;
    // [Ctrl]キーを押した時
    if( Shift.Contains(ssCtrl) ){
        BtnF01->Caption = "全情報表示";
        BtnF02->Caption = "素材値表示";
        BtnF03->Caption = "履歴値表示";
        BtnF04->Caption = "グラフ表示";
        BtnF05->Caption = "備考欄表示";
        BtnF06->Caption = "項目編集";
        BtnF07->Caption = "素材ロット";
        BtnF08->Caption = "分割票入力";
        BtnF09->Caption = "印刷値編集";
        BtnF10->Caption = "素材取直し";
        BtnF11->Caption = "";
        BtnF12->Caption = "";

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
        BtnF11->Enabled = false;
        BtnF12->Enabled = false;

        BtnF01->Tag = 1;
        BtnF02->Tag = 1;
        BtnF03->Tag = 1;
        BtnF04->Tag = 1;
        BtnF05->Tag = 1;
        BtnF06->Tag = 1;
        BtnF07->Tag = 1;
        BtnF08->Tag = 1;
        BtnF09->Tag = 1;
        BtnF10->Tag = 1;
        BtnF11->Tag = 1;
        BtnF12->Tag = 1;
    }
    switch(Key) {
        case VK_F1:  BtnF01Click(Sender);    break;
        case VK_F2:  Key = VK_F13;
                     Delete_InplaceEdit(Sender);		// 編集ウィンドウを無効にします
                     BtnF02Click(Sender);
                     break;
        case VK_F3:  BtnF03Click(Sender);    break;
        case VK_F4:  BtnF04Click(Sender);    break;
        case VK_F5:  BtnF05Click(Sender);    break;
        case VK_F6:  BtnF06Click(Sender);    break;
        case VK_F7:  BtnF07Click(Sender);    break;
        case VK_F8:
    				 switch(pInfoGlaph.GRID_NO)
    				 {
	    			 case 1: AllGRID_SelectCell(SGr_vSOKU_SYUKA,SGr_vSOKU_SYUKA->Col,0,blnHoge);
							 break;
                     case 2: AllGRID_SelectCell(SGr_vRIRE_SYUKA,SGr_vRIRE_SYUKA->Col,0,blnHoge);
                     		 break;
	    			 case 3: AllGRID_SelectCell(SGr_vSOKU_SOZAI,SGr_vSOKU_SOZAI->Col,0,blnHoge);
							 break;
	    			 case 4: AllGRID_SelectCell(SGr_vRIRE_SOZAI,SGr_vRIRE_SOZAI->Col,0,blnHoge);
							 break;
					 }


        			 BtnF08Click(Sender);    break;
        case VK_F9:  BtnF09Click(Sender);    break;
        case VK_F10: BtnF10Click(Sender);
                     if( Shift.Contains(ssCtrl) ) Key = 0;
					 break;
        case VK_F11: BtnF11Click(Sender);    break;
        case VK_ESCAPE:
        case VK_F12: BtnF12Click(Sender);    break;

        // Enter
        case VK_RETURN:

                // 代表得意先品番にカーソルがあるとき
        		if( Cmb_DTKSHIN->Focused() ){
                	Edt_LOTNO->SetFocus();
                	break;
                }

                // ロットNOなどにカーソルがあるとき
        		if( Edt_LOTNO->Focused()		||
                	CHkSEIKANDATA->Focused()	||
                    Chk_RIRE->Focused()			||
                    Edt_RIRE_NUM->Focused()		){
                    BtnF07Click(Sender);
                }
				break;

        case VK_LEFT:
        case VK_RIGHT:
                if( SGr_vRIRE_SOZAI->EditorMode	||
                	SGr_vSOKU_SOZAI->EditorMode	||
                	SGr_vRIRE_SYUKA->EditorMode	||
                    SGr_vSOKU_SYUKA->EditorMode ){
                    if( AnsiString(Sender->ClassName()) == "TStringGrid" ){

						TStringGrid		*Sgr = (TStringGrid *)Sender;

						// キャレットの位置を取得
						// 編集セル（TInplaceEdit）を検索
						TInplaceEdit *edit = NULL;
						int ComCount = Sgr->ComponentCount;  // 全コンポーネント数

						for( int i=0; i<ComCount; i++ ){
							TComponent *component = Sgr->Components[i];
                            AnsiString name = component->ClassName();
							if( name == "TInplaceEdit" ){
								edit = ( TInplaceEdit* )component;
								break;
							}
						}

						// 編集セル（TInplaceEdit）が存在する
						if( edit ){
                            if( Key == VK_LEFT && Sgr->Col > 0 ){
                            	if( edit->SelStart == 0 && edit->SelLength == 0 ){
                                	Sgr->Col = Sgr->Col - 1;
								}
                            }
                            if( Key == VK_RIGHT && Sgr->Col < (Sgr->ColCount - 1) ){
                            	if( edit->SelStart == edit->Text.Length() && edit->SelLength == 0 ){
                                	Sgr->Col = Sgr->Col + 1;
								}
                            }
						}
                    }
                }
				break;
        case VK_DELETE:
                if( AnsiString(Sender->ClassName()) == "TStringGrid" ){

					TStringGrid		*Sgr = (TStringGrid *)Sender;

					// キャレットの位置を取得
					// 編集セル（TInplaceEdit）を検索
					TInplaceEdit *edit = NULL;
					int ComCount = Sgr->ComponentCount;  // 全コンポーネント数
                    int bAllClear;
                    bAllClear = false;
					for( int i=0; i<ComCount; i++ ){
						TComponent *component = Sgr->Components[i];
                        AnsiString name = component->ClassName();
						if( name == "TInplaceEdit" ){
							edit = ( TInplaceEdit* )component;
                            if( !edit->Visible() ){
                            	edit = NULL;
                            }
							break;
						}
					}

                    // 編集できないセルは、削除も出来ません
					if(Sender == SGr_vSOKU_SYUKA) {
						if((Sgr->Cells[Sgr->Col][Sgr->Row] == "不要" && bKASOU_MOVE == false)
							|| !hCELLINFO_SOKU_SYUKA) {
							break;
						}
						if( hCELLINFO_SOKU_SYUKA) {
							if( AnsiString(pCELLINFO_SOKU_SYUKA[Sgr->Col*Sgr->RowCount+Sgr->Row].RESULT) == "不要") {
								break;
							}
						}
					}
					if(Sender == SGr_vSOKU_SOZAI) {
						if((Sgr->Cells[Sgr->Col][Sgr->Row] == "不要" && bKASOU_MOVE == false)
							|| !hCELLINFO_SOKU_SOZAI) {
							break;
						}
						if( hCELLINFO_SOKU_SOZAI) {
							if( AnsiString(pCELLINFO_SOKU_SOZAI[Sgr->Col*Sgr->RowCount+Sgr->Row].RESULT) == "不要") {
								break;
							}
						}
					}
					if(Sender == SGr_vRIRE_SYUKA) {
						if((Sgr->Cells[Sgr->Col][Sgr->Row] == "不要" && bKASOU_MOVE == false)
							|| !hCELLINFO_RIRE_SYUKA) {
							break;
						}
						if( hCELLINFO_RIRE_SYUKA) {
							if( AnsiString(pCELLINFO_RIRE_SYUKA[Sgr->Col*Sgr->RowCount+Sgr->Row].RESULT) == "不要") {
								break;
							}
						}
					}
					if(Sender == SGr_vRIRE_SOZAI) {
						if((Sgr->Cells[Sgr->Col][Sgr->Row] == "不要" && bKASOU_MOVE == false)
							|| !hCELLINFO_RIRE_SOZAI) {
							break;
						}
						if( hCELLINFO_RIRE_SOZAI) {
							if( AnsiString(pCELLINFO_RIRE_SOZAI[Sgr->Col*Sgr->RowCount+Sgr->Row].RESULT) == "不要") {
								break;
							}
						}
					}
					if( Sgr->Row == 0 ) {
						break;
					}

					// 編集セル（TInplaceEdit）が存在しない
                    if( !edit ){
                        Sgr->Cells[Sgr->Col][Sgr->Row] = "";
                        GRID_SetEditText(Sender,Sgr->Col, Sgr->Row, "");

                    }
                }
                if( Sender == SGr_vSOKU_SYUKA ) SGr_vSOKU_SYUKAKeyPress(Sender, VK_DELETE);
                if( Sender == SGr_vRIRE_SYUKA ) SGr_vRIRE_SYUKAKeyPress(Sender, VK_DELETE);
                if( Sender == SGr_vSOKU_SOZAI ) SGr_vSOKU_SOZAIKeyPress(Sender, VK_DELETE);
                if( Sender == SGr_vRIRE_SOZAI ) SGr_vRIRE_SOZAIKeyPress(Sender, VK_DELETE);
                break;
    }

	int iCol,iRow;
    //前項／次項／Returnの入力は後処理としてグリッド上にフォーカスをセットします
	if(Key == VK_F13 || Key == VK_F3 || Key == VK_RETURN)
    {
    	switch(pInfoGlaph.GRID_NO)
    	{
	    case 1:
    	    iCol = SGr_vSOKU_SYUKA->Col;
			iRow = SGr_vSOKU_SYUKA->Row;
			AllGRID_SelectCell(SGr_vSOKU_SYUKA,iCol,iRow,blnHoge);
			break;
	    case 2:
    	    iCol = SGr_vRIRE_SYUKA->Col;
			iRow = SGr_vRIRE_SYUKA->Row;
			AllGRID_SelectCell(SGr_vRIRE_SYUKA,iCol,iRow,blnHoge);
			break;
	    case 3:
    	    iCol = SGr_vSOKU_SOZAI->Col;
			iRow = SGr_vSOKU_SOZAI->Row;
			AllGRID_SelectCell(SGr_vSOKU_SOZAI,iCol,iRow,blnHoge);
			break;
	    case 4:
    	    iCol = SGr_vRIRE_SOZAI->Col;
			iRow = SGr_vRIRE_SOZAI->Row;
			AllGRID_SelectCell(SGr_vRIRE_SOZAI,iCol,iRow,blnHoge);
			break;
		}
	}
}

//---------------------------------------------------------------------------
//
//  概要
//    OnKeyUpイベント	：ユーザーが任意のキーを離すと発生します
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
void __fastcall TForm1::AllKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
      if( Key == 17 ){
          BtnF01->Caption = "一覧検索";
          BtnF02->Caption = "前項";
          BtnF03->Caption = "次項";
          BtnF04->Caption = "ｶｰｿﾙ方向";
          BtnF05->Caption = "Ch切替";
          BtnF06->Caption = "HT読込";
          BtnF07->Caption = "検索";
          BtnF08->Caption = "担当者切替";
          BtnF09->Caption = "画面印刷";
          BtnF10->Caption = "Excel出力";
          BtnF11->Caption = "保存";
          BtnF12->Caption = "戻る";

          // 2003/05/19 A.T
          //BtnF01->Enabled = true;
          FormEnter(Sender);

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

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：素材検査用スクロールボックスのスクロールイベント処理
//
//  機能説明
//    スクロールボックスがスクロールしたとき隣のグリッドも合わせてスクロールします
//
//  パラメタ説明
//    TMessage& msg		：Windows メッセージを示します。
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SBx_Left_SOZAI_WndProc(TMessage& msg) {
    if (msg.Msg == WM_VSCROLL){
        int iPos;
        iPos = (int)(SBx_Left_SOZAI->VertScrollBar->Position / 25);
        SGr_vRIRE_SOZAI->TopRow = iPos;
        SGr_vSOKU_SOZAI->TopRow = iPos;
        if( SBx_Left_SOZAI->VertScrollBar->Position != (iPos * 25))
        	SBx_Left_SOZAI->VertScrollBar->Position = iPos * 25;
    }
    SaveSBx_Left_SOZAI_WndProc(msg);
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：出荷検査用スクロールボックスのスクロールイベント処理
//
//  機能説明
//    スクロールボックスがスクロールしたとき隣のグリッドも合わせてスクロールします
//
//  パラメタ説明
//    TMessage& msg		：Windows メッセージを示します。
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SBx_Left_SYUKA_WndProc(TMessage& msg) {
    if (msg.Msg == WM_VSCROLL){
        int iPos;
        iPos = (int)(SBx_Left_SYUKA->VertScrollBar->Position / 25);
        SGr_vRIRE_SYUKA->TopRow = iPos;
        SGr_vSOKU_SYUKA->TopRow = iPos;
        if( SBx_Left_SYUKA->VertScrollBar->Position != (iPos * 25))
        	SBx_Left_SYUKA->VertScrollBar->Position = iPos * 25;
    }
    SaveSBx_Left_SYUKA_WndProc(msg);
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：備考（測定）用スクロールボックスのスクロールイベント処理
//
//  機能説明
//    スクロールボックスがスクロールしたとき上のグリッドも合わせてスクロールします
//
//  パラメタ説明
//    TMessage& msg		：Windows メッセージを示します。
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SBx_vSOKU_MEMO_WndProc(TMessage& msg) {
    if (msg.Msg == WM_HSCROLL){
        int iPos;
        iPos = (int)(SBx_vSOKU_MEMO->HorzScrollBar->Position / Mem_vSOKU_MEMOORG->Width);
        SGr_vSOKU_SOZAI->LeftCol = iPos;
        SGr_vSOKU_SYUKA->LeftCol = iPos;
        if( SBx_vSOKU_MEMO->HorzScrollBar->Position != (iPos * (Mem_vSOKU_MEMOORG->Width + 1)))
        	SBx_vSOKU_MEMO->HorzScrollBar->Position = iPos * (Mem_vSOKU_MEMOORG->Width + 1);
    }
    SaveSBx_vSOKU_MEMO_WndProc(msg);
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：備考（履歴）用スクロールボックスのスクロールイベント処理
//
//  機能説明
//    スクロールボックスがスクロールしたとき上のグリッドも合わせてスクロールします
//
//  パラメタ説明
//    TMessage& msg		：Windows メッセージを示します。
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SBx_vRIRE_MEMO_WndProc(TMessage& msg) {
    if (msg.Msg == WM_HSCROLL){
        int iPos;
        iPos = (int)(SBx_vRIRE_MEMO->HorzScrollBar->Position / Mem_vRIRE_MEMOORG->Width);
        SGr_vRIRE_SOZAI->LeftCol = iPos;
        SGr_vRIRE_SYUKA->LeftCol = iPos;
        if( SBx_vRIRE_MEMO->HorzScrollBar->Position != (iPos * (Mem_vRIRE_MEMOORG->Width + 1 )))
        	SBx_vRIRE_MEMO->HorzScrollBar->Position = iPos * (Mem_vRIRE_MEMOORG->Width + 1 );
    }
    SaveSBx_vRIRE_MEMO_WndProc(msg);
}

//---------------------------------------------------------------------------
//
//  概要
//    OnTopLeftChange	：TopRow プロパティまたは LeftCol プロパティが変更された直後に発生します。
//
//  機能説明
//    素材検査（履歴）のグリッドがスクロールしたときに左＆下のスクロールボックスも
//    合わせてスクロールします
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
void __fastcall TForm1::SGr_vRIRE_SOZAITopLeftChanged(TObject *Sender)
{
	//TRect Rectangle;
    int   i;
    int   iPos;


    // スクロールバーの連携について

    SGr_vSOKU_SOZAI->TopRow  = SGr_vRIRE_SOZAI->TopRow;
    SGr_vRIRE_SYUKA->LeftCol = SGr_vRIRE_SOZAI->LeftCol;
    SGr_tRIRE->LeftCol       = SGr_vRIRE_SOZAI->LeftCol;
    SGr_tRIRE_SOZAI->LeftCol = SGr_vRIRE_SOZAI->LeftCol;
    SGr_tRIRE_SYUKA->LeftCol = SGr_vRIRE_SOZAI->LeftCol;
	SBx_vRIRE_MEMO->HorzScrollBar->Position = SGr_vRIRE_SOZAI->LeftCol * (Mem_vRIRE_MEMOORG->Width + 1);
    iPos = 0;
    for( i=0; i<SGr_vRIRE_SOZAI->TopRow; i++){
    	iPos += (SGr_vRIRE_SOZAI->RowHeights[i] + 1);
    }
	SBx_Left_SOZAI->VertScrollBar->Position = iPos;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnTopLeftChange	：TopRow プロパティまたは LeftCol プロパティが変更された直後に発生します。
//
//  機能説明
//    素材検査（測定）のグリッドがスクロールしたときに左＆下のスクロールボックスも
//    合わせてスクロールします
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
void __fastcall TForm1::SGr_vSOKU_SOZAITopLeftChanged(TObject *Sender)
{
    int   i;
    int   iPos;

    SGr_vRIRE_SOZAI->TopRow  = SGr_vSOKU_SOZAI->TopRow;  //履歴と同一ROWにする
    SGr_vSOKU_SYUKA->LeftCol = SGr_vSOKU_SOZAI->LeftCol;
    SGr_tSOKU->LeftCol       = SGr_vSOKU_SOZAI->LeftCol;
    SGr_tSOKU_SOZAI->LeftCol = SGr_vSOKU_SOZAI->LeftCol;
    SGr_tSOKU_SYUKA->LeftCol = SGr_vSOKU_SOZAI->LeftCol;
    SGr_tSOKU_SOZAI->LeftCol = SGr_vSOKU_SOZAI->LeftCol;
	SBx_vSOKU_MEMO->HorzScrollBar->Position = SGr_vSOKU_SOZAI->LeftCol * (Mem_vSOKU_MEMOORG->Width + 1);
    iPos = 0;
    for( i=0; i<SGr_vSOKU_SOZAI->TopRow; i++){
    	iPos += (SGr_vSOKU_SOZAI->RowHeights[i] + 1);
    }
	SBx_Left_SOZAI->VertScrollBar->Position = iPos;
}

//---------------------------------------------------------------------------
//
//  概要
//    OnTopLeftChange	：TopRow プロパティまたは LeftCol プロパティが変更された直後に発生します。
//
//  機能説明
//    出荷検査（履歴）のグリッドがスクロールしたときに左＆下のスクロールボックスも
//    合わせてスクロールします
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
void __fastcall TForm1::SGr_vRIRE_SYUKATopLeftChanged(TObject *Sender)
{
    int   i;
    int   iPos;

    SGr_vSOKU_SYUKA->TopRow  = SGr_vRIRE_SYUKA->TopRow;
    SGr_vRIRE_SOZAI->LeftCol = SGr_vRIRE_SYUKA->LeftCol;
    SGr_tRIRE->LeftCol       = SGr_vRIRE_SYUKA->LeftCol;
    SGr_tRIRE_SOZAI->LeftCol = SGr_vRIRE_SYUKA->LeftCol;
    SGr_tRIRE_SYUKA->LeftCol = SGr_vRIRE_SYUKA->LeftCol;
	SBx_vRIRE_MEMO->HorzScrollBar->Position = SGr_vRIRE_SYUKA->LeftCol * (Mem_vRIRE_MEMOORG->Width + 1);
    iPos = 0;
    for( i=0; i<SGr_vRIRE_SYUKA->TopRow; i++){
    	iPos += (SGr_vRIRE_SYUKA->RowHeights[i] + 1);
    }
	SBx_Left_SYUKA->VertScrollBar->Position = iPos;
}

//---------------------------------------------------------------------------
//
//  概要
//    OnTopLeftChange	：TopRow プロパティまたは LeftCol プロパティが変更された直後に発生します。
//
//  機能説明
//    出荷検査（測定）のグリッドがスクロールしたときに左＆下のスクロールボックスも
//    合わせてスクロールします
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
void __fastcall TForm1::SGr_vSOKU_SYUKATopLeftChanged(TObject *Sender)
{
    int   i;
    int   iPos;

    SGr_vRIRE_SYUKA->TopRow  = SGr_vSOKU_SYUKA->TopRow;
    SGr_vSOKU_SOZAI->LeftCol = SGr_vSOKU_SYUKA->LeftCol;          //Grid表示開始位置を測定出荷Gridと同じにする
    SGr_tSOKU->LeftCol       = SGr_vSOKU_SYUKA->LeftCol;          //Grid表示開始位置を測定出荷Gridと同じにする
    SGr_tSOKU_SOZAI->LeftCol = SGr_vSOKU_SYUKA->LeftCol;          //Grid表示開始位置を測定出荷Gridと同じにする
    SGr_tSOKU_SYUKA->LeftCol = SGr_vSOKU_SYUKA->LeftCol;          //Grid表示開始位置を測定出荷Gridと同じにする
	SBx_vSOKU_MEMO->HorzScrollBar->Position = SGr_vSOKU_SYUKA->LeftCol * (Mem_vSOKU_MEMOORG->Width + 1);
    iPos = 0;
    for( i=0; i<SGr_vSOKU_SYUKA->TopRow; i++){
    	iPos += (SGr_vSOKU_SYUKA->RowHeights[i] + 1);
    }
	SBx_Left_SYUKA->VertScrollBar->Position = iPos;
}

//---------------------------------------------------------------------------
//
//  概要
//    OnCanResize       ：ユーザーがスプリッタをマウスで移動しようとすると発生します。
//
//  機能説明
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
void __fastcall TForm1::Splitter4CanResize(TObject *Sender, int &NewSize,
      bool &Accept)
{
          BtnF12->Tag = 0;

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：DrawCellやセーブ時に使用するロット毎の判定を行います。
//
//  機能説明
//    ロットの判定を内部メモリに反映します。
//    −１：未測定、０：ＯＫ、１：ＮＧ、２：指示無し
//  　優先度は　未測定＞ＮＧ＞ＯＫ＞指示無しです
//
//  パラメタ説明
//    TObject *Sender   対象セル
//    int ACol          対象セルのCol位置
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::GET_HANTEI(TObject *Sender, int ACol)
{
	int iGridTag;
    int iRow,iRowCount,i1;
    int iJudge,iDISP_JUDGE,iSOKU_JUDGE;
	AnsiString sBuf,sRESULT,sDISP_RESULT,sTEMP_RESULT;
	AnsiString sDECI;
	AnsiString sMAX,sMIN;
	bool bRtn;
	iGridTag = 0;
	iRowCount = 0;
	iJudge = 2;
	iRow = 0;
    sBuf ="";
                                                  
    //Senderが有効かを判断します
 	if(Sender == SGr_vSOKU_SYUKA)
	{
        if(!hCELLINFO_SOKU_SYUKA) return;
 		iGridTag = 1;
        iRowCount = SGr_vSOKU_SYUKA->RowCount;
	}
 	if(Sender == SGr_vRIRE_SYUKA)
	{
        if(!hCELLINFO_RIRE_SYUKA) return;
 		iGridTag = 2;
       	iRowCount = SGr_vRIRE_SYUKA->RowCount;
	}
 	if(Sender == SGr_vSOKU_SOZAI)
	{
        if(!hCELLINFO_SOKU_SOZAI) return;
 		iGridTag = 3;
       	iRowCount = SGr_vSOKU_SOZAI->RowCount;
	}
 	if(Sender == SGr_vRIRE_SOZAI)
	{
        if(!hCELLINFO_RIRE_SYUKA) return;
    	iGridTag = 4;
       	iRowCount = SGr_vRIRE_SOZAI->RowCount;
	}
    //選択されたグリッドに対して判定処理を行います（全グリッドに対して処理を分けていますが処理内容は同じです）
	switch( iGridTag )
	{
    case 1:
		if(hCELLINFO_SOKU_SYUKA && hSOKU_KSD01_DATA)
		{
            //初期値は測定指示無し
			iSOKU_JUDGE = 2;
			iDISP_JUDGE = 2;
            //0行目は判定なので1行目から値を調べる
			for( iRow = 1;iRow < iRowCount;iRow++)
			{
                if((AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].SOKU_FLG).ToIntDef(0) != 0 )
                //&& (AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].KOMK_NO).ToIntDef(0) != 0))
                && (pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].INS_ON != false))
                {
    				switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].VALUE_TYPE).ToIntDef(0))
	    			{
                    case 0:
			    	case 1:
   				    	sDECI = "0";
					    for(i1 = 0;i1 < AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].VALUE_DECI).ToIntDef(0);i1++)
    					{
                            if( sDECI.Length() == 1 ) sDECI += ".";
		    				sDECI +="0";
			    		}
				    	break;
                    default:
	    				break;
		    		}

    				switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].VALUE_TYPE).ToIntDef(0))
	    			{
		    		case 0:
                    case 1:
				    	sMAX = pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].MAX;
					    sMIN = pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].MIN;
                    	sRESULT = pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].RESULT;
	    				sTEMP_RESULT = sRESULT;
                    	bRtn = ConvDoubleDefS(sTEMP_RESULT,sDECI,sTEMP_RESULT,&sRESULT);
                        //無効な入力は未測定個所とします
                        if(bRtn)
				    	{
					    	switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].KIKA_TYPE).ToIntDef(0))
                            {
    						case 1:
	    						switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].KIKA_KIND).ToIntDef(0))
                            	{
			    				case 1:
				    				if((sMIN.ToDouble() > sRESULT.ToDouble())
					    			|| (sMAX.ToDouble() < sRESULT.ToDouble()))
						    		{
							    		if(iSOKU_JUDGE != -1) iSOKU_JUDGE = 1;
								    }
                                    else if( iSOKU_JUDGE == 2 ) {
                                        iSOKU_JUDGE = 0;
                                    }
    								break;
	    						case 2:
		    						if( sRESULT.ToDouble() > sMAX.ToDouble())
			    					{
				    					if(iSOKU_JUDGE != -1) iSOKU_JUDGE = 1;
					    			}
                                    else if( iSOKU_JUDGE == 2 ) {
                                        iSOKU_JUDGE = 0;
                                    }
						    		break;
							    case 3:
								    if( sRESULT.ToDouble() < sMIN.ToDouble())
    								{
	    								if(iSOKU_JUDGE != -1) iSOKU_JUDGE = 1;
		    						}
                                    else if( iSOKU_JUDGE == 2 ) {
                                        iSOKU_JUDGE = 0;
                                    }
			    					break;
				    			}
                                break;
						    case 2:
    							if((sMIN.ToDouble() > sRESULT.ToDouble())
	    						|| (sMAX.ToDouble() < sRESULT.ToDouble()))
		    					{
			    					if(iSOKU_JUDGE != -1) iSOKU_JUDGE = 1;
				    			}
                                else if( iSOKU_JUDGE == 2 ) {
                                    iSOKU_JUDGE = 0;
                                }
                                break;
						    }
    					}
                        else
                        {
                            iSOKU_JUDGE = -1;           //未測定個所発見
                        }
                    	sDISP_RESULT = pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].DISP_RESULT;
	    				sTEMP_RESULT = sDISP_RESULT;
                    	bRtn = ConvDoubleDefS(sTEMP_RESULT,sDECI,sTEMP_RESULT,&sDISP_RESULT);
                        //無効な入力は未測定個所とします
                        if(bRtn)
				    	{
					    	switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].KIKA_TYPE).ToIntDef(0))
                            {
    						case 1:
	    						switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].KIKA_KIND).ToIntDef(0))
                            	{
			    				case 1:
				    				if((sMIN.ToDouble() > sDISP_RESULT.ToDouble())
					    			|| (sMAX.ToDouble() < sDISP_RESULT.ToDouble()))
						    		{
							    		if(iDISP_JUDGE != -1) iDISP_JUDGE = 1;
								    }
                                    else if( iDISP_JUDGE == 2 ) {
                                        iDISP_JUDGE = 0;
                                    }
    								break;
	    						case 2:
		    						if( sDISP_RESULT.ToDouble() > sMAX.ToDouble())
			    					{
				    					if(iDISP_JUDGE != -1) iDISP_JUDGE = 1;
					    			}
                                    else if( iDISP_JUDGE == 2 ) {
                                        iDISP_JUDGE = 0;
                                    }
						    		break;
							    case 3:
								    if( sDISP_RESULT.ToDouble() < sMIN.ToDouble())
    								{
	    								if(iDISP_JUDGE != -1) iDISP_JUDGE = 1;
		    						}
                                    else if( iDISP_JUDGE == 2 ) {
                                        iDISP_JUDGE = 0;
                                    }
			    					break;
				    			}
                                break;
						    case 2:
							    if((sMIN.ToDouble() > sDISP_RESULT.ToDouble())
    							|| (sMAX.ToDouble() < sDISP_RESULT.ToDouble()))
	    						{
		    						if(iDISP_JUDGE != -1) iDISP_JUDGE = 1;
			    				}
                                else if( iDISP_JUDGE == 2 ) {
                                    iDISP_JUDGE = 0;
                                }
                                break;
					    	}
    					}
                        else
                        {
                            iDISP_JUDGE = -1;           //未測定個所発見
                        }
                        break;
		    		case 2: //良否判定です
                        if(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].RESULT).Trim().Length() != 0)
                        {
                    	    if((AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].RESULT).ToIntDef(0)) != 0)
				    	    {
					    	    if(iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
                            }
                            else if(iSOKU_JUDGE == 2 ){
                                iSOKU_JUDGE = 0;
                            }
    					}
                        else
                        {
                            iSOKU_JUDGE = -1;
                        }

                        if(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].DISP_RESULT).Trim().Length() != 0)
                        {
                    	    if((AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].DISP_RESULT).ToIntDef(0)) != 0)
				    	    {
					    	    if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
                            }
                            else if(iDISP_JUDGE == 2 ){
                                iDISP_JUDGE = 0;
                            }
    					}
                        else
                        {
                            iDISP_JUDGE = -1;
                        }
                        break;
                    case 3: //文字入力
                        if(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].RESULT).Trim().Length() ==0)
                        {
                            iSOKU_JUDGE = -1;
                        }
                        else if(iSOKU_JUDGE == 2 ){
                            iSOKU_JUDGE = 0;
                        }
                        if(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].DISP_RESULT).Trim().Length() ==0)
                        {
                            iDISP_JUDGE = -1;
                        }
                        else if(iDISP_JUDGE == 2 ){
                            iDISP_JUDGE = 0;
                        }
                        break;
    				default:
	    				break;
		    		}
                }
            }
            //判定を内部メモリに書きます
            strcpy(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].SOKU_OK,AnsiString(iSOKU_JUDGE).c_str());
            strcpy(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+iRow].DISP_OK,AnsiString(iDISP_JUDGE).c_str());
            strcpy(pSOKU_KSD01_DATA[ACol].SYUKA_OK		,AnsiString(iSOKU_JUDGE).c_str());
        	strcpy(pSOKU_KSD01_DATA[ACol].SYUKA_OK_PRT	,AnsiString(iDISP_JUDGE).c_str());
		}
 		break;
    //以下Case　2、3、4はセルの位置と対象の入れるが違うだけで処理内容は同じです
    case 2:
        if(Form1->iRIRE_CNT == 0 ) return;
		if(hCELLINFO_RIRE_SYUKA && hRIRE_KSD01_DATA)
		{
			iSOKU_JUDGE = 2;
			iDISP_JUDGE = 2;
			for( iRow = 1;iRow < iRowCount;iRow++)		//0行目は判定なので1から値を調べる
			{
                if((AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].SOKU_FLG).ToIntDef(0) != 0)
                //&& (AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].KOMK_NO).ToIntDef(0) != 0))
                && (pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].INS_ON != false))
                {
    				switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].VALUE_TYPE).ToIntDef(0))
	    			{
                    case 0:
			    	case 1:
   				    	sDECI = "0";
					    for(i1 = 0;i1 < AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].VALUE_DECI).ToIntDef(0);i1++)
    					{
                            if( sDECI.Length() == 1 ) sDECI += ".";
		    				sDECI +="0";
			    		}
				    	break;
                   default:
	    				break;
		    		}

    				switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].VALUE_TYPE).ToIntDef(0))
	    			{
		    		case 0:
                    case 1:
				    	sMAX = pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].MAX;
					    sMIN = pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].MIN;
                    	sRESULT = pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].RESULT;
	    				sTEMP_RESULT = sRESULT;
                    	bRtn = ConvDoubleDefS(sTEMP_RESULT,sDECI,sTEMP_RESULT,&sRESULT);
                        if(bRtn)
				    	{
					    	switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].KIKA_TYPE).ToIntDef(0))
                            {
    						case 1:
	    						switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].KIKA_KIND).ToIntDef(0))
                            	{
			    				case 1:
				    				if((sMIN.ToDouble() > sRESULT.ToDouble())
					    			|| (sMAX.ToDouble() < sRESULT.ToDouble()))
						    		{
							    		if(iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
								    }
                                    else if(iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
    								break;
	    						case 2:
		    						if( sRESULT.ToDouble() > sMAX.ToDouble())
			    					{
				    					if(iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
					    			}
                                    else if(iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
						    		break;
							    case 3:
    								if( sRESULT.ToDouble() < sMIN.ToDouble())
	    							{
		    							if(iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
			    					}
                                    else if(iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
				    				break;
					    		}
                                break;
    						case 2:
	    						if((sMIN.ToDouble() > sRESULT.ToDouble())
		    					|| (sMAX.ToDouble() < sRESULT.ToDouble()))
			    				{
				    				if(iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
					    		}
                                else if(iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
                                break;
    						}
	    				}
                        else
                        {
                            iSOKU_JUDGE = -1;
                        }
                    	sDISP_RESULT = pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].DISP_RESULT;
			    		sTEMP_RESULT = sDISP_RESULT;
                    	bRtn = ConvDoubleDefS(sTEMP_RESULT,sDECI,sTEMP_RESULT,&sDISP_RESULT);
                        if(bRtn)
    					{
	    					switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].KIKA_TYPE).ToIntDef(0))
                            {
			    			case 1:
				    			switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].KIKA_KIND).ToIntDef(0))
                            	{
						    	case 1:
							    	if((sMIN.ToDouble() > sDISP_RESULT.ToDouble())
								    || (sMAX.ToDouble() < sDISP_RESULT.ToDouble()))
    								{
	    								if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
		    						}
                                    else if(iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
			    					break;
				    			case 2:
					    			if( sDISP_RESULT.ToDouble() > sMAX.ToDouble())
						    		{
							    		if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
								    }
                                    else if(iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
    								break;
	    						case 3:
		    						if( sDISP_RESULT.ToDouble() < sMIN.ToDouble())
			    					{
				    					if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
					    			}
                                    else if(iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
						    		break;
							    }
                                break;
	    					case 2:
		    					if((sMIN.ToDouble() > sDISP_RESULT.ToDouble())
			    				|| (sMAX.ToDouble() < sDISP_RESULT.ToDouble()))
				    			{
					    			if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
						    	}
                                else if(iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
                                break;
    						}
                        }
                        else
                        {
                            iDISP_JUDGE = -1;
                        }
                        break;
			    	case 2:
                        if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].RESULT).Trim().Length() != 0)
                        {
                    	    if((AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].RESULT).ToIntDef(0)) != 0)
					        {
    						    if( iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
                            }
                            else if(iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
	    				}
                        else iSOKU_JUDGE = -1;

                        if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].DISP_RESULT).Trim().Length() != 0)
                        {
                    	    if((AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].DISP_RESULT).ToIntDef(0)) != 0)
			    		    {
				    		    if( iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
                            }
                            else if(iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
					    }
                        else iDISP_JUDGE = -1;
                        break;
                    case 3:                     //文字入力
                        if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].RESULT).Trim().Length() ==0)
                        {
                            iSOKU_JUDGE = -1;
                        }
                        if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].DISP_RESULT).Trim().Length() ==0)
                        {
                            iDISP_JUDGE = -1;
                        }
                        break;
	    			default:
		    			break;
			    	}
                }
			}
            strcpy(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].SOKU_OK,AnsiString(iSOKU_JUDGE).c_str());
            strcpy(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+iRow].DISP_OK,AnsiString(iDISP_JUDGE).c_str());
            strcpy(pRIRE_KSD01_DATA[ACol].SYUKA_OK		,AnsiString(iSOKU_JUDGE).c_str());
        	strcpy(pRIRE_KSD01_DATA[ACol].SYUKA_OK_PRT	,AnsiString(iDISP_JUDGE).c_str());
		}
 		break;
    case 3:
		if(hCELLINFO_SOKU_SOZAI && hSOKU_KSD01_DATA)
		{
			iSOKU_JUDGE = 2;
			iDISP_JUDGE = 2;
			for( iRow = 1;iRow < iRowCount;iRow++)		//0行目は判定なので1から値を調べる
			{
                if((AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].SOKU_FLG).ToIntDef(0) != 0)
                //&& (AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].KOMK_NO).ToIntDef(0) != 0))
                && (pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].INS_ON != false))
                {
    				switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].VALUE_TYPE).ToIntDef(0))
	    			{
                    case 0:
			    	case 1:
   				    	sDECI = "0";
					    for(i1 = 0;i1 < AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].VALUE_DECI).ToIntDef(0);i1++)
    					{
                            if( sDECI.Length() == 1 ) sDECI += ".";
		    				sDECI +="0";
			    		}
				    	break;
                   default:
	    				break;
		    		}
    				switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].VALUE_TYPE).ToIntDef(0))
	    			{
		    		case 0:
                    case 1:
	    				sMAX = pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].MAX;
    	   				sMIN = pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].MIN;
                    	sRESULT = pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].RESULT;
	    				sTEMP_RESULT = sRESULT;
                    	bRtn = ConvDoubleDefS(sTEMP_RESULT,sDECI,sTEMP_RESULT,&sRESULT);
                        if(bRtn)
				    	{
					    	switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].KIKA_TYPE).ToIntDef(0))
                            {
    						case 1:
	    						switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].KIKA_KIND).ToIntDef(0))
                            	{
			    				case 1:
				    				if((sMIN.ToDouble() > sRESULT.ToDouble())
					    			|| (sMAX.ToDouble() < sRESULT.ToDouble()))
						    		{
							    		if(iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
								    }
                                    else if(iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
    								break;
	    						case 2:
		    						if( sRESULT.ToDouble() > sMAX.ToDouble())
			    					{
				    					if(iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
					    			}
                                    else if(iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
						    		break;
							    case 3:
    								if( sRESULT.ToDouble() < sMIN.ToDouble())
	    							{
		    							if(iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
			    					}
                                    else if(iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
				    				break;
					    		}
                                break;
    						case 2:
	    						if((sMIN.ToDouble() > sRESULT.ToDouble())
		    					|| (sMAX.ToDouble() < sRESULT.ToDouble()))
			    				{
				    				if(iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
					    		}
                                else if(iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
                                break;
    						}
	    				}
                        else
                        {
                            iSOKU_JUDGE = -1;
                        }
                    	sDISP_RESULT = pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].DISP_RESULT;
			    		sTEMP_RESULT = sDISP_RESULT;
                    	bRtn = ConvDoubleDefS(sTEMP_RESULT,sDECI,sTEMP_RESULT,&sDISP_RESULT);
                        if(bRtn)
    					{
	    					switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].KIKA_TYPE).ToIntDef(0))
                            {
			    			case 1:
				    			switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].KIKA_KIND).ToIntDef(0))
                            	{
						    	case 1:
							    	if((sMIN.ToDouble() > sDISP_RESULT.ToDouble())
								    || (sMAX.ToDouble() < sDISP_RESULT.ToDouble()))
    								{
	    								if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
		    						}
                                    else if( iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
			    					break;
				    			case 2:
					    			if( sDISP_RESULT.ToDouble() > sMAX.ToDouble())
						    		{
							    		if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
								    }
                                    else if( iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
    								break;
	    						case 3:
		    						if( sDISP_RESULT.ToDouble() < sMIN.ToDouble())
			    					{
				    					if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
					    			}
                                    else if( iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
						    		break;
							    }
                                break;
	    					case 2:
		    					if((sMIN.ToDouble() > sDISP_RESULT.ToDouble())
			    				|| (sMAX.ToDouble() < sDISP_RESULT.ToDouble()))
				    			{
					    			if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
						    	}
                                else if( iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
                                break;
    						}
	    				}
                        else
                        {
                            iDISP_JUDGE = -1;
                        }
                        break;
			    	case 2:
                        if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].RESULT).Trim().Length() != 0)
                        {
                    	    if((AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].RESULT).ToIntDef(0)) != 0)
					        {
    						    if(iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
	    				    }else if( iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
                        }
                        else
                        {
                            iSOKU_JUDGE = -1;
                        }

                    	if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].DISP_RESULT).Trim().Length() != 0)
                        {
                    	    if((AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].DISP_RESULT).ToIntDef(0)) != 0)
			    		    {
				    		    if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
                            } else if( iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;

					    }
                        else
                        {
                            iDISP_JUDGE = -1;
                        }
                        break;
                    case 3:                     //文字入力
                        if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].RESULT).Trim().Length() ==0)
                        {
                            iSOKU_JUDGE = -1;
                        }
                        if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].DISP_RESULT).Trim().Length() ==0)
                        {
                            iDISP_JUDGE = -1;
                        }
                        break;
	    			default:
		    			break;
			    	}
                }
			}
            strcpy(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].SOKU_OK,AnsiString(iSOKU_JUDGE).c_str());
            strcpy(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+iRow].DISP_OK,AnsiString(iDISP_JUDGE).c_str());
            strcpy(pSOKU_KSD01_DATA[ACol].SOZAI_OK		,AnsiString(iSOKU_JUDGE).c_str());
        	strcpy(pSOKU_KSD01_DATA[ACol].SOZAI_OK_PRT	,AnsiString(iDISP_JUDGE).c_str());
		}
 		break;
    case 4:
        if(Form1->iRIRE_CNT == 0 ) return;
		if(hCELLINFO_RIRE_SOZAI && hRIRE_KSD01_DATA)
		{
			iSOKU_JUDGE = 2;
			iDISP_JUDGE = 2;
			for( iRow = 1;iRow < iRowCount;iRow++)		//0行目は判定なので1から値を調べる
			{
                if((AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].SOKU_FLG).ToIntDef(0)!= 0)
                //&& (AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].KOMK_NO).ToIntDef(0)!= 0))
                && (pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].INS_ON != false))
                {
    				switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].VALUE_TYPE).ToIntDef(0))
	    			{
                    case 0:
			    	case 1:
   				    	sDECI = "0";
					    for(i1 = 0;i1 < AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].VALUE_DECI).ToIntDef(0);i1++)
    					{
                            if( sDECI.Length() == 1 ) sDECI += ".";
		    				sDECI +="0";
			    		}
				    	break;
                   default:
	    				break;
		    		}
    				switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].VALUE_TYPE).ToIntDef(0))
	    			{
		    		case 0:
                    case 1:
				    	sMAX = pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].MAX;
					    sMIN = pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].MIN;
                    	sRESULT = pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].RESULT;
	    				sTEMP_RESULT = sRESULT;
                    	bRtn = ConvDoubleDefS(sTEMP_RESULT,sDECI,sTEMP_RESULT,&sRESULT);
                        if(bRtn)
				    	{
					    	switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].KIKA_TYPE).ToIntDef(0))
                            {
    						case 1:
	    						switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].KIKA_KIND).ToIntDef(0))
                            	{
			    				case 1:
				    				if((sMIN.ToDouble() > sRESULT.ToDouble())
					    			|| (sMAX.ToDouble() < sRESULT.ToDouble()))
						    		{
							    		if( iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
								    }
                                    else if ( iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
    								break;
	    						case 2:
		    						if( sRESULT.ToDouble() > sMAX.ToDouble())
			    					{
				    					if( iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
					    			}
                                    else if ( iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
						    		break;
							    case 3:
    								if( sRESULT.ToDouble() < sMIN.ToDouble())
	    							{
		    							if( iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
			    					}
                                    else if ( iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
				    				break;
					    		}
                                break;
    						case 2:
	    						if((sMIN.ToDouble() > sRESULT.ToDouble())
		    					|| (sMAX.ToDouble() < sRESULT.ToDouble()))
			    				{
				    				if( iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
					    		}
                                else if( iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
                                break;
    						}
	    				}
                        else
                        {
                            iSOKU_JUDGE = -1;
                        }
                    	sDISP_RESULT = pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].DISP_RESULT;
			    		sTEMP_RESULT = sDISP_RESULT;
                    	bRtn = ConvDoubleDefS(sTEMP_RESULT,sDECI,sTEMP_RESULT,&sDISP_RESULT);
                        if(bRtn)
    					{
	    					switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].KIKA_TYPE).ToIntDef(0))
                            {
			    			case 1:
				    			switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].KIKA_KIND).ToIntDef(0))
                            	{
						    	case 1:
							    	if((sMIN.ToDouble() > sDISP_RESULT.ToDouble())
								    || (sMAX.ToDouble() < sDISP_RESULT.ToDouble()))
    								{
	    								if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
		    						} else if(iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
			    					break;
				    			case 2:
					    			if( sDISP_RESULT.ToDouble() > sMAX.ToDouble())
						    		{
							    		if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
								    } else if(iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
    								break;
	    						case 3:
		    						if( sDISP_RESULT.ToDouble() < sMIN.ToDouble())
			    					{
				    					if(iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
					    			} else if(iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
						    		break;
							    }
                                break;
	    					case 2:
		    					if((sMIN.ToDouble() > sDISP_RESULT.ToDouble())
			    				|| (sMAX.ToDouble() < sDISP_RESULT.ToDouble()))
				    			{
					    			if(iDISP_JUDGE != -1) iDISP_JUDGE = 1;
						    	} else if(iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
                                break;
    						}
	    				}
                        else
                        {
                            iDISP_JUDGE = -1;
                        }
                        break;
			    	case 2:
                    	if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].RESULT).Trim().Length() != 0)
                        {
                    	    if((AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].RESULT).ToIntDef(0)) != 0)
					        {
						        if( iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
    					    }
                            else
                            {
                                if( iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
                            }
                        }
                        else
                        {
                            iSOKU_JUDGE = -1;
                        }
                    	if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].DISP_RESULT).Trim().Length() != 0)
                        {
                    	    if((AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].DISP_RESULT).ToIntDef(0)) != 0)
		    			    {
			    			    if( iDISP_JUDGE != -1 ) iDISP_JUDGE = 1;
                            }
                            else
                            {
                                if( iDISP_JUDGE == 2 ) iDISP_JUDGE = 0;
                            }
				    	}
                        else
                        {
                            iDISP_JUDGE = -1;
                        }
                        break;
                    case 3:                     //文字入力
                        if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].RESULT).Trim().Length() ==0)
                        {
                            iSOKU_JUDGE = -1;
                        }
                        if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].DISP_RESULT).Trim().Length() ==0)
                        {
                            iDISP_JUDGE = -1;
                        }
                        break;
    				default:
	    				break;
		    		}
                }
			}
            strcpy(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].SOKU_OK,AnsiString(iSOKU_JUDGE).c_str());
            strcpy(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+iRow].DISP_OK,AnsiString(iDISP_JUDGE).c_str());
            strcpy(pRIRE_KSD01_DATA[ACol].SOZAI_OK		,AnsiString(iSOKU_JUDGE).c_str());
        	strcpy(pRIRE_KSD01_DATA[ACol].SOZAI_OK_PRT	,AnsiString(iDISP_JUDGE).c_str());
		}
 		break;
	default:
		break;
	}
    //結果を画面上に反映します
    if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD)
	{
		iJudge = iSOKU_JUDGE;
	}
    else
	{
		iJudge = iDISP_JUDGE;
	}
	switch( iJudge )
	{
    case -1:
        sBuf = "測定中";
        break;
    case 0:
		sBuf = "OK";
		break;
	case 1:
		sBuf = "NG";
		break;
	case 2:
    default:
		sBuf = "";
		break;
	}
	bHANTEI_DISP = true;
	switch( iGridTag )
	{
    case 1:
		pCELLINFO_SOKU_SYUKA[ACol*iRowCount+0].JUDGE        = iSOKU_JUDGE;
		pCELLINFO_SOKU_SYUKA[ACol*iRowCount+0].DISP_JUDGE   = iDISP_JUDGE;
		SGr_vSOKU_SYUKA->Cells[ACol][0] = sBuf;
		break;
    case 2:
		pCELLINFO_RIRE_SYUKA[ACol*iRowCount+0].JUDGE        = iSOKU_JUDGE;
		pCELLINFO_RIRE_SYUKA[ACol*iRowCount+0].DISP_JUDGE   = iDISP_JUDGE;
		SGr_vRIRE_SYUKA->Cells[ACol][0] = sBuf;
		break;
    case 3:
		pCELLINFO_SOKU_SOZAI[ACol*iRowCount+0].JUDGE        = iSOKU_JUDGE;
		pCELLINFO_SOKU_SOZAI[ACol*iRowCount+0].DISP_JUDGE   = iDISP_JUDGE;
		SGr_vSOKU_SOZAI->Cells[ACol][0] = sBuf;
		break;
    case 4:
		pCELLINFO_RIRE_SOZAI[ACol*iRowCount+0].JUDGE        = iSOKU_JUDGE;
		pCELLINFO_RIRE_SOZAI[ACol*iRowCount+0].DISP_JUDGE   = iDISP_JUDGE;
		SGr_vRIRE_SOZAI->Cells[ACol][0] = sBuf;
		break;
    }
	bHANTEI_DISP = false;
}
//---------------------------------------------------------------------------
//
//  概要
//    OnDrawCellイベント	：４分割グリッドの描画処理を行います。
//
//  機能説明
//    表示するセルを指示された桁数、形式で表示し、エラー等の判断を色を変えて表現します。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int ACol          ：対象セルのカラム位置
//    int ARow          ：対象セルのＲＯＷ位置
//  　TRect &Rect       ：セルの位置情報
//  　TGridDrawState State  : セルのステータス（フォーカスの有無等）
//  戻り値
//    なし。
//
//  備考
//    ４つのグリッドに処理は分かれていますが、参照メモリの位置などが違うだけで内容は同じです。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::AllGRID_DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
	if(iDEBUG == 1) return;
	AnsiString asString,sBuf,sBuf2;
	RECT r=RECT(Rect);
	int i1;
	int iGridTag;
	AnsiString	sDeci1,sDeci2;
	double dMAX,dMIN;
	AnsiString sTemp;
	int iKIKA_KIND;			//1：上下限判定、2：以下、3：以上
	bool bRtn;	 			//2003.05.08 E.Takase Add
	double dBuf;	 		//2003.05.08 E.Takase Add
	AnsiString sComp1,sComp2,sTempComp;	//表示値と印刷値を比較するバッファ

    //メモリがあるかを判断します
	if(Sender == SGr_vSOKU_SYUKA)
	{
		iGridTag = 1;
		asString = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
		SGr_vSOKU_SYUKA->Canvas->Font->Size = 12;
		if(!hCELLINFO_SOKU_SYUKA) return;
	}
	if(Sender == SGr_vRIRE_SYUKA)
	{
		iGridTag = 2;
		asString = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
		SGr_vRIRE_SYUKA->Canvas->Font->Size = 12;
		if(!hCELLINFO_RIRE_SYUKA) return;
	}
	if(Sender == SGr_vSOKU_SOZAI)
	{
		iGridTag = 3;
		asString = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
		SGr_vSOKU_SOZAI->Canvas->Font->Size = 12;
		if(!hCELLINFO_SOKU_SOZAI) return;
	}
	if(Sender == SGr_vRIRE_SOZAI)
	{
		iGridTag = 4;
		asString = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
		SGr_vRIRE_SOZAI->Canvas->Font->Size = 12;
		if(!hCELLINFO_RIRE_SOZAI) return;
	}
	//固定セルの背景色をセット
	if(State.Contains(gdFixed))
	{
	}
	else if(asString == "不要")
	{
		switch( iGridTag )
		{
		case 1:
			SGr_vSOKU_SYUKA->Canvas->Brush->Color= clGray;
			break;
		case 2:
			SGr_vRIRE_SYUKA->Canvas->Brush->Color= clGray;
			break;
		case 3:
			SGr_vSOKU_SOZAI->Canvas->Brush->Color= clGray;
			break;
		case 4:
			SGr_vRIRE_SOZAI->Canvas->Brush->Color= clGray;
			break;
		default:
			break;
		}
	}
	//フォーカスのあるセルの背景色をセット
	else if(State.Contains(gdFocused))
	{
		switch( iGridTag )
		{
		case 1:
			SGr_vSOKU_SYUKA->Canvas->Brush->Color= clHighlight;
			break;
		case 2:
			SGr_vRIRE_SYUKA->Canvas->Brush->Color= clHighlight;
			break;
		case 3:
			SGr_vSOKU_SOZAI->Canvas->Brush->Color= clHighlight;
			break;
		case 4:
			SGr_vRIRE_SOZAI->Canvas->Brush->Color= clHighlight;
			break;
		default:
			break;
		}
	}
	//普通のセルの背景色をセット
	else
	{
		switch( iGridTag )
		{
		case 1:
			SGr_vSOKU_SYUKA->Canvas->Brush->Color= SGr_vSOKU_SYUKA->Color;
			break;
		case 2:
			SGr_vRIRE_SYUKA->Canvas->Brush->Color= SGr_vRIRE_SYUKA->Color;
			break;
		case 3:
			SGr_vSOKU_SOZAI->Canvas->Brush->Color= SGr_vSOKU_SOZAI->Color;
			break;
		case 4:
			SGr_vRIRE_SOZAI->Canvas->Brush->Color= SGr_vRIRE_SOZAI->Color;
			break;
		default:
			break;
		}
	}
    if( ARow == 0 )
    {
    // １行目は、「判定」
        switch( iGridTag )
        {
        case 1:
            SGr_vSOKU_SYUKA->Canvas->Brush->Color= (TColor)0x00FFDCB9;
            break;
        case 2:
            SGr_vRIRE_SYUKA->Canvas->Brush->Color= (TColor)0x00FFDCB9;
            break;
        case 3:
            SGr_vSOKU_SOZAI->Canvas->Brush->Color= (TColor)0x0080FFFF;
            break;
        case 4:
            SGr_vRIRE_SOZAI->Canvas->Brush->Color= (TColor)0x0080FFFF;
            break;
        default:
            break;
        }
        switch( iGridTag )
        {
        case 1:
            if(asString == "NG" )
            {
                SGr_vSOKU_SYUKA->Canvas->Font->Color = clRed;
            }
            else
            {
                SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;
            }
            SGr_vSOKU_SYUKA->Canvas->FillRect(Rect);
            sBuf = asString;
            InflateRect(&r,-2,-2);
            DrawText(SGr_vSOKU_SYUKA->Canvas->Handle,sBuf.c_str(),-1,&r,DT_CENTER); //中央？
            break;
        case 2:
            if(asString == "NG" )
            {
                SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
            }
            else
            {
                SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
            }
            SGr_vRIRE_SYUKA->Canvas->FillRect(Rect);
            sBuf = asString;
            InflateRect(&r,-2,-2);
            DrawText(SGr_vRIRE_SYUKA->Canvas->Handle,sBuf.c_str(),-1,&r,DT_CENTER); //中央？
            break;
        case 3:
            if(asString == "NG" )
            {
                SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
            }
            else
            {
                SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
            }
            SGr_vSOKU_SOZAI->Canvas->FillRect(Rect);
            sBuf = asString;
            InflateRect(&r,-2,-2);
            DrawText(SGr_vSOKU_SOZAI->Canvas->Handle,sBuf.c_str(),-1,&r,DT_CENTER); //中央？
            break;
        case 4:
            if(asString == "NG" )
            {
                SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
            }
            else
            {
                SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
            }
            SGr_vRIRE_SOZAI->Canvas->FillRect(Rect);
            sBuf = asString;
            InflateRect(&r,-2,-2);
            DrawText(SGr_vRIRE_SOZAI->Canvas->Handle,sBuf.c_str(),-1,&r,DT_CENTER); //中央？
            break;
        default:
            break;
        }
        return;
    }
/////////////////////////////////////////////////////////////////////
//以下は測定項目の表示についてのコードです
	switch( iGridTag )
	{
	case 1:
	//配列が取れていないので描画を中止します
		if(!hCELLINFO_SOKU_SYUKA) return;
		break;
	case 2:
	//配列が取れていないので描画を中止します
		if(!hCELLINFO_RIRE_SYUKA) return;
		break;
	case 3:
	//配列が取れていないので描画を中止します
		if(!hCELLINFO_SOKU_SOZAI) return;
		break;
	case 4:
	//配列が取れていないので描画を中止します
		if(!hCELLINFO_RIRE_SOZAI) return;
		break;
	}
	//日付の表示を行います
    //測定画面かを調べます
	if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD)
	{
        //測定画面なので測定画面の測定日を表示します
		switch( iGridTag )
		{
		case 1:
			if(!hSOKU_KSD01_DATA) break;
			sBuf 	= AnsiString(pSOKU_KSD01_DATA[ACol].SKTYMD);
			SGr_tSOKU_SYUKA->Cells[ACol][0] = sBuf;
			break;
		case 2:
			if(!hRIRE_KSD01_DATA) break;
			if(Form1->iRIRE_CNT == 0) break;                      
			//**** 2003/05/15　ここがあやしい「メモリ読み込みエラー」たまに発生
			sBuf	= AnsiString(pRIRE_KSD01_DATA[ACol].SKTYMD);
			SGr_tRIRE_SYUKA->Cells[ACol][0] = sBuf;
			break;
		case 3:

			if(!hSOKU_KSD01_DATA) break;
			sBuf	= AnsiString(pSOKU_KSD01_DATA[ACol].SKTYMD_SZ);
			SGr_tSOKU_SOZAI->Cells[ACol][0] = sBuf;
			break;
		case 4:
			//if(!hRIRE_KSD01_DATA) break;
			if(Form1->iRIRE_CNT == 0) break;
			sBuf	= AnsiString(pRIRE_KSD01_DATA[ACol].SKTYMD_SZ);
			SGr_tRIRE_SOZAI->Cells[ACol][0] = sBuf;
			break;
		}
	}
	else
	{
        //印刷編集画面なので印刷用の測定日を表示します
		switch( iGridTag )
		{
		case 1:
			if(!hSOKU_KSD01_DATA) break;
			sBuf 	= AnsiString(pSOKU_KSD01_DATA[ACol].SKTYMD_PRT);
			SGr_tSOKU_SYUKA->Cells[ACol][0] = sBuf;
			break;
		case 2:
			if(!hRIRE_KSD01_DATA) break;
			sBuf	= AnsiString(pRIRE_KSD01_DATA[ACol].SKTYMD_PRT);
			SGr_tRIRE_SYUKA->Cells[ACol][0] = sBuf;
			break;
		case 3:
			if(!hSOKU_KSD01_DATA) break;
			sBuf	= AnsiString(pSOKU_KSD01_DATA[ACol].SKTYMD_SZ_PRT);
			SGr_tSOKU_SOZAI->Cells[ACol][0] = sBuf;
			break;
		case 4:
			if(!hRIRE_KSD01_DATA) break;
			sBuf	= AnsiString(pRIRE_KSD01_DATA[ACol].SKTYMD_SZ_PRT);
			SGr_tRIRE_SOZAI->Cells[ACol][0] = sBuf;
			break;
		}
	}

	switch( iGridTag )
	{
	//出荷測定画面
	case 1:
		if(!hCELLINFO_SOKU_SYUKA) return;
		// 2003/06/02 K.Yamada 対象セルが無い時は、処理を中止します
		if( SGr_vSOKU_SYUKA->RowCount == 1 ) return;
	//背景色で消去
		SGr_vSOKU_SYUKA->Canvas->FillRect(Rect);
	//固定セルの立体枠を描く
		if(SGr_vSOKU_SYUKA->Ctl3D&&State.Contains(gdFixed))
		{
			DrawEdge(SGr_vSOKU_SYUKA->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);
		}
	//フォーカスのあるセルの文字色をセット
		if(State.Contains(gdFocused))
		{
			SGr_vSOKU_SYUKA->Canvas->Font->Color= clHighlightText;
			SGr_vSOKU_SYUKA->Canvas->Font->Color= clBlack;
		}
	//選択されているセルの文字色をセット
		else if(State.Contains(gdSelected))
		{
	//普通のセルの文字色をセット
		}
		else
		{
			SGr_vSOKU_SYUKA->Canvas->Font->Color= SGr_vSOKU_SYUKA->Font->Color;
		}
		if(asString == "不要")
		{
			SGr_vSOKU_SYUKA->Canvas->Font->Color= clGray;
		}
		else
		{
			SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;
		}

		if(Form1->SGr_tSOKU->Cells[0][0]!="" && hCELLINFO_SOKU_SYUKA != NULL)
		{
            //表示されている画面（測定／印刷用画面）により入力値をメモリから取り出す
			if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
				sBuf = pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount + ARow].RESULT;
			}
			sBuf = pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount + ARow].DISP_RESULT;
			if( hCELLINFO_SOKU_SYUKA )
			{
            //入力が数値の場合、規格を算出する
				if((AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 1)
				|| (AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 2))
				{
					dMAX = pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].MAX;
					dMIN = pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].MIN;
				}
			}
		}
	//以上以下の規格の場合対策
		iKIKA_KIND = 1;		//デフォルトは上下限で判定
		if(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].KIKA_TYPE) == 1)
		{
			if(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].KIKA_KIND) == 2)
			{
				iKIKA_KIND = 2;
			}
			else if(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].KIKA_KIND) == 3)
			{
				iKIKA_KIND = 3;
			}
		}

//フォーマット調整
		if(hCELLINFO_SOKU_SYUKA )
		{
            //文字列が不要ならの処理ですが今は処理そのものが不要です（不要文字列で見なくなった為）
			if(asString == "不要"
			|| AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].RESULT) == "不要")
			{
				sBuf = "不要";
				//セル入力をバッファに取り込む
				strcpy(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].RESULT		,sBuf.c_str());
				strcpy(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].DISP_RESULT,sBuf.c_str());
				pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].JUDGE = 2;
			}
			else
			{
                //整数、少数、角度の場合はフォーマット文字列を作成します
				switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:		//整数・少数
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_SOKU_SYUKA[(ACol*SGr_vSOKU_SYUKA->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( sDeci1.Length() == 1 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 1:		//角度
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_SOKU_SYUKA[(ACol*SGr_vSOKU_SYUKA->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( sDeci1.Length() == 1 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 2:  	//良・否
					break;
				default:	//文字
					break;
				}
				SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;		//判定用色初期値はOKで
				switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:
                    //入力がなければバッファを空にします
					if(AnsiString(SGr_vSOKU_SYUKA->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}
                    //高瀬さんの判定式を使い無効入力でもエラーを出さないようにします。
					//2003.05.08 E.Takase Add↓
					bRtn = ConvDoubleDefS(SGr_vSOKU_SYUKA->Cells[ACol][ARow],sDeci1,SGr_vSOKU_SYUKA->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add↑
					//2003.05.08 E.Takase Add コメント↓
					//try{
					//	sBuf = FormatFloat(sDeci1,SGr_vSOKU_SYUKA->Cells[ACol][ARow].ToDouble());
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
					//}
					//catch(...){
					//	sBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
					//}
					//2003.05.08 E.Takase Add コメント↑

					//セル入力をバッファに取り込む
					if(hCELLINFO_SOKU_SYUKA)
					{
						//印刷用画面以外
						if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_SOKU_SYUKA[ACol*Form1->SGr_vSOKU_SYUKA->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
					//良否判定
					//2003.05.08 E.Takase Add↓
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
                        //以下判定
						case 2:
							if( dBuf <= dMAX  )
							{
								SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vSOKU_SYUKA->Canvas->Font->Color = clRed;
							}
							break;
                        //以上判定
						case 3:
							if( dBuf >= dMIN )
							{
								SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vSOKU_SYUKA->Canvas->Font->Color = clRed;
							}
							break;
                        //範囲判定
						default:
                            /*
							if( ((float)dMAX >= (float)dBuf) &&
                            	((float)dBuf >= (float)dMIN) ) {
								SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;
							}
							else {
								SGr_vSOKU_SYUKA->Canvas->Font->Color = clRed;
							}
                            */
                            // 2003/10/06 A.Tamura なぜか規格内なのに規格外と判定されるのでDouble型を再設定します。
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();
                            if( dBuf <= dMAX && dBuf >= dMIN ){
                            	SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;
                            }
                            else {
                                SGr_vSOKU_SYUKA->Canvas->Font->Color = clRed;
                            }

						}

					} else {
						sBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
					}
					//2003.05.08 E.Takase Add↑
					break;
				case 1:
					if(AnsiString(SGr_vSOKU_SYUKA->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}
					//2003.05.08 E.Takase Add↓
					bRtn = ConvDoubleDefS(SGr_vSOKU_SYUKA->Cells[ACol][ARow],sDeci1,SGr_vSOKU_SYUKA->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add↑
					//2003.05.08 E.Takase Add コメント↓
					//try{
					//	sBuf = FormatFloat(sDeci1,SGr_vSOKU_SYUKA->Cells[ACol][ARow].ToDouble());
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
					//}
					//catch(...){
					//	sBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
					//}
					//2003.05.08 E.Takase Add コメント↑

					//良否判定
					//2003.05.08 E.Takase Add↓
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
                        //以下判定
						case 2:
							if( dBuf <= dMAX )
							{
								SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vSOKU_SYUKA->Canvas->Font->Color = clRed;
							}
							break;
                        //以上判定
						case 3:
							if( dBuf >= dMIN )
							{
								SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vSOKU_SYUKA->Canvas->Font->Color = clRed;
							}
							break;
                        //範囲判定
						default:
                            // 2003/10/06 A.Tamura なぜか規格内なのに規格外と判定されるのでDouble型を再設定します。
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN)
							{
								SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vSOKU_SYUKA->Canvas->Font->Color = clRed;
							}
						}
					} else {
						if(hCELLINFO_SOKU_SYUKA)
						{
							sBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_SOKU_SYUKA[ACol*Form1->SGr_vSOKU_SYUKA->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
					//2003.05.08 E.Takase Add↑

					//セル入力をバッファに取り込む
					if(hCELLINFO_SOKU_SYUKA)
					{
						//印刷用画面で以外
						if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_SOKU_SYUKA[ACol*Form1->SGr_vSOKU_SYUKA->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
					if(sBuf.Trim().Length() != 0)
					{
						i1 = strcspn(sBuf.c_str(),".");
						sTemp = sBuf.SubString(1,i1);
						sTemp += "°";
						if(sBuf.SubString(i1+2,sBuf.Length() - i1).Length()!=0)
						{
							sTemp += sBuf.SubString(i1+2,sBuf.Length() - i1);
							sTemp += "'";
						}
						sBuf = sTemp;
					}
					break;
				case 2:
                    //良否判定
					sBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
					sBuf = sBuf.Trim();
					if( sBuf == 0 || sBuf == "良")
					{
						sBuf ="良";
					}
					else if( sBuf.Length() != 0)
					{
						sBuf = "否";
					}
                    //印刷用画面以外
                    if(SGr_vSOKU_SYUKA->Color != 0x00DDDDDD){
                        sBuf = sBuf.SubString(1,14);
                        if( sBuf.Length() == 14 ){
                            if ( sBuf.ByteType( 14 ) == mbLeadByte ){
                                sBuf = sBuf.SubString(1,13);
                            }
                        }
					    if( sBuf == 0 || sBuf == "良")
					    {
                            strcpy(pCELLINFO_SOKU_SYUKA[ACol*Form1->SGr_vSOKU_SYUKA->RowCount+ARow].RESULT,"0");
                        }
                        else if( sBuf.Length() != 0 )
					    {
                            strcpy(pCELLINFO_SOKU_SYUKA[ACol*Form1->SGr_vSOKU_SYUKA->RowCount+ARow].RESULT,"1");
                        }
                        else
                        {
                            strcpy(pCELLINFO_SOKU_SYUKA[ACol*Form1->SGr_vSOKU_SYUKA->RowCount+ARow].RESULT,"");
                        }
                    }
					if( sBuf == "否" )
					{
						SGr_vSOKU_SYUKA->Canvas->Font->Color = clRed;
					}
					else
					{
						SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;
					}
					break;
				default:
                    //文字列判定
					sBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
					SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;
					//セル入力をバッファに取り込む
					if(hCELLINFO_SOKU_SYUKA)
					{
						//印刷用画面でなければ
						if(SGr_vSOKU_SYUKA->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_SOKU_SYUKA[ACol*Form1->SGr_vSOKU_SYUKA->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
				}
			}
		}
		else
		{
			sBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
		}
    //選択中はハイライト表示
   		if(State.Contains(gdFocused)
		&& SGr_vSOKU_SYUKA->Canvas->Font->Color != clRed
		&& SGr_vSOKU_SYUKA->Canvas->Font->Color != clGray)
		{
			SGr_vSOKU_SYUKA->Canvas->Font->Color= clHighlightText;
   		}
    //印刷編集画面はカラーを変更する
		if(SGr_vSOKU_SYUKA->Color == 0x00DDDDDD)
		{
            //表示する際のカラーを設定します
            //測定用カラー
            //ＮＧ：clRed、ＯＫ：clBlack
            //印刷用カラー
            //測定用と印刷用の値が同じ場合：  ＮＧ：clRed、ＯＫ：clBlack
            //測定用と印刷用の値が違う場合：　ＮＧ：clMaroon、ＯＫ：clBlue
			switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*Form1->SGr_vSOKU_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
			{
			case 0:
			case 1:
			case 2:
				try{
				sComp1 = AnsiString(pCELLINFO_SOKU_SYUKA[ACol*Form1->SGr_vSOKU_SYUKA->RowCount+ARow].RESULT);
				sComp2 = AnsiString(pCELLINFO_SOKU_SYUKA[ACol*Form1->SGr_vSOKU_SYUKA->RowCount+ARow].DISP_RESULT);
				sTempComp = sComp1;
				bRtn = ConvDoubleDefS(sTempComp,sDeci1,sTempComp,&sComp1);
				sTempComp = sComp2;
				bRtn = ConvDoubleDefS(sTempComp,sDeci1,sTempComp,&sComp2);
				if( sComp1 != sComp2)
				{
					if(SGr_vSOKU_SYUKA->Canvas->Font->Color == clRed)
					{
						SGr_vSOKU_SYUKA->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vSOKU_SYUKA->Canvas->Font->Color= clBlue;
					}
				}
				else
				{
					if(SGr_vSOKU_SYUKA->Canvas->Font->Color == clRed)
					{
 						SGr_vSOKU_SYUKA->Canvas->Font->Color= clRed;
					}
					else
					{
						SGr_vSOKU_SYUKA->Canvas->Font->Color= clGray;
					}
				}
				}
				catch(EConvertError& e){
					if(SGr_vSOKU_SYUKA->Canvas->Font->Color == clRed)
					{
						SGr_vSOKU_SYUKA->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vSOKU_SYUKA->Canvas->Font->Color= clBlue;
					}
				}
				catch(...){
					if(SGr_vSOKU_SYUKA->Canvas->Font->Color == clRed)
					{
						SGr_vSOKU_SYUKA->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vSOKU_SYUKA->Canvas->Font->Color= clBlue;
					}
				}
				break;
			default:
				if(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*Form1->SGr_vSOKU_SYUKA->RowCount+ARow].RESULT).Trim()
		 		!= AnsiString(pCELLINFO_SOKU_SYUKA[ACol*Form1->SGr_vSOKU_SYUKA->RowCount+ARow].DISP_RESULT).Trim())
				{
					if(SGr_vSOKU_SYUKA->Canvas->Font->Color == clRed)
					{
						SGr_vSOKU_SYUKA->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vSOKU_SYUKA->Canvas->Font->Color= clBlue;
					}
				}
				else
				{
					if(SGr_vSOKU_SYUKA->Canvas->Font->Color == clRed)
					{
 						SGr_vSOKU_SYUKA->Canvas->Font->Color= clRed;
					}
					else
					{
						SGr_vSOKU_SYUKA->Canvas->Font->Color= clGray;
					}
				}
				break;
			}
   			if(State.Contains(gdFocused))
			{
				SGr_vSOKU_SYUKA->Canvas->Font->Color= clHighlightText;
   			}
		}

        //測定中のロットは処理をしない
//		if( AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].KOMK_NO).ToIntDef(0) == 0
		if( pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].INS_ON == false
		||  AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].SOKU_FLG).ToIntDef(0) == 0)
		{
			SGr_vSOKU_SYUKA->Canvas->Font->Color= clGray;
			SGr_vSOKU_SYUKA->Canvas->Brush->Color= clGray;
		}
		SGr_vSOKU_SYUKA->Canvas->FillRect(Rect);
		InflateRect(&r,-2,-2);
    //出力タイプによるフォーマット位置調整
		switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
		{
		case 0:		//整数・少数
		case 1:		//角度
			DrawText(SGr_vSOKU_SYUKA->Canvas->Handle,sBuf.c_str(),-1,&r,DT_RIGHT); //右寄せ
			break;
		case 2:  	//良・否
			DrawText(SGr_vSOKU_SYUKA->Canvas->Handle,sBuf.c_str(),-1,&r,DT_CENTER); //中央寄せ
			break;
		default:	//文字
			DrawText(SGr_vSOKU_SYUKA->Canvas->Handle,sBuf.c_str(),-1,&r,DT_LEFT); //左寄せ
			break;
		}
    //現在は不要な処理です（心配だからコメントにしませんが、消して戴いても問題は無いです
    //色による判定
		if(hCELLINFO_SOKU_SYUKA)
		{
			if(SGr_vSOKU_SYUKA->Color != 0x00DDDDDD)
			{
				switch(SGr_vSOKU_SYUKA->Canvas->Font->Color)
				{
				case clBlack:
					pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].JUDGE = 0;
					break;
				case clRed:
					pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].JUDGE = 1;
					break;
				default:
					pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].JUDGE = 2;
					break;
				}
			}
			else
			{
				switch(SGr_vSOKU_SYUKA->Canvas->Font->Color)
				{
				case clBlue:
				//規格判定がいります
					pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].JUDGE = 0;
					break;
				case clGray:
					pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].JUDGE = 0;
					break;
				case clRed:
					pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].JUDGE = 1;
					break;
				case clMaroon:
					pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].JUDGE = 1;
					break;
				default:
					pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].JUDGE = 2;
					break;
				}
			}
			if(sBuf.Trim().Length() == 0) pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].JUDGE = 2;
		}
		break;
    //以降Case2、3、4（出荷検査履歴、素材検査出荷、素材検査履歴）も処理内容は同じです
   case 2:
		if(!hCELLINFO_RIRE_SYUKA) return;
		// 2003/06/02 K.Yamada 対象セルが無い時は、処理を中止します
		if( SGr_vRIRE_SYUKA->RowCount == 1 ) return;
	//背景色で消去
		SGr_vRIRE_SYUKA->Canvas->FillRect(Rect);
	//固定セルの立体枠を描く
		if(SGr_vRIRE_SYUKA->Ctl3D&&State.Contains(gdFixed))
		{
	   		DrawEdge(SGr_vRIRE_SYUKA->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);
   		}
   //フォーカスのあるセルの文字色をセット
   		if(State.Contains(gdFocused))
		{
			SGr_vRIRE_SYUKA->Canvas->Font->Color= clHighlightText;
			SGr_vRIRE_SYUKA->Canvas->Font->Color= clBlack;
   		}
   //選択されているセルの文字色をセット
   		else if(State.Contains(gdSelected))
		{
   //普通のセルの文字色をセット
   		}
   		else
		{
	   		SGr_vRIRE_SYUKA->Canvas->Font->Color= SGr_vRIRE_SYUKA->Font->Color;
   		}
		if(asString == "不要")
		{
			SGr_vRIRE_SYUKA->Canvas->Font->Color= clGray;
		}
		else
		{
			SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
		}

		if(Form1->SGr_tRIRE->Cells[0][0]!="" && hCELLINFO_RIRE_SYUKA != NULL)
		{
			if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
				sBuf = pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount + ARow].RESULT;
			}
			sBuf = pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount + ARow].DISP_RESULT;
			if( hCELLINFO_RIRE_SYUKA )
			{
//入力が数値の場合、規格を算出する
				if((AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 1)
				|| (AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 2))
				{
					dMAX = pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].MAX;
					dMIN = pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].MIN;
				}
			}
		}

	//以上以下の規格の場合対策
		iKIKA_KIND = 1;		//デフォルトは上下限で判定
		if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].KIKA_TYPE) == 1)
		{
			if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].KIKA_KIND) == 2)
			{
				iKIKA_KIND = 2;
			}
			else if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].KIKA_KIND) == 3)
			{
				iKIKA_KIND = 3;
			}
		}
//フォーマット調整
		if(hCELLINFO_RIRE_SYUKA )
		{
			if(asString == "不要"
			|| AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].RESULT) == "不要")
			{
				sBuf = "不要";
				//セル入力をバッファに取り込む
				strcpy(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].RESULT		,sBuf.c_str());
				strcpy(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].DISP_RESULT,sBuf.c_str());
				pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].JUDGE = 2;
			}
			else
			{
				switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:		//整数・少数
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_RIRE_SYUKA[(ACol*SGr_vRIRE_SYUKA->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( sDeci1.Length() == 1 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 1:		//角度
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_RIRE_SYUKA[(ACol*SGr_vRIRE_SYUKA->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( sDeci1.Length() == 1 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 2:  	//良・否
					break;
				default:	//文字
					break;
				}
				SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;		//判定用色初期値はOKで
				switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:
					if(AnsiString(SGr_vRIRE_SYUKA->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}
					//2003.05.08 E.Takase Add↓
					bRtn = ConvDoubleDefS(SGr_vRIRE_SYUKA->Cells[ACol][ARow],sDeci1,SGr_vRIRE_SYUKA->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add↑
					//2003.05.08 E.Takase Add コメント↓
					//try{
					//	sBuf = FormatFloat(sDeci1,SGr_vRIRE_SYUKA->Cells[ACol][ARow].ToDouble());
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
					//}
					//catch(...){
					//	sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
					//}
					//2003.05.08 E.Takase Add コメント↑
					//セル入力をバッファに取り込む
					if(hCELLINFO_RIRE_SYUKA)
					{
						//印刷用画面で以外
						if(SGr_vRIRE_SYUKA->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
					//良否判定
					//2003.05.08 E.Takase Add↓
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
						case 2:
							if( dBuf <= dMAX )
							{
								SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
							}
							break;
						case 3:
							if( dBuf >= dMIN )
							{
								SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
							}
							break;
						default:
                            // 2003/10/06 A.Tamura なぜか規格内なのに規格外と判定されるのでDouble型を再設定します。
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN)
							{
								SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
							}
						}
					} else {
						sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
					}
					//2003.05.08 E.Takase Add↑
					//2003.05.08 E.Takase Add コメント↓
					//try{
					//	switch( iKIKA_KIND )
					//	{
					//	case 2:
					//		if( sBuf.ToDouble() <= dMAX )
					//		{
					//			SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
					//		}
					//		break;
					//	case 3:
					//		if( sBuf.ToDouble() >= dMIN )
					//		{
					//			SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
					//		}
					//		break;
					//	default:
					//		if( sBuf.ToDouble() <= dMAX && sBuf.ToDouble() >= dMIN)
					//		{
					//			SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
					//		}
					//	}
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
					//}
					//catch(...){
					//	sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
					//}
					//2003.05.08 E.Takase Add コメント↑
					break;
				case 1:
					if(AnsiString(SGr_vRIRE_SYUKA->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}

					//2003.05.08 E.Takase Add↓
					bRtn = ConvDoubleDefS(SGr_vRIRE_SYUKA->Cells[ACol][ARow],sDeci1,SGr_vRIRE_SYUKA->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add↑
					//2003.05.08 E.Takase Add コメント↓
					//try{
					//	sBuf = FormatFloat(sDeci1,SGr_vRIRE_SYUKA->Cells[ACol][ARow].ToDouble());
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
					//}
					//catch(...){
					//	sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
					//}
					//2003.05.08 E.Takase Add コメント↑
					//良否判定
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
						case 2:
							if( dBuf <= dMAX )
							{
								SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
							}
							break;
						case 3:
							if( dBuf >= dMIN )
							{
								SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
							}
							break;
						default:
                            // 2003/10/06 A.Tamura なぜか規格内なのに規格外と判定されるのでDouble型を再設定します。
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

                            // 2003/10/06 A.Tamura なんでこんなコードなの？　元にもどす
							// if( dBuf <= dMAX && sBuf.ToDouble() >= dMIN)
							if( dBuf <= dMAX && dBuf >= dMIN)
							{
								SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
							}
						}

					} else {
						sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
						if(hCELLINFO_RIRE_SYUKA)
						{
						//印刷用画面で以外
							if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
								sBuf = sBuf.SubString(1,14);
								if( sBuf.Length() == 14 ){
									if ( sBuf.ByteType( 14 ) == mbLeadByte ){
										sBuf = sBuf.SubString(1,13);
									}
								}
								strcpy(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].RESULT,sBuf.c_str());
							}
						}
					}
					//2003.05.08 E.Takase Add↑
					//2003.05.08 E.Takase Add コメント↓
					//try{
					//	switch( iKIKA_KIND )
					//	{
					//	case 2:
					//		if( sBuf.ToDouble() <= dMAX )
					//		{
					//			SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
					//		}
					//		break;
					//	case 3:
					//		if( sBuf.ToDouble() >= dMIN )
					//		{
					//			SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
					//		}
					//		break;
					//	default:
					//		if( sBuf.ToDouble() <= dMAX && sBuf.ToDouble() >= dMIN)
					//		{
					//			SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
					//		}
					//	}
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
					//	if(hCELLINFO_RIRE_SYUKA)
					//	{
					//	//印刷用画面で以外
					//		if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
					//			strcpy(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].RESULT,sBuf.c_str());
					//		}
					//	}
					//	break;
					//}
					//catch(...){
					//	sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
					//	if(hCELLINFO_RIRE_SYUKA)
					//	{
					//		//印刷用画面で以外
					//		if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
					//			strcpy(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].RESULT,sBuf.c_str());
					//		}
					//	}
					//	break;
					//}
					//2003.05.08 E.Takase Add コメント↑

					//セル入力をバッファに取り込む
					if(hCELLINFO_RIRE_SYUKA)
					{
						//印刷用画面で以外
						if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
					if(sBuf.Trim().Length() != 0)
					{
						i1 = strcspn(sBuf.c_str(),".");
						sTemp = sBuf.SubString(1,i1);
						sTemp += "°";
						if(sBuf.SubString(i1+2,sBuf.Length() - i1).Length()!=0)
						{
							sTemp += sBuf.SubString(i1+2,sBuf.Length() - i1);
							sTemp += "'";
						}
						sBuf = sTemp;
					}
					break;
				case 2:
					sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
					sBuf = sBuf.Trim();
					if( sBuf == 0 || sBuf == "良")
					{
						sBuf ="良";
					}
					else if( sBuf.Length() != 0)
					{
						sBuf = "否";
					}
					if( sBuf == "否" )
					{
						SGr_vRIRE_SYUKA->Canvas->Font->Color = clRed;
					}
					else
					{
						SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
					}
                    //印刷用画面以外
                    if(SGr_vRIRE_SYUKA->Color != 0x00DDDDDD){
                        sBuf = sBuf.SubString(1,14);
                        if( sBuf.Length() == 14 ){
                            if ( sBuf.ByteType( 14 ) == mbLeadByte ){
                                sBuf = sBuf.SubString(1,13);
                            }
                        }
					    if( sBuf == 0 || sBuf == "良")
					    {
                            strcpy(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].RESULT,"0");
                        }
                        else if(sBuf.Length() != 0)
					    {
                            strcpy(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].RESULT,"1");
                        }
                        else
                        {
                            strcpy(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].RESULT,"");
                        }
                    }
					break;
				default:
					sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
					SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
					//セル入力をバッファに取り込む
					if(hCELLINFO_RIRE_SYUKA)
					{
						//印刷用画面で以外
						if(SGr_vRIRE_SYUKA->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
				}
			}
		}
		else
		{
			sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
		}
		InflateRect(&r,-2,-2);
//選択中はハイライト表示
   		if(State.Contains(gdFocused)
		&& SGr_vRIRE_SYUKA->Canvas->Font->Color != clRed
		&& SGr_vRIRE_SYUKA->Canvas->Font->Color != clGray)
		{
			SGr_vRIRE_SYUKA->Canvas->Font->Color= clHighlightText;
   		}
//印刷編集画面はカラーを変更する
		if(SGr_vRIRE_SYUKA->Color == 0x00DDDDDD)
		{
			switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
			{
			case 0:
			case 1:
			case 2:
				try{
//				if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].RESULT).Trim().ToDouble()
//			 	!= AnsiString(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].DISP_RESULT).Trim().ToDouble())
				sComp1 = AnsiString(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].RESULT);
				sComp2 = AnsiString(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].DISP_RESULT);
				sTempComp = sComp1;
				bRtn = ConvDoubleDefS(sTempComp,sDeci1,sTempComp,&sComp1);
				sTempComp = sComp2;
				bRtn = ConvDoubleDefS(sTempComp,sDeci1,sTempComp,&sComp2);
				if( sComp1 != sComp2)
				{
					if(SGr_vRIRE_SYUKA->Canvas->Font->Color == clRed)
					{
						SGr_vRIRE_SYUKA->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vRIRE_SYUKA->Canvas->Font->Color= clBlue;
					}
				}
				else
				{
					if(SGr_vRIRE_SYUKA->Canvas->Font->Color == clRed)
					{
 						SGr_vRIRE_SYUKA->Canvas->Font->Color= clRed;
					}
					else
					{
						SGr_vRIRE_SYUKA->Canvas->Font->Color= clGray;
					}
				}
				}
				catch(EConvertError& e){
					if(SGr_vRIRE_SYUKA->Canvas->Font->Color == clRed)
					{
						SGr_vRIRE_SYUKA->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vRIRE_SYUKA->Canvas->Font->Color= clBlue;
					}
				}
				catch(...){
					if(SGr_vRIRE_SYUKA->Canvas->Font->Color == clRed)
					{
						SGr_vRIRE_SYUKA->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vRIRE_SYUKA->Canvas->Font->Color= clBlue;
					}
				}
				break;
			default:
				if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].RESULT).Trim()
			 	!= AnsiString(pCELLINFO_RIRE_SYUKA[ACol*Form1->SGr_vRIRE_SYUKA->RowCount+ARow].DISP_RESULT).Trim())
				{
					if(SGr_vRIRE_SYUKA->Canvas->Font->Color == clRed)
					{
						SGr_vRIRE_SYUKA->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vRIRE_SYUKA->Canvas->Font->Color= clBlue;
					}
				}
				else
				{
					if(SGr_vRIRE_SYUKA->Canvas->Font->Color == clRed)
					{
 						SGr_vRIRE_SYUKA->Canvas->Font->Color= clRed;
					}
					else
					{
						SGr_vRIRE_SYUKA->Canvas->Font->Color= clGray;
					}
				}
				break;
			}
		}
	//不要文字？
//		if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].KOMK_NO).ToIntDef(0) == 0
		if(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].INS_ON == false
		|| AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].SOKU_FLG).ToIntDef(0) == 0)
		{
			SGr_vRIRE_SYUKA->Canvas->Font->Color= clGray;
			SGr_vRIRE_SYUKA->Canvas->Brush->Color= clGray;
		}
//出力タイプによるフォーマット位置調整
		SGr_vRIRE_SYUKA->Canvas->FillRect(Rect);
		InflateRect(&r,-2,-2);
		switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
		{
		case 0:		//整数・少数
		case 1:		//角度
			DrawText(SGr_vRIRE_SYUKA->Canvas->Handle,sBuf.c_str(),-1,&r,DT_RIGHT); //右寄せ
			break;
		case 2:  	//良・否
			DrawText(SGr_vRIRE_SYUKA->Canvas->Handle,sBuf.c_str(),-1,&r,DT_CENTER); //中央寄せ
			break;
		default:	//文字
			DrawText(SGr_vRIRE_SYUKA->Canvas->Handle,sBuf.c_str(),-1,&r,DT_LEFT); //左寄せ
			break;
		}
//色による判定
		if(hCELLINFO_RIRE_SYUKA)
		{
			if(SGr_vRIRE_SYUKA->Color != 0x00DDDDDD)
			{
				switch(SGr_vRIRE_SYUKA->Canvas->Font->Color)
				{
				case clBlack:
					pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].JUDGE = 0;
					break;
				case clRed:
					pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].JUDGE = 1;
					break;
				default:
					pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].JUDGE = 2;
					break;
				}
			}
			else
			{
				switch(SGr_vRIRE_SYUKA->Canvas->Font->Color)
				{
				case clBlue:
				//規格判定がいります
					pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].JUDGE = 0;
					break;
				case clGray:
					pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].JUDGE = 0;
					break;
				case clRed:
					pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].JUDGE = 1;
					break;
				case clMaroon:
					pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].JUDGE = 1;
					break;
				default:
					pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].JUDGE = 2;
					break;
				}
			}
			if(sBuf.Trim() == 0) pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].JUDGE = 2;
		}
		break;
//測定素材画面
   case 3:
		if(!hCELLINFO_SOKU_SOZAI) return;
		// 2003/06/02 K.Yamada 対象セルが無い時は、処理を中止します
		if( SGr_vSOKU_SOZAI->RowCount == 1 ) return;
	//背景色で消去
		SGr_vSOKU_SOZAI->Canvas->FillRect(Rect);
	//固定セルの立体枠を描く
		if(SGr_vSOKU_SOZAI->Ctl3D&&State.Contains(gdFixed))
		{
	   		DrawEdge(SGr_vSOKU_SOZAI->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);
   		}
   //フォーカスのあるセルの文字色をセット
   		if(State.Contains(gdFocused))
		{
			SGr_vSOKU_SOZAI->Canvas->Font->Color= clHighlightText;
			SGr_vSOKU_SOZAI->Canvas->Font->Color= clBlack;
   		}
   //選択されているセルの文字色をセット
   		else if(State.Contains(gdSelected))
		{
   //普通のセルの文字色をセット
   		}
   		else
		{
	   		SGr_vSOKU_SOZAI->Canvas->Font->Color= SGr_vSOKU_SOZAI->Font->Color;
   		}
		if(asString == "不要")
		{
			SGr_vSOKU_SOZAI->Canvas->Font->Color= clGray;
		}
		else
		{
			SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
		}

		if(Form1->SGr_tSOKU->Cells[0][0]!="" && hCELLINFO_SOKU_SOZAI != NULL)
		{
			if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD){
				sBuf = pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount + ARow].RESULT;
			}
			sBuf = pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount + ARow].DISP_RESULT;
			if( hCELLINFO_SOKU_SOZAI )
			{
//入力が数値の場合、規格を算出する
				if((AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 1)
				|| (AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 2))
				{
					dMAX = pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].MAX;
					dMIN = pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].MIN;
				}
			}
		}
	//以上以下の規格の場合対策
		iKIKA_KIND = 1;		//デフォルトは上下限で判定
		if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].KIKA_TYPE) == 1)
		{
			if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].KIKA_KIND) == 2)
			{
				iKIKA_KIND = 2;
			}
			else if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].KIKA_KIND) == 3)
			{
				iKIKA_KIND = 3;
			}
		}

//フォーマット調整
		if(hCELLINFO_SOKU_SOZAI )
		{
			if(asString == "不要"
			|| AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].RESULT) == "不要")
			{
				sBuf = "不要";
				//セル入力をバッファに取り込む
				strcpy(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].RESULT		,sBuf.c_str());
				strcpy(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].DISP_RESULT,sBuf.c_str());
				pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].JUDGE = 2;
			}
			else
			{
				switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:		//整数・少数
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_SOKU_SOZAI[(ACol*SGr_vSOKU_SOZAI->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( i1 == 0 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 1:		//角度
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_SOKU_SOZAI[(ACol*SGr_vSOKU_SOZAI->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( i1 == 0 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 2:  	//良・否
					break;
				default:	//文字
					break;
				}
				SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;		//判定用色初期値はOKで
				switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:
					if(AnsiString(SGr_vSOKU_SOZAI->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}
					//2003.05.08 E.Takase Add↓
					bRtn = ConvDoubleDefS(SGr_vSOKU_SOZAI->Cells[ACol][ARow],sDeci1,SGr_vSOKU_SOZAI->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add↑
					//2003.05.08 E.Takase Add コメント↓
					//try{
					//	sBuf = FormatFloat(sDeci1,SGr_vSOKU_SOZAI->Cells[ACol][ARow].ToDouble());
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
					//}
					//catch(...){
					//	sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
					//}
					//2003.05.08 E.Takase Add コメント↑
					//セル入力をバッファに取り込む
					if(hCELLINFO_SOKU_SOZAI)
					{
						//印刷用画面で以外
						if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
					//良否判定
					//2003.05.08 E.Takase Add↓
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
						case 2:
							if( dBuf <= dMAX )
							{
								SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
							}
							break;
						case 3:
							if( dBuf >= dMIN )
							{
								SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
							}
							break;
						default:
                            // 2003/10/06 A.Tamura なぜか規格内なのに規格外と判定されるのでDouble型を再設定します。
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN)
							{
								SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
							}
						}
					} else {
						sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
					}
					//2003.05.08 E.Takase Add↑
					//2003.05.08 E.Takase Add コメント↓
					//try{
					//	switch( iKIKA_KIND )
					//	{
					//	case 2:
					//		if( sBuf.ToDouble() <= dMAX )
					//		{
					//			SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
					//		}
					//		break;
					//	case 3:
					//		if( sBuf.ToDouble() >= dMIN )
					//		{
					//			SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
					//		}
					//		break;
					//	default:
					//		if( sBuf.ToDouble() <= dMAX && sBuf.ToDouble() >= dMIN)
					//		{
					//			SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
					//		}
					//	}
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
					//}
					//catch(...){
					//	sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
					//}
					//2003.05.08 E.Takase Add コメント↑
					break;
				case 1:
					if(AnsiString(SGr_vSOKU_SOZAI->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}
					//2003.05.08 E.Takase Add↓
					bRtn = ConvDoubleDefS(SGr_vSOKU_SOZAI->Cells[ACol][ARow],sDeci1,SGr_vSOKU_SOZAI->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add↑
					//2003.05.08 E.Takase Add コメント↓
					//try{
					//	sBuf = FormatFloat(sDeci1,SGr_vSOKU_SOZAI->Cells[ACol][ARow].ToDouble());
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
					//}
					//catch(...){
					//	sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
					//}
					//2003.05.08 E.Takase Add コメント↑

					//良否判定
					//2003.05.08 E.Takase Add↓
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
						case 2:
							if( dBuf <= dMAX )
							{
								SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
							}
							break;
						case 3:
							if( dBuf >= dMIN )
							{
								SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
							}
							break;
						default:
                            // 2003/10/06 A.Tamura なぜか規格内なのに規格外と判定されるのでDouble型を再設定します。
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN)
							{
								SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
							}
						}
					} else {
						sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
						//印刷用画面で以外
						if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
					//2003.05.08 E.Takase Add↑
					//2003.05.08 E.Takase Add コメント↓
					//try{
					//	switch( iKIKA_KIND )
					//	{
					//	case 2:
					//		if( sBuf.ToDouble() <= dMAX )
					//		{
					//			SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
					//		}
					//		break;
					//	case 3:
					//		if( sBuf.ToDouble() >= dMIN )
					//		{
					//			SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
					//		}
					//		break;
					//	default:
					//		if( sBuf.ToDouble() <= dMAX && sBuf.ToDouble() >= dMIN)
					//		{
					//			SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
					//		}
					//	}
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
					//	//印刷用画面で以外
					//	if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD){
					//		strcpy(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
					//	}
					//	break;
					//}
					//catch(...){
					//	sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
					//	//印刷用画面で以外
					//	if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD){
					//		strcpy(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
					//	}
					//	break;
					//}
					//2003.05.08 E.Takase Add コメント↑

					//セル入力をバッファに取り込む
					if(hCELLINFO_SOKU_SOZAI)
					{
						//印刷用画面で以外
						if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD){
							strcpy(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
					if(sBuf.Trim().Length() != 0)
					{
						i1 = strcspn(sBuf.c_str(),".");
						sTemp = sBuf.SubString(1,i1);
						sTemp += "°";
						if(sBuf.SubString(i1+2,sBuf.Length() - i1).Length()!=0)
						{
							sTemp += sBuf.SubString(i1+2,sBuf.Length() - i1);
							sTemp += "'";
						}
						sBuf = sTemp;
					}
					break;
				case 2:
					sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
					sBuf = sBuf.Trim();
					if( sBuf == 0 || sBuf == "良")
					{
						sBuf ="良";
					}
					else if( sBuf.Length() != 0)
					{
						sBuf = "否";
					}
					if( sBuf == "否" )
					{
						SGr_vSOKU_SOZAI->Canvas->Font->Color = clRed;
					}
					else
					{
						SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
					}
                    //印刷用画面以外
                    if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD){
                        sBuf = sBuf.SubString(1,14);
                        if( sBuf.Length() == 14 ){
                            if ( sBuf.ByteType( 14 ) == mbLeadByte ){
                                sBuf = sBuf.SubString(1,13);
                            }
                        }
					    if( sBuf == 0 || sBuf == "良")
					    {
                            strcpy(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].RESULT,"0");
                        }
                        else if(sBuf.Length() != 0)
					    {
                            strcpy(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].RESULT,"1");
                        }
                        else
					    {
                            strcpy(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].RESULT,"");
                        }
                    }
					break;
				default:
					sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
					SGr_vSOKU_SOZAI->Canvas->Font->Color = clBlack;
					//セル入力をバッファに取り込む
					if(hCELLINFO_SOKU_SOZAI)
					{
						//印刷用画面で以外
						if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
				}
			}
		}
		else
		{
			sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
		}
		InflateRect(&r,-2,-2);
//選択中はハイライト表示
   		if(State.Contains(gdFocused)
		&& SGr_vSOKU_SOZAI->Canvas->Font->Color != clRed
		&& SGr_vSOKU_SOZAI->Canvas->Font->Color != clGray)
		{
			SGr_vSOKU_SOZAI->Canvas->Font->Color= clHighlightText;
   		}
//印刷編集画面はカラーを変更する
		if(SGr_vSOKU_SOZAI->Color == 0x00DDDDDD)
		{
			switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
			{
			case 0:
			case 1:
			case 2:
				try{
//				if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].RESULT).Trim().ToDouble()
//			 	!= AnsiString(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].DISP_RESULT).Trim().ToDouble())
				sComp1 = AnsiString(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].RESULT);
				sComp2 = AnsiString(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].DISP_RESULT);
				sTempComp = sComp1;
				bRtn = ConvDoubleDefS(sTempComp,sDeci1,sTempComp,&sComp1);
				sTempComp = sComp2;
				bRtn = ConvDoubleDefS(sTempComp,sDeci1,sTempComp,&sComp2);
				if( sComp1 != sComp2)
				{
					if(SGr_vSOKU_SOZAI->Canvas->Font->Color == clRed)
					{
						SGr_vSOKU_SOZAI->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vSOKU_SOZAI->Canvas->Font->Color= clBlue;
					}
				}
				else
				{
					if(SGr_vSOKU_SOZAI->Canvas->Font->Color == clRed)
					{
	 					SGr_vSOKU_SOZAI->Canvas->Font->Color= clRed;
					}
					else
					{
						SGr_vSOKU_SOZAI->Canvas->Font->Color= clGray;
					}
				}
				}
				catch(EConvertError& e){
					if(SGr_vSOKU_SOZAI->Canvas->Font->Color == clRed)
					{
						SGr_vSOKU_SOZAI->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vSOKU_SOZAI->Canvas->Font->Color= clBlue;
					}
				}
				catch(...){
					if(SGr_vSOKU_SOZAI->Canvas->Font->Color == clRed)
					{
						SGr_vSOKU_SOZAI->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vSOKU_SOZAI->Canvas->Font->Color= clBlue;
					}
				}
				break;
			default:
				if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].RESULT).Trim()
			 	!= AnsiString(pCELLINFO_SOKU_SOZAI[ACol*Form1->SGr_vSOKU_SOZAI->RowCount+ARow].DISP_RESULT).Trim())
				{
					if(SGr_vSOKU_SOZAI->Canvas->Font->Color == clRed)
					{
						SGr_vSOKU_SOZAI->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vSOKU_SOZAI->Canvas->Font->Color= clBlue;
					}
				}
				else
				{
					if(SGr_vSOKU_SOZAI->Canvas->Font->Color == clRed)
					{
	 					SGr_vSOKU_SOZAI->Canvas->Font->Color= clRed;
					}
					else
					{
						SGr_vSOKU_SOZAI->Canvas->Font->Color= clGray;
					}
				}
				break;
			}
		}
	//不要文字？
//		if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].KOMK_NO).ToIntDef(0) == 0
		if(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].INS_ON == false
		|| AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].SOKU_FLG).ToIntDef(0) == 0)
		{
			SGr_vSOKU_SOZAI->Canvas->Font->Color= clGray;
			SGr_vSOKU_SOZAI->Canvas->Brush->Color= clGray;
		}
		SGr_vSOKU_SOZAI->Canvas->FillRect(Rect);
		InflateRect(&r,-2,-2);
//出力タイプによるフォーマット位置調整
		switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
		{
		case 0:		//整数・少数
		case 1:		//角度
			DrawText(SGr_vSOKU_SOZAI->Canvas->Handle,sBuf.c_str(),-1,&r,DT_RIGHT); //右寄せ
			break;
		case 2:  	//良・否
			DrawText(SGr_vSOKU_SOZAI->Canvas->Handle,sBuf.c_str(),-1,&r,DT_CENTER); //中央寄せ
			break;
		default:	//文字
			DrawText(SGr_vSOKU_SOZAI->Canvas->Handle,sBuf.c_str(),-1,&r,DT_LEFT); //左寄せ
			break;
		}
//色による判定
		if(hCELLINFO_SOKU_SOZAI)
		{
			if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD)
			{
				switch(SGr_vSOKU_SOZAI->Canvas->Font->Color)
				{
				case clBlack:
					pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].JUDGE = 0;
					break;
				case clRed:
					pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].JUDGE = 1;
					break;
				default:
					pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].JUDGE = 2;
					break;
				}
			}
			else
			{
				switch(SGr_vSOKU_SOZAI->Canvas->Font->Color)
				{
				case clBlue:
				//規格判定がいります
					pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].JUDGE = 0;
					break;
				case clGray:
					pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].JUDGE = 0;
					break;
				case clRed:
					pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].JUDGE = 1;
					break;
				case clMaroon:
					pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].JUDGE = 1;
					break;
				default:
					pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].JUDGE = 2;
					break;
				}
	  		}
			if(sBuf.Trim() == 0) pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].JUDGE = 2;
		}
		break;
//履歴素材グリッド
   case 4:
		if(!hCELLINFO_RIRE_SOZAI) return;
		// 2003/06/02 K.Yamada 対象セルが無い時は、処理を中止します
		if( SGr_vRIRE_SOZAI->RowCount == 1 ) return;
	//背景色で消去
		SGr_vRIRE_SOZAI->Canvas->FillRect(Rect);
	//固定セルの立体枠を描く
		if(SGr_vRIRE_SOZAI->Ctl3D&&State.Contains(gdFixed))
		{
	   		DrawEdge(SGr_vRIRE_SOZAI->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);
   		}
   //フォーカスのあるセルの文字色をセット
   		if(State.Contains(gdFocused))
		{
			SGr_vRIRE_SOZAI->Canvas->Font->Color= clHighlightText;
			SGr_vRIRE_SOZAI->Canvas->Font->Color= clBlack;
   		}
   //選択されているセルの文字色をセット
   		else if(State.Contains(gdSelected))
		{
   //普通のセルの文字色をセット
   		}
   		else
		{
	   		SGr_vRIRE_SOZAI->Canvas->Font->Color= SGr_vRIRE_SOZAI->Font->Color;
   		}
		if(asString == "不要")
		{
			SGr_vRIRE_SOZAI->Canvas->Font->Color= clGray;
		}
		else
		{
			SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
		}

		if(Form1->SGr_tRIRE->Cells[0][0]!="" && hCELLINFO_RIRE_SOZAI != NULL)
		{
			if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
				sBuf = pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount + ARow].RESULT;
			}
			sBuf = pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount + ARow].DISP_RESULT;
			if( hCELLINFO_RIRE_SOZAI )
			{
//入力が数値の場合、規格を算出する
				if((AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 1)
				|| (AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 2))
				{
					dMAX = pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].MAX;
					dMIN = pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].MIN;
				}
			}
		}
	//以上以下の規格の場合対策
		iKIKA_KIND = 1;		//デフォルトは上下限で判定
		if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].KIKA_TYPE) == 1)
		{
			if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].KIKA_KIND) == 2)
			{
				iKIKA_KIND = 2;
			}
			else if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].KIKA_KIND) == 3)
			{
				iKIKA_KIND = 3;
			}
		}

//フォーマット調整
		if(hCELLINFO_RIRE_SOZAI )
		{
			if(asString == "不要"
			|| AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].RESULT) == "不要")
			{
				sBuf = "不要";
				//セル入力をバッファに取り込む
				strcpy(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].RESULT		,sBuf.c_str());
				strcpy(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].DISP_RESULT,sBuf.c_str());
				pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].JUDGE = 2;
			}
			else
			{
				switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:		//整数・少数
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_RIRE_SOZAI[(ACol*SGr_vRIRE_SOZAI->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( sDeci1.Length() == 1 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 1:		//角度
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_RIRE_SOZAI[(ACol*SGr_vRIRE_SOZAI->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( sDeci1.Length() == 1 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 2:  	//良・否
					break;
				default:	//文字
					break;
				}
				SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;		//判定用色初期値はOKで
				switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:
					if(AnsiString(SGr_vRIRE_SOZAI->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}
					//2003.05.08 E.Takase Add↓
					bRtn = ConvDoubleDefS(SGr_vRIRE_SOZAI->Cells[ACol][ARow],sDeci1,SGr_vRIRE_SOZAI->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add↑
					//2003.05.08 E.Takase Add コメント↓
					//try{
					//	sBuf = FormatFloat(sDeci1,SGr_vRIRE_SOZAI->Cells[ACol][ARow].ToDouble());
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
					//}
					//catch(...){
					//	sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
					//}
					//2003.05.08 E.Takase Add コメント↑

					//セル入力をバッファに取り込む
					if(hCELLINFO_RIRE_SOZAI)
					{
						//印刷用画面で以外
						if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
					//良否判定
					//2003.05.08 E.Takase Add↓
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);

						switch( iKIKA_KIND )
						{
						case 2:
							if( dBuf <= dMAX )
							{
								SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
							}
							break;
						case 3:
							if( dBuf >= dMIN )
							{
								SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
							}
							break;
						default:
                            // 2003/10/06 A.Tamura なぜか規格内なのに規格外と判定されるのでDouble型を再設定します。
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN)
							{
								SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
							}
						}

					} else {
						sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
					}
					//2003.05.08 E.Takase Add↑
					//2003.05.08 E.Takase Add コメント↓
					//try{
					//	switch( iKIKA_KIND )
					//	{
					//	case 2:
					//		if( sBuf.ToDouble() <= dMAX )
					//		{
					//			SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
					//		}
					//		break;
					//	case 3:
					//		if( sBuf.ToDouble() >= dMIN )
					//		{
					//			SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
					//		}
					//		break;
					//	default:
					//		if( sBuf.ToDouble() <= dMAX && sBuf.ToDouble() >= dMIN)
					//		{
					//			SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
					//		}
					//	}
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
					//}
					//catch(...){
					//	sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
					//}
					//2003.05.08 E.Takase Add コメント↑
					break;
				case 1:
					if(AnsiString(SGr_vRIRE_SOZAI->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}

					//2003.05.08 E.Takase Add↓
					bRtn = ConvDoubleDefS(SGr_vRIRE_SOZAI->Cells[ACol][ARow],sDeci1,SGr_vRIRE_SOZAI->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add↑
					//2003.05.08 E.Takase Add コメント↓
					//try{
					//	sBuf = FormatFloat(sDeci1,SGr_vRIRE_SOZAI->Cells[ACol][ARow].ToDouble());
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
					//}
					//catch(...){
					//	sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
					//}
					//2003.05.08 E.Takase Add コメント↑

					//良否判定
					//2003.05.08 E.Takase Add↓
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
						case 2:
							if( dBuf <= dMAX )
							{
								SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
							}
							break;
						case 3:
							if( dBuf >= dMIN )
							{
								SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
							}
							break;
						default:
                            // 2003/10/06 A.Tamura なぜか規格内なのに規格外と判定されるのでDouble型を再設定します。
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN)
							{
								SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
							}
							else
							{
								SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
							}
						}
					} else {
						sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
						//印刷用画面で以外
						if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
					//2003.05.08 E.Takase Add↑
					//2003.05.08 E.Takase Add コメント↓
					//try{
					//	switch( iKIKA_KIND )
					//	{
					//	case 2:
					//		if( sBuf.ToDouble() <= dMAX )
					//		{
					//			SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
					//		}
					//		break;
					//	case 3:
					//		if( sBuf.ToDouble() >= dMIN )
					//		{
					//			SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
					//		}
					//		break;
					//	default:
					//		if( sBuf.ToDouble() <= dMAX && sBuf.ToDouble() >= dMIN)
					//		{
					//			SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
					//		}
					//		else
					//		{
					//			SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
					//		}
					//	}
					//}
					//catch(EConvertError& e){
					//	sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
					//	//印刷用画面で以外
					//	if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
					//		strcpy(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
					//	}
					//	break;
					//}
					//catch(...){
					//	sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
					//	//印刷用画面で以外
					//	if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
					//		strcpy(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
					//	}
					//	break;
					//}
					//2003.05.08 E.Takase Add コメント↑

					//セル入力をバッファに取り込む
					if(hCELLINFO_SOKU_SOZAI)
					{
						//印刷用画面で以外
						if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
					if(sBuf.Trim().Length() != 0)
					{
						i1 = strcspn(sBuf.c_str(),".");
						sTemp = sBuf.SubString(1,i1);
						sTemp += "°";
						if(sBuf.SubString(i1+2,sBuf.Length() - i1).Length()!=0)
						{
							sTemp += sBuf.SubString(i1+2,sBuf.Length() - i1);
							sTemp += "'";
						}
						sBuf = sTemp;
					}
					break;
				case 2:
					sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
					sBuf = sBuf.Trim();
					if( sBuf == 0 || sBuf == "良")
					{
						sBuf ="良";
					}
					else if( sBuf.Length() != 0)
					{
						sBuf = "否";
					}
					if( sBuf == "否" )
					{
						SGr_vRIRE_SOZAI->Canvas->Font->Color = clRed;
					}
					else
					{
						SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
					}
              //印刷用画面以外
                    if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD)
                    {
                        sBuf = sBuf.SubString(1,14);
                        if( sBuf.Length() == 14 )
                        {
                            if ( sBuf.ByteType( 14 ) == mbLeadByte ){
                                sBuf = sBuf.SubString(1,13);
                            }
                        }
					    if( sBuf == 0 || sBuf == "良")
					    {
                            strcpy(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT,"0");
                        }
                        else if(sBuf.Length() != 0)
					    {
                            strcpy(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT,"1");
                        }
                        else
					    {
                            strcpy(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT,"");
                        }
                    }
                    break;
				default:
					sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
					SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;
					//セル入力をバッファに取り込む
					if(hCELLINFO_RIRE_SOZAI)
					{
						//印刷用画面で以外
						if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
				}
			}
		}
		else
		{
			sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
		}
		InflateRect(&r,-2,-2);
//選択中はハイライト表示
   		if(State.Contains(gdFocused)
		&& SGr_vRIRE_SOZAI->Canvas->Font->Color != clRed
		&& SGr_vRIRE_SOZAI->Canvas->Font->Color != clGray)
		{
			SGr_vRIRE_SOZAI->Canvas->Font->Color= clHighlightText;
   		}
//印刷編集画面はカラーを変更する
		if(SGr_vRIRE_SOZAI->Color == 0x00DDDDDD)
		{
			switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
			{
			case 0:
			case 1:
			case 2:
				try{
//				if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT).Trim()
//			 	!= AnsiString(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].DISP_RESULT).Trim())
				sComp1 = AnsiString(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT);
				sComp2 = AnsiString(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].DISP_RESULT);
				sTempComp = sComp1;
				bRtn = ConvDoubleDefS(sTempComp,sDeci1,sTempComp,&sComp1);
				sTempComp = sComp2;
				bRtn = ConvDoubleDefS(sTempComp,sDeci1,sTempComp,&sComp2);
				if( sComp1 != sComp2)
				{
					if(SGr_vRIRE_SOZAI->Canvas->Font->Color == clRed)
					{
						SGr_vRIRE_SOZAI->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vRIRE_SOZAI->Canvas->Font->Color= clBlue;
					}
				}
				else
				{
					if(SGr_vRIRE_SOZAI->Canvas->Font->Color == clRed)
					{
 						SGr_vRIRE_SOZAI->Canvas->Font->Color= clRed;
					}
					else
					{
						SGr_vRIRE_SOZAI->Canvas->Font->Color= clGray;
					}
				}
				}
				catch(EConvertError& e){
					if(SGr_vRIRE_SOZAI->Canvas->Font->Color == clRed)
					{
						SGr_vRIRE_SOZAI->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vRIRE_SOZAI->Canvas->Font->Color= clBlue;
					}
				}
				catch(...){
					if(SGr_vRIRE_SOZAI->Canvas->Font->Color == clRed)
					{
						SGr_vRIRE_SOZAI->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vRIRE_SOZAI->Canvas->Font->Color= clBlue;
					}
				}
				break;
			default:
				if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT).Trim()
			 	!= AnsiString(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].DISP_RESULT).Trim())
				{
					if(SGr_vRIRE_SOZAI->Canvas->Font->Color == clRed)
					{
						SGr_vRIRE_SOZAI->Canvas->Font->Color= clMaroon;
					}
					else
					{
						SGr_vRIRE_SOZAI->Canvas->Font->Color= clBlue;
					}
				}
				else
				{
					if(SGr_vRIRE_SOZAI->Canvas->Font->Color == clRed)
					{
 						SGr_vRIRE_SOZAI->Canvas->Font->Color= clRed;
					}
					else
					{
						SGr_vRIRE_SOZAI->Canvas->Font->Color= clGray;
					}
				}
				break;
			}
		}
	//不要文字？
//		if( AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].KOMK_NO).ToIntDef(0) == 0
		if( pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].INS_ON == false
		|| AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].SOKU_FLG).ToIntDef(0) == 0)
		{
			SGr_vRIRE_SOZAI->Canvas->Font->Color= clGray;
			SGr_vRIRE_SOZAI->Canvas->Brush->Color= clGray;
		}
		SGr_vRIRE_SOZAI->Canvas->FillRect(Rect);
		InflateRect(&r,-2,-2);
//出力タイプによるフォーマット位置調整
		switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
		{
		case 0:		//整数・少数
		case 1:		//角度
			DrawText(SGr_vRIRE_SOZAI->Canvas->Handle,sBuf.c_str(),-1,&r,DT_RIGHT); //右寄せ
			break;
		case 2:  	//良・否
			DrawText(SGr_vRIRE_SOZAI->Canvas->Handle,sBuf.c_str(),-1,&r,DT_CENTER); //中央寄せ
			break;
		default:	//文字
			DrawText(SGr_vRIRE_SOZAI->Canvas->Handle,sBuf.c_str(),-1,&r,DT_LEFT); //左寄せ
			break;
		}
//色による判定
		if(hCELLINFO_RIRE_SOZAI)
		{
			if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD)
	   		{
		   		switch(SGr_vRIRE_SOZAI->Canvas->Font->Color)
				{
			   	case clBlack:
			  		pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].JUDGE = 0;
			 		break;
			   	case clRed:
			   		pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].JUDGE = 1;
		  			break;
		 		default:
					pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].JUDGE = 2;
			   		break;
	   			}
	 		}
			else
   			{
  				switch(SGr_vRIRE_SOZAI->Canvas->Font->Color)
				{
				case clBlue:
				//規格判定がいります
					pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].JUDGE = 0;
					break;
				case clGray:
					pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].JUDGE = 0;
					break;
				case clRed:
					pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].JUDGE = 1;
					break;
				case clMaroon:
					pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].JUDGE = 1;
					break;
				default:
					pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].JUDGE = 2;
					break;
				}
			}
			if(sBuf.Trim() == 0) pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].JUDGE = 2;
		}
		break;
	}
	GET_HANTEI(Sender, ACol);
}

//---------------------------------------------------------------------------
//
//  概要
//    OnDrawCellイベント	：素材履歴の日付描画時発生します。
//
//  機能説明
//    YYYY/MM/DD形式で日付を描画します。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int ACol          ：対象セルのカラム位置
//    int ARow          ：対象セルのＲＯＷ位置
//  　TRect &Rect       ：セルの位置情報
//  　TGridDrawState State  : セルのステータス（フォーカスの有無等）
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tRIRE_SOZAIDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{

   RECT r=RECT(Rect);
	AnsiString sBuf,sBuf1;
	int i1;
	sBuf = SGr_tRIRE_SOZAI->Cells[ACol][0];

    sBuf1 ="";
    //無効な文字は表示対照から外します
    for(i1=1;i1<=sBuf.Length();i1++)
    {
       	if(strcspn(sBuf.SubString(i1,1).c_str(),"0123456789")==0)
        {
           	sBuf1 += sBuf.SubString(i1,1);
        }
    }
	if( sBuf1.Length() != 8)
	{
		sBuf = "";
	}
	else
	{
    	sBuf = sBuf1.SubString(1,4) + "/" + sBuf1.SubString(5,2) + "/" + sBuf1.SubString(7,2);
	}
   //固定セルの背景色をセット
   if(State.Contains(gdFixed)){

   }
   //フォーカスのあるセルの背景色をセット
   else if(State.Contains(gdFocused)){
		SGr_tRIRE_SOZAI->Canvas->Brush->Color= clHighlight;
   }

   //普通のセルの背景色をセット
   else{
       SGr_tRIRE_SOZAI->Canvas->Brush->Color= SGr_tRIRE_SOZAI->Color;
   }
   //背景色で消去
   SGr_tRIRE_SOZAI->Canvas->FillRect(Rect);

   //固定セルの立体枠を描く
   if(SGr_tRIRE_SOZAI->Ctl3D&&State.Contains(gdFixed)){
       DrawEdge(SGr_tRIRE_SOZAI->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);
   }
   //フォーカスのあるセルの文字色をセット
   if(State.Contains(gdFocused)){
	   SGr_tRIRE_SOZAI->Canvas->Font->Color= clHighlightText;
   }
   else{
       SGr_tRIRE_SOZAI->Canvas->Font->Color= SGr_tRIRE_SOZAI->Font->Color;
   }

   //テキスト表示領域の設定
   InflateRect(&r,-2,-2);

   //テキストの表示
   DrawText(SGr_tRIRE_SOZAI->Canvas->Handle,sBuf.c_str(),-1,&r,0); //右寄せ

}

//---------------------------------------------------------------------------
//
//  概要
//    OnDrawCellイベント	：素材測定の日付描画時発生します。
//
//  機能説明
//    YYYY/MM/DD形式で日付を描画します。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int ACol          ：対象セルのカラム位置
//    int ARow          ：対象セルのＲＯＷ位置
//  　TRect &Rect       ：セルの位置情報
//  　TGridDrawState State  : セルのステータス（フォーカスの有無等）
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tSOKU_SOZAIDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
   	RECT r=RECT(Rect);
	AnsiString sBuf,sBuf1;
    int i1;
	sBuf = SGr_tSOKU_SOZAI->Cells[ACol][0];

   	sBuf1="";
    //無効な文字は表示対照から外します
    for(i1=1;i1<=sBuf.Length();i1++)
    {
    	if(strcspn(sBuf.SubString(i1,1).c_str(),"0123456789")==0)
        {
        	sBuf1 += sBuf.SubString(i1,1);
        }
	}
	if(sBuf1.Length() != 8)
	{
		sBuf ="";
	}
	else
	{
		sBuf = sBuf1.SubString(1,4) + "/" + sBuf1.SubString(5,2) + "/" + sBuf1.SubString(7,2);
	}
   //固定セルの背景色をセット
   if(State.Contains(gdFixed)){

   }
   //フォーカスのあるセルの背景色をセット
   else if(State.Contains(gdFocused)){
		SGr_tSOKU_SOZAI->Canvas->Brush->Color= clHighlight;
   }
   //普通のセルの背景色をセット
   else{
       SGr_tSOKU_SOZAI->Canvas->Brush->Color= SGr_tSOKU_SOZAI->Color;
   }
   //背景色で消去
   SGr_tSOKU_SOZAI->Canvas->FillRect(Rect);

   //固定セルの立体枠を描く
   if(SGr_tSOKU_SOZAI->Ctl3D&&State.Contains(gdFixed)){
       DrawEdge(SGr_tSOKU_SOZAI->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);
   }
   //フォーカスのあるセルの文字色をセット
   if(State.Contains(gdFocused)){
	   SGr_tSOKU_SOZAI->Canvas->Font->Color= clHighlightText;
   //普通のセルの文字色をセット
   }
   else{
       SGr_tSOKU_SOZAI->Canvas->Font->Color= SGr_tSOKU_SOZAI->Font->Color;
   }

   //テキスト表示領域の設定
   InflateRect(&r,-2,-2);

   //テキストの表示
   DrawText(SGr_tSOKU_SOZAI->Canvas->Handle,sBuf.c_str(),-1,&r,0); //右寄せ
}

//---------------------------------------------------------------------------
//
//  概要
//    OnDrawCellイベント	：出荷履歴の日付描画時発生します。
//
//  機能説明
//    YYYY/MM/DD形式で日付を描画します。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int ACol          ：対象セルのカラム位置
//    int ARow          ：対象セルのＲＯＷ位置
//  　TRect &Rect       ：セルの位置情報
//  　TGridDrawState State  : セルのステータス（フォーカスの有無等）
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tRIRE_SYUKADrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
   	RECT r=RECT(Rect);
	AnsiString sBuf,sBuf1;
	int i1;
	sBuf = SGr_tRIRE_SYUKA->Cells[ACol][0];

    sBuf1="";
    //数字以外の文字列は描画対照から外します
    for(i1=1;i1<=sBuf.Length();i1++)
    {
    	if(strcspn(sBuf.SubString(i1,1).c_str(),"0123456789")==0)
        {
        	sBuf1 += sBuf.SubString(i1,1);
        }
	}
    if( sBuf1.Length() != 8)
	{
		sBuf = "";
	}
	else
	{
    	sBuf = sBuf1.SubString(1,4) + "/" + sBuf1.SubString(5,2) + "/" + sBuf1.SubString(7,2);
	}
   //固定セルの背景色をセット
   if(State.Contains(gdFixed)){

   }
   //フォーカスのあるセルの背景色をセット
   else if(State.Contains(gdFocused)){
		SGr_tRIRE_SYUKA->Canvas->Brush->Color= clHighlight;
   }
   //普通のセルの背景色をセット
   else{
       SGr_tRIRE_SYUKA->Canvas->Brush->Color= SGr_tRIRE_SYUKA->Color;
   }
   //背景色で消去
   SGr_tRIRE_SYUKA->Canvas->FillRect(Rect);

   //固定セルの立体枠を描く
   if(SGr_tRIRE_SYUKA->Ctl3D&&State.Contains(gdFixed)){
       DrawEdge(SGr_tRIRE_SYUKA->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);
   }
   //フォーカスのあるセルの文字色をセット
   if(State.Contains(gdFocused)){
	   SGr_tRIRE_SYUKA->Canvas->Font->Color= clHighlightText;

   //普通のセルの文字色をセット
   }
   else{
       SGr_tRIRE_SYUKA->Canvas->Font->Color= SGr_tRIRE_SYUKA->Font->Color;
   }

   //テキスト表示領域の設定
   InflateRect(&r,-2,-2);

   //テキストの表示
   DrawText(SGr_tRIRE_SYUKA->Canvas->Handle,sBuf.c_str(),-1,&r,0); //右寄せ

}

//---------------------------------------------------------------------------
//
//  概要
//    OnDrawCellイベント	：出荷測定の日付描画時発生します。
//
//  機能説明
//    YYYY/MM/DD形式で日付を描画します。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int ACol          ：対象セルのカラム位置
//    int ARow          ：対象セルのＲＯＷ位置
//  　TRect &Rect       ：セルの位置情報
//  　TGridDrawState State  : セルのステータス（フォーカスの有無等）
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tSOKU_SYUKADrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
	RECT r=RECT(Rect);
	AnsiString sBuf,sBuf1;
	int i1;
	sBuf = SGr_tSOKU_SYUKA->Cells[ACol][0];

    sBuf1="";
    //数字以外は描画対象から外します
    for(i1=1;i1<=sBuf.Length();i1++)
    {
    	if(strcspn(sBuf.SubString(i1,1).c_str(),"0123456789")==0)
        {
        	sBuf1 += sBuf.SubString(i1,1);
        }
	}
    if(sBuf1.Length() != 8 )
	{
		sBuf ="";
	}
	else
	{
		sBuf = sBuf1.SubString(1,4) + "/" + sBuf1.SubString(5,2) + "/" + sBuf1.SubString(7,2);
	}
   //固定セルの背景色をセット
   if(State.Contains(gdFixed)){

   }
   //フォーカスのあるセルの背景色をセット
   else if(State.Contains(gdFocused)){
		SGr_tSOKU_SYUKA->Canvas->Brush->Color= clHighlight;
   }
   //普通のセルの背景色をセット
   else{
       SGr_tSOKU_SYUKA->Canvas->Brush->Color= SGr_tSOKU_SYUKA->Color;
   }
   //背景色で消去
   SGr_tSOKU_SYUKA->Canvas->FillRect(Rect);

   //固定セルの立体枠を描く
   if(SGr_tSOKU_SYUKA->Ctl3D&&State.Contains(gdFixed)){
       DrawEdge(SGr_tSOKU_SYUKA->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);
   }
   //フォーカスのあるセルの文字色をセット
   if(State.Contains(gdFocused)){
	   SGr_tSOKU_SYUKA->Canvas->Font->Color= clHighlightText;
   //普通のセルの文字色をセット
   }
   else{
       SGr_tSOKU_SYUKA->Canvas->Font->Color= SGr_tSOKU_SYUKA->Font->Color;
   }

   //テキスト表示領域の設定
   InflateRect(&r,-2,-2);

   //テキストの表示
   DrawText(SGr_tSOKU_SYUKA->Canvas->Handle,sBuf.c_str(),-1,&r,0); //右寄せ
}

//---------------------------------------------------------------------------
//
//  概要
//    OnExitイベント	：素材履歴の日付描画を終了するときに発生します。
//
//  機能説明
//    YYYY/MM/DD形式で日付を再描画します。
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
void __fastcall TForm1::SGr_tRIRE_SOZAIExit(TObject *Sender)
{
    TGridDrawState State;

    // フォーカスを失う時、選択状態の文字色が正常に戻らない為、
    // 再度、通常のセルとして再描画させます。
    SGr_tRIRE_SOZAIDrawCell( Sender,
                             SGr_tRIRE_SOZAI->Col,
                             SGr_tRIRE_SOZAI->Row,
                             SGr_tRIRE_SOZAI->CellRect(SGr_tRIRE_SOZAI->Col, SGr_tRIRE_SOZAI->Row),
                             State);
}

//---------------------------------------------------------------------------
//
//  概要
//    OnExitイベント	：素材履歴のデータ描画を終了するときに発生します。
//
//  機能説明
//    データを再描画します。
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
void __fastcall TForm1::SGr_vRIRE_SOZAIExit(TObject *Sender)
{
    TGridDrawState State;

    // フォーカスを失う時、選択状態の文字色が正常に戻らない為、
    // 再度、通常のセルとして再描画させます。
    AllGRID_DrawCell( Sender,
                             SGr_vRIRE_SOZAI->Col,
                             SGr_vRIRE_SOZAI->Row,
                             SGr_vRIRE_SOZAI->CellRect(SGr_vRIRE_SOZAI->Col, SGr_vRIRE_SOZAI->Row),
                             State);
}

//---------------------------------------------------------------------------
//
//  概要
//    OnExitイベント	：素材測定のデータ描画を終了するときに発生します。
//
//  機能説明
//    データを再描画します。
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
void __fastcall TForm1::SGr_vSOKU_SOZAIExit(TObject *Sender)
{
    TGridDrawState State;

    // フォーカスを失う時、選択状態の文字色が正常に戻らない為、
    // 再度、通常のセルとして再描画させます。
    AllGRID_DrawCell( Sender,
                             SGr_vSOKU_SOZAI->Col,
                             SGr_vSOKU_SOZAI->Row,
                             SGr_vSOKU_SOZAI->CellRect(SGr_vSOKU_SOZAI->Col, SGr_vSOKU_SOZAI->Row),
                             State);
}

//---------------------------------------------------------------------------
//
//  概要
//    OnExitイベント	：素材測定のデータ描画を終了するときに発生します。
//
//  機能説明
//    データを再描画します。
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
void __fastcall TForm1::SGr_vRIRE_SYUKAExit(TObject *Sender)
{
    TGridDrawState State;

    // フォーカスを失う時、選択状態の文字色が正常に戻らない為、
    // 再度、通常のセルとして再描画させます。
    AllGRID_DrawCell( Sender,
                             SGr_vRIRE_SYUKA->Col,
                             SGr_vRIRE_SYUKA->Row,
                             SGr_vRIRE_SYUKA->CellRect(SGr_vRIRE_SYUKA->Col, SGr_vRIRE_SYUKA->Row),
                             State);
}

//---------------------------------------------------------------------------
//
//  概要
//    OnExitイベント	：出荷測定のデータ描画を終了するときに発生します。
//
//  機能説明
//    データを再描画します。
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
void __fastcall TForm1::SGr_vSOKU_SYUKAExit(TObject *Sender)
{
    TGridDrawState State;

    // フォーカスを失う時、選択状態の文字色が正常に戻らない為、
    // 再度、通常のセルとして再描画させます。
    AllGRID_DrawCell( Sender,
                             SGr_vSOKU_SYUKA->Col,
                             SGr_vSOKU_SYUKA->Row,
                             SGr_vSOKU_SYUKA->CellRect(SGr_vSOKU_SYUKA->Col, SGr_vSOKU_SYUKA->Row),
                             State);
}

//---------------------------------------------------------------------------
//
//  概要
//    OnExitイベント	：素材測定の日付描画を終了するときに発生します。
//
//  機能説明
//    YYYY/MM/DD形式で日付を再描画します。
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tSOKU_SOZAIExit(TObject *Sender)
{
    TGridDrawState State;

    // フォーカスを失う時、選択状態の文字色が正常に戻らない為、
    // 再度、通常のセルとして再描画させます。
    SGr_tSOKU_SOZAIDrawCell( Sender,
                             SGr_tSOKU_SOZAI->Col,
                             SGr_tSOKU_SOZAI->Row,
                             SGr_tSOKU_SOZAI->CellRect(SGr_tSOKU_SOZAI->Col, SGr_tSOKU_SOZAI->Row),
                             State);
}

//---------------------------------------------------------------------------
//
//  概要
//    OnExitイベント	:出荷履歴の日付描画を終了するときに発生します。
//
//  機能説明
//    YYYY/MM/DD形式で日付を再描画します。
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tRIRE_SYUKAExit(TObject *Sender)
{
    TGridDrawState State;

    // フォーカスを失う時、選択状態の文字色が正常に戻らない為、
    // 再度、通常のセルとして再描画させます。
    SGr_tRIRE_SYUKADrawCell( Sender,
                             SGr_tRIRE_SYUKA->Col,
                             SGr_tRIRE_SYUKA->Row,
                             SGr_tRIRE_SYUKA->CellRect(SGr_tRIRE_SYUKA->Col, SGr_tRIRE_SYUKA->Row),
                             State);
}

//---------------------------------------------------------------------------
//
//  概要
//    OnExitイベント	:出荷測定の日付描画を終了するときに発生します。
//
//  機能説明
//    YYYY/MM/DD形式で日付を再描画します。
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tSOKU_SYUKAExit(TObject *Sender)
{
    TGridDrawState State;

    // フォーカスを失う時、選択状態の文字色が正常に戻らない為、
    // 再度、通常のセルとして再描画させます。
    SGr_tSOKU_SYUKADrawCell( Sender,
                             SGr_tSOKU_SYUKA->Col,
                             SGr_tSOKU_SYUKA->Row,
                             SGr_tSOKU_SYUKA->CellRect(SGr_tSOKU_SYUKA->Col, SGr_tSOKU_SYUKA->Row),
                             State);
}

//---------------------------------------------------------------------------
//
//  概要
//    デストラクタイベント	:フォームがメモリ上から消えるときに発生します。
//
//  機能説明
//    動的コントロールを消去します。
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
__fastcall TForm1::~TForm1()
{
    int i2;

    for(i2=0 ;i2<iPnl_InsKikiNameCnt;i2++)
    {
        delete Form1->Pnl_InsKikiName[i2];

    }

    for(i2=0 ;i2<iPnl_InsNoCnt;i2++)
    {
        delete Form1->Pnl_InsNo[i2];
    }

    for(i2=0 ;i2<iOrCnt;i2++)
    {
        delete Form1->Pnl_InsName[i2];
    }

    for(i2=0 ;i2<iOrCnt;i2++)
    {
        delete Form1->Pnl_SubBase[i2];
    }

    for(i2 = 0 ; i2 < iSOKU_MEMO_CNT ;i2++)
    {
    	delete Mem_vSOKU_MEMO[i2];
    }

    for(i2 = 0 ; i2 < iRIRE_MEMO_CNT ;i2++)
    {
    	delete Mem_vRIRE_MEMO[i2];
    }

	// メモリの開放
	if( hCELLINFO_SOKU_SYUKA ){
        GlobalUnlock( hCELLINFO_SOKU_SYUKA );
        hCELLINFO_SOKU_SYUKA = GlobalFree( hCELLINFO_SOKU_SYUKA );
    }
	// メモリの開放
	if( hCELLINFO_RIRE_SYUKA ){
        GlobalUnlock( hCELLINFO_RIRE_SYUKA );
        hCELLINFO_RIRE_SYUKA = GlobalFree( hCELLINFO_RIRE_SYUKA );
    }
	// メモリの開放
	if( hCELLINFO_SOKU_SOZAI ){
        GlobalUnlock( hCELLINFO_SOKU_SOZAI );
        hCELLINFO_SOKU_SOZAI = GlobalFree( hCELLINFO_SOKU_SOZAI );
    }
	// メモリの開放
	if( hCELLINFO_RIRE_SOZAI ){
        GlobalUnlock( hCELLINFO_RIRE_SOZAI );
        hCELLINFO_RIRE_SOZAI = GlobalFree( hCELLINFO_RIRE_SOZAI );
    }

/* k.y 2003.05.17
	// メモリの開放
	if( hInfoGlaph ){
        GlobalUnlock( hInfoGlaph );
        hInfoGlaph = GlobalFree( hInfoGlaph );
    }
*/

	//2003.05.08 E.Takase Add↓
	delete sRIREKI_LOT;
    delete sHT_LOT;
    delete sShiji_Data;

	//for(i2=0;i2<iContCnt;i2++)
    //{
    //    delete Lab_KOMK_NM[i2];
    //    delete Lab_TANI[i2];
    //    delete Lab_KIKA[i2];
    //    delete Lab_UPKIKA[i2];
    //    delete Lab_LOKIKA[i2];
    //}
    //for(i2=0 ; i2 < iPnl_InsKikiNameCnt; i2++)
    //{
	//	delete Form1->Lab_KIKI_NM[i2];
    //}

/* k.y 2003.05.17
	// メモリの開放
	if(hInfoGlaph!=NULL){
		GlobalUnlock(hInfoGlaph);
		GlobalFree(hInfoGlaph);
	}
	if(hKSM01_DATA!=NULL){
		GlobalUnlock(hKSM01_DATA);
		GlobalFree(hKSM01_DATA);
	}
	if(hSYUKA_DATA!=NULL){
		GlobalUnlock(hSYUKA_DATA);
		GlobalFree(hSYUKA_DATA);
	}
	if(hRIREKI_DATA!=NULL){
		GlobalUnlock(hRIREKI_DATA);
		GlobalFree(hRIREKI_DATA);
	}
	if(hORDATA!=NULL){
		GlobalUnlock(hORDATA);
		GlobalFree(hORDATA);
	}
*/
	if(hSOKU_KSD01DATA!=NULL){
		GlobalUnlock(hSOKU_KSD01DATA);
		GlobalFree(hSOKU_KSD01DATA);
	}
	if(hSOKU_KSD01_DATA!=NULL){
		GlobalUnlock(hSOKU_KSD01_DATA);
		GlobalFree(hSOKU_KSD01_DATA);
	}
	if(hRIRE_KSD01DATA!=NULL){
		GlobalUnlock(hRIRE_KSD01DATA);
		GlobalFree(hRIRE_KSD01DATA);
	}
/* k.y 2003.05.17
	if(hSOZAI_OR_DATA!=NULL){
		GlobalUnlock(hSOZAI_OR_DATA);
		GlobalFree(hSOZAI_OR_DATA);
	}
*/
	if(hRIRE_KSD01_DATA!=NULL){
		GlobalUnlock(hRIRE_KSD01_DATA);
		GlobalFree(hRIRE_KSD01_DATA);
	}
	//2003.05.08 E.Takase Add↑

	CommClose(1);
}

//---------------------------------------------------------------------------
//
//  概要
//    OnSelectCellイベント	：４分割グリッド内のセルを選択すると発生します。
//
//  機能説明
//    無効セルの選択の禁止やセルの選択で発生するグラフ描画関数の呼び出しを行います。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int ACol          ：対象セルのカラム位置
//    int ARow          ：対象セルのＲＯＷ位置
//  　bool &CanSelect   ：セルの選択、有効／無効を行います
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::AllGRID_SelectCell(TObject *Sender,
      int ACol, int ARow, bool &CanSelect)
{
	int i1;
	int iGridTag,iRow;
	bool bNum;				//規格が数値？フラグ

	AnsiString sBuf;
    //検索中はセルの移動に制限を持たせない
    if(bNowF7 == true) return;

	bNum = false;
 	if(Sender == SGr_vSOKU_SYUKA)
	{
    	SGr_vSOKU_SYUKA->Options << goEditing;

 		iGridTag=SGr_vSOKU_SYUKA->Tag;
/*
        if((Form1->SGr_vSOKU_SYUKA->Cells[ACol][ARow] == "不要" && bKASOU_MOVE == false)
			|| !hCELLINFO_SOKU_SYUKA)
        {
        	CanSelect = false;
            Delete_InplaceEdit(Sender);		// 編集ウィンドウを無効にします
            return;
        }
*/
        //if(((	AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].KOMK_NO).ToIntDef(0) == 0)
/* 2005.09.29 Y.Sano Add start	*/
/* 一度も検索していない状態でアクセスしにいくと	*/
/* アプリケーションエラーが発生すすため			*/
/* NULL判定を追加した							*/
		if( pCELLINFO_RIRE_SOZAI == NULL ) return;
/* 2005.09.29 Y.Sano Add end	*/
        if(((	pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].INS_ON == false)
        ||(	AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].SOKU_FLG).ToIntDef(0) == 0))
         && bKASOU_MOVE == false)
        {
            Delete_InplaceEdit(Sender);		// 編集ウィンドウを無効にします
        	CanSelect = false;
            return;
        }
		if( SGr_vSOKU_SYUKA->RowCount < 2 )
		{
        	CanSelect = false;
            Delete_InplaceEdit(Sender);		// 編集ウィンドウを無効にします
            return;
		}
	}
 	if(Sender == SGr_vSOKU_SOZAI)
	{
    	SGr_vSOKU_SOZAI->Options << goEditing;

		iGridTag=SGr_vSOKU_SOZAI->Tag;
/*
        if((Form1->SGr_vSOKU_SOZAI->Cells[ACol][ARow] == "不要" && bKASOU_MOVE == false)
			|| !hCELLINFO_SOKU_SOZAI)
		{
            Delete_InplaceEdit(Sender);		// 編集ウィンドウを無効にします
        	CanSelect = false;
            return;
        }
*/
        //if(((	AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].KOMK_NO).ToIntDef(0) == 0)
/* 2005.09.29 Y.Sano Add start	*/
/* 一度も検索していない状態でアクセスしにいくと	*/
/* アプリケーションエラーが発生すすため			*/
/* NULL判定を追加した							*/
        if( pCELLINFO_SOKU_SOZAI == NULL ) return;
/* 2005.09.29 Y.Sano Add end	*/
        if(((	pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].INS_ON == false)
        ||  (	AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].SOKU_FLG).ToIntDef(0) == 0 ))
        && bKASOU_MOVE == false)
        {
            Delete_InplaceEdit(Sender);		// 編集ウィンドウを無効にします
        	CanSelect = false;
            return;
        }
		if( SGr_vSOKU_SOZAI->RowCount < 2 )
		{
        	CanSelect = false;
            Delete_InplaceEdit(Sender);		// 編集ウィンドウを無効にします
            return;
		}
	}
 	if(Sender == SGr_vRIRE_SYUKA)
	{
    	SGr_vRIRE_SYUKA->Options << goEditing;

 		iGridTag=SGr_vRIRE_SYUKA->Tag;
/*
        if((Form1->SGr_vRIRE_SYUKA->Cells[ACol][ARow] == "不要" && bKASOU_MOVE == false)
			|| !hCELLINFO_RIRE_SYUKA)
        {
            Delete_InplaceEdit(Sender);		// 編集ウィンドウを無効にします
        	CanSelect = false;
            return;
        }
*/
//        if(((	AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].KOMK_NO).ToIntDef(0) == 0)
/* 2005.09.29 Y.Sano Add start	*/
/* 一度も検索していない状態でアクセスしにいくと	*/
/* アプリケーションエラーが発生すすため			*/
/* NULL判定を追加した							*/
        if( pCELLINFO_RIRE_SYUKA == NULL ) return;
/* 2005.09.29 Y.Sano Add end	*/
        if(((	pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].INS_ON == false)
        ||  (	AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].SOKU_FLG).ToIntDef(0) == 0 ))
        && bKASOU_MOVE == false)
        {
            Delete_InplaceEdit(Sender);		// 編集ウィンドウを無効にします
        	CanSelect = false;
            return;
        }
		if( SGr_vRIRE_SYUKA->RowCount < 2 )
		{
        	CanSelect = false;
            Delete_InplaceEdit(Sender);		// 編集ウィンドウを無効にします
            return;
		}
	}
 	if(Sender == SGr_vRIRE_SOZAI)
	{
    	SGr_vRIRE_SOZAI->Options << goEditing;

 		iGridTag=SGr_vRIRE_SOZAI->Tag;
/*
        if((Form1->SGr_vRIRE_SOZAI->Cells[ACol][ARow] == "不要" && bKASOU_MOVE == false)
			|| !hCELLINFO_RIRE_SOZAI)
        {
            Delete_InplaceEdit(Sender);		// 編集ウィンドウを無効にします
        	CanSelect = false;
            return;
        }
*/
//        if(((	AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].KOMK_NO).ToIntDef(0) == 0)
/* 2005.09.29 Y.Sano Add start	*/
/* 一度も検索していない状態でアクセスしにいくと	*/
/* アプリケーションエラーが発生すすため			*/
/* NULL判定を追加した							*/
		if( pCELLINFO_RIRE_SOZAI == NULL ) return;
/* 2005.09.29 Y.Sano Add end	*/
        if(((	pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].INS_ON == false)
        ||  (	AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].SOKU_FLG).ToIntDef(0) == 0 ))
        && bKASOU_MOVE == false)
        {
            Delete_InplaceEdit(Sender);		// 編集ウィンドウを無効にします
        	CanSelect = false;
            return;
        }
		if( SGr_vRIRE_SOZAI->RowCount < 2 )
		{
        	CanSelect = false;
            Delete_InplaceEdit(Sender);		// 編集ウィンドウを無効にします
            return;
		}
	}
	if( ARow == 0 )
//	if(ARow == 0 && bHANTEI_DISP == false)
    {
        Delete_InplaceEdit(Sender);		// 編集ウィンドウを無効にします
		CanSelect = false;
		return;
    }

    CanSelect = true;
    //グラフ描画する際のセルの情報を収集します
    i1 = Get_GRAPHSTART_Info(ARow,ACol,iGridTag);
    switch(iGridTag)
    {
	case 1:
		iRow = SGr_vSOKU_SYUKA->RowCount;
    	sBuf = pCELLINFO_SOKU_SYUKA[ACol*iRow+ARow].KIKI_NO;
		if (AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRow+ARow].VALUE_TYPE).ToIntDef(0) < 2 ) bNum = true;
        iRow_vSOKU_SYUKA = ARow;
        iCol_vSOKU_SYUKA = ACol;
        break;
	case 2:
		iRow = SGr_vRIRE_SYUKA->RowCount;
    	sBuf = pCELLINFO_RIRE_SYUKA[ACol*iRow+ARow].KIKI_NO;
		if (AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRow+ARow].VALUE_TYPE).ToIntDef(0) < 2 ) bNum = true;
        iRow_vRIRE_SYUKA = ARow;
        iCol_vRIRE_SYUKA = ACol;
        break;
	case 3:
		iRow = SGr_vSOKU_SOZAI->RowCount;
    	sBuf = pCELLINFO_SOKU_SOZAI[ACol*iRow+ARow].KIKI_NO;
		if (AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRow+ARow].VALUE_TYPE).ToIntDef(0) < 2 ) bNum = true;
        iRow_vSOKU_SOZAI = ARow;
        iCol_vSOKU_SOZAI = ACol;
        break;
	case 4:
		iRow = SGr_vRIRE_SOZAI->RowCount;
    	sBuf = pCELLINFO_RIRE_SOZAI[ACol*iRow+ARow].KIKI_NO;
		if (AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRow+ARow].VALUE_TYPE).ToIntDef(0) < 2 ) bNum = true;
        iRow_vRIRE_SOZAI = ARow;
        iCol_vRIRE_SOZAI = ACol;
        break;
    }
    if(bCellWrite == true ) return;
    //グラフ描画を開始します
    Get_GRAPHLOT(i1,ACol,iGridTag);
}

//---------------------------------------------------------------------------
//
//  概要
//    OnKeyPressイベント	：出荷測定セル上で単一の文字キー入力があると発生します。
//
//  機能説明
//    アップデートフラグの更新。
//    文字列長の確認
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    char &Key         : char型のキーコード
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vSOKU_SYUKAKeyPress(TObject *Sender, char &Key)
{
	int iRow,iCol,iRowCount;
    AnsiString sBuf,sDATE,sTIME;
//    MSG msg;

	iCol = SGr_vSOKU_SYUKA->Col;
	iRow = SGr_vSOKU_SYUKA->Row;
    iRowCount = SGr_vSOKU_SYUKA->RowCount;
    if(iRowCount < 2 ) return;
    sBuf = SGr_vSOKU_SYUKA->Cells[iCol][iRow];
//    strcpy(pCELLINFO_SOKU_SYUKA[iCol*SGr_vSOKU_SYUKA->RowCount +iRow].RESULT,sBuf.c_str());
	if( Key == VK_RETURN ) GridSetPointMove(Sender,Key);

    //文字列長チェック
    //2003.05.17 E.Takase Add↓
    bool bRtn = ChkSize( hCELLINFO_SOKU_SYUKA, iCol*SGr_vSOKU_SYUKA->RowCount+iRow, sizeof(struct CELLINFO_DATA));
    if ( bRtn ) {
		int iVALUE_TYPE = AnsiString(pCELLINFO_SOKU_SYUKA[iCol*SGr_vSOKU_SYUKA->RowCount+iRow].VALUE_TYPE).ToIntDef(0);
        int iLenMAX = 14;
        if ( iVALUE_TYPE == 2 ) {
        	iLenMAX = 1;
        }
	    ChkInputData( sBuf, iVALUE_TYPE, Sender, Key, iLenMAX);
    }
    //RETURNキー以外（Returnキーは本イベントに入ってくるためチェックしています）
	//2003.05.17 E.Takase Add↑
    if(Key != VK_RETURN && bCellWrite == false)
    {
        //アップデートフラグをはじめとして、日付等の更新を行います
        if( hSOKU_KSD01_DATA && hCELLINFO_SOKU_SYUKA )
        {
            pSOKU_KSD01_DATA[iCol].UPD_FLG = true;          //UPDATEフラグ（RETURN KEY以外なら？）
            if(SGr_vSOKU_SYUKA->Color != (TColor)0x00DDDDDD)   //印刷画面では更新者等の書き換えは行わない
            {
            //代表更新者の書き換え
                strcpy(pSOKU_KSD01_DATA[iCol].UPDCHR 	 ,AnsiString(Form1->USER_COD).c_str());
            //更新者の書き換え(セル毎）
                strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDCHR , AnsiString(Form1->USER_COD).c_str());
            //2003.05.17 E.Takase Add↓
                strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDNAME , AnsiString(Form1->USER_NAM).c_str());
            //2003.05.17 E.Takase Add↑
            //日付の書き換え(セル毎）
                sDATE = FormatDateTime("yyyymmdd",Date());
                sTIME = FormatDateTime("hhmm",TDateTime::CurrentTime());
                strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDYMD,sDATE.c_str());
                strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDTIM,sTIME.c_str());
            //未登録なら測定日、登録日も更新（新規）する
                if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].SKTYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].SKTYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].ADDYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].ADDYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].ADDTIM).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].ADDTIM,sTIME.c_str());
                }
            }
        }
    }
	iCol = SGr_vSOKU_SYUKA->Col;
	iRow = SGr_vSOKU_SYUKA->Row;
//	AllGRID_SelectCell(Sender,iCol,iRow, blnHoge);
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：出荷測定グリッド上で外部計測器からの入力を受けます
//
//  機能説明
//    アップデートフラグの更新。
//    文字列長の確認
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
void __fastcall TForm1::SGr_vSOKU_SYUKAComPress(void)
{
	int iRow,iCol,iRowCount;
    AnsiString sBuf,sDATE,sTIME;

	iCol = SGr_vSOKU_SYUKA->Col;
	iRow = SGr_vSOKU_SYUKA->Row;
    iRowCount = SGr_vSOKU_SYUKA->RowCount;
    sBuf = SGr_vSOKU_SYUKA->Cells[iCol][iRow];
    if( hSOKU_KSD01_DATA && hCELLINFO_SOKU_SYUKA )
    {
        pSOKU_KSD01_DATA[iCol].UPD_FLG = true;          //UPDATEフラグ（RETURN KEY以外なら？）
        if(SGr_vSOKU_SYUKA->Color != (TColor)0x00DDDDDD)   //印刷画面では更新者等の書き換えは行わない
        {
        //代表更新者の書き換え
            strcpy(pSOKU_KSD01_DATA[iCol].UPDCHR 	 ,AnsiString(Form1->USER_COD).c_str());
        //更新者の書き換え(セル毎）
            strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDCHR , AnsiString(Form1->USER_COD).c_str());
        //2003.05.17 E.Takase Add↓
            strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDNAME , AnsiString(Form1->USER_NAM).c_str());
        //2003.05.17 E.Takase Add↑
        //日付の書き換え(セル毎）
            sDATE = FormatDateTime("yyyymmdd",Date());
            sTIME = FormatDateTime("hhmm",TDateTime::CurrentTime());
            strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDYMD,sDATE.c_str());
            strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDTIM,sTIME.c_str());
        //未登録なら測定日、登録日も更新（新規）する
            if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].SKTYMD).Trim().Length() == 0)
            {
                strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].SKTYMD,sDATE.c_str());
            }
            if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].ADDYMD).Trim().Length() == 0)
            {
                strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].ADDYMD,sDATE.c_str());
            }
            if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].ADDTIM).Trim().Length() == 0)
            {
                strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].ADDTIM,sTIME.c_str());
            }
        }
    }
}

//---------------------------------------------------------------------------
//
//  概要
//    OnKeyPressイベント	：素材測定セル上で単一の文字キー入力があると発生します。
//
//  機能説明
//    アップデートフラグの更新。
//    文字列長の確認
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    char &Key         : char型のキーコード
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vSOKU_SOZAIKeyPress(TObject *Sender, char &Key)
{
	int iRow,iCol,iRowCount;
    AnsiString sBuf,sDATE,sTIME;
    bool blnHoge=true;

	iCol = SGr_vSOKU_SOZAI->Col;
	iRow = SGr_vSOKU_SOZAI->Row;
	iRowCount = SGr_vSOKU_SOZAI->RowCount;
    if(iRowCount < 2 ) return;
    sBuf = SGr_vSOKU_SOZAI->Cells[iCol][iRow];
//    strcpy(pCELLINFO_SOKU_SOZAI[iCol*SGr_vSOKU_SOZAI->RowCount +iRow].RESULT,sBuf.c_str());
	if( Key == VK_RETURN ) GridSetPointMove(Sender,Key);

    //2003.05.17 E.Takase Add↓
    bool bRtn = ChkSize( hCELLINFO_SOKU_SOZAI, iCol*SGr_vSOKU_SOZAI->RowCount+iRow, sizeof(struct CELLINFO_DATA));
    if ( bRtn ) {
		int iVALUE_TYPE = AnsiString(pCELLINFO_SOKU_SOZAI[iCol*SGr_vSOKU_SOZAI->RowCount+iRow].VALUE_TYPE).ToIntDef(0);
        int iLenMAX = 14;
        if ( iVALUE_TYPE == 2 ) {
        	iLenMAX = 1;
        }
	    ChkInputData( sBuf, iVALUE_TYPE, Sender, Key, iLenMAX);
    }
	//2003.05.17 E.Takase Add↑

    if(Key != VK_RETURN && bCellWrite == false)
    {
        if( hSOKU_KSD01_DATA && hCELLINFO_SOKU_SOZAI)
        {
            pSOKU_KSD01_DATA[iCol].UPD_FLG = true;          //UPDATEフラグ（RETURN KEY以外なら？）
            if(SGr_vSOKU_SOZAI->Color != (TColor)0x00DDDDDD)   //印刷画面では更新者等の書き換えは行わない
            {
            //代表更新者の書き換え
                strcpy(pSOKU_KSD01_DATA[iCol].UPDCHR 	 ,AnsiString(Form1->USER_COD).c_str());
            //更新者の書き換え(セル毎）
                strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDCHR , AnsiString(Form1->USER_COD).c_str());
            //2003.05.17 E.Takase Add↓
                strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDNAME , AnsiString(Form1->USER_NAM).c_str());
            //2003.05.17 E.Takase Add↑
            //日付の書き換え(セル毎）
                sDATE = FormatDateTime("yyyymmdd",Date());
                sTIME = FormatDateTime("hhmm",TDateTime::CurrentTime());
                strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDYMD,sDATE.c_str());
                strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDTIM,sTIME.c_str());
            //未登録なら測定日、登録日も更新（新規）する
                if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].SKTYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].SKTYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].ADDYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].ADDYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].ADDTIM).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].ADDTIM,sTIME.c_str());
                }
            }
        }
    }
	iCol = SGr_vSOKU_SOZAI->Col;
	iRow = SGr_vSOKU_SOZAI->Row;
	AllGRID_SelectCell(Sender,iCol,iRow, blnHoge);
}
//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：素材測定グリッド上で外部計測器からの入力を受けます
//
//  機能説明
//    アップデートフラグの更新。
//    文字列長の確認
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
void __fastcall TForm1::SGr_vSOKU_SOZAIComPress(void)
{
	int iRow,iCol,iRowCount;
    AnsiString sBuf,sDATE,sTIME;

	iCol = SGr_vSOKU_SOZAI->Col;
	iRow = SGr_vSOKU_SOZAI->Row;
	iRowCount = SGr_vSOKU_SOZAI->RowCount;
    sBuf = SGr_vSOKU_SOZAI->Cells[iCol][iRow];
//    strcpy(pCELLINFO_SOKU_SOZAI[iCol*SGr_vSOKU_SOZAI->RowCount +iRow].RESULT,sBuf.c_str());

        if( hSOKU_KSD01_DATA && hCELLINFO_SOKU_SOZAI)
        {
            pSOKU_KSD01_DATA[iCol].UPD_FLG = true;          //UPDATEフラグ（RETURN KEY以外なら？）
            if(SGr_vSOKU_SOZAI->Color != (TColor)0x00DDDDDD)   //印刷画面では更新者等の書き換えは行わない
            {
            //代表更新者の書き換え
                strcpy(pSOKU_KSD01_DATA[iCol].UPDCHR 	 ,AnsiString(Form1->USER_COD).c_str());
            //更新者の書き換え(セル毎）
                strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDCHR , AnsiString(Form1->USER_COD).c_str());
            //2003.05.17 E.Takase Add↓
                strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDNAME , AnsiString(Form1->USER_NAM).c_str());
            //2003.05.17 E.Takase Add↑
            //日付の書き換え(セル毎）
                sDATE = FormatDateTime("yyyymmdd",Date());
                sTIME = FormatDateTime("hhmm",TDateTime::CurrentTime());
                strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDYMD,sDATE.c_str());
                strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDTIM,sTIME.c_str());
            //未登録なら測定日、登録日も更新（新規）する
                if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].SKTYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].SKTYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].ADDYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].ADDYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].ADDTIM).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].ADDTIM,sTIME.c_str());
                }
            }
        }
}
//---------------------------------------------------------------------------
//
//  概要
//    OnKeyPressイベント	：履歴測定セル上で単一の文字キー入力があると発生します。
//
//  機能説明
//    アップデートフラグの更新。
//    文字列長の確認
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    char &Key         : char型のキーコード
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vRIRE_SYUKAKeyPress(TObject *Sender, char &Key)
{
	int iRow,iCol,iRowCount;
    AnsiString sBuf,sDATE,sTIME;
    bool blnHoge=true;

    if(Form1->iRIRE_CNT == 0) return;
	iCol = SGr_vRIRE_SYUKA->Col;
	iRow = SGr_vRIRE_SYUKA->Row;
	iRowCount = SGr_vRIRE_SYUKA->RowCount;
    sBuf = SGr_vRIRE_SYUKA->Cells[iCol][iRow];
	if( Key == VK_RETURN ) GridSetPointMove(Sender,Key);

    //2003.05.17 E.Takase Add↓
    bool bRtn = ChkSize( hCELLINFO_RIRE_SYUKA, iCol*SGr_vRIRE_SYUKA->RowCount+iRow, sizeof(struct CELLINFO_DATA));
    if ( bRtn ) {
		int iVALUE_TYPE = AnsiString(pCELLINFO_RIRE_SYUKA[iCol*SGr_vRIRE_SYUKA->RowCount+iRow].VALUE_TYPE).ToIntDef(0);
        int iLenMAX = 14;
        if ( iVALUE_TYPE == 2 ) {
        	iLenMAX = 1;
        }
	    ChkInputData( sBuf, iVALUE_TYPE, Sender, Key, iLenMAX);
    }
	//2003.05.17 E.Takase Add↑

    if(Key != VK_RETURN && bCellWrite == false )
    {
        if( hRIRE_KSD01_DATA && hCELLINFO_RIRE_SYUKA)
        {
            pRIRE_KSD01_DATA[iCol].UPD_FLG = true;          //UPDATEフラグ（RETURN KEY以外なら？）
            if(SGr_vRIRE_SYUKA->Color != (TColor)0x00DDDDDD)   //印刷画面では更新者等の書き換えは行わない
            {
            //代表更新者の書き換え
                strcpy(pRIRE_KSD01_DATA[iCol].UPDCHR 	 ,AnsiString(Form1->USER_COD).c_str());
            //更新者の書き換え(セル毎）
                strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDCHR , AnsiString(Form1->USER_COD).c_str());
            //2003.05.17 E.Takase Add↓
                strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDNAME , AnsiString(Form1->USER_NAM).c_str());
            //2003.05.17 E.Takase Add↑
            //日付の書き換え(セル毎）
                sDATE = FormatDateTime("yyyymmdd",Date());
                sTIME = FormatDateTime("hhmm",TDateTime::CurrentTime());
                strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDYMD,sDATE.c_str());
                strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDTIM,sTIME.c_str());
            //未登録なら測定日、登録日も更新（新規）する
                if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].SKTYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].SKTYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].ADDYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].ADDYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].ADDTIM).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].ADDTIM,sTIME.c_str());
                }
            }       
        }
    }
	iCol = SGr_vRIRE_SYUKA->Col;
	iRow = SGr_vRIRE_SYUKA->Row;
	AllGRID_SelectCell(Sender,iCol,iRow, blnHoge);
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：出荷履歴グリッド上で外部計測器からの入力を受けます
//
//  機能説明
//    アップデートフラグの更新。
//    文字列長の確認
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
void __fastcall TForm1::SGr_vRIRE_SYUKAComPress(void)
{
	int iRow,iCol,iRowCount;
    AnsiString sBuf,sDATE,sTIME;

	iCol = SGr_vRIRE_SYUKA->Col;
	iRow = SGr_vRIRE_SYUKA->Row;
	iRowCount = SGr_vRIRE_SYUKA->RowCount;
    sBuf = SGr_vRIRE_SYUKA->Cells[iCol][iRow];

        if( hRIRE_KSD01_DATA && hCELLINFO_RIRE_SYUKA)
        {
            pRIRE_KSD01_DATA[iCol].UPD_FLG = true;          //UPDATEフラグ（RETURN KEY以外なら？）
            if(SGr_vRIRE_SYUKA->Color != (TColor)0x00DDDDDD)   //印刷画面では更新者等の書き換えは行わない
            {
            //代表更新者の書き換え
                strcpy(pRIRE_KSD01_DATA[iCol].UPDCHR 	 ,AnsiString(Form1->USER_COD).c_str());
            //更新者の書き換え(セル毎）
                strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDCHR , AnsiString(Form1->USER_COD).c_str());
            //2003.05.17 E.Takase Add↓
                strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDNAME , AnsiString(Form1->USER_NAM).c_str());
            //2003.05.17 E.Takase Add↑
            //日付の書き換え(セル毎）
                sDATE = FormatDateTime("yyyymmdd",Date());
                sTIME = FormatDateTime("hhmm",TDateTime::CurrentTime());
                strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDYMD,sDATE.c_str());
                strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDTIM,sTIME.c_str());
            //未登録なら測定日、登録日も更新（新規）する
                if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].SKTYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].SKTYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].ADDYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].ADDYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].ADDTIM).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].ADDTIM,sTIME.c_str());
                }
            }
        }
}

//---------------------------------------------------------------------------
//
//  概要
//    OnKeyPressイベント	：履歴素材セル上で単一の文字キー入力があると発生します。
//
//  機能説明
//    アップデートフラグの更新。
//    文字列長の確認
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    char &Key         : char型のキーコード
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vRIRE_SOZAIKeyPress(TObject *Sender, char &Key)
{
	int iRow,iCol,iRowCount;
    AnsiString sBuf,sTIME,sDATE;
    bool blnHoge=true;

    if(iRIRE_CNT == 0) return;
	iCol = SGr_vRIRE_SOZAI->Col;
	iRow = SGr_vRIRE_SOZAI->Row;
	iRowCount = SGr_vRIRE_SOZAI->RowCount;
    sBuf = SGr_vRIRE_SOZAI->Cells[iCol][iRow];
	if( Key == VK_RETURN ) GridSetPointMove(Sender,Key);

    //2003.05.17 E.Takase Add↓
    bool bRtn = ChkSize( hCELLINFO_RIRE_SOZAI, iCol*SGr_vRIRE_SOZAI->RowCount+iRow, sizeof(struct CELLINFO_DATA));
    if ( bRtn ) {
		int iVALUE_TYPE = AnsiString(pCELLINFO_RIRE_SOZAI[iCol*SGr_vRIRE_SOZAI->RowCount+iRow].VALUE_TYPE).ToIntDef(0);
        int iLenMAX = 14;
        if ( iVALUE_TYPE == 2 ) {
        	iLenMAX = 1;
        }
	    ChkInputData( sBuf, iVALUE_TYPE, Sender, Key, iLenMAX);
    }
	//2003.05.17 E.Takase Add↑

    if(Key != VK_RETURN && bCellWrite == false )
    {
        if( hRIRE_KSD01_DATA && hCELLINFO_RIRE_SOZAI)
        {
            pRIRE_KSD01_DATA[iCol].UPD_FLG = true;              //UPDATEフラグ（RETURN KEY以外なら？）
            if(SGr_vRIRE_SOZAI->Color != (TColor)0x00DDDDDD)    //印刷画面では更新者等の書き換えは行わない
            {
            //代表更新者の書き換え
                strcpy(pRIRE_KSD01_DATA[iCol].UPDCHR 	 ,AnsiString(Form1->USER_COD).c_str());
            //更新者の書き換え(セル毎）
                strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDCHR , AnsiString(Form1->USER_COD).c_str());
            //2003.05.17 E.Takase Add↓
                strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDNAME , AnsiString(Form1->USER_NAM).c_str());
            //2003.05.17 E.Takase Add↑
            //日付の書き換え(セル毎）
                sDATE = FormatDateTime("yyyymmdd",Date());
                sTIME = FormatDateTime("hhmm",TDateTime::CurrentTime());
                strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDYMD,sDATE.c_str());
                strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDTIM,sTIME.c_str());
            //未登録なら測定日、登録日も更新（新規）する
                if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].SKTYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].SKTYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].ADDYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].ADDYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].ADDTIM).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].ADDTIM,sTIME.c_str());
                }
            }
        }
    }
	iCol = SGr_vRIRE_SOZAI->Col;
	iRow = SGr_vRIRE_SOZAI->Row;
	AllGRID_SelectCell(Sender,iCol,iRow, blnHoge);
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：素材履歴グリッド上で外部計測器からの入力を受けます
//
//  機能説明
//    アップデートフラグの更新。
//    文字列長の確認
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
void __fastcall TForm1::SGr_vRIRE_SOZAIComPress(void)
{
	int iRow,iCol,iRowCount;
    AnsiString sBuf,sTIME,sDATE;

	iCol = SGr_vRIRE_SOZAI->Col;
	iRow = SGr_vRIRE_SOZAI->Row;
	iRowCount = SGr_vRIRE_SOZAI->RowCount;
    sBuf = SGr_vRIRE_SOZAI->Cells[iCol][iRow];
        if( hRIRE_KSD01_DATA && hCELLINFO_RIRE_SOZAI)
        {
            pRIRE_KSD01_DATA[iCol].UPD_FLG = true;              //UPDATEフラグ（RETURN KEY以外なら？）
            if(SGr_vRIRE_SOZAI->Color != (TColor)0x00DDDDDD)    //印刷画面では更新者等の書き換えは行わない
            {
            //代表更新者の書き換え
                strcpy(pRIRE_KSD01_DATA[iCol].UPDCHR 	 ,AnsiString(Form1->USER_COD).c_str());
            //更新者の書き換え(セル毎）
                strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDCHR , AnsiString(Form1->USER_COD).c_str());
            //2003.05.17 E.Takase Add↓
                strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDNAME , AnsiString(Form1->USER_NAM).c_str());
            //2003.05.17 E.Takase Add↑
            //日付の書き換え(セル毎）
                sDATE = FormatDateTime("yyyymmdd",Date());
                sTIME = FormatDateTime("hhmm",TDateTime::CurrentTime());
                strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDYMD,sDATE.c_str());
                strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDTIM,sTIME.c_str());
            //未登録なら測定日、登録日も更新（新規）する
                if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].SKTYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].SKTYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].ADDYMD).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].ADDYMD,sDATE.c_str());
                }
                if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].ADDTIM).Trim().Length() == 0)
                {
                    strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].ADDTIM,sTIME.c_str());
                }
            }
        }
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：データを保存する際、各々のロットの測定が終了しているかを調べる
//
//  機能説明
//  �@全ロットに対してロット毎の判定を行います
//  �A更新ロットが全測定を済ましているかを調べる。
//  パラメタ説明
//    なし。
//
//  戻り値
//    true:　更新ロットに未測定は含まれていない。
//    false：　更新ロットに未測定個所がある。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::ALL_INSPECT(void)
{
	int iCol;
    int iColCount,iRowCount;
    bool bALL_INSPECT;

    // 2004/09/13 A.Tamura アプリケーションエラーの為、try.. catch()を行なう。
	try
	{

	    bALL_INSPECT = true;

//�@全ロットに対してロット毎の判定を行います。

	    if(hCELLINFO_SOKU_SYUKA)
	    {
	        iColCount = SGr_vSOKU_SYUKA->ColCount;
	        iRowCount = SGr_vSOKU_SYUKA->RowCount;
	        for(iCol = 0; iCol < iColCount; iCol++)
	        {
	            GET_HANTEI(SGr_vSOKU_SYUKA, iCol);
	            if((pCELLINFO_SOKU_SYUKA[iCol*iRowCount + 0].JUDGE      == -1)
	            || (pCELLINFO_SOKU_SYUKA[iCol*iRowCount + 0].DISP_JUDGE == -1))
	            {
	                bALL_INSPECT = false;
	            }
	        }
	    }

	    if(hCELLINFO_RIRE_SYUKA && Form1->iRIRE_CNT != 0 )
	    {
	        iColCount = SGr_vRIRE_SYUKA->ColCount;
	        iRowCount = SGr_vRIRE_SYUKA->RowCount;
	        for(iCol = 0; iCol < iColCount; iCol++)
	        {
	            GET_HANTEI(SGr_vRIRE_SYUKA, iCol);
	            if((pCELLINFO_RIRE_SYUKA[iCol*iRowCount + 0].JUDGE      == -1)
	            || (pCELLINFO_RIRE_SYUKA[iCol*iRowCount + 0].DISP_JUDGE == -1))
	            {
	                bALL_INSPECT = false;
	            }
	        }
	    }

	    if( hCELLINFO_SOKU_SOZAI )
	    {
	        iColCount = SGr_vSOKU_SOZAI->ColCount;
	        iRowCount = SGr_vSOKU_SOZAI->RowCount;
	        for(iCol = 0; iCol < iColCount; iCol++)
	        {
	            GET_HANTEI(SGr_vSOKU_SOZAI, iCol);
	            if((pCELLINFO_SOKU_SOZAI[iCol*iRowCount + 0].JUDGE      == -1)
	            || (pCELLINFO_SOKU_SOZAI[iCol*iRowCount + 0].DISP_JUDGE == -1))
	            {
	                bALL_INSPECT = false;
	            }
	        }
	    }

	    if(hCELLINFO_RIRE_SOZAI && Form1->iRIRE_CNT != 0)
	    {
	        iColCount = SGr_vRIRE_SOZAI->ColCount;
	        iRowCount = SGr_vRIRE_SOZAI->RowCount;
	        for(iCol = 0; iCol < iColCount; iCol++)
	        {
	            GET_HANTEI(SGr_vRIRE_SOZAI, iCol);
	            if((pCELLINFO_RIRE_SOZAI[iCol*iRowCount + 0].JUDGE      == -1)
	            || (pCELLINFO_RIRE_SOZAI[iCol*iRowCount + 0].DISP_JUDGE == -1))
	            {
	                bALL_INSPECT = false;
	            }
	        }
	    }
	//---------------------------------------------------------------------------
	//  �A更新ロットが全測定を済ましているかを調べる。
	    bALL_INSPECT = true;

	    if(hCELLINFO_SOKU_SYUKA)
	    {
	        iColCount = SGr_vSOKU_SYUKA->ColCount;
	        iRowCount = SGr_vSOKU_SYUKA->RowCount;
	        for(iCol = 0; iCol < iColCount; iCol++)
	        {
	            if(pSOKU_KSD01_DATA[iCol].UPD_FLG == true)
	            {
	                if((pCELLINFO_SOKU_SYUKA[iCol*iRowCount + 0].JUDGE      == -1)
	                || (pCELLINFO_SOKU_SYUKA[iCol*iRowCount + 0].DISP_JUDGE == -1))
	                {
	                    bALL_INSPECT = false;
	                }
	            }
	        }
	    }

	    if(hCELLINFO_RIRE_SYUKA && Form1->iRIRE_CNT != 0 )
	    {
	        iColCount = SGr_vRIRE_SYUKA->ColCount;
	        iRowCount = SGr_vRIRE_SYUKA->RowCount;
	        for(iCol = 0; iCol < iColCount; iCol++)
	        {
	            if(pRIRE_KSD01_DATA[iCol].UPD_FLG == true)
	            {
	                if((pCELLINFO_RIRE_SYUKA[iCol*iRowCount + 0].JUDGE      == -1)
	                || (pCELLINFO_RIRE_SYUKA[iCol*iRowCount + 0].DISP_JUDGE == -1))
	                {
	                    bALL_INSPECT = false;
	                }
	            }
	        }
	    }

	    if( hCELLINFO_SOKU_SOZAI )
	    {
	        iColCount = SGr_vSOKU_SOZAI->ColCount;
	        iRowCount = SGr_vSOKU_SOZAI->RowCount;
	        for(iCol = 0; iCol < iColCount; iCol++)
	        {
	            if(pSOKU_KSD01_DATA[iCol].UPD_FLG == true)
	            {
	                if((pCELLINFO_SOKU_SOZAI[iCol*iRowCount + 0].JUDGE      == -1)
	                || (pCELLINFO_SOKU_SOZAI[iCol*iRowCount + 0].DISP_JUDGE == -1))
	                {
	                    bALL_INSPECT = false;
	                }
	            }
	        }
	    }

	    if(hCELLINFO_RIRE_SOZAI && Form1->iRIRE_CNT != 0)
	    {
	        iColCount = SGr_vRIRE_SOZAI->ColCount;
	        iRowCount = SGr_vRIRE_SOZAI->RowCount;
	        for(iCol = 0; iCol < iColCount; iCol++)
	        {
	            if(pRIRE_KSD01_DATA[iCol].UPD_FLG == true)
	            {
	                if((pCELLINFO_RIRE_SOZAI[iCol*iRowCount + 0].JUDGE      == -1)
	                || (pCELLINFO_RIRE_SOZAI[iCol*iRowCount + 0].DISP_JUDGE == -1))
	                {
	                    bALL_INSPECT = false;
	                }
	            }
	        }
	    }
	}
    catch ( ... )
    {
        return( false );
    }

	return( bALL_INSPECT );
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ１１：保存」ボタンを押した時の処理
//
//  機能説明
//    CtrlOFF:更新データの保存を行います。
//    CtrlON :無し
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
    TShiftState State;
    int iCol;
    bool bHan;
    AnsiString sBuf;
    TMsgDlgButtons MsgButton;
    unsigned short shtHoge=17;


    if( !BtnF11->Enabled )    return;
    //ロット入力判定
    if( !bINPUTLOT_OK )
    {
       	sBuf  = "有効なロットが入力されていない為保存できません。";
		MsgButton << mbOK;
        MessageDlg( sBuf, mtWarning	, MsgButton, 0);
        return;
    }
    // 2003/05/14 A.Tamura
    if( !BtnF11->Tag )
    {
        // 2003/10/30 A.Tamura 最後にフォーカスの有ったセルが編集モードの時、
        // 「値の保存」と「判定処理」を確実に行なうため、DrawCellを呼び出します。
		TGridDrawState DrawState;
    	AllGRID_DrawCell( SGr_vSOKU_SYUKA, SGr_vSOKU_SYUKA->Col, SGr_vSOKU_SYUKA->Row, SGr_vSOKU_SYUKA->CellRect(SGr_vSOKU_SYUKA->Col, SGr_vSOKU_SYUKA->Row), DrawState);
    	AllGRID_DrawCell( SGr_vRIRE_SYUKA, SGr_vRIRE_SYUKA->Col, SGr_vRIRE_SYUKA->Row, SGr_vRIRE_SYUKA->CellRect(SGr_vRIRE_SYUKA->Col, SGr_vRIRE_SYUKA->Row), DrawState);
    	AllGRID_DrawCell( SGr_vSOKU_SOZAI, SGr_vSOKU_SOZAI->Col, SGr_vSOKU_SOZAI->Row, SGr_vSOKU_SOZAI->CellRect(SGr_vSOKU_SOZAI->Col, SGr_vSOKU_SOZAI->Row), DrawState);
    	AllGRID_DrawCell( SGr_vRIRE_SOZAI, SGr_vRIRE_SOZAI->Col, SGr_vRIRE_SOZAI->Row, SGr_vRIRE_SOZAI->CellRect(SGr_vRIRE_SOZAI->Col, SGr_vRIRE_SOZAI->Row), DrawState);

        //測定画面終了時処理と見分けるためのフラグです。
        if( bQUIT_FLG == false )
        {
            //更新されているか
            if( UPDATE_CHECK())
            {
                //更新データの測定が全て終わっているか。
                if( !ALL_INSPECT())
                {
                    sBuf  = "未測定の項目が有ります。変更内容を保存しますか。";
        	    sBuf += "\n[は　い] 変更内容を保存して続行します。";
        	    sBuf += "\n[キャンセル] 保存処理の取り消し。";
                    MsgButton << mbYes << mbCancel;
                    switch( MessageDlg( sBuf, mtWarning	, MsgButton, 0) ){
                        // 「Yes」      保存
                        case mrYes:
                             break;
                         // 「Cancel」   キャンセル
                        case mrCancel:
                             return;
             	    }
                }
            }
        }
        else
        {
            //測定画面終了時はロットの判定を行います
            ALL_INSPECT();
        }

        //セル情報の保存
        ADD_SPACE();
    	bHan = Set_DB_SOKU();
    	bHan = Set_DB_RIRE();
    	bHan = Set_DB_SOKU_SOZAI();
    	bHan = Set_DB_RIRE_SOZAI();
        //保存が終了したので「アップデートフラグと保存フラグを初期化します
	if( hSOKU_KSD01_DATA)
	{
	    for(iCol = 0; iCol<SGr_tSOKU->ColCount;iCol++)
	    {
		pSOKU_KSD01_DATA[iCol].UPD_FLG = false;
		pSOKU_KSD01_DATA[iCol].SAVE_FLG = true;
	    }
    	}

	if( hRIRE_KSD01_DATA)
	{
	    for(iCol = 0; iCol<SGr_tRIRE->ColCount;iCol++)
	    {
		pRIRE_KSD01_DATA[iCol].UPD_FLG = false;
		pRIRE_KSD01_DATA[iCol].SAVE_FLG = true;
	    }
	}
	AllKeyUp(Sender ,shtHoge,State);	// ファンクションキーの状態を元に戻します。
    }
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：前項／次項／Enter押下時にセルを正しい位置に置く関数です
//
//  機能説明
//  灰色の部分を除いたセルで前項／次項にあたる部分を探します。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    char Key          :１文字のコード(VK_F13 or VK_F3 or VK_RETURN)
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::GridSetPointMove(TObject *Sender, char Key)
{
	int iRow,iCol,iX,iY,i1,i2; // ,fSts,iRoopCount,iTEMP_X,iTEMP_Y;
	int iORG_SOKU_SU,iRowTop,iORG_KOMK_NO,iORG_KIKI_NO;
	//int iNEW_KOMK_NO,iNEW_KIKI_NO,iNEW_SOKU_SU,iNEW_UNQ_NO;
	//int iORG_SKB_NO,iNEW_SKB_NO;
	int iTargetGrid;
	int iRowCount,iColCount;
    int iHANTEI;
	//bool bNEXTPOINT;
    //bool bKMOVE;
	bool bSTS;
	bool bFIRSTMOVE;
	//bNEXTPOINT = false;
    bKASOU_MOVE = false;
//グリッドの場所を求める
	iTargetGrid = WhereGrid();
//次項への移動
    if(Key == VK_RETURN || Key == VK_F3)
    {
		switch(iTargetGrid)
		{
        case 1:
        	iRow = Form1->SGr_vSOKU_SYUKA->Row;
        	iCol = Form1->SGr_vSOKU_SYUKA->Col;
			iRowCount = Form1->SGr_vSOKU_SYUKA->RowCount;
			iColCount = Form1->SGr_vSOKU_SYUKA->ColCount;
        	if(SGr_tSOKU->Cells[iCol][0].Trim().Length() == 0) return;
            if(iRowCount < 2 ) return;
			break;
        case 2:
        	iRow = Form1->SGr_vRIRE_SYUKA->Row;
        	iCol = Form1->SGr_vRIRE_SYUKA->Col;
			iRowCount = Form1->SGr_vRIRE_SYUKA->RowCount;
			iColCount = Form1->SGr_vRIRE_SYUKA->ColCount;
        	if(SGr_tRIRE->Cells[iCol][0].Trim().Length() == 0) return;
            if(Form1->iRIRE_CNT == 0 || iRowCount < 2 ) return;
			break;
		case 3:
        	iRow = Form1->SGr_vSOKU_SOZAI->Row;
        	iCol = Form1->SGr_vSOKU_SOZAI->Col;
			iRowCount = Form1->SGr_vSOKU_SOZAI->RowCount;
			iColCount = Form1->SGr_vSOKU_SOZAI->ColCount;
        	if(SGr_tSOKU->Cells[iCol][0].Trim().Length() == 0) return;
            if(iRowCount < 2 ) return;
			break;
		case 4:
        	iRow = Form1->SGr_vRIRE_SOZAI->Row;
        	iCol = Form1->SGr_vRIRE_SOZAI->Col;
			iRowCount = Form1->SGr_vRIRE_SOZAI->RowCount;
			iColCount = Form1->SGr_vRIRE_SOZAI->ColCount;
        	if(SGr_tRIRE->Cells[iCol][0].Trim().Length() == 0) return;
            if(Form1->iRIRE_CNT == 0 || iRowCount < 2 ) return;
			break;
		default:
            return; //2003.05.15 M.HIRAI
		}
/////////////////
        //移動の際に判定音を鳴らす 2003.06.19
        iHANTEI = CELL_HANTEI(Sender,iCol,iRow);
        switch(iHANTEI)
        {
        case 0:
            OK_BEEP(0);
            break;
        case 1:
            NG_BEEP(0);
            break;
        }
//////////////////
        if(!Form1->bCursolMove)
        {
	    //横方向への移動
			iRowTop = Get_GRAPHSTART_Info(iRow,iCol,iTargetGrid) + 1;
    	    iY = iRow;
        	iX = iCol;
	        bSTS = false;
            bFIRSTMOVE = true;
			switch(iTargetGrid)
			{
	        case 1:
				//同一項目数が何件続くかを取得（最大数）
            	iORG_SOKU_SU = 0;
                if(hCELLINFO_RIRE_SYUKA)
                {
                    for(i1=0;i1<SGr_vRIRE_SYUKA->ColCount;i1++)
                    {
                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                        {
                    	    iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        }
				    }
                }
                if(hCELLINFO_SOKU_SYUKA)
                {
                    for(i1=0;i1<SGr_vSOKU_SYUKA->ColCount;i1++)
                    {
                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                        {
                    	    iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        }
				    }
                } 
		        while( !bSTS )
    		    {
        			for(iX = iX;iX < iColCount; iX++)
            		{
                        //同一測定項目内で有効なセルがあるかを確認します。
            			for(iY = iY;iY < iRowTop+iORG_SOKU_SU; iY++)
	      	          	{
                            //移動可能条件として無い項目(KOMK_NO=0)、測定項目無し以外
    	            		//if((AnsiString(pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].INS_ON != false)
                            && (AnsiString(pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
    	            	    {
								if(bFIRSTMOVE == false )
								{
            	        			bSTS= true;
                	        		break;
								}
								else
                                //最初に見つけた位置は開始位置と同じなので除外します。
								{
									bFIRSTMOVE = false;
								}
                    		}
	                	}
    	            	if(bSTS) break;
        	        	iY = iRowTop;
            		}
                    //移動可能場所が見つからなかった場合は次の項目のパラメータを入手します。
	            	if(!bSTS)
    	        	{
        	    		iX = 0;
            	    	iY = iRowTop + iORG_SOKU_SU;	//次の項目への移動
						iRowTop = iY;
                		if(iY >= iRowCount )    //項目が無ければ一番上の項目を指します
						{
							iY = 1;
							iRowTop = 1;
						}
		            	iORG_SOKU_SU = 0;
                        if(hCELLINFO_RIRE_SYUKA)
                        {
        		            for(i1=0;i1<SGr_vRIRE_SYUKA->ColCount;i1++)
                		    {
		                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
        		                {
                		    	    iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	    }
	                        }
                        }
                        if(hCELLINFO_SOKU_SYUKA)
                        {
    	                    for(i1=0;i1<SGr_vSOKU_SYUKA->ColCount;i1++)
        	                {
            	        	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                	            {
                    	    	    iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	    }
						    }
                        }
	          		}
	        	}
            	//Form1->SBr1->Panels->Items[0]->Text = AnsiString(iX) + "," + AnsiString(iY);
                //Form1->SBr1->Update();
				i2 = iX-1;
				if(SGr_vSOKU_SYUKA->RowCount <= iY
                || SGr_vSOKU_SYUKA->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE = true;
					while( 1 )
					{
                    	SGr_vSOKU_SYUKA->Row = iY;
                        SGr_vSOKU_SYUKA->Col = iX;
						if(SGr_vSOKU_SYUKA->Row == iY && SGr_vSOKU_SYUKA->Col == iX) break;
						for(i1=0;i1 < iRowCount ; i1++)
						{
        					SGr_vSOKU_SYUKA->Row = i1;
                    		SGr_vSOKU_SYUKA->Col = iX;
							if( SGr_vSOKU_SYUKA->Col == iX)
							{
    	                		SGr_vSOKU_SYUKA->Row = iY;
        	                    break;
							}
                	    }
						break;
					}
					bKASOU_MOVE = false;
				}
				break;
            //以下はグリッドの位置が違うだけで同じ処理を行います。
	        case 2:
				//同一項目数が何件続くかを取得（最大数）
            	iORG_SOKU_SU = 0;
                if(hCELLINFO_RIRE_SYUKA)
                {
                    for(i1=0;i1<SGr_vRIRE_SYUKA->ColCount;i1++)
                    {
                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                        {
                    	    iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        }
				    }
                }
                if(hCELLINFO_SOKU_SYUKA)
                {
                    for(i1=0;i1<SGr_vSOKU_SYUKA->ColCount;i1++)
                    {
                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                        {
                    	    iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        }
				    }
                }
		        while( !bSTS )
    		    {
        			for(iX = iX;iX < iColCount; iX++)
            		{
            			for(iY = iY;iY < iRowTop+iORG_SOKU_SU; iY++)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].RESULT) != "不要")
    	            		//if((AnsiString(pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].INS_ON != false)
                        //測定項目無しも判定に追加
                            && (AnsiString(pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
								if(bFIRSTMOVE == false )
								{
            	        			bSTS= true;
                	        		break;
								}
								else
								{
									bFIRSTMOVE = false;
								}
                    		}
	                	}
    	            	if(bSTS) break;
        	        	iY = iRowTop;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = 0;
            	    	iY = iRowTop + iORG_SOKU_SU;	//次の項目への移動
						iRowTop = iY;
                		if(iY >= iRowCount )    //項目が無ければ一番上の項目を指します
						{
							iY = 1;
							iRowTop = 1;
						}
		            	iORG_SOKU_SU = 0;
                        if(hCELLINFO_RIRE_SYUKA)
                        {
        		            for(i1=0;i1<SGr_vRIRE_SYUKA->ColCount;i1++)
                		    {
		                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
        		                {
                		    	    iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	    }
	                        }
                        }
                        if(hCELLINFO_SOKU_SYUKA)
                        {
    	                    for(i1=0;i1<SGr_vSOKU_SYUKA->ColCount;i1++)
        	                {
            	        	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                	            {
                    	    	    iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	    }
						    }
                        }
	          		}
	        	}
            	//Form1->SBr1->Panels->Items[0]->Text = AnsiString(iX) + "," + AnsiString(iY);
                //Form1->SBr1->Update();
				i2 = iX-1;
				if(SGr_vRIRE_SYUKA->RowCount <= iY
                || SGr_vRIRE_SYUKA->ColCount <= iX)
                {
					break;
				}
				else
				{
					bKASOU_MOVE = true;
					while( 1 )
					{
                    	SGr_vRIRE_SYUKA->Row = iY;
                        SGr_vRIRE_SYUKA->Col = iX;
						if(SGr_vRIRE_SYUKA->Row == iY && SGr_vRIRE_SYUKA->Col == iX) break;
						for(i1=0;i1 < iRowCount ; i1++)
						{
        					SGr_vRIRE_SYUKA->Row = i1;
                    		SGr_vRIRE_SYUKA->Col = iX;
							if( SGr_vRIRE_SYUKA->Col == iX)
							{
        	            		SGr_vRIRE_SYUKA->Row = iY;
            	                break;
							}
                    	}
						break;
					}
					bKASOU_MOVE = false;
				}
				break;
	        case 3:
				//同一項目数が何件続くかを取得（最大数）
            	iORG_SOKU_SU = 0;
                if(hCELLINFO_RIRE_SOZAI)
                {
                    for(i1=0;i1<SGr_vRIRE_SOZAI->ColCount;i1++)
                    {
                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                        {
                    	    iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        }
				    }
                }
                if(hCELLINFO_SOKU_SOZAI)
                {
                    for(i1=0;i1<SGr_vSOKU_SOZAI->ColCount;i1++)
                    {
                    	if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                        {
                        	iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        }
				    }
                }
		        while( !bSTS )
    		    {
        			for(iX = iX;iX < iColCount; iX++)
            		{
            			for(iY = iY;iY < iRowTop+iORG_SOKU_SU; iY++)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].RESULT) != "不要")
    	            		//if((AnsiString(pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].INS_ON != false)
                        //測定項目無しも判定に追加
                            && (AnsiString(pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
								if(bFIRSTMOVE == false )
								{
            	        			bSTS= true;
                	        		break;
								}
								else
								{
									bFIRSTMOVE = false;
								}
                    		}
	                	}
    	            	if(bSTS) break;
        	        	iY = iRowTop;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = 0;
            	    	iY = iRowTop + iORG_SOKU_SU;	//次の項目への移動
						iRowTop = iY;
                		if(iY >= iRowCount )    //項目が無ければ一番上の項目を指します
						{
							iY = 1;
							iRowTop = 1;
						}
		            	iORG_SOKU_SU = 0;
                        if(hCELLINFO_RIRE_SOZAI)
                        {
        		            for(i1=0;i1<SGr_vRIRE_SOZAI->ColCount;i1++)
                		    {
		                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
        		                {
                		    	    iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	    }
	                        }
                        }
                        if(hCELLINFO_SOKU_SOZAI)
                        {
    	                    for(i1=0;i1<SGr_vSOKU_SOZAI->ColCount;i1++)
        	                {
            	        	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                	            {
                    	    	    iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	    }
						    }
                        }
	          		}
	        	}
            	//Form1->SBr1->Panels->Items[0]->Text = AnsiString(iX) + "," + AnsiString(iY);
                //Form1->SBr1->Update();
				i2 = iX-1;
				if(SGr_vSOKU_SOZAI->RowCount <= iY
                || SGr_vSOKU_SOZAI->ColCount <= iX)
                {
					break;
				}
				else
                {
                	bKASOU_MOVE = true;
					while( 1 )
					{
                    	SGr_vSOKU_SOZAI->Row = iY;
                        SGr_vSOKU_SOZAI->Col = iX;
						if(SGr_vSOKU_SOZAI->Row == iY && SGr_vSOKU_SOZAI->Col == iX) break;
						for(i1=0;i1 < iRowCount ; i1++)
						{
        					SGr_vSOKU_SOZAI->Row = i1;
                    		SGr_vSOKU_SOZAI->Col = iX;
							if( SGr_vSOKU_SOZAI->Col == iX)
							{
    	                		SGr_vSOKU_SOZAI->Row = iY;
        	                    break;
							}
                	    }
						break;
					}
					bKASOU_MOVE = false;
				}
				break;
	        case 4:
			//同一項目数が何件続くかを取得（最大数）
            	iORG_SOKU_SU = 0;
                if( hCELLINFO_RIRE_SOZAI)
                {
                    for(i1=0;i1<SGr_vRIRE_SOZAI->ColCount;i1++)
                    {
                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                        {
                    	    iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        }
				    }
                }
                if( hCELLINFO_SOKU_SOZAI)
                {
                    for(i1=0;i1<SGr_vSOKU_SOZAI->ColCount;i1++)
                    {
                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                        {
                    	    iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        }
				    }
                }
		        while( !bSTS )
    		    {
        			for(iX = iX;iX < iColCount; iX++)
            		{
            			for(iY = iY;iY < iRowTop+iORG_SOKU_SU; iY++)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].RESULT) != "不要")
    	            		//if((AnsiString(pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].INS_ON != false)
                        //測定項目無しも判定に追加
                            && (AnsiString(pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
								if(bFIRSTMOVE == false )
								{
            	        			bSTS= true;
                	        		break;
								}
								else
								{
									bFIRSTMOVE = false;
								}
                    		}
	                	}
    	            	if(bSTS) break;
        	        	iY = iRowTop;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = 0;
            	    	iY = iRowTop + iORG_SOKU_SU;	//次の項目への移動
						iRowTop = iY;
                		if(iY >= iRowCount )    //項目が無ければ一番上の項目を指します
						{
							iY = 1;
							iRowTop = 1;
						}
		            	iORG_SOKU_SU = 0;
                        if(hCELLINFO_RIRE_SOZAI)
                        {
        		            for(i1=0;i1<SGr_vRIRE_SOZAI->ColCount;i1++)
                		    {
		                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
        		                {
                		    	    iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	    }
	                        }
                        }
                        if(hCELLINFO_SOKU_SOZAI)
                        {
    	                    for(i1=0;i1<SGr_vSOKU_SOZAI->ColCount;i1++)
        	                {
            	        	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                	            {
                    	    	    iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	    }
						    }
                        }                      
	          		}
	        	}
            	//Form1->SBr1->Panels->Items[0]->Text = AnsiString(iX) + "," + AnsiString(iY);
                //Form1->SBr1->Update();
				i2 = iX-1;
				if(SGr_vRIRE_SOZAI->RowCount <= iY
                || SGr_vRIRE_SOZAI->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE =true;
					while( 1 )
					{
                    	SGr_vRIRE_SOZAI->Row = iY;
                        SGr_vRIRE_SOZAI->Col = iX;
						if(SGr_vRIRE_SOZAI->Row == iY && SGr_vRIRE_SOZAI->Col == iX) break;
						for(i1=0;i1 < iRowCount ; i1++)
						{
        					SGr_vRIRE_SOZAI->Row = i1;
                    		SGr_vRIRE_SOZAI->Col = iX;
							if( SGr_vRIRE_SOZAI->Col == iX)
							{
    	                		SGr_vRIRE_SOZAI->Row = iY;
        	                    break;
							}
                	    }
						break;
					}
					bKASOU_MOVE = false;
				}
				break;
			}
    	}
		else
		{
	//縦方向への移動
			iRowTop = Get_GRAPHSTART_Info(iRow,0,iTargetGrid);
    	    iORG_KOMK_NO = AnsiString(pInfoGlaph.KOMK_NO).ToIntDef(0);
        	iORG_KIKI_NO = AnsiString(pInfoGlaph.KIKI_NO).ToIntDef(0);
	        iORG_SOKU_SU = AnsiString(pInfoGlaph.SOKU_SU).ToIntDef(0);
    	    iY = iRow+1;
        	iX = iCol;
	        bSTS = false;
			switch(iTargetGrid)
			{
	        case 1:
		        while( !bSTS )
    		    {
        			for(iX = iX;iX < iColCount; iX++)
            		{
            			for(iY = iY;iY < iRowCount; iY++)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].RESULT) != "不要")
    	            		//if((AnsiString(pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].INS_ON != false)
                        //測定項目無しも判定に追加
                            && (AnsiString(pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
            	        		bSTS= true;
                	        	break;
                    		}
	                	}
						if( !bSTS ) iY = 1;
						if( bSTS ) break;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = 0;
            	    	iY = 1;
            		}
	        	}
				if(SGr_vSOKU_SYUKA->RowCount <= iY
                || SGr_vSOKU_SYUKA->ColCount <= iX)
                {
					break;
				}
				else
                {
					while( 1 )
					{
        				SGr_vSOKU_SYUKA->Col = iX;
        				SGr_vSOKU_SYUKA->Row = iY;
						if( SGr_vSOKU_SYUKA->Col == iX && SGr_vSOKU_SYUKA->Row == iY) break;
					}
				}
				break;
	        case 2:
		        while( !bSTS )
    		    {
        			for(iX = iX;iX < iColCount; iX++)
            		{
            			for(iY = iY;iY < iRowCount; iY++)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].RESULT) != "不要")
    	            		//if((AnsiString(pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].INS_ON != false)
                        //測定項目無しも判定に追加
                            && (AnsiString(pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
            	        		bSTS= true;
                	        	break;
                    		}
	                	}
						if( !bSTS ) iY = 1;
						if( bSTS ) break;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = 0;
            	    	iY = 1;
            		}
	        	}
				if(SGr_vRIRE_SYUKA->RowCount <= iY
                || SGr_vRIRE_SYUKA->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE = true;
					while( 1 )
					{
        				SGr_vRIRE_SYUKA->Col = iX;
        				SGr_vRIRE_SYUKA->Row = iY;
						if( SGr_vRIRE_SYUKA->Col == iX && SGr_vRIRE_SYUKA->Row == iY) break;
					}
					bKASOU_MOVE = false;
				}
				break;
	        case 3:
		        while( !bSTS )
    		    {
        			for(iX = iX;iX < iColCount; iX++)
            		{
            			for(iY = iY;iY < iRowCount; iY++)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].RESULT) != "不要")
    	            		//if((AnsiString(pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].INS_ON != false)
                        //測定項目無しも判定に追加
                            && (AnsiString(pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
            	        		bSTS= true;
                	        	break;
                    		}
	                	}
						if( !bSTS ) iY = 1;
						if( bSTS ) break;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = 0;
            	    	iY = 1;
            		}
	        	}
				if(SGr_vSOKU_SOZAI->RowCount <= iY
                || SGr_vSOKU_SOZAI->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE = true;
					while( 1 )
					{
        				SGr_vSOKU_SOZAI->Col = iX;
        				SGr_vSOKU_SOZAI->Row = iY;
						if( SGr_vSOKU_SOZAI->Col == iX && SGr_vSOKU_SOZAI->Row == iY) break;
					}
					bKASOU_MOVE = false;
				}
				break;
	        case 4:
		        while( !bSTS )
    		    {
        			for(iX = iX;iX < iColCount; iX++)
            		{
            			for(iY = iY;iY < iRowCount; iY++)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].RESULT) != "不要")
    	            		//if((AnsiString(pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].INS_ON != false)
                        //測定項目無しも判定に追加
                            && (AnsiString(pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
            	        		bSTS= true;
                	        	break;
                    		}
	                	}
						if( !bSTS ) iY = 1;
						if( bSTS ) break;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = 0;
            	    	iY = 1;
            		}
	        	}
				if(SGr_vRIRE_SOZAI->RowCount <= iY
                || SGr_vRIRE_SOZAI->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE = true;
					while( 1 )
					{
        				SGr_vRIRE_SOZAI->Col = iX;
        				SGr_vRIRE_SOZAI->Row = iY;
						if( SGr_vRIRE_SOZAI->Col == iX && SGr_vRIRE_SOZAI->Row == iY) break;
					}
					bKASOU_MOVE = false;
				}
				break;
    		}
    	}
    }
    //Ｆ２の処理です
    if(Key == VK_F13)
    {
    	switch(iTargetGrid)
		{
        case 1:
        	iRow = Form1->SGr_vSOKU_SYUKA->Row;
        	iCol = Form1->SGr_vSOKU_SYUKA->Col;
			iRowCount = Form1->SGr_vSOKU_SYUKA->RowCount;
			iColCount = Form1->SGr_vSOKU_SYUKA->ColCount;
        	if(SGr_tSOKU->Cells[iCol][0].Trim().Length() == 0) return;
            if(iRowCount < 2 ) return;
			break;
        case 2:
        	iRow = Form1->SGr_vRIRE_SYUKA->Row;
        	iCol = Form1->SGr_vRIRE_SYUKA->Col;
			iRowCount = Form1->SGr_vRIRE_SYUKA->RowCount;
			iColCount = Form1->SGr_vRIRE_SYUKA->ColCount;
        	if(SGr_tRIRE->Cells[iCol][0].Trim().Length() == 0) return;
            if(Form1->iRIRE_CNT == 0 || iRowCount < 2 ) return;
			break;
		case 3:
        	iRow = Form1->SGr_vSOKU_SOZAI->Row;
        	iCol = Form1->SGr_vSOKU_SOZAI->Col;
			iRowCount = Form1->SGr_vSOKU_SOZAI->RowCount;
			iColCount = Form1->SGr_vSOKU_SOZAI->ColCount;
        	if(SGr_tSOKU->Cells[iCol][0].Trim().Length() == 0) return;
            if(iRowCount < 2 ) return;
			break;
		case 4:
        	iRow = Form1->SGr_vRIRE_SOZAI->Row;
        	iCol = Form1->SGr_vRIRE_SOZAI->Col;
			iRowCount = Form1->SGr_vRIRE_SOZAI->RowCount;
			iColCount = Form1->SGr_vRIRE_SOZAI->ColCount;
        	if(SGr_tRIRE->Cells[iCol][0].Trim().Length() == 0) return;
            if(Form1->iRIRE_CNT == 0 || iRowCount < 2 ) return;
			break;
		default:
            return; //2003.05.15 M.HIRAI
		}
/////////////////
        //移動の際に判定音を鳴らす 2003.06.19
        iHANTEI = CELL_HANTEI(Sender,iCol,iRow);
        switch(iHANTEI)
        {
        case 0:
            OK_BEEP(0);
            break;
        case 1:
            NG_BEEP(0);
            break;
        }
////////////////
        if(!Form1->bCursolMove)
        {
	//横方向への移動
			iRowTop = Get_GRAPHSTART_Info(iRow,0,iTargetGrid)+1;
    	    iORG_KOMK_NO = AnsiString(pInfoGlaph.KOMK_NO).ToIntDef(0);
        	iORG_KIKI_NO = AnsiString(pInfoGlaph.KIKI_NO).ToIntDef(0);
	        iORG_SOKU_SU = AnsiString(pInfoGlaph.SOKU_SU).ToIntDef(0);
    	    iY = iRow;
        	iX = iCol;
	        bSTS = false;
			switch(iTargetGrid)
			{
	        case 1:
				//同一項目数が何件続くかを取得（最大数）
            	iORG_SOKU_SU = 0;
                if(Form1->iRIRE_CNT != 0)
                {
                    for(i1=0;i1<SGr_vRIRE_SYUKA->ColCount;i1++)
                    {
                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                        {
                    	    iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        }
				    }
                }
                for(i1=0;i1<SGr_vSOKU_SYUKA->ColCount;i1++)
                {
                	if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                    {
                    	iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                    }
				}
		        while( !bSTS )
    		    {
                    //ここからのForNextが減算していること以外はＦ３／Returnキーの動作と同じです。
        			for(iX = iX;iX >= 0; iX--)
            		{
            			for(iY = iY;iY >= iRowTop; iY--)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].RESULT) != "不要")
    	            		//if((AnsiString(pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].INS_ON != false)
                        //測定項目無しも判定に追加
                            && (AnsiString(pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
								if(bFIRSTMOVE == false )
								{
            	        			bSTS= true;
                	        		break;
								}
								else
								{
									bFIRSTMOVE = false;
								}
                    		}
	                	}
    	            	if(bSTS) break;
        	        	iY = iRowTop+iORG_SOKU_SU-1;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = iColCount-1;
            	    	iY = iRowTop - 1;	//次の項目への移動
						iRowTop = Get_GRAPHSTART_Info(iY,0,iTargetGrid) + 1;
                		if(iY < 1 )    //項目が無ければ一番上の項目を指します
						{
							iY = iRowCount-1;
							iRowTop = Get_GRAPHSTART_Info(iY,0,iTargetGrid) + 1;
						}
		            	iORG_SOKU_SU = 0;
                        if(Form1->iRIRE_CNT != 0)
                        {
        		            for(i1=0;i1<SGr_vRIRE_SYUKA->ColCount;i1++)
                		    {
		                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
        		                {
                		    	    iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	    }
	                        }
                        }
    	                for(i1=0;i1<SGr_vSOKU_SYUKA->ColCount;i1++)
        	            {
            	        	if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                	        {
                    	    	iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	}
						}
	          		}
	        	}
            	//Form1->SBr1->Panels->Items[0]->Text = AnsiString(iX) + "," + AnsiString(iY);
                //Form1->SBr1->Update();
				i2 = iX-1;
				if(SGr_vSOKU_SYUKA->RowCount <= iY
                || SGr_vSOKU_SYUKA->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE = true;
					while( 1 )
					{
						SGr_vSOKU_SYUKA->Row = iY;
						SGr_vSOKU_SYUKA->Col = iX;
						if(SGr_vSOKU_SYUKA->Col == iX && SGr_vSOKU_SYUKA->Row == iY) break;
						for(i1=0;i1 < iRowCount ; i1++)
						{
    	    				SGr_vSOKU_SYUKA->Row = i1;
        	            	SGr_vSOKU_SYUKA->Col = iX;
							if( SGr_vSOKU_SYUKA->Col == iX)
							{
                    			SGr_vSOKU_SYUKA->Row = iY;
                        	    break;
							}
    	                }
						break;
					}
					bKASOU_MOVE = false;
				}
				break;
	        case 2:
				//同一項目数が何件続くかを取得（最大数）
            	iORG_SOKU_SU = 0;
                for(i1=0;i1<SGr_vRIRE_SYUKA->ColCount;i1++)
                {
                	if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                    {
                    	iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                    }
				}
                for(i1=0;i1<SGr_vSOKU_SYUKA->ColCount;i1++)
                {
                	if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                    {
                    	iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                    }
				}
		        while( !bSTS )
    		    {
        			for(iX = iX;iX >= 0; iX--)
            		{
            			for(iY = iY;iY >= iRowTop; iY--)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].RESULT) != "不要")
    	            		//if((AnsiString(pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].INS_ON != false)
                        //測定項目無しも判定に追加
                            && (AnsiString(pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
								if(bFIRSTMOVE == false )
								{
            	        			bSTS= true;
                	        		break;
								}
								else
								{
									bFIRSTMOVE = false;
								}
                    		}
	                	}
    	            	if(bSTS) break;
        	        	iY = iRowTop+iORG_SOKU_SU-1;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = iColCount-1;
            	    	iY = iRowTop - 1;	//次の項目への移動
						iRowTop = Get_GRAPHSTART_Info(iY,0,iTargetGrid) + 1;
                		if(iY < 1 )    //項目が無ければ一番上の項目を指します
						{
							iY = iRowCount-1;
							iRowTop = Get_GRAPHSTART_Info(iY,0,iTargetGrid) + 1;
						}
		            	iORG_SOKU_SU = 0;
        		        for(i1=0;i1<SGr_vRIRE_SYUKA->ColCount;i1++)
                		{
		                	if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
        		            {
                		    	iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	}
	                    }
    	                for(i1=0;i1<SGr_vSOKU_SYUKA->ColCount;i1++)
        	            {
            	        	if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                	        {
                    	    	iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SYUKA[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	}
						}
	          		}
	        	}
            	//Form1->SBr1->Panels->Items[0]->Text = AnsiString(iX) + "," + AnsiString(iY);
                //Form1->SBr1->Update();
				i2 = iX-1;
				if(SGr_vRIRE_SYUKA->RowCount <= iY
                || SGr_vRIRE_SYUKA->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE = true;
					while( 1 )
					{
						SGr_vRIRE_SYUKA->Row = iY;
						SGr_vRIRE_SYUKA->Col = iX;
						if(SGr_vRIRE_SYUKA->Col == iX && SGr_vRIRE_SYUKA->Row == iY) break;
						for(i1=0;i1 < iRowCount ; i1++)
						{
    	    				SGr_vRIRE_SYUKA->Row = i1;
        	            	SGr_vRIRE_SYUKA->Col = iX;
							if( SGr_vRIRE_SYUKA->Col == iX)
							{
                    			SGr_vRIRE_SYUKA->Row = iY;
                        	    break;
							}
    	                }
						break;
					}
					bKASOU_MOVE = false;
				}
				break;
	        case 3:
				//同一項目数が何件続くかを取得（最大数）
            	iORG_SOKU_SU = 0;
                if(Form1->iRIRE_CNT != 0)
                {
                    for(i1=0;i1<SGr_vRIRE_SOZAI->ColCount;i1++)
                    {
                    	if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                        {
                        	iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        }
				    }
                }
                for(i1=0;i1<SGr_vSOKU_SOZAI->ColCount;i1++)
                {
                	if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                    {
                    	iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                    }
				}
		        while( !bSTS )
    		    {
        			for(iX = iX;iX >= 0; iX--)
            		{
            			for(iY = iY;iY >= iRowTop; iY--)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].RESULT) != "不要")
    	            		//if((AnsiString(pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].INS_ON != false)
                        //測定項目無しも判定に追加
                            && (AnsiString(pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
								if(bFIRSTMOVE == false )
								{
            	        			bSTS= true;
                	        		break;
								}
								else
								{
									bFIRSTMOVE = false;
								}
                    		}
	                	}
    	            	if(bSTS) break;
        	        	iY = iRowTop+iORG_SOKU_SU-1;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = iColCount-1;
            	    	iY = iRowTop - 1;	//次の項目への移動
						iRowTop = Get_GRAPHSTART_Info(iY,0,iTargetGrid) + 1;
                		if(iY < 1 )    //項目が無ければ一番上の項目を指します
						{
							iY = iRowCount-1;
							iRowTop = Get_GRAPHSTART_Info(iY,0,iTargetGrid) + 1;
						}
		            	iORG_SOKU_SU = 0;
                        if(Form1->iRIRE_CNT != 0)
                        {
        		            for(i1=0;i1<SGr_vRIRE_SOZAI->ColCount;i1++)
                		    {
		                	    if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
        		                {
                		    	    iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	    }
	                        }
                        }
    	                for(i1=0;i1<SGr_vSOKU_SOZAI->ColCount;i1++)
        	            {
            	        	if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                	        {
                    	    	iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	}
						}
	          		}
	        	}
            	//Form1->SBr1->Panels->Items[0]->Text = AnsiString(iX) + "," + AnsiString(iY);
                //Form1->SBr1->Update();
				i2 = iX-1;
				if(SGr_vSOKU_SOZAI->RowCount <= iY
                || SGr_vSOKU_SOZAI->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE = true;
					while( 1 )
					{
						SGr_vSOKU_SOZAI->Row = iY;
						SGr_vSOKU_SOZAI->Col = iX;
						if(SGr_vSOKU_SOZAI->Col == iX && SGr_vSOKU_SOZAI->Row == iY) break;
						for(i1=0;i1 < iRowCount ; i1++)
						{
    	    				SGr_vSOKU_SOZAI->Row = i1;
        	            	SGr_vSOKU_SOZAI->Col = iX;
							if( SGr_vSOKU_SOZAI->Col == iX)
							{
                    			SGr_vSOKU_SOZAI->Row = iY;
                            	break;
							}
	                    }
						break;
					}
					bKASOU_MOVE = false;
				}
				break;
	        case 4:
				//同一項目数が何件続くかを取得（最大数）
            	iORG_SOKU_SU = 0;
                for(i1=0;i1<SGr_vRIRE_SOZAI->ColCount;i1++)
                {
                	if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                    {
                    	iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                    }
				}
                for(i1=0;i1<SGr_vSOKU_SOZAI->ColCount;i1++)
                {
                	if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                    {
                    	iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                    }
				}
		        while( !bSTS )
    		    {
        			for(iX = iX;iX >= 0; iX--)
            		{
            			for(iY = iY;iY >= iRowTop; iY--)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].RESULT) != "不要")
    	            		//if((AnsiString(pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].INS_ON != false)
                        //測定項目無しも判定に追加
                            && (AnsiString(pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
								if(bFIRSTMOVE == false )
								{
            	        			bSTS= true;
                	        		break;
								}
								else
								{
									bFIRSTMOVE = false;
								}
                    		}
	                	}
    	            	if(bSTS) break;
        	        	iY = iRowTop+iORG_SOKU_SU-1;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = iColCount-1;
            	    	iY = iRowTop - 1;	//次の項目への移動
						iRowTop = Get_GRAPHSTART_Info(iY,0,iTargetGrid) + 1;
                		if(iY < 1 )    //項目が無ければ一番上の項目を指します
						{
							iY = iRowCount-1;
							iRowTop = Get_GRAPHSTART_Info(iY,0,iTargetGrid) + 1;
						}
		            	iORG_SOKU_SU = 0;
        		        for(i1=0;i1<SGr_vRIRE_SOZAI->ColCount;i1++)
                		{
		                	if( iORG_SOKU_SU < AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
        		            {
                		    	iORG_SOKU_SU = AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	}
	                    }
    	                for(i1=0;i1<SGr_vSOKU_SOZAI->ColCount;i1++)
        	            {
            	        	if( iORG_SOKU_SU < AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0))
                	        {
                    	    	iORG_SOKU_SU = AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iY].SOKU_SU).ToIntDef(0);
                        	}
						}
	          		}
	        	}
            	//Form1->SBr1->Panels->Items[0]->Text = AnsiString(iX) + "," + AnsiString(iY);
                //Form1->SBr1->Update();
				i2 = iX-1;
				if(SGr_vRIRE_SOZAI->RowCount <= iY
                || SGr_vRIRE_SOZAI->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE = true;
					while( 1 )
					{
						SGr_vRIRE_SOZAI->Row = iY;
						SGr_vRIRE_SOZAI->Col = iX;
						if(SGr_vRIRE_SOZAI->Col == iX && SGr_vRIRE_SOZAI->Row == iY) break;
						for(i1=0;i1 < iRowCount ; i1++)
						{
    	    				SGr_vRIRE_SOZAI->Row = i1;
        	            	SGr_vRIRE_SOZAI->Col = iX;
							if( SGr_vRIRE_SOZAI->Col == iX)
							{
                    			SGr_vRIRE_SOZAI->Row = iY;
                        	    break;
							}
    	                }
						break;
					}
                    bKASOU_MOVE = false;
				}
				break;
			}
		}
		else
		{
	//縦方向への移動
			iRowTop = Get_GRAPHSTART_Info(iRow,0,iTargetGrid);
    	    iORG_KOMK_NO = AnsiString(pInfoGlaph.KOMK_NO).ToIntDef(0);
        	iORG_KIKI_NO = AnsiString(pInfoGlaph.KIKI_NO).ToIntDef(0);
	        iORG_SOKU_SU = AnsiString(pInfoGlaph.SOKU_SU).ToIntDef(0);
    	    iY = iRow-1;
        	iX = iCol;
	        bSTS = false;
			switch(iTargetGrid)
			{
	        case 1:
		        while( !bSTS )
    		    {
        			for(iX = iX;iX >= 0; iX--)
            		{
            			for(iY = iY;iY > 0; iY--)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].INS_ON != false)
                        //測定項目無しも判定に追加
                            && (AnsiString(pCELLINFO_SOKU_SYUKA[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
            	        		bSTS= true;
                	        	break;
                    		}
	                	}
						if( !bSTS ) iY = iRowCount-1;
						if( bSTS ) break;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = iColCount-1;
            	    	iY = iRowCount-1;
            		}
	        	}
				if(SGr_vSOKU_SYUKA->RowCount <= iY
                || SGr_vSOKU_SYUKA->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE = true;
					while( 1 )
					{
						SGr_vSOKU_SYUKA->Row = iY;
						SGr_vSOKU_SYUKA->Col = iX;
						if(SGr_vSOKU_SYUKA->Col == iX && SGr_vSOKU_SYUKA->Row == iY) break;
						for(i1=0;i1 < iRowCount ; i1++)
						{
    	    				SGr_vSOKU_SYUKA->Row = i1;
        	            	SGr_vSOKU_SYUKA->Col = iX;
							if( SGr_vSOKU_SYUKA->Col == iX)
							{
                    			SGr_vSOKU_SYUKA->Row = iY;
                        	    break;
							}
    	                }
						break;
					}
                    bKASOU_MOVE = false;
				}
                break;
	        case 2:
		        while( !bSTS )
    		    {
        			for(iX = iX;iX >= 0; iX--)
            		{
            			for(iY = iY;iY > 0 ; iY--)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].INS_ON != false)
                        //測定項目無しも判定に追加
                            && (AnsiString(pCELLINFO_RIRE_SYUKA[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
            	        		bSTS= true;
                	        	break;
                    		}                             
	                	}
						if( !bSTS ) iY = iRowCount-1;
						if( bSTS ) break;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = iColCount-1;
            	    	iY = iRowCount-1;
            		}
	        	}
				if(SGr_vRIRE_SYUKA->RowCount <= iY
                || SGr_vRIRE_SYUKA->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE = true;
					while( 1 )
					{
						SGr_vRIRE_SYUKA->Row = iY;
						SGr_vRIRE_SYUKA->Col = iX;
						if(SGr_vRIRE_SYUKA->Col == iX && SGr_vRIRE_SYUKA->Row == iY) break;
						for(i1=0;i1 < iRowCount ; i1++)
						{
    	    				SGr_vRIRE_SYUKA->Row = i1;
        	            	SGr_vRIRE_SYUKA->Col = iX;
							if( SGr_vRIRE_SYUKA->Col == iX)
							{
                    			SGr_vRIRE_SYUKA->Row = iY;
                        	    break;
							}
    	                }
						break;
					}
					bKASOU_MOVE = false;
				}
				break;
	        case 3:
		        while( !bSTS )
    		    {
        			for(iX = iX;iX >= 0; iX--)
            		{
            			for(iY = iY;iY > 0; iY--)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].INS_ON != false)
                        //測定項目無しも判定に追加
                            && (AnsiString(pCELLINFO_SOKU_SOZAI[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
            	        		bSTS= true;
                	        	break;
                    		}
	                	}
						if( !bSTS ) iY = iRowCount-1;
						if( bSTS ) break;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = iColCount - 1;
            	    	iY = iRowCount - 1;
            		}
	        	}
				if(SGr_vSOKU_SOZAI->RowCount <= iY
                || SGr_vSOKU_SOZAI->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE = true;
					while( 1 )
					{
						SGr_vSOKU_SOZAI->Row = iY;
						SGr_vSOKU_SOZAI->Col = iX;
						if(SGr_vSOKU_SOZAI->Col == iX && SGr_vSOKU_SOZAI->Row == iY) break;
						for(i1=0;i1 < iRowCount ; i1++)
						{
    	    				SGr_vSOKU_SOZAI->Row = i1;
        	            	SGr_vSOKU_SOZAI->Col = iX;
							if( SGr_vSOKU_SOZAI->Col == iX)
							{
                    			SGr_vSOKU_SOZAI->Row = iY;
                        	    break;
							}
    	                }
						break;
					}
					bKASOU_MOVE = false;
				}
				break;
	        case 4:
		        while( !bSTS )
    		    {
        			for(iX = iX;iX >= 0; iX--)
            		{
            			for(iY = iY;iY > 0; iY--)
	      	          	{
    	            		//if((AnsiString(pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].KOMK_NO).ToIntDef(0) != 0)
    	            		if((pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].INS_ON != false)
                        //測定項目無しも判定に追加
                            && (AnsiString(pCELLINFO_RIRE_SOZAI[iX*iRowCount+iY].SOKU_FLG).ToIntDef(0) != 0))
        	            	{
            	        		bSTS= true;
                	        	break;
                    		}
	                	}
						if( !bSTS ) iY = iRowCount-1;
						if( bSTS ) break;
            		}
	            	if(!bSTS)
    	        	{
        	    		iX = iColCount-1;
            	    	iY = iRowCount-1;
            		}
	        	}
				if(SGr_vRIRE_SOZAI->RowCount <= iY
                || SGr_vRIRE_SOZAI->ColCount <= iX)
                {
					break;
				}
				else
                {
					bKASOU_MOVE = true;
					while( 1 )
					{
						SGr_vRIRE_SOZAI->Row = iY;
						SGr_vRIRE_SOZAI->Col = iX;
						if(SGr_vRIRE_SOZAI->Col == iX && SGr_vRIRE_SOZAI->Row == iY) break;
						for(i1=0;i1 < iRowCount ; i1++)
						{
    	    				SGr_vRIRE_SOZAI->Row = i1;
        	            	SGr_vRIRE_SOZAI->Col = iX;
							if( SGr_vRIRE_SOZAI->Col == iX)
							{
                    			SGr_vRIRE_SOZAI->Row = iY;
                        	    break;
							}
    	                }
						break;
					}
					bKASOU_MOVE = false;
				}
				break;
    		}
    	}
    }
    //2003.05.15　M.HIRAI
    //ボタンクリック時の対応（グリッドへフォーカス移動）
	switch(iTargetGrid)
    {
    case 1:
    	Form1->SGr_vSOKU_SYUKA->SetFocus();
        break;
    case 2:
    	Form1->SGr_vRIRE_SYUKA->SetFocus();
        break;
    case 3:
    	Form1->SGr_vSOKU_SOZAI->SetFocus();
        break;
    case 4:
    	Form1->SGr_vRIRE_SOZAI->SetFocus();
        break;
    default:
    	break;
    }

    bKASOU_MOVE = false;
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：印刷編集画面を描画します。
//
//  機能説明
//    セルインフォにあるRESULT値（入力値）を描画します。
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
void __fastcall TForm1::DISP_SCREEN_SET(void)
{
	int i1,i2;
	//測定出荷グリッド
	if(hCELLINFO_SOKU_SYUKA)
	{
		for(i1 = 0; i1 < SGr_vSOKU_SYUKA->ColCount ;i1++)
		{
			for(i2 = 1;i2 < SGr_vSOKU_SYUKA->RowCount ; i2++)
			{
				SGr_vSOKU_SYUKA->Cells[i1][i2] = pCELLINFO_SOKU_SYUKA[i1*SGr_vSOKU_SYUKA->RowCount+i2].DISP_RESULT;
			}
        }
	}
	//履歴出荷グリッド
	if(hCELLINFO_RIRE_SYUKA)
	{
		for(i1 = 0; i1 < SGr_vRIRE_SYUKA->ColCount ;i1++)
		{
			for(i2 = 1;i2 < SGr_vRIRE_SYUKA->RowCount ; i2++)
			{
				SGr_vRIRE_SYUKA->Cells[i1][i2] = pCELLINFO_RIRE_SYUKA[i1*SGr_vRIRE_SYUKA->RowCount+i2].DISP_RESULT;
			}
        }
	}
	//測定素材グリッド
	if(hCELLINFO_SOKU_SOZAI)
	{
		for(i1 = 0; i1 < SGr_vSOKU_SOZAI->ColCount ;i1++)
		{
			for(i2 = 1;i2 < SGr_vSOKU_SOZAI->RowCount ; i2++)
			{
				SGr_vSOKU_SOZAI->Cells[i1][i2] = pCELLINFO_SOKU_SOZAI[i1*SGr_vSOKU_SOZAI->RowCount+i2].DISP_RESULT;
			}
        }
	}
	//測定出荷グリッド
	if(hCELLINFO_RIRE_SOZAI)
	{
		for(i1 = 0; i1 < SGr_vRIRE_SOZAI->ColCount ;i1++)
		{
			for(i2 = 1;i2 < SGr_vRIRE_SOZAI->RowCount ; i2++)
			{
				SGr_vRIRE_SOZAI->Cells[i1][i2] = pCELLINFO_RIRE_SOZAI[i1*SGr_vRIRE_SOZAI->RowCount+i2].DISP_RESULT;
			}
        }
	}
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：測定画面を描画します。
//
//  機能説明
//    セルインフォにあるRESULT値（入力値）を描画します。
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
void __fastcall TForm1::SCREEN_SET(void)
{
	int i1,i2;
	//測定出荷グリッド
	if(hCELLINFO_SOKU_SYUKA)
	{
		for(i1 = 0; i1 < SGr_vSOKU_SYUKA->ColCount ;i1++)
		{
			for(i2 = 1;i2 < SGr_vSOKU_SYUKA->RowCount ; i2++)
			{
				SGr_vSOKU_SYUKA->Cells[i1][i2] = pCELLINFO_SOKU_SYUKA[i1*SGr_vSOKU_SYUKA->RowCount+i2].RESULT;
			}
        }
	}
	//履歴出荷グリッド
	if(hCELLINFO_RIRE_SYUKA)
	{
		for(i1 = 0; i1 < SGr_vRIRE_SYUKA->ColCount ;i1++)
		{
			for(i2 = 1;i2 < SGr_vRIRE_SYUKA->RowCount ; i2++)
			{
				SGr_vRIRE_SYUKA->Cells[i1][i2] = pCELLINFO_RIRE_SYUKA[i1*SGr_vRIRE_SYUKA->RowCount+i2].RESULT;
			}
        }
	}
	//測定素材グリッド
	if(hCELLINFO_SOKU_SOZAI)
	{
		for(i1 = 0; i1 < SGr_vSOKU_SOZAI->ColCount ;i1++)
		{
			for(i2 = 1;i2 < SGr_vSOKU_SOZAI->RowCount ; i2++)
			{
				SGr_vSOKU_SOZAI->Cells[i1][i2] = pCELLINFO_SOKU_SOZAI[i1*SGr_vSOKU_SOZAI->RowCount+i2].RESULT;
			}
        }
	}
	//測定出荷グリッド
	if(hCELLINFO_RIRE_SOZAI)
	{
		for(i1 = 0; i1 < SGr_vRIRE_SOZAI->ColCount ;i1++)
		{
			for(i2 = 1;i2 < SGr_vRIRE_SOZAI->RowCount ; i2++)
			{
				SGr_vRIRE_SOZAI->Cells[i1][i2] = pCELLINFO_RIRE_SOZAI[i1*SGr_vRIRE_SOZAI->RowCount+i2].RESULT;
			}
        }
	}
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：コマンドライン引数を分離（部署名、ユーザ名など）
//
//  機能説明
//    プログラム起動時のコマンドライン引数を分離し変数に設定します。
//    ユーザコード、ユーザ名、部署コード、部署名、デバッグモードを抽出します
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
					case 5:
						iDEBUG = AnsiString(str.SubString(n1,i - n1)).ToIntDef(0);
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
//    SetEditTextイベント	：グリッド上でセルの入力が行われると発生します。
//
//  機能説明
//    印刷用の値の入力。
//    文字列長の確認
//
//  パラメタ説明
//    TObject *Sender	            ：呼び出し元のVCLオブジェクト
//    int ACol                      ：対象セルのカラム位置
//    int ARow                      ：対象セルのＲＯＷ位置
//  　const AnsiString Value        ：セルの文字列
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::GRID_SetEditText(TObject *Sender,
      int ACol, int ARow, const AnsiString Value)
{
	int i1,iGrid;
	AnsiString sBuf,sDeci1;
    bool bRtn;

  	if(Sender == SGr_vSOKU_SYUKA) iGrid = 1;
 	if(Sender == SGr_vRIRE_SYUKA) iGrid = 2;
 	if(Sender == SGr_vSOKU_SOZAI) iGrid = 3;
 	if(Sender == SGr_vRIRE_SOZAI) iGrid = 4;

	switch( iGrid )
    {
    case 1:
		//メモリーチェック
		if( !hCELLINFO_SOKU_SYUKA ) return;
		switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
        {
        case 0:		//整数・少数
        case 1:		//角度
        	sDeci1 = "0";
            for(i1 = 0;i1 < AnsiString(pCELLINFO_SOKU_SYUKA[(ACol*SGr_vSOKU_SYUKA->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
            {
            	if( sDeci1.Length() == 1 ) sDeci1 += ".";
                sDeci1 +="0";
            }
        //入力がない時
        	if(AnsiString(Value).Length() == 0)
            {
            	sBuf =Value;
                break;
            }
        //入力チェック
            //2003.05.08 E.Takase Add↓
            bRtn = ConvDoubleDefS(Value,sDeci1,Value,&sBuf);
            //2003.05.08 E.Takase Add↑
            break;
        case 2:  	//良・否
        default:	//文字
        	sBuf = Value;
            sBuf = sBuf.Trim();
            break;
        }
		sBuf = sBuf.SubString(1,14);
        if( sBuf.Length() == 14 ){
    		if ( sBuf.ByteType( 14 ) == mbLeadByte ){
				sBuf = sBuf.SubString(1,13);
            }
        }
        strcpy(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].DISP_RESULT,sBuf.c_str());

        if(SGr_vSOKU_SYUKA->Row == ARow && SGr_vSOKU_SYUKA->Col == ACol && bCellWrite == false)
        {
            Get_GRAPHLOT(Get_GRAPHSTART_Info(ARow,ACol,iGrid),ACol,iGrid);
        }
		break;

    case 2:
		//メモリーチェック
		if( !hCELLINFO_RIRE_SYUKA ) return;
		switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
        {
        case 0:		//整数・少数
        case 1:		//角度
        	sDeci1 = "0";
            for(i1 = 0;i1 < AnsiString(pCELLINFO_RIRE_SYUKA[(ACol*SGr_vRIRE_SYUKA->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
            {
            	if( sDeci1.Length() == 1 ) sDeci1 += ".";
                sDeci1 +="0";
            }
        //入力がない時
        	if(AnsiString(Value).Length() == 0)
            {
            	sBuf =Value;
                break;
            }
        //入力チェック
            //2003.05.08 E.Takase Add↓
            bRtn = ConvDoubleDefS(Value,sDeci1,Value,&sBuf);
            //2003.05.08 E.Takase Add↑
            break;
        case 2:  	//良・否
        default:	//文字
        	sBuf = Value;
            sBuf = sBuf.Trim();
        	break;
        }

		sBuf = sBuf.SubString(1,14);
        if( sBuf.Length() == 14 ){
    		if ( sBuf.ByteType( 14 ) == mbLeadByte ){
				sBuf = sBuf.SubString(1,13);
            }
        }
        strcpy(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].DISP_RESULT,sBuf.c_str());

        if(SGr_vRIRE_SYUKA->Row == ARow && SGr_vRIRE_SYUKA->Col == ACol && bCellWrite == false)
        {
            Get_GRAPHLOT(Get_GRAPHSTART_Info(ARow,ACol,iGrid),ACol,iGrid);
        }
		break;

    case 3:
		//メモリーチェック
		if( !hCELLINFO_SOKU_SOZAI ) return;
		switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
        {
        case 0:		//整数・少数
        case 1:		//角度
        	sDeci1 = "0";
            for(i1 = 0;i1 < AnsiString(pCELLINFO_SOKU_SOZAI[(ACol*SGr_vSOKU_SOZAI->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
            {
            	if( sDeci1.Length() == 1 ) sDeci1 += ".";
                sDeci1 +="0";
            }
        //入力がない時
        	if(AnsiString(Value).Length() == 0)
            {
            	sBuf =Value;
                break;
            }
        //入力チェック
            //2003.05.08 E.Takase Add↓
            bRtn = ConvDoubleDefS(Value,sDeci1,Value,&sBuf);
            //2003.05.08 E.Takase Add↑
            break;
        case 2:  	//良・否
        default:	//文字
        	sBuf = Value;
            sBuf = sBuf.Trim();
        	break;
        }
		sBuf = sBuf.SubString(1,14);
        if( sBuf.Length() == 14 ){
    		if ( sBuf.ByteType( 14 ) == mbLeadByte ){
				sBuf = sBuf.SubString(1,13);
            }
        }
        strcpy(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].DISP_RESULT,sBuf.c_str());

        if(SGr_vSOKU_SOZAI->Row == ARow && SGr_vSOKU_SOZAI->Col == ACol && bCellWrite == false)
        {
            Get_GRAPHLOT(Get_GRAPHSTART_Info(ARow,ACol,iGrid),ACol,iGrid);
        }
		break;

    case 4:
		//メモリーチェック
		if( !hCELLINFO_RIRE_SOZAI ) return;
		switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
        {
        case 0:		//整数・少数
        case 1:		//角度
        	sDeci1 = "0";
            for(i1 = 0;i1 < AnsiString(pCELLINFO_RIRE_SOZAI[(ACol*SGr_vRIRE_SOZAI->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
            {
            	if( sDeci1.Length() == 1 ) sDeci1 += ".";
                sDeci1 +="0";
            }
        //入力がない時
        	if(AnsiString(Value).Length() == 0)
            {
            	sBuf =Value;
                break;
            }
        //入力チェック
            //2003.05.08 E.Takase Add↓
            bRtn = ConvDoubleDefS(Value,sDeci1,Value,&sBuf);
            //2003.05.08 E.Takase Add↑
            break;
        case 2:  	//良・否
        default:	//文字
        	sBuf = Value;
            sBuf = sBuf.Trim();
        	break;
        }
		sBuf = sBuf.SubString(1,14);
        if( sBuf.Length() == 14 ){
    		if ( sBuf.ByteType( 14 ) == mbLeadByte ){
				sBuf = sBuf.SubString(1,13);
            }
        }
        strcpy(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].DISP_RESULT,sBuf.c_str());

        if(SGr_vRIRE_SOZAI->Row == ARow && SGr_vRIRE_SOZAI->Col == ACol && bCellWrite == false)
        {
            Get_GRAPHLOT(Get_GRAPHSTART_Info(ARow,ACol,iGrid),ACol,iGrid);
        }
		break;

	}

}

//---------------------------------------------------------------------------
//
//  概要
//    FormEnterイベント	：フォームにフォーカスがあたった時に発生します。
//
//  機能説明
//    一覧検索ボタンの有効、無効を決定します。
//
//  パラメタ説明
//    TObject *Sender	            ：呼び出し元のVCLオブジェクト
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

    AnsiString	sBuf;
    TComponent	*cmp	= dynamic_cast<TComponent*>(Sender);

    if( BtnF01->Focused() )		return;

    sBuf = cmp->Name;

    // 検索部　代表得意先品番にフォーカスが有る場合
    if( Cmb_DTKSHIN->Focused() || sBuf == "Cmb_DTKSHIN" ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        Form2->Tag = 1;
        return;
    }

    // 検索部　ロットNOにフォーカスが有る場合
    if( Edt_LOTNO->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        Form2->Tag = 2;
        return;
    }

    if( Form2->Tag == 12 ){
        BtnF01->Enabled = true;
        Form2->Tag = 12;
        return;
    }

    // 「F1：一覧検索」ボタンを使えないようにする
    BtnF01->Enabled = false;


}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：ＯＫ時のサウンドを鳴動させます。
//
//  機能説明
//    既存のＷＡＶデータを鳴動します。
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
void __fastcall TForm1::OK_BEEP(TObject *Sender)
{
	MdPlayer->FileName = "RS_OK.wav";
	MdPlayer->Open();
	MdPlayer->Play();
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：ＮＧ時のサウンドを鳴動させます。
//
//  機能説明
//    既存のＷＡＶデータを鳴動します。
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
void __fastcall TForm1::NG_BEEP(TObject *Sender)
{
	MdPlayer2->FileName = "RS_NG.wav";
	MdPlayer2->Open();
	MdPlayer2->Play();

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：測定項目変更時のサウンドを鳴動させます。
//
//  機能説明
//    既存のＷＡＶデータを鳴動します。
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
void __fastcall TForm1::KMCH_BEEP(TObject *Sender)
{
	MdPlayer3->FileName = "KM_Change.wav";
	MdPlayer3->Open();
	MdPlayer3->Play();

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：ハンディターミナルからデータをUPLOADします。
//
//  機能説明
//    COM3を通信ポートとし、ハンディーターミナルからデータをUPLOADします。
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    -1                ：通信エラー
//     1                ：正常終了
//
//  備考
//    古門さん作成関数
//
//---------------------------------------------------------------------------
int TForm1::DataUpLoad()
{
    //TODO この下にコードを追加してください

	char tmp[64];
	int rtn;
    int nFlag;						// 処理フラグ　
    AnsiString asBufData,asBuf;		// ポートバッファ用
	AnsiString sTmp1, sTmp2;
	time_t nowTime;


    nFlag = 0;
    while (1) {
		switch (nFlag) {
		case 0:
			nFlag = 10;
			break;
		case 10:
			// 通信ポートオープン
			rtn = CommOpen("COM3","115200","N,8,1");
			if (rtn < 0) {
				MessageBox(NULL, "通信ポートオープンエラー", "エラー", MB_ICONSTOP);
			}
			iComPort = rtn;
			nFlag = 200;
			break;
		case 200:
			// 受信
			sprintf(tmp, "%c%s%c", STX, "1A**", ETX);
	        /*
	        sprintf(tmp, "%c%s", STX, "1A");
			// BCCチェック
			if (chkBCC->State == cbChecked) {
				sTmp1 = tmp;
				sTmp2 = CreatBCC(sTmp1);
				strcat(tmp, sTmp2.c_str());
			} else
				strcat(tmp, "**");
			//sprintf(tmp, "%s%c", tmp, ETX);
			tmp[5] = ETX;
			tmp[6] = '\0';
	        */
	        CommClear(iComPort);                       // ポートバッファクリア
			CommWrite(iComPort, tmp);				   // アップロードコマンド送信
			time(&sTime);
			nFlag = 210;
			break;
		case 210:
			// タイムアウトチェック
			time(&nowTime);
			if (nowTime - sTime > 1) {
                CommClose(iComPort);
				return (-1);
			}

			nFlag = 220;
			break;
		case 220:
			// バッファ受信
			asBufData = DataReceive();
            if (asBufData.IsEmpty() == true) {
                CommClose(iComPort);
                return (-1);
            }

			// 送信判別
			if (asBufData.AnsiPos("\x06") > 0) {
				nFlag = 230;	// ACK受信
			} else {
                CommClose(iComPort);
                return (-1);	// NAK受信
            }
			break;
		case 230:
	        // タイムアウトチェック
			time(&nowTime);
			if (nowTime - sTime > 1) {
                CommClose(iComPort);
				return (-1);
			}
			nFlag = 240;
			break;
		case 240:
			// バッファ受信　
			asBufData = DataReceive();
            if (asBufData.IsEmpty() == true) {
                CommClose(iComPort);
                return (-1);
            }
			asBuf = asBufData.SubString(9,32);
			// データがある場合（データ番号が"00000"以外）は出力
			// データIDは4バイト目から5バイト分（"00001〜99999"）
			if (asBufData.SubString(4,5) != "00000"){
                sShiji_Data->Add(asBuf);
			}
			nFlag = 250;
			break;
		case 250:
			// ACK送信
			sprintf(tmp, "%c%s%c%s%c", STX, "1R", ACK, "**", ETX);
	        /*
	        sprintf(tmp, "%c%s%c", STX, "1R", ACK);
			// BCCチェック
			if (chkBCC->State == cbChecked) {
				sTmp1 = tmp;
				sTmp2 = CreatBCC(sTmp1);
				strcat(tmp, sTmp2.c_str());
			} else
				strcat(tmp, "**");
			//sprintf(tmp, "%s%c", tmp, ETX);
			tmp[6] = ETX;
			tmp[7] = '\0';
	        */
			CommClear(iComPort);		// ポートバッファクリア
			CommWrite(iComPort, tmp);   // 送信
			// データがあればバッファ受信から繰り返し
			if (asBufData.SubString(4,5) != "00000")
				nFlag = 240;
			else {
				nFlag = 999;
	        }
			break;
		case 999:
			// 通信終了
			CommClose(iComPort);          // ポートクローズ
	        return(1);
		}
	}
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：データ受信処理。
//
//  機能説明
//    ハンディーターミナルから１バイト毎にデータを読み取りETXで抜ける。
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    ""                ：通信エラー
//    品番orロット文字列：正常終了
//
//  備考
//    古門さん作成関数
//
//---------------------------------------------------------------------------
AnsiString TForm1::DataReceive()
{
	//TODO この下にコードを追加してください
	int iSW;
	char Buf[64];
	AnsiString asRet;
	AnsiString asRecBuf;
	time_t nowTime;

	iSW = 10;
	// 制御フロー設定 ON
	CommSetFlow(iComPort,1,1,1,1,1);
	while (1){
		// タイムアウトチェック
		time(&nowTime);
		if (nowTime - sTime > 1) {
			MessageDlg("通信がタイムアウトになりました。", mtError, TMsgDlgButtons() << mbOK , 0);
			return "";
		}
		// １バイト毎に取得
		CommReadNum(iComPort,Buf,1);
		switch (iSW){
		case 10:
			// ヘッダ情報 STX（0x02）
			if (Buf[0] == STX) {
				asRecBuf = Buf[0];
				iSW++;
			}
			break;
		case 11:
			// ID情報
			if (Buf[0] == '1' || Buf[0] == '2'){
				asRecBuf = asRecBuf + Buf[0];
				iSW++;
			}
			break;
		case 12:
			//  区分情報
			if (Buf[0] == 'A' || Buf[0] == 'D' || Buf[0] == 'R' ||
				Buf[0] == 'S' || Buf[0] == 'M'){
				asRecBuf = asRecBuf + Buf[0];
				iSW++;
			}
			break;
		case 13:
			// フッタ情報 ETX（0x03）
			// フッタ（ETX）になったら処理を抜ける　
			if (Buf[0] == ETX){
				asRecBuf = asRecBuf + Buf[0];
				iSW = 20;
				break;
			} else {
				// データ部
				asRecBuf = asRecBuf + Buf[0];
			}
			break;
//		case 14:
//			iSW = 20;
//			break;
		}
		if (iSW == 20) break;
	}
	// 制御フロー設定 OFF
	CommSetFlow(iComPort,0,0,0,0,0);
	return (asRecBuf);

}

//---------------------------------------------------------------------------
//
//  概要
//    OnChangeイベント	：編集領域に表示されたテキストが変更されると発生します。
//
//  機能説明
//    代表得意先品番の入力を大文字に変える。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    高瀬さん作成関数
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Cmb_DTKSHINChange(TObject *Sender)
{
    int			i;
    int			iSelStart;
    AnsiString	sBuf;
    TComboBox* cmb = dynamic_cast<TComboBox*>(Sender);

    sBuf = cmb->Text;
    iSelStart = cmb->SelStart;
    
    if (cmb->ItemIndex >= 0) {
        // LOTを表示
        Edt_LOTNO->Text = sHT_LOT->Strings[cmb->ItemIndex];
        // インデックス表示
        sBuf = AnsiString(cmb->ItemIndex + 1) + "/" + AnsiString(sHT_LOT->Count);
        Lab_Num->Caption = sBuf;
    }

    // シングルコーテーションはＤＢ登録時にエラーが発生する
    // ので全角のシングルコーテーションに変換します
    i = sBuf.AnsiPos("'");
    if( i > 0 ){
        sBuf.Delete( i, 1);
        if( cmb->MaxLength == 0 || cmb->MaxLength >= sBuf.Length() + 2 ){
        	sBuf.Insert("’",i);
    	}
        //cmb->Text = sBuf;
        //cmb->SelStart = i + 1;
        iSelStart = i + 1;
    }
    // 2003/9/10 A.Tamura
    //cmb->Text = sBuf.UpperCase();

    cmb->SelStart = iSelStart;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnTopLeftChanged イベント	：TopRow プロパティまたは LeftCol プロパティが変更された直後に発生します。
//
//  機能説明
//    素材（履歴）と他のStringGridのスクロール連携させるための関数です。
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
void __fastcall TForm1::SGr_tRIRE_SOZAITopLeftChanged(TObject *Sender)
{

    // 他のGrid、スクロールボックスの連携
    SGr_vRIRE_SYUKA->LeftCol = SGr_tRIRE_SOZAI->LeftCol;
    SGr_tRIRE->LeftCol       = SGr_tRIRE_SOZAI->LeftCol;
    SGr_vRIRE_SOZAI->LeftCol = SGr_tRIRE_SOZAI->LeftCol;
    SGr_tRIRE_SYUKA->LeftCol = SGr_tRIRE_SOZAI->LeftCol;
	SBx_vRIRE_MEMO->HorzScrollBar->Position = SGr_tRIRE_SOZAI->LeftCol *  Mem_vRIRE_MEMOORG->Width;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnTopLeftChanged イベント	：TopRow プロパティまたは LeftCol プロパティが変更された直後に発生します。
//
//  機能説明
//    出荷（履歴）と他のStringGridのスクロール連携させるための関数です。
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
void __fastcall TForm1::SGr_tRIRE_SYUKATopLeftChanged(TObject *Sender)
{

    // 他のGrid、スクロールボックスの連携
    SGr_vRIRE_SYUKA->LeftCol = SGr_tRIRE_SYUKA->LeftCol;
    SGr_tRIRE->LeftCol       = SGr_tRIRE_SYUKA->LeftCol;
    SGr_vRIRE_SOZAI->LeftCol = SGr_tRIRE_SYUKA->LeftCol;
    SGr_tRIRE_SOZAI->LeftCol = SGr_tRIRE_SYUKA->LeftCol;
	SBx_vRIRE_MEMO->HorzScrollBar->Position = SGr_tRIRE_SYUKA->LeftCol *  Mem_vRIRE_MEMOORG->Width;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnTopLeftChanged イベント	：TopRow プロパティまたは LeftCol プロパティが変更された直後に発生します。
//
//  機能説明
//    素材（測定）と他のStringGridのスクロール連携させるための関数です。
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
void __fastcall TForm1::SGr_tSOKU_SOZAITopLeftChanged(TObject *Sender)
{

    // 他のGrid、スクロールボックスの連携
    SGr_vSOKU_SYUKA->LeftCol = SGr_tSOKU_SOZAI->LeftCol;
    SGr_tSOKU->LeftCol       = SGr_tSOKU_SOZAI->LeftCol;
    SGr_vSOKU_SOZAI->LeftCol = SGr_tSOKU_SOZAI->LeftCol;
    SGr_tSOKU_SYUKA->LeftCol = SGr_tSOKU_SOZAI->LeftCol;
	SBx_vSOKU_MEMO->HorzScrollBar->Position = SGr_tSOKU_SOZAI->LeftCol *  Mem_vSOKU_MEMOORG->Width;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnTopLeftChanged イベント	：TopRow プロパティまたは LeftCol プロパティが変更された直後に発生します。
//
//  機能説明
//    出荷（測定）と他のStringGridのスクロール連携させるための関数です。
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
void __fastcall TForm1::SGr_tSOKU_SYUKATopLeftChanged(TObject *Sender)
{

    // 他のGrid、スクロールボックスの連携
    SGr_vSOKU_SYUKA->LeftCol = SGr_tSOKU_SYUKA->LeftCol;
    SGr_tSOKU->LeftCol       = SGr_tSOKU_SYUKA->LeftCol;
    SGr_vSOKU_SOZAI->LeftCol = SGr_tSOKU_SYUKA->LeftCol;
    SGr_tSOKU_SOZAI->LeftCol = SGr_tSOKU_SYUKA->LeftCol;
	SBx_vSOKU_MEMO->HorzScrollBar->Position = SGr_tSOKU_SYUKA->LeftCol *  Mem_vSOKU_MEMOORG->Width;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnGetEditText イベント	：インプレースエディタがセルの値を要求したときに発生します。
//
//  機能説明
//    素材（測定）セルの値要求時にセレクトセルを発生します。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int ACol          ：対象セルのカラム位置
//  　int ARow          ：対象セルのROW位置
//  　AnsiString &Value ：セルの文字列
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vSOKU_SOZAIGetEditText(TObject *Sender,
      int ACol, int ARow, AnsiString &Value)
{
	if( iRow_vSOKU_SOZAI == ARow &&
        iCol_vSOKU_SOZAI == ACol ){

        bool	CanSelect;
		AllGRID_SelectCell(	SGr_vSOKU_SOZAI,
        					ACol,
               	            ARow,
                   	        CanSelect);
    }
}

//---------------------------------------------------------------------------
//
//  概要
//    OnGetEditText イベント	：インプレースエディタがセルの値を要求したときに発生します。
//
//  機能説明
//    出荷（測定）セルの値要求時にセレクトセルを発生します。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int ACol          ：対象セルのカラム位置
//  　int ARow          ：対象セルのROW位置
//  　AnsiString &Value ：セルの文字列
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vSOKU_SYUKAGetEditText(TObject *Sender,
      int ACol, int ARow, AnsiString &Value)
{
	if( iRow_vSOKU_SYUKA == ARow &&
        iCol_vSOKU_SYUKA == ACol ){

        bool	CanSelect;
		AllGRID_SelectCell(	SGr_vSOKU_SYUKA,
        					ACol,
               	            ARow,
                   	        CanSelect);
    }

}

//---------------------------------------------------------------------------
//
//  概要
//    OnGetEditText イベント	：インプレースエディタがセルの値を要求したときに発生します。
//
//  機能説明
//    素材（履歴）セルの値要求時にセレクトセルを発生します。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int ACol          ：対象セルのカラム位置
//  　int ARow          ：対象セルのROW位置
//  　AnsiString &Value ：セルの文字列
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vRIRE_SOZAIGetEditText(TObject *Sender,
      int ACol, int ARow, AnsiString &Value)
{
	if( iRow_vRIRE_SOZAI == ARow &&
        iCol_vRIRE_SOZAI == ACol ){

        bool	CanSelect;
		AllGRID_SelectCell(	SGr_vRIRE_SOZAI,
        					ACol,
               	            ARow,
                   	        CanSelect);
    }

}

//---------------------------------------------------------------------------
//
//  概要
//    OnGetEditText イベント	：インプレースエディタがセルの値を要求したときに発生します。
//
//  機能説明
//    出荷（履歴）セルの値要求時にセレクトセルを発生します。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int ACol          ：対象セルのカラム位置
//  　int ARow          ：対象セルのROW位置
//  　AnsiString &Value ：セルの文字列
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_vRIRE_SYUKAGetEditText(TObject *Sender,
      int ACol, int ARow, AnsiString &Value)
{
	if( iRow_vRIRE_SYUKA == ARow &&
        iCol_vRIRE_SYUKA == ACol ){

        bool	CanSelect;
		AllGRID_SelectCell(	SGr_vRIRE_SYUKA,
        					ACol,
               	            ARow,
                   	        CanSelect);
    }

}

//---------------------------------------------------------------------------
//
//  概要
//    OnResize イベント ：スクロールボックスをサイズ変更したときに発生します。
//
//  機能説明
//    測定備考欄のスクロールボックスをサイズ変更したときに発生します。
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
void __fastcall TForm1::SBx_vSOKU_MEMOResize(TObject *Sender)
{
	if(SGr_tSOKU->Cells[0][0]!="" && !bNowF7 )
	{
        int	i1;
		for(i1 = 0 ; i1 < SGr_tSOKU->ColCount ;i1++)
		{
           	Mem_vSOKU_MEMO[i1]->Height	= SBx_vSOKU_MEMO->Height - 1;
    	}
	}
}

//---------------------------------------------------------------------------
//
//  概要
//    OnResize イベント ：スクロールボックスをサイズ変更したときに発生します。
//
//  機能説明
//    履歴備考欄のスクロールボックスをサイズ変更したときに発生します。
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
void __fastcall TForm1::SBx_vRIRE_MEMOResize(TObject *Sender)
{
	if(SGr_tRIRE->Cells[0][0]!="" && !bNowF7 )
	{
        int	i1;
		for(i1 = 0 ; i1 < SGr_tRIRE->ColCount ;i1++)
		{
           	Mem_vRIRE_MEMO[i1]->Height	= SBx_vRIRE_MEMO->Height - 1;
    	}
	}

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数 ：文字列を数値に変換する。
//
//  機能説明
//    文字列を数値に変換する。変換エラーの場合はデフォルト値（数値型）を返します。
//
//  パラメタ説明
//    AnsiString sTarget	：変換する文字列
//    double dValue         ：デフォルト値
//  戻り値
//    変換成功時            ：変換された数値
//  　変換失敗              ：デフォルト値
//
//  備考
//****************************************************************************
//2003.05.08 E.Takase Add
//---------------------------------------------------------------------------
//文字列を数値に変換する。変換エラーの場合はデフォルト値（数値型）を返す
//****************************************************************************
//
//---------------------------------------------------------------------------
double __fastcall TForm1::ConvDoubleDefD(AnsiString sTarget, double dValue)
{
	AnsiString 	sBuf;
	AnsiString 	sTargetTrim;
	AnsiString 	sCheckStr;
	int 		iLength;
	int 		i;
	int 		n;
    double 		dRtnValue;

	try{
    	sCheckStr = "-+0123456789.";
    	dRtnValue = dValue;

    	sTargetTrim = Trim(sTarget);    //前後のスペースを省く
    	iLength = sTargetTrim.Length();

    	if ( sTargetTrim == "" ) {
    		return(dRtnValue);
    	}

    	//数字以外の文字が含まれているか、1文字ずつチェックしていく
    	for ( i = 1; i <= iLength; i++ ) {
    		//1文字ずつチェック
   	    	sBuf = sTargetTrim.SubString(i,1);

			n = sCheckStr.AnsiPos(sBuf);

   	     	if ( n <= 0 ) {
   	    		//数字以外の文字が含まれているのでデフォルト値を返す
        		return(dRtnValue);
       		}
    	}

    	//ピリオド（小数点）が2つ以上含まれていたらデフォルト値を返す
    	n = sTargetTrim.AnsiPos(".");
    	if ( n > 0 ) {
			sBuf = sTargetTrim.SubString(n+1,iLength-n);
        	n = sBuf.AnsiPos(".");
        	if ( n > 0 ) {
        		return(dRtnValue);
        	}
    	}

    	//マイナスが2つ以上含まれていたらデフォルト値を返す
        //マイナスが一番左にない場合もデフォルト値を返す
        //2003.06.16 E.Takase Add
        if ( sTargetTrim == "-" ) {
         	return(dRtnValue);
        }
    	n = sTargetTrim.AnsiPos("-");
    	if ( n > 0 ) {
            if ( n != 1 ) {
            	return(dRtnValue);
            } else {
				sBuf = sTargetTrim.SubString(n+1,iLength-n);
        		n = sBuf.AnsiPos("-");
        		if ( n > 0 ) {
        			return(dRtnValue);
        		}
        	}
    	}

    	//プラスが2つ以上含まれていたらデフォルト値を返す
        //プラスが一番左にない場合もデフォルト値を返す
        //2003.06.16 E.Takase Add
        if ( sTargetTrim == "+" ) {
         	return(dRtnValue);
        }
    	n = sTargetTrim.AnsiPos("+");
    	if ( n > 0 ) {
            if ( n != 1 ) {
            	return(dRtnValue);
            } else {
				sBuf = sTargetTrim.SubString(n+1,iLength-n);
        		n = sBuf.AnsiPos("+");
        		if ( n > 0 ) {
        			return(dRtnValue);
        		}
        	}
    	}

    	dRtnValue = sTarget.ToDouble();   //double型に変換
    	return(dRtnValue);

	}
	catch(EConvertError& e){
		return(dRtnValue);
	}
	catch(...){
		return(dRtnValue);
	}


}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数 ：文字列を数値に変換する。
//
//  機能説明
//    文字列を数値に変換する。変換エラーの場合はデフォルト値（文字型）を返します。
//
//  パラメタ説明
//    AnsiString sTarget	：変換する文字列
//    AnsiString sFormat    ：変換するフォーマット
//  　AnsiString dValue     ：デフォルト値
//    AnsiString *sRtn      ：変換された文字列
//  戻り値
//    true                  ：変換成功
//  　false                 ：変換失敗
//
//  備考
//****************************************************************************
//2003.05.08 E.Takase Add
//---------------------------------------------------------------------------
//文字列を数値に変換する。変換エラーの場合はデフォルト値（文字型）を返す
//****************************************************************************
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::ConvDoubleDefS(AnsiString sTarget, AnsiString sFormat, AnsiString dValue, AnsiString *sRtn)
{
	AnsiString 	sBuf;
	AnsiString 	sTargetTrim;
	AnsiString 	sCheckStr;
	int 		iLength;
	int 		i;
	int 		n;
    AnsiString 	sRtnValue;
	double 		dRtnValue;

	try{
	
		*sRtn =dValue;

    	sCheckStr = "-+0123456789.";
    	sRtnValue = dValue;
        dRtnValue = 0;

    	sTargetTrim = Trim(sTarget);    //前後のスペースを省く
    	iLength = sTargetTrim.Length();

    	if ( sTargetTrim == "" ) {
    		return(false);
    	}

    	//数字以外の文字が含まれているか、1文字ずつチェックしていく
    	for ( i = 1; i <= iLength; i++ ) {
    		//1文字ずつチェック
   	    	sBuf = sTargetTrim.SubString(i,1);

			n = sCheckStr.AnsiPos(sBuf);

   	     	if ( n <= 0 ) {
   	    		//数字以外の文字が含まれているのでデフォルト値を返す
        		return(false);
       		}
    	}

    	//ピリオド（小数点）が2つ以上含まれていたらデフォルト値を返す
    	n = sTargetTrim.AnsiPos(".");
    	if ( n > 0 ) {
			sBuf = sTargetTrim.SubString(n+1,iLength-n);
        	n = sBuf.AnsiPos(".");
        	if ( n > 0 ) {
        		return(false);
        	}
    	}

    	//マイナスが2つ以上含まれていたらデフォルト値を返す
        //マイナスが一番左にない場合もデフォルト値を返す
        //2003.06.16 E.Takase Add
        if ( sTargetTrim == "-" ) {
        	*sRtn ="0";
        	return(true);
        }
    	n = sTargetTrim.AnsiPos("-");
    	if ( n > 0 ) {
            if ( n != 1 ) {
            	return(false);
            } else {
				sBuf = sTargetTrim.SubString(n+1,iLength-n);
        		n = sBuf.AnsiPos("-");
        		if ( n > 0 ) {
        			return(false);
        		}
        	}
    	}

    	//プラスが2つ以上含まれていたらデフォルト値を返す
        //プラスが一番左にない場合もデフォルト値を返す
        //2003.06.16 E.Takase Add
        if ( sTargetTrim == "+" ) {
        	*sRtn ="0";
        	return(true);
        }
    	n = sTargetTrim.AnsiPos("+");
    	if ( n > 0 ) {
            if ( n != 1 ) {
            	return(false);
            } else {
				sBuf = sTargetTrim.SubString(n+1,iLength-n);
        		n = sBuf.AnsiPos("+");
        		if ( n > 0 ) {
        			return(false);
        		}
        	}
    	}

    	dRtnValue = sTarget.ToDouble();   //double型に変換
        if ( Trim(sFormat) != "" ) {
        	sRtnValue = FormatFloat(sFormat,dRtnValue);
        } else {
        	sRtnValue = FloatToStr(dRtnValue);
        }
        *sRtn =sRtnValue;
    	return(true);

	}
	catch(EConvertError& e){
		return(false);
	}
	catch(...){
		return(false);
	}


}


//---------------------------------------------------------------------------
//
//  概要
//    自作関数 ：Nullならブランクを返す。
//
//  機能説明
//    Nullならブランクを返す。
//
//  パラメタ説明
//    Variant &vBuf	        ：???
//
//  戻り値
//    なし。
//
//  備考
//      現在未使用。
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::Null_S(Variant &vBuf)
{
	AnsiString sBuf;

	if ( vBuf.IsNull() ) {
		sBuf = " ";
	} else {
		sBuf = VarToStr(vBuf);
	}
    if ( Trim(sBuf) == "" ) {
        sBuf = " ";
    }
	return ( sBuf );

}

//---------------------------------------------------------------------------
//
//  概要
//    OnSetEditText イベント    ：ユーザーがセルの値の編集を完了したときに発生します。
//
//  機能説明
//    出荷（測定）の検査日に入力された値を代入する。（カラーによって測定用にも反映する）
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int ACol          ：対象セルのカラム位置
//  　int ARow          ：対象セルのROW位置
//  　AnsiString &Value ：セルの文字列
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tSOKU_SYUKASetEditText(TObject *Sender,
      int ACol, int ARow, const AnsiString Value)
{
	int i1;
	AnsiString sBuf;
	sBuf = "";
	if(pSOKU_KSD01_DATA)
	{
    	for(i1=1;i1<=Value.Length();i1++)
        {
            if(strcspn(Value.SubString(i1,1).c_str(),"0123456789")==0)
            {
		   		sBuf += Value.SubString(i1,1);
		  	}
        }
		if(sBuf.Length() == 8)
		{
			strcpy(pSOKU_KSD01_DATA[ACol].SKTYMD_PRT,sBuf.c_str());
   			if(SGr_vSOKU_SYUKA->Color != 0x00DDDDDD)		//表示用カラー
			{
				strcpy(pSOKU_KSD01_DATA[ACol].SKTYMD,sBuf.c_str());
			}
            pSOKU_KSD01_DATA[ACol].UPD_FLG = true;
		}
	}
	
}

//---------------------------------------------------------------------------
//
//  概要
//    OnSetEditText イベント    ：ユーザーがセルの値の編集を完了したときに発生します。
//
//  機能説明
//    出荷（履歴）の検査日に入力された値を代入する。（カラーによって測定用にも反映する）
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int ACol          ：対象セルのカラム位置
//  　int ARow          ：対象セルのROW位置
//  　AnsiString &Value ：セルの文字列
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tRIRE_SYUKASetEditText(TObject *Sender,
      int ACol, int ARow, const AnsiString Value)
{
	int i1;
	AnsiString sBuf;
	sBuf = "";
	if(pRIRE_KSD01_DATA)
	{
    	for(i1=1;i1<=Value.Length();i1++)
        {
            if(strcspn(Value.SubString(i1,1).c_str(),"0123456789")==0)
            {
		   		sBuf += Value.SubString(i1,1);
		  	}
        }
		if(sBuf.Length() == 8)
		{
			strcpy(pRIRE_KSD01_DATA[ACol].SKTYMD_PRT,Value.c_str());
   			if(SGr_vRIRE_SYUKA->Color != 0x00DDDDDD)		//表示用カラー
			{
				strcpy(pRIRE_KSD01_DATA[ACol].SKTYMD,sBuf.c_str());
			}
		    if( hRIRE_KSD01_DATA && Form1->iRIRE_CNT != 0  )
		    {
				pRIRE_KSD01_DATA[ACol].UPD_FLG = true;
			}
		}
	}
	
}

//---------------------------------------------------------------------------
//
//  概要
//    OnSetEditText イベント    ：ユーザーがセルの値の編集を完了したときに発生します。
//
//  機能説明
//    素材（測定）の検査日に入力された値を代入する。（カラーによって測定用にも反映する）
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int ACol          ：対象セルのカラム位置
//  　int ARow          ：対象セルのROW位置
//  　AnsiString &Value ：セルの文字列
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tSOKU_SOZAISetEditText(TObject *Sender,
      int ACol, int ARow, const AnsiString Value)
{
	int i1;
	AnsiString sBuf;
	sBuf = "";
	if(pSOKU_KSD01_DATA)
	{
    	for(i1=1;i1<=Value.Length();i1++)         
        {
            if(strcspn(Value.SubString(i1,1).c_str(),"0123456789")==0)
            {
		   		sBuf += Value.SubString(i1,1);
		  	}
        }
		if(sBuf.Length() == 8)
		{
			strcpy(pSOKU_KSD01_DATA[ACol].SKTYMD_SZ_PRT,Value.c_str());
   			if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD)		//表示用カラー
			{
				strcpy(pSOKU_KSD01_DATA[ACol].SKTYMD_SZ,sBuf.c_str());
			}
            pSOKU_KSD01_DATA[ACol].UPD_FLG = true;
		}
	}
	
}

//---------------------------------------------------------------------------
//
//  概要
//    OnSetEditText イベント    ：ユーザーがセルの値の編集を完了したときに発生します。
//
//  機能説明
//    素材（履歴）の検査日に入力された値を代入する。（カラーによって測定用にも反映する）
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int ACol          ：対象セルのカラム位置
//  　int ARow          ：対象セルのROW位置
//  　AnsiString &Value ：セルの文字列
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tRIRE_SOZAISetEditText(TObject *Sender,
      int ACol, int ARow, const AnsiString Value)
{
	int i1;
	AnsiString sBuf;
	sBuf = "";
	if(pSOKU_KSD01_DATA)
	{
    	for(i1=1;i1<=Value.Length();i1++)
        {
            if(strcspn(Value.SubString(i1,1).c_str(),"0123456789")==0)
            {
		   		sBuf += Value.SubString(i1,1);
		  	}
        }
		if(sBuf.Length() == 8)
		{
			strcpy(pRIRE_KSD01_DATA[ACol].SKTYMD_SZ_PRT,Value.c_str());
   			if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD)		//表示用カラー
			{
				strcpy(pRIRE_KSD01_DATA[ACol].SKTYMD_SZ,sBuf.c_str());
			}
		    if( hRIRE_KSD01_DATA && Form1->iRIRE_CNT != 0  )
		    {
				pRIRE_KSD01_DATA[ACol].UPD_FLG = true;
			}
    	}
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SGr_vRIRE_SYUKADblClick(TObject *Sender)
{
    SBr1->Panels->Items[0]->Text = "DoubleClick()";
    SBr1->Update();
    Beep();
}

//---------------------------------------------------------------------------
// 編集コントロールウィンドウを表示しません
// 【注意】：この関数をコールすると以降、編集コントロールウィンドウが
//           表示されません。
//           復活させる場合は、他の処理で以下のコードで編集コントロール
//           ウィンドウを使える状態に戻して下さい。
//           TStringGrid->Options << goEditing;
void __fastcall TForm1::Delete_InplaceEdit(TObject *Sender)
{
	if( AnsiString(Sender->ClassName()) == "TStringGrid" ){

		TStringGrid		*Sgr = (TStringGrid *)Sender;

		// キャレットの位置を取得
		// 編集セル（TInplaceEdit）を検索
		//int i;
		TInplaceEdit *edit = NULL;
		int ComCount = Sgr->ComponentCount;  // 全コンポーネント数

		for( int i=0; i<ComCount; i++ ){
			TComponent *component = Sgr->Components[i];
			AnsiString name = component->ClassName();
			if( name == "TInplaceEdit" ){
				edit = ( TInplaceEdit* )component;
                //edit->Hide();
                //edit->Invalidate();
                Sgr->Options >> goEditing;
				break;
			}
		}
	}

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数    ：ユーザーの入力に対して有効な入力がされているかをチェックします。
//
//  機能説明
//    ユーザーの入力に対して有効な入力がされているかをチェックします。
//
//  パラメタ説明
//    AnsiString sBuf	：セルの入力
//    int   iVALUE_TYPE ：測定値表現（0：整数、少数　1：角度　2：良否　3：文字列）
//  　TObject *Sender   ：呼び出し元のVCLオブジェクト
//    char &Key         ：ユーザーが押下したキー
//  　int iLenMAX       ：入力最大文字数
//
//  戻り値
//    なし。
//
//  備考
//2003.05.15 E.Takase Add ↓
//
//---------------------------------------------------------------------------
void __fastcall TForm1::ChkInputData(AnsiString sBuf, int iVALUE_TYPE, TObject *Sender, char &Key, int iLenMAX)
{

	//int iVALUE_DECI;
	AnsiString sDeci1;
	AnsiString sBuf2;
	AnsiString sKey;
	AnsiString sBufChk;
    bool bRtn;

	TStringGrid	*Sgr = (TStringGrid *)Sender;
	//int 	i;
	TInplaceEdit *edit = NULL;
	int 	ComCount = Sgr->ComponentCount;  // 全コンポーネント数
	bool	fOK;


    //備考欄は改行あり
    if( Key == VK_RETURN && iVALUE_TYPE != 9 )  {
    	return;
    }

    if( Key == VK_BACK || Key == VK_TAB )  {
    	return;
    }

    sKey = Key;
    sBufChk = sBuf + sKey;

    //有効な文字が入力されていたら文字の長さチェック
	// キャレットの位置を取得
	// 編集セル（TInplaceEdit）を検索
	fOK = false;
	for( int i=0; i<ComCount; i++ ){
		TComponent *component = Sgr->Components[i];
		AnsiString name = component->ClassName();
		if( name == "TInplaceEdit" ){
			edit = ( TInplaceEdit* )component;
	        //if( edit->SelStart == 0 && edit->SelLength == sBuf.Length()){
            if( edit->SelStart > 0 ){
                sBufChk = sBuf.SubString(1,edit->SelStart);
            }
            else {
             	sBufChk = "";
            }
            sBufChk = sBufChk + sKey;
            if( edit->SelStart + edit->SelLength < sBuf.Length() ){
              	sBufChk = sBufChk + sBuf.SubString(edit->SelStart + edit->SelLength + 1,
                                  sBuf.Length() - (edit->SelStart + edit->SelLength));
	        }
		}
	}

    //有効な文字列がセットされたかチェック
	switch(iVALUE_TYPE)
	{
        case 0:	//整数・小数
        case 1: //角度
			if ( Key == VK_SPACE ) {
	        	Key = '\0';
				return;
			}

			//マイナスのみの場合 チェックをスキップ
			if ( sBufChk == "-" ) {
				return;
			}

            sDeci1 = "";
    		//数値チェック
    		bRtn = ConvDoubleDefS(sBufChk,sDeci1,sBufChk,&sBuf2);
			//数値でなかった場合、最後に入力された文字をカット
			if ( bRtn == false ) {
				Key = '\0';
				return;
			}
			break;

        case 2: //良・否
			if ( Key == VK_SPACE ) {
	        	Key = '\0';
				return;
			}
            //0・1のみ有効
        	if ( sKey != "0" &&  sKey != "1" ) {
	        	Key = '\0';
				return;
        	}

			break;

        case 3: //文字
			if ( Key == VK_SPACE ) {
	        	Key = '\0';
				return;
			}
/*
            sDeci1 = "";
    		//数値チェック
    		bRtn = ConvDoubleDefS(sBufChk,sDeci1,sBufChk,&sBuf2);
			//数値でなかった場合、最後に入力された文字をカット
			if ( bRtn == false ) {
				Key = '\0';
				return;
			}
*/
            //数値チェックでは "-"、"+"、"."がOKだが、日付では有効ではないのでカット
        	//if ( sKey == "-" || sKey == "+" || sKey == "." ) {
        	if ( sKey == "'" ) {
	        	Key = '\0';
				return;
        	}

			break;
        case 4: //日付
			if ( Key == VK_SPACE ) {
	        	Key = '\0';
				return;
			}

            sDeci1 = "";
    		//数値チェック
    		bRtn = ConvDoubleDefS(sBufChk,sDeci1,sBufChk,&sBuf2);
			//数値でなかった場合、最後に入力された文字をカット
			if ( bRtn == false ) {
				Key = '\0';
				return;
			}

            //数値チェックでは "-"、"+"、"."がOKだが、日付では有効ではないのでカット
        	if ( sKey == "-" || sKey == "+" || sKey == "." ) {
	        	Key = '\0';
				return;
        	}

			break;
		default:

			break;

	}

    //有効な文字が入力されていたら文字の長さチェック
	// キャレットの位置を取得
	// 編集セル（TInplaceEdit）を検索
	fOK = false;
	for( int i=0; i<ComCount; i++ ){
			TComponent *component = Sgr->Components[i];
			AnsiString name = component->ClassName();
			if( name == "TInplaceEdit" ){
				edit = ( TInplaceEdit* )component;
	            //if( edit->SelStart == 0 && edit->SelLength == sBuf.Length()){
	            if( edit->SelLength > 0){
	              	fOK = true;
	            }
			}
	}
	//長さチェック
	if ( fOK == false && sBufChk.Length() > iLenMAX ) {
		Key = '\0';
	}


}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数    ：文字列sMasterに含まれるsAを検索してsBに置き換える。
//
//  機能説明
//    文字列sMasterに含まれるsAを検索してsBに置き換える。
//
//  パラメタ説明
//    AnsiString sMaster：対象文字列
//    AnsiString sA     ：変換したい文字列
//  　AnsiString sB     ：変換後の文字列
//
//  戻り値
//    なし。
//
//  備考
//　高瀬さん作成 ↓
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::ReplaceStrAtoB(AnsiString sMaster, AnsiString sA, AnsiString sB)
{
	int iLength;
    AnsiString sBuf;
    int iPos;

    sBuf = sMaster;
    iLength = sMaster.Length();

    if ( iLength <= 0 ) {
    	return ( sBuf );
    }

    while ( 1 ) {

    	iPos = sBuf.AnsiPos(sA);
        if ( iPos <= 0 ) {
        	break;
        }

        sBuf.Delete(iPos, sA.Length());
        sBuf.Insert(sB, iPos);


    }



    return ( sBuf );
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数    ：文字列を指定された長さでカット。
//
//  機能説明
//    文字列を指定された長さでカット。
//
//  パラメタ説明
//    AnsiString sMaster：対象文字列
//    int iLenMAX       ：最大文字数
//
//  戻り値
//    なし。
//
//  備考
//　田村さん作成 ↓
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::CutStrLenMAX(AnsiString sMaster,int iLenMAX)
{
    AnsiString sBuf;


	//sMasterの最大文字数はiLenMAX
	if ( sMaster.Length() > iLenMAX ) {
		if ( sMaster.ByteType(iLenMAX) == mbLeadByte ) {
			sBuf = sMaster.SubString(1,iLenMAX-1);
		} else {
			sBuf = sMaster.SubString(1,iLenMAX);
		}
	} else {
    	sBuf = sMaster;
	}


    return ( sBuf );
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数    ：文字列の最後の1文字をカット。
//
//  機能説明
//    文字列の最後が2バイト文字だとカットします。
//
//  パラメタ説明
//    AnsiString sMaster：対象文字列
//
//  戻り値
//    なし。
//
//  備考
//　田村さん作成 ↓
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::CutStrEndChar(AnsiString sMaster)
{
	int iLength;
    AnsiString sBuf;

    iLength = sMaster.Length();

    if ( sMaster.ByteType(iLength-1) == mbLeadByte ) {
    	sBuf = sMaster.SubString(1,iLength-2);
    } else {
    	sBuf = sMaster.SubString(1,iLength-1);
    }

    return ( sBuf );

}
//---------------------------------------------------------------------------


//指定した配列のiPos番目の値の取得は可能か？
bool __fastcall TForm1::ChkSize(HANDLE hChk, int iPos, long lSize)
{
    //int iChkPos;


/*
    long lFlags = GlobalFlags( hChk );
    //指定されたグローバルハンドルは有効か？
    if ( lFlags == GMEM_INVALID_HANDLE ) {
    	return ( false );
    }
*/
	WORD wSize  = (WORD)GlobalSize( hChk );
    //配列のサイズチェック
    if ( wSize <= 0 ) {
    	return ( false );
    }
/* とりあえず メモリ確保してたらOKにします。 2003.05.17
    //iPosは配列の有効な位置か？
    iChkPos = wSize / lSize;
    if ( iChkPos <= iPos ) {
    	return ( false );
    }

*/
    return ( true );

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数    ：グラフの初期化を行います。
//
//  機能説明
//    グラフの初期化を行います。
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    なし。
//
//  備考
//　 古門さん作成 ↓
//
//---------------------------------------------------------------------------
void TForm1::Graph_Format()
{
    //TODO この下にコードを追加してください
    int CharWidth;                                //Y軸座標値を描画するための余白
    int CharHeight;                               //X軸座標値を描画するための余白
    int FontHeight;
	int ImageW,ImageH;                            //イメージの高さ、幅
	int x,y,yst,i1,i;
	double dMaxMinHeight;
    TImage *glh;

	for ( i = 0; i < 2; i++ ){
	    if (i == 0) {
		    glh = ImgGlaphSYUKA;
	    } else {
		    glh = ImgGlaphSOZAI;
		}

		glh->Canvas->Pen->Color = clBlack;
		glh->Canvas->Pen->Style = (TPenStyle)bsSolid;
		glh->Canvas->Pen->Width = 1;       //線の太さ
		glh->Canvas->Font->Size = 7;       //文字のサイズ

		glh->Canvas->Brush->Color = clWhite;
		glh->Canvas->Rectangle(0,0,glh->Width,glh->Height);

		//グラフ描画の際に使用する定数の設定
		CharWidth 	= glh->Canvas->Font->Height * 3;   //左端とY軸の間の余白
		CharHeight 	= glh->Canvas->Font->Height * 2;  //下端とX軸の間の余白
		FontHeight 	= glh->Canvas->Font->Height;      //文字の高さ
		ImageH = glh->Height - 2* CharHeight;
		ImageW = glh->Width - CharWidth;

		//グラフの描画
		glh->Canvas->Brush->Color =clWhite;
		glh->Canvas->Pen->Color =clGray;

		//上限ライン
		glh->Canvas->Pen->Color = clGray;
		y = 1 * (glh->Height/9);
		glh->Canvas->Rectangle(1,y-1,glh->Width-1,y);

		//上限下限の間ライン
		yst = 1 * (glh->Height/9);
		x=( 7 * (glh->Height/9) );
		for(i1=1;i1<8;i1++)
		{
			if( i1 == 2 || i1 == 4 || i1 == 6 ) {
				glh->Canvas->Pen->Color = clGray;
			} else {
				glh->Canvas->Pen->Color = clSilver;
			}
			y = yst + ( i1 * (x/8) );
			glh->Canvas->Rectangle(1,y,glh->Width-1,y+1);
		}

		//下限ライン
		glh->Canvas->Pen->Color = clGray;
		y = 8 * (glh->Height/9);
		glh->Canvas->Rectangle(1,y-1,glh->Width-1,y);

		//x軸ライン
		glh->Canvas->Pen->Color = clGray;
		dMaxMinHeight = (glh->Height/9)*8 - (glh->Height/9);
		for(i1 = 0;i1 < 10;i1++)
		{
			x =	((ImageW) / 12) * (9-i1)+glh->Canvas->Font->Size+20;
			glh->Canvas->Rectangle(x+10,1,x+11,glh->Height-1);
		}
	}


}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数    ：入力文字のチェックを行ない、有効な文字列を返します。
//
//  機能説明
//    入力文字のチェックを行ない、有効な文字列（”’”、”，”抜き）を返します。
//
//  パラメタ説明
//    AnsiString sTarget    ：入力文字
//    int iLenMAX           ：文字列最大長
//
//  戻り値
//    なし。
//
//  備考
//　  なし。 ↓
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::GetValidityData(AnsiString sTarget, int iLenMAX)
{
	AnsiString sBuf;

    sBuf = sTarget;

    // シングルコーテーションはＤＢ登録時にエラーが発生する
    // ので全角のシングルコーテーションに変換します
    sBuf = ReplaceStrAtoB( sBuf, "'", "’");

    // 半角カンマはレポート出力時にエラーが発生する
    // ので全角のカンマに変換します
    sBuf = ReplaceStrAtoB( sBuf, ",", "，");

	//長さチェック
    sBuf = CutStrLenMAX( sBuf, iLenMAX);

    return ( sBuf );


}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数    ：備考欄の入力文字をチェックします。
//
//  機能説明
//    備考欄の文字列が、有効な文字列か（”’”、”，”抜き）を返します。
//  　また、入力されたロットのUPDATEフラグをtrueにします。
//
//  パラメタ説明
//    AnsiString sTarget    ：入力文字
//    int iLenMAX           ：文字列最大長
//
//  戻り値
//    なし。
//
//  備考
//　  なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Mem_MEMOKeyPress(TObject *Sender, char &Key)
{
    AnsiString sBuf;
    AnsiString sNum;
    int iNum;
    TMemo* memoBuf = dynamic_cast<TMemo*>(Sender);
    sBuf = memoBuf->Text;

    int iLenMAX = 128;
	ChkInputData( sBuf, 9, Sender, Key, iLenMAX);
    sNum = memoBuf->Name;
    iNum = sNum.SubString(15,sNum.Length()-14).ToIntDef(0);
    if(sNum.SubString(5,5) == "vRIRE" )
    {
        pRIRE_KSD01_DATA[iNum].UPD_FLG = true;
    }
    else
    {
        pSOKU_KSD01_DATA[iNum].UPD_FLG = true;
    }
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数    ：備考欄の入力文字をチェックします。
//
//  機能説明
//    備考欄の文字列が、有効な文字列か（”’”、”，”抜き）を返します。
//  　また、入力されたロットのUPDATEフラグをtrueにします。
//
//  パラメタ説明
//    AnsiString sTarget    ：入力文字
//    int iLenMAX           ：文字列最大長
//
//  戻り値
//    なし。
//
//  備考
//　  なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Edt_LOTNOChange(TObject *Sender)
{
    int			i;
    int			iSelStart;
    AnsiString	sBuf;
    TEdit* edt = dynamic_cast<TEdit*>(Sender);


    sBuf = edt->Text;
    iSelStart = edt->SelStart;

    // シングルコーテーションはＤＢ登録時にエラーが発生する
    // ので全角のシングルコーテーションに変換します
    i = sBuf.AnsiPos("'");
    if( i > 0 ){
        sBuf.Delete( i, 1);
        if( edt->MaxLength == 0 || edt->MaxLength >= sBuf.Length() + 2 ){
        	sBuf.Insert("’",i);
    	}
        //edt->Text = sBuf;
        //edt->SelStart = i + 1;
       	iSelStart = i + 1;
    }
    edt->Text = sBuf.UpperCase();
    edt->SelStart = iSelStart;
}


//---------------------------------------------------------------------------
//
//  概要
//    自作関数    ：日付入力をチェックします。
//
//  機能説明
//    日付入力をチェックします。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    char &Key         ：入力された文字コード
//
//  戻り値
//    なし。
//
//  備考
//　  なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tKeyPress(TObject *Sender, char &Key)
{
	int iRow,iCol;
    AnsiString sBuf;
	int iVALUE_TYPE;

	TStringGrid		*Sgr = (TStringGrid *)Sender;

	iCol = Sgr->Col;
	iRow = Sgr->Row;
    sBuf = Sgr->Cells[iCol][iRow];
    iVALUE_TYPE = 4;
	ChkInputData( sBuf, iVALUE_TYPE, Sender, Key, 8);

}

//---------------------------------------------------------------------------
//
//  概要
//    OnCloseQuery イベント ：Close メソッドが呼び出されたとき，またはユーザーがフォームの
//                          　システムメニューで［閉じる］を選択したときに発生します。
//
//  機能説明
//    ユーザーが戻るボタン押下かメインフォームの閉じる（「X」ボタン）を押下時に発生して
//    メッセージを出力します。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    bool &CanClose    ：フォームのクローズが可能かどうかを決める論理型変数
//
//  戻り値
//    なし。
//
//  備考
//　  なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	TMsgDlgButtons mRet;
	AnsiString sBuf;
	TShiftState State;
	TMsgDlgButtons MsgButton;

    CanClose = true;

    if( UPDATE_CHECK())
    {
        if( !ALL_INSPECT())
        {
            sBuf  = "未測定の項目が有ります。保存してメインメニューに戻りますか？";
            sBuf += "\n[は　い] 未測定項目ありのまま、保存して戻ります。";
            sBuf += "\n[いいえ] 内容を破棄して戻ります。";
            sBuf += "\n[キャンセル] 戻りません。";
            switch( MessageDlg( sBuf, mtWarning, mbYesNoCancel, 0) )
            {
            // 「Yes」      保存
            case mrYes:
                bQUIT_FLG = true;
            	BtnF11Click(Sender);
                CanClose = true;
                break;
            // 「No」       変更を破棄
            case mrNo:
                CanClose = true;
            	break;
    	    // 「Cancel」   キャンセル
            case mrCancel:
                CanClose = false;
            	return;
             }
        }
        else
	    {
        	sBuf  = "データが変更されています。変更内容を保存してメインメニューに戻りますか？";
            sBuf += "\n[は　い] 変更内容を保存して戻ります。";
            sBuf += "\n[いいえ] 変更内容を破棄して戻ります。";
            sBuf += "\n[キャンセル] 戻りません。";
            switch( MessageDlg( sBuf, mtConfirmation, mbYesNoCancel, 0) )
            {
            // 「Yes」      保存                  
            case mrYes:
                bQUIT_FLG = true;
        	    BtnF11Click(Sender);
                CanClose = true;
                break;
            // 「No」       変更を破棄
            case mrNo:
                CanClose = true;
            	break;
        	// 「Cancel」   キャンセル
            case mrCancel:
                CanClose = false;
        	    return;
             }
        }
    }                               
    else
    {
        // 確認
        sBuf  = "メインメニューに戻ります。よろしいですか？";
        sBuf += "\n[は　い] メインメニューに戻ります。";
        sBuf += "\n[キャンセル] 戻りません。";
        MsgButton << mbYes << mbCancel;
        switch( MessageDlg( sBuf, mtConfirmation , MsgButton, 0) ){
        // 「Yes」      保存
        case mrYes:
            break;
        // 「Cancel」   キャンセル
        case mrCancel:
            CanClose = false;
            return;
        }
    }
	CommClose(1);
	//2003.05.08 E.Takase Add↑
	//2003.05.08 E.Takase Add コメント↓
	//delete sRIREKI_LOT;
    //delete sHT_LOT;
    //delete sShiji_Data;
    //2003.05.08 E.Takase Add コメント↑
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClose イベントは    ：フォームを閉じたときに発生します。
//
//  機能説明
//    フォームを閉じる際、明示的に全QueryをCloseし、DataBaseをCloseします。
//    メッセージを出力します。
//
//  パラメタ説明
//    TObject *Sender	        ：呼び出し元のVCLオブジェクト
//     TCloseAction &Action     ：フォームを実際に閉じるどうかを決めます。
//
//  戻り値
//    なし。
//
//  備考
//　  なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
    //2003.05.08 E.Takase Add↓
	Query1->Close();
	Query2->Close();
	Query3->Close();
	Query4->Close();
	Query5->Close();
	Query6->Close();
	Query7->Close();
	Query8->Close();
	Query10->Close();
	QueryTANTO->Close();
	QueryTANTO2->Close();
	Database1->Close();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
//  概要
//    自作関数：    	：判定音発生用の判定を行います。
//
//  機能説明
//    セルの入力値を判定します。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int ACol          ：対象セルのカラム位置
//    int ARow          ：対象セルのＲＯＷ位置
//  戻り値
//    判定結果（０：ＯＫ、１:ＮＧ、２:以外（空欄など））
//
//  備考
//    ４つのグリッドに処理は分かれていますが、参照メモリの位置などが違うだけで内容は同じです。
//
//---------------------------------------------------------------------------
int __fastcall TForm1::CELL_HANTEI(TObject *Sender,int ACol,int ARow)
{
	if(iDEBUG == 1) return(2);
	AnsiString asString,sBuf,sBuf2;
	int i1;
	int iGridTag;
	AnsiString	sDeci1,sDeci2;
	double dMAX,dMIN;
	AnsiString sTemp;
	int iKIKA_KIND;			//1：上下限判定、2：以下、3：以上
	bool bRtn;	 			//2003.05.08 E.Takase Add
	double dBuf;	 		//2003.05.08 E.Takase Add
	AnsiString sComp1,sComp2,sTempComp;	//表示値と印刷値を比較するバッファ
    int iHANTEI;

    //メモリがあるかを判断します
	if(Sender == SGr_vSOKU_SYUKA)
	{
		iGridTag = 1;
		asString = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
		SGr_vSOKU_SYUKA->Canvas->Font->Size = 12;
		if(!hCELLINFO_SOKU_SYUKA) return(2);
	}
	if(Sender == SGr_vRIRE_SYUKA)
	{
		iGridTag = 2;
		asString = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
		SGr_vRIRE_SYUKA->Canvas->Font->Size = 12;
		if(!hCELLINFO_RIRE_SYUKA) return(2);
	}
	if(Sender == SGr_vSOKU_SOZAI)
	{
		iGridTag = 3;
		asString = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
		SGr_vSOKU_SOZAI->Canvas->Font->Size = 12;
		if(!hCELLINFO_SOKU_SOZAI) return(2);
	}
	if(Sender == SGr_vRIRE_SOZAI)
	{
		iGridTag = 4;
		asString = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
		SGr_vRIRE_SOZAI->Canvas->Font->Size = 12;
		if(!hCELLINFO_RIRE_SOZAI) return(2);
	}
/////////////////////////////////////////////////////////////////////
//以下は測定項目の表示についてのコードです
	switch( iGridTag )
	{
	case 1:
	//配列が取れていないので描画を中止します
		if(!hCELLINFO_SOKU_SYUKA) return(2);
		break;
	case 2:
	//配列が取れていないので描画を中止します
		if(!hCELLINFO_RIRE_SYUKA) return(2);
		break;
	case 3:
	//配列が取れていないので描画を中止します
		if(!hCELLINFO_SOKU_SOZAI) return(2);
		break;
	case 4:
	//配列が取れていないので描画を中止します
		if(!hCELLINFO_RIRE_SOZAI) return(2);
		break;
	}

	switch( iGridTag )
	{
	//出荷測定画面
	case 1:
		if(!hCELLINFO_SOKU_SYUKA) return(2);
		// 2003/06/02 K.Yamada 対象セルが無い時は、処理を中止します
		if( SGr_vSOKU_SYUKA->RowCount == 1 ) return(2);

		if(Form1->SGr_tSOKU->Cells[0][0]!="" && hCELLINFO_SOKU_SYUKA != NULL)
		{
			if( hCELLINFO_SOKU_SYUKA )
			{
            //入力が数値の場合、規格を算出する
				if((AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 1)
				|| (AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 2))
				{
					dMAX = pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].MAX;
					dMIN = pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].MIN;
				}
			}
		}
	//以上以下の規格の場合対策
		iKIKA_KIND = 1;		//デフォルトは上下限で判定
		if(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].KIKA_TYPE) == 1)
		{
			if(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].KIKA_KIND) == 2)
			{
				iKIKA_KIND = 2;
			}
			else if(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].KIKA_KIND) == 3)
			{
				iKIKA_KIND = 3;
			}
		}

//フォーマット調整
		if(hCELLINFO_SOKU_SYUKA )
		{
            //文字列が不要ならの処理ですが今は処理そのものが不要です（不要文字列で見なくなった為）
			if(asString == "不要"
			|| AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].RESULT) == "不要")
			{
				sBuf = "不要";
				//セル入力をバッファに取り込む
				strcpy(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].RESULT		,sBuf.c_str());
				strcpy(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].DISP_RESULT,sBuf.c_str());
				pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].JUDGE = 2;
			}
			else
			{
                //整数、少数、角度の場合はフォーマット文字列を作成します
				switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:		//整数・少数
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_SOKU_SYUKA[(ACol*SGr_vSOKU_SYUKA->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( sDeci1.Length() == 1 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 1:		//角度
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_SOKU_SYUKA[(ACol*SGr_vSOKU_SYUKA->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( sDeci1.Length() == 1 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 2:  	//良・否
					break;
				default:	//文字
					break;
				}
				switch(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*SGr_vSOKU_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:
                    //入力がなければバッファを空にします
					if(AnsiString(SGr_vSOKU_SYUKA->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}
                    //高瀬さんの判定式を使い無効入力でもエラーを出さないようにします。
					//2003.05.08 E.Takase Add↓
					bRtn = ConvDoubleDefS(SGr_vSOKU_SYUKA->Cells[ACol][ARow],sDeci1,SGr_vSOKU_SYUKA->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add↑

					//良否判定
					//2003.05.08 E.Takase Add↓
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
                        //以下判定
						case 2:
							if( dBuf <= dMAX  )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
							break;
                        //以上判定
						case 3:
							if( dBuf >= dMIN )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
							break;
                        //範囲判定
						default:
                            // 2003/10/06 A.Tamura なぜか規格内なのに規格外と判定されるのでDouble型を再設定します。
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
						}

					} else {
                        iHANTEI = 2;
					}
					//2003.05.08 E.Takase Add↑
					break;
				case 1:
					if(AnsiString(SGr_vSOKU_SYUKA->Cells[ACol][ARow]).Length() == 0)
					{
                        iHANTEI = 2;
					}
					//2003.05.08 E.Takase Add↓
					bRtn = ConvDoubleDefS(SGr_vSOKU_SYUKA->Cells[ACol][ARow],sDeci1,SGr_vSOKU_SYUKA->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add↑

					//良否判定
					//2003.05.08 E.Takase Add↓
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
                        //以下判定
						case 2:
							if( dBuf <= dMAX )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
							break;
                        //以上判定
						case 3:
							if( dBuf >= dMIN )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
							break;
                        //範囲判定
						default:
                            // 2003/10/06 A.Tamura なぜか規格内なのに規格外と判定されるのでDouble型を再設定します。
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN)
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
						}
					} else {
						iHANTEI = 2;
					}
					//2003.05.08 E.Takase Add↑

					break;
				case 2:
                    //良否判定
                    iHANTEI = 2;
					sBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
					sBuf = sBuf.Trim();
					if( sBuf == 0 || sBuf == "良")
					{
                        iHANTEI = 0;
					}
					else if( sBuf.Length() != 0)
					{
                        iHANTEI = 1;
					}
					break;
				default:
                    //文字列判定
                    iHANTEI = 2;
					sBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
                    if(sBuf.Length() != 0 ) iHANTEI = 0;
				}
			}
		}
		break;
    //以降Case2、3、4（出荷検査履歴、素材検査出荷、素材検査履歴）も処理内容は同じです
   case 2:
		if(!hCELLINFO_RIRE_SYUKA) return(2);
		// 2003/06/02 K.Yamada 対象セルが無い時は、処理を中止します
		if( SGr_vRIRE_SYUKA->RowCount == 1 ) return(2);

		if(Form1->SGr_tRIRE->Cells[0][0]!="" && hCELLINFO_RIRE_SYUKA != NULL)
		{
			if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
				sBuf = pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount + ARow].RESULT;
			}
			sBuf = pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount + ARow].DISP_RESULT;
			if( hCELLINFO_RIRE_SYUKA )
			{
//入力が数値の場合、規格を算出する
				if((AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 1)
				|| (AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 2))
				{
					dMAX = pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].MAX;
					dMIN = pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].MIN;
				}
			}
		}

	//以上以下の規格の場合対策
		iKIKA_KIND = 1;		//デフォルトは上下限で判定
		if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].KIKA_TYPE) == 1)
		{
			if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].KIKA_KIND) == 2)
			{
				iKIKA_KIND = 2;
			}
			else if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].KIKA_KIND) == 3)
			{
				iKIKA_KIND = 3;
			}
		}
//フォーマット調整
		if(hCELLINFO_RIRE_SYUKA )
		{
			if(asString == "不要"
			|| AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].RESULT) == "不要")
			{
				sBuf = "不要";
				//セル入力をバッファに取り込む
				strcpy(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].RESULT		,sBuf.c_str());
				strcpy(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].DISP_RESULT,sBuf.c_str());
				pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].JUDGE = 2;
			}
			else
			{
				switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:		//整数・少数
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_RIRE_SYUKA[(ACol*SGr_vRIRE_SYUKA->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( sDeci1.Length() == 1 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 1:		//角度
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_RIRE_SYUKA[(ACol*SGr_vRIRE_SYUKA->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( sDeci1.Length() == 1 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 2:  	//良・否
					break;
				default:	//文字
					break;
				}
				switch(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*SGr_vRIRE_SYUKA->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:
					if(AnsiString(SGr_vRIRE_SYUKA->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}
					//2003.05.08 E.Takase Add↓
					bRtn = ConvDoubleDefS(SGr_vRIRE_SYUKA->Cells[ACol][ARow],sDeci1,SGr_vRIRE_SYUKA->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add↑
					//良否判定
					//2003.05.08 E.Takase Add↓
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
						case 2:
							if( dBuf <= dMAX )
							{
                                iHANTEI = 0;
							}
							else
							{
                                iHANTEI = 1;
							}
							break;
						case 3:
							if( dBuf >= dMIN )
							{
                                iHANTEI = 0;
							}
							else
							{
                                iHANTEI = 1;
							}
							break;
						default:
                            // 2003/10/06 A.Tamura なぜか規格内なのに規格外と判定されるのでDouble型を再設定します。
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN)
							{
                                iHANTEI = 0;
							}
							else
							{
                                iHANTEI = 1;
							}
						}
					} else {
                        iHANTEI = 2;
					}
					//2003.05.08 E.Takase Add↑
					break;
				case 1:
					if(AnsiString(SGr_vRIRE_SYUKA->Cells[ACol][ARow]).Length() == 0)
					{
                        iHANTEI = 2;
					}

					//2003.05.08 E.Takase Add↓
					bRtn = ConvDoubleDefS(SGr_vRIRE_SYUKA->Cells[ACol][ARow],sDeci1,SGr_vRIRE_SYUKA->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add↑
					//良否判定
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
						case 2:
							if( dBuf <= dMAX )
							{
                                iHANTEI = 0;
							}
							else
							{
                                iHANTEI = 1;
							}
							break;
						case 3:
							if( dBuf >= dMIN )
							{
                                iHANTEI = 0;
							}
							else
							{
                                iHANTEI = 1;
							}
							break;
						default:
                            // 2003/10/06 A.Tamura なぜか規格内なのに規格外と判定されるのでDouble型を再設定します。
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

                            // 2003/10/06 A.Tamura なんでこんなコードなの？　元にもどす
							//if( dBuf <= dMAX && sBuf.ToDouble() >= dMIN)
							if( dBuf <= dMAX && dBuf >= dMIN)
							{
                                iHANTEI = 0;
							}
							else
							{
                                iHANTEI = 1;
							}
						}

					} else {
                        iHANTEI = 2;
					}
					//2003.05.08 E.Takase Add↑

					break;
				case 2:
                    iHANTEI = 2;
					sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
					sBuf = sBuf.Trim();
					if( sBuf == 0 || sBuf == "良")
					{
                                iHANTEI = 0;
					}
					else if( sBuf.Length() != 0)
					{
                                iHANTEI = 1;
					}
					break;
				default:
                    iHANTEI = 2;
					sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
                    if(sBuf.Length() != 0 ) iHANTEI = 0;
				}
			}
		}
		break;
//測定素材画面
   case 3:
		if(!hCELLINFO_SOKU_SOZAI) return(2);
		// 2003/06/02 K.Yamada 対象セルが無い時は、処理を中止します
		if( SGr_vSOKU_SOZAI->RowCount == 1 ) return(2);
		if(Form1->SGr_tSOKU->Cells[0][0]!="" && hCELLINFO_SOKU_SOZAI != NULL)
		{
			if(SGr_vSOKU_SOZAI->Color != 0x00DDDDDD){
				sBuf = pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount + ARow].RESULT;
			}
			sBuf = pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount + ARow].DISP_RESULT;
			if( hCELLINFO_SOKU_SOZAI )
			{
//入力が数値の場合、規格を算出する
				if((AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 1)
				|| (AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 2))
				{
					dMAX = pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].MAX;
					dMIN = pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].MIN;
				}
			}
		}
	//以上以下の規格の場合対策
		iKIKA_KIND = 1;		//デフォルトは上下限で判定
		if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].KIKA_TYPE) == 1)
		{
			if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].KIKA_KIND) == 2)
			{
				iKIKA_KIND = 2;
			}
			else if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].KIKA_KIND) == 3)
			{
				iKIKA_KIND = 3;
			}
		}

//フォーマット調整
		if(hCELLINFO_SOKU_SOZAI )
		{
			if(asString == "不要"
			|| AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].RESULT) == "不要")
			{
				sBuf = "不要";
				//セル入力をバッファに取り込む
				strcpy(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].RESULT		,sBuf.c_str());
				strcpy(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].DISP_RESULT,sBuf.c_str());
				pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].JUDGE = 2;
			}
			else
			{
				switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:		//整数・少数
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_SOKU_SOZAI[(ACol*SGr_vSOKU_SOZAI->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( i1 == 0 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 1:		//角度
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_SOKU_SOZAI[(ACol*SGr_vSOKU_SOZAI->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( i1 == 0 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 2:  	//良・否
					break;
				default:	//文字
					break;
				}
				switch(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*SGr_vSOKU_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:
					if(AnsiString(SGr_vSOKU_SOZAI->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}
					//2003.05.08 E.Takase Add↓
					bRtn = ConvDoubleDefS(SGr_vSOKU_SOZAI->Cells[ACol][ARow],sDeci1,SGr_vSOKU_SOZAI->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add↑
					//良否判定
					//2003.05.08 E.Takase Add↓
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
						case 2:
							if( dBuf <= dMAX )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
							break;
						case 3:
							if( dBuf >= dMIN )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
							break;
						default:
                            // 2003/10/06 A.Tamura なぜか規格内なのに規格外と判定されるのでDouble型を再設定します。
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN)
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
						}
					} else {
						iHANTEI = 2;
					}
					//2003.05.08 E.Takase Add↑
					break;
				case 1:
					if(AnsiString(SGr_vSOKU_SOZAI->Cells[ACol][ARow]).Length() == 0)
					{
						iHANTEI = 2;
					}
					//2003.05.08 E.Takase Add↓
					bRtn = ConvDoubleDefS(SGr_vSOKU_SOZAI->Cells[ACol][ARow],sDeci1,SGr_vSOKU_SOZAI->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add↑
					//良否判定
					//2003.05.08 E.Takase Add↓
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
						case 2:
							if( dBuf <= dMAX )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
							break;
						case 3:
							if( dBuf >= dMIN )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
							break;
						default:
                            // 2003/10/06 A.Tamura なぜか規格内なのに規格外と判定されるのでDouble型を再設定します。
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN)
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
						}
					} else {
                        iHANTEI = 2;
					}
					//2003.05.08 E.Takase Add↑

					break;
				case 2:
                    iHANTEI = 2;
					sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
					sBuf = sBuf.Trim();
					if( sBuf == 0 || sBuf == "良")
					{
						iHANTEI = 0;
					}
					else if( sBuf.Length() != 0)
					{
						iHANTEI = 1;
					}
					break;
				default:
                    iHANTEI = 2;
					sBuf = SGr_vSOKU_SOZAI->Cells[ACol][ARow];
                    if( sBuf.Length() != 0 ) iHANTEI = 0;
				}
			}
		}
		break;
//履歴素材グリッド
   case 4:
		if(!hCELLINFO_RIRE_SOZAI) return(2);
		// 2003/06/02 K.Yamada 対象セルが無い時は、処理を中止します
		if( SGr_vRIRE_SOZAI->RowCount == 1 ) return(2);

		if(Form1->SGr_tRIRE->Cells[0][0]!="" && hCELLINFO_RIRE_SOZAI != NULL)
		{
			if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
				sBuf = pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount + ARow].RESULT;
			}
			sBuf = pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount + ARow].DISP_RESULT;
			if( hCELLINFO_RIRE_SOZAI )
			{
//入力が数値の場合、規格を算出する
				if((AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 1)
				|| (AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].KIKA_TYPE).ToIntDef(0) == 2))
				{
					dMAX = pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].MAX;
					dMIN = pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].MIN;
				}
			}
		}
	//以上以下の規格の場合対策
		iKIKA_KIND = 1;		//デフォルトは上下限で判定
		if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].KIKA_TYPE) == 1)
		{
			if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].KIKA_KIND) == 2)
			{
				iKIKA_KIND = 2;
			}
			else if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].KIKA_KIND) == 3)
			{
				iKIKA_KIND = 3;
			}
		}

//フォーマット調整
		if(hCELLINFO_RIRE_SOZAI )
		{
			if(asString == "不要"
			|| AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].RESULT) == "不要")
			{
				sBuf = "不要";
				//セル入力をバッファに取り込む
				strcpy(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].RESULT		,sBuf.c_str());
				strcpy(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].DISP_RESULT,sBuf.c_str());
				pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].JUDGE = 2;
			}
			else
			{
				switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:		//整数・少数
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_RIRE_SOZAI[(ACol*SGr_vRIRE_SOZAI->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( sDeci1.Length() == 1 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 1:		//角度
   					sDeci1 = "0";
					for(i1 = 0;i1 < AnsiString(pCELLINFO_RIRE_SOZAI[(ACol*SGr_vRIRE_SOZAI->RowCount)+ARow].VALUE_DECI).ToIntDef(0);i1++)
					{
						if( sDeci1.Length() == 1 ) sDeci1 += ".";
						sDeci1 +="0";
					}
					break;
				case 2:  	//良・否
					break;
				default:	//文字
					break;
				}
				//SGr_vRIRE_SOZAI->Canvas->Font->Color = clBlack;		//判定用色初期値はOKで
				switch(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*SGr_vRIRE_SOZAI->RowCount+ARow].VALUE_TYPE).ToIntDef(0))
				{
				case 0:
					if(AnsiString(SGr_vRIRE_SOZAI->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}
					//2003.05.08 E.Takase Add↓
					bRtn = ConvDoubleDefS(SGr_vRIRE_SOZAI->Cells[ACol][ARow],sDeci1,SGr_vRIRE_SOZAI->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add↑

					//セル入力をバッファに取り込む
					if(hCELLINFO_RIRE_SOZAI)
					{
						//印刷用画面で以外
						if(SGr_vRIRE_SOZAI->Color != 0x00DDDDDD){
							sBuf = sBuf.SubString(1,14);
							if( sBuf.Length() == 14 ){
								if ( sBuf.ByteType( 14 ) == mbLeadByte ){
									sBuf = sBuf.SubString(1,13);
								}
							}
							strcpy(pCELLINFO_RIRE_SOZAI[ACol*Form1->SGr_vRIRE_SOZAI->RowCount+ARow].RESULT,sBuf.c_str());
						}
					}
					//良否判定
					//2003.05.08 E.Takase Add↓
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);

						switch( iKIKA_KIND )
						{
						case 2:
							if( dBuf <= dMAX )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
							break;
						case 3:
							if( dBuf >= dMIN )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
							break;
						default:
                            // 2003/10/06 A.Tamura なぜか規格内なのに規格外と判定されるのでDouble型を再設定します。
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN)
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
						}

					} else {
						iHANTEI = 2;
					}
					//2003.05.08 E.Takase Add↑
					break;
				case 1:
					if(AnsiString(SGr_vRIRE_SOZAI->Cells[ACol][ARow]).Length() == 0)
					{
						sBuf ="";
					}

					//2003.05.08 E.Takase Add↓
					bRtn = ConvDoubleDefS(SGr_vRIRE_SOZAI->Cells[ACol][ARow],sDeci1,SGr_vRIRE_SOZAI->Cells[ACol][ARow],&sBuf);
					//2003.05.08 E.Takase Add↑

					//良否判定
					//2003.05.08 E.Takase Add↓
					if ( bRtn ) {
						dBuf = ConvDoubleDefD(sBuf,0.0);
						switch( iKIKA_KIND )
						{
						case 2:
							if( dBuf <= dMAX )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
							break;
						case 3:
							if( dBuf >= dMIN )
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
							break;
						default:
                            // 2003/10/06 A.Tamura なぜか規格内なのに規格外と判定されるのでDouble型を再設定します。
                            sBuf2 = AnsiString(dMAX);
                            dMAX  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dMIN);
                            dMIN  = sBuf2.ToDouble();
                            sBuf2 = AnsiString(dBuf);
                            dBuf  = sBuf2.ToDouble();

							if( dBuf <= dMAX && dBuf >= dMIN)
							{
								iHANTEI = 0;
							}
							else
							{
								iHANTEI = 1;
							}
						}
					} else {
						iHANTEI = 2;
					}
					//2003.05.08 E.Takase Add↑

					break;
				case 2:
                    iHANTEI = 2;
					sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
					sBuf = sBuf.Trim();
					if( sBuf == 0 || sBuf == "良")
					{
						iHANTEI = 0;
					}
					else if( sBuf.Length() != 0)
					{
						iHANTEI = 1;
					}
                    break;
				default:
					iHANTEI = 2;
					sBuf = SGr_vRIRE_SOZAI->Cells[ACol][ARow];
                    if(sBuf.Length()!=0) iHANTEI = 0;
				}
			}
		}
	}
    return(iHANTEI);
}



//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
//  概要
//    自作関数    ：備考欄にフォーカスがあたった場合の処理を行います。
//
//  機能説明
//    BtnF01 を　有効にします。。
//    Form2->Tag の値を12にセットし「一覧検索」ボタン押下後の処理を有効にします。
//
//  パラメタ説明
//  　TObject *Sender   ：呼び出し元のVCLオブジェクト(動的コントロール（MEMO））
//
//  戻り値
//    AnsiString sMEMO_NAME ：呼び出し元MEMOの名前
//
//  備考
//　  なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Mem_MEMOEnter(TObject *Sender)
{
    TMemo* memoBuf = dynamic_cast<TMemo*>(Sender);

    sMEMO_NAME = memoBuf->Name;
    Form2->Tag = 12;
    BtnF01->Enabled = true;
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数    ：備考欄からフォーカスが外れた場合の処理を行います。
//
//  機能説明
//    BtnF01 を　無効にします。。
//    Form2->Tag の値を0にセットし「一覧検索」ボタン押下後の処理を無効にします。
//
//  パラメタ説明
//  　TObject *Sender   ：呼び出し元のVCLオブジェクト(動的コントロール（MEMO））
//
//  戻り値
//    なし。
//
//  備考
//　  なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Mem_MEMOExit(TObject *Sender)
{
    Form2->Tag = 0;
    BtnF01->Enabled = false;
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数：検査ロットに分割表で測定されたものがあるかを調べます。
//
//  機能説明
//    �@同一ロットが分割表にあればフラグをTrueにして再描画を行います。
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
void __fastcall TForm1::BUNKATU_CHECK(void)
{
	AnsiString sBuf,sLot;
	int iCol;
    int i1;
	AnsiString sSelectLot;
    bool bBUNKATUARI;

//フラグの初期化
    for(i1 = 0;i1<1000;i1++)
    {
        bBUNKATU_RIRE[i1] = false;
        bBUNKATU_SOKU[i1] = false;
    }
//sLot に　分割表で測定するロットを代入し、履歴があるかを調べる
//分割表過去実績のロード＆配列代入
	sLot = "";
//検査中のロットの読み込み
    for(iCol = 0; iCol < SGr_tRIRE->ColCount;iCol++)
    {
		if(SGr_tRIRE->Cells[iCol][0].Length() !=0)
		{
			sLot += "'" + SGr_tRIRE->Cells[iCol][0] + "',";
		}
	}
    for(iCol = 0; iCol < SGr_tSOKU->ColCount;iCol++)
    {
		if(SGr_tSOKU->Cells[iCol][0].Length() !=0)
		{
			sLot += "'" + SGr_tSOKU->Cells[iCol][0] + "',";
		}
	}
	sLot = sLot.SubString(1,sLot.Length()-1);

    //2003.05.12 E.Takase Add↓
/* 2005.09.26 Y.Sano 検証用削除
    sBuf  = "SELECT  KSD11.*, SM12S.TANNAM As UPDNAME ";*/
/* 2005.09.26 Y.Sano 検証用追加*/
    sBuf  = "SELECT  KSD11.LOTNO, SM12S.TANNAM As UPDNAME ";
    sBuf += " FROM KSD11 LEFT JOIN SM12S ON KSD11.UPDCHR = SM12S.TANSYA ";
    //2003.05.12 E.Takase Add↑
    sBuf += " WHERE DTKSHIN ='" + sNowDTKSHIN + "'";
    if( sLot.Length() > 3 ) {
        sBuf += " AND LOTNO IN ("+ sLot + ")";
    }
    //2003.05.12 E.Takase Add↓
    sBuf += " ORDER BY LOTNO,KSD11.UPDYMD,KSD11.UPDTIM";
    //2003.05.12 E.Takase Add↑

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();
    Query1->SQL->Add(sBuf);
    Query1->Open();
    Query1->Active = true;

    while( Query1->Eof == false )
    {
        sSelectLot = Query1->FieldValues["LOTNO"];
        bBUNKATUARI = false;
        for(iCol = 0; iCol < SGr_tRIRE->ColCount;iCol++)
        {
            if(sSelectLot == SGr_tRIRE->Cells[iCol][0])
            {
                bBUNKATUARI = true;
                bBUNKATU_RIRE[iCol] = true;
                break;
            }
        }
        if(bBUNKATUARI == false )
        {
            for(iCol = 0; iCol < SGr_tSOKU->ColCount;iCol++)
            {
                if(sSelectLot == SGr_tSOKU->Cells[iCol][0])
                {
                    bBUNKATU_SOKU[iCol] = true;
                    break;
                }
            }
        }
        Query1->Next();
    }
    Query1->Close();
    for(iCol = 0; iCol < SGr_tRIRE->ColCount;iCol++)
    {
		if(SGr_tRIRE->Cells[iCol][0].Length() !=0)
		{
			SGr_tRIRE->Cells[iCol][0] =  SGr_tRIRE->Cells[iCol][0];
		}
	}
    for(iCol = 0; iCol < SGr_tSOKU->ColCount;iCol++)
    {
		if(SGr_tSOKU->Cells[iCol][0].Length() !=0)
		{
			SGr_tSOKU->Cells[iCol][0] = SGr_tSOKU->Cells[iCol][0];
		}
	}
    bBUNKATUARI = false;
}

//---------------------------------------------------------------------------
//
//  概要
//    DrawCellイベント	：測定ロットのセルを書き換えると発生します。
//
//  機能説明
//    文字色の変更（現状はclGreen or clBlack)。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int   ACol         : AnsiStingのカラム位置
//    int   ARow        :  AnsiStingのRow位置(１行なので常に0）
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tSOKUDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
    AnsiString sBuf;
    TStringGrid* strGrid = dynamic_cast<TStringGrid*>(Sender);
	RECT r=RECT(Rect);

    sBuf ="       ";
    if(bBUNKATU_SOKU[ACol] == true ) {
        SGr_tSOKU->Canvas->Font->Color = clGreen;
        DrawText(SGr_tSOKU->Canvas->Handle,sBuf.c_str(),-1,&r,DT_LEFT); //左寄せ
    }
    else
    {
        SGr_tSOKU->Canvas->Font->Color = clBlack;
    }
    sBuf = strGrid->Cells[ACol][0];
    SGr_tSOKU->Canvas->FillRect(Rect);
    InflateRect(&r,-2,-2);
    DrawText(SGr_tSOKU->Canvas->Handle,sBuf.c_str(),-1,&r,DT_LEFT); //左寄せ
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//
//  概要
//    DrawCellイベント	：履歴ロットのセルを書き換えると発生します。
//
//  機能説明
//    文字色の変更（現状はclGreen or clBlack)。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int   ACol         : AnsiStingのカラム位置
//    int   ARow        :  AnsiStingのRow位置(１行なので常に0）
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_tRIREDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
    AnsiString sBuf;
    TStringGrid* strGrid = dynamic_cast<TStringGrid*>(Sender);
	RECT r=RECT(Rect);

    sBuf ="       ";
    if(bBUNKATU_RIRE[ACol] == true ) {
        SGr_tRIRE->Canvas->Font->Color = clGreen;
        DrawText(SGr_tRIRE->Canvas->Handle,sBuf.c_str(),-1,&r,DT_LEFT); //左寄せ
    }
    else
    {
        SGr_tRIRE->Canvas->Font->Color = clBlack;
    }
    sBuf = strGrid->Cells[ACol][0];
    SGr_tRIRE->Canvas->FillRect(Rect);
    InflateRect(&r,-2,-2);
    DrawText(SGr_tRIRE->Canvas->Handle,sBuf.c_str(),-1,&r,DT_LEFT); //左寄せ

}
//---------------------------------------------------------------------------

