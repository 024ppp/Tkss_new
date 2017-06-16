//---------------------------------------------------------------------------
//
//  Unit4.cpp
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
#include "Unit4.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F���|�[�g�쐬�������J�n���܂��i�����o��[�p�j
//
//  �@�\����
//    ����Ώۃf�[�^�̏����擾��ACreateReportSub6FOut�����s���܂��B
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
bool __fastcall TForm1::CreateReportSub6(int iAutoType)
{
	int i;
	int iFlag;
	int iFlag2;
	AnsiString sBuf;
	AnsiString sBufWLOTNO;
	AnsiString sBufDTKSHIN;
	AnsiString sBufLOTNO;
	AnsiString sBufSKTYMD;
    AnsiString sBufClb6_CHK_LOT;
    AnsiString sBufExcelFileName;
	int iFlagExcel;

	sBufLOTNO  	    = "";
	sBufDTKSHIN     = "";
	sBufWLOTNO 	    = "";
	sBufSKTYMD 	    = "";
    iFlagExcel      = 0;

	//�t�@�C���I�[�v��
	if( (fCRSF_stream1 = fopen( sRepData6_1, "w+" )) == NULL ){
		return(false);
	}
	if( (fCRSF_stream2 = fopen( sRepData6_2, "w+" )) == NULL ){
		fclose(fCRSF_stream1);
		return(false);
	}
	if( (fCRSF_stream3 = fopen( sRepData6_3, "w+" )) == NULL ){
		fclose(fCRSF_stream1);
		fclose(fCRSF_stream2);
		return(false);
	}

	iCRSF_PageNo = 0;

    iRDiMax = 0;
    iRDjMax = 0;

    sBufSKTYMD  = Edt_SEIKAN_YMD->Text;

	//--------------------------------------------------------------------------
	//�@�`�F�b�N���ꂽ���b�g������Ώۃf�[�^�擾
	//���Ӑ�i�ԁE���b�g�w��̏ꍇ
	if ( Rdo6_WHR_TYPE1->Checked == true ){
        //���Ӑ�i��
		sBufDTKSHIN = Edt6_WHR_DTKSHIN1->Text;

        //���b�gNo
		for ( i = 0; i < Clb6_CHK_LOT->Items->Count; i++ ) {
			if ( Clb6_CHK_LOT->Checked[i] == true ){
				sBufLOTNO = Clb6_CHK_LOT->Items->Strings[i];
				sBufWLOTNO += ", '" + sBufLOTNO + "' ";
				iLOTNO_Length = sBufLOTNO.Length();

                //Excel�̃t�@�C��������
                if ( iFlagExcel == 0 ) {
                	sBufExcelFileName = "�����o��[" + sBufDTKSHIN + "_" + sBufLOTNO + ".xls";
                    iFlagExcel = 1;
                }
			}
		}
		sBufWLOTNO = sBufWLOTNO.SubString(2,sBufWLOTNO.Length()-1);


        if ( Trim(sBufDTKSHIN) != "" && Trim(sBufWLOTNO) != "" ) {
		   CreateReportSub6FOut(sBufDTKSHIN,sBufWLOTNO,sBufSKTYMD);
        }

	} else {
	//�������w��̏ꍇ
        iFlag = 0;
        iFlag2 = 0;
        //���Ӑ�i�Ԃƃ��b�gNo��1�s�ŃZ�b�g���Ă���̂ŕ�������
		for ( i = 0; i < Clb6_CHK_LOT->Items->Count; i++ ) {
			if ( Clb6_CHK_LOT->Checked[i] == true ){
				sBufClb6_CHK_LOT = Clb6_CHK_LOT->Items->Strings[i];
                sBuf = Trim(sBufClb6_CHK_LOT.SubString(1,20));

                if ( iFlag == 1 && sBuf != sBufDTKSHIN ) {
                    sBufWLOTNO = sBufWLOTNO.SubString(2,sBufWLOTNO.Length()-1);
                    if ( Trim(sBufDTKSHIN) != "" && Trim(sBufWLOTNO) != "" ) {
		               CreateReportSub6FOut(sBufDTKSHIN,sBufWLOTNO,sBufSKTYMD);
                    }
					sBufWLOTNO = "";
                    iFlag2 = 0;
                }
                sBufDTKSHIN = sBuf;
                sBufLOTNO = Trim(sBufClb6_CHK_LOT.SubString(21,sBufClb6_CHK_LOT.Length()-20));

				sBufWLOTNO += ", '" + sBufLOTNO + "' ";
				iLOTNO_Length = sBufLOTNO.Length();
                iFlag = 1;
                iFlag2 = 1;
                //Excel�̃t�@�C��������
                if ( iFlagExcel == 0 ) {
                	sBufExcelFileName = "�����o��[" + sBufDTKSHIN + "_" + sBufLOTNO + ".xls";
                    iFlagExcel = 1;
                }

			}
		}
        if ( iFlag2 == 1 ) {
            sBufWLOTNO = sBufWLOTNO.SubString(2,sBufWLOTNO.Length()-1);
            if ( Trim(sBufDTKSHIN) != "" && Trim(sBufWLOTNO) != "" ) {
		       CreateReportSub6FOut(sBufDTKSHIN,sBufWLOTNO,sBufSKTYMD);
            }
            sBufWLOTNO = "";
            iFlag2 = 0;

        }


    }

	//--------------------------------------------------------------------------

    //�^�C�g�����f�[�^�o��
	fprintf( fCRSF_stream1,"%d,%d,%d,%d,%s,\n",iCRSF_PageNo,iRDiMax,iRDjMax,iAutoType,sBufExcelFileName.c_str());

	// �t�@�C�������
	fclose(fCRSF_stream1);
	fclose(fCRSF_stream2);
	fclose(fCRSF_stream3);

	Q_CRSub_KSD01->Close();
	Q_CRSub_KSD02->Close();
	Q_CRSub_KSD11->Close();
	Q_CRSub_KSD12->Close();

    return(true);


}
//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�					�F���|�[�g�쐬�������J�n���܂��i�����o��[�p�j
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
bool __fastcall TForm1::CreateReportSub6FOut(AnsiString sBufDTKSHIN, AnsiString sBufWLOTNO, AnsiString sBufSKTYMD)
{

	int i;

	AnsiString sBufSQL;
	AnsiString sBufWhere;
	AnsiString sBufOrder;
	AnsiString sBufWFix;
	AnsiString sBufWSKB_NO;
	AnsiString sBufWTOKU_FLG;
    int 	   iBufSKB_NO;
    int 	   iBufUPDCHRCD;

	AnsiString sBuf;

	int iFlag;

	sBufWhere       = "";
    sBufWSKB_NO     = "";
    sBufWTOKU_FLG   = "";
	sBufOrder       = "";

	//SQL�����쐬
	//���P�FKSD02������ ����No=9(�X�y�[�X) �͏Ȃ�
	//���Q�F���荀�ړo�^No=1�̃f�[�^�͍��ځu�O�ρv�֕`�悷��

    //���ʂ̏������쐬
	sBufWFix = " SKB_NO <> 9 ";

    //2004.10.06 E.Takase �� �R�����g
    //����No�̏����s�v�i����́u�o�͓��e�̊m�F�v�̍ۂɂ̂݁A�K�v�j
	sBufWSKB_NO = "";
    sBufWTOKU_FLG = "";
	////����No
	//sBufWSKB_NO = "";
    ////2003.08.05 E.Takase
    ////�o�͑Ώۂ̑��荀�ڂ��ǂ����𔻒f
    ////�������w��̏�̂ݏ������w��
	//if ( Rdo6_WHR_TYPE1->Checked == true ){
	////���Ӑ�i�ԁE���b�g�w��̏ꍇ
    //    sBufWSKB_NO = "";
    //} else {
    ////�������w��̏ꍇ
	//	//�f�ޑ��荀��
	//	if ( Rdo6_WHR_SOZAI_ON->Checked ) {
	//	    sBufWSKB_NO += " OR SKB_NO = 1 ";
	//	}
	//	//�o�ב��荀��
	//	if ( Rdo6_WHR_SYUKA_ON->Checked ) {
	//	    sBufWSKB_NO += " OR SKB_NO = 2 ";
	//	}
	//	//�ޗ��ؖ�����
	//	if ( Rdo6_WHR_ZAIRYOU_ON->Checked ) {
	//	    sBufWSKB_NO += " OR SKB_NO = 3 ";
	//	}
	//	sBufWSKB_NO = sBufWSKB_NO.SubString(4,sBufWSKB_NO.Length()-3);
	//    if ( Trim(sBufWSKB_NO) != "" ) {
	//		sBufWSKB_NO = " ( " + sBufWSKB_NO + " ) ";
	//    }
    //
	//	//���ʏo�͍���
	//	if ( Rdo6_WHR_TOKUBETSU_ON->Checked ) {
	//	    sBufWTOKU_FLG = "";
	//	} else {
	//	    sBufWTOKU_FLG = "AND TOKU_FLG = 0";
	//	}
    //}
    //2004.10.06 E.Takase �� �R�����g

	//��������������������������������������������������������������
    //KSD02 ���� KSD02W����f�[�^���擾
    //�������� �쐬
	sBufWhere =  " WHERE " + sBufWFix;
    //2003/08/29 E.Takase
    //�w�肳�ꂽ�����ɂ��A�f�[�^�擾�̃e�[�u�����f
	//���Ӑ�i�ԁE���b�g�w��̏ꍇ KSD02W����f�[�^�擾����
	//�������w��̏ꍇ             KSD02 ����f�[�^�擾����
	if ( Rdo6_WHR_TYPE1->Checked == true ){ //���Ӑ�i�ԁE���b�g�w��
		//���������ǉ� �z�X�g��
		sBufWhere += " AND PCNAME ='" + HostName + "'";
    }
	sBufWhere += " AND DTKSHIN ='" + sBufDTKSHIN + "'";
	sBufWhere += " AND SKTYMD >='" + sBufSKTYMD + "'";
	sBufWhere += " AND LOTNO IN (" + sBufWLOTNO + ")";
    if ( Trim(sBufWSKB_NO) != "" ) {
		sBufWhere += " AND " + sBufWSKB_NO;
    }
	sBufWhere += sBufWTOKU_FLG;
	sBufWhere += " AND DISP_VAL_SU > 0 ";
	if( iLOTNO_Length == 5 ){
		sBufOrder = " ORDER BY DTKSHIN,SUBSTR(LOTNO,2),ORDER_NO";
	} else {
		sBufOrder = " ORDER BY DTKSHIN,LOTNO,ORDER_NO";
	}


    //2003/08/29 E.Takase
    //�w�肳�ꂽ�����ɂ��A�f�[�^�擾�̃e�[�u�����f
	//���Ӑ�i�ԁE���b�g�w��̏ꍇ KSD02W����f�[�^�擾����
	//�������w��̏ꍇ             KSD02 ����f�[�^�擾����
	if ( Rdo6_WHR_TYPE1->Checked == true ){ //���Ӑ�i�ԁE���b�g�w��
		sBufSQL = "SELECT * FROM KSD02W";
    } else {
		sBufSQL = "SELECT * FROM KSD02";
    }
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


	//��������������������������������������������������������������
    //KSD01 ���� KSD01W����f�[�^���擾
    //�������� �쐬
	sBufWhere =  " WHERE ";
    //2003/08/29 E.Takase
    //�w�肳�ꂽ�����ɂ��A�f�[�^�擾�̃e�[�u�����f
	//���Ӑ�i�ԁE���b�g�w��̏ꍇ KSD02W����f�[�^�擾����
	//�������w��̏ꍇ             KSD02 ����f�[�^�擾����
	if ( Rdo6_WHR_TYPE1->Checked == true ){ //���Ӑ�i�ԁE���b�g�w��
		//���������ǉ� �z�X�g��
		sBufWhere += " PCNAME ='" + HostName + "' AND ";
    }
	sBufWhere += " DTKSHIN ='" + sBufDTKSHIN + "'";
	sBufWhere += " AND SKTYMD >='" + sBufSKTYMD + "'";
	sBufWhere += " AND LOTNO IN (" + sBufWLOTNO + ")";
	if( iLOTNO_Length == 5 ){
		sBufOrder = " ORDER BY DTKSHIN,SUBSTR(LOTNO,2)";
	} else {
		sBufOrder = " ORDER BY DTKSHIN,LOTNO";
	}

    //2003/08/29 E.Takase
    //�w�肳�ꂽ�����ɂ��A�f�[�^�擾�̃e�[�u�����f
	//���Ӑ�i�ԁE���b�g�w��̏ꍇ KSD02W����f�[�^�擾����
	//�������w��̏ꍇ             KSD02 ����f�[�^�擾����
	if ( Rdo6_WHR_TYPE1->Checked == true ){ //���Ӑ�i�ԁE���b�g�w��
		sBufSQL = "SELECT * FROM KSD01W";
    } else {
		sBufSQL = "SELECT * FROM KSD01";
    }
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

	//��������������������������������������������������������������
	//KSD11
	sBufWhere =  " WHERE ";
	sBufWhere += " DTKSHIN ='" + sBufDTKSHIN + "'";
	sBufWhere += " AND SKTYMD >='" + sBufSKTYMD + "'";
	sBufWhere += " AND LOTNO IN (" + sBufWLOTNO + ")";
	sBufWhere += " AND SOKU_VAL_SU > 0 ";
	if( iLOTNO_Length == 5 ){
		sBufOrder = " ORDER BY DTKSHIN,SUBSTR(LOTNO,2),SKTYMD";
	} else {
		sBufOrder = " ORDER BY DTKSHIN,LOTNO,SKTYMD";
	}

	sBufSQL = "SELECT * FROM KSD11";
	sBufSQL += sBufWhere;
	sBufSQL += sBufOrder;

	Q_CRSub_KSD11->Close();
	Q_CRSub_KSD11->SQL->Clear();
	Q_CRSub_KSD11->SQL->Add(sBufSQL);
	Q_CRSub_KSD11->Open();
	Q_CRSub_KSD11->Active = true;

	//��������������������������������������������������������������
	//�f�[�^������
	iCRSF_KSD01_MAX = 12;
	iCRSF_KSD01_Num = 0;
	iCRSF_KSD01_Pos = 0;
	iCRSF_KSD02_MAX = GetCRSF_KSD02_NUM();
   	CRSF_KSD02 = new  struct TCRSF_KSD02[iCRSF_KSD02_MAX];
	CRSF_KSD12 = new  struct TCRSF_KSD02[iCRSF_KSD02_MAX];

	iCRSF_KSD02_Num = 0;
	iCRSF_KSD02_Pos = 0;
	iCRSF_KSD12_Num = 0;
	iCRSF_KSD12_Pos = 0;
	iCRSF_KSD11_MAX = GetCRSF_KSD11_NUM() * GetCRSF_KSD11_DayNUM();
	iCRSF_KSD11_Num1 = 0;
	iCRSF_KSD11_Pos = 0;
	//CRSF_KSD11 = new  struct TCRSF_KSD11[iCRSF_KSD11_MAX];

	CRSF_KSD11 = new  struct TCRSF_KSD11*[iCRSF_KSD01_MAX];
	for ( i = 0; i < iCRSF_KSD01_MAX; i++ ) {
	    CRSF_KSD11[i] = new  struct TCRSF_KSD11[iCRSF_KSD11_MAX];
	}
	iCRSF_KSD11_Num2      = new  int[iCRSF_KSD01_MAX];
    //2003.05.26 E.Takase Add ��
	iCRSF_KSD11_SKTYMDNum = new  int[iCRSF_KSD01_MAX];
    //2003.05.26 E.Takase Add ��
    //2003.05.26 E.Takase �R�����g ��
	//iCRSF_KSD11_OUTFLAG   = new  int[iCRSF_KSD01_MAX];
	//2003.06.10 E.Takase Edit iCRSF_KSD11_OUTFLAG   = new  int[iCRSF_KSD11_MAX];
	iCRSF_KSD11_OUTFLAG   = new  int[iCRSF_KSD01_MAX];
    //2003.05.26 E.Takase �R�����g ��


    //2003.05.26 E.Takase Add ��
    sCRSF_KSD11_SKTYMDMin->Clear();
    sCRSF_KSD11_SKTYMDStr->Clear();
    sCRSF_KSD11_UPDCHR->Clear();
    sCRSF_KSD11_SKTYMD->Clear();
	for ( i = 0; i < iCRSF_KSD01_MAX; i++ ) {
    	sCRSF_KSD11_SKTYMDMin->Add("");
    	sCRSF_KSD11_SKTYMDStr->Add("");
    	sCRSF_KSD11_UPDCHR->Add("");
    	sCRSF_KSD11_SKTYMD->Add("");
	}
    //2003.05.26 E.Takase Add ��
    //2003.05.26 E.Takase �R�����g ��
	//sCRSF_KSD11_SKTYMDMin = new  AnsiString[iCRSF_KSD01_MAX];
	//sCRSF_KSD11_SKTYMDStr = new  AnsiString[iCRSF_KSD01_MAX];
	//sCRSF_KSD11_UPDCHR    = new  AnsiString[iCRSF_KSD01_MAX];
	//sCRSF_KSD11_SKTYMD    = new  AnsiString[iCRSF_KSD01_MAX];
    //2003.05.26 E.Takase �R�����g ��

	//�f�[�^�̏o�́��Z�b�g
	Q_CRSub_KSD01->First();
	Q_CRSub_KSD02->First();

	strcpy(sCRSF_DTKSHIN , Null_S(Q_CRSub_KSD01->FieldValues["DTKSHIN"]).c_str());	//�@���Ӑ�i��
	strcpy(sCRSF_ZISNAM  , Null_S(Q_CRSub_KSD01->FieldValues["ZISNAM"]).c_str());	//�A�ގ����́i�i��j
	strcpy(sCRSF_HINMEI  , Null_S(Q_CRSub_KSD01->FieldValues["HINMEI"]).c_str());	//�B�i��

/*
	while(Q_CRSub_KSD02->Eof == false) {
		//���b�g�̕`��ʒu�擾(���̎�1�y�[�W�ɓ��郍�b�g���𒴂�������y�[�W���܂�)
		iCRSF_KSD01_Pos = GetiCRSF_KSD01_Pos6(Null_S(Q_CRSub_KSD02->FieldValues["LOTNO"]));

		//�����O�σf�[�^(SKB_NO=2 && KOMK_NO=1)�Ȃ� CRSF_KSD01[i].DISP_VAL01�ɃZ�b�g
		if ( Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NO"]) == "1" &&
             Null_S(Q_CRSub_KSD02->FieldValues["SKB_NO"])  == "2"  ) {
            //2003.05.16 E.Takase
			//if ( Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL01"]) == "1" ) {
			if ( Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL01"]) == "0" ) {
				strcpy(CRSF_KSD01[iCRSF_KSD01_Pos].DISP_VAL01 , "��");
			} else {
				strcpy(CRSF_KSD01[iCRSF_KSD01_Pos].DISP_VAL01 , "��");
			}
        //����ȊO�͏ڍו��ɏo��
		} else {

			//���荀�ڂ̕`��ʒu�擾
            //2003.06.10 E.Takase
			//iCRSF_KSD02_Pos = GetiCRSF_KSD02_Pos(Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NM"]),
			//								 Null_S(Q_CRSub_KSD02->FieldValues["KOMK_SUB"]));
			iCRSF_KSD02_Pos = GetiCRSF_KSD02_Pos(Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NM"]),
										 		 Null_S(Q_CRSub_KSD02->FieldValues["KOMK_SUB"]),
										 		 Null_S(Q_CRSub_KSD02->FieldValues["HINBAN_SK"]),
										 		 atoi(Null_S(Q_CRSub_KSD02->FieldValues["KIKI_NO"]).c_str()),
										 		 atoi(Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NO"]).c_str()) );

			//�f�[�^�ڍו�(sRepData6_3)�Ƀf�[�^�o��
			WriteCRSF_sRepData6_3();

            //������
            iBufSKB_NO = atoi(Null_S(Q_CRSub_KSD02->FieldValues["SKB_NO"]).c_str());
            if ( iBufSKB_NO == 2 || iBufSKB_NO == 3 ) {
            	iBufUPDCHRCD = atoi(Null_S(Q_CRSub_KSD02->FieldValues["UPDCHR"]).c_str());
                if ( iBufUPDCHRCD != 0 ) {
                	if ( CRSF_KSD01[iCRSF_KSD01_Pos].UPDCHRCD2 == 0 || CRSF_KSD01[iCRSF_KSD01_Pos].UPDCHRCD2 > iBufUPDCHRCD ) {
                    	CRSF_KSD01[iCRSF_KSD01_Pos].UPDCHRCD2 = iBufUPDCHRCD;
                    }
                }
            }

		}

		Q_CRSub_KSD02->Next();
	}
*/

	while(Q_CRSub_KSD02->Eof == false) {
        sBuf = "";
        //2003.08.05 E.Takase
        //�o�͑Ώۂ̑��荀�ڂ��ǂ����𔻒f
        //���Ӑ�i�ԁE���b�g�w��̏ꍇ�̂݃`�F�b�N
		if ( Rdo6_WHR_TYPE1->Checked == true ){
		//���Ӑ�i�ԁE���b�g�w��̏ꍇ
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
	        for ( i = 0; i < Clb6_CHK_KOUMOKU->Items->Count; i++ ) {
	        	if ( Clb6_CHK_KOUMOKU->Items->Strings[i] == sBuf ) {
	                if ( Clb6_CHK_KOUMOKU->Checked[i] == true ) {
	            		iFlag = 1;
	                }
	            }
	        }
        } else {
        //�������w��̏ꍇ
        	iFlag = 1;
        }

        ////2003/08/30 E.Takase
        //test
        //iFlag = 1;

        if ( iFlag == 1 ) {

			//���b�g�̕`��ʒu�擾(���̎�1�y�[�W�ɓ��郍�b�g���𒴂�������y�[�W���܂�)
			iCRSF_KSD01_Pos = GetiCRSF_KSD01_Pos6(Null_S(Q_CRSub_KSD02->FieldValues["LOTNO"]));

			//�����O�σf�[�^(SKB_NO=2 && KOMK_NO=1)�Ȃ� CRSF_KSD01[i].DISP_VAL01�ɃZ�b�g
			if ( Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NO"]) == "1" &&
	             Null_S(Q_CRSub_KSD02->FieldValues["SKB_NO"])  == "2"  ) {
	            //2003.05.16 E.Takase
				//if ( Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL01"]) == "1" ) {
				if ( Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL01"]) == "0" ) {
					strcpy(CRSF_KSD01[iCRSF_KSD01_Pos].DISP_VAL01 , "��");
				} else {
                	//2003.09.16 E.Takase
                    //�O�� �󔒂̂Ƃ��͂��̂܂ܕ\��
                    if ( Trim(Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL01"])) == "" ) {
						strcpy(CRSF_KSD01[iCRSF_KSD01_Pos].DISP_VAL01 , " ");
                    } else {
						strcpy(CRSF_KSD01[iCRSF_KSD01_Pos].DISP_VAL01 , "��");
                    }
				}
	        //����ȊO�͏ڍו��ɏo��
			} else {

				//���荀�ڂ̕`��ʒu�擾
	            //2003.06.10 E.Takase
				//iCRSF_KSD02_Pos = GetiCRSF_KSD02_Pos(Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NM"]),
				//								 Null_S(Q_CRSub_KSD02->FieldValues["KOMK_SUB"]));
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

				//�f�[�^�ڍו�(sRepData6_3)�Ƀf�[�^�o��
				WriteCRSF_sRepData6_3();

	            //������
	            iBufSKB_NO = atoi(Null_S(Q_CRSub_KSD02->FieldValues["SKB_NO"]).c_str());
	            if ( iBufSKB_NO == 2 || iBufSKB_NO == 3 ) {
	            	iBufUPDCHRCD = atoi(Null_S(Q_CRSub_KSD02->FieldValues["UPDCHR"]).c_str());
	                if ( iBufUPDCHRCD != 0 ) {
	                	if ( CRSF_KSD01[iCRSF_KSD01_Pos].UPDCHRCD2 == 0 || CRSF_KSD01[iCRSF_KSD01_Pos].UPDCHRCD2 > iBufUPDCHRCD ) {
	                    	CRSF_KSD01[iCRSF_KSD01_Pos].UPDCHRCD2 = iBufUPDCHRCD;
	                    }
	                }
	            }

			}
        }

		Q_CRSub_KSD02->Next();
	}



	//�y�[�WNo���o��
	fprintf( fCRSF_stream2,"*,0,PAGENO,");
   	//fprintf( fCRSF_stream2,"%d,%s,%s,%s,\n",iCRSF_PageNo+1,sCRSF_DTKSHIN,sCRSF_ZISNAM,sCRSF_HINMEI);
   	//
	//fprintf( fCRSF_stream2,"%d,%s,%s,%s,%s,\n",
   	//		iCRSF_PageNo,sCRSF_DTKSHIN,sCRSF_ZISNAM,sCRSF_HINMEI,CRSF_KSD01[0].LOTNO);
	if ( Rdo6_WHR_TYPE1->Checked == true ){
		//���Ӑ�i�ԁE���b�g�w��̏ꍇ�͕i���ƕi��̓t�H�[���Ŏw�肳�ꂽ����
		fprintf( fCRSF_stream2,"%d,%s,%s,%s,%s,\n",
    		iCRSF_PageNo+1,sCRSF_DTKSHIN,Edt6_CHK_HINSYU->Text.c_str(),Edt6_CHK_HINMEI->Text.c_str(),CRSF_KSD01[0].LOTNO);
	} else {
		//�������w��̏ꍇ�̓f�[�^�x�[�X����
		fprintf( fCRSF_stream2,"%d,%s,%s,%s,%s,\n",
    			iCRSF_PageNo+1,sCRSF_DTKSHIN,sCRSF_ZISNAM,sCRSF_HINMEI,CRSF_KSD01[0].LOTNO);
	}

	//���b�g�f�[�^���o��
	WriteCRSF_KSD01();
	//���荀�ڃf�[�^���o��
	WriteCRSF_KSD02();
    //�����f�[�^�擾�E�o��
    SetCRSF_KSD11();
   	iCRSF_PageNo++;


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
//    CreateReportSub6FOut�Ŏg�p����܂�
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
int  __fastcall TForm1::GetiCRSF_KSD01_Pos6(AnsiString sSrchLOTNO)
{
	int i;
	int iPos;
	AnsiString sBuf;
	AnsiString sBufSKTYMD;

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
			//�y�[�WNo���o��
	        fprintf( fCRSF_stream2,"*,0,PAGENO,");
	        //fprintf( fCRSF_stream2,"%d,%s,%s,%s,\n",iCRSF_PageNo+1,sCRSF_DTKSHIN,sCRSF_ZISNAM,sCRSF_HINMEI);
		 	fprintf( fCRSF_stream2,"%d,%s,%s,%s,%s,\n",
    						iCRSF_PageNo+1,sCRSF_DTKSHIN,sCRSF_ZISNAM,sCRSF_HINMEI,CRSF_KSD01[0].LOTNO);
			//fprintf( fCRSF_stream2,"*,0,PAGENO,");
			//fprintf( fCRSF_stream2,"%d,\n",iCRSF_PageNo+1);

			//���b�g�f�[�^���o��
			WriteCRSF_KSD01();
			//���荀�ڃf�[�^���o��
			WriteCRSF_KSD02();

			//�����f�[�^�擾�E�o��
            SetCRSF_KSD11();


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
				//CRSF_KSD01[iPos].SKTYMD		 	 = Null_S(Q_CRSub_KSD01->FieldValues["SKTYMD"]);
                sBufSKTYMD = Null_S(Q_CRSub_KSD01->FieldValues["SKTYMD"]);
                if ( Trim(sBufSKTYMD) != "" ) {
				    sBufSKTYMD.Insert("/",7);
				    sBufSKTYMD.Insert("/",5);
                }
                strcpy(CRSF_KSD01[iPos].SKTYMD , sBufSKTYMD.c_str());

                //2003.05.10 E.Takase Add ��
				//CRSF_KSD01[iPos].SKTYMD_SZ		 = Null_S(Q_CRSub_KSD01->FieldValues["SKTYMD_SZ_PRT"]);
                sBufSKTYMD = Null_S(Q_CRSub_KSD01->FieldValues["SKTYMD_SZ_PRT"]);
                if ( Trim(sBufSKTYMD) != "" ) {
				    sBufSKTYMD.Insert("/",7);
				    sBufSKTYMD.Insert("/",5);
                }
                strcpy(CRSF_KSD01[iPos].SKTYMD_SZ , sBufSKTYMD.c_str());
                //2003.05.10 E.Takase Add ��

                //2003.06.11 E.Takase Add
                CRSF_KSD01[iPos].UPDCHRCD = atoi(Null_S(Q_CRSub_KSD01->FieldValues["UPDCHR"]).c_str());

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
//    ����֐�					�F���荀�ڂ̕`��ʒu�擾���܂�
//
//  �@�\����
//	  �\����CRSF_KSD02�Ɏw�肳�ꂽ���荀�ڂ̏��������܂��B
//    CreateReportSub5FOut�Ŏg�p����܂�
//    CreateReportSub6FOut�Ŏg�p����܂�
//
//  �p�����^����
//    AnsiString sSrchKOMK_NM		�F���������i���荀�ږ��́j
//    AnsiString sSrchKOMK_SUB		�F���������i���荀�ڃT�u���́j
//    AnsiString sSrchHINBAN_SK		�F���������i�i�ԁj
//    int		 iSrchKIKI_NO		�F���������i����@��No�j
//    int		 iSrchKOMK_NO		�F���������i���荀��No�j
//    AnsiString sSrchTANI			�F���������i�P�ʁj   //2003/10/22 E.Takase Add
//
//  �߂�l
//    int						�F���荀�ڂ̕`��ʒu
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
int  __fastcall TForm1::GetiCRSF_KSD02_Pos(AnsiString sSrchKOMK_NM, AnsiString sSrchKOMK_SUB,
											AnsiString sSrchHINBAN_SK, int iSrchKIKI_NO, int iSrchKOMK_NO,
                                            AnsiString sSrchTANI)
{
	int i;
	int iBufSKB_NO;
	int iPos;
	AnsiString sBufSKTYMD;

	iPos = -1;
	for ( i = 0; i < iCRSF_KSD02_Num; i++ ) {
        // 2003/10/21 A.Tamura ������[TANI]�͕K�v���H
        // 2003/10/22 E.Takase Add ������[TANI]�͕K�v
		if ( AnsiString(CRSF_KSD02[i].KOMK_NM)   == sSrchKOMK_NM   	&&
			 AnsiString(CRSF_KSD02[i].KOMK_SUB)  == sSrchKOMK_SUB 	&&
			 AnsiString(CRSF_KSD02[i].HINBAN_SK) == sSrchHINBAN_SK 	&&
			 CRSF_KSD02[i].KIKI_NO 				 == iSrchKIKI_NO 	&&
			 CRSF_KSD02[i].KOMK_NO 				 == iSrchKOMK_NO 	&&
			 AnsiString(CRSF_KSD02[i].TANI)   	 == sSrchTANI	 	) {
			iPos = i;
		}
	}
	if ( iPos == -1 ) {
		//iPos�ʒu�ɑ��荀�ڃf�[�^���Z�b�g
		iPos = iCRSF_KSD02_Num;
		CRSF_KSD02[iPos].SKB_NO		 = atoi(Null_S(Q_CRSub_KSD02->FieldValues["SKB_NO"]).c_str());
		strcpy(CRSF_KSD02[iPos].KOMK_NM	 	 , Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NM"]).c_str());
		strcpy(CRSF_KSD02[iPos].KOMK_SUB	 , Null_S(Q_CRSub_KSD02->FieldValues["KOMK_SUB"]).c_str());
		strcpy(CRSF_KSD02[iPos].TANI		 , Null_S(Q_CRSub_KSD02->FieldValues["TANI"]).c_str());
		CRSF_KSD02[iPos].KIKA_TYPE	 = atoi(Null_S(Q_CRSub_KSD02->FieldValues["KIKA_TYPE"]).c_str());
		CRSF_KSD02[iPos].KIKA_KIND	 = atoi(Null_S(Q_CRSub_KSD02->FieldValues["KIKA_KIND"]).c_str());
		CRSF_KSD02[iPos].KIKA_DECI	 = atoi(Null_S(Q_CRSub_KSD02->FieldValues["KIKA_DECI"]).c_str());
		CRSF_KSD02[iPos].KIKA_NUM1	 = atof(Null_S(Q_CRSub_KSD02->FieldValues["KIKA_NUM1"]).c_str());
		CRSF_KSD02[iPos].KIKA_NUM2	 = atof(Null_S(Q_CRSub_KSD02->FieldValues["KIKA_NUM2"]).c_str());
		CRSF_KSD02[iPos].KIKA_NUM3	 = atof(Null_S(Q_CRSub_KSD02->FieldValues["KIKA_NUM3"]).c_str());
		CRSF_KSD02[iPos].KIKA_PRT	 = atoi(Null_S(Q_CRSub_KSD02->FieldValues["KIKA_PRT"]).c_str());
		CRSF_KSD02[iPos].VALUE_TYPE	 = atoi(Null_S(Q_CRSub_KSD02->FieldValues["VALUE_TYPE"]).c_str());
		CRSF_KSD02[iPos].VALUE_DECI	 = atoi(Null_S(Q_CRSub_KSD02->FieldValues["VALUE_DECI"]).c_str());
		strcpy(CRSF_KSD02[iPos].KIKA_STR	 , Null_S(Q_CRSub_KSD02->FieldValues["KIKA_STR"]).c_str());
		strcpy(CRSF_KSD02[iPos].KOMK_ENG	 , Null_S(Q_CRSub_KSD02->FieldValues["KOMK_ENG"]).c_str());
		//������̏����ݒ�(yyyymmdd��yyyy/mm/dd)
		//CRSF_KSD02[iPos].SKTYMD		 = Null_S(Q_CRSub_KSD02->FieldValues["SKTYMD"]);
        sBufSKTYMD = Null_S(Q_CRSub_KSD02->FieldValues["SKTYMD"]);
        if ( Trim(sBufSKTYMD) != "" ) {
		    sBufSKTYMD.Insert("/",7);
		    sBufSKTYMD.Insert("/",5);
        }
        strcpy(CRSF_KSD02[iPos].SKTYMD ,sBufSKTYMD.c_str());

        //2003.06.10 E.Takase Add
		strcpy(CRSF_KSD02[iPos].HINBAN_SK	 , Null_S(Q_CRSub_KSD02->FieldValues["HINBAN_SK"]).c_str());
		CRSF_KSD02[iPos].KIKI_NO	 = atoi(Null_S(Q_CRSub_KSD02->FieldValues["KIKI_NO"]).c_str());
		CRSF_KSD02[iPos].KOMK_NO	 = atoi(Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NO"]).c_str());

		iCRSF_KSD02_Num++;
	} else {
		//������̔�r
		iBufSKB_NO = atoi(Null_S(Q_CRSub_KSD02->FieldValues["SKB_NO"]).c_str());
		if ( iBufSKB_NO == 1 ) {
			sBufSKTYMD = Null_S(Q_CRSub_KSD02->FieldValues["SKTYMD"]);
            if ( Trim(AnsiString(CRSF_KSD02[iPos].SKTYMD)) != "" ) {
			    sBufSKTYMD.Insert("/",7);
			    sBufSKTYMD.Insert("/",5);
            }
			if ( AnsiString(CRSF_KSD02[iPos].SKTYMD) > sBufSKTYMD ) {
            	strcpy(CRSF_KSD02[iPos].SKTYMD , sBufSKTYMD.c_str());
			}
		}
	}

	return ( iPos );
	

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�					�F���b�g�f�[�^���o�͂��܂�
//
//  �@�\����
//	  CRSF_KSD01�̃f�[�^���o�͂��܂��B
//    CreateReportSub5FOut�EGetiCRSF_KSD01_Pos5�Ŏg�p����܂�
//    CreateReportSub6FOut�EGetiCRSF_KSD01_Pos6�Ŏg�p����܂�
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
void __fastcall TForm1::WriteCRSF_KSD01(void)
{
	int i;
    AnsiString sBufMEMO;
    AnsiString sBufLOTNO;
    int        iLenLOTNO;
    int        iPosLOTNO;

	fprintf( fCRSF_stream2,"*,1,LTONO,\n");

	for ( i = 0; i < iCRSF_KSD01_Num; i++ ) {
        //sBufMEMO = StrConvAtoB( AnsiString(CRSF_KSD01[i].MEMO),"\n","[CR+LF]");
        //2003.05.23 E.Takase Add ��
        sBufMEMO = AnsiString(CRSF_KSD01[i].MEMO);
        sBufMEMO = StrConvAtoB( AnsiString(sBufMEMO),"\r\n","[CR+LF]");
        sBufMEMO = StrConvAtoB( AnsiString(sBufMEMO),"\n\n","[CR+LF]");
        sBufMEMO = StrConvAtoB( AnsiString(sBufMEMO),"\n","[CR+LF]");
        sBufMEMO = StrConvAtoB( AnsiString(sBufMEMO),"\r","[CR+LF]");
		//2003.05.23 E.Takase Add ��

        //2003.06.11 E.Takase Edit
        if ( CRSF_KSD01[i].UPDCHRCD2 != 0 ) {
        	strcpy(CRSF_KSD01[i].UPDCHR2, GetTANNAM(IntToStr(CRSF_KSD01[i].UPDCHRCD2)).c_str());
        } else {
        	strcpy(CRSF_KSD01[i].UPDCHR2, CRSF_KSD01[i].UPDCHR);
        }

        //2003/08/27 E.Takase
        //���b�gNO�̌��� ��ʂŎw��i���n��j
        sBufLOTNO = CRSF_KSD01[i].LOTNO;
        if ( iLOTNO_OUT_Length < 6 ) {
        	// �E���� iLOTNO_OUT_Length �����p
	        iLenLOTNO = sBufLOTNO.Length();
            iPosLOTNO = iLenLOTNO - iLOTNO_OUT_Length;
            if( iPosLOTNO > 0 ){
            	sBufLOTNO = sBufLOTNO.SubString( iPosLOTNO + 1, iLOTNO_OUT_Length );
        	}
        }
        fprintf( fCRSF_stream2,"%d,%s,%s,%s,%s,%s,%s,%s,%s,\n",
						i,
						sBufLOTNO.c_str(),
						CRSF_KSD01[i].DISP_VAL01,
						CRSF_KSD01[i].SOZAI_OK_PRT,
						CRSF_KSD01[i].SYUKA_OK_PRT,
						CRSF_KSD01[i].UPDCHR2,
						CRSF_KSD01[i].SKTYMD,
						sBufMEMO.c_str(),
                        CRSF_KSD01[i].SKTYMD_SZ
						);
	}
}
//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�					�F���荀�ڃf�[�^���o�͂��܂�
//
//  �@�\����
//	  CRSF_KSD02�̃f�[�^���o�͂��܂��B
//    CreateReportSub5FOut�EGetiCRSF_KSD01_Pos5�Ŏg�p����܂�
//    CreateReportSub6FOut�EGetiCRSF_KSD01_Pos6�Ŏg�p����܂�
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
void __fastcall TForm1::WriteCRSF_KSD02(void)
{
	int i;

	fprintf( fCRSF_stream2,"*,2,KOMK_NM,\n");

	for ( i = 0; i < iCRSF_KSD02_Num; i++ ) {
        //���j-1�͕������i��������Ȃ��̂�-1�j
		fprintf( fCRSF_stream2,"%d,-1,%s,%s,%s,%d,%d,%d,%lf,%lf,%lf,%d,%s,%s,\n",
						i,
						CRSF_KSD02[i].KOMK_NM,
						CRSF_KSD02[i].KOMK_SUB,
						CRSF_KSD02[i].TANI,
						CRSF_KSD02[i].KIKA_TYPE,
						CRSF_KSD02[i].KIKA_KIND,
						CRSF_KSD02[i].KIKA_DECI,
						CRSF_KSD02[i].KIKA_NUM1,
						CRSF_KSD02[i].KIKA_NUM2,
						CRSF_KSD02[i].KIKA_NUM3,
						CRSF_KSD02[i].KIKA_PRT,
						CRSF_KSD02[i].KIKA_STR,
						CRSF_KSD02[i].KOMK_ENG
						);
	}

	//for ( i = 0; i < iCRSF_KSD02_Num; i++ ) {
	//	fprintf( fCRSF_stream2,"%d,%s,%s,%s,%d,%d,%d,%lf,%lf,%lf,%d,%d,%d,%s,\n",
	//					i,
	//					CRSF_KSD02[i].KOMK_NM.c_str(),
	//					CRSF_KSD02[i].KOMK_SUB.c_str(),
	//					CRSF_KSD02[i].TANI.c_str(),
	//					CRSF_KSD02[i].KIKA_TYPE,
	//					CRSF_KSD02[i].KIKA_KIND,
	//					CRSF_KSD02[i].KIKA_DECI,
	//					CRSF_KSD02[i].KIKA_NUM1,
	//					CRSF_KSD02[i].KIKA_NUM2,
	//					CRSF_KSD02[i].KIKA_NUM3,
	//					CRSF_KSD02[i].KIKA_PRT,
	//					CRSF_KSD02[i].VALUE_TYPE,
	//					CRSF_KSD02[i].VALUE_DECI,
	//					CRSF_KSD02[i].SKTYMD.c_str()
	//					);
	//}


}
//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�					�F�f�[�^�ڍו�(sRepData6_3)�Ƀf�[�^�o�͂��܂�
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
void __fastcall TForm1::WriteCRSF_sRepData6_3(void)
{

	int iBuf;
	int i;
	int n;
	AnsiString sBufSOKU_FLG;
	AnsiString sBuf;
	AnsiString sBufSQL;
	AnsiString sBufSOKUVAL[10];

    //2003/08/30 E.Takase
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
        	//����l�\��,����l�����_�ȉ�����
            fprintf( fCRSF_stream3,"%d,",atoi(sReVALUE_TYPE.c_str()));
            fprintf( fCRSF_stream3,"%d,",atoi(sReVALUE_DECI.c_str()));
  			//���萔,
 			fprintf( fCRSF_stream3,"%d,",atoi(sReDISP_VAL_SU.c_str()));
			//����l1,�E�E�E�E
			for ( i = 0; i < iBuf; i++ ) {
				fprintf( fCRSF_stream3,"%s,",sReDISP_VAL->Strings[i].c_str());
			}
		    if ( iRDjMax < iBuf ) {
		        iRDjMax = iBuf;
		    }

        } else {
        	//����l�\��,����l�����_�ȉ�����
            fprintf( fCRSF_stream3,"0,");
            fprintf( fCRSF_stream3,"0,");
  			//���萔,
            //2003.09.13 E.Takase
 			//fprintf( fCRSF_stream3,"0,");
 			fprintf( fCRSF_stream3,"1,");
			//����l1,�E�E�E�E
			fprintf( fCRSF_stream3," ,");
        }

		fprintf( fCRSF_stream3,"\n");
	    iRDiMax++;

    } else {
    	//�u���肷��(SOKU_FLG = 1)�v
		//����l�\��,����l�����_�ȉ�����,
		iBuf = atoi(Null_S(Q_CRSub_KSD02->FieldValues["VALUE_TYPE"]).c_str());
		fprintf( fCRSF_stream3,"%d,",iBuf);
		iBuf = atoi(Null_S(Q_CRSub_KSD02->FieldValues["VALUE_DECI"]).c_str());
		fprintf( fCRSF_stream3,"%d,",iBuf);

		//���萔,
		iBuf = atoi(Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL_SU"]).c_str());
		fprintf( fCRSF_stream3,"%d,",iBuf);

		//����l1,�E�E�E�E
		sBufSOKUVAL[0] =  Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL01"]);
		sBufSOKUVAL[1] =  Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL02"]);
		sBufSOKUVAL[2] =  Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL03"]);
		sBufSOKUVAL[3] =  Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL04"]);
		sBufSOKUVAL[4] =  Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL05"]);
		sBufSOKUVAL[5] =  Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL06"]);
		sBufSOKUVAL[6] =  Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL07"]);
		sBufSOKUVAL[7] =  Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL08"]);
		sBufSOKUVAL[8] =  Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL09"]);
		sBufSOKUVAL[9] =  Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL10"]);
		if ( iBuf > 10 ) {
			n = 10;
		} else {
			n = iBuf;
		}
		for ( i = 0; i < n; i++ ) {
			fprintf( fCRSF_stream3,"%s,",sBufSOKUVAL[i].c_str());
		}

		//���萔��10�`�Ȃ��O�e�[�u�����瑪��l�擾
		if ( iBuf > 10 ) {
		    //2003/08/29 E.Takase
		    //�w�肳�ꂽ�����ɂ��A�f�[�^�擾�̃e�[�u�����f
			//���Ӑ�i�ԁE���b�g�w��̏ꍇ KSD03W����f�[�^�擾����
			//�������w��̏ꍇ             KSD03 ����f�[�^�擾����
			if ( Rdo6_WHR_TYPE1->Checked == true ){ //���Ӑ�i�ԁE���b�g�w��
 				sBufSQL = "SELECT * FROM KSD03W";
				//���������ǉ� �z�X�g��
				sBufSQL += " WHERE PCNAME ='" + HostName + "'";
				sBufSQL += " AND DTKSHIN ='" + Null_S(Q_CRSub_KSD02->FieldValues["DTKSHIN"]) + "'";
				sBufSQL += " AND LOTNO = '" + Null_S(Q_CRSub_KSD02->FieldValues["LOTNO"]) + "'";
				sBufSQL += " AND UNQ_NO = " + Null_S(Q_CRSub_KSD02->FieldValues["UNQ_NO"]);
				sBufSQL += " ORDER BY SOKU_NO";
		    } else {
				sBufSQL = "SELECT * FROM KSD03";
				sBufSQL += " WHERE DTKSHIN ='" + Null_S(Q_CRSub_KSD02->FieldValues["DTKSHIN"]) + "'";
				sBufSQL += " AND LOTNO = '" + Null_S(Q_CRSub_KSD02->FieldValues["LOTNO"]) + "'";
				sBufSQL += " AND UNQ_NO = " + Null_S(Q_CRSub_KSD02->FieldValues["UNQ_NO"]);
				sBufSQL += " ORDER BY SOKU_NO";
		    }

			Q_CRSub_KSD03->Close();
			Q_CRSub_KSD03->SQL->Clear();
			Q_CRSub_KSD03->SQL->Add(sBufSQL);
			Q_CRSub_KSD03->Open();
			Q_CRSub_KSD03->Active = true;
			while(Q_CRSub_KSD03->Eof == false) {
				fprintf( fCRSF_stream3, "%s,",
								Null_S(Q_CRSub_KSD03->FieldValues["DISP_VAL"]).c_str());
				Q_CRSub_KSD03->Next();
			}

		}


		fprintf( fCRSF_stream3,"\n");
	    iRDiMax++;

		iBuf = atoi(Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL_SU"]).c_str());
	    if ( iRDjMax < iBuf ) {
	        iRDjMax = iBuf;
	    }


    }


}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�					�FKSD02���荀�ڐ����擾���܂�
//
//  �@�\����
//	  �\����CRSF_KSD02�̃������擾�̍ۂ̌����擾���܂��B
//	  �\����CRSF_KSD02�ɂ͑�����уf�[�^���Z�b�g����܂��B
//    CreateReportSub5FOut�Ŏg�p����܂�
//    CreateReportSub6FOut�Ŏg�p����܂�
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    int						�FKSD02���荀�ڐ�
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
int __fastcall TForm1::GetCRSF_KSD02_NUM(void)
{
    int n;
    AnsiString sBuf;
    AnsiString sBufA;

    Q_CRSub_KSD02->First();
    n = 0;
    sBuf = ",";
	while(Q_CRSub_KSD02->Eof == false) {
        sBufA  = "";
        sBufA += Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NM"]);
        sBufA += " ";
        sBufA += Null_S(Q_CRSub_KSD02->FieldValues["KOMK_SUB"]);
        //2003.06.10 E.Takase Add
        sBufA += " ";
        sBufA += Null_S(Q_CRSub_KSD02->FieldValues["HINBAN_SK"]);
        sBufA += " ";
        sBufA += Null_S(Q_CRSub_KSD02->FieldValues["KIKI_NO"]);
        sBufA += " ";
        sBufA += Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NO"]);

        sBufA += ",";

        if ( sBuf.AnsiPos("," + sBufA) == 0 ) {
            n++;
            sBuf += sBufA;
        }

		Q_CRSub_KSD02->Next();
	}

    return ( n );
}
//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�					�FKSD11���荀�ڐ����擾���܂�
//
//  �@�\����
//	  �\����CRSF_KSD11�̃������擾�̍ۂ̌���GetCRSF_KSD11_DayNUM�ƃZ�b�g�Ŏ擾���܂��B
//	  �\����CRSF_KSD11�ɂ͑�����ѕ����f�[�^���Z�b�g����܂��B
//    CreateReportSub6FOut�Ŏg�p����܂�
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    int						�FKSD11���荀�ڐ�
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
int __fastcall TForm1::GetCRSF_KSD11_NUM(void)
{
    int n;
    AnsiString sBuf;
    AnsiString sBufA;

    Q_CRSub_KSD11->First();
    n = 0;
    sBuf = ",";
	while(Q_CRSub_KSD11->Eof == false) {
        sBufA  = "";
        sBufA += Null_S(Q_CRSub_KSD11->FieldValues["KOMK_NM"]);
        sBufA += " ";
        sBufA += Null_S(Q_CRSub_KSD11->FieldValues["KOMK_SUB"]);
        //2003.06.10 E.Takase Add
        sBufA += " ";
        sBufA += Null_S(Q_CRSub_KSD11->FieldValues["KIKI_NO"]);
        sBufA += " ";
        sBufA += Null_S(Q_CRSub_KSD11->FieldValues["KOMK_NO"]);

        sBufA += ",";

        if ( sBuf.AnsiPos("," + sBufA) == 0 ) {
            n++;
            sBuf += sBufA;
        }

		Q_CRSub_KSD11->Next();
	}

    return ( n );
}
//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�					�FKSD11������̎�ސ����܂�
//
//  �@�\����
//	  �\����CRSF_KSD11�̃������擾�̍ۂ̌���GetCRSF_KSD11_NUM�ƃZ�b�g�Ŏ擾���܂��B
//	  �\����CRSF_KSD11�ɂ͑�����ѕ����f�[�^���Z�b�g����܂��B
//    CreateReportSub6FOut�Ŏg�p����܂�
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    int						�FKSD11������̎�ސ�
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
int __fastcall TForm1::GetCRSF_KSD11_DayNUM(void)
{
    int n;
    AnsiString sBuf;
    AnsiString sBufA;

    Q_CRSub_KSD11->First();
    n = 0;
    sBuf = ",";
	while(Q_CRSub_KSD11->Eof == false) {
        sBufA  = "";
        sBufA += Null_S(Q_CRSub_KSD11->FieldValues["SKTYMD"]);
        sBufA += ",";

        if ( sBuf.AnsiPos("," + sBufA) == 0 ) {
            n++;
            sBuf += sBufA;
        }

		Q_CRSub_KSD11->Next();
	}

    return ( n );
}
//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�					�FQ_CRSub_KSD11����K�v�ȃf�[�^�̂�CRSF_KSD11�ɃZ�b�g���܂�
//
//  �@�\����
//	  �\����CRSF_KSD01�ɃZ�b�g����Ă���f�[�^��
//    ��v���郌�R�[�h�̂݁i���b�g�mNo�E���荀�ڂŔ��f�jCRSF_KSD11�ɃZ�b�g���܂��B
//    CreateReportSub6FOut�EGetiCRSF_KSD01_Pos6�Ŏg�p����܂�
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
void __fastcall TForm1::SetCRSF_KSD11(void)
{

    int i;
    int j;
    int n;
    int m;
    int l;
    int a;
    int iPos1;
    int iPos2;
    int iFlag2;
    int iBuf;
    AnsiString sBuf;
    AnsiString sBufFileOut;
    AnsiString sBufFileOut_Day;
    char       cBufFileOut[2056];
    AnsiString sBufSQL;
    AnsiString sBufLOTNO;
    AnsiString sBufKOMK_NM;
    AnsiString sBufKOMK_SUB;
	AnsiString sBufSOKUVAL[10];
    AnsiString sBufSKTYMD;
    AnsiString sBufTANNAM;
    AnsiString sBufWtiteStr;
	int 	   iBufKIKI_NO;         	//�@��No		//2003.06.10 E.Takase Add
	int 	   iBufKOMK_NO;         	//���荀��No	//2003.06.10 E.Takase Add

    AnsiString sBufTANI;

    iPos1  = -1;
    iPos2  = -1;
    iFlag2 = -1;
    iCRSF_KSD11_Num1 = iCRSF_KSD01_Num;
    iCRSF_KSD11_SKTYMDNumMax = 0;
	//���荀�ڃf�[�^��������
	//memset( CRSF_KSD11, (int)NULL, sizeof(struct TCRSF_KSD11)*(iCRSF_KSD01_MAX*iCRSF_KSD11_MAX ));
    FormatCRSF_KSD11();
	memset( iCRSF_KSD11_Num2, (int)NULL, sizeof(int)*iCRSF_KSD01_MAX );
	memset( iCRSF_KSD11_SKTYMDNum, (int)NULL, sizeof(int)*iCRSF_KSD01_MAX );
    //2003.05.26 E.Takase �R�����g ��
	//memset( sCRSF_KSD11_SKTYMDMin, (int)NULL, sizeof(AnsiString)*iCRSF_KSD01_MAX );
	//memset( sCRSF_KSD11_SKTYMDStr, (int)NULL, sizeof(AnsiString)*iCRSF_KSD01_MAX );
    //2003.05.26 E.Takase �R�����g ��
    for ( i = 0; i < iCRSF_KSD01_MAX; i++ ) {
        //sCRSF_KSD11_SKTYMDStr[i] = ",";
    	//2003.05.26 E.Takase Add ��
        sCRSF_KSD11_SKTYMDMin->Strings[i] = "";
        sCRSF_KSD11_SKTYMDStr->Strings[i] = ",";
    	//2003.05.26 E.Takase Add ��
    }
    Q_CRSub_KSD11->First();


	while(Q_CRSub_KSD11->Eof == false) {
        iPos1 = -1;
        iPos2 = -1;
        iFlag2 = -1;
        //�`�F�b�N�@���b�g
        sBufLOTNO = Null_S(Q_CRSub_KSD11->FieldValues["LOTNO"]);
        for ( i = 0; i < iCRSF_KSD01_Num; i++ ) {
            if ( sBufLOTNO == AnsiString(CRSF_KSD01[i].LOTNO) ) {
                iPos1 = i;
                break;
            }
        }
        if ( iPos1 >= 0 ) {
            //�`�F�b�N�A�������ږ���
            sBufKOMK_NM  = Null_S(Q_CRSub_KSD11->FieldValues["KOMK_NM"]);
            sBufKOMK_SUB = Null_S(Q_CRSub_KSD11->FieldValues["KOMK_SUB"]);
            //2003.06.10 E.Takase Add
            iBufKIKI_NO = atoi(Null_S(Q_CRSub_KSD11->FieldValues["KIKI_NO"]).c_str());
            iBufKOMK_NO = atoi(Null_S(Q_CRSub_KSD11->FieldValues["KOMK_NO"]).c_str());
            // 2003/10/22 E.Takase Add
            sBufTANI = Null_S(Q_CRSub_KSD11->FieldValues["TANI"]);
            for ( i = 0; i < iCRSF_KSD02_Num; i++ ) {
                //2003.06.10 E.Takase Edit
                //if ( sBufKOMK_NM  == AnsiString(CRSF_KSD02[i].KOMK_NM)  &&
                //     sBufKOMK_SUB == AnsiString(CRSF_KSD02[i].KOMK_SUB) ) {

                // 2003/10/21 A.Tamura ������[TANI]�͕K�v���H
		        // 2003/10/22 E.Takase Add ������[TANI]�͕K�v
				if ( sBufKOMK_NM  == AnsiString(CRSF_KSD02[i].KOMK_NM)  &&
                     sBufKOMK_SUB == AnsiString(CRSF_KSD02[i].KOMK_SUB) &&
                     iBufKIKI_NO  == CRSF_KSD02[i].KIKI_NO  &&
                     iBufKOMK_NO  == CRSF_KSD02[i].KOMK_NO  &&
                     sBufTANI     == AnsiString(CRSF_KSD02[i].TANI)  ) {
                    iFlag2 = i;
                    break;
                }
            }
        }
        if ( iPos1 >= 0 && iFlag2 >= 0 ) {
            iPos2 = iCRSF_KSD11_Num2[iPos1];

			strcpy(CRSF_KSD11[iPos1][iPos2].KOMK_NM	 , Null_S(Q_CRSub_KSD11->FieldValues["KOMK_NM"]).c_str());
			strcpy(CRSF_KSD11[iPos1][iPos2].KOMK_SUB	 , Null_S(Q_CRSub_KSD11->FieldValues["KOMK_SUB"]).c_str());
			strcpy(CRSF_KSD11[iPos1][iPos2].TANI		 , Null_S(Q_CRSub_KSD11->FieldValues["TANI"]).c_str());
			CRSF_KSD11[iPos1][iPos2].KIKA_TYPE	 = atoi(Null_S(Q_CRSub_KSD11->FieldValues["KIKA_TYPE"]).c_str());
			CRSF_KSD11[iPos1][iPos2].KIKA_KIND	 = atoi(Null_S(Q_CRSub_KSD11->FieldValues["KIKA_KIND"]).c_str());
			CRSF_KSD11[iPos1][iPos2].KIKA_DECI	 = atoi(Null_S(Q_CRSub_KSD11->FieldValues["KIKA_DECI"]).c_str());
			CRSF_KSD11[iPos1][iPos2].KIKA_NUM1	 = atof(Null_S(Q_CRSub_KSD11->FieldValues["KIKA_NUM1"]).c_str());
			CRSF_KSD11[iPos1][iPos2].KIKA_NUM2	 = atof(Null_S(Q_CRSub_KSD11->FieldValues["KIKA_NUM2"]).c_str());
			CRSF_KSD11[iPos1][iPos2].KIKA_NUM3	 = atof(Null_S(Q_CRSub_KSD11->FieldValues["KIKA_NUM3"]).c_str());
			CRSF_KSD11[iPos1][iPos2].KIKA_PRT	 = atoi(Null_S(Q_CRSub_KSD11->FieldValues["KIKA_PRT"]).c_str());
			CRSF_KSD11[iPos1][iPos2].VALUE_TYPE	 = atoi(Null_S(Q_CRSub_KSD11->FieldValues["VALUE_TYPE"]).c_str());
			CRSF_KSD11[iPos1][iPos2].VALUE_DECI	 = atoi(Null_S(Q_CRSub_KSD11->FieldValues["VALUE_DECI"]).c_str());
			strcpy(CRSF_KSD11[iPos1][iPos2].SKTYMD		 , Null_S(Q_CRSub_KSD11->FieldValues["SKTYMD"]).c_str());
			CRSF_KSD11[iPos1][iPos2].SOKU_VAL_SU = atoi(Null_S(Q_CRSub_KSD11->FieldValues["SOKU_VAL_SU"]).c_str());
			strcpy(CRSF_KSD11[iPos1][iPos2].UPDCHR		 , Null_S(Q_CRSub_KSD11->FieldValues["UPDCHR"]).c_str());

            //2003.06.10 E.Takase Add
            CRSF_KSD11[iPos1][iPos2].KIKI_NO 	= atoi(Null_S(Q_CRSub_KSD11->FieldValues["KIKI_NO"]).c_str());
            CRSF_KSD11[iPos1][iPos2].KOMK_NO 	= atoi(Null_S(Q_CRSub_KSD11->FieldValues["KOMK_NO"]).c_str());


			//����l1,�E�E�E�E
			sBufSOKUVAL[0] =  Null_S(Q_CRSub_KSD11->FieldValues["SOKU_VAL01"]);
			sBufSOKUVAL[1] =  Null_S(Q_CRSub_KSD11->FieldValues["SOKU_VAL02"]);
			sBufSOKUVAL[2] =  Null_S(Q_CRSub_KSD11->FieldValues["SOKU_VAL03"]);
			sBufSOKUVAL[3] =  Null_S(Q_CRSub_KSD11->FieldValues["SOKU_VAL04"]);
			sBufSOKUVAL[4] =  Null_S(Q_CRSub_KSD11->FieldValues["SOKU_VAL05"]);
			sBufSOKUVAL[5] =  Null_S(Q_CRSub_KSD11->FieldValues["SOKU_VAL06"]);
			sBufSOKUVAL[6] =  Null_S(Q_CRSub_KSD11->FieldValues["SOKU_VAL07"]);
			sBufSOKUVAL[7] =  Null_S(Q_CRSub_KSD11->FieldValues["SOKU_VAL08"]);
			sBufSOKUVAL[8] =  Null_S(Q_CRSub_KSD11->FieldValues["SOKU_VAL09"]);
			sBufSOKUVAL[9] =  Null_S(Q_CRSub_KSD11->FieldValues["SOKU_VAL10"]);
	        if ( CRSF_KSD11[iPos1][iPos2].SOKU_VAL_SU > 10 ) {
		        n = 10;
	        } else {
		        n = CRSF_KSD11[iPos1][iPos2].SOKU_VAL_SU;
	        }

            sBufWtiteStr = "";
	        for ( i = 0; i < n; i++ ) {
		        sBufWtiteStr += sBufSOKUVAL[i] + ",";
	        }

			//���萔��10�`�Ȃ��O�e�[�u�����瑪��l�擾
			if ( CRSF_KSD11[iPos1][iPos2].SOKU_VAL_SU > 10 ) {
				sBufSQL = "SELECT * FROM KSD12";
				sBufSQL += " WHERE DTKSHIN ='" + Null_S(Q_CRSub_KSD11->FieldValues["DTKSHIN"]) + "'";
				sBufSQL += " AND LOTNO = '" + Null_S(Q_CRSub_KSD11->FieldValues["LOTNO"]) + "'";
				sBufSQL += " AND BNKT_UNQ_NO = " + Null_S(Q_CRSub_KSD11->FieldValues["BNKT_UNQ_NO"]);
				sBufSQL += " ORDER BY SOKU_NO";
				Q_CRSub_KSD12->Close();
				Q_CRSub_KSD12->SQL->Clear();
				Q_CRSub_KSD12->SQL->Add(sBufSQL);
				Q_CRSub_KSD12->Open();
				Q_CRSub_KSD12->Active = true;
				while(Q_CRSub_KSD12->Eof == false) {
                    //2003.06.11 E.Takase Edit
					//sBufWtiteStr += Null_S(Q_CRSub_KSD12->FieldValues["DISP_VAL"]) + ",";
					sBufWtiteStr += Null_S(Q_CRSub_KSD12->FieldValues["SOKU_VAL"]) + ",";
					Q_CRSub_KSD12->Next();
				}
			}
            strcpy(CRSF_KSD11[iPos1][iPos2].WtiteStr,sBufWtiteStr.c_str());

	        //���b�g���̓��t�̎��
	        sBuf = "," + AnsiString(CRSF_KSD11[iPos1][iPos2].SKTYMD) + ",";
	        iBuf = sCRSF_KSD11_SKTYMDStr->Strings[iPos1].AnsiPos(sBuf);
	        if ( iBuf > 0 ) {
	            //���ɓo�^����Ă���
	            //SKTYMD_ID�ɃZ�b�g
	            CRSF_KSD11[iPos1][iPos2].SKTYMD_ID = (iBuf - 1) / 9;
	        } else {
	            CRSF_KSD11[iPos1][iPos2].SKTYMD_ID = iCRSF_KSD11_SKTYMDNum[iPos1];
	            if ( sCRSF_KSD11_SKTYMDMin->Strings[iPos1] == "" ) {
	                sCRSF_KSD11_SKTYMDMin->Strings[iPos1] = CRSF_KSD11[iPos1][iPos2].SKTYMD;
	            } else {
	                if ( sCRSF_KSD11_SKTYMDMin->Strings[iPos1] > CRSF_KSD11[iPos1][iPos2].SKTYMD ) {
	                    sCRSF_KSD11_SKTYMDMin->Strings[iPos1] = CRSF_KSD11[iPos1][iPos2].SKTYMD;
	                }
	            }
	            //sCRSF_KSD11_SKTYMDStr->Strings[iPos1] += AnsiString(CRSF_KSD11[iPos1][iPos2].SKTYMD) + ",";
	            sCRSF_KSD11_SKTYMDStr->Strings[iPos1] = sCRSF_KSD11_SKTYMDStr->Strings[iPos1] + AnsiString(CRSF_KSD11[iPos1][iPos2].SKTYMD) + ",";
	            iCRSF_KSD11_SKTYMDNum[iPos1]++;
	        }

            iCRSF_KSD11_Num2[iPos1]++;
        }


		Q_CRSub_KSD11->Next();
	}
    //���b�g���̓��t��ސ�MAX���擾
    for ( i = 0; i < iCRSF_KSD11_Num1; i++ ) {
        if ( iCRSF_KSD11_SKTYMDNumMax < iCRSF_KSD11_SKTYMDNum[i] ) {
            iCRSF_KSD11_SKTYMDNumMax = iCRSF_KSD11_SKTYMDNum[i];
        }
    }

    //���b�g���̓��t��ސ�MAX�Ń��[�v����CSV�t�@�C���ɏo��
    for ( i = 0; i < iCRSF_KSD11_SKTYMDNumMax; i++ ) {
        memset( CRSF_KSD12, (int)NULL, sizeof(struct TCRSF_KSD02)*iCRSF_KSD02_MAX );
        //2003.05.26 E.Takase Add ��
        for ( j = 0; j < iCRSF_KSD01_MAX; j++ ) {
        	sCRSF_KSD11_UPDCHR->Strings[j] = "";
        	sCRSF_KSD11_SKTYMD->Strings[j] = "";
        }
        //2003.05.26 E.Takase Add ��
        //2003.05.26 E.Takase �R�����g ��
        //memset( sCRSF_KSD11_UPDCHR, (int)NULL, sizeof(AnsiString)*iCRSF_KSD02_MAX );
        //memset( sCRSF_KSD11_SKTYMD, (int)NULL, sizeof(AnsiString)*iCRSF_KSD02_MAX );
        //2003.05.26 E.Takase �R�����g ��

        //2003.05.26 E.Takase Add ��
	    //2003.06.10 E.Takase Edit memset( iCRSF_KSD11_OUTFLAG, (int)NULL, sizeof(int)*iCRSF_KSD11_MAX );
	    memset( iCRSF_KSD11_OUTFLAG, (int)NULL, sizeof(int)*iCRSF_KSD01_MAX );
        //2003.05.26 E.Takase Add ��
        //2003.05.26 E.Takase �R�����g ��
        //memset( iCRSF_KSD11_OUTFLAG, (int)NULL, sizeof(int)*iCRSF_KSD02_MAX );
        //2003.05.26 E.Takase �R�����g ��

        iCRSF_KSD12_Num = 0;
        sBufFileOut = "";
        sBufFileOut_Day = "";
        //���݂̃��b�g�̎�ސ��`�F�b�N
        //if ( iCRSF_KSD11_SKTYMDNum[i] > i ) {
            for ( j = 0; j < iCRSF_KSD02_Num; j++ ) {
                for ( n = 0; n < iCRSF_KSD11_Num1; n++ ) {
                    for ( m = 0; m < iCRSF_KSD11_Num2[n]; m++ ) {
                        //i�Ԗڂ̓���j���ڂ����肳��Ă��邩�H

                        // 2003/10/21 A.Tamura ������[TANI]�͕K�v���H
                        // 2003/10/22 E.Takase Add ������[TANI]�͕K�v
                        if ( CRSF_KSD11[n][m].SKTYMD_ID == i &&
                             strcmp(CRSF_KSD11[n][m].KOMK_NM , CRSF_KSD02[j].KOMK_NM ) == 0 &&
                             strcmp(CRSF_KSD11[n][m].KOMK_SUB , CRSF_KSD02[j].KOMK_SUB ) == 0 &&
                             CRSF_KSD11[n][m].KIKI_NO == CRSF_KSD02[j].KIKI_NO  &&
                             CRSF_KSD11[n][m].KOMK_NO == CRSF_KSD02[j].KOMK_NO  &&
                             strcmp(CRSF_KSD11[n][m].TANI , CRSF_KSD02[j].TANI ) == 0 ) {
                            //���肳��Ă���̂ŏo��
                            CRSF_KSD11[n][m].Write_FLG = 1;
                            //�c�i���荀�ځj�ʒu�̎擾
                            iPos1 = -1;
                            for ( l = 0; l < iCRSF_KSD12_Num; l++ ) {
		                        // 2003/10/21 A.Tamura ������[TANI]�͕K�v���H
                                // 2003/10/22 E.Takase Add ������[TANI]�͕K�v
                                if ( strcmp(CRSF_KSD11[n][m].KOMK_NM   , CRSF_KSD12[l].KOMK_NM ) == 0  &&
                                     strcmp(CRSF_KSD11[n][m].KOMK_SUB  , CRSF_KSD12[l].KOMK_SUB ) == 0  &&
                             		 CRSF_KSD11[n][m].KIKI_NO == CRSF_KSD12[l].KIKI_NO  &&
                             		 CRSF_KSD11[n][m].KOMK_NO == CRSF_KSD12[l].KOMK_NO   &&
                             		 strcmp(CRSF_KSD11[n][m].TANI   , CRSF_KSD12[l].TANI ) == 0   ) {
                                    iPos1 = l;
                                    break;
                                }
                            }
                            if ( iPos1 < 0 ) {
                                iPos1 = iCRSF_KSD12_Num;

								strcpy(CRSF_KSD12[iPos1].KOMK_NM  	, CRSF_KSD11[n][m].KOMK_NM);		//a���荀�ږ���
								strcpy(CRSF_KSD12[iPos1].KOMK_SUB 	, CRSF_KSD11[n][m].KOMK_SUB);		//a���荀�ڃT�u����
								strcpy(CRSF_KSD12[iPos1].TANI	  	, CRSF_KSD11[n][m].TANI);			//a�P��
								CRSF_KSD12[iPos1].KIKA_TYPE		= CRSF_KSD11[n][m].KIKA_TYPE;		//b�K�i�^�C�v
								CRSF_KSD12[iPos1].KIKA_KIND		= CRSF_KSD11[n][m].KIKA_KIND;		//b�K�i���
								CRSF_KSD12[iPos1].KIKA_DECI		= CRSF_KSD11[n][m].KIKA_DECI;		//b�K�i�����_�ȉ�����
								CRSF_KSD12[iPos1].KIKA_NUM1		= CRSF_KSD11[n][m].KIKA_NUM1;		//b�K�i�l1
								CRSF_KSD12[iPos1].KIKA_NUM2		= CRSF_KSD11[n][m].KIKA_NUM2;		//b�K�i�l2
								CRSF_KSD12[iPos1].KIKA_NUM3		= CRSF_KSD11[n][m].KIKA_NUM3;		//b�K�i�l3
								CRSF_KSD12[iPos1].KIKA_PRT  	= CRSF_KSD11[n][m].KIKA_PRT;		//b��������l�̈��
								CRSF_KSD12[iPos1].VALUE_TYPE	= CRSF_KSD11[n][m].VALUE_TYPE;		//b,c����l�\��
								CRSF_KSD12[iPos1].VALUE_DECI	= CRSF_KSD11[n][m].VALUE_DECI;		//c����l�����_�ȉ�����

								sBufSKTYMD = AnsiString(CRSF_KSD11[n][m].SKTYMD);			//�����(�����p)
                                if ( Trim(sBufSKTYMD) != "" ) {
			                        sBufSKTYMD.Insert("/",7);
			                        sBufSKTYMD.Insert("/",5);
                                }
                                strcpy(CRSF_KSD12[iPos1].SKTYMD,sBufSKTYMD.c_str());

					            //2003.06.10 E.Takase Add
					            CRSF_KSD12[iPos1].KIKI_NO 	= CRSF_KSD11[n][m].KIKI_NO;
					            CRSF_KSD12[iPos1].KOMK_NO 	= CRSF_KSD11[n][m].KOMK_NO;


                                iCRSF_KSD12_Num++;
                            }

                            //2004.09.27 E.Takase Edit
                            //�����
                            //sCRSF_KSD11_SKTYMD->Strings[n] = AnsiString(CRSF_KSD12[iPos1].SKTYMD);
							sBufSKTYMD = AnsiString(CRSF_KSD11[n][m].SKTYMD);			//�����(�����p)
                            if ( Trim(sBufSKTYMD) != "" ) {
		                        sBufSKTYMD.Insert("/",7);
		                        sBufSKTYMD.Insert("/",5);
                            }
                            sCRSF_KSD11_SKTYMD->Strings[n] = sBufSKTYMD;

                            //�f�[�^�ڍו�(sRepData6_3)�o�̓f�[�^�쐬�i�o�͂͌�Łj
	                        //�y�[�W�ԍ�,�f�[�^��ʁi�����ł�2�j�C���b�g�ʒu�C�������ڂ�,
                            //�����,���萔,����l�\��,����l�����_�ȉ�����,����l1,�E�E�E�E
	                        sprintf( cBufFileOut,"%d,2,%d,%d,%d,%s,%d,%d,%d,%s,\n",
                                                    iCRSF_PageNo,n,iPos1,i,CRSF_KSD12[iPos1].SKTYMD,
                                                    CRSF_KSD11[n][m].VALUE_TYPE,
                                                    CRSF_KSD11[n][m].VALUE_DECI,
                                                    CRSF_KSD11[n][m].SOKU_VAL_SU,
                                                    CRSF_KSD11[n][m].WtiteStr);
	                        //sprintf( cBufFileOut,"%d,2,%d,%d,%d,%s,\n",
                            //                        iCRSF_PageNo,n,m,
                            //                        CRSF_KSD11[n][m].SOKU_VAL_SU,CRSF_KSD11[n][m].WtiteStr);
                            sBufFileOut += cBufFileOut;
                            iRDiMax++;
                            if ( iRDjMax < CRSF_KSD11[n][m].SOKU_VAL_SU ) {
                                iRDjMax = CRSF_KSD11[n][m].SOKU_VAL_SU;
                            }

                            //�����
                            if ( sCRSF_KSD11_UPDCHR->Strings[n] == "" ) {
                                sCRSF_KSD11_UPDCHR->Strings[n] = AnsiString(CRSF_KSD11[n][m].UPDCHR);
                            } else {
                                if ( sCRSF_KSD11_UPDCHR->Strings[n] > AnsiString(CRSF_KSD11[n][m].UPDCHR) ) {
                                    sCRSF_KSD11_UPDCHR->Strings[n] = AnsiString(CRSF_KSD11[n][m].UPDCHR);
                                }
                            }
                            iCRSF_KSD11_OUTFLAG[n] = 1;
                         }
                    }
                }
            }

            if ( sBufFileOut != "" ) {
                //�f�[�^�ڍו�(sRepData6_3)�Ƀf�[�^�o��
                //���t�A�����
                for ( a = 0; a < iCRSF_KSD11_Num1; a++ ) {
                    //����҂ͺ��ނœ����Ă���̂Ŏ����ɕϊ�
                    if ( iCRSF_KSD11_OUTFLAG[a] == 1 ) {
                        sBufSKTYMD = "";
                        sBufTANNAM = "";
                        
                        sBufSKTYMD = sCRSF_KSD11_SKTYMD->Strings[a];

                        sBufTANNAM = GetTANNAM(sCRSF_KSD11_UPDCHR->Strings[a]);
                        
                        fprintf( fCRSF_stream3,"%d,1,%d,%d,%s,%s,\n",
                                        iCRSF_PageNo,a,i,
                                        sBufSKTYMD.c_str(),sBufTANNAM.c_str());
                    	iRDiMax++;
                    }
                }

                //����l
                fprintf( fCRSF_stream3,"%s",sBufFileOut.c_str());
                


                //���荀�ڃf�[�^���o��
				fprintf( fCRSF_stream2,"*,3,SKTYMD_B,\n%d,\n",i);
				fprintf( fCRSF_stream2,"*,4,KOMK_NM_B,\n");

				for ( a = 0; a < iCRSF_KSD12_Num; a++ ) {
					fprintf( fCRSF_stream2,"%d,%d,%s,%s,%s,%d,%d,%d,%lf,%lf,%lf,%d,,\n",
									a,
                                    i,
									CRSF_KSD12[a].KOMK_NM,
									CRSF_KSD12[a].KOMK_SUB,
									CRSF_KSD12[a].TANI,
									CRSF_KSD12[a].KIKA_TYPE,
									CRSF_KSD12[a].KIKA_KIND,
									CRSF_KSD12[a].KIKA_DECI,
									CRSF_KSD12[a].KIKA_NUM1,
									CRSF_KSD12[a].KIKA_NUM2,
									CRSF_KSD12[a].KIKA_NUM3,
									CRSF_KSD12[a].KIKA_PRT
									);
					//fprintf( fCRSF_stream2,"%d,%s,%s,%s,%d,%d,%d,%lf,%lf,%lf,%d,%d,%d,%s,\n",
					//				a,
					//				CRSF_KSD12[a].KOMK_NM.c_str(),
					//				CRSF_KSD12[a].KOMK_SUB.c_str(),
					//				CRSF_KSD12[a].TANI.c_str(),
					//				CRSF_KSD12[a].KIKA_TYPE,
					//				CRSF_KSD12[a].KIKA_KIND,
					//				CRSF_KSD12[a].KIKA_DECI,
					//				CRSF_KSD12[a].KIKA_NUM1,
					//				CRSF_KSD12[a].KIKA_NUM2,
					//				CRSF_KSD12[a].KIKA_NUM3,
					//				CRSF_KSD12[a].KIKA_PRT,
					//				CRSF_KSD12[a].VALUE_TYPE,
					//				CRSF_KSD12[a].VALUE_DECI,
					//				CRSF_KSD12[a].SKTYMD.c_str()
					//				);
				}

            }
        //}

        sBufFileOut = "";
    }
}
//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�					�F�S���҃R�[�h����S���Җ����擾���܂�
//
//  �@�\����
//    GetiCRSF_KSD01_Pos5�Ŏg�p���܂��B
//    GetiCRSF_KSD01_Pos6�ESetCRSF_KSD11�Ŏg�p���܂��B
//
//  �p�����^����
//    AnsiString sTANSYA		�F�S���҃R�[�h
//
//  �߂�l
//    AnsiString 				�F�S���Җ�
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::GetTANNAM(AnsiString sTANSYA)
{
	AnsiString sBuf;
	AnsiString sBufTANNAM;

    if ( Trim(sTANSYA) == "" ) {
    	return(" ");
    }
	sBufTANNAM = " ";

	//���[�U�[������
	// Initial Query
	Q_CRSub_TANSYA->Close();
	Q_CRSub_TANSYA->SQL->Clear();

	// �⍇�����s
	sBuf = "SELECT TANSYA, TANNAM, SZKBSY FROM SM12S WHERE  TANSYA = ";
	sBuf += sTANSYA;

	Q_CRSub_TANSYA->SQL->Add(sBuf);
	Q_CRSub_TANSYA->Open();
	Q_CRSub_TANSYA->Active = true;

	if (Q_CRSub_TANSYA->Eof == false ) {
		sBufTANNAM = Null_S(Q_CRSub_TANSYA->FieldValues["TANNAM"]);
	}
	return(sBufTANNAM);


}
//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�					�F�\���̂̏�����
//
//  �@�\����
//    CRSF_KSD11�����������܂��B
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
void __fastcall TForm1::FormatCRSF_KSD11(void)
{
    int i;
    int j;

    for ( i = 0; i < iCRSF_KSD01_MAX; i++ ) {
        for ( j = 0; j < iCRSF_KSD11_MAX; j++ ) {
			strcpy(CRSF_KSD11[i][j].KOMK_NM  	 , "");
			strcpy(CRSF_KSD11[i][j].KOMK_SUB     , "");
			strcpy(CRSF_KSD11[i][j].TANI	 	 , "");
			CRSF_KSD11[i][j].KIKA_TYPE   = 0;
			CRSF_KSD11[i][j].KIKA_KIND	 = 0;
			CRSF_KSD11[i][j].KIKA_DECI	 = 0;
			CRSF_KSD11[i][j].KIKA_NUM1 	 = 0;
			CRSF_KSD11[i][j].KIKA_NUM2 	 = 0;
			CRSF_KSD11[i][j].KIKA_NUM3	 = 0;
			CRSF_KSD11[i][j].KIKA_PRT	 = 0;
			CRSF_KSD11[i][j].VALUE_TYPE	 = 0;
			CRSF_KSD11[i][j].VALUE_DECI	 = 0;
			strcpy(CRSF_KSD11[i][j].SKTYMD 	 , "");
			strcpy(CRSF_KSD11[i][j].UPDCHR 	 , "");
			CRSF_KSD11[i][j].SOKU_VAL_SU = 0;
			strcpy(CRSF_KSD11[i][j].WtiteStr  	 , "");
            CRSF_KSD11[i][j].SKTYMD_ID   = 0;
            CRSF_KSD11[i][j].Write_FLG   = 0;  
            CRSF_KSD11[i][j].KIKI_NO  	 = 0;  //�@��No		//2003.06.10 E.Takase Add
            CRSF_KSD11[i][j].KOMK_NO  	 = 0;  //���荀��No	//2003.06.10 E.Takase Add
        }
    }

}

