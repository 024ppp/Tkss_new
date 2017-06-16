//---------------------------------------------------------------------------
#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>
#include <CheckLst.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <stdio.h>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE 管理のコンポーネント
	TPanel *Panel9;
	TButton *BtnF01;
	TButton *BtnF02;
	TButton *BtnF03;
	TButton *BtnF04;
	TButton *BtnF05;
	TButton *BtnF06;
	TButton *BtnF07;
	TButton *BtnF08;
	TButton *BtnF09;
	TButton *BtnF10;
	TButton *BtnF11;
	TButton *BtnF12;
	TPanel *Panel22;
	TPanel *Pnl01;
	TEdit *Edt_DTKSCOD;
	TEdit *Edt_DTKSNAM;
	TPanel *Pnl03;
	TPanel *Panel28;
	TListBox *Lbx_DTKSHIN_SZ;
	TPanel *Pnl04;
	TEdit *Edt_HINBAN;
	TPanel *Pnl05;
	TEdit *Edt_ZISNAM;
	TPanel *Panel27;
	TPanel *Pnl_SOKUTEI_NUM;
	TPanel *Pnl_SOKUT;
	TStringGrid *SGr_SOKUT;
	TPanel *Panel13;
	TBitBtn *Btn_ADD_SZ;
	TPanel *Panel15;
	TBitBtn *Btn_ADD_SK;
	TPanel *Panel18;
	TBitBtn *Btn_ADD_SP;
	TPanel *Panel20;
	TBitBtn *Btn_DEL;
	TPanel *Panel21;
	TBitBtn *Btn_UP;
	TBitBtn *Btn_DOWN;
	TPanel *Panel26;
	TBitBtn *Btn_EDIT;
	TPanel *Panel1;
	TPanel *Panel4;
	TEdit *Edt_HINMEI;
	TEdit *Edt_DTKSHIN;
	TPanel *Panel34;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TCheckListBox *Clb_OUT_TITLE;
	TPanel *Panel2;
	TRadioButton *Rdo_Object_NowLOT;
	TRadioButton *Rdo_Object_NowLOT_AndMASTER;
    TPanel *Panel30;
    TLabel *Label5;
    TPanel *Panel19;
    TShape *Shape1;
    TPanel *Panel25;
	TRadioButton *Rdo_XOUT_ON;
	TRadioButton *Rdo_XOUT_OFF;
    TPanel *PnlUPDYMD1;
    TPanel *PnlUPDYMD2;
    TPanel *PnlUPDCHR1;
    TPanel *PnlUPDCHR2;
	TPanel *PnlMaster;
    TLabel *Label1;
    TLabel *Label6;
    TPanel *Panel5;
    TPanel *Panel6;
	TRadioButton *Rdo_LOT_LINK_SZ_ON;
	TRadioButton *Rdo_LOT_LINK_SZ_OFF;
	TButton *Btn_DTKSHIN_SZ_ADD;
	TButton *Btn_DTKSHIN_SZ_DEL;
	TDatabase *Database1;
	TQuery *Query1;
	TQuery *Query2;
	TQuery *Query3;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall BtnF12Click(TObject *Sender);
	void __fastcall Btn_ADD_SZClick(TObject *Sender);
	void __fastcall Btn_ADD_SKClick(TObject *Sender);
	void __fastcall Btn_EDITClick(TObject *Sender);
	void __fastcall SGr_SOKUTDblClick(TObject *Sender);
	void __fastcall FormEnter(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall Edt_ALLChange_Base(TObject *Sender);
	void __fastcall Edt_ALLChange(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall Btn_DTKSHIN_SZ_DELClick(TObject *Sender);
	void __fastcall Btn_DTKSHIN_SZ_ADDClick(TObject *Sender);
	void __fastcall Clb_OUT_TITLEClickCheck(TObject *Sender);
	void __fastcall SGr_SOKUTDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
	void __fastcall Btn_UPClick(TObject *Sender);
	void __fastcall Btn_DOWNClick(TObject *Sender);
	void __fastcall SGr_SOKUTClick(TObject *Sender);
	void __fastcall SGr_ListKeyPress(TObject *Sender, char &Key);
	void __fastcall SGr_SOKUTRowMoved(TObject *Sender, int FromIndex,
          int ToIndex);
	void __fastcall Btn_ADD_SPClick(TObject *Sender);
	void __fastcall Btn_DELClick(TObject *Sender);
	void __fastcall Rdo_AllClick(TObject *Sender);
	void __fastcall Edt_ALLChange_DTKSHIN(TObject *Sender);
	void __fastcall BtnF02Click(TObject *Sender);
	void __fastcall BtnF03Click(TObject *Sender);
	void __fastcall BtnF05Click(TObject *Sender);
	void __fastcall BtnF01Click(TObject *Sender);
	void __fastcall BtnF11Click(TObject *Sender);
	void __fastcall Pnl_SOKUTResize(TObject *Sender);

private:	// ユーザー宣言
	int     USER_COD;
	String  USER_NAM;
	String  BUMO_COD;
	String  BUMO_NAM;

    // 検査成績書タイトル項目マスターの件数分メモリ確保
    int		*iTITLE;
    int		iTITLE_Cnt;
    HANDLE  hMemTITLE;

    //int  iSOKUT_UNQ_NO_MAX;
    int		iRowSelTop;
    int		iRowSelBottom;

	// 製品規格マスター
	struct KSM01_DATA {
		char	DTKSHIN[21];		// 得意先品番
		char	REVCNT[4];			// 改訂番号
		char	HINBAN[21];			// 自社品番
		char	DTKSCOD[6];			// 得意先コード
		char	DTKSNAM[51];		// 得意先名称
		char	ZISNAM[21];			// 材質名称（品種）
		char	HINMEI[61];			// 品名
		char	DTKSHIN1_SZ[21];	// 素材用得意先品番1
		char	DTKSHIN2_SZ[21];	// 素材用得意先品番2
		char	DTKSHIN3_SZ[21];	// 素材用得意先品番3
		char	DTKSHIN4_SZ[21];	// 素材用得意先品番4
		char	DTKSHIN5_SZ[21];	// 素材用得意先品番5
		char	DTKSHIN6_SZ[21];	// 素材用得意先品番6
		char	LOT_LINK_SZ[2];		// 素材用ロットのリンク
		char	SOKUTEI_NUM[3];		// 測定項目数
		char	OUT_TITLE1[5];		// 成績書タイトル出力項目1
		char	OUT_TITLE2[5];		// 成績書タイトル出力項目2
		char	OUT_TITLE3[5];		// 成績書タイトル出力項目3
		char	OUT_TITLE4[5];		// 成績書タイトル出力項目4
		char	OUT_TITLE5[5];		// 成績書タイトル出力項目5
		char	OUT_TITLE6[5];		// 成績書タイトル出力項目6
		char	OUT_TITLE7[5];		// 成績書タイトル出力項目7
		char	OUT_TITLE8[5];		// 成績書タイトル出力項目8
		char	X_OUT[2];			// Ｘの出力
		char	MEMO[130];			// 備考
		char	ADDYMD[9];			// 登録日
		char	ADDTIM[5];			// 登録時間
		char	UPDYMD[9];			// 変更日
		char	UPDTIM[5];			// 変更時間
		char   	UPDCHR[7];			// 更新者（コード）
        char    UPDNAM[51];			// 更新者（名称）
		char	UPDCNT[4];			// 更新回数
	} tmpKSM01_DATA;

	// 測定実績データ
	struct KSD01_DATA {
		char	DTKSHIN[21];		// 得意先品番
		char	LOTNO[7];			// ロットNO
		char	LOTNO1_SZ[7];		// 素材用ロットNO1
		char	LOTNO2_SZ[7];		// 素材用ロットNO2
		char	LOTNO3_SZ[7];		// 素材用ロットNO3
		char	LOTNO4_SZ[7];		// 素材用ロットNO4
		char	LOTNO5_SZ[7];		// 素材用ロットNO5
		char	LOTNO6_SZ[7];		// 素材用ロットNO6
		char	HINBAN[21];			// 自社品番
		char	DTKSCOD[6];			// 得意先コード
		char	DTKSNAM[51];		// 得意先名称
		char	ZISNAM[21];			// 材質名称（品種）
		char	HINMEI[61];			// 品名
		char	DTKSHIN1_SZ[21];	// 素材用得意先品番1
		char	DTKSHIN2_SZ[21];	// 素材用得意先品番2
		char	DTKSHIN3_SZ[21];	// 素材用得意先品番3
		char	DTKSHIN4_SZ[21];	// 素材用得意先品番4
		char	DTKSHIN5_SZ[21];	// 素材用得意先品番5
		char	DTKSHIN6_SZ[21];	// 素材用得意先品番6
		char	LOT_LINK_SZ[2];		// 素材用ロットのリンク
		char	SOKUTEI_NUM[3];		// 測定項目数
		char	SOZAI_OK[3];		// 素材判定
		char	SOZAI_OK_PRT[3];	// 素材判定 印刷用
		char	SYUKA_OK[3];		// 出荷判定
		char	SYUKA_OK_PRT[3];	// 出荷判定 印刷用
		char	OUT_TITLE1[5];		// 成績書タイトル出力項目1
		char	OUT_TITLE2[5];		// 成績書タイトル出力項目2
		char	OUT_TITLE3[5];		// 成績書タイトル出力項目3
		char	OUT_TITLE4[5];		// 成績書タイトル出力項目4
		char	OUT_TITLE5[5];		// 成績書タイトル出力項目5
		char	OUT_TITLE6[5];		// 成績書タイトル出力項目6
		char	OUT_TITLE7[5];		// 成績書タイトル出力項目7
		char	OUT_TITLE8[5];		// 成績書タイトル出力項目8
		char	X_OUT[2];			// Ｘの出力
		char	MEMO[130];			// 備考
		char	SKTYMD[9];			// 測定日
		char	SKTYMD_PRT[9];		// 測定日 印刷用
		char	ADDYMD[9];			// 登録日
		char	ADDTIM[5];			// 登録時間
		char	UPDYMD[9];			// 変更日
		char	UPDTIM[5];			// 変更時間
		char   	UPDCHR[7];			// 更新者（コード）
        char    UPDNAM[51];			// 更新者（名称）
		char	UPDCNT[4];			// 更新回数
	} tmpKSD01_DATA;

	void __fastcall SetDTKSHIN_SZ( AnsiString sDTKSHIN );
    void __fastcall SetDTKSNAM( AnsiString sDTKSCOD );
    bool __fastcall UpdData_KSD01( AnsiString sLOTNO );
    bool __fastcall UpdData_Details_KSD02_03( AnsiString sLOTNO );
	void __fastcall UpdKaiteiNo_KSM01_02( AnsiString sDTKSHIN );
    bool __fastcall AddData_KSM01( int iUpd );
    bool __fastcall AddData_Details_KSM02( int iUpd );

public:		// ユーザー宣言

    // 測定画面と共有する変数
    AnsiString	sNOW_DTKSHIN;		// (Input)項目編集対象の得意先品番
    AnsiString	sNOW_LOTNO;			// (Input)項目編集対象のロットNO
    int			iFROM_DATA;			// (Input)初期表示する項目データの表示元
    								//		  1=選択ロットから表示
                                    //		  2=製品規格マスターから表示
    bool		bDispRefresh;		// (Output)項目編集された場合の再表示フラグ

    // 測定機器項目マスターの件数分メモリ確保
    int		*iKIKI;
    int		iKIKI_Cnt;
    HANDLE  hMemKIKI;

    // TStrings
    TStrings *sDEL_UNQ_NO;

    // フォント関連
    HANDLE  OrgFont, MyFont;
    LOGFONT LogFont;

    // データが変更されたかどうかのフラグ(0=更新済又はデータ変更未だ、1=更新未だ)
    int		DataChange;

	// 製品規格明細マスター
	struct KSM02_DATA {
		char	DTKSHIN[21];		// 代表得意先品番
		char	REVCNT[5];			// 改訂番号
		char	UNQ_NO[5];			// 明細NO
		char	ORDER_NO[5];		// 表示順
		char	SKB_NO[2];			// 識別NO
		char	HINBAN_SK[21];		// 品番
		char	KOMK_NO[5];			// 項目NO
		char	KOMK_NM[41];		// 測定項目名称（日本語）
		char	KOMK_ENG[41];		// 測定項目名称（英語）
		char	KOMK_SUB[21];		// 測定項目サブ名称（日本語）
		char	KOMK_SUB_ENG[21];	// 測定項目サブ名称（英語）
		char	KIKI_NO[3];			// 測定機器NO
		char	KIKI_NM[41];		// 測定機器名称
		char    TANI[21];			// 単位
		char    KIKA_TYPE[2];		// 規格タイプ
		char    KIKA_KIND[2];		// 規格種類
		char    KIKA_DECI[2];		// 規格小数点以下桁数
		char    KIKA_NUM1[13];		// 規格値１
		char    KIKA_NUM2[13];		// 規格値２
		char    KIKA_NUM3[13];		// 規格値３
		char    KIKA_STR[41];		// 規格値文字
		char    KIKA_SUB1[21];		// 規格値サブ１
		char    KIKA_SUB2[21];		// 規格値サブ２
		char    KIKA_SUB3[21];		// 規格値サブ３
		char    SOKU_SU[3];			// 測定指示n数
		char    SOKU_FLG[2];		// 測定項目の有無
		char    TOKU_FLG[2];		// 特別項目の有無
		char    KIKA_PRT[2];		// 上限下限値の印刷
		char    VALUE_TYPE[2];		// 測定値表現
		char    VALUE_DECI[2];		// 測定値小数点以下桁数
	} tmpKSM02_DATA;

	// 測定実績明細データ
	struct KSD02_DATA {
		char	DTKSHIN[21];		// 代表得意先品番
		char	LOTNO[7];			// ロットNO
		char	UNQ_NO[5];			// 明細NO
		char	ORDER_NO[5];		// 表示順
		char	SKB_NO[2];			// 識別NO
		char	HINBAN_SK[21];		// 品番
		char	KOMK_NO[5];			// 項目NO
		char	KOMK_NM[41];		// 測定項目名称（日本語）
		char	KOMK_ENG[41];		// 測定項目名称（英語）
		char	KOMK_SUB[21];		// 測定項目サブ名称（日本語）
		char	KOMK_SUB_ENG[21];	// 測定項目サブ名称（英語）
		char	KIKI_NO[3];			// 測定機器NO
		char	KIKI_NM[41];		// 測定機器名称
		char    TANI[21];			// 単位
		char    KIKA_TYPE[2];		// 規格タイプ
		char    KIKA_KIND[2];		// 規格種類
		char    KIKA_DECI[2];		// 規格小数点以下桁数
		char    KIKA_NUM1[13];		// 規格値１
		char    KIKA_NUM2[13];		// 規格値２
		char    KIKA_NUM3[13];		// 規格値３
		char    KIKA_STR[41];		// 規格値文字
		char    KIKA_SUB1[21];		// 規格値サブ１
		char    KIKA_SUB2[21];		// 規格値サブ２
		char    KIKA_SUB3[21];		// 規格値サブ３
		char    SOKU_SU[3];			// 測定指示n数
		char    SOKU_FLG[2];		// 測定項目の有無
		char    TOKU_FLG[2];		// 特別項目の有無
		char    KIKA_PRT[2];		// 上限下限値の印刷
		char    VALUE_TYPE[2];		// 測定値表現
		char    VALUE_DECI[2];		// 測定値小数点以下桁数
		char    SOKU_VAL01[15];		// 測定値1
		char    SOKU_VAL02[15];		// 測定値2
		char    SOKU_VAL03[15];		// 測定値3
		char    SOKU_VAL04[15];		// 測定値4
		char    SOKU_VAL05[15];		// 測定値5
		char    SOKU_VAL06[15];		// 測定値6
		char    SOKU_VAL07[15];		// 測定値7
		char    SOKU_VAL08[15];		// 測定値8
		char    SOKU_VAL09[15];		// 測定値9
		char    SOKU_VAL10[15];		// 測定値10
		char    SOKU_VAL_SU[3];		// 測定実績ｎ数
		char    SOKU_VAL_AVE[16];	// 測定平均値
		char    SOKU_VAL_MAX[15];	// 測定最大値
		char    SOKU_VAL_MIN[15];	// 測定最小値
		char    SOKU_OK[3];			// 測定値判定
		char    DISP_VAL01[15];		// 測定値1 印刷用
		char    DISP_VAL02[15];		// 測定値2 印刷用
		char    DISP_VAL03[15];		// 測定値3 印刷用
		char    DISP_VAL04[15];		// 測定値4 印刷用
		char    DISP_VAL05[15];		// 測定値5 印刷用
		char    DISP_VAL06[15];		// 測定値6 印刷用
		char    DISP_VAL07[15];		// 測定値7 印刷用
		char    DISP_VAL08[15];		// 測定値8 印刷用
		char    DISP_VAL09[15];		// 測定値9 印刷用
		char    DISP_VAL10[15];		// 測定値10 印刷用
		char    DISP_VAL_SU[3];		// 測定実績ｎ数 印刷用
		char    DISP_VAL_AVE[16];	// 測定平均値 印刷用
		char    DISP_VAL_MAX[15];	// 測定最大値 印刷用
		char    DISP_VAL_MIN[15];	// 測定最小値 印刷用
		char    DISP_OK[3];			// 測定値判定 印刷用
		char	SKTYMD[9];			// 測定日
		char	ADDYMD[9];			// 登録日
		char	ADDTIM[5];			// 登録時間
		char	UPDYMD[9];			// 変更日
		char	UPDTIM[5];			// 変更時間
		char   	UPDCHR[7];			// 更新者（コード）
		char	UPDCNT[4];			// 更新回数
	} tmpKSD02_DATA;

    KSM02_DATA	*cpyKSM02_DATA;		// 測定項目コピー用バッファ
    HANDLE		hMemCpyKSM02_DATA;	// 測定項目コピー用バッファのメモリハンドル
    int			iCntCpyKSM02_DATA;	// 測定項目コピー用バッファの数

    void __fastcall Ins_SGr_SOKUT(int iRow);
    void __fastcall RowExchange(int FromIndex, int ToIndex);
	AnsiString __fastcall SGr_SOKUT_GridLineCopy(int iCpyIndex);
	void __fastcall SGr_SOKUT_GridLinePaste(int iPstIndex, AnsiString sUpdFlg, bool iOrderNo_UP);
	__fastcall TForm3(TComponent* Owner);

	bool __fastcall SGr_SOKUT_GridMultiLineCopy();
	bool __fastcall SGr_SOKUT_GridMultiLinePaste();

};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
