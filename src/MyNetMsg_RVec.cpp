
#include "MyNetMsg_RVec.h"

#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr {
    
    NetMsgMacroDefinition( MyNetMsg_RVec );

    MyNetMsg_RVec::MyNetMsg_RVec() {
        randDev rd;
        MersenneTw gen = MersenneTw(rd());
        fdist rX = fdist(-100.0f,100.0f);
        fdist rY = fdist(-100.0f,100.0f);
        fdist rZ = fdist(   0.0f, 50.0f);
        vec = Vector(rX(gen),rY(gen),rZ(gen));
    }
    
    MyNetMsg_RVec::~MyNetMsg_RVec() {}
    
    bool MyNetMsg_RVec::toStream( NetMessengerStreamBuffer& os) const {
        os << vec.x << vec.y << vec.z;
        return true;
    }

    bool MyNetMsg_RVec::fromStream( NetMessengerStreamBuffer& is ) {
        is >> vec.x >> vec.y >> vec.z;
        return true;
    }
    
    void MyNetMsg_RVec::onMessageArrived() {
        //i used GLView::subscribe_NetMsg_to_callback
    }

    std::string MyNetMsg_RVec::toString() const {
        std::stringstream ss;
        ss << NetMsg::toString();
        ss << "   Payload: " << size << "...\n";
        return ss.str();
    }

}

#endif