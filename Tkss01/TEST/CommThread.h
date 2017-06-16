//---------------------------------------------------------------------------
#ifndef CommThreadH
#define CommThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class CommThread : public TThread
{
private:
	void __fastcall NG_BEEP(void);
	void __fastcall OK_BEEP(void);
protected:
	void __fastcall Execute();
public:
	__fastcall CommThread(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
