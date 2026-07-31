Option Explicit

' RES remote enclosure generator for CATIA V5-6R2022.
' Units are millimetres. The script attaches to the currently running CATIA.
' It creates a new timestamped output folder on every run and never overwrites
' an earlier generated model.

Const PI = 3.14159265358979

Dim CATIA_APP, FSO, OUTPUT_DIR

' --------------------------- USER PARAMETERS ----------------------------
Dim BODY_L, BODY_W, BODY_H, WALL, BOTTOM_T, TOP_T, BAT_COVER_T
Dim OUTER_R, CAVITY_L, CAVITY_W, TOP_OPEN_L, TOP_OPEN_W
Dim RESIN_CLEARANCE, LIP_T, LIP_H
Dim SEAL25_GROOVE_W, SEAL25_GROOVE_D
Dim TOP_NECK_H, CAP_SKIRT_T, CAP_SKIRT_H, CAP_INNER_L, CAP_INNER_W
Dim TOP_NECK_L, TOP_NECK_W, SIDE_SCREW_Z, SIDE_BOSS_D, SIDE_BOSS_DEPTH, SIDE_BOSS_NOSE
Dim TOP_INSERT_POCKET_D
Dim SIDE_SLOT_L, SIDE_SLOT_W, TOP_SCREW_SEAT_D, TOP_SCREW_SEAT_DEPTH
Dim TOP_GASKET_T, TOP_GASKET_COMP_T, TOP_GASKET_OUTER_L, TOP_GASKET_OUTER_W
Dim TOP_GASKET_INNER_L, TOP_GASKET_INNER_W, PANEL_SEAL_PAD_H, SMA_SEAL_PAD_H
Dim BAT_LAB_GROOVE_W, BAT_LAB_GROOVE_D, BAT_LAB_LIP_T, BAT_LAB_LIP_H
Dim BAT_LAB_CL_L, BAT_LAB_CL_W
Dim BAT_SCREW_SEAT_DEPTH, BAT_SCREW_SEAT_D
Dim BAT_LAB_BACKUP_H, BAT_LAB_BACKUP_W, BAT_GROOVE_BACKUP_H, BAT_GROOVE_BACKUP_W
Dim WALL_RELIEF_D, WALL_RELIEF_CELL_X, WALL_RELIEF_CELL_Z
Dim PLATE_L, PLATE_W, PLATE_T
Dim SUPPORT_X, SUPPORT_Y, SUPPORT_TOP_Z, SUPPORT_BASE_H, SUPPORT_BASE_D
Dim SUPPORT_COLLAR_H, SUPPORT_COLLAR_D, SUPPORT_POST_D
Dim ISOLATOR_INSERT_POCKET_D
Dim ISOLATOR_D, ISOLATOR_H, ISOLATOR_STUD_L
Dim INSERT_HOLE_D, INSERT_ENTRY_D, INSERT_ENTRY_DEPTH, INSERT_L
Dim COVER_HOLE_D, M4_COVER_SCREW_L, TOP_BOSS_D, BOTTOM_BOSS_D, BOTTOM_BOSS_H
Dim BOSS_RIB_SPAN, BOSS_RIB_T, SIDE_RIB_DEPTH, BOTTOM_RIB_H
Dim HANDLE_CENTER_Y, HANDLE_CENTER_Z, HANDLE_BASE_L, HANDLE_BASE_H
Dim HANDLE_INSERT_D, HANDLE_INSERT_L, HANDLE_INSERT_POCKET_D, HANDLE_ENTRY_D, HANDLE_ENTRY_DEPTH
Dim HANDLE_BOSS_D, HANDLE_BOSS_DEPTH
Dim STRAP_CENTER_Y, STRAP_CENTER_Z
Dim SMA_X, SMA_Z, SMA_HOLE_D, SMA_RECESS_D
Dim BAT_L, BAT_W, BAT_H, BAT_SLOT_L, BAT_SLOT_W, BAT_SLOT_H
Dim BAT_TRAY_WALL, BAT_TRAY_ROOF_T, BAT_OPEN_L, BAT_OPEN_W, BAT_COVER_L, BAT_COVER_W

BODY_L = 188
BODY_W = 150
BODY_H = 68
WALL = 4
BOTTOM_T = 3.6
TOP_T = 3.2
BAT_COVER_T = 3.0
OUTER_R = 10

CAVITY_L = BODY_L - 2 * WALL       ' 180
CAVITY_W = BODY_W - 2 * WALL       ' 142
TOP_OPEN_L = 170
TOP_OPEN_W = 132

RESIN_CLEARANCE = 0.9              ' per side; includes allowance for large-part SLA warp
SEAL25_GROOVE_W = 3.4
SEAL25_GROOVE_D = 1.9
LIP_T = 2.5
LIP_H = 2.5

' Full rain skirt: the lid keeps the original 188 x 150 mm envelope, while
' the upper 10 mm of the main housing steps inward. Ten horizontal M4 screws
' sit outside the primary O-ring and terminate in blind side bosses.
TOP_NECK_H = 10
CAP_SKIRT_T = 3
TOP_GASKET_T = 3.0
TOP_GASKET_COMP_T = 2.3
CAP_SKIRT_H = TOP_NECK_H + TOP_GASKET_COMP_T
CAP_INNER_L = BODY_L - 2 * CAP_SKIRT_T
CAP_INNER_W = BODY_W - 2 * CAP_SKIRT_T
TOP_NECK_L = CAP_INNER_L - 2 * RESIN_CLEARANCE
TOP_NECK_W = CAP_INNER_W - 2 * RESIN_CLEARANCE
' D11 side boss at Z62 keeps its top at Z67.5, 0.5 mm below the Z68 seal.
' Removing the cover counterbore leaves 1.5-1.7 mm solid skirt below the slot.
SIDE_SCREW_Z = 62
SIDE_BOSS_D = 11
SIDE_BOSS_DEPTH = 12
' A 0.4 mm external circular nose leaves 0.5 mm nominal skirt clearance.
' Each insert pocket is cut once from the outer nose face; no pocket seam is
' allowed at the neck plane.
SIDE_BOSS_NOSE = 0.4
TOP_INSERT_POCKET_D = 8.5
SIDE_SLOT_L = 5.0
SIDE_SLOT_W = 4.6
TOP_SCREW_SEAT_D = 11
TOP_SCREW_SEAT_DEPTH = 0

' A die-cut flat silicone gasket replaces the tolerance-sensitive O-ring
' groove. Its 4 mm ring sits on a full-thickness 5.1 mm land. The skirt bottom
' contacts the housing shoulder when the 3 mm sheet reaches 2.3 mm. With a
' +/-0.4 mm two-part stack, compression remains approximately 10 to 37%.
TOP_GASKET_OUTER_L = 179
TOP_GASKET_OUTER_W = 141
TOP_GASKET_INNER_L = 171
TOP_GASKET_INNER_W = 133
PANEL_SEAL_PAD_H = 0.8
SMA_SEAL_PAD_H = 1.0

' Bottom battery-cover labyrinth. The 2 mm wall enters a 3.4 mm x 2 mm groove,
' giving 0.7 mm clearance per side. It is outside every screw and the O-ring.
BAT_LAB_GROOVE_W = 3.4
BAT_LAB_GROOVE_D = 2
BAT_LAB_LIP_T = 2
BAT_LAB_LIP_H = 1.5
BAT_LAB_CL_L = 132
BAT_LAB_CL_W = 112
BAT_SCREW_SEAT_DEPTH = 0.4
BAT_SCREW_SEAT_D = 11
BAT_LAB_BACKUP_H = 1.5
BAT_LAB_BACKUP_W = 7
BAT_GROOVE_BACKUP_H = 2.0
BAT_GROOVE_BACKUP_W = 8

' Internal wall relief only: 4 mm ribs remain full thickness and every pocket
' stops at a continuous 2.8 mm nominal waterproof outer skin (2.6 mm at the
' negative local tolerance). No relief crosses a seal, insert or load path.
WALL_RELIEF_D = 1.2
WALL_RELIEF_CELL_X = 18
WALL_RELIEF_CELL_Z = 12

PLATE_L = 168
PLATE_W = 130
PLATE_T = 2
SUPPORT_X = 78
SUPPORT_Y = 59
SUPPORT_TOP_Z = 18
SUPPORT_BASE_H = 3
SUPPORT_BASE_D = 22
SUPPORT_COLLAR_H = 6
SUPPORT_COLLAR_D = 20
SUPPORT_POST_D = 16
ISOLATOR_INSERT_POCKET_D = 8.5

' VD rubber isolator: M4 male stud 8 mm, D10 rubber body, H10 body.
' Compact bonded-insert mounts: D22 x H3 load-spreading feet under D16 posts.
' The top is Z18; the plate underside is nominally Z28, leaving 2 mm above
' the Z26 battery-slot roof. The M4 x 8 isolator stud enters a blind D5.1 x 8.5
' pocket containing the supplier-specified L8 insert, with 0.5 mm base relief.
ISOLATOR_D = 10
ISOLATOR_H = 10
ISOLATOR_STUD_L = 8

' M4 x D5 x L8 inserts per the supplier's final table. Black SLA resin is thermoset,
' therefore the pocket is sized for low-temperature press insertion rather
' than thermoplastic melt displacement. A D5.6 x 0.5 lead-in prevents edge
' chipping; the D5.1 body follows the supplier's reserved-hole table. Verify
' coupons at D4.9 / 5.1 / 5.3 before releasing the full print and use a small amount
' of toughened two-part epoxy after insertion.
INSERT_HOLE_D = 5.1
INSERT_ENTRY_D = 5.6
INSERT_ENTRY_DEPTH = 0.5
INSERT_L = 8.0
COVER_HOLE_D = 4.8
M4_COVER_SCREW_L = 8
TOP_BOSS_D = 14
BOTTOM_BOSS_D = 14
BOTTOM_BOSS_H = 12
BOSS_RIB_SPAN = 24
BOSS_RIB_T = 3
' Horizontal XY ribs follow almost the full 12 mm blind-boss projection.
' The 0.5 mm setback avoids a coplanar fin/boss end face in the production STL.
SIDE_RIB_DEPTH = 11.5
BOTTOM_RIB_H = 5

' Two purchased 73 x 38 x 6 mm folding handles, 64 mm hole pitch. They mount
' to bonded M5 blind inserts in local D16 inner bosses; no hole enters the bay.
HANDLE_CENTER_Y = 0
HANDLE_CENTER_Z = 19
HANDLE_BASE_L = 73
HANDLE_BASE_H = 38
HANDLE_INSERT_D = 7.1
HANDLE_INSERT_L = 8.0
HANDLE_INSERT_POCKET_D = 8.5
HANDLE_ENTRY_D = 7.6
HANDLE_ENTRY_DEPTH = 0.5
HANDLE_BOSS_D = 16
HANDLE_BOSS_DEPTH = 8

' Integral closed strap loops are centred on the left/right short walls.
' They have no wall penetration. A thin 20-25 mm webbing loop passes through
' the 3 mm stand-off rather than using a bulky snap hook.
STRAP_CENTER_Y = 0
STRAP_CENTER_Z = 51

' Front-wall SMA-K bulkhead, near the planned LoRa module zone.
SMA_X = 72
SMA_Z = 48
SMA_HOLE_D = 10.4
SMA_RECESS_D = 20

' IMPORTANT: replace these three values with the maximum measured battery
' envelope, including shrink wrap and cable outlet.
BAT_L = 70
BAT_W = 56
BAT_H = 20

' Dedicated bottom-loading battery slot. With 1 mm EVA on each side, the
' remaining nominal clearance is 1 mm per side around the measured battery.
BAT_SLOT_L = BAT_L + 4
BAT_SLOT_W = BAT_W + 4
BAT_SLOT_H = 23
BAT_TRAY_WALL = 4
BAT_TRAY_ROOF_T = 3
BAT_OPEN_L = BAT_SLOT_L
BAT_OPEN_W = BAT_SLOT_W
BAT_COVER_L = 138
BAT_COVER_W = 118
' ------------------------------------------------------------------------

Call Main()

