#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    int jour;
    int mois;
    int annee;
}Date_naissance;

typedef struct 
{
    char nom[10];
    char prenom[10];
    char CIN[10];
    char sexe[7];
    char categorie_maladie[20];
    int Numero_Telephone[10];
    char Ville[10];
    char Consultation[100];
    Date_naissance DN;
    Date_naissance Date_Visite;
}Patient;

typedef struct Node 
{
    Patient P;
    int Numero_Patient;
    struct Node *prev;
    struct Node *next;
}Node;

typedef struct List
{
    Node *First;
    Node *Last;
}List;

int est_vide(Node *head) // fonction de verification de la liste.
{
    int C;

    if (head == NULL)
    {
        C = 0;
    }
    else
    {
        C = 1;
    }

    return C;
}

void Afficher(Node *P) // Fonction d'affichage d'un patient.
{
    if (P == NULL)
    {
        printf("Aucun patient à afficher.\n");
        return;
    }

    printf("Patient numero : %d\n", P->Numero_Patient);
    printf("\n");
    printf("Nom : %s\n", P->P.nom);
    printf("Prenom : %s\n", P->P.prenom);
    printf("CIN : %s\n", P->P.CIN);
    printf("Sexe : %s\n", P->P.sexe);
    printf("Categorie Maladie : %s\n", P->P.categorie_maladie);
    printf("Date de Naissance : %02d/%02d/%04d\n", P->P.DN.jour, P->P.DN.mois, P->P.DN.annee);
    printf("Numero de Telephone : %d\n", P->P.Numero_Telephone);
    printf("Ville : %s\n", P->P.Ville);
    printf("Date de la visite : %02d/%02d/%04d\n", P->P.Date_Visite.jour, P->P.Date_Visite.mois, P->P.Date_Visite.annee);
    printf("Consultation : %s\n", P->P.Consultation);

    printf("\n");

}

Node *Creer_Liste_Patients() // fonction de creation d une liste.
{
    Node *head, *new = (Node*)malloc(sizeof(Node));
    new->next = NULL;
    new->prev = NULL;
    
    head = new;

    return head;
}

Node *Creer_Patient() //fonction de creation d un patient.
{
    Node *P = (Node*)malloc(sizeof(Node));
    if (P == NULL)
    {
        printf("Erreur d'allocation mémoire !\n");
        return NULL;
    }
    P->next = NULL;
    P->prev = NULL;

    strcpy(P->P.Consultation, "Aucune"); // on done une valeur par defaut a la consultation.

    printf("-----Ajout d un Patient-----\n");
    printf("Donner le nom : ");
    scanf("%s", &P->P.nom);
    printf("Donner le prenom : ");
    scanf("%s", &P->P.prenom);
    printf("Donner le CIN : ");
    scanf("%s", &P->P.CIN);
    printf("Donner le sexe : ");
    scanf("%s", &P->P.sexe);
    printf("Categorie Maladie : ");
    scanf("%s", &P->P.categorie_maladie);
    printf("Donner la date de naissance : \n");
    printf("Jour : ");
    scanf("%d", &P->P.DN.jour);
    printf("Mois : ");
    scanf("%d", &P->P.DN.mois);  
    printf("Annee : ");
    scanf("%d", &P->P.DN.annee);
    printf("Donner le numero de telephone : ");
    scanf("%d", &P->P.Numero_Telephone);
    printf("Donner la ville : ");
    scanf("%s", &P->P.Ville);

    printf("\n");
    
    printf("Donnerla date de la visite : \n");
    printf("Jour : ");
    scanf("%d", &P->P.Date_Visite.jour);
    printf("Mois : ");
    scanf("%d", &P->P.Date_Visite.mois);
    printf("Annee : ");
    scanf("%d", &P->P.Date_Visite.annee);


    printf("\n");

    // Open the file in append mode to add the patient data
    FILE *fptr = fopen("Patients.txt", "w");
    if (fptr == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier !\n");
        free(P);
        return NULL;
    }

    fprintf(fptr, "Nom: %s, Prenom: %s, CIN: %s, Sexe: %s, Categorie Maladie: %s, Date de Naissance: %02d/%02d/%04d, Telephone: %d, Ville: %s \n", P->P.nom, P->P.prenom, P->P.CIN, P->P.sexe, P->P.categorie_maladie, P->P.DN.jour, P->P.DN.mois, P->P.DN.annee, P->P.Numero_Telephone, P->P.Ville);

    fclose(fptr);

    printf("Patient ajoute avec succes et enregistre dans le fichier !\n");
    printf("\n");

    return P;
}   

