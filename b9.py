"""
To understand the code better i have written a a lot of print statments.
Uncomment those to understand what exactly is going on in different functions
also the params to all the functions are now properly named to understand what is happeing in the functions
Best of luck.
1byxero
"""


from math import sqrt,log
from collections import Counter
from operator import itemgetter

def idf(word,allDocuments):
	# inverse document frequency	
	numofdocswiththisword = 0
	for document in allDocuments:
		if word in document:
			numofdocswiththisword+=1
	if numofdocswiththisword:
		return round(log(float(float(len(allDocuments))/float(numofdocswiththisword)),2),3)
	else:
		return 0

def tf(word,file):
	#term frequency
	return file.count(word)

def calculate_tfidf(word,testfile,clean_filecontents):	
	return tf(word,testfile)*idf(word,clean_filecontents)

def lengthof(file,unq_words,clean_filecontents):
	val = 0
	for word in unq_words:
		val+=pow(calculate_tfidf(word,file,clean_filecontents),2)
	return sqrt(val)

def cosineSimilarity(testfile,trainfile,unique_words,clean_filecontents):
	a = 0			
	b = lengthof(testfile,unique_words,clean_filecontents)*lengthof(trainfile,unique_words,clean_filecontents)
	for word in unique_words:
		a+=calculate_tfidf(word,testfile,clean_filecontents)*calculate_tfidf(word,trainfile,clean_filecontents)
	if not b:
		return 0
	else:
		return round(a/b,3)




def main():
	documents = ["doc1.txt","doc2.txt","doc3.txt","doc4.txt","doc5.txt","doc6.txt",]
	dataset = [["doc1.txt", "animals"],["doc2.txt","animals"],["doc3.txt","animals"],
				["doc4.txt","sports"],["doc5.txt","sports"],["doc6.txt","sports"]]

	#dataset has files with class
	filecontents = []

	for file in documents:
		filecontents.append(open(file,"r").read())

	# print "\n"
	# for i in filecontents:
	# 	print i

	clean_filecontents = []

	for i in filecontents:
		clean_filecontents.append(i.lower().rstrip("\n"))
	#removed newline charaters from right ends of sentences

	# print "\n"
	# for i in clean_filecontents:
	# 	print i

	unique_words = []
	for i in clean_filecontents:
		unique_words += i.split()


	# this isnt really needed but if things dont go right uncomment this :-p . i dont really have a reason to why uncomment this
	# unique_words = set(unique_words)
	# unique_words = list(unique_words)

	# print "\n"
	# for i in unique_words:
	# 	print i


	testfilename = raw_input("Enter test filename: ")
	testfile = open(testfilename,"r").read().lower()

	count = 0		

	#add cos similarity to dataset
	for trainfile in clean_filecontents:				
		dataset[count]+=[cosineSimilarity(testfile,trainfile,unique_words,clean_filecontents)]
		count+=1	

	k = 3
	#knn with cosine similarity to find 3 closest documents

	sorted_dataset = sorted(dataset,key=itemgetter(2),reverse=True)

	#sortdataset in descending order depending on scores i.e. 2nd index
	
	#sort dataset using cosine similarity

	top_k = sorted_dataset[:k]
	#here take top k similar docs
	print top_k
	top_k[:] = ( x for x in top_k if x[2]!=0)
	#here take top k similar docs and remove any if its score is xero

	if len(top_k):		
		class_count = Counter(category for (document,category,value) in top_k)		
		#count number of files in each category

		classification = max(class_count, key=lambda cls:class_count[cls])
		#return class with max count

		print "Class for test file is"
		print classification
	else:
		print "Does not match"


main()


