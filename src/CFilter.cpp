#include "CFilter.hpp"

CFilter::CFilter()
    : bFirstExecution_(true)
    , fLastValue_(0)
{
}

SStateVectorData CFilter::filter(const SStateVectorData& sData)
{
    SStateVectorData sDataRet = sData;

    if (bFirstExecution_ == true)
    {
        bFirstExecution_ = false;

        fLastValue_ = sData.mPhi_A;
    }
    else
    {
        fLastValue_ = fAlpha_ * (fLastValue_ + fT_ * sData.mPhi_d) + (1 - fAlpha_) * sData.mPhi_A;
    }

    sDataRet.mPhi_C = fLastValue_;

    return sDataRet;
}