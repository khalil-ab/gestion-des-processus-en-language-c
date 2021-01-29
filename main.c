#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define maxim 500 //le maximum du temps d'arret
#define meth_affich 1 //pour chosir la methode d'affichage de la grill soit 1 ou 2

typedef struct
{
    int elu;
    int pret;
    int ent_sor;
    int blq;
}
comment;

typedef struct processus
{
    char code[30];
    int date_arr;
    int dur_exec_non_modif_proc;
    int dur_exec_modif_proc;
    int dur_non_modif_es;
    int dur_modif_es;
    int priorite;
    int dur_pret;
    int dur_blq;
    int turn;
    int etat;
    comment cmt[maxim];
    struct processus *suiv;//c est une structure recursive qui consiste a declarer un pointeur ayant les meme paramettres nom note et pointeur suiv
}
processus ;

typedef struct
{
    int elu;
    int pret;
    int ent_sor;
    int blq;
}
info;

typedef struct
{
    char cd[30];
}
code_proc;

///////////////////////////////////////////Les fonctions de vérification et comparaison////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int verif_bcp(char nom_fich[])
{
    FILE *p=fopen(nom_fich,"rt");
    int c,cmpt_poin_vrg=0,cmpt_lign=0;
    char ch[100];


    if(p==NULL)
    {
        printf("Impossible d'ouvrir le fichier !!");
        fclose(p);

        getch();

        return 0;
    }
    else
    {
        p=fopen(nom_fich,"rt");

        while(fgets(ch,sizeof(ch),p)!=NULL)
        {
            if(strcmp(ch,"\n")!=0)
                cmpt_lign++;
        }
        fclose(p);
printf("%d",cmpt_lign);
getch();

        p=fopen(nom_fich,"rt");

        while((c=fgetc(p))!=EOF)
        {
            if(c==';')
            {
                cmpt_poin_vrg++;
            }
            else
            {
                if(c==' ')
                {
                    printf("Votre fichier contient des espaces qu'il faut %cviter !!",130);
                    fclose(p);
                    getch();
                    return 0;
                }
            }
        }
        fclose(p);

        if(cmpt_lign==0)
        {
            printf("Votre fichier est vide !!");
            getch();
            return 0;
        }
        else
        {
            if(cmpt_poin_vrg!=(4*cmpt_lign))
            {
                printf("Les points virgules sont mal position%cs dans ce fichier !!",130);
                getch();
                return 0;
            }
            else
                return 1;
        }


    }
}

int verif_nombre(char nb[],int a)
{
    char *p  ;
    int erreur=0;

    p=nb;

    while (*p!=NULL)
    {
        if (isdigit(*p))//si le caractere pointé est un chiffre digital
        {
            p++;
        }
        else
        {
            erreur=1;
            break;
        }
    }

    if(erreur==0)
    {
        if(a==1)
        {
            if(atoi(nb)>maxim||atoi(nb)==0)
            {
                printf("\nDonnez un temps d'arr%ct non nul et qui qui ne d%cpasse pas %d !!",136,130,maxim);
                return 0;
            }
            else
                return atoi(nb);
        }
        else
        {
            if(atoi(nb)==0)
            {
                printf("\nDonnez un quantum non nul !!");
                return 0;
            }
            else
                return atoi(nb);

        }
    }
    else
    {
        printf("Donnez un nombre positif et correct !!");
        return 0;
    }
    return 0;
}

int verif_occur_code(char nom_fich[])
{
    int cpt_ocur,j,i=0;
    code_proc cod[20];
    char *nom_code;
    FILE *p;

    p=fopen(nom_fich,"rt");//read si on veut lire le fichier or write si on veut ecrire dans le fichier

    while(fscanf(p,"%s",cod[i].cd)!=EOF)
    {
        nom_code = strtok (cod[i].cd,";");

        strcpy(cod[i].cd,nom_code);

        i++;
    }
    strcpy(cod[i].cd,"stop");

    fclose(p);

    i=0;

    while(strcmp(cod[i].cd,"stop")!=0)
    {
        j=0;
        cpt_ocur=0;

        while(strcmp(cod[j].cd,"stop")!=0)
        {
            if(strcmp(cod[j].cd,cod[i].cd)==0)
                cpt_ocur++;
            j++;
        }

        if(cpt_ocur==1)
        {
            i++;
        }
        else
        {
            printf("\nErreur !! Il existe %d processus ayant le meme code %s !!",cpt_ocur,cod[i].cd);
            getch();
            return 0;
        }
    }
    return 1;
}

int som_acsii(char *code)
{
    char*p = code;
    int som=0;

    while (*p!='\0')//ça marche pas avec '\n'
    {
        som=som+*p;//la somme de chaque caractere des code en ascii
        p++;
    }
    return som;

}

///////////////////////////////////////////Les fonctions de modification de la liste des processus chargées/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
processus* enreg_bcp(FILE *fich_bcp,code_proc *code)
{
    processus *i= malloc(sizeof(processus));
    int date_arr;
    int dur_exec_non_modif_proc;
    int dur_non_modif_es;
    int priorite;
    char *fileRead;
    char chaine[100];
    char *part;

    fileRead =fgets(chaine,sizeof(chaine),fich_bcp);

    if(fileRead != NULL&&strcmp(chaine,"\n")!=0)
    {
        part = strtok (chaine,";");
        strcpy(code[0].cd,part);

        part = strtok(NULL, ";");
        date_arr=atoi(part);

        part = strtok (NULL, ";");
        dur_exec_non_modif_proc=atoi(part);

        part = strtok (NULL, ";");
        dur_non_modif_es=atoi(part);

        part = strtok (NULL, "\n");
        priorite=atoi(part);

        strcpy(i->code,code[0].cd);
        i->date_arr = date_arr;
        i->dur_exec_non_modif_proc = dur_exec_non_modif_proc;
        i->dur_exec_modif_proc = dur_exec_non_modif_proc;
        i->dur_non_modif_es=dur_non_modif_es;
        i->dur_modif_es=dur_non_modif_es;
        i->priorite=priorite;
        i->etat=0;
        i->dur_pret=0;
        i->dur_blq=0;
        code++;
        i->suiv = enreg_bcp(fich_bcp,code);
    }
    else
    {
        if(fileRead != NULL&&strcmp(chaine,"\n")==0)
        {
            strcpy(i->code,"zzzzzz");
            i->date_arr = 1000;
            i->suiv = enreg_bcp(fich_bcp,code);
        }
    }

    if(fileRead == NULL)
    {
        return NULL;
    }

    return i;
}

void supp_liste(processus *proc)
{
    processus *T;
    int boucle=1;
    do
    {
        T=proc;
        if(T->suiv!=NULL)
        {
            proc=proc->suiv;
            free(T);
        }
        else
        {
            boucle=0;
            free(T);
        }
    }
    while(boucle==1);
}

void supp_not(processus *proc)
{
    int boucle;
    processus *T=proc;

    boucle=1;

    do
    {
        if(T->suiv==NULL)
            break;

        if(strcmp(T->suiv->code,"zzzzzz")==0)
        {
            boucle=0;
            T->suiv=NULL;
        }
        else
            T=T->suiv;
    }
    while(boucle==1);
}

int nbr_proc(processus *proc)
{
    int nbr_pr=1;
    processus *pr=proc;

    if(pr->suiv!=NULL)
    {
        return nbr_pr+nbr_proc(pr->suiv);
    }
    else
    {
        return nbr_pr;
    }
}

void trie_proc(processus *proc)
{
    int permut,temp;
    char k[30];
    processus *T;
    do
    {
        T=proc;
        permut=0;

        while (T->suiv!=NULL)
        {
            if(T->date_arr>T->suiv->date_arr||(T->date_arr==T->suiv->date_arr&&strcmp(T->code,T->suiv->code)>0))
            {
                strcpy(k,T->code);
                strcpy(T->code,T->suiv->code);
                strcpy(T->suiv->code,k);

                temp=T->date_arr;
                T->date_arr=T->suiv->date_arr;
                T->suiv->date_arr=temp;

                temp=T->dur_exec_non_modif_proc;
                T->dur_exec_non_modif_proc=T->suiv->dur_exec_non_modif_proc;
                T->suiv->dur_exec_non_modif_proc=temp;

                temp=T->dur_exec_modif_proc;
                T->dur_exec_modif_proc=T->suiv->dur_exec_modif_proc;
                T->suiv->dur_exec_modif_proc=temp;

                temp=T->priorite;
                T->priorite=T->suiv->priorite;
                T->suiv->priorite=temp;

                temp=T->dur_modif_es;
                T->dur_modif_es=T->suiv->dur_modif_es;
                T->suiv->dur_modif_es=temp;

                temp=T->dur_non_modif_es;
                T->dur_non_modif_es=T->suiv->dur_non_modif_es;
                T->suiv->dur_non_modif_es=temp;

                temp=T->dur_blq;
                T->dur_blq=T->suiv->dur_blq;
                T->suiv->dur_blq=temp;

                temp=T->dur_pret;
                T->dur_pret=T->suiv->dur_pret;
                T->suiv->dur_pret=temp;

                permut=1;
            }
            T=T->suiv;
        }
    }
    while(permut!=0);
}

