
# !assumes working directory set to project directory!

if(length(filter(x -> x=="ComicNEAT", readdir())) != 0)
    cd("ComicNEAT") # set dir if wd is git root
end

#module ComicNEAT
using(JLD)
using Serialization


include("src/Comic.jl") # make module comic "visible"
import .Comic # do not import .Comic twice! it will reset the added instances tracking potentially resulting in a segfault


include("src/NEAT.jl")
using .NEAT

function run_individual(individual::Individual, instance_id::Int, n_output::Int)
    # start with a fitness of 1
    fitness = 1
    last_fitness = 0.1
    counter = 0
    Comic.tick(instance_id)
    while(true) # run player
        environment = Comic.get_environment(instance_id)
        outputs = run_network(individual, environment, n_output)
        last_fitness = fitness
        fitness = Comic.tick(instance_id,UInt8.(outputs)...)
        if(fitness > last_fitness)
            counter=0
        else
            counter+=1
        end
        if(isnan(fitness) || counter > 128) # comic died
            break;
        end
    end
    Comic.reset(instance_id)
    return last_fitness
end

generations = []
function neat_step(population::Population, gen::Int, comic_train, comic_view,  n_input, n_output, runid)
    #train players
    best_individual = nothing
    best_fitness = 0
    for species in population.species
        for individual in species.individuals
            fitness = run_individual(individual, comic_train, n_output)
            # hall of fame ?
            if(fitness > best_fitness)
                best_fitness = fitness
                best_individual = individual
            end
            individual.fitness = isnan(fitness) ? 1 : fitness
        end
    end
    # now every instance is evaluates, show best
    print(run_individual(best_individual, comic_view, n_output))
    println(" generation ", gen, " fitness: ", best_fitness, " species: ", length(population.species),"/",population.setting.target_species, " - ",Int(floor(population.setting.species_threshold)), "\t#nodes: ", length(best_individual.nodes), "\t#connections: ", length(filter(x->x.enabled,best_individual.connections)))
    Comic.reset(comic_view)
    serialize(string(runid,"_",gen), population)
    # generate next gen
    push!(generations,Pair(deepcopy(population), deepcopy(best_individual)))
    next_generation(population)
end


function test()
    # create train and view instance
    comic_train = 3
    comic_view = 4
    Comic.add_instance(comic_train,0,0,1,-1)
    Comic.add_instance(comic_view,1,1,1,1)
    # create initial population
    environment = Comic.get_environment(comic_train)
    n_input = length(environment)
    n_output = 6
    a = rand()
    b = rand()
    c = rand()
    d = rand()
    println(a," ",b," ",c, " ",d)
    population = Population(n_input,n_output,a,b,c,d, 2048)
    gen = 0
    last_best_fitness = 0
    runid = string("runs/",floor(a*100),"-",floor(b*100),"-",floor(c*100),"-",floor(d*100))
    try
        while(true) # for every generation
            neat_step(population, gen, comic_train, comic_view, n_input, n_output, runid)
            gen+=1
        end
    catch e
        if e isa InterruptException
            # cleanup
            println("terminated by user")
        else
            rethrow(e)
        end
    end
end

test()
