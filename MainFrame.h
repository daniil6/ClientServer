#ifndef CMAINFRAME_H
#define CMAINFRAME_H

// #include <wx/tglbtn.h>
#include <thread>
#include <wx/wx.h>

// #include "link/tcpclient.hpp"
// #include "link/tcpserver.hpp"
// #include "link/udpclient.hpp"
// #include "link/udpserver.hpp"

#include <win/socket/tcpclient.h>
#include <win/socket/tcpserver.h>

class CMainFrame : public wxFrame
{
private:
    enum { ID_CLIENT = wxID_HIGHEST + 1, ID_SERVER, ID_UDP, ID_TCP, ID_DISCONNECT };

    int m_idLink;
    int m_idProtocol;
    int m_idArchitect;

    bool m_resolutionLink;
    wxString m_labelLink;

    // CBaseLink* m_link;

    CTCPBase* m_links;

    wxButton* m_btnLink;
    wxTextCtrl* m_txtPort;
    wxTextCtrl* m_txtSend;
    wxTextCtrl* m_txtAddress;
    wxTextCtrl* m_txtReceive;

    wxRadioButton* m_btnUdp;
    wxRadioButton* m_btnTcp;
    wxRadioButton* m_btnClient;
    wxRadioButton* m_btnServer;

    wxStaticBitmap* m_indicateLink;

    std::thread* thrLink;
    void FuncServer();
    void FuncClient();
    void FuncReceiveMessage(const uint8_t* data, const int& size);

    void Link();
    void Process();
    void SwitchLinkAndProtocol();
    void EnablePanelAtLink(wxString labelLink, bool enablePanel, wxIcon ico);
    void EnablePanelAtSwitch(CTCPBase* link, bool enableAddress, wxString labelLink);

    void OnSend(wxCommandEvent& event);
    void OnLink(wxCommandEvent& event);
    void OnSwitchLink(wxCommandEvent& event);
    void OnSwitchProtocol(wxCommandEvent& event);

public:
    CMainFrame(wxWindow* parent = nullptr);
    ~CMainFrame();
};

#endif // CMAINFRAME_H