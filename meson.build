project('CMaNGOS_TBC', 'cpp', 'c',
  default_options : ['cpp_std=c++17', 'buildtype=release', 'warning_level=0'])

if build_machine.system() == 'windows'
  warning('Windows requires extra care when installing dependencies, as it has no integrated system to manage them.')
  warning('Boost in particular needs to be installed from SourceForge and must not contain any .pdb files to be properly detected.')
  warning('It is strongly recommended to use the Ninja generator instead of the MSVC generator.')
  warning('To configure the build use `meson configure` in the build directory.')
  add_project_arguments('/Zc:strictStrings-', language : 'cpp')
endif

_linker_args = ''

boost_dep = dependency('boost', version: '>=1.66.0', modules: ['thread', 'program_options', 'system', 'filesystem'], static: true)
mariadb_dep = dependency('mariadb', required: false)
mysql_dep = dependency('mysql', required: false)
postgresql_dep = dependency('postgresql', required: get_option('POSTGRESQL'))
zlib_dep = dependency('zlib', static: true, fallback: ['zlib', 'zlib_dep'])
openssl_dep = dependency('openssl', version: ['>=1.1.0', '<3.0.0'], static: true, fallback: ['openssl'])

if not mariadb_dep.found() and not mysql_dep.found() and not postgresql_dep.found()
  if build_machine.system() == 'windows'
    mysql_dirs = [
      'C:\Program Files\MySQL\MySQL Server 8.0\lib',
      'C:\Program Files\MySQL\MySQL Server 5.7\lib'
    ]

    fs = import('fs')
    if fs.is_dir('C:\Program Files\MySQL\MySQL Server 8.0\lib')
      mysql_dll = 'C:\Program Files\MySQL\MySQL Server 8.0\lib\libmysql.dll'
    elif fs.is_dir('C:\Program Files\MySQL\MySQL Server 8.0\lib')
      mysql_dll = 'C:\Program Files\MySQL\MySQL Server 5.7\lib\libmysql.dll'
    else
      error('No local MySQL Server installation found')
    endif

    mysql_dep = meson.get_compiler('cpp').find_library('mysql', dirs: mysql_dirs, static: true, required: true)
    install_data(mysql_dll, install_dir: get_option('bindir'))
  else
    error('Either MySQL or MariaDB are required to build CMaNGOS')
  endif
endif

if get_option('POSTGRESQL')
  add_project_arguments('-DDO_POSTGRESQL', language: 'cpp')
endif

if get_option('DEBUG')
  add_project_arguments('-g3', language: 'cpp')
endif

if not get_option('WARNINGS')
  add_project_arguments('-w', language: 'cpp')
endif

if build_machine.system() == 'linux'
  add_project_arguments('-DSYSCONFDIR="../etc/"', language: 'cpp')
endif

add_project_arguments('-DBOOST_ALL_NO_LIB', language: 'cpp')

if get_option('BUILD_SCRIPTDEV')
  add_project_arguments('-DBUILD_SCRIPTDEV', language: 'cpp')
endif
if get_option('BUILD_PLAYERBOT')
  add_project_arguments('-DBUILD_PLAYERBOT', language: 'cpp')
endif
if get_option('BUILD_AHBOT')
  add_project_arguments('-DBUILD_AHBOT', language: 'cpp')
endif
if get_option('BUILD_METRICS')
  add_project_arguments('-DBUILD_METRICS', language: 'cpp')
endif

if get_option('BUILD_DOCS')
  subdir('doc')
endif

if get_option('BUILD_RECASTDEMOMOD')
  error('RECASTDEMOMOD currently unavailable')
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

