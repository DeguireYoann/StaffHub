/*

IFT1169 - TP3 A24 -

Auteur: Yoann Deguire - decembre 2024

Description: Gestionnaire de l'interface graphique
------------
*/
#include "InterfaceController.h"
#include "FileReader.h"
#include "Programmer.h"
#include "Manager.h"

using namespace std;

InterfaceController::InterfaceController()
    : wxFrame(nullptr, -1, "Charger les fichiers", wxDefaultPosition, wxDefaultSize) {
    // Créer le panel principal
    currentPanel = new wxPanel(this);
    this->SetTitle("Configuration");
    this->Maximize(true);

    // Créer les éléments de l'interface
    wxStaticText* labelManager = new wxStaticText(currentPanel, -1, "Fichier Managers:", wxPoint(10, 20));
    wxTextCtrl* fichierManager = new wxTextCtrl(currentPanel, -1, "./Data/managers.csv", wxPoint(150, 20), wxSize(250, 25));

    wxStaticText* labelProgrammeur = new wxStaticText(currentPanel, -1, "Fichier Programmeurs:", wxPoint(10, 60));
    wxTextCtrl* fichierProgrammeur = new wxTextCtrl(currentPanel, -1, "./Data/Programmeurs.csv", wxPoint(150, 60), wxSize(250, 25));

    wxButton* btnProcess = new wxButton(currentPanel, -1, "Continuer", wxPoint(150, 100), wxSize(100, 30));

    // Connecter le bouton
    btnProcess->Bind(wxEVT_BUTTON, [this, fichierManager, fichierProgrammeur](wxCommandEvent&) {
        this->validerFichier(fichierManager->GetValue(), fichierProgrammeur->GetValue());
    });
    Bind(wxEVT_CLOSE_WINDOW, &InterfaceController::OnClose, this);
    ajouterMenu();
}

void InterfaceController::lire(wxCommandEvent& event) {
   // Créer le panel principal
    if (currentPanel) {
        currentPanel->Destroy();  // Détruire l'ancien panel
    }
    currentPanel = new wxPanel(this);
    this->SetTitle("Lire");

    // Créer les éléments de l'interface
    wxStaticText* labelManager = new wxStaticText(currentPanel, -1, "Fichier Managers:", wxPoint(10, 20));
    wxTextCtrl* fichierManager = new wxTextCtrl(currentPanel, -1, "./Data/managers.csv", wxPoint(150, 20), wxSize(250, 25));

    wxStaticText* labelProgrammeur = new wxStaticText(currentPanel, -1, "Fichier Programmeurs:", wxPoint(10, 60));
    wxTextCtrl* fichierProgrammeur = new wxTextCtrl(currentPanel, -1, "./Data/Programmeurs.csv", wxPoint(150, 60), wxSize(250, 25));

    wxButton* btnProcess = new wxButton(currentPanel, -1, "Continuer", wxPoint(150, 100), wxSize(100, 30));

    // Connecter le bouton
    btnProcess->Bind(wxEVT_BUTTON, [this, fichierManager, fichierProgrammeur](wxCommandEvent&) {
        this->validerFichier(fichierManager->GetValue(), fichierProgrammeur->GetValue());
    });

    currentPanel->Layout();
    currentPanel->Show(true);
    this->Maximize(true);
    this->Layout();
    this->Refresh();
}

void InterfaceController::sauvegarder(wxCommandEvent& event) {
    if (currentPanel) {
        currentPanel->Destroy();  // Détruire l'ancien panel
    }
    currentPanel = new wxPanel(this);
    this->SetTitle("Sauvegarder");

    // Créer les éléments de l'interface
    wxStaticText* labelManager = new wxStaticText(currentPanel, -1, "Fichier Managers:", wxPoint(10, 20));
    wxTextCtrl* fichierManager = new wxTextCtrl(currentPanel, -1, "./Data/managers_nouveau.csv", wxPoint(150, 20), wxSize(250, 25));

    wxStaticText* labelProgrammeur = new wxStaticText(currentPanel, -1, "Fichier Programmeurs:", wxPoint(10, 60));
    wxTextCtrl* fichierProgrammeur = new wxTextCtrl(currentPanel, -1, "./Data/Programmeurs_nouveau.csv", wxPoint(150, 60), wxSize(250, 25));

    wxButton* btnProcess = new wxButton(currentPanel, -1, "Sauvegarder", wxPoint(150, 100), wxSize(100, 30));

    btnProcess->Bind(wxEVT_BUTTON, [this, fichierManager, fichierProgrammeur, &event](wxCommandEvent&) {
        this->sauvegarderFichier(fichierManager->GetValue(), fichierProgrammeur->GetValue());
    });

    currentPanel->Layout();
    currentPanel->Show(true);
    this->Maximize(true);
    this->Layout();
    this->Refresh();
    }

