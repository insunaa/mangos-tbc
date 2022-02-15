utf8cpp_inc = include_directories('../../../dep/include/utf8cpp')

utf8cpp_source = []

if build_machine.system() == 'windows'
  utf8cpp_source = 'utf8.cpp'
endif

libutf8cpp = static_library('utf8cpp',
                        utf8cpp_source,
                        include_directories: utf8cpp_inc,
                        install : false)