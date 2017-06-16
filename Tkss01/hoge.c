void __fastcall TForm1::Set_Ins_Disp(void)
{
    //double dMAX,dMIN;
	//int i01,i02,i03,i04;
    //KSM02_DATA RIREKI_SWAP;
    //int iRireCnt,iSyukaCnt;
    //int iSyukaWait,iRireWait;
    //char cFormatBuf[20],c1[20],c2[10];
    //int iRow,iKikiNum;
    //int iCel;
	int i1,i2,i3,i4,iCol;
    int iPanelNum,iSokuGoukei;
    int iSokuCnt;
    int iPutKiki;
    AnsiString sBuf,sLot,sTempBuf,sBuf1;
     int nDRAW_GRID;
	double dMAX,dMIN;					//規格ソートに使用
	extern int iKikiCnt;
//ORテーブル作成用
	AnsiString KOMK_NM,KOMK_SUB,HINBAN_SK,TANI;
    AnsiString KIKI_NO,KOMK_NO,SOKU_SU,SKB_NO;

    iSokuGoukei = 0;
//動的コントロールの開放
//2003.05.15　M.HIRAI　関数化
    DynamicCtrl_Free();

/* k.y 2003.05.17
	// メモリの開放
	if( hOldInfoGlaph ){
        GlobalUnlock( hOldInfoGlaph );
        GlobalFree( hOldInfoGlaph );
    }
    hOldInfoGlaph = NULL;
    // メモリの確保
    hOldInfoGlaph = GlobalAlloc( GHND, sizeof(struct GRAPH_DATA) * 1 );
    if( hOldInfoGlaph == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        SBr1->Update();
        Beep();
        return;
    }
    pOldInfoGlaph = (struct GRAPH_DATA *)GlobalLock(hOldInfoGlaph);
    if( hOldInfoGlaph == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        SBr1->Update();
        Beep();
        return;
    }
*/
    memset(&pOldInfoGlaph,(int)NULL,sizeof(pOldInfoGlaph));

//抽出ロットのｎ数のMAX値の抽出                      
//	履歴ロットの描画
	for( i1 = 0;i1 < Form1->iRIRE_CNT ; i1++)
	{
		Form1->SGr_tRIRE->Cells[i1][0] = Form1->sRIREKI_LOT->Strings[i1];
	}

    iRIREKI_KOMKCNT = 0;

	sLot = "";
	for(i1 = 0; i1 < SGr_tSOKU->ColCount ; i1++)
	{
		sLot += "'" + SGr_tSOKU->Cells[i1][0] + "',";
	}
	//for(i1 = 0; i1 < SGr_tRIRE->ColCount ; i1++)
	//{
	//	sLot += "'" + SGr_tRIRE->Cells[i1][0] + "',";
	//}
    for(i1=0;i1 < Form1->iRIRE_CNT ;i1++ )
    {
        sLot += "'" + Form1->sRIREKI_LOT->Strings[i1] + "',";
    }
    sLot = sLot.SubString(1,sLot.Length()-1);


    SGr_vRIRE_SOZAI->RowCount = 1;
    SGr_vRIRE_SYUKA->RowCount = 1;

    sBuf = "SELECT KIKI_NO, KOMK_NM, KOMK_SUB, KOMK_NO, TANI, MAX(SOKU_SU) AS SOKU_SU_MAX FROM KSD02";
    //2003.05.09 E.Takase Add↓
    sBuf += " WHERE DTKSHIN ='" + sNowDTKSHIN + "'";
    //2003.05.09 E.Takase Add↑
    //2003.05.09 E.Takase Add コメント↓
    //sBuf += " WHERE DTKSHIN ='" + Cmb_DTKSHIN->Text + "'";
    //2003.05.09 E.Takase Add コメント↑
    sBuf += " AND SKB_NO IN ( 2 , 3 )";                        //出荷検査項目、材料証明項目
    sBuf += " AND LOTNO IN (";
    sBuf += sLot;
    sBuf += " )";
    sBuf += " GROUP BY KIKI_NO, KOMK_NM, KOMK_SUB, KOMK_NO, TANI";
    sBuf += " ORDER BY KIKI_NO, KOMK_NM, KOMK_SUB, KOMK_NO, TANI";

//履歴データ格納用メモリの宣言

/* k.y 2003.05.17
	// メモリの開放
		if( hRIREKI_DATA ){
        	GlobalUnlock( hRIREKI_DATA );
        	GlobalFree( hRIREKI_DATA );
    	}
        hRIREKI_DATA = NULL;

    // メモリの確保
    	hRIREKI_DATA = GlobalAlloc( GHND, sizeof(struct KSD02_DATA) * (100 ) );
    	if( hRIREKI_DATA == NULL ){
        	SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        	SBr1->Update();
        	Beep();
        	return;
    	}
    	pRIREKI_DATA = (struct KSD02_DATA *)GlobalLock(hRIREKI_DATA);
    	if( hRIREKI_DATA == NULL ){
        	SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        	SBr1->Update();
        	Beep();
        	return;
    	}
*/
    memset(&pRIREKI_DATA,(int)NULL,sizeof(pRIREKI_DATA));

//For Debug
    // 2003.06.03 k.y
    if( iDEBUG == 1 )
    {
        ClpBrd = Clipboard();
        ClpBrd->Open();
        ClpBrd->SetTextBuf(sBuf.c_str());
        ClpBrd->Close();
    }
// Initial Query
    Query1->Close();
    Query1->SQL->Clear();
    Query1->SQL->Add(sBuf);
    Query1->Open();
    Query1->Active = true;

//対象過去履歴の検索　STEP1

		while( Query1->Eof != true )
        {
            if ( VarIsNull(Query1->FieldValues["SOKU_SU_MAX"]) != true)
            {
            	sBuf = Query1->FieldValues["SOKU_SU_MAX"];
            	strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT].SOKU_SU 	,sBuf.c_str());
			}
            if ( VarIsNull(Query1->FieldValues["KIKI_NO"]) != true)
            {
	            sBuf = Query1->FieldValues["KIKI_NO"];
            	strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT].KIKI_NO 	,sBuf.c_str());
			}
            if ( VarIsNull(Query1->FieldValues["KOMK_NM"]) != true)
            {
	            sBuf = Query1->FieldValues["KOMK_NM"];
    	        strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT].KOMK_NM 	,sBuf.c_str());
            }
            if ( VarIsNull(Query1->FieldValues["KOMK_SUB"]) != true)
            {
				sBuf = Query1->FieldValues["KOMK_SUB"];
                strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT].KOMK_SUB	,sBuf.c_str());
            }
            if ( VarIsNull(Query1->FieldValues["KOMK_NO"]) != true)
            {
				sBuf = Query1->FieldValues["KOMK_NO"];
                strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT].KOMK_NO	,sBuf.c_str());
            }
            if ( VarIsNull(Query1->FieldValues["TANI"]) != true)
            {
				sBuf = Query1->FieldValues["TANI"];
                strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT].TANI		,sBuf.c_str());
            }
            iRIREKI_KOMKCNT ++;                                              //項目数
            Query1->Next();
        }
        Query1->Close();
	//}
//現在の出荷用の項目と過去履歴の項目の最大数のORを別メモリ上へ格納
	//iRireCnt = 0;
    //iSyukaCnt = 0;
    	iOrCnt = 0;

/* k.y 2003.05.17
	// メモリの開放
		if( hTEMPORDATA ){
    	    GlobalUnlock( hTEMPORDATA );
        	GlobalFree( hTEMPORDATA );
	    }
        hTEMPORDATA = NULL;

    // メモリの確保
	    hTEMPORDATA = GlobalAlloc( GHND, sizeof(struct KSM02_DATA) * (100) );
    	if( hTEMPORDATA == NULL ){
        	SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
	        SBr1->Update();
    	    Beep();
        	return;
	    }
    	pTEMPORDATA = (struct KSM02_DATA *)GlobalLock(hTEMPORDATA);
	    if( hTEMPORDATA == NULL ){
    	    SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        	SBr1->Update();
	        Beep();
    	    return;
	    }
*/
        memset(pTEMPORDATA,0x00,sizeof(pTEMPORDATA));

//ORテーブル作成　Part1
bool bALL_RIRE_DATA;				//履歴データフラグ
bALL_RIRE_DATA = ALL_RIRE_DATA();

		if(!bALL_RIRE_DATA)
        {
    	for(i1 = 0;i1 < iSYUKA_KOMKCNT;i1++)
	    {
    		KOMK_NM 	= pSYUKA_DATA[i1].KOMK_NM;
	        KOMK_SUB 	= pSYUKA_DATA[i1].KOMK_SUB;
	        TANI 		= pSYUKA_DATA[i1].TANI;
    	    HINBAN_SK 	= pSYUKA_DATA[i1].HINBAN_SK;
	        KOMK_NO 	= AnsiString(pSYUKA_DATA[i1].KOMK_NO).ToIntDef(0);
    	    KIKI_NO 	= AnsiString(pSYUKA_DATA[i1].KIKI_NO).ToIntDef(0);
        	SOKU_SU 	= AnsiString(pSYUKA_DATA[i1].SOKU_SU).ToIntDef(0);
	        for( i2 = 0;i2 < iRIREKI_KOMKCNT ; i2++)
    	    {
        		if(AnsiString(pRIREKI_DATA[i2].KIKI_NO).ToIntDef(0) != 9999)
	            {
    	        	if((KOMK_NM 			== AnsiString(pRIREKI_DATA[i2].KOMK_NM))
        	        &&(KOMK_SUB 			== AnsiString(pRIREKI_DATA[i2].KOMK_SUB))
        	        &&(TANI 				== AnsiString(pRIREKI_DATA[i2].TANI))
            	    &&(KOMK_NO.ToIntDef(0) 	== AnsiString(pRIREKI_DATA[i2].KOMK_NO).ToIntDef(0))
                	&&(KIKI_NO.ToIntDef(0) 	== AnsiString(pRIREKI_DATA[i2].KIKI_NO).ToIntDef(0)))
	                {
    	            	if(SOKU_SU.ToIntDef(0) <  AnsiString(pRIREKI_DATA[i2].SOKU_SU).ToIntDef(0))
        	            {
            	        	SOKU_SU = AnsiString(pRIREKI_DATA[i2].SOKU_SU).ToIntDef(0);
                	    }
	                    strcpy(pRIREKI_DATA[i2].KIKI_NO,"9999");
                    }
	            }
    	    }
            strcpy(pTEMPORDATA[iOrCnt].KIKI_NO	,KIKI_NO.c_str());
            strcpy(pTEMPORDATA[iOrCnt].KOMK_NM	,KOMK_NM.c_str());
            strcpy(pTEMPORDATA[iOrCnt].KOMK_NO	,KOMK_NO.c_str());
            strcpy(pTEMPORDATA[iOrCnt].KOMK_SUB	,KOMK_SUB.c_str());
            strcpy(pTEMPORDATA[iOrCnt].TANI		,TANI.c_str());
            strcpy(pTEMPORDATA[iOrCnt].SOKU_SU	,SOKU_SU.c_str());
            strcpy(pTEMPORDATA[iOrCnt].HINBAN_SK	,HINBAN_SK.c_str());
            iOrCnt++;
    	}
		}
	    for( i1 = 0;i1 < iRIREKI_KOMKCNT ; i1++)
    	{
    		if(AnsiString(pRIREKI_DATA[i1].KIKI_NO).ToIntDef(0) != 9999)
	        {
    	    	KOMK_NM = pRIREKI_DATA[i1].KOMK_NM;
        	    KOMK_SUB =pRIREKI_DATA[i1].KOMK_SUB;
        	    TANI =pRIREKI_DATA[i1].TANI;
            	HINBAN_SK =pRIREKI_DATA[i1].HINBAN_SK;
	            KOMK_NO = AnsiString(pRIREKI_DATA[i1].KOMK_NO).ToIntDef(0);
    	        KIKI_NO = AnsiString(pRIREKI_DATA[i1].KIKI_NO).ToIntDef(0);
        	    SOKU_SU = AnsiString(pRIREKI_DATA[i1].SOKU_SU).ToIntDef(0);

	            strcpy(pTEMPORDATA[iOrCnt].KIKI_NO	,KIKI_NO.c_str());
    	        strcpy(pTEMPORDATA[iOrCnt].KOMK_NM	,KOMK_NM.c_str());
        	    strcpy(pTEMPORDATA[iOrCnt].KOMK_NO	,KOMK_NO.c_str());
            	strcpy(pTEMPORDATA[iOrCnt].KOMK_SUB	,KOMK_SUB.c_str());
            	strcpy(pTEMPORDATA[iOrCnt].TANI		,TANI.c_str());
	            strcpy(pTEMPORDATA[iOrCnt].SOKU_SU	,SOKU_SU.c_str());
    	        strcpy(pTEMPORDATA[iOrCnt].HINBAN_SK,HINBAN_SK.c_str());
        	    iOrCnt++;
	        }
    	}