Sub Main()
  Dim docs, mainDoc, coverDoc, batDoc, plateDoc, gasketDoc, handleGasketDoc, couponDoc
  Dim outputRoot, stamp, logFile

  Set FSO = CreateObject("Scripting.FileSystemObject")

  On Error Resume Next
  Set CATIA_APP = GetObject(, "CATIA.Application")
  If Err.Number <> 0 Then
    WScript.Echo "ERROR: CATIA is not running. Start CATIA V5 first."
    WScript.Quit 1
  End If
  On Error GoTo 0

  If BAT_COVER_L > BODY_L - 8 Or BAT_COVER_W > BODY_W - 8 Then
    WScript.Echo "ERROR: Battery cover is too large for the current housing."
    WScript.Echo "BAT_COVER = " & BAT_COVER_L & " x " & BAT_COVER_W
    WScript.Quit 2
  End If

  If BAT_H + 2 > BAT_SLOT_H Then
    WScript.Echo "ERROR: Battery plus 1 mm bottom EVA and 1 mm top EVA exceeds BAT_SLOT_H."
    WScript.Quit 3
  End If

  outputRoot = FSO.GetParentFolderName(WScript.ScriptFullName) & "\generated"
  If Not FSO.FolderExists(outputRoot) Then FSO.CreateFolder outputRoot
  stamp = TimeStampText(Now)
  OUTPUT_DIR = outputRoot & "\RES_Enclosure_" & stamp
  FSO.CreateFolder OUTPUT_DIR

  CATIA_APP.DisplayFileAlerts = False
  CATIA_APP.RefreshDisplay = False

  StepLog "Creating main housing..."
  Set mainDoc = BuildMainHousing()
  mainDoc.SaveAs OUTPUT_DIR & "\RES_MainHousing.CATPart"
  mainDoc.ExportData OUTPUT_DIR & "\RES_MainHousing.stl", "stl"
  mainDoc.ExportData OUTPUT_DIR & "\RES_MainHousing.stp", "stp"

  StepLog "Creating top cover..."
  Set coverDoc = BuildTopCover()
  coverDoc.SaveAs OUTPUT_DIR & "\RES_TopCover.CATPart"
  coverDoc.ExportData OUTPUT_DIR & "\RES_TopCover.stl", "stl"
  coverDoc.ExportData OUTPUT_DIR & "\RES_TopCover.stp", "stp"

  StepLog "Creating battery cover..."
  Set batDoc = BuildBatteryCover()
  batDoc.SaveAs OUTPUT_DIR & "\RES_BatteryCover.CATPart"
  batDoc.ExportData OUTPUT_DIR & "\RES_BatteryCover.stl", "stl"
  batDoc.ExportData OUTPUT_DIR & "\RES_BatteryCover.stp", "stp"

  StepLog "Creating top flat gasket reference..."
  Set gasketDoc = BuildTopGasket()
  gasketDoc.SaveAs OUTPUT_DIR & "\RES_TopGasket_3mm.CATPart"
  gasketDoc.ExportData OUTPUT_DIR & "\RES_TopGasket_3mm.stl", "stl"

  StepLog "Creating handle flat gasket reference..."
  Set handleGasketDoc = BuildHandleGasket()
  handleGasketDoc.SaveAs OUTPUT_DIR & "\RES_HandleGasket_1mm.CATPart"
  handleGasketDoc.ExportData OUTPUT_DIR & "\RES_HandleGasket_1mm.stl", "stl"

  StepLog "Creating insulation plate..."
  Set plateDoc = BuildInsulationPlate()
  plateDoc.SaveAs OUTPUT_DIR & "\RES_InsulationPlate.CATPart"
  plateDoc.ExportData OUTPUT_DIR & "\RES_InsulationPlate.stl", "stl"

  StepLog "Creating M4 insert process coupon..."
  Set couponDoc = BuildM4InsertCoupon()
  couponDoc.SaveAs OUTPUT_DIR & "\RES_M4_InsertCoupon.CATPart"
  couponDoc.ExportData OUTPUT_DIR & "\RES_M4_InsertCoupon.stl", "stl"
  couponDoc.ExportData OUTPUT_DIR & "\RES_M4_InsertCoupon.stp", "stp"

  Set logFile = FSO.CreateTextFile(OUTPUT_DIR & "\BUILD_PARAMETERS.txt", True, True)
  WriteBuildParameters logFile
  logFile.Close

  CATIA_APP.RefreshDisplay = True
  CATIA_APP.DisplayFileAlerts = True
  coverDoc.Activate
  On Error Resume Next
  CATIA_APP.ActiveWindow.ActiveViewer.Reframe
  On Error GoTo 0

  WScript.Echo "DONE"
  WScript.Echo OUTPUT_DIR
End Sub

