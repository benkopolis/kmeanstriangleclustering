#!/usr/bin/python3.4

import os, time, sys
from getfiles import read_int, read_float, choose_file, get_filename, get_fileid, execute
from readclustered import read_clustered, variation_of_information
from configs import ClusteringConfig,\
 TfidfConfig, RandConfig, SilhouetteConfig, VariationOfInformationConfig

PIPE_NAME = ''
result_stats_path = '/home/zby/MAGISTERKA/MGR/results_stats/'
results_path = '/home/zby/MAGISTERKA/MGR/results/'
doc_path = '/home/zby/MAGISTERKA/law'

EXTENSIONS = {'clustered' : '.clustered',
              'tclustered' : '.clustered.t',
              'feature' : '.tfidf',
              'stemmed' : '.stem',
              'stopwords' : '.stem.stop'}

class CanceledException(Exception):
    """
    Error raised when user cancles operation, just show menu again.
    """
    pass

def menu():
    """
    Shows the menu
    """
    print("0. exit")
    print("1. cluster [obsolete]")
    print("2. get tfidf [obsolete]")
    print("3. count rand")
    print("4. count silhouette")
    print("5. count variation of information")
    print("10. print param line form last execution")

def cancel():
    """
    Cancles current operatiom
    """
    raise CanceledException()

def try_again():
    """
    Prints try again message
    """
    return "No such option, please try again."

def read_choice(switcher, read_func, def_value, msg, limit):
    """
    Reads menu choice
    """
    while True:
        val = read_func(msg, def_value, limit)
        func = switcher.get(val, try_again)
        param = func()
        if param != try_again():
            return param
        print(param)

def picker(last_picker):
    """
    Reads and constructs picker param
    """
    if last_picker is not None:
        print("-1. last used [{}]".format(last_picker))
    print("0. cancel")
    print("1. random picker")
    print("2. sequential picker")
    print("3. MST picker")
    pdict = {
        0 : cancel,
        1 : lambda: "-rand",
        2 : lambda: "-seq",
        3 : lambda: "-dim"
    }
    msg = "Choose picker [0]: "
    if last_picker is not None:
        msg = "Coose picker [-1]: "
    return read_choice(pdict, read_int, -1, msg, 4)

def distance(last_dist):
    """
    Reads and sets distance param
    """
    if last_dist is not None:
        print("-1. last used [{}]".format(last_dist))
    print("0. cancel")
    print("1. Hamming")
    print("2. Manhattan")
    print("3. Euclidean")
    print("4. Cosine")
    ddict = {
        0 : cancel,
        1 : lambda: "-dham",
        2 : lambda: "-dman",
        3 : lambda: "-deuc",
        4 : lambda: "-dcos"
    }
    msg = "Choose distance [0]: "
    if last_dist is not None:
        msg = "Choose distance [-1]: "
    return read_choice(ddict, read_int, -1, msg, 5)

def cluster(cluster_config):
    """
    Gets clustering stuff and executes
    """
    tfidf = ()
    tfidf_ext = [EXTENSIONS["feature"]]
    picker_param = None
    dist_param = None
    iters = 0
    out_file = ()
    exts = [EXTENSIONS["clustered"], EXTENSIONS["tclustered"]]
    if cluster_config is not None:
        picker_param = picker(cluster_config.picker)
        dist_param = distance(cluster_config.distance)
        tfidf = choose_file(results_path, tfidf_ext, get_fileid(cluster_config.tfidf), [])
        out_file = choose_file(results_path, exts, get_fileid(cluster_config.out), [])
        iters = read_int(
            "Numer of iteratios [{}]: ".format(
                cluster_config.iterations),
            cluster_config.iterations)
    else:
        picker_param = picker(None)
        dist_param = distance(None)
        tfidf = choose_file(results_path, tfidf_ext, None, [])
        out_file = choose_file(results_path, exts, None, [])
        iters = read_int("Numer of iteratios [25]: ", 25)
    cluster_config = ClusteringConfig(tfidf, out_file, picker_param, dist_param, iters, None)
    execute(cluster_config)
    return cluster_config


def count_tfidf(tfidf_config):
    """
    Method sets and counts tfidf
    """
    stem_file = ()
    stem_ext = [EXTENSIONS["stemmed"]]
    stop_out = ()
    stop_in = ()
    stop_ext = [EXTENSIONS["stopwords"]]
    stop_stats = ()
    tfidf = ()
    tfidf_ext = [EXTENSIONS["feature"]]
    min_variation = read_float('Please provide minimal variation: [{}]'.format(0), 0)
    if tfidf_config is None:
        stem_file = choose_file(results_path, stem_ext, None, [])
        stop_out = choose_file(results_path, stop_ext, None, [])
        stop_in = choose_file(results_path, stop_ext, None, [])
        stop_stats = choose_file(result_stats_path, ['.txt'], None, [])
        tfidf = choose_file(results_path, tfidf_ext, None, [])
        min_variation = read_float('Please provide minimal varation: ', 0)
    else:
        stem_file = choose_file(results_path, stem_ext, get_fileid(tfidf_config.stem), [])
        stop_out = choose_file(results_path, stop_ext, get_fileid(tfidf_config.stop_out), [])
        stop_in = choose_file(results_path, stop_ext, get_fileid(tfidf_config.stop_in), [])
        stop_stats = choose_file(
            result_stats_path, ['.txt'], get_fileid(tfidf_config.stop_stats), [])
        tfidf = choose_file(results_path, tfidf_ext, get_fileid(tfidf_config.tfidf), [])
        min_variation = read_float('Please provide minimal varation: ', tfidf_config.variation)
    tfidf_config = TfidfConfig(
        stem_file, stop_out, stop_stats, stop_in, tfidf, min_variation, 0, None)
    execute(tfidf_config)
    return tfidf_config