Node *Ajout_Debut(Node *head) // fonction d ajout d un patient au debut de la liste.
{
    Node *new = Creer_Patient();
    Node *temp = head;
    int C;

    C = est_vide(head);

    if(C == 1)
    {
        new->next = temp;
        new->prev = NULL;
        temp->prev = new;
        head = new;
        new->Numero_Patient = 1;

        temp = new->next;
        while (temp != NULL)
        {
            temp->Numero_Patient++;
            temp = temp->next;
        }
    }
    else if(C == 0)
    {
        new->next = temp;
        new->prev = NULL;
        head = new;
        new->Numero_Patient = 1;
    }
    
    printf("NP : %d\n", new->Numero_Patient);

    return head;
}

Node *Ajout_Fin(Node *head) // fonction d ajout d un patient a la fin de la liste.
{
    Node *new = Creer_Patient();
    Node *temp = head;
    int C;

    C = est_vide(head);

    if(C == 1)
    {
        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = new;
        new->prev = temp;
        new->next = NULL;
        new->Numero_Patient = temp->Numero_Patient + 1;
    }
    else if(C == 0)
    {
        new->next = temp;
        new->prev = NULL;
        head = new;
        new->Numero_Patient = 1;
    }

    printf("NP : %d\n", new->Numero_Patient);

    return head;
}

Node *Ajout_Position(Node *head, int R_num_P) //fonction d ajout d un patient a une position donnee.
{
    Node *new = Creer_Patient();
    Node *temp = head;
    int C;

    C = est_vide(head);

    if(C == 1)
    {
        while(temp->next != NULL && temp->Numero_Patient != R_num_P)
        {
            temp=temp->next;
        }

        if(temp->Numero_Patient == R_num_P)
        {
            new->next = temp->next;
            new->prev = temp;
            temp->next->prev = new;
            temp->next = new;

            new->Numero_Patient = temp->Numero_Patient + 1;        

            while(temp != NULL)
            {
                temp->Numero_Patient++;
                temp = temp->next;
            }
        }
        else
        {
            printf("Le Patient n existe pas !\n");
        }
    }
    else if(C == 0)
    {
        printf("La liste est vide !\nPatient ajouter au debut. \n");
        head = Ajout_Debut(head);
    }

    printf("NP : %d\n", new->Numero_Patient);

    return head;
}

Node *Suppression_Debut(Node *head) // fonction de suppression d un patient au debut de la liste.
{
    Node *temp = head;
    int C;

    C = est_vide(head);

    if(C == 1)
    {
        head = temp->next;
        head->prev = NULL;
        free(temp);

        temp = head;
        while(temp != NULL)
        {
            temp->Numero_Patient--;
            temp = temp->next;
        }

        printf("Patient supprime avec succes !\n");
        printf("\n");
    }
    else if(C == 0)
    {
        printf("La liste est vide !\n");
        printf("\n");
    }

    return head;
}

Node *Suppression_Fin(Node *head) //fonction de suppression d un patient a la fin de la liste.
{
    Node *temp = head;
    int C;

    C = est_vide(head);

    if(C == 1)
    {
        while(temp->next !=NULL)
        {
            temp = temp->next;
        }
        temp->prev->next = NULL;
        free(temp);

        printf("Patient supprime avec succes !\n");
        printf("\n");
    }
    else if(C == 0)
    {
        printf("La liste est vide !\n");
        printf("\n");
    }

    return head;
}

