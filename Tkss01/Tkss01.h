//�i�������i�o�ׁj�V�X�e���@�e�[�u���o�^
struct  KSM01_DATA   {          //���i���}�X�^�[
    char	DTKSHIN[21];        //���Ӑ�i��
    char   	REVCNT[4];         	//�����ԍ�
    char   	HINBAN[21];        	//���Еi��
    char  	DTKSCOD[6];        	//���Ӑ�R�[�h
    char  	DTKSNAM[51];        //���Ӑ於��
    char  	ZISNAM[21];         //�ގ����́i�i��j
    char  	HINMEI[61];         //�i��
    char  	DTKSHIN1_SZ[21];    //�f�ޗp���Ӑ�i�ԂP
    char  	DTKSHIN2_SZ[21];    //�f�ޗp���Ӑ�i�ԂQ
    char  	DTKSHIN3_SZ[21];    //�f�ޗp���Ӑ�i�ԂR
    char  	DTKSHIN4_SZ[21];    //�f�ޗp���Ӑ�i�ԂS
    char  	DTKSHIN5_SZ[21];    //�f�ޗp���Ӑ�i�ԂT
    char  	DTKSHIN6_SZ[21];    //�f�ޗp���Ӑ�i�ԂU
    char    LOT_LINK_SZ[2];    	//�f�ރ��b�g�̃����N
    char    SOKUTEI_NUM[3];    	//���荀�ڐ�
    char    OUT_TITLE1[5];     	//���я��^�C�g���o�͍��ڂP
    char    OUT_TITLE2[5];     	//���я��^�C�g���o�͍��ڂQ
    char    OUT_TITLE3[5];     	//���я��^�C�g���o�͍��ڂR
    char    OUT_TITLE4[5];     	//���я��^�C�g���o�͍��ڂS
    char    OUT_TITLE5[5];     	//���я��^�C�g���o�͍��ڂT
    char    OUT_TITLE6[5];     	//���я��^�C�g���o�͍��ڂU
    char    OUT_TITLE7[5];     	//���я��^�C�g���o�͍��ڂV
    char    OUT_TITLE8[5];     	//���я��^�C�g���o�͍��ڂW
    char    X_OUT[2];          	//X�o�[(���ρj�̏o��
    char  	MEMO[129];      	//���l
    char  	ADDYMD[9];         	//�o�^��
    char  	ADDTIM[5];         	//�o�^����
    char  	UPDYMD[9];         	//�ύX��
    char  	UPDTIM[5];         	//�ύX����
    char    UPDCHR[7];         	//�X�V��
    char    UPDCNT[4];         	//�X�V��
    char    UPDNAME[50];        //�\���p�X�V�҃l�[��	//2003.05.17 E.Takase Add
    char    SOKCHR[7];         	//�����                //onishi
} ;

struct KSM02_DATA {       		//���i�K�i���׃}�X�^�[
    char	DTKSHIN[21];        //���Ӑ�i��
    char    REVCNT[5];         	//�����ԍ�
    char    UNQ_NO[5];         	//����NO
    char    ORDER_NO[5];       	//�\���E�����
    char    SKB_NO[2];         	//����NO
    char  	HINBAN_SK[21];      //�i��
    char    KOMK_NO[5];        	//���荀��NO
    char  	KOMK_NM[41];        //���荀�ږ���
    char  	KOMK_ENG[41];       //���荀�ږ��́i�p��j
    char  	KOMK_SUB[21];       //���荀�ڃT�u����
    char  	KOMK_SUB_ENG[21];   //���荀�ڃT�u���́i�p��j
    char    KIKI_NO[3];        	//����@��NO
    char  	KIKI_NM[41];        //����@�햼��
    char  	TANI[21];           //�P��
    char    KIKA_TYPE[2];      	//�K�i�^�C�v
    char    KIKA_KIND[2];      	//�K�i���
    char    KIKA_DECI[2];      	//�K�i�����_�ȉ�����
    char    KIKA_NUM1[13];      //�K�i�l1
    char    KIKA_NUM2[13];      //�K�i�l2
    char    KIKA_NUM3[13];      //�K�i�l3
    char  	KIKA_STR[41];       //�K�i�l����
    char  	KIKA_SUB1[21];      //�K�i�l�T�u1
    char   	KIKA_SUB2[21];      //�K�i�l�T�u2
    char  	KIKA_SUB3[21];      //�K�i�l�T�u3
    char    SOKU_SU[3];        	//����w������
    char    SOKU_FLG[2];       	//���荀�ڂ̗L��
    char    TOKU_FLG[2];       	//���ʍ��ڂ̗L��
    char    KIKA_PRT[2];       	//��������l�̈��
    char    VALUE_TYPE[2];     	//����l�\��
    char    VALUE_DECI[2];     	//����l�����_�ȉ�����
};

struct KSM11_DATA {          	//���荀�ڃ}�X�^�[
    char	KOMK_NO[5];        	//���荀��
    char    ORDER_NO[5];       	//�\���E�����
    char  	KOMK_NM[41];        //���荀�ږ���
    char  	KOMK_ENG[41];       //���荀�ږ��́i�p��j
    char  	KOMK_SUB[21];       //���荀�ڃT�u����
    char  	KOMK_SUB_ENG[21];   //���荀�ڃT�u���́i�p��j
    char    KIKI_NO[3];        	//����@��NO
    char  	KIKI_NM[41];        //����@�햼��
    char  	TANI[21];           //�P��
    char    KIKA_TYPE[2];      	//�K�i�^�C�v
    char    KIKA_KIND[2];      	//�K�i���
    char    KIKA_DECI[2];      	//�K�i�����_�ȉ�����
    char    KIKA_NUM1[13];      //�K�i�l�P
    char    KIKA_NUM2[13];      //�K�i�l�Q
    char    KIKA_NUM3[13];      //�K�i�l�R
    char  	KIKA_STR[41];       //�K�i�l����
    char  	KIKA_SUB1[21];      //�K�i�l�T�u�P
    char  	KIKA_SUB2[21];      //�K�i�l�T�u�Q
    char  	KIKA_SUB3[21];      //�K�i�l�T�u�R
    char    SOKU_SU[3];        	//����w������
    char    SOKU_FLG[2];       	//���荀�ڂ̗L��
    char    TOKU_FLG[2];       	//���ʍ��ڂ̗L��
    char    KIKA_PRT[2];       	//��������l�̈��
    char    VALUE_TYPE[2];     	//����l�\��
    char    VALUE_DECI[2];     	//����l�����_�ȉ�����
    char   	ADDYMD[9];         	//�o�^��
    char   	ADDTIM[5];         	//�o�^����
    char   	UPDYMD[9];         	//�ύX��
    char  	UPDTIM[5];         	//�ύX����
    char   	UPDCHR[7];         	//�X�V��
    char    UPDCNT[4];         	//�X�V��
    char    UPDNAME[50];        //�\���p�X�V�҃l�[��	//2003.05.17 E.Takase Add
};

