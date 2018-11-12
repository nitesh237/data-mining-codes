import csv
import math
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.cm as cm
import random as rd

label={}
c1=[]
c2=[]

def read_data(filename):

    with open(filename, 'r') as csvfile:
        datareader = csv.reader(csvfile, delimiter=' ')
        traindata = []
        ct=1
        for row in datareader:
            for i in range(len(row)):
                row[i]=float(row[i])/10
            
            row=[ct]+row
            label[ct]=-1
            traindata.append(row)
            ct=ct+1
            
    return (traindata)

def findmin(pi,pt,k):
    mind=-1
    mdis=99999
    for i in range(k):
        if(disti(pi[i],pt) <= mdis):
            mdis=disti(pi[i],pt)
            mind=i
    return mind    

def disti(p1,p2):
  #  print(p1,p2)
    dist = math.sqrt(  (float(p1[1]) - float(p2[1])  )**2 + ( float(p1[2]) - float(p2[2])  )**2)  
    return dist  

def checkex(pi,pinew,k):
    ex=1
    if pi==pinew:
        return 1
    return 0
    

def kmeans(data,k):
    sz=len(data)-1
    pi=[]
    for i in range(k):
        pi.append(data[rd.randint(0,int(sz))])

    pas=0
    while(True):
        szi={}
        for i in range(k):
            szi[i]=1

        pinew=[]
        pas=pas+1

        for p in data:
            ind=findmin(pi,p,k)
            label[p[0]]=ind
            szi[ind]+=1
        
        #print(szi)

        for i in range(k):
            pinew.append([pi[i][0],pi[i][1],pi[i][2]])
            label[pi[i][0]]=i

        for i in data:
            for j in range(k):
                if(label[i[0]]==j):
                    pinew[j][1]+=i[1]
                    pinew[j][2]+=i[2]

        for j in range(k):
            pinew[j][1]=pinew[j][1]/szi[j]
            pinew[j][2]=pinew[j][2]/szi[j]
       
        if(checkex(pi,pinew,k)==1):
            break
            
        for i in range(k):
            pi[i]=pinew[i]
     
    return (pinew, pas)



kr=[]
errsm=[]

indata=read_data('DBSCAN.txt')



for i in range(1,11):
    kr.append(i)
    errsm.append(0)

for k in kr:
    errsm[k-1]=0
    ci,pa=kmeans(indata,k)
    print('( k=',k,') No. of passes :',pa)
    for j in range(k):
        for i in indata:
            if(label[i[0]]==j):        
                errsm[k-1]+=(disti(i,ci[j])**2)


plt.plot(kr,errsm,'ro-')

plt.show()