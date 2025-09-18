#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>
#include <stdio.h>
#include <ctype.h>

#define RESET_COLOR    "\x1b[0m"
#define ROJO_T         "\x1b[31m"
#define VERDE_T        "\x1b[32m"
#define AZUL_T         "\x1b[34m"
#define MAGENTA_T      "\x1b[35m"
#define CYAN_T         "\x1b[36m"

/*
El proyecto final puede ser una aplicación de gestión o un
juego, los criterios de evaluación del proyecto serán los siguientes:

- Obligatorio el uso de punteros y estructuras dinámicas
para el almacenamiento de información

- Obligatoria la persistencia de datos al cierre
del programa con uso de ficheros

- Obligatorio el uso de la librería grafica que
veremos en clase (graphics.h)

- Mínimo 1500 líneas de código útil y limpio

- Se valorará positivamente el uso de las buenas
practicas de programación vistas en clase (código legible, uso de librerías y
funciones reutilizables, optimización de memoria, etc.)

- Se valorará positivamente la funcionalidad
correcta ante la creatividad

- Se valorará positivamente la entrega de un manual de
uso del programa desarrollado

La idea utilizada para el proyecto puede influir
en la nota positivamente o negativamente, el proyecto se puede hacer máximo en parejas de
2 pero la defensa va a ser individual y puede haber grupos en los que un miembro
tenga un 10 y otro suspenda (depende de la calidad del trabajo y de la defensa).

*/

typedef struct{
    char nombre[25];
    char tipo[25];
    char tipo2[25];
    int lvl;
    int xp;
    int at;
    int df;
    int atE;
    int dfE;
    int ps;
    int psMAX;
    int vel;
} Pokemon;

typedef struct{
    Pokemon *p;
    char apodo[25];
} Equipo;

typedef struct{
    int dinero;
    int pokeballs;
    int pociones;
} Inventario;

