//
// Created by 10580.
//
#include "catch_amalgamated.hpp"
#include "meta/template/kvtable.hpp"

using byte_t = uint8_t;
using enum_t = int;

struct rational {
    int32_t numerator;
    int32_t denominator;
};

enum Tag {
    ANDROID_COLOR_CORRECTION_MODE,
    ANDROID_COLOR_CORRECTION_TRANSFORM,
    ANDROID_COLOR_CORRECTION_GAINS,
    ANDROID_COLOR_CORRECTION_ABERRATION_MODE,
    ANDROID_COLOR_CORRECTION_AVAILABLE_ABERRATION_MODES,
    ANDROID_CONTROL_AE_ANTIBANDING_MODE,
    ANDROID_CONTROL_AE_EXPOSURE_COMPENSATION,
    ANDROID_CONTROL_AE_LOCK,
    ANDROID_CONTROL_AE_MODE,
    ANDROID_CONTROL_AE_REGIONS,
    ANDROID_CONTROL_AE_TARGET_FPS_RANGE,
    ANDROID_CONTROL_AE_PRECAPTURE_TRIGGER,
    ANDROID_CONTROL_AF_MODE,
    ANDROID_CONTROL_AF_REGIONS,
    ANDROID_CONTROL_AF_TRIGGER,
    ANDROID_CONTROL_AWB_LOCK,
    ANDROID_CONTROL_AWB_MODE,
    ANDROID_CONTROL_AWB_REGIONS,
    ANDROID_CONTROL_CAPTURE_INTENT,
    ANDROID_CONTROL_EFFECT_MODE

};


using tag_entries = meta::type_list<
meta::entry<ANDROID_COLOR_CORRECTION_MODE,                                                   enum_t>,
meta::entry<ANDROID_COLOR_CORRECTION_TRANSFORM,                                              rational[3*3]>,
meta::entry<ANDROID_COLOR_CORRECTION_GAINS,                                                  float[4]>,
meta::entry<ANDROID_COLOR_CORRECTION_ABERRATION_MODE,                                        enum_t>,
meta::entry<ANDROID_COLOR_CORRECTION_AVAILABLE_ABERRATION_MODES,                             byte_t[32]>,
meta::entry<ANDROID_CONTROL_AE_ANTIBANDING_MODE,                                             enum_t>,
meta::entry<ANDROID_CONTROL_AE_EXPOSURE_COMPENSATION,                                        int32_t>,
meta::entry<ANDROID_CONTROL_AE_LOCK,                                                         enum_t>,
meta::entry<ANDROID_CONTROL_AE_MODE,                                                         enum_t>,
meta::entry<ANDROID_CONTROL_AE_REGIONS,                                                      int32_t[5*5]>,
meta::entry<ANDROID_CONTROL_AE_TARGET_FPS_RANGE,                                             int32_t[2]>,
meta::entry<ANDROID_CONTROL_AE_PRECAPTURE_TRIGGER,                                           enum_t>,
meta::entry<ANDROID_CONTROL_AF_MODE,                                                         enum_t>,
meta::entry<ANDROID_CONTROL_AF_REGIONS,                                                      int32_t[5*5]>,
meta::entry<ANDROID_CONTROL_AF_TRIGGER,                                                      enum_t>,
meta::entry<ANDROID_CONTROL_AWB_LOCK,                                                        enum_t>,
meta::entry<ANDROID_CONTROL_AWB_MODE,                                                        enum_t>,
meta::entry<ANDROID_CONTROL_AWB_REGIONS,                                                     int32_t[5*5]>,
meta::entry<ANDROID_CONTROL_CAPTURE_INTENT,                                                  enum_t>,
meta::entry<ANDROID_CONTROL_EFFECT_MODE,                                                     enum_t>
>;


TEST_CASE("kv-table-testing")
{
    using namespace meta;
    SECTION("KVEntry-concept")
    {
        STATIC_REQUIRE(KVEntry<meta::entry<0, char[10]>>);

    }

    SECTION("dump_group_info")
    {
        data_table<tag_entries > dt;
        dt.dump_group_info();
    }
}






