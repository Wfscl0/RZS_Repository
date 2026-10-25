from pathlib import Path
from zipfile import ZipFile
from shutil import copy2
from lxml import etree as E
from collections import Counter
from docx import Document
import re,json

root=Path(r'D:\git\RZS_Repository\设计报告\答辩准备_20261016')
path=root/'RZS整车电气系统答辩准备材料.docx'
work=root/'_work/中文字体与接口顺序校订';work.mkdir(exist_ok=True)
backup=work/'修改前.docx'
assert not backup.exists(),'Backup exists; do not overwrite the reviewed input'
copy2(path,backup)
ns={'w':'http://schemas.openxmlformats.org/wordprocessingml/2006/main','a':'http://schemas.openxmlformats.org/drawingml/2006/main'}
w='{'+ns['w']+'}'
with ZipFile(path) as z:
 infos=z.infolist();data={i.filename:z.read(i.filename) for i in infos}
doc=E.fromstring(data['word/document.xml']);body=doc.find('w:body',ns)
before_text=doc.xpath('//w:t/text()',namespaces=ns)
styles=E.fromstring(data['word/styles.xml'])
heading_ids={s.get(w+'styleId') for s in styles.findall('w:style',ns) if s.find('w:name',ns) is not None and s.find('w:name',ns).get(w+'val','').lower()=='heading 1'}
def heading(el):return el.tag==w+'p' and any(x.get(w+'val') in heading_ids for x in el.xpath('./w:pPr/w:pStyle',namespaces=ns))
def text(el):return ''.join(el.xpath('.//w:t/text()',namespaces=ns))
children=list(body)
heads=[(i,e,text(e)) for i,e in enumerate(children) if heading(e)]
start=next(i for i,e,t in heads if '基板外部接口 CN7' in t)-1
stop=next(i for i,e,t in heads if 'BSPD 制动与驱动冲突检测' in t)-1
assert children[start].xpath('.//w:br[@w:type="page"]',namespaces=ns)
blocks=children[start:stop]
assert len([e for e in blocks if heading(e)])==6
for el in blocks:body.remove(el)
sect=body.find('w:sectPr',ns)
assert sect is not None
for el in blocks:sect.addprevious(el)
renumber=[]
for n,el in enumerate([e for e in body if heading(e)],1):
 old=text(el);new=re.sub(r'^\d+\s+',str(n)+' ',old)
 if old!=new:
  nodes=el.xpath('.//w:t',namespaces=ns)
  # 只替换章节编号对应的文本，保留各run和原有格式。
  oldprefix=re.match(r'^\d+\s+',old).group()
  remaining=len(oldprefix)
  for node in nodes:
   val=node.text or ''
   if remaining:
    take=min(remaining,len(val));node.text=(str(n)+' ' if remaining==len(oldprefix) else '')+val[take:];remaining-=take
  assert text(el)==new
  renumber.append({'before':old,'after':new})

# 显式指定中文字体及中文语言，避免依赖日文主题回退。
for font in styles.xpath('//w:rFonts',namespaces=ns):
 current=font.get(w+'eastAsia')
 if not current or current in ['MS Mincho','MS Gothic','ＭＳ 明朝','ＭＳ ゴシック','Yu Mincho','Yu Gothic']:
  font.set(w+'eastAsia','宋体')
 font.attrib.pop(w+'eastAsiaTheme',None)
for lang in styles.xpath('//w:lang',namespaces=ns):lang.set(w+'eastAsia','zh-CN')
for lang in doc.xpath('//w:lang',namespaces=ns):lang.set(w+'eastAsia','zh-CN')
for font in doc.xpath('//w:rFonts',namespaces=ns):
 current=font.get(w+'eastAsia')
 if current in ['MS Mincho','MS Gothic','ＭＳ 明朝','ＭＳ ゴシック','Yu Mincho','Yu Gothic']:
  font.set(w+'eastAsia','宋体')
 font.attrib.pop(w+'eastAsiaTheme',None)
theme=E.fromstring(data['word/theme/theme1.xml'])
for node in theme.xpath('//a:fontScheme//a:ea | //a:fontScheme//a:font[@script="Jpan"] | //a:fontScheme//a:font[@script="Hans"]',namespaces=ns):node.set('typeface','宋体')
settings=E.fromstring(data['word/settings.xml'])
for node in settings.xpath('//w:themeFontLang',namespaces=ns):node.set(w+'eastAsia','zh-CN')
def xml(node):return E.tostring(node,encoding='UTF-8',xml_declaration=True,standalone=True)
data.update({'word/document.xml':xml(doc),'word/styles.xml':xml(styles),'word/theme/theme1.xml':xml(theme),'word/settings.xml':xml(settings)})
tmp=work/'revised.docx'
with ZipFile(tmp,'w') as z:
 for info in infos:z.writestr(info,data[info.filename])

# 按XML块核对正文、表格内容完全不变，只有标题数字和块顺序变化。
original=E.fromstring(ZipFile(backup).read('word/document.xml'))
normalize=lambda e:re.sub(r'^\d+\s+','',text(e)) if heading(e) else text(e)
old_blocks=Counter(normalize(e) for e in original.find('w:body',ns) if e.tag!=w+'sectPr')
new_blocks=Counter(normalize(e) for e in body if e.tag!=w+'sectPr')
assert old_blocks==new_blocks,'Unexpected content changes'
assert not re.search('[\u3040-\u30ff\uff66-\uff9f]',''.join(doc.xpath('//w:t/text()',namespaces=ns)))
assert [text(e).split(' ',1)[1] for e in body if heading(e)][-6:]==[t.split(' ',1)[1] for _,_,t in heads if '基板外部接口' in t or '基板板卡排针' in t]
tmp.replace(path)
report={'body_and_tables_preserved':True,'moved_interface_sections':6,'remaining_japanese_kana':0,'chinese_font':'宋体','chinese_language':'zh-CN','renumbered_headings':renumber}
(work/'校核记录.json').write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf8')
print(json.dumps(report,ensure_ascii=False,indent=2))
