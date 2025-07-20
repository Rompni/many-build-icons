#pragma once
#include <Geode/modify/GJGarageLayer.hpp>

class GJGarageLayerExt : public geode::Modify<GJGarageLayerExt, GJGarageLayer> {
public:
    bool init();
    void onMyButton(CCObject*);
};