Function BuildMainHousing()
  Dim doc, part, body, sf, hb
  Dim sk, feat, refXY, refZX, refYZ
  Dim p68Down, pNeckBase, pSupportUp, p4Up, pBatRoofUp
  Dim pFrontInner, pFrontOuter, pRearInner
  Dim pRightInner, pRightOuter, pLeftInner, pLeftOuter
  Dim pRightRingFace, pLeftRingFace
  Dim pCapFrontOuter, pCapRearOuter, pCapRightOuter, pCapLeftOuter
  Dim pCapFrontNoseOuter, pCapRearNoseOuter, pCapRightNoseOuter, pCapLeftNoseOuter
  Dim f, i, j, x, y, screwY, endX, batScrewX, batScrewY
  Dim gasketCLL, gasketCLW, gasketOuterL, gasketOuterW, gasketInnerL, gasketInnerW

  Set doc = CATIA_APP.Documents.Add("Part")
  Set part = doc.Part
  Set body = part.Bodies.Item(1)
  body.Name = "MAIN_HOUSING"
  Set sf = part.ShapeFactory
  Set hb = part.HybridBodies.Add()
  hb.Name = "REFERENCE_PLANES"
  Set refXY = part.OriginElements.PlaneXY
  Set refZX = part.OriginElements.PlaneZX
  Set refYZ = part.OriginElements.PlaneYZ

  ' Lower outer solid stops below the wrap-around lid skirt.
  Set sk = NewSketch(body, refXY, "SK_OUTER")
  Set f = sk.OpenEdition()
  DrawRoundedRectAt f, 0, 0, BODY_L, BODY_W, OUTER_R
  sk.CloseEdition
  Set feat = AddPad(part, sk, BODY_H - TOP_NECK_H, "PAD_LOWER_OUTER")

  ' Inset upper neck. The cover skirt overlaps this neck with 0.6 mm radial
  ' clearance while the assembled external envelope remains 188 x 150 mm.
  Set pNeckBase = AddPlaneOffset(part, hb, refXY, BODY_H - TOP_NECK_H, False, "PLN_TOP_NECK_BASE")
  Set sk = NewSketch(body, pNeckBase, "SK_TOP_NECK_OUTER")
  Set f = sk.OpenEdition()
  DrawRoundedRectAt f, 0, 0, TOP_NECK_L, TOP_NECK_W, 6.4
  sk.CloseEdition
  Set feat = AddPad(part, sk, TOP_NECK_H, "PAD_INSET_TOP_NECK")

  ' The top opening passes through the full 10 mm neck, leaving a protected
  ' annular land for the continuous flat top gasket.
  Set p68Down = AddPlaneOffset(part, hb, refXY, BODY_H, False, "PLN_TOP_DOWN")
  Set sk = NewSketch(body, p68Down, "SK_TOP_OPENING")
  Set f = sk.OpenEdition()
  DrawRoundedRectAt f, 0, 0, TOP_OPEN_L, TOP_OPEN_W, 5
  sk.CloseEdition
  Set feat = AddPocketReverse(part, sk, TOP_NECK_H, "POCKET_TOP_OPENING")

  ' Larger inner cavity from the neck shoulder down to the 4 mm floor.
  Set sk = NewSketch(body, pNeckBase, "SK_MAIN_CAVITY")
  Set f = sk.OpenEdition()
  DrawRoundedRectAt f, 0, 0, CAVITY_L, CAVITY_W, 6
  sk.CloseEdition
  Set feat = AddPocketReverse(part, sk, BODY_H - TOP_NECK_H - BOTTOM_T, "POCKET_MAIN_CAVITY")

  ' Outer battery-cover labyrinth groove. It remains outside all eight screw
  ' heads and leaves 2 mm of the original bottom wall below the groove floor.
  Set sk = NewSketch(body, refXY, "SK_BAT_OUTER_LABYRINTH_GROOVE")
  Set f = sk.OpenEdition()
  DrawRoundedRectAt f, 0, 0, BAT_LAB_CL_L + BAT_LAB_GROOVE_W, BAT_LAB_CL_W + BAT_LAB_GROOVE_W, 12.5
  DrawRoundedRectAt f, 0, 0, BAT_LAB_CL_L - BAT_LAB_GROOVE_W, BAT_LAB_CL_W - BAT_LAB_GROOVE_W, 9.5
  sk.CloseEdition
  Set feat = AddPocket(part, sk, BAT_LAB_GROOVE_D, "POCKET_BAT_OUTER_LABYRINTH_3X2")

  ' A local annular rib on the cavity side backs the 2 mm residual floor below
  ' the labyrinth groove. The sealing floor therefore has 3.5 mm local section
  ' without thickening the complete enclosure bottom.
  Set p4Up = AddPlaneOffset(part, hb, refXY, BOTTOM_T, False, "PLN_BAT_LABYRINTH_BACKUP")
  Set sk = NewSketch(body, p4Up, "SK_BAT_LABYRINTH_BACKUP_RING")
  Set f = sk.OpenEdition()
  DrawRoundedRectAt f, 0, 0, BAT_LAB_CL_L + BAT_LAB_BACKUP_W, BAT_LAB_CL_W + BAT_LAB_BACKUP_W, 14.5
  DrawRoundedRectAt f, 0, 0, BAT_LAB_CL_L - BAT_LAB_BACKUP_W, BAT_LAB_CL_W - BAT_LAB_BACKUP_W, 7.5
  sk.CloseEdition
  Set feat = AddPad(part, sk, BAT_LAB_BACKUP_H, "PAD_BAT_LABYRINTH_BACKUP_W7XH1_5")

  ' Battery service opening through the 4 mm bottom.
  Set sk = NewSketch(body, refXY, "SK_BATTERY_OPENING")
  Set f = sk.OpenEdition()
  DrawRoundedRectAt f, 0, 0, BAT_OPEN_L, BAT_OPEN_W, 6
  sk.CloseEdition
  Set feat = AddPocket(part, sk, BOTTOM_T, "POCKET_BATTERY_OPENING")

  ' Dedicated battery-slot side walls, loading from the bottom opening.
  ' Inner slot is 74 x 60 x 23 mm for a 70 x 56 x 20 mm battery plus
  ' 1 mm EVA above and below and 1 mm residual assembly clearance.
  Set sk = NewSketch(body, refXY, "SK_BATTERY_SLOT_WALLS")
  Set f = sk.OpenEdition()
  DrawRoundedRectAt f, 0, 0, BAT_SLOT_L + 2 * BAT_TRAY_WALL, BAT_SLOT_W + 2 * BAT_TRAY_WALL, 9
  DrawRoundedRectAt f, 0, 0, BAT_SLOT_L, BAT_SLOT_W, 5
  sk.CloseEdition
  Set feat = AddPad(part, sk, BAT_SLOT_H, "PAD_BATTERY_SLOT_WALLS")

  ' A 3 mm roof isolates the battery from the electronics compartment.
  Set pBatRoofUp = AddPlaneOffset(part, hb, refXY, BAT_SLOT_H, False, "PLN_BATTERY_ROOF_UP")
  Set sk = NewSketch(body, pBatRoofUp, "SK_BATTERY_SLOT_ROOF")
  Set f = sk.OpenEdition()
  DrawRoundedRectAt f, 0, 0, BAT_SLOT_L + 2 * BAT_TRAY_WALL, BAT_SLOT_W + 2 * BAT_TRAY_WALL, 9
  sk.CloseEdition
  Set feat = AddPad(part, sk, BAT_TRAY_ROOF_T, "PAD_BATTERY_SLOT_ROOF")

  ' Internal cable passage near one short end; not exposed to the exterior.
  Set sk = NewSketch(body, pBatRoofUp, "SK_BATTERY_CABLE_PASSAGE")
  Set f = sk.OpenEdition()
  DrawHorizontalSlot f, -28, 0, 14, 8
  sk.CloseEdition
  Set feat = AddPocket(part, sk, BAT_TRAY_ROOF_T, "POCKET_BATTERY_CABLE_14X8")

  ' Compact shock-mount feet replace the tall rectangular pillars. A D22 x H3
  ' base spreads impact into the 4 mm floor while the D16 post frees corner
  ' space for wiring and modules.
  Set p4Up = AddPlaneOffset(part, hb, refXY, BOTTOM_T, False, "PLN_SHOCK_MOUNT_BASE")
  Set sk = NewSketch(body, p4Up, "SK_SHOCK_MOUNT_D22_BASES")
  Set f = sk.OpenEdition()
  For i = -1 To 1 Step 2
    For j = -1 To 1 Step 2
      f.CreateClosedCircle i * SUPPORT_X, j * SUPPORT_Y, SUPPORT_BASE_D / 2
    Next
  Next
  sk.CloseEdition
  Set feat = AddPad(part, sk, SUPPORT_BASE_H, "PAD_SHOCK_MOUNT_D22XH3_BASES")

  Set sk = NewSketch(body, p4Up, "SK_SHOCK_MOUNT_D20_COLLARS")
  Set f = sk.OpenEdition()
  For i = -1 To 1 Step 2
    For j = -1 To 1 Step 2
      f.CreateClosedCircle i * SUPPORT_X, j * SUPPORT_Y, SUPPORT_COLLAR_D / 2
    Next
  Next
  sk.CloseEdition
  Set feat = AddPad(part, sk, SUPPORT_COLLAR_H, "PAD_SHOCK_MOUNT_D20_COLLARS")

  Set sk = NewSketch(body, p4Up, "SK_SHOCK_MOUNT_D16_POSTS")
  Set f = sk.OpenEdition()
  For i = -1 To 1 Step 2
    For j = -1 To 1 Step 2
      f.CreateClosedCircle i * SUPPORT_X, j * SUPPORT_Y, SUPPORT_POST_D / 2
    Next
  Next
  sk.CloseEdition
  Set feat = AddPad(part, sk, SUPPORT_TOP_Z - BOTTOM_T, "PAD_SHOCK_MOUNT_D16_POSTS_TO_Z18")

  ' The M4 x 8 male stud screws into an M4 x D5 x L8 insert. The blind
  ' D5.1 x 8.5 pocket leaves 0.5 mm base/adhesive relief and 9.5 mm of
  ' resin/floor below the pocket; no stud is forced into solid resin.
  Set pSupportUp = AddPlaneOffset(part, hb, refXY, SUPPORT_TOP_Z, False, "PLN_SHOCK_MOUNT_TOP_Z18")
  Set sk = NewSketch(body, pSupportUp, "SK_SHOCK_MOUNT_M4_INSERT_POCKETS")
  Set f = sk.OpenEdition()
  For i = -1 To 1 Step 2
    For j = -1 To 1 Step 2
      f.CreateClosedCircle i * SUPPORT_X, j * SUPPORT_Y, INSERT_HOLE_D / 2
    Next
  Next
  sk.CloseEdition
  Set feat = AddPocketReverse(part, sk, ISOLATOR_INSERT_POCKET_D, "POCKET_SHOCK_MOUNT_M4_D5_1X8_5_BLIND")

  ' Shallow lead-in counterbores prevent the D5 brass insert from chipping the
  ' printed mouth during controlled low-temperature installation.
  Set sk = NewSketch(body, pSupportUp, "SK_SHOCK_MOUNT_M4_INSERT_LEAD_INS")
  Set f = sk.OpenEdition()
  For i = -1 To 1 Step 2
    For j = -1 To 1 Step 2
      f.CreateClosedCircle i * SUPPORT_X, j * SUPPORT_Y, INSERT_ENTRY_D / 2
    Next
  Next
  sk.CloseEdition
  Set feat = AddPocketReverse(part, sk, INSERT_ENTRY_DEPTH, "POCKET_SHOCK_MOUNT_M4_D5_6_LEAD_IN")

  ' Six of the ten side-facing bosses are on the front/rear long walls. The screw axes stay
  ' below the top sealing land, and the D5.1 x 8.5 pockets stop blind inside the
  ' 12 mm bosses. No top screw penetrates the primary gasket plane.
  Set pCapFrontOuter = AddPlaneOffset(part, hb, refZX, TOP_NECK_W / 2, False, "PLN_CAP_FRONT_NECK_OUTER")
  Set pCapRearOuter = AddPlaneOffset(part, hb, refZX, -TOP_NECK_W / 2, False, "PLN_CAP_REAR_NECK_OUTER")
  Set pCapFrontNoseOuter = AddPlaneOffset(part, hb, refZX, TOP_NECK_W / 2 + SIDE_BOSS_NOSE, False, "PLN_CAP_FRONT_BOSS_NOSE_OUTER")
  Set pCapRearNoseOuter = AddPlaneOffset(part, hb, refZX, -TOP_NECK_W / 2 - SIDE_BOSS_NOSE, False, "PLN_CAP_REAR_BOSS_NOSE_OUTER")

  Set sk = NewSketch(body, pCapFrontOuter, "SK_FRONT_SIDE_M4_BOSSES")
  Set f = sk.OpenEdition()
  For i = 0 To 2
    x = Array(-60, 0, 60)(i)
    f.CreateClosedCircle SIDE_SCREW_Z, x, SIDE_BOSS_D / 2
  Next
  sk.CloseEdition
  Set feat = AddPadReverse(part, sk, SIDE_BOSS_DEPTH, "PAD_FRONT_SIDE_M4_BOSSES")

  Set sk = NewSketch(body, pCapFrontOuter, "SK_FRONT_SIDE_M4_BOSS_NOSES")
  Set f = sk.OpenEdition()
  For i = 0 To 2
    x = Array(-60, 0, 60)(i)
    f.CreateClosedCircle SIDE_SCREW_Z, x, SIDE_BOSS_D / 2
  Next
  sk.CloseEdition
  Set feat = AddPad(part, sk, SIDE_BOSS_NOSE, "PAD_FRONT_SIDE_M4_BOSS_NOSES_0_4")

  ' One horizontal XY through-rib per boss forms two load-spreading arms along
  ' the wall. No symmetric vertical rib is used: at Z62 a 24 mm vertical rib
  ' would rise to Z74 and interfere with the Z68 cover/gasket interface. The
  ' rib follows 11.5 mm of the 12 mm boss projection, leaving a 0.5 mm setback.
  Set sk = NewSketch(body, pCapFrontOuter, "SK_FRONT_SIDE_M4_HORIZONTAL_RIBS_X")
  Set f = sk.OpenEdition()
  For i = 0 To 2
    x = Array(-60, 0, 60)(i)
    ' Plane ZX sketch coordinates are (Z, X): thin in Z, long in global X.
    DrawRectangleAt f, SIDE_SCREW_Z, x, BOSS_RIB_T, BOSS_RIB_SPAN
  Next
  sk.CloseEdition
  Set feat = AddPadReverse(part, sk, SIDE_RIB_DEPTH, "PAD_FRONT_SIDE_M4_HORIZONTAL_RIBS_X")

  Set sk = NewSketch(body, pCapRearOuter, "SK_REAR_SIDE_M4_BOSSES")
  Set f = sk.OpenEdition()
  For i = 0 To 2
    x = Array(-60, 0, 60)(i)
    f.CreateClosedCircle SIDE_SCREW_Z, x, SIDE_BOSS_D / 2
  Next
  sk.CloseEdition
  Set feat = AddPad(part, sk, SIDE_BOSS_DEPTH, "PAD_REAR_SIDE_M4_BOSSES")

  Set sk = NewSketch(body, pCapRearOuter, "SK_REAR_SIDE_M4_BOSS_NOSES")
  Set f = sk.OpenEdition()
  For i = 0 To 2
    x = Array(-60, 0, 60)(i)
    f.CreateClosedCircle SIDE_SCREW_Z, x, SIDE_BOSS_D / 2
  Next
  sk.CloseEdition
  Set feat = AddPadReverse(part, sk, SIDE_BOSS_NOSE, "PAD_REAR_SIDE_M4_BOSS_NOSES_0_4")

  Set sk = NewSketch(body, pCapRearOuter, "SK_REAR_SIDE_M4_HORIZONTAL_RIBS_X")
  Set f = sk.OpenEdition()
  For i = 0 To 2
    x = Array(-60, 0, 60)(i)
    ' Plane ZX sketch coordinates are (Z, X): thin in Z, long in global X.
    DrawRectangleAt f, SIDE_SCREW_Z, x, BOSS_RIB_T, BOSS_RIB_SPAN
  Next
  sk.CloseEdition
  Set feat = AddPad(part, sk, SIDE_RIB_DEPTH, "PAD_REAR_SIDE_M4_HORIZONTAL_RIBS_X")

  Set sk = NewSketch(body, pCapFrontNoseOuter, "SK_FRONT_SIDE_M4_INSERTS_FROM_NOSE_FACE")
  Set f = sk.OpenEdition()
  For i = 0 To 2
    x = Array(-60, 0, 60)(i)
    f.CreateClosedCircle SIDE_SCREW_Z, x, INSERT_HOLE_D / 2
  Next
  sk.CloseEdition
  Set feat = AddPocketReverse(part, sk, TOP_INSERT_POCKET_D, "POCKET_FRONT_SIDE_M4_INSERTS_D5_1X8_5_FROM_NOSE")

  Set sk = NewSketch(body, pCapRearNoseOuter, "SK_REAR_SIDE_M4_INSERTS_FROM_NOSE_FACE")
  Set f = sk.OpenEdition()
  For i = 0 To 2
    x = Array(-60, 0, 60)(i)
    f.CreateClosedCircle SIDE_SCREW_Z, x, INSERT_HOLE_D / 2
  Next
  sk.CloseEdition
  Set feat = AddPocket(part, sk, TOP_INSERT_POCKET_D, "POCKET_REAR_SIDE_M4_INSERTS_D5_1X8_5_FROM_NOSE")

  ' Four additional side screws on the left/right short walls keep O-ring
  ' compression uniform at the ends. Y=+/-50 clears the central strap loops
  ' and the 73 mm handles below them.
  Set pCapRightOuter = AddPlaneOffset(part, hb, refYZ, TOP_NECK_L / 2, False, "PLN_CAP_RIGHT_NECK_OUTER")
  Set pCapLeftOuter = AddPlaneOffset(part, hb, refYZ, -TOP_NECK_L / 2, False, "PLN_CAP_LEFT_NECK_OUTER")
  Set pCapRightNoseOuter = AddPlaneOffset(part, hb, refYZ, TOP_NECK_L / 2 + SIDE_BOSS_NOSE, False, "PLN_CAP_RIGHT_BOSS_NOSE_OUTER")
  Set pCapLeftNoseOuter = AddPlaneOffset(part, hb, refYZ, -TOP_NECK_L / 2 - SIDE_BOSS_NOSE, False, "PLN_CAP_LEFT_BOSS_NOSE_OUTER")

  Set sk = NewSketch(body, pCapRightOuter, "SK_RIGHT_SIDE_M4_BOSSES")
  Set f = sk.OpenEdition()
  For i = -1 To 1 Step 2
    f.CreateClosedCircle i * 50, SIDE_SCREW_Z, SIDE_BOSS_D / 2
  Next
  sk.CloseEdition
  Set feat = AddPadReverse(part, sk, SIDE_BOSS_DEPTH, "PAD_RIGHT_SIDE_M4_BOSSES")

  Set sk = NewSketch(body, pCapRightOuter, "SK_RIGHT_SIDE_M4_BOSS_NOSES")
  Set f = sk.OpenEdition()
  For i = -1 To 1 Step 2
    f.CreateClosedCircle i * 50, SIDE_SCREW_Z, SIDE_BOSS_D / 2
  Next
  sk.CloseEdition
  Set feat = AddPad(part, sk, SIDE_BOSS_NOSE, "PAD_RIGHT_SIDE_M4_BOSS_NOSES_0_4")

  Set sk = NewSketch(body, pCapRightOuter, "SK_RIGHT_SIDE_M4_HORIZONTAL_RIBS_Y")
  Set f = sk.OpenEdition()
  For i = -1 To 1 Step 2
    DrawRectangleAt f, i * 50, SIDE_SCREW_Z, BOSS_RIB_SPAN, BOSS_RIB_T
  Next
  sk.CloseEdition
  Set feat = AddPadReverse(part, sk, SIDE_RIB_DEPTH, "PAD_RIGHT_SIDE_M4_HORIZONTAL_RIBS_Y")

  Set sk = NewSketch(body, pCapLeftOuter, "SK_LEFT_SIDE_M4_BOSSES")
  Set f = sk.OpenEdition()
  For i = -1 To 1 Step 2
    f.CreateClosedCircle i * 50, SIDE_SCREW_Z, SIDE_BOSS_D / 2
  Next
  sk.CloseEdition
  Set feat = AddPad(part, sk, SIDE_BOSS_DEPTH, "PAD_LEFT_SIDE_M4_BOSSES")

  Set sk = NewSketch(body, pCapLeftOuter, "SK_LEFT_SIDE_M4_BOSS_NOSES")
  Set f = sk.OpenEdition()
  For i = -1 To 1 Step 2
    f.CreateClosedCircle i * 50, SIDE_SCREW_Z, SIDE_BOSS_D / 2
  Next
  sk.CloseEdition
  Set feat = AddPadReverse(part, sk, SIDE_BOSS_NOSE, "PAD_LEFT_SIDE_M4_BOSS_NOSES_0_4")

  Set sk = NewSketch(body, pCapLeftOuter, "SK_LEFT_SIDE_M4_HORIZONTAL_RIBS_Y")
  Set f = sk.OpenEdition()
  For i = -1 To 1 Step 2
    DrawRectangleAt f, i * 50, SIDE_SCREW_Z, BOSS_RIB_SPAN, BOSS_RIB_T
  Next
  sk.CloseEdition
  Set feat = AddPad(part, sk, SIDE_RIB_DEPTH, "PAD_LEFT_SIDE_M4_HORIZONTAL_RIBS_Y")

  Set sk = NewSketch(body, pCapRightNoseOuter, "SK_RIGHT_SIDE_M4_INSERTS_FROM_NOSE_FACE")
  Set f = sk.OpenEdition()
  For i = -1 To 1 Step 2
    f.CreateClosedCircle i * 50, SIDE_SCREW_Z, INSERT_HOLE_D / 2
  Next
  sk.CloseEdition
  Set feat = AddPocketReverse(part, sk, TOP_INSERT_POCKET_D, "POCKET_RIGHT_SIDE_M4_INSERTS_D5_1X8_5_FROM_NOSE")

  Set sk = NewSketch(body, pCapLeftNoseOuter, "SK_LEFT_SIDE_M4_INSERTS_FROM_NOSE_FACE")
  Set f = sk.OpenEdition()
  For i = -1 To 1 Step 2
    f.CreateClosedCircle i * 50, SIDE_SCREW_Z, INSERT_HOLE_D / 2
  Next
  sk.CloseEdition
  Set feat = AddPocket(part, sk, TOP_INSERT_POCKET_D, "POCKET_LEFT_SIDE_M4_INSERTS_D5_1X8_5_FROM_NOSE")

  ' The neck top is intentionally left flat and full thickness. A separate
  ' 3 mm die-cut silicone ring covers a 4 mm-wide band; the skirt shoulder
  ' provides a positive 2.3 mm compression stop. No narrow resin groove wall
  ' remains to crack, chip or disappear inside the +/-0.2 mm SLA tolerance.

  ' Eight blind bosses for the battery cover.
  batScrewX = 57
  batScrewY = 47
  Set sk = NewSketch(body, refXY, "SK_BOTTOM_BOSSES")
  Set f = sk.OpenEdition()
  For i = -1 To 1
    f.CreateClosedCircle i * 36, batScrewY, BOTTOM_BOSS_D / 2
    f.CreateClosedCircle i * 36, -batScrewY, BOTTOM_BOSS_D / 2
  Next
  f.CreateClosedCircle batScrewX, 0, BOTTOM_BOSS_D / 2
  f.CreateClosedCircle -batScrewX, 0, BOTTOM_BOSS_D / 2
  sk.CloseEdition
  Set feat = AddPad(part, sk, BOTTOM_BOSS_H, "PAD_BOTTOM_INSERT_BOSSES_H12")

  ' Four-way roots model the proven plus-rib boss geometry while keeping the
  ' upper half of each boss clear for insert heating and screw-tip inspection.
  Set sk = NewSketch(body, refXY, "SK_BOTTOM_M4_BOSS_RIBS_X")
  Set f = sk.OpenEdition()
  For i = -1 To 1
    DrawRectangleAt f, i * 36, batScrewY, BOSS_RIB_SPAN, BOSS_RIB_T
    DrawRectangleAt f, i * 36, -batScrewY, BOSS_RIB_SPAN, BOSS_RIB_T
  Next
  DrawRectangleAt f, batScrewX, 0, BOSS_RIB_SPAN, BOSS_RIB_T
  DrawRectangleAt f, -batScrewX, 0, BOSS_RIB_SPAN, BOSS_RIB_T
  sk.CloseEdition
  Set feat = AddPad(part, sk, BOTTOM_RIB_H, "PAD_BOTTOM_M4_BOSS_RIBS_X")

  Set sk = NewSketch(body, refXY, "SK_BOTTOM_M4_BOSS_RIBS_Y")
  Set f = sk.OpenEdition()
  For i = -1 To 1
    DrawRectangleAt f, i * 36, batScrewY, BOSS_RIB_T, BOSS_RIB_SPAN
    DrawRectangleAt f, i * 36, -batScrewY, BOSS_RIB_T, BOSS_RIB_SPAN
  Next
  DrawRectangleAt f, batScrewX, 0, BOSS_RIB_T, BOSS_RIB_SPAN
  DrawRectangleAt f, -batScrewX, 0, BOSS_RIB_T, BOSS_RIB_SPAN
  sk.CloseEdition
  Set feat = AddPad(part, sk, BOTTOM_RIB_H, "PAD_BOTTOM_M4_BOSS_RIBS_Y")

  Set sk = NewSketch(body, refXY, "SK_BOTTOM_INSERT_POCKETS")
  Set f = sk.OpenEdition()
  For i = -1 To 1
    f.CreateClosedCircle i * 36, batScrewY, INSERT_HOLE_D / 2
    f.CreateClosedCircle i * 36, -batScrewY, INSERT_HOLE_D / 2
  Next
  f.CreateClosedCircle batScrewX, 0, INSERT_HOLE_D / 2
  f.CreateClosedCircle -batScrewX, 0, INSERT_HOLE_D / 2
  sk.CloseEdition
  Set feat = AddPocket(part, sk, TOP_INSERT_POCKET_D, "POCKET_BOTTOM_M4_INSERTS_D5_1X8_5")

  Set sk = NewSketch(body, refXY, "SK_BOTTOM_M4_INSERT_LEAD_INS")
  Set f = sk.OpenEdition()
  For i = -1 To 1
    f.CreateClosedCircle i * 36, batScrewY, INSERT_ENTRY_D / 2
    f.CreateClosedCircle i * 36, -batScrewY, INSERT_ENTRY_D / 2
  Next
  f.CreateClosedCircle batScrewX, 0, INSERT_ENTRY_D / 2
  f.CreateClosedCircle -batScrewX, 0, INSERT_ENTRY_D / 2
  sk.CloseEdition
  Set feat = AddPocket(part, sk, INSERT_ENTRY_DEPTH, "POCKET_BOTTOM_M4_D5_6_LEAD_INS")

  ' Purchased 73 x 38 x 6 folding handles mount flush to the left and right
  ' short walls using bonded M5 blind inserts and compact internal bosses.
  Set pFrontInner = AddPlaneOffset(part, hb, refZX, BODY_W / 2 - WALL, False, "PLN_FRONT_INNER")
  Set pFrontOuter = AddPlaneOffset(part, hb, refZX, BODY_W / 2, False, "PLN_FRONT_OUTER")
  Set pRearInner = AddPlaneOffset(part, hb, refZX, -BODY_W / 2 + WALL, False, "PLN_REAR_INNER")
  Set pRightInner = AddPlaneOffset(part, hb, refYZ, BODY_L / 2 - WALL, False, "PLN_RIGHT_INNER")
  Set pRightOuter = AddPlaneOffset(part, hb, refYZ, BODY_L / 2, False, "PLN_RIGHT_OUTER")
  Set pLeftInner = AddPlaneOffset(part, hb, refYZ, -BODY_L / 2 + WALL, False, "PLN_LEFT_INNER")
  Set pLeftOuter = AddPlaneOffset(part, hb, refYZ, -BODY_L / 2, False, "PLN_LEFT_OUTER")

  ' Weight-saving waffle pockets on the INNER faces of the long walls.
  ' Each pocket is 18 mm along global X, 12 mm high and 1.2 mm deep. The
  ' remaining 3.0 mm outer skin is continuous and waterproof; 4 mm full-wall
  ' ribs remain between adjacent cells. Lower corner cells are omitted around
  ' the shock-mount supports, and the front upper-right cells are omitted for
  ' the SMA sealing land and cable bend radius.
  Set sk = NewSketch(body, pFrontInner, "SK_FRONT_INNER_WAFFLE_RELIEF")
  Set f = sk.OpenEdition()
  For i = 0 To 6
    x = Array(-66, -44, -22, 0, 22, 44, 66)(i)
    For j = 0 To 2
      y = Array(12, 28, 44)(j)
      If Not (y = 12 And Abs(x) > 55) Then
        If Not (x > 54 And y > 34) Then
          DrawRoundedRectAt f, y, x, WALL_RELIEF_CELL_Z, WALL_RELIEF_CELL_X, 2
        End If
      End If
    Next
  Next
  sk.CloseEdition
  Set feat = AddPocket(part, sk, WALL_RELIEF_D, "POCKET_FRONT_INNER_WAFFLE_D1_2")

  Set sk = NewSketch(body, pRearInner, "SK_REAR_INNER_WAFFLE_RELIEF")
  Set f = sk.OpenEdition()
  For i = 0 To 6
    x = Array(-66, -44, -22, 0, 22, 44, 66)(i)
    For j = 0 To 2
      y = Array(12, 28, 44)(j)
      If Not (y = 12 And Abs(x) > 55) Then
        DrawRoundedRectAt f, y, x, WALL_RELIEF_CELL_Z, WALL_RELIEF_CELL_X, 2
      End If
    Next
  Next
  sk.CloseEdition
  Set feat = AddPocketReverse(part, sk, WALL_RELIEF_D, "POCKET_REAR_INNER_WAFFLE_D1_2")

  ' The short walls also receive an internal pocket field, but every load path
  ' around the two handle inserts, strap feet, top screws and shock mounts is
  ' left full thickness. Pockets never break the continuous 3.0 mm outer skin.
  Set sk = NewSketch(body, pRightInner, "SK_RIGHT_INNER_WAFFLE_RELIEF")
  Set f = sk.OpenEdition()
  For i = 0 To 5
    x = Array(-60, -36, -12, 12, 36, 60)(i)
    For j = 0 To 3
      y = Array(8, 24, 40, 56)(j)
      If Not ((Abs(x - 32) < 18 Or Abs(x + 32) < 18) And Abs(y - HANDLE_CENTER_Z) < 16) Then
        If Not (Abs(x) < 30 And y > 34) Then
          If Not (Abs(Abs(x) - 50) < 16 And y > 48) Then
            If Not (Abs(x) > 48 And y < 16) Then
              DrawRoundedRectAt f, x, y, WALL_RELIEF_CELL_X, WALL_RELIEF_CELL_Z, 2
            End If
          End If
        End If
      End If
    Next
  Next
  sk.CloseEdition
  Set feat = AddPocket(part, sk, WALL_RELIEF_D, "POCKET_RIGHT_INNER_WAFFLE_D1_2")

  Set sk = NewSketch(body, pLeftInner, "SK_LEFT_INNER_WAFFLE_RELIEF")
  Set f = sk.OpenEdition()
  For i = 0 To 5
    x = Array(-60, -36, -12, 12, 36, 60)(i)
    For j = 0 To 3
      y = Array(8, 24, 40, 56)(j)
      If Not ((Abs(x - 32) < 18 Or Abs(x + 32) < 18) And Abs(y - HANDLE_CENTER_Z) < 16) Then
        If Not (Abs(x) < 30 And y > 34) Then
          If Not (Abs(Abs(x) - 50) < 16 And y > 48) Then
            If Not (Abs(x) > 48 And y < 16) Then
              DrawRoundedRectAt f, x, y, WALL_RELIEF_CELL_X, WALL_RELIEF_CELL_Z, 2
            End If
          End If
        End If
      End If
    Next
  Next
  sk.CloseEdition
  Set feat = AddPocketReverse(part, sk, WALL_RELIEF_D, "POCKET_LEFT_INNER_WAFFLE_D1_2")

  ' Two local D16 x 8 mm inner bosses per handle create a 12 mm total wall
  ' thickness only where load enters. This is lighter and occupies less module
  ' space than the former 90 x 42 mm internal pad.
  Set sk = NewSketch(body, pRightInner, "SK_RIGHT_HANDLE_D16_INNER_BOSSES")
  Set f = sk.OpenEdition()
  f.CreateClosedCircle HANDLE_CENTER_Y - 32, HANDLE_CENTER_Z, HANDLE_BOSS_D / 2
  f.CreateClosedCircle HANDLE_CENTER_Y + 32, HANDLE_CENTER_Z, HANDLE_BOSS_D / 2
  sk.CloseEdition
  Set feat = AddPadReverse(part, sk, HANDLE_BOSS_DEPTH, "PAD_RIGHT_HANDLE_D16X8_BLIND_BOSSES")

  Set sk = NewSketch(body, pLeftInner, "SK_LEFT_HANDLE_D16_INNER_BOSSES")
  Set f = sk.OpenEdition()
  f.CreateClosedCircle HANDLE_CENTER_Y - 32, HANDLE_CENTER_Z, HANDLE_BOSS_D / 2
  f.CreateClosedCircle HANDLE_CENTER_Y + 32, HANDLE_CENTER_Z, HANDLE_BOSS_D / 2
  sk.CloseEdition
  Set feat = AddPad(part, sk, HANDLE_BOSS_DEPTH, "PAD_LEFT_HANDLE_D16X8_BLIND_BOSSES")

  ' Handle faces remain flat and full thickness. The purchased ID60 O-rings
  ' are too large for a 73 x 38 base once manufacturing margin is included.
  ' Use die-cut 71 x 36 x 1 mm closed-cell EPDM full-face gaskets instead.

  ' No handle hole reaches the electronics cavity. Supplier-table M5 x D7 x L8
  ' inserts are bonded into D7.1 x 8.5 blind pockets from the outside. Across
  ' the 4 mm wall plus 8 mm local boss, 3.5 mm solid resin remains at the blind end.
  Set sk = NewSketch(body, pRightOuter, "SK_RIGHT_HANDLE_M5_BLIND_INSERTS")
  Set f = sk.OpenEdition()
  f.CreateClosedCircle HANDLE_CENTER_Y - 32, HANDLE_CENTER_Z, HANDLE_INSERT_D / 2
  f.CreateClosedCircle HANDLE_CENTER_Y + 32, HANDLE_CENTER_Z, HANDLE_INSERT_D / 2
  sk.CloseEdition
  Set feat = AddPocketReverse(part, sk, HANDLE_INSERT_POCKET_D, "POCKET_RIGHT_HANDLE_M5_D7_1X8_5_BLIND")

  Set sk = NewSketch(body, pRightOuter, "SK_RIGHT_HANDLE_M5_INSERT_LEAD_INS")
  Set f = sk.OpenEdition()
  f.CreateClosedCircle HANDLE_CENTER_Y - 32, HANDLE_CENTER_Z, HANDLE_ENTRY_D / 2
  f.CreateClosedCircle HANDLE_CENTER_Y + 32, HANDLE_CENTER_Z, HANDLE_ENTRY_D / 2
  sk.CloseEdition
  Set feat = AddPocketReverse(part, sk, HANDLE_ENTRY_DEPTH, "POCKET_RIGHT_HANDLE_M5_D7_6X0_5_LEAD_INS")

  Set sk = NewSketch(body, pLeftOuter, "SK_LEFT_HANDLE_M5_BLIND_INSERTS")
  Set f = sk.OpenEdition()
  f.CreateClosedCircle HANDLE_CENTER_Y - 32, HANDLE_CENTER_Z, HANDLE_INSERT_D / 2
  f.CreateClosedCircle HANDLE_CENTER_Y + 32, HANDLE_CENTER_Z, HANDLE_INSERT_D / 2
  sk.CloseEdition
  Set feat = AddPocket(part, sk, HANDLE_INSERT_POCKET_D, "POCKET_LEFT_HANDLE_M5_D7_1X8_5_BLIND")

  Set sk = NewSketch(body, pLeftOuter, "SK_LEFT_HANDLE_M5_INSERT_LEAD_INS")
  Set f = sk.OpenEdition()
  f.CreateClosedCircle HANDLE_CENTER_Y - 32, HANDLE_CENTER_Z, HANDLE_ENTRY_D / 2
  f.CreateClosedCircle HANDLE_CENTER_Y + 32, HANDLE_CENTER_Z, HANDLE_ENTRY_D / 2
  sk.CloseEdition
  Set feat = AddPocket(part, sk, HANDLE_ENTRY_DEPTH, "POCKET_LEFT_HANDLE_M5_D7_6X0_5_LEAD_INS")

  ' Integral closed strap loops: centred, no holes and no waterproofing risk.
  ' Two broad feet stand 2.5 mm off each wall; a 3.5 mm bridge completes the
  ' loop. Total projection remains 6 mm while the loaded bridge is thicker.
  Set sk = NewSketch(body, pRightOuter, "SK_RIGHT_INTEGRAL_STRAP_FEET")
  Set f = sk.OpenEdition()
  DrawRoundedRectAt f, -15, STRAP_CENTER_Z - 2, 14, 18, 3
  DrawRoundedRectAt f, 15, STRAP_CENTER_Z - 2, 14, 18, 3
  sk.CloseEdition
  Set feat = AddPad(part, sk, 2.5, "PAD_RIGHT_INTEGRAL_STRAP_FEET")

  Set pRightRingFace = AddPlaneOffset(part, hb, refYZ, BODY_L / 2 + 2.5, False, "PLN_RIGHT_STRAP_RING_FACE")
  Set sk = NewSketch(body, pRightRingFace, "SK_RIGHT_INTEGRAL_STRAP_LOOP")
  Set f = sk.OpenEdition()
  DrawDProfileAt f, STRAP_CENTER_Y, STRAP_CENTER_Z, 40, 22
  DrawDProfileAt f, STRAP_CENTER_Y, STRAP_CENTER_Z, 26, 9
  sk.CloseEdition
  Set feat = AddPad(part, sk, 3.5, "PAD_RIGHT_INTEGRAL_STRAP_LOOP")

  Set sk = NewSketch(body, pLeftOuter, "SK_LEFT_INTEGRAL_STRAP_FEET")
  Set f = sk.OpenEdition()
  DrawRoundedRectAt f, -15, STRAP_CENTER_Z - 2, 14, 18, 3
  DrawRoundedRectAt f, 15, STRAP_CENTER_Z - 2, 14, 18, 3
  sk.CloseEdition
  Set feat = AddPadReverse(part, sk, 2.5, "PAD_LEFT_INTEGRAL_STRAP_FEET")

  Set pLeftRingFace = AddPlaneOffset(part, hb, refYZ, -BODY_L / 2 - 2.5, False, "PLN_LEFT_STRAP_RING_FACE")
  Set sk = NewSketch(body, pLeftRingFace, "SK_LEFT_INTEGRAL_STRAP_LOOP")
  Set f = sk.OpenEdition()
  DrawDProfileAt f, STRAP_CENTER_Y, STRAP_CENTER_Z, 40, 22
  DrawDProfileAt f, STRAP_CENTER_Y, STRAP_CENTER_Z, 26, 9
  sk.CloseEdition
  Set feat = AddPadReverse(part, sk, 3.5, "PAD_LEFT_INTEGRAL_STRAP_LOOP")

  ' Front-wall SMA-K bulkhead. Local ZX sketch X maps to global Z and local
  ' sketch Y maps to global X. A D20 inner recess leaves a 3 mm panel.
  Set sk = NewSketch(body, pFrontInner, "SK_FRONT_SMA_LOCAL_THINNING")
  Set f = sk.OpenEdition()
  f.CreateClosedCircle SMA_Z, SMA_X, SMA_RECESS_D / 2
  sk.CloseEdition
  Set feat = AddPocket(part, sk, 1, "POCKET_FRONT_SMA_PANEL_T3")

  ' The D22 annulus around the SMA opening is reserved as a flat sealing land
  ' for the supplied bulkhead O-ring. It stays flush with the Y=75 wall so the
  ' enclosure remains inside the 150 mm rule envelope; do not place supports,
  ' texture or paint runs on this annulus.

  Set sk = NewSketch(body, pFrontOuter, "SK_FRONT_SMA_CUTOUT")
  Set f = sk.OpenEdition()
  f.CreateClosedCircle SMA_Z, SMA_X, SMA_HOLE_D / 2
  sk.CloseEdition
  Set feat = AddPocketReverse(part, sk, WALL, "POCKET_FRONT_SMA_D10_4")

  AddNotes part, "Black high-toughness SLA final: supplier-table M4 x D5 x L8 inserts use D5.1 x 8.5 blind pockets. The ten upper side pockets are straight bores and receive a post-print 0.2-0.3 mm hand deburr/chamfer; this avoids coincident Pocket seams in the production STL. Their bosses use D24 x T3 horizontal double-arm ribs only, preventing any rib from crossing the Z68 cover/gasket interface; the eight bottom bosses retain four-way ribs and modeled D5.6 x 0.5 lead-ins. Install only after same-batch D4.9/D5.1/D5.3 coupon validation, using controlled low-temperature press plus toughened epoxy. The inset neck uses a 3 mm die-cut flat silicone gasket with a positive 2.3 mm compression stop. Ten side M4 x 8 screws remain outside the primary seal. Relieved wall cells retain a continuous 2.8 mm nominal waterproof skin and every load path remains full 4 mm."
  HideObject doc, hb
  part.Update
  Set BuildMainHousing = doc
