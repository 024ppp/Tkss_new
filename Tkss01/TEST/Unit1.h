//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Clipbrd.hpp>
#include "PERFGRAP.h"
#include "NumberEdit.h"
#include <Db.hpp>
#include <DBTables.hpp>

#include <Chart.hpp>
#include <Series.hpp>
#include <TeeFunci.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <string.h>
#include <math.h>
#include <Mask.hpp>
#include <MPlayer.hpp>
#include <time.h>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE 管理のコンポーネント
	TPanel *Panel1;
	TStatusBar *SBr1;
	TPanel *Panel2;
	TButton *BtnF02;
	TButton *BtnF01;
	TButton *BtnF03;
	TButton *BtnF04;
	TButton *BtnF05;
	TButton *BtnF06;
	TButton *BtnF07;
	TButton *BtnF08;
	TButton *BtnF09;
	TButton *BtnF10;
	TBitBtn *BtnF11;
	TBitBtn *BtnF12;
	TPanel *Pnl_skInfo;
	TSplitter *Splitter1;
	TPanel *Panel3;
	TPanel *Panel4;
	TPanel *Panel12;
	TPanel *Panel14;
	TSplitter *Splitter2;
	TPanel *Panel15;
	TPanel *Panel16;
	TPanel *Panel18;
	TPanel *Panel19;
	TPanel *Panel20;
	TPanel *Panel21;
	TPanel *Panel22;
	TPanel *Panel23;
	TPanel *Panel24;
	TSplitter *Splitter3;
	TSplitter *Splitter4;
	TSplitter *Splitter5;
	TPanel *Panel25;
	TPanel *Pnl_skInfo_Title;
	TPanel *Panel87;
	TPanel *Pnl_skInfo_tDTKS;
	TPanel *Pnl_skInfo_tLOTBNG1;
	TPanel *Pnl_skInfo_tHINBAN;
	TPanel *Pnl_skInfo_tHINMEI;
	TPanel *Pnl_skInfo_vDTKS;
	TPanel *Pnl_skInfo_tKENSA1;
	TPanel *Pnl_skInfo_tKIKAKU1;
	TPanel *Pnl_skInfo_tKIKI1;
	TPanel *Pnl_skInfo_vHINBAN;
	TPanel *Pnl_skInfo_vHINMEI;
	TPanel *Pnl_skInfo_vLOTBNG1;
	TPanel *Pnl_skInfo_vKENSA1;
	TPanel *Pnl_skInfo_vKIKAKU1;
	TPanel *Pnl_skInfo_vKIKI1;
	TPageControl *Pcl_skInfo_page1;
	TTabSheet *Tst_skInfo_page1_1;
	TTabSheet *Tst_skInfo_page1_2;
	TPanel *Panel37;
	TPanel *Pnl_skInfo_tLOTBNG2;
	TPanel *Pnl_skInfo_vLOTBNG2;
	TPanel *Pnl_skInfo_tKENSA2;
	TPanel *Pnl_skInfo_vKENSA2;
	TPanel *Pnl_skInfo_tKIKI2;
	TPanel *Pnl_skInfo_vKIKI2;
	TPanel *Pnl_skInfo_tKIKAKU2;
	TPanel *Pnl_skInfo_vKIKAKU2;
	TScrollBox *SBox_skInfo_1;
	TPanel *Panel35;
	TPanel *pnlSOZAINCount;
	TPanel *Panel88;
	TPanel *pnlSOZAIMin;
	TPanel *Panel89;
	TPanel *pnlSOZAIMax;
	TPanel *Panel36;
	TPanel *pnlSOZAIAve;
	TPanel *Panel90;
	TPanel *pnlSOZAIR;
	TPanel *Panel91;
	TPanel *pnlSOZAISiguma;
	TPanel *Panel92;
	TPanel *pnlSOZAICp;
	TPanel *Panel93;
	TPanel *pnlSOZAICpk;
	TPanel *Panel94;
	TPanel *pnlSOZAIK;
	TPanel *Panel95;
	TPanel *pnlSOZAINGPercent;
	TPanel *Panel17;
	TStringGrid *SGr_tRIRE;
	TStringGrid *SGr_tSOKU;
	TPanel *Panel27;
	TPanel *Panel33;
	TScrollBox *SBx_Left_SOZAI;
	TPanel *PnlArrow;
    TPanel *Pnl_SOZAI_ORG_SUBBASE;
    TPanel *Pnl_SOZAI_ORG_INSNAME;
    TLabel *Lab_BASESOZAIKOMK_NM;
    TLabel *Lab_BASESOZAIKIKA;
    TPanel *Pnl_SOZAI_ORG_INSNUM;
    TScrollBox *SBx_Left_SYUKA;
    TPanel *Pnl_OriginalSubBase;
    TPanel *Pnl_OrgInsName;
    TLabel *Lab_BASEKOMK_NM;
    TLabel *Lab_BASEKIKA;
    TPanel *Pnl_OrgInsNum;
    TLabel *Lab_BASETANI;
    TPanel *Pnl_OrgKikiName;
        TLabel *LabBASEKIKI_NM;
	TPanel *Panel160;
	TStringGrid *SGr_tRIRE_SOZAI;
	TPanel *Panel161;
	TStringGrid *SGr_vRIRE_SOZAI;
	TPanel *Panel162;
	TStringGrid *SGr_tSOKU_SOZAI;
	TPanel *Panel163;
	TPanel *Panel164;
	TStringGrid *SGr_tRIRE_SYUKA;
	TPanel *Panel165;
	TStringGrid *SGr_vSOKU_SOZAI;
	TPanel *Panel166;
	TPanel *Panel167;
	TPanel *Panel168;
	TStringGrid *SGr_tSOKU_SYUKA;
	TPanel *Panel169;
	TStringGrid *SGr_vSOKU_SYUKA;
	TPanel *Panel170;
	TPanel *Panel5;
	TPanel *Panel6;
	TPanel *PnlBumCode;
	TPanel *PnlBumName;
	TPanel *Panel9;
	TPanel *PnlTanCode;
	TPanel *PnlTanName;
	TPanel *Panel171;
	TPanel *Panel172;
	TCheckBox *Chk_RIRE;
	TPanel *Panel173;
	TSplitter *Splitter6;
	TPanel *Panel174;
	TSplitter *Splitter7;
	TScrollBox *SBx_vRIRE_MEMO;
	TMemo *Mem_vRIRE_MEMOORG;
	TPanel *Panel175;
	TScrollBox *SBx_vSOKU_MEMO;
	TMemo *Mem_vSOKU_MEMOORG;
	TSplitter *Splitter8;
	TPanel *Panel176;
	TStringGrid *SGr_vRIRE_SYUKA;
	TComboBox *Cmb_DTKSHIN;
	TEdit *Edt_LOTNO;
	TPanel *Panel177;
	TPanel *Panel178;
	TLabel *Label77;
	TLabel *Lab_Num;
	TShape *Shp_ColorLine1;
	TShape *Shp_ColorLine2;
	TPanel *Panel179;
    TPanel *PnlGAIKAN;
	TPanel *Pnl_SOKUHAN;
	TPanel *Panel182;
	TPanel *Panel183;
	TLabel *Label79;
	TPanel *Pnl_skInfo_vHINSYU;
	TPanel *Pnl_skInfo_tHINSYU;
	TNumberEdit *Edt_RIRE_NUM;
    TQuery *Query1;
    TDatabase *Database1;
    TCheckBox *CHkSEIKANDATA;
    TQuery *Query2;
    TQuery *Query3;
    TLabel *Lab_BASEUPKIKA;
    TLabel *Lab_BASELOKIKA;
    TLabel *Lab_BASESOZAITANI;
    TLabel *Lab_BASESOZAIUPKIKA;
    TLabel *Lab_BASESOZAILOKIKA;
	TImage *ImgGlaphSOZAI;
	TLabel *Lab_skInfo_Kikaku2;
	TLabel *Lab_skInfo_KIKAKU2UP;
	TLabel *Lab_skInfo_KIKAKU2LOW;
	TLabel *Lab_skInfo_Kikaku1;
	TLabel *Lab_skInfo_KIKAKU1UP;
	TLabel *Lab_skInfo_KIKAKU1LOW;
	TPageControl *Pcl_skInfo_page2;
	TTabSheet *Tst_skInfo_page2_1;
	TPanel *Panel13;
	TImage *ImgGlaphSYUKA;
	TTabSheet *Tst_skInfo_page2_2;
	TScrollBox *SBox_skInfo_2;
	TPanel *Panel26;
	TPanel *pnlSYUKANCount;
	TPanel *Panel29;
	TPanel *pnlSYUKAMin;
	TPanel *Panel31;
	TPanel *pnlSYUKAMax;
	TPanel *Panel34;
	TPanel *pnlSYUKAAve;
	TPanel *Panel39;
	TPanel *pnlSYUKAR;
	TPanel *Panel41;
	TPanel *pnlSYUKASiguma;
	TPanel *Panel43;
	TPanel *pnlSYUKACp;
	TPanel *Panel45;
	TPanel *pnlSYUKACpk;
	TPanel *Panel47;
	TPanel *pnlSYUKAK;
	TPanel *Panel49;
	TPanel *pnlSYUKANGPercent;
	TQuery *Query4;
	TQuery *Query5;
	TQuery *Query6;
	TQuery *Query7;
	TQuery *Query8;
	TQuery *Query10;
	TMediaPlayer *MdPlayer;
	TMediaPlayer *MdPlayer2;
	TMediaPlayer *MdPlayer3;
	TShape *OldMIDASI;
	TShape *NewMIDASI;
	TPanel *Pnl_skInfo_tSOKUUSER2;
	TPanel *Pnl_skInfo_vSOKUUSER2;
	TPanel *Pnl_skInfo_tSOKUUSER1;
	TPanel *Pnl_skInfo_vSOKUUSER1;
	TPanel *Pnl_DUMMY;
	TPanel *Pnl_DUMMY2;
	TPanel *Pnl_DUMMY3;
	TPanel *Pnl_DUMMY4;
	TQuery *QueryTANTO;
	TQuery *QueryTANTO2;
        TLabel *DENYMD_SOKU;
        TLabel *DENYMD_RIRE;
	void __fastcall BtnF04Click(TObject *Sender);
	void __fastcall BtnF03Click(TObject *Sender);
	void __fastcall BtnF02Click(TObject *Sender);
	void __fastcall Pnl_skInfoResize(TObject *Sender);
	void __fastcall Panel22Resize(TObject *Sender);
	void __fastcall Panel23Resize(TObject *Sender);
	void __fastcall Panel24Resize(TObject *Sender);
	void __fastcall BtnF05Click(TObject *Sender);
	void __fastcall AllKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall AllKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnF01Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Panel14Resize(TObject *Sender);
	void __fastcall SGr_vRIRE_SOZAITopLeftChanged(TObject *Sender);
	void __fastcall SGr_vSOKU_SOZAITopLeftChanged(TObject *Sender);
	void __fastcall Panel173Resize(TObject *Sender);
	void __fastcall Panel174Resize(TObject *Sender);
	void __fastcall Panel175Resize(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnF07Click(TObject *Sender);
	void __fastcall BtnF09Click(TObject *Sender);
	void __fastcall BtnF08Click(TObject *Sender);
	void __fastcall BtnF12Click(TObject *Sender);
	void __fastcall Splitter4CanResize(TObject *Sender, int &NewSize,
          bool &Accept);
	void __fastcall SGr_vRIRE_SYUKATopLeftChanged(TObject *Sender);
	void __fastcall SGr_vSOKU_SYUKATopLeftChanged(TObject *Sender);
    void __fastcall SGr_tRIRE_SOZAIDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
    void __fastcall SGr_tRIRE_SOZAIExit(TObject *Sender);
    void __fastcall SGr_vRIRE_SOZAIExit(TObject *Sender);
    void __fastcall SGr_vSOKU_SOZAIExit(TObject *Sender);
    void __fastcall SGr_vRIRE_SYUKAExit(TObject *Sender);
    void __fastcall SGr_vSOKU_SYUKAExit(TObject *Sender);
    void __fastcall SGr_tSOKU_SOZAIDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
    void __fastcall SGr_tRIRE_SYUKADrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
    void __fastcall SGr_tSOKU_SYUKADrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
    void __fastcall SGr_tSOKU_SOZAIExit(TObject *Sender);
    void __fastcall SGr_tRIRE_SYUKAExit(TObject *Sender);
    void __fastcall SGr_tSOKU_SYUKAExit(TObject *Sender);
	void __fastcall BtnF06Click(TObject *Sender);
    bool __fastcall Set_Lot(void);          //入力ロットの取り出し
    //void __fastcall Set_GridWidth(void);    //グリッドの幅決定
    //void __fastcall Set_RotName(void);      //ロットネームの表示
    void __fastcall Set_Ins_Disp(void);
    void __fastcall SGr_vSOKU_SYUKAKeyPress(TObject *Sender, char &Key);
    void __fastcall SGr_vRIRE_SYUKAKeyPress(TObject *Sender, char &Key);
    bool __fastcall Set_DB_SOKU(void);
	bool __fastcall Set_DB_RIRE(void);
	bool __fastcall Set_DB_SOKU_SOZAI(void);
    void __fastcall BtnF11Click(TObject *Sender);
	void __fastcall Get_KSM02(void);		//得意先品番に該当する測定実績明細データの読み込み
	void __fastcall Get_RIRELOT(void);
	int __fastcall Get_GRAPHSTART_Info(int Row,int Col,int GridNo);
	void __fastcall Get_GRAPHLOT(int iGraphRow,int iGraphCol,int GridNo);
	void __fastcall SGr_vSOKU_SOZAIKeyPress(TObject *Sender, char &Key);
	void __fastcall SGr_vRIRE_SOZAIKeyPress(TObject *Sender, char &Key);
	void __fastcall AllGRID_SelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall AllGRID_DrawCell(TObject *Sender, int ACol,int ARow, TRect &Rect, TGridDrawState State);
	//bool __fastcall SD21SLOT(AnsiString sLot);
	int __fastcall SD21SLOT(AnsiString sLOT_S, AnsiString sLOT_E);
	void __fastcall Set_SYUKAJISSEKI(void);
	void __fastcall Set_RIRE_SYUKAJISSEKI(void);
	//void __fastcall Set_SOZAIJISSEKI(void);
	void __fastcall Set_RIREMEMO(void);
	void __fastcall GridSetPointMove(TObject *Sender, char Key);
	int __fastcall 	WhereGrid(void);
	void __fastcall Get_KSD91_SHUKA(void);
	void __fastcall Get_KSD91_RIREKI(void);
	void __fastcall CopyBeforeGlaph(void);
	void __fastcall DISP_SCREEN_SET(void);
	void __fastcall SCREEN_SET(void);
	void __fastcall ExtractCode(AnsiString str);
	int __fastcall 	Get_KASOUIDO_GRAPHSTART_Info(int Row,int Col,int GridNo);
	void __fastcall GetKIKAKU(int iIndex,double *dMAX,double *dMIN);
    void __fastcall GetLotKIKAKU(int iIndex,double *dMAX,double *dMIN);
	void __fastcall Get_GKIKAKU(void);
	bool __fastcall Get_KSM01(void);
	void __fastcall GET_HANTEI(TObject *Sender, int ACol);
	void __fastcall GRID_SetEditText(TObject *Sender, int ACol,int ARow, const AnsiString Value);
	void __fastcall FormEnter(TObject *Sender);
	void __fastcall BtnF10Click(TObject *Sender);
	bool __fastcall Set_DB_RIRE_SOZAI(void);
	void __fastcall Set_RIRE_SOZAIJISSEKI(void);
	void __fastcall OK_BEEP(TObject *Sender);
	void __fastcall NG_BEEP(TObject *Sender);
	void __fastcall KMCH_BEEP(TObject *Sender);
	void __fastcall Cmb_DTKSHINChange(TObject *Sender);
	void __fastcall GET_SPACE(void);
	void __fastcall SGr_tRIRE_SOZAITopLeftChanged(TObject *Sender);
	void __fastcall SGr_tRIRE_SYUKATopLeftChanged(TObject *Sender);
	void __fastcall SGr_tSOKU_SOZAITopLeftChanged(TObject *Sender);
	void __fastcall SGr_tSOKU_SYUKATopLeftChanged(TObject *Sender);
	void __fastcall SGr_vSOKU_SOZAIGetEditText(TObject *Sender, int ACol,
          int ARow, AnsiString &Value);
	void __fastcall SGr_vSOKU_SYUKAGetEditText(TObject *Sender, int ACol,
          int ARow, AnsiString &Value);
	void __fastcall SGr_vRIRE_SOZAIGetEditText(TObject *Sender, int ACol,
          int ARow, AnsiString &Value);
	void __fastcall SGr_vRIRE_SYUKAGetEditText(TObject *Sender, int ACol,
          int ARow, AnsiString &Value);
	void __fastcall SBx_vSOKU_MEMOResize(TObject *Sender);
	void __fastcall SBx_vRIRE_MEMOResize(TObject *Sender);
	void __fastcall SGr_tSOKU_SYUKASetEditText(TObject *Sender, int ACol,
          int ARow, const AnsiString Value);
	void __fastcall SGr_tRIRE_SYUKASetEditText(TObject *Sender, int ACol,
          int ARow, const AnsiString Value);
	void __fastcall SGr_tSOKU_SOZAISetEditText(TObject *Sender, int ACol,
          int ARow, const AnsiString Value);
	void __fastcall SGr_tRIRE_SOZAISetEditText(TObject *Sender, int ACol,
          int ARow, const AnsiString Value);
	AnsiString __fastcall GetTANTO(AnsiString CODE);
	AnsiString __fastcall GetTANTO2(AnsiString CODE);
	void __fastcall SET_KSD01(void);
	void __fastcall SGr_vRIRE_SYUKADblClick(TObject *Sender);
	void __fastcall Glaph_Init(void);
	bool __fastcall UPDATE_CHECK(void);
//追加コードです
	bool __fastcall ALL_RIRE_DATA( void );
	void __fastcall DynamicCtrl_Free( void );
    void __fastcall Replace_ORData(int x, int y);
    void __fastcall ORData_To_Tmp(int x);
    void __fastcall ORData_To_ORData(int x, int y);
    void __fastcall Tmp_To_ORData(int x);

    // k.k 2003.05.17
 	void __fastcall GET_SOZAI_KSM02(void);
	void __fastcall GET_SOZAI_KSD01(void);
	void __fastcall GET_SOZAI_KSD02(void);
	void __fastcall GET_SOZAI_KSD02_SECOND(void);
	void __fastcall GET_SOZAI_TANI(void);
	void __fastcall SetSYKA_Sozai(void);
	void __fastcall Set_SOZAI_GRID(void);
	void __fastcall GET_SOZAI_KSD02_DISP(void);
	void __fastcall SetRIRE_Sozai(void);
	void __fastcall SOZAI_PROCESS(void);
	void __fastcall GET_KSD22(void);
	void __fastcall GET_KSD22_AGAIN(void);
	void __fastcall GetSOZAI_KIKAKU(int iIndex,double *dMAX,double *dMIN);
	void __fastcall SET_RIRE_KSD01(void);
	void __fastcall GET_RIRE_KSD22(void);
	void __fastcall PLOT_FORM8(void);
	void __fastcall PUT_SOZAIRIRE_KSD02_DISP(void);
	void __fastcall GET_SOZAIRIRE_KSD02(void);
	void __fastcall Edt_LOTNOChange(TObject *Sender);
	void __fastcall SGr_tKeyPress(TObject *Sender, char &Key);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall SGr_vSOKU_SYUKAComPress(void);
    void __fastcall SGr_vRIRE_SYUKAComPress(void);
    void __fastcall SGr_vSOKU_SOZAIComPress(void);
    void __fastcall SGr_vRIRE_SOZAIComPress(void);
    bool __fastcall ALL_INSPECT(void);
    void __fastcall ADD_SPACE( void );
    void __fastcall Set_SOKU_SOZAIJISSEKI(void);

    int __fastcall CELL_HANTEI(TObject *Sender,int ACol,int ARow);
    void __fastcall SGr_tSOKUDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
    void __fastcall SGr_tRIREDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);

