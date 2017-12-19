#pragma once

class CUserCmd {
public:
	virtual ~CUserCmd() {}
	
	// for matching server and client commands for debugging.
	int		command_number;
	// the tick the client created this command.
	int		tick_count;

	// player instantaneous view angles.
	Ang_t	viewangles;

	//	forward velocity.
	float	forwardmove;
	//  sideways velocity.
	float	sidemove;
	//  upward velocity.
	float	upmove;

	// attack button states.
	int		buttons;

	// impulse command issued.
	byte    impulse;

	// current weapon id
	int		weaponselect;
	int		weaponsubtype;

	// for shared random functions.
	int		random_seed;

	// mouse accum in x from create move.
	short	mousedx;
	// mouse accum in y from create move.
	short	mousedy;

	// client only, tracks whether we've predicted this command at least once.
	bool	hasbeenpredicted;
};