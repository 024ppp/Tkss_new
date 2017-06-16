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

//素材測定実績データ前回取り込み日時
extern struct structKSD29{
	AnsiString FUNC_ID ;  // 処理NO
    AnsiString UPDYMD ;   // 処理日付
    AnsiString UPDTIM ;   // 処理時間
    AnsiString STRWHERE ; // 条件文
}KSD29;

//素材測定データ
extern struct structKD_1{
	AnsiString KENSA_YMD; 		// 検査予定年月日
	AnsiString TOLEY_NO;  		// トレーＮｏ
	AnsiString SAMPLE_P;  		// サンプルポジション
	AnsiString SOKUTEI_SU;		// 測定数
	AnsiString DTKSHIN; 		// 得意先品番
	AnsiString LOTNO; 			// ロットNO
	AnsiString HINBAN;			// 品番
	AnsiString ZISCOD;			// 材質コード
	AnsiString ZISNAM;			// 材質名
	AnsiString KIKA_NUM1;		// 規格1（下限 取付抵抗：上限）
	AnsiString KIKA_NUM2;		// 規格2（上限 取付抵抗：電圧）
	AnsiString KIKA_SUB1;		// 規格サブ1（ 取付抵抗：時間   取付強度：速度 抵抗率：電流 曲げ：スパン）
	AnsiString KIKA_SUB2;		// 規格サブ1（ 取付抵抗：タイプ 取付強度：単位              曲げ：単位）
	AnsiString KEIJYO_KBN;		// 形状区分
	AnsiString SOKUTEI[100];	// 測定値
	AnsiString SOKUTEI_NM;		// 測定数
	AnsiString SOKUTE_AVE;		// 平均値
	AnsiString ADDYMD;			// 登録日
	AnsiString ADDTIM;			// 登録時間
	AnsiString UPDYMD;			// 変更日
	AnsiString UPDTIM;			// 変更時間
	AnsiString UPDCHR;			// 更新者
	AnsiString UPDCNT;			// 更新回数
	AnsiString MEMO;			// 備考
	AnsiString SOKUTE_MAX;		// 最大値
	AnsiString SOKUTE_MIN;		// 最小値
	AnsiString SOKUTE_OK;		// 判定
	AnsiString SKTYMD; 			// 測定日
        //20170417 Y.Onishi 工場区分追加
        AnsiString KOJOKBN; 			// 工場区分
}KD_1;

//素材測定実績データ
extern struct structKSD21{
	int 	   InsFlag; 		// 新規の場合：-1
	AnsiString DTKSHIN; 		// 得意先品番
	AnsiString LOTNO; 			// ロットNO
	AnsiString HINBAN; 			// 自社品番
	AnsiString DTKSCOD; 		// 得意先コード
	AnsiString DTKSNAM; 		// 得意先名称
	AnsiString ZISNAM; 			// 材質名称（品種）
	AnsiString SOKUTEI_NUM; 	// 測定項目数
	AnsiString SOZAI_OK; 		// 素材判定
	AnsiString MEMO; 			// 備考
	AnsiString SKTYMD; 			// 測定日
	AnsiString ADDYMD; 			// 登録日
	AnsiString ADDTIM; 			// 登録時間
	AnsiString UPDYMD; 			// 変更日
	AnsiString UPDTIM; 			// 変更時間
	AnsiString UPDCHR; 			// 更新者
	AnsiString UPDCNT; 			// 更新回数
}KSD21;


