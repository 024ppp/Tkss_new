//i¿¸io×jVXe@e[uo^
struct  KSM01_DATA   {          //»iéæ}X^[
    char	DTKSHIN[21];        //¾ÓæiÔ
    char   	REVCNT[4];         	//üùÔ
    char   	HINBAN[21];        	//©ÐiÔ
    char  	DTKSCOD[6];        	//¾ÓæR[h
    char  	DTKSNAM[51];        //¾Óæ¼Ì
    char  	ZISNAM[21];         //Þ¿¼Ìiiíj
    char  	HINMEI[61];         //i¼
    char  	DTKSHIN1_SZ[21];    //fÞp¾ÓæiÔP
    char  	DTKSHIN2_SZ[21];    //fÞp¾ÓæiÔQ
    char  	DTKSHIN3_SZ[21];    //fÞp¾ÓæiÔR
    char  	DTKSHIN4_SZ[21];    //fÞp¾ÓæiÔS
    char  	DTKSHIN5_SZ[21];    //fÞp¾ÓæiÔT
    char  	DTKSHIN6_SZ[21];    //fÞp¾ÓæiÔU
    char    LOT_LINK_SZ[2];    	//fÞbgÌN
    char    SOKUTEI_NUM[3];    	//ªèÚ
    char    OUT_TITLE1[5];     	//¬Ñ^CgoÍÚP
    char    OUT_TITLE2[5];     	//¬Ñ^CgoÍÚQ
    char    OUT_TITLE3[5];     	//¬Ñ^CgoÍÚR
    char    OUT_TITLE4[5];     	//¬Ñ^CgoÍÚS
    char    OUT_TITLE5[5];     	//¬Ñ^CgoÍÚT
    char    OUT_TITLE6[5];     	//¬Ñ^CgoÍÚU
    char    OUT_TITLE7[5];     	//¬Ñ^CgoÍÚV
    char    OUT_TITLE8[5];     	//¬Ñ^CgoÍÚW
    char    X_OUT[2];          	//Xo[(½ÏjÌoÍ
    char  	MEMO[129];      	//õl
    char  	ADDYMD[9];         	//o^ú
    char  	ADDTIM[5];         	//o^Ô
    char  	UPDYMD[9];         	//ÏXú
    char  	UPDTIM[5];         	//ÏXÔ
    char    UPDCHR[7];         	//XVÒ
    char    UPDCNT[4];         	//XVñ
    char    UPDNAME[50];        //\¦pXVÒl[	//2003.05.17 E.Takase Add
    char    SOKCHR[7];         	//ªèÒ                //onishi
} ;

struct KSM02_DATA {       		//»iKi¾×}X^[
    char	DTKSHIN[21];        //¾ÓæiÔ
    char    REVCNT[5];         	//üùÔ
    char    UNQ_NO[5];         	//¾×NO
    char    ORDER_NO[5];       	//\¦Eóü
    char    SKB_NO[2];         	//¯ÊNO
    char  	HINBAN_SK[21];      //iÔ
    char    KOMK_NO[5];        	//ªèÚNO
    char  	KOMK_NM[41];        //ªèÚ¼Ì
    char  	KOMK_ENG[41];       //ªèÚ¼Ìipêj
    char  	KOMK_SUB[21];       //ªèÚTu¼Ì
    char  	KOMK_SUB_ENG[21];   //ªèÚTu¼Ìipêj
    char    KIKI_NO[3];        	//ªè@íNO
    char  	KIKI_NM[41];        //ªè@í¼Ì
    char  	TANI[21];           //PÊ
    char    KIKA_TYPE[2];      	//Ki^Cv
    char    KIKA_KIND[2];      	//KiíÞ
    char    KIKA_DECI[2];      	//Ki¬_Èº
    char    KIKA_NUM1[13];      //Kil1
    char    KIKA_NUM2[13];      //Kil2
    char    KIKA_NUM3[13];      //Kil3
    char  	KIKA_STR[41];       //Kil¶
    char  	KIKA_SUB1[21];      //KilTu1
    char   	KIKA_SUB2[21];      //KilTu2
    char  	KIKA_SUB3[21];      //KilTu3
    char    SOKU_SU[3];        	//ªèw¦
    char    SOKU_FLG[2];       	//ªèÚÌL³
    char    TOKU_FLG[2];       	//ÁÊÚÌL³
    char    KIKA_PRT[2];       	//ãÀºÀlÌóü
    char    VALUE_TYPE[2];     	//ªèl\»
    char    VALUE_DECI[2];     	//ªèl¬_Èº
};

