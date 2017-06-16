//---------------------------------------------------------------------------
//
//  Unit.cpp
//    【出荷検査システム－ロット割り当て】
//    ロット割り当てフォーム（TForm8クラス）のメンバ関数の定義
//
//  作成者
//    市川　和弘
//
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit8.h"
#include "Tkss01.h"
#include "ThreadSozaiMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm8 *Form8;

//セル情報
extern HANDLE hCELLINFO_SOKU_SYUKA;
extern HANDLE hCELLINFO_RIRE_SYUKA;
extern HANDLE hCELLINFO_SOKU_SOZAI;
extern HANDLE hCELLINFO_RIRE_SOZAI;
extern CELLINFO_DATA *pCELLINFO_SOKU_SYUKA;
extern CELLINFO_DATA *pCELLINFO_RIRE_SYUKA;
extern CELLINFO_DATA *pCELLINFO_SOKU_SOZAI;
extern CELLINFO_DATA *pCELLINFO_RIRE_SOZAI;

HANDLE hCELLINFO_RIRELOT_SYUKA;
DTKSHIN_LOT *pCELLINFO_RIRELOT_SYUKA;
HANDLE hCELLINFO_SOKULOT_SYUKA;
DTKSHIN_LOT *pCELLINFO_SOKULOT_SYUKA;

//製品規格マスター
// k.y 2003.05.17
//extern HANDLE hKSM01_DATA;

//extern KSM01_DATA *pKSM01_DATA;
extern	HANDLE 		hKSD01_DATA;
extern 	KSD01_DATA 	*pKSD01_DATA;

//ロット割り当て用（出荷検査）
extern HANDLE hSOKU_KSD01_DATA;
extern KSD01_DATA *pSOKU_KSD01_DATA;
extern HANDLE hRIRE_KSD01_DATA;
extern KSD01_DATA *pRIRE_KSD01_DATA;

extern bool bLOTCHANGE;				//スレッド処理との通信用フラグ

