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

int main()
{
    Nodo *Head = NULL;
    crearListaVacia(&Head);

    Tarea *tarea1 = crearTarea(1000, "Tarea a hacer", 60);
    Tarea *tarea2 = crearTarea(1001, "Tarea a hacer 2", 120);
    insertarNodo(&Head, tarea1);
    insertarNodo(&Head, tarea2);

    mostrarTareas(&Head);

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