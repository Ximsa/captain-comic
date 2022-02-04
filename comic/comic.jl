
using Base.Libc.Libdl

comic_lib = "./comic_linux.so"
comic_instances = Dict()
instance_id = 1

function comic_add_instance(instance_id, graphic, sound, skip_intro)
    file_name = comic_lib * "." * string(instance_id)
    cp(comic_lib, file_name, force=true)
    handle = dlopen(file_name)
    comic_instances[instance_id] = Dict()
    comic_instances[instance_id][:handle] = handle

    comic_instances[instance_id][:tick] = dlsym(handle, :tick)
    comic_instances[instance_id][:get_environment] = dlsym(handle, :get_environment)
    comic_instances[instance_id][:reset] = dlsym(handle, :reset)
    ccall(dlsym(handle, :setup), Cvoid,
          (UInt8,UInt8,UInt8),
          graphic,sound,skip_intro)
    rm(file_name)
end

function comic_tick(instance_id, jump=0,
                    open_door=0, teleport=0,
                    left=0, right=0,
                    pause=0, fire=0)
    ccall(comic_instances[instance_id][:tick], Cvoid,
          (UInt8,UInt8,UInt8,UInt8,UInt8,UInt8,UInt8),
          jump, open_door, teleport, left, right, pause, fire)
end

function comic_get_environment(instance_id)
    environment = UInt8[0 for i=1:(20*24)]
    stats = UInt8[0 for i=1:(20*24)]
    ccall(comic_instances[instance_id][:get_environment], Cvoid,
          (Ptr{UInt8}, Ptr{UInt8}),
          environment, stats)
    return environment,stats
end

function comic_reset(instance_id)
    ccall(comic_instances[instance_id][:reset], Cvoid,())
end