void InterfaceController::afficherPropos(wxCommandEvent& event) {
    wxDialog* proposDialog = new wxDialog(this, wxID_ANY, "A propos", wxDefaultPosition, wxSize(400, 200));

    wxPanel* panel = new wxPanel(proposDialog);

    wxStaticText* auteurTitre = new wxStaticText(panel, wxID_ANY, "Auteur : Yoann Deguire", wxPoint(20, 20));
    auteurTitre->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    wxStaticText* descriptionTexte = new wxStaticText(panel, wxID_ANY, 
        "Travail realise dans le cadre du TP3 du cours IFT-1169 durant la session d'automne 2024.",
        wxPoint(20, 60), wxSize(360, 80));

    // Ajouter un bouton OK pour fermer
    wxButton* btnClose = new wxButton(panel, wxID_OK, "OK", wxPoint(150, 150), wxSize(100, 30));

    // Connecter le bouton OK
    btnClose->Bind(wxEVT_BUTTON, [proposDialog](wxCommandEvent&) {
        proposDialog->EndModal(wxID_OK);
    });

    proposDialog->ShowModal();
    // Liberer la mémoire après la fermeture
    proposDialog->Destroy();
}

void InterfaceController::ajouterMenu() {
    wxMenu* menuFichier = new wxMenu;
    wxMenu* menu = new wxMenu;

    // Ajouter les éléments de menuFichier
    menuFichier->Append(ID_MENU_LIRE, "Lire");
    menuFichier->Append(ID_MENU_SAUVEGARDER, "Sauvegarder");

    // Ajouter les éléments de menu
    menu->Append(ID_MENU_RECHERCHER, "Rechercher");
    menu->Append(ID_MENU_AJOUTER, "Ajouter");
    menu->Append(ID_MENU_SUPPRIMER, "Supprimer");
    menu->Append(ID_MENU_APROPOS, "A Propos");

    // Créer un menu bar et ajouter le menu
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFichier, "Fichier");
    menuBar->Append(menu, "Menu");

    // Ajouter le menu bar à la fenêtre
    SetMenuBar(menuBar);

    // Connecter les boutons pour menuFichier
    Bind(wxEVT_MENU, &InterfaceController::lire, this, ID_MENU_LIRE);
    Bind(wxEVT_MENU, &InterfaceController::sauvegarder, this, ID_MENU_SAUVEGARDER);

    // Connecter les boutons pour menu
    Bind(wxEVT_MENU, &InterfaceController::rechercher, this, ID_MENU_RECHERCHER);
    Bind(wxEVT_MENU, &InterfaceController::ajouter, this, ID_MENU_AJOUTER);
    Bind(wxEVT_MENU, &InterfaceController::supprimer, this, ID_MENU_SUPPRIMER);
    Bind(wxEVT_MENU, &InterfaceController::afficherPropos, this, ID_MENU_APROPOS);
}

void InterfaceController::validerFichier(const wxString& fichierManager, const wxString& fichierProg) {
    // Si il manque un fichier afficher un message
    if (fichierManager.IsEmpty() || fichierProg.IsEmpty()) {
        wxMessageBox("Veuillez valider les deux champs avant de continuer.", "Erreur", wxOK | wxICON_ERROR);
        return;
    }

    // Utilisé la classe  lecteurFichier setter les routes
    LecteurFichier lecteur;
    lecteur.setRouteFichierManager(fichierManager.ToStdString());
    lecteur.setRouteFichierProg(fichierProg.ToStdString());
    // Valider les fichiers
    const bool fichiersValide = lecteur.validerFichiers();

    /*
        Si valide on créer les vector
        Lecture des fichiers (implementation des listes)
        On sort les fichiers
    */
    if(fichiersValide) {
        vector<Manager> managers;
        vector<Programmer> programmeurs;

        lecteur.lireFichierManager(managers);
        lecteur.lireFichierProgrammeur(programmeurs);

        sort(managers.begin(), managers.end());
        sort(programmeurs.begin(), programmeurs.end());

       // Appeler ajouterManager pour chaque manager
        for (auto& manager : managers) {
            gestionnaireEmployes.ajouterManager(manager);
        }

        // Appeler ajouterProgrammeur pour chaque programmeur
        for (auto& programmeur : programmeurs) {
            gestionnaireEmployes.ajouterProgrammeur(programmeur);
        }

        afficherMenuPrincipal();
    } else {
        // Si non valide on afficher une erreur
        wxMessageBox("Fichier invalide.", "Erreur", wxOK | wxICON_ERROR);
    }
}

