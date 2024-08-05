//
// Created by 10580.
//
#include <cstdint>
#include <cassert>
#include "meta/constexpr/kvtable.hpp"
using namespace meta;

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
    ANDROID_CONTROL_EFFECT_MODE,
    ANDROID_CONTROL_MODE,
    ANDROID_CONTROL_SCENE_MODE,
    ANDROID_CONTROL_VIDEO_STABILIZATION_MODE,
    ANDROID_CONTROL_AE_AVAILABLE_ANTIBANDING_MODES,
    ANDROID_CONTROL_AE_AVAILABLE_MODES,
    ANDROID_CONTROL_AE_AVAILABLE_TARGET_FPS_RANGES,
    ANDROID_CONTROL_AE_COMPENSATION_RANGE,
    ANDROID_CONTROL_AE_COMPENSATION_STEP,
    ANDROID_CONTROL_AF_AVAILABLE_MODES,
    ANDROID_CONTROL_AVAILABLE_EFFECTS,
    ANDROID_CONTROL_AVAILABLE_SCENE_MODES,
    ANDROID_CONTROL_AVAILABLE_VIDEO_STABILIZATION_MODES,
    ANDROID_CONTROL_AWB_AVAILABLE_MODES,
    ANDROID_CONTROL_MAX_REGIONS,
    ANDROID_CONTROL_SCENE_MODE_OVERRIDES,
    ANDROID_CONTROL_AE_PRECAPTURE_ID,
    ANDROID_CONTROL_AE_STATE,
    ANDROID_CONTROL_AF_STATE,
    ANDROID_CONTROL_AF_TRIGGER_ID,
    ANDROID_CONTROL_AWB_STATE,
    ANDROID_CONTROL_AVAILABLE_HIGH_SPEED_VIDEO_CONFIGURATIONS,
    ANDROID_CONTROL_AE_LOCK_AVAILABLE,
    ANDROID_CONTROL_AWB_LOCK_AVAILABLE,
    ANDROID_CONTROL_AVAILABLE_MODES,
    ANDROID_CONTROL_POST_RAW_SENSITIVITY_BOOST_RANGE,
    ANDROID_CONTROL_POST_RAW_SENSITIVITY_BOOST,
    ANDROID_CONTROL_ENABLE_ZSL,
    ANDROID_CONTROL_AF_SCENE_CHANGE,
    ANDROID_CONTROL_AVAILABLE_EXTENDED_SCENE_MODE_MAX_SIZES,
    ANDROID_CONTROL_AVAILABLE_EXTENDED_SCENE_MODE_ZOOM_RATIO_RANGES,
    ANDROID_CONTROL_EXTENDED_SCENE_MODE,
    ANDROID_CONTROL_ZOOM_RATIO_RANGE,
    ANDROID_CONTROL_ZOOM_RATIO,
    ANDROID_CONTROL_AVAILABLE_HIGH_SPEED_VIDEO_CONFIGURATIONS_MAXIMUM_RESOLUTION,
    ANDROID_CONTROL_AF_REGIONS_SET,
    ANDROID_CONTROL_AE_REGIONS_SET,
    ANDROID_CONTROL_AWB_REGIONS_SET,
    ANDROID_DEMOSAIC_MODE,
    ANDROID_EDGE_MODE,
    ANDROID_EDGE_STRENGTH,
    ANDROID_EDGE_AVAILABLE_EDGE_MODES,
    ANDROID_FLASH_FIRING_POWER,
    ANDROID_FLASH_FIRING_TIME,
    ANDROID_FLASH_MODE,
    ANDROID_FLASH_COLOR_TEMPERATURE,
    ANDROID_FLASH_MAX_ENERGY,
    ANDROID_FLASH_STATE,
    ANDROID_FLASH_INFO_AVAILABLE,
    ANDROID_FLASH_INFO_CHARGE_DURATION,
    ANDROID_HOT_PIXEL_MODE,
    ANDROID_HOT_PIXEL_AVAILABLE_HOT_PIXEL_MODES,
    ANDROID_JPEG_GPS_COORDINATES,
    ANDROID_JPEG_GPS_PROCESSING_METHOD,
    ANDROID_JPEG_GPS_TIMESTAMP,
    ANDROID_JPEG_ORIENTATION,
    ANDROID_JPEG_QUALITY,
    ANDROID_JPEG_THUMBNAIL_QUALITY,
    ANDROID_JPEG_THUMBNAIL_SIZE,
    ANDROID_JPEG_AVAILABLE_THUMBNAIL_SIZES,
    ANDROID_JPEG_MAX_SIZE,
    ANDROID_JPEG_SIZE,
    ANDROID_LENS_APERTURE,
    ANDROID_LENS_FILTER_DENSITY,
    ANDROID_LENS_FOCAL_LENGTH,
    ANDROID_LENS_FOCUS_DISTANCE,
    ANDROID_LENS_OPTICAL_STABILIZATION_MODE,
    ANDROID_LENS_FACING,
    ANDROID_LENS_POSE_ROTATION,
    ANDROID_LENS_POSE_TRANSLATION,
    ANDROID_LENS_FOCUS_RANGE,
    ANDROID_LENS_STATE,
    ANDROID_LENS_INTRINSIC_CALIBRATION,
    ANDROID_LENS_RADIAL_DISTORTION,
    ANDROID_LENS_POSE_REFERENCE,
    ANDROID_LENS_DISTORTION,
    ANDROID_LENS_DISTORTION_MAXIMUM_RESOLUTION,
    ANDROID_LENS_INTRINSIC_CALIBRATION_MAXIMUM_RESOLUTION,
    ANDROID_LENS_INFO_AVAILABLE_APERTURES,
    ANDROID_LENS_INFO_AVAILABLE_FILTER_DENSITIES,
    ANDROID_LENS_INFO_AVAILABLE_FOCAL_LENGTHS,
    ANDROID_LENS_INFO_AVAILABLE_OPTICAL_STABILIZATION,
    ANDROID_LENS_INFO_HYPERFOCAL_DISTANCE,
    ANDROID_LENS_INFO_MINIMUM_FOCUS_DISTANCE,
    ANDROID_LENS_INFO_SHADING_MAP_SIZE,
    ANDROID_LENS_INFO_FOCUS_DISTANCE_CALIBRATION,
    ANDROID_NOISE_REDUCTION_MODE,
    ANDROID_NOISE_REDUCTION_STRENGTH,
    ANDROID_NOISE_REDUCTION_AVAILABLE_NOISE_REDUCTION_MODES,
    ANDROID_QUIRKS_METERING_CROP_REGION,
    ANDROID_QUIRKS_TRIGGER_AF_WITH_AUTO,
    ANDROID_QUIRKS_USE_ZSL_FORMAT,
    ANDROID_QUIRKS_USE_PARTIAL_RESULT,
    ANDROID_QUIRKS_PARTIAL_RESULT,
    ANDROID_REQUEST_FRAME_COUNT,
    ANDROID_REQUEST_ID,
    ANDROID_REQUEST_INPUT_STREAMS,
    ANDROID_REQUEST_METADATA_MODE,
    ANDROID_REQUEST_OUTPUT_STREAMS,
    ANDROID_REQUEST_TYPE,
    ANDROID_REQUEST_MAX_NUM_OUTPUT_STREAMS,
    ANDROID_REQUEST_MAX_NUM_REPROCESS_STREAMS,
    ANDROID_REQUEST_MAX_NUM_INPUT_STREAMS,
    ANDROID_REQUEST_PIPELINE_DEPTH,
    ANDROID_REQUEST_PIPELINE_MAX_DEPTH,
    ANDROID_REQUEST_PARTIAL_RESULT_COUNT,
    ANDROID_REQUEST_AVAILABLE_CAPABILITIES,
    ANDROID_REQUEST_AVAILABLE_REQUEST_KEYS,
    ANDROID_REQUEST_AVAILABLE_RESULT_KEYS,
    ANDROID_REQUEST_AVAILABLE_CHARACTERISTICS_KEYS,
    ANDROID_REQUEST_AVAILABLE_SESSION_KEYS,
    ANDROID_REQUEST_AVAILABLE_PHYSICAL_CAMERA_REQUEST_KEYS,
    ANDROID_REQUEST_CHARACTERISTIC_KEYS_NEEDING_PERMISSION,
    ANDROID_SCALER_CROP_REGION,
    ANDROID_SCALER_AVAILABLE_FORMATS,
    ANDROID_SCALER_AVAILABLE_JPEG_MIN_DURATIONS,
    ANDROID_SCALER_AVAILABLE_JPEG_SIZES,
    ANDROID_SCALER_AVAILABLE_MAX_DIGITAL_ZOOM,
    ANDROID_SCALER_AVAILABLE_PROCESSED_MIN_DURATIONS,
    ANDROID_SCALER_AVAILABLE_PROCESSED_SIZES,
    ANDROID_SCALER_AVAILABLE_RAW_MIN_DURATIONS,
    ANDROID_SCALER_AVAILABLE_RAW_SIZES,
    ANDROID_SCALER_AVAILABLE_INPUT_OUTPUT_FORMATS_MAP,
    ANDROID_SCALER_AVAILABLE_STREAM_CONFIGURATIONS,
    ANDROID_SCALER_AVAILABLE_MIN_FRAME_DURATIONS,
    ANDROID_SCALER_AVAILABLE_STALL_DURATIONS,
    ANDROID_SCALER_CROPPING_TYPE,
    ANDROID_SCALER_AVAILABLE_RECOMMENDED_STREAM_CONFIGURATIONS,
    ANDROID_SCALER_AVAILABLE_RECOMMENDED_INPUT_OUTPUT_FORMATS_MAP,
    ANDROID_SCALER_AVAILABLE_ROTATE_AND_CROP_MODES,
    ANDROID_SCALER_ROTATE_AND_CROP,
    ANDROID_SCALER_DEFAULT_SECURE_IMAGE_SIZE,
    ANDROID_SCALER_PHYSICAL_CAMERA_MULTI_RESOLUTION_STREAM_CONFIGURATIONS,
    ANDROID_SCALER_AVAILABLE_STREAM_CONFIGURATIONS_MAXIMUM_RESOLUTION,
    ANDROID_SCALER_AVAILABLE_MIN_FRAME_DURATIONS_MAXIMUM_RESOLUTION,
    ANDROID_SCALER_AVAILABLE_STALL_DURATIONS_MAXIMUM_RESOLUTION,
    ANDROID_SCALER_AVAILABLE_INPUT_OUTPUT_FORMATS_MAP_MAXIMUM_RESOLUTION,
    ANDROID_SCALER_MULTI_RESOLUTION_STREAM_SUPPORTED,
    ANDROID_SCALER_CROP_REGION_SET,
    ANDROID_SENSOR_EXPOSURE_TIME,
    ANDROID_SENSOR_FRAME_DURATION,
    ANDROID_SENSOR_SENSITIVITY,
    ANDROID_SENSOR_REFERENCE_ILLUMINANT1,
    ANDROID_SENSOR_REFERENCE_ILLUMINANT2,
    ANDROID_SENSOR_CALIBRATION_TRANSFORM1,
    ANDROID_SENSOR_CALIBRATION_TRANSFORM2,
    ANDROID_SENSOR_COLOR_TRANSFORM1,
    ANDROID_SENSOR_COLOR_TRANSFORM2,
    ANDROID_SENSOR_FORWARD_MATRIX1,
    ANDROID_SENSOR_FORWARD_MATRIX2,
    ANDROID_SENSOR_BASE_GAIN_FACTOR,
    ANDROID_SENSOR_BLACK_LEVEL_PATTERN,
    ANDROID_SENSOR_MAX_ANALOG_SENSITIVITY,
    ANDROID_SENSOR_ORIENTATION,
    ANDROID_SENSOR_PROFILE_HUE_SAT_MAP_DIMENSIONS,
    ANDROID_SENSOR_TIMESTAMP,
    ANDROID_SENSOR_TEMPERATURE,
    ANDROID_SENSOR_NEUTRAL_COLOR_POINT,
    ANDROID_SENSOR_PROFILE_TONE_CURVE,
    ANDROID_SENSOR_GREEN_SPLIT,
    ANDROID_SENSOR_TEST_PATTERN_DATA,
    ANDROID_SENSOR_TEST_PATTERN_MODE,
    ANDROID_SENSOR_AVAILABLE_TEST_PATTERN_MODES,
    ANDROID_SENSOR_ROLLING_SHUTTER_SKEW,
    ANDROID_SENSOR_OPTICAL_BLACK_REGIONS,
    ANDROID_SENSOR_DYNAMIC_BLACK_LEVEL,
    ANDROID_SENSOR_DYNAMIC_WHITE_LEVEL,
    ANDROID_SENSOR_OPAQUE_RAW_SIZE,
    ANDROID_SENSOR_OPAQUE_RAW_SIZE_MAXIMUM_RESOLUTION,
    ANDROID_SENSOR_PIXEL_MODE,
    ANDROID_SENSOR_RAW_BINNING_FACTOR_USED,
    ANDROID_SENSOR_INFO_ACTIVE_ARRAY_SIZE,
    ANDROID_SENSOR_INFO_SENSITIVITY_RANGE,
    ANDROID_SENSOR_INFO_COLOR_FILTER_ARRANGEMENT,
    ANDROID_SENSOR_INFO_EXPOSURE_TIME_RANGE,
    ANDROID_SENSOR_INFO_MAX_FRAME_DURATION,
    ANDROID_SENSOR_INFO_PHYSICAL_SIZE,
    ANDROID_SENSOR_INFO_PIXEL_ARRAY_SIZE,
    ANDROID_SENSOR_INFO_WHITE_LEVEL,
    ANDROID_SENSOR_INFO_TIMESTAMP_SOURCE,
    ANDROID_SENSOR_INFO_LENS_SHADING_APPLIED,
    ANDROID_SENSOR_INFO_PRE_CORRECTION_ACTIVE_ARRAY_SIZE,
    ANDROID_SENSOR_INFO_ACTIVE_ARRAY_SIZE_MAXIMUM_RESOLUTION,
    ANDROID_SENSOR_INFO_PIXEL_ARRAY_SIZE_MAXIMUM_RESOLUTION,
    ANDROID_SENSOR_INFO_PRE_CORRECTION_ACTIVE_ARRAY_SIZE_MAXIMUM_RESOLUTION,
    ANDROID_SENSOR_INFO_BINNING_FACTOR,
    ANDROID_SHADING_MODE,
    ANDROID_SHADING_STRENGTH,
    ANDROID_SHADING_AVAILABLE_MODES,
    ANDROID_STATISTICS_FACE_DETECT_MODE,
    ANDROID_STATISTICS_HISTOGRAM_MODE,
    ANDROID_STATISTICS_SHARPNESS_MAP_MODE,
    ANDROID_STATISTICS_HOT_PIXEL_MAP_MODE,
    ANDROID_STATISTICS_FACE_IDS,
    ANDROID_STATISTICS_FACE_LANDMARKS,
    ANDROID_STATISTICS_FACE_RECTANGLES,
    ANDROID_STATISTICS_FACE_SCORES,
    ANDROID_STATISTICS_HISTOGRAM,
    ANDROID_STATISTICS_LENS_SHADING_CORRECTION_MAP,
    ANDROID_STATISTICS_PREDICTED_COLOR_GAINS,
    ANDROID_STATISTICS_PREDICTED_COLOR_TRANSFORM,
    ANDROID_STATISTICS_SCENE_FLICKER,
    ANDROID_STATISTICS_HOT_PIXEL_MAP,
    ANDROID_STATISTICS_LENS_SHADING_MAP_MODE,
    ANDROID_STATISTICS_OIS_DATA_MODE,
    ANDROID_STATISTICS_OIS_TIMESTAMPS,
    ANDROID_STATISTICS_OIS_X_SHIFTS,
    ANDROID_STATISTICS_OIS_Y_SHIFTS,
    ANDROID_STATISTICS_INFO_AVAILABLE_FACE_DETECT_MODES
};


