//---------------------------------------------------------------------------
//
//  ThreadSozaiMain.cpp
//    �y�o�׌����V�X�e���|�f�ޓǂݎ�胁�C���z
//    ���C���t�H�[���iTForm1�N���X�j�̃����o�֐��̒�`
//
//  �쐬��
//    �s��@�a�O
//
//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <Clipbrd.hpp>
#pragma hdrstop

#include "ThreadSozaiMain.h"
#include "ThreadSozaiRire.h"
#include "Tkss01.h"               
#include "Unit1.h"
#include "Unit8.h"
#include "UnitDataAccess.h"
#pragma package(smart_init)
// k.y 2003.05.17
//extern HANDLE hSOZAI_OR_DATA;

// k.y 2003.05.17
//extern KSM02_DATA *pSOZAI_OR_DATA;         // �f�ނ̂n�q�f�[�^
extern KSM02_DATA pSOZAI_OR_DATA[100];

// k.y 2003.05.17
//extern HANDLE hKSM01_DATA;

// k.y 2003.05.17
//extern KSM01_DATA *pKSM01_DATA;				//���i�K�i�}�X�^�[
extern KSM01_DATA pKSM01_DATA;
extern int iDEBUG;
extern bool bLOTCHANGE;						//���b�g���蓖�ĉ�ʂƂ̒ʐM�p�t���O

// k.y 2003.05.17
//HANDLE hSOZAI_OR_DATA2;
// k.y 2003.05.17
//KSM02_DATA *pSOZAI_OR_DATA2;        // �f�ނ̂n�q�f�[�^�i�f�ރ��C���ō쐬�j
KSM02_DATA pSOZAI_OR_DATA2[100];

// k.y 2003.05.17
//HANDLE hSOZAI_SYKA_DATA;

// k.y 2003.05.17
//KSM02_DATA *pSOZAI_SYKA_DATA;
KSM02_DATA pSOZAI_SYKA_DATA[100];

// k.y 2003.05.17
//HANDLE hSOZAI_RIRE_DATA;
// k.y 2003.05.17
//KSD02_DATA *pSOZAI_RIRE_DATA;
KSD02_DATA pSOZAI_RIRE_DATA[100];

// k.y 2003.05.17
//HANDLE hSOZAI_RIRE_LOT;

// k.y 2003.05.17
//KSD01_DATA *pSOZAI_RIRE_LOT;
KSD01_DATA pSOZAI_RIRE_LOT[100];

// k.y 2003.05.17
//extern HANDLE	   hTEMPORDATA;

// k.y 2003.05.17
//extern KSM02_DATA  *pTEMPORDATA;
extern KSM02_DATA  pTEMPORDATA[100];

extern int iSOZAI_KOMKCNT;
extern int iSOZAI_CONT_CONT;
extern int iSOZAI_RIRE_LOT;
extern int iSOZAI_ORCNT;
extern int iSOZAI_SOKUCNT;													//�\�[�g���g�p����d�݌v�Z�p�o�b�t�@
extern HANDLE hSOKU_KSD01_DATA;
extern KSD01_DATA *pSOKU_KSD01_DATA;
extern HANDLE hRIRE_KSD01_DATA;
extern KSD01_DATA *pRIRE_KSD01_DATA;
	int iRow,i1,i2,i3,i4;
    //int iRIRE_CNT;
    int iKOMK_CNT;
    int iKOMK_NUM;
    int iSOKU_SU;
    int iLOT_CNT;
    int iPanelNum,iKikiNum,iSokuGoukei;
    int iPutKiki;
    int iSyukaWait,iRireWait;
    int iCel;
	int iSOZAI_SYKA_KOMKCNT;
	int iSOZAI_RIRE_KOMKCNT;
	int iSOZAI_SYKACNT;
	int iSOZAI_RIRECNT;
  	int iSOZAI_ORCNT2;
	int	iSOZAI_KOMKCNT2;
    int iSYKAWAIT,iRIREWAIT;
    int iSOZAI_RireCnt,iSOZAI_SyukaCnt,iSOZAI_SokuCnt,iSOZAI_ContCnt,iSOZAI_KikiCnt;
//���I�p�l�����i�f�ޗp�j
    int iPnl_SOZAI_InsNoCnt;
    int iPnl_SOZAI_InsNameCnt;
    int iPnl_SOZAI_InsKikiNameCnt;
    int iPnl_SOZAI_InsSubBaseCnt;
    int iSOZAI_RecordCount;
    int iSOZAI_SokuSuu;
    int iSOZAI_KikiCount;
    int iSOZAI_RotCount;                  //���̓��b�g��
extern    int iSOZAI_DEL_OrCnt;                     //Or�\����
extern    int iSOZAI_DEL_SokuCnt;                     //Or�\����

/* k.k 2003.05.17 DELETE
__fastcall ThreadSozaiMain::ThreadSozaiMain(bool CreateSuspended)
	: TThread(CreateSuspended)
{
  Priority = tpIdle;
}
//---------------------------------------------------------------------------
//�f�ނ̕\��
//---------------------------------------------------------------------------
void __fastcall ThreadSozaiMain::Execute()
{
//	Synchronize(SOZAI_PROCESS);
	SOZAI_PROCESS();

    // �����I���t���O
    Form1->bNowF7 = false;

	if( Terminated ) return;
}
*/
//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�ޓǂݎ�胁�C���B
//
//  �@�\����
//    �f�ނ�ǂݎ�邽�߂̂n�q�e�[�u�����쐬����B
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
void __fastcall TForm1::SOZAI_PROCESS(void)
{
	AnsiString sBuf,sLot,sTempBuf,sTempLot;
    bool bSOZAI_LOT;                        //�f�ރ��b�g�w���L��^�����t���O
    int iRow,iRowCount;
//�f�ޓǂݎ�莞�g�p���郁�����̊m��
    memset(pSOZAI_OR_DATA2,0x00,sizeof(pSOZAI_OR_DATA2));
    memset(pSOZAI_RIRE_LOT,0x00,sizeof(pSOZAI_RIRE_LOT));
    memset(&pSOZAI_SYKA_DATA,(int)NULL,sizeof(pSOZAI_SYKA_DATA));
    memset(pSOZAI_RIRE_DATA,0x00,sizeof(pSOZAI_RIRE_DATA));
    if(bNowF7 == true)      //�����L�[�ł̌�����
    {
    	iSOZAI_SYKA_KOMKCNT = 0;
	    iSOZAI_RIRE_KOMKCNT = 0;
    	iSOZAI_SYKACNT		= 0;
	    iSOZAI_RIRECNT		= 0;
      	iSOZAI_ORCNT		= 0;
  	    iSOZAI_ORCNT2		= 0;
    	iSOZAI_KOMKCNT2		= 0;
        iTHREAD_CNT			= 0;

        // 2003/11/18 A.Tamura �}�X�^�[KSM02�𒆐S�ɑf�ރf�[�^OR���쐬���Ă��܂�
        //                     �ł����A���̂܂܂��ƁA
        //                     ��ʂɕ\�����������b�g������ς݂݂̂̏ꍇ�A
        //                     [����ς݃��b�g�̑f�ޗp�i��]��
        //                     [�}�X�^�[�ɓo�^����Ă���f�ޗp�i��]��
        //                     �قȂ��
        //                     [�}�X�^�[�ɓo�^����Ă���f�ޗp�i��]��
        //                     ���荀��(����s)���y����\�ȃZ���S�Ė����z��
        //                     �\�������̂ňȉ��̊֐����̏������������܂����B  �����̃o�O�́A2003/11/17����!!
        //                     �@�\�����悤�Ƃ��Ă��郍�b�g���S�đ���ς݂��ǂ������f
        //                     �A�V�K���b�g���܂�ł���ꍇ�́AKSM02(���荀��)�𒆐S�Ƃ����������s�Ȃ��B
        //                     �B�S�đ���ς݃��b�g�̏ꍇ�́A����Grid��ԍ��̃��b�g(���荀��)�𒆐S�ɏ������s�Ȃ��B
        //                     �����S�ƂȂ鑪�荀�ڂ͂����܂ŏ����̎n�܂��
        //                     �@�Ȍ�AOR�f�[�^�쐬�Ŗ��ߐs������܂�
        //
    	//�}�X�^�[�f�[�^��ǂݎ��܂�
        GET_SOZAI_KSM02();

        iLOT_CNT    = 0;
        Form1->iSOZAI_RIREKI_KOMKCNT = 0;
	//2003.05.12 E.Takase Add��
	//if(Form1->bNowRIRE == true)

		//�ߋ��ɑ��肵�����ǂ����𒲂ׂ܂�
    	//���������Ă���Γǂݎ��܂�
        GET_SOZAI_KSD01();
        GET_SOZAI_KSD02();
        if(Form1->iRIRE_CNT != 0)
    	//2003.05.12 E.Takase Add��
	    {
            SGr_vRIRE_SOZAI->Visible = true;
    	}
        else
        {
            SGr_vRIRE_SOZAI->Visible = false;
        }
        iSOZAI_SYKACNT 	= 0;
        iSOZAI_RIRECNT 	= 0;
        iSOZAI_ORCNT 	= 0;


    	// 2003/10/20 A.Tamura ��r�����ɒP�ʂ�ǉ����܂��i�O��̊֌W���C���ς݁j
    	//                     KSM02�Ƀu���V����[mm][Cpk]���������ɁA
    	//                     KSD02�ɂ��̂Q������Ɛ������\������Ȃ��G���[�����
    	AnsiString KOMK_NM,KOMK_SUB,TANI,HINBAN_SK;
        AnsiString KIKI_NO,KOMK_NO,SOKU_SU;
    //�f�ޗp�̂n�q�e�[�u�����쐬���܂�
        for(i1 = 0;i1 < iSOZAI_SYKA_KOMKCNT;i1++)
        {
        	KOMK_NM   = pSOZAI_SYKA_DATA[i1].KOMK_NM;
            KOMK_SUB  = pSOZAI_SYKA_DATA[i1].KOMK_SUB;
            TANI      = pSOZAI_SYKA_DATA[i1].TANI;
            HINBAN_SK = pSOZAI_SYKA_DATA[i1].HINBAN_SK;
            KOMK_NO = AnsiString(pSOZAI_SYKA_DATA[i1].KOMK_NO).ToIntDef(0);
            KIKI_NO = AnsiString(pSOZAI_SYKA_DATA[i1].KIKI_NO).ToIntDef(0);
            SOKU_SU = AnsiString(pSOZAI_SYKA_DATA[i1].SOKU_SU).ToIntDef(0);
            for( i2 = 0;i2 < iSOZAI_RIRE_KOMKCNT ; i2++)
            {
                //�}�X�^�[�Ɨ����̍ő吔���r���傫���ق����n�q�e�[�u���ɑ�����܂��B
            	if(AnsiString(pSOZAI_RIRE_DATA[i2].KIKI_NO).ToIntDef(0) != 9999)
                {
                    if((KOMK_NO.ToIntDef(0) == AnsiString(pSOZAI_RIRE_DATA[i2].KOMK_NO).ToIntDef(0))
                    && (KIKI_NO.ToIntDef(0) == AnsiString(pSOZAI_RIRE_DATA[i2].KIKI_NO).ToIntDef(0))
                    && (KOMK_NM 			== AnsiString(pSOZAI_RIRE_DATA[i2].KOMK_NM))
                	&& (KOMK_SUB	 		== AnsiString(pSOZAI_RIRE_DATA[i2].KOMK_SUB))
                	&& (TANI	 			== AnsiString(pSOZAI_RIRE_DATA[i2].TANI))
                    // 2003/11/24 A.Tamura �e�X�g�I�ɃR�����g
                    && (HINBAN_SK 			== AnsiString(pSOZAI_RIRE_DATA[i2].HINBAN_SK)))
                    {
                    	if(SOKU_SU.ToIntDef(0) <  AnsiString(pSOZAI_RIRE_DATA[i2].SOKU_SU).ToIntDef(0))
                        {
                        	SOKU_SU = AnsiString(pSOZAI_RIRE_DATA[i2].SOKU_SU).ToIntDef(0);
                        }
                        strcpy(pSOZAI_RIRE_DATA[i2].KIKI_NO,"9999");
                    }
                }
            }
            strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].KIKI_NO	,KIKI_NO.c_str());
            strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].KOMK_NM	,KOMK_NM.c_str());
            strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].KOMK_NO	,KOMK_NO.c_str());
            strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].KOMK_SUB	,KOMK_SUB.c_str());
            strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].TANI		,TANI.c_str());
            strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].SOKU_SU	,SOKU_SU.c_str());
            strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].HINBAN_SK	,HINBAN_SK.c_str());
            iSOZAI_ORCNT++;
        }
        for( i1 = 0;i1 < iSOZAI_RIRE_KOMKCNT ; i1++)
        {
        	if(AnsiString(pSOZAI_RIRE_DATA[i1].KIKI_NO).ToIntDef(0) != 9999)
            {
            	KOMK_NM   = pSOZAI_RIRE_DATA[i1].KOMK_NM;
                KOMK_SUB  = pSOZAI_RIRE_DATA[i1].KOMK_SUB;
                TANI      = pSOZAI_RIRE_DATA[i1].TANI;
                HINBAN_SK = pSOZAI_RIRE_DATA[i1].HINBAN_SK;
                KOMK_NO = AnsiString(pSOZAI_RIRE_DATA[i1].KOMK_NO).ToIntDef(0);
                KIKI_NO = AnsiString(pSOZAI_RIRE_DATA[i1].KIKI_NO).ToIntDef(0);
                SOKU_SU = AnsiString(pSOZAI_RIRE_DATA[i1].SOKU_SU).ToIntDef(0);

                strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].KIKI_NO	,KIKI_NO.c_str());
                strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].KOMK_NM	,KOMK_NM.c_str());
                strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].KOMK_NO	,KOMK_NO.c_str());
                strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].KOMK_SUB	,KOMK_SUB.c_str());
                strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].TANI		,TANI.c_str());
                strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].SOKU_SU	,SOKU_SU.c_str());
                strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].HINBAN_SK	,HINBAN_SK.c_str());
                iSOZAI_ORCNT++;
            }
        }


// ---------------------------------------------------------
//���݂̏o�חp�̍��ڂƑ�����т̍��ڂ̍ő吔��OR��ʃ�������֊i�[
//������ѓǂݎ��
//���o���b�g�̂�����MAX�l�̒��o

        memset(pSOZAI_RIRE_DATA,0x00,sizeof(pSOZAI_RIRE_DATA));


//    if( Form1->iRIRE_CNT > 0 )          //�ߋ�������0���łȂ����
    	iSOZAI_KOMKCNT2 = 0;
        if( Form1->iRIRE_CNT > 0 )          //���b�g�������
        {
        	GET_SOZAI_KSD02_SECOND();
        }
        memset(pSOZAI_OR_DATA,0x00,sizeof(pSOZAI_OR_DATA));

//���݂̏o�חp�̍��ڂƉߋ������̍��ڂ̍ő吔��OR��ʃ�������֊i�[
        iSOZAI_RIRECNT 	= 0;
        iSOZAI_SYKACNT 	= 0;
        iSOZAI_ORCNT2 	= 0;

        for(i1 = 0;i1 < iSOZAI_ORCNT;i1++)
        {
        	KOMK_NM   = pSOZAI_OR_DATA2[i1].KOMK_NM;
            KOMK_SUB  = pSOZAI_OR_DATA2[i1].KOMK_SUB;
            TANI      = pSOZAI_OR_DATA2[i1].TANI;
            HINBAN_SK = pSOZAI_OR_DATA2[i1].HINBAN_SK;
            KOMK_NO = AnsiString(pSOZAI_OR_DATA2[i1].KOMK_NO).ToIntDef(0);
            KIKI_NO = AnsiString(pSOZAI_OR_DATA2[i1].KIKI_NO).ToIntDef(0);
            SOKU_SU = AnsiString(pSOZAI_OR_DATA2[i1].SOKU_SU).ToIntDef(0);
            for( i2 = 0;i2 < iSOZAI_KOMKCNT2 ; i2++)
            {
            	if(AnsiString(pSOZAI_RIRE_DATA[i2].KIKI_NO).ToIntDef(0) != 9999)
                {
/*
    	        	if((KOMK_NM 			== AnsiString(pRIREKI_DATA[i2].KOMK_NM))
        	        &&(KOMK_SUB 			== AnsiString(pRIREKI_DATA[i2].KOMK_SUB))
        	        &&(TANI 				== AnsiString(pRIREKI_DATA[i2].TANI))
            	    &&(KOMK_NO.ToIntDef(0) 	== AnsiString(pRIREKI_DATA[i2].KOMK_NO).ToIntDef(0))
                	&&(KIKI_NO.ToIntDef(0) 	== AnsiString(pRIREKI_DATA[i2].KIKI_NO).ToIntDef(0)))
*/
                    if((KOMK_NO.ToIntDef(0) == AnsiString(pSOZAI_RIRE_DATA[i2].KOMK_NO).ToIntDef(0))
                    && (KIKI_NO.ToIntDef(0) == AnsiString(pSOZAI_RIRE_DATA[i2].KIKI_NO).ToIntDef(0))
                    && (KOMK_NM 			== AnsiString(pSOZAI_RIRE_DATA[i2].KOMK_NM))
                    && (KOMK_SUB 			== AnsiString(pSOZAI_RIRE_DATA[i2].KOMK_SUB))
                    && (TANI 				== AnsiString(pSOZAI_RIRE_DATA[i2].TANI))
                    // 2003/11/24 A.Tamura �e�X�g�I�ɃR�����g
                    && (HINBAN_SK 			== AnsiString(pSOZAI_RIRE_DATA[i2].HINBAN_SK)))
	    			{
                    	if(SOKU_SU.ToIntDef(0) <  AnsiString(pSOZAI_RIRE_DATA[i2].SOKU_SU).ToIntDef(0))
                        {
                    	SOKU_SU = AnsiString(pSOZAI_RIRE_DATA[i2].SOKU_SU).ToIntDef(0);
                        }
                        strcpy(pSOZAI_RIRE_DATA[i2].KIKI_NO,"9999");
                    }
                }
            }
            strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].KIKI_NO	,KIKI_NO.c_str());
            strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].KOMK_NM	,KOMK_NM.c_str());
            strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].KOMK_NO	,KOMK_NO.c_str());
            strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].KOMK_SUB	,KOMK_SUB.c_str());
            strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].TANI		,TANI.c_str());
            strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].SOKU_SU	,SOKU_SU.c_str());
            strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].HINBAN_SK	,HINBAN_SK.c_str());
            iSOZAI_ORCNT2++;
        }
        for( i1 = 0;i1 < iSOZAI_KOMKCNT2 ; i1++)
        {
    	    if(AnsiString(pSOZAI_RIRE_DATA[i1].KIKI_NO).ToIntDef(0) != 9999)
            {
            	KOMK_NM   = pSOZAI_RIRE_DATA[i1].KOMK_NM;
                KOMK_SUB  = pSOZAI_RIRE_DATA[i1].KOMK_SUB;
                TANI      = pSOZAI_RIRE_DATA[i1].TANI;
                HINBAN_SK = pSOZAI_RIRE_DATA[i1].HINBAN_SK;
                KOMK_NO = AnsiString(pSOZAI_RIRE_DATA[i1].KOMK_NO).ToIntDef(0);
                KIKI_NO = AnsiString(pSOZAI_RIRE_DATA[i1].KIKI_NO).ToIntDef(0);
                SOKU_SU = AnsiString(pSOZAI_RIRE_DATA[i1].SOKU_SU).ToIntDef(0);

                strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].KIKI_NO	,KIKI_NO.c_str());
                strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].KOMK_NM	,KOMK_NM.c_str());
                strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].KOMK_NO	,KOMK_NO.c_str());
                strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].KOMK_SUB	,KOMK_SUB.c_str());
                strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].TANI		,TANI.c_str());
                strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].SOKU_SU	,SOKU_SU.c_str());
                strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].HINBAN_SK	,HINBAN_SK.c_str());
                iSOZAI_ORCNT2++;
            }
        }
    	iSOZAI_ORCNT = iSOZAI_ORCNT2;

    	//�n�q�e�[�u�������������̂ŒP�ʂȂǂ̏���ǂݍ��݂܂��B
    	// 2003/10/20 A.Tamura �R�����g�����ǉ����܂�
    	//                     �u���������n�q�e�[�u���̃\�[�g�v��
    	//                     �u�K�i�\���ɕK�v�ȓ��I�R���g���[���̍쐬�v�����̒��ōs�Ȃ��Ă���
        GET_SOZAI_TANI();
    }

	Form1->bLOT_LINK = true;
