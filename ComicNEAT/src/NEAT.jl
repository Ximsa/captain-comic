module NEAT

using GLMakie
using Graphs
using GraphMakie
#using GraphRecipes
using Plots
using StatsBase
using LayeredLayouts
import Base: isless
import Base: show
import Base: sort
import GraphMakie: graphplot
export run_network, graphplot, Population


# helper
sigmoid(x) = 2.0/(1+exp(-4.9*x))-1

# structs
@enum Node_Type input hidden bias output

mutable struct Node
    rank::Int
    type::Node_Type
    value::Float32
end

mutable struct Connection
    innovation_id::Int
    left_node_id::Int
    right_node_id::Int
    weight::Float32
    enabled::Bool
    function Connection(setting, left_node_id, right_node_id, weight, enabled)
        innovation_id = 0
        if(haskey(setting.innovation_lookup, Pair(left_node_id,right_node_id))) # use existing id
            innovation_id = setting.innovation_lookup[Pair(left_node_id,right_node_id)]
        else # generate new innovation id
            setting.innovation_counter += 1
            innovation_id = setting.innovation_lookup[Pair(left_node_id,right_node_id)] = setting.innovation_counter
        end
        return new(innovation_id, left_node_id, right_node_id, weight, enabled)
    end
end


mutable struct Individual
    fitness::Float32
    nodes::Vector{Node}
    connections::Vector{Connection}
end

mutable struct Species
    best_fitness::Float32
    n_offspring::Int
    gens_since_improved::Int
    individuals::Vector{Individual}
    Species(n_offspring, gens_since_improved, individuals) = new(0, n_offspring, gens_since_improved, individuals)
end

mutable struct Setting
    innovation_counter::Int
    innovation_lookup::Dict{Pair{Int,Int},Int}
    population_size::Int
    weight_range::Float32
    species_threshold::Float32
    target_species::Int
    connectivity::Float32
    input_n::Int
    output_n::Int
    weight_mutation::Float32
    connection_mutation::Float32
    node_mutation::Float32
end

mutable struct Population
    setting::Setting
    species::Vector{Species}
    function Population(input_nodes, output_nodes,
                        population_size=192, weight_range=20.0,
                        weight_mutation=0.5, connection_mutation=0.05, node_mutation=0.05)
        connectivity = 1.0/sqrt(input_nodes)
        target_species = Int(floor(sqrt(population_size/2)))
        # create setting struct
        setting = Setting(0,Dict(),population_size,weight_range,10.0,
                          target_species, connectivity, input_nodes, output_nodes,
                          weight_mutation, connection_mutation, node_mutation)
        # generate individuals from setting
        individuals = map(x -> Individual(setting),
                          1:population_size)
        species = [Species(0, 0, individuals)] # start with 1 species
        return new(setting, species)
    end
end

#external constructors

# generate a new random individual
function Individual(setting::Setting)
    # generate initial nodes and connections
    nodes = []
    connections = Connection[]
    first = true
    for id in 1:setting.input_n
        push!(nodes, Node(id, input, 0))
        if(rand() < setting.connectivity || first)
            first=false
            # add connection from id to random output node
            push!(connections, Connection(
                setting, id, sample(1+setting.input_n:setting.input_n+setting.output_n),
                (2*setting.weight_range)*rand() - setting.weight_range, true))
        end
    end
    for id in 1+setting.input_n:setting.input_n+setting.output_n
        push!(nodes, Node(id, output, 0))
    end
    return sort(Individual(floor(100*rand()),nodes,connections))
end

# overrides
Base.show(io::IO, x::Individual) = print("Fitness:\t", x.fitness,
                                         "\n# nodes:\t", length(x.nodes),
                                         "\n# connections:\t", length(x.connections), "\n")
Base.show(io::IO, x::Species) = print("# individuals:\t", length(x.individuals),
                                      "\n# offsprings:\t", x.n_offspring,
                                      "\nnot improved since ", x.gens_since_improved, " generations\n")
# make Node sortable - sort by id
isless(a::Node, b::Node) = a.id < b.id

