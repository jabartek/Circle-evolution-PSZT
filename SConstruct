test = ARGUMENTS.get('test', 0)

if not test:
    env = Environment() 
    env.Append(CPPPATH = ['#include'])
    env.Append(LINKFLAGS='/SUBSYSTEM:CONSOLE') 
    env.Append(CXXFLAGS='/EHsc /MD /std:c++14')
    VariantDir('#/build', '#/src', duplicate=0)
    Repository([ '#/lib/SFML-2.5.1' ]) 
    resources=Glob('#/src/*.cpp')
    env.Program( '#/bin/PSZT_SFML', resources, LIBS=['sfml-graphics', 'sfml-window','sfml-system'], LIBPATH=[ '#/lib/SFML-2.5.1/lib'])
else:
    env = Environment() 
    env.Append(CPPPATH = ['#include'])
    env.Append(LINKFLAGS='/SUBSYSTEM:CONSOLE') 
    env.Append(CXXFLAGS='/EHsc /MD /std:c++14')
    VariantDir('#/build', '#/src', duplicate=0)
    resources = [ '#/tests/test.cpp', '#/src/evolutionModule.cpp']
    env.Program( '#/bin/TESTS', resources)