#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Declaracion de estructuras */

struct Cliente {                  // LISTA CIRCULAR DE CLIENTES
    char *nombre;
    char *rut;
    char *direccion;
    char *ciudad;
    char *telefono;
    char *email;
    int   edad;
    int   ID_consulta;
    int   estado_reclamos;       /*  numero de reclamos creados por el usuario */
    int mas_clientes;
    struct Cliente *izq , *der ;
};

struct pila{
    struct Cliente *valor;
    struct pila *sig;
};

struct Departamento {            // LISTA SIMPLE DEPARTAMENTOS
    char *nombre;
    char *telefono;
    int valoracion;
    struct Departamento * sig;
};

struct Sucursales {             //LISTA DOBLEMENTE ENLAZADA DE SUCURSALES
    char *nombre_suc;
    char *direccion_suc;
    char *comuna_suc;
    char *ciudad_suc;
    char *fono_suc;
    int  ID;

    char  *name_boss;           // JEFATURA
    char  *rut_boss;
    int    id_boss ;

    struct Departamento *Lista_dpto;

    struct Sucursales *sig, *ant;
};

struct Regiones {               /*  VECTOR DE PUNTEROS DE REGIONES */
    char *nombre;
    int   ID;
    struct Sucursales *Lista_sucursales;
};

struct Empresa {
    char *nombre;
    char *rut;
    int     ultimo;
    int     clave;

    struct Regiones *Region [15];
    struct Cliente *Arbol_clientes;
};

//------------------------------------------------------------------- FUNCIONES DEL ARBOL  //

void agregar_clientes(struct Cliente **raiz);
void mostrar_clientes(struct Cliente *inicio);
void modificar_clientes(struct Cliente* inicio,int id);
struct Cliente * pop(struct pila **cima);
void push(struct pila **cima,struct Cliente *nuevo);
void guardar_clientes(struct Empresa *Empresa_Proyecto);
void cargar_clientes(struct Cliente **raiz);
void eliminar_cliente (struct Cliente **inicio,int ID );
void reemplazar(struct Cliente **inicio,struct Cliente** aux);
struct Cliente* busqueda_clientes(struct Cliente *arbol, struct Cliente **ant, int ID);
void postorden_cliente_reclamon(struct Cliente *p, struct Cliente**cliente_reclamon);

//------------------------------------------------------------------- FUNCIONES EXTRAS  //
struct Departamento* mejorevaluado(struct Empresa *Empresa_Proyecto,int pos);
void cliente_reclamon(struct Empresa *Empresa_Proyecto);
//------------------------------------------------------------------- CREACION DE NODOS  //

struct Empresa *Crear_Empresa();
void   Crear_regiones (struct Empresa  ** Empresa_Proyecto );
struct Sucursales  *Crear_sucursal();
struct Departamento *Crear_Departamento();

//------------------------------------------------------------------- AGREGAR NODOS     //

void Enlazar_Suc(struct Empresa **Empresa_Proyecto , struct Sucursales *nueva , int pos );
void Enlazar_Departamentos( struct Departamento **head,struct Departamento *nuevo);
void Agregar_regiones(struct Empresa **Empresa_Proyecto);

//------------------------------------------------------------------- ELIMINACION       //

void Eliminar_Suc(struct Empresa **Empresa_Proyecto ,int pos);
void Eliminar_departamento(struct Departamento **head);
void Eliminar_region(struct Empresa **Empresa_Proyecto, int pos);

//------------------------------------------------------------------- MENTENEDOR DEL SISTEMA    //

void Funciones_Administradoras( struct Empresa *Empresa_Proyecto);

//------------------------------------------------------------------- EDITAR DATOS  POR NIVEL //

void Modificar_Sucursal(struct Empresa **Empresa_Proyecto,int pos);
void Modificar_Departamento(struct Empresa **Empresa_Proyecto,int pos);
void modificar_region(struct Empresa **Empresa_Proyecto);

//------------------------------------------------------------------- LISTAR NIVELES    //
void Mostrar_regiones(struct Empresa *Empresa_Proyecto);
void mostrar_Sucursales(struct Empresa *Empresa_Proyecto,int pos);
void Mostrar_datos_suc(struct Sucursales * rec ,int i);
void Mostrar_Departamento(struct Empresa *Empresa_Proyecto,int pos );
void Mostrar_datos_departamentos(struct Departamento *rec_dep ,int i);

//------------------------------------------------------------------- SALVADO DE DATOS  //

void Guardar_Datos_Regiones(struct Empresa *Empresa_Proyecto );
void Guardar_Datos(struct Empresa *Empresa_Proyecto );
void Guardar_Datos_Sucursales(struct Empresa *Empresa_Proyecto );
void Guardar_Datos_Departamento(struct Empresa *Empresa_Proyecto );
void Guardar_Reclamos( struct Cliente **Usuario_rec   );
void Guardar_Consultas( struct Cliente **Usuario_rec );

//------------------------------------------------------------------- SEARCH PTR XD//
struct Departamento* buscar_depto(struct Departamento *nodo,char *nombredepto);
struct Sucursales * Buscar_sucursal( struct Sucursales *Lista_sucursales, int id );
struct Sucursales * Buscar_sucursal_dep( struct Sucursales *Lista_sucursales, char *nombrejefe );
int buscar_region(struct Empresa *Empresa_Proyecto, int id);

//------------------------------------------------------------------- LOADS //

struct Empresa *Cargar_Empresa();

//------------------------------------------------------------------- MODULOS COMPLEMENTARIOS //

int Validar_usuario( struct Empresa *Empresa_Proyecto );
int validar_rut(char rut[]);
int validar_clave(struct Empresa *Empresa_Proyecto,int master_key);
void Cambiar_clave(struct Empresa *Empresa_Proyecto );
int POS();  // validacion de indice que ingrese el usuario retorna el indice
int Pos();
int Generar_ID_CONSULTA(); // NUMERO DE 5 CIFRAS

//------------------------------------------------------------------------- FIN DE DECLARACIONES