struct  KSM12_DATA   {          //�ޗ��ؖ����ڃ}�X�^�[
    char	KOMK_NO[5];         //���荀��
    char    ORDER_NO[5];        //�\���E�����
    char  	KOMK_NM[41];        //���荀�ږ���
    char  	KOMK_ENG[41];       //���荀�ږ��́i�p��j
    char  	KOMK_SUB[21];       //���荀�ڃT�u����
    char  	KOMK_SUB_ENG[21];   //���荀�ڃT�u���́i�p��j
    char    KIKI_NO[3];         //����@��NO
    char  	KIKI_NM[41];        //����@�햼��
    char  	TANI[21];           //�P��
    char    KIKA_TYPE[2];       //�K�i�^�C�v
    char    KIKA_KIND[2];       //�K�i���
    char    KIKA_DECI[2];       //�K�i�����_�ȉ�����
    char    KIKA_NUM1[13];      //�K�i�l�P
    char    KIKA_NUM2[13];      //�K�i�l�Q
    char    KIKA_NUM3[13];      //�K�i�l�R
    char  	KIKA_STR[41];       //�K�i�l����
    char  	KIKA_SUB1[21];      //�K�i�l�T�u�P
    char  	KIKA_SUB2[21];      //�K�i�l�T�u�Q
    char  	KIKA_SUB3[21];      //�K�i�l�T�u�R
    char    SOKU_SU[3];         //����w������
    char    SOKU_FLG[2];        //���荀�ڂ̗L��
    char    TOKU_FLG[2];        //���ʍ��ڂ̗L��
    char    KIKA_PRT[2];        //��������l�̈��
    char    VALUE_TYPE[2];      //����l�\��
    char    VALUE_DECI[2];      //����l�����_�ȉ�����
    char  	ADDYMD[9];          //�o�^��
    char  	ADDTIM[5];          //�o�^����
    char  	UPDYMD[9];          //�ύX��
    char  	UPDTIM[5];          //�ύX����
    char    UPDCHR[7];          //�X�V��
    char    UPDCNT[4];          //�X�V��
    char    UPDNAME[50];        //�\���p�X�V�҃l�[��	//2003.05.17 E.Takase Add
};


struct  KSM13_DATA   {          //�f�ޑ��荀�ڃ}�X�^�[
    char	KOMK_NO[5];         //���荀��
    char    ORDER_NO[5];        //�\���E�����
    char  	KOMK_NM[41];        //���荀�ږ���
    char  	KOMK_ENG[41];       //���荀�ږ��́i�p��j
    char  	KOMK_SUB[21];       //���荀�ڃT�u����
    char  	KOMK_SUB_ENG[21];   //���荀�ڃT�u���́i�p��j
    char    KIKI_NO[3];         //����@��NO
    char  	KIKI_NM[41];        //����@�햼��
    char  	TANI[21];           //�P��
    char    KIKA_TYPE[2];       //�K�i�^�C�v
    char    KIKA_KIND[2];       //�K�i���
    char    KIKA_DECI[2];       //�K�i�����_�ȉ�����
    char    KIKA_NUM1[13];      //�K�i�l�P
    char    KIKA_NUM2[13];      //�K�i�l�Q
    char    KIKA_NUM3[13];      //�K�i�l�R
    char  	KIKA_STR[41];       //�K�i�l����
    char  	KIKA_SUB1[21];      //�K�i�l�T�u�P
    char  	KIKA_SUB2[21];      //�K�i�l�T�u�Q
    char  	KIKA_SUB3[21];      //�K�i�l�T�u�R
    char    SOKU_SU[3];         //����w������
    char    SOKU_FLG[2];        //���荀�ڂ̗L��
    char    TOKU_FLG[2];        //���ʍ��ڂ̗L��
    char    KIKA_PRT[2];        //��������l�̈��
    char    VALUE_TYPE[2];      //����l�\��
    char    VALUE_DECI[2];      //����l�����_�ȉ�����
    char  	ADDYMD[9];          //�o�^��
    char  	ADDTIM[5];          //�o�^����
    char  	UPDYMD[9];          //�ύX��
    char  	UPDTIM[5];          //�ύX����
    char    UPDCHR[7];          //�X�V��
    char    UPDCNT[4];          //�X�V��
    char    UPDNAME[50];        //�\���p�X�V�҃l�[��	//2003.05.17 E.Takase Add
};

struct  KSM14_DATA {            //����@�퍀�ڃ}�X�^�[
    char    KIKA_NO[3];         //����NO
    char    ORDER_NO[3];        //�\���E�����
    char  	KIKI_NM[41];        //����@�햼
    char  	ADDYMD[9];          //�o�^��
    char  	ADDTIM[5];          //�o�^����
    char  	UPDYMD[9];          //�ύX��
    char  	UPDTIM[5];          //�ύX����
    char    UPDCHR[7];          //�X�V��
    char    UPDCNT[4];          //�X�V��
    char    UPDNAME[50];        //�\���p�X�V�҃l�[��	//2003.05.17 E.Takase Add
};

