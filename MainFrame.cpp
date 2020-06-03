#include "MainFrame.h"

#include <thread>
#include <wx/valnum.h>

#define DEF_RECT wxDefaultPosition, wxDefaultSize

CMainFrame::CMainFrame(wxWindow* parent)
    : wxFrame(parent, wxID_ANY, wxT("Client Server"))
{
    SetIcon(wxICON(link));
    SetBackgroundColour(*wxWHITE);

    m_link = new CClient;
    m_resolutionLink = false;
    m_labelLink = wxT("Connect");

    m_indicateLink = new wxStaticBitmap(this, NewControlId(), wxICON(disconnect));

    m_btnClient = new wxRadioButton(this, ID_CLIENT, wxT("Client"), DEF_RECT, wxRB_GROUP);
    m_btnServer = new wxRadioButton(this, ID_SERVER, wxT("Server"));

    wxIntegerValidator<unsigned short> vPort;
    vPort.SetRange(1, 65534);

    m_txtPort = new wxTextCtrl(this, NewControlId(), wxT("55001"), wxPoint(-1, -1), wxSize(40, -1), wxNO_BORDER, vPort);
    m_txtAddress = new wxTextCtrl(this, NewControlId(), wxT(""), wxDefaultPosition, wxSize(90, -1), wxNO_BORDER);
    m_txtAddress->SetValue(wxT("192.168.1.2"));

    m_btnLink = new wxButton(this, NewControlId(), m_labelLink, wxDefaultPosition, wxSize(70, 30));

    m_txtSend = new wxTextCtrl(this, NewControlId(), wxT(""), DEF_RECT, wxTE_PROCESS_ENTER | wxTE_MULTILINE);
    m_txtReceive = new wxTextCtrl(this, NewControlId(), wxT(""), DEF_RECT, wxTE_MULTILINE | wxTE_READONLY);

    wxBoxSizer* m_box = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* h_box = new wxBoxSizer(wxHORIZONTAL);
    wxStaticBoxSizer* st_box = nullptr;

    h_box->Add(m_indicateLink);

    st_box = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Choose link"));
    st_box->Add(m_btnClient);
    st_box->Add(m_btnServer);
    h_box->Add(st_box, 0, wxRIGHT, 5);

    st_box = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Port"));
    st_box->Add(m_txtPort);
    h_box->Add(st_box, 0, wxRIGHT, 5);

    st_box = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("IP address"));
    st_box->Add(m_txtAddress);
    h_box->Add(st_box, 0, wxRIGHT, 5);

    h_box->Add(m_btnLink, 0, wxTOP, 6);

    m_box->Add(h_box, 0, wxALL, 6);

    st_box = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Send"));
    st_box->Add(m_txtSend, 1, wxEXPAND);
    m_box->Add(st_box, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);

    st_box = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Receive"));
    st_box->Add(m_txtReceive, 1, wxEXPAND);
    m_box->Add(st_box, 1, wxEXPAND | wxALL, 5);

    SetSizerAndFit(m_box);

    Bind(wxEVT_RADIOBUTTON, &CMainFrame::OnSwitchLink, this, ID_CLIENT);
    Bind(wxEVT_RADIOBUTTON, &CMainFrame::OnSwitchLink, this, ID_SERVER);
    Bind(wxEVT_BUTTON, &CMainFrame::OnLink, this, m_btnLink->GetId());
    Bind(wxEVT_TEXT_ENTER, &CMainFrame::OnSend, this, m_txtSend->GetId());

    std::thread thr(&CMainFrame::Process, this);
    thr.detach();
}

CMainFrame::~CMainFrame()
{
    if(m_link != nullptr)
        delete m_link;
}

void CMainFrame::OnSwitchLink(wxCommandEvent& event)
{
    if(m_link != nullptr)
        delete m_link;

    switch(event.GetId()) {
    case ID_CLIENT:
        EnablePanelAtSwitch(new CClient, true, wxT("Connect"));
        break;
    case ID_SERVER:
        EnablePanelAtSwitch(new CServer, false, wxT("Listen"));
        break;
    }
}

void CMainFrame::OnLink(wxCommandEvent& event)
{
    Link();
}

void CMainFrame::OnSend(wxCommandEvent& event)
{
    if(m_link != nullptr) {
        if(m_resolutionLink == true) {
            m_link->Send(m_txtSend->GetValue().mb_str());
            m_txtSend->Clear();
            std::cout << m_link->GetError();
        }
    }
}

void CMainFrame::Link()
{
    wxString address = m_txtAddress->GetValue();
    int port = wxAtoi(m_txtPort->GetValue());

    if(m_link != nullptr) {
        if(m_resolutionLink == true) {
            if(m_link->Disconnect() == true)
                EnablePanelAtLink(m_labelLink, true, wxICON(disconnect));
        } else {
            if(m_link->Connect(address.mb_str(), port) == true)
                EnablePanelAtLink(wxT("Disconnect"), false, wxICON(connect));
        }
        std::cout << m_link->GetError();
    }
}

void CMainFrame::Process()
{
    while(1) {
        // std::this_thread::yield();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        while(m_resolutionLink == true) {
            // wxYield();
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            char message[100] = { 0 };
            int size = sizeof(message) / sizeof(message[0]);

            if(m_link->Receive(message, size) == false)
                Link();
            else
                m_txtReceive->AppendText(wxString::FromUTF8(message) + wxT('\n'));

            std::cout << m_link->GetError();
        }
    }
}

void CMainFrame::EnablePanelAtLink(wxString labelLink, bool enablePanel, wxIcon ico)
{
    m_indicateLink->SetIcon(ico);
    m_btnLink->SetLabel(labelLink);
    m_resolutionLink = !enablePanel;
    m_btnClient->Enable(enablePanel);
    m_btnServer->Enable(enablePanel);
    m_txtPort->Enable(enablePanel);
    m_txtAddress->Enable(enablePanel);

    if(labelLink == wxT("Listen"))
        m_txtAddress->Enable(false);
}

void CMainFrame::EnablePanelAtSwitch(CBaseLink* link, bool enableAddress, wxString labelLink)
{
    m_link = link;
    m_txtAddress->SetValue(wxT("127.0.0.1"));
    m_txtAddress->Enable(enableAddress);
    m_labelLink = labelLink;
    m_btnLink->SetLabel(labelLink);
}