
#pragma once

#include "NetMsg.h"
#include "Vector.h"
#include "VectorFwd.h"
#include "ManagerGLView.h"
#include <random>

#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr {

    class MyNetMsg_RVec : public NetMsg {
    public:

        NetMsgMacroDeclaration( MyNetMsg_RVec );

        MyNetMsg_RVec();
        ~MyNetMsg_RVec();
        bool toStream( NetMessengerStreamBuffer& os) const;
        bool fromStream( NetMessengerStreamBuffer& is );
        void onMessageArrived();
        std::string toString() const;

        size_t const size = 3;
        Vector vec;
        
    protected:

        // for C++ random number generation stuff
        using randDev = std::random_device;
        using MersenneTw = std::mt19937;
        using fdist = std::uniform_real_distribution<float>;

    };

}

#endif