/*

Author: Yoann Deguire

Description: Graphical Interface Manager
------------
*/
#include "InterfaceController.h"
#include "FileReader.h"
#include "Programmer.h"
#include "Manager.h"

using namespace std;

InterfaceController::InterfaceController()
    : wxFrame(nullptr, -1, "Load files", wxDefaultPosition, wxDefaultSize) {
    // Create main panel
    currentPanel = new wxPanel(this);
    this->SetTitle("Configuration");
    this->Maximize(true);

    // Create interface elements
    wxStaticText* labelManager = new wxStaticText(currentPanel, -1, "Managers file:", wxPoint(10, 20));
    wxTextCtrl* managerFile = new wxTextCtrl(currentPanel, -1, "./Data/managers.csv", wxPoint(150, 20), wxSize(250, 25));

    wxStaticText* labelProgrammer = new wxStaticText(currentPanel, -1, "Programmers file:", wxPoint(10, 60));
    wxTextCtrl* programmerFile = new wxTextCtrl(currentPanel, -1, "./Data/Programmers.csv", wxPoint(150, 60), wxSize(250, 25));

    wxButton* btnProcess = new wxButton(currentPanel, -1, "Continue", wxPoint(150, 100), wxSize(100, 30));

    // Connect button
    btnProcess->Bind(wxEVT_BUTTON, [this, managerFile, programmerFile](wxCommandEvent&) {
        this->validateFile(managerFile->GetValue(), programmerFile->GetValue());
    });
    Bind(wxEVT_CLOSE_WINDOW, &InterfaceController::OnClose, this);
    addMenu();
}

void InterfaceController::read(wxCommandEvent& event) {
   // Create main panel
    if (currentPanel) {
        currentPanel->Destroy();  // Destroy old panel
    }
    currentPanel = new wxPanel(this);
    this->SetTitle("Read");

    // Create interface elements
    wxStaticText* labelManager = new wxStaticText(currentPanel, -1, "Managers file:", wxPoint(10, 20));
    wxTextCtrl* managerFile = new wxTextCtrl(currentPanel, -1, "./Data/managers.csv", wxPoint(150, 20), wxSize(250, 25));

    wxStaticText* labelProgrammer = new wxStaticText(currentPanel, -1, "Programmers file:", wxPoint(10, 60));
    wxTextCtrl* programmerFile = new wxTextCtrl(currentPanel, -1, "./Data/Programmers.csv", wxPoint(150, 60), wxSize(250, 25));

    wxButton* btnProcess = new wxButton(currentPanel, -1, "Continue", wxPoint(150, 100), wxSize(100, 30));

    // Connect button
    btnProcess->Bind(wxEVT_BUTTON, [this, managerFile, programmerFile](wxCommandEvent&) {
        this->validateFile(managerFile->GetValue(), programmerFile->GetValue());
    });

    currentPanel->Layout();
    currentPanel->Show(true);
    this->Maximize(true);
    this->Layout();
    this->Refresh();
}

void InterfaceController::save(wxCommandEvent& event) {
    if (currentPanel) {
        currentPanel->Destroy();  // Destroy old panel
    }
    currentPanel = new wxPanel(this);
    this->SetTitle("Save");

    // Create interface elements
    wxStaticText* labelManager = new wxStaticText(currentPanel, -1, "Managers file:", wxPoint(10, 20));
    wxTextCtrl* managerFile = new wxTextCtrl(currentPanel, -1, "./Data/managers_new.csv", wxPoint(150, 20), wxSize(250, 25));

    wxStaticText* labelProgrammer = new wxStaticText(currentPanel, -1, "Programmers file:", wxPoint(10, 60));
    wxTextCtrl* programmerFile = new wxTextCtrl(currentPanel, -1, "./Data/Programmers_new.csv", wxPoint(150, 60), wxSize(250, 25));

    wxButton* btnProcess = new wxButton(currentPanel, -1, "Save", wxPoint(150, 100), wxSize(100, 30));

    btnProcess->Bind(wxEVT_BUTTON, [this, managerFile, programmerFile, &event](wxCommandEvent&) {
        this->saveFile(managerFile->GetValue(), programmerFile->GetValue());
    });

    currentPanel->Layout();
    currentPanel->Show(true);
    this->Maximize(true);
    this->Layout();
    this->Refresh();
    }