void InterfaceController::sauvegarderFichier(const wxString& fichierManager, const wxString& fichierProg) {
    // Si il manque un fichier afficher un message
    if (fichierManager.IsEmpty() || fichierProg.IsEmpty()) {
        wxMessageBox("Veuillez valider les deux champs avant de continuer.", "Erreur", wxOK | wxICON_ERROR);
        return;
    }

    // Utilisé la classe  lecteurFichier setter les routes
    LecteurFichier lecteur;
    lecteur.setRouteFichierManager(fichierManager.ToStdString());
    lecteur.setRouteFichierProg(fichierProg.ToStdString());

    // Écriture des fichiers
    lecteur.ecrireFichierManager(this->gestionnaireEmployes.getManagers());
    lecteur.ecrireFichierProgrammeur(this->gestionnaireEmployes.getProgrammeurs());

    wxMessageBox("Fichier Sauvegarder", "Sauvegarde", wxOK | wxICON_INFORMATION);
}

void InterfaceController::afficherMenuPrincipal() {
    if (currentPanel) {
        currentPanel->Destroy();  // Détruire l'ancien panel
    }

    // Créer un nouveau panel si nécessaire
    currentPanel = new wxPanel(this);

    // Mettre à jour le titre
    this->SetTitle("Menu Principal");

    // Ajouter les boutons principaux
    wxButton* btnRechercher = new wxButton(currentPanel, -1, "Rechercher", wxPoint(50, 20), wxSize(100, 30));
    wxButton* btnAjouter = new wxButton(currentPanel, -1, "Ajouter", wxPoint(50, 70), wxSize(100, 30));
    wxButton* btnSupprimer = new wxButton(currentPanel, -1, "Supprimer", wxPoint(50, 120), wxSize(100, 30));

    // Connecter les events des boutons
    btnRechercher->Bind(wxEVT_BUTTON, &InterfaceController::rechercher, this);
    btnAjouter->Bind(wxEVT_BUTTON, &InterfaceController::ajouter, this);
    btnSupprimer->Bind(wxEVT_BUTTON, &InterfaceController::supprimer, this);

    // Ajuster la taille de la fenêtre
    currentPanel->Show(true);
    this->Maximize(true);
    this->Layout();
    this->Refresh();
}



