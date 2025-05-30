# 20230499 Kim JaeHwan

import os
import math
from utils import converged, plot_2d, read_data, load_centroids, write_centroids_tofile, set_seed
import matplotlib.pyplot as plt

set_seed(42)

############################################################
# Problem 1: k-means clustering
############################################################

############################################################
# Problem 1a: calculate distance

def euclidean_distance(dp1, dp2):
    """Calculate the Euclidean distance between two data points.

    Arguments:
        dp1: a list of floats representing a data point
        dp2: a list of floats representing a data point

    Returns: the Euclidean distance between two data points
    """
    # BEGIN_YOUR_ANSWER
    return math.sqrt(sum([(i - j) ** 2 for i, j in zip(dp1, dp2)]))
    # END_YOUR_ANSWER

############################################################
# Problem 1b: assign data points

def assign_data(data_point, centroids):
    """Assign a single data point to the closest centroid. You should use
    the euclidean_distance function (that you previously implemented).

    Arguments:
        data_point: a list of floats representing a data point
        centroids: a dictionary representing the centroids where the keys are
                   strings (centroid names) and the values are lists of
                   centroid locations

    Returns: a string as the key name of the closest centroid to the data point
    """
    # BEGIN_YOUR_ANSWER
    return min(centroids, key=lambda x: euclidean_distance(data_point, centroids[x]))
    # END_YOUR_ANSWER

############################################################
# Problem 1c: update assignment

def update_assignment(data, centroids):
    """Assign all data points to the closest centroids. You should use
    the assign_data function (that you previously implemented).

    Arguments:
        data: a list of lists representing all data points
        centroids: a dictionary representing the centroids where the keys are
                   strings (centroid names) and the values are lists of
                   centroid locations

    Returns: a new dictionary whose keys are the centroids' key names and
             values are lists of points that belong to the centroid. If a
             given centroid does not have any data points closest to it,
             do not include the centroid in the returned dictionary.
    """
    # BEGIN_YOUR_ANSWER
    cent_dist = dict()
    for d in data:
        closest = assign_data(d, centroids)
        cent_dist[closest] = cent_dist.get(closest, list()) + [d]
    return cent_dist
    # END_YOUR_ANSWER
            
############################################################
# Problem 1d: update centroids

def mean_of_points(data):
    """Calculate the mean of a given group of data points. You should NOT
    hard-code the dimensionality of the data points).

    Arguments:
        data: a list of lists representing a group of data points

    Returns: a list of floats as the mean of the given data points
    """
    # BEGIN_YOUR_ANSWER
    return [sum(x) / len(data) for x in zip(*data)]
    # END_YOUR_ANSWER


def update_centroids(assignment_dict):
    """Update centroid locations as the mean of all data points that belong
    to the cluster. You should use the mean_of_points function (that you
    previously implemented).

    Arguments:
        assignment_dict: the dictionary returned by update_assignment function

    Returns: A new dictionary representing the updated centroids
    """
    # BEGIN_YOUR_ANSWER
    return {k: mean_of_points(v) for k, v in assignment_dict.items()}
    # END_YOUR_ANSWER



def main(data, init_centroids):
    #######################################################
    # You do not need to change anything in this function #
    #######################################################
    centroids = init_centroids
    old_centroids = None
    step = 0
    while not converged(centroids, old_centroids):
        # save old centroid
        old_centroids = centroids
        # new assignment
        assignment_dict = update_assignment(data, old_centroids)
        # update centroids
        centroids = update_centroids(assignment_dict)
        # plot centroid
        fig = plot_2d(assignment_dict, centroids)
        plt.title(f"step{step}")
        fig.savefig(os.path.join("results", "2D", f"step{step}.png"))
        plt.clf()
        step += 1
    print(f"K-means converged after {step} steps.")
    return centroids


if __name__ == '__main__':
    data, label = read_data("data/data_2d.csv")
    init_c = load_centroids("data/2d_init_centroids.csv")
    final_c = main(data, init_c)
    write_centroids_tofile("2d_final_centroids.csv", final_c)
