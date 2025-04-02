
import os
import import_suite
import subprocess
from pytorch import *
import os.path as osp
import onnx
from onnx import version_converter, helper





def torch2onnx(path, model, inputs,version=11):
    print(f"process model in : {path} ")
    outputs = model(*inputs)
    if not isinstance(outputs, (tuple, list)):
        outputs = (outputs, )
    input_names = ["input"+str(i) for i in range(len(inputs))]
    output_names = ["output"+str(i) for i in range(len(outputs))]
    torch.onnx.export(
        model, inputs,
        osp.join(path, "model.onnx"),
        input_names=input_names,
        output_names=output_names,
        export_params=True,
        training=torch.onnx.TrainingMode.EVAL,
        do_constant_folding=False,
        opset_version=version)
    return


def torch2mlir(path, model, input ,name="model.mlir",target = "linalg-on-tensors"):
    from torch_mlir import fx
    print(f"process model in : {path} ")
    module = fx.export_and_import(model, *input, output_type = target)
    mlir_str = str(module)
    
    with open(osp.join(path, name), "w", encoding="utf-8") as outf:
        outf.write(mlir_str)
    return 


def onnx2mlir(model_path, new):
    
    mp = osp.join(model_path, "model.onnx")
    original_model = onnx.load(mp)
    converted_model = version_converter.convert_version(original_model, new)
    converted_model.graph.name= "main"
    new_onnx_path = osp.join(model_path, f"model_{new}.onnx")
    onnx.save(converted_model, new_onnx_path)
    # import to mlir
    export_mlir = f"iree-import-onnx  {new_onnx_path} -o {model_path}/model.mlir"
    subprocess.run(export_mlir, shell=True, check=True)
                
    return 



if __name__ == "__main__":
    prefix = "/root/Documents/Projects/PrivSphere/out/"
    torch.random.manual_seed(0)
    
    
    for model, bs, tp in import_suite.model_dirs:
        assert (model in globals()), "Model {} not found.".format(model)
        
        for b in bs:
            for t in tp:
                suffix = str(b) + ("_fp16" if t == "fp16" else "")
                model_path = osp.join(prefix, model, suffix)
                os.makedirs(model_path, exist_ok=True)
                modelt, inputs = globals()[model](b)
                modelt.eval()
                torch2onnx(model_path, modelt, inputs)
                torch2mlir(model_path, modelt, inputs, target = "tosa")
                # onnx2mlir(model_path,17)