struct KSM21_DATA {
	char	KMK_NO[5];
	char	ORDER_NO[5];
	char	KMK_NM_JPN[129];
	char	KMK_NM_ENG[129];
	char	NOUPD_FLG[2];
	char	ADDYMD[9];
    char	ADDTIM[5];
	char	UPDYMD[9];
	char	UPDTIM[5];
	char	UPDCHR[7];
	char	UPDCNT[4];
    char    UPDNAME[50];        //�\���p�X�V�҃l�[��	//2003.05.17 E.Takase Add
};

struct KSD01_DATA {          	//������уf�[�^
    char  	DTKSHIN[21];        //���Ӑ�i��
    char  	LOTNO[7];           //���b�gNo
    char	LOTNO1_SZ[7];	    //�f�ތ����p���b�gNo1
    char 	LOTNO2_SZ[7];       //�f�ތ����p���b�gNO2
    char 	LOTNO3_SZ[7];       //�f�ތ����p���b�gNO3
    char 	LOTNO4_SZ[7];       //�f�ތ����p���b�gNO4
    char 	LOTNO5_SZ[7];       //�f�ތ����p���b�gNO5
    char 	LOTNO6_SZ[7];       //�f�ތ����p���b�gNO6
    char	LOTNOCHANGE1_SZ[2]; //�f�ތ����p���b�g�ύX�t���ONO1
    char	LOTNOCHANGE2_SZ[2]; //�f�ތ����p���b�g�ύX�t���ONO2
    char	LOTNOCHANGE3_SZ[2]; //�f�ތ����p���b�g�ύX�t���ONO3
    char	LOTNOCHANGE4_SZ[2]; //�f�ތ����p���b�g�ύX�t���ONO4
    char	LOTNOCHANGE5_SZ[2]; //�f�ތ����p���b�g�ύX�t���ONO5
    char	LOTNOCHANGE6_SZ[2]; //�f�ތ����p���b�g�ύX�t���ONO6
    char  	HINBAN[21];         //���Еi��
    char  	DTKSCOD[6];         //���Ӑ�R�[�h
    char  	DTKSNAM[51];        //���Ӑ於��
    char  	ZISNAM[21];         //�ގ�����
    char  	HINMEI[61];         //�i��
    char  	DTKSHIN1_SZ[21];    //�f�ޗp���Ӑ�i�ԂP
    char  	DTKSHIN2_SZ[21];    //�f�ޗp���Ӑ�i�ԂQ
    char  	DTKSHIN3_SZ[21];    //�f�ޗp���Ӑ�i�ԂR
    char  	DTKSHIN4_SZ[21];    //�f�ޗp���Ӑ�i�ԂS
    char  	DTKSHIN5_SZ[21];    //�f�ޗp���Ӑ�i�ԂT
    char  	DTKSHIN6_SZ[21];    //�f�ޗp���Ӑ�i�ԂU
    char  	HINBAN1_SZ[21];     //�f�ޗp���Ӑ�i�ԂP
    char  	HINBAN2_SZ[21];     //�f�ޗp���Ӑ�i�ԂQ
    char  	HINBAN3_SZ[21];     //�f�ޗp���Ӑ�i�ԂR
    char  	HINBAN4_SZ[21];     //�f�ޗp���Ӑ�i�ԂS
    char  	HINBAN5_SZ[21];     //�f�ޗp���Ӑ�i�ԂT
    char  	HINBAN6_SZ[21];     //�f�ޗp���Ӑ�i�ԂU
    char    LOT_LINK_SZ[2];    	//�f�ޗp���b�g�̃����N
    char    SOKUTEI_NUM[3];    	//���荀�ڐ�
    char    SOZAI_OK[3];       	//�f�ޔ���
    char    SOZAI_OK_PRT[3];   	//�f�ޔ���@����p
    char    SYUKA_OK[3];       	//�o�ה���
    char    SYUKA_OK_PRT[3];   	//�o�ה���@����p
    char    OUT_TITLE1[5];     	//���я��^�C�g���o�͍��ڂP
    char    OUT_TITLE2[5];     	//���я��^�C�g���o�͍��ڂQ
    char    OUT_TITLE3[5];     	//���я��^�C�g���o�͍��ڂR
    char    OUT_TITLE4[5];     	//���я��^�C�g���o�͍��ڂS
    char    OUT_TITLE5[5];     	//���я��^�C�g���o�͍��ڂT
    char    OUT_TITLE6[5];     	//���я��^�C�g���o�͍��ڂU
    char   	OUT_TITLE7[5];     	//���я��^�C�g���o�͍��ڂV
    char   	OUT_TITLE8[5];     	//���я��^�C�g���o�͍��ڂW
    char   	X_OUT[2];          	//X�o�[�̏o��
    char  	MEMO[129];        	//���l
    char  	SKTYMD_SZ[9];       //�f�ޗp�����
    char  	SKTYMD_SZ_PRT[9];   //�f�ޗp������i����p�j
    char  	SKTYMD[9];         	//�o�חp�����
    char  	SKTYMD_PRT[9];      //�o�חp������i����p�j
    char  	ADDYMD[9];         	//��\�o�^��
    char  	ADDTIM[5];         	//��\�o�^����
    char  	UPDYMD[9];         	//��\�ύX��
    char  	UPDTIM[5];         	//��\�ύX����
    char    UPDCHR[7];         	//��\�X�V��
    char    UPDCNT[4];         	//��\�X�V��

