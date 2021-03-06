#ifndef MainMenuH
#define MainMenuH

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Chart.hpp>
#include <Series.hpp>
#include <TeeFunci.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Db.hpp>
#include <DBTables.hpp>


#include <fcntl.h>
#include <io.h>

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <dir.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <winbase.h>
#include <shellapi.h>
#include <Printers.hpp>
#include <malloc.h>
#include <memory.h>
#include <time.h>
#include <wingdi.h>

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"

//fÞªèÀÑf[^OñæèÝú
extern struct structKSD29{
	AnsiString FUNC_ID ;  // NO
    AnsiString UPDYMD ;   // út
    AnsiString UPDTIM ;   // Ô
    AnsiString STRWHERE ; // ð¶
}KSD29;

//fÞªèf[^
extern struct structKD_1{
	AnsiString KENSA_YMD; 		// ¸\èNú
	AnsiString TOLEY_NO;  		// g[m
	AnsiString SAMPLE_P;  		// Tv|WV
	AnsiString SOKUTEI_SU;		// ªè
	AnsiString DTKSHIN; 		// ¾ÓæiÔ
	AnsiString LOTNO; 			// bgNO
	AnsiString HINBAN;			// iÔ
	AnsiString ZISCOD;			// Þ¿R[h
	AnsiString ZISNAM;			// Þ¿¼
	AnsiString KIKA_NUM1;		// Ki1iºÀ ætïRFãÀj
	AnsiString KIKA_NUM2;		// Ki2iãÀ ætïRFd³j
	AnsiString KIKA_SUB1;		// KiTu1i ætïRFÔ   æt­xF¬x ïR¦Fd¬ È°FXpj
	AnsiString KIKA_SUB2;		// KiTu1i ætïRF^Cv æt­xFPÊ              È°FPÊj
	AnsiString KEIJYO_KBN;		// `óæª
	AnsiString SOKUTEI[100];	// ªèl
	AnsiString SOKUTEI_NM;		// ªè
	AnsiString SOKUTE_AVE;		// ½Ïl
	AnsiString ADDYMD;			// o^ú
	AnsiString ADDTIM;			// o^Ô
	AnsiString UPDYMD;			// ÏXú
	AnsiString UPDTIM;			// ÏXÔ
	AnsiString UPDCHR;			// XVÒ
	AnsiString UPDCNT;			// XVñ
	AnsiString MEMO;			// õl
	AnsiString SOKUTE_MAX;		// Åål
	AnsiString SOKUTE_MIN;		// Å¬l
	AnsiString SOKUTE_OK;		// »è
	AnsiString SKTYMD; 			// ªèú
        //20170417 Y.Onishi HêæªÇÁ
        AnsiString KOJOKBN; 			// Hêæª
}KD_1;

//fÞªèÀÑf[^
extern struct structKSD21{
	int 	   InsFlag; 		// VKÌêF-1
	AnsiString DTKSHIN; 		// ¾ÓæiÔ
	AnsiString LOTNO; 			// bgNO
	AnsiString HINBAN; 			// ©ÐiÔ
	AnsiString DTKSCOD; 		// ¾ÓæR[h
	AnsiString DTKSNAM; 		// ¾Óæ¼Ì
	AnsiString ZISNAM; 			// Þ¿¼Ìiiíj
	AnsiString SOKUTEI_NUM; 	// ªèÚ
	AnsiString SOZAI_OK; 		// fÞ»è
	AnsiString MEMO; 			// õl
	AnsiString SKTYMD; 			// ªèú
	AnsiString ADDYMD; 			// o^ú
	AnsiString ADDTIM; 			// o^Ô
	AnsiString UPDYMD; 			// ÏXú
	AnsiString UPDTIM; 			// ÏXÔ
	AnsiString UPDCHR; 			// XVÒ
	AnsiString UPDCNT; 			// XVñ
}KSD21;