struct KSM11_DATA {          	//ªèÚ}X^[
    char	KOMK_NO[5];        	//ªèÚ
    char    ORDER_NO[5];       	//\¦Eóü
    char  	KOMK_NM[41];        //ªèÚ¼Ì
    char  	KOMK_ENG[41];       //ªèÚ¼Ìipêj
    char  	KOMK_SUB[21];       //ªèÚTu¼Ì
    char  	KOMK_SUB_ENG[21];   //ªèÚTu¼Ìipêj
    char    KIKI_NO[3];        	//ªè@íNO
    char  	KIKI_NM[41];        //ªè@í¼Ì
    char  	TANI[21];           //PÊ
    char    KIKA_TYPE[2];      	//Ki^Cv
    char    KIKA_KIND[2];      	//KiíÞ
    char    KIKA_DECI[2];      	//Ki¬_Èº
    char    KIKA_NUM1[13];      //KilP
    char    KIKA_NUM2[13];      //KilQ
    char    KIKA_NUM3[13];      //KilR
    char  	KIKA_STR[41];       //Kil¶
    char  	KIKA_SUB1[21];      //KilTuP
    char  	KIKA_SUB2[21];      //KilTuQ
    char  	KIKA_SUB3[21];      //KilTuR
    char    SOKU_SU[3];        	//ªèw¦
    char    SOKU_FLG[2];       	//ªèÚÌL³
    char    TOKU_FLG[2];       	//ÁÊÚÌL³
    char    KIKA_PRT[2];       	//ãÀºÀlÌóü
    char    VALUE_TYPE[2];     	//ªèl\»
    char    VALUE_DECI[2];     	//ªèl¬_Èº
    char   	ADDYMD[9];         	//o^ú
    char   	ADDTIM[5];         	//o^Ô
    char   	UPDYMD[9];         	//ÏXú
    char  	UPDTIM[5];         	//ÏXÔ
    char   	UPDCHR[7];         	//XVÒ
    char    UPDCNT[4];         	//XVñ
    char    UPDNAME[50];        //\¦pXVÒl[	//2003.05.17 E.Takase Add
};

struct  KSM12_DATA   {          //Þ¿Ø¾Ú}X^[
    char	KOMK_NO[5];         //ªèÚ
    char    ORDER_NO[5];        //\¦Eóü
    char  	KOMK_NM[41];        //ªèÚ¼Ì
    char  	KOMK_ENG[41];       //ªèÚ¼Ìipêj
    char  	KOMK_SUB[21];       //ªèÚTu¼Ì
    char  	KOMK_SUB_ENG[21];   //ªèÚTu¼Ìipêj
    char    KIKI_NO[3];         //ªè@íNO
    char  	KIKI_NM[41];        //ªè@í¼Ì
    char  	TANI[21];           //PÊ
    char    KIKA_TYPE[2];       //Ki^Cv
    char    KIKA_KIND[2];       //KiíÞ
    char    KIKA_DECI[2];       //Ki¬_Èº
    char    KIKA_NUM1[13];      //KilP
    char    KIKA_NUM2[13];      //KilQ
    char    KIKA_NUM3[13];      //KilR
    char  	KIKA_STR[41];       //Kil¶
    char  	KIKA_SUB1[21];      //KilTuP
    char  	KIKA_SUB2[21];      //KilTuQ
    char  	KIKA_SUB3[21];      //KilTuR
    char    SOKU_SU[3];         //ªèw¦
    char    SOKU_FLG[2];        //ªèÚÌL³
    char    TOKU_FLG[2];        //ÁÊÚÌL³
    char    KIKA_PRT[2];        //ãÀºÀlÌóü
    char    VALUE_TYPE[2];      //ªèl\»
    char    VALUE_DECI[2];      //ªèl¬_Èº
    char  	ADDYMD[9];          //o^ú
    char  	ADDTIM[5];          //o^Ô
    char  	UPDYMD[9];          //ÏXú
    char  	UPDTIM[5];          //ÏXÔ
    char    UPDCHR[7];          //XVÒ
    char    UPDCNT[4];          //XVñ
    char    UPDNAME[50];        //\¦pXVÒl[	//2003.05.17 E.Takase Add
};


struct  KSM13_DATA   {          //fÞªèÚ}X^[
    char	KOMK_NO[5];         //ªèÚ
    char    ORDER_NO[5];        //\¦Eóü
    char  	KOMK_NM[41];        //ªèÚ¼Ì
    char  	KOMK_ENG[41];       //ªèÚ¼Ìipêj
    char  	KOMK_SUB[21];       //ªèÚTu¼Ì
    char  	KOMK_SUB_ENG[21];   //ªèÚTu¼Ìipêj
    char    KIKI_NO[3];         //ªè@íNO
    char  	KIKI_NM[41];        //ªè@í¼Ì
    char  	TANI[21];           //PÊ
    char    KIKA_TYPE[2];       //Ki^Cv
    char    KIKA_KIND[2];       //KiíÞ
    char    KIKA_DECI[2];       //Ki¬_Èº
    char    KIKA_NUM1[13];      //KilP
    char    KIKA_NUM2[13];      //KilQ
    char    KIKA_NUM3[13];      //KilR
    char  	KIKA_STR[41];       //Kil¶
    char  	KIKA_SUB1[21];      //KilTuP
    char  	KIKA_SUB2[21];      //KilTuQ
    char  	KIKA_SUB3[21];      //KilTuR
    char    SOKU_SU[3];         //ªèw¦
    char    SOKU_FLG[2];        //ªèÚÌL³
    char    TOKU_FLG[2];        //ÁÊÚÌL³
    char    KIKA_PRT[2];        //ãÀºÀlÌóü
    char    VALUE_TYPE[2];      //ªèl\»
    char    VALUE_DECI[2];      //ªèl¬_Èº
    char  	ADDYMD[9];          //o^ú
    char  	ADDTIM[5];          //o^Ô
    char  	UPDYMD[9];          //ÏXú
    char  	UPDTIM[5];          //ÏXÔ
    char    UPDCHR[7];          //XVÒ
    char    UPDCNT[4];          //XVñ
    char    UPDNAME[50];        //\¦pXVÒl[	//2003.05.17 E.Takase Add
};

