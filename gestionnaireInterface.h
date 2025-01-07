/*

IFT1169 - TP3 A24 -

Auteur: Yoann Deguire - decembre 2024

Description: Définition du Gestionnaire de l'interface graphique
------------
*/

#ifndef GESTIONNAIRE_INTERFACE_H
#define GESTIONNAIRE_INTERFACE_H

#include <wx/wx.h>
#include "GestionnaireEmployes.h"

class GestionnaireInterface : public wxFrame {
public:
    GestionnaireInterface();  // Constructor
    enum {
        ID_MENU_LIRE,
        ID_MENU_SAUVEGARDER,
        ID_MENU_RECHERCHER = wxID_HIGHEST + 1,
        ID_MENU_AJOUTER,
        ID_MENU_SUPPRIMER,
        ID_MENU_APROPOS
    };
private:
    GestionnaireEmployes gestionnaireEmployes; // Membre de type GestionnaireEmployes

    wxTextCtrl* txtManager;       // texte pour le fichier Managers
    wxTextCtrl* txtProgrammeur;   // texte pour le fichier Programmeurs
    wxPanel* currentPanel = nullptr;
    
    void lire(wxCommandEvent& event); // Ajoute le menu dans la bar
    void afficherPropos(wxCommandEvent& event); // Afficher le à propos
    void sauvegarder(wxCommandEvent& event); // Ajoute le menu dans la bar
    void ajouterMenu(); // Ajoute le menu dans la bar
    void validerFichier(const wxString& fichierManager, const wxString& fichierProg);  // Valide les routes et les fichiers pour managers et programmeurs
    void sauvegarderFichier(const wxString& fichierManager, const wxString& fichierProg); // Écrire les fichiers
    void afficherMenuPrincipal();  // Affiche le menu principal
    void rechercher(wxCommandEvent& event); // Menu de Recherche
    void ouvrirFenetreRecherche(
        const wxString& titreFenetre, 
        const wxString& texteLabel, 
        function<string(const string&)> fonctionTraitement
    );
    void ajouter(wxCommandEvent& event); // Menu pour ajouter une propriété a un employé
    void supprimer(wxCommandEvent& event); // Menu pour supprimer une propriété a un employé
    template <typename T>
    void ouvrirFenetreAjouterSupprimer(
        const wxString& titreFenetre, 
        const wxString& texteLabel1, 
        const wxString& texteLabel2,
        const wxString& action,
        const vector<T>& employes,
        function<void(const string&, const string&)> fonctionTraitement
    );
    void OnClose(wxCloseEvent& event); // Surchage de onClose de wxWidget
};

#endif
