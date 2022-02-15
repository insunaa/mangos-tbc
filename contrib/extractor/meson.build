ad_sources = [
  'loadlib/loadlib.cpp',
  'loadlib/adt.cpp',
  'loadlib/wdt.cpp',
  'loadlib/loadlib.h',
  'loadlib/adt.h',
  'loadlib/wdt.h',
  'dbcfile.cpp',
  'dbcfile.h',
  'mpq_libmpq.cpp',
  'mpq_libmpq.h',
  'System.cpp',
]

ad_inc = include_directories('../../src/game', '../../dep/libmpq')

executable('ad',
            ad_sources,
            link_with: [lib_libmpq],
            include_directories: ad_inc,
            dependencies: [boost_dep, mariadb_dep, zlib_dep, mysql_dep, postgresql_dep],
            link_args: _linker_args,
            install_dir: 'bin/tools',
            install: true
)