void inicializarPokedex(Pokemon p[]){
	int i;
	
    const char* nombresPrimeraGen[151] = { 
        "Bulbasaur", "Ivysaur", "Venusaur", "Charmander", "Charmeleon", "Charizard",
        "Squirtle", "Wartortle", "Blastoise", "Caterpie", "Metapod", "Butterfree",
        "Weedle", "Kakuna", "Beedrill", "Pidgey", "Pidgeotto", "Pidgeot",
        "Rattata", "Raticate", "Spearow", "Fearow", "Ekans", "Arbok", "Pikachu",
        "Raichu", "Sandshrew", "Sandslash", "Nidoran?", "Nidorina", "Nidoqueen",
        "Nidoran?", "Nidorino", "Nidoking", "Clefairy", "Clefable", "Vulpix",
        "Ninetales", "Jigglypuff", "Wigglytuff", "Zubat", "Golbat", "Oddish",
        "Gloom", "Vileplume", "Paras", "Parasect", "Venonat", "Venomoth",
        "Diglett", "Dugtrio", "Meowth", "Persian", "Psyduck", "Golduck",
        "Mankey", "Primeape", "Growlithe", "Arcanine", "Poliwag", "Poliwhirl",
        "Poliwrath", "Abra", "Kadabra", "Alakazam", "Machop", "Machoke",
        "Machamp", "Bellsprout", "Weepinbell", "Victreebel", "Tentacool",
        "Tentacruel", "Geodude", "Graveler", "Golem", "Ponyta", "Rapidash",
        "Slowpoke", "Slowbro", "Magnemite", "Magneton", "Farfetch’d", "Doduo",
        "Dodrio", "Seel", "Dewgong", "Grimer", "Muk", "Shellder", "Cloyster",
        "Gastly", "Haunter", "Gengar", "Onix", "Drowzee", "Hypno", "Krabby",
        "Kingler", "Voltorb", "Electrode", "Exeggcute", "Exeggutor", "Cubone",
        "Marowak", "Hitmonlee", "Hitmonchan", "Lickitung", "Koffing", "Weezing",
        "Rhyhorn", "Rhydon", "Chansey", "Tangela", "Kangaskhan", "Horsea",
        "Seadra", "Goldeen", "Seaking", "Staryu", "Starmie", "Mr. Mime",
        "Scyther", "Jynx", "Electabuzz", "Magmar", "Pinsir", "Tauros", "Magikarp",
        "Gyarados", "Lapras", "Ditto", "Eevee", "Vaporeon", "Jolteon", "Flareon",
        "Porygon", "Omanyte", "Omastar", "Kabuto", "Kabutops", "Aerodactyl",
        "Snorlax", "Articuno", "Zapdos", "Moltres", "Dratini", "Dragonair",
        "Dragonite", "Mewtwo", "Mew"
    };
    
    const char* tiposPrimeraGen[151] = {
        "Planta", "Planta", "Planta", "Fuego", "Fuego", "Fuego",
        "Agua", "Agua", "Agua", "Bicho", "Bicho", "Bicho",
        "Bicho", "Bicho", "Bicho", "Normal", "Normal", "Normal",
        "Normal", "Normal", "Normal", "Normal", "Veneno", "Veneno", "Electrico",
        "Electrico", "Tierra", "Tierra", "Veneno", "Veneno", "Veneno",
        "Veneno", "Veneno", "Veneno", "Normal", "Normal", "Fuego",
        "Fuego", "Normal", "Normal", "Veneno", "Veneno", "Planta",
        "Planta", "Planta", "Bicho", "Bicho", "Bicho", "Bicho",
        "Tierra", "Tierra", "Normal", "Normal", "Agua", "Agua",
        "Lucha", "Lucha", "Fuego", "Fuego", "Agua", "Agua",
        "Agua", "Psiquico", "Psiquico", "Psiquico", "Lucha", "Lucha",
        "Lucha", "Planta", "Planta", "Planta", "Agua",
        "Agua", "Roca", "Roca", "Roca", "Fuego", "Fuego",
        "Agua", "Agua", "Electrico", "Electrico", "Normal", "Normal",
        "Normal", "Agua", "Agua", "Veneno", "Veneno", "Agua", "Agua",
        "Fantasma", "Fantasma", "Fantasma", "Roca", "Psiquico", "Psiquico", "Agua",
        "Agua", "Electrico", "Electrico", "Planta", "Planta", "Tierra",
        "Tierra", "Lucha", "Lucha", "Normal", "Veneno", "Veneno",
        "Tierra", "Tierra", "Normal", "Planta", "Normal", "Agua",
        "Agua", "Agua", "Agua", "Agua", "Agua", "Psiquico",
        "Bicho", "Hielo", "Electrico", "Fuego", "Bicho", "Normal", "Agua",
        "Agua", "Agua", "Normal", "Normal", "Agua", "Electrico", "Fuego",
        "Normal", "Roca", "Roca", "Roca", "Roca", "Roca",
        "Normal", "Hielo", "Electrico", "Fuego", "Dragon", "Dragon",
        "Dragon", "Psiquico", "Psiquico"
    };    
	
    const char* tipoSecundario[151] = {
	    "Veneno", "Veneno", "Veneno", "0", "0", "Volador",
        "0", "0", "0", "0", "0", "Volador",
        "Veneno", "Veneno", "Veneno", "Volador", "Volador", "Volador",
        "0", "0", "Volador", "Volador", "0", "0", "0",
        "0", "0", "0", "0", "0", "Tierra",
        "0", "0", "Tierra", "0", "0", "0",
        "0", "0", "0", "Volador", "Volador", "Veneno",
        "Veneno", "Veneno", "Planta", "Planta", "Veneno", "Veneno",
        "0", "0", "0", "0", "0", "0",
        "0", "0", "0", "0", "0", "0",
        "Lucha", "0", "0", "0", "0", "0",
        "0", "Veneno", "Veneno", "Veneno", "Veneno",
        "Veneno", "Tierra", "Tierra", "Tierra", "0", "0",
        "Psiquico", "Psiquico", "0", "0", "Volador", "Volador",
        "Volador", "0", "Hielo", "0", "0", "0", "Hielo",
        "Veneno", "Veneno", "Veneno", "Tierra", "0", "0", "0",
        "0", "0", "0", "Psiquico", "Psiquico", "0",
        "0", "0", "0", "0", "0", "0",
        "Roca", "Roca", "0", "0", "0", "0",
        "0", "0", "0", "0", "Psiquico", "0",
        "Volador", "Psiquico", "0", "0", "0", "0", "0",
        "Volador", "Hielo", "0", "0", "0", "0", "0",
        "0", "Agua", "Agua", "Agua", "Agua", "Volador",
        "0", "Volador", "Volador", "Volador", "0", "0",
        "Volador", "Psiquico", "Psiquico"
	};

    for(i = 0; i < 151; i++){
        strcpy(p[i].nombre, nombresPrimeraGen[i]);
        strcpy(p[i].tipo, tiposPrimeraGen[i]);
        strcpy(p[i].tipo2, tipoSecundario[i]);
        p[i].lvl = 1 + rand() % 5;
        p[i].xp = 0;
        p[i].at = 5 + rand() % 11;
        p[i].df = 5 + rand() % 11;
        p[i].atE = 5 + rand() % 11;
        p[i].dfE = 5 + rand() % 11;
        p[i].ps = 15 + rand() % 11;
        p[i].psMAX = p[i].ps;
        p[i].vel = 5 + rand() % 11;
    }
}

void inicializarInventario(Inventario *inv){
    inv->dinero = 1500;
    inv->pokeballs = 15;
    inv->pociones = 10;
}

