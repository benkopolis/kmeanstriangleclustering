"""
Module for mass test cases execution.
It does full clustering process, and based on that,
it can execute clustering evaluation.
"""

import sys
import configs
from getfiles import execute
from readclustered import read_clustered, variation_of_information

R_DIR = '/home/zby/MAGISTERKA/'
EXEC_PATH = '/home/zby/MAGISTERKA/MGR/mass_results/'
TF_IDF = '/home/zby/MAGISTERKA/MGR/results/tfidf/mass3_randonly/'

def drange(start, stop, step):
    """
    creates a decimal range, by defined step
    """
    elem = start
    while elem <= stop:
        yield elem
        elem += step

def root_name(file_name, file_id):
    """
    Returns a filename from root mgr dir"
    """
    if file_id is not None:
        return "{}{}".format(R_DIR, file_name.format(file_id))
    else:
        return "{}{}".format(R_DIR, file_name)

def tfidf_name(file_name, file_id):
    """
    creates a file path for tfidf
    """
    return "{}{}".format(TF_IDF, file_name.format(file_id))

def test(dist_param, picker_param, iters):
    """
    Tests clustering and tfidf - uses configuration passed.
    Increments stopwords variation entry by 0.5 each step.
    """
    orig = '/home/zby/MAGISTERKA/MGR/results/oryginal.clustered.t'
    cl_orig = read_clustered(orig)
    name_tag = ''
    ndist = dist_param[1:]
    npick = picker_param[1:]
    for index in drange(4, 20, 0.5):
        name_tag = "{}_{}_{}".format(index, npick, ndist)
        tf_conf = configs.TfidfConfig(
            root_name('all_merged.txt', None),
            tfidf_name('merged.stem{}.stop', name_tag),
            tfidf_name('merged.stem{}.stop.txt', name_tag),
            None,
            tfidf_name('merged.stem{}.tfidf', name_tag),
            10,
            0,
            None)
        execute(tf_conf)
        tf_conf = configs.TfidfConfig(
            root_name('all_merged.txt', None),
            None,
            tfidf_name('merged.stem{}.stop.txt', name_tag),
            tfidf_name('merged.stem{}.stop', name_tag),
            tfidf_name('merged.stem{}.stop.tfidf', name_tag),
            None,
            None,
            None)
        execute(tf_conf)
        #input, out, picker, distance, iterations,
        clust_cfg = configs.ClusteringConfig(
            tfidf_name('merged.stem{}.stop.tfidf', name_tag),
            tfidf_name('merged.stem{}.stop.clustered.t', name_tag),
            picker_param,
            dist_param,
            iters,
            None
        )
        execute(clust_cfg)
        clust2 = read_clustered(tfidf_name('merged.stem{}.stop.clustered.t', name_tag))
        var, norm = variation_of_information(cl_orig, clust2)
        print("**** FOR var {} VOI is {}".format(name_tag, norm))

def count_vario(dist_param, picker_param):
    """
    Tests clustering and tfidf - uses configuration passed.
    Increments stopwords variation entry by 0.5 each step.
    """
    orig = '/home/zby/MAGISTERKA/MGR/results/oryginal.clustered.t'
    cl_orig = read_clustered(orig)
    name_tag = ''
    ndist = dist_param[1:]
    npick = picker_param[1:]
    for index in drange(5, 20, 0.5):
        name_tag = "{}_{}_{}".format(index, npick, ndist)
        try:
            clust2 = read_clustered(tfidf_name('merged.stem{}.stop.clustered.t', name_tag))
        except:
            print("no data for {}".format(name_tag))
            continue
        var, norm = variation_of_information(cl_orig, clust2)
        print(" {} VOI is {}".format(name_tag, norm))

# -dham
# -rand
# 50
#
if __name__ == "__main__":
    """
    Tests everything
    """
    DISTS = ['-deuc', '-dcos'] # dham dman
    PICKERS = ['-rand'] # , , '-seq', '-dim'
    for dist in DISTS:
        for picker in PICKERS:
            print("Doing for: {}, {}".format(picker, dist))
            if sys.argv[1] == '-test':
                test(str(dist), str(picker), 30) # count_vario(dist, picker)
            elif sys.argv[1] == '-vario':
                count_vario(dist, picker)
            elif sys.argv[1] == '-sil':
                sil_count()


