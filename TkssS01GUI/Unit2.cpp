//---------------------------------------------------------------------------
//
//  Unit2.cpp
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
//    ����֐�				�F���������o�^
//
//  �@�\����
//    �@�f�ޑ�����уf�[�^�O���荞�ݓ������璆�Ԍ���DB�̌����������쐬
//    �A�@�̏����Œ��Ԍ���DB����f�[�^���擾���o�׌���DB�ֈڍs
//    �B�f�ޑ�����уf�[�^�iKSD21�j�̍X�V�񐔂���ёf�ޔ�����X�V
//
//  �p�����^����
//    �Ȃ�
//
//  �߂�l
//    int					�F�X�V�������Ӑ�i�ԁE���b�g��
//
//  ���l
//    �Ȃ��B
//
/*----------------------------------------------------------------------------*/
int __fastcall TForm1::AutoEntry()
{
	int iRtn;
	AnsiString sRtn;
	int i;
	AnsiString FileName;
	FILE *fp;

	//FixStr������
	FormatFixStr();

	//TStrings������
	//sDTKSHIN	= new TStringList;    	//���Ӑ�i��
	//sLOTNO		= new TStringList; 		//���b�gNO
	sDTKSHIN->Clear();
	sHINBAN->Clear();
	sLOTNO->Clear();
	isDTKSHINNum = 0;

    FileName = Application->ExeName;
    FileName = FileName.SubString(1,FileName.Length()-4);
    FileName = FileName + ".log";
	if( (fp = fopen( FileName.c_str(), "w" )) != NULL ){
		fclose(fp);
	}

	//�f�ޑ�����уf�[�^�O���荞�ݓ����f�[�^�擾
	//iRtn = GetKSD29("1");
   	KSD29.STRWHERE = " WHERE ( ADDYMD >='" + KSD29.UPDYMD + "'" +
						  " OR UPDYMD >='" + KSD29.UPDYMD + "' ) ";


	//�f�ޑ�����і��׃f�[�^�擾(KDX1)
	for ( i = 0; i < FixStrNum; i++ ) {
		iRtn = GetKD_1(i);
	}
	//iRtn = GetKD_1(14);

	//�f�ޑ�����уf�[�^�iKSD21�j�̍X�V�񐔂���ёf�ޔ�����X�V
	for ( i = 0; i < isDTKSHINNum; i++ ) {
		sRtn = UpdDataKSD21_UPDCNT(sDTKSHIN->Strings[i],sLOTNO->Strings[i]);
		WriteErrLog(sRtn,"UpdDataKSD21_UPDCNT",KSD21.DTKSHIN,KSD21.LOTNO);
	}

	return(isDTKSHINNum);
}
/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�f�ޑ�����і��׃f�[�^�擾(KDX1)
//
//  �@�\����
//    �@KDX1����f�[�^���擾���AQ_KD_1�ɃZ�b�g
//    �AQ_KD_1��1�������Ă����AKDS21�EKDS22�EKDS23���������f�[�^�x�[�X�ɓo�^
//
//  �p�����^����
//    int iNo				�F�����Ώۂ̑��荀��ID
//
//  �߂�l
//    int					�F0=�������� -1=�������s
//
//  ���l
//    �Ȃ��B
//
/*----------------------------------------------------------------------------*/
int __fastcall TForm1::GetKD_1(int iNo)
{
	AnsiString sBuf;
	AnsiString sErr;
	int iRtn;
	int iSOKUTEI_SU;
	int iSOKUTEI_SU2;
	AnsiString sSOKUTEI_SU2;
	int i;
	int iSOKU_VAL_SU;
	int iFlag;
	AnsiString sKEIJYO_KBN;
	int iKEIJYO_KBN_OK;
    int LogCnt = 0;

	//KDX1����f�[�^���擾���AQ_KD_1�ɃZ�b�g
	iRtn = SrchKD_1(iNo);
	//�������ʂO���̏ꍇ�͏I��
	if ( iRtn < 0 ) {
		return(-1);
	}

	//Q_KD_1��1�������Ă����AKDS21�EKDS22�EKDS23������
	Q_KD_1->First();
	while( !Q_KD_1->Eof ) {

    	LogCnt++;
        //�t�H�[���� LogCnt��\��
        Lbl_3->Caption = FixStr[iNo].TABLE1 + "����f�[�^�擾�E�o�^��[" + IntToStr(LogCnt) + "]";
        Form1->Refresh();

		//�u���V���E���a�E�u���V�c�E�O�a�̏ꍇ
		//�`��敪�ɂ��A�����𑱍s���邩������
		iKEIJYO_KBN_OK = 0;
		switch (iNo)
		{
			case 1: //�u���V��
			case 3: //�u���V�c
				//�`��敪���R���~�ȊO�̏ꍇ ���s
				sKEIJYO_KBN = GetKEIJYO_KBN();
				if ( sKEIJYO_KBN != "5" ) {
					iKEIJYO_KBN_OK = 0;
				} else {
					iKEIJYO_KBN_OK = 1;
				}
				break;

			case 2: //���a
			case 4: //�O�a
				//�`��敪���R���~�̏ꍇ ���s
				sKEIJYO_KBN = GetKEIJYO_KBN();
				if ( sKEIJYO_KBN == "5" ) {
					iKEIJYO_KBN_OK = 0;
				} else {
					iKEIJYO_KBN_OK = 1;
				}
				break;

			default: //���̑� �������s
				iKEIJYO_KBN_OK = 0;
				break;

		}

		if ( iKEIJYO_KBN_OK == 0 ) {
			//�\���̂ɃZ�b�g
			SetKD_1(iNo);

			//���荀�ڐ����Q�ȏ�̏ꍇ�A��O�e�[�u��������
			iSOKUTEI_SU = KD_1.SOKUTEI_SU.ToIntDef(0);
			if ( iSOKUTEI_SU > 2 ) {
				iRtn = SrchKD_2(iNo);
				if ( iRtn == 0 ) {
					//�\���̂ɃZ�b�g
					SetKD_2(iNo);
				}
			}

			//����ŏ��l�E�ő�l�E����
			CalcKD_1(iNo);

			//�\����KSD21�EKSD22�EKSD23��������
			FormatKSD21(iNo);
			FormatKSD22(iNo);
			FormatKSD23(iNo);

			//���Ӑ�i�ԁA���b�gNo���KSD21������
			KSD21.InsFlag = SrchKSD21(iNo);
			//���Ӑ�i�ԁA���b�gNo���KSD22������
			KSD22.InsFlag = SrchKSD22(iNo);

			//������ѐ���10�ȏ�̏ꍇ�A��O�e�[�u��������
			if ( KSD22.InsFlag >= 0 ) {
				sSOKUTEI_SU2 = Null_S(Q_KSD22->FieldValues["SOKU_VAL_SU"]);
				iSOKUTEI_SU2 = sSOKUTEI_SU2.ToIntDef(0);
				if ( iSOKUTEI_SU2 > 10 ) {
					//���Ӑ�i�ԁA���b�gNo���KSD23������
					KSD23.InsFlag = SrchKSD23(iNo);
					////�\����KSD23�ɃZ�b�g
					//if ( KSD23.InsFlag > 0 ) {
					//	SetKSD23(iNo);
					//}
				}
			}

			//�\����KSD22�ɃZ�b�g
			SetKSD22(iNo);
			//�\����KSD21�ɃZ�b�g
			SetKSD21(iNo);

			//�f�[�^�x�[�X�o�^
			//-KSD22
			if ( KSD22.InsFlag >= 0 ) {
				sErr = UpdDataKSD22();
				WriteErrLog(sErr,"UpdDataKSD22",KSD21.DTKSHIN,KSD21.LOTNO);
			} else {
				sErr = AddDataKSD22();
				WriteErrLog(sErr,"AddDataKSD22",KSD21.DTKSHIN,KSD21.LOTNO);
			}


			//-KSD23
			if ( KSD23.InsFlag >= 0 ) {
				sErr = DelDataKSD23();
				WriteErrLog(sErr,"DelDataKSD23",KSD21.DTKSHIN,KSD21.LOTNO);
			}
			iSOKU_VAL_SU = atoi(KSD22.SOKU_VAL_SU.c_str());
			if ( iSOKU_VAL_SU > 10 ) {
				for ( i = 10; i < iSOKU_VAL_SU; i++ ) {
					sErr = AddDataKSD23(i);
					WriteErrLog(sErr,"AddDataKSD23(" + IntToStr(i) + ")",KSD21.DTKSHIN,KSD21.LOTNO);
				}
			}

			//-KSD21
			if ( KSD21.InsFlag >= 0 ) {
				sErr = UpdDataKSD21();
				WriteErrLog(sErr,"UpdDataKSD21",KSD21.DTKSHIN,KSD21.LOTNO);
			} else {
				sErr = AddDataKSD21();
				WriteErrLog(sErr,"AddDataKSD21",KSD21.DTKSHIN,KSD21.LOTNO);
			}

			//�Ō�ɍX�V�񐔂�ݒ肷�邽�߂̃f�[�^
			iFlag = 0;
			for ( i = 0; i < isDTKSHINNum; i++ ) {
				if ( KSD21.DTKSHIN == sDTKSHIN->Strings[i] &&
					 KSD21.LOTNO   == sLOTNO->Strings[i] ) {
					iFlag = 1;
					break;
				}
			}
			if ( iFlag == 0 ) {
				sDTKSHIN->Add(KSD21.DTKSHIN);
				sLOTNO->Add(KSD21.LOTNO);
				isDTKSHINNum++;
			}
		}

		Q_KD_1->Next();
	}



	 return(0);
}
/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F����l�ő�E�ŏ��E����𔻒f
//
//  �@�\����
//    KD_1��SOKUTEI����ő�E�ŏ��E������擾���܂��B
//
//  �p�����^����
//    int iNo				�F�����Ώۂ̑��荀��ID
//
//  �߂�l
//    �Ȃ�
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::CalcKD_1(int iNo)
{
	int i;
	int iSOKUTEI_SU;
	float fSOKUTEI;
	float fSOKUTE_MAX;
	float fSOKUTE_MIN;
	float fKIKA_NUM1;
	float fKIKA_NUM2;
	int iSOKUTE_OK;
	
	iSOKUTEI_SU = KD_1.SOKUTEI_SU.ToIntDef(0);
	fSOKUTE_MAX = atof(KD_1.SOKUTEI[0].c_str());
	fSOKUTE_MIN = atof(KD_1.SOKUTEI[0].c_str());
	iSOKUTE_OK  = 0;
	KD_1.SOKUTE_MAX = KD_1.SOKUTEI[0];
	KD_1.SOKUTE_MIN = KD_1.SOKUTEI[0];
	
	for ( i = 0; i < iSOKUTEI_SU; i++ ) {
		fSOKUTEI = atof(KD_1.SOKUTEI[i].c_str());
		//�ő�l
		if ( fSOKUTE_MAX < fSOKUTEI ) {
			fSOKUTE_MAX = fSOKUTEI;
			KD_1.SOKUTE_MAX = KD_1.SOKUTEI[i];
		}
		//�ŏ��l
		if ( fSOKUTE_MIN > fSOKUTEI ) {
			fSOKUTE_MIN = fSOKUTEI;
			KD_1.SOKUTE_MIN = KD_1.SOKUTEI[i];
		}
		//����
		if ( iSOKUTE_OK == 0 ) {
			switch (iNo)
			{
				case 6: //��t���x �����K�i
					fKIKA_NUM1 = atof(KD_1.KIKA_NUM1.c_str());
					if ( fKIKA_NUM1 > fSOKUTEI ) {
						iSOKUTE_OK = 1;
					}
					break;

				case 7: //��t��R ����K�i
					fKIKA_NUM1 = atof(KD_1.KIKA_NUM1.c_str());
					if ( fKIKA_NUM1 < fSOKUTEI ) {
						iSOKUTE_OK = 1;
					}
					break;

                //2003.06.03 E.Takase
				case 16: //�q�X�g�O�����i�u���V����Min�EMax�j
				case 17: //�q�X�g�O�����i�u���V����Cp�ECpk�j
                    switch (FixStr[iNo].KIKA_KIND.ToIntDef(1)) {
                    	case 2:
							fKIKA_NUM1 = atof(KD_1.KIKA_NUM1.c_str());
							if ( fKIKA_NUM1 < fSOKUTEI ) { //����K�i
								iSOKUTE_OK = 1;
							}
							break;
                    	case 3:
							fKIKA_NUM1 = atof(KD_1.KIKA_NUM1.c_str());
							if ( fKIKA_NUM1 > fSOKUTEI ) { //�����K�i
								iSOKUTE_OK = 1;
							}
                            break;
						default:
							fKIKA_NUM1 = atof(KD_1.KIKA_NUM1.c_str());
							fKIKA_NUM2 = atof(KD_1.KIKA_NUM2.c_str());
							if ( fKIKA_NUM1 > fSOKUTEI || fSOKUTEI > fKIKA_NUM2) { //�����K�i
								iSOKUTE_OK = 1;
							}
                            break;
					}


					break;

				default: //���̑� �����K�i
					fKIKA_NUM1 = atof(KD_1.KIKA_NUM1.c_str());
					fKIKA_NUM2 = atof(KD_1.KIKA_NUM2.c_str());
					if ( fKIKA_NUM1 > fSOKUTEI || fSOKUTEI > fKIKA_NUM2) {
						iSOKUTE_OK = 1;
					}
					break;

			}
		}
	}

	KD_1.SOKUTE_OK = IntToStr(iSOKUTE_OK);

    //���ϒl�̌v�Z �q�X�g�O�����̂�    //2003.06.03 E.Takase
    if ( iNo == 16 || iNo == 17 ) {
    	KD_1.SOKUTE_AVE =  ( fSOKUTE_MAX + fSOKUTE_MIN ) / 2.0;
    }


}

/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�f�[�^����
//
//  �@�\����
//    KDX1����f�[�^���擾���AQ_KD_1�ɃZ�b�g
//
//  �p�����^����
//    int iNo				�F�����Ώۂ̑��荀��ID
//
//  �߂�l
//    int					�F0=�������� -1=�������s
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
int __fastcall TForm1::SrchKD_1(int iNo)
{
	AnsiString sBuf;

	//Initial Query
	Q_KD_1->Close();
	Q_KD_1->SQL->Clear();

    //2003.06.03 E.Takase
    if ( iNo == 16 || iNo == 17 ) {
		// �⍇�����s
		sBuf = "";
		//SELECT��
		sBuf += " SELECT  ";
		//���ʃt�B�[���h1
		sBuf += " KENSA_YMD, SEQNO, HIST_KIKAK, ";
		sBuf += " DTKSCOD, DTKSHIN, ";
		sBuf += " LOTNO, HINBAN, ZISCOD, ZISNAM, ";
		//�e�f�ތ����ɂ���ĈقȂ�t�B�[���h��
		sBuf += FixStr[iNo].F_SOKUTE_KBN + " As SOKUTE_KBN, ";
		sBuf += FixStr[iNo].F_KIKA_NUM1  + " As KIKA_NUM1, ";
		sBuf += FixStr[iNo].F_KIKA_NUM2  + " As KIKA_NUM2, ";
		sBuf += FixStr[iNo].F_KIKA_SUB1  + " As KIKA_SUB1, ";
		sBuf += FixStr[iNo].F_KIKA_SUB2  + " As KIKA_SUB2, ";
		sBuf += FixStr[iNo].F_KEIJYO_KBN + " As KEIJYO_KBN,";
		sBuf += FixStr[iNo].F_SOKUTEI_1  + " As SOKUTEI_1, ";
		sBuf += FixStr[iNo].F_SOKUTEI_2  + " As SOKUTEI_2, ";
		sBuf += FixStr[iNo].F_SOKUTEI_SU + " As SOKUTEI_SU,";
		sBuf += FixStr[iNo].F_SOKUTEI_NM + " As SOKUTEI_NM,";
		sBuf += FixStr[iNo].F_SOKUTE_AVE + " As SOKUTE_AVE,";
		//���ʃt�B�[���h2
		sBuf += " ADDYMD, ADDTIM, UPDYMD, UPDTIM, ";
		sBuf += " UPDCHR, UPDCNT, MEMO ";
                //20170417 Y.Onishi �H��敪�ǉ�
		sBuf += " , KOJOKBN ";
		//�e�[�u����
		sBuf += " FROM " + FixStr[iNo].TABLE1;
		//WHERE��
		sBuf += KSD29.STRWHERE;
		//- SOKUTE_KBN
	    if ( Trim(FixStr[iNo].W_SOKUTE_KBN) != "" ) {
			sBuf +=  " AND " + FixStr[iNo].W_SOKUTE_KBN;
		}

		//ORDER��
		sBuf += " ORDER BY DTKSHIN, LOTNO, KENSA_YMD,SEQNO " ;
    } else {
		// �⍇�����s
		sBuf = "";
		//SELECT��
		sBuf += " SELECT  ";
		//���ʃt�B�[���h1
		sBuf += " KENSA_YMD, TOLEY_NO, SAMPLE_P, ";
		sBuf += " DTKSCOD, DTKSHIN, ";
		sBuf += " LOTNO, HINBAN, ZISCOD, ZISNAM, ";
		//�e�f�ތ����ɂ���ĈقȂ�t�B�[���h��
		sBuf += FixStr[iNo].F_SOKUTE_KBN + " As SOKUTE_KBN, ";
		sBuf += FixStr[iNo].F_KIKA_NUM1  + " As KIKA_NUM1, ";
		sBuf += FixStr[iNo].F_KIKA_NUM2  + " As KIKA_NUM2, ";
		sBuf += FixStr[iNo].F_KIKA_SUB1  + " As KIKA_SUB1, ";
		sBuf += FixStr[iNo].F_KIKA_SUB2  + " As KIKA_SUB2, ";
		sBuf += FixStr[iNo].F_KEIJYO_KBN + " As KEIJYO_KBN,";
		sBuf += FixStr[iNo].F_SOKUTEI_1  + " As SOKUTEI_1, ";
		sBuf += FixStr[iNo].F_SOKUTEI_2  + " As SOKUTEI_2, ";
		sBuf += FixStr[iNo].F_SOKUTEI_SU + " As SOKUTEI_SU,";
		sBuf += FixStr[iNo].F_SOKUTEI_NM + " As SOKUTEI_NM,";
		sBuf += FixStr[iNo].F_SOKUTE_AVE + " As SOKUTE_AVE,";
		//���ʃt�B�[���h2
		sBuf += " ADDYMD, ADDTIM, UPDYMD, UPDTIM, ";
		sBuf += " UPDCHR, UPDCNT, MEMO ";
                //20170417 Y.Onishi �H��敪�ǉ�
		sBuf += " , KOJOKBN ";
		//�e�[�u����
		sBuf += " FROM " + FixStr[iNo].TABLE1;
		//WHERE��
		sBuf += KSD29.STRWHERE;
		//- SOKUTE_KBN
	    if ( Trim(FixStr[iNo].W_SOKUTE_KBN) != "" ) {
			sBuf +=  " AND " + FixStr[iNo].W_SOKUTE_KBN;
		}

		//ORDER��
		sBuf += " ORDER BY DTKSHIN, LOTNO " ;

    }

	//Test
	sBufSQL = sBuf;

	Q_KD_1->SQL->Add(sBuf);
	Q_KD_1->Open();
	Q_KD_1->Active = true;

	if ( Q_KD_1->Bof && Q_KD_1->Eof ) {
		//�������� �O��
		return(-1);
	}

	return(0);
}
/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�\���̂Ƀf�[�^����
//
//  �@�\����
//    SrchKD_1�ł̌������ʂ��\���́iKD_1�j�ɃZ�b�g
//
//  �p�����^����
//    int iNo				�F�����Ώۂ̑��荀��ID
//
//  �߂�l
//    �Ȃ�
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::SetKD_1(int iNo)
{

	//Q_KD_1���\���̂ɃZ�b�g
	KD_1.KENSA_YMD  = Null_S(Q_KD_1->FieldValues["KENSA_YMD"]);

    //2003.06.03 E.Takase
    if ( iNo == 16 || iNo == 17 ) {
		KD_1.TOLEY_NO   = "";
		KD_1.SAMPLE_P   = "";

        //�K�i  HIST_KIKAK
        if ( iNo == 16 ) {
        	switch ( Null_S(Q_KD_1->FieldValues["HIST_KIKAK"]).ToIntDef(1) ) {
        		case 1: FixStr[iNo].KIKA_KIND = "1";	break;
        		case 2: FixStr[iNo].KIKA_KIND = "3";	break;
        		case 3: FixStr[iNo].KIKA_KIND = "2";	break;
            }
        } else {
        	 FixStr[iNo].KIKA_KIND = "3";
        }

    } else {
		KD_1.TOLEY_NO   = Null_S(Q_KD_1->FieldValues["TOLEY_NO"]);
		KD_1.SAMPLE_P   = Null_S(Q_KD_1->FieldValues["SAMPLE_P"]);
    }

	KD_1.SOKUTEI_SU = Null_S(Q_KD_1->FieldValues["SOKUTEI_SU"]);
	KD_1.DTKSHIN    = Null_S(Q_KD_1->FieldValues["DTKSHIN"]);
	KD_1.LOTNO      = Null_S(Q_KD_1->FieldValues["LOTNO"]);
	KD_1.HINBAN 	= Null_S(Q_KD_1->FieldValues["HINBAN"]);
	KD_1.ZISCOD 	= Null_S(Q_KD_1->FieldValues["ZISCOD"]);
	KD_1.ZISNAM 	= Null_S(Q_KD_1->FieldValues["ZISNAM"]);
	KD_1.KIKA_NUM1 	= Null_S(Q_KD_1->FieldValues["KIKA_NUM1"]);
	KD_1.KIKA_NUM2 	= Null_S(Q_KD_1->FieldValues["KIKA_NUM2"]);
	KD_1.KIKA_SUB1 	= Null_S(Q_KD_1->FieldValues["KIKA_SUB1"]);
	KD_1.KIKA_SUB2 	= Null_S(Q_KD_1->FieldValues["KIKA_SUB2"]);
	KD_1.KEIJYO_KBN = Null_S(Q_KD_1->FieldValues["KEIJYO_KBN"]);
	KD_1.SOKUTEI[0] = Null_S(Q_KD_1->FieldValues["SOKUTEI_1"]);
	KD_1.SOKUTEI[1] = Null_S(Q_KD_1->FieldValues["SOKUTEI_2"]);
	KD_1.SOKUTEI_SU = Null_S(Q_KD_1->FieldValues["SOKUTEI_SU"]);
	KD_1.SOKUTEI_NM = Null_S(Q_KD_1->FieldValues["SOKUTEI_NM"]);
	KD_1.SOKUTE_AVE = Null_S(Q_KD_1->FieldValues["SOKUTE_AVE"]);
	KD_1.ADDYMD 	= Null_S(Q_KD_1->FieldValues["ADDYMD"]);
	KD_1.ADDTIM 	= Null_S(Q_KD_1->FieldValues["ADDTIM"]);
	KD_1.UPDYMD 	= Null_S(Q_KD_1->FieldValues["UPDYMD"]);
	KD_1.UPDTIM 	= Null_S(Q_KD_1->FieldValues["UPDTIM"]);
	KD_1.UPDCHR 	= Null_S(Q_KD_1->FieldValues["UPDCHR"]);
	KD_1.UPDCNT 	= Null_S(Q_KD_1->FieldValues["UPDCNT"]);
	KD_1.MEMO		= Null_S(Q_KD_1->FieldValues["MEMO"]);

    //2003.08.22 E.Takase
	//if ( Trim(KD_1.UPDYMD) == "" ) {
	//	KD_1.SKTYMD = KD_1.ADDYMD;
	//} else {
	//	KD_1.SKTYMD = KD_1.UPDYMD;
	//}
	//KD_1.SKTYMD = KD_1.KENSA_YMD;
    //2004.02.26 E.Takase ������� ADDYMD
    KD_1.SKTYMD = KD_1.ADDYMD;

    //20170417 Y.Onishi �H��敪�ǉ�
    KD_1.KOJOKBN 	= Null_S(Q_KD_1->FieldValues["KOJOKBN"]);

}
/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�f�[�^����
//
//  �@�\����
//    KDX2����f�[�^���擾���AQ_KD_2�ɃZ�b�g
//
//  �p�����^����
//    int iNo				�F�����Ώۂ̑��荀��ID
//
//  �߂�l
//    int					�F0=�������� -1=�������s
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
int __fastcall TForm1::SrchKD_2(int iNo)
{
	AnsiString sBuf;

    //2003.06.03 E.Takase
    if ( iNo == 16 || iNo == 17 ) {
    	return(0);
    }
	//Initial Query
	Q_KD_2->Close();
	Q_KD_2->SQL->Clear();

	// �⍇�����s
	sBuf = "";
	//SELECT��
	sBuf += " SELECT  ";
	//���ʃt�B�[���h1
	sBuf += " KENSA_YMD,TOLEY_NO,SAMPLE_P, " ;
	sBuf += " SOKUTEI_NO, ";
	//�e�f�ތ����ɂ���ĈقȂ�t�B�[���h��
	sBuf += FixStr[iNo].F_SOKUTEICHI  + " As SOKUTEICHI ";
	//�e�[�u����
	sBuf += " FROM " + FixStr[iNo].TABLE2;
	//WHERE��
	sBuf += " WHERE  ";
	sBuf += " KENSA_YMD ='" + KD_1.KENSA_YMD + "' AND ";
	sBuf += " TOLEY_NO ="   + KD_1.TOLEY_NO + " AND ";
	sBuf += " SAMPLE_P ="   + KD_1.SAMPLE_P;
        //20170417 Y.Onishi �H��敪�ǉ�
	sBuf += " AND KOJOKBN ="   + KD_1.KOJOKBN;
	//ORDER��
	sBuf += " ORDER BY SOKUTEI_NO " ;


	Q_KD_2->SQL->Add(sBuf);
	Q_KD_2->Open();
	Q_KD_2->Active = true;

	if ( Q_KD_2->Bof && Q_KD_2->Eof ) {
		//�������� �O��
		return(-1);
	}

	return(0);
}
/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�\���̂Ƀf�[�^����
//
//  �@�\����
//    SrchKD_2�ł̌������ʂ��\���́iKD_2�j�ɃZ�b�g
//
//  �p�����^����
//    int iNo				�F�����Ώۂ̑��荀��ID
//
//  �߂�l
//    �Ȃ�
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::SetKD_2(int iNo)
{
	int i;

    //2003.06.03 E.Takase
    if ( iNo == 16 || iNo == 17 ) {
    	return;
    }

	//Q_KD_2���\���̂ɃZ�b�g
	i = 2;
	Q_KD_2->First();
	while( !Q_KD_2->Eof ) {
		KD_1.SOKUTEI[i] = Null_S(Q_KD_2->FieldValues["SOKUTEICHI"]);
		i++;
		Q_KD_2->Next();
	}


}
/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�f�[�^����
//
//  �@�\����
//    KSD21����f�[�^���擾���AQ_KSD21�ɃZ�b�g
//
//  �p�����^����
//    int iNo				�F�����Ώۂ̑��荀��ID
//
//  �߂�l
//    int					�F0=�������� -1=�������s
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
int __fastcall TForm1::SrchKSD21(int iNo)
{
	AnsiString sBuf;

	//Initial Query
	Q_KSD21->Close();
	Q_KSD21->SQL->Clear();

	// �⍇�����s
	sBuf = "";
	//SELECT��
	sBuf += " SELECT ";
	sBuf += " DTKSHIN, LOTNO, HINBAN, DTKSCOD, ";
	sBuf += " DTKSNAM, ZISNAM, SOKUTEI_NUM, ";
	sBuf += " SOZAI_OK, MEMO, SKTYMD, ";
	sBuf += " ADDYMD, ADDTIM, UPDYMD, UPDTIM, ";
	sBuf += " UPDCHR, UPDCNT ";
	//�e�[�u����
	sBuf += " FROM KSD21 ";
	//WHERE��
	sBuf += " WHERE  ";
	sBuf += " DTKSHIN ='" + KD_1.DTKSHIN + "' AND ";
	sBuf += " HINBAN  ='" + KD_1.HINBAN + "' AND ";
	sBuf += " LOTNO   ='" + KD_1.LOTNO + "' ";


	Q_KSD21->SQL->Add(sBuf);
	Q_KSD21->Open();
	Q_KSD21->Active = true;

	if ( Q_KSD21->Bof && Q_KSD21->Eof ) {
		//�������� �O��
		return(-1);
	}

	return(0);
}
/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�\���̂Ƀf�[�^����
//
//  �@�\����
//    SrchKSD21�ł̌������ʂ��\���́iKSD21�j�ɃZ�b�g
//
//  �p�����^����
//    int iNo				�F�����Ώۂ̑��荀��ID
//
//  �߂�l
//    �Ȃ�
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::SetKSD21(int iNo)
{
	int iRtn;
	int iUPDCHR1;
	int iUPDCHR2;

	if ( KSD21.InsFlag == 0 ) {
		KSD21.DTKSCOD = Null_S(Q_KSD21->FieldValues["DTKSCOD"]);
		KSD21.DTKSNAM = Null_S(Q_KSD21->FieldValues["DTKSNAM"]);
		//KSD21.SOKUTEI_NUM = Null_S(Q_KSD21->FieldValues["SOKUTEI_NUM"]);
		//KSD21.SOZAI_OK = Null_S(Q_KSD21->FieldValues["SOZAI_OK"]);
		KSD21.MEMO = Null_S(Q_KSD21->FieldValues["MEMO"]);
		KSD21.SKTYMD = Null_S(Q_KSD21->FieldValues["SKTYMD"]);
		//KSD21.ADDYMD = Null_S(Q_KSD21->FieldValues["ADDYMD"]);
		//KSD21.ADDTIM = Null_S(Q_KSD21->FieldValues["ADDTIM"]);
		//KSD21.UPDYMD = FormatDateTime("yyyymmdd",Now());// �X�V��
		//KSD21.UPDTIM = FormatDateTime("hhnn",Now());	// �X�V����

		KSD21.SKTYMD = Null_S(Q_KSD21->FieldValues["SKTYMD"]);	//�����
		KSD21.UPDCHR = Null_S(Q_KSD21->FieldValues["UPDCHR"]);	//�X�V��

		////���荀��No�X�V
		//if ( KSD22.InsFlag != 0 ) {
		//	//�V�K�������ڂ̎� ���荀��No���C���N�������g
		//	iBuf = KSD21.SOKUTEI_NUM.ToIntDef(0);
		//	KSD21.SOKUTEI_NUM = IntToStr(iBuf+1);
		//}

		//����o�^����f�[�^�Ɣ�r
		//����� �V�������t�D��
        //2004.02.26 E.Takase Edit
        //��j2/10��2/12�Ȃ� 2/10���̗p
		//if ( Trim(KSD21.SKTYMD) == "" || KSD21.SKTYMD < KD_1.SKTYMD ) {
		if ( Trim(KSD21.SKTYMD) == "" || KSD21.SKTYMD > KD_1.SKTYMD ) {
			KSD21.SKTYMD = KD_1.SKTYMD;
		}
		//�X�V�� �������ق��D��
		iUPDCHR2 = atoi(KD_1.UPDCHR.c_str());
		if ( iUPDCHR2 != 0 ) {
			iUPDCHR1 = atoi(KSD21.UPDCHR.c_str());
			if ( iUPDCHR1 > iUPDCHR2 ) {
				KSD21.UPDCHR = KD_1.UPDCHR;
			}
		}

	} else {
		//�V�K�̏ꍇ ���Ӑ�R�[�h�A���Ӑ於�� �擾
		iRtn = GetDTKS();
		KSD21.SOKUTEI_NUM = "1";
		KSD21.SKTYMD = KD_1.SKTYMD; //�����
		KSD21.UPDCHR = KD_1.UPDCHR; //�X�V��
	}

	////�f�ޔ���X�V
	//if ( KD_1.SOKUTE_OK == "1" ) {
	//	//NG�̏ꍇ 1�ɍX�V
	//	KSD21.SOZAI_OK = "1";
	//}

	//���l
	if ( Trim(KD_1.MEMO) != "" ) {
		KSD21.MEMO = InsMEMO(KSD21.MEMO,iNo,KD_1.MEMO);
	}



}

/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�Ł[������
//
//  �@�\����
//    KSD22����f�[�^���擾���AQ_KSD22�ɃZ�b�g
//
//  �p�����^����
//    int iNo				�F�����Ώۂ̑��荀��ID
//
//  �߂�l
//    int					�F0=�������� -1=�������s
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
int __fastcall TForm1::SrchKSD22(int iNo)
{
	AnsiString sBuf;

	//Initial Query
	Q_KSD22->Close();
	Q_KSD22->SQL->Clear();

	// �⍇�����s
	sBuf = "";
	//SELECT��
	sBuf += " SELECT ";
	sBuf += " DTKSHIN, LOTNO, UNQ_NO, KOMK_NO, KOMK_NM, ";
	sBuf += " KOMK_ENG, KOMK_SUB, KOMK_SUB_ENG, KIKI_NO, ";
	sBuf += " KIKI_NM, TANI, KIKA_TYPE, KIKA_KIND, KIKA_DECI, ";
	sBuf += " KIKA_NUM1, KIKA_NUM2, KIKA_NUM3, KIKA_STR, ";
	sBuf += " KIKA_SUB1, KIKA_SUB2, SOKU_SU, VALUE_TYPE, VALUE_DECI, ";
	sBuf += " SOKU_VAL01, SOKU_VAL02, SOKU_VAL03, SOKU_VAL04, SOKU_VAL05, ";
	sBuf += " SOKU_VAL06, SOKU_VAL07, SOKU_VAL08, SOKU_VAL09, SOKU_VAL10, ";
	sBuf += " SOKU_VAL_SU, SOKU_VAL_AVE, SOKU_VAL_MAX, SOKU_VAL_MIN, SOKU_OK, SKTYMD, ";
	sBuf += " ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT, HINBAN ";
	//�e�[�u����
	sBuf += " FROM KSD22 ";
	//WHERE��
	sBuf += " WHERE  ";
	sBuf += " DTKSHIN ='" + KD_1.DTKSHIN + "' AND ";
	sBuf += " HINBAN  ='" + KD_1.HINBAN + "' AND ";
	sBuf += " LOTNO   ='" + KD_1.LOTNO + "' AND ";
	sBuf += " UNQ_NO =" + FixStr[iNo].KOMK_NO;



	Q_KSD22->SQL->Add(sBuf);
	Q_KSD22->Open();
	Q_KSD22->Active = true;

	if ( Q_KSD22->Bof && Q_KSD22->Eof ) {
		//�������� �O��
		return(-1);
	}

	return(0);
}
/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�\���̂Ƀf�[�^����
//
//  �@�\����
//    SrchKSD22�ł̌������ʂ��\���́iKSD22�j�ɃZ�b�g
//
//  �p�����^����
//    int iNo				�F�����Ώۂ̑��荀��ID
//
//  �߂�l
//    �Ȃ�
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::SetKSD22(int iNo)
{
	AnsiString sBuf;
	int i;
	int iSOKU_VAL_SU;
	int iUPDCNT;

	//���і��׃f�[�^�iKSD22�j���
	if ( KSD22.InsFlag == 0 ) {
		KSD22.ADDYMD = Null_S(Q_KSD22->FieldValues["ADDYMD"]);
		KSD22.ADDTIM = Null_S(Q_KSD22->FieldValues["ADDTIM"]);
		KSD22.UPDYMD = FormatDateTime("yyyymmdd",Now());// �X�V��
		KSD22.UPDTIM = FormatDateTime("hhnn",Now());	// �X�V����
		KSD22.UPDCNT = Null_S(Q_KSD22->FieldValues["UPDCNT"]);

	}
	//�X�V�񐔃C���N�������g
	iUPDCNT = atoi(KSD22.UPDCNT.c_str());
	iUPDCNT++;
	KSD22.UPDCNT = IntToStr(iUPDCNT);

	//�f�ޖ��׃f�[�^�iKDX1�j���
	//�P��
	KSD22.TANI = "";
	switch (iNo)
	{
		case 6: //��t���x
			sBuf = KD_1.KIKA_SUB2;
            switch( sBuf.ToIntDef(1) ){
				case 1:	KSD22.TANI = FixStr[iNo].TANI[0];	break;
                case 2:	KSD22.TANI = FixStr[iNo].TANI[1];	break;
                case 3:	KSD22.TANI = FixStr[iNo].TANI[2];	break;
            }
			break;

		case 7: //��t��R
			KSD22.TANI = FixStr[iNo].TANI[0] + KD_1.KIKA_NUM2 + FixStr[iNo].TANI[1];
			break;

        //2003.07.01 ��R�� �ʃ��cm10A �� �ʃ��cm �ɕύX�ɂȂ���
		//case 8: //��R��
		//	KSD22.TANI = FixStr[iNo].TANI[0] + KD_1.KIKA_SUB1 + FixStr[iNo].TANI[1];
		//	break;

		case 9: //�Ȃ�����
			sBuf = KD_1.KIKA_SUB2;
            switch( sBuf.ToIntDef(1) ){
            	case 1:	KSD22.TANI = FixStr[iNo].TANI[0];	break;
                case 2:	KSD22.TANI = FixStr[iNo].TANI[1];	break;
                case 3:	KSD22.TANI = FixStr[iNo].TANI[2];	break;
				case 4:	KSD22.TANI = FixStr[iNo].TANI[3];	break;
            }
			break;

		case 10: //�Ȃ������i�����j
			sBuf = KD_1.KIKA_SUB2;
            switch( sBuf.ToIntDef(1) ){
            	case 1:	KSD22.TANI = FixStr[iNo].TANI[0];	break;
                case 2:	KSD22.TANI = FixStr[iNo].TANI[1];	break;
                case 3:	KSD22.TANI = FixStr[iNo].TANI[2];	break;
                case 4:	KSD22.TANI = FixStr[iNo].TANI[3];	break;
                //2003/07/22 E.Takase �P�ʒǉ�
                case 5:	KSD22.TANI = FixStr[iNo].TANI[4];	break;
            }
			break;
			
		default: //���̑� �����K�i
			KSD22.TANI = FixStr[iNo].TANI[0];
			break;

	}

	//�K�i�l1�E�K�i�l2
	switch (iNo)
	{
		case 6: //��t���x �����K�i
			KSD22.KIKA_NUM1 = KD_1.KIKA_NUM1;
			break;

		case 7: //��t��R ����K�i
        	//2003.05.29 E.Takase Mod
			//KSD22.KIKA_NUM1 = KD_1.KIKA_NUM1;
			KSD22.KIKA_NUM1 = "0";
			KSD22.KIKA_NUM2 = KD_1.KIKA_NUM1;
			break;

		default: //���̑� �����K�i
			KSD22.KIKA_NUM1 = KD_1.KIKA_NUM1;
			KSD22.KIKA_NUM2 = KD_1.KIKA_NUM2;
			break;

	}

	//�K�i�l�T�u1�E�K�i�l�T�u2
	switch (iNo)
	{
		case 6: //��t���x�i���葬�x�E�P�ʋL���j
			KSD22.KIKA_SUB1 = KD_1.KIKA_SUB1;
			KSD22.KIKA_SUB2 = KD_1.KIKA_SUB2;
			break;

		case 7: //��t��R�i���莞�ԁE����^�C�v�j
			KSD22.KIKA_SUB1 = KD_1.KIKA_SUB1;
			KSD22.KIKA_SUB2 = KD_1.KIKA_SUB2;
			break;

		case 9: //�Ȃ��i�X�p���E�P�ʋL���j
			KSD22.KIKA_SUB1 = KD_1.KIKA_SUB1;
			KSD22.KIKA_SUB2 = KD_1.KIKA_SUB2;
			break;

		case 10: //�Ȃ��i�X�p���E�P�ʋL���j
			KSD22.KIKA_SUB1 = KD_1.KIKA_SUB1;
			KSD22.KIKA_SUB2 = KD_1.KIKA_SUB2;
			break;

	}


	KSD22.SOKU_SU = KD_1.SOKUTEI_NM; 		//����w��n��
	KSD22.SOKU_VAL_SU = KD_1.SOKUTEI_SU;  	//�������n��

	//����l
	iSOKU_VAL_SU = KSD22.SOKU_VAL_SU.ToIntDef(0);
	for ( i = 0; i < iSOKU_VAL_SU; i++ ) {
		KSD22.SOKU_VAL[i] = KD_1.SOKUTEI[i];
	}

	KSD22.SOKU_VAL_AVE = KD_1.SOKUTE_AVE; 	//���蕽�ϒl
	KSD22.SOKU_VAL_MAX = KD_1.SOKUTE_MAX; 	//����ő�l
	KSD22.SOKU_VAL_MIN = KD_1.SOKUTE_MIN; 	//����ŏ��l
	KSD22.SOKU_OK = KD_1.SOKUTE_OK;       	//����l����
	KSD22.SKTYMD = KD_1.SKTYMD;           	//�����
	KSD22.UPDCHR = KD_1.UPDCHR;           	//�X�V��


}

/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�f�[�^����
//
//  �@�\����
//    KSD22����f�[�^���擾���AQ_KSD22�ɃZ�b�g
//
//  �p�����^����
//    int iNo				�F�����Ώۂ̑��荀��ID
//
//  �߂�l
//    int					�F0=�������� -1=�������s
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
int __fastcall TForm1::SrchKSD23(int iNo)
{
	AnsiString sBuf;

	//Initial Query
	Q_KSD23->Close();
	Q_KSD23->SQL->Clear();

	// �⍇�����s
	sBuf = "";
	//SELECT��
	sBuf += " SELECT ";
	sBuf += " DTKSHIN, LOTNO, UNQ_NO, SOKU_NO, SOKU_VAL, HINBAN ";
	//�e�[�u����
	sBuf += " FROM KSD23 ";
	//WHERE��
	sBuf += " WHERE  ";
	sBuf += " DTKSHIN ='" + KD_1.DTKSHIN + "' AND ";
	sBuf += " HINBAN  ='" + KD_1.HINBAN + "' AND ";
	sBuf += " LOTNO   ='" + KD_1.LOTNO + "' AND ";
	sBuf += " UNQ_NO =" + FixStr[iNo].KOMK_NO;



	Q_KSD23->SQL->Add(sBuf);
	Q_KSD23->Open();
	Q_KSD23->Active = true;

	if ( Q_KSD23->Bof && Q_KSD23->Eof ) {
		//�������� �O��
		return(-1);
	}

	return(0);
}

/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�\���̂̏�����
//
//  �@�\����
//    KSD21�����������������܂��B
//
//  �p�����^����
//    int iNo				�F�����Ώۂ̑��荀��ID
//
//  �߂�l
//    �Ȃ�
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::FormatKSD21(int iNo)
{

	KSD21.InsFlag 		= -1; 								// �V�K�̏ꍇ�F-1
	KSD21.DTKSHIN 		= KD_1.DTKSHIN;						// ���Ӑ�i��
	KSD21.LOTNO   		= KD_1.LOTNO; 						// ���b�gNO
	KSD21.HINBAN		= KD_1.HINBAN; 						// ���Еi��
	KSD21.DTKSCOD 		= " "; 								// ���Ӑ�R�[�h
	KSD21.DTKSNAM 		= " "; 								// ���Ӑ於��
	KSD21.ZISNAM 		= KD_1.ZISNAM; 						// �ގ����́i�i��j
	KSD21.SOKUTEI_NUM 	= "0"; 								// ���荀�ڐ�
	KSD21.SOZAI_OK 		= "0"; 								// �f�ޔ���
	KSD21.MEMO 			= " "; 								// ���l
	KSD21.SKTYMD		= " "; 								// �����
	KSD21.ADDYMD 		= FormatDateTime("yyyymmdd",Now());	// �o�^��
	KSD21.ADDTIM 		= FormatDateTime("hhnn",Now());		// �o�^����
	KSD21.UPDYMD 		= " "; 								// �ύX��
	KSD21.UPDTIM 		= " "; 								// �ύX����
	KSD21.UPDCHR 		= "0"; 								// �X�V��
	KSD21.UPDCNT 		= "0"; 								// �X�V��

}
/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�\���̂̏�����
//
//  �@�\����
//    KSD22�����������������܂��B
//
//  �p�����^����
//    int iNo				�F�����Ώۂ̑��荀��ID
//
//  �߂�l
//    �Ȃ�
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::FormatKSD22(int iNo)
{
	int i;

	//�f�ޑ�����і��׃f�[�^
	KSD22.InsFlag 		= -1; 							// �V�K�̏ꍇ�F-1
	KSD22.DTKSHIN 		= KD_1.DTKSHIN; 				// ���Ӑ�i��
	KSD22.LOTNO 		= KD_1.LOTNO; 					// ���b�gNO
	KSD22.HINBAN 		= KD_1.HINBAN; 					// ���Еi��
	KSD22.UNQ_NO 		= FixStr[iNo].KOMK_NO; 			// ����NO
	KSD22.KOMK_NO 		= FixStr[iNo].KOMK_NO; 			// ���荀��NO
	KSD22.KOMK_NM 		= FixStr[iNo].KOMK_NM; 			// ���荀�ږ���
	KSD22.KOMK_ENG 		= FixStr[iNo].KOMK_ENG; 		// ���荀�ږ��́i�p��j
	KSD22.KOMK_SUB 		= ""; 							// ���荀�ڃT�u����
	KSD22.KOMK_SUB_ENG 	= ""; 							// ���荀�ڃT�u���́i�p��j
	KSD22.KIKI_NO 		= FixStr[iNo].KIKI_NO; 			// ����@��NO
	KSD22.KIKI_NM 		= FixStr[iNo].KIKI_NM; 			// ����@�햼��
	KSD22.TANI 			= ""; 							// �P��
	KSD22.KIKA_TYPE 	= FixStr[iNo].KIKA_TYPE; 		// �K�i�^�C�v
	KSD22.KIKA_KIND 	= FixStr[iNo].KIKA_KIND; 		// �K�i���
	KSD22.KIKA_DECI 	= FixStr[iNo].KIKA_DECI; 		// �K�i�����_�ȉ�����
	KSD22.KIKA_NUM1 	= "0"; 							// �K�i�l1
	KSD22.KIKA_NUM2 	= "0"; 							// �K�i�l2
	KSD22.KIKA_NUM3 	= FixStr[iNo].KIKA_NUM3; 		// �K�i�l3
	KSD22.KIKA_STR 		= FixStr[iNo].KIKA_STR; 		// �K�i�l����
	KSD22.KIKA_SUB1 	= ""; 							// �K�i�l�T�u1
	KSD22.KIKA_SUB2 	= ""; 							// �K�i�l�T�u2
	KSD22.SOKU_SU 		= "0"; 							// ����w��n��
	KSD22.VALUE_TYPE 	= FixStr[iNo].VALUE_TYPE; 		// ����l�\��
	KSD22.VALUE_DECI 	= FixStr[iNo].VALUE_DECI; 		// ����l�����_�ȉ�����

	for ( i = 0; i < 100; i++ ) {
		KSD22.SOKU_VAL[i] = ""; 						// ����l
	}
	KSD22.SOKU_VAL_SU 	= "0";							// �������n��
	KSD22.SOKU_VAL_AVE 	= "0"; 							// ���蕽�ϒl
	KSD22.SOKU_VAL_MAX 	= "0"; 							// ����ő�l
	KSD22.SOKU_VAL_MIN 	= "0";							// ����ŏ��l
	KSD22.SOKU_OK 		= "0"; 							// ����l����
	KSD22.SKTYMD 		= ""; 							// �����
	KSD22.ADDYMD 		= FormatDateTime("yyyymmdd",Now());// �o�^��
	KSD22.ADDTIM 		= FormatDateTime("hhnn",Now());	// �o�^����
	KSD22.UPDYMD 		= ""; 							// �ύX��
	KSD22.UPDTIM 		= ""; 							// �ύX����
	KSD22.UPDCHR 		= "0"; 							// �X�V��
	KSD22.UPDCNT 		= "0"; 							// �X�V��

}
/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�\���̂̏�����
//
//  �@�\����
//    KSD23�����������������܂��B
//
//  �p�����^����
//    int iNo				�F�����Ώۂ̑��荀��ID
//
//  �߂�l
//    �Ȃ�
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::FormatKSD23(int iNo)
{
	KSD23.InsFlag = -1; 					// �V�K�̏ꍇ�F-1
}
/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�\���̂̏�����
//
//  �@�\����
//    FixStr�����������������܂��B
//
//  �p�����^����
//    int iNo				�F�����Ώۂ̑��荀��ID
//
//  �߂�l
//    �Ȃ�
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::FormatFixStr(void)
{

	//FixStrNum = 16;
	FixStrNum = 18;

	//�t�B�[���h��
	//���[�h������
	FixStr[0].F_SOKUTE_KBN = "SOKUTE_KBN";
	FixStr[0].F_KIKA_NUM1 = "LD_LNG_MIN";
	FixStr[0].F_KIKA_NUM2 = "LD_LNG_MAX";
	FixStr[0].F_KIKA_SUB1 = "' '";
	FixStr[0].F_KIKA_SUB2 = "' '";
	FixStr[0].F_KEIJYO_KBN = "' '";
	FixStr[0].F_SOKUTEI_1 = "SOKUTEI_1";
	FixStr[0].F_SOKUTEI_2 = "SOKUTEI_2";
	FixStr[0].F_SOKUTEI_SU = "SOKUTEI_SU";
	FixStr[0].F_SOKUTEI_NM = "SOKUTEI_NM";
	FixStr[0].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[0].F_SOKUTEICHI = "SOKUTEICHI";
	FixStr[0].W_SOKUTE_KBN = " (SOKUTE_KBN = 1) ";

	//�u���V��
	FixStr[1].F_SOKUTE_KBN = "SOKUTE_KBN";
	FixStr[1].F_KIKA_NUM1 = "BURASI_MIN";
	FixStr[1].F_KIKA_NUM2 = "BURASI_MAX";
	FixStr[1].F_KIKA_SUB1 = "' '";
	FixStr[1].F_KIKA_SUB2 = "' '";
	FixStr[1].F_KEIJYO_KBN = "' '";
	FixStr[1].F_SOKUTEI_1 = "SOKUTEI_1";
	FixStr[1].F_SOKUTEI_2 = "SOKUTEI_2";
	FixStr[1].F_SOKUTEI_SU = "SOKUTEI_SU";
	FixStr[1].F_SOKUTEI_NM = "SOKUTEI_NM";
	FixStr[1].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[1].F_SOKUTEICHI = "SOKUTEICHI";
	FixStr[1].W_SOKUTE_KBN = " (SOKUTE_KBN = 1) ";

	//���a
	FixStr[2].F_SOKUTE_KBN = "SOKUTE_KBN";
	FixStr[2].F_KIKA_NUM1 = "BURASI_MIN";
	FixStr[2].F_KIKA_NUM2 = "BURASI_MAX";
	FixStr[2].F_KIKA_SUB1 = "' '";
	FixStr[2].F_KIKA_SUB2 = "' '";
	FixStr[2].F_KEIJYO_KBN = "' '";
	FixStr[2].F_SOKUTEI_1 = "SOKUTEI_1";
	FixStr[2].F_SOKUTEI_2 = "SOKUTEI_2";
	FixStr[2].F_SOKUTEI_SU = "SOKUTEI_SU";
	FixStr[2].F_SOKUTEI_NM = "SOKUTEI_NM";
	FixStr[2].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[2].F_SOKUTEICHI = "SOKUTEICHI";
	FixStr[2].W_SOKUTE_KBN = " (SOKUTE_KBN = 1) ";

	//�u���V�� (�c����)
	FixStr[3].F_SOKUTE_KBN = "SOKUTE_KBN";
	FixStr[3].F_KIKA_NUM1 = "BURASIT_MIN";
	FixStr[3].F_KIKA_NUM2 = "BURASIT_MAX";
	FixStr[3].F_KIKA_SUB1 = "' '";
	FixStr[3].F_KIKA_SUB2 = "' '";
	FixStr[3].F_KEIJYO_KBN = "' '";
	FixStr[3].F_SOKUTEI_1 = "SOKUTEI_1";
	FixStr[3].F_SOKUTEI_2 = "SOKUTEI_2";
	FixStr[3].F_SOKUTEI_SU = "SOKUTEI_SU";
	FixStr[3].F_SOKUTEI_NM = "SOKUTEI_NM";
	FixStr[3].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[3].F_SOKUTEICHI = "SOKUTEICHI";
	FixStr[3].W_SOKUTE_KBN = " (SOKUTE_KBN = 1) ";

	//�O�a
	FixStr[4].F_SOKUTE_KBN = "SOKUTE_KBN";
	FixStr[4].F_KIKA_NUM1 = "BURASIT_MIN";
	FixStr[4].F_KIKA_NUM2 = "BURASIT_MAX";
	FixStr[4].F_KIKA_SUB1 = "' '";
	FixStr[4].F_KIKA_SUB2 = "' '";
	FixStr[4].F_KEIJYO_KBN = "' '";
	FixStr[4].F_SOKUTEI_1 = "SOKUTEI_1";
	FixStr[4].F_SOKUTEI_2 = "SOKUTEI_2";
	FixStr[4].F_SOKUTEI_SU = "SOKUTEI_SU";
	FixStr[4].F_SOKUTEI_NM = "SOKUTEI_NM";
	FixStr[4].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[4].F_SOKUTEICHI = "SOKUTEICHI";
	FixStr[4].W_SOKUTE_KBN = " (SOKUTE_KBN = 1) ";

	//���|��d
	FixStr[5].F_SOKUTE_KBN = "SOKUTE_KBN";
	FixStr[5].F_KIKA_NUM1 = "BOTAI_MIN";
	FixStr[5].F_KIKA_NUM2 = "BOTAI_MAX";
	FixStr[5].F_KIKA_SUB1 = "' '";
	FixStr[5].F_KIKA_SUB2 = "' '";
	FixStr[5].F_KEIJYO_KBN = "KEIJYO_KBN";
	FixStr[5].F_SOKUTEI_1 = "SOKUTEI_1B";
	FixStr[5].F_SOKUTEI_2 = "SOKUTEI_2B";
	FixStr[5].F_SOKUTEI_SU = "SOKUTEI_SU";
	FixStr[5].F_SOKUTEI_NM = "SOKUTEI_NM";
	FixStr[5].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[5].F_SOKUTEICHI = "SOKUTEI_B";
	FixStr[5].W_SOKUTE_KBN = " (SOKUTE_KBN = 1) ";

	//���[�h����t���x
	FixStr[6].F_SOKUTE_KBN = "SOKUTE_KBN";
	FixStr[6].F_KIKA_NUM1 = "LD_HP_MIN";
	FixStr[6].F_KIKA_NUM2 = "' '";
	FixStr[6].F_KIKA_SUB1 = "LD_HP_SPD";
	FixStr[6].F_KIKA_SUB2 = "LD_HP_TAN";
	FixStr[6].F_KEIJYO_KBN = "' '";
	FixStr[6].F_SOKUTEI_1 = "SOKUTEI_1";
	FixStr[6].F_SOKUTEI_2 = "SOKUTEI_2";
	FixStr[6].F_SOKUTEI_SU = "SOKUTEI_SU";
	FixStr[6].F_SOKUTEI_NM = "SOKUTEI_NM";
	FixStr[6].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[6].F_SOKUTEICHI = "SOKUTEICHI";
	FixStr[6].W_SOKUTE_KBN = " (SOKUTE_KBN = 1) ";

	//���[�h����t��R
	FixStr[7].F_SOKUTE_KBN = "SOKUTE_KBN";
	FixStr[7].F_KIKA_NUM1 = "LD_TR_MAX";
	FixStr[7].F_KIKA_NUM2 = "LD_TR_DEN";
	FixStr[7].F_KIKA_SUB1 = "LD_TR_TIME";
	FixStr[7].F_KIKA_SUB2 = "LD_TR_TYPE";
	FixStr[7].F_KEIJYO_KBN = "' '";
	FixStr[7].F_SOKUTEI_1 = "SOKUTEI_1";
	FixStr[7].F_SOKUTEI_2 = "SOKUTEI_2";
	FixStr[7].F_SOKUTEI_SU = "SOKUTEI_SU";
	FixStr[7].F_SOKUTEI_NM = "SOKUTEI_NM";
	FixStr[7].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[7].F_SOKUTEICHI = "SOKUTEICHI";
	FixStr[7].W_SOKUTE_KBN = " (SOKUTE_KBN = 1) ";

	//��R��
	FixStr[8].F_SOKUTE_KBN = "SOKUTE_KBN";
	FixStr[8].F_KIKA_NUM1 = "KOYU_MIN";
	FixStr[8].F_KIKA_NUM2 = "KOYU_MAX";
	FixStr[8].F_KIKA_SUB1 = "KOYU_DEN";
	FixStr[8].F_KIKA_SUB2 = "' '";
	FixStr[8].F_KEIJYO_KBN = "KEIJYO_KBN";
	FixStr[8].F_SOKUTEI_1 = "SOKUTEI_1T";
	FixStr[8].F_SOKUTEI_2 = "SOKUTEI_2T";
	FixStr[8].F_SOKUTEI_SU = "SOKUTEI_SU";
	FixStr[8].F_SOKUTEI_NM = "SOKUTEI_NM";
	FixStr[8].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[8].F_SOKUTEICHI = "SOKUTEI_T";
	FixStr[8].W_SOKUTE_KBN = " (SOKUTE_KBN = 1) ";

	//�Ȃ�����
	FixStr[9].F_SOKUTE_KBN = "SOKUTE_KBN";
	FixStr[9].F_KIKA_NUM1 = "MAGE_MIN";
	FixStr[9].F_KIKA_NUM2 = "MAGE_MAX";
	FixStr[9].F_KIKA_SUB1 = "MAGE_SPAN";
	FixStr[9].F_KIKA_SUB2 = "MAGE_TAN";
	FixStr[9].F_KEIJYO_KBN = "KEIJYO_KBN";
	FixStr[9].F_SOKUTEI_1 = "SOKUTEI_1M";
	FixStr[9].F_SOKUTEI_2 = "SOKUTEI_2M";
	FixStr[9].F_SOKUTEI_SU = "SOKUTEI_SU";
	FixStr[9].F_SOKUTEI_NM = "SOKUTEI_NM";
	FixStr[9].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[9].F_SOKUTEICHI = "SOKUTEI_M";
	FixStr[9].W_SOKUTE_KBN = " (SOKUTE_KBN = 1) ";

	//�Ȃ������i�����j
	FixStr[10].F_SOKUTE_KBN = "SOKUTE_KBN";
	FixStr[10].F_KIKA_NUM1 = "MAGEG_MIN";
	FixStr[10].F_KIKA_NUM2 = "MAGEG_MAX";
	FixStr[10].F_KIKA_SUB1 = "MAGEG_SPAN";
	FixStr[10].F_KIKA_SUB2 = "MAGEG_TAN";
	FixStr[10].F_KEIJYO_KBN = "KEIJYO_KBN";
	FixStr[10].F_SOKUTEI_1 = "SOKUTEI_1M";
	FixStr[10].F_SOKUTEI_2 = "SOKUTEI_2M";
	FixStr[10].F_SOKUTEI_SU = "SOKUTEI_SU";
	FixStr[10].F_SOKUTEI_NM = "SOKUTEI_NM";
	FixStr[10].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[10].F_SOKUTEICHI = "SOKUTEI_M";
	FixStr[10].W_SOKUTE_KBN = " (SOKUTE_KBN = 1) ";

	//�d�x�g���b�i���ʁj
	FixStr[11].F_SOKUTE_KBN = "SOKUTE_KBN1";
	FixStr[11].F_KIKA_NUM1 = "HSC_A_MIN";
	FixStr[11].F_KIKA_NUM2 = "HSC_A_MAX";
	FixStr[11].F_KIKA_SUB1 = "' '";
	FixStr[11].F_KIKA_SUB2 = "' '";
	FixStr[11].F_KEIJYO_KBN = "' '";
	FixStr[11].F_SOKUTEI_1 = "HSC_A_1";
	FixStr[11].F_SOKUTEI_2 = "HSC_A_2";
	FixStr[11].F_SOKUTEI_SU = "HSC_SK_SU";
	FixStr[11].F_SOKUTEI_NM = "HSC_SK_NUM";
	FixStr[11].F_SOKUTE_AVE = "HSC_A_AVE";
	FixStr[11].F_SOKUTEICHI = "HSC_A";
	FixStr[11].W_SOKUTE_KBN = " ( SOKUTE_KBN1 = 1 OR SOKUTE_KBN1 = 3 ) ";

	//�d�x�g���b�i���ʁj
	FixStr[12].F_SOKUTE_KBN = "SOKUTE_KBN1";
	FixStr[12].F_KIKA_NUM1 = "HSC_S_MIN";
	FixStr[12].F_KIKA_NUM2 = "HSC_S_MAX";
	FixStr[12].F_KIKA_SUB1 = "' '";
	FixStr[12].F_KIKA_SUB2 = "' '";
	FixStr[12].F_KEIJYO_KBN = "' '";
	FixStr[12].F_SOKUTEI_1 = "HSC_S_1";
	FixStr[12].F_SOKUTEI_2 = "HSC_S_2";
	FixStr[12].F_SOKUTEI_SU = "HSC_SK_SU";
	FixStr[12].F_SOKUTEI_NM = "HSC_SK_NUM";
	FixStr[12].F_SOKUTE_AVE = "HSC_S_AVE";
	FixStr[12].F_SOKUTEICHI = "HSC_S";
	FixStr[12].W_SOKUTE_KBN = " ( SOKUTE_KBN1 = 2 OR SOKUTE_KBN1 = 3 ) ";

	//�d�x (HsD ����)
	FixStr[13].F_SOKUTE_KBN = "SOKUTE_KBN2";
	FixStr[13].F_KIKA_NUM1 = "HSD_A_MIN";
	FixStr[13].F_KIKA_NUM2 = "HSD_A_MAX";
	FixStr[13].F_KIKA_SUB1 = "' '";
	FixStr[13].F_KIKA_SUB2 = "' '";
	FixStr[13].F_KEIJYO_KBN = "' '";
	FixStr[13].F_SOKUTEI_1 = "HSD_A_1";
	FixStr[13].F_SOKUTEI_2 = "HSD_A_2";
	FixStr[13].F_SOKUTEI_SU = "HSD_SK_SU";
	FixStr[13].F_SOKUTEI_NM = "HSD_SK_NUM";
	FixStr[13].F_SOKUTE_AVE = "HSD_A_AVE";
	FixStr[13].F_SOKUTEICHI = "HSD_A";
	FixStr[13].W_SOKUTE_KBN = " ( SOKUTE_KBN2 = 1 OR SOKUTE_KBN2 = 3 ) ";

	//�d�x (HsD ����)
	FixStr[14].F_SOKUTE_KBN = "SOKUTE_KBN2";
	FixStr[14].F_KIKA_NUM1 = "HSD_S_MIN";
	FixStr[14].F_KIKA_NUM2 = "HSD_S_MAX";
	FixStr[14].F_KIKA_SUB1 = "' '";
	FixStr[14].F_KIKA_SUB2 = "' '";
	FixStr[14].F_KEIJYO_KBN = "' '";
	FixStr[14].F_SOKUTEI_1 = "HSD_S_1";
	FixStr[14].F_SOKUTEI_2 = "HSD_S_2";
	FixStr[14].F_SOKUTEI_SU = "HSD_SK_SU";
	FixStr[14].F_SOKUTEI_NM = "HSD_SK_NUM";
	FixStr[14].F_SOKUTE_AVE = "HSD_S_AVE";
	FixStr[14].F_SOKUTEICHI = "HSD_S";
	FixStr[14].W_SOKUTE_KBN = " ( SOKUTE_KBN2 = 2 OR SOKUTE_KBN2 = 3 ) ";

	//����
	FixStr[15].F_SOKUTE_KBN = "SOKUTE_KBN";
	FixStr[15].F_KIKA_NUM1 = "ZAKUT_MIN";
	FixStr[15].F_KIKA_NUM2 = "ZAKUT_MAX";
	FixStr[15].F_KIKA_SUB1 = "' '";
	FixStr[15].F_KIKA_SUB2 = "' '";
	FixStr[15].F_KEIJYO_KBN = "' '";
	FixStr[15].F_SOKUTEI_1 = "SOKUTEI_1";
	FixStr[15].F_SOKUTEI_2 = "SOKUTEI_2";
	FixStr[15].F_SOKUTEI_SU = "SOKUTEI_SU";
	FixStr[15].F_SOKUTEI_NM = "SOKUTEI_NM";
	FixStr[15].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[15].F_SOKUTEICHI = "SOKUTEICHI";
	FixStr[15].W_SOKUTE_KBN = " SOKUTE_KBN = 1 ";

	//�q�X�g�O����(�u���V����Min�EMax)
	FixStr[16].F_SOKUTE_KBN = "' '";
	FixStr[16].F_KIKA_NUM1 = "HIST_MIN";
	FixStr[16].F_KIKA_NUM2 = "HIST_MAX";
	FixStr[16].F_KIKA_SUB1 = "' '";
	FixStr[16].F_KIKA_SUB2 = "' '";
	FixStr[16].F_KEIJYO_KBN = "' '";
	FixStr[16].F_SOKUTEI_1 = "SOKUTE_MIN";
	FixStr[16].F_SOKUTEI_2 = "SOKUTE_MAX";
	FixStr[16].F_SOKUTEI_SU = "'2'";
	FixStr[16].F_SOKUTEI_NM = "'2'";
	FixStr[16].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[16].F_SOKUTEICHI = "' '";
	FixStr[16].W_SOKUTE_KBN = "";
	FixStr[16].W_SOKUTE_KBN = "";

	//�q�X�g�O����(�u���V����Cp�ECpk)
	FixStr[17].F_SOKUTE_KBN = "' '";
	FixStr[17].F_KIKA_NUM1 = "'1.33'";
	FixStr[17].F_KIKA_NUM2 = "'0'";
	FixStr[17].F_KIKA_SUB1 = "' '";
	FixStr[17].F_KIKA_SUB2 = "' '";
	FixStr[17].F_KEIJYO_KBN = "' '";
	FixStr[17].F_SOKUTEI_1 = "SOKUTE_CP";
	FixStr[17].F_SOKUTEI_2 = "SOKUTE_CPK";
	FixStr[17].F_SOKUTEI_SU = "'2'";
	FixStr[17].F_SOKUTEI_NM = "'2'";
	FixStr[17].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[17].F_SOKUTEICHI = "' '";
	FixStr[17].W_SOKUTE_KBN = "";

	//*********************************************************
	//�Œ蕶����
	//���[�h������
	FixStr[0].TABLE1 = "KD01";
	FixStr[0].TABLE2 = "KD02";
	FixStr[0].KOMK_NO = "1";
	FixStr[0].ORDER_NO = "11";
	FixStr[0].KOMK_NM = "���[�h������";
	FixStr[0].KOMK_ENG = "L/W Length";
	FixStr[0].KIKI_NO = "2";
	FixStr[0].KIKI_NM = "�m�M�X";
	FixStr[0].TANI[0] = "mm";
	FixStr[0].TANI[1] = "";
	FixStr[0].TANI[2] = "";
	FixStr[0].TANI[3] = "";
	FixStr[0].KIKA_TYPE = "1";
	FixStr[0].KIKA_KIND = "1";
	FixStr[0].KIKA_DECI = "2";
	FixStr[0].KIKA_NUM2 = "";
	FixStr[0].KIKA_NUM3 = "0";
	FixStr[0].KIKA_STR = "";
	FixStr[0].SOKU_FLG = "1";
	FixStr[0].TOKU_FLG = "0";
	FixStr[0].KIKA_PRT = "1";
	FixStr[0].VALUE_TYPE = "0";
	FixStr[0].VALUE_DECI = "2";

	//�u���V��
	FixStr[1].TABLE1 = "KD11";
	FixStr[1].TABLE2 = "KD12";
	FixStr[1].KOMK_NO = "2";
	FixStr[1].ORDER_NO = "12";
	FixStr[1].KOMK_NM = "�u���V��";
	FixStr[1].KOMK_ENG = "Brush Width";
	FixStr[1].KIKI_NO = "1";
	FixStr[1].KIKI_NM = "�}�C�N�����[�^";
	FixStr[1].TANI[0] = "mm";
	FixStr[1].TANI[1] = "";
	FixStr[1].TANI[2] = "";
	FixStr[1].TANI[3] = "";
	FixStr[1].KIKA_TYPE = "1";
	FixStr[1].KIKA_KIND = "1";
	FixStr[1].KIKA_DECI = "3";
	FixStr[1].KIKA_NUM2 = "";
	FixStr[1].KIKA_NUM3 = "0";
	FixStr[1].KIKA_STR = "";
	FixStr[1].SOKU_FLG = "1";
	FixStr[1].TOKU_FLG = "0";
	FixStr[1].KIKA_PRT = "1";
	FixStr[1].VALUE_TYPE = "0";
	FixStr[1].VALUE_DECI = "3";

	//���a
	FixStr[2].TABLE1 = "KD11";
	FixStr[2].TABLE2 = "KD12";
	FixStr[2].KOMK_NO = "3";
	FixStr[2].ORDER_NO = "14";
	FixStr[2].KOMK_NM = "���a";
	FixStr[2].KOMK_ENG = "";
	FixStr[2].KIKI_NO = "1";
	FixStr[2].KIKI_NM = "�}�C�N�����[�^";
	FixStr[2].TANI[0] = "mm";
	FixStr[2].TANI[1] = "";
	FixStr[2].TANI[2] = "";
	FixStr[2].TANI[3] = "";
	FixStr[2].KIKA_TYPE = "1";
	FixStr[2].KIKA_KIND = "1";
	FixStr[2].KIKA_DECI = "3";
	FixStr[2].KIKA_NUM2 = "";
	FixStr[2].KIKA_NUM3 = "0";
	FixStr[2].KIKA_STR = "";
	FixStr[2].SOKU_FLG = "1";
	FixStr[2].TOKU_FLG = "0";
	FixStr[2].KIKA_PRT = "1";
	FixStr[2].VALUE_TYPE = "0";
	FixStr[2].VALUE_DECI = "3";

	//�u���V�� (�c����)
	FixStr[3].TABLE1 = "KD21";
	FixStr[3].TABLE2 = "KD22";
	FixStr[3].KOMK_NO = "4";
	FixStr[3].ORDER_NO = "13";
	FixStr[3].KOMK_NM = "�u���V�� (�c����)";
	FixStr[3].KOMK_ENG = "Brush Width A";
	FixStr[3].KIKI_NO = "1";
	FixStr[3].KIKI_NM = "�}�C�N�����[�^";
	FixStr[3].TANI[0] = "mm";
	FixStr[3].TANI[1] = "";
	FixStr[3].TANI[2] = "";
	FixStr[3].TANI[3] = "";
	FixStr[3].KIKA_TYPE = "1";
	FixStr[3].KIKA_KIND = "1";
	FixStr[3].KIKA_DECI = "3";
	FixStr[3].KIKA_NUM2 = "";
	FixStr[3].KIKA_NUM3 = "0";
	FixStr[3].KIKA_STR = "";
	FixStr[3].SOKU_FLG = "1";
	FixStr[3].TOKU_FLG = "0";
	FixStr[3].KIKA_PRT = "1";
	FixStr[3].VALUE_TYPE = "0";
	FixStr[3].VALUE_DECI = "3";

	//�O�a
	FixStr[4].TABLE1 = "KD21";
	FixStr[4].TABLE2 = "KD22";
	FixStr[4].KOMK_NO = "5";
	FixStr[4].ORDER_NO = "15";
	FixStr[4].KOMK_NM = "�O�a";
	FixStr[4].KOMK_ENG = "";
	FixStr[4].KIKI_NO = "1";
	FixStr[4].KIKI_NM = "�}�C�N�����[�^";
	FixStr[4].TANI[0] = "mm";
	FixStr[4].TANI[1] = "";
	FixStr[4].TANI[2] = "";
	FixStr[4].TANI[3] = "";
	FixStr[4].KIKA_TYPE = "1";
	FixStr[4].KIKA_KIND = "1";
	FixStr[4].KIKA_DECI = "3";
	FixStr[4].KIKA_NUM2 = "";
	FixStr[4].KIKA_NUM3 = "0";
	FixStr[4].KIKA_STR = "";
	FixStr[4].SOKU_FLG = "1";
	FixStr[4].TOKU_FLG = "0";
	FixStr[4].KIKA_PRT = "1";
	FixStr[4].VALUE_TYPE = "0";
	FixStr[4].VALUE_DECI = "3";

	//���|��d
	FixStr[5].TABLE1 = "KD51";
	FixStr[5].TABLE2 = "KD52";
	FixStr[5].KOMK_NO = "6";
	FixStr[5].ORDER_NO = "1";
	FixStr[5].KOMK_NM = "���|��d";
	FixStr[5].KOMK_ENG = "Apparent Density";
	FixStr[5].KIKI_NO = "3";
	FixStr[5].KIKI_NM = "�}�C�N�����[�^�A�V��";
	FixStr[5].TANI[0] = "";
	FixStr[5].TANI[1] = "";
	FixStr[5].TANI[2] = "";
	FixStr[5].TANI[3] = "";
	FixStr[5].KIKA_TYPE = "1";
	FixStr[5].KIKA_KIND = "1";
	FixStr[5].KIKA_DECI = "2";
	FixStr[5].KIKA_NUM2 = "";
	FixStr[5].KIKA_NUM3 = "0";
	FixStr[5].KIKA_STR = "";
	FixStr[5].SOKU_FLG = "1";
	FixStr[5].TOKU_FLG = "0";
	FixStr[5].KIKA_PRT = "1";
	FixStr[5].VALUE_TYPE = "0";
	FixStr[5].VALUE_DECI = "2";

	//���[�h����t���x
	FixStr[6].TABLE1 = "KD41";
	FixStr[6].TABLE2 = "KD42";
	FixStr[6].KOMK_NO = "7";
	FixStr[6].ORDER_NO = "10";
	FixStr[6].KOMK_NM = "���[�h����t���x";
	FixStr[6].KOMK_ENG = "Pull Strength";
	FixStr[6].KIKI_NO = "5";
	FixStr[6].KIKI_NM = "�ޗ������@";
	FixStr[6].TANI[0] = "kgf";
	FixStr[6].TANI[1] = "N";
	FixStr[6].TANI[2] = "MPa";
	FixStr[6].TANI[3] = "";
	FixStr[6].KIKA_TYPE = "1";
	FixStr[6].KIKA_KIND = "3";
	FixStr[6].KIKA_DECI = "1";
	FixStr[6].KIKA_NUM2 = "0";
	FixStr[6].KIKA_NUM3 = "0";
	FixStr[6].KIKA_STR = "";
	FixStr[6].SOKU_FLG = "1";
	FixStr[6].TOKU_FLG = "0";
	FixStr[6].KIKA_PRT = "1";
	FixStr[6].VALUE_TYPE = "0";
	FixStr[6].VALUE_DECI = "1";

	//���[�h����t��R
	FixStr[7].TABLE1 = "KD31";
	FixStr[7].TABLE2 = "KD32";
	FixStr[7].KOMK_NO = "8";
	FixStr[7].ORDER_NO = "9";
	FixStr[7].KOMK_NM = "���[�h����t��R";
	FixStr[7].KOMK_ENG = "Connection Drop";
	FixStr[7].KIKI_NO = "12";
	FixStr[7].KIKI_NM = "���[�h����t��R����@";
	FixStr[7].TANI[0] = "mV/";
	FixStr[7].TANI[1] = "A";
	FixStr[7].TANI[2] = "";
	FixStr[7].TANI[3] = "";
	FixStr[7].KIKA_TYPE = "1";
	FixStr[7].KIKA_KIND = "2";
	FixStr[7].KIKA_DECI = "1";
	FixStr[7].KIKA_NUM2 = "0";
	FixStr[7].KIKA_NUM3 = "0";
	FixStr[7].KIKA_STR = "";
	FixStr[7].SOKU_FLG = "1";
	FixStr[7].TOKU_FLG = "0";
	FixStr[7].KIKA_PRT = "1";
	FixStr[7].VALUE_TYPE = "0";
	FixStr[7].VALUE_DECI = "1";

	//��R��
	FixStr[8].TABLE1 = "KD71";
	FixStr[8].TABLE2 = "KD72";
	FixStr[8].KOMK_NO = "9";
	FixStr[8].ORDER_NO = "6";
	FixStr[8].KOMK_NM = "��R��";
	FixStr[8].KOMK_ENG = "Specific Resistance";
	FixStr[8].KIKI_NO = "11";
	FixStr[8].KIKI_NM = "��R������@";
    //2003.07.01 ��R�� �ʃ��cm10A �� �ʃ��cm �ɕύX�ɂȂ���
	//FixStr[8].TANI[0] = "�ʃ��cm ";
	//FixStr[8].TANI[1] = "A";
	FixStr[8].TANI[0] = "�ʃ��cm";
	FixStr[8].TANI[1] = "";
	FixStr[8].TANI[2] = "";
	FixStr[8].TANI[3] = "";
	FixStr[8].KIKA_TYPE = "1";
	FixStr[8].KIKA_KIND = "1";
	FixStr[8].KIKA_DECI = "0";
	FixStr[8].KIKA_NUM2 = "";
	FixStr[8].KIKA_NUM3 = "0";
	FixStr[8].KIKA_STR = "";
	FixStr[8].SOKU_FLG = "1";
	FixStr[8].TOKU_FLG = "0";
	FixStr[8].KIKA_PRT = "1";
	FixStr[8].VALUE_TYPE = "0";
	FixStr[8].VALUE_DECI = "0";

	//�Ȃ�����
	FixStr[9].TABLE1 = "KD81";
	FixStr[9].TABLE2 = "KD82";
	FixStr[9].KOMK_NO = "10";
	FixStr[9].ORDER_NO = "7";
	FixStr[9].KOMK_NM = "�Ȃ�����";
	FixStr[9].KOMK_ENG = "Transverse Strength";
	FixStr[9].KIKI_NO = "5";
	FixStr[9].KIKI_NM = "�ޗ������@";
	FixStr[9].TANI[0] = "kgf/c�u";
	FixStr[9].TANI[1] = "N/c�u";
	FixStr[9].TANI[2] = "Mpa";
	FixStr[9].TANI[3] = "N/m�u";
	FixStr[9].KIKA_TYPE = "1";
	FixStr[9].KIKA_KIND = "1";
	FixStr[9].KIKA_DECI = "1";
	FixStr[9].KIKA_NUM2 = "";
	FixStr[9].KIKA_NUM3 = "0";
	FixStr[9].KIKA_STR = "";
	FixStr[9].SOKU_FLG = "1";
	FixStr[9].TOKU_FLG = "0";
	FixStr[9].KIKA_PRT = "1";
	FixStr[9].VALUE_TYPE = "0";
	FixStr[9].VALUE_DECI = "1";

	//�Ȃ������i�����j
	FixStr[10].TABLE1 = "KDC1";
	FixStr[10].TABLE2 = "KDC2";
	FixStr[10].KOMK_NO = "11";
	FixStr[10].ORDER_NO = "8";
	FixStr[10].KOMK_NM = "�Ȃ������i�����j";
	FixStr[10].KOMK_ENG = "Transverse Strength(Genuine)";
	FixStr[10].KIKI_NO = "5";
	FixStr[10].KIKI_NM = "�ޗ������@";
	FixStr[10].TANI[0] = "kgf/c�u";
	FixStr[10].TANI[1] = "N/c�u";
	FixStr[10].TANI[2] = "Mpa";
	FixStr[10].TANI[3] = "N/m�u";
    //2003/07/22 E.Takase �P�ʒǉ�
	FixStr[10].TANI[4] = "N";
	FixStr[10].KIKA_TYPE = "1";
	FixStr[10].KIKA_KIND = "1";
	FixStr[10].KIKA_DECI = "1";
	FixStr[10].KIKA_NUM2 = "";
	FixStr[10].KIKA_NUM3 = "0";
	FixStr[10].KIKA_STR = "";
	FixStr[10].SOKU_FLG = "1";
	FixStr[10].TOKU_FLG = "0";
	FixStr[10].KIKA_PRT = "1";
	FixStr[10].VALUE_TYPE = "0";
	FixStr[10].VALUE_DECI = "1";

	//�d�x�g���b�i���ʁj
	FixStr[11].TABLE1 = "KD61";
	FixStr[11].TABLE2 = "KD62";
	FixStr[11].KOMK_NO = "12";
	FixStr[11].ORDER_NO = "2";
	FixStr[11].KOMK_NM = "�d�x�g���b�i���ʁj";
	FixStr[11].KOMK_ENG = "Hardness(HsC P)";
	FixStr[11].KIKI_NO = "9";
	FixStr[11].KIKI_NM = "�V���A�d�x�v�b�^";
	FixStr[11].TANI[0] = "HsC";
	FixStr[11].TANI[1] = "";
	FixStr[11].TANI[2] = "";
	FixStr[11].TANI[3] = "";
	FixStr[11].KIKA_TYPE = "1";
	FixStr[11].KIKA_KIND = "1";
	FixStr[11].KIKA_DECI = "0";
	FixStr[11].KIKA_NUM2 = "";
	FixStr[11].KIKA_NUM3 = "0";
	FixStr[11].KIKA_STR = "";
	FixStr[11].SOKU_FLG = "1";
	FixStr[11].TOKU_FLG = "0";
	FixStr[11].KIKA_PRT = "1";
	FixStr[11].VALUE_TYPE = "0";
	FixStr[11].VALUE_DECI = "0";

	//�d�x�g���b�i���ʁj
	FixStr[12].TABLE1 = "KD61";
	FixStr[12].TABLE2 = "KD62";
	FixStr[12].KOMK_NO = "13";
	FixStr[12].ORDER_NO = "3";
	FixStr[12].KOMK_NM = "�d�x�g���b�i���ʁj";
	FixStr[12].KOMK_ENG = "Hardness(HsC S)";
	FixStr[12].KIKI_NO = "9";
	FixStr[12].KIKI_NM = "�V���A�d�x�v�b�^";
	FixStr[12].TANI[0] = "HsC";
	FixStr[12].TANI[1] = "";
	FixStr[12].TANI[2] = "";
	FixStr[12].TANI[3] = "";
	FixStr[12].KIKA_TYPE = "1";
	FixStr[12].KIKA_KIND = "1";
	FixStr[12].KIKA_DECI = "0";
	FixStr[12].KIKA_NUM2 = "";
	FixStr[12].KIKA_NUM3 = "0";
	FixStr[12].KIKA_STR = "";
	FixStr[12].SOKU_FLG = "1";
	FixStr[12].TOKU_FLG = "0";
	FixStr[12].KIKA_PRT = "1";
	FixStr[12].VALUE_TYPE = "0";
	FixStr[12].VALUE_DECI = "0";

	//�d�x (HsD ����)
	FixStr[13].TABLE1 = "KD61";
	FixStr[13].TABLE2 = "KD62";
	FixStr[13].KOMK_NO = "14";
	FixStr[13].ORDER_NO = "4";
	FixStr[13].KOMK_NM = "�d�x (HsD ���ʁj";
	FixStr[13].KOMK_ENG = "Hardness(HsD P)";
	FixStr[13].KIKI_NO = "10";
	FixStr[13].KIKI_NM = "�V���A�d�x�v�c�^";
	FixStr[13].TANI[0] = "HsD";
	FixStr[13].TANI[1] = "";
	FixStr[13].TANI[2] = "";
	FixStr[13].TANI[3] = "";
	FixStr[13].KIKA_TYPE = "1";
	FixStr[13].KIKA_KIND = "1";
	FixStr[13].KIKA_DECI = "1";
	FixStr[13].KIKA_NUM2 = "";
	FixStr[13].KIKA_NUM3 = "0";
	FixStr[13].KIKA_STR = "";
	FixStr[13].SOKU_FLG = "1";
	FixStr[13].TOKU_FLG = "0";
	FixStr[13].KIKA_PRT = "1";
	FixStr[13].VALUE_TYPE = "0";
	FixStr[13].VALUE_DECI = "1";

	//�d�x (HsD ����)
	FixStr[14].TABLE1 = "KD61";
	FixStr[14].TABLE2 = "KD62";
	FixStr[14].KOMK_NO = "15";
	FixStr[14].ORDER_NO = "5";
	FixStr[14].KOMK_NM = "�d�x (HsD ���ʁj";
	FixStr[14].KOMK_ENG = "Hardness(HsD S)";
	FixStr[14].KIKI_NO = "10";
	FixStr[14].KIKI_NM = "�V���A�d�x�v�c�^";
	FixStr[14].TANI[0] = "HsD";
	FixStr[14].TANI[1] = "";
	FixStr[14].TANI[2] = "";
	FixStr[14].TANI[3] = "";
	FixStr[14].KIKA_TYPE = "1";
	FixStr[14].KIKA_KIND = "1";
	FixStr[14].KIKA_DECI = "1";
	FixStr[14].KIKA_NUM2 = "";
	FixStr[14].KIKA_NUM3 = "0";
	FixStr[14].KIKA_STR = "";
	FixStr[14].SOKU_FLG = "1";
	FixStr[14].TOKU_FLG = "0";
	FixStr[14].KIKA_PRT = "1";
	FixStr[14].VALUE_TYPE = "0";
	FixStr[14].VALUE_DECI = "1";

	//����
	FixStr[15].TABLE1 = "KD91";
	FixStr[15].TABLE2 = "KD92";
	FixStr[15].KOMK_NO = "16";
	FixStr[15].ORDER_NO = "16";
	FixStr[15].KOMK_NM = "����";
	FixStr[15].KOMK_ENG = "Crackforce";
	FixStr[15].KIKI_NO = "5";
	FixStr[15].KIKI_NM = "�ޗ������@";
	FixStr[15].TANI[0] = "N";
	FixStr[15].TANI[1] = "";
	FixStr[15].TANI[2] = "";
	FixStr[15].TANI[3] = "";
	FixStr[15].KIKA_TYPE = "1";
	FixStr[15].KIKA_KIND = "1";
	FixStr[15].KIKA_DECI = "1";
	FixStr[15].KIKA_NUM2 = "";
	FixStr[15].KIKA_NUM3 = "0";
	FixStr[15].KIKA_STR = "";
	FixStr[15].SOKU_FLG = "1";
	FixStr[15].TOKU_FLG = "0";
	FixStr[15].KIKA_PRT = "1";
	FixStr[15].VALUE_TYPE = "0";
	FixStr[15].VALUE_DECI = "1";

	//�q�X�g�O����(�u���V����Min�EMax)
	FixStr[16].TABLE1 = "KDA1";
	FixStr[16].TABLE2 = " ";
	FixStr[16].KOMK_NO = "17";
	FixStr[16].ORDER_NO = "17";
	FixStr[16].KOMK_NM = "�u���V����";
	FixStr[16].KOMK_ENG = "Brush Thickness";
	FixStr[16].KIKI_NO = "1";
	FixStr[16].KIKI_NM = "�}�C�N�����[�^";
	FixStr[16].TANI[0] = "mm";
	FixStr[16].TANI[1] = "";
	FixStr[16].TANI[2] = "";
	FixStr[16].TANI[3] = "";
	FixStr[16].KIKA_TYPE = "1";
	FixStr[16].KIKA_KIND = "";
	FixStr[16].KIKA_DECI = "2";
	FixStr[16].KIKA_NUM2 = "0";
	FixStr[16].KIKA_NUM3 = "0";
	FixStr[16].KIKA_STR = "";
	FixStr[16].SOKU_FLG = "1";
	FixStr[16].TOKU_FLG = "0";
	FixStr[16].KIKA_PRT = "1";
	FixStr[16].VALUE_TYPE = "0";
	FixStr[16].VALUE_DECI = "2";

	//�q�X�g�O����(�u���V����Cp�ECpk)
	FixStr[17].TABLE1 = "KDA1";
	FixStr[17].TABLE2 = " ";
	FixStr[17].KOMK_NO = "18";
	FixStr[17].ORDER_NO = "18";
	FixStr[17].KOMK_NM = "�u���V����";
	FixStr[17].KOMK_ENG = "Brush Thickness";
	FixStr[17].KIKI_NO = "1";
	FixStr[17].KIKI_NM = "�}�C�N�����[�^";
	FixStr[17].TANI[0] = "Cpk";
	FixStr[17].TANI[1] = "";
	FixStr[17].TANI[2] = "";
	FixStr[17].TANI[3] = "";
	FixStr[17].KIKA_TYPE = "1";
	FixStr[17].KIKA_KIND = "3";
	FixStr[17].KIKA_DECI = "2";
	FixStr[17].KIKA_NUM2 = "0";
	FixStr[17].KIKA_NUM3 = "0";
	FixStr[17].KIKA_STR = "";
	FixStr[17].SOKU_FLG = "1";
	FixStr[17].TOKU_FLG = "0";
	FixStr[17].KIKA_PRT = "1";
	FixStr[17].VALUE_TYPE = "0";
	FixStr[17].VALUE_DECI = "2";

}
/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�f�[�^�x�[�X����
//
//  �@�\����
//    ���i�K�i�}�X�^��蓾�Ӑ�R�[�h�E���Ӑ於�̎擾���܂�
//
//  �p�����^����
//    int iNo				�F�����Ώۂ̑��荀��ID
//
//  �߂�l
//    int					�F0=�������� -1=�������s
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
int __fastcall TForm1::GetDTKS(void)
{
	AnsiString sBuf;

	KSD21.DTKSCOD = "";
	KSD21.DTKSNAM = "";

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// �⍇�����s
	sBuf = "";
	sBuf += "SELECT DTKSCOD, DTKSNAM, DTKSHIN, HINBAN ";
	sBuf += "FROM KM02 WHERE DTKSHIN='";
	sBuf += KD_1.DTKSHIN;
	sBuf += "' AND REVCNT = 0";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	if ( Query1->Bof && Query1->Eof ) {
	//�������� �O��
		return(-1);
	}
	Query1->First();
	KSD21.DTKSCOD = Null_S(Query1->FieldValues["DTKSCOD"]);
	KSD21.DTKSNAM = Null_S(Query1->FieldValues["DTKSNAM"]);


	return(0);
}
/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�f�[�^�x�[�X����
//
//  �@�\����
//    ���i�K�i�}�X�^���A�`��敪�擾
//
//  �p�����^����
//    int iNo				�F�����Ώۂ̑��荀��ID
//
//  �߂�l
//    int					�F0=�������� -1=�������s
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
AnsiString __fastcall TForm1::GetKEIJYO_KBN(void)
{
	AnsiString sBuf;
	AnsiString sKEIJYO_KBN;
	AnsiString sDTKSHIN;

	sKEIJYO_KBN = "";
	sDTKSHIN    = Null_S(Q_KD_1->FieldValues["DTKSHIN"]);
	
	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// �⍇�����s
	sBuf  = "";
	sBuf += "SELECT KEIJKBN ";
	sBuf += "FROM KM02 WHERE DTKSHIN='";
	sBuf += sDTKSHIN;
	sBuf += "' AND REVCNT = 0";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	if ( Query1->Bof && Query1->Eof ) {
	//�������� �O��
		return(-1);
	}
	Query1->First();
	sKEIJYO_KBN = Null_S(Query1->FieldValues["KEIJKBN"]);


	return(sKEIJYO_KBN);
}

/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�����񑀍�
//
//  �@�\����
//    ������Null�Ȃ�X�y�[�X��Ԃ�
//
//  �p�����^����
//    Variant &vBuf			�F�����Ώە�����
//
//  �߂�l
//    AnsiString			�F�����񑀍쌋��
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
AnsiString __fastcall TForm1::Null_S(Variant &vBuf)
{
	AnsiString sBuf;

	if ( vBuf.IsNull() ) {
		sBuf = " ";
	} else {
		sBuf = VarToStr(vBuf);
	}
	return ( sBuf );

}

/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F�����񑀍�
//
//  �@�\����
//    ���lstrM��strA��}��
//
//  �p�����^����
//    AnsiString strM		�F�������镶����
//    int iNo				�F�����Ώۂ̑��荀��ID
//    AnsiString strA		�F������镶����
//
//  �߂�l
//    AnsiString			�F�����񑀍쌋��
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
AnsiString __fastcall TForm1::InsMEMO(AnsiString strM, int iNo, AnsiString strA)
{
	int iPos;
	int iPos2;
	int iPos3;
	int iLen;
	int i;
	AnsiString sBuf;
	AnsiString sBuf2;
	sBuf = "";
	sBuf2 = "";

	//MEMOStr�z�񏉊���
	for ( i = 0; i < FixStrNum; i++ ) {
		MEMOStr[i] = "";
	}

	//MEMOStr�z��ɃZ�b�g
	for ( i = 0; i < FixStrNum; i++ ) {
		iPos = strM.AnsiPos(FixStr[i].KOMK_NM);
		//�e�X�g�p�ŏ����������BiPos = strM.AnsiPos(FixStr[i].KOMK_NO);
		if ( iPos > 0 ) {
			iLen = strM.Length();
			iPos2 = iPos + FixStr[i].KOMK_NM.Length() ;
			sBuf = strM.SubString(iPos2+1,iLen-iPos2);
			iPos3 = sBuf.AnsiPos("��");
			if ( iPos3 > 0 ) {
				sBuf2 = sBuf.SubString(1,iPos3-2);
			} else {
				sBuf2 = sBuf;
			}
            MEMOStr[i] = sBuf2;
		}
	}

	MEMOStr[iNo] = strA;
	sBuf = "";
	for ( i = 0; i < FixStrNum; i++ ) {
		if ( Trim(MEMOStr[i]) != "" ) {
			sBuf += FixStr[i].KOMK_NM + ":" + MEMOStr[i] + "��";
			//�e�X�g�p�ŏ����������BsBuf += FixStr[i].KOMK_NO + ":" + MEMOStr[i] + "��";
		}
	}

	//MEMO�̍ő啶������128
	if ( sBuf.Length() > 128 ) {
		if ( sBuf.ByteType(128) == mbLeadByte ) {
			sBuf2 = sBuf.SubString(1,128-1);
		} else {
			sBuf2 = sBuf.SubString(1,128);
		}
	} else {
    	sBuf2 = sBuf;
	}
	return(sBuf2);
}
/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�				�F���O�o��
//
//  �@�\����
//    ���X�g�{�b�N�X�E���O�t�@�C���Ƀ��O���o��
//
//  �p�����^����
//    AnsiString sErrLog	�F�G���[���b�Z�[�W
//    AnsiString sePrg		�F�֐���
//    AnsiString seDTKSHIN	�F���Ӑ�i��
//    AnsiString seLOTNO  	�F���b�gNo
//
//  �߂�l
//    AnsiString			�F�����񑀍쌋��
//
//  ���l
//    �Ȃ�
//
/*----------------------------------------------------------------------------*/
//���X�g�{�b�N�X�Ƀ��O���o��
void __fastcall TForm1::WriteErrLog(AnsiString sErrLog,  AnsiString sePrg,
								 	AnsiString seDTKSHIN,AnsiString seLOTNO)
{
	AnsiString sBuf;
	AnsiString FileName;
	FILE *fp;

    if ( ListLog->Items->Count > 100 ) {
    	ListLog->Clear();
    }

	sBuf = "";
	sBuf += sePrg + AnsiString::StringOfChar(' ', 25-sePrg.Length());
	sBuf += "DTKSHIN�F" + seDTKSHIN + AnsiString::StringOfChar(' ', 20-seDTKSHIN.Length());
	sBuf += " LOTNO�F" + seLOTNO    + AnsiString::StringOfChar(' ', 8-seLOTNO.Length());
    ListLog->Items->Add(sBuf);

    if ( Trim(sErrLog) != "" ) {
		sBuf = "   Error�F" + sErrLog + "(" + sePrg + ")";
        ListLog->Items->Add(sBuf);
    }


    Form1->Refresh();


    FileName = Application->ExeName;
    FileName = FileName.SubString(1,FileName.Length()-4);
    FileName = FileName + ".log";
	if( (fp = fopen( FileName.c_str(), "a" )) != NULL ){
		fprintf(fp,"%s\n", sBuf.c_str());
		fclose(fp);
	}


}
//---------------------------------------------------------------------------


