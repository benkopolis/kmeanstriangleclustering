#!/usr/bin/python3.4

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

    return True

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
        res = p.map(process, itertools.islice(toProc, N))
        if res:
            result.extend(res)
            print("Processed 11\n")
            time.sleep(1)
        else:
            print("Done\n")
            break
        
