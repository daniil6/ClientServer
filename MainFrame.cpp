#include "MainFrame.h"

#include <wx/gbsizer.h>
#include <wx/sizer.h>
#include <wx/valnum.h>

#include <win/socket/tcpclient.h>
#include <win/socket/tcpserver.h>
#include <win/socket/udpclient.h>
#include <win/socket/udpserver.h>

#define DEF_RECT wxDefaultPosition, wxDefaultSize
#define MESSAGE_RECT wxDefaultPosition, wxSize(250, 120)

CMainFrame::CMainFrame(wxWindow* parent)
    : wxFrame(parent, wxID_ANY, wxT("Client Server"))
{
    this->SetIcon(wxICON(link));
    this->SetBackgroundColour(*wxWHITE);

    m_link = false;
    m_focused_txt_remote_port = false;
    m_focused_txt_locale_port = false;
    m_labelLink = wxT("Connect");

    m_architecture = new CTCPClient;

    m_indicateLink = new wxStaticBitmap(this, NewControlId(), wxICON(disconnect));

    m_btnTcp = new wxRadioButton(this, ID_TCP, wxT("TCP"), DEF_RECT, wxRB_GROUP);
    m_btnUdp = new wxRadioButton(this, ID_UDP, wxT("UDP"));

    m_btnClient = new wxRadioButton(this, ID_CLIENT, wxT("Client"), DEF_RECT, wxRB_GROUP);
    m_btnServer = new wxRadioButton(this, ID_SERVER, wxT("Server"));

    m_chOpenSSL = new wxCheckBox(this, NewControlId(), wxT(""));
    m_chOpenSSL->Enable(false);

    wxIntegerValidator<unsigned short> vPort;
    vPort.SetRange(1, 65534);

    m_txt_locale_port =
        new wxTextCtrl(this, NewControlId(), wxT("55001"), wxPoint(-1, -1), wxSize(40, -1), wxNO_BORDER, vPort);
    m_txt_remote_port =
        new wxTextCtrl(this, NewControlId(), wxT("55001"), wxPoint(-1, -1), wxSize(40, -1), wxNO_BORDER, vPort);
    m_txt_address = new wxComboBox(this, NewControlId(), wxT(""), wxDefaultPosition, wxSize(90, -1));
    m_txt_address->Append({ wxT("127.0.0.1"), wxT("localhost"), wxT("0.0.0.0") });
    m_txt_address->SetSelection(0);

    m_btnLink = new wxButton(this, NewControlId(), m_labelLink);

    m_txtSend = new wxTextCtrl(this, NewControlId(), wxT(""), MESSAGE_RECT, wxTE_PROCESS_ENTER | wxTE_MULTILINE);
    m_txtReceive = new wxTextCtrl(this, NewControlId(), wxT(""), MESSAGE_RECT, wxTE_MULTILINE | wxTE_READONLY);

    m_list_link = new wxListBox(this, NewControlId(), wxDefaultPosition, wxSize(250, -1));

    wxBoxSizer* main_box = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* h_box = nullptr;
    wxStaticBoxSizer* st_box = nullptr;
    wxStaticBoxSizer* st_sub_box = nullptr;
    wxGridBagSizer* grgb_box = nullptr;

    grgb_box = new wxGridBagSizer();
    {
        grgb_box->Add(m_indicateLink, wxGBPosition(0, 0), wxGBSpan(), wxRIGHT, 5);

        st_box = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Protocol"));
        st_box->Add(m_btnTcp, 1, wxEXPAND);
        st_box->Add(m_btnUdp, 1, wxEXPAND);
        grgb_box->Add(st_box, wxGBPosition(0, 1), wxGBSpan(), wxEXPAND);

        st_box = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("SSL"));
        st_box->Add(m_chOpenSSL, 0, wxALIGN_CENTER);
        grgb_box->Add(st_box, wxGBPosition(1, 0), wxGBSpan(), wxRIGHT, 5);

        st_box = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Architecture"));
        st_box->Add(m_btnClient, 0, wxALIGN_CENTER);
        st_box->Add(m_btnServer, 0, wxALIGN_CENTER);
        grgb_box->Add(st_box, wxGBPosition(1, 1));

        st_box = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Port"));
        {
            st_sub_box = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Locale"));
            st_sub_box->Add(m_txt_locale_port, 1, wxEXPAND);
            st_box->Add(st_sub_box, 1, wxEXPAND | wxRIGHT, 5);

            st_sub_box = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Remote"));
            st_sub_box->Add(m_txt_remote_port, 1, wxEXPAND);
            st_box->Add(st_sub_box, 1, wxEXPAND);
        }
        grgb_box->Add(st_box, wxGBPosition(2, 0), wxGBSpan(1, 2), wxEXPAND);

        st_box = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("IP address"));
        st_box->Add(m_txt_address, 1, wxEXPAND);
        grgb_box->Add(st_box, wxGBPosition(3, 0), wxGBSpan(1, 2), wxEXPAND);

        grgb_box->Add(m_btnLink, wxGBPosition(4, 0), wxGBSpan(1, 2), wxEXPAND | wxTOP, 5);
    }
    main_box->Add(grgb_box, 0, wxALL, 5);

    h_box = new wxBoxSizer(wxVERTICAL);
    {
        st_box = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Receive"));
        st_box->Add(m_txtReceive, 1, wxEXPAND);
        h_box->Add(st_box, 1, wxEXPAND | wxALL, 5);

        st_box = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Send"));
        st_box->Add(m_txtSend, 1, wxEXPAND);
        h_box->Add(st_box, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
    }
    main_box->Add(h_box, 1, wxEXPAND);

    st_box = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("List link"));
    st_box->Add(m_list_link, 1, wxEXPAND);
    main_box->Add(st_box, 0, wxEXPAND | wxALL, 5);

    SetSizerAndFit(main_box);

    Bind(wxEVT_RADIOBUTTON, &CMainFrame::OnSwitchMode, this, ID_CLIENT);
    Bind(wxEVT_RADIOBUTTON, &CMainFrame::OnSwitchMode, this, ID_SERVER);
    Bind(wxEVT_RADIOBUTTON, &CMainFrame::OnSwitchMode, this, ID_UDP);
    Bind(wxEVT_RADIOBUTTON, &CMainFrame::OnSwitchMode, this, ID_TCP);
    Bind(wxEVT_CHECKBOX, &CMainFrame::OnSwitchMode, this, m_chOpenSSL->GetId());

    Bind(wxEVT_BUTTON, &CMainFrame::OnLink, this, m_btnLink->GetId());
    Bind(wxEVT_TEXT_ENTER, &CMainFrame::OnSend, this, m_txtSend->GetId());

    Bind(wxEVT_CLOSE_WINDOW, &CMainFrame::OnClose, this);

    m_txt_locale_port->Connect(wxEVT_SET_FOCUS, wxFocusEventHandler(CMainFrame::OnSetFocusLocalePort), nullptr, this);
    m_txt_locale_port->Connect(wxEVT_IDLE, wxIdleEventHandler(CMainFrame::OnIdle), nullptr, this);

    m_txt_remote_port->Connect(wxEVT_SET_FOCUS, wxFocusEventHandler(CMainFrame::OnSetFocusRemotePort), nullptr, this);
    m_txt_remote_port->Connect(wxEVT_IDLE, wxIdleEventHandler(CMainFrame::OnIdle), nullptr, this);

    m_process = 0;
    this->CallAfter(&CMainFrame::Process);
}

