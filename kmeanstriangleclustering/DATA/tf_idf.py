import math
import pymongo
from pymongo import MongoClient
from operator import itemgetter

def wordCount(document):
  return len(document)

class TfidfClass:

  def __init__(self):
    self.documents = []
    self.client = MongoClient('localhost', 27017)
    self.db = self.client.test
    self.collection = self.db.collection

  def freq(self, word, document, index):
    #res = self.collection.find_one({ 'index' : str(index), 'word' : word })
    #cnt = 0
    #if res is None:
    #  cnt = document.count(word)
    #  self.collection.insert({ 'index' : str(index), 'word' : word, 'count' : str(cnt) })
    #else:
    #  cnt = int(res['count'])
    #return cnt
    return document.count(word)

  def numDocsContaining(self, word):
    count = 0
    for index, document in enumerate(self.documents):
      if self.freq(word, document, index) > 0:
        count += 1
    return count

  def tf(self, word, document, index):
    return (self.freq(word, document, index) / float(wordCount(document)))

  def idf(self, word):
    return math.log(len(self.documents) / 
                   float(self.numDocsContaining(word)))

  def tfidf(self, word, document, index):
    return (self.tf(word,document, index) * self.idf(word))

  def readNewsGroups(self):
    f = open('20ng-train-stemmed.txt', 'r')
    for line in f:
      words = line.split()
      self.documents.append(words[1:])
    f.close()
    print "Read news groups\n"
    return self.documents

  def runAlgorithm(self):
    words = {}
    words_coords = {}
    tfidf_file = open('tf_idf_pout.txt', 'w')
    documentNumber = 0
    next_coord = 0
    documentList = self.documents
    for index, document in enumerate(documentList):
      print "Doc number {0}\n".format(index)
      print "Contains {0} words\n".format(len(document))    
      doc_desc = {}
      for word in document:
        if word not in words_coords:
          words_coords[word] = next_coord
          next_coord = next_coord + 1
        if words_coord[word] not in doc_desc:
          doc_desc[words_coord[word]] = self.tfidf(word, document, index)
      for coord, tfidf_num in zip(doc_coords, doc_tfidf):
        tfidf_file.write("{0}:{1} ".format(coord, tfidf_num))
      tfidf_file.write("\n")
    tfidf_file.flush()
    tfidf_file.close()
    print "Done.\n"
    
	
if __name__ == '__main__':
  obj = TfidfClass()
  obj.readNewsGroups()
  obj.runAlgorithm()
  
 

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	