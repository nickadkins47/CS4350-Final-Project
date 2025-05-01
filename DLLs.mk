
# FINAL PROJECT: feel free to delete this file, im not using irrklang for this project

# Seperate makefile for handling DLLs (changes depending on the project)

IRK_BIN = C:\repos\aftr\usr\include\irrklang\bin\winx64-visualStudio
IRK_1 = irrKlang.dll
IRK_2 = ikpMP3.dll
IRK_3 = ikpFlac.dll

mode = Release
dll_out = .\cwin64\$(mode)
dll_com = copy BIN\DLL $(dll_out)\DLL

dlls = $(dll_out)\$(IRK_1) $(dll_out)\$(IRK_2) #$(dll_out)\$(IRK_3)

main: $(dlls)

$(dlls):
	$(subst BIN,$(IRK_BIN),$(subst DLL,$(IRK_1),$(dll_com)))
	$(subst BIN,$(IRK_BIN),$(subst DLL,$(IRK_2),$(dll_com)))
#	$(subst BIN,$(IRK_BIN),$(subst DLL,$(IRK_3),$(dll_com)))

clean:
	del $(dll_out)\$(IRK_1)
	del $(dll_out)\$(IRK_2)
#	del $(dll_out)\$(IRK_3)