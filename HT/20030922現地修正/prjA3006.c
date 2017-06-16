/************************************************************************/
/*	出荷検査システム													*/
/*	プログラム名	:prjA3006.c											*/
/*	パラメータ	:なし													*/
/*	復帰情報	:なし													*/
/*	処理内容	:ハンディターミナル処理									*/
/*	作成日付	:2003/04/16												*/
/*	作成者		:橋本電子工業株式会社 菅 雅幸							*/
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

/*ＢＣＴテーブル*/
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

int mnSw1;								/*状態変数１*/
int mnSw2;								/*状態変数２*/
int mnAtvMode;							/*上下選択状態変数*/
int mnScr1, mnScr2;						/*上下画面番号変数*/
unsigned long mlKeySts;					/*キー入力変数*/
unsigned long mlKeyStsOld;				/*前回のキー入力変数*/
int mnCurNum;							/*現在の指示数*/
int mnTtlNum;							/*合計の指示数*/
int mnCurPos;							/*現在の項目 0:工管,1:品番,2:LOT,3:確認*/
int mnInputMode;						/*現在の入力モード 0:数字,1:英字*/
int mnInputFlag;						/*0:英字未入力,1:英字入力中*/
char msValue;
int mnKeyRepeat;

char masKoukanNo[7];					/*工管NO*/
char masHinban[21];						/*得意先品番*/
char masLotNo[7];						/*ロットNO*/
char masNewKoukanNo[7];					/*工管NO*/
char masNewHinban[21];					/*得意先品番*/
char masNewLotNo[7];					/*ロットNO*/
char masTmpKoukanNo[7];					/*工管NO*/
char masTmpHinban[21];					/*得意先品番*/
char masTmpLotNo[7];					/*ロットNO*/

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

/*文字列比較 0:一致,1:不一致*/
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

/*未入力項目チェック 0:未入力,1:入力あり*/
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

/*工管NO比較 -1:小なり,0:同じ,1:大なり,*/
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

/*マスターデータのバイナリーサーチ 0:検索ヒット,1:検索エラー,-1:制御エラー*/
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

	if((fp = fopen("master  .dat", "r")) == NULL)	/* ファイルオープン（必ずファイル名８文字、拡張子３文字） */
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

	fclose(fp);	/* ファイルのクローズ */

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

	if((fp = fopen("sijidata.dat", "r")) == NULL)	/* ファイルオープン（必ずファイル名８文字、拡張子３文字） */
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

	fclose(fp);	/* ファイルのクローズ */

	return nRet;
}

int fncSijiDataRead(void)
{
	FILE *fp;
	char asReadBuf[100];
	int n1;
	char sChar;

	if((fp = fopen("sijidata.dat", "r")) == NULL)	/* ファイルオープン（必ずファイル名８文字、拡張子３文字） */
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

	fclose(fp);	/* ファイルのクローズ */

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

	if((fp = fopen("sijidata.dat", "r")) == NULL)	/* ファイルオープン（必ずファイル名８文字、拡張子３文字） */
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

	fclose(fp);	/* ファイルのクローズ */

	fncSijiDataAllDel();

	if((fp = fopen("sijidata.dat", "a")) == NULL)	/* ファイルオープン（必ずファイル名８文字、拡張子３文字） */
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

	fclose(fp);	/* ファイルのクローズ */

	return 0;
}

int fncSijiDataInsert(char *asKoukanNo, char *asHinban, char *asLotNo)
{
	FILE *fp;
	char asTmp[100];

	if((fp = fopen("sijidata.dat", "a")) == NULL)	/* ファイルオープン（必ずファイル名８文字、拡張子３文字） */
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

	fclose(fp);	/* ファイルのクローズ */

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

	if((fp = fopen("sijidata.dat", "r")) == NULL)	/* ファイルオープン（必ずファイル名８文字、拡張子３文字） */
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

	fclose(fp);	/* ファイルのクローズ */

	fncSijiDataAllDel();

	if((fp = fopen("sijidata.dat", "a")) == NULL)	/* ファイルオープン（必ずファイル名８文字、拡張子３文字） */
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

	fclose(fp);	/* ファイルのクローズ */

	return 0;
}

int fncSijiDataAllDel(void)
{
	FILE *fp;
	char asTmp[100];

	if((fp = fopen("sijidata.dat", "w")) == NULL)	/* ファイルオープン（必ずファイル名８文字、拡張子３文字） */
	{
//		dspstring("File Open Error!!\r\n");
		return -1;
	}

	memsetEx(asTmp, '\0', sizeof(asTmp));
	fwriteEx(asTmp, 0, fp);

	fclose(fp);	/* ファイルのクローズ */

	return 0;
}

void subSijiDataTest()
{
	FILE *fp;
	char asTmp[100];

	if((fp = fopen("sijidata.dat", "r")) == NULL)	/* ファイルオープン（必ずファイル名８文字、拡張子３文字） */
	{
		fp = fopen("sijidata.dat", "w");
		memsetEx(asTmp, '\0', sizeof(asTmp));
		fwriteEx(asTmp, 0, fp);
	}

	fclose(fp);	/* ファイルのクローズ */
}

