#include "includes.h"

void Menu::init() {
	// create form.
	m_form = std::static_pointer_cast< OSHGui::Form >( std::make_shared< MainForm >() );

	// set form as mainform.
	g_custom_renderer.m_instance->Run( m_form );

	OSHGui::Timer *timer = new OSHGui::Timer();
	timer->SetInterval( 100 );
	timer->Start();
	m_form->AddControl( timer );

	timer->GetTickEvent() += OSHGui::TickEventHandler( [ this ]( OSHGui::Control *sender ) {
		g_custom_renderer.m_instance->SetPrimaryColor( g_config.string_to_color( 1.f, g_cvar.m_colors.menu_accent_color->szValue ) );
		g_menu.m_form->SetBackColor( g_custom_renderer.m_instance->GetPrimaryColor() );
	});
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

void MainForm::legitbot() {
	OSHGui::TabControl *weapon_group_tab = new OSHGui::TabControl();
	weapon_group_tab->SetSize( 261, 310 );
	weapon_group_tab->SetLocation( 16, 10 );
	weapon_group_tab->SetBackColor( OSHGui::Drawing::Color::FromARGB( 255, 32, 32, 38 ) );
	weapon_group_tab->SetFont( g_custom_renderer.m_instance->GetDefaultFont() );
	weapon_group_tab->SetButtonWidth( 53 );

	OSHGui::TabPage *pistols_page = new OSHGui::TabPage();
	pistols_page->SetText( "Pistol" );
	pistols_page->SetBorder( false );

	OSHGui::TabPage *smgs_page = new OSHGui::TabPage();
	smgs_page->SetText( "SMG" );
	smgs_page->SetBorder( false );

	OSHGui::TabPage *rifles_page = new OSHGui::TabPage();
	rifles_page->SetText( "Rifle" );
	rifles_page->SetBorder( false );

	OSHGui::TabPage *shotguns_page = new OSHGui::TabPage();
	shotguns_page->SetText( "Shotgun" );
	shotguns_page->SetBorder( false );

	OSHGui::TabPage *snipers_page = new OSHGui::TabPage();
	snipers_page->SetText( "Sniper" );
	snipers_page->SetBorder( false );

	weapon_group_tab->AddTabPage( pistols_page );
	weapon_group_tab->AddTabPage( smgs_page );
	weapon_group_tab->AddTabPage( rifles_page );
	weapon_group_tab->AddTabPage( shotguns_page );
	weapon_group_tab->AddTabPage( snipers_page );

	// ================= PISTOLS
	Controls::Groupbox *pistol_general_groupbox = new Controls::Groupbox( "General", -1, 13, 260, 234 );
	pistols_page->AddControl( pistol_general_groupbox );

	Controls::Combobox *pistol_historyaim_type = new Controls::Combobox( "History aim", { "Off", "Low", "Medium", "High" }, 5, pistol_general_groupbox, &g_cvar.m_legit.pistol_historyaim->iValue, pistol_general_groupbox->GetWidth() - 15 );

	Controls::Groupbox *pistol_trigger_groupbox = new Controls::Groupbox( "Triggerbot", pistol_general_groupbox->GetRight() + 19, -31, 259, 254 );

	Controls::Checkbox *pistol_trigger_check = new Controls::Checkbox( "Enabled", pistol_trigger_groupbox, &g_cvar.m_legit.pistol_trigger->bValue );
	Controls::Hotkey *pistol_trigger_activation_hotkey = new Controls::Hotkey( "Activation key", pistol_trigger_groupbox, &g_cvar.m_legit.pistol_trigger_key->iValue, pistol_trigger_groupbox->GetWidth() );
	Controls::Combobox *pistol_trigger_hitgroup = new Controls::Combobox( "Hitgroup", { "Head only", "Body only", "Upper body", "All" }, 5, pistol_trigger_groupbox, &g_cvar.m_legit.pistol_trigger_hitgroup->iValue, pistol_trigger_groupbox->GetWidth() );
	Controls::Slider *pistol_trigger_hitchance = new Controls::Slider( "Hitchance seed", pistol_trigger_groupbox, 0, 255, &g_cvar.m_legit.pistol_trigger_hitchance->iValue );
	Controls::Checkbox *pistol_trigger_ignoreair_check = new Controls::Checkbox( "Disable in-air", pistol_trigger_groupbox, &g_cvar.m_legit.pistol_trigger_ignoreair->bValue );
	Controls::Checkbox *pistol_trigger_ignoresmoke_check = new Controls::Checkbox( "Disable through smoke", pistol_trigger_groupbox, &g_cvar.m_legit.pistol_trigger_ignoresmoke->bValue );
	Controls::Checkbox *pistol_trigger_ignoreflashed_check = new Controls::Checkbox( "Disable when flashed", pistol_trigger_groupbox, &g_cvar.m_legit.pistol_trigger_ignoreflash->bValue );
	Controls::Slider *pistol_trigger_delay = new Controls::Slider( "Delay", pistol_trigger_groupbox, 0, 500, &g_cvar.m_legit.pistol_trigger_delay->iValue );
	Controls::Checkbox *pistol_trigger_team_check = new Controls::Checkbox( "Teammate", pistol_trigger_groupbox, &g_cvar.m_legit.pistol_trigger_team->bValue );

	pistols_page->AddControl( pistol_trigger_groupbox );

	// ================= SMGS
	Controls::Groupbox *smg_general_groupbox = new Controls::Groupbox( "General", -1, 13, 260, 234 );
	smgs_page->AddControl( smg_general_groupbox );

	Controls::Combobox *smg_historyaim_type = new Controls::Combobox( "History aim", { "Off", "Low", "Medium", "High" }, 5, smg_general_groupbox, &g_cvar.m_legit.smg_historyaim->iValue, smg_general_groupbox->GetWidth() - 15 );

	Controls::Groupbox *smg_trigger_groupbox = new Controls::Groupbox( "Triggerbot", smg_general_groupbox->GetRight() + 19, -31, 259, 254 );

	Controls::Checkbox *smg_trigger_check = new Controls::Checkbox( "Enabled", smg_trigger_groupbox, &g_cvar.m_legit.smg_trigger->bValue );	
	Controls::Hotkey *smg_trigger_activation_hotkey = new Controls::Hotkey( "Activation key", smg_trigger_groupbox, &g_cvar.m_legit.smg_trigger_key->iValue, smg_trigger_groupbox->GetWidth() );
	Controls::Combobox *smg_trigger_hitgroup = new Controls::Combobox( "Hitgroup", { "Head only", "Body only", "Upper body", "All" }, 5, smg_trigger_groupbox, &g_cvar.m_legit.smg_trigger_hitgroup->iValue, smg_trigger_groupbox->GetWidth() );
	Controls::Slider *smg_trigger_hitchance = new Controls::Slider( "Hitchance seed", smg_trigger_groupbox, 0, 255, &g_cvar.m_legit.smg_trigger_hitchance->iValue );
	Controls::Checkbox *smg_trigger_ignoreair_check = new Controls::Checkbox( "Disable in-air", smg_trigger_groupbox, &g_cvar.m_legit.smg_trigger_ignoreair->bValue );
	Controls::Checkbox *smg_trigger_ignoresmoke_check = new Controls::Checkbox( "Disable through smoke", smg_trigger_groupbox, &g_cvar.m_legit.smg_trigger_ignoresmoke->bValue );
	Controls::Checkbox *smg_trigger_ignoreflashed_check = new Controls::Checkbox( "Disable when flashed", smg_trigger_groupbox, &g_cvar.m_legit.smg_trigger_ignoreflash->bValue );
	Controls::Slider *smg_trigger_delay = new Controls::Slider( "Delay", smg_trigger_groupbox, 0, 500, &g_cvar.m_legit.smg_trigger_delay->iValue );
	Controls::Checkbox *smg_trigger_team_check = new Controls::Checkbox( "Teammate", smg_trigger_groupbox, &g_cvar.m_legit.smg_trigger_team->bValue );

	smgs_page->AddControl( smg_trigger_groupbox );

	// ================= RIFLES
	Controls::Groupbox *rifles_general_groupbox = new Controls::Groupbox( "General", -1, 13, 260, 234 );
	rifles_page->AddControl( rifles_general_groupbox );

	Controls::Combobox *rifle_historyaim_type = new Controls::Combobox( "History aim", { "Off", "Low", "Medium", "High" }, 5, rifles_general_groupbox, &g_cvar.m_legit.rifle_historyaim->iValue, rifles_general_groupbox->GetWidth() - 15 );

	Controls::Groupbox *rifle_trigger_groupbox = new Controls::Groupbox( "Triggerbot", rifles_general_groupbox->GetRight() + 19, -31, 259, 254 );

	Controls::Checkbox *rifle_trigger_check = new Controls::Checkbox( "Enabled", rifle_trigger_groupbox, &g_cvar.m_legit.rifle_trigger->bValue );
	Controls::Hotkey *rifle_trigger_activation_hotkey = new Controls::Hotkey( "Activation key", rifle_trigger_groupbox, &g_cvar.m_legit.rifle_trigger_key->iValue, rifle_trigger_groupbox->GetWidth() );
	Controls::Combobox *rifle_trigger_hitgroup = new Controls::Combobox( "Hitgroup", { "Head only", "Body only", "Upper body", "All" }, 5, rifle_trigger_groupbox, &g_cvar.m_legit.rifle_trigger_hitgroup->iValue, rifle_trigger_groupbox->GetWidth() );
	Controls::Slider *rifle_trigger_hitchance = new Controls::Slider( "Hitchance seed", rifle_trigger_groupbox, 0, 255, &g_cvar.m_legit.rifle_trigger_hitchance->iValue );
	Controls::Checkbox *rifle_trigger_ignoreair_check = new Controls::Checkbox( "Disable in-air", rifle_trigger_groupbox, &g_cvar.m_legit.rifle_trigger_ignoreair->bValue );
	Controls::Checkbox *rifle_trigger_ignoresmoke_check = new Controls::Checkbox( "Disable through smoke", rifle_trigger_groupbox, &g_cvar.m_legit.rifle_trigger_ignoresmoke->bValue );
	Controls::Checkbox *rifle_trigger_ignoreflashed_check = new Controls::Checkbox( "Disable when flashed", rifle_trigger_groupbox, &g_cvar.m_legit.rifle_trigger_ignoreflash->bValue );
	Controls::Slider *rifle_trigger_delay = new Controls::Slider( "Delay", rifle_trigger_groupbox, 0, 500, &g_cvar.m_legit.rifle_trigger_delay->iValue );
	Controls::Checkbox *rifle_trigger_team_check = new Controls::Checkbox( "Teammate", rifle_trigger_groupbox, &g_cvar.m_legit.rifle_trigger_team->bValue );

	rifles_page->AddControl( rifle_trigger_groupbox );

	// ================= SHOTGUNS
	Controls::Groupbox *shotguns_general_groupbox = new Controls::Groupbox( "General", -1, 13, 260, 234 );
	shotguns_page->AddControl( shotguns_general_groupbox );

	Controls::Combobox *shotguns_historyaim_type = new Controls::Combobox( "History aim", { "Off", "Low", "Medium", "High" }, 5, shotguns_general_groupbox, &g_cvar.m_legit.shotgun_historyaim->iValue, shotguns_general_groupbox->GetWidth() - 15 );

	Controls::Groupbox *shotgun_trigger_groupbox = new Controls::Groupbox( "Triggerbot", shotguns_general_groupbox->GetRight() + 19, -31, 259, 254 );

	Controls::Checkbox *shotgun_trigger_check = new Controls::Checkbox( "Enabled", shotgun_trigger_groupbox, &g_cvar.m_legit.shotgun_trigger->bValue );
	Controls::Hotkey *shotgun_trigger_activation_hotkey = new Controls::Hotkey( "Activation key", shotgun_trigger_groupbox, &g_cvar.m_legit.shotgun_trigger_key->iValue, shotgun_trigger_groupbox->GetWidth() );
	Controls::Combobox *shotgun_trigger_hitgroup = new Controls::Combobox( "Hitgroup", { "Head only", "Body only", "Upper body", "All" }, 5, shotgun_trigger_groupbox, &g_cvar.m_legit.shotgun_trigger_hitgroup->iValue, shotgun_trigger_groupbox->GetWidth() );
	Controls::Slider *shotgun_trigger_hitchance = new Controls::Slider( "Hitchance seed", shotgun_trigger_groupbox, 0, 255, &g_cvar.m_legit.shotgun_trigger_hitchance->iValue );
	Controls::Checkbox *shotgun_trigger_ignoreair_check = new Controls::Checkbox( "Disable in-air", shotgun_trigger_groupbox, &g_cvar.m_legit.shotgun_trigger_ignoreair->bValue );
	Controls::Checkbox *shotgun_trigger_ignoresmoke_check = new Controls::Checkbox( "Disable through smoke", shotgun_trigger_groupbox, &g_cvar.m_legit.shotgun_trigger_ignoresmoke->bValue );
	Controls::Checkbox *shotgun_trigger_ignoreflashed_check = new Controls::Checkbox( "Disable when flashed", shotgun_trigger_groupbox, &g_cvar.m_legit.shotgun_trigger_ignoreflash->bValue );
	Controls::Slider *shotgun_trigger_delay = new Controls::Slider( "Delay", shotgun_trigger_groupbox, 0, 500, &g_cvar.m_legit.shotgun_trigger_delay->iValue );
	Controls::Checkbox *shotgun_trigger_team_check = new Controls::Checkbox( "Teammate", shotgun_trigger_groupbox, &g_cvar.m_legit.shotgun_trigger_team->bValue );

	shotguns_page->AddControl( shotgun_trigger_groupbox );

	// ================= SNIPERS
	Controls::Groupbox *sniper_general_groupbox = new Controls::Groupbox( "General", -1, 13, 260, 234 );
	snipers_page->AddControl( sniper_general_groupbox );

	Controls::Combobox *sniper_historyaim_type = new Controls::Combobox( "History aim", { "Off", "Low", "Medium", "High" }, 5, sniper_general_groupbox, &g_cvar.m_legit.sniper_historyaim->iValue, sniper_general_groupbox->GetWidth() - 15 );

	Controls::Groupbox *sniper_trigger_groupbox = new Controls::Groupbox( "Triggerbot", sniper_general_groupbox->GetRight() + 19, -31, 259, 254 );

	Controls::Checkbox *sniper_trigger_check = new Controls::Checkbox( "Enabled", sniper_trigger_groupbox, &g_cvar.m_legit.sniper_trigger->bValue );
	Controls::Hotkey *sniper_trigger_activation_hotkey = new Controls::Hotkey( "Activation key", sniper_trigger_groupbox, &g_cvar.m_legit.sniper_trigger_key->iValue, sniper_trigger_groupbox->GetWidth() );
	Controls::Combobox *sniper_trigger_hitgroup = new Controls::Combobox( "Hitgroup", { "Head only", "Body only", "Upper body", "All" }, 5, sniper_trigger_groupbox, &g_cvar.m_legit.sniper_trigger_hitgroup->iValue, sniper_trigger_groupbox->GetWidth() );
	Controls::Slider *sniper_trigger_hitchance = new Controls::Slider( "Hitchance seed", sniper_trigger_groupbox, 0, 255, &g_cvar.m_legit.sniper_trigger_hitchance->iValue );
	Controls::Checkbox *sniper_trigger_ignoreair_check = new Controls::Checkbox( "Disable in-air", sniper_trigger_groupbox, &g_cvar.m_legit.sniper_trigger_ignoreair->bValue );
	Controls::Checkbox *sniper_trigger_ignoresmoke_check = new Controls::Checkbox( "Disable through smoke", sniper_trigger_groupbox, &g_cvar.m_legit.sniper_trigger_ignoresmoke->bValue );
	Controls::Checkbox *sniper_trigger_ignoreflashed_check = new Controls::Checkbox( "Disable when flashed", sniper_trigger_groupbox, &g_cvar.m_legit.sniper_trigger_ignoreflash->bValue );
	Controls::Slider *sniper_trigger_delay = new Controls::Slider( "Delay", sniper_trigger_groupbox, 0, 500, &g_cvar.m_legit.sniper_trigger_delay->iValue );
	Controls::Checkbox *sniper_trigger_team_check = new Controls::Checkbox( "Teammate", sniper_trigger_groupbox, &g_cvar.m_legit.sniper_trigger_team->bValue );

	snipers_page->AddControl( sniper_trigger_groupbox );

	m_pages.at( PAGE_LEGITBOT )->AddControl( weapon_group_tab );
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
	Controls::Checkbox *visibleonly_check = new Controls::Checkbox( "Visible only", generic_esp_page, &g_cvar.m_visuals.visible_only->bValue );
	Controls::Checkbox *throughsmoke_check = new Controls::Checkbox( "Disable through smoke", generic_esp_page, &g_cvar.m_visuals.disable_thru_smoke->bValue );
	Controls::Checkbox *teammates_check = new Controls::Checkbox( "Teammate", generic_esp_page, &g_cvar.m_visuals.teammates->bValue );

	Controls::Checkbox *bbox_check = new Controls::Checkbox( "Bounding box", generic_esp_page, &g_cvar.m_visuals.bbox->bValue );
	Controls::ColorButton *box_color = new Controls::ColorButton( generic_esp_page, bbox_check, g_cvar.m_colors.box_color->szValue );

	Controls::Checkbox *health_check = new Controls::Checkbox( "Health bar", generic_esp_page, &g_cvar.m_visuals.healthbar->bValue );
	Controls::Checkbox *name_check = new Controls::Checkbox( "Name", generic_esp_page, &g_cvar.m_visuals.name->bValue );
	Controls::Checkbox *weapon_check = new Controls::Checkbox( "Weapon", generic_esp_page, &g_cvar.m_visuals.weapon->bValue );
	Controls::Combobox *ammo_combo = new Controls::Combobox( "Ammo", { "Off", "Bar", "Text" }, 3, generic_esp_page, &g_cvar.m_visuals.ammo->iValue, player_esp_groupbox->GetWidth() - 15 );
	Controls::Checkbox *flags_check = new Controls::Checkbox( "Flags", generic_esp_page, &g_cvar.m_visuals.flags->bValue );
	g_menu.m_control_x_pos = 27;

	// model page.
	g_menu.m_control_x_pos = 19;
	g_menu.m_control_y_pos = 10;
	Controls::Checkbox *player_chams_check = new Controls::Checkbox( "Player", player_chams, &g_cvar.m_visuals.player_chams->bValue );
	Controls::Checkbox *ignorez_check = new Controls::Checkbox( "Two-pass", player_chams, &g_cvar.m_visuals.player_chams_ignorez->bValue );
	Controls::Checkbox *outline_check = new Controls::Checkbox( "Outline", player_chams, &g_cvar.m_visuals.cham_outline->bValue );

	Controls::Combobox *cham_type = new Controls::Combobox( "Type", { "Material", "Flat", "Rim", "Model hull", "Pulsate", "Gold", "Wildfire" }, 5, player_chams, &g_cvar.m_visuals.cham_type->iValue, player_esp_groupbox->GetWidth() - 15 );
	Controls::Combobox *twopass_type = new Controls::Combobox( "Two-pass type", { "Material", "Flat", "Rim", "Model hull", "Pulsate", "Gold", "Wildfire" }, 5, player_chams, &g_cvar.m_visuals.cham_twopass_type->iValue, player_esp_groupbox->GetWidth() - 15 );

	Controls::Combobox *lagrecord_combo = new Controls::Combobox( "Lag record", { "Off", "All records", "Oldest record" }, 3, player_chams, &g_cvar.m_visuals.cham_lagrecords->iValue, player_esp_groupbox->GetWidth() - 15 );
	
	Controls::Checkbox *arms_check = new Controls::Checkbox( "Arms", player_chams, &g_cvar.m_visuals.cham_arms->bValue );
	Controls::Checkbox *weaponcham_check = new Controls::Checkbox( "Local weapon", player_chams, &g_cvar.m_visuals.cham_weapon->bValue );

	Controls::ColorButton *weapon_color = new Controls::ColorButton( player_chams, weaponcham_check, g_cvar.m_colors.weapon_cham_color->szValue );
	Controls::ColorButton *arms_color = new Controls::ColorButton( player_chams, arms_check, g_cvar.m_colors.arms_color->szValue );
	Controls::ColorButton *record_color = new Controls::ColorButton( player_chams, lagrecord_combo, g_cvar.m_colors.lag_record_color->szValue );
	Controls::ColorButton *ignorez_color = new Controls::ColorButton( player_chams, ignorez_check, g_cvar.m_colors.ignorez_color->szValue );
	Controls::ColorButton *chams_color = new Controls::ColorButton( player_chams, player_chams_check, g_cvar.m_colors.cham_color->szValue );
	g_menu.m_control_x_pos = 27;

	// extra player.
	g_menu.m_control_x_pos = 19;
	g_menu.m_control_y_pos = 10;
	Controls::Checkbox *lagrecord_check = new Controls::Checkbox( "Lag records", extra_esp_page, &g_cvar.m_visuals.lagrecord->bValue );
	Controls::Checkbox *skeleton_check = new Controls::Checkbox( "Skeleton", extra_esp_page, &g_cvar.m_visuals.skeleton->bValue );
	Controls::Checkbox *money_check = new Controls::Checkbox( "Money", extra_esp_page, &g_cvar.m_visuals.money->bValue );
	Controls::Checkbox *defuser_check = new Controls::Checkbox( "Defuser", extra_esp_page, &g_cvar.m_visuals.defuser->bValue );
	Controls::Checkbox *glow_check = new Controls::Checkbox( "Glow", extra_esp_page, &g_cvar.m_visuals.glow->bValue );
	Controls::Combobox *glow_type_combo = new Controls::Combobox( "Type", { "Normal", "Models", "Inline", "Inline pulsate" }, 5, extra_esp_page, &g_cvar.m_visuals.glow_type->iValue, player_esp_groupbox->GetWidth() - 15 );

	Controls::ColorButton *glow_color = new Controls::ColorButton( extra_esp_page, glow_check, g_cvar.m_colors.glow_color->szValue );
	Controls::ColorButton *skeleton_color = new Controls::ColorButton( extra_esp_page, skeleton_check, g_cvar.m_colors.skeleton_color->szValue );
	Controls::ColorButton *lagrecord_color = new Controls::ColorButton( extra_esp_page, lagrecord_check, g_cvar.m_colors.lag_record_color->szValue );
	g_menu.m_control_x_pos = 27;

	// other visuals groupbox.
	OSHGui::TabControl *world_tab = new OSHGui::TabControl();
	world_tab->SetSize( 241, 100 );
	world_tab->SetBackColor( OSHGui::Drawing::Color::FromARGB( 255, 27, 27, 34 ) );
	world_tab->SetFont( g_custom_renderer.m_instance->GetDefaultFont() );
	world_tab->SetButtonWidth( 121 );

	OSHGui::TabPage *generic_world = new OSHGui::TabPage();
	generic_world->SetText( "General" );
	generic_world->SetBorder( false );

	OSHGui::TabPage *world_chams = new OSHGui::TabPage();
	world_chams->SetText( "Extra" );
	world_chams->SetBorder( false );

	world_tab->AddTabPage( generic_world );
	world_tab->AddTabPage( world_chams );

	Controls::Groupbox *other_esp_groupbox = new Controls::Groupbox( "World ESP", player_esp_groupbox->GetRight() + 19, 6, 259, 150 );

	other_esp_groupbox->AddControl( world_tab );

	g_menu.m_control_x_pos = 19;
	Controls::Checkbox *dropped_weapon_check = new Controls::Checkbox( "Dropped weapon", generic_world, &g_cvar.m_visuals.dropped_weapons->bValue );
	Controls::Checkbox *objective_check = new Controls::Checkbox( "Objective", generic_world, &g_cvar.m_visuals.objectives->bValue );
	Controls::Checkbox *bullettracer_check = new Controls::Checkbox( "Bullet tracer", generic_world, &g_cvar.m_visuals.bullet_tracer->bValue );
	Controls::Checkbox *grenade_check = new Controls::Checkbox( "Grenade", generic_world, &g_cvar.m_visuals.grenade_projectiles->bValue );
	Controls::Checkbox *grenadetrajectory_check = new Controls::Checkbox( "Grenade trajectory", generic_world, &g_cvar.m_visuals.grenade_trajectory->bValue );
	Controls::ColorButton *trajectory_color = new Controls::ColorButton( generic_world, grenadetrajectory_check, g_cvar.m_colors.trajectory_color->szValue );
	Controls::ColorButton *tracer_color = new Controls::ColorButton( generic_world, bullettracer_check, g_cvar.m_colors.tracer_color->szValue );
	g_menu.m_control_x_pos = 27;

	g_menu.m_control_x_pos = 19;
	g_menu.m_control_y_pos = 10;
	//::Checkbox *crosshair = new Controls::Checkbox( "Sniper crosshair", world_chams, &g_cvar.m_visuals.cham_chicken->bValue );
	//Controls::Checkbox *playerweaponcham_check = new Controls::Checkbox( "Player weapon", world_chams, &g_cvar.m_visuals.champlayer_weapon->bValue );
	Controls::Checkbox *hitmarker_check = new Controls::Checkbox( "Hitmarker", world_chams, &g_cvar.m_visuals.hitmarker->bValue );
	Controls::Checkbox *inaccuracy_check = new Controls::Checkbox( "Visualize inaccuracy", world_chams, &g_cvar.m_visuals.inaccuracy->bValue );
	Controls::Checkbox *chicken_check = new Controls::Checkbox( "Chicken", world_chams, &g_cvar.m_visuals.chicken->bValue );

	Controls::ColorButton *inaccuracy_color = new Controls::ColorButton( world_chams, inaccuracy_check, g_cvar.m_colors.inaccuracy_color->szValue );
	g_menu.m_control_x_pos = 27;

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
	Controls::Slider *overridefov_slider = new Controls::Slider( "Camera FOV", general_effects_page, 0, 180, &g_cvar.m_visuals.override_fov->iValue );
	Controls::Slider *weaponfov_slider = new Controls::Slider( "Weapon FOV", general_effects_page, 0, 180, &g_cvar.m_visuals.weapon_fov->iValue );
	Controls::Checkbox *fullbright_check = new Controls::Checkbox( "Fullbright", general_effects_page, &g_cvar.m_visuals.fullbright->bValue );
	//Controls::Checkbox *nightmode_check = new Controls::Checkbox( "Nightmode", general_effects_page, &g_cvar.m_visuals.nightmode->bValue );
	//Controls::Checkbox *drawgray_check = new Controls::Checkbox( "Draw gray", general_effects_page, &g_cvar.m_visuals.draw_gray->bValue );
	//Controls::Checkbox *lowres_check = new Controls::Checkbox( "Low resolution textures", general_effects_page, &g_cvar.m_visuals.low_res->bValue );
	g_menu.m_control_x_pos = 27;

	// removals page.
	g_menu.m_control_x_pos = 19;
	g_menu.m_control_y_pos = 10;
	Controls::Checkbox *remove_fog_check = new Controls::Checkbox( "Fog", removals_page, &g_cvar.m_visuals.remove_fog->bValue );
	Controls::Checkbox *remove_scopedoverlay_check = new Controls::Checkbox( "Scope overlay", removals_page, &g_cvar.m_visuals.remove_scope->bValue );
	Controls::Checkbox *remove_scopedirt_check = new Controls::Checkbox( "Scope clutter", removals_page, &g_cvar.m_visuals.remove_scopedirt->bValue );
	Controls::Checkbox *remove_pp_check = new Controls::Checkbox( "Post processing", removals_page, &g_cvar.m_visuals.remove_post_processing->bValue );
	Controls::Checkbox *remove_smoke_check = new Controls::Checkbox( "Smoke", removals_page, &g_cvar.m_visuals.remove_smoke->bValue );
	Controls::Checkbox *remove_flash = new Controls::Checkbox( "Flash", removals_page, &g_cvar.m_visuals.remove_flash->bValue );
	g_menu.m_control_x_pos = 27;

	m_pages.at( PAGE_VISUALS )->AddControl( effects_groupbox );
	m_pages.at( PAGE_VISUALS )->AddControl( other_esp_groupbox );
	m_pages.at( PAGE_VISUALS )->AddControl( player_esp_groupbox );
}

void MainForm::misc() {
	Controls::Groupbox *general_groupbox = new Controls::Groupbox( "General", 17, 6, 260, 334 );

	Controls::Checkbox *remove_fog_check = new Controls::Checkbox( "Bunnyhop", general_groupbox, &g_cvar.m_misc.bunnyhop->bValue );
	Controls::Checkbox *spectators_check = new Controls::Checkbox( "Spectators", general_groupbox, &g_cvar.m_misc.spectators->bValue );
	Controls::Checkbox *buylog_check = new Controls::Checkbox( "Log weapon purchases", general_groupbox, &g_cvar.m_misc.buy_log->bValue );
	Controls::Checkbox *hurtlog_check = new Controls::Checkbox( "Log damage dealt", general_groupbox, &g_cvar.m_misc.hurt_log->bValue );
	Controls::Checkbox *hitsound_check = new Controls::Checkbox( "Hit sound", general_groupbox, &g_cvar.m_misc.hitsound->bValue );
	Controls::Checkbox *clantag_check = new Controls::Checkbox( "Clantag", general_groupbox, &g_cvar.m_misc.clantag->bValue );
	Controls::Checkbox *radar_check = new Controls::Checkbox( "Radar", general_groupbox, &g_cvar.m_misc.radar->bValue );
	Controls::Checkbox *revealranks_check = new Controls::Checkbox( "Reveal competitive ranks", general_groupbox, &g_cvar.m_misc.reveal_ranks->bValue );
	Controls::Checkbox *autopistol_check = new Controls::Checkbox( "Automatic pistol", general_groupbox, &g_cvar.m_misc.autopistol->bValue );

	m_pages.at( PAGE_MISC )->AddControl( general_groupbox );
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
		if( name_textbox->GetText().empty() ) {
			OSHGui::MessageBox::Show( "You must set a name." );
			return;
		}

		if( name_textbox->GetText().length() > 25 ) {
			OSHGui::MessageBox::Show( "Profile name cannot exceed 25 characters in length." );
			return;
		}

		if( items.size() > 100 ) {
			OSHGui::MessageBox::Show( "You cannot create anymore profiles." );
			return;
		}

		if( name_textbox->GetText() == "default" ) {
			OSHGui::MessageBox::Show( "You cannot replace the default profile." );
			return;
		}

		g_config.load( "default.cfg" );
		g_config.save( name_textbox->GetText(), false );

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

		if( items.at( index ) == "default.cfg" ) {
			OSHGui::MessageBox::Show( "You cannot delete the default profile." );
			return;
		}

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

	OSHGui::Label *menu_color = new OSHGui::Label();
	menu_color->SetText( "Menu accent" );
	menu_color->SetForeColor( OSHColor::FromARGB( 255, 201, 201, 201 ) );
	menu_color->SetFont( g_custom_renderer.m_fonts.at( 0 ) );
	menu_color->SetStyle( 1 );
	menu_color->SetLocation( config2_groupbox->GetWidth() / 2 - menu_color->GetWidth() / 2 - 51, config2_groupbox->GetBottom() - 37 );
	config2_groupbox->AddControl( menu_color );

	Controls::ColorButton *menu_color_selector = new Controls::ColorButton( config2_groupbox->GetWidth() / 2 - menu_color->GetWidth() / 2 + 95, config2_groupbox->GetBottom() - 35, config2_groupbox, g_cvar.m_colors.menu_accent_color->szValue );
	

	m_pages.at( PAGE_CONFIG )->AddControl( config2_groupbox );
}