project('cmangos', 'cpp',
    default_options : ['cpp_std=c++17'])

boost_dep = dependency('boost', modules: ['thread', 'program_options', 'system', 'filesystem'])
zlib_dep = dependency('zlib')
openssl_dep = dependency('openssl')
mariadb_dep = dependency('mariadb')

add_global_arguments('-DSYSCONFDIR="../etc/"', language: 'cpp')

subdir('dep')
subdir('src')