Attribute VB_Name = "modSio"
Option Explicit

'�ʐM�ݒ�
Type COM
    nPort As Integer    '�g�p�|�[�g
    sLen As String      '�f�[�^��
    sBor As String      '�ʐM���x
    sStop As String     '�X�g�b�v�r�b�g
End Type
Public gtCom As COM     '�ʐM�ݒ�

'�ʐM�|�[�g������
Public Sub subSioInit()
    Dim sBuf As String
    
    '�ʐM�d�l�ݒ�
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

'�ʐM�|�[�g�I�[�v��
Public Sub subSioOpen()
    Dim lRet As Long
    
    On Error GoTo ErrorHandler                  '�G���[�������[�`�����s���܂��B
    frmMain.comHT.PortOpen = True
    gbSIO = True
    Exit Sub
ErrorHandler:
    '�G���[����
    Debug.Print Err.Number
    Debug.Print Err.Description
    If Err.Number = comPortInvalid Then   '8002:�߰Ĕԍ����s���ł��B
    
    End If
    lRet = MsgBox("�ʐM�|�[�g�I�[�v���G���[", vbCritical + vbOKOnly, "�x���_�C�A���O")
End Sub

'�ʐM�|�[�g�N���[�Y
Public Sub subSioClose()
    Dim nRet As Integer
    
    On Error GoTo ErrorHandler                  '�G���[�������[�`�����s���܂��B
    
    If gbSIO = False Then
        Exit Sub
    End If
    frmMain.comHT.PortOpen = False
    Exit Sub
ErrorHandler:
    '�G���[����
    Debug.Print Err.Number
    Debug.Print Err.Description
    If Err.Number = comNoOpen Then   '8012:���޲����J����Ă��܂���B
    
    End If
    nRet = MsgBox("�ʐM�|�[�g�N���[�Y�G���[", vbCritical + vbOKOnly, "�x���_�C�A���O")
    End
End Sub

'�ʐM�|�[�g���M
Public Function fncSioSend(sSendBuf As String) As Boolean
    Dim nRet As Integer
    
    On Error GoTo ErrorHandler                  '�G���[�������[�`�����s���܂��B
    frmMain.comHT.Output = sSendBuf
    fncSioSend = True
    Exit Function
ErrorHandler:
    '�G���[����
    Debug.Print Err.Number
    Debug.Print Err.Description
    nRet = MsgBox("�ʐM�|�[�g���M�G���[", vbCritical + vbOKOnly, "�x���_�C�A���O")
End Function

'�ʐM�|�[�g��M
Public Function fncSioRecv() As String
    Dim sRet As String
    Dim nRet As Integer
    
    On Error GoTo ErrorHandler                  '�G���[�������[�`�����s���܂��B
    If gbSIO = False Then
        Exit Function
    End If
    sRet = frmMain.comHT.Input
    fncSioRecv = sRet
    Exit Function
ErrorHandler:
    '�G���[����
    Debug.Print Err.Number
    Debug.Print Err.Description
    nRet = MsgBox("�ʐM�|�[�g��M�G���[", vbCritical + vbOKOnly, "�x���_�C�A���O")
End Function

'�ʐM�|�[�g���Z�b�g
Public Sub subSioRest()
    Dim sRet As String
    Dim nRet As Integer
    
    On Error GoTo ErrorHandler                  '�G���[�������[�`�����s���܂��B
    frmMain.comHT.InBufferCount = 0
    Exit Sub
ErrorHandler:
    '�G���[����
    Debug.Print Err.Number
    Debug.Print Err.Description
    nRet = MsgBox("�ʐM�|�[�g���Z�b�g�G���[", vbCritical + vbOKOnly, "�x���_�C�A���O")
End Sub

'�ʐM�|�[�g��M�o�b�t�@�`�F�b�N
Public Function fncSioRecvLen() As Integer
    Dim nRet As Integer
    
    On Error GoTo ErrorHandler                  '�G���[�������[�`�����s���܂��B
    If gbSIO = False Then
        Exit Function
    End If
    nRet = frmMain.comHT.InBufferCount
    fncSioRecvLen = nRet
    Exit Function
ErrorHandler:
    '�G���[����
    Debug.Print Err.Number
    Debug.Print Err.Description
    nRet = MsgBox("�ʐM�|�[�g��M�o�b�t�@�`�F�b�N�G���[", vbCritical + vbOKOnly, "�x���_�C�A���O")
End Function

'�a�b�b�̐���
Public Function fncBCC(s1 As String) As String
    Dim n1 As Integer
    Dim l2 As Long
    
    l2 = Asc(Mid(s1, 1, 1))
    For n1 = 2 To Len(s1)
        l2 = l2 + Asc(Mid(s1, n1, 1))
    Next n1
    fncBCC = Right("0" & Hex(l2), 2)        '�P�U�i���ɕϊ�
End Function

'�ʐM�|�[�g��M
Public Function fncSioRecvEx() As String
    Dim sRet  As String
    Dim nRet As Integer
    Dim nSW As Integer
    Dim sRecvBuf As String
    Dim saRet(10)  As String
    Dim nLen As Integer
    Dim sCmd As String
    
    On Error GoTo ErrorHandler                  '�G���[�������[�`�����s���܂��B
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
    '�G���[����
    Debug.Print Err.Number
    Debug.Print Err.Description
    nRet = MsgBox("�ʐM�|�[�g��M�G���[", vbCritical + vbOKOnly, "�x���_�C�A���O")
End Function