// ---------------------------------------------------------
//現在の出荷用の項目と測定実績の項目の最大数のORを別メモリ上へ格納
//測定実績読み取り
//抽出ロットのｎ数のMAX値の抽出
/* k.y 2003.05.17
    // メモリの開放
    if( hRIREKI_DATA ){
        GlobalUnlock( hRIREKI_DATA );
        GlobalFree( hRIREKI_DATA );
    }
    hRIREKI_DATA = NULL;

    // メモリの確保
    hRIREKI_DATA = GlobalAlloc( GHND, sizeof(struct KSD02_DATA) * (100*100) );
    if( hRIREKI_DATA == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        SBr1->Update();
        Beep();
        return;
    }
    pRIREKI_DATA = (struct KSD02_DATA *)GlobalLock(hRIREKI_DATA);
    if( hRIREKI_DATA == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        SBr1->Update();
        Beep();
        return;
    }
*/
    memset(pRIREKI_DATA,0x00,sizeof(pRIREKI_DATA));

	int iRIREKI_KOMKCNT2;
	iRIREKI_KOMKCNT2 = 0;
	sLot ="";
	for(i1 = 0;i1 <= SGr_tRIRE->ColCount ; i1++)
	{
    	if(SGr_tRIRE->Cells[i1][0].Trim().Length() != 0)
		{
			sLot += "'" + SGr_tRIRE->Cells[i1][0] + "'" + ",";
		}
	}
	//for(i1 = 0;i1 < SGr_tSOKU->ColCount ; i1++)
	//{
    //	if(SGr_tSOKU->Cells[i1][0].Trim().Length() != 0)
	//	{
	//		sLot += "'" + SGr_tSOKU->Cells[i1][0] + "'" + ",";
	//	}
	//}
	sLot = sLot.SubString(1,sLot.Length()-1);

    if( sLot > 3 )          //ロットがあれば
    {
        SGr_vRIRE_SOZAI->RowCount = 1;
        SGr_vRIRE_SYUKA->RowCount = 1;

        sBuf  = "SELECT KIKI_NO, KOMK_NM, KOMK_SUB, TANI, KOMK_NO,";
		sBuf += " MAX(SOKU_SU) AS SOKU_SU_MAX FROM KSD02";
		//2003.05.09 E.Takase Add↓
        sBuf += " WHERE DTKSHIN ='" + sNowDTKSHIN + "'";
		//2003.05.09 E.Takase Add↑
		//2003.05.09 E.Takase Add コメント↓
        //sBuf += " WHERE DTKSHIN ='" + Cmb_DTKSHIN->Text + "'";
		//2003.05.09 E.Takase Add コメント↑
        sBuf += " AND (SKB_NO = 2 OR SKB_NO = 3 )";                        //出荷検査項目、材料証明項目
        sBuf += " AND LOTNO IN (" + sLot + ")";
        sBuf += " GROUP BY KIKI_NO, KOMK_NM, KOMK_SUB, TANI, KOMK_NO";
        sBuf += " ORDER BY KIKI_NO, KOMK_NM, KOMK_SUB, TANI, KOMK_NO";

//For Debug
    // 2003.06.03 k.y
    if( iDEBUG == 1 )
    {
        ClpBrd = Clipboard();
        ClpBrd->Open();
        ClpBrd->SetTextBuf(sBuf.c_str());
        ClpBrd->Close();
    }
// Initial Query
        Query1->Close();
        Query1->SQL->Clear();
        Query1->SQL->Add(sBuf);
        Query1->Open();
        Query1->Active = true;
//出荷検査ロット中で検査済みロットの検索
		while( Query1->Eof == false )
    	{
    		sBuf = Query1->FieldValues["SOKU_SU_MAX"];
        	strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT2].SOKU_SU		,sBuf.c_str());

        	sBuf = Query1->FieldValues["KIKI_NO"];
        	strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT2].KIKI_NO		,sBuf.c_str());

        	strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT2].KOMK_NM 		,"");
        	if ( VarIsNull(Query1->FieldValues["KOMK_NM"]) != true
        	&& VarIsEmpty(Query1->FieldValues["KOMK_NM"]) != true )
        	{
        		sBuf = Query1->FieldValues["KOMK_NM"];
        		strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT2].KOMK_NM 		,sBuf.c_str());
			}
        	strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT2].KOMK_SUB 		,"");
        	if ( VarIsNull(Query1->FieldValues["KOMK_SUB"]) != true
        	&& VarIsEmpty(Query1->FieldValues["KOMK_SUB"]) != true )
        	{
        		sBuf = Query1->FieldValues["KOMK_SUB"];
            	strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT2].KOMK_SUB	,sBuf.c_str());
        	}
        	strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT2].TANI 		,"");
        	if ( VarIsNull(Query1->FieldValues["TANI"]) != true
        	&& VarIsEmpty(Query1->FieldValues["TANI"]) != true )
        	{
        		sBuf = Query1->FieldValues["TANI"];
            	strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT2].TANI	,sBuf.c_str());
        	}
            if ( VarIsNull(Query1->FieldValues["KOMK_NO"]) != true)
            {
				sBuf = Query1->FieldValues["KOMK_NO"];
                strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT2].KOMK_NO	,sBuf.c_str());
            }
        	iRIREKI_KOMKCNT2 ++;                                              //項目数
        	Query1->Next();
    	}
    	Query1->Close();
    }

/* k.y 2003.05.17
    // メモリの開放
    if( hORDATA ){
        GlobalUnlock( hORDATA );
        GlobalFree( hORDATA );
    }
    hORDATA = NULL;
    // メモリの確保
    hORDATA = GlobalAlloc( GHND, sizeof(struct KSM02_DATA) * (100) );
    if( hORDATA == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        SBr1->Update();
        Beep();
        return;
    }
    pORDATA = (struct KSM02_DATA *)GlobalLock(hORDATA);
    if( hORDATA == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        SBr1->Update();
        Beep();
        return;
    }
*/
    memset(pORDATA,0x00,sizeof(pORDATA));

    iOrCnt2	 	= 0;
    //iRireCnt 	= 0;
    iSyukaCnt2 	= 0;

//ORデータ作成Part2
    for(i1 = 0;i1 < iOrCnt;i1++)
    {
    	KOMK_NM 	= pTEMPORDATA[i1].KOMK_NM;
        KOMK_SUB 	= pTEMPORDATA[i1].KOMK_SUB;
        TANI 		= pTEMPORDATA[i1].TANI;
        HINBAN_SK 	= pTEMPORDATA[i1].HINBAN_SK;
        KOMK_NO 	= AnsiString(pTEMPORDATA[i1].KOMK_NO).ToIntDef(0);
        KIKI_NO 	= AnsiString(pTEMPORDATA[i1].KIKI_NO).ToIntDef(0);
        SOKU_SU 	= AnsiString(pTEMPORDATA[i1].SOKU_SU).ToIntDef(0);
        for( i2 = 0;i2 < iRIREKI_KOMKCNT2 ; i2++)
        {
        	if(AnsiString(pRIREKI_DATA[i2].KIKI_NO).ToIntDef(0) != 9999)
            {
            	if((KOMK_NM 			== AnsiString(pRIREKI_DATA[i2].KOMK_NM))
                &&(KOMK_SUB 			== AnsiString(pRIREKI_DATA[i2].KOMK_SUB))
                &&(TANI 				== AnsiString(pRIREKI_DATA[i2].TANI))
                &&(KOMK_NO.ToIntDef(0) 	== AnsiString(pRIREKI_DATA[i2].KOMK_NO).ToIntDef(0))
                &&(KIKI_NO.ToIntDef(0) 	== AnsiString(pRIREKI_DATA[i2].KIKI_NO).ToIntDef(0)))
                {
                	if(SOKU_SU.ToIntDef(0) <  AnsiString(pRIREKI_DATA[i2].SOKU_SU).ToIntDef(0))
                    {
                    	SOKU_SU = AnsiString(pRIREKI_DATA[i2].SOKU_SU).ToIntDef(0);
                    }
                    strcpy(pRIREKI_DATA[i2].KIKI_NO,"9999");
                }
            }
        }
        strcpy(pORDATA[iOrCnt2].KIKI_NO	,KIKI_NO.c_str());
        strcpy(pORDATA[iOrCnt2].KOMK_NM	,KOMK_NM.c_str());
        strcpy(pORDATA[iOrCnt2].KOMK_NO	,KOMK_NO.c_str());
        strcpy(pORDATA[iOrCnt2].KOMK_SUB,KOMK_SUB.c_str());
        strcpy(pORDATA[iOrCnt2].TANI	,TANI.c_str());
        strcpy(pORDATA[iOrCnt2].SOKU_SU	,SOKU_SU.c_str());
        strcpy(pORDATA[iOrCnt2].HINBAN_SK,HINBAN_SK.c_str());
        iOrCnt2++;
    }
    for( i1 = 0;i1 < iRIREKI_KOMKCNT2 ; i1++)
    {
    	if(AnsiString(pRIREKI_DATA[i1].KIKI_NO).ToIntDef(0) != 9999)
        {
        	KOMK_NM 	= pRIREKI_DATA[i1].KOMK_NM;
            KOMK_SUB	= pRIREKI_DATA[i1].KOMK_SUB;
            TANI 		= pRIREKI_DATA[i1].TANI;
            HINBAN_SK	= pRIREKI_DATA[i1].HINBAN_SK;
            KOMK_NO		= AnsiString(pRIREKI_DATA[i1].KOMK_NO).ToIntDef(0);
            KIKI_NO		= AnsiString(pRIREKI_DATA[i1].KIKI_NO).ToIntDef(0);
            SOKU_SU		= AnsiString(pRIREKI_DATA[i1].SOKU_SU).ToIntDef(0);

            strcpy(pORDATA[iOrCnt2].KIKI_NO	,KIKI_NO.c_str());
            strcpy(pORDATA[iOrCnt2].KOMK_NM	,KOMK_NM.c_str());
            strcpy(pORDATA[iOrCnt2].KOMK_NO	,KOMK_NO.c_str());
            strcpy(pORDATA[iOrCnt2].KOMK_SUB,KOMK_SUB.c_str());
            strcpy(pORDATA[iOrCnt2].TANI	,TANI.c_str());
            strcpy(pORDATA[iOrCnt2].SOKU_SU	,SOKU_SU.c_str());
            strcpy(pORDATA[iOrCnt2].HINBAN_SK	,HINBAN_SK.c_str());
            iOrCnt2++;
        }
    }
	iOrCnt = iOrCnt2;

/* k.y 2003.05.17
    // メモリの開放
    if( hRIREKI_DATA ){
        GlobalUnlock( hRIREKI_DATA );
        hRIREKI_DATA = GlobalFree( hRIREKI_DATA );
    }
    // メモリの開放
    if( hTEMPORDATA ){
        GlobalUnlock( hTEMPORDATA );
        hTEMPORDATA = GlobalFree( hTEMPORDATA );
    }
*/

// ---------------------------------------------------------


//総ｎ数の算出
    iSokuCnt = 0;
    for(i1=0;i1<iOrCnt;i1++)
    {
		sBuf = pORDATA[i1].SOKU_SU;
        iSokuCnt += sBuf.ToIntDef(0);
    }

