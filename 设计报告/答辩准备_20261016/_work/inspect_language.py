from zipfile import ZipFile
from lxml import etree as E
P='设计报告/答辩准备_20261016/RZS整车电气系统答辩准备材料.docx'
z=ZipFile(P)
ns={'w':'http://schemas.openxmlformats.org/wordprocessingml/2006/main','a':'http://schemas.openxmlformats.org/drawingml/2006/main'}
s=E.fromstring(z.read('word/styles.xml'));d=E.fromstring(z.read('word/document.xml'))
used=set(d.xpath('//w:pStyle/@w:val',namespaces=ns));used.add('Normal')
for x in s.xpath('//w:style',namespaces=ns):
 if x.get('{'+ns['w']+'}styleId') in used:
  print(x.get('{'+ns['w']+'}styleId'),[dict(n.attrib) for n in x.xpath('./w:rPr/w:rFonts | ./w:rPr/w:lang',namespaces=ns)])
t=E.fromstring(z.read('word/theme/theme1.xml'))
print('theme fonts',[(x.tag.split('}')[-1],dict(x.attrib)) for x in t.xpath('//a:fontScheme//a:ea | //a:fontScheme//a:font',namespaces=ns) if x.tag.endswith('ea') or x.get('script') in ['Hans','Jpan']])
body=d.find('w:body',ns)
for i,el in enumerate(body):
 if el.tag.endswith('p') and el.xpath('./w:pPr/w:pStyle[@w:val="Heading1"]',namespaces=ns):
  print('HEADING',i,''.join(el.xpath('.//w:t/text()',namespaces=ns)),'prev',E.tostring(body[i-1]).decode()[-180:])