//	Synchronize(GET_SOZAI_TANI);
//	Synchronize(SetSYKA_Sozai);
//	GET_SOZAI_TANI();
    //�f�ޏo�דǂݎ����s���܂��B
	SetSYKA_Sozai();
    //�f�ޗ���ǂݎ����s���܂��B
    SetRIRE_Sozai();

    //�f�[�^�ǂݎ���Ƀ��b�g���蓖�ĉ�ʂ�\�����邩�̃t���O���쐬���܂��B
	if(bNowLotF7 == false )
	{
		if(Form1->iRIRE_CNT != 0)
		{
			//2003.05.12 E.Takase Add��
            //����ǂݎ��w��������A���𐔂��O�łȂ����͗����f�[�^�̌������s���܂�
			if(Form1->bNowRIRE == true && Form1->iRIRE_CNT != 0)
			//2003.05.12 E.Takase Add��
			{
 				for( i1 = 0;i1 < Form1->iRIRE_CNT ;i1++)
				{
					if(Form1->SGr_tRIRE->Cells[i1][0].Trim().Length() != 0 )
					{
                        bSOZAI_LOT = false;
                        iRowCount = Form1->SGr_vRIRE_SOZAI->RowCount;
                        for(iRow = 1;iRow < iRowCount ; iRow++)
                        {
                            //�����̎w�������邩�ǂ����̔���
                            if(AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iRow].KOMK_NO).ToIntDef(0) != -999 )
                            {
                                bSOZAI_NASI = false;
                                //�����̎w�����������̂Ń��b�g�̎w�����m�F���܂�
                                bSOZAI_LOT = true;
                                break;
                            }
                        }
                        if( bSOZAI_LOT == true )        //�f�ރ��b�g�̎w���������
                        {
                            //���b�g�����N���m�F���܂�
						    if(AnsiString(pRIRE_KSD01_DATA[i1].LOT_LINK_SZ).ToIntDef(0) == 0)
						    {
       						    Form1->bLOT_LINK = false;
							    break;
						    }
                        }
					}
			    }
			}
    	}
		for( i1 = 0;i1 < Form1->SGr_tSOKU->ColCount;i1++)
		{
			if(Form1->SGr_tSOKU->Cells[i1][0].Trim().Length() != 0 )
			{
    	    	while(!hSOKU_KSD01_DATA){}
                bSOZAI_LOT = false;
                iRowCount = Form1->SGr_vSOKU_SOZAI->RowCount;
                for(iRow = 1;iRow < iRowCount ; iRow++)
                {
                    if(AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iRow].KOMK_NO).ToIntDef(0) != -999 )
                    {
                        bSOZAI_NASI = false;
                        bSOZAI_LOT = true;
                        break;
                    }
                }
                if( bSOZAI_LOT == true )
                {
				    if(AnsiString(pSOKU_KSD01_DATA[i1].LOT_LINK_SZ).ToIntDef(0) == 0)
				    {
       				    Form1->bLOT_LINK = false;
				    	break;
				    }
                }
			}
	    }
	}
	Form1->SGr_vRIRE_SOZAI->Refresh();
	Form1->SGr_vSOKU_SOZAI->Refresh();
