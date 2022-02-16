error('Docs Currently unsupported')
doxygen = find_program('doxygen', required : false)
if doxygen.found()
  run_target('docs', command : [doxygen, meson.source_root() + '/doc/Doxyfile'])    
else
  warning('Documentation disabled without doxygen')
endif