object Form1: TForm1
  Left = 0
  Top = 0
  Caption = #1051#1072#1073#1086#1088#1072#1090#1086#1088#1085#1072#1103' 2 '
  ClientHeight = 618
  ClientWidth = 1053
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  OnPaint = FormPaint
  PixelsPerInch = 96
  TextHeight = 13
  object Label2: TLabel
    Left = 8
    Top = 8
    Width = 125
    Height = 13
    Caption = #1042#1072#1088#1080#1072#1085#1090' 6 - (d) (a) (c) (b)'
  end
  object Label3: TLabel
    Left = 8
    Top = 27
    Width = 67
    Height = 13
    Caption = #1057#1077#1088#1075#1077#1077#1074' '#1051'.'#1040'.'
  end
  object Label4: TLabel
    Left = 8
    Top = 244
    Width = 110
    Height = 13
    Caption = #1043#1088#1072#1085#1080#1095#1085#1099#1077' '#1079#1085#1072#1095#1077#1085#1080#1103':'
  end
  object Label5: TLabel
    Left = 8
    Top = 263
    Width = 6
    Height = 13
    Caption = #1061
  end
  object Label6: TLabel
    Left = 384
    Top = 560
    Width = 124
    Height = 13
    Caption = #1050#1086#1101#1092'. '#1084#1072#1089#1096#1090#1072#1073#1080#1088#1086#1074#1072#1085#1080#1103
  end
  object LVecOP: TLabel
    Left = 167
    Top = 560
    Width = 46
    Height = 13
    Caption = #1058#1086#1095#1082#1072' 1: '
  end
  object LTurn: TLabel
    Left = 911
    Top = 557
    Width = 37
    Height = 13
    Caption = #1058#1086#1095#1082#1072': '
  end
  object Label8: TLabel
    Left = 911
    Top = 577
    Width = 75
    Height = 13
    Caption = #1059#1075#1086#1083' '#1087#1086#1074#1086#1088#1086#1090#1072
  end
  object LReflection: TLabel
    Left = 679
    Top = 560
    Width = 40
    Height = 13
    Caption = #1042#1077#1082#1090#1086#1088':'
  end
  object Label7: TLabel
    Left = 75
    Top = 263
    Width = 6
    Height = 13
    Caption = 'Y'
  end
  object SpeedButton1: TSpeedButton
    Left = 442
    Top = 492
    Width = 295
    Height = 26
    AllowAllUp = True
    GroupIndex = 1
    Caption = #1044#1080#1085#1072#1084#1080#1095#1077#1089#1082#1072#1103' '#1074#1080#1079#1091#1072#1083#1080#1079#1072#1094#1080#1103
  end
  object Label9: TLabel
    Left = 167
    Top = 579
    Width = 43
    Height = 13
    Caption = #1058#1086#1095#1082#1072' 2:'
  end
  object CAxis: TCheckBox
    Left = 8
    Top = 151
    Width = 97
    Height = 17
    Caption = #1054#1089#1080
    Checked = True
    State = cbChecked
    TabOrder = 0
  end
  object CGrid: TCheckBox
    Left = 8
    Top = 110
    Width = 137
    Height = 17
    Caption = #1050#1086#1086#1088#1076#1080#1085#1072#1090#1085#1072#1103' '#1089#1077#1090#1082#1072
    Checked = True
    State = cbChecked
    TabOrder = 1
  end
  object CScale: TCheckBox
    Left = 8
    Top = 189
    Width = 137
    Height = 17
    Caption = #1052#1072#1089#1096#1090#1072#1073#1085#1072#1103' '#1083#1080#1085#1077#1081#1082#1072
    Checked = True
    State = cbChecked
    TabOrder = 2
  end
  object EScaleX: TEdit
    Left = 20
    Top = 259
    Width = 34
    Height = 21
    TabOrder = 3
    Text = '6'
    OnChange = EScaleXChange
  end
  object EScaleY: TEdit
    Left = 87
    Top = 259
    Width = 34
    Height = 21
    TabOrder = 4
    Text = '6'
    OnChange = EScaleYChange
  end
  object Panel1: TPanel
    Left = 135
    Top = 8
    Width = 914
    Height = 478
    TabOrder = 6
    object Image: TImage
      Left = 4
      Top = 0
      Width = 450
      Height = 473
      OnMouseDown = ImageMouseDown
    end
    object ImageRe: TImage
      Left = 460
      Top = 0
      Width = 450
      Height = 473
    end
  end
  object EOXrate: TEdit
    Left = 384
    Top = 575
    Width = 54
    Height = 21
    TabOrder = 5
    Text = '1'
  end
  object RBInput: TRadioButton
    Left = 8
    Top = 326
    Width = 113
    Height = 17
    Caption = #1042#1074#1086#1076' '#1092#1080#1075#1091#1088#1099
    Checked = True
    TabOrder = 7
    TabStop = True
  end
  object RBVecOP: TRadioButton
    Left = 167
    Top = 537
    Width = 113
    Height = 17
    Caption = #1055#1077#1088#1077#1085#1086#1089
    TabOrder = 8
    OnClick = RBVecOPClick
  end
  object RBScaling: TRadioButton
    Left = 384
    Top = 537
    Width = 113
    Height = 17
    Caption = #1052#1072#1089#1096#1090#1072#1073#1080#1088#1086#1074#1072#1085#1080#1077
    TabOrder = 9
  end
  object RBTurn: TRadioButton
    Left = 911
    Top = 537
    Width = 113
    Height = 17
    Caption = #1055#1086#1074#1086#1088#1086#1090
    TabOrder = 10
    OnClick = RBTurnClick
  end
  object ETurn: TEdit
    Left = 911
    Top = 592
    Width = 54
    Height = 21
    TabOrder = 11
    Text = '45'
    OnChange = ETurnChange
  end
  object RBReflection: TRadioButton
    Left = 679
    Top = 537
    Width = 113
    Height = 17
    Caption = #1054#1090#1088#1072#1078#1077#1085#1080#1077
    TabOrder = 12
  end
  object StringGrid: TStringGrid
    Left = 5
    Top = 431
    Width = 124
    Height = 71
    ColCount = 3
    DefaultColWidth = 40
    DefaultRowHeight = 20
    DoubleBuffered = True
    FixedCols = 0
    RowCount = 3
    FixedRows = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goTabs]
    ParentColor = True
    ParentDoubleBuffered = False
    ScrollBars = ssNone
    TabOrder = 13
  end
  object Button1: TButton
    Left = 134
    Top = 492
    Width = 298
    Height = 25
    Caption = #1053#1086#1074#1072#1103' '#1092#1080#1075#1091#1088#1072
    TabOrder = 14
    OnClick = Button1Click
  end
  object BCalc: TButton
    Left = 68
    Top = 400
    Width = 61
    Height = 25
    Caption = #1056#1072#1089#1095#1105#1090
    TabOrder = 15
    OnClick = BCalcClick
  end
  object BInputM: TButton
    Left = 8
    Top = 400
    Width = 54
    Height = 25
    Caption = #1042#1099#1074#1086#1076
    TabOrder = 16
    OnClick = BInputMClick
  end
  object RBMatrix: TRadioButton
    Left = 8
    Top = 377
    Width = 113
    Height = 17
    Caption = #1055#1086' '#1084#1072#1090#1088#1080#1094#1077
    TabOrder = 17
    OnClick = RBTurnClick
  end
  object Button2: TButton
    Left = 745
    Top = 492
    Width = 295
    Height = 25
    Caption = #1057#1073#1088#1086#1089' '#1074#1080#1079#1091#1072#1083#1080#1079#1072#1094#1080#1080
    TabOrder = 18
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 444
    Top = 572
    Width = 64
    Height = 25
    Caption = #1042#1074#1077#1089#1090#1080
    TabOrder = 19
    Visible = False
    OnClick = Button3Click
  end
  object Timer1: TTimer
    Interval = 500
    OnTimer = Timer1Timer
    Left = 8
    Top = 512
  end
end
