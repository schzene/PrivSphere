# # import torch
# # import torch.nn as nn


# # class SimpleModel(nn.Module):
# #     def __init__(self, input_size, output_size):
# #         super(SimpleModel, self).__init__()
# #         self.linear1 = nn.Linear(input_size, output_size)
# #         self.linear2 = nn.Linear(input_size, output_size)
# #         self.softmax = nn.Softmax()
# #         self.layernorm = nn.LayerNorm(input_size)
# #         self.linear4 = nn.Linear(input_size, output_size)
# #         self.gelu = nn.GELU()
        

# #     def forward(self, x):
# #         out = self.linear1(x)
# #         out = self.softmax(out)
# #         out = self.layernorm(out)
# #         out = self.gelu(out)
# #         return out



# import torch
# import torch.nn as nn

# class MyModel(nn.Module):
#     def __init__(self, input_dim, hidden_dim, output_dim):
#         super().__init__()
#         self.linear1 = nn.Linear(input_dim, hidden_dim)
#         self.norm1 = nn.LayerNorm(hidden_dim)
#         self.linear2 = nn.Linear(hidden_dim, hidden_dim)
#         self.gelu = nn.GELU()
#         self.linear3 = nn.Linear(hidden_dim, output_dim)
#         self.softmax = nn.Softmax(dim=-1)

#     def forward(self, x):
#         out = self.linear1(x)
#         out = self.norm1(out)
#         residual = out
#         out = self.linear2(out)
#         out = self.gelu(out)
#         out += residual 
#         out = self.linear3(out)
#         out = self.softmax(out)
#         return out

# model = MyModel(10, 5)  



# import torch.onnx


# dummy_input = torch.randn(1, 10)  


# torch.onnx.export(model,  
#                   dummy_input, 
#                   "model.onnx",  
#                   verbose=True,  
#                   opset_version=11)  



import torch
import torch.nn as nn
import torch.onnx
import torch
import torch.nn as nn
import torch.onnx
import math

import logging
import warnings
# 自定义的GELU近似计算
def my_gelu(x):
    return 0.5 * x * (1 + torch.tanh(math.sqrt(2 / math.pi) * (x + 0.044715 * x**3)))


# def my_gelu(x):
#     return 0.5*x + 0.5*x**2

class ReLU(nn.Module):
    r"""
    Module that computes rectified linear unit (ReLU) activations element-wise.

    :math:`\text{ReLU}(x)= \max(0, x)`
    """

    def __init__(self, inplace=False):
        super().__init__()
        if inplace:
            logging.warning("CrypTen ReLU module does not support inplace computation.")

    def forward(self, x):
        return x.relu()

    @staticmethod
    def from_onnx(attributes=None):
        return ReLU()






class MyModel(nn.Module):
    def __init__(self, input_dim, hidden_dim, output_dim):
        super().__init__()
        self.fc1 = nn.Linear(input_dim, hidden_dim)
        self.norm1 = nn.LayerNorm(hidden_dim)
        self.fc2 = nn.Linear(hidden_dim, hidden_dim)
        self.fc3 = nn.Linear(hidden_dim, output_dim)
        self.relu = ReLU()

    def forward(self, x):
        out = self.fc1(x)
        out = self.norm1(out)
        residual = out
        out = self.fc2(out)
        out = my_gelu(out)  
        out += residual
        out = self.fc3(out)
        out = self.relu(out)  
        return out


model = MyModel(input_dim=10, hidden_dim=20, output_dim=5)


dummy_input = torch.randn(1, 10)


model.eval()


torch.onnx.export(model, dummy_input, "modules/model.onnx", verbose=True, input_names=["input"], output_names=["output"])