/*/////////////////////////////////////////////////
////                Gruppe KuGo             ////
////   Andrea Kuchar          Bob Godar    ////
////      10389540             10708175   ////
/////////////////////////////////////////////*/

#include "main.h"

// Initialisierung der Applikation
IMPLEMENT_APP(MainApp);


// Implementierung der "main()" Klasse für das Hauptfenster
bool MainApp::OnInit()
{
	SetTopWindow( new MainFrame( NULL ) );
	GetTopWindow()->Show();
	return true;
}


// Implementierung des Hauptfensters bzw. des Einstiegsfensters
// Es ist geschickter in der main() Funktion von MainFrameBase zu programmieren,
// da man das konkrete Fenster verändert und nicht ein Fenster-Pointer
MainFrame::MainFrame(wxWindow *parent) : MainFrameBase( parent )
{
}

MainFrame::~MainFrame()
{
}

mf::mf(wxWindow *parent) : mfb( parent )
{
}

mf::~mf()
{
}

void mf::OnCloseFrame(wxCloseEvent& event)
{
	Destroy();
}

void mf::OnExitClick(wxCommandEvent& event)
{
	Destroy();
}


void MainFrame::OnCloseFrame(wxCloseEvent& event)
{
	Destroy();
}

void MainFrame::OnExitClick(wxCommandEvent& event)
{
	Destroy();
}
