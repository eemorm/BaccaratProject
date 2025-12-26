project('BaccaratProject', 'cpp', default_options: ['cpp_std=c++17'])

cxx = meson.get_compiler('cpp')

# ---- Detect host OS ----
if host_machine.system() == 'darwin'
  # macOS (Homebrew SFML)
  sfml_inc = include_directories('/opt/homebrew/Cellar/sfml@2/2.6.2_1/include')
  sfml_lib_dir = '/opt/homebrew/Cellar/sfml@2/2.6.2_1/lib'

  sfml_graphics = cxx.find_library('sfml-graphics', dirs: sfml_lib_dir)
  sfml_window   = cxx.find_library('sfml-window',   dirs: sfml_lib_dir)
  sfml_system   = cxx.find_library('sfml-system',   dirs: sfml_lib_dir)
  sfml_network  = cxx.find_library('sfml-network',  dirs: sfml_lib_dir)
  sfml_audio    = cxx.find_library('sfml-audio',    dirs: sfml_lib_dir)

  sfml_deps = [sfml_graphics, sfml_window, sfml_system, sfml_network, sfml_audio]

elif host_machine.system() == 'windows'
  # Windows (SFML inside project)
  sfml_inc = include_directories('libs/SFML/include')

  windows_libs = [
    'libs/SFML/lib/sfml-graphics-s.lib',
    'libs/SFML/lib/sfml-window-s.lib',
    'libs/SFML/lib/sfml-system-s.lib',
    'libs/SFML/lib/sfml-network-s.lib',
    'libs/SFML/lib/sfml-audio-s.lib',
  ]
endif

# ---- Sources ----
sources = files('src/main.cpp')

# ---- Executable ----
if host_machine.system() == 'darwin'
  executable(
    'BaccaratProject',
    sources,
    include_directories: sfml_inc,
    dependencies: sfml_deps
  )
elif host_machine.system() == 'windows'
  executable(
    'BaccaratProject',
    sources,
    include_directories: sfml_inc,
    link_args: windows_libs
  )
endif