//------------------------------------------------------------------------- INICIO MAIN
main() {
    int i,op,op2,master_key,estado,ID_cliente ,flag,may=-1,pos,s;
    FILE *EMP=NULL;
    char buffer[30];
    // inicializacion del puntero principal del programa
    struct Empresa *Empresa_Proyecto=NULL;
    struct Cliente *Usuario=NULL,*Usuario_rec=NULL,*AUX_ID=NULL,*aux_buscar=NULL;
    struct Sucursales *buscar=NULL,*suc=NULL;
    struct Departamento *buscar_dep=NULL,*nodo=NULL;
//------------------------------------------------------------------------- CARGA EMPRESA


    if((EMP=fopen("Datos_Empresa.txt","r"))!=NULL){

         Empresa_Proyecto=Cargar_Empresa();

    }else{

        /*  crea nodo del sistema  */
        Empresa_Proyecto=Crear_Empresa();

        Guardar_Datos(Empresa_Proyecto );

    }

//------------------------------------------------------------------------- VENTANA INICIO
    /*  carga pantalla de inicio */
    system("Inicio.exe");

    /* Crea structuras del programa y lee datos de los clientes en txt "Datos_Clientes" */

    Crear_regiones(&Empresa_Proyecto);

    cargar_clientes(&Empresa_Proyecto->Arbol_clientes);




    Guardar_Datos_Regiones(Empresa_Proyecto );

    /*  menu */
    do{

        system("cls");
        printf("\n\t %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c",22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22);
        printf("\n\t%c                                         %c\n\t%c          ATENCI%cN AL PUBLICO            %c\n\t%c                                         %c\n",22,22,22,224,22,22,22);
        printf("\t%c          EMPRESA    [%s]         %c\n",22,Empresa_Proyecto->nombre,22 );
        printf("\t%c            RUT   [%s]             %c\n",22,Empresa_Proyecto->rut,22 );
        printf("\t %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\n\n",22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22);

//------------------------------------------------------------------------- VENTANA MENU
        op=system("Menu.exe");

        switch(op) {

        case(1):

                printf("\n\t\20 Ingrese ID de consulta personal \n\t\20 ");
                scanf("%d",&ID_cliente);
                Usuario=busqueda_clientes(Empresa_Proyecto->Arbol_clientes ,&aux_buscar, ID_cliente);

                    if( Usuario == NULL ){

                         printf("\n\t\20ID INVALIDA");
                         system("pause");
                         flag=1;


                }else{

                    do {
//------------------------------------------------------------------------- VENTANA CLIENTES
                        op2=system("Clientes.exe");

                        switch(op2) {

                        case(1):
                            Usuario_rec=busqueda_clientes(Empresa_Proyecto->Arbol_clientes ,&aux_buscar, ID_cliente);
                            flag=0;

                            if( Usuario_rec == NULL ){
                                if(flag == 0 ){
                                    printf("ID INVALIDA");
                                    system("pause");
                                    flag=1;
                                }
                            }else{
                                Guardar_Consultas(&Usuario_rec );

                            }
                            break;
                        case(2):

                            Usuario_rec=busqueda_clientes(Empresa_Proyecto->Arbol_clientes ,&aux_buscar, ID_cliente);
                            flag=0;

                                if( Usuario_rec == NULL ){
                                    if(flag == 0 ){
                                        printf("ID INVALIDA");
                                        system("pause");
                                        flag=1;
                                    }
                                }else{
                                    pos=Pos()-1;
                                    fflush(stdin);
                                    printf("\n\t\20 INGRESE EL ID DE LA SUCURSAL \n");
                                    scanf("%d",&s);
                                    buscar=(Empresa_Proyecto->Region[pos])->Lista_sucursales;
                                    if(buscar){

                                        suc= Buscar_sucursal( buscar,s);
                                        if(suc==NULL){
                                            return;
                                        }else{
                                           printf("\n\t\20Ingrese nombre de depto donde quiere reclamar\n");
                                           scanf("%s", buffer);
                                           buscar_dep=buscar_depto(suc->Lista_dpto,buffer);
                                           if(buscar_dep==NULL){
                                           return;

                                           }else{
                                            buscar_dep->valoracion--;
                                            Guardar_Reclamos( &Usuario_rec );
                                            //Guardar_Datos_Clientes(Empresa_Proyecto );
                                            guardar_clientes(Empresa_Proyecto);/*  llamada para
                                            actualizar datos pues estado de reclamos se aumento y debe
                                            guardarse en fichero Datos_clientes */
                                           }
                                        }


                                }
                                }
                            break;


                        case(6):
                            system("cls");
                            cliente_reclamon(Empresa_Proyecto);
                            break;

                        case(7):

                            buscar_dep=mejorevaluado(Empresa_Proyecto,POS()-1);
                            system("pause");
                            if(buscar_dep==NULL){
                                printf("NO HAY NODOS CREADOS");
                            }else{
                            printf("\n\t\20El Departamento mejor evaluado es : %s\n\t\20 con  Evaluacion = %d  \n",buscar_dep->nombre,buscar_dep->valoracion);
                            }
                            system("pause");
                            break;


                        case(5):
                            break;

                        default:
                            system("cls");
                            printf("\n\t\20 A%cn no tenemos esa opci%cn intente denuevo\n\n\n\n\n\n\n",163, 162);
                            system("pause");
                        }
                    } while(op2!=5);
                }
                break;

        case(2):
                agregar_clientes(&Empresa_Proyecto->Arbol_clientes);
                guardar_clientes( Empresa_Proyecto);
                break;

        case(3):
            do {
                system("cls");
                printf("\n\n\t MENU ADMINISTRADOR  \n\n");
                printf("\t1) INGRESAR CLAVE     \n");
                printf("\t2) CAMBIAR CLAVE \n");
                printf("\t3) OLVIDO SU CLAVE    \n");
                printf("\n\t4) %c%c VOLVER \n\n\t\20 ",174,174);
                scanf("%d",&op2);
                switch(op2) {

                case(1):
                    do {
                        system("cls");
                        printf("\n\t\20DIGITE SU CLAVE:   inicial (1234)\n\t\20 ");
                        scanf("%d",&master_key);
                        estado = validar_clave( Empresa_Proyecto , master_key);
                    } while(estado !=0 ); //0 correcto 1 mala

                    Funciones_Administradoras( Empresa_Proyecto);
                    break;

                case(2):
                    Cambiar_clave( Empresa_Proyecto );
                    break;

                case(3):
                    printf("\n\t\20 SU CLAVE ES %d \n",Empresa_Proyecto->clave );///
                    system("pause");

                    break;
                case(4):
                    break;
                default:
                    system("cls");
                    printf("\n\t\20 A%cn no tenemos esa opci%cn intente denuevo\n\n\n\n\n\n\n",163,162);
                    system("pause");
                    system("cls");
                }

            } while(op2!=4);
            break;
        case(4):
            system("cls");
            printf("\n\n\n     \20\20\20 ADIOS VUELVA PRONTO \21\21\21\n\n\n\n\t\t[by bekan-venen-kakar00t-JUD0]/.\n");
            return 0;

        default:
            system("cls");
            printf("\n\t\20 Opci%cn no se encuentra disponible\n\n\n\n\n\n\n",162);
            system("pause");
            system("cls");
        }
    }while(op!=4);

}//------------------------------------------------------------------------- FIN MAIN

struct Empresa *Crear_Empresa() {
    struct Empresa *nuevo=NULL;
    char buffer[20];
    int i,rut_val;
    nuevo=((struct Empresa*)malloc(sizeof (struct Empresa)));

    printf("[by bekan-venen-kakar00t-JUD0]/.\n\n\tATENCI%cN AL PUBLICO\n\n   A continuaci%cn se piden los datos necesarios\npara iniciar el programa. \n\20 Escriba el nombre de la empresa  : ", 224, 162);
    fflush(stdin);
    scanf(" %[^\n]",buffer);
    nuevo->nombre=(char*)malloc(sizeof(char)*strlen(buffer)+1);

    strcpy(nuevo->nombre, buffer);
    fflush(stdin);
    do {

        printf("\n\20 Escriba rut de empresa [ %s ]:  (12345678-9) ",nuevo->nombre);
        scanf(" %[^\n]",buffer);
        rut_val=validar_rut(buffer);	//	Por mientras no valida rut, falta arreglarlo.
        // rut_val=0;

    } while(rut_val!=1);

    nuevo->rut=(char*)malloc(sizeof(char)*strlen(buffer)+1);
    strcpy(nuevo->rut, buffer);
    printf("\n->Cargando datos de la empresa\n ");
    for(i=0; i<15 ; i++) {   // seteando vector de punteros
        nuevo->Region[i]=NULL;
        printf(".");
    }
    printf("\n->Creando datos de las regiones \n ");
    nuevo->clave=1234;          // seteando clave de la empresa
    printf("\n->Creando datos de la empresa\n ");
    nuevo->Arbol_clientes=NULL;  // seteando puntero de clientes
    printf("\n->Creando datos de sucursales\n ");
    printf("\n->Ok\n");
    system("\n\n\npause");
    return nuevo;
}

void Crear_regiones(struct Empresa  **Empresa_Proyecto ) {
    /* el vector de regiones de crea al comenzar
    el programa agregandole sus respectivos nombres e indices */
    char *reg[15] = {"Region de Arica y Parinacota","Region de Tarapaca",
                     "Region de Antofagasta","Region de Atacama","Region de Coquimbo",
                     "Region de Valparaiso","Region Metropolitana de Santiago",
                     "Region del Libertador General Bernardo O Higgins","Region del Maule",
                     "Region del Biobio","Region de la Aracucanía","Region de los Ríos",
                     "Region de los Lagos","Region de Aisén del General Carlos Ibáñez del Campo",
                     "Region de Magallanes y la Antártica Chilena"
                    };
    int pos;
    for( pos=0; pos<15; pos++) {

        (*Empresa_Proyecto)->Region[pos]=(struct Regiones*) malloc (sizeof(struct Regiones));

        (*Empresa_Proyecto)->Region[pos]->nombre=(char*)malloc(sizeof(char)*strlen(reg[pos])+1);
        strcpy((*Empresa_Proyecto)->Region[pos]->nombre, reg[pos]);

        (*Empresa_Proyecto)->Region[pos]->ID=pos+1;

        (*Empresa_Proyecto)->Region[pos]->Lista_sucursales=NULL; //seteando nodo sucursal de cada region

    }
    (*Empresa_Proyecto)->ultimo=pos;  // se manejara de forma contigua (var ultimo)
}

int validar_clave(struct Empresa *Empresa_Proyecto,int master_key) {
    if( master_key == Empresa_Proyecto->clave) {
        return 0;
    }
    printf("\n\t\20Clave incorrecta \n");
    system("pause");
    return 1;
}

void Cambiar_clave(struct Empresa *Empresa_Proyecto ) {
    char buffer[20];
    int key1, key2,error=0;

    system("cls");
    printf("\n\t\20 DIGITE EL RUT DE LA EMPRESA PARA CAMBIAR CLAVE \n\t \20 ");
    scanf("%s",buffer);
    do {
        if( strcmp( Empresa_Proyecto->rut,buffer )==0) {
            printf("\n\t\20 DIGITE LA NUEVA CLAVE  \20");
            scanf("%d",&key1);
            printf("\n\t\20 DIGITE NUEVAMENTE  LA  CLAVE \20");
            scanf("%d",&key2);
            system("cls");
            if(key1 == key2 ) {
                Empresa_Proyecto->clave =key1;
                printf("\n\t\20 CLAVE CAMBIADA EXITOSAMENTE \n\n");
                system("pause");
                return;
            } else {
                printf("\n\t\20  LAS CLAVES NO COINCIDEN  \n\n");
                error=1;
                system("pause");
            }
        }
    } while(error==1);
}

