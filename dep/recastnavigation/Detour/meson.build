detour_sources = [
    'Source/DetourAlloc.cpp',
    'Source/DetourAssert.cpp',
    'Source/DetourCommon.cpp',
    'Source/DetourNavMesh.cpp',
    'Source/DetourNavMeshBuilder.cpp',
    'Source/DetourNavMeshQuery.cpp',
    'Source/DetourNode.cpp'
]

detour_inc = include_directories('Include')

detourlib = static_library('Detour',
                        detour_sources,
                        include_directories: detour_inc,
                        install : false)