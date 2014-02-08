#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"

fenetreprincipale::fenetreprincipale(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fenetreprincipale)
{
    ui->setupUi(this);
}

fenetreprincipale::~fenetreprincipale()
{
    delete ui;
}
