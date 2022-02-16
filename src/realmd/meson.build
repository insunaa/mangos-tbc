realmd_sources = [
    'AuthCodes.h',
    'AuthSocket.cpp',
    'AuthSocket.h',
    'Main.cpp',
    'RealmList.cpp',
    'RealmList.h'
]

realmd_inc = include_directories('../shared', '../game', '../framework', '../../dep/include/utf8cpp', '../../dep/include/gsoap')

if get_option('BUILD_LOGIN_SERVER')
executable('realmd',
            realmd_sources,
            link_with: [sharedlib],
            include_directories: realmd_inc,
            dependencies: [boost_dep, mariadb_dep, zlib_dep, mysql_dep, postgresql_dep],
            link_args: _linker_args,
            install: true
)
install_data('realmd.conf.dist.in', rename: 'realmd.conf.dist', install_dir: 'etc')
endif