    char  	KOMKNO1_SZ[5];    	//�f�ޗp���Ӑ�i�ԂP
    char  	KOMKNO2_SZ[5];    	//�f�ޗp���Ӑ�i�ԂQ
    char  	KOMKNO3_SZ[5];    	//�f�ޗp���Ӑ�i�ԂR
    char  	KOMKNO4_SZ[5];    	//�f�ޗp���Ӑ�i�ԂS
    char  	KOMKNO5_SZ[5];    	//�f�ޗp���Ӑ�i�ԂT
    char  	KOMKNO6_SZ[5];    	//�f�ޗp���Ӑ�i�ԂU
    char  	KOMKNM1_SZ[41];    	//�f�ޗp���Ӑ�i�ԂP
    char  	KOMKNM2_SZ[41];    	//�f�ޗp���Ӑ�i�ԂQ
    char  	KOMKNM3_SZ[41];    	//�f�ޗp���Ӑ�i�ԂR
    char  	KOMKNM4_SZ[41];    	//�f�ޗp���Ӑ�i�ԂS
    char  	KOMKNM5_SZ[41];    	//�f�ޗp���Ӑ�i�ԂT
    char  	KOMKNM6_SZ[41];    	//�f�ޗp���Ӑ�i�ԂU
    char  	KOMKSUB1_SZ[21];    //�f�ޗp���Ӑ�i�ԂP
    char  	KOMKSUB2_SZ[21];    //�f�ޗp���Ӑ�i�ԂQ
    char  	KOMKSUB3_SZ[21];    //�f�ޗp���Ӑ�i�ԂR
    char  	KOMKSUB4_SZ[21];    //�f�ޗp���Ӑ�i�ԂS
    char  	KOMKSUB5_SZ[21];    //�f�ޗp���Ӑ�i�ԂT
    char  	KOMKSUB6_SZ[21];    //�f�ޗp���Ӑ�i�ԂU
	bool	UPD_FLG;			//�X�V�L��t���O
	bool	SAVE_FLG;			//�ۑ��t���O
    char    UPDNAME[50];        //�\���p�X�V�҃l�[��	//2003.05.17 E.Takase Add

//    char  	HINBAN[9];         	//�H�ǔ��s��
    char  	KOKBNG[7];         	//�H�ǔԍ�
};

struct KSD02_DATA {          	//������і��׃f�[�^
    char  	DTKSHIN[21];        //���Ӑ�i��
    char  	LOTNO[7];          	//���b�gNo
    char  	UNQ_NO[5];         	//�f�ޗp���b�gNO
    char 	ORDER_NO[5];       	//���Еi��
    char   	SKB_NO[2];         	//���Ӑ�R�[�h
    char  	HINBAN_SK[21];      //���Ӑ於��
    char   	KOMK_NO[5];        	//�ގ�����
    char   	KOMK_NM[41];        //�i��
    char	KOMK_ENG[41];       //�f�ޗp���Ӑ�i�ԂP
    char  	KOMK_SUB[21];       //�f�ޗp���Ӑ�i�ԂQ
    char  	KOMK_SUB_ENG[21];   //�f�ޗp���Ӑ�i�ԂR
    char    KIKI_NO[3];        	//����@��NO
    char  	KIKI_NM[41];        //����@�햼��
    char  	TANI[21];           //�P��
    char   	KIKA_TYPE[2];      	//�K�i�^�C�v
    char   	KIKA_KIND[2];      	//�K�i���
    char   	KIKA_DECI[2];      	//�K�i�����_�ȉ�����
    char    KIKA_NUM1[13];      //�K�i�l�P
    char    KIKA_NUM2[13];      //�K�i�l�Q
    char    KIKA_NUM3[13];      //�K�i�l�R
    char  	KIKA_STR[41];       //�K�i�l����
    char  	KIKA_SUB1[21];      //�K�i�l�T�u�P
    char   	KIKA_SUB2[21];      //�K�i�l�T�u�Q
    char   	KIKA_SUB3[21];      //�K�i�l�T�u�R
    char    SOKU_SU[3];        	//����w������
    char   	SOKU_FLG[2];       	//���荀�ڂ̗L��
    char    TOKU_FLG[2];       	//���ʍ��ڂ̗L��
    char    KIKA_PRT[2];       	//��������l�̈��
    char    VALUE_TYPE[2];     	//����l�\��
    char    VALUE_DECI[2];     	//����l�����_�ȉ�����
    char  	SOKU_VAL01[15];     //����l�P
    char 	SOKU_VAL02[15];     //����l�Q
    char  	SOKU_VAL03[15];     //����l�R
    char  	SOKU_VAL04[15];     //����l�S
    char  	SOKU_VAL05[15];     //����l�T
    char  	SOKU_VAL06[15];     //����l�U
    char  	SOKU_VAL07[15];     //����l�V
    char  	SOKU_VAL08[15];     //����l�W
    char  	SOKU_VAL09[15];     //����l�X
    char  	SOKU_VAL10[15];     //����l�P�O
    char    SOKU_VAL_SU[3];    	//������т���
    char    SOKU_VAL_AVE[16];   //���蕽�ϒl
    char    SOKU_VAL_MAX[15];   //����ő�l
    char    SOKU_VAL_MIN[15];   //����ŏ��l
    char    SOKU_OK[3];        	//����l����
    char  	DISP_VAL01[15];     //����p����l�P
    char  	DISP_VAL02[15];     //����p����l�Q
    char  	DISP_VAL03[15];     //����p����l�R
    char  	DISP_VAL04[15];     //����p����l�S
    char  	DISP_VAL05[15];     //����p����l�T
    char  	DISP_VAL06[15];     //����p����l�U
    char  	DISP_VAL07[15];     //����p����l�V
    char  	DISP_VAL08[15];     //����p����l�W
    char  	DISP_VAL09[15];     //����p����l�X
    char  	DISP_VAL10[15];     //����p����l�P�O
    char    DISP_VAL_SU[3];    	//����p������т���
    char    DISP_VAL_AVE[16];   //����p���蕽�ϒl
    char    DISP_VAL_MAX[15];   //����p����ő�l
    char    DISP_VAL_MIN[15];   //����p����ŏ��l
    char    DISP_OK[3];        	//����p����l����
    char  	SKTYMD[9];         	//�����
    char  	ADDYMD[9];         	//�o�^��
    char  	ADDTIM[9];         	//�o�^����
    char  	UPDYMD[9];         	//�ύX��
    char  	UPDTIM[9];         	//�ύX����
    char    UPDCHR[7];         	//�X�V��
    char    UPDCNT[4];         	//�X�V��
    char    UPDNAME[50];        //�\���p�X�V�҃l�[��	//2003.05.17 E.Takase Add

    char  	HINBAN[9];         	//�H�ǔ��s��
    char  	KOKBNG[7];         	//�H�ǔԍ�
};


