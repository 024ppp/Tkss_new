/************************************************************************/
/*	�o�׌����V�X�e��													*/
/*	�v���O������	:prjA3006.c											*/
/*	�p�����[�^	:�Ȃ�													*/
/*	���A���	:�Ȃ�													*/
/*	�������e	:�n���f�B�^�[�~�i������									*/
/*	�쐬���t	:2003/04/16												*/
/*	�쐬��		:���{�d�q�H�Ɗ������ �� ��K							*/
/************************************************************************/
#include <lcd.h>
#include <key.h>
#include <ramf.h>
#include <rs232c.h>
#include <photo.h>
#include <sys_menu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rtc.h>
#include <bcr.h>
#include <buzzer.h>
#include <timer.h>

/*�a�b�s�e�[�u��*/
char bct[32] = {
				0x20,0x00,0x0d,0x01,
				0x05,0x05,0x01,0x01,
				0x0a,0x01,0x01,0x01,
				0x04,0x32,0x03,0x31,
				0x03,0x31,0x03,0x31,
				0x03,0x31,0x03,0x31,
				0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00
        };

int mnSw1;								/*��ԕϐ��P*/
int mnSw2;								/*��ԕϐ��Q*/
int mnAtvMode;							/*�㉺�I����ԕϐ�*/
int mnScr1, mnScr2;						/*�㉺��ʔԍ��ϐ�*/
unsigned long mlKeySts;					/*�L�[���͕ϐ�*/
unsigned long mlKeyStsOld;				/*�O��̃L�[���͕ϐ�*/
int mnCurNum;							/*���݂̎w����*/
int mnTtlNum;							/*���v�̎w����*/
int mnCurPos;							/*���݂̍��� 0:�H��,1:�i��,2:LOT,3:�m�F*/
int mnInputMode;						/*���݂̓��̓��[�h 0:����,1:�p��*/
int mnInputFlag;						/*0:�p��������,1:�p�����͒�*/
char msValue;
int mnKeyRepeat;

char masKoukanNo[7];					/*�H��NO*/
char masHinban[21];						/*���Ӑ�i��*/
char masLotNo[7];						/*���b�gNO*/
char masNewKoukanNo[7];					/*�H��NO*/
char masNewHinban[21];					/*���Ӑ�i��*/
char masNewLotNo[7];					/*���b�gNO*/
char masTmpKoukanNo[7];					/*�H��NO*/
char masTmpHinban[21];					/*���Ӑ�i��*/
char masTmpLotNo[7];					/*���b�gNO*/

void strncpyEx(char * sDisBuf, char * sSorBuf, int nLen)
{
	int n1;

	for(n1 = 0; n1 <= nLen - 1; n1++)
	{
		sDisBuf[n1] = sSorBuf[n1];
	}
}

void memsetEx(char * sBuf, char c, int nLen)
{
	int n1;

	for(n1 = 0; n1 < nLen; n1++)
	{
		sBuf[n1] = c;
	}
}

void fwriteEx(char *sBuf, int nLen, FILE *fp)
{
	int n1;

	for(n1 = 0; n1 < nLen; n1++)
	{
		putc(sBuf[n1] , fp);
	}
}

/*�������r 0:��v,1:�s��v*/
int strncmpEx(char *sDisBuf, char *sSorBuf, int nLen)
{
	int nRet, n1;

	nRet = 0;
	for(n1 = 0; n1 < nLen; n1++)
	{
		if(sDisBuf[n1] == sSorBuf[n1])
		{
			nRet = 1;
			break;
		}
	}

	return nRet;
}

/*�����͍��ڃ`�F�b�N 0:������,1:���͂���*/
int subSpaceCheckEx(char *sBuf, int nLen)
{
	int nRet, n1;

	nRet = 0;
	for(n1 = 0; n1 < nLen; n1++)
	{
		if(sBuf[n1] != ' ')
		{
			nRet = 1;
			break;
		}
	}

	return nRet;
}

/*�H��NO��r -1:���Ȃ�,0:����,1:��Ȃ�,*/
int subKoukanCmpEx(char *sDisBuf, char *sSorBuf, int nLen)
{
	int nRet;
	char s1[100], s2[100];
	long l1, l2;

	nRet = 0;

	strncpyEx(s1, sDisBuf, nLen);
	strncpyEx(s2, sSorBuf, nLen);
	s1[nLen] = '\0';
	s2[nLen] = '\0';
	l1 = atol(s1);
	l2 = atol(s2);

	if(l1 > l2)
	{
		nRet = 1;
	}
	else if(l1 < l2)
	{
		nRet = -1;
	}
	else if(l1 == l2)
	{
		nRet = 0;
	}

	return nRet;
}

/*�}�X�^�[�f�[�^�̃o�C�i���[�T�[�` 0:�����q�b�g,1:�����G���[,-1:����G���[*/
int fncBinarySearch(char *saBarCodeBuf, char *saRetBuf)
{
	FILE *fp;
	long nRec;
	int nRet;
	int nCmp;
	int n1;
	char saReadBuf[100];
	int nCnt;
	char sChar;
	char asTmp[100];
	int nTry;

	if((fp = fopen("master  .dat", "r")) == NULL)	/* �t�@�C���I�[�v���i�K���t�@�C�����W�����A�g���q�R�����j */
	{
//		dspstring("File Open Error!!\r\n");
		return -1;
	}

	fseek(fp, 0, SEEK_SET);
	nRec = 0;

	nCnt = 1000;
	nTry = 0;
	nRet = 0;
	while(1)
	{
		fseek(fp, nRec * 34, SEEK_SET);
		memsetEx(saReadBuf, '\0', sizeof(saReadBuf));
		for(n1 = 0; n1 <= 33; n1++)
		{
			sChar = fgetc(fp);
			if(sChar == EOF)
			{
//				dspstring("eof break\r\n");
				strncpyEx(saReadBuf, "999999", 6);
				nRet = 1;
				break;
			}
			saReadBuf[n1] = sChar;
		}

		nCmp = subKoukanCmpEx(saReadBuf, saBarCodeBuf, 6);

		if(nCmp == 0)
		{
//			dspstring("Search Hit\r\n");
			strncpyEx(saRetBuf, saReadBuf, 32);
			saRetBuf[32] = '\0';
			nRet = 0;
			break;
		}
		else if(nCmp == -1)
		{
			if(nCnt <= 1)
			{
				nTry++;
			}
			else
			{
				nTry = 0;
			}
			nRec = nRec + nCnt;
		}
		else if(nCmp == 1)
		{
			nCnt = nCnt / 2;
			if(nCnt <= 1)
			{
				nTry++;
				nCnt = 1;
			}
			else
			{
				nTry = 0;
			}
			nRec = nRec - nCnt;
		}

		if(nTry >= 100)
		{
//			dspstring("Search Error\r\n");
			saRetBuf[0] = '\0';
			nRet = 1;
			break;
		}
	}

	fclose(fp);	/* �t�@�C���̃N���[�Y */

	return nRet;
}

int fncSijiDataNumGet(void)
{
	FILE *fp;
	int n1;
	char sChar;
	int nEof;
	int nRet;
	int nRec;

	if((fp = fopen("sijidata.dat", "r")) == NULL)	/* �t�@�C���I�[�v���i�K���t�@�C�����W�����A�g���q�R�����j */
	{
//		dspstring("File Open Error!!\r\n");
		return 0;
	}

	fseek(fp, 0, SEEK_SET);

	nEof = 0;
	nRec = 0;
	while(1)
	{
		for(n1 = 0; n1 <= 33; n1++)
		{
			sChar = fgetc(fp);
			if(sChar == EOF)
			{
//				dspstring("eof break\r\n");
				nEof = 1;
				break;
			}
		}
		nRec++;
		if(nEof == 1)
		{
			break;
		}
	}
	nRet = nRec;

	fclose(fp);	/* �t�@�C���̃N���[�Y */

	return nRet;
}

int fncSijiDataRead(void)
{
	FILE *fp;
	char asReadBuf[100];
	int n1;
	char sChar;

	if((fp = fopen("sijidata.dat", "r")) == NULL)	/* �t�@�C���I�[�v���i�K���t�@�C�����W�����A�g���q�R�����j */
	{
//		dspstring("File Open Error!!\r\n");
		memsetEx(masKoukanNo, ' ', 6);
		memsetEx(masHinban, ' ', 20);
		memsetEx(masLotNo, ' ', 6);
		return -1;
	}

	fseek(fp, (mnCurNum - 1) * 34, SEEK_SET);

	for(n1 = 0; n1 <= 33; n1++)
	{
		sChar = fgetc(fp);
		if(sChar == EOF)
		{
//			dspstring("eof break\r\n");
			memsetEx(asReadBuf, ' ', sizeof(asReadBuf));
			break;
		}
		asReadBuf[n1] = sChar;
	}
	strncpyEx(masKoukanNo, &asReadBuf[0], 6);
	strncpyEx(masHinban, &asReadBuf[6], 20);
	strncpyEx(masLotNo, &asReadBuf[26], 6);

	fclose(fp);	/* �t�@�C���̃N���[�Y */

	return 0;
}

