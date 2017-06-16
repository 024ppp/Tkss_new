Attribute VB_Name = "modDefine"
Option Explicit

'カラー定数
Public Const COLOR_BLACK = &H0&                                 '黒色
Public Const COLOR_RED = &HFF&                                  '赤色
Public Const COLOR_GREEN = &HC000&                              '緑色
Public Const COLOR_WHITE = &HFFFFFF                             '白色
Public Const COLOR_GRAY = &H8000000F                            '灰色
Public Const COLOR_BLUE = &HFF0000                              '青色
Public Const COLOR_GREENISHBROWN = &HFF0000                     '鶯色
Public Const COLOR_LIGHTBLUE = &HFFFFC0                         '水色
Public Const COLOR_YELLOWGREEN = &HC0FFC0                       '黄緑色
Public Const COLOR_YELLOW = &HFFFF&                             '黄色
Public Const COLOR_BROWN = &H40C0&                              '茶色
Public Const COLOR_ORANGE = &HC0E0FF                            '橙色
Public Const COLOR_PINK = &HFF00FF                              '桃色
Public Const COLOR_EMERALDGREEND = &HFFFF00                     'エメラルドグリーン色
Public Const COLOR_DARKBLUE = &H800000                          '群青色
Public Const COLOR_PURPLE = &HC000C0                            '紫色

Public Const gnHeight = 9045
Public Const gnWidth = 12105

Public Const TIMEOUTTIME = 3000                                 'タイムアウト時間

Public gbSIO As Boolean                                         '通信OKフラグ

