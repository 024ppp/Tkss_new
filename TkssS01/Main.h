#ifndef MainMenuH
#define MainMenuH

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Chart.hpp>
#include <Series.hpp>
#include <TeeFunci.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Db.hpp>
#include <DBTables.hpp>


#include <fcntl.h>
#include <io.h>

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <dir.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <winbase.h>
#include <shellapi.h>
#include <Printers.hpp>
#include <malloc.h>
#include <memory.h>
#include <time.h>
#include <wingdi.h>

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"

//�f�ޑ�����уf�[�^�O���荞�ݓ���
extern struct structKSD29{
	AnsiString FUNC_ID ;  //����NO
    AnsiString UPDYMD ;   //�������t
    AnsiString UPDTIM ;   //��������
    AnsiString STRWHERE ; //������
}KSD29;

//�f�ޑ���f�[�^
extern struct structKD_1{
	AnsiString KENSA_YMD; 		//�����\��N����
	AnsiString TOLEY_NO;  		//�g���[�m��
	AnsiString SAMPLE_P;  		//�T���v���|�W�V����
	AnsiString SOKUTEI_SU;		//���萔
	AnsiString DTKSHIN; 		//���Ӑ�i��
	AnsiString LOTNO; 			//���b�gNO
	AnsiString HINBAN;
	AnsiString ZISCOD;
	AnsiString ZISNAM;
	AnsiString KIKA_NUM1;
	AnsiString KIKA_NUM2;
	AnsiString KIKA_SUB1;
	AnsiString KIKA_SUB2;
	AnsiString KEIJYO_KBN;
	AnsiString SOKUTEI[100];
	AnsiString SOKUTEI_NM;
	AnsiString SOKUTE_AVE;
	AnsiString ADDYMD;
	AnsiString ADDTIM;
	AnsiString UPDYMD;
	AnsiString UPDTIM;
	AnsiString UPDCHR;
	AnsiString UPDCNT;
	AnsiString MEMO;
	AnsiString SOKUTE_MAX;
	AnsiString SOKUTE_MIN;
	AnsiString SOKUTE_OK;
	AnsiString SKTYMD; 			// �����
}KD_1;

//�f�ޑ�����уf�[�^
extern struct structKSD21{
	int 	   InsFlag; 		// �V�K�̏ꍇ�F-1
	AnsiString DTKSHIN; 		// ���Ӑ�i��
	AnsiString LOTNO; 			// ���b�gNO
	AnsiString HINBAN; 			// ���Еi��
	AnsiString DTKSCOD; 		// ���Ӑ�R�[�h
	AnsiString DTKSNAM; 		// ���Ӑ於��
	AnsiString ZISNAM; 			// �ގ����́i�i��j
	AnsiString SOKUTEI_NUM; 	// ���荀�ڐ�
	AnsiString SOZAI_OK; 		// �f�ޔ���
	AnsiString MEMO; 			// ���l
	AnsiString SKTYMD; 			// �����
	AnsiString ADDYMD; 			// �o�^��
	AnsiString ADDTIM; 			// �o�^����
	AnsiString UPDYMD; 			// �ύX��
	AnsiString UPDTIM; 			// �ύX����
	AnsiString UPDCHR; 			// �X�V��
	AnsiString UPDCNT; 			// �X�V��
}KSD21;


