#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <vector>
#include <numeric>

class dijkstra
{
public:
    dijkstra(void);
    dijkstra(std::vector <std::vector <double> > const& MatriceDureeTrajet, std::vector <std::vector <std::vector <double> > > const& MatriceLigneSurTrajet, double const& TpsCorres);
    ~dijkstra(void);

    void SetCodeStationDepart(int CSD);
    void SetCodeStationArrivee(int CSA);
    void SetMatricePoidsArete(std::vector <std::vector <double> > MPA);
    void SetMatriceLigneSurTrajet(std::vector <std::vector <std::vector <double> > > MLST);
    void SetTpsCorres(double Tps);

    double GetDureeTotale(void) const;
    int GetNbCorres(void) const;
    std::vector <std::vector <double> > GetMatriceSortie(void) const;

    // fonction interne à l'algorithme

   void InitDijk(void);
   int AppartAVecteurNoeudATester(int CodeStationATester);
   std::vector <int> RechercheVoisin(int CodeStationAct);
   void LignePossibleTrajetAvecVoisin(std::vector <int> const& voisin);
   void MajDistanceSommet(std::vector <int> const& voisin);
   int RechercheMin(void);
   void AlgoDuree(void);
   void RecuperationPlusCourtChemin(void);
   void ConstructionSortie(void);

   //fonction génrale pour execution de l'algorithme

   void AlgoDijkstra(int CodeStationDepart, int CodeStationArrivee);

private:

    // Champs d'entrées
    int m_CodeStationDepart;
    int m_CodeStationArrivee;
    double m_TpsCorres;
    std::vector <std::vector <double> > m_MatricePoidsArete;
    std::vector <std::vector <std::vector <double> > > m_MatriceLigneSurTrajet;

    // Champs interne de travail
    std::vector <double> m_VecteurDistanceSommet;
    std::vector <int> m_VecteurNoeudATester;
    std::vector <int> m_ListeCodeStationPlusCourtChemin;

    std::vector <std::vector <int> > m_VecteurBidimNoeudVoisin;
    /* Vecteur Bi-dimensionnel :
     * Echelle 1 (extérieure) : nombre de recherche de voisin = nombre itération de l'algorithme dijkstra
     * Echelle 2 : nombre de voisin et donc de trajet possible pour chaque recherche de voisin
     */

    std::vector <std::vector <std::vector <double> > > m_VecteurTridimLigneAct;
    /* Vecteur Tri-dimensionnel :
     * Echelle 1 (extérieure) : nombre de recherche de voisin = nombre itération de l'algorithme dijkstra
     * Echelle 2 : nombre de voisin et donc de trajet possible pour chaque recherche de voisin
     * Echelle 3 : Nombre de ligne avec direction pour un trajet unitaire signé (1 ou 2 pour paris)
     * Contenu : Code des lignes qui sont actualiser au fur et à mesure de l'algorithme
     * En effet pour bien traiter la question des correspondances et des trajet unitaire où plusieurs
     * ligne sont possible on doit actualiser la ligne actuelle pour chaque trajet selon le chemin suivi
     * jusqu'à ce trajet
     */

    // Champs de Sorties
    int m_NbCorres;
    double m_DureeTotale;
    std::vector <std::vector <double> > m_MatriceSortie;

};

#endif // DIJKSTRA_H
