#include "dijkstra.h"

dijkstra::dijkstra()
{
    m_CodeStationDepart = 0;
    m_CodeStationArrivee = 0;
    m_MatricePoidsArete = std::vector <std::vector <double> > (1,std::vector <double> (1,0.0));
    m_MatriceLigneSurTrajet = std::vector <std::vector <std::vector <double> > > (1,std::vector <std::vector <double> > (1,std::vector <double> (1,0.0)));
    m_TpsCorres = 0.0;
    m_NbCorres = 0;
    m_DureeTotale = 0.0;

}

dijkstra::dijkstra(std::vector<std::vector<double> > const& MatriceDureeTrajet, std::vector<std::vector<std::vector<double> > > const& MatriceLigneSurTrajet, double const& TpsCorres)
{
    m_CodeStationDepart = 0;
    m_CodeStationArrivee = 0;
    m_MatricePoidsArete = MatriceDureeTrajet;
    m_MatriceLigneSurTrajet = MatriceLigneSurTrajet;
    m_TpsCorres = TpsCorres;
    m_NbCorres = 0;
    int lgh = MatriceDureeTrajet.size();
    m_DureeTotale = 0.0;
    m_VecteurDistanceSommet = std::vector <double> (lgh,0.0);

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
    m_VecteurNoeudATester.erase(m_VecteurNoeudATester.begin()+m_CodeStationDepart);
}

int dijkstra::AppartAVecteurNoeudATester(int CodeStationATester)
{
    int k=0;
    int nbk = m_VecteurNoeudATester.size();
    int test = 0;
    while(test == 0 || k <nbk)
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
        A = m_MatriceLigneSurTrajet[voisin[0]][voisin[v]];
        inter.push_back(A);
    }
    m_VecteurTridimLigneAct.push_back(inter);
}
// on obtient donc le vecteur des codes des ligne possible pour chaque trajet

/*
void dijkstra::MajDistanceSommet(std::vector <int> const& voisin)
{

    int nbv = voisin.size();
    int v=0;
    int StationRef = voisin[0];
    for (v=1;j<nbv;v++)
    {
        if(StationRef == _CodeStationDepart)
        {
            _VecteurLigneAct[v] = _MatriceLigneSurTrajet[_CodeStationDepart][v];
        }
        else
        {
            int p = 0;
            int nbp = Ligneprec.size();
            std::vector <double> MLSTv = _MatriceLigneSurTrajet[StationRef][v];
            int MLSTvsize = MLSTv.size();
            for(p=0;p<nbp;p++)
            {
                if()
            }
            if()
        }


        if(_VecteurDistanceSommet[v] > _VecteurDistanceSommet[StationRef] + Trajet)
        {
            _VecteurDistanceSommet[v] = _VecteurDistanceSommet[StationRef] + Trajet ;
        }
    }
}
*/

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
    int stop = m_MatricePoidsArete.size() - 1;
    int stmin = m_CodeStationDepart;
    std::vector <int> voisin;

    // Algorithme
    while (stmin != m_CodeStationArrivee && stop > 0)
    {
        voisin = RechercheVoisin(stmin);
        LignePossibleTrajetAvecVoisin(voisin);
        //MajDistanceSommet(voisin);
        stmin = RechercheMin();
        stop = stop - 1;
    }

    m_DureeTotale = m_VecteurDistanceSommet[m_CodeStationArrivee];
}

void dijkstra::RecuperationPlusCourtChemin()
{

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





















