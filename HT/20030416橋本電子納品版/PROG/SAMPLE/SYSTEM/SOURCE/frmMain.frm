VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Begin VB.Form frmMain 
   BorderStyle     =   1  '固定(実線)
   Caption         =   "メイン画面"
   ClientHeight    =   8670
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   12015
   ControlBox      =   0   'False
   BeginProperty Font 
      Name            =   "ＭＳ ゴシック"
      Size            =   12
      Charset         =   128
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "frmMain.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   ScaleHeight     =   8670
   ScaleWidth      =   12015
   Begin VB.CheckBox chkBcc 
      Caption         =   "BCCﾁｪｯｸ"
      Height          =   255
      Left            =   240
      TabIndex        =   12
      Top             =   7200
      Width           =   1575
   End
   Begin MSComDlg.CommonDialog dlgSijiDataRef 
      Left            =   2160
      Top             =   7560
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin MSComDlg.CommonDialog dlgMasterDataRef 
      Left            =   1560
      Top             =   7560
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.ListBox lstSijiData 
      Height          =   2700
      Left            =   240
      TabIndex        =   11
      Top             =   4320
      Width           =   11055
   End
   Begin VB.ListBox lstMasterData 
      Height          =   2700
      Left            =   240
      TabIndex        =   10
      Top             =   840
      Width           =   11055
   End
   Begin VB.CommandButton cmdSijiDataReceive 
      Caption         =   "受信"
      Height          =   375
      Left            =   10560
      TabIndex        =   9
      Top             =   3720
      Width           =   735
   End
   Begin VB.CommandButton cmdSijiDataRef 
      Caption         =   "参照"
      Height          =   375
      Left            =   9720
      TabIndex        =   8
      Top             =   3720
      Width           =   735
   End
   Begin VB.CommandButton cmdMasterDataSend 
      Caption         =   "送信"
      Height          =   375
      Left            =   10560
      TabIndex        =   7
      Top             =   240
      Width           =   735
   End
   Begin VB.CommandButton cmdMasterDataRef 
      Caption         =   "参照"
      Height          =   375
      Left            =   9720
      TabIndex        =   6
      Top             =   240
      Width           =   735
   End
   Begin MSCommLib.MSComm comHT 
      Left            =   840
      Top             =   7560
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
   End
   Begin VB.Timer tmrTimer 
      Interval        =   10
      Left            =   240
      Top             =   7680
   End
   Begin VB.CommandButton cmdEnd 
      Caption         =   "終了"
      Height          =   615
      Left            =   10200
      TabIndex        =   1
      Top             =   7440
      Width           =   1575
   End
   Begin MSComctlLib.StatusBar sbrStatus 
      Align           =   2  '下揃え
      Height          =   375
      Left            =   0
      TabIndex        =   0
      Top             =   8295
      Width           =   12015
      _ExtentX        =   21193
      _ExtentY        =   661
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   1
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
         EndProperty
      EndProperty
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "ＭＳ ゴシック"
         Size            =   12
         Charset         =   128
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin VB.Label labSijiDataDileSavePath 
      Appearance      =   0  'ﾌﾗｯﾄ
      BackColor       =   &H80000005&
      BorderStyle     =   1  '実線
      ForeColor       =   &H80000008&
      Height          =   375
      Left            =   4320
      TabIndex        =   5
      Top             =   3720
      Width           =   5295
   End
   Begin VB.Label labMasterDataDileSavePath 
      Appearance      =   0  'ﾌﾗｯﾄ
      BackColor       =   &H80000005&
      BorderStyle     =   1  '実線
      ForeColor       =   &H80000008&
      Height          =   375
      Left            =   4320
      TabIndex        =   4
      Top             =   240
      Width           =   5295
   End
   Begin VB.Label Label2 
      Caption         =   "指示データファイル保存先パス："
      Height          =   255
      Left            =   240
      TabIndex        =   3
      Top             =   3840
      Width           =   3615
   End
   Begin VB.Label Label1 
      Caption         =   "マスターデータファイル保存先パス："
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   360
      Width           =   4095
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim mnSW As Integer
Dim mbSendFlag As Boolean
Dim mbReceiveFlag As Boolean
Dim mlRec As Long
Dim mnFileNo As Integer
Dim mdteStart As Date
Dim mlTimeStart As Long

Private Sub cmdEnd_Click()
    Call subFinal
    Unload Me
End Sub

