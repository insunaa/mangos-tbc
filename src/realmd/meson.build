realmd_sources = [
    'AuthCodes.h',
    'AuthSocket.cpp',
    'AuthSocket.h',
    'Main.cpp',
    'RealmList.cpp',
    'RealmList.h'
]

realmd_inc_dirs = ['../shared', '../game', '../framework', '../../dep/include/gsoap']

if utfcpp_dep.found() == false
  realmd_inc_dirs = [realmd_inc_dirs, '../../dep/include/utf8cpp']
endif

if build_machine.system() == 'windows'
  realmd_inc_dirs = realmd_inc_dirs + ['../../dep/lib/include', '../../dep/lib/include/mysql']
endif

realmd_inc = include_directories(realmd_inc_dirs)

if get_option('BUILD_LOGIN_SERVER')
executable('realmd',
            realmd_sources,
            link_with: [sharedlib],
            include_directories: realmd_inc,
            dependencies: [boost_dep, mariadb_dep, zlib_dep, mysql_dep, postgresql_dep, openssl_dep, utfcpp_dep],
            link_args: _linker_args,
            install: true
)
install_data('realmd.conf.dist.in', rename: 'realmd.conf.dist', install_dir: 'etc')
endif