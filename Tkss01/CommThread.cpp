//---------------------------------------------------------------------------
//
//  CommThread.cpp
//    �y�o�׌����V�X�e���|�O���@��ʐM�z
//    �T�u�t�H�[���iCommThread�N���X�j�̃����o�֐��̒�`
//
//  �쐬��
//    �s��@�a�O
//
//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "CommThread.h"
#include <windows>
#include "Tkss01.h"
#include "Unit1.h"
#include "Unit7.h"
#include "UnitDataAccess.h"
#include "StdComm32.h"
#pragma package(smart_init)

// k.y 2003.05.17
// GRAPH_DATA	*pInfoGlaph;
GRAPH_DATA	pInfoGlaph;

//�Z�����
extern HANDLE hCELLINFO_SOKU_SYUKA;
extern HANDLE hCELLINFO_RIRE_SYUKA;
extern HANDLE hCELLINFO_SOKU_SOZAI;
extern HANDLE hCELLINFO_RIRE_SOZAI;
extern CELLINFO_DATA *pCELLINFO_SOKU_SYUKA;
extern CELLINFO_DATA *pCELLINFO_RIRE_SYUKA;
extern CELLINFO_DATA *pCELLINFO_SOKU_SOZAI;
extern CELLINFO_DATA *pCELLINFO_RIRE_SOZAI;
int		iPORT_NO;
int     iKIKA_KIND;
extern bool bCellWrite;
//---------------------------------------------------------------------------
// ���ӁF�قȂ�X���b�h�����L���� VCL �̃��\�b�h/�֐�/�v���p�e�B��
//       �ʂ̃X���b�h�̒����爵���ꍇ�C�r�������̖�肪�������܂��B
//
//       ���C���X���b�h�̏��L����I�u�W�F�N�g�ɑ΂��Ă� Synchronize
//       ���\�b�h���g�������ł��܂��B���̃I�u�W�F�N�g���Q�Ƃ��邽��
//       �̃��\�b�h���X���b�h�N���X�ɒǉ����CSynchronize ���\�b�h��
//       �����Ƃ��ēn���܂��B
//
//       ���Ƃ��� UpdateCaption ���ȉ��̂悤�ɒ�`���A
//
//          void __fastcall MyThread::UpdateCaption()
//          {
//            Form1->Caption = "�X���b�h���珑�������܂���";
//          }
//
//       Execute ���\�b�h�̒��� Synchronize ���\�b�h�ɓn�����ƂŃ��C
//       ���X���b�h�����L���� Form1 �� Caption �v���p�e�B�����S�ɕ�
//       �X�ł��܂��B
//
//          Synchronize(UpdateCaption);
//
//---------------------------------------------------------------------------

extern RSCOM RS232;

