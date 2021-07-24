#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>

/* *****************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* Se trata de una lista que contiene datos de tipo void*/

struct lista;
typedef struct lista lista_t;
struct lista_iter;
typedef struct lista_iter lista_iter_t;

/* *****************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/
 
// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

// Devuelve verdadero o falso, según si la lista tiene o no elementos encolados.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento a la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al principio
// de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento a la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al final
// de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t *lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la cola, cuando no está vacía.
void *lista_ver_ultimo(const lista_t* lista);

//Obtiene el largo de la lista
//Pre: la lista fue creada.
//Post: se devolvió el largo de la lista.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void *));

/* *****************************************************************
 *                    PRIMITIVA DEL ITERADOR INTERNO
 * *****************************************************************/
 
 //Va a iterar internamente en la lista recorriendola por completo.
 //Pre: la lista fue creada.
 //Post: se itero sobre toda la lista.
 void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);
 
 /* *****************************************************************
 *                    PRIMITIVAs DEL ITERADOR EXTERNO
 * *****************************************************************/
 
 //Crea un iterador externo para iterar sobre la lista.
 //Pre: la lista fue creada.
 //Post: se devolvio un iterador exteron.
lista_iter_t *lista_iter_crear(lista_t *lista);

//Avanza en la lista. Devuelve true si se pudo avanzar y false en caso contrario.
//Pre: la lista y el iterador externo se crearon.
//Post: Devuelve true solamente si se pudo avanzar.
bool lista_iter_avanzar(lista_iter_t *iter);

//Devuelve el nodo actual sobre el que esta detenido el iterador externo.
//Pre: la lista y el iterador externo se crearon.
//Post: Devuelve el nodo actual.
void *lista_iter_ver_actual(const lista_iter_t *iter);

//Verifica si el iterador externo esta al final de la lista. Devuelve
//true en caso de que sea asi.
//Pre: la lista y el iterador externo se crearon.
//Post: Devuelve true si el iterador externo se encuentra al final de la lista.
bool lista_iter_al_final(const lista_iter_t *iter);

//Destruye el iterador externo.
//Pre: la lista y el iterador externo se crearon.
//Post: se destruye el iterador externo.
void lista_iter_destruir(lista_iter_t *iter);

//Inserta un elemento con el dato en la lista. Si lo puede hacer devuelve true,
//false en caso contrario.
//Pre: la lista y el iterador externo se crearon.
//Post: Devuelve true si pudo insertar el elemento con el dato.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

//Elimina el elemento actual de la lista en cual esta detenido el iterador externo
//y devuelve su dato. Devuelve NULL en caso de que la lista este vacia.
//Pre: la lista y el iterador externo se crearon.
//Post: El elemento actual es borrado y se devuelve su valor o NULL si no hay elemento.
void *lista_iter_borrar(lista_iter_t *iter);

/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/
 
 void pruebas_cola_alumno(void);

#endif
