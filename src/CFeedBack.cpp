#include "CFeedBack.hpp"

float CFeedBack::calculate(SStateVectorData& data) const
{
    float fRet = 0;

    fRet += data.mPhi_C * K_[K_phi];
    fRet += data.mPhi_d * K_[K_phi_d];
    fRet += data.mPsi_d * K_[K_psi_d];

    return -fRet;
}