void Funciones_Administradoras( struct Empresa *Empresa_Proyecto) {

    char buffer[30];
    int reg;
    int op,s, pos,id_region,aux,ID,*may=0,flag;
    struct Sucursales *new_suc=NULL, *buscar=NULL,*suc=NULL;
    struct Cliente *Usuario_rec=NULL,*aux_buscar=NULL;
    struct Departamento *nodo=NULL;
    do {
        system("cls");
        op=system("Administrador.exe");              //------------------------------------------VENTANA
        system("cls");

        switch(op) {

        case(1):
            system("cls");
            Agregar_regiones(&Empresa_Proyecto);
            system("pause");
            break;

        case(2):
            Enlazar_Suc(&Empresa_Proyecto , Crear_sucursal() ,  POS()-1 );
            Guardar_Datos_Sucursales(Empresa_Proyecto);
            break;

        case(3):

            pos=POS()-1;
            fflush(stdin);
            printf("\n\t\20 INGRESE EL ID DE LA SUCURSAL \n");
            scanf("%d",&s);
            buscar=Empresa_Proyecto->Region[pos]->Lista_sucursales;
                if(buscar){

                    suc= Buscar_sucursal( buscar,s);
                    if(suc==NULL){
                    return;
                    }
                    Enlazar_Departamentos( &suc->Lista_dpto, Crear_Departamento());
                    Guardar_Datos_Departamento(Empresa_Proyecto );
                }else{
                    printf("\n\t\20No hay sucursales\n");
                    system("PAUSE");
                    return;
                }
            break;

        case(4):
            //Enlazar_clientes(&Empresa_Proyecto, Crear_cliente());
            agregar_clientes(&Empresa_Proyecto->Arbol_clientes);
            guardar_clientes( Empresa_Proyecto);
            break;

        case(5):
            system("cls");
            printf("\n\t\20Ingrese ID de la regi%cn a eliminar \n\t",162);
            scanf("%d", &id_region);
            aux=buscar_region(Empresa_Proyecto, id_region);
            printf("%d", aux);
            if(aux!=-1){
                Eliminar_region(&Empresa_Proyecto,aux);
            }else{
                printf("\n\t\20Ingrese una id valida\n");
                system("pause");
            }
            system("pause");
            break;

        case(6):
            Eliminar_Suc(&Empresa_Proyecto,POS()-1);
            break;

        case(7):
            pos=POS()-1;
            printf("\n\t\20INGRESE EL ID DE LA SUCURSAL \n");
            scanf("%d",&s);
            buscar=Empresa_Proyecto->Region[pos]->Lista_sucursales;
                if(buscar){
                    suc= Buscar_sucursal( buscar,s);
                    if(suc==NULL){
                    return;
                    }
                    Eliminar_departamento(&suc->Lista_dpto);
                }else{
                    printf("\n\t\20No hay sucursales creadas\n");
                    system("PAUSE");
                    return;
                }
            break;

        case(8):

              printf("Ingrese ID de consulta para  eliminar su cliente :\n");
              scanf("%d", &ID);
              eliminar_cliente(&Empresa_Proyecto->Arbol_clientes, ID);
              guardar_clientes(Empresa_Proyecto );


//            Eliminar_Clientes(&Empresa_Proyecto);
            break;

        case(9):

            system("cls");
            modificar_region(&Empresa_Proyecto);
            system("pause");
            break;

        case(10):
            Modificar_Sucursal(&Empresa_Proyecto,POS()-1);
            break;

        case(11):
            Modificar_Departamento(&Empresa_Proyecto,POS()-1);

            break;

        case(12):
            printf("\n\t\20 Ingrese la ID de consulta del cliente , para eliminarlo \n\t");
            scanf("%d",&ID);
            modificar_clientes(Empresa_Proyecto->Arbol_clientes,ID);
            guardar_clientes(Empresa_Proyecto);
            break;

        case(13):

            system("cls");
            Mostrar_regiones(Empresa_Proyecto);
            system("pause");
            break;

        case(14):
            system("cls");
            mostrar_Sucursales(Empresa_Proyecto,POS()-1);
            system("pause");
            break;

        case(15):
            Mostrar_Departamento(Empresa_Proyecto,POS()-1);
            nodo=mejorevaluado(Empresa_Proyecto,POS()-1);
            system("pause");
            if(nodo==NULL){
                printf("NO HAY NODOS CREADOS");
            }
            else{
            printf("\n\t\20El Departamento mejor evaluado es : %s con  Evaluacion = %d  \n",nodo->nombre,nodo->valoracion);
            }
            system("pause");
            break;

        case(16):
            system("cls");
            mostrar_clientes(Empresa_Proyecto->Arbol_clientes );
            system("pause");
            break;



        case(18):
            system("cls");
            printf("\n\n\t\20 Ingrese ID de consulta personal \n\t\20 ");
            scanf("%d",&ID);
            Usuario_rec=busqueda_clientes(Empresa_Proyecto->Arbol_clientes ,&aux_buscar, ID);
            flag=0;

            if( Usuario_rec == NULL ){
                if(flag == 0 ){
                    printf("\n\n\t\20ID INVALIDA\n\t");
                    system("pause");
                    flag=1;
                }
            }else{
                printf("\n=======================    //   =========================\n");
                printf("\20 CLIENTE :\n");
                printf("\t\t\21 NOMBRE      : %s \n", Usuario_rec->nombre);
                printf("\t\t\21 RUT         : %s \n", Usuario_rec->rut);
                printf("\t\t\21 DIRECCION   : %s \n", Usuario_rec->direccion);
                printf("\t\t\21 CIUDAD      : %s \n", Usuario_rec->telefono);
                printf("\t\t\21 TELEFONO    : %s \n", Usuario_rec->ciudad);
                printf("\t\t\21 EMAIL       : %s \n\n", Usuario_rec->email);
                printf("\t\t\21 EDAD        : %d \n", Usuario_rec->edad);
                printf("\t\t\21 ID DE CONSULTA  : %d \n\n", Usuario_rec->ID_consulta);

            }
            system("pause");
            break;




        case(17)://volver
            break;

        default:
            system("cls");
            printf("\n\t\20 A%cn no tenemos esa opci%cn intente denuevo\n\n\n\n\n\n\n",163,162);
            system("pause");
            system("cls");
        }
    } while(op!=17);

}

struct Sucursales  *Crear_sucursal() {

    struct Sucursales *nueva=NULL;
    char buffer[50];
    int rut_val=0;
    nueva=(struct Sucursales*)malloc(sizeof(struct Sucursales));
    system("cls");
    fflush(stdin);
    printf("\n\n\t CREAR SUCURSAL \n\n\t\20Ingrese el nombre: ");
    scanf("%[^\n]",buffer);

    nueva->nombre_suc   =(char*)malloc(sizeof(char)*strlen(buffer)+1);
    strcpy(nueva->nombre_suc, buffer);

    fflush(stdin);
    printf("\n\t\20Ingrese ID: ");
    scanf("%d", &nueva->ID);

    fflush(stdin);
    printf("\n\t\20Ingrese la ciudad: ");
    scanf("%[^\n]", buffer);
    nueva->ciudad_suc=(char*)malloc(sizeof(char)*strlen(buffer)+1);
    strcpy(nueva->ciudad_suc, buffer);

    fflush(stdin);
    printf("\n\t\20Ingrese la comuna: ");
    scanf("%[^\n]", buffer);
    nueva->comuna_suc=(char*)malloc(sizeof(char)*strlen(buffer)+1);
    strcpy(nueva->comuna_suc, buffer);
    fflush(stdin);

    printf("\n\t\20Ingrese la direcci%cn: ", 162);
    scanf("%[^\n]", buffer);
    nueva->direccion_suc=(char*)malloc(sizeof(char)*strlen(buffer)+1);
    strcpy(nueva->direccion_suc, buffer);

    fflush(stdin);
    printf("\n\t\20Ingrese el tel%cfono: ", 130);
    scanf("%[^\n]", buffer);
    nueva->fono_suc=(char*)malloc(sizeof(char)*strlen(buffer)+1);
    strcpy(nueva->fono_suc, buffer);

    fflush(stdin);
    printf("\n\t\20Datos del Jefe de Sucursal : ");
    printf("\n\t\20Ingrese su nombre completo : ");
    scanf("%[^\n]", buffer);
    nueva->name_boss=(char*)malloc(sizeof(char)*strlen(buffer)+1);
    strcpy(nueva->name_boss ,buffer);

    do {

        fflush(stdin);
        printf("\n\t\20Ingrese el rut del Jefe de Sucursal : ");
        scanf("%[^\n]", buffer);
        rut_val =validar_rut(buffer);

    } while(rut_val!=1);

    nueva->rut_boss=(char*)malloc(sizeof(char)*strlen(buffer)+1);
    strcpy(nueva->rut_boss,buffer);

    fflush(stdin);
    printf("\n\t\20Ingrese ID del boss: ");
    scanf("%d", &nueva->id_boss);

    fflush(stdin);
    nueva->Lista_dpto=NULL;

    nueva->sig=NULL;
    nueva->ant=NULL;

    return nueva;
}

void Enlazar_Suc(struct Empresa **Empresa_Proyecto , struct Sucursales *nueva , int pos ) {

    struct Sucursales *rec=(*Empresa_Proyecto)->Region[pos]->Lista_sucursales;

    if ( (*Empresa_Proyecto)->Region[pos]->Lista_sucursales==NULL) {
        (*Empresa_Proyecto)->Region[pos]->Lista_sucursales=nueva;  // primer caso
    } else {
        while(rec) {
            if(rec->sig==NULL) {
                rec->sig=nueva;
                rec->sig->ant=rec;
                rec=nueva;
            }
            rec=rec->sig;
        }
    }
    printf("\n\t\20Sucursal creada con %cxito \n\n\n\n",130);
    system("pause");
}

