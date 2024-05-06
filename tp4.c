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

    // PUNTO 2 - Menú para transferir tareas pendientes a realizadas
    do
    {
        printf("\n*** REALIZACION DE TAREAS ***");
        printf("\n\t1. Marcar como pendiente una nueva tarea");
        printf("\n\t2. Ver tareas pendientes");
        printf("\n\t3. Ver tareas realizadas");
        printf("\n\t4. Finalizar transferencia de tareas");
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
            printf("\n*** TRANSFERENCIA DE TAREAS FINALIZADA ***\n");
            break;
        default:
            printf("\n[!] Ingrese una opcion valida\n");
            break;
        }

    } while (opcion != 4);

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