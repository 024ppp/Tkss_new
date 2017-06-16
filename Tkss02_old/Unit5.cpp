//---------------------------------------------------------------------------
//
//  Unit5.cpp
//    �y�o�׌����V�X�e���|���|�[�g�o�́z
//    ���C���t�H�[���iTForm1�N���X�j�̃����o�֐��̒�`
//
//  �쐬��
//    �����@�b��
//
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit5.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)


//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�w�肳�ꂽ�͈͎w��̃��b�gNO�̗L�����b�gNO��₢���킹�܂�
//
//  �@�\����
//    �w�肵���J�n���b�g�ƏI�����b�g�̑���ς݃��b�g���X�g���擾���܂��B
//    �����܂������b�g�͈͎̔w��ɑΉ����Ă��܂�
//
//  �p�����^����
//    AnsiString sDTKSHIN�F��\���Ӑ�i��
//    AnsiString sLOT_S	�F�J�n���b�gNO
//    AnsiString sLOT_E	�F�I�����b�gNO
//
//  �߂�l
//    AnsiString		�F�J���}�ŋ�؂�ꂽ���b�gNO���X�g�̕�������������܂�
//                        ['LOTNO1','LOTNO2',]�Ɩ߂�܂�
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::GetLotList2(AnsiString sDTKSHIN, AnsiString sLOT_S, AnsiString sLOT_E)
{
	AnsiString sBuf;
	AnsiString sRet;

	if( sLOT_S.Trim() == "" || sLOT_E.Trim() == "" ) return( "" );

	sBuf = "SELECT LOTBNG FROM SD21S";
	sBuf += " WHERE DTKSHIN = '" + sDTKSHIN + "'";

    if( iLOT_LENGTH == 5 ){
	    // �������b�g�i5���j�ɑΉ�
    	sBuf += " AND SUBSTR(LOTBNG,2) >= '" + sLOT_S.SubString(2,5) + "'";
	    sBuf += " AND SUBSTR(LOTBNG,2) <= '" + sLOT_E.SubString(2,5) + "'";
        sBuf += " AND DENYMD >= '" + Edt_SEIKAN_YMD->Text + "'";      //onishi
	    sBuf += " ORDER BY SUBSTR(LOTBNG,2)";
	} else {
	    // �C�O���b�g�i6���j�ɑΉ�
    	sBuf += " AND LOTBNG >= '" + sLOT_S + "'";
	    sBuf += " AND LOTBNG <= '" + sLOT_E + "'";
        sBuf += " AND DENYMD >= '" + Edt_SEIKAN_YMD->Text + "'";      //onishi
	    sBuf += " ORDER BY LOTBNG";
	}

	// Initial Query
	Query3->Close();
	Query3->SQL->Clear();
	Query3->SQL->Add(sBuf);
	Query3->Open();
	Query3->Active = true;
        sRet = "";
	while(Query3->Eof == false) {

        if( !VarIsNull(Query3->FieldValues["LOTBNG"]) ){
            sRet += "'" + AnsiString(Query3->FieldValues["LOTBNG"]) + "',";
        }
	    Query3->Next();
	}
	Query3->Close();

	return( sRet );

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�ȑO�̃��b�g�̒l���擾����
//
//  �@�\����
//	  �ȑO ���肵�����b�g�̒l���擾���܂�
//    �i���b�g�̍��ڂ����肵�Ȃ��ɐݒ肵�Ă���ꍇ�Ɏg�p���܂��j
//
//  �p�����^����
//    AnsiString sSrchDTKSHIN		�F���������i���Ӑ�i�ԁj
//    AnsiString sSrchLOTNO		    �F���������i���b�gNo�j
//    AnsiString sSrchKOMK_NM		�F���������i���荀�ږ��́j
//    AnsiString sSrchKOMK_SUB		�F���������i���荀�ڃT�u���́j
//    AnsiString sSrchHINBAN_SK		�F���������i�i�ԁj
//    int		 iSrchKIKI_NO		�F���������i����@��No�j
//    int		 iSrchKOMK_NO		�F���������i���荀��No�j
//    AnsiString sSrchTANI          �F���������i�P�ʁj
//    AnsiString sReSOKU_SU         �FOUT����  ����w��n��
//    AnsiString sReKIKA_PRT        �FOUT����  ��������l�̈��
//    AnsiString sReVALUE_TYPE      �FOUT����  ����l�\��
//    AnsiString sReVALUE_DECI      �FOUT����  ����l�����_�ȉ�����
//    AnsiString sReDISP_VAL_SU     �FOUT����  ����p�������n��
//    AnsiString sReDISP_VAL_AVE    �FOUT����  ����p���蕽�ϒl
//    AnsiString sReDISP_VAL_MAX    �FOUT����  ����p����ő�l
//    AnsiString sReDISP_VAL_MIN    �FOUT����  ����p����ŏ��l
//    AnsiString sReDISP_OK         �FOUT����  ����p����l����
//    TStrings *sReDISP_VAL         �FOUT����  ���荀��
//
//  �߂�l
//    int						    �F���荀�ڐ��i��������0���̏ꍇ��-1��߂��܂��j
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
int  __fastcall TForm1::GetBeforeLotVal(AnsiString sSrchDTKSHIN, AnsiString sSrchLOTNO,
										AnsiString sSrchKOMK_NM, AnsiString sSrchKOMK_SUB,
										AnsiString sSrchHINBAN_SK, int iSrchKIKI_NO, int iSrchKOMK_NO,
                                        AnsiString sSrchTANI,
										AnsiString *sReSOKU_SU, AnsiString *sReKIKA_PRT,
										AnsiString *sReVALUE_TYPE,
										AnsiString *sReVALUE_DECI, AnsiString *sReDISP_VAL_SU,
										AnsiString *sReDISP_VAL_AVE, AnsiString *sReDISP_VAL_MAX,
										AnsiString *sReDISP_VAL_MIN, AnsiString *sReDISP_OK,
										TStrings *sReDISP_VAL )
{
	int iRtnVal;
    int iLotLen;
    int i;
    int n;
    AnsiString sBufSQL;
	AnsiString sBufSOKUVAL[10];

    iRtnVal = -1;
    iLotLen = sSrchLOTNO.Length();
	*sReVALUE_DECI = "0";
	*sReDISP_VAL_SU = "0";
	*sReDISP_VAL_AVE = "0";
	*sReDISP_VAL_MAX = "0";
	*sReDISP_VAL_MIN = "0";
	*sReDISP_OK = "0";
    sReDISP_VAL->Clear();

    //Q_BLOTVAL
    //KSD02����f�[�^���擾
	sBufSQL = "SELECT * FROM KSD02";
    //�������� �쐬
	sBufSQL +=  " WHERE SKB_NO <> 9 AND SOKU_FLG = 1 ";
	sBufSQL += " AND DISP_VAL_SU > 0 ";
	sBufSQL += " AND DTKSHIN ='" + sSrchDTKSHIN + "'";
	//LOTNO
	if( iLotLen == 5 ){
		sBufSQL += " AND SUBSTR(LOTNO,2) <'" + sSrchLOTNO.SubString(2,5) + "'";
	} else {
		sBufSQL += " AND LOTNO <'" + sSrchLOTNO + "'";
	}
    //KOMK_NM
    if ( Trim(sSrchKOMK_NM) == "" ) {
		sBufSQL += " AND KOMK_NM Is Null ";
    } else {
		sBufSQL += " AND KOMK_NM ='"   + sSrchKOMK_NM + "'";
    }
    //KOMK_SUB
    if ( Trim(sSrchKOMK_SUB) == "" ) {
		sBufSQL += " AND KOMK_SUB Is Null ";
    } else {
		sBufSQL += " AND KOMK_SUB ='"  + sSrchKOMK_SUB + "'";
    }
    // 2003/10/21 A.Tamura������TANI�͂���Ȃ��́H
    //TANI
    if ( Trim(sSrchTANI) == "" ) {
		sBufSQL += " AND TANI Is Null ";
    } else {
		sBufSQL += " AND TANI ='"  + sSrchTANI + "'";
    }

    //HINBAN_SK
    if ( Trim(sSrchHINBAN_SK) == "" ) {
		sBufSQL += " AND HINBAN_SK Is Null ";
    } else {
		sBufSQL += " AND HINBAN_SK ='"  + sSrchHINBAN_SK + "'";
    }
	sBufSQL += " AND KIKI_NO ="    + IntToStr(iSrchKIKI_NO);
	sBufSQL += " AND KOMK_NO ="    + IntToStr(iSrchKOMK_NO);

	//�\�[�g
	if( iLotLen == 5 ){
		sBufSQL += " ORDER BY SUBSTR(LOTNO,2) DESC";
	} else {
		sBufSQL += " ORDER BY LOTNO DESC";
	}

	Q_BLOTVAL->Close();
	Q_BLOTVAL->SQL->Clear();
	Q_BLOTVAL->SQL->Add(sBufSQL);
	Q_BLOTVAL->Open();
	Q_BLOTVAL->Active = true;
    if ( Q_BLOTVAL->Eof == true ) {
        return(iRtnVal);
    }

    //2003/11/25 E.Takase �uatoi�v�͂܂������I
	//*sReSOKU_SU 	 = AnsiString(atoi(Null_S(Q_BLOTVAL->FieldValues["SOKU_SU"]).c_str()));
	//*sReKIKA_PRT 	 = AnsiString(atoi(Null_S(Q_BLOTVAL->FieldValues["KIKA_PRT"]).c_str()));
	//*sReVALUE_TYPE 	 = AnsiString(atoi(Null_S(Q_BLOTVAL->FieldValues["VALUE_TYPE"]).c_str()));
	//*sReVALUE_DECI 	 = AnsiString(atoi(Null_S(Q_BLOTVAL->FieldValues["VALUE_DECI"]).c_str()));
	//*sReDISP_VAL_SU  = AnsiString(atoi(Null_S(Q_BLOTVAL->FieldValues["DISP_VAL_SU"]).c_str()));
	//*sReDISP_VAL_AVE = AnsiString(atoi(Null_S(Q_BLOTVAL->FieldValues["DISP_VAL_AVE"]).c_str()));
	//*sReDISP_VAL_MAX = AnsiString(atoi(Null_S(Q_BLOTVAL->FieldValues["DISP_VAL_MAX"]).c_str()));
	//*sReDISP_VAL_MIN = AnsiString(atoi(Null_S(Q_BLOTVAL->FieldValues["DISP_VAL_MIN"]).c_str()));
	//*sReDISP_OK		 = AnsiString(atoi(Null_S(Q_BLOTVAL->FieldValues["DISP_OK"]).c_str()));
	*sReSOKU_SU 	 = AnsiString(Null_S(Q_BLOTVAL->FieldValues["SOKU_SU"]));
	*sReKIKA_PRT 	 = AnsiString(Null_S(Q_BLOTVAL->FieldValues["KIKA_PRT"]));
	*sReVALUE_TYPE 	 = AnsiString(Null_S(Q_BLOTVAL->FieldValues["VALUE_TYPE"]));
	*sReVALUE_DECI 	 = AnsiString(Null_S(Q_BLOTVAL->FieldValues["VALUE_DECI"]));
	*sReDISP_VAL_SU  = AnsiString(Null_S(Q_BLOTVAL->FieldValues["DISP_VAL_SU"]));
	*sReDISP_VAL_AVE = AnsiString(Null_S(Q_BLOTVAL->FieldValues["DISP_VAL_AVE"]));
	*sReDISP_VAL_MAX = AnsiString(Null_S(Q_BLOTVAL->FieldValues["DISP_VAL_MAX"]));
	*sReDISP_VAL_MIN = AnsiString(Null_S(Q_BLOTVAL->FieldValues["DISP_VAL_MIN"]));
	*sReDISP_OK		 = AnsiString(Null_S(Q_BLOTVAL->FieldValues["DISP_OK"]));

	//���萔,
	iRtnVal = atoi((Null_S(Q_BLOTVAL->FieldValues["DISP_VAL_SU"])).c_str());

	if ( iRtnVal > 10 ) {
		n = 10;
	} else {
		n = iRtnVal;
	}

	//����l1,�E�E�E�E
	for ( i = 0; i < n; i++ ) {
        sReDISP_VAL->Add(Null_S(Q_BLOTVAL->FieldValues["DISP_VAL" + FormatFloat("00",i+1)]));
	}

	//���萔��10�`�Ȃ��O�e�[�u�����瑪��l�擾
	if ( iRtnVal > 10 ) {
		sBufSQL = "SELECT * FROM KSD03";
		sBufSQL += " WHERE DTKSHIN ='" + Null_S(Q_BLOTVAL->FieldValues["DTKSHIN"]) + "'";
		sBufSQL += " AND LOTNO = '" + Null_S(Q_BLOTVAL->FieldValues["LOTNO"]) + "'";
		sBufSQL += " AND UNQ_NO = " + Null_S(Q_BLOTVAL->FieldValues["UNQ_NO"]);
		sBufSQL += " ORDER BY SOKU_NO";
		Q_BLOTVAL2->Close();
		Q_BLOTVAL2->SQL->Clear();
		Q_BLOTVAL2->SQL->Add(sBufSQL);
		Q_BLOTVAL2->Open();
		Q_BLOTVAL2->Active = true;
		while(Q_BLOTVAL2->Eof == false) {
        	sReDISP_VAL->Add(Null_S(Q_BLOTVAL->FieldValues["DISP_VAL"]));
			Q_BLOTVAL2->Next();
		}
	}

     return(iRtnVal);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�w�肳�ꂽ���b�gNO���X�g���烏�[�N�e�[�u�����쐬
//
//  �@�\����
//    �w�肵�����b�gNO���X�g�����������ɂ��ă��[�N�e�[�u���Ƀf�[�^���Z�b�g���܂��B
//
//  �p�����^����
//    AnsiString sDTKSHIN�F��\���Ӑ�i��
//    AnsiString sLOT	�F���b�gNO���X�g�i�J���}��؂�j
//
//  �߂�l
//    bool				�Ftrue=�f�[�^�쐬�����Afalse=�f�[�^�쐬���s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::KSDCreateData(AnsiString sDTKSHIN, AnsiString sLOT)
{
	AnsiString sBufSQL;
	AnsiString sBufSQL2;
	bool bRet;
	int iCol;

   	bool bRtn;
    AnsiString sReDTKSHIN;
    AnsiString sReLOT;
    AnsiString sReSKB_NO;
    AnsiString sReKOMK_NO;
    AnsiString sReUNQ_NO;




    //��������������������������������������������������������������������������
    //�@�z�X�g���擾
	char tmpHostName[256];
	unsigned long CPUname_MaxLength = 256;
	if(GetComputerName( tmpHostName, &CPUname_MaxLength ) ){
		HostName = AnsiString(tmpHostName);
	}

    //��������������������������������������������������������������������������
	//�A���[�N�e�[�u����������
    //�A-1 KSD01W
	// Initial Query
	Q_WORK->Close();
	Q_WORK->SQL->Clear();
	// �⍇�����쐬
	sBufSQL = "delete from KSD01W where PCNAME='" + HostName + "'";
	Q_WORK->SQL->Add(sBufSQL);

	// �₢�������̎��s
	try
	{
		Q_WORK->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		ShowMessage(e.Message);
		return(false);
	}
	catch(Exception& e)
	{
		ShowMessage(e.Message);
		return(false);
	}

    //��������������������������������������������������������������������������
    //�A-2 KSD02W
	// Initial Query
	Q_WORK->Close();
	Q_WORK->SQL->Clear();
	// �⍇�����쐬
	sBufSQL = "delete from KSD02W where PCNAME='" + HostName + "'";
	Q_WORK->SQL->Add(sBufSQL);

	// �₢�������̎��s
	try
	{
		Q_WORK->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		ShowMessage(e.Message);
		return(false);
	}
	catch(Exception& e)
	{
		ShowMessage(e.Message);
		return(false);
	}

    //��������������������������������������������������������������������������
    //�A-3 KSD03W
	// Initial Query
	Q_WORK->Close();
	Q_WORK->SQL->Clear();
	// �⍇�����쐬
	sBufSQL = "delete from KSD03W where PCNAME='" + HostName + "'";
	Q_WORK->SQL->Add(sBufSQL);

	// �₢�������̎��s
	try
	{
		Q_WORK->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		ShowMessage(e.Message);
		return(false);
	}
	catch(Exception& e)
	{
		ShowMessage(e.Message);
		return(false);
	}

    //���b�g�Ɍ��������ɃZ�b�g����Ă��Ȃ����͏I��
	if( sLOT.Trim() == "" ) return( false );

/*
    //��������������������������������������������������������������������������
	//�B���[�N�e�[�u�����쐬���Ă����܂�
    //�B-1 �܂��AKSD01W�`KSD03W�܂ŕK�v�ȃ��b�g�Řg�g�݂����
	// Initial Query
	Q_WORK->Close();
	Q_WORK->SQL->Clear();
	// �⍇�����쐬
    sBufSQL = "";
	sBufSQL += " INSERT INTO KSD01W ( ";
	sBufSQL += " PCNAME, DTKSHIN, LOTNO ";
	sBufSQL += " ) ";
	sBufSQL += " SELECT '" + HostName + "' AS PCNAME, DTKSHIN, LOTNO ";
	sBufSQL += " FROM KSD01 ";
	sBufSQL += " WHERE DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND LOTNO IN (" + sLOT + ")";
	sBufSQL += " UNION ";
	sBufSQL += " SELECT '" + HostName + "' AS PCNAME, DTKSHIN, LOTNO ";
	sBufSQL += " FROM KSD21 ";
	sBufSQL += " WHERE DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND LOTNO IN (" + sLOT + ")";
	sBufSQL += " UNION ";
	sBufSQL += " SELECT '" + HostName + "' AS PCNAME, DTKSHIN, LOTBNG AS LOTNO ";
	sBufSQL += " FROM SD21S ";
	sBufSQL += " WHERE DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND LOTBNG IN (" + sLOT + ")";

	Q_WORK->SQL->Add(sBufSQL);
	// �₢�������̎��s
	try
	{
		Q_WORK->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		ShowMessage(e.Message);
		return(false);
	}
	catch(Exception& e)
	{
		ShowMessage(e.Message);
		return(false);
	}


*/

    //��������������������������������������������������������������������������
	//�B������уf�[�^(KSD0�V���[�Y)���[�N�e�[�u�����쐬���Ă����܂�
    //�B-1 KSD01 �� KSD01W
	// Initial Query
	Q_WORK->Close();
	Q_WORK->SQL->Clear();
	// �⍇�����쐬
    sBufSQL = "";
	sBufSQL += " INSERT INTO KSD01W ( ";
	sBufSQL += " PCNAME, DTKSHIN, LOTNO, HINBAN, DTKSCOD, DTKSNAM, ZISNAM, HINMEI, ";
	sBufSQL += " DTKSHIN1_SZ, DTKSHIN2_SZ, DTKSHIN3_SZ, DTKSHIN4_SZ, DTKSHIN5_SZ, ";
	sBufSQL += " DTKSHIN6_SZ, LOT_LINK_SZ, SOKUTEI_NUM, SOZAI_OK, SOZAI_OK_PRT, SYUKA_OK, ";
	sBufSQL += " SYUKA_OK_PRT, OUT_TITLE1, OUT_TITLE2, OUT_TITLE3, OUT_TITLE4, OUT_TITLE5, ";
	sBufSQL += " OUT_TITLE6, OUT_TITLE7, OUT_TITLE8, X_OUT, MEMO, SKTYMD, SKTYMD_PRT, ";
	sBufSQL += " ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT, LOTNO1_SZ, LOTNO2_SZ, ";
	sBufSQL += " LOTNO3_SZ, LOTNO4_SZ, LOTNO5_SZ, LOTNO6_SZ, SKTYMD_SZ, SKTYMD_SZ_PRT ) ";

	sBufSQL += " SELECT '" + HostName + "' AS PCNAME, DTKSHIN, LOTNO, HINBAN,  ";
	sBufSQL += " DTKSCOD, DTKSNAM, ZISNAM, HINMEI, DTKSHIN1_SZ,  ";
	sBufSQL += " DTKSHIN2_SZ, DTKSHIN3_SZ, DTKSHIN4_SZ, DTKSHIN5_SZ,  ";
	sBufSQL += " DTKSHIN6_SZ, LOT_LINK_SZ, SOKUTEI_NUM, SOZAI_OK,  ";
	sBufSQL += " SOZAI_OK_PRT, SYUKA_OK, SYUKA_OK_PRT, OUT_TITLE1,  ";
	sBufSQL += " OUT_TITLE2, OUT_TITLE3, OUT_TITLE4, OUT_TITLE5,  ";
	sBufSQL += " OUT_TITLE6, OUT_TITLE7, OUT_TITLE8, X_OUT, MEMO,  ";
	sBufSQL += " SKTYMD, SKTYMD_PRT, ADDYMD, ADDTIM, UPDYMD, UPDTIM,  ";
	sBufSQL += " UPDCHR, UPDCNT, LOTNO1_SZ, LOTNO2_SZ, LOTNO3_SZ, LOTNO4_SZ,  ";
	sBufSQL += " LOTNO5_SZ, LOTNO6_SZ, SKTYMD_SZ, SKTYMD_SZ_PRT ";
	sBufSQL += " FROM KSD01 ";
	sBufSQL += " WHERE DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND   LOTNO IN (" + sLOT + ")";
    sBufSQL += " AND   SKTYMD >= '" + Form1->Edt_SEIKAN_YMD->Text + "'";      //onishi

	Q_WORK->SQL->Add(sBufSQL);
	// �₢�������̎��s
	try
	{
		Q_WORK->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		ShowMessage(e.Message);
		return(false);
	}
	catch(Exception& e)
	{
		ShowMessage(e.Message);
		return(false);
	}


    //��������������������������������������������������������������������������
    //�B-2 KSD02 �� KSD02W
	// Initial Query
	Q_WORK->Close();
	Q_WORK->SQL->Clear();
	// �⍇�����쐬
    sBufSQL = "";
	sBufSQL += " INSERT INTO KSD02W ( ";
	sBufSQL += " PCNAME, DTKSHIN, LOTNO, UNQ_NO, ORDER_NO, SKB_NO, HINBAN_SK, KOMK_NO, ";
	sBufSQL += " KOMK_NM, KOMK_ENG, KOMK_SUB, KOMK_SUB_ENG, KIKI_NO, KIKI_NM, TANI, ";
	sBufSQL += " KIKA_TYPE, KIKA_KIND, KIKA_DECI, KIKA_NUM1, KIKA_NUM2, KIKA_NUM3, ";
	sBufSQL += " KIKA_STR, KIKA_SUB1, KIKA_SUB2, KIKA_SUB3, SOKU_SU, SOKU_FLG, TOKU_FLG, ";
	sBufSQL += " KIKA_PRT, VALUE_TYPE, VALUE_DECI, SOKU_VAL01, SOKU_VAL02, SOKU_VAL03, ";
	sBufSQL += " SOKU_VAL04, SOKU_VAL05, SOKU_VAL06, SOKU_VAL07, SOKU_VAL08, SOKU_VAL09, ";
	sBufSQL += " SOKU_VAL10, SOKU_VAL_SU, SOKU_VAL_AVE, SOKU_VAL_MAX, SOKU_VAL_MIN, SOKU_OK, ";
	sBufSQL += " DISP_VAL01, DISP_VAL02, DISP_VAL03, DISP_VAL04, DISP_VAL05, DISP_VAL06, ";
	sBufSQL += " DISP_VAL07, DISP_VAL08, DISP_VAL09, DISP_VAL10, DISP_VAL_SU, DISP_VAL_AVE, ";
	sBufSQL += " DISP_VAL_MAX, DISP_VAL_MIN, DISP_OK, SKTYMD, ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT ) ";
	sBufSQL += " SELECT '" + HostName + "'  AS PCNAME, DTKSHIN, LOTNO, UNQ_NO, ORDER_NO, SKB_NO, HINBAN_SK, ";
	sBufSQL += " KOMK_NO, KOMK_NM, KOMK_ENG, KOMK_SUB, KOMK_SUB_ENG, KIKI_NO, KIKI_NM, TANI, KIKA_TYPE, ";
	sBufSQL += " KIKA_KIND, KIKA_DECI, KIKA_NUM1, KIKA_NUM2, KIKA_NUM3, KIKA_STR, KIKA_SUB1, KIKA_SUB2, ";
	sBufSQL += " KIKA_SUB3, SOKU_SU, SOKU_FLG, TOKU_FLG, KIKA_PRT, VALUE_TYPE, VALUE_DECI, SOKU_VAL01, ";
	sBufSQL += " SOKU_VAL02, SOKU_VAL03, SOKU_VAL04, SOKU_VAL05, SOKU_VAL06, SOKU_VAL07, SOKU_VAL08, ";
	sBufSQL += " SOKU_VAL09, SOKU_VAL10, SOKU_VAL_SU, SOKU_VAL_AVE, SOKU_VAL_MAX, SOKU_VAL_MIN, SOKU_OK, ";
	sBufSQL += " DISP_VAL01, DISP_VAL02, DISP_VAL03, DISP_VAL04, DISP_VAL05, DISP_VAL06, DISP_VAL07, ";
	sBufSQL += " DISP_VAL08, DISP_VAL09, DISP_VAL10, DISP_VAL_SU, DISP_VAL_AVE, DISP_VAL_MAX, DISP_VAL_MIN, ";
	sBufSQL += " DISP_OK, SKTYMD, ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT";
	sBufSQL += " FROM KSD02 ";
	sBufSQL += " WHERE DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND   LOTNO IN (" + sLOT + ")";
    sBufSQL += " AND   SKTYMD >= '" + Form1->Edt_SEIKAN_YMD->Text + "'";      //onishi

	Q_WORK->SQL->Add(sBufSQL);
	// �₢�������̎��s
	try
	{
		Q_WORK->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		ShowMessage(e.Message);
		return(false);
	}
	catch(Exception& e)
	{
		ShowMessage(e.Message);
		return(false);
	}

    //��������������������������������������������������������������������������
    //�B-3 KSD03 �� KSD03W
	// Initial Query
	Q_WORK->Close();
	Q_WORK->SQL->Clear();
	// �⍇�����쐬
    sBufSQL = "";
	sBufSQL += " INSERT INTO KSD03W ( ";
	sBufSQL += " PCNAME, DTKSHIN, LOTNO, UNQ_NO, SOKU_NO, SOKU_VAL, DISP_VAL, SKB_NO, KOMK_NO ) ";
	sBufSQL += " SELECT '" + HostName + "'  AS PCNAME, ";
	sBufSQL += " KSD03.DTKSHIN, KSD03.LOTNO, KSD03.UNQ_NO, KSD03.SOKU_NO, ";
    sBufSQL += " KSD03.SOKU_VAL, KSD03.DISP_VAL, ";
	sBufSQL += " KSD02.SKB_NO, KSD02.KOMK_NO ";
	sBufSQL += " FROM KSD03,KSD02 ";
	sBufSQL += " WHERE KSD03.DTKSHIN = KSD02.DTKSHIN ";
	sBufSQL += " AND KSD03.LOTNO = KSD02.LOTNO ";
	sBufSQL += " AND KSD03.UNQ_NO = KSD02.UNQ_NO ";
	sBufSQL += " AND KSD03.DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND KSD03.LOTNO IN (" + sLOT + ")";

	Q_WORK->SQL->Add(sBufSQL);
	// �₢�������̎��s
	try
	{
		Q_WORK->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		ShowMessage(e.Message);
		return(false);
	}
	catch(Exception& e)
	{
		ShowMessage(e.Message);
		return(false);
	}

    //��������������������������������������������������������������������������
	//�C�f�ރf�[�^(KSD2�V���[�Y)�����[�N�e�[�u���֒ǉ����܂��B
    //���ɓo�^����Ă���i������уe�[�u���Ƀf�[�^������j�ꍇ�́A�������܂���
    //�C-1 KSD21 �� KSD01W
    sBufSQL = "";
	sBufSQL += " SELECT * ";
	sBufSQL += " FROM KSD21 ";
	sBufSQL += " WHERE DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND   LOTNO IN (" + sLOT + ")";
    sBufSQL += " AND   SKTYMD >= '" + Form1->Edt_SEIKAN_YMD->Text + "'";      //onishi
	Q_GetKSD21->Close();
	Q_GetKSD21->SQL->Clear();
	Q_GetKSD21->SQL->Add(sBufSQL);
	Q_GetKSD21->Open();
	Q_GetKSD21->Active = true;
    if ( Q_GetKSD21->Eof != true ) {
    	Q_GetKSD21->First();
    	//����KSD01W�ɓo�^����Ă��邩���`�F�b�N����
		while(Q_GetKSD21->Eof == false) {

            sReDTKSHIN = Null_S(Q_GetKSD21->FieldValues["DTKSHIN"]);
            sReLOT     = Null_S(Q_GetKSD21->FieldValues["LOTNO"]);

        	bRtn = KSD01WGetLot(sReDTKSHIN,sReLOT);

            if ( bRtn == false ) {
            	//KSD01W�ɓo�^����Ă��Ȃ��̂ŁA�ǉ����܂�
				sBufSQL =  "";
				sBufSQL += " INSERT INTO KSD01W ( PCNAME,  ";
				sBufSQL += " DTKSHIN, LOTNO, HINBAN, DTKSCOD, ";
				sBufSQL += " DTKSNAM, ZISNAM, SOKUTEI_NUM, ";
				sBufSQL += " SOZAI_OK, SOZAI_OK_PRT, ";
				sBufSQL += " SYUKA_OK, SYUKA_OK_PRT, ";
				sBufSQL += " MEMO, ";
                //�o�׌����͂��Ă��Ȃ��̂ŁA�o�׌������͐ݒ肵�Ȃ�
				//sBufSQL += " SKTYMD, SKTYMD_PRT, ";
				sBufSQL += " SKTYMD_SZ, SKTYMD_SZ_PRT, ";
                //�o�׌����͂��Ă��Ȃ��̂ŁA�X�V�Ґݒ肵�Ȃ�
				//sBufSQL += " ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT ) ";
				sBufSQL += " ADDYMD, ADDTIM, UPDYMD, UPDTIM,  UPDCNT ) ";

				sBufSQL += " SELECT '" + HostName + "' AS PCNAME,  ";
				sBufSQL += " DTKSHIN, LOTNO, HINBAN, DTKSCOD, ";
				sBufSQL += " DTKSNAM, ZISNAM, SOKUTEI_NUM, ";
				sBufSQL += " SOZAI_OK, SOZAI_OK As SOZAI_OK_PRT, ";
                //�o�׌����͂��Ă��Ȃ��̂ŁA���ۂ͋�
				sBufSQL += " 2, 2, ";
				sBufSQL += " MEMO,";
                //�o�׌����͂��Ă��Ȃ��̂ŁA�o�׌������͐ݒ肵�Ȃ�
				//sBufSQL += " SKTYMD, SKTYMD As SKTYMD_PRT, ";
				sBufSQL += " SKTYMD As SKTYMD_SZ, SKTYMD As SKTYMD_SZ_PRT, ";
                //�o�׌����͂��Ă��Ȃ��̂ŁA�X�V�Ґݒ肵�Ȃ�
				//sBufSQL += " ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT ";
				sBufSQL += " ADDYMD, ADDTIM, UPDYMD, UPDTIM,  UPDCNT ";
				sBufSQL += " FROM KSD21 ";
				sBufSQL += " WHERE DTKSHIN = '" + sReDTKSHIN + "'";
				sBufSQL += " AND LOTNO ='" + sReLOT + "'";

				// Initial Query
				Q_WORK->Close();
				Q_WORK->SQL->Clear();
				Q_WORK->SQL->Add(sBufSQL);
				// �₢�������̎��s
				try
				{
					Q_WORK->ExecSQL();
				}
				catch(EDatabaseError& e)
				{
					ShowMessage(e.Message);
					return(false);
				}
				catch(Exception& e)
				{
					ShowMessage(e.Message);
					return(false);
				}


			    //��������������������������������������������������������������
    			//�C-2 KSD22 �� KSD02W
    			sBufSQL = "";
				sBufSQL += " SELECT *  FROM KSM02,KSD22  ";
				sBufSQL += " WHERE KSD22.DTKSHIN = KSM02.DTKSHIN ";
				sBufSQL += " AND KSD22.KOMK_NO = KSM02.KOMK_NO ";
				sBufSQL += " AND KSM02.SKB_NO = 1 AND REVCNT = 0 ";
				sBufSQL += " AND KSD22.DTKSHIN = '" + sReDTKSHIN + "'";
				sBufSQL += " AND KSD22.LOTNO ='" + sReLOT + "'";
                sBufSQL += " AND KSD22.SKTYMD >= '" + Form1->Edt_SEIKAN_YMD->Text + "'";      //onishi
				Q_GetKSD22->Close();
				Q_GetKSD22->SQL->Clear();
				Q_GetKSD22->SQL->Add(sBufSQL);
				Q_GetKSD22->Open();
				Q_GetKSD22->Active = true;


			    if ( Q_GetKSD22->Eof != true ) {
			    	Q_GetKSD22->First();
			    	//����KSD02W�ɓo�^����Ă��邩���`�F�b�N����
					while(Q_GetKSD22->Eof == false) {


			            sReSKB_NO  = "1";
			            sReKOMK_NO = Null_S(Q_GetKSD22->FieldValues["KOMK_NO"]);
		                sReUNQ_NO  = Null_S(Q_GetKSD22->FieldValues["UNQ_NO"]);
		         		bRtn = KSD02WGetLot(sReDTKSHIN,sReLOT,sReSKB_NO,sReKOMK_NO);

		            	if ( bRtn == false ) {
                            /*
		            		//KSD02W�ɓo�^����Ă��Ȃ��̂ŁA�ǉ����܂�
							sBufSQL =  "";
							sBufSQL += " INSERT INTO KSD02W ( PCNAME,  ";
							sBufSQL += " DTKSHIN, LOTNO, UNQ_NO, SKB_NO, HINBAN_SK, ";
                            sBufSQL += " ORDER_NO, ";
							sBufSQL += " KOMK_NO, KOMK_NM, KOMK_ENG, KOMK_SUB,  ";
							sBufSQL += " KOMK_SUB_ENG, KIKI_NO, KIKI_NM, TANI,  ";
							sBufSQL += " KIKA_TYPE, KIKA_KIND, KIKA_DECI, KIKA_NUM1,  ";
							sBufSQL += " KIKA_NUM2, KIKA_NUM3, KIKA_STR, KIKA_SUB1,  ";
                            //2003.09.16 E.Takase
							//sBufSQL += " KIKA_SUB2, SOKU_SU, SOKU_FLG, TOKU_FLG,  ";
							sBufSQL += " KIKA_SUB2, SOKU_SU,  ";
							sBufSQL += " VALUE_TYPE, VALUE_DECI, SOKU_VAL01, SOKU_VAL02,  ";
							sBufSQL += " SOKU_VAL03, SOKU_VAL04, SOKU_VAL05, SOKU_VAL06,  ";
							sBufSQL += " SOKU_VAL07, SOKU_VAL08, SOKU_VAL09, SOKU_VAL10,  ";
							sBufSQL += " SOKU_VAL_SU, SOKU_VAL_AVE, SOKU_VAL_MAX, SOKU_VAL_MIN,  ";
							sBufSQL += " SOKU_OK, DISP_VAL01, DISP_VAL02, DISP_VAL03,  ";
							sBufSQL += " DISP_VAL04, DISP_VAL05, DISP_VAL06, DISP_VAL07,  ";
							sBufSQL += " DISP_VAL08, DISP_VAL09, DISP_VAL10, DISP_VAL_SU,  ";
							sBufSQL += " DISP_VAL_AVE, DISP_VAL_MAX, DISP_VAL_MIN, ";
			                //�o�׌����͂��Ă��Ȃ��̂ŁA���ۂ͋�
		                    sBufSQL += " DISP_OK,  ";
			                //�����͂��Ă��Ȃ��̂ŁA�������͐ݒ肵�Ȃ�
							//sBufSQL += " SKTYMD, ADDYMD, ADDTIM, UPDYMD,  ";
							sBufSQL += "  ADDYMD, ADDTIM, UPDYMD,  ";
			                //�����͂��Ă��Ȃ��̂ŁA�X�V�҂͐ݒ肵�Ȃ�
							//sBufSQL += " UPDTIM, UPDCHR, UPDCNT )";
							sBufSQL += " UPDTIM,  UPDCNT, " ;
                            //2003.09.16 E.Takase
                            sBufSQL += "SOKU_FLG, TOKU_FLG, KIKA_PRT " ;
                            sBufSQL += " )";

							sBufSQL += " SELECT '" + HostName + "' AS PCNAME,  ";
							sBufSQL += " KSD22.DTKSHIN, KSD22.LOTNO, KSD22.UNQ_NO, 1 As SKB_NO, KSD22.DTKSHIN As HINBAN_SK, ";
                            sBufSQL += " KSD22.KOMK_NO As ORDER_NO, ";
							sBufSQL += " KSD22.KOMK_NO, KSD22.KOMK_NM, KSD22.KOMK_ENG, KSD22.KOMK_SUB, ";
							sBufSQL += " KSD22.KOMK_SUB_ENG, KSD22.KIKI_NO, KSD22.KIKI_NM, KSD22.TANI, ";
							sBufSQL += " KSD22.KIKA_TYPE, KSD22.KIKA_KIND, KSD22.KIKA_DECI, KSD22.KIKA_NUM1, ";
							sBufSQL += " KSD22.KIKA_NUM2, KSD22.KIKA_NUM3, KSD22.KIKA_STR, KSD22.KIKA_SUB1, ";
                            //2003.09.16 E.Takase
							//sBufSQL += " KIKA_SUB2, SOKU_SU, 1 As SOKU_FLG, 0 As TOKU_FLG, ";
							sBufSQL += " KSD22.KIKA_SUB2, KSD22.SOKU_SU,  ";
							sBufSQL += " KSD22.VALUE_TYPE, KSD22.VALUE_DECI, KSD22.SOKU_VAL01, KSD22.SOKU_VAL02, ";
							sBufSQL += " KSD22.SOKU_VAL03, KSD22.SOKU_VAL04, KSD22.SOKU_VAL05, KSD22.SOKU_VAL06, ";
							sBufSQL += " KSD22.SOKU_VAL07, KSD22.SOKU_VAL08, KSD22.SOKU_VAL09, KSD22.SOKU_VAL10, ";
							sBufSQL += " KSD22.SOKU_VAL_SU, KSD22.SOKU_VAL_AVE, KSD22.SOKU_VAL_MAX, ";
							sBufSQL += " KSD22.SOKU_VAL_MIN, KSD22.SOKU_OK, ";
							sBufSQL += " KSD22.SOKU_VAL01 As DISP_VAL01, KSD22.SOKU_VAL02 As DISP_VAL02, ";
							sBufSQL += " KSD22.SOKU_VAL03 As DISP_VAL03, KSD22.SOKU_VAL04 As DISP_VAL04, ";
							sBufSQL += " KSD22.SOKU_VAL05 As DISP_VAL05, KSD22.SOKU_VAL06 As DISP_VAL06, ";
							sBufSQL += " KSD22.SOKU_VAL07 As DISP_VAL07, KSD22.SOKU_VAL08 As DISP_VAL08, ";
							sBufSQL += " KSD22.SOKU_VAL09 As DISP_VAL09, KSD22.SOKU_VAL10 As DISP_VAL10, ";
							sBufSQL += " KSD22.SOKU_VAL_SU As DISP_VAL_SU, SOKU_VAL_AVE As DISP_VAL_AVE, ";
							sBufSQL += " KSD22.SOKU_VAL_MAX As DISP_VAL_MAX, KSD22.SOKU_VAL_MIN As DISP_VAL_MIN, ";
			                //�o�׌����͂��Ă��Ȃ��̂ŁA���ۂ͋�
							sBufSQL += " 2, ";
			                //�����͂��Ă��Ȃ��̂ŁA�������͐ݒ肵�Ȃ�
							//sBufSQL += " SKTYMD, ADDYMD, ADDTIM, UPDYMD, ";
							sBufSQL += "  KSD22.ADDYMD, KSD22.ADDTIM, KSD22.UPDYMD, ";
			                //�����͂��Ă��Ȃ��̂ŁA�X�V�҂͐ݒ肵�Ȃ�
							//sBufSQL += " UPDTIM, UPDCHR, UPDCNT ";
							sBufSQL += " KSD22.UPDTIM,  KSD22.UPDCNT, ";
                            //2003.09.16 E.Takase
                            sBufSQL += "KSM02.SOKU_FLG, KSM02.TOKU_FLG, KSM02.KIKA_PRT " ;

							sBufSQL += " FROM KSD22, KSM02 ";
							sBufSQL += " WHERE KSD22.DTKSHIN = KSM02.DTKSHIN ";
							sBufSQL += " AND KSD22.KOMK_NO = KSM02.KOMK_NO ";
							sBufSQL += " AND KSM02.SKB_NO = 1 AND REVCNT = 0 ";
							sBufSQL += " AND KSD22.DTKSHIN = '" + sReDTKSHIN + "'";
							sBufSQL += " AND KSD22.LOTNO ='" + sReLOT + "'";
							sBufSQL += " AND KSD22.KOMK_NO ='" + sReKOMK_NO + "'";

                            */

 		            		//KSD02W�ɓo�^����Ă��Ȃ��̂ŁA�ǉ����܂�
							sBufSQL =  "";
							sBufSQL += " INSERT INTO KSD02W ( PCNAME,  ";
							sBufSQL += " DTKSHIN, LOTNO, UNQ_NO, SKB_NO, HINBAN_SK, ";
                            sBufSQL += " ORDER_NO, ";
							sBufSQL += " KOMK_NO, KOMK_NM, KOMK_ENG, KOMK_SUB,  ";
							sBufSQL += " KOMK_SUB_ENG, KIKI_NO, KIKI_NM, TANI,  ";
							sBufSQL += " KIKA_TYPE, KIKA_KIND, KIKA_DECI, KIKA_NUM1,  ";
							sBufSQL += " KIKA_NUM2, KIKA_NUM3, KIKA_STR, KIKA_SUB1,  ";
                            //2003.09.16 E.Takase
							//sBufSQL += " KIKA_SUB2, SOKU_SU, SOKU_FLG, TOKU_FLG,  ";
							sBufSQL += " KIKA_SUB2, SOKU_SU,  ";
							sBufSQL += " VALUE_TYPE, VALUE_DECI, SOKU_VAL01, SOKU_VAL02,  ";
							sBufSQL += " SOKU_VAL03, SOKU_VAL04, SOKU_VAL05, SOKU_VAL06,  ";
							sBufSQL += " SOKU_VAL07, SOKU_VAL08, SOKU_VAL09, SOKU_VAL10,  ";
							sBufSQL += " SOKU_VAL_SU, SOKU_VAL_AVE, SOKU_VAL_MAX, SOKU_VAL_MIN,  ";
							sBufSQL += " SOKU_OK, DISP_VAL01, DISP_VAL02, DISP_VAL03,  ";
							sBufSQL += " DISP_VAL04, DISP_VAL05, DISP_VAL06, DISP_VAL07,  ";
							sBufSQL += " DISP_VAL08, DISP_VAL09, DISP_VAL10, DISP_VAL_SU,  ";
							sBufSQL += " DISP_VAL_AVE, DISP_VAL_MAX, DISP_VAL_MIN, ";
			                //�o�׌����͂��Ă��Ȃ��̂ŁA���ۂ͋�
		                    sBufSQL += " DISP_OK,  ";
			                //�����͂��Ă��Ȃ��̂ŁA�������͐ݒ肵�Ȃ�
							//sBufSQL += " SKTYMD, ADDYMD, ADDTIM, UPDYMD,  ";
							sBufSQL += "  ADDYMD, ADDTIM, UPDYMD,  ";
			                //�����͂��Ă��Ȃ��̂ŁA�X�V�҂͐ݒ肵�Ȃ�
							//sBufSQL += " UPDTIM, UPDCHR, UPDCNT )";
							sBufSQL += " UPDTIM,  UPDCNT, " ;
                            //2003.09.16 E.Takase
                            sBufSQL += "SOKU_FLG, TOKU_FLG, KIKA_PRT " ;
                            sBufSQL += " )";
							sBufSQL += " values (" ;
							sBufSQL += " '" +  HostName 										+ "' , ";
							sBufSQL += " '" +  Trim(Null_S(Q_GetKSD22->FieldValues["DTKSHIN"])) 		+ "' , ";
							sBufSQL += " '" +  Trim(Null_S(Q_GetKSD22->FieldValues["LOTNO"])) 		+ "' , ";
							sBufSQL += " '" +  Trim(Null_S(Q_GetKSD22->FieldValues["UNQ_NO"])) 		+ "' , ";
							sBufSQL +=         "1, ";
                            sBufSQL += " '" +  Trim(Null_S(Q_GetKSD22->FieldValues["HINBAN_SK"])) 	+ "' , ";
							sBufSQL += " '" +  Trim(Null_S(Q_GetKSD22->FieldValues["ORDER_NO"])) 		+ "' , ";
							sBufSQL +=         Trim(Null_S(Q_GetKSD22->FieldValues["KOMK_NO"])) 		+ ", ";
							sBufSQL += " '" +  Trim(Null_S(Q_GetKSD22->FieldValues["KOMK_NM"])) 		+ "' , ";
							sBufSQL += " '" +  Trim(Null_S(Q_GetKSD22->FieldValues["KOMK_ENG"]))		+ "' , ";
							sBufSQL += " '" +  Trim(Null_S(Q_GetKSD22->FieldValues["KOMK_SUB"])) 		+ "' , ";
							sBufSQL += " '" +  Trim(Null_S(Q_GetKSD22->FieldValues["KOMK_SUB_ENG"])) 	+ "' , ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["KIKI_NO"]) 		+ ", ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["KIKI_NM"]) 		+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["TANI"]) 			+ "' , ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["KIKA_TYPE"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["KIKA_KIND"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["KIKA_DECI"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["KIKA_NUM1"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["KIKA_NUM2"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["KIKA_NUM3"]) 	+ ", ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["KIKA_STR"]) 		+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["KIKA_SUB1"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["KIKA_SUB2"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_SU"]) 		+ "' , ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["VALUE_TYPE"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["VALUE_DECI"]) 	+ ", ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL01"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL02"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL03"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL04"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL05"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL06"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL07"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL08"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL09"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL10"]) 	+ "' , ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["SOKU_VAL_SU"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["SOKU_VAL_AVE"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["SOKU_VAL_MAX"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["SOKU_VAL_MIN"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["SOKU_OK"]) 		+ ", ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL01"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL02"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL03"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL04"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL05"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL06"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL07"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL08"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL09"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL10"]) 	+ "' , ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["SOKU_VAL_SU"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["SOKU_VAL_AVE"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["SOKU_VAL_MAX"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["SOKU_VAL_MIN"]) 	+ ", ";
							sBufSQL +=         "2, ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["ADDYMD"]) 		+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["ADDTIM"]) 		+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["UPDYMD"]) 		+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["UPDTIM"]) 		+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["UPDCNT"]) 		+ "' , ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["SOKU_FLG"]) 		+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["TOKU_FLG"]) 		+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["KIKA_PRT"]) 		;
							sBufSQL += ")";

							// Initial Query
							Q_WORK->Close();
							Q_WORK->SQL->Clear();
							Q_WORK->SQL->Add(sBufSQL);
							// �₢�������̎��s
							try
							{
								Q_WORK->ExecSQL();
							}
							catch(EDatabaseError& e)
							{
								ShowMessage(e.Message);
								return(false);
							}
							catch(Exception& e)
							{
								ShowMessage(e.Message);
								return(false);
							}

		                    //����������������������������������������������������������
		            		//�C-3KSD03W�ɂ��o�^����Ă��Ȃ��̂ŁA�ǉ����܂�
							sBufSQL =  "";
							sBufSQL += " INSERT INTO KSD03W ( PCNAME,  ";
							sBufSQL += " DTKSHIN, LOTNO, UNQ_NO, ";
							sBufSQL += " SOKU_NO, SOKU_VAL, DISP_VAL, ";
							sBufSQL += " SKB_NO, KOMK_NO )";
							sBufSQL += " SELECT '" + HostName + "' AS PCNAME,  ";
							sBufSQL += " DTKSHIN, LOTNO, UNQ_NO, ";
							sBufSQL += " SOKU_NO, SOKU_VAL, SOKU_VAL As DISP_VAL, ";
                            sBufSQL +=  sReSKB_NO + " AS SKB_NO," + sReKOMK_NO + " AS KOMK_NO ";
							sBufSQL += " FROM KSD23 ";
							sBufSQL += " WHERE DTKSHIN = '" + sReDTKSHIN + "'";
							sBufSQL += " AND LOTNO ='" + sReLOT + "'";
							sBufSQL += " AND UNQ_NO ='" + sReUNQ_NO + "'";

							// Initial Query
							Q_WORK->Close();
							Q_WORK->SQL->Clear();
							Q_WORK->SQL->Add(sBufSQL);
							// �₢�������̎��s
							try
							{
								Q_WORK->ExecSQL();
							}
							catch(EDatabaseError& e)
							{
								ShowMessage(e.Message);
								return(false);
							}
							catch(Exception& e)
							{
								ShowMessage(e.Message);
								return(false);
							}

		                }

			            Q_GetKSD22->Next();
					}	
				}

            }

            Q_GetKSD21->Next();
        }

    }

    //2003.10.22 E.Takase
    //��������������������������������������������������������������������������
    //������̃��b�g�����邩�ǂ����𔻒f����
    //���f���@�F���������̃��b�g����KSD02W�̃��b�g�����r
    //          ���������̃��b�g���������Ȃ疢����̃��b�g������Ƃ���
    //������̃��b�g���������ꍇ�D�`�̏������s��
    int iSrchLOTNum;
    int iKSD02WLOTNum;

    //���������̃��b�g��
    AnsiString Str = sLOT;  	// �Ώە�����
    AnsiString From = ",";      // ����������
    AnsiString To = "";         // �u��������
    AnsiString Result;          // �u�����ʕ�����
    Result = StringReplace( Str, From, To, TReplaceFlags() << rfReplaceAll << rfIgnoreCase );

    iSrchLOTNum = sLOT.Length() - Result.Length() + 1;

    //���肳��Ă��郍�b�g�̌�
    sBufSQL = "";
	sBufSQL += " SELECT DISTINCT DTKSHIN, LOTNO FROM KSD02W  ";
	sBufSQL += " WHERE PCNAME='" + HostName + "'";
	Q_GetKSD22->Close();
	Q_GetKSD22->SQL->Clear();
	Q_GetKSD22->SQL->Add(sBufSQL);
	Q_GetKSD22->Open();
	Q_GetKSD22->Active = true;
	if ( Q_GetKSD22->Eof != true ) {
     	iKSD02WLOTNum = Q_GetKSD22->RecordCount;
    } else {
    	iKSD02WLOTNum = 0;
    }

    //���������̃��b�g����KSD02W�̃��b�g�����r
    if ( iSrchLOTNum == iKSD02WLOTNum ) {
		return(true);
	}


    //2003.09.16 E.Takase
    //��������������������������������������������������������������������������
    //�D������̃��b�g�����[�N�e�[�u���ɒǉ����܂�
    //���[�N�e�[�u���ɒǉ�����Ă��Ȃ����b�g�݂̂�ǉ����܂�
    //�D-1 SD21S �� KSD01W
    sBufSQL = "";
	sBufSQL += " SELECT * ";
	sBufSQL += " FROM SD21S ";
	sBufSQL += " WHERE DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND LOTBNG IN (" + sLOT + ")";
    sBufSQL += " AND DENYMD >= '" + Form1->Edt_SEIKAN_YMD->Text + "'";      //onishi

	Q_GetKSD21->Close();
	Q_GetKSD21->SQL->Clear();
	Q_GetKSD21->SQL->Add(sBufSQL);
	Q_GetKSD21->Open();
	Q_GetKSD21->Active = true;
    if ( Q_GetKSD21->Eof != true ) {
    	//����KSD01W�ɓo�^����Ă��邩���`�F�b�N����
		while(Q_GetKSD21->Eof == false) {

            sReDTKSHIN = Null_S(Q_GetKSD21->FieldValues["DTKSHIN"]);
            sReLOT     = Null_S(Q_GetKSD21->FieldValues["LOTBNG"]);

        	bRtn = KSD01WGetLot(sReDTKSHIN,sReLOT);

            if ( bRtn == false ) {
            	//KSD01W�ɓo�^����Ă��Ȃ��̂ŁA�ǉ����܂�
				sBufSQL =  "";
				sBufSQL += " INSERT INTO KSD01W ( PCNAME,  ";
				sBufSQL += " DTKSHIN, LOTNO, ";
                //�����͂��Ă��Ȃ��̂ŁA���ۂ͋�
				sBufSQL += " SOZAI_OK, SOZAI_OK_PRT, ";
				sBufSQL += " SYUKA_OK, SYUKA_OK_PRT ";
                sBufSQL += "  ) ";

				sBufSQL += " values ( '" + HostName + "' ,  ";
				sBufSQL += " '" + sReDTKSHIN + "', ";
				sBufSQL += " '" + sReLOT + "' , ";
                //�����͂��Ă��Ȃ��̂ŁA���ۂ͋�
				sBufSQL += " 2, 2, 2, 2 ) ";

				// Initial Query
				Q_WORK->Close();
				Q_WORK->SQL->Clear();
				Q_WORK->SQL->Add(sBufSQL);
				// �₢�������̎��s
				try
				{
					Q_WORK->ExecSQL();
				}
				catch(EDatabaseError& e)
				{
					ShowMessage(e.Message);
					return(false);
				}
				catch(Exception& e)
				{
					ShowMessage(e.Message);
					return(false);
				}


            }
            Q_GetKSD21->Next();
        }
    }

    //��������������������������������������������������������������������������
	//�E���i�K�i�f�[�^(KSM02)�����[�N�e�[�u���֒ǉ����܂��B
    //���ɓo�^����Ă���i������сE�f�ރe�[�u���Ƀf�[�^������j�ꍇ�́A�������܂���
    //�E-1 KSM02 ��  KSD02W
    sBufSQL = "";
	sBufSQL += " SELECT *  from KSM02";
	sBufSQL += " where DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND REVCNT = 0 ";
	Q_GetKSM02->Close();
	Q_GetKSM02->SQL->Clear();
	Q_GetKSM02->SQL->Add(sBufSQL);
	Q_GetKSM02->Open();
	Q_GetKSM02->Active = true;
    if ( Q_GetKSM02->Eof != true ) {
    	//KSD01W�̊e���b�g�ɑ΂��āA���荀�ڂ�ǉ����邩���f���Ă���
	    sBufSQL = "";
		sBufSQL += " SELECT *  from KSD01W";
		sBufSQL += " where PCNAME = '" + HostName + "'";
		Q_GetKSD21->Close();
		Q_GetKSD21->SQL->Clear();
		Q_GetKSD21->SQL->Add(sBufSQL);
		Q_GetKSD21->Open();
		Q_GetKSD21->Active = true;
        if ( Q_GetKSD21->Eof != true ) {
        	while(Q_GetKSD21->Eof == false) {
	            sReDTKSHIN = Null_S(Q_GetKSD21->FieldValues["DTKSHIN"]);
	            sReLOT     = Null_S(Q_GetKSD21->FieldValues["LOTNO"]);
                Q_GetKSM02->First();
                while(Q_GetKSM02->Eof == false) {
                    //���݂̃��b�g�����荀�ڂ̃p�^�[����KSD02W�ɑ��݂��邩���`�F�b�N��
                    //���݂��Ȃ���Βǉ����܂��B

		            sReSKB_NO  = Null_S(Q_GetKSM02->FieldValues["SKB_NO"]);
		            sReKOMK_NO = Null_S(Q_GetKSM02->FieldValues["KOMK_NO"]);
		         	bRtn = KSD02WGetLot(sReDTKSHIN,sReLOT,sReSKB_NO,sReKOMK_NO);

		            if ( bRtn == false ) {
                        sBufSQL  = "";
					   	sBufSQL += " INSERT INTO KSD02W ( PCNAME,  ";
						sBufSQL += " DTKSHIN, LOTNO, UNQ_NO, ";
						sBufSQL += " SKB_NO, HINBAN_SK, ORDER_NO, KOMK_NO, ";
						sBufSQL += " KOMK_NM, KOMK_ENG, KOMK_SUB, KOMK_SUB_ENG, ";
						sBufSQL += " KIKI_NO, KIKI_NM, TANI, KIKA_TYPE, KIKA_KIND, ";
						sBufSQL += " KIKA_DECI, KIKA_NUM1, KIKA_NUM2, KIKA_NUM3, ";
						sBufSQL += " KIKA_STR, KIKA_SUB1, KIKA_SUB2, SOKU_SU, ";
						sBufSQL += " VALUE_TYPE, VALUE_DECI, SOKU_OK, DISP_OK, DISP_VAL_SU, ";
						sBufSQL += " SOKU_FLG, TOKU_FLG, KIKA_PRT ";
                        sBufSQL += " )";
						sBufSQL += " values (" ;
						sBufSQL += " '" +  HostName 										+ "' , ";
						sBufSQL += " '" +  sReDTKSHIN 										+ "' , ";
						sBufSQL += " '" +  sReLOT 											+ "' , ";
						//sBufSQL += " '" +  Null_S(Q_GetKSM02->FieldValues["UNQ_NO"]) 		+ "' , ";
						sBufSQL += " '" +  Trim(Null_S(Q_GetKSM02->FieldValues["KOMK_NO"])) 		+ "' , ";
						sBufSQL +=         Trim(Null_S(Q_GetKSM02->FieldValues["SKB_NO"])) 		+ ", ";
                        sBufSQL += " '" +  Trim(Null_S(Q_GetKSM02->FieldValues["HINBAN_SK"])) 	+ "' , ";
						sBufSQL += " '" +  Trim(Null_S(Q_GetKSM02->FieldValues["ORDER_NO"])) 		+ "' , ";
						sBufSQL +=         Trim(Null_S(Q_GetKSM02->FieldValues["KOMK_NO"])) 		+ ", ";
						sBufSQL += " '" +  Trim(Null_S(Q_GetKSM02->FieldValues["KOMK_NM"])) 		+ "' , ";
						sBufSQL += " '" +  Trim(Null_S(Q_GetKSM02->FieldValues["KOMK_ENG"]))		+ "' , ";
						sBufSQL += " '" +  Trim(Null_S(Q_GetKSM02->FieldValues["KOMK_SUB"])) 		+ "' , ";
						sBufSQL += " '" +  Trim(Null_S(Q_GetKSM02->FieldValues["KOMK_SUB_ENG"])) 	+ "' , ";
						sBufSQL +=         Null_S(Q_GetKSM02->FieldValues["KIKI_NO"]) 		+ ", ";
						sBufSQL += " '" +  Null_S(Q_GetKSM02->FieldValues["KIKI_NM"]) 		+ "' , ";
						sBufSQL += " '" +  Null_S(Q_GetKSM02->FieldValues["TANI"]) 			+ "' , ";
						sBufSQL +=         Null_S(Q_GetKSM02->FieldValues["KIKA_TYPE"]) 	+ ", ";
						sBufSQL +=         Null_S(Q_GetKSM02->FieldValues["KIKA_KIND"]) 	+ ", ";
						sBufSQL +=         Null_S(Q_GetKSM02->FieldValues["KIKA_DECI"]) 	+ ", ";
						sBufSQL +=         Null_S(Q_GetKSM02->FieldValues["KIKA_NUM1"]) 	+ ", ";
						sBufSQL +=         Null_S(Q_GetKSM02->FieldValues["KIKA_NUM2"]) 	+ ", ";
						sBufSQL +=         Null_S(Q_GetKSM02->FieldValues["KIKA_NUM3"]) 	+ ", ";
						sBufSQL += " '" +  Null_S(Q_GetKSM02->FieldValues["KIKA_STR"]) 		+ "' , ";
						sBufSQL += " '" +  Null_S(Q_GetKSM02->FieldValues["KIKA_SUB1"]) 	+ "' , ";
						sBufSQL += " '" +  Null_S(Q_GetKSM02->FieldValues["KIKA_SUB2"]) 	+ "' , ";
						sBufSQL += " '" +  Null_S(Q_GetKSM02->FieldValues["SOKU_SU"]) 		+ "' , ";
						sBufSQL +=         Null_S(Q_GetKSM02->FieldValues["VALUE_TYPE"]) 	+ ", ";
						sBufSQL +=         Null_S(Q_GetKSM02->FieldValues["VALUE_DECI"]) 	+ ", ";
						sBufSQL +=         "2, ";
						sBufSQL +=         "2, ";
						sBufSQL += " '" +  Null_S(Q_GetKSM02->FieldValues["SOKU_SU"]) 		+ "' , ";
						sBufSQL +=         Null_S(Q_GetKSM02->FieldValues["SOKU_FLG"]) 		+ ", ";
						sBufSQL +=         Null_S(Q_GetKSM02->FieldValues["TOKU_FLG"]) 		+ ", ";
						sBufSQL +=         Null_S(Q_GetKSM02->FieldValues["KIKA_PRT"]) 		;
						sBufSQL += ")";

						// Initial Query
						Q_WORK->Close();
						Q_WORK->SQL->Clear();
						Q_WORK->SQL->Add(sBufSQL);
						// �₢�������̎��s
						try
						{
							Q_WORK->ExecSQL();
						}
						catch(EDatabaseError& e)
						{
							ShowMessage(e.Message);
							return(false);
						}
						catch(Exception& e)
						{
							ShowMessage(e.Message);
							return(false);
						}

                    }

                	Q_GetKSM02->Next();
                }

            	Q_GetKSD21->Next();
            }
        }
    }


    //��������������������������������������������������������������������������
	//�F������z�f�[�^(SD21S)�����[�N�e�[�u���֒ǉ����܂��B
    //���ɓo�^����Ă���i������сE�f�ށE���i�K�i�e�[�u���Ƀf�[�^������j�ꍇ�́A�������܂���
    //�F-1 SD21S �� KSD02W
    //���ۂ�KSD01W�ɓo�^����Ă��郍�b�g��KSD02W�ɓo�^����Ă��Ȃ������ꍇ�A�_�~�[�f�[�^��ǉ�����
    sBufSQL = "";
	sBufSQL += " SELECT KSD01W.LOTNO ";
	sBufSQL += " FROM KSD01W, KSD02W ";
	sBufSQL += " where KSD02W.PCNAME(+) = KSD01W.PCNAME  ";
	sBufSQL += " AND KSD02W.DTKSHIN(+) = KSD01W.DTKSHIN  ";
	sBufSQL += " AND KSD02W.LOTNO(+) = KSD01W.LOTNO  ";
	sBufSQL += " AND KSD01W.PCNAME = '" + HostName + "'";
	sBufSQL += " AND KSD01W.DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND KSD02W.LOTNO IS NULL ";
	Q_GetKSD21->Close();
	Q_GetKSD21->SQL->Clear();
	Q_GetKSD21->SQL->Add(sBufSQL);
	Q_GetKSD21->Open();
	Q_GetKSD21->Active = true;
    if ( Q_GetKSD21->Eof != true ) {
	}

	//KSD02W�ɓo�^����Ă��Ȃ��̂ŁA�ǉ����܂�
	sBufSQL =  "";
	sBufSQL += " INSERT INTO KSD02W ( PCNAME,  ";
	sBufSQL += " DTKSHIN, LOTNO, UNQ_NO, SKB_NO, HINBAN_SK, ";
	sBufSQL += " ORDER_NO, KOMK_NO, KOMK_NM, ";
	sBufSQL += " SOKU_SU, SOKU_FLG, DISP_VAL_SU, ";
	//�����͂��Ă��Ȃ��̂ŁA���ۂ͋�
	sBufSQL += " DISP_OK  ";
	sBufSQL += " ) ";

	sBufSQL += " SELECT '" + HostName + "' AS PCNAME,  ";

	sBufSQL += " KSD01W.DTKSHIN As DTKSHIN, KSD01W.LOTNO As LOTNO, ";
	sBufSQL += " 1 As UNQ_NO , 1 As SKB_NO ,  ";
	sBufSQL += " KSD01W.DTKSHIN As HINBAN_SK,  ";
	sBufSQL += " 9999 As ORDER_NO, 9999 As KOMK_NO , '-' As KOMK_NM,  ";
	sBufSQL += " 1 As SOKU_SU , 1 As SOKU_FLG, 1 As DISP_VAL_SU, ";
	sBufSQL += " 2 As DISP_OK ";
	sBufSQL += " FROM KSD01W, KSD02W ";
	sBufSQL += " where KSD02W.PCNAME(+) = KSD01W.PCNAME  ";
	sBufSQL += " AND KSD02W.DTKSHIN(+) = KSD01W.DTKSHIN  ";
	sBufSQL += " AND KSD02W.LOTNO(+) = KSD01W.LOTNO  ";
	sBufSQL += " AND KSD01W.PCNAME = '" + HostName + "'";
	sBufSQL += " AND KSD01W.DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND KSD02W.LOTNO IS NULL ";

	// Initial Query
	Q_WORK->Close();
	Q_WORK->SQL->Clear();
	Q_WORK->SQL->Add(sBufSQL);
	// �₢�������̎��s
	try
	{
		Q_WORK->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		ShowMessage(e.Message);
		return(false);
	}
	catch(Exception& e)
	{
		ShowMessage(e.Message);
		return(false);
	}


/*
    //��������������������������������������������������������������������������
	//�D���i�K�i�f�[�^(KSM02)�����[�N�e�[�u���֒ǉ����܂��B
    //���ɓo�^����Ă���i������сE�f�ރe�[�u���Ƀf�[�^������j�ꍇ�́A�������܂���
    //�D-1 KSM02 ��  KSD02W
    sBufSQL = "";
	sBufSQL += " SELECT DISTINCT  ";
	sBufSQL += "KSM02.DTKSHIN,SD21S.LOTBNG ";
	sBufSQL += "from KSM02, SD21S  ";
	sBufSQL += "where SD21S.DTKSHIN = KSM02.DTKSHIN  ";
	sBufSQL += " AND KSM02.DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND KSM02.REVCNT = 0 ";
	sBufSQL += " AND SD21S.LOTBNG IN (" + sLOT + ")";
	Q_GetKSD21->Close();
	Q_GetKSD21->SQL->Clear();
	Q_GetKSD21->SQL->Add(sBufSQL);
	Q_GetKSD21->Open();
	Q_GetKSD21->Active = true;
    if ( Q_GetKSD21->Eof != true ) {
    	//����KSD01W�ɓo�^����Ă��邩���`�F�b�N����
		while(Q_GetKSD21->Eof == false) {

            sReDTKSHIN = Null_S(Q_GetKSD21->FieldValues["DTKSHIN"]);
            sReLOT     = Null_S(Q_GetKSD21->FieldValues["LOTBNG"]);

        	bRtn = KSD01WGetLot(sReDTKSHIN,sReLOT);

            if ( bRtn == false ) {
            	//KSD01W�ɓo�^����Ă��Ȃ��̂ŁA�ǉ����܂�
				sBufSQL =  "";
				sBufSQL += " INSERT INTO KSD01W ( PCNAME,  ";
				sBufSQL += " DTKSHIN, LOTNO, ";
                //�����͂��Ă��Ȃ��̂ŁA���ۂ͋�
				sBufSQL += " SOZAI_OK, SOZAI_OK_PRT, ";
				sBufSQL += " SYUKA_OK, SYUKA_OK_PRT ";
                sBufSQL += "  ) ";

				sBufSQL += " values ( '" + HostName + "' ,  ";
				sBufSQL += " '" + sReDTKSHIN + "', ";
				sBufSQL += " '" + sReLOT + "' , ";
                //�����͂��Ă��Ȃ��̂ŁA���ۂ͋�
				sBufSQL += " 2, 2, 2, 2 ) ";

				// Initial Query
				Q_WORK->Close();
				Q_WORK->SQL->Clear();
				Q_WORK->SQL->Add(sBufSQL);
				// �₢�������̎��s
				try
				{
					Q_WORK->ExecSQL();
				}
				catch(EDatabaseError& e)
				{
					ShowMessage(e.Message);
					return(false);
				}
				catch(Exception& e)
				{
					ShowMessage(e.Message);
					return(false);
				}
            	//KSD02W�ɓo�^����Ă��Ȃ��̂ŁA�ǉ����܂�
                sBufSQL = "";
				sBufSQL += " INSERT INTO KSD02W ( PCNAME,  ";
				sBufSQL += " DTKSHIN,LOTNO,UNQ_NO,ORDER_NO, ";
				sBufSQL += " SKB_NO,HINBAN_SK,KOMK_NO,KOMK_NM, ";
				sBufSQL += " KOMK_ENG,KOMK_SUB,KOMK_SUB_ENG, ";
				sBufSQL += " KIKI_NO,KIKI_NM,TANI,KIKA_TYPE, ";
				sBufSQL += " KIKA_KIND,KIKA_DECI,KIKA_NUM1, ";
				sBufSQL += " KIKA_NUM2,KIKA_NUM3,KIKA_STR, ";
				sBufSQL += " KIKA_SUB1,KIKA_SUB2,KIKA_SUB3, ";
				sBufSQL += " SOKU_SU,SOKU_FLG,TOKU_FLG, ";
				sBufSQL += " KIKA_PRT,VALUE_TYPE,VALUE_DECI, ";
				sBufSQL += " DISP_OK, DISP_VAL_SU  ";
				sBufSQL += "  )";

				sBufSQL += " SELECT '" + HostName + "' AS PCNAME,  ";

				sBufSQL += " DTKSHIN, '" + sReLOT + "' As LOTNO,UNQ_NO,ORDER_NO, ";
				sBufSQL += " SKB_NO,HINBAN_SK,KOMK_NO,KOMK_NM, ";
				sBufSQL += " KOMK_ENG,KOMK_SUB,KOMK_SUB_ENG, ";
				sBufSQL += " KIKI_NO,KIKI_NM,TANI,KIKA_TYPE, ";
				sBufSQL += " KIKA_KIND,KIKA_DECI,KIKA_NUM1, ";
				sBufSQL += " KIKA_NUM2,KIKA_NUM3,KIKA_STR, ";
				sBufSQL += " KIKA_SUB1,KIKA_SUB2,KIKA_SUB3, ";
				sBufSQL += " SOKU_SU,SOKU_FLG,TOKU_FLG, ";
				sBufSQL += " KIKA_PRT,VALUE_TYPE,VALUE_DECI, ";
				sBufSQL += " 2 As DISP_OK , SOKU_SU As DISP_VAL_SU ";
                //�����͂��Ă��Ȃ��̂ŁA���ۂ͋�
				sBufSQL += " FROM KSM02 ";
				sBufSQL += " WHERE DTKSHIN = '" + sReDTKSHIN + "'";
                sBufSQL += " AND REVCNT = 0";


				// Initial Query
				Q_WORK->Close();
				Q_WORK->SQL->Clear();
				Q_WORK->SQL->Add(sBufSQL);
				// �₢�������̎��s
				try
				{
					Q_WORK->ExecSQL();
				}
				catch(EDatabaseError& e)
				{
					ShowMessage(e.Message);
					return(false);
				}
				catch(Exception& e)
				{
					ShowMessage(e.Message);
					return(false);
				}

            }



        	Q_GetKSD21->Next();
        }
    }
    //��������������������������������������������������������������������������
	//�E������z�f�[�^(SD21S)�����[�N�e�[�u���֒ǉ����܂��B
    //���ɓo�^����Ă���i������сE�f�ށE���i�K�i�e�[�u���Ƀf�[�^������j�ꍇ�́A�������܂���
    //�E-1 SD21S �� KSD01W , KSD02W
    sBufSQL = "";
	sBufSQL += " SELECT * ";
	sBufSQL += " FROM SD21S ";
	sBufSQL += " WHERE DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND LOTBNG IN (" + sLOT + ")";
	Q_GetKSD21->Close();
	Q_GetKSD21->SQL->Clear();
	Q_GetKSD21->SQL->Add(sBufSQL);
	Q_GetKSD21->Open();
	Q_GetKSD21->Active = true;
    if ( Q_GetKSD21->Eof != true ) {
    	//����KSD01W�ɓo�^����Ă��邩���`�F�b�N����
		while(Q_GetKSD21->Eof == false) {

            sReDTKSHIN = Null_S(Q_GetKSD21->FieldValues["DTKSHIN"]);
            sReLOT     = Null_S(Q_GetKSD21->FieldValues["LOTBNG"]);

        	bRtn = KSD01WGetLot(sReDTKSHIN,sReLOT);

            if ( bRtn == false ) {
            	//KSD01W�ɓo�^����Ă��Ȃ��̂ŁA�ǉ����܂�
				sBufSQL =  "";
				sBufSQL += " INSERT INTO KSD01W ( PCNAME,  ";
				sBufSQL += " DTKSHIN, LOTNO, ";
                //�����͂��Ă��Ȃ��̂ŁA���ۂ͋�
				sBufSQL += " SOZAI_OK, SOZAI_OK_PRT, ";
				sBufSQL += " SYUKA_OK, SYUKA_OK_PRT ";
                sBufSQL += "  ) ";

				sBufSQL += " values ( '" + HostName + "' ,  ";
				sBufSQL += " '" + sReDTKSHIN + "', ";
				sBufSQL += " '" + sReLOT + "' , ";
                //�����͂��Ă��Ȃ��̂ŁA���ۂ͋�
				sBufSQL += " 2, 2, 2, 2 ) ";

				// Initial Query
				Q_WORK->Close();
				Q_WORK->SQL->Clear();
				Q_WORK->SQL->Add(sBufSQL);
				// �₢�������̎��s
				try
				{
					Q_WORK->ExecSQL();
				}
				catch(EDatabaseError& e)
				{
					ShowMessage(e.Message);
					return(false);
				}
				catch(Exception& e)
				{
					ShowMessage(e.Message);
					return(false);
				}


            	//KSD02W�ɓo�^����Ă��Ȃ��̂ŁA�ǉ����܂�
				sBufSQL =  "";
				sBufSQL += " INSERT INTO KSD02W ( PCNAME,  ";
				sBufSQL += " DTKSHIN, LOTNO, UNQ_NO, SKB_NO, HINBAN_SK, ";
				sBufSQL += " ORDER_NO, KOMK_NO, KOMK_NM, ";
				sBufSQL += " SOKU_SU, SOKU_FLG, DISP_VAL_SU, ";
                //�����͂��Ă��Ȃ��̂ŁA���ۂ͋�
                sBufSQL += " DISP_OK  ";
				sBufSQL += " ) ";

				sBufSQL += " values ( '" + HostName + "' ,  ";
				sBufSQL += " '" + sReDTKSHIN + "', ";
				sBufSQL += " '" + sReLOT + "',  ";
				sBufSQL += " 1, 1,  ";
				sBufSQL += " '" + sReDTKSHIN + "',  ";
				sBufSQL += " 9999,9999, '-',  ";
				sBufSQL += " 1, 1, 1, ";
                sBufSQL += " 2 ";
                //�����͂��Ă��Ȃ��̂ŁA���ۂ͋�
				sBufSQL += ")  ";

				// Initial Query
				Q_WORK->Close();
				Q_WORK->SQL->Clear();
				Q_WORK->SQL->Add(sBufSQL);
				// �₢�������̎��s
				try
				{
					Q_WORK->ExecSQL();
				}
				catch(EDatabaseError& e)
				{
					ShowMessage(e.Message);
					return(false);
				}
				catch(Exception& e)
				{
					ShowMessage(e.Message);
					return(false);
				}


            }
            Q_GetKSD21->Next();
        }
    }

*/
	return( true );
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F���[�N�e�[�u����������
//
//  �@�\����
//    �z�X�g�����L�[�ɂ��ă��[�N�e�[�u�������������܂��B
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    bool				�Ftrue=�e�[�u�������������Afalse=�e�[�u�����������s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::KSDDeleteData(void)
{
	AnsiString sBufSQL;
	AnsiString sBufSQL2;
	bool bRet;
	int iCol;

   	bool bRtn;


    //��������������������������������������������������������������������������
    //�@�z�X�g���擾
	char tmpHostName[256];
	unsigned long CPUname_MaxLength = 256;
	if(GetComputerName( tmpHostName, &CPUname_MaxLength ) ){
		HostName = AnsiString(tmpHostName);
	}

    //��������������������������������������������������������������������������
	//�A���[�N�e�[�u����������
    //�A-1 KSD01W
	// Initial Query
	Q_WORK->Close();
	Q_WORK->SQL->Clear();
	// �⍇�����쐬
	sBufSQL = "delete from KSD01W where PCNAME='" + HostName + "'";
	Q_WORK->SQL->Add(sBufSQL);

	// �₢�������̎��s
	try
	{
		Q_WORK->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		ShowMessage(e.Message);
		return(false);
	}
	catch(Exception& e)
	{
		ShowMessage(e.Message);
		return(false);
	}

    //��������������������������������������������������������������������������
    //�A-2 KSD02W
	// Initial Query
	Q_WORK->Close();
	Q_WORK->SQL->Clear();
	// �⍇�����쐬
	sBufSQL = "delete from KSD02W where PCNAME='" + HostName + "'";
	Q_WORK->SQL->Add(sBufSQL);

	// �₢�������̎��s
	try
	{
		Q_WORK->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		ShowMessage(e.Message);
		return(false);
	}
	catch(Exception& e)
	{
		ShowMessage(e.Message);
		return(false);
	}

    //��������������������������������������������������������������������������
    //�A-3 KSD03W
	// Initial Query
	Q_WORK->Close();
	Q_WORK->SQL->Clear();
	// �⍇�����쐬
	sBufSQL = "delete from KSD03W where PCNAME='" + HostName + "'";
	Q_WORK->SQL->Add(sBufSQL);

	// �₢�������̎��s
	try
	{
		Q_WORK->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		ShowMessage(e.Message);
		return(false);
	}
	catch(Exception& e)
	{
		ShowMessage(e.Message);
		return(false);
	}

	return( true );
}


//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�w�肳�ꂽ���b�gNO�����݂��邩�₢���킹�܂�
//
//  �@�\����
//    �w�肵�����b�gNO�����[�N�e�[�u���iKSD01W�j�ɑ��݂��邩�ǂ������擾���܂��B
//
//  �p�����^����
//    AnsiString sDTKSHIN�F��\���Ӑ�i��
//    AnsiString sLOT	�F���b�gNO
//
//  �߂�l
//    bool				�Ftrue=�Ώۃ��b�g����Afalse=�Ώۃ��b�g�Ȃ�
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::KSD01WGetLot(AnsiString sDTKSHIN, AnsiString sLOT)
{
	AnsiString sBuf;

	sBuf = "SELECT * FROM KSD01W";
	sBuf += " WHERE PCNAME = '" + HostName + "'";
	sBuf += " AND DTKSHIN = '" + sDTKSHIN + "'";
	sBuf += " AND LOTNO = '" + sLOT + "'";

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();
	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;
    if ( Query1->Eof != true ) {
    	//����KSD01W�ɓo�^����Ă���
		return( true );
    } else {
		return( false );
    }

}
//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�w�肳�ꂽ���b�gNO�̑��荀�ڂ����݂��邩�₢���킹�܂�
//
//  �@�\����
//    �w�肵�����b�gNO�̑��荀�ڂ����[�N�e�[�u���iKSD02W�j�ɑ��݂��邩�ǂ������擾���܂��B
//
//  �p�����^����
//    AnsiString sDTKSHIN�F��\���Ӑ�i��
//    AnsiString sLOT	 �F���b�gNO
//    AnsiString sSKB_NO �F����NO
//    AnsiString sKOMK_NO�F���荀��NO
//
//  �߂�l
//    bool				�Ftrue=�Ώۃ��b�g����Afalse=�Ώۃ��b�g�Ȃ�
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::KSD02WGetLot(AnsiString sDTKSHIN, AnsiString sLOT,AnsiString sSKB_NO,AnsiString sKOMK_NO)
{
	AnsiString sBuf;

	sBuf = "SELECT * FROM KSD02W";
	sBuf += " WHERE PCNAME = '" + HostName + "'";
	sBuf += " AND DTKSHIN = '"  + sDTKSHIN + "'";
	sBuf += " AND LOTNO = '"    + sLOT + "'";
	sBuf += " AND SKB_NO = '"   + sSKB_NO + "'";
	sBuf += " AND KOMK_NO = '"  + sKOMK_NO + "'";

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();
	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;
    if ( Query1->Eof != true ) {
    	//����KSD02W�ɓo�^����Ă���
		return( true );
    } else {
		return( false );
    }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�w�肳�ꂽ���b�gNO���X�g�̗L�����b�gNO��₢���킹�܂�
//
//  �@�\����
//    �w�肵�����b�gNO���X�g������ς݃��b�g���ǂ������擾���܂��B
//
//  �p�����^����
//    AnsiString sDTKSHIN�F��\���Ӑ�i��
//    AnsiString sLOT	�F���b�gNO���X�g�i�J���}��؂�j
//    (OUT)
//    StringList sLots	�F�L���ȃ��b�gNO���X�g�iStringList�j
//
//  �߂�l
//    bool				�Ftrue=�Ώۃ��b�g����Afalse=�Ώۃ��b�g�Ȃ�
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::KSD01GetLot2(AnsiString sDTKSHIN, AnsiString sLOT)
{
	AnsiString sBuf;
	bool bRet;
	int iCol;

	if( sLOT.Trim() == "" ) return( false );


	iCol = 0;
	sBuf = "SELECT * FROM KSD01W";
    sBuf += " WHERE PCNAME='" + HostName + "'" ;
	sBuf += " AND DTKSHIN = '" + sDTKSHIN + "'";
	sBuf += " AND SKTYMD >= '" + Edt_SEIKAN_YMD->Text + "'";      //onishi

	sBuf += " AND LOTNO IN (" + sLOT + ")";
    if( iLOT_LENGTH == 5 ){
		sBuf += " ORDER BY SUBSTR(LOTNO,2)";
    } else {
		sBuf += " ORDER BY LOTNO";
    }

    bRet = false;
    sLots->Clear();
    sHins->Clear();

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();
	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;
	while(Query1->Eof == false) {

        if( iCol >= 99 ){                                                     //onishi99
			MessageDlg("��x�Ɉ����郍�b�g��(�ő�99��)�𒴂��܂����B\n�ȍ~�̃��b�g�͑ΏۊO�ɂȂ�܂��B",
            			mtWarning, TMsgDlgButtons() << mbOK , 0);
        	break;
        }

        if( !VarIsNull(Query1->FieldValues["LOTNO"]) ){
        	sLots->Add( AnsiString(Query1->FieldValues["LOTNO"]) );
        	sHins->Add( AnsiString(Query1->FieldValues["HINBAN"]) );
        }

		Query1->Next();
		iCol++;
	}

	if( iCol > 0 ) bRet = true;

	return( bRet );
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�L���ȑ��荀�ڂ̌���
//
//  �@�\����
//    �w�肵���i�ԁE���b�g�E������������L���ȑ��荀�ڂ�KSD02�f�[�^����擾��
//    �������ڂɃ`�F�b�N��t���܂�
//
//  �p�����^����
//    AnsiString sDTKSHIN�F��\���Ӑ�i��
//    AnsiString sLOT	�F���b�gNO���X�g�i�J���}��؂�j
//    bool		iSEL_SZ	�F�f�ތ������ڂ̏o�́itrue=����/false=���Ȃ��j
//    bool		iSEL_SK	�F�o�׌������ڂ̏o�́itrue=����/false=���Ȃ��j
//    bool		iSEL_TK	�F���ʏo�͍��ڂ̏o�́itrue=����/false=���Ȃ��j
//    bool		iSEL_ZR	�F�ޗ��ؖ����ڂ̏o�́itrue=����/false=���Ȃ��j
//
//  �߂�l
//    bool				�Ftrue=���������Afalse=�������s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::KSD02GetKOMOKU2(AnsiString sDTKSHIN, AnsiString sLOT,
                             bool iSEL_SZ, bool iSEL_SK, int iSEL_TK, bool iSEL_ZR)
{
	int				i, k, iCol;
	bool			bRet;
	AnsiString		sBuf;
    int				iSKB_NO;
    int				iTOKU_FLG;
    TCheckListBox*	clb;


	iCol = 0;
	sBuf = "SELECT * FROM KSD02W";
    sBuf += " WHERE PCNAME='" + HostName + "'" ;
	sBuf += " AND DTKSHIN = '" + sDTKSHIN + "'";
	sBuf += " AND SKTYMD >= '" + Edt_SEIKAN_YMD->Text + "'";      //onishi
	sBuf += " AND LOTNO IN (" + sLOT + ")";
	sBuf += " ORDER BY ORDER_NO";
	//sBuf += " ORDER BY SUBSTR(LOTNO,2), ORDER_NO";

    bRet = false;


	if( PgCtr_REPORT->ActivePage->Name == "TabSheet1" ){
        // �������я�
    	clb = dynamic_cast<TCheckListBox*>(Clb1_CHK_KOUMOKU);
    }
    else if( PgCtr_REPORT->ActivePage->Name == "TabSheet2" ){
        // �������я��i���ʁj
    	clb = dynamic_cast<TCheckListBox*>(Clb2_CHK_KOUMOKU);
    }
    else if( PgCtr_REPORT->ActivePage->Name == "TabSheet3" ){
        // �ޗ��ؖ���
    	clb = dynamic_cast<TCheckListBox*>(Clb3_CHK_KOUMOKU);
    }
    else if( PgCtr_REPORT->ActivePage->Name == "TabSheet4" ){
        // �ޗ��ؖ����i���ʁj
    	clb = dynamic_cast<TCheckListBox*>(Clb4_CHK_KOUMOKU);
    }
    else if( PgCtr_REPORT->ActivePage->Name == "TabSheet5" ){
        // �������ʎ��n��Ǘ��\
    	clb = dynamic_cast<TCheckListBox*>(Clb5_CHK_KOUMOKU);
    }
    else if( PgCtr_REPORT->ActivePage->Name == "TabSheet6" ){
        // �����o��[
    	clb = dynamic_cast<TCheckListBox*>(Clb6_CHK_KOUMOKU);
    }

    clb->Clear();

	// Initial Query
	Query2->Close();
	Query2->SQL->Clear();
	Query2->SQL->Add(sBuf);
	Query2->Open();
	Query2->Active = true;
	while(Query2->Eof == false) {

        // ���荀�ڂƂ��ďo�͂��܂��B
        iSKB_NO = AnsiString(Query2->FieldValues["SKB_NO"]).ToIntDef(9);
        if( iSKB_NO != 9 ){
            sBuf = "";
        	if( !VarIsNull(Query2->FieldValues["KOMK_NM"]) ){
        		sBuf = Query2->FieldValues["KOMK_NM"];
            }
        	if( !VarIsNull(Query2->FieldValues["KOMK_SUB"]) ){
        		sBuf = sBuf + " " + Query2->FieldValues["KOMK_SUB"];
            }
            // 2003/10/21 A.Tamura ������[TANI]�͕K�v���H
        	if( !VarIsNull(Query2->FieldValues["TANI"]) ){
        		sBuf = sBuf + " " + Query2->FieldValues["TANI"];
            }
            if( sBuf != "" ){

		        iTOKU_FLG = AnsiString(Query2->FieldValues["TOKU_FLG"]).ToIntDef(0);

                // ���o�^�̑��荀�ڂ��L�����ꍇ�����A�ǉ����܂�
                k = 0;
				for( i = 0; i < clb->Items->Count; i++){
					if( clb->Items->Strings[i] == sBuf ){
						k = 1;
                        break;
                    }
                }
                if( k == 0 ){

                	// �V�������荀�ڂ�ǉ����܂�
			        clb->Items->Add(sBuf);

                	// �f�ތ������ڂőf�ތ������ڂ�I�����鎞�̓`�F�b�NON
                    if( iSKB_NO == 1 ){
                    	if( iSEL_SZ == true ){
							clb->Checked[clb->Items->Count-1] = true;
                    	} else {
                        	clb->Checked[clb->Items->Count-1] = false;
                    	}
                    }

                	// �o�׌������ڂŏo�׌������ڂ�I�����鎞�̓`�F�b�NON
                    if( iSKB_NO == 2 ){
                    	if( iSEL_SK == true ){
							clb->Checked[clb->Items->Count-1] = true;
                    	} else {
                        	clb->Checked[clb->Items->Count-1] = false;
                    	}
                    }

                	// ���ʌ������ڂœ��ʌ������ڂ�I�����鎞�̓`�F�b�NON
                    if( iTOKU_FLG == 1 ){
                    	if( iSEL_TK == 1 ){
                        	// �u����v
							clb->Checked[clb->Items->Count-1] = true;
                    	} else if( iSEL_TK == 0 ){
                        	// �u���Ȃ��v
                        	clb->Checked[clb->Items->Count-1] = false;
                    	} else {
                        	// �u�����v
                    	}
                    }

                	// �ޗ��ؖ����ڂōޗ��ؖ����ڂ�I�����鎞�̓`�F�b�NON
                    if( iSKB_NO == 3 ){
                    	if( iSEL_ZR == true ){
							clb->Checked[clb->Items->Count-1] = true;
                    	} else {
                        	clb->Checked[clb->Items->Count-1] = false;
                    	}
                    }
				}
            }

        }

		Query2->Next();
		iCol++;
	}

	//Query1->Close();
    if( iCol > 0 ) bRet = true;

	return( bRet );
}