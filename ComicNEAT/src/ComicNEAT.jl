# !assumes working directory set to project directory!

if(length(filter(x -> x=="ComicNEAT", readdir())) != 0)
    cd("ComicNEAT") # set dir if wd is git root
end

#module ComicNEAT

include("src/comic.jl") # make module comic "visible"
include("src/NEAT.jl")
import .Comic # do not import .Comic twice! it will reset the added instances tracking potentially resulting in a segfault
using .NEAT



# some basic movement
Comic.add_instance(2,1,1,1,2)

Comic.reset(2)
environment = Comic.get_environment(2)
n_input = length(environment)
n_output = 6
n_hidden = Int(floor(sqrt(n_input)))
player = Individual(n_input,n_output,n_hidden, 0.5)
fitness = 0
for i in 1:512
    environment = Comic.get_environment(2)
    outputs = run_network(player, environment)
    last_fitness = fitness
    fitness = Comic.tick(2,UInt8.(outputs)...)
    if(fitness > last_fitness)
        println(fitness)
    end
    if(isnan(fitness)) # comic died
        break;
    end
    sleep(0.002)
end

Comic.reset(2)
#end # module
