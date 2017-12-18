#include "includes.h"

Menu::Menu() {

}

void Menu::init() {
	// create and set form as mainform.
	g_custom_renderer.m_instance->Run( std::shared_ptr< OSHGui::Form>( new MainForm() ) );

	// enable it.
	g_custom_renderer.m_instance->Enable();

	// register hotkey.
	g_custom_renderer.m_instance->RegisterHotkey( OSHGui::Hotkey( OSHGui::Key::Insert, [] {
		OSHGui::Application::Instance().Toggle();
	}));
}

void Menu::MainForm::InitializeComponent() {
	this->SetSize( OSHGui::Drawing::SizeI( 600, 400 ) );
	this->SetBackColor( OSHGui::Drawing::Color::FromARGB( 255, 206, 115, 136 ) );

	OSHGui::CheckBox *checkbox = new OSHGui::CheckBox();
	this->AddControl( checkbox );
}