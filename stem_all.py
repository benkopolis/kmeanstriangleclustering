#!/usr/bin/python3.4
# shell command to find and check files generated
# find . -type f -name *.abs -exec ls -l {} \;
# merge per type
# find . -type f -name *.key -exec cat {} + >> keywords_merged
# merge all for mass tfidf
# find . -type f \( -name "*.key" -o -name "*.ctn" -o -name "*.abs" \) -exec cat {} + >> merged_all

from multiprocessing import Pool
from os import walk
from process_one import DocumentProcessor, NoFileIdError

import itertools
import time
import sys

def process(input):
    time.sleep(1)
    dProc = DocumentProcessor(input[0], input[1])
    try:
        dProc.pre_process_file()
    except NoFileIdError:
        print("\n-------------\n")
        print("No FileID " + input[1])
        print("\n-------------\n")
    try:
        dProc.tokenize_files()
    except FileNotFoundError:
        print("\n-------------\n")
        print("Error processing " + input[1])
        print("\n-------------\n")
    return dProc
    
def initProcessor(input):
    time.sleep(1)
    return DocumentProcessor(input[0], input[1])

def getFiles():
    dict = {}
    mypath = '/home/zby/MAGISTERKA/law'
    for (dirpath, dirnames, filenames) in walk(mypath):
        print("{} {} {}\n".format(dirpath, dirnames, filenames))
        for fname in filenames:
            if fname.endswith('.txt'):
                yield (dirpath, fname)


if __name__ == "__main__":
    p = Pool(4)
    toProc = getFiles()
    N = 11
    result = []
    while True:
        if len(sys.argv) > 1:
            res = p.map(initProcessor, itertools.islice(toProc, N))
        else:
            res = p.map(process, itertools.islice(toProc, N))
        if res:
            result.extend(res)
            print("Processed 11\n")
            time.sleep(1)
        else:
            print("Done\n")
            break
    keys = open("keywords.txt", 'w')
    abstracts = open("abstracts.txt", 'w')
    contents = open("contents.txt", 'w')
    merged = open("all_merged.txt", 'w')
    for proc in result:
        try:
            key = open(proc.kwFNameResult, 'r')
            abstract = open(proc.abstractFNameResult, 'r')
            content = open(proc.preProcessedFNameResult, 'r')
            keys.write(proc.file_id + ': ')
            abstracts.write(proc.file_id + ': ')
            contents.write(proc.file_id + ': ')
            merged.write(proc.file_id + ': ')
            for line in key:
                keys.write(line.strip() + ' ')
                merged.write(line.strip() + ' ')
            key.close()
            keys.write('\n')
            for line in abstract:
                abstracts.write(line.strip() + ' ')
                merged.write(line.strip() + ' ')
            abstracts.write('\n')
            abstract.close()
            for line in content:
                contents.write(line.strip() + ' ')
                merged.write(line.strip() + ' ')
            contents.write('\n')
            content.close()
            merged.write('\n')
        except FileNotFoundError:
            print (proc.preProcessedFNameResult + ' was not found')
    keys.close()
    abstracts.close()
    contents.close()
    merged.close()
        
        
