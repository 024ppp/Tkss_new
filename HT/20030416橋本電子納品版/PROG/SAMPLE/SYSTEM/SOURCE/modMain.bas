Attribute VB_Name = "modMain"
Option Explicit

Public Sub Main()
    Dim lRet As Long
    
    '---�A�v���̓�d�N���h�~�@�\---
    If App.PrevInstance = True Then
        lRet = MsgBox("���ɃV�X�e���͋N������Ă���܂��", vbOKOnly + vbCritical, "�x���_�C�A���O")
        Exit Sub
    End If
    '------
    Call subStartup                                                                 '�V�X�e���̃X�^�[�g�A�b�v����
    frmMain.Show                                                                    '���C����ʂ̕\��
End Sub

Public Sub subFinal()
    Call subCleanup                                                                 '�V�X�e���̃N���[���A�b�v
End Sub

Private Sub subStartup()
    Dim nRet As Integer
    
End Sub

Private Sub subCleanup()
    Dim nRet As Integer
    
End Sub


