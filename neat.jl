include("./comic.jl") # make module comic "visible"
import .Comic
# change working directory to comic folder for the library to not go haywire
# it is important to reset the working directory to the comic subdirectory if changed
cd(string(pwd(), "/comic"))

# some basic movement
Comic.add_instance(1)
Comic.tick(1,0,0,0,1)
Comic.tick(1,0,0,0,1)
Comic.tick(1,0,0,0,0,1)
Comic.tick(1,0,0,0,0,1)
for k in 1:3
    for i in 1:40
        Comic.tick(1,0,0,0,0,1)
    end
    for i in 1:4
        Comic.tick(1,1,0,0,0,1)
    end
    for i in 1:2
        Comic.tick(1,0,0,0,0,1)
    end
    for j in 1:5
        for i in 1:2
            Comic.tick(1,1,0,0,0,1)
        end
        for i in 1:5
            Comic.tick(1,0,0,0,0,1)
        end
    end
    for j in 1:10
        for i in 1:6
            Comic.tick(1,1,0,0,0,1)
        end
        for i in 1:5
            Comic.tick(1,0,0,0,0,1)
        end
    end
end




Comic.tick(1,1,1)
