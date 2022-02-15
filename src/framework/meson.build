framework_sources = [
    'Dynamic/FactoryHolder.h',
    'Dynamic/ObjectRegistry.h',
    'GameSystem/Grid.h',
    'GameSystem/GridLoader.h',
    'GameSystem/GridReference.h',
    'GameSystem/GridRefManager.h',
    'GameSystem/NGrid.h',
    'GameSystem/TypeContainer.h',
    'GameSystem/TypeContainerFunctions.h',
    'GameSystem/TypeContainerVisitor.h',
    'Platform/CompilerDefs.h',
    'Platform/Define.h',
    'Policies/CreationPolicy.h',
    'Policies/ObjectLifeTime.cpp',
    'Policies/ObjectLifeTime.h',
    'Policies/Singleton.h',
    'Policies/ThreadingModel.h',
    'Utilities/ByteConverter.h',
    'Utilities/Callback.h',
    'Utilities/EventProcessor.cpp',
    'Utilities/EventProcessor.h',
    'Utilities/LinkedList.h',
    'Utilities/TypeList.h',
    'Utilities/LinkedReference/Reference.h',
    'Utilities/LinkedReference/RefManager.h'
]

if get_option('BUILD_GAME_SERVER') or get_option('BUILD_LOGIN_SERVER') or get_option('BUILD_EXTRACTORS')
frameworklib = static_library('framework',
                        framework_sources,
                        install : false
)
endif