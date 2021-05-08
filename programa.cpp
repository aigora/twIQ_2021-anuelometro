#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define N 1000

struct variables{
	int poblacion, ejercito;
	float dinero,metal,alimentos,madera;
};

void informe(struct variables variable[N]); 
void explorar (struct variables variable);
void final();

int main(){
	
	int i=1;	
	FILE *fentrada;	
	struct variables variable[N];
	char nombre[N],nombreimperio[N],respuesta;

//MENU INICIAL

	printf("				*EMPIRES GLOBAL OFFENSIVE*\n");	
	printf("	Bienvenido jugador, si quiere empezar a jugar introduzca una E; de lo contrario, una S para salir.\n");	
	scanf("%c",&respuesta);
	
do {	
	if ((respuesta == 'E')||(respuesta == 'e')){
		i=0;
	}
	else if  ((respuesta == 'S')||(respuesta == 's')){
		printf("	Esperamos verte pronto. Hasta luego !!!");
		return 0;
	}
	else {
		printf("El caracter introducido no es valido. Introduzca un caracter valido (E para empezar y S para salir).\n");
		fflush(stdin);
		scanf("%c",&respuesta);
	}
}while (i!=0);

//PEDIMOS NOMBRE AL USUARIO Y preguntamos si es novato. Si lo es, le explicamos el juego.
	// Preguntamos el nombre
		
	printf("	Empecemos entonces!!\n	Antes de nada, te recomendamos que pongas la pantalla completa, te va a tocar leer bastante xD.\n	Dinos un nombre con el que referirnos a ti:\n");	
	fflush(stdin);
	gets(nombre);

	//Preguntamos si conoce el juego, si no, se lo explicamos 
	printf("	Nos dirigiremos hacia ti como %s a partir de ahora.\n",nombre);
	printf("\n");
	printf("	Dinos %s, eres nuevo en EMPIRES GLOBAL OFFENSIVE?? (EGO para los amigos) Si no lo has hecho nunca te vendria bien una explicacion de como funciona. Quieres que te expliquemos lo basico??\n",nombre);
	printf("Introduce S para si y N para no:\n");
	fflush(stdin);
	scanf("%c",&respuesta);
	printf("\n");
		
	i=1;
do { 
		if ((respuesta == 'S')||(respuesta == 's')){
			printf("	Este juego se basa en la creacion de un imperio. Para poder crear, mantener y expandir tu propia superpotencia continental, deberas tener en cuenta una serie de asuntos como la salud y lealtad de tu ejercito, el bienestar de tu pueblo, la relaciones internacionales que tengas con los imperios vecinos, la religon que impantes (o no), tu destreza a la hora de enfrentarte en la guerra, o guerras. Estos asuntos se van a materializar a traves de 4 variables que, como ya sabes, condicionaran el fututro de tu imperio; estas son: la economia de tu imperio ; la lealtad, fuerza y fama de tu ejercito; la cantidad y calidad de los recursos que seas capaz de obtener, y por supuesto, el estado de tu pueblo. Que seria de una nacion, SIN SU PUEBLO!!\n");
			printf("\n");
			printf("	Desde aqui te deseamos fuerza para la batalla y prudencia en tu toma de decisiones.\n Que la suerte juegue de tu lado.\n");
			printf("\n");
			printf("	En definitiva, sera un videojuego donde tienes el poder de escribir el futuro de tu nacion; ya sea desde un trono en tu palacete, o desde el campo de batalla, d�ndole ejemplo a tus aliados en la batalla. Y para ello tienes que tomar una serie de decisiones que se le plantean teniendo en cuenta todas las variables anteriormente descritas y muchas mas. Ademas de esto, en las guerras (que aunque podr�s evitarlas, a veces ser�n muy provechsas para tu imperio), se te plantearan diferentes minijuegos, adivinanzas, o aquello que el destino te depare a ti y a tu ejercito.\n");
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
	}while (i!=0);
	
	printf("\n");
	printf("	Procedamos a la creacion de tu imperio. Lo primero que hay que concretar es el nombre. Este es un momneto importante... tomate tu tiempo, porque no lo podras cambiar despues:\n");
	fflush(stdin);
	gets(nombreimperio);
	printf("	Uh! %s? es un buen nombre... Pero necesitas algo mas que eso para conquistar El Contintente!!\n	Sin mas dilacion... EMPECEMOS DE VERDAD\n(presiona ENTER)\n",nombreimperio);
	getch();
	
					//Guardamos los datos de nombres ():	//Guardamos la decision en el fichero de decisiones:
					fentrada = fopen("decisiones.txt", "w");
						if (fentrada == NULL){
							printf("Ha ocurrido un error en la escritura del archivo. Reinicie el programa");
						return 0;	}
						fprintf(fentrada,"NUEVA PARTIDA\n		Jug�: %s\n 		Su imperio se llam�: %s",nombre,nombreimperio);
						fclose(fentrada);
	
	
// EMPEZAMOS CON LA TOMA DE DECISIONES --> ASENTAMIENTO 
	
	printf("\n");
		printf("	Lo segundo que debes elegir, %s, es un buen lugar en el que asentarte al inicio. Posteriormente, este lugar pasara a ser la capital de tu imperio.\n 	Cada localizacion tiene bentajas y desventajas:\n(presiona ENTER)\n",nombre);
	getch();	printf("\n\n");

	
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
	
	int asentamiento;
	printf("Introduce un 1 para asentarte en la COSTA.		Introduce un 2 para asentarte en la CORDILLERA.		Introduce un 3 para asentarte en la MESETA\n");
	fflush(stdin);
	scanf("%i",&asentamiento);
	do {if ((asentamiento!=1)&&(asentamiento!=2)&&(asentamiento!=3)){
			printf("El caracter introducido no es valido. Introduzca un 1, un 2, o 3.\n");
			fflush(stdin);
			scanf("%c",&respuesta);
		}
	}while (i!=0);
	
	if (asentamiento==1){printf("	Has elegido sabiamente la COSTA.\n");	}
	else if(asentamiento==2){printf("	Has elegido sabiamente la CORDILLERA.\n");	}
	else {printf("	Has elegido sabiamente la MESETA.\n");	}	

	printf("	No te acostumbres a que te digamos todas las consecuencias de tus decisiones. A partir de ahora vas a tener que apaniartelas solito.\n");
	
				//Guardamos la decision en el fichero de decisiones:
					fentrada = fopen("decisiones.txt", "w");
					
						if (fentrada == NULL){
							printf("Ha ocurrido un error en la lectura del archivo. Reinicie el programa");
						return 0;	}
					
						if(asentamiento==1){fprintf(fentrada,"Decision 2: Asentamiento inicial---> COSTA");	}
						else if(asentamiento==2){fprintf(fentrada,"Decision 2: Asentamiento inicial---> CORDILLERA");	}	
						else {fprintf(fentrada,"Decision 2: Asentamiento inicial---> MESETA");	}
						
						fclose(fentrada);
	
// EMPEZAMOS  CON EL JUEGO //*******************************************************************************************************************************************************
	//declaramos los vaslores iniciales de las variables (iguales para todos)
	
		variable[N].dinero=100;
		variable[N].poblacion=10;
		variable[N].ejercito=5;
		variable[N].metal=0;
		variable[N].alimentos=0;
		variable[N].madera=0;
		//comunicamos al jugador
		informe(variable);
		
	int num; 		//Esta variable ser� usada para recoger la respuesta a multiples preguntas durante el programa.
					//cumple un papel parecido al de la variable "respuesta", pero con valores enteros.

	printf("	Debes mandar a algunas de las personas a por recursos. Tu eliges a cuantos de los %i mandas.\n",variable[N].poblacion);
	fflush(stdin);
	scanf("%i",&num);
	
	i=0;
	do{
		if (num==10){
			printf("	%s, lamentamos comunicarle, que su aldea a sido asaltada por el pueblo vecino. A quien se le ocurre dejarla sin nadie que la proteja... De verdad que... EN QUE ESTABAS PENSANDO!!",nombre);
			printf("Lo has perdido TODO. Aunque casi no te ha dado tiempo a tener nada....\n 	Este es el final de %s\n",nombreimperio);
			printf("	Esperamos que te lo hayas pasado bien en tu corta estancia jungando EGO. Tambien espaeramos que vuelvas pronto.\n HASTA LA PROXIMA!!");
			i=1;
			//Aqui se puede ejecutar una funcion de final del programa. Que haga un resumende la partida o algo por el estilo
			return 0;
		}
		else if((num>10)||(num<0)){	printf("El caracter introducido no es valido. Introduzca un numero del 1 al 10.\n");
				fflush(stdin);
				scanf("%i",&num);
		}
		else{
			if(asentamiento==1){
				variable[N].dinero=variable[N].dinero+num*1.5;
				variable[N].madera=1.4*num;
				variable[N].metal=1.2*num;
				variable[N].alimentos=num*1.5;
				i=1;
			}
			else if(asentamiento==2){
				variable[N].madera=1.2*num;
				variable[N].metal=1.8*num;
				variable[N].alimentos=num*1.5;
				i=1;
			}
			else{
				if (num>5){
					variable[N].dinero=variable[N].dinero-30;
					printf("	Siento mucho tener que ser yo quien te lo diga, pero mandaste demasiadas personas a recolectar. Ha venido el pueblo vecino, y se ha llevado 30 dolares de las arcas publicas. Suerte has tenido de que no se llevase mas.");
				}
					variable[N].madera=1.9*num;
					variable[N].metal=1.8*num;
					variable[N].alimentos=num*2;
					i=1;
			}
		}
		
	}while(i==0);
	informe(variable);
	
	//2� MOVIMIENTO DEL JUGARDOR: Gastar o ganar dinero:
	float aux;
	int j=0;
		if (asentamiento==1){
			printf("	La recolecta que has hecho, no ha sido demasiado frctifera, por ello seria conveniente que algunos de tus ciudadanos vayan en busca de mas recusos.\n");
			printf("	Ten en cuenta que el resto de pueblos igual prefieren saquear a tus marineros antes de mediar palabra. Ademas del gasto inicial que supone fabricar un barco desde cero.\n");
			printf("(S para construir el barco, N pra no hacerlo)\n");
				fflush(stdin);
				scanf("c",&respuesta);
					
			i=0;
				while(i=0){
					if ((respuesta=='S')||(respuesta=='s')){
						printf("	Cuantos recursos quieres gastar en la construccion del barco??\n");
							//DINERO
						printf("	En dinero($):\n");
						fflush(stdin);
						scanf("f",&aux);		
						variable.dinero=variable.dinero-aux;
							//MADERA
						printf("	En madera (kg):\n");
						fflush(stdin);
						scanf("%f",&aux);		
						variable.madera=variable.madera-aux;
							//METAL
						printf("	En metal (kg):\n");
						fflush(stdin);
						scanf("%f",&aux);		
						variable.metal=variable.metal-aux;
						
						//INCIDENTE DE LOS OBREROS Y LA COMIDA:
							printf("	3 de los obreros que trabajan en el astillero quieren comida (1kg cada uno). Vas a tener que d�rsela para que no se te revelen.\n	Se la das??");
							printf("(S para darsela y N para no:)\n");
								fflush(stdin);
								scanf("%c",&respuesta);
									while(j==0){
										
										if((respuesta=='S')||(respuesta=='s')){ 
											variables.alimentos = variables.alimentos-3;
												if (variable.alimentos<0){
													printf("Lo siento %s, pero no tienes ni para alimentar a tu pueblo. HAS PERDIDO.",nombre); 
													final();	
												}													
											j=1;
										}
										else if((respuesta=='N')||(respuesta=='n')){
											printf("	Tienes agallas %s... Por desgacia los obreros no les ha hecho mucha gracia tu decision.\n	Han cogido sus cosas y se han marchado. Ahora sois tres menos en tu imperio...\n",nombre);
											j=1;
										}
										else{
											printf("El caracter introducido no es valido. Escriba una S o una N por favor.");
												fflush(stdin);
												scanf("%f",&aux);
										}
										
									}
							i=1;
						}
						else if((respuesta=='N')||(respuesta=='n')){
							i=1;
							printf("Tu mismo con tu mecanismo amigo... A ver como te las apanias en el futuro...");
						}
						else {
							printf("El caracter introducido no es valido. Escriba una S o una N por favor.");
							fflush(stdin);
							scanf("%f",&aux);
						}
				}
		
		else{
			printf("Se ve que vienen unas personas hacia %s. Debemos atacarlesantes de que ellos nos ataquen primero??",nombreimperio);
			printf("(S para si, y N para no)");
				fflush(stdin);
				scanf("c",&respuesta);
		printf("CONTINUARA");
		}
	
	
	
	
	
	
	
	
	
	
return 0;	
}

//************************************		FUNCIONES 	***************************************		FUNCIONES		***************************************

void informe(struct variables variable[N]){	//Informamos del estado del imperio:
		printf("	Actualmente, tu imperio cuenta con:\n");
		printf("			%i personas. De los cuales, %i pertenecen al ejercito.\n",variable[N].poblacion,variable[N].ejercito);
		printf("			%.1f dolares en las arcas publicas.\n",variable[N].dinero);
		printf("			%.2f Kg de madera; %.1f Kg de alimentos; y otros %.2f Kg de metal.\n",variable[N].madera,variable[N].alimentos,variable[N].metal);

}

void explorar (struct variables variable){
	int i,num;
	printf("	Debes mandar a algunas de las personas a por recursos. Tu eliges a cuantos de los %i mandas.\n",variable[N].poblacion);
	fflush(stdin);
	scanf("%i",&num);
	i=0;
	do{
		if (num==variable.poblacion){
			printf("	%s, lamentamos comunicarle, que su aldea a sido asaltada por el pueblo vecino. A quien se le ocurre dejarla sin nadie que la proteja... De verdad que... EN QUE ESTABAS PENSANDO!!",nombre);
			printf("Lo has perdido TODO. Aunque casi no te ha dado tiempo a tener nada....\n 	Este es el final de %s\n",nombreimperio);
			printf("	Esperamos que te lo hayas pasado bien en tu corta estancia jungando EGO. Tambien espaeramos que vuelvas pronto.\n HASTA LA PROXIMA!!");
			i=1;
			//Aqui se puede ejecutar una funcion de final del programa. Que haga un resumende la partida o algo por el estilo
			final();
		}
		else if((num>10)||(num<0)){	printf("El caracter introducido no es valido. Introduzca un numero del 1 al 10.\n");
				fflush(stdin);
				scanf("%i",&num);
		}
		else{
			if(asentamiento==1){
				variable[N].dinero=variable[N].dinero+num*1.45;
				variable[N].madera=1.5*num;
				variable[N].metal=1.2*num;
				variable[N].alimentos=num*1.8;
				i=1;
			}
			else if(asentamiento==2){
				variable[N].dinero
				variable[N].madera=1.2*num;
				variable[N].metal=1.8*num;
				variable[N].alimentos=num*1.5;
				i=1;
			}
			else{
				if (num>){
					variable[N].dinero=variable[N].dinero-30;
					printf("	Siento mucho tener que ser yo quien te lo diga, pero mandaste demasiadas personas a recolectar. Ha venido el pueblo vecino, y se ha llevado 30 dolares de las arcas publicas. Suerte has tenido de que no se llevase mas.");
				}
					variable[N].madera=1.9*num;
					variable[N].metal=1.8*num;
					variable[N].alimentos=num*2;
					i=1;
			}
		}
		
	}while(i==0);
}

void final(){	printf("	Te agradecemos que hayas invertido tu tiempo en jugar a EGO. A ver si tienes mas suerte la proxima vez que no veamos. HASTA LUEGO !!!!");}