int iWhereGrid;
bool bCELLWRITE;
//extern bool bNowLotF7;
//---------------------------------------------------------------------------
__fastcall TForm8::TForm8(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ１２：戻る」ボタンを押した時の処理
//
//  機能説明
//    ロット割り当て画面が終了したことを示すｂNowLotF7フラグをtrueにします。(素材読み込み処理時に使用）
//  　フォームを閉じメインフォームに戻ります。
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
void __fastcall TForm8::BtnF12Click(TObject *Sender)
{
    Form1->bNowLotF7 = true;
    Close();
}

//---------------------------------------------------------------------------
//
//  概要
//    OnKeyDown イベント：　コントロールにフォーカスがある間にユーザーが任意のキーを押すと発生します。
//
//  機能説明
//    ファンクションキー押下イベントを発生させます。
//
//  パラメタ説明
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    WORD &Key         ：入力されたユニークなキーコード
//  　TShiftState Shift ：Shift，Alt，Ctrlキーがキーストロークに結び付けられているかどうかを示します。
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm8::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    switch(Key)
    {
        case VK_F1:  BtnF01Click(Sender);    break;
        //case VK_F2:  BtnF02Click(Sender);    break;
        //case VK_F3:  BtnF03Click(Sender);    break;
        case VK_F5:  BtnF05Click(Sender);    break;
        // 2003/05/19 A.Tamura
        case VK_F10: Key = 0;
					 break;
        case VK_F11: BtnF11Click(Sender);    break;
        case VK_ESCAPE:
        case VK_F12: BtnF12Click(Sender);    break;
		//case VK_RETURN :  BtnF03Click(Sender);    break;
    }
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
void __fastcall TForm8::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    if( !fFind )   return;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnCreateイベント	：Form8を作成したときに発生します。
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
void __fastcall TForm8::FormCreate(TObject *Sender)
{

	// ダミーロット番号の設定


}

//---------------------------------------------------------------------------
//
//  概要
//    OnActivate イベント：　Form8がアクティブになったときに発生します。
//
//  機能説明
//    初期画面のイニシャライズを行います。
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
void __fastcall TForm8::FormActivate(TObject *Sender)
{
	iWhereGrid = 0;			//0:履歴、1：測定
    bCELLWRITE = false;
	Set_LOT_GRID();
	GET_KSD01();

	SET_INIT_FLAG();

    SGr_vRIRE_SYUKA->RowCount = SGr_vRIRE_SYUKA->RowCount + 1;
    SGr_vRIRE_SYUKA->Row = SGr_vRIRE_SYUKA->RowCount - 1;
    SGr_vRIRE_SYUKA->Row = 1;
    SGr_vRIRE_SYUKA->RowCount = SGr_vRIRE_SYUKA->RowCount - 1;
	if( SGr_vRIRE_SYUKA->Cells[1][1] == "不要" ){
        Form1->Delete_InplaceEdit(Sender);		// 編集ウィンドウを無効にします
    	BtnF01->Enabled = false;
    }else{
    	BtnF01->Enabled = true;
    }

    SGr_vSOKU_SYUKA->RowCount = SGr_vSOKU_SYUKA->RowCount + 1;
    SGr_vSOKU_SYUKA->Row = SGr_vSOKU_SYUKA->RowCount - 1;
    SGr_vSOKU_SYUKA->Row = 1;
    SGr_vSOKU_SYUKA->RowCount = SGr_vSOKU_SYUKA->RowCount - 1;
	if( SGr_vSOKU_SYUKA->Cells[0][1] == "不要" ){
        Form1->Delete_InplaceEdit(Sender);		// 編集ウィンドウを無効にします
    	BtnF01->Enabled = false;
    }else{
    	BtnF01->Enabled = true;
    }


    SGr_vRIRE_HINBAN->RowCount = SGr_vRIRE_HINBAN->RowCount + 1;
    SGr_vRIRE_HINBAN->Row = SGr_vRIRE_HINBAN->RowCount - 1;
    SGr_vRIRE_HINBAN->Row = 1;
    SGr_vRIRE_HINBAN->RowCount = SGr_vRIRE_HINBAN->RowCount - 1;

    SGr_vSOKU_HINBAN->RowCount = SGr_vSOKU_HINBAN->RowCount + 1;
    SGr_vSOKU_HINBAN->Row = SGr_vSOKU_HINBAN->RowCount - 1;
    SGr_vSOKU_HINBAN->Row = 1;
    SGr_vSOKU_HINBAN->RowCount = SGr_vSOKU_HINBAN->RowCount - 1;

    SGr_vSOKU_SYUKA->SetFocus();
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数：　StringGridの書式の初期化を行います。
//
//  機能説明
//    StringGridのイニシャライズを行います。
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
void __fastcall TForm8::Set_LOT_GRID(void)
{
	int iCol,iRow;

	for(iCol = 0;iCol < SGr_vRIRE_SYUKA->ColCount;iCol++ )
	{
		for(iRow = 0;iRow < SGr_vRIRE_SYUKA->RowCount;iRow++)
		{
			SGr_vRIRE_SYUKA->Cells[iCol][iRow] = "";
			SGr_vRIRE_HINBAN->Cells[iCol][iRow] = "";
		}
	}
	for(iCol = 0;iCol < SGr_vSOKU_SYUKA->ColCount;iCol++ )
	{
		for(iRow = 0;iRow < SGr_vSOKU_SYUKA->RowCount;iRow++)
		{
			SGr_vSOKU_SYUKA->Cells[iCol][iRow] = "";
			SGr_vSOKU_HINBAN->Cells[iCol][iRow] = "";
		}
	}

	SGr_vRIRE_SYUKA->RowCount = 2;
	SGr_vSOKU_SYUKA->RowCount = 2;
	SGr_vRIRE_SYUKA->ColCount = Form1->SGr_vRIRE_SYUKA->ColCount+1;
	SGr_vSOKU_SYUKA->ColCount = Form1->SGr_vSOKU_SYUKA->ColCount;

	SGr_vRIRE_HINBAN->RowCount = 2;
	SGr_vSOKU_HINBAN->RowCount = 2;
	SGr_vRIRE_HINBAN->ColCount = Form1->SGr_vRIRE_SYUKA->ColCount+1;
	SGr_vSOKU_HINBAN->ColCount = Form1->SGr_vSOKU_SYUKA->ColCount;

	//出荷検査時ロットNO表示
    SGr_vRIRE_SYUKA->ColWidths[0] = 170;
	SGr_vRIRE_SYUKA->Cells[0][0] = "出荷検査時品番";
    //ロットの表示
	for(iCol = 1;iCol < SGr_vRIRE_SYUKA->ColCount+1;iCol++)           //onishi
    {
		SGr_vRIRE_SYUKA->Cells[iCol][0] = Form1->SGr_tRIRE->Cells[iCol-1][0];
		SGr_vRIRE_SYUKA->Cells[iCol][1] = Form1->SGr_tRIRE->Cells[iCol-1][1];

		SGr_vRIRE_HINBAN->Cells[iCol][0] = Form1->SGr_tRIRE->Cells[iCol-1][0];
	}
	for(iCol = 0;iCol < SGr_vSOKU_SYUKA->ColCount;iCol++)
    {
		SGr_vSOKU_SYUKA->Cells[iCol][0] = Form1->SGr_tSOKU->Cells[iCol][0];
		SGr_vSOKU_SYUKA->Cells[iCol][1] = Form1->SGr_tSOKU->Cells[iCol][1];

		SGr_vSOKU_HINBAN->Cells[iCol][0] = Form1->SGr_tSOKU->Cells[iCol][0];
    }

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数：　登録済みのロットをグリッド上に表示します。
//
//  機能説明
//    登録済みのロットをグリッド上に表示します。
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
void __fastcall TForm8::GET_KSD01(void)
{
	int iCol,iRow,iRow2;
	int i1;
    //int i2,i3;
    int iColCount;
    AnsiString sLot,sBuf,sHin;

    bCELLWRITE = true;
//デフォルト素材用得意先品番の表示
/* 2003/11/18 A.Tamura 必ずマスターの素材用品番を表示？　→ではないです。
                       このコメントの下のコードに変更します。

	for(i1 = 0;i1 < 6;i1++)
    {
		switch( i1 )
		{
		case 0:
//			sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN1_SZ;	//品番
			sBuf = pKSM01_DATA.DTKSHIN1_SZ;
			break;
		case 1:
			sBuf = pKSM01_DATA.DTKSHIN2_SZ;
			break;
		case 2:
			sBuf = pKSM01_DATA.DTKSHIN3_SZ;
			break;
		case 3:
			sBuf = pKSM01_DATA.DTKSHIN4_SZ;
			break;
		case 4:
			sBuf = pKSM01_DATA.DTKSHIN5_SZ;
			break;
		case 5:
			sBuf = pKSM01_DATA.DTKSHIN6_SZ;
			break;
        }
		if(sBuf.Trim().Length() == 0) break;
		for( iRow = 1; iRow < SGr_vRIRE_SYUKA->RowCount ; iRow++)
		{
        	if( SGr_vRIRE_SYUKA->Cells[0][iRow].Trim()  == sBuf ) break;
        	if( SGr_vRIRE_SYUKA->Cells[0][iRow].Trim().Length() == 0 )
			{
            	SGr_vRIRE_SYUKA->Cells[0][iRow] = sBuf;
                break;
        	}
		}
        if(iRow == SGr_vRIRE_SYUKA->RowCount)
		{
			SGr_vRIRE_SYUKA->RowCount ++;
			SGr_vSOKU_SYUKA->RowCount ++;
			SGr_vRIRE_SYUKA->Cells[0][iRow] = sBuf;
		}
    }
*/
    //履歴ロット用ロットNOの表示
	if(hSOKU_KSD01_DATA )
    {
	   	iColCount = SGr_vSOKU_SYUKA->ColCount;
		for(iCol = 1;iCol < iColCount;iCol++)
		{
			//デフォルトのKSM01の素材用品番の表示
			for(iRow = 0;iRow < 6;iRow++)
			{
				switch( iRow )
				{
				case 0:
					sBuf = pSOKU_KSD01_DATA[iCol-1].DTKSHIN1_SZ;
					sLot = pSOKU_KSD01_DATA[iCol-1].LOTNO1_SZ;
					sHin = pSOKU_KSD01_DATA[iCol-1].HINBAN1_SZ;
					break;
				case 1:
					sBuf = pSOKU_KSD01_DATA[iCol-1].DTKSHIN2_SZ;
					sLot = pSOKU_KSD01_DATA[iCol-1].LOTNO2_SZ;
					sHin = pSOKU_KSD01_DATA[iCol-1].HINBAN2_SZ;
					break;
				case 2:
					sBuf = pSOKU_KSD01_DATA[iCol-1].DTKSHIN3_SZ;
					sLot = pSOKU_KSD01_DATA[iCol-1].LOTNO3_SZ;
					sHin = pSOKU_KSD01_DATA[iCol-1].HINBAN3_SZ;
					break;
				case 3:
					sBuf = pSOKU_KSD01_DATA[iCol-1].DTKSHIN4_SZ;
					sLot = pSOKU_KSD01_DATA[iCol-1].LOTNO4_SZ;
					sHin = pSOKU_KSD01_DATA[iCol-1].HINBAN4_SZ;
					break;
				case 4:
					sBuf = pSOKU_KSD01_DATA[iCol-1].DTKSHIN5_SZ;
					sLot = pSOKU_KSD01_DATA[iCol-1].LOTNO5_SZ;
					sHin = pSOKU_KSD01_DATA[iCol-1].HINBAN5_SZ;
					break;
				case 5:
					sBuf = pSOKU_KSD01_DATA[iCol-1].DTKSHIN6_SZ;
					sLot = pSOKU_KSD01_DATA[iCol-1].LOTNO6_SZ;
					sHin = pSOKU_KSD01_DATA[iCol-1].HINBAN6_SZ;
					break;
				}
    	        //if( sBuf.Trim().Length() == 0 || sLot.Trim().Length()==0 )
    	        if( sBuf.Trim().Length() == 0 )
				{
					iRow = 10;
        	    	break;
				}
	            for(iRow2 = 1;iRow2 < SGr_vRIRE_SYUKA->RowCount; iRow2++)
    	        {
            	    if(SGr_vRIRE_SYUKA->Cells[0][iRow2].Trim() == sBuf.Trim())	//同じ品番が見つかった
               		{
				  		if(AnsiString(pSOKU_KSD01_DATA[iCol-1].LOT_LINK_SZ).ToIntDef(0) == 1) 	//ロットリンクしない場合は
				 		{
        	       			SGr_vRIRE_SYUKA->Cells[iCol][iRow2] = "不要";
            	       		break;
		   				}
		  				else
			 			{
    	           			SGr_vRIRE_SYUKA->Cells[iCol][iRow2] = sLot;
    	           			SGr_vRIRE_HINBAN->Cells[iCol][iRow2] = sHin;
							break;
	   					}
					}
                    else if(SGr_vRIRE_SYUKA->Cells[0][iRow2].Trim().Length() == 0)	//空品番
               		{
				  		if(AnsiString(pSOKU_KSD01_DATA[iCol-1].LOT_LINK_SZ).ToIntDef(0) == 1) 	//ロットリンクしない場合は
				 		{
   	                        SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
        	       			SGr_vRIRE_SYUKA->Cells[iCol][iRow2] = "不要";
            	       		break;
		   				}
		  				else
			 			{
   	                        SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
    	           			SGr_vRIRE_SYUKA->Cells[iCol][iRow2] = sLot;
    	           			SGr_vRIRE_HINBAN->Cells[iCol][iRow2] = sHin;
							break;
	   					}
					}

	           }
    	       if( iRow2 == SGr_vRIRE_SYUKA->RowCount)
        	   {
            		SGr_vRIRE_SYUKA->RowCount ++;
                	SGr_vSOKU_SYUKA->RowCount ++;
	                SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
    	            SGr_vSOKU_SYUKA->Cells[iCol][iRow2] = sLot;

            		SGr_vRIRE_HINBAN->RowCount ++;
                	SGr_vSOKU_HINBAN->RowCount ++;
    	            SGr_vSOKU_HINBAN->Cells[iCol][iRow2] = sHin;
               }
           }
    	}
	}


    //履歴ロット用ロットNOの表示
	if(hRIRE_KSD01_DATA && Form1->iRIRE_CNT != 0)				//履歴があれば
	{
	   	iColCount = SGr_vRIRE_SYUKA->ColCount;
		for(iCol = 1;iCol < iColCount;iCol++)
		{
			//デフォルトのKSM01の素材用品番の表示
			for(iRow = 0;iRow < 6;iRow++)
			{
				switch( iRow )
				{
				case 0:
					sBuf = pRIRE_KSD01_DATA[iCol-1].DTKSHIN1_SZ;
					sLot = pRIRE_KSD01_DATA[iCol-1].LOTNO1_SZ;
					sHin = pRIRE_KSD01_DATA[iCol-1].HINBAN1_SZ;
					break;
				case 1:
					sBuf = pRIRE_KSD01_DATA[iCol-1].DTKSHIN2_SZ;
					sLot = pRIRE_KSD01_DATA[iCol-1].LOTNO2_SZ;
					sHin = pRIRE_KSD01_DATA[iCol-1].HINBAN2_SZ;
					break;
				case 2:
					sBuf = pRIRE_KSD01_DATA[iCol-1].DTKSHIN3_SZ;
					sLot = pRIRE_KSD01_DATA[iCol-1].LOTNO3_SZ;
					sHin = pRIRE_KSD01_DATA[iCol-1].HINBAN3_SZ;
					break;
				case 3:
					sBuf = pRIRE_KSD01_DATA[iCol-1].DTKSHIN4_SZ;
					sLot = pRIRE_KSD01_DATA[iCol-1].LOTNO4_SZ;
					sHin = pRIRE_KSD01_DATA[iCol-1].HINBAN4_SZ;
					break;
				case 4:
					sBuf = pRIRE_KSD01_DATA[iCol-1].DTKSHIN5_SZ;
					sLot = pRIRE_KSD01_DATA[iCol-1].LOTNO5_SZ;
					sHin = pRIRE_KSD01_DATA[iCol-1].HINBAN5_SZ;
					break;
				case 5:
					sBuf = pRIRE_KSD01_DATA[iCol-1].DTKSHIN6_SZ;
					sLot = pRIRE_KSD01_DATA[iCol-1].LOTNO6_SZ;
					sHin = pRIRE_KSD01_DATA[iCol-1].HINBAN6_SZ;
					break;
				}
    	        //if( sBuf.Trim().Length() == 0 || sLot.Trim().Length()==0 )
    	        if( sBuf.Trim().Length() == 0 )
				{
					iRow = 10;
        	    	break;
				}
	            for(iRow2 = 1;iRow2 < SGr_vRIRE_SYUKA->RowCount; iRow2++)
    	        {
            	    if(SGr_vRIRE_SYUKA->Cells[0][iRow2].Trim() == sBuf.Trim())	//同じ品番が見つかった
               		{
				  		if(AnsiString(pRIRE_KSD01_DATA[iCol-1].LOT_LINK_SZ).ToIntDef(0) == 1) 	//ロットリンクしない場合は
				 		{
        	       			SGr_vRIRE_SYUKA->Cells[iCol][iRow2] = "不要";
            	       		break;
		   				}
		  				else
			 			{
    	           			SGr_vRIRE_SYUKA->Cells[iCol][iRow2] = sLot;
    	           			SGr_vRIRE_HINBAN->Cells[iCol][iRow2] = sHin;
							break;
	   					}
					}
                    else if(SGr_vRIRE_SYUKA->Cells[0][iRow2].Trim().Length() == 0)	//空品番
               		{
				  		if(AnsiString(pRIRE_KSD01_DATA[iCol-1].LOT_LINK_SZ).ToIntDef(0) == 1) 	//ロットリンクしない場合は
				 		{
   	                        SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
        	       			SGr_vRIRE_SYUKA->Cells[iCol][iRow2] = "不要";
            	       		break;
		   				}
		  				else
			 			{
   	                        SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
    	           			SGr_vRIRE_SYUKA->Cells[iCol][iRow2] = sLot;
    	           			SGr_vRIRE_HINBAN->Cells[iCol][iRow2] = sHin;
							break;
	   					}
					}

	           }
    	       if( iRow2 == SGr_vRIRE_SYUKA->RowCount)
        	   {
            		SGr_vRIRE_SYUKA->RowCount ++;
                	SGr_vSOKU_SYUKA->RowCount ++;
	                SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
    	            SGr_vSOKU_SYUKA->Cells[iCol][iRow2] = sLot;

            		SGr_vRIRE_HINBAN->RowCount ++;
                	SGr_vSOKU_HINBAN->RowCount ++;
    	            SGr_vSOKU_HINBAN->Cells[iCol][iRow2] = sHin;
               }
           }
    	}
	}

    //測定ロット用ロットNOの表示
   	iColCount = SGr_vSOKU_SYUKA->ColCount;
	for(iCol = 0;iCol < iColCount;iCol++)
	{
		//デフォルトのKSM01の素材用品番の表示
		for(iRow = 0;iRow < 6;iRow++)
		{
			switch( iRow )
			{
			case 0:
				sBuf = pSOKU_KSD01_DATA[iCol].DTKSHIN1_SZ;
				sLot = pSOKU_KSD01_DATA[iCol].LOTNO1_SZ;
				sHin = pSOKU_KSD01_DATA[iCol].HINBAN1_SZ;
				break;
			case 1:
				sBuf = pSOKU_KSD01_DATA[iCol].DTKSHIN2_SZ;
				sLot = pSOKU_KSD01_DATA[iCol].LOTNO2_SZ;
				sHin = pSOKU_KSD01_DATA[iCol].HINBAN2_SZ;
				break;
			case 2:
				sBuf = pSOKU_KSD01_DATA[iCol].DTKSHIN3_SZ;
				sLot = pSOKU_KSD01_DATA[iCol].LOTNO3_SZ;
				sHin = pSOKU_KSD01_DATA[iCol].HINBAN3_SZ;
				break;
			case 3:
				sBuf = pSOKU_KSD01_DATA[iCol].DTKSHIN4_SZ;
				sLot = pSOKU_KSD01_DATA[iCol].LOTNO4_SZ;
				sHin = pSOKU_KSD01_DATA[iCol].HINBAN4_SZ;
				break;
			case 4:
				sBuf = pSOKU_KSD01_DATA[iCol].DTKSHIN5_SZ;
				sLot = pSOKU_KSD01_DATA[iCol].LOTNO5_SZ;
				sHin = pSOKU_KSD01_DATA[iCol].HINBAN5_SZ;
				break;
			case 5:
				sBuf = pSOKU_KSD01_DATA[iCol].DTKSHIN6_SZ;
				sLot = pSOKU_KSD01_DATA[iCol].LOTNO6_SZ;
				sHin = pSOKU_KSD01_DATA[iCol].HINBAN6_SZ;
				break;
			}
            //if( sBuf.Trim().Length() == 0 || sLot.Trim().Length()==0 )
            if( sBuf.Trim().Length() == 0 )
			{
			}
			else
			{
	            for(iRow2 = 1;iRow2 < SGr_vSOKU_SYUKA->RowCount; iRow2++)
    	        {
        	        if(SGr_vRIRE_SYUKA->Cells[0][iRow2].Trim() == sBuf.Trim())	//同じ品番が見つかった
            	   	{
			  			if(AnsiString(pSOKU_KSD01_DATA[iCol].LOT_LINK_SZ).ToIntDef(0) == 1)
			 			{
	               			SGr_vSOKU_SYUKA->Cells[iCol][iRow2] = "不要";
    	               		break;
			   			}
		  				else
		 				{
               				SGr_vSOKU_SYUKA->Cells[iCol][iRow2] = sLot;
               				SGr_vSOKU_HINBAN->Cells[iCol][iRow2] = sHin;
							break;
		   				}
					}
        	        else if(SGr_vRIRE_SYUKA->Cells[0][iRow2].Trim().Length() == 0)	//同じ品番が見つかった
            	   	{
			  			if(AnsiString(pSOKU_KSD01_DATA[iCol].LOT_LINK_SZ).ToIntDef(0) == 1)
			 			{
                	        SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
	               			SGr_vSOKU_SYUKA->Cells[iCol][iRow2] = "不要";
    	               		break;
			   			}
		  				else
		 				{
                	        SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
               				SGr_vSOKU_SYUKA->Cells[iCol][iRow2] = sLot;
               				SGr_vSOKU_HINBAN->Cells[iCol][iRow2] = sHin;
							break;
		   				}
					}
        	   	}
	           	if( iRow2 == SGr_vRIRE_SYUKA->RowCount)
    	       	{
        	    	SGr_vRIRE_SYUKA->RowCount ++;
            	    SGr_vSOKU_SYUKA->RowCount ++;
                	SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
	                SGr_vSOKU_SYUKA->Cells[iCol][iRow2] = sLot;

        	    	SGr_vRIRE_HINBAN->RowCount ++;
            	    SGr_vSOKU_HINBAN->RowCount ++;
	                SGr_vSOKU_HINBAN->Cells[iCol][iRow2] = sHin;
    	       	}
			}
    	}
	}

    //全ての表示をグレーにする
    for(iCol = 1;iCol < SGr_vRIRE_SYUKA->ColCount ;iCol++)
    {
        for(iRow = 1;iRow < SGr_vRIRE_SYUKA->RowCount ;iRow++)
        {
            SGr_vRIRE_SYUKA->Cells[iCol][iRow] = "不要";
        }
    }
    for(iCol = 0;iCol < SGr_vSOKU_SYUKA->ColCount ;iCol++)
    {
        for(iRow = 1;iRow < SGr_vSOKU_SYUKA->RowCount ;iRow++)
        {
            SGr_vSOKU_SYUKA->Cells[iCol][iRow] = "不要";
        }
    }

	// メモリの開放
	if( hCELLINFO_RIRELOT_SYUKA ){
        GlobalUnlock( hCELLINFO_RIRELOT_SYUKA );
        GlobalFree( hCELLINFO_RIRELOT_SYUKA );
    }
    hCELLINFO_RIRELOT_SYUKA = NULL;
    // メモリの確保
    hCELLINFO_RIRELOT_SYUKA = GlobalAlloc( GHND, sizeof(struct DTKSHIN_LOT) * ((SGr_vRIRE_SYUKA->ColCount+1) * SGr_vRIRE_SYUKA->RowCount));
    if( hCELLINFO_RIRELOT_SYUKA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
    pCELLINFO_RIRELOT_SYUKA = (struct DTKSHIN_LOT *)GlobalLock(hCELLINFO_RIRELOT_SYUKA);
    if( hCELLINFO_RIRELOT_SYUKA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        Form1->SBr1->Update();
        Beep();
        return;
    }

	// メモリの開放
	if( hCELLINFO_SOKULOT_SYUKA ){
        GlobalUnlock( hCELLINFO_SOKULOT_SYUKA );
        GlobalFree( hCELLINFO_SOKULOT_SYUKA );
    }
    hCELLINFO_SOKULOT_SYUKA = NULL;
    // メモリの確保
    hCELLINFO_SOKULOT_SYUKA = GlobalAlloc( GHND, sizeof(struct DTKSHIN_LOT) * ((SGr_vSOKU_SYUKA->ColCount+1) * SGr_vSOKU_SYUKA->RowCount));
    if( hCELLINFO_SOKULOT_SYUKA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
    pCELLINFO_SOKULOT_SYUKA = (struct DTKSHIN_LOT *)GlobalLock(hCELLINFO_SOKULOT_SYUKA);
    if( hCELLINFO_SOKULOT_SYUKA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        Form1->SBr1->Update();
        Beep();
        return;
    }

//全ての表示をグレーにする
    for(iCol = 1;iCol < SGr_vRIRE_SYUKA->ColCount ;iCol++)
    {
        for(iRow = 1;iRow < SGr_vRIRE_SYUKA->RowCount ;iRow++)
        {
            strcpy(pCELLINFO_RIRELOT_SYUKA[iCol*SGr_vRIRE_SYUKA->RowCount+iRow].DTKSIN_SZ,AnsiString("不要").c_str());
        }
    }
    for(iCol = 0;iCol < SGr_vSOKU_SYUKA->ColCount ;iCol++)
    {
        for(iRow = 1;iRow < SGr_vSOKU_SYUKA->RowCount ;iRow++)
        {
            strcpy(pCELLINFO_SOKULOT_SYUKA[iCol*SGr_vSOKU_SYUKA->RowCount+iRow].DTKSIN_SZ,AnsiString("不要").c_str());
        }
    }



    //履歴ロット用ロットNOの表示
	if(hRIRE_KSD01_DATA && Form1->iRIRE_CNT != 0)				//履歴があれば
	{
	   	iColCount = SGr_vRIRE_SYUKA->ColCount;
		for(iCol = 1;iCol < iColCount;iCol++)
		{
            if(AnsiString(pRIRE_KSD01_DATA[iCol-1].LOT_LINK_SZ).ToIntDef(0) == 1) 	//ロットリンクする場合
            {
            }
            else
            {
    			//デフォルトのKSM01の素材用品番の表示
	    		for(iRow = 0;iRow < 6;iRow++)
		    	{
			    	switch( iRow )
				    {
    				case 0:
	    				sBuf = pRIRE_KSD01_DATA[iCol-1].DTKSHIN1_SZ;
		    			sLot = pRIRE_KSD01_DATA[iCol-1].LOTNO1_SZ;
		    			sHin = pRIRE_KSD01_DATA[iCol-1].HINBAN1_SZ;
			    		break;
    				case 1:
	    				sBuf = pRIRE_KSD01_DATA[iCol-1].DTKSHIN2_SZ;
		    			sLot = pRIRE_KSD01_DATA[iCol-1].LOTNO2_SZ;
		    			sHin = pRIRE_KSD01_DATA[iCol-1].HINBAN2_SZ;
			    		break;
    				case 2:
	    				sBuf = pRIRE_KSD01_DATA[iCol-1].DTKSHIN3_SZ;
		    			sLot = pRIRE_KSD01_DATA[iCol-1].LOTNO3_SZ;
		    			sHin = pRIRE_KSD01_DATA[iCol-1].HINBAN3_SZ;
			    		break;
				    case 3:
    					sBuf = pRIRE_KSD01_DATA[iCol-1].DTKSHIN4_SZ;
	    				sLot = pRIRE_KSD01_DATA[iCol-1].LOTNO4_SZ;
		    			sHin = pRIRE_KSD01_DATA[iCol-1].HINBAN4_SZ;
		    			break;
			    	case 4:
				    	sBuf = pRIRE_KSD01_DATA[iCol-1].DTKSHIN5_SZ;
					    sLot = pRIRE_KSD01_DATA[iCol-1].LOTNO5_SZ;
		    			sHin = pRIRE_KSD01_DATA[iCol-1].HINBAN5_SZ;
    					break;
	    			case 5:
		    			sBuf = pRIRE_KSD01_DATA[iCol-1].DTKSHIN6_SZ;
			    		sLot = pRIRE_KSD01_DATA[iCol-1].LOTNO6_SZ;
		    			sHin = pRIRE_KSD01_DATA[iCol-1].HINBAN6_SZ;
				    	break;
    				}
        	        if( sBuf.Trim().Length() == 0 )
	    			{
		    			iRow = 10;
        	        	break;
				    }
    	            for(iRow2 = 1;iRow2 < SGr_vRIRE_SYUKA->RowCount; iRow2++)
        	        {
                	    if(SGr_vRIRE_SYUKA->Cells[0][iRow2].Trim() == sBuf.Trim())	//同じ品番が見つかった
                   		{
                            SGr_vRIRE_SYUKA->Cells[iCol][iRow2] = sLot;
                            SGr_vRIRE_HINBAN->Cells[iCol][iRow2] = sHin;
                            strcpy(pCELLINFO_RIRELOT_SYUKA[iCol*SGr_vRIRE_SYUKA->RowCount+iRow2].DTKSIN_SZ,sLot.c_str());
                            break;
    					}
                        else if(SGr_vRIRE_SYUKA->Cells[0][iRow2].Trim().Length() == 0)	//空のセルが見つかった
            	   	    {
                	        SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
               				SGr_vRIRE_SYUKA->Cells[iCol][iRow2] = sLot;
               				SGr_vRIRE_HINBAN->Cells[iCol][iRow2] = sHin;
                            strcpy(pCELLINFO_RIRELOT_SYUKA[iCol*SGr_vRIRE_SYUKA->RowCount+iRow2].DTKSIN_SZ,sLot.c_str());
 							break;
		   				}
					}
   	                if( iRow2 == SGr_vRIRE_SYUKA->RowCount)
        	        {
            		    SGr_vRIRE_SYUKA->RowCount ++;
                	    SGr_vSOKU_SYUKA->RowCount ++;
	                    SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
    	                SGr_vSOKU_SYUKA->Cells[iCol][iRow2] = sLot;

            		    SGr_vRIRE_HINBAN->RowCount ++;
                	    SGr_vSOKU_HINBAN->RowCount ++;
    	                SGr_vSOKU_HINBAN->Cells[iCol][iRow2] = sHin;
                    }
                }
    	    }
	    }
    }

    //測定ロット用ロットNOの表示
   	iColCount = SGr_vSOKU_SYUKA->ColCount;
	for(iCol = 0;iCol < iColCount;iCol++)
	{
        if(AnsiString(pSOKU_KSD01_DATA[iCol].LOT_LINK_SZ).ToIntDef(0) == 1)
        {
        }
        else
        {
    		//デフォルトのKSM01の素材用品番の表示
	    	for(iRow = 0;iRow < 6;iRow++)
		    {
    			switch( iRow )
	    		{
		    	case 0:
			    	sBuf = pSOKU_KSD01_DATA[iCol].DTKSHIN1_SZ;
  				    sLot = pSOKU_KSD01_DATA[iCol].LOTNO1_SZ;
  				    sHin = pSOKU_KSD01_DATA[iCol].HINBAN1_SZ;
    				break;
	    		case 1:
		    		sBuf = pSOKU_KSD01_DATA[iCol].DTKSHIN2_SZ;
			    	sLot = pSOKU_KSD01_DATA[iCol].LOTNO2_SZ;
  				    sHin = pSOKU_KSD01_DATA[iCol].HINBAN2_SZ;
				    break;
    			case 2:
	    			sBuf = pSOKU_KSD01_DATA[iCol].DTKSHIN3_SZ;
		    		sLot = pSOKU_KSD01_DATA[iCol].LOTNO3_SZ;
  				    sHin = pSOKU_KSD01_DATA[iCol].HINBAN3_SZ;
			    	break;
    			case 3:
	    			sBuf = pSOKU_KSD01_DATA[iCol].DTKSHIN4_SZ;
		    		sLot = pSOKU_KSD01_DATA[iCol].LOTNO4_SZ;
  				    sHin = pSOKU_KSD01_DATA[iCol].HINBAN4_SZ;
			    	break;
    			case 4:
	    			sBuf = pSOKU_KSD01_DATA[iCol].DTKSHIN5_SZ;
		    		sLot = pSOKU_KSD01_DATA[iCol].LOTNO5_SZ;
  				    sHin = pSOKU_KSD01_DATA[iCol].HINBAN5_SZ;
			    	break;
    			case 5:
	    			sBuf = pSOKU_KSD01_DATA[iCol].DTKSHIN6_SZ;
		    		sLot = pSOKU_KSD01_DATA[iCol].LOTNO6_SZ;
  				    sHin = pSOKU_KSD01_DATA[iCol].HINBAN6_SZ;
			    	break;
    			}
                if( sBuf.Trim().Length() == 0 )
	    		{
		    	}
			    else
    			{
	                for(iRow2 = 1;iRow2 < SGr_vSOKU_SYUKA->RowCount; iRow2++)
    	            {
        	            if(SGr_vRIRE_SYUKA->Cells[0][iRow2].Trim() == sBuf.Trim())	//同じ品番が見つかった
            	       	{
               				SGr_vSOKU_SYUKA->Cells[iCol][iRow2] = sLot;
               				SGr_vSOKU_HINBAN->Cells[iCol][iRow2] = sHin;
                            strcpy(pCELLINFO_SOKULOT_SYUKA[iCol*SGr_vSOKU_SYUKA->RowCount+iRow2].DTKSIN_SZ,sLot.c_str());
 							break;
		   				}
            	        else if(SGr_vRIRE_SYUKA->Cells[0][iRow2].Trim().Length() == 0)	//同じ品番が見つかった
		 				{
                	        SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
               				SGr_vSOKU_SYUKA->Cells[iCol][iRow2] = sLot;
               				SGr_vSOKU_HINBAN->Cells[iCol][iRow2] = sHin;
                            strcpy(pCELLINFO_SOKULOT_SYUKA[iCol*SGr_vSOKU_SYUKA->RowCount+iRow2].DTKSIN_SZ,sLot.c_str());
 							break;
		   				}
					}
    	           	if( iRow2 == SGr_vRIRE_SYUKA->RowCount)
        	       	{
            	    	SGr_vRIRE_SYUKA->RowCount ++;
                	    SGr_vSOKU_SYUKA->RowCount ++;
                    	SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
	                    SGr_vSOKU_SYUKA->Cells[iCol][iRow2] = sLot;

            	    	SGr_vRIRE_HINBAN->RowCount ++;
                	    SGr_vSOKU_HINBAN->RowCount ++;
	                    SGr_vSOKU_HINBAN->Cells[iCol][iRow2] = sHin;
        	       	}
	    		}
    	    }
	    }
    }
    bCELLWRITE = false;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ１１：決定」ボタンを押した時の処理
//
//  機能説明
//    登録されているロットと入力されたロットを比較して、違っているときは変更フラグをtrueにします。
//    その後で、入力ロットを読み込みます。
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
void __fastcall TForm8::BtnF11Click(TObject *Sender)
{
	int iCol,iRow,i1;
 	AnsiString sLot,sHin,sDTKSHIN,sDTKSHIN_SZ,sBuf,sMsg;
  	TMsgDlgButtons MsgButton;

    //ロット割り当てメモリへ保存
    //履歴
	if( hRIRE_KSD01_DATA )
	{
		for(iCol=1;iCol<SGr_vRIRE_SYUKA->ColCount;iCol++)
    	{
			for(iRow=0;iRow<SGr_vRIRE_SYUKA->RowCount;iRow++)
			{
				sDTKSHIN = SGr_vRIRE_SYUKA->Cells[0][iRow+1];

				//if( SGr_vRIRE_SYUKA->Cells[iCol][iRow] != "不要" )
                sBuf = pCELLINFO_RIRELOT_SYUKA[(iCol)*SGr_vRIRE_SYUKA->RowCount+(iRow+1)].DTKSIN_SZ;
                if( sBuf.Trim() != "不要")
 				{
					for(i1 = 0;i1 < 6;i1++)
					{
	                	switch(i1)
						{
						    case 0:
							sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol-1].DTKSHIN1_SZ;
							break;
						    case 1:
							sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol-1].DTKSHIN2_SZ;
							break;
						    case 2:
							sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol-1].DTKSHIN3_SZ;
							break;
					        case 3:
							sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol-1].DTKSHIN4_SZ;
							break;
						    case 4:
							sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol-1].DTKSHIN5_SZ;
							break;
						    case 5:
							sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol-1].DTKSHIN6_SZ;
							break;
						}
						if(sDTKSHIN_SZ.Trim() == sDTKSHIN.Trim())
						{
							sLot = SGr_vRIRE_SYUKA->Cells[iCol][iRow+1];
							sHin = SGr_vRIRE_HINBAN->Cells[iCol][iRow+1];

                            //ロット入力判定
                            if( sLot != ""  &&  sHin == "" )
	                        {
       	                        sMsg  = "有効な自社品番が選択されていません１";
		                        MsgButton << mbOK;
                                MessageDlg( sMsg, mtWarning	, MsgButton, 0);
                                return;
                            }

							switch( i1 )
							{
							case 0:
								if(AnsiString(pRIRE_KSD01_DATA[iCol-1].LOTNO1_SZ) != sLot)
								{
									strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE1_SZ,"1");
				                    pRIRE_KSD01_DATA[iCol-1].UPD_FLG = true;
                                    bLOTCHANGE = true;
								}
                                else
								{
									strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE1_SZ,"0");
								}
								strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNO1_SZ,sLot.c_str());
								strcpy(pRIRE_KSD01_DATA[iCol-1].HINBAN1_SZ,sHin.c_str());
								break;
							case 1:
								if(AnsiString(pRIRE_KSD01_DATA[iCol-1].LOTNO2_SZ) != sLot)
								{
									strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE2_SZ,"1");
				                    pRIRE_KSD01_DATA[iCol-1].UPD_FLG = true;
                                    bLOTCHANGE = true;
								}
                                else
								{
									strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE2_SZ,"0");
								}
								strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNO2_SZ,sLot.c_str());
								strcpy(pRIRE_KSD01_DATA[iCol-1].HINBAN2_SZ,sHin.c_str());
								break;
							case 2:
								if(AnsiString(pRIRE_KSD01_DATA[iCol-1].LOTNO3_SZ) != sLot)
								{
									strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE3_SZ,"1");
				                    pRIRE_KSD01_DATA[iCol-1].UPD_FLG = true;
                                    bLOTCHANGE = true;
								}
                                else
								{
									strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE3_SZ,"0");
								}
								strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNO3_SZ,sLot.c_str());
								strcpy(pRIRE_KSD01_DATA[iCol-1].HINBAN3_SZ,sHin.c_str());
								break;
							case 3:
								if(AnsiString(pRIRE_KSD01_DATA[iCol-1].LOTNO4_SZ) != sLot)
								{
									strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE4_SZ,"1");
				                    pRIRE_KSD01_DATA[iCol-1].UPD_FLG = true;
                                    bLOTCHANGE = true;
								}
                                else
								{
									strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE4_SZ,"0");
								}
								strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNO4_SZ,sLot.c_str());
								strcpy(pRIRE_KSD01_DATA[iCol-1].HINBAN4_SZ,sHin.c_str());
								break;
							case 4:
								if(AnsiString(pRIRE_KSD01_DATA[iCol-1].LOTNO5_SZ) != sLot)
								{
									strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE5_SZ,"1");
				                    pRIRE_KSD01_DATA[iCol-1].UPD_FLG = true;
                                    bLOTCHANGE = true;
								}
                                else
								{
									strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE5_SZ,"0");
								}
								strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNO5_SZ,sLot.c_str());
								strcpy(pRIRE_KSD01_DATA[iCol-1].HINBAN5_SZ,sHin.c_str());
								break;
							case 5:
								if(AnsiString(pRIRE_KSD01_DATA[iCol-1].LOTNO6_SZ) != sLot)
								{
									strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE6_SZ,"1");
				                    pRIRE_KSD01_DATA[iCol-1].UPD_FLG = true;
                                    bLOTCHANGE = true;
								}
                                else
								{
									strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE6_SZ,"0");
								}
								strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNO6_SZ,sLot.c_str());
								strcpy(pRIRE_KSD01_DATA[iCol-1].HINBAN6_SZ,sHin.c_str());
								break;
							}
	                        break;
    	            	}
        	        }
				}
			}
		}
	}

    //測定
	for(iCol=0;iCol<SGr_vSOKU_SYUKA->ColCount;iCol++)
    {
		for(iRow=1;iRow<SGr_vSOKU_SYUKA->RowCount;iRow++)
		{
			sDTKSHIN = SGr_vRIRE_SYUKA->Cells[0][iRow];			//ＫＳＭ01に登録されている素材用得意先品番

			//if( SGr_vSOKU_SYUKA->Cells[iCol][iRow] != "不要" )
            sBuf = pCELLINFO_SOKULOT_SYUKA[iCol*SGr_vSOKU_SYUKA->RowCount+iRow].DTKSIN_SZ;
            if( sBuf.Trim() != "不要")
			{
				for(i1 = 0;i1 < 6;i1++)
				{
                	switch(i1)
					{
					case 0:
						sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN1_SZ;	//品番
						break;
					case 1:
						sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN2_SZ;
						break;
					case 2:
						sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN3_SZ;
						break;
					case 3:
						sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN4_SZ;
						break;
					case 4:
						sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN5_SZ;
						break;
					case 5:
						sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN6_SZ;
						break;
					}
					if(sDTKSHIN_SZ.Trim() == sDTKSHIN.Trim())
					{
						sLot = SGr_vSOKU_SYUKA->Cells[iCol][iRow];
						sHin = SGr_vSOKU_HINBAN->Cells[iCol][iRow];

                        //ロット入力判定
                        if( sLot != ""  &&  sHin == "" )
	                    {
       	                    sMsg  = "有効な自社品番が選択されていません２";
		                    MsgButton << mbOK;
                            MessageDlg( sMsg, mtWarning	, MsgButton, 0);
                            return;
                        }

						switch( i1 )
						{
						case 0:
                        	if(AnsiString(pSOKU_KSD01_DATA[iCol].LOTNO1_SZ) != sLot)
					   		{
                            	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE1_SZ,"1");
                                pSOKU_KSD01_DATA[iCol].UPD_FLG = true;
                                bLOTCHANGE = true;
                            }
                            else
                            {
                            	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE1_SZ,"0");
                            }
							strcpy(pSOKU_KSD01_DATA[iCol].LOTNO1_SZ,sLot.c_str());
							strcpy(pSOKU_KSD01_DATA[iCol].HINBAN1_SZ,sHin.c_str());
							break;
						case 1:
                        	if(AnsiString(pSOKU_KSD01_DATA[iCol].LOTNO2_SZ) != sLot)
					   		{
                            	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE2_SZ,"1");
                                pSOKU_KSD01_DATA[iCol].UPD_FLG = true;
                                bLOTCHANGE = true;
                            }
                            else
                            {
                            	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE2_SZ,"0");
                            }
							strcpy(pSOKU_KSD01_DATA[iCol].LOTNO2_SZ,sLot.c_str());
							strcpy(pSOKU_KSD01_DATA[iCol].HINBAN2_SZ,sHin.c_str());
							break;
						case 2:
                        	if(AnsiString(pSOKU_KSD01_DATA[iCol].LOTNO3_SZ) != sLot)
					   		{
                            	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE3_SZ,"1");
                                pSOKU_KSD01_DATA[iCol].UPD_FLG = true;
                                bLOTCHANGE = true;
                            }
                            else
                            {
                            	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE3_SZ,"0");
                            }
							strcpy(pSOKU_KSD01_DATA[iCol].LOTNO3_SZ,sLot.c_str());
							strcpy(pSOKU_KSD01_DATA[iCol].HINBAN3_SZ,sHin.c_str());
							break;
						case 3:
                        	if(AnsiString(pSOKU_KSD01_DATA[iCol].LOTNO4_SZ) != sLot)
					   		{
                            	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE4_SZ,"1");
                                pSOKU_KSD01_DATA[iCol].UPD_FLG = true;
                                bLOTCHANGE = true;
                            }
                            else
                            {
                            	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE4_SZ,"0");
                            }
							strcpy(pSOKU_KSD01_DATA[iCol].LOTNO4_SZ,sLot.c_str());
							strcpy(pSOKU_KSD01_DATA[iCol].HINBAN4_SZ,sHin.c_str());
							break;
						case 4:
                        	if(AnsiString(pSOKU_KSD01_DATA[iCol].LOTNO5_SZ) != sLot)
					   		{
                            	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE5_SZ,"1");
                                pSOKU_KSD01_DATA[iCol].UPD_FLG = true;
                                bLOTCHANGE = true;
                            }
                            else
                            {
                            	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE5_SZ,"0");
                            }
							strcpy(pSOKU_KSD01_DATA[iCol].LOTNO5_SZ,sLot.c_str());
							strcpy(pSOKU_KSD01_DATA[iCol].HINBAN5_SZ,sHin.c_str());
							break;
						case 5:
                        	if(AnsiString(pSOKU_KSD01_DATA[iCol].LOTNO6_SZ) != sLot)
					   		{
                            	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE6_SZ,"1");
                                pSOKU_KSD01_DATA[iCol].UPD_FLG = true;
                                bLOTCHANGE = true;
                            }
                            else
                            {
                            	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE6_SZ,"0");
                            }
							strcpy(pSOKU_KSD01_DATA[iCol].LOTNO6_SZ,sLot.c_str());
							strcpy(pSOKU_KSD01_DATA[iCol].HINBAN6_SZ,sHin.c_str());
							break;
						}
                        break;
                	}
                }
			}
		}
	}
    Form1->bNowLotF7 = true;
	Close();
}