struct  KSM14_DATA {            //ªè@íÚ}X^[
    char    KIKA_NO[3];         //ÚNO
    char    ORDER_NO[3];        //\¦Eóü
    char  	KIKI_NM[41];        //ªè@í¼
    char  	ADDYMD[9];          //o^ú
    char  	ADDTIM[5];          //o^Ô
    char  	UPDYMD[9];          //ÏXú
    char  	UPDTIM[5];          //ÏXÔ
    char    UPDCHR[7];          //XVÒ
    char    UPDCNT[4];          //XVñ
    char    UPDNAME[50];        //\¦pXVÒl[	//2003.05.17 E.Takase Add
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
    char    UPDNAME[50];        //\¦pXVÒl[	//2003.05.17 E.Takase Add
};

struct KSD01_DATA {          	//ªèÀÑf[^
    char  	DTKSHIN[21];        //¾ÓæiÔ
    char  	LOTNO[7];           //bgNo
    char	LOTNO1_SZ[7];	    //fÞ¸pbgNo1
    char 	LOTNO2_SZ[7];       //fÞ¸pbgNO2
    char 	LOTNO3_SZ[7];       //fÞ¸pbgNO3
    char 	LOTNO4_SZ[7];       //fÞ¸pbgNO4
    char 	LOTNO5_SZ[7];       //fÞ¸pbgNO5
    char 	LOTNO6_SZ[7];       //fÞ¸pbgNO6
    char	LOTNOCHANGE1_SZ[2]; //fÞ¸pbgÏXtONO1
    char	LOTNOCHANGE2_SZ[2]; //fÞ¸pbgÏXtONO2
    char	LOTNOCHANGE3_SZ[2]; //fÞ¸pbgÏXtONO3
    char	LOTNOCHANGE4_SZ[2]; //fÞ¸pbgÏXtONO4
    char	LOTNOCHANGE5_SZ[2]; //fÞ¸pbgÏXtONO5
    char	LOTNOCHANGE6_SZ[2]; //fÞ¸pbgÏXtONO6
    char  	HINBAN[21];         //©ÐiÔ
    char  	DTKSCOD[6];         //¾ÓæR[h
    char  	DTKSNAM[51];        //¾Óæ¼Ì
    char  	ZISNAM[21];         //Þ¿¼Ì
    char  	HINMEI[61];         //i¼
    char  	DTKSHIN1_SZ[21];    //fÞp¾ÓæiÔP
    char  	DTKSHIN2_SZ[21];    //fÞp¾ÓæiÔQ
    char  	DTKSHIN3_SZ[21];    //fÞp¾ÓæiÔR
    char  	DTKSHIN4_SZ[21];    //fÞp¾ÓæiÔS
    char  	DTKSHIN5_SZ[21];    //fÞp¾ÓæiÔT
    char  	DTKSHIN6_SZ[21];    //fÞp¾ÓæiÔU
    char  	HINBAN1_SZ[21];     //fÞp¾ÓæiÔP
    char  	HINBAN2_SZ[21];     //fÞp¾ÓæiÔQ
    char  	HINBAN3_SZ[21];     //fÞp¾ÓæiÔR
    char  	HINBAN4_SZ[21];     //fÞp¾ÓæiÔS
    char  	HINBAN5_SZ[21];     //fÞp¾ÓæiÔT
    char  	HINBAN6_SZ[21];     //fÞp¾ÓæiÔU
    char    LOT_LINK_SZ[2];    	//fÞpbgÌN
    char    SOKUTEI_NUM[3];    	//ªèÚ
    char    SOZAI_OK[3];       	//fÞ»è
    char    SOZAI_OK_PRT[3];   	//fÞ»è@óüp
    char    SYUKA_OK[3];       	//o×»è
    char    SYUKA_OK_PRT[3];   	//o×»è@óüp
    char    OUT_TITLE1[5];     	//¬Ñ^CgoÍÚP
    char    OUT_TITLE2[5];     	//¬Ñ^CgoÍÚQ
    char    OUT_TITLE3[5];     	//¬Ñ^CgoÍÚR
    char    OUT_TITLE4[5];     	//¬Ñ^CgoÍÚS
    char    OUT_TITLE5[5];     	//¬Ñ^CgoÍÚT
    char    OUT_TITLE6[5];     	//¬Ñ^CgoÍÚU
    char   	OUT_TITLE7[5];     	//¬Ñ^CgoÍÚV
    char   	OUT_TITLE8[5];     	//¬Ñ^CgoÍÚW
    char   	X_OUT[2];          	//Xo[ÌoÍ
    char  	MEMO[129];        	//õl
    char  	SKTYMD_SZ[9];       //fÞpªèú
    char  	SKTYMD_SZ_PRT[9];   //fÞpªèúióüpj
    char  	SKTYMD[9];         	//o×pªèú
    char  	SKTYMD_PRT[9];      //o×pªèúióüpj
    char  	ADDYMD[9];         	//ã\o^ú
    char  	ADDTIM[5];         	//ã\o^Ô
    char  	UPDYMD[9];         	//ã\ÏXú
    char  	UPDTIM[5];         	//ã\ÏXÔ
    char    UPDCHR[7];         	//ã\XVÒ
    char    UPDCNT[4];         	//ã\XVñ

