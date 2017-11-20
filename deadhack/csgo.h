#pragma once

class CSGO : protected Interfaces {
private:

public:
    CSGO() {
    
    }

    bool init() {
        
        return true;
    }
};

extern CSGO g_csgo;