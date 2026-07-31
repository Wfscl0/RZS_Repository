set pagination off
set confirm off
target remote localhost:2331
monitor reset halt
set $msp = *(unsigned int *)0x00020000
set $psp = 0
set $xpsr = 0x01000000
set $pc = Reset_Handler
hbreak main
continue
printf "APP_MAIN_REACHED pc=0x%x sp=0x%x\n", $pc, $sp
delete breakpoints
set $pc = main
monitor go
detach
quit