__fastcall CommThread::CommThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
//  Priority = tpIdle;
  Priority = tpNormal;
}
//---------------------------------------------------------------------------
//
//  �T�v
//    Execute�C�x���g	�F�X���b�h�����s���ꂽ�Ƃ��Ɏ��ۂɌĂяo�����R�[�h���܂ޏ������z���\�b�h��񋟂��܂��B
//
//  �@�\����
//    �X���b�h���s���ɌĂяo���ƁA�Ȍ�X���b�h��������J�n���܂��B
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall CommThread::Execute()
{
	AnsiString sBuf;
	char c1[128];
    char c2[3];
	int iRow,iCol;//,i1;
    int iOldPort;
    //bool bCom1;
	int iRowCount;
	int ACol,ARow;
    double dMAX,dMIN;
    bool bRtn;				//2003.05.08 E.Takase Add
    //double dBuf;			//2003.05.08 E.Takase Add
    AnsiString sBufConv;	//2003.05.08 E.Takase Add

//�V���A���|�[�g������
	//bCom1 = false;
	while( 1 )
	{
		if( CommOpen("COM1", "9600", "N,8,1") == 1 )
		{
			//bCom1 = true;
			break;
		}
		else
		{
//			if(Application->MessageBox("�|�[�g���J���܂���B�@��̐ڑ����m�F���ĉ������B","�x��",MB_OK) == IDOK);
		}
	}

//�ʐM�|�[�g1�I��
	RS232.COMNO = 1;
    iPORT_NO = 0;
	iOldPort = 0;
	while(1)
	{
//�@�탊�Z�b�g
		sprintf(c1,"%C%C%C",EOT,'C',CR);
		CommWrite(RS232.COMNO,c1);
		switch(iPORT_NO)
		{
		case 0:
			sprintf(c1,"%C%C%C",EOT,PNO1,CR);
			break;
		case 1:
			sprintf(c1,"%C%C%C",EOT,PNO2,CR);
			break;
		case 2:
			sprintf(c1,"%C%C%C",EOT,PNO3,CR);
			break;
		case 3:
			sprintf(c1,"%C%C%C",EOT,PNO4,CR);
			break;
		case 4:
			sprintf(c1,"%C%C%C",EOT,PNO5,CR);
			break;
        default:
			break;
		}
        CommWrite(RS232.COMNO,c1);
        while(1)
        {
        	Sleep(70);
            CommRead(RS232.COMNO, c1);
            sBuf = c1;
            if(sBuf.SubString(1,1) == (char)ACK) break;
            if((sBuf.SubString(1,1) == (char)NAK))
            {
				switch(iPORT_NO)
				{
				case 0:
					sprintf(c1,"%C%C%C",EOT,PNO1,CR);
					break;
				case 1:
					sprintf(c1,"%C%C%C",EOT,PNO2,CR);
					break;
				case 2:
					sprintf(c1,"%C%C%C",EOT,PNO3,CR);
					break;
				case 3:
					sprintf(c1,"%C%C%C",EOT,PNO4,CR);
					break;
				case 4:
					sprintf(c1,"%C%C%C",EOT,PNO5,CR);
					break;
        		default:
					break;
				}
                CommWrite(RS232.COMNO,c1);
            }
        }
//����f�[�^���͑҂�
       	sprintf(c1,"%C%C",ENQ,CR);
        CommWrite(RS232.COMNO,c1);
		while(1)
		{
            //���C����ʂȂǂŃ`�����l���̐ؑւ�����ƈȉ��̃X�C�b�`�������s����܂��B
			if( iOldPort != iPORT_NO )
			{
            	iOldPort = iPORT_NO;
				Sleep(70);
  				sprintf(c1,"%C%C%C",EOT,'C',CR);
                CommWrite(RS232.COMNO,c1);
				while(1)
				{
					switch(iPORT_NO)
                	{
					case 0:
						sprintf(c1,"%C%C%C",EOT,PNO1,CR);
						break;
					case 1:
						sprintf(c1,"%C%C%C",EOT,PNO2,CR);
						break;
					case 2:
						sprintf(c1,"%C%C%C",EOT,PNO3,CR);
						break;
					case 3:
						sprintf(c1,"%C%C%C",EOT,PNO4,CR);
						break;
					case 4:
						sprintf(c1,"%C%C%C",EOT,PNO5,CR);
						break;
        			default:
						break;
					}
        			CommWrite(RS232.COMNO,c1);
                	Sleep(150);
                	CommRead(RS232.COMNO, c1);
                	sBuf = c1;
                	if(sBuf.SubString(1,1) == (char)ACK)
        			{
						sprintf(c1,"%C%C",ENQ,CR);
        				CommWrite(RS232.COMNO,c1);
                        Sleep(70);
						break;
					}
                }
			}
        	Sleep(70);
			CommRead(RS232.COMNO, c1);
			sBuf = c1;
            //�f�[�^�̓��͂�����ƈȉ��̏��������s���܂��B
			if(sBuf.SubString(1,1) == (char)STX )
			{

        		Form1->sCommBuff = sBuf.SubString(3,1);
                //2003.05.08 E.Takase Add��
        		Form1->sCommBuff += Form1->ConvDoubleDefD(sBuf.SubString(4,sBuf.Length()-4),0.0);
                //2003.05.08 E.Takase Add��
                //2003.05.08 E.Takase Add �R�����g��
        		//Form1->sCommBuff += sBuf.SubString(4,sBuf.Length()-4).ToDouble();
                //2003.05.08 E.Takase Add �R�����g��
				switch(pInfoGlaph.GRID_NO)
				{
				case 1:
					ACol = Form1->SGr_vSOKU_SYUKA->Col;
					ARow = Form1->SGr_vSOKU_SYUKA->Row;
					iRowCount = Form1->SGr_vSOKU_SYUKA->RowCount;
					iRow = Form1->SGr_vSOKU_SYUKA->Row;
					iCol = Form1->SGr_vSOKU_SYUKA->Col;
                //�A�������o�͂Ŗ���O���t��`�悷���PC�̓��삪�s����ɂȂ�̂Ń��b�N�t���O��݂��܂���
                    bCellWrite = true;
                //�L�[�{�[�h�C�x���g�ŃZ���ɓ��̓Z����҂����܂�
                    keybd_event(VK_SPACE,0,0,0);
					Form1->SGr_vSOKU_SYUKA->Cells[iCol][iRow] = Form1->sCommBuff;
                    Form1->SGr_vSOKU_SYUKAComPress();
                    bCellWrite = false;
                //�L�[�{�[�h�C�x���g�ŃZ���̈ړ��ƃO���t�̕`����s���܂�
                    keybd_event(VK_RETURN,0,0,0);
                //�`���C����炵�܂�
                //�`���C����������ꍇ��VCL�R���|�[�l���g���g�p����̂�Synchronize�R�}���h���K�{
					iRow = Form1->SGr_vSOKU_SYUKA->RowCount;
	                //�ȏ�ȉ��̋K�i�̏ꍇ�΍�
                    iKIKA_KIND = 1;		//�f�t�H���g�͏㉺���Ŕ���
            		if(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+ARow].KIKA_TYPE) == 1)
                    {
            			if(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+ARow].KIKA_KIND) == 2)
			            {
            				iKIKA_KIND = 2;
			            }
            			else if(AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRowCount+ARow].KIKA_KIND) == 3)
			            {
            				iKIKA_KIND = 3;
			            }
            		}
					dMAX= pCELLINFO_SOKU_SYUKA[ACol*iRow+ARow].MAX;
                    dMIN= pCELLINFO_SOKU_SYUKA[ACol*iRow+ARow].MIN;
			        switch (AnsiString(pCELLINFO_SOKU_SYUKA[ACol*iRow+ARow].KIKA_TYPE).ToIntDef(0))
					{
			        case 1:
					case 2:
                    	//2003.05.08 E.Takase Add��
                        bRtn = Form1->ConvDoubleDefS(AnsiString(Form1->sCommBuff),"0.00",AnsiString(Form1->sCommBuff),&sBufConv);
                        if ( bRtn )
                        {
    						switch( iKIKA_KIND )
	    					{
		    				case 2:
	                        	if( Form1->ConvDoubleDefD(AnsiString(Form1->sCommBuff),0.0) <= dMAX  )
    	                    	{
                             	    Synchronize(OK_BEEP);
            	            	}
                	    	    else
                        		{
                             	    Synchronize(NG_BEEP);
                        		}
                                break;
				    		case 3:
	                        	if( Form1->ConvDoubleDefD(AnsiString(Form1->sCommBuff),0.0) >= dMIN )
    	                    	{
                             	    Synchronize(OK_BEEP);
                	        	}
                    	    	else
                        		{
                             	    Synchronize(NG_BEEP);
                        		}
                                break;
                            default:
	                    	    if( Form1->ConvDoubleDefD(AnsiString(Form1->sCommBuff),0.0) <= dMAX
                                &&  Form1->ConvDoubleDefD(AnsiString(Form1->sCommBuff),0.0) >= dMIN )
        	                	{
                             	    Synchronize(OK_BEEP);
                	        	}
                    	    	else
                        		{
                              	    Synchronize(NG_BEEP);
	                    	    }
						    }
                        } else {
							if(AnsiString(Form1->sCommBuff).Length() != 0)
							{
								Synchronize(NG_BEEP);
							}
                        }
                        //2003.05.08 E.Takase Add��
                        //2003.05.08 E.Takase Add �R�����g��
            			break;
					default:
						break;
					}