private:	// ユーザー宣言
    TWndMethod SaveSBx_Left_SOZAI_WndProc;
    TWndMethod SaveSBx_Left_SYUKA_WndProc;
    TWndMethod SaveSBx_vSOKU_MEMO_WndProc;
    TWndMethod SaveSBx_vRIRE_MEMO_WndProc;
    void __fastcall SBx_Left_SOZAI_WndProc(TMessage& msg);
    void __fastcall SBx_Left_SYUKA_WndProc(TMessage& msg);
	void __fastcall SBx_vSOKU_MEMO_WndProc(TMessage& msg);
	void __fastcall SBx_vRIRE_MEMO_WndProc(TMessage& msg);
//ディストラクション用宣言
    __fastcall ~TForm1();
    // K.K
    TStrings *sHT_LOT;
    TStrings *sShiji_Data;
    // A.T 2003/05/07 各測定Gridの最終Cellの位置
    int	iRow_vSOKU_SYUKA;
    int iCol_vSOKU_SYUKA;
    int iRow_vRIRE_SYUKA;
    int iCol_vRIRE_SYUKA;
    int iRow_vSOKU_SOZAI;
    int iCol_vSOKU_SOZAI;
    int iRow_vRIRE_SOZAI;
    int iCol_vRIRE_SOZAI;

    // k.k 2003.05.17
    void __fastcall SubSearch(AnsiString sYMD);
	void __fastcall GET_RIRE_SYUKA(void);
	void __fastcall GET_KSD01(void);
	void __fastcall Terminate(void);