void inicializarMapa(char ***mapa, int *dimensiones){
    int i, j, x, y, rng, alto, ancho;

    printf("Dimensiones del Mapa:\n---> ");
    
    do{
        scanf("%d", dimensiones);
    } while(*dimensiones < 15 || *dimensiones > 40);

    alto = *dimensiones;
    ancho = *dimensiones;

    *mapa = (char**) malloc(alto * sizeof(char*));
    if(*mapa == NULL){
        printf("Error al asignar memoria para filas\n");
        return;
    }
	
    for(i = 0; i < alto; i++){
        (*mapa)[i] = (char*) malloc(ancho * sizeof(char));
        if((*mapa)[i] == NULL){
            printf("Error al asignar memoria para columnas\n");
            exit(1);
        }
    }

    for(i = 0; i < alto; i++){
        for(j = 0; j < ancho; j++){
            rng = rand() % 2;
            (*mapa)[i][j] = (rng == 0) ? 'H' : '-';
        }
    }

    x = (rand() % (alto - 4)) + 2;
    y = rand() % (ancho / 3);
    (*mapa)[x][y] = 'P';

    x = (rand() % (alto - 4)) + 2;
    y = (rand() % (ancho / 3)) + (ancho / 3);
    (*mapa)[x][y] = 'O';

    x = (rand() % (alto - 4)) + 2;
    y = (rand() % (ancho / 3)) + (2 * (ancho / 3));
    (*mapa)[x][y] = 'T';
    
    do{
    	x = (rand() % alto);
    	y = (rand() % ancho);
	} while((*mapa)[x][y] != '-' && (*mapa)[x][y]);
	(*mapa)[x][y] = 'A';
}

void guardarPartidaCompleta(Equipo e[], int contEquipo, Inventario *inv, char **mapa, int dimensiones, char ultimaCasilla) {
    FILE *f = fopen("partida_completa.txt", "w");
    int i;
    
    if (!f){
        printf("Error al guardar la partida\n");
        return;
    }

    // Guardar inventario
    fprintf(f, "%d %d %d\n", inv->dinero, inv->pokeballs, inv->pociones);

    // Guardar equipo (maximo 6)
    for(i = 0; i < 6; i++){
        if(e[i].p != NULL && e[i].p->lvl > 0 && strlen(e[i].p->nombre) > 0){
            Pokemon *pk = e[i].p;
            fprintf(f, "1\n");  // Pokemon presente
            fprintf(f, "%s\n", e[i].apodo);
            fprintf(f, "%s %s %s %d %d %d %d %d %d %d %d %d\n",
                pk->nombre, pk->tipo, pk->tipo2,
                pk->lvl, pk->xp, pk->at, pk->df,
                pk->atE, pk->dfE, pk->ps, pk->psMAX,
                pk->vel);
        } else {
            fprintf(f, "0\n");  // slot vacio
        }
    }
}

void cargarPartidaCompleta(Equipo e[], Pokemon p[], Inventario *inv, int *contEquipo, char ***mapa, int *dimensiones, char *ultimaCasilla) {
    FILE *f = fopen("partida_completa.txt", "r");
    int i;
    
    if(!f){
        printf("No se encontro partida guardada\n");
        return;
    }

    // Inicializar equipo vacio
    for(i = 0; i < 6; i++){
        if(e[i].p != NULL){
            free(e[i].p);
            e[i].p = NULL;
        }
        e[i].apodo[0] = '\0';
    }
    *contEquipo = 0;

    // Leer inventario
    if(fscanf(f, "%d %d %d\n", &inv->dinero, &inv->pokeballs, &inv->pociones) != 3){
        printf("Error leyendo inventario\n");
        fclose(f);
        return;
    }

    // Leer equipo
    for(i = 0; i < 6; i++){
        int tienePokemon;
        if(fscanf(f, "%d\n", &tienePokemon) != 1){
            printf("Error leyendo indicador del Pokemon (%d)\n", *contEquipo);
            fclose(f);
            return;
        }

        if(tienePokemon == 1){
            if(fgets(e[i].apodo, sizeof(e[i].apodo), f) == NULL){
                printf("Error leyendo apodo\n");
                fclose(f);
                return;
            }
            e[i].apodo[strcspn(e[i].apodo, "\n")] = '\0';

            e[i].p = (Pokemon*) malloc(sizeof(Pokemon));
            if(e[i].p == NULL){
                printf("Fallo al asignar memoria para Pokemon\n");
                fclose(f);
                return;
            }

            if(fscanf(f, "%24s %24s %24s %d %d %d %d %d %d %d %d %d\n",
                       e[i].p->nombre, e[i].p->tipo, e[i].p->tipo2,
                       &e[i].p->lvl, &e[i].p->xp, &e[i].p->at, &e[i].p->df,
                       &e[i].p->atE, &e[i].p->dfE, &e[i].p->ps, &e[i].p->psMAX,
                       &e[i].p->vel) != 12){
                printf("Error leyendo datos del Pokemon\n");
                free(e[i].p);
                e[i].p = NULL;
                fclose(f);
                return;
            }

            (*contEquipo)++;
        } else {
            e[i].p = NULL;
            e[i].apodo[0] = '\0';
        }
    }

    fclose(f);
    printf("Partida cargada correctamente desde partida_completa.txt\n");
    printf("Pokemon en equipo: %d\n", *contEquipo);
    
    system("pause");
    system("cls");
}

