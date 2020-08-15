@echo off
set tmpdir=release
echo 正在创建安装包...
set rardir="C:\Program Files\WinRAR\WinRAR.exe"
if not exist %rardir% (set rardir="C:\Program Files (x86)\WinRAR\WinRAR.exe")
%rardir%  a -as -r -sfx -zIPCActiveX\rar\sfxpara.ini  -EP1  "IPCActiveX.exe" %tmpdir%\XPLAY.dll %tmpdir%\ARNET_SDK.dll %tmpdir%\EventContent.dll %tmpdir%\GxxWebClient.ocx %tmpdir%\IPCActiveX.bat %tmpdir%\pthreadGC2.dll %tmpdir%\AR.dll  %tmpdir%\XPlay.ini   %tmpdir%\ARNET_SDK.ini
echo 打包完成!
pause

