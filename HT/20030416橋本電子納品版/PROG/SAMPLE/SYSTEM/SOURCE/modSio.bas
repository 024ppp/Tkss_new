Attribute VB_Name = "modSio"
Option Explicit

'通信設定
Type COM
    nPort As Integer    '使用ポート
    sLen As String      'データ長
    sBor As String      '通信速度
    sStop As String     'ストップビット
End Type
Public gtCom As COM     '通信設定

'通信ポート初期化
Public Sub subSioInit()
    Dim sBuf As String
    
    '通信仕様設定
    gtCom.nPort = 1
    gtCom.sLen = 8
    gtCom.sBor = 38400 '19200
    gtCom.sStop = 1
    sBuf = gtCom.sBor & ",N," & gtCom.sLen & "," & gtCom.sStop
    frmMain.comHT.CommPort = gtCom.nPort
    frmMain.comHT.Settings = sBuf
'    frmMain.comHT.Handshaking = comRTSXOnXOff
    frmMain.comHT.Handshaking = comRTS
End Sub

'通信ポートオープン
Public Sub subSioOpen()
    Dim lRet As Long
    
    On Error GoTo ErrorHandler                  'エラー処理ルーチンを行います。
    frmMain.comHT.PortOpen = True
    gbSIO = True
    Exit Sub
ErrorHandler:
    'エラー処理
    Debug.Print Err.Number
    Debug.Print Err.Description
    If Err.Number = comPortInvalid Then   '8002:ﾎﾟｰﾄ番号が不正です。
    
    End If
    lRet = MsgBox("通信ポートオープンエラー", vbCritical + vbOKOnly, "警告ダイアログ")
End Sub

'通信ポートクローズ
Public Sub subSioClose()
    Dim nRet As Integer
    
    On Error GoTo ErrorHandler                  'エラー処理ルーチンを行います。
    
    If gbSIO = False Then
        Exit Sub
    End If
    frmMain.comHT.PortOpen = False
    Exit Sub
ErrorHandler:
    'エラー処理
    Debug.Print Err.Number
    Debug.Print Err.Description
    If Err.Number = comNoOpen Then   '8012:ﾃﾞﾊﾞｲｽが開かれていません。
    
    End If
    nRet = MsgBox("通信ポートクローズエラー", vbCritical + vbOKOnly, "警告ダイアログ")
    End
End Sub

'通信ポート送信
Public Function fncSioSend(sSendBuf As String) As Boolean
    Dim nRet As Integer
    
    On Error GoTo ErrorHandler                  'エラー処理ルーチンを行います。
    frmMain.comHT.Output = sSendBuf
    fncSioSend = True
    Exit Function
ErrorHandler:
    'エラー処理
    Debug.Print Err.Number
    Debug.Print Err.Description
    nRet = MsgBox("通信ポート送信エラー", vbCritical + vbOKOnly, "警告ダイアログ")
End Function

'通信ポート受信
Public Function fncSioRecv() As String
    Dim sRet As String
    Dim nRet As Integer
    
    On Error GoTo ErrorHandler                  'エラー処理ルーチンを行います。
    If gbSIO = False Then
        Exit Function
    End If
    sRet = frmMain.comHT.Input
    fncSioRecv = sRet
    Exit Function
ErrorHandler:
    'エラー処理
    Debug.Print Err.Number
    Debug.Print Err.Description
    nRet = MsgBox("通信ポート受信エラー", vbCritical + vbOKOnly, "警告ダイアログ")
End Function

'通信ポートリセット
Public Sub subSioRest()
    Dim sRet As String
    Dim nRet As Integer
    
    On Error GoTo ErrorHandler                  'エラー処理ルーチンを行います。
    frmMain.comHT.InBufferCount = 0
    Exit Sub
ErrorHandler:
    'エラー処理
    Debug.Print Err.Number
    Debug.Print Err.Description
    nRet = MsgBox("通信ポートリセットエラー", vbCritical + vbOKOnly, "警告ダイアログ")
End Sub

'通信ポート受信バッファチェック
Public Function fncSioRecvLen() As Integer
    Dim nRet As Integer
    
    On Error GoTo ErrorHandler                  'エラー処理ルーチンを行います。
    If gbSIO = False Then
        Exit Function
    End If
    nRet = frmMain.comHT.InBufferCount
    fncSioRecvLen = nRet
    Exit Function
ErrorHandler:
    'エラー処理
    Debug.Print Err.Number
    Debug.Print Err.Description
    nRet = MsgBox("通信ポート受信バッファチェックエラー", vbCritical + vbOKOnly, "警告ダイアログ")
End Function

'ＢＣＣの生成
Public Function fncBCC(s1 As String) As String
    Dim n1 As Integer
    Dim l2 As Long
    
    l2 = Asc(Mid(s1, 1, 1))
    For n1 = 2 To Len(s1)
        l2 = l2 + Asc(Mid(s1, n1, 1))
    Next n1
    fncBCC = Right("0" & Hex(l2), 2)        '１６進数に変換
End Function

'通信ポート受信
Public Function fncSioRecvEx() As String
    Dim sRet  As String
    Dim nRet As Integer
    Dim nSW As Integer
    Dim sRecvBuf As String
    Dim saRet(10)  As String
    Dim nLen As Integer
    Dim sCmd As String
    
    On Error GoTo ErrorHandler                  'エラー処理ルーチンを行います。
    frmMain.comHT.InputLen = 1
    nSW = 10
    frmMain.comHT.RTSEnable = True
    Do
        saRet(0) = frmMain.comHT.Input
        Select Case nSW
        Case 10:
            If saRet(0) = Chr(&H2) Then
                sRecvBuf = saRet(0)
                nSW = nSW + 1
            End If
        Case 11:
            If saRet(0) = "1" Or saRet(0) = "2" Then
                sRecvBuf = sRecvBuf & saRet(0)
                nSW = nSW + 1
            End If
        Case 12:
            If saRet(0) = "A" Or saRet(0) = "D" Or saRet(0) = "R" Or saRet(0) = "S" Or saRet(0) = "M" Then
                sRecvBuf = sRecvBuf & saRet(0)
                nSW = nSW + 1
            End If
        Case 13:
            If saRet(0) = Chr(&H3) Then
                sRecvBuf = sRecvBuf & saRet(0)
                nSW = nSW + 1
            Else
                sRecvBuf = sRecvBuf & saRet(0)
            End If
        Case 14:
            nSW = 20
        Case 20:
            Exit Do
        End Select
        DoEvents
    Loop
    frmMain.comHT.RTSEnable = False
    fncSioRecvEx = sRecvBuf
    Exit Function
ErrorHandler:
    'エラー処理
    Debug.Print Err.Number
    Debug.Print Err.Description
    nRet = MsgBox("通信ポート受信エラー", vbCritical + vbOKOnly, "警告ダイアログ")
End Function