void InterfaceController::rechercher(wxCommandEvent& event) {
    if (currentPanel) {
        currentPanel->Destroy();  // Détruire l'ancien panel
    }

    // Créer un nouveau panel si nécessaire
    currentPanel = new wxPanel(this);
    this->SetTitle("Rechercher");

    // Créer un grid avec 2 colonnes
    wxGridSizer* griller = new wxGridSizer(2, 10, 10);

    /**
     * Création des différents boutons
     * Bind avec la méthode ouvrirFenetreRecherche avec les props et la methode associer pour l'action
     */
    wxButton* btnRechercheManagerParProjet = new wxButton(currentPanel, -1, "Rechercher manager par projet");
    btnRechercheManagerParProjet->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        ouvrirFenetreRecherche(
            "Rechercher manager par projet",
            "Nom du projet:",
            [this](const string& input) {
                return this->gestionnaireEmployes.managerParProjet(input);
            }
        );
    });
    griller->Add(btnRechercheManagerParProjet, 0, wxEXPAND | wxALL, 5);

    wxButton* btnRechercheProjetDuManager = new wxButton(currentPanel, -1, "Rechercher projet du manager");
    btnRechercheProjetDuManager->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        ouvrirFenetreRecherche(
            "Rechercher projet du manager",
            "Nom du manager:",
            [this](const string& input) {
                return this->gestionnaireEmployes.afficherProjetManager(input);
            }
        );
    });
    griller->Add(btnRechercheProjetDuManager, 0, wxEXPAND | wxALL, 5);

    wxButton* btnRechercheProgDuManager = new wxButton(currentPanel, -1, "Rechercher programmeur par manager");
    btnRechercheProgDuManager->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        ouvrirFenetreRecherche(
            "Rechercher programmeur par manager",
            "Nom du manager:",
            [this](const string& input) {
                return this->gestionnaireEmployes.programmeurAssocier(input);
            }
        );
    });
    griller->Add(btnRechercheProgDuManager, 0, wxEXPAND | wxALL, 5);

    wxButton* btnRechercheManagerduProg = new wxButton(currentPanel, -1, "Rechercher manager par programmeur");
    btnRechercheManagerduProg->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        ouvrirFenetreRecherche(
            "Rechercher manager du programmeur",
            "Nom du programmeur:",
            [this](const string& input) {
                return this->gestionnaireEmployes.managerDuProgrammeur(input);
            }
        );
    });
    griller->Add(btnRechercheManagerduProg, 0, wxEXPAND | wxALL, 5);

    wxButton* btnRechercheProjetParProg = new wxButton(currentPanel, -1, "Rechercher projet par programmeur");
    btnRechercheProjetParProg->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        ouvrirFenetreRecherche(
            "Rechercher projet par programmeur",
            "Nom du programmeur:",
            [this](const string& input) {
                return this->gestionnaireEmployes.afficherProjetProgrammeur(input);
            }
        );
    });
    griller->Add(btnRechercheProjetParProg, 0, wxEXPAND | wxALL, 5);
    
    wxButton* btnRechercheProgParProjet = new wxButton(currentPanel, -1, "Rechercher programmeur par projet");
    btnRechercheProgParProjet->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        ouvrirFenetreRecherche(
            "Rechercher programmeur par projet",
            "Nom du projet:",
            [this](const string& input) {
                return this->gestionnaireEmployes.programmeurParProjet(input);
            }
        );
    });
    griller->Add(btnRechercheProgParProjet, 0, wxEXPAND | wxALL, 5);
    


    // Ajuster la taille
    currentPanel->SetSizer(griller);
    currentPanel->Layout();
    currentPanel->Show(true);
    this->Maximize(true);
    this->Layout();
    this->Refresh();
}

/**
 * Methode pour ouvrir la fenetre de recherche
 * Prend en parametres les strings pour l'affichage et un fonction pour traiter l'action
 */
void InterfaceController::ouvrirFenetreRecherche(
    const wxString& titreFenetre, 
    const wxString& texteLabel, 
    function<string(const string&)> fonctionTraitement
) {
    // Créer une nouvelle fenêtre pour la recherche
    wxFrame* frame = new wxFrame(
        this, 
        wxID_ANY, 
        titreFenetre, 
        wxDefaultPosition, 
        wxSize(400, 200), 
        wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)
    );

    wxPanel* panneau = new wxPanel(frame);

    wxStaticText* label = new wxStaticText(panneau, wxID_ANY, texteLabel, wxPoint(10, 20));

    wxTextCtrl* inputText = new wxTextCtrl(panneau, wxID_ANY, "", wxPoint(200, 18), wxSize(150, 25));

    // Ajouter un bouton pour rechercher
    wxButton* btnProcess = new wxButton(panneau, wxID_ANY, "Rechercher", wxPoint(150, 100), wxSize(100, 30));

    // Connecter le bouton a l'action
    btnProcess->Bind(wxEVT_BUTTON, [fonctionTraitement, inputText](wxCommandEvent& event) {
        string resultat = fonctionTraitement(inputText->GetValue().ToStdString());
        wxMessageBox(wxString(resultat), "Resultat", wxOK | wxICON_INFORMATION);
    });

    // Afficher la fenêtre de recherche
    frame->Show(true);
}