//---------------------------------------------------------------------------
//
//  概要
//    OnDrawCell イベント：グリッド内のセルを描画する必要があるときに発生します。
//
//  機能説明
//    グリッド内のセルを描画を行います。
//
//  パラメタ説明
//    TObject *Sender	    ：呼び出し元のVCLオブジェクト
//  　int ACol              ：対象セルのCol位置
//    int ARow              ：対象セルのRow位置
//    TRect &Rect           ：セルの位置情報
//    TGridDrawState State  ：描画セルの状態
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm8::SGr_vRIRE_SYUKADrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
	AnsiString asBuf;
	RECT r=RECT(Rect);

	asBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];		//ロットNo
    SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;		//不要なので灰色
	if(State.Contains(gdFixed))
	{
	}
	else if(asBuf == "不要")
	{
    	SGr_vRIRE_SYUKA->Canvas->Brush->Color= clGray;		//不要なので灰色
    	SGr_vRIRE_SYUKA->Canvas->Font->Color = clGray;		//不要なので灰色
    }
   	else if(State.Contains(gdFocused))
	{
    	SGr_vRIRE_SYUKA->Canvas->Brush->Color= clHighlight;	//選択中
    	SGr_vRIRE_SYUKA->Canvas->Font->Color= clHighlightText;
	}
   	else
    {
    	SGr_vRIRE_SYUKA->Canvas->Brush->Color= SGr_vRIRE_SYUKA->Color; //ノーマル色
		SGr_vRIRE_SYUKA->Canvas->Font->Color= SGr_vRIRE_SYUKA->Font->Color;
    }
