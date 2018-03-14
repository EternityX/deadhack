#pragma once

/*
Developed by sk0r / Czybik

Features:
- CVars (types: bool, int, float, double and string)
- Commands (with event function or event class)
- Commandline handler
- Script expression
- Any amount of spaces/tabs between each argument
- Separate arguments via quotes and/or brackets(nested)
- Separate item expressions via delimiter
- Use comments
- Config interface
- Basic script expressions

Script examples:
- expression value1 value2 value3
- expression "value1 value2" "value3" # This is a comment
- expression "argument 1" [argument 2]
- expression     "this is"      [a]       "test" # :-)
- expression "arg1"; expression arg2; expression arg3
- expression "arg1" [ expression2 "arg1" "arg2"; expression3 [expression4 "arg1" [ arg2 ]; ]; ]
Commandline examples:
- +cl_variable1 1 +cl_variable2 2
- -argument1 -argument2 "value" -argument3 1 2 3
- +cl_variable 1 -argument
Basic script commands:
- alias <name> <expression> -> Adds a new alias to list or overwrites an existing alias
- delalias <name> -> Deletes a specified alias
- clearaliases -> Clears list of aliases
- alexec <name> -> Handles the expression of a specified alias
- exec <script> -> Executes a specified script file
*/

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string.h>

#pragma warning(disable : 4355)

#define CM_CVAR_MAX_STRING_LEN 256
#define CM_DIR_CHAR '/'

namespace config_manager {
	class CVar {
	public:
		CVar() { }

		~CVar() {
			this->Release( );
		}

		enum cvar_type_e {
			CVAR_TYPE_BOOL,
			CVAR_TYPE_INT,
			CVAR_TYPE_FLOAT,
			CVAR_TYPE_DOUBLE,
			CVAR_TYPE_STRING
		};

		struct cvar_s {
			std::string identifier;
			cvar_type_e type;

			union {
				bool bValue;
				int iValue;
				float flValue;
				double dbValue;
				char szValue[ CM_CVAR_MAX_STRING_LEN ];
			};
		};

		cvar_s *Add( const std::string &identifier, const cvar_type_e type, const std::string &initialValue ) {
			if( !identifier.length( ) )
				return nullptr;

			if( Find( identifier ) )
				return nullptr;

			cvar_s *cvar = new cvar_s;
			if( !cvar )
				return nullptr;

			cvar->identifier = identifier;
			cvar->type = type;

			if( initialValue.length( ) ) {
				switch( type ) {
				case CVAR_TYPE_BOOL:
					cvar->bValue = atoi( initialValue.c_str( ) ) != 0;
					break;
				case CVAR_TYPE_INT:
					cvar->iValue = atoi( initialValue.c_str( ) );
					break;
				case CVAR_TYPE_FLOAT:
					cvar->flValue = static_cast< float >(atof( initialValue.c_str( ) ));
					break;
				case CVAR_TYPE_DOUBLE:
					cvar->dbValue = atof( initialValue.c_str( ) );
					break;
				case CVAR_TYPE_STRING:
					strcpy_s( cvar->szValue, initialValue.c_str( ) );
					break;
				default:
					break;
				}
			}

			cvars_.emplace_back( cvar );

			return cvar;
		}

		cvar_s *Find( const std::string &identifier ) {
			if( !identifier.length( ) )
				return nullptr;

			for( size_t i = 0; i < cvars_.size( ); ++i )
				if( cvars_.at( i ) && cvars_.at( i )->identifier == identifier )
					return cvars_.at( i );

			return nullptr;
		}

		bool Set( const std::string &identifier, const bool value ) {
			cvar_s *cvar = Find( identifier );
			if( !cvar )
				return false;

			cvar->bValue = value;

			return true;
		}

		bool Set( const std::string &identifier, const int value ) {
			cvar_s *cvar = Find( identifier );
			if( !cvar )
				return false;

			cvar->iValue = value;

			return true;
		}

		bool Set( const std::string &identifier, const float value ) {
			cvar_s *cvar = Find( identifier );
			if( !cvar )
				return false;

			cvar->flValue = value;

			return true;
		}

		bool Set( const std::string &identifier, const double value ) {
			cvar_s *cvar = Find( identifier );
			if( !cvar )
				return false;

			cvar->dbValue = value;

			return true;
		}

