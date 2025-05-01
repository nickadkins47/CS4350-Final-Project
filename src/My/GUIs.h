
/* #pragma once

#include <string>

#include "WO.h"
#include "AftrConfig.h"
#include "AftrImGuiIncludes.h"
#include "Vector.h"
#include "Mat4.h"

#ifdef  AFTR_CONFIG_USE_IMGUI

class MyGUI_ObjectMovements {
public:
    Aftr::WO* obj = nullptr;
    void draw();
    void update();
private:
    float coordinates[3] = {0,0,0};
    float gRotation[3] = {0,0,0};
    float lRotation[3] = {0,0,0};
};

class MyGUI_InfoTab {
public:
    void draw();
    void update();
};

#endif */