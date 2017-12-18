#pragma once

class Menu {
private:

public:
	std::shared_ptr< OSHGui::Form > m_form;

	Menu();
	void init();

	class MainForm : public OSHGui::Form {
	private:
		OSHGui::Drawing::Color m_primary_color = OSHGui::Drawing::Color::FromARGB( 255, 206, 115, 136 );

		// pages
		OSHGui::TabPage *m_page_legitbot;
		OSHGui::TabPage *m_page_ragebot;
		OSHGui::TabPage *m_tab_visuals;
		OSHGui::TabPage *m_tab_misc;
		OSHGui::TabPage *m_tab_config;

		void InitializeComponent();
		void create_tabs();
		void legitbot();
	public:
		MainForm() : Form() {
			InitializeComponent();
		}
	};
};

extern Menu g_menu;