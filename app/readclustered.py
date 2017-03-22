"""
Module for variation counting
"""

from math import log

def variation_of_information(X, Y):
    """
    Counts variation of information
    """
    n = float(sum([len(x) for x in X]))
    sigma = 0.0
    for x in X:
        pindex = len(x) / n
        for y in Y:
            qindex = len(y) / n
            rindex = len(set(x) & set(y)) / n
            if rindex > 0.0:
                sigma += rindex * (log(rindex / pindex, 2) + log(rindex / qindex, 2))
    return abs(sigma), abs(sigma) / log(n, 2)

class InvalidClusteredFormat(Exception):
    """
    Class represents error when wrong reader was used to read clustered file
    """
    pass


def read_tclustered(file_name):
    """
    reads t-clustered files
    """
    data = {}
    result = []
    with open(file_name, 'r') as tclust:
        for line in tclust:
            if len(line) == 0:
                continue
            splitted = line.split()
            if len(splitted) == 0:
                continue
            if len(splitted) != 2:
                raise InvalidClusteredFormat
            if int(splitted[1]) not in data:
                data[int(splitted[1])] = []
            data[int(splitted[1])].append(int(splitted[0]))
    for key, value in data.items():
        result.append(value)
    return result

def read_nclustered(file_name):
    """
    reads n-clustered files
    """
    result = []
    with open(file_name, 'r') as tclust:
        for line in tclust:
            splitted = line.split()
            cluster = []
            for elem in splitted[1:]:
                cluster.append(elem)
            result.append(cluster)
    return result

def read_clustered(file_name):
    """
    Read general clustered file
    """
    result = []
    try:
        result = read_tclustered(file_name)
    except InvalidClusteredFormat:
        print("INVALID FORMAT")
        result = read_nclustered(file_name)
    return result