//測定機器名称、項目名称、単位、規格の抽出（最新のものを表示する）
    for(i1=0;i1<iOrCnt;i1++)
    {
        //マスターから読み込み
        sBuf = "SELECT * FROM KSM02";
		//2003.05.09 E.Takase Add↓
        sBuf += " WHERE DTKSHIN ='" + sNowDTKSHIN + "'";
		//2003.05.09 E.Takase Add↑
		//2003.05.09 E.Takase Add コメント↓
        //sBuf += " WHERE DTKSHIN ='" + Cmb_DTKSHIN->Text + "'";
		//2003.05.09 E.Takase Add コメント↑
        sBuf += " AND KIKI_NO = " + AnsiString(pORDATA[i1].KIKI_NO);
        if(AnsiString(pORDATA[i1].KOMK_NM).Length() != 0)
        {
            sBuf += " AND KOMK_NM ='"  + AnsiString(pORDATA[i1].KOMK_NM) + "'";
        }
        else
        {
            sBuf += " AND KOMK_NM IS NULL";
        }
        if(AnsiString(pORDATA[i1].KOMK_SUB).Length() != 0)
        {
            sBuf += " AND KOMK_SUB ='"  + AnsiString(pORDATA[i1].KOMK_SUB) + "'";
        }
        else
        {
            sBuf += " AND KOMK_SUB IS NULL";
        }
        if(AnsiString(pORDATA[i1].TANI).Length() != 0)
        {
            sBuf += " AND TANI ='"  + AnsiString(pORDATA[i1].TANI) + "'";
        }
        else
        {
            sBuf += " AND TANI IS NULL";
        }
		sBuf += " AND REVCNT = 0";
        sBuf += " AND (SKB_NO = 2 OR SKB_NO = 3)";                        //出荷検査項目、材料証明項目

//For Debug
        // 2003.06.03 k.y
        if( iDEBUG == 1 )
        {
     	    ClpBrd = Clipboard();
     	    ClpBrd->Open();
     	    ClpBrd->SetTextBuf(sBuf.c_str());
     	    ClpBrd->Close();
        }
// Initial Query
        Query1->Close();
        Query1->SQL->Clear();
        Query1->SQL->Add(sBuf);
        Query1->Open();
        Query1->Active = true;
        if( Query1->Eof == false )
        {

            strcpy(pORDATA[i1].DTKSHIN		,"");
        	if ( VarIsNull(Query1->FieldValues["DTKSHIN"]) != true )
            {
	        	sBuf 		= Query1->FieldValues["DTKSHIN"];		//得意先品番
    	    	strcpy(pORDATA[i1].DTKSHIN		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].REVCNT		,"");
        	if ( VarIsNull(Query1->FieldValues["REVCNT"]) != true  )
            {
        		sBuf 		= Query1->FieldValues["REVCNT"];      	//改訂番号
        		strcpy(pORDATA[i1].REVCNT		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].UNQ_NO		,"");
        	if ( VarIsNull(Query1->FieldValues["UNQ_NO"]) != true  )
            {
	        	sBuf 		= Query1->FieldValues["UNQ_NO"];    		//明細NO
    	    	strcpy(pORDATA[i1].UNQ_NO		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].ORDER_NO		,"");
        	if ( VarIsNull(Query1->FieldValues["ORDER_NO"]) != true )
            {
        		sBuf 		= Query1->FieldValues["ORDER_NO"];  		//表示・印刷順
        		strcpy(pORDATA[i1].ORDER_NO		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].SKB_NO		,"");
        	if ( VarIsNull(Query1->FieldValues["SKB_NO"]) != true   )
            {
	        	sBuf 		= Query1->FieldValues["SKB_NO"];    		//識別NO
    	    	strcpy(pORDATA[i1].SKB_NO		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].HINBAN_SK		,"");
        	if ( VarIsNull(Query1->FieldValues["HINBAN_SK"]) != true)
            {
        		sBuf 		= Query1->FieldValues["HINBAN_SK"];  	//品番
        		strcpy(pORDATA[i1].HINBAN_SK		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KOMK_NO		,"");
        	if ( VarIsNull(Query1->FieldValues["KOMK_NO"]) != true  )
            {
	        	sBuf 		= Query1->FieldValues["KOMK_NO"];   		//測定項目NO
    	    	strcpy(pORDATA[i1].KOMK_NO		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KOMK_NM		,"");
        	if ( VarIsNull(Query1->FieldValues["KOMK_NM"]) != true  )
            {
				sBuf 		= Query1->FieldValues["KOMK_NM"];  		//測定項目名称
				strcpy(pORDATA[i1].KOMK_NM		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KOMK_ENG		,"");
        	if ( VarIsNull(Query1->FieldValues["KOMK_ENG"]) != true )
            {
				sBuf 		= Query1->FieldValues["KOMK_ENG"]; 		//測定項目名称（英語）
				strcpy(pORDATA[i1].KOMK_ENG		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KOMK_SUB		,"");
        	if ( VarIsNull(Query1->FieldValues["KOMK_SUB"]) != true )
            {
				sBuf 		= Query1->FieldValues["KOMK_SUB"];   	//測定項目サブ名称
				strcpy(pORDATA[i1].KOMK_SUB		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KOMK_SUB_ENG		,"");
        	if ( VarIsNull(Query1->FieldValues["KOMK_SUB_ENG"]) != true )
            {
				sBuf 		= Query1->FieldValues["KOMK_SUB_ENG"];	//測定項目サブ名称（英語）
				strcpy(pORDATA[i1].KOMK_SUB_ENG		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKI_NO		,"");
			if ( VarIsNull(Query1->FieldValues["KIKI_NO"]) != true )
            {
				sBuf 		= Query1->FieldValues["KIKI_NO"];     	//測定機器NO
				strcpy(pORDATA[i1].KIKI_NO		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKI_NM		,"");
			if ( VarIsNull(Query1->FieldValues["KIKI_NM"]) != true )
            {
				sBuf 		= Query1->FieldValues["KIKI_NM"];  		//測定機器名称
				strcpy(pORDATA[i1].KIKI_NM		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].TANI		,"");
			if ( VarIsNull(Query1->FieldValues["TANI"]) != true    )
            {
            	sBuf 		= Query1->FieldValues["TANI"];         	//単位
            	strcpy(pORDATA[i1].TANI			,sBuf.c_str());
   			}
            strcpy(pORDATA[i1].KIKA_TYPE		,"");
           	if ( VarIsNull(Query1->FieldValues["KIKA_TYPE"]) != true )
            {
            	sBuf 	= Query1->FieldValues["KIKA_TYPE"];      	//規格タイプ
            	strcpy(pORDATA[i1].KIKA_TYPE	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_KIND		,"");
			if ( VarIsNull(Query1->FieldValues["KIKA_KIND"]) != true )
            {
            	sBuf 	= Query1->FieldValues["KIKA_KIND"];        	//規格種類
            	strcpy(pORDATA[i1].KIKA_KIND	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_DECI		,"");
			if ( VarIsNull(Query1->FieldValues["KIKA_DECI"]) != true )
            {
            	sBuf 	= Query1->FieldValues["KIKA_DECI"];      	//規格小数点以下桁数
            	strcpy(pORDATA[i1].KIKA_DECI	,sBuf.c_str());
			}
            strcpy(pORDATA[i1].KIKA_NUM1		,"");
        	if ( VarIsNull(Query1->FieldValues["KIKA_NUM1"]) != true )
            {
            	sBuf 	= Query1->FieldValues["KIKA_NUM1"];     		//規格値１
            	strcpy(pORDATA[i1].KIKA_NUM1	,sBuf.c_str());
			}
            strcpy(pORDATA[i1].KIKA_NUM2		,"");
        	if ( VarIsNull(Query1->FieldValues["KIKA_NUM2"]) != true )
            {
	            sBuf 	= Query1->FieldValues["KIKA_NUM2"];        	//規格値２
    	        strcpy(pORDATA[i1].KIKA_NUM2	,sBuf.c_str());
			}
            strcpy(pORDATA[i1].KIKA_NUM3		,"");
        	if ( VarIsNull(Query1->FieldValues["KIKA_NUM3"]) != true )
            {
            	sBuf 	= Query1->FieldValues["KIKA_NUM3"];        	//規格値３
            	strcpy(pORDATA[i1].KIKA_NUM3	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_STR		,"");
			if ( VarIsNull(Query1->FieldValues["KIKA_STR"]) != true  )
            {
            	sBuf  	= Query1->FieldValues["KIKA_STR"];        	//規格値文字
            	strcpy(pORDATA[i1].KIKA_STR		,sBuf.c_str());
   			}
            strcpy(pORDATA[i1].KIKA_SUB1		,"");
           	if ( VarIsNull(Query1->FieldValues["KIKA_SUB1"]) != true )
            {
            	sBuf 	= Query1->FieldValues["KIKA_SUB1"];       	//規格値サブ１
            	strcpy(pORDATA[i1].KIKA_SUB1	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_SUB2		,"");
			if ( VarIsNull(Query1->FieldValues["KIKA_SUB2"]) != true )
            {
            	sBuf 	= Query1->FieldValues["KIKA_SUB2"];          //規格値サブ２
            	strcpy(pORDATA[i1].KIKA_SUB2	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_SUB3		,"");
			if ( VarIsNull(Query1->FieldValues["KIKA_SUB3"]) != true )
            {
            	sBuf 	= Query1->FieldValues["KIKA_SUB3"];         	//規格値サブ３
            	strcpy(pORDATA[i1].KIKA_SUB3	,sBuf.c_str());
            }
            //strcpy(pORDATA[i1].SOKU_SU		,"");
			//if ( VarIsNull(Query1->FieldValues["SOKU_SU"]) != true   )
            //{
            // 	sBuf 	= Query1->FieldValues["SOKU_SU"];            //測定指示ｎ数
            //	strcpy(pORDATA[i1].SOKU_SU	,sBuf.c_str());          //測定指示ｎ数は読み込み終了しているので読まない。
            //}
            strcpy(pORDATA[i1].SOKU_FLG		,"");
			if ( VarIsNull(Query1->FieldValues["SOKU_FLG"]) != true  )
            {
             	sBuf 	= Query1->FieldValues["SOKU_FLG"];        	//測定項目の有無
            	strcpy(pORDATA[i1].SOKU_FLG	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].TOKU_FLG		,"");
			if ( VarIsNull(Query1->FieldValues["TOKU_FLG"]) != true  )
            {
             	sBuf 	= Query1->FieldValues["TOKU_FLG"];       	//特別項目の有無
            	strcpy(pORDATA[i1].TOKU_FLG	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_PRT		,"");
			if ( VarIsNull(Query1->FieldValues["KIKA_PRT"]) != true  )
            {
             	sBuf 	= Query1->FieldValues["KIKA_PRT"];     		//上限下限値の印刷
            	strcpy(pORDATA[i1].KIKA_PRT	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].VALUE_TYPE		,"");
            if ( VarIsNull(Query1->FieldValues["VALUE_TYPE"]) != true)
            {
             	sBuf 	= Query1->FieldValues["VALUE_TYPE"];         //測定値表現
            	strcpy(pORDATA[i1].VALUE_TYPE	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].VALUE_DECI		,"");
			if ( VarIsNull(Query1->FieldValues["VALUE_DECI"]) != true)
            {
             	sBuf 	= Query1->FieldValues["VALUE_DECI"];         //測定値小数点以下桁数
            	strcpy(pORDATA[i1].VALUE_DECI	,sBuf.c_str());
			}
        }
        else
        {
			//2003.05.10 E.Takase Add↓
			sBuf  = "SELECT  KSD02.*, SM12S.TANNAM As UPDNAME ";
			sBuf += " FROM KSD02 LEFT JOIN SM12S ON KSD02.UPDCHR = SM12S.TANSYA ";
			//2003.05.10 E.Takase Add↑
			//2003.05.10 E.Takase Add コメント↓
            //sBuf = "SELECT * FROM KSD02";
			//2003.05.10 E.Takase Add コメント↑
			//2003.05.09 E.Takase Add↓
            sBuf += " WHERE DTKSHIN ='" + sNowDTKSHIN + "'";
            //sBuf += " WHERE DTKSHIN IN ('" + sNowDTKSHIN + "')";
			//2003.05.09 E.Takase Add↑
			//2003.05.09 E.Takase Add コメント↓
            //sBuf += " WHERE DTKSHIN IN ('" + Cmb_DTKSHIN->Text + "')";
			//2003.05.09 E.Takase Add コメント↑
            sBuf += " AND KIKI_NO = " + AnsiString(pORDATA[i1].KIKI_NO) ;
            if(AnsiString(pORDATA[i1].KOMK_NM).Length() != 0)
            {
                sBuf += " AND KOMK_NM ='"  + AnsiString(pORDATA[i1].KOMK_NM) + "'";
            }
            else
            {
                sBuf += " AND KOMK_NM IS NULL";
            }
            if(AnsiString(pORDATA[i1].KOMK_SUB).Length() != 0)
            {
                sBuf += " AND KOMK_SUB ='"  + AnsiString(pORDATA[i1].KOMK_SUB) + "'";
            }
            else
            {
                sBuf += " AND KOMK_SUB IS NULL";
            }
            if(AnsiString(pORDATA[i1].TANI).Length() != 0)
            {
                sBuf += " AND TANI ='"  + AnsiString(pORDATA[i1].TANI) + "'";
            }
            else
            {
                sBuf += " AND TANI IS NULL";
            }
            sBuf += " AND SKB_NO IN ( 2 , 3) ";                        //出荷検査項目、材料証明項目
            sBuf += " ORDER BY KSD02.UPDYMD DESC, KSD02.UPDTIM DESC";

		//For Debug
            // 2003.06.03 k.y
            if( iDEBUG == 1 )
            {
        	    ClpBrd = Clipboard();
     		    ClpBrd->Open();
     		    ClpBrd->SetTextBuf(sBuf.c_str());
     		    ClpBrd->Close();
            }
		// Initial Query
            Query1->Close();
            Query1->SQL->Clear();
            Query1->SQL->Add(sBuf);
            Query1->Open();
            Query1->Active = true;
		//履歴読み込み（ＫＳＤ０２）
            if( Query1->Eof == false )
            {
	            strcpy(pORDATA[i1].DTKSHIN		,"");
    	    	if ( VarIsNull(Query1->FieldValues["DTKSHIN"]) != true )
            	{
		        	sBuf 		= Query1->FieldValues["DTKSHIN"];		//得意先品番
    		    	strcpy(pORDATA[i1].DTKSHIN		,sBuf.c_str());
				}
				strcpy(pORDATA[i1].UNQ_NO		,"");
    	    	if ( VarIsNull(Query1->FieldValues["UNQ_NO"]) != true  )
            	{
	        		sBuf 		= Query1->FieldValues["UNQ_NO"];    		//明細NO
    	    		strcpy(pORDATA[i1].UNQ_NO		,sBuf.c_str());
				}
	            strcpy(pORDATA[i1].ORDER_NO		,"");
    	    	if ( VarIsNull(Query1->FieldValues["ORDER_NO"]) != true )
            	{
        			sBuf 		= Query1->FieldValues["ORDER_NO"];  		//表示・印刷順
	        		strcpy(pORDATA[i1].ORDER_NO		,sBuf.c_str());
				}
	            strcpy(pORDATA[i1].SKB_NO		,"");
    	    	if ( VarIsNull(Query1->FieldValues["SKB_NO"]) != true  )
            	{
    	    		sBuf 		= Query1->FieldValues["SKB_NO"];    		//識別NO
        			strcpy(pORDATA[i1].SKB_NO		,sBuf.c_str());
				}
	            strcpy(pORDATA[i1].HINBAN_SK		,"");
    	    	if ( VarIsNull(Query1->FieldValues["HINBAN_SK"]) != true)
            	{
        			sBuf 		= Query1->FieldValues["HINBAN_SK"];  	//品番
	        		strcpy(pORDATA[i1].HINBAN_SK		,sBuf.c_str());
				}
	            strcpy(pORDATA[i1].KOMK_NO		,"");
    	    	if ( VarIsNull(Query1->FieldValues["KOMK_NO"]) != true )
            	{
    	    		sBuf 		= Query1->FieldValues["KOMK_NO"];   		//測定項目NO
        			strcpy(pORDATA[i1].KOMK_NO		,sBuf.c_str());
				}
	            strcpy(pORDATA[i1].KOMK_NM		,"");
    	    	if ( VarIsNull(Query1->FieldValues["KOMK_NM"]) != true )
            	{
					sBuf 		= Query1->FieldValues["KOMK_NM"];  		//測定項目名称
					strcpy(pORDATA[i1].KOMK_NM		,sBuf.c_str());
                }
	            strcpy(pORDATA[i1].KOMK_ENG		,"");
    	    	if ( VarIsNull(Query1->FieldValues["KOMK_ENG"]) != true )
            	{
					sBuf 		= Query1->FieldValues["KOMK_ENG"]; 		//測定項目名称（英語）
					strcpy(pORDATA[i1].KOMK_ENG		,sBuf.c_str());
                }
	            strcpy(pORDATA[i1].KOMK_SUB		,"");
    	    	if ( VarIsNull(Query1->FieldValues["KOMK_SUB"]) != true )
            	{
					sBuf 		= Query1->FieldValues["KOMK_SUB"];   	//測定項目サブ名称
					strcpy(pORDATA[i1].KOMK_SUB		,sBuf.c_str());
    	        }
	            strcpy(pORDATA[i1].KOMK_SUB_ENG		,"");
    	    	if ( VarIsNull(Query1->FieldValues["KOMK_SUB_ENG"]) != true )
            	{
					sBuf 		= Query1->FieldValues["KOMK_SUB_ENG"];	//測定項目サブ名称（英語）
					strcpy(pORDATA[i1].KOMK_SUB_ENG		,sBuf.c_str());
        	    }
	            strcpy(pORDATA[i1].KIKI_NO		,"");
				if ( VarIsNull(Query1->FieldValues["KIKI_NO"]) != true )
	            {
					sBuf 		= Query1->FieldValues["KIKI_NO"];     	//測定機器NO
					strcpy(pORDATA[i1].KIKI_NO		,sBuf.c_str());
	            }
    	        strcpy(pORDATA[i1].KIKI_NM		,"");
				if ( VarIsNull(Query1->FieldValues["KIKI_NM"]) != true )
	            {
					sBuf 		= Query1->FieldValues["KIKI_NM"];  		//測定機器名称
					strcpy(pORDATA[i1].KIKI_NM		,sBuf.c_str());
	            }
    	        strcpy(pORDATA[i1].TANI		,"");
				if ( VarIsNull(Query1->FieldValues["TANI"]) != true )
	            {
    	        	sBuf 		= Query1->FieldValues["TANI"];         	//単位
        	    	strcpy(pORDATA[i1].TANI			,sBuf.c_str());
	   			}
    	        strcpy(pORDATA[i1].KIKA_TYPE		,"");
        	   	if ( VarIsNull(Query1->FieldValues["KIKA_TYPE"]) != true )
	            {
    	        	sBuf 	= Query1->FieldValues["KIKA_TYPE"];      	//規格タイプ
        	    	strcpy(pORDATA[i1].KIKA_TYPE	,sBuf.c_str());
	            }
    	        strcpy(pORDATA[i1].KIKA_KIND		,"");
				if ( VarIsNull(Query1->FieldValues["KIKA_KIND"]) != true )
	            {
    	        	sBuf 	= Query1->FieldValues["KIKA_KIND"];        	//規格種類
        	    	strcpy(pORDATA[i1].KIKA_KIND	,sBuf.c_str());
	            }
    	        strcpy(pORDATA[i1].KIKA_DECI		,"");
				if ( VarIsNull(Query1->FieldValues["KIKA_DECI"]) != true )
	            {
    	        	sBuf 	= Query1->FieldValues["KIKA_DECI"];      	//規格小数点以下桁数
        	    	strcpy(pORDATA[i1].KIKA_DECI	,sBuf.c_str());
				}
	            strcpy(pORDATA[i1].KIKA_NUM1		,"");
    	    	if ( VarIsNull(Query1->FieldValues["KIKA_NUM1"]) != true )
            	{
	            	sBuf 	= Query1->FieldValues["KIKA_NUM1"];     		//規格値１
    	        	strcpy(pORDATA[i1].KIKA_NUM1	,sBuf.c_str());
				}
	            strcpy(pORDATA[i1].KIKA_NUM2		,"");
    	    	if ( VarIsNull(Query1->FieldValues["KIKA_NUM2"]) != true )
            	{
		            sBuf 	= Query1->FieldValues["KIKA_NUM2"];        	//規格値２
    		        strcpy(pORDATA[i1].KIKA_NUM2	,sBuf.c_str());
				}
	            strcpy(pORDATA[i1].KIKA_NUM3		,"");
    	    	if ( VarIsNull(Query1->FieldValues["KIKA_NUM3"]) != true )
            	{
	            	sBuf 	= Query1->FieldValues["KIKA_NUM3"];        	//規格値３
    	        	strcpy(pORDATA[i1].KIKA_NUM3	,sBuf.c_str());
        	    }
	            strcpy(pORDATA[i1].KIKA_STR		,"");
				if ( VarIsNull(Query1->FieldValues["KIKA_STR"]) != true  )
            	{
            		sBuf  	= Query1->FieldValues["KIKA_STR"];        	//規格値文字
	            	strcpy(pORDATA[i1].KIKA_STR		,sBuf.c_str());
   				}
        	    strcpy(pORDATA[i1].KIKA_SUB1		,"");
           		if ( VarIsNull(Query1->FieldValues["KIKA_SUB1"]) != true )
    	        {
        	    	sBuf 	= Query1->FieldValues["KIKA_SUB1"];       	//規格値サブ１
            		strcpy(pORDATA[i1].KIKA_SUB1	,sBuf.c_str());
	            }
    	        strcpy(pORDATA[i1].KIKA_SUB2		,"");
				if ( VarIsNull(Query1->FieldValues["KIKA_SUB2"]) != true )
	            {
    	        	sBuf 	= Query1->FieldValues["KIKA_SUB2"];          //規格値サブ２
        	    	strcpy(pORDATA[i1].KIKA_SUB2	,sBuf.c_str());
	            }
    	        strcpy(pORDATA[i1].KIKA_SUB3		,"");
				if ( VarIsNull(Query1->FieldValues["KIKA_SUB3"]) != true )
	            {
    	        	sBuf 	= Query1->FieldValues["KIKA_SUB3"];         	//規格値サブ３
        	    	strcpy(pORDATA[i1].KIKA_SUB3	,sBuf.c_str());
	            }
    	        //strcpy(pORDATA[i1].SOKU_SU		,"");
				//if ( VarIsNull(Query1->FieldValues["SOKU_SU"]) != true  )
	            //{
    	        // 	sBuf 	= Query1->FieldValues["SOKU_SU"];            //測定指示ｎ数
        	    //	strcpy(pORDATA[i1].SOKU_SU	,sBuf.c_str());
            	//}
	            strcpy(pORDATA[i1].SOKU_FLG		,"");
				if ( VarIsNull(Query1->FieldValues["SOKU_FLG"]) != true )
            	{
	             	sBuf 	= Query1->FieldValues["SOKU_FLG"];        	//測定項目の有無
    	        	strcpy(pORDATA[i1].SOKU_FLG	,sBuf.c_str());
        	    }
	            strcpy(pORDATA[i1].TOKU_FLG		,"");
				if ( VarIsNull(Query1->FieldValues["TOKU_FLG"]) != true )
	            {
    	         	sBuf 	= Query1->FieldValues["TOKU_FLG"];       	//特別項目の有無
        	    	strcpy(pORDATA[i1].TOKU_FLG	,sBuf.c_str());
	            }
    	        strcpy(pORDATA[i1].KIKA_PRT		,"");
				if ( VarIsNull(Query1->FieldValues["KIKA_PRT"]) != true )
	            {
    	         	sBuf 	= Query1->FieldValues["KIKA_PRT"];     		//上限下限値の印刷
        	    	strcpy(pORDATA[i1].KIKA_PRT	,sBuf.c_str());
            	}
	            strcpy(pORDATA[i1].VALUE_TYPE		,"");
    	        if ( VarIsNull(Query1->FieldValues["VALUE_TYPE"]) != true)
            	{
	             	sBuf 	= Query1->FieldValues["VALUE_TYPE"];         //測定値表現
    	        	strcpy(pORDATA[i1].VALUE_TYPE	,sBuf.c_str());
        	    }
	            strcpy(pORDATA[i1].VALUE_DECI		,"");
				if ( VarIsNull(Query1->FieldValues["VALUE_DECI"]) != true )
            	{
             		sBuf 	= Query1->FieldValues["VALUE_DECI"];         //測定値小数点以下桁数
	            	strcpy(pORDATA[i1].VALUE_DECI	,sBuf.c_str());
				}

            }
        }

        //2003.05.10 E.Takase Add↓
        sBuf  = "SELECT  KSD02.*, SM12S.TANNAM As UPDNAME ";
        sBuf += " FROM KSD02 LEFT JOIN SM12S ON KSD02.UPDCHR = SM12S.TANSYA ";
        //2003.05.10 E.Takase Add↑
        //2003.05.10 E.Takase Add コメント↓
        //sBuf = "SELECT * FROM KSD02";
        //2003.05.10 E.Takase Add コメント↑
        //2003.05.09 E.Takase Add↓
        sBuf += " WHERE DTKSHIN ='" + sNowDTKSHIN + "'";
        //sBuf += " WHERE DTKSHIN IN ('" + sNowDTKSHIN + "')";
        //2003.05.09 E.Takase Add↑
        //2003.05.09 E.Takase Add コメント↓
        //sBuf += " WHERE DTKSHIN IN ('" + Cmb_DTKSHIN->Text + "')";
        //2003.05.09 E.Takase Add コメント↑
        sBuf += " AND KIKI_NO = " + AnsiString(pORDATA[i1].KIKI_NO) ;
        if(AnsiString(pORDATA[i1].KOMK_NM).Length() != 0)
        {
            sBuf += " AND KOMK_NM ='"  + AnsiString(pORDATA[i1].KOMK_NM) + "'";
        }
        else
        {
            sBuf += " AND KOMK_NM IS NULL";
        }
        if(AnsiString(pORDATA[i1].KOMK_SUB).Length() != 0)
        {
            sBuf += " AND KOMK_SUB ='"  + AnsiString(pORDATA[i1].KOMK_SUB) + "'";
        }
        else
        {
            sBuf += " AND KOMK_SUB IS NULL";
        }
//単位が違う場合に対応(2003/09/01)
        if(AnsiString(pORDATA[i1].TANI).Length() != 0)
        {
            sBuf += " AND TANI ='"  + AnsiString(pORDATA[i1].TANI) + "'";
        }
        else
        {
            sBuf += " AND TANI IS NULL";
        }
        sBuf += " AND SKB_NO IN ( 2 , 3) ";                        //出荷検査項目、材料証明項目
        sBuf += " AND LOTNO ='" + AnsiString(SGr_tSOKU->Cells[0][0]).Trim() + "'";
        sBuf += " ORDER BY KSD02.UPDYMD DESC, KSD02.UPDTIM DESC";
//For Debug
        // 2003.06.03 k.y
        if( iDEBUG == 1 )
        {
     	    ClpBrd = Clipboard();
     	    ClpBrd->Open();
     	    ClpBrd->SetTextBuf(sBuf.c_str());
     	    ClpBrd->Close();
        }
// Initial Query
        Query1->Close();
        Query1->SQL->Clear();
        Query1->SQL->Add(sBuf);
        Query1->Open();
        Query1->Active = true;
        if( Query1->Eof == false )
        {
            strcpy(pORDATA[i1].DTKSHIN		,"");
            if ( VarIsNull(Query1->FieldValues["DTKSHIN"]) != true )
            {
                sBuf 		= Query1->FieldValues["DTKSHIN"];		//得意先品番
                strcpy(pORDATA[i1].DTKSHIN		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].UNQ_NO		,"");
            if ( VarIsNull(Query1->FieldValues["UNQ_NO"]) != true  )
            {
                sBuf 		= Query1->FieldValues["UNQ_NO"];    		//明細NO
                strcpy(pORDATA[i1].UNQ_NO		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].ORDER_NO		,"");
            if ( VarIsNull(Query1->FieldValues["ORDER_NO"]) != true )
            {
                sBuf 		= Query1->FieldValues["ORDER_NO"];  		//表示・印刷順
                strcpy(pORDATA[i1].ORDER_NO		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].SKB_NO		,"");
            if ( VarIsNull(Query1->FieldValues["SKB_NO"]) != true  )
            {
                sBuf 		= Query1->FieldValues["SKB_NO"];    		//識別NO
                strcpy(pORDATA[i1].SKB_NO		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].HINBAN_SK		,"");
            if ( VarIsNull(Query1->FieldValues["HINBAN_SK"]) != true)
            {
                sBuf 		= Query1->FieldValues["HINBAN_SK"];  	//品番
                strcpy(pORDATA[i1].HINBAN_SK		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KOMK_NO		,"");
            if ( VarIsNull(Query1->FieldValues["KOMK_NO"]) != true )
            {
                sBuf 		= Query1->FieldValues["KOMK_NO"];   		//測定項目NO
                strcpy(pORDATA[i1].KOMK_NO		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KOMK_NM		,"");
            if ( VarIsNull(Query1->FieldValues["KOMK_NM"]) != true )
            {
                sBuf 		= Query1->FieldValues["KOMK_NM"];  		//測定項目名称
                strcpy(pORDATA[i1].KOMK_NM		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KOMK_ENG		,"");
            if ( VarIsNull(Query1->FieldValues["KOMK_ENG"]) != true )
            {
                sBuf 		= Query1->FieldValues["KOMK_ENG"]; 		//測定項目名称（英語）
                strcpy(pORDATA[i1].KOMK_ENG		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KOMK_SUB		,"");
            if ( VarIsNull(Query1->FieldValues["KOMK_SUB"]) != true )
            {
                sBuf 		= Query1->FieldValues["KOMK_SUB"];   	//測定項目サブ名称
                strcpy(pORDATA[i1].KOMK_SUB		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KOMK_SUB_ENG		,"");
            if ( VarIsNull(Query1->FieldValues["KOMK_SUB_ENG"]) != true )
            {
                sBuf 		= Query1->FieldValues["KOMK_SUB_ENG"];	//測定項目サブ名称（英語）
                strcpy(pORDATA[i1].KOMK_SUB_ENG		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKI_NO		,"");
            if ( VarIsNull(Query1->FieldValues["KIKI_NO"]) != true )
            {
                sBuf 		= Query1->FieldValues["KIKI_NO"];     	//測定機器NO
                strcpy(pORDATA[i1].KIKI_NO		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKI_NM		,"");
            if ( VarIsNull(Query1->FieldValues["KIKI_NM"]) != true )
            {
                sBuf 		= Query1->FieldValues["KIKI_NM"];  		//測定機器名称
                strcpy(pORDATA[i1].KIKI_NM		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].TANI		,"");
            if ( VarIsNull(Query1->FieldValues["TANI"]) != true )
            {
                sBuf 		= Query1->FieldValues["TANI"];         	//単位
                strcpy(pORDATA[i1].TANI			,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_TYPE		,"");
            if ( VarIsNull(Query1->FieldValues["KIKA_TYPE"]) != true )
            {
                sBuf 	= Query1->FieldValues["KIKA_TYPE"];      	//規格タイプ
                strcpy(pORDATA[i1].KIKA_TYPE	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_KIND		,"");
            if ( VarIsNull(Query1->FieldValues["KIKA_KIND"]) != true )
            {
                sBuf 	= Query1->FieldValues["KIKA_KIND"];        	//規格種類
                strcpy(pORDATA[i1].KIKA_KIND	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_DECI		,"");
            if ( VarIsNull(Query1->FieldValues["KIKA_DECI"]) != true )
            {
                sBuf 	= Query1->FieldValues["KIKA_DECI"];      	//規格小数点以下桁数
                strcpy(pORDATA[i1].KIKA_DECI	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_NUM1		,"");
            if ( VarIsNull(Query1->FieldValues["KIKA_NUM1"]) != true )
            {
                sBuf 	= Query1->FieldValues["KIKA_NUM1"];     		//規格値１
                strcpy(pORDATA[i1].KIKA_NUM1	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_NUM2		,"");
            if ( VarIsNull(Query1->FieldValues["KIKA_NUM2"]) != true )
            {
                sBuf 	= Query1->FieldValues["KIKA_NUM2"];        	//規格値２
                strcpy(pORDATA[i1].KIKA_NUM2	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_NUM3		,"");
            if ( VarIsNull(Query1->FieldValues["KIKA_NUM3"]) != true )
            {
                sBuf 	= Query1->FieldValues["KIKA_NUM3"];        	//規格値３
                strcpy(pORDATA[i1].KIKA_NUM3	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_STR		,"");
            if ( VarIsNull(Query1->FieldValues["KIKA_STR"]) != true  )
            {
                sBuf  	= Query1->FieldValues["KIKA_STR"];        	//規格値文字
                strcpy(pORDATA[i1].KIKA_STR		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_SUB1		,"");
            if ( VarIsNull(Query1->FieldValues["KIKA_SUB1"]) != true )
            {
                sBuf 	= Query1->FieldValues["KIKA_SUB1"];       	//規格値サブ１
                strcpy(pORDATA[i1].KIKA_SUB1	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_SUB2		,"");
            if ( VarIsNull(Query1->FieldValues["KIKA_SUB2"]) != true )
            {
                sBuf 	= Query1->FieldValues["KIKA_SUB2"];          //規格値サブ２
                strcpy(pORDATA[i1].KIKA_SUB2	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_SUB3		,"");
            if ( VarIsNull(Query1->FieldValues["KIKA_SUB3"]) != true )
            {
                sBuf 	= Query1->FieldValues["KIKA_SUB3"];         	//規格値サブ３
                strcpy(pORDATA[i1].KIKA_SUB3	,sBuf.c_str());
            }
            //strcpy(pORDATA[i1].SOKU_SU		,"");
            //if ( VarIsNull(Query1->FieldValues["SOKU_SU"]) != true  )
            //{
            // 	sBuf 	= Query1->FieldValues["SOKU_SU"];            //測定指示ｎ数
            //	strcpy(pORDATA[i1].SOKU_SU	,sBuf.c_str());
            //}
/*
            strcpy(pORDATA[i1].SOKU_FLG		,"");
            if ( VarIsNull(Query1->FieldValues["SOKU_FLG"]) != true )
            {
                sBuf 	= Query1->FieldValues["SOKU_FLG"];        	//測定項目の有無
                strcpy(pORDATA[i1].SOKU_FLG	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].TOKU_FLG		,"");
            if ( VarIsNull(Query1->FieldValues["TOKU_FLG"]) != true )
            {
                sBuf 	= Query1->FieldValues["TOKU_FLG"];       	//特別項目の有無
                strcpy(pORDATA[i1].TOKU_FLG	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_PRT		,"");
            if ( VarIsNull(Query1->FieldValues["KIKA_PRT"]) != true )
            {
                sBuf 	= Query1->FieldValues["KIKA_PRT"];     		//上限下限値の印刷
                strcpy(pORDATA[i1].KIKA_PRT	,sBuf.c_str());
            }
*/
            strcpy(pORDATA[i1].VALUE_TYPE		,"");
            if ( VarIsNull(Query1->FieldValues["VALUE_TYPE"]) != true)
            {
                sBuf 	= Query1->FieldValues["VALUE_TYPE"];         //測定値表現
                strcpy(pORDATA[i1].VALUE_TYPE	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].VALUE_DECI		,"");
            if ( VarIsNull(Query1->FieldValues["VALUE_DECI"]) != true )
            {
                sBuf 	= Query1->FieldValues["VALUE_DECI"];         //測定値小数点以下桁数
                strcpy(pORDATA[i1].VALUE_DECI	,sBuf.c_str());
            }

        }


        Query1->Close();
    }
	iOrCount = iOrCnt;


//規格の読み込みが終了したので改めてソート（規格の昇順）を行う

	double dHalf1,dHalf2;

/* k.y 2003.05.17
    // メモリの開放
    if( hTEMPORDATA ){
        GlobalUnlock( hTEMPORDATA );
        GlobalFree( hTEMPORDATA );
    }
    hTEMPORDATA = NULL;
    // メモリの確保
    hTEMPORDATA = GlobalAlloc( GHND, sizeof(struct KSM02_DATA) * 1 );
    if( hTEMPORDATA == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        SBr1->Update();
        Beep();
        return;
    }
    pTEMPORDATA = (struct KSM02_DATA *)GlobalLock(hTEMPORDATA);
    if( hTEMPORDATA == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        SBr1->Update();
        Beep();
        return;
    }
*/
    memset(pTEMPORDATA,0x00,sizeof(pTEMPORDATA));

//2003.05.15 M.HIRAI 修正 ↓
	for(i2 = 0; i2 < iOrCount-1; i2++)
	{
		for(i1 = i2+1; i1 < iOrCount; i1++)
		{
            //出荷検査項目と素材検査項目とを分ける
			//if( AnsiString(pORDATA[i2].SKB_NO) > AnsiString(pORDATA[i1].SKB_NO) )
			if( AnsiString(pORDATA[i2].SKB_NO).ToIntDef(0) > AnsiString(pORDATA[i1].SKB_NO).ToIntDef(0) )
			{
 			    Replace_ORData(i2, i1);
			}
		    //同一識別NO（同一検査項目）
			else if( AnsiString(pORDATA[i2].SKB_NO) == AnsiString(pORDATA[i1].SKB_NO) )
			{
                //機器別ソート
			    //if( AnsiString(pORDATA[i2].KIKI_NO) > AnsiString(pORDATA[i1].KIKI_NO) )
                if( AnsiString(pORDATA[i2].KIKI_NO).ToIntDef(0) > AnsiString(pORDATA[i1].KIKI_NO).ToIntDef(0) )
                {
     			    Replace_ORData(i2, i1);
                }
		        //同一機器NO（同一機器）検査
                else if( AnsiString(pORDATA[i2].KIKI_NO) == AnsiString(pORDATA[i1].KIKI_NO) )
                {
                    //規格ソート
        			GetKIKAKU(i2,&dMAX,&dMIN);
	    			dHalf1 = dMIN;
    	    		GetKIKAKU(i1,&dMAX,&dMIN);
			    	dHalf2 = dMIN;
				    if( dHalf1 > dHalf2 )
				    {
     			        Replace_ORData(i2, i1);
                    }
                }
            }
		}
	}

    //外観検査項目NO＝1を一番上に上げる
	for(i1 = 0; i1 < iOrCount; i1++)
	{
		if(AnsiString(pORDATA[ i1 ].KOMK_NO).ToIntDef(0) == 1)
		{
			// dTEMPORDATA[0] <- dORDATA[i1]
            ORData_To_Tmp(i1);
            //１つずつ下げる
			for(i2 = i1-1;i2 >= 0; i2--)
			{
			    // dORDATA[i2+1] <- dORDATA[i2]
                ORData_To_ORData( i2+1, i2 );
			}
			// dORDATA[0] <- dTEMPORDATA[0]
            Tmp_To_ORData(0);
            break;
		}
	}

    //同じ項目をまとめる
	for(i1 = 1; i1 < iOrCount-1; i1++)
	{
		KOMK_NM 	= pORDATA[ i1 ].KOMK_NM;
		KIKI_NO 	= pORDATA[ i1 ].KIKI_NO;
		KOMK_SUB	= pORDATA[ i1 ].KOMK_SUB;
		TANI		= pORDATA[ i1 ].TANI;
		SKB_NO 		= pORDATA[ i1 ].SKB_NO;
		for(i2 = i1+1; i2 < iOrCount; i2++)
		{
			if((AnsiString(pORDATA[ i2 ].KOMK_NM) == KOMK_NM)
            && (AnsiString(pORDATA[ i2 ].KIKI_NO) == KIKI_NO)
            && (AnsiString(pORDATA[ i2 ].SKB_NO) == SKB_NO))
			{
			    // dTEMPORDATA[0] <- dORDATA[i2]
                ORData_To_Tmp(i2);
			    //１つずつ下げる
				for(i3 = i2-1; i3 > i1; i3--)
				{
    			    // pORDATA[i3+1] <- pORDATA[i3]
                    ORData_To_ORData( i3+1, i3 );
				}
    			// dORDATA[i1+1] <- dTEMPORDATA[0]
                Tmp_To_ORData(i1+1);
        		break;
			}
		}
    }
//2003.05.15 M.HIRAI 修正 ↑

/* k.y 2003.05.17
    // メモリの開放
    if( hTEMPORDATA ){
        GlobalUnlock( hTEMPORDATA );
        GlobalFree( hTEMPORDATA );
    }
    hTEMPORDATA = NULL;
*/

//総機器数の算出
    iKikiCnt = 1;
    i2 = AnsiString(pORDATA[0].KIKI_NO).ToIntDef(0);
    for(i1 = 0;i1 < iOrCnt ; i1++)
    {
        if(i2 != AnsiString(pORDATA[i1].KIKI_NO).ToIntDef(0))
        {
            i2 = AnsiString(pORDATA[i1].KIKI_NO).ToIntDef(0);
            iKikiCnt ++;
        }
    }

// 動的コントロールの作成(必要数分の宣言）
//外観検査はコントロールを使わないので数を１引く（外観検査は１項目として考える）
    if(AnsiString(pORDATA[0].KOMK_NO).ToIntDef(0) == 1)
    {
//        iOrCnt--;
//        iSokuCnt -= AnsiString(pORDATA[0].SOKU_SU).ToIntDef(0);
//        iKikiCnt--;
    }
    Pnl_SubBase 	= new TPanel *[iOrCount];
    Pnl_InsName  	= new TPanel *[iOrCount];
    Lab_KOMK_NM  	= new TLabel *[iOrCount];
    Lab_TANI     	= new TLabel *[iOrCount];
    Lab_KIKA     	= new TLabel *[iOrCount];
    Lab_UPKIKA   	= new TLabel *[iOrCount];
    Lab_LOKIKA   	= new TLabel *[iOrCount];
    Pnl_InsNo    	= new TPanel *[iSokuCnt];
    Pnl_InsKikiName = new TPanel *[iKikiCnt];
    Lab_KIKI_NM  	= new TLabel *[iKikiCnt];
    i2 = 0;
    i1 = 0;
    iContCnt = 0;
    iPnl_InsNoCnt = 0;
	iPnl_InsKikiNameCnt = 0;

    iPanelNum 			= 0;
    iSokuGoukei 		= 0;
    iPnl_InsNoCnt 		= 0;
    iPnl_InsNameCnt 	= 0;
    iPanelNum 			= 0;
    iSokuGoukei 		= 0;
    iPnl_InsNoCnt 		= 0;
    iContCnt			= 0;
    iPnl_InsKikiNameCnt = 0;


    SGr_vRIRE_SYUKA->RowCount = 1;
    SGr_vSOKU_SYUKA->RowCount = 1;
    PnlGAIKAN->Visible = false;
    bGAIKAN = false;

    Form1->Refresh();

    int nKIKIPNL_HIGHT;
	while( iContCnt < iOrCnt )
    {
    	SBx_Left_SYUKA->Refresh();
        iPutKiki = AnsiString(pORDATA[iContCnt].KIKI_NO).ToIntDef(0);
		nKIKIPNL_HIGHT = 0;
//同一機器の測定ループ
        while( iPutKiki == AnsiString(pORDATA[iContCnt].KIKI_NO).ToIntDef(0) && iContCnt < iOrCnt)
        {
//ベースパネルの描画
            sBuf = IntToStr(iContCnt);
            Pnl_SubBase[iContCnt] = new TPanel(SBx_Left_SYUKA);
            Pnl_SubBase[iContCnt]->Name = "Pnl_SubBase" + AnsiString::StringOfChar('0', 2-sBuf.Length()) + sBuf;
            Pnl_SubBase[iContCnt]->Parent = SBx_Left_SYUKA;
            Pnl_SubBase[iContCnt]->Left = Pnl_OriginalSubBase->Left;
//外観検査パネルなら
			if(AnsiString(pORDATA[iContCnt].KOMK_NO).ToIntDef(0) == 1)
			{
            	Pnl_SubBase[iContCnt]->Left = 0;
				PnlGAIKAN->Caption = AnsiString(pORDATA[iContCnt].KOMK_NM) + AnsiString(pORDATA[iContCnt].KIKA_STR);
			}
            if( iContCnt == 0 )
            {
                Pnl_SubBase[iContCnt]->Top = PnlGAIKAN->Top;
            }
            else
            {
                Pnl_SubBase[iContCnt]->Top =  Pnl_SubBase[iContCnt - 1 ]->Top+Pnl_SubBase[ iContCnt - 1 ]->Height; ;
            }
            Pnl_SubBase[iContCnt]->Width = Pnl_OriginalSubBase->Width;
//外観検査パネルなら
			if(AnsiString(pORDATA[iContCnt].KOMK_NO).ToIntDef(0) == 1)
			{
            	Pnl_SubBase[iContCnt]->Width = Pnl_SOKUHAN->Width ;
			}
            Pnl_SubBase[iContCnt]->Height =
				24*(AnsiString(pORDATA[iContCnt].SOKU_SU).ToIntDef(0))+(AnsiString(pORDATA[iContCnt].SOKU_SU).ToIntDef(0));
            Pnl_SubBase[iContCnt]->Ctl3D = true;
            Pnl_SubBase[iContCnt]->BevelInner = bvNone;
            Pnl_SubBase[iContCnt]->BevelOuter = bvNone;
            Pnl_SubBase[iContCnt]->BorderWidth = 0;
			nKIKIPNL_HIGHT += Pnl_SubBase[iContCnt]->Height;
            iPnl_InsSubBaseCnt ++;
//測定項目表示パネルの描画
            Pnl_InsName[iContCnt] = new TPanel(Pnl_SubBase[iContCnt]);
            Pnl_InsName[iContCnt]->Name = "Pnl_InsName" + AnsiString::StringOfChar('0', 2-sBuf.Length()) + sBuf;
            Pnl_InsName[iContCnt]->Alignment = taLeftJustify;
            Pnl_InsName[iContCnt]->Align =alLeft ;
            Pnl_InsName[iContCnt]->Caption = "";
            Pnl_InsName[iContCnt]->Parent = Pnl_SubBase[iContCnt];
            Pnl_InsName[iContCnt]->Left = Pnl_OrgInsName->Left;
            Pnl_InsName[iContCnt]->Top = 0;
            Pnl_InsName[iContCnt]->Width = Pnl_OrgInsName->Width;
			if(AnsiString(pORDATA[iContCnt].KOMK_NO).ToIntDef(0) == 1)
			{
            	Pnl_InsName[iContCnt]->Width = Pnl_SOKUHAN->Width ;
			}
            Pnl_InsName[iContCnt]->Height = Pnl_SubBase[iContCnt]->Height;
            Pnl_InsName[iContCnt]->Color = (TColor)GAIKAN_NAME_COLOR;
            Pnl_InsName[iContCnt]->Ctl3D = false;
            Pnl_InsName[iContCnt]->BevelInner = bvNone;
            Pnl_InsName[iContCnt]->BevelOuter = bvRaised;
            Pnl_InsName[iContCnt]->BorderStyle = bsNone;
            Pnl_InsName[iContCnt]->BorderWidth = 0;
			if(AnsiString(pORDATA[iContCnt].SKB_NO) == 3 )
			{
				Pnl_InsName[iContCnt]->Color = (TColor)0x00FFE1FD;
			}
            iPnl_InsNameCnt ++;
//測定項目+単位の描画
            Lab_KOMK_NM[iContCnt] =  new TLabel(Pnl_InsName[iContCnt]);
            Lab_KOMK_NM[iContCnt]->Parent = Pnl_InsName[iContCnt];
            Lab_KOMK_NM[iContCnt]->AutoSize = true;
            Lab_KOMK_NM[iContCnt]->Top = 6;
            Lab_KOMK_NM[iContCnt]->Left = 0;
            Lab_KOMK_NM[iContCnt]->Height = Lab_BASEKOMK_NM->Height;
            Lab_KOMK_NM[iContCnt]->Caption =
				AnsiString(pORDATA[iContCnt].KOMK_NM) + AnsiString(pORDATA[iContCnt].KOMK_SUB);
			if(AnsiString(pORDATA[iContCnt].KIKA_TYPE).ToIntDef(0) == 3)  Lab_KOMK_NM[iContCnt]->Caption += pORDATA[iContCnt].KIKA_STR;
            Lab_KOMK_NM[iContCnt]->Font->Size = 11;
//単位の描画
            Lab_TANI[iContCnt] =     new TLabel(Pnl_InsName[iContCnt]);
            Lab_TANI[iContCnt]->Parent    = Pnl_InsName[iContCnt];
            Lab_TANI[iContCnt]->AutoSize = true;
            Lab_TANI[iContCnt]->Caption = pORDATA[iContCnt].TANI;
            Lab_TANI[iContCnt]->Top = 6;
            Lab_TANI[iContCnt]->Height = Lab_BASETANI->Height;
            Lab_TANI[iContCnt]->Font->Size = 11;
            Lab_TANI[iContCnt]->Left = Pnl_InsName[iContCnt]->Width-Lab_TANI[iContCnt]->Width-2 ;
//ｎ数の表示
            iPanelNum = 0;
            for(i4=0 ; i4 < AnsiString(pORDATA[iContCnt].SOKU_SU).ToIntDef(0);i4++)
            {
                sBuf = IntToStr(iPanelNum);
                Pnl_InsNo[iPnl_InsNoCnt] = new TPanel(Pnl_SubBase[iContCnt]);
                Pnl_InsNo[iPnl_InsNoCnt]->Name = "Pnl_InsNo" + AnsiString::StringOfChar('0', 4-sBuf.Length()) + sBuf;
                Pnl_InsNo[iPnl_InsNoCnt]->Caption = i4+1;
                Pnl_InsNo[iPnl_InsNoCnt]->Parent = Pnl_SubBase[iContCnt];
                Pnl_InsNo[iPnl_InsNoCnt]->Left = Pnl_OrgInsNum->Left;
                Pnl_InsNo[iPnl_InsNoCnt]->Top = (Pnl_SubBase[iContCnt]->Height)/AnsiString(pORDATA[iContCnt].SOKU_SU).ToIntDef(0) * i4;
                Pnl_InsNo[iPnl_InsNoCnt]->Width = Pnl_OrgInsNum->Width;
                Pnl_InsNo[iPnl_InsNoCnt]->Height = (Pnl_SubBase[iContCnt]->Height)/AnsiString(pORDATA[iContCnt].SOKU_SU).ToIntDef(0);
                Pnl_InsNo[iPnl_InsNoCnt]->Color = (TColor)GAIKAN_NAME_COLOR;
//素材検査ならパネルの色を変える
				if(AnsiString(pORDATA[iContCnt].SKB_NO) == 3 )
				{
					Pnl_InsNo[iPnl_InsNoCnt]->Color = (TColor)0x00FFE1FD;
				}
//外観検査項目なら
				if(AnsiString(pORDATA[iContCnt].KOMK_NO).ToIntDef(0) == 1 )
				{
 					Pnl_InsNo[iPnl_InsNoCnt]->Visible = false;
				}
                iPanelNum ++;
                iSokuGoukei ++;
                iPnl_InsNoCnt ++;
                SGr_vRIRE_SYUKA->RowCount ++;
                SGr_vSOKU_SYUKA->RowCount ++;
            }
//規格の表示
//規格値メインラベル
            Lab_KIKA[iContCnt] =  new TLabel(Pnl_InsName[iContCnt]);
            Lab_KIKA[iContCnt]->Parent = Pnl_InsName[iContCnt];
            Lab_KIKA[iContCnt]->ParentColor = false;
            Lab_KIKA[iContCnt]->AutoSize = true;
            Lab_KIKA[iContCnt]->Top = Lab_BASEKIKA->Top;
            Lab_KIKA[iContCnt]->Left =  Pnl_InsName[iContCnt]->Width-Lab_KIKA[iContCnt]->Width;
            Lab_KIKA[iContCnt]->Height =  Lab_BASEKIKA->Height ;
            Lab_KIKA[iContCnt]->Font->Color = clBlack;
            Lab_KIKA[iContCnt]->Font->Size = 11;
            Lab_KIKA[iContCnt]->Font->Name ="ＭＳ ゴシック";
//規格値上限ラベル
            Lab_UPKIKA[iContCnt] =  new TLabel(Pnl_InsName[iContCnt]);
            Lab_UPKIKA[iContCnt]->Parent = Pnl_InsName[iContCnt];
            Lab_UPKIKA[iContCnt]->AutoSize = true;
            Lab_UPKIKA[iContCnt]->Top = Lab_BASEUPKIKA->Top;
            Lab_UPKIKA[iContCnt]->Left =  Lab_BASEUPKIKA->Left  ;
            Lab_UPKIKA[iContCnt]->Height =  Lab_BASEUPKIKA->Height ;
            Lab_UPKIKA[iContCnt]->Font->Color = clBlack;;
            Lab_UPKIKA[iContCnt]->Font->Size = 9;
            Lab_KIKA[iContCnt]->Font->Name ="ＭＳ ゴシック";
//規格値下限ラベル
            Lab_LOKIKA[iContCnt] =  new TLabel(Pnl_InsName[iContCnt]);
            Lab_LOKIKA[iContCnt]->Parent = Pnl_InsName[iContCnt];
            Lab_LOKIKA[iContCnt]->AutoSize = true;
            Lab_LOKIKA[iContCnt]->Top = Lab_BASELOKIKA->Top;
            Lab_LOKIKA[iContCnt]->Left =  Lab_BASELOKIKA->Left  ;
            Lab_LOKIKA[iContCnt]->Height =  Lab_BASELOKIKA->Height ;
            Lab_LOKIKA[iContCnt]->Font->Color = clBlack;;
            Lab_LOKIKA[iContCnt]->Font->Size = 9;
            Lab_KIKA[iContCnt]->Font->Name ="ＭＳ ゴシック";
//規格表示色々
//フォーマット指定（％*.*ｆ）
			AnsiString 	sDeci1;
   			sDeci1 = "0";
			for(i1 = 0;i1 < AnsiString(pORDATA[iContCnt].KIKA_DECI).ToIntDef(0);i1++)
			{
				if( i1 == 0 ) sDeci1 += ".";
				sDeci1 +="0";
			}

            switch(AnsiString(pORDATA[iContCnt].KIKA_TYPE).ToIntDef(0))
            {
            case 1:
                switch(AnsiString(pORDATA[iContCnt].KIKA_KIND).ToIntDef(0))
                {
                case 1:
                	//2003.05.08 E.Takase Add↓
                	sBuf = FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pORDATA[iContCnt].KIKA_NUM1),0.0));
                    sBuf +=  "～";
                    sBuf += FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pORDATA[iContCnt].KIKA_NUM2),0.0));
                    //2003.05.08 E.Takase Add↑
                    //2003.05.08 E.Takase Add コメント↓
                	//sBuf = FormatFloat(sDeci1,AnsiString(pORDATA[iContCnt].KIKA_NUM1).ToDouble());
                    //sBuf +=  "～";
                    //sBuf += FormatFloat(sDeci1,AnsiString(pORDATA[iContCnt].KIKA_NUM2).ToDouble());
                    //2003.05.08 E.Takase Add コメント↑
                    Lab_KIKA[iContCnt]->Caption = sBuf;
					break;
                case 2:
                    //2003.05.08 E.Takase Add↓
                    sBuf = FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pORDATA[iContCnt].KIKA_NUM2),0.0));
                    //2003.05.08 E.Takase Add↑
                    //2003.05.08 E.Takase Add コメント↓
                	//sBuf = FormatFloat(sDeci1,AnsiString(pORDATA[iContCnt].KIKA_NUM2).ToDouble());
                    //2003.05.08 E.Takase Add コメント↑
                   	Lab_KIKA[iContCnt]->Caption = sBuf +"以下";
                    break;
                case 3:
                    //2003.05.08 E.Takase Add↓
                	sBuf = FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pORDATA[iContCnt].KIKA_NUM1),0.0));
                    //2003.05.08 E.Takase Add↑
                    //2003.05.08 E.Takase Add コメント↓
                	//sBuf = FormatFloat(sDeci1,AnsiString(pORDATA[iContCnt].KIKA_NUM1).ToDouble());
                    //2003.05.08 E.Takase Add コメント↑
                    Lab_KIKA[iContCnt]->Caption = sBuf +"以上";
                    break;
                default:
                    break;
                }
                Lab_KIKA[iContCnt]->Left =
                Pnl_InsName[iContCnt]->Width-Lab_KIKA[iContCnt]->Width-2;
                Lab_UPKIKA[iContCnt]->Visible = false;
                Lab_LOKIKA[iContCnt]->Visible = false;
                break;
            case 2:
            	//2003.05.08 E.Takase Add↓
                sBuf = FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pORDATA[iContCnt].KIKA_NUM1),0.0));
                //2003.05.08 E.Takase Add↑
                //2003.05.08 E.Takase Add コメント↓
                //sBuf = FormatFloat(sDeci1,AnsiString(pORDATA[iContCnt].KIKA_NUM1).ToDouble());
                //2003.05.08 E.Takase Add コメント↑
                Lab_KIKA[iContCnt]->Caption = sBuf;
                switch(AnsiString(pORDATA[iContCnt].KIKA_KIND).ToIntDef(0))
                {
                case 1:
                	//2003.05.08 E.Takase Add↓
                	Lab_UPKIKA[iContCnt]->Caption = FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pORDATA[iContCnt].KIKA_NUM2),0.0));
                	Lab_LOKIKA[iContCnt]->Caption = FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pORDATA[iContCnt].KIKA_NUM3),0.0));
					if(Form1->ConvDoubleDefD(Lab_UPKIKA[iContCnt]->Caption,0.0) >=0) {
                    	Lab_UPKIKA[iContCnt]->Caption = "+"+Lab_UPKIKA[iContCnt]->Caption;
                    }
					if(Form1->ConvDoubleDefD(Lab_LOKIKA[iContCnt]->Caption,0.0) >=0) {
                    	Lab_LOKIKA[iContCnt]->Caption = "+"+Lab_LOKIKA[iContCnt]->Caption;
                    }
                	//2003.05.08 E.Takase Add↑
                	//2003.05.08 E.Takase Add コメント↓
                	//Lab_UPKIKA[iContCnt]->Caption = FormatFloat(sDeci1,AnsiString(pORDATA[iContCnt].KIKA_NUM2).ToDouble());
                	//Lab_LOKIKA[iContCnt]->Caption = FormatFloat(sDeci1,AnsiString(pORDATA[iContCnt].KIKA_NUM3).ToDouble());
					//if(Lab_UPKIKA[iContCnt]->Caption.ToDouble() >=0) Lab_UPKIKA[iContCnt]->Caption = "+"+Lab_UPKIKA[iContCnt]->Caption;
					//if(Lab_LOKIKA[iContCnt]->Caption.ToDouble() >=0) Lab_LOKIKA[iContCnt]->Caption = "+"+Lab_LOKIKA[iContCnt]->Caption;
                    //2003.05.08 E.Takase Add コメント↑
                    break;
                case 2:
                    //2003.05.08 E.Takase Add↓
                    Lab_UPKIKA[iContCnt]->Caption = FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pORDATA[iContCnt].KIKA_NUM2),0.0));
                    Lab_LOKIKA[iContCnt]->Caption ="";
					if(Form1->ConvDoubleDefD(Lab_UPKIKA[iContCnt]->Caption,0.0) >=0) {
                    	Lab_UPKIKA[iContCnt]->Caption = "+"+Lab_UPKIKA[iContCnt]->Caption;
                    }
                	//2003.05.08 E.Takase Add↑
                	//2003.05.08 E.Takase Add コメント↓
                    //Lab_UPKIKA[iContCnt]->Caption = FormatFloat(sDeci1,AnsiString(pORDATA[iContCnt].KIKA_NUM2).ToDouble());
                    //Lab_LOKIKA[iContCnt]->Caption ="";
					//if(Lab_UPKIKA[iContCnt]->Caption.ToDouble() >=0) Lab_UPKIKA[iContCnt]->Caption = "+"+Lab_UPKIKA[iContCnt]->Caption;
                    //2003.05.08 E.Takase Add コメント↑
                    break;
                case 3:
                    //2003.05.08 E.Takase Add↓
                    Lab_UPKIKA[iContCnt]->Caption = "";
                    Lab_LOKIKA[iContCnt]->Caption = FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pORDATA[iContCnt].KIKA_NUM3),0.0));
					if(Form1->ConvDoubleDefD(Lab_LOKIKA[iContCnt]->Caption,0.0) >=0) {
                    	Lab_LOKIKA[iContCnt]->Caption = "+"+Lab_LOKIKA[iContCnt]->Caption;
                    }
                	//2003.05.08 E.Takase Add↑
                	//2003.05.08 E.Takase Add コメント↓
                    //Lab_UPKIKA[iContCnt]->Caption = "";
                    //Lab_LOKIKA[iContCnt]->Caption = FormatFloat(sDeci1,AnsiString(pORDATA[iContCnt].KIKA_NUM3).ToDouble());
					//if(Lab_LOKIKA[iContCnt]->Caption.ToDouble() >=0) Lab_LOKIKA[iContCnt]->Caption = "+"+Lab_LOKIKA[iContCnt]->Caption;
                    //2003.05.08 E.Takase Add コメント↑
                    break;
                 default:
                    break;
                }
                if(Lab_UPKIKA[iContCnt]->Width >= Lab_LOKIKA[iContCnt]->Width)
                {
                    Lab_UPKIKA[iContCnt]->Left =
                        Pnl_InsName[iContCnt]->Width - Lab_UPKIKA[iContCnt]->Width -2;
                    Lab_LOKIKA[iContCnt]->Left = Lab_UPKIKA[iContCnt]->Left;
                }
                else
                {
                    Lab_LOKIKA[iContCnt]->Left =
                        Pnl_InsName[iContCnt]->Width - Lab_LOKIKA[iContCnt]->Width -2;
                    Lab_UPKIKA[iContCnt]->Left = Lab_LOKIKA[iContCnt]->Left;
                }
                Lab_KIKA[iContCnt]->Left =
                    Lab_UPKIKA[iContCnt]->Left-Lab_KIKA[iContCnt]->Width-2;
                break;
            case 3:
                Lab_KIKA[iContCnt]->Caption = pORDATA[iContCnt].KIKA_STR;
                Lab_UPKIKA[iContCnt]->Caption ="";
                Lab_LOKIKA[iContCnt]->Caption ="";
                Lab_KIKA[iContCnt]->Left =
                Pnl_InsName[iContCnt]->Width-Lab_KIKA[iContCnt]->Width-2;
				Lab_KIKA[iContCnt]->Visible = true;
                Lab_UPKIKA[iContCnt]->Visible = false;
                Lab_LOKIKA[iContCnt]->Visible = false;
                break;
            default:
                break;
            }
//グリッドの拡大
            iContCnt++;
        }
//機器名称の表示
        sBuf = IntToStr(iPnl_InsKikiNameCnt);
        Pnl_InsKikiName[iPnl_InsKikiNameCnt] = new TPanel(SBx_Left_SYUKA);
        Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Parent = SBx_Left_SYUKA;
        Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Name = "Pnl_InsKikiName" + AnsiString::StringOfChar('0', 4-sBuf.Length()) + sBuf;
        Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Caption = "";
        Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Left = Pnl_OrgKikiName->Left;
        if(iPnl_InsKikiNameCnt == 0 )
        {
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Top = Pnl_SubBase[0]->Top;
        }
        else
        {
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Top = Pnl_InsKikiName[iPnl_InsKikiNameCnt-1]->Top+Pnl_InsKikiName[iPnl_InsKikiNameCnt-1]->Height;
        }
        Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Width = Pnl_OrgKikiName->Width;
        Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Height = nKIKIPNL_HIGHT;
        switch(AnsiString(pORDATA[iContCnt-1].KIKI_NO).ToIntDef(0))
        {
        case 1:
            //マイクロメータ
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)MICROMETER_COLOR;
            break;
        case 2:
            //ノギス
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)NOGISU_COLOR;
            break;
        case 3:
            //マイクロメータ／天秤
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)MICROTENBIN_COLOR;
            break;
        case 4:
            //天秤
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)TENBIN_COLOR;
            break;
        case 5:
            //材料試験機
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)ZAIRYOU_COLOR;
            break;
        case 6:
            //投影機
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)TOUEIKI_COLOR;
            break;
        case 7:
            //顕微鏡
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)KENBIKYO_COLOR;
            break;
        case 8:
            //面粗度計
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)MENARAKEI_COLOR;
            break;
        case 9:
            //シュア硬度形C型
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)KOUDOKEI_C_COLOR;
            break;
        case 10:
            //シュア硬度形D型
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)KOUDOKEI_D_COLOR;
            break;
        case 11:
            //抵抗率測定器
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)TEIKOU_COLOR;
            break;
        case 12:
            //リード線取付抵抗測定機
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)READTEIKOU_COLOR;
            break;
        case 99:
        default:
            //その他
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)ETC_COLOR;
            break;
        }
        Lab_KIKI_NM[iPnl_InsKikiNameCnt] = new TLabel(Pnl_InsKikiName[iPnl_InsKikiNameCnt]);
        Lab_KIKI_NM[iPnl_InsKikiNameCnt]->Name = "Lab_KIKI_NM" + AnsiString::StringOfChar('0', 4-sBuf.Length()) + sBuf;
        Lab_KIKI_NM[iPnl_InsKikiNameCnt]->Caption = pORDATA[iContCnt-1].KIKI_NM;
        Lab_KIKI_NM[iPnl_InsKikiNameCnt]->Parent = Pnl_InsKikiName[iPnl_InsKikiNameCnt];
        Lab_KIKI_NM[iPnl_InsKikiNameCnt]->Left = LabBASEKIKI_NM->Left;
        Lab_KIKI_NM[iPnl_InsKikiNameCnt]->Width = LabBASEKIKI_NM->Width;
        Lab_KIKI_NM[iPnl_InsKikiNameCnt]->WordWrap = True;
        Lab_KIKI_NM[iPnl_InsKikiNameCnt]->Top =
            (Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Height-Lab_KIKI_NM[iPnl_InsKikiNameCnt]->Height)/2;
