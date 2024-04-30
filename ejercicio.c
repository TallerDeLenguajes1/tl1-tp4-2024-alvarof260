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

    mostrarTareas(&listasPendientes);

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
