//---------------------------------------------------------------------------
//
//  Unit3.cpp
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
#include "Unit3.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F���|�[�g�쐬�������J�n���܂��i�������ʎ��n��Ǘ��\�p�j
//
//  �@�\����
//    ����Ώۃf�[�^�̏����擾��ACreateReportSub5FOut�����s���܂��B
//
//  �p�����^����
//    int iAutoType		�F�o�͌`��
//                        0=����w��CSV�t�@�C���쐬��Excel�N���������Excel�I��
//                        1=����w��CSV�t�@�C���쐬��Excel�N��
//
//  �߂�l
//    bool				 �Ftrue  ��������
//        				 �Ffalse �������s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::CreateReportSub5(int iAutoType)
{
	int i;
	AnsiString sBuf;
	AnsiString sBufWLOTNO;
	AnsiString sBufDTKSHIN;
	AnsiString sBufLOTNO;
	AnsiString sBufSKTYMD;
    AnsiString sBufClb6_CHK_LOT;
    AnsiString sBufExcelFileName;
	int iFlagExcel;
    int iFlagKOTEI_PRN;

	sBufLOTNO  	    = "";
	sBufDTKSHIN     = "";
	sBufWLOTNO 	    = "";
	sBufSKTYMD 	    = "";
    iFlagExcel      = 0;

	//�t�@�C���I�[�v��
	if( (fCRSF_stream1 = fopen( sRepData5_1, "w+" )) == NULL ){
    	//ShowMessage("�P�ł����B");
		return(false);
	}
	if( (fCRSF_stream2 = fopen( sRepData5_2, "w+" )) == NULL ){
		fclose(fCRSF_stream1);
    	//ShowMessage("�Q�ł����B");
		return(false);
	}
	if( (fCRSF_stream3 = fopen( sRepData5_3, "w+" )) == NULL ){
		fclose(fCRSF_stream1);
		fclose(fCRSF_stream2);
    	//ShowMessage("�R�ł����B");
		return(false);
	}

	iCRSF_PageNo = 0;

    iRDiMax = 0;
    iRDjMax = 0;

	//--------------------------------------------------------------------------
	//�@�`�F�b�N���ꂽ���b�g������Ώۃf�[�^�擾
	//���Ӑ�i�ԁE���b�g�w��̏ꍇ
	//���Ӑ�i��
	sBufDTKSHIN = Edt5_WHR_DTKSHIN1->Text;
	sBufSKTYMD  = Edt_SEIKAN_YMD->Text;

	//���b�gNo
	for ( i = 0; i < Clb5_CHK_LOT->Items->Count; i++ ) {
		if ( Clb5_CHK_LOT->Checked[i] == true ){
			sBufLOTNO = Clb5_CHK_LOT->Items->Strings[i];
			sBufWLOTNO += ", '" + sBufLOTNO + "' ";
			iLOTNO_Length = sBufLOTNO.Length();

	        //Excel�̃t�@�C��������
	        if ( iFlagExcel == 0 ) {
	        	sBufExcelFileName = "�������ʎ��n��Ǘ��\" + sBufDTKSHIN + "_" + sBufLOTNO + ".xls";
	            iFlagExcel = 1;
	        }
		}
	}
	sBufWLOTNO = sBufWLOTNO.SubString(2,sBufWLOTNO.Length()-1);


	if ( Trim(sBufDTKSHIN) != "" && Trim(sBufWLOTNO) != "" ) {
	   CreateReportSub5FOut(sBufDTKSHIN,sBufWLOTNO,sBufSKTYMD);
	}


	//--------------------------------------------------------------------------

	Q_CRSub_KSD01->Close();
	Q_CRSub_KSD02->Close();
	Q_CRSub_KSD11->Close();
	Q_CRSub_KSD12->Close();


    //�^�C�g�����f�[�^�o��
    if ( Rdo5_KOTEI_PRN_ON->Checked == true ) {
    	iFlagKOTEI_PRN = 0;
    } else {
    	iFlagKOTEI_PRN = 1;
    }
	fprintf( fCRSF_stream1,"%d,%d,%d,%d,%s,%s,%s,%d,\n",
    		iCRSF_PageNo,iRDiMax,iRDjMax,iAutoType,sBufExcelFileName.c_str(),
            Edt5_CHK_CUSTOMER->Text.c_str(),Edt5_CHK_CUSTOMER2->Text.c_str(),iFlagKOTEI_PRN );

	// �t�@�C�������
	fclose(fCRSF_stream1);
	fclose(fCRSF_stream2);
	fclose(fCRSF_stream3);

    return(true);

}
//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�					�F���|�[�g�쐬�������J�n���܂��i�������ʎ��n��Ǘ��\�p�j
//
//  �@�\����
//    ����Ώۃf�[�^�擾��A����w���t�@�C��(CSV)���쐬���܂�
//
//  �p�����^����
//    AnsiString sBufDTKSHIN	�F���������i���Ӑ�i�ԁj
//    AnsiString sBufWLOTNO		�F���������i���b�gNo�j
//
//  �߂�l
//    bool				 �Ftrue  ��������
//        				 �Ffalse �������s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::CreateReportSub5FOut(AnsiString sBufDTKSHIN, AnsiString sBufWLOTNO, AnsiString sBufSKTYMD)
{

	AnsiString sBufSQL;
	AnsiString sBufWhere;
	AnsiString sBufOrder;
	AnsiString sBufWFix;
	AnsiString sBufWSKB_NO;
	AnsiString sBufWTOKU_FLG;

    int i;
    int iFlag;
	AnsiString sBuf;

    AnsiString sBufLOTNO;
    int        iLenLOTNO;
    int        iPosLOTNO;

	sBufWhere       = "";
    sBufWSKB_NO     = "";
    sBufWTOKU_FLG   = "";
	sBufOrder       = "";

	//SQL�����쐬
	//���P�FKSD02������ ����No=9(�X�y�[�X) �͏Ȃ�
	//���Q�FKSD02������ ����l�\��=0,1�̂ݎ擾

    //���ʂ̏������쐬
	sBufWFix = " SKB_NO <> 9 AND ( VALUE_TYPE = 0 OR VALUE_TYPE = 1 ) ";

    //2004.10.06 E.Takase �� �R�����g
    //����No�̏����s�v�i����́u�o�͓��e�̊m�F�v�̍ۂɂ̂݁A�K�v�j
	sBufWSKB_NO = "";
    sBufWTOKU_FLG = "";
	////����No
	//sBufWSKB_NO = "";
	//�f�ޑ��荀��
	//if ( Rdo5_WHR_SOZAI_ON->Checked ) {
	//    sBufWSKB_NO += " OR SKB_NO = 1 ";
	//}
	////�o�ב��荀��
	//if ( Rdo5_WHR_SYUKA_ON->Checked ) {
	//    sBufWSKB_NO += " OR SKB_NO = 2 ";
	//}
	////�ޗ��ؖ�����
	//if ( Rdo5_WHR_ZAIRYOU_ON->Checked ) {
	//    sBufWSKB_NO += " OR SKB_NO = 3 ";
	//}
	//sBufWSKB_NO = sBufWSKB_NO.SubString(4,sBufWSKB_NO.Length()-3);
    //if ( Trim(sBufWSKB_NO) != "" ) {
	//	sBufWSKB_NO = " ( " + sBufWSKB_NO + " ) ";
    //}
    //
	////���ʏo�͍���
	//if ( Rdo5_WHR_TOKUBETSU_ON->Checked ) {
	//    sBufWTOKU_FLG = "";
	//} else {
	//    sBufWTOKU_FLG = "AND TOKU_FLG = 0";
	//}
    ////2004.10.06 E.Takase �� �R�����g


	//KSD02
	sBufWhere =  " WHERE " + sBufWFix;
	sBufWhere += " AND DTKSHIN ='" + sBufDTKSHIN + "'";
	sBufWhere += " AND LOTNO IN (" + sBufWLOTNO + ")";
    sBufWhere += " AND SKTYMD >= '" + sBufSKTYMD + "'";      //onishi
    if ( Trim(sBufWSKB_NO) != "" ) {
		sBufWhere += " AND " + sBufWSKB_NO;
    }
	sBufWhere += sBufWTOKU_FLG;
	//sBufWhere += " AND DISP_VAL_SU > 0 ";
	if( iLOTNO_Length == 5 ){
		sBufOrder = " ORDER BY DTKSHIN,SUBSTR(LOTNO,2),ORDER_NO";
	} else {
		sBufOrder = " ORDER BY DTKSHIN,LOTNO,ORDER_NO";
	}

	//KSD02
	sBufSQL = "SELECT * FROM KSD02";
	sBufSQL += sBufWhere;
	sBufSQL += sBufOrder;

	Q_CRSub_KSD02->Close();
	Q_CRSub_KSD02->SQL->Clear();
	Q_CRSub_KSD02->SQL->Add(sBufSQL);
	Q_CRSub_KSD02->Open();
	Q_CRSub_KSD02->Active = true;
    if ( Q_CRSub_KSD02->Eof == true ) {
        return(false);
    }

	//KSD01
	sBufWhere =  " WHERE ";
	sBufWhere += " DTKSHIN ='" + sBufDTKSHIN + "'";
	sBufWhere += " AND LOTNO IN (" + sBufWLOTNO + ")";
    sBufWhere += " AND SKTYMD >= '" + sBufSKTYMD + "'";      //onishi
	if( iLOTNO_Length == 5 ){
		sBufOrder = " ORDER BY DTKSHIN,SUBSTR(LOTNO,2)";
	} else {
		sBufOrder = " ORDER BY DTKSHIN,LOTNO";
	}

	//KSD01
	sBufSQL = "SELECT * FROM KSD01";
	sBufSQL += sBufWhere;
	sBufSQL += sBufOrder;

	Q_CRSub_KSD01->Close();
	Q_CRSub_KSD01->SQL->Clear();
	Q_CRSub_KSD01->SQL->Add(sBufSQL);
	Q_CRSub_KSD01->Open();
	Q_CRSub_KSD01->Active = true;
    if ( Q_CRSub_KSD01->Eof == true ) {
        return(false);
    }

 	//�f�[�^������
	iCRSF_KSD01_MAX = 18;
	iCRSF_KSD01_Num = 0;
	iCRSF_KSD01_Pos = 0;
	iCRSF_KSD02_MAX = GetCRSF_KSD02_NUM();
	CRSF_KSD02 = new  struct TCRSF_KSD02[iCRSF_KSD02_MAX];
	CRSF_KSD12 = new  struct TCRSF_KSD02[iCRSF_KSD02_MAX];
	iCRSF_KSD02_Num = 0;
	iCRSF_KSD02_Pos = 0;
	iCRSF_KSD12_Num = 0;
	iCRSF_KSD12_Pos = 0;


	//�f�[�^�̏o�́��Z�b�g
	Q_CRSub_KSD01->First();
	Q_CRSub_KSD02->First();

	strcpy(sCRSF_DTKSHIN , Null_S(Q_CRSub_KSD01->FieldValues["DTKSHIN"]).c_str());	//�@���Ӑ�i��
	strcpy(sCRSF_ZISNAM  , Null_S(Q_CRSub_KSD01->FieldValues["ZISNAM"]).c_str());	//�A�ގ����́i�i��j
	strcpy(sCRSF_HINMEI  , Null_S(Q_CRSub_KSD01->FieldValues["HINMEI"]).c_str());	//�B�i��


	while(Q_CRSub_KSD02->Eof == false) {
        //�o�͑Ώۂ̑��荀�ڂ��ǂ����𔻒f
        sBuf = "";
        if( !VarIsNull(Q_CRSub_KSD02->FieldValues["KOMK_NM"]) ){
        	sBuf = Q_CRSub_KSD02->FieldValues["KOMK_NM"];
        }
        if( !VarIsNull(Q_CRSub_KSD02->FieldValues["KOMK_SUB"]) ){
        	sBuf = sBuf + " " + Q_CRSub_KSD02->FieldValues["KOMK_SUB"];
        }
        // 2003/10/21 A.Tamura [�P��]���܂߂đI�������ɓ����B
        if( !VarIsNull(Q_CRSub_KSD02->FieldValues["TANI"]) ){
        	sBuf = sBuf + " " + Q_CRSub_KSD02->FieldValues["TANI"];
        }
        iFlag = 0;
        for ( i = 0; i < Clb5_CHK_KOUMOKU->Items->Count; i++ ) {
        	if ( Clb5_CHK_KOUMOKU->Items->Strings[i] == sBuf ) {
                if ( Clb5_CHK_KOUMOKU->Checked[i] == true ) {
            		iFlag = 1;
                }
            }
        }
        if ( iFlag == 1 ) {
			//���b�g�̕`��ʒu�擾(���̎�1�y�[�W�ɓ��郍�b�g���𒴂�������y�[�W���܂�)
			iCRSF_KSD01_Pos = GetiCRSF_KSD01_Pos5(Null_S(Q_CRSub_KSD02->FieldValues["LOTNO"]));

			//���荀�ڂ̕`��ʒu�擾
            //2003.06.10 E.Takase
			//iCRSF_KSD02_Pos = GetiCRSF_KSD02_Pos(Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NM"]),
			//							 		 Null_S(Q_CRSub_KSD02->FieldValues["KOMK_SUB"]));
            //2003.10.22 E.Takase
			//iCRSF_KSD02_Pos = GetiCRSF_KSD02_Pos(Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NM"]),
			//							 		 Null_S(Q_CRSub_KSD02->FieldValues["KOMK_SUB"]),
			//							 		 Null_S(Q_CRSub_KSD02->FieldValues["HINBAN_SK"]),
			//							 		 atoi(Null_S(Q_CRSub_KSD02->FieldValues["KIKI_NO"]).c_str()),
			//							 		 atoi(Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NO"]).c_str()) );
			iCRSF_KSD02_Pos = GetiCRSF_KSD02_Pos(Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NM"]),
										 		 Null_S(Q_CRSub_KSD02->FieldValues["KOMK_SUB"]),
										 		 Null_S(Q_CRSub_KSD02->FieldValues["HINBAN_SK"]),
										 		 atoi(Null_S(Q_CRSub_KSD02->FieldValues["KIKI_NO"]).c_str()),
										 		 atoi(Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NO"]).c_str()),
										 		 Null_S(Q_CRSub_KSD02->FieldValues["TANI"]) );

			//�f�[�^�ڍו�(sRepData5_3)�Ƀf�[�^�o��
			WriteCRSF_sRepData5_3();

        }
		Q_CRSub_KSD02->Next();
	}

	//�y�[�WNo���o��
    iCRSF_PageNo++;
    //2003/08/27 E.Takase
    //���b�gNO�̌��� ��ʂŎw��i���n��j
    sBufLOTNO = CRSF_KSD01[0].LOTNO;
    if ( iLOTNO_OUT_Length < 6 ) {
     	// �E���� iLOTNO_OUT_Length �����p
        iLenLOTNO = sBufLOTNO.Length();
        iPosLOTNO = iLenLOTNO - iLOTNO_OUT_Length;
        if( iPosLOTNO > 0 ){
           	sBufLOTNO = sBufLOTNO.SubString( iPosLOTNO + 1, iLOTNO_OUT_Length );
      	}
    }
	fprintf( fCRSF_stream2,"*,0,PAGENO,");
    //fprintf( fCRSF_stream2,"%d,%s,%s,%s,\n",iCRSF_PageNo+1,sCRSF_DTKSHIN,sCRSF_ZISNAM,sCRSF_HINMEI);
	//fprintf( fCRSF_stream2,"%d,%s,%s,%s,%s,\n",
    //		iCRSF_PageNo,sCRSF_DTKSHIN,sCRSF_ZISNAM,sCRSF_HINMEI,CRSF_KSD01[0].LOTNO);
	fprintf( fCRSF_stream2,"%d,%s,%s,%s,%s,\n",
    		iCRSF_PageNo,sCRSF_DTKSHIN,sCRSF_ZISNAM,sCRSF_HINMEI,sBufLOTNO.c_str());
	//���b�g�f�[�^���o��
	WriteCRSF_KSD01();
	//���荀�ڃf�[�^���o��
	WriteCRSF_KSD02();

    //���b�g�f�[�^��������
	memset( CRSF_KSD01, (int)NULL, sizeof(struct TCRSF_KSD01)*iCRSF_KSD01_MAX );
	iCRSF_KSD01_Num = 0;

	//���荀�ڃf�[�^��������
	memset( CRSF_KSD02, (int)NULL, sizeof(struct TCRSF_KSD02)*iCRSF_KSD02_MAX );
	iCRSF_KSD02_Num = 0;

    return(true);

}
//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�					�F���b�g�̕`��ʒu�擾���܂�
//
//  �@�\����
//	  �\����CRSF_KSD01�Ɏw�肳�ꂽ���b�g�̏��������܂��B
//    �A���A1�y�[�W�ɓ��郍�b�g���Ɣ�r���A�����Ă�������y�[�W�������܂��B
//    ���y�[�W�������s������A�\����CRSF_KSD01�����������܂��B
//    CreateReportSub5FOut�Ŏg�p����܂�
//
//  �p�����^����
//    AnsiString sSrchLOTNO		�F���������i���b�gNo�j
//
//  �߂�l
//    int						�F���b�g�̕`��ʒu
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
int  __fastcall TForm1::GetiCRSF_KSD01_Pos5(AnsiString sSrchLOTNO)
{
	int i;
	int iPos;
	AnsiString sBuf;
	AnsiString sBufSKTYMD;
	AnsiString sBufDTKSHIN;
	AnsiString sBufLOTNO;
	AnsiString sBufSQL;

    AnsiString sBufLOTNO2;
    int        iLenLOTNO;
    int        iPosLOTNO;

	iPos = -1;
	for ( i = 0; i < iCRSF_KSD01_Num; i++ ) {
		if ( AnsiString(CRSF_KSD01[i].LOTNO) == sSrchLOTNO ) {
			iPos = i;
		}
	}
	if ( iPos == -1 ) {
		//1�y�[�W�ɓ��郍�b�g���Ɣ�r���A�����Ă�������y�[�W����
		//�f�[�^�^�C�g����(sRepData6_2)
		if ( iCRSF_KSD01_Num+1 > iCRSF_KSD01_MAX ) {
        	//2003/08/27 E.Takase
        	//���b�gNO�̌��� ��ʂŎw��i���n��j
        	sBufLOTNO2 = CRSF_KSD01[0].LOTNO;
        	if ( iLOTNO_OUT_Length < 6 ) {
        		// �E���� iLOTNO_OUT_Length �����p
	        	iLenLOTNO = sBufLOTNO2.Length();
            	iPosLOTNO = iLenLOTNO - iLOTNO_OUT_Length;
            	if( iPosLOTNO > 0 ){
            		sBufLOTNO2 = sBufLOTNO2.SubString( iPosLOTNO + 1, iLOTNO_OUT_Length );
        		}
        	}
			//�y�[�WNo���o��
	        fprintf( fCRSF_stream2,"*,0,PAGENO,");
	        //fprintf( fCRSF_stream2,"%d,%s,%s,%s,\n",iCRSF_PageNo+1,sCRSF_DTKSHIN,sCRSF_ZISNAM,sCRSF_HINMEI);
		 	//fprintf( fCRSF_stream2,"%d,%s,%s,%s,%s,\n",
    		//				iCRSF_PageNo+1,sCRSF_DTKSHIN,sCRSF_ZISNAM,sCRSF_HINMEI,CRSF_KSD01[0].LOTNO);
		 	fprintf( fCRSF_stream2,"%d,%s,%s,%s,%s,\n",
    						iCRSF_PageNo+1,sCRSF_DTKSHIN,sCRSF_ZISNAM,sCRSF_HINMEI,sBufLOTNO2.c_str());
			//fprintf( fCRSF_stream2,"*,0,PAGENO,");
			//fprintf( fCRSF_stream2,"%d,\n",iCRSF_PageNo+1);

			//���b�g�f�[�^���o��
			WriteCRSF_KSD01();
			//���荀�ڃf�[�^���o��
			WriteCRSF_KSD02();


			//���b�g�f�[�^��������
			memset( CRSF_KSD01, (int)NULL, sizeof(struct TCRSF_KSD01)*iCRSF_KSD01_MAX );
			iPos = 0;
			iCRSF_KSD01_Num = 0;

			//���荀�ڃf�[�^��������
			memset( CRSF_KSD02, (int)NULL, sizeof(struct TCRSF_KSD02)*iCRSF_KSD02_MAX );
			iCRSF_KSD02_Num = 0;

			iCRSF_PageNo++;
		}
		//iPos�ʒu�Ƀ��b�g�f�[�^���Z�b�g
		iPos = iCRSF_KSD01_Num;
		//Q_CRSub_KSD01����Z�b�g����f�[�^������
		Q_CRSub_KSD01->First();
		while(Q_CRSub_KSD01->Eof == false) {
			sBuf = Null_S(Q_CRSub_KSD01->FieldValues["LOTNO"]);
			if (sSrchLOTNO == sBuf) {

				strcpy(CRSF_KSD01[iPos].LOTNO			 , Null_S(Q_CRSub_KSD01->FieldValues["LOTNO"]).c_str());
				strcpy(CRSF_KSD01[iPos].SOZAI_OK_PRT	 , Null_S(Q_CRSub_KSD01->FieldValues["SOZAI_OK_PRT"]).c_str());
				strcpy(CRSF_KSD01[iPos].SYUKA_OK_PRT	 , Null_S(Q_CRSub_KSD01->FieldValues["SYUKA_OK_PRT"]).c_str());
				strcpy(CRSF_KSD01[iPos].UPDCHR		  	 , GetTANNAM(Null_S(Q_CRSub_KSD01->FieldValues["UPDCHR"])).c_str());
				strcpy(CRSF_KSD01[iPos].MEMO			 , Null_S(Q_CRSub_KSD01->FieldValues["MEMO"]).c_str());

				//������̏����ݒ�(yyyymmdd��yyyy/mm/dd)
				//�����,
			    //2003.08.23 E.Takase Add ��
			    //SD21S�̏o�ד����擾���ďo��
				sBufDTKSHIN = Null_S(Q_CRSub_KSD01->FieldValues["DTKSHIN"]);
				sBufLOTNO = Null_S(Q_CRSub_KSD01->FieldValues["LOTNO"]);

                /*
			 	sBufSQL  = "select DTKSHIN, LOTBNG, ESYUYMD from SD21S ";
				sBufSQL += "where ESYUYMD != '00000000' ";
				sBufSQL += "and DTKSHIN = '" + sBufDTKSHIN + "' ";
				sBufSQL += "and LOTBNG = '"  + sBufLOTNO + "' ";
                */
				// 2004/09/24 A.Tamura �o�ד��͍ŏ��̓�(��ԌÂ����t)�Ƃ���B
/* 2005/09/26 Y.Sano ���ؗp�e�X�g
				sBufSQL  = "select TSUYMD";
				sBufSQL += " FROM SD15S RIGHT JOIN SD16S ON SD15S.JSKBNG = SD16S.JSKBNG";
				sBufSQL += " where SD16S.TKSHIN = '" + sBufDTKSHIN + "'";
				sBufSQL += " and SD16S.LOTBNG = '" + sBufLOTNO + "' ";
				sBufSQL += " order by SD15S.TSUYMD";
*/
/* 2005/09/26 Y.Sano ���ؗp�e�X�g*/
                sBufSQL = "SELECT TSUYMD_MIN from SD15S_16S";
			    sBufSQL += " WHERE TKSHIN='" + sBufDTKSHIN + "'";
                sBufSQL += " AND LOTBNG='" + sBufLOTNO + "'";
                sBufSQL += " AND TSUYMD_MIN >= '" + Edt_SEIKAN_YMD->Text + "'";      //onishi
                sBufSQL += " ORDER BY TSUYMD_MIN";

				Q_CRSub_SD21S->Close();
				Q_CRSub_SD21S->SQL->Clear();
				Q_CRSub_SD21S->SQL->Add(sBufSQL);
				Q_CRSub_SD21S->Open();
				Q_CRSub_SD21S->Active = true;
			    if ( Q_CRSub_SD21S->Eof == true ) {
			        sBuf = "";
			    } else {
					// sBuf = Null_S(Q_CRSub_SD21S->FieldValues["ESYUYMD"]);
					// 2004/09/24 A.Tamura �o�ד��͍ŏ��̓�(��ԌÂ����t)�Ƃ���B
/* 2005/09/26 Y.Sano ���ؗp�e�X�g
					sBuf = Null_S(Q_CRSub_SD21S->FieldValues["TSUYMD"]);
*/
/* 2005/09/26 Y.Sano ���ؗp�e�X�g*/
					sBuf = Null_S(Q_CRSub_SD21S->FieldValues["TSUYMD_MIN"]);

			    	if ( Trim(sBuf) != "" ) {
				    	sBuf.Insert("/",7);
			    		sBuf.Insert("/",5);
			    	}
			    }
			    sBufSKTYMD = sBuf;

			    //2003.05.26 E.Takase Add ��
			    //2003.05.26 E.Takase �R�����g ��

				////CRSF_KSD01[iPos].SKTYMD		 	 = Null_S(Q_CRSub_KSD01->FieldValues["SKTYMD"]);
                //sBufSKTYMD = Null_S(Q_CRSub_KSD01->FieldValues["SKTYMD"]);
                //if ( Trim(sBufSKTYMD) != "" ) {
				//    sBufSKTYMD.Insert("/",7);
				//    sBufSKTYMD.Insert("/",5);
                //}
                //
			    //2003.05.26 E.Takase �R�����g ��
                strcpy(CRSF_KSD01[iPos].SKTYMD , sBufSKTYMD.c_str());




                //2003.05.10 E.Takase Add ��
				//CRSF_KSD01[iPos].SKTYMD_SZ		 = Null_S(Q_CRSub_KSD01->FieldValues["SKTYMD_SZ_PRT"]);
				//�f�ޑ�����̏����ݒ�(yyyymmdd��yyyy/mm/dd)
                sBufSKTYMD = Null_S(Q_CRSub_KSD01->FieldValues["SKTYMD_SZ_PRT"]);
                if ( Trim(sBufSKTYMD) != "" ) {
				    sBufSKTYMD.Insert("/",7);
				    sBufSKTYMD.Insert("/",5);
                }
                strcpy(CRSF_KSD01[iPos].SKTYMD_SZ , sBufSKTYMD.c_str());
                //2003.05.10 E.Takase Add ��
				break;
			}
			Q_CRSub_KSD01->Next();
		}
		iCRSF_KSD01_Num++;
	}

	return ( iPos );

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�					�F�f�[�^�ڍו�(sRepData5_3)�Ƀf�[�^�o�͂��܂�
//
//  �@�\����
//	  Q_CRSub_KSD02�̃J�����g���R�[�h�̃f�[�^���o�͂��܂��B
//    CreateReportSub5FOut�Ŏg�p����܂��B
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
void __fastcall TForm1::WriteCRSF_sRepData5_3(void)
{

	int iBuf;
	AnsiString sBuf;
	AnsiString sBufSQL;
	AnsiString sBufSOKUVAL[10];
	AnsiString sBufDTKSHIN;
	AnsiString sBufLOTNO;

    //2003/08/30 E.Takase
	AnsiString sBufSOKU_FLG;
	AnsiString sReSOKU_SU;
	AnsiString sReKIKA_PRT;
	AnsiString sReVALUE_TYPE;
	AnsiString sReVALUE_DECI;
	AnsiString sReDISP_VAL_SU;
	AnsiString sReDISP_VAL_AVE;
	AnsiString sReDISP_VAL_MAX;
	AnsiString sReDISP_VAL_MIN;
	AnsiString sReDISP_OK;
	TStrings *sReDISP_VAL;
	sReDISP_VAL	= new TStringList;

	//�y�[�W�ԍ�,�f�[�^��ʁi�����ł�0�j�C���b�g�ʒu�C���荀�ڈʒu,�������i��������Ȃ��̂�-1�j
	fprintf( fCRSF_stream3,"%d,0,%d,%d,-1,",iCRSF_PageNo,iCRSF_KSD01_Pos,iCRSF_KSD02_Pos);

	//�����,
	sBuf = Null_S(Q_CRSub_KSD02->FieldValues["SKTYMD"]);
    if ( Trim(sBuf) != "" ) {
	    sBuf.Insert("/",7);
    	sBuf.Insert("/",5);
    }

	fprintf( fCRSF_stream3,"%s,",sBuf.c_str());



    //2003/09/01 E.Takase
    //�u���肵�Ȃ�(SOKU_FLG = 0)�v�Ɛݒ肳��Ă��郍�b�g�͈ȑO�̃��b�g�̑���l���R�s�[����
    sBufSOKU_FLG = Null_S(Q_CRSub_KSD02->FieldValues["SOKU_FLG"]);
    if ( sBufSOKU_FLG == "0" ) {
    	//�u���肵�Ȃ�(SOKU_FLG = 0)�v
        //2003/10/22 E.Takase ���������ɒP�ʒǉ�
		//iBuf = GetBeforeLotVal(Null_S(Q_CRSub_KSD02->FieldValues["DTKSHIN"]),
        //        			   Null_S(Q_CRSub_KSD02->FieldValues["LOTNO"]),
        //        			   Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NM"]),
		//					   Null_S(Q_CRSub_KSD02->FieldValues["KOMK_SUB"]),
		//					   Null_S(Q_CRSub_KSD02->FieldValues["HINBAN_SK"]),
		//					   atoi(Null_S(Q_CRSub_KSD02->FieldValues["KIKI_NO"]).c_str()),
		//					   atoi(Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NO"]).c_str()),
        //                       &sReSOKU_SU, &sReKIKA_PRT, &sReVALUE_TYPE,
        //                       &sReVALUE_DECI, &sReDISP_VAL_SU, &sReDISP_VAL_AVE,
        //                       &sReDISP_VAL_MAX, &sReDISP_VAL_MIN, &sReDISP_OK, sReDISP_VAL );
		iBuf = GetBeforeLotVal(Null_S(Q_CRSub_KSD02->FieldValues["DTKSHIN"]),
                			   Null_S(Q_CRSub_KSD02->FieldValues["LOTNO"]),
                			   Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NM"]),
							   Null_S(Q_CRSub_KSD02->FieldValues["KOMK_SUB"]),
							   Null_S(Q_CRSub_KSD02->FieldValues["HINBAN_SK"]),
							   atoi(Null_S(Q_CRSub_KSD02->FieldValues["KIKI_NO"]).c_str()),
							   atoi(Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NO"]).c_str()),
							   Null_S(Q_CRSub_KSD02->FieldValues["TANI"]),
                               &sReSOKU_SU, &sReKIKA_PRT, &sReVALUE_TYPE,
                               &sReVALUE_DECI, &sReDISP_VAL_SU, &sReDISP_VAL_AVE,
                               &sReDISP_VAL_MAX, &sReDISP_VAL_MIN, &sReDISP_OK, sReDISP_VAL );
        if ( iBuf != -1 ) {
			//����l�\��,����l�����_�ȉ�����,
			fprintf( fCRSF_stream3,"%d,", atoi(sReVALUE_TYPE.c_str()));
			fprintf( fCRSF_stream3,"%d,",atoi(sReVALUE_DECI.c_str()));
			//���萔 ,
			fprintf( fCRSF_stream3,"%d,",atoi(sReDISP_VAL_SU.c_str()));

		    //����l�̍ŏ��E�ő�E����
			fprintf( fCRSF_stream3, "%s,", sReDISP_VAL_MIN.c_str());
			fprintf( fCRSF_stream3, "%s,", sReDISP_VAL_MAX.c_str());
			fprintf( fCRSF_stream3, "%s,", sReDISP_VAL_AVE.c_str());
        } else {
			//����l�\��,����l�����_�ȉ�����,
			fprintf( fCRSF_stream3,"0,");
			fprintf( fCRSF_stream3,"0,");
			//���萔 ,
			fprintf( fCRSF_stream3,"0,");

		    //����l�̍ŏ��E�ő�E����
			fprintf( fCRSF_stream3, " ,");
			fprintf( fCRSF_stream3, " ,");
			fprintf( fCRSF_stream3, " ,");
        } 

    } else {
    	//�u���肷��(SOKU_FLG = 1)�v
		//����l�\��,����l�����_�ȉ�����,
		iBuf = atoi(Null_S(Q_CRSub_KSD02->FieldValues["VALUE_TYPE"]).c_str());
		fprintf( fCRSF_stream3,"%d,",iBuf);
		iBuf = atoi(Null_S(Q_CRSub_KSD02->FieldValues["VALUE_DECI"]).c_str());
		fprintf( fCRSF_stream3,"%d,",iBuf);

		//���萔 ,
		iBuf = atoi(Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL_SU"]).c_str());
		////���萔�i�ő�E�ŏ��E���ςȂ̂łR�Œ�j,
		//iBuf = 3;
		fprintf( fCRSF_stream3,"%d,",iBuf);

	    //����l�̍ŏ��E�ő�E����
		fprintf( fCRSF_stream3, "%s,",
						Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL_MIN"]).c_str());
		fprintf( fCRSF_stream3, "%s,",
						Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL_MAX"]).c_str());
		fprintf( fCRSF_stream3, "%s,",
						Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL_AVE"]).c_str());
	}


	fprintf( fCRSF_stream3,"\n");
    iRDiMax++;

	iBuf = 2; //���萔�i�ő�E�ŏ��Ȃ̂łQ�Œ�j
    if ( iRDjMax < iBuf ) {
        iRDjMax = iBuf;
    }

}
//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�					�F������u������
//
//  �@�\����
//	  ������sMaster�Ɋ܂܂��sA����������sB�ɒu�������܂��B
//    WriteCRSF_KSD01�Ŏg�p����܂��B
//
//  �p�����^����
//    AnsiString sMaster		�F�u�������Ώە�����
//    AnsiString sA				�F����������
//    AnsiString sB				�F�u��������
//
//  �߂�l
//    AnsiString				�F�u��������̕�����
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::StrConvAtoB(AnsiString sMaster, AnsiString sA, AnsiString sB)
{
	int iLength;
    AnsiString sBuf;
    int iPos;

    sBuf = sMaster;
    iLength = sMaster.Length();

    if ( iLength <= 0 ) {
    	return ( sBuf );
    }

    while ( 1 ) {

    	iPos = sBuf.AnsiPos(sA);
        if ( iPos <= 0 ) {
        	break;
        }

        sBuf.Delete(iPos, sA.Length());
        sBuf.Insert(sB, iPos);


    }



    return ( sBuf );
}

