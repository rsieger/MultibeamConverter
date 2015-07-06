; Script nerated by the HM NIS Edit Script Wizard.

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "MultibeamConverter"
!define PRODUCT_VERSION "2.1.1"
!define PRODUCT_PUBLISHER "PANGAEA"
!define PRODUCT_WEB_SITE "http://www.pangaea.de"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\MultibeamConverter.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "C:\Users\rsieger\Documents\Development\Distribution\MultibeamConverter\License\License.txt"
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\MultibeamConverter.exe"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"

; MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "C:\Users\rsieger\Documents\Development\Distribution\MultibeamConverter_Win.exe"
InstallDir "$PROGRAMFILES\PANGAEA\MultibeamConverter"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show
RequestExecutionLevel admin

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  File "C:\Users\rsieger\Documents\Development\Distribution\MultibeamConverter\MultibeamConverter.exe"
  File "C:\Users\rsieger\Documents\Development\Distribution\MultibeamConverter\Qt5Core.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\MultibeamConverter\Qt5Gui.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\MultibeamConverter\Qt5Network.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\MultibeamConverter\Qt5Widgets.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\MultibeamConverter\icudt54.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\MultibeamConverter\icuin54.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\MultibeamConverter\icuuc54.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\MultibeamConverter\libgcc_s_dw2-1.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\MultibeamConverter\libstdc++-6.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\MultibeamConverter\libwinpthread-1.dll"

  SetOutPath "$INSTDIR\platforms"
  File "C:\Users\rsieger\Documents\Development\Distribution\MultibeamConverter\platforms\qminimal.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\MultibeamConverter\platforms\qwindows.dll"

  SetOutPath "$INSTDIR\License"
  File "C:\Users\rsieger\Documents\Development\Distribution\MultibeamConverter\License\gpl-3.0.txt"
  File "C:\Users\rsieger\Documents\Development\Distribution\MultibeamConverter\License\License.txt"
  File "C:\Users\rsieger\Documents\Development\Distribution\MultibeamConverter\License\Readme.txt"
  
  CreateDirectory "$SMPROGRAMS\PANGAEA"
  CreateDirectory "$SMPROGRAMS\PANGAEA\MultibeamConverter"
  CreateShortCut "$SMPROGRAMS\PANGAEA\MultibeamConverter\MultibeamConverter.lnk" "$INSTDIR\MultibeamConverter.exe"
  CreateShortCut "$DESKTOP\MultibeamConverter.lnk" "$INSTDIR\MultibeamConverter.exe"
SectionEnd

Section -AdditionalIcons
  CreateShortCut "$SMPROGRAMS\PANGAEA\MultibeamConverter\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\MultibeamConverter.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\MultibeamConverter.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) was successfully removed from your computer."
FunctionEnd

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove $(^Name) and all of its components?" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  Delete "$INSTDIR\MultibeamConverter.exe"
  Delete "$INSTDIR\Qt5Core.dll"
  Delete "$INSTDIR\Qt5Gui.dll"
  Delete "$INSTDIR\Qt5Network.dll"
  Delete "$INSTDIR\Qt5Widgets.dll"
  Delete "$INSTDIR\icudt54.dll"
  Delete "$INSTDIR\icuin54.dll"
  Delete "$INSTDIR\icuuc54.dll"
  Delete "$INSTDIR\libgcc_s_dw2-1.dll"
  Delete "$INSTDIR\libstdc++-6.dll"
  Delete "$INSTDIR\libwinpthread-1.dll"
  Delete "$INSTDIR\platforms\qminimal.dll"
  Delete "$INSTDIR\platforms\qwindows.dll"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\License\Readme.txt"
  Delete "$INSTDIR\License\License.txt"
  Delete "$INSTDIR\License\gpl-3.0.txt"

  Delete "$SMPROGRAMS\PANGAEA\MultibeamConverter\Uninstall.lnk"
  Delete "$SMPROGRAMS\PANGAEA\MultibeamConverter\MultibeamConverter.lnk"
  Delete "$DESKTOP\MultibeamConverter.lnk"

  RMDir "$SMPROGRAMS\PANGAEA\MultibeamConverter"
  RMDir "$INSTDIR\License"
  RMDir "$INSTDIR\platforms"
  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd
