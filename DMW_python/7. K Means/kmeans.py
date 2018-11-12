import csv
import math
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.cm as cm
import random as rd

label={}

def read_data(filename):
    data = np.loadtxt(filename, delimiter = ' ')
    dataset = []
    rows = len(data)
    for i in range(1,rows):
        dataset.append(list(data[i]))
    return dataset

def distance(p1,p2):
    dist = math.sqrt( (float(p1[0]) - float(p2[0])  )**2 + ( float(p1[1]) - float(p2[1])  )**2)  
    return dist 

def find_cluster(centroids, point, k):
    index = -1
    min_distance = 99999
    for i in range(k):
        dist = distance(centroids[i], point)
        if(dist <= min_distance):
            min_distance = dist
            index = i
    return index    

def check(centroids, new_centroids, k):
    if centroids == new_centroids:
        return 1
    return 0
    

def kmeans(data,k):
    size = len(data)
    centroids = []
    for i in range(k):
        centroids.append(data[rd.randint(0,int(size))])

    iteration = 0

    while(True):
        iteration += 1

        for point in data:
            index = find_cluster(centroids, point, k)
            label[tuple(point)] = index

        new_centroids = []
        for i in range(k):
            new_centroids.append([0.0,0.0])

        points_count = [0] * k

        #print(new_centroids)

        for point in data:
            index = label[tuple(point)]
            new_centroids[index][0] += point[0]
            new_centroids[index][1] += point[1]
            points_count[index] += 1
        
        for i in range(k):
            new_centroids[i][0] = new_centroids[i][0] / points_count[i]
            new_centroids[i][1] = new_centroids[i][1] / points_count[i]
        print(new_centroids)
        if(check(centroids,new_centroids,k) == 1):
            break
        
        for i in range(k):
            centroids[i] = new_centroids[i]
     
    return (new_centroids, iteration)



k = int(input())
dataset = read_data('K-means dataset.txt')
centroids , iteration = kmeans(dataset, k)

print('No. of passes :',iteration)

colors = [0] * len(dataset)
for i in range(len(dataset)):
    colors[i] = label[tuple(dataset[i])]

dataset = np.array(dataset)
plt.scatter(dataset[:,0], dataset[:,1], c = colors)
plt.show()