CMainFrame::~CMainFrame()
{
    if(m_architecture != nullptr) {
        delete m_architecture;
        m_architecture = nullptr;
    }
}

void CMainFrame::Process()
{
    int remote_port = 0;
    char* ip = nullptr;
    unsigned int size_list = -1;

    while(m_process == 0) {

        wxYield();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        if(m_queue_process.empty() == false) {

            auto& item = m_queue_process.front();
            switch(item.first) {
                case DISCONNECTED:
                    EnablePanelAtLink(m_labelLink, true, wxICON(disconnect));
                    break;
                case MESSAGE:
                    m_txtReceive->AppendText(item.second + wxT('\n'));
                    break;
            }

            m_queue_process.pop();
        }

        if(m_architecture != nullptr) {

            auto& list_link = m_architecture->GetListLink();
            if(size_list != list_link.size()) {
                size_list = list_link.size();

                m_list_link->Clear();

                for(auto& item_link : list_link) {

                    ip = inet_ntoa(item_link.remote_addr.sin_addr);
                    remote_port = htons(item_link.remote_addr.sin_port);

                    m_list_link->Append(
                        wxString::Format(wxT("socket:%llu ip:%s port:%d"), item_link.socket, ip, remote_port));
                }
            }
        }
    }

    this->Destroy();
}

void CMainFrame::OnClose(wxCloseEvent& WXUNUSED(event))
{
    m_process = 1;
}

void CMainFrame::OnIdle(wxIdleEvent& event)
{
    if(m_focused_txt_locale_port == true) {
        m_focused_txt_locale_port = false;
        m_txt_locale_port->SelectAll();
    }

    if(m_focused_txt_remote_port == true) {
        m_focused_txt_remote_port = false;
        m_txt_remote_port->SelectAll();
    }

    event.Skip();
}

void CMainFrame::OnSetFocusRemotePort(wxFocusEvent& event)
{
    m_focused_txt_remote_port = true;
    event.Skip();
}

void CMainFrame::OnSetFocusLocalePort(wxFocusEvent& event)
{
    m_focused_txt_locale_port = true;
    event.Skip();
}

