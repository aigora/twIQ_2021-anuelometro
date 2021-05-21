#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 1000
		
		
		
struct variables{
	int contadorpartida, partepartida;
	char nombre[N],nombreimperio[N];
	float dinero,metal,alimentos,madera,poblacion, ejercito;
};


	//	FUNCIONES "MISIONES"
void introduccion (struct variables variable[]); 				//nombre del jugador y del imperio.
int episodio1 (struct variables variable[]);					//elige asentamiento.
//EPISODIO 2	(No tiene funcion, porque es sencillo)			//Sale a explorar por primera vez.
int episodio3 (struct variables variable[], int asentamiento);				//Construccion del barco para la COSTA.		Aparicion de indigenas para MESETA y CORDILLERA
//EPISODIO 4	(No tiene funcion, porque es sencillo. Es igual que el 2)	//Preparacion para la 1 guerra.

	// FUNCIONES "SECUNDARIAS"
void informe(struct variables variable[]); 						//Le comumnica al jugador el estado de su imperio.
int explorar (struct variables variable[], int asentamiento);	//Le permite al jugador avanzar y prosperar como imperio.
void final( struct variables variable[]);						//Le agradece al jugado cuando acaba la partida, y escribe datos en el archivo decisiones.txt
int guardar(struct variables variable[], int asentamiento);		//Guarda los avances en el archivo historial.txt
int CargaPartida (struct variables variable[]);					//Carga la informacion del archivo historial.txt para que el jugador pueda seguir la partida, en el mismo punto, habiendo cerrado el programa.



