# Installer for Isle Sound Enhancer — target layout per DESIGN.md section 4.
#   C:\IsleSoundEnhancer\
#       IsleSoundEnhancer.exe
#       ise.dll                    (audio-hook DLL, mechanism-dependent)
#       settings.json
#       rtgrid.bin                 (cached grid; refreshed on built_at change)
#       zone_masks.json            (cached masks; refreshed on load)
#       logs\
# If the hook mechanism needs a game-side file, it is placed in the game's
# Binaries\Win64\ (section 5 — PENDING boss's hook decision).
# MUST NOT touch the webui or the Pi.

!include "MUI2.nsh"

Name "Isle Sound Enhancer"
OutFile "IsleSoundEnhancer-Setup.exe"
InstallDir "$PROGRAMFILES64\IsleSoundEnhancer"
Unicode True

!define MUI_ABORTWARNING
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_LANGUAGE "English"

Section "Install"
  SetOutPath "$INSTDIR"
  File "..\build\Release\IsleSoundEnhancer.exe"
  File "settings.json"
  ; File "ise.dll"          ; hook DLL — wire in per DESIGN.md section 5
  CreateDirectory "$INSTDIR\logs"

  ; Start with Windows (per DESIGN.md section 7) — registry for the current
  ; user; the real run command lands once the tray app shape is final.
  WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Run" \
              "IsleSoundEnhancer" '"$INSTDIR\IsleSoundEnhancer.exe"'

  ; Game-side hook placement — ONLY when the mechanism requires it
  ; (section 5 pending). Leave commented until then.
  ; SetOutPath "$PROGRAMFILES64\TheIsle\Binaries\Win64"
  ; File "ise.dll"

  WriteUninstaller "$INSTDIR\Uninstall.exe"
SectionEnd

Section "Uninstall"
  Delete "$INSTDIR\IsleSoundEnhancer.exe"
  Delete "$INSTDIR\settings.json"
  RMDir /r "$INSTDIR\logs"
  DeleteRegValue HKCU "Software\Microsoft\Windows\CurrentVersion\Run" \
                 "IsleSoundEnhancer"
  Delete "$INSTDIR\Uninstall.exe"
  RMDir "$INSTDIR"
SectionEnd