End Function

Function BuildTopCover()
  Dim doc, part, body, sf, hb, refXY, refZX, refYZ
  Dim p0Down, pTopFace, pFrontOuter, pRearOuter, pRightOuter, pLeftOuter, sk, f, feat, i, x
  Dim lipOuterL, lipOuterW, lipInnerL, lipInnerW

  Set doc = CATIA_APP.Documents.Add("Part")
  Set part = doc.Part
  Set body = part.Bodies.Item(1)
  body.Name = "TOP_COVER"
  Set sf = part.ShapeFactory
  Set hb = part.HybridBodies.Add()
  hb.Name = "REFERENCE_PLANES"
  Set refXY = part.OriginElements.PlaneXY
  Set refZX = part.OriginElements.PlaneZX
  Set refYZ = part.OriginElements.PlaneYZ

  Set sk = NewSketch(body, refXY, "SK_COVER_OUTER")
  Set f = sk.OpenEdition()
  DrawRoundedRectAt f, 0, 0, BODY_L, BODY_W, OUTER_R
  sk.CloseEdition
  Set feat = AddPad(part, sk, TOP_T, "PAD_COVER_BASE")

  ' Full downward skirt. Its length is also the gasket compression stop: at
  ' shoulder contact the 3 mm flat seal is compressed to 2.3 mm.
  Set p0Down = AddPlaneOffset(part, hb, refXY, 0, False, "PLN_COVER_UNDERSIDE")
  Set sk = NewSketch(body, p0Down, "SK_FULL_WRAP_SKIRT")
  Set f = sk.OpenEdition()
  DrawRoundedRectAt f, 0, 0, BODY_L, BODY_W, OUTER_R
  DrawRoundedRectAt f, 0, 0, CAP_INNER_L, CAP_INNER_W, 7
  sk.CloseEdition
  Set feat = AddPadReverse(part, sk, CAP_SKIRT_H, "PAD_FULL_WRAP_SKIRT_WITH_STOP")

  ' Ten horizontal clearance holes surround all four sides. They are below
  ' and outside the continuous top flat gasket. M4 x 8 screws reach blind side
  ' inserts without creating any vertical leak path into the electronics bay.
  ' The purchased M4 x 8 sealing screws clamp their O-rings directly against
  ' the full 3 mm flat skirt. No D11 counterbore is permitted near the edge.
  Set pFrontOuter = AddPlaneOffset(part, hb, refZX, BODY_W / 2, False, "PLN_COVER_FRONT_OUTER")
  Set pRearOuter = AddPlaneOffset(part, hb, refZX, -BODY_W / 2, False, "PLN_COVER_REAR_OUTER")

  Set sk = NewSketch(body, pFrontOuter, "SK_FRONT_SIDE_M4_CLEARANCE")
  Set f = sk.OpenEdition()
  For i = 0 To 2
    x = Array(-60, 0, 60)(i)
    DrawVerticalSlot f, SIDE_SCREW_Z - BODY_H - TOP_GASKET_COMP_T, x, SIDE_SLOT_L, SIDE_SLOT_W
  Next
  sk.CloseEdition
  Set feat = AddPocketReverse(part, sk, CAP_SKIRT_T, "POCKET_FRONT_SIDE_M4_SLOT_5_0X4_6")

  Set sk = NewSketch(body, pRearOuter, "SK_REAR_SIDE_M4_CLEARANCE")
  Set f = sk.OpenEdition()
  For i = 0 To 2
    x = Array(-60, 0, 60)(i)
    DrawVerticalSlot f, SIDE_SCREW_Z - BODY_H - TOP_GASKET_COMP_T, x, SIDE_SLOT_L, SIDE_SLOT_W
  Next
  sk.CloseEdition
  Set feat = AddPocket(part, sk, CAP_SKIRT_T, "POCKET_REAR_SIDE_M4_SLOT_5_0X4_6")

  Set pRightOuter = AddPlaneOffset(part, hb, refYZ, BODY_L / 2, False, "PLN_COVER_RIGHT_OUTER")
  Set pLeftOuter = AddPlaneOffset(part, hb, refYZ, -BODY_L / 2, False, "PLN_COVER_LEFT_OUTER")

  Set sk = NewSketch(body, pRightOuter, "SK_RIGHT_SIDE_M4_CLEARANCE")
  Set f = sk.OpenEdition()
  For i = -1 To 1 Step 2
    DrawHorizontalSlot f, i * 50, SIDE_SCREW_Z - BODY_H - TOP_GASKET_COMP_T, SIDE_SLOT_L, SIDE_SLOT_W
  Next
  sk.CloseEdition
  Set feat = AddPocketReverse(part, sk, CAP_SKIRT_T, "POCKET_RIGHT_SIDE_M4_SLOT_5_0X4_6")

  Set sk = NewSketch(body, pLeftOuter, "SK_LEFT_SIDE_M4_CLEARANCE")
  Set f = sk.OpenEdition()
  For i = -1 To 1 Step 2
    DrawHorizontalSlot f, i * 50, SIDE_SCREW_Z - BODY_H - TOP_GASKET_COMP_T, SIDE_SLOT_L, SIDE_SLOT_W
  Next
  sk.CloseEdition
  Set feat = AddPocket(part, sk, CAP_SKIRT_T, "POCKET_LEFT_SIDE_M4_SLOT_5_0X4_6")

  ' Continuous secondary water lip. It is inset from the opening so the
  ' complete closed ring remains a second labyrinth barrier.
  lipOuterL = 140
  lipOuterW = 108
  lipInnerL = lipOuterL - 2 * LIP_T
  lipInnerW = lipOuterW - 2 * LIP_T
  Set sk = NewSketch(body, p0Down, "SK_POSITIONING_LIP")
  Set f = sk.OpenEdition()
  DrawRoundedRectAt f, 0, 0, lipOuterL, lipOuterW, 5.4
  DrawRoundedRectAt f, 0, 0, lipInnerL, lipInnerW, 2.9
  sk.CloseEdition
  Set feat = AddPadReverse(part, sk, LIP_H, "PAD_POSITIONING_LIP")

  ' Local 0.2 mm underside calibration recess keeps the start switch panel at
  ' 3.0 mm while the cost-optimised general lid is 3.2 mm.
  Set sk = NewSketch(body, refXY, "SK_LOCAL_THINNING")
  Set f = sk.OpenEdition()
  f.CreateClosedCircle -48, -17, 11
  sk.CloseEdition
  Set feat = AddPocket(part, sk, 0.2, "POCKET_LOCAL_PANEL_T3")

  ' Raised sealing lands keep every supplied component gasket on a controlled,
  ' easily lapped surface. Material is added around the holes; no narrow O-ring
  ' grooves are cut into the 4 mm cover.
  Set pTopFace = AddPlaneOffset(part, hb, refXY, TOP_T, False, "PLN_PANEL_SEAL_LANDS")
  Set sk = NewSketch(body, pTopFace, "SK_PANEL_RAISED_SEAL_LANDS")
  Set f = sk.OpenEdition()
  For i = 0 To 3
    x = Array(-39, -13, 13, 39)(i)
    f.CreateClosedCircle x, 22, 10
    f.CreateClosedCircle x, 22, 8.2
  Next
  f.CreateClosedCircle -48, -17, 9.5
  f.CreateClosedCircle -48, -17, 6.9
  f.CreateClosedCircle 32, -17, 18
  f.CreateClosedCircle 32, -17, 11.2
  sk.CloseEdition
  Set feat = AddPad(part, sk, PANEL_SEAL_PAD_H, "PAD_LED_BUTTON_ESTOP_SEAL_LANDS")

  ' Operator controls and indicators; all values include the +/-0.2 mm SLA allowance.
  Set sk = NewSketch(body, refXY, "SK_PANEL_CUTOUTS")
  Set f = sk.OpenEdition()
  f.CreateClosedCircle -39, 22, 8.2
  f.CreateClosedCircle -13, 22, 8.2
  f.CreateClosedCircle 13, 22, 8.2
  f.CreateClosedCircle 39, 22, 8.2
  f.CreateClosedCircle -48, -17, 6.9       ' start switch D13.8
  f.CreateClosedCircle 32, -17, 11.2       ' emergency stop D22.4
  sk.CloseEdition
  Set feat = AddPocket(part, sk, TOP_T + PANEL_SEAL_PAD_H, "POCKET_PANEL_CUTOUTS")

  AddNotes part, "Wrap-around lid with positive compression stop: use the separate 179 x 141 / 171 x 133 x 3 mm soft silicone flat gasket, compressed to 2.3 mm. Ten side M4 x 8 screws sit outside the seal; each supplied sealing ring clamps directly on the full 3 mm flat skirt. No D11 counterbore is allowed. With screw centre Z62 and 5.0 x 4.6 slots, the minimum solid skirt below a slot is 1.5 mm on the long sides and 1.7 mm on the short sides. LED, start and E-stop holes have raised 0.8 mm gasket lands; retain each component's supplied IP gasket."
  HideObject doc, hb
  part.Update
  Set BuildTopCover = doc