void InterfaceController::showAbout(wxCommandEvent& event) {
    wxDialog* aboutDialog = new wxDialog(this, wxID_ANY, "About", wxDefaultPosition, wxSize(400, 200));

    wxPanel* panel = new wxPanel(aboutDialog);

    wxStaticText* authorTitle = new wxStaticText(panel, wxID_ANY, "Author: Yoann Deguire", wxPoint(20, 20));
    authorTitle->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    wxStaticText* descriptionText = new wxStaticText(panel, wxID_ANY, 
        "Work done for TP3 of course IFT-1169 during Fall 2024 semester.",
        wxPoint(20, 60), wxSize(360, 80));

    // Add OK button to close
    wxButton* btnClose = new wxButton(panel, wxID_OK, "OK", wxPoint(150, 150), wxSize(100, 30));

    // Connect OK button
    btnClose->Bind(wxEVT_BUTTON, [aboutDialog](wxCommandEvent&) {
        aboutDialog->EndModal(wxID_OK);
    });

    aboutDialog->ShowModal();
    // Free memory after closing
    aboutDialog->Destroy();
}

void InterfaceController::addMenu() {
    wxMenu* fileMenu = new wxMenu;
    wxMenu* menu = new wxMenu;

    // Add items to fileMenu
    fileMenu->Append(ID_MENU_READ, "Read");
    fileMenu->Append(ID_MENU_SAVE, "Save");

    // Add items to menu
    menu->Append(ID_MENU_SEARCH, "Search");
    menu->Append(ID_MENU_ADD, "Add");
    menu->Append(ID_MENU_DELETE, "Delete");
    menu->Append(ID_MENU_ABOUT, "About");

    // Create menu bar and add menu
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(fileMenu, "File");
    menuBar->Append(menu, "Menu");

    // Add menu bar to window
    SetMenuBar(menuBar);

    // Connect buttons for fileMenu
    Bind(wxEVT_MENU, &InterfaceController::read, this, ID_MENU_READ);
    Bind(wxEVT_MENU, &InterfaceController::save, this, ID_MENU_SAVE);

    // Connect buttons for menu
    Bind(wxEVT_MENU, &InterfaceController::search, this, ID_MENU_SEARCH);
    Bind(wxEVT_MENU, &InterfaceController::add, this, ID_MENU_ADD);
    Bind(wxEVT_MENU, &InterfaceController::delete, this, ID_MENU_DELETE);
    Bind(wxEVT_MENU, &InterfaceController::showAbout, this, ID_MENU_ABOUT);
}

