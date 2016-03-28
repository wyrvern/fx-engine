@echo off

@path=""
@path=D:\null\bin\vs.12\VC\bin\

    @set include=""
rem @set include=C:\null\bin\vs.6\VC98\Include;C:\null\src\fx\bin\bin.engine\current-win\inc\;C:\null\src\fx\bin\bin.engine\current-win\ext\sdl\SDL-devel-1.2.15-VC\SDL-1.2.15\include\
    @set include=D:\null\bin\vs.12\VC\include;D:\null\src\fx\bin\bin.engine\inc\;D:\null\src\fx\bin\bin.engine\ext\sdl\SDL-devel-1.2.15-VC\SDL-1.2.15\include\;D:\null\sdk\ms\psdk\Include\

    @set lib=""
rem @set lib=C:\null\bin\vs.6\VC98\Lib;C:\null\src\fx\bin\bin.engine\current-win\ext\sdl\SDL-devel-1.2.15-VC\SDL-1.2.15\lib
    @set lib=D:\null\bin\vs.12\VC\lib\;D:\null\src\fx\bin\bin.engine\ext\sdl\SDL-devel-1.2.15-VC\SDL-1.2.15\lib;D:\null\sdk\ms\psdk\Lib\

rem @cl /MD /GX /c main.c load3ds.c loadjpeg.c mathlib.c
    @cl /MD /GX /c main.cpp load3ds.cpp loadjpeg.cpp mathlib.cpp

rem @link /noentry /defaultlib:winmm.lib opengl32.lib glu32.lib glaux.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib advapi32.lib lib/glut32.lib lib/libstr.lib lib/libimg.lib lib/libsys.lib lib/libml.lib lib/jpeg.lib ext/sdl/SDL-devel-1.2.15-VC/SDL-1.2.15/lib/x86/SDL.lib ext/sdl/SDL-devel-1.2.15-VC/SDL-1.2.15/lib/x86/SDLmain.lib /subsystem:windows /out:e.exe main.obj load3ds.obj loadjpeg.obj mathlib.obj 
    @link /defaultlib:winmm.lib opengl32.lib glu32.lib glaux.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib advapi32.lib lib/glut32.lib lib/libstr.lib lib/libimg.lib lib/libsys.lib lib/libml.lib lib/jpeg.lib ext/sdl/SDL-devel-1.2.15-VC/SDL-1.2.15/lib/x86/SDL.lib ext/sdl/SDL-devel-1.2.15-VC/SDL-1.2.15/lib/x86/SDLmain.lib /subsystem:windows /out:e.exe main.obj load3ds.obj loadjpeg.obj mathlib.obj 

