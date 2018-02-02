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
	VM_PUMA_WHITE_START

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
	m_tab_control->SetBackColor( OSHGui::Drawing::Color::FromARGB( 255, 32, 32, 38 ) );
	m_tab_control->SetLocation( 6, -15 );
	m_tab_control->SetButtonWidth( 116 );

	// add all pages to tab control.
	for( auto &item : m_pages )
		m_tab_control->AddTabPage( item.get() );

	this->AddControl( m_tab_control );

	VM_PUMA_WHITE_END
}

void MainForm::visuals() {
	// player esp groupbox.

	OSHGui::TabControl *player_tab = new OSHGui::TabControl();
	player_tab->SetSize( 241, 310 );
	player_tab->SetBackColor( OSHGui::Drawing::Color::FromARGB( 255, 27, 27, 34 ) );
	player_tab->SetFont( g_custom_renderer.m_instance->GetDefaultFont() );
	player_tab->SetButtonWidth( 81 );

	OSHGui::TabPage *generic_esp_page = new OSHGui::TabPage();
	generic_esp_page->SetText( "General" );
	generic_esp_page->SetBorder( false );

	OSHGui::TabPage *player_chams = new OSHGui::TabPage();
	player_chams->SetText( "Models" );
	player_chams->SetBorder( false );

	OSHGui::TabPage *extra_esp_page = new OSHGui::TabPage();
	extra_esp_page->SetText( "Extra" );
	extra_esp_page->SetBorder( false );

	player_tab->AddTabPage( generic_esp_page );
	player_tab->AddTabPage( player_chams );
	player_tab->AddTabPage( extra_esp_page );

	Controls::Groupbox *player_esp_groupbox = new Controls::Groupbox( "Player ESP", 17, 6, 260, 334 );

	player_esp_groupbox->AddControl( player_tab );

	// generic esp page.
	g_menu.m_control_x_pos = 19;
	Controls::Combobox *activation_type = new Controls::Combobox( "Activation type", { "Always", "On-key", "Toggle" }, 3, generic_esp_page, &g_cvar.m_visuals.activation_type->iValue, player_esp_groupbox->GetWidth() - 15 );
	Controls::Hotkey *activation_hotkey = new Controls::Hotkey( "Activation key", generic_esp_page, &g_cvar.m_visuals.activation_key->iValue, player_esp_groupbox->GetWidth() - 15 );
	Controls::Checkbox *teammates_check = new Controls::Checkbox( "Teammates", m_primary_color, generic_esp_page, &g_cvar.m_visuals.teammates->bValue );
	Controls::Checkbox *bbox_check = new Controls::Checkbox( "Bounding box", m_primary_color, generic_esp_page, &g_cvar.m_visuals.bbox->bValue );
	Controls::Checkbox *health_check = new Controls::Checkbox( "Health bar", m_primary_color, generic_esp_page, &g_cvar.m_visuals.healthbar->bValue );
	Controls::Checkbox *name_check = new Controls::Checkbox( "Name", m_primary_color, generic_esp_page, &g_cvar.m_visuals.name->bValue );
	Controls::Checkbox *weapon_check = new Controls::Checkbox( "Weapon", m_primary_color, generic_esp_page, &g_cvar.m_visuals.weapon->bValue );
	Controls::Combobox *ammo_combo = new Controls::Combobox( "Ammo", { "Off", "Bar", "Text" }, 3, generic_esp_page, &g_cvar.m_visuals.ammo->iValue, player_esp_groupbox->GetWidth() - 15 );
	Controls::Checkbox *flags_check = new Controls::Checkbox( "Flags", m_primary_color, generic_esp_page, &g_cvar.m_visuals.flags->bValue );
	Controls::Checkbox *money_check = new Controls::Checkbox( "Money", m_primary_color, generic_esp_page, &g_cvar.m_visuals.money->bValue );
	g_menu.m_control_x_pos = 27;

	// model page.
	g_menu.m_control_x_pos = 19;
	g_menu.m_control_y_pos = 10;
	Controls::Combobox *cham_type = new Controls::Combobox( "Type", { "Material", "Flat", "Gold" }, 3, player_chams, &g_cvar.m_visuals.cham_type->iValue, player_esp_groupbox->GetWidth() - 15 );
	Controls::Checkbox *player_chams_check = new Controls::Checkbox( "Player", m_primary_color, player_chams, &g_cvar.m_visuals.player_chams->bValue );
	Controls::Checkbox *ignorez_check = new Controls::Checkbox( "Two pass", m_primary_color, player_chams, &g_cvar.m_visuals.player_chams_ignorez->bValue );
	Controls::Checkbox *outline_check = new Controls::Checkbox( "Outline", m_primary_color, player_chams, &g_cvar.m_visuals.cham_outline->bValue );
	g_menu.m_control_x_pos = 27;

	// other visuals groupbox.
	Controls::Groupbox *other_esp_groupbox = new Controls::Groupbox( "World ESP", player_esp_groupbox->GetRight() + 19, 6, 259, 150 );
	Controls::Checkbox *dropped_weapon_check = new Controls::Checkbox( "Dropped weapons", m_primary_color, other_esp_groupbox, &g_cvar.m_visuals.dropped_weapons->bValue );
	Controls::Checkbox *objective_check = new Controls::Checkbox( "Objectives", m_primary_color, other_esp_groupbox, &g_cvar.m_visuals.objectives->bValue );

	// effects groupbox.
	OSHGui::TabControl *effects_tab = new OSHGui::TabControl();
	effects_tab->SetSize( 241, 100 );
	effects_tab->SetBackColor( OSHGui::Drawing::Color::FromARGB( 255, 27, 27, 34 ) );
	effects_tab->SetFont( g_custom_renderer.m_instance->GetDefaultFont() );
	effects_tab->SetButtonWidth( 121 );

	OSHGui::TabPage *general_effects_page = new OSHGui::TabPage();
	general_effects_page->SetText( "General" );
	general_effects_page->SetBorder( false );

	OSHGui::TabPage *removals_page = new OSHGui::TabPage();
	removals_page->SetText( "Removals" );
	removals_page->SetBorder( false );

	effects_tab->AddTabPage( general_effects_page );
	effects_tab->AddTabPage( removals_page );

	Controls::Groupbox *effects_groupbox = new Controls::Groupbox( "Effects", player_esp_groupbox->GetRight() + 19, other_esp_groupbox->GetBottom() + 14, 259, 170 );

	effects_groupbox->AddControl( effects_tab );

	// general effects page.
	g_menu.m_control_x_pos = 19;
	Controls::Slider *overridefov_slider = new Controls::Slider( "Camera FOV", m_primary_color, general_effects_page, 0, 180, &g_cvar.m_visuals.override_fov->iValue );
	Controls::Slider *weaponfov_slider = new Controls::Slider( "Weapon FOV", m_primary_color, general_effects_page, 0, 180, &g_cvar.m_visuals.weapon_fov->iValue );
	Controls::Checkbox *fullbright_check = new Controls::Checkbox( "Fullbright", m_primary_color, general_effects_page, &g_cvar.m_visuals.fullbright->bValue );
	Controls::Checkbox *nightmode_check = new Controls::Checkbox( "Nightmode", m_primary_color, general_effects_page, &g_cvar.m_visuals.nightmode->bValue );
	//Controls::Checkbox *drawgray_check = new Controls::Checkbox( "Draw gray", m_primary_color, general_effects_page, &g_cvar.m_visuals.draw_gray->bValue );
	//Controls::Checkbox *lowres_check = new Controls::Checkbox( "Low resolution textures", m_primary_color, general_effects_page, &g_cvar.m_visuals.low_res->bValue );
	g_menu.m_control_x_pos = 27;

	// removals page.
	g_menu.m_control_x_pos = 19;
	g_menu.m_control_y_pos = 10;
	Controls::Checkbox *remove_fog_check = new Controls::Checkbox( "Remove fog", m_primary_color, removals_page, &g_cvar.m_visuals.remove_fog->bValue );
	Controls::Checkbox *remove_scopedoverlay_check = new Controls::Checkbox( "Remove scope overlay", m_primary_color, removals_page, &g_cvar.m_visuals.remove_scope->bValue );
	Controls::Checkbox *remove_scopedirt_check = new Controls::Checkbox( "Remove scope dirt", m_primary_color, removals_page, &g_cvar.m_visuals.remove_scopedirt->bValue );
	g_menu.m_control_x_pos = 27;

	m_pages.at( PAGE_VISUALS )->AddControl( effects_groupbox );
	m_pages.at( PAGE_VISUALS )->AddControl( other_esp_groupbox );
	m_pages.at( PAGE_VISUALS )->AddControl( player_esp_groupbox );
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