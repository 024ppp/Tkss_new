Public Function Page_Cheak() As Boolean

Dim r1 As Integer
Dim c1 As Integer
Dim KetaSu As String
Dim blnRtn As Boolean

On Error GoTo Err_Rtn


'If intPage <> Page Then
'    GFlag = 0
'End If


    If Page = 1 Then
    
        'GFlag������l�̍s�������ɂȂ������p
'        r1 = PosRow1 + PosRow2 + PosRow3 + PosRow4 + PosRow1_2 + PosRow2_2 + GFlag
        r1 = PosRow1 + PosRow2 + PosRow4 + PosRow1_2 + PosRow2_2 + GFlag + 1
        c1 = PosCol1_2
        
        
        
        '���荀��
        If OutForm = 0 Then
            Sheets(RotNo).Range("A1").Offset(r1, c1) = KOMK_NM
        Else
            Sheets(RotNo).Range("A1").Offset(r1, c1) = KOMK_ENG
        End If
        
        '�P��
        Sheets(RotNo).Range("A1").Offset(r1, c1 + 1) = TANI
        
        
        '�K�i�����_�ȉ������̌���
        For i = 1 To KIKA_DECI
            KetaSu = KetaSu & "0"
        Next i
        
        
        
        '�K�i
        Select Case KIKA_TYPE
            Case 1
                Select Case KIKA_KIND
                    Case 1
                        Sheets(RotNo).Range("A1").Offset(r1, c1 + 2) = Format([KIKA_NUM1], "0." & KetaSu)
                        Sheets(RotNo).Range("A1").Offset(r1, c1 + 3) = "�`"
                        Sheets(RotNo).Range("A1").Offset(r1, c1 + 4) = Format([KIKA_NUM2], "0." & KetaSu)
                    
                    Case 2
                        Sheets(RotNo).Range("A1").Offset(r1, c1 + 2) = Format([KIKA_NUM2], "0." & KetaSu)
                        Sheets(RotNo).Range("A1").Offset(r1, c1 + 3) = "�ȉ�"
                    
                    
                    Case 3
                        'TODO 2P�ȍ~�A�K�i�l���ɕs�v�ȏ����_���\�������
                        Sheets(RotNo).Range("A1").Offset(r1, c1 + 2) = Format([KIKA_NUM1], "0." & KetaSu)
                        Sheets(RotNo).Range("A1").Offset(r1, c1 + 3) = "�ȏ�"
                    
                    
                End Select
                
            Case 2
                Select Case KIKA_KIND
                    Case 1
                        Sheets(RotNo).Range("A1").Offset(r1, c1 + 2) = Format([KIKA_NUM1], "0." & KetaSu)
                        Sheets(RotNo).Range("A1").Offset(r1 - 1, c1 + 4) = Format([KIKA_NUM2], "0." & KetaSu)
                        Sheets(RotNo).Range("A1").Offset(r1, c1 + 4) = Format([KIKA_NUM3], "0." & KetaSu)
                    
                    
                    Case 2
                        Sheets(RotNo).Range("A1").Offset(r1, c1 + 2) = Format([KIKA_NUM1], "0." & KetaSu)
                        Sheets(RotNo).Range("A1").Offset(r1 - 1, c1 + 4) = Format([KIKA_NUM2], "0." & KetaSu)
                    
                    
                    Case 3
                        Sheets(RotNo).Range("A1").Offset(r1, c1 + 2) = Format([KIKA_NUM1], "0." & KetaSu)
                        Sheets(RotNo).Range("A1").Offset(r1, c1 + 4) = Format([KIKA_NUM3], "0." & KetaSu)
                    
                    
                End Select
                
                
            Case 3
                Sheets(RotNo).Range("A1").Offset(r1, c1 + 2) = KIKA_STR
                
        End Select
        
    '    Page = 2
    
    
    ElseIf Page > 1 Then
            
        'GFlag������l�̍s�������ɂȂ������p
        r1 = (PosRow1 + PosRow2 + PosRow4) + (PosRow1_2 + PosRow2_2) * Page - 2 + GFlag
        c1 = PosCol1_2
        
        
        '�⏕�V�[�g�̃R�s�[
        If intPage = 1 Then
        
            Sheets(DrawSheetSub).Select
            Rows("1:83").Select
            Selection.Copy
            Sheets(RotNo).Select
            Range("A1").Offset(r1, c1).Select
            ActiveSheet.Paste
            Range("A1").Select
            Sheets(DrawSheetSub).Select
            Application.CutCopyMode = False
            Range("A1").Select
            Sheets(RotNo).Select
            
        End If
        
        
        '���荀��
        If OutForm = 0 Then
            Sheets(RotNo).Range("A1").Offset(r1 + 3, c1) = KOMK_NM
        Else
            Sheets(RotNo).Range("A1").Offset(r1 + 3, c1) = KOMK_ENG
        End If
        
        '�P��
        Sheets(RotNo).Range("A1").Offset(r1 + 3, c1 + 1) = TANI
        
        
        '�K�i�����_�ȉ������̌���
        For i = 1 To KIKA_DECI
            KetaSu = KetaSu & "0"
        Next i
        
        
        
        '�K�i
        Select Case KIKA_TYPE
            Case 1
                Select Case KIKA_KIND
                    Case 1
                        Sheets(RotNo).Range("A1").Offset(r1 + 3, c1 + 2) = Format([KIKA_NUM1], "0." & KetaSu)
                        Sheets(RotNo).Range("A1").Offset(r1 + 3, c1 + 3) = "�`"
                        Sheets(RotNo).Range("A1").Offset(r1 + 3, c1 + 4) = Format([KIKA_NUM2], "0." & KetaSu)
                    
                    Case 2
                        Sheets(RotNo).Range("A1").Offset(r1 + 3, c1 + 2) = Format([KIKA_NUM2], "0." & KetaSu)
                        Sheets(RotNo).Range("A1").Offset(r1 + 3, c1 + 3) = "�ȉ�"
                    
                    
                    Case 3
                        Sheets(RotNo).Range("A1").Offset(r1 + 3, c1 + 2) = Format([KIKA_NUM1], "0." & KetaSu)
                        Sheets(RotNo).Range("A1").Offset(r1 + 3, c1 + 3) = "�ȏ�"
                    
                    
                End Select
                
            Case 2
                Select Case KIKA_KIND
                    Case 1
                        Sheets(RotNo).Range("A1").Offset(r1 + 3, c1 + 2) = Format([KIKA_NUM1], "0." & KetaSu)
                        Sheets(RotNo).Range("A1").Offset(r1 + 2, c1 + 4) = Format([KIKA_NUM2], "0." & KetaSu)
                        Sheets(RotNo).Range("A1").Offset(r1 + 3, c1 + 4) = Format([KIKA_NUM3], "0." & KetaSu)
                    
                    
                    Case 2
                        Sheets(RotNo).Range("A1").Offset(r1 + 3, c1 + 2) = Format([KIKA_NUM1], "0." & KetaSu)
                        Sheets(RotNo).Range("A1").Offset(r1 + 2, c1 + 4) = Format([KIKA_NUM2], "0." & KetaSu)
                    
                    
                    Case 3
                        Sheets(RotNo).Range("A1").Offset(r1 + 3, c1 + 2) = Format([KIKA_NUM1], "0." & KetaSu)
                        Sheets(RotNo).Range("A1").Offset(r1 + 3, c1 + 4) = Format([KIKA_NUM3], "0." & KetaSu)
                    
                    
                End Select
                
                
            Case 3
                Sheets(RotNo).Range("A1").Offset(r1 + 3, c1 + 2) = KIKA_STR
                
        End Select
    

'Page = Page + 1
    

End If

    
   
    
    Page_Cheak = True
    
    Exit Function
    


'�G���[����
Err_Rtn:
    MsgBox "��O���������܂���(Page_Cheak)"

    Page_Cheak = False
    Exit Function
        

End Function