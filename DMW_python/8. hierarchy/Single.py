import numpy as np
import pandas as pd
import copy


def agglo(n,dis,clus):
    x=n
    for outer in range(n-1):
        ans=1e10
        mi=0
        mj=0
        for i in range(x):
            for j in range(x):
                if ans >= dis[i][j] and i!=j:
                    ans=dis[i][j]
                    mi=i
                    mj=j
        print('Merged ',clus[mi],clus[mj],' at step ',outer)
        nclus={}
        j=0
        for i in range(x):
            if i!=mi and i!=mj:
                nclus[j]=clus[i]
                j=j+1

        nclus[j]=[]
        mp={}

        j=0
        for i in range(x):
            if i!=mi and i!=mj:
                mp[j]=i
                j=j+1

        for i in clus[mi]:
            nclus[j].append(i)
        for i in clus[mj]:
            nclus[j].append(i)

        #print(clus,nclus)
        #print()
        #print(mp)

        ndis=[[0 for i in range(x-1)] for j in range(x-1)]

        for i in range(x-2):
            for j in range(x-2):
                if i==j:
                    ndis[i][j]=0
                else:
                    ndis[i][j]=dis[mp[i]][mp[j]]

        for i in range(x-1):
            if i==x-2:
                ndis[x-2][x-2]=0
                continue
            ndis[x-2][i]=min(dis[mi][mp[i]],dis[mj][mp[i]])

        for i in range(x-1):
            if i==x-2:
                ndis[x-2][x-2]=0
                continue
            ndis[i][x-2]=ndis[x-2][i]

        x=x-1

        dis=copy.deepcopy(ndis)
        for i in dis:
            print(i)
        print()
        print()
        clus=copy.deepcopy(nclus)
        #print(dis)

    return

dis=[]
n=input()
n=int(n)
for i in range(n):
    x=input().split(' ')
    p=[]
    #print(x)
    for i in x:
        p.append(int(i))
    dis.append(p)

#print()
#print(dis)

x=input().split(' ')


clus={}
for i in range(n):
    clus[i]=[x[i]]

agglo(n,dis,clus)

'''
6
0 662 877 255 412 996
662 0 295 468 268 400
877 295 0 754 564 138
255 468 754 0 219 869
412 268 564 219 0 669
996 400 138 869 669 0
BA FI MI NA RM TO
'''


'''
5
0 2 6 10 9
2 0 3 9 8
6 3 0 7 5
10 9 7 0 4
9 8 5 4 6
1 2 3 4 5
'''