/*
    //選択されているセルの文字色をセット
    if(State.Contains(gdFocused))
    {
    	SGr_vRIRE_SYUKA->Canvas->Font->Color= clHighlightText;
    }
   	else if(State.Contains(gdSelected))
   	{
   	//普通のセルの文字色をセット
   	}
   	else
   	{
		SGr_vRIRE_SYUKA->Canvas->Font->Color= SGr_vRIRE_SYUKA->Font->Color;
   	}
*/
//選択中はハイライト表示
	SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
	if(State.Contains(gdFocused))
	{
    	SGr_vRIRE_SYUKA->Canvas->Font->Color= clHighlightText;
    }
   	if(asBuf == "不要")
   	{
   		SGr_vRIRE_SYUKA->Canvas->Font->Color= clGray;
   	}
    SGr_vRIRE_SYUKA->Canvas->FillRect(Rect);
    InflateRect(&r,-2,-2);
    asBuf = asBuf.UpperCase();
   	DrawText(SGr_vRIRE_SYUKA->Canvas->Handle,asBuf.c_str(),-1,&r,DT_CENTER); //中央寄せ（水平）

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
void __fastcall TForm8::BtnF01Click(TObject *Sender)
{
	if( !BtnF01->Enabled ) return;

    ////////////////////
    // 一覧検索
    if( BtnF01->Tag == 3 ){
		if( SGr_vRIRE_SYUKA->Cells[SGr_vRIRE_SYUKA->Col][SGr_vRIRE_SYUKA->Row] == "不要" ||
        	SGr_vRIRE_SYUKA->RowCount <= SGr_vRIRE_SYUKA->Row ||
            SGr_vRIRE_SYUKA->Col == 0 || SGr_vRIRE_SYUKA->Row == 0 )
            return;
    }
    if( BtnF01->Tag == 4 ){
		if( SGr_vSOKU_SYUKA->Cells[SGr_vSOKU_SYUKA->Col][SGr_vSOKU_SYUKA->Row] == "不要" ||
        	SGr_vSOKU_SYUKA->RowCount <= SGr_vSOKU_SYUKA->Row ||
            SGr_vSOKU_SYUKA->Row == 0 )
        	return;
    }
    Form2->Tag = BtnF01->Tag;
    Form2->ShowModal();

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ５：画面印刷」ボタンを押した時の処理
//
//  機能説明
//    画面印刷を行います。
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
void __fastcall TForm8::BtnF05Click(TObject *Sender)
{
//画面印刷
	Form8->Print();
}

//---------------------------------------------------------------------------
//
//  概要
//    OnSelectCell イベント：　グリッド内のセルが選択される前に発生します。
//
//  機能説明
//    出荷（履歴）グリッド内の移動の制限を行います。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int ACol          ：対象セルのCol位置
//    int ARow          ：対象セルのRow位置
//  　bool &CanSelect   ：セルの選択、有効／無効を行います
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm8::SGr_vRIRE_SYUKASelectCell(TObject *Sender,
      int ACol, int ARow, bool &CanSelect)
{
    if(bCELLWRITE) return;
	iWhereGrid = 0;			//履歴グリッド選択中
   	SGr_vRIRE_SYUKA->Options << goEditing;
	//if( SGr_vRIRE_SYUKA->Cells[ACol][ARow] == "不要" ||
	//	SGr_vRIRE_SYUKA->RowCount <= SGr_vRIRE_SYUKA->Row ||
	//	SGr_vRIRE_SYUKA->Col == 0 || SGr_vRIRE_SYUKA->Row == 0 )
	if( SGr_vRIRE_SYUKA->Cells[ACol][ARow] == "不要" ||
		SGr_vRIRE_SYUKA->RowCount <= ARow ||
		ACol == 0 || ARow == 0 )                                
    {
    	CanSelect = false;
        Form1->Delete_InplaceEdit(Sender);		// 編集ウィンドウを無効にします
    	BtnF01->Enabled = false;
    }else{
    	BtnF01->Enabled = true;
    }
}

//---------------------------------------------------------------------------
//
//  概要
//    OnSelectCell イベント：　グリッド内のセルが選択される前に発生します。
//
//  機能説明
//    出荷（測定）グリッド内の移動の制限を行います。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int ACol          ：対象セルのCol位置
//    int ARow          ：対象セルのRow位置
//  　bool &CanSelect   ：セルの選択、有効／無効を行います
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm8::SGr_vSOKU_SYUKASelectCell(TObject *Sender,
      int ACol, int ARow, bool &CanSelect)
{
    if(bCELLWRITE) return;
	iWhereGrid = 1;		//測定グリッド選択中
   	SGr_vSOKU_SYUKA->Options << goEditing;
	//if( SGr_vSOKU_SYUKA->Cells[ACol][ARow] == "不要" ||
	//	SGr_vRIRE_SYUKA->RowCount <= SGr_vRIRE_SYUKA->Row ||
	//	SGr_vRIRE_SYUKA->Row == 0 )
	if( SGr_vSOKU_SYUKA->Cells[ACol][ARow] == "不要" ||
		SGr_vRIRE_SYUKA->RowCount <= ARow ||
		ARow == 0 )
    {
    	CanSelect = false;
        Form1->Delete_InplaceEdit(Sender);		// 編集ウィンドウを無効にします
    	BtnF01->Enabled = false;
    }else{
    	BtnF01->Enabled = true;
    }
}

//---------------------------------------------------------------------------
//
//  概要
//    OnDrawCell イベント：　グリッド内のセルを描画する必要があるときに発生します。
//
//  機能説明
//    出荷（測定）グリッド内の移動の制限を行います。
//
//  パラメタ説明
//    TObject *Sender	    ：呼び出し元のVCLオブジェクト
//    int ACol              ：対象セルのCol位置
//    int ARow              ：対象セルのRow位置
//    TRect &Rect           ：位置情報
//  　TGridDrawState State   ：描画セルの状態
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm8::SGr_vSOKU_SYUKADrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
	AnsiString asBuf;
	RECT r=RECT(Rect);

	asBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];		//ロットNo
    SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;		//不要なので灰色
	if(State.Contains(gdFixed))
	{
	}
	else if(asBuf == "不要")
	{
    	SGr_vSOKU_SYUKA->Canvas->Brush->Color= clGray;		//不要なので灰色
    	SGr_vSOKU_SYUKA->Canvas->Font->Color = clGray;		//不要なので灰色
    }
   	else if(State.Contains(gdFocused))
	{
    	SGr_vSOKU_SYUKA->Canvas->Brush->Color= clHighlight;	//選択中
	}
   	else
    {
    	SGr_vSOKU_SYUKA->Canvas->Brush->Color= SGr_vSOKU_SYUKA->Color; //ノーマル色
    }
    //選択されているセルの文字色をセット
    if(State.Contains(gdFocused))
    {
    	SGr_vSOKU_SYUKA->Canvas->Font->Color= clHighlightText;
    }
   	else if(State.Contains(gdSelected))
   	{
   	//普通のセルの文字色をセット
   	}
   	else
   	{
		SGr_vSOKU_SYUKA->Canvas->Font->Color= SGr_vSOKU_SYUKA->Font->Color;
   	}
    SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;
