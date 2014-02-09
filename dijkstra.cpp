#include "dijkstra.h"

dijkstra::dijkstra()
{
    m_CodeStationDepart = 0;
    m_CodeStationArrivee = 0;
    m_MatricePoidsArete = std::vector <std::vector <double> > (1,std::vector <double> (1,0.0));
    m_MatriceLigneSurTrajet = std::vector <std::vector <std::vector <double> > > (1,std::vector <std::vector <double> > (1,std::vector <double> (1,0.0)));
    m_TpsCorres = 0.0;
    m_TpsAttente = 0.0;
    m_NbCorres = 0;
    m_DureeTotale = 0.0;

}

dijkstra::dijkstra(std::vector<std::vector<double> > const& MatriceDureeTrajet, std::vector<std::vector<std::vector<double> > > const& MatriceLigneSurTrajet, double const& TpsCorres, double const& Ta)
{
    m_CodeStationDepart = 0;
    m_CodeStationArrivee = 0;
    m_MatricePoidsArete = MatriceDureeTrajet;
    m_MatriceLigneSurTrajet = MatriceLigneSurTrajet;
    m_TpsCorres = TpsCorres;
    m_TpsAttente = Ta
    m_NbCorres = 0;
    int lgh = MatriceDureeTrajet.size();
    m_DureeTotale = 0.0;
    m_VecteurDistanceSommet = std::vector <double> (lgh,0.0);
    m_VecteurPredecesseur = std::vector <double> (lgh,-1.0);

    int k=0;
    for (k=0;k<lgh;k++)
    {
        m_VecteurNoeudATester.push_back(k);
    }
}

dijkstra::~dijkstra()
{

}

void dijkstra::SetCodeStationDepart(int CSD)
{
    m_CodeStationDepart = CSD;
}

void dijkstra::SetCodeStationArrivee(int CSA)
{
    m_CodeStationArrivee = CSA ;
}


void dijkstra::SetMatricePoidsArete(std::vector <std::vector <double> > MPA)
{
    m_MatricePoidsArete = MPA;
}

void dijkstra::SetMatriceLigneSurTrajet(std::vector <std::vector <std::vector <double> > > MLST)
{
    m_MatriceLigneSurTrajet = MLST;
}

void dijkstra::SetTpsCorres(double Tps)
{
    m_TpsCorres = Tps;
}

void dijkstra::SetTpsAttente(double Ta)
{
    m_TpsAttente = Ta;
}

double dijkstra::GetDureeTotale() const
{
    return m_DureeTotale;
}

int dijkstra::GetNbCorres() const
{
    return m_NbCorres;
}

std::vector <std::vector <double> > dijkstra::GetMatriceSortie() const
{
    return m_MatriceSortie;
}



void dijkstra::InitDijk()
{
    std::vector <double> AretesDeb = m_MatricePoidsArete[m_CodeStationDepart];
    int LVDS = AretesDeb.size();

    int i;
    for (i=0;i<LVDS;i++)
    {
        if (i==m_CodeStationDepart)
        {
            m_VecteurDistanceSommet[i] = 0.0;
        }
        else
        {
            m_VecteurDistanceSommet[i] = 1000000.0;
        }
    }
    m_VecteurNoeudATester.erase(m_VecteurNoeudATester.begin() + m_CodeStationDepart);
}

int dijkstra::AppartAVecteurNoeudATester(int CodeStationATester)
{
    int k=0;
    int nbk = m_VecteurNoeudATester.size();
    int test = 0;
    while(test == 0 && k < nbk)
    {
        if(m_VecteurNoeudATester[k] == CodeStationATester)
        {
            test = 1;
        }
        k = k+1;
    }
    return test;
}

