#import PyPDF2
import textract
import nltk
import re
import string
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
    text = textract.process(filename).decode("utf-8")
    #print text

    ref_pos = text.find('REFERENCES')
    if ref_pos == -1:
        ref_pos = text.find('EFERENCES')

    if ref_pos != -1:
        ref_text = text[ref_pos-1:]

    pattern = re.compile('[\W_]+', re.UNICODE)

    text = re.sub(r'\W+', ' ', text)

    #pdfFileObj = open(filename, 'rb')

    #pdfReader = PyPDF2.PdfFileReader(pdfFileObj)

    #num_pages = pdfReader.numPages
    #print "Numpages: " + str(num_pages)

    #count = 0
    #title = ''
    #while count < num_pages:
    #    pageObj = pdfReader.getPage(count)
    #    count +=1
    #    title = pageObj.extractText()
    #    if count == 2:
    #        break
    #print title

    tokens = word_tokenize(text)

    #print tokens
    punctuations = ['(',')',';',':','[',']',',', '.', '{', '}', '!', '@', '#', '$', '%', '"', '>', '<', '+', '=',
                    '?', '/']

    stop_words = set(stopwords.words('english'))

    keywords = []
    for word in tokens:
        word = word.lower()

        if (not (word in stop_words)) and (not word in punctuations):
            keywords.append(word)

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

    #print sorted_top

    outf = open(out_files[i],"w+")

    outf.write("10 termos mais citados:\n")
    for t in sorted_top:
        outf.write(t[0] + ": " + str(t[1]) + "\n")

    outf.write(";;\n")

    outf.write(ref_text.encode('utf-8'))

    outf.write("\n;;\n")

    outf.close()

    i = i + 1
