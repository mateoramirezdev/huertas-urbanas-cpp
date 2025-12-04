#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_CADENA 50
#define CANT_GENEROS 20
#define MAX_AUTORES 100

using namespace std;

struct Libro {
    char genero[MAX_CADENA];
    int cod_genero;
    char titulo[MAX_CADENA];
    char autor[MAX_CADENA];
    int paginas;
};

struct NodoLibro {
    Libro libro;
    NodoLibro* sig;
};
struct Autor{  
	char nombre[MAX_CADENA];
	int cantidadLibros;
	};


void crear_datos() {
    int cant;
    cout << "Cuantos libros desea cargar?" << endl;
    cin >> cant;

    FILE* miArchivo = fopen("ArchivoLibros.dat", "wb");
    if (!miArchivo) {
        cout << "Error al abrir archivo" << endl;
        return;
    }

    Libro data;
    for (int i = 0; i < cant; i++) {
        cout << "Escriba el genero del libro: ";
        cin >> data.genero;
        cout << "Escriba el codigo de genero del libro (1-20): ";
        cin >> data.cod_genero;
        cout << "Escriba el titulo del libro: ";
        cin >> data.titulo;
        cout << "Escriba el autor del libro: ";
        cin >> data.autor;
        cout << "Escriba la cantidad de paginas del libro: ";
        cin >> data.paginas;

        fwrite(&data, sizeof(Libro), 1, miArchivo);
    }
    fclose(miArchivo);
}

NodoLibro* insertarOrdenado(NodoLibro*& p, Libro info) {
    NodoLibro* nuevo = new NodoLibro();
    nuevo->libro = info;
    nuevo->sig = NULL; 
    
    NodoLibro* ant = NULL;
    NodoLibro* aux = p;
 
    while (aux != NULL && aux->libro.paginas < info.paginas) {
        ant = aux;
        aux = aux->sig;
    }

    if (ant == NULL) {
     
        nuevo->sig = p; 
        p = nuevo;      
    } else {
        
        ant->sig = nuevo; 
        nuevo->sig = aux; 
    }
    

    return p;
}


void cargarDatos(NodoLibro* vector_generos[]) {
    FILE* miArchivo = fopen("ArchivoLibros.dat", "rb");
    if (!miArchivo) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }
	long posicionInicio = ftell(miArchivo);
    fseek(miArchivo, 0, SEEK_END);
    long posicionFinal = ftell(miArchivo);
	int cant_libros = (posicionFinal - posicionInicio) / sizeof(Libro);

    
    fseek(miArchivo, posicionInicio, SEEK_SET);

    Libro data;
    for (int i = 0; i < cant_libros; i++) {
        if (fread(&data, sizeof(Libro), 1, miArchivo) == 1) {
            
            
                insertarOrdenado(vector_generos[data.cod_genero - 1], data);
        }
        }
    

    fclose(miArchivo);
}


void encontrarAutorFrecuente(NodoLibro* vector_generos[]){
	char autorFrecuente[MAX_CADENA];

	Autor autores[MAX_AUTORES]; 
	int cantAutores = 0; 
	int encontrado = 0;
	
	for (int i = 0; i < CANT_GENEROS; i++) {
        NodoLibro* actual = vector_generos[i];
        while (actual != NULL) {
       		int encontrado = 0;
			for (int j = 0; j < cantAutores; j++) {
    			if (strcmp(autores[j].nombre, actual->libro.autor) == 0) { 
        			autores[j].cantidadLibros++; 
        			encontrado = 1;  
  	  			}
			}	

			if (!encontrado && cantAutores < MAX_AUTORES) { 
				strcpy(autores[cantAutores].nombre, actual->libro.autor);  
				autores[cantAutores].cantidadLibros = 1; 
    			cantAutores++; 
    		}
 			actual = actual->sig; 
	 	}
	}
	
	int maxAutor = 0; 
    	for (int i = 1; i < cantAutores; i++) { 
        	if (autores[i].cantidadLibros > autores[maxAutor].cantidadLibros) { 
           		maxAutor = i;
        	}
    	}
    
	cout<<"Autor más frecuente: "<<autores[maxAutor].nombre<<" con "<<autores[maxAutor].cantidadLibros<<" libros."<<endl; 
};


