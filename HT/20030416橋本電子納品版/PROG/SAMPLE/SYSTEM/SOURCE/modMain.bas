Attribute VB_Name = "modMain"
Option Explicit

Public Sub Main()
    Dim lRet As Long
    
    '---アプリの二重起動防止機能---
    If App.PrevInstance = True Then
        lRet = MsgBox("既にシステムは起動されております｡", vbOKOnly + vbCritical, "警告ダイアログ")
        Exit Sub
    End If
    '------
    Call subStartup                                                                 'システムのスタートアップ処理
    frmMain.Show                                                                    'メイン画面の表示
End Sub

Public Sub subFinal()
    Call subCleanup                                                                 'システムのクリーンアップ
End Sub

Private Sub subStartup()
    Dim nRet As Integer
    
End Sub

Private Sub subCleanup()
    Dim nRet As Integer
    
End Sub


