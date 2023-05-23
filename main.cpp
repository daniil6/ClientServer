#include "MainFrame.h"

#include <wx/app.h>

class wxMiniApp : public wxApp
{
public:
    bool OnInit() override
    {
        return (new CMainFrame)->Show();
    }
};

IMPLEMENT_APP(wxMiniApp)