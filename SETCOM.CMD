@echo Enter the COM_PORT_NUMBER
@set /p SERCOMNO=
@echo %SERCOMNO% > TWI_COM.CFG
@mode COM%SERCOMNO% baud=115200 parity=n data=8
