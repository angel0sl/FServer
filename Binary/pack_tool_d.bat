cls 
@echo off
::���ԭ��Ŀ¼���ļ�
rd /s/q .\Game
::�½���Ŀ¼��ʼcopy
mkdir .\Game
mkdir .\Game\Log
::����bat�ļ�
xcopy .\start_d.bat .\Game\ /y
xcopy .\close_d.bat .\Game\ /y
::lib��dll�ļ�
xcopy .\libmysql.dll .\Game\ /y
xcopy .\libcurld.dll .\Game\ /y
xcopy .\Lib\Core_d.lib .\Game\Lib\ /y
xcopy .\Lib\hiredis_d.lib .\Game\Lib\ /y
xcopy .\Lib\libevent_d.lib .\Game\Lib\ /y
xcopy .\Lib\libglog_static_d.lib .\Game\Lib\ /y
xcopy .\Lib\libmysql.lib .\Game\Lib\ /y
xcopy .\Lib\libprotobuf_d.lib .\Game\Lib\ /y
xcopy .\Lib\libprotoc_d.lib .\Game\Lib\ /y
xcopy .\Lib\lua_d.lib .\Game\Lib\ /y
xcopy .\Lib\mysqlpp_d.lib .\Game\Lib\ /y
xcopy .\Lib\Win32_Interop_d.lib .\Game\Lib\ /y
::exe�ļ�
xcopy .\BaseApp_d.exe .\Game\ /y
xcopy .\BaseCenterApp_d.exe .\Game\ /y
xcopy .\CubbyApp_d.exe .\Game\ /y
xcopy .\DBMgrApp_d.exe .\Game\ /y
xcopy .\GameApp_d.exe .\Game\ /y
xcopy .\GameCenterApp_d.exe .\Game\ /y
xcopy .\InterfaceApp_d.exe .\Game\ /y
xcopy .\LoginApp_d.exe .\Game\ /y
xcopy .\PaymentApp_d.exe .\Game\ /y
::��Դ���ñ��ű�
xcopy .\Resource\Config .\Game\Resource\Config /s/e/i/y
xcopy .\Resource\Script .\Game\Resource\Script /s/e/i/y

@echo off
echo Copy finished ...

@echo off
pause