void elegirInicial(Equipo *e){
    int inicial;
    char sn;
    
    e->p = (Pokemon*) malloc(sizeof(Pokemon));
    
    if(e->p == NULL){
        printf("Error al asignar memoria\n");
        return;
    }
    
    do{
        system("cls");
        printf("Elige tu Pokemon inicial:\n");
        printf("1. Bulbasaur\n2. Squirtle\n3. Charmander\n---> ");
        scanf("%d", &inicial);
    } while(inicial < 1 || inicial > 3);

    do{
        system("cls");
        printf("Deseas ponerle un mote a tu Pokemon? (s/n)");
        sn = getch();
        sn = tolower(sn);
    } while(sn != 's' && sn != 'n');

    const char* nombres[] = {"Bulbasaur", "Squirtle", "Charmander"};
    const char* tipos[] = {"Planta", "Agua", "Fuego"};
    const char* tipos2[] = {"Veneno", "", ""};
    strcpy(e->p->nombre, nombres[inicial - 1]);
    strcpy(e->p->tipo, tipos[inicial - 1]);
    strcpy(e->p->tipo2, tipos2[inicial - 1]);

    e->p->lvl = 5;
    e->p->xp = 0;
    e->p->at = (rand() % 20) + 6;
    e->p->df = (rand() % 20) + 6;
    e->p->atE = (rand() % 20) + 6;
    e->p->dfE = (rand() % 20) + 6;
    e->p->ps = (rand() % 6) + 15;
    e->p->psMAX = e->p->ps;
    e->p->vel = (rand() % 20) + 6;

    if(sn == 's'){
        printf("\nElige un mote para tu %s: ", e->p->nombre);
        scanf("%24s", e->apodo);
    } else {
        strcpy(e->apodo, e->p->nombre);
    }

    printf("\nHas elegido a %s!\n\n", e->apodo);
    
    system("pause");
    system("cls");
}

void imprimirMapa(char **mapa, int dimensiones, char *ultimaCasilla){
	int i, j;
    int ancho = dimensiones;
    int alto = dimensiones;
    
    if(mapa == NULL || dimensiones <= 0){
        printf("Mapa no está disponible para imprimir\n");
        return;
    }

    printf("Estas en");
    
    switch(*ultimaCasilla){
        case '-':
            printf(" Tierra\n");
            break;
        case 'H':
            printf(" la Hierba Alta\n");
            break;
        case 'P':
            printf(" el Centro Pokemon\n");
            break;
        case 'T':
            printf(" la Tienda Pokemon\n");
            break;
        case 'O':
            printf(" un Gimnasio Pokemon\n");
            break;
        case 'A':
            printf(" un sitio de pesca\n");
            break;
        default:
            printf(" una zona desconocida\n");
            break;
    }

    for(i = 0; i < alto; i++){
        for(j = 0; j < ancho; j++){
            switch(mapa[i][j]){
                case '-':
                    printf(RESET_COLOR "[%c]", mapa[i][j]);
                    break;
                case 'H':
                    printf(VERDE_T "[%c]", mapa[i][j]);
                    break;
                case 'P':
                    printf(ROJO_T "[%c]", mapa[i][j]);
                    break;
                case 'T':
                    printf(AZUL_T "[%c]", mapa[i][j]);
                    break;
                case 'O':
                    printf(MAGENTA_T "[%c]", mapa[i][j]);
                    break;
                case 'A':
                    printf(CYAN_T "[%c]", mapa[i][j]);
                    break;
                default:
                    printf(RESET_COLOR "[%c]", mapa[i][j]);
                    break;
            }
        }
        printf(RESET_COLOR "\n");
    }

    printf("\n(WASD) | 1. Pokemon | 2. Bolsa | 3. Guardar | 4. Opciones\n---> ");
}

void curarPokemon(Inventario *inv, int pok, Equipo e[]){
	int psAntes = e[pok].p->ps;
    int psCurados = 0;
    
	system("cls");
	
	if(e[pok].p->ps == e[pok].p->psMAX){
		printf("Este pokemon ya tiene la vida al maximo\n");
	} else {
		e[pok].p->ps += 20;
		
        if(e[pok].p->ps > e[pok].p->psMAX){
        	e[pok].p->ps = e[pok].p->psMAX;
        }
		
		psCurados = e[pok].p->ps - psAntes;
		printf("Tu %s ha recuperado %dPS\n", e[pok].apodo, psCurados);
	}
	
	system("pause");
	system("cls");
}

void verDatos(Equipo e){
	
	system("cls");
	
    if(e.p == NULL){
        printf("No hay Pokemon en este slot\n");
        return;
    }

    printf("======= ESTADISTICAS DE %s =======\n", e.apodo);
    printf("Nombre:       %s\n", e.p->nombre);
    printf("Nivel:        %d\n", e.p->lvl);
    printf("Tipo:         %s", e.p->tipo);
    if(strcmp(e.p->tipo2, "0") == 0){
    	printf("\n");
	} else {
		printf("/%s\n", e.p->tipo2);
	} 
    printf("Experiencia:  %d\n", e.p->xp);
    printf("Ataque:       %d\n", e.p->at);
    printf("Defensa:      %d\n", e.p->df);
    printf("At. Esp.:     %d\n", e.p->atE);
    printf("Def. Esp.:    %d\n", e.p->dfE);
    printf("Velocidad:    %d\n", e.p->vel);
    printf("PS:           %d/%d\n", e.p->ps, e.p->psMAX);
    printf("===================================\n");
    system("pause");
}