    char  	KOMKNO1_SZ[5];    	//fÞp¾ÓæiÔP
    char  	KOMKNO2_SZ[5];    	//fÞp¾ÓæiÔQ
    char  	KOMKNO3_SZ[5];    	//fÞp¾ÓæiÔR
    char  	KOMKNO4_SZ[5];    	//fÞp¾ÓæiÔS
    char  	KOMKNO5_SZ[5];    	//fÞp¾ÓæiÔT
    char  	KOMKNO6_SZ[5];    	//fÞp¾ÓæiÔU
    char  	KOMKNM1_SZ[41];    	//fÞp¾ÓæiÔP
    char  	KOMKNM2_SZ[41];    	//fÞp¾ÓæiÔQ
    char  	KOMKNM3_SZ[41];    	//fÞp¾ÓæiÔR
    char  	KOMKNM4_SZ[41];    	//fÞp¾ÓæiÔS
    char  	KOMKNM5_SZ[41];    	//fÞp¾ÓæiÔT
    char  	KOMKNM6_SZ[41];    	//fÞp¾ÓæiÔU
    char  	KOMKSUB1_SZ[21];    //fÞp¾ÓæiÔP
    char  	KOMKSUB2_SZ[21];    //fÞp¾ÓæiÔQ
    char  	KOMKSUB3_SZ[21];    //fÞp¾ÓæiÔR
    char  	KOMKSUB4_SZ[21];    //fÞp¾ÓæiÔS
    char  	KOMKSUB5_SZ[21];    //fÞp¾ÓæiÔT
    char  	KOMKSUB6_SZ[21];    //fÞp¾ÓæiÔU
	bool	UPD_FLG;			//XVLètO
	bool	SAVE_FLG;			//Û¶tO
    char    UPDNAME[50];        //\¦pXVÒl[	//2003.05.17 E.Takase Add

//    char  	HINBAN[9];         	//HÇ­sú
    char  	KOKBNG[7];         	//HÇÔ
};

struct KSD02_DATA {          	//ªèÀÑ¾×f[^
    char  	DTKSHIN[21];        //¾ÓæiÔ
    char  	LOTNO[7];          	//bgNo
    char  	UNQ_NO[5];         	//fÞpbgNO
    char 	ORDER_NO[5];       	//©ÐiÔ
    char   	SKB_NO[2];         	//¾ÓæR[h
    char  	HINBAN_SK[21];      //¾Óæ¼Ì
    char   	KOMK_NO[5];        	//Þ¿¼Ì
    char   	KOMK_NM[41];        //i¼
    char	KOMK_ENG[41];       //fÞp¾ÓæiÔP
    char  	KOMK_SUB[21];       //fÞp¾ÓæiÔQ
    char  	KOMK_SUB_ENG[21];   //fÞp¾ÓæiÔR
    char    KIKI_NO[3];        	//ªè@íNO
    char  	KIKI_NM[41];        //ªè@í¼Ì
    char  	TANI[21];           //PÊ
    char   	KIKA_TYPE[2];      	//Ki^Cv
    char   	KIKA_KIND[2];      	//KiíÞ
    char   	KIKA_DECI[2];      	//Ki¬_Èº
    char    KIKA_NUM1[13];      //KilP
    char    KIKA_NUM2[13];      //KilQ
    char    KIKA_NUM3[13];      //KilR
    char  	KIKA_STR[41];       //Kil¶
    char  	KIKA_SUB1[21];      //KilTuP
    char   	KIKA_SUB2[21];      //KilTuQ
    char   	KIKA_SUB3[21];      //KilTuR
    char    SOKU_SU[3];        	//ªèw¦
    char   	SOKU_FLG[2];       	//ªèÚÌL³
    char    TOKU_FLG[2];       	//ÁÊÚÌL³
    char    KIKA_PRT[2];       	//ãÀºÀlÌóü
    char    VALUE_TYPE[2];     	//ªèl\»
    char    VALUE_DECI[2];     	//ªèl¬_Èº
    char  	SOKU_VAL01[15];     //ªèlP
    char 	SOKU_VAL02[15];     //ªèlQ
    char  	SOKU_VAL03[15];     //ªèlR
    char  	SOKU_VAL04[15];     //ªèlS
    char  	SOKU_VAL05[15];     //ªèlT
    char  	SOKU_VAL06[15];     //ªèlU
    char  	SOKU_VAL07[15];     //ªèlV
    char  	SOKU_VAL08[15];     //ªèlW
    char  	SOKU_VAL09[15];     //ªèlX
    char  	SOKU_VAL10[15];     //ªèlPO
    char    SOKU_VAL_SU[3];    	//ªèÀÑ
    char    SOKU_VAL_AVE[16];   //ªè½Ïl
    char    SOKU_VAL_MAX[15];   //ªèÅål
    char    SOKU_VAL_MIN[15];   //ªèÅ¬l
    char    SOKU_OK[3];        	//ªèl»è
    char  	DISP_VAL01[15];     //óüpªèlP
    char  	DISP_VAL02[15];     //óüpªèlQ
    char  	DISP_VAL03[15];     //óüpªèlR
    char  	DISP_VAL04[15];     //óüpªèlS
    char  	DISP_VAL05[15];     //óüpªèlT
    char  	DISP_VAL06[15];     //óüpªèlU
    char  	DISP_VAL07[15];     //óüpªèlV
    char  	DISP_VAL08[15];     //óüpªèlW
    char  	DISP_VAL09[15];     //óüpªèlX
    char  	DISP_VAL10[15];     //óüpªèlPO
    char    DISP_VAL_SU[3];    	//óüpªèÀÑ
    char    DISP_VAL_AVE[16];   //óüpªè½Ïl
    char    DISP_VAL_MAX[15];   //óüpªèÅål
    char    DISP_VAL_MIN[15];   //óüpªèÅ¬l
    char    DISP_OK[3];        	//óüpªèl»è
    char  	SKTYMD[9];         	//ªèú
    char  	ADDYMD[9];         	//o^ú
    char  	ADDTIM[9];         	//o^Ô
    char  	UPDYMD[9];         	//ÏXú
    char  	UPDTIM[9];         	//ÏXÔ
    char    UPDCHR[7];         	//XVÒ
    char    UPDCNT[4];         	//XVñ
    char    UPDNAME[50];        //\¦pXVÒl[	//2003.05.17 E.Takase Add

