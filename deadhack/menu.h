#pragma once

class Menu {
private:
public:
	//std::shared_ptr< OSHGui::Form > m_form;

	Menu();
	void init();

	class MainForm : public OSHGui::Form {
	private:
		void InitializeComponent();
	public:
		MainForm() : Form() {
			InitializeComponent();
		}
	};
};

extern Menu g_menu;