int fncSijiDataOneDel(void)
{
	FILE *fp;
	char asReadBuf[100];
	char asSijiData[100][100];
	int n1, nEof, nRec;
	char sChar;
	char asTmp[100];

	if((fp = fopen("sijidata.dat", "r")) == NULL)	/* �t�@�C���I�[�v���i�K���t�@�C�����W�����A�g���q�R�����j */
	{
//		dspstring("File Open Error!!\r\n");
		return -1;
	}

	nRec = 0;
	nEof = 0;
	while(1)
	{
		fseek(fp, nRec * 34, SEEK_SET);
		memsetEx(asReadBuf, '\0', sizeof(asReadBuf));
		for(n1 = 0; n1 <= 33; n1++)
		{
			sChar = fgetc(fp);
			if(sChar == EOF)
			{
//				dspstring("eof break\r\n");
				memsetEx(asReadBuf, ' ', sizeof(asReadBuf));
				nEof = 1;
				break;
			}
			asReadBuf[n1] = sChar;
		}
		if(nEof == 1)
		{
			break;
		}
		strncpyEx(asSijiData[nRec], asReadBuf, 32);
		nRec++;
	}

	fclose(fp);	/* �t�@�C���̃N���[�Y */

	fncSijiDataAllDel();

	if((fp = fopen("sijidata.dat", "a")) == NULL)	/* �t�@�C���I�[�v���i�K���t�@�C�����W�����A�g���q�R�����j */
	{
//		dspstring("File Open Error!!\r\n");
		return -1;
	}

	for(n1 = 0; n1 < mnCurNum - 1; n1++)
	{
		strncpyEx(asTmp, asSijiData[n1], 32);
		asTmp[32] = 0x0d;
		asTmp[33] = 0x0a;
		fwriteEx(asTmp, 34, fp);
	}

	for(n1 = mnCurNum; n1 < mnTtlNum; n1++)
	{
		strncpyEx(asTmp, asSijiData[n1], 32);
		asTmp[32] = 0x0d;
		asTmp[33] = 0x0a;
		fwriteEx(asTmp, 34, fp);
	}

	fclose(fp);	/* �t�@�C���̃N���[�Y */

	return 0;
}

int fncSijiDataInsert(char *asKoukanNo, char *asHinban, char *asLotNo)
{
	FILE *fp;
	char asTmp[100];

	if((fp = fopen("sijidata.dat", "a")) == NULL)	/* �t�@�C���I�[�v���i�K���t�@�C�����W�����A�g���q�R�����j */
	{
//		dspstring("File Open Error!!\r\n");
		return -1;
	}

	strncpyEx(&asTmp[0], asKoukanNo, 6);
	strncpyEx(&asTmp[6], asHinban, 20);
	strncpyEx(&asTmp[26], asLotNo, 6);
	asTmp[32] = 0x0d;
	asTmp[33] = 0x0a;
	fwriteEx(asTmp, 34, fp);

	fclose(fp);	/* �t�@�C���̃N���[�Y */

	return 0;
}

int fncSijiDataUpdate(char *asKoukanNo, char *asHinban, char *asLotNo)
{
	FILE *fp;
	char asReadBuf[100];
	char asSijiData[100][100];
	int n1, nEof, nRec;
	char sChar;
	char asTmp[100];

	if((fp = fopen("sijidata.dat", "r")) == NULL)	/* �t�@�C���I�[�v���i�K���t�@�C�����W�����A�g���q�R�����j */
	{
//		dspstring("File Open Error!!\r\n");
		return -1;
	}

	nRec = 0;
	nEof = 0;
	while(1)
	{
		fseek(fp, nRec * 34, SEEK_SET);
		memsetEx(asReadBuf, '\0', sizeof(asReadBuf));
		for(n1 = 0; n1 <= 33; n1++)
		{
			sChar = fgetc(fp);
			if(sChar == EOF)
			{
//				dspstring("eof break\r\n");
				memsetEx(asReadBuf, ' ', sizeof(asReadBuf));
				nEof = 1;
				break;
			}
			asReadBuf[n1] = sChar;
		}
		if(nEof == 1)
		{
			break;
		}
		strncpyEx(asSijiData[nRec], asReadBuf, 32);
		nRec++;
	}

	fclose(fp);	/* �t�@�C���̃N���[�Y */

	fncSijiDataAllDel();

	if((fp = fopen("sijidata.dat", "a")) == NULL)	/* �t�@�C���I�[�v���i�K���t�@�C�����W�����A�g���q�R�����j */
	{
//		dspstring("File Open Error!!\r\n");
		return -1;
	}

	for(n1 = 0; n1 < mnCurNum - 1; n1++)
	{
		strncpyEx(asTmp, asSijiData[n1], 32);
		asTmp[32] = 0x0d;
		asTmp[33] = 0x0a;
		fwriteEx(asTmp, 34, fp);
	}

	strncpyEx(&asTmp[0], asKoukanNo, 6);
	strncpyEx(&asTmp[6], asHinban, 20);
	strncpyEx(&asTmp[26], asLotNo, 6);
	asTmp[32] = 0x0d;
	asTmp[33] = 0x0a;
	fwriteEx(asTmp, 34, fp);

	for(n1 = mnCurNum; n1 < mnTtlNum; n1++)
	{
		strncpyEx(asTmp, asSijiData[n1], 32);
		asTmp[32] = 0x0d;
		asTmp[33] = 0x0a;
		fwriteEx(asTmp, 34, fp);
	}

	fclose(fp);	/* �t�@�C���̃N���[�Y */

	return 0;
}

int fncSijiDataAllDel(void)
{
	FILE *fp;
	char asTmp[100];

	if((fp = fopen("sijidata.dat", "w")) == NULL)	/* �t�@�C���I�[�v���i�K���t�@�C�����W�����A�g���q�R�����j */
	{
//		dspstring("File Open Error!!\r\n");
		return -1;
	}

	memsetEx(asTmp, '\0', sizeof(asTmp));
	fwriteEx(asTmp, 0, fp);

	fclose(fp);	/* �t�@�C���̃N���[�Y */

	return 0;
}

void subSijiDataTest()
{
	FILE *fp;
	char asTmp[100];

	if((fp = fopen("sijidata.dat", "r")) == NULL)	/* �t�@�C���I�[�v���i�K���t�@�C�����W�����A�g���q�R�����j */
	{
		fp = fopen("sijidata.dat", "w");
		memsetEx(asTmp, '\0', sizeof(asTmp));
		fwriteEx(asTmp, 0, fp);
	}

	fclose(fp);	/* �t�@�C���̃N���[�Y */
}

void subNowDateGet(char *sDate)
{
	char date_tbl[3];
	int year , month , day;

	getdate(date_tbl);/* ���t�̎擾 */
	year = (((int)date_tbl[1]) * 256) + (int)date_tbl[0];
	month = (int)date_tbl[2];
	day = (int)date_tbl[3];
	sprintf(sDate, "%4d%02d%02d " , year , month , day );
}

void subNowTimeGet(char *sTime)
{
	char time_tbl[3];
	int hour , minute , second;

	gettime(time_tbl);/* ���Ԃ̎擾 */
	hour = (int)time_tbl[0];
	minute = (int)time_tbl[1];
	second = (int)time_tbl[2];
	sprintf(sTime, "%02d:%02d:%02d " , hour , minute , second );
}

int fncNowSecontGet(void)
{
	char time_tbl[3];
	int second;

	gettime(time_tbl);/* ���Ԃ̎擾 */
	second = (int)time_tbl[2];
	return second;
}

/*�J�n���*/
void StartScreenDisp(void)
{
	char saTmp[10];
	int nY1, nY2;
	int nScr;

	subNowDateGet(saTmp);
	saTmp[8] = '\0';

	if(mnAtvMode == 1)
	{
		/*��i�I��*/
		nY1 = 1;
		nY2 = 27;
		mnScr1 = 1;
		mnScr2 = 2;
		nScr = 0;
	}
	else
	{
		/*���i�I��*/
		nY1 = 24;
		nY2 = 62;
		mnScr1 = 0;
		mnScr2 = 1;
		nScr = 2;
	}
	SetDisplayType(nY1 , nY2);			/*��ʂ̂R����*/
	SetScrollBar(0 , 0);				/*���0�̃X�N���[���o�[�\��*/
	SetScrollBar(1 , 0);				/*���1�̃X�N���[���o�[�\��*/
	SetScrollBar(2 , 0);				/*���2�̃X�N���[���o�[�\��*/

	SelectActCur(nScr);				/*��ʂɃJ�[�\����\��*/
	dspone(0x0c);					/*��ʂ������A�J�[�\�����z�[���|�W�V�����ֈړ�������B*/

	SelectActCur(mnScr1);				/*��ʂɃJ�[�\����\��*/
	dspone(0x0c);					/*��ʂ������A�J�[�\�����z�[���|�W�V�����ֈړ�������B*/
	SetAbsCharAd(0,0,0);
	dspstring("�w��");
	sprintf(saTmp, "[%02d/%02d]  " , mnCurNum, mnTtlNum);
	saTmp[9] = '\0';
	dspstring(saTmp);
	subNowDateGet(saTmp);
	saTmp[8] = '\0';
	dspstring(saTmp);
	SetAbsCharAd(0,1,0);
	dspstring("1.�ر 3.�S�ر F2.�ؑ�");

	SelectActCur(mnScr2);				/*��ʂɃJ�[�\����\��*/
	dspone(0x0c);					/*��ʂ������A�J�[�\�����z�[���|�W�V�����ֈړ�������B*/

	fncSijiDataRead();

	SetAbsCharAd(0,0,0);
	dspstring("�H��>");
	strncpyEx(saTmp, masKoukanNo, 6);
	saTmp[6] = '\0';
	dspstring(saTmp);
	dspstring("    [�o�^]");

	SetAbsCharAd(0,1,0);
	dspstring("�i��>");
	strncpyEx(saTmp, masHinban, 15);
	saTmp[15] = '\0';
	dspstring(saTmp);

	SetAbsCharAd(0,2,0);
	dspstring("LOT >");
	strncpyEx(saTmp, masLotNo, 6);
	saTmp[6] = '\0';
	dspstring(saTmp);
	dspstring("    ");
	strncpyEx(saTmp, &masHinban[15], 5);
	saTmp[5] = '\0';
	dspstring(saTmp);
}

