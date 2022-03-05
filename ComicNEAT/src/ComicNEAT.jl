# !assumes working directory set to project directory!
module ComicNEAT

include("src/comic.jl") # make module comic "visible"

import .Comic



# some basic movement
Comic.add_instance(1,1,1,1,2)

for i in 1:1
    Comic.tick(1,0,0,0,0,1)
end


end # module
