#ifndef SRC_DIFF_OBJECT_H_
#define SRC_DIFF_OBJECT_H_

#include "engine.h"
#include <stdint.h>
#include <string>
#include <vector>
#include <napi.h>

class Example : public Napi::ObjectWrap<Example> {

public:
    static void Init(const Napi::Env &env, Napi::Object &exports);// initializes class and adds it to exports
    Example(const Napi::CallbackInfo &info);// constructor

private:
    static Napi::FunctionReference constructor;
    uint_fast32_t engineType_;// int used in switch for determining which function to use
    std::string myValue_;// used as a test for setter/getter
    std::string target_;// all, mask, region
    std::string filter_;// percent, bounds, blobs
    uint_fast32_t width_;// pixel width
    uint_fast32_t height_;// pixel height
    uint_fast32_t depth_;// 1, 3, 4
    uint_fast32_t pixCount_;// width * height
    uint_fast32_t bufLen_;// pixCount_ * depth
    uint_fast8_t pixDiff_;// 1 - 255
    uint_fast8_t diffsPerc_;// 1 - 100
    uint_fast32_t bitsetCount_;// mask, count of 1's in bitset
    std::vector<bool> bitsetVec_;// mask, 1's and 0's based on pixel index
    uint_fast32_t minDiff_;// regions, minimum pixDiff when comparing all set regions
    uint_fast32_t regionsLen_;// regions, number of regions
    std::vector<Engine::Region> regionsVec_;// regions
    bool async_;// using async or sync
    void Compare(const Napi::CallbackInfo &info);// instance method
    void SetMyValue(const Napi::CallbackInfo &info, const Napi::Value &value);// setter
    Napi::Value GetMyValue(const Napi::CallbackInfo &info);// getter
    Napi::Value (Example::*comparePtr_)(const uint_fast8_t *, const uint_fast8_t *, const Napi::Function &);// function pointer
    Napi::Value GrayAllPercentSync(const uint_fast8_t * buf0, const uint_fast8_t * buf1, const Napi::Function &cb);
    Napi::Value GrayMaskPercentSync(const uint_fast8_t * buf0, const uint_fast8_t * buf1, const Napi::Function &cb);
    Napi::Value GrayRegionsPercentSync(const uint_fast8_t * buf0, const uint_fast8_t * buf1, const Napi::Function &cb);
    Napi::Value GrayAllPercentAsync(const uint_fast8_t * buf0, const uint_fast8_t * buf1, const Napi::Function &cb);
    Napi::Value GrayMaskPercentAsync(const uint_fast8_t * buf0, const uint_fast8_t * buf1, const Napi::Function &cb);
    Napi::Value GrayRegionsPercentAsync(const uint_fast8_t * buf0, const uint_fast8_t * buf1, const Napi::Function &cb);
    Napi::Value RgbAllPercentSync(const uint_fast8_t * buf0, const uint_fast8_t * buf1, const Napi::Function &cb);
    Napi::Value RgbMaskPercentSync(const uint_fast8_t * buf0, const uint_fast8_t * buf1, const Napi::Function &cb);
    Napi::Value RgbRegionsPercentSync(const uint_fast8_t * buf0, const uint_fast8_t * buf1, const Napi::Function &cb);
    Napi::Value RgbAllPercentAsync(const uint_fast8_t * buf0, const uint_fast8_t * buf1, const Napi::Function &cb);
    Napi::Value RgbMaskPercentAsync(const uint_fast8_t * buf0, const uint_fast8_t * buf1, const Napi::Function &cb);
    Napi::Value RgbRegionsPercentAsync(const uint_fast8_t * buf0, const uint_fast8_t * buf1, const Napi::Function &cb);
    static uint_fast32_t GetEngine(const uint_fast32_t depth, const std::string target, const std::string returns, const bool async);
    static void RegionsJsToCpp(const uint_fast32_t pixLen, const uint_fast8_t regionsLen, const Napi::Array &regionsJs, std::vector<Engine::Region> &regionsVec);
    enum Engines {
        GRAY_ALL_PERCENT_SYNC = 0,
        GRAY_MASK_PERCENT_SYNC = 10,
        GRAY_REGIONS_PERCENT_SYNC = 20,
        GRAY_ALL_BOUNDS_SYNC = 100,
        GRAY_MASK_BOUNDS_SYNC = 110,
        GRAY_REGIONS_BOUNDS_SYNC = 120,
        GRAY_ALL_BLOBS_SYNC = 200,
        GRAY_MASK_BLOBS_SYNC = 210,
        GRAY_REGIONS_BLOBS_SYNC = 220,
        GRAY_ALL_PERCENT_ASYNC = 1000,
        GRAY_MASK_PERCENT_ASYNC = 1010,
        GRAY_REGIONS_PERCENT_ASYNC = 1020,
        GRAY_ALL_BOUND_ASYNC = 1100,
        GRAY_MASK_BOUNDS_ASYNC = 1110,
        GRAY_REGIONS_BOUNDS_ASYNC = 1120,
        GRAY_ALL_BLOBS_ASYNC = 1200,
        GRAY_MASK_BLOBS_ASYNC = 1210,
        GRAY_REGIONS_BLOBS_ASYNC = 1220,
        RGB_ALL_PERCENT_SYNC = 1,
        RGB_MASK_PERCENT_SYNC = 11,
        RGB_REGIONS_PERCENT_SYNC = 21,
        RGB_ALL_BOUNDS_SYNC = 101,
        RGB_MASK_BOUNDS_SYNC = 111,
        RGB_REGIONS_BOUNDS_SYNC = 121,
        RGB_ALL_BLOBS_SYNC = 201,
        RGB_MASK_BLOBS_SYNC = 211,
        RGB_REGIONS_BLOBS_SYNC = 221,
        RGB_ALL_PERCENT_ASYNC = 1001,
        RGB_MASK_PERCENT_ASYNC = 1011,
        RGB_REGIONS_PERCENT_ASYNC = 1021,
        RGB_ALL_BOUND_ASYNC = 1101,
        RGB_MASK_BOUNDS_ASYNC = 1111,
        RGB_REGIONS_BOUNDS_ASYNC = 1121,
        RGB_ALL_BLOBS_ASYNC = 1201,
        RGB_MASK_BLOBS_ASYNC = 1211,
        RGB_REGIONS_BLOBS_ASYNC = 1221
    };
};

#endif