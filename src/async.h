#ifndef SRC_ASYNC_H_
#define SRC_ASYNC_H_

#include "engine.h"
#include <stdint.h>
#include <vector>
#include <napi.h>

class DiffWorker : public Napi::AsyncWorker {

public:
    DiffWorker(const uint_fast32_t pixCount, const uint_fast8_t pixDiff, const uint_fast8_t diffsPerc, const uint_fast8_t *buf0, const uint_fast8_t *buf1, const Napi::Function &cb);
    DiffWorker(const uint_fast32_t pixCount, const uint_fast8_t pixDiff, const uint_fast8_t diffsPerc, const uint_fast32_t bitsetCount, const std::vector<bool> &bitsetVec, const uint_fast8_t *buf0, const uint_fast8_t *buf1, const Napi::Function &cb);
    DiffWorker(const uint_fast32_t pixCount, const uint_fast8_t minDiff, const uint_fast8_t regionsLen, std::vector<Engine::Region> &regionsVec, const uint_fast8_t *buf0, const uint_fast8_t *buf1, const Napi::Function &cb);
    DiffWorker(const uint_fast32_t pixCount, const uint_fast8_t pixDepth, const uint_fast8_t pixDiff, const uint_fast8_t diffsPerc, const uint_fast8_t *buf0, const uint_fast8_t *buf1, const Napi::Function &cb);
    DiffWorker(const uint_fast32_t pixCount, const uint_fast8_t pixDepth, const uint_fast8_t pixDiff, const uint_fast8_t diffsPerc, const uint_fast32_t bitsetCount, const std::vector<bool> &bitsetVec, const uint_fast8_t *buf0, const uint_fast8_t *buf1, const Napi::Function &cb);
    DiffWorker(const uint_fast32_t pixCount, const uint_fast8_t pixDepth, const uint_fast8_t minDiff, const uint_fast8_t regionsLen, std::vector<Engine::Region> &regionsVec, const uint_fast8_t *buf0, const uint_fast8_t *buf1, const Napi::Function &cb);
    void Execute();
    void OnOK();

private:
    uint_fast32_t pixCount_;// number of pixels
    uint_fast8_t pixDepth_;// number of bytes per pixel
    uint_fast8_t pixDiff_;// can only be 0 - 255
    uint_fast8_t diffsPerc_;// minimum percent 0 - 100
    uint_fast32_t bitsetCount_;// number of 1's in bitset, others are 0
    const std::vector<bool> bitsetVec_;// mask, 1's and 0's based on pixel index
    uint_fast8_t minDiff_;// can only be 0 - 255
    uint_fast8_t regionsLen_;// number of 1's in bitset, others are 0
    const std::vector<Engine::Region> regionsVec_;//
    const uint_fast8_t *buf0_;// pixel buffer
    const uint_fast8_t *buf1_;// pixel buffer
    uint_fast8_t percentResult_;// percent placeholder
    std::vector<uint_fast32_t> resultsVec_;//

    void (DiffWorker::*ExecutePtr_)();// function pointer
    void (DiffWorker::*OnOkPtr_)();// function pointer

    void GrayAllPercentExecute();
    void GrayAllPercentOnOk();

    void GrayMaskPercentExecute();
    void GrayMaskPercentOnOk();

    void GrayRegionsPercentExecute();
    void GrayRegionsPercentOnOk();

    void RgbAllPercentExecute();
    void RgbAllPercentOnOk();

    void RgbMaskPercentExecute();
    void RgbMaskPercentOnOk();

    void RgbRegionsPercentExecute();
    void RgbRegionsPercentOnOk();
};

#endif