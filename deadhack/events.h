#pragma once

class Events {
private:
public:
	void init() {
		m_item_purchase = new ItemPurchaseEvent();
		m_item_purchase->RegisterSelf();

		m_player_hurt = new PlayerHurtEvent();
		m_player_hurt->RegisterSelf();

		m_bullet_impact = new BulletImpactEvent();
		m_bullet_impact->RegisterSelf();

		m_foot_step = new FootStepEvent();
		m_foot_step->RegisterSelf();

		m_inferno_start_burn = new InfernoStartBurnEvent();
		m_inferno_start_burn->RegisterSelf();

		m_round_end = new RoundEndEvent();
		m_round_end->RegisterSelf();
	}

	void remove() {
		m_item_purchase->UnregisterSelf();
		m_player_hurt->UnregisterSelf();
		m_bullet_impact->UnregisterSelf();
		m_foot_step->UnregisterSelf();
		m_inferno_start_burn->UnregisterSelf();
		m_round_end->UnregisterSelf();
	}

	class ItemPurchaseEvent : public IGameEventListener2 {
	public:
		void FireGameEvent( IGameEvent *event ) override;
		int  GetEventDebugID() override;

		void RegisterSelf();
		void UnregisterSelf();
	};

	class PlayerHurtEvent : public IGameEventListener2 {
	private:
	public:
		float m_hitmarker_alpha;

		void FireGameEvent( IGameEvent *event ) override;
		int  GetEventDebugID() override;

		void RegisterSelf();
		void UnregisterSelf();
	};

	class BulletImpactEvent : public IGameEventListener2 {
	public:
		void FireGameEvent( IGameEvent *event ) override;
		int  GetEventDebugID() override;

		void RegisterSelf();
		void UnregisterSelf();
	};

	class FootStepEvent: public IGameEventListener2 {
	public:
		void FireGameEvent( IGameEvent *event ) override;
		int  GetEventDebugID() override;

		void RegisterSelf();
		void UnregisterSelf();
	};
	
	class InfernoStartBurnEvent: public IGameEventListener2 {
	private:
		struct Inferno_t {
			float m_expiration;
			Vec3_t m_position;
			C_BaseEntity *m_ent;
		};
	public:
		std::vector< Inferno_t > m_inferno;

		void FireGameEvent( IGameEvent *event ) override;
		int  GetEventDebugID() override;

		void RegisterSelf();
		void UnregisterSelf();

		void draw();
	};

	class RoundEndEvent : public IGameEventListener2 {
	public:
		void FireGameEvent( IGameEvent *event ) override;
		int  GetEventDebugID() override;

		void RegisterSelf();
		void UnregisterSelf();
	};

	ItemPurchaseEvent        *m_item_purchase;
	PlayerHurtEvent          *m_player_hurt;
	BulletImpactEvent        *m_bullet_impact;
	FootStepEvent            *m_foot_step;
	InfernoStartBurnEvent    *m_inferno_start_burn;
	RoundEndEvent            *m_round_end;
};

extern Events g_events;
