#module NEAT

export sigmoid



sigmoid(x) = 2.0/(1+exp(-4.9*x) - 1)

population_size = 196
weight_min = -20.0
weight_max = 20.0
const layer_input = 0
const layer_output = typemax(Int)

@enum Node_Type input hidden bias output

struct Node
    id::Int
    type::Node_Type
    layer::Int
    input::Float64
    output::Float64
end

struct Connection
    innovation_id::Int
    in_node_id::Int
    out_node_id::Int
    weight::Float64
    enabled::Bool
end

struct Individual
    nodes::Vector{Node}
    connections::Vector{Connection}
end

"""
    Individual(input_n, output_n, hidden_n = 0, connectivity = 0.2)

    Create a new Individual with given input and output nodes.
    Optionally set amount of hidden nodes and connectivity rate of nodes
"""
function Individual(input_n, output_n, hidden_n = 0, connectivity = 0.2)
    # generate initial nodes
    nodes = map(function(node_id)
                    return if (node_id <= input_n)
                        Node(node_id, input, layer_input, 0, 0)
                    elseif (node_id <= input_n + output_n)
                        Node(node_id, output, layer_output, 0, 0)
                    else
                        Node(node_id, hidden, 1, 0, 0)
                    end
                end,
                1:input_n+output_n+hidden_n)
    # generate initial connections
    
end
