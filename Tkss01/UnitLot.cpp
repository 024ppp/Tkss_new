//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "Thread.h"
#include "Thread1.h"
#include "Unit1.h"
#include "Unit2.h"
#include "Tkss01.h"
#include "UnitDataAccess.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

extern 	KSM02_DATA pORDATA[100];

extern HANDLE		hSOZAI_RIREKI_DATA;   	// �ߋ�����Ώۃ��b�g�f�[�^
extern KSD02_DATA 	*pSOZAI_RIREKI_DATA;   	// �ߋ�����Ώۃ��b�g�f�[�^
extern KSD02_DATA 	pRIREKI_DATA[100];	  	// �ߋ�����Ώۃ��b�g�f�[�^
extern KSM02_DATA 	pSYUKA_DATA[100];	   	// �o�חp�f�[�^
extern KSM02_DATA 	pTEMPORDATA[100];

extern int iSOKU_MEMO_CNT;					//������
extern int iDEBUG;

//���b�g�����ǃf�[�^�ɂ��邩�̖₢���킹
int __fastcall TForm1::SD21SLOT(AnsiString sLOT_S, AnsiString sLOT_E)       //onishi
{
    AnsiString sBuf;
    int iRet;

    sBuf = "SELECT LOTBNG, HINBAN, DENYMD, KOKBNG  FROM SD21S";
    sBuf += " WHERE DTKSHIN ='" + sNowDTKSHIN    + "'";
    sBuf += " AND   DENYMD >='" + sNowSEIKAN_YMD + "'";

    if( sLOT_E.Length() == 0 ){
	sBuf += " AND LOTBNG ='" + sLOT_S + "'";
    } else {
	if( sLOT_S.Length() == 5 ){
	    // �������b�g�i5���j�ɑΉ�
            sBuf += " AND SUBSTR(LOTBNG,2) >= '" + sLOT_S.SubString(2,5) + "'";
            sBuf += " AND SUBSTR(LOTBNG,2) <= '" + sLOT_E.SubString(2,5) + "'";
            sBuf += " ORDER BY SUBSTR(LOTBNG,2)";
	} else {
	    // �C�O���b�g�i6���j�ɑΉ�
            sBuf += " AND LOTBNG >= '" + sLOT_S + "'";
            sBuf += " AND LOTBNG <= '" + sLOT_E + "'";
            sBuf += " ORDER BY LOTBNG";
        }
    }

    //For Debug
    if( iDEBUG == 1 )
    {
        ClpBrd = Clipboard();
        ClpBrd->Open();
        ClpBrd->SetTextBuf(sBuf.c_str());
        ClpBrd->Close();
    }
    //  Initial Query
    Query1->Close();
    Query1->SQL->Clear();
    Query1->SQL->Add(sBuf);
    Query1->Open();
    Query1->Active = true;
    iRet = Query1->RecordCount;

    return( iRet );
}