/*�J�n���(�w�����̂�) 0:�t�@�C������Ǎ���,1:�}����X�V*/
void StartScreenDispEx(int nCode)
{
	char saTmp[10];

	SelectActCur(mnScr1);				/*��ʂɃJ�[�\����\��*/
	SetAbsCharAd(0,0,0);
	dspstring("�w��");
	sprintf(saTmp, "[%02d/%02d]  " , mnCurNum, mnTtlNum);
	saTmp[9] = '\0';
	dspstring(saTmp);

	switch(nCode)
	{
	case 0:
		fncSijiDataRead();
		break;
	case 1:
		strncpyEx(masKoukanNo, masNewKoukanNo, 6);
		strncpyEx(masHinban, masNewHinban, 20);
		strncpyEx(masLotNo, masNewLotNo, 6);
		break;
	case 2:
		strncpyEx(masKoukanNo, masTmpKoukanNo, 6);
		strncpyEx(masHinban, masTmpHinban, 20);
		strncpyEx(masLotNo, masTmpLotNo, 6);
		break;
	}

	SelectActCur(mnScr2);				/*��ʂɃJ�[�\����\��*/
	SetAbsCharAd(5,0,0);
	strncpyEx(saTmp, masKoukanNo, 6);
	saTmp[6] = '\0';
	dspstring(saTmp);

	SetAbsCharAd(5,1,0);
	strncpyEx(saTmp, masHinban, 15);
	saTmp[15] = '\0';
	dspstring(saTmp);

	SetAbsCharAd(5,2,0);
	strncpyEx(saTmp, masLotNo, 6);
	saTmp[6] = '\0';
	dspstring(saTmp);
	SetAbsCharAd(15,2,0);
	strncpyEx(saTmp, &masHinban[15], 5);
	saTmp[5] = '\0';
	dspstring(saTmp);
}

/*�ʸر���*/
void OneClearScreenDisp(void)
{
	SelectActCur(mnScr1);				/*��ʂɃJ�[�\����\��*/
	dspone(0x0c);					/*��ʂ������A�J�[�\�����z�[���|�W�V�����ֈړ�������B*/
	SetAbsCharAd(0,0,0);
	dspstring("�����ް����������܂� ");
	SetAbsCharAd(0,1,0);
	dspstring("Yes...�o�^ No...�ر  ");
}

/*�S�ر���*/
void AllClearScreenDisp(void)
{
	char saTmp[10];

	subNowDateGet(saTmp);
	saTmp[8] = '\0';

	SelectActCur(mnScr2);				/* ��ʂɃJ�[�\����\�� */
	dspone(0x0c);					/*��ʂ������A�J�[�\�����z�[���|�W�V�����ֈړ�������B*/
	SetAbsCharAd(0,0,0);
	dspstring("  �S�Ă̎w���ް���   ");
	SetAbsCharAd(0,1,0);
	dspstring("  �������܂�         ");
	SetAbsCharAd(0,2,0);
	dspstring("Yes...�o�^ No...�ر  ");
}

void subKoukanDisp(int n1)
{
	SetAbsAtb(0, 0, n1);
	SetAbsAtb(1, 0, n1);
	SetAbsAtb(2, 0, n1);
	SetAbsAtb(3, 0, n1);
}

void subHinbanDisp(int n1)
{
	SetAbsAtb(0, 1, n1);
	SetAbsAtb(1, 1, n1);
	SetAbsAtb(2, 1, n1);
	SetAbsAtb(3, 1, n1);
}

void subLotDisp(int n1)
{
	SetAbsAtb(0, 2, n1);
	SetAbsAtb(1, 2, n1);
	SetAbsAtb(2, 2, n1);
	SetAbsAtb(3, 2, n1);
}

void subKakuninDisp(int n1)
{
	SetAbsAtb(16, 0, n1);
	SetAbsAtb(17, 0, n1);
	SetAbsAtb(18, 0, n1);
	SetAbsAtb(19, 0, n1);
}

/*-1:�X�y�[�X�Ȃ�,0:�S�ăX�y�[�X,1 <= n:�r���ɃX�y�[�X����*/
int strlenEx(char *asTmp, int nLen)
{
	int n1;
	int nFlag;

	nFlag = 0;
	for(n1 = nLen - 1; n1 >= 0; n1--)
	{
		if(asTmp[n1] != ' ')
		{
			nFlag = 1;
			break;
		}
	}
	if(nFlag == 0)
	{
		n1 = -1;
	}

	return n1;
}

/*���݂̍��ڂ𔽓]����*/
void subCurPosDisp(void)
{
	int nLoc;

	switch(mnCurPos)
	{
	case 0:		/*�H��*/
		subKoukanDisp(1);
		subHinbanDisp(0);
		subLotDisp(0);
		subKakuninDisp(0);
		break;
	case 1:		/*�i��*/
		subKoukanDisp(0);
		subHinbanDisp(1);
		subLotDisp(0);
		subKakuninDisp(0);
		break;
	case 2:		/*LOT*/
		subKoukanDisp(0);
		subHinbanDisp(0);
		subLotDisp(1);
		subKakuninDisp(0);
		break;
	case 3:		/*�m�F*/
		subKoukanDisp(0);
		subHinbanDisp(0);
		subLotDisp(0);
		subKakuninDisp(1);
		break;
	}
}

/*�J�[�\���ʒu�𔽓]����*/
void subCurPosDispEx(void)
{
	int nLoc;

	switch(mnCurPos)
	{
	case 0:		/*�H��*/
		nLoc = strlenEx(masKoukanNo, 6);
		if(mnInputFlag == 1)
		{
			nLoc--;
		}
		if(nLoc < 0)
		{
			nLoc = 0;
		}
		else if(nLoc < 6 - 1)
		{
			nLoc++;
		}
		SetAbsCharAd(5 + nLoc, 0, 1);	/*���݂̃J�[�\���ʒu�𔽓]������*/
		break;
	case 1:		/*�i��*/
		nLoc = strlenEx(masHinban, 20);
		if(mnInputFlag == 1)
		{
			nLoc--;
		}
		if(nLoc < 0)
		{
			nLoc = 0;
		}
		else if(nLoc < 20 - 1)
		{
			nLoc++;
		}
		if(nLoc >= 15)
		{
			SetAbsCharAd(nLoc, 2, 1);	/*���݂̃J�[�\���ʒu�𔽓]������*/
		}
		else
		{
			SetAbsCharAd(5 + nLoc, 1, 1);	/*���݂̃J�[�\���ʒu�𔽓]������*/
		}
		break;
	case 2:		/*LOT*/
		nLoc = strlenEx(masLotNo, 6);
		if(mnInputFlag == 1)
		{
			nLoc--;
		}
		if(nLoc < 0)
		{
			nLoc = 0;
		}
		else if(nLoc < 6 - 1)
		{
			nLoc++;
		}
		SetAbsCharAd(5 + nLoc, 2, 1);	/*���݂̃J�[�\���ʒu�𔽓]������*/
		break;
	case 3:		/*�m�F*/
		nLoc = strlenEx(masKoukanNo, 6);
		SetAbsCharAd(0, 0, 0);		/*�J�[�\����\��������*/
		break;
	}
}

void subCurPosDel(void)
{
	int nLoc;

	switch(mnCurPos)
	{
	case 0:		/*�H��*/
		nLoc = strlenEx(masTmpKoukanNo, 6);
		if(nLoc == - 1)
		{
			nLoc = 6 - 1;
		}
		masTmpKoukanNo[nLoc] = ' ';
		break;
	case 1:		/*�i��*/
		nLoc = strlenEx(masTmpHinban, 20);
		if(nLoc == - 1)
		{
			nLoc = 20 - 1;
		}
		masTmpHinban[nLoc] = ' ';
		break;
	case 2:		/*LOT*/
		nLoc = strlenEx(masTmpLotNo, 6);
		if(nLoc == - 1)
		{
			nLoc = 6 - 1;
		}
		masTmpLotNo[nLoc] = ' ';
		break;
	}
}

/*�����L�[���͏���*/
void subCurPosIn(void)
{
	int nLoc;

	switch(mlKeySts)
	{
	case 0x4000:	/*1�L�[*/
		msValue = '1';
		break;
	case 0x8000:	/*2�L�[*/
		msValue = '2';
		break;
	case 0x10000:	/*3�L�[*/
		msValue = '3';
		break;
	case 0x800:		/*4�L�[*/
		msValue = '4';
		break;
	case 0x1000:	/*5�L�[*/
		msValue = '5';
		break;
	case 0x2000:	/*6�L�[*/
		msValue = '6';
		break;
	case 0x100:		/*7�L�[*/
		msValue = '7';
		break;
	case 0x200:		/*8�L�[*/
		msValue = '8';
		break;
	case 0x400:		/*9�L�[*/
		msValue = '9';
		break;
	case 0x20000:	/*0�L�[*/
		msValue = '0';
		break;
	case 0x40000:	/*.�L�[*/
		msValue = '.';
		break;
	case 0x80000:	/*SF�L�[*/
		msValue = '-';
		break;
	}

	switch(mnCurPos)
	{
	case 0:		/*�H��*/
		nLoc = strlenEx(masTmpKoukanNo, 6);
		if(nLoc == - 1)
		{
			nLoc = 0;
		}
		else if(nLoc < 6 - 1)
		{
			nLoc++;
		}
		masTmpKoukanNo[nLoc] = msValue;
		break;
	case 1:		/*�i��*/
		nLoc = strlenEx(masTmpHinban, 20);
		if(nLoc == - 1)
		{
			nLoc = 0;
		}
		else if(nLoc < 20 - 1)
		{
			nLoc++;
		}
		masTmpHinban[nLoc] = msValue;
		break;
	case 2:		/*LOT*/
		nLoc = strlenEx(masTmpLotNo, 6);
		if(nLoc == - 1)
		{
			nLoc = 0;
		}
		else if(nLoc < 6 - 1)
		{
			nLoc++;
		}
		masTmpLotNo[nLoc] = msValue;
		break;
	}
}

