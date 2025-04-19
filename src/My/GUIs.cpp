
#include "GUIs.h"

void MyGUI_ObjectMovements::draw() {
    if (ImGui::Begin("Change Object Position")) {
        if( ImGui::SliderFloat3("Translate", coordinates, -10.0f, 10.0f));
        if( ImGui::SliderFloat3("Rotate (Global)", gRotation, -.1f, .1f));
        if( ImGui::SliderFloat3("Rotate (Local)", lRotation, -.1f, .1f));
        ImGui::End();
    }
}

void MyGUI_ObjectMovements::update() {
    if (obj == nullptr) return;

    obj->moveRelative(Aftr::Vector(coordinates));

    obj->rotateAboutGlobalX(gRotation[0]);
    obj->rotateAboutGlobalY(gRotation[1]);
    obj->rotateAboutGlobalZ(gRotation[2]);

    obj->rotateAboutRelX(lRotation[0]);
    obj->rotateAboutRelY(lRotation[1]);
    obj->rotateAboutRelZ(lRotation[2]);
}

void MyGUI_InfoTab::draw() {
    if (ImGui::Begin("Change Object Position")) {
        ImGui::Text("");
        ImGui::Text("");
        ImGui::Text("");
        ImGui::End();
    }
}

void MyGUI_InfoTab::update() {
    
}