///////////////////////////////////////////fonction d'affichage de la grille/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void affich_res(info proces[],int N,char *code,int a,int k)
{
    int i;

    if(meth_affich==1)
    {
        putchar(218);
        putchar(196);
        putchar(196);
        putchar(196);
        putchar(196);
        putchar(196);
        putchar(194);
        putchar(196);
        putchar(196);
        putchar(196);
        putchar(196);
        putchar(196);
        putchar(196);
        for(i=k; i<=N; i++)
        {
            putchar(194);
            putchar(196);
        }
        putchar(191);



        printf("\n");
        putchar(179);
        printf("     ");
        putchar(179);
        printf(" %clu  ",144);

        for(i=k; i<=N; i++)
        {
            if(proces[i].elu==-1)
            {
                putchar(179);
                printf(" ");
                if(i==N)putchar(179);
            }
            else
            {
                if(proces[i].elu==0)
                {
                    putchar(179);
                    printf(" ");
                    if(i==N)putchar(179);
                }
                else
                {
                    if(proces[i].elu==1)
                    {
                        putchar(179);
                        printf("X");
                        if(i==N)putchar(179);
                    }
                    else
                    {
                        putchar(179);
                        printf(" ");
                        if(i==N)putchar(179);
                    }
                }
            }
        }

        printf("\n");
        putchar(179);
        printf("     ");
        putchar(195);
        putchar(196);
        putchar(196);
        putchar(196);
        putchar(196);
        putchar(196);
        putchar(196);
        for(i=k; i<=N; i++)
        {
            putchar(197);
            putchar(196);
        }
        putchar(180);
        printf("\n");
        putchar(179);


        if(a==1)
        {

            if(strlen(code)==1)
            {
                printf("  ");
            }
            else
            {
                if(strlen(code)==2||strlen(code)==3)
                    printf(" ");
            }

            printf("%s",code);

            if(strlen(code)==1||strlen(code)==2)
            {
                printf("  ");
            }
            else
            {
                if(strlen(code)==3||strlen(code)==4)
                    printf(" ");
            }
        }
        else
            printf("     ");

        putchar(179);
        printf(" Pr%ct ",136);

        for(i=k; i<=N; i++)
        {
            if(proces[i].pret==-1)
            {
                putchar(179);
                printf(" ");
                if(i==N)putchar(179);

            }
            else
            {
                if(proces[i].pret==0)
                {
                    putchar(179);
                    printf(" ");
                    if(i==N)putchar(179);

                }
                else
                {
                    if(proces[i].pret==1)
                    {
                        putchar(179);
                        printf("X");
                        if(i==N)putchar(179);

                    }
                    else
                    {
                        putchar(179);
                        printf(" ");
                        if(i==N)putchar(179);

                    }
                }

            }
        }

        printf("\n");


        putchar(179);


        if(a==2)
        {

            if(strlen(code)==1)
            {
                printf("  ");
            }
            else
            {
                if(strlen(code)==2||strlen(code)==3)
                    printf(" ");
            }

            printf("%s",code);

            if(strlen(code)==1||strlen(code)==2)
            {
                printf("  ");
            }
            else
            {
                if(strlen(code)==3||strlen(code)==4)
                    printf(" ");
            }
        }
        else
            printf("     ");

        putchar(195);
        putchar(196);
        putchar(196);
        putchar(196);
        putchar(196);
        putchar(196);
        putchar(196);
        for(i=k; i<=N; i++)
        {
            putchar(197);
            putchar(196);
        }
        putchar(180);
        printf("\n");
        putchar(179);
        printf("     ");
        putchar(179);
        printf(" E/S  ");

        for(i=k; i<=N; i++)
        {
            if(proces[i].ent_sor==-1)
            {
                putchar(179);
                printf(" ");
                if(i==N)putchar(179);

            }
            else
            {
                if(proces[i].ent_sor==0)
                {
                    putchar(179);
                    printf(" ");
                    if(i==N)putchar(179);

                }
                else
                {
                    if(proces[i].ent_sor==1)
                    {
                        putchar(179);
                        printf("X");
                        if(i==N)putchar(179);

                    }
                    else
                    {
                        putchar(179);
                        printf(" ");
                        if(i==N)putchar(179);

                    }
                }
            }
        }


        if(a==2)
        {
            printf("\n");
            putchar(179);
            printf("     ");
            putchar(195);
            putchar(196);
            putchar(196);
            putchar(196);
            putchar(196);
            putchar(196);
            putchar(196);
            for(i=k; i<=N; i++)
            {
                putchar(197);
                putchar(196);
            }
            putchar(180);
            printf("\n");
            putchar(179);
            printf("     ");
            putchar(179);
            printf("Bloqu%c",130);

            for(i=k; i<=N; i++)
            {
                if(proces[i].blq==-1)
                {
                    putchar(179);
                    printf(" ");
                    if(i==N)putchar(179);

                }
                else
                {
                    if(proces[i].blq==0)
                    {
                        putchar(179);
                        printf(" ");
                        if(i==N)putchar(179);

                    }
                    else
                    {
                        if(proces[i].blq==1)
                        {
                            putchar(179);
                            printf("X");
                            if(i==N)putchar(179);

                        }
                        else
                        {
                            putchar(179);
                            printf(" ");
                            if(i==N)putchar(179);

                        }
                    }
                }
            }

        }

        printf("\n");
        putchar(192);
        putchar(196);
        putchar(196);
        putchar(196);
        putchar(196);
        putchar(196);
        putchar(193);
        putchar(196);
        putchar(196);
        putchar(196);
        putchar(196);
        putchar(196);
        putchar(196);
        for(i=k; i<=N; i++)
        {
            putchar(193);
            putchar(196);
        }
        putchar(217);

        printf("\n\t      ");
        for(i=k; i<=N; i++)
        {
            if(i<10)
            {
                printf("%d ",i);
            }
            else
            {
                if(i>=10&&i<=99)
                {
                    printf("%d ",i/10);
                }
                else
                {
                    if(i>=100&&i<=maxim)
                    {
                        printf("%d ",i/100);
                    }
                    else
                    {
                        printf(" ");
                    }
                }
            }
        }

        printf("\n\t      ");
        for(i=k; i<=N; i++)
        {
            if(i<10)
            {
                printf("  ");
            }
            else
            {
                if(i>=10&&i<=99)
                {
                    printf("%d ",i%10);
                }
                else
                {
                    if(i>=100&&i<=maxim)
                    {
                        printf("%d ",(i%100)/10);
                    }
                    else
                    {
                        printf(" ");
                    }
                }
            }
        }

        printf("\n\t      ");
        for(i=k; i<=N; i++)
        {
            if(i<10)
            {
                printf("  ");
            }
            else
            {
                if(i>=10&&i<=99)
                {
                    printf("  ");
                }
                else
                {
                    if(i>=100&&i<=maxim)
                    {
                        printf("%d ",(i%100)%10);
                    }
                    else
                    {
                        printf(" ");
                    }
                }
            }
        }

        printf("\n");
    }
    else
    {
        printf("\n\t%clu\t: ",144);
        for(i=k; i<=N; i++)
        {
            if(proces[i].elu==-1)
                printf(" ");
            else
            {
                if(proces[i].elu==0)
                    printf("-");
                else
                {
                    if(proces[i].elu==1)
                        printf("X");
                    else
                        printf(" ");
                }
            }
        }

        printf("\n%s\tPr%ct\t: ",code,136);
        for(i=k; i<=N; i++)
        {
            if(proces[i].pret==-1)
                printf(" ");
            else
            {
                if(proces[i].pret==0)
                    printf("-");
                else
                {
                    if(proces[i].pret==1)
                        printf("X");
                    else
                        printf(" ");
                }

            }
        }

        printf("\n\tE/S\t: ");
        for(i=k; i<=N; i++)
        {
            if(proces[i].ent_sor==-1)
                printf(" ");
            else
            {
                if(proces[i].ent_sor==0)
                    printf("-");
                else
                {
                    if(proces[i].ent_sor==1)
                        printf("X");
                    else
                        printf(" ");
                }
            }
        }

        if(a==2)
        {
            printf("\n\tBloqu%c\t: ",130);
            for(i=k; i<=N; i++)
            {
                if(proces[i].blq==-1)
                    printf(" ");
                else
                {
                    if(proces[i].blq==0)
                        printf("-");
                    else
                    {
                        if(proces[i].blq==1)
                            printf("X");
                        else
                            printf(" ");
                    }
                }
            }
        }

        printf("\n\n\t          ");
        for(i=k; i<=N; i++)
        {
            if(i<10)
            {
                printf("%d",i);
            }
            else
            {
                if(i>=10&&i<=99)
                {
                    printf("%d",i/10);
                }
                else
                {
                    if(i>=100&&i<=maxim)
                    {
                        printf("%d",i/100);
                    }
                    else
                    {
                        printf(" ");
                    }
                }
            }
        }

        printf("\n\t          ");
        for(i=k; i<=N; i++)
        {
            if(i<10)
            {
                printf(" ");
            }
            else
            {
                if(i>=10&&i<=99)
                {
                    printf("%d",i%10);
                }
                else
                {
                    if(i>=100&&i<=maxim)
                    {
                        printf("%d",(i%100)/10);
                    }
                    else
                    {
                        printf(" ");
                    }
                }
            }
        }

        printf("\n\t          ");
        for(i=k; i<=N; i++)
        {
            if(i<10)
            {
                printf(" ");
            }
            else
            {
                if(i>=10&&i<=99)
                {
                    printf(" ");
                }
                else
                {
                    if(i>=100&&i<=maxim)
                    {
                        printf("%d",(i%100)%10);
                    }
                    else
                    {
                        printf(" ");
                    }
                }
            }
        }

    }
}

/////////////////////////////////////////////////////////////TOURNIQUET PREMIER CAS////////////////////////////////////////////////////////////////////////
void tourniquet_pro(processus *proc,int N,char *code,int qt,info proces[])
{
    processus *T;
    processus *q;
    int boucle,cpt,maj;
    int duratt_cpu,place,pos,i,existe_cpu,util_cpu=0,pause=0;
    char cd_proc[10];
    int execution_proc=proc->date_arr;

    strcpy(cd_proc,"nothing");

    for(i=0; i<N; i++)
    {
        proces[i].elu=-2;
        proces[i].ent_sor=-2;
        proces[i].pret=-2;
    }

    boucle=1;
    T=proc;

    do
    {
        for(i=0; i<N; i++)
        {
            T->cmt[i].elu=0;
            T->cmt[i].pret=0;
            T->cmt[i].ent_sor=0;
            T->cmt[i].blq=0;
        }
        if(T->suiv!=NULL)
            T=T->suiv;
        else
            boucle=0;
    }
    while(boucle==1);

    i=proc->date_arr;

    do
    {
/////////////////////////////////////////////////////////////Traitement du processus élu/////////////////////////////////////////////////////////////////////////
        if(util_cpu==0)
        {
            boucle=1;
            q=proc;
            pos=0;
            place=0;
            while(boucle==1)////////////////pour pointer sur le premier processus non encore terminé
            {
                if(q->date_arr<=execution_proc&&q->etat==0)
                {
                    existe_cpu=1;
                    duratt_cpu=q->dur_pret;
                    place=pos;
                    break;
                }
                if(q->suiv!=NULL) q=q->suiv;
                else boucle=0;
                pos++;
            }

            if(existe_cpu==1)
            {
                existe_cpu=0;
                boucle=1;
                T=proc;
                pos=0;
                while(boucle==1)////////////////pour detecter le processus qui doit utiliser le CPU car il a la plus grande duree d'attente
                {
                    if(T->date_arr<=execution_proc&&T->etat==0&&(T->dur_pret>duratt_cpu))
                    {
                        place=pos;
                        duratt_cpu=T->dur_pret;
                    }

                    if(T->suiv!=NULL) T=T->suiv;
                    else boucle=0;
                    pos++;
                }

                boucle=1;
                q=proc;
                cpt=0;
                while(boucle==1)////////////////pour compter le nombre des processus ayant la meme grande duree d'attente choisie
                {
                    if(q->date_arr<=execution_proc&&q->etat==0&&(q->dur_pret==duratt_cpu))
                    {
                        cpt++;
                    }
                    if(q->suiv!=NULL) q=q->suiv;
                    else boucle=0;
                }

                if(cpt!=1)
                {
                    boucle=1;
                    q=proc;
                    maj=1000;
                    pos=0;

                    while(boucle==1)////////////////choix par ordre alphabetique
                    {
                        if(q->date_arr<=execution_proc&&q->etat==0&&(q->dur_pret==duratt_cpu)&&som_acsii(q->code)<maj)
                        {
                            maj=som_acsii(q->code);
                            place=pos;
                        }
                        if(q->suiv!=NULL) q=q->suiv;
                        else boucle=0;
                        pos++;
                    }
                }

                boucle=1;
                T=proc;
                pos=0;
                while(boucle==1)////////////////pour pointer sur le processus choisis
                {
                    if(pos==place)
                    {
                        if(T->dur_exec_modif_proc>=qt)
                            util_cpu=qt;
                        else
                            util_cpu=T->dur_exec_modif_proc;
                        break;
                    }
                    if(T->suiv!=NULL) T=T->suiv;
                    else boucle=0;
                    pos++;
                }

                if(strcmp(T->code,cd_proc)!=0)
                {
                    strcpy(cd_proc,T->code);

                    pause=1;
                    T->cmt[i+1].elu=1;
                }
                else
                {
                    T->dur_exec_modif_proc--;
                    util_cpu--;

                    if(util_cpu==0&&T->dur_exec_modif_proc!=0)
                    {
                        strcpy(cd_proc,T->code);
                    }
                    T->cmt[i].elu=1;
                }
                T->dur_pret=0;

            }
        }
        else
        {
            T->dur_exec_modif_proc--;
            util_cpu--;

            if(util_cpu==0&&T->dur_exec_modif_proc!=0)
            {
                T->dur_pret--;
                strcpy(cd_proc,T->code);
            }
        }
/////////////////////////////////////////////////////////////Traitement des processus prets/////////////////////////////////////////////////////////////////////////
        boucle=1;
        q=proc;
        while(boucle==1)////////////////pour calculer la duree d'attente pour chaque processus pret
        {
            if(q->date_arr<=execution_proc&&q->etat==0)
            {
                if(strcmp(q->code,T->code)!=0)
                {
                    if(strcmp(q->code,code)==0&&proces[i-1].elu==1)//processus de elu vers pret venant de terminer son qt
                    {
                        proces[i].pret=-1;
                        proces[i].elu=-1;
                        proces[i].ent_sor=0;
                    }
                    else
                    {
                        if(strcmp(q->code,code)==0&&proces[i-1].elu!=1)//processus tjrs pret
                        {
                            proces[i].pret=1;
                            proces[i].elu=0;
                            proces[i].ent_sor=0;
                        }
                    }
                    q->dur_pret++;
                    if(q->dur_pret==1)
                        q->cmt[i].pret=1;
                }
                else
                {
                    if(strcmp(q->code,code)==0&&pause==0)//processus tjrs elu
                    {
                        proces[i].pret=0;
                        proces[i].elu=1;
                        proces[i].ent_sor=0;
                    }
                    else
                    {
                        if(strcmp(q->code,code)==0&&pause==1)
                        {
                            pause=0;

                            if(proces[i-1].ent_sor==0||proces[i-1].pret==1)
                            {
                                proces[i].pret=-1;//de pret vers elu
                            }
                            else proces[i].pret=0;

                            proces[i].elu=-1;

                            if(proces[i-1].ent_sor!=1||execution_proc==0)
                                proces[i].ent_sor=0;
                            else
                                proces[i].ent_sor=-1;//de E/S vers elu
                        }
                    }
                }
            }

            if(q->suiv!=NULL) q=q->suiv;
            else boucle=0;
        }
/////////////////////////////////////////////////////////////Traitement des entrées et sorties/////////////////////////////////////////////////////////////////////////
        boucle=1;
        q=proc;
        while(boucle==1)////////////////pour decrementer la dur es
        {

            if(q->date_arr<=execution_proc&&(q->etat==1||q->etat==2))
            {

                if(q->etat==1)
                {
                    if(strcmp(q->code,code)==0)
                    {
                        proces[i].pret=0;
                        proces[i].elu=-1;
                        proces[i].ent_sor=-1;
                    }

                    q->etat=2;
                }
                else
                {
                    if(strcmp(q->code,code)==0&&q->etat==2)
                    {
                        proces[i].pret=0;
                        proces[i].elu=0;
                        proces[i].ent_sor=1;
                    }
                    q->dur_modif_es--;

                    if(q->dur_modif_es==0)
                    {
                        q->etat=0;
                        q->dur_modif_es=q->dur_non_modif_es;
                    }
                }
            }
            if(q->suiv!=NULL) q=q->suiv;
            else boucle=0;
        }

        if(T->dur_exec_modif_proc==0&&T->etat==0)
        {
            if(T->dur_modif_es!=0)
            {
                T->etat=1;
                strcpy(cd_proc,"nothing");
                T->cmt[i+2].ent_sor=1;
            }
            T->dur_exec_modif_proc=T->dur_exec_non_modif_proc;
        }
        execution_proc++;
        i++;
    }
    while(execution_proc<N+1);
/////////////////////////////////////////////////////////////Initialisation des donées/////////////////////////////////////////////////////////////////////////
    boucle=1;
    T=proc;
    while(boucle==1)////////////////pour initialiser les donnees
    {
        T->dur_exec_modif_proc=T->dur_exec_non_modif_proc;
        T->dur_modif_es=T->dur_non_modif_es;
        T->dur_pret=0;
        T->etat=0;
        T->turn=0;
        T->dur_blq=0;

        if(T->suiv!=NULL) T=T->suiv;
        else boucle=0;
    }
}

