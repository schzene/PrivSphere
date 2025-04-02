import torch.nn as nn
import torch
import torch.nn.functional as F


class ConvPooling(nn.Module):
    def __init__(self):
        super(ConvPooling, self).__init__()
        self.layer = nn.Sequential(
            nn.Conv2d(in_channels=3, out_channels=64, kernel_size=3, stride=1, padding=1),  # Conv2d Layer
            nn.ReLU(),  # ReLU Activation
            nn.MaxPool2d(kernel_size=2, stride=2, padding=0)  # MaxPool Layer
        )
    
    def forward(self, x):
        return self.layer(x)


class LayerNorm(nn.Module):
    def __init__(self) -> None:
        super().__init__()
        self.LayerNorm = nn.LayerNorm(768, eps=1e-12)

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        return self.LayerNorm(x)
    


class Softmaxchain(nn.Module):
    def __init__(self) -> None:
        super().__init__()

     
    def forward(self, q: torch.Tensor , k: torch.Tensor ,v: torch.Tensor, attention_mask: torch.Tensor) -> torch.Tensor:
        attention_scores = torch.matmul(q, k)
        attention_scores = attention_scores / 8

        # Apply the attention mask is (precomputed for all layers in BertModel forward() function)
        attention_scores = attention_scores + attention_mask

        # Normalize the attention scores to probabilities.
        attention_probs = F.softmax(attention_scores, dim=-1)

        context_layer = torch.matmul(attention_probs, v)
        return context_layer
    

