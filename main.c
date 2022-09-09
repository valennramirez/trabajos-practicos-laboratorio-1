#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "pila.h"
typedef struct
{
    int legajo;
    char nombreYapellido [30];
    int edad;
    int grado;
} stalumno;

void cargarAlumno (stalumno alumno);
void cargaArchivo (char alumnos[]);
void mostrarAlumno (stalumno alumno);
void muestraArchivo (char alumnos[]);
int cantidadRegistros (char alumnos[]);
void cargarCincoDatos (char alumnos[]);
void seguirCargando (char alumnos[]);
void pilaMayores(char alumnos[], Pila *pila);
int contarMayores (char alumnos[], int edad);
void mostrarPorRango (char alumnos[], int rango1, int rango2);
void mostrarMayores (char alumnos[]);
int contarAlumnosGrado (char alumnos[], int grado);
void copiarArregloToArchivo (char alumnos[],int validos, stalumno arreglo[]);
int registrosConSeekTell(char alumnos[]);
void mostrarArchivoCon10Registros (char alumnos[], int num);
void reescribirDatos(char alumnos[]);
void modificarArchivo (char alumnos[]);

void ejercicio1();
void ejercicio2();
void ejercicio3();
void ejercicio4();
void ejercicio5();
void ejercicio6();
void ejercicio7();
void ejercicio8();
void ejercicio9(); //sin hacer
void ejercicio10(); //sin hacer
void ejercicio11();//sin hacer
void ejercicio12();//sin hacer
void ejercicio13();//sin hacer
void ejercicio14();//sin hacer
void ejercicio15();//sin hacer

int main()
{
    int ejercicio=0;

    printf ("\nQue ejercicio le gustaria ejecutar? (1 a 15): ");
    scanf ("%i", &ejercicio);

    switch (ejercicio)
    {
        case 1:
        {
            ejercicio1();
        }break;
        case 2:
        {
            ejercicio2();
        }break;
        case 3:
        {
            ejercicio3();
        }break;
        case 4:
        {
            ejercicio4();
        }break;
        case 5:
        {
            ejercicio5();
        }break;
        case 6:
        {
            ejercicio6();
        }break;
        case 7:
        {
            ejercicio7();
        }break;
        case 8:
        {
            ejercicio8();
        }break;
        case 9:
        {
            ejercicio9();
        }break;
        case 10:
        {
            ejercicio10();
        }break;
        case 11:
        {
            ejercicio11();
        }break;
        case 12:
        {
            ejercicio12();
        }break;
        case 13:
        {
            ejercicio13();
        }break;
        case 14:
        {
            ejercicio14();
        }break;
        case 15:
        {
            ejercicio15();
        }break;
    }
}

void cargarAlumno (stalumno alumno) ///funcion1
{
    printf ("Numero de legajo ");
    scanf ("%d", &alumno.legajo);
    printf ("Nombre y apellido ");
    fflush(stdin);
    scanf ("%s", alumno.nombreYapellido);
    printf ("Edad ");
    scanf ("%d", &alumno.edad);
    printf ("Grado ");
    scanf ("%d", &alumno.grado);

}

void cargaArchivo (char alumnos[]) ///funcion1
{
    char continuar;

    stalumno alumno;

    FILE *archivo= fopen(alumnos,"wb");

    if (archivo!=NULL)
    {
        do
        {
            cargarAlumno(alumno);
            fwrite (&alumno, sizeof(stalumno), 1, archivo);
            printf ("Desea continuar? s/n");
            fflush(stdin);
            scanf ("%c", &continuar);
        } while (continuar=='s');

        fclose(archivo);
    }
    else
    {
        printf ("Error al abrir archivo");
    }
}
void mostrarAlumno (stalumno alumno) ///funcion2
{
    printf ("Legajo: %d\n", alumno.legajo);
    printf ("Nombre: %s\n", alumno.nombreYapellido);
    printf ("Edad: %d\n", alumno.edad);
    printf ("Grado: %d\n", alumno.grado);
}

