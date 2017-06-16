// シリアルデバイス制御
//
// StdComm32.cpp
//
// 1999/02/23 by teruk
//
// ソースコードは自由に修正・配布することが可能です。
// ただし、上記行為に関しては各自の責任とさせていただきます。
//

#include "StdComm32.h"

#define CommGetDev(n)		(g_Comm[n-1].hDev)
#define CommGetDCB(n)		(g_Comm[n-1].dcb)
#define CommGetTimeouts(n)	(g_Comm[n-1].timeouts)

static DWORD CommThread(LPDWORD lpdwParam);

typedef struct tagCOMM
{
	HANDLE hDev;
	DCB dcb;
	COMMTIMEOUTS timeouts;
}
COMM;

#define QUEUESIZE	(4096)	// キューサイズ

#define MAX_COMM	(4)		// 通信ポート最大数

static COMM g_Comm[MAX_COMM];	// シリアルデバイス

static LPCTSTR apszComPort[] = {
	"COM1", "COM2", "COM3", "COM4", NULL
};

static LPCTSTR apszBaudRate[] = {
	"115200","57600","38400","28800","19200","14400","9600", NULL
};

static LPCTSTR apszStopBits[] = {
	"1", "1.5", "2", NULL
};

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	return 1;   // OK
}

// COMポートをオープンします
// 
// 戻値 : 1,2,3,4 = 成功 (1 = COM1)
//        -1 = ポート指定が正しくない
//        -2 = ボーレート指定が正しくない
//        -3 = コンフィグ指定が正しくない
// 引数 : pszComPort = COMポート文字列 ("COM1")
//        pszBaudRate = ボーレート文字列 ("38400")
//        pszConfig = 設定文字列 ("N,8,1" = NoParity/8bit/1stop)
int APIENTRY
CommOpen(LPCTSTR pszComPort, LPCTSTR pszBaudRate, LPCTSTR pszConfig)
{
	int i;

	// COMポート
	int nComPort = 0;

	for(i = 0; apszComPort[i] != NULL; i++)
	{
		if(lstrcmp(pszComPort, apszComPort[i]) == 0)
		{
			nComPort = i + 1;
			break;
		}
	}
	if(nComPort == 0)
	{
		return COMM_PORTERR;
	}

	// ボーレート
	DWORD dwBaudRate = 0;

	for(i = 0; apszBaudRate[i] != NULL; i++)
	{
		if(lstrcmp(pszBaudRate, apszBaudRate[i]) == 0)
		{
			sscanf(pszBaudRate, "%ld", &dwBaudRate);
			break;
		}
	}
	if(dwBaudRate == 0)
	{
		return COMM_BAUDRATEERR;
	}

	// パリティ
	int nParity;
	switch(pszConfig[0]&0xdf)
	{
	case 'N':
		nParity = NOPARITY;
		break;
	case 'E':
		nParity = EVENPARITY;
		break;
	case 'O':
		nParity = ODDPARITY;
		break;
	default:
		return COMM_CONFIGERR;
	}

	// バイトサイズ
	int nByteSize;
	char c = pszConfig[2];
	if((c < '5')||(c > '8'))
	{
		return COMM_CONFIGERR;
	}
	nByteSize = c - 0x30;

	// ストップビット
	int nStopBits = -1;
	for(i = 0; apszStopBits[i] != NULL; i++)
	{
		if(lstrcmp((pszConfig + 4), apszStopBits[i]) == 0)
		{
			nStopBits = i;
			break;
		}
	}
	if(nStopBits == -1)
	{
		return COMM_CONFIGERR;
	}

	// ポートオープン
	HANDLE h;

	h = CreateFile(pszComPort, GENERIC_READ|GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(h == INVALID_HANDLE_VALUE)
	{
		return COMM_OPENERR;
	}

	CommGetDev(nComPort) = h;

	if(!SetCommMask(h, 0))
	{
		CommClose(nComPort);
		return COMM_OPENERR;
	}

	if(!SetupComm(h, QUEUESIZE, QUEUESIZE))
	{
		CommClose(nComPort);
		return COMM_OPENERR;
	}

	// DCB設定
	DCB dcb;

	if(!GetCommState(h, &dcb))
	{
		CommClose(nComPort);
		return COMM_OPENERR;
	}

	dcb.DCBlength = sizeof(DCB);
	dcb.fBinary = TRUE;
	dcb.BaudRate = dwBaudRate;
	dcb.ByteSize = nByteSize;
	dcb.Parity = nParity;
	dcb.StopBits = nStopBits;
	dcb.fParity = (nParity == NOPARITY) ? FALSE : TRUE;
	dcb.fRtsControl = RTS_CONTROL_DISABLE;
	dcb.fDtrControl = DTR_CONTROL_DISABLE;
	dcb.fOutxCtsFlow = FALSE;
	dcb.fTXContinueOnXoff = TRUE;
	dcb.fInX = dcb.fOutX = FALSE;
	dcb.XonChar = 0x11;
	dcb.XoffChar = 0x13;
	dcb.XonLim = 100;
	dcb.XoffLim = 1500;

	if(!SetCommState(h, &dcb))
	{
		CommClose(nComPort);
		return COMM_OPENERR;
	}

	CommGetDCB(nComPort) = dcb;

	// タイムアウト設定
	COMMTIMEOUTS to;

	to.ReadIntervalTimeout = 100;		// 次のキャラクタを受信するまでのタイムアウト
	to.ReadTotalTimeoutMultiplier = 10;	// Read : 1バイトに対するタイムアウト
	to.ReadTotalTimeoutConstant = 500;	// Read : 0バイト時のタイムアウト
	to.WriteTotalTimeoutMultiplier = 10;// Write : 1バイトに対するタイムアウト
	to.WriteTotalTimeoutConstant = 500;	// Write : 0バイト時のタイムアウト

	if(!CommSetTimeouts(nComPort, to))
	{
		CommClose(nComPort);
		return COMM_OPENERR;
	}

	return nComPort;
}

// COMポートをクローズします
//
int APIENTRY
CommClose(int nComPort)
{
	if(nComPort > MAX_COMM)
		return COMM_PORTERR;

	// ポートクローズ
	CloseHandle(CommGetDev(nComPort));
	CommGetDev(nComPort) = NULL;
	return TRUE;
}

// COMポートのバッファをクリアします
//
int APIENTRY
CommClear(int nComPort)
{
	if(nComPort > MAX_COMM)
		return COMM_PORTERR;

	return PurgeComm(CommGetDev(nComPort),
		PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
}

// COMポートにデータを書き込みます
//
int APIENTRY
CommWrite(int nComPort, LPCTSTR pszBuffer)
{
	if(nComPort > MAX_COMM)
		return COMM_PORTERR;

	DWORD dwWritten;

	return WriteFile(CommGetDev(nComPort),
		pszBuffer, lstrlen(pszBuffer), &dwWritten, NULL);
}

// COMポートにデータ1バイトを書き込みます
//
int APIENTRY
CommWriteChar(int nComPort, int nChar)
{
	if(nComPort > MAX_COMM)
		return COMM_PORTERR;

	DWORD dwWritten;

	return WriteFile(CommGetDev(nComPort),
		&nChar, 1, &dwWritten, NULL);
}

// COMポートからデータを読み出します
//
int APIENTRY
CommRead(int nComPort, LPTSTR pszBuffer)
{
	if(nComPort > MAX_COMM)
		return COMM_PORTERR;

	DWORD dwError;
	COMSTAT ComStat;

	ClearCommError(CommGetDev(nComPort), &dwError, &ComStat);

	DWORD dwCount = (DWORD)ComStat.cbInQue;

	DWORD dwRead;

	if(!ReadFile(CommGetDev(nComPort),
			pszBuffer, 1, &dwRead, NULL))
	{
		return FALSE;
	}

	pszBuffer[dwRead] = 0x00;

	if(dwRead == 0)
	{
		return FALSE;
	}

	return TRUE;
}

// COMポートから指定バイト数だけデータを読み出します
//
int APIENTRY
CommReadNum(int nComPort, LPTSTR pszBuffer, DWORD dwCount)
{
	if(nComPort > MAX_COMM)
		return COMM_PORTERR;

	DWORD dwRead;

	if(!ReadFile(CommGetDev(nComPort),
			pszBuffer, 1, &dwRead, NULL))
	{
		return FALSE;
	}

	pszBuffer[dwRead] = 0x00;

	if(dwRead == 0)
	{
		return COMM_TIMEOUT;
	}

	return TRUE;
}

// COMポートから1バイトだけデータを読み出します
//
int APIENTRY
CommReadChar(int nComPort, int* pnChar)
{
	if(nComPort > MAX_COMM)
		return COMM_PORTERR;

	DWORD dwRead;

	if(!ReadFile(CommGetDev(nComPort),
			pnChar, 1, &dwRead, NULL))
	{
		return FALSE;
	}

	if(dwRead == 0)
	{
		return COMM_TIMEOUT;
	}

	return TRUE;
}

// タイムアウトを設定します
//
int APIENTRY
CommSetTimeouts(int nComPort, COMMTIMEOUTS timeouts)
{
	if(nComPort > MAX_COMM)
		return COMM_PORTERR;

	if(!SetCommTimeouts(CommGetDev(nComPort), &timeouts))
	{
		return FALSE;
	}

	CommGetTimeouts(nComPort) = timeouts;

	return TRUE;
}

// フロー制御を設定します
//
int APIENTRY
CommSetFlow(int nComPort, BOOL fOutxCtsFlow, BOOL fOutxDsrFlow, int fDtrControl, BOOL fDsrSensitivity, int fRtsControl)
{
	if(nComPort > MAX_COMM)
		return COMM_PORTERR;

	DCB dcb;

	if(!GetCommState(CommGetDev(nComPort), &dcb))
	{
		return FALSE;
	}

	dcb.fOutxCtsFlow = fOutxCtsFlow;
	dcb.fOutxDsrFlow = fOutxDsrFlow;
	dcb.fDtrControl = fDtrControl;
	dcb.fDsrSensitivity = fDsrSensitivity;
	dcb.fRtsControl = fRtsControl;

	if(!SetCommState(CommGetDev(nComPort), &dcb))
	{
		return FALSE;
	}

	CommGetDCB(nComPort) = dcb;

	return TRUE;
}

// XON/XOFFを設定します
//
int APIENTRY
CommSetXonXoff(int nComPort, BOOL fTXContinueOnXoff, BOOL fOutX, BOOL fInX, WORD XonLim, WORD XoffLim)
{
	if(nComPort > MAX_COMM)
		return COMM_PORTERR;

	DCB dcb;

	if(!GetCommState(CommGetDev(nComPort), &dcb))
	{
		return FALSE;
	}

	dcb.fTXContinueOnXoff = fTXContinueOnXoff;
	dcb.fInX = fInX;
	dcb.fOutX = fOutX;
	dcb.XonLim = XonLim;
	dcb.XoffLim = XoffLim;

	if(!SetCommState(CommGetDev(nComPort), &dcb))
	{
		return FALSE;
	}

	CommGetDCB(nComPort) = dcb;

	return TRUE;
}

// 制御キャラクタを設定します
//
int APIENTRY
CommSetChar(int nComPort, char XonChar, char XoffChar, char ErrorChar, char EofChar, char EvtChar)
{
	if(nComPort > MAX_COMM)
		return COMM_PORTERR;

	DCB dcb;

	if(!GetCommState(CommGetDev(nComPort), &dcb))
	{
		return FALSE;
	}

	dcb.XonChar = XonChar;
	dcb.XoffChar = XoffChar;
	dcb.ErrorChar = ErrorChar;
	dcb.EofChar = EofChar;
	dcb.EvtChar = EvtChar;

	if(!SetCommState(CommGetDev(nComPort), &dcb))
	{
		return FALSE;
	}

	CommGetDCB(nComPort) = dcb;

	return TRUE;
}
