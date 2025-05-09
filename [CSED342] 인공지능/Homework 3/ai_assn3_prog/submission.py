# 20230499 KimJaeHwan

import random
import collections
import math
import sys
from collections import Counter
from util import *

SEED = 4312

############################################################
# Problem 3: binary classification
############################################################

############################################################
# Problem 3a: feature extraction


def extractWordFeatures(x):
    """
    Extract word features for a string x. Words are delimited by
    whitespace characters only.
    @param string x:
    @return dict: feature vector representation of x.
    Example: "I am what I am" --> {'I': 2, 'am': 2, 'what': 1}
    """
    # BEGIN_YOUR_ANSWER (our solution is 6 lines of code, but don't worry if you deviate from this)
    d = dict()
    for word in x.split(" "):
        d[word] = d.get(word, 0) + 1
    return d
    # END_YOUR_ANSWER


############################################################
# Problem 3b: stochastic gradient descent


def learnPredictor(trainExamples, testExamples, featureExtractor, numIters, eta):
    """
    Given |trainExamples| and |testExamples| (each one is a list of (x,y)
    pairs), a |featureExtractor| to apply to x, and the number of iterations to
    train |numIters|, the step size |eta|, return the weight vector (sparse
    feature vector) learned.

    You should implement stochastic gradient descent.

    Note:
    1. only use the trainExamples for training!
    You can call evaluatePredictor() on both trainExamples and testExamples
    to see how you're doing as you learn after each iteration.
    2. don't shuffle trainExamples and use them in the original order to update weights.
    3. don't use any mini-batch whose size is more than 1
    """
    weights = {}  # feature => weight

    def sigmoid(n):
        return 1 / (1 + math.exp(-n))

    # BEGIN_YOUR_ANSWER (our solution is 14 lines of code, but don't worry if you deviate from this)

    for _ in range(numIters):
        for X, y in trainExamples:
            phi = featureExtractor(X)
            score = dotProduct(weights, phi)
            prob = sigmoid(score)
            # epsilon = 0.001
            # loss = - math.log(prob) if y == 1 else - math.log(1 - prob)
            # gradient = dict()
            # for feature in phi.keys():
            #     weights[feature] = weights.get(feature, 0) + epsilon
            #     plus = - math.log(sigmoid(dotProduct(weights, phi))) if y == 1 else - math.log(1 - sigmoid(dotProduct(weights, phi)))
            #     gradient[feature] = (plus - loss) / epsilon
            #     weights[feature] -= epsilon
            gradient = {feature: (prob - 1) * phi[feature] if y == 1 else prob * phi[feature] for feature in phi.keys()}
            increment(weights, -eta, gradient)

    # END_YOUR_ANSWER
    return weights


############################################################
# Problem 3c: bigram features


def extractBigramFeatures(x):
    """
    Extract unigram and bigram features for a string x, where bigram feature is a tuple of two consecutive words. In addition, you should consider special words '<s>' and '</s>' which represent the start and the end of sentence respectively. You can exploit extractWordFeatures to extract unigram features.

    For example:
    >>> extractBigramFeatures("I am what I am")
    {('am', 'what'): 1, 'what': 1, ('I', 'am'): 2, 'I': 2, ('what', 'I'): 1, 'am': 2, ('<s>', 'I'): 1, ('am', '</s>'): 1}
    """
    # BEGIN_YOUR_ANSWER (our solution is 5 lines of code, but don't worry if you deviate from this)
    words = (["<s>"] + x.split() + ["</s>"])
    phi = dict()
    for i in range(len(words) - 1):
        phi[words[i]] = phi.get(words[i], 0) + 1
        phi[(words[i], words[i + 1])] = phi.get((words[i], words[i + 1]), 0) + 1
    phi.pop("<s>")
    # END_YOUR_ANSWER
    return phi