public:		// ユーザー宣言
	bool bLOT_LINK;					//ロットリンクフラグ
    // A.T 2003/05/08
    bool    ThreadSupport;			//スレッドとしての動作をするかしないかを決定します
                                    // true  = スレッド動作を行ないます
                                    // false = スレッド動作を行ないません
    // 2003/06/02 A.Tamura スレッド未使用の為コメント
    /*
	TThread *SecondThread;			//スレッド①	出荷履歴読み込み等
    TThread *ThirdThread;           //スレッド② 	素材検査読み込み等
	TThread *FourThread;           	//スレッド③	測定機器との通信
    */
    TClipboard *ClpBrd;
    __fastcall TForm1(TComponent* Owner);
//ユーザー情報
	int     USER_COD;
	String  USER_NAM;
	String  BUMO_COD;
	String  BUMO_NAM;
//出荷用パネル宣言
    TPanel 	**Pnl_InsNo;
    TPanel 	**Pnl_InsName;
    TPanel 	**Pnl_InsKikiName;
    TPanel 	**Pnl_SubBase;
    TLabel 	**Lab_KOMK_NM;
    TLabel 	**Lab_TANI;
    TLabel 	**Lab_KIKA;
    TLabel 	**Lab_UPKIKA;
    TLabel 	**Lab_LOKIKA;
    TLabel 	**Lab_KIKI_NM;
    TMemo  	**Mem_vSOKU_MEMO;
