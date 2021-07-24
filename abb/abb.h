#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//Struct del abb
typedef struct abb abb_t;

//Struct del abb_iter
typedef struct abb_iter abb_iter_t;

// Tipo de función para comparar clave
typedef int (*abb_comparar_clave_t) (const char *, const char *);

// Tipo de función para destruir dato
typedef void (*abb_destruir_dato_t) (void *);

/* Crea el abb
*/
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

/* Guarda un elemento en el abb, si la clave ya se encuentra en la
 * estructura, la reemplaza. De no poder guardarlo devuelve false.
 * Pre: La estructura abb fue inicializada
 * Post: Se almacenó el par (clave, dato)
 */
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

/* Borra un elemento del abb y devuelve el dato asociado.  Devuelve
 * NULL si el dato no estaba.
 * Pre: La estructura abb fue inicializada
 * Post: El elemento fue borrado de la estructura y se lo devolvió,
 * en el caso de que estuviera guardado.
 */
void *abb_borrar(abb_t *arbol, const char *clave);

/* Obtiene el valor de un elemento del abb, si la clave no se encuentra
 * devuelve NULL.
 * Pre: La estructura abb fue inicializada
 */
void *abb_obtener(const abb_t *arbol, const char *clave);

/* Determina si clave pertenece o no al abb.
 * Pre: La estructura abb fue inicializada
 */
bool abb_pertenece(const abb_t *arbol, const char *clave);

/* Devuelve la cantidad de elementos del abb.
 * Pre: La estructura abb fue inicializada
 */
size_t abb_cantidad(abb_t *arbol);

/* Destruye la estructura liberando la memoria pedida y llamando a la función
 * destruir para cada par (clave, dato).
 * Pre: La estructura abb fue inicializada
 * Post: La estructura abb fue destruida
 */
void abb_destruir(abb_t *arbol);

/*Funcion del iterador interno
 * Itera todos los elementos del abb, aplicando en cada elemento la funcion visitar
 * Pre: La estructura abb fue inicializada
 */
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);




/* Crea el iterador del abb
 * Pre: La estructura abb fue inicializada
 */
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

/* Avanza el iterador
 * Pre: El iterador fue inicializado
 */
bool abb_iter_in_avanzar(abb_iter_t *iter);

/* Devuelve el dato de la posicion actual del iterador
 * Pre: El iterador fue inicializado
 */
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

/* Devuelve un bool dependiendo de si el iterador esta en el final o no
 * Pre: El iterador fue inicializado
 * Post: Devuelve true si el iterador esta en el final del abb; caso contrario devuelve false
 */
bool abb_iter_in_al_final(const abb_iter_t *iter);

/* Destruye el iterador
 * Pre: El iterador fue inicializado
 * Post: El iterador es destruido
 */
void abb_iter_in_destruir(abb_iter_t* iter);
