from pathlib import Path
import pypdfium2 as pdfium
from PIL import Image,ImageDraw,ImageFont
import json
W=Path(__file__).parent; folder=W/'word_render';summary=[]
for path in folder.glob('*.pdf'):
 doc=pdfium.PdfDocument(path);out=folder/path.stem;out.mkdir(exist_ok=True);thumbs=[]
 for i in range(len(doc)):
  page=doc[i];im=page.render(scale=1.5).to_pil().convert('RGB');im.save(out/f'page-{i+1}.png')
  text=page.get_textpage().get_text_range()
  summary.append({'file':path.stem,'page':i+1,'chars':len(text),'tail':text[-120:]})
  thumb=im.copy();thumb.thumbnail((360,510)); canvas=Image.new('RGB',(380,540),'#d9dfe6');canvas.paste(thumb,((380-thumb.width)//2,20));ImageDraw.Draw(canvas).text((10,520),str(i+1),fill='black');thumbs.append(canvas)
 for i in range(0,len(thumbs),9):
  canvas=Image.new('RGB',(1140,1620),'#bbc6d1')
  for j,im in enumerate(thumbs[i:i+9]):canvas.paste(im,((j%3)*380,(j//3)*540))
  canvas.save(out/f'contact-{i//9+1}.png')
(W/'page_metrics.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2),encoding='utf8')
print(json.dumps([r for r in summary if r['chars']<120],ensure_ascii=False))