void verEquipo(Equipo e[], Inventario *inv){
    int i, opc, pok, destino;
    bool salir = false;
    Pokemon *temp;
    char tempApodo[25], seguir;
    
    do{
	    system("cls");
	    printf("======== EQUIPO POKEMON ========\n");
	    for(i = 0; i < 6; i++){
	        printf("Slot %d:\n", i + 1);
	        if(e[i].p != NULL){
	            printf("\tNombre:  %s\n", e[i].apodo);
	            printf("\tNivel:  %d\n", e[i].p->lvl);
	            printf("\tPS:     %d/%d\n", e[i].p->ps, e[i].p->psMAX);
	        } else {
	            printf("\t(Vacio)\n");
	        }
	        printf("================================\n");
	    }
	    
	    printf("Deseas interactuar con tu equipo (s/n)");
	    do{
	    	seguir = getch();
	    	seguir = tolower(seguir);
		} while(seguir != 's' && seguir != 'n');
		
		if(seguir == 's'){
			printf("\nQue pokemon deseas seleccionar (1-6)\n---> ");
		    do{
		    	scanf("%d", &pok);
			} while(pok < 1 || pok > 6);
			pok--;
			
			if(e[pok].p == NULL){
				printf("Selecciona otro espacio\n");
			} else {
				printf("Que deseas hacer?\n1.Ver datos\n2.Mover\n3.Usar objeto\n4.Salir\n---> ");
				do{
					scanf("%d", &opc);
				} while(opc < 1 || opc > 4);
				
				if(opc == 1){
					verDatos(e[pok]);
				} else if(opc == 2){
					printf("Donde deseas mover a %s(1-6)\n---> ", e[pok].apodo);
					do{
						scanf("%d", &destino);
					} while(destino < 1 || destino > 6);
					destino--;
					
					if(e[destino].p == NULL){
						printf("Selecciona otro espacio\n");
					} else {
						temp = e[pok].p;
			            e[pok].p = e[destino].p;
			            e[destino].p = temp;
			
			            strcpy(tempApodo, e[pok].apodo);
			            strcpy(e[pok].apodo, e[destino].apodo);
			            strcpy(e[destino].apodo, tempApodo);
			            
			            printf("Movimiento realizado correctamente\n");
					}
					system("pause");
					system("cls");
				} else if(opc == 3){
					curarPokemon(inv, pok, e);
				} else if(opc == 4){
					salir = true;
				}
			}
		} else if(seguir == 'n'){
			printf("\nSaliendo...\n");
			system("pause");
			system("cls");
			salir = true;
		}
		    
	} while(!salir);
}

int atraparPokemonSalvaje(Inventario *inv, Equipo equipo[], Pokemon *salvaje){
	int i, probabilidad, ponerMote;
	char mote[25];
	
    if(inv->pokeballs <= 0){
        printf("\nNo tienes Pokeballs\n");
        system("pause");
        return 0;
    }

    inv->pokeballs--;

    probabilidad = rand() % 100;

    printf("\nLanzas una Pokeball...\n");
    system("pause");

    if(probabilidad < 50){  
    	inv->dinero += 200;
        for(i = 0; i < 6; i++){
            if(equipo[i].p == NULL){
            	printf("\nHas atrapado a %s!\n", salvaje->nombre);
            	
                equipo[i].p = (Pokemon*) malloc(sizeof(Pokemon));
			    if(equipo[i].p == NULL) {
			        printf("Error al asignar memoria\n");
			        return 0; 
			    }
                *(equipo[i].p) = *salvaje;
                
                printf("Deseas ponerle un mote a tu %s?\n1.Si\n2.No\n---> ", salvaje->nombre);
                do{
                	scanf("%d", &ponerMote);
				} while(ponerMote != 1 && ponerMote != 2);
				
                if(ponerMote == 1){
                	printf("Como quieres que se llame tu %s?\n---> ", salvaje->nombre);
                	scanf("%s", mote);
                	strcpy(equipo[i].apodo, mote); 	
				} else {
					strcpy(equipo[i].apodo, salvaje->nombre); 	
				}
                 
                system("pause");
                system("cls");
                return 1;
            }
        }
        printf("\nHas atrapado a %s, pero tu equipo esta lleno!\n", salvaje->nombre);
        printf("Se envia al PC\n");
        system("pause");
        system("cls");
        return 1;
    } else {
        printf("\n%s ha escapado de la Pokeball\n", salvaje->nombre);
        system("pause");
        system("cls");
        return 0;
    }
}

