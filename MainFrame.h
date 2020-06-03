#ifndef CMAINFRAME_H
#define CMAINFRAME_H

#include <wx/tglbtn.h>

#include "link/client.hpp"
#include "link/server.hpp"

#include <wx/wx.h>

class CMainFrame : public wxFrame
{
private:
    enum { ID_CLIENT = wxID_HIGHEST + 1, ID_SERVER };

    bool m_resolutionLink;
    wxString m_labelLink;

    CBaseLink* m_link;

    wxButton* m_btnLink;
    wxTextCtrl* m_txtPort;
    wxTextCtrl* m_txtSend;
    wxTextCtrl* m_txtAddress;
    wxTextCtrl* m_txtReceive;
    wxRadioButton* m_btnClient;
    wxRadioButton* m_btnServer;
    wxStaticBitmap* m_indicateLink;

    void Link();
    void Process();
    void EnablePanelAtLink(wxString labelLink, bool enablePanel, wxIcon ico);
    void EnablePanelAtSwitch(CBaseLink* link, bool enableAddress, wxString labelLink);

    void OnSend(wxCommandEvent& event);
    void OnLink(wxCommandEvent& event);
    void OnSwitchLink(wxCommandEvent& event);

public:
    CMainFrame(wxWindow* parent = nullptr);
    ~CMainFrame();
};

#endif // CMAINFRAME_H