    char  	HINBAN[9];         	//HÇ­sú
    char  	KOKBNG[7];         	//HÇÔ
};


struct  KSD03_DATA   {          //ªèÀÑáOf[^
    char  	DTKSHIN[21];        //¾ÓæiÔ
    char  	LOTNO[7];           //bgNO
    char    UNQ_NO[5];          //¾×NO
    char  	SOKU_NO[3];         //ªèNOi½ñÚÌªèj
    char  	SOKU_VAL[15];       //ªèl
    char  	DISP_VAL[15];       //óüpªèl

    char  	HINBAN[9];         	//HÇ­sú
    char  	KOKBNG[7];         	//HÇÔ
};

struct  KSD11_DATA   {          //ªèÀÑªf[^
    char  	DTKSHIN[21];        //¾ÓæiÔ
    char  	LOTNO[7];           //bgNO
    char    BNKT_UNQ_NO[5];     //ªp¾×NO
    char    UNQ_NO[5];          //¾×NO
    char    KOMK_NO[5];         //ªèÚNO
    char    SOKU_SU[3];         //ªèw¦
    char  	SOKU_VAL01[15];     //ªèl1
    char  	SOKU_VAL02[15];     //ªèl2
    char  	SOKU_VAL03[15];     //ªèl3
    char  	SOKU_VAL04[15];     //ªèl4
    char  	SOKU_VAL05[15];     //ªèl5
    char  	SOKU_VAL06[15];     //ªèl6
    char  	SOKU_VAL07[15];     //ªèl7
    char  	SOKU_VAL08[15];     //ªèl8
    char 	SOKU_VAL09[15];     //ªèl9
    char  	SOKU_VAL10[15];     //ªèl10
    char    SOKU_VAL_SU[3];     //ªèÀÑ
    char    SOKU_VAL_AVE[16];   //ªè½Ïl
    char    SOKU_VAL_MAX[16];   //ªèÅål
    char    SOKU_VAL_MIN[16];   //ªèÅ¬l
    char    SOKU_OK[2];         //ªèl»è
    char  	SKTYMD[9];          //ªèú
    char  	ADDYMD[9];          //o^ú
    char  	ADDTIM[5];          //o^Ô
    char  	UPDYMD[9];          //ÏXú
    char  	UPDTIM[5];          //ÏXÔ
    char    UPDCHR[7];          //XVÒ
    char    UPDCNT[4];          //XVñ
    char    UPDNAME[50];        //\¦pXVÒl[	//2003.05.17 E.Takase Add

    char  	HINBAN[9];         	//HÇ­sú
    char  	KOKBNG[7];         	//HÇÔ
};

struct  KSD12_DATA   {          //ªèÀÑªáOf[^
    char  	DTKSHIN[21];        //¾ÓæiÔ
    char  	LOTNO[7];           //bgNO
    char    BNKT_UNQ_NO[5];     //ªp¾×NO
    char    SOKU_NO[3];         //ªèNO
    char  	SOKU_VAL[15];       //ªèl

    char  	HINBAN[9];         	//HÇ­sú
    char  	KOKBNG[7];         	//HÇÔ
};

struct  KSD21_DATA   {          //fÞªèÀÑf[^
    char  	DTKSHIN[21];        //fÞ¸ÌiÔ
    char  	LOTNO[7];           //bgNO
    char  	HINBAN[21];         //©ÐiÔ
    char  	DTKSCOD[6];         //¾ÓæR[h
    char  	DTKSNAM[51];        //¾Óæ¼Ì
    char  	ZISNAM[21];         //Þ¿¼Ìiiíj
    char    SOKUTEI_NUM[3];     //ªèÚ
    char    SOZAI_OK[2];        //fÞ»è
    char  	MEMO[129];          //õl
    char  	SKTYMD[9];          //ªèú
    char  	ADDYMD[9];          //o^ú
    char  	ADDTIM[5];          //o^Ô
    char  	UPDYMD[9];          //ÏXú
    char  	UPDTIM[5];          //ÏXÔ
    char    UPDCHR[7];          //XVÒ
    char    UPDCNT[4];          //XVñ
    char    UPDNAME[50];        //\¦pXVÒl[	//2003.05.17 E.Takase Add

//    char  	HINBAN[9];         	//HÇ­sú
    char  	KOKBNG[7];         	//HÇÔ
};

