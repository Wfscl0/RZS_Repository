# STM32 侧兼容性实机测试

## 结果

未改 PCB、未烧录 STM8，仅在遥控 STM32 临时运行现有 RES_RADIO_STOP_BENCH 配置：强制 STOP、2 秒周期、不发送 READY/GO。车载固件保持原样。

本次确认 SN20090928 为遥控 role1，SN69400240 为车载 role2。测试前遥控只收到 58 字节 LoRa 启动文本、ACK=0，车载收到数据并回复。

测试开始 20 秒：TX=10、RX=477、decoded=9、accepted ACK=9、unmatched=0，UART 错误/溢出/发送失败均为 0。该快照最后发送时间 0x467B、最后接收时间 0x4AF9，时间差 1150ms；这是单个快照样本，不是完整时延分布。后续 8 秒窗口 TX25→29、ACK22→26，证明反向链路能持续返回认证有效回复。不能将 26/29 直接当成稳态丢包率，包含初始化和在途帧。

## 判断与限制

降低发包频率后双向通信恢复，强烈支持现有桥接固件吞吐/收发调度与正常发包节奏不匹配。不能仅凭该测试精确区分 RF 空中时间、STM8 阻塞或缓存所占比例。也不能证明所有电气连接均无隐患。

约 1.15 秒回复样本不满足正常版 260ms ACK 窗口和 500ms 失联约束。诊断配置的 ACK 等待为 1800ms，但强制 STOP 且失联阈值仍为 500ms，不是合格运行模式。不得将 2 秒周期移植为车辆运行配置。

核对厂商原始 IT_Timer_UartCheck：正常空闲分帧为大于10 timer ticks，500 ticks是后备处理；此前“固定等待500ms”表述不准确，已修正遥控源码注释。

## 收尾

测试前备份完整128KiB Flash：tmp/remote_pre_stock_probe_flash.bin。测试后已恢复该镜像，J-Link verifybin 全量校验成功并恢复运行。车载未烧录，STM8未烧录。未留下低频测试程序。

日志：tmp/stock_probe_flash.log、tmp/stock_probe_restore.log。诊断固件位于 artifacts/stock_bridge_probe_20260915/remote/gcc，仅供STOP台架排障。

正式解决路径仍需降低桥接端延迟并重新实测。已编译的STM8桥接固件是一条候选路径，需要SWIM部署两块板并验证，不保证仅烧录即可通过ASF。当前遥控STOP输入及电量无效故障仍须独立处理，不得旁路。
