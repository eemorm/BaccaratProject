project('Croupier', 'cpp', default_options: ['cpp_std=c++17'])

cxx = meson.get_compiler('cpp')

# ---- Sources ----
sources = files('src/main.cpp', 'src/Architecture/GameStateManager.cpp')

# ---- Detect host OS ----
if host_machine.system() == 'darwin'
  sfml_inc = include_directories('/opt/homebrew/Cellar/sfml@2/2.6.2_1/include')
  sfml_lib_dir = '/opt/homebrew/Cellar/sfml@2/2.6.2_1/lib'

  sfml_graphics = cxx.find_library('sfml-graphics', dirs: sfml_lib_dir)
  sfml_window   = cxx.find_library('sfml-window',   dirs: sfml_lib_dir)
  sfml_system   = cxx.find_library('sfml-system',   dirs: sfml_lib_dir)
  sfml_network  = cxx.find_library('sfml-network',  dirs: sfml_lib_dir)
  sfml_audio    = cxx.find_library('sfml-audio',    dirs: sfml_lib_dir)

  sfml_deps = declare_dependency(
    include_directories: sfml_inc,
    dependencies: [sfml_graphics, sfml_window, sfml_system, sfml_network, sfml_audio]
  )

elif host_machine.system() == 'windows'
  sfml_inc = include_directories('libs/SFML/include')
  sfml_lib_dir = meson.source_root() / 'libs/SFML/lib'

  sfml_graphics = cxx.find_library('sfml-graphics', dirs: sfml_lib_dir)
  sfml_window   = cxx.find_library('sfml-window',   dirs: sfml_lib_dir)
  sfml_system   = cxx.find_library('sfml-system',   dirs: sfml_lib_dir)
  sfml_network  = cxx.find_library('sfml-network',  dirs: sfml_lib_dir)
  sfml_audio    = cxx.find_library('sfml-audio',    dirs: sfml_lib_dir)

  sfml_deps = declare_dependency(
    include_directories: sfml_inc,
    dependencies: [sfml_graphics, sfml_window, sfml_system, sfml_network, sfml_audio]
  )
endif

# ---- Executable ----
# Install EXE directly to prefix (root install folder)
executable(
  'Croupier',
  sources,
  dependencies: sfml_deps,
  install: true,
  install_dir: get_option('prefix')
)

# ---- Assets ----
install_subdir('textures', install_dir: get_option('prefix'))
install_subdir('audio',    install_dir: get_option('prefix'))
install_subdir('fonts',    install_dir: get_option('prefix'))
install_subdir('shaders',  install_dir: get_option('prefix'))

# ---- SFML DLLs for Windows ----
if host_machine.system() == 'windows'
  sfml_dlls = files(
    'libs/SFML/bin/sfml-graphics-2.dll',
    'libs/SFML/bin/sfml-window-2.dll',
    'libs/SFML/bin/sfml-system-2.dll',
    'libs/SFML/bin/sfml-network-2.dll',
    'libs/SFML/bin/sfml-audio-2.dll'
  )
  install_data(sfml_dlls, install_dir: get_option('prefix'))  # Root, not bin
endif