/*�p���L�[���͏���*/
void subCurPosInEx(void)
{
	int nLoc;
	int nFlag;

	nFlag = 1;
	switch(mlKeySts)
	{
	case 0x4000:	/*STU�L�[*/
		if(msValue != 'S' && msValue != 'T' && msValue != 'U')
		{
			nFlag = 0;
			msValue = 'S';
		}
		else if(msValue == 'S')
		{
			msValue = 'T';
		}
		else if(msValue == 'T')
		{
			msValue = 'U';
		}
		else if(msValue == 'U')
		{
			msValue = 'S';
		}
		break;
	case 0x8000:	/*VWX�L�[*/
		if(msValue != 'V' && msValue != 'W' && msValue != 'X')
		{
			nFlag = 0;
			msValue = 'V';
		}
		else if(msValue == 'V')
		{
			msValue = 'W';
		}
		else if(msValue == 'W')
		{
			msValue = 'X';
		}
		else if(msValue == 'X')
		{
			msValue = 'V';
		}
		break;
	case 0x10000:	/*YZ#�L�[*/
		if(msValue != 'Y' && msValue != 'Z' && msValue != '#')
		{
			nFlag = 0;
			msValue = 'Y';
		}
		else if(msValue == 'Y')
		{
			msValue = 'Z';
		}
		else if(msValue == 'Z')
		{
			msValue = '#';
		}
		else if(msValue == '#')
		{
			msValue = 'Y';
		}
		break;
	case 0x800:		/*JKL�L�[*/
		if(msValue != 'J' && msValue != 'K' && msValue != 'L')
		{
			nFlag = 0;
			msValue = 'J';
		}
		else if(msValue == 'J')
		{
			msValue = 'K';
		}
		else if(msValue == 'K')
		{
			msValue = 'L';
		}
		else if(msValue == 'L')
		{
			msValue = 'J';
		}
		break;
	case 0x1000:	/*MNO�L�[*/
		if(msValue != 'M' && msValue != 'N' && msValue != 'O')
		{
			nFlag = 0;
			msValue = 'M';
		}
		else if(msValue == 'M')
		{
			msValue = 'N';
		}
		else if(msValue == 'N')
		{
			msValue = 'O';
		}
		else if(msValue == 'O')
		{
			msValue = 'M';
		}
		break;
	case 0x2000:	/*PQR�L�[*/
		if(msValue != 'P' && msValue != 'Q' && msValue != 'R')
		{
			nFlag = 0;
			msValue = 'P';
		}
		else if(msValue == 'P')
		{
			msValue = 'Q';
		}
		else if(msValue == 'Q')
		{
			msValue = 'R';
		}
		else if(msValue == 'R')
		{
			msValue = 'P';
		}
		break;
	case 0x100:		/*ABC�L�[*/
		if(msValue != 'A' && msValue != 'B' && msValue != 'C')
		{
			nFlag = 0;
			msValue = 'A';
		}
		else if(msValue == 'A')
		{
			msValue = 'B';
		}
		else if(msValue == 'B')
		{
			msValue = 'C';
		}
		else if(msValue == 'C')
		{
			msValue = 'A';
		}
		break;
	case 0x200:		/*DEF�[*/
		if(msValue != 'D' && msValue != 'E' && msValue != 'F')
		{
			nFlag = 0;
			msValue = 'D';
		}
		else if(msValue == 'D')
		{
			msValue = 'E';
		}
		else if(msValue == 'E')
		{
			msValue = 'F';
		}
		else if(msValue == 'F')
		{
			msValue = 'D';
		}
		break;
	case 0x400:		/*GHI�L�[*/
		if(msValue != 'G' && msValue != 'H' && msValue != 'I')
		{
			nFlag = 0;
			msValue = 'G';
		}
		else if(msValue == 'G')
		{
			msValue = 'H';
		}
		else if(msValue == 'H')
		{
			msValue = 'I';
		}
		else if(msValue == 'I')
		{
			msValue = 'G';
		}
		break;
	case 0x20000:	/*\%/�L�[*/
		if(msValue != '\\' && msValue != '%' && msValue != '/')
		{
			nFlag = 0;
			msValue = '\\';
		}
		else if(msValue == '\\')
		{
			msValue = '%';
		}
		else if(msValue == '%')
		{
			msValue = '/';
		}
		else if(msValue == '/')
		{
			msValue = '\\';
		}
		break;
	case 0x40000:	/**+-�L�[*/
		if(msValue != '*' && msValue != '+' && msValue != '-')
		{
			nFlag = 0;
			msValue = '*';
		}
		else if(msValue == '*')
		{
			msValue = '+';
		}
		else if(msValue == '+')
		{
			msValue = '-';
		}
		else if(msValue == '-')
		{
			msValue = '*';
		}
		break;
	case 0x80000:	/*SP@=�[*/
		if(msValue != '_' && msValue != '@' && msValue != '=')
		{
			nFlag = 0;
			msValue = '_';
		}
		else if(msValue == '_')
		{
			msValue = '@';
		}
		else if(msValue == '@')
		{
			msValue = '=';
		}
		else if(msValue == '=')
		{
			msValue = '_';
		}
		break;
	}

	switch(mnCurPos)
	{
	case 0:		/*�H��*/
		nLoc = strlenEx(masTmpKoukanNo, 6);
		if(nFlag == 1)
		{
			nLoc--;
		}
		if(nLoc < 0)
		{
			nLoc = 0;
		}
		else if(nLoc < 6 - 1)
		{
			nLoc++;
		}
		masTmpKoukanNo[nLoc] = msValue;
		break;
	case 1:		/*�i��*/
		nLoc = strlenEx(masTmpHinban, 20);
		if(nFlag == 1)
		{
			nLoc--;
		}
		if(nLoc < 0)
		{
			nLoc = 0;
		}
		else if(nLoc < 20 - 1)
		{
			nLoc++;
		}
		masTmpHinban[nLoc] = msValue;
		break;
	case 2:		/*LOT*/
		nLoc = strlenEx(masTmpLotNo, 6);
		if(nFlag == 1)
		{
			nLoc--;
		}
		if(nLoc < 0)
		{
			nLoc = 0;
		}
		else if(nLoc < 6 - 1)
		{
			nLoc++;
		}
		masTmpLotNo[nLoc] = msValue;
		break;
	}
}

