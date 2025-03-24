/*

Author: Yoann Deguire

Description: Definition of the Graphical Interface Manager
------------
*/

#ifndef INTERFACE_CONTROLLER_H
#define INTERFACE_CONTROLLER_H

#include <wx/wx.h>
#include "EmployeeController.h"

class InterfaceController : public wxFrame {
public:
    InterfaceController();  // Constructor
    enum {
        ID_MENU_READ,
        ID_MENU_SAVE,
        ID_MENU_SEARCH = wxID_HIGHEST + 1,
        ID_MENU_ADD,
        ID_MENU_DELETE,
        ID_MENU_ABOUT
    };
private:
    EmployeeController employeeManager; // Member of type EmployeeController

    wxTextCtrl* txtManager;       // Text box for the Managers file
    wxTextCtrl* txtProgrammer;    // Text box for the Programmers file
    wxPanel* currentPanel = nullptr;
    
    void read(wxCommandEvent& event); // Adds the menu to the bar
    void showAbout(wxCommandEvent& event); // Displays the "About" dialog
    void save(wxCommandEvent& event); // Adds the menu to the bar
    void addMenu(); // Adds the menu to the bar
    void validateFile(const wxString& managerFile, const wxString& programmerFile);  // Validates paths and files for managers and programmers
    void saveFile(const wxString& managerFile, const wxString& programmerFile); // Writes the files
    void showMainMenu();  // Displays the main menu
    void search(wxCommandEvent& event); // Search menu
    void openSearchWindow(
        const wxString& windowTitle, 
        const wxString& labelText, 
        function<string(const string&)> processingFunction
    );
    void add(wxCommandEvent& event); // Menu to add an employee property
    void delete(wxCommandEvent& event); // Menu to delete an employee property
    template <typename T>
    void openAddDeleteWindow(
        const wxString& windowTitle, 
        const wxString& labelText1, 
        const wxString& labelText2,
        const wxString& action,
        const vector<T>& employees,
        function<void(const string&, const string&)> processingFunction
    );
    void OnClose(wxCloseEvent& event); // Overrides wxWidget's OnClose
};

#endif