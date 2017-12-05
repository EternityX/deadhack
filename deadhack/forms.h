#pragma once

class MainForm : public OSHGui::Form {
private:
	void InitializeComponent() {
		OSHGui::Button* test_button = new OSHGui::Button();
		test_button->SetText( "Button" );

		this->AddControl( test_button );
	}

public:
	MainForm() {
		InitializeComponent();
	}
};