# make Individual topological sortable
# sets rank in nodes
function sort(individual::Individual)
    nodes = individual.nodes
    connections = individual.connections
    # based upon Kahn's algorithm / countingsort
    max_node_id = maximum(map(c -> c.left_node_id > c.right_node_id ? c.left_node_id : c.right_node_id, connections))
    # first group connections by left node id
    # and count how many incoming connections each node has
    neighbours = map(x -> [], 1:max_node_id)
    counts = zeros(Int, max_node_id)
    for connection in connections
        push!(neighbours[connection.left_node_id], connection)
        counts[connection.right_node_id]+=1
    end
    # now push all nodes with no incoming nodes on the stack
    rank = 0
    stack = []
    new_connections = []
    for i = 1:max_node_id
        if(counts[i] == 0)
            push!(stack, i)
        end
    end
    # now the actual algorithm: while the stack is not empty pop an element
    # and decrement the neighbour's count.
    # if the neighbour's count reaches zero, push that connection on the stack
    while(!isempty(stack))
        node_id = pop!(stack)
        nodes[node_id].rank = rank
        rank+=1
        for neighbour in neighbours[node_id]
            push!(new_connections, neighbour)
            counts[neighbour.right_node_id]-=1
            if(counts[neighbour.right_node_id] == 0)
                push!(stack, neighbour.right_node_id)
            end
        end
    end
    individual.connections = new_connections
    return individual
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
    xs, ys, paths = solve_positions(Zarate(), graph);
    # plot graph
    lay = _ -> Point.(zip(xs,ys))
    graphplot(graph, layout=lay, nlabels=map(string,1:length(individual.nodes)))
end

# runs the network with given input vector
# assumes that connections are topological sorted
function run_network( (;fitness, nodes, connections)::Individual, inputs::Vector, n_outputs)
    # keep track of when to trigger activation function
    visited = zeros(Bool,length(nodes))
    # copy inputs over
    for i in 1:length(inputs)
        nodes[i].value = inputs[i]
        visited[i] = true
    end
    # propagate through the network
    for connection in connections
        if(connection.enabled)
            if(!visited[connection.left_node_id])
                nodes[connection.left_node_id].value = sigmoid(nodes[connection.left_node_id].value)
                visited[connection.left_node_id] = true
            end
            nodes[connection.right_node_id].value += nodes[connection.left_node_id].value * connection.weight
        end
    end
    # read output nodes
    return map(x -> sigmoid(x.value) > 0, nodes[length(inputs)+1:length(inputs)+n_outputs])
end

# excess connections + disjoint connections + average weight difference
# assumes sorted by innovation id!!
function distance(a::Individual, b::Individual)
    as = a.connections
    bs = b.connections
    ai = bi = 1
    exess=0
    disjoint=0
    weight_sum=0
    weight_count=1 # prevents div by 0
    while(ai <= length(as) && bi <= length(bs)) # iterate through the arrays
        #if a connection is disabled: skip
        if(!as[ai].enabled)
            ai+=1
            continue
        end
        if(!bs[bi].enabled)
            bi+=1
            continue
        end
        #compare innovation id's
        if(as[ai].innovation_id == bs[bi].innovation_id) # same innovation id's, weight
            weight_sum+=abs(as[ai].weight - bs[bi].weight)
            ai+=1
            bi+=1
        elseif(as[ai].innovation_id < bs[bi].innovation_id) # a < b
            disjoint+=1
            ai+=1
        else # b < a
            disjoint+=1
            bi+=1
        end
    end
    # count excess id's
    excess = (length(as)-ai+1)+(length(bs)-bi+1)
    N = length(as) > length(bs) ? length(as) : length(bs)
    return 1*excess/N+1*disjoint/N+0.4*weight_sum/weight_count
end

