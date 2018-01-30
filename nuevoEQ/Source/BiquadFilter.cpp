//
//  BiquadFilter.cpp
//  IIR_coeff
//
//  Created by Mateo Yepes on 2/09/16.
//  Copyright (c) 2016 Mateo Yepes. All rights reserved.
//

#define _USE_MATH_DEFINES
#include "BiquadFilter.h"
#include <iostream>
#include <cmath>


void BiquadFilter::initBiquad (float samplingFrequency, bool curve)
{
    hostFrequency = samplingFrequency;
    
    for (int i = 0; i < 3; i++)
    {
        a[i] = 0;  // a = {a0, a1, a2}
        b[i] = 0;  // b = {b0, b1, b2}
        x[i] = 0;  // x = {[xn], [xn-1], [xn-2]} // Left or mono channel
        y[i] = 0;  // y = {[yn], [yn-1], [yn-2]} // Left or mono channel
        xR[i] = 0; // x = {[xn], [xn-1], [xn-2]} // Right Channel
        yR[i] = 0; // y = {[yn], [yn-1], [yn-2]} // Right Channel
    }
    
    if (curve)
    {
        
        float temp = 3.0f / 890.0f;
                
        float hold = 1;
        
        for (int i = 0; i < 890; i++)
        {
            curveVector[i] = 2 * (pow (10, hold));
            
            hold = hold + temp;
            
            curveVector[i] = (2 * curveVector[i] * M_PI) / samplingFrequency;
            
            curveVector[i] = pow (sin (curveVector[i] / 2.0f), 2);
            
        }
    }
    
}

void BiquadFilter::peakingCoeff()
{
    float A = pow(10, (Gain/40));
    
    float w0 = (2 * PI * Frequency) / hostFrequency;
    
    float alpha = sin(w0) / (2 * Q);
    
    float ao = 1 + (alpha / A);
    
    a[0] = 1;                       // a0
    a[1] = (- 2 * cos(w0))/ ao;     // a1
    a[2] = (1 - (alpha / A)) / ao;  // a2
    
    b[0] = (1 + alpha * A) / ao;    // b0
    b[1] = (- 2 * cos (w0)) / ao;   // b1
    b[2] = (1 - alpha * A) / ao;    // b2
}

void BiquadFilter::lowPassCoeff()
{
    float w0 = (2 * PI * Frequency) / hostFrequency;
    
    float alpha = sin(w0) / (2 * Q);
    
    float ao = 1 + alpha;
    
    a[0] = 1;                        // a0
    a[1] = (- 2 * cos(w0)) / ao;     // a1
    a[2] = (1 - alpha) / ao;         // a2
    
    b[0] = ((1 - cos(w0)) / 2) / ao; // b0
    b[1] = (1 - cos(w0)) / ao;       // b1
    b[2] = ((1 - cos(w0)) / 2) / ao; // b2
}

void BiquadFilter::highPassCoeff()
{
    float w0 = (2 * PI * Frequency) / hostFrequency;
    
    float alpha = sin(w0) / (2 * Q);
    
    float ao = 1 + alpha;
    
    a[0] = 1;                        // a0
    a[1] = (- 2 * cos(w0)) / ao;     // a1
    a[2] = (1 - alpha) / ao;         // a2
    
    b[0] = ((1 + cos(w0)) / 2) / ao; // b0
    b[1] = -(1 + cos(w0)) / ao;      // b1
    b[2] = ((1 + cos(w0)) / 2) / ao; // b2
}

void BiquadFilter::displayCoeff()
{
    std::cout << "a0 = " << a[0] << std::endl;
    std::cout << "a1 = " << a[1] << std::endl;
    std::cout << "a2 = " << a[2] << std::endl;
    
    std::cout << "b0 = " << b[0] << std::endl;
    std::cout << "b1 = " << b[1] << std::endl;
    std::cout << "b2 = " << b[2] << std::endl;
}

void BiquadFilter::resetCoeff()
{
    for (int i = 0; i < 3; i++)
    {
        a[i] = 0;  // a = {a0, a1, a2}
        b[i] = 0;  // b = {b0, b1, b2}
        x[i] = 0;  // x = {[xn], [xn-1], [xn-2]} // Left or mono channel
        y[i] = 0;  // y = {[yn], [yn-1], [yn-2]} // Left or mono channel
        xR[i] = 0; // x = {[xn], [xn-1], [xn-2]} // Right Channel
        yR[i] = 0; // y = {[yn], [yn-1], [yn-2]} // Right Channel
    }
}

