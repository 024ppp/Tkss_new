//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <SvcMgr.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
//---------------------------------------------------------------------------
class TServiceTkssS01 : public TService
{
__published:    // IDE 管理のコンポーネント
	TDatabase *Database1;
	TQuery *Query1;
	TQuery *Q_KSD21;
	TQuery *Q_KSD22;
	TQuery *Q_KSD23;
	TQuery *Q_KD_1;
	TQuery *Q_KD_2;
	void __fastcall Service1Start(TService *Sender, bool &Started);
	void __fastcall Service1Continue(TService *Sender, bool &Continued);
	void __fastcall Service1Pause(TService *Sender, bool &Paused);
	void __fastcall Service1Stop(TService *Sender, bool &Stopped);
private:        // ユーザー宣言
public:         // ユーザー宣言
    int __fastcall GetKSD29(AnsiString strFUNC_ID);
	__fastcall TServiceTkssS01(TComponent* Owner);
	PServiceController __fastcall GetServiceController(void);

	friend void __stdcall ServiceController(unsigned CtrlCode);
};
class TSparkyThread : public TThread

{
private:
protected:
      void __fastcall Execute();
public:
		__fastcall TSparkyThread(bool CreateSuspended);
	AnsiString __fastcall SetKSD29(AnsiString strFUNC_ID,AnsiString strUPDYMD);

	int __fastcall AutoEntry();
    int __fastcall GetKSD29(AnsiString strFUNC_ID);
    int __fastcall GetDTKS(void);
	AnsiString __fastcall GetKEIJYO_KBN(void);
	void __fastcall FormatFixStr(void);

	void __fastcall FormatKSD21(int iNo);
	void __fastcall FormatKSD22(int iNo);
	void __fastcall FormatKSD23(int iNo);

	int __fastcall GetKD_1(int iNo);
	int __fastcall SrchKD_1(int iNo);
	int __fastcall SrchKD_2(int iNo);
	int __fastcall SrchKSD21(int iNo);
	int __fastcall SrchKSD22(int iNo);
	int __fastcall SrchKSD23(int iNo);

	void __fastcall SetKD_1(int iNo);
	void __fastcall SetKD_2(int iNo);
	void __fastcall SetKSD21(int iNo);
	void __fastcall SetKSD22(int iNo);

	void __fastcall CalcKD_1(int iNo);

	//データベース更新関係（Unit2）
	AnsiString __fastcall AddDataKSD21(void);
	AnsiString __fastcall UpdDataKSD21(void);

	AnsiString __fastcall AddDataKSD22(void);
	AnsiString __fastcall UpdDataKSD22(void);

	AnsiString __fastcall AddDataKSD23(int iPos);
	AnsiString __fastcall DelDataKSD23(void);

	AnsiString __fastcall UpdDataKSD21_UPDCNT(AnsiString swDTKSHIN,AnsiString swHINBAN,AnsiString swLOTNO);

	AnsiString __fastcall Null_S(Variant &vBuf);
	AnsiString __fastcall InsMEMO(AnsiString strM, int iNo, AnsiString strA);

	void __fastcall WriteErrLog(AnsiString sErrLog,  AnsiString sePrg,
								AnsiString seDTKSHIN,AnsiString seHINBAN,AnsiString seLOTNO);//ログを出力

		
};


//---------------------------------------------------------------------------
extern PACKAGE TServiceTkssS01 *ServiceTkssS01;
//---------------------------------------------------------------------------
#endif
