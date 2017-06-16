//---------------------------------------------------------------------------
//
//  Unit12.cpp
//    【出荷検査システム－検査測定】
//    素材データの取り直しフォーム（TForm12クラス）のメンバ関数の定義
//
//  作成者
//    市川　和弘
//
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit12.h"
#include "Tkss01.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm12 *Form12;

extern CELLINFO_DATA *pCELLINFO_SOKU_SYUKA;
extern CELLINFO_DATA *pCELLINFO_RIRE_SYUKA;
extern CELLINFO_DATA *pCELLINFO_SOKU_SOZAI;
extern CELLINFO_DATA *pCELLINFO_RIRE_SOZAI;
//ロット割り当て＆ＫＳＤ01
//ロット割り当て
extern HANDLE hSOKU_KSD01_DATA;
extern KSD01_DATA *pSOKU_KSD01_DATA;
extern HANDLE hRIRE_KSD01_DATA;
extern KSD01_DATA *pRIRE_KSD01_DATA;
//---------------------------------------------------------------------------
__fastcall TForm12::TForm12(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「ＯＫ」ボタンを押した時の処理
//
//  機能説明
//    RadioButton1Checked = true:測定値（表）のみの取り込みを素材データから行います。
//            〃          = false:測定値（表）、印刷値（裏）の取り込みを素材データから行います。
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
void __fastcall TForm12::ButtonOKClick(TObject *Sender)
{
    // 通常の測定画面に変更
    Form1->SGr_vRIRE_SOZAI->Color = (TColor)0x00D2FFFF;
    Form1->SGr_vSOKU_SOZAI->Color = (TColor)0x00D2FFFF;
    Form1->SGr_vRIRE_SYUKA->Color = (TColor)0x00FFEEDD;
    Form1->SGr_vSOKU_SYUKA->Color = clWindow;
    Form1->SCREEN_SET();
    Form1->Mem_vRIRE_MEMOORG->Color = (TColor)0x00FFEEDD;
    Form1->SBr1->Panels->Items[0]->Text = "通常の測定画面です。";
    InfoClear();

	// 2004.12.24(X'mas Eve) A.Tamura 取り込み予定のLOTNO1_SZ～LOTNO6_SZを再設定する
    LOTNO1_SZ_Clear();

    if(Rdo_Button1->Checked == true)
    {
        Form1->GET_KSD22_AGAIN();
    }
    else
    {
        Form1->GET_KSD22();
    }
    Form1->GET_SOZAI_KSD02_DISP();
    Close();
}
//---------------------------------------------------------------------------
//
//  概要
//    OnActivateイベント	：フォームがアクティブになったときに発生します。
//
//  機能説明
//    デフォルトのラジオボタンにチェックを入れます。
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
void __fastcall TForm12::FormActivate(TObject *Sender)
{
     Rdo_Button1->Checked = true;
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Cancel」ボタンを押した時の処理
//
//  機能説明
//    Formを閉じます。
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
void __fastcall TForm12::ButtonCancelClick(TObject *Sender)
{
    Close();    
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数：KSD01に格納される予定のLOTNO1_SZ～LOTNO6_SZを再設定します。
//
//  機能説明
//    KSD01に格納される予定のLOTNO1_SZ～LOTNO6_SZを再設定します。
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
void __fastcall TForm12::LOTNO1_SZ_Clear(void)
{
	int iCol,i2;
	AnsiString sBuf2;

    // 測定画面側
	for(iCol = 0;iCol<Form1->SGr_tSOKU->ColCount;iCol++)
	{
        for(i2 = 0;i2 < 6;i2++)
        {
        	switch( i2 )
            {
            case 0:
            	sBuf2 = pSOKU_KSD01_DATA[iCol].DTKSHIN1_SZ;
                break;
            case 1:
            	sBuf2 = pSOKU_KSD01_DATA[iCol].DTKSHIN2_SZ;
                break;
            case 2:
            	sBuf2 = pSOKU_KSD01_DATA[iCol].DTKSHIN3_SZ;
                break;
            case 3:
            	sBuf2 = pSOKU_KSD01_DATA[iCol].DTKSHIN4_SZ;
                break;
            case 4:
            	sBuf2 = pSOKU_KSD01_DATA[iCol].DTKSHIN5_SZ;
                break;
            case 5:
            	sBuf2 = pSOKU_KSD01_DATA[iCol].DTKSHIN6_SZ;
                break;
            }
	 		if(AnsiString(pKSM01_DATA.LOT_LINK_SZ) == 1 && sBuf2.Length() != 0)
			{
                switch( i2 )
                {
                case 0:
				    strcpy(pSOKU_KSD01_DATA[iCol].LOTNO1_SZ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
                    break;
                case 1:
				    strcpy(pSOKU_KSD01_DATA[iCol].LOTNO2_SZ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
                    break;
                case 2:
                    strcpy(pSOKU_KSD01_DATA[iCol].LOTNO3_SZ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
                    break;
                case 3:
                    strcpy(pSOKU_KSD01_DATA[iCol].LOTNO4_SZ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
                    break;
                case 4:
                    strcpy(pSOKU_KSD01_DATA[iCol].LOTNO5_SZ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
                    break;
                case 5:
                    strcpy(pSOKU_KSD01_DATA[iCol].LOTNO6_SZ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
                    break;
                }
			}
		}
	}


    // 履歴画面側
    if(Form1->iRIRE_CNT == 0 ) return;
	for(iCol = 0;iCol<Form1->SGr_tRIRE->ColCount;iCol++)
	{
        for(i2 = 0;i2 < 6;i2++)
        {
        	switch( i2 )
            {
            case 0:
            	sBuf2 = pRIRE_KSD01_DATA[iCol].DTKSHIN1_SZ;
                break;
            case 1:
            	sBuf2 = pRIRE_KSD01_DATA[iCol].DTKSHIN2_SZ;
                break;
            case 2:
            	sBuf2 = pRIRE_KSD01_DATA[iCol].DTKSHIN3_SZ;
                break;
            case 3:
            	sBuf2 = pRIRE_KSD01_DATA[iCol].DTKSHIN4_SZ;
                break;
            case 4:
            	sBuf2 = pRIRE_KSD01_DATA[iCol].DTKSHIN5_SZ;
                break;
            case 5:
            	sBuf2 = pRIRE_KSD01_DATA[iCol].DTKSHIN6_SZ;
                break;
            }
	 		if(AnsiString(pKSM01_DATA.LOT_LINK_SZ) == 1 && sBuf2.Length() != 0)
			{
				strcpy(pRIRE_KSD01_DATA[iCol].LOTNO1_SZ,Form1->SGr_tRIRE->Cells[iCol][0].c_str());
				strcpy(pRIRE_KSD01_DATA[iCol].LOTNO2_SZ,Form1->SGr_tRIRE->Cells[iCol][0].c_str());
				strcpy(pRIRE_KSD01_DATA[iCol].LOTNO3_SZ,Form1->SGr_tRIRE->Cells[iCol][0].c_str());
				strcpy(pRIRE_KSD01_DATA[iCol].LOTNO4_SZ,Form1->SGr_tRIRE->Cells[iCol][0].c_str());
				strcpy(pRIRE_KSD01_DATA[iCol].LOTNO5_SZ,Form1->SGr_tRIRE->Cells[iCol][0].c_str());
				strcpy(pRIRE_KSD01_DATA[iCol].LOTNO6_SZ,Form1->SGr_tRIRE->Cells[iCol][0].c_str());
			}
		}
	}

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：素材測定バッファをクリアします。
//
//  機能説明
//    読み込み前に素材バッファをクリアします。
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
void __fastcall TForm12::InfoClear(void)
{
    int i1,i2;
    for( i1 = 0; i1 < Form1->SGr_vSOKU_SOZAI->ColCount ; i1++)
    {
        for(i2= 1; i2 <  Form1->SGr_vSOKU_SOZAI->RowCount ; i2++)
        {
            Form1->SGr_vSOKU_SOZAI->Cells[i1][i2]="";
            strcpy(pCELLINFO_SOKU_SOZAI[i1*Form1->SGr_vSOKU_SOZAI->RowCount+i2].RESULT,"");
            if(Rdo_Button1->Checked == false)
            {
                strcpy(pCELLINFO_SOKU_SOZAI[i1*Form1->SGr_vSOKU_SOZAI->RowCount+i2].DISP_RESULT,"");
            }
            pCELLINFO_SOKU_SOZAI[i1*Form1->SGr_vSOKU_SOZAI->RowCount+i2].JUDGE = 2;
            //新規に取り直すので強制的にUPDATEフラグをTrueにしてセーブが出来るようにします。
            pSOKU_KSD01_DATA[i1].UPD_FLG = true;
        }
    }
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：Label4(測定用値（表）と印刷用値（裏）に取り込みを行う。)を押した時の処理
//
//  機能説明
//    Formを閉じます。
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
void __fastcall TForm12::Label4Click(TObject *Sender)
{
    Rdo_Button2->Checked = true;
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：Label2(測定用値（表）のみに取り込みを行う。)を押した時の処理
//
//  機能説明
//    Formを閉じます。
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
void __fastcall TForm12::Label2Click(TObject *Sender)
{
    Rdo_Button1->Checked = true;

}
//---------------------------------------------------------------------------