//	外観検査なら機器名称の表示は不要なのでコントロールを見えなくします
        if(AnsiString(pORDATA[iContCnt-1].KOMK_NO).ToIntDef(0) == 1)
		{
			Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Visible = false;
		}
        iPnl_InsKikiNameCnt ++;
    }
//セルと項目パネルのHEIGHTの調整のためDUMMYパネルを置きます
	if(iContCnt > 0 )
	{
		Pnl_DUMMY->Parent = SBx_Left_SYUKA;
		Pnl_DUMMY->Top = Pnl_SubBase[iContCnt - 1]->Top+Pnl_SubBase[iContCnt - 1]->Height;
	    Pnl_DUMMY->Height = 39;		//グリッドにスクロールバーが出現/未出現で高さを変えたいが、手段が無いため中間の値をとる
	    Pnl_DUMMY->Width = 1;
		Pnl_DUMMY->Left = 0;
	    Pnl_DUMMY->Ctl3D = false;
    	Pnl_DUMMY->BevelInner = bvNone;
	    Pnl_DUMMY->BevelOuter = bvRaised;
    	Pnl_DUMMY->BorderStyle = bsNone;
	    Pnl_DUMMY->BorderWidth = 0;
		Pnl_DUMMY->Visible = true;
    }
	SGr_vSOKU_SYUKA->Refresh();
