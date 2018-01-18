#pragma once

class IClientUnknown;
class ClientClass;
class bf_read;

class IClientNetworkable {
public:
	virtual IClientUnknown *GetIClientUnknown() = 0;
	virtual void Release() = 0;
	virtual ClientClass *GetClientClass() = 0;
	virtual void NotifyShouldTransmit( int state ) = 0;
	virtual void OnPreDataChanged( int updateType ) = 0;
	virtual void OnDataChanged( int updateType ) = 0;
	virtual void PreDataUpdate( int updateType ) = 0;
	virtual void PostDataUpdate( int updateType ) = 0;
	virtual void __unkn() = 0;
	virtual bool IsDormant() = 0;
	virtual int GetIndex() const = 0;
	virtual void ReceiveMessage( int classID, bf_read &msg ) = 0;
	virtual void *GetDataTableBasePtr() = 0;
	virtual void SetDestroyedOnRecreateEntities() = 0;
};

//
//class IClientNetworkable {
//public:
//	ClientClass *GetClientClass() {
//		return Utils::get_method< ClientClass *(__thiscall *)( decltype( this ) )>( this, 2 )( this );
//	}
//
//	bool IsDormant() {
//		return Utils::get_method< bool(__thiscall *)( decltype( this ) )>( this, 9 )( this );
//	}
//
//	int GetIndex() {
//		return Utils::get_method< int(__thiscall *)( decltype( this ) )>( this, 10 )( this );
//	}
//};