struct  KSD03_DATA   {          //������ї�O�f�[�^
    char  	DTKSHIN[21];        //���Ӑ�i��
    char  	LOTNO[7];           //���b�gNO
    char    UNQ_NO[5];          //����NO
    char  	SOKU_NO[3];         //����NO�i����ڂ̑���j
    char  	SOKU_VAL[15];       //����l
    char  	DISP_VAL[15];       //����p����l

    char  	HINBAN[9];         	//�H�ǔ��s��
    char  	KOKBNG[7];         	//�H�ǔԍ�
};

struct  KSD11_DATA   {          //������ѕ����f�[�^
    char  	DTKSHIN[21];        //���Ӑ�i��
    char  	LOTNO[7];           //���b�gNO
    char    BNKT_UNQ_NO[5];     //�����p����NO
    char    UNQ_NO[5];          //����NO
    char    KOMK_NO[5];         //���荀��NO
    char    SOKU_SU[3];         //����w������
    char  	SOKU_VAL01[15];     //����l1
    char  	SOKU_VAL02[15];     //����l2
    char  	SOKU_VAL03[15];     //����l3
    char  	SOKU_VAL04[15];     //����l4
    char  	SOKU_VAL05[15];     //����l5
    char  	SOKU_VAL06[15];     //����l6
    char  	SOKU_VAL07[15];     //����l7
    char  	SOKU_VAL08[15];     //����l8
    char 	SOKU_VAL09[15];     //����l9
    char  	SOKU_VAL10[15];     //����l10
    char    SOKU_VAL_SU[3];     //������т���
    char    SOKU_VAL_AVE[16];   //���蕽�ϒl
    char    SOKU_VAL_MAX[16];   //����ő�l
    char    SOKU_VAL_MIN[16];   //����ŏ��l
    char    SOKU_OK[2];         //����l����
    char  	SKTYMD[9];          //�����
    char  	ADDYMD[9];          //�o�^��
    char  	ADDTIM[5];          //�o�^����
    char  	UPDYMD[9];          //�ύX��
    char  	UPDTIM[5];          //�ύX����
    char    UPDCHR[7];          //�X�V��
    char    UPDCNT[4];          //�X�V��
    char    UPDNAME[50];        //�\���p�X�V�҃l�[��	//2003.05.17 E.Takase Add

    char  	HINBAN[9];         	//�H�ǔ��s��
    char  	KOKBNG[7];         	//�H�ǔԍ�
};

struct  KSD12_DATA   {          //������ѕ�����O�f�[�^
    char  	DTKSHIN[21];        //���Ӑ�i��
    char  	LOTNO[7];           //���b�gNO
    char    BNKT_UNQ_NO[5];     //�����p����NO
    char    SOKU_NO[3];         //����NO
    char  	SOKU_VAL[15];       //����l

    char  	HINBAN[9];         	//�H�ǔ��s��
    char  	KOKBNG[7];         	//�H�ǔԍ�
};

struct  KSD21_DATA   {          //�f�ޑ�����уf�[�^
    char  	DTKSHIN[21];        //�f�ތ������̕i��
    char  	LOTNO[7];           //���b�gNO
    char  	HINBAN[21];         //���Еi��
    char  	DTKSCOD[6];         //���Ӑ�R�[�h
    char  	DTKSNAM[51];        //���Ӑ於��
    char  	ZISNAM[21];         //�ގ����́i�i��j
    char    SOKUTEI_NUM[3];     //���荀�ڐ�
    char    SOZAI_OK[2];        //�f�ޔ���
    char  	MEMO[129];          //���l
    char  	SKTYMD[9];          //�����
    char  	ADDYMD[9];          //�o�^��
    char  	ADDTIM[5];          //�o�^����
    char  	UPDYMD[9];          //�ύX��
    char  	UPDTIM[5];          //�ύX����
    char    UPDCHR[7];          //�X�V��
    char    UPDCNT[4];          //�X�V��
    char    UPDNAME[50];        //�\���p�X�V�҃l�[��	//2003.05.17 E.Takase Add

//    char  	HINBAN[9];         	//�H�ǔ��s��
    char  	KOKBNG[7];         	//�H�ǔԍ�
};

struct  KSD22_DATA   {          //�f�ޑ�����і��׃f�[�^
    char  	DTKSHIN[21];        //���Ӑ�i��
    char  	LOTNO[7];           //���b�gNO
    char    UNQ_NO[5];          //����NO
    char    KOMK_NO[5];         //���荀��NO
    char  	KOMK_NM[41];        //���荀�ږ���
    char  	KOMK_ENG[41];       //���荀�ږ��́i�p��j
    char  	KOMK_SUB[21];       //���荀�ڃT�u����
    char  	KOMK_SUB_ENG[21];   //���荀�ڃT�u���́i�p��j
    char    KIKI_NO[3];         //����@��NO
    char  	KIKI_NM[41];        //����@�햼��
    char  	TANI[21];           //�P��
    char    KIKA_TYPE[2];       //�K�i�^�C�v
    char    KIKA_KIND[2];       //�K�i���
    char    KIKA_DECI[2];       //�K�i�����_�ȉ�����
    char    KIKA_NUM1[13];      //�K�i�l�P
    char    KIKA_NUM2[13];      //�K�i�l�Q
    char    KIKA_NUM3[13];      //�K�i�l�R
    char  	KIKA_STR[41];       //�K�i�l����
    char  	KIKA_SUB1[21];      //�K�i�l�T�u�P
    char  	KIKA_SUB2[21];      //�K�i�l�T�u�Q
    char    SOKU_SU[3];         //����w������
	char	VALUE_TYPE[2];		//����l�\��
    char    VALUE_DECI[2];      //����l�����_�ȉ�����
    char  	SOKU_VAL01[15];     //����l�P
    char  	SOKU_VAL02[15];     //����l�Q
    char  	SOKU_VAL03[15];     //����l�R
    char  	SOKU_VAL04[15];     //����l�S
    char  	SOKU_VAL05[15];     //����l�T
    char  	SOKU_VAL06[15];     //����l�U
    char  	SOKU_VAL07[15];     //����l�V
    char  	SOKU_VAL08[15];     //����l�W
    char  	SOKU_VAL09[15];     //����l�X
    char  	SOKU_VAL10[15];     //����l�P�O
    char    SOKU_VAL_SU[3];     //������т���
    char    SOKU_VAL_AVE[14];   //���蕽�ϒl
    char    SOKU_VAL_MAX[13];   //����ő�l
    char    SOKU_VAL_MIN[13];   //����ŏ��l
    char    SOKU_OK[2];         //����l����
    char  	SKTYMD[9];          //�����
    char  	ADDYMD[9];          //�o�^��
    char  	ADDTIM[5];          //�o�^����
    char  	UPDYMD[9];          //�ύX��
    char  	UPDTIM[5];          //�ύX����
    char    UPDCHR[7];          //�X�V��
    char    UPDCNT[4];          //�X�V��
    char    UPDNAME[50];        //�\���p�X�V�҃l�[��	//2003.05.17 E.Takase Add

