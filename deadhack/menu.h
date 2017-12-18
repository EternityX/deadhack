#pragma once

class Menu {
private:
public:
	std::shared_ptr< OSHGui::Form > m_form;

	Menu();
	void init();

	class MainForm : public OSHGui::Form {
	private:
		void initialize_component();
	public:
		MainForm() : Form() {
			initialize_component();
		}
	};
};

extern Menu g_menu;