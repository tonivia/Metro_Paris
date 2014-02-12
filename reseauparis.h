#ifndef RESEAUPARIS_H
#define RESEAUPARIS_H
#include <QString>
#include <vector>
#include "trajetunit.h"

class reseauparis
{

public:
    reseauparis(void);
    ~reseauparis (void);

    std::vector <QString> GetTableNomStation(void) const;
    std::vector <double> GetTableCodeLigne(void) const;
    std::vector <QString> GetTableNomLigne(void) const;
    std::vector <station> GetListeStation(void) const;
    std::vector <ligne> GetListeLigne(void) const;
    std::vector <std::vector <double> > GetMatriceTrajet(void) const;
    std::vector <std::vector <std::vector <double> > > GetMatriceLigneSurTrajet(void) const;

    void Codage(void);

    QString TCSN(int CodeStation);
    int TNSC(QString NomStation);
    QString TCLN(double CodeLigne);
    double TNLC(QString NomLigne);

    void CreationReseauStation(void);
    void CreationReseauLigne(void);
    void CreationMatrices(void);
    void CreationReseauComplet(void);

private:
    std::vector <QString> m_TableNomStation;
    std::vector <QString> m_TableNomLigne;
    std::vector <double> m_TableCodeLigne;
    std::vector <station> m_ListeStation;
    std::vector <ligne> m_ListeLigne;
    std::vector <std::vector <double> > m_VecteurBidimTrajet;
    std::vector <std::vector <std::vector <double> > > m_VecteurTridimLigneSurTrajet;

};

#endif // RESEAUPARIS_H