//選択中はハイライト表示
	if(State.Contains(gdFocused))
	{
    	SGr_vSOKU_SYUKA->Canvas->Font->Color= clHighlightText;
    }
   	if(asBuf == "不要")
   	{                                            
   		SGr_vSOKU_SYUKA->Canvas->Font->Color= clGray;
   	}

    SGr_vSOKU_SYUKA->Canvas->FillRect(Rect);
    InflateRect(&r,-2,-2);
    asBuf = asBuf.UpperCase();
   	DrawText(SGr_vSOKU_SYUKA->Canvas->Handle,asBuf.c_str(),-1,&r,DT_CENTER); //中央寄せ（水平）

}

//---------------------------------------------------------------------------
//
//  概要
//    OnExit イベント：　入力フォーカスがコントロールから別のコントロールへ移ったときに発生します。
//
//  機能説明
//   出荷（測定）グリッドからフォーカスが抜けたときに明示的にDrawCellイベントを発生します。
//
//  パラメタ説明
//    TObject *Sender	    ：呼び出し元のVCLオブジェクト
//    int ACol              ：対象セルのCol位置
//    int ARow              ：対象セルのRow位置
//    TRect &Rect           ：位置情報
//  　TGridDrawState State   ：描画セルの状態
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm8::SGr_vSOKU_SYUKAExit(TObject *Sender)
{
    TGridDrawState State;

    SGr_vSOKU_SYUKADrawCell( Sender,
                             SGr_vSOKU_SYUKA->Col,
                             SGr_vSOKU_SYUKA->Row,
                             SGr_vSOKU_SYUKA->CellRect(SGr_vSOKU_SYUKA->Col, SGr_vSOKU_SYUKA->Row),
                             State);

}