def count_rand(rand_config):
    """ function counts rand, if config present
    last used can be chosen """
    file1 = ()
    file2 = ()
    exts = [EXTENSIONS["clustered"], EXTENSIONS["tclustered"]]
    if rand_config is not None:
        file1 = choose_file(results_path, exts, get_fileid(rand_config.first_partition), [])
        file2 = choose_file(
            results_path, exts, get_fileid(rand_config.second_partition), [get_fileid(file1)])
    else:
        file1 = choose_file(results_path, exts, None, [])
        file2 = choose_file(results_path, exts, None, [get_fileid(file1)])
    print(PIPE_NAME)
    rand_config = RandConfig(file1, file2, None)
    execute(rand_config)
    return rand_config

def count_vario(vario_config):
    """ function counts variation of information, if config present
    last used can be chosen """
    file1 = ()
    file2 = ()
    exts = [EXTENSIONS["clustered"], EXTENSIONS["tclustered"]]
    if vario_config is not None:
        file1 = choose_file(results_path, exts, get_fileid(vario_config.first_partition), [])
        file2 = choose_file(
            results_path, exts, get_fileid(vario_config.second_partition), [get_fileid(file1)])
    else:
        file1 = choose_file(results_path, exts, None, [])
        file2 = choose_file(results_path, exts, None, [get_fileid(file1)])
    print(PIPE_NAME)
    vario_config = VariationOfInformationConfig(file1, file2, None)
    clust1 = read_clustered(get_filename(file1))
    clust2 = read_clustered(get_filename(file2))
    var, norm = variation_of_information(clust1, clust2)
    print("VARIATION_OF_INFORMATION {}".format(norm))
    return vario_config

def count_silhouette(sil_config):
    """ count silhouette index
    """
    dist_param = ''
    partition = ()
    tfidf = ()
    exts_partition = [EXTENSIONS["clustered"], EXTENSIONS["tclustered"]]
    exts_tfidf = [EXTENSIONS["feature"]]
    if sil_config is None:
        dist_param = distance(None)
        partition = choose_file(results_path, exts_partition, None, [])
        tfidf = choose_file(results_path, exts_tfidf, None, [])
    else:
        dist_param = distance(sil_config.lastDistance)
        partition = choose_file(results_path, exts_partition, get_fileid(sil_config.partition), [])
        tfidf = choose_file(results_path, exts_tfidf, get_fileid(sil_config.tfidf), [])
    sil_config = SilhouetteConfig(partition, tfidf, dist_param, None)
    execute(sil_config)
    return sil_config

def open_pipe():
    """
    currently not used, hangs on open
    """
    if len(sys.argv) > 2 and sys.argv[1] == '-pipe':
        pipe_name = sys.argv[2]
        print(pipe_name)
        if not os.path.exists(pipe_name):
            os.mkfifo(pipe_name)
        pipein = os.open(pipe_name, os.O_RDONLY)
        return os.fdopen(pipein)
    else:
        raise ValueError

def read_pipe_line():
    """
    Reads pipe - not used now.
    """
    pipein = open_pipe()
    while True:
        line = pipein.readline()
        if len(line) == 0:
            return
        yield line

if __name__ == "__main__":
    SWITCH = {
        1 : None,
        2 : None,
        3 : None,
        4 : None,
        5 : None
    }
    LAST = None
    while True:
        menu()
        CHOICE = read_int("Choose number [0]: ", 0, 10)
        print("Chosen option is {}".format(CHOICE))
        try:
            if CHOICE == 0:
                break
            elif CHOICE == 1:
                SWITCH[CHOICE] = cluster(SWITCH[CHOICE])
            elif CHOICE == 2:
                SWITCH[CHOICE] = count_tfidf(SWITCH[CHOICE])
            elif CHOICE == 3:
                SWITCH[CHOICE] = count_rand(SWITCH[CHOICE])
            elif CHOICE == 4:
                SWITCH[CHOICE] = count_silhouette(SWITCH[CHOICE])
            elif CHOICE == 5:
                SWITCH[CHOICE] = count_vario(SWITCH[CHOICE])
            elif CHOICE == 10:
                print(LAST.to_string())
            LAST = SWITCH[CHOICE]
        except CanceledException:
            pass
    print("Done\n")
    exit(0)