/////////////////////////////////////////////////////////////TOURNIQUET DEUXIEME CAS////////////////////////////////////////////////////////////////////////
void tourniquet_pro_2(processus *proc,int N,char *code,int qt,info proces[])
{
    processus *T;
    processus *q;
    processus *K;
    processus *L;
    int boucle,cpt,maj;
    int duratt_cpu,place,pos,i,existe_cpu,util_cpu=0,pause=0,es_lib=1,existe_es=0,dur_es;
    int execution_proc=proc->date_arr;
    char cd_proc[10];
    strcpy(cd_proc,"nothing");

    for(i=0; i<N; i++)
    {
        proces[i].elu=-2;
        proces[i].ent_sor=-2;
        proces[i].pret=-2;
        proces[i].blq=-2;
    }

    boucle=1;
    T=proc;

    do
    {
        for(i=0; i<N; i++)
        {
            T->cmt[i].elu=0;
            T->cmt[i].pret=0;
            T->cmt[i].ent_sor=0;
            T->cmt[i].blq=0;
        }
        if(T->suiv!=NULL)
            T=T->suiv;
        else
            boucle=0;
    }
    while(boucle==1);


    i=proc->date_arr;

    do
    {
/////////////////////////////////////////////////////////////Traitement du processus élu/////////////////////////////////////////////////////////////////////////
        if(util_cpu==0)
        {
            boucle=1;
            q=proc;
            pos=0;
            place=0;
            while(boucle==1)////////////////pour pointer sur le premier processus non encore terminé
            {
                if(q->date_arr<=execution_proc&&q->etat==0)
                {
                    existe_cpu=1;
                    duratt_cpu=q->dur_pret;
                    place=pos;
                    break;
                }
                if(q->suiv!=NULL) q=q->suiv;
                else boucle=0;
                pos++;
            }

            if(existe_cpu==1)
            {
                existe_cpu=0;
                boucle=1;
                T=proc;
                pos=0;
                while(boucle==1)////////////////pour detecter le processus qui doit utiliser le CPU car il a la plus grande duree d'attente
                {
                    if(T->date_arr<=execution_proc&&T->etat==0&&(T->dur_pret>duratt_cpu))
                    {
                        place=pos;
                        duratt_cpu=T->dur_pret;
                    }

                    if(T->suiv!=NULL) T=T->suiv;
                    else boucle=0;
                    pos++;
                }

                boucle=1;
                T=proc;
                pos=0;
                while(boucle==1)////////////////pour pointer sur le processus choisis
                {
                    if(pos==place)
                    {
                        if(T->dur_exec_modif_proc>=qt)
                            util_cpu=qt;
                        else
                            util_cpu=T->dur_exec_modif_proc;
                        break;
                    }
                    if(T->suiv!=NULL) T=T->suiv;
                    else boucle=0;
                    pos++;
                }

                boucle=1;
                q=proc;
                cpt=0;
                while(boucle==1)////////////////pour compter le nombre des processus ayant la meme grande duree d'attente choisie
                {
                    if(q->date_arr<=execution_proc&&q->etat==0&&(q->dur_pret==duratt_cpu))
                    {
                        cpt++;
                    }
                    if(q->suiv!=NULL) q=q->suiv;
                    else boucle=0;
                }

                if(cpt!=1)
                {
                    boucle=1;
                    q=proc;
                    maj=1000;
                    pos=0;

                    while(boucle==1)////////////////choix par ordre alphabetique
                    {
                        if(q->date_arr<=execution_proc&&q->etat==0&&(q->dur_pret==duratt_cpu)&&som_acsii(q->code)<maj)
                        {
                            maj=som_acsii(q->code);
                            place=pos;
                        }
                        if(q->suiv!=NULL) q=q->suiv;
                        else boucle=0;
                        pos++;
                    }

                    boucle=1;
                    T=proc;
                    pos=0;
                    while(boucle==1)////////////////pour pointer sur le processus choisis
                    {
                        if(pos==place)
                        {
                            if(T->dur_exec_modif_proc>=qt)
                                util_cpu=qt;
                            else
                                util_cpu=T->dur_exec_modif_proc;
                            break;
                        }
                        if(T->suiv!=NULL) T=T->suiv;
                        else boucle=0;
                        pos++;
                    }
                }

                if(strcmp(T->code,cd_proc)!=0)
                {
                    strcpy(cd_proc,T->code);
                    pause=1;//TC au debut du processus
                    T->cmt[i+1].elu=1;
                }
                else
                {
                    T->dur_exec_modif_proc--;
                    util_cpu--;

                    if(util_cpu==0&&T->dur_exec_modif_proc!=0)
                    {
                        T->dur_pret--;
                        strcpy(cd_proc,T->code);
                    }
                    T->cmt[i].elu=1;
                }
                T->dur_pret=0;

            }
        }
        else
        {
            T->dur_exec_modif_proc--;
            util_cpu--;

            if(util_cpu==0&&T->dur_exec_modif_proc!=0)
            {
                T->dur_pret--;
                strcpy(cd_proc,T->code);
            }
        }
/////////////////////////////////////////////////////////////Traitement des processus prets/////////////////////////////////////////////////////////////////////////
        boucle=1;
        q=proc;
        while(boucle==1)////////////////pour calculer la duree d'attente pour chaque processus pret
        {
            if(q->date_arr<=execution_proc&&q->etat==0)
            {
                if(strcmp(q->code,T->code)!=0)
                {
                    if(strcmp(q->code,code)==0&&proces[i-1].elu==1)
                    {
                        proces[i].pret=-1;
                        proces[i].elu=-1;
                        proces[i].ent_sor=0;
                        proces[i].blq=0;
                    }
                    else
                    {
                        if(strcmp(q->code,code)==0&&proces[i-1].elu!=1)
                        {
                            proces[i].pret=1;
                            proces[i].elu=0;
                            proces[i].ent_sor=0;
                            proces[i].blq=0;
                        }
                    }
                    q->dur_pret++;
                    if(q->dur_pret==1)
                        q->cmt[i].pret=1;
                }
                else
                {
                    if(strcmp(q->code,code)==0&&pause==0)
                    {
                        proces[i].pret=0;
                        proces[i].elu=1;
                        proces[i].ent_sor=0;
                        proces[i].blq=0;
                    }
                    else
                    {
                        if(strcmp(q->code,code)==0&&pause==1)
                        {
                            pause=0;

                            if(proces[i-1].ent_sor==0||proces[i-1].pret==1)
                            {
                                proces[i].pret=-1;
                            }
                            else proces[i].pret=0;

                            proces[i].elu=-1;
                            proces[i].blq=0;

                            if(proces[i-1].ent_sor!=1||execution_proc==0)
                                proces[i].ent_sor=0;
                            else
                                proces[i].ent_sor=-1;
                        }
                    }
                }
            }

            if(q->suiv!=NULL) q=q->suiv;
            else boucle=0;
        }

/////////////////////////////////////////////////////////////Traitement du processus E/S/////////////////////////////////////////////////////////////////////////
        if(es_lib==1)
        {
            boucle=1;
            K=proc;
            pos=0;
            place=0;
            while(boucle==1)////////////////pour pointer sur le premier processus non encore terminé
            {
                if(K->date_arr<=execution_proc&&(K->etat==1||K->etat==2))
                {
                    existe_es=1;
                    dur_es=K->dur_non_modif_es;
                    place=pos;
                    break;
                }
                if(K->suiv!=NULL) K=K->suiv;
                else boucle=0;
                pos++;
            }

            if(existe_es==1)
            {
                existe_es=0;
                boucle=1;
                K=proc;
                pos=0;
                while(boucle==1)////////////////pour detecter le processus qui doit utiliser le E/S car il a la plus courte duree d'ES
                {
                    if(K->date_arr<=execution_proc&&(K->etat==1||K->etat==2)&&(K->dur_non_modif_es<dur_es))
                    {
                        place=pos;
                        dur_es=K->dur_non_modif_es;
                    }
                    if(K->suiv!=NULL) K=K->suiv;
                    else boucle=0;
                    pos++;
                }

                boucle=1;
                K=proc;
                cpt=0;
                while(boucle==1)////////////////pour compter le nombre des processus ayant la meme petite duree ES choisie
                {
                    if(K->date_arr<=execution_proc&&(K->etat==1||K->etat==2)&&(K->dur_non_modif_es==dur_es))
                    {
                        cpt++;
                    }
                    if(K->suiv!=NULL) K=K->suiv;
                    else boucle=0;
                }

                if(cpt!=1)
                {
                    boucle=1;
                    K=proc;
                    pos=0;
                    place=0;
                    while(boucle==1)////////////////pour pointer sur le premier processus non encore terminé
                    {
                        if(K->date_arr<=execution_proc&&(K->etat==1||K->etat==2))
                        {
                            dur_es=K->dur_blq;
                            place=pos;
                            break;
                        }
                        if(K->suiv!=NULL) K=K->suiv;
                        else boucle=0;
                        pos++;
                    }

                    boucle=1;
                    K=proc;
                    pos=0;
                    while(boucle==1)////////////////pour detecter le processus qui doit utiliser le E/S car il a la plus grande duree d'attente
                    {
                        if(K->date_arr<=execution_proc&&(K->etat==1||K->etat==2)&&(K->dur_blq>dur_es))
                        {
                            place=pos;
                            dur_es=K->dur_blq;
                        }
                        if(K->suiv!=NULL) K=K->suiv;
                        else boucle=0;
                        pos++;
                    }
                }

                boucle=1;
                K=proc;
                pos=0;
                while(boucle==1)////////////////pour pointer sur le processus choisis
                {
                    if(pos==place)
                        break;
                    else
                    {
                        if(K->suiv!=NULL) K=K->suiv;
                        else boucle=0;
                    }
                    pos++;
                }
                K->dur_blq=0;
                K->cmt[i+1].ent_sor=1;
                es_lib=0;
            }
        }
/////////////////////////////////////////////////////////////Traitement des processus bloqués/////////////////////////////////////////////////////////////////////////
        boucle=1;
        L=proc;
        while(boucle==1)
        {
            if(L->date_arr<=execution_proc&&(L->etat==1||L->etat==2))
            {
                if(L->etat==1)
                {
                    if(strcmp(L->code,code)==0&&strcmp(L->code,K->code)==0)
                    {
                        proces[i].pret=0;
                        proces[i].elu=-1;
                        proces[i].ent_sor=-1;
                        proces[i].blq=0;
                    }
                    else
                    {
                        if(strcmp(L->code,code)==0&&strcmp(L->code,K->code)!=0)
                        {
                            proces[i].pret=0;
                            proces[i].elu=-1;
                            proces[i].ent_sor=0;
                            proces[i].blq=-1;
                        }
                    }
                    L->etat=2;
                }
                else
                {
                    if(strcmp(L->code,K->code)!=0)
                    {
                        if(strcmp(L->code,code)==0)
                        {
                            proces[i].pret=0;
                            proces[i].elu=0;
                            proces[i].ent_sor=0;
                            proces[i].blq=1;
                        }
                        L->dur_blq++;
                        if(L->dur_blq==1)
                            L->cmt[i+1].blq=1;
                    }
                    else
                    {
                        if(strcmp(L->code,code)==0)
                        {
                            proces[i].pret=0;
                            proces[i].elu=0;
                            proces[i].ent_sor=1;
                            proces[i].blq=0;
                        }
                        L->dur_modif_es--;
                    }
                }

                if(L->dur_modif_es==0)
                {
                    es_lib=1;
                    L->dur_modif_es=L->dur_non_modif_es;
                    L->etat=0;
                }
            }

            if(L->suiv!=NULL) L=L->suiv;
            else boucle=0;
        }

        if(T->dur_exec_modif_proc==0&&T->etat==0)
        {
            if(T->dur_modif_es!=0)
            {
                T->etat=1;
                strcpy(cd_proc,"nothing");
            }
            T->dur_exec_modif_proc=T->dur_exec_non_modif_proc;
        }
        execution_proc++;
        i++;
    }
    while(execution_proc<N+1);
/////////////////////////////////////////////////////////////Initialisation des donées/////////////////////////////////////////////////////////////////////////
    boucle=1;
    T=proc;
    while(boucle==1)////////////////pour initialiser les donnees
    {
        T->dur_exec_modif_proc=T->dur_exec_non_modif_proc;
        T->dur_modif_es=T->dur_non_modif_es;
        T->dur_pret=0;
        T->dur_blq=0;
        T->etat=0;
        T->turn=0;

        if(T->suiv!=NULL) T=T->suiv;
        else boucle=0;
    }
}

