#pragma once

class Menu {
private:
	std::shared_ptr< OSHGui::Form > m_form;

public:
	// ctor.
	Menu::Menu() : m_form{}, m_control_x_pos{ 25 }, m_control_y_pos{ 10 } { }

	// initialize form and set hotkey.
	void init();

	// x axis pos.
	int m_control_x_pos;

	// y axis pos.
	int m_control_y_pos;
};
extern Menu g_menu;

namespace Controls {
	// control wrappers.
	class Groupbox : public OSHGui::GroupBox {
	public:
		// manual positioning.
		Groupbox( const OSHGui::Misc::AnsiString &text, int x, int y, int w, int h ) {
			GroupBox::SetFont( g_custom_renderer.m_fonts.at( 1 ) );
			Control::SetBounds( x, y, w, h );
			SetText( text );
		}
	};

	class Combobox : public OSHGui::ComboBox {
	private:
		void init( const OSHGui::Misc::AnsiString &text, std::vector< OSHGui::Misc::AnsiString > items, int x, int y, Control *parent ) {
			SetLocation( x, y );
			SetFont( g_custom_renderer.m_fonts.at( 0 ) );

			auto label = new OSHGui::Label();
			label->SetForeColor( OSHGui::Drawing::Color::FromARGB( 255, 201, 201, 201 ) );
			label->SetFont( g_custom_renderer.m_fonts.at( 0 ) );
			label->SetLocation( GetLeft(), GetTop() - 13 );
			label->SetStyle( 1 );
			label->SetText( text );
			parent->AddControl( label );

			for( auto const& item : items )
				AddItem( item );
		}
	public:
		// manual positioning.
		Combobox( const OSHGui::Misc::AnsiString &text, std::vector< OSHGui::Misc::AnsiString > items, int x, int y, Control *parent ) {
			init( text, items, x, y, parent );
		}

		// automatic positioning.
		Combobox( const OSHGui::Misc::AnsiString &text, std::vector< OSHGui::Misc::AnsiString > items, Control *parent ) {
			init( text, items, parent->GetWidth() / 2 - Control::GetWidth() / 2 - 3, g_menu.m_control_y_pos + 10, parent );
			g_menu.m_control_y_pos += 40;
		}
	};

	class Checkbox : public OSHGui::CheckBox {
	private:
		void init( const OSHGui::Misc::AnsiString &text, int x, int y, OSHGui::Drawing::Color fore_color ) {
			SetBackColor( fore_color );
			SetFont( g_custom_renderer.m_fonts.at( 0 ) );
			SetLocation( x, y );
			SetText( text );
		}
	public:
		Checkbox( const OSHGui::Misc::AnsiString &text, int x, int y, OSHGui::Drawing::Color fore_color ) {
			init( text, x, y, fore_color );
		}

		// automatic y axis positioning.
		Checkbox( const OSHGui::Misc::AnsiString &text, OSHGui::Drawing::Color fore_color ) {
			init( text, g_menu.m_control_x_pos, g_menu.m_control_y_pos, fore_color );
			g_menu.m_control_y_pos += 18;
		}
	};
}

class MainForm : public OSHGui::Form {
public:
	// primary color for controls.
	OSHGui::Drawing::Color m_primary_color = OSHGui::Drawing::Color::FromARGB( 255, 206, 115, 136 );

private:
	// tab pages.
	OSHGui::TabPage *m_page_legitbot;
	OSHGui::TabPage *m_page_ragebot;
	OSHGui::TabPage *m_tab_visuals;
	OSHGui::TabPage *m_tab_misc;
	OSHGui::TabPage *m_tab_config;

	// initialize all components.
	void InitializeComponent() {
		this->SetSize( OSHGui::Drawing::SizeI( 600, 400 ) );
		this->SetBackColor( m_primary_color );

		create_tabs();

		// init tab content.
		visuals();
	}

	void create_tabs() {
		OSHGui::TabControl* tab = new OSHGui::TabControl();

		m_tab_visuals = new OSHGui::TabPage();
		m_tab_visuals->SetText( "Visuals" );

		// set style.
		tab->SetSize( 576, 380 );
		tab->SetBackColor( OSHGui::Drawing::Color::FromARGB( 255, 32, 32, 32 ) );
		tab->SetLocation( 6, -15 );

		// add all pages.
		tab->AddTabPage( m_tab_visuals );

		this->AddControl( tab );
	}

	// visual tab components.
	void visuals() {
		// player esp groupbox.
		Controls::Groupbox *player_esp_groupbox = new Controls::Groupbox( "Player ESP", 17, 6, 256, 334 );

		Controls::Combobox *activation_type_combo = new Controls::Combobox( "Activation type", { "On-key", "Toggle", "Always" }, player_esp_groupbox );

		Controls::Checkbox *teammate_check = new Controls::Checkbox( "Teammates", m_primary_color );
		teammate_check->GetClickEvent() += OSHGui::ClickEventHandler( std::bind( &MainForm::team_checkbox_CheckChanged, this, std::placeholders::_1 ) );

		Controls::Checkbox *bbox_check = new Controls::Checkbox( "Bounding box", m_primary_color );

		player_esp_groupbox->AddControl( activation_type_combo );
		player_esp_groupbox->AddControl( teammate_check );
		player_esp_groupbox->AddControl( bbox_check );
		
		m_tab_visuals->AddControl( player_esp_groupbox );
	}

	// events
	void team_checkbox_CheckChanged( Control *sender );

public:
	MainForm() : Form() {
		InitializeComponent();
	}
};