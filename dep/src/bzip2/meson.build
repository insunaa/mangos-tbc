bzip2_sources = [
  'compress.c',
  'crctable.c',
  'decompress.c',
  'huffman.c',
  'randtable.c',
  'blocksort.c',
  'bzlib.c'
]

bz2_inc = include_directories(['../../../dep/include/bzip2', '.'])

bz2lib = static_library('bzip2',
                        bzip2_sources,
                        include_directories: bz2_inc,
                        install : false)

bzip2_dep = declare_dependency(
    include_directories: bz2_inc,
    link_with: bz2lib
)