void tituloMaxPaginas(NodoLibro* vector_generos[]){
	int maxPaginas = 0;
	char tituloMasPaginas[MAX_CADENA];
	for (int i = 0; i < CANT_GENEROS; i++) { 
        NodoLibro* actual = vector_generos[i];
        while (actual != NULL) { 
   			if (actual->libro.paginas > maxPaginas) {  
        		maxPaginas = actual->libro.paginas; 
        		strcpy(tituloMasPaginas, actual->libro.titulo);  
   			}
    		actual = actual->sig; 
		}
	}
    cout<<"Libro con mayor cantidad de paginas: "<<tituloMasPaginas<<" con "<<maxPaginas<<" páginas."<<endl; 
};

void paginas(NodoLibro* vector_generos[]) {
    int totalLibros = 0;
    int sumaPaginas = 0;

    
    for (int i = 0; i < CANT_GENEROS; i++) {
        NodoLibro* aux = vector_generos[i];
        while (aux != NULL) {
            totalLibros++;
            sumaPaginas += aux->libro.paginas;
            aux = aux->sig;
        }
    }

    cout << "\n RESULTADOS" << endl;
    cout << "Cantidad total de libros registrados: " << totalLibros << endl;

    
    if (totalLibros > 0) {
        int promedio = sumaPaginas / totalLibros;
        cout << "Promedio de paginas por libro: " << promedio << endl;
    } else {
        cout << "No hay libros cargados." << endl;
        return; 
    }
}

void contarPorGenero(NodoLibro* vector_generos[]) {
    int maxLibros = 0;
    int generoMax = -1;

    for (int i = 0; i < CANT_GENEROS; i++) {
        int contador = 0;
        NodoLibro* aux = vector_generos[i];

   
        while (aux != NULL) {
            contador++;
            aux = aux->sig;
        }

        cout << "Genero " << (i + 1) << " -> " << contador << " libros" << endl;

       
        
		
		 
        if (contador > maxLibros) {
            maxLibros = contador;
            generoMax = i + 1;  
    	}
    }

    if (generoMax != -1) {
        cout << "\nEl genero con mas libros es el " << generoMax 
             << " con " << maxLibros << " libros." << endl;
    } else {
        cout << "No hay libros cargados." << endl;
    }
}

void mostrarResultados (NodoLibro*vector_generos[]){
	        contarPorGenero(vector_generos);
			paginas(vector_generos);       
			encontrarAutorFrecuente (vector_generos);
			tituloMaxPaginas(vector_generos);
}


int main() {

    NodoLibro* vector_generos[CANT_GENEROS]={NULL};

    
    cargarDatos(vector_generos); 

    int opcion = 0;
    string respuesta;

    while (opcion != 3) {
        cout << "\n--- MENU ---" << endl;
        cout << "1) Cargar Datos" << endl;
        cout << "2) Mostrar Resultados" << endl;
        cout << "3) Salir" << endl;
        cin >> opcion;

        if (opcion == 1) {
            

            for (int i = 0; i < CANT_GENEROS; i++) {
                vector_generos[i] = NULL; 
            }
            
            cout << "Desea SOBREESCRIBIR el archivo con nuevos libros? (Si/No): ";
            cin >> respuesta;
            
            if (respuesta == "Si" || respuesta == "si") {

                crear_datos(); 
            } 

            cargarDatos(vector_generos);
            cout << "\nDatos leídos/actualizados desde el archivo a la memoria correctamente." << endl;
            
        } else if (opcion == 2) {
           mostrarResultados (vector_generos);
		}
    }

    return 0;
} 
