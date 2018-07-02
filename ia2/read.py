import PyPDF2
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

    pattern = re.compile('[\W_]+', re.UNICODE)

    text = re.sub(r'\W+', ' ', text)

    #write a for-loop to open many files -- leave a comment if you'd #like to learn how
    #open allows you to read the file
    pdfFileObj = open(filename, 'rb')
    #The pdfReader variable is a readable object that will be parsed
    pdfReader = PyPDF2.PdfFileReader(pdfFileObj)
    #discerning the number of pages will allow us to parse through all #the pages
    num_pages = pdfReader.numPages
    print "Numpages: " + str(num_pages)

    #The word_tokenize() function will break our text phrases into #individual words
    tokens = word_tokenize(text)
    #print tokens
    #we'll create a new list which contains punctuation we wish to clean
    punctuations = ['(',')',';',':','[',']',',', '.', '{', '}', '!', '@', '#', '$', '%', '"', '>', '<', '+', '=',
                    '?', '/']

    #We initialize the stopwords variable which is a list of words like #"The", "I", "and", etc. that don't hold much value as keywords
    stop_words = set(stopwords.words('english'))

    #We create a list comprehension which only returns a list of words #that are NOT IN stop_words and NOT IN punctuations.

    keywords = []
    for word in tokens:
        word = word.lower()

        if (not (word in stop_words)) and (not word in punctuations):
            keywords.append(word)

    #keywords = [word for word in tokens if not word in stop_words and not word in punctuations]
    #print "KEYORDS"

    top_words = {}
    in_refs = False
    references = ''

    for word in keywords:
        word = word.lower()

        if in_refs:
            references += " " + word
        elif (not word.isdigit()) and (len(word) > min_tam):
            if word in refs:
                in_refs = True
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

    outf.write(references)

    outf.write("\n;;\n")

    outf.close()

    i = i + 1
