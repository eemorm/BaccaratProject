project('BaccaratProject', 'cpp',
  default_options: ['cpp_std=c++17']
)

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

  # Wrap static SFML libs as project-built targets
  sfml_graphics = static_library('sfml-graphics', 'libs/SFML/lib/libsfml-graphics-s.lib')
  sfml_window   = static_library('sfml-window',   'libs/SFML/lib/libsfml-window-s.lib')
  sfml_system   = static_library('sfml-system',   'libs/SFML/lib/libsfml-system-s.lib')
  sfml_network  = static_library('sfml-network',  'libs/SFML/lib/libsfml-network-s.lib')
  sfml_audio    = static_library('sfml-audio',    'libs/SFML/lib/libsfml-audio-s.lib')

  sfml_deps = [sfml_graphics, sfml_window, sfml_system, sfml_network, sfml_audio]
endif

# ---- Sources ----
sources = files('src/main.cpp')

# ---- Build Executable ----
executable(
  'BaccaratProject',
  sources,
  include_directories: sfml_inc,
  dependencies: sfml_deps
)