struct  KSD22_DATA   {          //fÞªèÀÑ¾×f[^
    char  	DTKSHIN[21];        //¾ÓæiÔ
    char  	LOTNO[7];           //bgNO
    char    UNQ_NO[5];          //¾×NO
    char    KOMK_NO[5];         //ªèÚNO
    char  	KOMK_NM[41];        //ªèÚ¼Ì
    char  	KOMK_ENG[41];       //ªèÚ¼Ìipêj
    char  	KOMK_SUB[21];       //ªèÚTu¼Ì
    char  	KOMK_SUB_ENG[21];   //ªèÚTu¼Ìipêj
    char    KIKI_NO[3];         //ªè@íNO
    char  	KIKI_NM[41];        //ªè@í¼Ì
    char  	TANI[21];           //PÊ
    char    KIKA_TYPE[2];       //Ki^Cv
    char    KIKA_KIND[2];       //KiíÞ
    char    KIKA_DECI[2];       //Ki¬_Èº
    char    KIKA_NUM1[13];      //KilP
    char    KIKA_NUM2[13];      //KilQ
    char    KIKA_NUM3[13];      //KilR
    char  	KIKA_STR[41];       //Kil¶
    char  	KIKA_SUB1[21];      //KilTuP
    char  	KIKA_SUB2[21];      //KilTuQ
    char    SOKU_SU[3];         //ªèw¦
	char	VALUE_TYPE[2];		//ªèl\»
    char    VALUE_DECI[2];      //ªèl¬_Èº
    char  	SOKU_VAL01[15];     //ªèlP
    char  	SOKU_VAL02[15];     //ªèlQ
    char  	SOKU_VAL03[15];     //ªèlR
    char  	SOKU_VAL04[15];     //ªèlS
    char  	SOKU_VAL05[15];     //ªèlT
    char  	SOKU_VAL06[15];     //ªèlU
    char  	SOKU_VAL07[15];     //ªèlV
    char  	SOKU_VAL08[15];     //ªèlW
    char  	SOKU_VAL09[15];     //ªèlX
    char  	SOKU_VAL10[15];     //ªèlPO
    char    SOKU_VAL_SU[3];     //ªèÀÑ
    char    SOKU_VAL_AVE[14];   //ªè½Ïl
    char    SOKU_VAL_MAX[13];   //ªèÅål
    char    SOKU_VAL_MIN[13];   //ªèÅ¬l
    char    SOKU_OK[2];         //ªèl»è
    char  	SKTYMD[9];          //ªèú
    char  	ADDYMD[9];          //o^ú
    char  	ADDTIM[5];          //o^Ô
    char  	UPDYMD[9];          //ÏXú
    char  	UPDTIM[5];          //ÏXÔ
    char    UPDCHR[7];          //XVÒ
    char    UPDCNT[4];          //XVñ
    char    UPDNAME[50];        //\¦pXVÒl[	//2003.05.17 E.Takase Add

    char  	HINBAN[9];         	//HÇ­sú
    char  	KOKBNG[7];         	//HÇÔ
};

struct  KSD23_DATA   {          //fÞªèÀÑáOf[^
    char  	DTKSHIN[21];        //¾ÓæiÔ
    char  	LOTNO[7];           //bgNO
    char    UNQ_NO[5];          //¾×NO
    char    SOKU_NO[3];         //ªèNOi½ñÚÌªèj
    char  	SOKU_VAL[15];       //ªèl

    char  	HINBAN[9];         	//HÇ­sú
    char  	KOKBNG[7];         	//HÇÔ
};


struct GRAPHADDRESS	{
	int 	GRID;		//GridÔ
	int 	COL;        //X^[gJ
	double 	SUM;        //bgv
	double 	AVE;        //bg½Ï
    double 	MAX;        //bgMax
	double 	MIN;        //bgMin
	int 	NCNT;       //bgTv
	char LOTNAME[6]; 	//bg¼  	//2003.05.17 E.Takase Add
};

struct RSCOM {
	int COMNO;
};

struct KIKAKU {
	char HANI[50];
	char UPLIMIT[20];
	char LOLIMIT[20];
};


struct CELLINFO_DATA {          //ªèÀÑ¾×f[^
    char  	DTKSHIN[21];        //¾ÓæiÔ
    char  	LOTNO[7];          	//bgNo
    char  	UNQ_NO[5];         	//fÞpbgNO
    char 	ORDER_NO[5];       	//©ÐiÔ
    char   	SKB_NO[2];         	//¾ÓæR[h
    char  	HINBAN_SK[21];      //¾Óæ¼Ì
    char   	KOMK_NO[5];        	//Þ¿¼Ì
    char   	KOMK_NM[41];        //i¼
    char	KOMK_ENG[41];       //fÞp¾ÓæiÔP
    char  	KOMK_SUB[21];       //fÞp¾ÓæiÔQ
    char  	KOMK_SUB_ENG[21];   //fÞp¾ÓæiÔR
    char    KIKI_NO[3];        	//ªè@íNO
    char  	KIKI_NM[41];        //ªè@í¼Ì
    char  	TANI[21];           //PÊ
    char   	KIKA_TYPE[2];      	//Ki^Cv
    char   	KIKA_KIND[2];      	//KiíÞ
    char   	KIKA_DECI[2];      	//Ki¬_Èº
    char    KIKA_NUM1[13];      //KilP
    char    KIKA_NUM2[13];      //KilQ
    char    KIKA_NUM3[13];      //KilR
    char  	KIKA_STR[41];       //Kil¶
    char  	KIKA_SUB1[21];      //KilTuP
    char   	KIKA_SUB2[21];      //KilTuQ
    char   	KIKA_SUB3[21];      //KilTuR
    char    SOKU_SU[3];        	//ªèw¦
    char   	SOKU_FLG[2];       	//ªèÚÌL³
    char    TOKU_FLG[2];       	//ÁÊÚÌL³
    char    KIKA_PRT[2];       	//ãÀºÀlÌóü
    char    VALUE_TYPE[2];     	//ªèl\»
    char    VALUE_DECI[2];     	//ªèl¬_Èº
    char    SOKU_VAL_SU[3];    	//ªèÀÑ
    char    SOKU_VAL_AVE[14];   //ªè½Ïl
    char    SOKU_VAL_MAX[13];   //ªèÅål
    char    SOKU_VAL_MIN[13];   //ªèÅ¬l
    char    SOKU_OK[2];        	//ªèl»è
    char    DISP_VAL_SU[3];    	//óüpªèÀÑ
    char    DISP_VAL_AVE[14];   //óüpªè½Ïl
    char    DISP_VAL_MAX[13];   //óüpªèÅål
    char    DISP_VAL_MIN[13];   //óüpªèÅ¬l
    char    DISP_OK[2];        	//óüpªèl»è
    char  	SKTYMD[9];         	//ªèú
	char	DISP_SKTYMD[9];		//óüpªèú
    char  	ADDYMD[9];         	//o^ú
    char  	ADDTIM[5];         	//o^Ô
    char  	UPDYMD[9];         	//ÏXú
    char  	UPDTIM[5];         	//ÏXÔ
    char    UPDCHR[7];         	//XVÒ
    char    UPDCNT[4];         	//XVñ
	char	MEMO[130];			//õl
	long	COLOR;
	char	RESULT[15];         //Ê
	char	DISP_RESULT[15];    //óüpªèl
	double  MAX;
	double	MIN;
	char	SOZAI_LOTNO[7];		//fÞpbg
    int 	JUDGE;				// 0:OK,1:NG,2:O©¢vª
    int 	DISP_JUDGE;			// 0:OK,1:NG,2:O©¢vª
    char    UPDNAME[50];        //\¦pXVÒl[	//2003.05.17 E.Takase Add
    bool    INS_ON;
	double  GMAX;
	double	GMIN;

