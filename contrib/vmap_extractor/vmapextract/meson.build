vmap_extractor_sources = [
    'adtfile.cpp',
    'dbcfile.cpp',
    'gameobject_extract.cpp',
    'model.cpp',
    'mpq_libmpq.cpp',
    'vmapexport.cpp',
    'wdtfile.cpp',
    'wmo.cpp',
    'adtfile.h',
    'dbcfile.h',
    'modelheaders.h',
    'model.h',
    'mpq_libmpq04.h',
    'vmapexport.h',
    'wdtfile.h',
    'wmo.h',
    'vec3d.h'
]

executable('vmap_extractor',
            vmap_extractor_sources,
            include_directories: include_directories('../../../../dep/g3dlite', '../../../../dep/libmpq', '../../../../dep/recastnavigation', '../../../../src/game'),
            link_with: [g3dlib, lib_libmpq, gamelib, detourlib, recastlib],
            link_args: _linker_args,
            install_dir: 'bin/tools',
            install: true
)
install_data(extractor_script_file, install_dir: 'bin/tools')