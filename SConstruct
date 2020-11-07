env = Environment() 
env.Append(CPPPATH = ['#include'])
env.Append(LINKFLAGS='/SUBSYSTEM:CONSOLE') 
env.Append(CXXFLAGS='/EHsc /MD /std:c++14')
VariantDir('#/build', '#/src', duplicate=0)
Repository([ '#/lib/SFML-2.5.1' ]) 
env.Program( '#/bin/PSZT_SFML', Glob('#/src/*.cpp'), LIBS=['sfml-graphics', 'sfml-window','sfml-system'], LIBPATH=[ '#/lib/SFML-2.5.1/lib'],
)