int abrirInventario(Inventario *inv, Equipo e[], Pokemon *salvaje, int *contEquipo){
    int opcion, i, elegido, cura;

    do{
        system("cls");
        printf("====== INVENTARIO ======\n");
        printf("1. Usar Pocion (%d disponibles)\n", inv->pociones);
        printf("2. Usar Pokeball (%d disponibles)\n", inv->pokeballs);
        printf("3. Salir\n");
        printf("Elige una opcion: ");
        opcion = getch() - '0';

        if(opcion == 1){
            if(inv->pociones <= 0){
                printf("\nNo tienes pociones\n");
                system("pause");
            } else {
                system("cls");
                printf("A que Pokemon quieres curar?\n");
                
                printf("======== EQUIPO POKEMON ========\n");
			
			    for(i = 0; i < 6; i++){
			        printf("Slot %d:\n", i + 1);
			        if(e[i].p != NULL){
			            printf("\tNombre:  %s\n", e[i].apodo);
			            printf("\tNivel:  %d\n", e[i].p->lvl);
			            printf("\tPS:     %d/%d\n", e[i].p->ps, e[i].p->psMAX);
			        } else {
			            printf("\t(Vacio)\n");
			        }
			        printf("================================\n");
			    }
                
                printf("Selecciona un numero (1-6): ");
                elegido = getch() - '1';

                if(elegido < 0 || elegido >= 6 || e[elegido].p == NULL){
                    printf("\nSeleccion invalida\n");
                } else {
                    if(e[elegido].p->ps == e[elegido].p->psMAX){
                        printf("\nEse Pokemon ya tiene la vida completa\n");
                    } else {
                        cura = 20; 
                        e[elegido].p->ps += cura;
                        
                        if(e[elegido].p->ps > e[elegido].p->psMAX){
                        	e[elegido].p->ps = e[elegido].p->psMAX;
						}
                            
                        inv->pociones--;
                        printf("\nHas curado a %s, ahora tiene %d/%d PS\n", e[elegido].apodo, e[elegido].p->ps, e[elegido].p->psMAX);
                    }
                }
                
                system("pause");
            }
        } else if(opcion == 2){
            return 1;
        } else if(opcion == 3){
        	system("cls");
            return 0;
        } else {
            printf("\nOpcion invalida\n");
            system("pause");
        }
    } while (1);
}

void combate(Equipo e[], Pokemon *salvaje, int *contEquipo, Inventario *inv){
    int danio, vivos = 0, i, atrapado, objeto;
    char opcion;
    
    system("cls");

    for(i=0;i<*contEquipo;i++){
        if(e[i].p->ps > 0){
            vivos++;
        }
    }

    if(vivos == 0){
        printf("\nNo tienes pokemons para luchar en el combate\nHas escapado con exito\n\n");
        return;
    }

    printf("Comienza el combate entre %s [%d] y %s [%d]\n\n", e[0].apodo, e[0].p->ps, salvaje->nombre, salvaje->ps);
    system("pause");
    system("cls");

    while(e[0].p->ps > 0 && salvaje->ps > 0){
    	printf("%s [%d] VS %s [%d]\n\n", e[0].apodo, e[0].p->ps, salvaje->nombre, salvaje->ps);
        printf("Elige una opcion:\n");
        printf("1. Luchar\n");
        printf("2. Bolsa\n");
        printf("3. Pokemons\n");
        printf("4. Huir\n");

        opcion = getch();

        if(opcion == '1'){
            if(e[0].p->vel >= salvaje->vel){
                danio = e[0].p->at - salvaje->df / 2;
                if(danio < 1){
                    danio = 1;
                }
                salvaje->ps -= danio;
                if(salvaje->ps < 0){
                    salvaje->ps = 0;
                }
                printf("%s [%d] ataca y causa %d de dano, %s [%d] queda con %d PS\n", e[0].apodo, e[0].p->ps, danio, salvaje->nombre, salvaje->ps + danio, salvaje->ps);
                if(salvaje->ps == 0){
                	inv->dinero += 200;
                    printf("%s ha sido debilitado\n", salvaje->nombre);
                    break;
                }
                system("pause");

                danio = salvaje->at - e[0].p->df / 2;
                if(danio < 1){
                    danio = 1;
                }
                e[0].p->ps -= danio;
                if(e[0].p->ps < 0){
                    e[0].p->ps = 0;
                }
                printf("%s [%d] ataca y causa %d de dano, %s [%d] queda con %d PS\n", salvaje->nombre, salvaje->ps, danio, e[0].apodo, e[0].p->ps + danio, e[0].p->ps);
                if(e[0].p->ps == 0){
                    printf("%s ha sido debilitado\n", e[0].apodo);
                    break;
                }
                system("pause");
                system("cls");
            } else {
                danio = salvaje->at - e[0].p->df / 2;
                if(danio < 1){
                    danio = 1;
                }
                e[0].p->ps -= danio;
                if(e[0].p->ps < 0){
                    e[0].p->ps = 0;
                }
                printf("%s [%d] ataca y causa %d de dano, %s [%d] queda con %d PS\n", salvaje->nombre, salvaje->ps, danio, e[0].apodo, e[0].p->ps + danio, e[0].p->ps);
                if(e[0].p->ps == 0){
                    printf("%s ha sido debilitado\n", e[0].apodo);
                    break;
                }
                system("pause");

                danio = e[0].p->at - salvaje->df / 2;
                if(danio < 1){
                    danio = 1;
                }
                salvaje->ps -= danio;
                if(salvaje->ps < 0){
                    salvaje->ps = 0;
                }
                printf("%s [%d] ataca y causa %d de dano, %s [%d] queda con %d PS\n", e[0].apodo, e[0].p->ps, danio, salvaje->nombre, salvaje->ps + danio, salvaje->ps);
                if(salvaje->ps == 0){
                	inv->dinero += 200;
                    printf("%s ha sido debilitado\n", salvaje->nombre);
                    break;
                }
                system("pause");
                system("cls");
            }
        } else if(opcion == '2'){
        	objeto = abrirInventario(inv, e, salvaje, contEquipo);
        	
            if(objeto == 1){ // se ha usado pokeball
            	atrapado = atraparPokemonSalvaje(inv, e, salvaje);
            	
            	if(atrapado == 0){
		        	//se ha escapado		        	
				} else if(atrapado == 1){
					return;				
				}
			} else if(objeto == 2){ //se ha usado pocion
				
			}
            
        } else if(opcion == '3'){
		    system("cls");
			verEquipo(e, inv);
			system("pause");
		} else if(opcion == '4'){
            printf("Has huido del combate\n");
            system("pause");
            return;
        } else {
            printf("Opcion invalida\n");
            system("pause");
            system("cls");
        }
    }

    if(e[0].p->ps > 0){
        printf("Has ganado el combate\n");
    } else {
        printf("Has perdido el combate\n");
    }
    system("pause");
}

