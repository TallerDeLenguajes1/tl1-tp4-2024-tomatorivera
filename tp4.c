#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variables globales
int ultimoId = 1000;

// Estructuras
typedef struct Tarea
{
    int TareaID;       // Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
} Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

// Funciones
Nodo *crearListaVacia();
Tarea crearTarea();
void insertarNodo(Nodo **start, Nodo *nuevaTarea);
Nodo *crearNodo(Tarea tarea);
void eliminarNodo(Nodo **start);
void mostrarLista(Nodo *start);
void liberarMemoria(Nodo **start);
Tarea seleccionarTarea(Nodo **start);
Tarea filtrarId(Nodo *lista, int id);
Tarea filtrarPalabra(Nodo *lista, char *palabraClave);
void mostrarTarea(Tarea tarea, char * tipoTarea);

int main()
{
    Nodo *tareasPendientes = crearListaVacia();
    Nodo *tareasRealizadas = crearListaVacia();

    int opcion = 0;

    // PUNTO 1 - Menú de opciones para la carga de tareas pendientes
    do
    {
        printf("\n*** CARGA DE TAREAS ***");
        printf("\n\t1. Insertar una nueva tarea pendiente");
        printf("\n\t2. Finalizar carga de tareas");
        printf("\n> Digite su opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            insertarNodo(&tareasPendientes, crearNodo(crearTarea()));
            break;
        case 2:
            printf("\n*** CARGA DE TAREAS FINALIZADA ***\n");
            break;
        default:
            printf("\n[!] Ingrese una opcion valida\n");
            break;
        }

    } while (opcion != 2);

    // PUNTO 2 y 3 - Menú para transferir tareas pendientes a realizadas, y ver tareas tanto pendientes como realizadas
    // PUNTO 4 - Implementación del módulo de busqueda
    do
    {
        printf("\n*** MENU DE OPERACIONES ***");
        printf("\n\t1. Marcar como pendiente una nueva tarea");
        printf("\n\t2. Ver tareas pendientes");
        printf("\n\t3. Ver tareas realizadas");
        printf("\n\t4. Filtrar tarea por ID");
        printf("\n\t5. Filtrar tarea por palabra clave");
        printf("\n\t6. Finalizar transferencia de tareas");
        printf("\n> Digite su opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf(""); // C no me permite poner una declaración luego de un label unu
            Tarea tareaTransferida = seleccionarTarea(&tareasPendientes);
            
            // Si el ID de la tarea devuelta es distinto de -1, quiere decir que se seleccionó una tarea existente
            if (tareaTransferida.TareaID != -1) insertarNodo(&tareasRealizadas, crearNodo(tareaTransferida));

            break;
        case 2:
            mostrarLista(tareasPendientes);
            break;
        case 3:
            mostrarLista(tareasRealizadas);
            break;
        case 4:
            fflush(stdin);
            int id;
            char *tipoTarea;

            printf("\n> Digite el ID a buscar: ");
            scanf("%d", &id);

            Tarea tareaFiltrada = filtrarId(tareasPendientes, id);
            if (tareaFiltrada.TareaID == -1) // Si el ID de la tarea es -1, quiere decir que no se encontró una tarea con ese ID en la lista
            {
                tareaFiltrada = filtrarId(tareasRealizadas, id);
                if (tareaFiltrada.TareaID == -1) // Si el ID de la tarea es -1, quiere decir que no se encontró una tarea con ese ID en la lista
                {
                    printf("\n[!] NO se ha encontrado una tarea con el ID especificado [!]\n");
                }
                else
                {
                    mostrarTarea(tareaFiltrada, "TAREA REALIZADA");
                }
            }
            else
            {
                mostrarTarea(tareaFiltrada, "TAREA PENDIENTE");
            }

            break;
        
        case 6:
            printf("\n*** OPERACIONES FINALIZADAS ***\n");
            break;
        default:
            printf("\n[!] Ingrese una opcion valida\n");
            break;
        }

    } while (opcion != 6);

    // Libero memoria de las listas
    liberarMemoria(&tareasPendientes);
    liberarMemoria(&tareasRealizadas);
}

/**
 * Crea una lista enlazada vacía
 */
Nodo *crearListaVacia()
{
    return NULL;
}

/**
 * Solicita al usuario los datos necesarios para crear una nueva Tarea
 */
Tarea crearTarea()
{
    printf("\n\n*** INSERTANDO UNA NUEVA TAREA ***");

    Tarea nuevaTarea;
    char buff[100];

    nuevaTarea.TareaID = ultimoId++;
    printf("\n- Tarea ID: %d", nuevaTarea.TareaID);

    fflush(stdin);
    printf("\n\t- Ingrese la descripcion: ");
    gets(buff);
    nuevaTarea.Descripcion = (char *)malloc((strlen(buff) + 1) * sizeof(char));
    strcpy(nuevaTarea.Descripcion, buff);

    // Ingreso la duración verificando que sea un número entre 10 y 100
    fflush(stdin);
    int duracion = 0;
    do
    {
        printf("\t- Ingrese la duracion: ");
        scanf("%d", &duracion);

        if ((duracion < 10) || (duracion > 100))
            printf("\n\t[!] Duracion invalida [!]\n\n");
    } while ((duracion < 10) || (duracion > 100));

    nuevaTarea.Duracion = duracion;

    return nuevaTarea;
}

/**
 * Inserta un nuevo nodo al final de una lista de tareas
 *
 * @param start      Cabecera de la lista
 * @param nuevaTarea Nodo a insertar
 */
