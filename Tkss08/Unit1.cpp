//---------------------------------------------------------------------------
//
//  Unit1.cpp
//    【出荷検査システム−ハンディーターミナルメンテナンス】
//    メインフォーム（TForm1クラス）のメンバ関数の定義
//
//  作成者
//    田村　敦司
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
//  概要
//    OnCreateイベント	：タイマーイベント（1000msec）が発生したとき実行します。
//
//  機能説明
//    カウントダウン処理
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Tmr_CountDownTimer(TObject *Sender)
{
    Tmr_CountDown->Tag = Tmr_CountDown->Tag - 1;
    if( Tmr_CountDown->Tag <= 0 ){
        Tmr_CountDown->Enabled = false;
        Btn_Exit->Visible = false;

		// マスターデータ生成＆ＨＴへのダウンロード処理開始
        Main();

    } else{
		Lbl_2->Caption = "開始まで " + IntToStr(Tmr_CountDown->Tag) + "秒";
    }
}

//---------------------------------------------------------------------------
//
//  概要
//    OnCreateイベント	：Form1を作成したときに発生します。
//
//  機能説明
//    初期画面の状態を設定します。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    フォームが作成されるときイベントが以下の順序で発生します。
//    OnCreate→OnShow→OnActivate→OnPaint
//
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{

    if( sCOMMAND.AnsiCompareIC( "/DIRECT" ) == 0 ){
        // メインメニューからユーザーが起動した時は、
        // 即座に処理を開始します

		// マスターデータ生成＆ＨＴへのダウンロード処理開始
        Main();

    } else {
        // パソコン起動時又は、指定時間に自動実行する時は、
        // カウントダウン後（中止可能）、処理を開始します
		Lbl_1->Caption = "ハンディーターミナルメンテナンス処理を開始します。";
		Lbl_2->Caption = "開始まで 5秒";
    	Tmr_CountDown->Tag = 5;
        Tmr_CountDown->Enabled = true;
    }
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「処理中止」ボタンを押した時の処理
//
//  機能説明
//    フォームを閉じます
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Btn_ExitClick(TObject *Sender)
{
    Close();
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：マスターデータ生成＆ＨＴへのダウンロード処理開始
//
//  機能説明
//    マスターデータの生成を行ないます
//    ハンディーターミナルへのダウンロード処理開始します
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
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


	Lbl_1->Caption = "ハンディーターミナル用のマスターデータを整理しています。";
	Lbl_2->Caption = "しばらくお待ちください。";
    Form1->Refresh();

    //カレントディレクトリの取得
    strcpy(CDPath, "X:\\");	/* 値を返す形式: X:\ で文字列を満たす */
    CDPath[0] = 'A' + getdisk();	/* X を現在のドライブ名に置き換える */
    getcurdir(0, CDPath+3);	/* 文字列部分の残りにカレントディレクトリを追加 */

    // ファイルを更新用に開く
    strcpy(path,CDPath);
    strcat(path, "\\master.dat");
    if( (stream = fopen( path, "w+" )) != NULL ){
    	//正常にファイルをオープンできた場合

	    // データベース初期化
	    Database1->Open();

        // ３年前のデータまで検索します
		dtDate = Date();
		dtDate -= 356 * 3;
	    sDATE = FormatDateTime( "yyyymmdd", dtDate);

		// 問合せ実行
		sSQL  = "SELECT KOKBNG, DTKSHIN, LOTBNG ";
		sSQL += "FROM SD21S ";
		sSQL += "WHERE DENYMD>'" + sDATE + "' AND SYUKBN='0' ";
		sSQL += "ORDER BY KOKBNG";

		Query1->SQL->Add(sSQL);
		Query1->Open();
		Query1->Active = true;

		while( !Query1->Eof ){

            // ［工管NO］の取得
			sBuf1 = Query1->FieldValues["KOKBNG"];

            // ［代表得意先品番］の取得
	        if( VarIsNull(Query1->FieldValues["DTKSHIN"]) ){
				sBuf2 = "";
			} else{
				sBuf2 = Query1->FieldValues["DTKSHIN"];
	        }

            if( sBuf2.Trim() != "" ){

	            // ［ロットNO］の取得
	        	if( VarIsNull(Query1->FieldValues["LOTBNG"]) ){
					sBuf3 = "";
				} else{
					sBuf3 = Query1->FieldValues["LOTBNG"];
	        	}

	            if( sBuf3.Trim() != "" ){

                    // 文字長さを調整します
                    sBuf1 = sBuf1 + AnsiString::StringOfChar(' ',  6 - sBuf1.Length());
                    sBuf2 = sBuf2 + AnsiString::StringOfChar(' ', 20 - sBuf2.Length());
                    sBuf3 = sBuf3 + AnsiString::StringOfChar(' ',  6 - sBuf3.Length());

	        	    // １レコードの書込み
			        fprintf( stream,"%s%s%s\n", sBuf1.c_str(),
                    							sBuf2.c_str(),
                                                sBuf3.c_str());

                }
            }

			// カーソルを次にセットする
			Query1->Next();

		}

		// データベース接続を開放します
	    Query1->Close();
		Database1->Close();

	    // ファイルを閉じる
    	fclose(stream);


    // k.k start
	Lbl_1->Caption = "マスターデータをハンディーターミナルに転送しています。";
	Lbl_2->Caption = "しばらくお待ちください。";
    Form1->Refresh();

    fn = path;

    // データダウンロード
    rtn = DataDownLoad();

    if (rtn < 0) {
        // 失敗メッセージ
        MessageDlg("マスターデータの転送が失敗しました。", mtError, TMsgDlgButtons() << mbOK , 0);
    } else {
        // 完了メッセージ
        MessageDlg("マスターデータの転送が完了しました。", mtInformation, TMsgDlgButtons() << mbOK , 0);
    }

    // k.k end


 	}else{
    	//ファイルのオープンに失敗した場合
		fclose(stream);
	}

    Close();
}

//---------------------------------------------------------------------------
// BCCの生成 k.k
/*AnsiString TForm1::CreatBCC(AnsiString asStr)
{
	//TODO この下にコードを追加してください
	int iAscii;

	// 1バイト毎にASCIIコードに変換し足していく
	iAscii = STX;
	int len = asStr.Length();
	for (int i = 2; i <= len; i++)
		iAscii = iAscii + int(asStr[i]) & 0xff;

	// 16進数に変換して返す
	return IntToHex(iAscii,2);

}
//---------------------------------------------------------------------------*/


//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：RS-232C データ受信処理
//
//  機能説明
//    RS-232C データ受信処理
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    AnsiString		：受信したバッファを返します
//
//  備考
//    作成者			：古門　和幸
//
//---------------------------------------------------------------------------
AnsiString TForm1::DataReceive()
{
	//TODO この下にコードを追加してください
	int iSW;
	char Buf[64];
	AnsiString asRet;
	AnsiString asRecBuf;
	time_t nowTime;

	iSW = 10;
	// 制御フロー設定 ON
	CommSetFlow(iComPort,1,1,1,1,1);
	while (1){
		// タイムアウトチェック
		time(&nowTime);
		if (nowTime - sTime > 1) {
			MessageDlg("通信がタイムアウトになりました。", mtError, TMsgDlgButtons() << mbOK , 0);
			return "";
		}
		// １バイト毎に取得
		CommReadNum(iComPort,Buf,1);
		switch (iSW){
		case 10:
			// ヘッダ情報 STX（0x02）
			if (Buf[0] == STX) {
				asRecBuf = Buf[0];
				iSW++;
			}
			break;
		case 11:
			// ID情報
			if (Buf[0] == '1' || Buf[0] == '2'){
				asRecBuf = asRecBuf + Buf[0];
				iSW++;
			}
			break;
		case 12:
			//  区分情報
			if (Buf[0] == 'A' || Buf[0] == 'D' || Buf[0] == 'R' ||
				Buf[0] == 'S' || Buf[0] == 'M'){
				asRecBuf = asRecBuf + Buf[0];
				iSW++;
			}
			break;
		case 13:
			// フッタ情報 ETX（0x03）
			// フッタ（ETX）になったら処理を抜ける　
			if (Buf[0] == ETX){
				asRecBuf = asRecBuf + Buf[0];
				iSW = 20;
				break;
			} else {
				// データ部
				asRecBuf = asRecBuf + Buf[0];
			}
			break;
//		case 14:
//			iSW = 20;
//			break;
		}
		if (iSW == 20) break;
	}
	// 制御フロー設定 OFF
	CommSetFlow(iComPort,0,0,0,0,0);
	return (asRecBuf);

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：ハンディーターミナルへデータを送信
//
//  機能説明
//    ハンディーターミナルへデータをダウンロード（送信）します
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    AnsiString		：受信したバッファを返します
//
//  備考
//    作成者			：古門　和幸
//
//---------------------------------------------------------------------------
int TForm1::DataDownLoad()
{
    //TODO この下にコードを追加してください
	char tmp[64];
	char sData[64];
	int rtn;
    int Cnt;
    int nFlag;						// 処理フラグ　
    int ComFlag;					// 送受信フラグ
    int iRec;						// マスターファイルデータ数
    AnsiString asBufData,asBuf;		// ポートバッファ用
	AnsiString sTmp1, sTmp2;
	time_t nowTime;

    // マスターデータ行数取得
    Cnt = 0;
    nFlag = 0;
    fs.open(fn.c_str(), ios_base::in);
    if (!fs) {
        MessageDlg("ファイルが開けません。", mtError, TMsgDlgButtons() << mbOK , 0);
            return (-1);
    }
    while (fs.getline(sData, sizeof sData))
        Cnt++;
    fs.close();
    // プログレスバー初期化
    ProgressBar->Max = Cnt;
    ProgressBar->Min = 0;

	while (1) {
		// Sleep(100);
		switch (nFlag) {
		case 0:
			nFlag = 10;
			break;
		case 10:
			// 通信ポートオープン
			rtn = CommOpen("COM3","115200","N,8,1");
			if (rtn < 0) {
				MessageDlg("通信ポートオープンエラー", mtError, TMsgDlgButtons() << mbOK , 0);
				return (-1);
			}
			iComPort = rtn;
			nFlag = 100;
			break;
		case 100:
	        // 送信
	        sprintf(tmp, "%c%s%c", STX, "1D**", ETX);
	        /*
	        sprintf(tmp, "%c%s", STX, "1D");
			// BCCチェック
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
			CommClear(iComPort);		// ポートバッファクリア
			CommWrite(iComPort, tmp);	// ダウンロードコマンド送信
			time(&sTime);				// 現在時刻取得
			nFlag = 110;
			break;
		case 110:
			// タイムアウトチェック（１ｓ）
			time(&nowTime);
			if (nowTime - sTime > 1) {
				CommClose(iComPort);
				MessageDlg("通信がタイムアウトになりました。", mtError, TMsgDlgButtons() << mbOK , 0);
				return (-1);
			}
			nFlag = 120;
			break;
	    case 120:
			// バッファ受信
			asBufData = DataReceive();

			// 送信判別
			if (asBufData.AnsiPos("\x06") > 0) {
				nFlag = 130;	        // ACK受信
			} else {
				CommClose(iComPort);	// NAK受信
                return (-1);
            }
			break;
		case 130:
			// 入力ファイル
			fs.open(fn.c_str(), ios_base::in);
			if (!fs) {
				CommClose(iComPort);
				MessageDlg("ファイルが開けません。", mtError, TMsgDlgButtons() << mbOK , 0);
				return (-1);
			}
			iRec = 0;
			nFlag = 140;
			break;
		case 140:
			// ファイルがEOFになるまで送信データ文字列を作成
			// EOFになったら空のデータを作成
			if (fs.eof() != 0){
				sprintf(tmp, "%c%s", STX, "1M00000");
				sprintf(sData, "%32s", " ");
				nFlag = 150;
			} else {
				// 行数カウント
				iRec++;
				sprintf(tmp, "%c%s%05d", STX, "1M", iRec);
				fs.getline(sData, sizeof sData);
				time(&sTime);
				nFlag = 145;
                ProgressBar->Position = iRec;
			}
	        // 暫定
	        if (sData[0] == '\0') {
	           sprintf(tmp, "%c%s", STX, "1M00000");
	           sprintf(sData, "%32s", " ");
	           nFlag = 150;
	        }
			strcat(tmp, sData);
	/*
			// BCCチェック
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

			CommClear(iComPort);        // ポートバッファクリア
			CommWrite(iComPort, tmp);   // マスターデータ・コマンド送信
			break;
		case 145:
			// タイムアウトチェック
			time(&nowTime);
			if (nowTime - sTime > 1) {
				MessageDlg("通信がタイムアウトになりました。", mtError, TMsgDlgButtons() << mbOK , 0);
				fs.close();
				CommClose(iComPort);
				return(-1);
			}
			nFlag = 146;
			break;
		case 146:
			// バッファ受信
			asBufData = DataReceive();

			// 送信判別
			if (asBufData.AnsiPos("\x06") > 0) {
				nFlag = 140;	// ACK受信
			} else {
				CommClose(iComPort);	// NAK受信
                return (-1);
            }
			break;
		case 150:
			// ファイルクローズ
			fs.close();
			time(&sTime);
			nFlag = 160;
			break;
		case 160:
			// タイムアウトチェック
			time(&nowTime);
			if (nowTime - sTime > 1) {
				MessageDlg("通信がタイムアウトになりました。", mtError, TMsgDlgButtons() << mbOK , 0);
				CommClose(iComPort);
				return (-1);
			}
			nFlag = 170;
			break;
		case 170:
			// バッファ受信
			asBufData = DataReceive();

			// 送信判別
			if (asBufData.AnsiPos("\x06") > 0) {
				nFlag = 999;		// ACK受信
			} else {
				CommClose(iComPort);	// NAK受信
                return (-1);
            }
			break;
		case 999:
			// 通信終了
			CommClose(iComPort);	// ポートクローズ
			fs.close();
			return (1);
			break;
		}
	}
}