void CMainFrame::OnSwitchMode(wxCommandEvent& WXUNUSED(event))
{
    if(m_architecture != nullptr) {
        delete m_architecture;
        m_architecture = nullptr;
    }

    bool udp = m_btnUdp->GetValue();
    bool tcp = m_btnTcp->GetValue();
    bool client = m_btnClient->GetValue();
    bool server = m_btnServer->GetValue();
    bool ssl = m_chOpenSSL->GetValue();
    bool loop = false;

    if(udp == true && client == true && ssl == false && loop == false) // UDPClient
        return EnablePanelAtSwitch(new CUDPClient, wxT("Connect"));

    if(udp == true && server == true && ssl == false && loop == false) // UDPServer
        return EnablePanelAtSwitch(new CUDPServer, wxT("Listen"));

    if(udp == true && server == true && ssl == false && loop == true) // UDPServerLoop
        return EnablePanelAtSwitch(nullptr, wxT("Listen"));

    if(udp == true && client == true && ssl == true && loop == false) // UDPClientSSL
        return EnablePanelAtSwitch(nullptr, wxT("Connect"));

    if(udp == true && server == true && ssl == true && loop == false) // UDPServerSSL
        return EnablePanelAtSwitch(nullptr, wxT("Listen"));

    // -------------------------------------------------------------------

    if(tcp == true && client == true && ssl == false && loop == false) // TCPClient
        return EnablePanelAtSwitch(new CTCPClient, wxT("Connect"));

    if(tcp == true && server == true && ssl == false && loop == false) // TCPServer
        return EnablePanelAtSwitch(new CTCPServer, wxT("Listen"));

    if(tcp == true && server == true && ssl == false && loop == true) // TCPServerLoop
        return EnablePanelAtSwitch(new CTCPServer, wxT("Listen"));

    if(tcp == true && client == true && ssl == true && loop == false) // TCPClientSSL
        return EnablePanelAtSwitch(nullptr, wxT("Connect"));

    if(tcp == true && server == true && ssl == true && loop == false) // TCPServerSSL
        return EnablePanelAtSwitch(nullptr, wxT("Listen"));

    printf("error: architect is nullptr\n");
}

void CMainFrame::OnLink(wxCommandEvent& WXUNUSED(event))
{
    wxString address = m_txt_address->GetValue();
    int locale_port = wxAtoi(m_txt_locale_port->GetValue());
    int remote_port = wxAtoi(m_txt_remote_port->GetValue());

    int result = 0;

    if(m_architecture != nullptr) {

        if(m_link == false) {

            m_architecture->SetAddress(address.mb_str());
            m_architecture->SetLocalPort(locale_port);
            m_architecture->SetRemotePort(remote_port);
            m_architecture->SetCloseFunction([this](const SOCKET& socket) { CloseLink(socket); });
            m_architecture->SetReceiveFunction([this](const SOCKET& socket, const char* data, const int& size) {
                FuncReceiveMessage(socket, data, size);
            });

            result = m_architecture->Connect();
            if(result == 0) {

                if(m_txt_address->FindString(address) == -1)
                    m_txt_address->Append(address);

                EnablePanelAtLink(wxT("Disconnect"), false, wxICON(connect));
            }

        } else {

            result = m_architecture->Disconnect();

            if(result == 0) {

                EnablePanelAtLink(m_labelLink, true, wxICON(disconnect));
            }
        }

    } else
        printf("error: architect is nullptr\n");
}

void CMainFrame::OnSend(wxCommandEvent& WXUNUSED(event))
{
    if(m_architecture != nullptr) {

        if(m_link == true) {

            wxString value = m_txtSend->GetValue();

            m_architecture->Send(value.mb_str(), (int)value.size());

            m_txtSend->Clear();
        }
    } else
        printf("error: architect is nullptr\n");
}

void CMainFrame::CloseLink(const SOCKET& UNUSED(socket))
{
    m_queue_process.emplace(DISCONNECTED, wxT(""));
}

void CMainFrame::FuncReceiveMessage(const SOCKET& UNUSED(socket), const char* data, const int& size)
{
    wxString message(data, wxConvFile);
    message.resize(size);

    wxString messag1(data, wxConvLibc);
    wxString messag2(data, wxConvLocal);
    wxString messag3(data, wxConvWhateverWorks);
    wxString messag4 = wxString::FromUTF8(data) + wxT('\n');

    m_queue_process.emplace(MESSAGE, message);
}

void CMainFrame::EnablePanelAtLink(const wxString& labelLink, bool enablePanel, const wxIcon& ico)
{
    m_indicateLink->SetIcon(ico);
    m_btnLink->SetLabel(labelLink);
    m_link = !enablePanel;
    m_btnTcp->Enable(enablePanel);
    m_btnUdp->Enable(enablePanel);
    m_btnClient->Enable(enablePanel);
    m_btnServer->Enable(enablePanel);
    m_txt_locale_port->Enable(enablePanel);
    m_txt_remote_port->Enable(enablePanel);
    m_txt_address->Enable(enablePanel);
}

void CMainFrame::EnablePanelAtSwitch(CBaseSocket* link, const wxString& labelLink)
{
    m_architecture = link;
    m_labelLink = labelLink;
    m_btnLink->SetLabel(labelLink);
}