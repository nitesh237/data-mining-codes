import csv
from random import shuffle
import matplotlib.pyplot as plt

def read_data(filename):

    with open(filename, 'r') as csvfile:
        datareader = csv.reader(csvfile, delimiter=',')
        traindata = []
        metadata=[]
        ct=1
        for row in datareader:
            if(ct==1):
                metadata=row
                ct+=1
                continue
            id=row[0]
            label=row[1]
            row=[id]+row[2:]+[label]
            for i in range(1,len(row)-1):
                row[i]=float(row[i])
            row[0]=int(row[0])
            traindata.append(row)
            
    return (traindata,metadata)

def distm(p1,p2):
    dist=0
    for i in range(len(p1)-1):
        dist+=(p1[i]-p2[i])**2
    return dist**(0.5)

def checkmaj(res,k,data):
    freq={}
    for i in res:
        freq[i[2]]=freq.get(i[2],0)+1

    mxfreq=-1
    mxclass='Null'
    for clas,freq in freq.items():
        if(freq>mxfreq):
            mxfreq=freq
            mxclass=clas
    #sorted_x = sorted(x.items(), key=operator.itemgetter(1))
    return mxclass


def knn(data,header,k,test):

    predict=[]
    sz=len(data[0])-1
    for inp in test:
        dlist=[]
        for j in data:
            dis=distm(j,inp)
            dlist.append( (j[0],dis,j[sz]) )
        dlist=sorted(dlist, key=lambda x: x[1])
        dlist=dlist[0:k]
        ans=checkmaj(dlist,k,data)
        predict+=[ans]
    
    return predict 


dataset,meta=read_data('datas.csv')
sz=len(dataset[0])
#shuffle(dataset)
testSet=dataset[70:]
dataset=dataset[:70]
accur=[]
kr=[]
for i in range(1,20):
    kr.append(i)
    accur.append(0)

print(len(kr),len(accur))

for k in kr:
    result=knn(dataset,meta,k,testSet)
    accur[k-1]=0
    for i in range(len(testSet)):
        if(testSet[i][sz-1]==result[i]):
            accur[k-1]+=1
    print('Training Accuracy :',(accur[k-1]/len(testSet))*100,' %')
    accur[k-1]=accur[k-1]*100/len(testSet)

#plt.subplot(121)
plt.plot(kr,[100-i for i in accur],'ro-',markevery=200)
plt.show()