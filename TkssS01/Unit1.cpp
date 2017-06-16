//---------------------------------------------------------------------------
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TServiceTkssS01 *ServiceTkssS01;
TSparkyThread *SparkyThread;

//データ検索結果格納
structKSD29 KSD29;
structKSD21 KSD21;
structKSD22 KSD22;
structKSD23 KSD23;
structKD_1  KD_1;

structFixStr FixStr[16]; //各素材の固定文字列
int FixStrNum;           //素材の種類

AnsiString MEMOStr[16];
AnsiString sBufSQL;

//素材測定実績データ（KSD21）の
//更新回数・素材測定更新に必要なキーを保存
TStrings *sDTKSHIN;    	//得意先品番
TStrings *sLOTNO; 		//ロットNO
TStrings *sHINBAN; 		//自社品番                            //onishi
int isDTKSHINNum;       //データ数

AnsiString sExecDate;
AnsiString sStartTime;


//---------------------------------------------------------------------------
__fastcall TServiceTkssS01::TServiceTkssS01(TComponent* Owner)
	: TService(Owner)
{
}

PServiceController __fastcall TServiceTkssS01::GetServiceController(void)
{
    return (PServiceController) ServiceController;
}

void __stdcall ServiceController(unsigned CtrlCode)
{
	ServiceTkssS01->Controller(CtrlCode);
}
__fastcall TSparkyThread::TSparkyThread(bool CreateSuspended): TThread(CreateSuspended)
{
}

void __fastcall TSparkyThread::Execute()
{

	int iRtn;
	AnsiString sRtn;
	AnsiString sMsg;

	TDateTime dtNow;    	//現在の日時
	WORD Y,M,D,H,N,S,MS;   	//現在の日時を各成分にセット
	AnsiString sNowDate;
	AnsiString sNowTime;

	//TStrings初期化
	sDTKSHIN	= new TStringList;    	//得意先品番
	sLOTNO		= new TStringList; 		//ロットNO
	sHINBAN		= new TStringList; 		//自社品番  onishi

	while ( 1 ) {

		//現在の時刻を取得
		dtNow = Now( );
		DecodeDate(dtNow,Y,M,D);
		DecodeTime(dtNow,H,N,S,MS);
		sNowDate = "";
		sNowDate += FormatFloat("0000",Y);
		sNowDate += FormatFloat("00",M);
		sNowDate += FormatFloat("00",D);
		sNowTime = "";
		sNowTime += FormatFloat("00",H);
		sNowTime += FormatFloat("00",N);


		if ( sExecDate != sNowDate && sStartTime < sNowTime ) {

			//自動整理登録実行
			iRtn = AutoEntry();
			sMsg = "自動整理登録実行 " + IntToStr(iRtn) + "件更新しました（" + sNowDate + sNowTime + "）";
			//イベントログ出力
			//ServiceTkssS01->LogMessage(KSD29.STRWHERE,EVENTLOG_INFORMATION_TYPE,0,0);
			ServiceTkssS01->LogMessage(sMsg,EVENTLOG_INFORMATION_TYPE,0,0);

			//実行日付更新
			sExecDate = sNowDate;
			sRtn = SetKSD29("1",sExecDate);
			KSD29.UPDYMD = sNowDate;

		}

		Sleep(300000);

	}



}



//---------------------------------------------------------------------------

void __fastcall TServiceTkssS01::Service1Start(TService *Sender, bool &Started)
{
	//前回実行日時取得
	int iRtn = GetKSD29("1");
    if( iRtn < 0 ){
        // データ取得失敗
        KSD29.UPDYMD = "19900101";
	    KSD29.UPDTIM = "0400";
    }

    // データ取得成功
    sExecDate = KSD29.UPDYMD;
	sStartTime = KSD29.UPDTIM;

	LogMessage("自動整理登録サービスの開始（" + sExecDate + sStartTime + "）",EVENTLOG_INFORMATION_TYPE,0,0);
	SparkyThread = new TSparkyThread(false);
    Started = true;

	Beep();


}
//---------------------------------------------------------------------------
void __fastcall TServiceTkssS01::Service1Continue(TService *Sender,
      bool &Continued)
{
    SparkyThread->Resume();
    Continued = true;

}
//---------------------------------------------------------------------------
void __fastcall TServiceTkssS01::Service1Pause(TService *Sender, bool &Paused)
{
    SparkyThread->Suspend();
    Paused = true;
	
}
//---------------------------------------------------------------------------
void __fastcall TServiceTkssS01::Service1Stop(TService *Sender, bool &Stopped)
{
    SparkyThread->Terminate();
	Stopped = true;
	LogMessage("自動整理登録サービスの終了",EVENTLOG_INFORMATION_TYPE,0,0);

}

//---------------------------------------------------------------------------
//素材測定実績データ前回取り込み日時データ取得
int __fastcall TServiceTkssS01::GetKSD29(AnsiString strFUNC_ID)
{
	AnsiString sBuf;

	//素材測定実績データ前回取り込み日時データ取得
	KSD29.FUNC_ID = strFUNC_ID;
	KSD29.UPDYMD = "";
	KSD29.UPDTIM = "";

	// Initial Query
	ServiceTkssS01->Query1->Close();
	ServiceTkssS01->Query1->SQL->Clear();

	// 問合せ実行
	sBuf = "SELECT FUNC_ID, UPDYMD, UPDTIM FROM KSD29 WHERE  FUNC_ID = ";
	sBuf += KSD29.FUNC_ID;

	ServiceTkssS01->Query1->SQL->Add(sBuf);
	ServiceTkssS01->Query1->Open();
	ServiceTkssS01->Query1->Active = true;

	if ( ServiceTkssS01->Query1->Bof && ServiceTkssS01->Query1->Eof ) {
	//検索結果 ０件
		return(-1);
	}
	KSD29.UPDYMD = ServiceTkssS01->Query1->FieldValues["UPDYMD"];
	KSD29.UPDTIM = ServiceTkssS01->Query1->FieldValues["UPDTIM"];


	return(0);
}
//---------------------------------------------------------------------------
//素材測定実績データ前回取り込み日時データセット
AnsiString __fastcall TSparkyThread::SetKSD29(AnsiString strFUNC_ID,AnsiString strUPDYMD)
{
	AnsiString sBufSQL;

	// Initial Query
	ServiceTkssS01->Query1->Close();
	ServiceTkssS01->Query1->SQL->Clear();

	// 問合せ文作成
	sBufSQL = "update KSD29 set ";
	sBufSQL += "UPDYMD='" + strUPDYMD + "'"	;

	sBufSQL += " WHERE  FUNC_ID = ";
	sBufSQL += strFUNC_ID;

	ServiceTkssS01->Query1->SQL->Add(sBufSQL);

	// 問い合せ文の実行
	try
	{
		ServiceTkssS01->Query1->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		return(e.Message);
	}
	catch(Exception& e)
	{
		return(e.Message);
	}

	return("");


}
//---------------------------------------------------------------------------