/////////////////////////////////
					break;
                //�ȍ~��CASE���̓O���b�h�̈ʒu���Ⴄ�����ŏ������e�͓����ł��B
				case 2:
					ACol = Form1->SGr_vRIRE_SYUKA->Col;
					ARow = Form1->SGr_vRIRE_SYUKA->Row;
					iRowCount = Form1->SGr_vRIRE_SYUKA->RowCount;
					iRow = Form1->SGr_vRIRE_SYUKA->Row;
					iCol = Form1->SGr_vRIRE_SYUKA->Col;
                //�A�������o�͂Ŗ���O���t��`�悷���PC�̓��삪�s����ɂȂ�̂Ń��b�N�t���O��݂��܂���
                    bCellWrite = true;
                //�L�[�{�[�h�C�x���g�ŃZ���ɓ��̓Z����҂����܂�
                    keybd_event(VK_SPACE,0,0,0);
					Form1->SGr_vRIRE_SYUKA->Cells[iCol][iRow] = Form1->sCommBuff;
                    Form1->SGr_vRIRE_SYUKAComPress();
                    bCellWrite = false;
                    keybd_event(VK_RETURN,0,0,0);
					strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].DISP_RESULT,Form1->SGr_vRIRE_SYUKA->Cells[iCol][iRow].c_str());
					/////////////////////////////////
                    iKIKA_KIND = 1;		//�f�t�H���g�͏㉺���Ŕ���
            		if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+ARow].KIKA_TYPE) == 1)
                    {
            			if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+ARow].KIKA_KIND) == 2)
			            {
            				iKIKA_KIND = 2;
			            }
            			else if(AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRowCount+ARow].KIKA_KIND) == 3)
			            {
            				iKIKA_KIND = 3;
			            }
            		}
					//�`���C����炵�܂�
					iRow = Form1->SGr_vRIRE_SYUKA->RowCount;
					dMAX= pCELLINFO_RIRE_SYUKA[ACol*iRow+ARow].MAX;
                    dMIN= pCELLINFO_RIRE_SYUKA[ACol*iRow+ARow].MIN;
			        switch (AnsiString(pCELLINFO_RIRE_SYUKA[ACol*iRow+ARow].KIKA_TYPE).ToIntDef(0))
					{
			        case 1:
					case 2:

                    	//2003.05.08 E.Takase Add��
                        bRtn = Form1->ConvDoubleDefS(AnsiString(Form1->sCommBuff),"0.00",AnsiString(Form1->sCommBuff),&sBufConv);
                        if ( bRtn )
                        {
    						switch( iKIKA_KIND )
	    					{
		    				case 2:
	                        	if( Form1->ConvDoubleDefD(AnsiString(Form1->sCommBuff),0.0) <= dMAX  )
    	                    	{
                             	    Synchronize(OK_BEEP);
            	            	}
                	    	    else
                        		{
                             	    Synchronize(NG_BEEP);
                        		}
                                break;
				    		case 3:
	                        	if( Form1->ConvDoubleDefD(AnsiString(Form1->sCommBuff),0.0) >= dMIN )
    	                    	{
                             	    Synchronize(OK_BEEP);
                	        	}
                    	    	else
                        		{
                             	    Synchronize(NG_BEEP);
                        		}
                                break;
                            default:
	                    	    if( Form1->ConvDoubleDefD(AnsiString(Form1->sCommBuff),0.0) <= dMAX
                                &&  Form1->ConvDoubleDefD(AnsiString(Form1->sCommBuff),0.0) >= dMIN )
        	                	{
                             	    Synchronize(OK_BEEP);
                	        	}
                    	    	else
                        		{
                              	    Synchronize(NG_BEEP);
	                    	    }
						    }
                        } else {
							if(AnsiString(Form1->sCommBuff).Length() != 0)
							{
                             	Synchronize(NG_BEEP);
							}
                        }
                        //2003.05.08 E.Takase Add��
                        //2003.05.08 E.Takase Add �R�����g��
						//try {
						//		if((dMIN > AnsiString(Form1->sCommBuff).ToDouble()) || (dMAX < AnsiString(Form1->sCommBuff).ToDouble()))
	   					//	{
						//		Form1->NG_BEEP(0);
						//	}
						//	else
						//	{
						//		Form1->OK_BEEP(0);
						//	}
        			    //}
						//catch(EConvertError& e){
						//	if(AnsiString(Form1->sCommBuff).Length() != 0)
						//	{
						//		Form1->NG_BEEP(0);
						//	}
						//}
						//catch(...){
						//	if(AnsiString(Form1->sCommBuff).Length() != 0)
						//   	{
						//			Form1->NG_BEEP(0);
   						//	}
						//}
                        //2003.05.08 E.Takase Add �R�����g��
            			break;
					default:
						break;
					}
