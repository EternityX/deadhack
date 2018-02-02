#pragma once

class IPanel {
public:
	const char *GetName( int vguiPanel ) {
		return Utils::get_method< const char *(__thiscall *)( decltype( this ), int )>( this, 36 )( this, vguiPanel );
	}
};