    char  	HINBAN[9];         	//HÇ­sú
    char  	KOKBNG[7];         	//HÇÔ
};

struct GRAPH_DATA {       		//»iKi¾×}X^[
    char	DTKSHIN[21];        //¾ÓæiÔ
    char    REVCNT[5];         	//üùÔ
    char    UNQ_NO[5];         	//¾×NO
    char    ORDER_NO[5];       	//\¦Eóü
    char    SKB_NO[2];         	//¯ÊNO
    char  	HINBAN_SK[21];      //iÔ
    char    KOMK_NO[5];        	//ªèÚNO
    char  	KOMK_NM[41];        //ªèÚ¼Ì
    char  	KOMK_ENG[41];       //ªèÚ¼Ìipêj
    char  	KOMK_SUB[21];       //ªèÚTu¼Ì
    char  	KOMK_SUB_ENG[21];   //ªèÚTu¼Ìipêj
    char    KIKI_NO[3];        	//ªè@íNO
    char  	KIKI_NM[41];        //ªè@í¼Ì
    char  	TANI[21];           //PÊ
    char    KIKA_TYPE[2];      	//Ki^Cv
    char    KIKA_KIND[2];      	//KiíÞ
    char    KIKA_DECI[2];      	//Ki¬_Èº
    char    KIKA_NUM1[13];      //Kil1
    char    KIKA_NUM2[13];      //Kil2
    char    KIKA_NUM3[13];      //Kil3
    char  	KIKA_STR[41];       //Kil¶
    char  	KIKA_SUB1[21];      //KilTu1
    char   	KIKA_SUB2[21];      //KilTu2
    char  	KIKA_SUB3[21];      //KilTu3
    char    SOKU_SU[3];        	//ªèw¦
    char    SOKU_FLG[2];       	//ªèÚÌL³
    char    TOKU_FLG[2];       	//ÁÊÚÌL³
    char    KIKA_PRT[2];       	//ãÀºÀlÌóü
    char    VALUE_TYPE[2];     	//ªèl\»
    char    VALUE_DECI[2];     	//ªèl¬_Èº
	int		GRID_NO;
	double 	MAX;
	double 	MIN;
	double 	GMAX;
	double 	GMIN;
    char    UPDNAME[50];        //\¦pXVÒl[	//2003.05.17 E.Takase Add

    char  	HINBAN[9];         	//HÇ­sú
    char  	KOKBNG[7];         	//HÇÔ
};

struct  BUN_DATA   {          	//ªèÀÑªf[^
    char  	DTKSHIN[21];        //¾ÓæiÔ
    char  	LOTNO[7];          	//bgNo
	char	BNKT_UNQ_NO[5];		//¾×¯ÊÔ
    char  	UNQ_NO[5];         	//fÞpbgNO
    char   	KOMK_NO[5];        	//Þ¿¼Ì
    char   	KOMK_NM[41];        //i¼
    char	KOMK_ENG[41];       //fÞp¾ÓæiÔP
    char  	KOMK_SUB[21];       //fÞp¾ÓæiÔQ
    char  	KOMK_SUB_ENG[21];   //fÞp¾ÓæiÔR
    char    KIKI_NO[3];        	//ªè@íNO
    char  	KIKI_NM[41];        //ªè@í¼Ì
    char  	TANI[21];           //PÊ
    char   	KIKA_TYPE[2];      	//Ki^Cv
    char   	KIKA_KIND[2];      	//KiíÞ
    char   	KIKA_DECI[2];      	//Ki¬_Èº
    char    KIKA_NUM1[13];      //KilP
    char    KIKA_NUM2[13];      //KilQ
    char    KIKA_NUM3[13];      //KilR
    char  	KIKA_STR[41];       //Kil¶
    char  	KIKA_SUB1[21];      //KilTuP
    char   	KIKA_SUB2[21];      //KilTuQ
    char   	KIKA_SUB3[21];      //KilTuR
    char    SOKU_SU[3];        	//ªèw¦
    char   	SOKU_FLG[2];       	//ªèÚÌL³
    char    TOKU_FLG[2];       	//ÁÊÚÌL³
    char    KIKA_PRT[2];       	//ãÀºÀlÌóü
    char    VALUE_TYPE[2];     	//ªèl\»
    char    VALUE_DECI[2];     	//ªèl¬_Èº
	char	SOKU_VAL[99][16];
    char    SOKU_VAL_SU[3];    	//ªèÀÑ
    char    SOKU_VAL_AVE[16];   //ªè½Ïl
    char    SOKU_VAL_MAX[15];   //ªèÅål
    char    SOKU_VAL_MIN[15];   //ªèÅ¬l
    char    SOKU_OK[4];        	//ªèl»è
    char  	SKTYMD[9];         	//ªèú
    char  	ADDYMD[9];         	//o^ú
    char  	ADDTIM[5];         	//o^Ô
    char  	UPDYMD[9];         	//ÏXú
    char  	UPDTIM[5];         	//ÏXÔ
    char    UPDCHR[7];         	//SÒR[h
    char    UPDCNT[4];         	//XVñ
	char 	UPD_NAME[50];		//SÒ¼	//2003.05.17 E.Takase Add
	int		COL;
	int		ROW;
	double	MAX;
	double	MIN;