//出荷検査項目総数
	Panel33->Caption = AnsiString("出　荷　検　査　（") + iContCnt + AnsiString("項）");
//セル情報メモリ設定(測定実績明細データ）
	// メモリの開放
	if( hCELLINFO_SOKU_SYUKA ){
        GlobalUnlock( hCELLINFO_SOKU_SYUKA );
        GlobalFree( hCELLINFO_SOKU_SYUKA );
    }
    hCELLINFO_SOKU_SYUKA = NULL;
    // メモリの確保
	SBx_Left_SYUKA->Refresh();
	SGr_tSOKU->Refresh();
	SGr_vSOKU_SYUKA->Refresh();
    hCELLINFO_SOKU_SYUKA = GlobalAlloc( GHND, sizeof(struct CELLINFO_DATA) * ((SGr_vSOKU_SYUKA->ColCount+1) * SGr_vSOKU_SYUKA->RowCount));
    if( hCELLINFO_SOKU_SYUKA == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        SBr1->Update();
        Beep();
        return;
    }
    pCELLINFO_SOKU_SYUKA = (struct CELLINFO_DATA *)GlobalLock(hCELLINFO_SOKU_SYUKA);
    if( hCELLINFO_SOKU_SYUKA == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        SBr1->Update();
        Beep();
        return;
    }


