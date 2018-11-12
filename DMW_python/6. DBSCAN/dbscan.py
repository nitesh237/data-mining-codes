from sklearn.metrics import pairwise_distances_argmin
import numpy as np
import matplotlib.pyplot as plt
import math
import stack

X = np.loadtxt(fname = 'DBSCAN.txt', skiprows = 1)

'''plt.scatter(X[:, 0], X[:, 1], s=10, c='black')
plt.show()
'''

def dist(x, y):
    return math.sqrt(((x[0] - y[0]) * (x[0] - y[0])) + ((x[1] - y[1]) * (x[1] - y[1])))


def dist_query(visited, X, c_p, eps):
    neighbours = []
    i = 0
    for point in X:
        # and visited[i] != 'YV'
        if dist(point, c_p) <= eps :
            # print(point)
            # print(c_p)
            # print(dist(point, c_p))
            neighbours.append(i)
        i += 1
    return neighbours


def dbscan(X, eps, min_points):
    visited = {}
    n_cluster = 0
    for i in range(X.shape[0]):
        visited[i] = 'NV'

    # print(visited)
    final_clusters = []
    for point in visited:
        print(point)
        s = set()
        if visited[point] != 'NV':
            continue

        # print('n')
        neighbours = dist_query(visited, X, X[point], eps)
        # print(neighbours)
        
        if len(neighbours) < min_points:
            visited[point] = 'Noise'
            continue

        n_cluster += 1
        visited[point] = 'YV'

        s = set(neighbours)
        s.remove(point)

        stk = stack.Stack()
        for elem in s:
            stk.push(elem)
        temp = []
        temp.append(point)
        while stk.isEmpty() == False:
            q = stk.pop()
            if visited[q] == 'Noise':
                visited[q] = 'YV'
            if visited[q] == 'YV':
                continue;
            temp.append(q)
            visited[q] = 'YV'
            neighbours = dist_query(visited, X, X[q], eps)
            if len(neighbours) >= min_points :
                for elem in neighbours:
                    stk.push(elem)
        
        final_clusters.append(temp)


    return n_cluster, final_clusters



#  parameters for 2nd dataset 12000 8
# parameters for 1st question 7 12
# 7 and 9 best
# 20 and 100

n_cluster, final_clusters = dbscan(X, 20, 100)
labels = [0] * X.shape[0]

color = 1
for row in final_clusters:
    for elem in row:
        labels[elem] = color
    color += 1

print(n_cluster)
'''cmap = plt.get_cmap('jet', color)
cmap.set_under('gray')
fig, ax = plt.subplots()
labels = np.array(labels)
cax = ax.scatter(X[:, 0], X[:, 1], c=labels, s=4, cmap= cmap, vmin = 0.1, vmax=labels.max())
fig.colorbar(cax, extend='min')
plt.show()'''
plt.scatter(X[:, 0], X[:, 1], c = labels, s=4)
plt.show()
# for k in range(1, 11):

# 	centers, labels = find_clusters(X, k)
# 	
