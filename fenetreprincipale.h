#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QDialog>

namespace Ui {
class fenetreprincipale;
}

class fenetreprincipale : public QDialog
{
    Q_OBJECT

public:
    explicit fenetreprincipale(QWidget *parent = 0);
    ~fenetreprincipale();

private:
    Ui::fenetreprincipale *ui;
};

#endif // FENETREPRINCIPALE_H
