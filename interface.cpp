#include "interface.h"

interface::interface(std::vector<std::vector<double> > TEST, double CC, double DD,reseauparis const& RATP) : QWidget()
{
    //ChampsTest
    m_TempsAttente = DD;
    m_TpCor = CC;
    m_CheminOpt = TEST;


//interface::interface(reseauparis const& RATP, dijkstra& DJK) : QWidget()
//{

    m_RATP = RATP;
    //m_DJK = DJK;
    //m_TempsAttente = DJK.GetTpAttente();
    //m_TpCor = DJK.GetTpsCorres();
    m_DurTot = 0.0;
    m_StationDepartSelect = -1;
    m_StationArriveeSelect = -1;

    setWindowTitle("Métro Parisien");
    DefAlpha();

    // général

    setMinimumSize(920,680);
    setMaximumSize(1150,840);
    m_DispoVGen = new QVBoxLayout();
    QFont e("lucida grande",12);
    QFont f("lucida grande",13);
    QFont g("lucida grande",14,QFont::Bold);



    //Partie recherche

    m_FrameRecherche = new QFrame;
    m_DispoHChoixBout = new QHBoxLayout;
    m_Choix = new QVBoxLayout;
    m_ChampsDep = new QHBoxLayout;
    m_ChampsArr = new QHBoxLayout;

    m_TextChoisirDep = new QLabel;
    m_TextChoisirArr = new QLabel;
    m_TextComDep = new QLabel;
    m_TextComArr = new QLabel;
    m_ListeAlphaDep = new QComboBox;
    m_ListeAlphaArr = new QComboBox;
    m_ListeStaDep = new QComboBox;
    m_ListeStaArr = new QComboBox;
    m_RechercheBoutton = new QPushButton;


    m_TextChoisirDep->setFont(g);
    m_TextChoisirDep->setTextFormat(Qt::RichText);
    m_TextChoisirDep->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_TextChoisirDep->setText("Choisir la Station de Départ : ");

    m_TextChoisirArr->setFont(g);
    m_TextChoisirArr->setTextFormat(Qt::RichText);
    m_TextChoisirArr->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_TextChoisirArr->setText("Choisir la Station d'Arrivée' : ");

    m_TextComDep->setFont(e);
    m_TextComDep->setTextFormat(Qt::RichText);
    m_TextComDep->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_TextComDep->setText("Commençant par : ");

    m_TextComArr->setFont(e);
    m_TextComArr->setTextFormat(Qt::RichText);
    m_TextComArr->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_TextComArr->setText("Commençant par : ");


