shared_sources = [
    'Auth/AuthCrypt.cpp',
    'Auth/AuthCrypt.h',
    'Auth/BigNumber.cpp',
    'Auth/BigNumber.h',
    'Auth/HMACSHA1.cpp',
    'Auth/HMACSHA1.h',
    'Auth/md5.h',
    'Auth/Sha1.cpp',
    'Auth/Sha1.h',
    'Auth/base32.cpp',
    'Auth/base32.h',
    'Config/Config.cpp',
    'Config/Config.h',
    'Database/Database.cpp',
    'Database/Database.h',
    'Database/DatabaseEnv.h',
    'Database/DatabaseImpl.h',
    'Database/DatabaseMysql.cpp',
    'Database/DatabaseMysql.h',
    'Database/DatabasePostgre.cpp',
    'Database/DatabasePostgre.h',
    'Database/Field.cpp',
    'Database/Field.h',
    'Database/PGSQLDelayThread.h',
    'Database/QueryResult.h',
    'Database/QueryResultMysql.cpp',
    'Database/QueryResultMysql.h',
    'Database/QueryResultPostgre.cpp',
    'Database/QueryResultPostgre.h',
    'Database/SqlDelayThread.cpp',
    'Database/SqlDelayThread.h',
    'Database/SqlOperations.cpp',
    'Database/SqlOperations.h',
    'Database/SqlPreparedStatement.cpp',
    'Database/SqlPreparedStatement.h',
    'Database/SQLStorage.cpp',
    'Database/SQLStorage.h',
    'Database/SQLStorageImpl.h',
    'Database/DBCFileLoader.cpp',
    'Database/DBCFileLoader.h',
    'Database/DBCStore.h',
    'Log.cpp',
    'Log.h',
    'Multithreading/Messager.h',
    'Multithreading/Messager.cpp',
    'Metric/Measurement.cpp',
    'Metric/Measurement.h',
    'Metric/Metric.cpp',
    'Metric/Metric.h',
    'Network/PacketBuffer.cpp',
    'Network/Socket.cpp',
    'Network/Listener.hpp',
    'Network/NetworkThread.hpp',
    'Network/PacketBuffer.hpp',
    'Network/Socket.hpp',
    'ByteBuffer.cpp',
    'ByteBuffer.h',
    'Errors.h',
    'ProgressBar.cpp',
    'ProgressBar.h',
    'Timer.h',
    'Util.cpp',
    'Util.h',
    'WorldPacket.h',
    'ProducerConsumerQueue.h',
    'CommonDefines.h',
    'SRP6/SRP6.cpp',
    'SRP6/SRP6.h',
    'Common.cpp',
    'Common.h',
    'Filesystem.h',
    'revision_sql.h',
    'Threading.cpp',
    'Threading.h',
    'SystemConfig.h'
]

shared_linux = [
    'PosixDaemon.cpp',
    'PosixDaemon.h'
]

shared_windows = [
    'ServiceWin32.cpp',
    'ServiceWin32.h'
]

shared_inc_dirs = ['../framework', '../../dep/include/gsoap', '../../dep/include', 'Database']

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
                        include_directories: shared_inc,
                        dependencies: [zlib_dep, boost_dep, mariadb_dep, mysql_dep, postgresql_dep, openssl_dep, utfcpp_dep],
                        link_with: [frameworklib],
                        install : false
)
endif