End Function

Function BuildBatteryCover()
  Dim doc, part, body, sf, hb, refXY, p0Down, pBottomExternal, sk, f, feat, i
  Dim lipOuterL, lipOuterW, lipInnerL, lipInnerW
  Dim clL, clW, outerL, outerW, innerL, innerW
  Dim sx, sy

  Set doc = CATIA_APP.Documents.Add("Part")
  Set part = doc.Part
  Set body = part.Bodies.Item(1)
  body.Name = "BATTERY_COVER"
  Set sf = part.ShapeFactory
  Set hb = part.HybridBodies.Add()
  hb.Name = "REFERENCE_PLANES"
  Set refXY = part.OriginElements.PlaneXY
  Set p0Down = AddPlaneOffset(part, hb, refXY, 0, False, "PLN_BAT_COVER_DOWN")
  Set pBottomExternal = AddPlaneOffset(part, hb, refXY, -BAT_COVER_T, False, "PLN_BAT_COVER_EXTERNAL")

  ' Cover base extends down from Z=0 to Z=-4.
  Set sk = NewSketch(body, p0Down, "SK_BAT_COVER_OUTER")
  Set f = sk.OpenEdition()
  DrawRoundedRectAt f, 0, 0, BAT_COVER_L, BAT_COVER_W, 10
  sk.CloseEdition
  Set feat = AddPadReverse(part, sk, BAT_COVER_T, "PAD_BAT_COVER_BASE")

  ' Purchased ID100 x CS2.5 O-ring. A 96 x 72, R8 rounded-rectangle centre
  ' line has a 322.27 mm perimeter, matching 102.5*pi = 322.01 mm.
  clL = 96
  clW = 72
  outerL = clL + SEAL25_GROOVE_W
  outerW = clW + SEAL25_GROOVE_W
  innerL = clL - SEAL25_GROOVE_W
  innerW = clW - SEAL25_GROOVE_W
  Set sk = NewSketch(body, p0Down, "SK_BAT_GASKET_GROOVE")
  Set f = sk.OpenEdition()
  DrawRoundedRectAt f, 0, 0, outerL, outerW, 9.7
  DrawRoundedRectAt f, 0, 0, innerL, innerW, 6.3
  sk.CloseEdition
  Set feat = AddPocketReverse(part, sk, SEAL25_GROOVE_D, "POCKET_BAT_O_RING_100X2_5")

  ' Local external backing ring restores the residual section below the O-ring
  ' groove to 3.1 mm while the general cover is reduced to 3.0 mm for lower
  ' resin cost. It also acts as a broad protective skid around the battery zone.
  Set sk = NewSketch(body, pBottomExternal, "SK_BAT_O_RING_BACKUP")
  Set f = sk.OpenEdition()
  DrawRoundedRectAt f, 0, 0, clL + BAT_GROOVE_BACKUP_W, clW + BAT_GROOVE_BACKUP_W, 12
  DrawRoundedRectAt f, 0, 0, clL - BAT_GROOVE_BACKUP_W, clW - BAT_GROOVE_BACKUP_W, 4
  sk.CloseEdition
  Set feat = AddPadReverse(part, sk, BAT_GROOVE_BACKUP_H, "PAD_BAT_O_RING_BACKUP_W8XH2")

  ' Lip enters the main housing opening with 0.6 mm clearance per side.
  lipOuterL = BAT_OPEN_L - 2 * RESIN_CLEARANCE
  lipOuterW = BAT_OPEN_W - 2 * RESIN_CLEARANCE
  lipInnerL = lipOuterL - 2 * LIP_T
  lipInnerW = lipOuterW - 2 * LIP_T
  Set sk = NewSketch(body, refXY, "SK_BAT_POSITIONING_LIP")
  Set f = sk.OpenEdition()
  DrawRoundedRectAt f, 0, 0, lipOuterL, lipOuterW, 5.4
  DrawRoundedRectAt f, 0, 0, lipInnerL, lipInnerW, 2.9
  sk.CloseEdition
  Set feat = AddPad(part, sk, LIP_H, "PAD_BAT_POSITIONING_LIP")

  ' Outer raised labyrinth wall. It fits the 3 x 2 mm groove in the main
  ' housing with 0.5 mm clearance on both sides and remains 2 mm inboard from
  ' the cover edge. This protects screws and the primary O-ring from direct
  ' splash before water reaches either sealing element.
  Set sk = NewSketch(body, refXY, "SK_BAT_OUTER_LABYRINTH_LIP")
  Set f = sk.OpenEdition()
  DrawRoundedRectAt f, 0, 0, BAT_LAB_CL_L + BAT_LAB_LIP_T, BAT_LAB_CL_W + BAT_LAB_LIP_T, 12
  DrawRoundedRectAt f, 0, 0, BAT_LAB_CL_L - BAT_LAB_LIP_T, BAT_LAB_CL_W - BAT_LAB_LIP_T, 10
  sk.CloseEdition
  Set feat = AddPad(part, sk, BAT_LAB_LIP_H, "PAD_BAT_OUTER_LABYRINTH_LIP_2X1_5")

  ' Eight M4 holes are moved completely outside the O-ring outer envelope.
  ' Matching housing insert pockets are blind, so a wet screw cannot provide
  ' a bypass into the battery slot. Bonded washers remain a secondary seal.
  sx = 57
  sy = 47

  ' Each M4 x 8 screw head and supplied sealing ring sits in a D11 x 0.4 mm
  ' shallow exterior seat. This leaves a 2.6 mm nominal local wall and gives
  ' approximately 5.0 mm nominal brass-thread engagement after seal compression.
  Set sk = NewSketch(body, pBottomExternal, "SK_BAT_SCREW_O_RING_SEATS")
  Set f = sk.OpenEdition()
  For i = -1 To 1
    f.CreateClosedCircle i * 36, sy, BAT_SCREW_SEAT_D / 2
    f.CreateClosedCircle i * 36, -sy, BAT_SCREW_SEAT_D / 2
  Next
  f.CreateClosedCircle sx, 0, BAT_SCREW_SEAT_D / 2
  f.CreateClosedCircle -sx, 0, BAT_SCREW_SEAT_D / 2
  sk.CloseEdition
  Set feat = AddPocket(part, sk, BAT_SCREW_SEAT_DEPTH, "POCKET_BAT_M4_O_RING_SEATS_D11X0_4")

  Set sk = NewSketch(body, p0Down, "SK_BAT_M4_HOLES")
  Set f = sk.OpenEdition()
  For i = -1 To 1
    f.CreateClosedCircle i * 36, sy, COVER_HOLE_D / 2
    f.CreateClosedCircle i * 36, -sy, COVER_HOLE_D / 2
  Next
  f.CreateClosedCircle sx, 0, COVER_HOLE_D / 2
  f.CreateClosedCircle -sx, 0, COVER_HOLE_D / 2
  sk.CloseEdition
  Set feat = AddPocketReverse(part, sk, BAT_COVER_T, "POCKET_BAT_M4_CLEARANCE_D4_8")

  AddNotes part, "Battery cover has three barriers: an outer 2 x 1.5 mm labyrinth wall in a 3.4 x 2 mm housing groove, the ID100 x CS2.5 O-ring, and eight outside M4 x 8 screws mating to blind inserts. The 3.0 mm general plate plus a local W8 x H2.0 backing ring retains 3.1 mm below the O-ring groove. Each screw has a D11 x 0.4 recessed sealing-ring seat, leaving 2.6 mm nominal local wall and about 5.0 mm nominal thread engagement. Use 1 mm EVA above and below the battery and 1 mm EVA on side contact areas."
  HideObject doc, hb
  part.Update
  Set BuildBatteryCover = doc
End Function

Function BuildTopGasket()
  Dim doc, part, body, hb, refXY, sk, f, feat

  Set doc = CATIA_APP.Documents.Add("Part")
  Set part = doc.Part
  Set body = part.Bodies.Item(1)
  body.Name = "TOP_FLAT_GASKET_REFERENCE"
  Set hb = part.HybridBodies.Add()
  hb.Name = "REFERENCE_PLANES"
  Set refXY = part.OriginElements.PlaneXY

  Set sk = NewSketch(body, refXY, "SK_TOP_FLAT_GASKET")
  Set f = sk.OpenEdition()
  DrawRoundedRectAt f, 0, 0, TOP_GASKET_OUTER_L, TOP_GASKET_OUTER_W, 8.5
  DrawRoundedRectAt f, 0, 0, TOP_GASKET_INNER_L, TOP_GASKET_INNER_W, 4.5
  sk.CloseEdition
  Set feat = AddPad(part, sk, TOP_GASKET_T, "PAD_SILICONE_GASKET_T3")

  AddNotes part, "REFERENCE ONLY - do not print in resin. Cut from 3 mm soft closed-cell silicone sheet, Shore A 25-35. Outer 179 x 141, inner 171 x 133. Adhesive-tack to the housing neck; the cover skirt stop compresses it to 2.3 mm."
  HideObject doc, hb
  part.Update
  Set BuildTopGasket = doc
End Function

Function BuildHandleGasket()
  Dim doc, part, body, hb, refXY, sk, f, feat

  Set doc = CATIA_APP.Documents.Add("Part")
  Set part = doc.Part
  Set body = part.Bodies.Item(1)
  body.Name = "HANDLE_FLAT_GASKET_REFERENCE"
  Set hb = part.HybridBodies.Add()
  hb.Name = "REFERENCE_PLANES"
  Set refXY = part.OriginElements.PlaneXY

  Set sk = NewSketch(body, refXY, "SK_HANDLE_FLAT_GASKET")
  Set f = sk.OpenEdition()
  DrawRoundedRectAt f, 0, 0, 71, 36, 4
  f.CreateClosedCircle -32, 0, 3
  f.CreateClosedCircle 32, 0, 3
  sk.CloseEdition
  Set feat = AddPad(part, sk, 1, "PAD_CLOSED_CELL_EPDM_T1")

  AddNotes part, "REFERENCE ONLY - make two pieces from 1 mm closed-cell EPDM. Outer 71 x 36 mm with two D6 holes at 64 mm pitch. Compress below the handle base over the two bonded M5 blind inserts. The pockets do not enter the electronics bay; use a thin neutral-RTV film only as secondary protection around each insert mouth."
  HideObject doc, hb
  part.Update
  Set BuildHandleGasket = doc
End Function

