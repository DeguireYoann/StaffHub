/*

IFT1169 - TP3 A24 -

Auteur: Yoann Deguire - decembre 2024

Description: Travail pratique #3
------------
*/

#include "gestionnaireInterface.h"
#include <wx/wx.h>

class TP3A24App : public wxApp {
public:
    virtual bool OnInit() {
        InterfaceController* gestionnaireInterface = new InterfaceController();
        gestionnaireInterface->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(TP3A24App);