Private Sub cmdMasterDataRef_Click()
    Dim nRet As Integer
    Dim sPath As String
    
    On Error GoTo ErrorHandler                  'エラー処理ルーチンを行います。
    With dlgMasterDataRef
        .DialogTitle = "パラメータファイル保存先パス選択画面"
        .DefaultExt = ".dat"
        .Filter = "パラメータファイル(*.dat)|*.dat"
        .InitDir = labMasterDataDileSavePath.Caption
        .Flags = cdlOFNPathMustExist Or cdlOFNHideReadOnly
        .FileName = "master.dat"
        .CancelError = True
        .ShowSave
        sPath = Left(.FileName, Len(.FileName) - Len(.FileTitle))
    End With
    labMasterDataDileSavePath.Caption = sPath
    Call subMasterDataListSet
    Exit Sub
ErrorHandler:
    'エラー処理
    Debug.Print Err.Number
    Debug.Print Err.Description
End Sub

Private Sub cmdMasterDataSend_Click()
    Dim sFileName As String
    Dim lRet As Long
    Dim fso1 As New FileSystemObject
    
    sFileName = labMasterDataDileSavePath.Caption & "\master.dat"
    If sFileName = "" Or fso1.FileExists(sFileName) = False Then
        lRet = MsgBox("正しいパスを設定して下さい。", vbOKOnly + vbExclamation, "警告ダイアログ")
        Set fso1 = Nothing
        Exit Sub
    End If
    sbrStatus.Panels.Item(1).Text = ""
    mbSendFlag = True
    Set fso1 = Nothing
End Sub

Private Sub cmdSijiDataReceive_Click()
    Dim sFileName As String
    Dim lRet As Long
    Dim fso1 As New FileSystemObject
    
    sFileName = labSijiDataDileSavePath.Caption & "\sijidata.dat"
    If sFileName = "" Or fso1.FileExists(sFileName) = False Then
        lRet = MsgBox("正しいパスを設定して下さい。", vbOKOnly + vbExclamation, "警告ダイアログ")
        Set fso1 = Nothing
        Exit Sub
    End If
    sbrStatus.Panels.Item(1).Text = ""
    mbReceiveFlag = True
    Set fso1 = Nothing
End Sub

Private Sub cmdSijiDataRef_Click()
    Dim nRet As Integer
    Dim sPath As String
    
    On Error GoTo ErrorHandler                  'エラー処理ルーチンを行います。
    With dlgSijiDataRef
        .DialogTitle = "パラメータファイル保存先パス選択画面"
        .DefaultExt = ".dat"
        .Filter = "パラメータファイル(*.dat)|*.dat"
        .InitDir = labSijiDataDileSavePath.Caption
        .Flags = cdlOFNPathMustExist Or cdlOFNHideReadOnly
        .FileName = "sijidata.dat"
        .CancelError = True
        .ShowSave
        sPath = Left(.FileName, Len(.FileName) - Len(.FileTitle))
    End With
    labSijiDataDileSavePath.Caption = sPath
    Exit Sub
ErrorHandler:
    'エラー処理
    Debug.Print Err.Number
    Debug.Print Err.Description
End Sub

Private Sub Form_Load()
    With Me   '---ﾌｫｰﾑを中央に表示---
        .Height = gnHeight
        .Width = gnWidth
        .Top = (Screen.Height - .Height) / 2
        .Left = (Screen.Width - .Width) / 2
    End With
    Call subInitStatus
    mnSW = 0
    mbSendFlag = False
    mbReceiveFlag = False
End Sub

Private Sub subInitStatus()
   Dim i As Integer
   Dim pnlX As Panel
   
   ' 変数を宣言します。
   For i = 1 To 4   '４個のパネルを追加します。
      Set pnlX = sbrStatus.Panels.Add()
   Next i

   ' 各パネルのスタイルを設定します。
   With sbrStatus.Panels
      .Item(1).Width = Me.Width - 4500
      .Item(1).Text = ""
      .Item(2).Width = 1500
      .Item(2).Text = ""
      .Item(3).Width = 1500
      .Item(3).Style = sbrDate ' 日付を表示するように設定します。
      .Item(4).Width = 1500
      .Item(4).Style = sbrTime ' 時刻を表示するように設定します。
   End With
End Sub

Private Sub subMasterDataListSet()
    Dim nFileNo As Integer
    Dim fso1 As New FileSystemObject
    Dim sFileName As String
    Dim lRet As Long
    Dim s1 As String
    
    On Error GoTo ErrorHandler                                      'エラー処理ルーチンを行います。
    sFileName = labMasterDataDileSavePath.Caption & "\master.dat"
    If fso1.FileExists(sFileName) = False Then
        Exit Sub
    End If
    nFileNo = FreeFile
    Open sFileName For Input As #nFileNo
    lstMasterData.Clear
    lstMasterData.Visible = False
    Do
        If EOF(nFileNo) = True Then
            Exit Do
        End If
        Line Input #nFileNo, s1
        lstMasterData.AddItem s1
        DoEvents
    Loop
    lstMasterData.Visible = True
    sbrStatus.Panels.Item(1).Text = "マスターデータを " & lstMasterData.ListCount & " 件読込みました。"
    Close #nFileNo
    Exit Sub