void muestraArchivo (char alumnos[]) ///funcion2y5
{
    stalumno alumno;
    FILE *archivo= fopen(alumnos,"rb");

    if (archivo!=NULL)
    {
        while (!feof(archivo))
        {
            fread(&alumno, sizeof (stalumno), 1, archivo);
            if (!feof(archivo))
            {
                mostrarAlumno(alumno);
            }
        }
        fclose(archivo);
    }
    else
    {
        printf ("Error al abrir archivo");
    }
}
int cantidadRegistros (char alumnos[]) ///funcion3
{
    int cant=0;

    stalumno alumno;
    FILE *archivo= fopen(alumnos,"wb");

    if (archivo!=NULL)
    {
        while (!feof(archivo))
        {
            cant=fwrite(&alumno, sizeof (stalumno), 1, archivo);
        }

        fclose(archivo);
    }
    else
    {
        printf ("Error al abrir archivo");
    }

    return cant;
}

void cargarCincoDatos (char alumnos[]) ///funcion4
{
    int i=0;
    char continuar='s';

    stalumno alumno;

    FILE *archivo= fopen(alumnos,"wb");

    if (archivo!=NULL)
    {
        while (i<5 && continuar=='s')
        {
            cargaArchivo(alumnos);
            fwrite (&alumno, sizeof(stalumno), 1, archivo);
            printf ("Desea continuar? s/n");
            fflush(stdin);
            scanf ("%c", &continuar);
            i++;
        }
        fclose(archivo);
    }
    else
    {
        printf ("Error al abrir archivo");
    }
}
void seguirCargando (char alumnos[]) ///funcion6
{
    int i=0;
    char continuar='s';

    stalumno alumno;

    FILE *archivo= fopen(alumnos,"ab");

    if (archivo!=NULL)
    {
        while (continuar=='s')
        {
            fseek(archivo, sizeof (stalumno), SEEK_END);
            cargaArchivo(alumnos);
            fwrite (&alumno, sizeof(stalumno), 1, archivo);
            printf ("Desea continuar? s/n");
            fflush(stdin);
            scanf ("%c", &continuar);
            i++;
        }
        fclose(archivo);
    }
}
void pilaMayores(char alumnos[], Pila *pila) ///funcion7
{
    int num=0;
    stalumno alumno;
    FILE *archivo= fopen(alumnos,"rb");

    if (archivo!=NULL)
    {
        while (fread(&alumno, sizeof (stalumno), 1, archivo)>0)
        {
            if (alumno.edad>17)
            {
                apilar(pila, alumno.edad);
            }
        }
        fclose(archivo);
    }
    else
    {
        printf ("Error al abrir archivo");
    }
}
int contarMayores (char alumnos[], int edad) ///funcion8
{
    int cant;
    stalumno alumno;
    FILE *archivo= fopen(alumnos,"rb");

    if (archivo!=NULL)
    {
        while (fread(&alumno, sizeof (stalumno), 1, archivo)>0)
        {
            if (alumno.edad>edad)
            {
                cant++;
            }
        }
        fclose(archivo);
    }
    else
    {
        printf ("Error al abrir archivo");
    }

    return cant;
}
void mostrarPorRango (char alumnos[], int rango1, int rango2) ///funcion9
{
    stalumno alumno;
    FILE *archivo= fopen(alumnos,"rb");

    if (archivo!=NULL)
    {
        while (fread(&alumno, sizeof (stalumno), 1, archivo)>0)
        {
            if (rango1<alumno.edad && alumno.edad<rango2)
            {
                mostrarAlumno(alumno);
            }
        }

        fclose(archivo);
    }
    else
    {
        printf ("Error al abrir archivo");
    }
}

void mostrarMayores (char alumnos[]) ///funcion10
{
    stalumno alumno;
    FILE *archivo= fopen(alumnos,"rb");

    if (archivo!=NULL)
    {
        while (fread(&alumno, sizeof (stalumno), 1, archivo)>0)
        {
            if (17<alumno.edad)
            {
                mostrarAlumno(alumno);
            }
        }

        fclose(archivo);
    }
    else
    {
        printf ("Error al abrir archivo");
    }
}

int contarAlumnosGrado (char alumnos[], int grado) ///funcion11
{
    int cant;
    stalumno alumno;
    FILE *archivo= fopen(alumnos,"rb");

    if (archivo!=NULL)
    {
        while (fread(&alumno, sizeof (stalumno), 1, archivo)>0)
        {
            if (alumno.grado==grado)
            {
                cant++;
            }
        }
        fclose(archivo);
    }
    else
    {
        printf ("Error al abrir archivo");
    }

    return cant;
}