//素材測定実績明細データ
extern struct structKSD22{
	int 	   InsFlag; 		// 新規の場合：-1
	AnsiString DTKSHIN; 		// 得意先品番
	AnsiString LOTNO; 			// ロットNO
	AnsiString UNQ_NO; 			// 明細NO
	AnsiString KOMK_NO; 		// 測定項目NO
	AnsiString KOMK_NM; 		// 測定項目名称
	AnsiString KOMK_ENG; 		// 測定項目名称（英語）
	AnsiString KOMK_SUB; 		// 測定項目サブ名称
	AnsiString KOMK_SUB_ENG; 	// 測定項目サブ名称（英語）
	AnsiString KIKI_NO; 		// 測定機器NO
	AnsiString KIKI_NM; 		// 測定機器名称
	AnsiString TANI; 			// 単位
	AnsiString KIKA_TYPE; 		// 規格タイプ
	AnsiString KIKA_KIND; 		// 規格種類
	AnsiString KIKA_DECI; 		// 規格小数点以下桁数
	AnsiString KIKA_NUM1; 		// 規格値1
	AnsiString KIKA_NUM2; 		// 規格値2
	AnsiString KIKA_NUM3; 		// 規格値3
	AnsiString KIKA_STR; 		// 規格値文字
	AnsiString KIKA_SUB1; 		// 規格値サブ1
	AnsiString KIKA_SUB2; 		// 規格値サブ2
	AnsiString SOKU_SU; 		// 測定指示n数
	AnsiString VALUE_TYPE; 		// 測定値表現
	AnsiString VALUE_DECI; 		// 測定値小数点以下桁数
	AnsiString SOKU_VAL[100]; 	// 測定値
	//AnsiString SOKU_VAL01; 		// 測定値1
	//AnsiString SOKU_VAL02; 		// 測定値2
	//AnsiString SOKU_VAL03; 		// 測定値3
	//AnsiString SOKU_VAL04; 		// 測定値4
	//AnsiString SOKU_VAL05; 		// 測定値5
	//AnsiString SOKU_VAL06; 		// 測定値6
	//AnsiString SOKU_VAL07; 		// 測定値7
	//AnsiString SOKU_VAL08; 		// 測定値8
	//AnsiString SOKU_VAL09; 		// 測定値9
	//AnsiString SOKU_VAL10; 		// 測定値10
	AnsiString SOKU_VAL_SU;		// 測定実績n数
	AnsiString SOKU_VAL_AVE; 	// 測定平均値
	AnsiString SOKU_VAL_MAX; 	// 測定最大値
	AnsiString SOKU_VAL_MIN;	// 測定最小値
	AnsiString SOKU_OK; 		// 測定値判定
	AnsiString SKTYMD; 			// 測定日
	AnsiString ADDYMD; 			// 登録日
	AnsiString ADDTIM; 			// 登録時間
	AnsiString UPDYMD; 			// 変更日
	AnsiString UPDTIM; 			// 変更時間
	AnsiString UPDCHR; 			// 更新者
	AnsiString UPDCNT; 			// 更新回数
	AnsiString HINBAN; 			// 自社品番
}KSD22;

//素材測定実績例外データ
extern struct structKSD23{
	int 	   InsFlag; 		// 新規の場合：-1
//	AnsiString DTKSHIN; 		// 得意先品番
//	AnsiString LOTNO; 			// ロットNO
//	AnsiString UNQ_NO; 			// 明細NO
//	AnsiString SOKU_NO; 		// 測定NO
//	AnsiString SOKU_VAL; 		// 測定値
}KSD23;

//各素材の固定文字列
extern struct structFixStr{
	AnsiString TABLE1;			// テーブル名
	AnsiString TABLE2;			// 例外テーブル名
	AnsiString KOMK_NO;			// 測定項目No
	AnsiString ORDER_NO;		// 表示順
	AnsiString KOMK_NM;			// 測定項目名称
	AnsiString KOMK_ENG;		// 測定項目名称（英語）
	AnsiString KIKI_NO;			// 測定機器No
	AnsiString KIKI_NM;			// 測定機器名称
	AnsiString TANI[5];			// 単位
	AnsiString KIKA_TYPE;		// 規格タイプ
	AnsiString KIKA_KIND;		// 規格種類
	AnsiString KIKA_DECI;		// 規格小数点以下桁数
	AnsiString KIKA_NUM2;		// 規格値２
	AnsiString KIKA_NUM3;		// 規格値３
	AnsiString KIKA_STR;		// 規格値文字
	AnsiString SOKU_FLG;		// 測定項目の有無
	AnsiString TOKU_FLG;		// 特別項目の有無
	AnsiString KIKA_PRT;		// 上限・下限値の印刷
	AnsiString VALUE_TYPE;		// 測定値表現
	AnsiString VALUE_DECI;		// 測定値小数点以下桁数
	AnsiString F_SOKUTE_KBN;	// フィールド名：測定区分
	AnsiString F_KIKA_NUM1;		// フィールド名：規格値１
	AnsiString F_KIKA_NUM2;		// フィールド名：規格値２
	AnsiString F_KIKA_SUB1;		// フィールド名：規格値サブ１
	AnsiString F_KIKA_SUB2;		// フィールド名：規格値サブ２
	AnsiString F_KEIJYO_KBN;	// フィールド名：形状区分
	AnsiString F_SOKUTEI_1;		// フィールド名：測定値１
	AnsiString F_SOKUTEI_2;		// フィールド名：測定値２
	AnsiString F_SOKUTEI_SU;	// フィールド名：測定指示数
	AnsiString F_SOKUTEI_NM;	// フィールド名：測定実績数
	AnsiString F_SOKUTE_AVE;	// フィールド名：測定値 平均
	AnsiString F_SOKUTEICHI;	// フィールド名：測定値
	AnsiString W_SOKUTE_KBN;	// フィールド名：測定区分
} FixStr[18];
extern int FixStrNum;			// 固定文字列の配列数 16

extern AnsiString MEMOStr[18];  // 各測定値の備考

extern AnsiString sBufSQL;      // バッファ SQL文

//素材測定実績データ（KSD21）の
//更新回数・素材測定更新に必要なキーを保存
extern TStrings *sDTKSHIN;    	// 得意先品番
extern TStrings *sLOTNO; 		// ロットNO
extern TStrings *sHINBAN; 		// 自社品番
extern int isDTKSHINNum;		// データ数

#endif







