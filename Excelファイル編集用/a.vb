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
    
        'GFlag←測定値の行が複数になった時用
'        r1 = PosRow1 + PosRow2 + PosRow3 + PosRow4 + PosRow1_2 + PosRow2_2 + GFlag
        r1 = PosRow1 + PosRow2 + PosRow4 + PosRow1_2 + PosRow2_2 + GFlag + 1
        c1 = PosCol1_2
        
        
        
        '測定項目
        If OutForm = 0 Then
            Sheets(RotNo).Range("A1").Offset(r1, c1) = KOMK_NM
        Else
            Sheets(RotNo).Range("A1").Offset(r1, c1) = KOMK_ENG
        End If
        
        '単位
        Sheets(RotNo).Range("A1").Offset(r1, c1 + 1) = TANI
        
        
        '規格小数点以下桁数の決定
        For i = 1 To KIKA_DECI
            KetaSu = KetaSu & "0"
        Next i
        
        
        
        '規格
        Select Case KIKA_TYPE
            Case 1
                Select Case KIKA_KIND
                    Case 1
                        Sheets(RotNo).Range("A1").Offset(r1, c1 + 2) = Format([KIKA_NUM1], "0." & KetaSu)
                        Sheets(RotNo).Range("A1").Offset(r1, c1 + 3) = "～"
                        Sheets(RotNo).Range("A1").Offset(r1, c1 + 4) = Format([KIKA_NUM2], "0." & KetaSu)
                    
                    Case 2
                        Sheets(RotNo).Range("A1").Offset(r1, c1 + 2) = Format([KIKA_NUM2], "0." & KetaSu)
                        Sheets(RotNo).Range("A1").Offset(r1, c1 + 3) = "以下"
                    
                    
                    Case 3
                        'TODO 2P以降、規格値欄に不要な小数点が表示される
                        Sheets(RotNo).Range("A1").Offset(r1, c1 + 2) = Format([KIKA_NUM1], "0." & KetaSu)
                        Sheets(RotNo).Range("A1").Offset(r1, c1 + 3) = "以上"
                    
                    
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
            
        'GFlag←測定値の行が複数になった時用
        r1 = (PosRow1 + PosRow2 + PosRow4) + (PosRow1_2 + PosRow2_2) * Page - 2 + GFlag
        c1 = PosCol1_2
        
        
        '補助シートのコピー
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
        
        
        '測定項目
        If OutForm = 0 Then
            Sheets(RotNo).Range("A1").Offset(r1 + 3, c1) = KOMK_NM
        Else
            Sheets(RotNo).Range("A1").Offset(r1 + 3, c1) = KOMK_ENG
        End If
        
        '単位
        Sheets(RotNo).Range("A1").Offset(r1 + 3, c1 + 1) = TANI
        
        
        '規格小数点以下桁数の決定
        For i = 1 To KIKA_DECI
            KetaSu = KetaSu & "0"
        Next i
        
        
        
        '規格
        Select Case KIKA_TYPE
            Case 1
                Select Case KIKA_KIND
                    Case 1
                        Sheets(RotNo).Range("A1").Offset(r1 + 3, c1 + 2) = Format([KIKA_NUM1], "0." & KetaSu)
                        Sheets(RotNo).Range("A1").Offset(r1 + 3, c1 + 3) = "～"
                        Sheets(RotNo).Range("A1").Offset(r1 + 3, c1 + 4) = Format([KIKA_NUM2], "0." & KetaSu)
                    
                    Case 2
                        Sheets(RotNo).Range("A1").Offset(r1 + 3, c1 + 2) = Format([KIKA_NUM2], "0." & KetaSu)
                        Sheets(RotNo).Range("A1").Offset(r1 + 3, c1 + 3) = "以下"
                    
                    
                    Case 3
                        Sheets(RotNo).Range("A1").Offset(r1 + 3, c1 + 2) = Format([KIKA_NUM1], "0." & KetaSu)
                        Sheets(RotNo).Range("A1").Offset(r1 + 3, c1 + 3) = "以上"
                    
                    
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
    


'エラー処理
Err_Rtn:
    MsgBox "例外が発生しました(Page_Cheak)"

    Page_Cheak = False
    Exit Function
        

End Function