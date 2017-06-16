//---------------------------------------------------------------------------
//
//  Unit1.cpp
//    �y�o�׌����V�X�e���|�n���f�B�[�^�[�~�i�������e�i���X�z
//    ���C���t�H�[���iTForm1�N���X�j�̃����o�֐��̒�`
//
//  �쐬��
//    �c���@�֎i
//
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"



//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnCreate�C�x���g	�F�^�C�}�[�C�x���g�i1000msec�j�����������Ƃ����s���܂��B
//
//  �@�\����
//    �J�E���g�_�E������
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Tmr_CountDownTimer(TObject *Sender)
{
    Tmr_CountDown->Tag = Tmr_CountDown->Tag - 1;
    if( Tmr_CountDown->Tag <= 0 ){
        Tmr_CountDown->Enabled = false;
        Btn_Exit->Visible = false;

		// �}�X�^�[�f�[�^�������g�s�ւ̃_�E�����[�h�����J�n
        Main();

    } else{
		Lbl_2->Caption = "�J�n�܂� " + IntToStr(Tmr_CountDown->Tag) + "�b";
    }
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnCreate�C�x���g	�FForm1���쐬�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    ������ʂ̏�Ԃ�ݒ肵�܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �t�H�[�����쐬�����Ƃ��C�x���g���ȉ��̏����Ŕ������܂��B
//    OnCreate��OnShow��OnActivate��OnPaint
//
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{

    if( sCOMMAND.AnsiCompareIC( "/DIRECT" ) == 0 ){
        // ���C�����j���[���烆�[�U�[���N���������́A
        // �����ɏ������J�n���܂�

		// �}�X�^�[�f�[�^�������g�s�ւ̃_�E�����[�h�����J�n
        Main();

    } else {
        // �p�\�R���N�������́A�w�莞�ԂɎ������s���鎞�́A
        // �J�E���g�_�E����i���~�\�j�A�������J�n���܂�
		Lbl_1->Caption = "�n���f�B�[�^�[�~�i�������e�i���X�������J�n���܂��B";
		Lbl_2->Caption = "�J�n�܂� 5�b";
    	Tmr_CountDown->Tag = 5;
        Tmr_CountDown->Enabled = true;
    }
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�������~�v�{�^�������������̏���
//
//  �@�\����
//    �t�H�[������܂�
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Btn_ExitClick(TObject *Sender)
{
    Close();
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�}�X�^�[�f�[�^�������g�s�ւ̃_�E�����[�h�����J�n
//
//  �@�\����
//    �}�X�^�[�f�[�^�̐������s�Ȃ��܂�
//    �n���f�B�[�^�[�~�i���ւ̃_�E�����[�h�����J�n���܂�
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Main()
{

    TDateTime	dtDate;
	char 		CDPath[256];
	char 		path[256];
    AnsiString	sDATE;
    AnsiString	sSQL;
    AnsiString	sBuf1;
    AnsiString	sBuf2;
    AnsiString	sBuf3;
    FILE		*stream;
    int rtn;


	Lbl_1->Caption = "�n���f�B�[�^�[�~�i���p�̃}�X�^�[�f�[�^�𐮗����Ă��܂��B";
	Lbl_2->Caption = "���΂炭���҂����������B";
    Form1->Refresh();

    //�J�����g�f�B���N�g���̎擾
    strcpy(CDPath, "X:\\");	/* �l��Ԃ��`��: X:\ �ŕ�����𖞂��� */
    CDPath[0] = 'A' + getdisk();	/* X �����݂̃h���C�u���ɒu�������� */
    getcurdir(0, CDPath+3);	/* �����񕔕��̎c��ɃJ�����g�f�B���N�g����ǉ� */

    // �t�@�C�����X�V�p�ɊJ��
    strcpy(path,CDPath);
    strcat(path, "\\master.dat");
    if( (stream = fopen( path, "w+" )) != NULL ){
    	//����Ƀt�@�C�����I�[�v���ł����ꍇ

	    // �f�[�^�x�[�X������
	    Database1->Open();

        // �R�N�O�̃f�[�^�܂Ō������܂�
		dtDate = Date();
		dtDate -= 356 * 3;
	    sDATE = FormatDateTime( "yyyymmdd", dtDate);

		// �⍇�����s
		sSQL  = "SELECT KOKBNG, DTKSHIN, LOTBNG ";
		sSQL += "FROM SD21S ";
		sSQL += "WHERE DENYMD>'" + sDATE + "' AND SYUKBN='0' ";
		sSQL += "ORDER BY KOKBNG";

		Query1->SQL->Add(sSQL);
		Query1->Open();
		Query1->Active = true;

		while( !Query1->Eof ){

            // �m�H��NO�n�̎擾
			sBuf1 = Query1->FieldValues["KOKBNG"];

            // �m��\���Ӑ�i�ԁn�̎擾
	        if( VarIsNull(Query1->FieldValues["DTKSHIN"]) ){
				sBuf2 = "";
			} else{
				sBuf2 = Query1->FieldValues["DTKSHIN"];
	        }

            if( sBuf2.Trim() != "" ){

	            // �m���b�gNO�n�̎擾
	        	if( VarIsNull(Query1->FieldValues["LOTBNG"]) ){
					sBuf3 = "";
				} else{
					sBuf3 = Query1->FieldValues["LOTBNG"];
	        	}

	            if( sBuf3.Trim() != "" ){

                    // ���������𒲐����܂�
                    sBuf1 = sBuf1 + AnsiString::StringOfChar(' ',  6 - sBuf1.Length());
                    sBuf2 = sBuf2 + AnsiString::StringOfChar(' ', 20 - sBuf2.Length());
                    sBuf3 = sBuf3 + AnsiString::StringOfChar(' ',  6 - sBuf3.Length());

	        	    // �P���R�[�h�̏�����
			        fprintf( stream,"%s%s%s\n", sBuf1.c_str(),
                    							sBuf2.c_str(),
                                                sBuf3.c_str());

                }
            }

			// �J�[�\�������ɃZ�b�g����
			Query1->Next();

		}

		// �f�[�^�x�[�X�ڑ����J�����܂�
	    Query1->Close();
		Database1->Close();

	    // �t�@�C�������
    	fclose(stream);


    // k.k start
	Lbl_1->Caption = "�}�X�^�[�f�[�^���n���f�B�[�^�[�~�i���ɓ]�����Ă��܂��B";
	Lbl_2->Caption = "���΂炭���҂����������B";
    Form1->Refresh();

    fn = path;

    // �f�[�^�_�E�����[�h
    rtn = DataDownLoad();

    if (rtn < 0) {
        // ���s���b�Z�[�W
        MessageDlg("�}�X�^�[�f�[�^�̓]�������s���܂����B", mtError, TMsgDlgButtons() << mbOK , 0);
    } else {
        // �������b�Z�[�W
        MessageDlg("�}�X�^�[�f�[�^�̓]�����������܂����B", mtInformation, TMsgDlgButtons() << mbOK , 0);
    }

    // k.k end


 	}else{
    	//�t�@�C���̃I�[�v���Ɏ��s�����ꍇ
		fclose(stream);
	}

    Close();
}

//---------------------------------------------------------------------------
// BCC�̐��� k.k
/*AnsiString TForm1::CreatBCC(AnsiString asStr)
{
	//TODO ���̉��ɃR�[�h��ǉ����Ă�������
	int iAscii;

	// 1�o�C�g����ASCII�R�[�h�ɕϊ��������Ă���
	iAscii = STX;
	int len = asStr.Length();
	for (int i = 2; i <= len; i++)
		iAscii = iAscii + int(asStr[i]) & 0xff;

	// 16�i���ɕϊ����ĕԂ�
	return IntToHex(iAscii,2);

}
//---------------------------------------------------------------------------*/


//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�FRS-232C �f�[�^��M����
//
//  �@�\����
//    RS-232C �f�[�^��M����
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    AnsiString		�F��M�����o�b�t�@��Ԃ��܂�
//
//  ���l
//    �쐬��			�F�Ö�@�a�K
//
//---------------------------------------------------------------------------
AnsiString TForm1::DataReceive()
{
	//TODO ���̉��ɃR�[�h��ǉ����Ă�������
	int iSW;
	char Buf[64];
	AnsiString asRet;
	AnsiString asRecBuf;
	time_t nowTime;

	iSW = 10;
	// ����t���[�ݒ� ON
	CommSetFlow(iComPort,1,1,1,1,1);
	while (1){
		// �^�C���A�E�g�`�F�b�N
		time(&nowTime);
		if (nowTime - sTime > 1) {
			MessageDlg("�ʐM���^�C���A�E�g�ɂȂ�܂����B", mtError, TMsgDlgButtons() << mbOK , 0);
			return "";
		}
		// �P�o�C�g���Ɏ擾
		CommReadNum(iComPort,Buf,1);
		switch (iSW){
		case 10:
			// �w�b�_��� STX�i0x02�j
			if (Buf[0] == STX) {
				asRecBuf = Buf[0];
				iSW++;
			}
			break;
		case 11:
			// ID���
			if (Buf[0] == '1' || Buf[0] == '2'){
				asRecBuf = asRecBuf + Buf[0];
				iSW++;
			}
			break;
		case 12:
			//  �敪���
			if (Buf[0] == 'A' || Buf[0] == 'D' || Buf[0] == 'R' ||
				Buf[0] == 'S' || Buf[0] == 'M'){
				asRecBuf = asRecBuf + Buf[0];
				iSW++;
			}
			break;
		case 13:
			// �t�b�^��� ETX�i0x03�j
			// �t�b�^�iETX�j�ɂȂ����珈���𔲂���@
			if (Buf[0] == ETX){
				asRecBuf = asRecBuf + Buf[0];
				iSW = 20;
				break;
			} else {
				// �f�[�^��
				asRecBuf = asRecBuf + Buf[0];
			}
			break;
//		case 14:
//			iSW = 20;
//			break;
		}
		if (iSW == 20) break;
	}
	// ����t���[�ݒ� OFF
	CommSetFlow(iComPort,0,0,0,0,0);
	return (asRecBuf);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�n���f�B�[�^�[�~�i���փf�[�^�𑗐M
//
//  �@�\����
//    �n���f�B�[�^�[�~�i���փf�[�^���_�E�����[�h�i���M�j���܂�
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    AnsiString		�F��M�����o�b�t�@��Ԃ��܂�
//
//  ���l
//    �쐬��			�F�Ö�@�a�K
//
//---------------------------------------------------------------------------
int TForm1::DataDownLoad()
{
    //TODO ���̉��ɃR�[�h��ǉ����Ă�������
	char tmp[64];
	char sData[64];
	int rtn;
    int Cnt;
    int nFlag;						// �����t���O�@
    int ComFlag;					// ����M�t���O
    int iRec;						// �}�X�^�[�t�@�C���f�[�^��
    AnsiString asBufData,asBuf;		// �|�[�g�o�b�t�@�p
	AnsiString sTmp1, sTmp2;
	time_t nowTime;

    // �}�X�^�[�f�[�^�s���擾
    Cnt = 0;
    nFlag = 0;
    fs.open(fn.c_str(), ios_base::in);
    if (!fs) {
        MessageDlg("�t�@�C�����J���܂���B", mtError, TMsgDlgButtons() << mbOK , 0);
            return (-1);
    }
    while (fs.getline(sData, sizeof sData))
        Cnt++;
    fs.close();
    // �v���O���X�o�[������
    ProgressBar->Max = Cnt;
    ProgressBar->Min = 0;

	while (1) {
		// Sleep(100);
		switch (nFlag) {
		case 0:
			nFlag = 10;
			break;
		case 10:
			// �ʐM�|�[�g�I�[�v��
			rtn = CommOpen("COM3","115200","N,8,1");
			if (rtn < 0) {
				MessageDlg("�ʐM�|�[�g�I�[�v���G���[", mtError, TMsgDlgButtons() << mbOK , 0);
				return (-1);
			}
			iComPort = rtn;
			nFlag = 100;
			break;
		case 100:
	        // ���M
	        sprintf(tmp, "%c%s%c", STX, "1D**", ETX);
	        /*
	        sprintf(tmp, "%c%s", STX, "1D");
			// BCC�`�F�b�N
			if (chkBCC->State == cbChecked) {
				sTmp1 = tmp;
				sTmp2 = CreatBCC(sTmp1);
				strcat(tmp, sTmp2.c_str());
			} else
				strcat(tmp, "**");
			//sprintf(tmp, "%s%c", tmp, ETX);
			tmp[5] = ETX;
			tmp[6] = '\0';
	        */
			CommClear(iComPort);		// �|�[�g�o�b�t�@�N���A
			CommWrite(iComPort, tmp);	// �_�E�����[�h�R�}���h���M
			time(&sTime);				// ���ݎ����擾
			nFlag = 110;
			break;
		case 110:
			// �^�C���A�E�g�`�F�b�N�i�P���j
			time(&nowTime);
			if (nowTime - sTime > 1) {
				CommClose(iComPort);
				MessageDlg("�ʐM���^�C���A�E�g�ɂȂ�܂����B", mtError, TMsgDlgButtons() << mbOK , 0);
				return (-1);
			}
			nFlag = 120;
			break;
	    case 120:
			// �o�b�t�@��M
			asBufData = DataReceive();

			// ���M����
			if (asBufData.AnsiPos("\x06") > 0) {
				nFlag = 130;	        // ACK��M
			} else {
				CommClose(iComPort);	// NAK��M
                return (-1);
            }
			break;
		case 130:
			// ���̓t�@�C��
			fs.open(fn.c_str(), ios_base::in);
			if (!fs) {
				CommClose(iComPort);
				MessageDlg("�t�@�C�����J���܂���B", mtError, TMsgDlgButtons() << mbOK , 0);
				return (-1);
			}
			iRec = 0;
			nFlag = 140;
			break;
		case 140:
			// �t�@�C����EOF�ɂȂ�܂ő��M�f�[�^��������쐬
			// EOF�ɂȂ������̃f�[�^���쐬
			if (fs.eof() != 0){
				sprintf(tmp, "%c%s", STX, "1M00000");
				sprintf(sData, "%32s", " ");
				nFlag = 150;
			} else {
				// �s���J�E���g
				iRec++;
				sprintf(tmp, "%c%s%05d", STX, "1M", iRec);
				fs.getline(sData, sizeof sData);
				time(&sTime);
				nFlag = 145;
                ProgressBar->Position = iRec;
			}
	        // �b��
	        if (sData[0] == '\0') {
	           sprintf(tmp, "%c%s", STX, "1M00000");
	           sprintf(sData, "%32s", " ");
	           nFlag = 150;
	        }
			strcat(tmp, sData);
	/*
			// BCC�`�F�b�N
			if (chkBCC->State == cbChecked) {
				sTmp1 = tmp;
				sTmp2 = CreatBCC(sTmp1);
				strcat(tmp, sTmp2.c_str());
			} else
				strcat(tmp, "**");

	*/		//sprintf(tmp, "%s%c", tmp, ETX);
	        strcat(tmp, "**");
			tmp[42] = ETX;
			tmp[43] = '\0';

			CommClear(iComPort);        // �|�[�g�o�b�t�@�N���A
			CommWrite(iComPort, tmp);   // �}�X�^�[�f�[�^�E�R�}���h���M
			break;
		case 145:
			// �^�C���A�E�g�`�F�b�N
			time(&nowTime);
			if (nowTime - sTime > 1) {
				MessageDlg("�ʐM���^�C���A�E�g�ɂȂ�܂����B", mtError, TMsgDlgButtons() << mbOK , 0);
				fs.close();
				CommClose(iComPort);
				return(-1);
			}
			nFlag = 146;
			break;
		case 146:
			// �o�b�t�@��M
			asBufData = DataReceive();

			// ���M����
			if (asBufData.AnsiPos("\x06") > 0) {
				nFlag = 140;	// ACK��M
			} else {
				CommClose(iComPort);	// NAK��M
                return (-1);
            }
			break;
		case 150:
			// �t�@�C���N���[�Y
			fs.close();
			time(&sTime);
			nFlag = 160;
			break;
		case 160:
			// �^�C���A�E�g�`�F�b�N
			time(&nowTime);
			if (nowTime - sTime > 1) {
				MessageDlg("�ʐM���^�C���A�E�g�ɂȂ�܂����B", mtError, TMsgDlgButtons() << mbOK , 0);
				CommClose(iComPort);
				return (-1);
			}
			nFlag = 170;
			break;
		case 170:
			// �o�b�t�@��M
			asBufData = DataReceive();

			// ���M����
			if (asBufData.AnsiPos("\x06") > 0) {
				nFlag = 999;		// ACK��M
			} else {
				CommClose(iComPort);	// NAK��M
                return (-1);
            }
			break;
		case 999:
			// �ʐM�I��
			CommClose(iComPort);	// �|�[�g�N���[�Y
			fs.close();
			return (1);
			break;
		}
	}
}