    char  	HINBAN[9];         	//�H�ǔ��s��
    char  	KOKBNG[7];         	//�H�ǔԍ�
};

struct  KSD23_DATA   {          //�f�ޑ�����ї�O�f�[�^
    char  	DTKSHIN[21];        //���Ӑ�i��
    char  	LOTNO[7];           //���b�gNO
    char    UNQ_NO[5];          //����NO
    char    SOKU_NO[3];         //����NO�i����ڂ̑���j
    char  	SOKU_VAL[15];       //����l

    char  	HINBAN[9];         	//�H�ǔ��s��
    char  	KOKBNG[7];         	//�H�ǔԍ�
};


struct GRAPHADDRESS	{
	int 	GRID;		//Grid�ԍ�
	int 	COL;        //�X�^�[�g�J����
	double 	SUM;        //���b�g���v
	double 	AVE;        //���b�g����
    double 	MAX;        //���b�gMax
	double 	MIN;        //���b�gMin
	int 	NCNT;       //���b�g�T���v����
	char LOTNAME[6]; 	//���b�g��  	//2003.05.17 E.Takase Add
};

struct RSCOM {
	int COMNO;
};

struct KIKAKU {
	char HANI[50];
	char UPLIMIT[20];
	char LOLIMIT[20];
};


struct CELLINFO_DATA {          //������і��׃f�[�^
    char  	DTKSHIN[21];        //���Ӑ�i��
    char  	LOTNO[7];          	//���b�gNo
    char  	UNQ_NO[5];         	//�f�ޗp���b�gNO
    char 	ORDER_NO[5];       	//���Еi��
    char   	SKB_NO[2];         	//���Ӑ�R�[�h
    char  	HINBAN_SK[21];      //���Ӑ於��
    char   	KOMK_NO[5];        	//�ގ�����
    char   	KOMK_NM[41];        //�i��
    char	KOMK_ENG[41];       //�f�ޗp���Ӑ�i�ԂP
    char  	KOMK_SUB[21];       //�f�ޗp���Ӑ�i�ԂQ
    char  	KOMK_SUB_ENG[21];   //�f�ޗp���Ӑ�i�ԂR
    char    KIKI_NO[3];        	//����@��NO
    char  	KIKI_NM[41];        //����@�햼��
    char  	TANI[21];           //�P��
    char   	KIKA_TYPE[2];      	//�K�i�^�C�v
    char   	KIKA_KIND[2];      	//�K�i���
    char   	KIKA_DECI[2];      	//�K�i�����_�ȉ�����
    char    KIKA_NUM1[13];      //�K�i�l�P
    char    KIKA_NUM2[13];      //�K�i�l�Q
    char    KIKA_NUM3[13];      //�K�i�l�R
    char  	KIKA_STR[41];       //�K�i�l����
    char  	KIKA_SUB1[21];      //�K�i�l�T�u�P
    char   	KIKA_SUB2[21];      //�K�i�l�T�u�Q
    char   	KIKA_SUB3[21];      //�K�i�l�T�u�R
    char    SOKU_SU[3];        	//����w������
    char   	SOKU_FLG[2];       	//���荀�ڂ̗L��
    char    TOKU_FLG[2];       	//���ʍ��ڂ̗L��
    char    KIKA_PRT[2];       	//��������l�̈��
    char    VALUE_TYPE[2];     	//����l�\��
    char    VALUE_DECI[2];     	//����l�����_�ȉ�����
    char    SOKU_VAL_SU[3];    	//������т���
    char    SOKU_VAL_AVE[14];   //���蕽�ϒl
    char    SOKU_VAL_MAX[13];   //����ő�l
    char    SOKU_VAL_MIN[13];   //����ŏ��l
    char    SOKU_OK[2];        	//����l����
    char    DISP_VAL_SU[3];    	//����p������т���
    char    DISP_VAL_AVE[14];   //����p���蕽�ϒl
    char    DISP_VAL_MAX[13];   //����p����ő�l
    char    DISP_VAL_MIN[13];   //����p����ŏ��l
    char    DISP_OK[2];        	//����p����l����
    char  	SKTYMD[9];         	//�����
	char	DISP_SKTYMD[9];		//����p�����
    char  	ADDYMD[9];         	//�o�^��
    char  	ADDTIM[5];         	//�o�^����
    char  	UPDYMD[9];         	//�ύX��
    char  	UPDTIM[5];         	//�ύX����
    char    UPDCHR[7];         	//�X�V��
    char    UPDCNT[4];         	//�X�V��
	char	MEMO[130];			//���l
	long	COLOR;
	char	RESULT[15];         //����
	char	DISP_RESULT[15];    //����p����l
	double  MAX;
	double	MIN;
	char	SOZAI_LOTNO[7];		//�f�ޗp���b�g
    int 	JUDGE;				// 0:OK,1:NG,2:���O�����v��
    int 	DISP_JUDGE;			// 0:OK,1:NG,2:���O�����v��
    char    UPDNAME[50];        //�\���p�X�V�҃l�[��	//2003.05.17 E.Takase Add
    bool    INS_ON;
	double  GMAX;
	double	GMIN;