/////////////////////////////////
					break;
				case 3:
					ACol = Form1->SGr_vSOKU_SOZAI->Col;
					ARow = Form1->SGr_vSOKU_SOZAI->Row;
					iRowCount = Form1->SGr_vSOKU_SOZAI->RowCount;
					iRow = Form1->SGr_vSOKU_SOZAI->Row;
					iCol = Form1->SGr_vSOKU_SOZAI->Col;
                //�A�������o�͂Ŗ���O���t��`�悷���PC�̓��삪�s����ɂȂ�̂Ń��b�N�t���O��݂��܂���
                    bCellWrite = true;
                //�L�[�{�[�h�C�x���g�ŃZ���ɓ��̓Z����҂����܂�
                    keybd_event(VK_SPACE,0,0,0);
					Form1->SGr_vSOKU_SOZAI->Cells[iCol][iRow] = Form1->sCommBuff;
                    Form1->SGr_vSOKU_SOZAIComPress();
                    bCellWrite = false;
                    keybd_event(VK_RETURN,0,0,0);
					strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].DISP_RESULT,Form1->SGr_vSOKU_SOZAI->Cells[iCol][iRow].c_str());
					/////////////////////////////////
                    iKIKA_KIND = 1;		//�f�t�H���g�͏㉺���Ŕ���
            		if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+ARow].KIKA_TYPE) == 1)
                    {
            			if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+ARow].KIKA_KIND) == 2)
			            {
            				iKIKA_KIND = 2;
			            }
            			else if(AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRowCount+ARow].KIKA_KIND) == 3)
			            {
            				iKIKA_KIND = 3;
			            }
            		}
					//�`���C����炵�܂�
					iRow = Form1->SGr_vSOKU_SOZAI->RowCount;
					dMAX= pCELLINFO_SOKU_SOZAI[ACol*iRow+ARow].MAX;
                    dMIN= pCELLINFO_SOKU_SOZAI[ACol*iRow+ARow].MIN;
			        switch (AnsiString(pCELLINFO_SOKU_SOZAI[ACol*iRow+ARow].KIKA_TYPE).ToIntDef(0))
					{
			        case 1:
					case 2:
                    	//2003.05.08 E.Takase Add��
                        bRtn = Form1->ConvDoubleDefS(AnsiString(Form1->sCommBuff),"0.00",AnsiString(Form1->sCommBuff),&sBufConv);
                        if ( bRtn ) {
    						switch( iKIKA_KIND )
	    					{
		    				case 2:
	                        	if( Form1->ConvDoubleDefD(AnsiString(Form1->sCommBuff),0.0) <= dMAX  )
    	                    	{
                             	    Synchronize(OK_BEEP);
            	            	}
                	    	    else
                        		{
                             	    Synchronize(NG_BEEP);
                        		}
                                break;
				    		case 3:
	                        	if( Form1->ConvDoubleDefD(AnsiString(Form1->sCommBuff),0.0) >= dMIN )
    	                    	{
                             	    Synchronize(OK_BEEP);
                	        	}
                    	    	else
                        		{
                             	    Synchronize(NG_BEEP);
                        		}
                                break;
                            default:
	                    	    if( Form1->ConvDoubleDefD(AnsiString(Form1->sCommBuff),0.0) <= dMAX
                                &&  Form1->ConvDoubleDefD(AnsiString(Form1->sCommBuff),0.0) >= dMIN )
        	                	{
                             	    Synchronize(OK_BEEP);
                	        	}
                    	    	else
                        		{
                              	    Synchronize(NG_BEEP);
	                    	    }
						    }
                        } else {
							if(AnsiString(Form1->sCommBuff).Length() != 0)
							{
                             	Synchronize(NG_BEEP);
							}
                        }
                        //2003.05.08 E.Takase Add��
                        //2003.05.08 E.Takase Add �R�����g��
						//try {
						//		if((dMIN > AnsiString(Form1->sCommBuff).ToDouble()) || (dMAX < AnsiString(Form1->sCommBuff).ToDouble()))
	   					//	{
						//		Form1->NG_BEEP(0);
						//	}
						//	else
						//	{
						//		Form1->OK_BEEP(0);
						//	}
        			    //}
						//catch(EConvertError& e){
						//	if(AnsiString(Form1->sCommBuff).Length() != 0)
						//	{
						//		Form1->NG_BEEP(0);
						//	}
						//}
						//catch(...){
						//	if(AnsiString(Form1->sCommBuff).Length() != 0)
						//   	{
						//			Form1->NG_BEEP(0);
   						//	}
						//}
                        //2003.05.08 E.Takase Add �R�����g��
            			break;
					default:
						break;
					}
