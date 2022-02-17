movemapgen_args = ''
movemapgen_args = [movemapgen_args, '-DMMAP_GENERATOR', '-DNO_CORE_FUNCS', '-DNO_vsnprintf']
movemapgen_sources = [
  'src/generator.cpp',
  'src/IntermediateValues.h',
  'src/IntermediateValues.cpp',
  'src/MapBuilder.h',
  'src/MapBuilder.cpp',
  'src/MMapCommon.h',
  'src/TerrainBuilder.cpp',
  'src/TerrainBuilder.h',
  'src/VMapExtensions.cpp'
]

if build_machine.system() == 'linux'
  movemapgen_args = [movemapgen_args, '-ggdb']
endif

movemapgen_inc = include_directories('../../src', '../../src/game', '../../src/game/vmap')

vmaplib = static_library('vmaplib',
                        ['../../src/game/vmap/BIH.cpp', '../../src/game/vmap/VMapManager2.cpp', '../../src/game/vmap/MapTree.cpp', '../../src/game/vmap/TileAssembler.cpp', '../../src/game/vmap/WorldModel.cpp', '../../src/game/vmap/ModelInstance.cpp'],
                        include_directories: include_directories('../../src/framework', '../../src/game', '../../dep/json', '../../dep/g3dlite', '../../src/shared', '../../dep/recastnavigation', '../../dep/recastnavigation/Recast/Include', '../../dep/recastnavigation/Detour/Include', '../../src/game/vmap',),
                        dependencies: [zlib_dep, boost_dep, mariadb_dep, mysql_dep, postgresql_dep],
                        link_with: [g3dlib, detourlib, recastlib, frameworklib, sharedlib, gamelib],
                        install : false
)

mmaplib = static_library('mmaplib',
                         ['src/IntermediateValues.cpp', 'src/MapBuilder.cpp', 'src/TerrainBuilder.cpp', 'src/VMapExtensions.cpp'],
                         include_directories: include_directories('../../src/framework', '../../src/game', '../../dep/json', '../../dep/recastnavigation', '../../dep/recastnavigation/Recast/Include', '../../dep/recastnavigation/Detour/Include', '../../src/game/vmap', '../../dep/g3dlite'),
                         cpp_args: movemapgen_args,
                         link_with: [vmaplib, gamelib, detourlib, recastlib, g3dlib, frameworklib],
                         install: false
)

if get_option('BUILD_EXTRACTORS')
  if build_machine.system() == 'linux'
    local_linker = [_linker_args, '-rdynamic']
  endif
  executable('MoveMapGen',
              movemapgen_sources,
              link_with: [vmaplib, detourlib, recastlib, mmaplib],
              include_directories: include_directories('../../src/framework', '../../src/game', '../../dep/json', '../../dep/recastnavigation', '../../dep/recastnavigation/Recast/Include', '../../dep/recastnavigation/Detour/Include', '../../src/game/vmap', '../../dep/g3dlite'),
              dependencies: [boost_dep, mariadb_dep, zlib_dep, mysql_dep, postgresql_dep],
              cpp_args: movemapgen_args,
              link_args: _linker_args,
              install_dir: 'bin/tools',
              install: true
  )
  install_data(movemapgen_script_file, install_dir: 'bin/tools')
  install_data(offmesh_file, install_dir: 'bin/tools')
endif

