#pragma once

class Offsets {
private:
public:
	ulong_t m_iHealth;
	ulong_t m_bGunGameImmunity;
	ulong_t m_bHasHelmet;
	ulong_t m_bHasDefuser;
	ulong_t m_iTeamNum;
	ulong_t m_iAccount;
	ulong_t m_hActiveWeapon;

	bool init() {
		m_iHealth = g_netvars.get( CT_HASH32( "DT_BasePlayer" ), CT_HASH32( "m_iHealth" ) );

		m_bGunGameImmunity = g_netvars.get( CT_HASH32( "DT_CSPlayer" ), CT_HASH32( "m_bGunGameImmunity" ) );
		m_bHasHelmet = g_netvars.get( CT_HASH32( "DT_CSPlayer" ), CT_HASH32( "m_bHasHelmet" ) );
		m_bHasDefuser = g_netvars.get( CT_HASH32( "DT_CSPlayer" ), CT_HASH32( "m_bHasDefuser" ) );
		m_iAccount = g_netvars.get( CT_HASH32( "DT_CSPlayer" ), CT_HASH32( "m_iAccount" ) );

		m_iTeamNum = g_netvars.get( CT_HASH32( "DT_BaseEntity" ), CT_HASH32( "m_iTeamNum" ) );

		m_hActiveWeapon = g_netvars.get( CT_HASH32( "DT_BaseCombatCharacter" ), CT_HASH32( "m_hActiveWeapon" ) );

		return true;
	}
};

extern Offsets g_offsets;