void InterfaceController::validateFile(const wxString& managerFile, const wxString& progFile) {
    // If a file is missing, show message
    if (managerFile.IsEmpty() || progFile.IsEmpty()) {
        wxMessageBox("Please validate both fields before continuing.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    // Use FileReader class to set paths
    FileReader reader;
    reader.setManagerFilePath(managerFile.ToStdString());
    reader.setProgrammerFilePath(progFile.ToStdString());
    // Validate files
    const bool filesValid = reader.validateFiles();

    /*
        If valid, create vectors
        Read files (list implementation)
        Sort files
    */
    if(filesValid) {
        vector<Manager> managers;
        vector<Programmer> programmers;

        reader.readManagerFile(managers);
        reader.readProgrammerFile(programmers);

        sort(managers.begin(), managers.end());
        sort(programmers.begin(), programmers.end());

       // Call addManager for each manager
        for (auto& manager : managers) {
            employeeManager.addManager(manager);
        }

        // Call addProgrammer for each programmer
        for (auto& programmer : programmers) {
            employeeManager.addProgrammer(programmer);
        }

        showMainMenu();
    } else {
        // If invalid, show error
        wxMessageBox("Invalid file.", "Error", wxOK | wxICON_ERROR);
    }
}

void InterfaceController::saveFile(const wxString& managerFile, const wxString& progFile) {
    // If a file is missing, show message
    if (managerFile.IsEmpty() || progFile.IsEmpty()) {
        wxMessageBox("Please validate both fields before continuing.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    // Use FileReader class to set paths
    FileReader reader;
    reader.setManagerFilePath(managerFile.ToStdString());
    reader.setProgrammerFilePath(progFile.ToStdString());

    // Write files
    reader.writeManagerFile(this->employeeManager.getManagers());
    reader.writeProgrammerFile(this->employeeManager.getProgrammers());

    wxMessageBox("File Saved", "Save", wxOK | wxICON_INFORMATION);
}

void InterfaceController::showMainMenu() {
    if (currentPanel) {
        currentPanel->Destroy();  // Destroy old panel
    }

    // Create new panel if needed
    currentPanel = new wxPanel(this);

    // Update title
    this->SetTitle("Main Menu");

    // Add main buttons
    wxButton* btnSearch = new wxButton(currentPanel, -1, "Search", wxPoint(50, 20), wxSize(100, 30));
    wxButton* btnAdd = new wxButton(currentPanel, -1, "Add", wxPoint(50, 70), wxSize(100, 30));
    wxButton* btnDelete = new wxButton(currentPanel, -1, "Delete", wxPoint(50, 120), wxSize(100, 30));

    // Connect button events
    btnSearch->Bind(wxEVT_BUTTON, &InterfaceController::search, this);
    btnAdd->Bind(wxEVT_BUTTON, &InterfaceController::add, this);
    btnDelete->Bind(wxEVT_BUTTON, &InterfaceController::delete, this);

    // Adjust window size
    currentPanel->Show(true);
    this->Maximize(true);
    this->Layout();
    this->Refresh();
}

void InterfaceController::search(wxCommandEvent& event) {
    if (currentPanel) {
        currentPanel->Destroy();  // Destroy old panel
    }

    // Create new panel if needed
    currentPanel = new wxPanel(this);
    this->SetTitle("Search");

    // Create grid with 2 columns
    wxGridSizer* grid = new wxGridSizer(2, 10, 10);

    /**
     * Create different buttons
     * Bind with openSearchWindow method with props and associated method for action
     */
    wxButton* btnSearchManagerByProject = new wxButton(currentPanel, -1, "Search manager by project");
    btnSearchManagerByProject->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        openSearchWindow(
            "Search manager by project",
            "Project name:",
            [this](const string& input) {
                return this->employeeManager.managerByProject(input);
            }
        );
    });
    grid->Add(btnSearchManagerByProject, 0, wxEXPAND | wxALL, 5);

    wxButton* btnSearchManagerProjects = new wxButton(currentPanel, -1, "Search manager's projects");
    btnSearchManagerProjects->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        openSearchWindow(
            "Search manager's projects",
            "Manager name:",
            [this](const string& input) {
                return this->employeeManager.displayManagerProjects(input);
            }
        );
    });
    grid->Add(btnSearchManagerProjects, 0, wxEXPAND | wxALL, 5);

    wxButton* btnSearchManagerProgrammers = new wxButton(currentPanel, -1, "Search programmers by manager");
    btnSearchManagerProgrammers->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        openSearchWindow(
            "Search programmers by manager",
            "Manager name:",
            [this](const string& input) {
                return this->employeeManager.associatedProgrammers(input);
            }
        );
    });
    grid->Add(btnSearchManagerProgrammers, 0, wxEXPAND | wxALL, 5);

    wxButton* btnSearchProgrammerManager = new wxButton(currentPanel, -1, "Search programmer's manager");
    btnSearchProgrammerManager->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        openSearchWindow(
            "Search programmer's manager",
            "Programmer name:",
            [this](const string& input) {
                return this->employeeManager.programmerManager(input);
            }
        );
    });
    grid->Add(btnSearchProgrammerManager, 0, wxEXPAND | wxALL, 5);

    wxButton* btnSearchProgrammerProjects = new wxButton(currentPanel, -1, "Search projects by programmer");
    btnSearchProgrammerProjects->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        openSearchWindow(
            "Search projects by programmer",
            "Programmer name:",
            [this](const string& input) {
                return this->employeeManager.displayProgrammerProjects(input);
            }
        );
    });
    grid->Add(btnSearchProgrammerProjects, 0, wxEXPAND | wxALL, 5);
    
    wxButton* btnSearchProjectProgrammers = new wxButton(currentPanel, -1, "Search programmers by project");
    btnSearchProjectProgrammers->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        openSearchWindow(
            "Search programmers by project",
            "Project name:",
            [this](const string& input) {
                return this->employeeManager.programmersByProject(input);
            }
        );
    });
    grid->Add(btnSearchProjectProgrammers, 0, wxEXPAND | wxALL, 5);

    // Adjust size
    currentPanel->SetSizer(grid);
    currentPanel->Layout();
    currentPanel->Show(true);
    this->Maximize(true);
    this->Layout();
    this->Refresh();
}

