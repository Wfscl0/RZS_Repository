# RES

RES 遥控急停系统的硬件工程、STM32 固件和设计资料统一放在本目录。
当前功能定义以仓库中的
`规则/2026中国大学生方程式系列赛事规则（最终版）.pdf`
为准，`Documentation/Legacy` 内资料仅用于历史对照。

## 快速入口

- STM32 工程：`Firmware/RES_Controller_F103`
- 可烧录固件：`Firmware/RES_Controller_F103/output/RES_Controller_F103C8T6.bin`
- 接口汇总：`Documentation/RES_Controller_接口汇总.md`
- 嘉立创 EDA 主工程：`Hardware/JLCEDA/RES_Controler.eprj2`
- 遥控端拓扑网表：`Hardware/Netlists/RES_Controller.NET`

## 目录结构

```text
RES/
├─ Documentation/
│  ├─ RES_Controller_接口汇总.md
│  ├─ Legacy/                 # 旧说明书，不作为当前功能定义
│  └─ Renders/                # PDF/原理图页面渲染图
├─ Firmware/
│  └─ RES_Controller_F103/    # STM32F103C8T6 PlatformIO 工程
└─ Hardware/
   ├─ JLCEDA/                 # EDA 工程及自动备份
   └─ Netlists/               # 拓扑和详细网表导出
```

`RES_Controler` 是原 EDA 工程历史名称，虽然拼写少了一个 `l`，但为保持
工程与自动备份目录兼容而不做改名。