void BiquadFilter::createCurve()
{
    if (curveVector == nullptr)
        return;
    else
    {
        
        float temp = 3.0f / 890.0f;
                
        float hold = 1;
        
        for (int i = 0; i < 890; i++)
        {
            curveVector[i] = 2 * (pow (10, hold));
            
            hold = hold + temp;
            
            curveVector[i] = (2 * curveVector[i] * M_PI) / hostFrequency;
            
            curveVector[i] = pow (sin (curveVector[i] / 2.0f), 2);
            
        }
        
        for (int i = 0; i < 890; i++)
        {
            curveVector[i] = (pow (((b[0] + b[1] + b[2]) / 2), 2) - curveVector[i] * ((4 * b[0] * b[2])
                            * (1 - curveVector[i]) + b[1] * (b[0] + b[2]))) / (pow (((a[0] + a[1] + a[2]) / 2), 2)
                            - curveVector[i] * ((4 * a[0] * a[2]) * (1 - curveVector[i]) + a[1] * (a[0] + a[2])));
                            
            curveVector[i] = 10 * log10 (std::abs(curveVector[i]));
            
        }
    }
}

// ==========================================================================================

void BiquadFilter::filterSignalMono (float* audioData)
{

	if (Active)
	{
		x[0] = *audioData;

		// Filter Transfer Function - Direct Method 1
		y[0] = (x[0] * b[0]) + (x[1] * b[1]) + (x[2] * b[2]) - (a[1] * y[1]) - (a[2] * y[2]);
		
		// Output Data
		*audioData = y[0];

		// Delay Trail
		// Do not Change Order
		x[2] = x[1];
		x[1] = x[0];

		y[2] = y[1];
		y[1] = y[0];
    }
    else
    {	
		// Data passes intact
		x[0] = *audioData;
		*audioData = x[0];
		// Keep in memory older input values
		// Same Delay Trail - Do not change order
		x[2] = x[1];
		x[1] = x[0];

		y[0] = 0;
		y[2] = y[1];
		y[1] = y[0];
    }
}

void BiquadFilter::filterSignalStereo (float* audioDataL, float* audioDataR)
{

	if (Active)
	{
	    // Left Channel
	    
		x[0] = *audioDataL;

		// Filter Transfer Function - Direct Method 1
		y[0] = (x[0] * b[0]) + (x[1] * b[1]) + (x[2] * b[2]) - (a[1] * y[1]) - (a[2] * y[2]);
		
		// Output Data
		*audioDataL = y[0];

		// Delay Trail
		// Do not Change Order
		x[2] = x[1];
		x[1] = x[0];

		y[2] = y[1];
		y[1] = y[0];
		
		// Right Channel
	    
		xR[0] = *audioDataR;

		// Filter Transfer Function - Direct Method 1
		yR[0] = (xR[0] * b[0]) + (xR[1] * b[1]) + (xR[2] * b[2]) - (a[1] * yR[1]) - (a[2] * yR[2]);
		
		// Output Data
		*audioDataR = yR[0];

		// Delay Trail
		// Do not Change Order
		xR[2] = xR[1];
		xR[1] = xR[0];

		yR[2] = yR[1];
		yR[1] = yR[0];
    }
    else
    {	
        // Left Channel
		// Data passes intact
		x[0] = *audioDataL;
		*audioDataL = x[0];
		// Keep in memory older input values
		// Same Delay Trail - Do not change order
		x[2] = x[1];
		x[1] = x[0];

		y[0] = 0;
		y[2] = y[1];
		y[1] = y[0];
		
		// Right Channel
		// Data passes intact
		x[0] = *audioDataR;
		*audioDataR = x[0];
		// Keep in memory older input values
		// Same Delay Trail - Do not change order
		xR[2] = xR[1];
		xR[1] = xR[0];

		yR[0] = 0;
		yR[2] = yR[1];
		yR[1] = yR[0];
    }
}
