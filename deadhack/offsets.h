#pragma once

class Offsets {
private:
public:
	uint32_t m_iHealth;

	bool init() {
		m_iHealth = g_netvars.get( CT_HASH32( "DT_BasePlayer" ), CT_HASH32( "m_iHealth" ) );

		return true;
	}
};

extern Offsets g_offsets;