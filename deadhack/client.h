#pragma once

class Client {
private:
public:
	CUserCmd     *m_cmd = nullptr;
	C_CSPlayer   *m_local = nullptr;
	ConVar       *c4_timer = nullptr;

	int          m_tamper_check;
	bool         m_send_packet;
	int          m_ping;
	int          m_rtt;
	int          m_ur;
};

extern Client g_cl;