/*�J�n��ʂł̏���*/
void StartScreenProc(void)
{
	char rbca[64];
	int n1, bsts, nLen;
	char asTmp[100];
	int nRet;
	char asBarCodeBuf[100];

	switch(mnSw2)
	{
	case 1:
		StartScreenDisp();
		mnSw2++;
		break;
	case 2:
		if((mlKeySts & 0x200000) != 0)	/*F2�L�[*/
		{
			if(mnAtvMode == 1)
			{
				mnAtvMode = 2;		/*���i�I��*/
				mnCurPos = 0;		/*���݂̍��ڂ�������*/
				mnInputMode = 0;	/*�������̓��[�h*/
				strncpyEx(masNewKoukanNo, masKoukanNo, 6);
				strncpyEx(masNewHinban, masHinban, 20);
				strncpyEx(masNewLotNo, masLotNo, 6);
				strncpyEx(masTmpKoukanNo, masKoukanNo, 6);
				strncpyEx(masTmpHinban, masHinban, 20);
				strncpyEx(masTmpLotNo, masLotNo, 6);
//				memsetEx(masTmpKoukanNo, ' ', 6);		/*�H�Ǖϐ���������*/
//				memsetEx(masTmpHinban, ' ', 20);		/*�i�ԕϐ���������*/
//				memsetEx(masTmpLotNo, ' ', 6);			/*LOT�ϐ���������*/
			}
			else
			{
				mnAtvMode = 1;		/*��i�I��*/
				memsetEx(masNewKoukanNo, ' ', 6);
				memsetEx(masNewHinban, ' ', 20);
				memsetEx(masNewLotNo, ' ', 6);
				memsetEx(masTmpKoukanNo, ' ', 6);		/*�H�Ǖϐ���������*/
				memsetEx(masTmpHinban, ' ', 20);		/*�i�ԕϐ���������*/
				memsetEx(masTmpLotNo, ' ', 6);			/*LOT�ϐ���������*/
			}
			StartScreenDisp();
			if(mnAtvMode == 1)
			{
				/*��i�I��*/
//				subKoukanDisp(0);
//				subHinbanDisp(0);
//				subLotDisp(0);
//				subKakuninDisp(0);
			}
			else
			{
				/*���i�I��*/
				subCurPosDisp();
				subCurPosDispEx();
			}
		}
		if(mnAtvMode == 1)
		{
			/*��i�I��*/
			if((mlKeySts & 0x4000) != 0)		/*1�L�[*/
			{
				if(mnCurNum <= mnTtlNum)		/*�N���A����*/
				{
					mnSw1 = 2;
					mnSw2 = 1;
				}
			}
			else if((mlKeySts & 0x10000) != 0)	/*3�L�[*/
			{
				if(mnTtlNum != 0)				/*�N���A����*/
				{
					mnSw1 = 3;
					mnSw2 = 1;
				}
			}
			else if((mlKeySts & 0x8) != 0 || (mlKeySts & 0x4) != 0)	/*���L�[���́��L�[*/
			{
				if(mnKeyRepeat == 0)
				{
					mnCurNum--;
				}
				else
				{
					mnCurNum -= 10;
				}
				if(mnCurNum < 1)
				{
					mnCurNum = 1;
				}
				StartScreenDispEx(0);
			}
			else if((mlKeySts & 0x10) != 0 || (mlKeySts & 0x20) != 0)	/*���L�[���́��L�[*/
			{
				if(mnKeyRepeat == 0)
				{
					mnCurNum++;
				}
				else
				{
					mnCurNum += 10;
				}
				if(mnCurNum > 99)
				{
					mnCurNum = 99;
				}
				else if(mnCurNum > mnTtlNum + 1)
				{
					mnCurNum = mnTtlNum + 1;
				}
				StartScreenDispEx(0);
			}
			else if((mlKeySts & 0x1) != 0 || (mlKeySts & 0x2) != 0)		/*���E�g���K*/
			{
				if(mnTtlNum == 99)
				{
					/*�w���f�[�^�������ő�ɒB���܂���*/
					erbz1();								/*�G���[�u�U�[������ 200ms*3��*/
					break;
				}
				while(1)
				{
					bsts = readbc(rbca);		/* �o�[�R�[�h�̓ǂݎ�� */
					if((bsts >> 8) == 0x0)
					{
						/*�L�[���͂��ꂽ�ꍇ*/
						kbin();
						break;
					}
					else
					{
						/*�o�[�R�[�h���X�L�������ꂽ�ꍇ*/
						nLen = rbca[1];								/* �o�[�R�[�h�f�[�^�̃T�C�Y�̎擾 */
						memsetEx(asBarCodeBuf, ' ', 32);
						strncpyEx(&asBarCodeBuf[0], &rbca[2], nLen);
						if(nLen <= 0 || nLen > 6)
						{
							erbz1();								/*�G���[�u�U�[������ 200ms*3��*/
							mnCurPos = 0;							/*���݂̍��ڂ��m�F�ɂ���*/
						}
						else
						{
							nRet = fncBinarySearch(asBarCodeBuf, asTmp);
							if(nRet == 0)
							{
								/*�}�X�^�[�f�[�^�ɊY���f�[�^������*/
								strncpyEx(masNewKoukanNo, &asTmp[0], 6);
								strncpyEx(masNewHinban, &asTmp[6], 20);
								strncpyEx(masNewLotNo, &asTmp[26], 6);
								strncpyEx(masTmpKoukanNo, &asTmp[0], 6);
								strncpyEx(masTmpHinban, &asTmp[6], 20);
								strncpyEx(masTmpLotNo, &asTmp[26], 6);
								mnCurPos = 3;						/*���݂̍��ڂ��m�F�ɂ���*/
							}
							else
							{
								/*�}�X�^�[�f�[�^�ɊY���f�[�^������*/
								erbz1();					/*�G���[�u�U�[������ 200ms*3��*/
								strncpyEx(masNewKoukanNo, &asBarCodeBuf[0], 6);
								memsetEx(masNewHinban, ' ', 20);	/*�i�ԕϐ���������*/
								memsetEx(masNewLotNo, ' ', 6);		/*LOT�ϐ���������*/
								strncpyEx(masTmpKoukanNo, &asBarCodeBuf[0], 6);		/*�H�Ǖϐ���������*/
								memsetEx(masTmpHinban, ' ', 20);	/*�i�ԕϐ���������*/
								memsetEx(masTmpLotNo, ' ', 6);		/*LOT�ϐ���������*/
								mnCurPos = 1;						/*���݂̍��ڂ��m�F�ɂ���*/
							}
						}
						mnAtvMode = 2;								/*���i�I��*/
						StartScreenDisp();
						mnCurNum = mnTtlNum + 1;
						if(mnCurNum > 99)
						{
							mnCurNum = 99;
						}
						StartScreenDispEx(1);
						subCurPosDisp();
						break;
					}
				}
			}
		}
		else
		{
			/*���i�I��*/
			if((mlKeySts & 0x8) != 0 || (mlKeySts & 0x4) != 0)		/*���L�[���́��L�[*/
			{
				if(mnInputFlag == 0)
				{
					if(mnCurPos != 0)
					{
						mnCurPos--;
					}
					else
					{
						mnCurPos = 3;
					}
					strncpyEx(masTmpKoukanNo, masNewKoukanNo, 6);
					strncpyEx(masTmpHinban, masNewHinban, 20);
					strncpyEx(masTmpLotNo, masNewLotNo, 6);
					StartScreenDispEx(1);
					subCurPosDisp();
				}
				else
				{
					msValue = ' ';
					mnInputFlag = 0;
				}
				subCurPosDispEx();
			}
			else if((mlKeySts & 0x10) != 0 || (mlKeySts & 0x20) != 0)	/*���L�[���́��L�[*/
			{
				if(mnInputFlag == 0)
				{
					if(mnCurPos != 3)
					{
						mnCurPos++;
					}
					else
					{
						mnCurPos = 0;
					}
					strncpyEx(masTmpKoukanNo, masNewKoukanNo, 6);
					strncpyEx(masTmpHinban, masNewHinban, 20);
					strncpyEx(masTmpLotNo, masNewLotNo, 6);
					StartScreenDispEx(1);
					subCurPosDisp();
				}
				else
				{
					msValue = ' ';
					mnInputFlag = 0;
				}
				subCurPosDispEx();
			}
			else if((mlKeySts & 0x40) != 0)	/*�N���A�L�[*/
			{
				subCurPosDel();
				StartScreenDispEx(2);
				subCurPosDispEx();
			}
			else if((mlKeySts & 0x4000) != 0 || (mlKeySts & 0x8000) != 0 || (mlKeySts & 0x10000) != 0 || (mlKeySts & 0x800) != 0 || (mlKeySts & 0x1000) != 0 ||
			(mlKeySts & 0x2000) != 0 || (mlKeySts & 0x100) != 0 || (mlKeySts & 0x200) != 0 || (mlKeySts & 0x400) != 0 || (mlKeySts & 0x20000) != 0 ||
			(mlKeySts & 0x40000) != 0 || (mlKeySts & 0x80000) != 0)	/*�����L�[*/
			{
				if(mnInputMode == 0)
				{
					subCurPosIn();
				}
				else
				{
					mnInputFlag = 1;
					subCurPosInEx();
				}
				StartScreenDispEx(2);
				subCurPosDispEx();
			}
			else if((mlKeySts & 0x100000) != 0)	/*F1�L�[*/
			{
				msValue = ' ';
				mnInputFlag = 0;
				if(mnInputMode == 0)
				{
					mnInputMode = 1;			/*�p�����̓��[�h*/
				}
				else
				{
					mnInputMode = 0;			/*�������̓��[�h*/
				}
			}
			else if((mlKeySts & 0x1) != 0 || (mlKeySts & 0x2) != 0)		/*���E�g���K*/
			{
				msValue = ' ';
				mnInputFlag = 0;
				while(1)
				{
					bsts = readbc(rbca);							/* �o�[�R�[�h�̓ǂݎ�� */
					if((bsts >> 8) == 0x0)
					{
						/*�L�[���͂��ꂽ�ꍇ*/
						kbin();
						break;
					}
					else
					{
						/*�o�[�R�[�h���X�L�������ꂽ�ꍇ*/
						nLen = rbca[1];								/* �o�[�R�[�h�f�[�^�̃T�C�Y�̎擾 */
						memsetEx(asBarCodeBuf, ' ', 32);
						strncpyEx(&asBarCodeBuf[0], &rbca[2], nLen);
						if(nLen <= 0 || nLen > 6)
						{
							erbz1();								/*�G���[�u�U�[������ 200ms*3��*/
						}
						else
						{
							nRet = fncBinarySearch(asBarCodeBuf, asTmp);
							if(nRet == 0)
							{
								/*�}�X�^�[�f�[�^�ɊY���f�[�^������*/
								strncpyEx(masNewKoukanNo, &asTmp[0], 6);
								strncpyEx(masNewHinban, &asTmp[6], 20);
								strncpyEx(masNewLotNo, &asTmp[26], 6);
								strncpyEx(masTmpKoukanNo, &asTmp[0], 6);
								strncpyEx(masTmpHinban, &asTmp[6], 20);
								strncpyEx(masTmpLotNo, &asTmp[26], 6);
								mnCurPos = 3;						/*���݂̍��ڂ��m�F�ɂ���*/
							}
							else
							{
								/*�}�X�^�[�f�[�^�ɊY���f�[�^������*/
								erbz1();							/*�G���[�u�U�[������ 200ms*3��*/
								strncpyEx(masNewKoukanNo, &asBarCodeBuf[0], 6);
								memsetEx(masNewHinban, ' ', 20);	/*�i�ԕϐ���������*/
								memsetEx(masNewLotNo, ' ', 6);		/*LOT�ϐ���������*/
								strncpyEx(masTmpKoukanNo, &asBarCodeBuf[0], 6);		/*�H�Ǖϐ���������*/
								memsetEx(masTmpHinban, ' ', 20);	/*�i�ԕϐ���������*/
								memsetEx(masTmpLotNo, ' ', 6);		/*LOT�ϐ���������*/
								mnCurPos = 1;						/*���݂̍��ڂ��m�F�ɂ���*/
							}
						}
						StartScreenDisp();
						StartScreenDispEx(1);
						subCurPosDisp();
						subCurPosDispEx();
						break;
					}
				}
			}
			else if((mlKeySts & 0x80) != 0)							/*�o�^�L�[*/
			{
				mnInputFlag = 0;
				if(mnCurPos == 0)									/*�H��*/
				{
					/*�o�[�R�[�h���X�L�������ꂽ�ꍇ*/
					nLen = strlenEx(masTmpKoukanNo, 6);
					nLen++;
					memsetEx(asBarCodeBuf, ' ', 32);
					strncpyEx(&asBarCodeBuf[0], masTmpKoukanNo, nLen);
					if(nLen <= 0 || nLen > 6)
					{
						erbz1();									/*�G���[�u�U�[������ 200ms*3��*/
						mnCurPos = 1;								/*���݂̍��ڂ�i�Ԃɂ���*/
					}
					else
					{
						nRet = fncBinarySearch(asBarCodeBuf, asTmp);
						if(nRet == 0)
						{
							/*�}�X�^�[�f�[�^�ɊY���f�[�^������*/
							strncpyEx(masNewKoukanNo, &asTmp[0], 6);
							strncpyEx(masNewHinban, &asTmp[6], 20);
							strncpyEx(masNewLotNo, &asTmp[26], 6);
							mnCurPos = 3;							/*���݂̍��ڂ��m�F�ɂ���*/
						}
						else
						{
							/*�}�X�^�[�f�[�^�ɊY���f�[�^������*/
							erbz1();								/*�G���[�u�U�[������ 200ms*3��*/
							strncpyEx(masNewKoukanNo, &asBarCodeBuf[0], 6);
							memsetEx(masNewHinban, ' ', 20);		/*�i�ԕϐ���������*/
							memsetEx(masNewLotNo, ' ', 6);			/*LOT�ϐ���������*/
							strncpyEx(masTmpKoukanNo, &asBarCodeBuf[0], 6);		/*�H�Ǖϐ���������*/
							memsetEx(masTmpHinban, ' ', 20);		/*�i�ԕϐ���������*/
							memsetEx(masTmpLotNo, ' ', 6);			/*LOT�ϐ���������*/
							mnCurPos = 1;							/*���݂̍��ڂ�i�Ԃɂ���*/
						}
					}
					StartScreenDisp();
					StartScreenDispEx(1);
					subCurPosDisp();
					subCurPosDispEx();
				}
				else if(mnCurPos == 1)
				{
					strncpyEx(masNewHinban, masTmpHinban, 20);		/*�i��*/
					mnCurPos++;
					StartScreenDispEx(1);
					subCurPosDisp();
					subCurPosDispEx();
				}
				else if(mnCurPos == 2)
				{
					strncpyEx(masNewLotNo, masTmpLotNo, 6);		/*LOT*/
					mnCurPos++;
					StartScreenDispEx(1);
					subCurPosDisp();
					subCurPosDispEx();
				}
				else if(mnCurPos == 3)	/*�o�^*/
				{
					if(mnCurNum == mnTtlNum + 1)			/*�w���f�[�^(�V�K)*/
					{
						if(subSpaceCheckEx(masNewHinban, 20) == 0 || subSpaceCheckEx(masNewLotNo, 6) == 0)
						{
							/*�i�Ԗ���LOT�������͍��ڂ���*/
//							ctrlbuzz(0xff, 50, 0);		/*�m�F�p�u�U�[������ ��,50*20ms,�ʏ�*/
//							ctrlbuzz2(0xff, 50, 50, 50);	/*�m�F�p�u�U�[������ ��,50*20ms,50%,50*/
							erbz1();			/*�G���[�u�U�[������ 200ms*3��*/
						}
						else
						{
							/*�w���f�[�^�}��*/
							fncSijiDataInsert(masNewKoukanNo, masNewHinban, masNewLotNo);
							mnTtlNum = fncSijiDataNumGet() - 1;
//							mnAtvMode = 1;					/*��i�I��*/
							mnCurPos = 0;					/*���݂̍��ڂ��H�ǂɂ���*/
							StartScreenDisp();
							mnCurNum = mnTtlNum + 1;
							if(mnCurNum > 99)
							{
								mnCurNum = 99;
							}
							memsetEx(masNewKoukanNo, ' ', 6);
							memsetEx(masNewHinban, ' ', 20);
							memsetEx(masNewLotNo, ' ', 6);
							memsetEx(masTmpKoukanNo, ' ', 6);		/*�H�Ǖϐ���������*/
							memsetEx(masTmpHinban, ' ', 20);		/*�i�ԕϐ���������*/
							memsetEx(masTmpLotNo, ' ', 6);			/*LOT�ϐ���������*/
							StartScreenDispEx(0);
							subCurPosDisp();
							subCurPosDispEx();
						}
					}
					else						/*�w���f�[�^(�X�V)*/
					{
						if(subSpaceCheckEx(masHinban, 20) == 0 || subSpaceCheckEx(masLotNo, 6) == 0)
						{
							/*�i�Ԗ���LOT�������͍��ڂ���*/
							erbz1();			/*�G���[�u�U�[������ 200ms*3��*/
						}
						else
						{
							/*�w���f�[�^�X�V*/
							strncpyEx(masNewKoukanNo, masKoukanNo, 6);
							strncpyEx(masNewHinban, masHinban, 20);
							strncpyEx(masNewLotNo, masLotNo, 6);
							fncSijiDataUpdate(masNewKoukanNo, masNewHinban, masNewLotNo);
							mnCurPos = 0;					/*���݂̍��ڂ��H�ǂɂ���*/
							StartScreenDisp();
							memsetEx(masNewKoukanNo, ' ', 6);
							memsetEx(masNewHinban, ' ', 20);
							memsetEx(masNewLotNo, ' ', 6);
							memsetEx(masTmpKoukanNo, ' ', 6);		/*�H�Ǖϐ���������*/
							memsetEx(masTmpHinban, ' ', 20);		/*�i�ԕϐ���������*/
							memsetEx(masTmpLotNo, ' ', 6);			/*LOT�ϐ���������*/
							StartScreenDispEx(0);
							subCurPosDisp();
							subCurPosDispEx();
						}
					}
				}
			}
		}
		break;
	}
}