void Eliminar_Suc(struct Empresa **Empresa_Proyecto, int pos) {
    struct Sucursales *rec=(*Empresa_Proyecto)->Region[pos]->Lista_sucursales;
    int id_aux;

    system("cls");
    printf("\n\t\20Ingrese id\n");
    scanf("%d",&id_aux);

    if(!(*Empresa_Proyecto)->Region[pos]->Lista_sucursales) {
        printf("\n\t\20No hay sucursales creadas\n\n");
        system("pause");
        system("cls");
        return;
    } else {
        // CASO I : El Buscado es el 1er NODO (Ind. de si es el único).
        if(((*Empresa_Proyecto)->Region[pos]->Lista_sucursales)->ID == id_aux) {
            if(((*Empresa_Proyecto)->Region[pos]->Lista_sucursales)->sig) {
                (*Empresa_Proyecto)->Region[pos]->Lista_sucursales=((*Empresa_Proyecto)->Region[pos]->Lista_sucursales)->sig;
                ((*Empresa_Proyecto)->Region[pos]->Lista_sucursales)->ant=NULL;
            } else {
                (*Empresa_Proyecto)->Region[pos]->Lista_sucursales=NULL;
                free(rec);
                system("PAUSE");
                return;
            }
        }
        // CASO II : Es desde el 2ndo hasta el final.
        while(rec) {
            if(rec->ID==id_aux) {
                if(rec->ant)
                    rec->ant->sig=rec->sig;
                if(rec->sig)
                    rec->sig->ant=rec->ant;
                free(rec);
            }
            rec=rec->sig;
        }
    }
    system("pause");
}

void mostrar_Sucursales(struct Empresa *Empresa_Proyecto , int pos) {
    struct Sucursales *rec=(Empresa_Proyecto)->Region[pos]->Lista_sucursales;
    int i=1;

    system("cls");
    if((Empresa_Proyecto)->Region[pos]->Lista_sucursales==NULL) {
        printf("\n\n\t\t\20No se han creado sucursales en esta regi%cn\n",162);
    } else {

        while(rec) {

            Mostrar_datos_suc(rec,i);
            rec=rec->sig;
            i++;
        }
    }
}

void Mostrar_datos_suc(struct Sucursales * rec ,int i){

    printf("\n=======================    //   =========================\n");
    printf("\20 SUCURSAL N:%d\n", i);
    printf("\t\t\21 NOMBRE              : %s \n", rec->nombre_suc);
    printf("\t\t\21 ID                  : %d \n", rec->ID);
    printf("\t\t\21 DIRECCI%cN           : %s \n",224, rec->direccion_suc);
    printf("\t\t\21 COMUNA              : %s \n", rec->comuna_suc);
    printf("\t\t\21 CIUDAD              : %s \n", rec->ciudad_suc);
    printf("\t\t\21 FONO                : %s \n\n", rec->fono_suc);
    printf("\t\t\21 JEFATURA A CARGO DE : %s \n", rec->name_boss);
    printf("\t\t\21 RUT                 : %s \n", rec->rut_boss);
    printf("\t\t\21 ID PERSONAL         : %d \n\n", rec->id_boss );
}


void Modificar_Sucursal(struct Empresa **Empresa_Proyecto,int pos) {

    struct Sucursales *rec=(*Empresa_Proyecto)->Region[pos]->Lista_sucursales;
    int op,id,i=1;
    char buffer[50];
    printf("\n\t\20INGRESE NOMBRE DE LA SUCURSAL A BUSCAR\n");
    scanf("%s",buffer);
    /*  Validacion lista sucursales*/
    if( !rec){
        printf("\n\t\20No hay sucursales creadas\n");
        return;
    }
    /*  busca el nombre dentro de la lista y para */
    while(rec ){
        if(strcmp(buffer,rec->nombre_suc)== 0){
            break;
        }
        i++;
        rec=rec->sig;
    };
    /*  no pertenece el nombre */
    if(rec == NULL ){
        printf("\n\t\20No se encontro ese nombre\n  ");
        return;
    }
    do {
        system("cls");
        Mostrar_datos_suc(rec,i); /* muestra la sucursal a editar */
        printf("\n\n\t\20Modificar datos de la sucursal  \n\t escoja una opci%cn \n\n", 162);
        printf("\t1) NOMBRE \n");
        printf("\t2) DIRECCION \n");
        printf("\t3) COMUNA  \n");
        printf("\t4) FONO \n");
        printf("\t5) ID  \n");
        printf("\n\t6) SALIR \n");

        scanf("%d",&op);
        switch(op) {
            system("cls");
        case(1):
                    printf("\n\t\20INGRESE EL NUEVO NOMBRE DE LA SUCURSAL\n");
                    scanf("%s",buffer);
                    strcpy(rec->nombre_suc,buffer);
                    printf("\n\t\20EL NOMBRE SE HA MODIFICADO CORRECTAMENTE\n");
                    system("pause");
                    system("cls");
            break;
        case(2):
                    printf("\n\t\20INGRESE LA NUEVA DIRECCI%cN DE LA SUCURSAL\n", 224);
                    scanf("%s",buffer);
                    strcpy(rec->direccion_suc,buffer);
                    printf("\n\t\20LA DIRECCI%cN SE HA MODIFICADO CORRECTAMENTE\n", 224);
                    system("pause");
                    system("cls");
            break;

        case(3):
                    printf("\n\t\20INGRESE LA NUEVA COMUNA DE LA SUCURSAL\n");
                    scanf("%s",buffer);
                    strcpy(rec->comuna_suc,buffer);
                    printf("\n\t\20LA COMUNA SE HA MODIFICADO CORRECTAMENTE\n");
                    system("pause");
                    system("cls");
            break;

        case(4):
                    printf("\n\t\20INGRESE EL NUEVO FONO DE LA SUCURSAL\n");
                    scanf("%s",buffer);
                    strcpy(rec->fono_suc,buffer);
                    printf("\n\t\20EL FONO SE HA MODIFICADO CORRECTAMENTE\n");
                    system("pause");
                    system("cls");
            break;

        case(5):
                    printf("\n\t\20INGRESE EL NUEVO ID DE LA SUCURSAL\n");
                    scanf("%d",&id);
                    rec->ID=id;
                    printf("\n\t\20 EL ID SE HA MODIFICADO CORRECTAMENTE\n");
                    system("pause");
                    system("cls");
            break;
        }
    } while(op!=6);
}

void Guardar_Datos(struct Empresa *Empresa_Proyecto ) {

    FILE *TXT;
    TXT=fopen("Datos_Empresa.txt", "w");

    if(TXT==NULL) {
        printf("\n\t\20NO HAY DATOS CREADOS\n");
        system("pause");
        return;
    }
    if(TXT) {
        //escribir en archivo
        if(Empresa_Proyecto) {  //mientras exista la empresa
            fprintf(TXT,"EMPRESA  [ %s ]\nRUT      [ %s ]\nCLAVE    [ %d ]",Empresa_Proyecto->nombre , Empresa_Proyecto->rut, Empresa_Proyecto->clave);
        }
    }
    fclose(TXT);
}

void Guardar_Datos_Regiones(struct Empresa *Empresa_Proyecto ) {
    int i;
    FILE *TXT;
    TXT=fopen("Datos_Regiones.txt", "w");

    if(TXT==NULL) {
        printf("\n\t\20NO HAY DATOS CREADOS\n");
        system("pause");
        return;
    }
    if(TXT) {
        //escribir en archivo
        if(Empresa_Proyecto) {  //mientras exista la empresa

            for(i=0; i<Empresa_Proyecto->ultimo; i++) {
                fprintf(TXT,"REGION  [%s]\nID      [%d]\n\n========================//==========================\n",Empresa_Proyecto->Region[i]->nombre, Empresa_Proyecto->Region[i]->ID);
            }
        }
    }
    fclose(TXT);
}

void Guardar_Datos_Sucursales(struct Empresa *Empresa_Proyecto ) {
    int i;
    struct Sucursales *aux=NULL;
    FILE *TXT;
    TXT=fopen("Datos_Sucursales.txt", "w");

    if(TXT==NULL) {
        printf("\n\t\20NO HAY DATOS CREADOS\n");
        system("pause");
        return;
    }
    if(TXT) {
        //escribir en archivo
        if(Empresa_Proyecto) {  //mientras exista la empresa
            for(i=0; i<15; i++) {
                fprintf(TXT,"-[[%d]]\n",i+1);
                if(Empresa_Proyecto->Region[i]->Lista_sucursales) { // si hay sucursales creadas
                    aux=Empresa_Proyecto->Region[i]->Lista_sucursales;
                    while(aux) {
                        fprintf(TXT,"%s %s %s %s %s %d %s %s %d\n",aux->nombre_suc,aux->fono_suc,aux->direccion_suc,aux->ciudad_suc,aux->comuna_suc,aux->ID,aux->name_boss,aux->rut_boss,aux->id_boss);

                        /* SUCURSAL  [%s]\n\tTELEFONO  [%s]\n\tDIRECCION  [%s]\n\tCIUDAD  [%s]\n\tCOMUNA  [%s]\n\tID [%d]\n\tJEFATURA  [%s]\n\tRUT DEL JEFE  [%s]\n\tID PERSONAL */

                        aux=aux->sig;
                    }
                }
            }
            fprintf(TXT,"\n**************************************\nREGION [%d]\n",i+1);
        }
    }
    fclose(TXT);
}

int validar_rut(char *pn) { //Verifica si lo ingresado es un rut mayor a 5millones sin puntos mas guion y digito verificador
    int aux=1,cont=0;
    char *aux2;

    aux2=pn;
    while(*pn!='-') {
        if(*pn=='0'&&cont==0)cont--;//Si encuentra cero y aun no a encontrado numeros distintos a 0
        if((*pn>'9')||(*pn<'0')) { //si encuentra un caracter ke no sea numerico
            aux=0;
            break;
        }
        cont++;
        pn++;
    }

    if(aux==0) { //si se encontro un caracter no numerico
        printf("\n\t\20RUT INCORRECTO");
        return aux;
    } else {
        if(cont<7)//si la cantidad de numeros es menor a 7(seria un numero de miles, no de millon) o no
            aux=0;
        else {
            if(*(pn+1)=='\0')//si el caracter que viene despues del guion es fin de string (\0) o no
                aux=0;
            else {
                if(*(pn+2)!='\0')aux=0;//si hay mas de 1 digito verificador
                if(cont==7) {
                    pn=aux2;
                    if(*pn<'5')aux=0;
                }
            }
        }
        return aux;
    }
}

