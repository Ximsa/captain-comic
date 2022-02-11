module Comic

export add_instance, tick, get_environment, reset
export instances

using Base.Libc.Libdl

lib = "./comic_linux.so"
lib_win = "comic_windows.dll"
instances = Dict()
first_run = true
function add_instance(instance_id, graphic=1, sound=1, skip_intro=1)
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
              (UInt8,UInt8,UInt8),
              graphic,sound,skip_intro)
        if !Sys.iswindows() rm(file_name) end
    end
end

function tick(instance_id, jump=0,
              open_door=0, teleport=0,
              left=0, right=0,
              pause=0, fire=0)
    ccall(instances[instance_id][:tick], Cvoid,
          (UInt8,UInt8,UInt8,UInt8,UInt8,UInt8,UInt8),
          jump, open_door, teleport, left, right, pause, fire)
end

function get_environment(instance_id)
    environment = UInt8[0 for i=1:(20*24)]
    stats = UInt8[0 for i=1:(20*24)]
    ccall(instances[instance_id][:get_environment], Cvoid,
          (Ptr{UInt8}, Ptr{UInt8}),
          environment, stats)
    return environment, stats
end

function reset(instance_id)
    ccall(instances[instance_id][:reset], Cvoid,())
end
end