//素材用パネル宣言
    TPanel 	**Pnl_SOZAI_InsNo;
    TPanel 	**Pnl_SOZAI_InsName;
    TPanel 	**Pnl_SOZAI_InsKikiName;
    TPanel 	**Pnl_SOZAI_SubBase;
    TLabel 	**Lab_SOZAI_KOMK_NM;
    TLabel 	**Lab_SOZAI_TANI;
    TLabel 	**Lab_SOZAI_KIKA;
    TLabel 	**Lab_SOZAI_UPKIKA;
    TLabel 	**Lab_SOZAI_LOKIKA;
	TMemo	**Mem_vRIRE_MEMO;
//動的パネル数（出荷用）
    int iPnl_InsNoCnt;
    int iPnl_InsNameCnt;
    int iPnl_InsKikiNameCnt;
    int iPnl_InsSubBaseCnt;
    int iRecordCount;
    int iSokuSuu;
    int iKikiCount;
    int iRotCount;                  //入力ロット数
    int iOrCnt;                     //Or表示数
    AnsiString sRots[100];          //入力ロット
    bool bKikanF[100];              //期間フラグ(true時は次のロットまでグリッドに表示)
//その他変数
    int iRIRE_CNT;
	int iOrCount;						  //ORDATA数(検査項目数)
    bool bGAIKAN_F;
    int iSOZAI_SYUKA_KOMKCNT;             //出荷検査の項目数
    int iSOZAI_RIREKI_KOMKCNT;            //履歴の項目数
    bool bGAIKAN;                         //外観検査有り／無しフラグ
    bool bCursolMove;                     //False:横方向,True:縦方向
    bool bEnterMove;                     //現在Returnキー押下処理中
	AnsiString sCommBuff;
    bool bSOZAI_NASI;                   //素材無しフラグ
	TStrings	*sRIREKI_LOT;			// 履歴ロット

    // k.k
    int iComPort;					// ポート
    time_t sTime;                   // タイムアウトチェック用
    // k.k start
    AnsiString DataReceive();
    int DataUpLoad();

    // 検索終了フラグ
    bool	bNowF7;
    bool    bNowLotF7;
