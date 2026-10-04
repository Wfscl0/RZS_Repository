// Remove the two USART routes that crossed unrelated STM32 connector pins,
// then redraw them through the free corridor below the module sockets.
const old = await eda.sch_PrimitiveWire.get([
  "268eaf84bd6b78cb",
  "b0e7365b78e63d78"
]);
if (old.length) await eda.sch_PrimitiveWire.delete(old);

const tx = await eda.sch_PrimitiveWire.create(
  [495,560, 510,560, 510,525, 690,525, 690,640, 760,640],
  "UART_MCU_TX"
);
const rx = await eda.sch_PrimitiveWire.create(
  [575,570, 565,570, 565,515, 680,515, 680,680, 760,680],
  "UART_MCU_RX"
);

return {
  deleted: old.length,
  created: [tx.getState_PrimitiveId(), rx.getState_PrimitiveId()]
};
