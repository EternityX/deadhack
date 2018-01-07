#include "includes.h"

void Menu::init() {
	// create form.
	m_form = std::static_pointer_cast< OSHGui::Form >( std::make_shared< MainForm >() );

	// set form as mainform.
	g_custom_renderer.m_instance->Run( m_form );

	// enable it.
	//g_custom_renderer.m_instance->Enable();

	// register hotkey.
	/*g_custom_renderer.m_instance->RegisterHotkey( OSHGui::Hotkey( OSHGui::Key::Insert, [] {
		OSHGui::Application::Instance().Toggle();
	}));*/
}

void MainForm::create_tabs() {
	m_tab_control = new OSHGui::TabControl();

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
	m_tab_control->SetFont( g_custom_renderer.m_instance->GetDefaultFont() );
	m_tab_control->SetSize( 576, 380 );
	m_tab_control->SetBackColor( OSHGui::Drawing::Color::FromARGB( 255, 32, 32, 32 ) );
	m_tab_control->SetLocation( 6, -15 );

	// add all pages to tab control.
	for( auto &item : m_pages )
		m_tab_control->AddTabPage( item.get() );

	this->AddControl( m_tab_control );
}

void MainForm::visuals() {
	// player esp groupbox.
	Controls::Groupbox *player_esp_groupbox = new Controls::Groupbox( "Player ESP", 17, 6, 260, 334 );

	m_pages.at( PAGE_VISUALS )->AddControl( player_esp_groupbox );

	// other visuals groupbox.
	Controls::Groupbox *other_esp_groupbox = new Controls::Groupbox( "Other ESP", player_esp_groupbox->GetRight() + 19, 6, 259, 150 );
	Controls::Checkbox *watermark_check = new Controls::Checkbox( "Watermark", m_primary_color, other_esp_groupbox, &g_cvar.m_misc.watermark->bValue );

	m_pages.at( PAGE_VISUALS )->AddControl( other_esp_groupbox );

	// effects groupbox.
	Controls::Groupbox *effects_groupbox = new Controls::Groupbox( "Effects", player_esp_groupbox->GetRight() + 19, other_esp_groupbox->GetBottom() + 14, 259, 170 );

	Controls::Slider *overridefov_slider = new Controls::Slider( "Camera FOV", m_primary_color, effects_groupbox, 0, 180, &g_cvar.m_misc.override_fov->iValue );

	m_pages.at( PAGE_VISUALS )->AddControl( effects_groupbox );
}

void MainForm::configuration() {
	// profile groupbox.
	Controls::Groupbox *config_groupbox = new Controls::Groupbox( "Profiles", 17, 6, 260, 334 );

	// list index.
	static int index = 0;

	// list view.
	OSHGui::ListBox* list = new OSHGui::ListBox();
	list->SetSize( 234, 300 );
	list->SetLocation( config_groupbox->GetWidth() / 2 - list->GetWidth() / 2 - 3, 10 );
	list->ExpandSizeToShowItems( 20 );
	list->SetAutoScrollEnabled( true );
	list->SetFont( g_custom_renderer.m_fonts.at( 0 ) );

	// get index from event.
	list->GetSelectedIndexChangedEvent() += OSHGui::SelectedIndexChangedEventHandler( [ this, list ]( Control *sender ) {
		index = list->GetSelectedIndex();
	}); 

	// items.
	static std::vector< std::string > items = g_config.get_config_files();

	// fill list with configs.
	for( auto const &item : items )
		list->AddItem( item.c_str() );

	// add list to groupbox.
	config_groupbox->AddControl( list );

	m_pages.at( PAGE_CONFIG )->AddControl( config_groupbox );

	Controls::Groupbox *config2_groupbox = new Controls::Groupbox( "Configuration", config_groupbox->GetRight() + 19, 6, 259, 334 );

	// config name textbox.
	Controls::Textbox *name_textbox = new Controls::Textbox( "", config2_groupbox );

	// new button.
	Controls::Button *button_new = new Controls::Button( "New", config2_groupbox );
	button_new->GetClickEvent() += OSHGui::ClickEventHandler( [ this, name_textbox, list ]( Control *sender ) {
		if ( name_textbox->GetText().empty() ) {
			OSHGui::MessageBox::Show( "You must set a name." );
			return;
		}

		if( items.size() > 15 ) {
			OSHGui::MessageBox::Show( "You cannot create anymore profiles." );
			return;
		}

		g_config.save( name_textbox->GetText(), true );

		items = g_config.get_config_files();

		for( auto &item : items ) {
			// reinit list view items.
			for( int i = 0; i < list->GetItemsCount(); i++ ) {
				auto list_item = list->GetItem( i );
				if( !list_item )
					continue;

				if( item.c_str() == list_item->GetItemText() ) {
					list->RemoveItem( i );
					continue;
				}
			}

			list->AddItem( item.c_str() );
		}
	}); config2_groupbox->AddControl( button_new );

	// save button.
	Controls::Button *button_save = new Controls::Button( "Save", config2_groupbox );
	button_save->GetClickEvent() += OSHGui::ClickEventHandler( [ this, list ]( Control *sender ) {
		if( items.empty() || list->GetSelectedIndex() == -1 )
			return;

		OSHGui::MessageBox::ShowDialog( "Saving will override any changes, are you sure you want to save?", "", OSHGui::MessageBoxButtons::YesNo, [ this, list ]( OSHGui::DialogResult result ) {
			if( result == OSHGui::DialogResult::Yes ) {
				g_config.save( items.at( index ), false );
			}
		});		
	}); config2_groupbox->AddControl( button_save );

	// load button.
	Controls::Button *button_load = new Controls::Button( "Load", config2_groupbox );
	button_load->GetClickEvent() += OSHGui::ClickEventHandler( [ this, list ]( Control *sender ) {
		if( items.empty() || list->GetSelectedIndex() == -1 )
			return;

		OSHGui::MessageBox::ShowDialog( "Are you sure you want to load the selected profile?", "", OSHGui::MessageBoxButtons::YesNo, [ this ]( OSHGui::DialogResult result ) {
			if( result == OSHGui::DialogResult::Yes )
				g_config.load( items.at( index ) );
		});
	}); config2_groupbox->AddControl( button_load );

	// delete button.
	Controls::Button *button_delete = new Controls::Button( "Delete", config2_groupbox );
	button_delete->GetClickEvent() += OSHGui::ClickEventHandler( [ this, list ]( Control *sender ) {
		if( items.empty() || list->GetSelectedIndex() == -1 )
			return;

		OSHGui::MessageBox::ShowDialog( "Are you sure you want to delete the selected profile?", "", OSHGui::MessageBoxButtons::YesNo, [ this, list ]( OSHGui::DialogResult result ) {
			if( result == OSHGui::DialogResult::Yes ) {
				g_config.remove( items.at( index ) );
				list->RemoveItem( index );
				items = g_config.get_config_files();

				for( auto &item : items ) {
					// reinit list view items.
					for( int i = 0; i < list->GetItemsCount(); i++ ) {
						auto list_item = list->GetItem( i );
						if( !list_item )
							continue;

						if( item.c_str() == list_item->GetItemText() ) {
							list->RemoveItem( i );
							continue;
						}
					}

					list->AddItem( item.c_str() );
				}
			}
		});
	}); config2_groupbox->AddControl( button_delete );

	m_pages.at( PAGE_CONFIG )->AddControl( config2_groupbox );
}