//製品規格マスター(測定実績データ用）
	// メモリの開放
	if( hSOKU_KSD01DATA ){
        GlobalUnlock( hSOKU_KSD01DATA );
        GlobalFree( hSOKU_KSD01DATA );
    }
    hSOKU_KSD01DATA = NULL;
    // メモリの確保
    hSOKU_KSD01DATA = GlobalAlloc( GHND, sizeof(struct KSD01_DATA) * ((SGr_vSOKU_SYUKA->ColCount+1)));
    if( hSOKU_KSD01DATA == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        SBr1->Update();
        Beep();
        return;
    }
    pSOKU_KSD01DATA = (struct KSD01_DATA *)GlobalLock(hSOKU_KSD01DATA);
    if( hSOKU_KSD01DATA == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        SBr1->Update();
        Beep();
        return;
    }

//ディフォルトのKSM01を各ロットに割り当て
	for(iCol = 0 ; iCol < SGr_tSOKU_SYUKA->ColCount ; iCol++)
	{
		strcpy(pSOKU_KSD01DATA[iCol].DTKSHIN,pKSM01_DATA.DTKSHIN);
		strcpy(pSOKU_KSD01DATA[iCol].HINBAN,pKSM01_DATA.HINBAN);
		strcpy(pSOKU_KSD01DATA[iCol].DTKSCOD,pKSM01_DATA.DTKSCOD);
		strcpy(pSOKU_KSD01DATA[iCol].DTKSNAM,pKSM01_DATA.DTKSNAM);
		strcpy(pSOKU_KSD01DATA[iCol].ZISNAM,pKSM01_DATA.ZISNAM);
		strcpy(pSOKU_KSD01DATA[iCol].HINMEI,pKSM01_DATA.HINMEI);
		strcpy(pSOKU_KSD01DATA[iCol].DTKSHIN1_SZ,pKSM01_DATA.DTKSHIN1_SZ);
		strcpy(pSOKU_KSD01DATA[iCol].DTKSHIN2_SZ,pKSM01_DATA.DTKSHIN2_SZ);
		strcpy(pSOKU_KSD01DATA[iCol].DTKSHIN3_SZ,pKSM01_DATA.DTKSHIN3_SZ);
		strcpy(pSOKU_KSD01DATA[iCol].DTKSHIN4_SZ,pKSM01_DATA.DTKSHIN4_SZ);
		strcpy(pSOKU_KSD01DATA[iCol].DTKSHIN5_SZ,pKSM01_DATA.DTKSHIN5_SZ);
		strcpy(pSOKU_KSD01DATA[iCol].DTKSHIN6_SZ,pKSM01_DATA.DTKSHIN6_SZ);
		strcpy(pSOKU_KSD01DATA[iCol].LOT_LINK_SZ,pKSM01_DATA.LOT_LINK_SZ);
		strcpy(pSOKU_KSD01DATA[iCol].SOKUTEI_NUM,pKSM01_DATA.SOKUTEI_NUM);
		strcpy(pSOKU_KSD01DATA[iCol].OUT_TITLE1,pKSM01_DATA.OUT_TITLE1);
		strcpy(pSOKU_KSD01DATA[iCol].OUT_TITLE2,pKSM01_DATA.OUT_TITLE2);
		strcpy(pSOKU_KSD01DATA[iCol].OUT_TITLE3,pKSM01_DATA.OUT_TITLE3);
		strcpy(pSOKU_KSD01DATA[iCol].OUT_TITLE4,pKSM01_DATA.OUT_TITLE4);
		strcpy(pSOKU_KSD01DATA[iCol].OUT_TITLE5,pKSM01_DATA.OUT_TITLE5);
		strcpy(pSOKU_KSD01DATA[iCol].OUT_TITLE6,pKSM01_DATA.OUT_TITLE6);
		strcpy(pSOKU_KSD01DATA[iCol].OUT_TITLE7,pKSM01_DATA.OUT_TITLE7);
		strcpy(pSOKU_KSD01DATA[iCol].OUT_TITLE8,pKSM01_DATA.OUT_TITLE8);
		strcpy(pSOKU_KSD01DATA[iCol].X_OUT,pKSM01_DATA.X_OUT);
		strcpy(pSOKU_KSD01DATA[iCol].MEMO,pKSM01_DATA.MEMO);
		strcpy(pSOKU_KSD01DATA[iCol].ADDYMD,pKSM01_DATA.ADDYMD);
		strcpy(pSOKU_KSD01DATA[iCol].ADDTIM,pKSM01_DATA.ADDTIM);
		strcpy(pSOKU_KSD01DATA[iCol].UPDYMD,pKSM01_DATA.UPDYMD);
		strcpy(pSOKU_KSD01DATA[iCol].UPDTIM,pKSM01_DATA.UPDTIM);
		strcpy(pSOKU_KSD01DATA[iCol].UPDCHR,pKSM01_DATA.UPDCHR);
		strcpy(pSOKU_KSD01DATA[iCol].UPDCNT,pKSM01_DATA.UPDCNT);
		//2003.05.10 E.Takase Add↓
		//2003.05.17 E.Takase Add↓
		strcpy(pSOKU_KSD01DATA[iCol].UPDNAME , pKSM01_DATA.UPDNAME);
		//2003.05.17 E.Takase Add↑
		//2003.05.17 E.Takase Add コメント↓
		//pSOKU_KSD01DATA[iCol].UPDNAME = pKSM01_DATA.UPDNAME;
		//2003.05.17 E.Takase Add コメント↑
		//2003.05.10 E.Takase Add↑
        pSOKU_KSD01DATA[iCol].UPD_FLG = false;
        pSOKU_KSD01DATA[iCol].SAVE_FLG = true;
    }

