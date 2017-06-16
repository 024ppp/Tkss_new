//---------------------------------------------------------------------------
//
//  UnitDataAccess.cpp
//    �y�o�׌����V�X�e���|����f�[�^�폜�z
//    ���C���t�H�[���iTForm1�N���X�j�̃����o�֐��i�f�[�^�A�N�Z�X�֘A�j�̒�`
//
//  �쐬��
//    �c���@�֎i
//
//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "UnitDataAccess.h"
#include "unit1.h"
#include "Unit2.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F����ς݃f�[�^���폜���܂��B
//
//  �@�\����
//    �w�肳�ꂽ�i�ԁA���b�gNO�̑���ς݃f�[�^��
//    �e�[�u��(KSD01,KSD02,KSD03,KSD11,KSD12)����폜���܂�
//
//  �p�����^����
//    AnsiString sDTKSHIN�F��\���Ӑ�i��
//    AnsiString sLOTNO	�F���b�gNO
//
//  �߂�l
//    bool				�Ftrue = �����Afalse = ���s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
//20170406 Y.Onishi �u�폜�v���s���A���Еi�Ԃ��l��
//bool __fastcall TForm1::DelData( AnsiString sDTKSHIN, AnsiString sLOTNO )
bool __fastcall TForm1::DelData( AnsiString sDTKSHIN, AnsiString sLOTNO , AnsiString sHINBAN )
{
     AnsiString sBuf;

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����쐬
     sBuf = "DELETE from KSD01";
     sBuf +=" WHERE DTKSHIN='" + sDTKSHIN + "'";        // ���Ӑ�i��
     sBuf +=" AND LOTNO='" + sLOTNO + "'";            	// LOTNO
     //20170406 Y.Onishi
     sBuf +=" AND HINBAN='" + sHINBAN + "'";            // ���Еi��
     Query1->SQL->Add(sBuf);

     // �₢�������̎��s
     try {
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e) {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e) {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }


     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����쐬
     sBuf = "DELETE from KSD02";
     sBuf +=" WHERE DTKSHIN='" + sDTKSHIN + "'";        // ���Ӑ�i��
     sBuf +=" AND LOTNO='" + sLOTNO + "'";            	// LOTNO
     //20170406 Y.Onishi
     sBuf +=" AND HINBAN='" + sHINBAN + "'";            // ���Еi��
     Query1->SQL->Add(sBuf);

     // �₢�������̎��s
     try {
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e) {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e) {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }


     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����쐬
     sBuf = "DELETE from KSD03";
     sBuf +=" WHERE DTKSHIN='" + sDTKSHIN + "'";        // ���Ӑ�i��
     sBuf +=" AND LOTNO='" + sLOTNO + "'";            	// LOTNO
     //20170406 Y.Onishi
     sBuf +=" AND HINBAN='" + sHINBAN + "'";            // ���Еi��
     Query1->SQL->Add(sBuf);

     // �₢�������̎��s
     try {
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e) {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e) {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }


     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����쐬
     sBuf = "DELETE from KSD11";
     sBuf +=" WHERE DTKSHIN='" + sDTKSHIN + "'";        // ���Ӑ�i��
     sBuf +=" AND LOTNO='" + sLOTNO + "'";            	// LOTNO
     //20170406 Y.Onishi
     sBuf +=" AND HINBAN='" + sHINBAN + "'";            // ���Еi��
     Query1->SQL->Add(sBuf);

     // �₢�������̎��s
     try {
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e) {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e) {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }


     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����쐬
     sBuf = "DELETE from KSD12";
     sBuf +=" WHERE DTKSHIN='" + sDTKSHIN + "'";        // ���Ӑ�i��
     sBuf +=" AND LOTNO='" + sLOTNO + "'";            	// LOTNO
     //20170406 Y.Onishi
     sBuf +=" AND HINBAN='" + sHINBAN + "'";            // ���Еi��
     Query1->SQL->Add(sBuf);

     // �₢�������̎��s
     try {
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e) {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e) {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }


     return(True);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F����ς݃f�[�^���������܂��B�i�Ăяo���j
//
//  �@�\����
//    �w�肳�ꂽ�i�ԁA���b�gNO�̌���������葪��ς݃f�[�^�̌������܂�
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    int				�F1 = �������ʂ���A 0 = �������ʂȂ�
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
int __fastcall TForm1::MAIN_Serch01(void)
{
    // �V�����g�����U�N�V�������J�n
    if( Database1->InTransaction == false )
    {
        Database1->StartTransaction();
        DataSave = false;
    }

    if ( KSD01_Serch01() == 0)
    {
       return(0);
    }
    return(1);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F����ς݃f�[�^���������܂��B�i�{�́j
//
//  �@�\����
//    �w�肳�ꂽ�i�ԁA���b�gNO�̌���������葪��ς݃f�[�^�̌������A
//    StringGrid�Ƀf�[�^��ݒ肵�܂�
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    int				�F1 = �������ʂ���A 0 = �������ʂȂ�
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
//KSD01���猟��
int __fastcall TForm1::KSD01_Serch01(void)
{
	int iRow;
	AnsiString sBuf;
	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// �⍇�����s
	sBuf = "SELECT KSD01.DTKSHIN, KSD01.LOTNO, KSD01.HINBAN, KSD01.ZISNAM, KSD01.HINMEI,";
    sBuf += " KSD01.DTKSNAM, KSD01.SOKUTEI_NUM, KSD01.SOZAI_OK, KSD01.SYUKA_OK,";
    sBuf += " KSD01.SKTYMD_SZ, KSD01.SKTYMD, SM12S.TANNAM";
    sBuf += " FROM KSD01";
    sBuf += " LEFT JOIN SM12S ON KSD01.UPDCHR = SM12S.TANSYA";
	sBuf += " WHERE KSD01.DTKSHIN LIKE '" + EdtHIN->Text + "%'";
	sBuf += " AND KSD01.LOTNO LIKE '" + EdtLOT->Text + "%'";
	sBuf += " ORDER BY KSD01.DTKSHIN, SUBSTR(KSD01.LOTNO,2)";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	if ( Query1->Bof == true && Query1->Eof ) {
		//�������� �O��
		return(0);

	}
	iRow = 1;

	while( !Query1->Eof ){

		// �O���b�h�̍ő�s���������Ă��Ȃ����`�F�b�N����
		if( iRow >= SGr_List->RowCount ){
			SGr_List->RowCount = iRow + 1;
		}

		// �O���b�h�Ƀf�[�^���Z�b�g���܂��B
		sBuf = iRow ;
		SGr_List->Cells[0][iRow] = AnsiString::StringOfChar(' ', 7-sBuf.Length()) + sBuf;    //No
		sBuf = iRow + 1;

		sBuf = Form1->Query1->FieldValues["DTKSHIN"];
		SGr_List->Cells[1][iRow] = sBuf;   //���Ӑ�i��

		sBuf = Form1->Query1->FieldValues["LOTNO"];
		SGr_List->Cells[2][iRow] = sBuf;   //���b�gNO

        if( VarIsNull(Query1->FieldValues["HINBAN"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["HINBAN"];
		}
        SGr_List->Cells[3][iRow] = sBuf;   //���Еi��

        if( VarIsNull(Query1->FieldValues["ZISNAM"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["ZISNAM"];
		}
        SGr_List->Cells[4][iRow] = sBuf;   //�ގ���

        if( VarIsNull(Query1->FieldValues["HINMEI"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["HINMEI"];
		}
        SGr_List->Cells[5][iRow] = sBuf;   //�i��

        if( VarIsNull(Query1->FieldValues["DTKSNAM"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["DTKSNAM"];
		}
        SGr_List->Cells[6][iRow] = sBuf;   //��\���Ӑ於

		sBuf = Query1->FieldValues["SOKUTEI_NUM"];
		SGr_List->Cells[7][iRow] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;	//���荀�ڐ�

		sBuf = Query1->FieldValues["SOZAI_OK"];
        switch( sBuf.ToIntDef(-1) ){
        	case -1:	sBuf = " ���蒆";	break;
        	case  0:	sBuf = "  �n�j";	break;
        	case  1:	sBuf = "  �m�f";	break;
        	case  2:
            default:	sBuf = "";			break;
		}
        SGr_List->Cells[8][iRow] = sBuf;   //�f�ޔ���

		sBuf = Query1->FieldValues["SYUKA_OK"];
        switch( sBuf.ToIntDef(-1) ){
        	case -1:	sBuf = " ���蒆";	break;
        	case  0:	sBuf = "  �n�j";	break;
        	case  1:	sBuf = "  �m�f";	break;
        	case  2:
            default:	sBuf = "";			break;
		}
		SGr_List->Cells[9][iRow] = sBuf;   //�o�ה���

        if( VarIsNull(Query1->FieldValues["SKTYMD_SZ"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["SKTYMD_SZ"];
		}
    	if( sBuf.Length() == 8 ){
    		sBuf.Insert("/",5);
       		sBuf.Insert("/",8);
   		}
		SGr_List->Cells[10][iRow] = sBuf;  //�f�ޗp�����

        if( VarIsNull(Query1->FieldValues["SKTYMD"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["SKTYMD"];
		}
    	if( sBuf.Length() == 8 ){
    		sBuf.Insert("/",5);
       		sBuf.Insert("/",8);
   		}
		SGr_List->Cells[11][iRow] = sBuf;  //�o�חp�����

        if( VarIsNull(Query1->FieldValues["TANNAM"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["TANNAM"];
		}
        SGr_List->Cells[12][iRow] = sBuf;  //��\�X�V��

		// �J�[�\�������ɃZ�b�g����
		Query1->Next();

		iRow += 1;
	}

    SGr_List->RowCount = iRow + 1;
    SGr_List->Cells[ 0][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[ 1][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[ 2][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[ 3][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[ 4][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[ 5][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[ 6][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[ 7][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[ 8][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[ 9][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[10][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[11][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[12][SGr_List->RowCount - 1 ] = "";

	return(1);
}


