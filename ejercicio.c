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
    Tarea Tarea;
    struct Nodo *sig;
} Nodo;

Nodo *crearLista();
int esListaVacia(Nodo *start);
int generadorID(Nodo *start);
Nodo *crearNodo(int id, char *desc, int dura);
void insertarNodo(Nodo **start, Nodo *tarea);
void mostrar(Nodo *start);
void liberarLista(Nodo *start);
Nodo *desenlazar(Nodo **start, int id);
void filtrarPorId(Nodo *start, Nodo *startR, int id);
void filtrarPorPalabra(Nodo *start, Nodo *startR, char *palabra);

int main()
{
    Nodo *tareasPendientes;
    Nodo *tareasRealizadas;
    tareasPendientes = crearLista();
    tareasRealizadas = crearLista();
    int opcion;
    int opcion2;
    int id;
    char desc[100];
    int dura;
    char palabra[20];
    int opcion3;

    do
    {
        printf("\n\t/***** MENU *****\\\n");
        printf("| 1- crear nueva tarea pendiente    |\n");
        printf("| 2- dejar de agregar nuevas tareas |\n");
        printf("Ingrese su opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("\nCrea la tarea\n");
            printf("Ingrese la descripcion:\n");
            getchar();
            gets(desc);
            printf("Ingrese la duracion:\n");
            scanf("%d", &dura);
            getchar();
            insertarNodo(&tareasPendientes, crearNodo(generadorID(tareasPendientes), desc, dura));
            break;
        case 2:
            printf("Saliendo del programa\n");
        default:
            printf("Ingresaste una opcion no valida\n");
            break;
        }
    } while (opcion != 2);

    do
    {
        printf("\n\t/***** MENU *****\\\n");
        printf("| 1- Mostrar las tareas pendientes        |\n");
        printf("| 2- Mostrar las tareas realizadas        |\n");
        printf("| 3- Cambiar estado de tarea              |\n");
        printf("| 4- Buscar tarea por id o palabra        |\n");
        printf("Ingrese su opcion: ");
        scanf("%d", &opcion2);

        switch (opcion2)
        {
        case 1:
            printf("Tareas pendientes\n");
            mostrar(tareasPendientes);
            break;
        case 2:
            printf("Tareas realizadas\n");
            mostrar(tareasRealizadas);
            break;
        case 3:
            printf("Ingrese el id que desea cambiar de estado: ");
            scanf("%d", &id);
            insertarNodo(&tareasRealizadas, desenlazar(&tareasPendientes, id));
            break;
        case 4:
            printf(" 1- Buscar por id\n");
            printf(" 2- Buscar por palabra clave\n");
            printf("Ingrese la opcion: ");
            scanf("%d", &opcion3);
            if (opcion3 == 1)
            {
                printf("Ingrese el id: ");
                scanf("%d", &id);
                filtrarPorId(tareasPendientes, tareasRealizadas, id);
            }
            else if (opcion3 == 2)
            {
                printf("Ingrese la palabra clave\n");
                scanf("%s", palabra);
                filtrarPorPalabra(tareasPendientes, tareasRealizadas, palabra);
            }

            break;
        }
    } while (opcion2 != 5);

    liberarLista(tareasPendientes);
    liberarLista(tareasRealizadas);
    return 0;
}

Nodo *crearLista()
{
    return NULL;
}

int esListaVacia(Nodo *start)
{
    return start == NULL;
}

int generadorID(Nodo *start)
{
    if (esListaVacia(start))
        return 1000;
    else
    {
        Nodo *aux = start;
        int id = 1000;
        while (aux != NULL)
        {
            id++;
            aux = aux->sig;
        }
        return id;
    }
}

Nodo *crearNodo(int id, char *desc, int dura)
{
    Nodo *nNodo = (Nodo *)malloc(sizeof(Nodo));
    nNodo->Tarea.TareaID = id;
    nNodo->Tarea.Descripcion = (char *)malloc(strlen(desc) + 1);
    strcpy(nNodo->Tarea.Descripcion, desc);
    nNodo->Tarea.Duracion = dura;
    nNodo->sig = NULL;
    return nNodo;
}

void insertarNodo(Nodo **start, Nodo *tarea)
{
    tarea->sig = *start;
    *start = tarea;
}

void mostrar(Nodo *start)
{
    Nodo *aux = start;
    while (aux)
    {
        printf("\n");
        printf("La tarea %d\n", aux->Tarea.TareaID);
        printf("Descripcion: %s\n", aux->Tarea.Descripcion);
        printf("Duracion: %d\n", aux->Tarea.Duracion);
        aux = aux->sig;
    }
}

void liberarLista(Nodo *start)
{
    Nodo *aux;
    while (start)
    {
        aux = start;
        start = start->sig;
        free(aux->Tarea.Descripcion);
        free(aux);
    }
}

Nodo *desenlazar(Nodo **start, int id)
{
    Nodo *actual = *start;
    Nodo *anterior = NULL;

    while (actual && actual->Tarea.TareaID != id)
    {
        anterior = actual;
        actual = actual->sig;
    }

    if (actual)
    {
        if (anterior)
            anterior->sig = actual->sig;
        else
            *start = actual->sig;

        actual->sig = NULL;
        return actual;
    }
    return NULL;
}

void filtrarPorId(Nodo *start, Nodo *startR, int id)
{
    Nodo *aux = start;
    while (aux && aux->Tarea.TareaID != id)
    {
        aux = aux->sig;
    }

    if (aux)
    {
        printf("\n");
        printf("La tarea %d\n", aux->Tarea.TareaID);
        printf("Descripcion: %s\n", aux->Tarea.Descripcion);
        printf("Duracion: %d\n", aux->Tarea.Duracion);
        return;
    }

    aux = startR;

    while (aux && aux->Tarea.TareaID != id)
    {
        aux = aux->sig;
    }

    if (aux)
    {
        printf("\n");
        printf("La tarea %d\n", aux->Tarea.TareaID);
        printf("Descripcion: %s\n", aux->Tarea.Descripcion);
        printf("Duracion: %d\n", aux->Tarea.Duracion);
        return;
    }
    else
        printf("No se encontro la id\n");
}

void filtrarPorPalabra(Nodo *start, Nodo *startR, char *palabra)
{
    Nodo *aux = start;
    int encontrado = 0;

    while (aux)
    {
        if (strstr(aux->Tarea.Descripcion, palabra) != NULL)
        {
            printf("\n");
            printf("La tarea %d\n", aux->Tarea.TareaID);
            printf("Descripcion: %s\n", aux->Tarea.Descripcion);
            printf("Duracion: %d\n", aux->Tarea.Duracion);
            encontrado = 1;
        }
        aux = aux->sig;
    }

    aux = startR;
    while (aux)
    {
        if (strstr(aux->Tarea.Descripcion, palabra) != NULL)
        {
            printf("\n");
            printf("La tarea %d\n", aux->Tarea.TareaID);
            printf("Descripcion: %s\n", aux->Tarea.Descripcion);
            printf("Duracion: %d\n", aux->Tarea.Duracion);
            encontrado = 1;
        }
        aux = aux->sig;
    }

    if (!encontrado)
    {
        printf("No se encontro ninguna palabra clave\n");
    }
}