/////////////////////////////////
					break;
				case 4:
					ACol = Form1->SGr_vRIRE_SOZAI->Col;
					ARow = Form1->SGr_vRIRE_SOZAI->Row;
					iRowCount = Form1->SGr_vRIRE_SOZAI->RowCount;
					iRow = Form1->SGr_vRIRE_SOZAI->Row;
					iCol = Form1->SGr_vRIRE_SOZAI->Col;
                //�A�������o�͂Ŗ���O���t��`�悷���PC�̓��삪�s����ɂȂ�̂Ń��b�N�t���O��݂��܂���
                    bCellWrite = true;
                //�L�[�{�[�h�C�x���g�ŃZ���ɓ��̓Z����҂����܂�
                    keybd_event(VK_SPACE,0,0,0);
					Form1->SGr_vRIRE_SOZAI->Cells[iCol][iRow] = Form1->sCommBuff;
                    Form1->SGr_vRIRE_SOZAIComPress();
                    bCellWrite = false;
                    keybd_event(VK_RETURN,0,0,0);
					strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].DISP_RESULT,Form1->SGr_vRIRE_SOZAI->Cells[iCol][iRow].c_str());
					/////////////////////////////////
                    iKIKA_KIND = 1;		//�f�t�H���g�͏㉺���Ŕ���
            		if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+ARow].KIKA_TYPE) == 1)
                    {
            			if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+ARow].KIKA_KIND) == 2)
			            {
            				iKIKA_KIND = 2;
			            }
            			else if(AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRowCount+ARow].KIKA_KIND) == 3)
			            {
            				iKIKA_KIND = 3;
			            }
            		}
					//�`���C����炵�܂�
					dMAX= pCELLINFO_RIRE_SOZAI[ACol*iRow+ARow].MAX;
                    dMIN= pCELLINFO_RIRE_SOZAI[ACol*iRow+ARow].MIN;
					iRow = Form1->SGr_vRIRE_SOZAI->RowCount;
			        switch (AnsiString(pCELLINFO_RIRE_SOZAI[ACol*iRow+ARow].KIKA_TYPE).ToIntDef(0))
					{
			        case 1:
					case 2:
                    	//2003.05.08 E.Takase Add��
                        bRtn = Form1->ConvDoubleDefS(AnsiString(Form1->sCommBuff),"0.00",AnsiString(Form1->sCommBuff),&sBufConv);
                        if ( bRtn ) {
    						switch( iKIKA_KIND )
	    					{
		    				case 2:
	                        	if( Form1->ConvDoubleDefD(AnsiString(Form1->sCommBuff),0.0) <= dMAX  )
    	                    	{
                             	    Synchronize(OK_BEEP);
            	            	}
                	    	    else
                        		{
                             	    Synchronize(NG_BEEP);
                        		}
                                break;
				    		case 3:
	                        	if( Form1->ConvDoubleDefD(AnsiString(Form1->sCommBuff),0.0) >= dMIN )
    	                    	{
                             	    Synchronize(OK_BEEP);
                	        	}
                    	    	else
                        		{
                             	    Synchronize(NG_BEEP);
                        		}
                                break;
                            default:
	                    	    if( Form1->ConvDoubleDefD(AnsiString(Form1->sCommBuff),0.0) <= dMAX
                                &&  Form1->ConvDoubleDefD(AnsiString(Form1->sCommBuff),0.0) >= dMIN )
        	                	{
                             	    Synchronize(OK_BEEP);
                	        	}
                    	    	else
                        		{
                              	    Synchronize(NG_BEEP);
	                    	    }
						    }
                        } else {
							if(AnsiString(Form1->sCommBuff).Length() != 0)
							{
                             	Synchronize(NG_BEEP);
							}
                        }
                        //2003.05.08 E.Takase Add��
                        //2003.05.08 E.Takase Add �R�����g��
						//try {
						//		if((dMIN > AnsiString(Form1->sCommBuff).ToDouble()) || (dMAX < AnsiString(Form1->sCommBuff).ToDouble()))
	   					//	{
						//		Form1->NG_BEEP(0);
						//	}
						//	else
						//	{
						//		Form1->OK_BEEP(0);
						//	}
        			    //}
						//catch(EConvertError& e){
						//	if(AnsiString(Form1->sCommBuff).Length() != 0)
						//	{
						//		Form1->NG_BEEP(0);
						//	}
						//}
						//catch(...){
						//	if(AnsiString(Form1->sCommBuff).Length() != 0)
						//   	{
						//		   Form1->	NG_BEEP(0);
   						//	}
						//}
                        //2003.05.08 E.Takase Add �R�����g��
            			break;
					default:
						break;
					}