void InterfaceController::ajouter(wxCommandEvent& event) {
    if (currentPanel) {
        currentPanel->Destroy();  // Détruire l'ancien panel
    }

    // Créer un nouveau panel si nécessaire
    currentPanel = new wxPanel(this);
    this->SetTitle("Ajouter");

    // Créer un grid avec 2 colonnes
    wxGridSizer* griller = new wxGridSizer(2, 10, 10);

    /**
     * Création des différents boutons
     * Bind avec la méthode ouvrirFenetreAjouterSupprimer avec les props et la methode associer pour l'action
     */
    wxButton* btnRechercheManagerParProjet = new wxButton(currentPanel, -1, "Ajouter un projet a un manager");
    btnRechercheManagerParProjet->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        ouvrirFenetreAjouterSupprimer(
            "Ajouter un projet a un manager",
            "Ajouter le projet:",
            "au manager:",
            "ajouter",
            gestionnaireEmployes.getManagers(),
            [this](const string& lastName, const string& projet) {
                return this->gestionnaireEmployes.ajouterProjetAuManager(lastName, projet);
            }
        );
    });
    griller->Add(btnRechercheManagerParProjet, 0, wxEXPAND | wxALL, 5);

    wxButton* btnRechercheProjetDuManager = new wxButton(currentPanel, -1, "Ajouter un programmeur a un manager");
    btnRechercheProjetDuManager->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        ouvrirFenetreAjouterSupprimer(
            "Ajouter un programmeur a un manager",
            "Ajouter le programmeur:",
            "au manager:",
            "ajouter",
            gestionnaireEmployes.getManagers(),
            [this](const string& lastName, const string& prog) {
                return this->gestionnaireEmployes.ajouterProgAuManager(lastName, prog);
            }
        );
    });
    griller->Add(btnRechercheProjetDuManager, 0, wxEXPAND | wxALL, 5);

    wxButton* btnRechercheProgDuManager = new wxButton(currentPanel, -1, "Ajouter un projet a un programmeur");
    btnRechercheProgDuManager->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        ouvrirFenetreAjouterSupprimer(
            "Ajouter un projet a un programmeur",
            "Ajouter le projet:",
            "au programmeur:",
            "ajouter",
            gestionnaireEmployes.getProgrammeurs(),
            [this](const string& lastName, const string& projet) {
                return this->gestionnaireEmployes.ajouterProjetAuProg(lastName, projet);
            }
        );
    });
    griller->Add(btnRechercheProgDuManager, 0, wxEXPAND | wxALL, 5);

    // Ajuster la taille
    currentPanel->SetSizer(griller);
    currentPanel->Layout();
    currentPanel->Show(true);
    this->Maximize(true);
    this->Layout();
    this->Refresh();
}

void InterfaceController::supprimer(wxCommandEvent& event) {
    if (currentPanel) {
        currentPanel->Destroy();  // Détruire l'ancien panel
    }

    // Créer un nouveau panel si nécessaire
    currentPanel = new wxPanel(this);
    this->SetTitle("Retirer");

    // Créer un grid avec 2 colonnes
    wxGridSizer* griller = new wxGridSizer(2, 10, 10);

    /**
     * Création des différents boutons
     * Bind avec la méthode ouvrirFenetreAjouterSupprimer avec les props et la methode associer pour l'action
     */
    wxButton* btnRechercheManagerParProjet = new wxButton(currentPanel, -1, "Retirer un projet d'un manager");
    btnRechercheManagerParProjet->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        ouvrirFenetreAjouterSupprimer(
            "Retirer un projet d'un manager",
            "Retirer le projet:",
            "au manager:",
            "retirer",
            gestionnaireEmployes.getManagers(),
            [this](const string& lastName, const string& projet) {
                return this->gestionnaireEmployes.supprimerProjetAuManager(lastName, projet);
            }
        );
    });
    griller->Add(btnRechercheManagerParProjet, 0, wxEXPAND | wxALL, 5);

    wxButton* btnRechercheProjetDuManager = new wxButton(currentPanel, -1, "Retirer un programmeur d'un manager");
    btnRechercheProjetDuManager->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        ouvrirFenetreAjouterSupprimer(
            "Retirer un programmeur d'un manager",
            "Retirer le programmeur:",
            "au manager:",
            "retirer",
            gestionnaireEmployes.getManagers(),
            [this](const string& lastName, const string& prog) {
                return this->gestionnaireEmployes.supprimerProgAuManager(lastName, prog);
            }
        );
    });
    griller->Add(btnRechercheProjetDuManager, 0, wxEXPAND | wxALL, 5);

    wxButton* btnRechercheProgDuManager = new wxButton(currentPanel, -1, "Retirer un projet d'un programmeur");
    btnRechercheProgDuManager->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        ouvrirFenetreAjouterSupprimer(
            "Retirer un projet d'un programmeur",
            "Retirer le projet:",
            "au programmeur:",
            "retirer",
            gestionnaireEmployes.getProgrammeurs(),
            [this](const string& lastName, const string& projet) {
                return this->gestionnaireEmployes.supprimerProjetAuProg(lastName, projet);
            }
        );
    });
    griller->Add(btnRechercheProgDuManager, 0, wxEXPAND | wxALL, 5);

    // Ajuster la taille
    currentPanel->SetSizer(griller);
    currentPanel->Layout();
    currentPanel->Show(true);
    this->Maximize(true);
    this->Layout();
    this->Refresh();
}