/////////////////////////////////////////////////////////////FIFO PREMIER CAS/////////////////////////////////////////////////////////////////////////
void fifo_pro(processus *proc,int N,char *code,info proces[])
{
    processus *T;
    processus *q;
    int boucle;
    int proc_lib=1,duratt_cpu,place,pos,i,existe_cpu,cpt,maj;
    int execution_proc=proc->date_arr;

    for(i=0; i<N; i++)
    {
        proces[i].elu=-2;
        proces[i].ent_sor=-2;
        proces[i].pret=-2;
    }

    boucle=1;
    T=proc;

    do
    {
        for(i=0; i<N; i++)
        {
            T->cmt[i].elu=0;
            T->cmt[i].pret=0;
            T->cmt[i].ent_sor=0;
            T->cmt[i].blq=0;
        }
        if(T->suiv!=NULL)
            T=T->suiv;
        else
            boucle=0;
    }
    while(boucle==1);

    i=proc->date_arr;

    do
    {
/////////////////////////////////////////////////////////////Traitement du processus élu/////////////////////////////////////////////////////////////////////////
        if(proc_lib==1)
        {
            boucle=1;
            q=proc;
            pos=0;
            place=0;
            while(boucle==1)////////////////pour pointer sur le premier processus non encore terminé
            {
                if(q->date_arr<=execution_proc&&q->etat==0)
                {
                    existe_cpu=1;
                    duratt_cpu=q->dur_pret;
                    place=pos;
                    break;
                }
                if(q->suiv!=NULL) q=q->suiv;
                else boucle=0;
                pos++;
            }

            if(existe_cpu==1)
            {
                existe_cpu=0;
                boucle=1;
                T=proc;
                pos=0;
                while(boucle==1)////////////////pour detecter le processus qui doit utiliser le CPU car il a la plus grande duree d'attente
                {
                    if(T->date_arr<=execution_proc&&T->etat==0&&(T->dur_pret>duratt_cpu))
                    {
                        place=pos;
                        duratt_cpu=T->dur_pret;
                    }

                    if(T->suiv!=NULL) T=T->suiv;
                    else boucle=0;
                    pos++;
                }

                boucle=1;
                q=proc;
                cpt=0;
                while(boucle==1)////////////////pour compter le nombre des processus ayant la meme grande duree d'attente choisie
                {
                    if(q->date_arr<=execution_proc&&q->etat==0&&(q->dur_pret==duratt_cpu))
                    {
                        cpt++;
                    }
                    if(q->suiv!=NULL) q=q->suiv;
                    else boucle=0;
                }

                if(cpt!=1)
                {
                    boucle=1;
                    q=proc;
                    maj=1000;
                    pos=0;

                    while(boucle==1)////////////////choix par ordre alphabetique
                    {
                        if(q->date_arr<=execution_proc&&q->etat==0&&(q->dur_pret==duratt_cpu)&&som_acsii(q->code)<maj)
                        {
                            maj=som_acsii(q->code);
                            place=pos;
                        }
                        if(q->suiv!=NULL) q=q->suiv;
                        else boucle=0;
                        pos++;
                    }
                }

                boucle=1;
                T=proc;
                pos=0;
                while(boucle==1)////////////////pour pointer sur le processus choisis
                {
                    if(pos==place)
                        break;
                    else
                    {
                        if(T->suiv!=NULL) T=T->suiv;
                        else boucle=0;
                    }
                    pos++;
                }
                T->dur_pret=0;
                T->cmt[i].elu=1;
                proc_lib=0;
            }
        }
/////////////////////////////////////////////////////////////Traitement des processus prets/////////////////////////////////////////////////////////////////////////
        boucle=1;
        q=proc;
        while(boucle==1)////////////////pour calculer la duree d'attente de chaque processus pret
        {
            if(q->date_arr<=execution_proc&&q->etat==0)
            {
                if(strcmp(q->code,T->code)!=0)
                {
                    if(strcmp(q->code,code)==0)
                    {
                        proces[i].pret=1;
                        proces[i].elu=0;
                        proces[i].ent_sor=0;
                    }
                    q->dur_pret++;
                    if(q->dur_pret==1)
                        q->cmt[i].pret=1;
                }
                else
                {
                    if(strcmp(q->code,code)==0)
                    {
                        proces[i].pret=0;
                        proces[i].elu=1;
                        proces[i].ent_sor=0;
                    }
                    q->dur_exec_modif_proc--;
                }
            }

            if(q->suiv!=NULL) q=q->suiv;
            else boucle=0;
        }
/////////////////////////////////////////////////////////////Traitement des entrées et sorties/////////////////////////////////////////////////////////////////////////
        boucle=1;
        q=proc;
        while(boucle==1)////////////////pour decrementer la dur es
        {
            if(q->date_arr<=execution_proc&&q->etat==1)
            {
                if(strcmp(q->code,code)==0)
                {
                    proces[i].pret=0;
                    proces[i].elu=0;
                    proces[i].ent_sor=1;
                }
                q->dur_modif_es--;

                if(q->dur_modif_es==0)
                {
                    q->etat=0;
                    q->dur_modif_es=q->dur_non_modif_es;
                }
            }
            if(q->suiv!=NULL) q=q->suiv;
            else boucle=0;
        }

        if(T->date_arr<=execution_proc&&T->dur_exec_modif_proc==0&&T->etat==0)
        {
            if(T->dur_modif_es!=0)
            {
                T->etat=1;
                T->cmt[i+1].ent_sor=1;
            }
            T->dur_exec_modif_proc=T->dur_exec_non_modif_proc;
            proc_lib=1;
        }

        execution_proc++;
        i++;
    }
    while(execution_proc<N+1);
/////////////////////////////////////////////////////////////Initialisation des donées/////////////////////////////////////////////////////////////////////////
    boucle=1;
    T=proc;
    while(boucle==1)////////////////pour initialiser les donnees
    {
        T->dur_exec_modif_proc=T->dur_exec_non_modif_proc;
        T->dur_modif_es=T->dur_non_modif_es;
        T->dur_pret=0;
        T->etat=0;
        T->turn=0;
        T->dur_blq=0;

        if(T->suiv!=NULL) T=T->suiv;
        else boucle=0;
    }
}

/////////////////////////////////////////////////////////////FIFO DEUXIEME CAS/////////////////////////////////////////////////////////////////////////
void fifo_pro_2(processus *proc,int N,char *code,info proces[])
{
    processus *T;
    processus *q;
    processus *K;
    processus *L;
    int boucle;
    int proc_lib=1,es_lib=1,duratt_cpu,dur_es,place,pos,i,existe_cpu,existe_es=0,cpt,maj;
    int execution_proc=proc->date_arr;

    for(i=0; i<N; i++)
    {
        proces[i].elu=-2;
        proces[i].ent_sor=-2;
        proces[i].pret=-2;
        proces[i].blq=-2;
    }

    boucle=1;
    T=proc;

    do
    {
        for(i=0; i<N; i++)
        {
            T->cmt[i].elu=0;
            T->cmt[i].pret=0;
            T->cmt[i].ent_sor=0;
            T->cmt[i].blq=0;
        }
        if(T->suiv!=NULL)
            T=T->suiv;
        else
            boucle=0;
    }
    while(boucle==1);


    i=proc->date_arr;

    do
    {
/////////////////////////////////////////////////////////////Traitement du processus élu/////////////////////////////////////////////////////////////////////////
        if(proc_lib==1)
        {
            boucle=1;
            q=proc;
            pos=0;
            place=0;
            while(boucle==1)////////////////pour pointer sur le premier processus non encore terminé
            {
                if(q->date_arr<=execution_proc&&q->etat==0)
                {
                    existe_cpu=1;
                    duratt_cpu=q->dur_pret;
                    place=pos;
                    break;
                }
                if(q->suiv!=NULL) q=q->suiv;
                else boucle=0;
                pos++;
            }

            if(existe_cpu==1)
            {
                existe_cpu=0;
                boucle=1;
                T=proc;
                pos=0;
                while(boucle==1)////////////////pour detecter le processus qui doit utiliser le CPU car il a la plus grande duree d'attente
                {
                    if(T->date_arr<=execution_proc&&T->etat==0&&(T->dur_pret>duratt_cpu))
                    {
                        place=pos;
                        duratt_cpu=T->dur_pret;
                    }

                    if(T->suiv!=NULL) T=T->suiv;
                    else boucle=0;
                    pos++;
                }

                boucle=1;
                q=proc;
                cpt=0;
                while(boucle==1)////////////////pour compter le nombre des processus ayant la meme grande duree d'attente choisie
                {
                    if(q->date_arr<=execution_proc&&q->etat==0&&(q->dur_pret==duratt_cpu))
                    {
                        cpt++;
                    }
                    if(q->suiv!=NULL) q=q->suiv;
                    else boucle=0;
                }

                if(cpt!=1)
                {
                    boucle=1;
                    q=proc;
                    maj=1000;
                    pos=0;

                    while(boucle==1)////////////////choix par ordre alphabetique
                    {
                        if(q->date_arr<=execution_proc&&q->etat==0&&(q->dur_pret==duratt_cpu)&&som_acsii(q->code)<maj)
                        {
                            maj=som_acsii(q->code);
                            place=pos;
                        }
                        if(q->suiv!=NULL) q=q->suiv;
                        else boucle=0;
                        pos++;
                    }
                }

                boucle=1;
                T=proc;
                pos=0;
                while(boucle==1)////////////////pour pointer sur le processus choisis
                {
                    if(pos==place)
                        break;
                    else
                    {
                        if(T->suiv!=NULL) T=T->suiv;
                        else boucle=0;
                    }
                    pos++;
                }
                T->dur_pret=0;
                T->cmt[i].elu=1;
                proc_lib=0;
            }
        }
/////////////////////////////////////////////////////////////Traitement du processus E/S/////////////////////////////////////////////////////////////////////////
        if(es_lib==1)
        {
            boucle=1;
            K=proc;
            pos=0;
            place=0;
            while(boucle==1)////////////////pour pointer sur le premier processus non encore terminé
            {
                if(K->date_arr<=execution_proc&&K->etat==1)
                {
                    existe_es=1;
                    dur_es=K->dur_non_modif_es;
                    place=pos;
                    break;
                }
                if(K->suiv!=NULL) K=K->suiv;
                else boucle=0;
                pos++;
            }

            if(existe_es==1)
            {
                existe_es=0;
                boucle=1;
                K=proc;
                pos=0;
                while(boucle==1)////////////////pour detecter le processus qui doit utiliser le E/S car il a la plus courte duree d'ES
                {
                    if(K->date_arr<=execution_proc&&K->etat==1&&(K->dur_non_modif_es<dur_es))
                    {
                        place=pos;
                        dur_es=K->dur_non_modif_es;
                    }
                    if(K->suiv!=NULL) K=K->suiv;
                    else boucle=0;
                    pos++;
                }

                boucle=1;
                K=proc;
                cpt=0;
                while(boucle==1)////////////////pour compter le nombre des processus ayant la meme petite duree ES choisie
                {
                    if(K->date_arr<=execution_proc&&K->etat==1&&(K->dur_non_modif_es==dur_es))
                    {
                        cpt++;
                    }
                    if(K->suiv!=NULL) K=K->suiv;
                    else boucle=0;
                }

                if(cpt!=1)
                {
                    boucle=1;
                    K=proc;
                    pos=0;
                    place=0;
                    while(boucle==1)////////////////pour pointer sur le premier processus non encore terminé
                    {
                        if(K->date_arr<=execution_proc&&K->etat==1)
                        {
                            dur_es=K->dur_blq;
                            place=pos;
                            break;
                        }
                        if(K->suiv!=NULL) K=K->suiv;
                        else boucle=0;
                        pos++;
                    }

                    boucle=1;
                    K=proc;
                    pos=0;
                    while(boucle==1)////////////////pour detecter le processus qui doit utiliser le E/S car il a la plus grande duree d'attente
                    {
                        if(K->date_arr<=execution_proc&&K->etat==1&&(K->dur_blq>dur_es))
                        {
                            place=pos;
                            dur_es=K->dur_blq;
                        }
                        if(K->suiv!=NULL) K=K->suiv;
                        else boucle=0;
                        pos++;
                    }
                }

                boucle=1;
                K=proc;
                pos=0;
                while(boucle==1)////////////////pour pointer sur le processus choisis
                {
                    if(pos==place)
                        break;
                    else
                    {
                        if(K->suiv!=NULL) K=K->suiv;
                        else boucle=0;
                    }
                    pos++;
                }
                K->dur_blq=0;
                K->cmt[i].ent_sor=1;
                es_lib=0;
            }
        }

/////////////////////////////////////////////////////////////Traitement des processus prets/////////////////////////////////////////////////////////////////////////
        boucle=1;
        q=proc;
        while(boucle==1)////////////////pour calculer la duree d'attente pour chaque processus pret
        {
            if(q->date_arr<=execution_proc&&q->etat==0)
            {
                if(strcmp(q->code,T->code)!=0)
                {
                    if(strcmp(q->code,code)==0)
                    {
                        proces[i].pret=1;
                        proces[i].elu=0;
                        proces[i].ent_sor=0;
                        proces[i].blq=0;
                    }
                    q->dur_pret++;
                    if(q->dur_pret==1)
                        q->cmt[i].pret=1;
                }
                else
                {
                    if(strcmp(q->code,code)==0)
                    {
                        proces[i].pret=0;
                        proces[i].elu=1;
                        proces[i].ent_sor=0;
                        proces[i].blq=0;
                    }
                    q->dur_exec_modif_proc--;
                }
            }

            if(q->suiv!=NULL) q=q->suiv;
            else boucle=0;
        }

/////////////////////////////////////////////////////////////Traitement des processus bloqués/////////////////////////////////////////////////////////////////////////
        boucle=1;
        L=proc;
        while(boucle==1)
        {
            if(L->date_arr<=execution_proc&&L->etat==1)
            {
                if(strcmp(L->code,K->code)!=0)
                {
                    if(strcmp(L->code,code)==0)
                    {
                        proces[i].pret=0;
                        proces[i].elu=0;
                        proces[i].ent_sor=0;
                        proces[i].blq=1;
                    }
                    L->dur_blq++;
                    if(L->dur_blq==1)
                        L->cmt[i].blq=1;
                }
                else
                {
                    if(strcmp(L->code,code)==0)
                    {
                        proces[i].pret=0;
                        proces[i].elu=0;
                        proces[i].ent_sor=1;
                        proces[i].blq=0;
                    }
                    L->dur_modif_es--;
                }

                if(L->dur_modif_es==0)
                {
                    es_lib=1;
                    L->dur_modif_es=L->dur_non_modif_es;
                    L->etat=0;
                }
            }

            if(L->suiv!=NULL) L=L->suiv;
            else boucle=0;
        }

        if(T->dur_exec_modif_proc==0&&T->etat==0)////test qu'il vaut mieux le mettre apres le traitement des bloqués
        {
            if(T->dur_modif_es!=0)T->etat=1;
            T->dur_exec_modif_proc=T->dur_exec_non_modif_proc;
            proc_lib=1;
        }

        execution_proc++;
        i++;
    }
    while(execution_proc<N+1);

/////////////////////////////////////////////////////////////Initialisation des donées/////////////////////////////////////////////////////////////////////////
    boucle=1;
    T=proc;
    while(boucle==1)////////////////pour initialiser les donnees
    {
        T->dur_exec_modif_proc=T->dur_exec_non_modif_proc;
        T->dur_modif_es=T->dur_non_modif_es;
        T->dur_pret=0;
        T->dur_blq=0;
        T->etat=0;
        T->turn=0;

        if(T->suiv!=NULL) T=T->suiv;
        else boucle=0;
    }
}

