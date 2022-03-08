
# !assumes working directory set to project directory!

if(length(filter(x -> x=="ComicNEAT", readdir())) != 0)
    cd("ComicNEAT") # set dir if wd is git root
end

#module ComicNEAT

include("src/comic.jl") # make module comic "visible"
import .Comic # do not import .Comic twice! it will reset the added instances tracking potentially resulting in a segfault


include("src/NEAT.jl")

using .NEAT




function demo()
    comic_instance_id = 6
    Comic.add_instance(comic_instance_id,1,1,1,-1)
    Comic.reset(comic_instance_id)
    environment = Comic.get_environment(comic_instance_id)
    n_input = length(environment)
    n_output = 6
    n_hidden = 0
    population = Population(n_input,n_output)
    players = population.species[1].individuals
    for player in players
        fitness = 0
        counter = 0
        while(true)
            environment = Comic.get_environment(comic_instance_id)
            outputs = run_network(player, environment, n_output)
            last_fitness = fitness
            fitness = Comic.tick(comic_instance_id,UInt8.(outputs)...)
            if(fitness > last_fitness)
                #println(fitness)
            else
                counter+=1
            end
            if(isnan(fitness) || counter > 768) # comic died
                break;
            end
        end
        Comic.reset(comic_instance_id)
    end
end
