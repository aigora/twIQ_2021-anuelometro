#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<windows.h>
#define N 1000
		
		
		
struct variables{
	int jugador, partepartida,unidos,asentamiento;
	char nombre[N],nombreimperio[N];
	float dinero,metal,alimentos,madera,poblacion, ejercito;
};


	//	FUNCIONES "MISIONES"
void introduccion (struct variables variable[], int jugador); 				//nombre del jugador y del imperio.
void episodio1 (struct variables variable[], int jugador);					//elige asentamiento.
//EPISODIO 2	(No tiene funcion, porque es sencillo)			//Sale a explorar por primera vez.
int episodio3 (struct variables variable[], int jugador);				//Construccion del barco para la COSTA.		Aparicion de indigenas para MESETA y CORDILLERA
//EPISODIO 4	(No tiene funcion, porque es sencillo. Es igual que el 2)	//Preparacion para la 1 guerra.
int episodio5 (struct variables variable[], int jugador);

	// FUNCIONES "SECUNDARIAS"
void informe(struct variables variable[], int jugador); 						//Le comumnica al jugador el estado de su imperio.
int explorar (struct variables variable[], int jugador);						//Le permite al jugador avanzar y prosperar como imperio.
void final( struct variables variable[], int jugador);						//Le agradece al jugado cuando acaba la partida, y escribe datos en el archivo decisiones.txt
int guardar(struct variables variable[], int jugador);			//Guarda los avances en el archivo historial.txt
int CargaPartida (struct variables variable[], int jugador);			//Carga la informacion del archivo historial.txt para que el jugador pueda seguir la partida, en el mismo punto, habiendo cerrado el programa.

void prueba (struct variables variable[], int jugador);