std::vector <int> dijkstra::RechercheVoisin(int CodeStationAct)
{
    std::vector <int> voisin(1,CodeStationAct);
    int j=0;
    int nbj = m_MatricePoidsArete.size();
    for(j=0;j<nbj;j++)
    {
        int Q = AppartAVecteurNoeudATester(j);
        if(m_MatricePoidsArete[CodeStationAct][j] > 0.0 && m_MatricePoidsArete[CodeStationAct][j] < 1000000.0 && Q == 1)
        {
             voisin.push_back(j);
        }
    }
    m_VecteurBidimNoeudVoisin.push_back(voisin);
    return voisin;
    // le vecteur contient donc en premiere position la station dont on cherche les voisins
    // puis les codes des différentes stations voisines qui n'ont pas encore étaient tester
    // (interdiction de repasser plusieurs fois dans une même station)
}

void dijkstra::LignePossibleTrajetAvecVoisin(std::vector <int> const& voisin)
{
    int v=1;
    int nbv= voisin.size();
    std::vector <std::vector <double> > inter;
    for(v=1;v<nbv;v++)
    {
        std::vector <double> A;
        A = m_MatriceLigneSurTrajet[voisin[0]][voisin[v]];// A modifier
        inter.push_back(A);
    }
    m_VecteurTridimLigneAct.push_back(inter);
}
// on obtient donc le vecteur des codes des ligne possible pour chaque trajet



