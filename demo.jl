function run_demo()
    Comic.add_instance(1)
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
end
