/*
  ==============================================================================

    midSideProcess.cpp
    Created: 1 Feb 2017 8:30:33pm
    Author:  Mateo Yepes

  ==============================================================================
*/

#include "midSideProcess.h"

void midSideProcess::processMidSide (bool isProcess, bool isMid, float* audioDataL, float* audioDataR)
{
    if (isProcess)
    {
        if (!isMid)
        {
            float midSum;
            
            midSum = (*audioDataL + *audioDataR) * 0.5;
            *audioDataL = midSum; *audioDataR = midSum;
        }
        else
        {
            float sideSum;
            
            sideSum = (*audioDataL - *audioDataR) * 0.5;
            *audioDataL = sideSum; *audioDataR = - (sideSum);
        }
    }
}