		bool Set( const std::string &identifier, const std::string &value ) {
			cvar_s *cvar = Find( identifier );
			if( !cvar )
				return false;

			strcpy_s( cvar->szValue, value.c_str( ) );

			return true;
		}

		bool SetCast( const std::string &identifier, const std::string &value ) {
			cvar_s *cvar = Find( identifier );
			if( !cvar )
				return false;

			switch( cvar->type ) {
			case CVAR_TYPE_BOOL:
				cvar->bValue = atoi( value.c_str( ) ) != 0;
				break;
			case CVAR_TYPE_INT:
				cvar->iValue = atoi( value.c_str( ) );
				break;
			case CVAR_TYPE_FLOAT:
				cvar->flValue = static_cast< float >(atof( value.c_str( ) ));
				break;
			case CVAR_TYPE_DOUBLE:
				cvar->dbValue = atof( value.c_str( ) );
				break;
			case CVAR_TYPE_STRING:
				strcpy_s( cvar->szValue, value.c_str( ) );
				break;
			default:
				return false;
			}

			return true;
		}

		bool Delete( const std::string &identifier ) {
			cvar_s *cvar = Find( identifier );
			if( !cvar )
				return false;

			return Delete( cvar );
		}

		bool Delete( const cvar_s *cvar ) const {
			return Delete( cvar );
		}

		std::vector< cvar_s * > cvars_;

	private:
		void Release() {
			for( size_t i = 0; i < cvars_.size( ); ++i )
				delete cvars_.at( i );

			cvars_.clear( );
		}

		size_t Find( const cvar_s *cvar ) {
			if( !cvar )
				return std::string::npos;

			for( size_t i = 0; i < cvars_.size( ); ++i )
				if( cvars_.at( i ) == cvar )
					return i;

			return std::string::npos;
		}

		bool Delete( const size_t id ) {
			if( id >= cvars_.size( ) )
				return false;

			delete cvars_.at( id );

			cvars_.erase( cvars_.begin( ) + id );

			return true;
		}
	};

	class Command {
#define CM_DEFINE_CMDF( n ) void Cmd_##n( )
#define CM_DEFINE_CMDC( n, c ) struct Cmd##n : public config_manager::Command::CmdCallback { virtual void CommandCallback( ) { c } }; Cmd##n oCmd##n;
#define CM_ADD_CMDF( o, n ) ( o.Command::Add( #n, &Cmd_##n, config_manager::Command::CMDCBT_FUNCTION ) )
#define CM_ADD_CMDC( o, n ) ( o.Command::Add( #n, &oCmd##n, config_manager::Command::CMDCBT_CLASS ) )

	public:
		Command() { }

		~Command() {
			cmds_.clear( );
		}

		enum cmd_callbacktype_e {
			CMDCBT_FUNCTION,
			CMDCBT_CLASS
		};

		struct CmdCallback {
			virtual ~CmdCallback() = default;
			virtual void CommandCallback() = 0;
		};

		using CommandCallback = void( *)();

		bool Add( const std::string &identifier, const void *object, cmd_callbacktype_e callbackType ) {
			if( !identifier.length( ) || !object )
				return false;

			if( Find( identifier, nullptr ) )
				return false;

			command_s data;
			data.identifier = identifier;
			data.callbackObject = object;
			data.callbackType = callbackType;

			cmds_.emplace_back( data );

			return true;
		}

		bool Handle( const std::string &identifier ) {
			size_t id;

			if( !Find( identifier, &id ) )
				return false;

			if( !cmds_.at( id ).callbackObject )
				return false;

			switch( cmds_.at( id ).callbackType ) {
			case CMDCBT_FUNCTION: {
				CommandCallback callbackFn = (CommandCallback)cmds_.at( id ).callbackObject;
				callbackFn( );
				break;
			}
			case CMDCBT_CLASS: {
				CmdCallback *callbackInt = (CmdCallback *)cmds_.at( id ).callbackObject;
				callbackInt->CommandCallback( );
				break;
			}
			default:
				return false;
			}

			return true;
		}

		bool Delete( const std::string &identifier ) {
			size_t id;

			if( !Find( identifier, &id ) )
				return false;

			cmds_.erase( cmds_.begin( ) + id );

			return true;
		}

