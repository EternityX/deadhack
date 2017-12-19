#include "includes.h"

Menu::Menu() : m_form{} {

}

void Menu::init() {
	// create form.
	m_form = std::static_pointer_cast< OSHGui::Form >( std::make_shared< MainForm >() );

	// set form as mainform.
	g_custom_renderer.m_instance->Run( m_form );

	// enable it.
	g_custom_renderer.m_instance->Enable();

	// register hotkey.
	g_custom_renderer.m_instance->RegisterHotkey( OSHGui::Hotkey( OSHGui::Key::Insert, [] {
		OSHGui::Application::Instance().Toggle();
	}));
}

void Menu::MainForm::InitializeComponent() {
	this->SetSize( OSHGui::Drawing::SizeI( 600, 400 ) );
	this->SetBackColor( m_primary_color );

	create_tabs();
	
	// init tab content.
	legitbot();
}

void Menu::MainForm::create_tabs() {
	
}

void Menu::MainForm::legitbot() {
}