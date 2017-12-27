#pragma once

class Menu {
private:
	std::shared_ptr< OSHGui::Form > m_form;

public:
	// x axis pos.
	int m_control_x_pos;

	// y axis pos.
	int m_control_y_pos;

	// ctor.
	Menu::Menu() : m_form{}, m_control_x_pos{ 27 }, m_control_y_pos{ 10 } { }

	// initialize form and set hotkey.
	void init();
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

			// reset y axis.
			g_menu.m_control_y_pos = 10;
		}
	};

	class Combobox : public OSHGui::ComboBox {
	private:
		void init( const OSHGui::Misc::AnsiString &text, std::vector< OSHGui::Misc::AnsiString > items, int x, int y, int max_items, Control *parent ) {
			SetLocation( x, y );
			SetFont( g_custom_renderer.m_fonts.at( 0 ) );
			SetMaxShowItems( max_items );
			parent->AddControl( this );

			auto label = new OSHGui::Label();
			label->SetForeColor( OSHGui::Drawing::Color::FromARGB( 255, 201, 201, 201 ) );
			label->SetFont( g_custom_renderer.m_fonts.at( 0 ) );
			label->SetLocation( GetLeft(), GetTop() - 13 );
			label->SetStyle( 1 );
			label->SetText( text );
			parent->AddControl( label );

			for( auto const &item : items )
				AddItem( item );
		}
	public:
		// manual positioning.
		Combobox( const OSHGui::Misc::AnsiString &text, std::vector< OSHGui::Misc::AnsiString > items, int x, int y, int max_items, Control *parent ) {
			init( text, items, x, y, max_items, parent );
		}

		// automatic positioning.
		Combobox( const OSHGui::Misc::AnsiString &text, std::vector< OSHGui::Misc::AnsiString > items, int max_items, Control *parent ) {
			init( text, items, parent->GetWidth() / 2 - Control::GetWidth() / 2 - 3, g_menu.m_control_y_pos + 10, max_items, parent );
			g_menu.m_control_y_pos += 40;
		}
	};

	class Checkbox : public OSHGui::CheckBox {
	private:
		void init( const OSHGui::Misc::AnsiString &text, int x, int y, OSHGui::Drawing::Color fore_color, Control *parent, bool &cvar ) {
			SetBackColor( fore_color );
			SetFont( g_custom_renderer.m_fonts.at( 0 ) );
			SetLocation( x, y );
			SetText( text );
			SetChecked( cvar );

			parent->AddControl( this );

			// click event.
			this->GetClickEvent() += OSHGui::ClickEventHandler( [ this, &cvar ]( Control *sender ) {
				cvar = !cvar;
			});
		}
	public:
		Checkbox( const OSHGui::Misc::AnsiString &text, int x, int y, OSHGui::Drawing::Color fore_color, Control *parent, bool &cvar ) {
			init( text, x, y, fore_color, parent, cvar );
		}

		// automatic positioning.
		Checkbox( const OSHGui::Misc::AnsiString &text, OSHGui::Drawing::Color fore_color, Control *parent, bool &cvar ) {
			init( text, g_menu.m_control_x_pos, g_menu.m_control_y_pos, fore_color, parent, cvar );
			g_menu.m_control_y_pos += 18;
		}
	};
}

class MainForm : public OSHGui::Form {
public:
	// primary color for controls.
	OSHGui::Drawing::Color m_primary_color = OSHGui::Drawing::Color::FromARGB( 255, 206, 115, 136 );

private:
	std::vector< std::shared_ptr< OSHGui::TabPage > > m_pages;

	// tab pages.
	enum Pages {
		PAGE_LEGITBOT,
		PAGE_RAGEBOT,
		PAGE_VISUALS,
		PAGE_MISC,
		PAGE_CONFIG
	};

	// initialize all controls.
	void InitializeComponent() {
		this->SetSize( OSHGui::Drawing::SizeI( 600, 400 ) );
		this->SetBackColor( m_primary_color );

		create_tabs();

		// init tab controls.
		visuals();
	}

	// create tabs.
	void create_tabs();

	// visual tab controls.
	void visuals();

public:
	MainForm() : Form() {
		InitializeComponent();
	}
};