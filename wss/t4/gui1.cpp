///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

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
///////////////////////////////////////////////////////////////////////////

MainFrameBase::MainFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{

	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	CreateStatusBar(3);
    SetStatusText(wxT("Ready"), 0); 
	menuBar = new wxMenuBar();
	menu = new wxMenu();
	//wxMenuItem* menuFileExit;
	menu->Append(wxID_OPEN,_T("&Open"));
	//menuFileExit = new wxMenuItem( m_menuFile, wxID_EXIT, wxString( _T("&Exit") ) + wxT('\t') + wxT("Alt+X"), wxEmptyString, wxITEM_NORMAL );
	//m_menuFile->Append( menuFileExit );
	menu->AppendSeparator(); 
	menu->Append(wxID_ANY,_T("E&xit"));
	menuBar->Append(menu,_T("&Puzzle")); 
	
	SetMenuBar(menuBar); 
	this->Bind(wxEVT_MENU,&MainFrameBase::OpenFile, this, wxID_OPEN);
	
/*
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBase::OnCloseFrame ) );
	//this->Connect( wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnExitClick ) ); 
	 * */
}
void MainFrameBase::OpenFile(wxCommandEvent& WXUNUSED(event))
{

		wxString  CurrentDocPath;
		wxString wxdir ;
		wxMessageBox("You have selected Open", "Your selection", wxOK | wxICON_INFORMATION);
		wxFileDialog *OpenDialog = new wxFileDialog(this, _("Open a Puzzle"), "", "","XYZ files (*.txt)|*.txt", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
	    OpenDialog->ShowModal();
       if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "cancel"
	   {  
		  wxdir.clear(); 
		  CurrentDocPath.clear();
		  CurrentDocPath = OpenDialog->GetPath();
		  wxdir = OpenDialog->GetDirectory();

	   } 
	   else {
		   return;   
		}
		
		std::string dir = wxdir.ToStdString();
       std::string path = CurrentDocPath.ToStdString();
	   std::vector<int> pb = clsol(path,dir);
	   if (pb.empty()) {
		   wxMessageBox("Error : Empty result from picosat", "ERROR", wxOK | wxICON_INFORMATION);
		   return ;
	   } 
       ColPanel(pb,this);
return;


}
void MainFrameBase::ColPanel(std::vector<int> pb,wxWindow *mf){	
 wxWindow *mf1 = new MainFrameBase(NULL); 
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);	
 wxFlexGridSizer *fgs = new wxFlexGridSizer(1, 2, 1,1); 
 fgs->AddGrowableRow(0) ;
fgs->AddGrowableCol(0);
int r = pb[pb.size()-1]; 
int c = pb[pb.size()-2];
int l = r*c;
std::cout <<"c : "<<r<<std::endl;
std::cout <<"pb size -2 : "<<l<<std::endl;
wxGridSizer *gs = new wxGridSizer(r, c, 8,8);
for (int i = 1; i<=l; i++) { 
	    std::cout <<"c : "<<pb[i]<<std::endl;
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
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBase::OnCloseFrame ) );
	this->Disconnect( wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnExitClick ) );
	
} 
