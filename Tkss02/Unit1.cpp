//---------------------------------------------------------------------------
//
//  Unit1.cpp
//    �y�o�׌����V�X�e���|���|�[�g�o�́z
//    ���C���t�H�[���iTForm1�N���X�j�̃����o�֐��̒�`
//
//  �쐬��
//    �c���@�֎i
//
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NumberEdit"
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
//    OnCreate�C�x���g	�FForm1���쐬�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �e�ϐ��������ݒ肵�܂�
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

	char 		CDPath[256];

    // �f�[�^�x�[�X������
    Database1->Open();

    // StringList������
	sLots		= new TStringList;
	sHins		= new TStringList;
    sDtkshins	= new TStringList;
	sTITLE_JPN	= new TStringList;
	sTITLE_ENG	= new TStringList;

    //2003.05.26 E.Takase Add ��
	sCRSF_KSD11_SKTYMDMin	= new TStringList;  	//���b�g���̓��t�ŏ��l
	sCRSF_KSD11_SKTYMDStr	= new TStringList;  	//���b�g���̓��t���J���}��؂��
	sCRSF_KSD11_UPDCHR		= new TStringList;     	//���b�g���̑�\�X�V��(CSV�o�͎��Ɏg�p)
	sCRSF_KSD11_SKTYMD		= new TStringList;     	//���b�g���̓��t(CSV�o�͎��Ɏg�p)
    //2003.05.26 E.Takase Add ��

    //�J�����g�f�B���N�g���̎擾
    strcpy(CDPath, "X:\\");	/* �l��Ԃ��`��: X:\ �ŕ�����𖞂��� */
    CDPath[0] = 'A' + getdisk();	/* X �����݂̃h���C�u���ɒu�������� */
    getcurdir(0, CDPath+3);	/* �����񕔕��̎c��ɃJ�����g�f�B���N�g����ǉ� */

    // ����w���p���[�N�t�@�C���������肵�܂�
    strcpy(sRepData1,CDPath);
    strcpy(sRepData2,CDPath);
    strcpy(sRepData3,CDPath);
    strcpy(sRepData4,CDPath);
    strcpy(sRepData5_1,CDPath);
    strcpy(sRepData5_2,CDPath);
    strcpy(sRepData5_3,CDPath);
	strcpy(sRepData6_1,CDPath);
 	strcpy(sRepData6_2,CDPath);
	strcpy(sRepData6_3,CDPath);
    strcat(sRepData1,   "\\Reports\\RepData1.csv");
    strcat(sRepData2,   "\\Reports\\RepData2.csv");
    strcat(sRepData3,   "\\Reports\\RepData3.csv");
    strcat(sRepData4,   "\\Reports\\RepData4.csv");
    strcat(sRepData5_1, "\\Reports\\RepData5_1.csv");
    strcat(sRepData5_2, "\\Reports\\RepData5_2.csv");
    strcat(sRepData5_3, "\\Reports\\RepData5_3.csv");
	strcat(sRepData6_1, "\\Reports\\RepData6_1.csv");
	strcat(sRepData6_2, "\\Reports\\RepData6_2.csv");
	strcat(sRepData6_3, "\\Reports\\RepData6_3.csv");

    // ����p�G�N�Z���t�@�C���������肵�܂�
    strcpy(sRepExcel1,CDPath);
    strcpy(sRepExcel2,CDPath);
    strcpy(sRepExcel3,CDPath);
    strcpy(sRepExcel4,CDPath);
    strcpy(sRepExcel5,CDPath);
    strcpy(sRepExcel6,CDPath);
    //20170419 Y.Onishi ��Ver�������я��̏o�͂ɑΉ�
    strcpy(sRepExcel7,CDPath);
    
    strcat(sRepExcel1, "\\Reports\\�������я�.xls");
    strcat(sRepExcel2, "\\Reports\\�������я�(����).xls");
    strcat(sRepExcel3, "\\Reports\\�ޗ��ؖ���.xls");
    strcat(sRepExcel4, "\\Reports\\�ޗ��ؖ����i���ʁj.xls");
    strcat(sRepExcel5, "\\Reports\\�������ʎ��n��Ǘ��\.xls");
    strcat(sRepExcel6, "\\Reports\\�����o��[.xls");
    //20170419 Y.Onishi ��Ver�������я��̏o�͂ɑΉ�
    strcat(sRepExcel7, "\\Reports\\�������я�_new.xls");

	AnsiString sDATE, sYY, sMM, sDD;                                  //onishi �������t������
    int iYY;
    sDATE = FormatDateTime("yyyymmdd",Date()).c_str();
    sYY = sDATE.SubString(1,4);
    iYY = sYY.ToInt() - 3;                                            //onishi 3�N�O����
    sYY = AnsiString().sprintf("%d",iYY);
    sMM = sDATE.SubString(5,2);
    sDD = sDATE.SubString(7,2);
    sDATE = sYY + sMM + sDD;
    Edt_SEIKAN_YMD->Text = sDATE;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnActivate�C�x���g	�F�t�H�[�����A�N�e�B�u�ɂȂ����Ƃ��ɔ������܂��B
//
//  �@�\����
//    ������ԂŕK�v�Ȍ����������s�Ȃ��܂�
//    �y�������я��^�C�g�����ڃ}�X�^�[�̌����z
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
void __fastcall TForm1::FormActivate(TObject *Sender)
{
    int			iRow;
    AnsiString	sBuf;


    //----------------------------------------------
    // �������я��^�C�g�����o�͏��̌���

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // �⍇�����s�i�������я��^�C�g�����ڃ}�X�^�[�̌����擾�j
    sBuf = "SELECT COUNT(*) AS TITLE_NUM FROM KSM21";

    Query1->SQL->Add(sBuf);
    Query1->Open();
    Query1->Active = true;

    if( !Query1->Eof ){
        iTITLE_Cnt = Query1->FieldValues["TITLE_NUM"];
    }
    else {
        iTITLE_Cnt = 50;
    }

    // �������̊m�ہi�������я��^�C�g�����ڃ}�X�^�[�̌������j
    hMemTITLE = GlobalAlloc( GHND, sizeof(int) * iTITLE_Cnt );
    if( hMemTITLE == NULL ){
        SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(01)";
        SBr1->Update();
        Beep();
        return;
    }
    iTITLE = (int *)GlobalLock(hMemTITLE);
    if( hMemTITLE == NULL ){
        SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(02)";
        SBr1->Update();
        Beep();
        return;
    }

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // �⍇�����s�i�������я��^�C�g�����ڃ}�X�^�[�j
    sBuf = "SELECT KMK_NO, KMK_NM_JPN, KMK_NM_ENG FROM KSM21 ORDER BY ORDER_NO";

    Query1->SQL->Add(sBuf);
    Query1->Open();
    Query1->Active = true;

    iRow = 0;
    Clb1_CHK_TITLE->Clear();
    Clb2_CHK_TITLE->Clear();
    Clb3_CHK_TITLE->Clear();
    Clb4_CHK_TITLE->Clear();
    sTITLE_JPN->Clear();
    sTITLE_ENG->Clear();
    while( !Query1->Eof ){

        // �^�C�g�������`�F�b�N���X�g�{�b�N�X�ɒǉ�
        sBuf  = Query1->FieldValues["KMK_NM_JPN"];
        sTITLE_JPN->Add(sBuf);
        if( !VarIsNull(Query1->FieldValues["KMK_NM_ENG"]) ){
        	sBuf += "(" + AnsiString(Query1->FieldValues["KMK_NM_ENG"]) + ")";
        	sTITLE_ENG->Add(Query1->FieldValues["KMK_NM_ENG"]);
        }
        else {
        	sTITLE_ENG->Add("");
        }
        Clb1_CHK_TITLE->Items->Add(sBuf);
        Clb2_CHK_TITLE->Items->Add(sBuf);
        Clb3_CHK_TITLE->Items->Add(sBuf);
        Clb4_CHK_TITLE->Items->Add(sBuf);

        // �^�C�g������No���L���i�z��ԍ��́A�`�F�b�N���X�g�{�b�N�X��Item�C���f�b�N�X�j
        iTITLE[iRow] = Query1->FieldValues["KMK_NO"];
        iRow++;

        // �J�[�\�������ɃZ�b�g����
        Query1->Next();
    }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnCloseQuery�C�x���g�FClose ���\�b�h���Ăяo���ꂽ�Ƃ��܂��̓��[�U�[��
//          �t�H�[���̃V�X�e�����j���[�Łm����n��I�������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �J���������s�Ȃ��܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    bool &CanClose	�Ftrue  = ���̂܂܃t�H�[������܂�
//                        false = �t�H�[��Close���L�����Z�����܂�
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{

    //2003/10/22 E.Takase
    //���[�N�e�[�u����������
    bool bRtn = KSDDeleteData();

	// �f�[�^�x�[�X�ڑ����J�����܂�
    Query1->Close();
    Query2->Close();
    Query3->Close();
    Q_CRSub_KSD01->Close();
    Q_CRSub_KSD11->Close();
    Q_CRSub_KSD02->Close();
    Q_CRSub_KSD12->Close();
    Q_CRSub_KSD03->Close();
    Q_CRSub_TANSYA->Close();

	Database1->Close();

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�P�F�ꗗ�����v�{�^�������������̏���
//
//  �@�\����
//    �ꗗ�����t�H�[���iForm2�j��\�����܂��B
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
void __fastcall TForm1::BtnF01Click(TObject *Sender)
{
    if( !BtnF01->Enabled )    return;

    ////////////////////
    // �ꗗ����
    Form2->ShowModal();

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�Q�F�O���v�{�^�������������̏���
//
//  �@�\����
//    [Shift]+[TAB]�L�[�R�[�h�̃C�x���g�𔭐������܂��B
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
void __fastcall TForm1::BtnF02Click(TObject *Sender)
{
    if( !BtnF02->Enabled )    return;

	keybd_event(VK_SHIFT,0,0,0);
	keybd_event(VK_TAB,0,0,0);
	keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
	keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�R�F�����v�{�^�������������̏���
//
//  �@�\����
//    [TAB]�L�[�R�[�h�̃C�x���g�𔭐������܂��B
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
void __fastcall TForm1::BtnF03Click(TObject *Sender)
{
    if( !BtnF03->Enabled )    return;

	keybd_event(VK_TAB,0,0,0);
	keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�T�F��ʈ���v�{�^�������������̏���
//
//  �@�\����
//    ���C���t�H�[����������܂��B
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
void __fastcall TForm1::BtnF05Click(TObject *Sender)
{
	if( !BtnF05->Enabled ) return;

    ////////////////////
    // ��ʈ��
	Form1->Print();

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�V�F���e�m�F�v�{�^�������������̏���
//
//  �@�\����
//    �u�o�͓��e�m�F�v�{�^���������܂��B
//    �w�肳�ꂽ��������ɂ��ڍ׏��̌����������J�n���܂�
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
void __fastcall TForm1::BtnF07Click(TObject *Sender)
{
	if( !BtnF07->Enabled ) return;

    Btn1_OUT_CHECKClick(Sender);

    return;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�X�FExcel����v�{�^�������������̏���
//
//  �@�\����
//    �w�肳�ꂽ��������ɂ�背�|�[�g�쐬�������J�n���܂�
//    ����w��CSV�t�@�C���쐬��Excel�N���������Excel�I��
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
void __fastcall TForm1::BtnF09Click(TObject *Sender)
{
	if( !BtnF09->Enabled )    return;

    // ���|�[�g�쐬�����J�n
    CreateReport(0);

	return;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�P�O�FExcel�o�́v�{�^�������������̏���
//
//  �@�\����
//    �w�肳�ꂽ��������ɂ�背�|�[�g�쐬�������J�n���܂�
//    ����w��CSV�t�@�C���쐬��Excel�N��
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
void __fastcall TForm1::BtnF10Click(TObject *Sender)
{
	if( !BtnF10->Enabled )    return;

    // ���|�[�g�쐬�����J�n
    CreateReport(1);

	return;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�P�Q�F�߂�v�{�^�������������̏���
//
//  �@�\����
//    ���C���t�H�[����Close���܂�
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
void __fastcall TForm1::BtnF12Click(TObject *Sender)
{
	if( !BtnF12->Enabled )    return;
	Close();
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�o�͓��e�̊m�F�v�{�^�������������̏���
//
//  �@�\����
//    �e���|�[�g�^�u�̑I����Ԃ𔻒f���܂�
//    �w�肳�ꂽ��������ɂ��ڍ׏��̌������܂�
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
void __fastcall TForm1::Btn1_OUT_CHECKClick(TObject *Sender)
{

    int				i;
    int				iType;
    bool			iSEL_SZ;
    bool			iSEL_SK;
    int				iSEL_TK;	// 2004/09/24 A.Tamura �u�����v��ǉ�
    bool			iSEL_ZR;
    AnsiString		sBuf, sBuf2;
    TEdit*			edt_DTKSHIN;
    TEdit*			edt_LOTNO;
    TMaskEdit*		edt_DATE1;
    TMaskEdit*		edt_DATE2;
    TEdit*			edt_CUSTOM;
    TTabSheet*		tst_LOTNO;
    TCheckListBox*	clb_TITLE;
    TCheckListBox*	clb_LOTNO;
    TRadioButton*	rdo_X_ON;
    TRadioButton*	rdo_X_OFF;
    //20161214 Y.Onishi
    //Cp,Cpk�o�͂ɑΉ�
    TRadioButton*	rdo_X_CP;


    // �߂�l������
	ret_Btn1_OUT_CHECKClick = true;

	if( PgCtr_REPORT->ActivePage->Name == "TabSheet1" ){
        //----------------------------------------------
        // �������я�
        iNowTab = 1;

        iType = 1;

    	edt_DTKSHIN	= dynamic_cast<TEdit*>(Edt1_WHR_DTKSHIN);
    	edt_LOTNO	= dynamic_cast<TEdit*>(Edt1_WHR_LOTNO);
        edt_CUSTOM	= dynamic_cast<TEdit*>(Edt1_CHK_CUSTOMER);
        tst_LOTNO	= dynamic_cast<TTabSheet*>(PgCtr1_tst01);
        clb_TITLE	= dynamic_cast<TCheckListBox*>(Clb1_CHK_TITLE);
        rdo_X_ON	= dynamic_cast<TRadioButton*>(Rdo1_CHK_X_ON);
        rdo_X_OFF	= dynamic_cast<TRadioButton*>(Rdo1_CHK_X_OFF);
        //20161214 Y.Onishi
        //Cp,Cpk�o�͂ɑΉ�
        rdo_X_CP	= dynamic_cast<TRadioButton*>(Rdo1_CHK_X_CP);

		// �I���I�v�V�����̏�Ԃ��擾���܂�
		if( Rdo1_WHR_SOZAI_ON->Checked == true )	iSEL_SZ = true;
		else										iSEL_SZ = false;
		if( Rdo1_WHR_SYUKA_ON->Checked == true )	iSEL_SK = true;
		else										iSEL_SK = false;
		if( Rdo1_WHR_TOKUBETSU_ON->Checked == true )		iSEL_TK =  1;	// ����
		else if( Rdo1_WHR_TOKUBETSU_OFF->Checked == true )	iSEL_TK =  0;   // ���Ȃ�
		else												iSEL_TK = -1;   // ����
		if( Rdo1_WHR_ZAIRYOU_ON->Checked == true )	iSEL_ZR = true;
		else										iSEL_ZR = false;

    }
    else if( PgCtr_REPORT->ActivePage->Name == "TabSheet2" ){
        //----------------------------------------------
        // �������я��i���ʁj
        iNowTab = 2;

        if( Rdo2_WHR_TYPE1->Checked == true ){
        	// �i�ԁE���b�g�ɂ�錟��
        	iType = 1;

    		edt_DTKSHIN	= dynamic_cast<TEdit*>(Edt2_WHR_DTKSHIN1);
    		edt_LOTNO	= dynamic_cast<TEdit*>(Edt2_WHR_LOTNO1);
        } else {
        	// �i�ԁE�o�ד��ɂ�錟��
        	iType = 2;

    		edt_DTKSHIN	= dynamic_cast<TEdit*>(Edt2_WHR_DTKSHIN2);
    		edt_DATE1	= dynamic_cast<TMaskEdit*>(Edt2_WHR_SYUKADATE1);
    		edt_DATE2	= dynamic_cast<TMaskEdit*>(Edt2_WHR_SYUKADATE2);
        }

        edt_CUSTOM	= dynamic_cast<TEdit*>(Edt2_CHK_CUSTOMER);
        clb_LOTNO	= dynamic_cast<TCheckListBox*>(Clb2_CHK_LOT);
        clb_TITLE	= dynamic_cast<TCheckListBox*>(Clb2_CHK_TITLE);
        rdo_X_ON	= dynamic_cast<TRadioButton*>(Rdo2_CHK_X_ON);
        rdo_X_OFF	= dynamic_cast<TRadioButton*>(Rdo2_CHK_X_OFF);

		// �I���I�v�V�����̏�Ԃ��擾���܂�
		if( Rdo2_WHR_SOZAI_ON->Checked == true )	iSEL_SZ = true;
		else										iSEL_SZ = false;
		if( Rdo2_WHR_SYUKA_ON->Checked == true )	iSEL_SK = true;
		else										iSEL_SK = false;
		if( Rdo2_WHR_TOKUBETSU_ON->Checked == true )		iSEL_TK =  1;	// ����
		else if( Rdo2_WHR_TOKUBETSU_OFF->Checked == true )	iSEL_TK =  0;   // ���Ȃ�
		else												iSEL_TK = -1;   // ����
		if( Rdo2_WHR_ZAIRYOU_ON->Checked == true )	iSEL_ZR = true;
		else										iSEL_ZR = false;

    }
    else if( PgCtr_REPORT->ActivePage->Name == "TabSheet3" ){
        //----------------------------------------------
        // �ޗ��ؖ���
        iNowTab = 3;

        iType = 1;

    	edt_DTKSHIN	= dynamic_cast<TEdit*>(Edt3_WHR_DTKSHIN);
    	edt_LOTNO	= dynamic_cast<TEdit*>(Edt3_WHR_LOTNO);
        edt_CUSTOM	= dynamic_cast<TEdit*>(Edt3_CHK_CUSTOMER);
        tst_LOTNO	= dynamic_cast<TTabSheet*>(PgCtr3_tst01);
        clb_TITLE	= dynamic_cast<TCheckListBox*>(Clb3_CHK_TITLE);
        rdo_X_ON	= dynamic_cast<TRadioButton*>(Rdo3_CHK_X_ON);
        rdo_X_OFF	= dynamic_cast<TRadioButton*>(Rdo3_CHK_X_OFF);

		// �I���I�v�V�����̏�Ԃ��擾���܂�
		if( Rdo3_WHR_SOZAI_ON->Checked == true )	iSEL_SZ = true;
		else										iSEL_SZ = false;
		if( Rdo3_WHR_SYUKA_ON->Checked == true )	iSEL_SK = true;
		else										iSEL_SK = false;
		if( Rdo3_WHR_TOKUBETSU_ON->Checked == true )		iSEL_TK =  1;	// ����
		else if( Rdo3_WHR_TOKUBETSU_OFF->Checked == true )	iSEL_TK =  0;   // ���Ȃ�
		else												iSEL_TK = -1;   // ����
		if( Rdo3_WHR_ZAIRYOU_ON->Checked == true )	iSEL_ZR = true;
		else										iSEL_ZR = false;

    }
    else if( PgCtr_REPORT->ActivePage->Name == "TabSheet4" ){
        //----------------------------------------------
        // �ޗ��ؖ����i���ʁj
        iNowTab = 4;

        if( Rdo4_WHR_TYPE1->Checked == true ){
        	// �i�ԁE���b�g�ɂ�錟��
        	iType = 1;

    		edt_DTKSHIN	= dynamic_cast<TEdit*>(Edt4_WHR_DTKSHIN1);
    		edt_LOTNO	= dynamic_cast<TEdit*>(Edt4_WHR_LOTNO1);
        } else {
        	// �i�ԁE�o�ד��ɂ�錟��
        	iType = 2;

    		edt_DTKSHIN	= dynamic_cast<TEdit*>(Edt4_WHR_DTKSHIN2);
    		edt_DATE1	= dynamic_cast<TMaskEdit*>(Edt4_WHR_SYUKADATE1);
    		edt_DATE2	= dynamic_cast<TMaskEdit*>(Edt4_WHR_SYUKADATE2);
        }

        edt_CUSTOM	= dynamic_cast<TEdit*>(Edt4_CHK_CUSTOMER);
        clb_LOTNO	= dynamic_cast<TCheckListBox*>(Clb4_CHK_LOT);
        clb_TITLE	= dynamic_cast<TCheckListBox*>(Clb4_CHK_TITLE);
        rdo_X_ON	= dynamic_cast<TRadioButton*>(Rdo4_CHK_X_ON);
        rdo_X_OFF	= dynamic_cast<TRadioButton*>(Rdo4_CHK_X_OFF);

		// �I���I�v�V�����̏�Ԃ��擾���܂�
		if( Rdo4_WHR_SOZAI_ON->Checked == true )	iSEL_SZ = true;
		else										iSEL_SZ = false;
		if( Rdo4_WHR_SYUKA_ON->Checked == true )	iSEL_SK = true;
		else										iSEL_SK = false;
		if( Rdo4_WHR_TOKUBETSU_ON->Checked == true )		iSEL_TK =  1;	// ����
		else if( Rdo4_WHR_TOKUBETSU_OFF->Checked == true )	iSEL_TK =  0;   // ���Ȃ�
		else												iSEL_TK = -1;   // ����
		if( Rdo4_WHR_ZAIRYOU_ON->Checked == true )	iSEL_ZR = true;
		else										iSEL_ZR = false;

    }
    else if( PgCtr_REPORT->ActivePage->Name == "TabSheet5" ){
        //----------------------------------------------
        // �������ʎ��n��Ǘ��\
        iNowTab = 5;

        if( Rdo5_WHR_TYPE1->Checked == true ){
        	// �i�ԁE���b�g�ɂ�錟��
        	iType = 1;

    		edt_DTKSHIN	= dynamic_cast<TEdit*>(Edt5_WHR_DTKSHIN1);
    		edt_LOTNO	= dynamic_cast<TEdit*>(Edt5_WHR_LOTNO);
        } else {
        	// �i�ԁE�o�ד��ɂ�錟��
        	iType = 2;

    		edt_DTKSHIN	= dynamic_cast<TEdit*>(Edt5_WHR_DTKSHIN1);
    		edt_DATE1	= dynamic_cast<TMaskEdit*>(Edt5_WHR_SYUKADATE1);
    		edt_DATE2	= dynamic_cast<TMaskEdit*>(Edt5_WHR_SYUKADATE2);
        }

        edt_CUSTOM	= dynamic_cast<TEdit*>(Edt5_CHK_CUSTOMER);
        clb_LOTNO	= dynamic_cast<TCheckListBox*>(Clb5_CHK_LOT);

		// �I���I�v�V�����̏�Ԃ��擾���܂�
		if( Rdo5_WHR_SOZAI_ON->Checked == true )	iSEL_SZ = true;
		else										iSEL_SZ = false;
		if( Rdo5_WHR_SYUKA_ON->Checked == true )	iSEL_SK = true;
		else										iSEL_SK = false;
		if( Rdo5_WHR_TOKUBETSU_ON->Checked == true )		iSEL_TK =  1;	// ����
		else if( Rdo5_WHR_TOKUBETSU_OFF->Checked == true )	iSEL_TK =  0;   // ���Ȃ�
		else												iSEL_TK = -1;   // ����
		if( Rdo5_WHR_ZAIRYOU_ON->Checked == true )	iSEL_ZR = true;
		else										iSEL_ZR = false;

    }
    else if( PgCtr_REPORT->ActivePage->Name == "TabSheet6" ){
        //----------------------------------------------
        // �����o��[
        iNowTab = 6;

        if( Rdo6_WHR_TYPE1->Checked == true ){
            //2003/08/28 E.Takase
        	//// �i�ԁE���b�g�ɂ�錟��
        	//iType = 1;
        	// �i�ԁE���b�g�ɂ�錟��(������̃��b�g�o��)
        	iType = 4;

    		edt_DTKSHIN	= dynamic_cast<TEdit*>(Edt6_WHR_DTKSHIN1);
    		edt_LOTNO	= dynamic_cast<TEdit*>(Edt6_WHR_LOTNO1);
        } else {
        	// �������ɂ�錟��
        	iType = 3;

    		edt_DATE1	= dynamic_cast<TMaskEdit*>(Edt6_WHR_KENSADATE1);
    		edt_DATE2	= dynamic_cast<TMaskEdit*>(Edt6_WHR_KENSADATE2);
        }

        clb_LOTNO	= dynamic_cast<TCheckListBox*>(Clb6_CHK_LOT);

		// �I���I�v�V�����̏�Ԃ��擾���܂�
		if( Rdo6_WHR_SOZAI_ON->Checked == true )	iSEL_SZ = true;
		else										iSEL_SZ = false;
		if( Rdo6_WHR_SYUKA_ON->Checked == true )	iSEL_SK = true;
		else										iSEL_SK = false;
		if( Rdo6_WHR_TOKUBETSU_ON->Checked == true )		iSEL_TK =  1;	// ����
		else if( Rdo6_WHR_TOKUBETSU_OFF->Checked == true )	iSEL_TK =  0;   // ���Ȃ�
		else												iSEL_TK = -1;   // ����
		if( Rdo6_WHR_ZAIRYOU_ON->Checked == true )	iSEL_ZR = true;
		else										iSEL_ZR = false;

    }

	// �w�肳�ꂽ�i�ԁE���b�gNo������ς݂��ǂ������f���܂��B
   	// �w�肳�ꂽ�i�ԁE���t�i�o�ד��E�������j������ς݂��ǂ������f���܂��B
	if( Get_DTKSHIN_LOT( iType, edt_DTKSHIN, edt_LOTNO,
              edt_DATE1, edt_DATE2, iSEL_SZ, iSEL_SK, iSEL_TK, iSEL_ZR) == false){
    	// �߂�l������
		ret_Btn1_OUT_CHECKClick = false;
   		return;
   	}

    // 1�ڂ̃��b�gTabSheet���쐬���܂�
    if( sLots->Count >= 1 ){

        // �o�̓��b�gTabSheet�̈ꖇ�ڂɃ��b�g�ԍ���\�����܂�
		if( PgCtr_REPORT->ActivePage->Name == "TabSheet1" ||
        	PgCtr_REPORT->ActivePage->Name == "TabSheet3" ){
        	// �������я�
            // �ޗ��ؖ���

    		tst_LOTNO->Caption = sLots->Strings[0];
        }

        // �o�͑Ώۂ̃��b�g��I����Ԃŕ\�����܂�
        //2003/08/28 E.Takase
		//if( PgCtr_REPORT->ActivePage->Name == "TabSheet2" ||
        //	PgCtr_REPORT->ActivePage->Name == "TabSheet4" ||
        //	PgCtr_REPORT->ActivePage->Name == "TabSheet5" ||
        //    ( PgCtr_REPORT->ActivePage->Name == "TabSheet6" && iType == 1 ) ){
		if( PgCtr_REPORT->ActivePage->Name == "TabSheet2" ||
        	PgCtr_REPORT->ActivePage->Name == "TabSheet4" ||
        	PgCtr_REPORT->ActivePage->Name == "TabSheet5" ||
            ( PgCtr_REPORT->ActivePage->Name == "TabSheet6" && ( iType == 1 || iType == 4 )) ){
        	// �������я��i���ʁj
            // �ޗ��ؖ����i���ʁj
            // �������ʎ��n��Ǘ��\

			clb_LOTNO->Clear();
			for( i = 0; i < sLots->Count; i++){
			    clb_LOTNO->Items->Add(sLots->Strings[i]);
				clb_LOTNO->Checked[clb_LOTNO->Items->Count-1] = true;
            }
        }

        // �o�͑Ώۂ̃��b�g��I����Ԃŕ\�����܂�
		if( PgCtr_REPORT->ActivePage->Name == "TabSheet6" && iType == 3 ){
        	// �����o��[

			clb_LOTNO->Clear();
			for( i = 0; i < sDtkshins->Count; i++){
                sBuf2 = sDtkshins->Strings[i];
                sBuf  = sBuf2 + AnsiString::StringOfChar(' ', 20-sBuf2.Length());
                sBuf2 = sLots->Strings[i];
                sBuf  = sBuf + " " + sBuf2 + AnsiString::StringOfChar(' ',  6-sBuf2.Length());
			    clb_LOTNO->Items->Add( sBuf );
				clb_LOTNO->Checked[clb_LOTNO->Items->Count-1] = true;
            }
    		// �߂�l������
			ret_Btn1_OUT_CHECKClick = false;
        	return;
        }


        Query1->FindFirst();
		if(Query1->Eof == false) {

            // �Ж�(Customer)��\�����܂�
			if( PgCtr_REPORT->ActivePage->Name == "TabSheet1" ||
	        	PgCtr_REPORT->ActivePage->Name == "TabSheet2" ||
	        	PgCtr_REPORT->ActivePage->Name == "TabSheet3" ||
	        	PgCtr_REPORT->ActivePage->Name == "TabSheet4" ||
	        	PgCtr_REPORT->ActivePage->Name == "TabSheet5" ){
	        	// �������я�
                // �������я��i���ʁj
                // �ޗ��ؖ���
                // �ޗ��ؖ����i���ʁj
                // �������ʎ��n��Ǘ��\

				if( !VarIsNull(Query1->FieldValues["DTKSNAM"]) ){
					edt_CUSTOM->Text = AnsiString(Query1->FieldValues["DTKSNAM"]);
				}
	            else {
					edt_CUSTOM->Text = "";
	    		}
            }

			// �������я��^�C�g�����o�͍���
			if( PgCtr_REPORT->ActivePage->Name == "TabSheet1" ||
	        	PgCtr_REPORT->ActivePage->Name == "TabSheet2" ||
	        	PgCtr_REPORT->ActivePage->Name == "TabSheet3" ||
	        	PgCtr_REPORT->ActivePage->Name == "TabSheet4" ){
	        	// �������я�
                // �������я��i���ʁj
                // �ޗ��ؖ���
                // �ޗ��ؖ����i���ʁj

				for( i = 0; i < iTITLE_Cnt; i++){
					if( iTITLE[i] == AnsiString(Query1->FieldValues["OUT_TITLE1"]).ToIntDef(-1)
					 || iTITLE[i] == AnsiString(Query1->FieldValues["OUT_TITLE2"]).ToIntDef(-1)
					 || iTITLE[i] == AnsiString(Query1->FieldValues["OUT_TITLE3"]).ToIntDef(-1)
					 || iTITLE[i] == AnsiString(Query1->FieldValues["OUT_TITLE4"]).ToIntDef(-1)
					 || iTITLE[i] == AnsiString(Query1->FieldValues["OUT_TITLE5"]).ToIntDef(-1)
					 || iTITLE[i] == AnsiString(Query1->FieldValues["OUT_TITLE6"]).ToIntDef(-1)
					 || iTITLE[i] == AnsiString(Query1->FieldValues["OUT_TITLE7"]).ToIntDef(-1)
					 || iTITLE[i] == AnsiString(Query1->FieldValues["OUT_TITLE8"]).ToIntDef(-1) ){
						if( iTITLE[i] == 4 &&
                        	(PgCtr_REPORT->ActivePage->Name == "TabSheet2" ||
	        				 PgCtr_REPORT->ActivePage->Name == "TabSheet4" ) ){
                			// �������я��i���ʁj
                			// �ޗ��ؖ����i���ʁj�̎��́A�u���b�gNo�v��I�����邱�Ƃ͂��肦�Ȃ��B
                        	clb_TITLE->Checked[i] = false;
						}
                        else {
                        	clb_TITLE->Checked[i] = true;
                    	}
					}
					else {
						clb_TITLE->Checked[i] = false;
					}
				}
			}

            // X�̏o��
			if( PgCtr_REPORT->ActivePage->Name == "TabSheet1" ||
	        	PgCtr_REPORT->ActivePage->Name == "TabSheet2" ||
	        	PgCtr_REPORT->ActivePage->Name == "TabSheet3" ||
	        	PgCtr_REPORT->ActivePage->Name == "TabSheet4" ){
	        	// �������я�
                // �������я��i���ʁj
                // �ޗ��ؖ���
                // �ޗ��ؖ����i���ʁj

				if( AnsiString(Query1->FieldValues["X_OUT"]).ToIntDef(0) == 1 ){
	            	rdo_X_ON->Checked = true;
	            }
	            else {
	            	rdo_X_OFF->Checked = true;
	            }
			}

            //2003.05.16 E.Takase ��
            //�i���E�i��̏o��
            Edt6_CHK_HINMEI->Text = "";
            Edt6_CHK_HINSYU->Text = "";
			if( PgCtr_REPORT->ActivePage->Name == "TabSheet6") {
				if ( Rdo6_WHR_TYPE1->Checked == true ){
					//���Ӑ�i�ԁE���b�g�w��̏ꍇ
					if( !VarIsNull(Query1->FieldValues["HINMEI"]) ){
						Edt6_CHK_HINMEI->Text = AnsiString(Query1->FieldValues["HINMEI"]);
					}
	            	else {
						Edt6_CHK_HINMEI->Text = "";
	    			}
					if( !VarIsNull(Query1->FieldValues["ZISNAM"]) ){
						Edt6_CHK_HINSYU->Text = AnsiString(Query1->FieldValues["ZISNAM"]);
					}
	            	else {
						Edt6_CHK_HINSYU->Text = "";
	    			}
                }
            }

            //2003.05.16 E.Takase ��
		}
	}

    // ���b�g���̃^�C�g�����o�͍��ڂ��X�V���܂�
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet1" ){
      	// �������я�
        Btn_CHK_TITLEREFClick(Btn1_CHK_TITLEREF);

	}
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet2" ){
      	// �������я��i���ʁj
        Btn_CHK_TITLEREFClick(Btn2_CHK_TITLEREF);

	}
    if( PgCtr_REPORT->ActivePage->Name == "TabSheet3" ){
        // �ޗ��ؖ���
        Btn_CHK_TITLEREFClick(Btn3_CHK_TITLEREF);

    }
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet4" ){
      	// �ޗ��ؖ����i���ʁj
        Btn_CHK_TITLEREFClick(Btn4_CHK_TITLEREF);

	}

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�w�胍�b�gNo�ʂ̃^�C�g�������e�X�V���v�{�^�������������̏���
//
//  �@�\����
//    �w�肳�ꂽ�^�C�g�����o�͏��ɂ��^�C�g�����ڂ�ݒ肵�܂�
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
void __fastcall TForm1::Btn_CHK_TITLEREFClick(TObject *Sender)
{

    int			i, k, m;
    int			iMax;
    bool		iJapanese;
    AnsiString	sBuf, sBuf2, sBuf3;
    AnsiString	sDTKSHIN, sLOTNO;
	AnsiString	sTabSheetNM;

    TButton*		btn	= dynamic_cast<TButton*>(Sender);
    TPanel*			pnl_LOT1[9];
    TEdit*			edt_LOT1[8];
    TPageControl*	pct_LOT;
    TRadioButton*	rdo_LOT[3];
    TPanel*			pnl_DUMMY;
    TEdit*			edt_DUMMY;
    TRadioButton*	rdo_DUMMY;
    TCheckListBox*	clb_TITLE;


    if( btn->Name == "Btn1_CHK_TITLEREF" ){
        //---------------------------------
    	// �������я�

        if( iNowTab != 1 ){
			MessageDlg("��Ɂu�o�͓��e�̊m�F�v�{�^���������ĉ������B", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
    		// �߂�l������
			ret_Btn1_OUT_CHECKClick = false;
        	return;
        }

        sDTKSHIN = Edt1_WHR_DTKSHIN->Text;
        sLOTNO   = PgCtr1_tst01->Caption;

        if( Rdo1_WHR_FORMAT_JPN->Checked == true )	iJapanese = true;
        else                                        iJapanese = false;

        iMax		= 8;

	    clb_TITLE	= dynamic_cast<TCheckListBox*>(Clb1_CHK_TITLE);

    	pnl_LOT1[0] = dynamic_cast<TPanel*>(PgCtr1_tst1_Pnl1);
    	pnl_LOT1[1] = dynamic_cast<TPanel*>(PgCtr1_tst1_Pnl2);
    	pnl_LOT1[2] = dynamic_cast<TPanel*>(PgCtr1_tst1_Pnl3);
    	pnl_LOT1[3] = dynamic_cast<TPanel*>(PgCtr1_tst1_Pnl4);
    	pnl_LOT1[4] = dynamic_cast<TPanel*>(PgCtr1_tst1_Pnl5);
    	pnl_LOT1[5] = dynamic_cast<TPanel*>(PgCtr1_tst1_Pnl6);
    	pnl_LOT1[6] = dynamic_cast<TPanel*>(PgCtr1_tst1_Pnl7);
    	pnl_LOT1[7] = dynamic_cast<TPanel*>(PgCtr1_tst1_Pnl8);
    	pnl_LOT1[8] = dynamic_cast<TPanel*>(PgCtr1_tst1_Pnl9);

    	edt_LOT1[0] = dynamic_cast<TEdit*>(PgCtr1_tst1_Edt1);
    	edt_LOT1[1] = dynamic_cast<TEdit*>(PgCtr1_tst1_Edt2);
    	edt_LOT1[2] = dynamic_cast<TEdit*>(PgCtr1_tst1_Edt3);
    	edt_LOT1[3] = dynamic_cast<TEdit*>(PgCtr1_tst1_Edt4);
    	edt_LOT1[4] = dynamic_cast<TEdit*>(PgCtr1_tst1_Edt5);
    	edt_LOT1[5] = dynamic_cast<TEdit*>(PgCtr1_tst1_Edt6);
    	edt_LOT1[6] = dynamic_cast<TEdit*>(PgCtr1_tst1_Edt7);
    	edt_LOT1[7] = dynamic_cast<TEdit*>(PgCtr1_tst1_Edt8);

        pct_LOT     = dynamic_cast<TPageControl*>(PgCtr1_LOT);

        sTabSheetNM = "PgCtr1_tst";

    	rdo_LOT[0] = dynamic_cast<TRadioButton*>(PgCtr1_tst1_LOT4);
    	rdo_LOT[1] = dynamic_cast<TRadioButton*>(PgCtr1_tst1_LOT5);
    	rdo_LOT[2] = dynamic_cast<TRadioButton*>(PgCtr1_tst1_LOT6);

    } else if( btn->Name == "Btn2_CHK_TITLEREF" ){
        //---------------------------------
    	// �������я��i���ʁj

        if( iNowTab != 2 ){
			MessageDlg("��Ɂu�o�͓��e�̊m�F�v�{�^���������ĉ������B", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
    		// �߂�l������
			ret_Btn1_OUT_CHECKClick = false;
        	return;
        }

		k = 0;
		for( i = 0; i < iTITLE_Cnt; i++){
			if( Clb2_CHK_TITLE->Checked[i] == true ){
				k++;
			}
		}
        if( k > 6 ){
			MessageDlg("�^�C�g�����o�͏�񂪂U�ȏ�I������Ă��܂��B\n�I���������ĉ������B", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
    		// �߂�l������
			ret_Btn1_OUT_CHECKClick = false;
        	return;
        }

        if( Rdo2_WHR_TYPE1->Checked == true ){
        	sDTKSHIN = Edt2_WHR_DTKSHIN1->Text;
        } else {
        	sDTKSHIN = Edt2_WHR_DTKSHIN2->Text;
        }
        if( sLots->Count <= 0 )	return;
        sLOTNO   = sLots->Strings[0];

        if( Rdo2_WHR_FORMAT_JPN->Checked == true )	iJapanese = true;
        else                                        iJapanese = false;

        iMax		= 6;

	    clb_TITLE	= dynamic_cast<TCheckListBox*>(Clb2_CHK_TITLE);

    	pnl_LOT1[0] = dynamic_cast<TPanel*>(PgCtr2_tst1_Pnl1);
    	pnl_LOT1[1] = dynamic_cast<TPanel*>(PgCtr2_tst1_Pnl2);
    	pnl_LOT1[2] = dynamic_cast<TPanel*>(PgCtr2_tst1_Pnl3);
    	pnl_LOT1[3] = dynamic_cast<TPanel*>(PgCtr2_tst1_Pnl4);
    	pnl_LOT1[4] = dynamic_cast<TPanel*>(PgCtr2_tst1_Pnl5);
    	pnl_LOT1[5] = dynamic_cast<TPanel*>(PgCtr2_tst1_Pnl6);
    	pnl_LOT1[8] = dynamic_cast<TPanel*>(PgCtr2_tst1_Pnl9);

    	edt_LOT1[0] = dynamic_cast<TEdit*>(PgCtr2_tst1_Edt1);
    	edt_LOT1[1] = dynamic_cast<TEdit*>(PgCtr2_tst1_Edt2);
    	edt_LOT1[2] = dynamic_cast<TEdit*>(PgCtr2_tst1_Edt3);
    	edt_LOT1[3] = dynamic_cast<TEdit*>(PgCtr2_tst1_Edt4);
    	edt_LOT1[4] = dynamic_cast<TEdit*>(PgCtr2_tst1_Edt5);
    	edt_LOT1[5] = dynamic_cast<TEdit*>(PgCtr2_tst1_Edt6);


    	rdo_LOT[0] = dynamic_cast<TRadioButton*>(PgCtr2_tst1_LOT4);
    	rdo_LOT[1] = dynamic_cast<TRadioButton*>(PgCtr2_tst1_LOT5);
    	rdo_LOT[2] = dynamic_cast<TRadioButton*>(PgCtr2_tst1_LOT6);

    } else if( btn->Name == "Btn3_CHK_TITLEREF" ){
        //---------------------------------
    	// �ޗ��ؖ���

        if( iNowTab != 3 ){
			MessageDlg("��Ɂu�o�͓��e�̊m�F�v�{�^���������ĉ������B", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
    		// �߂�l������
			ret_Btn1_OUT_CHECKClick = false;
        	return;
        }

        sDTKSHIN    = Edt3_WHR_DTKSHIN->Text;
        sLOTNO      = PgCtr3_tst01->Caption;

        if( Rdo3_WHR_FORMAT_JPN->Checked == true )	iJapanese = true;
        else                                        iJapanese = false;

        iMax		= 8;

	    clb_TITLE	= dynamic_cast<TCheckListBox*>(Clb3_CHK_TITLE);

    	pnl_LOT1[0] = dynamic_cast<TPanel*>(PgCtr3_tst1_Pnl1);
    	pnl_LOT1[1] = dynamic_cast<TPanel*>(PgCtr3_tst1_Pnl2);
    	pnl_LOT1[2] = dynamic_cast<TPanel*>(PgCtr3_tst1_Pnl3);
    	pnl_LOT1[3] = dynamic_cast<TPanel*>(PgCtr3_tst1_Pnl4);
    	pnl_LOT1[4] = dynamic_cast<TPanel*>(PgCtr3_tst1_Pnl5);
    	pnl_LOT1[5] = dynamic_cast<TPanel*>(PgCtr3_tst1_Pnl6);
    	pnl_LOT1[6] = dynamic_cast<TPanel*>(PgCtr3_tst1_Pnl7);
    	pnl_LOT1[7] = dynamic_cast<TPanel*>(PgCtr3_tst1_Pnl8);
    	pnl_LOT1[8] = dynamic_cast<TPanel*>(PgCtr3_tst1_Pnl9);

    	edt_LOT1[0] = dynamic_cast<TEdit*>(PgCtr3_tst1_Edt1);
    	edt_LOT1[1] = dynamic_cast<TEdit*>(PgCtr3_tst1_Edt2);
    	edt_LOT1[2] = dynamic_cast<TEdit*>(PgCtr3_tst1_Edt3);
    	edt_LOT1[3] = dynamic_cast<TEdit*>(PgCtr3_tst1_Edt4);
    	edt_LOT1[4] = dynamic_cast<TEdit*>(PgCtr3_tst1_Edt5);
    	edt_LOT1[5] = dynamic_cast<TEdit*>(PgCtr3_tst1_Edt6);
    	edt_LOT1[6] = dynamic_cast<TEdit*>(PgCtr3_tst1_Edt7);
    	edt_LOT1[7] = dynamic_cast<TEdit*>(PgCtr3_tst1_Edt8);

        pct_LOT     = dynamic_cast<TPageControl*>(PgCtr3_LOT);

        sTabSheetNM = "PgCtr3_tst";

    	rdo_LOT[0] = dynamic_cast<TRadioButton*>(PgCtr3_tst1_LOT4);
    	rdo_LOT[1] = dynamic_cast<TRadioButton*>(PgCtr3_tst1_LOT5);
    	rdo_LOT[2] = dynamic_cast<TRadioButton*>(PgCtr3_tst1_LOT6);

    } else if( btn->Name == "Btn4_CHK_TITLEREF" ){
        //---------------------------------
    	// �ޗ��ؖ����i���ʁj

        if( iNowTab != 4 ){
			MessageDlg("��Ɂu�o�͓��e�̊m�F�v�{�^���������ĉ������B", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
    		// �߂�l������
			ret_Btn1_OUT_CHECKClick = false;
        	return;
        }

		k = 0;
		for( i = 0; i < iTITLE_Cnt; i++){
			if( Clb4_CHK_TITLE->Checked[i] == true ){
				k++;
			}
		}
        if( k > 6 ){
			MessageDlg("�^�C�g�����o�͏�񂪂U�ȏ�I������Ă��܂��B\n�I���������ĉ������B", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
    		// �߂�l������
			ret_Btn1_OUT_CHECKClick = false;
        	return;
        }

        if( Rdo4_WHR_TYPE1->Checked == true ){
        	sDTKSHIN = Edt4_WHR_DTKSHIN1->Text;
        } else {
        	sDTKSHIN = Edt4_WHR_DTKSHIN2->Text;
        }
        if( sLots->Count <= 0 )	return;
        sLOTNO   = sLots->Strings[0];

        if( Rdo4_WHR_FORMAT_JPN->Checked == true )	iJapanese = true;
        else                                        iJapanese = false;

        iMax		= 6;

	    clb_TITLE	= dynamic_cast<TCheckListBox*>(Clb4_CHK_TITLE);

    	pnl_LOT1[0] = dynamic_cast<TPanel*>(PgCtr4_tst1_Pnl1);
    	pnl_LOT1[1] = dynamic_cast<TPanel*>(PgCtr4_tst1_Pnl2);
    	pnl_LOT1[2] = dynamic_cast<TPanel*>(PgCtr4_tst1_Pnl3);
    	pnl_LOT1[3] = dynamic_cast<TPanel*>(PgCtr4_tst1_Pnl4);
    	pnl_LOT1[4] = dynamic_cast<TPanel*>(PgCtr4_tst1_Pnl5);
    	pnl_LOT1[5] = dynamic_cast<TPanel*>(PgCtr4_tst1_Pnl6);
    	pnl_LOT1[8] = dynamic_cast<TPanel*>(PgCtr4_tst1_Pnl9);

    	edt_LOT1[0] = dynamic_cast<TEdit*>(PgCtr4_tst1_Edt1);
    	edt_LOT1[1] = dynamic_cast<TEdit*>(PgCtr4_tst1_Edt2);
    	edt_LOT1[2] = dynamic_cast<TEdit*>(PgCtr4_tst1_Edt3);
    	edt_LOT1[3] = dynamic_cast<TEdit*>(PgCtr4_tst1_Edt4);
    	edt_LOT1[4] = dynamic_cast<TEdit*>(PgCtr4_tst1_Edt5);
    	edt_LOT1[5] = dynamic_cast<TEdit*>(PgCtr4_tst1_Edt6);


    	rdo_LOT[0] = dynamic_cast<TRadioButton*>(PgCtr4_tst1_LOT4);
    	rdo_LOT[1] = dynamic_cast<TRadioButton*>(PgCtr4_tst1_LOT5);
    	rdo_LOT[2] = dynamic_cast<TRadioButton*>(PgCtr4_tst1_LOT6);

    } else {

   		// �߂�l������
		ret_Btn1_OUT_CHECKClick = false;
    	return;
    }

    // ���b�gNO�p�̃p�l�����B���܂�
    pnl_LOT1[8]->Visible = false;

    // �^�C�g�����ڔԍ������Z�b�g���܂�
    for( i = 0; i < iMax; i++){
        edt_LOT1[i]->Tag     = 0;
        edt_LOT1[i]->Text    = "";
        edt_LOT1[i]->Visible = true;
    }

    k = 0;
    for( i = 0; i < iTITLE_Cnt; i++){
        if( clb_TITLE->Checked[i] == true ){
            sBuf = sTITLE_JPN->Strings[i];

            pnl_LOT1[k]->Caption	= sBuf;
            edt_LOT1[k]->Tag		= iTITLE[i];
            if( iTITLE[i] == 4 ){
                // ���b�gNO�̏ꍇ
                edt_LOT1[k]->Visible	= false;
                pnl_LOT1[8]->Top		= edt_LOT1[k]->Top;
                pnl_LOT1[8]->Left		= edt_LOT1[k]->Left;
                pnl_LOT1[8]->Height		= edt_LOT1[k]->Height;
                pnl_LOT1[8]->Width		= edt_LOT1[k]->Width;
                pnl_LOT1[8]->Visible	= true;
            }
            else {
                edt_LOT1[k]->Visible	= true;
                edt_LOT1[k]->Text		= GetTitleData(sDTKSHIN, sLOTNO, iTITLE[i], iJapanese);
            }

            k++;

            if( k >= iMax ) break;
        }
    }

    // �^�C�g�����ڂ��W���͂U�ɖ����Ȃ����́A���̂��N���A�[���܂�
    for( i = k; i < iMax; i++){
        pnl_LOT1[i]->Caption = "";
    }

    // �������я��i���ʁj�A�ޗ��ؖ����i���ʁj�͂����ŏ����I���B
    if( btn->Name == "Btn2_CHK_TITLEREF" ||
        btn->Name == "Btn4_CHK_TITLEREF" ){
    	return;
    }

    // �O��쐬����TabSheet���폜���܂�
    for( i = 2; i <= pct_LOT->Tag; i++){
        if( btn->Name == "Btn1_CHK_TITLEREF" ){
    		delete PgCtr1_tst[i];
        } else {
    		delete PgCtr3_tst[i];
        }

    }

    // 2�ڈȍ~�̃��b�gTabSheet���쐬���܂�
    for( i = 2; i <= sLots->Count; i++){

		sBuf = IntToStr(i);

        // �^�u�V�[�g�̍쐬
        if( btn->Name == "Btn1_CHK_TITLEREF" ){
			PgCtr1_tst[i]				= new TTabSheet(pct_LOT);
    		PgCtr1_tst[i]->Name			= sTabSheetNM + AnsiString::StringOfChar('0', 2-sBuf.Length()) + sBuf;
        	PgCtr1_tst[i]->Parent		= pct_LOT;
			PgCtr1_tst[i]->PageControl	= pct_LOT;
        	PgCtr1_tst[i]->Caption		= sLots->Strings[i-1];
			PgCtr1_tst[i]->TabVisible	= true;
        } else {
			PgCtr3_tst[i]				= new TTabSheet(pct_LOT);
    		PgCtr3_tst[i]->Name			= sTabSheetNM + AnsiString::StringOfChar('0', 2-sBuf.Length()) + sBuf;
        	PgCtr3_tst[i]->Parent		= pct_LOT;
			PgCtr3_tst[i]->PageControl	= pct_LOT;
        	PgCtr3_tst[i]->Caption		= sLots->Strings[i-1];
			PgCtr3_tst[i]->TabVisible	= true;
        }


	    for( k = 0; k <= 8; k++){
			sBuf2 = IntToStr(k);

			// ���x���̍쐬
        	if( btn->Name == "Btn1_CHK_TITLEREF" ){
        		PgCtr1_tst_Pnl[i][k]			= new TPanel(PgCtr1_tst[i]);
            	PgCtr1_tst_Pnl[i][k]->Name		= sTabSheetNM	+ AnsiString::StringOfChar('0', 2-sBuf.Length()) + sBuf +
            									  "_Pnl"		+ AnsiString::StringOfChar('0', 2-sBuf2.Length()) + sBuf2;
            	PgCtr1_tst_Pnl[i][k]->Parent	= PgCtr1_tst[i];
	            pnl_DUMMY = dynamic_cast<TPanel*>(PgCtr1_tst_Pnl[i][k]);
            } else {
        		PgCtr3_tst_Pnl[i][k]			= new TPanel(PgCtr3_tst[i]);
            	PgCtr3_tst_Pnl[i][k]->Name		= sTabSheetNM	+ AnsiString::StringOfChar('0', 2-sBuf.Length()) + sBuf +
            									  "_Pnl"		+ AnsiString::StringOfChar('0', 2-sBuf2.Length()) + sBuf2;
            	PgCtr3_tst_Pnl[i][k]->Parent	= PgCtr3_tst[i];
	            pnl_DUMMY = dynamic_cast<TPanel*>(PgCtr3_tst_Pnl[i][k]);
            }
           	pnl_DUMMY->Caption		= pnl_LOT1[k]->Caption;
           	pnl_DUMMY->Top			= pnl_LOT1[k]->Top;
           	pnl_DUMMY->Left			= pnl_LOT1[k]->Left;
           	pnl_DUMMY->Height		= pnl_LOT1[k]->Height;
           	pnl_DUMMY->Width		= pnl_LOT1[k]->Width;
           	pnl_DUMMY->Enabled		= pnl_LOT1[k]->Enabled;
           	pnl_DUMMY->Font			= pnl_LOT1[k]->Font;
           	pnl_DUMMY->Color		= pnl_LOT1[k]->Color;
           	pnl_DUMMY->BevelInner	= pnl_LOT1[k]->BevelInner;
           	pnl_DUMMY->BevelOuter	= pnl_LOT1[k]->BevelOuter;
           	pnl_DUMMY->Visible		= pnl_LOT1[k]->Visible;

			// �e�L�X�g�{�b�N�X�̍쐬
            if( k < 8 ){
        		if( btn->Name == "Btn1_CHK_TITLEREF" ){
        			PgCtr1_tst_Edt[i][k]			= new TEdit(PgCtr1_tst[i]);
            		PgCtr1_tst_Edt[i][k]->Name		= sTabSheetNM	+ AnsiString::StringOfChar('0', 2-sBuf.Length()) + sBuf +
            										  "_Edt"		+ AnsiString::StringOfChar('0', 2-sBuf2.Length()) + sBuf2;
            		PgCtr1_tst_Edt[i][k]->Parent	= PgCtr1_tst[i];
            		PgCtr1_tst_Edt[i][k]->OnEnter	= FormEnter;
            		PgCtr1_tst_Edt[i][k]->OnKeyDown	= FormKeyDown;
            		PgCtr1_tst_Edt[i][k]->OnKeyPress= FormKeyPress;
            		PgCtr1_tst_Edt[i][k]->OnChange	= Edt_ALLChange;
                    PgCtr1_tst_Edt[i][k]->OnExit	= Edt_iTITLE5_Exit;
                    edt_DUMMY = dynamic_cast<TEdit*>(PgCtr1_tst_Edt[i][k]);
                	sLOTNO = PgCtr1_tst[i]->Caption;
            	} else {
        			PgCtr3_tst_Edt[i][k]			= new TEdit(PgCtr3_tst[i]);
            		PgCtr3_tst_Edt[i][k]->Name		= sTabSheetNM	+ AnsiString::StringOfChar('0', 2-sBuf.Length()) + sBuf +
            										  "_Edt"		+ AnsiString::StringOfChar('0', 2-sBuf2.Length()) + sBuf2;
            		PgCtr3_tst_Edt[i][k]->Parent	= PgCtr3_tst[i];
            		PgCtr3_tst_Edt[i][k]->OnEnter	= FormEnter;
            		PgCtr3_tst_Edt[i][k]->OnKeyDown	= FormKeyDown;
            		PgCtr3_tst_Edt[i][k]->OnKeyPress= FormKeyPress;
            		PgCtr3_tst_Edt[i][k]->OnChange	= Edt_ALLChange;
                    PgCtr3_tst_Edt[i][k]->OnExit	= Edt_iTITLE5_Exit;
                    edt_DUMMY = dynamic_cast<TEdit*>(PgCtr3_tst_Edt[i][k]);
                	sLOTNO = PgCtr3_tst[i]->Caption;
                }
                edt_DUMMY->Top		= edt_LOT1[k]->Top;
                edt_DUMMY->Left		= edt_LOT1[k]->Left;
                edt_DUMMY->Height	= edt_LOT1[k]->Height;
                edt_DUMMY->Width	= edt_LOT1[k]->Width;
                edt_DUMMY->Enabled	= edt_LOT1[k]->Enabled;
                edt_DUMMY->Font		= edt_LOT1[k]->Font;
                edt_DUMMY->Visible	= edt_LOT1[k]->Visible;
           	    edt_DUMMY->Tag		= edt_LOT1[k]->Tag;
                edt_DUMMY->Text		= GetTitleData(sDTKSHIN, sLOTNO, edt_LOT1[k]->Tag, iJapanese);
            }
            else {

                // ���b�gNo�I��p�I�v�V�����{�b�N�X�̍쐬
				for( m = 0; m < 3; m++){
       	        	if( btn->Name == "Btn1_CHK_TITLEREF" ){
						PgCtr1_tst_LOT[i][m]			= new TRadioButton(PgCtr1_tst_Pnl[i][k]);
						PgCtr1_tst_LOT[i][m]->Name		= sTabSheetNM	+ AnsiString::StringOfChar('0', 2-sBuf.Length())
														  + sBuf + "_LOT" + IntToStr(m+4);
						PgCtr1_tst_LOT[i][m]->Parent	= PgCtr1_tst_Pnl[i][k];
						rdo_DUMMY = dynamic_cast<TRadioButton*>(PgCtr1_tst_LOT[i][m]);
                	} else {
						PgCtr3_tst_LOT[i][m]			= new TRadioButton(PgCtr3_tst_Pnl[i][k]);
						PgCtr3_tst_LOT[i][m]->Name		= sTabSheetNM	+ AnsiString::StringOfChar('0', 2-sBuf.Length())
														  + sBuf + "_LOT" + IntToStr(m+4);
						PgCtr3_tst_LOT[i][m]->Parent	= PgCtr3_tst_Pnl[i][k];
						rdo_DUMMY = dynamic_cast<TRadioButton*>(PgCtr3_tst_LOT[i][m]);
                    }
					rdo_DUMMY->Caption	= rdo_LOT[m]->Caption;
               		rdo_DUMMY->Top		= rdo_LOT[m]->Top;
               		rdo_DUMMY->Left		= rdo_LOT[m]->Left;
               		rdo_DUMMY->Height	= rdo_LOT[m]->Height;
               		rdo_DUMMY->Width	= rdo_LOT[m]->Width;
               		rdo_DUMMY->Enabled	= rdo_LOT[m]->Enabled;
               		rdo_DUMMY->Font		= rdo_LOT[m]->Font;
               		rdo_DUMMY->Color	= rdo_LOT[m]->Color;
               		rdo_DUMMY->Checked	= rdo_LOT[m]->Checked;
				}

            }

        }

    }

    // ���I�쐬����TabSheet�̌����i�[���܂�
    pct_LOT->Tag = sLots->Count;

	return;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�\�����̓��e�𑼂̃��b�g�ɔ��f���v�{�^�������������̏���
//
//  �@�\����
//    �\�����ꂽ���b�g���̃^�C�g�����o�͏��ɑ΂���
//    �\������Ă��郍�b�g�̃^�C�g�����o�͏���
//    ���̃��b�g�̃^�C�g�����o�͏��ɃR�s�[���܂�
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
void __fastcall TForm1::Btn1_CHK_TITLECOPYClick(TObject *Sender)
{

    int			i, k;
	int			iPageNo;
    int			iNotCopyNo;
    AnsiString  sBuf[8];
    bool		iBuf[3];

    TButton* 		btn = dynamic_cast<TButton*>(Sender);
    iNotCopyNo = -1;

    if( btn->Name == "Btn1_CHK_TITLECOPY" ){
        //---------------------------------
    	// �������я�

        if( iNowTab != 1 ){
			MessageDlg("��Ɂu�o�͓��e�̊m�F�v�{�^���������ĉ������B", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
        	return;
        }

        // ���ʌ��̒l���i�[���܂�
        iPageNo = PgCtr1_LOT->ActivePage->PageIndex;
        if( iPageNo == 0 ){
        	sBuf[0] = PgCtr1_tst1_Edt1->Text;
        	sBuf[1] = PgCtr1_tst1_Edt2->Text;
        	sBuf[2] = PgCtr1_tst1_Edt3->Text;
        	sBuf[3] = PgCtr1_tst1_Edt4->Text;
        	sBuf[4] = PgCtr1_tst1_Edt5->Text;
        	sBuf[5] = PgCtr1_tst1_Edt6->Text;
        	sBuf[6] = PgCtr1_tst1_Edt7->Text;
        	sBuf[7] = PgCtr1_tst1_Edt8->Text;
            iBuf[0] = PgCtr1_tst1_LOT4->Checked;
            iBuf[1] = PgCtr1_tst1_LOT5->Checked;
            iBuf[2] = PgCtr1_tst1_LOT6->Checked;
            if( PgCtr1_tst1_Edt1->Tag == 6 )	iNotCopyNo = 0;
            if( PgCtr1_tst1_Edt2->Tag == 6 )	iNotCopyNo = 1;
            if( PgCtr1_tst1_Edt3->Tag == 6 )	iNotCopyNo = 2;
            if( PgCtr1_tst1_Edt4->Tag == 6 )	iNotCopyNo = 3;
            if( PgCtr1_tst1_Edt5->Tag == 6 )	iNotCopyNo = 4;
            if( PgCtr1_tst1_Edt6->Tag == 6 )	iNotCopyNo = 5;
            if( PgCtr1_tst1_Edt7->Tag == 6 )	iNotCopyNo = 6;
            if( PgCtr1_tst1_Edt8->Tag == 6 )	iNotCopyNo = 7;
        } else {
            for( i = 0; i < 8; i++ ){
        		sBuf[i] = PgCtr1_tst_Edt[iPageNo+1][i]->Text;
            	if( PgCtr1_tst_Edt[iPageNo+1][i]->Tag == 6 )	iNotCopyNo = i;
            }
            for( i = 0; i < 3; i++ ){
        		iBuf[i] = PgCtr1_tst_LOT[iPageNo+1][i]->Checked;
            }
        }

        // ���ʐ�փR�s�[���J�n���܂�
        for( k = 0; k < PgCtr1_LOT->PageCount; k++ ){
            if( k == iPageNo )	continue;
        	if( k == 0 ){
            	if( iNotCopyNo != 0 )	PgCtr1_tst1_Edt1->Text = sBuf[0];
        		if( iNotCopyNo != 1 )	PgCtr1_tst1_Edt2->Text = sBuf[1];
        		if( iNotCopyNo != 2 )	PgCtr1_tst1_Edt3->Text = sBuf[2];
        		if( iNotCopyNo != 3 )	PgCtr1_tst1_Edt4->Text = sBuf[3];
        		if( iNotCopyNo != 4 )	PgCtr1_tst1_Edt5->Text = sBuf[4];
        		if( iNotCopyNo != 5 )	PgCtr1_tst1_Edt6->Text = sBuf[5];
        		if( iNotCopyNo != 6 )	PgCtr1_tst1_Edt7->Text = sBuf[6];
        		if( iNotCopyNo != 7 )	PgCtr1_tst1_Edt8->Text = sBuf[7];
        		PgCtr1_tst1_LOT4->Checked = iBuf[0];
        		PgCtr1_tst1_LOT5->Checked = iBuf[1];
        		PgCtr1_tst1_LOT6->Checked = iBuf[2];
        	} else {
            	for( i = 0; i < 8; i++ ){
        			if( iNotCopyNo != i )	PgCtr1_tst_Edt[k+1][i]->Text = sBuf[i];
            	}
            	for( i = 0; i < 3; i++ ){
        			PgCtr1_tst_LOT[k+1][i]->Checked	= iBuf[i];
            	}
        	}
        }

    }

    if( btn->Name == "Btn3_CHK_TITLECOPY" ){
        //---------------------------------
    	// �ޗ��ؖ���

        if( iNowTab != 3 ){
			MessageDlg("��Ɂu�o�͓��e�̊m�F�v�{�^���������ĉ������B", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
        	return;
        }

        // ���ʌ��̒l���i�[���܂�
        iPageNo = PgCtr3_LOT->ActivePage->PageIndex;
        if( iPageNo == 0 ){
        	sBuf[0] = PgCtr3_tst1_Edt1->Text;
        	sBuf[1] = PgCtr3_tst1_Edt2->Text;
        	sBuf[2] = PgCtr3_tst1_Edt3->Text;
        	sBuf[3] = PgCtr3_tst1_Edt4->Text;
        	sBuf[4] = PgCtr3_tst1_Edt5->Text;
        	sBuf[5] = PgCtr3_tst1_Edt6->Text;
        	sBuf[6] = PgCtr3_tst1_Edt7->Text;
        	sBuf[7] = PgCtr3_tst1_Edt8->Text;
            iBuf[0] = PgCtr3_tst1_LOT4->Checked;
            iBuf[1] = PgCtr3_tst1_LOT5->Checked;
            iBuf[2] = PgCtr3_tst1_LOT6->Checked;
            if( PgCtr3_tst1_Edt1->Tag == 6 )	iNotCopyNo = 0;
            if( PgCtr3_tst1_Edt2->Tag == 6 )	iNotCopyNo = 1;
            if( PgCtr3_tst1_Edt3->Tag == 6 )	iNotCopyNo = 2;
            if( PgCtr3_tst1_Edt4->Tag == 6 )	iNotCopyNo = 3;
            if( PgCtr3_tst1_Edt5->Tag == 6 )	iNotCopyNo = 4;
            if( PgCtr3_tst1_Edt6->Tag == 6 )	iNotCopyNo = 5;
            if( PgCtr3_tst1_Edt7->Tag == 6 )	iNotCopyNo = 6;
            if( PgCtr3_tst1_Edt8->Tag == 6 )	iNotCopyNo = 7;
        } else {
            for( i = 0; i < 8; i++ ){
                sBuf[i] = PgCtr3_tst_Edt[iPageNo+1][i]->Text;
        		if( PgCtr3_tst_Edt[iPageNo+1][i]->Tag == 6 )	iNotCopyNo = i;
            }
            for( i = 0; i < 3; i++ ){
        		iBuf[i] = PgCtr3_tst_LOT[iPageNo+1][i]->Checked;
            }
        }

        // ���ʐ�փR�s�[���J�n���܂�
        for( k = 0; k < PgCtr3_LOT->PageCount; k++ ){
            if( k == iPageNo )	continue;
        	if( k == 0 ){
        		if( iNotCopyNo != 0 )	PgCtr3_tst1_Edt1->Text = sBuf[0];
        		if( iNotCopyNo != 1 )	PgCtr3_tst1_Edt2->Text = sBuf[1];
        		if( iNotCopyNo != 2 )	PgCtr3_tst1_Edt3->Text = sBuf[2];
        		if( iNotCopyNo != 3 )	PgCtr3_tst1_Edt4->Text = sBuf[3];
        		if( iNotCopyNo != 4 )	PgCtr3_tst1_Edt5->Text = sBuf[4];
        		if( iNotCopyNo != 5 )	PgCtr3_tst1_Edt6->Text = sBuf[5];
        		if( iNotCopyNo != 6 )	PgCtr3_tst1_Edt7->Text = sBuf[6];
        		if( iNotCopyNo != 7 )	PgCtr3_tst1_Edt8->Text = sBuf[7];
        		PgCtr3_tst1_LOT4->Checked	= iBuf[0];
        		PgCtr3_tst1_LOT5->Checked	= iBuf[1];
        		PgCtr3_tst1_LOT6->Checked	= iBuf[2];
        	} else {
            	for( i = 0; i < 8; i++ ){
        			if( iNotCopyNo != i )	PgCtr3_tst_Edt[k+1][i]->Text = sBuf[i];
            	}
            	for( i = 0; i < 3; i++ ){
        			PgCtr3_tst_LOT[k+1][i]->Checked	= iBuf[i];
            	}
        	}
        }

    }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnExit�C�x���g	�F���̓t�H�[�J�X���R���g���[������ʂ̃R���g���[���ֈڂ����Ƃ��ɔ���
//
//  �@�\����
//    �[�����̂��߂ɁA��P�ʂ�,�������ݒ肵�܂�
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
void __fastcall TForm1::Edt_iTITLE5_Exit(TObject *Sender)
{
    AnsiString	sBuf;
    int			i;
    TEdit* 		edt = dynamic_cast<TEdit*>(Sender);

    if( edt->Tag != 5 )	return;

    sBuf = "";

    for( i = 1; i <= edt->Text.Length() ; i++){
		if( strcspn( edt->Text.SubString(i,1).c_str(), "-0123456789" ) != 0 ) {
        } else{
            sBuf = sBuf + edt->Text.SubString(i,1);
        }
    }

    edt->Text = FormatFloat("#,##0", (double)sBuf.ToIntDef(0));

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnKeyDown�C�x���g	�F���[�U�[���C�ӂ̃L�[�������Ɣ������܂�
//
//  �@�\����
//    �t�@���N�V�����L�[�ɂ��{�^����I�����܂�
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    WORD &Key			�F�L�[�R�[�h
//    TShiftState Shift	�F[Shift]�C[Alt]�C[Ctrl]�L�[�𔻒肵�܂�
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     switch(Key) {
         case VK_F1:  BtnF01Click(BtnF01);		break;
         case VK_F2:  BtnF02Click(BtnF02);		break;
         case VK_F3:  BtnF03Click(BtnF03);		break;
         case VK_F5:  BtnF05Click(BtnF05);		break;
         case VK_F7:  BtnF07Click(BtnF07);		break;
         case VK_F9:  BtnF09Click(BtnF09);		break;
         case VK_F10: BtnF10Click(BtnF10);		break;
         case VK_F12: BtnF12Click(BtnF12);		break;
         case VK_RETURN:
                    if( Memo1_CHK_REMARK->Focused() ||
                    	Memo2_CHK_REMARK->Focused() ||
                    	Memo3_CHK_REMARK->Focused() ||
                    	Memo4_CHK_REMARK->Focused() ){
                    	break;
                    }
               		keybd_event(VK_TAB,0,0,0);
                	keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
     }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u��������̎w��v���W�I�{�^�������������̏���
//
//  �@�\����
//    �I�����ꂽ���W�I�{�^���𔻒f���A
//    �ΏۂƂȂ郉�x���A�e�L�X�g�{�b�N�X�̗L���^������ݒ肵�܂�
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
void __fastcall TForm1::Rdo2_WHR_TYPE1Click(TObject *Sender)
{

    TRadioButton* rdo = dynamic_cast<TRadioButton*>(Sender);

    // �������я��i���ʁj
    if( rdo->Name == "Rdo2_WHR_TYPE1" && rdo->Checked == true ){
        // ON
        Pnl2_WHR_DTKSHIN1->Color	= (TColor)0x00FEE7BA;
        Pnl2_WHR_LOTNO1->Color		= (TColor)0x00FEE7BA;
        Edt2_WHR_DTKSHIN1->Color	= (TColor)clWindow;
        Edt2_WHR_LOTNO1->Color		= (TColor)clWindow;
        Edt2_WHR_DTKSHIN1->Enabled	= true;
        Edt2_WHR_LOTNO1->Enabled	= true;
        // OFF
        Pnl2_WHR_DTKSHIN2->Color	= (TColor)clSilver;
        Pnl2_WHR_SYUKADATE->Color	= (TColor)clSilver;
        Edt2_WHR_DTKSHIN2->Color	= (TColor)clSilver;
        Edt2_WHR_SYUKADATE1->Color	= (TColor)clSilver;
        Edt2_WHR_SYUKADATE2->Color	= (TColor)clSilver;
        Edt2_WHR_DTKSHIN2->Enabled	= false;
        Edt2_WHR_SYUKADATE1->Enabled= false;
        Edt2_WHR_SYUKADATE2->Enabled= false;
    }
    if( rdo->Name == "Rdo2_WHR_TYPE2" && rdo->Checked == true ){
        // OFF
        Pnl2_WHR_DTKSHIN1->Color	= (TColor)clSilver;
        Pnl2_WHR_LOTNO1->Color		= (TColor)clSilver;
        Edt2_WHR_DTKSHIN1->Color	= (TColor)clSilver;
        Edt2_WHR_LOTNO1->Color		= (TColor)clSilver;
        Edt2_WHR_DTKSHIN1->Enabled	= false;
        Edt2_WHR_LOTNO1->Enabled	= false;
        // ON
        Pnl2_WHR_DTKSHIN2->Color	= (TColor)0x00FEE7BA;
        Pnl2_WHR_SYUKADATE->Color	= (TColor)0x00FEE7BA;
        Edt2_WHR_DTKSHIN2->Color	= (TColor)clWindow;
        Edt2_WHR_SYUKADATE1->Color	= (TColor)clWindow;
        Edt2_WHR_SYUKADATE2->Color	= (TColor)clWindow;
        Edt2_WHR_DTKSHIN2->Enabled	= true;
        Edt2_WHR_SYUKADATE1->Enabled= true;
        Edt2_WHR_SYUKADATE2->Enabled= true;
    }

    // �������я��i���ʁj
    if( rdo->Name == "Rdo4_WHR_TYPE1" && rdo->Checked == true ){
        // ON
        Pnl4_WHR_DTKSHIN1->Color	= (TColor)0x00FEE7BA;
        Pnl4_WHR_LOTNO1->Color		= (TColor)0x00FEE7BA;
        Edt4_WHR_DTKSHIN1->Color	= (TColor)clWindow;
        Edt4_WHR_LOTNO1->Color		= (TColor)clWindow;
        Edt4_WHR_DTKSHIN1->Enabled	= true;
        Edt4_WHR_LOTNO1->Enabled	= true;
        // OFF
        Pnl4_WHR_DTKSHIN2->Color	= (TColor)clSilver;
        Pnl4_WHR_SYUKADATE->Color	= (TColor)clSilver;
        Edt4_WHR_DTKSHIN2->Color	= (TColor)clSilver;
        Edt4_WHR_SYUKADATE1->Color	= (TColor)clSilver;
        Edt4_WHR_SYUKADATE2->Color	= (TColor)clSilver;
        Edt4_WHR_DTKSHIN2->Enabled	= false;
        Edt4_WHR_SYUKADATE1->Enabled= false;
        Edt4_WHR_SYUKADATE2->Enabled= false;
    }
    if( rdo->Name == "Rdo4_WHR_TYPE2" && rdo->Checked == true ){
        // OFF
        Pnl4_WHR_DTKSHIN1->Color	= (TColor)clSilver;
        Pnl4_WHR_LOTNO1->Color		= (TColor)clSilver;
        Edt4_WHR_DTKSHIN1->Color	= (TColor)clSilver;
        Edt4_WHR_LOTNO1->Color		= (TColor)clSilver;
        Edt4_WHR_DTKSHIN1->Enabled	= false;
        Edt4_WHR_LOTNO1->Enabled	= false;
        // ON
        Pnl4_WHR_DTKSHIN2->Color	= (TColor)0x00FEE7BA;
        Pnl4_WHR_SYUKADATE->Color	= (TColor)0x00FEE7BA;
        Edt4_WHR_DTKSHIN2->Color	= (TColor)clWindow;
        Edt4_WHR_SYUKADATE1->Color	= (TColor)clWindow;
        Edt4_WHR_SYUKADATE2->Color	= (TColor)clWindow;
        Edt4_WHR_DTKSHIN2->Enabled	= true;
        Edt4_WHR_SYUKADATE1->Enabled= true;
        Edt4_WHR_SYUKADATE2->Enabled= true;
    }


    // ���n��Ǘ��\
    if( rdo->Name == "Rdo5_WHR_TYPE1" && rdo->Checked == true ){
        // ON
        Pnl5_WHR_LOTNO->Color		= (TColor)0x00FEE7BA;
        Edt5_WHR_LOTNO->Color		= (TColor)clWindow;
        Edt5_WHR_LOTNO->Enabled	= true;
        // OFF
        Pnl5_WHR_SYUKADATE->Color	= (TColor)clSilver;
        Edt5_WHR_SYUKADATE1->Color	= (TColor)clSilver;
        Edt5_WHR_SYUKADATE2->Color	= (TColor)clSilver;
        Edt5_WHR_SYUKADATE1->Enabled= false;
        Edt5_WHR_SYUKADATE2->Enabled= false;
    }
    if( rdo->Name == "Rdo5_WHR_TYPE2" && rdo->Checked == true ){
        // OFF
        Pnl5_WHR_LOTNO->Color		= (TColor)clSilver;
        Edt5_WHR_LOTNO->Color		= (TColor)clSilver;
        Edt5_WHR_LOTNO->Enabled	= false;
        // ON
        Pnl5_WHR_SYUKADATE->Color	= (TColor)0x00FEE7BA;
        Edt5_WHR_SYUKADATE1->Color	= (TColor)clWindow;
        Edt5_WHR_SYUKADATE2->Color	= (TColor)clWindow;
        Edt5_WHR_SYUKADATE1->Enabled= true;
        Edt5_WHR_SYUKADATE2->Enabled= true;
    }


    // �����o��[
    if( rdo->Name == "Rdo6_WHR_TYPE1" && rdo->Checked == true ){
        // ON
        Pnl6_WHR_DTKSHIN1->Color	= (TColor)0x00FEE7BA;
        Pnl6_WHR_LOTNO1->Color		= (TColor)0x00FEE7BA;
        Edt6_WHR_DTKSHIN1->Color	= (TColor)clWindow;
        Edt6_WHR_LOTNO1->Color		= (TColor)clWindow;
        Edt6_WHR_DTKSHIN1->Enabled	= true;
        Edt6_WHR_LOTNO1->Enabled	= true;
        // OFF
        Pnl6_WHR_KENSADATE->Color	= (TColor)clSilver;
        Edt6_WHR_KENSADATE1->Color	= (TColor)clSilver;
        Edt6_WHR_KENSADATE2->Color	= (TColor)clSilver;
        Edt6_WHR_KENSADATE1->Enabled= false;
        Edt6_WHR_KENSADATE2->Enabled= false;
        // ON
        Pnl6_CHK_HINMEI->Color		= (TColor)0x00FEE7BA;
        Pnl6_CHK_HINSYU->Color		= (TColor)0x00FEE7BA;
        Pnl6_CHK_KOUMOKU->Color		= (TColor)0x00FEE7BA;
        Edt6_CHK_HINMEI->Color		= (TColor)clWindow;
        Edt6_CHK_HINSYU->Color		= (TColor)clWindow;
        Clb6_CHK_KOUMOKU->Color		= (TColor)clWindow;
        Edt6_CHK_HINMEI->Enabled	= true;
        Edt6_CHK_HINSYU->Enabled	= true;
        Clb6_CHK_KOUMOKU->Enabled	= true;

		Pnl6_LOTNO_OUT->Caption		= "�o�͑Ώۂ̃��b�g";
    }
    if( rdo->Name == "Rdo6_WHR_TYPE2" && rdo->Checked == true ){
        // OFF
        Pnl6_WHR_DTKSHIN1->Color	= (TColor)clSilver;
        Pnl6_WHR_LOTNO1->Color		= (TColor)clSilver;
        Edt6_WHR_DTKSHIN1->Color	= (TColor)clSilver;
        Edt6_WHR_LOTNO1->Color		= (TColor)clSilver;
        Edt6_WHR_DTKSHIN1->Enabled	= false;
        Edt6_WHR_LOTNO1->Enabled	= false;
        // ON
        Pnl6_WHR_KENSADATE->Color	= (TColor)0x00FEE7BA;
        Edt6_WHR_KENSADATE1->Color	= (TColor)clWindow;
        Edt6_WHR_KENSADATE2->Color	= (TColor)clWindow;
        Edt6_WHR_KENSADATE1->Enabled= true;
        Edt6_WHR_KENSADATE2->Enabled= true;
        // OFF
        Pnl6_CHK_HINMEI->Color		= (TColor)clSilver;
        Pnl6_CHK_HINSYU->Color		= (TColor)clSilver;
        Pnl6_CHK_KOUMOKU->Color		= (TColor)clSilver;
        Edt6_CHK_HINMEI->Color		= (TColor)clSilver;
        Edt6_CHK_HINSYU->Color		= (TColor)clSilver;
        Clb6_CHK_KOUMOKU->Color		= (TColor)clSilver;
        Edt6_CHK_HINMEI->Enabled	= false;
        Edt6_CHK_HINSYU->Enabled	= false;
        Clb6_CHK_KOUMOKU->Enabled	= false;

		Pnl6_LOTNO_OUT->Caption		= "�o�͑Ώۂ̕i�ԥۯ�";
    }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�^�C�g�����o�͏��v
//    ���[�U�[�����ڂ̃`�F�b�N�{�b�N�X��I���܂��͑I�����������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �^�C�g�����o�͏��̍��ڑI�𐔂𐧌����܂��B
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
void __fastcall TForm1::Clb_CHK_TITLEClickCheck(TObject *Sender)
{

    int		i, k;
    int		iMax;
    TCheckListBox*	clb = dynamic_cast<TCheckListBox*>(Sender);

    if( clb->Name == "Clb2_CHK_TITLE" || clb->Name == "Clb4_CHK_TITLE" ){
        // �������я��i���ʁj
        // �ޗ��ؖ����i���ʁj
    	iMax = 8;
    } else {
        // �������я�
        // �ޗ��ؖ���
    	iMax = 8;
    }

    k = 0;
    for( i = 0; i < iTITLE_Cnt; i++){
        if( clb->Checked[i] == true ){
            k++;
        }
    }

    if( k > iMax ){
    	clb->Checked[clb->ItemIndex] = false;
    } else {
        // �f�[�^�ύX�t���O�̐ݒ�
        // DataChange = 1;
    }

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�w������ł̌�������
//
//  �@�\����
//    �w�肳�ꂽ�i�ԁE���b�gNo
//    �w�肳�ꂽ�i�ԁE���t�i�o�ד����͌������j
//    �w�肳�ꂽ������
//    ������ς݂��ǂ������f���܂��B
//    �������ꂽ����ς݃��b�g���L�����ꍇ�A���荀�ڈꗗ���쐬���܂�
//
//  �p�����^����
//    int		iType	�F1 = �i�ԁE���b�g�ɂ�錟��
//                        2 = �i�ԁE�o�ד��ɂ�錟��
//                        3 = �������ɂ�錟��
//                        4 = �i�ԁE���b�g�ɂ�錟��(������̃��b�g�o��)//2003.08.28 E.Takase
//    TEdit		*edtA	�F��\���Ӑ�i�Ԃ��w�肳��Ă���TEdit
//    TEdit		*edtB	�F���b�gNO���w�肳��Ă���TEdit
//    TMaskEdit	*edtC	�F���t�͈́i�J�n�j
//    TMaskEdit	*edtD	�F���t�͈́i�I���j
//    bool		iSEL_SZ	�F�f�ތ������ڂ̏o�́itrue=����/false=���Ȃ��j
//    bool		iSEL_SK	�F�o�׌������ڂ̏o�́itrue=����/false=���Ȃ��j
//    int		iSEL_TK	�F���ʏo�͍��ڂ̏o�́itrue=����/false=���Ȃ��j
//    bool		iSEL_ZR	�F�ޗ��ؖ����ڂ̏o�́itrue=����/false=���Ȃ��j
//
//  �߂�l
//    bool				�Ftrue=���������Afalse=�������s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::Get_DTKSHIN_LOT(int iType, TEdit *edtA, TEdit *edtB,
					TMaskEdit *edtC, TMaskEdit *edtD, bool iSEL_SZ, bool iSEL_SK, int iSEL_TK, bool iSEL_ZR)
{

	int			i1,iCount/*,iOldCol*/;
	int			iCnt,iCnt2;
	AnsiString	sDTKSHIN;
	AnsiString	sLot;
    AnsiString	sDate1, sDate2;
	AnsiString	sLot1,sLot2,sCmpStr,sBuf,sAllLot;
	bool		bKikanF[100];
	AnsiString	sRots[100];

    //2003/08/28 E.Takase
    //if( iType == 1 || iType == 2 ){
    if( iType == 1 || iType == 2  || iType == 4 ){
    	sDTKSHIN	= edtA->Text;

		// �i�ԓ��̓`�F�b�N
		if( sDTKSHIN.Length() == 0 || sDTKSHIN.Trim() == "" ){
			MessageDlg("���Ӑ�i�Ԃ̎w�肪����������܂���B", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
			edtA->SetFocus();
			return( false );
    	}
	}


    //2003/08/28 E.Takase
    //if( iType == 1 ){
    if( iType == 1 || iType == 4 ){
        //----------------------------------------
        // �i�ԁE���b�g�ł̌��������s���܂�

		sLot = edtB->Text;

		// ���b�g���̓`�F�b�N
		if( sLot.Length() == 0 || sLot.Trim() == "" ){
			MessageDlg("���b�g�̎w�肪����������܂���B", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
			edtB->SetFocus();
			return( false );
		}

//2003/12/02 E.Takase
/*
		// ���̓��b�g�ɋ֑��������Ȃ���
		for( i1=1; i1<=sLot.Length(); i1++) {
			if( strcspn(sLot.SubString(i1,1).c_str(),"0123456789xyzXYZ -,")!=0) {
				MessageDlg("���b�g���͂�����������܂���B", mtWarning,
							TMsgDlgButtons() << mbOK , 0);
				edtB->SetFocus();
				return( false );
				//break;
			}
		}

		// �������������̊m�F
		for( i1=1; i1<=sLot.Length(); i1++) {
			if( strcspn(sLot.SubString(i1,1).c_str(),"0123456789")==0) {
			iCount = 1;
				i1++;
				while(strcspn(sLot.SubString(i1,1).c_str(),"0123456789")==0) {
					iCount++;
					i1++;
					if(i1 > sLot.Length()) break;
				}
				if(iCount < 3 || iCount > 6) {
					MessageDlg("���b�g���͂�����������܂���B", mtWarning,
								TMsgDlgButtons() << mbOK , 0);
					edtB->SetFocus();
					return( false );
				}
			}
		}

		//�������͂̊m�F(X,Y,Z)
		for( i1=1; i1<=sLot.Length(); i1++) {
			if( strcspn(sLot.SubString(i1,1).c_str(),"XYZxyz")==0) {
				iCount = 0;
				i1++;
				while(strcspn(sLot.SubString(i1,1).c_str(),"0123456789")==0) {
					iCount++;
					i1++;
					if(i1 > sLot.Length()) break;
				}
				if(iCount < 3 || iCount > 5) {
					MessageDlg("���b�g���͂�����������܂���B", mtWarning,
								TMsgDlgButtons() << mbOK , 0);
					edtB->SetFocus();
					return( false );
				}
			}
		}

		//�Ԑڎq�̑Ó����m�F
		for( i1=1; i1<=sLot.Length(); i1++) {
			if( strcspn(sLot.SubString(i1,1).c_str(),"-,")==0) {
				i1++;
				while(1) {
					if(strcspn(sLot.SubString(i1,1).c_str(),"0123456789XYZxyz")==0) {
						i1++;
						break;
					}
					if(strcspn(sLot.SubString(i1,1).c_str(),",-")==0) {
						MessageDlg("���b�g���͂�����������܂���B", mtWarning,
									TMsgDlgButtons() << mbOK , 0);
						edtB->SetFocus();
						return( false );
					}
					i1++;
					if(i1 > sLot.Length()) break;
				}
			}
		}

*/
//2003/12/02 E.Takase

		//���b�g�̐؂�o���i�ʓ��́A��ԓ��͑Ή����邱�Ɓj
		//�����̐؂�o��
		//���b�g���̓ǂݏo���isLots[]�֑��)
		iCnt = 0;
		for( i1=1; i1<=sLot.Length(); i1++) {
			if( strcspn(sLot.SubString(i1,1).c_str(),"0123456789XYZxyz")==0) {
				iCount = 1;
				i1++;
				while(strcspn(sLot.SubString(i1,1).c_str(),"-, ")!=0) {
					i1++;
					iCount ++;
					if(i1 > sLot.Length()) break;
				}
				sRots[iCnt]=sLot.SubString(i1-iCount,iCount);
				iCnt ++;
				if( iCnt > 99 ) {                                             //onishi99
					MessageDlg("���b�g�w��͈͂��������܂��B", mtWarning,
								TMsgDlgButtons() << mbOK , 0);
					edtB->SetFocus();
					return( false );
				}
			}
		}

		//���b�g�����i�͈�OR�ʁj�t���O���
		iCnt2 = 0;
		for( i1=1; i1<=sLot.Length(); i1++) {
			while( strcspn(sLot.SubString(i1,1).c_str(),"0123456789XYZxyz")==0
				&& (i1 < sLot.Length()) ) {
				i1+=sRots[iCnt2].Length();
				bKikanF[iCnt2]=false;
				while( strcspn(sLot.SubString(i1,1).c_str(),"0123456789XYZxyz")!=0
					&& (i1 < sLot.Length()) ) {
					if(strcspn(sLot.SubString(i1,1).c_str(),"-")==0) {
						bKikanF[iCnt2] = true;
						break;
					}
					i1++;
				}
				iCnt2++;
			}
		}
		iCnt2 -= 1;
		bKikanF[iCnt2] = false;

        // ���b�g������̒����𔻒f���ȍ~�̌��������A�\�[�g�����Ŏg���܂�
        iLOT_LENGTH = sRots[0].Length();

		// KSD01������уf�[�^�`�F�b�N�p�̃��b�g��������쐬���܂�
		//iOldCol = 0;
		sAllLot = "";
		for(i1=0;i1<=iCnt2;i1++) {
			if( bKikanF[i1] == true ) {
				// ��ԁi�͈͎w��j�ŏ���
				sLot1 = sRots[i1];
				sLot2 = sRots[i1+1];

				// �w�肵���J�n���b�g�ƏI�����b�g�̑���ς݃��b�g���X�g���擾���܂��B
				// �����܂������b�g�͈͎̔w��ɑΉ��i['LOTNO1','LOTNO2',]�Ɩ߂�܂��j
                //2003/09/09 E.Takase
                if(iType == 4 ){
                	sAllLot += GetLotList2( sDTKSHIN, sLot1, sLot2 );
                } else {
                	sAllLot += GetLotList( sDTKSHIN, sLot1, sLot2 );
                }

                /* ���R�[�h�i�����܂������b�gNo�ɖ��Ή��j
				sLot1 = sRots[i1].SubString(2,sRots[i1].Length()-1);
				sLot2 = sRots[i1+1].SubString(2,sRots[i1+1].Length()-1);
				for(iOldCol=sLot1.ToInt();iOldCol < sLot2.ToInt();iOldCol++) {
					sBuf = iOldCol;
					sAllLot += "'"+sRots[i1].SubString(1,1) + AnsiString::StringOfChar('0', sLot1.Length()-sBuf.Length()) + sBuf + "'";
					sAllLot += ",";
				}
                */
                i1++;
			}
			else {
				// �ʁi�J���}��؂�j�ŏ���
				sAllLot += "'"+sRots[ i1 ]+"'";
				sAllLot += ",";
			}

		}

		// �Ō��,���폜���܂�
		sAllLot = sAllLot.SubString(1,sAllLot.Length()-1);

    } else {
        //------------------------------------------------------
        // �i�ԁE���t�i�o�ד����͌������j�ł̌��������s���܂�

		sDate1 = DelSEPA(edtC->Text);
		sDate2 = DelSEPA(edtD->Text);

		// ���t���̓`�F�b�N
		if( sDate1 < "19900101" || sDate1 > "21000101" ){
			MessageDlg("���t�̎w�肪����������܂���B", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
			edtC->SetFocus();
			return( false );
		}
		if( sDate2 < "19900101" || sDate2 > "21000101" ){
			MessageDlg("���t�̎w�肪����������܂���B", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
			edtD->SetFocus();
			return( false );
		}
		if( sDate2 < sDate1 ){
			MessageDlg("���t�̎w�肪����������܂���B", mtWarning,
						TMsgDlgButtons() << mbOK , 0);
			edtD->SetFocus();
			return( false );
		}

        // �Ώۃ��b�g�����b�g���Ō������܂�
        if( iType == 2 ){
			// �o�ד�

        	// �w��i�Ԃ̃��b�g�̒����𒲂ׂ܂�
			sBuf = "SELECT LOTBNG FROM SD21S";
			sBuf += " WHERE DTKSHIN ='" + sDTKSHIN + "'";
			Query3->Close();
			Query3->SQL->Clear();
			Query3->SQL->Add(sBuf);
			Query3->Open();
			Query3->Active = true;
            sBuf = "12345";
			if(Query3->Eof == false) {
	    	    sBuf = Query3->FieldValues["LOTBNG"];
			}
			Query3->Close();
        	// ���b�g������̒����𔻒f���ȍ~�̌��������A�\�[�g�����Ŏg���܂�
        	iLOT_LENGTH = sBuf.Length();

            // 2003/09/18 A.Tamura �o�ד��̎擾��SD15,SD16�ɕύX
            /*
			sBuf = "SELECT LOTBNG FROM SD21S";
			sBuf += " WHERE DTKSHIN ='" + sDTKSHIN + "'";
			sBuf += " AND ESYUYMD >= '" + sDate1 + "'";
			sBuf += " AND ESYUYMD <= '" + sDate2 + "'";
            if( iLOT_LENGTH == 5 ){
        		sBuf += " ORDER BY SUBSTR(LOTBNG,2)";
        	} else {
        		sBuf += " ORDER BY LOTBNG";
            }
            */

/* 2005.09.26 Y.Sano �폜
			sBuf = "SELECT LOTBNG FROM SD15S RIGHT JOIN SD16S ON SD15S.JSKBNG = SD16S.JSKBNG";
			sBuf += " WHERE SD16S.TKSHIN='" + sDTKSHIN + "'";
			sBuf += " GROUP BY SD16S.LOTBNG";
			sBuf += " HAVING Min(SD15S.TSUYMD)>='" + sDate1 + "'";
			sBuf += " And Min(SD15S.TSUYMD)<='" + sDate2 + "'";


            if( iLOT_LENGTH == 5 ){
        		sBuf += " ORDER BY SUBSTR(LOTBNG,2)";
        	} else {
        		sBuf += " ORDER BY LOTBNG";
            }
*/
/*    2005.09.26 Y.Sano ���ؗp�e�X�g  */
			sBuf = "SELECT LOTBNG FROM SD15S_16S ";
			sBuf += " WHERE TKSHIN='" + sDTKSHIN + "'";
			sBuf += " and TSUYMD_MIN>='" + sDate1 + "'";
			sBuf += " And TSUYMD_MIN<='" + sDate2 + "'";
            if( iLOT_LENGTH == 5 ){
        		sBuf += " ORDER BY SUBSTR(LOTBNG,2)";
        	} else {
        		sBuf += " ORDER BY LOTBNG";
            }

        } else {
			// ������

        	// ���b�g������̒����𔻒f���ȍ~�̌��������A�\�[�g�����Ŏg���܂�
            iLOT_LENGTH == 5;		// ���f����������ȈׁA�Œ��5���Ɖ��肵�܂�

			sBuf = "SELECT DTKSHIN, LOTNO, HINBAN FROM KSD01";
            /*
			sBuf += " WHERE (SKTYMD >= '" + sDate1 + "'";
			sBuf += " AND SKTYMD <= '" + sDate2 + "')";
			sBuf += " OR (SKTYMD_PRT >= '" + sDate1 + "'";
			sBuf += " AND SKTYMD_PRT <= '" + sDate2 + "')";
            */
			sBuf += " WHERE SKTYMD_PRT >= '" + sDate1 + "'";
			sBuf += " AND SKTYMD_PRT <= '" + sDate2 + "'";
			sBuf += " ORDER BY DTKSHIN, HINBAN, SUBSTR(LOTNO,2)";
        }

		// Initial Query
		Query3->Close();
		Query3->SQL->Clear();
		Query3->SQL->Add(sBuf);
		Query3->Open();
		Query3->Active = true;

       	if( iType == 2 ){
			// �o�ד�
			sAllLot = "";
			while(Query3->Eof == false) {
	        	sBuf = Query3->FieldValues["LOTBNG"];
	            if( sAllLot != "" )	sAllLot += ",";
    	        sAllLot += "'" + sBuf + "'";
				Query3->Next();
			}
			Query3->Close();

        } else {
			// ������
            sDtkshins->Clear();
			sLots->Clear();
			sHins->Clear();
            i1 = 0;
			while(Query3->Eof == false) {
				sDtkshins->Add( AnsiString(Query3->FieldValues["DTKSHIN"]) );
				sLots->Add( AnsiString(Query3->FieldValues["LOTNO"]) );
				sHins->Add( AnsiString(Query3->FieldValues["HINBAN"]) );
				Query3->Next();
            	i1++;
			}
			Query3->Close();

            if( i1 == 0 ){
				MessageDlg("�w�肳�ꂽ�i�ԁE���b�g��������܂���B", mtWarning,
							TMsgDlgButtons() << mbOK , 0);
				edtD->SetFocus();
				return( false );
        	}
        }

	}

    // �u�������̂݌����v�̏����ȊO�w�胍�b�g�̑��݃`�F�b�N�Ƒ��荀�ڂ̒ǉ��ݒ菈�����s�Ȃ��܂�
    if( iType != 3 ){

    	//2003/08/28 E.Takase
    	if(iType == 4 ){
            // �w�肳�ꂽ���b�g��KSD01������ыy��KSD21�f�ޑ�����уf�[�^���擾�����[�N�e�[�u�����쐬���܂�
            if( KSDCreateData(sDTKSHIN, sAllLot) == false ) {
				MessageDlg("�f�[�^�̍쐬�Ɏ��s���܂����B", mtWarning,
							TMsgDlgButtons() << mbOK , 0);
				edtA->SetFocus();
				return( false );
            }
    		// �w�肳�ꂽ���b�g��KSD01������уf�[�^,KSD21�f�ޑ�����уf�[�^�Ń`�F�b�N���܂�
			if( KSD01GetLot2(sDTKSHIN, sAllLot) == false ) {
				MessageDlg("�w�肳�ꂽ�i�ԁE���b�g��������܂���B", mtWarning,
							TMsgDlgButtons() << mbOK , 0);
				edtA->SetFocus();
				return( false );
    		}

    		// �w�肳�ꂽ�i�ԁE���b�g�̑��荀�ڂ�KSD02������уf�[�^,KSD22�f�ޑ�����уf�[�^����S�Ď擾���܂�
    		if( KSD02GetKOMOKU2(sDTKSHIN, sAllLot, iSEL_SZ, iSEL_SK, iSEL_TK, iSEL_ZR) == false ) {
				MessageDlg("�w�肳�ꂽ�i�ԁE���b�g�̑��荀�ڂ�������܂���B", mtWarning,
							TMsgDlgButtons() << mbOK , 0);
				edtA->SetFocus();
				return( false );
    		}

        } else {
    		// �w�肳�ꂽ���b�g��KSD01������уf�[�^�Ń`�F�b�N���܂�
			if( KSD01GetLot(sDTKSHIN, sAllLot) == false ) {
				MessageDlg("�w�肳�ꂽ�i�ԁE���b�g��������܂���B", mtWarning,
							TMsgDlgButtons() << mbOK , 0);
				edtA->SetFocus();
				return( false );
    		}

    		// �w�肳�ꂽ�i�ԁE���b�g�̑��荀�ڂ�KSD02������уf�[�^����S�Ď擾���܂�
    		if( KSD02GetKOMOKU(sDTKSHIN, sAllLot, iSEL_SZ, iSEL_SK, iSEL_TK, iSEL_ZR) == false ) {
				MessageDlg("�w�肳�ꂽ�i�ԁE���b�g�̑��荀�ڂ�������܂���B", mtWarning,
							TMsgDlgButtons() << mbOK , 0);
				edtA->SetFocus();
				return( false );
    		}
    	}

    }

    return( true );

}

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
AnsiString __fastcall TForm1::GetLotList(AnsiString sDTKSHIN, AnsiString sLOT_S, AnsiString sLOT_E)
{
	AnsiString sBuf;
	AnsiString sRet;

	if( sLOT_S.Trim() == "" || sLOT_E.Trim() == "" ) return( "" );

	sBuf = "SELECT LOTNO FROM KSD01";
	sBuf += " WHERE DTKSHIN = '" + sDTKSHIN + "'";

    if( iLOT_LENGTH == 5 ){
	    // �������b�g�i5���j�ɑΉ�
    	sBuf += " AND SUBSTR(LOTNO,2) >= '" + sLOT_S.SubString(2,5) + "'";
	    sBuf += " AND SUBSTR(LOTNO,2) <= '" + sLOT_E.SubString(2,5) + "'";
        sBuf += " AND SKTYMD >= '" + Edt_SEIKAN_YMD->Text + "'";      //onishi
	    sBuf += " ORDER BY SUBSTR(LOTNO,2)";
	} else {
	    // �C�O���b�g�i6���j�ɑΉ�
    	sBuf += " AND LOTNO >= '" + sLOT_S + "'";
	    sBuf += " AND LOTNO <= '" + sLOT_E + "'";
        sBuf += " AND SKTYMD >= '" + Edt_SEIKAN_YMD->Text + "'";      //onishi
	    sBuf += " ORDER BY LOTNO";
	}

	// Initial Query
	Query3->Close();
	Query3->SQL->Clear();
	Query3->SQL->Add(sBuf);
	Query3->Open();
	Query3->Active = true;
    sRet = "";
	while(Query3->Eof == false) {

        if( !VarIsNull(Query3->FieldValues["LOTNO"]) ){
        	sRet += "'" + AnsiString(Query3->FieldValues["LOTNO"]) + "',";
        }

		Query3->Next();
	}
	Query3->Close();

	return( sRet );

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
bool __fastcall TForm1::KSD01GetLot(AnsiString sDTKSHIN, AnsiString sLOT)
{
	AnsiString sBuf;
	bool bRet;
	int iCol;

	if( sLOT.Trim() == "" ) return( false );

	iCol = 0;
	sBuf = "SELECT * FROM KSD01";
	sBuf += " WHERE DTKSHIN = '" + sDTKSHIN + "'";
	sBuf += " AND   SKTYMD >= '" + Edt_SEIKAN_YMD->Text + "'";      //onishi
	sBuf += " AND   LOTNO IN (" + sLOT + ")";
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
//    int		iSEL_TK	�F���ʏo�͍��ڂ̏o�́itrue=����/false=���Ȃ��j
//    bool		iSEL_ZR	�F�ޗ��ؖ����ڂ̏o�́itrue=����/false=���Ȃ��j
//
//  �߂�l
//    bool				�Ftrue=���������Afalse=�������s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::KSD02GetKOMOKU(AnsiString sDTKSHIN, AnsiString sLOT,
                             bool iSEL_SZ, bool iSEL_SK, int iSEL_TK, bool iSEL_ZR)
{
	int				i, k, iCol;
	bool			bRet;
	AnsiString		sBuf;
    int				iSKB_NO;
    int				iTOKU_FLG;
    TCheckListBox*	clb;


	iCol = 0;
	sBuf = "SELECT * FROM KSD02";
	sBuf += " WHERE DTKSHIN ='" + sDTKSHIN + "'";
	sBuf += " AND   SKTYMD >= '" + Edt_SEIKAN_YMD->Text + "'";      //onishi
	sBuf += " AND   LOTNO IN (" + sLOT + ")";
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
            // 2003/10/21 A.Tamura [�P��]���܂߂đI�������ɓ����B
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

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�^�C�g�����̃f�[�^���������܂�
//
//  �@�\����
//    �w�肳�ꂽ�i�ԁE���b�g�̃^�C�g����񍀖ڃf�[�^���擾���܂�
//
//  �p�����^����
//    AnsiString sDTKSHIN�F��\���Ӑ�i��
//    AnsiString sLOT	 �F���b�gNO���X�g�i�J���}��؂�j
//    int		 iTileNo �F�^�C�g������NO
//                         1:�i�ԁA2:�i��A3:���s���A4:���b�gNo
//                         5:�[�����A6:������A7:�i���A8:����No 10:�o�ד�
//    bool		 iJapanese�Ftrue=���{��t�H�[�}�b�g�Afalse=�p��t�H�[�}�b�g
//
//  �߂�l
//    AnsiString		�F�擾����������
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::GetTitleData(AnsiString sDTKSHIN, AnsiString sLOT, int iTileNo, bool iJapanese)
{

	AnsiString	sBuf;
	AnsiString	sSQL;


    sBuf = "";


    // 1:�i��
    if( iTileNo == 1 ){
    	sBuf = sDTKSHIN;
    }

    // 3:���s��
    if( iTileNo == 3 ){
    	sBuf = FormatDateTime("yyyy/mm/dd",Date());
        if( iJapanese == false ){
        	sBuf = ToDateEnglish(sBuf);
        }
    }

    // 4:���b�gNo
    // �����w��Ȃ̂ŉ����Ԃ��Ȃ�

    // 5:�[����
    if( iTileNo == 5 ){
		sSQL = "SELECT SIJISU FROM SD21S";
		sSQL += " WHERE DTKSHIN ='" + sDTKSHIN + "'";
		sSQL += " AND LOTBNG = '" + sLOT + "'";

		// Initial Query
		Query3->Close();
		Query3->SQL->Clear();
		Query3->SQL->Add(sSQL);
		Query3->Open();
		Query3->Active = true;
		if(Query3->Eof == false) {
        	//sBuf = AnsiString(Query3->FieldValues["SIJISU"]).ToIntDef(0);
            sBuf = FormatFloat("#,##0", (double)AnsiString(Query3->FieldValues["SIJISU"]).ToIntDef(0));
		}
		Query3->Close();
    }

    // 8:����No
    // �擾���Ȃ��B�i�d�l�ō�����c�Ŏ擾���Ȃ����ƂŌ��肵���j

    // 2:�i��A6:������A7:�i��
    if( iTileNo == 2 || iTileNo == 6 || iTileNo == 7 ){
	    Query1->FindFirst();
		while(Query1->Eof == false) {

	        // �����i�ԁE���b�g�̃f�[�^��T���܂�
	        if( Query1->FieldValues["DTKSHIN"] == sDTKSHIN &&
	            Query1->FieldValues["LOTNO"] == sLOT ){
                // 2:�i��
                if( iTileNo == 2 ){
                    if( !VarIsNull(Query1->FieldValues["ZISNAM"]) ){
                		sBuf = Query1->FieldValues["ZISNAM"];
                    }
                }
                // 6:�����
                if( iTileNo == 6 ){
		        	if( !VarIsNull(Query1->FieldValues["SKTYMD_PRT"]) ){
                        if( AnsiString(Query1->FieldValues["SKTYMD_PRT"]).Trim() != "" ){
							sBuf = Query1->FieldValues["SKTYMD_PRT"];
							sBuf = sBuf.Insert("/",5);
							sBuf = sBuf.Insert("/",8);
					        if( iJapanese == false ){
					        	sBuf = ToDateEnglish(sBuf);
					        }
                    	}
                    }
                }
                // 7:�i��
                if( iTileNo == 7 ){
		        	if( !VarIsNull(Query1->FieldValues["HINMEI"]) ){
                		sBuf = Query1->FieldValues["HINMEI"];
                    }
                }

                break;
	        }

			Query1->Next();
		}
	}

    //2004.06.09 E.Takase ADD
    // 10:�o�ד�
    if( iTileNo == 10 ){
    	sBuf = FormatDateTime("yyyy/mm/dd",Date());
        if( iJapanese == false ){
        	sBuf = ToDateEnglish(sBuf);
        }
    }

	return( sBuf );

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F���|�[�g�쐬�������J�n���܂�
//
//  �@�\����
//    �w�肳�ꂽ�o�͏�񂩂����w���t�@�C��(CSV)���쐬���AExcel���N�����܂�
//
//  �p�����^����
//    int iAutoType		�F�o�͌`��
//                        0=����w��CSV�t�@�C���쐬��Excel�N���������Excel�I��
//                        1=����w��CSV�t�@�C���쐬��Excel�N��
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::CreateReport(int iAutoType)
{

    int			i, k, m, p;
    int			iEnglish;
    int			iX_OUT;
    int			iSKB_NO;
    int			iBLANK;
    int			iLOT_KETA;
	AnsiString	sBuf;
	AnsiString	sDTKSHIN;
	AnsiString	sLOTNO;
	AnsiString	sBuf1,sBuf2,sBuf3,sBuf4,sBuf5,sBuf6,sBuf7,sBuf8;
    double		dVal1, dVal2, dVal3;

    int			iBuf;
	AnsiString	sReSOKU_SU;
	AnsiString	sReKIKA_PRT;
	AnsiString	sReVALUE_TYPE;
	AnsiString	sReVALUE_DECI;
    int			iReDISP_VAL_SU;
	AnsiString	sReDISP_VAL_SU;
	AnsiString	sReDISP_VAL_AVE;
	AnsiString	sReDISP_VAL_MAX;
	AnsiString	sReDISP_VAL_MIN;
	AnsiString	sReDISP_OK;
	TStrings	*sReDISP_VAL;
	sReDISP_VAL	= new TStringList;

    FILE		*stream;

    bool        retDLL;
	char 		path[256];

    bool		bOKFlag;	//Excel�N���t���O

    bOKFlag = false;

    //--------------------------------------------------------------------------------------------
    // �������я��w���t�@�C���̍쐬
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet1" ){

    	    // �o�͓��e�̊m�F��������Ă��Ȃ��ꍇ�́A�������s���܂�
    	    if( iNowTab != 1 ){
			Btn1_OUT_CHECKClick(Btn1_OUT_CHECK);
			if( ret_Btn1_OUT_CHECKClick == false ) return;
            }

    	if( (stream = fopen( sRepData1, "w+" )) != NULL ){
    		// ����Ƀt�@�C�����I�[�v���ł����ꍇ

			// [����̌`��(0=������Ď����I��/1=Excel�I�����Ȃ��A����Ȃ��j],
            // [�i��],
            // [�Ж�],
            // [�o�͌`��(0=���{��/1=�p��)],
            // [X�̏o��(0=���Ȃ�/1=����)]
            if( Rdo1_WHR_FORMAT_JPN->Checked == true )		iEnglish = 0;
            else											iEnglish = 1;
            if( Rdo1_CHK_X_ON->Checked == true )			iX_OUT = 1;
            //20161214 Y.Onishi
            //Cp,Cpk�o�͂ɑΉ�
            else if( Rdo1_CHK_X_CP->Checked == true )			iX_OUT = 2;
            else											iX_OUT = 0;
			fprintf( stream,"%d,%s,\"%s\",%d,%d\n",
            								iAutoType,
											Edt1_WHR_DTKSHIN->Text.c_str(),
											Edt1_CHK_CUSTOMER->Text.c_str(),
                                            iEnglish,
                                            iX_OUT );

            // [�^�C�g����1],[�^�C�g����2],[�^�C�g����3],[...4],[...5],[...6],[...7],[�^�C�g����8]
            // (���{��)
            k = 0;
    		for( i = 0; i < iTITLE_Cnt; i++){
        		if( Clb1_CHK_TITLE->Checked[i] == true ){
            		sBuf = sTITLE_JPN->Strings[i];
                    if( k == 0 )	fprintf( stream, "\"%s\"", sBuf.c_str() );
                    else        	fprintf( stream,",\"%s\"", sBuf.c_str() );
                    k++;
                }
            }
    		for( i = k; i < 8; i++){
                fprintf( stream,"," );
            }
            fprintf( stream,"\n" );

            // [�^�C�g����1],[�^�C�g����2],[�^�C�g����3],[...4],[...5],[...6],[...7],[�^�C�g����8]
            // (�p��)
            k = 0;
    		for( i = 0; i < iTITLE_Cnt; i++){
        		if( Clb1_CHK_TITLE->Checked[i] == true ){
            		sBuf = sTITLE_ENG->Strings[i];
                    if( k == 0 )	fprintf( stream, "\"%s\"", sBuf.c_str() );
                    else        	fprintf( stream,",\"%s\"", sBuf.c_str() );
                    k++;
                }
            }
    		for( i = k; i < 8; i++){
                fprintf( stream,"," );
            }
            fprintf( stream,"\n" );

            // ���l�i���s�R�[�h��[CR+LF]�ɕϊ����܂��j
            sBuf = "";
    		for( i = 0; i < Memo1_CHK_REMARK->Lines->Count; i++){
            	sBuf = sBuf + Memo1_CHK_REMARK->Lines->Strings[i];
            	sBuf = sBuf + "[CR+LF]";
            }
			fprintf( stream,"%s\n", sBuf.c_str() );

            // ���b�g��
			fprintf( stream,"%d\n", PgCtr1_LOT->Tag );

          	// [���b�gNo1],[�^�C�g����1],[�^�C�g����2],[�^�C�g����3],[...4],[...5],[...6],[...7],[�^�C�g����8]
            // �w�胍�b�g�����o�͂��܂�
    		for( i = 0; i < PgCtr1_LOT->Tag; i++){

                if( i == 0 ){
                	// 1���b�g��
					sLOTNO = PgCtr1_tst01->Caption.Trim();

                    if( PgCtr1_tst1_Edt1->Tag == 4 )	sBuf1 = GetTitleLotNo( i );
                    else								sBuf1 = PgCtr1_tst1_Edt1->Text;
                    if( PgCtr1_tst1_Edt2->Tag == 4 )	sBuf2 = GetTitleLotNo( i );
                    else								sBuf2 = PgCtr1_tst1_Edt2->Text;
                    if( PgCtr1_tst1_Edt3->Tag == 4 )	sBuf3 = GetTitleLotNo( i );
                    else								sBuf3 = PgCtr1_tst1_Edt3->Text;
                    if( PgCtr1_tst1_Edt4->Tag == 4 )	sBuf4 = GetTitleLotNo( i );
                    else								sBuf4 = PgCtr1_tst1_Edt4->Text;
                    if( PgCtr1_tst1_Edt5->Tag == 4 )	sBuf5 = GetTitleLotNo( i );
                    else								sBuf5 = PgCtr1_tst1_Edt5->Text;
                    if( PgCtr1_tst1_Edt6->Tag == 4 )	sBuf6 = GetTitleLotNo( i );
                    else								sBuf6 = PgCtr1_tst1_Edt6->Text;
                    if( PgCtr1_tst1_Edt7->Tag == 4 )	sBuf7 = GetTitleLotNo( i );
                    else								sBuf7 = PgCtr1_tst1_Edt7->Text;
                    if( PgCtr1_tst1_Edt8->Tag == 4 )	sBuf8 = GetTitleLotNo( i );
                    else								sBuf8 = PgCtr1_tst1_Edt8->Text;
                }
                else {
                	// 2���b�g�ڈȍ~
					sLOTNO = PgCtr1_tst[i+1]->Caption.Trim();

                   	if( PgCtr1_tst1_Edt1->Tag == 4 )	sBuf1 = GetTitleLotNo( i+1 );
                   	else								sBuf1 = PgCtr1_tst_Edt[i+1][0]->Text;
                   	if( PgCtr1_tst1_Edt2->Tag == 4 )	sBuf2 = GetTitleLotNo( i+1 );
                   	else								sBuf2 = PgCtr1_tst_Edt[i+1][1]->Text;
                   	if( PgCtr1_tst1_Edt3->Tag == 4 )	sBuf3 = GetTitleLotNo( i+1 );
                   	else								sBuf3 = PgCtr1_tst_Edt[i+1][2]->Text;
                   	if( PgCtr1_tst1_Edt4->Tag == 4 )	sBuf4 = GetTitleLotNo( i+1 );
                   	else								sBuf4 = PgCtr1_tst_Edt[i+1][3]->Text;
                   	if( PgCtr1_tst1_Edt5->Tag == 4 )	sBuf5 = GetTitleLotNo( i+1 );
                   	else								sBuf5 = PgCtr1_tst_Edt[i+1][4]->Text;
                   	if( PgCtr1_tst1_Edt6->Tag == 4 )	sBuf6 = GetTitleLotNo( i+1 );
                   	else								sBuf6 = PgCtr1_tst_Edt[i+1][5]->Text;
                   	if( PgCtr1_tst1_Edt7->Tag == 4 )	sBuf7 = GetTitleLotNo( i+1 );
                   	else								sBuf7 = PgCtr1_tst_Edt[i+1][6]->Text;
                   	if( PgCtr1_tst1_Edt8->Tag == 4 )	sBuf8 = GetTitleLotNo( i+1 );
                   	else								sBuf8 = PgCtr1_tst_Edt[i+1][7]->Text;
                }

				fprintf( stream,"%s,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\n",
                												sLOTNO.c_str(),
																sBuf1.c_str(),
																sBuf2.c_str(),
																sBuf3.c_str(),
																sBuf4.c_str(),
																sBuf5.c_str(),
																sBuf6.c_str(),
																sBuf7.c_str(),
																sBuf8.c_str());
            }

            // ��؂�
			fprintf( stream,"@@@�o�͍���@@@\n" );

          	// [���b�gNo1],[�^�C�g����1],[�^�C�g����2],[�^�C�g����3],[...4],[...5],[...6],[...7],[�^�C�g����8]
            // �w�胍�b�g�����o�͂��܂�
    		for( i = 0; i < PgCtr1_LOT->Tag; i++){

				if( i == 0 ){
					sLOTNO = PgCtr1_tst01->Caption.Trim();
				}
				else {
					sLOTNO = PgCtr1_tst[i+1]->Caption.Trim();
				}

				Query2->FindFirst();
				while(Query2->Eof == false) {

					sBuf = Query2->FieldValues["LOTNO"];

                    // �Y���̃��b�g�m�����������܂�
                    if( sLOTNO == sBuf ){

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
							// 2003/10/21 A.Tamura [�P��]���܂߂đI�������ɓ����B
							if( !VarIsNull(Query2->FieldValues["TANI"]) ){
								sBuf = sBuf + " " + Query2->FieldValues["TANI"];
							}
							if( sBuf != "" ){

								// �I������Ă��鍀�ڂ����o�͑ΏۂƔ��f���܂�
                                k = 0;
								for( m = 0; m < Clb1_CHK_KOUMOKU->Items->Count; m++){
									if( Clb1_CHK_KOUMOKU->Items->Strings[m] == sBuf ){
                                        if( Clb1_CHK_KOUMOKU->Checked[m] == true ){
											k = 1;
										}
                                        break;
									}
								}
								if( k == 1 ){
									// �o�͍��ځi���荀�ڍs�j���������݂܂�
                                    bOKFlag = true;	//2003/07/22 E.Takase
									fprintf( stream, "%s,%d,",
                                    	                sLOTNO.c_str(),
                                                        iSKB_NO );
                                    fprintf( stream, "\"%s\",\"%s\",\"%s\",\"%s\",%d,%s,%s,",
                                    					Null_S(Query2->FieldValues["KOMK_NM"]).c_str(),
                                                        Null_S(Query2->FieldValues["KOMK_ENG"]).c_str(),
                                                        Null_S(Query2->FieldValues["KOMK_SUB"]).c_str(),
                                                        Null_S(Query2->FieldValues["KOMK_SUB_ENG"]).c_str(),
                                                        AnsiString(Query2->FieldValues["KIKI_NO"]).ToIntDef(0),
                                                        Null_S(Query2->FieldValues["KIKI_NM"]).c_str(),
                                                        Null_S(Query2->FieldValues["TANI"]).c_str() );
                                    dVal1 = Query2->FieldValues["KIKA_NUM1"];
                                    dVal2 = Query2->FieldValues["KIKA_NUM2"];
                                    dVal3 = Query2->FieldValues["KIKA_NUM3"];
                                    fprintf( stream, "%d,%d,%d,%f,%f,%f,%s,",
                                    					AnsiString(Query2->FieldValues["KIKA_TYPE"]).ToIntDef(1),
                                    					AnsiString(Query2->FieldValues["KIKA_KIND"]).ToIntDef(1),
                                    					AnsiString(Query2->FieldValues["KIKA_DECI"]).ToIntDef(0),
                                    					dVal1,
                                    					dVal2,
                                    					dVal3,
                                                        Null_S(Query2->FieldValues["KIKA_STR"]).c_str() );

                                    fprintf( stream, "%d,%d,%d,",
                                      					AnsiString(Query2->FieldValues["KIKA_PRT"]).ToIntDef(0),
                                       					AnsiString(Query2->FieldValues["VALUE_TYPE"]).ToIntDef(0),
                                       					AnsiString(Query2->FieldValues["VALUE_DECI"]).ToIntDef(0) );

                                    // ���荀�ڂ̗L��			2003/08/28 A.Tamura
                                    if( Query2->FieldValues["SOKU_FLG"] == 0 ){
                                    	// �u���肵�Ȃ��v�̎�

                                        //2003/10/22 E.Takase ���������ɒP�ʒǉ�
				                  		//iBuf = GetBeforeLotVal(
                                        //			Null_S(Query2->FieldValues["DTKSHIN"]),
                                        //            Null_S(Query2->FieldValues["LOTNO"]),
					                	//            Null_S(Query2->FieldValues["KOMK_NM"]),
                                    	//			Null_S(Query2->FieldValues["KOMK_SUB"]),
                                    	//			Null_S(Query2->FieldValues["HINBAN_SK"]),
                                    	//			atoi(Null_S(Query2->FieldValues["KIKI_NO"]).c_str()),
                                    	//			atoi(Null_S(Query2->FieldValues["KOMK_NO"]).c_str()),
                                		//			&sReSOKU_SU, &sReKIKA_PRT, &sReVALUE_TYPE,
                                    	//			&sReVALUE_DECI, &sReDISP_VAL_SU, &sReDISP_VAL_AVE,
                                    	//			&sReDISP_VAL_MAX, &sReDISP_VAL_MIN, &sReDISP_OK, sReDISP_VAL );
				                  		iBuf = GetBeforeLotVal(
                                        			Null_S(Query2->FieldValues["DTKSHIN"]),
                                                    Null_S(Query2->FieldValues["LOTNO"]),
					                	            Null_S(Query2->FieldValues["KOMK_NM"]),
                                    				Null_S(Query2->FieldValues["KOMK_SUB"]),
                                    				Null_S(Query2->FieldValues["HINBAN_SK"]),
                                    				atoi(Null_S(Query2->FieldValues["KIKI_NO"]).c_str()),
                                    				atoi(Null_S(Query2->FieldValues["KOMK_NO"]).c_str()),
                                    				Null_S(Query2->FieldValues["TANI"]),
                                					&sReSOKU_SU, &sReKIKA_PRT, &sReVALUE_TYPE,
                                    				&sReVALUE_DECI, &sReDISP_VAL_SU, &sReDISP_VAL_AVE,
                                    				&sReDISP_VAL_MAX, &sReDISP_VAL_MIN, &sReDISP_OK, sReDISP_VAL );
                                    	iReDISP_VAL_SU = sReDISP_VAL_SU.ToIntDef(0);
                                        // 2003/11/5 A.Tamura �����̊Y�����b�g��������Ȃ����ADISP_VAL_SU�́A�o�̓��b�g��SOKU_SU�����܂�
                                        if( iBuf < 0 ){
                                        	sReDISP_VAL_SU = AnsiString(Query2->FieldValues["SOKU_SU"]);
                                        	iReDISP_VAL_SU = 0;
                                        }

										// ���萔�A���ϒl
                                        fprintf( stream, "%s,%s", sReDISP_VAL_SU, sReDISP_VAL_AVE );

                                        // ����l1�`�̒l�ݒ�
										for( m = 0; m < iReDISP_VAL_SU; m++){
 										    fprintf( stream, ",%s", sReDISP_VAL->Strings[m].c_str() );
                                        }

                                        // ����l��10�ɖ����Ȃ��ꍇ�͋󔒂�ݒ�
										for( m = iReDISP_VAL_SU; m < 10; m++){
 										    fprintf( stream, ",%s", " " );
                                        }

                                    }
                                    else {
                                    	// �u���肷��v�̎�

										// ���萔�A���ϒl
                                        dVal1 = Query2->FieldValues["DISP_VAL_AVE"];
                                        fprintf( stream, "%d,%f,",
                                        					AnsiString(Query2->FieldValues["DISP_VAL_SU"]).ToIntDef(0),
                                                            dVal1 );

                                        // ����l1�`10�̒l�ݒ�
                                        fprintf( stream, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
                                        					Null_S(Query2->FieldValues["DISP_VAL01"]).c_str(),
                                        					Null_S(Query2->FieldValues["DISP_VAL02"]).c_str(),
                                        					Null_S(Query2->FieldValues["DISP_VAL03"]).c_str(),
                                        					Null_S(Query2->FieldValues["DISP_VAL04"]).c_str(),
                                        					Null_S(Query2->FieldValues["DISP_VAL05"]).c_str(),
                                        					Null_S(Query2->FieldValues["DISP_VAL06"]).c_str(),
                                        					Null_S(Query2->FieldValues["DISP_VAL07"]).c_str(),
                                        					Null_S(Query2->FieldValues["DISP_VAL08"]).c_str(),
                                        					Null_S(Query2->FieldValues["DISP_VAL09"]).c_str(),
                                        					Null_S(Query2->FieldValues["DISP_VAL10"]).c_str() );

                                        // ����l11�`�̒l�ݒ�
                                        if( AnsiString(Query2->FieldValues["DISP_VAL_SU"]).ToIntDef(0) > 10 ){
											sBuf = "SELECT * FROM KSD03";
											sBuf += " WHERE DTKSHIN ='" + Edt1_WHR_DTKSHIN->Text + "'";
											sBuf += " AND LOTNO = '" + sLOTNO + "'";
											sBuf += " AND UNQ_NO = " + AnsiString(Query2->FieldValues["UNQ_NO"]);
											sBuf += " ORDER BY SOKU_NO";

											// Initial Query
											Query3->Close();
											Query3->SQL->Clear();
											Query3->SQL->Add(sBuf);
											Query3->Open();
											Query3->Active = true;
 	 										while(Query3->Eof == false) {
			                                    fprintf( stream, ",%s",
                                                			Null_S(Query3->FieldValues["DISP_VAL"]).c_str() );
  	  											Query3->Next();
  	  										}
                                        }

                                    }

                                    fprintf( stream, "\n" );
                             	}
							}
						}
                        else {
							// �o�͍��ځi�󔒍s�j���������݂܂�
							fprintf( stream, "%s,%d,,,,,,,,,,,,,,,,,,,,0,0,,,,,,,,,,\n",
                            					sLOTNO.c_str(),	iSKB_NO);
                        }
					}
					Query2->Next();
				}
        	}
		}

	    // �t�@�C�������
    	fclose(stream);

    }


    //--------------------------------------------------------------------------------------------
    // �������я��i���ʁj�w���t�@�C���̍쐬
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet2" ){

    	// �o�͓��e�̊m�F��������Ă��Ȃ��ꍇ�́A�������s���܂�
    	if( iNowTab != 2 ){
			Btn1_OUT_CHECKClick(Btn2_OUT_CHECK);
			if( ret_Btn1_OUT_CHECKClick == false ) return;
    	}

    	if( (stream = fopen( sRepData2, "w+" )) != NULL ){
    		// ����Ƀt�@�C�����I�[�v���ł����ꍇ

			// [����̌`��(0=������Ď����I��/1=Excel�I�����Ȃ��A����Ȃ��j],
            // [�i��],
            // [�Ж�],
            // [�[����],
            // [�o�͌`��(0=���{��/1=�p��)],
            // [X�̏o��(0=���Ȃ�/1=����)]
            // [��s�󂯂ďo��(0=���Ȃ�/1=����)]
            // [���b�g�m���̌�(4or5or6)]
            if( Rdo2_WHR_FORMAT_JPN->Checked == true )		iEnglish = 0;
            else											iEnglish = 1;
            if( Rdo2_CHK_X_ON->Checked == true )			iX_OUT = 1;
            else											iX_OUT = 0;
            if( Rdo2_WHR_BLANK_ON->Checked == true )		iBLANK = 1;
            else											iBLANK = 0;
            if( Rdo2_WHR_TYPE1->Checked == true )			sDTKSHIN = Edt2_WHR_DTKSHIN1->Text;
            else											sDTKSHIN = Edt2_WHR_DTKSHIN2->Text;
            if( Rdo2_LOT_KETA4->Checked == true ){			iLOT_KETA = 4;
            } else if( Rdo2_LOT_KETA5->Checked == true ){   iLOT_KETA = 5;
            } else {                                        iLOT_KETA = 6;
            }
			fprintf( stream,"%d,%s,\"%s\",\"%s\",%d,%d,%d,%d\n",
            								iAutoType,
											sDTKSHIN.c_str(),
											Edt2_CHK_CUSTOMER->Text.c_str(),
                                            Edt2_TITLE_MONTH->Text.c_str(),
                                            iEnglish,
                                            iX_OUT,
                                            iBLANK,
                                            iLOT_KETA );

            // [�^�C�g����1],[�^�C�g����2],[�^�C�g����3],[...4],[...5],[�^�C�g����6]
            // (���{��)
            k = 0;
    		for( i = 0; i < iTITLE_Cnt; i++){
        		if( Clb2_CHK_TITLE->Checked[i] == true ){
            		sBuf = sTITLE_JPN->Strings[i];
                    if( k == 0 )	fprintf( stream, "\"%s\"", sBuf.c_str() );
                    else        	fprintf( stream,",\"%s\"", sBuf.c_str() );
                    k++;
                }
            }
    		for( i = k; i < 6; i++){
                fprintf( stream,"," );
            }
            fprintf( stream,"\n" );

            // [�^�C�g����1],[�^�C�g����2],[�^�C�g����3],[...4],[...5],[�^�C�g����6]
            // (�p��)
            k = 0;
    		for( i = 0; i < iTITLE_Cnt; i++){
        		if( Clb2_CHK_TITLE->Checked[i] == true ){
            		sBuf = sTITLE_ENG->Strings[i];
                    if( k == 0 )	fprintf( stream, "\"%s\"", sBuf.c_str() );
                    else        	fprintf( stream,",\"%s\"", sBuf.c_str() );
                    k++;
                }
            }
    		for( i = k; i < 6; i++){
                fprintf( stream,"," );
            }
            fprintf( stream,"\n" );

          	// [�^�C�g����1],[�^�C�g����2],[�^�C�g����3],[...4],[...5],[�^�C�g����6]
            if( PgCtr2_tst1_Edt1->Tag == 4 )	sBuf1 = "";
            else								sBuf1 = PgCtr2_tst1_Edt1->Text;
            if( PgCtr2_tst1_Edt2->Tag == 4 )	sBuf2 = "";
            else								sBuf2 = PgCtr2_tst1_Edt2->Text;
            if( PgCtr2_tst1_Edt3->Tag == 4 )	sBuf3 = "";
            else								sBuf3 = PgCtr2_tst1_Edt3->Text;
            if( PgCtr2_tst1_Edt4->Tag == 4 )	sBuf4 = "";
            else								sBuf4 = PgCtr2_tst1_Edt4->Text;
            if( PgCtr2_tst1_Edt5->Tag == 4 )	sBuf5 = "";
            else								sBuf5 = PgCtr2_tst1_Edt5->Text;
            if( PgCtr2_tst1_Edt6->Tag == 4 )	sBuf6 = "";
            else								sBuf6 = PgCtr2_tst1_Edt6->Text;
			fprintf( stream,"\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\n",
            										sBuf1.c_str(),
												    sBuf2.c_str(),
												    sBuf3.c_str(),
												    sBuf4.c_str(),
												    sBuf5.c_str(),
												    sBuf6.c_str());

            // ���l�i���s�R�[�h��[CR+LF]�ɕϊ����܂��j
            sBuf = "";
    		for( i = 0; i < Memo2_CHK_REMARK->Lines->Count; i++){
            	sBuf = sBuf + Memo2_CHK_REMARK->Lines->Strings[i];
            	sBuf = sBuf + "[CR+LF]";
            }
			fprintf( stream,"%s\n", sBuf.c_str() );

            // ���b�g��
            k = 0;
    		for( i = 0; i < Clb2_CHK_LOT->Items->Count; i++){
        		if( Clb2_CHK_LOT->Checked[i] == true )	k++;
            }
			fprintf( stream,"%d\n", k );

            // ��؂�
			fprintf( stream,"@@@�o�͍���@@@\n" );

			// �w�胍�b�g�����o�͂��܂�
			for( i = 0; i < Clb2_CHK_LOT->Items->Count; i++){
				if( Clb2_CHK_LOT->Checked[i] == true ){

					// �o�͑Ώۂ̃��b�g���擾���܂�
					sLOTNO = Clb2_CHK_LOT->Items->Strings[i];

					// �I������Ă��鍀�ڂ����o�͑ΏۂƔ��f���܂�
					for( m = 0; m < Clb2_CHK_KOUMOKU->Items->Count; m++){
						if( Clb2_CHK_KOUMOKU->Checked[m] == true ){

							// 2003/10/21 A.Tamura
							// �Ώۃ��b�g�̏o�͂��������荀�ڂ��Ώۃ��b�g�ɖ��������ꍇ�A���̃��b�g�ɗL��͂��̑��荀�ڂ���
							// ���荀�ږ��A�K�i�Ȃǂ��擾���A�_�~�[�s�iCSV�j���o�͂���ׂ̃��[�v
							// ���̃��[�v���Q��ڂ̎��́A����ɊY������
							for( k = 0; k < 2; k++ ){
								
								Query2->FindFirst();
								while(Query2->Eof == false) {

									sBuf = Query2->FieldValues["LOTNO"];

									// �Y���̃��b�g�m�����������܂�
									// 2003/10/21 A.Tamura ���̃��[�v���Q��ڂ̎��́A�_�~�[�s�iCSV�j���o�͏���
									if( sLOTNO == sBuf || k == 1 ){

										// ���荀�ڂƂ��ďo�͂��܂��B
										iSKB_NO = AnsiString(Query2->FieldValues["SKB_NO"]).ToIntDef(9);
										if( iSKB_NO != 9 ){

											// �Ώۃ��R�[�h�̑��荀�ڂ��擾���܂��B
											sBuf = "";
											if( !VarIsNull(Query2->FieldValues["KOMK_NM"]) ){
												sBuf = Query2->FieldValues["KOMK_NM"];
											}
											if( !VarIsNull(Query2->FieldValues["KOMK_SUB"]) ){
												sBuf = sBuf + " " + Query2->FieldValues["KOMK_SUB"];
											}
											// 2003/10/21 A.Tamura [�P��]���܂߂đI�������ɓ����B
											if( !VarIsNull(Query2->FieldValues["TANI"]) ){
												sBuf = sBuf + " " + Query2->FieldValues["TANI"];
											}
											if( sBuf != "" ){
												// �Ώۃ��R�[�h���I������Ă��鑪�荀�ڂƓ������ǂ������f���܂��B
												if( Clb2_CHK_KOUMOKU->Items->Strings[m] == sBuf ){
													
													// �Y�����R�[�h����
													if( k == 0 )	k = 2;

													// �o�͍��ځi���荀�ڍs�j���������݂܂�
													bOKFlag = true;	//2003/07/22 E.Takase
													fprintf( stream, "%s,%d,",
																		sLOTNO.c_str(),
																		iSKB_NO );
													fprintf( stream, "\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",",
																		Null_S(Query2->FieldValues["KOMK_NM"]).c_str(),
																		Null_S(Query2->FieldValues["KOMK_ENG"]).c_str(),
																		Null_S(Query2->FieldValues["KOMK_SUB"]).c_str(),
																		Null_S(Query2->FieldValues["KOMK_SUB_ENG"]).c_str(),
																		AnsiString(Query2->FieldValues["KIKI_NO"]).ToIntDef(0),
																		Null_S(Query2->FieldValues["KIKI_NM"]).c_str(),
																		Null_S(Query2->FieldValues["TANI"]).c_str() );
													dVal1 = Query2->FieldValues["KIKA_NUM1"];
													dVal2 = Query2->FieldValues["KIKA_NUM2"];
													dVal3 = Query2->FieldValues["KIKA_NUM3"];
													if( iSKB_NO == 2 && AnsiString(Query2->FieldValues["KOMK_NO"]).ToIntDef(0) == 1 ){
														sBuf = " ";
													}
													else {
														sBuf = Null_S(Query2->FieldValues["KIKA_STR"]).c_str();
													}
													fprintf( stream, "%d,%d,%d,%f,%f,%f,%s,",
																		AnsiString(Query2->FieldValues["KIKA_TYPE"]).ToIntDef(1),
																		AnsiString(Query2->FieldValues["KIKA_KIND"]).ToIntDef(1),
																		AnsiString(Query2->FieldValues["KIKA_DECI"]).ToIntDef(0),
																		dVal1,
																		dVal2,
																		dVal3,
																		sBuf );

													fprintf( stream, "%d,%d,%d,",
																		AnsiString(Query2->FieldValues["KIKA_PRT"]).ToIntDef(0),
																		AnsiString(Query2->FieldValues["VALUE_TYPE"]).ToIntDef(0),
																		AnsiString(Query2->FieldValues["VALUE_DECI"]).ToIntDef(0) );

													// ���荀�ڂ̗L��			2003/08/28 A.Tamura
													// 2003/10/21 A.Tamura ���̃��[�v���Q��ڂ̎��́A�_�~�[�s�iCSV�j���o�͏���
													if( Query2->FieldValues["SOKU_FLG"] == 0 || k == 1 ){
														// �u���肵�Ȃ��v�̎�

                                                        // �O���b�g���瓯���l�����p���i�擾�j���܂�
                                                        //2003/10/22 E.Takase ���������ɒP�ʒǉ�
														//iBuf = GetBeforeLotVal(
														//			Null_S(Query2->FieldValues["DTKSHIN"]),
														//			sLOTNO,
														//			Null_S(Query2->FieldValues["KOMK_NM"]),
														//			Null_S(Query2->FieldValues["KOMK_SUB"]),
														//			Null_S(Query2->FieldValues["HINBAN_SK"]),
														//			atoi(Null_S(Query2->FieldValues["KIKI_NO"]).c_str()),
														//			atoi(Null_S(Query2->FieldValues["KOMK_NO"]).c_str()),
														//			&sReSOKU_SU, &sReKIKA_PRT, &sReVALUE_TYPE,
														//			&sReVALUE_DECI, &sReDISP_VAL_SU, &sReDISP_VAL_AVE,
														//			&sReDISP_VAL_MAX, &sReDISP_VAL_MIN, &sReDISP_OK, sReDISP_VAL );
														iBuf = GetBeforeLotVal(
																	Null_S(Query2->FieldValues["DTKSHIN"]),
																	sLOTNO,
																	Null_S(Query2->FieldValues["KOMK_NM"]),
																	Null_S(Query2->FieldValues["KOMK_SUB"]),
																	Null_S(Query2->FieldValues["HINBAN_SK"]),
																	atoi(Null_S(Query2->FieldValues["KIKI_NO"]).c_str()),
																	atoi(Null_S(Query2->FieldValues["KOMK_NO"]).c_str()),
																	Null_S(Query2->FieldValues["TANI"]),
																	&sReSOKU_SU, &sReKIKA_PRT, &sReVALUE_TYPE,
																	&sReVALUE_DECI, &sReDISP_VAL_SU, &sReDISP_VAL_AVE,
																	&sReDISP_VAL_MAX, &sReDISP_VAL_MIN, &sReDISP_OK, sReDISP_VAL );
														iReDISP_VAL_SU = sReDISP_VAL_SU.ToIntDef(0);
                                                        // 2003/11/5 A.Tamura �����̊Y�����b�g��������Ȃ����ADISP_VAL_SU�́A�o�̓��b�g��SOKU_SU�����܂�
                                                        if( iBuf < 0 ){
                                                        	sReDISP_VAL_SU = AnsiString(Query2->FieldValues["SOKU_SU"]);
                                                        	iReDISP_VAL_SU = 0;
                                                        }

														// ���萔�A���ϒl�A�ő�l�A�ŏ��l
                                                        //2003/11/26 E.Takase
														//fprintf( stream, "%s,%s,%s,%s,",
														fprintf( stream, "%s,%s,%s,%s",
																			sReDISP_VAL_SU,
																			sReDISP_VAL_AVE,
																			sReDISP_VAL_MAX,
																			sReDISP_VAL_MIN);

														// ����l1�`�̒l�ݒ�
														for( p = 0; p < iReDISP_VAL_SU; p++){
															fprintf( stream, ",%s", sReDISP_VAL->Strings[p].c_str() );
														}

														// ����l��10�ɖ����Ȃ��ꍇ�͋󔒂�ݒ�
														for( p = iReDISP_VAL_SU; p < 10; p++){
															fprintf( stream, ",%s", " " );
														}

													}
													else {
														// �u���肷��v�̎�

														// ���萔�A���ϒl�A�ő�l�A�ŏ��l
														dVal1 = Query2->FieldValues["DISP_VAL_AVE"];
														dVal2 = Query2->FieldValues["DISP_VAL_MAX"];
														dVal3 = Query2->FieldValues["DISP_VAL_MIN"];
														fprintf( stream, "%d,%f,%f,%f,",
																			AnsiString(Query2->FieldValues["DISP_VAL_SU"]).ToIntDef(0),
																			dVal1,
																			dVal2,
																			dVal3 );

														// ����l1�`10�̒l�ݒ�
														fprintf( stream, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
																			Null_S(Query2->FieldValues["DISP_VAL01"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL02"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL03"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL04"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL05"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL06"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL07"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL08"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL09"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL10"]).c_str() );

														// ����l11�`�̒l�ݒ�
														if( AnsiString(Query2->FieldValues["DISP_VAL_SU"]).ToIntDef(0) > 10 ){
															sBuf = "SELECT * FROM KSD03";
															sBuf += " WHERE DTKSHIN ='" + sDTKSHIN + "'";
															sBuf += " AND LOTNO = '" + sLOTNO + "'";
															sBuf += " AND UNQ_NO = " + AnsiString(Query2->FieldValues["UNQ_NO"]);
															sBuf += " ORDER BY SOKU_NO";

															// Initial Query
															Query3->Close();
															Query3->SQL->Clear();
															Query3->SQL->Add(sBuf);
															Query3->Open();
															Query3->Active = true;
															while(Query3->Eof == false) {
																fprintf( stream, ",%s",
																			Null_S(Query3->FieldValues["DISP_VAL"]).c_str() );
																Query3->Next();
															}
														}
													}
													fprintf( stream, "\n" );
													
													break;
												}
											}
										}
									}
									Query2->Next();
									
								}	// While
							}
						}
					}	// for m end
				}
			}	// for i end
		}

	    // �t�@�C�������
    	fclose(stream);

    }


    //--------------------------------------------------------------------------------------------
    // �ޗ��ؖ����w���t�@�C���̍쐬
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet3" ){

    	// �o�͓��e�̊m�F��������Ă��Ȃ��ꍇ�́A�������s���܂�
    	if( iNowTab != 3 ){
			Btn1_OUT_CHECKClick(Btn3_OUT_CHECK);
			if( ret_Btn1_OUT_CHECKClick == false ) return;
    	}

    	if( (stream = fopen( sRepData3, "w+" )) != NULL ){
    		// ����Ƀt�@�C�����I�[�v���ł����ꍇ

			// [����̌`��(0=������Ď����I��/1=Excel�I�����Ȃ��A����Ȃ��j],
            // [�i��],
            // [�Ж�],
            // [�o�͌`��(0=���{��/1=�p��)],
            // [X�̏o��(0=���Ȃ�/1=����)]
            if( Rdo3_WHR_FORMAT_JPN->Checked == true )		iEnglish = 0;
            else											iEnglish = 1;
            if( Rdo3_CHK_X_ON->Checked == true )			iX_OUT = 1;
            else											iX_OUT = 0;
			fprintf( stream,"%d,%s,\"%s\",%d,%d\n",
            								iAutoType,
											Edt3_WHR_DTKSHIN->Text.c_str(),
											Edt3_CHK_CUSTOMER->Text.c_str(),
                                            iEnglish,
                                            iX_OUT );

            // [�^�C�g����1],[�^�C�g����2],[�^�C�g����3],[...4],[...5],[...6],[...7],[�^�C�g����8]
            // (���{��)
            k = 0;
    		for( i = 0; i < iTITLE_Cnt; i++){
        		if( Clb3_CHK_TITLE->Checked[i] == true ){
            		sBuf = sTITLE_JPN->Strings[i];
                    if( k == 0 )	fprintf( stream, "\"%s\"", sBuf.c_str() );
                    else        	fprintf( stream,",\"%s\"", sBuf.c_str() );
                    k++;
                }
            }
    		for( i = k; i < 8; i++){
                fprintf( stream,"," );
            }
            fprintf( stream,"\n" );

            // [�^�C�g����1],[�^�C�g����2],[�^�C�g����3],[...4],[...5],[...6],[...7],[�^�C�g����8]
            // (�p��)
            k = 0;
    		for( i = 0; i < iTITLE_Cnt; i++){
        		if( Clb3_CHK_TITLE->Checked[i] == true ){
            		sBuf = sTITLE_ENG->Strings[i];
                    if( k == 0 )	fprintf( stream, "\"%s\"", sBuf.c_str() );
                    else        	fprintf( stream,",\"%s\"", sBuf.c_str() );
                    k++;
                }
            }
    		for( i = k; i < 8; i++){
                fprintf( stream,"," );
            }
            fprintf( stream,"\n" );

            // ���l�i���s�R�[�h��[CR+LF]�ɕϊ����܂��j
            sBuf = "";
    		for( i = 0; i < Memo3_CHK_REMARK->Lines->Count; i++){
            	sBuf = sBuf + Memo3_CHK_REMARK->Lines->Strings[i];
            	sBuf = sBuf + "[CR+LF]";
            }
			fprintf( stream,"%s\n", sBuf.c_str() );

            // ���b�g��
			fprintf( stream,"%d\n", PgCtr3_LOT->Tag );

          	// [���b�gNo1],[�^�C�g����1],[�^�C�g����2],[�^�C�g����3],[...4],[...5],[...6],[...7],[�^�C�g����8]
            // �w�胍�b�g�����o�͂��܂�
    		for( i = 0; i < PgCtr3_LOT->Tag; i++){

                if( i == 0 ){
                	// 1���b�g��
					sLOTNO = PgCtr3_tst01->Caption.Trim();

                    if( PgCtr3_tst1_Edt1->Tag == 4 )	sBuf1 = GetTitleLotNo( i );
                    else								sBuf1 = PgCtr3_tst1_Edt1->Text;
                    if( PgCtr3_tst1_Edt2->Tag == 4 )	sBuf2 = GetTitleLotNo( i );
                    else								sBuf2 = PgCtr3_tst1_Edt2->Text;
                    if( PgCtr3_tst1_Edt3->Tag == 4 )	sBuf3 = GetTitleLotNo( i );
                    else								sBuf3 = PgCtr3_tst1_Edt3->Text;
                    if( PgCtr3_tst1_Edt4->Tag == 4 )	sBuf4 = GetTitleLotNo( i );
                    else								sBuf4 = PgCtr3_tst1_Edt4->Text;
                    if( PgCtr3_tst1_Edt5->Tag == 4 )	sBuf5 = GetTitleLotNo( i );
                    else								sBuf5 = PgCtr3_tst1_Edt5->Text;
                    if( PgCtr3_tst1_Edt6->Tag == 4 )	sBuf6 = GetTitleLotNo( i );
                    else								sBuf6 = PgCtr3_tst1_Edt6->Text;
                    if( PgCtr3_tst1_Edt7->Tag == 4 )	sBuf7 = GetTitleLotNo( i );
                    else								sBuf7 = PgCtr3_tst1_Edt7->Text;
                    if( PgCtr3_tst1_Edt8->Tag == 4 )	sBuf8 = GetTitleLotNo( i );
                    else								sBuf8 = PgCtr3_tst1_Edt8->Text;
                }
                else {
                	// 2���b�g�ڈȍ~
					sLOTNO = PgCtr3_tst[i+1]->Caption.Trim();

                   	if( PgCtr3_tst1_Edt1->Tag == 4 )	sBuf1 = GetTitleLotNo( i+1 );
                   	else								sBuf1 = PgCtr3_tst_Edt[i+1][0]->Text;
                   	if( PgCtr3_tst1_Edt2->Tag == 4 )	sBuf2 = GetTitleLotNo( i+1 );
                   	else								sBuf2 = PgCtr3_tst_Edt[i+1][1]->Text;
                   	if( PgCtr3_tst1_Edt3->Tag == 4 )	sBuf3 = GetTitleLotNo( i+1 );
                   	else								sBuf3 = PgCtr3_tst_Edt[i+1][2]->Text;
                   	if( PgCtr3_tst1_Edt4->Tag == 4 )	sBuf4 = GetTitleLotNo( i+1 );
                   	else								sBuf4 = PgCtr3_tst_Edt[i+1][3]->Text;
                   	if( PgCtr3_tst1_Edt5->Tag == 4 )	sBuf5 = GetTitleLotNo( i+1 );
                   	else								sBuf5 = PgCtr3_tst_Edt[i+1][4]->Text;
                   	if( PgCtr3_tst1_Edt6->Tag == 4 )	sBuf6 = GetTitleLotNo( i+1 );
                   	else								sBuf6 = PgCtr3_tst_Edt[i+1][5]->Text;
                   	if( PgCtr3_tst1_Edt7->Tag == 4 )	sBuf7 = GetTitleLotNo( i+1 );
                   	else								sBuf7 = PgCtr3_tst_Edt[i+1][6]->Text;
                   	if( PgCtr3_tst1_Edt8->Tag == 4 )	sBuf8 = GetTitleLotNo( i+1 );
                   	else								sBuf8 = PgCtr3_tst_Edt[i+1][7]->Text;
                }

				fprintf( stream,"%s,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\n",
                												sLOTNO.c_str(),
																sBuf1.c_str(),
																sBuf2.c_str(),
																sBuf3.c_str(),
																sBuf4.c_str(),
																sBuf5.c_str(),
																sBuf6.c_str(),
																sBuf7.c_str(),
																sBuf8.c_str());
            }

            // ��؂�
			fprintf( stream,"@@@�o�͍���@@@\n" );

          	// [���b�gNo1],[�^�C�g����1],[�^�C�g����2],[�^�C�g����3],[...4],[...5],[...6],[...7],[�^�C�g����8]
            // �w�胍�b�g�����o�͂��܂�
    		for( i = 0; i < PgCtr3_LOT->Tag; i++){

				if( i == 0 ){
					sLOTNO = PgCtr3_tst01->Caption.Trim();
				}
				else {
					sLOTNO = PgCtr3_tst[i+1]->Caption.Trim();
				}

				Query2->FindFirst();
				while(Query2->Eof == false) {

					sBuf = Query2->FieldValues["LOTNO"];

                    // �Y���̃��b�g�m�����������܂�
                    if( sLOTNO == sBuf ){

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
							// 2003/10/21 A.Tamura [�P��]���܂߂đI�������ɓ����B
							if( !VarIsNull(Query2->FieldValues["TANI"]) ){
								sBuf = sBuf + " " + Query2->FieldValues["TANI"];
							}
							if( sBuf != "" ){

								// �I������Ă��鍀�ڂ����o�͑ΏۂƔ��f���܂�
                                k = 0;
								for( m = 0; m < Clb3_CHK_KOUMOKU->Items->Count; m++){
									if( Clb3_CHK_KOUMOKU->Items->Strings[m] == sBuf ){
                                        if( Clb3_CHK_KOUMOKU->Checked[m] == true ){
											k = 1;
										}
                                        break;
									}
								}
								if( k == 1 ){
									// �o�͍��ځi���荀�ڍs�j���������݂܂�
                                    bOKFlag = true;	//2003/07/22 E.Takase
									fprintf( stream, "%s,%d,",
                                    	                sLOTNO.c_str(),
                                                        iSKB_NO );
                                    fprintf( stream, "\"%s\",\"%s\",\"%s\",\"%s\",%d,%s,%s,",
                                    					Null_S(Query2->FieldValues["KOMK_NM"]).c_str(),
                                                        Null_S(Query2->FieldValues["KOMK_ENG"]).c_str(),
                                                        Null_S(Query2->FieldValues["KOMK_SUB"]).c_str(),
                                                        Null_S(Query2->FieldValues["KOMK_SUB_ENG"]).c_str(),
                                                        AnsiString(Query2->FieldValues["KIKI_NO"]).ToIntDef(0),
                                                        Null_S(Query2->FieldValues["KIKI_NM"]).c_str(),
                                                        Null_S(Query2->FieldValues["TANI"]).c_str() );
                                    dVal1 = Query2->FieldValues["KIKA_NUM1"];
                                    dVal2 = Query2->FieldValues["KIKA_NUM2"];
                                    dVal3 = Query2->FieldValues["KIKA_NUM3"];
                                    fprintf( stream, "%d,%d,%d,%f,%f,%f,%s,",
                                    					AnsiString(Query2->FieldValues["KIKA_TYPE"]).ToIntDef(1),
                                    					AnsiString(Query2->FieldValues["KIKA_KIND"]).ToIntDef(1),
                                    					AnsiString(Query2->FieldValues["KIKA_DECI"]).ToIntDef(0),
                                    					dVal1,
                                    					dVal2,
                                    					dVal3,
                                                        Null_S(Query2->FieldValues["KIKA_STR"]).c_str() );

                                    fprintf( stream, "%d,%d,%d,",
                                       					AnsiString(Query2->FieldValues["KIKA_PRT"]).ToIntDef(0),
                                       					AnsiString(Query2->FieldValues["VALUE_TYPE"]).ToIntDef(0),
                                       					AnsiString(Query2->FieldValues["VALUE_DECI"]).ToIntDef(0) );

                                    // ���荀�ڂ̗L��			2003/08/28 A.Tamura
                                    if( Query2->FieldValues["SOKU_FLG"] == 0 ){
                                    	// �u���肵�Ȃ��v�̎�

                                        //2003/10/22 E.Takase ���������ɒP�ʒǉ�
				                  		//iBuf = GetBeforeLotVal(
                                        //			Null_S(Query2->FieldValues["DTKSHIN"]),
                                        //            Null_S(Query2->FieldValues["LOTNO"]),
					                	//            Null_S(Query2->FieldValues["KOMK_NM"]),
                                    	//			Null_S(Query2->FieldValues["KOMK_SUB"]),
                                    	//			Null_S(Query2->FieldValues["HINBAN_SK"]),
                                    	//			atoi(Null_S(Query2->FieldValues["KIKI_NO"]).c_str()),
                                    	//			atoi(Null_S(Query2->FieldValues["KOMK_NO"]).c_str()),
                                		//			&sReSOKU_SU, &sReKIKA_PRT, &sReVALUE_TYPE,
                                    	//			&sReVALUE_DECI, &sReDISP_VAL_SU, &sReDISP_VAL_AVE,
                                    	//			&sReDISP_VAL_MAX, &sReDISP_VAL_MIN, &sReDISP_OK, sReDISP_VAL );
				                  		iBuf = GetBeforeLotVal(
                                        			Null_S(Query2->FieldValues["DTKSHIN"]),
                                                    Null_S(Query2->FieldValues["LOTNO"]),
					                	            Null_S(Query2->FieldValues["KOMK_NM"]),
                                    				Null_S(Query2->FieldValues["KOMK_SUB"]),
                                    				Null_S(Query2->FieldValues["HINBAN_SK"]),
                                    				atoi(Null_S(Query2->FieldValues["KIKI_NO"]).c_str()),
                                    				atoi(Null_S(Query2->FieldValues["KOMK_NO"]).c_str()),
					                	            Null_S(Query2->FieldValues["TANI"]),
                                					&sReSOKU_SU, &sReKIKA_PRT, &sReVALUE_TYPE,
                                    				&sReVALUE_DECI, &sReDISP_VAL_SU, &sReDISP_VAL_AVE,
                                    				&sReDISP_VAL_MAX, &sReDISP_VAL_MIN, &sReDISP_OK, sReDISP_VAL );
                                    	iReDISP_VAL_SU = sReDISP_VAL_SU.ToIntDef(0);
                                        // 2003/11/5 A.Tamura �����̊Y�����b�g��������Ȃ����ADISP_VAL_SU�́A�o�̓��b�g��SOKU_SU�����܂�
                                        if( iBuf < 0 ){
                                       		sReDISP_VAL_SU = AnsiString(Query2->FieldValues["SOKU_SU"]);
                                        	iReDISP_VAL_SU = 0;
                                        }

										// ���萔�A���ϒl
                                        fprintf( stream, "%s,%s", sReDISP_VAL_SU, sReDISP_VAL_AVE );

                                        // ����l1�`�̒l�ݒ�
										for( m = 0; m < iReDISP_VAL_SU; m++){
 										    fprintf( stream, ",%s", sReDISP_VAL->Strings[m].c_str() );
                                        }

                                        // ����l��10�ɖ����Ȃ��ꍇ�͋󔒂�ݒ�
										for( m = iReDISP_VAL_SU; m < 10; m++){
 										    fprintf( stream, ",%s", " " );
                                        }

                                    }
                                    else {
                                    	// �u���肷��v�̎�

										// ���萔�A���ϒl
                                    	dVal1 = Query2->FieldValues["DISP_VAL_AVE"];
                                        fprintf( stream, "%d,%f,",
                                    					AnsiString(Query2->FieldValues["DISP_VAL_SU"]).ToIntDef(0),
                                    					dVal1 );

                                		// ����l1�`10�̒l�ݒ�
		                                fprintf( stream, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
                                        				Null_S(Query2->FieldValues["DISP_VAL01"]).c_str(),
                                        				Null_S(Query2->FieldValues["DISP_VAL02"]).c_str(),
                                        				Null_S(Query2->FieldValues["DISP_VAL03"]).c_str(),
                                        				Null_S(Query2->FieldValues["DISP_VAL04"]).c_str(),
                                        				Null_S(Query2->FieldValues["DISP_VAL05"]).c_str(),
                                        				Null_S(Query2->FieldValues["DISP_VAL06"]).c_str(),
                                        				Null_S(Query2->FieldValues["DISP_VAL07"]).c_str(),
                                        				Null_S(Query2->FieldValues["DISP_VAL08"]).c_str(),
                                        				Null_S(Query2->FieldValues["DISP_VAL09"]).c_str(),
                                        				Null_S(Query2->FieldValues["DISP_VAL10"]).c_str() );

                                        // ����l11�`�̒l�ݒ�
                                        if( AnsiString(Query2->FieldValues["DISP_VAL_SU"]).ToIntDef(0) > 10 ){
											sBuf = "SELECT * FROM KSD03";
											sBuf += " WHERE DTKSHIN ='" + Edt3_WHR_DTKSHIN->Text + "'";
											sBuf += " AND LOTNO = '" + sLOTNO + "'";
											sBuf += " AND UNQ_NO = " + AnsiString(Query2->FieldValues["UNQ_NO"]);
											sBuf += " ORDER BY SOKU_NO";

											// Initial Query
											Query3->Close();
											Query3->SQL->Clear();
											Query3->SQL->Add(sBuf);
											Query3->Open();
											Query3->Active = true;
 	 										while(Query3->Eof == false) {
			                                    fprintf( stream, ",%s",
                                                			Null_S(Query3->FieldValues["DISP_VAL"]).c_str() );
  	  											Query3->Next();
  	  										}
                                        }
                                    }

                                    fprintf( stream, "\n" );
                             	}
							}
						}
                        else {
							// �o�͍��ځi�󔒍s�j���������݂܂�
							fprintf( stream, "%s,%d,,,,,,,,,,,,,,,,,,,,0,0,,,,,,,,,,\n",
                            					sLOTNO.c_str(),	iSKB_NO);
                        }
					}
					Query2->Next();
				}
        	}
		}

	    // �t�@�C�������
    	fclose(stream);

    }

    //--------------------------------------------------------------------------------------------
    // �ޗ��ؖ����i���ʁj�w���t�@�C���̍쐬
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet4" ){

    	// �o�͓��e�̊m�F��������Ă��Ȃ��ꍇ�́A�������s���܂�
    	if( iNowTab != 4 ){
			Btn1_OUT_CHECKClick(Btn4_OUT_CHECK);
			if( ret_Btn1_OUT_CHECKClick == false ) return;
    	}

    	if( (stream = fopen( sRepData4, "w+" )) != NULL ){
    		// ����Ƀt�@�C�����I�[�v���ł����ꍇ

			// [����̌`��(0=������Ď����I��/1=Excel�I�����Ȃ��A����Ȃ��j],
            // [�i��],
            // [�Ж�],
            // [�[����],
            // [�o�͌`��(0=���{��/1=�p��)],
            // [X�̏o��(0=���Ȃ�/1=����)]
            // [��s�󂯂ďo��(0=���Ȃ�/1=����)]
            // [���b�g�m���̌�(4or5or6)]
            if( Rdo4_WHR_FORMAT_JPN->Checked == true )		iEnglish = 0;
            else											iEnglish = 1;
            if( Rdo4_CHK_X_ON->Checked == true )			iX_OUT = 1;
            else											iX_OUT = 0;
            if( Rdo4_WHR_BLANK_ON->Checked == true )		iBLANK = 1;
            else											iBLANK = 0;
            if( Rdo4_WHR_TYPE1->Checked == true )			sDTKSHIN = Edt4_WHR_DTKSHIN1->Text;
            else											sDTKSHIN = Edt4_WHR_DTKSHIN2->Text;
            if( Rdo4_LOT_KETA4->Checked == true ){			iLOT_KETA = 4;
            } else if( Rdo4_LOT_KETA5->Checked == true ){   iLOT_KETA = 5;
            } else {                                        iLOT_KETA = 6;
            }

			fprintf( stream,"%d,%s,\"%s\",\"%s\",%d,%d,%d,%d\n",
            								iAutoType,
											sDTKSHIN.c_str(),
											Edt4_CHK_CUSTOMER->Text.c_str(),
                                            Edt4_TITLE_MONTH->Text.c_str(),
                                            iEnglish,
                                            iX_OUT,
                                            iBLANK,
                                            iLOT_KETA );

            // [�^�C�g����1],[�^�C�g����2],[�^�C�g����3],[...4],[...5],[�^�C�g����6]
            // (���{��)
            k = 0;
    		for( i = 0; i < iTITLE_Cnt; i++){
        		if( Clb4_CHK_TITLE->Checked[i] == true ){
            		sBuf = sTITLE_JPN->Strings[i];
                    if( k == 0 )	fprintf( stream, "\"%s\"", sBuf.c_str() );
                    else        	fprintf( stream,",\"%s\"", sBuf.c_str() );
                    k++;
                }
            }
    		for( i = k; i < 6; i++){
                fprintf( stream,"," );
            }
            fprintf( stream,"\n" );

            // [�^�C�g����1],[�^�C�g����2],[�^�C�g����3],[...4],[...5],[�^�C�g����6]
            // (�p��)
            k = 0;
    		for( i = 0; i < iTITLE_Cnt; i++){
        		if( Clb4_CHK_TITLE->Checked[i] == true ){
            		sBuf = sTITLE_ENG->Strings[i];
                    if( k == 0 )	fprintf( stream, "\"%s\"", sBuf.c_str() );
                    else        	fprintf( stream,",\"%s\"", sBuf.c_str() );
                    k++;
                }
            }
    		for( i = k; i < 6; i++){
                fprintf( stream,"," );
            }
            fprintf( stream,"\n" );

          	// [�^�C�g����1],[�^�C�g����2],[�^�C�g����3],[...4],[...5],[�^�C�g����6]
            if( PgCtr4_tst1_Edt1->Tag == 4 )	sBuf1 = "";
            else								sBuf1 = PgCtr4_tst1_Edt1->Text;
            if( PgCtr4_tst1_Edt2->Tag == 4 )	sBuf2 = "";
            else								sBuf2 = PgCtr4_tst1_Edt2->Text;
            if( PgCtr4_tst1_Edt3->Tag == 4 )	sBuf3 = "";
            else								sBuf3 = PgCtr4_tst1_Edt3->Text;
            if( PgCtr4_tst1_Edt4->Tag == 4 )	sBuf4 = "";
            else								sBuf4 = PgCtr4_tst1_Edt4->Text;
            if( PgCtr4_tst1_Edt5->Tag == 4 )	sBuf5 = "";
            else								sBuf5 = PgCtr4_tst1_Edt5->Text;
            if( PgCtr4_tst1_Edt6->Tag == 4 )	sBuf6 = "";
            else								sBuf6 = PgCtr4_tst1_Edt6->Text;
			fprintf( stream,"\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\n",
            										sBuf1.c_str(),
												    sBuf2.c_str(),
												    sBuf3.c_str(),
												    sBuf4.c_str(),
												    sBuf5.c_str(),
												    sBuf6.c_str());

            // ���l�i���s�R�[�h��[CR+LF]�ɕϊ����܂��j
            sBuf = "";
    		for( i = 0; i < Memo4_CHK_REMARK->Lines->Count; i++){
            	sBuf = sBuf + Memo4_CHK_REMARK->Lines->Strings[i];
            	sBuf = sBuf + "[CR+LF]";
            }
			fprintf( stream,"%s\n", sBuf.c_str() );

            // ���b�g��
            k = 0;
    		for( i = 0; i < Clb4_CHK_LOT->Items->Count; i++){
        		if( Clb4_CHK_LOT->Checked[i] == true )	k++;
            }
			fprintf( stream,"%d\n", k );

            // ��؂�
			fprintf( stream,"@@@�o�͍���@@@\n" );

			// �w�胍�b�g�����o�͂��܂�
			for( i = 0; i < Clb2_CHK_LOT->Items->Count; i++){
				if( Clb2_CHK_LOT->Checked[i] == true ){

					// �o�͑Ώۂ̃��b�g���擾���܂�
					sLOTNO = Clb2_CHK_LOT->Items->Strings[i];

					// �I������Ă��鍀�ڂ����o�͑ΏۂƔ��f���܂�
					for( m = 0; m < Clb2_CHK_KOUMOKU->Items->Count; m++){
						if( Clb2_CHK_KOUMOKU->Checked[m] == true ){

							// 2003/10/21 A.Tamura
							// �Ώۃ��b�g�̏o�͂��������荀�ڂ��Ώۃ��b�g�ɖ��������ꍇ�A���̃��b�g�ɗL��͂��̑��荀�ڂ���
							// ���荀�ږ��A�K�i�Ȃǂ��擾���A�_�~�[�s�iCSV�j���o�͂���ׂ̃��[�v
							// ���̃��[�v���Q��ڂ̎��́A����ɊY������
							for( k = 0; k < 2; k++ ){
								
								Query2->FindFirst();
								while(Query2->Eof == false) {

									sBuf = Query2->FieldValues["LOTNO"];

									// �Y���̃��b�g�m�����������܂�
									// 2003/10/21 A.Tamura ���̃��[�v���Q��ڂ̎��́A�_�~�[�s�iCSV�j���o�͏���
									if( sLOTNO == sBuf || k == 1 ){

										// ���荀�ڂƂ��ďo�͂��܂��B
										iSKB_NO = AnsiString(Query2->FieldValues["SKB_NO"]).ToIntDef(9);
										if( iSKB_NO != 9 ){

											// �Ώۃ��R�[�h�̑��荀�ڂ��擾���܂��B
											sBuf = "";
											if( !VarIsNull(Query2->FieldValues["KOMK_NM"]) ){
												sBuf = Query2->FieldValues["KOMK_NM"];
											}
											if( !VarIsNull(Query2->FieldValues["KOMK_SUB"]) ){
												sBuf = sBuf + " " + Query2->FieldValues["KOMK_SUB"];
											}
											// 2003/10/21 A.Tamura [�P��]���܂߂đI�������ɓ����B
											if( !VarIsNull(Query2->FieldValues["TANI"]) ){
												sBuf = sBuf + " " + Query2->FieldValues["TANI"];
											}
											if( sBuf != "" ){
												// �Ώۃ��R�[�h���I������Ă��鑪�荀�ڂƓ������ǂ������f���܂��B
												if( Clb2_CHK_KOUMOKU->Items->Strings[m] == sBuf ){
													
													// �Y�����R�[�h����
													if( k == 0 )	k = 2;

													// �o�͍��ځi���荀�ڍs�j���������݂܂�
													bOKFlag = true;	//2003/07/22 E.Takase
													fprintf( stream, "%s,%d,",
																		sLOTNO.c_str(),
																		iSKB_NO );
													fprintf( stream, "\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",",
																		Null_S(Query2->FieldValues["KOMK_NM"]).c_str(),
																		Null_S(Query2->FieldValues["KOMK_ENG"]).c_str(),
																		Null_S(Query2->FieldValues["KOMK_SUB"]).c_str(),
																		Null_S(Query2->FieldValues["KOMK_SUB_ENG"]).c_str(),
																		AnsiString(Query2->FieldValues["KIKI_NO"]).ToIntDef(0),
																		Null_S(Query2->FieldValues["KIKI_NM"]).c_str(),
																		Null_S(Query2->FieldValues["TANI"]).c_str() );
													dVal1 = Query2->FieldValues["KIKA_NUM1"];
													dVal2 = Query2->FieldValues["KIKA_NUM2"];
													dVal3 = Query2->FieldValues["KIKA_NUM3"];
													if( iSKB_NO == 2 && AnsiString(Query2->FieldValues["KOMK_NO"]).ToIntDef(0) == 1 ){
														sBuf = " ";
													}
													else {
														sBuf = Null_S(Query2->FieldValues["KIKA_STR"]).c_str();
													}
													fprintf( stream, "%d,%d,%d,%f,%f,%f,%s,",
																		AnsiString(Query2->FieldValues["KIKA_TYPE"]).ToIntDef(1),
																		AnsiString(Query2->FieldValues["KIKA_KIND"]).ToIntDef(1),
																		AnsiString(Query2->FieldValues["KIKA_DECI"]).ToIntDef(0),
																		dVal1,
																		dVal2,
																		dVal3,
																		sBuf );

													fprintf( stream, "%d,%d,%d,",
																		AnsiString(Query2->FieldValues["KIKA_PRT"]).ToIntDef(0),
																		AnsiString(Query2->FieldValues["VALUE_TYPE"]).ToIntDef(0),
																		AnsiString(Query2->FieldValues["VALUE_DECI"]).ToIntDef(0) );

													// ���荀�ڂ̗L��			2003/08/28 A.Tamura
													// 2003/10/21 A.Tamura ���̃��[�v���Q��ڂ̎��́A�_�~�[�s�iCSV�j���o�͏���
													if( Query2->FieldValues["SOKU_FLG"] == 0 || k == 1 ){
														// �u���肵�Ȃ��v�̎�

                                                        // �O���b�g���瓯���l�����p���i�擾�j���܂�
                                                        //2003/10/22 E.Takase ���������ɒP�ʒǉ�
														//iBuf = GetBeforeLotVal(
														//			Null_S(Query2->FieldValues["DTKSHIN"]),
														//			sLOTNO,
														//			Null_S(Query2->FieldValues["KOMK_NM"]),
														//			Null_S(Query2->FieldValues["KOMK_SUB"]),
														//			Null_S(Query2->FieldValues["HINBAN_SK"]),
														///			atoi(Null_S(Query2->FieldValues["KIKI_NO"]).c_str()),
														//			atoi(Null_S(Query2->FieldValues["KOMK_NO"]).c_str()),
														//			&sReSOKU_SU, &sReKIKA_PRT, &sReVALUE_TYPE,
														//	 		&sReVALUE_DECI, &sReDISP_VAL_SU, &sReDISP_VAL_AVE,
														//			&sReDISP_VAL_MAX, &sReDISP_VAL_MIN, &sReDISP_OK, sReDISP_VAL );
														iBuf = GetBeforeLotVal(
																	Null_S(Query2->FieldValues["DTKSHIN"]),
																	sLOTNO,
																	Null_S(Query2->FieldValues["KOMK_NM"]),
																	Null_S(Query2->FieldValues["KOMK_SUB"]),
																	Null_S(Query2->FieldValues["HINBAN_SK"]),
																	atoi(Null_S(Query2->FieldValues["KIKI_NO"]).c_str()),
																	atoi(Null_S(Query2->FieldValues["KOMK_NO"]).c_str()),
																	Null_S(Query2->FieldValues["TANI"]),
																	&sReSOKU_SU, &sReKIKA_PRT, &sReVALUE_TYPE,
																	&sReVALUE_DECI, &sReDISP_VAL_SU, &sReDISP_VAL_AVE,
																	&sReDISP_VAL_MAX, &sReDISP_VAL_MIN, &sReDISP_OK, sReDISP_VAL );
														iReDISP_VAL_SU = sReDISP_VAL_SU.ToIntDef(0);
                                                        // 2003/11/5 A.Tamura �����̊Y�����b�g��������Ȃ����ADISP_VAL_SU�́A�o�̓��b�g��SOKU_SU�����܂�
                                                        if( iBuf < 0 ){
                                                        	sReDISP_VAL_SU = AnsiString(Query2->FieldValues["SOKU_SU"]);
                                                        	iReDISP_VAL_SU = 0;
                                                        }

														// ���萔�A���ϒl�A�ő�l�A�ŏ��l
                                                        //2003/11/26 E.Takase
														//fprintf( stream, "%s,%s,%s,%s,",
														fprintf( stream, "%s,%s,%s,%s",
																			sReDISP_VAL_SU,
                                                                            sReDISP_VAL_AVE,
																			sReDISP_VAL_MAX,
																			sReDISP_VAL_MIN);

														// ����l1�`�̒l�ݒ�
														for( p = 0; p < iReDISP_VAL_SU; p++){
															fprintf( stream, ",%s", sReDISP_VAL->Strings[p].c_str() );
														}

														// ����l��10�ɖ����Ȃ��ꍇ�͋󔒂�ݒ�
														for( p = iReDISP_VAL_SU; p < 10; p++){
															fprintf( stream, ",%s", " " );
														}

													}
													else {
														// �u���肷��v�̎�

														// ���萔�A���ϒl�A�ő�l�A�ŏ��l
														dVal1 = Query2->FieldValues["DISP_VAL_AVE"];
														dVal2 = Query2->FieldValues["DISP_VAL_MAX"];
														dVal3 = Query2->FieldValues["DISP_VAL_MIN"];
														fprintf( stream, "%d,%f,%f,%f,",
																			AnsiString(Query2->FieldValues["DISP_VAL_SU"]).ToIntDef(0),
																			dVal1,
																			dVal2,
																			dVal3 );

														// ����l1�`10�̒l�ݒ�
														fprintf( stream, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
																			Null_S(Query2->FieldValues["DISP_VAL01"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL02"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL03"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL04"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL05"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL06"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL07"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL08"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL09"]).c_str(),
																			Null_S(Query2->FieldValues["DISP_VAL10"]).c_str() );

														// ����l11�`�̒l�ݒ�
														if( AnsiString(Query2->FieldValues["DISP_VAL_SU"]).ToIntDef(0) > 10 ){
															sBuf = "SELECT * FROM KSD03";
															sBuf += " WHERE DTKSHIN ='" + sDTKSHIN + "'";
															sBuf += " AND LOTNO = '" + sLOTNO + "'";
															sBuf += " AND UNQ_NO = " + AnsiString(Query2->FieldValues["UNQ_NO"]);
															sBuf += " ORDER BY SOKU_NO";

															// Initial Query
															Query3->Close();
															Query3->SQL->Clear();
															Query3->SQL->Add(sBuf);
															Query3->Open();
															Query3->Active = true;
															while(Query3->Eof == false) {
																fprintf( stream, ",%s",
																			Null_S(Query3->FieldValues["DISP_VAL"]).c_str() );
																Query3->Next();
															}
														}
													}
													fprintf( stream, "\n" );
													
													break;
												}
											}
										}
									}
									Query2->Next();
									
								}	// While
							}
						}
					}	// for m end
				}
			}	// for i end

		}

	    // �t�@�C�������
    	fclose(stream);

    }

	//--------------------------------------------------------------------------------------------
	//2003.04.23 Takase
	// �������ʎ��n��Ǘ��[�f�[�^�̃t�@�C���̍쐬
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet5" ){
    	// �o�͓��e�̊m�F��������Ă��Ȃ��ꍇ�́A�������s���܂�
    	if( iNowTab != 5 ){
			Btn1_OUT_CHECKClick(Btn5_OUT_CHECK);
			if( ret_Btn1_OUT_CHECKClick == false ) return;
    	}
        //2003/08/27 E.Takase
        //���b�gNO�̌������w��
        if ( Rdo5_LOT_KETA4->Checked == true ) {
        	iLOTNO_OUT_Length = 4;
        } else {
        	if ( Rdo5_LOT_KETA5->Checked == true ) {
        		iLOTNO_OUT_Length = 5;
        	} else {
        		iLOTNO_OUT_Length = 6;
        	}
        }
	    bOKFlag = CreateReportSub5(iAutoType);
	}

	//--------------------------------------------------------------------------------------------
	//2003.04.23 Takase
	//�����o��\�f�[�^�̃t�@�C���̍쐬
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet6" ){
    	// �o�͓��e�̊m�F��������Ă��Ȃ��ꍇ�́A�������s���܂�
    	if( iNowTab != 6 ){
			Btn1_OUT_CHECKClick(Btn6_OUT_CHECK);
			if( ret_Btn1_OUT_CHECKClick == false ) return;
    	}
        //2003/08/27 E.Takase
        //���b�gNO�̌������w��
		iLOTNO_OUT_Length = 6;
	    bOKFlag = CreateReportSub6(iAutoType);
	}

    //2003/07/22 E.Takase
    if ( bOKFlag == false ) {
    	ShowMessage("��������0���ł����B");
     	return;
    }

	//--------------------------------------------------------------------------------------------
	//2003.04.30 Takase
    //Excel�N��
    //--------------------------------------------------------------------------------------------
    // �������я��w�� Excel�N��
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet1" ){
	    // �t�@�C�����X�V�p�ɊJ��
            //20170419 Y.Onishi ��Ver�������я��̏o�͂ɑΉ�
            //strcpy(path,sRepExcel1);
            if (iX_OUT == 2) {
               //Cp,Cpk�̏o�͑I�����͐VVer�ɂďo��
               strcpy(path,sRepExcel7);
            }
            else {
               strcpy(path,sRepExcel1);
            }

	    retDLL = ShellExecute(NULL, "open", path, "", "", SW_HIDE);
	}

    //--------------------------------------------------------------------------------------------
    // �������я��i���ʁj Excel�N��
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet2" ){
	    strcpy(path,sRepExcel2);
	    retDLL = ShellExecute(NULL, "open", path, "", "", SW_HIDE);
	}

    //--------------------------------------------------------------------------------------------
    // �ޗ��ؖ����w�� Excel�N��
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet3" ){
	    strcpy(path,sRepExcel3);
	    retDLL = ShellExecute(NULL, "open", path, "", "", SW_HIDE);
	}

    //--------------------------------------------------------------------------------------------
    // �ޗ��ؖ����i���ʁj Excel�N��
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet4" ){
	    strcpy(path,sRepExcel4);
	    retDLL = ShellExecute(NULL, "open", path, "", "", SW_HIDE);
	}


    //--------------------------------------------------------------------------------------------
    // �������ʎ��n��Ǘ��[ Excel�N��
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet5" ){
	    strcpy(path,sRepExcel5);
	    retDLL = ShellExecute(NULL, "open", path, "", "", SW_HIDE);
	}

	//--------------------------------------------------------------------------------------------
	//�����o��\�f�[�^�̃t�@�C���̍쐬
	if( PgCtr_REPORT->ActivePage->Name == "TabSheet6" ){
	    strcpy(path,sRepExcel6);
	    retDLL = ShellExecute(NULL, "open", path, "", "", SW_HIDE);
	}

	//--------------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------------

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F����������̃��b�gNO��Ԃ��܂�
//
//  �@�\����
//    �w�肵�����b�g�̃^�u���őI������Ă��郍�b�g�̌����w����l���������b�gNo��Ԃ��܂�
//
//  �p�����^����
//    int iTabSheetNo	�F�Ώۂ̃V�[�gNO
//
//  �߂�l
//    AnsiString		�F����������̃��b�gNO
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::GetTitleLotNo(int iTabSheetNo)
{

    int				iLen, iPos;
    AnsiString		sBuf;
    TTabSheet*		tst_LOTNO;
    TRadioButton*	rdo_LOT4;
    TRadioButton*	rdo_LOT5;


    if( PgCtr_REPORT->ActivePage->Name == "TabSheet1" ||
    	PgCtr_REPORT->ActivePage->Name == "TabSheet3" ){
		// �������я�
		// �ޗ��ؖ���	�̂ݑΏہi�������s�j�Ƃ��܂�
    } else {
        sBuf = "";
    	return( sBuf );
    }


    if( iTabSheetNo == 0 ){

		if( PgCtr_REPORT->ActivePage->Name == "TabSheet1" ){
	        // �������я�
	        tst_LOTNO	= dynamic_cast<TTabSheet*>(PgCtr1_tst01);
	    	rdo_LOT4	= dynamic_cast<TRadioButton*>(PgCtr1_tst1_LOT4);
	    	rdo_LOT5	= dynamic_cast<TRadioButton*>(PgCtr1_tst1_LOT5);
		}
        else {
        	// �ޗ��ؖ���
	        tst_LOTNO	= dynamic_cast<TTabSheet*>(PgCtr3_tst01);
	    	rdo_LOT4	= dynamic_cast<TRadioButton*>(PgCtr3_tst1_LOT4);
	    	rdo_LOT5	= dynamic_cast<TRadioButton*>(PgCtr3_tst1_LOT5);
	    }

		sBuf = tst_LOTNO->Caption.Trim();
        if( rdo_LOT4->Checked == true ){
        	// �E����S�����p
	        iLen = sBuf.Length();
            iPos = iLen - 4;
            if( iPos > 0 ){
            	sBuf = sBuf.SubString( iPos + 1, 4 );
        	}
        }
        if( rdo_LOT5->Checked == true ){
        	// �E����T�����p
	        iLen = sBuf.Length();
            iPos = iLen - 5;
            if( iPos > 0 ){
            	sBuf = sBuf.SubString( iPos + 1, 5 );
        	}
        }
        // �t���U���o�͂Ȃ̂ŉ������Ȃ��Ăn�j
        //if( PgCtr1_tst1_LOT6->Checked == true ){
        //	// �E����U�����p
        //
        //}
    } else{

		if( PgCtr_REPORT->ActivePage->Name == "TabSheet1" ){
	        // �������я�
	        tst_LOTNO	= dynamic_cast<TTabSheet*>(PgCtr1_tst[iTabSheetNo]);
	    	rdo_LOT4	= dynamic_cast<TRadioButton*>(PgCtr1_tst_LOT[iTabSheetNo][0]);
	    	rdo_LOT5	= dynamic_cast<TRadioButton*>(PgCtr1_tst_LOT[iTabSheetNo][1]);
		}
        else {
        	// �ޗ��ؖ���
	        tst_LOTNO	= dynamic_cast<TTabSheet*>(PgCtr3_tst[iTabSheetNo]);
	    	rdo_LOT4	= dynamic_cast<TRadioButton*>(PgCtr3_tst_LOT[iTabSheetNo][0]);
	    	rdo_LOT5	= dynamic_cast<TRadioButton*>(PgCtr3_tst_LOT[iTabSheetNo][1]);
	    }

        sBuf = tst_LOTNO->Caption.Trim();
        if( rdo_LOT4->Checked == true ){
        	// �E����S�����p
	        iLen = sBuf.Length();
            iPos = iLen - 4;
            if( iPos > 0 ){
            	sBuf = sBuf.SubString( iPos + 1, 4 );
        	}
        }
        if( rdo_LOT5->Checked == true ){
        	// �E����T�����p
	        iLen = sBuf.Length();
            iPos = iLen - 5;
            if( iPos > 0 ){
            	sBuf = sBuf.SubString( iPos + 1, 5 );
        	}
        }
        // �t���U���o�͂Ȃ̂ŉ������Ȃ��Ăn�j
        //if( PgCtr1_tst_LOT[iTabSheetNo+1][2]->Checked == true ){
        //	// �E����U�����p
        //
        //}
    }

    return( sBuf );

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�FVariant�^��NULL���u�����N�ɕϊ����܂�
//
//  �@�\����
//    Variant�^�̒l��Null�Ȃ�AnsiString�^�̃u�����N��Ԃ��܂��B
//    Null�o�Ȃ��Ƃ���AnsiString�^�̕���������̂܂ܕԂ��܂��B
//
//  �p�����^����
//    int iTabSheetNo	�F�Ώۂ̃V�[�gNO
//
//  �߂�l
//    AnsiString		�F����������̃��b�gNO
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::Null_S(Variant &vBuf)
{
	AnsiString sBuf;

	if ( vBuf.IsNull() ) {
		sBuf = " ";
	} else {
		sBuf = VarToStr(vBuf);
	}
    if ( Trim(sBuf) == "" ) {
        sBuf = " ";
    }
	return ( sBuf );

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�R�}���h���C�������𕪗��i�������A���[�U���Ȃǁj
//
//  �@�\����
//    �v���O�����N�����̃R�}���h���C�������𕪗����ϐ��ɐݒ肵�܂��B
//    ���[�U�R�[�h�A���[�U���A�����R�[�h�A�������𒊏o���܂�
//
//  �p�����^����
//    AnsiString str	�F�Ώۂ̃V�[�gNO
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �v���O�����N�����Ɏg�p
//
//---------------------------------------------------------------------------
void __fastcall TForm1::ExtractCode_Report(AnsiString str)
{
    int i,n1,m,strlen;

    //������
    USER_COD = 0;
    USER_NAM = "";
    BUMO_COD = "";
    BUMO_NAM = "";
    AUTO_DTKSHIN = "";
    AUTO_LOTNO = "";

    strlen = str.Length();
    n1 = m = 1;

    for ( i = 1; i <= strlen; i++ ) {
        //��؂�L��","�̌���
        if ( str.SubString(i,1) == "," ) {
            if ( n1 < i ) {
            //n1=i�̎��͕�����NULL
                switch(m){
                //�ϐ��ɕ�������
                    case 1:
                    //USER_COD
                        USER_COD = StrToInt(str.SubString(n1,i - n1));
                        break;
                    case 2:
                    //USER_NAM
                        USER_NAM = str.SubString(n1,i - n1);
                        break;
                    case 3:
                    //BUMO_COD
                        BUMO_COD = str.SubString(n1,i - n1);
                        break;
                    case 4:
                    //BUMO_NAM
                        BUMO_NAM = str.SubString(n1,i - n1);
                        break;
                    case 5:
                    //���Ӑ�i��
                        AUTO_DTKSHIN = str.SubString(n1,i - n1);
                    //���b�gNo
                        AUTO_LOTNO = str.SubString(i + 1, strlen - i);
                        break;
                    default:
                        break;
                }

            }
            //���̕�����J�n�ʒu
            n1 = i + 1;
            m++;

        }
    }
    if ( m <= 4 ) {
        //BUMO_NAM
        BUMO_NAM = str.SubString(n1,strlen - n1 + 1);
    }

    // �������\��
    PnlBumCode->Caption = BUMO_COD;
    PnlBumName->Caption = BUMO_NAM;
    PnlTanCode->Caption = IntToStr(USER_COD);
    PnlTanName->Caption = USER_NAM;

    if( AUTO_DTKSHIN != "" ){
    	Edt1_WHR_DTKSHIN->Text	= AUTO_DTKSHIN;
    	Edt2_WHR_DTKSHIN1->Text	= AUTO_DTKSHIN;
    	Edt2_WHR_DTKSHIN2->Text	= AUTO_DTKSHIN;
    	Edt3_WHR_DTKSHIN->Text	= AUTO_DTKSHIN;
    	Edt4_WHR_DTKSHIN1->Text	= AUTO_DTKSHIN;
    	Edt4_WHR_DTKSHIN2->Text	= AUTO_DTKSHIN;
    	Edt5_WHR_DTKSHIN1->Text	= AUTO_DTKSHIN;
    	Edt6_WHR_DTKSHIN1->Text	= AUTO_DTKSHIN;
    }
    if( AUTO_LOTNO != "" ){
    	Edt1_WHR_LOTNO->Text	= AUTO_LOTNO;
    	Edt2_WHR_LOTNO1->Text	= AUTO_LOTNO;
    	Edt3_WHR_LOTNO->Text	= AUTO_LOTNO;
    	Edt4_WHR_LOTNO1->Text	= AUTO_LOTNO;
    	Edt5_WHR_LOTNO->Text	= AUTO_LOTNO;
    	Edt6_WHR_LOTNO1->Text	= AUTO_LOTNO;
    }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnEnter�C�x���g	�F�e�R���g���[�����t�H�[�J�X�擾�����Ƃ�
//
//  �@�\����
//    �uF1�F�ꗗ�����v�{�^���̗L���^������ݒ肵�܂�
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
void __fastcall TForm1::FormEnter(TObject *Sender)
{
    if( BtnF01->Focused() )		return;

    // �u�������я��v���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
    if( Edt1_WHR_DTKSHIN->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 1;
        return;
    }

    // �u�������я��v���b�g�Ƀt�H�[�J�X���L��ꍇ
    if( Edt1_WHR_LOTNO->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 2;
        return;
    }

    // �u�������я��v�Ж��Ƀt�H�[�J�X���L��ꍇ
    if( Edt1_CHK_CUSTOMER->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        if( Rdo1_WHR_FORMAT_JPN->Checked )	BtnF01->Tag = 21;
        else                                BtnF01->Tag = 22;
        return;
    }

    // �u�������я�(����)�v���Ӑ�i�ԁi��j�Ƀt�H�[�J�X���L��ꍇ
    if( Edt2_WHR_DTKSHIN1->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 3;
        return;
    }

    // �u�������я�(����)�v���b�g�Ƀt�H�[�J�X���L��ꍇ
    if( Edt2_WHR_LOTNO1->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 4;
        return;
    }

    // �u�������я�(����)�v���Ӑ�i�ԁi���j�Ƀt�H�[�J�X���L��ꍇ
    if( Edt2_WHR_DTKSHIN2->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 5;
        return;
    }

    // �u�������я�(����)�v�o�ד��i���j�Ƀt�H�[�J�X���L��ꍇ
    if( Edt2_WHR_SYUKADATE1->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 6;
        return;
    }

    // �u�������я�(����)�v�o�ד��i���j�Ƀt�H�[�J�X���L��ꍇ
    if( Edt2_WHR_SYUKADATE2->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 7;
        return;
    }

    // �u�������я�(����)�v�Ж��Ƀt�H�[�J�X���L��ꍇ
    if( Edt2_CHK_CUSTOMER->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        if( Rdo2_WHR_FORMAT_JPN->Checked )	BtnF01->Tag = 23;
        else                                BtnF01->Tag = 24;
        return;
    }

    // �u�ޗ��ؖ����v���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
    if( Edt3_WHR_DTKSHIN->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 8;
        return;
    }

    // �u�ޗ��ؖ����v���b�g�Ƀt�H�[�J�X���L��ꍇ
    if( Edt3_WHR_LOTNO->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 9;
        return;
    }

    // �u�ޗ��ؖ����v�Ж��Ƀt�H�[�J�X���L��ꍇ
    if( Edt3_CHK_CUSTOMER->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        if( Rdo3_WHR_FORMAT_JPN->Checked )	BtnF01->Tag = 25;
        else                                BtnF01->Tag = 26;
        return;
    }

    // �u�ޗ��ؖ���(����)�v���Ӑ�i�ԁi��j�Ƀt�H�[�J�X���L��ꍇ
    if( Edt4_WHR_DTKSHIN1->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 10;
        return;
    }

    // �u�ޗ��ؖ���(����)�v���b�g�Ƀt�H�[�J�X���L��ꍇ
    if( Edt4_WHR_LOTNO1->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 11;
        return;
    }

    // �u�ޗ��ؖ���(����)�v���Ӑ�i�ԁi���j�Ƀt�H�[�J�X���L��ꍇ
    if( Edt4_WHR_DTKSHIN2->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 12;
        return;
    }

    // �u�ޗ��ؖ���(����)�v�o�ד��i���j�Ƀt�H�[�J�X���L��ꍇ
    if( Edt4_WHR_SYUKADATE1->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 13;
        return;
    }

    // �u�ޗ��ؖ���(����)�v�o�ד��i���j�Ƀt�H�[�J�X���L��ꍇ
    if( Edt4_WHR_SYUKADATE2->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 14;
        return;
    }

    // �u�ޗ��ؖ���(����)�v�Ж��Ƀt�H�[�J�X���L��ꍇ
    if( Edt4_CHK_CUSTOMER->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        if( Rdo4_WHR_FORMAT_JPN->Checked )	BtnF01->Tag = 27;
        else                                BtnF01->Tag = 28;
        return;
    }

    // �u�������ʎ��n��Ǘ��\�v���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
    if( Edt5_WHR_DTKSHIN1->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 15;
        return;
    }

    // �u�������ʎ��n��Ǘ��\�v���b�g�Ƀt�H�[�J�X���L��ꍇ
    if( Edt5_WHR_LOTNO->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 16;
        return;
    }

    // �u�������ʎ��n��Ǘ��\�v�o�ד��i���j�Ƀt�H�[�J�X���L��ꍇ
    if( Edt5_WHR_SYUKADATE1->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 31;
        return;
    }

    // �u�������ʎ��n��Ǘ��\�v�o�ד��i���j�Ƀt�H�[�J�X���L��ꍇ
    if( Edt5_WHR_SYUKADATE2->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 32;
        return;
    }

    // �u�������ʎ��n��Ǘ��\�v�Ж��i���{��j�Ƀt�H�[�J�X���L��ꍇ
    if( Edt5_CHK_CUSTOMER->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 29;
        return;
    }

    // �u�������ʎ��n��Ǘ��\�v�Ж��i�p��j�Ƀt�H�[�J�X���L��ꍇ
    if( Edt5_CHK_CUSTOMER2->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 30;
        return;
    }

    // �u�����o��[�v���Ӑ�i�ԁi��j�Ƀt�H�[�J�X���L��ꍇ
    if( Edt6_WHR_DTKSHIN1->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 17;
        return;
    }

    // �u�����o��[�v���b�g�Ƀt�H�[�J�X���L��ꍇ
    if( Edt6_WHR_LOTNO1->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 18;
        return;
    }

    // �u�����o��[�v�������i���j�Ƀt�H�[�J�X���L��ꍇ
    if( Edt6_WHR_KENSADATE1->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 19;
        return;
    }

    // �u�����o��[�v�������i���j�Ƀt�H�[�J�X���L��ꍇ
    if( Edt6_WHR_KENSADATE2->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 20;
        return;
    }

    // �uF1�F�ꗗ�����v�{�^�����g���Ȃ��悤�ɂ���
    BtnF01->Enabled = false;
    BtnF01->Tag = 0;


}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnKeyPress�C�x���g�F�P��̕����L�[���������Ƃ��ɔ������܂��B
//
//  �@�\����
//    RETURN�R�[�h���N���A�[���܂�
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    char &Key			�F�L�[�R�[�h
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyPress(TObject *Sender, char &Key)
{
    if( Key == VK_RETURN )   Key = 0;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnChange�C�x���g	�F�ҏW�R���g���[���̃e�L�X�g�ɕύX��������ꂽ�Ƃ��ɔ������܂��B
//
//  �@�\����
//    ���͕���(�V���O���R�[�e�[�V����)�̃`�F�b�N���s�Ȃ��܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �V���O���R�[�e�[�V�����͂c�a�o�^���ɃG���[����������
//    �̂őS�p�̃V���O���R�[�e�[�V�����ɕϊ����܂�
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Edt_ALLChange(TObject *Sender)
{

    int			i;
    AnsiString	sBuf;
    TEdit* edt = dynamic_cast<TEdit*>(Sender);


    sBuf = edt->Text;

    // �V���O���R�[�e�[�V�����͂c�a�o�^���ɃG���[����������
    // �̂őS�p�̃V���O���R�[�e�[�V�����ɕϊ����܂�
    i = sBuf.AnsiPos("'");
    if( i > 0 ){
        sBuf.Delete( i, 1);
        if( edt->MaxLength >= sBuf.Length() + 2 ){
        	sBuf.Insert("�f",i);
    	}
        edt->Text = sBuf;
        edt->SelStart = i + 1;
    }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnChange�C�x���g	�F�ҏW�R���g���[���̃e�L�X�g�ɕύX��������ꂽ�Ƃ��ɔ������܂��B
//
//  �@�\����
//    ���͕���(�V���O���R�[�e�[�V�����A���p�J���})�̃`�F�b�N���s�Ȃ��܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �V���O���R�[�e�[�V�����͂c�a�o�^���ɃG���[����������
//    �̂őS�p�̃V���O���R�[�e�[�V�����ɕϊ����܂�
//    ���p�J���}�̓��|�[�g�o�͎��ɃG���[����������̂őS�p
//    �̃J���}�ɕϊ����܂�
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Edt_ALLChange2(TObject *Sender)
{

    int			i;
    AnsiString	sBuf;
    TEdit* edt = dynamic_cast<TEdit*>(Sender);


    sBuf = edt->Text;

    // �V���O���R�[�e�[�V�����͂c�a�o�^���ɃG���[����������
    // �̂őS�p�̃V���O���R�[�e�[�V�����ɕϊ����܂�
    i = sBuf.AnsiPos("'");
    if( i > 0 ){
        sBuf.Delete( i, 1);
        if( edt->MaxLength >= sBuf.Length() + 2 ){
        	sBuf.Insert("�f",i);
    	}
        edt->Text = sBuf;
        edt->SelStart = i + 1;
    }

    // ���p�J���}�̓��|�[�g�o�͎��ɃG���[����������
    // �̂őS�p�̃J���}�ɕϊ����܂�
    i = sBuf.AnsiPos(",");
    if( i > 0 ){
        sBuf.Delete( i, 1);
        if( edt->MaxLength >= sBuf.Length() + 2 ){
        	sBuf.Insert("�C",i);
    	}
        edt->Text = sBuf;
        edt->SelStart = i + 1;
    }
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F���t������/���폜���܂�
//
//  �@�\����
//    ���t������/���폜���܂�
//
//  �p�����^����
//    AnsiString sYMD	�F���t�����̕�����
//
//  �߂�l
//    AnsiString          ������̕�����
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::DelSEPA( AnsiString sYMD )
{
  int        iPos;
  AnsiString sRet;

  sRet = sYMD ;
  while( ( iPos = sRet.AnsiPos("/")) != 0 ){
      sRet.Delete(iPos, 1) ;

  }
  return ( sRet );

}


//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F"YYYY/MM/DD"�`���̓��t��"Jan DD.YYYY"�`���̓��t�ɕϊ����܂�
//
//  �@�\����
//    "YYYY/MM/DD"�`���̓��t��"Mmm DD.YYYY"�`���̓��t�ɕϊ����܂�
//
//  �p�����^����
//    AnsiString sYMD	�F���t�����̕�����
//
//  �߂�l
//    AnsiString          ������̕�����
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::ToDateEnglish(AnsiString sDate)
{
	AnsiString	sYear;
    AnsiString	sMonth;
    AnsiString	sDay;

    AnsiString	sRet;


    sYear = sDate.SubString(1,4);
    sMonth = sDate.SubString(6,2);
    sDay = sDate.SubString(9,2);

    sRet = "";
    switch(sMonth.ToIntDef(0)){
        case 1:  sRet = "Jan";
        		 break;
        case 2:  sRet = "Feb";
        		 break;
        case 3:  sRet = "Mar";
        		 break;
        case 4:  sRet = "Apr";
        		 break;
        case 5:  sRet = "May";
        		 break;
        case 6:  sRet = "Jun";
        		 break;
        case 7:  sRet = "Jul";
        		 break;
        case 8:  sRet = "Aug";
        		 break;
        case 9:  sRet = "Sep";
        		 break;
        case 10: sRet = "Oct";
        		 break;
        case 11: sRet = "Nov";
        		 break;
        case 12: sRet = "Dec";
        		 break;
    	default: return( sDate );
    }

    sRet = sRet + " " + sDay + "." + sYear;

    return( sRet );
}







