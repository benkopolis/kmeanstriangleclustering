#!/usr/bin/python3.4

from enum import Enum
from nltk.corpus import stopwords, wordnet
from nltk.stem.wordnet import WordNetLemmatizer
from nltk.tag import pos_tag
from nltk.tokenize import sent_tokenize, word_tokenize
from stemming.porter2 import stem

import sys
import re

def get_wordnet_pos(treebank_tag):
    if treebank_tag.startswith('J'):
        return wordnet.ADJ
    elif treebank_tag.startswith('V'):
        return wordnet.VERB
    elif treebank_tag.startswith('N'):
        return wordnet.NOUN
    elif treebank_tag.startswith('R'):
        return wordnet.ADV
    else:
        return ''

class ProcessStatus(Enum):
    Initial = 0
    Abstract = 1
    Keywords = 2
    Content = 3
    PageOnContent = 4
    End = 5
    Jel = 6

P_PAGE = r"^[0-9]{1,5}$"
P_ABSTRACT = r"^Abstract$"
P_KEYWORDS = r"^Keywords\:\s"
P_JEL = r"JEL\sclassification\:\s"
JEL_LEN = 19
JEL_SEP = ','
KW_LEN = 9
KW_SEP = ','
P_CHAPTER = r"^[1-9][0-9]{0,3}\.\s\w+(\s\w*)*$"
P_BIBLIO = r"Bibliography\son\s"
P_TITLE = r"^[A-Z]+\s([A-Z]+\s*)*$"

