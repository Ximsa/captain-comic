include("./comic.jl") # make module comic "visible"
import .Comic
# change working directory to comic folder for the library to not go haywire
# it is important to reset the working directory to the comic subdirectory if changed
cd(string(pwd(), "/comic"))

# some basic movement
Comic.add_instance(1,0,0,1)

for i in 1:10
    Comic.tick(1)
end