Node *Suppression_Position(Node *head, int R_num_P) // fonction de suppression d un patient a une position donnee.
{
    Node *temp = head;
    int C;

    C = est_vide(head);

    if(C == 1)
    {
        while(temp->next !=NULL && temp->Numero_Patient != R_num_P)
        {
            temp = temp->next;
        }

        if(temp->Numero_Patient == R_num_P)
        {
            temp = temp->next;
            
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            free(temp);

            printf("Patient supprime avec succes !\n");
            printf("\n");
        }
        else
        {
            printf("Le Patient n existe pas !\n");
        }
    }
    else if(C == 0)
    {
        printf("La liste est vide !\n");
        printf("\n");
    }

    return head;
}

void Recherche_Nom_Prenom(Node *head, char R_nom[], char R_prenom[]) // fonction de recherche par nom et prenom.
{
    Node *temp = head;
    int C;

    C = est_vide(head);
    
    if(C == 1)
    {
        while(temp != NULL)
        {
            if(strcmp(temp->P.nom, R_nom) == 0 && strcmp(temp->P.prenom, R_prenom) == 0)
            {
                break;
            }
            temp = temp->next;
        }

        if(strcmp(temp->P.nom, R_nom) == 0 && strcmp(temp->P.prenom, R_prenom) == 0)
        {
            Afficher(temp);
        }
        else
        {
            printf("Patient non trouve ! \n");
            printf("\n");
        }
    }
    else if(C == 0)
    {
        printf("La liste est vide !\n");
        printf("\n");
    }

}

void Recherche_Date_Naissance(Node *head, int R_jour, int R_mois, int R_annee) // fonction de recherche par date de naissance.
{
    Node *temp = head;
    int C;

    C = est_vide(head);

    if(C == 1)
    {
        while(temp != NULL)
        {
            if(temp->P.DN.jour == R_jour && temp->P.DN.mois == R_mois && temp->P.DN.annee == R_annee)
            {
                break;
            }
            temp = temp->next;
        }

        if(temp->P.DN.jour == R_jour && temp->P.DN.mois == R_mois && temp->P.DN.annee == R_annee)
        {
            Afficher(temp);
        }
        else
        {
            printf("Patient non trouve ! \n");
            printf("\n");
        }
    }
    else if(C == 0)
    {
        printf("La liste est vide !\n");
        printf("\n");
    }

}

void Recherche_Num_Patient(Node *head, int R_num_P) // fonction de recherche par numero de patient.
{
    Node *temp = head;
    int C;

    C = est_vide(head);

    if(C == 1)
    {
        while(temp != NULL)
        {
            if(temp->Numero_Patient == R_num_P)
            {
                break;
            }
            temp = temp->next;
        }

        if(temp->Numero_Patient == R_num_P)
        {
            Afficher(temp);
        }
        else
        {
            printf("Patient non trouve ! \n");
            printf("\n");
        }
    }
    else if(C == 0)
    {
        printf("La liste est vide !\n");
        printf("\n");
    }

}

void Afficher_Patients(Node *head) // fonction d affichage de touts les patients dans la liste.
{
    Node *temp = head;
    int C;

    C = est_vide(head);

    if(C == 1)
    {
        while(temp != NULL)
        {
            Afficher(temp);
            temp = temp->next;
        }
    }
    else if(C == 0)
    {
        printf("La liste est vide !\n");
        printf("\n");
    }

}

void Afficher_Patients_Categorie(Node *head, char R_categorie[]) // fonction d affichage des patients par categorie madical.
{
    Node *temp = head;
    int C;

    C = est_vide(head);

    if(C == 1)
    {
        while(temp != NULL)
        {
            if(strcmp(temp->P.categorie_maladie, R_categorie) == 0)
            {
                Afficher(temp);
            }
            temp = temp->next;
        } 
    }
    else if(C == 0)
    {
        printf("La liste est vide !\n");
        printf("\n");
    }
}

