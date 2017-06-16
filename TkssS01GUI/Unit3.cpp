//---------------------------------------------------------------------------
//
//  Unit3.cpp
//    �y�o�׌����V�X�e���|���������o�^�����z
//    ���C���t�H�[���iTForm1�N���X�j�̃����o�֐��̒�`
//
//  �쐬��
//    �����@�b��
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�f�[�^�ǉ�
//
//  �@�\����
//    KSD21�Ƀf�[�^��ǉ����܂��B
//
//  �p�����^����
//    �Ȃ�
//
//  �߂�l
//    AnsiString			�F""=�ǉ����� �G���[���b�Z�[�W=�ǉ����s
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
AnsiString __fastcall TForm1::AddDataKSD21(void)
{
	AnsiString sBuf;
	int iEnd;
	int iSOKU_VAL_SU;


	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// �⍇�����쐬
	sBufSQL = "insert into KSD21(";
	sBufSQL += " DTKSHIN, LOTNO, HINBAN, ";
	sBufSQL += " DTKSCOD, DTKSNAM, ZISNAM, ";
	//sBufSQL += " SOKUTEI_NUM, ";
	//sBufSQL += " SOZAI_OK, ";
	sBufSQL += " MEMO, ";
	sBufSQL += " SKTYMD, ";
	//sBufSQL += " ADDYMD, ADDTIM, ";
	//sBufSQL += " UPDYMD, UPDTIM, ";
	sBufSQL += " UPDCHR ";
	sBufSQL += " )";

	sBufSQL += " values(";
	sBufSQL += " '" + KSD21.DTKSHIN  		+ "',";
	sBufSQL += " '" + KSD21.LOTNO  			+ "',";
	sBufSQL += " '" + KSD21.HINBAN  		+ "',";
	sBufSQL += " '" + KSD21.DTKSCOD  		+ "',";
	sBufSQL += " '" + KSD21.DTKSNAM  		+ "',";
	sBufSQL += " '" + KSD21.ZISNAM  		+ "',";
	//sBufSQL +=        KSD21.SOKUTEI_NUM  	+ "," ;
	//sBufSQL +=        KSD21.SOZAI_OK  		+ "," ;
	sBufSQL += " '" + KSD21.MEMO  			+ "',";
	sBufSQL += " '" + KSD21.SKTYMD  		+ "',";
	//sBufSQL += " '" + KSD21.ADDYMD  		+ "',";
	//sBufSQL += " '" + KSD21.ADDTIM 			+ "',";
	//sBufSQL += " '" + KSD21.UPDYMD  		+ "',";
	//sBufSQL += " '" + KSD21.UPDTIM  		+ "',";
	sBufSQL +=        KSD21.UPDCHR        		  ;
	sBufSQL += ")";

	Query1->SQL->Add(sBufSQL);

	// �₢�������̎��s
	try
	{
		Query1->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
	    return(e.Message);
	}
	catch(Exception& e)
	{
	    return(e.Message);
	}

	return("");

}


/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�f�[�^�X�V
//
//  �@�\����
//    KSD21�̃f�[�^���X�V���܂��B
//
//  �p�����^����
//    �Ȃ�
//
//  �߂�l
//    AnsiString			�F""=�X�V���� �G���[���b�Z�[�W=�X�V���s
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
AnsiString __fastcall TForm1::UpdDataKSD21(void)
{
	AnsiString sBuf;
	int iEnd;
	int iSOKU_VAL_SU;


	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// �⍇�����쐬
	sBufSQL = "update KSD21 set ";
	//sBufSQL += "DTKSHIN='" 	+ KSD21.DTKSHIN  		+ "',";
	//sBufSQL += "LOTNO='" 	+ KSD21.LOTNO  			+ "',";
	//sBufSQL += "HINBAN='" 		+ KSD21.HINBAN  		+ "',";
	sBufSQL += "DTKSCOD='" 		+ KSD21.DTKSCOD 		+ "',";
	sBufSQL += "DTKSNAM='" 		+ KSD21.DTKSNAM  		+ "',";
	sBufSQL += "ZISNAM='" 		+ KSD21.ZISNAM  		+ "',";
	//sBufSQL += "SOKUTEI_NUM=" 	+ KSD21.SOKUTEI_NUM  	+ "," ;
	//sBufSQL += "SOZAI_OK=" 	+ KSD21.SOZAI_OK  		+ "," ;
	sBufSQL += "MEMO='" 		+ KSD21.MEMO  			+ "',";
	sBufSQL += "SKTYMD='" 		+ KSD21.SKTYMD  		+ "',";
	//sBufSQL += "ADDYMD='" 		+ KSD21.ADDYMD  		+ "',";
	//sBufSQL += "ADDTIM='" 		+ KSD21.ADDTIM  		+ "',";
	//sBufSQL += "UPDYMD='" 		+ KSD21.UPDYMD  		+ "',";
	//sBufSQL += "UPDTIM='" 		+ KSD21.UPDTIM  		+ "',";
	sBufSQL += "UPDCHR=" 		+ KSD21.UPDCHR        		  ;

	sBufSQL += " where  ";
	sBufSQL += "DTKSHIN='" 		+ KSD21.DTKSHIN  		+ "' AND "	;
	sBufSQL += "HINBAN='" 		+ KSD21.HINBAN  		+ "' AND "	;
	sBufSQL += "LOTNO='" 		+ KSD21.LOTNO  			+ "'  "	;


	Query1->SQL->Add(sBufSQL);

	// �₢�������̎��s
	try
	{
		Query1->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
	    return(e.Message);
	}
	catch(Exception& e)
	{
	    return(e.Message);
	}

	return("");

}

/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�f�[�^�ǉ�
//
//  �@�\����
//    KSD22�Ƀf�[�^��ǉ����܂��B
//
//  �p�����^����
//    �Ȃ�
//
//  �߂�l
//    AnsiString			�F""=�ǉ����� �G���[���b�Z�[�W=�ǉ����s
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
AnsiString __fastcall TForm1::AddDataKSD22(void)
{
	AnsiString sBuf;
	int i;
	int iEnd;
	int iSOKU_VAL_SU;


	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// �⍇�����쐬
	sBufSQL = "insert into KSD22(";
	sBufSQL += " DTKSHIN, LOTNO, HINBAN, UNQ_NO, KOMK_NO, ";
	sBufSQL += " KOMK_NM, KOMK_ENG, KOMK_SUB, ";
	sBufSQL += " KOMK_SUB_ENG, KIKI_NO, KIKI_NM, ";
	sBufSQL += " TANI, KIKA_TYPE, KIKA_KIND, ";
	sBufSQL += " KIKA_DECI, KIKA_NUM1, KIKA_NUM2, ";
	sBufSQL += " KIKA_NUM3, KIKA_STR, KIKA_SUB1, ";
	sBufSQL += " KIKA_SUB2, SOKU_SU, VALUE_TYPE, ";
	sBufSQL += " VALUE_DECI, SOKU_VAL01, SOKU_VAL02, ";
	sBufSQL += " SOKU_VAL03, SOKU_VAL04, SOKU_VAL05, ";
	sBufSQL += " SOKU_VAL06, SOKU_VAL07, SOKU_VAL08, ";
	sBufSQL += " SOKU_VAL09, SOKU_VAL10, SOKU_VAL_SU, ";
	sBufSQL += " SOKU_VAL_AVE, SOKU_VAL_MAX, SOKU_VAL_MIN, ";
	sBufSQL += " SOKU_OK, SKTYMD, ADDYMD, ADDTIM, ";
	sBufSQL += " UPDYMD, UPDTIM, UPDCHR, UPDCNT ";
	sBufSQL += " )";

	sBufSQL += " values(";
	sBufSQL += " '" + KSD22.DTKSHIN	 		+ "',"	;
	sBufSQL += " '" + KSD22.LOTNO	  		+ "',"	;
	sBufSQL += " '" + KSD22.HINBAN	  		+ "',"	;
	sBufSQL +=        KSD22.UNQ_NO			+ ","	;
	sBufSQL +=        KSD22.KOMK_NO			+ ","	;
	sBufSQL += " '" + KSD22.KOMK_NM	  		+ "',"	;
	sBufSQL += " '" + KSD22.KOMK_ENG	  	+ "',"	;
	sBufSQL += " '" + KSD22.KOMK_SUB	  	+ "',"	;
	sBufSQL += " '" + KSD22.KOMK_SUB_ENG	+ "',"	;
	sBufSQL +=        KSD22.KIKI_NO			+ ","	;
	sBufSQL += " '" + KSD22.KIKI_NM	  		+ "',"	;
	sBufSQL += " '" + KSD22.TANI	  		+ "',"	;
	sBufSQL +=        KSD22.KIKA_TYPE		+ ","	;
	sBufSQL +=        KSD22.KIKA_KIND		+ ","	;
	sBufSQL +=        KSD22.KIKA_DECI		+ ","	;
	sBufSQL +=        KSD22.KIKA_NUM1		+ ","	;
	sBufSQL +=        KSD22.KIKA_NUM2		+ ","	;
	sBufSQL +=        KSD22.KIKA_NUM3		+ ","	;
	sBufSQL += " '" + KSD22.KIKA_STR	  	+ "',"	;
	sBufSQL += " '" + KSD22.KIKA_SUB1	  	+ "',"	;
	sBufSQL += " '" + KSD22.KIKA_SUB2	  	+ "',"	;
	sBufSQL +=        KSD22.SOKU_SU			+ ","	;
	sBufSQL +=        KSD22.VALUE_TYPE		+ ","	;
	sBufSQL += " '" + KSD22.VALUE_DECI	  	+ "',"	;
	iSOKU_VAL_SU = atoi(KSD22.SOKU_VAL_SU.c_str());
	if ( iSOKU_VAL_SU > 10 ) {
		iEnd = 10;
	} else {
		iEnd = iSOKU_VAL_SU;
	}
	for ( i = 0; i < iEnd; i++ ) {
		sBufSQL += " '" + KSD22.SOKU_VAL[i]	+ "',"	;
	}
	for ( i = iEnd; i < 10; i++ ) {
		sBufSQL += " ' ',"	;
	}
	sBufSQL +=        KSD22.SOKU_VAL_SU		+ ","	;
	sBufSQL +=        KSD22.SOKU_VAL_AVE	+ ","	;
	sBufSQL +=        KSD22.SOKU_VAL_MAX	+ ","	;
	sBufSQL +=        KSD22.SOKU_VAL_MIN	+ ","	;
	sBufSQL +=        KSD22.SOKU_OK			+ ","	;
	sBufSQL += " '" + KSD22.SKTYMD	  		+ "',"	;
	sBufSQL += " '" + KSD22.ADDYMD	  		+ "',"	;
	sBufSQL += " '" + KSD22.ADDTIM	  		+ "',"	;
	sBufSQL += " '" + KSD22.UPDYMD	  		+ "',"	;
	sBufSQL += " '" + KSD22.UPDTIM	 		+ "',"	;
	sBufSQL +=        KSD22.UPDCHR			+ ","	;
	sBufSQL +=        KSD22.UPDCNT					;
	sBufSQL += ")";

	Query1->SQL->Add(sBufSQL);

	// �₢�������̎��s
	try
	{
		Query1->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		return(e.Message);
	}
	catch(Exception& e)
	{
	    return(e.Message);
	}

	return("");

}


/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�f�[�^�X�V
//
//  �@�\����
//    KSD22�̃f�[�^���X�V���܂��B
//
//  �p�����^����
//    �Ȃ�
//
//  �߂�l
//    AnsiString			�F""=�X�V���� �G���[���b�Z�[�W=�X�V���s
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
//KSD22�̃f�[�^���C�����܂��B
AnsiString __fastcall TForm1::UpdDataKSD22(void)
{
	AnsiString sBuf;
	int i;
	int iEnd;
	int iSOKU_VAL_SU;


	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// �⍇�����쐬
	sBufSQL = "update KSD22 set ";
	//sBufSQL += "DTKSHIN='" 		+ KSD22.DTKSHIN  		+ "',"	;
	//sBufSQL += "LOTNO='" 		+ KSD22.LOTNO  			+ "',"	;
	//sBufSQL += "UNQ_NO="  		+ KSD22.UNQ_NO			+ ","	;
	sBufSQL += "KOMK_NO="  			+ KSD22.KOMK_NO			+ ","	;
	sBufSQL += "KOMK_NM='" 			+ KSD22.KOMK_NM  		+ "',"	;
	sBufSQL += "KOMK_ENG='" 		+ KSD22.KOMK_ENG  		+ "',"	;
	sBufSQL += "KOMK_SUB='" 		+ KSD22.KOMK_SUB  		+ "',"	;
	sBufSQL += "KOMK_SUB_ENG='" 	+ KSD22.KOMK_SUB_ENG  	+ "',"	;
	sBufSQL += "KIKI_NO="  			+ KSD22.KIKI_NO			+ ","	;
	sBufSQL += "KIKI_NM='" 			+ KSD22.KIKI_NM  		+ "',"	;
	sBufSQL += "TANI='" 			+ KSD22.TANI  			+ "',"	;
	sBufSQL += "KIKA_TYPE="  		+ KSD22.KIKA_TYPE		+ ","	;
	sBufSQL += "KIKA_KIND="  		+ KSD22.KIKA_KIND		+ ","	;
	sBufSQL += "KIKA_DECI="  		+ KSD22.KIKA_DECI		+ ","	;
	sBufSQL += "KIKA_NUM1="  		+ KSD22.KIKA_NUM1		+ ","	;
	sBufSQL += "KIKA_NUM2="  		+ KSD22.KIKA_NUM2		+ ","	;
	sBufSQL += "KIKA_NUM3="  		+ KSD22.KIKA_NUM3		+ ","	;
	sBufSQL += "KIKA_STR='" 		+ KSD22.KIKA_STR  		+ "',"	;
	sBufSQL += "KIKA_SUB1='" 		+ KSD22.KIKA_SUB1  		+ "',"	;
	sBufSQL += "KIKA_SUB2='"		+ KSD22.KIKA_SUB2  		+ "',"	;
	sBufSQL += "SOKU_SU="  			+ KSD22.SOKU_SU			+ ","	;
	sBufSQL += "VALUE_TYPE="  		+ KSD22.VALUE_TYPE		+ ","	;
	sBufSQL += "VALUE_DECI='" 		+ KSD22.VALUE_DECI  	+ "',"	;

	//sBufSQL += "SOKU_VAL[iPos]='" 	+ KSD22.SOKU_VAL[iPos]  + "',"	;
	iSOKU_VAL_SU = atoi(KSD22.SOKU_VAL_SU.c_str());
	if ( iSOKU_VAL_SU > 10 ) {
		iEnd = 10;
	} else {
		iEnd = iSOKU_VAL_SU;
	}
	for ( i = 0; i < iEnd; i++ ) {
		sBufSQL += "SOKU_VAL" + FormatFloat("00",i+1) + "='" 	+ KSD22.SOKU_VAL[i]  + "',";
	}
	for ( i = iEnd; i < 10; i++ ) {
		sBufSQL += "SOKU_VAL" + FormatFloat("00",i+1) + "=' ',";
	}

	sBufSQL += "SOKU_VAL_SU="  		+ KSD22.SOKU_VAL_SU		+ ","	;
	sBufSQL += "SOKU_VAL_AVE="  	+ KSD22.SOKU_VAL_AVE	+ ","	;
	sBufSQL += "SOKU_VAL_MAX="  	+ KSD22.SOKU_VAL_MAX	+ ","	;
	sBufSQL += "SOKU_VAL_MIN="  	+ KSD22.SOKU_VAL_MIN	+ ","	;
	sBufSQL += "SOKU_OK="  			+ KSD22.SOKU_OK			+ ","	;
	sBufSQL += "SKTYMD='" 			+ KSD22.SKTYMD  		+ "',"	;
	sBufSQL += "ADDYMD='" 			+ KSD22.ADDYMD  		+ "',"	;
	sBufSQL += "ADDTIM='" 			+ KSD22.ADDTIM  		+ "',"	;
	sBufSQL += "UPDYMD='" 			+ KSD22.UPDYMD  		+ "',"	;
	sBufSQL += "UPDTIM='" 			+ KSD22.UPDTIM  		+ "',"	;
	sBufSQL += "UPDCHR="  			+ KSD22.UPDCHR			+ ","	;
	sBufSQL += "UPDCNT="  			+ KSD22.UPDCNT					;

	sBufSQL += " where  ";
	sBufSQL += "DTKSHIN='" 			+ KSD22.DTKSHIN  		+ "' AND "	;
	sBufSQL += "LOTNO='" 			+ KSD22.LOTNO  			+ "' AND "	;
	sBufSQL += "HINBAN='" 			+ KSD22.HINBAN 			+ "' AND "	;
	sBufSQL += "UNQ_NO="  			+ KSD22.UNQ_NO						;


	Query1->SQL->Add(sBufSQL);
	// �₢�������̎��s
	try
	{
		Query1->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
	    return(e.Message);
	}
	catch(Exception& e)
	{
	    return(e.Message);
	}

	return("");

}

/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�f�[�^�ǉ�
//
//  �@�\����
//    KSD23�Ƀf�[�^��ǉ����܂��B
//
//  �p�����^����
//    �Ȃ�
//
//  �߂�l
//    AnsiString			�F""=�ǉ����� �G���[���b�Z�[�W=�ǉ����s
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
AnsiString __fastcall TForm1::AddDataKSD23(int iPos)
{
     AnsiString sBuf;


     // Initial Query
	 Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����쐬
     sBufSQL = "insert into KSD23(";
     sBufSQL += " DTKSHIN, LOTNO, HINBAN, UNQ_NO, SOKU_NO, SOKU_VAL  ";
     sBufSQL += " )";

     sBufSQL += " values(";
     sBufSQL += " '" + KSD22.DTKSHIN  + "',";  	//���Ӑ�i��
     sBufSQL += " '" + KSD22.LOTNO    + "',";  	//���b�gNO
     sBufSQL += " '" + KSD22.HINBAN   + "',";  	//���Еi��
	 sBufSQL +=        KSD22.UNQ_NO   + ",";  		//����NO
	 sBufSQL +=        IntToStr(iPos+1)  + ",";  	//����NO
     sBufSQL +=        KSD22.SOKU_VAL[iPos] ;  	//����l
	 sBufSQL += ")";

     Query1->SQL->Add(sBufSQL);

     // �₢�������̎��s
     try
	 {
		Query1->ExecSQL();
	 }
     catch(EDatabaseError& e)
     {
         return(e.Message);
     }
     catch(Exception& e)
     {
         return(e.Message);
     }

     return("");

}

/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�f�[�^�폜
//
//  �@�\����
//    KSD23�̃f�[�^���폜���܂��B
//
//  �p�����^����
//    �Ȃ�
//
//  �߂�l
//    AnsiString			�F""=�폜���� �G���[���b�Z�[�W=�폜���s
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
AnsiString __fastcall TForm1::DelDataKSD23(void)
{
     AnsiString sBuf;

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����쐬
     sBufSQL = "delete from KSD23 ";
     sBufSQL +=" where DTKSHIN='" 	+ KSD22.DTKSHIN + "'";  	//���Ӑ�i��
     sBufSQL +=" AND LOTNO='" 		+ KSD22.LOTNO + "'";      	//���b�gNO
     sBufSQL +=" AND HINBAN='" 		+ KSD22.HINBAN + "'";      	//���Еi��
     sBufSQL +=" AND UNQ_NO=" 		+ KSD22.UNQ_NO;         	//����NO

     Query1->SQL->Add(sBufSQL);

     // �₢�������̎��s
     try
	 {
		Query1->ExecSQL();
	 }
	 catch(EDatabaseError& e)
     {
         return(e.Message);
     }
     catch(Exception& e)
     {
         return(e.Message);
     }

     return("");

}

/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�f�[�^�X�V
//
//  �@�\����
//    KSD21�̍X�V�񐔁E�f�ޑ���f�[�^�E�f�ޑ��萔�E�o�^���E�C�������C�����܂��B
//
//  �p�����^����
//    �Ȃ�
//
//  �߂�l
//    AnsiString			�F""=�X�V���� �G���[���b�Z�[�W=�X�V���s
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
AnsiString __fastcall TForm1::UpdDataKSD21_UPDCNT(AnsiString swDTKSHIN,AnsiString swLOTNO)
{
	AnsiString sBuf;
	AnsiString sUPDCNT;
	int iUPDCNT;
	AnsiString sSOZAI_OK;
	int iSOZAI_OK;
	AnsiString sSOKUTEI_NUM;
	AnsiString sADDYMD;
	AnsiString sADDTIM;
	AnsiString sUPDYMD;
	AnsiString sUPDTIM;

	//�@�f�ނ̑��茋�ʂ��擾
	//Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// �⍇�����s
	sBufSQL = "";
	//SELECT��
	sBufSQL += " SELECT ";
	sBufSQL += " SUM(SOKU_OK) As SUMSOKU_OK ";
	//�e�[�u����
	sBufSQL += " FROM KSD22 ";
	//WHERE��
	sBufSQL += " WHERE  ";
	sBufSQL += " DTKSHIN ='" + swDTKSHIN + "' AND ";
	sBufSQL += " LOTNO ='"   + swLOTNO + "' ";

	Query1->SQL->Add(sBufSQL);
	Query1->Open();
	Query1->Active = true;

	if ( Query1->Bof && Query1->Eof ) {
		//�������� �O��
		return("��������0��");
	}
	sSOZAI_OK = Null_S(Query1->FieldValues["SUMSOKU_OK"]);
	iSOZAI_OK = atoi(sSOZAI_OK.c_str());
	if ( iSOZAI_OK == 0 ) {
		sSOZAI_OK = "0";
	} else {
		sSOZAI_OK = "1";
	}


	//�A�X�V�񐔂��擾
	//�C�o�^�����擾
	//Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// �⍇�����s
	sBufSQL = "";
	//SELECT��
	sBufSQL += " SELECT ";
	sBufSQL += " UPDCNT, ADDYMD, ADDTIM ";
	//�e�[�u����
	sBufSQL += " FROM KSD21 ";
	//WHERE��
	sBufSQL += " WHERE  ";
	sBufSQL += " DTKSHIN ='" + swDTKSHIN + "' AND ";
	sBufSQL += " LOTNO ='"   + swLOTNO + "' ";

	Query1->SQL->Add(sBufSQL);
	Query1->Open();
	Query1->Active = true;

	if ( Query1->Bof && Query1->Eof ) {
		//�������� �O��
		return("��������0��");
	}
	//�X�V�񐔂̌���
	sUPDCNT = Null_S(Query1->FieldValues["UPDCNT"]);
	iUPDCNT = atoi(sUPDCNT.c_str());
	iUPDCNT++;
	sUPDCNT = IntToStr(iUPDCNT);

	//�o�^���E�X�V���̌���
	sADDYMD = Null_S(Query1->FieldValues["ADDYMD"]);
	sADDTIM = Null_S(Query1->FieldValues["ADDTIM"]);
	if ( Trim(sADDYMD) == "" ) {
		sADDYMD = FormatDateTime("yyyymmdd",Now());
		sADDTIM = FormatDateTime("hhnn",Now());
		sUPDYMD = " ";
		sUPDTIM = " ";
	} else {
		sUPDYMD = FormatDateTime("yyyymmdd",Now());
		sUPDTIM = FormatDateTime("hhnn",Now());
	}

	//�B�f�ޑ��萔���擾
	//Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// �⍇�����s
	sBufSQL = "";
	//SELECT��
	sBufSQL += " SELECT ";
	sBufSQL += " COUNT(*) As SOKUTEI_NUM_COUNT ";
	//�e�[�u����
	sBufSQL += " FROM KSD22 ";
	//WHERE��
	sBufSQL += " WHERE  ";
	sBufSQL += " DTKSHIN ='" + swDTKSHIN + "' AND ";
	sBufSQL += " LOTNO ='"   + swLOTNO + "' ";

	Query1->SQL->Add(sBufSQL);
	Query1->Open();
	Query1->Active = true;

	if ( Query1->Bof && Query1->Eof ) {
		//�������� �O��
		return("��������0��");
	}
	sSOKUTEI_NUM = Null_S(Query1->FieldValues["SOKUTEI_NUM_COUNT"]);


	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// �⍇�����쐬
	sBufSQL = "update KSD21 set ";
	sBufSQL += " UPDCNT=" 		+ sUPDCNT;
	sBufSQL += ",SOZAI_OK=" 	+ sSOZAI_OK;
	sBufSQL += ",SOKUTEI_NUM=" 	+ sSOKUTEI_NUM;
	sBufSQL += ",ADDYMD='" 		+ sADDYMD + "'" ;
	sBufSQL += ",ADDTIM='" 		+ sADDTIM + "'" ;
	sBufSQL += ",UPDYMD='" 		+ sUPDYMD + "'" ;
	sBufSQL += ",UPDTIM='" 		+ sUPDTIM + "'" ;

	sBufSQL += " where  ";
	sBufSQL += "DTKSHIN='" 		+ swDTKSHIN  		+ "' AND "	;
	sBufSQL += "LOTNO='" 		+ swLOTNO  			+ "'  "	;

	Query1->SQL->Add(sBufSQL);

	// �₢�������̎��s
	try
	{
		Query1->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		return(e.Message);
	}
	catch(Exception& e)
	{
		return(e.Message);
	}

	return("");

}