constexpr auto tag_entries = type_list<
entry<ANDROID_COLOR_CORRECTION_MODE,                                                   enum_t>,
entry<ANDROID_COLOR_CORRECTION_TRANSFORM,                                              rational[3*3]>,
entry<ANDROID_COLOR_CORRECTION_GAINS,                                                  float[4]>,
entry<ANDROID_COLOR_CORRECTION_ABERRATION_MODE,                                        enum_t>,
entry<ANDROID_COLOR_CORRECTION_AVAILABLE_ABERRATION_MODES,                             byte_t[32]>,
entry<ANDROID_CONTROL_AE_ANTIBANDING_MODE,                                             enum_t>,
entry<ANDROID_CONTROL_AE_EXPOSURE_COMPENSATION,                                        int32_t>,
entry<ANDROID_CONTROL_AE_LOCK,                                                         enum_t>,
entry<ANDROID_CONTROL_AE_MODE,                                                         enum_t>,
entry<ANDROID_CONTROL_AE_REGIONS,                                                      int32_t[5*5]>,
entry<ANDROID_CONTROL_AE_TARGET_FPS_RANGE,                                             int32_t[2]>,
entry<ANDROID_CONTROL_AE_PRECAPTURE_TRIGGER,                                           enum_t>,
entry<ANDROID_CONTROL_AF_MODE,                                                         enum_t>,
entry<ANDROID_CONTROL_AF_REGIONS,                                                      int32_t[5*5]>,
entry<ANDROID_CONTROL_AF_TRIGGER,                                                      enum_t>,
entry<ANDROID_CONTROL_AWB_LOCK,                                                        enum_t>,
entry<ANDROID_CONTROL_AWB_MODE,                                                        enum_t>,
entry<ANDROID_CONTROL_AWB_REGIONS,                                                     int32_t[5*5]>,
entry<ANDROID_CONTROL_CAPTURE_INTENT,                                                  enum_t>,
entry<ANDROID_CONTROL_EFFECT_MODE,                                                     enum_t>,
entry<ANDROID_CONTROL_MODE,                                                            enum_t>,
entry<ANDROID_CONTROL_SCENE_MODE,                                                      enum_t>,
entry<ANDROID_CONTROL_VIDEO_STABILIZATION_MODE,                                        enum_t>,
entry<ANDROID_CONTROL_AE_AVAILABLE_ANTIBANDING_MODES,                                  byte_t[32]>,
entry<ANDROID_CONTROL_AE_AVAILABLE_MODES,                                              byte_t[32]>,
entry<ANDROID_CONTROL_AE_AVAILABLE_TARGET_FPS_RANGES,                                  int32_t[2*32]>,
entry<ANDROID_CONTROL_AE_COMPENSATION_RANGE,                                           int32_t[2]>,
entry<ANDROID_CONTROL_AE_COMPENSATION_STEP,                                            rational>,
entry<ANDROID_CONTROL_AF_AVAILABLE_MODES,                                              byte_t[32]>,
entry<ANDROID_CONTROL_AVAILABLE_EFFECTS,                                               byte_t[32]>,
entry<ANDROID_CONTROL_AVAILABLE_SCENE_MODES,                                           byte_t[32]>,
entry<ANDROID_CONTROL_AVAILABLE_VIDEO_STABILIZATION_MODES,                             byte_t[32]>,
entry<ANDROID_CONTROL_AWB_AVAILABLE_MODES,                                             byte_t[32]>,
entry<ANDROID_CONTROL_MAX_REGIONS,                                                     int32_t[3]>,
entry<ANDROID_CONTROL_SCENE_MODE_OVERRIDES,                                            byte_t[3*10]>,
entry<ANDROID_CONTROL_AE_PRECAPTURE_ID,                                                int32_t>,
entry<ANDROID_CONTROL_AE_STATE,                                                        enum_t>,
entry<ANDROID_CONTROL_AF_STATE,                                                        enum_t>,
entry<ANDROID_CONTROL_AF_TRIGGER_ID,                                                   int32_t>,
entry<ANDROID_CONTROL_AWB_STATE,                                                       enum_t>,
entry<ANDROID_CONTROL_AVAILABLE_HIGH_SPEED_VIDEO_CONFIGURATIONS,                       int32_t[5*32]>,
entry<ANDROID_CONTROL_AE_LOCK_AVAILABLE,                                               enum_t>,
entry<ANDROID_CONTROL_AWB_LOCK_AVAILABLE,                                              enum_t>,
entry<ANDROID_CONTROL_AVAILABLE_MODES,                                                 byte_t[32]>,
entry<ANDROID_CONTROL_POST_RAW_SENSITIVITY_BOOST_RANGE,                                int32_t[2]>,
entry<ANDROID_CONTROL_POST_RAW_SENSITIVITY_BOOST,                                      int32_t>,
entry<ANDROID_CONTROL_ENABLE_ZSL,                                                      enum_t>,
entry<ANDROID_CONTROL_AF_SCENE_CHANGE,                                                 enum_t>,
entry<ANDROID_CONTROL_AVAILABLE_EXTENDED_SCENE_MODE_MAX_SIZES,                         int32_t[3*32]>,
entry<ANDROID_CONTROL_AVAILABLE_EXTENDED_SCENE_MODE_ZOOM_RATIO_RANGES,                 float[2*32]>,
entry<ANDROID_CONTROL_EXTENDED_SCENE_MODE,                                             enum_t>,
entry<ANDROID_CONTROL_ZOOM_RATIO_RANGE,                                                float[2]>,
entry<ANDROID_CONTROL_ZOOM_RATIO,                                                      float>,
entry<ANDROID_CONTROL_AVAILABLE_HIGH_SPEED_VIDEO_CONFIGURATIONS_MAXIMUM_RESOLUTION,    int32_t[5*32]>,
entry<ANDROID_CONTROL_AF_REGIONS_SET,                                                  enum_t>,
entry<ANDROID_CONTROL_AE_REGIONS_SET,                                                  enum_t>,
entry<ANDROID_CONTROL_AWB_REGIONS_SET,                                                 enum_t>,
entry<ANDROID_DEMOSAIC_MODE,                                                           enum_t>,
entry<ANDROID_EDGE_MODE,                                                               enum_t>,
entry<ANDROID_EDGE_STRENGTH,                                                           byte_t>,
entry<ANDROID_EDGE_AVAILABLE_EDGE_MODES,                                               byte_t[32]>,
entry<ANDROID_FLASH_FIRING_POWER,                                                      byte_t>,
entry<ANDROID_FLASH_FIRING_TIME,                                                       int64_t>,
entry<ANDROID_FLASH_MODE,                                                              enum_t>,
entry<ANDROID_FLASH_COLOR_TEMPERATURE,                                                 byte_t>,
entry<ANDROID_FLASH_MAX_ENERGY,                                                        byte_t>,
entry<ANDROID_FLASH_STATE,                                                             enum_t>,
entry<ANDROID_FLASH_INFO_AVAILABLE,                                                    enum_t>,
entry<ANDROID_FLASH_INFO_CHARGE_DURATION,                                              int64_t>,
entry<ANDROID_HOT_PIXEL_MODE,                                                          enum_t>,
entry<ANDROID_HOT_PIXEL_AVAILABLE_HOT_PIXEL_MODES,                                     byte_t[32]>,
entry<ANDROID_JPEG_GPS_COORDINATES,                                                    double[3]>,
entry<ANDROID_JPEG_GPS_PROCESSING_METHOD,                                              byte_t>,
entry<ANDROID_JPEG_GPS_TIMESTAMP,                                                      int64_t>,
entry<ANDROID_JPEG_ORIENTATION,                                                        int32_t>,
entry<ANDROID_JPEG_QUALITY,                                                            byte_t>,
entry<ANDROID_JPEG_THUMBNAIL_QUALITY,                                                  byte_t>,
entry<ANDROID_JPEG_THUMBNAIL_SIZE,                                                     int32_t[2]>,
entry<ANDROID_JPEG_AVAILABLE_THUMBNAIL_SIZES,                                          int32_t[2*32]>,
entry<ANDROID_JPEG_MAX_SIZE,                                                           int32_t>,
entry<ANDROID_JPEG_SIZE,                                                               int32_t>,
entry<ANDROID_LENS_APERTURE,                                                           float>,
entry<ANDROID_LENS_FILTER_DENSITY,                                                     float>,
entry<ANDROID_LENS_FOCAL_LENGTH,                                                       float>,
entry<ANDROID_LENS_FOCUS_DISTANCE,                                                     float>,
entry<ANDROID_LENS_OPTICAL_STABILIZATION_MODE,                                         enum_t>,
entry<ANDROID_LENS_FACING,                                                             enum_t>,
entry<ANDROID_LENS_POSE_ROTATION,                                                      float[4]>,
entry<ANDROID_LENS_POSE_TRANSLATION,                                                   float[3]>,
entry<ANDROID_LENS_FOCUS_RANGE,                                                        float[2]>,
entry<ANDROID_LENS_STATE,                                                              enum_t>,
entry<ANDROID_LENS_INTRINSIC_CALIBRATION,                                              float[5]>,
entry<ANDROID_LENS_RADIAL_DISTORTION,                                                  float[6]>,
entry<ANDROID_LENS_POSE_REFERENCE,                                                     enum_t>,
entry<ANDROID_LENS_DISTORTION,                                                         float[5]>,
entry<ANDROID_LENS_DISTORTION_MAXIMUM_RESOLUTION,                                      float[5]>,
entry<ANDROID_LENS_INTRINSIC_CALIBRATION_MAXIMUM_RESOLUTION,                           float[5]>,
entry<ANDROID_LENS_INFO_AVAILABLE_APERTURES,                                           float[32]>,
entry<ANDROID_LENS_INFO_AVAILABLE_FILTER_DENSITIES,                                    float[32]>,
entry<ANDROID_LENS_INFO_AVAILABLE_FOCAL_LENGTHS,                                       float[32]>,
entry<ANDROID_LENS_INFO_AVAILABLE_OPTICAL_STABILIZATION,                               byte_t[32]>,
entry<ANDROID_LENS_INFO_HYPERFOCAL_DISTANCE,                                           float>,
entry<ANDROID_LENS_INFO_MINIMUM_FOCUS_DISTANCE,                                        float>,
entry<ANDROID_LENS_INFO_SHADING_MAP_SIZE,                                              int32_t[2]>,
entry<ANDROID_LENS_INFO_FOCUS_DISTANCE_CALIBRATION,                                    enum_t>,
entry<ANDROID_NOISE_REDUCTION_MODE,                                                    enum_t>,
entry<ANDROID_NOISE_REDUCTION_STRENGTH,                                                byte_t>,
entry<ANDROID_NOISE_REDUCTION_AVAILABLE_NOISE_REDUCTION_MODES,                         byte_t[32]>,
entry<ANDROID_QUIRKS_METERING_CROP_REGION,                                             byte_t>,
entry<ANDROID_QUIRKS_TRIGGER_AF_WITH_AUTO,                                             byte_t>,
entry<ANDROID_QUIRKS_USE_ZSL_FORMAT,                                                   byte_t>,
entry<ANDROID_QUIRKS_USE_PARTIAL_RESULT,                                               byte_t>,
entry<ANDROID_QUIRKS_PARTIAL_RESULT,                                                   enum_t>,
entry<ANDROID_REQUEST_FRAME_COUNT,                                                     int32_t>,
entry<ANDROID_REQUEST_ID,                                                              int32_t>,
entry<ANDROID_REQUEST_INPUT_STREAMS,                                                   int32_t[32]>,
entry<ANDROID_REQUEST_METADATA_MODE,                                                   enum_t>,
entry<ANDROID_REQUEST_OUTPUT_STREAMS,                                                  int32_t[32]>,
entry<ANDROID_REQUEST_TYPE,                                                            enum_t>,
entry<ANDROID_REQUEST_MAX_NUM_OUTPUT_STREAMS,                                          int32_t[3]>,
entry<ANDROID_REQUEST_MAX_NUM_REPROCESS_STREAMS,                                       int32_t[1]>,
entry<ANDROID_REQUEST_MAX_NUM_INPUT_STREAMS,                                           int32_t>,
entry<ANDROID_REQUEST_PIPELINE_DEPTH,                                                  byte_t>,
entry<ANDROID_REQUEST_PIPELINE_MAX_DEPTH,                                              byte_t>,
entry<ANDROID_REQUEST_PARTIAL_RESULT_COUNT,                                            int32_t>,
entry<ANDROID_REQUEST_AVAILABLE_CAPABILITIES,                                          enum_t[32]>,
entry<ANDROID_REQUEST_AVAILABLE_REQUEST_KEYS,                                          int32_t[32]>,
entry<ANDROID_REQUEST_AVAILABLE_RESULT_KEYS,                                           int32_t[32]>,
entry<ANDROID_REQUEST_AVAILABLE_CHARACTERISTICS_KEYS,                                  int32_t[32]>,
entry<ANDROID_REQUEST_AVAILABLE_SESSION_KEYS,                                          int32_t[32]>,
entry<ANDROID_REQUEST_AVAILABLE_PHYSICAL_CAMERA_REQUEST_KEYS,                          int32_t[32]>,
entry<ANDROID_REQUEST_CHARACTERISTIC_KEYS_NEEDING_PERMISSION,                          int32_t[32]>,
entry<ANDROID_SCALER_CROP_REGION,                                                      int32_t[4]>,
entry<ANDROID_SCALER_AVAILABLE_FORMATS,                                                enum_t[32]>,
entry<ANDROID_SCALER_AVAILABLE_JPEG_MIN_DURATIONS,                                     int64_t[32]>,
entry<ANDROID_SCALER_AVAILABLE_JPEG_SIZES,                                             int32_t[32*2]>,
entry<ANDROID_SCALER_AVAILABLE_MAX_DIGITAL_ZOOM,                                       float>,
entry<ANDROID_SCALER_AVAILABLE_PROCESSED_MIN_DURATIONS,                                int64_t[32]>,
entry<ANDROID_SCALER_AVAILABLE_PROCESSED_SIZES,                                        int32_t[32*2]>,
entry<ANDROID_SCALER_AVAILABLE_RAW_MIN_DURATIONS,                                      int64_t[32]>,
entry<ANDROID_SCALER_AVAILABLE_RAW_SIZES,                                              int32_t[32*2]>,
entry<ANDROID_SCALER_AVAILABLE_INPUT_OUTPUT_FORMATS_MAP,                               int32_t>,
entry<ANDROID_SCALER_AVAILABLE_STREAM_CONFIGURATIONS,                                  enum_t[32*4]>,
entry<ANDROID_SCALER_AVAILABLE_MIN_FRAME_DURATIONS,                                    int64_t[4*32]>,
entry<ANDROID_SCALER_AVAILABLE_STALL_DURATIONS,                                        int64_t[4*32]>,
entry<ANDROID_SCALER_CROPPING_TYPE,                                                    enum_t>,
entry<ANDROID_SCALER_AVAILABLE_RECOMMENDED_STREAM_CONFIGURATIONS,                      enum_t[32*5]>,
entry<ANDROID_SCALER_AVAILABLE_RECOMMENDED_INPUT_OUTPUT_FORMATS_MAP,                   int32_t>,
entry<ANDROID_SCALER_AVAILABLE_ROTATE_AND_CROP_MODES,                                  byte_t[32]>,
entry<ANDROID_SCALER_ROTATE_AND_CROP,                                                  enum_t>,
entry<ANDROID_SCALER_DEFAULT_SECURE_IMAGE_SIZE,                                        int32_t[2]>,
entry<ANDROID_SCALER_PHYSICAL_CAMERA_MULTI_RESOLUTION_STREAM_CONFIGURATIONS,           enum_t[32*4]>,
entry<ANDROID_SCALER_AVAILABLE_STREAM_CONFIGURATIONS_MAXIMUM_RESOLUTION,               enum_t[32*4]>,
entry<ANDROID_SCALER_AVAILABLE_MIN_FRAME_DURATIONS_MAXIMUM_RESOLUTION,                 int64_t[4*32]>,
entry<ANDROID_SCALER_AVAILABLE_STALL_DURATIONS_MAXIMUM_RESOLUTION,                     int64_t[4*32]>,
entry<ANDROID_SCALER_AVAILABLE_INPUT_OUTPUT_FORMATS_MAP_MAXIMUM_RESOLUTION,            int32_t>,
entry<ANDROID_SCALER_MULTI_RESOLUTION_STREAM_SUPPORTED,                                enum_t>,
entry<ANDROID_SCALER_CROP_REGION_SET,                                                  enum_t>,
entry<ANDROID_SENSOR_EXPOSURE_TIME,                                                    int64_t>,
entry<ANDROID_SENSOR_FRAME_DURATION,                                                   int64_t>,
entry<ANDROID_SENSOR_SENSITIVITY,                                                      int32_t>,
entry<ANDROID_SENSOR_REFERENCE_ILLUMINANT1,                                            enum_t>,
entry<ANDROID_SENSOR_REFERENCE_ILLUMINANT2,                                            byte_t>,
entry<ANDROID_SENSOR_CALIBRATION_TRANSFORM1,                                           rational[3*3]>,
entry<ANDROID_SENSOR_CALIBRATION_TRANSFORM2,                                           rational[3*3]>,
entry<ANDROID_SENSOR_COLOR_TRANSFORM1,                                                 rational[3*3]>,
entry<ANDROID_SENSOR_COLOR_TRANSFORM2,                                                 rational[3*3]>,
entry<ANDROID_SENSOR_FORWARD_MATRIX1,                                                  rational[3*3]>,
entry<ANDROID_SENSOR_FORWARD_MATRIX2,                                                  rational[3*3]>,
entry<ANDROID_SENSOR_BASE_GAIN_FACTOR,                                                 rational>,
entry<ANDROID_SENSOR_BLACK_LEVEL_PATTERN,                                              int32_t[4]>,
entry<ANDROID_SENSOR_MAX_ANALOG_SENSITIVITY,                                           int32_t>,
entry<ANDROID_SENSOR_ORIENTATION,                                                      int32_t>,
entry<ANDROID_SENSOR_PROFILE_HUE_SAT_MAP_DIMENSIONS,                                   int32_t[3]>,
entry<ANDROID_SENSOR_TIMESTAMP,                                                        int64_t>,
entry<ANDROID_SENSOR_TEMPERATURE,                                                      float>,
entry<ANDROID_SENSOR_NEUTRAL_COLOR_POINT,                                              rational[3]>,
entry<ANDROID_SENSOR_PROFILE_TONE_CURVE,                                               float[10*2]>,
entry<ANDROID_SENSOR_GREEN_SPLIT,                                                      float>,
entry<ANDROID_SENSOR_TEST_PATTERN_DATA,                                                int32_t[4]>,
entry<ANDROID_SENSOR_TEST_PATTERN_MODE,                                                enum_t>,
entry<ANDROID_SENSOR_AVAILABLE_TEST_PATTERN_MODES,                                     int32_t[32]>,
entry<ANDROID_SENSOR_ROLLING_SHUTTER_SKEW,                                             int64_t>,
entry<ANDROID_SENSOR_OPTICAL_BLACK_REGIONS,                                            int32_t[4*10]>,
entry<ANDROID_SENSOR_DYNAMIC_BLACK_LEVEL,                                              float[4]>,
entry<ANDROID_SENSOR_DYNAMIC_WHITE_LEVEL,                                              int32_t>,
entry<ANDROID_SENSOR_OPAQUE_RAW_SIZE,                                                  int32_t[32*3]>,
entry<ANDROID_SENSOR_OPAQUE_RAW_SIZE_MAXIMUM_RESOLUTION,                               int32_t[32*3]>,
entry<ANDROID_SENSOR_PIXEL_MODE,                                                       enum_t>,
entry<ANDROID_SENSOR_RAW_BINNING_FACTOR_USED,                                          enum_t>,
entry<ANDROID_SENSOR_INFO_ACTIVE_ARRAY_SIZE,                                           int32_t[4]>,
entry<ANDROID_SENSOR_INFO_SENSITIVITY_RANGE,                                           int32_t[2]>,
entry<ANDROID_SENSOR_INFO_COLOR_FILTER_ARRANGEMENT,                                    enum_t>,
entry<ANDROID_SENSOR_INFO_EXPOSURE_TIME_RANGE,                                         int64_t[2]>,
entry<ANDROID_SENSOR_INFO_MAX_FRAME_DURATION,                                          int64_t>,
entry<ANDROID_SENSOR_INFO_PHYSICAL_SIZE,                                               float[2]>,
entry<ANDROID_SENSOR_INFO_PIXEL_ARRAY_SIZE,                                            int32_t[2]>,
entry<ANDROID_SENSOR_INFO_WHITE_LEVEL,                                                 int32_t>,
entry<ANDROID_SENSOR_INFO_TIMESTAMP_SOURCE,                                            enum_t>,
entry<ANDROID_SENSOR_INFO_LENS_SHADING_APPLIED,                                        enum_t>,
entry<ANDROID_SENSOR_INFO_PRE_CORRECTION_ACTIVE_ARRAY_SIZE,                            int32_t[4]>,
entry<ANDROID_SENSOR_INFO_ACTIVE_ARRAY_SIZE_MAXIMUM_RESOLUTION,                        int32_t[4]>,
entry<ANDROID_SENSOR_INFO_PIXEL_ARRAY_SIZE_MAXIMUM_RESOLUTION,                         int32_t[2]>,
entry<ANDROID_SENSOR_INFO_PRE_CORRECTION_ACTIVE_ARRAY_SIZE_MAXIMUM_RESOLUTION,         int32_t[4]>,
entry<ANDROID_SENSOR_INFO_BINNING_FACTOR,                                              int32_t[2]>,
entry<ANDROID_SHADING_MODE,                                                            enum_t>,
entry<ANDROID_SHADING_STRENGTH,                                                        byte_t>,
entry<ANDROID_SHADING_AVAILABLE_MODES,                                                 byte_t[32]>,
entry<ANDROID_STATISTICS_FACE_DETECT_MODE,                                             enum_t>,
entry<ANDROID_STATISTICS_HISTOGRAM_MODE,                                               enum_t>,
entry<ANDROID_STATISTICS_SHARPNESS_MAP_MODE,                                           enum_t>,
entry<ANDROID_STATISTICS_HOT_PIXEL_MAP_MODE,                                           enum_t>,
entry<ANDROID_STATISTICS_FACE_IDS,                                                     int32_t[32]>,
entry<ANDROID_STATISTICS_FACE_LANDMARKS,                                               int32_t[32*6]>,
entry<ANDROID_STATISTICS_FACE_RECTANGLES,                                              int32_t[32*4]>,
entry<ANDROID_STATISTICS_FACE_SCORES,                                                  byte_t[32]>,
entry<ANDROID_STATISTICS_HISTOGRAM,                                                    int32_t[32*3]>,
entry<ANDROID_STATISTICS_LENS_SHADING_CORRECTION_MAP,                                  byte_t>,
entry<ANDROID_STATISTICS_PREDICTED_COLOR_GAINS,                                        float[4]>,
entry<ANDROID_STATISTICS_PREDICTED_COLOR_TRANSFORM,                                    rational[3*3]>,
entry<ANDROID_STATISTICS_SCENE_FLICKER,                                                enum_t>,
entry<ANDROID_STATISTICS_HOT_PIXEL_MAP,                                                int32_t[2*32]>,
entry<ANDROID_STATISTICS_LENS_SHADING_MAP_MODE,                                        enum_t>,
entry<ANDROID_STATISTICS_OIS_DATA_MODE,                                                enum_t>,
entry<ANDROID_STATISTICS_OIS_TIMESTAMPS,                                               int64_t[32]>,
entry<ANDROID_STATISTICS_OIS_X_SHIFTS,                                                 float[32]>,
entry<ANDROID_STATISTICS_OIS_Y_SHIFTS,                                                 float[32]>,
entry<ANDROID_STATISTICS_INFO_AVAILABLE_FACE_DETECT_MODES,                             byte_t[32]>
>;