//2003.05.08 E.Takase Add
    double __fastcall ConvDoubleDefD(AnsiString sTarget, double dValue);
	bool __fastcall ConvDoubleDefS(AnsiString sTarget, AnsiString sFormat, AnsiString dValue, AnsiString *sRtn);
    AnsiString __fastcall Null_S(Variant &vBuf);
//2003.05.10 A.Tamura Add
    void __fastcall Delete_InplaceEdit(TObject *Sender);		// 編集ウィンドウを無効にします

	AnsiString sNowDTKSHIN;
	AnsiString sNowLOTNO;
	bool	   bNowSEIKANDATA;
	bool	   bNowRIRE;
	int 	   iNowRIRE_NUM;


//2003.05.15 E.Takase Add
	void __fastcall ChkInputData(AnsiString sBuf, int iVALUE_TYPE, TObject *Sender, char &Key, int iLenMAX);
	AnsiString __fastcall ReplaceStrAtoB(AnsiString sMaster, AnsiString sA, AnsiString sB);
	AnsiString __fastcall CutStrLenMAX(AnsiString sMaster,int iLenMAX);
	AnsiString __fastcall CutStrEndChar(AnsiString sMaster);
//2003.05.15 k.k
    void Graph_Format();
//2003.05.17 k.k
	__fastcall ThreadRIRE_SYUKA(bool CreateSuspended);
	__fastcall ThreadSozaiMain(bool CreateSuspended);
	int iTHREAD_CNT;

//2003.05.17 E.Takase Add
	bool __fastcall ChkSize(HANDLE hChk, int iPos, long lSize);
	AnsiString __fastcall GetValidityData(AnsiString sTarget, int iLenMAX);
	void __fastcall Mem_MEMOKeyPress(TObject *Sender, char &Key);

//2003.08.26
	void __fastcall Mem_MEMOEnter(TObject *Sender);
	void __fastcall Mem_MEMOExit(TObject *Sender);
    void __fastcall BUNKATU_CHECK(void);
};



//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