class DocumentProcessor:
    def __init__(self, dirpath, fileName):
        self.dName = dirpath
        self.fName = "{}/{}".format(self.dName, fileName)
        self.file_id = fileName[:4]
        self.fNamePattern = fileName[:-4]
        self.preProcessedFName = \
            "{}/{}{}".format(self.dName, self.fNamePattern, '.ctn')
        self.abstractFName = \
            "{}/{}{}".format(self.dName, self.fNamePattern, '.abs')
        self.kwFName = \
            "{}/{}{}".format(self.dName, self.fNamePattern, '.key')
        self.jelFName = \
            "{}/{}{}".format(self.dName, self.fNamePattern, '.jel')
        self.abstr_out = None
        self.kw_out = None
        self.jel_out = None
        self.pre_out = None
        self.title = ''
        self.biblio_title = None
        self.biblio_id = None
        self.page = False
        self.status = ProcessStatus.Initial
    
    def __store_abstract(self, aline):
        if not self.abstr_out:
            self.abstr_out = open(self.abstractFName, 'w')
        if not re.match(P_JEL, aline):
            self.abstr_out.write(aline)
            return True
        else:
            self.abstr_out.close()
            return False
    
    def __store_kw(self, aline):
        if not self.kw_out:
            self.kw_out = open(self.kwFName, 'w')
            if not len(aline) == 1:
                if re.match(P_KEYWORDS, aline):
                    aline = aline[KW_LEN:]
                splitted = aline.split(KW_SEP)
                for word in splitted:
                    self.kw_out.write(word.strip())
                    self.kw_out.write('\n')
                return True
            else:
                self.kw_out.close()
                return False
    
    def __store_jel(self, aline):
        if not self.jel_out:
            self.jel_out = open(self.jelFName, 'w')
            if not re.match(P_KEYWORDS, aline):
                if re.match(P_JEL, aline):
                    aline = aline[JEL_LEN:]
                splitted = aline.split(JEL_SEP)
                for word in splitted:
                    self.jel_out.write(word.strip())
                    self.jel_out.write('\n')
                return True
            else:
                self.jel_out.close()
                return False
                
    def __store_content(self, aline):
        if not self.pre_out:
            self.pre_out = open(self.preProcessedFName, 'w')
        if re.search(P_BIBLIO, aline) and \
            re.search(self.biblio_title, aline) and \
            re.search(self.biblio_id, aline):
            print("\t\tBiblio!!\n")
            self.pre_out.close()
            return False
        tmpLine = aline.strip()
        if len(tmpLine) < 5:
            if tmpLine == self.file_id:
                if self.status == ProcessStatus.Content:
                    self.status = ProcessStatus.PageOnContent
                    print("\t\tstarted page\n")
                else:
                    print("\t\tended page\n")
                    self.status = ProcessStatus.Content
                return True
            if re.search(P_PAGE, aline):
                if self.status == ProcessStatus.Content:
                    print("\t\tstarted page\n")
                    self.status = ProcessStatus.PageOnContent
                else:
                    print("\t\tended page\n")
                    self.status = ProcessStatus.Content
                return True
            if self.status == ProcessStatus.PageOnContent:
                print("\t\tstumbled upon a title on page\n")
                print(aline)
                return True
        if re.search(P_CHAPTER, aline):
            self.pre_out.write("{}.\n".format(aline.strip()))
        else:
            self.pre_out.write(aline)
        return True
    
    def __set_biblio_tags(self):
        self.biblio_title = re.compile(self.title)
        self.biblio_id = "\\({}\\)".format(self.file_id)
    
    def pre_process_file(self):
        """ Produces content file, abstract file,
        keywords file and jel classification file.
        """
        print("PREPROCESSING: '{}'\n".format(self.fName))
        patternTitle = ''
        tmpLine = ''
        lineCounter = 0
        result = False
        with open(self.fName, 'r') as fstep_file:
            for line in fstep_file:
                if self.status == ProcessStatus.Initial:
                    if lineCounter == 0 and line.strip() != self.file_id:
                        raise Exception('No id at first line')
                    if re.match(P_TITLE, line) and lineCounter < 10:
                        if len(self.title) > 1:
                            self.title = \
                                "{} {}".format(self.title, line.strip())
                        else:
                            self.title = line.strip()
                    if re.match(P_ABSTRACT, line):
                        self.status = ProcessStatus.Abstract
                        self.__set_biblio_tags()
                        continue
                if self.status == ProcessStatus.Abstract:
                    result = self.__store_abstract(line)
                    if not result:
                        self.status = ProcessStatus.Jel
                        self.__store_jel(line)
                    continue
                if self.status == ProcessStatus.Jel:
                    result = self.__store_jel(line)
                    if not result:
                        self.status = ProcessStatus.Keywords
                        self.__store_kw(line)
                    continue
                if self.status == ProcessStatus.Keywords:
                    result = self.__store_kw(line)
                    if not result:
                        self.status = ProcessStatus.Content
                        continue
                if self.status == ProcessStatus.Content or \
                    self.status == ProcessStatus.PageOnContent:
                    result = self.__store_content(line)
                    if not result:
                        print("\t Leaving early\n")
                        break
                lineCounter = lineCounter + 1
        print("Done preprocessing of {} lines".format(lineCounter))
    
    def __tokenize_single(self, fileInName):
        with open(fileInName, 'r') as ctn_in:
            data = ctn_in.read()
            lmtzr = WordNetLemmatizer()
            token_res = open(fileInName + '.tkn', 'w')
            lem_res = open(fileInName + '.lem', 'w')
            ilem_res = open(fileInName + '.ilem', 'w')
            stem_res = open(fileInName + '.stem', 'w')
            sentences = sent_tokenize(data)
            ignoreTypes = ['TO', 'CD', '.', 'LS', '']
            for sentence in sentences:
                words = word_tokenize(sentence)
                tags = pos_tag(words)
                for (word, type) in tags:
                    if type in ignoreTypes:
                        ilem_res.write(word + ' ')
                        continue
                    if word in stopwords.words('english'):
                        continue
                    tag = get_wordnet_pos(type)
                    if tag == '':
                        ilem_res.write(word + ' ')
                        continue
                    lema = lmtzr.lemmatize(word, tag)
                    lem_res.write(lema + ' ')
                    stemW = stem(lema)
                    stem_res.write(stemW + ' ')
                lem_res.write('\n')
                stem_res.write('\n')
                ilem_res.write('\n')
            token_res.write('\n\n'.join(sentences))
            token_res.close()
            lem_res.close()
            stem_res.close()
            ilem_res.close()
    
    def tokenize_files(self):
        """ Gets abstract and content files and performes tokenization.
        """
        self.__tokenize_single(self.preProcessedFName)
        self.__tokenize_single(self.abstractFName)


def main(argv):
    inputDir = '/home/zby/MAGISTERKA/law/civil and criminal procedure'
    inputFile = '7000book.txt'
    if len(argv) == 2:
        inputDir = argv[0]
        inputFile = argv[1]
    dProc = DocumentProcessor(inputDir, inputFile)
    dProc.pre_process_file()
    dProc.tokenize_files()

if __name__ == "__main__":
    main(sys.argv[1:])
