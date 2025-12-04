#include <iostream>
using namespace std;



//Dato de las huertas
struct huertas_registradas {
	int id_huerta;
	string barrio;
	char tipo_cultivo;
	float sup_cultivada;
	float prod_mensual;
	string fertilizante;
	};
	
char mas_frecuente(huertas_registradas array[], int cant);

//Funcion para cargar los datos en mi array de huertas
void carga_datos(huertas_registradas array [], int cant_huertas){
	for (int i=0; i<cant_huertas; i++){
		cout<<"Ingrese el identificador de la huerta"<<endl;
		cin>>array[i].id_huerta;
		cout<<"Ingrese el barrio"<<endl;
		cin>>array[i].barrio;
		cout<<"Ingrese el tipo de cultivo"<<endl;
		cin>>array[i].tipo_cultivo;
		cout<<"Ingrese la superficie cultivada"<<endl;
		cin>>array[i].sup_cultivada;
		cout<<"Ingrese la produccion mensual"<<endl;
		cin>>array[i].prod_mensual;
		cout<<"Ingrese si utlizo fertilizante"<<endl;
		cin>>array[i].fertilizante;
	}
}
//Muestro  la cantidad de huertas registradas, el promedio mensual de produccion y de superficie cultivda, el porcentaje de fertilizados
// y el tipo de cultivo mas frecuente
void mostrar (huertas_registradas array[], int cant ){
	float suma=0;
	for (int j=0; j<cant; j++){
		suma+=array[j].prod_mensual;
	}
	float promedio=suma/cant;
	float suma_sup=0;
	for (int l=0; l<cant; l++){
		suma_sup+=array[l].sup_cultivada;
	}
	float promedio_sup=suma_sup/cant;
	int fertilizantes=0;
	int porcentaje;
	for (int k=0; k<cant; k++){
		if (array[k].fertilizante=="Si"){
			fertilizantes++;
		}
	}
	porcentaje=(fertilizantes*100)/cant;
	
	
		cout<<"Cantidad de huertas registradas:  "<<cant<<endl;
		cout<< "Produccion mensual promedio"<<promedio<<endl;
		cout<<"Porcentaje de huertas que usan fertilizante"<<porcentaje<<"%"<<endl;
		cout<<"Promedio de superficie cultivada"<<promedio_sup<<endl;
		cout<<"Tipo de cultivo mas frecuente: "<<mas_frecuente (array, cant)<<endl;
		
	
}


//Me tira el tipo de cultivo mas frecuente
char mas_frecuente(huertas_registradas array[], int cant) {
    int cH = 0, cF = 0, cA = 0, cL = 0, cO = 0;

    for (int i = 0; i < cant; i++) {
     		switch(array[i].tipo_cultivo){
        	case'H': cH++;
        	break;
        	case'F': cF++;
        	break;
        	case'A': cA++;
        	break;
        	case'L': cL++;
        	break;
        	case'O': cO++;
        	break;
        }
    }

    // Comparar para obtener el tipo con mayor cantidad
    int mayor = cH;
    char tipo = 'H';

    if (cF > mayor) {
        mayor = cF;
        tipo = 'F';
    }
    if (cA > mayor) {
        mayor = cA;
        tipo = 'A';
    }
    if (cL > mayor) {
        mayor = cL;
        tipo = 'L';
    }
    if (cO > mayor) {
        mayor = cO;
        tipo = 'O';
    }

    return tipo;
}


//Me muestra la cantidad de cultivos por barrio
void Barrios (huertas_registradas arrayh[], int cant_pb [], string arrayb [], int canth, int cantb){
	for(int i=0; i<canth; i++){
		for (int j=0;j<cantb; j++){
			if (arrayh[i].barrio==arrayb[j]){
				cant_pb[j]++;
			}
		}
	}
	for (int k=0; k<cantb; k++){
		int d=cant_pb[k];
		if(d!=0){
		
		cout<<"Cantidad de huertas en "<<arrayb[k]<<" es de "<<cant_pb[k]<<endl;
	}
	}}
	

void menu(){
	
	cout<<"Seleccione una opcion"<<endl;
	cout<<"1) Cargar y procesar datos de huerta"<<endl;
	cout<<"2) Mostrar resultados"<<endl;
	cout<<"3) Salir"<<endl;

}



int main(int argc, char** argv) {
	const int MAX=100;
	huertas_registradas a_huertas [MAX];
	int respuesta;
	int cant_huertas=0;
	
	int cant_por_barrios [48]{0};
	string barrios [48]{"Agronomia", "Almagro", "Balvanera",
	"Barracas", "Belgrano", "Boedo", "Caballito", "Chacarita", "Coghlan",
	"Colegiales", "Constitucion", "Flores", "Floresta", "La Boca", "La Paternal",
	"Liniers", "Mataderos", "Monte Castro", "Monserrat", "Nueva Pompeya", "Nunez", "Palermo",
	"Parque Avellaneda", "Parque Chacabuco", "Parque Chas", "Parque Patricios", "Puerto Madero",
	"Recoleta", "Retiro", "Saveedra", "San Cristobal", "San Nicolas", "San Telmo",
	"Velez Sarsfield", "Versalles", "Villa Crespo", "Villa del Parque",
	"Villa Devoto", "Villa General Mitre", "Villa Lugano", "Villa Luro",
	"Villa Ortuzar", "Villa Pueyrredon", "Villa Real", "Villa Riachuelo",
	"Villa Santa Rita", "Villa Soldati", "Villa Urquiza"};
	cout<<"Bienvenido"<<endl;
	while(respuesta!=3){
	menu();
	cin>>respuesta;
		if (respuesta==1){
			cout<<" Cuantas huertas desea cargar?"<<endl;
			cin>>cant_huertas;
		
			carga_datos (a_huertas, cant_huertas);
			string res2;
			cout<<"Desea ver los resultados?"<<endl;
			cin>>res2;
			if (res2=="Si"){
			mostrar (a_huertas, cant_huertas);
			Barrios (a_huertas, cant_por_barrios, barrios, cant_huertas, 48);
			cout<< "Tipo de cultivo mas frecuente"<<mas_frecuente  (a_huertas, cant_huertas)<<endl;
		
		 }
		}
		if(respuesta==2 ){
			if(cant_huertas==0){
			
			cout << "No se han cargado datos de huertas" << endl;
			cout  << "Puedes cerrar el programa o volver al menu" << endl;
			cout << " Cerrar el programa=0 | Volver al menu=1" << endl;
			int cerrar;
			cin >> cerrar;
			if(cerrar==0) return 0;}
			
			else {
      		mostrar(a_huertas, cant_huertas);
     		Barrios(a_huertas, cant_por_barrios, barrios, cant_huertas, 48);
        	
    }
			}
		}	return 0;
	}