void test_set_get_data()
{
    constexpr auto all_entries = type_list<
            entry<0, int>,
            entry<1, char>,
            entry<2, char>,
            entry<3, short>,
            entry<4, char[10]>,
            entry<5, char[10]>,
            entry<6, int>
    >;

    data_table<all_entries> datatbl;
    datatbl.dump_group_info();

    {
        int expectedValue = 23;
        assert(! datatbl.get_data(0, &expectedValue));
        assert(datatbl.set_data(0, &expectedValue));
        int value = -1;
        assert(datatbl.get_data(0, &value));
        assert(value == expectedValue);
    }

    {
        int expectedValue = 23;
        assert(! datatbl.get_data(6, &expectedValue));
        assert(datatbl.set_data(6, &expectedValue));
        int value = -1;
        assert(datatbl.get_data(6, &value));
        assert(value == expectedValue);
    }

    {
        int invalid;
        assert(! datatbl.get_data(7, &invalid));
        assert(! datatbl.set_data(7, &invalid));
    }

    {
        std::string_view expectedValue = "hello";
        char value[10] {};
        assert(! datatbl.get_data(4, value));
        assert(datatbl.set_data(4, expectedValue.data(), expectedValue.length()));
        assert(datatbl.get_data(4, value));

        assert(expectedValue == value);
    }
}

void test_kvtable()
{

    static_assert(concepts::kventry<entry<0, int>>);
    static_assert(concepts::kventry<entry<1, int[2]>>);
    static_assert(entry<0, char[3]>{} == entry<1, char[3]>{});
#ifdef WIN32
    static_assert(entry<2, long>{} == entry<3, int>{});
#else
    static_assert(entry<2, long>{} == entry<3, long>{});
#endif
}


void test_big_data()
{

    data_table<tag_entries> datatbl;
    datatbl.dump_group_info();
}



int main(int argc, char **argv)
{
    test_kvtable();
    test_set_get_data();
    test_big_data();



    return 0;
}
























