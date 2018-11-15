/*/////////////////////////////////////////////////
////                Gruppe KuGo             ////
////   Andrea Kuchar          Bob Godar    ////
////      10389540             10708175   ////
/////////////////////////////////////////////*/

#include "gui1.h"
#include "wx/wx.h"
#include "wx/wxprec.h"
#include <wx/textfile.h>
#include "clsol.h"
#include "vector"
#include <wx/clipbrd.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/gdicmn.h>
#include <wx/wfstream.h>


std::string newPuzzle ="";
long wexeb1 = wxNewId();

wxTextCtrl *eb ;


// Implementierung der main() des Ausgabefensters
mfb::mfb( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{

	this->SetSize(1000,1000);
	this->Centre( wxBOTH );
	
}


// Implementierung der main() des Hauptfensters
MainFrameBase::MainFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{

	long wex = wxNewId();
	long wexb1 = wxNewId();
	long wexb2 = wxNewId();
	
	this->SetSize(1000,1000);
	
	// Fenstererweiterungen(Menu, Buttons, Textfeld etc...)
	CreateStatusBar(3);
    SetStatusText(wxT("Sat Solving"), 0); 	
	menuBar = new wxMenuBar();
	menu = new wxMenu();
	menu->Append(wxID_OPEN,_T("&Open"));
	menu->Append(wxID_OPEN,_T("&New"));
	menu->AppendSeparator(); 
	menu->Append(wex,_T("E&xit"));
	menuBar->Append(menu,_T("&Puzzle")); 
	SetMenuBar(menuBar); 
	
	wxButton *wbOP = new wxButton(this, wexb1, _T("Open and solve a Puzzle"),wxPoint(50, 200),wxSize(220,220), 0);
	wxButton *wbOP1 = new wxButton(this, wexb2, _T("Solve new a Puzzle"),wxPoint(50, 400),wxSize(220,220), 0);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	vbox->Add(wexb1,1,wxEXPAND | wxALL,5);
	vbox->Add(wexb2,1,wxEXPAND | wxALL,5);
	eb = new wxTextCtrl(this,wexeb1," Enter a new Puzzle",wxPoint(400,80), wxSize(500,500),  wxTE_MULTILINE | wxTE_RICH |wxHSCROLL, wxDefaultValidator,wxTextCtrlNameStr);
	vbox->Add(wexeb1,1,wxEXPAND | wxALL,5);
	this->SetSizer(vbox);
	
	
	// Events an eine Funktion knüpfen
	this->Bind(wxEVT_COMMAND_BUTTON_CLICKED,&MainFrameBase::NewFile, this, wexb2);
	this->Bind(wxEVT_COMMAND_BUTTON_CLICKED,&MainFrameBase::OpenFile, this, wexb1);
	this->Bind(wxEVT_MENU,&MainFrameBase::OpenFile, this, wxID_OPEN);
	this->Bind(wxEVT_MENU,&MainFrameBase::OnClose, this, wex);
    
	
	this->Centre( wxBOTH );
	
}


// Eingebenes Puzzle wird eingelesen und gelöst
void MainFrameBase::NewFile(wxCommandEvent& WXUNUSED(event)){
	
	wxString dir ; 
	wxString filename;
	wxFileDialog *OD = new wxFileDialog(this, _("Select the formular.cnf path"), "", "","XYZ files (*.cnf)|*.cnf", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
	eb->Refresh();
	if (OD->ShowModal() == wxID_CANCEL)
	   return;     
    
	dir = OD->GetDirectory() ; 
	std::string sdir = dir.ToStdString();
	std::string sfilename = "Temp.txt";
	eb->SaveFile(_T("Temp.txt"),0);
	std::vector<int> pb = clsol(sfilename,sdir);
	if (pb.empty()) {
	   wxMessageBox("Error : Empty result from picosat", "ERROR", wxOK | wxICON_INFORMATION);
	   return ;
	} 
	
	 // Falls das Puzzle erfolgreich gelöst wurde, wird es durch ColPanel grafisch ausgegeben
	 mfb(NULL).ColPanel(pb);  
	
	
	return;
}


// Fenster schließen 
void MainFrameBase::OnClose(wxCommandEvent& WXUNUSED(event)) {
	Destroy();
}


// Öffnen einer .txt Datei
void MainFrameBase::OpenFile(wxCommandEvent& WXUNUSED(event))
{
	wxString  filename;
	wxString wxdir ;
	wxFileDialog *OpenDialog = new wxFileDialog(this, _("Open a Puzzle"), "", "","XYZ files (*.txt)|*.txt", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
	OpenDialog->ShowModal();
	if (OpenDialog->ShowModal() == wxID_OK) 
	{  
	   wxdir.clear(); 
	   filename.clear();
	   filename = OpenDialog->GetPath();
	   wxdir = OpenDialog->GetDirectory();
	} 
	else {
	   return;   
	}
	
    // Aufruf der clsol() Funktion um das Puzzle zu lösen 	
	std::string dir = wxdir.ToStdString();
	std::string sfilename = filename.ToStdString();
	std::vector<int> pb = clsol(sfilename,dir);
	if (pb.empty()) {
	   wxMessageBox("Error : Empty result from picosat", "ERROR", wxOK | wxICON_INFORMATION);
	   return ;
	} 
	
	// Falls das Puzzle erfolgreich gelöst wurde, wird es durch ColPanel grafisch ausgegeben
	mfb(NULL).ColPanel(pb);  
  
return;


}


// Zeichnen der Puzzlelösung in einem neuen Fenster
void mfb::ColPanel(std::vector<int> pb){	
	
	long w = wxNewId();
	wxWindow *mf1 = new mfb( NULL,  w, wxEmptyString,  wxDefaultPosition,  wxSize( 500,300 ),  wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL); 
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);	
    wxFlexGridSizer *fgs = new wxFlexGridSizer(1, 2, 0,0); 
    fgs->AddGrowableRow(0) ;
    fgs->AddGrowableCol(0);
    int r = pb[pb.size()-1]; 
    int c = pb[pb.size()-2];
    int l = r*c;
    wxGridSizer *gs = new wxGridSizer(r, c, 0,0);
	
	
    for (int i = 1; i<=l; i++) { 
		int k = pb[i]; 
		wxPanel *xpanel = new wxPanel(mf1, wxID_ANY,wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
		switch (k) {
		   case 1 : {
		      xpanel->SetBackgroundColour(*wxBLACK);
			  break;
		   }
		   case 0 : {
		      xpanel->SetBackgroundColour(*wxWHITE);
			  break;
		   }
		   case 2 : {
		      xpanel->SetBackgroundColour(*wxLIGHT_GREY);
			  break;
		   }
           default : {
		      break;
		   }
		} 
		gs->Add(xpanel,1,wxEXPAND | wxALL,5);
	}
    fgs->Add(gs,1,wxEXPAND| wxALL, 5 );
    vbox->Add(fgs,1,wxEXPAND | wxALL, 5);
    mf1->SetSizer(vbox);
    mf1->Show();
	
return;
}


MainFrameBase::~MainFrameBase()
{
	
} 
mfb::~mfb()
{
	
} 