/////////////////////////////////////////////////////////////PRIO AVEC REQUI PREMIER CAS/////////////////////////////////////////////////////////////////////////
void prio_avec_req(processus *proc,int N,char *code,info proces[])
{
    processus *T;
    processus *q;
    int boucle,prem_tour,tour=0;
    int place,pos,i,cpt_arr,prio_max,cpt_ocu,maj;
    char cd_proc[10];
    int execution_proc=proc->date_arr;
    strcpy(cd_proc,"nothing");

    for(i=0; i<N; i++)
    {
        proces[i].elu=-2;
        proces[i].ent_sor=-2;
        proces[i].pret=-2;
    }

    boucle=1;
    T=proc;

    do
    {
        for(i=0; i<N; i++)
        {
            T->cmt[i].elu=0;
            T->cmt[i].pret=0;
            T->cmt[i].ent_sor=0;
            T->cmt[i].blq=0;
        }
        if(T->suiv!=NULL)
            T=T->suiv;
        else
            boucle=0;
    }
    while(boucle==1);


    i=proc->date_arr;

    do
    {
/////////////////////////////////////////////////////////////Traitement du processus élu/////////////////////////////////////////////////////////////////////////
        boucle=1;
        q=proc;
        cpt_arr=0;

        while(boucle==1)////////////////pour pointer sur le premier processus non encore terminé
        {
            if(q->date_arr<=execution_proc&&q->etat==0&&q->dur_exec_modif_proc!=0&&q->dur_modif_es==q->dur_non_modif_es)
            {
                cpt_arr++;
            }
            if(q->suiv!=NULL) q=q->suiv;
            else boucle=0;
        }

        if((cpt_arr>1)||(cpt_arr==1&&strcmp(cd_proc,T->code)!=0))
        {
            if(T->date_arr<=execution_proc&&T->etat==0&&T->dur_exec_modif_proc!=T->dur_exec_non_modif_proc)
            {
                tour++;
                T->turn=tour;
            }

            boucle=1;
            q=proc;
            pos=0;
            place=0;
            while(boucle==1)////////////////pour pointer sur le premier processus non encore terminé
            {
                if(q->date_arr<=execution_proc&&q->etat==0)
                {
                    prio_max=q->priorite;
                    place=pos;
                    break;
                }
                if(q->suiv!=NULL) q=q->suiv;
                else boucle=0;
                pos++;
            }


            boucle=1;
            T=proc;
            pos=0;
            while(boucle==1)////////////////pour detecter le processus qui doit utiliser le CPU car il a la plus grande priorité
            {
                if(T->date_arr<=execution_proc&&T->etat==0&&(T->priorite)>(prio_max))
                {
                    place=pos;
                    prio_max=T->priorite;
                }
                if(T->suiv!=NULL) T=T->suiv;
                else
                {
                    boucle=0;
                }
                pos++;
            }

            cpt_ocu=0;
            boucle=1;
            q=proc;
            while(boucle==1)////////////////pour savoir s'il y a des processus ayant la meme priorité
            {
                if(q->date_arr<=execution_proc&&q->etat==0&&q->priorite==prio_max)
                {
                    cpt_ocu++;
                }
                if(q->suiv!=NULL) q=q->suiv;
                else boucle=0;
            }

            if(cpt_ocu!=1)
            {
                boucle=1;
                q=proc;
                while(boucle==1)////////////////pour pointer sur le premier processus ayant la priorité max
                {
                    if(q->date_arr<=execution_proc&&q->etat==0&&q->priorite==prio_max)
                    {
                        prem_tour=q->turn;
                        break;
                    }
                    if(q->suiv!=NULL) q=q->suiv;
                    else boucle=0;
                }

                boucle=1;
                T=proc;
                pos=0;
                while(boucle==1)////////////////pour detecter le processus qui doit utiliser le CPU car il a la plus grande priorité et le premier tour (remise en tete)
                {
                    if(T->date_arr<=execution_proc&&T->etat==0&&(T->turn)>(prem_tour))
                    {
                        place=pos;
                        prem_tour=T->turn;
                    }
                    if(T->suiv!=NULL) T=T->suiv;
                    else
                    {
                        boucle=0;
                    }
                    pos++;
                }


                boucle=1;
                q=proc;
                cpt_ocu=0;
                while(boucle==1)////////////////pour compter le nombre des processus ayant le meme grand tour
                {
                    if(q->date_arr<=execution_proc&&q->etat==0&&(q->turn==prem_tour))
                    {
                        cpt_ocu++;
                    }
                    if(q->suiv!=NULL) q=q->suiv;
                    else boucle=0;
                }

                if(cpt_ocu!=1)
                {

                    boucle=1;
                    q=proc;
                    maj=1000;
                    pos=0;

                    while(boucle==1)////////////////choix par ordre alphabetique pour le cas des processus ayant la meme pluis rande priorité et meme tour = 0 car ils ont la meme date d'arrivée
                    {
                        if(q->date_arr<=execution_proc&&q->etat==0&&(q->turn==prem_tour)&&som_acsii(q->code)<maj)
                        {

                            maj=som_acsii(q->code);
                            place=pos;
                        }
                        if(q->suiv!=NULL) q=q->suiv;
                        else
                        {
                            boucle=0;
                        }
                        pos++;
                    }
                }
            }

            boucle=1;
            T=proc;
            pos=0;
            while(boucle==1)////////////////pour pointer sur le processus choisis
            {
                if(pos==place)
                    break;
                else
                {
                    if(T->suiv!=NULL) T=T->suiv;
                    else boucle=0;
                }
                pos++;
            }

            if(strcmp(cd_proc,T->code)!=0)
            {
                strcpy(cd_proc,T->code);
                T->cmt[i].elu=1;
                T->dur_pret=0;
                T->turn=0;
            }
        }
        else
            tour=0;

/////////////////////////////////////////////////////////////Traitement des processus prets/////////////////////////////////////////////////////////////////////////
        boucle=1;
        q=proc;
        while(boucle==1)////////////////pour calculer la duree d'attente pour chaque processus pret
        {
            if(q->date_arr<=execution_proc&&q->etat==0)
            {
                if(strcmp(q->code,T->code)!=0)
                {
                    if(strcmp(q->code,code)==0)
                    {
                        proces[i].pret=1;
                        proces[i].elu=0;
                        proces[i].ent_sor=0;
                    }
                    q->dur_pret++;
                    if(q->dur_pret==1)
                        q->cmt[i].pret=1;
                }
                else
                {
                    if(strcmp(q->code,code)==0)
                    {
                        proces[i].pret=0;
                        proces[i].elu=1;
                        proces[i].ent_sor=0;
                    }
                    q->dur_exec_modif_proc--;
                }
            }

            if(q->suiv!=NULL) q=q->suiv;
            else boucle=0;
        }
/////////////////////////////////////////////////////////////Traitement des entrées et sorties/////////////////////////////////////////////////////////////////////////
        boucle=1;
        q=proc;
        while(boucle==1)////////////////pour decrementer la dur es
        {
            if(q->date_arr<=execution_proc&&q->etat==1)
            {
                if(strcmp(q->code,code)==0)
                {
                    proces[i].pret=0;
                    proces[i].elu=0;
                    proces[i].ent_sor=1;
                }
                q->dur_modif_es--;

                if(q->dur_modif_es==0)
                {
                    q->etat=0;
                    q->dur_modif_es=q->dur_non_modif_es;
                }
            }
            if(q->suiv!=NULL) q=q->suiv;
            else boucle=0;
        }

        if(T->dur_exec_modif_proc==0&&T->etat==0)
        {
            if(T->dur_modif_es!=0)
            {
                T->etat=1;
                T->cmt[i+1].ent_sor=1;
                strcpy(cd_proc,"nothing");
            }
            T->dur_exec_modif_proc=T->dur_exec_non_modif_proc;
        }
        execution_proc++;
        i++;
    }
    while(execution_proc<N+1);

/////////////////////////////////////////////////////////////Initialisation des donées/////////////////////////////////////////////////////////////////////////
    boucle=1;
    T=proc;
    while(boucle==1)////////////////pour initialiser les donnees
    {
        T->dur_exec_modif_proc=T->dur_exec_non_modif_proc;
        T->dur_modif_es=T->dur_non_modif_es;
        T->dur_pret=0;
        T->dur_blq=0;
        T->turn=0;
        T->etat=0;

        if(T->suiv!=NULL) T=T->suiv;
        else boucle=0;
    }
}

