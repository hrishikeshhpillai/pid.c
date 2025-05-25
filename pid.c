#include <stdio.h>
#include <stdint.h>


float runPid(sPid_t *pidInstance, uint16_t measuredValue);
float clampPidOut(float pidOut, float clampMin, float clampMax);

typedef struct pid{
    float setPoint;
    float kp;
    float kd;
    float ki;
    float prevError;
    float integralError;
    float diffError;
    float clampMax;
    float clampMin;
}sPid_t;


float runPid(sPid_t *pidInstance, uint16_t measuredValue)
{
    float error = pidInstance->setPoint - measuredValue;
    pidInstance->integralError+=error;
    pidInstance->diffError = error - pidInstance->prevError;
    pidInstance->prevError = error;
    float pidOut = pidInstance->kp*error + pidInstance->ki*pidInstance->integralError + pidInstance->kd*pidInstance->diffError;
    pidOut = clampPidOut(pidOut, pidInstance->clampMin, pidInstance->clampMax);
    return pidOut;
}


float clampPidOut(float pidOut, float clampMin, float clampMax)
{
    float clampedOut = pidOut;
    if(pidOut < clampMin)
    {
        clampedOut = clampMin;
    }
    else if(pidOut > clampMax)
    {
        clampedOut = clampMax;
    }
    return clampedOut;
}