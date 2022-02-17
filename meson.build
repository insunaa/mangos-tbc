project('CMaNGOS_TBC', 'cpp', 'c',
  default_options : ['cpp_std=c++17'])

if build_machine.system() == 'windows'
  error('Windows is currently not supported through Meson. Please use CMake instead')
endif

_linker_args = ''

boost_dep = dependency('boost', version: '>=1.66.0', modules: ['thread', 'program_options', 'system', 'filesystem'], static: true)
zlib_dep = dependency('zlib', static: true)
openssl_dep = dependency('openssl', version: '>=1.1.0')
mariadb_dep = dependency('mariadb', required: false)
mysql_dep = dependency('mysql', required: false)
postgresql_dep = dependency('postgresql', required: false)

if not mariadb_dep.found() and not mysql_dep.found() and not postgresql_dep.found()
  error('Either MySQL or MariaDB are required to build CMaNGOS')
else
  if get_option('POSTGRESQL')
    if postgresql_dep.found()
      add_global_arguments('-DDO_POSTGRESQL', language: 'cpp')
    else
      error('PostgreSQL could not be found.')
    endif
  else
    add_global_arguments('-DDO_MYSQL', language: 'cpp')
  endif
endif

if get_option('DEBUG')
  add_global_arguments('-g3', language: 'cpp')
else
  add_global_arguments('-DNDEBUG', language: 'cpp')
endif

if not get_option('WARNINGS')
  add_global_arguments('-w', language: 'cpp')
endif

if build_machine.system() == 'linux'
  add_global_arguments('-DSYSCONFDIR="../etc/"', language: 'cpp')
  if get_option('EXPERIMENTAL_LTO')
    if meson.get_compiler('cpp').get_id() == 'clang'
      add_global_arguments('-flto=thin', '-flto-jobs=all', '-fuse-ld=lld', language: 'cpp')
      _linker_args = '-fuse-ld=lld'
    elif meson.get_compiler('cpp').get_id() == 'gcc'
      add_global_arguments('-flto', language: 'cpp')
    else
      warning('LTO not supported')
    endif
  endif
endif

add_global_arguments('-DBOOST_ALL_NO_LIB', language: 'cpp')
add_global_arguments('-D__ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES=0', language: 'cpp')
add_global_arguments('-DDT_POLYREF64', language: 'cpp')

if get_option('BUILD_SCRIPTDEV')
  add_global_arguments('-DBUILD_SCRIPTDEV', language: 'cpp')
endif
if get_option('BUILD_PLAYERBOT')
  add_global_arguments('-DBUILD_PLAYERBOT', language: 'cpp')
endif
if get_option('BUILD_AHBOT')
  add_global_arguments('-DBUILD_AHBOT', language: 'cpp')
endif
if get_option('BUILD_METRICS')
  add_global_arguments('-DBUILD_METRICS', language: 'cpp')
endif

if get_option('BUILD_DOCS')
  subdir('doc')
endif

if get_option('BUILD_RECASTDEMOMOD')
  if build_machine.system() == 'windows'
    if not get_option('BUILD_EXTRACTORS')
      subdir('contrib/mmap')
    endif
    subdir('contrib/recastdemomod')
  else
    message('BUILD_RECASTDEMOMOD forced to OFF. Not supported on non windows system.')
  endif
endif

if get_option('BUILD_GIT_ID')
  subdir('contrib/git_id')
endif

subdir('dep')
if get_option('BUILD_GAME_SERVER') or get_option('BUILD_LOGIN_SERVER') or ('BUILD_EXTRACTORS')
  subdir('src')
endif

if get_option('BUILD_EXTRACTORS')
  extractor_script_file = files('contrib/extractor_scripts/ExtractResources.sh')
  movemapgen_script_file = files('contrib/extractor_scripts/MoveMapGen.sh')
  offmesh_file = files('contrib/extractor_scripts/offmesh.txt')
  subdir('contrib/extractor')
  subdir('contrib/vmap_extractor')
  subdir('contrib/vmap_assembler')
  subdir('contrib/mmap')
endif