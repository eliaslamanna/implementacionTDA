#include "heap.h"
#include "testing.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//funcion de comparacion
int strcmp_heap(const void* a, const void* b){
	return strcmp(a, b);
}
//

static void prueba_crear_heap_vacio()
{
	printf("\n");
	printf("PRUBEAS CREAR HEAP VACIO:\n");
    heap_t* heap = heap_crear(NULL);

    print_test("Prueba heap crear heap vacio", heap);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap esta vacio", heap_esta_vacio(heap));

    heap_destruir(heap, NULL);
    printf("\n");
}

static void prueba_heap_vacio()
{
	printf("PRUEBAS HEAP VACIO\n");
    heap_t* heap = heap_crear(NULL);
    print_test("Prueba heap ver max cuando esta vacio es NULL", heap_ver_max(heap) == NULL);
    print_test("Prueba heap desencolar cuando esta vacio es NULL", heap_desencolar(heap) == NULL);

    heap_destruir(heap, NULL);
    printf("\n");
}

static void prueba_heap_insertar()
{
	printf("PRUEBAS HEAP INSERTAR\n");
	heap_t* heap = heap_crear(strcmp_heap);

	char* valor1 = "a";
	char* valor2 = "c";
	char* valor3 = "b";

	heap_encolar(heap, valor1);
	print_test("Prueba heap inster valor1", strcmp(heap_ver_max(heap), "a") == 0);
	print_test("Prueba cantidad de elementos es 1", heap_cantidad(heap) == 1);
	heap_encolar(heap, valor2);
	print_test("Prueba heap inster valor2", strcmp(heap_ver_max(heap), "c") == 0);
	print_test("Prueba cantidad de elementos es 2", heap_cantidad(heap) == 2);
	heap_encolar(heap, valor3);
	print_test("Prueba heap inster valor3", strcmp(heap_ver_max(heap), "c") == 0);
	print_test("Prueba cantidad de elementos es 3", heap_cantidad(heap) == 3);

	heap_destruir(heap, NULL);
	printf("\n");
}

static void prueba_heap_borrar()
{
	printf("PRUEBAS HEAP BORRAR\n");
	heap_t* heap = heap_crear(strcmp_heap);

	char* valor1 = "b";
	char* valor2 = "c";
	char* valor3 = "a";

	heap_encolar(heap, valor1);
	heap_encolar(heap, valor2);
	heap_encolar(heap, valor3);
	char* valor_c = heap_desencolar(heap);
	print_test("Prueba heap el valor borrado es el correcto", strcmp(valor_c, "c") == 0);
	print_test("Prueba heap max es el correcto", strcmp(heap_ver_max(heap), "b") == 0);
	print_test("Prueba heap cantidad despues de borrar es 2", heap_cantidad(heap) == 2);
	char* valor_b = heap_desencolar(heap);
	print_test("Prueba heap el valor borrado es el correcto", strcmp(valor_b, "b") == 0);
	print_test("Prueba heap max es el correcto", strcmp(heap_ver_max(heap), "a") == 0);
	print_test("Prueba heap cantidad despues de borrar es 1", heap_cantidad(heap) == 1);
	char* valor_a = heap_desencolar(heap);
	print_test("Prueba heap el valor borrado es el correcto", strcmp(valor_a, "a") == 0);
	print_test("Prueba heap quedo vacio tras borrar", heap_esta_vacio(heap));
	print_test("Prueba heap cantidad despues de borrar es 0", heap_cantidad(heap) == 0);

	heap_destruir(heap, NULL);
	printf("\n");
}

static void prueba_heap_crear_arr()
{
	printf("PRUEBAS HEAP CREAR ARR\n");
	void* datos[5] = {"b", "a", "j", "c", "z"};
	void* correcto[5] = {"z", "j", "c", "b", "a"};
	
	heap_t* heap = heap_crear_arr(datos, 5, strcmp_heap);

	bool funciona = true;
	for(size_t i = 0; i < 5; i ++){
		if(heap_desencolar(heap) != correcto[i]){
			funciona = false;
		}
	}

	print_test("Se creo un heap con el array pasado por parametro", funciona);

	heap_destruir(heap, NULL);
	printf("\n");
}

static void prueba_heap_sort()
{
	printf("PRUEBAS HEAP SORT\n");
	void* datos[5] = {"b", "a", "j", "c", "z"};
	char* correcto[5] = {"a", "b", "c", "j", "z"};
	heap_sort(datos, 5, strcmp_heap);

	bool funciona = true;
	for(size_t i = 0; i < 5; i ++){
		if(datos[i] != correcto[i]){
			funciona = false;
		}
	}

	print_test("El array pasado por parametro quedo ordenado", funciona);

	printf("\n");
}

void pruebas_heap_alumno(){
	prueba_crear_heap_vacio();
	prueba_heap_vacio();
	prueba_heap_insertar();
	prueba_heap_borrar();
	prueba_heap_crear_arr();
	prueba_heap_sort();
}