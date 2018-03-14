#pragma once

class CMoveData {
public:
	bool    m_bFirstRunOfFunctions : 1;
	bool    m_bGameCodeMovedPlayer : 1;
	int     m_nPlayerHandle;        // edict index on server, client entity handle on client=
	int     m_nImpulseCommand;      // Impulse command issued.
	Vec3_t  m_vecViewAngles;        // Command view angles (local space)
	Vec3_t  m_vecAbsViewAngles;     // Command view angles (world space)
	int     m_nButtons;             // Attack buttons.
	int     m_nOldButtons;          // From host_client->oldbuttons;
	float   m_flForwardMove;
	float   m_flSideMove;
	float   m_flUpMove;
	float   m_flMaxSpeed;
	float   m_flClientMaxSpeed;
	Vec3_t  m_vecVelocity;          // edict::velocity        // Current movement direction.
	Vec3_t  m_vecAngles;            // edict::angles
	Vec3_t  m_vecOldAngles;
	float   m_outStepHeight;        // how much you climbed this move
	Vec3_t  m_outWishVel;           // This is where you tried 
	Vec3_t  m_outJumpVel;           // This is your jump velocity
	Vec3_t  m_vecConstraintCenter;
	float   m_flConstraintRadius;
	float   m_flConstraintWidth;
	float   m_flConstraintSpeedFactor;
	float   m_flUnknown[5];
	Vec3_t  m_vecAbsOrigin;
};

class IGameMovement {
public:
	virtual			~IGameMovement(void) {}

	virtual void	          ProcessMovement(C_BaseEntity *pPlayer, CMoveData *pMove) = 0;
	virtual void	          Reset(void) = 0;
	virtual void	          StartTrackPredictionErrors(C_BaseEntity *pPlayer) = 0;
	virtual void	          FinishTrackPredictionErrors(C_BaseEntity *pPlayer) = 0;
	virtual void	          DiffPrint(char const *fmt, ...) = 0;
	virtual Vec3_t const&	  GetPlayerMins(bool ducked) const = 0;
	virtual Vec3_t const&	  GetPlayerMaxs(bool ducked) const = 0;
	virtual Vec3_t const&   GetPlayerViewOffset(bool ducked) const = 0;
	virtual bool		        IsMovingPlayerStuck(void) const = 0;
	virtual C_BaseEntity*   GetMovingPlayer(void) const = 0;
	virtual void		        UnblockPusher(C_BaseEntity *pPlayer, C_BaseEntity *pPusher) = 0;
	virtual void            SetupMovementBounds(CMoveData *pMove) = 0;
};