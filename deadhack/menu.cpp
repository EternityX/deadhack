#include "includes.h"

Menu::Menu() {

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

void Menu::MainForm::initialize_component() {
	this->SetSize( OSHGui::Drawing::SizeI( 600, 400 ) );
	this->SetBackColor( OSHGui::Drawing::Color::FromARGB( 255, 206, 115, 136 ) );
}