    char  	HINBAN[9];         	//�H�ǔ��s��
    char  	KOKBNG[7];         	//�H�ǔԍ�
};

struct GRAPH_DATA {       		//���i�K�i���׃}�X�^�[
    char	DTKSHIN[21];        //���Ӑ�i��
    char    REVCNT[5];         	//�����ԍ�
    char    UNQ_NO[5];         	//����NO
    char    ORDER_NO[5];       	//�\���E�����
    char    SKB_NO[2];         	//����NO
    char  	HINBAN_SK[21];      //�i��
    char    KOMK_NO[5];        	//���荀��NO
    char  	KOMK_NM[41];        //���荀�ږ���
    char  	KOMK_ENG[41];       //���荀�ږ��́i�p��j
    char  	KOMK_SUB[21];       //���荀�ڃT�u����
    char  	KOMK_SUB_ENG[21];   //���荀�ڃT�u���́i�p��j
    char    KIKI_NO[3];        	//����@��NO
    char  	KIKI_NM[41];        //����@�햼��
    char  	TANI[21];           //�P��
    char    KIKA_TYPE[2];      	//�K�i�^�C�v
    char    KIKA_KIND[2];      	//�K�i���
    char    KIKA_DECI[2];      	//�K�i�����_�ȉ�����
    char    KIKA_NUM1[13];      //�K�i�l1
    char    KIKA_NUM2[13];      //�K�i�l2
    char    KIKA_NUM3[13];      //�K�i�l3
    char  	KIKA_STR[41];       //�K�i�l����
    char  	KIKA_SUB1[21];      //�K�i�l�T�u1
    char   	KIKA_SUB2[21];      //�K�i�l�T�u2
    char  	KIKA_SUB3[21];      //�K�i�l�T�u3
    char    SOKU_SU[3];        	//����w������
    char    SOKU_FLG[2];       	//���荀�ڂ̗L��
    char    TOKU_FLG[2];       	//���ʍ��ڂ̗L��
    char    KIKA_PRT[2];       	//��������l�̈��
    char    VALUE_TYPE[2];     	//����l�\��
    char    VALUE_DECI[2];     	//����l�����_�ȉ�����
	int		GRID_NO;
	double 	MAX;
	double 	MIN;
	double 	GMAX;
	double 	GMIN;
    char    UPDNAME[50];        //�\���p�X�V�҃l�[��	//2003.05.17 E.Takase Add

    char  	HINBAN[9];         	//�H�ǔ��s��
    char  	KOKBNG[7];         	//�H�ǔԍ�
};

struct  BUN_DATA   {          	//������ѕ����f�[�^
    char  	DTKSHIN[21];        //���Ӑ�i��
    char  	LOTNO[7];          	//���b�gNo
	char	BNKT_UNQ_NO[5];		//���׎��ʔԍ�
    char  	UNQ_NO[5];         	//�f�ޗp���b�gNO
    char   	KOMK_NO[5];        	//�ގ�����
    char   	KOMK_NM[41];        //�i��
    char	KOMK_ENG[41];       //�f�ޗp���Ӑ�i�ԂP
    char  	KOMK_SUB[21];       //�f�ޗp���Ӑ�i�ԂQ
    char  	KOMK_SUB_ENG[21];   //�f�ޗp���Ӑ�i�ԂR
    char    KIKI_NO[3];        	//����@��NO
    char  	KIKI_NM[41];        //����@�햼��
    char  	TANI[21];           //�P��
    char   	KIKA_TYPE[2];      	//�K�i�^�C�v
    char   	KIKA_KIND[2];      	//�K�i���
    char   	KIKA_DECI[2];      	//�K�i�����_�ȉ�����
    char    KIKA_NUM1[13];      //�K�i�l�P
    char    KIKA_NUM2[13];      //�K�i�l�Q
    char    KIKA_NUM3[13];      //�K�i�l�R
    char  	KIKA_STR[41];       //�K�i�l����
    char  	KIKA_SUB1[21];      //�K�i�l�T�u�P
    char   	KIKA_SUB2[21];      //�K�i�l�T�u�Q
    char   	KIKA_SUB3[21];      //�K�i�l�T�u�R
    char    SOKU_SU[3];        	//����w������
    char   	SOKU_FLG[2];       	//���荀�ڂ̗L��
    char    TOKU_FLG[2];       	//���ʍ��ڂ̗L��
    char    KIKA_PRT[2];       	//��������l�̈��
    char    VALUE_TYPE[2];     	//����l�\��
    char    VALUE_DECI[2];     	//����l�����_�ȉ�����
	char	SOKU_VAL[99][16];
    char    SOKU_VAL_SU[3];    	//������т���
    char    SOKU_VAL_AVE[16];   //���蕽�ϒl
    char    SOKU_VAL_MAX[15];   //����ő�l
    char    SOKU_VAL_MIN[15];   //����ŏ��l
    char    SOKU_OK[4];        	//����l����
    char  	SKTYMD[9];         	//�����
    char  	ADDYMD[9];         	//�o�^��
    char  	ADDTIM[5];         	//�o�^����
    char  	UPDYMD[9];         	//�ύX��
    char  	UPDTIM[5];         	//�ύX����
    char    UPDCHR[7];         	//�S���҃R�[�h
    char    UPDCNT[4];         	//�X�V��
	char 	UPD_NAME[50];		//�S���Җ�	//2003.05.17 E.Takase Add
	int		COL;
	int		ROW;
	double	MAX;
	double	MIN;

    char  	HINBAN[9];         	//�H�ǔ��s��
    char  	KOKBNG[7];         	//�H�ǔԍ�
};

struct LOTWARI_DATA {
	char LOTNO[7];
	char DTKSHIN1_SZ[21];
	char DTKSHIN2_SZ[21];
	char DTKSHIN3_SZ[21];
	char DTKSHIN4_SZ[21];
	char DTKSHIN5_SZ[21];
	char DTKSHIN6_SZ[21];
	char SOZAI1_LOTNO[7];
	char SOZAI2_LOTNO[7];
	char SOZAI3_LOTNO[7];
	char SOZAI4_LOTNO[7];
	char SOZAI5_LOTNO[7];
	char SOZAI6_LOTNO[7];
};


