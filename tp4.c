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
Nodo * crearListaVacia();
Tarea crearTarea();
void insertarNodo(Nodo ** start, Nodo * nuevaTarea);
Nodo * crearNodo(Tarea tarea);
void mostrarLista(Nodo * start);
void liberarMemoria(Nodo ** start);

int main() 
{
    Nodo * tareasPendientes = crearListaVacia();
    Nodo * tareasRealizadas = crearListaVacia();

    int opcion = 0;

    // Menú de opciones para la carga de tareas
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

    mostrarLista(tareasPendientes);
    
    // Libero memoria de las listas
    liberarMemoria(&tareasPendientes);
}

/**
 * Crea una lista enlazada vacía
 */
Nodo * crearListaVacia()
{
    return NULL;
}

/**
 * Solicita al usuario los datos necesarios para crear una nueva Tarea
 */
Tarea crearTarea() {
    printf("\n\n*** INSERTANDO UNA NUEVA TAREA ***");

    Tarea nuevaTarea;
    char buff[100];

    nuevaTarea.TareaID = ultimoId++;
    printf("\n- Tarea ID: %d", nuevaTarea.TareaID);

    fflush(stdin);
    printf("\n\t- Ingrese la descripcion: ");
    gets(buff);
    nuevaTarea.Descripcion = (char *)malloc( (strlen(buff) + 1) * sizeof(char) );
    strcpy(nuevaTarea.Descripcion, buff);

    // Ingreso la duración verificando que sea un número entre 10 y 100
    fflush(stdin);
    int duracion = 0;
    do
    {
        printf("\t- Ingrese la duracion: ");
        scanf("%d", &duracion);

        if ((duracion < 10) || (duracion > 100)) printf("\n\t[!] Duracion invalida [!]\n\n");
    } while ( (duracion < 10) || (duracion > 100) );

    nuevaTarea.Duracion = duracion;

    return nuevaTarea;
}   

/**
 * Inserta un nuevo nodo al final de una lista de tareas
 * 
 * @param start      Cabecera de la lista
 * @param nuevaTarea Nodo a insertar
 */
void insertarNodo(Nodo ** start, Nodo * nuevaTarea)
{
    if (*start == NULL)
    {
        nuevaTarea->Siguiente = *start;
        *start = nuevaTarea;
    }
    else
    {
        Nodo * aux = *start;
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
Nodo * crearNodo(Tarea tarea)
{
    Nodo * nuevoNodo = (Nodo *)malloc(sizeof(Nodo));

    nuevoNodo->T.Descripcion = (char *)malloc( (strlen(tarea.Descripcion) + 1) * sizeof(char) );
    strcpy(nuevoNodo->T.Descripcion, tarea.Descripcion);
    nuevoNodo->T.TareaID = tarea.TareaID;
    nuevoNodo->T.Duracion = tarea.Duracion;

    nuevoNodo->Siguiente = NULL;

    return nuevoNodo;
}

/**
 * Muestra todos los nodos de una lista
 * 
 * @param start Lista enlazada
 */
void mostrarLista(Nodo * start)
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
 * Libera la memoria dinámica asignada a los nodos de la lista
 * 
 * @param start Lista a liberar
 */
void liberarMemoria(Nodo ** start)
{
    while (*start != NULL)
    {
        Nodo *temp = *start;
        *start = (*start)->Siguiente;
        free(temp->T.Descripcion);
        free(temp);
    }
}