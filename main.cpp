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

    SetTempsArretMoyenStation(20.0);
    SetCoefLinRegressionLineaire(0.9);
    SetCoefQuadraRegressionLineaire(0.23);
    estimdurees Regress(MDistanceTrajet);


    double TempsCorrespndance = estimdurees.Get.TpsCorres();
    //std::vector <std::vector <double> > MDureeTrajet = estimdurees.GetMatriceDuree();

    /*
     * En effet comme le calcul des durée est le point du projet qui peut être trandformé pour
     * coller mieux à la réalité on le sépare de la construction du réseau.
     * Ainsi un utilisateur du programme pourra modifier l'algorithme permettant le calcul des
     * durées des trajet simple (trajet entre 2 stations directement liées) à partir de la distance
     * entre 2 stations (issues des coordonnées GPS)
     * Et aussi affiner les temps de correspondances que nous considerons comme unique et constant
     */


    //PHASE 3 : recherche du chemin le plus rapide avec l'algorithme dijkstra

    //dijkstra DJK(MDureeTrajet, MLigne);

    // Testgit



    // PHASE 4 : Interface Graphique

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
