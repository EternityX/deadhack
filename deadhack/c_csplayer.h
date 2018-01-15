#pragma once

class C_CSPlayer {
private:

public:
	static C_CSPlayer* get_local() {
		return (C_CSPlayer *)g_csgo.m_entity_list->GetClientEntity( g_csgo.m_engine->GetLocalPlayer() );
	}
};