    char  	HINBAN[9];         	//HÇ­sú
    char  	KOKBNG[7];         	//HÇÔ
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
extern int     KENSAKU_Mode;           //êõ[h
                                       //PF¸\èú
                                       //QF¾ÓæiÔ
                                       //RFbgNO

//extern KDB1_DATA Tmp_KDB1;             // Iðµ½Hö\Í
//extern KDB1_DATA Cur_Kdb1;             // Iðµ½qXgOf[^

extern double E_Screen_Data[3][20];

extern int E_Scale;

extern int KEIJKBN_KM02;                //KM02Ì»iKiÌ`óæª
extern int LD_HP_TAN_KM02;                //KM02Ì»iKiÌ`óæª
extern int MAGE_TAN_KM02;                //KM02Ì»iKiÌ`óæª

extern RSCOM RS232;
extern KIKAKU KIKAKU_MOJI;

extern HANDLE hSOZAI_RIREKI_DATA;		//fÞðf[^
extern HANDLE hSOZAI_SYUKA_DATA; 		//fÞo×pf[^
extern HANDLE hSOZAI_OR_DATA;    		//fÞORf[^
extern HANDLE hRIREKI_DATA;      		// ßðÎÛbgf[^
extern HANDLE hSYUKA_DATA;       		// o×pf[^
extern HANDLE hORDATA;           		//o×ORf[^
extern HANDLE hRIREKI_DATA;       		// ßðÎÛbgõp
extern HANDLE hSOZAI_RIREKI_LOT; 		// ßðÎÛbgõp
extern HANDLE hKSM01_DATA;

extern KSM01_DATA 	pKSM01_DATA;
extern KSM02_DATA 	pORDATA[100];
extern KSM02_DATA   pSOZAI_OR_DATA[100];

extern GRAPHADDRESS GraphLotAddress[10];	//Ot`æÎÛ

//ªèÀÑf[^p
extern HANDLE 		hRIRE_KSD01DATA;
extern KSD01_DATA 	*pRIRE_KSD01DATA;
extern HANDLE 		hSOKU_KSD01DATA;
extern KSD01_DATA 	*pSOKU_KSD01DATA;



extern HANDLE 		hKSD01_DATA;
extern KSD01_DATA 	*pKSD01_DATA;

//Zîñ
extern HANDLE hCELLINFO_SOKU_SYUKA;
extern HANDLE hCELLINFO_RIRE_SYUKA;
extern HANDLE hCELLINFO_SOKU_SOZAI;
extern HANDLE hCELLINFO_RIRE_SOZAI;
extern CELLINFO_DATA *pCELLINFO_SOKU_SYUKA;
extern CELLINFO_DATA *pCELLINFO_RIRE_SYUKA;
extern CELLINFO_DATA *pCELLINFO_SOKU_SOZAI;
extern CELLINFO_DATA *pCELLINFO_RIRE_SOZAI;
//ªf[^
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
//ªè@íJ[ê
//KIKI_NO = 1 }CN[^
#define MICROMETER_COLOR  0x009FFDD2
//KIKI_NO = 2 mMX
#define NOGISU_COLOR      0x001FFA97
//KIKI_NO = 3 }CN[^V
#define MICROTENBIN_COLOR 0x0004DD7B
//KIKI_NO = 4 V
#define TENBIN_COLOR      0x00EAF7AC
//KIKI_NO = 5 Þ¿±@
#define ZAIRYOU_COLOR     0x00FFEEDD
//KIKI_NO = 6 e@
#define TOUEIKI_COLOR     0x00D2D2FF
//KIKI_NO = 7 °÷¾
#define KENBIKYO_COLOR    0x00ACACFF
//KIKI_NO = 8 Êev
#define MENARAKEI_COLOR   0x00D9D9D9
//KIKI_NO = 9 dxvC
#define KOUDOKEI_C_COLOR  0x00AAD5FF
//KIKI_NO = 10 dxvD
#define KOUDOKEI_D_COLOR  0x0080BFFF
//KIKI_NO = 11 ïR¦ªèí
#define TEIKOU_COLOR      0x00FED1C9
//KIKI_NO = 12 [hüïR¦ªèí
#define READTEIKOU_COLOR  0x00FEB8AB
//KIKI_NO = 99 »Ì¼
#define ETC_COLOR         0x00F3F3F3