extern HANDLE hRIRE_LOTWARI_DATA;
extern LOTWARI_DATA *pRIRE_LOTWARI_DATA;
extern HANDLE hSOKU_LOTWARI_DATA;
extern LOTWARI_DATA *pSOKU_LOTWARI_DATA;

struct DTKSHIN_LOT {
    char DTKSIN_SZ[21];
};



extern int     SEQNOMAX;
extern int     USER_COD;
extern String  USER_NAM;
extern String  BUMO_COD;
extern String  BUMO_NAM;
extern bool    DataSave;
extern int 	   RSInputFlag;
extern int     KENSAKU_Mode;           //�ꗗ�������[�h
                                       //�P�F�����\���
                                       //�Q�F���Ӑ�i��
                                       //�R�F���b�gNO

//extern KDB1_DATA Tmp_KDB1;             // �I�������H���\��
//extern KDB1_DATA Cur_Kdb1;             // �I�������q�X�g�O�����f�[�^

extern double E_Screen_Data[3][20];

extern int E_Scale;

extern int KEIJKBN_KM02;                //KM02�̐��i�K�i�̌`��敪
extern int LD_HP_TAN_KM02;                //KM02�̐��i�K�i�̌`��敪
extern int MAGE_TAN_KM02;                //KM02�̐��i�K�i�̌`��敪

extern RSCOM RS232;
extern KIKAKU KIKAKU_MOJI;

extern HANDLE hSOZAI_RIREKI_DATA;		//�f�ޗ����f�[�^
extern HANDLE hSOZAI_SYUKA_DATA; 		//�f�ޏo�חp�f�[�^
extern HANDLE hSOZAI_OR_DATA;    		//�f��OR�f�[�^
extern HANDLE hRIREKI_DATA;      		// �ߋ�����Ώۃ��b�g�f�[�^
extern HANDLE hSYUKA_DATA;       		// �o�חp�f�[�^
extern HANDLE hORDATA;           		//�o��OR�f�[�^
extern HANDLE hRIREKI_DATA;       		// �ߋ�����Ώۃ��b�g�����p
extern HANDLE hSOZAI_RIREKI_LOT; 		// �ߋ�����Ώۃ��b�g�����p
extern HANDLE hKSM01_DATA;

extern KSM01_DATA 	pKSM01_DATA;
extern KSM02_DATA 	pORDATA[100];
extern KSM02_DATA   pSOZAI_OR_DATA[100];

extern GRAPHADDRESS GraphLotAddress[10];	//�O���t�`��Ώ�

//������уf�[�^�p������
extern HANDLE 		hRIRE_KSD01DATA;
extern KSD01_DATA 	*pRIRE_KSD01DATA;
extern HANDLE 		hSOKU_KSD01DATA;
extern KSD01_DATA 	*pSOKU_KSD01DATA;



extern HANDLE 		hKSD01_DATA;
extern KSD01_DATA 	*pKSD01_DATA;

//�Z�����
extern HANDLE hCELLINFO_SOKU_SYUKA;
extern HANDLE hCELLINFO_RIRE_SYUKA;
extern HANDLE hCELLINFO_SOKU_SOZAI;
extern HANDLE hCELLINFO_RIRE_SOZAI;
extern CELLINFO_DATA *pCELLINFO_SOKU_SYUKA;
extern CELLINFO_DATA *pCELLINFO_RIRE_SYUKA;
extern CELLINFO_DATA *pCELLINFO_SOKU_SOZAI;
extern CELLINFO_DATA *pCELLINFO_RIRE_SOZAI;
//�����f�[�^
extern BUN_DATA *pBUN_DATA;

extern AnsiString MSG_00;
extern AnsiString MSG_01;
extern AnsiString MSG_02;
extern AnsiString MSG_03;
extern AnsiString MSG_04;
extern AnsiString MSG_05;
extern AnsiString MSG_06;
extern AnsiString MSG_07;
extern AnsiString MSG_08;
extern AnsiString MSG_09;
extern AnsiString MSG_10;
extern AnsiString MSG_11;
extern AnsiString MSG_12;
extern AnsiString MSG_13;

extern AnsiString Select_Str1;
extern AnsiString Select_Str2;
extern AnsiString Select_Str3;
extern AnsiString Select_Str4;
extern AnsiString Select_Str5;
extern int Select_Cnt;
//extern AnsiString sBuf;
extern AnsiString sMsg2;

#define GAIKAN_NAME_COLOR 0x00FFEEDD
//#define MICRO_COLOR 0x00CEFFCE
#define SOZAI_COLOR 0x00D2FFFF
//����@��J���[�ꗗ
//KIKI_NO = 1 �}�C�N�����[�^
#define MICROMETER_COLOR  0x009FFDD2
//KIKI_NO = 2 �m�M�X
#define NOGISU_COLOR      0x001FFA97
//KIKI_NO = 3 �}�C�N�����[�^���V��
#define MICROTENBIN_COLOR 0x0004DD7B
//KIKI_NO = 4 �V��
#define TENBIN_COLOR      0x00EAF7AC
//KIKI_NO = 5 �ޗ������@
#define ZAIRYOU_COLOR     0x00FFEEDD
//KIKI_NO = 6 ���e�@
#define TOUEIKI_COLOR     0x00D2D2FF
//KIKI_NO = 7 ������
#define KENBIKYO_COLOR    0x00ACACFF
//KIKI_NO = 8 �ʑe�v
#define MENARAKEI_COLOR   0x00D9D9D9
//KIKI_NO = 9 �d�x�vC
#define KOUDOKEI_C_COLOR  0x00AAD5FF
//KIKI_NO = 10 �d�x�vD
#define KOUDOKEI_D_COLOR  0x0080BFFF
//KIKI_NO = 11 ��R�������
#define TEIKOU_COLOR      0x00FED1C9
//KIKI_NO = 12 ���[�h����R�������
#define READTEIKOU_COLOR  0x00FEB8AB
//KIKI_NO = 99 ���̑�
#define ETC_COLOR         0x00F3F3F3
