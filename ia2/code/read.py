import textract
import nltk
import re
from nltk.tokenize import word_tokenize
from nltk.corpus import stopwords

files = ['./pdfs/13.pdf', './pdfs/17.pdf', './pdfs/19.pdf', './pdfs/20.pdf',
         './pdfs/21.pdf', './pdfs/22.pdf', './pdfs/23.pdf', './pdfs/29.pdf',
         './pdfs/31.pdf', './pdfs/46.pdf', './pdfs/48.pdf', './pdfs/49.pdf',
         './pdfs/50.pdf', './pdfs/98.pdf', './pdfs/118.pdf', './pdfs/120.pdf']

out_files = ['./out/13.txt', './out/17.txt', './out/19.txt', './out/20.txt',
         './out/21.txt', './out/22.txt', './out/23.txt', './out/29.txt',
         './out/31.txt', './out/46.txt', './out/48.txt', './out/49.txt',
         './out/50.txt', './out/98.txt', './out/118.txt', './out/120.txt']

min_tam = 2

refs = ['references', 'eferences']

i = 0
for filename in files:
    #Le o texto do PDF e armazena em uma unica string
    text = textract.process(filename).decode("utf-8")

    #Leitura da intituicao
    inst_start = text.find('IEEE')
    inst_end = text.find(',')
    inst = text[inst_start:inst_end]

    #Leitura dos autores
    abs_start = text.find("Abstract")
    lines = text[:abs_start].split("\n")

    j = len(lines) - 1
    while lines[j] == '':
        del lines[j]
        j = j - 1

    autores = ''
    autores = lines[-1].encode("UTF-8")
    if lines[-2][-1] == ',':
        autores = autores + "\n" + lines[-2].encode("UTF-8")

    #Leitura das referencias
    ref_pos = text.find('REFERENCES')
    if ref_pos == -1:
        ref_pos = text.find('EFERENCES')

    if ref_pos != -1:
        ref_text = text[ref_pos-1:]

    #Pre-processamento
    pattern = re.compile('[\W_]+', re.UNICODE)

    text = re.sub(r'\W+', ' ', text)

    tokens = word_tokenize(text)

    punctuations = ['(',')',';',':','[',']',',', '.', '{', '}', '!', '@', '#', '$', '%', '"', '>', '<', '+', '=',
                    '?', '/']

    stop_words = set(stopwords.words('english'))

    keywords = []
    for word in tokens:
        word = word.lower()

        if (not (word in stop_words)) and (not word in punctuations):
            keywords.append(word)

    #Procura das top 10 palavras
    top_words = {}
    for word in keywords:
        word = word.lower()

        if (not word.isdigit()) and (len(word) > min_tam):
            if word in refs:
                break
            else:
                if word not in top_words.keys():
                    top_words[word] = 1
                else:
                    top_words[word] += 1

    sorted_top = sorted(top_words.items(), key=lambda x: x[1])
    sorted_top = sorted_top[-10:]

    #Escrita no arquivo
    outf = open(out_files[i],"w+")

    for t in sorted_top:
        outf.write(t[0] + ": " + str(t[1]) + "\n")
    outf.write(";;\n")

    outf.write(ref_text.encode('utf-8'))
    outf.write("\n;;\n")

    outf.write(inst)
    outf.write("\n;;\n")

    outf.write(autores)
    outf.write("\n;;\n")

    outf.close()

    i = i + 1
