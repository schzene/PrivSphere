import os
from torch2mlir_model import torch2mlir,torch2onnx
from pytorch import *
import os.path as osp




def translate(model, input_dict, prefix ,name="test"):
    model_path = osp.join(prefix, name)
    os.makedirs(model_path, exist_ok=True)
    model.eval()
    # torch2onnx(model_path, model, input_dict)
    torch2mlir(model_path, model, input_dict)
    


if __name__ == "__main__":
    prefix = "../temp2/ops"
    test_list = m_lists
    # test_list = c_lists
    torch.random.manual_seed(0)
    
    for name, func, args in test_list:
        translate(*func(*args), prefix, name)




# def torch2onnx(path, model, inputs):
#     print(f"process ops in : {path} ")
#     outputs = model(*inputs)
#     if not isinstance(outputs, (tuple, list)):
#         outputs = (outputs, )
#     input_names = ["input"+str(i) for i in range(len(inputs))]
#     output_names = ["output"+str(i) for i in range(len(outputs))]
#     torch.onnx.export(
#         model, inputs,
#         osp.join(path, "model.onnx"),
#         input_names=input_names,
#         output_names=output_names,
#         export_params=True,
#         training=torch.onnx.TrainingMode.EVAL,
#         do_constant_folding=False,
#         opset_version=11)
#     return


# def torch2mlir(path, model, input ,target = "linalg-on-tensors"):
#     print(f"process model in : {path} ")
#     module = torch_mlir.fx.export_and_import(model, *input, output_type = target)
#     mlir_str = str(module)
    
#     with open(osp.join(path, "model.mlir"), "w", encoding="utf-8") as outf:
#         outf.write(mlir_str)
#     return 





