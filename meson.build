project('BaccaratProject', 'cpp',
  version : '0.1.0',
  default_options : ['cpp_std=c++20']
)

sfml_graphics = dependency('sfml-graphics')
sfml_network  = dependency('sfml-network')

executable('BaccaratProject', 'src/main.cpp',
  dependencies : [sfml_graphics, sfml_network]
)
