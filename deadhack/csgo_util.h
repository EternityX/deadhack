#pragma once

namespace CSGO_Util {
	__forceinline void push_notification( Color color, const char *text ) {	
		auto AddToNotify = ( void(__stdcall *)( const Color &, char const * ) )g_offsets.m_PushNotification;
		AddToNotify( color, text );
	}

	__forceinline void init_key_values( KeyValues *key_values, const char* key_name ) {
		using InitKeyValues_t = void(__thiscall *)( void *, const char * );
		static InitKeyValues_t InitKeyValuesEx = nullptr;

		if( !InitKeyValuesEx )
			InitKeyValuesEx = (InitKeyValues_t)( g_offsets.m_InitKeyValues + *(ulong_t *)( g_offsets.m_InitKeyValues + 1 ) + 5 );

		InitKeyValuesEx( key_values, key_name );
	}

	__forceinline void load_from_buffer( KeyValues *key_values, const char *resource_name, const char *buf, void *file_sys = nullptr, const char *path_id = nullptr, void *eval_sym_proc = nullptr ) {		
		using LoadFromBuffer_t = void(__thiscall *)( void *, const char *, const char *, void *, const char *, void * );
		static LoadFromBuffer_t LoadFromBufferEx = nullptr;

		if( !LoadFromBufferEx )
			LoadFromBufferEx = (LoadFromBuffer_t)g_offsets.m_LoadFromBuffer;

		LoadFromBufferEx( key_values, resource_name, buf, file_sys, path_id, eval_sym_proc);
	}

	__forceinline IMaterial *create_material( bool shade, bool wireframe, bool ignorez, int rimlight_boost = 0 ) {
		static const std::string material_name = "game_material.vmt";
		const std::string material_type = shade ? "VertexLitGeneric" : "UnlitGeneric";

		std::string material_data;

		material_data += "\"" + material_type + "\"\n{\n";
		material_data += "\t\"$basetexture\" \"vgui/white_additive\"\n";
		material_data += "\t\"$envmap\" \"\"\n";
		material_data += "\t\"$model\" \"1\"\n";
		material_data += "\t\"$flat\" \"1\"\n";
		material_data += "\t\"$nocull\" \"0\"\n";
		material_data += "\t\"$selfillum\" \"1\"\n";
		material_data += "\t\"$halflambert\" \"1\"\n";
		material_data += "\t\"$znearer\" \"0\"\n";
		material_data += "\t\"$rimlightboost\" \"" + std::to_string( rimlight_boost ) + "\"\n";
		material_data += "\t\"$rimlightexponent\" \"" + std::to_string( 4 ) + "\"\n";
		material_data += "\t\"$ambientreflectionboost\" \"0.2\"\n";
		material_data += "\t\"$envmaplightscale\" \"" + std::to_string( 0.1 ) + "\"\n";
		material_data += "\t\"$wireframe\" \"" + std::to_string( wireframe ) + "\"\n";
		material_data += "\t\"$ignorez\" \"" + std::to_string( ignorez ) + "\"\n";
		material_data += "}\n";

		//const std::string material_data = "\"" + material_type + "\"\n{\n\t\"$basetexture\" \"vgui/white_additive\"\n\t\"$envmap\"  \"\"\n\t\"$model\" \"1\"\n\t\"$flat\" \"1\"\n\t\"$nocull\"  \"0\"\n\t\"$selfillum\" \"1\"\n\t\"$halflambert\" \"1\"\n\t\"$nofog\"  \"0\"\n\t\"$znearer\" \"0\"\n\t\"$wireframe\" \"" + std::to_string( wireframe ) + "\"\n\t\"$ignorez\" \"" + std::to_string( ignorez ) + "\"\n\t\"rimlightboost\" \"" + std::to_string( rimlight_boost ) + "\"\n}\n";

		KeyValues *key_values = new KeyValues();
		init_key_values( key_values, material_type.c_str() );
		load_from_buffer( key_values, material_name.c_str(), material_data.c_str() );

		return g_csgo.m_material_system->CreateMaterial( material_name.c_str(), key_values );
	}

	__forceinline IMaterial *create_rim_mat( bool shade, bool wireframe, bool ignorez ) {
		static const std::string material_name = "game_material.vmt";
		const std::string material_type = shade ? "VertexLitGeneric" : "UnlitGeneric";

		std::string material_data;

		material_data += "\"" + material_type + "\"\n{\n";
		material_data += "\t\"$additive\" \"1\"\n";
		material_data += "\t\"$envmap\" \"models/effects/crystal_cube_vertigo_hdr\"\n";
		material_data += "\t\"$envmapfresnel\" \"1\"\n";
		material_data += "\t\"$envmapfresnelminmaxexp\" \"[0 255 18]\"\n";
		material_data += "\t\"$alpha\" \"0.8\"\n";
		material_data += "\t\"$wireframe\" \"" + std::to_string( wireframe ) + "\"\n";
		material_data += "\t\"$ignorez\" \"" + std::to_string( ignorez ) + "\"\n";
		material_data += "}\n";

		//const std::string material_data = "\"" + material_type + "\"\n{\n\t\"$basetexture\" \"vgui/white_additive\"\n\t\"$envmap\"  \"\"\n\t\"$model\" \"1\"\n\t\"$flat\" \"1\"\n\t\"$nocull\"  \"0\"\n\t\"$selfillum\" \"1\"\n\t\"$halflambert\" \"1\"\n\t\"$nofog\"  \"0\"\n\t\"$znearer\" \"0\"\n\t\"$wireframe\" \"" + std::to_string( wireframe ) + "\"\n\t\"$ignorez\" \"" + std::to_string( ignorez ) + "\"\n\t\"rimlightboost\" \"" + std::to_string( rimlight_boost ) + "\"\n}\n";

		KeyValues *key_values = new KeyValues();
		init_key_values( key_values, material_type.c_str() );
		load_from_buffer( key_values, material_name.c_str(), material_data.c_str() );

		return g_csgo.m_material_system->CreateMaterial( material_name.c_str(), key_values );
	}

