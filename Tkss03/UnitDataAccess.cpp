//---------------------------------------------------------------------------
//
//  UnitDataAccess.cpp
//    �y�o�׌����V�X�e���|���l���O�o�^�z
//    ���C���t�H�[���t�H�[���i�c�a�A�N�Z�X�֘A�j�iTForm1�N���X�j�̃����o�֐��̒�`
//
//  �쐬��
//    �s��@�a�O
//
//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "UnitDataAccess.h"
#include "unit1.h"
#include "Unit2.h"
extern KSD91_DATA Tmp_KSD91;             // �I���������l�f�[�^
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�FKSD91�\���̂̏��������s�Ȃ��܂�
//
//  �@�\����
//    KSD91�\���̂̏��������s�Ȃ��܂�
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
void  __fastcall TForm1::Tmp_KSD91_SYOKIKA(void)
{
	//Tmp_KSD91������
	Tmp_KSD91.KENSA_YMD	= "";		// �����N����
	Tmp_KSD91.DTKSHIN	= "";		// ���Ӑ�i��
	Tmp_KSD91.HINBAN	= "";		// ���Еi��
	Tmp_KSD91.LOTNO		= "";		// ���b�gNo
	Tmp_KSD91.ADDYMD	= "";		// �o�^��
	Tmp_KSD91.ADDTIM	= "";		// �o�^����
	Tmp_KSD91.UPDYMD	= "";		// �ύX��
	Tmp_KSD91.UPDTIM	= "";		// �ύX����
	Tmp_KSD91.UPDCHR	= 0;		// �X�V��
	Tmp_KSD91.UPDCNT	= 0;		// �X�V��
    Tmp_KSD91.MEMO      = "";       // ���l
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�e�[�u��KSD91�փf�[�^�̓o�^���s�Ȃ��܂�
//
//  �@�\����
//    �e�[�u��KSD91�փf�[�^�̓o�^���s�Ȃ��܂�
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    true = �����Afalse = ���s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::AddData()
{
     AnsiString sBuf;

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����쐬
     sBuf = "select * from KSD91";
     sBuf +=" WHERE DTKSHIN='" + Tmp_KSD91.DTKSHIN + "'";          // ���Ӑ�i��
     sBuf +=" AND   HINBAN ='" + Tmp_KSD91.HINBAN + "'";           // ���Еi��
     sBuf +=" AND   LOTNO  ='" + Tmp_KSD91.LOTNO + "'";            // LOTNO
     sBuf +=" AND   MEMO   ='" + Tmp_KSD91.MEMO + "'";        	   // ���l
     sBuf +=" AND   ADDYMD ='" + Tmp_KSD91.ADDYMD + "'";           // �o�^��
     sBuf +=" AND   ADDTIM ='" + Tmp_KSD91.ADDTIM + "'";           // �o�^����
     sBuf +=" AND   UPDYMD ='" + Tmp_KSD91.UPDYMD + "'";           // �X�V��
     sBuf +=" AND   UPDTIM ='" + Tmp_KSD91.UPDTIM + "'";           // �X�V����
     sBuf +=" AND   UPDCHR ='" + IntToStr(Tmp_KSD91.UPDCHR) + "'"; // �X�V�S����
     sBuf +=" AND   UPDCNT ='" + IntToStr(Tmp_KSD91.UPDCNT) + "'"; // �X�V��

     Query1->SQL->Add(sBuf);

     // �₢�������̎��s
     try
     {
        Query1->Open();
        Query1->Active = true;

        if( !(Query1->Eof == True &&  Query1->Bof == True) ){
            SBr1->Panels->Items[0]->Text = "���ɓo�^����Ă��܂��B";
            SBr1->Update();
            return(False);
        }
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }


     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����쐬
     sBuf = "insert into KSD91(";
     sBuf += " DTKSHIN, HINBAN, LOTNO, MEMO, ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT";
     sBuf += " )";

     sBuf += " VALUES('";
     sBuf += Tmp_KSD91.DTKSHIN			+ "','";	//	���Ӑ�i��
     sBuf += Tmp_KSD91.HINBAN		    + "','";	//	���Еi��
     sBuf += Tmp_KSD91.LOTNO 		    + "','";	//	���b�gNO
     sBuf += Tmp_KSD91.MEMO			    + "','";	//	���l
     sBuf += Tmp_KSD91.ADDYMD			+ "','";	//	�o�^��
     sBuf += Tmp_KSD91.ADDTIM		    + "','";	//	�o�^����
     sBuf += Tmp_KSD91.UPDYMD			+ "','";	//	�o�^��
     sBuf += Tmp_KSD91.UPDTIM			+ "',";		//	�o�^����
     sBuf += IntToStr(Tmp_KSD91.UPDCHR)	+ ",";		//	�X�V��
     sBuf += IntToStr(Tmp_KSD91.UPDCNT)  ;			//	�X�V��
     sBuf += ")";

     Query1->SQL->Add(sBuf);

     // �₢�������̎��s
     try
     {
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }

     return(True);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�e�[�u��KSD91�̃��R�[�h���X�V���܂�
//
//  �@�\����
//    �e�[�u��KSD91�̃��R�[�h���X�V���܂�
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    true = �����Afalse = ���s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::CollectData()
{
     AnsiString sBuf;

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����쐬
     sBuf = "update KSD91 set ";
	 sBuf +=	"DTKSHIN='"	+ Tmp_KSD91.DTKSHIN + "', "	;    //	���Ӑ�i��
	 sBuf +=	"HINBAN ='"	+ Tmp_KSD91.HINBAN  + "', "	;    //	���Еi��
	 sBuf +=	"LOTNO  ='"	+ Tmp_KSD91.LOTNO   + "', "	;    //	���b�gNO
	 sBuf +=	"MEMO   ='"	+ Tmp_KSD91.MEMO	+ "', "	;    //	���l
	 sBuf +=	"ADDYMD ='"	+ Tmp_KSD91.ADDYMD  + "', "	;    //	�o�^��
	 sBuf +=	"ADDTIM ='"	+ Tmp_KSD91.ADDTIM  + "', "	;    //	�o�^����
	 sBuf +=	"UPDYMD ='"	+ Tmp_KSD91.UPDYMD  + "', "	;    //	�X�V��
	 sBuf +=	"UPDTIM ='"	+ Tmp_KSD91.UPDTIM  + "', "	;    //	�X�V����
	 sBuf +=	"UPDCHR ="	+ IntToStr(Tmp_KSD91.UPDCHR) + ", "	; // �X�V��
	 sBuf +=	"UPDCNT ="	+ IntToStr(Tmp_KSD91.UPDCNT) + " "	; // �X�V��

     sBuf += "WHERE DTKSHIN='" + Tmp_KSD91.DTKSHIN + "'";
     sBuf += " AND  HINBAN ='" + Tmp_KSD91.HINBAN + "'";
     sBuf += " AND  LOTNO  ='" + Tmp_KSD91.LOTNO + "'";

     Query1->SQL->Add(sBuf);

     // �₢�������̎��s
     try
     {
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }

     return(True);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�e�[�u��KSD91�̃��R�[�h���폜���܂�
//
//  �@�\����
//    �e�[�u��KSD91�̃��R�[�h���폜���܂�
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    true = �����Afalse = ���s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::DelData()
{
     AnsiString sBuf;

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();


     // �⍇�����쐬
     sBuf = "select * from KSD91 ";
     sBuf +=" WHERE DTKSHIN='" + Tmp_KSD91.DTKSHIN + "'";        // ���Ӑ�i��
     sBuf +=" AND   HINBAN ='" + Tmp_KSD91.HINBAN  + "'";        // ���Еi��
     sBuf +=" AND   LOTNO  ='" + Tmp_KSD91.LOTNO   + "'";        // LOTNO

     Query1->SQL->Add(sBuf);

     // �₢�������̎��s
     try
     {
        Query1->Open();
        Query1->Active = true;

        if( Query1->Eof == True &&  Query1->Bof == True )
        {
            SBr1->Panels->Items[0]->Text = "�Y���̃f�[�^��������܂���B�폜�ł��܂���ł����B";
            SBr1->Update();
            return(False);
        }
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����쐬
     sBuf = "DELETE from KSD91";
     sBuf +=" WHERE DTKSHIN='" + Tmp_KSD91.DTKSHIN + "'";      	// DTKSHIN
     sBuf +=" AND HINBAN='" + Tmp_KSD91.HINBAN + "'";      		// HINBAN
     sBuf +=" AND LOTNO='" + Tmp_KSD91.LOTNO + "'";      		// LOTNO


     Query1->SQL->Add(sBuf);

     // �₢�������̎��s
     try
     {
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     return(True);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�e�[�u��KSD91�̃��R�[�h�����������J�n���܂�
//
//  �@�\����
//    �e�[�u��KSD91�̃��R�[�h�����������J�n���܂�
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    1 = �����A0 = ���s
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

    if ( KSD91_Serch01() == 0)
    {
       return(0);
    }
    return(1);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�e�[�u��KSD91�̃��R�[�h���������܂�
//
//  �@�\����
//    �e�[�u��KSD91�̃��R�[�h���������܂�
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    1 = �����A0 = ���s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
int __fastcall TForm1::KSD91_Serch01(void)
{
	int iRow;
	AnsiString sBuf;
	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();
	Query3->Close();
	Query3->SQL->Clear();

	// �⍇�����s
	// �������@�@
	sBuf = "SELECT KSD91.DTKSHIN, KSD91.LOTNO, KSD91.MEMO, KSD91.UPDYMD, KSD91.UPDCHR,";
    sBuf += " KSD91.ADDYMD, KSD91.ADDTIM, KSD91.UPDTIM, KSD91.UPDCNT, SM12S.TANNAM, KSD91.HINBAN";
    sBuf += " FROM KSD91";
    sBuf += " LEFT JOIN SM12S ON KSD91.UPDCHR = SM12S.TANSYA";

	//sBuf += " WHERE KSD91.DTKSHIN LIKE '" + Form1->EdtHIN->Text + "%'";
	//sBuf += " AND   KSD91.LOTNO   LIKE '" + Form1->EdtLOT->Text + "%'";
	sBuf += " WHERE KSD91.DTKSHIN = '" + Form1->EdtHIN->Text + "'";
	sBuf += " AND   KSD91.LOTNO   LIKE '" + Form1->EdtLOT->Text + "%'";
	sBuf += " ORDER BY KSD91.DTKSHIN, KSD91.HINBAN, SUBSTR(KSD91.LOTNO,2)";

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
		SGr_List->Cells[0][iRow] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;    //No
		sBuf = iRow + 1;

		sBuf = Form1->Query1->FieldValues["DTKSHIN"];
		SGr_List->Cells[1][iRow] = sBuf;   //���Ӑ�i��

		sBuf = Form1->Query1->FieldValues["LOTNO"];
		SGr_List->Cells[2][iRow] = sBuf;   //���b�gNO

        if( VarIsNull(Form1->Query1->FieldValues["MEMO"]) ){
			sBuf = "";
		} else{
			sBuf = Form1->Query1->FieldValues["MEMO"];
		}
		SGr_List->Cells[3][iRow] =  sBuf;   //���l

        if( VarIsNull(Form1->Query1->FieldValues["UPDYMD"]) ){
			sBuf = "";
		} else{
			sBuf = Form1->Query1->FieldValues["UPDYMD"];
		}
        sBuf = sBuf.Insert("/",5);
        sBuf = sBuf.Insert("/",8);
        SGr_List->Cells[4][iRow] = sBuf;   //�ύX��

		sBuf = Form1->Query1->FieldValues["UPDCHR"];
		SGr_List->Cells[6][iRow] = sBuf;   //�X�V��(�S���҃R�[�h)

        if( VarIsNull(Form1->Query1->FieldValues["TANNAM"]) ){
			sBuf = "";
		} else{
			sBuf = Form1->Query1->FieldValues["TANNAM"];
		}
		SGr_List->Cells[5][iRow] = sBuf;   //�X�V��(�S���Җ�)

        if( VarIsNull(Form1->Query1->FieldValues["ADDYMD"]) ){
			sBuf = "";
		} else{
			sBuf = Form1->Query1->FieldValues["ADDYMD"];
		}
		SGr_List->Cells[7][iRow] = sBuf;   //�o�^��

        if( VarIsNull(Form1->Query1->FieldValues["ADDTIM"]) ){
			sBuf = "";
		} else{
			sBuf = Form1->Query1->FieldValues["ADDTIM"];
		}
		SGr_List->Cells[8][iRow] =  sBuf;   //�o�^����

        if( VarIsNull(Form1->Query1->FieldValues["UPDTIM"]) ){
			sBuf = "";
		} else{
			sBuf = Form1->Query1->FieldValues["UPDTIM"];
		}
		SGr_List->Cells[9][iRow] = sBuf;   //�X�V����

		sBuf = Form1->Query1->FieldValues["UPDCNT"];
		SGr_List->Cells[10][iRow] = sBuf;   //�X�V��

        if( VarIsNull(Form1->Query1->FieldValues["HINBAN"]) ){
			sBuf = "";
		} else{
			sBuf = Form1->Query1->FieldValues["HINBAN"];
		}
		SGr_List->Cells[11][iRow] = sBuf;   //���Еi��

		// �J�[�\�������ɃZ�b�g����
		Query1->Next();

		iRow += 1;
	}

    SGr_List->RowCount = iRow + 1;
    SGr_List->Cells[0][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[1][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[2][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[3][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[4][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[5][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[6][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[7][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[8][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[9][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[10][SGr_List->RowCount - 1 ] = "";
    SGr_List->Cells[11][SGr_List->RowCount - 1 ] = "";

	// �ŐV�̎��Еi��
	sBuf = "SELECT MAX(HINBAN) HINBAN FROM SD21S";
	sBuf += " WHERE DTKSHIN = '" + Form1->EdtHIN->Text + "'";

	Query3->SQL->Add(sBuf);
	Query3->Open();
	Query3->Active = true;

	if ( !Query3->Eof ) {
        if( VarIsNull(Form1->Query3->FieldValues["HINBAN"]) ){
			sBuf = "";
		} else{
			sBuf = Form1->Query3->FieldValues["HINBAN"];
		}
        Form1->EdtMAXBAN->Text = sBuf;   //���Еi��
	}

	return(1);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�e�[�u��KSD91�̃��R�[�h���`�F�b�N���܂�
//
//  �@�\����
//    �e�[�u��KSD91�Ɏw�肳�ꂽ���R�[�h�����݂��邩�ǂ����`�F�b�N���܂�
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    1 = �����A0 = ���s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
//  KSD91����Q�d�o�^�̊m�F
bool __fastcall TForm1::KSD91_Serch02(void)
{
	AnsiString sBuf;
	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	sBuf = "SELECT DTKSHIN,LOTNO FROM KSD91";
	sBuf += " WHERE DTKSHIN ='" + Form1->EdtSETHIN->Text + "'";
	sBuf += " AND   HINBAN  ='" + Form1->EdtSETBAN->Text + "'";
	sBuf += " AND   LOTNO   ='" + Form1->EdtSETLOT->Text + "'";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	if ( Query1->Eof == false ){
		return(false);
	}
    else {
        return(true);
    }
}





