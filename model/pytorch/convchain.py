
import torch
import torch.nn as nn
import sys

class Conv(nn.Module):
    def __init__(self,c, f, kh, kw, stride,dilation, pad) -> None:
        super().__init__()
        self.features = nn.Sequential(
            nn.Conv2d(c, f, kernel_size=(kh,kw), stride=stride,dilation=dilation ,padding=pad,bias=False)
        )

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        x = self.features(x)
        return x


class LinearModel(nn.Module):
    def __init__(self,k,n):
        super(LinearModel, self).__init__()
        self.linear = nn.Linear(k, n, bias=False)

    def forward(self, x):
        return torch.relu(self.linear(x))






class Convchain(nn.Module):
    def __init__(self) -> None:
        super().__init__()
        self.features = nn.Sequential(
            nn.Conv2d(3, 64, kernel_size=3, stride=1, padding=1),
            nn.ReLU(inplace=True),
            nn.MaxPool2d(kernel_size=2, stride=2,padding=0),
        )
        # self.avgpool = nn.AdaptiveAvgPool2d((6, 6))
        # self.classifier = nn.Sequential(
        #     nn.Dropout(p=dropout),
        #     nn.Linear(256 * 6 * 6, 4096),
        #     nn.ReLU(inplace=True),
        #     nn.Dropout(p=dropout),
        #     nn.Linear(4096, 4096),
        #     nn.ReLU(inplace=True),
        #     nn.Linear(4096, num_classes),
        # )

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        x = self.features(x)
        # for name, layer in self.features._modules.items():
        #     x = layer(x)
        #     if isinstance(x, torch.Tensor):  # 打印卷积层的输出shape
        #         print(f'Conv Layer: {name}, Output Shape: {x.shape}')
        # x = self.features(x)
        # x = self.avgpool(x)
        # x = torch.flatten(x, 1)
        # x = self.classifier(x)
        return x
    