//未使用のグリッド（検査しない）のバックカラーを灰色にする
//出荷検査
    nDRAW_GRID = 1;
    //int nKENSAKU_KEY,nCOMP_KEY;
//出荷検査のグリッドをすべて灰色にする
	for( i1 = 0; i1 < SGr_vSOKU_SYUKA->ColCount ; i1++)
    {
		for(i2= 0; i2 <  SGr_vSOKU_SYUKA->RowCount ; i2++)
        {
        	strcpy(pCELLINFO_SOKU_SYUKA[i1*SGr_vSOKU_SYUKA->RowCount+i2].RESULT,"");
        	strcpy(pCELLINFO_SOKU_SYUKA[i1*SGr_vSOKU_SYUKA->RowCount+i2].DISP_RESULT,"");
        	pCELLINFO_SOKU_SYUKA[i1*SGr_vSOKU_SYUKA->RowCount+i2].JUDGE = 2;
		//灰色表示を実現する為項目NOの初期値は0としています。
        	strcpy(pCELLINFO_SOKU_SYUKA[i1*SGr_vSOKU_SYUKA->RowCount+i2].KOMK_NO , "0");
            pCELLINFO_SOKU_SYUKA[i1*SGr_vSOKU_SYUKA->RowCount+i2].INS_ON = false;
        }
    }