int POS() {
    int pos;

    do {
        printf("\n\t\20INGRESE EL ID DE LA REGI%cN  \n\n", 224);
        scanf("%d",&pos);
        if(  (pos >15)||(pos<0)  ) {
            system("cls");
            printf("\n\t\20Esa regi%cn no existe \n\n\n\n\n\n\n",162);
            system("pause");
            system("cls");
        }
    } while( pos >15 || pos<0);

    return(pos);
}

int Pos() {
    int pos;

    do {
        printf("\n\t\20INGRESE EL ID DE LA REGI%cN (para agregar sucursal)\n\n", 224);
        scanf("%d",&pos);
        if(  (pos >15)||(pos<0)  ) {
            system("cls");
            printf("\n\t\20Esa regi%cn no existe \n\n\n\n\n\n\n",162);
            system("pause");
            system("cls");
        }
    } while( pos >15 || pos<0);

    return(pos);
}

struct Departamento *Crear_Departamento() {

    struct Departamento  *nuevo=NULL;
    char buffer[30];

    nuevo=((struct Departamento *)malloc(sizeof(struct Departamento )));

    fflush(stdin);
    printf("\n\t\20Ingrese el nombre del departamento : ");
    scanf("%[^\n]", buffer);
    nuevo->nombre=(char*)malloc(sizeof(char)*strlen(buffer)+1);
    strcpy(nuevo->nombre, buffer);

    fflush(stdin);
    printf("\n\t\20Ingrese su tel%cfono  : ", 130);
    scanf("%[^\n]", buffer);
    nuevo->telefono=(char*)malloc(sizeof(char)*strlen(buffer)+1);
    strcpy(nuevo->telefono , buffer);

    nuevo->valoracion=10;

    /*  comente estas lineas */
    nuevo->sig=NULL;
    return(nuevo);

}

struct Sucursales *Buscar_sucursal( struct Sucursales *Lista_sucursales, int id ) {

    struct Sucursales *rec=Lista_sucursales;
    if( rec==NULL) {
        printf("\n\t\20LA LISTA DE SUCURSALES ESTA VACIA");
        return;
    }
    while( rec ){
        if(rec->ID==id){
            printf("\n\t\20SUCURSAL ENCONTRADA CON %cXITO",144);
            return(rec);
        }
        rec=rec->sig;
    }
    printf("\n\t\20NO SE ENCONTRO LA SUCURSAL");
    return NULL;
}

void Guardar_Datos_Departamento(struct Empresa *Empresa_Proyecto ) {
    int i;
    struct Sucursales *aux=NULL;
    struct Departamento *rec=NULL;
    FILE *TXT;
    TXT=fopen("Datos_Departamento.txt", "w");

    if(TXT==NULL) {
        printf("\n\t\20NO HAY DATOS CREADOS \n");
        system("pause");
        return;
    }
    if(TXT) {
        //escribir en archivo
        if(Empresa_Proyecto) {  //mientras exista la empresa
            for(i=0; i<15; i++) {
                if(Empresa_Proyecto->Region[i]->Lista_sucursales) { // si hay sucursales creadas
                    aux=Empresa_Proyecto->Region[i]->Lista_sucursales;
                    while(aux) {
                        rec=aux->Lista_dpto;
                        while( rec ) {
                            fprintf(TXT,"%s\t%s\t%d\n",rec->nombre,rec->telefono,rec->valoracion);

                            rec=rec->sig;
                        }
                        aux=aux->sig;
                    }
                }
            }
        }
    }
    fclose(TXT);
}


int Generar_ID_CONSULTA() {
    /* Funcion encargada de crear una clave o id de coonsulta unica para cada usuario
    es necesaria para ingresar al sistema y sus servicios  */

    srand((unsigned)time(NULL));

    /* La función rand() genera un número aleatorio entre
    0 y RAND_MAX-1. Donde RAND_MAX es una constante entera cuyo valor es de 32767
    -> rand()%N, genera un  valor entre 0 y N-1.*/
    int id;
    int A = 10000;
    int B = 32767;

    id = A + rand() % ( (B-A)+1 );
    printf("\n\n\t\20 Su ID de consultas es  [ %d ] No lo olvide \n\n\tEste codigo es personal cuidelo",id);
    //system("pause");
    return id;
}

int  Validar_usuario( struct Empresa *Empresa_Proyecto ) {
    /*  se retorna 0 si el cliente pertenece a la empresa ,1 en otro caso */

    struct Cliente   *rec=Empresa_Proyecto->Arbol_clientes;
    char buffer[50];
    int clave,rut_val=0;

    do {
        fflush(stdin);
        printf("\n\t\20Ingresar como cliente de %s ",Empresa_Proyecto->nombre );
        printf("\n\t\20 Digite su rut: ");
        scanf("%[^\n]", buffer);
        rut_val = validar_rut(buffer);

    } while(rut_val!=1);

    printf("\n\t\20Digite id de atencion \n");
    scanf(" %d",&clave);

    if (rec==NULL ) {
        system("cls");
        printf("\n\t\20NO HAY CLIENTES,\n LO INVITAMOS  REGISTRESE EN %s \n\n\n\n",Empresa_Proyecto->nombre);
        system("pause");
        return 1;
    }
    while (rec) {
        if(  strcmp(  rec->rut , buffer  ) == 0 ) {

            if(rec->ID_consulta == clave) {

                return 0;
            } else {
                system("cls");
                printf("\n\t\20 Su id de atenci%cn no coincide\n\n\n\n", 162 );
                system("pause");
                return 1;
            }
        } else {
            system("cls");
            printf("\n\t\20Su rut no esta en nuestra base de datos \n\n\n\n" );
            system("pause");
            return 1;
        }
    }

}

void Eliminar_departamento(struct Departamento **head) {

     struct Departamento *rec=*head,*aux=*head;
     char buffer[20];

     printf("\n\t\20INGRESE EL NOMBRE DEL DEPARTAMENTO A ELIMINAR\n");
     scanf("%s",buffer);
     if(*head==NULL)
        return;
    if(strcmp(rec->nombre,buffer)==0)
    {
        *head=rec->sig;
        free(rec);
    }
    else
    {
        while(rec && rec->nombre!=buffer)
        {
            rec=rec->sig;
        }
        while(aux->sig!=rec)
        {
            aux=aux->sig;
        }
        aux->sig=rec->sig;
        free(rec);
    }
}

/*  pedir id de la suc en funcion adminis */
void Enlazar_Departamentos( struct Departamento **head,struct Departamento *nuevo) {

    struct Departamento *rec=*head;

    /*  buscar en lista sucursales para encontrar donde agregar el departamento */

    if ( !(*head)) {
        /*  primer caso no hay dptos  */
        *head = nuevo;

    } else {

        /* rec= lista de dptos para seguir agregando  */

        while(rec) {
            if(rec->sig==NULL) {
                rec->sig=nuevo;
                rec=nuevo;
            }
            rec=rec->sig;
        }
    }
    printf("\n\t\20Departamento  creado con %cxito \n\n\n\n",130);
    system("pause");
}

void Modificar_Departamento(struct Empresa **Empresa_Proyecto,int pos) {

    struct Sucursales *rec=(*Empresa_Proyecto)->Region[pos]->Lista_sucursales,*aux=NULL;
    struct Departamento *aux2=NULL;
    int op,id1,i=1;
    char buffer[50];
    printf("\n\t\20INGRESE EL NOMBRE DEL JEFE PARA RECORRER SUS DEPARTAMENTOS\n\t");
    scanf("%s",buffer);

    aux=Buscar_sucursal_dep(rec,buffer);
    aux2=aux->Lista_dpto;
    printf("\n\t\20INGRESE NOMBRE DEL DEPARTAMENTO A BUSCAR\n");
    scanf("%s",buffer);
    /*  Validacion lista departamentos*/
    if( !aux2){
        printf("\n\t\20No hay departamentos creados\n");
        return;
    }
    system("PAUSE");
    /*  busca el nombre dentro de la lista y para */
    while(aux2){
        if(strcmp(buffer,aux2->nombre)== 0){
            break;
        }
        aux2=aux2->sig;
        i++;

    };
    /*  no pertenece el nombre */
    if(aux2 == NULL ){
        printf("\n\t\20No se encontro ese nombre\n  ");
        return;
    }
    system("PAUSE");
    do {
        system("cls");
        Mostrar_datos_departamentos(aux2,i); /* muestra el departamento a editar */
        printf("\n\n\t Modificar datos del departamento  \n\t\20Escoja una opci%cn \n\n", 162);
        printf("\t1) NOMBRE \n");
        printf("\t2) TEL%cFONO \n",144);
        printf("\n\t3) SALIR \n");

        scanf("%d",&op);
        switch(op) {
            system("cls");
        case(1):
                    printf("\n\t\20INGRESE EL NUEVO NOMBRE DEL DEPARTAMENTO\n");
                    scanf("%s",buffer);
                    strcpy(aux2->nombre,buffer);
                    printf("\n\t\20EL NOMBRE SE HA MODIFICADO CORRECTAMENTE\n");
                    system("pause");
                    system("cls");
            break;
        case(2):
                    printf("\n\t\20INGRESE EL NUEVO TEL%cFONO DEL DEPARTAMENTO\n", 144);
                    scanf("%s",buffer);
                    strcpy(aux2->telefono,buffer);
                    printf("\n\t\20 EL TEL%cFONO SE HA MODIFICADO CORRECTAMENTE\n",144);
                    system("pause");
                    system("cls");
            break;

        }
    } while(op!=3);
}

