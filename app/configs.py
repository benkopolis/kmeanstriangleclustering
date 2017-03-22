from getfiles import get_fileid, get_filename

class Config:
    """
    Basic class for config
    """
    def __init__(self, pipe_name, inputid, outputid):
        self.pipe_name = pipe_name
        self.input_id = inputid
        self.output_id = outputid

    def to_string(self):
        """
        Converts to comand line params 
        """
        if self.pipe_name is not None and len(self.pipe_name) > 0:
            return "-pipe {}".format(self.pipe_name)
        else:
            return ""

class ClusteringConfig(Config):
    """
    Comand line config for clustering 
    """
    def __init__(self, input, out, picker, distance, iterations, pipeName):
        Config.__init__(self, pipeName, ["tfidf"], ["clustered", "tclustered"])
        self.tfidf = input
        self.out = out
        self.picker = picker
        self.iterations = iterations
        self.distance = distance

    def to_string(self):
        return "-input {} -out {} -iter {} {} {} {}".format(
            get_filename(self.tfidf),
            get_filename(self.out),
            self.iterations,
            self.distance,
            self.picker,
            Config.to_string(self))

class TfidfConfig(Config):
    """
    Tfidf config clas
    """
    def __init__(
            self,
            stemFile,
            stopOut,
            stopStats,
            stopIn,
            tfidf,
            minVariation,
            minDocFreq,
            pipeName):
        Config.__init__(self, pipeName, ["stem", "stop"], ["tfidf", "stop"])
        self.stem = stemFile
        self.stop_out = stopOut
        self.stop_in = stopIn
        self.stop_stats = stopStats
        self.tfidf = tfidf
        self.variation = minVariation
        self.doc_freq = minDocFreq

    def to_string(self):
        if self.stop_in is not None:
            return "-stem {} -istop {} -tfidf {} {}".format(
                get_filename(self.stem),
                get_filename(self.stop_in),
                get_filename(self.tfidf),
                Config.to_string(self))
        else:
            return \
            "-stem {} -stop {} -stop_stats {} -tfidf {} -min_variation {} -min_docfreq {} {}" \
            .format(get_filename(self.stem),
                    get_filename(self.stop_out),
                    get_filename(self.stop_stats),
                    get_filename(self.tfidf),
                    self.variation,
                    self.doc_freq,
                    Config.to_string(self))

class RandConfig(Config):
    """
    Rand config class
    """
    def __init__(self, partOne, partTwo, pipe_name):
        Config.__init__(self, pipe_name, ["clustered", "tclustered"], [])
        self.first_partition = partOne
        self.second_partition = partTwo

    def to_string(self):
        return "-randindex -pone {} -ptwo {} {}".format(
            get_filename(self.first_partition),
            get_filename(self.second_partition),
            Config.to_string(self))

class VariationOfInformationConfig(Config):
    """
    Variation of information config class
    """
    def __init__(self, partOne, partTwo, pipe_name):
        Config.__init__(self, pipe_name, ["clustered", "tclustered"], [])
        self.first_partition = partOne
        self.second_partition = partTwo

    def to_string(self):
        return "-varoi -pone {} -ptwo {} {}".format(
            get_filename(self.first_partition),
            get_filename(self.second_partition),
            Config.to_string(self))

class SilhouetteConfig(Config):
    """
    Silhouette config class
    """
    def __init__(self, partition, tfidf, distance_param, pipe_name):
        Config.__init__(self, pipe_name, ["tfidf", "clustered", "tclustered"], [])
        self.partition = partition
        self.tfidf = tfidf
        self.distance = distance_param

    def to_string(self):
        return "-silhouette -partition {} -tfidf {} {} {}".format(
            get_filename(self.partition),
            get_filename(self.tfidf),
            self.distance,
            Config.to_string(self))

