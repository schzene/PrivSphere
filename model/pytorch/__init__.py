import numpy as np
import torchvision
import torch

# ---------------------------------------------------------------------
# single op
# ---------------------------------------------------------------------

def conv(n, c, h, w, f, kh, kw, s, d, p):
    from .convchain import Conv
    model = Conv(c, f, kh, kw, s, d, p)
    input = torch.randn(n, c, h, w)
    return model, (input,)

def matmul(batch,m,k,n):
    from .convchain import LinearModel
    model = LinearModel(k,n)
    input = torch.randn(batch, m, k)
    return model, (input,)


c_lists = [
    # ('C0', conv, [128, 128, 28, 28, 128, 3, 3, 1, 1, 1]),
    ('C1', conv, [1, 3, 224, 224, 64, 11, 11, 4, 1, 2]),
    # ('C2', conv, [128, 256, 14, 14, 256, 3, 3, 2, 1, 0]),
    # ('C3', conv, [128, 168, 42, 42, 168, 1, 1, 1, 1, 0]),

]

m_lists = [
    # bert
    ('M1', matmul, [12, 128, 128, 64]),
    # ('M2', matmul_nn, [128, 3072, 768], [[32, 8, 1],[32, 128, 32]]),
    # ('M3', matmul_nn, [128, 768, 768],  [[32, 8, 1],[32, 128, 32]]),
    # ('M4', matmul_nn, [128, 2304, 768], [[32, 8, 1],[32, 128, 32]]),
    # ('M5', matmul_nt, [128, 64, 128],   [[16, 8, 1],[128, 64, 8]]),
    # ('M6', matmul_nt, [128, 128, 64],   [[32, 8, 1],[32, 128, 32]]),
  
    # Nerf
    # ('M0', matmul_nn, [1, 512, 1000]),
    # ('M0', matmul, [1, 65536, 2, 1024]),
    # ('M1', matmul, [1, 128, 4032, 1000]),
    # ('M2', matmul, [1, 128, 2048, 1000]),
    # ('M3', matmul, [1, 65536, 1024, 4096]),
    # ('M4', matmul, [1, 65536, 1024, 1024]),
    # ('M5', matmul, [1, 65536, 4096, 1024]),
    # ('M6', matmul, [1, 65536, 30522, 1024]),
    # ('M7', matmul, [1, 3, 2, 4]),
    # ('bert_mat14', matmul, [1, 128, 3072, 768]),
    # ('mat_relu', matmul, [1, 128, 3072, 768]),
    # ('bert_1', matmul, [1, 128, 3072, 768]),
    # ('mat_relu', matmul, [1, 128, 3072, 768]),
    # ('mat_relu', matmul, [1, 128, 3072, 768]),
    # ('mat_relu', matmul, [1, 128, 3072, 768]),
    # ('mat_relu', matmul, [1, 128, 3072, 768]),


]



# ---------------------------------------------------------------------
# subgraph
# ---------------------------------------------------------------------
def softmaxchain(batch_size):
    from .subgraph import Softmaxchain
    model = Softmaxchain()
    q = torch.randn(12, 128, 64, dtype=torch.float32)
    k = torch.randn(12, 64, 128, dtype=torch.float32)
    v = torch.randn(12, 128, 64, dtype=torch.float32)
    attention_mask = torch.randn(1, 1, 1,128, dtype=torch.float32)
    return model, (q,k,v, attention_mask)


def convchain(batch_size):
    from .convchain import Convchain
    model = Convchain()
    input = torch.randn(batch_size, 3, 224, 224)
    return model, (input,)


def layernorm(batch_size):
    from .subgraph import LayerNorm
    model = LayerNorm()
    input = torch.randn(batch_size,128,768)
    return model, (input,)






# ---------------------------------------------------------------------
# model
# ---------------------------------------------------------------------

def alexnet(batch_size):
    from torchvision.models import alexnet as Net
    model = Net()
    input = torch.randn(batch_size, 3, 224, 224)
    return model,(input,)

def resnet18(batch_size):
    from torchvision.models import resnet18 as Net
    model = Net()
    input = torch.randn(batch_size, 3, 224, 224)
    return model, (input, )

def resnet50(batch_size):
    from torchvision.models import resnet50 as Net
    model = Net()
    input = torch.randn(batch_size, 3, 224, 224)
    return model, (input, )

def vgg16(batch_size):
    from torchvision.models import vgg11 as Net
    model = Net()
    input = torch.randn(batch_size, 3, 224, 224)
    return model, (input, )

def unet(batch_size):
    from .unet import UNet as Net
    model = Net(3, 100)
    input = torch.randn(batch_size, 3, 224, 224)
    return model, (input, )

def mobilenet(batch_size):
    from torchvision.models import mobilenet_v2 as Net
    model = Net()
    input = torch.randn(batch_size, 3, 224, 224)
    return model, (input, )

def swin_transformer(batch_size):
    from timm.models.swin_transformer import SwinTransformer
    model = SwinTransformer()
    input = torch.randn(batch_size, 3, 224, 224)
    return model, (input, )