void dijkstra::MajDistanceSommet(std::vector <int> const& voisin, int cpt)
{
    if(cpt == 0)
    {
        // rien à faire pour le passage des "lignes possibles sur le trajet" aux "lignes réllement utilisées"
        int nbv = voisin.size();
        int v=1;
        for(v=1;v<nbv;v++)
        {
            m_VecteurDistanceSommet[voisin[v]] = m_MatricePoidsArete[m_CodeStationDepart][voisin[v]];
            m_VecteurPredecesseur[voisin[v]] = m_CodeStationDepart;
        }
    }
    else
    {
        std::vector <double> t = m_VecteurTridimLigneAct[m_VecteurPredecesseur[voisin[0]]][voisin[0]];
        // trier t par ordre croissant
        int nbv = voisin.size();
        int v=1;
        for (v=1;j<nbv;v++)
        {
            int lt = t.size();
            std::vector <double> vv = m_MatriceLigneSurTrajet[voisin[0]][voisin[v]];
            // trier vv par ordre croissant
            int lvv = vv.size();
            if(lt == 2 && lvv == 2)
            {
                if((vv[0] == t[0] && vv[0] != t[1]) || (vv[0] == t[1] && vv[0] != t[0]) || (vv[1] == t[0] && vv[1] != t[1]) || (vv[1] == t[1] && vv[1] != t[0]) ) // pas de corres
                {
                    if(m_VecteurDistanceSommet[voisin[v]] > m_VecteurDistanceSommet[voisin[0]] + m_MatricePoidsArete[voisin[0]][voisin[v]])
                    {
                        m_VecteurDistanceSommet[voisin[v]] = m_VecteurDistanceSommet[voisin[0]] + m_MatricePoidsArete[voisin[0]][voisin[v]];
                        m_VecteurTridimLigneAct[voisin[0]][voisin[v]] = // seule la ligne commune à t et vv reste
                        m_VecteurPredecesseur[voisin[v]] = voisin[0];
                    }
                }
                else if((vv[0] == t[0] && vv[1] == t[1])) // pas de corres, trajet identique en terme de ligne
                {
                    if(m_VecteurDistanceSommet[voisin[v]] > m_VecteurDistanceSommet[voisin[0]] + m_MatricePoidsArete[voisin[0]][voisin[v]])
                    {
                        m_VecteurDistanceSommet[voisin[v]] = m_VecteurDistanceSommet[voisin[0]] + m_MatricePoidsArete[voisin[0]][voisin[v]];
                        m_VecteurTridimLigneAct[voisin[0]][voisin[v]] = m_MatriceLigneSurTrajet[voisin[0]][voisin[v]];
                        m_VecteurPredecesseur[voisin[v]] = voisin[0];
                    }
                }
                else if((vv[0] != t[0] && vv[0] != t[1]) && (vv[1] != t[0] && vv[1] != t[1])) // corres
                {
                    if(m_VecteurDistanceSommet[voisin[v]] > m_VecteurDistanceSommet[voisin[0]] + m_MatricePoidsArete[voisin[0]][voisin[v]] + m_TpsCorres)
                    {
                        m_VecteurDistanceSommet[voisin[v]] = m_VecteurDistanceSommet[voisin[0]] + m_MatricePoidsArete[voisin[0]][voisin[v]] + m_TpsCorres;
                        m_VecteurTridimLigneAct[voisin[0]][voisin[v]] = m_MatriceLigneSurTrajet[voisin[0]][voisin[v]];
                        m_VecteurPredecesseur[voisin[v]] = voisin[0];
                    }
                }
            }
            else if(lt == 1 && lvv == 2)
            {
                if (vv[0] == t[0] || vv[1] == t[0]) // pas de corres mais on corrige la ligne emprunté pour le trajet voisin[0]->voisin[v]
                {

                    if(m_VecteurDistanceSommet[voisin[v]] > m_VecteurDistanceSommet[voisin[0]] + m_MatricePoidsArete[voisin[0]][voisin[v]])
                    {
                        m_VecteurDistanceSommet[voisin[v]] = m_VecteurDistanceSommet[voisin[0]] + m_MatricePoidsArete[voisin[0]][voisin[v]];
                        m_VecteurTridimLigneAct[voisin[0]][voisin[v]] = // ligne commune entre trajet prec et trajet entre voisin[0] et voisin [v]
                        m_VecteurPredecesseur[voisin[v]] = voisin[0];
                    }
                }
                else if (vv[0] != t[0] && vv[0] != t[1]) // corres
                {

                    if(m_VecteurDistanceSommet[voisin[v]] > m_VecteurDistanceSommet[voisin[0]] + m_MatricePoidsArete[voisin[0]][voisin[v]] + m_TpsCorres)
                    {
                        m_VecteurDistanceSommet[voisin[v]] = m_VecteurDistanceSommet[voisin[0]] + m_MatricePoidsArete[voisin[0]][voisin[v]] + m_TpsCorres;
                        m_VecteurTridimLigneAct[voisin[0]][voisin[v]] = m_MatriceLigneSurTrajet[voisin[0]][voisin[v]];
                        m_VecteurPredecesseur[voisin[v]] = voisin[0];
                    }
                }

            }
            else if(lt == 2 && lvv == 1)
            {
                if (vv[0] == t[0] || vv[0] == t[1]) // pas de corres
                {
                    if(m_VecteurDistanceSommet[voisin[v]] > m_VecteurDistanceSommet[voisin[0]] + m_MatricePoidsArete[voisin[0]][voisin[v]])
                    {
                        m_VecteurDistanceSommet[voisin[v]] = m_VecteurDistanceSommet[voisin[0]] + m_MatricePoidsArete[voisin[0]][voisin[v]];
                        m_VecteurTridimLigneAct[voisin[0]][voisin[v]] = m_MatriceLigneSurTrajet[voisin[0]][voisin[v]];
                        m_VecteurPredecesseur[voisin[v]] = voisin[0];
                    }
                }
                else if (vv[0] != t[0] && vv[0] != t[1]) // corres
                {
                    if(m_VecteurDistanceSommet[voisin[v]] > m_VecteurDistanceSommet[voisin[0]] + m_MatricePoidsArete[voisin[0]][voisin[v]] + m_TpsCorres)
                    {
                        m_VecteurDistanceSommet[voisin[v]] = m_VecteurDistanceSommet[voisin[0]] + m_MatricePoidsArete[voisin[0]][voisin[v]] + m_TpsCorres;
                        m_VecteurTridimLigneAct[voisin[0]][voisin[v]] = m_MatriceLigneSurTrajet[voisin[0]][voisin[v]];
                        m_VecteurPredecesseur[voisin[v]] = voisin[0];
                    }
                }

            }
            else if(lt ==1 && lvv == 1)
            {
                if(vv[0] != t[0]) // corres (cas le plus fréquent)
                {
                    if(m_VecteurDistanceSommet[voisin[v]] > m_VecteurDistanceSommet[voisin[0]] + m_MatricePoidsArete[voisin[0]][voisin[v]] + m_TpsCorres)
                    {
                        m_VecteurDistanceSommet[voisin[v]] = m_VecteurDistanceSommet[voisin[0]] + m_MatricePoidsArete[voisin[0]][voisin[v]] + m_TpsCorres;
                        m_VecteurTridimLigneAct[voisin[0]][voisin[v]] = m_MatriceLigneSurTrajet[voisin[0]][voisin[v]];
                        m_VecteurPredecesseur[voisin[v]] = voisin[0];
                    }
                }
                else // Pas de corres
                {

                    if(m_VecteurDistanceSommet[voisin[v]] > m_VecteurDistanceSommet[voisin[0]] + m_MatricePoidsArete[voisin[0]][voisin[v]])
                    {
                        m_VecteurDistanceSommet[voisin[v]] = m_VecteurDistanceSommet[voisin[0]] + m_MatricePoidsArete[voisin[0]][voisin[v]];
                        m_VecteurTridimLigneAct[voisin[0]][voisin[v]] = m_MatriceLigneSurTrajet[voisin[0]][voisin[v]];
                        m_VecteurPredecesseur[voisin[v]] = voisin[0];
                    }
                }
            }
        }
    }

}


