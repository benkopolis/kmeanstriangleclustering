import math
import pymongo
from pymongo import MongoClient
from operator import itemgetter
from random import sample, randint
from heapq import heappush, heappop

def wordCount(document):
  return len(document)

def random_sample(seq):
  """ Used to generate abstracts
  """
  if len(seq) = 0:
    return None
  return sample(seq, randint(1, len(seq)/2))

def get_keywords(seq):
  """ Used to generate keywords
  """
  if len(seq) = 0:
    return None
  freqs = {}
  for w in seq: 
    if w not in freqs:
	  freqs[w] = 1
	else
	  freqs[w] += 1
   num_keys = len(freqs)
   res = []
   
   return res

class TfidfClass:

  def __init__(self):
    self.documents = []
    self.words = {}
    self.words_coords = {}
    self.zero_words = {}
    self.nonzero_words = {}

  def freq(self, word, document, index):
    c = self.words_coords[word]
    if c in self.zero_words:
      if index in self.zero_words[c]:
        return 0
    elif index in self.nonzero_words:
      if c in self.nonzero_words[index]:
        return self.nonzero_words[index][c]
    cnt = document.count(word)
    if cnt == 0:
      if c not in self.zero_words:
        self.zero_words[c] = {}
      self.zero_words[c][index] = 0
    else:
      self.nonzero_words[index] = {}
      self.nonzero_words[index][c] = cnt
    return cnt

  def numDocsContaining(self, word):
    count = 0
    for index, document in enumerate(self.documents):
      if self.freq(word, document, index) > 0:
        count += 1
    return count

  def tf(self, word, document, index):
    result = self.freq(word, document, index)
    return (float(result) / float(wordCount(document))), result

  def idf(self, word):
    return math.log(len(self.documents) / 
                   float(self.numDocsContaining(word)))

  def tfidf(self, word, document, index):
    result, freq = self.tf(word, document, index)
    return ( * self.idf(word))

  def readNewsGroups(self):
    f = open('20ng-train-stemmed.txt', 'r')
    for line in f:
      words = line.split()
      self.documents.append(words[1:])
    f.close()
    print "Read news groups\n"
    return self.documents

  def runAlgorithm(self):
    tfidf_file = open('tf_idf_pout.txt', 'w')
    documentNumber = 0
    next_coord = 0
    documentList = self.documents
    for index, document in enumerate(documentList):
      print "Doc number {0}\n".format(index)
      print "Contains {0} words\n".format(len(document))    
      doc_tfidf = []
      doc_coords = []
      doc_freq = []
      for word in document:
        if word not in self.words_coords:
          self.words_coords[word] = next_coord
          next_coord = next_coord + 1
        doc_tfidf.append(self.tfidf(word, document, index))
        doc_coords.append(self.words_coords[word])
      for coord, tfidf_num in zip(doc_coords, doc_tfidf):
        tfidf_file.write("{0}:{1} ".format(coord, tfidf_num))
      tfidf_file.write("\n")
    tfidf_file.close()
    print "Done.\n"
    
	
if __name__ == '__main__':
  obj = TfidfClass()
  obj.readNewsGroups()
  obj.runAlgorithm()
  
 

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	