/**
 * Method to open search window
 * Takes display strings and processing function as parameters
 */
void InterfaceController::openSearchWindow(
    const wxString& windowTitle, 
    const wxString& labelText, 
    function<string(const string&)> processingFunction
) {
    // Create new search window
    wxFrame* frame = new wxFrame(
        this, 
        wxID_ANY, 
        windowTitle, 
        wxDefaultPosition, 
        wxSize(400, 200), 
        wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)
    );

    wxPanel* panel = new wxPanel(frame);

    wxStaticText* label = new wxStaticText(panel, wxID_ANY, labelText, wxPoint(10, 20));

    wxTextCtrl* inputText = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(200, 18), wxSize(150, 25));

    // Add search button
    wxButton* btnProcess = new wxButton(panel, wxID_ANY, "Search", wxPoint(150, 100), wxSize(100, 30));

    // Connect button to action
    btnProcess->Bind(wxEVT_BUTTON, [processingFunction, inputText](wxCommandEvent& event) {
        string result = processingFunction(inputText->GetValue().ToStdString());
        wxMessageBox(wxString(result), "Result", wxOK | wxICON_INFORMATION);
    });

    // Show search window
    frame->Show(true);
}

void InterfaceController::add(wxCommandEvent& event) {
    if (currentPanel) {
        currentPanel->Destroy();  // Destroy old panel
    }

    // Create new panel if needed
    currentPanel = new wxPanel(this);
    this->SetTitle("Add");

    // Create grid with 2 columns
    wxGridSizer* grid = new wxGridSizer(2, 10, 10);

    /**
     * Create different buttons
     * Bind with openAddDeleteWindow method with props and associated method for action
     */
    wxButton* btnAddProjectToManager = new wxButton(currentPanel, -1, "Add project to manager");
    btnAddProjectToManager->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        openAddDeleteWindow(
            "Add project to manager",
            "Project to add:",
            "to manager:",
            "add",
            employeeManager.getManagers(),
            [this](const string& lastName, const string& project) {
                return this->employeeManager.addProjectToManager(lastName, project);
            }
        );
    });
    grid->Add(btnAddProjectToManager, 0, wxEXPAND | wxALL, 5);

    wxButton* btnAddProgrammerToManager = new wxButton(currentPanel, -1, "Add programmer to manager");
    btnAddProgrammerToManager->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        openAddDeleteWindow(
            "Add programmer to manager",
            "Programmer to add:",
            "to manager:",
            "add",
            employeeManager.getManagers(),
            [this](const string& lastName, const string& prog) {
                return this->employeeManager.addProgrammerToManager(lastName, prog);
            }
        );
    });
    grid->Add(btnAddProgrammerToManager, 0, wxEXPAND | wxALL, 5);

    wxButton* btnAddProjectToProgrammer = new wxButton(currentPanel, -1, "Add project to programmer");
    btnAddProjectToProgrammer->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        openAddDeleteWindow(
            "Add project to programmer",
            "Project to add:",
            "to programmer:",
            "add",
            employeeManager.getProgrammers(),
            [this](const string& lastName, const string& project) {
                return this->employeeManager.addProjectToProgrammer(lastName, project);
            }
        );
    });
    grid->Add(btnAddProjectToProgrammer, 0, wxEXPAND | wxALL, 5);

    // Adjust size
    currentPanel->SetSizer(grid);
    currentPanel->Layout();
    currentPanel->Show(true);
    this->Maximize(true);
    this->Layout();
    this->Refresh();
}

