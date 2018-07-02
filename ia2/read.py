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

min_tam = 2

refs = ['references', 'eferences']

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

    print sorted_top

    for t in sorted_top:
        print t[0] + ": " + str(t[1])

    print references