int main(){
	
	
	int i=1,j=1,jugador,aux;
	FILE *fentrada;	
	FILE *fhistorial;	
	struct variables variable[N];
	char respuesta,compnombre[N];

//MENU INICIAL

	printf("				*EMPIRES GLOBAL OFFENSIVE*\n");	
	printf("	Bienvenido jugador, si quiere empezar a jugar introduzca una E; una S para salir del juego,una C para ver los creditos, o una P para poner la pausa.\n");	
		scanf("%c",&respuesta);
	
do{
	if ((respuesta == 'E')||(respuesta == 'e')){
		printf("	Tienes alguna partida iniciacada ya?? (S para si Y N para no)");
			fflush(stdin);
			scanf("%c",&respuesta);
				while(j!=0){
					if ((respuesta == 'S')||(respuesta == 's')){
						printf("	Perfecto!! Vamos a cargar tu partida. Que numero de jugador eras?? (Numero del 0 al 4 por favor)\n");
							fflush(stdin);
							scanf("%i",&jugador);
							if((jugador<0)||(jugador>4)){
								printf("Ha introducido un numero que no es valido. Reinicie el programa.");
								return 0;
							}
						printf("De acuerdo, vamos a cargar tu partida.\n");
							aux=CargaPartida(variable, jugador);
								if(aux==5){
									printf(" Ha ocurrido un error al leer el archivo 'historial.txt', compruebe si todo está en su sitio en la caarpeta del juego.\n");
									return 0;
								}
								else if(aux==6){
									printf(" No se ha detectado ningun jugador con ese numero. Pruebe de nuevo tras reiniciar.\n");
									return 0;
								}
						j=0;
					}
					else if ((respuesta == 'N')||(respuesta == 'n')){
						printf("	Vas a empezar una nueva partida. Revisa el documento 'historial.txt', que esta en la carpeta del juego, y busca un slot con todo 0's menos el 1º numero. Si no hay elija cualquier otro.\n");
						printf("	Introduce el numero de jugador que quieres tomar. Ten en cuenta que si eliges el nmumero de alguien que tenga su partida iniciada, se perderan sus datos.\n");
							fflush(stdin);
							scanf("%i",&jugador);
							printf("\n");
								aux=CargaPartida(variable, jugador);
									if(aux==5){
										printf(" Ha ocurrido un error al leer el archivo 'historial.txt', compruebe si todo está en su sitio en la caarpeta del juego.\n");
										return 0;
									}
									else if(aux==6){
										printf(" No se ha detectado ningun jugador con ese numero. Pruebe de nuevo tras reiniciar.\n");
										return 0;
									}
						variable[jugador].partepartida=0;
						j=0;
					}
					else{
						printf("El caracter que ha introducino no es valido, por favor, introduzca S para si, y N para no:");
							fflush(stdin);
							scanf("%c",&respuesta);
					}
				}
		i=0;
	}
	else if  ((respuesta == 'S')||(respuesta == 's')){
		printf("	Esperamos verte pronto. Hasta luego !!!");
		return 0;
	}
	else if  ((respuesta == 'P')||(respuesta == 'p')){
		printf("(Presiona ENTER para salir de la pausa)\n");
		getch();	
			printf("	Tienes alguna partida iniciacada ya?? (S para si Y N para no)");
				fflush(stdin);
				scanf("%c",&respuesta);
				j=1;
				while(j!=0){
					if ((respuesta == 'S')||(respuesta == 's')){
						printf("	Perfecto!! Vamos a cargar tu partida. Cual era tu numero de jugador??\n");
							fflush(stdin);
							scanf("%i",&jugador);
							if((jugador<0)||(jugador>4)){
								printf("Ha introducido un numero que no es valido. Reinicie el programa.");
								return 0;
							}
						printf("De acuerdo, vamos a cargar tu partida.\n");
							aux=CargaPartida(variable, jugador);
							if(aux==5){
								printf(" Ha ocurrido un error al escribir en el archivo 'historial.txt', compruebe si todo está en su sitio en la caarpeta del juego.\n");
								return 0;
							}
							else if(aux==6){
									printf(" No se ha detectado ningun jugador con ese numero. Pruebe de nuevo tras reiniciar.\n");
									return 0;
							}
						printf("%i",variable[jugador].partepartida);
						j=0;
						}
					else if ((respuesta == 'N')||(respuesta == 'n')){
						printf("	Vas a empezar una nueva partida.Revisa el documento 'historial.txt', que esta en la carpeta del juego, y busca un slot con todo 0's menos el 1º numero. Si no hay elija cualquier otro.\n");
						printf("	Introduce el numero de jugador que quieres tomar. Ten en cuenta que si eliges el nmumero de alguien que tenga su partida iniciada, se perderan sus datos.\n");
							fflush(stdin);
							scanf("%i",&jugador);
							printf("\n");
								aux=CargaPartida(variable, jugador);
									if(aux==5){
										printf(" Ha ocurrido un error al leer el archivo 'historial.txt', compruebe si todo está en su sitio en la caarpeta del juego.\n");
										return 0;
									}
									else if(aux==6){
										printf(" No se ha detectado ningun jugador con ese numero. Pruebe de nuevo tras reiniciar.\n");
										return 0;
									}
						variable[jugador].partepartida=0;
						j=0;
					}
					else{
						printf("El caracter que ha introducino no es valido, por favor, introduzca S para si, y N para no:");
							fflush(stdin);
							scanf("%c",&respuesta);
					}
				}
		i=0;
	}
	else if  ((respuesta == 'C')||(respuesta == 'c')){
		printf("	Este videojuego, ha sido realizado enteramente por:\n");
		printf("			Angel Rubio Ramos.\n			Federico Javier Laoroga de Villa\n			Alejandro Bejar.\n");
		printf("(Presiona ENTER para empezar)\n");
			getch();
			printf("	Tienes alguna partida iniciacada ya?? (S para si Y N para no)");
				fflush(stdin);
				scanf("%c",&respuesta);
			j=1;
				while(j!=0){
					if ((respuesta == 'S')||(respuesta == 's')){
						printf("	Perfecto!! Vamos a cargar tu partida. Como te llamabas??\n");
							fflush(stdin);
							scanf("%i",&jugador);
							if((jugador<0)||(jugador>4)){
								printf("Ha introducido un numero que no es valido. Reinicie el programa.");
								return 0;
							}
						printf("De acuerdo, vamos a cargar tu partida.");
							aux=CargaPartida(variable, jugador);
							if(aux==5){
								printf(" Ha ocurrido un error al escribir en el archivo 'historial.txt', compruebe si todo está en su sitio en la caarpeta del juego.\n");
								return 0;
							}
							else if(aux==6){
									printf(" No se ha detectado ningun jugador con ese numero. Pruebe de nuevo tras reiniciar.\n");
									return 0;
							}
						j=0;
					}
					else if ((respuesta == 'N')||(respuesta == 'n')){
						printf("Vas a empezar una nueva partida.Revisa el documento 'historial.txt', que esta en la carpeta del juego, y busca un slot con todo 0's menos el 1º numero. Si no hay elija cualquier otro.\n");
						printf("	Introduce el numero de jugador que quieres tomar. Ten en cuenta que si eliges el nmumero de alguien que tenga su partida iniciada, se perderan sus datos.\n");
							fflush(stdin);
							scanf("%i",&jugador);
							aux=CargaPartida(variable, jugador);
								if(aux==5){
									printf(" Ha ocurrido un error al leer el archivo 'historial.txt', compruebe si todo está en su sitio en la caarpeta del juego.\n");
									return 0;
								}
								else if(aux==6){
									printf(" No se ha detectado ningun jugador con ese numero. Pruebe de nuevo tras reiniciar.\n");
									return 0;
								}
								printf("\n");
							variable[jugador].partepartida=0;
						j=0;
					}
					else{
						printf("El caracter que ha introducino no es valido, por favor, introduzca S para si, y N para no:");
							fflush(stdin);
							scanf("%c",&respuesta);
					}
				}
		i=0;
	}
	else {
		printf("El caracter introducido no es valido. Introduzca un caracter valido.\n");
		printf("(E para empezar y S para salir)\n");
			fflush(stdin);
			scanf("%c",&respuesta);
	}
}while (i!=0);



				//*************INTRODUCCION*************//
				
	if(variable[jugador].partepartida==0){
		introduccion(variable, jugador);
		variable[jugador].partepartida++;
	}
	
		//Guardamos los datos de nombres ():	//Guardamos la decision en el fichero de decisiones:
		
					fentrada = fopen("decisiones.txt", "w");
						if (fentrada == NULL){
							printf("Ha ocurrido un error en la escritura del archivo 'decisiones.txt'. Reinicie el programa. Revise la ubicadion del archivo, y si se encuentra en la misma carpeta que el archivo de texto: 'decisiones.txt'.\n");
							return 0;
							}
						fprintf(fentrada,"NUEVA PARTIDA\n	Jugó: %s\n	Su imperio se llamó: %s\n",variable[jugador].nombre, variable[jugador].nombreimperio);
	
	
	// EMPEZAMOS  CON EL JUEGO //*******************************************************************************************************************************************************

		// EMPEZAMOS CON LA TOMA DE DECISIONES --> variable[jugador].variable[jugador].asentamiento
	if(variable[jugador].partepartida==1){
		episodio1(variable, jugador);
		variable[jugador].partepartida++;
					
			//Guardamos la decision en el fichero de decisiones:
						if(variable[jugador].asentamiento==1){fprintf(fentrada,"variable[jugador].asentamientoinicial---> COSTA\n");	}
						else if(variable[jugador].asentamiento==2){fprintf(fentrada,"Asentamiento inicial---> CORDILLERA\n");	}	
						else {fprintf(fentrada,"Asentamiento inicial---> MESETA\n");	}
	
			if (aux==0){
				final(variable, jugador);
				return 0;
			}
			
		//Guardamos partida
		printf("\n\n");
			if (guardar(variable, jugador)==0){
				printf(" Ha ocurrido un error al escribir en el archivo 'historial.txt', compruebe si todo está en su sitio en la caarpeta del juego.\n");
				return 0;
			}
	}

		//**************  declaramos los VALORES INICIALES de las variables (iguales para todos)  ***************//
		if (variable[jugador].partepartida==2){
			variable[jugador].dinero=100;
			variable[jugador].poblacion=10;
			variable[jugador].ejercito=5;
			variable[jugador].metal=0;
			variable[jugador].alimentos=0;
			variable[jugador].madera=0;
			variable[jugador].unidos=0;
				//comunicamos al jugador
				informe(variable, jugador);
					printf("\n\n");
		}
				
					
		
		
		
	//2º EPISODIO: Exploracion ******************* 2 ************** 2 ************ 2 ************* 2 ************ 2 ************* 2 ************ 2 ************* 2 ***************//
	
			// Para este poco código, no merece la pena hacer una fincion a parte, se queda asi.
	if(variable[jugador].partepartida==2){
			if(explorar(variable,jugador)==0) {
				// Final ya está incluido en Explorar
				return 0;
			}
		informe(variable, jugador);
		variable[jugador].partepartida++;

					//Guardamos partida
			if (guardar(variable, jugador)==0){
				printf(" Ha ocurrido un error al escribir en el archivo 'historial.txt', compruebe si todo está en su sitio en la caarpeta del juego.\n");
				return 0;
			}
	
		}
	
	
	//ANTES TENEMOS QUE HACER ACLARACIONES SOBRE COMO FUNCIONANAN LAS GUERRAS Y COMO SE POSICIONAN LOS PUEBLOS EN FUNCION DE SU ASENTAMIENTO.
		printf("\n");
	printf("	Te vamos a explicar como se distribuyen los imperios en El continente:\n");		printf("\n\n\n");
	printf("	Veras; %s, se encuentra en la siguiente posicion gegrafica con respecto al resto de imperios cercanos:\n",variable[jugador].nombreimperio);
	
		//PRESENTACION DE LOS IMPERIOS EN FUNCION DEL variable[jugador].variable[jugador].asentamiento
		if(variable[jugador].asentamiento==1){
			printf("	Al rededor nuestro, tenemos 4 imperios grandes. Sus nombres en clave son, por orden de cercania a la capital: 'Alfa','Beta''Gamma','Delta'.\n");
				printf("\n");
				printf("		La verdad es que el imperio Alfa es el que menos te debe preocupar, porque acaba de salir de una crisis social y economica y no parece que tenga muchas ganas de pelear. Puedes aprobechar eso para tratar de llegar a acuerdos, o directamente llevamos al ejército.\n");
				printf("\n");
				printf("		El imperio Beta, está posicionado en una peninsula al norte de %s. Se llega antes por agua que por tierra. Actrualmente se encuentra en expansion.\n",variable[jugador].nombreimperio);
				printf("\n");
				printf("		El imperio Gamma, está algo alejado, pero no tanto como el Delta.Estos dos tienen asuntos por resolver, por la hija del rey de Gamma y el principe de Delta, que al parecer tienen sus cositas en comun; aunque aun es prnto para saber si terminaran en guerra o en alienza... Todo se vera con el tiempo.\n");
				printf("\n");
				printf("		Por ultimo, el imperio Delta, es el mas alejado; a mas de dos dias de camino. Es un imperio de los mas potentes, ten seguro que como hagan bien las cosas... tienes poco a lo que recurrir para tratar de ganarles la batalla.\n");
		}	
		else if(variable[jugador].asentamiento==2){
			printf("	Al rededor nuestro, tenemos 4 imperios grandes. Sus nombres en clave son, por orden de cercania a la capital: 'Alfa','Beta''Gamma','Delta'.\n");	
				printf("\n");
				printf("		La verdad es que el imperio Alfa es el que menos te debe preocupar, porque acaba de salir de una crisis social y economica y no parece que tenga muchas ganas de pelear. Puedes aprobechar eso para tratar de llegar a acuerdos, o directamente llevamos al ejército.\n ");
				printf("\n");
				printf("		El imperio Beta, está en expansion. TIENES SUERTE... creo. Su emperador es tu primo!! Eso te puede servir para llegar a pactos de familia. Aunque tambien ten en cuenta que te conoce a la perfeccion, no intentes colarsela que te tiene fichado.\n");
				printf("\n");
				printf("		El imperio Gamma, está algo alejado, pero no tanto como el Delta.Estos dos tienen asuntos por resolver, por la hija del rey de Gamma y el principe de Delta, que al parecer tienen sus cositas en comun; aunque aun es prnto para saber si terminaran en guerra o en alienza... Todo se vera con el tiempo.\n");
				printf("\n");
				printf("		Por ultimo, el imperio Delta, es el mas alejado; a mas de dos dias de camino. Es un imperio de los mas potentes, ten seguro que como hagan bien las cosas... tienes poco a lo que recurrir para tratar de ganarles la batalla.\n");
			}
		else{
			printf("	Al rededor nuestro, tenemos 4 imperios grandes. Sus nombres en clave son, por orden de cercania a la capital: 'Alfa','Beta''Gamma','Delta'.\n");	
				printf("\n");
				printf("		La verdad es que el imperio Alfa es el que menos te debe preocupar, porque acaba de salir de una crisis social y economica y no parece que tenga muchas ganas de pelear. Puedes aprobechar eso para tratar de llegar a acuerdos, o directamente llevamos al ejercito.\n ");
				printf("\n");
				printf("		El imperio Beta, se encuentra en un momento complicado, acaba de estallar la revolucion del pueblo por los excesivos impuestos. Mantente atento porque nunca se sabe por donde salen estas cosas. Imaginate que a algun iluminado de %s se le ocurre imitarles... tu cargo de emperador estaria en peligro %s. Solo queria avisarte.\n",variable[jugador].nombreimperio,variable[jugador].nombre);
				printf("\n");
				printf("		El imperio Gamma, esta algo alejado, pero no tanto como el Delta. Estos dos tienen asuntos por resolver, por la hija del rey de Gamma y el principe de Delta, al parecer tienen una historia rocambolesca en comun; aunque aun es prnto para saber si terminaran en guerra o en alienza... Todo se vera con el tiempo.\n");
				printf("\n");
				printf("		Por ultimo, el imperio Delta, es el mas alejado; a mas de dos dias de camino. Es un imperio de los mas potentes, ten seguro que como hagan bien las cosas... tienes poco a lo que recurrir para tratar de ganarles la batalla.\n");
			}
		printf("\n\n\n\n");
	
	//3º EPISODIO: Gastar o ganar dinero (Declaracion de guerara):******************* 2 ************** 2 ************ 2 ************* 2 ************ 2 ************* 2 ************ 2 ************* 2 ***************

	if(variable[jugador].partepartida==3){
		printf("	Asi es como estan las cosas en %s, %s:\n",variable[jugador].nombreimperio,variable[jugador].nombre);
		informe(variable, jugador);
		aux=episodio3(variable, jugador);
		variable[jugador].partepartida++;
	
	
				//Guardamos lo decidido en decisiones.txt
					if (aux==0){
						fprintf(fentrada,"%s no debió haber construido el barco.",variable[jugador].nombre);
						final(variable, jugador);
						return 0;
					}
					else if(aux==1){	fprintf(fentrada,"%s decidió atacar a las personas que se acercaron a %s. Esto provocó tensiones con el imperio alfa que ya \n",variable[jugador].nombre,variable[jugador].nombreimperio);		}
					else if(aux==2){		fprintf(fentrada,"%s decidió NO atacar a las personas que se acercaron a %s\n",variable[jugador].nombre,variable[jugador].nombreimperio);	}
					else if(aux==3){variable[jugador].unidos=1;}
					else{variable[jugador].unidos=0;}
			
		if (guardar(variable, jugador)==0){
				printf(" Ha ocurrido un error al escribir en el archivo 'historial.txt', compruebe si todo está en su sitio en la caarpeta del juego.\n");
				return 0;
			}
			
	}
	
	//4º EPISODIO: Declaracion de guerra y exploracion.****************************** 3************** 3 ************ 3 ************* 3 ************ 3 ************* 3 ************ 3 ********* 3 **************
	
	if (variable[jugador].partepartida==4){
			printf("	Toca salir a explorar... a ver que nos encontramos hoy!\n");
		if(explorar(variable, jugador)==0) {
			final(variable, jugador);
			return 0;
		}
	informe(variable, jugador);
		if (guardar(variable, jugador)==0){
			printf(" Ha ocurrido un error al escribir en el archivo 'historial.txt', compruebe si todo está en su sitio en la caarpeta del juego.\n");
			return 0;
		}
	variable[jugador].partepartida++;
	}

	
	//5º EPISODIO: 1ª GUERRA****************************** 4 ************** 4 ******************* 4 ************* 4 ************ 4 ************* 4 *********** 4 ******** 4 *****
	if (variable[jugador].partepartida==5){
		if (episodio5(variable, jugador)==0){
			//No ponemos aqui la funcion final porque en este caso ya estaba puesto dentro de episodio5
			return 0;
		}
		if (guardar(variable, jugador)==0){
			return 0;
		}
		variable[jugador].partepartida++;
	}

	
	if (variable[jugador].partepartida==6){	//Igualamos a 0 todas las variable para "desalojar el hueco" 
		variable[jugador].partepartida=0;
		variable[jugador].nombre[N]={'V','A','C','I','O','\0',};
		variable[jugador].nombreimperio[N]={"VACIO"};
		variable[jugador].poblacion=0;
		variable[jugador].ejercito=0;
		variable[jugador].alimentos=0;
		variable[jugador].metal=0;
		variable[jugador].madera=0;
		variable[jugador].dinero=0;
		variable[jugador].unidos=0;
		variable[jugador].asentamiento=0;	
	}
	final(variable, jugador);
	fclose(fentrada);
return 0;	
}

