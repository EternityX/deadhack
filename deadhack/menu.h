#pragma once

constexpr int default_x_pos = 27;
constexpr int default_y_pos = 10;

class Menu {
private:
	std::shared_ptr< OSHGui::Form > m_form;
public:
	// x axis pos.
	int m_control_x_pos;

	// y axis pos.
	int m_control_y_pos;

	// ctor.
	Menu::Menu() : m_form{}, m_control_x_pos{ default_x_pos }, m_control_y_pos{ default_y_pos } { }

	// initialize form and set hotkey.
	void init();
};

extern Menu g_menu;

namespace Controls {
	using namespace OSHGui::Drawing;
	using namespace OSHGui::Misc;

	// control wrappers.
	class Groupbox : public OSHGui::GroupBox {
	public:
		// manual positioning.
		Groupbox( const AnsiString &text, int x, int y, int w, int h ) {
			GroupBox::SetFont( g_custom_renderer.m_fonts.at( 1 ) );
			Control::SetBounds( x, y, w, h );
			SetText( text );

			// reset y axis.
			g_menu.m_control_y_pos = default_y_pos;
		}
	};

	class Combobox : public OSHGui::ComboBox {
	private:
		void init( const AnsiString &text, std::vector< AnsiString > items, int x, int y, int max_items, Control *parent ) {
			SetLocation( x, y );
			SetFont( g_custom_renderer.m_fonts.at( 0 ) );
			SetMaxShowItems( max_items );
			parent->AddControl( this );

			auto label = new OSHGui::Label();
			label->SetForeColor( Color::FromARGB( 255, 201, 201, 201 ) );
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
		Combobox( const AnsiString &text, std::vector< AnsiString > items, int x, int y, int max_items, Control *parent ) {
			init( text, items, x, y, max_items, parent );
		}

		// automatic positioning.
		Combobox( const AnsiString &text, std::vector< AnsiString > items, int max_items, Control *parent ) {
			init( text, items, parent->GetWidth() / 2 - Control::GetWidth() / 2 - 3, g_menu.m_control_y_pos + 10, max_items, parent );
			g_menu.m_control_y_pos += 40;
		}
	};

	class Checkbox : public OSHGui::CheckBox {
	private:
		void init( const AnsiString &text, int x, int y, Color fore_color, Control *parent, bool *cvar ) {
			SetBackColor( fore_color );
			SetFont( g_custom_renderer.m_fonts.at( 0 ) );
			SetLocation( x, y );
			SetText( text );
			SetChecked( *cvar );

			// atleast it's better than reinitializing the controls...
			OSHGui::Timer *timer = new OSHGui::Timer();
			timer->SetInterval( 250 );
			timer->Start();
			parent->AddControl( timer );

			timer->GetTickEvent() += OSHGui::TickEventHandler( [ this, cvar ]( Control *sender ) {
				this->SetChecked( *cvar );
			});

			parent->AddControl( this );

			// click event.
			this->GetClickEvent() += OSHGui::ClickEventHandler( [ this, cvar ]( Control *sender ) {
				*cvar = !( *cvar );
			});
		}
	public:
		Checkbox( const AnsiString &text, int x, int y, Color fore_color, Control *parent, bool *cvar ) {
			init( text, x, y, fore_color, parent, cvar );
		}

		// automatic positioning.
		Checkbox( const AnsiString &text, Color fore_color, Control *parent, bool *cvar ) {
			init( text, g_menu.m_control_x_pos, g_menu.m_control_y_pos, fore_color, parent, cvar );
			g_menu.m_control_y_pos += 18;
		}
	};

	class Button : public OSHGui::Button {
	private:
		void init( const AnsiString &text, int x, int y, Control *parent ) {
			SetFont( g_custom_renderer.m_fonts.at( 0 ) );
			SetLocation( x, y );
			//SetSize( 220, 30 );
			SetText( text );

			// i'm not sure how to pass a lambda as a function parameter.
			// so we'll just have to call AddControl manually.
			// parent->AddControl( this );
		}
	public:
		Button( const AnsiString &text, int x, int y, Control *parent ) {
			init( text, x, y, parent );
		}

		// automatic positioning.
		Button( const AnsiString &text, Control *parent ) {
			// set size here.
			Control::SetSize( 160, 20 );

			init( text, parent->GetWidth() / 2 - Control::GetWidth() / 2 - 3, g_menu.m_control_y_pos, parent );
			g_menu.m_control_y_pos += 28;
		}
	};

	class Textbox : public OSHGui::TextBox {
	private:
		void init( const AnsiString &text, int x, int y, Control *parent ) {
			SetFont( g_custom_renderer.m_fonts.at( 0 ) );
			SetLocation( x, y );
			//SetSize( 220, 30 );
			// SetText( text );

			parent->AddControl( this );
		}
	public:
		Textbox( const AnsiString &text, int x, int y, Control *parent ) {
			init( text, x, y, parent );
		}

		// automatic positioning.
		Textbox( const AnsiString &text, Control *parent ) {
			// set size here.
			Control::SetSize( 160, 20 );

			init( text, parent->GetWidth() / 2 - Control::GetWidth() / 2 - 3, g_menu.m_control_y_pos, parent );
			g_menu.m_control_y_pos += 28;
		}
	};
}

class MainForm : public OSHGui::Form {
public:
	// primary color for controls.
	OSHGui::Drawing::Color m_primary_color = OSHGui::Drawing::Color::FromARGB( 255, 206, 115, 136 );

private:
	std::vector< std::shared_ptr< OSHGui::TabPage > > m_pages;
	OSHGui::TabControl *m_tab_control;

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
		configuration();
	}

	void reinit();

	// create tabs.
	void create_tabs();

	// visual tab controls.
	void visuals();
	void configuration();

public:
	MainForm() : Form() {
		InitializeComponent();
	}
};