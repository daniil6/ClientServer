#include "MainFrame.h"

class wxMiniApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        return (new CMainFrame())->Show();
    }
};

IMPLEMENT_APP(wxMiniApp);