	private:
		struct command_s {
			std::string identifier;
			const void *callbackObject;
			cmd_callbacktype_e callbackType;
		};

		std::vector< command_s > cmds_;

	protected:
		bool Find( const std::string &identifier, size_t *entryId ) {
			for( size_t i = 0; i < cmds_.size( ); ++i ) {
				if( cmds_.at( i ).identifier == identifier ) {
					if( entryId )
						*entryId = i;

					return true;
				}
			}

			return false;
		}
	};

	class CmdLine : public CVar {
		static const char C_CVAR_CHAR = '+';
		static const char C_ARG_CHAR = '-';

	public:
		struct cmd_arg_s {
			std::string identifier;
			std::vector< std::string > args;
		};

		CmdLine() : args_( nullptr ), count_( 0 ) { }

		CmdLine( char **args, const int &argCount ) : args_( args ), count_( argCount ) {
			Collect( );
		}

		~CmdLine() {
			this->Release( );
		}

		void SetCmdArgs( char **args, const int &argCount ) {
			args_ = args;
			count_ = argCount;
		}

		bool Collect() {
			if( !args_ || !count_ )
				return false;

			if( count_ == 1 )
				return true;

			for( int i = 1; i < count_; ++i ) {
				if( !args_[ i ] )
					return false;

				if( args_[ i ][ 0 ] == C_CVAR_CHAR ) {
					if( i + 1 >= count_ )
						return false;

					const char *cvarValue = args_[ i + 1 ];
					if( !cvarValue )
						return false;

					SetCast( std::string( &args_[ i ][ 1 ] ), std::string( cvarValue ) );

					i++;

				}
				if( args_[ i ][ 0 ] == C_ARG_CHAR ) {
					int ignoreCount = HandleArg( std::string( &args_[ i ][ 1 ] ), i + 1 );
					if( ignoreCount == -1 )
						return false;

					i += ignoreCount;

					continue;
				}
				return false;
			}

			return true;
		}

		size_t Count() const {
			return cmdArgs_.size( );
		}

		cmd_arg_s *Item( const size_t &id ) {
			if( id >= cmdArgs_.size( ) )
				return nullptr;

			return cmdArgs_.at( id );
		}

	private:
		int HandleArg( const std::string &identifier, int argStart ) {
			int ignoreCount = 0;

			cmd_arg_s *arg = new cmd_arg_s;
			if( !arg )
				return -1;

			arg->identifier = identifier;

			for( auto i = argStart; i < count_; ++i ) {
				if( args_[ i ][ 0 ] == C_CVAR_CHAR || args_[ i ][ 0 ] == C_ARG_CHAR )
					break;

				arg->args.push_back( std::string( args_[ i ] ) );

				ignoreCount++;
			}

			cmdArgs_.push_back( arg );

			return ignoreCount;
		}

		void Release() {
			for( size_t i = 0; i < cmdArgs_.size( ); ++i )
				delete cmdArgs_.at( i );

			cmdArgs_.clear( );
		}

		std::vector< cmd_arg_s* > cmdArgs_;
		char **args_;
		int count_;
	};

	class ScriptParser : public CmdLine, public Command {
		static const char C_SPACE_CHAR = ' ';
		static const char C_TAB_CHAR = '\t';
		static const char C_QUOTE_CHAR = '\"';
		static const char C_BRACKET_START_CHAR = '[';
		static const char C_BRACKET_END_CHAR = ']';
		static const char C_COMMENT_CHAR = '#';
		static const char C_ITEMS_DELIM = ';';

	public:
		ScriptParser() : UnknownExpressionInformFn( nullptr ) { }
		ScriptParser( const CommandCallback function ) : UnknownExpressionInformFn( function ) { }

		ScriptParser( const CommandCallback function, const std::string &expression ) : UnknownExpressionInformFn( function ) {
			Parse( expression );
		}

		~ScriptParser() {
			expressionItems_.clear( );
		}

		bool SetUnknownExpressionInformer( const CommandCallback callbackFn ) {
			if( !callbackFn )
				return false;

			UnknownExpressionInformFn = callbackFn;

			return true;
		}

