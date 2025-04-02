

import torch
from enum import Enum
import os
from pytorch import *
import torch_mlir.fx
import torch.nn as nn

import torch_mlir
import torch_mlir.tools


class LinearModel(nn.Module):
    def __init__(self,k,n):
        super(LinearModel, self).__init__()
        self.linear = nn.Linear(k,n)


    def forward(self, x):
        return self.linear(x)
    

    

class OutTypeEnum(Enum):
    linalg = "linalg"
    tosa = "tosa"
    torch= "torch"


def nisl_compile_import(
    model: torch.nn.Module,
    input_tensor,
    out_name,  # model  or single op name for output
    mlir_type=OutTypeEnum.linalg,
    fix_param=True,
):
    model.eval()

    # default
    if not os.path.exists(".logs"):
        os.makedirs(".logs")
    # output type
    mlir_output_type = "Tosa"
    if mlir_type == OutTypeEnum.linalg:
        mlir_output_type = "linalg-on-tensors"
    # out file
    mlir_file_name = f"{out_name}_{mlir_type.value}_{fix_param}.mlir"
    # fixed params
    if fix_param is True:
        for param in model.parameters():
            param.data.fill_(3)
    else:
        # create log dir for model with weights
        mlir_file_name = ".logs/" + mlir_file_name
    # pytorch test result


    module = torch_mlir.fx.export_and_import(model, input_tensor, output_type=mlir_output_type)
    
    # print("TORCH OutputType\n", module.operation.get_asm(large_elements_limit=10))

    # module = torchscript.compile(resnet18, torch.ones(1, 3, 224, 224), output_type="tosa")
    # print("TOSA OutputType\n", module.operation.get_asm(large_elements_limit=10))


    # mlir_str = str(module).replace("maximumf", "maxf")  #for old version
    mlir_str = str(module)

    with open(mlir_file_name, "w", encoding="utf-8") as outf:
        outf.write(mlir_str)
    # netron.start(".logs/model.onnx")


def default_eg():
    prefix = "../temp2/"
    torch.random.manual_seed(0)

    model,input = resnet18(1)

    input = torch.ones(1, 3, 224, 224)

    module = torch_mlir.fx.export_and_import(model, input, output_type="linalg-on-tensors")
    
    mlir_str = str(module)

    with open("resnet", "w", encoding="utf-8") as outf:
        outf.write(mlir_str)



if __name__ == "__main__":
    model,inputs = convchain(1)
    model.eval()
    print(inputs[0])
    module = torch_mlir.fx.export_and_import(model, inputs[0], output_type="linalg-on-tensors")