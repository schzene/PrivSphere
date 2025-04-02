from op_entity import MyOp
import logging
import re
import os.path as osp
import subprocess
from typing import Dict
import os
import pandas as pd
from pytorch import *
import shutil

name_pattern = r'linalg\.(\w+)'
input_pattern = r'ins\(%\w+, %\w+ : tensor<(\w+)>, tensor<(\w+)>\)'
out_pattern = r'outs\(%\w+ : tensor<(\w+)>\)'


# %18 = linalg.generic {
# indexing_maps = [affine_map<(d0, d1, d2) -> (d0, d2)>, affine_map<(d0, d1, d2) -> (d1, d2)>, affine_map<(d0, d1, d2) -> (d0, d1)>], 
# iterator_types = ["parallel", "parallel", "reduction"]} 
# ins(%13, %14 : tensor<128x768xf32>, tensor<3072x768xf32>) outs(%17 : tensor<128x3072xf32>) 
def generate_matmul(line):
    name = re.search(name_pattern, line).group(1)
    input1 = re.search(input_pattern, line).group(1)
    input2 = re.search(input_pattern, line).group(2)

    dims1 = input1.split('x')
    dims2 = input2.split('x')
    layout = ''
    m,k = map(int,dims1[-3:-1])
    if name == 'batch_matmul':
        # MxK KxN
        layout = 'MKN'
        k, n = map(int,dims2[-3:-1])
        b = int(dims1[0])
    else: 
        #  generic matmul_transpose_b
        layout = 'MNK'
        name = "matmul_trans"
        n, k = map(int,dims2[-3:-1])
        b = 1
        
    dimension = [b, m, n, k]
    matmul_op = MyOp(name,dimension,[b,m,n],[k])    
    matmul_op.layout = layout
    return matmul_op


def generate_conv(str):
    pass

def generate_pooling(str):
    pass


def append_op(id, op:MyOp , ops_list):
    if op in ops_list:
        return
    id += 1
    op.id = id
    ops_list.append(op)


def gather_ops(mlir_file:str)-> list[MyOp]:
    # list for all ops
    ops_list = []
    id = 0
    with open(mlir_file, 'r', encoding='utf-8') as file:
        for line in file:
            if "dialect_resources" in line:
                # skip params
                return ops_list
            if "linalg." not in line:
                continue
            if "conv" in line:
                name = re.search(name_pattern, line).group(1)
                # n c h w
                input = re.search(input_pattern, line).group(1)
                # f c kh kw
                kernel = re.search(input_pattern, line).group(2)
                # n f h w
                out = re.search(out_pattern, line).group(1)
                stride_pattern = r'strides = dense<(\d+)>'
                dilation_pattern = r'dilations = dense<(\d+)>'
                stride = re.search(stride_pattern, line).group(1)
                dilation = re.search(dilation_pattern, line).group(1)

                if stride is None or dilation is None or input is None or out is None:
                    logging.error(f"cannot parse conv in: {line}")
                    break
                n,c,ih,iw = map(int,input.split('x')[:-1])
                f,c,kh,kw = map(int,kernel.split('x')[:-1])
                n,f,oh,ow = map(int,out.split('x')[:-1])
                # note:  dims for output , aims for input conv , save all dims with nchw_fhw_hw layout
                dimension = [n,c,ih,iw,f,kh,kw,oh,ow]
                conv_op = MyOp(name,dimension,[n,f,oh,ow],[c,kh,kw],int(stride),int(dilation))
                append_op(id, conv_op, ops_list)
            elif "matmul" in line:
                matmul_op = generate_matmul(line)
                append_op(id, matmul_op, ops_list)

            elif "linalg.generic" in line:
                if '["parallel", "parallel", "reduction"]' in line:
                    matmul_op = generate_matmul(line) 
                    append_op(id, matmul_op, ops_list)
            else:
                pass
    return ops_list


            




class LinalgGenericParser:
    def __init__(self, ir_string:str):
        self.ir_string = ir_string
        self.tensor_shapes = {}
        self.parse()
        self.stack = []


    def parse(self):
        name_pattern = r'linalg\.(\w+)'
        input_reg = r"ins\((%[a-z0-9_]+(, )?)+ : (tensor<[\dxfi]+>(, )?)+\)"
        out_reg = r"outs\((%[a-z0-9_]+(, )?)+ : (tensor<[\dxfi]+>(, )?)+\)"
        name = re.search(name_pattern, self.ir_string).group(1)
        if name is None:
            raise Exception("tiling config on no linalg op case!"+ self.ir_string)
        input1 = re.search(input_reg, self.ir_string).group(1)
        input2 = re.search(out_reg, self.ir_string).group(2)
        print()
        




@DeprecationWarning
def generate_mlir(op_path, op:MyOp):
    from torch2mlir_model import torch2mlir
    os.makedirs(op_path, exist_ok=True)
    if "matmul" in op.name:
        model,input_dict = matmul(op.parallel_axis[0],op.parallel_axis[1],op.reduce_axis[0],op.parallel_axis[2])
    elif "conv" in op.name:
        # n, c, h, w, f, kh, kw, s, d, p  [n,c,ih,iw,f,kh,kw,oh,ow]
        model,input_dict = conv(op.dimension[0],op.dimension[1],op.dimension[2],op.dimension[3],
                                op.dimension[4],op.dimension[5],op.dimension[6],op.stride, op.dilation, op.pad)
    else:
        # TODO other op for profile
        return
    model.eval()   
    torch2mlir(op_path, model, input_dict)
    
    export_benchmark = f"iree-compile  {op_path}/model.mlir --iree-hal-target-backends=cuda  \
    --iree-flow-export-benchmark-funcs  --iree-hal-dump-executable-benchmarks-to={op_path}  -o /dev/null"
    subprocess.run(export_benchmark, shell=True, check=True)





def move_file(source_file,destination_folder):

    # 如果目标文件夹不存在，创建它
    if not os.path.exists(destination_folder):
        os.makedirs(destination_folder)

    # 获取文件名
    file_name = os.path.basename(source_file)

    # 目标文件路径
    destination_file = os.path.join(destination_folder, file_name)

    # 移动文件
    shutil.move(source_file, destination_file)

    print(f"文件已移动到 {destination_file}")