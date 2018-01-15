#include "includes.h"

// going to use the outdated matrix for now...

void Visuals::work() {
	if( !g_client.m_local )
		return;

	for ( int i = 1; i <= g_csgo.m_entity_list->GetHighestEntityIndex(); i++ ) {
		C_CSPlayer* entity = (C_CSPlayer *)g_csgo.m_entity_list->GetClientEntity( i );
		if ( !entity )
			continue;
	}
}