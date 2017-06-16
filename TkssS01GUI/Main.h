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
	AnsiString FUNC_ID ;  // ����NO
    AnsiString UPDYMD ;   // �������t
    AnsiString UPDTIM ;   // ��������
    AnsiString STRWHERE ; // ������
}KSD29;

//�f�ޑ���f�[�^
extern struct structKD_1{
	AnsiString KENSA_YMD; 		// �����\��N����
	AnsiString TOLEY_NO;  		// �g���[�m��
	AnsiString SAMPLE_P;  		// �T���v���|�W�V����
	AnsiString SOKUTEI_SU;		// ���萔
	AnsiString DTKSHIN; 		// ���Ӑ�i��
	AnsiString LOTNO; 			// ���b�gNO
	AnsiString HINBAN;			// �i��
	AnsiString ZISCOD;			// �ގ��R�[�h
	AnsiString ZISNAM;			// �ގ���
	AnsiString KIKA_NUM1;		// �K�i1�i���� ��t��R�F����j
	AnsiString KIKA_NUM2;		// �K�i2�i��� ��t��R�F�d���j
	AnsiString KIKA_SUB1;		// �K�i�T�u1�i ��t��R�F����   ��t���x�F���x ��R���F�d�� �Ȃ��F�X�p���j
	AnsiString KIKA_SUB2;		// �K�i�T�u1�i ��t��R�F�^�C�v ��t���x�F�P��              �Ȃ��F�P�ʁj
	AnsiString KEIJYO_KBN;		// �`��敪
	AnsiString SOKUTEI[100];	// ����l
	AnsiString SOKUTEI_NM;		// ���萔
	AnsiString SOKUTE_AVE;		// ���ϒl
	AnsiString ADDYMD;			// �o�^��
	AnsiString ADDTIM;			// �o�^����
	AnsiString UPDYMD;			// �ύX��
	AnsiString UPDTIM;			// �ύX����
	AnsiString UPDCHR;			// �X�V��
	AnsiString UPDCNT;			// �X�V��
	AnsiString MEMO;			// ���l
	AnsiString SOKUTE_MAX;		// �ő�l
	AnsiString SOKUTE_MIN;		// �ŏ��l
	AnsiString SOKUTE_OK;		// ����
	AnsiString SKTYMD; 			// �����
        //20170417 Y.Onishi �H��敪�ǉ�
        AnsiString KOJOKBN; 			// �H��敪
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
	AnsiString HINBAN; 			// ���Еi��
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

//�e�f�ނ̌Œ蕶����
extern struct structFixStr{
	AnsiString TABLE1;			// �e�[�u����
	AnsiString TABLE2;			// ��O�e�[�u����
	AnsiString KOMK_NO;			// ���荀��No
	AnsiString ORDER_NO;		// �\����
	AnsiString KOMK_NM;			// ���荀�ږ���
	AnsiString KOMK_ENG;		// ���荀�ږ��́i�p��j
	AnsiString KIKI_NO;			// ����@��No
	AnsiString KIKI_NM;			// ����@�햼��
	AnsiString TANI[5];			// �P��
	AnsiString KIKA_TYPE;		// �K�i�^�C�v
	AnsiString KIKA_KIND;		// �K�i���
	AnsiString KIKA_DECI;		// �K�i�����_�ȉ�����
	AnsiString KIKA_NUM2;		// �K�i�l�Q
	AnsiString KIKA_NUM3;		// �K�i�l�R
	AnsiString KIKA_STR;		// �K�i�l����
	AnsiString SOKU_FLG;		// ���荀�ڂ̗L��
	AnsiString TOKU_FLG;		// ���ʍ��ڂ̗L��
	AnsiString KIKA_PRT;		// ����E�����l�̈��
	AnsiString VALUE_TYPE;		// ����l�\��
	AnsiString VALUE_DECI;		// ����l�����_�ȉ�����
	AnsiString F_SOKUTE_KBN;	// �t�B�[���h���F����敪
	AnsiString F_KIKA_NUM1;		// �t�B�[���h���F�K�i�l�P
	AnsiString F_KIKA_NUM2;		// �t�B�[���h���F�K�i�l�Q
	AnsiString F_KIKA_SUB1;		// �t�B�[���h���F�K�i�l�T�u�P
	AnsiString F_KIKA_SUB2;		// �t�B�[���h���F�K�i�l�T�u�Q
	AnsiString F_KEIJYO_KBN;	// �t�B�[���h���F�`��敪
	AnsiString F_SOKUTEI_1;		// �t�B�[���h���F����l�P
	AnsiString F_SOKUTEI_2;		// �t�B�[���h���F����l�Q
	AnsiString F_SOKUTEI_SU;	// �t�B�[���h���F����w����
	AnsiString F_SOKUTEI_NM;	// �t�B�[���h���F������ѐ�
	AnsiString F_SOKUTE_AVE;	// �t�B�[���h���F����l ����
	AnsiString F_SOKUTEICHI;	// �t�B�[���h���F����l
	AnsiString W_SOKUTE_KBN;	// �t�B�[���h���F����敪
} FixStr[18];
extern int FixStrNum;			// �Œ蕶����̔z�� 16

extern AnsiString MEMOStr[18];  // �e����l�̔��l

extern AnsiString sBufSQL;      // �o�b�t�@ SQL��

//�f�ޑ�����уf�[�^�iKSD21�j��
//�X�V�񐔁E�f�ޑ���X�V�ɕK�v�ȃL�[��ۑ�
extern TStrings *sDTKSHIN;    	// ���Ӑ�i��
extern TStrings *sLOTNO; 		// ���b�gNO
extern TStrings *sHINBAN; 		// ���Еi��
extern int isDTKSHINNum;		// �f�[�^��

#endif







