#include "path_finding.h"

typedef std::map< std::pair<int, int>, noeud> l_noeud;

PathFinding::PathFinding() {

}

void PathFinding::findRoad(MyMap* map, sf::RenderWindow* window, const int start_x, const int start_y, const int end_x, const int end_y)
{
	arrivee.x = end_x;
	arrivee.y = end_y;

	depart.parent.first = start_x;
	depart.parent.second = start_y;

	std::pair <int, int> courant;

	/* déroulement de l'algo A* */

	courant.first = start_x;
	courant.second = start_y;
	// ajout de courant dans la liste ouverte

	liste_ouverte[courant] = depart;
	ajouter_liste_fermee(courant);
	ajouter_cases_adjacentes(courant, window, map);

	while (!((courant.first == arrivee.x) && (courant.second == arrivee.y))
		&&
		(!liste_ouverte.empty())
		) {


		// on cherche le meilleur noeud de la liste ouverte, on sait qu'elle n'est pas vide donc il existe
		courant = meilleur_noeud(liste_ouverte);

		// on le passe dans la liste fermee, il ne peut pas déjà y être
		ajouter_liste_fermee(courant);

		ajouter_cases_adjacentes(courant, window, map);
	}

	if ((courant.first == arrivee.x) && (courant.second == arrivee.y)) {
		retrouver_chemin();

	}
	else {
		/* pas de solution */
		std::cout << "errreuurrrr" << std::endl;
	}
}

float PathFinding::distance(int x1, int y1, int x2, int y2) {
	//return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}


bool PathFinding::deja_present_dans_liste(std::pair<int, int> n, l_noeud& l) {
	l_noeud::iterator i = l.find(n);
	if (i == l.end())
		return false;
	else
		return true;
}

std::pair<int, int> PathFinding::meilleur_noeud(l_noeud& l) {
	float m_coutf = l.begin()->second.cout_f;
	std::pair<int, int> m_noeud = l.begin()->first;

	for (l_noeud::iterator i = l.begin(); i != l.end(); i++)
		if (i->second.cout_f< m_coutf) {
			m_coutf = i->second.cout_f;
			m_noeud = i->first;
		}

	return m_noeud;
}

void PathFinding::ajouter_cases_adjacentes(std::pair <int, int>& n, sf::RenderWindow* window, MyMap* map) {
	noeud tmp;

	// on met tous les noeud adjacents dans la liste ouverte (+vérif)
	for (int i = n.first - 1; i <= n.first + 1; i++) {
		if ((i<0) || (i >= map->width))
			continue;
		for (int j = n.second - 1; j <= n.second + 1; j++) {
			if ((j<0) || (j >= map->height))
				continue;
			if ((i == n.first) && (j == n.second))  // case actuelle n
				continue;
			if (map->getOnThisPositionNoeud(i, j).passable == 0)
				// obstace, terrain non franchissable
				continue;
			// it for 4 direction onlye - remove if you wanna 8 direction
			if (((i == n.first - 1 || i == n.first + 1) && j == n.second) || ((j == n.second - 1 || j == n.second + 1) && i == n.first))
			{
				std::pair<int, int> it(i, j);

				if (!deja_present_dans_liste(it, liste_fermee)) {
					/* le noeud n'est pas déjà présent dans la liste fermée */

					tmp.cout_g = liste_fermee[n].cout_g + distance(i, j, n.first, n.second) + map->getOnThisPositionNoeud(i, j).weight;
					tmp.cout_h = distance(i, j, arrivee.x, arrivee.y);
					tmp.cout_f = tmp.cout_g + tmp.cout_h;
					tmp.parent = n;

					if (deja_present_dans_liste(it, liste_ouverte)) {
						/* le noeud est déjà présent dans la liste ouverte, il faut comparer les couts */
						if (tmp.cout_f < liste_ouverte[it].cout_f) {
							/* si le nouveau chemin est meilleur, on update */
							liste_ouverte[it] = tmp;
						}

						/* le noeud courant a un moins bon chemin, on ne change rien */


					}
					else {
						/* le noeud n'est pas présent dans la liste ouverte, on l'ajoute */
						liste_ouverte[std::pair<int, int>(i, j)] = tmp;
					}
				}
			}
		}
	}
}


void PathFinding::ajouter_liste_fermee(std::pair<int, int>& p) {
	noeud& n = liste_ouverte[p];
	liste_fermee[p] = n;

	// il faut le supprimer de la liste ouverte, ce n'est plus une solution explorable
	if (liste_ouverte.erase(p) == 0)
		std::cout << "n'apparait pas dans la liste ouverte, impossible à supprimer" << std::endl;
	return;
}

void PathFinding::retrouver_chemin() {
	// l'arrivée est le dernier élément de la liste fermée.
	noeud& tmp = liste_fermee[std::pair<int, int>(arrivee.x, arrivee.y)];

	struct point n;
	std::pair<int, int> prec;
	n.x = arrivee.x;
	n.y = arrivee.y;
	prec.first = tmp.parent.first;
	prec.second = tmp.parent.second;
	chemin.push_front(n);

	while (prec != std::pair<int, int>(depart.parent.first, depart.parent.second)) {
		n.x = prec.first;
		n.y = prec.second;
		chemin.push_front(n);

		tmp = liste_fermee[tmp.parent];
		prec.first = tmp.parent.first;
		prec.second = tmp.parent.second;
	}
}
