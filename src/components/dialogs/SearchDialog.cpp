// SearchDialog.cpp
#include "SearchDialog.h"

SearchDialog::SearchDialog(wxWindow* parent, 
                         const wxString& title,
                         const wxString& label,
                         std::function<std::string(const std::string&)> processor)
    : wxDialog(parent, wxID_ANY, title), processor_(processor) {
    
    wxPanel* panel = new wxPanel(this);
    new wxStaticText(panel, wxID_ANY, label, {10, 20});
    wxTextCtrl* input = new wxTextCtrl(panel, wxID_ANY, "", {150, 18}, {200, 25});
    
    wxButton* btn = new wxButton(panel, wxID_OK, "Valider", {150, 60});
    btn->Bind(wxEVT_BUTTON, [this, input](wxCommandEvent&) {
        std::string result = processor_(input->GetValue().ToStdString());
        wxMessageBox(result, "Résultat", wxOK, this);
    });
}