module NEAT

using GLMakie
using Graphs
using GraphMakie
#using GraphRecipes
using Plots
import Base: isless
import GraphMakie: graphplot
export Individual, run_network, graphplot


sigmoid(x) = 2.0/(1+exp(-4.9*x))-1

population_size = 196
weight_min = -20.0
weight_max = 20.0

@enum Node_Type input hidden bias output

mutable struct Node
    id::Int
    type::Node_Type
    layer::Int
    value::Float32
end

mutable struct Connection
    innovation_id::Int
    left_node_id::Int
    right_node_id::Int
    weight::Float32
    enabled::Bool
    Connection(left_node_id, right_node_id, weight, enabled) =
        new(get_innovation(left_node_id, right_node_id),left_node_id, right_node_id, weight, enabled)
end


struct Individual
    nodes::Vector{Node}
    connections::Vector{Connection}
end

get_innovation(left_node_id::Int, right_node_id::Int) = left_node_id * 100000 + right_node_id

# make Node  sortable - first sort by layer, then by id
isless(a::Node, b::Node) = a.layer < b.layer || (a.layer == b.layer && a.id < b.id)
# make Connection  sortable - first sort by left node, then by tight node
isless(a::Connection, b::Connection) = a.left_node_id < b.left_node_id || (a.left_node_id == b.left_node_id && a.right_node_id < b.right_node_id)

# generate a new random individual
function Individual(input_n::Int, output_n::Int, hidden_n::Int = 0, connectivity = 0.05)
    # generate initial nodes
    nodes = []
    has_hidden = false
    for id in 1:input_n
        push!(nodes, Node(id, input, 0, 0))
    end
    for id in 1+input_n:input_n+hidden_n
        has_hidden = true
        push!(nodes, Node(id, hidden, 1, 0))
    end
    for id in 1+input_n+hidden_n:input_n+hidden_n+output_n
        push!(nodes, Node(id, output, 1+Int(has_hidden), 0))
    end
    # generate initial connections
    connections = Connection[]
    for node_a in nodes
        for node_b in nodes
            if(node_a.layer < node_b.layer && rand() < connectivity)
                #availible for connection
                push!(connections, Connection(
                    node_a.id, node_b.id, (weight_max - weight_min)*rand() + weight_min, true))
            end
        end
    end
    return Individual(sort(nodes), sort(connections))
end


# runs the network with given input vector
# assumes that both - connections and nodes are sorted!
function run_network( (; nodes, connections)::Individual, inputs::Vector)
    connection_index = 1
    node_index = 1
    weighted_sum_cache = zeros(Float32,length(nodes))
    result = []
    # forward propagate through the network
    while(node_index <= length(nodes))
        node = nodes[node_index]
        if(node.type == input) # input node? copy input from input vector over
            node.value = inputs[node_index]
        elseif(node.type != bias) # get the input value of our node from the cache
            node.value = sigmoid(weighted_sum_cache[node.id])
        end
        # do we have outgoing connections from our node?
        # if yes, add to input of other node
        while(connection_index <= length(connections) && node.id == connections[connection_index].left_node_id)
            if(connections[connection_index].enabled)
                weighted_sum_cache[connections[connection_index].right_node_id] +=
                    connections[connection_index].weight * node.value
            end
            connection_index+=1
        end
        # are we a output node?
        if(node.type == output)
            push!(result, node.value > 0)
        end
        node_index+=1
    end
    return result
end

function graphplot(individual::Individual)
    # create graph
    labels = String[]
    graph = DiGraph(filter(
        edge -> edge!=nothing,
        map(connection -> if (connection.enabled)
                push!(labels, string(connection.weight))
                Edge(connection.left_node_id, connection.right_node_id)
            else
                nothing
            end,
            individual.connections)))
    # set graph layout, names
    fixed_layout(_), names = let # nice way to "hide" "dirty" code :p
        layout = []
        names = String[]
        current_y = 0
        current_x = 0
        output_x = 0
        sort!(individual.nodes)
        for node_index in 1:length(individual.nodes)
            node = individual.nodes[node_index]
            # check if we change layer
            if (node.layer > current_x)
                current_x = node.layer
                current_y = 0;
            end
            # if we don't have connections we teleport the nodes to nirvana
            if(node.id <= nv(graph) && length(all_neighbors(graph,vertices(graph)[node_index])) == 0) # node has no connections
                push!(layout, (-1,1))
                push!(names, "unused")
            else
                current_y +=1
                push!(layout, ((output_x == 0 ? current_x : output_x)*1.5, current_y))
                push!(names, string(node_index))
            end
        end
        layout, names
    end
    # plot graph
    graphplot(graph, curves=false, nlabels=names,nodesize=1,fontsize=10,nodecolor=3,layout = fixed_layout, elabels = labels, elabels_textsize = 10)
end


end