#ifndef RESEAUPARIS_H
#define RESEAUPARIS_H
#include <vector>
#include <iostream>
#include "trajetunit.h"

class reseauparis
{

public:
    reseauparis(void);
    ~reseauparis (void);

    std::vector <std::string> GetTableNomStation(void) const;
    std::vector <double> GetTableCodeLigne(void) const;
    std::vector <std::string> GetTableNomLigne(void) const;
    std::vector <station> GetListeStation(void) const;
    std::vector <ligne> GetListeLigne(void) const;
    std::vector <std::vector <double> > GetMatriceTrajet(void) const;
    std::vector <std::vector <std::vector <double> > > GetMatriceLigneSurTrajet(void) const;

    void Codage(void);

    std::string TCSN(int CodeStation);
    int TNSC(std::string NomStation);
    std::string TCLN(double CodeLigne);
    double TNLC(std::string NomLigne);

    void CreationReseauStation(void);
    void CreationReseauLigne(void);
    void CreationMatrices(void);

private:
    std::vector <std::string> m_TableNomStation;
    std::vector <std::string> m_TableNomLigne;
    std::vector <double> m_TableCodeLigne;
    std::vector <station> m_ListeStation;
    std::vector <ligne> m_ListeLigne;
    std::vector <std::vector <double> > m_VecteurBidimTrajet;
    std::vector <std::vector <std::vector <double> > > m_VecteurTridimLigneSurTrajet;

};

#endif // RESEAUPARIS_H

