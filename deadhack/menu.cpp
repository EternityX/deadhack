#include "includes.h"

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

void MainForm::create_tabs() {
	OSHGui::TabControl* tab = new OSHGui::TabControl();

	// create pages.
	for( int i = 0; i < 5; ++i )
		m_pages.push_back( std::make_shared< OSHGui::TabPage >() );

	// set page titles.
	m_pages.at( PAGE_LEGITBOT )->SetText( "Legitbot" );
	m_pages.at( PAGE_RAGEBOT )->SetText( "Ragebot" );
	m_pages.at( PAGE_VISUALS )->SetText( "Visuals" );
	m_pages.at( PAGE_MISC )->SetText( "Miscellaneous" );
	m_pages.at( PAGE_CONFIG )->SetText( "Configuration" );

	// set page style.
	tab->SetFont( g_custom_renderer.m_fonts.at( 4 ) );
	tab->SetSize( 576, 380 );
	tab->SetBackColor( OSHGui::Drawing::Color::FromARGB( 255, 32, 32, 32 ) );
	tab->SetLocation( 6, -15 );

	// add all pages to tab control.
	for( auto const &item : m_pages )
		tab->AddTabPage( item.get() );

	this->AddControl( tab );
}

void MainForm::visuals() {
	// player esp groupbox.
	Controls::Groupbox *player_esp_groupbox = new Controls::Groupbox( "Player ESP", 17, 6, 260, 334 );

	m_pages.at( PAGE_VISUALS )->AddControl( player_esp_groupbox );

	// other visuals groupbox.
	Controls::Groupbox *other_esp_groupbox = new Controls::Groupbox( "Other visuals", player_esp_groupbox->GetRight() + 19, 6, 259, 334 );
	Controls::Checkbox *watermark_check = new Controls::Checkbox( "Watermark", m_primary_color, other_esp_groupbox, g_cvar.m_misc.watermark );

	m_pages.at( PAGE_VISUALS )->AddControl( other_esp_groupbox );
}