//���b�gNo���o��
bool __fastcall TForm1::Set_Lot(void)                         //onishi
{
    int i1,iCount;
    int iCnt,iCnt2;
    int iGridWidth = 0;
    int iCol = 0;
    int iOldCol;
    AnsiString sLot,sLot1,sLot2,sAllLot,sCmpStr,sBuf;
    sLot = Edt_LOTNO->Text ;
    sLot2="";

    //���b�g�̐؂�o���i�ʓ��́A��ԓ��͑Ή����邱�Ɓj
    //�����̐؂�o��
    //���b�g���̓ǂݏo���isLots[]�֑��)
    iCnt = 0;
    for(i1=1;i1< sLot.Length() ;i1++)
    {
	    if( strcspn(sLot.SubString(i1,1).c_str(),"0123456789XYZxyz")==0)
	    {
	        iCount = 1;
	        i1++;
	        while(strcspn(sLot.SubString(i1,1).c_str(),"-, ")!=0)
	        {
		        i1++;
		        iCount ++;
		        if(i1 > sLot.Length()) break;
	        }
	        sRots[iCnt]=sLot.SubString(i1-iCount,iCount);
	        iCnt ++;
            // 2003/05/15 A.Tamura
            if( iCnt >= 100 )   break;
	    }
    }
    if(iCnt == 0 )
    {
	    SGr_vSOKU_SYUKA->ColCount 	= 1;
	    SGr_tSOKU->ColCount		= 1;
	    SGr_vSOKU_SOZAI->ColCount 	= 1;
	    SGr_tSOKU_SYUKA->ColCount 	= 1;
	    SGr_tSOKU_SOZAI->ColCount 	= 1;
	    SGr_tSOKU->Cells[1][1] = "";
	    SGr_tSOKU->Cells[1][0] = "";
	    SGr_tSOKU->Cells[0][0] = "";
    }

    //���b�g�����i�͈�OR�ʁj�t���O���
    iCnt2 = 0;
    for(i1=1;i1< sLot.Length() ;i1++)
    {
	    while( strcspn(sLot.SubString(i1,1).c_str(),"0123456789XYZxyz")==0
	    && (i1 < sLot.Length()) )
	    {
	        i1+=sRots[iCnt2].Length();
	        bKikanF[iCnt2]=false;
	        while( strcspn(sLot.SubString(i1,1).c_str(),"0123456789XYZxyz")!=0
	        && (i1 < sLot.Length()) )
	        {
		        if(strcspn(sLot.SubString(i1,1).c_str(),"-")==0)
		        {
		            bKikanF[iCnt2] = true;
		            break;
		        }
		        i1++;
	        }
	        iCnt2++;
            // 2003/05/15 A.Tamura
            if( iCnt2 >= 100 )   break;
	    }
        // 2003/05/15 A.Tamura
        if( iCnt2 >= 100 )   break;
    }
    iCnt2 -= 1;
    bKikanF[iCnt2] = false;
    iRotCount = iCnt2;  //�O���܂�ł���̂Ŏ��ۂ�+�P�Ń��b�g��

    // �͈͎w��̎��A�����܂������b�gNO���w�肳��Ă��邩�`�F�b�N���܂�
    for(i1=0;i1<=iRotCount;i1++) {

	    //��Ԃŏ���
	    if( bKikanF[i1] == true ) {
	        if( sRots[i1].Length() == 6 ){
		        sLot1 = sRots[i1].SubString(1,2);
		        sLot2 = sRots[i1+1].SubString(1,2);
	        } else {
		        sLot1 = sRots[i1].SubString(1,1);
		        sLot2 = sRots[i1+1].SubString(1,1);
	        }
	        if( bNowSEIKANDATA == false && sLot1 != sLot2 ) {
		        MessageDlg("�����܂������b�gNO�͈͎̔w��́A�u�����ǃf�[�^���猟���v���`�F�b�N���ĉ������B", mtWarning,
                        TMsgDlgButtons() << mbOK , 0);
		        return(false);
	        }
	    }
    }

    // Grid��Colum�������������܂�
    SGr_vSOKU_SYUKA->ColCount 	= 1;
    SGr_tSOKU->ColCount		= 1;
    SGr_vSOKU_SOZAI->ColCount 	= 1;
    SGr_tSOKU_SYUKA->ColCount 	= 1;
    SGr_tSOKU_SOZAI->ColCount 	= 1;
    SGr_tSOKU->Cells[1][0] = "";
    // k.k 2003.05.15
    SGr_vRIRE_SOZAI->ColCount = 1;
    SGr_vSOKU_SOZAI->ColCount = 1;
    SGr_vRIRE_SYUKA->ColCount = 1;
    SGr_vSOKU_SYUKA->ColCount = 1;
    SGr_tRIRE_SOZAI->ColCount = 0;
    SGr_tRIRE_SYUKA->ColCount = 0;
    // ���l�������������܂�
    for(i1 = 0 ; i1 < iSOKU_MEMO_CNT ; i1++) {
	    if(Mem_vSOKU_MEMO[i1]) {
	        delete Mem_vSOKU_MEMO[i1];
	    }
    }
    iSOKU_MEMO_CNT = 0;

    iCol = 0;
    //���ԓ��͂ōŏI���b�g��2�\�������̂ő΍���u���邱��
    for(i1=0;i1<=iRotCount;i1++) {

 	    //��Ԃŏ���
        if( bKikanF[i1] == true ) {
	        if(bNowSEIKANDATA == false) {
		    // ���Y�Ǘ��V�X�e��SD21S�ɖ₢���킹�����܂���
                if( sRots[i1].Length() == 6 ){
		            sLot1 = sRots[i1].SubString(3,sRots[i1].Length()-2);
                    sLot2 = sRots[i1+1].SubString(3,sRots[i1+1].Length()-2);
                } else {
		            sLot1 = sRots[i1].SubString(2,sRots[i1].Length()-1);
                    sLot2 = sRots[i1+1].SubString(2,sRots[i1+1].Length()-1);
                }

                // Colum�����v�Z
                iGridWidth += (sLot2.ToIntDef(0)-sLot1.ToIntDef(0)) + 1;

                // �K�v��Colum��ݒ�
                SGr_vSOKU_SYUKA->ColCount 	= iGridWidth;
                SGr_tSOKU->ColCount 		= iGridWidth;
                SGr_vSOKU_SOZAI->ColCount 	= iGridWidth;
                SGr_tSOKU_SYUKA->ColCount 	= iGridWidth;
                SGr_tSOKU_SOZAI->ColCount 	= iGridWidth;

                // ���b�gNO��\�����܂�
                for(iOldCol=sLot1.ToIntDef(0);iOldCol <= sLot2.ToIntDef(0);iOldCol++) {
		            sBuf = iOldCol;
                    SGr_tSOKU->Cells[iCol][0] = sRots[i1].SubString(1,1) + AnsiString::StringOfChar('0', sLot1.Length()-sBuf.Length()) + sBuf;
                    SGr_tSOKU->Cells[iCol][0] = SGr_tSOKU->Cells[iCol][0].Trim();
                    SGr_tSOKU->Cells[iCol][1] = " ";                           //onishi HINBAN
                    iCol++;
                    // SGr_tSOKU->Refresh();
            }
	    } else {
	        // ���Y�Ǘ��V�X�e��SD21S�ɖ₢���킹�����܂�
            iCnt2 = SD21SLOT(sRots[i1], sRots[i1+1]);
            if( iCnt2 > 0 ){

		    // Colum�����v�Z
                    iGridWidth += iCnt2;

                    // �K�v��Colum��ݒ�
                    SGr_vSOKU_SYUKA->ColCount 	= iGridWidth;
                    SGr_tSOKU->ColCount 	    = iGridWidth;
                    SGr_vSOKU_SOZAI->ColCount 	= iGridWidth;
                    SGr_tSOKU_SYUKA->ColCount 	= iGridWidth;
                    SGr_tSOKU_SOZAI->ColCount 	= iGridWidth;

                    // ���b�gNO��\�����܂�
                    while(Query1->Eof == false) {
			            SGr_tSOKU->Cells[iCol][0] = Query1->FieldValues["LOTBNG"];
                        SGr_tSOKU->Cells[iCol][1] = Query1->FieldValues["HINBAN"];    //onishi SD21S.HINBAN
                        Query1->Next();
                        iCol++;
                    }
                }
            }
            i1++;

	} else {
	    if(bNowSEIKANDATA == false) {
		// ���Y�Ǘ��V�X�e��SD21S�ɖ₢���킹�����܂���

                // Colum�����v�Z
                iGridWidth ++;

                // �K�v��Colum��ݒ�
                SGr_vSOKU_SYUKA->ColCount 	= iGridWidth;
                SGr_tSOKU->ColCount 		= iGridWidth;
                SGr_vSOKU_SOZAI->ColCount 	= iGridWidth;
                SGr_tSOKU_SYUKA->ColCount 	= iGridWidth;
                SGr_tSOKU_SOZAI->ColCount 	= iGridWidth;

                // ���b�gNO��\�����܂�
                SGr_tSOKU->Cells[iCol][0] = sRots[ i1 ];
                SGr_tSOKU->Cells[iCol][1] = " ";                               //onishi HINBAN
                iCol++;
            } else {
		// ���Y�Ǘ��V�X�e��SD21S�ɖ₢���킹�����܂�
                iCnt2 = SD21SLOT(sRots[i1], "");
                if( iCnt2 > 0 ){

		    // Colum�����v�Z
                    iGridWidth += 1;

                    // �K�v��Colum��ݒ�
                    SGr_vSOKU_SYUKA->ColCount 	= iGridWidth;
                    SGr_tSOKU->ColCount 	= iGridWidth;
                    SGr_vSOKU_SOZAI->ColCount 	= iGridWidth;
                    SGr_tSOKU_SYUKA->ColCount 	= iGridWidth;
                    SGr_tSOKU_SOZAI->ColCount 	= iGridWidth;

                    // ���b�gNO��\�����܂�
                    if(Query1->Eof == false) {
			            SGr_tSOKU->Cells[iCol][0] = Query1->FieldValues["LOTBNG"];
                        SGr_tSOKU->Cells[iCol][1] = Query1->FieldValues["HINBAN"];    //onishi SD21S.HINBAN
                        iCol++;
                    }
                }
            }
        }
    }

    // �������ʂȂ��i�������f�j
    if( iCol <= 0 ){
    	MessageDlg("�ΏۂƂȂ郍�b�gNO��������܂���ł����B", mtWarning,
        TMsgDlgButtons() << mbOK , 0);
        return(false);
    }

    iSOKU_MEMO_CNT = 0;
    SGr_vSOKU_SOZAI->LeftCol = 0;
    SGr_vSOKU_SYUKA->LeftCol = 0;
    SBx_vSOKU_MEMO->HorzScrollBar->Position = 0;
    if(SGr_tSOKU->Cells[0][0]!="")
    {
	    Mem_vSOKU_MEMOORG->Visible = false;
	    Mem_vSOKU_MEMO  = new TMemo *[SGr_tSOKU->ColCount];

	    for(i1 = 0 ; i1 < SGr_tSOKU->ColCount ;i1++)
	    {
	        sBuf = i1;
	        Mem_vSOKU_MEMO[i1]		        = new TMemo(SBx_vSOKU_MEMO);
	        Mem_vSOKU_MEMO[i1]->Name	    = "Mem_vSOKU_MEMO" + AnsiString::StringOfChar('0000', 5-sBuf.Length()) + sBuf;
	        Mem_vSOKU_MEMO[i1]->Parent	    = SBx_vSOKU_MEMO;
	        Mem_vSOKU_MEMO[i1]->Width	    = Mem_vSOKU_MEMOORG->Width;
	        Mem_vSOKU_MEMO[i1]->Left	    = (Mem_vSOKU_MEMOORG->Width + 1) * i1;
	        Mem_vSOKU_MEMO[i1]->Height	    = Mem_vSOKU_MEMOORG->Height;
	        Mem_vSOKU_MEMO[i1]->Text	    = "";
	        Mem_vSOKU_MEMO[i1]->BorderStyle = bsNone;
	        Mem_vSOKU_MEMO[i1]->OnEnter	    = FormEnter;
	        Mem_vSOKU_MEMO[i1]->OnKeyDown   = AllKeyDown;
	        Mem_vSOKU_MEMO[i1]->OnKeyUp	    = AllKeyUp;
	        Mem_vSOKU_MEMO[i1]->OnKeyPress  = Mem_MEMOKeyPress;
	        Mem_vSOKU_MEMO[i1]->OnEnter	    = Mem_MEMOEnter;
	        Mem_vSOKU_MEMO[i1]->OnExit	    = Mem_MEMOExit;
	    }
	    if( SGr_tSOKU->ColCount > 0 ){
	        Pnl_DUMMY3->Parent		= SBx_vSOKU_MEMO;
	        Pnl_DUMMY3->Top		    = 0;
	        Pnl_DUMMY3->Height		= Mem_vSOKU_MEMOORG->Height;
	        Pnl_DUMMY3->Width		= Mem_vSOKU_MEMOORG->Width + 15;
	        Pnl_DUMMY3->Left		= (Mem_vSOKU_MEMOORG->Width + 1) * i1;
	        Pnl_DUMMY3->Ctl3D		= false;
	        Pnl_DUMMY3->BevelInner	= bvNone;
	        Pnl_DUMMY3->BevelOuter	= bvNone;
	        Pnl_DUMMY3->BorderStyle	= bsNone;
	        Pnl_DUMMY3->BorderWidth	= 0;
	        Pnl_DUMMY3->Visible		= true;
	    }
	    iSOKU_MEMO_CNT = i1;
    }

    return(true);
}




