rem This file exports Zeta to a predefined location.

set SRC=ZetaCore\src
set LIB_SRC_DEBUG=bin\Debug
set LIB_SRC_RELEASE=bin\Release
set DEST=..\..\Libs\Zeta\
set INCLUDE_DEST=%DEST%\include\zeta
set LIB_DEST=%DEST%\bin

del /s /q %DEST%
rmdir /s /q %DEST%

xcopy %SRC%\*.h %INCLUDE_DEST% /s /i

echo f|xcopy %LIB_SRC_DEBUG%\ZetaCoreD.lib %LIB_DEST%\ZetaCoreD.lib
echo f|xcopy %LIB_SRC_DEBUG%\ZetaCoreD.pdb %LIB_DEST%\ZetaCoreD.pdb
echo f|xcopy %LIB_SRC_RELEASE%\ZetaCore.lib %LIB_DEST%\ZetaCore.lib
echo f|xcopy %LIB_SRC_RELEASE%\FreeImage.dll %LIB_DEST%\FreeImage.dll

pause