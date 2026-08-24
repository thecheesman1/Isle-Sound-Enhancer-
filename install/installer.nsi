# TODO(agent-2, piece 2): installer harness placeholder.
# The real setup spec (file layout, target dirs, no game-file overwrites,
# uninstall, architecture check) comes from helper-1's design doc (piece 1).
# Choice: NSIS or Inno per design doc. This template is NOT production-ready.

!include "MUI2.nsh"

Name "Isle Sound Enhancer"
OutFile "IsleSoundEnhancer-Setup.exe"
Unicode True

!define MUI_ABORTWARNING
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_LANGUAGE "English"

Section "Install"
  ; Placeholder - destination and file set are design-doc driven.
  ; SetOutPath "$INSTDIR"
  ; File "..\build\Release\isle_sound_enhancer.exe"
SectionEnd

Section "Uninstall"
  ; Placeholder.
SectionEnd