		bool Parse( const std::string &expression ) {
			if( !expression.length( ) )
				return false;

			bool isInQuotes = false;
			bool hasNonSpaceChar = false;

			short bracketCounter = 0;

			std::string tempString( "" );

			expressionItems_.clear( );

			for( size_t i = 0; i <= expression.length( ); ++i ) {
				if( !tempString.length( ) && ( expression[ i ] == C_SPACE_CHAR || expression[ i ] == C_TAB_CHAR ) )
					continue;

				if( expression[ i ] == C_QUOTE_CHAR ) {
					isInQuotes = !isInQuotes;

					if( !bracketCounter )
						continue;
				}

				if( !hasNonSpaceChar && ( expression[ i ] != C_SPACE_CHAR || expression[ i ] != C_TAB_CHAR ) )
					hasNonSpaceChar = true;

				if( !hasNonSpaceChar )
					continue;

				if( !isInQuotes ) {
					if( ( expression[ i ] == C_SPACE_CHAR || expression[ i ] == C_TAB_CHAR ) && ( expression[ i + 1 ] == C_SPACE_CHAR || expression[ i + 1 ] == C_TAB_CHAR ) )
						continue;

					if( expression[ i ] == C_BRACKET_START_CHAR ) {
						bracketCounter++;

						if( bracketCounter == 1 )
							continue;
					}
					else if( expression[ i ] == C_BRACKET_END_CHAR ) {
						bracketCounter--;

						if( bracketCounter == 0 )
							continue;
					}

					if( !bracketCounter && ( expression[ i ] == C_SPACE_CHAR || expression[ i ] == C_TAB_CHAR || expression[ i ] == C_BRACKET_END_CHAR || expression[ i ] == C_COMMENT_CHAR || expression[ i ] == C_ITEMS_DELIM || !expression[ i ] ) ) {
						if( !expressionItems_.size( ) && ( i > 0 && !tempString.length( ) ) ) {
							tempString.clear( );
							continue;
						}

						expressionItems_.emplace_back( tempString );

						if( expression[ i ] == C_COMMENT_CHAR )
							break;

						tempString.clear( );

						if( expression[ i ] == C_ITEMS_DELIM ) {
							HandleCurrentItem( true );
							hasNonSpaceChar = false;
						}

						continue;
					}
				}

				tempString += expression[ i ];
			}

			HandleCurrentItem( );

			return true;
		}

		size_t ExpressionItemCount() const {
			return expressionItems_.size( );
		}

		std::string ExpressionItemValue( const size_t &id ) {
			std::string result( "" );

			if( id < expressionItems_.size( ) )
				result = expressionItems_[ id ];

			return result;
		}

		void HandleCurrentItem( bool shouldClear = false ) {
			if( expressionItems_.size( ) ) {
				if( expressionItems_.size( ) > 1 && SetCast( expressionItems_[ 0 ], expressionItems_[ 1 ] ) ) {
					if( shouldClear )
						expressionItems_.clear( );

					return;
				}

				if( Handle( expressionItems_[ 0 ] ) ) {
					if( shouldClear )
						expressionItems_.clear( );

					return;
				}

				if( UnknownExpressionInformFn )
					UnknownExpressionInformFn( );

				if( shouldClear )
					expressionItems_.clear( );
			}
		}

		std::vector< std::string > expressionItems_;

		CommandCallback UnknownExpressionInformFn;
	};

	class ConfigInt : public ScriptParser {
	public:
		ConfigInt() : scriptDirectory_( "" ) { }
		ConfigInt( const std::string &scriptDirectory ) : scriptDirectory_( scriptDirectory ) { }

		ConfigInt( const std::string &scriptDirectory, const std::string script ) : scriptDirectory_( scriptDirectory ) {
			Execute( script );
		}

		~ConfigInt() { }

		void set_script_directory( const std::string &scriptDirectory ) {
			scriptDirectory_ = scriptDirectory;

			if( scriptDirectory_.at( scriptDirectory_.length( ) - 1 ) != CM_DIR_CHAR )
				scriptDirectory_ += CM_DIR_CHAR;
		}

		bool Execute( const std::string &scriptFile ) {
			std::ifstream file( scriptDirectory_ + scriptFile );
			if( file.is_open() ) {

				std::string currentLine( "" );

				while( !file.eof( ) ) {
					getline( file, currentLine, '\n' );

					if( !currentLine.length( ) )
						continue;

					Parse( currentLine );
				}

				file.close( );

				return true;
			}

			return false;
		}

