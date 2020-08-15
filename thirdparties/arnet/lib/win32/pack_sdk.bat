@echo off
set tmpdir=win32\release
echo 正在创建安装包...
set rardir="C:\Program Files\WinRAR\WinRAR.exe"
set filename="bin/ARSDK3.1.1_%date:~0,4%%date:~5,2%%date:~8,2%win32.rar"
echo %filename%

if not exist %rardir% (set rardir="C:\Program Files (x86)\WinRAR\WinRAR.exe")
%rardir%  a -as -r -EP1  \
%filename% \
%tmpdir%\libmysql.dll \
%tmpdir%\XPLAY.dll %tmpdir%\ARNET_SDK.dll %tmpdir%\IPCSDK.dll %tmpdir%\NVDDec.dll %tmpdir%\IMSDec.dll %tmpdir%\ARNET_SDK.lib %tmpdir%\XPLAY.lib %tmpdir%\IPCSDK.lib %tmpdir%\XPLAY.pdb %tmpdir%\ARNET_SDK.pdb  %tmpdir%\IPCSDK.pdb %tmpdir%\IPCSDK.pdb %tmpdir%\NVDDec.pdb %tmpdir%\AR_DEFINE.h %tmpdir%\ARNET_DATATYPE.H %tmpdir%\IPC_DATATYPE.H %tmpdir%\IPC_SDK.h %tmpdir%\ARNET_SDK.h %tmpdir%\net_protocol.h %tmpdir%\net_protocol_robot.h %tmpdir%\XPlay.h %tmpdir%\readme.ini %tmpdir%\xplay.ini %tmpdir%\ARNET_SDK.ini GXXIPC播放库开发使用手册_V1.1.0.doc GXXIPC客户端SDK开发使用手册_V2.0.doc %tmpdir%\w.exe  %tmpdir%\pthreadGC2.dll

echo 打包完成!
pause