/**
 * Methode avec vector de type générique
 * Prend en parametres les strings pour l'affichage et un fonction pour traiter l'action
 */
template <typename T>
void InterfaceController::ouvrirFenetreAjouterSupprimer(
    const wxString& titreFenetre, 
    const wxString& texteLabel1, 
    const wxString& texteLabel2,
    const wxString& action,
    const vector<T>& employes,
    function<void(const string&, const string&)> fonctionTraitement
) {
    // Créer une nouvelle fenêtre pour la recherche
    wxFrame* searchFrame = new wxFrame(
        this, 
        wxID_ANY, 
        titreFenetre, 
        wxDefaultPosition, 
        wxSize(400, 250), 
        wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)
    );

    wxPanel* panneau = new wxPanel(searchFrame);
    wxStaticText* label1 = new wxStaticText(panneau, wxID_ANY, texteLabel1, wxPoint(10, 20));
    wxTextCtrl* propriete = new wxTextCtrl(panneau, wxID_ANY, "", wxPoint(200, 18), wxSize(150, 25));
    wxStaticText* label2 = new wxStaticText(panneau, wxID_ANY, texteLabel2, wxPoint(10, 70));

    // Créer un dropdown pour les noms
    wxArrayString nomsArray;
    for (auto& item : employes) {
        const string lastName = item.getLastName(); 
        nomsArray.Add(lastName); // Ajouter les noms des employés
    }
    wxChoice* dropdownNoms = new wxChoice(panneau, wxID_ANY, wxPoint(200, 68), wxSize(150, 25), nomsArray);

    // Ajouter un bouton pour l'action
    wxButton* btnProcess = new wxButton(panneau, wxID_ANY, action, wxPoint(150, 150), wxSize(100, 30));

    // Connecter le bouton
    btnProcess->Bind(wxEVT_BUTTON, [this, propriete, action, dropdownNoms, fonctionTraitement](wxCommandEvent& event) {
        
        // Récupérer le lastName sélectionné dans le dropdown
        wxString nomSelectionner = dropdownNoms->GetStringSelection();
        try {
            fonctionTraitement(nomSelectionner.ToStdString(), propriete->GetValue().ToStdString());
            // Afficher succès
            wxMessageBox(propriete->GetValue() + " " + action, "Résultat", wxOK | wxICON_INFORMATION);
        } catch(string message) {
            // Afficher erreur
            wxMessageBox(message, "Erreur", wxNO | wxICON_ERROR);
        }
    });

    // Afficher la fenêtre de recherche
    searchFrame->Show(true);
}

void InterfaceController::OnClose(wxCloseEvent& event) {
    // Afficher une boîte de dialogue pour demander confirmation
    int result = wxMessageBox(
        "Voulez-vous sauvegarder les fichiers avant de fermer l'application ?", 
        "Confirmer", 
        wxYES_NO | wxCANCEL | wxICON_QUESTION);

    if (result == wxYES) {
        event.Veto();
        // Créer un event et appeler la méthode sauvegarder avec le paramètre `true`
        wxCommandEvent sauvegardeEvent(wxEVT_BUTTON);
        sauvegarder(sauvegardeEvent);        
    } else if (result == wxNO) {
        event.Skip(); // Fermer l'app
    } else {
        // Annuler la fermeture
        event.Veto();
    }
}