void accionHierba(Pokemon p[], Equipo e[], int *contEquipo, Inventario *inv){
    int rng;
    
	rng = rand() % 151;

    if((rand() % 100) < 15){
        system("cls");
        printf("Un %s salvaje aparecio!\n", p[rng].nombre);
        system("pause");

        Pokemon salvaje = p[rng];
        printf("%s - NV:%d XP:%d AT:%d DF:%d AE:%d DE:%d PS:%d/%d VEL:%d\n", (p + rng)->nombre, (p + rng)->lvl, (p + rng)->xp, (p + rng)->at, (p + rng)->df, (p + rng)->atE, (p + rng)->dfE, (p + rng)->ps, (p + rng)->psMAX, (p + rng)->vel);

        combate(e, &salvaje, contEquipo, inv);

        system("cls");
    }
}

void accionCentroPokemon(Equipo e[], int *contEquipo){
	int i;
	
    printf("\nEstas en el Centro Pokemon\n");

    for(i = 0; i < *contEquipo; i++) {
        e[i].p->ps = e[i].p->psMAX; 
    }

    printf("Todos tus Pokemon han sido curados\n");
    system("pause");
}

void accionTienda(Inventario *inv){
    int opcion = 0;
    int cantidad = 0;

    do{
        system("cls");
        printf("Bienvenido a la Tienda\n");
        printf("Tienes %d pokemonedas\n", inv->dinero);
        printf("1. Pokeball (200)\n");
        printf("2. Pocion (150)\n");
        printf("0. Salir\n---> ");
        opcion = getch() - '0';

        if(opcion == 1){
            printf("Cuantas pokeballs deseas comprar? ");
            scanf("%d", &cantidad);
            
            if(inv->dinero >= cantidad * 200){
                inv->dinero -= cantidad * 200;
                inv->pokeballs += cantidad;
                printf("Compraste %d pokeballs\n", cantidad);
            } else {
                printf("No tienes suficiente dinero\n");
            }
            
        } else if(opcion == 2){
            printf("Cuantas pociones deseas comprar? ");
            scanf("%d", &cantidad);
            
            if(inv->dinero >= cantidad * 150){
                inv->dinero -= cantidad * 150;
                inv->pociones += cantidad;
                printf("Compraste %d pociones\n", cantidad);
                
            } else {
                printf("No tienes suficiente dinero\n");
            }
        }

        if(opcion != 0){
            system("pause");
        }

    } while(opcion != 0);
}

void accionAgua(Pokemon p[], Equipo e[], int *contEquipo, Inventario *inv){
	int rng;
    
	do{
        rng = rand() % 151;
    } while(strcmp(p[rng].tipo, "Agua") != 0 && strcmp(p[rng].tipo2, "Agua") != 0);

    system("cls");
    printf("Un %s salvaje aparecio!\n", p[rng].nombre);
    system("pause");

    Pokemon salvaje = p[rng];
    printf("%s - NV:%d XP:%d AT:%d DF:%d AE:%d DE:%d PS:%d/%d VEL:%d\n", (p + rng)->nombre, (p + rng)->lvl, (p + rng)->xp, (p + rng)->at, (p + rng)->df, (p + rng)->atE, (p + rng)->dfE, (p + rng)->ps, (p + rng)->psMAX, (p + rng)->vel);
	
    combate(e, &salvaje, contEquipo, inv);

    system("cls");
}

