#pragma once

#include <wx/atomic.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/combobox.h>
#include <wx/frame.h>
#include <wx/listbox.h>
#include <wx/radiobut.h>
#include <wx/statbmp.h>
#include <wx/textctrl.h>

#include <win/socket/basesocket.h>

#include <queue>

class CMainFrame : public wxFrame
{
private:
    enum { ID_CLIENT = wxID_HIGHEST + 1, ID_SERVER, ID_UDP, ID_TCP, ID_DISCONNECT };

    enum { MESSAGE, CONNECTED, DISCONNECTED };

    std::queue<std::pair<int, wxString>> m_queue_process;

    bool m_link;

    bool m_focused_txt_remote_port;
    bool m_focused_txt_locale_port;

    wxString m_labelLink;

    CBaseSocket* m_architecture;

    wxButton* m_btnLink;

    wxComboBox* m_txt_address;
    wxTextCtrl* m_txt_locale_port;
    wxTextCtrl* m_txt_remote_port;

    wxTextCtrl* m_txtSend;
    wxTextCtrl* m_txtReceive;

    wxListBox* m_list_link;

    wxRadioButton* m_btnUdp;
    wxRadioButton* m_btnTcp;
    wxRadioButton* m_btnClient;
    wxRadioButton* m_btnServer;

    wxCheckBox* m_chOpenSSL;

    wxStaticBitmap* m_indicateLink;

    wxAtomicInt m_process;

    void CloseLink(const SOCKET& socket);
    void FuncReceiveMessage(const SOCKET& socket, const char* data, const int& size);

    void Process();
    void EnablePanelAtLink(const wxString& labelLink, bool enablePanel, const wxIcon& ico);
    void EnablePanelAtSwitch(CBaseSocket* link, const wxString& labelLink);

    void OnSend(wxCommandEvent& event);
    void OnLink(wxCommandEvent& event);

    void OnSwitchMode(wxCommandEvent& event);

    void OnIdle(wxIdleEvent& event);

    void OnSetFocusRemotePort(wxFocusEvent& event);
    void OnSetFocusLocalePort(wxFocusEvent& event);

    void OnClose(wxCloseEvent& event);

public:
    CMainFrame(wxWindow* parent = nullptr);
    ~CMainFrame() override;
};