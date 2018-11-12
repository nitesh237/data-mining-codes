
from pyclustering.utils import read_sample;
from pyclustering.utils import timedcall;

from pyclustering.samples.definitions import SIMPLE_SAMPLES;
from pyclustering.samples.definitions import FCPS_SAMPLES;

from pyclustering.cluster import cluster_visualizer;
from pyclustering.cluster.cure import cure;

'''
import time
start_time = time.time()
main()
print("--- %s seconds ---" % (time.time() - start_time))'''
def template_clustering(number_clusters, path, number_represent_points = 5, compression = 0.5, draw = True, ccore_flag = False):
    sample = read_sample(path);
    
    cure_instance = cure(sample, number_clusters, number_represent_points, compression, ccore_flag);
    (ticks, _) = timedcall(cure_instance.process);
    
    clusters = cure_instance.get_clusters();
    representors = cure_instance.get_representors();
    means = cure_instance.get_means();
    
    print("Sample: ", path, "\t\tExecution time: ", ticks, "\n");

    if (draw is True):
        visualizer = cluster_visualizer();
        
        visualizer.append_clusters(clusters, sample);

        for cluster_index in range(len(clusters)):
            visualizer.append_cluster_attribute(0, cluster_index, representors[cluster_index], '*', 10);
            visualizer.append_cluster_attribute(0, cluster_index, [ means[cluster_index] ], 'o');
        
        visualizer.show();


template_clustering(5, 'DBSCAN.txt');