function speciate(population::Population)
    # repartition species: select random representant from each species
    representants = map(
        function(individual) # sort connections
            sort!(individual.connections, by=connection->connection.innovation_id)
            return individual
        end,
        map(x->sample(x.individuals), population.species))
    # flatten population list and sort connections by innovation id
    individuals = map(
        function(individual) # sort connections
            sort!(individual.connections, by=connection->connection.innovation_id)
            return individual
        end,
        vcat(map(x->x.individuals, population.species)...)) # flatten population
    # reset specification
    for species in population.species
        species.individuals = []
    end
    # assign each individual to a species
    for individual in individuals
        distances = map(representant -> let
                            d=distance(individual, representant)
                            d==0 ? population.setting.species_threshold : d
                        end,
                        representants)
        if(min(distances...) > population.setting.species_threshold) # create new species
            push!(population.species, Species(0,0,[individual]))
            push!(representants, individual)
        else # append to existing species
            push!(population.species[argmin(distances)].individuals, individual)
        end
    end
    # delete empty species
    filter!(species -> !isempty(species.individuals), population.species)
    # recalculate species_threshold
    population.setting.species_threshold += length(population.species) - population.setting.target_species > 0 ? 0.3 : -0.3
end

function survivor_selection(population::Population)
    # crossover preparation
    # calculate adjusted fitness for each individual
    # adj. fitness = fitness/spezies size
    sum_fitness = 0
    n_fitness = 0
    species_fitness = zeros(Float32,length(population.species))
    for species_id in 1:length(population.species)
        size=length(population.species[species_id].individuals)
        n_fitness += size
        for individual in population.species[species_id].individuals
            if(individual.fitness > population.species[species_id].best_fitness)
                population.species[species_id].best_fitness = individual.fitness
                population.species[species_id].gens_since_improved = 0
            end
            individual.fitness /= size
            # prefer growing individuals
            individual.fitness /= 1+(population.species[species_id].gens_since_improved / 12.0)
            sum_fitness += individual.fitness
            species_fitness[species_id] += individual.fitness
        end
        species_fitness[species_id] /= size
    end
    average_fitness = sum_fitness / n_fitness
    total_offsprings = 0
    # determine allowed offspring count
    for species_id in 1:length(population.species)
        offspring_count = floor(length(population.species[species_id].individuals) * species_fitness[species_id] / average_fitness)
        population.species[species_id].n_offspring = offspring_count
        total_offsprings+=offspring_count
    end
    # incase there are not enough offsprings add the dividend to a random species
    divident = population.setting.population_size - total_offsprings
    if(divident > 0)
        population.species[sample(1:length(population.species))].n_offspring += divident
    end
end

# combine 2 individuals into one, keep disjunct and excess genes from the better performer
function crossover(a::Individual, b::Individual)
    a, b = a.fitness > b.fitness ? (a, b) : (b, a)
    result = deepcopy(a)
    as = a.connections
    bs = b.connections
    ai = 0
    bi = 0
    while(ai <= length(as) && bi <= length(bs)) # iterate through the arrays
        #compare innovation id's
        if(as[ai].innovation_id == bs[bi].innovation_id) # same innovation id's, weight
            weight_sum+=abs(as[ai].weight - bs[bi].weight)
            result.connections[ai].weight = sample([as[ai].weight, bs[bi].weight])
            ai+=1
            bi+=1
        elseif(as[ai].innovation_id < bs[bi].innovation_id) # a < b
            ai+=1
        else # b < a
            bi+=1
        end
    end
    return result
end

# mutates an individual
function mutate(individual::Individual, weight_mutation::Float32, )
    # mutate weights - % change, 
end

# performs roulette wheel selection for crossover for each species
function perform_crossover_and_mutation(population::Population)
    for kind in population.species
        weights = Weights(map(individual->individual.fitness, kind.individuals))
        individuals = kind.individuals
        next_individuals = []
        for i in 1:kind.n_offspring
            push!(next_individuals, mutate(crossover(sample(individuals, weights, 2)...)))
        end
        kind.individuals = next_individuals
    end
end

# creates the next generation based on the fitness of the last one
function next_generation(population::Population)
    speciate(population) # (re-)categorize population into species, also sorts connections by innovation
    survivor_selection(population) # select how many "survive" in each species
    # now we know the number of offsprings per species
    perform_crossover_and_mutation(population)
    # increment gens_since_improved
    for kind in population.species
        kind.gens_since_improved+=1
    end
end
end

