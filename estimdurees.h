#ifndef ESTIMDUREES_H
#define ESTIMDUREES_H
#include <vector>

class estimdurees
{
public:

    estimdurees(void);
    estimdurees(std::vector <std::vector <double> > const& MatriceDistance);
    ~estimdurees(void);

    void SetTempsArretMoyenStation(double beta0);
    void SetCoefLinRegressionLineaire(double beta1);
    void SetCoefQuadraRegressionLineaire(double beta2);

    double GetTpsCorres(void)const;
    std::vector <std::vector <double> > GetMatriceDurees(void) const;

    double ModelisationDurees(double Distance);
    void CalculDureesTrajet(void);
    double CalculTempsCorrespondanceMoyen(void);


private:

    double m_TpsCorres;
    double m_TempsArretMoyenStation;
    double m_CoefLinRegressionLineaire;
    double m_CoefQuadraRegressionLineaire;
    std::vector <std::vector <double> > m_MatriceDistance ;
    std::vector <std::vector <double> > m_MatriceDurees ;

};

#endif // ESTIMDUREES_H
