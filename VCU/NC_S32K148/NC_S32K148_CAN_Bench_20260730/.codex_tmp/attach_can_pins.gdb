set pagination off
set confirm off
target remote localhost:2331
info registers pc sp xpsr
printf "PTE_PDIR (bit4=CAN0_RX, bit5=CAN0_TX pad):\n"
x/1wx 0x400ff110
printf "CAN0 MCR ECR ESR1:\n"
x/1wx 0x40024000
x/1wx 0x4002401c
x/1wx 0x40024020
monitor go
disconnect
quit