/*�ʃN���A��ʂł̏���*/
void OneClearScreenProc(void)
{
	switch(mnSw2)
	{
	case 1:
		OneClearScreenDisp();
		mnSw2++;
		break;
	case 2:
		if((mlKeySts & 0x80) != 0)		/*�o�^�L�[*/
		{

			/*�I���w���f�[�^(�������A�t�@�C��)���폜����B*/
			fncSijiDataOneDel();
			if(mnTtlNum <= 1)
			{
				mnCurNum = 0;
			}
			if(mnTtlNum > 1)
			{
				mnTtlNum--;
			}
			mnSw1 = 1;
			mnSw2 = 1;
		}
		else if((mlKeySts & 0x40) != 0)		/*�N���A�L�[*/
		{
			/*�L�����Z���Ȃ̂Ŗ������Ŕ�����B*/
			mnSw1 = 1;
			mnSw2 = 1;
		}
		break;
	}
}

/*�S�N���A��ʂł̏���*/
void AllClearScreenProc(void)
{
	switch(mnSw2)
	{
	case 1:
		AllClearScreenDisp();
		mnSw2++;
		break;
	case 2:
		if((mlKeySts & 0x80) != 0)		/*�o�^�L�[*/
		{
			/*�S�w���f�[�^(�������A�t�@�C��)���폜����B*/
			fncSijiDataAllDel();
			mnCurNum = 1;
			mnTtlNum = 0;
			mnSw1 = 1;
			mnSw2 = 1;
		}
		else if((mlKeySts & 0x40) != 0)		/*�N���A�L�[*/
		{
			/*�L�����Z���Ȃ̂Ŗ������Ŕ�����B*/
			mnSw1 = 1;
			mnSw2 = 1;
		}
		break;
	}
}

/*�_�E�����[�h�^�A�b�v���[�h�@�n�܂�*/
/*IrDA�|�[�g������*/
void subSioInit(void)
{
//	auto char fmtt[4] = {0x07, 0x01, 0x00, 0x00};	/*�{�[���[�g:19,200,�f�[�^��:8�r�b�g,�p���e�B:�Ȃ�,�X�g�b�v�r�b�g:1�r�b�g*/
//	auto char fmtt[4] = {0x08, 0x01, 0x00, 0x00};	/*�{�[���[�g:38,400,�f�[�^��:8�r�b�g,�p���e�B:�Ȃ�,�X�g�b�v�r�b�g:1�r�b�g*/
	auto char fmtt[4] = {0x09, 0x01, 0x00, 0x00};	/*�{�[���[�g:115,200,�f�[�^��:8�r�b�g,�p���e�B:�Ȃ�,�X�g�b�v�r�b�g:1�r�b�g*/
	
	char sts, asTmp[100];

	sts = setphfmt(fmtt);
//	dspstring("init:");
//	sprintf(asTmp, "[%x]\r\n", sts);
//	dspstring(asTmp);
//	kbin();
}

/*IrDA�|�[�g�I�[�v��*/
void subSioOpen(void)
{
	char sts, asTmp[100];

	sts = ctrlphport(0xff);
//	dspstring("open:");
//	sprintf(asTmp, "[%x]\r\n", sts);
//	dspstring(asTmp);
//	kbin();
}

/*IrDA�|�[�g�N���[�Y*/
void subSioClose(void)
{
	char sts, asTmp[100];

	while(1)
	{
		if(ckphoutbfe() == 0x00)
		{
			/*�o�̓o�b�t�@�Ƀf�[�^�Ȃ�*/
			break;
		}
	}
	sts = ctrlphport(0x00);
//	dspstring("close:");
//	sprintf(asTmp, "[%x]\r\n", sts);
//	dspstring(asTmp);
//	kbin();
}