ErrorHandler:
    'エラー処理
    Debug.Print Err.Number
    Debug.Print Err.Description
End Sub

Private Sub subSijiDataListSet()
    Dim nFileNo As Integer
    Dim fso1 As New FileSystemObject
    Dim sFileName As String
    Dim lRet As Long
    Dim s1 As String
    
    On Error GoTo ErrorHandler                                      'エラー処理ルーチンを行います。
    sFileName = labSijiDataDileSavePath.Caption & "\sijidata.dat"
    If fso1.FileExists(sFileName) = False Then
        Exit Sub
    End If
    nFileNo = FreeFile
    Open sFileName For Input As #nFileNo
    lstSijiData.Clear
    lstSijiData.Visible = False
    Do
        If EOF(nFileNo) = True Then
            Exit Do
        End If
        Line Input #nFileNo, s1
        lstSijiData.AddItem s1
        DoEvents
    Loop
    lstSijiData.Visible = True
    Close #nFileNo
    Exit Sub
ErrorHandler:
    'エラー処理
    Debug.Print Err.Number
    Debug.Print Err.Description
End Sub

Private Sub tmrTimer_Timer()
    Dim sRet As String
    Dim bRet As Boolean
    Dim sCmd As String
    Dim sFileName As String
    Dim s1 As String
    
    Select Case mnSW
    Case 0:
        mnSW = 10
    Case 10:
        If mbSendFlag = True Then
            'ダウンロード
#If nDEBUG Then
#Else
            Call subSioInit
            Call subSioOpen
#End If
            mbSendFlag = False
            mnSW = 100
        End If
        If mbReceiveFlag = True Then
            'アップロード
#If nDEBUG Then
#Else
            Call subSioInit
            Call subSioOpen
#End If
            mbReceiveFlag = False
            mnSW = 200
        End If
    Case 100:
        sCmd = Chr(&H2) & "1D"
        If chkBcc.Value = vbChecked Then
            sCmd = sCmd & fncBCC(sCmd)
        Else
            sCmd = sCmd & "**"
        End If
        sCmd = sCmd & Chr(&H3)
#If nDEBUG Then
#Else
        Call subSioRest
        Debug.Print sCmd
        bRet = fncSioSend(sCmd)   'ダウンロード・コマンド送信
#End If
        mlTimeStart = timeGetTime
        mnSW = 110
    Case 110:
        If (timeGetTime - mlTimeStart) >= 1000 Then
            'タイムアウト(1S)
            sbrStatus.Panels.Item(1).Text = "タイムアウト"
            mnSW = 999
        End If
#If nDEBUG Then
        If True Then
#Else
        If fncSioRecvLen > 0 Then
#End If
            mnSW = 120
        End If
    Case 120:
#If nDEBUG Then
        If True Then
#Else
        sRet = fncSioRecvEx         'レスポンス受信
        If Mid(sRet, 4, 1) = Chr(&H6) Then
#End If
            'ACK受信
            mnSW = 130
        Else
            'NAK受信
            mnSW = 999
        End If
    Case 130:
        'マスターデータ送信
        mdteStart = Time
        sFileName = labMasterDataDileSavePath.Caption & "\master.dat"
        mnFileNo = FreeFile
        Open sFileName For Input As #mnFileNo
        mlRec = 0
        mnSW = 140
    Case 140:
        If EOF(mnFileNo) = True Then
            sCmd = Chr(&H2) & "1M00000"
            s1 = Space(32)
            mnSW = 150
        Else
            mlRec = mlRec + 1
            sCmd = Chr(&H2) & "1M" & Format(mlRec, "00000")
            Line Input #mnFileNo, s1
            mlTimeStart = timeGetTime
            mnSW = 145
        End If
'        Debug.Print s1
        sCmd = sCmd & s1
        If chkBcc.Value = vbChecked Then
            sCmd = sCmd & fncBCC(sCmd)
        Else
            sCmd = sCmd & "**"
        End If
        sCmd = sCmd & Chr(&H3)
#If nDEBUG Then
#Else
        Call subSioRest
        Debug.Print sCmd
        bRet = fncSioSend(sCmd)   'マスターデータ・コマンド送信
#End If
    Case 145:
        If (timeGetTime - mlTimeStart) >= 1000 Then
            'タイムアウト(1S)
            sbrStatus.Panels.Item(1).Text = "タイムアウト"
            Close #mnFileNo
            mnSW = 999
        End If
#If nDEBUG Then
        If True Then
#Else
        If fncSioRecvLen > 0 Then
#End If
            mnSW = 146
        End If
    Case 146:
#If nDEBUG Then
        If True Then
#Else
        sRet = fncSioRecvEx         'レスポンス受信
        If Mid(sRet, 4, 1) = Chr(&H6) Then
