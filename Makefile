
# Simple makefile utilizing Visual Studio's 'nmake' and 'MSBuild'/'msbuild' CLI 
# so that i can just run everything i need to do from VSCode from just one command.
# IE just enter "nmake" and it should compile & execute the whole module from scratch.
# sorry Visual Studio.

# Just ensure both programs are in your PATH so that this makefile runs properly
# On my computer they were at:
# C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.42.34433\bin\Hostx64\x64\nmake.exe
# C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe

# ===================================================================================================================

proj_name=FinalProject #set project name here (cant figure out how to do this automatically)

default: ex_rls # Set default target

# === ===

rls=.\cwin64\Release\$(proj_name).exe #release executable
dbg=.\cwin64\Debug\$(proj_name).exe #debug executable
sln=.\cwin64\$(proj_name).sln #solution file
src=.\src\**.cpp .\src\**.h .\src\My\* #cpp/h files

# === Release ===

ex_rls: $(rls) #execute release build
	@cd .\cwin64 && .\Release\$(proj_name).exe

bl_rls $(rls): $(sln) $(src) #build release
	@cd .\cwin64 && msbuild .\$(proj_name).sln /p:Configuration=Release
#	@$(MAKE) /F DLLs.mk mode=Release
# dont need the irrklang dll for this project

# === Debug ===

ex_dbg: $(dbg) #execute debug build
	@cd .\cwin64 && .\Debug\$(proj_name).exe

bl_dbg $(dbg): $(sln) $(src) #build debug
	@cd .\cwin64 && msbuild .\$(proj_name).sln /p:Configuration=Debug
#	@$(MAKE) /F DLLs.mk mode=Debug
# dont need the irrklang dll for this project

# === Solution ===

sln $(sln): .\src\CMakeLists.txt #build solution
	@cmake -G "Visual Studio 17 2022" -A x64 -S .\src\ -B .\cwin64

# === Set Path Bins ===

# for some reason i gotta do this once in a while
paths:
	sudo C:\repos\aftr\libs\AFTR__Set_Path_Bins_RUN_AS_ADMIN.bat

# === Clean ===

clean: #clean, just removes cwin64
	@rmdir .\cwin64 /S