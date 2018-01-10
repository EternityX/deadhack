#pragma once

class NetVars {
private:
	struct NetvarData {
		bool        m_datamap_var; // we can't do proxies on stuff from datamaps :).
		RecvProp    *m_prop_ptr;
		size_t      m_offset;

		__forceinline NetvarData() : m_datamap_var{}, m_prop_ptr{}, m_offset{} { }
	};
	
	std::unordered_map< hash32_t, int > m_client_ids;

	// netvar container.
	std::unordered_map< hash32_t,     // hash key + tables
		std::unordered_map< hash32_t, // hash key + props
		NetvarData                    // prop offset / prop ptr
		> > m_offsets;

public:
	// ctor.
	NetVars() : m_offsets{} { }

	// dtor.
	~NetVars() {
		m_offsets.clear();
	}

	void init() {
		ClientClass *list;

		// sanity check on client.
		if( !g_csgo.m_client )
			return;

		// grab linked list.
		list = g_csgo.m_client->GetAllClasses();
		if( !list )
			return;

		// iterate list of netvars.
		for( ; list != nullptr; list = list->m_pNext )
			store_table( list->m_pRecvTable->m_pNetTableName, list->m_pRecvTable );

		// find all datamaps
		// store_datamaps();
	}

	void store_table( const std::string &name, RecvTable *table, size_t offset = 0 ) {
		hash32_t    var, base{ Hash::fnv1a_32( name ) };
		RecvProp*   prop;
		RecvTable*  child;

		// iterate props
		for( int i{}; i < table->m_nProps; ++i ) {
			prop = &table->m_pProps[ i ];
			child = prop->m_pDataTable;

			// we have a child table, that contains props.
			if( child && child->m_nProps > 0 )
				store_table( name, child, prop->m_Offset + offset );

			// hash var name.
			var = Hash::fnv1a_32( prop->m_pVarName );

			// insert if not present.
			if( !m_offsets[ base ][ var ].m_offset ) {
				m_offsets[ base ][ var ].m_datamap_var = false;
				m_offsets[ base ][ var ].m_prop_ptr    = prop;
				m_offsets[ base ][ var ].m_offset      = (size_t)( prop->m_Offset + offset );
			}
		}
	}

	// get client id.
	__forceinline int get_client_id( hash32_t network_name ) {
		return m_client_ids[ network_name ];
	}

	// get netvar offset.
	__forceinline int get( hash32_t table, hash32_t prop ) {
		return m_offsets[ table ][ prop ].m_offset;
	}
};

extern NetVars g_netvars;