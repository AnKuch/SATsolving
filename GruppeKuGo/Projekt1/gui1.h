
/*/////////////////////////////////////////////////
////                Gruppe KuGo             ////
////   Andrea Kuchar          Bob Godar    ////
////      10389540             10708175   ////
/////////////////////////////////////////////*/



#ifndef __GUI_H__
#define __GUI_H__

#include "wx/wx.h"
#include "wx/wxprec.h"
#include <wx/textfile.h>
#include "clsol.h"
#include "vector"
#include <wx/clipbrd.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/gdicmn.h>
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
#include <wx/frame.h>



// Klasse MainFrameBase
class MainFrameBase : public wxFrame 
{
	private:

	protected:
		wxMenuBar* menuBar;
		wxMenu* menu;
		wxStatusBar* m_statusBar;
		
		// Default Definitionen von Event Handler
		virtual void OnCloseFrame( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnExitClick( wxCommandEvent& event ) { event.Skip(); }
		
	
public:
		
		// MainFrameBase ist der eigentliche Konstruktor
		MainFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		void OpenFile(wxCommandEvent& WXUNUSED(event));
		void OnClose(wxCommandEvent& WXUNUSED(event));
		void NewFile(wxCommandEvent& WXUNUSED(event));
		~MainFrameBase();
	
};


// Klasse mfb
class mfb : public wxFrame {
		private:

	protected:
		wxMenuBar* menuBar;
		wxMenu* menu;
		wxStatusBar* m_statusBar;
		
	
public:
		
		// mfb ist der eigentliche Konstruktor
		mfb( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		void ColPanel(std::vector<int> pb);
		void OnClose(wxCommandEvent& WXUNUSED(event));
		void NewFile(wxCommandEvent& WXUNUSED(event));
		~mfb();
	
};

#endif //__GUI_H__