//fÞªèÀÑ¾×f[^
extern struct structKSD22{
	int 	   InsFlag; 		// VKÌêF-1
	AnsiString DTKSHIN; 		// ¾ÓæiÔ
	AnsiString LOTNO; 			// bgNO
	AnsiString UNQ_NO; 			// ¾×NO
	AnsiString KOMK_NO; 		// ªèÚNO
	AnsiString KOMK_NM; 		// ªèÚ¼Ì
	AnsiString KOMK_ENG; 		// ªèÚ¼Ìipêj
	AnsiString KOMK_SUB; 		// ªèÚTu¼Ì
	AnsiString KOMK_SUB_ENG; 	// ªèÚTu¼Ìipêj
	AnsiString KIKI_NO; 		// ªè@íNO
	AnsiString KIKI_NM; 		// ªè@í¼Ì
	AnsiString TANI; 			// PÊ
	AnsiString KIKA_TYPE; 		// Ki^Cv
	AnsiString KIKA_KIND; 		// KiíÞ
	AnsiString KIKA_DECI; 		// Ki¬_Èº
	AnsiString KIKA_NUM1; 		// Kil1
	AnsiString KIKA_NUM2; 		// Kil2
	AnsiString KIKA_NUM3; 		// Kil3
	AnsiString KIKA_STR; 		// Kil¶
	AnsiString KIKA_SUB1; 		// KilTu1
	AnsiString KIKA_SUB2; 		// KilTu2
	AnsiString SOKU_SU; 		// ªèw¦n
	AnsiString VALUE_TYPE; 		// ªèl\»
	AnsiString VALUE_DECI; 		// ªèl¬_Èº
	AnsiString SOKU_VAL[100]; 	// ªèl
	//AnsiString SOKU_VAL01; 		// ªèl1
	//AnsiString SOKU_VAL02; 		// ªèl2
	//AnsiString SOKU_VAL03; 		// ªèl3
	//AnsiString SOKU_VAL04; 		// ªèl4
	//AnsiString SOKU_VAL05; 		// ªèl5
	//AnsiString SOKU_VAL06; 		// ªèl6
	//AnsiString SOKU_VAL07; 		// ªèl7
	//AnsiString SOKU_VAL08; 		// ªèl8
	//AnsiString SOKU_VAL09; 		// ªèl9
	//AnsiString SOKU_VAL10; 		// ªèl10
	AnsiString SOKU_VAL_SU;		// ªèÀÑn
	AnsiString SOKU_VAL_AVE; 	// ªè½Ïl
	AnsiString SOKU_VAL_MAX; 	// ªèÅål
	AnsiString SOKU_VAL_MIN;	// ªèÅ¬l
	AnsiString SOKU_OK; 		// ªèl»è
	AnsiString SKTYMD; 			// ªèú
	AnsiString ADDYMD; 			// o^ú
	AnsiString ADDTIM; 			// o^Ô
	AnsiString UPDYMD; 			// ÏXú
	AnsiString UPDTIM; 			// ÏXÔ
	AnsiString UPDCHR; 			// XVÒ
	AnsiString UPDCNT; 			// XVñ
	AnsiString HINBAN; 			// ©ÐiÔ
}KSD22;

//fÞªèÀÑáOf[^
extern struct structKSD23{
	int 	   InsFlag; 		// VKÌêF-1
//	AnsiString DTKSHIN; 		// ¾ÓæiÔ
//	AnsiString LOTNO; 			// bgNO
//	AnsiString UNQ_NO; 			// ¾×NO
//	AnsiString SOKU_NO; 		// ªèNO
//	AnsiString SOKU_VAL; 		// ªèl
}KSD23;

//efÞÌÅè¶ñ
extern struct structFixStr{
	AnsiString TABLE1;			// e[u¼
	AnsiString TABLE2;			// áOe[u¼
	AnsiString KOMK_NO;			// ªèÚNo
	AnsiString ORDER_NO;		// \¦
	AnsiString KOMK_NM;			// ªèÚ¼Ì
	AnsiString KOMK_ENG;		// ªèÚ¼Ìipêj
	AnsiString KIKI_NO;			// ªè@íNo
	AnsiString KIKI_NM;			// ªè@í¼Ì
	AnsiString TANI[5];			// PÊ
	AnsiString KIKA_TYPE;		// Ki^Cv
	AnsiString KIKA_KIND;		// KiíÞ
	AnsiString KIKA_DECI;		// Ki¬_Èº
	AnsiString KIKA_NUM2;		// KilQ
	AnsiString KIKA_NUM3;		// KilR
	AnsiString KIKA_STR;		// Kil¶
	AnsiString SOKU_FLG;		// ªèÚÌL³
	AnsiString TOKU_FLG;		// ÁÊÚÌL³
	AnsiString KIKA_PRT;		// ãÀEºÀlÌóü
	AnsiString VALUE_TYPE;		// ªèl\»
	AnsiString VALUE_DECI;		// ªèl¬_Èº
	AnsiString F_SOKUTE_KBN;	// tB[h¼Fªèæª
	AnsiString F_KIKA_NUM1;		// tB[h¼FKilP
	AnsiString F_KIKA_NUM2;		// tB[h¼FKilQ
	AnsiString F_KIKA_SUB1;		// tB[h¼FKilTuP
	AnsiString F_KIKA_SUB2;		// tB[h¼FKilTuQ
	AnsiString F_KEIJYO_KBN;	// tB[h¼F`óæª
	AnsiString F_SOKUTEI_1;		// tB[h¼FªèlP
	AnsiString F_SOKUTEI_2;		// tB[h¼FªèlQ
	AnsiString F_SOKUTEI_SU;	// tB[h¼Fªèw¦
	AnsiString F_SOKUTEI_NM;	// tB[h¼FªèÀÑ
	AnsiString F_SOKUTE_AVE;	// tB[h¼Fªèl ½Ï
	AnsiString F_SOKUTEICHI;	// tB[h¼Fªèl
	AnsiString W_SOKUTE_KBN;	// tB[h¼Fªèæª
} FixStr[18];
extern int FixStrNum;			// Åè¶ñÌzñ 16

extern AnsiString MEMOStr[18];  // eªèlÌõl

extern AnsiString sBufSQL;      // obt@ SQL¶

//fÞªèÀÑf[^iKSD21jÌ
//XVñEfÞªèXVÉKvÈL[ðÛ¶
extern TStrings *sDTKSHIN;    	// ¾ÓæiÔ
extern TStrings *sLOTNO; 		// bgNO
extern TStrings *sHINBAN; 		// ©ÐiÔ
extern int isDTKSHINNum;		// f[^

#endif