int main(){
	
	int i=1,j=1;
	FILE *fentrada;	
	struct variables variable[1];
	char respuesta;
	int asentamiento;

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
						printf("De acuerdo, vamos a cargar tu partida.");
							CargaPartida(variable);
						printf("%i",variable[1].partepartida);
						j=0;
					}
					else if ((respuesta == 'N')||(respuesta == 'n')){
						printf("	Vas a empezar una nueva partida, si existian datos de otra diferente, quedaran sobreescritos.\n");
							printf("\n");
						variable[1].partepartida=0;
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
		getch();
		printf("(Presiona ENTER para salir de la pausa)\n");
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
			j=0;
				while(j!=0){
					if ((respuesta == 'S')||(respuesta == 's')){
						printf("De acuerdo, vamos a cargar tu partida.");
						CargaPartida(variable);
						
						j=0;
					}
					else if ((respuesta == 'N')||(respuesta == 'n')){
						printf("Vas a empezar una nueva partida, si existian datos de otra diferente, quedaran sobreescritos.\n");
							printf("\n");
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
				
	if(variable[1].partepartida==0){
		introduccion(variable);
		variable[1].partepartida++;
	}
	
		//Guardamos los datos de nombres ():	//Guardamos la decision en el fichero de decisiones:
		
					fentrada = fopen("decisiones.txt", "w");
						if (fentrada == NULL){
							printf("Ha ocurrido un error en la escritura del archivo. Reinicie el programa. Revise la ubicadion del archivo, y si se encuentra en la misma carpeta que el archivo de texto: 'decisiones.txt'.\n");
							return 0;
							}
						fprintf(fentrada,"NUEVA PARTIDA\n	Jugó: %s\n	Su imperio se llamó: %s\n",variable[1].nombre, variable[1].nombreimperio);
	
	
	// EMPEZAMOS  CON EL JUEGO //*******************************************************************************************************************************************************

		// EMPEZAMOS CON LA TOMA DE DECISIONES --> ASENTAMIENTO 
	if(variable[1].partepartida==1){
		asentamiento=episodio1(variable);
		variable[1].partepartida++;
	}
			//Guardamos la decision en el fichero de decisiones:
						if(asentamiento==1){fprintf(fentrada,"Asentamiento inicial---> COSTA\n");	}
						else if(asentamiento==2){fprintf(fentrada,"Asentamiento inicial---> CORDILLERA\n");	}	
						else {fprintf(fentrada,"Asentamiento inicial---> MESETA\n");	}
	


		//**************  declaramos los VALORES INICIALES de las variables (iguales para todos)  ***************
				variable[1].dinero=100;
				variable[1].poblacion=10;
				variable[1].ejercito=5;
				variable[1].metal=0;
				variable[1].alimentos=0;
				variable[1].madera=0;
					//comunicamos al jugador
					informe(variable);
						printf("\n\n");
					
		
	//2º EPISODIO: Exploracion ******************* 2 ************** 2 ************ 2 ************* 2 ************ 2 ************* 2 ************ 2 ************* 2 ***************//
	
			// Para este poco código, no merece la pena hacer una fincion a parte, se queda asi.
	if(variable[1].partepartida==2){
			if(explorar(variable, asentamiento)==0) {
				final(variable);
				return 0;
			}
		informe(variable);
	}
	
	//ANTES TENEMOS QUE HACER ACLARACIONES SOBRE COMO FUNCIONANAN LAS GUERRAS Y COMO SE POSICIONAN LOS PUEBLOS EN FUNCION DE SU ASENTAMIENTO.
		printf("\n");
	printf("	Te vamos a explicar como se distribuyen los imperios en El continente:\n");		printf("\n\n\n");
	printf("	Veras; %s, se encuentra en la siguiente posicion gegrafica con respecto al resto de imperios cercanos:\n",variable[1].nombreimperio);
	
		//PRESENTACION DE LOS IMPERIOS EN FUNCION DEL ASENTAMIENTO 
		if(asentamiento==1){
			printf("	Al rededor nuestro, tenemos 4 imperios grandes. Sus nombres en clave son, por orden de cercania a la capital: 'Alfa','Beta''Gamma','Delta'.\n");
				printf("\n");
				printf("		La verdad es que el imperio Alfa es el que menos te debe preocupar, porque acaba de salir de una crisis social y economica y no parece que tenga muchas ganas de pelear. Puedes aprobechar eso para tratar de llegar a acuerdos, o directamente llevamos al ejército.\n");
				printf("\n");
				printf("		El imperio Beta, está posicionado en una peninsula al norte de %s. Se llega antes por agua que por tierra. Actrualmente se encuentra en expansion.\n",variable[1].nombreimperio);
				printf("\n");
				printf("		El imperio Gamma, está algo alejado, pero no tanto como el Delta.Estos dos tienen asuntos por resolver, por la hija del rey de Gamma y el principe de Delta, que al parecer tienen sus cositas en comun; aunque aun es prnto para saber si terminaran en guerra o en alienza... Todo se vera con el tiempo.\n");
				printf("\n");
				printf("		Por ultimo, el imperio Delta, es el mas alejado; a mas de dos dias de camino. Es un imperio de los mas potentes, ten seguro que como hagan bien las cosas... tienes pocas cosas que hacer para ganarles la batalla.\n");
		}	
		else if(asentamiento==2){
			printf("	Al rededor nuestro, tenemos 4 imperios grandes. Sus nombres en clave son, por orden de cercania a la capital: 'Alfa','Beta''Gamma','Delta'.\n");	
				printf("\n");
				printf("		La verdad es que el imperio Alfa es el que menos te debe preocupar, porque acaba de salir de una crisis social y economica y no parece que tenga muchas ganas de pelear. Puedes aprobechar eso para tratar de llegar a acuerdos, o directamente llevamos al ejército.\n ");
				printf("\n");
				printf("		El imperio Beta, está en expansion. TIENES SUERTE... creo. Su emperador es tu primo!! Eso te puede servir para llegar a pactos de familia. Aunque tambien ten en cuenta que te conoce a la perfeccion, no intentes colarsela que te tiene fichado.\n");
				printf("\n");
				printf("		El imperio Gamma, está algo alejado, pero no tanto como el Delta.Estos dos tienen asuntos por resolver, por la hija del rey de Gamma y el principe de Delta, que al parecer tienen sus cositas en comun; aunque aun es prnto para saber si terminaran en guerra o en alienza... Todo se vera con el tiempo.\n");
				printf("\n");
				printf("		Por ultimo, el imperio Delta, es el mas alejado; a mas de dos dias de camino. Es un imperio de los mas potentes, ten seguro que como hagan bien las cosas... tienes pocas cosas que hacer para ganarles la batalla.\n");
			}
		else{
			printf("	Al rededor nuestro, tenemos 4 imperios grandes. Sus nombres en clave son, por orden de cercania a la capital: 'Alfa','Beta''Gamma','Delta'.\n");	
				printf("\n");
				printf("		La verdad es que el imperio Alfa es el que menos te debe preocupar, porque acaba de salir de una crisis social y economica y no parece que tenga muchas ganas de pelear. Puedes aprobechar eso para tratar de llegar a acuerdos, o directamente llevamos al ejército.\n ");
				printf("\n");
				printf("		El imperio Beta, se encuentra en un momento complicado, acaba de estallar la revolucion del pueblo por los excesivos impuestos. Mantente atento porque nunca se sabe por donde salen estas cosas. Imaginate que a algun iluminado de %s se le ocurre imiterles... tu cargo de emperador estaria en peligro %s. Solo queria avisarte.\n",variable[1].nombreimperio,variable[1].nombre);
				printf("\n");
				printf("		El imperio Gamma, está algo alejado, pero no tanto como el Delta.Estos dos tienen asuntos por resolver, por la hija del rey de Gamma y el principe de Delta, que al parecer tienen sus cositas en comun; aunque aun es prnto para saber si terminaran en guerra o en alienza... Todo se vera con el tiempo.\n");
				printf("\n");
				printf("		Por ultimo, el imperio Delta, es el mas alejado; a mas de dos dias de camino. Es un imperio de los mas potentes, ten seguro que como hagan bien las cosas... tienes pocas cosas que hacer para ganarles la batalla.\n");
			}
		printf("\n\n\n\n");
	
	//3º EPISODIO: Gastar o ganar dinero (Declaracion de guerara):******************* 2 ************** 2 ************ 2 ************* 2 ************ 2 ************* 2 ************ 2 ************* 2 ***************
	int aux,unidos;
	if(variable[1].partepartida==3){
		printf("	Asi es como estan las cosas en %s, %s:\n",variable[1].nombreimperio,variable[1].nombre);
		informe(variable);
		aux=episodio3(variable, asentamiento);
		variable[1].partepartida++;
	}
	
		//Guardamos lo decidido en decisiones.txt
			if (aux==0){
				fprintf(fentrada,"%s no debió haber construido el barco.",variable[1].nombre);
				final(variable);
				return 0;
			}
			else if(aux==1){	fprintf(fentrada,"%s decidió atacar a las personas que se acercaron a %s. Esto provocó tensiones con el imperio alfa que ya \n",variable[1].nombre,variable[1].nombreimperio);		}
			else if(aux==2){		fprintf(fentrada,"%s decidió NO atacar a las personas que se acercaron a %s\n",variable[1].nombre,variable[1].nombreimperio);	}
			else if(aux==3){unidos=1;}
			else{unidos=0;}
	
	
	//4º EPISODIO: Declaracion de guerra y exploracion.****************************** 3************** 3 ************ 3 ************* 3 ************ 3 ************* 3 ************ 3 ********* 3 **************
	
	printf("	Toca salir a explorar... a ver que nos encontramos hoy!\n");
	if(explorar(variable, asentamiento)==0) {
		final(variable);
		return 0;
	}
	informe(variable);
	
	
	//5º EPISODIO: 1ª GUERRA****************************** 4 ************** 4 ******************* 4 ************* 4 ************ 4 ************* 4 *********** 4 ******** 4 *****
	

	
	
	
	
	fclose(fentrada);
return 0;	
}

//************************************		FUNCIONES 	***************************************		FUNCIONES		***************************************//

													//*************	EPISODIOS	*****************//

void introduccion (struct variables variable[]){
	
	int i=1;
	char respuesta,aux[N];
		//PEDIMOS NOMBRE AL USUARIO Y preguntamos si es novato. Si lo es, le explicamos el juego.
			// Preguntamos el nombre
	
			printf("		Empecemos entonces!!\n\n	Antes de nada, te recomendamos que pongas la pantalla completa, te va a tocar leer bastante xD.\n 	Te recordamos ademas, que cuando acabes la partida, tendras un resumen de tus decisiones en la misma carpeta donde tengas el juego, en el archivo llamado 'decisiones'\n	Dinos un nombre con el que referirnos a ti:\n");	
				fflush(stdin);
				gets(variable[1].nombre);
		
				//Preguntamos si conoce el juego, si no, se lo explicamos 
			printf("	Nos dirigiremos hacia ti como %s a partir de ahora.\n",variable[1].nombre);
				printf("\n");
			printf("	Dinos %s, eres nuevo en EMPIRES GLOBAL OFFENSIVE?? (EGO para los amigos) Si no lo has hecho nunca te vendria bien una explicacion de como funciona. Quieres que te expliquemos lo basico??\n",variable[1].nombre);
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
		strcpy(variable[1].nombreimperio,aux);
		getch();
	
}


int episodio1 (struct variables variable[]){			// ASENTAMIENTO 
	int asentamiento,i=1;
	
			printf("\n");
		printf("	Lo segundo que debes elegir, %s, es un buen lugar en el que asentarte al inicio. Posteriormente, este lugar pasara a ser la capital de tu imperio.\n 	Cada localizacion tiene bentajas y desventajas:\n(presiona ENTER)\n",variable[1].nombre);
		getch();	
			printf("\n\n");
		
		printf("		ASENTAMIENTO EN LA COSTA:\n");
			printf("	Tendras un rapido crecimiento al inicio debido al comercio maritimo, pero si no eres capaz de aprovecharlo para sacarle el suficiente ventaja a los imperios rivales, te deseo suerte para defenderte en el futuro.\n");
				printf("\n");
		
		printf("		ASENTAMIENTO EN LA CORDILLERA:\n");
			printf("	Aqui , ademas de unas vistas privilegiadas de todo el valle (un matiz clave para la defensa de tu base), encontramos una gran variedad de minerales y metales, e incluso algo de madera. Sin embargo no se ven muchos sitios donde montar un huerto o una granja...\n");
				printf("\n");
		
		printf("		ASENTAMIENTO EN LA MESETA:\n");
			printf("	Este es un asentamiento complicado la verdad... No se ve ningun tipo de defensa natural que ayude ante un posible ataque enemigo. Sin embargo, esta REPLETO de materiales de todo tipo; tenemos madera, tierras para cultivo, animales que domesticar, una red de cuevas mas o menos cercana con metales y otros minerales....\n");
				printf("	Desde luego que empezar aqui no va a ser facil, pero como sobrevivas al inicio... VAS A SER INDESTRUCTIBLE!!");
					printf("\n\n");
		
					//El ususario lo intyroduce por teclado:
		printf("Introduce un 1 para asentarte en la COSTA.		Introduce un 2 para asentarte en la CORDILLERA.		Introduce un 3 para asentarte en la MESETA\n");
			
			scanf("%i",&asentamiento);
				do {if ((asentamiento!=1)&&(asentamiento!=2)&&(asentamiento!=3)){
						printf("El caracter introducido no es valido. Introduzca un 1, un 2, o 3.\n");
							fflush(stdin);
							scanf("%i",&asentamiento );
					}
				}while (i!=0);
		
		if (asentamiento==1){printf("	Has elegido sabiamente la COSTA.\n");	}
		else if(asentamiento==2){printf("	Has elegido sabiamente la CORDILLERA.\n");	}
		else {printf("	Has elegido sabiamente la MESETA.\n");	}	
	
		printf("	[ No te acostumbres a que te digamos todas las consecuencias de tus decisiones. A partir de ahora vas a tener que apaniartelas solito. ]\n");
return asentamiento;
}

int episodio3 (struct variables variable[], int asentamiento) {
	int i,j,aleatorio;
	float aux;
	char respuesta,letra;

	
	j=0;
		printf("	Hoy hace un dia esplendido... El pueblo de %s se levanta para tomar un poco el sol y ponerse a trabajar, que el continente no se conquista solo.\n",variable[1].nombreimperio);
		
		if (asentamiento==1){
			printf("	La recolecta que has hiciste, no fue demasiado fructifera, por ello seria conveniente que algunos de tus ciudadanos vayan en busca de mas recusos.\n");
			printf("	Ten en cuenta que el resto de pueblos igual prefieren saquear a tus marineros antes de mediar palabra. Ademas del gasto inicial que supone fabricar un barco desde cero.\n");
			printf("(S para construir el barco, N pra no hacerlo)\n");
				fflush(stdin);
				scanf("%c",&respuesta);
					
			i=0; 
				while(i=0){
					if ((respuesta=='S')||(respuesta=='s')){
						printf("			Cuantos recursos quieres gastar en la construccion del barco??:\n");
					//DINERO
						printf("	En dinero (dolares):\n");
							fflush(stdin);
							scanf("f",&aux);		
								variable[1].dinero=variable[1].dinero-aux;
								if (variable[1].dinero<0){ printf("	No tienes suficientes materiales.\n");	return 0;}
					//MADERA
						printf("	En madera (kg):\n");
							fflush(stdin);
							scanf("%f",&aux);		
								variable[1].madera=variable[1].madera-aux;
								if (variable[1].madera<0){ printf("	No tienes suficientes materiales.\n");	return 0;}
					//METAL
						printf("	En metal (kg):\n");
							fflush(stdin);
							scanf("%f",&aux);		
								variable[1].metal=variable[1].metal-aux;
									if (variable[1].metal<0){ printf("	No tienes suficientes materiales.\n");	return 0;}
						
						//INCIDENTE DE LOS OBREROS Y LA COMIDA:
							printf("	Algunos de los obreros que trabajan en el astillero quieren comida (casi 2kg cada uno). Vas a tener que dársela para que no se te revelen.\n	Se la das??\n");
							printf("(S para darsela y N para no:)\n");
								fflush(stdin);
								scanf("%c",&letra);
									j=0;
									while(j==0){
										
										if((letra=='S')||(letra=='s')){ 
											variable[1].alimentos = variable[1].alimentos-20;
												//Si no tiene comida suficiente:
												if (variable[1].alimentos<0){
													printf("Lo siento %s, pero no tienes ni para alimentar a tu pueblo. HAS PERDIDO.\n",variable[1].nombre); 
													final(variable);	
													return 0;
												}													
											j=1;
										}
										else if((letra=='N')||(letra=='n')){
											printf("	Tienes agallas %s... Por desgacia los obreros no les ha hecho mucha gracia tu decision.\n	Han cogido sus cosas y se han marchado. Ahora sois tres menos en tu imperio...\n",variable[1].nombre);
											variable[1].poblacion=variable[1].poblacion-10;
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
										variable[1].alimentos=variable[1].alimentos+5;
										variable[1].metal=variable[1].metal+18;
										variable[1].madera=variable[1].madera+15;
										variable[1].dinero=variable[1].dinero-50;
										variable[1].poblacion=variable[1].poblacion-3;
											if((variable[1].poblacion<0)||(variable[1].dinero<0)){
												printf("	Te has quedado sin recursos... HAS PERDIDO.\n");
												return 0;
											}
									}
									else if(5<aleatorio<8){
										printf("	\n");
										printf("	Los marineros traen algo de materiales, nada especial, pero menos da una piedra.\n");
										printf("	Segun dicen los marineros, se cruzaron con algunos de los marineros del impeio Alfa. Y gracias a que en el barco iba uno de los diplomaticos del imperio %s, se ha llegado a un acuero con el imperio vecino. A partir de ahora el imperio alfa se unirá con nosotros HURRA!!",variable[1].nombreimperio);
										variable[1].alimentos=variable[1].alimentos+19;
										variable[1].metal=variable[1].metal+25;
										variable[1].madera=variable[1].madera+30;
										variable[1].dinero=variable[1].dinero+110;
										variable[1].poblacion=variable[1].poblacion+30;
												return 3;
									}
									else{
										printf("	Ya han pasado mas de 5 dias desde que salio el barco, y no tenemos noticias... Veremos a ver que ocurre pero me huele a que no van a volver.\n");
										variable[1].poblacion=variable[1].poblacion-10;
											if(variable[1].poblacion<0){
												printf("	Te has quedado sin gente... HAS PERDIDO.\n");
												return 0;
											}
									}
								
								
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
		}//Aqui acaba el while del asentamiento 1 
					
		else{ //Lo que ocurre en la 2ª ronda para los asentamientos 2 y 3
			printf("	Se ve que vienen unas personas hacia %s. Crees que debemos atacarles antes de que ellos nos puedan atacar primero??\n",variable[1].nombreimperio);
			printf("(S para si, y N para no)\n");
				fflush(stdin);
				scanf("%c",&respuesta);
			i=0;j=0;
			while(i==0){
				if((respuesta=='S')||(respuesta=='s')){
					i=1;
					printf("AL ATAQUEEEEEEE !!!!!\n");
					
					printf("	Habeis herido a uno de ellos, a otro lo matasteis, y dos de ellos salieron corriendo. Supongo que nunca sabremos quienes eran....\n");
					printf("	Buenos dias emperador! Hoy ha salido un sol precioso, y podemos ver como %s empieza a coger forma y a ganarse el respeto de los imperios vecinos.\n ");
					printf("Quieres salir a la ventana y observar el maravilloso dia que hace??		(S para si y N para no)\n");
						fflush(stdin);
						scanf("%c",&letra);
					//Ver llegar al ejercito alfa
						while(j==0){
							if((letra=='S')||(letra=='s')){
							j=1;
								printf("	Bonito sol... Bonito cielo... Pero... Que es eso que se ve en el horizonte?! NO... NO PUEDE SER!! EL IMPERIO ALFA VIENE CON  TODO SU EJERCITO LISTO PARA LA BATALLA !!! \n");
								printf("	RAPIDO !! Es necesario un comite de emergencia!");
								j=1;
								
							}
							else if((letra=='n')||(letra=='N')){
							j=1;
								printf("	Uno de los altos mandos militares irrumpe en tu habitacion antes incluso de que te puedas levantgar de la cama. Casi sin aliento, te avisa de algo bastante grave y urgente que esta ocurriendo:\n");
								printf("	El ejercito del imperio alfa viene con cara de pocos amigos. Debe de ser que los individuos de ayer eran de los suyos. \n");
								printf("		Esto parece que se va a poner interesante...\n");
							}
							else{
								printf("	El caracter introducido no es valido, por favor introduzca una S o una N:\n");
									fflush(stdin);
									scanf("%c",&letra);
							}
						}//Acaba el bucle de la pregunta: ¿SALIMOS A LA VENTANA?
					//Hay que seguir con la declaracion de guerra.
					
				return 4;
				}
				else if((respuesta=='n')||(respuesta=='N')){
					i=1;
					printf("AL ATAQUEEEEEEE !!!!! Ah... que no ataquemos... okey, perdon me pudo la emocion xD... Bueno, al caso! BAJAD EL PUENTE!!\n");
					printf("	Tras el saludo y los cordialismos, te das cuenta de que las personas que han entrado son representantes diplomaticos del imperio Alfa. Tras su salida de la crisis social, han decidido tender puentes entre vosotros.\n");
					printf("	Te ofrecen sencillamente una union politica. Fusionar los dos imperios. Y como son conscientes de que no son el imperio más rico de El continente, asuemmen que será bajo el nombre de %s. Lo aceptas??\n",variable[1].nombreimperio);
						j=0;
							while(j==0){
							if((letra=='S')||(letra=='s')){
							j=1;
								printf("	ESTUPENDO!! Vayamos al despacho del emperador %s a terminar con el papeleo.\n",variable[1].nombreimperio);
								return 3;
								j=1;
								
							}
							else if((letra=='n')||(letra=='N')){
							j=1;
								printf("	\n");
								
							}
				return 5;		
					}
				}
				else{
					printf("	El caracter introducido no es valido, por favor introduzca una S o una N:\n");
						fflush(stdin);
						scanf("%c",&respuesta);
				}
			}//Acaba el bucle de la pregunta: ¿ATACAMOS A LOS QUE SE ACERCAN?
		}//Acaba el 2º movimiento del los asentamientos 2 y 3
return 6;
}




void informe(struct variables variable[1]){	//Informamos del estado del imperio:
		printf("	Actualmente, tu imperio cuenta con:\n");
		printf("			%.0f personas. De los cuales, %.0f pertenecen al ejercito.\n",variable[1].poblacion,variable[1].ejercito);
		printf("			%.1f dolares en las arcas publicas.\n",variable[1].dinero);
		printf("			%.2f Kg de madera; %.1f Kg de alimentos; y otros %.2f Kg de metal.\n",variable[1].madera,variable[1].alimentos,variable[1].metal);

}

int explorar (struct variables variable[], int asentamiento){
	int i,num;
	float mitad;
	printf("	Debes mandar a algunas de las personas a por recursos. Tu eliges a cuantos de los %.0f mandas.\n",variable[1].poblacion);
		fflush(stdin);
		scanf("%i",&num);
	mitad=variable[1].poblacion*0.5;
	i=0;
	while(i==0){
		if (num==variable[1].poblacion){
			printf("	Lamentamos comunicarte, que tu imperio a sido asaltado por el imperio vecino. A quien se le ocurre dejarla sin nadie que la proteja... De verdad que... EN QUE ESTABAS PENSANDO!!");
			printf("Lo has perdido TODO. Aunque casi no te ha dado tiempo a tener nada....\n 	Este es el final de tu imperio\n");
			printf("	Esperamos que te lo hayas pasado bien en tu corta estancia jungando EGO. Tambien espaeramos que vuelvas pronto.\n HASTA LA PROXIMA!!");
			i=1;
			final(variable);
			return 0;
		}
		else if((num>variable[1].poblacion)||(num<0)){	
			printf("El numero introducido no es valido. Introduzca un numero del 0 al numero de habitantes que tenga %s.\n",variable[1].nombreimperio);
				fflush(stdin);
				scanf("%i",&num);
		}
		else{
			if(asentamiento==1){
				variable[1].madera=variable[1].madera+1.2*num;
				variable[1].metal=variable[1].metal+1.2*num;
				variable[1].alimentos=variable[1].alimentos+num*1.8; 
				variable[1].poblacion=variable[1].poblacion+variable[1].alimentos*0.25;
				variable[1].ejercito=variable[1].ejercito+variable[1].poblacion*0.2;
				variable[1].dinero=variable[1].dinero+((variable[1].madera+variable[1].metal+variable[1].alimentos)/2.0);
			}
			else if(asentamiento==2){
				variable[1].madera=variable[1].madera+1.2*num;
				variable[1].metal=variable[1].metal+1.8*num;
				variable[1].alimentos=variable[1].alimentos+num*1.5;
				variable[1].poblacion=variable[1].poblacion+variable[1].alimentos*0.25;
				variable[1].ejercito=variable[1].ejercito+variable[1].poblacion*0.2;
				variable[1].dinero=variable[1].dinero+((variable[1].madera+variable[1].metal+variable[1].alimentos)*0.3);
			}
			else{   //asentamiento==3
				if (num>=mitad){
					variable[1].dinero=variable[1].dinero-40;
					printf("	Siento mucho tener que ser yo quien te lo diga, pero mandaste demasiadas personas a recolectar. Han venido ladrones, y se han llevado 40 dolares de las arcas publicas. Suerte has tenido de que no se llevasen mas.");
				}
					variable[1].madera=variable[1].madera+1.9*num;
					variable[1].metal=variable[1].metal+1.8*num;
					variable[1].alimentos=variable[1].alimentos+num*2;
					variable[1].poblacion=variable[1].poblacion+variable[1].alimentos*0.25;
					variable[1].ejercito=variable[1].ejercito+variable[1].poblacion*0.2;
					variable[1].dinero=variable[1].dinero+((variable[1].madera+variable[1].metal+variable[1].alimentos)*0.3);
			}
		i=1;
		}
		
	}
}

int guardar (struct variables variable[], int asentamiento) {
	
	FILE *fhistorial;
	
	fhistorial=fopen("historial","w");
			if (fhistorial==NULL){
				printf("Ha ocurrido un error en la escritura del fichero con los datos de las decidiones 'hitorial.txt'.");
				return 0;
			}
		
	fprintf(fhistorial,"%i ",variable[1].contadorpartida);
	fprintf(fhistorial,"%i ",variable[1].partepartida);
	fprintf(fhistorial,"%s ",variable[1].nombre);
	fprintf(fhistorial,"%s ",variable[1].nombreimperio);
	fprintf(fhistorial,"%.0f ",variable[1].poblacion);
	fprintf(fhistorial,"%.0f ",variable[1].ejercito);
	fprintf(fhistorial,"%.2f ",variable[1].alimentos);
	fprintf(fhistorial,"%.2f ",variable[1].madera);
	fprintf(fhistorial,"%.2f ",variable[1].metal);
	fprintf(fhistorial,"%.2f ",variable[1].dinero);
	fprintf(fhistorial,"%i ",asentamiento);
	fprintf(fhistorial,"\n");
 
}

int CargaPartida (struct variables variable[]){
	FILE *fhistorial;
	int asentamiento;
		fhistorial=fopen("historial.txt","r");
				if (fhistorial == NULL){
					printf("Ha ocurrido un error en la escritura del fichero con los datos de las decidiones 'decisiones.txt'.");
				}
		fscanf(fhistorial,"%i %i %s %s %f %f %f %f %f %f",&variable[1].contadorpartida,&variable[1].partepartida,variable[1].nombre,variable[1].nombreimperio,&variable[1].poblacion,&variable[1].ejercito,&variable[1].alimentos,&variable[1].madera,&variable[1].metal,&variable[1].dinero,&asentamiento);
	return asentamiento;
}
 
void final(struct variables variable[]){
	FILE *fentrada;
	printf("	Esto ha sido lo que el destino le tenia guardado a %s.\n");
	printf("	%s, te agradecemos que hayas invertido tu tiempo en jugar a EGO. A ver si tienes mas suerte la proxima vez que no veamos.\n\n\n				 HASTA LUEGO !!!!");
	printf("\n\n\n			ACUERDATE----> En el documento 'decisiones.txt' (que se encuentra en la misma carpeta que el archivo del juego 'programa.cpp'), tienes un resumen de como te ha ido en la partida de hoy.\n");
	printf("\n");
				//ABRIMOS EL FICHERO DE DECISIONES LOS DATOS DEL IMPERIO:
				fentrada=fopen("decisiones.txt","w");
							if (fentrada == NULL){
								printf("Ha ocurrido un error en la escritura del fichero con los datos de las decidiones 'decisiones.txt'.");
							}
				//ESCRIBIMOS LOS DATOS CON LOS QUE EL IMPERIO TERMINA SU HISTORIA:
				fprintf(fentrada,"El imperio %s, termino su historia con:\n");
					fprintf(fentrada,"	--> %.0f habitantes.\n",variable[1].poblacion);
					fprintf(fentrada,"	--> %.0f miembros del ejercito .\n");
					fprintf(fentrada,"	--> %.2f Dolares de dinero publico en las arcas del estado.\n",variable[1].dinero);
					fprintf(fentrada,"	--> %.2f kilogramos de madera.\n",variable[1].madera);
					fprintf(fentrada,"	--> %.2f kilogramos de metales y minerales.\n",variable[1].metal);
					fprintf(fentrada,"	--> %.2f kilogramos de alimentos con los que mantenía a su pueblo.\n",variable[1].alimentos);
			fclose(fentrada);
	}