		bool Save( const std::string &scriptFile, bool should_reset ) {
			std::ofstream file( scriptDirectory_ + scriptFile );
			if( file.is_open( ) ) {
				file.clear( );

				for( size_t i = 0; i < cvars_.size( ); ++i ) {
					std::string cmd;

					switch( cvars_.at( i )->type ) {
					case CVAR_TYPE_BOOL:
						cmd = cvars_.at( i )->identifier + " " + "\"" + std::to_string( should_reset ? false : cvars_.at( i )->bValue ) + "\"" + "\n";
						break;
					case CVAR_TYPE_INT:
						cmd = cvars_.at( i )->identifier + " " + "\"" + std::to_string( should_reset ? 0 : cvars_.at( i )->iValue ) + "\"" + "\n";
						break;
					case CVAR_TYPE_FLOAT:
						cmd = cvars_.at( i )->identifier + " " + "\"" + std::to_string( should_reset ? 0.000000f : cvars_.at( i )->flValue ) + "\"" + "\n";
						break;
					case CVAR_TYPE_DOUBLE:
						cmd = cvars_.at( i )->identifier + " " + "\"" + std::to_string( should_reset ? 0.0 : cvars_.at( i )->dbValue ) + "\"" + "\n";
						break;
					case CVAR_TYPE_STRING:
						cmd = cvars_.at( i )->identifier + " " + "\"" + ( should_reset ? "1.0,1.0,1.0" : cvars_.at( i )->szValue ) + "\"" + "\n";
						break;
					default:
						break;
					}

					if( !cmd.empty() )
						file << cmd;
				}

				file.close( );

				return true;
			}

			return false;
		}

	private:
		std::string scriptDirectory_;
	};

	class AliasManager {
	public:
		AliasManager() { }

		~AliasManager() {
			aliases_.clear( );
		}

		struct alias_s {
			std::string identifier;
			std::string expression;
		};

		alias_s *Find( const std::string &identifier, size_t *exitId = nullptr ) {
			for( size_t i = 0; i < aliases_.size( ); ++i ) {
				if( aliases_.at( i )->identifier == identifier ) {
					if( exitId )
						*exitId = i;

					return aliases_.at( i );
				}
			}

			return nullptr;
		}

		bool AddAlias( const std::string &identifier, const std::string &expression ) {
			if( !identifier.length( ) )
				return false;

			alias_s *alias = Find( identifier );
			if( alias ) {
				alias->expression = expression;

				return true;
			}

			alias_s *newAlias = new alias_s;
			if( !newAlias )
				return false;

			newAlias->identifier = identifier;
			newAlias->expression = expression;

			aliases_.emplace_back( newAlias );

			return true;
		}

		bool DelAlias( const std::string &identifier ) {
			size_t id;

			if( !Find( identifier, &id ) )
				return false;

			delete aliases_.at( id );

			aliases_.erase( aliases_.begin( ) + id );

			return true;
		}

		bool ClearAliases() {
			aliases_.clear( );

			return ( aliases_.size( ) == 0 );
		}

		std::vector< alias_s * > aliases_;
	};

	class CmdAlias : public Command::CmdCallback {
	public:
		CmdAlias() : configInt_( nullptr ), aliasManager_( nullptr ) { }
		CmdAlias( ConfigInt *configInt, AliasManager *aliasManager ) : configInt_( configInt ), aliasManager_( aliasManager ) { }

		void CommandCallback() override {
			if( configInt_ && aliasManager_ ) {
				std::string aliasName = configInt_->ExpressionItemValue( 1 );
				if( aliasName.length( ) )
					aliasManager_->AddAlias( aliasName, configInt_->ExpressionItemValue( 2 ) );
			}
		}

	private:
		ConfigInt *configInt_;
		AliasManager *aliasManager_;
	};

	class CmdDelAlias : public Command::CmdCallback {
	public:
		CmdDelAlias() : configInt_( nullptr ), aliasManager_( nullptr ) { }
		CmdDelAlias( ConfigInt *configInt, AliasManager *aliasManager ) : configInt_( configInt ), aliasManager_( aliasManager ) { }

