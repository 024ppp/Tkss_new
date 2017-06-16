//---------------------------------------------------------------------------
#ifndef ThreadSozaiMainH
#define ThreadSozaiMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Clipbrd.hpp>
//---------------------------------------------------------------------------
/* k.k 2003.05.17 DELETE
class ThreadSozaiMain : public TThread
{
private:
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
	void __fastcall GetSOZAI_KIKAKU(int iIndex,double *dMAX,double *dMIN);
	void __fastcall SET_KSD01(void);
	void __fastcall SOZAI_CONTROL_DELETE( void );
	void __fastcall SET_RIRE_KSD01(void);
	void __fastcall GET_RIRE_KSD22(void);
	void __fastcall PLOT_FORM8(void);
	void __fastcall PUT_SOZAIRIRE_KSD02_DISP(void);
	void __fastcall GET_SOZAIRIRE_KSD02(void);
protected:
	void __fastcall Execute();
    void __fastcall SubSearch(AnsiString sYMD);
	void __fastcall Terminate(void);
public:
    TClipboard *ClpBrd;
	__fastcall ThreadSozaiMain(bool CreateSuspended);
//K.ICHIKAWA Rev.2003.05.10
	int iTHREAD_CNT;
// Rev.End
};
*/
//---------------------------------------------------------------------------
#endif
