
#pragma once

#include "NetMsg.h"
#include "Mat4.h"
#include "Mat4Fwd.h"
#include "ManagerGLView.h"

#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr {

    class MyNetMsg_Pose : public NetMsg {
    public:
        NetMsgMacroDeclaration( MyNetMsg_Pose );

        MyNetMsg_Pose();
        MyNetMsg_Pose(Mat4 const& pose);
        ~MyNetMsg_Pose();
        bool toStream( NetMessengerStreamBuffer& os) const;
        bool fromStream( NetMessengerStreamBuffer& is );
        void onMessageArrived();
        std::string toString() const;

        size_t const size = 16;

        /**
         * Pose will be stored in the stream
         * as 16 sequential float values
         */
        Mat4 pose;

    };

}

#endif
