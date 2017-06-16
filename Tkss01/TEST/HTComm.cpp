//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "HTComm.h"
#include "Tkss01.h"
#include "Unit1.h"
#include "UnitDataAccess.h"
#include "StdComm32.h"
#pragma package(smart_init)


extern RSCOM RS232;

//---------------------------------------------------------------------------
//�f�ނ̕\��
//---------------------------------------------------------------------------
void __fastcall HTComm(void)
{
	AnsiString sBuf;
	char c1[128];
	int iRow,iCol;
    bool bCom1;
    char chrHoge=VK_RETURN;
//�V���A���|�[�g������
	bCom1 = false;
	while( 1 )
	{
		if( CommOpen("COM3", "9600", "N,8,1") == 3 )
		{
			bCom1 = true;
			break;
		}
		else
		{
			if(Application->MessageBox("�|�[�g���J���܂���B�@��̐ڑ����m�F���ĉ������B","�x��",MB_OK) == IDOK);
		}
	}

	while(1)
	{
//�@�탊�Z�b�g
		sprintf(c1,"%C%C%C",EOT,"C",CR);
		CommWrite(RS232.COMNO,c1);
    	sprintf(c1,"%C%C%C",EOT,PNO1,CR);
        CommWrite(RS232.COMNO,c1);
        while(1)
        {
        	Sleep(70);
            CommRead(RS232.COMNO, c1);
            sBuf = c1;
            if(sBuf.SubString(1,1) == (char)ACK) break;
            if(sBuf.SubString(1,1) == (char)NAK)
            {
            	sprintf(c1,"%C%C%C",EOT,PNO1,CR);
                CommWrite(RS232.COMNO,c1);
            }
        }
//����f�[�^���͑҂�
        sprintf(c1,"%C%C",ENQ,CR);
        CommWrite(RS232.COMNO,c1);
		while(1)
		{
        	Sleep(70);
			CommRead(RS232.COMNO, c1);
			sBuf = c1;
			if(sBuf.SubString(1,1) == (char)STX )
			{

				iRow = Form1->SGr_vSOKU_SYUKA->Row;
				iCol = Form1->SGr_vSOKU_SYUKA->Col;
        		Form1->sCommBuff = sBuf.SubString(3,1);
        		Form1->sCommBuff += sBuf.SubString(4,sBuf.Length()-4).ToDouble();
				Form1->SGr_vSOKU_SYUKA->Cells[iCol][iRow] = Form1->sCommBuff;
                Form1->SGr_vSOKU_SYUKAKeyPress(0,chrHoge);
				CommClear(RS232.COMNO);
            	break;
			}
			else
			{
        		sprintf(c1,"%C%C",ENQ,CR);
        		CommWrite(RS232.COMNO,c1);
			}
		}
	}
}