#End If
            'ACK受信
            mnSW = 140
        Else
            'NAK受信
            mnSW = 999
        End If
    
    Case 150:
        Close #mnFileNo
        sbrStatus.Panels.Item(1).Text = "マスターデータ送信転送時間(s)：" & Format(DateDiff("s", mdteStart, Time), "0")
        mlTimeStart = timeGetTime
        mnSW = 160
    Case 160:
        If (timeGetTime - mlTimeStart) >= 1000 Then
            'タイムアウト(1S)
            sbrStatus.Panels.Item(1).Text = "タイムアウト"
            mnSW = 999
        End If
#If nDEBUG Then
        If True Then
#Else
        If fncSioRecvLen > 0 Then
#End If
            mnSW = 170
        End If
    Case 170:
#If nDEBUG Then
        If True Then
#Else
        sRet = fncSioRecvEx         'レスポンス受信
        If Mid(sRet, 4, 1) = Chr(&H6) Then
#End If
            'ACK受信
            mnSW = 999
        Else
            'NAK受信
            mnSW = 999
        End If
    
    Case 200:
        sCmd = Chr(&H2) & "1A"
        If chkBcc.Value = vbChecked Then
            sCmd = sCmd & fncBCC(sCmd)
        Else
            sCmd = sCmd & "**"
        End If
        sCmd = sCmd & Chr(&H3)
#If nDEBUG Then
#Else
        Call subSioRest
        bRet = fncSioSend(sCmd)   'アップロード・コマンド送信
#End If
        mlTimeStart = timeGetTime
        mnSW = 210
    Case 210:
        If (timeGetTime - mlTimeStart) >= 1000 Then
            'タイムアウト(1S)
            sbrStatus.Panels.Item(1).Text = "タイムアウト"
            mnSW = 999
        End If
#If nDEBUG Then
        If True Then
#Else
        If fncSioRecvLen > 0 Then
#End If
            mnSW = 220
        End If
    Case 220:
#If nDEBUG Then
        If True Then
#Else
        sRet = fncSioRecvEx         'レスポンス受信
        If Mid(sRet, 4, 1) = Chr(&H6) Then
#End If
            'ACK受信
            mlTimeStart = timeGetTime
            mnSW = 230
        Else
            'NAK受信
            mnSW = 999
        End If
    Case 230:
        If (timeGetTime - mlTimeStart) >= 1000 Then
            'タイムアウト(1S)
            sbrStatus.Panels.Item(1).Text = "タイムアウト"
            mnSW = 999
        End If
#If nDEBUG Then
        If True Then
#Else
        If fncSioRecvLen > 0 Then
#End If
            mnSW = 240
        End If
    Case 240:
        '指示データ受信
        mdteStart = Time
        sFileName = labSijiDataDileSavePath.Caption & "\sijidata.dat"
        mnFileNo = FreeFile
        Open sFileName For Output As #mnFileNo
        mlRec = 0
        mlTimeStart = timeGetTime
        mnSW = 250
    Case 250:
        If (timeGetTime - mlTimeStart) >= 1000 Then
            'タイムアウト(1S)
            sbrStatus.Panels.Item(1).Text = "タイムアウト"
            Close #mnFileNo
            mnSW = 999
        End If
#If nDEBUG Then
        If True Then
#Else
        If fncSioRecvLen > 0 Then
#End If
            mnSW = 260
        End If
    Case 260:
#If nDEBUG Then
        sRet = Chr(&H2) & "2S00000" & Space(32) & "**" & Chr(&H3)
#Else
        sRet = fncSioRecvEx
#End If
        mlRec = Val(Mid(sRet, 4, 5))
        If mlRec <> 0 Then
            Print #mnFileNo, Mid(sRet, 9, 32)
        End If
        mnSW = 270
    Case 270:
        sCmd = Chr(&H2) & "1R" & Chr(&H6)
        If chkBcc.Value = vbChecked Then
            sCmd = sCmd & fncBCC(sCmd)
        Else
            sCmd = sCmd & "**"
        End If
        sCmd = sCmd & Chr(&H3)
#If nDEBUG Then
#Else
        Call subSioRest
        bRet = fncSioSend(sCmd)
#End If
        If mlRec <> 0 Then
            mlTimeStart = timeGetTime
            mnSW = 250
        Else
            mnSW = 280
        End If
    Case 280:
        Close #mnFileNo
        sbrStatus.Panels.Item(1).Text = "指示データ受信転送時間(s)：" & Format(DateDiff("s", mdteStart, Time), "0")
        Call subSijiDataListSet
        mnSW = 999
    
    Case 999:    '終了処理
#If nDEBUG Then
#Else
        Call subSioClose
#End If
        mnSW = 10
    End Select
End Sub
