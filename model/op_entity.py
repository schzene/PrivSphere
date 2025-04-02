
import re
import ast
import copy
from typing import List,Dict
import os


class MyOp:

    def __init__(self, name:str, dimension=[],parallel_axis=[],reduce_axis = [],stride=1, dilation=1):
        self.id = 0
        self.name = name
        self.dimension = dimension
        self.parallel_axis = parallel_axis
        self.reduce_axis = reduce_axis

        # attr for conv or pooling
        self.stride = stride
        self.dilation = dilation
        self.layout = ''
        self.pad = 0       # ignore pad now
        # export bench file here   
        self.bench_file = ''

    def generate_op_desc(self):
        result = 'x'.join(map(str, self.dimension))
        return f"{self.name}_{result}"

    def __repr__(self):
        return f"id {self.id} name='{self.name}', dimension='{self.dimension}' stride {self.stride} dilation {self.dilation}"

    
    def __eq__(self, other):
        if isinstance(other, MyOp):
            return self.name == other.name and self.dimension == other.dimension
        return



class SubGraph:

    def __init__(self, name:str):
        # id with root op dimention
        self.id = 0
        self.name = name
        self.pipeline = ''
        # raw workgroup info
        self.workgroup: SubGraph.WorkGroupConfig = None
        # ops tile config  
        self.tile_config : list[SubGraph.TileConfig] = []
        # result
        self.real_time = -1
        self.time_unit = 'us'
        self.bonus = -1
        self.default_time = -1
        self.dominate_op:MyOp = None
        # futher result 
        self.dram_bytes = 0
        self.compute_traffic = 0
        self.compute_throughout = 0
        self.mem_throughout = 0
        self.bench_file = ''

    def to_dict(self):
        return {
            'name': self.name,
            'id':self.id,
            'pipeline': self.pipeline,
            'workgroup': self.workgroup.workgroup if self.workgroup else None,
            'tile_config': self.tile_config[0].tile_config if self.tile_config else None,
            'real_time': self.real_time,
            'time_unit': self.time_unit,
            'bonus': self.bonus,
            'default_time': self.default_time,
            'dominate_op': self.dominate_op.generate_op_desc(),
            'dram_bytes': self.dram_bytes,
            'compute_traffic': self.compute_traffic,
            'compute_throughout': self.compute_throughout,
            'mem_throughout': self.mem_throughout,
        }
    
    @classmethod
    def from_dict(cls, data):
        subgraph = cls(data['name'])
        subgraph.id = data['id']
        subgraph.pipeline = data['pipeline']
        subgraph.workgroup = SubGraph.WorkGroupConfig(-1, str(data['workgroup']))
        subgraph.tile_config.append(SubGraph.TileConfig(-1, str(data['tile_config'])))
        subgraph.real_time = data['real_time']
        subgraph.default_time = data['default_time']
        subgraph.bonus = data['bonus']

        return subgraph
    
    def write_to_file(self, file_path, new_lines, lines):
        if not os.path.exists(file_path):
            with open(file_path, 'w') as file:
                file.write('')
        with open(file_path, 'w') as file:
            work_group_line_no = self.workgroup.workgroup_line_no
            new_lines[work_group_line_no] = lines[work_group_line_no].replace(self.workgroup.workgroup_str,str(self.workgroup.workgroup))

            for op_config in self.tile_config:
                tile_config_line_no = op_config.tile_config_line_no
                # warp single config
                if not isinstance(op_config.tile_config[0], list):
                    op_config.tile_config = [op_config.tile_config]
                new_lines[tile_config_line_no] = lines[tile_config_line_no].replace(op_config.tile_config_str,str(op_config.tile_config))
            file.writelines(new_lines)
    
    def set_ncu_result(self, result_dict:Dict[str,Dict]):
        ncu_time = 0
        ncu_mem = 0
        ncu_com = 0
        for key,value in result_dict.items():
            ncu_time += value["time"]
            ncu_mem += value["mem"]
            ncu_com += value["com"]
        self.real_time = ncu_time
        self.compute_throughout = ncu_com
        self.mem_throughout = ncu_mem




    class WorkGroupConfig:
        
        def __init__(self, id, ir:str):
            self.workgroup = ast.literal_eval(ir)
            self.workgroup_line_no = id
            self.workgroup_str = ir
        
    
    class TileConfig:
        
        def __init__(self, id, ir:str):
            self.tile_config = ast.literal_eval(ir) 
            self.tile_config_line_no = id
            self.tile_config_str = ir







class PolicyConfig:
    def __init__(self, workgroup:list,tile_config:list):
        self.workgroup = workgroup
        self.tile_config = tile_config
        # TODO vector etc..




@DeprecationWarning
class SimpleOp:

    def __init__(self, raw_str:str):
        pattern = r'(\d+)_(\w+)_([\d|x]+)'
        op_info = re.search(pattern, raw_str)
        if op_info is None:
            self.id = None
            return 
        self.id = op_info.group(1)
        self.name = op_info.group(2)
        self.dimension = op_info.group(3)
        self.parallel_axis = []
        self.reduce_axis = []
        self.bench_file = ''

    def __repr__(self):
        return f"Op(name='{self.name}', dimension='{self.dimension}')"



if __name__=="__main__":
    import pandas as pd
    path = '/root/Documents/welder/artifacts/temp2/bert/1/single_op/5_matmul/test'
    df = pd.read_csv(path, skiprows=2)
    exclude = "memcpy"

    gpu_time_duration = "gpu__time_duration.sum"
    memory_throughput = "gpu__compute_memory_throughput.avg.pct_of_peak_sustained_elapsed"
    compute_throughput = "sm__throughput.avg.pct_of_peak_sustained_elapsed"
    result_dict = {}
    for _, row in df.iterrows():
        kernel_name = row['Kernel Name'] 
        row_name = row['Metric Name']
        row_value = row["Metric Value"]
        if "memcpy" in kernel_name:
            continue
        if kernel_name not in result_dict:
            result_dict[kernel_name] = {}
        if  row_name == gpu_time_duration: 
            result_dict[kernel_name]["time"] = float(row_value) * 1e-3
        elif row_name == memory_throughput:
            result_dict[kernel_name]["mem"] = float(row_value)
        elif row_name == compute_throughput:
            result_dict[kernel_name]["com"] = float(row_value)
    print(result_dict)