    m_ListeAlphaDep->addItems(m_Alpha);
    m_ListeAlphaDep->setFont(e);
    m_ListeAlphaArr->addItems(m_Alpha);
    m_ListeAlphaArr->setFont(e);
    m_ListeAlphaDep->setFont(e);
    m_ListeAlphaArr->setFont(e);
    QObject::connect(m_ListeAlphaDep,SIGNAL(activated(int)),this,SLOT(MajListeStaDep(int));
    QObject::connect(m_ListeAlphaArr,SIGNAL(activated(int)),this,SLOT(MajListeStaArr(int));
    QObject::connect(m_ListeStaDep,SIGNAL(activated(int)),this,SLOT(RecupCodeDepSelect(int));
    QObject::connect(m_ListeStaArr,SIGNAL(activated(int)),this,SLOT(RecupCodeArrSelect(int));

    m_RechercheBoutton->setFont(f);
    m_RechercheBoutton->setText("Rechercher Trajet Optimal");
    QObject::connect(m_RechercheBoutton,SIGNAL(clicked()),this,SLOT(ExecutionAlgoDijkstra());

    m_FrameRecherche->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    m_FrameRecherche->setLineWidth(0);
    m_FrameRecherche->setMidLineWidth(1);

    m_ChampsDep->addWidget(m_TextComDep);
    m_ChampsDep->addWidget(m_ListeAlphaDep);
    m_ChampsDep->addWidget(m_ListeStaDep);
    m_ChampsArr->addWidget(m_TextComArr);
    m_ChampsArr->addWidget(m_ListeAlphaArr);
    m_ChampsArr->addWidget(m_ListeStaArr);
    m_Choix->addWidget(m_TextChoisirDep);
    m_Choix->addLayout(m_ChampsDep);
    m_Choix->addWidget(m_TextChoisirArr);
    m_Choix->addLayout(m_ChampsArr);
    m_DispoHChoixBout->addLayout(m_Choix);
    m_DispoHChoixBout->addWidget(m_RechercheBoutton);
    m_FrameRecherche->setLayout(m_DispoHChoixBout);


    //Partie Resultat



    m_FrameResult = new QFrame;
    m_DispoResult = new QHBoxLayout;

    m_TextDurTot = new QLabel;
    m_DurTot = new QLCDNumber();
    m_SepV = new QFrame;
    m_TextCorres = new QLabel;
    m_NbCorres = new QLCDNumber;


    m_FrameResult->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    m_FrameResult->setLineWidth(0);
    m_FrameResult->setMidLineWidth(1);

    m_TextDurTot->setFont(f);
    m_TextDurTot->setTextFormat(Qt::RichText);
    m_TextDurTot->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_TextDurTot->setText("Durée totale du trajet le plus rapide (en minutes) : ");

    m_DurTot->setDigitCount(2);

    m_SepV->setFrameStyle(QFrame::VLine | QFrame::Raised);
    m_SepV->setLineWidth(0);
    m_SepV->setMidLineWidth(1);

    m_TextCorres->setFont(f);
    m_TextCorres->setTextFormat(Qt::RichText);
    m_TextCorres->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_TextCorres->setText("Nombre de correspondances : ");

    m_NbCorres->setDigitCount(1);


    m_DispoResult->addWidget(m_TextDurTot);
    m_DispoResult->addWidget(m_DurTot);
    m_DispoResult->addWidget(m_SepV);
    m_DispoResult->addWidget(m_TextCorres);
    m_DispoResult->addWidget(m_NbCorres);
    m_FrameResult->setLayout(m_DispoResult);


    //Texte "Detail..."


    m_TextDetailTraj = new QLabel();
    m_TextDetailTraj->setFont(g);
    m_TextDetailTraj->setFrameStyle(QFrame::NoFrame);
    m_TextDetailTraj->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_TextDetailTraj->setTextFormat(Qt::RichText);
    m_TextDetailTraj->setText("Détail du trajet le plus rapide : ");

    //Onglets

    m_Onglets = new QTabWidget;
    m_VectOnglets = new QVector<ongletdetailtrajet>;

    m_DispoVGen->addWidget(m_FrameRecherche);
    m_DispoVGen->addWidget(m_FrameResult);
    m_DispoVGen->addWidget(m_TextDetailTraj);
    m_DispoVGen->addWidget(m_Onglets);
    setLayout(m_DispoVGen);


}

// Fonction concernant la gestion des listes déroulantes

void interface::DefAlpha()
{
     m_Alpha.append("A");
     m_Alpha.append("B");
     m_Alpha.append("C");
     m_Alpha.append("D");
     m_Alpha.append("E");
     m_Alpha.append("F");
     m_Alpha.append("G");
     m_Alpha.append("H");
     m_Alpha.append("I");
     m_Alpha.append("J");
     m_Alpha.append("K");
     m_Alpha.append("L");
     m_Alpha.append("M");
     m_Alpha.append("N");
     m_Alpha.append("O");
     m_Alpha.append("P");
     m_Alpha.append("Q");
     m_Alpha.append("R");
     m_Alpha.append("S");
     m_Alpha.append("T");
     m_Alpha.append("U");
     m_Alpha.append("V");
     m_Alpha.append("W");
     m_Alpha.append("X");
     m_Alpha.append("Y");
     m_Alpha.append("Z");
}

void interface::MajListeStaDep(int RgDepLetSta)
{
    m_ListeStaDep->clear();
    m_CodeStationDepIssueTriAlpha.clear();

    QString lettre = m_Alpha[RgDepLetSta];
    int l=0;
    std::vector <QString> sta=m_RATP.GetTableNomStation();
    int nbl = sta.size();
    for(l=0;l<nbl;l++)
    {
        QString ll = sta[l];
        if(ll[0] == lettre[0])
        {
            m_QSListeStaDep.append(ll);
            int cdd = RATP.TNSC(ll);
            m_CodeStationDepIssueTriAlpha.push_back(cdd);
        }
    }
    m_ListeStaDep->addItems(m_QSListeStaDep);
    m_ListeStaDep->update();
}

void interface::MajListeStaArr(int RgArrLetSta)
{
    m_ListeStaArr->clear();
    m_CodeStationArrIssueTriAlpha.clear();

    QString lettre = m_Alpha[RgArrLetSta];
    int l=0;
    std::vector <QString> sta=m_RATP.GetTableNomStation();
    int nbl = sta.size();
    for(l=0;l<nbl;l++)
    {
        QString ll = sta[l];
        if(ll[0] == lettre[0])
        {
            m_QSListeStaArr.append(ll);
            int cdd = RATP.TNSC(ll);
            m_CodeStationArrIssueTriAlpha.push_back(cdd);
        }
    }
    m_ListeStaArr->addItems(m_QSListeStaArr);
    m_ListeStaArr->update();
}

void interface::RecupCodeDepSelect(int CodeStaDepSelect)
{
    //m_StationDepartSelect = m_CodeStationDepIssueTriAlpha[CodeStaDepSelect]; //suspendu pour test
    m_StationDepartSelect = TEST[0][0] //ajouter pour test
}

void interface::RecupCodeArrSelect(int CodeStaArrSelect)
{
    //m_StationArriveeSelect = m_CodeStationArrIssueTriAlpha[CodeStaArrSelect]; //suspendu pour test
    m_StationArriveeSelect = TEST[m_CheminOpt.size()-1][1] //ajouter pour test
}


void interface::ExecutionAlgoDijkstra()
{
    if(m_StationDepartSelect == m_StationArriveeSelect || m_StationDepartSelect == -1 || m_StationArriveeSelect == -1)
    {
        QMessageBox::warning(this,"Erreur","Veuillez choisr des Stations de Départ et d'Arrivée (qui soient différentes)");
    }
    else
    {
        /*Suppression Ancien affichage */
        delete m_Onglets;
        m_VectOnglets->clear();
        m_Onglets = new QTabWidget;

        /*Excution Alogrithme */

        //m_DJK.AlgoDijkstra(m_StationDepartSelect,m_StationArriveeSelect); //suspendu pour test
        int nbo = m_CheminOpt.size();
        //m_CheminOpt = m_DJK.GetMatriceSortie(); //suspendu pour test

        //transformation Temps d'attente et temps de correspondance en minutes (avec arrondi supérieur)
        m_TpCor = m_TpCor / 60;
        int TPC = (int)m_TpCor;
        TPC = TPC + 1;
        m_TempsAttente = m_TempsAttente / 60;
        int TPA =(int)m_TempsAttente;
        TPA = TPA + 1;

        /* Nouvel Affichage et calcul durée totale reconstitué et arrondi */
        int DureeTotalEstim = (TPC * (nbo-1)) + TPA;
        int o=0;
        for(o=0;o<nbo;o++)
        {
            int st1 = (int)m_CheminOpt[o][0];
            QString ST1 = m_RATP.TCSN(st1);
            int st2 = (int)m_CheminOpt[o][1];
            QString ST2 = m_RATP.TCSN(st2);
            int st3 = (int)m_CheminOpt[o][2];
            st3 = st3 + 1;
            DureeTotalEstim = DureeTotalEstim + st3;
            QString ST3 = QString::number(st3);
            QString ST4 = m_RATP.TCLN(m_CheminOpt[o][3]);

            if (o==0)
            {
                QString ST5 = QString::number(TPA);
            }
            else
            {
                QString ST5 = QString::number(TPC);
            }

            int rg = -1;
            if(nbo == 1)
            {
                rg = 1;
            }
            else if(nbo > 1 && o == 0)
            {
                rg = 0;
            }
            else if(nbo > 1 && o == (nbo-1))
            {
                rg = 2;
            }
            else if(nbo > 1 && o != 0 && o != (nbo-1))
            {
                rg = 3;
            }
            QString Nomongl = QString::number(o+1);
            ongletdetailtrajet QQ(ST1,ST2,ST3,ST4,ST5,rg);
            m_Onglets->addTab(QQ,"Tronçon "+ Nomongl);
        }

        m_DurTot->display(DTI);
        m_NbCorres->display(nbo-1);
        m_Onglets->update();
}



