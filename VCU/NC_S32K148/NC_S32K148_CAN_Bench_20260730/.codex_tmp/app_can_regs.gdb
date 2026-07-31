set pagination off
set confirm off
set target-async on
set logging file C:/Users/icemi/Desktop/RZS_Repository/VCU/NC_S32K148/NC_S32K148_CAN_Bench_20260730/.codex_tmp/gdb_can_regs.log
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
hbreak OS_Task_CanOut
continue
printf "CAN_TASK_REACHED pc=0x%x sp=0x%x\n", $pc, $sp
delete 2
continue&
shell ping 127.0.0.1 -n 4 > nul
interrupt -a
info registers pc sp lr xpsr
printf "PrgSts:\n"
p PrgSts
printf "CAN0 MCR CTRL1 TIMER ECR ESR1 IMASK1 IFLAG1 CTRL2:\n"
x/1wx 0x40024000
x/1wx 0x40024004
x/1wx 0x40024008
x/1wx 0x4002401c
x/1wx 0x40024020
x/1wx 0x40024028
x/1wx 0x40024030
x/1wx 0x40024034
printf "PCC_CAN0 PORTE_PCR4 PORTE_PCR5:\n"
x/1wx 0x40065090
x/1wx 0x4004d010
x/1wx 0x4004d014
printf "SCB CFSR VTOR:\n"
x/1wx 0xE000ED28
x/1wx 0xE000ED08
monitor go
disconnect
set logging off
quit
