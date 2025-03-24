// SearchDialog.h
#include <wx/wx.h>

class SearchDialog : public wxDialog {
    public:
        SearchDialog(wxWindow* parent, 
                    const wxString& title,
                    const wxString& label,
                    std::function<std::string(const std::string&)> handler);
    };