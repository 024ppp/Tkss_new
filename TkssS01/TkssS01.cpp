#include <SysUtils.hpp>
#include <SvcMgr.hpp>
#pragma hdrstop
#define Application Svcmgr::Application
USERES("TkssS01.res");
USEFORM("Unit1.cpp", ServiceTkssS01); /* TService: DesignClass */
USEFILE("Main.h");
USEUNIT("Unit2.cpp");
USEUNIT("Unit3.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->Title = "’†ŠÔŒŸ¸DB‚©‚ço‰×ŒŸ¸DB‚Ö‚ÌˆÚs";
        Application->CreateForm(__classid(TServiceTkssS01), &ServiceTkssS01);
         Application->Run();
	}
	catch (Exception &exception)
	{
		Sysutils::ShowException(&exception, Sysutils::ExceptAddr());
	}
	return 0;
}