void insertarNodo(Nodo **start, Nodo *nuevaTarea)
{
    if (*start == NULL)
    {
        nuevaTarea->Siguiente = *start;
        *start = nuevaTarea;
    }
    else
    {
        Nodo *aux = *start;
        while (aux->Siguiente)
        {
            aux = aux->Siguiente;
        }
        aux->Siguiente = nuevaTarea;
    }
}

/**
 * Crea un nuevo nodo a partir de los datos de una estructura Tarea enviada por parámetro
 *
 * @param tarea Datos de la nueva tarea a ingresar
 */
Nodo *crearNodo(Tarea tarea)
{
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));

    nuevoNodo->T.Descripcion = (char *)malloc((strlen(tarea.Descripcion) + 1) * sizeof(char));
    strcpy(nuevoNodo->T.Descripcion, tarea.Descripcion);
    nuevoNodo->T.TareaID = tarea.TareaID;
    nuevoNodo->T.Duracion = tarea.Duracion;

    nuevoNodo->Siguiente = NULL;

    return nuevoNodo;
}

/**
 * Elimina un nodo de una lista
 * 
 * @param start Nodo a eliminar
 */
void eliminarNodo(Nodo **start)
{
    Nodo *temp = (*start);
    (*start) = (*start)->Siguiente;
    free(temp->T.Descripcion);
    free(temp);
}

/**
 * Muestra todos los nodos de una lista
 *
 * @param start Lista enlazada
 */
void mostrarLista(Nodo *start)
{
    printf("\n\n*** MOSTRANDO LISTA ***\n");

    while (start != NULL)
    {
        printf("\n- Tarea ID: %d", start->T.TareaID);
        printf("\n\t- Descripcion: %s", start->T.Descripcion);
        printf("\n\t- Duracion: %d", start->T.Duracion);
        printf("\n");

        start = start->Siguiente;
    }
}

/**
 * Permite al usuario seleccionar una Tarea de una lista
 *
 * @param start Cabecera de la lista en donde se buscará la tarea
 * @return Datos de la Tarea seleccionada
 */
Tarea seleccionarTarea(Nodo **start)
{
    printf("\n\n*** SELECCIONANDO UNA TAREA PARA TRANSFERIR ***");

    Nodo **aux = start;
    int idSeleccionado = 0;
    Tarea tareaSeleccionada;

    printf("\n- Digite el ID de la tarea a transferir: ");
    fflush(stdin);
    scanf("%d", &idSeleccionado);

    // Recorro las tareas hasta encontrar la seleccionada o llegar al final de la lista
    while ((*aux != NULL) && ((*aux)->T.TareaID != idSeleccionado))
    {
        aux = &(*aux)->Siguiente;
    }

    // Si aux NO es null, quiere decir que encontré una tarea con el ID indicado
    if ((*aux) != NULL)
    {
        // Almaceno los datos de la tarea seleccionada en una nueva Tarea
        tareaSeleccionada.TareaID = (*aux)->T.TareaID;
        tareaSeleccionada.Descripcion = (char *)malloc((strlen((*aux)->T.Descripcion) + 1) * sizeof(char));
        strcpy(tareaSeleccionada.Descripcion, (*aux)->T.Descripcion);
        tareaSeleccionada.Duracion = (*aux)->T.Duracion;

        // Elimino el nodo correspondiente a la tarea que será transferida
        eliminarNodo(aux);
    }
    else
    {
        printf("\n\n[!] El ID ingresado no corresponde a ninguna tarea [!]\n\n");
        tareaSeleccionada.TareaID = -1;
    }

    return tareaSeleccionada;
}

/**
 * Busca una tarea que tenga un cierto ID en una lista
 * 
 * @param lista Lista enlazada en la cual buscar una tarea con cierto ID
 * @param id    ID a filtrar
 * @return Tarea encontrada, o una tarea con ID -1 en caso de no encontrarse en la lista
 */
Tarea filtrarId(Nodo *lista, int id)
{
    Tarea tareaEncontrada;
    tareaEncontrada.TareaID = -1;
    
    while ( (lista != NULL) && (lista->T.TareaID != id) )
    {
        lista = lista->Siguiente;
    }

    if (lista != NULL)
    {
        tareaEncontrada.TareaID = lista->T.TareaID;
        tareaEncontrada.Descripcion = (char *)malloc( (strlen(lista->T.Descripcion) + 1) * sizeof(char) );
        strcpy(tareaEncontrada.Descripcion, lista->T.Descripcion);
        tareaEncontrada.Duracion = lista->T.Duracion;
    }

    return tareaEncontrada;
}

/**
 * Muestra por pantalla los detalles de una Tarea
 * 
 * @param tarea     Tarea a mostrar
 * @param tipoTarea Tipo de la tarea enviada (pendiente o a realizar)
*/
void mostrarTarea(Tarea tarea, char *tipoTarea)
{
    printf("\n*** Tarea de ID %d (%s) ***", tarea.TareaID, tipoTarea);
    printf("\n\t- Descripcion: %s", tarea.Descripcion);
    printf("\n\t- Duracion: %d\n", tarea.Duracion);
}

/**
 * Libera la memoria dinámica asignada a los nodos de la lista
 *
 * @param start Lista a liberar
 */
void liberarMemoria(Nodo **start)
{
    while (*start != NULL)
    {
        Nodo *temp = *start;
        *start = (*start)->Siguiente;
        free(temp->T.Descripcion);
        free(temp);
    }
}
