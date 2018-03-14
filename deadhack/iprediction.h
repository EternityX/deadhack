#pragma once

class IMoveHelper {
public:
	bool m_bFirstRunOfFunctions : 1;
	bool m_bGameCodeMovedPlayer : 1;
	int m_nPlayerHandle; // edict index on server, client entity handle on client=
	int m_nImpulseCommand; // Impulse command issued.
	Vec3_t m_vecViewAngles; // Command view angles (local space)
	Vec3_t m_vecAbsViewAngles; // Command view angles (world space)
	int m_nButtons; // Attack buttons.
	int m_nOldButtons; // From host_client->oldbuttons;
	float m_flForwardMove;
	float m_flSideMove;
	float m_flUpMove;
	float m_flMaxSpeed;
	float m_flClientMaxSpeed;
	Vec3_t m_vecVelocity; // edict::velocity // Current movement direction.
	Vec3_t m_vecAngles; // edict::angles
	Vec3_t m_vecOldAngles;
	float m_outStepHeight; // how much you climbed this move
	Vec3_t m_outWishVel; // This is where you tried 
	Vec3_t m_outJumpVel; // This is your jump velocity
	Vec3_t m_vecConstraintCenter;
	float m_flConstraintRadius;
	float m_flConstraintWidth;
	float m_flConstraintSpeedFactor;
	float m_flUnknown[5];
	Vec3_t m_vecAbsOrigin;

	virtual	void _vpad() = 0;
	virtual void SetHost(IClientEntity* host) = 0;
};

class IPrediction
{
public:
	void SetupMove( IClientEntity *entity, CUserCmd *command, IMoveHelper *helper, CMoveData *data ) {
		using original_fn = void( __thiscall * )( void *, IClientEntity *, CUserCmd *, IMoveHelper *, CMoveData * );
		Utils::get_method<original_fn>( this, 20 )( this, entity, command, helper, data );
	}

	void FinishMove( IClientEntity *entity, CUserCmd *command, CMoveData *data ) {
		using original_fn = void( __thiscall * )( void *, IClientEntity *, CUserCmd *, CMoveData * );
		Utils::get_method<original_fn>( this, 21 )( this, entity, command, data );
	}
};