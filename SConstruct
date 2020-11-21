import platform
env = Environment() 
system =platform.system().lower()
VariantDir('#/build', '#/src', duplicate=0)
resources=Glob('#/src/*.cpp')
if system == "windows":
    env.Append(CPPPATH = ['#include/'])
    env.Append(LINKFLAGS='/SUBSYSTEM:CONSOLE') 
    env.Append(CXXFLAGS='/EHsc /MD /std:c++17')
    env.Program( '#/bin/PSZT_SFML', resources, LIBS=['sfml-graphics', 'sfml-window','sfml-system'], LIBPATH=[ 'lib/SFML-2.5.1-Win/lib/'])
else:
    env.Append(CPPPATH = ['include'])
    env.Append(CXXFLAGS="-std=c++17")
    env.Program( '#/bin/PSZT_SFML', resources, LIBS=['sfml-graphics', 'sfml-window','sfml-system'])
