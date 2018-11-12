from sklearn.cluster import Birch
import csv
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import numpy as np

X = np.loadtxt(fname = 'Dataset.txt', skiprows = 1)
# print(X)
X = [list(i) for i in X]
for i in range(len(X)):
	for j in range(2):
		X[i][j] = X[i][j] / 1000000

print(X)
X = np.array(X)
plt.scatter(X[:, 0], X[:, 1], s=4, c='black')
plt.show()

brc = Birch(branching_factor=50, n_clusters=7, threshold=0.05,compute_labels=True)
cftree = brc.fit(X)
ans = brc.predict(X)
labs = np.unique(ans)

cmap = plt.get_cmap('jet', len(labs))
plt.scatter(X[:, 0], X[:, 1], c=ans, s=4, cmap=cmap)
plt.show()