/*BCC����*/
void subBccMake(char *sData, int nLen, char *sBcc)
{
	int n1;
	long l2;
	char asTmp[10];

    l2 = 0;
    for(n1 = 0; n1 < nLen; n1++)
	{
        l2 = l2 + sData[n1];
	}
    sprintf(asTmp, "%02X", l2);	/*16�i���ɕϊ�*/
	nLen = strlen(asTmp);
	sBcc[0] = asTmp[nLen - 2];
	sBcc[1] = asTmp[nLen - 1];
	sBcc[2] = '\0';
}

void subResponseSend(int nResponse)
{
	unsigned char dt;
	char asTmp[100];
	char asTmp2[3];

	dt = 0x2;
	asTmp[0] = dt;
	putph(dt);
	dt = '2';
	asTmp[1] = dt;
	putph(dt);
	dt = 'R';
	asTmp[2] = dt;
	putph(dt);
	if(nResponse == 0)
	{
		/*ACK*/
		dt = 0x6;
	}
	else
	{
		/*NAK*/
		dt = 0x15;
	}
	asTmp[3] = dt;
	putph(dt);
	subBccMake(asTmp, 4, asTmp2);
	dt = asTmp2[0];
	putph(dt);
	dt = asTmp2[1];
	putph(dt);
	dt = 0x3;
	putph(dt);
}

/* Ir�c�`����̃f�[�^��M�֐� */
int fncDataRead(char *asTmp)
{
	int n1, s1;
	unsigned char dt;
	int sts;
	int nFlag;
	int nRet;

	n1 = 0;
	sts = 1;
	nFlag = 0;
	while(sts == 1)
	{
		s1 = getph();/* �P�o�C�g��M */
		dt = s1 & 0x00ff;
//		putph(dt);
		asTmp[n1] = dt & 0x00ff;
//		dspone(asTmp[n1]);/* ��M�����f�[�^��\�� */
		if(n1 == 0 && dt != 0x02)
		{
			nRet = -1;
			sts = 0;
			break;
		}
		if(dt == 0x02)
		{
			nFlag = 1;
		}
		if(nFlag == 1)
		{
			n1++;
		}
		if(dt == 0x03)
		{
			/*ETX��M�ŏI��*/
			nRet = 0;
			sts = 0;
		}
	}
	return nRet;
}

/*�_�E�����[�h*/
int subDownload(void)
{
	int n1, s1;
	unsigned char dt;
	int sts;
	FILE *fp;
	char asTmp[100];
	char asTmp2[100];
	char asTmp3[100];
	char asTmp4[3];
	int nRec;
	int nRet;
	int nSW;

//	dspstring("download start\r\n");

	if((fp = fopen("master  .dat", "w")) == NULL)	/* �t�@�C���I�[�v���i�K���t�@�C�����W�����A�g���q�R�����j */
	{
		dspstring("File Open Error!!\r\n");
		return -1;
	}
	fclose(fp);	/* �t�@�C���̃N���[�Y */

	if((fp = fopen("master  .dat", "a")) == NULL)	/* �t�@�C���I�[�v���i�K���t�@�C�����W�����A�g���q�R�����j */
	{
		dspstring("File Open Error!!\r\n");
		return -1;
	}

	sts = 1;
	nRec = 0;
	nSW = 0;
	while(sts == 1)
	{
		if(ckdpasts() == 0x00)
		{
			/*�߰���ٱ����������ި����ق��u����Ă��Ȃ��B*/
			/*���f*/
			nRet = -1;
			nSW = 30;
		}
		else if(getkeysts() != 0)
		{
			/*�L�[���͂���*/
			/*���f*/
			nRet = -1;
			nSW = 30;
		}
		else if(nRec >= 20000)
		{
			/*�������[�I�[�o�[*/
			/*���f*/
			nRet = -2;
			nSW = 30;
		}

		switch(nSW)
		{
		case 0:
			if(ckphibf() != 0)
			{
				s1 = getph();/* �P�o�C�g��M */
				dt = s1 & 0x00ff;
			}
			if(dt == 0x02)
			{
				/*STX��M*/
				asTmp3[0] = s1;
				n1 = 0;
				nSW++;
			}
			break;
		case 1:
			if(ckphibf() != 0)
			{
				s1 = getph();/* �P�o�C�g��M */
				dt = s1 & 0x00ff;
				asTmp3[1 + n1] = s1;
				asTmp[n1] = s1;
				n1++;
			}
			if(n1 == 7)
			{
				nSW++;
			}
			break;
		case 2:
			if(asTmp[1] != 'M')
			{
				/*���f*/
				nRet = -1;
				nSW = 30;
			}
			else if(asTmp[2] == '0' && asTmp[3] == '0' && asTmp[4] == '0' && asTmp[5] == '0' && asTmp[6] == '0')
			{
				/*�����f�[�^*/
				nSW = 20;
			}
			else
			{
				n1 = 0;
				nSW = 10;
			}
			break;
		case 10:
			if(ckphibf() != 0)
			{
				s1 = getph();/* �P�o�C�g��M */
				dt = s1 & 0x00ff;
				if(dt == 0x03)
				{
					/*ETX��M*/
					subBccMake(asTmp3, 40, asTmp4);
					if((asTmp3[40] == asTmp4[0] && asTmp3[41] == asTmp4[1]) || (asTmp3[40] == '*' && asTmp3[41] == '*'))
					{
						memsetEx(asTmp2, ' ', 32);
						strncpyEx(&asTmp2[0], &asTmp[0], 6);
						strncpyEx(&asTmp2[6], &asTmp[6], 20);
						strncpyEx(&asTmp2[26], &asTmp[26], 6);
						asTmp2[32] = 0x0d;
						asTmp2[33] = 0x0a;
						fwriteEx(asTmp2, 34, fp);
						nRec++;
						subResponseSend(0);			/*���X�|���X(ACK)���M*/
						nSW = 0;
					}
					else
					{
						subResponseSend(1);			/*���X�|���X(NAK)���M*/
						/*���f*/
						nRet = -1;
						nSW = 30;
					}
				}
				else
				{
					asTmp3[8 + n1] = s1;
					asTmp[n1] = s1;
//					dspone(asTmp[n1]);
					n1++;
				}
			}
			break;
		case 20:
			if(ckphibf() != 0)
			{
				s1 = getph();/* �P�o�C�g��M */
				dt = s1 & 0x00ff;
				if(dt == 0x03)
				{
					/*ETX��M*/
					subResponseSend(0);			/*���X�|���X(ACK)���M*/
					nRet = nRec;
					sts = 0;
				}
			}
			break;
		case 30:
			while(1)
			{
				if(ckphibf() == 0)
				{
					break;
				}
				getph();
			}
			sts = 0;
			break;
		}
	}
	fclose(fp);	/* �t�@�C���̃N���[�Y */
//	dspstring("download end\r\n");

	return nRet;
}

/*�A�b�v���[�h*/
int subUpload(void)
{
	FILE *fp;
	int n1;
	char s1;
	int nRet;
	int nRec;
	unsigned char dt;
	int nSW;
	char asTmp[100];
	char asTmp2[100];
	char asTmp3[100];
	char asTmp4[3];
	int sts;
	int nEof;

//	dspstring("upload start\r\n");

	if((fp = fopen("sijidata.dat", "r")) == NULL)	/* �t�@�C���I�[�v���i�K���t�@�C�����W�����A�g���q�R�����j */
	{
		dspstring("File Open Error!!\r\n");
		return -1;
	}

	nRec = 0;
	nSW = 0;
	sts = 1;
	nEof = 0;
	while(sts == 1)
	{
		if(ckdpasts() == 0x00)
		{
			/*�߰���ٱ����������ި����ق��u����Ă��Ȃ��B*/
			/*���f*/
			nRet = -1;
			nSW = 40;
		}
		else if(getkeysts() != 0)
		{
			/*�L�[���͂���*/
			/*���f*/
			nRet = -1;
			nSW = 40;
		}

		switch(nSW)
		{
		case 0:
			nRec++;
			for(n1 = 0; n1 <= 33; n1++)
			{
				s1 = fgetc(fp);
				if(s1 == EOF)
				{
//					dspstring("eof break\r\n");
					memsetEx(asTmp, ' ', 32);
					nEof = 1;
					break;
				}
				asTmp[n1] = s1 & 0x00ff;
			}
			nSW = 10;
			break;
		case 10:
			dt = 0x2;
			asTmp3[0] = dt;
			putph(dt);	/*STX���M*/
			dt = '2';
			asTmp3[1] = dt;
			putph(dt);	/*ID��񑗐M*/
			dt = 'S';
			asTmp3[2] = dt;
			putph(dt);	/*�敪��񑗐M*/
			if(nEof == 1)
			{
				memsetEx(asTmp2, '0', 5);
			}
			else
			{
				sprintf(asTmp2, "%05d", nRec);
			}
			for(n1 = 0; n1 < 5; n1++)
			{
				dt = asTmp2[n1] & 0x00ff;
				asTmp3[3 + n1] = dt;
				putph(dt);	/*�f�[�^�ԍ����M*/
			}
			for(n1 = 0; n1 < 32; n1++)
			{
				dt = asTmp[n1] & 0x00ff;
				asTmp3[8 + n1] = dt;
				putph(dt);	/*�w���f�[�^���M*/
			}
			subBccMake(asTmp3, 40, asTmp4);
			dt = asTmp4[0];
			putph(dt);	/*BCC���M*/
			dt = asTmp4[1];
			putph(dt);	/*BCC���M*/
			dt = 0x03;
			putph(dt);	/*ETX���M*/
			nSW = 20;
			break;
		case 20:
			if(ckphibf() != 0)
			{
				s1 = getph();/* �P�o�C�g��M */
				dt = s1 & 0x00ff;
				if(dt == 0x02)
				{
					/*STX��M*/
					s1 = getph();/*ID����M*/
					s1 = getph();/*�敪����M*/
					s1 = getph();/*�f�[�^����M*/
					dt = s1 & 0x00ff;
					if(dt == 0x06)
					{
						/*ACK*/
						nSW = 30;
					}
					else
					{
						/*NAK*/
						/*���f*/
						nSW = 40;
						nRet = -1;
						sts = 0;
					}
				}
			}
			break;
		case 30:
			if(ckphibf() != 0)
			{
				s1 = getph();/* �P�o�C�g��M */
				dt = s1 & 0x00ff;
				if(dt == 0x03)
				{
					/*ETX��M*/
					if(nEof == 1)
					{
						nRet = nRec - 1;
						sts = 0;
					}
					else
					{
						nSW = 0;
					}
				}
			}
			break;
		case 40:
			if(ckphibf() != 0)
			{
				s1 = getph();/* �P�o�C�g��M */
				dt = s1 & 0x00ff;
				if(dt == 0x03)
				{
					/*ETX��M*/
					sts = 0;
				}
			}
			break;
		}
	}

	fclose(fp);	/* �t�@�C���̃N���[�Y */

//	dspstring("upload end\r\n");

	return nRet;
}

