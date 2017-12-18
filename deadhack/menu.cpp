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

void Menu::MainForm::InitializeComponent() {
	this->SetSize( OSHGui::Drawing::SizeI( 600, 400 ) );
	this->SetBackColor( m_primary_color );

	create_tabs();
	
	// init tab content.
	legitbot();
}

void Menu::MainForm::create_tabs() {
	m_page_legitbot = new OSHGui::TabPage();
	m_page_ragebot = new OSHGui::TabPage();
	m_tab_visuals = new OSHGui::TabPage();
	m_tab_misc = new OSHGui::TabPage();
	m_tab_config = new OSHGui::TabPage();

	OSHGui::TabControl *tab = new OSHGui::TabControl( );

	m_page_legitbot->SetText( "Legitbot" );
	m_page_ragebot->SetText( "Ragebot" );	
	m_tab_visuals->SetText( "Visuals" );	
	m_tab_misc->SetText( "Miscellaneous" );	
	m_tab_config->SetText( "Config" );

	tab->SetSize( 576, 380 );
	tab->SetLocation( OSHGui::Drawing::PointI( 6, -15 ) );
	tab->SetBackColor( OSHGui::Drawing::Color::FromARGB( 255, 32, 32, 32 ) );

	tab->AddTabPage( m_page_legitbot );
	tab->AddTabPage( m_page_ragebot );
	tab->AddTabPage( m_tab_visuals );
	tab->AddTabPage( m_tab_misc );
	tab->AddTabPage( m_tab_config );

	this->AddControl( tab );
}

void Menu::MainForm::legitbot() {
	OSHGui::CheckBox *check_enable_legit = new OSHGui::CheckBox();

	check_enable_legit->SetText( "Enable" );
	check_enable_legit->SetBackColor( m_primary_color );
	check_enable_legit->SetFont( g_custom_renderer.m_fonts.at( 0 ) );

	m_page_legitbot->AddControl( check_enable_legit );
}