//---------------------------------------------------------------------------
//
//  概要
//    OnEnter イベント：　コントロールが入力フォーカスを受け取ったときに発生します。
//
//  機能説明
//   出荷（測定）グリッド、出荷（履歴）グリッドにフォーカスがある場合はＦ１：一覧検索ボタンを有効にする。。
//
//  パラメタ説明
//    TObject *Sender	    ：呼び出し元のVCLオブジェクト
//    int ACol              ：対象セルのCol位置
//    int ARow              ：対象セルのRow位置
//    TRect &Rect           ：位置情報
//  　TGridDrawState State   ：描画セルの状態
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm8::FormEnter(TObject *Sender)
{
    AnsiString	sBuf;
    TComponent	*cmp	= dynamic_cast<TComponent*>(Sender);

    if( BtnF01->Focused() )		return;

    sBuf = cmp->Name;

    // StringGrid部　履歴ロットにフォーカスが有る場合
    if( SGr_vRIRE_SYUKA->Focused() || sBuf == "SGr_vRIRE_SYUKA" ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 3;
        return;
    }

    // StringGrid部　測定ロットにフォーカスが有る場合
    if( SGr_vSOKU_SYUKA->Focused() || sBuf == "SGr_vSOKU_SYUKA" ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 4;
        return;
    }

    // 「F1：一覧検索」ボタンを使えないようにする
    BtnF01->Enabled = false;
    BtnF01->Tag = 0;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnExit イベント：　入力フォーカスがコントロールから別のコントロールへ移ったときに発生します。
//
//  機能説明
//   出荷（履歴）グリッドからフォーカスが抜けたときに明示的にDrawCellイベントを発生します。
//
//  パラメタ説明
//    TObject *Sender	    ：呼び出し元のVCLオブジェクト
//    int ACol              ：対象セルのCol位置
//    int ARow              ：対象セルのRow位置
//    TRect &Rect           ：位置情報
//  　TGridDrawState State   ：描画セルの状態
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm8::SGr_vRIRE_SYUKAExit(TObject *Sender)
{
    TGridDrawState State;

    SGr_vRIRE_SYUKADrawCell( Sender,
                             SGr_vRIRE_SYUKA->Col,
                             SGr_vRIRE_SYUKA->Row,
                             SGr_vRIRE_SYUKA->CellRect(SGr_vRIRE_SYUKA->Col, SGr_vRIRE_SYUKA->Row),
                             State);

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数：　ロット変更フラグを初期化します。
//
//  機能説明
//   ロット変更フラグを初期化します。
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
void __fastcall TForm8::SET_INIT_FLAG(void)
{
	int iCol,iRow,i1;
 	AnsiString sLot,sDTKSHIN,sDTKSHIN_SZ;
//ロット割り当てメモリへ保存
//履歴
	if( hRIRE_KSD01_DATA )
	{
		for(iCol=1;iCol<SGr_vRIRE_SYUKA->ColCount;iCol++)
    	{
			for(iRow=0;iRow<SGr_vRIRE_SYUKA->RowCount;iRow++)
			{
				sDTKSHIN = SGr_vRIRE_SYUKA->Cells[0][iRow+1];
				if( SGr_vSOKU_SYUKA->Cells[iCol][iRow] != "不要" )
				{
					for(i1 = 0;i1 < 6;i1++)
					{
	                	switch(i1)
						{
						case 0:
							sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol-1].DTKSHIN1_SZ;
							break;
						case 1:
							sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol-1].DTKSHIN2_SZ;
							break;
						case 2:
							sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol-1].DTKSHIN3_SZ;
							break;
						case 3:
							sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol-1].DTKSHIN4_SZ;
							break;
						case 4:
							sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol-1].DTKSHIN5_SZ;
							break;
						case 5:
							sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol-1].DTKSHIN6_SZ;
							break;
						}
						if(sDTKSHIN_SZ.Trim() == sDTKSHIN.Trim())
						{
							sLot = SGr_vRIRE_SYUKA->Cells[iCol][iRow+1];
							switch( i1 )
							{
							case 0:
                            	strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE1_SZ,"0");
								break;
							case 1:
                            	strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE2_SZ,"0");
								break;
							case 2:
                            	strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE3_SZ,"0");
								break;
							case 3:
                            	strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE4_SZ,"0");
								break;
							case 4:
                            	strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE5_SZ,"0");
								break;
							case 5:
                            	strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE6_SZ,"0");
								break;
							}
	                        break;
    	            	}
        	        }
				}
			}
		}                                             
	}
