rem ����˳�򲻿��������,��������DBMgr,�����⿪�ŵ�LoginApp
rem --appid��ServerConfig.xml��AppID,���ڶ�Ӧ��ط�������ȡ�������ã�ͬʱҲ���������͹�����ͬ���ͽ���

@echo off
ping /n 4 127.1>nul
start DBMgrApp.exe --appid=1
ping /n 4 127.1>nul
start BaseCenterApp.exe --appid=2
ping /n 4 127.1>nul
start GameCenterApp.exe --appid=3
ping /n 4 127.1>nul
start BaseApp.exe --appid=100
ping /n 4 127.1>nul
start InterfaceApp.exe --appid=6
ping /n 4 127.1>nul
start PaymentApp.exe --appid=5
ping /n 1 127.1>nul
start LoginApp.exe --appid=4
ping /n 4 127.1>nul