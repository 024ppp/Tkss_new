//���l���O�o�^�f�[�^
struct KSD91_DATA {
	AnsiString	KENSA_YMD;		//	�����N����
	AnsiString	DTKSHIN;		//	���Ӑ�i��
	AnsiString	HINBAN;			//	���Еi��
	AnsiString	LOTNO;          //  ���b�gNo
	AnsiString	ADDYMD;			//	�o�^��
	AnsiString	ADDTIM;			//	�o�^����
	AnsiString	UPDYMD;			//	�ύX��
	AnsiString	UPDTIM;			//	�ύX����
	int	     	UPDCHR;			//	�X�V��
	int	     	UPDCNT;			//	�X�V��
    AnsiString  MEMO;           //  ���l
};

extern int     SEQNOMAX;
extern int     USER_COD;
extern String  USER_NAM;
extern String  BUMO_COD;
extern String  BUMO_NAM;
extern bool    DataSave;
extern int     KENSAKU_Mode;           // �ꗗ�������[�h
                                       // �P�F�����\���
                                       // �Q�F���Ӑ�i��
                                       // �R�F���b�gNO
/*
// extern KSD91_DATA Tmp_KSD91;           // �I���������l���O�o�^�f�[�^

*/
