/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2011 Advanced Micro Devices, Inc.  http://bulletphysics.org

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

///original author: Erwin Coumans

#include "btOpenCLUtils.h"
#include <stdio.h>

cl_context			g_cxMainContext;
cl_command_queue	g_cqCommandQue;



int main(int argc, char* argv[])
{
	int ciErrNum = 0;
	cl_device_type deviceType = CL_DEVICE_TYPE_ALL;//GPU;
	void* glCtx=0;
	void* glDC = 0;
	g_cxMainContext = btOpenCLUtils::createContextFromType(deviceType, &ciErrNum, glCtx, glDC);
	oclCHECKERROR(ciErrNum, CL_SUCCESS);

	int numDev = btOpenCLUtils::getNumDevices(g_cxMainContext);

	for (int i=0;i<numDev;i++)
	{
		cl_device_id		device;
		device = btOpenCLUtils::getDevice(g_cxMainContext,i);
		btOpenCLDeviceInfo clInfo;
		btOpenCLUtils::getDeviceInfo(device,clInfo);
		btOpenCLUtils::printDeviceInfo(device);
		// create a command-queue
		g_cqCommandQue = clCreateCommandQueue(g_cxMainContext, device, 0, &ciErrNum);
		oclCHECKERROR(ciErrNum, CL_SUCCESS);
		//normally you would create and execute kernels using this command queue

		clReleaseCommandQueue(g_cqCommandQue);
	}

	clReleaseContext(g_cxMainContext);
	return 0;
}