Node *Modification_Patient(Node *head, int R_num_P) // fonction de modification d un patient.
{
    Node *temp = head;
    int C;

    C = est_vide(head);

    printf("Attention ! Vous aurez l acces de juste modifier le Numero de Telephone et la Ville de patient !\n");
    printf("\n");

    if(C == 1)
    {
        while(temp != NULL)
        {
            if(temp->Numero_Patient == R_num_P)
            {
                break;
            }
            temp = temp->next;
        }

        if(temp->Numero_Patient == R_num_P)
        {
            printf("Donner le Numero de Telephone : ");
            scanf("%d", &temp->P.Numero_Telephone);
            printf("Donner la Ville : ");
            scanf("%s", &temp->P.Ville);

            printf("\n");
            
            printf("Patient modifier avec succes !\n");
            printf("\n");
        }
        else
        {
            printf("Patient non trouver ! \n");
            printf("\n");
        }
    }
    else if(C == 0)
    {
        printf("La liste est Vide !\n");
        printf("\n");
    }

    return head;
}

Node *Trie_par_Nom(Node *head) // fonction de tri des Patient par ordre alphabetique des noms.
{
    Node *temp1, *temp2;
    int C;

    C = est_vide(head);

    if (C == 1)
    {
        for (temp1 = head; temp1->next != NULL; temp1 = temp1->next)
        {
            for (temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next)
            {
                if (strcmp(temp1->P.nom, temp2->P.nom) > 0)
                {
                    Patient temp_P = temp1->P;
                    temp1->P = temp2->P;
                    temp2->P = temp_P;
                }
            }
        }
    }
    else if(C == 0)
    {
        printf("La liste est vide !\n");
    }

    printf("Tri par Nom effectue avec succes !\n");
    printf("\n");

    return head;
}

Node *Trie_par_Age(Node *head) // fonction de tri des patients par age.
{
    Node *temp1, *temp2;
    int C;

    C = est_vide(head);

    if (C == 1)
    {
        for (temp1 = head; temp1->next != NULL; temp1 = temp1->next)
        {
            for (temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next)
            {
                if (temp1->P.DN.annee > temp2->P.DN.annee)
                {
                    Patient temp_P = temp1->P;
                    temp1->P = temp2->P;
                    temp2->P = temp_P;
                }
                else if(temp1->P.DN.annee == temp2->P.DN.annee)
                {
                    if (temp1->P.DN.mois > temp2->P.DN.mois)
                    {
                        Patient temp_P = temp1->P;
                        temp1->P = temp2->P;
                        temp2->P = temp_P;
                    }
                    else if (temp1->P.DN.mois == temp2->P.DN.mois)
                    {
                        if (temp1->P.DN.jour > temp2->P.DN.jour)
                        {
                            Patient temp_P = temp1->P;
                            temp1->P = temp2->P;
                            temp2->P = temp_P;
                        }
                    }
                }
            }
        }
    }
    else if(C == 0)
    {
        printf("La liste est vide !\n");
    }

    printf("Tri par Age effectue avec succes !\n");
    printf("\n");

    return head;
}

Node *Trie_Date_Visite(Node *head) // fonction de tri des patients par date de visite.
{
    Node *temp1, *temp2;
    int C;

    C = est_vide(head);

    if (C == 1)
    {
        for (temp1 = head; temp1->next != NULL; temp1 = temp1->next)
        {
            for (temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next)
            {
                if (temp1->P.Date_Visite.annee > temp2->P.Date_Visite.annee)
                {
                    Patient temp_P = temp1->P;
                    temp1->P = temp2->P;
                    temp2->P = temp_P;
                }
                else if(temp1->P.Date_Visite.annee == temp2->P.Date_Visite.annee)
                {
                    if (temp1->P.Date_Visite.mois > temp2->P.Date_Visite.mois)
                    {
                        Patient temp_P = temp1->P;
                        temp1->P = temp2->P;
                        temp2->P = temp_P;
                    }
                    else if (temp1->P.Date_Visite.mois == temp2->P.Date_Visite.mois)
                    {
                        if (temp1->P.Date_Visite.jour > temp2->P.Date_Visite.jour)
                        {
                            Patient temp_P = temp1->P;
                            temp1->P = temp2->P;
                            temp2->P = temp_P;
                        }
                    }
                }
            }
        }
    }
    else if(C == 0)
    {
        printf("La liste est vide !\n");
    }

    printf("Tri par Date de Visite effectue avec succes !\n");
    printf("\n");

    return head;
}

