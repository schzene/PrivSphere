
import onnx
import networkx as nx

def parse_onnx_model(model_path):

    model = onnx.load(model_path)
    graph = model.graph
    

    G = nx.DiGraph()


    for node in graph.node:


        print("Node name:", node.name)
        print("Op type:", node.op_type)
        print("Inputs:", node.input) 
        print("Outputs:", node.output)
        print("Attributes:", node.attribute)

        G.add_node(node.name, op_type=node.op_type, inputs=node.input, outputs=node.output)


        for input_name in node.input:
            G.add_edge(input_name, node.name)
        # for output_name in node.output:
        #     G.add_edge(output_name, node.name)

    return G


import matplotlib.pyplot as plt
G = parse_onnx_model("/home/PrivaSphere/src/compiler/modules/model.onnx")
nx.draw(G, with_labels=True)
# plt.show()
plt.savefig("demp.png")