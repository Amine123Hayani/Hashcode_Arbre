// Projet Haschode_Arbre 
// Nom : M'hammed El Mrabet   Grp : B

#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <string.h>
using namespace std;

const int m=30;

typedef struct Liste
{
	string mot;
	string trad;
	Liste *suive;
}Liste;

typedef struct Liste* Pliste;

typedef struct
{
	int NbElem;
	Pliste Pl;
	
}ThashListe;

typedef struct Arbre
{
	string mot;
	string trad;
	Arbre *FG,*FD;
}Arbre;

typedef struct Arbre* PArbre;

typedef struct
{
	int NbElem;
	PArbre Plarbre;
}ThashArbre;


ThashListe Thash1[m];
ThashArbre Thash2[m];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*************************************************************** FONCTION HASHCODE *************************************************************************

int Fonc_Hashcode(string Ident,int m)
{
	int i,Cp,L;
	L=Ident.length();
	Cp=0;
	for(i=0;i<L;i++)
	{
		Cp = Cp + (Ident[i] - 65);
	}
	
	return Cp%m;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*************************************************************** PROCEDURE EXTRAIRE ************************************************************************


void extraire(string ligne,string &mot,string &trad)
{
	char c;
	int i=0;
	mot.clear();
	trad.clear(); 
		while(ligne[i]!='#')
		{
			c = ligne[i];
			mot.push_back(c) ;
			i++;
		}
		for(int j=i+1;j<ligne.length();j++)
		{
				c= ligne[j];
				trad.push_back(c);
		}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*************************************************************** Procedure InsererThash1 *******************************************************************

void InsererThash1(ThashListe Thash1[m],string mot,string trad,int m){
	
	int indice;
    bool trouve;
	Pliste P,Pred;
	indice=Fonc_Hashcode(mot,m);
	Pliste Q = new Liste;
	Q->mot=mot ; Q->trad=trad; Q->suive=NULL; 
	
	if(Thash1[indice].Pl==NULL)
	{
		Thash1[indice].Pl=Q;
		
	}
	else
	{
		P=Thash1[indice].Pl;
		if(mot< P->mot)
		{
			Q->suive=P;			
			Thash1[indice].Pl=Q;
		}
		else
		{
			trouve=false; Pred=P; P=P->suive;
			while(P!=NULL && trouve==false)
			{
				if(mot< P->mot)
				{
					trouve=true;	
					
				}
				else
				{
					Pred=Pred->suive;
					P=P->suive;
				}				
			}
				Pred->suive=Q;
				Q->suive=P;
			
		}
	}
	Thash1[indice].NbElem = Thash1[indice].NbElem+1;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*************************************************************** Procedure Trans1 **************************************************************************


void Trans1(string E,ThashListe Thash1[m],int m)
{
	string mot,trad,Ligne;
	int i;
	for(i=0;i<m;i++)
	{
		Thash1[i].NbElem = 0;
		Thash1[i].Pl = NULL;
	}
	ifstream file("mot_trad.txt", ios::in); 
	if(file)
	{
		while (getline(file,Ligne))
     	{
     		
     		extraire(Ligne,mot,trad);
			InsererThash1(Thash1,mot,trad,m);
     	}
		file.close();
	}
	else
	{
		cerr<<"File Erreur !!!!";
	}
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*************************************************************** Procedure SuppElem Thash1 ****************************************************************

void Supp_Mot_Thash1(ThashListe Thash1[m],string Elem,int m)
{
	int indice;
	Pliste P,Pred;
	bool arret;
	
	cout<<"Entrer le mot a supprimer Thash1 :  ";
	cin>>Elem;
	
	indice=Fonc_Hashcode(Elem,m);
	P=Thash1[indice].Pl;
	if(P==NULL)
	{		}
	else if(P->mot==Elem)
	{
		Thash1[indice].Pl=P->suive;
		free(P);
		Thash1[indice].NbElem = Thash1[indice].NbElem-1;
	}
	else
	{
		Pred=P; P=P->suive; arret=false;
		while(P!=NULL && arret==false)
		{
			if(P->mot==Elem)
			{
				arret=true;
				Pred->suive=P->suive;
				free(P);
				Thash1[indice].NbElem = Thash1[indice].NbElem-1;
			}
			else
			{
				Pred=Pred->suive;
				P=P->suive;
			}
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*************************************************************** Procedure InsererThash2 *******************************************************************

void InsererThash2(PArbre &Racine,string mot,string trad)
{
	
	if(Racine==NULL)
	{
		Racine = new Arbre;
		Racine->mot=mot; Racine->trad=trad;
		Racine->FG=NULL; Racine->FD=NULL;
	}
	else
	{
		if(mot<Racine->mot)
		{
			InsererThash2(Racine->FG,mot,trad);			
		}
		else
		{
			InsererThash2(Racine->FD,mot,trad);			
		}
	}  
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*************************************************************** Procedure Trans2 **************************************************************************


void Trans2(ThashListe Thash1[m] , ThashArbre Thash2[m] , int m)
{
	Pliste P;
	
	for(int i=0;i<m;i++)
	{
		Thash2[i].NbElem = 0;
		Thash2[i].Plarbre = NULL;
	}
	for(int i=0;i<m;i++)
	{
		P=Thash1[i].Pl;
		
		while(P!=NULL)
		{
			InsererThash2(Thash2[i].Plarbre,P->mot,P->trad);
			Thash2[i].NbElem = Thash2[i].NbElem + 1;			
			P=P->suive;
		}
	} 
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*************************************************************** Procedure add_Mot_thash2 ******************************************************************


void add_mot_thash2(ThashArbre Thash2[m],string mot , string trad,int m)
{
	int indice;
	PArbre P;
	cout<<"Entrer la nouvelle mot a ajouter au table thash2 :  ";
	cin>>mot;
	cout<<"Entrer la traduction du mot a ajouter :  ";
	cin>>trad;
	
	indice=Fonc_Hashcode(mot,m);
	InsererThash2(Thash2[indice].Plarbre,mot,trad);
	
	cout<<"Le mot et sa tradiction est bien ajouter a la table Thash2 a la case :  "<<indice<<endl;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*************************************************************** Procedure Supp Noeud **********************************************************************


void SuppNoeud(PArbre &Noeud)
{
	PArbre P,Q;
	P=Noeud;
	if(Noeud->FD==NULL)
	{
		Noeud=Noeud->FG;
	}
	else
	{
		Q=Noeud->FD;
		while(Q->FG!=NULL)
		{
			Q=Q->FG;
		}
		Q->FG=P->FG;
		Noeud=Noeud->FD;
	}
	free(P);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*************************************************************** Procedure Supp Elem ***********************************************************************

void Supp_Elem(PArbre &Racine,string mot)
{
	if(Racine!=NULL)
	{
		if(Racine->mot==mot)
		{
			SuppNoeud(Racine);
		}
		else if(mot<Racine->mot)
		{
			Supp_Elem(Racine->FG,mot);
		}
		else
		{
			Supp_Elem(Racine->FD,mot);
		}
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//****************************************************************** Procedure SuppMot Thash2 **************************************************************

void supp_Mot_thash2(ThashArbre Thash2[m],string mot,int m)
{
	int indice;
	cout<<"Entrer le mot a supprimer de Thash2 :  ";
	cin>>mot;
	indice=Fonc_Hashcode(mot,m);
	Supp_Elem(Thash2[indice].Plarbre,mot);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*************************************************************** Procedure Aficher NbElem Thash1 **********************************************************


void Afficher_NbElem_Thash1(ThashListe Thash1[m],int m)
{
	int i;
	cout<<"***************Thach1 *******************"<<endl;
	cout<<"De 0 a 14:"<<endl;
	for(i=0;i<15;i++)
	{
		cout << Thash1[i].NbElem << " , ";
	}
	cout<<endl;
	cout<<"De 14 a 29:"<<endl;
	for(i=15;i<m;i++)
	{
		cout << Thash1[i].NbElem << " , ";
	}
	cout<<endl;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*************************************************************** Procedure Afficher Contenue Thash1 ********************************************************


void Afficher_Contenu_Thash1(ThashListe Thash1[m],int m)
{
	string mot,trad;
	Pliste P;
	int Nb;
	int i;
	cout<<"Entrer le nombre de la case a afficher dans la table Thash1 : ";
	cin>>i;
	P=Thash1[i].Pl;
	Nb=Thash1[i].NbElem;	
	for(i=0;i<Nb;i++)
	{
		cout<<"Le mot :"<<P->mot<<"			La traduction :"<<P->trad<<endl;
		P=P->suive;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*************************************************************** Procedure Afficher Nbelem Thash1 **********************************************************

void Afficher_NbElem_Thash2(ThashArbre Thash2[m],int m)
{
	cout<<"***************Thach2 Arbre****************"<<endl;
	cout<<"De 0 a 14:"<<endl;
	for(int i=0;i<15;i++)
	{
		cout << Thash2[i].NbElem << " , ";
	}
	cout<<endl;
	cout<<"De 14 a 29:"<<endl;
	for(int i=15;i<30;i++)
	{
		cout << Thash2[i].NbElem << " , ";
	}
	cout<<endl;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*************************************************************** Procedure Aficher Centenu Thash2 **********************************************************


void Parcour_infixe(PArbre P)
{
	if(P==NULL)
	{		
		
	}
	else 
	{
		Parcour_infixe(P->FG);		
		cout<<"Le mot :"<<P->mot<<"			La traduction :"<<P->trad<<endl;
		Parcour_infixe(P->FD);
	}
}

void Afficher_Contenu_Thash2(ThashArbre Thash2[m],int m)
{
	PArbre P;
	int i;
	cout<<"Entrer le nombre de la case a afficher dans la table Thash2 : ";
	cin>>i;
	P=Thash2[i].Plarbre;
		
	Parcour_infixe(Thash2[i].Plarbre);
			
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*************************************************************** Procedure Menu ****************************************************************************

void Menu()
{
	cout<<"////////////////////////////////////////// Menu Pricipale //////////////////////////////////////////"<<endl<<endl;
	cout<<" 1- Afficher les nombres d'elements associe a chaque THash1[i]"<<endl;
	cout<<" 2- Afficher les nombres d'elements associe a chaque THash2[i]  "<<endl;
	cout<<" 3- Afficher le contenu de la liste associee a THash1[i]  "<<endl;
	cout<<" 4- Afficher le contenu de l'arbre associe a THash2[i], avec saisie de i  //(Parcours infixe de l'arbre)"<<endl;
	cout<<" 5- Supprimer un element dans THash1  "<<endl;
	cout<<" 6- Supprimer un element dans THash2  "<<endl;
	cout<<" 7- Ajouter un element dans THash2  "<<endl;
	cout<<" 8- QUITTER  "<<endl;
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*************************************************************** Menu Prancipale **************************************************************************

int main() 
{
	int choix,i;
	string E,Elem,mot,trad;
	Trans1(E,Thash1,m);
	Trans2(Thash1,Thash2,m);
	do {
	    Menu();		
		cout<<"Donner choix:"<<endl;
		cin>>choix;
		switch(choix)
		{
			case 1: Afficher_NbElem_Thash1(Thash1,m);
			break;
			case 2: Afficher_NbElem_Thash2(Thash2,m);
			break;
			case 3: Afficher_Contenu_Thash1(Thash1,m);
			break;
			case 4: Afficher_Contenu_Thash2(Thash2,m);				
			break;
			case 5: Supp_Mot_Thash1(Thash1,Elem,m);
			break;
			case 6: supp_Mot_thash2(Thash2,mot,m);
			break;
			case 7: add_mot_thash2(Thash2,mot,trad,m);
			break;
			default: cout<<"Fin du programme";
			break;
		}
	}while(choix!=8);	
	
	return 0;
}