//    bLOT_LINK = true;
    bLOTCHANGE = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PLOT_FORM8(void)
{
	Form8->ShowModal();
}
//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�FKSM02��ǂݎ��܂��B
//
//  �@�\����
//    �}�X�^�[�f�[�^��ǂݍ��݃}�X�^�[�o�b�t�@�ɒl�������܂��B
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
void __fastcall TForm1::GET_SOZAI_KSM02(void)
{
	int i1;
	AnsiString  sDTKSHIN,sBuf;

    // 2003/11/18 A.Tamura ���X���̏����́AKSM02����݂̂̃f�[�^�擾�ł����A
    //                     ���̂܂܂��ƁA���̊֐��𔲂����ȍ~�̏�����
    //                     �}�X�^�[KSM02�𒆐S�ɑf�ރf�[�^OR���쐬���Ă��܂���
    //                     ��ʂɕ\�����������b�g������ς݂݂̂̏ꍇ�A
    //                     [����ς݃��b�g�̑f�ޗp�i��]��
    //                     [�}�X�^�[�ɓo�^����Ă���f�ޗp�i��]��
    //                     �قȂ��
    //                     [�}�X�^�[�ɓo�^����Ă���f�ޗp�i��]��
    //                     ���荀��(����s)���y����\�ȃZ���S�Ė����z��
    //                     �\�������̂ňȉ��̏������������܂����B  �����̃o�O�́A2003/11/17����!!
    //                     �@�\�����悤�Ƃ��Ă��郍�b�g���S�đ���ς݂��ǂ������f
    //                     �A�V�K���b�g���܂�ł���ꍇ�́AKSM02(���荀��)�𒆐S�Ƃ����������s�Ȃ��B
    //                     �B�S�đ���ς݃��b�g�̏ꍇ�́A����Grid��ԍ��̃��b�g(���荀��)�𒆐S�ɏ������s�Ȃ��B
    //                     �����S�ƂȂ鑪�荀�ڂ͂����܂ŏ����̎n�܂��
    //                     �@�Ȍ�AOR�f�[�^�쐬�Ŗ��ߐs������܂�
    //
    //                     �����̊֐��ł́A[KSM02(���荀��)]����Ǎ��ނ�
    //                     �@[����Grid��ԍ��̃��b�g(���荀��)]����Ǎ��ނ��𔻒f����
    //                     �@���S���荀�ڂ����肵�܂��B
    AnsiString	sLot;
	int 		iCol;
    bool		bUseKSD01;
    AnsiString	sDTKSHIN1_SZ,sDTKSHIN2_SZ,sDTKSHIN3_SZ,sDTKSHIN4_SZ,sDTKSHIN5_SZ,sDTKSHIN6_SZ;
    AnsiString sLot_Where;

    sLot = "";
    for(iCol = 0 ; iCol < Form1->SGr_tSOKU->ColCount ; iCol++)
	{
		if(  Form1->SGr_tSOKU->Cells[iCol][0].Trim().Length() != 0 )
		{
	    	sLot += "'" + Form1->SGr_tSOKU->Cells[iCol][0] + "',";
		}
	}
    sLot = sLot.SubString(1,sLot.Length()-1);

    ///////////////////////////////////////////////////////////////onishi��
    // ���b�g��������������
    sLot_Where = "";
    for(iCol = 0 ; iCol < Form1->SGr_tSOKU->ColCount ; iCol++)
	{
		if(  Form1->SGr_tSOKU->Cells[iCol][0].Trim().Length() != 0 )
		{
            sLot_Where += "( LOTNO='" + Form1->SGr_tSOKU->Cells[iCol][0] + "' AND ";
            sLot_Where += " HINBAN='" + Form1->SGr_tSOKU->Cells[iCol][1] + "') OR ";
		}
	}
    sLot_Where = sLot_Where.SubString(1,sLot_Where.Length()-3);
    ///////////////////////////////////////////////////////////////onishi��

    sBuf = "SELECT * FROM KSD01 WHERE DTKSHIN = '" + Form1->sNowDTKSHIN + "'";
    //sBuf += " AND LOTNO IN (" + sLot + ")";
    sBuf += " AND (";
    sBuf += sLot_Where;
    sBuf += " )";

	// Initial Query
    Form1->Query3->Close();
    Form1->Query3->SQL->Clear();
    Form1->Query3->SQL->Add(sBuf);
    Form1->Query3->Open();
    Form1->Query3->Active = true;

    // �����������b�g���ƌ������ʂ̃��b�g�����Ⴆ�Ζ����胍�b�g���܂܂�Ă���Ɣ��f����
    iCol = 0;
	while(Form1->Query3->Eof == false)
	{
		if(VarIsNull(Form1->Query3->FieldValues["LOTNO"])!=true)
       	{
		    iCol++ ;
		}
		Form1->Query3->Next();
	}

    if( iCol < Form1->SGr_tSOKU->ColCount ){
    	bUseKSD01 = false;
    }
    else {
    	bUseKSD01 = true;

		Form1->Query3->First();

        sLot = Form1->Query3->FieldValues["LOTNO"];

        sDTKSHIN1_SZ = "";
        sDTKSHIN2_SZ = "";
        sDTKSHIN3_SZ = "";
        sDTKSHIN4_SZ = "";
        sDTKSHIN5_SZ = "";
        sDTKSHIN6_SZ = "";
		if(VarIsNull(Form1->Query3->FieldValues["DTKSHIN1_SZ"])!=true) {
		    sDTKSHIN1_SZ = Form1->Query3->FieldValues["DTKSHIN1_SZ"];
		}
		if(VarIsNull(Form1->Query3->FieldValues["DTKSHIN2_SZ"])!=true) {
		    sDTKSHIN2_SZ = Form1->Query3->FieldValues["DTKSHIN2_SZ"];
		}
		if(VarIsNull(Form1->Query3->FieldValues["DTKSHIN3_SZ"])!=true) {
		    sDTKSHIN3_SZ = Form1->Query3->FieldValues["DTKSHIN3_SZ"];
		}
		if(VarIsNull(Form1->Query3->FieldValues["DTKSHIN4_SZ"])!=true) {
		    sDTKSHIN4_SZ = Form1->Query3->FieldValues["DTKSHIN4_SZ"];
		}
		if(VarIsNull(Form1->Query3->FieldValues["DTKSHIN5_SZ"])!=true) {
		    sDTKSHIN5_SZ = Form1->Query3->FieldValues["DTKSHIN5_SZ"];
		}
		if(VarIsNull(Form1->Query3->FieldValues["DTKSHIN6_SZ"])!=true) {
		    sDTKSHIN6_SZ = Form1->Query3->FieldValues["DTKSHIN6_SZ"];
		}

    }

    Form1->Query3->Close();


    iSOZAI_SYKA_KOMKCNT = 0;
//���O�ɓǂݍ���KSM01�̑f�ޗp���Ӑ�i�Ԃ�KSM02�̒��o�����ɒǉ�
	for(i1=0;i1<6;i1++)
	{
		switch( i1 )
		{
		case 0:
            if( bUseKSD01 ){
            	sDTKSHIN = sDTKSHIN1_SZ;
    		}
            else{
            	sDTKSHIN = pKSM01_DATA.DTKSHIN1_SZ;
			}
            break;
		case 1:
            if( bUseKSD01 ){
            	sDTKSHIN = sDTKSHIN2_SZ;
    		}
            else{
    			sDTKSHIN = pKSM01_DATA.DTKSHIN2_SZ;
			}
			break;
		case 2:
            if( bUseKSD01 ){
            	sDTKSHIN = sDTKSHIN3_SZ;
    		}
            else{
    			sDTKSHIN = pKSM01_DATA.DTKSHIN3_SZ;
			}
			break;
		case 3:
            if( bUseKSD01 ){
            	sDTKSHIN = sDTKSHIN4_SZ;
    		}
            else{
    			sDTKSHIN = pKSM01_DATA.DTKSHIN4_SZ;
			}
			break;
		case 4:
            if( bUseKSD01 ){
            	sDTKSHIN = sDTKSHIN5_SZ;
    		}
            else{
    			sDTKSHIN = pKSM01_DATA.DTKSHIN5_SZ;
			}
			break;
		case 5:
            if( bUseKSD01 ){
            	sDTKSHIN = sDTKSHIN6_SZ;
    		}
            else{
    			sDTKSHIN = pKSM01_DATA.DTKSHIN6_SZ;
			}
			break;
        default:
			break;
        }
		if( sDTKSHIN.Trim().Length() == 0 ) break;
//���Ӑ�i�Ԃ��L�[�ɂ��đf�ނ̍��ڐ��𒊏o����
        if( bUseKSD01 ){
        	sBuf  = "SELECT * FROM KSD02";
			sBuf += " WHERE DTKSHIN ='" + Form1->sNowDTKSHIN + "'";
			sBuf += " AND LOTNO ='" + sLot + "'";
			sBuf += " AND HINBAN_SK ='" + sDTKSHIN + "'";
    		sBuf += " AND SKB_NO = 1" ;                                      //�f�ތ�������
		}
        else {
        	sBuf  = "SELECT * FROM KSM02";
			sBuf += " WHERE DTKSHIN ='" + Form1->sNowDTKSHIN + "'";
			sBuf += " AND HINBAN_SK ='" + sDTKSHIN + "'";
			sBuf += " AND REVCNT = 0" ;
    		sBuf += " AND SKB_NO = 1" ;                                      //�f�ތ�������
        }
		sBuf += " ORDER BY KIKI_NO, KOMK_NM, KOMK_SUB, UNQ_NO";

		//For Debug
        // 2003.06.03 k.y
        if( iDEBUG == 1 )
        {
		    ClpBrd = Clipboard();
		    ClpBrd->Open();
    	    ClpBrd->SetTextBuf(sBuf.c_str());
    	    ClpBrd->Close();
        }
	// Initial Query
		Form1->Query3->Close();
		Form1->Query3->SQL->Clear();
		Form1->Query3->SQL->Add(sBuf);
		Form1->Query3->Open();
		Form1->Query3->Active = true;

//���i�K�i���ׂ̓ǂݎ��
    	while( Form1->Query3->Eof == false )
	    {
        //�i��
    	    if ( VarIsNull(Form1->Query3->FieldValues["HINBAN_SK"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["HINBAN_SK"]) != true )
	        {
        	    sBuf  	= Form1->Query3->FieldValues["HINBAN_SK"];                        	//�i�ԁi�o�׎��͂�����L�[�ɂ���j
        	    strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].HINBAN_SK  	,sBuf.c_str());
            }
        //���荀�ڂm��
    	    if ( VarIsNull(Form1->Query3->FieldValues["KOMK_NO"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_NO"]) != true )
	        {
    	        sBuf	= Form1->Query3->FieldValues["KOMK_NO"];
    	        strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KOMK_NO		,sBuf.c_str());
            }
        //���荀�ږ���
    	    if ( VarIsNull(Form1->Query3->FieldValues["KOMK_NM"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_NM"]) != true )
	        {
           		sBuf   	= Form1->Query3->FieldValues["KOMK_NM"];
	            strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KOMK_NM    	,sBuf.c_str());
            }
        //���荀�ڃT�u����
    	    if ( VarIsNull(Form1->Query3->FieldValues["KOMK_SUB"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_SUB"]) != true )
	        {
    	        sBuf = Form1->Query3->FieldValues["KOMK_SUB"];
        	    strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KOMK_SUB	,sBuf.c_str());
	        }
        //����@��m��
    	    if ( VarIsNull(Form1->Query3->FieldValues["KIKI_NO"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKI_NO"]) != true )
	        {
		        sBuf    = Form1->Query3->FieldValues["KIKI_NO"];
    		    strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KIKI_NO    ,sBuf.c_str());
	        }
        //����@�햼��
			if ( VarIsNull(Form1->Query3->FieldValues["KIKI_NM"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKI_NM"]) != true )
	        {
    	    	sBuf    = Form1->Query3->FieldValues["KIKI_NM"];
        		strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KIKI_NM    ,sBuf.c_str());
	        }
        //�P��
			if ( VarIsNull(Form1->Query3->FieldValues["TANI"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["TANI"]) != true )
        	{
	        	sBuf   	= Form1->Query3->FieldValues["TANI"];
    	    	strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].TANI       ,sBuf.c_str());
			}
        //�K�i�^�C�v
	        if ( VarIsNull(Form1->Query3->FieldValues["KIKA_TYPE"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_TYPE"]) != true )
    	    {
        		sBuf  = Form1->Query3->FieldValues["KIKA_TYPE"];
        		strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KIKA_TYPE  ,sBuf.c_str());
			}
        //�K�i���
	        if ( VarIsNull(Form1->Query3->FieldValues["KIKA_KIND"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_KIND"]) != true )
	        {
    	    	sBuf  = Form1->Query3->FieldValues["KIKA_KIND"];
        		strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KIKA_KIND  ,sBuf.c_str());
			}
        //�K�i�����_�ȉ�����
    	    if ( VarIsNull(Form1->Query3->FieldValues["KIKA_DECI"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_DECI"]) != true )
	        {
    	    	sBuf  = Form1->Query3->FieldValues["KIKA_DECI"];
        		strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KIKA_DECI  ,sBuf.c_str());
			}
        //�K�i�l�P
    	    if ( VarIsNull(Form1->Query3->FieldValues["KIKA_NUM1"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_NUM1"]) != true )
	        {
    	    	sBuf  = Form1->Query3->FieldValues["KIKA_NUM1"];
        		strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KIKA_NUM1  ,sBuf.c_str());
			}
        //�K�i�l�Q
    	    if ( VarIsNull(Form1->Query3->FieldValues["KIKA_NUM2"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_NUM2"]) != true )
	        {
    	    	sBuf  = Form1->Query3->FieldValues["KIKA_NUM2"];
        		strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KIKA_NUM2 ,sBuf.c_str());
			}
        //�K�i�l�R
    	    if ( VarIsNull(Form1->Query3->FieldValues["KIKA_NUM3"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_NUM3"]) != true )
	        {
    	    	sBuf  = Form1->Query3->FieldValues["KIKA_NUM3"];
        		strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KIKA_NUM3  ,sBuf.c_str());
			}
        //�K�i�l����
    	    if ( VarIsNull(Form1->Query3->FieldValues["KIKA_STR"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_STR"]) != true )
	        {
    	    	sBuf   = Form1->Query3->FieldValues["KIKA_STR"];
        		strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KIKA_STR   ,sBuf.c_str());
			}
        //�K�i�l�T�u�P
    	    if ( VarIsNull(Form1->Query3->FieldValues["KIKA_SUB1"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_SUB1"]) != true )
	        {
    	    	sBuf  = Form1->Query3->FieldValues["KIKA_SUB1"];
        		strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KIKA_SUB1  ,sBuf.c_str());
			}
        //�K�i�l�T�u�Q
    	    if ( VarIsNull(Form1->Query3->FieldValues["KIKA_SUB2"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_SUB2"]) != true )
        	{
		        sBuf  = Form1->Query3->FieldValues["KIKA_SUB2"];
    		    strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KIKA_SUB2  ,sBuf.c_str());
        	}
        //�K�i�l�T�u�R
			if ( VarIsNull(Form1->Query3->FieldValues["KIKA_SUB3"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_SUB3"]) != true )
    	    {
        		sBuf  = Form1->Query3->FieldValues["KIKA_SUB3"];
        		strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KIKA_SUB3  ,sBuf.c_str());
			}
        //����w������
    	    if ( VarIsNull(Form1->Query3->FieldValues["SOKU_SU"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["SOKU_SU"]) != true )
        	{
	        	sBuf    = Form1->Query3->FieldValues["SOKU_SU"];
    	    	strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].SOKU_SU    ,sBuf.c_str());
			}
	        iSOZAI_SYKA_KOMKCNT ++;                                              //���ڐ�
    	    Form1->Query3->Next();
		}
    }
	Form1->Query3->Close();
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�FKSD01��ǂݎ��܂��B
//
//  �@�\����
//    ������уf�[�^��ǂݎ��o�b�t�@�ɒl�������܂��B
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
void __fastcall TForm1::GET_SOZAI_KSD01(void)
{
	AnsiString sTempLot,sBuf;
    iSOZAI_RIRE_LOT = 0;
    AnsiString sLot_Where;

    //�o�׌����ɂ��郍�b�g�𒊏o����NOT�̏����ɂ���
	sTempLot = "";
    for( i1 = 0;i1 < Form1->iRIRE_CNT ; i1++)
	{
		sTempLot += "'" + Form1->sRIREKI_LOT->Strings[i1] + "',";
	}
    sTempLot = sTempLot.SubString(1,sTempLot.Length()-1);

    ///////////////////////////////////////////////////////////////onishi��
    // ���b�g��������������
    sLot_Where = "";
    for( i1 = 0;i1 < Form1->iRIRE_CNT ; i1++)
	{
        sLot_Where += "( LOTNO='" + Form1->sRIREKI_LOT->Strings[i1] + "' AND ";
        sLot_Where += " HINBAN='" + Form1->sRIREKI_HIN->Strings[i1] + "') OR ";
	}
    sLot_Where = sLot_Where.SubString(1,sLot_Where.Length()-3);
    ///////////////////////////////////////////////////////////////onishi��

    //���Ӑ�i�Ԃ��L�[�ɂ��ĕK�v���b�g�̎擾������i���𐔕��j
	sBuf = "SELECT * FROM KSD01";
    sBuf += " WHERE DTKSHIN ='" + Form1->sNowDTKSHIN + "'";
    if( sTempLot.Length() > 3 ) {
    	//sBuf += " AND LOTNO IN ("+ sTempLot + ")";
        sBuf += " AND (";
        sBuf += sLot_Where;
        sBuf += " )";
    }
    sBuf += " ORDER BY UPDYMD, UPDTIM DESC";

    //For Debug
    if( iDEBUG == 1 )
    {
	    ClpBrd = Clipboard();
	    ClpBrd->Open();
        ClpBrd->SetTextBuf(sBuf.c_str());
        ClpBrd->Close();
    }
	// Initial Query
    Form1->Query3->Close();
    Form1->Query3->SQL->Clear();
    Form1->Query3->SQL->Add(sBuf);
    Form1->Query3->Open();
    Form1->Query3->Active = true;

    //����i�Ԃ̉ߋ��������b�g�̒��o
	iSOZAI_RIRE_LOT = 0;
    if( SGr_vSOKU_SOZAI->RowCount > 1 )
    {
        while( Form1->Query3->Eof == false )
        {
    	    strcpy(pSOZAI_RIRE_LOT[iSOZAI_RIRE_LOT].DTKSHIN	,"");
           	strcpy(pSOZAI_RIRE_LOT[iSOZAI_RIRE_LOT].LOTNO	,"");

        //���Ӑ�i��
            if ( VarIsNull(Form1->Query3->FieldValues["DTKSHIN"]) != true)
            {
            	sBuf 	= Form1->Query3->FieldValues["DTKSHIN"];
	            strcpy(pSOZAI_RIRE_LOT[iSOZAI_RIRE_LOT].DTKSHIN ,sBuf.c_str());
    		}
        //���b�g�m��
            if ( VarIsNull(Form1->Query3->FieldValues["LOTNO"]) != true)
            {
    	        sBuf 	= Form1->Query3->FieldValues["LOTNO"];
            	strcpy(pSOZAI_RIRE_LOT[iSOZAI_RIRE_LOT].LOTNO ,sBuf.c_str());
	    	}
        //�f�ޗp���Ӑ�i�ԂP
            if ( VarIsNull(Form1->Query3->FieldValues["DTKSHIN1_SZ"]) != true)
            {
	            sBuf 	= Form1->Query3->FieldValues["DTKSHIN1_SZ"];
    	        strcpy(pSOZAI_RIRE_LOT[iSOZAI_RIRE_LOT].DTKSHIN1_SZ ,sBuf.c_str());
    		}
        //�f�ޗp���Ӑ�i�ԂQ
            if ( VarIsNull(Form1->Query3->FieldValues["DTKSHIN2_SZ"]) != true)
            {
        	    sBuf 	= Form1->Query3->FieldValues["DTKSHIN2_SZ"];
    	        strcpy(pSOZAI_RIRE_LOT[iSOZAI_RIRE_LOT].DTKSHIN2_SZ ,sBuf.c_str());
	    	}
        //�f�ޗp���Ӑ�i�ԂR
            if ( VarIsNull(Form1->Query3->FieldValues["DTKSHIN3_SZ"]) != true)
            {
        	    sBuf 	= Form1->Query3->FieldValues["DTKSHIN3_SZ"];
            	strcpy(pSOZAI_RIRE_LOT[iSOZAI_RIRE_LOT].DTKSHIN3_SZ ,sBuf.c_str());
    		}
        //�f�ޗp���Ӑ�i�ԂS
            if ( VarIsNull(Form1->Query3->FieldValues["DTKSHIN4_SZ"]) != true)
            {
	            sBuf 	= Form1->Query3->FieldValues["DTKSHIN4_SZ"];
        	    strcpy(pSOZAI_RIRE_LOT[iSOZAI_RIRE_LOT].DTKSHIN4_SZ ,sBuf.c_str());
	    	}
        //�f�ޗp���Ӑ�i�ԂT
            if ( VarIsNull(Form1->Query3->FieldValues["DTKSHIN5_SZ"]) != true)
            {
            	sBuf 	= Form1->Query3->FieldValues["DTKSHIN5_SZ"];
	            strcpy(pSOZAI_RIRE_LOT[iSOZAI_RIRE_LOT].DTKSHIN5_SZ ,sBuf.c_str());
    		}
        //�f�ޗp���Ӑ�i�ԂU
            if ( VarIsNull(Form1->Query3->FieldValues["DTKSHIN6_SZ"]) != true)
            {
    	        sBuf 	= Form1->Query3->FieldValues["DTKSHIN6_SZ"];
            	strcpy(pSOZAI_RIRE_LOT[iSOZAI_RIRE_LOT].DTKSHIN6_SZ ,sBuf.c_str());
	    	}
            iSOZAI_RIRE_LOT++;
            Form1->Query3->Next();
        }
    }
    Form1->Query3->Close();
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�FKSD02��ǂݎ��܂��B
//
//  �@�\����
//    ������і��׃f�[�^��ǂݎ��o�b�t�@�ɒl�������܂��B(�n�q�e�[�u���쐬�p)
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
void __fastcall TForm1::GET_SOZAI_KSD02(void)
{
    AnsiString sBuf,sLot;
	int iCol;
    AnsiString sLot_Where;

	sLot = "";
    for( iCol = 0;iCol < Form1->iRIRE_CNT ; iCol++)
    {
        sLot += "'" + Form1->sRIREKI_LOT->Strings[iCol] + "'," ;
    }
    for(iCol = 0 ; iCol < Form1->SGr_tSOKU->ColCount ; iCol++)
	{
		if(  Form1->SGr_tSOKU->Cells[iCol][0].Trim().Length() != 0 )
		{
	    	sLot += "'" + Form1->SGr_tSOKU->Cells[iCol][0] + "',";
		}
	}
    sLot = sLot.SubString(1,sLot.Length()-1);

    ///////////////////////////////////////////////////////////////onishi��
    // ���b�g��������������
    sLot_Where = "";
    for( iCol = 0;iCol < Form1->iRIRE_CNT ; iCol++)
    {
        sLot_Where += "( LOTNO='" + Form1->sRIREKI_LOT->Strings[iCol] + "' AND ";
        sLot_Where += " HINBAN='" + Form1->sRIREKI_HIN->Strings[iCol] + "') OR ";
    }
    for(iCol = 0 ; iCol < Form1->SGr_tSOKU->ColCount ; iCol++)
	{
		if(  Form1->SGr_tSOKU->Cells[iCol][0].Trim().Length() != 0 )
		{
            sLot_Where += "( LOTNO='" + Form1->SGr_tSOKU->Cells[iCol][0] + "' AND ";
            sLot_Where += " HINBAN='" + Form1->SGr_tSOKU->Cells[iCol][1] + "') OR ";
		}
	}
    sLot_Where = sLot_Where.SubString(1,sLot_Where.Length()-3);
    ///////////////////////////////////////////////////////////////onishi��

	sBuf = "SELECT KIKI_NO, KOMK_NO, KOMK_NM, KOMK_SUB, TANI, HINBAN_SK, MAX(SOKU_SU) AS SOKU_SU_MAX FROM KSD02";
    sBuf += " WHERE DTKSHIN ='" + Form1->sNowDTKSHIN + "'";
    sBuf += " AND SKB_NO = 1";                        //�o�׌������ځA�ޗ��ؖ�����
    //sBuf += " AND LOTNO IN (";
	//sBuf += sLot;
    //sBuf += " )";
    sBuf += " AND (";
    sBuf += sLot_Where;
    sBuf += " )";
    sBuf += " GROUP BY KIKI_NO, KOMK_NO, KOMK_NM, KOMK_SUB, TANI, HINBAN_SK";
    sBuf += " ORDER BY KIKI_NO, KOMK_NO, KOMK_NM, KOMK_SUB, TANI, HINBAN_SK";

    //For Debug
    if( iDEBUG == 1 )
    {
	    ClpBrd = Clipboard();
	    ClpBrd->Open();
        ClpBrd->SetTextBuf(sBuf.c_str());
        ClpBrd->Close();
    }
    // Initial Query
	Form1->Query3->Close();
    Form1->Query3->SQL->Clear();
    Form1->Query3->SQL->Add(sBuf);
    Form1->Query3->Open();
    Form1->Query3->Active = true;

    //�Ώۉߋ������̌����@STEP1
	iSOZAI_RIRE_KOMKCNT = 0;
    while( Form1->Query3->Eof == false )
    {
    //����w�������i�����ő匏���j
    	if ( VarIsNull(Form1->Query3->FieldValues["SOKU_SU_MAX"]) != true)
        {
        	sBuf = Form1->Query3->FieldValues["SOKU_SU_MAX"];
            strcpy(pSOZAI_RIRE_DATA[iSOZAI_RIRE_KOMKCNT].SOKU_SU ,sBuf.c_str());
        }
    //����@��m��
        if ( VarIsNull(Form1->Query3->FieldValues["KIKI_NO"]) != true)
        {
        	sBuf = Form1->Query3->FieldValues["KIKI_NO"];
            strcpy(pSOZAI_RIRE_DATA[iSOZAI_RIRE_KOMKCNT].KIKI_NO ,sBuf.c_str());
        }
    //���荀�ڂm��
        if ( VarIsNull(Form1->Query3->FieldValues["KOMK_NO"]) != true)
        {
        	sBuf = Form1->Query3->FieldValues["KOMK_NO"];
            strcpy(pSOZAI_RIRE_DATA[iSOZAI_RIRE_KOMKCNT].KOMK_NO ,sBuf.c_str());
        }
    //���荀�ږ���
		if ( VarIsNull(Form1->Query3->FieldValues["KOMK_NM"]) != true)
        {
        	sBuf = Form1->Query3->FieldValues["KOMK_NM"];
            strcpy(pSOZAI_RIRE_DATA[iSOZAI_RIRE_KOMKCNT].KOMK_NM ,sBuf.c_str());
        }
    //���荀�ڃT�u����
        if ( VarIsNull(Form1->Query3->FieldValues["KOMK_SUB"]) != true )
        {
        	sBuf = Form1->Query3->FieldValues["KOMK_SUB"];
            strcpy(pSOZAI_RIRE_DATA[iSOZAI_RIRE_KOMKCNT].KOMK_SUB ,sBuf.c_str());
        }
    //�P�� 2002/10/20 A.Tamura
        if ( VarIsNull(Form1->Query3->FieldValues["TANI"]) != true )
        {
        	sBuf = Form1->Query3->FieldValues["TANI"];
            strcpy(pSOZAI_RIRE_DATA[iSOZAI_RIRE_KOMKCNT].TANI ,sBuf.c_str());
        }
    //�i��
        if ( VarIsNull(Form1->Query3->FieldValues["HINBAN_SK"]) != true )
        {
        	sBuf = Form1->Query3->FieldValues["HINBAN_SK"];
            strcpy(pSOZAI_RIRE_DATA[iSOZAI_RIRE_KOMKCNT].HINBAN_SK ,sBuf.c_str());
        }
        iSOZAI_RIRE_KOMKCNT ++;                                              //���ڐ�
        Form1->Query3->Next();
    }
    Form1->Query3->Close();
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�FKSD02��ǂݎ��܂��B(�Q��ځj
//
//  �@�\����
//    ������і��׃f�[�^��ǂݎ��o�b�t�@�ɒl�������܂��B(�n�q�e�[�u���쐬�p)
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
void __fastcall TForm1::GET_SOZAI_KSD02_SECOND(void)
{
	AnsiString sLot,sBuf;
	int iCol;
    AnsiString sLot_Where;

	sLot = "";
    for( iCol = 0;iCol < Form1->iRIRE_CNT ; iCol++)
    {
        Form1->SGr_tRIRE->Cells[iCol][0] = Form1->sRIREKI_LOT->Strings[iCol];
    }
	for(iCol = 0 ; iCol < Form1->SGr_tSOKU->ColCount ; iCol++)
	{
        if( Form1->SGr_tSOKU->Cells[iCol][0].Length() != 0 )
        {
    	    sLot += "'" + Form1->SGr_tSOKU->Cells[iCol][0] + "',";
        }
	}
    sLot = sLot.SubString(1,sLot.Length()-1);

    ///////////////////////////////////////////////////////////////onishi��
    // ���b�g��������������
    sLot_Where = "";
	for(iCol = 0 ; iCol < Form1->SGr_tSOKU->ColCount ; iCol++)
	{
        if( Form1->SGr_tSOKU->Cells[iCol][0].Length() != 0 )
        {
            sLot_Where += "( LOTNO='" + Form1->SGr_tSOKU->Cells[iCol][0] + "' AND ";
            sLot_Where += " HINBAN='" + Form1->SGr_tSOKU->Cells[iCol][1] + "') OR ";
        }
	}
    sLot_Where = sLot_Where.SubString(1,sLot_Where.Length()-3);
    ///////////////////////////////////////////////////////////////onishi��

    sBuf  = "SELECT KIKI_NO, KOMK_NO, KOMK_NM, KOMK_SUB, TANI, HINBAN_SK, MAX(SOKU_SU) AS SOKU_SU_MAX FROM KSD02";
    sBuf += " WHERE DTKSHIN ='" + Form1->sNowDTKSHIN + "'";
    sBuf += " AND SKB_NO = 1";                        		//�o�׌������ځA�ޗ��ؖ�����
    //sBuf += " AND LOTNO IN ("+ sLot + ")";
    sBuf += " AND (";
    sBuf += sLot_Where;
    sBuf += " )";
    sBuf += " GROUP BY KIKI_NO, KOMK_NO, KOMK_NM, KOMK_SUB, TANI, HINBAN_SK";
    sBuf += " ORDER BY KIKI_NO, KOMK_NO, KOMK_NM, KOMK_SUB, TANI, HINBAN_SK";

	//For Debug
        if( iDEBUG == 1 )
        {
		    ClpBrd = Clipboard();
		    ClpBrd->Open();
    	    ClpBrd->SetTextBuf(sBuf.c_str());
    	    ClpBrd->Close();
        }
	// Initial Query
        Form1->Query3->Close();
        Form1->Query3->SQL->Clear();
        Form1->Query3->SQL->Add(sBuf);
        Form1->Query3->Open();
        Form1->Query3->Active = true;

	//�o�׌������b�g���Ō����ς݃��b�g�̌���
		iSOZAI_KOMKCNT2 = 0;
		while( Form1->Query3->Eof == false )
    	{
        	if ( VarIsNull(Form1->Query3->FieldValues["SOKU_SU_MAX"]) != true)
        	{
	    		sBuf = Form1->Query3->FieldValues["SOKU_SU_MAX"];
        		strcpy(pSOZAI_RIRE_DATA[iSOZAI_KOMKCNT2].SOKU_SU ,sBuf.c_str());
			}
        	if ( VarIsNull(Form1->Query3->FieldValues["KIKI_NO"]) != true)
        	{
        		sBuf = Form1->Query3->FieldValues["KIKI_NO"];
        		strcpy(pSOZAI_RIRE_DATA[iSOZAI_KOMKCNT2].KIKI_NO ,sBuf.c_str());
			}
        	if ( VarIsNull(Form1->Query3->FieldValues["KOMK_NO"]) != true)
        	{
	        	sBuf = Form1->Query3->FieldValues["KOMK_NO"];
	        	strcpy(pSOZAI_RIRE_DATA[iSOZAI_KOMKCNT2].KOMK_NO ,sBuf.c_str());
			}

        	if ( VarIsNull(Form1->Query3->FieldValues["KOMK_NM"]) != true)
        	{
        		sBuf = Form1->Query3->FieldValues["KOMK_NM"];
            	strcpy(pSOZAI_RIRE_DATA[iSOZAI_KOMKCNT2].KOMK_NM ,sBuf.c_str());
        	}
        	if ( VarIsNull(Form1->Query3->FieldValues["KOMK_SUB"]) != true )
        	{
        		sBuf = Form1->Query3->FieldValues["KOMK_SUB"];
            	strcpy(pSOZAI_RIRE_DATA[iSOZAI_KOMKCNT2].KOMK_SUB ,sBuf.c_str());
        	}
        	if ( VarIsNull(Form1->Query3->FieldValues["TANI"]) != true )
        	{
        		sBuf = Form1->Query3->FieldValues["TANI"];
            	strcpy(pSOZAI_RIRE_DATA[iSOZAI_KOMKCNT2].TANI ,sBuf.c_str());
        	}
        	if ( VarIsNull(Form1->Query3->FieldValues["HINBAN_SK"]) != true )
        	{
        		sBuf = Form1->Query3->FieldValues["HINBAN_SK"];
            	strcpy(pSOZAI_RIRE_DATA[iSOZAI_KOMKCNT2].HINBAN_SK ,sBuf.c_str());
        	}
        	iSOZAI_KOMKCNT2 ++;                                              //���ڐ�
        	Form1->Query3->Next();
    	}
    	Form1->Query3->Close();
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�ތ������ڂ̒P�ʂȂǂ̏���ǂݎ��܂��B
//
//  �@�\����
//    �n�q�e�[�u�����Q�Ƃ�KSM02��������KSD02����P�ʁA�K�i�Ȃǂ̓ǂݎ����s���܂��B
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
void __fastcall TForm1::GET_SOZAI_TANI(void)
{
    AnsiString sBuf;
	AnsiString KOMK_NM,KIKI_NO;
    //double dMAX,dMIN;
	double dHalf1,dHalf2;       //�ő�ŏ��Ō���̂ł͂Ȃ��A�K�i�̒��S�̒l�����Ĕ��f

//�������̎Z�o
    iSOZAI_SOKUCNT  = 0;
    for(i1=0 ; i1 < iSOZAI_ORCNT;i1++)
    {
        iSOZAI_SOKUCNT += AnsiString(pSOZAI_OR_DATA[i1].SOKU_SU).ToIntDef(0);
    }

//����@�햼�́A���ږ��́A�P�ʁA�K�i�̒��o�i�ŐV�̂��̂�\������j

    for(i1=0;i1<iSOZAI_ORCNT;i1++)
    {
        sBuf = "SELECT * FROM KSM02";
        sBuf += " WHERE DTKSHIN ='" + Form1->sNowDTKSHIN + "'";
        sBuf += " AND KIKI_NO = " + AnsiString(pSOZAI_OR_DATA[i1].KIKI_NO);
        if(AnsiString(pSOZAI_OR_DATA[i1].KOMK_NM).Length() != 0)
        {
            sBuf += " AND KOMK_NM ='"  + AnsiString(pSOZAI_OR_DATA[i1].KOMK_NM) + "'";
        }
        else
        {
            sBuf += " AND KOMK_NM IS NULL";
        }
        if(AnsiString(pSOZAI_OR_DATA[i1].KOMK_SUB).Length() != 0)
        {
            sBuf += " AND KOMK_SUB ='"  + AnsiString(pSOZAI_OR_DATA[i1].KOMK_SUB) + "'";
        }
        else
        {
            sBuf += " AND KOMK_SUB IS NULL";
        }
        if(AnsiString(pSOZAI_OR_DATA[i1].KOMK_NO).Length() != 0)
        {
            sBuf += " AND KOMK_NO ='"  + AnsiString(pSOZAI_OR_DATA[i1].KOMK_NO) + "'";
        }
        else
        {
            sBuf += " AND KOMK_NO IS NULL";
        }
        // 2003/10/20 A.Tamura ��r�����ɒP�ʂ�ǉ����܂��i���̑O��OR�f�[�^�ɒP�ʂ��ݒ肵�Ă���j
        //                     KSM02�Ƀu���V����[mm][Cpk]���������ɁA
        //                     KSD02�ɂ��̂Q������Ɛ������\������Ȃ��G���[�����
        if(AnsiString(pSOZAI_OR_DATA[i1].TANI).Length() != 0)
        {
            sBuf += " AND TANI ='"  + AnsiString(pSOZAI_OR_DATA[i1].TANI) + "'";
        }
        else
        {
            sBuf += " AND TANI IS NULL";
        }
//�f�ނ�HI�ALO�̌����������Ȃ������̂�SQL���C�����܂����B
//REV. STEART

// 2003/11/24 A.Tamura �e�X�g�I�ɃR�����g
        if(AnsiString(pSOZAI_OR_DATA[i1].HINBAN_SK).Length() != 0)
        {
            sBuf += " AND HINBAN_SK ='"  + AnsiString(pSOZAI_OR_DATA[i1].HINBAN_SK) + "'";
        }
        else
        {
            sBuf += " AND HINBAN_SK IS NULL";
        }
//REV. END
		sBuf += " AND REVCNT = 0";
        sBuf += " AND SKB_NO = 1";                        //�o�׌������ځA�ޗ��ؖ�����

//For Debug
        // 2003.06.03 k.y
        if( iDEBUG == 1 )
        {
	        ClpBrd = Clipboard();
	        ClpBrd->Open();
	        ClpBrd->SetTextBuf(sBuf.c_str());
	        ClpBrd->Close();
        }
// Initial Query
        Form1->Query3->Close();
        Form1->Query3->SQL->Clear();
        Form1->Query3->SQL->Add(sBuf);
        Form1->Query3->Open();
        Form1->Query3->Active = true;
        if( Form1->Query3->Eof == false )
        {
        	if ( VarIsNull(Form1->Query3->FieldValues["DTKSHIN"]) != true)
			{
	        	sBuf 		= Form1->Query3->FieldValues["DTKSHIN"];		//���Ӑ�i��
    	    	strcpy(pSOZAI_OR_DATA[i1].DTKSHIN		,sBuf.c_str());
			}
        	if ( VarIsNull(Form1->Query3->FieldValues["REVCNT"]) != true)
			{
        		sBuf 		= Form1->Query3->FieldValues["REVCNT"];      	//�����ԍ�
	        	strcpy(pSOZAI_OR_DATA[i1].REVCNT		,sBuf.c_str());
            }
			if ( VarIsNull(Form1->Query3->FieldValues["UNQ_NO"]) != true)
            {
				sBuf 		= Form1->Query3->FieldValues["UNQ_NO"];    		//����NO
    	    	strcpy(pSOZAI_OR_DATA[i1].UNQ_NO		,sBuf.c_str());
			}
        	if ( VarIsNull(Form1->Query3->FieldValues["ORDER_NO"]) != true)
            {
				sBuf 		= Form1->Query3->FieldValues["ORDER_NO"];  		//�\���E�����
        		strcpy(pSOZAI_OR_DATA[i1].ORDER_NO		,sBuf.c_str());
            }
			if ( VarIsNull(Form1->Query3->FieldValues["SKB_NO"]) != true)
            {
				sBuf 		= Form1->Query3->FieldValues["SKB_NO"];    		//����NO
        		strcpy(pSOZAI_OR_DATA[i1].SKB_NO		,sBuf.c_str());
            }
			if ( VarIsNull(Form1->Query3->FieldValues["HINBAN_SK"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["HINBAN_SK"]) != true )
            {
				sBuf 		= Form1->Query3->FieldValues["HINBAN_SK"];  	//�i��
        		strcpy(pSOZAI_OR_DATA[i1].HINBAN_SK		,sBuf.c_str());
            }
			if ( VarIsNull(Form1->Query3->FieldValues["KOMK_NO"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_NO"]) != true )
            {
				sBuf 		= Form1->Query3->FieldValues["KOMK_NO"];   		//���荀��NO
        		strcpy(pSOZAI_OR_DATA[i1].KOMK_NO		,sBuf.c_str());
            }
			if ( VarIsNull(Form1->Query3->FieldValues["KOMK_NM"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_NM"]) != true )
            {
				sBuf 		= Form1->Query3->FieldValues["KOMK_NM"];  		//���荀�ږ���
				strcpy(pSOZAI_OR_DATA[i1].KOMK_NM		,sBuf.c_str());
            }
			if ( VarIsNull(Form1->Query3->FieldValues["KOMK_ENG"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_ENG"]) != true )
            {
				sBuf 		= Form1->Query3->FieldValues["KOMK_ENG"]; 		//���荀�ږ��́i�p��j
				strcpy(pSOZAI_OR_DATA[i1].KOMK_ENG		,sBuf.c_str());
            }
			sBuf = " ";
        	if ( VarIsNull(Form1->Query3->FieldValues["KOMK_SUB"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_SUB"]) != true )
            {
				sBuf 		= Form1->Query3->FieldValues["KOMK_SUB"];   	//���荀�ڃT�u����
				strcpy(pSOZAI_OR_DATA[i1].KOMK_SUB		,sBuf.c_str());
            }
            sBuf = " ";
        	if ( VarIsNull(Form1->Query3->FieldValues["KOMK_SUB_ENG"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_SUB_ENG"]) != true )
            {
				sBuf 		= Form1->Query3->FieldValues["KOMK_SUB_ENG"];	//���荀�ڃT�u���́i�p��j
				strcpy(pSOZAI_OR_DATA[i1].KOMK_SUB_ENG		,sBuf.c_str());
            }
            sBuf = " ";
			if ( VarIsNull(Form1->Query3->FieldValues["KIKI_NO"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKI_NO"]) != true )
            {
				sBuf 		= Form1->Query3->FieldValues["KIKI_NO"];     	//����@��NO
				strcpy(pSOZAI_OR_DATA[i1].KIKI_NO		,sBuf.c_str());
            }
            sBuf = " ";
			if ( VarIsNull(Form1->Query3->FieldValues["KIKI_NM"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKI_NM"]) != true )
            {
				sBuf 		= Form1->Query3->FieldValues["KIKI_NM"];  		//����@�햼��
				strcpy(pSOZAI_OR_DATA[i1].KIKI_NM		,sBuf.c_str());
            }
            sBuf = " ";
			if ( VarIsNull(Form1->Query3->FieldValues["TANI"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["TANI"]) != true )
            {
            	sBuf 		= Form1->Query3->FieldValues["TANI"];         	//�P��
            	strcpy(pSOZAI_OR_DATA[i1].TANI			,sBuf.c_str());
   			}
            sBuf = " ";
           	if ( VarIsNull(Form1->Query3->FieldValues["KIKA_TYPE"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_TYPE"]) != true )
            {
            	sBuf 	= Form1->Query3->FieldValues["KIKA_TYPE"];      	//�K�i�^�C�v
            	strcpy(pSOZAI_OR_DATA[i1].KIKA_TYPE	,sBuf.c_str());
            }
            sBuf = " ";
			if ( VarIsNull(Form1->Query3->FieldValues["KIKA_KIND"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_KIND"]) != true )
            {
            	sBuf 	= Form1->Query3->FieldValues["KIKA_KIND"];        	//�K�i���
            	strcpy(pSOZAI_OR_DATA[i1].KIKA_KIND	,sBuf.c_str());
            }
            sBuf = " ";
			if ( VarIsNull(Form1->Query3->FieldValues["KIKA_DECI"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_DECI"]) != true )
            {
            	sBuf 	= Form1->Query3->FieldValues["KIKA_DECI"];      	//�K�i�����_�ȉ�����
            	strcpy(pSOZAI_OR_DATA[i1].KIKA_DECI	,sBuf.c_str());
			}
            sBuf = " ";
        	if ( VarIsNull(Form1->Query3->FieldValues["KIKA_NUM1"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_NUM1"]) != true )
            {
            	sBuf 	= Form1->Query3->FieldValues["KIKA_NUM1"];     		//�K�i�l�P
            	strcpy(pSOZAI_OR_DATA[i1].KIKA_NUM1	,sBuf.c_str());
			}
            sBuf = " ";
        	if ( VarIsNull(Form1->Query3->FieldValues["KIKA_NUM2"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_NUM2"]) != true )
            {
	            sBuf 	= Form1->Query3->FieldValues["KIKA_NUM2"];        	//�K�i�l�Q
    	        strcpy(pSOZAI_OR_DATA[i1].KIKA_NUM2	,sBuf.c_str());
			}
            sBuf = " ";
        	if ( VarIsNull(Form1->Query3->FieldValues["KIKA_NUM3"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_NUM3"]) != true )
            {
            	sBuf 	= Form1->Query3->FieldValues["KIKA_NUM3"];        	//�K�i�l�R
            	strcpy(pSOZAI_OR_DATA[i1].KIKA_NUM3	,sBuf.c_str());
            }
            sBuf = " ";
			if ( VarIsNull(Form1->Query3->FieldValues["KIKA_STR"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_STR"]) != true )
            {
            	sBuf  	= Form1->Query3->FieldValues["KIKA_STR"];        	//�K�i�l����
            	strcpy(pSOZAI_OR_DATA[i1].KIKA_STR		,sBuf.c_str());
   			}
            sBuf = " ";
           	if ( VarIsNull(Form1->Query3->FieldValues["KIKA_SUB1"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_SUB1"]) != true )
            {
            	sBuf 	= Form1->Query3->FieldValues["KIKA_SUB1"];       	//�K�i�l�T�u�P
            	strcpy(pSOZAI_OR_DATA[i1].KIKA_SUB1	,sBuf.c_str());
            }
            sBuf = " ";
			if ( VarIsNull(Form1->Query3->FieldValues["KIKA_SUB2"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_SUB2"]) != true )
            {
            	sBuf 	= Form1->Query3->FieldValues["KIKA_SUB2"];          //�K�i�l�T�u�Q
            	strcpy(pSOZAI_OR_DATA[i1].KIKA_SUB2	,sBuf.c_str());
            }
            sBuf = " ";
			if ( VarIsNull(Form1->Query3->FieldValues["KIKA_SUB3"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_SUB3"]) != true )
            {
            	sBuf 	= Form1->Query3->FieldValues["KIKA_SUB3"];         	//�K�i�l�T�u�R
            	strcpy(pSOZAI_OR_DATA[i1].KIKA_SUB3	,sBuf.c_str());
            }
            sBuf = " ";
            //�w�������͏o���オ���Ă���̂œǂ܂Ȃ�
			//if ( VarIsNull(Form1->Query3->FieldValues["SOKU_SU"]) != true
            //&& VarIsEmpty(Form1->Query3->FieldValues["SOKU_SU"]) != true )
            //{
            // 	sBuf 	= Form1->Query3->FieldValues["SOKU_SU"];            //����w������
            //	strcpy(pSOZAI_OR_DATA[i1].SOKU_SU	,sBuf.c_str());
            //}
            sBuf = " ";
			if ( VarIsNull(Form1->Query3->FieldValues["SOKU_FLG"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["SOKU_FLG"]) != true )
            {
             	sBuf 	= Form1->Query3->FieldValues["SOKU_FLG"];        	//���荀�ڂ̗L��
            	strcpy(pSOZAI_OR_DATA[i1].SOKU_FLG	,sBuf.c_str());
            }
            sBuf = " ";
			if ( VarIsNull(Form1->Query3->FieldValues["TOKU_FLG"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["TOKU_FLG"]) != true )
            {
             	sBuf 	= Form1->Query3->FieldValues["TOKU_FLG"];       	//���ʍ��ڂ̗L��
            	strcpy(pSOZAI_OR_DATA[i1].TOKU_FLG	,sBuf.c_str());
            }
            sBuf = " ";
			if ( VarIsNull(Form1->Query3->FieldValues["KIKA_PRT"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_PRT"]) != true )
            {
             	sBuf 	= Form1->Query3->FieldValues["KIKA_PRT"];     		//��������l�̈��
            	strcpy(pSOZAI_OR_DATA[i1].KIKA_PRT	,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["VALUE_TYPE"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["VALUE_TYPE"]) != true )
            {
             	sBuf 	= Form1->Query3->FieldValues["VALUE_TYPE"];         //����l�\��
            	strcpy(pSOZAI_OR_DATA[i1].VALUE_TYPE	,sBuf.c_str());
            }
            sBuf = " ";
			if ( VarIsNull(Form1->Query3->FieldValues["VALUE_DECI"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["VALUE_DECI"]) != true )
            {
             	sBuf 	= Form1->Query3->FieldValues["VALUE_DECI"];         //����l�����_�ȉ�����
            	strcpy(pSOZAI_OR_DATA[i1].VALUE_DECI	,sBuf.c_str());
			}
        }
        else
        {
            sBuf = "SELECT * FROM KSD02";
			//2003.05.12 E.Takase Add��
            sBuf += " WHERE DTKSHIN ='" + Form1->sNowDTKSHIN + "'";
			//2003.05.12 E.Takase Add��
			//2003.05.12 E.Takase Add �R�����g��
            //sBuf += " WHERE DTKSHIN ='" + Form1->Cmb_DTKSHIN->Text + "'";
			//2003.05.12 E.Takase Add �R�����g��
            sBuf += " AND KIKI_NO = " + AnsiString(pSOZAI_OR_DATA[i1].KIKI_NO) ;
            if(AnsiString(pSOZAI_OR_DATA[i1].KOMK_NM).Length() != 0)
            {
                sBuf += " AND KOMK_NM ='"  + AnsiString(pSOZAI_OR_DATA[i1].KOMK_NM) + "'";
            }
            else
            {
                sBuf += " AND KOMK_NM IS NULL";
            }
            if(AnsiString(pSOZAI_OR_DATA[i1].KOMK_SUB).Length() != 0)
            {
            	sBuf += " AND KOMK_SUB ='"  + AnsiString(pSOZAI_OR_DATA[i1].KOMK_SUB) + "'";
// 2003/11/18 A.Tamura �ȉ��̍s�͂Ȃ��R�����g�������̂ł��傤���H
//                     �T�u���̂�HI,LO�Ȃǂŕ������Ƃ��A�s����o�Ă��܂��̂�
//                     �ȉ��̏�������L�R�[�h(1�s)�ɕύX���܂��B
//                sBuf += " AND KOMK_SUB ='"  + sBuf1 + "'";	//�����̃��b�g�̏W��sBuf1
            }
            else
            {
                sBuf += " AND KOMK_SUB IS NULL";
            }
            // 2003/10/20 A.Tamura ��r�����ɒP�ʂ�ǉ����܂��i���̑O��OR�f�[�^�ɒP�ʂ��ݒ肵�Ă���j
            //                     KSM02�Ƀu���V����[mm][Cpk]���������ɁA
            //                     KSD02�ɂ��̂Q������Ɛ������\������Ȃ��G���[�����
            if(AnsiString(pSOZAI_OR_DATA[i1].TANI).Length() != 0)
            {
                sBuf += " AND TANI ='"  + AnsiString(pSOZAI_OR_DATA[i1].TANI) + "'";
            }
            else
            {
                sBuf += " AND TANI IS NULL";
            }
            // 2003/11/24 A.Tamura �ʂ�HINBAN_SK�ŏ㏑������Ă��܂����荀�ڂ��o�Ȃ�
        	if(AnsiString(pSOZAI_OR_DATA[i1].HINBAN_SK).Length() != 0)
        	{
        	    sBuf += " AND HINBAN_SK ='"  + AnsiString(pSOZAI_OR_DATA[i1].HINBAN_SK) + "'";
        	}
        	else
        	{
        	    sBuf += " AND HINBAN_SK IS NULL";
        	}
            sBuf += " AND SKB_NO = 1";                        //�o�׌������ځA�ޗ��ؖ�����
            sBuf += " ORDER BY UPDYMD DESC, UPDTIM DESC";

		//For Debug
            // 2003.06.03 k.y
            if( iDEBUG == 1 )
            {
	            ClpBrd = Clipboard();
     		    ClpBrd->Open();
     		    ClpBrd->SetTextBuf(sBuf.c_str());
    	 	    ClpBrd->Close();
            }
		// Initial Query
            Form1->Query3->Close();
            Form1->Query3->SQL->Clear();
            Form1->Query3->SQL->Add(sBuf);
            Form1->Query3->Open();
            Form1->Query3->Active = true;
		//KSM02�ɖړI�f�[�^���Ȃ��ꍇ�͗���ǂݍ��݁i�j�r�c�O�Q�j
            if( Form1->Query3->Eof == false )
            {
				if ( VarIsNull(Form1->Query3->FieldValues["DTKSHIN"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["DTKSHIN"]) != true )
				{
        			sBuf 		= Form1->Query3->FieldValues["DTKSHIN"];		//���Ӑ�i��
        			strcpy(pSOZAI_OR_DATA[i1].DTKSHIN		,sBuf.c_str());
				}
				if ( VarIsNull(Form1->Query3->FieldValues["UNQ_NO"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["UNQ_NO"]) != true )
				{
        			sBuf 		= Form1->Query3->FieldValues["UNQ_NO"];    		//����NO
        			strcpy(pSOZAI_OR_DATA[i1].UNQ_NO		,sBuf.c_str());
				}
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["ORDER_NO"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["ORDER_NO"]) != true )
        	    {
        			sBuf 		= Form1->Query3->FieldValues["ORDER_NO"];  		//�\���E�����
        			strcpy(pSOZAI_OR_DATA[i1].ORDER_NO		,sBuf.c_str());
				}
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["SKB_NO"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["SKB_NO"]) != true )
        	    {
        			sBuf 		= Form1->Query3->FieldValues["SKB_NO"];    		//����NO
        			strcpy(pSOZAI_OR_DATA[i1].SKB_NO		,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["HINBAN_SK"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["HINBAN_SK"]) != true )
        	    {
        			sBuf 		= Form1->Query3->FieldValues["HINBAN_SK"];  	//�i��
        			strcpy(pSOZAI_OR_DATA[i1].HINBAN_SK		,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KOMK_NO"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KOMK_NO"]) != true )
        	    {
        			sBuf 		= Form1->Query3->FieldValues["KOMK_NO"];   		//���荀��NO
        			strcpy(pSOZAI_OR_DATA[i1].KOMK_NO		,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KOMK_NM"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KOMK_NM"]) != true )
        	    {
					sBuf 		= Form1->Query3->FieldValues["KOMK_NM"];  		//���荀�ږ���
					strcpy(pSOZAI_OR_DATA[i1].KOMK_NM		,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KOMK_ENG"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KOMK_ENG"]) != true )
        	    {
					sBuf 		= Form1->Query3->FieldValues["KOMK_ENG"]; 		//���荀�ږ��́i�p��j
					strcpy(pSOZAI_OR_DATA[i1].KOMK_ENG		,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KOMK_SUB"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KOMK_SUB"]) != true )
        	    {
					sBuf 		= Form1->Query3->FieldValues["KOMK_SUB"];   	//���荀�ڃT�u����
					strcpy(pSOZAI_OR_DATA[i1].KOMK_SUB		,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KOMK_SUB_ENG"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KOMK_SUB_ENG"]) != true )
        	    {
					sBuf 		= Form1->Query3->FieldValues["KOMK_SUB_ENG"];	//���荀�ڃT�u���́i�p��j
					strcpy(pSOZAI_OR_DATA[i1].KOMK_SUB_ENG		,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KIKI_NO"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKI_NO"]) != true )
        	    {
					sBuf 		= Form1->Query3->FieldValues["KIKI_NO"];     	//����@��NO
					strcpy(pSOZAI_OR_DATA[i1].KIKI_NO		,sBuf.c_str());
                }
				sBuf = " ";
                if ( VarIsNull(Form1->Query3->FieldValues["KIKI_NM"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKI_NM"]) != true )
        	    {
					sBuf 		= Form1->Query3->FieldValues["KIKI_NM"];  		//����@�햼��
					strcpy(pSOZAI_OR_DATA[i1].KIKI_NM		,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["TANI"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["TANI"]) != true )
        	    {
            		sBuf 		= Form1->Query3->FieldValues["TANI"];         	//�P��
            		strcpy(pSOZAI_OR_DATA[i1].TANI			,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KIKA_TYPE"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKA_TYPE"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["KIKA_TYPE"];      	//�K�i�^�C�v
            		strcpy(pSOZAI_OR_DATA[i1].KIKA_TYPE	,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KIKA_KIND"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKA_KIND"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["KIKA_KIND"];        	//�K�i���
            		strcpy(pSOZAI_OR_DATA[i1].KIKA_KIND	,sBuf.c_str());
				}
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KIKA_DECI"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKA_DECI"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["KIKA_DECI"];      	//�K�i�����_�ȉ�����
            		strcpy(pSOZAI_OR_DATA[i1].KIKA_DECI	,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KIKA_NUM1"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKA_NUM1"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["KIKA_NUM1"];     		//�K�i�l�P
            		strcpy(pSOZAI_OR_DATA[i1].KIKA_NUM1	,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KIKA_NUM2"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKA_NUM2"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["KIKA_NUM2"];        	//�K�i�l�Q
            		strcpy(pSOZAI_OR_DATA[i1].KIKA_NUM2	,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KIKA_NUM3"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKA_NUM3"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["KIKA_NUM3"];        	//�K�i�l�R
            		strcpy(pSOZAI_OR_DATA[i1].KIKA_NUM3	,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KIKA_STR"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKA_STR"]) != true )
        	    {
            		sBuf  	= Form1->Query3->FieldValues["KIKA_STR"];        	//�K�i�l����
            		strcpy(pSOZAI_OR_DATA[i1].KIKA_STR		,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KIKA_SUB1"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKA_SUB1"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["KIKA_SUB1"];       	//�K�i�l�T�u�P
            		strcpy(pSOZAI_OR_DATA[i1].KIKA_SUB1	,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KIKA_SUB2"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKA_SUB2"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["KIKA_SUB2"];          //�K�i�l�T�u�Q
            		strcpy(pSOZAI_OR_DATA[i1].KIKA_SUB2	,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KIKA_SUB3"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKA_SUB3"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["KIKA_SUB3"];         	//�K�i�l�T�u�R
            		strcpy(pSOZAI_OR_DATA[i1].KIKA_SUB3	,sBuf.c_str());
                }
				sBuf = " ";
				//if ( VarIsNull(Form1->Query3->FieldValues["SOKU_SU"]) != true
    	        //&& VarIsEmpty(Form1->Query3->FieldValues["SOKU_SU"]) != true )
        	    //{
            	//	sBuf 	= Form1->Query3->FieldValues["SOKU_SU"];            //����w������
            	//	strcpy(pSOZAI_OR_DATA[i1].SOKU_SU	,sBuf.c_str());
                //}
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["SOKU_FLG"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["SOKU_FLG"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["SOKU_FLG"];        	//���荀�ڂ̗L��
            		strcpy(pSOZAI_OR_DATA[i1].SOKU_FLG	,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["TOKU_FLG"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["TOKU_FLG"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["TOKU_FLG"];       	//���ʍ��ڂ̗L��
            		strcpy(pSOZAI_OR_DATA[i1].TOKU_FLG	,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KIKA_PRT"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKA_PRT"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["KIKA_PRT"];     		//��������l�̈��
            		strcpy(pSOZAI_OR_DATA[i1].KIKA_PRT	,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["VALUE_TYPE"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["VALUE_TYPE"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["VALUE_TYPE"];         //����l�\��
            		strcpy(pSOZAI_OR_DATA[i1].VALUE_TYPE	,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["VALUE_DECI"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["VALUE_DECI"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["VALUE_DECI"];         //����l�����_�ȉ�����
            		strcpy(pSOZAI_OR_DATA[i1].VALUE_DECI	,sBuf.c_str());
				}
            }
        }

/* 2003/11/24 A.Tamura �e�X�g�R�����g              ��L�̏����Őݒ�ς݂ł�...�Ȃ����H
        //��ԍ��[�̋K�i��ǂݎ��
        sBuf = "SELECT * FROM KSD02";
        //2003.05.12 E.Takase Add��
        sBuf += " WHERE DTKSHIN ='" + Form1->sNowDTKSHIN + "'";
        //2003.05.12 E.Takase Add��
        //2003.05.12 E.Takase Add �R�����g��
        //sBuf += " WHERE DTKSHIN ='" + Form1->Cmb_DTKSHIN->Text + "'";
        //2003.05.12 E.Takase Add �R�����g��
        sBuf += " AND KIKI_NO = " + AnsiString(pSOZAI_OR_DATA[i1].KIKI_NO) ;
        if(AnsiString(pSOZAI_OR_DATA[i1].KOMK_NM).Length() != 0)
        {
            sBuf += " AND KOMK_NM ='"  + AnsiString(pSOZAI_OR_DATA[i1].KOMK_NM) + "'";
        }
        else
        {
            sBuf += " AND KOMK_NM IS NULL";
        }
        if(AnsiString(pSOZAI_OR_DATA[i1].KOMK_SUB).Length() != 0)
        {
            sBuf += " AND KOMK_SUB ='"  + AnsiString(pSOZAI_OR_DATA[i1].KOMK_SUB) + "'";
// 2003/11/18 A.Tamura �ȉ��̍s�͂Ȃ��R�����g�������̂ł��傤���H
//                     �T�u���̂�HI,LO�Ȃǂŕ������Ƃ��A�s����o�Ă��܂��̂�
//                     �ȉ��̏�������L�R�[�h(1�s)�ɕύX���܂��B
//                sBuf += " AND KOMK_SUB ='"  + sBuf1 + "'";	//�����̃��b�g�̏W��sBuf1
        }
        else
        {
            sBuf += " AND KOMK_SUB IS NULL";
        }
//�P�ʂ��Ⴄ�ꍇ�ɑΉ�(2003/09/01)
        if(AnsiString(pSOZAI_OR_DATA[i1].TANI).Length() != 0)
        {
            sBuf += " AND TANI ='"  + AnsiString(pSOZAI_OR_DATA[i1].TANI) + "'";
        }
        else
        {
            sBuf += " AND TANI IS NULL";
        }
        sBuf += " AND SKB_NO = 1";                        //�o�׌������ځA�ޗ��ؖ�����
        sBuf += " AND LOTNO ='" + AnsiString(SGr_tSOKU->Cells[0][0]).Trim() + "'";
        sBuf += " ORDER BY UPDYMD DESC, UPDTIM DESC";

		//For Debug
        // 2003.06.03 k.y
        if( iDEBUG == 1 )
        {
            ClpBrd = Clipboard();
            ClpBrd->Open();
            ClpBrd->SetTextBuf(sBuf.c_str());
            ClpBrd->Close();
        }
		// Initial Query
        Form1->Query3->Close();
        Form1->Query3->SQL->Clear();
        Form1->Query3->SQL->Add(sBuf);
        Form1->Query3->Open();
        Form1->Query3->Active = true;
		//KSM02�ɖړI�f�[�^���Ȃ��ꍇ�͗���ǂݍ��݁i�j�r�c�O�Q�j
        if( Form1->Query3->Eof == false )
        {
            if ( VarIsNull(Form1->Query3->FieldValues["DTKSHIN"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["DTKSHIN"]) != true )
            {
                sBuf 		= Form1->Query3->FieldValues["DTKSHIN"];		//���Ӑ�i��
                strcpy(pSOZAI_OR_DATA[i1].DTKSHIN		,sBuf.c_str());
            }
            if ( VarIsNull(Form1->Query3->FieldValues["UNQ_NO"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["UNQ_NO"]) != true )
            {
                sBuf 		= Form1->Query3->FieldValues["UNQ_NO"];    		//����NO
                strcpy(pSOZAI_OR_DATA[i1].UNQ_NO		,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["ORDER_NO"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["ORDER_NO"]) != true )
            {
                sBuf 		= Form1->Query3->FieldValues["ORDER_NO"];  		//�\���E�����
                strcpy(pSOZAI_OR_DATA[i1].ORDER_NO		,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["SKB_NO"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["SKB_NO"]) != true )
            {
                sBuf 		= Form1->Query3->FieldValues["SKB_NO"];    		//����NO
                strcpy(pSOZAI_OR_DATA[i1].SKB_NO		,sBuf.c_str());
            }
            // 2003/11/24 A.Tamura �e�X�g�I�ɃR�����g����
            //sBuf = " ";
            //if ( VarIsNull(Form1->Query3->FieldValues["HINBAN_SK"]) != true
            //&& VarIsEmpty(Form1->Query3->FieldValues["HINBAN_SK"]) != true )
            //{
            //    sBuf 		= Form1->Query3->FieldValues["HINBAN_SK"];  	//�i��
            //    strcpy(pSOZAI_OR_DATA[i1].HINBAN_SK		,sBuf.c_str());
            //}

            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KOMK_NO"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_NO"]) != true )
            {
                sBuf 		= Form1->Query3->FieldValues["KOMK_NO"];   		//���荀��NO
                strcpy(pSOZAI_OR_DATA[i1].KOMK_NO		,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KOMK_NM"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_NM"]) != true )
            {
                sBuf 		= Form1->Query3->FieldValues["KOMK_NM"];  		//���荀�ږ���
                strcpy(pSOZAI_OR_DATA[i1].KOMK_NM		,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KOMK_ENG"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_ENG"]) != true )
            {
                sBuf 		= Form1->Query3->FieldValues["KOMK_ENG"]; 		//���荀�ږ��́i�p��j
                strcpy(pSOZAI_OR_DATA[i1].KOMK_ENG		,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KOMK_SUB"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_SUB"]) != true )
            {
                sBuf 		= Form1->Query3->FieldValues["KOMK_SUB"];   	//���荀�ڃT�u����
                strcpy(pSOZAI_OR_DATA[i1].KOMK_SUB		,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KOMK_SUB_ENG"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_SUB_ENG"]) != true )
            {
                sBuf 		= Form1->Query3->FieldValues["KOMK_SUB_ENG"];	//���荀�ڃT�u���́i�p��j
                strcpy(pSOZAI_OR_DATA[i1].KOMK_SUB_ENG		,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KIKI_NO"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKI_NO"]) != true )
            {
                sBuf 		= Form1->Query3->FieldValues["KIKI_NO"];     	//����@��NO
                strcpy(pSOZAI_OR_DATA[i1].KIKI_NO		,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KIKI_NM"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKI_NM"]) != true )
            {
                sBuf 		= Form1->Query3->FieldValues["KIKI_NM"];  		//����@�햼��
                strcpy(pSOZAI_OR_DATA[i1].KIKI_NM		,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["TANI"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["TANI"]) != true )
            {
                sBuf 		= Form1->Query3->FieldValues["TANI"];         	//�P��
                strcpy(pSOZAI_OR_DATA[i1].TANI			,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KIKA_TYPE"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_TYPE"]) != true )
            {
                sBuf 	= Form1->Query3->FieldValues["KIKA_TYPE"];      	//�K�i�^�C�v
                strcpy(pSOZAI_OR_DATA[i1].KIKA_TYPE	,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KIKA_KIND"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_KIND"]) != true )
            {
                sBuf 	= Form1->Query3->FieldValues["KIKA_KIND"];        	//�K�i���
                strcpy(pSOZAI_OR_DATA[i1].KIKA_KIND	,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KIKA_DECI"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_DECI"]) != true )
            {
                sBuf 	= Form1->Query3->FieldValues["KIKA_DECI"];      	//�K�i�����_�ȉ�����
                strcpy(pSOZAI_OR_DATA[i1].KIKA_DECI	,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KIKA_NUM1"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_NUM1"]) != true )
            {
                sBuf 	= Form1->Query3->FieldValues["KIKA_NUM1"];     		//�K�i�l�P
                strcpy(pSOZAI_OR_DATA[i1].KIKA_NUM1	,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KIKA_NUM2"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_NUM2"]) != true )
            {
                sBuf 	= Form1->Query3->FieldValues["KIKA_NUM2"];        	//�K�i�l�Q
                strcpy(pSOZAI_OR_DATA[i1].KIKA_NUM2	,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KIKA_NUM3"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_NUM3"]) != true )
            {
                sBuf 	= Form1->Query3->FieldValues["KIKA_NUM3"];        	//�K�i�l�R
                strcpy(pSOZAI_OR_DATA[i1].KIKA_NUM3	,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KIKA_STR"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_STR"]) != true )
            {
                sBuf  	= Form1->Query3->FieldValues["KIKA_STR"];        	//�K�i�l����
                strcpy(pSOZAI_OR_DATA[i1].KIKA_STR		,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KIKA_SUB1"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_SUB1"]) != true )
            {
                sBuf 	= Form1->Query3->FieldValues["KIKA_SUB1"];       	//�K�i�l�T�u�P
                strcpy(pSOZAI_OR_DATA[i1].KIKA_SUB1	,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KIKA_SUB2"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_SUB2"]) != true )
            {
                sBuf 	= Form1->Query3->FieldValues["KIKA_SUB2"];          //�K�i�l�T�u�Q
                strcpy(pSOZAI_OR_DATA[i1].KIKA_SUB2	,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KIKA_SUB3"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_SUB3"]) != true )
            {
                sBuf 	= Form1->Query3->FieldValues["KIKA_SUB3"];         	//�K�i�l�T�u�R
                strcpy(pSOZAI_OR_DATA[i1].KIKA_SUB3	,sBuf.c_str());
            }
            sBuf = " ";
            //if ( VarIsNull(Form1->Query3->FieldValues["SOKU_SU"]) != true
            //&& VarIsEmpty(Form1->Query3->FieldValues["SOKU_SU"]) != true )
            //{
            //	sBuf 	= Form1->Query3->FieldValues["SOKU_SU"];            //����w������
            //	strcpy(pSOZAI_OR_DATA[i1].SOKU_SU	,sBuf.c_str());
            //}


            //sBuf = " ";
            //if ( VarIsNull(Form1->Query3->FieldValues["SOKU_FLG"]) != true
            //&& VarIsEmpty(Form1->Query3->FieldValues["SOKU_FLG"]) != true )
            //{
            //    sBuf 	= Form1->Query3->FieldValues["SOKU_FLG"];        	//���荀�ڂ̗L��
            //    strcpy(pSOZAI_OR_DATA[i1].SOKU_FLG	,sBuf.c_str());
            //}
            //sBuf = " ";
            //if ( VarIsNull(Form1->Query3->FieldValues["TOKU_FLG"]) != true
            //&& VarIsEmpty(Form1->Query3->FieldValues["TOKU_FLG"]) != true )
            //{
            //    sBuf 	= Form1->Query3->FieldValues["TOKU_FLG"];       	//���ʍ��ڂ̗L��
            //    strcpy(pSOZAI_OR_DATA[i1].TOKU_FLG	,sBuf.c_str());
            //}
            //sBuf = " ";
            //if ( VarIsNull(Form1->Query3->FieldValues["KIKA_PRT"]) != true
            //&& VarIsEmpty(Form1->Query3->FieldValues["KIKA_PRT"]) != true )
            //{
            //    sBuf 	= Form1->Query3->FieldValues["KIKA_PRT"];     		//��������l�̈��
            //    strcpy(pSOZAI_OR_DATA[i1].KIKA_PRT	,sBuf.c_str());
            //}
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["VALUE_TYPE"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["VALUE_TYPE"]) != true )
            {
                sBuf 	= Form1->Query3->FieldValues["VALUE_TYPE"];         //����l�\��
                strcpy(pSOZAI_OR_DATA[i1].VALUE_TYPE	,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["VALUE_DECI"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["VALUE_DECI"]) != true )
            {
                sBuf 	= Form1->Query3->FieldValues["VALUE_DECI"];         //����l�����_�ȉ�����
                strcpy(pSOZAI_OR_DATA[i1].VALUE_DECI	,sBuf.c_str());
            }
        }

        Form1->Query3->Close();
*/
    }

/////////////////////
//�K�i�̓ǂݍ��݂��I�������̂ŉ��߂ă\�[�g�i�K�i�̏����j���s��


/* A.T 2003/05/08
    // �������̊J��
    if( hTEMPORDATA ){
        GlobalUnlock( hTEMPORDATA );
        GlobalFree( hTEMPORDATA );
    }
	hTEMPORDATA = NULL;
    // �������̊m��
    hTEMPORDATA = GlobalAlloc( GHND, sizeof(struct KSM02_DATA) * 1 );
    if( hTEMPORDATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(01)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
    pTEMPORDATA = (struct KSM02_DATA *)GlobalLock(hTEMPORDATA);
    if( hTEMPORDATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(02)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
*/
    memset(&pTEMPORDATA,(int)NULL,sizeof(pTEMPORDATA));


/* k.y 2003.05.17
    // �������̊J��
    if( hTEMPORDATA ){
        GlobalUnlock( hTEMPORDATA );
        GlobalFree( hTEMPORDATA );
    }
	hTEMPORDATA = NULL;
    // �������̊m��
    hTEMPORDATA = GlobalAlloc( GHND, sizeof(struct KSM02_DATA) * 1 );
    if( hTEMPORDATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(01)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
    pTEMPORDATA = (struct KSM02_DATA *)GlobalLock(hTEMPORDATA);
    if( hTEMPORDATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(02)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
*/
    memset(pTEMPORDATA,0x00,sizeof(pTEMPORDATA));

//�K�i�\�[�g
    //ORDER_NO�ŕ��я��̃\�[�g���s���܂�
	for(i2 = 0; i2 < iSOZAI_ORCNT ; i2++)
	{
		for(i1 = 0; i1 < iSOZAI_ORCNT-1; i1++)
		{
//			if( AnsiString(pSOZAI_OR_DATA[i1].KIKI_NO) == AnsiString(pSOZAI_OR_DATA[i1+1].KIKI_NO) )
//			if(1)
//			{
//    			GetSOZAI_KIKAKU(i1,&dMAX,&dMIN);
//				dHalf1 = dMAX - dMIN + dMIN;
//				dHalf1 = dMIN;
				dHalf1 = AnsiString(pSOZAI_OR_DATA[ i1 ].ORDER_NO).ToIntDef(0);
//   			GetSOZAI_KIKAKU(i1+1,&dMAX,&dMIN);
//				dHalf2 = dMAX - dMIN + dMIN;
//				dHalf2 = dMIN;
				dHalf2 = AnsiString(pSOZAI_OR_DATA[ i1+1 ].ORDER_NO).ToIntDef(0);
            if( dHalf1 > dHalf2 )
            {
			// dTEMPORDATA[0] <- dORDATA[i1]
                strcpy(pTEMPORDATA[ 0 ].DTKSHIN		, pSOZAI_OR_DATA[ i1 ].DTKSHIN);
                strcpy(pTEMPORDATA[ 0 ].UNQ_NO 		, pSOZAI_OR_DATA[ i1 ].UNQ_NO);
                strcpy(pTEMPORDATA[ 0 ].ORDER_NO 	, pSOZAI_OR_DATA[ i1 ].ORDER_NO);
			   	strcpy(pTEMPORDATA[ 0 ].SKB_NO 		, pSOZAI_OR_DATA[ i1 ].SKB_NO);
			  	strcpy(pTEMPORDATA[ 0 ].HINBAN_SK 	, pSOZAI_OR_DATA[ i1 ].HINBAN_SK);
			 	strcpy(pTEMPORDATA[ 0 ].KOMK_NO 	, pSOZAI_OR_DATA[ i1 ].KOMK_NO);
				strcpy(pTEMPORDATA[ 0 ].KOMK_NM 	, pSOZAI_OR_DATA[ i1 ].KOMK_NM);
		   		strcpy(pTEMPORDATA[ 0 ].KOMK_ENG 	, pSOZAI_OR_DATA[ i1 ].KOMK_ENG);
		  		strcpy(pTEMPORDATA[ 0 ].KOMK_SUB 	, pSOZAI_OR_DATA[ i1 ].KOMK_SUB);
		 		strcpy(pTEMPORDATA[ 0 ].KOMK_SUB_ENG, pSOZAI_OR_DATA[ i1 ].KOMK_SUB_ENG);
				strcpy(pTEMPORDATA[ 0 ].KIKI_NO 	, pSOZAI_OR_DATA[ i1 ].KIKI_NO);
	   			strcpy(pTEMPORDATA[ 0 ].KIKI_NM 	, pSOZAI_OR_DATA[ i1 ].KIKI_NM);
	  			strcpy(pTEMPORDATA[ 0 ].TANI 		, pSOZAI_OR_DATA[ i1 ].TANI);
			   	strcpy(pTEMPORDATA[ 0 ].KIKA_TYPE 	, pSOZAI_OR_DATA[ i1 ].KIKA_TYPE);
			  	strcpy(pTEMPORDATA[ 0 ].KIKA_KIND 	, pSOZAI_OR_DATA[ i1 ].KIKA_KIND);
			 	strcpy(pTEMPORDATA[ 0 ].KIKA_DECI 	, pSOZAI_OR_DATA[ i1 ].KIKA_DECI);
				strcpy(pTEMPORDATA[ 0 ].KIKA_NUM1 	, pSOZAI_OR_DATA[ i1 ].KIKA_NUM1);
		   		strcpy(pTEMPORDATA[ 0 ].KIKA_NUM2 	, pSOZAI_OR_DATA[ i1 ].KIKA_NUM2);
		  		strcpy(pTEMPORDATA[ 0 ].KIKA_NUM3 	, pSOZAI_OR_DATA[ i1 ].KIKA_NUM3);
		 		strcpy(pTEMPORDATA[ 0 ].KIKA_STR 	, pSOZAI_OR_DATA[ i1 ].KIKA_STR);
				strcpy(pTEMPORDATA[ 0 ].KIKA_SUB1 	, pSOZAI_OR_DATA[ i1 ].KIKA_SUB1);
	   			strcpy(pTEMPORDATA[ 0 ].KIKA_SUB2 	, pSOZAI_OR_DATA[ i1 ].KIKA_SUB2);
	  			strcpy(pTEMPORDATA[ 0 ].KIKA_SUB3 	, pSOZAI_OR_DATA[ i1 ].KIKA_SUB3);
	 			strcpy(pTEMPORDATA[ 0 ].SOKU_SU 	, pSOZAI_OR_DATA[ i1 ].SOKU_SU);
				strcpy(pTEMPORDATA[ 0 ].SOKU_FLG 	, pSOZAI_OR_DATA[ i1 ].SOKU_FLG);
   				strcpy(pTEMPORDATA[ 0 ].TOKU_FLG 	, pSOZAI_OR_DATA[ i1 ].TOKU_FLG);
		  		strcpy(pTEMPORDATA[ 0 ].KIKA_PRT 	, pSOZAI_OR_DATA[ i1 ].KIKA_PRT);
		 		strcpy(pTEMPORDATA[ 0 ].VALUE_TYPE 	, pSOZAI_OR_DATA[ i1 ].VALUE_TYPE);
				strcpy(pTEMPORDATA[ 0 ].VALUE_DECI 	, pSOZAI_OR_DATA[ i1 ].VALUE_DECI);

				// dORDATA[i1] <- dORDATA[i1+1]
		   		strcpy(pSOZAI_OR_DATA[ i1 ].DTKSHIN		, pSOZAI_OR_DATA[ i1+1 ].DTKSHIN);
		  		strcpy(pSOZAI_OR_DATA[ i1 ].UNQ_NO 		, pSOZAI_OR_DATA[ i1+1 ].UNQ_NO);
		 		strcpy(pSOZAI_OR_DATA[ i1 ].ORDER_NO 	, pSOZAI_OR_DATA[ i1+1 ].ORDER_NO);
				strcpy(pSOZAI_OR_DATA[ i1 ].SKB_NO 		, pSOZAI_OR_DATA[ i1+1 ].SKB_NO);
	   			strcpy(pSOZAI_OR_DATA[ i1 ].HINBAN_SK 	, pSOZAI_OR_DATA[ i1+1 ].HINBAN_SK);
	  			strcpy(pSOZAI_OR_DATA[ i1 ].KOMK_NO 	, pSOZAI_OR_DATA[ i1+1 ].KOMK_NO);
		   		strcpy(pSOZAI_OR_DATA[ i1 ].KOMK_NM 	, pSOZAI_OR_DATA[ i1+1 ].KOMK_NM);
		  		strcpy(pSOZAI_OR_DATA[ i1 ].KOMK_ENG 	, pSOZAI_OR_DATA[ i1+1 ].KOMK_ENG);
		 		strcpy(pSOZAI_OR_DATA[ i1 ].KOMK_SUB 	, pSOZAI_OR_DATA[ i1+1 ].KOMK_SUB);
				strcpy(pSOZAI_OR_DATA[ i1 ].KOMK_SUB_ENG, pSOZAI_OR_DATA[ i1+1 ].KOMK_SUB_ENG);
	   			strcpy(pSOZAI_OR_DATA[ i1 ].KIKI_NO 	, pSOZAI_OR_DATA[ i1+1 ].KIKI_NO);
	  			strcpy(pSOZAI_OR_DATA[ i1 ].KIKI_NM 	, pSOZAI_OR_DATA[ i1+1 ].KIKI_NM);
	 			strcpy(pSOZAI_OR_DATA[ i1 ].TANI 		, pSOZAI_OR_DATA[ i1+1 ].TANI);
				strcpy(pSOZAI_OR_DATA[ i1 ].KIKA_TYPE 	, pSOZAI_OR_DATA[ i1+1 ].KIKA_TYPE);
   				strcpy(pSOZAI_OR_DATA[ i1 ].KIKA_KIND 	, pSOZAI_OR_DATA[ i1+1 ].KIKA_KIND);
  				strcpy(pSOZAI_OR_DATA[ i1 ].KIKA_DECI 	, pSOZAI_OR_DATA[ i1+1 ].KIKA_DECI);
 				strcpy(pSOZAI_OR_DATA[ i1 ].KIKA_NUM1 	, pSOZAI_OR_DATA[ i1+1 ].KIKA_NUM1);
		 		strcpy(pSOZAI_OR_DATA[ i1 ].KIKA_NUM2 	, pSOZAI_OR_DATA[ i1+1 ].KIKA_NUM2);
				strcpy(pSOZAI_OR_DATA[ i1 ].KIKA_NUM3 	, pSOZAI_OR_DATA[ i1+1 ].KIKA_NUM3);
	   			strcpy(pSOZAI_OR_DATA[ i1 ].KIKA_STR 	, pSOZAI_OR_DATA[ i1+1 ].KIKA_STR);
	  			strcpy(pSOZAI_OR_DATA[ i1 ].KIKA_SUB1 	, pSOZAI_OR_DATA[ i1+1 ].KIKA_SUB1);
	 			strcpy(pSOZAI_OR_DATA[ i1 ].KIKA_SUB2 	, pSOZAI_OR_DATA[ i1+1 ].KIKA_SUB2);
				strcpy(pSOZAI_OR_DATA[ i1 ].KIKA_SUB3 	, pSOZAI_OR_DATA[ i1+1 ].KIKA_SUB3);
   				strcpy(pSOZAI_OR_DATA[ i1 ].SOKU_SU 	, pSOZAI_OR_DATA[ i1+1 ].SOKU_SU);
  				strcpy(pSOZAI_OR_DATA[ i1 ].SOKU_FLG 	, pSOZAI_OR_DATA[ i1+1 ].SOKU_FLG);
				strcpy(pSOZAI_OR_DATA[ i1 ].TOKU_FLG 	, pSOZAI_OR_DATA[ i1+1 ].TOKU_FLG);
		   		strcpy(pSOZAI_OR_DATA[ i1 ].KIKA_PRT 	, pSOZAI_OR_DATA[ i1+1 ].KIKA_PRT);
		  		strcpy(pSOZAI_OR_DATA[ i1 ].VALUE_TYPE 	, pSOZAI_OR_DATA[ i1+1 ].VALUE_TYPE);
		 		strcpy(pSOZAI_OR_DATA[ i1 ].VALUE_DECI 	, pSOZAI_OR_DATA[ i1+1 ].VALUE_DECI);
				// dORDATA[i1+1] <- dTEMPORDATA[0]
				strcpy(pSOZAI_OR_DATA[ i1+1 ].DTKSHIN	, pTEMPORDATA[ 0 ].DTKSHIN);
		   		strcpy(pSOZAI_OR_DATA[ i1+1 ].UNQ_NO 	, pTEMPORDATA[ 0 ].UNQ_NO);
		  		strcpy(pSOZAI_OR_DATA[ i1+1 ].ORDER_NO 	, pTEMPORDATA[ 0 ].ORDER_NO);
		 		strcpy(pSOZAI_OR_DATA[ i1+1 ].SKB_NO 	, pTEMPORDATA[ 0 ].SKB_NO);
				strcpy(pSOZAI_OR_DATA[ i1+1 ].HINBAN_SK , pTEMPORDATA[ 0 ].HINBAN_SK);
	   			strcpy(pSOZAI_OR_DATA[ i1+1 ].KOMK_NO 	, pTEMPORDATA[ 0 ].KOMK_NO);
	  			strcpy(pSOZAI_OR_DATA[ i1+1 ].KOMK_NM 	, pTEMPORDATA[ 0 ].KOMK_NM);
	 			strcpy(pSOZAI_OR_DATA[ i1+1 ].KOMK_ENG 	, pTEMPORDATA[ 0 ].KOMK_ENG);
				strcpy(pSOZAI_OR_DATA[ i1+1 ].KOMK_SUB 	, pTEMPORDATA[ 0 ].KOMK_SUB);
   				strcpy(pSOZAI_OR_DATA[ i1+1 ].KOMK_SUB_ENG , pTEMPORDATA[ 0 ].KOMK_SUB_ENG);
  				strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKI_NO 	, pTEMPORDATA[ 0 ].KIKI_NO);
 				strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKI_NM 	, pTEMPORDATA[ 0 ].KIKI_NM);
				strcpy(pSOZAI_OR_DATA[ i1+1 ].TANI 		, pTEMPORDATA[ 0 ].TANI);
				strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_TYPE , pTEMPORDATA[ 0 ].KIKA_TYPE);
		   		strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_KIND , pTEMPORDATA[ 0 ].KIKA_KIND);
		  		strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_DECI , pTEMPORDATA[ 0 ].KIKA_DECI);
		 		strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_NUM1 , pTEMPORDATA[ 0 ].KIKA_NUM1);
				strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_NUM2 , pTEMPORDATA[ 0 ].KIKA_NUM2);
	   			strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_NUM3 , pTEMPORDATA[ 0 ].KIKA_NUM3);
	  			strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_STR 	, pTEMPORDATA[ 0 ].KIKA_STR);
	 			strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_SUB1 , pTEMPORDATA[ 0 ].KIKA_SUB1);
				strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_SUB2 , pTEMPORDATA[ 0 ].KIKA_SUB2);
   				strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_SUB3 , pTEMPORDATA[ 0 ].KIKA_SUB3);
  				strcpy(pSOZAI_OR_DATA[ i1+1 ].SOKU_SU 	, pTEMPORDATA[ 0 ].SOKU_SU);
 				strcpy(pSOZAI_OR_DATA[ i1+1 ].SOKU_FLG 	, pTEMPORDATA[ 0 ].SOKU_FLG);
				strcpy(pSOZAI_OR_DATA[ i1+1 ].TOKU_FLG 	, pTEMPORDATA[ 0 ].TOKU_FLG);
		   		strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_PRT 	, pTEMPORDATA[ 0 ].KIKA_PRT);
		  		strcpy(pSOZAI_OR_DATA[ i1+1 ].VALUE_TYPE, pTEMPORDATA[ 0 ].VALUE_TYPE);
		  		strcpy(pSOZAI_OR_DATA[ i1+1 ].VALUE_DECI, pTEMPORDATA[ 0 ].VALUE_DECI);
            }
			//}
		}
	}

//�������ڂ��܂Ƃ߂�
    //KOMK_NM��KIKI_NO���������ڂ�����Ηׂɂ܂Ƃ߂܂��B
	for(i1 = 0; i1 < iSOZAI_ORCNT; i1++)
	{
		KOMK_NM = pSOZAI_OR_DATA[ i1 ].KOMK_NM;
		KIKI_NO = pSOZAI_OR_DATA[ i1 ].KIKI_NO;
		for(i2 = i1+1; i2 < iSOZAI_ORCNT; i2++)
		{
			if((AnsiString(pSOZAI_OR_DATA[ i2 ].KOMK_NM) == KOMK_NM)
            && (AnsiString(pSOZAI_OR_DATA[ i2 ].KIKI_NO) == KIKI_NO))
			{
			// dTEMPORDATA[0] <- dORDATA[i1]
	            strcpy(pTEMPORDATA[ 0 ].DTKSHIN	    , pSOZAI_OR_DATA[ i2 ].DTKSHIN);
    	        strcpy(pTEMPORDATA[ 0 ].UNQ_NO 	    , pSOZAI_OR_DATA[ i2 ].UNQ_NO);
        	    strcpy(pTEMPORDATA[ 0 ].ORDER_NO 	, pSOZAI_OR_DATA[ i2 ].ORDER_NO);
            	strcpy(pTEMPORDATA[ 0 ].SKB_NO 	    , pSOZAI_OR_DATA[ i2 ].SKB_NO);
	            strcpy(pTEMPORDATA[ 0 ].HINBAN_SK 	, pSOZAI_OR_DATA[ i2 ].HINBAN_SK);
    	        strcpy(pTEMPORDATA[ 0 ].KOMK_NO 	, pSOZAI_OR_DATA[ i2 ].KOMK_NO);
        	    strcpy(pTEMPORDATA[ 0 ].KOMK_NM 	, pSOZAI_OR_DATA[ i2 ].KOMK_NM);
	            strcpy(pTEMPORDATA[ 0 ].KOMK_ENG 	, pSOZAI_OR_DATA[ i2 ].KOMK_ENG);
    	        strcpy(pTEMPORDATA[ 0 ].KOMK_SUB 	, pSOZAI_OR_DATA[ i2 ].KOMK_SUB);
        	    strcpy(pTEMPORDATA[ 0 ].KOMK_SUB_ENG , pSOZAI_OR_DATA[ i2 ].KOMK_SUB_ENG);
	            strcpy(pTEMPORDATA[ 0 ].KIKI_NO 	, pSOZAI_OR_DATA[ i2 ].KIKI_NO);
    	        strcpy(pTEMPORDATA[ 0 ].KIKI_NM 	, pSOZAI_OR_DATA[ i2 ].KIKI_NM);
        	    strcpy(pTEMPORDATA[ 0 ].TANI 		, pSOZAI_OR_DATA[ i2 ].TANI);
	            strcpy(pTEMPORDATA[ 0 ].KIKA_TYPE 	, pSOZAI_OR_DATA[ i2 ].KIKA_TYPE);
    	        strcpy(pTEMPORDATA[ 0 ].KIKA_KIND 	, pSOZAI_OR_DATA[ i2 ].KIKA_KIND);
        	    strcpy(pTEMPORDATA[ 0 ].KIKA_DECI 	, pSOZAI_OR_DATA[ i2 ].KIKA_DECI);
	            strcpy(pTEMPORDATA[ 0 ].KIKA_NUM1 	, pSOZAI_OR_DATA[ i2 ].KIKA_NUM1);
    	        strcpy(pTEMPORDATA[ 0 ].KIKA_NUM2 	, pSOZAI_OR_DATA[ i2 ].KIKA_NUM2);
        	    strcpy(pTEMPORDATA[ 0 ].KIKA_NUM3 	, pSOZAI_OR_DATA[ i2 ].KIKA_NUM3);
	            strcpy(pTEMPORDATA[ 0 ].KIKA_STR 	, pSOZAI_OR_DATA[ i2 ].KIKA_STR);
    	        strcpy(pTEMPORDATA[ 0 ].KIKA_SUB1 	, pSOZAI_OR_DATA[ i2 ].KIKA_SUB1);
        	    strcpy(pTEMPORDATA[ 0 ].KIKA_SUB2 	, pSOZAI_OR_DATA[ i2 ].KIKA_SUB2);
	            strcpy(pTEMPORDATA[ 0 ].KIKA_SUB3 	, pSOZAI_OR_DATA[ i2 ].KIKA_SUB3);
    	        strcpy(pTEMPORDATA[ 0 ].SOKU_SU 	, pSOZAI_OR_DATA[ i2 ].SOKU_SU);
        	    strcpy(pTEMPORDATA[ 0 ].SOKU_FLG 	, pSOZAI_OR_DATA[ i2 ].SOKU_FLG);
	            strcpy(pTEMPORDATA[ 0 ].TOKU_FLG 	, pSOZAI_OR_DATA[ i2 ].TOKU_FLG);
    	        strcpy(pTEMPORDATA[ 0 ].KIKA_PRT 	, pSOZAI_OR_DATA[ i2 ].KIKA_PRT);
        	    strcpy(pTEMPORDATA[ 0 ].VALUE_TYPE 	, pSOZAI_OR_DATA[ i2 ].VALUE_TYPE);
	            strcpy(pTEMPORDATA[ 0 ].VALUE_DECI 	, pSOZAI_OR_DATA[ i2 ].VALUE_DECI);
				for(i3 = i2-1;i3 > i1; i3--)
				{
					strcpy(pSOZAI_OR_DATA[ i3+1 ].DTKSHIN	, pSOZAI_OR_DATA[ i3 ].DTKSHIN);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].UNQ_NO 	, pSOZAI_OR_DATA[ i3 ].UNQ_NO);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].ORDER_NO	, pSOZAI_OR_DATA[ i3 ].ORDER_NO);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].SKB_NO 	, pSOZAI_OR_DATA[ i3 ].SKB_NO);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].HINBAN_SK, pSOZAI_OR_DATA[ i3 ].HINBAN_SK);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KOMK_NO 	, pSOZAI_OR_DATA[ i3 ].KOMK_NO);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KOMK_NM 	, pSOZAI_OR_DATA[ i3 ].KOMK_NM);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KOMK_ENG 	, pSOZAI_OR_DATA[ i3 ].KOMK_ENG);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KOMK_SUB 	, pSOZAI_OR_DATA[ i3 ].KOMK_SUB);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KOMK_SUB_ENG , pSOZAI_OR_DATA[ i3 ].KOMK_SUB_ENG);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKI_NO 	, pSOZAI_OR_DATA[ i3 ].KIKI_NO);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKI_NM 	, pSOZAI_OR_DATA[ i3 ].KIKI_NM);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].TANI 		, pSOZAI_OR_DATA[ i3 ].TANI);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKA_TYPE 	, pSOZAI_OR_DATA[ i3 ].KIKA_TYPE);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKA_KIND 	, pSOZAI_OR_DATA[ i3 ].KIKA_KIND);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKA_DECI 	, pSOZAI_OR_DATA[ i3 ].KIKA_DECI);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKA_NUM1 	, pSOZAI_OR_DATA[ i3 ].KIKA_NUM1);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKA_NUM2 	, pSOZAI_OR_DATA[ i3 ].KIKA_NUM2);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKA_NUM3 	, pSOZAI_OR_DATA[ i3 ].KIKA_NUM3);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKA_STR 	, pSOZAI_OR_DATA[ i3 ].KIKA_STR);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKA_SUB1 	, pSOZAI_OR_DATA[ i3 ].KIKA_SUB1);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKA_SUB2 	, pSOZAI_OR_DATA[ i3 ].KIKA_SUB2);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKA_SUB3 	, pSOZAI_OR_DATA[ i3 ].KIKA_SUB3);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].SOKU_SU 	, pSOZAI_OR_DATA[ i3 ].SOKU_SU);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].SOKU_FLG 	, pSOZAI_OR_DATA[ i3 ].SOKU_FLG);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].TOKU_FLG 	, pSOZAI_OR_DATA[ i3 ].TOKU_FLG);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKA_PRT 	, pSOZAI_OR_DATA[ i3 ].KIKA_PRT);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].VALUE_TYPE 	, pSOZAI_OR_DATA[ i3 ].VALUE_TYPE);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].VALUE_DECI 	, pSOZAI_OR_DATA[ i3 ].VALUE_DECI);
				}
			// dORDATA[i1+1] <- dTEMPORDATA[0]
	            strcpy(pSOZAI_OR_DATA[ i1+1 ].DTKSHIN		, pTEMPORDATA[ 0 ].DTKSHIN);
    	        strcpy(pSOZAI_OR_DATA[ i1+1 ].UNQ_NO 		, pTEMPORDATA[ 0 ].UNQ_NO);
        	    strcpy(pSOZAI_OR_DATA[ i1+1 ].ORDER_NO 	    , pTEMPORDATA[ 0 ].ORDER_NO);
            	strcpy(pSOZAI_OR_DATA[ i1+1 ].SKB_NO 		, pTEMPORDATA[ 0 ].SKB_NO);
	            strcpy(pSOZAI_OR_DATA[ i1+1 ].HINBAN_SK 	, pTEMPORDATA[ 0 ].HINBAN_SK);
    	        strcpy(pSOZAI_OR_DATA[ i1+1 ].KOMK_NO 		, pTEMPORDATA[ 0 ].KOMK_NO);
        	    strcpy(pSOZAI_OR_DATA[ i1+1 ].KOMK_NM 		, pTEMPORDATA[ 0 ].KOMK_NM);
            	strcpy(pSOZAI_OR_DATA[ i1+1 ].KOMK_ENG 	    , pTEMPORDATA[ 0 ].KOMK_ENG);
	            strcpy(pSOZAI_OR_DATA[ i1+1 ].KOMK_SUB 	    , pTEMPORDATA[ 0 ].KOMK_SUB);
    	        strcpy(pSOZAI_OR_DATA[ i1+1 ].KOMK_SUB_ENG  , pTEMPORDATA[ 0 ].KOMK_SUB_ENG);
        	    strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKI_NO 		, pTEMPORDATA[ 0 ].KIKI_NO);
    	        strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKI_NM 		, pTEMPORDATA[ 0 ].KIKI_NM);
	            strcpy(pSOZAI_OR_DATA[ i1+1 ].TANI 		    , pTEMPORDATA[ 0 ].TANI);
        	    strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_TYPE 	, pTEMPORDATA[ 0 ].KIKA_TYPE);
            	strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_KIND 	, pTEMPORDATA[ 0 ].KIKA_KIND);
	            strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_DECI 	, pTEMPORDATA[ 0 ].KIKA_DECI);
    	        strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_NUM1 	, pTEMPORDATA[ 0 ].KIKA_NUM1);
        	    strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_NUM2 	, pTEMPORDATA[ 0 ].KIKA_NUM2);
            	strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_NUM3 	, pTEMPORDATA[ 0 ].KIKA_NUM3);
	            strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_STR 	    , pTEMPORDATA[ 0 ].KIKA_STR);
    	        strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_SUB1 	, pTEMPORDATA[ 0 ].KIKA_SUB1);
        	    strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_SUB2 	, pTEMPORDATA[ 0 ].KIKA_SUB2);
            	strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_SUB3 	, pTEMPORDATA[ 0 ].KIKA_SUB3);
	            strcpy(pSOZAI_OR_DATA[ i1+1 ].SOKU_SU 		, pTEMPORDATA[ 0 ].SOKU_SU);
    	        strcpy(pSOZAI_OR_DATA[ i1+1 ].SOKU_FLG 	    , pTEMPORDATA[ 0 ].SOKU_FLG);
        	    strcpy(pSOZAI_OR_DATA[ i1+1 ].TOKU_FLG 	    , pTEMPORDATA[ 0 ].TOKU_FLG);
            	strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_PRT 	    , pTEMPORDATA[ 0 ].KIKA_PRT);
	            strcpy(pSOZAI_OR_DATA[ i1+1 ].VALUE_TYPE 	, pTEMPORDATA[ 0 ].VALUE_TYPE);
    	        strcpy(pSOZAI_OR_DATA[ i1+1 ].VALUE_DECI 	, pTEMPORDATA[ 0 ].VALUE_DECI);
        		break;
			}
		}
    }


/* k.y 2003.05.17
    // �������̊J��
    if( hTEMPORDATA ){
        GlobalUnlock( hTEMPORDATA );
        GlobalFree( hTEMPORDATA );
    }
	hTEMPORDATA = NULL;
*/
//    Synchronize(Set_SOZAI_GRID);
    Set_SOZAI_GRID();

}


//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�쐬�����n�q�e�[�u�����g�����I�R���g���[���𐶐����č��ڂ��쐬���܂��B
//
//  �@�\����
//    �n�q�e�[�u�����Q�Ƃ��A���I�R���g���[�����쐬���܂��B
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
void __fastcall TForm1::Set_SOZAI_GRID(void)
{
// k.y 2003.05.17
//extern HANDLE hSOZAI_OR_DATA;

// k.y 2003.05.17
//extern KSM02_DATA *pSOZAI_OR_DATA;         // �f�ނ̂n�q�f�[�^
extern KSM02_DATA pSOZAI_OR_DATA[100];

// k.y 2003.05.17
//extern HANDLE hSOZAI_OR_DATA2;

// k.y 2003.05.17
//extern KSM02_DATA *pSOZAI_OR_DATA2;        // �f�ނ̂n�q�f�[�^�i�f�ރ��C���ō쐬�j
extern KSM02_DATA pSOZAI_OR_DATA2[100];

// k.y 2003.05.17
//extern HANDLE hSOZAI_SYKA_DATA;

// k.y 2003.05.17
//extern KSM02_DATA *pSOZAI_SYKA_DATA;
extern KSM02_DATA pSOZAI_SYKA_DATA[100];

// k.y 2003.05.17
//extern HANDLE hSOZAI_RIRE_DATA;
// k.y 2003.05.17
//extern KSD02_DATA *pSOZAI_RIRE_DATA;
extern KSD02_DATA pSOZAI_RIRE_DATA[100];

// k.y 2003.05.17
//extern HANDLE hSOZAI_RIRE_LOT;
// k.y 2003.05.17
//extern KSD01_DATA *pSOZAI_RIRE_LOT;
extern KSD01_DATA pSOZAI_RIRE_LOT[100];

extern 	int iSOZAI_ORCNT;
extern	int iSOZAI_SOKUCNT;													//�\�[�g���g�p����d�݌v�Z�p�o�b�t�@

AnsiString sBuf,sLot,sTempBuf;
AnsiString 	sDeci1;
//char cFormatBuf[20],c1[20],c2[10];

    //���I�R���g���[�����폜���܂��B
    for(i2=0 ;i2<iSOZAI_DEL_SokuCnt;i2++)
    {
        delete Form1->Pnl_SOZAI_InsNo[i2];
    }
    iSOZAI_DEL_SokuCnt = 0;
    for(i2=0 ;i2<iSOZAI_DEL_OrCnt;i2++)
    {
        delete Form1->Lab_SOZAI_KOMK_NM[i2];
        delete Form1->Lab_SOZAI_TANI[i2];
        delete Form1->Lab_SOZAI_KIKA[i2];
        delete Form1->Lab_SOZAI_UPKIKA[i2];
        delete Form1->Lab_SOZAI_LOKIKA[i2];
        delete Form1->Pnl_SOZAI_InsName[i2];
    }
    for(i2=0 ;i2<iSOZAI_DEL_OrCnt;i2++)
    {
        delete Form1->Pnl_SOZAI_SubBase[i2];
    }
    iSOZAI_DEL_OrCnt = 0;

    Form1->SGr_vRIRE_SOZAI->RowCount = 1;
    Form1->SGr_vSOKU_SOZAI->RowCount = 1;
    //Form1->SGr_vRIRE_SOZAI->Visible  = false;
    Form1->SGr_vSOKU_SOZAI->Visible  = false;

	Form1->Refresh();
// ���I�R���g���[���̍쐬(�K�v�����̐錾�j
    Form1->Pnl_SOZAI_SubBase    = new TPanel *[iSOZAI_ORCNT];
    Form1->Pnl_SOZAI_InsName    = new TPanel *[iSOZAI_ORCNT];
    Form1->Lab_SOZAI_KOMK_NM    = new TLabel *[iSOZAI_ORCNT];
    Form1->Lab_SOZAI_TANI       = new TLabel *[iSOZAI_ORCNT];
    Form1->Lab_SOZAI_KIKA       = new TLabel *[iSOZAI_ORCNT];
    Form1->Lab_SOZAI_UPKIKA     = new TLabel *[iSOZAI_ORCNT];
    Form1->Lab_SOZAI_LOKIKA     = new TLabel *[iSOZAI_ORCNT];
    Form1->Pnl_SOZAI_InsNo      = new TPanel *[iSOZAI_SOKUCNT];

    i2 = 0;
    i1 = 0;
    iSOZAI_ContCnt = 0;
    iPnl_SOZAI_InsNoCnt = 0;
	iSOZAI_SOKUCNT = 0;
    iPanelNum = 0;
    iSokuGoukei = 0;
    iPnl_SOZAI_InsNoCnt = 0;
	iPnl_SOZAI_InsNameCnt = 0;
    iPnl_SOZAI_InsSubBaseCnt = 0;
    iSOZAI_ContCnt = 0;

    //Form1->SGr_vRIRE_SOZAI->Visible  = true;
    Form1->SGr_vSOKU_SOZAI->Visible  = true;

    while( iSOZAI_ContCnt < iSOZAI_ORCNT )
    {
        iPutKiki = AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKI_NO).ToIntDef(0);
//����@��̑��胋�[�v
        while( iPutKiki == AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKI_NO).ToIntDef(0)
				&& iSOZAI_ContCnt < iSOZAI_ORCNT)
        {
//�x�[�X�p�l���̕`��
            sBuf = IntToStr(iSOZAI_ContCnt);
            Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt] = new TPanel(Form1->SBx_Left_SOZAI);
            Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->Name = "Pnl_Sozai_SubBase" + AnsiString::StringOfChar('0', 2-sBuf.Length()) + sBuf;
            Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->Parent = Form1->SBx_Left_SOZAI;
            Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->Left = Form1->Pnl_SOZAI_ORG_SUBBASE->Left;
            if( iSOZAI_ContCnt == 0 )
            {

                Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->Top = 25;
            }
            else
            {
                Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->Top = Form1-> Pnl_SOZAI_SubBase[iSOZAI_ContCnt - 1 ]->Top+Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt - 1 ]->Height;
            }
            Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->Width = Form1->Pnl_SOZAI_ORG_SUBBASE->Width;
            Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->Height =
				24*(AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].SOKU_SU).ToIntDef(0))
				+(AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].SOKU_SU).ToIntDef(0));
            Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->Ctl3D = true;
            Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->BevelInner = bvNone;
            Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->BevelOuter = bvNone;
            Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->BorderWidth = 0;
            iPnl_SOZAI_InsSubBaseCnt ++;
//���荀�ڕ\���p�l���̕`��
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt] = new TPanel(Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]);
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Name = "Pnl_SOZAI_InsName" + AnsiString::StringOfChar('0', 2-sBuf.Length()) + sBuf;
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Alignment = taLeftJustify;
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Align =alLeft ;
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Caption = "";
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Parent = Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt];
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Left = Form1->Pnl_SOZAI_ORG_INSNAME->Left;
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Top = 0;
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Width = Form1->Pnl_SOZAI_ORG_INSNAME->Width;
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Height = Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->Height;
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Color = (TColor)SOZAI_COLOR;
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Ctl3D = false;
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->BevelInner = bvNone;
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->BevelOuter = bvRaised;
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->BorderStyle = bsNone;
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->BorderWidth = 0;
            iPnl_SOZAI_InsNameCnt ++;
//���荀�ڂ̕`��
            Form1->Lab_SOZAI_KOMK_NM[iSOZAI_ContCnt] =  new TLabel(Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]);
            Form1->Lab_SOZAI_KOMK_NM[iSOZAI_ContCnt]->Parent = Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt];
            Form1->Lab_SOZAI_KOMK_NM[iSOZAI_ContCnt]->AutoSize = true;
            Form1->Lab_SOZAI_KOMK_NM[iSOZAI_ContCnt]->Top = 6;
            Form1->Lab_SOZAI_KOMK_NM[iSOZAI_ContCnt]->Left = 0;
            Form1->Lab_SOZAI_KOMK_NM[iSOZAI_ContCnt]->Height = Form1->Lab_BASESOZAIKOMK_NM->Height;
            Form1->Lab_SOZAI_KOMK_NM[iSOZAI_ContCnt]->Caption = AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KOMK_NM) + AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KOMK_SUB);
            Form1->Lab_SOZAI_KOMK_NM[iSOZAI_ContCnt]->Font->Size = 11;
//�P�ʂ̕`��
            Form1->Lab_SOZAI_TANI[iSOZAI_ContCnt] =     new TLabel(Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]);
            Form1->Lab_SOZAI_TANI[iSOZAI_ContCnt]->Parent    = Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt];
            Form1->Lab_SOZAI_TANI[iSOZAI_ContCnt]->AutoSize = true;
            Form1->Lab_SOZAI_TANI[iSOZAI_ContCnt]->Caption = pSOZAI_OR_DATA[iSOZAI_ContCnt].TANI;
            Form1->Lab_SOZAI_TANI[iSOZAI_ContCnt]->Top = 6;
            Form1->Lab_SOZAI_TANI[iSOZAI_ContCnt]->Height = Form1->Lab_BASESOZAITANI->Height;
            Form1->Lab_SOZAI_TANI[iSOZAI_ContCnt]->Font->Size = 11;
            Form1->Lab_SOZAI_TANI[iSOZAI_ContCnt]->Left = Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Width-Form1->Lab_SOZAI_TANI[iSOZAI_ContCnt]->Width-2 ;
//�����̕\��
            iPanelNum = 0;
            for(i4=0 ; i4 < AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].SOKU_SU).ToIntDef(0);i4++)
            {
                sBuf = IntToStr(iPanelNum);
                Form1->Pnl_SOZAI_InsNo[iPnl_SOZAI_InsNoCnt]           = new TPanel(Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]);
                Form1->Pnl_SOZAI_InsNo[iPnl_SOZAI_InsNoCnt]->Name     = "Pnl_SOZAI_InsNo" + AnsiString::StringOfChar('0', 4-sBuf.Length()) + sBuf;
                Form1->Pnl_SOZAI_InsNo[iPnl_SOZAI_InsNoCnt]->Caption  = i4+1;
                Form1->Pnl_SOZAI_InsNo[iPnl_SOZAI_InsNoCnt]->Parent   = Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt];
                Form1->Pnl_SOZAI_InsNo[iPnl_SOZAI_InsNoCnt]->Left     = Form1->Pnl_SOZAI_ORG_INSNUM->Left;
                Form1->Pnl_SOZAI_InsNo[iPnl_SOZAI_InsNoCnt]->Top      = (Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->Height)/AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].SOKU_SU).ToIntDef(0) * i4;
                Form1->Pnl_SOZAI_InsNo[iPnl_SOZAI_InsNoCnt]->Width    = Form1->Pnl_OrgInsNum->Width;
                Form1->Pnl_SOZAI_InsNo[iPnl_SOZAI_InsNoCnt]->Height   = (Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->Height)/AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].SOKU_SU).ToIntDef(0);
                Form1->Pnl_SOZAI_InsNo[iPnl_SOZAI_InsNoCnt]->Color    = (TColor)SOZAI_COLOR;
                iPanelNum ++;
                iSokuGoukei ++;
                iPnl_SOZAI_InsNoCnt ++;
                Form1->SGr_vRIRE_SOZAI->RowCount ++;
                Form1->SGr_vSOKU_SOZAI->RowCount ++;
            }
iSOZAI_SOKUCNT = iSokuGoukei;
//�K�i�̕\��
			Sleep(10);
    //�K�i�l���C�����x��
            Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt] =  new TLabel(Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]);
            Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Parent = Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt];
            Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->ParentColor = false;
            Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->AutoSize = true;
            Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Top = Form1->Lab_BASESOZAIKIKA->Top;
            Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Left =  Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Width-Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Width;
            Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Height =  Form1->Lab_BASESOZAIKIKA->Height ;
            Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Font->Color = clBlack;
            Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Font->Size = 11;
            Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Font->Name ="�l�r �S�V�b�N";
    //�K�i�l������x��
            Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt] =  new TLabel(Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]);
            Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Parent = Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt];
            Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->AutoSize = true;
            Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Top = Form1->Lab_BASESOZAIUPKIKA->Top;
            Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Left =  Form1->Lab_BASESOZAIUPKIKA->Left  ;
            Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Height =  Form1->Lab_BASESOZAIUPKIKA->Height ;
            Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Font->Color = clBlack;;
            Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Font->Size = 9;
            Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Font->Name ="�l�r �S�V�b�N";
    //�K�i�l�������x��
            Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt] =  new TLabel(Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]);
            Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Parent = Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt];
            Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->AutoSize = true;
            Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Top = Form1->Lab_BASESOZAILOKIKA->Top;
            Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Left =  Form1->Lab_BASESOZAILOKIKA->Left  ;
            Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Height =  Form1->Lab_BASESOZAILOKIKA->Height ;
            Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Font->Color = clBlack;;
            Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Font->Size = 9;
            Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Font->Name ="�l�r �S�V�b�N";
    //�K�i�\���F�X
    //�t�H�[�}�b�g�w��i��*.*���j
   			sDeci1 = "0";
			for(i1 = 0;i1 < AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_DECI).ToIntDef(0);i1++)
			{
				if(i1 == 0 ) sDeci1 += ".";
				sDeci1 +="0";
			}
            switch(AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_TYPE).ToIntDef(0))
            {
            case 1:
                switch(AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_KIND).ToIntDef(0))
                {
                case 1:
                     sBuf = FormatFloat(sDeci1,AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_NUM1).ToDouble());
                     sBuf +=  "�`";
                     sBuf += FormatFloat(sDeci1,AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_NUM2).ToDouble());
                     Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Caption = sBuf;
                     break;
                case 2:
                     sBuf = FormatFloat(sDeci1,AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_NUM2).ToDouble());
                     Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Caption = sBuf +"�ȉ�";
                     break;
                case 3:
                     sBuf = FormatFloat(sDeci1,AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_NUM1).ToDouble());
                     Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Caption = sBuf +"�ȏ�";
                     break;
                default:
                    break;
                }
                Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Left =
                Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Width-Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Width-2;
                Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Visible = false;
                Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Visible = false;
                break;
            case 2:
                sBuf = FormatFloat(sDeci1,AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_NUM1).ToDouble());
                Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Caption = sBuf;
                switch(AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_KIND).ToIntDef(0))
                {
                case 1:
                    Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Caption =
                        FormatFloat(sDeci1,AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_NUM2).ToDouble());
                    Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Caption =
                        FormatFloat(sDeci1,AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_NUM3).ToDouble());
					if(Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Caption.ToDouble()>=0) Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Caption = "+" + Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Caption;
					if(Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Caption.ToDouble()>=0) Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Caption = "+" + Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Caption;
                    break;
                case 2:
                    Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Caption =
                        FormatFloat(sDeci1,AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_NUM2).ToDouble());
                    Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Caption ="";
					if(Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Caption.ToDouble()>=0) Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Caption = "+" + Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Caption;
                    break;
                case 3:
                    Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Caption = "";
                    Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Caption =
                        FormatFloat(sDeci1,AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_NUM3).ToDouble());
					if(Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Caption.ToDouble()>=0) Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Caption = "+" + Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Caption;
                    break;
                 default:
                    break;
                }
                if(Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Width >= Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Width)
                {
                    Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Left =
                        Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Width - Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Width -2;
                    Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Left = Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Left;
                }
                else
                {
                    Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Left =
                        Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Width - Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Width -2;
                    Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Left = Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Left;
                }
                Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Left =
                    Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Left-Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Width-2;
                break;
            case 3:
                Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Caption = AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_STR);
                Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Caption ="";
                Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Caption ="";
                Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Left =
                Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Width-Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Width-2;
                Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Visible = false;
                Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Visible = false;
                break;
            default:
                break;
            }
            iSOZAI_ContCnt++;
        }
    }
    iSOZAI_DEL_SokuCnt  = 	iSOZAI_SOKUCNT;
    iSOZAI_DEL_OrCnt    =	iSOZAI_ORCNT;
	Form1->Panel27->Caption =AnsiString("�f�@�ށ@���@���@�i")+ iSOZAI_ContCnt +AnsiString("���j");