void Mostrar_Departamento(struct Empresa *Empresa_Proyecto,int pos ) {

    struct Sucursales *rec=Empresa_Proyecto->Region[pos]->Lista_sucursales,*aux=NULL;
    struct Departamento *rec_dep=NULL;
    int i=1;
    char buffer[20];

    printf("\n\t\20INGRESE EL NOMBRE DEL JEFE PARA MOSTRAR SUS DEPARTAMENTOS\n");
    scanf("%s",buffer);

    aux=Buscar_sucursal_dep(rec,buffer);


    if(aux==NULL){
         printf("\n\t\20No hay sucursales creadas  ");
        return;

    } else {

        if(aux->Lista_dpto== NULL) {
            printf("\n\n\t\t\21 No se han creado departamento en esta regi%cn\n", 162);
            system("PAUSE");
            return;
        }

        rec_dep=aux->Lista_dpto;
        while(rec_dep){
        Mostrar_datos_departamentos(rec_dep ,i);
            rec_dep=rec_dep->sig;
            i++;
        }
    }
    }

void Mostrar_datos_departamentos(struct Departamento *rec_dep ,int i){
    printf("\n=======================    //   =========================\n");
    printf("\20 DEPARTAMENTO  N:%d\n", i);
    printf("\t\t\21 NOMBRE              : %s \n", rec_dep->nombre);
    printf("\t\t\21 TEL%cFONO            : %s \n", 144, rec_dep->telefono);
    printf("\t\t\21 VALORACION            : %d \n", rec_dep->valoracion);

}

struct Sucursales *Buscar_sucursal_dep( struct Sucursales *Lista_sucursales, char *nombrejefe ) {

    struct Sucursales *rec=Lista_sucursales;
    if( rec==NULL) {
        printf("\n\t\20LA LISTA DE SUCURSALES ESTA VACIA\n");
        return NULL;
    }

    while( rec ) {
        if(strcmp(rec->name_boss,nombrejefe)==0) {
            printf("\n\t\20SUCURSAL ENCONTRADA CON %cXITO\n", 144);
            system("cls");
            return(rec);
        }else{
        printf("\n\t\20NO SE ENCONTRO LA SUCURSAL\n");
        return NULL;

        }
        rec=rec->sig;
    }
}

struct Departamento* buscar_depto(struct Departamento *nodo,char *nombredepto){

while( nodo ) {
    if(strcmp(nodo->nombre,nombredepto)==0){
    printf("se encontro el departamento");
    return nodo;
    }else{
    return NULL;
    }
    nodo=nodo->sig;
    }
}

void modificar_region(struct Empresa **Empresa_Proyecto)
{
    int i, id, pos, op, id_new,validar_region;
    struct Empresa *aux_emp=*Empresa_Proyecto;
    char buffer[50];

    printf("\n\t\20Ingrese id de la regi%cn a cambiar\n", 162);
    scanf("%d", &id);

    pos=buscar_region(aux_emp, id);
    if(pos==-1){
        printf("\n\t\20Ingrese una id valida\n");

    }
    for(i=0; i<(*Empresa_Proyecto)->ultimo; i++){
       if(i==pos){
           do{
                system("cls");
                printf("\n\n\t Modificar datos de la regi%cn  \n\t\20Escoja una opci%cn \n\n", 162, 162);
                printf("\t1) NOMBRE \n");
                printf("\t2) ID  \n");
                printf("\n\t3) SALIR \n");

                scanf("%d",&op);
                switch(op) {
                    system("cls");
                        case(1):
                            printf("\n\t\20INGRESE EL NUEVO NOMBRE DE LA REGI%cN\n", 224);
                            scanf("%s",buffer);
                            strcpy((*Empresa_Proyecto)->Region[i]->nombre,buffer);
                            printf("\n\t\20EL NOMBRE SE HA MODIFICADO CORRECTAMENTE:\n\n\t");
                            system("pause");
                            system("cls");
                            break;
                        case(2):
                            printf("\n\t\20INGRESE LA NUEVA ID DE LA REGI%cN\n", 224);
                            scanf("%d",&id_new);
                            validar_region=buscar_region(aux_emp, id_new);
                            if(validar_region==-1){
                            aux_emp->Region[i]->ID=id_new;
                            printf("\n\t\20IP SE HA MODIFICADO CORRECTAMENTE\n\n\t");
                            system("pause");
                            system("cls");
                            }else{
                                printf("\n\t\20ID se encuentra disponible, ocupe una distinta\n\n\t");
                                system("pause");
                            }
                            break;
                }
           }while(op!=3);
       }
    }
}

int buscar_region(struct Empresa *Empresa_Proyecto, int id)
{
    int i;

    for(i=0; i<Empresa_Proyecto->ultimo; i++){
        if(id==Empresa_Proyecto->Region[i]->ID)
        return i;
    }
    return -1;
}

void Eliminar_region(struct Empresa **Empresa_Proyecto, int pos){
    int ultimo, i;

    if((pos<0) || (pos>(*Empresa_Proyecto)->ultimo))
        printf("\n\t\20 Posici%cn no existe", 162);
    else{

        (*Empresa_Proyecto)->ultimo--;

        for(i=pos+1; i<=(*Empresa_Proyecto)->ultimo; i++)
            (*Empresa_Proyecto)->Region[i-1]=(*Empresa_Proyecto)->Region[i];
        printf("\n\t\20ELIMINADO CORRECTAMENTE");
    }
}

void Mostrar_regiones(struct Empresa *Empresa_Proyecto)
{
    int i;
    struct Regiones *aux_reg=NULL;

    printf("\n=========================    //   =========================\n");

    for(i=0; i<Empresa_Proyecto->ultimo; i++){
        aux_reg=Empresa_Proyecto->Region[i];
        printf("\20 \t %d", aux_reg->ID);
        printf("\t\t %s\n", aux_reg->nombre);

    }
}

void Agregar_regiones(struct Empresa **Empresa_Proyecto){
     char buffer[30];
     int i, aux_ult, id_aux;

     aux_ult=(*Empresa_Proyecto)->ultimo;
     printf("%d", aux_ult);
     if(aux_ult < 15){

        (*Empresa_Proyecto)->ultimo++;

        fflush(stdin);
        printf("\n\t\20Ingrese Nombre para agregar regi%cn\n", 162);
        scanf("%s",buffer);
        (*Empresa_Proyecto)->Region[(*Empresa_Proyecto)->ultimo]->nombre=(char*)malloc(sizeof(char)*strlen(buffer)+1);
        strcpy((*Empresa_Proyecto)->Region[(*Empresa_Proyecto)->ultimo]->nombre, buffer);

        printf("\n\t\20Ingrese ID de la regi%cn", 162);
        scanf("%d", &id_aux);
        (*Empresa_Proyecto)->Region[(*Empresa_Proyecto)->ultimo]->ID=id_aux;
        return;

     }else{
          printf("\n\t\20No se pueden agregar regiones\n");
        return;
     }
}

struct Empresa *Cargar_Empresa(){ //////////////////////////////////////////////

struct Empresa *nueva=NULL;
int clave,i;
char nombre[50],rut[50];

FILE  *TXT;
TXT=fopen("Datos_Empresa.txt", "r");

    if(TXT==NULL) {
        return;
    }

 while (!feof(TXT)){

        fscanf(TXT,"EMPRESA  [ %s ]\nRUT      [ %s ]\nCLAVE    [ %d ]",nombre,rut,&clave);

        /*  se pide memoria al nodo  empresa  */

        nueva=(struct Empresa*)malloc(sizeof ( struct Empresa));

        /*  agrega los datos a empresa */
        nueva->nombre =(char*)malloc(sizeof(char)*strlen(nombre)+1);
        strcpy(nueva->nombre, nombre );

        nueva->rut=(char*)malloc(sizeof(char)*strlen(rut)+1);
        strcpy(nueva->rut,rut);

        nueva->clave=clave;

        for(i=0; i<15 ; i++) {   // seteando vector de punteros
            nueva->Region[i]=NULL;
        }
        nueva->Arbol_clientes=NULL;
        return nueva;
    }
}


void Guardar_Reclamos( struct Cliente **Usuario_rec ){

FILE *TXT;

TXT=fopen("Reclamos.txt","a");
int i=0;
char reclamo[3000],c;
    if(TXT) {

            fprintf(TXT,"\nID_CONSULTA [ %d ]   RUT[ %s ] \n",(*Usuario_rec)->ID_consulta,(*Usuario_rec)->rut);
            printf("\n\t\20Exponga su situaci%cn 3000 caracteres disponibles\n\t\20 ",162);
            fflush(stdin);  /* NO BORRAR!! O SE SALTA LA LECTURA DE LOS DATOS..... */
            /* LINEA DE MIERDA ...POR ESTO NO PUDIMOS ENTREGARLO A LA HORA :((( */

//            /* utiliza getchar para leer cada caracter */
//            while ( ( c = getchar() ) != '\n') {
//                reclamo[ i++ ] = c;
//            } /* fin de while */
//
//            reclamo[ i ] = '\0'; /* termina la cadena */
//
            fgets(reclamo,3000,stdin);
            fputs(reclamo,TXT);

            /*  estado de reclamos aumenta  */
            (*Usuario_rec)->estado_reclamos++;

            system("cls");
            printf("\n\t\20 Se agrego el reclamo a su registro ! \n\n");
            system("pause");
            return;

    }else{

        printf("\n\t\20 Error del sistema no se pudo crear el reclamo \n");
        system("pause");
        return;

    }
    fclose(TXT);
}