	__forceinline std::vector< IMaterial * > find_materials( char *texture_group_name ) {
		std::vector< IMaterial * > materials;
		for ( int i = g_csgo.m_material_system->FirstMaterial(); i != g_csgo.m_material_system->InvalidMaterial(); i = g_csgo.m_material_system->NextMaterial( i ) ) {
			IMaterial* material = g_csgo.m_material_system->FindMaterial( i );

			if( !material )
				continue;

			if( std::strstr( material->GetTextureGroupName(), texture_group_name ) )
				materials.push_back( material );
		}

		return materials;
	}

	__forceinline void change_sky( std::string sky_name ) {	
		auto LoadNamedSky = ( void(__fastcall *)( const char * ) )g_offsets.m_LoadNamedSky;
		LoadNamedSky( sky_name.c_str() );
	}

	__forceinline int predict_tickbase( CUserCmd *cmd ) {
		static int g_tick = 0;
		static CUserCmd* g_pLastCmd = nullptr;
		if(!g_pLastCmd || g_pLastCmd->m_hasbeenpredicted) {
			g_tick = g_cl.m_local->get_tickbase();
		}
		else {
			// required because prediction only runs on frames, not ticks
			// so if your framerate goes below tickrate, m_nTickBase won't update every tick.
			++g_tick;
		}
		g_pLastCmd = cmd;
		float curtime = g_tick * g_csgo.m_global_vars->m_interval_per_tick;
		return curtime;
	}

	__forceinline void set_clan_tag( std::string tag ) {
		using SendClanTag_t = void(__fastcall *)( const char *, const char * );
		static SendClanTag_t SendClanTag = nullptr;

		if( !SendClanTag )
			SendClanTag = (SendClanTag_t)g_offsets.m_SetClanTag;

		SendClanTag( tag.c_str(), tag.c_str() );
	}

	__forceinline bool line_goes_thru_smoke( const Vec3_t &start, const Vec3_t &end ) {
		using LineGoesThruSmoke_t = bool( *)( Vec3_t, Vec3_t, int16_t );
		static LineGoesThruSmoke_t LineGoesThruSmoke = nullptr;

		if( !LineGoesThruSmoke )
			LineGoesThruSmoke = (LineGoesThruSmoke_t)g_offsets.m_LineGoesThruSmoke;

		return LineGoesThruSmoke( start, end, 1 );
	}

	__forceinline float distance_to_rays( const Vec3_t &pos, const Vec3_t &ray_start, const Vec3_t &ray_end, float *along = nullptr, Vec3_t *pont_on_ray = nullptr ) {
		Vec3_t to = pos - ray_start;
		Vec3_t dir = ray_end - ray_start;

		float length = dir.normalize_in_place();

		float range_along = Math::dot_product( dir, to );
		if( along )
			*along = range_along;

		float range;

		if( range_along < 0.f ) {
			// off start point
			range = -( pos - ray_start ).length();

			if( pont_on_ray )
				*pont_on_ray = ray_start;
		}
		else if( range_along > length ) {
			// off end point
			range = -( pos - ray_end ).length();

			if( pont_on_ray ) {
				*pont_on_ray = ray_end;
			}
		}
		else  {
			// within ray bounds
			Vec3_t onRay = ray_start + dir.operator*( range_along );
			range = ( pos - onRay ).length();

			if( pont_on_ray )
				*pont_on_ray = onRay;
		}

		return range;
	}

	__forceinline void clip_trace_to_player( const Vec3_t &start, const Vec3_t &end, uint32_t mask, ITraceFilter *filter, CGameTrace *tr ) {
		using UtilClipTraceToPlayer_t = void( *)( const Vec3_t &, const Vec3_t &, uint32_t, ITraceFilter *, CGameTrace * );
		static UtilClipTraceToPlayer_t ClipTraceToPlayers = nullptr;

		if( !ClipTraceToPlayers )
			ClipTraceToPlayers = (UtilClipTraceToPlayer_t)g_offsets.m_UTILClipTraceToPlayers;

		if( ClipTraceToPlayers ) {
			__asm {
				mov eax, filter
				lea ecx, tr
				push ecx
				push eax
				push mask
				lea edx, end
				lea ecx, start
				call ClipTraceToPlayers
				add esp, 0xC
			}
		}
	}

	// https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/game/shared/util_shared.cpp#L687
	/*__forceinline void clip_trace_to_player( Vec3_t &start, Vec3_t &end, unsigned int mask, ITraceFilter *filter, CGameTrace *tr ) {
		Ray_t ray;
		ray.init(start, end);

		for( int i = 1; i <= g_csgo.m_global_vars->m_max_clients; i++ ) {
			C_BaseEntity *player = (C_BaseEntity *)g_csgo.m_entity_list->GetClientEntity( i );

			if( !player || !player->IsDormant() )
				continue;

			if( filter && filter->ShouldHitEntity( player, mask ) == false )
				continue;

			float range = distance_to_rays( player->get_world_space_center(), start, end );
			if( range < 0.0f || range > 60.f )
				continue;

			float smallest_fraction = tr->fraction;

			CGameTrace trace;
			g_csgo.m_engine_trace->ClipRayToEntity( ray, mask | CONTENTS_HITBOX, player, &trace );
			if( trace.fraction < smallest_fraction ) {
				// we shortened the ray - save off the trace
				*tr = trace;

				smallest_fraction = trace.fraction;
			}
		}
	}*/
}