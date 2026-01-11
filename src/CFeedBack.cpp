#include "CFeedBack.hpp"

float CFeedBack::calculate(SStateVectorData& data) const
{
    float fRet = 0;

    // Contribution of angular position (with offset compensation)
    fRet += (data.mPhi_C + 0.0466200608116212f) * K_[K_phi];
    // Contribution of angular velocity
    fRet += data.mPhi_d * K_[K_phi_d];
    // Contribution of yaw rate
    fRet += data.mPsi_d * K_[K_psi_d];

    fRet *= -1;

    return fRet;
}