/////////////////////////////////////////////////////////////PRIO AVEC REQUI DEUXIEME CAS/////////////////////////////////////////////////////////////////////////
void prio_avec_req_2(processus *proc,int N,char *code,info proces[])
{
    processus *T;
    processus *q;
    processus *K;
    processus *L;
    int boucle,prem_tour,tour=0,maj;
    int place,pos,i,cpt_arr,prio_max,cpt_ocu,es_lib=1,dur_es,existe_es=0,cpt;
    char cd_proc[10];
    int execution_proc=proc->date_arr;

    strcpy(cd_proc,"nothing");

    for(i=0; i<N; i++)
    {
        proces[i].elu=-2;
        proces[i].ent_sor=-2;
        proces[i].pret=-2;
        proces[i].blq=-2;
    }

    boucle=1;
    T=proc;

    do
    {
        for(i=0; i<N; i++)
        {
            T->cmt[i].elu=0;
            T->cmt[i].pret=0;
            T->cmt[i].ent_sor=0;
            T->cmt[i].blq=0;
        }
        if(T->suiv!=NULL)
            T=T->suiv;
        else
            boucle=0;
    }
    while(boucle==1);


    i=proc->date_arr;

    do
    {
/////////////////////////////////////////////////////////////Traitement du processus élu/////////////////////////////////////////////////////////////////////////
        boucle=1;
        q=proc;
        cpt_arr=0;

        while(boucle==1)////////////////pour pointer sur le premier processus non encore terminé
        {
            if(q->date_arr<=execution_proc&&q->etat==0&&q->dur_exec_modif_proc!=0&&q->dur_modif_es==q->dur_non_modif_es)
            {
                cpt_arr++;
            }
            if(q->suiv!=NULL) q=q->suiv;
            else boucle=0;
        }

        if((cpt_arr>1)||(cpt_arr==1&&strcmp(cd_proc,T->code)!=0))
        {
            if(T->date_arr<=execution_proc&&T->etat==0&&T->dur_exec_modif_proc!=T->dur_exec_non_modif_proc)
            {
                tour++;
                T->turn=tour;
            }

            boucle=1;
            q=proc;
            pos=0;
            place=0;
            while(boucle==1)////////////////pour pointer sur le premier processus non encore terminé
            {
                if(q->date_arr<=execution_proc&&q->etat==0)
                {
                    prio_max=q->priorite;
                    place=pos;
                    break;
                }
                if(q->suiv!=NULL) q=q->suiv;
                else boucle=0;
                pos++;
            }

            boucle=1;
            T=proc;
            pos=0;
            while(boucle==1)////////////////pour detecter le processus qui doit utiliser le CPU car il a la plus grande priorité
            {
                if(T->date_arr<=execution_proc&&T->etat==0&&(T->priorite)>(prio_max))
                {
                    place=pos;
                    prio_max=T->priorite;
                }
                if(T->suiv!=NULL) T=T->suiv;
                else
                {
                    boucle=0;
                }
                pos++;
            }

            cpt_ocu=0;
            boucle=1;
            q=proc;
            while(boucle==1)////////////////pour savoir s'il y a des processus ayant la meme priorité
            {
                if(q->date_arr<=execution_proc&&q->etat==0&&q->priorite==prio_max)
                {
                    cpt_ocu++;
                }
                if(q->suiv!=NULL) q=q->suiv;
                else boucle=0;
            }

            if(cpt_ocu!=1)
            {
                boucle=1;
                q=proc;
                while(boucle==1)////////////////pour pointer sur le premier processus ayant la priorité max
                {
                    if(q->date_arr<=execution_proc&&q->etat==0&&q->priorite==prio_max)
                    {
                        prem_tour=q->turn;
                        break;
                    }
                    if(q->suiv!=NULL) q=q->suiv;
                    else boucle=0;
                }

                boucle=1;
                T=proc;
                pos=0;
                while(boucle==1)////////////////pour detecter le processus qui doit utiliser le CPU car il a la plus grande priorité et le premier tour (remise en tete)
                {
                    if(T->date_arr<=execution_proc&&T->etat==0&&(T->turn)>(prem_tour))
                    {
                        place=pos;
                        prem_tour=T->turn;
                    }
                    if(T->suiv!=NULL) T=T->suiv;
                    else
                    {
                        boucle=0;
                    }
                    pos++;
                }
                boucle=1;
                q=proc;
                cpt_ocu=0;
                while(boucle==1)////////////////pour compter le nombre des processus ayant le meme grand tour
                {
                    if(q->date_arr<=execution_proc&&q->etat==0&&(q->turn==prem_tour))
                    {
                        cpt_ocu++;
                    }
                    if(q->suiv!=NULL) q=q->suiv;
                    else boucle=0;
                }

                if(cpt_ocu!=1)
                {
                    boucle=1;
                    q=proc;
                    maj=1000;
                    pos=0;

                    while(boucle==1)////////////////choix par ordre alphabetique
                    {
                        if(q->date_arr<=execution_proc&&q->etat==0&&(q->turn==prem_tour)&&som_acsii(q->code)<maj)
                        {

                            maj=som_acsii(q->code);
                            place=pos;
                        }
                        if(q->suiv!=NULL) q=q->suiv;
                        else
                        {
                            boucle=0;
                        }
                        pos++;
                    }
                }
            }

            boucle=1;
            T=proc;
            pos=0;
            while(boucle==1)////////////////pour pointer sur le processus choisis
            {
                if(pos==place)
                    break;
                else
                {
                    if(T->suiv!=NULL) T=T->suiv;
                    else boucle=0;
                }
                pos++;
            }

            if(strcmp(cd_proc,T->code)!=0)
            {
                strcpy(cd_proc,T->code);
                T->cmt[i].elu=1;
                T->dur_pret=0;
                T->turn=0;
            }
        }
        else
            tour=0;
///////////////////////////////////////////////////////////Traitement du processus E/S/////////////////////////////////////////////////////////////////////////
        if(es_lib==1)
        {
            boucle=1;
            K=proc;
            pos=0;
            place=0;
            while(boucle==1)////////////////pour pointer sur le premier processus non encore terminé
            {
                if(K->date_arr<=execution_proc&&K->etat==1)
                {
                    existe_es=1;
                    dur_es=K->dur_non_modif_es;
                    place=pos;
                    break;
                }
                if(K->suiv!=NULL) K=K->suiv;
                else boucle=0;
                pos++;
            }
            if(existe_es==1)
            {
                existe_es=0;
                boucle=1;
                K=proc;
                pos=0;
                while(boucle==1)////////////////pour detecter le processus qui doit utiliser le E/S car il a la plus courte duree d'ES
                {
                    if(K->date_arr<=execution_proc&&K->etat==1&&(K->dur_non_modif_es<dur_es))
                    {
                        place=pos;
                        dur_es=K->dur_non_modif_es;
                    }
                    if(K->suiv!=NULL) K=K->suiv;
                    else boucle=0;
                    pos++;
                }

                boucle=1;
                K=proc;
                cpt=0;
                while(boucle==1)////////////////pour compter le nombre des processus ayant la meme petite duree ES choisie
                {
                    if(K->date_arr<=execution_proc&&K->etat==1&&(K->dur_non_modif_es==dur_es))
                    {
                        cpt++;
                    }
                    if(K->suiv!=NULL) K=K->suiv;
                    else boucle=0;
                }

                if(cpt!=1)
                {
                    boucle=1;
                    K=proc;
                    pos=0;
                    place=0;
                    while(boucle==1)////////////////pour pointer sur le premier processus non encore terminé
                    {
                        if(K->date_arr<=execution_proc&&K->etat==1)
                        {
                            dur_es=K->dur_blq;
                            place=pos;
                            break;
                        }
                        if(K->suiv!=NULL) K=K->suiv;
                        else boucle=0;
                        pos++;
                    }

                    boucle=1;
                    K=proc;
                    pos=0;
                    while(boucle==1)////////////////pour detecter le processus qui doit utiliser le E/S car il a la plus grande duree d'attente
                    {
                        if(K->date_arr<=execution_proc&&K->etat==1&&(K->dur_blq>dur_es))
                        {
                            place=pos;
                            dur_es=K->dur_blq;
                        }
                        if(K->suiv!=NULL) K=K->suiv;
                        else boucle=0;
                        pos++;
                    }
                }

                boucle=1;
                K=proc;
                pos=0;
                while(boucle==1)////////////////pour pointer sur le processus choisis
                {
                    if(pos==place)
                        break;
                    else
                    {
                        if(K->suiv!=NULL) K=K->suiv;
                        else boucle=0;
                    }
                    pos++;
                }
                K->dur_blq=0;
                K->cmt[i].ent_sor=1;
                es_lib=0;
            }
        }

/////////////////////////////////////////////////////////////Traitement des processus prets/////////////////////////////////////////////////////////////////////////
        boucle=1;
        q=proc;
        while(boucle==1)////////////////pour calculer la duree d'attente pour chaque processus pret
        {
            if(q->date_arr<=execution_proc&&q->etat==0)
            {
                if(strcmp(q->code,T->code)!=0)
                {
                    if(strcmp(q->code,code)==0)
                    {
                        proces[i].pret=1;
                        proces[i].elu=0;
                        proces[i].ent_sor=0;
                        proces[i].blq=0;
                    }
                    q->dur_pret++;
                    if(q->dur_pret==1)
                        q->cmt[i].pret=1;
                }
                else
                {
                    if(strcmp(q->code,code)==0)
                    {
                        proces[i].pret=0;
                        proces[i].elu=1;
                        proces[i].ent_sor=0;
                        proces[i].blq=0;
                    }
                    q->dur_exec_modif_proc--;
                }
            }

            if(q->suiv!=NULL) q=q->suiv;
            else boucle=0;
        }
/////////////////////////////////////////////////////////////Traitement des processus bloqués/////////////////////////////////////////////////////////////////////////
        boucle=1;
        L=proc;
        while(boucle==1)
        {
            if(L->date_arr<=execution_proc&&L->etat==1)
            {
                if(strcmp(L->code,K->code)!=0)
                {

                    if(strcmp(L->code,code)==0)
                    {
                        proces[i].pret=0;
                        proces[i].elu=0;
                        proces[i].ent_sor=0;
                        proces[i].blq=1;
                    }
                    L->dur_blq++;
                    if(L->dur_blq==1)
                        L->cmt[i].blq=1;
                }
                else
                {
                    if(strcmp(L->code,code)==0)
                    {

                        proces[i].pret=0;
                        proces[i].elu=0;
                        proces[i].ent_sor=1;
                        proces[i].blq=0;
                    }
                    L->dur_modif_es--;
                }

                if(L->dur_modif_es==0)
                {
                    es_lib=1;
                    L->dur_modif_es=L->dur_non_modif_es;
                    L->etat=0;
                }
            }

            if(L->suiv!=NULL) L=L->suiv;
            else boucle=0;
        }

        if(T->dur_exec_modif_proc==0&&T->etat==0)////test qu'il vaut mieux le mettre apres le traitement des bloqués
        {
            if(T->dur_modif_es!=0)
            {
                T->etat=1;
                strcpy(cd_proc,"nothing");
            }
            T->dur_exec_modif_proc=T->dur_exec_non_modif_proc;
        }
        execution_proc++;
        i++;
    }
    while(execution_proc<N+1);

/////////////////////////////////////////////////////////////Initialisation des donées/////////////////////////////////////////////////////////////////////////
    boucle=1;
    T=proc;
    while(boucle==1)////////////////pour initialiser les donnees
    {
        T->dur_exec_modif_proc=T->dur_exec_non_modif_proc;
        T->dur_modif_es=T->dur_non_modif_es;
        T->dur_pret=0;
        T->dur_blq=0;
        T->etat=0;
        T->turn=0;

        if(T->suiv!=NULL) T=T->suiv;
        else boucle=0;
    }
}