void Guardar_Consultas( struct Cliente **Usuario_rec ){

FILE *TXT;

TXT=fopen("Consultas.txt","a");
int i=0;
char reclamo[3000],c;
    if(TXT) {

            fprintf(TXT,"\nID_CONSULTA [ %d ]   RUT[ %s ] \n",(*Usuario_rec)->ID_consulta,(*Usuario_rec)->rut);
            printf("\n\t\20Exponga su consulta 3000 caracteres disponibles\n\t\20 ");
            fflush(stdin);
            fgets(reclamo,3000,stdin);
            fputs(reclamo,TXT);


            system("cls");
            printf("\n\t\20 Se agreago la consulta su registro ! \n\n");
            system("pause");
            return;

    }else{
        printf("\n\t\20 Error del sistema no se pudo crear la consulta \n");
        system("pause");
        return;
    }
    fclose(TXT);
}
void agregar_clientes(struct Cliente **raiz){

    struct Cliente *nodoarbol=(struct Cliente*)malloc(sizeof(struct Cliente));
    struct Cliente *tmp=NULL;
    int rut_val=0;
    char buffer[30];
    tmp=*raiz;
    fflush(stdin);
    if(!(*raiz)){
    system("cls");
    fflush(stdin);
    printf("\n\n\t Solisitud de nuevo cliente \n\n\t\20Ingrese su nombre: ");
    scanf(" %[^\n]",buffer);

    nodoarbol->nombre =(char*)malloc(sizeof(char)*strlen(buffer)+1);
    strcpy(nodoarbol->nombre, buffer);

    fflush(stdin);
    printf("\n\t\20Ingrese su edad: ");
    scanf("%d", &nodoarbol->edad);

    fflush(stdin);
    printf("\n\t\20 Ingrese su ciudad: ");
    scanf("%[^\n]", buffer);
    nodoarbol->ciudad=(char*)malloc(sizeof(char)*strlen(buffer)+1);
    strcpy(nodoarbol->ciudad, buffer);

    fflush(stdin);

    printf("\n\t\20 Ingrese su direcci%cn: ", 162);
    scanf("%[^\n]", buffer);
    nodoarbol->direccion=(char*)malloc(sizeof(char)*strlen(buffer)+1);
    strcpy(nodoarbol->direccion, buffer);

    fflush(stdin);
    printf("\n\t\20 Ingrese el tel%cfono: ", 130);
    scanf("%[^\n]", buffer);
    nodoarbol->telefono=(char*)malloc(sizeof(char)*strlen(buffer)+1);
    strcpy(nodoarbol->telefono, buffer);

    nodoarbol->ID_consulta= Generar_ID_CONSULTA();

    do {

        fflush(stdin);
        printf("\n\t\20 Ingrese su rut: ");
        scanf("%[^\n]", buffer);
        rut_val =validar_rut(buffer);

    } while(rut_val!=1);


    nodoarbol->rut=(char*)malloc(sizeof(char)*strlen(buffer)+1);
    strcpy(nodoarbol->rut,buffer);

    fflush(stdin);
    printf("\n\t\20 Ingrese su email: ");
    scanf("%[^\n]", buffer);
    nodoarbol->email=(char*)malloc(sizeof(char)*strlen(buffer)+1);
    strcpy(nodoarbol->email, buffer);

    nodoarbol->estado_reclamos=0;

    nodoarbol->der=NULL;
    nodoarbol->izq=NULL;
    *raiz=nodoarbol;
}else{

    system("cls");
    fflush(stdin);
    printf("\n\n\t Solisitud de nuevo cliente \n\n\t\20Ingrese su nombre: ");
    scanf(" %[^\n]",buffer);

    nodoarbol->nombre =(char*)malloc(sizeof(char)*strlen(buffer)+1);
    strcpy(nodoarbol->nombre, buffer);

    fflush(stdin);
    printf("\n\t\20Ingrese su edad: ");
    scanf("%d", &nodoarbol->edad);

    fflush(stdin);
    printf("\n\t\20 Ingrese su ciudad: ");
    scanf("%[^\n]", buffer);
    nodoarbol->ciudad=(char*)malloc(sizeof(char)*strlen(buffer)+1);
    strcpy(nodoarbol->ciudad, buffer);

    fflush(stdin);

    printf("\n\t\20 Ingrese su direcci%cn: ", 162);
    scanf("%[^\n]", buffer);
    nodoarbol->direccion=(char*)malloc(sizeof(char)*strlen(buffer)+1);
    strcpy(nodoarbol->direccion, buffer);

    fflush(stdin);
    printf("\n\t\20 Ingrese el tel%cfono: ", 130);
    scanf("%[^\n]", buffer);
    nodoarbol->telefono=(char*)malloc(sizeof(char)*strlen(buffer)+1);
    strcpy(nodoarbol->telefono, buffer);

    nodoarbol->ID_consulta= Generar_ID_CONSULTA();

    do {

        fflush(stdin);
        printf("\n\t\20 Ingrese su rut: ");
        scanf("%[^\n]", buffer);
        rut_val =validar_rut(buffer);

    } while(rut_val!=1);


    nodoarbol->rut=(char*)malloc(sizeof(char)*strlen(buffer)+1);
    strcpy(nodoarbol->rut,buffer);

    fflush(stdin);
    printf("\n\t\20 Ingrese su email: ");
    scanf("%[^\n]", buffer);
    nodoarbol->email=(char*)malloc(sizeof(char)*strlen(buffer)+1);
    strcpy(nodoarbol->email, buffer);

    nodoarbol->estado_reclamos=0;

    nodoarbol->der=NULL;
    nodoarbol->izq=NULL;
    while(tmp){
         if(nodoarbol->ID_consulta > tmp->ID_consulta){
             if(tmp->der==NULL){
                 tmp->der=nodoarbol;
                 return;
             }else{
                 tmp=tmp->der;
             }
         }
         if(nodoarbol->ID_consulta < tmp->ID_consulta){
             if(tmp->izq==NULL){
                 tmp->izq=nodoarbol;
                 return;
             }else{
                 tmp=tmp->izq;
             }
         }
    }
}
}

void modificar_clientes(struct Cliente* inicio,int id){
    int op,age,ID;
    char buffer[30];
     if(inicio){
     modificar_clientes(inicio->der,id);
     modificar_clientes(inicio->izq,id);
     if (inicio->ID_consulta==id){

        do {
            printf("\n\t\20 Modificar datos del Cliente  \n\t Escoja una opcion \n\n");
            printf("\t1) NOMBRE \n");
            printf("\t2) DIRECCI%cN \n", 224);
            printf("\t3) CIUDAD \n");
            printf("\t4) FONO \n");
            printf("\t5) EMAIL \n");
            printf("\t6) EDAD \n");
            printf("\t7) ID DE CONSULTA   \n");
            printf("\n\t8) SALIR \n");

            scanf("%d",&op);
            switch(op) {
                system("cls");
            case(1):
                        printf("\n\t\20INGRESE EL NUEVO NOMBRE DEL CLIENTE\n\t");
                        scanf("%s",buffer);
                        strcpy(inicio->nombre,buffer);
                        printf("\n\t\20EL NOMBRE SE HA MODIFICADO CORRECTAMENTE\n");

                        system("pause");
                        system("cls");
                break;
            case(2):
                        printf("\n\t\20INGRESE LA NUEVA DIRECCI%cN DEL CLIENTE\n\t", 224);
                        scanf("%s",buffer);
                        strcpy(inicio->direccion,buffer);
                        printf("\n\t\20LA DIRECCION SE HA MODIFICADO CORRECTAMENTE\n");
                        system("pause");
                        system("cls");
                break;

            case(3):
                        printf("\n\t\20INGRESE LA NUEVA CIUDAD DEL CLIENTE\n\t");
                        scanf("%s",buffer);
                        strcpy(inicio->ciudad,buffer);
                        printf("\n\t\20LA  CIUDAD SE HA MODIFICADO CORRECTAMENTE\n");
                        system("pause");
                        system("cls");
                break;
            case(4):
                        printf("\n\t\20INGRESE EL NUEVO FONO DEL CLIENTE\n\t");
                        scanf("%s",buffer);
                        strcpy(inicio->telefono,buffer);
                        printf("\n\t\20EL FONO SE AH MODIFICADO CORRECTAMENTE\n");
                        system("pause");
                        system("cls");
                break;
            case(5):
                        printf("\n\t\20INGRESE EL NUEVO MAIL DEL CLIENTE\n\t");
                        scanf("%s",buffer);
                        strcpy(inicio->email,buffer);
                        printf("\n\t\20EL MAIL SE HA MODIFICADO CORRECTAMENTE\n");
                        system("pause");
                        system("cls");
                break;
            case(6):
                        printf("\n\t\20INGRESE NUEVA EDAD DEL CLIENTE\n\t");
                        scanf("%d",&age);
                        inicio->edad=age;
                        printf("\n\t\20LA EDAD SE HA MODIFICADO CORRECTAMENTE\n");

                        system("pause");
                        system("cls");
                break;
            case(7):
                        printf("\n\t\20INGRESE EL NUEVO ID DEL CLIENTE\n\t");
                        scanf("%d",&ID);
                        inicio->ID_consulta=ID;
                        printf("\n\t\20 EL ID SE HA MODIFICADO CORRECTAMENTE\n");

                        system("pause");
                        system("cls");
                break;
            }
        } while(op!=8);
        }
        }
}