void subNowDateGet(char *sDate)
{
	char date_tbl[3];
	int year , month , day;

	getdate(date_tbl);/* 日付の取得 */
	year = (((int)date_tbl[1]) * 256) + (int)date_tbl[0];
	month = (int)date_tbl[2];
	day = (int)date_tbl[3];
	sprintf(sDate, "%4d%02d%02d " , year , month , day );
}

void subNowTimeGet(char *sTime)
{
	char time_tbl[3];
	int hour , minute , second;

	gettime(time_tbl);/* 時間の取得 */
	hour = (int)time_tbl[0];
	minute = (int)time_tbl[1];
	second = (int)time_tbl[2];
	sprintf(sTime, "%02d:%02d:%02d " , hour , minute , second );
}

int fncNowSecontGet(void)
{
	char time_tbl[3];
	int second;

	gettime(time_tbl);/* 時間の取得 */
	second = (int)time_tbl[2];
	return second;
}

/*開始画面*/
void StartScreenDisp(void)
{
	char saTmp[10];
	int nY1, nY2;
	int nScr;

	subNowDateGet(saTmp);
	saTmp[8] = '\0';

	if(mnAtvMode == 1)
	{
		/*上段選択*/
		nY1 = 1;
		nY2 = 27;
		mnScr1 = 1;
		mnScr2 = 2;
		nScr = 0;
	}
	else
	{
		/*下段選択*/
		nY1 = 24;
		nY2 = 62;
		mnScr1 = 0;
		mnScr2 = 1;
		nScr = 2;
	}
	SetDisplayType(nY1 , nY2);			/*画面の３分割*/
	SetScrollBar(0 , 0);				/*画面0のスクロールバー表示*/
	SetScrollBar(1 , 0);				/*画面1のスクロールバー表示*/
	SetScrollBar(2 , 0);				/*画面2のスクロールバー表示*/

	SelectActCur(nScr);				/*画面にカーソルを表示*/
	dspone(0x0c);					/*画面を消去、カーソルをホームポジションへ移動させる。*/

	SelectActCur(mnScr1);				/*画面にカーソルを表示*/
	dspone(0x0c);					/*画面を消去、カーソルをホームポジションへ移動させる。*/
	SetAbsCharAd(0,0,0);
	dspstring("指示");
	sprintf(saTmp, "[%02d/%02d]  " , mnCurNum, mnTtlNum);
	saTmp[9] = '\0';
	dspstring(saTmp);
	subNowDateGet(saTmp);
	saTmp[8] = '\0';
	dspstring(saTmp);
	SetAbsCharAd(0,1,0);
	dspstring("1.ｸﾘｱ 3.全ｸﾘｱ F2.切替");

	SelectActCur(mnScr2);				/*画面にカーソルを表示*/
	dspone(0x0c);					/*画面を消去、カーソルをホームポジションへ移動させる。*/

	fncSijiDataRead();

	SetAbsCharAd(0,0,0);
	dspstring("工管>");
	strncpyEx(saTmp, masKoukanNo, 6);
	saTmp[6] = '\0';
	dspstring(saTmp);
	dspstring("    [登録]");

	SetAbsCharAd(0,1,0);
	dspstring("品番>");
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

/*開始画面(指示数のみ) 0:ファイルから読込む,1:挿入･更新*/
void StartScreenDispEx(int nCode)
{
	char saTmp[10];

	SelectActCur(mnScr1);				/*画面にカーソルを表示*/
	SetAbsCharAd(0,0,0);
	dspstring("指示");
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

	SelectActCur(mnScr2);				/*画面にカーソルを表示*/
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

/*個別ｸﾘｱ画面*/
void OneClearScreenDisp(void)
{
	SelectActCur(mnScr1);				/*画面にカーソルを表示*/
	dspone(0x0c);					/*画面を消去、カーソルをホームポジションへ移動させる。*/
	SetAbsCharAd(0,0,0);
	dspstring("このﾃﾞｰﾀを消去します ");
	SetAbsCharAd(0,1,0);
	dspstring("Yes...登録 No...ｸﾘｱ  ");
}

/*全ｸﾘｱ画面*/
void AllClearScreenDisp(void)
{
	char saTmp[10];

	subNowDateGet(saTmp);
	saTmp[8] = '\0';

	SelectActCur(mnScr2);				/* 画面にカーソルを表示 */
	dspone(0x0c);					/*画面を消去、カーソルをホームポジションへ移動させる。*/
	SetAbsCharAd(0,0,0);
	dspstring("  全ての指示ﾃﾞｰﾀを   ");
	SetAbsCharAd(0,1,0);
	dspstring("  消去します         ");
	SetAbsCharAd(0,2,0);
	dspstring("Yes...登録 No...ｸﾘｱ  ");
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

/*-1:スペースなし,0:全てスペース,1 <= n:途中にスペースあり*/
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

/*現在の項目を反転する*/
void subCurPosDisp(void)
{
	int nLoc;

	switch(mnCurPos)
	{
	case 0:		/*工管*/
		subKoukanDisp(1);
		subHinbanDisp(0);
		subLotDisp(0);
		subKakuninDisp(0);
		break;
	case 1:		/*品番*/
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
	case 3:		/*確認*/
		subKoukanDisp(0);
		subHinbanDisp(0);
		subLotDisp(0);
		subKakuninDisp(1);
		break;
	}
}

/*カーソル位置を反転する*/
void subCurPosDispEx(void)
{
	int nLoc;

	switch(mnCurPos)
	{
	case 0:		/*工管*/
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
		SetAbsCharAd(5 + nLoc, 0, 1);	/*現在のカーソル位置を反転させる*/
		break;
	case 1:		/*品番*/
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
			SetAbsCharAd(nLoc, 2, 1);	/*現在のカーソル位置を反転させる*/
		}
		else
		{
			SetAbsCharAd(5 + nLoc, 1, 1);	/*現在のカーソル位置を反転させる*/
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
		SetAbsCharAd(5 + nLoc, 2, 1);	/*現在のカーソル位置を反転させる*/
		break;
	case 3:		/*確認*/
		nLoc = strlenEx(masKoukanNo, 6);
		SetAbsCharAd(0, 0, 0);		/*カーソル非表示させる*/
		break;
	}
}

void subCurPosDel(void)
{
	int nLoc;

	switch(mnCurPos)
	{
	case 0:		/*工管*/
		nLoc = strlenEx(masTmpKoukanNo, 6);
		if(nLoc == - 1)
		{
			nLoc = 6 - 1;
		}
		masTmpKoukanNo[nLoc] = ' ';
		break;
	case 1:		/*品番*/
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

/*数字キー入力処理*/
void subCurPosIn(void)
{
	int nLoc;

	switch(mlKeySts)
	{
	case 0x4000:	/*1キー*/
		msValue = '1';
		break;
	case 0x8000:	/*2キー*/
		msValue = '2';
		break;
	case 0x10000:	/*3キー*/
		msValue = '3';
		break;
	case 0x800:		/*4キー*/
		msValue = '4';
		break;
	case 0x1000:	/*5キー*/
		msValue = '5';
		break;
	case 0x2000:	/*6キー*/
		msValue = '6';
		break;
	case 0x100:		/*7キー*/
		msValue = '7';
		break;
	case 0x200:		/*8キー*/
		msValue = '8';
		break;
	case 0x400:		/*9キー*/
		msValue = '9';
		break;
	case 0x20000:	/*0キー*/
		msValue = '0';
		break;
	case 0x40000:	/*.キー*/
		msValue = '.';
		break;
	case 0x80000:	/*SFキー*/
		msValue = '-';
		break;
	}

	switch(mnCurPos)
	{
	case 0:		/*工管*/
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
	case 1:		/*品番*/
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

/*英字キー入力処理*/
void subCurPosInEx(void)
{
	int nLoc;
	int nFlag;

	nFlag = 1;
	switch(mlKeySts)
	{
	case 0x4000:	/*STUキー*/
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
	case 0x8000:	/*VWXキー*/
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
	case 0x10000:	/*YZ#キー*/
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
	case 0x800:		/*JKLキー*/
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
	case 0x1000:	/*MNOキー*/
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
	case 0x2000:	/*PQRキー*/
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
	case 0x100:		/*ABCキー*/
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
	case 0x200:		/*DEFー*/
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
	case 0x400:		/*GHIキー*/
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
	case 0x20000:	/*\%/キー*/
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
	case 0x40000:	/**+-キー*/
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
	case 0x80000:	/*SP@=ー*/
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
	case 0:		/*工管*/
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
	case 1:		/*品番*/
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

/*開始画面での処理*/
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
		if((mlKeySts & 0x200000) != 0)	/*F2キー*/
		{
			if(mnAtvMode == 1)
			{
				mnAtvMode = 2;		/*下段選択*/
				mnCurPos = 0;		/*現在の項目を初期化*/
				mnInputMode = 0;	/*数字入力モード*/
				strncpyEx(masNewKoukanNo, masKoukanNo, 6);
				strncpyEx(masNewHinban, masHinban, 20);
				strncpyEx(masNewLotNo, masLotNo, 6);
				strncpyEx(masTmpKoukanNo, masKoukanNo, 6);
				strncpyEx(masTmpHinban, masHinban, 20);
				strncpyEx(masTmpLotNo, masLotNo, 6);
//				memsetEx(masTmpKoukanNo, ' ', 6);		/*工管変数を初期化*/
//				memsetEx(masTmpHinban, ' ', 20);		/*品番変数を初期化*/
//				memsetEx(masTmpLotNo, ' ', 6);			/*LOT変数を初期化*/
			}
			else
			{
				mnAtvMode = 1;		/*上段選択*/
				memsetEx(masNewKoukanNo, ' ', 6);
				memsetEx(masNewHinban, ' ', 20);
				memsetEx(masNewLotNo, ' ', 6);
				memsetEx(masTmpKoukanNo, ' ', 6);		/*工管変数を初期化*/
				memsetEx(masTmpHinban, ' ', 20);		/*品番変数を初期化*/
				memsetEx(masTmpLotNo, ' ', 6);			/*LOT変数を初期化*/
			}
			StartScreenDisp();
			if(mnAtvMode == 1)
			{
				/*上段選択*/
//				subKoukanDisp(0);
//				subHinbanDisp(0);
//				subLotDisp(0);
//				subKakuninDisp(0);
			}
			else
			{
				/*下段選択*/
				subCurPosDisp();
				subCurPosDispEx();
			}
		}
		if(mnAtvMode == 1)
		{
			/*上段選択*/
			if((mlKeySts & 0x4000) != 0)		/*1キー*/
			{
				if(mnCurNum <= mnTtlNum)		/*クリア制限*/
				{
					mnSw1 = 2;
					mnSw2 = 1;
				}
			}
			else if((mlKeySts & 0x10000) != 0)	/*3キー*/
			{
				if(mnTtlNum != 0)				/*クリア制限*/
				{
					mnSw1 = 3;
					mnSw2 = 1;
				}
			}
			else if((mlKeySts & 0x8) != 0 || (mlKeySts & 0x4) != 0)	/*↑キー又は←キー*/
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
			else if((mlKeySts & 0x10) != 0 || (mlKeySts & 0x20) != 0)	/*↓キー又は→キー*/
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
			else if((mlKeySts & 0x1) != 0 || (mlKeySts & 0x2) != 0)		/*左右トリガ*/
			{
				if(mnTtlNum == 99)
				{
					/*指示データ件数が最大に達しました*/
					erbz1();								/*エラーブザー鳴動制御 200ms*3回*/
					break;
				}
				while(1)
				{
					bsts = readbc(rbca);		/* バーコードの読み取り */
					if((bsts >> 8) == 0x0)
					{
						/*キー入力された場合*/
						kbin();
						break;
					}
					else
					{
						/*バーコードがスキャンされた場合*/
						nLen = rbca[1];								/* バーコードデータのサイズの取得 */
						memsetEx(asBarCodeBuf, ' ', 32);
						strncpyEx(&asBarCodeBuf[0], &rbca[2], nLen);
						if(nLen <= 0 || nLen > 6)
						{
							erbz1();								/*エラーブザー鳴動制御 200ms*3回*/
							mnCurPos = 0;							/*現在の項目を確認にする*/
						}
						else
						{
							nRet = fncBinarySearch(asBarCodeBuf, asTmp);
							if(nRet == 0)
							{
								/*マスターデータに該当データがある*/
								strncpyEx(masNewKoukanNo, &asTmp[0], 6);
								strncpyEx(masNewHinban, &asTmp[6], 20);
								strncpyEx(masNewLotNo, &asTmp[26], 6);
								strncpyEx(masTmpKoukanNo, &asTmp[0], 6);
								strncpyEx(masTmpHinban, &asTmp[6], 20);
								strncpyEx(masTmpLotNo, &asTmp[26], 6);
								mnCurPos = 3;						/*現在の項目を確認にする*/
							}
							else
							{
								/*マスターデータに該当データが無い*/
								erbz1();					/*エラーブザー鳴動制御 200ms*3回*/
								strncpyEx(masNewKoukanNo, &asBarCodeBuf[0], 6);
								memsetEx(masNewHinban, ' ', 20);	/*品番変数を初期化*/
								memsetEx(masNewLotNo, ' ', 6);		/*LOT変数を初期化*/
								strncpyEx(masTmpKoukanNo, &asBarCodeBuf[0], 6);		/*工管変数を初期化*/
								memsetEx(masTmpHinban, ' ', 20);	/*品番変数を初期化*/
								memsetEx(masTmpLotNo, ' ', 6);		/*LOT変数を初期化*/
								mnCurPos = 1;						/*現在の項目を確認にする*/
							}
						}
						mnAtvMode = 2;								/*下段選択*/
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
			/*下段選択*/
			if((mlKeySts & 0x8) != 0 || (mlKeySts & 0x4) != 0)		/*↑キー又は←キー*/
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
			else if((mlKeySts & 0x10) != 0 || (mlKeySts & 0x20) != 0)	/*↓キー又は→キー*/
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
			else if((mlKeySts & 0x40) != 0)	/*クリアキー*/
			{
				subCurPosDel();
				StartScreenDispEx(2);
				subCurPosDispEx();
			}
			else if((mlKeySts & 0x4000) != 0 || (mlKeySts & 0x8000) != 0 || (mlKeySts & 0x10000) != 0 || (mlKeySts & 0x800) != 0 || (mlKeySts & 0x1000) != 0 ||
			(mlKeySts & 0x2000) != 0 || (mlKeySts & 0x100) != 0 || (mlKeySts & 0x200) != 0 || (mlKeySts & 0x400) != 0 || (mlKeySts & 0x20000) != 0 ||
			(mlKeySts & 0x40000) != 0 || (mlKeySts & 0x80000) != 0)	/*数字キー*/
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
			else if((mlKeySts & 0x100000) != 0)	/*F1キー*/
			{
				msValue = ' ';
				mnInputFlag = 0;
				if(mnInputMode == 0)
				{
					mnInputMode = 1;			/*英字入力モード*/
				}
				else
				{
					mnInputMode = 0;			/*数字入力モード*/
				}
			}
			else if((mlKeySts & 0x1) != 0 || (mlKeySts & 0x2) != 0)		/*左右トリガ*/
			{
				msValue = ' ';
				mnInputFlag = 0;
				while(1)
				{
					bsts = readbc(rbca);							/* バーコードの読み取り */
					if((bsts >> 8) == 0x0)
					{
						/*キー入力された場合*/
						kbin();
						break;
					}
					else
					{
						/*バーコードがスキャンされた場合*/
						nLen = rbca[1];								/* バーコードデータのサイズの取得 */
						memsetEx(asBarCodeBuf, ' ', 32);
						strncpyEx(&asBarCodeBuf[0], &rbca[2], nLen);
						if(nLen <= 0 || nLen > 6)
						{
							erbz1();								/*エラーブザー鳴動制御 200ms*3回*/
						}
						else
						{
							nRet = fncBinarySearch(asBarCodeBuf, asTmp);
							if(nRet == 0)
							{
								/*マスターデータに該当データがある*/
								strncpyEx(masNewKoukanNo, &asTmp[0], 6);
								strncpyEx(masNewHinban, &asTmp[6], 20);
								strncpyEx(masNewLotNo, &asTmp[26], 6);
								strncpyEx(masTmpKoukanNo, &asTmp[0], 6);
								strncpyEx(masTmpHinban, &asTmp[6], 20);
								strncpyEx(masTmpLotNo, &asTmp[26], 6);
								mnCurPos = 3;						/*現在の項目を確認にする*/
							}
							else
							{
								/*マスターデータに該当データが無い*/
								erbz1();							/*エラーブザー鳴動制御 200ms*3回*/
								strncpyEx(masNewKoukanNo, &asBarCodeBuf[0], 6);
								memsetEx(masNewHinban, ' ', 20);	/*品番変数を初期化*/
								memsetEx(masNewLotNo, ' ', 6);		/*LOT変数を初期化*/
								strncpyEx(masTmpKoukanNo, &asBarCodeBuf[0], 6);		/*工管変数を初期化*/
								memsetEx(masTmpHinban, ' ', 20);	/*品番変数を初期化*/
								memsetEx(masTmpLotNo, ' ', 6);		/*LOT変数を初期化*/
								mnCurPos = 1;						/*現在の項目を確認にする*/
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
			else if((mlKeySts & 0x80) != 0)							/*登録キー*/
			{
				mnInputFlag = 0;
				if(mnCurPos == 0)									/*工管*/
				{
					/*バーコードがスキャンされた場合*/
					nLen = strlenEx(masTmpKoukanNo, 6);
					nLen++;
					memsetEx(asBarCodeBuf, ' ', 32);
					strncpyEx(&asBarCodeBuf[0], masTmpKoukanNo, nLen);
					if(nLen <= 0 || nLen > 6)
					{
						erbz1();									/*エラーブザー鳴動制御 200ms*3回*/
						mnCurPos = 1;								/*現在の項目を品番にする*/
					}
					else
					{
						nRet = fncBinarySearch(asBarCodeBuf, asTmp);
						if(nRet == 0)
						{
							/*マスターデータに該当データがある*/
							strncpyEx(masNewKoukanNo, &asTmp[0], 6);
							strncpyEx(masNewHinban, &asTmp[6], 20);
							strncpyEx(masNewLotNo, &asTmp[26], 6);
							mnCurPos = 3;							/*現在の項目を確認にする*/
						}
						else
						{
							/*マスターデータに該当データが無い*/
							erbz1();								/*エラーブザー鳴動制御 200ms*3回*/
							strncpyEx(masNewKoukanNo, &asBarCodeBuf[0], 6);
							memsetEx(masNewHinban, ' ', 20);		/*品番変数を初期化*/
							memsetEx(masNewLotNo, ' ', 6);			/*LOT変数を初期化*/
							strncpyEx(masTmpKoukanNo, &asBarCodeBuf[0], 6);		/*工管変数を初期化*/
							memsetEx(masTmpHinban, ' ', 20);		/*品番変数を初期化*/
							memsetEx(masTmpLotNo, ' ', 6);			/*LOT変数を初期化*/
							mnCurPos = 1;							/*現在の項目を品番にする*/
						}
					}
					StartScreenDisp();
					StartScreenDispEx(1);
					subCurPosDisp();
					subCurPosDispEx();
				}
				else if(mnCurPos == 1)
				{
					strncpyEx(masNewHinban, masTmpHinban, 20);		/*品番*/
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
				else if(mnCurPos == 3)	/*登録*/
				{
					if(mnCurNum == mnTtlNum + 1)			/*指示データ(新規)*/
					{
						if(subSpaceCheckEx(masNewHinban, 20) == 0 || subSpaceCheckEx(masNewLotNo, 6) == 0)
						{
							/*品番又はLOTが未入力項目あり*/
//							ctrlbuzz(0xff, 50, 0);		/*確認用ブザー鳴動制御 鳴動,50*20ms,通常*/
//							ctrlbuzz2(0xff, 50, 50, 50);	/*確認用ブザー鳴動制御 鳴動,50*20ms,50%,50*/
							erbz1();			/*エラーブザー鳴動制御 200ms*3回*/
						}
						else
						{
							/*指示データ挿入*/
							fncSijiDataInsert(masNewKoukanNo, masNewHinban, masNewLotNo);
							mnTtlNum = fncSijiDataNumGet() - 1;
//							mnAtvMode = 1;					/*上段選択*/
							mnCurPos = 0;					/*現在の項目を工管にする*/
							StartScreenDisp();
							mnCurNum = mnTtlNum + 1;
							if(mnCurNum > 99)
							{
								mnCurNum = 99;
							}
							memsetEx(masNewKoukanNo, ' ', 6);
							memsetEx(masNewHinban, ' ', 20);
							memsetEx(masNewLotNo, ' ', 6);
							memsetEx(masTmpKoukanNo, ' ', 6);		/*工管変数を初期化*/
							memsetEx(masTmpHinban, ' ', 20);		/*品番変数を初期化*/
							memsetEx(masTmpLotNo, ' ', 6);			/*LOT変数を初期化*/
							StartScreenDispEx(0);
							subCurPosDisp();
							subCurPosDispEx();
						}
					}
					else						/*指示データ(更新)*/
					{
						if(subSpaceCheckEx(masHinban, 20) == 0 || subSpaceCheckEx(masLotNo, 6) == 0)
						{
							/*品番又はLOTが未入力項目あり*/
							erbz1();			/*エラーブザー鳴動制御 200ms*3回*/
						}
						else
						{
							/*指示データ更新*/
							strncpyEx(masNewKoukanNo, masKoukanNo, 6);
							strncpyEx(masNewHinban, masHinban, 20);
							strncpyEx(masNewLotNo, masLotNo, 6);
							fncSijiDataUpdate(masNewKoukanNo, masNewHinban, masNewLotNo);
							mnCurPos = 0;					/*現在の項目を工管にする*/
							StartScreenDisp();
							memsetEx(masNewKoukanNo, ' ', 6);
							memsetEx(masNewHinban, ' ', 20);
							memsetEx(masNewLotNo, ' ', 6);
							memsetEx(masTmpKoukanNo, ' ', 6);		/*工管変数を初期化*/
							memsetEx(masTmpHinban, ' ', 20);		/*品番変数を初期化*/
							memsetEx(masTmpLotNo, ' ', 6);			/*LOT変数を初期化*/
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

/*個別クリア画面での処理*/
void OneClearScreenProc(void)
{
	switch(mnSw2)
	{
	case 1:
		OneClearScreenDisp();
		mnSw2++;
		break;
	case 2:
		if((mlKeySts & 0x80) != 0)		/*登録キー*/
		{

			/*選択指示データ(メモリ、ファイル)を削除する。*/
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
		else if((mlKeySts & 0x40) != 0)		/*クリアキー*/
		{
			/*キャンセルなので未処理で抜ける。*/
			mnSw1 = 1;
			mnSw2 = 1;
		}
		break;
	}
}

/*全クリア画面での処理*/
void AllClearScreenProc(void)
{
	switch(mnSw2)
	{
	case 1:
		AllClearScreenDisp();
		mnSw2++;
		break;
	case 2:
		if((mlKeySts & 0x80) != 0)		/*登録キー*/
		{
			/*全指示データ(メモリ、ファイル)を削除する。*/
			fncSijiDataAllDel();
			mnCurNum = 1;
			mnTtlNum = 0;
			mnSw1 = 1;
			mnSw2 = 1;
		}
		else if((mlKeySts & 0x40) != 0)		/*クリアキー*/
		{
			/*キャンセルなので未処理で抜ける。*/
			mnSw1 = 1;
			mnSw2 = 1;
		}
		break;
	}
}

/*ダウンロード／アップロード　始まり*/
/*IrDAポート初期化*/
void subSioInit(void)
{
//	auto char fmtt[4] = {0x07, 0x01, 0x00, 0x00};	/*ボーレート:19,200,データ長:8ビット,パリティ:なし,ストップビット:1ビット*/
//	auto char fmtt[4] = {0x08, 0x01, 0x00, 0x00};	/*ボーレート:38,400,データ長:8ビット,パリティ:なし,ストップビット:1ビット*/
	auto char fmtt[4] = {0x09, 0x01, 0x00, 0x00};	/*ボーレート:115,200,データ長:8ビット,パリティ:なし,ストップビット:1ビット*/
	
	char sts, asTmp[100];

	sts = setphfmt(fmtt);
//	dspstring("init:");
//	sprintf(asTmp, "[%x]\r\n", sts);
//	dspstring(asTmp);
//	kbin();
}

/*IrDAポートオープン*/
void subSioOpen(void)
{
	char sts, asTmp[100];

	sts = ctrlphport(0xff);
//	dspstring("open:");
//	sprintf(asTmp, "[%x]\r\n", sts);
//	dspstring(asTmp);
//	kbin();
}

/*IrDAポートクローズ*/
void subSioClose(void)
{
	char sts, asTmp[100];

	while(1)
	{
		if(ckphoutbfe() == 0x00)
		{
			/*出力バッファにデータなし*/
			break;
		}
	}
	sts = ctrlphport(0x00);
//	dspstring("close:");
//	sprintf(asTmp, "[%x]\r\n", sts);
//	dspstring(asTmp);
//	kbin();
}

/*BCC生成*/
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
    sprintf(asTmp, "%02X", l2);	/*16進数に変換*/
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

/* IrＤＡからのデータ受信関数 */
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
		s1 = getph();/* １バイト受信 */
		dt = s1 & 0x00ff;
//		putph(dt);
		asTmp[n1] = dt & 0x00ff;
//		dspone(asTmp[n1]);/* 受信したデータを表示 */
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
			/*ETX受信で終了*/
			nRet = 0;
			sts = 0;
		}
	}
	return nRet;
}

/*ダウンロード*/
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

	if((fp = fopen("master  .dat", "w")) == NULL)	/* ファイルオープン（必ずファイル名８文字、拡張子３文字） */
	{
		dspstring("File Open Error!!\r\n");
		return -1;
	}
	fclose(fp);	/* ファイルのクローズ */

	if((fp = fopen("master  .dat", "a")) == NULL)	/* ファイルオープン（必ずファイル名８文字、拡張子３文字） */
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
			/*ﾎﾟｰﾀﾌﾞﾙｱﾀﾞﾌﾟﾀにﾊﾝﾃﾞｨﾀｰﾐﾅﾙが置かれていない。*/
			/*中断*/
			nRet = -1;
			nSW = 30;
		}
		else if(getkeysts() != 0)
		{
			/*キー入力あり*/
			/*中断*/
			nRet = -1;
			nSW = 30;
		}
		else if(nRec >= 20000)
		{
			/*メモリーオーバー*/
			/*中断*/
			nRet = -2;
			nSW = 30;
		}

		switch(nSW)
		{
		case 0:
			if(ckphibf() != 0)
			{
				s1 = getph();/* １バイト受信 */
				dt = s1 & 0x00ff;
			}
			if(dt == 0x02)
			{
				/*STX受信*/
				asTmp3[0] = s1;
				n1 = 0;
				nSW++;
			}
			break;
		case 1:
			if(ckphibf() != 0)
			{
				s1 = getph();/* １バイト受信 */
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
				/*中断*/
				nRet = -1;
				nSW = 30;
			}
			else if(asTmp[2] == '0' && asTmp[3] == '0' && asTmp[4] == '0' && asTmp[5] == '0' && asTmp[6] == '0')
			{
				/*完了データ*/
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
				s1 = getph();/* １バイト受信 */
				dt = s1 & 0x00ff;
				if(dt == 0x03)
				{
					/*ETX受信*/
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
						subResponseSend(0);			/*レスポンス(ACK)送信*/
						nSW = 0;
					}
					else
					{
						subResponseSend(1);			/*レスポンス(NAK)送信*/
						/*中断*/
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
				s1 = getph();/* １バイト受信 */
				dt = s1 & 0x00ff;
				if(dt == 0x03)
				{
					/*ETX受信*/
					subResponseSend(0);			/*レスポンス(ACK)送信*/
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
	fclose(fp);	/* ファイルのクローズ */
//	dspstring("download end\r\n");

	return nRet;
}

/*アップロード*/
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

	if((fp = fopen("sijidata.dat", "r")) == NULL)	/* ファイルオープン（必ずファイル名８文字、拡張子３文字） */
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
			/*ﾎﾟｰﾀﾌﾞﾙｱﾀﾞﾌﾟﾀにﾊﾝﾃﾞｨﾀｰﾐﾅﾙが置かれていない。*/
			/*中断*/
			nRet = -1;
			nSW = 40;
		}
		else if(getkeysts() != 0)
		{
			/*キー入力あり*/
			/*中断*/
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
			putph(dt);	/*STX送信*/
			dt = '2';
			asTmp3[1] = dt;
			putph(dt);	/*ID情報送信*/
			dt = 'S';
			asTmp3[2] = dt;
			putph(dt);	/*区分情報送信*/
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
				putph(dt);	/*データ番号送信*/
			}
			for(n1 = 0; n1 < 32; n1++)
			{
				dt = asTmp[n1] & 0x00ff;
				asTmp3[8 + n1] = dt;
				putph(dt);	/*指示データ送信*/
			}
			subBccMake(asTmp3, 40, asTmp4);
			dt = asTmp4[0];
			putph(dt);	/*BCC送信*/
			dt = asTmp4[1];
			putph(dt);	/*BCC送信*/
			dt = 0x03;
			putph(dt);	/*ETX送信*/
			nSW = 20;
			break;
		case 20:
			if(ckphibf() != 0)
			{
				s1 = getph();/* １バイト受信 */
				dt = s1 & 0x00ff;
				if(dt == 0x02)
				{
					/*STX受信*/
					s1 = getph();/*ID情報受信*/
					s1 = getph();/*区分情報受信*/
					s1 = getph();/*データ部受信*/
					dt = s1 & 0x00ff;
					if(dt == 0x06)
					{
						/*ACK*/
						nSW = 30;
					}
					else
					{
						/*NAK*/
						/*中断*/
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
				s1 = getph();/* １バイト受信 */
				dt = s1 & 0x00ff;
				if(dt == 0x03)
				{
					/*ETX受信*/
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
				s1 = getph();/* １バイト受信 */
				dt = s1 & 0x00ff;
				if(dt == 0x03)
				{
					/*ETX受信*/
					sts = 0;
				}
			}
			break;
		}
	}

	fclose(fp);	/* ファイルのクローズ */

//	dspstring("upload end\r\n");

	return nRet;
}

/*1:ダウンロード,2:アップロード*/
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
/*ダウンロード／アップロード　終わり*/

void subInit(void)
{
	mnSw1 = 1;				/*状態変数１を初期化*/
	mnSw2 = 1;				/*状態変数２を初期化*/
	mnAtvMode = 1;				/*上下選択状態を初期化*/
	mnCurNum = 1;				/*現在の指示数を初期化*/
	mnTtlNum = 0;				/*合計の指示数を初期化*/
	mnCurPos = 0;				/*現在の項目を初期化*/
	memsetEx(masKoukanNo, ' ', 6);		/*工管変数を初期化*/
	memsetEx(masHinban, ' ', 20);		/*品番変数を初期化*/
	memsetEx(masLotNo, ' ', 6);		/*LOT変数を初期化*/
	memsetEx(masNewKoukanNo, ' ', 6);	/*工管変数を初期化*/
	memsetEx(masNewHinban, ' ', 20);	/*品番変数を初期化*/
	memsetEx(masNewLotNo, ' ', 6);		/*LOT変数を初期化*/
	memsetEx(masTmpKoukanNo, ' ', 6);	/*工管変数を初期化*/
	memsetEx(masTmpHinban, ' ', 20);	/*品番変数を初期化*/
	memsetEx(masTmpLotNo, ' ', 6);		/*LOT変数を初期化*/

	ClrDisplay(3, 2);			/*全画面の初期化*/
	SetLcdMode(1);				/*画面モード＝ＨＴ２０モード*/
	SetSepBar(1);				/*境界線の表示*/
	setbcrfunc(bct);			/*バーコードの読み取り設定*/
	setbcrsts(0x16);			/*バーコードの読み取り時のアクション設定*/
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
				/*IrDA入力バッファにデータあり*/
//				dspstring("IrDA data ok\r\n");
				nSW = 5;
			}
			else
			{
				nSW = 99;
			}
			break;
		case 5:	/*コマンド待ち*/
			nRet = fncCommandGet();
			switch(nRet)
			{
			case 1:	/*ダウンロード*/
				subResponseSend(0);			/*レスポンス(ACK)送信*/
				nSW = 10;
				break;
			case 2:	/*アップロード*/
				subResponseSend(0);			/*レスポンス(ACK)送信*/
				nSW = 20;
				break;
			default:
				nSW = 99;
				break;
			}
			break;
		case 10:/*ダウンロード*/
			SelectAnothDisp(mnScr2, 1);		/*サブ画面*/
			dspone(0x0c);
			dspstring("ﾏｽﾀｰﾃﾞｰﾀをﾀﾞｳﾝﾛｰﾄﾞし\r\n");
			dspstring("ています。\r\n");
			dspstring("暫くお待ち下さい。\r\n");
			nRet = subDownload();
			if(nRet >= 0)
			{
				ctrlbuzz(0xff, 50, 0);		/*確認用ブザー鳴動制御 鳴動,50*20ms,通常*/
				dspone(0x0c);
				dspstring("ﾏｽﾀｰﾃﾞｰﾀのﾀﾞｳﾝﾛｰﾄﾞが\r\n");
				dspstring("終りました。\r\n");
				sprintf(asTmp, "件数:[%d]件\n\r", nRet);
				dspstring(asTmp);
				flshkb(0, asTmp);				/*キーボード入力バッファクリア*/
				waittm(70);					/* 70*20ms一時停止 2003/09/22 A.Tamura */
			}
			else if(nRet == -2)
			{
				erbz1();					/*エラーブザー鳴動制御 200ms*3回*/
				dspone(0x0c);
				dspstring("ﾒﾓﾘｰｵｰﾊﾞｰしました。\r\n");
				dspstring("ﾀﾞｳﾝﾛｰﾄﾞを中断します。\r\n");
				flshkb(0, asTmp);				/*キーボード入力バッファクリア*/
				kbin();
			}
			else
			{
				erbz1();					/*エラーブザー鳴動制御 200ms*3回*/
				dspone(0x0c);
				dspstring("ﾀﾞｳﾝﾛｰﾄﾞを中断します。\r\n");
				flshkb(0, asTmp);				/*キーボード入力バッファクリア*/
				kbin();
			}
			SelectAnothDisp(mnScr2, 0);		/*メイン画面*/
			nSW = 99;
			break;
		case 20:/*アップロード*/
			SelectAnothDisp(mnScr2, 1);		/*サブ画面*/
			dspone(0x0c);
			dspstring("指示ﾃﾞｰﾀをｱｯﾌﾟﾛｰﾄﾞし\r\n");
			dspstring("ています。\r\n");
			dspstring("暫くお待ち下さい。\r\n");
			nRet = subUpload();
			if(nRet >= 0)
			{
				ctrlbuzz(0xff, 50, 0);		/*確認用ブザー鳴動制御 鳴動,50*20ms,通常*/
				dspone(0x0c);
				dspstring("指示ﾃﾞｰﾀのｱｯﾌﾟﾛｰﾄﾞが\r\n");
				dspstring("終りました。\r\n");
				sprintf(asTmp, "件数:[%d]件\n\r", nRet);
				dspstring(asTmp);
				flshkb(0, asTmp);				/*キーボード入力バッファクリア*/
				waittm(70);					/* 70*20ms一時停止 2003/09/22 A.Tamura */
			}
			else
			{
				erbz1();					/*エラーブザー鳴動制御 200ms*3回*/
				dspone(0x0c);
				dspstring("ｱｯﾌﾟﾛｰﾄﾞを中断します。\r\n");
				flshkb(0, asTmp);				/*キーボード入力バッファクリア*/
				kbin();
			}
			SelectAnothDisp(mnScr2, 0);		/*メイン画面*/
			nSW = 99;
			break;
		case 99:/*終了処理*/
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
			/*上段選択*/
			/*前回が↑キー又は←キー又は↓キー又は→キーの場合*/
			mlKeyStsOld = mlKeySts;
			mnKeyRepeat = 1;
		}
		else if(mlKeySts != mlKeyStsOld || (mlKeySts & 0x1) != 0 || (mlKeySts & 0x2) != 0)/*前回と違うか左右トリガの場合*/
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