//�Z���ƍ��ڃp�l����HEIGHT�̒����̂���DUMMY�p�l����u���܂�
	if(iSOZAI_ContCnt > 0 )
	{
		Form1->Pnl_DUMMY2->Parent = Form1->SBx_Left_SOZAI;
		Form1->Pnl_DUMMY2->Top = Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt - 1]->Top+Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt - 1]->Height;
	    Form1->Pnl_DUMMY2->Height = 39;		//�O���b�h�ɃX�N���[���o�[���o��/���o���ō�����ς��������A��i���������ߒ��Ԃ̒l���Ƃ�
	    Form1->Pnl_DUMMY2->Width = 1;
		Form1->Pnl_DUMMY2->Left = 0;
	    Form1->Pnl_DUMMY2->Ctl3D = false;
    	Form1->Pnl_DUMMY2->BevelInner = bvNone;
	    Form1->Pnl_DUMMY2->BevelOuter = bvRaised;
    	Form1->Pnl_DUMMY2->BorderStyle = bsNone;
	    Form1->Pnl_DUMMY2->BorderWidth = 0;
		Form1->Pnl_DUMMY2->Visible = true;
    }
}
//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�n�q�f�[�^���炠�鍀�ڋK�i��MIN,MAX�l��Ԃ��܂��B
//
//  �@�\����
//    �n�q�f�[�^���瑴�̋K�i��MIN,MAX�l��Ԃ��܂��B
//
//  �p�����^����
//    int iIndex	�FOR�f�[�^�̉��Ԗڂ��Q�Ƃ��邩
//    double *dMAX  : MAX�l��Ԃ��܂�
//    double *dMIN  : MIN�l��Ԃ��܂�
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::GetSOZAI_KIKAKU(int iIndex,double *dMAX,double *dMIN)
{
	double dSWAP;

	*dMAX = 0.0;
	*dMIN = 0.0;

	if(iDEBUG == 1) return;
    if( AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_TYPE).ToIntDef(0) != 3 )
    {
        //2003.05.08 E.Takase Add��
       	*dMAX = Form1->ConvDoubleDefD(pSOZAI_OR_DATA[iIndex].KIKA_NUM1,0.0);
       	*dMIN = Form1->ConvDoubleDefD(pSOZAI_OR_DATA[iIndex].KIKA_NUM1,0.0);
        //2003.05.08 E.Takase Add��
        //2003.05.08 E.Takase Add �R�����g��
		//try{
    	//	*dMAX = AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_NUM1).ToDouble();
        //	*dMIN = AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_NUM1).ToDouble();
		//}
		//catch(EConvertError& e){
		//	return;
		//}
		//catch(...){
		//	return;
		//}
        //2003.05.08 E.Takase Add �R�����g��
        switch(AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_TYPE).ToIntDef(0))
        {
        case 1:
        	switch(AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_KIND).ToIntDef(0))
            {
            case 1:
                //2003.05.08 E.Takase Add��
            	*dMAX = Form1->ConvDoubleDefD(pSOZAI_OR_DATA[iIndex].KIKA_NUM2,0.0);
                *dMIN = Form1->ConvDoubleDefD(pSOZAI_OR_DATA[iIndex].KIKA_NUM1,0.0);
        		//2003.05.08 E.Takase Add��
        		//2003.05.08 E.Takase Add �R�����g��
				//try{
            	//	*dMAX = AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_NUM2).ToDouble();
                //	*dMIN = AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_NUM1).ToDouble();
                //}
				//catch(EConvertError& e){
				//	return;
				//}
				//catch(...){
				//	return;
				//}
        		//2003.05.08 E.Takase Add �R�����g��
                break;
            case 2:
                //2003.05.08 E.Takase Add��
                *dMAX = Form1->ConvDoubleDefD(pSOZAI_OR_DATA[iIndex].KIKA_NUM2,0.0);
        		//2003.05.08 E.Takase Add��
        		//2003.05.08 E.Takase Add �R�����g��
				//try{
            	//	*dMAX = AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_NUM2).ToDouble();
				//}
				//catch(EConvertError& e){
				//	return;
				//}
				//catch(...){
				//	return;
				//}
        		//2003.05.08 E.Takase Add �R�����g��
                break;
            case 3:
            	break;
            default:
            	break;
            }
            break;
        case 2:
        	switch(AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_KIND).ToIntDef(0))
            {
            case 1:
            	//2003.05.08 E.Takase Add��
            	*dMAX += Form1->ConvDoubleDefD(pSOZAI_OR_DATA[iIndex].KIKA_NUM2,0.0);
               	*dMIN += Form1->ConvDoubleDefD(pSOZAI_OR_DATA[iIndex].KIKA_NUM3,0.0);
        		//2003.05.08 E.Takase Add��
        		//2003.05.08 E.Takase Add �R�����g��
				//try{
            	//	*dMAX += AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_NUM2).ToDouble();
                //	*dMIN += AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_NUM3).ToDouble();
                //}
				//catch(EConvertError& e){
				//	return;
				//}
				//catch(...){
				//	return;
				//}
        		//2003.05.08 E.Takase Add �R�����g��
                break;
            case 2:
            	//2003.05.08 E.Takase Add��
            	*dMAX += Form1->ConvDoubleDefD(pSOZAI_OR_DATA[iIndex].KIKA_NUM2,0.0);
        		//2003.05.08 E.Takase Add��
        		//2003.05.08 E.Takase Add �R�����g��
				//try{
            	//	*dMAX += AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_NUM2).ToDouble();
                //}
				//catch(EConvertError& e){
				//	return;
				///}
				//catch(...){
				//	return;
				//}
        		//2003.05.08 E.Takase Add �R�����g��
                break;
            case 3:
            	//2003.05.08 E.Takase Add��
            	*dMIN += Form1->ConvDoubleDefD(pSOZAI_OR_DATA[iIndex].KIKA_NUM3,0.0);
        		//2003.05.08 E.Takase Add��
        		//2003.05.08 E.Takase Add �R�����g��
				//try{
            	// 	*dMIN += AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_NUM3).ToDouble();
                //}
				//catch(EConvertError& e){
				//	return;
				//}
				//catch(...){
				//	return;
				//}
        		//2003.05.08 E.Takase Add �R�����g��
                break;
            default:
            	break;
            }
            break;
        default:
        	break;
        }
		if( *dMAX < *dMIN )
		{
			dSWAP = *dMIN;
			*dMIN = *dMAX;
			*dMAX = dSWAP;
		}
	}
}