//************************************		FUNCIONES 	***************************************		FUNCIONES		***************************************//

													//*************	EPISODIOS	*****************//

void introduccion (struct variables variable[], int jugador){
	
	int i=1;
	char respuesta,aux[N];
		//PEDIMOS NOMBRE AL USUARIO Y preguntamos si es novato. Si lo es, le explicamos el juego.
			// Preguntamos el nombre
	
			printf("		Empecemos entonces!!\n\n	Antes de nada, te recomendamos que pongas la pantalla completa, te va a tocar leer bastante xD.\n 	Te recordamos ademas, que cuando acabes la partida, tendras un resumen de tus decisiones en la misma carpeta donde tengas el juego, en el archivo llamado 'decisiones'\n	Dinos un nombre con el que referirnos a ti:\n");	
				fflush(stdin);
				gets(variable[jugador].nombre);
		
				//Preguntamos si conoce el juego, si no, se lo explicamos 
			printf("	Nos dirigiremos hacia ti como %s a partir de ahora.\n",variable[jugador].nombre);
				printf("\n");
			printf("	Dinos %s, eres nuevo en EMPIRES GLOBAL OFFENSIVE?? (EGO para los amigos) Si no lo has hecho nunca te vendria bien una explicacion de como funciona. Quieres que te expliquemos lo basico??\n",variable[jugador].nombre);
			printf("Introduce S para si y N para no:\n");
					fflush(stdin);
					scanf("%c",&respuesta);
				printf("\n");
			
		while (i!=0){ 
			if ((respuesta == 'S')||(respuesta == 's')){
				printf("	Este juego se basa en la creacion de un imperio. Para poder crear, mantener y expandir tu propia superpotencia continental, deberas tener en cuenta una serie de asuntos como la salud y lealtad de tu ejercito, el bienestar de tu pueblo, la relaciones internacionales que tengas con los imperios vecinos, la religon que impantes (o no), tu destreza a la hora de enfrentarte en la guerra, o guerras. Estos asuntos se van a materializar a traves de 4 variables que, como ya sabes, condicionaran el fututro de tu imperio; estas son: la economia de tu imperio ; la lealtad, fuerza y fama de tu ejercito; la cantidad y calidad de los recursos que seas capaz de obtener, y por supuesto, el estado de tu pueblo. Que seria de una nacion, SIN SU PUEBLO!!\n");
				printf("\n");
				printf("	Desde aqui te deseamos fuerza para la batalla y prudencia en tu toma de decisiones.\n Que la suerte juegue de tu lado.\n");
				printf("\n");
				printf("	En definitiva, sera un videojuego donde tienes el poder de escribir el futuro de tu nacion; ya sea desde un trono en tu palacete, o desde el campo de batalla, dándole ejemplo a tus aliados en la batalla. Y para ello tienes que tomar una serie de decisiones que se le plantean teniendo en cuenta todas las variables anteriormente descritas y muchas mas. Ademas de esto, en las guerras (que aunque podrás evitarlas, a veces serán muy provechsas para tu imperio), se te plantearan diferentes minijuegos, adivinanzas, o aquello que el destino te depare a ti y a tu ejercito.\n");
				i=0;
			}
			else if  ((respuesta == 'N')||(respuesta == 'n')){
				printf("Estupendo, entoces nada nos impide empezar con la diversion.\n");
				i=0;
			}
			else {
				printf("El caracter introducido no es valido. Introduzca un caracter valido (S o N).\n");
					fflush(stdin);
					scanf("%c",&respuesta);
			}
		}
		
		printf("\n");
		printf("	Procedamos a la creacion de tu imperio. Lo primero que hay que concretar es el nombre. Este es un momneto importante... tomate tu tiempo, porque no lo podras cambiar despues:\n");
			fflush(stdin);
			gets(aux);
		printf("	Uh! %s? es un buen nombre... Pero necesitas algo mas que eso para conquistar El Contintente!!\n	Sin mas dilacion... EMPECEMOS DE VERDAD\n(presiona ENTER)\n",aux);
		strcpy(variable[jugador].nombreimperio,aux);
		getch();
}


void episodio1 (struct variables variable[], int jugador){			// variable[jugador].asentamiento
	int i=1,aux=0;
	
			printf("\n");
		printf("	Lo segundo que debes elegir, %s, es un buen lugar en el que asentarte al inicio. Posteriormente, este lugar pasara a ser la capital de tu imperio.\n 	Cada localizacion tiene bentajas y desventajas:\n(presiona ENTER)\n",variable[jugador].nombre);
		getch();	
			printf("\n\n");
		
		printf("		ASENTAMIENTO EN LA COSTA:\n");
			printf("	Tendras un rapido crecimiento al inicio debido al comercio maritimo, pero si no eres capaz de aprovecharlo para sacarle el suficiente ventaja a los imperios rivales, te deseo suerte para defenderte en el futuro.\n");
				printf("\n");
		
		printf("		ASENTAMIENTO EN LA CORDILLERA:\n");
			printf("	Aqui , ademas de unas vistas privilegiadas de todo el valle (un matiz clave para la defensa de tu base), encontramos una gran variedad de minerales y metales, e incluso algo de madera. Sin embargo no se ven muchos sitios donde montar un huerto o una granja...\n");
				printf("\n");
		
		printf("		ASENTAMIENTO EN LA MESETA:\n");
			printf("	Este es un territorio complicado la verdad... No se ve ningun tipo de defensa natural que ayude ante un posible ataque enemigo. Sin embargo, esta REPLETO de materiales de todo tipo; tenemos madera, tierras para cultivo, animales que domesticar, una red de cuevas mas o menos cercana con metales y otros minerales....\n");
				printf("	Desde luego que empezar aqui no va a ser facil, pero como sobrevivas al inicio... VAS A SER INDESTRUCTIBLE!!");
					printf("\n\n");
		
					//El ususario lo intyroduce por teclado:
		printf("Introduce un 1 para asentarte en la COSTA.		Introduce un 2 para asentarte en la CORDILLERA.		Introduce un 3 para asentarte en la MESETA\n");
		
			fflush(stdin);
			scanf("%i",&aux);
				do {if ((aux!=1)&&(aux!=2)&&(aux!=3)){
						printf("El caracter introducido no es valido. Introduzca un 1, un 2, o 3.\n");
							fflush(stdin);
							scanf("%i",&aux);
					}
					else{
						i=0;
					}
				}while (i!=0);
		variable[jugador].asentamiento=aux;
		
		if (variable[jugador].asentamiento==1){printf("	Has elegido sabiamente la COSTA.\n");	}
		else if(variable[jugador].asentamiento==2){printf("	Has elegido sabiamente la CORDILLERA.\n");	}
		else if (variable[jugador].asentamiento==3){printf("	Has elegido sabiamente la MESETA.\n");	}	
		else {	printf("ERROR. Por favor reinicie.\n");		}
	
		printf("	[ No te acostumbres a que te digamos todas las consecuencias de tus decisiones. A partir de ahora vas a tener que apaniartelas solito. ]\n");
		printf("\n\n");
}