//製品規格明細の各セル情報へのコピー
	if(hCELLINFO_SOKU_SYUKA)
	{
		for(i1=0;i1<(SGr_vSOKU_SYUKA->ColCount) ;i1++)
		{
			dMAX = 0;
			dMIN = 0;
    		i4 = 1;
			for(i2=0 ; i2 < iOrCount ; i2++)
			{
    			GetKIKAKU(i2, &dMAX, &dMIN);
				for(i3=0;i3 < AnsiString(pORDATA[i2].SOKU_SU).ToIntDef(0);i3++)
				{
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].DTKSHIN 		, pORDATA[ i2 ].DTKSHIN);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].LOTNO 		, SGr_tSOKU->Cells[i1][0].c_str());
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].UNQ_NO 		, pORDATA[ i2 ].UNQ_NO);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].ORDER_NO		, pORDATA[ i2 ].ORDER_NO);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].SKB_NO 		, pORDATA[ i2 ].SKB_NO);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].HINBAN_SK	, pORDATA[ i2 ].HINBAN_SK);
					//strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KOMK_NO 		, pORDATA[ i2 ].KOMK_NO);
 					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KOMK_NO 		, "0");
 					pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].INS_ON = false;
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KOMK_NM 		, pORDATA[ i2 ].KOMK_NM);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KOMK_ENG		, pORDATA[ i2 ].KOMK_ENG);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KOMK_SUB		, pORDATA[ i2 ].KOMK_SUB);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KOMK_SUB_ENG , pORDATA[ i2 ].KOMK_SUB_ENG);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKI_NO 		, pORDATA[ i2 ].KIKI_NO);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKI_NM 		, pORDATA[ i2 ].KIKI_NM);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].TANI    		, pORDATA[ i2 ].TANI);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKA_TYPE	, pORDATA[ i2 ].KIKA_TYPE);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKA_KIND	, pORDATA[ i2 ].KIKA_KIND);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKA_DECI	, pORDATA[ i2 ].KIKA_DECI);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKA_NUM1	, pORDATA[ i2 ].KIKA_NUM1);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKA_NUM2	, pORDATA[ i2 ].KIKA_NUM2);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKA_NUM3	, pORDATA[ i2 ].KIKA_NUM3);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKA_STR		, pORDATA[ i2 ].KIKA_STR);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKA_SUB1	, pORDATA[ i2 ].KIKA_SUB1);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKA_SUB2	, pORDATA[ i2 ].KIKA_SUB2);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKA_SUB3	, pORDATA[ i2 ].KIKA_SUB3);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].SOKU_SU 		, pORDATA[ i2 ].SOKU_SU);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].SOKU_FLG		, pORDATA[ i2 ].SOKU_FLG);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].TOKU_FLG		, pORDATA[ i2 ].TOKU_FLG);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKA_PRT		, pORDATA[ i2 ].KIKA_PRT);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].VALUE_TYPE	, pORDATA[ i2 ].VALUE_TYPE);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].VALUE_DECI	, pORDATA[ i2 ].VALUE_DECI);
				// 測定日
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].SKTYMD,FormatDateTime("yyyymmdd",Date()).c_str());
				// 測定日（印刷用）
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].DISP_SKTYMD,FormatDateTime("yyyymmdd",Date()).c_str());
				// 登録日
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].ADDYMD,pSOKU_KSD01DATA[i1].ADDYMD);
				// 登録時間
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].ADDTIM,pSOKU_KSD01DATA[i1].ADDTIM);
				// 変更日
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].UPDYMD,pSOKU_KSD01DATA[i1].UPDYMD);
				// 変更時間
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].UPDTIM,pSOKU_KSD01DATA[i1].UPDTIM);
				// 更新回数
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].UPDCNT,pSOKU_KSD01DATA[i1].UPDCNT);
				//製品規格マスターを使いましょう
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].UPDCHR,pSOKU_KSD01DATA[i1].UPDCHR);
					//2003.05.10 E.Takase Add↓
					//2003.05.17 E.Takase Add↓
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].UPDNAME , pSOKU_KSD01DATA[i1].UPDNAME);
					//2003.05.17 E.Takase Add↑
					//2003.05.17 E.Takase Add コメント↓
					//pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].UPDNAME = pSOKU_KSD01DATA[i1].UPDNAME;
					//2003.05.17 E.Takase Add コメント↑
					//2003.05.10 E.Takase Add↓
					//2003.05.10 E.Takase Add↑
					//2003.05.10 E.Takase Add コメント↓
					//pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].UPDNAME = GetTANTO(AnsiString(pSOKU_KSD01DATA[i1].UPDCHR));
					//2003.05.10 E.Takase Add コメント↑
				//規格
                    pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].MAX = dMAX ;
                    pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].MIN = dMIN ;
                    pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].GMAX = dMAX ;
                    pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].GMIN = dMIN ;
					//外観検査は初期化時は良を代入
					if(AnsiString(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KOMK_NO).ToIntDef(0) == 1 )
					{
                        // 2003/10/06 A.Tamura 海老様の要望により「外観＝良（デフォルト値）」を取りやめました。
                    	//strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].RESULT,"0");
                    	//strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].DISP_RESULT,"0");
					}
					i4++;
				}
			}
    	}
//出荷検査予定の項目の白抜き
    	for( i4 = 0; i4 < SGr_vSOKU_SYUKA->ColCount ; i4++)
        {
    	    for(i1 = 0; i1 < iSYUKA_KOMKCNT;i1++)
    		{
                nDRAW_GRID = 1;
                for( i2 = 0; i2 < iOrCount ; i2++)
                {
//ORテーブルの現在の機器NOと項目NOを抽出
                    if((AnsiString(pSYUKA_DATA[i1].KIKI_NO).ToIntDef(0) == AnsiString(pORDATA[i2].KIKI_NO).ToIntDef(0))
                    && (AnsiString(pSYUKA_DATA[i1].KOMK_NM).Trim() 		== AnsiString(pORDATA[i2].KOMK_NM).Trim())
                    && (AnsiString(pSYUKA_DATA[i1].KOMK_SUB).Trim() 	== AnsiString(pORDATA[i2].KOMK_SUB).Trim())
                    && (AnsiString(pSYUKA_DATA[i1].TANI).Trim() 		== AnsiString(pORDATA[i2].TANI).Trim()))
                    {
                        for(i3 = 0;i3 < AnsiString(pSYUKA_DATA[i1].SOKU_SU).ToIntDef(0);i3++)
                        {
                            strcpy(pCELLINFO_SOKU_SYUKA[i4*SGr_vSOKU_SYUKA->RowCount+nDRAW_GRID+i3].RESULT,"");
                            strcpy(pCELLINFO_SOKU_SYUKA[i4*SGr_vSOKU_SYUKA->RowCount+nDRAW_GRID+i3].DISP_RESULT,"");
                            strcpy(pCELLINFO_SOKU_SYUKA[i4*SGr_vSOKU_SYUKA->RowCount+nDRAW_GRID+i3].KOMK_NO,pSYUKA_DATA[i1].KOMK_NO);
                            pCELLINFO_SOKU_SYUKA[i4*SGr_vSOKU_SYUKA->RowCount+nDRAW_GRID+i3].INS_ON = true;
                            if(AnsiString(pCELLINFO_SOKU_SYUKA[i4*SGr_vSOKU_SYUKA->RowCount+nDRAW_GRID+i3].KOMK_NO).ToIntDef(0) == 1 )
					        {
                        		// 2003/10/06 A.Tamura 海老様の要望により「外観＝良（デフォルト値）」を取りやめました。
                    	        //strcpy(pCELLINFO_SOKU_SYUKA[i4*SGr_vSOKU_SYUKA->RowCount+nDRAW_GRID+i3].RESULT,"0");
                    	        //strcpy(pCELLINFO_SOKU_SYUKA[i4*SGr_vSOKU_SYUKA->RowCount+nDRAW_GRID+i3].DISP_RESULT,"0");
					        }
                        }
		    				//i2 = iOrCount+1;
			    			//break;
                        break;
                    }
                    nDRAW_GRID += AnsiString(pORDATA[ i2 ].SOKU_SU).ToIntDef(0);
                }
		    }
    	}
		Set_SYUKAJISSEKI();
		Get_KSD91_SHUKA();						//備考欄表示

//製品規格明細の各セル情報へのコピー
		for(i1=0;i1<(SGr_vSOKU_SYUKA->ColCount) ;i1++)
		{
    		i4 = 1;
			for(i2=0 ; i2 < iOrCount ; i2++)
			{
				for(i3=0;i3 < AnsiString(pORDATA[i2].SOKU_SU).ToIntDef(0);i3++)
				{
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].SOKU_SU 		, pORDATA[ i2 ].SOKU_SU);
					i4++;
				}
			}
    	}
//出荷検査の表示（4回目）
		for( i1 = 0; i1 < SGr_vSOKU_SYUKA->ColCount ; i1++)
    	{
			for(i2= 0; i2 <  SGr_vSOKU_SYUKA->RowCount ; i2++)
        	{
	            SGr_vSOKU_SYUKA->Cells[i1][i2]= pCELLINFO_SOKU_SYUKA[i1*SGr_vSOKU_SYUKA->RowCount+i2].RESULT;
	        }
    	}
/////////////////////////////
	    // メモリの開放
    	if( hSOKU_KSD01_DATA ){
    		GlobalUnlock( hSOKU_KSD01_DATA );
	        GlobalFree( hSOKU_KSD01_DATA );
    	}
        hSOKU_KSD01_DATA = NULL;
	    // メモリの確保
    	hSOKU_KSD01_DATA = GlobalAlloc( GHND, sizeof(struct KSD01_DATA) * (SGr_vSOKU_SYUKA->ColCount+1));
	    if( hSOKU_KSD01_DATA == NULL ){
    		Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(出荷履歴セル01)";
        	Form1->SBr1->Update();
	        Beep();
    	    return;
	    }
    	pSOKU_KSD01_DATA = (struct KSD01_DATA *)GlobalLock(hSOKU_KSD01_DATA);
	    if( hSOKU_KSD01_DATA == NULL ){
    		Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(出荷履歴セル02)";
        	Form1->SBr1->Update();
	        Beep();
    	    return;
	    }
    	SET_KSD01();							//測定実績等の取り込み
////////////////////////////////
	}
//出荷データ中で履歴データが有る物の表示

	//2003.05.09 E.Takase Add↓
 	if(bNowRIRE == true)
	//2003.05.09 E.Takase Add↑
	//2003.05.09 E.Takase Add コメント↓
 	//if(Chk_RIRE->Checked == true)
	//2003.05.09 E.Takase Add コメント↑
	{
		int iRowCount,iColCount;
		SGr_tRIRE->Refresh();
        SGr_vRIRE_SYUKA->Refresh();
		iRowCount = SGr_vRIRE_SYUKA->RowCount;
		iColCount = SGr_vRIRE_SYUKA->ColCount;
		// メモリの開放
		if( hCELLINFO_RIRE_SYUKA ){
        	GlobalUnlock( hCELLINFO_RIRE_SYUKA );
        	GlobalFree( hCELLINFO_RIRE_SYUKA );
    	}
        hCELLINFO_RIRE_SYUKA = NULL;
    	// メモリの確保
    	hCELLINFO_RIRE_SYUKA = GlobalAlloc( GHND, sizeof(struct CELLINFO_DATA) * ((iColCount+1) * iRowCount));
    	if( hCELLINFO_RIRE_SYUKA == NULL ){
        	SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(出荷履歴セル01)";
        	SBr1->Update();
        	Beep();
        	return;
    	}
    	pCELLINFO_RIRE_SYUKA = (struct CELLINFO_DATA *)GlobalLock(hCELLINFO_RIRE_SYUKA);
    	if( hCELLINFO_RIRE_SYUKA == NULL ){
        	SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(出荷履歴セル02)";
        	SBr1->Update();
        	Beep();
        	return;
    	}

        if(hCELLINFO_RIRE_SYUKA)
		{

/* k.k 2003.05.17 DELETE

    		// 素材検索用スレッド処理
    		//TThread *SecondThread = new ThreadRIRE_SYUKA( true );
	   		SecondThread = new ThreadRIRE_SYUKA( true );
   			SecondThread->FreeOnTerminate = true;
			SecondThread->Resume();
    		if( !SecondThread ){
    			// スレッド対応しない場合は、実行が終了するまで待ちます
        		SecondThread->WaitFor();
    		}
*/
            // k.k 2003.05.17 ADD
            // スレッド出荷履歴読み出し
        	GET_RIRE_SYUKA();

		}
	}
	else
	{
		SGr_tRIRE->Cells[0][0]="";
	}
	bLOTCHANGE = false;
/* k.k 2003.05.17 DELETE

    // A.T 2003/05/08
    // 素材検索用スレッド処理
    ThirdThread  = new ThreadSozaiMain( true );
    ThirdThread->FreeOnTerminate = true;
    ThirdThread->Resume();
    if( !ThreadSupport ){
    	// スレッド対応しない場合は、実行が終了するまで待ちます
        ThirdThread->WaitFor();
    }
*/
    // k.k 2003.05.17 ADD ----
    // 素材の表示
	SOZAI_PROCESS();

    // 検索終了フラグ
    Form1->bNowF7 = false;
    //------------------------

    if(bLOT_LINK == false)
	{
        // ロット割り当て画面　呼び出し
		OldMIDASI->Visible = false;
		NewMIDASI->Visible = false;
        OldMIDASI->Parent = SBx_Left_SYUKA;
        NewMIDASI->Parent = SBx_Left_SYUKA;

        // 分割票入力
		if(SGr_tSOKU->Cells[0][0].Trim().Length() != 0
		|| SGr_tRIRE->Cells[0][0].Trim().Length() != 0)
        {
	        Form8->ShowModal();
            // k.k 2003.05.17 DELETE ----
            // 素材の表示
    	    SOZAI_PROCESS();
            bNowLotF7 = false;
	        bLOT_LINK = false;

            // 検索終了フラグ
            Form1->bNowF7 = false;
            //---------------------------
        }
	}
//	bLOT_LINK = true;       //ロットリンクしないフラグ
//	while(!hCELLINFO_SOKU_SYUKA){}
// 2003/06/02 A.Tamura スレッド利用時にコールしていた
//	Sleep(200);

//最初のグリッドセット
    if(hCELLINFO_SOKU_SYUKA && SGr_vSOKU_SYUKA->RowCount > 1 )
    {
        // 2003/10/14 A.Tamura 外観はデフォルト空となるため、最初のカーソルは、Grid右下の一番上固定となります。
   		Form1->SGr_vSOKU_SYUKA->Row =1;
	    Form1->SGr_vSOKU_SYUKA->Col =0;
        /* 2003/10/14 A.Tamura 上記修正のためここは、コメントとなる
        // 2003/06/02 K.Yamada グリッドインデックスエラー回避
    	if((AnsiString(pCELLINFO_SOKU_SYUKA[1].KOMK_NO).ToIntDef(0) == 1)
          && SGr_vSOKU_SYUKA->RowCount > 2)
        {
    		Form1->SGr_vSOKU_SYUKA->Col =0;
	    	Form1->SGr_vSOKU_SYUKA->Row =2;
    	}
    	else
        {
    		Form1->SGr_vSOKU_SYUKA->Row =1;
		    Form1->SGr_vSOKU_SYUKA->Col =0;
	    }
        */
       	Form1->SGr_vSOKU_SYUKA->SetFocus();
        AllGRID_SelectCell(SGr_vSOKU_SYUKA,SGr_vSOKU_SYUKA->Col,SGr_vSOKU_SYUKA->Row,true);
    }
    else if(hCELLINFO_SOKU_SOZAI && SGr_vSOKU_SOZAI->RowCount > 1)
    {
        Form1->SGr_vSOKU_SOZAI->Col =0;
        Form1->SGr_vSOKU_SOZAI->Row =1;
        Form1->SGr_vSOKU_SOZAI->SetFocus();
        AllGRID_SelectCell(SGr_vSOKU_SOZAI,SGr_vSOKU_SOZAI->Col,SGr_vSOKU_SOZAI->Row,true);
    }

}
