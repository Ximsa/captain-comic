module Comic

export add_instance, tick, get_environment, reset, get_environment_raw
export instances

using Base.Libc.Libdl

lib = "./comic_linux.so"
lib_win = "comic_windows.dll"
instances = Dict()

"""
add_instance(instance_id, (optional) graphic, (optional) sound, (optional) skip_intro, (optional) speed)

Creates a new comic instance with the id "instance_id".
graphic determines if the graphics system should be initialized
sound determines if the sound system should be initialized
skip_intro determines if the intro sequence should be skipped
speed determines the speed factor of the game, -1 for unlimited

!graphic and !sound  => skip_intro = 1, speed = -1

Adding a instance_id that already exists results in the existing instance to be reseted

Also, even when graphic is false (0), the game still has static buffers for the graphics 
resulting in ~40MB per instance of extra ram footprint
"""
function add_instance(instance_id, graphic=1, sound=1, skip_intro=1, speed=1)
    if haskey(instances, instance_id)
        reset(instance_id)
    else
        file_name = if Sys.iswindows()
            string(chop(lib_win, tail = 4), instance_id, ".dll")
        else
            string(lib, ".", instance_id)
        end
        cp(if Sys.iswindows() lib_win else lib end, file_name, force=true)
        handle = dlopen(if Sys.iswindows() chop(file_name, tail = 4) else file_name end)
        instances[instance_id] = Dict()
        instances[instance_id][:handle] = handle
        instances[instance_id][:tick] = dlsym(handle, :tick)
        instances[instance_id][:get_environment] = dlsym(handle, :get_environment)
        instances[instance_id][:reset] = dlsym(handle, :reset)
        ccall(dlsym(handle, :setup), Cvoid,
              (UInt8,UInt8,UInt8,Float32),
              graphic,sound,skip_intro,speed)
        if !Sys.iswindows() rm(file_name) end
    end
end
"""
tick(instance_id, (optional) jump, (optional) open_door, (optional) teleport, (optional) left, (optional) right, (optional) fire)

tells the game with id "instance_id" to do one tick.
returns the fitness if comic is still alive, else NAN

fitness currently gets evaluated by time alive ( and not standing still ) + items collected
"""

function tick(instance_id, jump=0,
              open_door=0, teleport=0,
              left=0, right=0, fire=0)
    return ccall(instances[instance_id][:tick], Cdouble,
                 (UInt8,UInt8,UInt8,UInt8,UInt8,UInt8,UInt8),
                 jump, open_door, teleport, left, right, 0, fire)
end




"""
    B = shift_lr(A, k)
Shift `A` by `k` columns. If `k` is positive, shift to the
    right by inserting `k` columns on the left. If `k` is
    negative, shift to the left by inserting `k` columns
    on the right.
source: https://gist.github.com/kersulis/da5b4085e09ace35ce3e94416bf918e3
"""
function shift_lr(A::AbstractMatrix, k::Integer)
    k == 0 && return A
    m, n = size(A)
    if abs(k) > n
        @error "Cannot shift matrix with $n columns by $k columns"
    end
    fill_val = -1 #(k > 0 ? A[1] : A[end])
    F = fill(fill_val, m, abs(k))
    B = (k > 0 ? [F A[:, 1:(n - k)]] : [A[:, (abs(k) + 1):n] F])
    return B
end

"""
Shift `A` by `k` rows. If `k` is positive, shift upward by
    inserting `k` rows on the bottom. If `k` is
    negative, shift downward by inserting `k` rows
    on top.
source: https://gist.github.com/kersulis/da5b4085e09ace35ce3e94416bf918e3
"""
function shift_ud(A::AbstractMatrix, k::Integer)
    k == 0 && return A
    m, n = size(A)
    if abs(k) > m
        @error "Cannot shift matrix with $m rows by $k rows."
    end
    fill_val = -1 # = (k > 0 ? A[1] : A[end])
    F = fill(fill_val, abs(k), n)
    B = (k > 0 ? [A[(k + 1):m, :]; F] : [F; A[1:(m - abs(k)), :]])
    return B
end

"""
center_environment(environment::Vector{Float32})

centers the environment around comic
"""
function center_environment(environment::Vector{Float32})
    view = reshape(environment, 12, 10)
    comic_x = 0
    comic_y = 0
    for y = 1:size(view,2)
        for x = 1:size(view,1)
            if(view[x,y] == 4)
                view[x,y] = 0
                comic_x = x
                comic_y = y
            end
        end
    end
    comic_x -= Int(floor(size(view,1)/2))
    comic_y -= Int(floor(size(view,2)/2))
    return vec(shift_lr(shift_ud(view,comic_x),-comic_y))
end

"""
get_environment(instance_id)

tells the game with id "instance_id" to return the current game state.
returns 2 UInt8 arrays: 
  first array is the visible world (24*20)
  second array are the stats of comic:
    current_level_number
    current_stage_number
    comic_hp
    comic_firepower
    fireball_meter
    comic_jump_power
    comic_has_corkscrew;
    comic_has_door_key;
    comic_has_lantern;
    comic_has_teleport_wand;
    comic_has_gems;
    comic_has_gold;
    comic_has_crown;
    comic_facing;
        
example: 
julia> reshape(Comic.get_environment(instance_id)[1:10*12], 12, 10) |> transpose
returns the world "human readable"
"""
function get_environment(instance_id)
    environment = Vector{UInt8}(undef,10*12) #UInt8[0 for i=1:(20*24)]
    stats = Vector{UInt8}(undef,14) #UInt8[0 for i=1:(20*24)]
    ccall(instances[instance_id][:get_environment], Cvoid,
          (Ptr{UInt8}, Ptr{UInt8}),
          environment, stats)
    # environment ranges from 0 to 255
    return [center_environment(Float32.(environment)) ; Float32.(stats)]
end

function get_environment_raw(instance_id)
    environment = Vector{UInt8}(undef,10*12) #UInt8[0 for i=1:(20*24)]
    stats = Vector{UInt8}(undef,14) #UInt8[0 for i=1:(20*24)]
    ccall(instances[instance_id][:get_environment], Cvoid,
          (Ptr{UInt8}, Ptr{UInt8}),
          environment, stats)
    # environment ranges from 0 to 255
    return [Float32.(environment) ; Float32.(stats)]
end




"""
reset(instance_id)
resets the comic instance to the original state
"""
function reset(instance_id)
    ccall(instances[instance_id][:reset], Cvoid,())
end

end
