# import numpy as np
# import welder
# from welder.arch import *
# from welder.graph import IRNode, OutputNode
# from welder.policy import DefaultPolicy
# from welder.logging import setlog
# from welder.reference import get_subgraph_reference_outputs



class Result:
    def __init__(self, tilesize , work_group, real_time: float):
        self.parallel_dims = []
        self.reduce_axis = []
        self.tilesize = tilesize
        self.work_group = work_group
        self.real_time = real_time
        self.time_unit = 'ms'
        self.dram_bytes = 0
        self.compute_traffic = 0
        self.compute_throughout = 0
        self.mem_throughout = 0


if __name__ == "__main__":
    my_dict = {'a': 1, 'b': 2, 'c': 3}
    first_key, first_value = next(iter(my_dict.items()))
    print(first_key, first_value)
