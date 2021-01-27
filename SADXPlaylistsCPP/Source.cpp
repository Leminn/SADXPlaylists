// wxWidgets "Hello World" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/listctrl.h>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include<string>
#include<vector>
#include<filesystem>

using namespace std;
namespace fs = std::filesystem;

string GetModuleDirectory()
{
    //Gets the directory of the program
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);

    string FileName = string(buffer);
    string::size_type pos = FileName.find_last_of("\\/");

    return FileName.substr(0, pos);
};

const string modulePath = GetModuleDirectory();

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame();
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnSomething(wxCommandEvent& event);
    void OnItemSelected(wxListEvent& event);
};
enum
{
    ID_Hello = 1,
    ID_Something = 2,
    ID_Drag = 3
};
wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    frame->SetSize(wxSize(1200, 720));
    return true;
}

MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, "duck")
{
    SetOwnBackgroundColour(*wxLIGHT_GREY);

    wxListView* lview = new wxListView(this, ID_Drag, wxPoint(100, 100), wxSize(400, 400));
    lview->InsertColumn(0, "epic");
    lview->InsertColumn(1, "epicccccc");

    for (const auto& entry : fs::directory_iterator(modulePath))
    {
        lview->InsertItem(0, entry.path().filename().c_str());
        lview->SetItem(0, 1, entry.path().c_str());
    }

    wxListCtrl* lctrl = new wxListCtrl(this, wxID_ANY, wxPoint(700, 300), wxSize(400, 400));
    vector<string> items = { "lol", "epic", "dsivjsdiovjoi", "blahblah", "ps3 controller" };
    for (size_t i = 0; i < items.size(); i++) {
        lctrl->InsertColumn(i, "");
        lctrl->InsertItem(i, items[i]);
    }

    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
        "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenu* menuSomething = new wxMenu;
    menuSomething->Append(ID_Something, "Somethin&g\tCtrl-F", "idkidkidk");
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    menuBar->Append(menuSomething, "&Something");
    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnSomething, this, ID_Something);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_LIST_ITEM_SELECTED, &MyFrame::OnItemSelected, this, ID_Drag);    
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
        "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

void MyFrame::OnSomething(wxCommandEvent& event) 
{
    wxMessageBox("somethingsomethingsomething",
        "something", wxOK | wxICON_INFORMATION);
    SetOwnBackgroundColour(wxColour("#FF6A00"));
    ClearBackground();
}

void MyFrame::OnItemSelected(wxListEvent& event)
{
    SetBackgroundColour(*wxBLACK);
    ClearBackground();
}