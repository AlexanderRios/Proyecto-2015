#Variables
c = g++
principal = principal.cpp

#Compilando y Ejecutando
principal :
	@ reset
	@ $(c) $(principal) -o $@
	@ ./$@
	
#Eliminando Temporales
borrar :
	rm principal/*.o principal/*~