Node *Creer_Consultation(Node *head, int R_num_P) // fonction de creation d une consultation.
{
    Node *temp = head;
    int C;

    C = est_vide(head);

    if(C == 1)
    {
        while(temp != NULL)
        {
            if(temp->Numero_Patient == R_num_P)
            {
                break;
            }
            temp = temp->next;
        }

        if(temp->Numero_Patient == R_num_P)
        {
            printf("Donner la consultation : ");
            scanf("%s", &temp->P.Consultation);
        }
        else
        {
            printf("Patient non trouve !\n");
        }
    }
    else if(C == 0)
    {
        printf("La liste est vide !\n");
    }

    return head;
}

void Afficher_Consultation(Node *head, int R_num_P) // fonction d affichage d une consultation.
{
    Node *temp = head;
    int C;

    C = est_vide(head);

    if(C == 1)
    {
        while(temp != NULL)
        {
            if(temp->Numero_Patient == R_num_P)
            {
                break;
            }
            temp = temp->next;
        }

        if(temp->Numero_Patient == R_num_P)
        {
            if(strcmp(temp->P.Consultation, "Aucune") == 0)
            {
                printf("Aucune consultation !\n");
            }
            else
            {
                printf("Consultation : %s\n", temp->P.Consultation);
            }
        }
        else
        {
            printf("Patient non trouve !\n");
        }
    }
    else if(C == 0)
    {
        printf("La liste est vide !\n");
    }
}