void guardar_clientes(struct Empresa *Empresa_Proyecto){
    struct Cliente *raiz=(Empresa_Proyecto)->Arbol_clientes;
    struct pila *cima=NULL;
    FILE *TXT;

    TXT=fopen("Datos_Clientes.txt","w");
     if(TXT==NULL) {
        system("pause");
        return;
    }
    push(&cima,NULL);

    while(raiz){
        fflush(stdin);
        fprintf(TXT,"%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%d\n",raiz->nombre,raiz->rut,raiz->direccion,raiz->ciudad ,raiz->telefono,raiz->email ,raiz->edad,raiz->ID_consulta,raiz->estado_reclamos);
        if(raiz->der){
            push(&cima,raiz->der);
        }
        if(raiz->izq){
            raiz=raiz->izq;
        }else{
            raiz=pop(&cima);
        }
    }
}

void push(struct pila **cima,struct Cliente *nuevo){
    struct pila *nueva=(struct pila *)malloc(sizeof(struct pila));

    nueva->valor=nuevo;
    nueva->sig=*cima;
    *cima=nueva;
}
struct Cliente * pop(struct pila **cima){
    struct pila *p;
    struct Cliente *v;

    p=*cima;
    if(!*cima){
        return NULL;
    }
    *cima=p->sig;
    v=p->valor;
    free(p);

    return v;
}

void cargar_clientes(struct Cliente **raiz){
    struct Cliente *nueva;
    struct Cliente *tmp=NULL;
    int edad,reclamos,i,ID;
    char nombre[50],rut[50],direccion[50],ciudad[50],telefono[50] ,email[50];
    FILE  *TXT;
    TXT=fopen("Datos_Clientes.txt","r");

    if(TXT==NULL) {
        return;
    }


    if(TXT){
    while(!feof(TXT)){
     nueva=(struct Cliente*)malloc(sizeof(struct Cliente));

     tmp=*raiz;
     fflush(stdin);
     if(!(*raiz)){
         fscanf(TXT,"%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%d\n",nombre,rut,direccion,ciudad,telefono,email,&edad,&ID,&reclamos);


        nueva->nombre =(char*)malloc(sizeof(char)*strlen(nombre)+1);
        strcpy(nueva->nombre, nombre );

        nueva->rut=(char*)malloc(sizeof(char)*strlen(rut)+1);
        strcpy(nueva->rut,rut);

        nueva->direccion=(char*)malloc(sizeof(char)*strlen(direccion)+1);
        strcpy(nueva->direccion, direccion);

        nueva->ciudad=(char*)malloc(sizeof(char)*strlen(ciudad )+1);
        strcpy(nueva->ciudad, ciudad);

        nueva->telefono=(char*)malloc(sizeof(char)*strlen(telefono)+1);
        strcpy(nueva->telefono, telefono );

        nueva->email=(char*)malloc(sizeof(char)*strlen(email)+1);
        strcpy(nueva->email, email);

        nueva->edad=edad;

        nueva->ID_consulta=ID;

        nueva->estado_reclamos=reclamos;

         nueva->der=NULL;
         nueva->izq=NULL;
         *raiz=nueva;
         }else{
         fflush(stdin);
         fscanf(TXT,"%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%d\n",nombre,rut,direccion,ciudad,telefono,email,&edad,&ID,&reclamos);


        nueva->nombre =(char*)malloc(sizeof(char)*strlen(nombre)+1);
        strcpy(nueva->nombre, nombre );

        nueva->rut=(char*)malloc(sizeof(char)*strlen(rut)+1);
        strcpy(nueva->rut,rut);

        nueva->direccion=(char*)malloc(sizeof(char)*strlen(direccion)+1);
        strcpy(nueva->direccion, direccion);

        nueva->ciudad=(char*)malloc(sizeof(char)*strlen(ciudad )+1);
        strcpy(nueva->ciudad, ciudad);

        nueva->telefono=(char*)malloc(sizeof(char)*strlen(telefono)+1);
        strcpy(nueva->telefono, telefono );

        nueva->email=(char*)malloc(sizeof(char)*strlen(email)+1);
        strcpy(nueva->email, email);

        nueva->edad=edad;

        nueva->ID_consulta=ID;

        nueva->estado_reclamos=reclamos;
         nueva->der=NULL;
         nueva->izq=NULL;
        while(tmp){
         if(nueva->ID_consulta > (tmp)->ID_consulta){
             if((tmp)->der==NULL){
                 (tmp)->der=nueva;
                 return;
             }else{
                 (tmp)=(tmp)->der;
             }
         }
         if(nueva->ID_consulta < (tmp)->ID_consulta){
             if((tmp)->izq==NULL){
                 (tmp)->izq=nueva;
                 return;
             }else{
                 (tmp)=(tmp)->izq;
             }
         }
    }
     }
    }
    }
    fclose(TXT);
}

void eliminar_cliente (struct Cliente **inicio,int ID){
     struct Cliente *aux=NULL;

     if((*inicio)->ID_consulta < ID )
            eliminar_cliente(&(*inicio)->der,ID);
     else{
          if((*inicio)->ID_consulta > ID )
            eliminar_cliente(&(*inicio)->izq,ID);
          else{
               if((*inicio)->ID_consulta == ID ){
                  aux=(*inicio);
                  if(!((*inicio)->izq)){
                      (*inicio)=(*inicio)->der;
                  }else{
                       if(!((*inicio)->der)){
                       (*inicio)=(*inicio)->izq;
                       }else{
                       reemplazar(&(*inicio)->izq,&aux);
                       }
                  }
                       free(aux);
               }
          }
     }
}

void reemplazar(struct Cliente **inicio,struct Cliente** aux){
     if(!((*inicio)->der)){
          (*aux)->ID_consulta=(*inicio)->ID_consulta;
          (*aux)=(*inicio);
          (*inicio)=(*inicio)->izq;
     }else{
        reemplazar(&(*inicio)->der,&(*aux));
     }
}

struct Cliente* busqueda_clientes(struct Cliente *arbol, struct Cliente **ant, int ID){
    int enc=0;
    while(!enc && arbol){
        if(arbol->ID_consulta==ID){
            enc=1;
        }else{
            *ant=arbol;
            if(ID<arbol->ID_consulta){
                arbol=arbol->izq;
            }else{
                arbol=arbol->der;
            }
        }
    }
     return arbol;
}

void mostrar_clientes(struct Cliente *inicio){

     if(inicio){

        mostrar_clientes(inicio->der);

        printf("\n=======================    //   =========================\n");
        printf("\20 CLIENTE :\n");
        printf("\t\t\21 NOMBRE      : %s \n", inicio->nombre);
        printf("\t\t\21 RUT         : %s \n", inicio->rut);
        printf("\t\t\21 DIRECCION   : %s \n", inicio->direccion);
        printf("\t\t\21 CIUDAD      : %s \n", inicio->telefono);
        printf("\t\t\21 TELEFONO    : %s \n", inicio->ciudad);
        printf("\t\t\21 EMAIL       : %s \n\n", inicio->email);
        printf("\t\t\21 EDAD        : %d \n", inicio->edad);
        printf("\t\t\21 ID DE CONSULTA  : %d \n\n", inicio->ID_consulta);

        mostrar_clientes(inicio->izq);
     }
}





//----------------FUNCIONES EXTRAS----------------//




void cliente_reclamon(struct Empresa *Empresa_Proyecto){
    struct Cliente *cliente_reclamon;
    struct Cliente *tmp=Empresa_Proyecto->Arbol_clientes;

    postorden_cliente_reclamon(tmp, &cliente_reclamon);

    if(tmp){
        printf("\n\n\t El cliente : %s\n posee la mayor cantidad \n\t con  %d reclamos \n\n\t ",cliente_reclamon->nombre, cliente_reclamon->estado_reclamos);
        system("pause");
    }else{
        return;
    }
}

void postorden_cliente_reclamon(struct Cliente *p, struct Cliente**cliente_reclamon){
struct pila *cima;
int may=-1;


    cima=NULL;
    push(&cima,NULL);

        while(cima){
            while(p){
                push(&cima,p);
                if(p->der){
                    push(&cima, p->der);
                    push(&cima, NULL);
                }
                p=p->izq;
            }
            p=pop(&cima);
            while(p){
                if(p->estado_reclamos > may){
                may=p->estado_reclamos;
                *cliente_reclamon=p;
                }
            p=pop(&cima);
            }
            if(!p){
                p=pop(&cima);
            }
        }
}

struct Departamento* mejorevaluado(struct Empresa *Empresa_Proyecto,int pos){

struct Sucursales *rec=(Empresa_Proyecto)->Region[pos]->Lista_sucursales;
struct Departamento *dep=rec->Lista_dpto,*mejor_evaluada=NULL, *aux=dep ;

    if (dep==NULL){
        return NULL;
    }else{

        while(dep)
        {
            if(aux->valoracion<=dep->valoracion){
                    mejor_evaluada=dep;
            }
             dep=dep->sig;
        }
    }
    return mejor_evaluada;
}


/////////////////////////////////// FIN //////////////////////////////////