int episodio3 (struct variables variable[], int jugador) {
	int i,j,aleatorio;
	float aux,resto,total;
	char respuesta,letra;

	
	j=0;
		printf("	Hoy hace un dia esplendido... El pueblo de %s se levanta para tomar un poco el sol y ponerse a trabajar, que el continente no se conquista solo.\n",variable[jugador].nombreimperio);
		
		if (variable[jugador].asentamiento==1){
			printf("	La recolecta que hiciste, no fue demasiado fructifera, por ello seria conveniente que algunos de tus ciudadanos vayan en busca de mas recusos. Para ello necesitamos un barco\n");
			printf("	Ten en cuenta que el resto de pueblos igual prefieren saquear a tus marineros antes de mediar palabra. Ademas del gasto inicial que supone fabricar un barco desde cero.\n");
			printf("(S para construir el barco, N pra no hacerlo)\n");
				fflush(stdin);
				scanf("%c",&respuesta);
					
			i=0; 
				while(i==0){
					if ((respuesta=='S')||(respuesta=='s')){
						printf("			Cuantos recursos quieres gastar en la construccion del barco??:\n");
					//DINERO
						printf("	En dinero (dolares):\n");
							fflush(stdin);
							scanf("f",&aux);		
								variable[jugador].dinero=variable[jugador].dinero-aux;
								total=total+aux;
								if (variable[jugador].dinero<0){ printf("	No tienes suficientes materiales.\n");	return 0;}
					//MADERA
						printf("	En madera (kg):\n");
							fflush(stdin);
							scanf("%f",&aux);		
								variable[jugador].madera=variable[jugador].madera-aux;
								total=total+aux;
								if (variable[jugador].madera<0){ printf("	No tienes suficientes materiales.\n");	return 0;}
					//METAL
						printf("	En metal (kg):\n");
							fflush(stdin);
							scanf("%f",&aux);		
								variable[jugador].metal=variable[jugador].metal-aux;
								total=total+aux;
									if (variable[jugador].metal<0){ printf("	No tienes suficientes materiales.\n");	return 0;}
						
						//INCIDENTE DE LOS OBREROS Y LA COMIDA:
							printf("	Algunos de los obreros que trabajan en el astillero quieren comida (casi 2kg cada uno). Vas a tener que dársela para que no se te revelen.\n	Se la das??\n");
							printf("(S para darsela y N para no:)\n");
								fflush(stdin);
								scanf("%c",&letra);
									j=0;
									while(j==0){
										
										if((letra=='S')||(letra=='s')){ 
											variable[jugador].alimentos = variable[jugador].alimentos-10;
												//Si no tiene comida suficiente:
												if (variable[jugador].alimentos<0){
													printf("Lo siento %s, pero no tienes ni para alimentar a tu pueblo. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}													
											j=1;
										}
										else if((letra=='N')||(letra=='n')){
											printf("	Tienes agallas %s... Por desgacia los obreros no les ha hecho mucha gracia tu decision.\n	Han cogido sus cosas y se han marchado. Ahora sois tres menos en tu imperio...\n",variable[jugador].nombre);
											variable[jugador].poblacion=variable[jugador].poblacion-10;
											j=1;
										}
										else{
											printf("El caracter introducido no es valido. Escriba una S o una N por favor.\n");
												fflush(stdin);
												scanf("%c",&letra);
										}
									}
									
								//RECOMPENSAMOS LA CONSTRUCCION DEL BARCO:
								printf("	Ya han pasado varios dias desde que salieron tus tripulantes a ver que encuentran. Veamnos que les deparo la suerte.\n");
										srand(time(NULL));
										aleatorio= 1+rand()%(11);
										
									if(aleatorio<5){
										printf("	Los marineros traen algo de materiales, nada especial, pero menos da una piedra.\n");
										printf("	Parece que hay menos personas de las que salieron.... No... NO!... Entre los marineros ha habido un par de bajas...\n");
										variable[jugador].alimentos=variable[jugador].alimentos+5*(total*0.7);
										variable[jugador].metal=variable[jugador].metal+18*(total*0.7);
										variable[jugador].madera=variable[jugador].madera+15*(total*0.7);
										variable[jugador].dinero=variable[jugador].dinero-50*(total*0.7);
										variable[jugador].poblacion=variable[jugador].poblacion-3;
											if((variable[jugador].poblacion<0)||(variable[jugador].dinero<0)){
												printf("	Te has quedado sin recursos... HAS PERDIDO.\n");
												return 0;
											}
									}
									else if(5<aleatorio<8){
										printf("	\n");
										printf("	Los marineros traen algo de materiales, nada especial, pero menos da una piedra.\n");
										printf("	Segun dicen los marineros, se cruzaron con algunos de los marineros del impeio Alfa. Y gracias a que en el barco iba uno de los diplomaticos del imperio %s, se ha llegado a un acuero con el imperio vecino. A partir de ahora el imperio alfa se unirá con nosotros HURRA!!",variable[jugador].nombreimperio);
										variable[jugador].alimentos=variable[jugador].alimentos+19+(total*0.7);
										variable[jugador].metal=variable[jugador].metal+25+(total*0.7);
										variable[jugador].madera=variable[jugador].madera+30+(total*0.7);
										variable[jugador].dinero=variable[jugador].dinero+110+(total*0.7);
										variable[jugador].poblacion=variable[jugador].poblacion+20;
										variable[jugador].ejercito=variable[jugador].ejercito+15;
										
										printf("\n	Trás la union diplomatica, el imperio Alfa queda fusionado por completo con nosotros vajo el nmombre de %s, quedando asi:\n",variable[jugador].nombreimperio);
										informe(variable,jugador);
									
									return 3;
									}
									else{
										printf("	Ya han pasado mas de 5 dias desde que salio el barco, y no tenemos noticias... Veremos a ver que ocurre pero me huele a que no van a volver.\n");
										variable[jugador].poblacion=variable[jugador].poblacion-10;
											if(variable[jugador].poblacion<0){
												printf("	Te has quedado sin gente... HAS PERDIDO.\n");
												return 0;
											}
									}
								informe(variable, jugador);
								
							i=1;
						}	//Aqui acaba el 1º IF 
						
						else if((respuesta=='N')||(respuesta=='n')){	//Lo que pasa si NO quiene construir el barco:
							i=1;
							printf("Tu mismo con tu mecanismo amigo... A ver como te las apanias en el futuro sin ni siquiera alimentos para poder mantener al ejercito...");
						}
						else {
							printf("El caracter introducido no es valido. Escriba una S o una N por favor.");
								fflush(stdin);
								scanf("%c",&respuesta);
						}
				}	
		}//Aqui acaba el while del ASENTAMIENTO 1 
					
		else{ //Lo que ocurre en la 2ª ronda para los asentamientos 2 y 3
			printf("	Buenos dias emperador! Hoy ha salido un sol precioso, y podemos ver como %s empieza a coger forma y a ganarse el respeto de los imperios vecinos.\n ",variable[jugador].nombreimperio);
					printf("Quieres salir a la ventana y observar el maravilloso dia que hace??		(S para si y N para no)\n");
						fflush(stdin);
						scanf("%c",&letra);
					//Ver llegar al ejercito alfa
						while(j==0){
							if((letra=='S')||(letra=='s')){
								printf("	Bonito sol... Bonito cielo... Pero... Que es eso que se ve en el horizonte?! NO... NO PUEDE SER!! EL IMPERIO ALFA VIENE CON  TODO SU EJERCITO LISTO PARA LA BATALLA !!! \n");
								printf("	RAPIDO !! Es necesario un comite de emergencia!");
								j=1;
								
							}
							else if((letra=='n')||(letra=='N')){
							j=1;
								printf("	Uno de los altos mandos militares irrumpe en tu habitacion antes incluso de que te puedas levantar de la cama. Casi sin aliento, te avisa de algo bastante grave y urgente que esta ocurriendo:\n");
								printf("	El ejercito del imperio alfa viene con cara de pocos amigos. Debe de ser que los individuos de ayer eran de los suyos. \n");
								printf("		Esto parece que se va a poner interesante...\n");
							}
							else{
								printf("	El caracter introducido no es valido, por favor introduzca una S o una N:\n");
									fflush(stdin);
									scanf("%c",&letra);
							}
						}//Acaba el bucle de la pregunta: ¿SALIMOS A LA VENTANA?
			printf("	Se ve que vienen unas personas hacia %s. Crees que debemos atacarles antes de que ellos nos puedan atacar primero??\n",variable[jugador].nombreimperio);
			printf("(S para si, y N para no)\n");
				fflush(stdin);
				scanf("%c",&respuesta);
			i=0;j=0;
			while(i==0){
				if((respuesta=='S')||(respuesta=='s')){
					i=1;
					printf("AL ATAQUEEEEEEE !!!!!\n");
					
					printf("	Habeis herido a uno de ellos, a otro lo matasteis, y dos de ellos salieron corriendo. Supongo que nunca sabremos quienes eran....\n");
				
					//Hay que seguir con la declaracion de guerra.
					
				return 4;
				}
				else if((respuesta=='n')||(respuesta=='N')){
					i=1;
					printf("AL ATAQUEEEEEEE !!!!! Ah... que no ataquemos... okey, perdon me pudo la emocion xD... Bueno, al caso! BAJAD EL PUENTE!!\n");
					printf("	Tras el saludo y los cordialismos, te das cuenta de que las personas que han entrado son representantes diplomaticos del imperio Alfa. Tras su salida de la crisis social, han decidido tender puentes entre vosotros.\n");
					printf("	Te ofrecen sencillamente una union politica. Fusionar los dos imperios. Y como son conscientes de que no son el imperio más rico de El continente, asuemmen que será bajo el nombre de %s. Lo aceptas??\n",variable[jugador].nombreimperio);
						fflush(stdin);
						scanf("%c",&letra);
						j=0;
						while(j==0){
							if((letra=='S')||(letra=='s')){
								printf("	ESTUPENDO!! Vayamos al despacho del emperador %s a terminar con el papeleo.\n",variable[jugador].nombreimperio);
									variable[jugador].alimentos=variable[jugador].alimentos+19;
									variable[jugador].metal=variable[jugador].metal+25;
									variable[jugador].madera=variable[jugador].madera+30;
									variable[jugador].dinero=variable[jugador].dinero+110;
									variable[jugador].poblacion=variable[jugador].poblacion+30;
									variable[jugador].ejercito=variable[jugador].ejercito+15;
								return 3;
								j=1;
							}
							else if((letra=='n')||(letra=='N')){
							j=1;
								printf("	Uhhhh!! No parece que se lo hayan tomado muy fien la verdad. Se van por donde vinieron, pero algo me indica que la cosa no se quedara asi. Desde el imperio Alfa se habbra tomado como una ofensa, y lo más seguro es que haya represalias...\n		 Solo el tiempo lo dira.\n");	
							return 4;	
							}
							else{
								printf("	El caracter introducido no es valido, por favor introduzca una S o una N:\n");
									fflush(stdin);
									scanf("%c",&letra);
							}
						}//Acaba el bucle
	
					}
				else{
					printf("	El caracter introducido no es valido, por favor introduzca una S o una N:\n");
						fflush(stdin);
						scanf("%c",&respuesta);
				}
			}	//Acaba el bucle de la pregunta: ¿ATACAMOS A LOS QUE SE ACERCAN?
		}//Acaba el 2º movimiento del los asentamientos 2 y 3
return 6;
}

int episodio5 (struct variables variable [], int jugador){
	int i,j,aleatorio;
	int faseguerra=0;
	int victoria;
	float aux,resto;
	char respuesta, letra;
	
	if(variable[jugador].asentamiento==1 && variable[jugador].unidos==1){
		
		printf("\nGracias a la alianza que lograste con el imperio Alfa parece que las cosas estan mas calmadas.");
		printf("\nSin embargo tus nuevos aliados advierten que esta paz no parece que vaya a durar, por lo que se olle por los diferentes reinos, los imperios se estan organizando contra ti.");
		printf("\nLo mas recomendable sería enviar algunos aldeanos a buscar recursos para prepararse para la inminente guerra que se aproxima.");
		printf("\n(Pulsa S para enviar a parte de tu poblacion en busca de recursos)");
		fflush(stdin);
			scanf("%c",&respuesta);
			i=0;
			while(i==0){
				if((respuesta=='S')||(respuesta=='s')){
					aux=0;
					printf("Introduce el numero de pobladores que desea enviar: ");
						scanf("%f",&aux);
						variable[jugador].poblacion=variable[jugador].poblacion-aux;
						
							if (variable[jugador].poblacion<0){
													printf("Lo siento %s, pero te has quedado sin habitantes y tu territorio ha sido invadido. HAS PERDIDO.\n",variable[jugador].nombre); 
													return 0;
												}	
				}
				else if((respuesta=='N'||(respuesta=='n'))){
					printf("\nAlla tu, debes ser consciente que sin suficientes recursos luego no estaras listo para la guerra.");
					return 1;
				}
				else{
					printf("El caracter introducido no es valido. Escriba una S o una N por favor.\n");
												fflush(stdin);
												scanf("%c",&letra);
				}
				
			j=0;
			while(j==0){
			
			printf("\nYa han pasado tres días desde  que tus habitantes salieron en busca de recursos.");
			printf("\nAlguien se acerca al portón de la muralla.Alguien ha llegado.");
										srand(time(NULL));
										aleatorio= 1+rand()%(20);
						if(aleatorio<12){
							printf("\nTus habitantes han llegado y parecen muy contentos.");
							printf("\nEn su camino en busca de materiales han encontrado un poblado asolado por el imperio alfa y un grupo se ha unido a tu causa.");
							printf("\nAdemas parece que han traido bastantes recursos");
							
								variable[jugador].poblacion+=30;
								variable[jugador].dinero+=50;
								variable[jugador].madera+=15;
								variable[jugador].alimentos+=8;
								variable[jugador].metal+=25;
						}
						else if(12<aleatorio<18){
							printf("\nSon algunos de los habitantes que habías enviados y no parecen muy contentos.");
							printf("\nEn su camino en busca de materiales han encontrado un grupo de exploradores del imperio delta.");
							printf("\nVarios de ellos ha perdido la vida y han perdido parte de los recursos que habían conseguido.");
			
								variable[jugador].dinero+=8;
								variable[jugador].madera+=4;
								variable[jugador].alimentos+=2;
								variable[jugador].metal+=13;
							}
						else{
							printf("\nParece que solo ha vuelto uno de tus habitantes.");
							printf("\nAl parecer fueron emboscados por un grupo de exploradores del imperio Delta, fueron emboscados y capturados.");
							printf("\nEste acto no puede quedar indemne, esto es una declaracion de guerra.");
							
								variable[jugador].poblacion+=1;
							}
							j++;
						}
							
			i++;			
		}
		
			if(variable[jugador].asentamiento==1 && variable[jugador].unidos==0){
				printf("\nSe acercan tiempos moviditos, se rumorea que habra una guerra y no tienes ningun aliado, tu imperio es debil.");
				printf("\nDeberias enviar a parte de tu poblacion en busca de recursos.");
				printf("\n(Pulsa S para enviar a parte de tu poblacion en busca de recursos)");
					fflush(stdin);
					scanf("%c",&respuesta);
				
					while(i==0){
				if((respuesta=='S')||(respuesta=='s')){
					aux=0;
					printf("Introduce el numero de pobladores que desea enviar: ");
						scanf("%f",&aux);
						variable[jugador].poblacion=variable[jugador].poblacion-aux;
		
							if (variable[jugador].poblacion<0){
								printf("Lo siento %s, pero te has quedado sin habitantes y tu territorio ha sido invadido. HAS PERDIDO.\n",variable[jugador].nombre); 
								final(variable, jugador);	
								return 0;
							}
				}
				else if((respuesta=='N'||(respuesta=='n'))){
					printf("\nAlla tu, debes ser consciente que sin suficientes recursos luego no estaras listo para la guerra.");
					return 1;
				}
				else{
					printf("El caracter introducido no es valido. Escriba una S o una N por favor.\n");
												fflush(stdin);
												scanf("%c",&letra);
				}
				
			
			while(j==0){
			
			printf("\nYa han pasado tres días desde  que tus habitantes salieron en busca de recursos.");
			printf("\nAlguien se acerca al portón de la muralla.Alguien ha llegado.");
										srand(time(NULL));
										aleatorio= 1+rand()%(20);
						if(aleatorio<12){
							printf("\nTus habitantes han llegado y parecen muy contentos.");
							printf("\nEn su camino en busca de materiales han encontrado un poblado asolado por el imperio alfa y un grupo se ha unido a tu causa.");
							printf("\nAdemas parece que han traido bastantes recursos");
							
								variable[jugador].poblacion+=30;
								variable[jugador].dinero+=50;
								variable[jugador].madera+=15;
								variable[jugador].alimentos+=8;
								variable[jugador].metal+=25;
						}
						else if(12<aleatorio<18){
							printf("\nSon algunos de los habitantes que habías enviados y no parecen muy contentos.");
							printf("\nEn su camino en busca de materiales han encontrado un grupo de exploradores del imperio delta.");
							printf("\nVarios de ellos ha perdido la vida y han perdido parte de los recursos que habían conseguido.");
			
								variable[jugador].dinero+=8;
								variable[jugador].madera+=4;
								variable[jugador].alimentos+=2;
								variable[jugador].metal+=13;
							}
						else{
							printf("\nParece que solo ha vuelto uno de tus habitantes.");
							printf("\nAl parecer fueron emboscados por un grupo de exploradores del imperio Delta, fueron emboscados y capturados.");
							printf("\nEste acto no puede quedar indemne, esto es una declaracion de guerra.");
							
								variable[jugador].poblacion+=1;
							}
							j++;
						}
							
			i++;			
		}
			}
	}

	//Fin del primer if.
	aux=0;
			i=2;
			while(i==2){
			
			printf("\nDebido a los hechos que seacontecen deberias comenzar a preparar un ejercito para hacer frente a los demas ejercitos.");
			printf("\nDebes decidir la cantidad de poblacion que se van a alistar en el ejercito.");
			printf("\nCuanta poblacion decides entrenar??");
				scanf("%f",&aux);
			printf("\nAsí que %.0f habitantes, estas seguro??");
			printf("\nPulsa S para confirmar o N para volver a introducir el numero.");
				fflush(stdin);
				scanf("%c",&respuesta);
				
				if((respuesta=='s'||(respuesta=='S'))){
					if (variable[jugador].poblacion<0){
													printf("Lo siento %s, pero te has quedado sin habitantes y tu territorio ha sido invadido. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}
					else{
					printf("\nDe acuerdo %.0f habitantes se han unido al ejercito.",variable[jugador].poblacion);
					
					variable[jugador].ejercito+=aux;
					variable[jugador].poblacion-=aux;
				}
					aux=0;
				}
				else if((respuesta=='n')||(respuesta=='N')){
					printf("\nDe acuerdo, cuantas tropas deseas enviar pues??");
						fflush(stdin);
						scanf("%f",&aux);
						if (variable[jugador].poblacion<0){
													printf("Lo siento %s, pero te has quedado sin habitantes y tu territorio ha sido invadido. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}
							printf("De acuerdo, entonces %.0f seran enviados a formar filas.",variable[jugador].poblacion);
							variable[jugador].ejercito+=aux;
							variable[jugador].poblacion-=aux;
						}
						else{
					printf("El caracter introducido no es valido. Escriba una S o una N por favor.\n");
												fflush(stdin);
												scanf("%c",&letra);
											}
						i=0;
					}
					//Fin del 2do IF.
					
			
				
					while(faseguerra==0){
						victoria=0;
					
					if(variable[jugador].asentamiento==1 && variable[jugador].unidos==1){
						printf("\nEl ejercito del imperio Beta se aproxima a tus territorios.");
						printf("\nLa guerra es inminente.");
						printf("\ntu ejercito cuenta en este momento con %.0f soldados, recuerda que si tus tropas se quedan en 0 tu imperio llegara a su fin.",variable[jugador].ejercito);
						printf("\nDeseas enviar a tu ejercito a defender??");
						printf("\nIntroduce S para enviar el ejercito y N para no enviarlo: ");
							fflush(stdin);
							scanf("%c",&respuesta);
							i=0;
							while(i==0){
							
							
								if((respuesta=='S')||(respuesta=='s')){
									
										printf("\nTu ejercito ha salido de las murallas para defender la fortaleza.");
										
										srand(time(NULL));
										aleatorio= 1+rand()%(20);
								if(aleatorio<8){
									variable[jugador].ejercito-=3;
										if (variable[jugador].ejercito<0){
													printf("Lo siento %s, pero te has quedado sin ejercito con el que defender tu territorio y otros imperios han aprovechado para conquistarte. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
													victoria++;
												}
												else{
												
									printf("\nHa caido una parte de tu ejercito, sin embargo has vencido.");
									printf("\nHas hecho prisioneros de guerra y les has ofrecido unirse a tu ejercito a cambio de no ser ejecutados.");
									printf("\nGracias a ello las perdidas no han sido tan altas.");
									
								}
							}
							
								else if(9<=aleatorio<=15){
										
										variable[jugador].ejercito-=8;
										variable[jugador].dinero-=20;
										variable[jugador].poblacion-=20;
										variable[jugador].alimentos-=20;
									
										if (variable[jugador].ejercito<0){
													printf("Lo siento %s, pero te has quedado sin ejercito con el que defender tu territorio y otros imperios han aprovechado para conquistarte. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}
											
											 else if (variable[jugador].dinero<0){
													printf("Lo siento %s, sin dinero al no poder pagar el salario a tus soldados estos se han sublebado y han acabado con  tu imperio desde dentro. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}
												
											 else if (variable[jugador].poblacion<0){
													printf("Lo siento %s, pero te has quedado sin poblacion, no hay imperio sin habitantes. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}	
												
											 else if (variable[jugador].alimentos<0){
													printf("Lo siento %s, pero te has quedado sin comida para alimentar a tus subditos, por lo que tanto los soldados como la poblacion se ha sublebado contra ti y te han derrocado. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}	
									
										else{
										
									printf("\nHa caido una gran parte del ejercito, sin embargo has vencido.");
									printf("\nHas hecho prisioneros de guerra y les has ofrecido unirse a tu ejercito a cambio de no ser ejecutados.");
									printf("\nEsto no ha sido bien recibido por parte de tus habitantes por los que algunos se han amotinado y han robado viveres y dinero y han huido uniendose a los otros imperios.");
									
											
										victoria++;	
									}
										
																
												}
											else if(16<=aleatorio<=18){
												printf("\nHa caido tu ejercito integramente, te has quedado sin tropas para defender tu imerio.HAS PERDIDO.");
												return 0;
												victoria=0;
											}
											else{
												printf("\nEl despliegue de tu ejercito ha sido imponente han masacrado a casi todo el ejercito enemigo.");
												printf("\nLos que no han sido asesinados se han unido a tu ejercito por miedo a la ejecucion.");
												
													variable[jugador].ejercito+=30;
													victoria++;
											}
										
								
										
								}
								if((respuesta=='N')||(respuesta=='n')){
									printf("\nDe verdad que no se como has llegado hasta aqui, el ejercito contratio ha entrado en las murallas y ha arrasado con tu territorio.HAS PERDIDO.");
									return 0;
									victoria=0;
								}
								else{
										printf("El caracter introducido no es valido. Escriba una S o una N por favor.\n");
												fflush(stdin);
												scanf("%c",&respuesta);
								}
								i++;
					
				}
			}
							if((variable[jugador].asentamiento==1)&&(variable[jugador].unidos==0)){
									printf("\nEl ejercito del imperio Beta se aproxima a tus territorios.Debido a la mala relacion con el imperio Alfa, el ejercito de este participa en la ofensiva, estas en desentaja.");
						printf("\nLa guerra es inminente.");
						printf("\ntu ejercito cuenta en este momento con %.0f soldados, recuerda que si tus tropas se quedan en 0 tu imperio llegara a su fin.",variable[jugador].ejercito);
						printf("\nDeseas enviar a tu ejercito a defender??");
						i=0;
						while(i==0){
						
						printf("\nIntroduce S para enviar el ejercito y N para no enviarlo: ");
							fflush(stdin);
							scanf("%c",&respuesta);
							
								if((respuesta=='S')||(respuesta=='s')){
									printf("\nTu ejercito ha salido de las murallas para defender la fortaleza.");
										
										srand(time(NULL));
										aleatorio= 1+rand()%(20);
								if(aleatorio<5){
									
									variable[jugador].ejercito-=3;
										if (variable[jugador].ejercito<0){
													printf("Lo siento %s, pero te has quedado sin ejercito con el que defender tu territorio y otros imperios han aprovechado para conquistarte. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}
												else{
												
									printf("\nHa caido una parte de tu ejercito, sin embargo has vencido.");
									printf("\nHas hecho prisioneros de guerra y les has ofrecido unirse a tu ejercito a cambio de no ser ejecutados.");
									printf("\nGracias a ello las perdidas no han sido tan altas.");
								victoria++;
								}
										
							}
								else if(6<=aleatorio<=11){
									
									printf("\nHa caido una gran parte del ejercito, sin embargo has vencido.");
									printf("\nHas hecho prisioneros de guerra y les has ofrecido unirse a tu ejercito a cambio de no ser ejecutados.");
									printf("\nEsto no ha sido bien recibido por parte de tus habitantes por los que algunos se han amotinado y han robado viveres y dinero y han huido uniendose a los otros imperios.");
									
										variable[jugador].ejercito-=8;
										variable[jugador].dinero-=20;
										variable[jugador].poblacion-=20;
										variable[jugador].alimentos-=20;		
										
											if (variable[jugador].ejercito<0){
													printf("Lo siento %s, pero te has quedado sin ejercito con el que defender tu territorio y otros imperios han aprovechado para conquistarte. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}
											
											 if (variable[jugador].dinero<0){
													printf("Lo siento %s, sin dinero al no poder pagar el salario a tus soldados estos se han sublebado y han acabado con  tu imperio desde dentro. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}
												
											 if (variable[jugador].poblacion<0){
													printf("Lo siento %s, pero te has quedado sin poblacion, no hay imperio sin habitantes. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}	
												
											 if (variable[jugador].alimentos<0){
													printf("Lo siento %s, pero te has quedado sin comida para alimentar a tus subditos, por lo que tanto los soldados como la poblacion se ha sublebado contra ti y te han derrocado. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}							
												}
											else if(12<=aleatorio<=18){
												printf("\nHa caido tu ejercito integramente, te has quedado sin tropas para defender tu imerio.HAS PERDIDO.");
												return 0;
												
											}
											else{
												printf("\nEl despliegue de tu ejercito ha sido imponente han masacrado a casi todo el ejercito enemigo.");
												printf("\nLos que no han sido asesinados se han unido a tu ejercito por miedo a la ejecucion.");
												
													variable[jugador].ejercito+=30;
													victoria++;
											}
									
								
							}
							if((respuesta=='N')||(respuesta=='n')){
									printf("\nDe verdad que no se como has llegado hasta aqui, el ejercito contratio ha entrado en las murallas y ha arrasado con tu territorio.HAS PERDIDO.");
									return 0;
					}
					else{
					printf("El caracter introducido no es valido. Escriba una S o una N por favor.\n");
												fflush(stdin);
												scanf("%c",&respuesta);
											}
											i++;
				}
				}
				faseguerra++;
				}
				while(faseguerra==1 && victoria==1){
					
					if(variable[jugador].asentamiento==1 && variable[jugador].unidos==1){
						printf("\nTras la victoria contra el ejercito del imperio Beta este imperio es debil.");
						printf("\nes el momento perfecto para iniciar una ofensiva.");
						printf("\nDeseas enviar a tu ejercito a atacar la capital del imperio Beta??");
						printf("\nIntroduce S para enviar el ejercito y N para no enviarlo: ");
							fflush(stdin);
							scanf("%c",&respuesta);
							i=0;
							
								while(i==0){
									i=0;
									if((respuesta=='S')||(respuesta=='s')){
										
										printf("\nQue cantidad de tropas desea enviar??");
										printf("\nRecuerda que si envias mas cantidad de tropas de las que dispones tu capital quedara desprotegida y seras conquistado.");
											fflush(stdin);
											scanf("%f",&aux);
												if(aux<0){
													printf("\nIntroduce una cantidad valida de tropas.");
													scanf("%f",&aux);
												}
												else{
													printf("\nDe acuerdo, %.0f soldados seran enviados",aux);
														if (variable[jugador].ejercito<0){
													printf("Lo siento %s, pero te has quedado sin ejercito con el que defender tu territorio y otros imperios han aprovechado para conquistarte. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}
													
												}
										srand(time(NULL));
										aleatorio= 1+rand()%(5);
										if(aleatorio<4){
											printf("\n		Tu ejercito ha invadido exitosamente la capital, aumentando así tu poblacion y recursos.");
											variable[jugador].poblacion+=30;
								variable[jugador].dinero+=50;
								variable[jugador].madera+=15;
								variable[jugador].alimentos+=8;
								variable[jugador].metal+=25;
								variable[jugador].ejercito+=aux;
											
										}
										else{
											printf("	Tu ejercito ha salido con las manos vacías.\n");
											printf("	Las tropas del imperio Delta y Omega llegaron antes y derrotaron a la mitad de tus tropas.");
											
												variable[jugador].ejercito+=aux/2;
											
										}
										
									}
									if((respuesta=='S')||(respuesta=='s')){
									printf("\nDebido a esto, la alianza del imperio Delta y Omega terminaron conquistando los resquicios del imperio Beta.");
									
									}
									else{
											printf("El caracter introducido no es valido. Escriba una S o una N por favor.\n");
												fflush(stdin);
												scanf("%c",&respuesta);
									}
									i++;
								}
				}
				if(variable[jugador].asentamiento==1 && variable[jugador].unidos==0){
						printf("\n		Tras la victoria contra el ejercito del imperio Beta este imperio es debil.");
						printf("\n	Es el momento perfecto para iniciar una ofensiva.");
						printf("\n	Deseas enviar a tu ejercito a atacar la capital del imperio Beta??");
						printf("\n(Introduce S para enviar el ejercito y N para no enviarlo)");
							fflush(stdin);
							scanf("%c",&respuesta);
							i=0;
							
								while(i==0){
									i=0;
									if((respuesta=='S')||(respuesta=='s')){
										
										printf("\n		Que cantidad de tropas desea enviar??");
										printf("\n	Recuerda que si envias mas cantidad de tropas de las que dispones tu capital quedara desprotegida y seras conquistado.");
											fflush(stdin);
											scanf("%f",&aux);
												if(aux<0){
													printf("\n	Introduce una cantidad valida de tropas.");
													scanf("%f",&aux);
												}
												else{
													printf("\n	De acuerdo, %.0f soldados seran enviados",aux);
														if (variable[jugador].ejercito<0){
													printf("	Lo siento %s, pero te has quedado sin ejercito con el que defender tu territorio y otros imperios han aprovechado para conquistarte. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}
													
												}
										srand(time(NULL));
										aleatorio= 1+rand()%(8);
										if(aleatorio<5){
											printf("\n	Tu ejercito ha invadido exitosamente la capital, aumentando así tu poblacion y recursos.");
											variable[jugador].poblacion+=30;
								variable[jugador].dinero+=50;
								variable[jugador].madera+=15;
								variable[jugador].alimentos+=8;
								variable[jugador].metal+=25;
								variable[jugador].ejercito+=aux;
											
										}
										else{
											printf("	Tu ejercito ha salido con las manos vacías.");
											printf("	Las tropas del imperio Delta y Omega llegaron antes y derrotaron a la mitad de tus tropas.");
											
											variable[jugador].ejercito+=aux/2;
										}
										
									}
									if((respuesta=='N')||(respuesta=='n')){
									printf("\n		Debido a esto, la alianza del imperio Delta y Omega terminaron conquistando los resquicios del imperio Beta.");
									
									}
									else{
											printf("	El caracter introducido no es valido. Escriba una S o una N por favor.\n");
												fflush(stdin);
												scanf("%c",&respuesta);
									}
									i++;
								}
					
				}
				
				
			faseguerra++;	
				
		}
		//Aqui comienza la fase final de la guerra contra el imperio Delta y Omega
		
		while(faseguerra==2 && victoria==1){
			if(variable[jugador].asentamiento==1 && variable[jugador].unidos==1){
						printf("\n		Los ejercitos de los imperios Delta y Omega se han unido.");
						printf("\n	Esta sera la ultima batalla para poder conquistar todo el territorio.");
						printf("\n	Tu ejercito cuenta en este momento con %.0f soldados, recuerda que si tus tropas se quedan en 0 tu imperio llegara a su fin.",variable[jugador].ejercito);
						printf("\n	Deseas enviar a tu ejercito a defender??");
						printf("\n(Introduce S para enviar el ejercito y N para no enviarlo)");
							fflush(stdin);
							scanf("%c",&respuesta);
							i=0;
							while(i==0){
							
							
								if((respuesta=='S')||(respuesta=='s')){
									
										printf("\nTu ejercito ha salido de las murallas para defender la fortaleza.");
										
										srand(time(NULL));
										aleatorio= 1+rand()%(30);
								if(aleatorio<12){
									variable[jugador].ejercito-=7;
										if (variable[jugador].ejercito<0){
													printf("Lo siento %s, pero te has quedado sin ejercito con el que defender tu territorio y otros imperios han aprovechado para conquistarte. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
													victoria++;
												}
												else{
												
									printf("\nHa caido una parte de tu ejercito, sin embargo has vencido.");
									printf("\nPese a ello los soldados han salido a celebrar la victoria.");
									printf("\nAhora todo el territorio es tuyo. HAS GANADO; ENHORABUENA.");
								}
										
							}
								else if(13<=aleatorio<=21){
									
										variable[jugador].ejercito-=8;
										variable[jugador].dinero-=20;
										variable[jugador].poblacion-=20;
										variable[jugador].alimentos-=20;	
										victoria++;	
										
											if (variable[jugador].ejercito<0){
													printf("Lo siento %s, pero te has quedado sin ejercito con el que defender tu territorio y otros imperios han aprovechado para conquistarte. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}
											
											 else if (variable[jugador].dinero<0){
													printf("Lo siento %s, sin dinero al no poder pagar el salario a tus soldados estos se han sublebado y han acabado con  tu imperio desde dentro. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}
												
											 else if (variable[jugador].poblacion<0){
													printf("Lo siento %s, pero te has quedado sin poblacion, no hay imperio sin habitantes. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}	
												
											 else if (variable[jugador].alimentos<0){
													printf("Lo siento %s, pero te has quedado sin comida para alimentar a tus subditos, por lo que tanto los soldados como la poblacion se ha sublebado contra ti y te han derrocado. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}
												else{
													printf("\nHa caido una gran parte del ejercito, sin embargo has vencido.");
													printf("\nPese a ello los soldados han salido a celebrar con el resto del pueblo.");
												}
														
												}
											else if(22<=aleatorio<=25){
												printf("\nHa caido tu ejercito integramente, te has quedado sin tropas para defender tu imerio.HAS PERDIDO.");
												return 0;
												victoria=0;
											}
											else if(26<=aleatorio<=28){
												printf("\nEl despliegue de tu ejercito ha sido imponente han masacrado a casi todo el ejercito enemigo.");
												printf("\nLos que no han sido asesinados han huido por miedo a la ejecucion.");
												printf("\nAhora todo el territorio es tuyo. HAS GANADO; ENHORABUENA.");
												
													victoria++;
											}
											else{
												printf("\nTu ejercito ha ganado la batalla pero con un gran costo en bajas.");
												printf("\nSe celebra una gran fiesta. Los generales del ejercito van tan borrachos que se empiezan a pelear entre ellos.");
												printf("\nAl final se les pasa el mal rollo entre ellos, pero creen que la culpa de las bajas es tuya y te decapitan.HAS PERDIDO.");
											}
								
										
								}
								else if((respuesta=='N')||(respuesta=='n')){
									printf("\nLo siento, pero no se acepta no por respuesta, el ejercito ha salido, pero ahora cuenta con un tercio menos de posibilidades de ganar por chulo.");
									
										printf("\nTu ejercito ha salido de las murallas para defender la fortaleza.");
										
										srand(time(NULL));
										aleatorio= 1+rand()%(10);
								if(aleatorio<2){
									variable[jugador].ejercito-=7;
										if (variable[jugador].ejercito<0){
													printf("Lo siento %s, pero te has quedado sin ejercito con el que defender tu territorio y otros imperios han aprovechado para conquistarte. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
													victoria++;
												}
												else{
												
									printf("\nHa caido una parte de tu ejercito, sin embargo has vencido.");
									printf("\nPese a ello los soldados han salido a celebrar la victoria.");
									printf("\nAhora todo el territorio es tuyo. HAS GANADO; ENHORABUENA.");
								}
										
							}
								else if(3<=aleatorio<=5){
									
									variable[jugador].ejercito-=8;
										variable[jugador].dinero-=20;
										variable[jugador].poblacion-=20;
										variable[jugador].alimentos-=20;	
										victoria++;	
										
											if (variable[jugador].ejercito<0){
													printf("Lo siento %s, pero te has quedado sin ejercito con el que defender tu territorio y otros imperios han aprovechado para conquistarte. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}
											
											 else if (variable[jugador].dinero<0){
													printf("Lo siento %s, sin dinero al no poder pagar el salario a tus soldados estos se han sublebado y han acabado con  tu imperio desde dentro. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}
												
											 else if (variable[jugador].poblacion<0){
													printf("Lo siento %s, pero te has quedado sin poblacion, no hay imperio sin habitantes. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}	
												
											 else if (variable[jugador].alimentos<0){
													printf("Lo siento %s, pero te has quedado sin comida para alimentar a tus subditos, por lo que tanto los soldados como la poblacion se ha sublebado contra ti y te han derrocado. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}
												else{
												printf("\nHa caido una gran parte del ejercito, sin embargo has vencido.");
												printf("\nPese a ello los soldados han salido a celebrar con el resto del pueblo.");
												printf("\nAhora el territorio es tuyo, has ganado.ENHORABUENA.");
												}
														
												}
											else if(6<=aleatorio<=7){
												printf("\nHa caido tu ejercito integramente, te has quedado sin tropas para defender tu imerio.HAS PERDIDO.");
												return 0;
												victoria=0;
											}
											else if(8<=aleatorio<=9){
												printf("\nEl despliegue de tu ejercito ha sido imponente han masacrado a casi todo el ejercito enemigo.");
												printf("\nLos que no han sido asesinados han huido por miedo a la ejecucion.");
												printf("\nAhora todo el territorio es tuyo. HAS GANADO; ENHORABUENA.");
												
													victoria++;
											}
											else{
												printf("\nTu ejercito ha ganado la batalla pero con un gran costo en bajas.");
												printf("\nSe celebra una gran fiesta. Los generales del ejercito van tan borrachos que se empiezan a pelear entre ellos.");
												printf("\nAl final se les pasa el mal rollo entre ellos, pero creen que la culpa de las bajas es tuya y te decapitan.HAS PERDIDO.");
												
													return 0;
											}
								}
								else{
										printf("El caracter introducido no es valido. Escriba una S o una N por favor.\n");
												fflush(stdin);
												scanf("%c",&respuesta);
								}
								i++;
					
				}
			}
							else if((variable[jugador].asentamiento==1)&&(variable[jugador].unidos==0)){
												printf("\nLos ejercitos de los imperios Delta y Omega se han unido.");
						printf("\nEsta sera la ultima batalla para poder conquistar todo el territorio.");
						printf("\ntu ejercito cuenta en este momento con %.0f soldados, recuerda que si tus tropas se quedan en 0 tu imperio llegara a su fin.",variable[jugador].ejercito);
						printf("\nDeseas enviar a tu ejercito a defender??");
						printf("\n(Introduce S para enviar el ejercito y N para no enviarlo)");
							fflush(stdin);
							scanf("%c",&respuesta);
							i=0;
							while(i==0){
							
							
								if((respuesta=='S')||(respuesta=='s')){
									
										printf("\nTu ejercito ha salido de las murallas para defender la fortaleza.");
										
										srand(time(NULL));
										aleatorio= 1+rand()%(20);
								if(aleatorio<7){
									variable[jugador].ejercito-=7;
										if (variable[jugador].ejercito<0){
													printf("Lo siento %s, pero te has quedado sin ejercito con el que defender tu territorio y otros imperios han aprovechado para conquistarte. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
													
												}
												else{
												
									printf("\nHa caido una parte de tu ejercito, sin embargo has vencido.");
									printf("\nPese a ello los soldados han salido a celebrar la victoria.");
									printf("\nAhora todo el territorio es tuyo. HAS GANADO; ENHORABUENA.");
								}
										
							}
								else if(8<=aleatorio<=15){
									
									variable[jugador].ejercito-=8;
										variable[jugador].dinero-=20;
										variable[jugador].poblacion-=20;
										variable[jugador].alimentos-=20;	
										victoria++;	
										
											if (variable[jugador].ejercito<0){
													printf("Lo siento %s, pero te has quedado sin ejercito con el que defender tu territorio y otros imperios han aprovechado para conquistarte. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}
											
											 else if (variable[jugador].dinero<0){
													printf("Lo siento %s, sin dinero al no poder pagar el salario a tus soldados estos se han sublebado y han acabado con  tu imperio desde dentro. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}
												
											 else if (variable[jugador].poblacion<0){
													printf("Lo siento %s, pero te has quedado sin poblacion, no hay imperio sin habitantes. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}	
												
											 else if (variable[jugador].alimentos<0){
													printf("Lo siento %s, pero te has quedado sin comida para alimentar a tus subditos, por lo que tanto los soldados como la poblacion se ha sublebado contra ti y te han derrocado. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}
												else{
														
									
									printf("\nHa caido una gran parte del ejercito, sin embargo has vencido.");
									printf("\nPese a ello los soldados han salido a celebrar con el resto del pueblo.");
									printf("\nAhora todo el territorio es tuyo. HAS GANADO; ENHORABUENA.");
									
								}
														
												}
											else if(16<=aleatorio<=18){
												printf("\nHa caido tu ejercito integramente, te has quedado sin tropas para defender tu imerio.HAS PERDIDO.");
												return 0;
												victoria=0;
											}
											else if(aleatorio==19){
												printf("\nEl despliegue de tu ejercito ha sido imponente han masacrado a casi todo el ejercito enemigo.");
												printf("\nLos que no han sido asesinados han huido por miedo a la ejecucion.");
												printf("\nAhora todo el territorio es tuyo. HAS GANADO; ENHORABUENA.");
												
													victoria++;
											}
											else{
												printf("\nTu ejercito ha ganado la batalla pero con un gran costo en bajas.");
												printf("\nSe celebra una gran fiesta. Los generales del ejercito van tan borrachos que se empiezan a pelear entre ellos.");
												printf("\nAl final se les pasa el mal rollo entre ellos, pero creen que la culpa de las bajas es tuya y te decapitan.HAS PERDIDO.");
												return 0;
											}
								
										
								}
								if((respuesta=='N')||(respuesta=='n')){
									printf("\nLo siento, pero no se acepta no por respuesta, el ejercito ha salido, pero ahora cuenta con un tercio menos de posibilidades de ganar por chulo.");
									
										printf("\nTu ejercito ha salido de las murallas para defender la fortaleza.");
										
										srand(time(NULL));
										aleatorio= 1+rand()%(10);
								if(aleatorio<2){
									variable[jugador].ejercito-=7;
										if (variable[jugador].ejercito<0){
													printf("Lo siento %s, pero te has quedado sin ejercito con el que defender tu territorio y otros imperios han aprovechado para conquistarte. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
													victoria++;
												}
												else{			printf("\n");
													printf("\nHa caido una parte de tu ejercito, sin embargo has vencido.");
													printf("\nPese a ello los soldados han salido a celebrar la victoria.");
													printf("\nAhora todo el territorio es tuyo. HAS GANADO; ENHORABUENA.");
												}
										
							}
								else if(3<=aleatorio<=5){
									
									variable[jugador].ejercito-=8;
										variable[jugador].dinero-=20;
										variable[jugador].poblacion-=20;
										variable[jugador].alimentos-=20;	
										victoria++;	
										
											if (variable[jugador].ejercito<0){
													printf("Lo siento %s, pero te has quedado sin ejercito con el que defender tu territorio y otros imperios han aprovechado para conquistarte. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}
											
											 else if (variable[jugador].dinero<0){
													printf("Lo siento %s, sin dinero al no poder pagar el salario a tus soldados estos se han sublebado y han acabado con  tu imperio desde dentro. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}
												
											 else if (variable[jugador].poblacion<0){
													printf("Lo siento %s, pero te has quedado sin poblacion, no hay imperio sin habitantes. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}	
												
											 else if (variable[jugador].alimentos<0){
													printf("Lo siento %s, pero te has quedado sin comida para alimentar a tus subditos, por lo que tanto los soldados como la poblacion se ha sublebado contra ti y te han derrocado. HAS PERDIDO.\n",variable[jugador].nombre); 
													final(variable, jugador);	
													return 0;
												}
												else{
														
									
									printf("\nHa caido una gran parte del ejercito, sin embargo has vencido.");
									printf("\nPese a ello los soldados han salido a celebrar con el resto del pueblo.");
									printf("\nAhora el territorio es tuyo, has ganado.ENHORABUENA.");
									
								}
														
												}
											else if(6<=aleatorio<=7){
												printf("\nHa caido tu ejercito integramente, te has quedado sin tropas para defender tu imerio.HAS PERDIDO.");
												return 0;
												victoria=0;
											}
											else if(8<=aleatorio<=9){
												printf("\nEl despliegue de tu ejercito ha sido imponente han masacrado a casi todo el ejercito enemigo.");
												printf("\nLos que no han sido asesinados han huido por miedo a la ejecucion.");
												printf("\nAhora todo el territorio es tuyo. HAS GANADO; ENHORABUENA.");
												
													victoria++;
											}
											else{
												printf("\nTu ejercito ha ganado la batalla pero con un gran costo en bajas.");
												printf("\nSe celebra una gran fiesta. Los generales del ejercito van tan borrachos que se empiezan a pelear entre ellos.");
												printf("\nAl final se les pasa el mal rollo entre ellos, pero creen que la culpa de las bajas es tuya y te decapitan.HAS PERDIDO.");
												
													return 0;
											}
								}
								else{
										printf("El caracter introducido no es valido. Escriba una S o una N por favor.\n");
												fflush(stdin);
												scanf("%c",&respuesta);
								}
								i++;
					
				}
			}
		
		}
	}

//			Se acabaron los episodios
// Funciones que realizan funcionalidades, y no episodios:




void informe(struct variables variable[], int jugador){	//Informamos del estado del imperio:
		printf("	Actualmente, tu imperio cuenta con:\n");
		printf("			%.0f personas. De los cuales, %.0f pertenecen al ejercito.\n",variable[jugador].poblacion,variable[jugador].ejercito);
		printf("			%.1f dolares en las arcas publicas.\n",variable[jugador].dinero);
		printf("			%.2f Kg de madera; %.1f Kg de alimentos; y otros %.2f Kg de metal.\n",variable[jugador].madera,variable[jugador].alimentos,variable[jugador].metal);
		printf("			Estas aliado actualmente con %i imperios.\n",variable[jugador].unidos);
		printf("\n");
}

int explorar (struct variables variable[], int jugador){
	int i,num;
	float protegen;
	printf("	Debes mandar a algunas de las personas a por recursos. Tu eliges a cuantos de los %.0f mandas.\n",variable[jugador].poblacion);
		fflush(stdin);
		scanf("%i",&num);
	protegen=variable[jugador].poblacion*0.68;
	i=0;
	while(i==0){
		if (num==variable[jugador].poblacion*0.9){
			printf("	Lamentamos comunicarte, que tu imperio a sido asaltado por el imperio vecino. A quien se le ocurre dejarla sin nadie que la proteja... De verdad que... EN QUE ESTABAS PENSANDO!!");
			printf("Lo has perdido TODO. Aunque casi no te ha dado tiempo a tener nada....\n 	Este es el final de tu imperio\n");
			printf("	Esperamos que te lo hayas pasado bien en tu corta estancia jungando EGO. Tambien espaeramos que vuelvas pronto.\n HASTA LA PROXIMA!!");
			i=1;
			final(variable, jugador);
			return 0;
		}
		else if((num>variable[jugador].poblacion)||(num<0)){	
			printf("El numero introducido no es valido. Introduzca un numero del 0 al numero de habitantes que tenga %s.\n",variable[jugador].nombreimperio);
				fflush(stdin);
				scanf("%i",&num);
		}
		else{
			if(variable[jugador].asentamiento==1){
				variable[jugador].madera=variable[jugador].madera+3*num;
				variable[jugador].metal=variable[jugador].metal+3*num;
				variable[jugador].alimentos=variable[jugador].alimentos+num*5; 
				variable[jugador].poblacion=variable[jugador].poblacion+variable[jugador].alimentos*1.5;
				variable[jugador].ejercito=variable[jugador].ejercito+variable[jugador].poblacion*1.5;
				variable[jugador].dinero=variable[jugador].dinero+((variable[jugador].madera+variable[jugador].metal+variable[jugador].alimentos)/2.0);
			}
			else if(variable[jugador].asentamiento==2){
				variable[jugador].madera=variable[jugador].madera+1.2*num;
				variable[jugador].metal=variable[jugador].metal+1.8*num;
				variable[jugador].alimentos=variable[jugador].alimentos+num*1.5;
				variable[jugador].poblacion=variable[jugador].poblacion+variable[jugador].alimentos*0.25;
				variable[jugador].ejercito=variable[jugador].ejercito+variable[jugador].poblacion*0.2;
				variable[jugador].dinero=variable[jugador].dinero+((variable[jugador].madera+variable[jugador].metal+variable[jugador].alimentos)*0.3);
			}
			else{   //variable[jugador].asentamientos 2 y 3
				if (num>=protegen){
					variable[jugador].dinero=variable[jugador].dinero-40;
					printf("	Siento mucho tener que ser yo quien te lo diga, pero mandaste demasiadas personas a recolectar. Han venido ladrones, y se han llevado 40 dolares de las arcas publicas. Suerte has tenido de que no se llevasen mas.");
				}
					variable[jugador].madera=variable[jugador].madera+1.9*num;
					variable[jugador].metal=variable[jugador].metal+1.8*num;
					variable[jugador].alimentos=variable[jugador].alimentos+num*2;
					variable[jugador].poblacion=variable[jugador].poblacion+variable[jugador].alimentos*0.25;
					variable[jugador].ejercito=variable[jugador].ejercito+variable[jugador].poblacion*0.2;
					variable[jugador].dinero=variable[jugador].dinero+((variable[jugador].madera+variable[jugador].metal+variable[jugador].alimentos)*0.3);
			}
		i=1;
		}
		
	}
}

int guardar (struct variables variable[], int jugador) {
	int i;
	FILE *fhistorial;
	fhistorial=fopen("historial.txt","w");
			if (fhistorial==NULL){
				printf("Ha ocurrido un error en la escritura del fichero con los datos de las decidiones 'hitorial.txt'.");
				return 0;
			}
		for (i=0;i<5;i++){
			fprintf(fhistorial,"%i ",variable[i].jugador);
			fprintf(fhistorial,"%i ",variable[i].partepartida);
			fprintf(fhistorial,"%s ",variable[i].nombre);
			fprintf(fhistorial,"%s ",variable[i].nombreimperio);
			fprintf(fhistorial,"%.0f ",variable[i].poblacion);
			fprintf(fhistorial,"%.0f ",variable[i].ejercito);
			fprintf(fhistorial,"%.2f ",variable[i].alimentos);
			fprintf(fhistorial,"%.2f ",variable[i].madera);
			fprintf(fhistorial,"%.2f ",variable[i].metal);
			fprintf(fhistorial,"%.2f ",variable[i].dinero);
			fprintf(fhistorial,"%i ",variable[i].unidos);
			fprintf(fhistorial,"%i ",variable[i].asentamiento);
			fprintf(fhistorial,"\n");
		}
			printf("								GUARDANDO LA PARTIDA\n");
		fclose(fhistorial);
 return 1;
}

int CargaPartida (struct variables variable[], int jugador){
	FILE *fhistorial;
	int i=0, aux;
		fhistorial=fopen("historial.txt","r");
				if (fhistorial == NULL){
					printf("Ha ocurrido un error en la escritura del fichero con los datos de las decidiones 'historial.txt'.");
					return 5;
				}
		while(i<=4){
			fscanf(fhistorial,"%i %i %s %s %f %f %f %f %f %f %i %i",&variable[i].jugador,&variable[i].partepartida,variable[i].nombre,variable[i].nombreimperio,&variable[i].poblacion,&variable[i].ejercito,&variable[i].alimentos,&variable[i].madera,&variable[i].metal,&variable[i].dinero,&variable[i].unidos,&variable[i].asentamiento);
			i++;
		}
		if (jugador==variable[jugador].jugador){
			return jugador;
		}
	
return jugador;	
}
 
void final(struct variables variable[], int jugador){
	FILE *fentrada;
	FILE *fhistorial;
	printf("\n\n");
	printf("	Esto ha sido lo que el destino le tenia guardado a %s.\n");
	printf("	%s, te agradecemos que hayas invertido tu tiempo en jugar a EGO. A ver si tienes mas suerte la proxima vez que no veamos.\n\n\n				 HASTA LUEGO !!!!");
	printf("\n\n		ACUERDATE----> En el documento 'decisiones.txt' (que se encuentra en la misma carpeta que el archivo del juego 'programa.cpp'), tienes un resumen de como te ha ido en la partida de hoy.\n");
	printf("\n Esperamos verte de nuevo %s",variable[jugador].nombre);
				//ABRIMOS EL FICHERO DE DECISIONES LOS DATOS DEL IMPERIO:
				fentrada=fopen("decisiones.txt","w");
							if (fentrada == NULL){
								printf("Ha ocurrido un error en la escritura del fichero con los datos de las decidiones 'decisiones.txt'.");
							}
			//ESCRIBIMOS LOS DATOS CON LOS QUE EL IMPERIO TERMINA SU HISTORIA:
				fprintf(fentrada,"El imperio %s, termino su historia con:\n");
					fprintf(fentrada,"	--> %.0f habitantes.\n",variable[jugador].poblacion);
					fprintf(fentrada,"	--> %.0f miembros del ejercito .\n");
					fprintf(fentrada,"	--> %.2f Dolares de dinero publico en las arcas del estado.\n",variable[jugador].dinero);
					fprintf(fentrada,"	--> %.2f kilogramos de madera.\n",variable[jugador].madera);
					fprintf(fentrada,"	--> %.2f kilogramos de metales y minerales.\n",variable[jugador].metal);
					fprintf(fentrada,"	--> %.2f kilogramos de alimentos con los que mantenía a su pueblo.\n",variable[jugador].alimentos);
			fclose(fentrada);
			
		//Ahora hay dejar constancia en el fichero de 'historial.txt' de que se ha acabado la partida y de que otro puede usarlo.
			fhistorial=fopen("historial.txt","w");
				if (fhistorial == NULL){
					printf("Ha ocurrido un error en la escritura del fichero con los datos de las decidiones 'historial.txt'.");
				}
			fprintf(fhistorial,"%i ",variable[jugador].jugador);
			fprintf(fhistorial,"0 ");
			fprintf(fhistorial,"VACIO ");
			fprintf(fhistorial,"VACIO ");
			fprintf(fhistorial,"0 ");
			fprintf(fhistorial,"0 ");
			fprintf(fhistorial,"0.00f ");
			fprintf(fhistorial,"0.00 ");
			fprintf(fhistorial,"0.00 ");
			fprintf(fhistorial,"0.00 ");
			fprintf(fhistorial,"0 ");
			fprintf(fhistorial,"0 ");
			fprintf(fhistorial,"\n");
			
		fclose(fhistorial);
	}