void main()
{
    FILE *fptr;
    fptr = fopen("Patients.txt","w"); //cration d un fichier.txt.
    fclose(fptr); //fermeture du fichier.

    List *L = (List*)malloc(sizeof(List));
    Node *head = Creer_Liste_Patients();
    int choice, C, R_num_P;

    L->First = head;
    L->Last = head;

    do
    {
        printf("\n");

        printf("-----Menu Principal-----\n"); // menu principal.
        printf("1->Gestion des Patients. \n");
        printf("2->Quitter. \n");
        printf("Votre choix : ");
        scanf("%d",&choice);

        printf("\n");

        switch(choice)
        {
            case 1:
            {
                do
                {
                    printf("-----Gestion des Patients-----\n"); // menu de gestion des patients.
                    printf("1->Ajout d un Patient. \n");
                    printf("2->Suppression d un Patient. \n");
                    printf("3->Recherche d un patient. \n");
                    printf("4->Afficher les Patients. \n");
                    printf("5->Gerer les categories de patients. \n");
                    printf("6->Modification d un Patient. \n");
                    printf("7->Option de tri personnalisees. \n");
                    printf("8->Consultation Medicale d un Patient. \n");
                    printf("9->MENU principal. \n");
                    printf("Votre choix : ");
                    scanf("%d",&choice);
                    
                    printf("\n");

                    switch(choice)
                    {
                        case 1: // Ajout.
                        {
                            printf("-----Ajout d un Patient-----\n"); // menu d ajout d un patient.
                            printf("1.Ajout au debut. \n"); 
                            printf("2.Ajout a la fin. \n");
                            printf("3.Ajout apres un patient specifique. \n");
                            printf("Votre choix : ");
                            scanf("%d",&choice);

                            printf("\n");

                            switch(choice)
                            {
                                case 1: // ajout au debut de la liste.
                                {
                                    head = Ajout_Debut(head);
                                }
                                break;

                                case 2: // ajout a la fin de la liste.
                                {
                                    head = Ajout_Fin(head);
                                }
                                break;
                            
                                case 3: // ajout a une position donnee.
                                {
                                    printf("Donner le numero du patient : ");
                                    scanf("%d", &R_num_P);
                                    
                                    printf("\n");

                                    head = Ajout_Position(head, R_num_P);
                                }
                                break;
                        
                                default:
                                    printf("Choix invalide !\n");
                            }
                        }
                        break;

                        case 2: //Suppression. 
                            do
                            {
                                printf("-----Suppression d un Patient-----\n"); //menu de suppression d un patient.
                                printf("1.Suppression au debut. \n");
                                printf("2.Suppression a la fin. \n");
                                printf("3.Suppression apres un patient specifique. \n");
                                printf("4->Retour. \n");
                                printf("Votre choix : ");
                                scanf("%d",&choice);

                                printf("\n");

                                switch(choice)
                                {
                                    case 1: // suppression au debut de la liste.
                                    {
                                        head = Suppression_Debut(head);
                                    }
                                    break;
                                    
                                    case 2: // suppression a la fin de la liste.
                                    {
                                        head = Suppression_Fin(head);
                                    }
                                    break;

                                    case 3: // suppression a une position donnee.
                                    {
                                        printf("Donner le numero du patient : ");
                                        scanf("%d", &R_num_P);

                                        printf("\n");

                                        head = Suppression_Position(head, R_num_P);
                                    }
                                    break;

                                    case 4: // Retour.
                                    {
                                    }
                                    break;

                                    default:
                                        printf("Choix invalide !\n");

                                }
                            }while(choice != 4);
                        break;

                        case 3: // Recherche. 
                            do 
                            {
                                printf("-----Recherche d un Patient-----\n"); // menu de recherche d un patient.
                                printf("1.Par nom et prenom. \n");
                                printf("2.Par date de naissance. \n");
                                printf("3.Par numero de Patient. \n");
                                printf("4.Retour. \n");
                                printf("Votre choix : ");
                                scanf("%d",&choice);
                            
                                printf("\n");

                                switch(choice)
                                {
                                    case 1: // recherche par nom et prenom.
                                    {
                                        char R_nom[10], R_prenom[10];

                                        printf("Donner le nom : ");
                                        scanf("%s", R_nom);
                                        printf("Donner le prenom : ");
                                        scanf("%s", R_prenom);

                                        printf("\n");

                                        Recherche_Nom_Prenom(head, R_nom, R_prenom);
                                    }
                                    break;

                                    case 2: // recherche par date de naissance.
                                    {
                                        int R_jour, R_mois, R_annee;
                                        
                                        printf("Donner la date de naissance : \n");
                                        printf("Jour : ");
                                        scanf("%d", &R_jour);
                                        printf("Mois : ");
                                        scanf("%d", &R_mois);
                                        printf("Annee : ");
                                        scanf("%d", &R_annee);

                                        printf("\n");

                                        Recherche_Date_Naissance(head, R_jour, R_mois, R_annee);
                                    }
                                    break;

                                    case 3: //recherche par numero de patient.
                                    {
                                        printf("Donner le numero de patient : ");
                                        scanf("%d", &R_num_P);

                                        printf("\n");

                                        Recherche_Num_Patient(head, R_num_P);
                                    }
                                    break;

                                    case 4: // Retour.
                                    {
                                    }
                                    break;

                                    default:
                                        printf("Choix invalide !\n");
                                }
                            }while(choice != 4);
                        break;

                        case 4: // Affichage. 
                        {
                            printf("-----Afficher les Patients-----\n"); // affichage de touts les patients dans la liste.

                            printf("\n");

                            Afficher_Patients(head);
                        }
                        break;    

                        case 5: // Affichage des patients par categorie medicale.
                            do
                            {
                                printf("-----Gategoriser les Patients-----\n"); // menu de categorie de patients.
                                printf("1.Pediatrie. \n");
                                printf("2.Cardiologie. \n");
                                printf("3.Dermatologie. \n");
                                printf("4.Retour. \n");
                                printf("Votre choix : ");
                                scanf("%d", &choice);

                                printf("\n");

                                switch(choice)
                                {
                                    case 1: // Pediatrie.
                                    {
                                        char R_categorie[] = "Pediatrie";

                                        Afficher_Patients_Categorie(head, R_categorie);
                                    }
                                    break;

                                    case 2: // Cardiologie.
                                    {
                                        char R_categorie[] = "Cardiologie";

                                        Afficher_Patients_Categorie(head, R_categorie);
                                    }
                                    break;

                                    case 3: // Dermatologie.
                                    {
                                        char R_categorie[] = "Dermatologie";

                                        Afficher_Patients_Categorie(head, R_categorie);
                                    }
                                    break;

                                    case 4: // Retour.
                                    {
                                    }
                                    break;

                                    default:
                                        printf("Choix invalide !\n");
                                }
                            }while(choice != 4);
                        break;

                        case 6: // Modification d un patient.
                        {
                            printf("-----Modifier un Patient-----\n");
                            printf("Donner le numero du Patient : ");
                            scanf("%d", &R_num_P);

                            printf("\n");

                            head = Modification_Patient(head, R_num_P);
                        }
                        break;

                        case 7: // Tri des patients.
                            do
                            {
                                printf("-----Tri des Patients-----\n"); // manu de tri des Paatients.
                                printf("1.Tri par Nom. \n");
                                printf("2.Tri par Age. \n");
                                printf("3.Tri par Date de visite. \n");
                                printf("4.Retour. \n");
                                printf("Votre Choix : ");
                                scanf("%d", &choice);

                                printf("\n");

                                switch(choice)
                                {
                                    case 1: //Tri par Nom.
                                    {
                                        head = Trie_par_Nom(head);
                                    }
                                    break;

                                    case 2: //Tri par Age.
                                    {
                                        head = Trie_par_Age(head);
                                    }
                                    break;

                                    case 3: //Tri par Date de vidite.
                                    {
                                        head = Trie_Date_Visite(head);
                                    }
                                    break;

                                    case 4: // Retour.
                                    {
                                    }
                                    break;

                                    default:
                                        printf("Choix invalide !\n");
                                }
                            } while (choice != 4);
                        break;

                        case 8: // Consultation d un Patient.
                        {
                            do
                            {
                                printf("-----Consultation Medical-----\n"); // menu de consultaion medicale.
                                printf("1.Ajouter une consultation. \n");
                                printf("2.Afficher une consultation. \n");
                                printf("3.Retour. \n");
                                printf("Votre choix : ");
                                scanf("%d", &choice);

                                printf("\n");

                                switch(choice)
                                {
                                    case 1: // Ajout d une consultation.
                                    {
                                        printf("Donner le numero du Patient : ");
                                        scanf("%d", &R_num_P);

                                        printf("\n");

                                        head = Creer_Consultation(head, R_num_P);
                                    }
                                    break;

                                    case 2: // Affichage d une consultation.
                                    {
                                        printf("Donner le numero du Patient : ");
                                        scanf("%d", &R_num_P);

                                        printf("\n");

                                        Afficher_Consultation(head, R_num_P);
                                    }
                                    break;

                                    case 3: // Retour.
                                    {
                                    }
                                    break;

                                    default:
                                        printf("Choix invalide !\n");
                                }
                            }while(choice != 3);
                        }
                        break;

                        default:
                            printf("Choix invalide !\n");
                    }
                }while(choice != 9);
            }
            break;

            case 2: // Quitter.
            {
                printf("Merci d avoir utilise notre programme !\n");
                printf("\n");
            }
            break;

            default:
                printf("Choix invalide !\n");
                printf("\n");
            
        }
    }while(choice != 2);
}