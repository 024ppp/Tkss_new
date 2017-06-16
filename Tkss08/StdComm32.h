// シリアルデバイス制御
//
// StdComm32.h
//
// 1999/02/23 by teruk
//
// ソースコードは自由に修正・配布することが可能です。
// ただし、上記行為に関しては各自の責任とさせていただきます。
//

#ifndef __STDCOMM32_H__
#define __STDCOMM32_H__

#include <windows.h>
#include <stdio.h>

#define COMM_OK				(1)
#define COMM_FAILURE		(0)
#define COMM_PORTERR		(-1)
#define COMM_BAUDRATEERR	(-2)
#define COMM_CONFIGERR		(-3)
#define COMM_OPENERR		(-4)
#define COMM_TIMEOUT		(-5)

#define STX 0x2
#define ETX 0x3
#define EOT 0x4
#define ENQ 0x5
#define ACK 0x6
#define CR  0x0d
#define NAK 0x15
#define PNO1 0x31
#define PNO2 0x32
#define PNO3 0x33
#define PNO4 0x34
#define PNO5 0x35

#ifdef __cplusplus
extern "C" {
#endif

int APIENTRY CommOpen(LPCTSTR pszComPort, LPCTSTR pszBaudRate, LPCTSTR pszConfig);
int APIENTRY CommClose(int nComPort);
int APIENTRY CommClear(int nComPort);
int APIENTRY CommWrite(int nComPort, LPCTSTR pszBuffer);
int APIENTRY CommWriteChar(int nComPort, int nChar);
int APIENTRY CommRead(int nComPort, LPTSTR pszBuffer);
int APIENTRY CommReadNum(int nComPort, LPTSTR pszBuffer, DWORD dwCount);
int APIENTRY CommReadChar(int nComPort, int* pnChar);
int APIENTRY CommSetTimeouts(int nComPort, COMMTIMEOUTS timeouts);
int APIENTRY CommSetFlow(int nComPort, BOOL fOutxCtsFlow, BOOL fOutxDsrFlow, int fDtrControl, BOOL fDsrSensitivity, int fRtsControl);
int APIENTRY CommSetXonXoff(int nComPort, BOOL fTXContinueOnXoff, BOOL fOutX, BOOL fInX, WORD XonLim, WORD XoffLim);
int APIENTRY CommSetChar(int nComPort, char XonChar, char XoffChar, char ErrorChar, char EofChar, char EvtChar);

#ifdef __cplusplus
}
#endif

#endif