void InterfaceController::delete(wxCommandEvent& event) {
    if (currentPanel) {
        currentPanel->Destroy();  // Destroy old panel
    }

    // Create new panel if needed
    currentPanel = new wxPanel(this);
    this->SetTitle("Remove");

    // Create grid with 2 columns
    wxGridSizer* grid = new wxGridSizer(2, 10, 10);

    /**
     * Create different buttons
     * Bind with openAddDeleteWindow method with props and associated method for action
     */
    wxButton* btnRemoveProjectFromManager = new wxButton(currentPanel, -1, "Remove project from manager");
    btnRemoveProjectFromManager->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        openAddDeleteWindow(
            "Remove project from manager",
            "Project to remove:",
            "from manager:",
            "remove",
            employeeManager.getManagers(),
            [this](const string& lastName, const string& project) {
                return this->employeeManager.removeProjectFromManager(lastName, project);
            }
        );
    });
    grid->Add(btnRemoveProjectFromManager, 0, wxEXPAND | wxALL, 5);

    wxButton* btnRemoveProgrammerFromManager = new wxButton(currentPanel, -1, "Remove programmer from manager");
    btnRemoveProgrammerFromManager->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        openAddDeleteWindow(
            "Remove programmer from manager",
            "Programmer to remove:",
            "from manager:",
            "remove",
            employeeManager.getManagers(),
            [this](const string& lastName, const string& prog) {
                return this->employeeManager.removeProgrammerFromManager(lastName, prog);
            }
        );
    });
    grid->Add(btnRemoveProgrammerFromManager, 0, wxEXPAND | wxALL, 5);

    wxButton* btnRemoveProjectFromProgrammer = new wxButton(currentPanel, -1, "Remove project from programmer");
    btnRemoveProjectFromProgrammer->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        openAddDeleteWindow(
            "Remove project from programmer",
            "Project to remove:",
            "from programmer:",
            "remove",
            employeeManager.getProgrammers(),
            [this](const string& lastName, const string& project) {
                return this->employeeManager.removeProjectFromProgrammer(lastName, project);
            }
        );
    });
    grid->Add(btnRemoveProjectFromProgrammer, 0, wxEXPAND | wxALL, 5);

    // Adjust size
    currentPanel->SetSizer(grid);
    currentPanel->Layout();
    currentPanel->Show(true);
    this->Maximize(true);
    this->Layout();
    this->Refresh();
}

/**
 * Method with generic type vector
 * Takes display strings and processing function as parameters
 */
template <typename T>
void InterfaceController::openAddDeleteWindow(
    const wxString& windowTitle, 
    const wxString& labelText1, 
    const wxString& labelText2,
    const wxString& action,
    const vector<T>& employees,
    function<void(const string&, const string&)> processingFunction
) {
    // Create new search window
    wxFrame* searchFrame = new wxFrame(
        this, 
        wxID_ANY, 
        windowTitle, 
        wxDefaultPosition, 
        wxSize(400, 250), 
        wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)
    );

    wxPanel* panel = new wxPanel(searchFrame);
    wxStaticText* label1 = new wxStaticText(panel, wxID_ANY, labelText1, wxPoint(10, 20));
    wxTextCtrl* property = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(200, 18), wxSize(150, 25));
    wxStaticText* label2 = new wxStaticText(panel, wxID_ANY, labelText2, wxPoint(10, 70));

    // Create dropdown for names
    wxArrayString namesArray;
    for (auto& item : employees) {
        const string lastName = item.getLastName(); 
        namesArray.Add(lastName); // Add employee last names
    }
    wxChoice* dropdownNames = new wxChoice(panel, wxID_ANY, wxPoint(200, 68), wxSize(150, 25), namesArray);

    // Add action button
    wxButton* btnProcess = new wxButton(panel, wxID_ANY, action, wxPoint(150, 150), wxSize(100, 30));

    // Connect button
    btnProcess->Bind(wxEVT_BUTTON, [this, property, action, dropdownNames, processingFunction](wxCommandEvent& event) {
        
        // Get selected lastName from dropdown
        wxString selectedName = dropdownNames->GetStringSelection();
        try {
            processingFunction(selectedName.ToStdString(), property->GetValue().ToStdString());
            // Show success
            wxMessageBox(property->GetValue() + " " + action, "Result", wxOK | wxICON_INFORMATION);
        } catch(string message) {
            // Show error
            wxMessageBox(message, "Error", wxNO | wxICON_ERROR);
        }
    });

    // Show search window
    searchFrame->Show(true);
}

void InterfaceController::OnClose(wxCloseEvent& event) {
    // Show confirmation dialog
    int result = wxMessageBox(
        "Do you want to save files before closing the application?", 
        "Confirm", 
        wxYES_NO | wxCANCEL | wxICON_QUESTION);

    if (result == wxYES) {
        event.Veto();
        // Create event and call save method with `true` parameter
        wxCommandEvent saveEvent(wxEVT_BUTTON);
        save(saveEvent);        
    } else if (result == wxNO) {
        event.Skip(); // Close app
    } else {
        // Cancel closing
        event.Veto();
    }
}