set pagination off
set confirm off
set logging file C:/Users/icemi/Desktop/RZS_Repository/VCU/NC_S32K148/NC_S32K148_CAN_Bench_20260730/.codex_tmp/gdb_can0_rx.log
set logging overwrite on
set logging on
target remote localhost:2331
monitor reset halt
set $msp = *(unsigned int *)0x00020000
set $psp = 0
set $xpsr = 0x01000000
set $pc = Reset_Handler
hbreak main
continue
delete 1
hbreak CAN0_Callback
continue
printf "CAN0_CALLBACK_REACHED event=%u buffIdx=%u pc=0x%x\n", event, buffIdx, $pc
p/x recvMsg_CAN0_STD
p PrgSts
x/1wx 0x4002401c
x/1wx 0x40024020
x/1wx 0x40024030
delete
monitor go
disconnect
set logging off
quit
