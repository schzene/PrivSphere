

import os.path as osp
from pytorch import *

model_dirs = [


    # op chain
    # ["convchain", (1,), ("fp32", )],
    # ["layernorm", (1,), ("fp32", )],
    # ["resnet_conv", (1,), ("fp32", )],
    # ["conv_pooling", (1,), ("fp32", )],
    # ["softmaxchain", (1,), ("fp32",)],


    # # model benchmark
    # ["alexnet", (1, ), ("fp32", )],
    # ["vgg16", (1, ), ("fp32", )],
    #  ["NeRF", (1, ), ("fp32", )],
    # ["bert", (1, ), ("fp32", )],



    # ["bert_v0", (1, ), ("fp32", )],
    ["bertlayer", (1, ), ("fp32", )],


    # error 
    # ["swin_transformer", (1, ), ("fp32", )],
    # ["vit", (1, ), ("fp32", )],       
    # ["mobilenet", (1, ), ("fp32", )],  编译错误
    # ["resnet18", (1, ), ("fp32", )],  current version error

    # unused for now
    # ["resnet50", (1, 64), ("fp32", "fp16")],
    # ["mobilevit", (1, 64), ("fp32", "fp16")],
    # ["Conformer", (1, 64), ("fp32", "fp16")],
    # ["BSRN", (1, ), ("fp32", "fp16")],
    # ["restormer", (1, ), ("fp32", "fp16")],
    # ["NAFNet", (1, ), ("fp32", )], 
]


def generate_input_str(input_tensor):
    shape = 'x'.join(map(str, input_tensor.shape))  
    dtype = str(input_tensor.dtype).split('.')[-1]
    tp = dtype[0] + dtype[-2:]
    return f"--input={shape}x{tp}=2"




def get_sub_dirs(prefix):
    results = []
    model_strings = []
    input_tensor = []
    for model, bs, tp in model_dirs:
        assert (model in globals()), "Model {} not found.".format(model)
        for b in bs:
            for t in tp:
                suffix = str(b) + ("_fp16" if t == "fp16" else "")
                results.append(osp.join(prefix, model, suffix))
                model_strings.append(f"{model}_{b}_{t}")
                # input
                _, inputs = globals()[model](b)
                output_str = ' '.join(generate_input_str(input_tensor) for input_tensor in inputs)
                input_tensor.append(output_str)
    return results, model_strings, input_tensor



