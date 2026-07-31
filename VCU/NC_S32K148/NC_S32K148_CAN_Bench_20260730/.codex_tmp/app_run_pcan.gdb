set pagination off
set confirm off
set logging file C:/Users/icemi/Desktop/RZS_Repository/VCU/NC_S32K148/NC_S32K148_CAN_Bench_20260730/.codex_tmp/gdb_app_run.log
set logging overwrite on
set logging on
set target-async on
target remote localhost:2331
monitor reset halt
set $msp = *(unsigned int *)0x00020000
set $psp = 0
set $xpsr = 0x01000000
set $pc = Reset_Handler
hbreak main
continue
printf "APP_MAIN_REACHED pc=0x%x sp=0x%x\n", $pc, $sp
delete 1
continue&
shell python "C:/Users/icemi/Desktop/RZS_Repository/VCU/NC_S32K148/NC_S32K148_CAN_Bench_20260730/Bench_Test/pcan_raw_can0_smoke.py" > "C:/Users/icemi/Desktop/RZS_Repository/VCU/NC_S32K148/NC_S32K148_CAN_Bench_20260730/.codex_tmp/pcan_during_gdb.log" 2>&1
interrupt
info registers pc sp lr xpsr
x/1wx 0xE000ED28
x/1wx 0xE000ED08
monitor go
disconnect
set logging off
quit
