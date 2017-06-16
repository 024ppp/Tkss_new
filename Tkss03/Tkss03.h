//備考事前登録データ
struct KSD91_DATA {
	AnsiString	KENSA_YMD;		//	検査年月日
	AnsiString	DTKSHIN;		//	得意先品番
	AnsiString	HINBAN;			//	自社品番
	AnsiString	LOTNO;          //  ロットNo
	AnsiString	ADDYMD;			//	登録日
	AnsiString	ADDTIM;			//	登録時間
	AnsiString	UPDYMD;			//	変更日
	AnsiString	UPDTIM;			//	変更時間
	int	     	UPDCHR;			//	更新者
	int	     	UPDCNT;			//	更新回数
    AnsiString  MEMO;           //  備考
};

extern int     SEQNOMAX;
extern int     USER_COD;
extern String  USER_NAM;
extern String  BUMO_COD;
extern String  BUMO_NAM;
extern bool    DataSave;
extern int     KENSAKU_Mode;           // 一覧検索モード
                                       // １：検査予定日
                                       // ２：得意先品番
                                       // ３：ロットNO
/*
// extern KSD91_DATA Tmp_KSD91;           // 選択した備考事前登録データ

*/
