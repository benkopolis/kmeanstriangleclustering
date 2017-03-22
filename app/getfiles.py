"""
Module for reading user input
"""

import os


def read_int(console_msg, defaultValue = None, limit = None):
    while True:
        try:
            read = input(console_msg)
            if len(read) == 0 and defaultValue is not None:
                return defaultValue
            elif len(read) == 0:
                raise ValueError
            iread = int(read)
            if limit is not None and iread > limit:
                raise ValueError
            return iread
        except ValueError:
            print("Wrong format for integer, or too big number")

def read_float(console_msg, defaultValue = None):
    while True:
        try:
            read = input(console_msg)
            if len(read) == 0 and defaultValue is not None:
                return defaultValue
            elif len(read) == 0:
                raise ValueError
            return float(read)
        except ValueError:
            print("Wrong format for float")

def getFiles(aPath, extension):
    for (dirpath, dirnames, filenames) in os.walk(aPath):
        for fname in filenames:
            if fname.endswith(extension) and 'for_r' not in dirpath:
                yield (dirpath, fname)

def get_filename(file_triplet):
    """
    Gets file name and path
    """
    if isinstance(file_triplet, tuple):
        dir_p, file_p, id_p = file_triplet
        return "{}/{}".format(dir_p, file_p)
    else:
        return file_triplet

def get_fileid(file_triplet):
    """
    Gets file id
    """
    if isinstance(file_triplet, tuple):
        dir_p, file_p, id_p = file_triplet
        return id_p
    else:
        return file_triplet

def choose_file(path_param, extensions, def_value, exclude):
    """
    Choses files from all avaiable
    """
    files = {}
    counter = 0
    dir_chosen = ''
    file_chosen = ''
    for ext in extensions:
        for dirpath, fname in getFiles(path_param, ext):
            if counter not in exclude:
                files[counter] = (dirpath, fname)
                print("{}. {}".format(counter, fname))
            counter = counter + 1
    print("{}. Use empty value".format(counter + 1))
    print("{}. Enter new file full path".format(counter + 2))
    msg = "Please choose one of the files: "
    if def_value is not None:
        msg = "Please choose one of the files [{}]: ".format(def_value)
    choice = read_int(msg, def_value, counter + 2)
    if choice == counter + 1:
        return ('', '', '')
    elif choice == counter + 2:
        dir_chosen = input('Please provide directory in which file lies/should be created: ')
        file_chosen = input('Please provide plain file name: ')
    else:
        dir_chosen, file_chosen = files[choice]
        print("Selected file is: {}/{}".format(dir_chosen, file_chosen))
    return (dir_chosen, file_chosen, choice)

def execute(cfg):
    print(cfg.to_string())
    os.system("./app {}".format(cfg.to_string()))

if __name__ == "__main__":
   pass