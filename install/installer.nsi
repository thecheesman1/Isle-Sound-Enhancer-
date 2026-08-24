# Installer for Isle Sound Enhancer — target layout per DESIGN.md section 4.
#   C:\IsleSoundEnhancer\
#       IsleSoundEnhancer.exe
#       ise_apo.dll                (APO COM effect — REGISTERED, not dropped
#                                  into the game dir; runs in audiodg)
#       settings.json
#       rtgrid.bin                 (cached grid; refreshed on built_at change)
#       zone_masks.json            (cached masks; refreshed on load)
#       logs\
# Hook = Windows APO on the render endpoint (section 5, LOCKED): register the
# COM APO on the output endpoint + store the DSP params over IPC (property
# store / named pipe). WASAPI loopback = fallback (no game-dir files either).
# MUST NOT touch the webui or the Pi. Built on a dev machine / client PC
# only (boss no-Pi-compile rule); artifacts go to GitHub Releases/central
# store.

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
  File "..\build\Release\ise_apo.dll"     ; APO COM effect
  File "settings.json"
  CreateDirectory "$INSTDIR\logs"

  ; Start with Windows (per DESIGN.md section 7) — registry for the current
  ; user; the real run command lands once the tray app shape is final.
  WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Run" \
              "IsleSoundEnhancer" '"$INSTDIR\IsleSoundEnhancer.exe"'

  ; Register the APO COM object (effect on the render endpoint). regsvr32
  ; or self-registration flag — real command per the APO implementation
  ; (piece 2/3). Runs in audiodg; no game-dir file, no game overwrite.
  ; ExecWait "regsvr32 /s $INSTDIR\ise_apo.dll"

  WriteUninstaller "$INSTDIR\Uninstall.exe"
SectionEnd

Section "Uninstall"
  Delete "$INSTDIR\IsleSoundEnhancer.exe"
  Delete "$INSTDIR\ise_apo.dll"
  Delete "$INSTDIR\settings.json"
  RMDir /r "$INSTDIR\logs"
  DeleteRegValue HKCU "Software\Microsoft\Windows\CurrentVersion\Run" \
                 "IsleSoundEnhancer"
  ; Unregister the APO COM object (mirror of the install step).
  Delete "$INSTDIR\Uninstall.exe"
  RMDir "$INSTDIR"
SectionEnd
