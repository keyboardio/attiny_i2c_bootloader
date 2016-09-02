@rem TWIBL (TWO WIRE INTERFACE BOOTLOADER SCRIPT)
@rem 
@set MAIN_PROG=TWI_PROG
@set NLM=^


@set NL=^^^%NLM%%NLM%^%NLM%%NLM%
@set DEV=ATmega2560

@if NOT EXIST TWI_COM.CFG (
@SETCOM
@if s%1 EQU sCOMSETUP (
@goto QT
)
) else (
@set /P SERCOMNO= < TWI_COM.CFG
)

@if s%1 EQU s (
@echo %NL%usage :%NL%
@echo  TWIBL COMSETUP
@echo  TWIBL AVERSION 
@echo  TWIBL BVERSION
@rem echo  TWIBL STATUS
@echo  TWIBL ERASE
@echo  TWIBL UPDATE {filename.hex}
@echo  TWIBL EXEC
@rem echo  TWIBL CRC
@rem echo  TWIBL AVROSP {command line to go directly to avrosp}
@echo  TWIBL HOSTSIG
@echo  TWIBL DIAG 
@echo %NL%%NL%%NL%TWIBL USER INTERFACE
@echo Version 1.2%NL%
@goto QTF
)
@if %1 EQU COMSETUP (
@DEL TWI_COM.CFG
@SETCOM
@goto QT
)
@if %1 EQU AVERSION (
@echo APPLICATION VERSION:
@%MAIN_PROG% -d%DEV% -cCOM%SERCOMNO% -l61 > TWIBL_DUMP
@%MAIN_PROG% -d%DEV% -cCOM%SERCOMNO% -y >> TWIBL_DUMP
@extr01 TWIBL_DUMP
@goto QT
)
@if %1 EQU BVERSION (
@echo BOOTLOADER VERSION:
@%MAIN_PROG% -d%DEV% -cCOM%SERCOMNO% -l62 > TWIBL_DUMP
@%MAIN_PROG% -d%DEV% -cCOM%SERCOMNO% -y >> TWIBL_DUMP
@extr01 TWIBL_DUMP
@goto QT
)
@if %1 EQU ERASE (
@echo ERASING APPLICATION SECTION...
@%MAIN_PROG% -d%DEV% -cCOM%SERCOMNO% -e > TWIBL_DUMP
@extr01 TWIBL_DUMP
@goto QT
) 
@if %1 EQU EXEC (
@echo EXECUTING APPLICATION...
@%MAIN_PROG% -d%DEV% -cCOM%SERCOMNO% -bs > TWIBL_DUMP
@extr01 TWIBL_DUMP
@goto QT
) 
@if %1 EQU UPDATE (
@echo PROGRAMMING APPLICATION SECTION.... DO TWIBL DIAG TO RETRIVE DETAILS
@%MAIN_PROG% -d%DEV% -cCOM%SERCOMNO% -pf -if%2 > TWIBL_DUMP
@extr01 TWIBL_DUMP
@goto QT
)
@if %1 EQU STATUS (
@%MAIN_PROG% -d%DEV% -cCOM%SERCOMNO% -l66 > TWIBL_DUMP
@%MAIN_PROG% -d%DEV% -cCOM%SERCOMNO% -y >> TWIBL_DUMP
@echo The Status Code or Error Condition is
@extr01 TWIBL_DUMP
@goto QT
)
@if %1 EQU AVROSP (
%MAIN_PROG% %2 %3 %4 %5 %6 %7 %8 %9
@goto QT
)
@if %1 EQU DIAG (
@TYPE TWIBL_DUMP
@goto QT
)
@if %1 EQU HOSTSIG (
@%MAIN_PROG% -d%DEV% -cCOM%SERCOMNO% -s
@goto QT
)
@if %1 EQU CRC (
@%MAIN_PROG% -d%DEV% -cCOM%SERCOMNO% -l63 > TWIBL_DUMP
@%MAIN_PROG% -d%DEV% -cCOM%SERCOMNO% -l64 >> TWIBL_DUMP
@%MAIN_PROG% -d%DEV% -cCOM%SERCOMNO% -y >> TWIBL_DUMP
@extr01 TWIBL_DUMP
@%MAIN_PROG% -d%DEV% -cCOM%SERCOMNO% -l65 > TWIBL_DUMP
@%MAIN_PROG% -d%DEV% -cCOM%SERCOMNO% -y >> TWIBL_DUMP
@extr01 TWIBL_DUMP
@goto QT
)
@echo No Such Command Recognized
@echo Type TWIBL without any parameters to see usage help
@goto QTF
:QT 
:QTF

