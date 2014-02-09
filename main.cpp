#include "mainwindow.h"
#include <QApplication>
#include "reseauparis.h"
#include "estimdurees.h"
#include "dijkstra.h"

#include <vector>
#include <iostream>

int main(int argc, char *argv[])
{

    // PHASE 1 : Cosntruction Du Réseau

    // On construit le réseau parisien complet avec 302 stations et 16 lignes (De 1 à 14, 3bis et 7bis)

    reseauparis RATP;
    RATP.Codage();
    RATP.CreationReseauStation();
    RATP.CreationReseauLigne();
    RATP.CreationMatrices();
    std::vector <std::vector <double> > MDistanceTrajet = RATP.GetMatriceTrajet();
    std::vector <std::vector <std::vector <double> > > MLigne= RATP.GetMatriceLigneSurTrajet();

    /*
     * A l'issue de la construction nous obtenons donc 2 matrices :
     * l'une contient les distances en mètre entre tout les couples de station
     * - 0 entre une station et elle-même
     * - une valeur arbitrairement grande entre 2 stations qui ne sont pas en lien direct : 1 000 000
     * - la distance exacte entre 2 stations en lien direct
     *
     * L'autre contient dans chacune de ses cases un vecteur avec les codes des "lignes avec direction"
     * qui utilisent chaque trajet.
     *
     * Attention  :
     * les trajets sont signés : A->B différent de b->A
     * et de plus cette phase ne s'execute qu'une seule fois au lancement du programme
     * et non pas à chaque nouvelle recherche de trajet optimal d'un utilisateur
     */



    //PHASE 2 : Mise en place des durée des trajet et des durées des correspondances

    estimdurees Regress(MDistanceTrajet);
    Regress.SetTempsArretMoyenStation(20.0);
    Regress.SetCoefLinRegressionLineaire(0.9);
    Regress.SetCoefQuadraRegressionLineaire(0.23);
    Regress.CalculDureesTrajet();
    Regress.SetTempsCorrespondanceMoyen(240.0);
    //std::vector <std::vector <double> > MDureeTrajet = Regress.GetMatriceDuree();
    double Tcm = Regress.GetTpsCorres();

    //Temps attente première station moyen (selon la RATP en secondes)
    double Tam = 150.0;

    /*
     * En effet comme le calcul des durée est le point du projet qui peut être transformé pour
     * coller mieux à la réalité on le sépare de la construction du réseau.
     * Ainsi un utilisateur du programme pourra modifier l'algorithme permettant le calcul des
     * durées des trajet simple (trajet entre 2 stations directement liées) à partir de la distance
     * entre 2 stations (issues des coordonnées GPS)
     * Et aussi affiner les temps de correspondances que nous considerons comme unique et constant
     * et égal à 4 minutes ou 240.0 secondes
     * (valeur cohérante au vu de ce qui est dit sur le site de la RATP)
     */


    //PHASE 3 : recherche du chemin le plus rapide avec l'algorithme dijkstra


    //dijkstra DJK(MDureeTrajet, MLigne,Tcm,Tam);




    // PHASE 4 : Interface Graphique

    // doonée de test

    std::vector <double> TEST1(4,0.0);
    std::vector <std::vector <double> > TEST2(3,TEST1);

    TEST2[0][0] = 4.0;
    TEST2[0][1] = 14.0;
    TEST2[0][2] = 1.2;
    TEST2[0][3] = 725.0;

    TEST2[1][0] = 14.0;
    TEST2[1][1] = 86.0;
    TEST2[1][2] = 4.2;
    TEST2[1][3] = 260.0;

    TEST2[2][0] = 86.0;
    TEST2[2][1] = 110.0;
    TEST2[2][2] = 10.2;
    TEST2[2][3] = 455.0;

    double DurTot = 2070.0;
    int nbcor = 2;





    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
