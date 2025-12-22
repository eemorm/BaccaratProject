project('BaccaratProject', 'cpp', default_options: ['cpp_std=c++17'])

# Get C++ compiler
cxx = meson.get_compiler('cpp')

# Include directories
sfml_inc = include_directories('/opt/homebrew/Cellar/sfml@2/2.6.2_1/include')
openal_inc = include_directories('/opt/homebrew/opt/openal-soft/include')

# Library directories
sfml_lib_dir = '/opt/homebrew/Cellar/sfml@2/2.6.2_1/lib'
openal_lib_dir = '/opt/homebrew/opt/openal-soft/lib'

# External dependencies
sfml_graphics = cxx.find_library('sfml-graphics', dirs: sfml_lib_dir)
sfml_window   = cxx.find_library('sfml-window', dirs: sfml_lib_dir)
sfml_system   = cxx.find_library('sfml-system', dirs: sfml_lib_dir)
sfml_network  = cxx.find_library('sfml-network', dirs: sfml_lib_dir)
sfml_audio    = cxx.find_library('sfml-audio', dirs: sfml_lib_dir)
openal_lib    = cxx.find_library('openal', dirs: openal_lib_dir)

sfml_deps = [sfml_graphics, sfml_window, sfml_system, sfml_network, sfml_audio, openal_lib]

# Sources
sources = files('src/main.cpp')

# Build executable
executable('BaccaratProject',
    sources,
    include_directories: [sfml_inc, openal_inc],
    dependencies: sfml_deps
)
