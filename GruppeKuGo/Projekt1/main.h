/*/////////////////////////////////////////////////
////                Gruppe KuGo             ////
////   Andrea Kuchar          Bob Godar    ////
////      10389540             10708175   ////
/////////////////////////////////////////////*/



#ifndef __main__
#define __main__

// wx.h ist der "Hauptheader"
#include <wx/wx.h>
#include "gui1.h"


// Deklaration der Applikationsklasse ; OnInit() ist wie eine klassische main() Funktion
class MainApp : public wxApp
{
	public:
		virtual bool OnInit();
};


// Deklaration der globalen statischen Funktion wxGetApp() ; Ansonsten ist keine Visualiserung möglich 
DECLARE_APP(MainApp)


// Klassischer Teil eines Header
// Klasse des Hauptfensters
class MainFrame : public MainFrameBase
{
	public:
		MainFrame( wxWindow *parent );
		MainFrame( const wxString &title, const wxPoint &pos, const wxSize &size );
		virtual ~MainFrame();
	protected:
		
		// Event Handler  
		virtual void OnCloseFrame( wxCloseEvent& event );
		virtual void OnExitClick( wxCommandEvent& event );
};


// Klasse des Ausgabefensters
class mf : public mfb
{
	public:
		mf( wxWindow *parent );
		mf( const wxString &title, const wxPoint &pos, const wxSize &size );
		virtual ~mf();
	protected:
		
		// Event Handler  
		virtual void OnCloseFrame( wxCloseEvent& event );
		virtual void OnExitClick( wxCommandEvent& event );
};


#endif //__main__
