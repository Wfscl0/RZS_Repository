from pathlib import Path
from copy import copy
from openpyxl import load_workbook
from openpyxl.styles import Alignment
from math import ceil
R=Path(r'D:\git\RZS_Repository');P=Path(__file__).parent/'build_material.py';s=P.read_text(encoding='utf8')
s=s.replace("rows.append((c[0]+'.'+c[1],signal,electrical,beh))", "electrical=electrical if len(electrical)<=38 else electrical[:36]+'…'\n  beh=beh if len(beh)<=54 else beh[:52]+'…'\n  rows.append((c[0]+'.'+c[1],signal,electrical,beh))")
# 只在主文摘要压缩长度，完整电气定义仍在逐针索引。
s=s.replace("styles['Normal'].paragraph_format.line_spacing=1.16", "styles['Normal'].paragraph_format.line_spacing=1.16\nfor st in styles:\n for border in st._element.xpath('.//w:pBdr'):\n  border.getparent().remove(border)")
s=s.replace("sec.header_distance=Cm(.7);sec.footer_distance=Cm(.7)", "sec.header_distance=Cm(.7);sec.footer_distance=Cm(.7)\nsec.top_margin=Cm(1.55);sec.bottom_margin=Cm(1.45)")
# 索引排除接收端软件约束与旧整车报文；仅列RES自身CAN数据字段。
old="next(r['text'] for r in sources if r['path']=='RES/firmware/docs/RES_SYSTEM_DESCRIPTION_CN.md')"
new="next(r['text'] for r in sources if r['path']=='RES/firmware/docs/RES_SYSTEM_DESCRIPTION_CN.md').split('## 8 CAN 报文',1)[0]"
s=s.replace(old,new)
s=s.replace("'## RES CAN DBC 完整字段','','```dbc',next(r['text'] for r in sources if r['path'].endswith('.dbc')),'```'", "'## RES CAN 输出字段','','本节仅保留RES自身的字段定义，不包含外部控制器集成。','','```text','\\n'.join(line.split(' VCU')[0] for line in next(r['text'] for r in sources if r['path'].endswith('.dbc')).splitlines() if line.startswith('BO_ ') or line.startswith(' SG_ ')),'```'")
# 断言不再把来源修订情况写成未修改。
P.write_text(s,encoding='utf8')
for file in ['低压盒/硬件电路接口.xlsx','基板/基板全部接口特性与定义_2026-07-31_v7.xlsx']:
 p=R/file;w=load_workbook(p)
 for sheet in w:
  for row in sheet:
   maxlines=1
   for c in row:
    if c.value is None:continue
    align=copy(c.alignment);align.wrap_text=True;align.vertical='center';c.alignment=align
    width=sheet.column_dimensions[c.column_letter].width or 10
    for merge in sheet.merged_cells.ranges:
     if c.coordinate in merge and c.row==merge.min_row and c.column==merge.min_col:
      if merge.max_row!=merge.min_row:break
      width=sum(sheet.column_dimensions[__import__('openpyxl').utils.get_column_letter(i)].width or 10 for i in range(merge.min_col,merge.max_col+1));break
    weighted=lambda text:sum(2 if ord(ch)>255 else 1 for ch in text)
    lines=sum(max(1,ceil(weighted(line)/max(8,width-2))) for line in str(c.value).split('\n'))
    maxlines=max(maxlines,lines)
   if row[0].row>=4:
    # 表格保留原行高，下限根据文本长度估算，避免合并单元格不自动适应。
    sheet.row_dimensions[row[0].row].height=min(320,max(sheet.row_dimensions[row[0].row].height or 16,maxlines*12+10))
 # 新增校核行沿用上一条有效样式。
 target=w['校核清单'] if '校核清单' in w.sheetnames else w['待确认与测试']
 for row in target:
  for c in row:
   if c.has_style:continue
   template=target.cell(5,c.column)
   c._style=copy(template._style)
 w.save(p)
print('Polished pagination, title borders, scope and spreadsheet row wrapping')
