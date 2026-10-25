from pathlib import Path
import pypdfium2 as pdfium
from pypdf import PdfReader
from PIL import Image,ImageDraw
import json
w=Path(__file__).parent
p=pdfium.PdfDocument(w/'preview.pdf');thumbs=[];metrics=[]
for i in range(len(p)):
 page=p[i];im=page.render(scale=1.5).to_pil().convert('RGB');im.save(w/f'page-{i+1}.png')
 text=page.get_textpage().get_text_range();metrics.append({'page':i+1,'chars':len(text),'head':text[:140]})
 im.thumbnail((350,495));t=Image.new('RGB',(370,525),'#d8dfe6');t.paste(im,(10,10));ImageDraw.Draw(t).text((12,507),str(i+1),fill='black');thumbs.append(t)
for i in range(0,len(thumbs),8):
 c=Image.new('RGB',(1480,1050),'#c0cbd5')
 for j,t in enumerate(thumbs[i:i+8]):c.paste(t,((j%4)*370,(j//4)*525))
 c.save(w/f'contact-{i//8+1}.png')
r=PdfReader(w/'preview.pdf');fonts=set()
for page in r.pages:
 for font in page['/Resources'].get('/Font',{}).values():
  fonts.add(str(font.get_object().get('/BaseFont','')))
assert not any(any(s in f.lower() for s in ['mincho','gothic','meiryo','yumin']) for f in fonts),fonts
assert all(x['chars']>100 for x in metrics),[x for x in metrics if x['chars']<=100]
(w/'render_check.json').write_text(json.dumps({'pages':len(p),'fonts':sorted(fonts),'pages_info':metrics},ensure_ascii=False,indent=2),encoding='utf8')
print(json.dumps({'pages':len(p),'fonts':sorted(fonts),'last_pages':[x for x in metrics if x['page']>=len(p)-5]},ensure_ascii=False,indent=2))
