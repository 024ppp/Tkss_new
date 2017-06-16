Public Function Draw_DetTitle() As Boolean

Dim r1 As Integer
Dim c1 As Integer
Dim KetaSu As String
Dim blnRtn As Boolean
'2004.06.08 E.Takase âûã}èàíu
'Dim strA, strB As String
Dim strA, strB


On Error GoTo Err_Rtn


'éØï NOÇ™9ÇÃèÍçáãÛîí
If SKB_NO <> 9 Then

    'GFlagÅ©ë™íËílÇÃçsÇ™ï°êîÇ…Ç»Ç¡ÇΩéûóp
    r1 = PosRow1 + PosRow2 + 2 + GFlag - 1
    c1 = PosCol1
    
    
    'ÉyÅ[ÉWÉ`ÉFÉbÉN
    If r1 >= PosRow1 + PosRow2 + PosRow3 Then
        blnRtn = Page_Cheak()
        If (blnRtn = False) Then
            Exit Function
        End If
        
    Else
        Page = 1
        
        
        'ë™íËçÄñ⁄
        If OutForm = 0 Then
            Sheets(RotNo).Range("A1").Offset(r1, c1) = KOMK_NM
        Else
            Sheets(RotNo).Range("A1").Offset(r1, c1) = KOMK_ENG
        End If
            
        'íPà 
        Sheets(RotNo).Range("A1").Offset(r1, c1 + 1) = TANI
            
            
        'ãKäiè¨êîì_à»â∫åÖêîÇÃåàíË
        For i = 1 To KIKA_DECI
            KetaSu = KetaSu & "0"
        Next i
            
        
        
            
            'ãKäi
            Select Case KIKA_TYPE
                Case 1
                    Select Case KIKA_KIND
                        Case 1
                            If VALUE_TYPE = 1 Then
                                Sheets(RotNo).Range("A1").Offset(r1, c1 + 2) = Conv_Angle_Kika(KIKA_NUM1)
                                Sheets(RotNo).Range("A1").Offset(r1, c1 + 3) = "Å`"
                                Sheets(RotNo).Range("A1").Offset(r1, c1 + 4) = Conv_Angle_Kika(KIKA_NUM2)
                            Else
                                Sheets(RotNo).Range("A1").Offset(r1, c1 + 2) = IIf(KIKA_DECI = 0, CLng(KIKA_NUM1), Format([KIKA_NUM1], "0." & KetaSu))
                                Sheets(RotNo).Range("A1").Offset(r1, c1 + 3) = "Å`"
                                Sheets(RotNo).Range("A1").Offset(r1, c1 + 4) = IIf(KIKA_DECI = 0, CLng(KIKA_NUM2), Format([KIKA_NUM2], "0." & KetaSu))
                            End If
                            
                        Case 2
                            If VALUE_TYPE = 1 Then
                                Sheets(RotNo).Range("A1").Offset(r1, c1 + 2) = Conv_Angle_Kika(KIKA_NUM2)

                            Else
                                Sheets(RotNo).Range("A1").Offset(r1, c1 + 2) = IIf(KIKA_DECI = 0, CLng(KIKA_NUM2), Format([KIKA_NUM2], "0." & KetaSu))
                            End If
                            
                            If OutForm = 0 Then
                                Sheets(RotNo).Range("A1").Offset(r1, c1 + 4) = "à»â∫"
                            Else
                                Sheets(RotNo).Range("A1").Offset(r1, c1 + 4) = "MAX"
                            End If
                            
                            
                            
                        Case 3
                            If VALUE_TYPE = 1 Then
                                Sheets(RotNo).Range("A1").Offset(r1, c1 + 2) = Conv_Angle_Kika(KIKA_NUM1)
                            Else
                                Sheets(RotNo).Range("A1").Offset(r1, c1 + 2) = IIf(KIKA_DECI = 0, CLng(KIKA_NUM1), Format([KIKA_NUM1], "0." & KetaSu))
                            End If

                            If OutForm = 0 Then
                                Sheets(RotNo).Range("A1").Offset(r1, c1 + 4) = "à»è„"
                            Else
                                Sheets(RotNo).Range("A1").Offset(r1, c1 + 4) = "MIN"
                            End If
                            
                            
                    End Select
                    
                    'ÉZÉãÇÃåãçá
                    Sheets(RotNo).Select
                    Range(Cells(r1 + 1, 5), Cells(r1 + 2, 5)).Select
                    With Selection
                        .HorizontalAlignment = xlLeft
                        .VerticalAlignment = xlCenter
                        .WrapText = False
                        .Orientation = 0
                        .AddIndent = False
                        .ShrinkToFit = True
                        .MergeCells = True
                    End With
                    
                        
                Case 2
                    Select Case KIKA_KIND
                        Case 1
                            If VALUE_TYPE = 1 Then
                                Sheets(RotNo).Range("A1").Offset(r1, c1 + 2) = Conv_Angle_Kika([KIKA_NUM1])
                            Else
                                Sheets(RotNo).Range("A1").Offset(r1, c1 + 2) = IIf([KIKA_NUM1] = 0, 0, IIf(KIKA_DECI = 0, CLng(KIKA_NUM1), Format([KIKA_NUM1], "0." & KetaSu)))
                            End If
                            
                            If KIKA_PRT <> 0 Then
                                If VALUE_TYPE = 1 Then
                                    strA = IIf([KIKA_NUM2] = 0, 0, Conv_Angle_Kika([KIKA_NUM2]))
                                    strB = IIf([KIKA_NUM3] = 0, 0, Conv_Angle_Kika([KIKA_NUM3]))
                                Else
                                    strA = IIf([KIKA_NUM2] = 0, 0, IIf(KIKA_DECI = 0, CLng(KIKA_NUM2), Format([KIKA_NUM2], "0." & KetaSu)))
                                    strB = IIf([KIKA_NUM3] = 0, 0, IIf(KIKA_DECI = 0, CLng(KIKA_NUM3), Format([KIKA_NUM3], "0." & KetaSu)))
                                End If
                                
