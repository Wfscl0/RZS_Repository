# VCU TSMaster / PCAN台架测试副本

本目录对应的工程只用于低压台架测试。`ImpCode/interface/CAN_Node.h`中的
`VCU_ENABLE_BENCH_DEBUG`和`VCU_BENCH_SINGLE_CAN0`均已设为1；生产本体中的
台架调试开关仍为0。

## 安全边界

- PCAN或TSMaster只连接VCU的CAN0，500 kbit/s，Classical CAN。
- CAN0上同时存在11位标准测试报文和29位电机扩展帧。首轮测试必须断开逆变器CAN支路或可靠禁能逆变器，并断开高压。
- 保留机械急停和独立低压断电手段。
- 调试覆盖报文停止500 ms后会自动退回真实硬件输入，但不能把该超时作为唯一安全措施。

## TSMaster

可以直接打开`TSMaster_CAN0_Project/.TSProj`。该工程已缩减为一个逻辑CAN通道，数据库及发送窗口内的全部报文均绑定到CAN0。

如需手动建立工程，在TSMaster的CAN0通道加载`../DBC/VCU_TSMaster_Debug.dbc`，同时显示标准帧和扩展帧，周期发送：

- `0x7A0`：`A5 5A 0F 00 00 00 00 00`
- `0x7A1`：踏板/制动输入，100 ms
- `0x7A2`：两路气压，100 ms
- `0x7A3`：HIN输入，100 ms

确认`0x7B0`四个Active位均为1，再进行状态机测试。最新输出位定义为：

- LOX bit0～4：制动灯、ASSI蓝、ASSI黄、EBS错误灯、RES错误。
- HOX bit0～6：EBS触发、BMS灯、IMD灯、DI8、RUN、R2D蜂鸣器、Emergency蜂鸣器。

`0x7A0`同时是原Bootloader监听ID，但Bootloader仅在Byte0=`0x42`时触发；调试控制帧Byte0固定为`0xA5`，不会触发跳转。不要手工把`0x7A0`首字节改成`0x42`。

## PCAN Python测试

安装PEAK PCAN驱动和PCAN-Basic后，在本目录运行：

```powershell
py -m pip install -r requirements.txt
py pcan_vcu_bench.py --scenario override
py pcan_vcu_bench.py --scenario pedal-timeout
py pcan_vcu_bench.py --scenario brake-open
```

当前脚本依赖`python-can`和`cantools`，已固定在`requirements.txt`中。三个场景分别验证调试覆盖建立、踏板组单独超时回退和制动传感器断路故障；每个场景结束会输出`PASS`或`FAIL`。

如果适配器不是第一个USB通道，增加例如`--channel PCAN_USBBUS2`。

脚本同时模拟ESP、RES、IPC、AMI和EPS的基础周期报文，监听VCU回显并自动给出PASS/FAIL。退出时会主动关闭覆盖；VCU自身仍保留500 ms超时回退。