void copiarArregloToArchivo (char alumnos[],int validos, stalumno arreglo[]) ///funcion12
{
    stalumno alumno;
    FILE *archivo= fopen(alumnos,"wb");

    if (archivo!=NULL)
    {
        for(int i=0; i<validos; i++)
        {
            arreglo[validos]=alumno;
            validos++;
        }
        fclose(archivo);
    }
    else
    {
        printf ("Error al abrir archivo");
    }

}

int registrosConSeekTell(char alumnos[])///funcion13
{
    int cant;
    stalumno alumno;
    FILE *archivo= fopen(alumnos,"rb");

    if (archivo!=NULL)
    {
        fseek (archivo,0, SEEK_END);
        cant=ftell(archivo)/sizeof(stalumno);
        fclose(archivo);
    }
    else
    {
        printf ("Error al abrir archivo");
    }

    return cant;
}

void mostrarArchivoCon10Registros (char alumnos[], int num) ///funcion14
{
    int cant;
    stalumno alumno;
    FILE *archivo= fopen(alumnos,"rb");

    if (archivo!=NULL)
    {
        cant=registrosConSeekTell(alumnos);
    }

    if (cant>9)
    {
        cant=0;
        while (num!=cant)
        {
            cant=registrosConSeekTell(alumnos);
        }
        fclose(archivo);
    }
    else
    {
        printf ("Error al abrir archivo");
    }
}

void reescribirDatos(char alumnos[]) ///funcion15
{
    char continuar='s';
    stalumno alumno;
    FILE *archivo= fopen(alumnos,"ab");

    if (archivo!=NULL)
    {
        while (continuar=='s')
        {
            cargaArchivo(alumnos);
            fwrite (&alumno, sizeof(stalumno), 1, archivo);
            printf ("Desea continuar? s/n");
            fflush(stdin);
            scanf ("%c", &continuar);
        }
        fclose(archivo);
    }
    else
    {
        printf ("Error al abrir archivo");
    }
}
void modificarArchivo (char alumnos[]) ///funcion15
{
    int num;
    stalumno alumno;
    FILE *archivo= fopen(alumnos,"ab");

    if (archivo!=NULL)
    {
        printf ("Si desea añadir datos, presione | 1 | \n Si desea reescribir datos, presione | 2 |");
        scanf ("%d", &num);
    }
    else
    {
        printf ("Error al abrir archivo");
    }

    if (num==1)
    {
        seguirCargando(alumnos);
    }
    else
    {
        reescribirDatos(alumnos);
    }

    fclose(archivo);
}

void ejercicio1()
{
   char alumnos[15]={"alumnos.bin"};
   stalumno alumno;
   cargaArchivo(alumnos);
}
void ejercicio2()
{
    char alumnos[15]={"alumnos.bin"};
    muestraArchivo(alumnos);
}
void ejercicio3()
{
    stalumno alum[50];
    char alumnos[15]={"alumnos.bin"};
    muestraArchivo(alumnos);
    int cant;
    cant=cantidadRegistros(alumnos);

    printf ("La cantidad de archivos cargados es %d", cant);
}
void ejercicio4()
{
    char alumnos[15]={"alumnos.bin"};
    cargarCincoDatos(alumnos);
    muestraArchivo(alumnos);
}

void ejercicio5()
{
    char alumnos[15]={"alumnos.bin"};
    muestraArchivo(alumnos);
}
void ejercicio6()
{
    char alumnos[15]={"alumnos.bin"};
    muestraArchivo(alumnos);
    seguirCargando(alumnos);
    muestraArchivo(alumnos);
}
void ejercicio7()
{
    char alumnos[15]={"alumnos.bin"};
    Pila pila;
    inicpila (&pila);
    pilaMayores(alumnos, &pila);

    mostrar(&pila);
}
void ejercicio8()
{
    char alumnos[15]={"alumnos.bin"};
    int edad, cant;

    printf ("De que edad desea que sean mayores?");
    scanf("%d", &edad);

    cant=contarMayores(alumnos, edad);

    printf ("%d alumnos son mayores que %d", cant, edad);
}
void ejercicio9()
{


}
void ejercicio10()
{

}
void ejercicio11()
{

}
void ejercicio12()
{

}
void ejercicio13()
{

}
void ejercicio14()
{

}
void ejercicio15()
{

}





