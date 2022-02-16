mangosd_sources = [
    'CliRunnable.cpp',
    'CliRunnable.h',
    'MaNGOSsoap.cpp',
    'MaNGOSsoap.h',
    'Main.cpp',
    'Master.cpp',
    'Master.h',
    'RASocket.cpp',
    'RASocket.h',
    'WorldRunnable.cpp',
    'WorldRunnable.h',
    'soapC.cpp',
    'soapH.h',
    'soapServer.cpp',
    'soapStub.h'
]

mangosd_inc = include_directories('../shared', '../game', '../framework', '../../dep/include/utf8cpp', '../../dep/include/gsoap')

if get_option('BUILD_GAME_SERVER')
executable('mangosd',
            mangosd_sources,
            link_with: [sharedlib, gamelib, gsoaplib],
            include_directories: mangosd_inc,
            dependencies: [boost_dep, mariadb_dep, zlib_dep, mysql_dep, postgresql_dep],
            link_args: _linker_args,
            install: true
)
install_data('mangosd.conf.dist.in', rename: 'mangosd.conf.dist', install_dir: 'etc')
endif