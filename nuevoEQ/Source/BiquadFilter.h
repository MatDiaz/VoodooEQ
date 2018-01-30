//
//  BiquadFilter.h
//  IIR_coeff
//
//  Created by Mateo Yepes on 2/09/16.
//  Copyright (c) 2016 Mateo Yepes. All rights reserved.
//

#ifndef __IIR_coeff__BiquadFilter__
#define __IIR_coeff__BiquadFilter__

class BiquadFilter
{
    public:
    
	// Biquad IIR Filter
    
    void initBiquad (float samplingFrequency, bool curve);
    
    void filterSignalMono (float* audioData);
    
    void filterSignalStereo (float* audioDataL, float* audioDataR);
    
    void peakingCoeff();
    
    void lowPassCoeff();
    
    void highPassCoeff();
    
    void displayCoeff();
    
    void resetCoeff();
    
    void createCurve();
    
    float curveVector[890];
    
    //
    bool Active = true;
    
    float Frequency;
    
    float Q;
    
    float Gain;

	protected:

	// Coeff parameters

	float a[3], b[3];

	float hostFrequency;

	float PI = 3.141592653589793;

	// IIR Memory

	float x[3], y[3];
	float xR[3], yR[3];
    
};

#endif /* defined(__IIR_coeff__BiquadFilter__) */
