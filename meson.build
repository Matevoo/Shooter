project('Shooter', 'c', default_options : 'default_library=static')

add_global_arguments('-Wno-newline-eof', language : 'c')

srcs = []
deps = []

srcs += files(
    'src/logic/core/bullets.c', 'src/logic/core/core.c',
    'src/logic/core/effects.c', 'src/logic/core/motion.c',
    'src/logic/core/rendering.c',
    'src/logic/init/init.c',
    'src/logic/input/input.c',
    'src/logic/render/render.c',
    'src/logic/util/util.c'
)

deps += dependency(
    'sdl2', required : true,
    static : true, method : 'pkg-config'
)

deps += dependency(
    'sdl2_image', required : true,
    static : true, method : 'pkg-config'
)

executable(
    meson.project_name(), 'src/main.c',
    win_subsystem : 'windows',
    sources : srcs,
    dependencies : deps
)


