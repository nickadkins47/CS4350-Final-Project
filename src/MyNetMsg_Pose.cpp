
#include "MyNetMsg_Pose.h"

#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr {

    NetMsgMacroDefinition( MyNetMsg_Pose );

    MyNetMsg_Pose::MyNetMsg_Pose() {
        pose = Mat4();
    }

    MyNetMsg_Pose::MyNetMsg_Pose(Mat4 const& pose) {
        this->pose = pose;
    }
    
    MyNetMsg_Pose::~MyNetMsg_Pose() {}
    
    bool MyNetMsg_Pose::toStream( NetMessengerStreamBuffer& os) const {
        for (size_t i = 0; i < size; i++) {
            os << pose.at(i);
        }
        return true;
    }

    bool MyNetMsg_Pose::fromStream( NetMessengerStreamBuffer& is ) {
        for (size_t i = 0; i < size; i++) {
            is >> pose.at(i);
        }
        return true;
    }
    
    void MyNetMsg_Pose::onMessageArrived() {
        //i used GLView::subscribe_NetMsg_to_callback
    }

    std::string MyNetMsg_Pose::toString() const {
        std::stringstream ss;
        ss << NetMsg::toString();
        ss << "   Payload: " << size << "...\n";
        return ss.str();
    }

}

#endif