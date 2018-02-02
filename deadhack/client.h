#pragma once

class Client {
private:
public:
	C_CSPlayer *m_local = nullptr;
	ConVar *c4_timer = nullptr;
	int m_tamper_check;
};

extern Client g_client;