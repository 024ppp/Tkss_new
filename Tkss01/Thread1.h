//---------------------------------------------------------------------------
#ifndef Thread1H
#define Thread1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class MyThread1 : public TThread
{
private:
protected:
	void __fastcall Execute();
    void __fastcall SubSearch(AnsiString sYMD);
public:
	__fastcall MyThread1(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