//測定
	for(iCol=0;iCol<SGr_vSOKU_SYUKA->ColCount;iCol++)
    {
		for(iRow=1;iRow<SGr_vSOKU_SYUKA->RowCount;iRow++)
		{
			sDTKSHIN = SGr_vRIRE_SYUKA->Cells[0][iRow];			//ＫＳＭ01に登録されている素材用得意先品番

			if( SGr_vSOKU_SYUKA->Cells[iCol][iRow] != "不要" )
			{
				for(i1 = 0;i1 < 6;i1++)
				{
                	switch(i1)
					{
					case 0:
						sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN1_SZ;	//品番
						break;
					case 1:
						sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN2_SZ;
						break;
					case 2:
						sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN3_SZ;
						break;
					case 3:
						sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN4_SZ;
						break;
					case 4:
						sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN5_SZ;
						break;
					case 5:
						sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN6_SZ;
						break;
					}
					if(sDTKSHIN_SZ.Trim() == sDTKSHIN.Trim())
					{
						sLot = SGr_vSOKU_SYUKA->Cells[iCol][iRow];
						switch( i1 )
						{
						case 0:
                        	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE1_SZ,"0");
							break;
						case 1:
                        	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE2_SZ,"0");
							break;
						case 2:
                        	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE3_SZ,"0");
							break;
						case 3:
                        	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE4_SZ,"0");
							break;
						case 4:
                        	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE5_SZ,"0");
							break;
						case 5:
                        	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE6_SZ,"0");
							break;
						}
                        break;
                	}
                }
			}
		}
	}
    bLOTCHANGE = false;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnKeyPressイベント	：ユーザーが単一の文字キーを押したときに発生します。