Function BuildM4InsertCoupon()
  Dim doc, part, body, hb, refXY, pTop, sk, f, feat

  Set doc = CATIA_APP.Documents.Add("Part")
  Set part = doc.Part
  Set body = part.Bodies.Item(1)
  body.Name = "M4_INSERT_PROCESS_COUPON"
  Set hb = part.HybridBodies.Add()
  hb.Name = "REFERENCE_PLANES"
  Set refXY = part.OriginElements.PlaneXY

  Set sk = NewSketch(body, refXY, "SK_COUPON_BLOCK")
  Set f = sk.OpenEdition()
  DrawRoundedRectAt f, 0, 0, 52, 20, 3
  sk.CloseEdition
  Set feat = AddPad(part, sk, 12, "PAD_COUPON_52X20X12")

  Set pTop = AddPlaneOffset(part, hb, refXY, 12, False, "PLN_COUPON_TOP")
  Set sk = NewSketch(body, pTop, "SK_COUPON_D4_9_D5_1_D5_3")
  Set f = sk.OpenEdition()
  f.CreateClosedCircle -16, 0, 2.45
  f.CreateClosedCircle 0, 0, 2.55
  f.CreateClosedCircle 16, 0, 2.65
  sk.CloseEdition
  Set feat = AddPocketReverse(part, sk, TOP_INSERT_POCKET_D, "POCKET_COUPON_D4_9_D5_1_D5_3_X8_5")

  Set sk = NewSketch(body, pTop, "SK_COUPON_D5_6_LEAD_INS")
  Set f = sk.OpenEdition()
  f.CreateClosedCircle -16, 0, INSERT_ENTRY_D / 2
  f.CreateClosedCircle 0, 0, INSERT_ENTRY_D / 2
  f.CreateClosedCircle 16, 0, INSERT_ENTRY_D / 2
  sk.CloseEdition
  Set feat = AddPocketReverse(part, sk, INSERT_ENTRY_DEPTH, "POCKET_COUPON_D5_6X0_5_LEAD_INS")

  AddNotes part, "Mandatory same-batch black-resin process coupon. From left to right the blind hole bodies are D4.9, D5.1 and D5.3 mm; all are 8.5 mm deep with a D5.6 x 0.5 lead-in. Supplier nominal is D5.1 for M4 x D5 x L8. Select the smallest hole that accepts the insert without cracking, whitening or radial splitting. Low-temperature assistance does not melt thermoset SLA resin; use toughened epoxy for final retention."
  HideObject doc, hb
  part.Update
  Set BuildM4InsertCoupon = doc
End Function

Function BuildInsulationPlate()
  Dim doc, part, body, hb, refXY, sk, f, feat

  Set doc = CATIA_APP.Documents.Add("Part")
  Set part = doc.Part
  Set body = part.Bodies.Item(1)
  body.Name = "INSULATION_PLATE_FR4"
  Set hb = part.HybridBodies.Add()
  hb.Name = "REFERENCE_PLANES"
  Set refXY = part.OriginElements.PlaneXY

  Set sk = NewSketch(body, refXY, "SK_PLATE_OUTER")
  Set f = sk.OpenEdition()
  DrawRoundedRectAt f, 0, 0, PLATE_L, PLATE_W, 4
  sk.CloseEdition
  Set feat = AddPad(part, sk, PLATE_T, "PAD_FR4_PLATE")

  ' Error-releasing four-point mounting pattern.
  Set sk = NewSketch(body, refXY, "SK_PLATE_MOUNTING")
  Set f = sk.OpenEdition()
  f.CreateClosedCircle -SUPPORT_X, -SUPPORT_Y, 2.4
  DrawHorizontalSlot f, SUPPORT_X, -SUPPORT_Y, 6.5, 4.8
  DrawVerticalSlot f, -SUPPORT_X, SUPPORT_Y, 6.5, 4.8
  f.CreateClosedCircle SUPPORT_X, SUPPORT_Y, 3
  sk.CloseEdition
  Set feat = AddPocket(part, sk, PLATE_T, "POCKET_ERROR_RELEASE_MOUNTS")

  ' Four 8 x 20 mm edge notches preserve rubber-isolator travel above the
  ' handle load bosses. Without these notches the nominal vertical gap is only
  ' 1 mm and a compressed isolator could create an unwanted rigid contact.
  Set sk = NewSketch(body, refXY, "SK_HANDLE_BOSS_TRAVEL_NOTCHES")
  Set f = sk.OpenEdition()
  DrawRectangleAt f, -80, -32, 8, 20
  DrawRectangleAt f, -80, 32, 8, 20
  DrawRectangleAt f, 80, -32, 8, 20
  DrawRectangleAt f, 80, 32, 8, 20
  sk.CloseEdition
  Set feat = AddPocket(part, sk, PLATE_T, "POCKET_4X_HANDLE_BOSS_TRAVEL_NOTCH_8X20")

  AddNotes part, "FR-4 plate 168 x 130 x 2 mm: one datum hole, one X slot, one Y slot and one D6 floating hole. Four 8 x 20 edge notches at Y +/-32 clear the handle bosses throughout isolator travel. It fits flat through the 170 x 132 opening. Use two temporary long M4 screws or cable ties in diagonal holes as lowering handles; install the isolators first, then lower and fasten the empty plate before modules unless every module stays inside the plate outline. Add a 30 x 30 x 2 mm soft closed-cell foam bumper on the battery roof below the plate centre to limit impact deflection without hard over-constraint."
  part.Update
  Set BuildInsulationPlate = doc
End Function

' ----------------------------- CATIA HELPERS -----------------------------

Function NewSketch(body, planeRef, sketchName)
  Dim sk
  Set sk = body.Sketches.Add(planeRef)
  sk.Name = sketchName
  Set NewSketch = sk
End Function

Function AddPad(part, sketch, depth, featureName)
  Dim feature
  part.InWorkObject = sketch
  Set feature = part.ShapeFactory.AddNewPad(sketch, depth)
  feature.DirectionOrientation = 0
  feature.Name = featureName
  part.UpdateObject feature
  Set AddPad = feature
End Function

Function AddPadReverse(part, sketch, depth, featureName)
  Dim feature
  part.InWorkObject = sketch
  Set feature = part.ShapeFactory.AddNewPad(sketch, depth)
  feature.DirectionOrientation = 1
  feature.Name = featureName
  part.UpdateObject feature
  Set AddPadReverse = feature
End Function

Function AddPocket(part, sketch, depth, featureName)
  Dim feature
  part.InWorkObject = sketch
  Set feature = part.ShapeFactory.AddNewPocket(sketch, depth)
  feature.DirectionOrientation = 0
  feature.Name = featureName
  part.UpdateObject feature
  Set AddPocket = feature
End Function

Function AddPocketReverse(part, sketch, depth, featureName)
  Dim feature
  part.InWorkObject = sketch
  Set feature = part.ShapeFactory.AddNewPocket(sketch, depth)
  feature.DirectionOrientation = 1
  feature.Name = featureName
  part.UpdateObject feature
  Set AddPocketReverse = feature
End Function

Function AddPlaneOffset(part, hybridBody, basePlane, offsetValue, reverseNormal, planeName)
  Dim baseRef, planeObj
  Set baseRef = part.CreateReferenceFromObject(basePlane)
  Set planeObj = part.HybridShapeFactory.AddNewPlaneOffset(baseRef, offsetValue, reverseNormal)
  hybridBody.AppendHybridShape planeObj
  planeObj.Name = planeName
  part.UpdateObject planeObj
  Set AddPlaneOffset = part.CreateReferenceFromObject(planeObj)
End Function

Sub SetSketchAxis(sketch, ox, oy, oz, hx, hy, hz, vx, vy, vz)
  Dim axisData(8)
  axisData(0) = ox: axisData(1) = oy: axisData(2) = oz
  axisData(3) = hx: axisData(4) = hy: axisData(5) = hz
  axisData(6) = vx: axisData(7) = vy: axisData(8) = vz
  sketch.SetAbsoluteAxisData axisData
End Sub

Sub DrawRectangleAt(factory2D, cx, cy, rectL, rectW)
  Dim hx, hy
  hx = rectL / 2: hy = rectW / 2
  factory2D.CreateLine cx - hx, cy - hy, cx + hx, cy - hy
  factory2D.CreateLine cx + hx, cy - hy, cx + hx, cy + hy
  factory2D.CreateLine cx + hx, cy + hy, cx - hx, cy + hy
  factory2D.CreateLine cx - hx, cy + hy, cx - hx, cy - hy
End Sub

Sub DrawRoundedRectAt(factory2D, cx, cy, rectL, rectW, radius)
  Dim hx, hy
  hx = rectL / 2: hy = rectW / 2
  factory2D.CreateLine cx - hx + radius, cy - hy, cx + hx - radius, cy - hy
  factory2D.CreateCircle cx + hx - radius, cy - hy + radius, radius, -PI / 2, 0
  factory2D.CreateLine cx + hx, cy - hy + radius, cx + hx, cy + hy - radius
  factory2D.CreateCircle cx + hx - radius, cy + hy - radius, radius, 0, PI / 2
  factory2D.CreateLine cx + hx - radius, cy + hy, cx - hx + radius, cy + hy
  factory2D.CreateCircle cx - hx + radius, cy + hy - radius, radius, PI / 2, PI
  factory2D.CreateLine cx - hx, cy + hy - radius, cx - hx, cy - hy + radius
  factory2D.CreateCircle cx - hx + radius, cy - hy + radius, radius, PI, 3 * PI / 2
End Sub

Sub DrawDProfileAt(factory2D, cx, cy, totalWidth, totalHeight)
  Dim radius, flatX, arcCX
  radius = totalHeight / 2
  flatX = cx - totalWidth / 2
  arcCX = cx + totalWidth / 2 - radius
  factory2D.CreateLine flatX, cy - radius, arcCX, cy - radius
  factory2D.CreateCircle arcCX, cy, radius, -PI / 2, PI / 2
  factory2D.CreateLine arcCX, cy + radius, flatX, cy + radius
  factory2D.CreateLine flatX, cy + radius, flatX, cy - radius
End Sub

Sub DrawHorizontalSlot(factory2D, cx, cy, totalLength, slotWidth)
  Dim r, halfStraight
  r = slotWidth / 2
  halfStraight = (totalLength - slotWidth) / 2
  factory2D.CreateLine cx - halfStraight, cy + r, cx + halfStraight, cy + r
  factory2D.CreateCircle cx + halfStraight, cy, r, -PI / 2, PI / 2
  factory2D.CreateLine cx + halfStraight, cy - r, cx - halfStraight, cy - r
  factory2D.CreateCircle cx - halfStraight, cy, r, PI / 2, 3 * PI / 2
End Sub

Sub DrawVerticalSlot(factory2D, cx, cy, totalLength, slotWidth)
  Dim r, halfStraight
  r = slotWidth / 2
  halfStraight = (totalLength - slotWidth) / 2
  factory2D.CreateLine cx + r, cy - halfStraight, cx + r, cy + halfStraight
  factory2D.CreateCircle cx, cy + halfStraight, r, 0, PI
  factory2D.CreateLine cx - r, cy + halfStraight, cx - r, cy - halfStraight
  factory2D.CreateCircle cx, cy - halfStraight, r, PI, 2 * PI
End Sub

Sub HideObject(doc, obj)
  Dim sel
  On Error Resume Next
  Set sel = doc.Selection
  sel.Clear
  sel.Add obj
  sel.VisProperties.SetShow 1
  sel.Clear
  On Error GoTo 0
End Sub

Sub AddNotes(part, noteText)
  On Error Resume Next
  part.Parameters.CreateString "DESIGN_NOTE", noteText
  part.Parameters.CreateString "TOLERANCE_NOTE", "Black high-toughness SLA resin: local dimensional error +/-0.2 mm plus possible 0.3 mm large-part warp. Verify D4.9/D5.1/D5.3 insert coupons, gasket compression stop and skirt fit before production."
  On Error GoTo 0
End Sub

Sub StepLog(messageText)
  CATIA_APP.StatusBar = messageText
  WScript.Echo messageText
End Sub

Function TimeStampText(dateValue)
  TimeStampText = CStr(Year(dateValue)) & TwoDigits(Month(dateValue)) & TwoDigits(Day(dateValue)) _
    & "_" & TwoDigits(Hour(dateValue)) & TwoDigits(Minute(dateValue)) & TwoDigits(Second(dateValue))
End Function

Function TwoDigits(numberValue)
  If numberValue < 10 Then
    TwoDigits = "0" & CStr(numberValue)
  Else
    TwoDigits = CStr(numberValue)
  End If
End Function

