shared_sources = [
'./Metric/Measurement.cpp',
'./Metric/Metric.cpp',
'./Multithreading/Threading.cpp',
'./Multithreading/Messager.cpp',
'./Util/Util.cpp',
'./Util/ProgressBar.cpp',
'./Util/ByteBuffer.cpp',
'./Log.cpp',
'./pchdef.cpp',
'./Database/SqlPreparedStatement.cpp',
'./Database/SqlDelayThread.cpp',
'./Database/Field.cpp',
'./Database/Database.cpp',
'./Database/SqlOperations.cpp',
'./Database/QueryResultPostgre.cpp',
'./Database/DBCFileLoader.cpp',
'./Database/DatabasePostgre.cpp',
'./Database/SQLStorage.cpp',
'./Database/QueryResultMysql.cpp',
'./Database/DatabaseMysql.cpp',
'./Auth/SARC4.cpp',
'./Auth/base32.cpp',
'./Auth/HMACSHA1.cpp',
'./Auth/SRP6.cpp',
'./Auth/BigNumber.cpp',
'./Common.cpp',
'./Network/Socket.cpp',
'./Network/PacketBuffer.cpp',
'./Network/NetworkThread.cpp',
'./Network/Listener.cpp',
'./Config/Config.cpp'
]

shared_linux = [
    'Platform/PosixDaemon.cpp',
]

shared_windows = [
    'Platform/ServiceWin32.cpp',
    'Platform/WheatyExceptionReport.cpp',
]

shared_inc_dirs = ['../framework', '../../dep/include/gsoap', '../../dep/include', 'Database', '../mangosd', '../game']

if utfcpp_dep.found() == false
  shared_inc_dirs = [shared_inc_dirs, '../../dep/include/utf8cpp']
endif

if build_machine.system() == 'windows'
  shared_sources = shared_sources + shared_windows
  shared_inc_dirs = shared_inc_dirs + ['../../dep/lib/include', '../../dep/lib/include/mysql']
else
  shared_sources = shared_sources + shared_linux
endif

shared_inc = include_directories(shared_inc_dirs)

revision_target = vcs_tag(
  command        : ['git', 'rev-parse', 'HEAD'],
  fallback       : 'Devel',
  input          : 'meson_revision.h.in',
  output         : 'meson_revision.h.temp',
  replace_string : '@REVISION_ID@'
)

actual_rev = vcs_tag(
    command: ['git', 'show', '--quiet', '--date=iso-strict', '--format="%ad"', 'HEAD'],
    fallback: '"0000-00-00T00:00:00+00:00"',
    input: revision_target,
    output: 'revision.h',
    replace_string: '@REVISION_DATE@'
)

if get_option('BUILD_GAME_SERVER') or get_option('BUILD_LOGIN_SERVER')
sharedlib = static_library('shared',
                        [actual_rev, shared_sources],
                        include_directories: [shared_inc, global_includes],
                        dependencies: [zlib_dep, boost_dep, mariadb_dep, mysql_dep, postgresql_dep, openssl_dep, utfcpp_dep],
                        link_with: [frameworklib],
                        install : false
)
endif
