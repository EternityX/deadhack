#pragma once

constexpr int default_x_pos = 27;
constexpr int default_y_pos = 10;

class Menu {
private:
public:
	std::shared_ptr< OSHGui::Form > m_form;

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
		void init( const AnsiString &text, std::vector< AnsiString > items, int x, int y, int max_items, Control *parent, int *cvar ) {
			SetLocation( x, y );
			SetFont( g_custom_renderer.m_fonts.at( 0 ) );
			SetMaxShowItems( max_items );

			auto label = new OSHGui::Label();
			label->SetForeColor( Color::FromARGB( 255, 201, 201, 201 ) );
			label->SetFont( g_custom_renderer.m_fonts.at( 0 ) );
			label->SetLocation( GetLeft(), GetTop() - 13 );
			label->SetStyle( 1 );
			label->SetText( text );
			parent->AddControl( label );

			for( auto const &item : items )
				AddItem( item );

			OSHGui::Timer *timer = new OSHGui::Timer();
			timer->SetInterval( 250 );
			timer->Start();
			parent->AddControl( timer );

			timer->GetTickEvent() += OSHGui::TickEventHandler( [ this, cvar ]( Control *sender ) {
				this->SetSelectedIndex( *cvar, false );
			});

			parent->AddControl( this );

			// click event.
			this->GetSelectedIndexChangedEvent() += OSHGui::SelectedIndexChangedEventHandler( [ this, cvar ]( Control *sender ) {
				*cvar = this->GetSelectedIndex();
			});
		}
	public:
		// manual positioning.
		Combobox( const AnsiString &text, std::vector< AnsiString > items, int x, int y, int max_items, Control *parent, int *cvar ) {
			init( text, items, x, y, max_items, parent, cvar );
		}

		// automatic positioning.
		Combobox( const AnsiString &text, std::vector< AnsiString > items, int max_items, Control *parent, int *cvar ) {
			init( text, items, parent->GetWidth() / 2 - Control::GetWidth() / 2 - 3, g_menu.m_control_y_pos + 10, max_items, parent, cvar );
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

	class ColorButton : public OSHGui::ColorButton {
	private:
	public:
		void init( int x, int y, Control *parent, Control *control ) {
			SetLocation( x, y );
			parent->AddControl( this );

			OSHGui::Timer *timer = new OSHGui::Timer();
			timer->SetInterval( 5 );
			timer->Start();
			parent->AddControl( timer );

			timer->GetTickEvent() += OSHGui::TickEventHandler( [ this ]( Control *sender ) {
				
			});

			// click event.
			this->GetClickEvent() += OSHGui::ClickEventHandler( [ this ]( Control *sender ) {
				
			});	
		}

		ColorButton( Control *parent, Control *control ) {
			init( parent->GetRight() - 66, control->GetTop() + 2, parent, control );
		}
	};

	class Hotkey : public OSHGui::HotkeyControl {
	private:
	public:
		void init( const AnsiString &text, int x, int y, Control *parent, int *cvar ) {
			SetLocation( x, y );
			SetFont( g_custom_renderer.m_fonts.at( 0 ) );
			
			auto label = new OSHGui::Label();
			label->SetForeColor( Color::FromARGB( 255, 201, 201, 201 ) );
			label->SetFont( g_custom_renderer.m_fonts.at( 0 ) );
			label->SetLocation( GetLeft(), GetTop() - 13 );
			label->SetStyle( 1 );
			label->SetText( text );
			parent->AddControl( label );

			OSHGui::Timer *timer = new OSHGui::Timer();
			timer->SetInterval( 5 );
			timer->Start();
			parent->AddControl( timer );

			timer->GetTickEvent() += OSHGui::TickEventHandler( [ this, cvar ]( Control *sender ) {
				this->SetHotkey( (OSHGui::Key)*cvar );
			});

			parent->AddControl( this );

			// click event.
			this->GetHotkeyChangedEvent() += OSHGui::HotkeyChangedEventHandler( [ this, cvar ]( Control *sender ) {
				*cvar = (int)GetHotkey();
			});
		}

		Hotkey( const AnsiString &text, Control *parent, int *cvar ) {
			Control::SetSize( 160, 20 );
			init( text, parent->GetWidth() / 2 - Control::GetWidth() / 2 - 3, g_menu.m_control_y_pos + 10, parent, cvar );
			g_menu.m_control_y_pos += 40;
		}
	};

	class Slider : public OSHGui::TrackBar {
	private:
		void init( const AnsiString &text, int x, int y, Color back_color, Control *parent, float min, float max, int *value ) {
			SetFont( g_custom_renderer.m_fonts.at( FONT_VERDANA_BOLD_7PX ) );
			SetBackColor( back_color );
			SetLocation( x, y );
			SetMinimum( min );
			SetMaximum( max );
			SetPrecision( 0 );
			SetText( text );

			OSHGui::Timer *timer = new OSHGui::Timer();
			timer->SetInterval( 5 );
			timer->Start();
			parent->AddControl( timer );

			// tick event.
			timer->GetTickEvent() += OSHGui::TickEventHandler( [ this, value ]( Control *sender ) {
				this->SetValue( *value );
			});

			parent->AddControl( this );

			// value changed event.
			this->GetValueChangedEvent() += OSHGui::ValueChangedEventHandler( [ this, value ]( Control *sender ) {
				*value = this->GetValue();
			});
		}

		void init( const AnsiString &text, int x, int y, Color back_color, Control *parent, float min, float max, float *value, int precision ) {
			SetFont( g_custom_renderer.m_fonts.at( FONT_VERDANA_BOLD_7PX ) );
			SetBackColor( back_color );
			SetLocation( x, y );
			SetMinimum( min );
			SetMaximum( max );
			SetPrecision( precision );
			SetText( text );

			OSHGui::Timer *timer = new OSHGui::Timer();
			timer->SetInterval( 5 );
			timer->Start();
			parent->AddControl( timer );

			// tick event.
			timer->GetTickEvent() += OSHGui::TickEventHandler( [ this, value ]( Control *sender ) {
				this->SetValue( *value );
			});

			parent->AddControl( this );

			// value changed event.
			this->GetValueChangedEvent() += OSHGui::ValueChangedEventHandler( [ this, value ]( Control *sender ) {
				*value = this->GetValue();
			});
		}
	public:
		Slider( const AnsiString &text, int x, int y, Color back_color, Control *parent, float min, float max, int *value ) {
			init( text, x, y, back_color, parent, min, max, value );
		}

		Slider( const AnsiString &text, int x, int y, Color back_color, Control *parent, float min, float max, float *value, int precision ) {
			init( text, x, y, back_color, parent, min, max, value, precision );
		}

		// automatic positioning.
		Slider( const AnsiString &text, Color back_color, Control *parent, float min, float max, int *value ) {
			init( text, parent->GetWidth() / 2 - Control::GetWidth() / 2 - 2, g_menu.m_control_y_pos + 4, back_color, parent, min, max, value );
			g_menu.m_control_y_pos += 28;
		}

		Slider( const AnsiString &text, Color back_color, Control *parent, float min, float max, float *value, int precision ) {
			init( text, parent->GetWidth() / 2 - Control::GetWidth() / 2 - 2, g_menu.m_control_y_pos, back_color, parent, min, max, value, precision );
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