int dijkstra::RechercheMin()
{
    int nbs = m_VecteurNoeudATester.size();
    int s=0;
    double mini=1000000.0;
    int rgmin;
    for(s=0;s<nbs;s++)
    {
        if (m_VecteurDistanceSommet[m_VecteurNoeudATester[s]] <= mini )
        {
            mini = m_VecteurDistanceSommet[m_VecteurNoeudATester[s]];
            rgmin = m_VecteurNoeudATester[s];
        }
    }

    // suppresiion du min dans le vectuer des noeuds à tester
    int t = 0;
    int SommetASupprimer ;
    while(rgmin != m_VecteurNoeudATester[t] && t<nbs )
    {
    SommetASupprimer = t;
    t = t+1;
    }
    m_VecteurNoeudATester.erase(m_VecteurNoeudATester.begin()+t);

    return rgmin;
}

void dijkstra::AlgoDuree()
{
    //Initialisation
    InitDijk();
    int cpt = 0;
    int stop = m_MatricePoidsArete.size() - 1;
    int stmin = m_CodeStationDepart;
    std::vector <int> voisin;

    // Algorithme
    while (stmin != m_CodeStationArrivee && cpt < stop)
    {
        voisin = RechercheVoisin(stmin);
        LignePossibleTrajetAvecVoisin(voisin);
        MajDistanceSommet(voisin, cpt);
        stmin = RechercheMin();
        cpt + 1;
    }

    m_DureeTotale = m_VecteurDistanceSommet[m_CodeStationArrivee];
}

void dijkstra::RecuperationPlusCourtChemin()
{
    m_ListeCodeStationPlusCourtChemin.push_back(m_CodeStationArrivee);
    int prec = m_CodeStationArrivee;
    int nbs = m_VecteurDistanceSommet.size();
    int s=0;
    while(prec != m_CodeStationDepart && s<nbs)
    {
        prec = m_VecteurPredecesseur[prec];
        m_ListeCodeStationPlusCourtChemin.push_back(prec);
        s = s+1;
    }
    std::reverse(m_ListeCodeStationPlusCourtChemin.begin(),m_ListeCodeStationPlusCourtChemin.end());
}

void dijkstra::ConstructionSortie()
{

}

void dijkstra::AlgoDijkstra(int CodeStationDepart, int CodeStationArrivee)
{
    SetCodeStationDepart(CodeStationDepart);
    SetCodeStationArrivee(CodeStationArrivee);
    AlgoDuree();
    RecuperationPlusCourtChemin();
    ConstructionSortie();
}





















