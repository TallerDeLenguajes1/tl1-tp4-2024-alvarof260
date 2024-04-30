#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarea
{
    int TareaID;
    char *Descripcion;
    int Duracion;
} Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

void crearListaVacia(Nodo **head);
Tarea *crearTarea(int id, char *desc, int dura);
void insertarNodo(Nodo **head, Tarea *tarea);
void mostrarTareas(Nodo **head);
int generadorID(Nodo **head);
void moverTarea(Nodo **pendientes, Nodo **realizadas, int id);

int main()
{
    Nodo *listasPendientes = NULL;
    Nodo *ListasRealizadas = NULL;
    crearListaVacia(&listasPendientes);
    crearListaVacia(&ListasRealizadas);

    Tarea *tarea1 = crearTarea(generadorID(&listasPendientes), "Tarea a hacer", 60);
    insertarNodo(&listasPendientes, tarea1);
    Tarea *tarea2 = crearTarea(generadorID(&listasPendientes), "Tarea a hacer 2", 120);
    insertarNodo(&listasPendientes, tarea2);

    int opcion;
    do
    {
        printf("\nMenú:\n");
        printf("1. Mostrar tareas pendientes\n");
        printf("2. Mostrar tareas realizadas\n");
        printf("3. Mover tarea de pendientes a realizadas\n");
        printf("4. Salir\n");
        printf("Ingrese su opción: ");
        scanf("%d", &opcion);
        fflush(stdin); // Limpiar el búfer del teclado

        switch (opcion)
        {
        case 1:
            printf("\nTareas Pendientes:\n");
            mostrarTareas(&listasPendientes);
            break;
        case 2:
            printf("\nTareas Realizadas:\n");
            mostrarTareas(&ListasRealizadas);
            break;
        case 3:
            printf("\nIngrese el ID de la tarea a mover de pendientes a realizadas: ");
            int id;
            scanf("%d", &id);
            fflush(stdin);
            moverTarea(&listasPendientes, &ListasRealizadas, id);
            break;
        case 4:
            printf("\nSaliendo del programa...\n");
            break;
        default:
            printf("\nOpción no válida. Inténtelo de nuevo.\n");
            break;
        }
    } while (opcion != 4);

    return 0;
}

void crearListaVacia(Nodo **head)
{
    *head = NULL;
}

Tarea *crearTarea(int id, char *desc, int dura)
{
    Tarea *nuevaTarea = (Tarea *)malloc(sizeof(Tarea));
    nuevaTarea->TareaID = id;
    nuevaTarea->Descripcion = malloc(strlen(desc) + 1);
    strcpy(nuevaTarea->Descripcion, desc);
    nuevaTarea->Duracion = dura;
    return nuevaTarea;
}

void insertarNodo(Nodo **head, Tarea *tarea)
{
    Nodo *nuevoNodo = malloc(sizeof(Nodo));
    nuevoNodo->T = *tarea;

    nuevoNodo->Siguiente = *head;
    *head = nuevoNodo;
}

void mostrarTareas(Nodo **head)
{
    Nodo *aux = *head;
    while (aux != NULL)
    {
        printf("el id: %d\ndescripcion: %s\nduracion de la tarea: %d\n", aux->T.TareaID, aux->T.Descripcion, aux->T.Duracion);
        printf("\n");
        aux = aux->Siguiente;
    }
}

int generadorID(Nodo **head)
{
    if (*head == NULL)
    {
        return 1000;
    }
    else
    {
        int id;
        Nodo *aux = *head;
        while (aux != NULL)
        {
            id = aux->T.TareaID;
            aux = aux->Siguiente;
        }
        id++;
        return id;
    }
}

void moverTarea(Nodo **pendientes, Nodo **realizadas, int id)
{
    Nodo *prev = NULL;
    Nodo *actual = *pendientes;

    while (actual != NULL && actual->T.TareaID != id)
    {
        prev = actual;
        actual = actual->Siguiente;
    }

    if (actual != NULL)
    {
        if (prev != NULL)
            prev->Siguiente = actual->Siguiente;
        else
            *pendientes = actual->Siguiente;

        actual->Siguiente = *realizadas;
        *realizadas = actual;

        printf("Tarea movida de pendientes a realizadas.\n");
    }
    else
    {
        printf("No se encontró una tarea con el ID especificado en la lista de pendientes.\n");
    }
}