///////////////////////////////////////Les fonctions d'affichage du titre d'algorithme d'ordonnancement////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void title_fifo_1(void)
{
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(218);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(191);
    printf("\n");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(179);
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("First In First Out sans %ctat Bloqu%c",130,130);
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    putchar(179);
    printf("\n");
    printf("        ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    putchar(192);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(217);
    printf("\n");

}

void title_trq_1(void)
{
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(218);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(191);
    printf("\n");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(179);
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("Tourniquet avec TC=1 sans %ctat Bloqu%c",130,130);
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    putchar(179);
    printf("\n");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(192);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(217);
    printf("\n");

}

void title_par_1(void)
{
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(218);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(191);
    printf("\n");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(179);
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("Priorit%c avec r%cquisition sans %ctat Bloqu%c",130,130,130,130);
    printf(" ");
    printf(" ");
    printf(" ");
    putchar(179);
    printf("\n");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(192);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(217);
    printf("\n");

}

void title_fifo_2(void)
{
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(218);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(191);
    printf("\n");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(179);
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("First In First Out avec %ctat Bloqu%c",130,130);
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    putchar(179);
    printf("\n");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(192);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(217);
    printf("\n");

}

void title_trq_2(void)
{
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(218);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(191);
    printf("\n");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(179);
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("Tourniquet avec TC=1 avec %ctat Bloqu%c",130,130);
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    putchar(179);
    printf("\n");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(192);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(217);
    printf("\n");

}

void title_par_2(void)
{
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(218);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(191);
    printf("\n");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(179);
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("Priorit%c avec r%cquisition avec %ctat Bloqu%c",130,130,130,130);
    printf(" ");
    printf(" ");
    printf(" ");
    putchar(179);
    printf("\n");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(192);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(217);
    printf("\n");

}

///////////////////////////////////////////Les fonctions d'affichage du tableau des données//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void entete(void)
{
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(218);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(194);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(194);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(194);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(194);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(191);
    printf("\n");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(179);
    printf(" ");
    printf("Processus");
    printf(" ");
    putchar(179);
    printf(" ");
    printf("Date d'arr ");
    putchar(179);
    printf(" ");
    printf("Temps d'exec ");
    putchar(179);
    printf(" ");
    printf("Temps d'E/S");
    printf(" ");
    putchar(179);
    printf(" ");
    printf("Priorit%c ",130);
    printf(" ");
    putchar(179);
    printf("\n");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(195);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(197);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(197);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(197);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(197);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(180);
}

void milieu(char *a,int b,int c,int d,int e)
{
    int aa=strlen(a),i;
    int bb;
    int cc;
    int dd;
    int ee;

    if(b>=10)
        bb=2;
    else
        bb=1;

    if(c>=10)
        cc=2;
    else
        cc=1;

    if(d>=10)
        dd=2;
    else
        dd=1;

    if(e>=10)
        ee=2;
    else
        ee=1;



    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(179);
    printf(" ");

    for(i=1; i<=(9-aa)/2; i++)
        printf(" ");
    printf("%s",a);
    for(i=1; i<=((9-aa)/2)+(9-aa)%2; i++)
        printf(" ");

    printf(" ");
    putchar(179);
    printf(" ");


    if(bb==1)
    {
        for(i=1; i<=5; i++)
            printf(" ");
        printf("%d",b);
        for(i=1; i<=4; i++)
            printf(" ");
    }
    else
    {
        for(i=1; i<=4; i++)
            printf(" ");
        printf("%d",b);
        for(i=1; i<=4; i++)
            printf(" ");
    }


    printf(" ");
    putchar(179);
    printf(" ");

    if(cc==1)
    {
        for(i=1; i<=5; i++)
            printf(" ");
        printf("%d",c);
        for(i=1; i<=6; i++)
            printf(" ");
    }
    else
    {
        for(i=1; i<=5; i++)
            printf(" ");
        printf("%d",c);
        for(i=1; i<=5; i++)
            printf(" ");
    }

    printf(" ");
    putchar(179);
    printf(" ");

    if(dd==1)
    {
        for(i=1; i<=5; i++)
            printf(" ");
        printf("%d",d);
        for(i=1; i<=5; i++)
            printf(" ");
    }
    else
    {
        for(i=1; i<=5; i++)
            printf(" ");
        printf("%d",d);
        for(i=1; i<=4; i++)
            printf(" ");
    }

    printf(" ");
    putchar(179);
    printf(" ");

    if(ee==1)
    {
        for(i=1; i<=4; i++)
            printf(" ");
        printf("%d",e);
        for(i=1; i<=5; i++)
            printf(" ");
    }
    else
    {
        for(i=1; i<=4; i++)
            printf(" ");
        printf("%d",e);
        for(i=1; i<=4; i++)
            printf(" ");
    }

    putchar(179);
    printf("\n");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(195);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(197);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(197);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(197);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(197);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(180);
}

void fin_tab(char *a,int b,int c,int d,int e)
{
    int aa=strlen(a),i;
    int bb;
    int cc;
    int dd;
    int ee;

    if(b>=10)
        bb=2;
    else
        bb=1;

    if(c>=10)
        cc=2;
    else
        cc=1;

    if(d>=10)
        dd=2;
    else
        dd=1;

    if(e>=10)
        ee=2;
    else
        ee=1;


    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(179);
    printf(" ");

    for(i=1; i<=(9-aa)/2; i++)
        printf(" ");
    printf("%s",a);
    for(i=1; i<=((9-aa)/2)+(9-aa)%2; i++)
        printf(" ");

    printf(" ");
    putchar(179);
    printf(" ");

    if(bb==1)
    {
        for(i=1; i<=5; i++)
            printf(" ");
        printf("%d",b);
        for(i=1; i<=4; i++)
            printf(" ");
    }
    else
    {
        for(i=1; i<=4; i++)
            printf(" ");
        printf("%d",b);
        for(i=1; i<=4; i++)
            printf(" ");
    }

    printf(" ");
    putchar(179);
    printf(" ");

    if(cc==1)
    {
        for(i=1; i<=5; i++)
            printf(" ");
        printf("%d",c);
        for(i=1; i<=6; i++)
            printf(" ");
    }
    else
    {
        for(i=1; i<=5; i++)
            printf(" ");
        printf("%d",c);
        for(i=1; i<=5; i++)
            printf(" ");
    }

    printf(" ");
    putchar(179);
    printf(" ");


    if(dd==1)
    {
        for(i=1; i<=5; i++)
            printf(" ");
        printf("%d",d);
        for(i=1; i<=5; i++)
            printf(" ");
    }
    else
    {
        for(i=1; i<=5; i++)
            printf(" ");
        printf("%d",d);
        for(i=1; i<=4; i++)
            printf(" ");
    }

    printf(" ");
    putchar(179);
    printf(" ");

    if(ee==1)
    {
        for(i=1; i<=4; i++)
            printf(" ");
        printf("%d",e);
        for(i=1; i<=5; i++)
            printf(" ");
    }
    else
    {
        for(i=1; i<=4; i++)
            printf(" ");
        printf("%d",e);
        for(i=1; i<=4; i++)
            printf(" ");
    }



    putchar(179);
    printf("\n");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(192);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(193);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(193);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(193);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(193);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(217);
}

void afficher_proc(processus *proc,int nbr,char nom_fich[])
{

    int boucle=1;
    int pos=1;
    processus *T=proc;

    printf("\n\t\t           Liste des donn%ces du fichier %s : \n",130,nom_fich);
    printf("\n");
    entete();

    do
    {
        if(pos!=nbr)
        {
            printf("\n");
            milieu(T->code,T->date_arr,T->dur_exec_non_modif_proc,T->dur_non_modif_es,T->priorite);
        }
        else
        {
            printf("\n");
            fin_tab(T->code,T->date_arr,T->dur_exec_non_modif_proc,T->dur_non_modif_es,T->priorite);
        }

        if(T->suiv!=NULL)
        {
            T=T->suiv;
        }
        else
            boucle=0;
        pos++;
    }
    while(boucle==1);

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void titre(void)
{
    printf("                 --------------------------------------------------------\n");
    printf("                |                     ~~ ORDO-3P1B ~~                    |\n");
    printf("                |           PROGRAMME DE GESTION DES PROCESSUS           |\n");
    printf("                 --------------------------------------------------------\n");
}

int menu_prin(int enreg_don)
{
    int boucle=1,rep;

    printf(" \n                             -------------------------------\n");
    printf("                            |         MENU PRINCIPAL        |\n");
    printf("                             -------------------------------\n");
    printf("                            |   1 . Chargement des donn%ces  |\n",130);;
    printf("                            |   2 . Liste des donn%ces       |\n",130);;
    printf("                            |   3 . Choix d'algorithme      |\n");
    printf("                            |   4 . Quitter                 |\n");
    printf("                             -------------------------------\n");
    do
    {
        printf("\t\t\t\t\tVotre Choix : ");
        rep=getch();


        if(rep!=49&&rep!=50&&rep!=51&&rep!=52)
        {
            printf("\nVeuillez effectuer un choix entre 1 et 4 !!\n");
            boucle=1;
        }
        else
        {
            if(enreg_don==1)
            {
                boucle=0;
            }
            else
            {
                if((rep==50||rep==51)&&enreg_don==0)
                    printf("\nVous devez charger vos donn%ces d'abord !!\n",130);
                else
                    boucle=0;
            }
        }
    }
    while(boucle==1);
    return rep;
}

int menu_ch_algo(void)
{
    int rep;

    titre();

    printf(" \n                   ---------------------------------------------------\n");
    printf("                  |            ALGORITHMES D'ODONNANCEMENT            |\n");
    printf("                   ---------------------------------------------------\n");
    printf("\t          |\t\t   ");
    putchar(4);
    printf(" Sans %ctat bloqu%c ",130,130);
    putchar(4);
    printf("\t\t      |");
    printf("\n\t          |\t\t\t\t\t\t      |\n");
    printf("                  |   1 . FIFO                                        |\n");
    printf("                  |   2 . Tourniquet+TC=1                             |\n");
    printf("                  |   3 . Priorit%c avec r%cquisition                   |",130,130);
    printf("\n\t          |\t\t\t\t\t\t      |\n");
    printf("\t          |\t     ");
    putchar(4);
    printf(" Avec %ctat bloqu%c g%cr%c par SJF ",130,130,130,130);
    putchar(4);
    printf("\t      |");
    printf("\n\t          |\t\t\t\t\t\t      |\n");
    printf("                  |   4 . FIFO                                        |\n");
    printf("                  |   5 . Tourniquet+TC=1                             |\n");
    printf("                  |   6 . Priorit%c avec r%cquisition                   |",130,130);
    printf("\n\t          |\t\t\t\t\t\t      |\n");
    printf("                  |   7 . Retourner au menu principal                 |");
    printf("\n\t          |\t\t\t\t\t\t      |\n");
    printf("                   ---------------------------------------------------\n");

    printf("\t\t\t\t\t       Votre Choix : ");

    do
    {
        rep=getch();
    }
    while(rep!=49&&rep!=50&&rep!=51&&rep!=52&&rep!=53&&rep!=54&&rep!=55);

    return rep;
}

int main()
{
    int nbrproc,i,n;
    int boucle,choix,decalge,existe,Qt;
    int rep,db,fn,qs,rest,enreg_don=0;
    char nom_fich[30],N[12],qt[12];
    FILE *pntr;
    processus *bcp,*T;
    info res[maxim];
    code_proc cod[20];

    if(meth_affich==1)
    {
        decalge=38;
    }
    else
    {
        decalge=60;
    }

    titre();

    printf("\t\t\t\t       Salutation (^_^) !!\n\t\t       Voici un programme de gestion des processus \n\t\t         selon le type d'ordonnancement choisis\n\n");
    printf("   Ce programme a %ct%c cr%ce par ABOUABDELMAJID KHALIL : un %ctudiant dans une ecole marocaine des ingenieurs ",130,130,130,130);
    printf("  \n          si vous voulez me contacter : abouabdelmajidkhalil@gmail.com ");
    printf("\n\n\t           Appuyez sur n'importe quelle touche pour commencer ");
    getch();
    system("cls");
    rep=-1;

    do
    {
        if(rep==-1)
        {
            if(enreg_don==1)
            {
                system("cls");

            }
            titre();
            rep=menu_prin(enreg_don);
            if(rep==52)
            {
                printf("\n\n\t\tMerci pour avoir utilis%c ce programme (^_^) %c tr%cs bient%ct !!",130,133,138,147);
                getch();
            }
        }
        else
        {
            if(rep==49)
            {
                if(enreg_don==0)
                {
                    printf("\n\nDonnez le titre du fichier %c charger avec l'extension .TXT : ",133);
                    scanf("%s",nom_fich);

                    if(verif_bcp(nom_fich)==0)
                    {
                        rep=-1;
                        system("cls");
                    }
                    else
                    {
                        if(verif_occur_code(nom_fich)==0)
                        {
                            //supp_liste(bcp);
                            enreg_don=0;

                            rep=-1;
                            system("cls");
                        }
                        else
                        {
                            pntr=fopen(nom_fich,"rt");
                            bcp=enreg_bcp(pntr,&cod[0].cd);
                            fclose(pntr);

                            T=bcp;
                            trie_proc(T);
                            T=bcp;
                            supp_not(T);
                            T=bcp;
                            nbrproc=nbr_proc(T);

                            rep=-1;
                            enreg_don=1;
                            printf("Chargement des donn%ces r%cussi !! \n",130,130);
                            getch();
                        }
                    }
                }
                else
                {
                    printf("\nDes donn%ces sont d%cja charg%ces !! Voulez vous les %ccraser ? O/N : ",130,130,130,130);

                    do
                    {
                        rep=getch();
                    }
                    while(rep!=111&&rep!=110&&rep!=78&&rep!=79);

                    if(rep==111||rep==79)
                    {
                        supp_liste(bcp);
                        printf("\nSuppression des anciennes donn%ces r%cussi !!",130,130);

                        printf("\nDonnez le titre du nouveau fichier %c charger avec l'extension .TXT : ",133);
                        scanf("%s",nom_fich);

                        if(verif_bcp(nom_fich)==0)
                        {
                            rep=-1;
                            enreg_don=0;
                            system("cls");
                        }
                        else
                        {
                            if(verif_occur_code(nom_fich)==0)
                            {
                                //supp_liste(bcp);
                                enreg_don=0;

                                rep=-1;
                                system("cls");
                            }
                            else
                            {
                                pntr=fopen(nom_fich,"rt");
                                bcp=enreg_bcp(pntr,&cod[0].cd);
                                fclose(pntr);

                                T=bcp;
                                trie_proc(T);
                                T=bcp;
                                supp_not(T);
                                T=bcp;
                                nbrproc=nbr_proc(T);

                                rep=-1;
                                enreg_don=1;
                                printf("Chargement des donn%ces r%cussi !! \n",130,130);
                                getch();
                            }
                        }
                    }
                    else
                    {
                        printf("\nAucune t%cche n'a %ct%c effectu%ce\n",131,130,130,130);
                        getch();
                        rep=-1;
                    }
                }
            }
            else
            {
                if(rep==50)
                {
                    system("cls");
                    titre();
                    T=bcp;
                    afficher_proc(T,nbrproc,nom_fich);
                    printf("\n\nR : retourner au menu principal ");
                    do
                    {
                        rep=getch();
                    }
                    while(rep!=114&&rep!=82);

                    if(rep==114||rep==82)
                        rep=-1;
                }
                else
                {
                    if(rep==51)
                    {
                        system("cls");
                        rep=menu_ch_algo();

                        if(rep!=55)
                        {
                            system("cls");
                            titre();
                            switch (rep)
                            {
                            case 49:
                                title_fifo_1();
                                break;
                            case 50:
                                title_trq_1();
                                break;
                            case 51:
                                title_par_1();
                                break;
                            case 52:
                                title_fifo_2();
                                break;
                            case 53:
                                title_trq_2();
                                break;
                            case 54:
                                title_par_2();
                                break;
                            }
                            do
                            {
                                printf("\nDonnez le temps d'arr%ct :",136);
                                scanf("%s",N);
                            }
                            while(verif_nombre(N,1)==0);

                            n=atoi(N);

                            if(rep==50||rep==53)
                            {
                                do
                                {
                                    printf("\nDonnez le Quantum : ");
                                    scanf("%s",qt);
                                }
                                while(verif_nombre(qt,2)==0);
                            }

                            Qt=atoi(qt);

                            boucle=1;
                            T=bcp;

                            do
                            {
                                for(i=0; i<=n; i++)
                                {
                                    T->cmt[i].elu=0;
                                    T->cmt[i].pret=0;
                                    T->cmt[i].ent_sor=0;
                                    T->cmt[i].blq=0;
                                }

                                if(T->suiv!=NULL)
                                    T=T->suiv;
                                else
                                    boucle=0;
                            }
                            while(boucle==1);
                            qs=(n/decalge);
                            rest=n-(qs*decalge);
                            db=0;
                            fn=decalge;
                            do
                            {
                                if(qs!=0)
                                {
                                    system("cls");
                                    titre();

                                    switch (rep)
                                    {
                                    case 49:
                                        title_fifo_1();
                                        break;
                                    case 50:
                                        title_trq_1();
                                        break;
                                    case 51:
                                        title_par_1();
                                        break;
                                    case 52:
                                        title_fifo_2();
                                        break;
                                    case 53:
                                        title_trq_2();
                                        break;
                                    case 54:
                                        title_par_2();
                                        break;
                                    }

                                    T=bcp;
                                    afficher_proc(T,nbrproc,nom_fich);
                                    printf("\n\nLe temps d'arr%ct est : %d\n\n",136,n);
                                    if(rep==50||rep==53)
                                        printf("Le Quantum est : %d\n\n",Qt);

                                    T=bcp;
                                    for(i=0; i<nbrproc; i++)
                                    {
                                        switch (rep)
                                        {
                                        case 49:
                                            fifo_pro(T,fn,cod[i].cd,res);
                                            break;
                                        case 50:
                                            tourniquet_pro(T,fn,cod[i].cd,Qt,res);
                                            break;
                                        case 51:
                                            prio_avec_req(T,fn,cod[i].cd,res);
                                            break;
                                        case 52:
                                            fifo_pro_2(T,fn,cod[i].cd,res);
                                            break;
                                        case 53:
                                            tourniquet_pro_2(T,fn,cod[i].cd,Qt,res);
                                            break;
                                        case 54:
                                            prio_avec_req_2(T,fn,cod[i].cd,res);
                                            break;
                                        }

                                        switch (rep)
                                        {
                                        case 49:
                                            affich_res(res,fn,cod[i].cd,1,db);
                                            break;
                                        case 50:
                                            affich_res(res,fn,cod[i].cd,1,db);
                                            break;
                                        case 51:
                                            affich_res(res,fn,cod[i].cd,1,db);
                                            break;
                                        case 52:
                                            affich_res(res,fn,cod[i].cd,2,db);
                                            break;
                                        case 53:
                                            affich_res(res,fn,cod[i].cd,2,db);
                                            break;
                                        case 54:
                                            affich_res(res,fn,cod[i].cd,2,db);
                                            break;
                                        }
                                    }


                                    for(i=db; i<=fn; i++)/////////pour afficher les commentaires
                                    {
                                        T=bcp;
                                        boucle=1;
                                        existe=0;
                                        do
                                        {
                                            if(T->cmt[i].elu==1)
                                            {
                                                existe=1;
                                                break;
                                            }
                                            if(T->cmt[i].pret==1)
                                            {
                                                existe=1;
                                                break;
                                            }
                                            if(T->cmt[i].ent_sor==1)
                                            {
                                                existe=1;
                                                break;
                                            }
                                            if(T->cmt[i].blq==1)
                                            {
                                                existe=1;
                                                break;
                                            }

                                            if(T->suiv==NULL)
                                                boucle=0;
                                            else
                                                T=T->suiv;
                                        }
                                        while(boucle==1);

                                        if(existe==1)
                                        {
                                            printf("\nT=%d\t: ",i);
                                            T=bcp;
                                            boucle=1;
                                            do
                                            {
                                                if(T->cmt[i].elu==1)
                                                    printf("%s est %clu ",T->code,130);
                                                if(T->cmt[i].pret==1)
                                                    printf("%s est pr%ct ",T->code,136);
                                                if(T->cmt[i].ent_sor==1)
                                                    printf("%s utilise l'E/S ",T->code);
                                                if(T->cmt[i].blq==1)
                                                    printf("%s est bloqu%c ",T->code,130);

                                                if(T->suiv==NULL)
                                                    boucle=0;
                                                else
                                                    T=T->suiv;
                                            }
                                            while(boucle==1);
                                        }

                                    }

                                    if(rest==0)
                                    {
                                        if(qs-1==0)
                                        {
                                            if((n/decalge)>1)
                                            {
                                                printf("\n\n%c%c : Pr%cc%cdent\t\tR : retour au menu du choix des algorithmes\t",17,196,130,130);
                                                do
                                                {
                                                    choix=getch();
                                                }
                                                while(choix!=75&&choix!=114&&choix!=82);
                                            }
                                            else
                                            {
                                                if((n/decalge)==1&&rest==0)
                                                {
                                                    printf("\n\n\t\t          R : retour au menu du choix des algorithmes ");
                                                    do
                                                    {
                                                        choix=getch();
                                                    }
                                                    while(choix!=114&&choix!=82);
                                                }
                                                else
                                                {
                                                    if((n/decalge)==1&&rest==1)
                                                    {
                                                        printf("\n\n\t\t        R : retour au menu du choix des algorithmes\t         %c%c : Suivant",196,16);
                                                        do
                                                        {
                                                            choix=getch();
                                                        }
                                                        while(choix!=77&&choix!=114&&choix!=82);
                                                    }
                                                }

                                            }
                                        }
                                        else
                                        {
                                            if(qs==n/decalge)
                                            {
                                                printf("\n\n\t\t        R : retour au menu du choix des algorithmes\t         %c%c : Suivant",196,16);
                                                do
                                                {
                                                    choix=getch();
                                                }
                                                while(choix!=77&&choix!=114&&choix!=82);
                                            }
                                            else
                                            {
                                                printf("\n\n%c%c : Pr%cc%cdent\t          R : retour au menu du choix des algorithmes\t     %c%c : Suivant",17,196,130,130,196,16);
                                                do
                                                {
                                                    choix=getch();
                                                }
                                                while(choix!=77&&choix!=75&&choix!=114&&choix!=82);
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if(qs==n/decalge)
                                        {
                                            printf("\n\n\t\t        R : retour au menu du choix des algorithmes\t         %c%c : Suivant",196,16);
                                            do
                                            {
                                                choix=getch();
                                            }
                                            while(choix!=77&&choix!=114&&choix!=82);
                                        }
                                        else
                                        {
                                            printf("\n\n%c%c : Pr%cc%cdent\t           R : retour au menu du choix des algorithmes\t          %c%c : Suivant",17,196,130,130,196,16);
                                            do
                                            {
                                                choix=getch();
                                            }
                                            while(choix!=77&&choix!=75&&choix!=114&&choix!=82);
                                        }
                                    }

                                    if(choix==77)
                                    {
                                        db=fn;
                                        qs--;
                                        fn=fn+decalge;
                                    }
                                    else
                                    {
                                        if(choix==75)
                                        {
                                            fn=db;
                                            db=db-decalge;
                                            qs++;
                                        }
                                    }
                                }
                                else
                                {
                                    system("cls");
                                    titre();

                                    switch (rep)
                                    {
                                    case 49:
                                        title_fifo_1();
                                        break;
                                    case 50:
                                        title_trq_1();
                                        break;
                                    case 51:
                                        title_par_1();
                                        break;
                                    case 52:
                                        title_fifo_2();
                                        break;
                                    case 53:
                                        title_trq_2();
                                        break;
                                    case 54:
                                        title_par_2();
                                        break;
                                    }

                                    fn=n;
                                    T=bcp;
                                    afficher_proc(T,nbrproc,nom_fich);
                                    printf("\n\nLe temps d'arr%ct est : %d\n\n",136,n);
                                    if(rep==50||rep==53)
                                        printf("Le Quantum est : %d\n\n",Qt);

                                    for(i=0; i<nbrproc; i++)
                                    {
                                        switch (rep)
                                        {
                                        case 49:
                                            fifo_pro(T,fn,cod[i].cd,res);
                                            break;
                                        case 50:
                                            tourniquet_pro(T,fn,cod[i].cd,Qt,res);
                                            break;
                                        case 51:
                                            prio_avec_req(T,fn,cod[i].cd,res);
                                            break;
                                        case 52:
                                            fifo_pro_2(T,fn,cod[i].cd,res);
                                            break;
                                        case 53:
                                            tourniquet_pro_2(T,fn,cod[i].cd,Qt,res);
                                            break;
                                        case 54:
                                            prio_avec_req_2(T,fn,cod[i].cd,res);
                                            break;
                                        }

                                        switch (rep)
                                        {
                                        case 49:
                                            affich_res(res,fn,cod[i].cd,1,db);
                                            break;
                                        case 50:
                                            affich_res(res,fn,cod[i].cd,1,db);
                                            break;
                                        case 51:
                                            affich_res(res,fn,cod[i].cd,1,db);
                                            break;
                                        case 52:
                                            affich_res(res,fn,cod[i].cd,2,db);
                                            break;
                                        case 53:
                                            affich_res(res,fn,cod[i].cd,2,db);
                                            break;
                                        case 54:
                                            affich_res(res,fn,cod[i].cd,2,db);
                                            break;
                                        }
                                    }

                                    for(i=db; i<=fn; i++)/////////pour afficher les commentaires
                                    {
                                        T=bcp;
                                        boucle=1;
                                        existe=0;
                                        do
                                        {
                                            if(T->cmt[i].elu==1)
                                            {
                                                existe=1;
                                                break;
                                            }
                                            if(T->cmt[i].pret==1)
                                            {
                                                existe=1;
                                                break;
                                            }
                                            if(T->cmt[i].ent_sor==1)
                                            {
                                                existe=1;
                                                break;
                                            }
                                            if(T->cmt[i].blq==1)
                                            {
                                                existe=1;
                                                break;
                                            }

                                            if(T->suiv==NULL)
                                                boucle=0;
                                            else
                                                T=T->suiv;
                                        }
                                        while(boucle==1);

                                        if(existe==1)
                                        {
                                            printf("\nT=%d\t: ",i);
                                            T=bcp;
                                            boucle=1;
                                            do
                                            {
                                                if(T->cmt[i].elu==1)
                                                    printf("%s est %clu ",T->code,130);
                                                if(T->cmt[i].pret==1)
                                                    printf("%s est pr%ct ",T->code,136);
                                                if(T->cmt[i].ent_sor==1)
                                                    printf("%s utilise l'E/S ",T->code);
                                                if(T->cmt[i].blq==1)
                                                    printf("%s est bloqu%c ",T->code,130);

                                                if(T->suiv==NULL)
                                                    boucle=0;
                                                else
                                                    T=T->suiv;
                                            }
                                            while(boucle==1);
                                        }

                                    }

                                    if(n>decalge)
                                    {
                                        printf("\n\n%c%c : Pr%cc%cdent\t\t       R : retour au menu du choix des algorithmes\t",17,196,130,130);

                                        do
                                        {
                                            choix=getch();
                                        }
                                        while(choix!=75&&choix!=114&&choix!=82);

                                        if(choix==75)
                                        {
                                            fn=db;
                                            db=db-decalge;
                                            qs++;
                                        }
                                    }
                                    else
                                    {
                                        printf("\n\n\t\t         R : retour au menu du choix des algorithmes ");
                                        do
                                        {
                                            choix=getch();
                                        }
                                        while(choix!=114&&choix!=82);
                                    }
                                }
                            }
                            while(choix!=114&&choix!=82);
                            rep=51;
                            system("cls");

                        }
                        else
                        {
                            rep=-1;
                        }
                    }
                }
            }
        }
    }
    while(rep!=52);

    return 0;
}
