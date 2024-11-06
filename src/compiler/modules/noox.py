
import onnx
import networkx as nx

def parse_onnx_model(model_path):

    model = onnx.load(model_path)
    graph = model.graph
    

    G = nx.DiGraph()
    G.add_node("input", op_type="input", inputs=[], outputs=graph.input)
    G.add_node("output", op_type="output", inputs=graph.output, outputs=[])


    for node in graph.node:


        print("Node name:", node.name)
        # print("Op type:", node.op_type)
        print("Inputs:", node.input) 
        print("Outputs:", node.output)
        # print("Attributes:", node.attribute)
        print()

        if "Constant" in node.name:
            continue

        G.add_node(node.name, op_type=node.op_type, inputs=node.input, outputs=node.output)


        for input_name in node.input:
            if ('weight' in input_name or 'bias' in input_name):
                continue
            G.add_edge(input_name, node.name)
        for output_name in node.output:
            G.add_edge(node.name, output_name)
        

    all_nodes = list(G.nodes)
    
    for node in all_nodes:
        if 'output' in node and 'output' != node:
            for input_node in G.predecessors(node):
                for output_node in G.successors(node):
                    G.add_edge(input_node, output_node)
            G.remove_node(node)
    return G


import matplotlib.pyplot as plt
G = parse_onnx_model("modules/model.onnx")
nx.draw(G, with_labels=True)
# plt.show()
plt.savefig("modules/demo.png")