void verBolsa(Inventario *inv, Equipo e[]){
	int objeto, i, pok, psAntes, psCurados;
	
	system("cls");
	printf("======= INVENTARIO =======\n");
    printf("Dinero:      %d$\n", inv->dinero);
    printf("1. Pokeballs:   %d\n", inv->pokeballs);
    printf("2. Pociones:    %d\n", inv->pociones);
    printf("==========================\n");
    
    printf("Que objeto deseas usar?\n---> ");
    do{
    	scanf("%d", &objeto);
	} while(objeto < 1 || objeto > 2);
	
	if(objeto == 1){
		if(inv->pokeballs <= 0){
			printf("No tienes suficientes objetos\n");
		} else {
			printf("No puedes usar este objeto en este momento\n");
			system("pause");
	   	 	system("cls");
		}
		
	} else if(objeto == 2){
		if(inv->pociones <= 0){
			printf("No tienes suficientes objetos\n");
		} else {
			printf("======== EQUIPO POKEMON ========\n");
			
		    for(i = 0; i < 6; i++){
		        printf("Slot %d:\n", i + 1);
		        if(e[i].p != NULL){
		            printf("\tNombre:  %s\n", e[i].apodo);
		            printf("\tNivel:  %d\n", e[i].p->lvl);
		            printf("\tPS:     %d/%d\n", e[i].p->ps, e[i].p->psMAX);
		        } else {
		            printf("\t(Vacio)\n");
		        }
		        printf("================================\n");
		    }
			    
			printf("Que pokemon deseas seleccionar (1-6)\n---> ");
		    do{
		    	scanf("%d", &pok);
			} while(pok < 1 || pok > 6);
			pok--;
			
			system("cls");
			if(e[pok].p == NULL){
                printf("Selecciona otro espacio\n");

            } else if(e[pok].p->ps == e[pok].p->psMAX){
                printf("Este Pokemon ya tiene la vida al maximo\n");

            } else {
                psAntes = e[pok].p->ps;

                e[pok].p->ps += 20;
                if(e[pok].p->ps > e[pok].p->psMAX){
                    e[pok].p->ps = e[pok].p->psMAX;
                }

                psCurados = e[pok].p->ps - psAntes;
                inv->pociones--;

                printf("Tu %s ha recuperado %d PS\n", e[pok].apodo, psCurados);
            }

            system("pause");
            system("cls");
		}
	}
}

char movPersonaje(char **mapa, int dimensiones, char *ultimaCasilla, Pokemon p[], Equipo e[], Inventario *inv){
    char mov = tolower(getch());
    char resultado = *ultimaCasilla;  
    int i, j, x = -1, y = -1;
    int alto = dimensiones;
    int ancho = dimensiones;

    for(i = 0; i < alto; i++){
        for(j = 0; j < ancho; j++){
            if(mapa[i][j] == 'O'){
                x = i;
                y = j;
                mapa[i][j] = *ultimaCasilla;  
                break;
            }
        }
        if(x != -1) break;
    }

    if(mov == 'w' && x > 0){
        x--;
    } else if(mov == 's' && x < alto - 1){
        x++;
    } else if(mov == 'a' && y > 0){
        y--;
    } else if(mov == 'd' && y < ancho - 1){
        y++;
    }

    *ultimaCasilla = mapa[x][y];

    switch(mapa[x][y]){
        case 'H': //Pisando Hierva
        case 'P': //Pisando Centro Pokemon
        case 'T': //Pisando Tienda
        case 'A': //Pisando Agua
            resultado = mapa[x][y];
            break;
        default:
            resultado = '-';
            break;
    }

    switch(mov){
        case '1':
            verEquipo(e, inv);
            break;
        case '2':
        	verBolsa(inv, e);
            break;
        case '3':
            return 'X';
            break;
        case '4':
            //Opciones
            break;
    }

    mapa[x][y] = 'O';

    return resultado;
}

void mostrarPokedex(Pokemon p[]){
	int i;
	
    for(i = 0; i < 151; i++){
        printf("%s - NV:%d XP:%d AT:%d DF:%d AE:%d DE:%d PS:%d/%d VEL:%d\n",
        p[i].nombre, p[i].lvl, p[i].xp, p[i].at, p[i].df,
        p[i].atE, p[i].dfE, p[i].ps, p[i].psMAX, p[i].vel);
    }
}

int main() {
    Equipo e[6] = {0};
    Pokemon p[151];
    Inventario inv;
    int contEquipo = 0, i, dimensiones;
    bool finPartida = false;
    char **mapa, ultimaCasilla = '-', jugador, sn;
    
    srand(time(NULL));
	
	printf("Deseas cargar Partida? (s/n)");
	do{
		sn = getch();
		sn = tolower(sn);
	} while(sn != 's' && sn != 'n');
	printf("\n");
	
	inicializarMapa(&mapa, &dimensiones);
	inicializarPokedex(p);
	
	if(sn == 's'){
        cargarPartidaCompleta(e, p, &inv, &contEquipo, &mapa, &dimensiones, &ultimaCasilla);
    } else {
        inicializarInventario(&inv);
        elegirInicial(&e[contEquipo]);
        contEquipo++;
    }
    
    do{
        imprimirMapa(mapa, dimensiones, &ultimaCasilla);
        
        jugador = movPersonaje(mapa, dimensiones, &ultimaCasilla, p, e, &inv);
	        if(jugador == 'H'){
	        	accionHierba(p, e, &contEquipo, &inv);
			} else if(jugador == 'P'){
				accionCentroPokemon(e, &contEquipo);
			} else if(jugador == 'T'){
				accionTienda(&inv);	
			} else if(jugador == 'A'){
				accionAgua(p, e, &contEquipo, &inv);
			} else if(jugador == 'X'){
				guardarPartidaCompleta(e, contEquipo, &inv, mapa, dimensiones, ultimaCasilla);
                finPartida = true;
			}
			
        system("cls");
    } while(!finPartida);
	
	if(mapa != NULL){
        for(int i=0; i<dimensiones; i++){
            free(mapa[i]);
        }
        free(mapa);
    }
    printf("Gracias por jugar\n");
	
    return 0;
}

