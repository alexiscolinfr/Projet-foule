#include "../lib/libgraphique.h"
#include "../lib/lib_foule.h"
#include <unistd.h>

#define UNITE 10    //côté d'une case en pixels
#define NB_CASES_X 80  // nb de cases en abscisse (et dans le tableau 'plateau')
#define NB_CASES_Y 60  // nb de cases en ordonnée (et dans le tableau 'plateau')
#define FICHIER_PLAN "../data/plan.txt"

/******************************************************************************/
/* Déclaration des structures et variables globales                           */
/******************************************************************************/

//contient des 1 et des 0 suivant qu'il y ait un mur ou non
int plateau[NB_CASES_X][NB_CASES_Y]={{0}};  


/******************************************************************************/
/* Déclaration de vos fonctions                                               */
/******************************************************************************/

void affichage_plan(Point depart, Point arrivee);
void affichage_case(Point p1, Couleur couleur);
void affichage_joueur(Point p1);
void affichage_menu();
int dx_joueur(Point depart, Point arrivee);
int dy_joueur(Point depart, Point arrivee);
void deplacement_joueur(int dx, int dy, Point depart, Point arrivee);

/******************************************************************************/
/* main                                                                       */
/******************************************************************************/
int main(void)
{

    ouvrir_fenetre(NB_CASES_X*UNITE,NB_CASES_Y*UNITE);
    charge_plan(FICHIER_PLAN, plateau);
    //a vous !

	int dx,dy;

	Point depart={0,0};
	Point arrivee={79,59};
	
	affichage_menu();
	
	affichage_plan(depart, arrivee);

	dx = dx_joueur(depart, arrivee);
	dy = dy_joueur(depart, arrivee);

	deplacement_joueur(dx, dy, depart, arrivee);
	
	// fin du programme
    attendre_clic();
    fermer_fenetre();
    return 0;
}

/******************************************************************************/
/*  Définitions des autres fonctions                                          */
/******************************************************************************/

void affichage_plan(Point depart, Point arrivee) 
{
	int x,y;	
	Point coin;
	
	for (y=0 ; y<=NB_CASES_Y ; y++)
	{
		for (x=0 ; x<=NB_CASES_X ; x++)
		{
			if (plateau[x][y]==1)
			{
				coin.x = x*UNITE;
				coin.y = y*UNITE;
				dessiner_rectangle(coin,UNITE,UNITE,bleu);

			}
			else if (plateau[x][y]==0)
			{
				coin.x = x*UNITE;
				coin.y = y*UNITE;
				dessiner_rectangle(coin,UNITE,UNITE,noir);
			}
		}
	}
	
	affichage_case(depart, rouge);
	affichage_case(arrivee, blanc);
	actualiser();
}




void affichage_case(Point p1, Couleur couleur)
{
	Point p2;
	p2.x=p1.x*UNITE;
	p2.y=p1.y*UNITE;
	dessiner_rectangle(p2,UNITE,UNITE,couleur);
}




void affichage_joueur(Point p1)
{
	Point p2;
	p2.x=p1.x*UNITE;
	p2.y=p1.y*UNITE;
	afficher_image("../data/joueur.bmp", p2);
	actualiser();
	attente(100);
}




void affichage_menu()
{
	Point menu={0,0};
	afficher_image("../data/menu.bmp", menu);
	actualiser();
	attendre_clic();
}




int dx_joueur(Point depart, Point arrivee) // Détermination de la direction de x
{
	int dx;
	
	if (depart.x < arrivee.x)
		dx=1;
	else if (depart.x > arrivee.x)
		dx=-1;
	else if (depart.x == arrivee.x)
		dx=0;

	return dx;
}




int dy_joueur(Point depart, Point arrivee) // Détermination de la direction de y
{
	int dy;

	if (depart.y < arrivee.y)
		dy=1;		
	else if (depart.y > arrivee.y)
		dy=-1;
	else if (depart.y == arrivee.y)
		dy=0;

	return dy;
}




void deplacement_joueur(int dx, int dy, Point depart, Point arrivee)
{
	Point j=depart;
	int cptr;
	cptr=0;

	// Stratégie de déplacement

	while (j.x != arrivee.x || j.y != arrivee.y) // Tant que le joueur n'est pas sur l'arrivée
	{

		if (j.x != arrivee.x && j.y != arrivee.y) // Déplacement vertical et horizontal
		{

			if (plateau[j.x+dx][j.y+dy]==0)
			{
				j.x +=dx;
				j.y +=dy;
			}
			else if (plateau[j.x+dx][j.y+dy]==1) // Lorsque l'on rencontre un mur
			{
				if (plateau[j.x+dx][j.y]==0)
				{
					j.x+=dx;
				}	
				else if (plateau[j.x][j.y+dy]==0)
				{
					j.y+=dy;
				}
				else // Pour contourner un mur
				{
					while (plateau[j.x+dx][j.y] != 0)
					{
						affichage_plan(depart, arrivee);
						j.y-=dy;
						affichage_joueur(j);
						cptr++;
					}
				}
			}
		}

		if (j.x == arrivee.x) // Déplacement vertical
		{
			if (plateau[j.x][j.y+dy] == 0) 
			{
				j.y +=dy;
			}
			
			else // Lorsque l'on rencontre un mur
			{
				while (plateau[j.x][j.y+dy] != 0) 
					{
						affichage_plan(depart, arrivee);
						j.x-=dx;
						affichage_joueur(j);
						cptr++;
					}
			}
		}
		else if (j.y == arrivee.y) // Déplacement horizontal
		{
			if (plateau[j.x+dx][j.y] == 0) 
			{
				j.x +=dx;
			}
			else // Lorsque l'on rencontre un mur
			{
				while (plateau[j.x+dx][j.y] != 0)
					{
						affichage_plan(depart, arrivee);
						j.y-=dy;
						affichage_joueur(j);
						cptr++;
					}
			}
		}

		affichage_plan(depart, arrivee);
		affichage_joueur(j);
		cptr++;
	}

	printf("Le joueur à fait %d déplacements\n", cptr);
}