Sub WriteBuildParameters(stream)
  stream.WriteLine "RES enclosure generated by RES_Enclosure_Generator.vbs"
  stream.WriteLine "PRODUCTION MATERIAL = black high-toughness SLA resin, nominal local tolerance +/-0.2 mm"
  stream.WriteLine "BODY = " & BODY_L & " x " & BODY_W & " x " & BODY_H & " mm"
  stream.WriteLine "ASSEMBLED PRINTED HEIGHT INCLUDING RAISED SEAL LANDS = " & BODY_H + TOP_GASKET_COMP_T + TOP_T + PANEL_SEAL_PAD_H + BAT_COVER_T + BAT_GROOVE_BACKUP_H & " mm"
  stream.WriteLine "MAIN CAVITY = " & CAVITY_L & " x " & CAVITY_W & " mm"
  stream.WriteLine "TOP OPENING = " & TOP_OPEN_L & " x " & TOP_OPEN_W & " mm"
  stream.WriteLine "PLATE = " & PLATE_L & " x " & PLATE_W & " x " & PLATE_T & " mm"
  stream.WriteLine "VD ISOLATOR = M4 x " & ISOLATOR_STUD_L & " stud, D" & ISOLATOR_D & " x H" & ISOLATOR_H & " rubber body"
  stream.WriteLine "SHOCK MOUNT = D" & SUPPORT_BASE_D & " x H" & SUPPORT_BASE_H & " base + D" & SUPPORT_COLLAR_D & " x H" & SUPPORT_COLLAR_H & " collar + D" & SUPPORT_POST_D & " post, top Z" & SUPPORT_TOP_Z & " mm"
  stream.WriteLine "SHOCK MOUNT INSERT POCKET = D" & INSERT_HOLE_D & " x " & ISOLATOR_INSERT_POCKET_D & " deep blind pocket with D" & INSERT_ENTRY_D & " x " & INSERT_ENTRY_DEPTH & " lead-in for M4 x D5 x L8 insert and M4 x 8 stud"
  stream.WriteLine "NOMINAL PLATE UNDERSIDE WITH ISOLATOR = Z" & SUPPORT_TOP_Z + ISOLATOR_H & " mm"
  stream.WriteLine "CLEARANCE ABOVE BATTERY ROOF = " & SUPPORT_TOP_Z + ISOLATOR_H - (BAT_SLOT_H + BAT_TRAY_ROOF_T) & " mm"
  stream.WriteLine "RESIN MATING CLEARANCE = " & RESIN_CLEARANCE & " mm per side"
  stream.WriteLine "TOP GASKET = die-cut closed-cell silicone sheet, T" & TOP_GASKET_T & " mm"
  stream.WriteLine "TOP GASKET OUTER / INNER = " & TOP_GASKET_OUTER_L & " x " & TOP_GASKET_OUTER_W & " / " & TOP_GASKET_INNER_L & " x " & TOP_GASKET_INNER_W & " mm"
  stream.WriteLine "TOP GASKET COMPRESSED THICKNESS = " & TOP_GASKET_COMP_T & " mm, controlled by skirt shoulder"
  stream.WriteLine "TOP GASKET GROOVE = NONE; housing neck remains full thickness"
  stream.WriteLine "WRAP-AROUND TOP SKIRT = H" & CAP_SKIRT_H & " x T" & CAP_SKIRT_T & " mm"
  stream.WriteLine "TOP NECK = " & TOP_NECK_L & " x " & TOP_NECK_W & " mm; radial clearance " & RESIN_CLEARANCE & " mm"
  stream.WriteLine "TOP FASTENERS = 10 side M4 x " & M4_COVER_SCREW_L & " sealing screws: front/rear X=-60,0,60 and left/right Y=+/-50 / Z" & SIDE_SCREW_Z & " mm"
  stream.WriteLine "TOP COVER SIDE SLOTS = " & SIDE_SLOT_L & " horizontal x " & SIDE_SLOT_W & " vertical mm; ream vertical width only as required"
  stream.WriteLine "TOP SCREW O-RING SEATS = NONE; supplied sealing rings clamp on the full flat T" & CAP_SKIRT_T & " mm skirt"
  stream.WriteLine "TOP INSERT BOSS NOSE = " & SIDE_BOSS_NOSE & " mm into the nominal " & RESIN_CLEARANCE & " mm skirt gap"
  stream.WriteLine "TOP M4 X 8 NOMINAL ENGAGEMENT = " & M4_COVER_SCREW_L - CAP_SKIRT_T - (RESIN_CLEARANCE - SIDE_BOSS_NOSE) - 0.4 & " mm assuming 0.4 mm compressed screw seal"
  stream.WriteLine "TOP SLOT MINIMUM LOWER SKIRT = long sides " & CAP_SKIRT_H + SIDE_SCREW_Z - BODY_H - TOP_GASKET_COMP_T - SIDE_SLOT_L / 2 & " mm / short sides " & CAP_SKIRT_H + SIDE_SCREW_Z - BODY_H - TOP_GASKET_COMP_T - SIDE_SLOT_W / 2 & " mm"
  stream.WriteLine "TOP SIDE INSERT BOSS+NOSE / POCKET / BLIND WALL = " & SIDE_BOSS_DEPTH + SIDE_BOSS_NOSE & " / " & TOP_INSERT_POCKET_D & " / " & SIDE_BOSS_DEPTH + SIDE_BOSS_NOSE - TOP_INSERT_POCKET_D & " mm"
  stream.WriteLine "TOP SIDE M4 BOSS RIBS = horizontal double-arm span " & BOSS_RIB_SPAN & " x thickness " & BOSS_RIB_T & " x depth " & SIDE_RIB_DEPTH & " mm; no vertical rib may cross Z68 seal interface"
  stream.WriteLine "BOTTOM M4 BOSS ROOT RIBS = four-way span " & BOSS_RIB_SPAN & " x thickness " & BOSS_RIB_T & " x height " & BOTTOM_RIB_H & " mm"
  stream.WriteLine "TOP FACE SCREW PENETRATIONS = NONE"
  stream.WriteLine "CONTINUOUS SECONDARY TOP LIP = 140 x 108 x " & LIP_H & " mm, wall " & LIP_T & " mm"
  stream.WriteLine "TOP O-RING = NOT USED"
  stream.WriteLine "PURCHASED BATTERY O-RING = NBR ID100 x CS2.5 mm"
  stream.WriteLine "PURCHASED HANDLE O-RINGS ID60 x CS2.5 = NOT USED; insufficient edge margin on the 73 x 38 handle bases"
  stream.WriteLine "PURCHASED ID20 x CS1 = use only below D16 LED bezels if flange OD >= 23 mm"
  stream.WriteLine "BATTERY INPUT = " & BAT_L & " x " & BAT_W & " x " & BAT_H & " mm"
  stream.WriteLine "BATTERY SLOT INTERNAL = " & BAT_SLOT_L & " x " & BAT_SLOT_W & " x " & BAT_SLOT_H & " mm"
  stream.WriteLine "BATTERY SLOT WALL = " & BAT_TRAY_WALL & " mm"
  stream.WriteLine "BATTERY SLOT ROOF = " & BAT_TRAY_ROOF_T & " mm"
  stream.WriteLine "BATTERY CABLE PASSAGE = 14 x 8 mm"
  stream.WriteLine "BATTERY OPENING = " & BAT_OPEN_L & " x " & BAT_OPEN_W & " mm"
  stream.WriteLine "BATTERY COVER = " & BAT_COVER_L & " x " & BAT_COVER_W & " mm"
  stream.WriteLine "BATTERY OUTER LABYRINTH = cover lip T" & BAT_LAB_LIP_T & " x H" & BAT_LAB_LIP_H & " in housing groove W" & BAT_LAB_GROOVE_W & " x D" & BAT_LAB_GROOVE_D & " mm"
  stream.WriteLine "BATTERY LABYRINTH BACKUP = inner annular rib W" & BAT_LAB_BACKUP_W & " x H" & BAT_LAB_BACKUP_H & " mm; local residual section 3.5 mm"
  stream.WriteLine "BATTERY O-RING GROOVE BACKUP = external annular rib W" & BAT_GROOVE_BACKUP_W & " x H" & BAT_GROOVE_BACKUP_H & " mm; worst nominal local residual section " & BAT_COVER_T - SEAL25_GROOVE_D + BAT_GROOVE_BACKUP_H & " mm"
  stream.WriteLine "BATTERY M4 COVER CLEARANCE HOLES = D" & COVER_HOLE_D & " mm"
  stream.WriteLine "BOTTOM/SHOCK M4 INSERT LEAD-IN = D" & INSERT_ENTRY_D & " x " & INSERT_ENTRY_DEPTH & " mm"
  stream.WriteLine "MANDATORY INSERT COUPON = left/middle/right D4.9/D5.1/D5.3 x 8.5 mm, all with D5.6 x 0.5 lead-in"
  stream.WriteLine "TOP SIDE M4 INSERT POCKETS = straight D" & INSERT_HOLE_D & " x " & TOP_INSERT_POCKET_D & " deep mm for L8 insert; hand deburr/chamfer mouth 0.2-0.3 mm after printing"
  stream.WriteLine "BOTTOM M4 LOW-TEMP INSERT POCKETS = nominal D" & INSERT_HOLE_D & " x " & TOP_INSERT_POCKET_D & " deep mm; boss H" & BOTTOM_BOSS_H & " mm; verify D4.9/D5.1/D5.3 coupons"
  stream.WriteLine "BATTERY SCREW CENTRES = X +/-57 at Y0, plus X -36/0/36 at Y +/-47 mm"
  stream.WriteLine "BATTERY SCREW HOLES = outside O-ring; matching insert pockets are blind"
  stream.WriteLine "BATTERY FASTENERS = eight M4 x " & M4_COVER_SCREW_L & " sealing screws"
  stream.WriteLine "BATTERY SCREW SEALS = D" & BAT_SCREW_SEAT_D & " x D" & BAT_SCREW_SEAT_DEPTH & " recessed seats plus supplied screw O-rings"
  stream.WriteLine "BATTERY M4 X 8 NOMINAL ENGAGEMENT = " & M4_COVER_SCREW_L - (BAT_COVER_T - BAT_SCREW_SEAT_DEPTH) - 0.4 & " mm assuming 0.4 mm compressed screw seal"
  stream.WriteLine "PRINTED MAIN HOUSING = " & BODY_L & " x " & BODY_W & " x " & BODY_H & " mm"
  stream.WriteLine "ASSEMBLED PRINTED ENCLOSURE = " & BODY_L & " x " & BODY_W & " x " & BODY_H + TOP_GASKET_COMP_T + TOP_T + PANEL_SEAL_PAD_H + BAT_COVER_T + BAT_GROOVE_BACKUP_H & " mm"
  stream.WriteLine "FLUSH HANDLES = 2 pcs, " & HANDLE_BASE_L & " x " & HANDLE_BASE_H & " x 6 mm, 64 mm pitch"
  stream.WriteLine "HANDLE CENTRES ON LEFT/RIGHT WALLS = Y" & HANDLE_CENTER_Y & " / Z" & HANDLE_CENTER_Z
  stream.WriteLine "HANDLE INSERTS = two M5 x D7 x L8 bonded inserts per side at 64 mm pitch"
  stream.WriteLine "HANDLE BLIND POCKET / LOCAL BOSS = D" & HANDLE_INSERT_D & " x " & HANDLE_INSERT_POCKET_D & " deep / D" & HANDLE_BOSS_D & " x H" & HANDLE_BOSS_DEPTH & " mm"
  stream.WriteLine "HANDLE INSERT LEAD-IN = D" & HANDLE_ENTRY_D & " x " & HANDLE_ENTRY_DEPTH & " mm"
  stream.WriteLine "HANDLE BLIND-END WALL = " & WALL + HANDLE_BOSS_DEPTH - HANDLE_INSERT_POCKET_D & " mm nominal; no through-hole"
  stream.WriteLine "NOMINAL ENVELOPE INCLUDING INTEGRAL STRAP LOOPS = 200 x 150 x " & BODY_H + TOP_GASKET_COMP_T + TOP_T + PANEL_SEAL_PAD_H + BAT_COVER_T + BAT_GROOVE_BACKUP_H & " mm"
  stream.WriteLine "INTEGRAL STRAP LOOPS = centred Y" & STRAP_CENTER_Y & " / Z" & STRAP_CENTER_Z & ", outer 40 x 22, clear 26 x 9, stand-off 2.5 + bridge 3.5, no wall holes"
  stream.WriteLine "HANDLE SEAL = die-cut 71 x 36 x 1 mm closed-cell EPDM full-face gasket; no resin groove"
  stream.WriteLine "HANDLE BACKPLATE = NONE; load enters through two local D" & HANDLE_BOSS_D & " blind bosses"
  stream.WriteLine "ALL-WALL SELECTIVE WAFFLE RELIEF = inner pockets up to " & WALL_RELIEF_CELL_X & " x " & WALL_RELIEF_CELL_Z & " x D" & WALL_RELIEF_D & " mm; continuous outer skin " & WALL - WALL_RELIEF_D & " mm"
  stream.WriteLine "PLATE CENTRE BUMPER = 30 x 30 x 2 mm soft closed-cell silicone/EPDM foam on battery roof; damping contact only, not a rigid fifth mount"
  stream.WriteLine "M4 STRUCTURAL CLEARANCE HOLES = D4.8 mm"
  stream.WriteLine "E-STOP CUTOUT = D22.4 mm"
  stream.WriteLine "LED CUTOUTS = D16.4 mm"
  stream.WriteLine "START CUTOUT = D13.8 mm"
  stream.WriteLine "PANEL OPENING SEAL LANDS = raised " & PANEL_SEAL_PAD_H & " mm around LEDs/start/E-stop"
  stream.WriteLine "SMA CUTOUT = FRONT WALL X" & SMA_X & " / Z" & SMA_Z & ", D" & SMA_HOLE_D & " mm, local panel T3 mm"
  stream.WriteLine "SMA SEAL LAND = flush D22 annulus on the Y=75 wall; no supports or texture"
  stream.WriteLine "WARNING: Measure the real battery, switches, LEDs, SMA connector and inserts before manufacture."
End Sub
