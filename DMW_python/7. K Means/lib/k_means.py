from sklearn.metrics import pairwise_distances_argmin
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns; sns.set()
X = np.loadtxt(fname = 'K-means dataset.txt', skiprows = 1)


plt.scatter(X[:, 0], X[:, 1], s=10, c='black')
plt.show()


def find_clusters(X, n_clusters, rseed=2):
    # 1. Randomly choose clusters
    rng = np.random.RandomState(rseed)
    
    i = rng.permutation(X.shape[0])[:n_clusters]

    centers = X[i]
    # print(centers)
    while True:
        # 2a. Assign labels based on closest center
        labels = pairwise_distances_argmin(X, centers)
        
        # 2b. Find new centers from means of points
        # print([X[labels == i].mean(0) for i in range(n_clusters)].shape)
        new_centers = np.array([X[labels == i].mean(0)
                                for i in range(n_clusters)])
        print(new_centers.shape)
        # 2c. Check for convergence
        if np.all(centers == new_centers):
            break
        centers = new_centers
    

    return centers, labels

for k in range(1, 11):

    centers, labels = find_clusters(X, k)
    plt.scatter(X[:, 0], X[:, 1], c=labels, s=10, cmap='viridis')

    print(labels.shape)
    plt.show()