/*1:�_�E�����[�h,2:�A�b�v���[�h*/
int fncCommandGet(void)
{
	char asTmp[100];
	int nRet;

	nRet = fncDataRead(asTmp);

	if(asTmp[2] == 'A')
	{
		nRet = 2;
	}
	else if(asTmp[2] == 'D')
	{
		nRet = 1;
	}
//	dspstring("command get\r\n");
	
	return nRet;
}
/*�_�E�����[�h�^�A�b�v���[�h�@�I���*/

void subInit(void)
{
	mnSw1 = 1;				/*��ԕϐ��P��������*/
	mnSw2 = 1;				/*��ԕϐ��Q��������*/
	mnAtvMode = 1;				/*�㉺�I����Ԃ�������*/
	mnCurNum = 1;				/*���݂̎w������������*/
	mnTtlNum = 0;				/*���v�̎w������������*/
	mnCurPos = 0;				/*���݂̍��ڂ�������*/
	memsetEx(masKoukanNo, ' ', 6);		/*�H�Ǖϐ���������*/
	memsetEx(masHinban, ' ', 20);		/*�i�ԕϐ���������*/
	memsetEx(masLotNo, ' ', 6);		/*LOT�ϐ���������*/
	memsetEx(masNewKoukanNo, ' ', 6);	/*�H�Ǖϐ���������*/
	memsetEx(masNewHinban, ' ', 20);	/*�i�ԕϐ���������*/
	memsetEx(masNewLotNo, ' ', 6);		/*LOT�ϐ���������*/
	memsetEx(masTmpKoukanNo, ' ', 6);	/*�H�Ǖϐ���������*/
	memsetEx(masTmpHinban, ' ', 20);	/*�i�ԕϐ���������*/
	memsetEx(masTmpLotNo, ' ', 6);		/*LOT�ϐ���������*/

	ClrDisplay(3, 2);			/*�S��ʂ̏�����*/
	SetLcdMode(1);				/*��ʃ��[�h���g�s�Q�O���[�h*/
	SetSepBar(1);				/*���E���̕\��*/
	setbcrfunc(bct);			/*�o�[�R�[�h�̓ǂݎ��ݒ�*/
	setbcrsts(0x16);			/*�o�[�R�[�h�̓ǂݎ�莞�̃A�N�V�����ݒ�*/
}

void subCommProc(void)
{
	int nSW;
	int nRet;
	char asTmp[100];
	int sts;

	sts = 1;
	nSW = 0;
	while(sts == 1)
	{
		switch(nSW)
		{
		case 0:
			nSW++;
			break;
		case 1:
			nSW++;
			break;
		case 2:
			if(ckphibf() != 0)
			{
				/*IrDA���̓o�b�t�@�Ƀf�[�^����*/
//				dspstring("IrDA data ok\r\n");
				nSW = 5;
			}
			else
			{
				nSW = 99;
			}
			break;
		case 5:	/*�R�}���h�҂�*/
			nRet = fncCommandGet();
			switch(nRet)
			{
			case 1:	/*�_�E�����[�h*/
				subResponseSend(0);			/*���X�|���X(ACK)���M*/
				nSW = 10;
				break;
			case 2:	/*�A�b�v���[�h*/
				subResponseSend(0);			/*���X�|���X(ACK)���M*/
				nSW = 20;
				break;
			default:
				nSW = 99;
				break;
			}
			break;
		case 10:/*�_�E�����[�h*/
			SelectAnothDisp(mnScr2, 1);		/*�T�u���*/
			dspone(0x0c);
			dspstring("Ͻ���ް����޳�۰�ނ�\r\n");
			dspstring("�Ă��܂��B\r\n");
			dspstring("�b�����҂��������B\r\n");
			nRet = subDownload();
			if(nRet >= 0)
			{
				ctrlbuzz(0xff, 50, 0);		/*�m�F�p�u�U�[������ ��,50*20ms,�ʏ�*/
				dspone(0x0c);
				dspstring("Ͻ���ް����޳�۰�ނ�\r\n");
				dspstring("�I��܂����B\r\n");
				sprintf(asTmp, "����:[%d]��\n\r", nRet);
				dspstring(asTmp);
				flshkb(0, asTmp);				/*�L�[�{�[�h���̓o�b�t�@�N���A*/
				waittm(70);					/* 70*20ms�ꎞ��~ 2003/09/22 A.Tamura */
			}
			else if(nRet == -2)
			{
				erbz1();					/*�G���[�u�U�[������ 200ms*3��*/
				dspone(0x0c);
				dspstring("��ذ���ް���܂����B\r\n");
				dspstring("�޳�۰�ނ𒆒f���܂��B\r\n");
				flshkb(0, asTmp);				/*�L�[�{�[�h���̓o�b�t�@�N���A*/
				kbin();
			}
			else
			{
				erbz1();					/*�G���[�u�U�[������ 200ms*3��*/
				dspone(0x0c);
				dspstring("�޳�۰�ނ𒆒f���܂��B\r\n");
				flshkb(0, asTmp);				/*�L�[�{�[�h���̓o�b�t�@�N���A*/
				kbin();
			}
			SelectAnothDisp(mnScr2, 0);		/*���C�����*/
			nSW = 99;
			break;
		case 20:/*�A�b�v���[�h*/
			SelectAnothDisp(mnScr2, 1);		/*�T�u���*/
			dspone(0x0c);
			dspstring("�w���ް�����۰�ނ�\r\n");
			dspstring("�Ă��܂��B\r\n");
			dspstring("�b�����҂��������B\r\n");
			nRet = subUpload();
			if(nRet >= 0)
			{
				ctrlbuzz(0xff, 50, 0);		/*�m�F�p�u�U�[������ ��,50*20ms,�ʏ�*/
				dspone(0x0c);
				dspstring("�w���ް��̱���۰�ނ�\r\n");
				dspstring("�I��܂����B\r\n");
				sprintf(asTmp, "����:[%d]��\n\r", nRet);
				dspstring(asTmp);
				flshkb(0, asTmp);				/*�L�[�{�[�h���̓o�b�t�@�N���A*/
				waittm(70);					/* 70*20ms�ꎞ��~ 2003/09/22 A.Tamura */
			}
			else
			{
				erbz1();					/*�G���[�u�U�[������ 200ms*3��*/
				dspone(0x0c);
				dspstring("����۰�ނ𒆒f���܂��B\r\n");
				flshkb(0, asTmp);				/*�L�[�{�[�h���̓o�b�t�@�N���A*/
				kbin();
			}
			SelectAnothDisp(mnScr2, 0);		/*���C�����*/
			nSW = 99;
			break;
		case 99:/*�I������*/
			sts = 0;
			break;
		}
	}
}

int main(void)
{
	subSioInit();
	subSioOpen();
	subInit();
	subSijiDataTest();

	mnTtlNum = fncSijiDataNumGet() - 1;
	if(mnTtlNum < 0)
	{
		mnTtlNum = 0;
	}

	while(1)
	{
		mlKeySts = getkeysts();
		if(mnAtvMode == 1 && (((mlKeySts & 0x8) != 0 && (mlKeyStsOld & 0x8)) || ((mlKeySts & 0x4) != 0 && (mlKeyStsOld & 0x4)) || ((mlKeySts & 0x10) != 0 && (mlKeyStsOld & 0x10)) || ((mlKeySts & 0x20) != 0 && (mlKeyStsOld & 0x20))))
		{
			/*��i�I��*/
			/*�O�񂪁��L�[���́��L�[���́��L�[���́��L�[�̏ꍇ*/
			mlKeyStsOld = mlKeySts;
			mnKeyRepeat = 1;
		}
		else if(mlKeySts != mlKeyStsOld || (mlKeySts & 0x1) != 0 || (mlKeySts & 0x2) != 0)/*�O��ƈႤ�����E�g���K�̏ꍇ*/
		{
			mlKeyStsOld = mlKeySts;
			mnKeyRepeat = 0;
		}
		else
		{
			mlKeySts = 0;
		}


		switch(mnSw1)
		{
		case 1:
			StartScreenProc();
			break;
		case 2:
			OneClearScreenProc();
			break;
		case 3:
			AllClearScreenProc();
			break;
		}
		subCommProc();
	}
	subSioClose();

	return 0;
}
