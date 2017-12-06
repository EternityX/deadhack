#pragma once

class MainForm : public OSHGui::Form
{
private:
	void initialize_component() {
		// todo - eternity; move all component initialization here
	}
public:
	MainForm() : Form() {
		initialize_component();
	}
};