		void CommandCallback() override {
			if( configInt_ && aliasManager_ ) {
				std::string aliasName = configInt_->ExpressionItemValue( 1 );
				if( aliasName.length( ) )
					aliasManager_->DelAlias( aliasName );
			}
		}

	private:
		ConfigInt *configInt_;
		AliasManager *aliasManager_;
	};

	class CmdClearAliases : public Command::CmdCallback {
	public:
		CmdClearAliases() : configInt_( nullptr ), aliasManager_( nullptr ) { }
		CmdClearAliases( ConfigInt *configInt, AliasManager *aliasManager ) : configInt_( configInt ), aliasManager_( aliasManager ) { }

		void CommandCallback() override {
			if( configInt_ && aliasManager_ ) {
				aliasManager_->ClearAliases( );
			}
		}

	private:
		ConfigInt *configInt_;
		AliasManager *aliasManager_;
	};

	class CmdAlExec : public Command::CmdCallback {
	public:
		CmdAlExec() : configInt_( nullptr ), aliasManager_( nullptr ) { }
		CmdAlExec( ConfigInt *configInt, AliasManager *aliasManager ) : configInt_( configInt ), aliasManager_( aliasManager ) { }

		void CommandCallback() override {
			if( configInt_ && aliasManager_ ) {
				std::string aliasName = configInt_->ExpressionItemValue( 1 );
				if( aliasName.length( ) ) {
					AliasManager::alias_s *alias = aliasManager_->Find( aliasName );
					if( alias )
						configInt_->Parse( alias->expression );
				}
			}
		}

	private:
		ConfigInt *configInt_;
		AliasManager *aliasManager_;
	};

	class CmdExec : public Command::CmdCallback {
	public:
		CmdExec() : configInt_( nullptr ) { }
		CmdExec( ConfigInt *configInt ) : configInt_( configInt ) { }

		void CommandCallback() override {
			if( configInt_ )
				configInt_->Execute( configInt_->ExpressionItemValue( 1 ) );
		}

	private:
		ConfigInt *configInt_;
	};

	class BaseScripting : public ConfigInt {
	public:
		BaseScripting()
			: cmdAlias_( this, &aliasManager_ ), cmdDelAlias_( this, &aliasManager_ ), cmdClearAliases_( this, &aliasManager_ ), alExec_( this, &aliasManager_ ), cmdExec_( this ), isInitialized_( false ) {
			this->Initialize( );
		}

		~BaseScripting() {
			this->Release( );
		}

		static BaseScripting &BaseScripting::get_instance() {
			static std::unique_ptr< BaseScripting > instance;
			static std::once_flag once_flag;

			std::call_once( once_flag,
			                [ ] {
			                instance.reset( new BaseScripting );
		                } );

			return *instance.get( );
		}

		bool is_ready() const {
			return isInitialized_;
		}

	private:
		bool Initialize() {
			if( isInitialized_ ) {
				return false;
			}

			if( !Command::Add( "alias", &cmdAlias_, CMDCBT_CLASS ) )
				return false;
			if( !Command::Add( "delalias", &cmdDelAlias_, CMDCBT_CLASS ) )
				return false;
			if( !Command::Add( "clearaliases", &cmdClearAliases_, CMDCBT_CLASS ) )
				return false;
			if( !Command::Add( "alexec", &alExec_, CMDCBT_CLASS ) )
				return false;
			if( !Command::Add( "exec", &cmdExec_, CMDCBT_CLASS ) )
				return false;

			return isInitialized_ = true;
		}

		bool Release() {
			if( !isInitialized_ ) {
				return false;
			}

			if( !Command::Delete( "alias" ) )
				return false;
			if( !Command::Delete( "delalias" ) )
				return false;
			if( !Command::Delete( "clearaliases" ) )
				return false;
			if( !Command::Delete( "alexec" ) )
				return false;
			if( !Command::Delete( "exec" ) )
				return false;

			isInitialized_ = false;

			return true;
		}

		AliasManager aliasManager_;

		CmdAlias cmdAlias_;
		CmdDelAlias cmdDelAlias_;
		CmdClearAliases cmdClearAliases_;
		CmdAlExec alExec_;
		CmdExec cmdExec_;

		bool isInitialized_;
	};
}

extern config_manager::BaseScripting cfg_manager;
