
# FINAL PROJECT: was gonna try using a python script as a subsitute for
# nmake, but never finished it

# Also note: MSBuild is still required, make sure 
# it's in your path somewhere. Mine is at:
# C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe

import subprocess, os
from sys import argv

def RUN(script: str):
    subprocess.run(["powershell","-Command",script])

proj_name = os.path.basename(os.getcwd()) #name of project
rls = ".\cwin64\Release\$(proj_name).exe" #release executable
dbg = ".\cwin64\Debug\$(proj_name).exe" #debug executable
sln = ".\cwin64\$(proj_name).sln" #solution file
src = ".\src\**.cpp .\src\**.h" #cpp/h files

def test():
    RUN("echo Hello")

def ex_rls():
    RUN(f"cd .\\cwin64 && .\\Release\\{proj_name}.exe")

def bl_rls(): # === TODO ===
    #@cd .\cwin64 && msbuild .\$(proj_name).sln /p:Configuration=Release
	#@$(MAKE) /F DLLs.mk mode=Release
    pass

# === TODO === : rest of the commands

def clean():
    RUN("rmdir .\\cwin64 -Recurse")

clean()