'2003/08/29í«â¡Å´Å´Å´/////////////////////////////////////////////////
                                'ÇOÇÃèÍçáÅAêÊì™Ç…îºäpÉXÉyÅ[ÉXÇÇ¬ÇØÇÈ
                                'ÇOà»è„ÇÃèÍçá§êÊì™Ç…Åh+ÅhÇÇ¬ÇØÇÈ
                                'ÇOà»â∫ÇÃèÍçáÅAÇªÇÃÇ‹Ç‹ï\é¶Ç∑ÇÈ
                                If strA = 0 Then
                                    strA = Space(1) & strA
                                ElseIf strA > 0 Then
                                    strA = "+" & strA
                                ElseIf strA < 0 Then
                                    strA = strA
                                End If
                                
                                
                                
                                If strB = 0 Then
                                    strB = Space(1) & strB
                                ElseIf strB > 0 Then
                                    strB = "+" & strB
                                ElseIf strB < 0 Then
                                    strB = strB
                                End If
'2003/08/29í«â¡Å™Å™Å™//////////////////////////////////////////////////
                                
                                
                                
                                Sheets(RotNo).Range("A1").Offset(r1, c1 + 4) = strA
                                Sheets(RotNo).Range("A1").Offset(r1 + 1, c1 + 4) = strB
                            End If
                            
                        Case 2
                            If VALUE_TYPE = 1 Then
                                Sheets(RotNo).Range("A1").Offset(r1, c1 + 2) = Conv_Angle_Kika([KIKA_NUM1])
                            Else
                                Sheets(RotNo).Range("A1").Offset(r1, c1 + 2) = IIf([KIKA_NUM1] = 0, 0, IIf(KIKA_DECI = 0, CLng(KIKA_NUM1), Format([KIKA_NUM1], "0." & KetaSu)))
                            End If
                            
                             If KIKA_PRT <> 0 Then
                                If VALUE_TYPE = 1 Then
                                    strA = Conv_Angle_Kika([KIKA_NUM2])
                                Else
                                    strA = IIf([KIKA_NUM2] = 0, 0, IIf(KIKA_DECI = 0, CLng(KIKA_NUM2), Format([KIKA_NUM2], "0." & KetaSu)))
                                End If
                                
                                If strA > 0 Then
                                    strA = "+" & strA
                                ElseIf strA < 0 Then
                                    strA = strA
                                End If
                                
                                
                                Sheets(RotNo).Range("A1").Offset(r1, c1 + 4) = strA
                             End If
                            
                        Case 3
                            If VALUE_TYPE = 1 Then
                                Sheets(RotNo).Range("A1").Offset(r1, c1 + 2) = Conv_Angle_Kika([KIKA_NUM1])
                            Else
                                Sheets(RotNo).Range("A1").Offset(r1, c1 + 2) = IIf([KIKA_NUM1] = 0, 0, IIf(KIKA_DECI = 0, CLng(KIKA_NUM1), Format([KIKA_NUM1], "0." & KetaSu)))
                            End If
                            
                            If KIKA_PRT <> 0 Then
                                If VALUE_TYPE = 1 Then
                                    strA = IIf([KIKA_NUM3] = 0, 0, Conv_Angle_Kika([KIKA_NUM3]))
                                Else
                                    strA = IIf([KIKA_NUM3] = 0, 0, IIf(KIKA_DECI = 0, CLng(KIKA_NUM3), Format([KIKA_NUM3], "0." & KetaSu)))
                                End If
                                
                                If strA > 0 Then
                                    strA = "+" & strA
                                ElseIf strA < 0 Then
                                    strA = strA
                                End If
                                
                                Sheets(RotNo).Range("A1").Offset(r1 + 1, c1 + 4) = strA
                            End If
                            
                            
                    End Select
                        
                        
                Case 3
                    Sheets(RotNo).Range("A1").Offset(r1, c1 + 2) = KIKA_STR
                    Range(Cells(r1 + 1, c1 + 3), Cells(r1 + 1, c1 + 5)).Select
                    With Selection
                        .HorizontalAlignment = xlCenter
                        .VerticalAlignment = xlCenter
                        .WrapText = False
                        .Orientation = 0
                        .AddIndent = False
                        .ShrinkToFit = True
                        .MergeCells = True
                    End With
                        
            End Select
            
        
    End If
        
End If

   
    
    Draw_DetTitle = True
    
    Exit Function
    


'ÉGÉâÅ[èàóù
Err_Rtn:
    MsgBox "ó·äOÇ™î≠ê∂ÇµÇ‹ÇµÇΩ(Draw_DetTitle)"

    Draw_DetTitle = False
    Exit Function


End Function