/////////////////////////////////
					break;
				case 5:
                    keybd_event(VK_SPACE,0,0,0);
					iRowCount = Form7->SGr_vSOKUTEI->RowCount;
					iRow = Form7->SGr_vSOKUTEI->Row;
                    Form7->SGr_vSOKUTEI->Cells[1][iRow] = Form1->sCommBuff;
/*
                    for(i1=1;i1 <= Form1->sCommBuff.Trim().Length(); i1++)
                    {
                        //if(Form1->sCommBuff.SubString(i1,1).c_str() != " ")
                        //{
                            strcpy(c2 , (Form1->sCommBuff.Trim().SubString(i1,1).c_str()));
                            keybd_event((byte)c2[0],0,0,0);
                        //}
                    }
*/
                    //Form7->SGr_vSOKUTEI->SetFocus();
                    //Form7->SGr_vSOKUTEISelectCell(Form7->SGr_vSOKUTEI,1,iRow,true);
                    keybd_event(VK_RETURN,0,0,0);
					break;
				default:
					break;
				}
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
//Synchronize�R�}���h�����s�����邽�߃_�~�[�֐���݂��܂���
void __fastcall CommThread::NG_BEEP(void)
{
	//Form1->NG_BEEP(0);
}

void __fastcall CommThread::OK_BEEP(void)
{
	//Form1->OK_BEEP(0);
}


