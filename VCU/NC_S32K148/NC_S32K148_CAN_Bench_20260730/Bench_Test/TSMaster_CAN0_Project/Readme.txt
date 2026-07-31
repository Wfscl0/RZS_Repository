VCU CAN0单总线台架测试工程

1. 烧录NC_S32K148_CAN_Bench_20260730测试固件。
2. TSMaster适配器连接VCU CAN0，500 kbit/s，Classical CAN。
3. 断开逆变器CAN支路和高压，或确保逆变器可靠禁能。
4. 打开本目录中的.TSProj。所有数据库和发送窗口报文均已调整到逻辑CAN0。
5. 先周期发送0x7A0～0x7A3，确认0x7B0的四个Active位均为1。

注意：0x7A0首字节必须保持A5，不要改为42，否则会满足原Bootloader跳转识别条件。