def bertlayer(batch_size):
    from .bert_config import BertConfig
    from .pytorch_bert import BertModel,BertLayer

    config = BertConfig(vocab_size=30522,
        hidden_size=768,
        num_hidden_layers=1,
        num_attention_heads=12,
        intermediate_size=3072,
        max_position_embeddings=128,
        attention_probs_dropout_prob=0.1,
        hidden_dropout_prob=0.1,
        batch_size=batch_size)
    model = BertLayer(config)
    input1 = torch.ones(1,128,768,dtype=torch.float32)
    input2 = torch.ones(1,1,1,128,dtype=torch.float32)
    
    # shapetorch.Size([1, 128, 768]) torch.float32
    # shapetorch.Size([1, 1, 1, 128]) torch.float32
    inputs = (input1,input2)
    
    return model, inputs   

def bertselfattention(batch_size):
    from .bert_config import BertConfig
    from .pytorch_bert import BertSelfAttention

    config = BertConfig(vocab_size=30522,
        hidden_size=768,
        num_hidden_layers=1,
        num_attention_heads=12,
        intermediate_size=3072,
        max_position_embeddings=128,
        attention_probs_dropout_prob=0.1,
        hidden_dropout_prob=0.1,
        batch_size=batch_size)
    model = BertSelfAttention(config)
    input1 = torch.ones(1,128,768,dtype=torch.float32)
    input2 = torch.ones(1,1,1,128,dtype=torch.float32)

    inputs = (input1,input2)
    
    return model, inputs   


def bert(batch_size):
    from .bert_config import BertConfig
    from .pytorch_bert import BertModel

    # from transformers import BertConfig, BertModel
    config = BertConfig(vocab_size=30522,
                hidden_size=768,
                num_hidden_layers=12,
                num_attention_heads=12,
                intermediate_size=3072,
                max_position_embeddings=128,
                attention_probs_dropout_prob=0.1,
                hidden_dropout_prob=0.1,
                batch_size=batch_size)
    model = BertModel(config)
    input_ids = torch.LongTensor(np.ones([config.batch_size, config.max_position_embeddings]))
    token_type_ids = torch.LongTensor(np.ones([config.batch_size, config.max_position_embeddings]))
    attention_mask = torch.LongTensor(np.ones([config.batch_size, config.max_position_embeddings]))
    masked_lm_labels = None # torch.LongTensor(np.ones([config.batch_size, config.max_position_embeddings]))
    next_sentence_label = None # torch.LongTensor(np.ones([config.batch_size]))
    inputs = (input_ids, attention_mask, token_type_ids)
    # inputs = (input_ids, token_type_ids, attention_mask, masked_lm_labels, next_sentence_label)
    return model, inputs

def bert_v0(batch_size):
    from transformers import BertConfig, BertModel
    config = BertConfig(vocab_size=30522,
                hidden_size=768,
                num_hidden_layers=1,
                num_attention_heads=12,
                intermediate_size=3072,
                max_position_embeddings=128,
                attention_probs_dropout_prob=0.1,
                hidden_dropout_prob=0.1,
                batch_size=batch_size)
    model = BertModel(config)
    input_ids = torch.LongTensor(np.ones([config.batch_size, config.max_position_embeddings]))
    token_type_ids = torch.LongTensor(np.ones([config.batch_size, config.max_position_embeddings]))
    attention_mask = torch.LongTensor(np.ones([config.batch_size, config.max_position_embeddings]))
    masked_lm_labels = None # torch.LongTensor(np.ones([config.batch_size, config.max_position_embeddings]))
    next_sentence_label = None # torch.LongTensor(np.ones([config.batch_size]))
    inputs = (input_ids, attention_mask, token_type_ids)
    # inputs = (input_ids, token_type_ids, attention_mask, masked_lm_labels, next_sentence_label)
    return model, inputs

def vit(batch_size):
    from timm.models import vit_small_patch32_224 as Net
    model = Net()
    input = torch.randn(batch_size, 3, 224, 224)
    return model, (input, )

def BSRN(batch_size):
    from .BSRN import BSRN
    model = BSRN()
    input = torch.randn(batch_size, 3, 256, 256)
    return model, (input, )

def NAFNet(batch_size):
    from .nafnet import NAFNet
    model = NAFNet(3, 16, 1, [1, 1, 1], [1, 1, 1])
    input = torch.randn(batch_size, 3, 256, 256)
    return model, (input, )

def Restormer(batch_size):
    from .restormer import Restormer
    model = Restormer()
    input = torch.randn(batch_size, 3, 256, 256)
    return model, (input, )

def mobilevit(batch_size):
    from .mobilevit import mobilevit_s
    model = mobilevit_s()
    input = torch.randn(batch_size, 3, 256, 256)
    return model, (input, )

def NeRF(batch_size):
    from .mlp import MLP
    model = MLP(batch_size=512*512, in_dim=64, out_dim=3, hidden_dim=64, n_layers=7)
    input = torch.randn(512*512, 64)
    return model, (input, )

def Conformer(batch_size):
    # from torchaudio.models import Conformer # use the next line if torchaudio doesn't works
    from .Conformer import Conformer
    num_frame = 512
    input_dim = 512
    model = Conformer(input_dim=input_dim, num_heads=8, ffn_dim=512, num_layers=12, depthwise_conv_kernel_size=31)
    lengths = torch.LongTensor([num_frame for _ in range(batch_size)])
    input = torch.randn(batch_size, num_frame, input_dim)
    return model, (input, lengths)


if __name__=="__main__":
    model,input = NeRF(1)
    print(model(input))
    pass