//
//  機能説明
//    出荷（履歴）グリッドにユーザーの入力があるたびに入力文字が有効かを調べます。
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
void __fastcall TForm8::SGr_vRIRE_SYUKAKeyPress(TObject *Sender, char &Key)
{
    int iCol,iRow;
    AnsiString sBuf;

    iCol = SGr_vRIRE_SYUKA->Col;
    iRow = SGr_vRIRE_SYUKA->Row;
    sBuf = SGr_vRIRE_SYUKA->Cells[iCol][iRow];
    Form1->ChkInputData( sBuf, 3, Sender, Key, 6);

    // 入力値（半角小文字a～z）は、強制的に大文字変換してセットします
    if( Key >= 0x61 && Key <= 0x7A ){
		Key -= 0x20;
    }
}

//---------------------------------------------------------------------------
//
//  概要
//    OnKeyPressイベント	：ユーザーが単一の文字キーを押したときに発生します。
//
//  機能説明
//    出荷（測定）グリッドにユーザーの入力があるたびに入力文字が有効かを調べます。
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
void __fastcall TForm8::SGr_vSOKU_SYUKAKeyPress(TObject *Sender, char &Key)
{
    int iCol,iRow;
    AnsiString sBuf;

    iCol=SGr_vSOKU_SYUKA->Col;
    iRow=SGr_vSOKU_SYUKA->Row;
    sBuf = SGr_vSOKU_SYUKA->Cells[iCol][iRow];
    Form1->ChkInputData( sBuf, 3 , Sender, Key, 6);

    // 入力値（半角小文字a～z）は、強制的に大文字変換してセットします
    if( Key >= 0x61 && Key <= 0x7A ){
		Key -= 0x20;
    }
}
//---------------------------------------------------------------------------

