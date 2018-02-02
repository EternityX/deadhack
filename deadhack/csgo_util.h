#pragma once

namespace CSGO_Util {
	__forceinline void push_notification( Color color, const char *text ) {	
		auto AddToNotify = ( void(__stdcall *)( const Color &, char const * ) )g_offsets.m_PushNotification;
		AddToNotify( color, text );
	}

	__forceinline void init_key_values( KeyValues *key_values, const char* key_name ) {
		using InitKeyValues_t = void(__thiscall *)( void *, const char * );
		static InitKeyValues_t InitKeyValuesEx = nullptr;

		if ( !InitKeyValuesEx )
			InitKeyValuesEx = (InitKeyValues_t)( g_offsets.m_InitKeyValues + *(ulong_t *)( g_offsets.m_InitKeyValues + 1 ) + 5 );

		InitKeyValuesEx( key_values, key_name );
	}

	__forceinline void load_from_buffer( KeyValues *key_values, const char *resource_name, const char *buf, void *file_sys = nullptr, const char *path_id = nullptr, void *eval_sym_proc = nullptr ) {		
		using LoadFromBuffer_t = void(__thiscall *)( void *, const char *, const char *, void *, const char *, void * );
		static LoadFromBuffer_t LoadFromBufferEx = nullptr;

		if (!LoadFromBufferEx)
			LoadFromBufferEx = (LoadFromBuffer_t)g_offsets.m_LoadFromBuffer;

		LoadFromBufferEx( key_values, resource_name, buf, file_sys, path_id, eval_sym_proc);
	}

	__forceinline IMaterial *create_material( bool shade, bool wireframe, bool ignorez, int rimlight_boost = 0 ) {
		static const std::string material_name = "game_material.vmt";
		const std::string material_type = shade ? "VertexLitGeneric" : "UnlitGeneric";

		std::string material_data;

		material_data += "\"" + material_type + "\"\n{\n";
		material_data += "\t\"$basetexture\" \"vgui/white_additive\"\n";
		material_data += "\t\"$envmap\" \"env_cubemap\"\n";
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

	__forceinline std::vector< IMaterial * > find_materials( char *texture_group_name ) {
		std::vector< IMaterial * > materials;
		for ( int i = g_csgo.m_material_system->FirstMaterial(); i != g_csgo.m_material_system->InvalidMaterial(); i = g_csgo.m_material_system->NextMaterial( i ) ) {
			IMaterial* material = g_csgo.m_material_system->FindMaterial( i );

			if ( !material )
				continue;

			if ( std::strstr( material->GetTextureGroupName(), texture_group_name ) )
				materials.push_back( material );
		}

		return materials;
	}

	__forceinline void change_sky( std::string sky_name ) {	
		auto LoadNamedSky = ( void(__fastcall *)( const char * ) )g_offsets.m_LoadNamedSky;
		LoadNamedSky( sky_name.c_str() );
	}
}