//�f�ޑ�����і��׃f�[�^
extern struct structKSD22{
	int 	   InsFlag; 		// �V�K�̏ꍇ�F-1
	AnsiString DTKSHIN; 		// ���Ӑ�i��
	AnsiString LOTNO; 			// ���b�gNO
	AnsiString UNQ_NO; 			// ����NO
	AnsiString KOMK_NO; 		// ���荀��NO
	AnsiString KOMK_NM; 		// ���荀�ږ���
	AnsiString KOMK_ENG; 		// ���荀�ږ��́i�p��j
	AnsiString KOMK_SUB; 		// ���荀�ڃT�u����
	AnsiString KOMK_SUB_ENG; 	// ���荀�ڃT�u���́i�p��j
	AnsiString KIKI_NO; 		// ����@��NO
	AnsiString KIKI_NM; 		// ����@�햼��
	AnsiString TANI; 			// �P��
	AnsiString KIKA_TYPE; 		// �K�i�^�C�v
	AnsiString KIKA_KIND; 		// �K�i���
	AnsiString KIKA_DECI; 		// �K�i�����_�ȉ�����
	AnsiString KIKA_NUM1; 		// �K�i�l1
	AnsiString KIKA_NUM2; 		// �K�i�l2
	AnsiString KIKA_NUM3; 		// �K�i�l3
	AnsiString KIKA_STR; 		// �K�i�l����
	AnsiString KIKA_SUB1; 		// �K�i�l�T�u1
	AnsiString KIKA_SUB2; 		// �K�i�l�T�u2
	AnsiString SOKU_SU; 		// ����w��n��
	AnsiString VALUE_TYPE; 		// ����l�\��
	AnsiString VALUE_DECI; 		// ����l�����_�ȉ�����
	AnsiString SOKU_VAL[100]; 	// ����l
	//AnsiString SOKU_VAL01; 		// ����l1
	//AnsiString SOKU_VAL02; 		// ����l2
	//AnsiString SOKU_VAL03; 		// ����l3
	//AnsiString SOKU_VAL04; 		// ����l4
	//AnsiString SOKU_VAL05; 		// ����l5
	//AnsiString SOKU_VAL06; 		// ����l6
	//AnsiString SOKU_VAL07; 		// ����l7
	//AnsiString SOKU_VAL08; 		// ����l8
	//AnsiString SOKU_VAL09; 		// ����l9
	//AnsiString SOKU_VAL10; 		// ����l10
	AnsiString SOKU_VAL_SU;		// �������n��
	AnsiString SOKU_VAL_AVE; 	// ���蕽�ϒl
	AnsiString SOKU_VAL_MAX; 	// ����ő�l
	AnsiString SOKU_VAL_MIN;	// ����ŏ��l
	AnsiString SOKU_OK; 		// ����l����
	AnsiString SKTYMD; 			// �����
	AnsiString ADDYMD; 			// �o�^��
	AnsiString ADDTIM; 			// �o�^����
	AnsiString UPDYMD; 			// �ύX��
	AnsiString UPDTIM; 			// �ύX����
	AnsiString UPDCHR; 			// �X�V��
	AnsiString UPDCNT; 			// �X�V��
	AnsiString HINBAN;          // ���Еi��
}KSD22;

//�f�ޑ�����ї�O�f�[�^
extern struct structKSD23{
	int 	   InsFlag; 		// �V�K�̏ꍇ�F-1
//	AnsiString DTKSHIN; 		// ���Ӑ�i��
//	AnsiString LOTNO; 			// ���b�gNO
//	AnsiString UNQ_NO; 			// ����NO
//	AnsiString SOKU_NO; 		// ����NO
//	AnsiString SOKU_VAL; 		// ����l
}KSD23;

//�Œ蕶����
extern struct structFixStr{
	AnsiString TABLE1;
	AnsiString TABLE2;
	AnsiString KOMK_NO;
	AnsiString ORDER_NO;
	AnsiString KOMK_NM;
	AnsiString KOMK_ENG;
	AnsiString KIKI_NO;
	AnsiString KIKI_NM;
	AnsiString TANI[4];
	AnsiString KIKA_TYPE;
	AnsiString KIKA_KIND;
	AnsiString KIKA_DECI;
	AnsiString KIKA_NUM2;
	AnsiString KIKA_NUM3;
	AnsiString KIKA_STR;
	AnsiString SOKU_FLG;
	AnsiString TOKU_FLG;
	AnsiString KIKA_PRT;
	AnsiString VALUE_TYPE;
	AnsiString VALUE_DECI;
	AnsiString F_SOKUTE_KBN;
	AnsiString F_KIKA_NUM1;
	AnsiString F_KIKA_NUM2;
	AnsiString F_KIKA_SUB1;
	AnsiString F_KIKA_SUB2;
	AnsiString F_KEIJYO_KBN;
	AnsiString F_SOKUTEI_1;
	AnsiString F_SOKUTEI_2;
	AnsiString F_SOKUTEI_SU;
	AnsiString F_SOKUTEI_NM;
	AnsiString F_SOKUTE_AVE;
	AnsiString F_SOKUTEICHI;
	AnsiString W_SOKUTE_KBN;
} FixStr[16];
extern int FixStrNum;

extern AnsiString MEMOStr[16];

extern AnsiString sBufSQL;

//�f�ޑ�����уf�[�^�iKSD21�j��
//�X�V�񐔁E�f�ޑ���X�V�ɕK�v�ȃL�[��ۑ�
extern TStrings *sDTKSHIN;    	//���Ӑ�i��
extern TStrings *sLOTNO; 		//���b�gNO
extern TStrings *sHINBAN; 		//���Еi��       //onishi
extern int isDTKSHINNum;        //�f�[�^��

#endif






