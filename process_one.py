#!/usr/bin/python3.4

from enum import Enum
from nltk.corpus import stopwords, wordnet
from nltk.stem.wordnet import WordNetLemmatizer
from nltk.tag import pos_tag
from nltk.tokenize import sent_tokenize, word_tokenize
from stemming.porter2 import stem

import sys
import re

class NoFileIdError(Exception):
    """ Class that represents and error where there is no id"""
    
    def __init__(self, msg):
        self.message = msg

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
P_JEL = r"JEL\s(classification[s]{0,1}|categories|category)\:\s"
JEL_LEN = 19
JEL_SEP = ','
KW_LEN = 9
KW_SEP = ','
P_CHAPTER = r"^[1-9][0-9]{0,3}\.\s\w+(\s\w*)*$"
P_BIBLIO = r"Bibliography\son\s"
P_TITLE = r"^[A-Z]+\s([A-Z]+\s*)*$"

def log_debug(log):
    if False:
        print(log + '\n')

def try_open(fname, rw):
    try:
        return open(fname, rw)
    except FileNotFoundError:
        print("\n-------------\n")
        print("Cannot open '{}' as '{}'".format(fname, rw))
        print("\n-------------\n")
        raise

class DocumentProcessor:
    def __init__(self, dirpath, fileName):
        self.dName = dirpath
        self.fName = "{}/{}".format(self.dName, fileName)
        self.file_id = fileName[:4]
        self.fNamePattern = fileName[:-4]
        self.preProcessedFName = \
            "{}/{}{}".format(self.dName, self.fNamePattern, '.ctn')
        self.preProcOpened = False
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
            self.abstr_out = try_open(self.abstractFName, 'w')
        if not re.match(P_JEL, aline, re.IGNORECASE):
            log_debug("Line: '{}' did not match JEL".format(aline))
            self.abstr_out.write(aline)
            return True
        else:
            log_debug("Matching JEL")
            self.abstr_out.close()
            return False
    
    def __store_kw(self, aline):
        if not self.kw_out:
            self.kw_out = try_open(self.kwFName, 'w')
        if not len(aline) < 2:
            if re.match(P_KEYWORDS, aline, re.IGNORECASE):
                aline = aline[KW_LEN:]
            splitted = aline.split(KW_SEP)
            for word in splitted:
                self.kw_out.write(word.strip())
                self.kw_out.write(' ')
            return True
        else:
            self.kw_out.close()
            log_debug("End of KeyWords")
            return False
    
    def __store_jel(self, aline):
        if not self.jel_out:
            self.jel_out = try_open(self.jelFName, 'w')
        if not re.match(P_KEYWORDS, aline, re.IGNORECASE):
            if re.match(P_JEL, aline):
                aline = aline[JEL_LEN:]
            splitted = aline.split(JEL_SEP)
            for word in splitted:
                self.jel_out.write(word.strip())
                self.jel_out.write(' ')
            return True
        else:
            self.jel_out.close()
            return False
                
    def __store_content(self, aline):
        if not self.pre_out:
            self.pre_out = try_open(self.preProcessedFName, 'w')
            self.preProcOpened = True
            log_debug("Opened preout")
        if re.search(P_BIBLIO, aline) and \
            re.search(self.biblio_title, aline) and \
            re.search(self.biblio_id, aline):
            self.pre_out.close()
            self.preProcOpened = False
            log_debug("Encountered biblio - closing")
            return False
        tmpLine = aline.strip()
        if len(tmpLine) < 5:
            if tmpLine == self.file_id:
                if self.status == ProcessStatus.Content:
                    self.status = ProcessStatus.PageOnContent
                else:
                    self.status = ProcessStatus.Content
                return True
            if re.search(P_PAGE, aline):
                if self.status == ProcessStatus.Content:
                    self.status = ProcessStatus.PageOnContent
                else:
                    self.status = ProcessStatus.Content
                return True
            if self.status == ProcessStatus.PageOnContent:
                return True
        if re.search(P_CHAPTER, aline):
            self.pre_out.write("{}.\n".format(aline.strip()))
        else:
            self.pre_out.write(aline)
        return True
    
    def __set_biblio_tags(self):
        log_debug("Setting biblio tags")
        self.biblio_title = re.compile(self.title)
        self.biblio_id = "\\({}\\)".format(self.file_id)
        log_debug("Done setting biblio tags")
    
    def pre_process_file(self):
        """ Produces content file, abstract file,
        keywords file and jel classification file.
        """
        patternTitle = ''
        tmpLine = ''
        lineCounter = 0
        result = False
        with try_open(self.fName, 'r') as fstep_file:
            for line in fstep_file:
                if self.status == ProcessStatus.Initial:
                    log_debug("ProcessingInitial line is: '{}'".format(line))
                    if lineCounter == 0 and line.strip() != self.file_id:
                        raise NoFileIdError('No id at first line')
                    elif re.match(P_TITLE, line) and lineCounter < 10:
                        if len(self.title) > 1:
                            self.title = \
                                "{} {}".format(self.title, line.strip())
                        else:
                            self.title = line.strip()
                    elif re.match(P_ABSTRACT, line):
                        log_debug("Matching abstract")
                        self.status = ProcessStatus.Abstract
                        self.__set_biblio_tags()
                elif self.status == ProcessStatus.Abstract:
                    log_debug("Processing Abstract line is: '{}'".format(line))
                    result = self.__store_abstract(line)
                    if not result:
                        self.status = ProcessStatus.Jel
                        self.__store_jel(line)
                elif self.status == ProcessStatus.Jel:
                    result = self.__store_jel(line)
                    if not result:
                        self.status = ProcessStatus.Keywords
                        self.__store_kw(line)
                elif self.status == ProcessStatus.Keywords:
                    result = self.__store_kw(line)
                    if not result:
                        self.status = ProcessStatus.Content
                elif self.status == ProcessStatus.Content or \
                    self.status == ProcessStatus.PageOnContent:
                    result = self.__store_content(line)
                    if not result:
                        print("\t Leaving early\n")
                        break
                log_debug("Status: '{}'".format(self.status))
                lineCounter = lineCounter + 1
        if self.preProcOpened:
            self.preProcOpened = False
            self.pre_out.close()
        print("Done preprocessing of {} lines".format(lineCounter))
    
    def __tokenize_single(self, fileInName):
        with try_open(fileInName, 'r') as ctn_in:
            data = ctn_in.read()
            lmtzr = WordNetLemmatizer()
            token_res = try_open(fileInName + '.tkn', 'w')
            lem_res = try_open(fileInName + '.lem', 'w')
            ilem_res = try_open(fileInName + '.ilem', 'w')
            stem_res = try_open(fileInName + '.stem', 'w')
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
                lem_res.write(' ')
                stem_res.write(' ')
                ilem_res.write(' ')
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
    #/home/zby/MAGISTERKA/law/tort law and unjust enrichment/3800book.ctn
    inputDir = '/home/zby/MAGISTERKA/law/regulation of contracts'
    inputFile = '5550book.txt'
    log_debug("Test")
    if len(argv) == 2:
        inputDir = argv[0]
        inputFile = argv[1]
    dProc = DocumentProcessor(inputDir, inputFile)
    dProc.pre_process_file()
    #dProc.tokenize_files()

if __name__ == "__main__":
    main(sys.argv[1:])
