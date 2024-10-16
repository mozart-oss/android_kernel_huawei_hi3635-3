/*!
 *****************************************************************************
 *
 * @File       securemem.h
 * @Title      Memory interface component
 * @Description    This file contains the SecureMedia interface to MEM
 * ---------------------------------------------------------------------------
 *
 * Copyright (c) Imagination Technologies Ltd.
 * 
 * The contents of this file are subject to the MIT license as set out below.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 * 
 * Alternatively, the contents of this file may be used under the terms of the 
 * GNU General Public License Version 2 ("GPL")in which case the provisions of
 * GPL are applicable instead of those above. 
 * 
 * If you wish to allow use of your version of this file only under the terms 
 * of GPL, and not to allow others to use your version of this file under the 
 * terms of the MIT license, indicate your decision by deleting the provisions 
 * above and replace them with the notice and other provisions required by GPL 
 * as set out in the file called "GPLHEADER" included in this distribution. If 
 * you do not delete the provisions above, a recipient may use your version of 
 * this file under the terms of either the MIT license or GPL.
 * 
 * This License is also included in this distribution in the file called 
 * "MIT_COPYING".
 *
 *****************************************************************************/

#if !defined (__SECUREMEM_H__)
#define __SECUREMEM_H__

#if defined(__cplusplus)
extern "C" {
#endif

#include <img_include.h>

/*!
******************************************************************************

 @Function              SECMEM_MemoryCpuToDevice

 @Description

 Updates device memory from CPU.
 
 @Input     isSecure      : TRUE if memory is secure (i.e. ui32Id is valid)
 @Input     ui32Id        : Id of secure memory to be updated
  
 @Return    This function returns either IMG_SUCCESS or an
                              error code.

******************************************************************************/
IMG_RESULT
SECMEM_MemoryCpuToDevice(
    IMG_BOOL        isSecure,
    IMG_PHYSADDR    paPhysAddr
);


/*!
******************************************************************************

 @Function              SECMEM_MemoryDeviceToCpu

 @Description

 Updates CPU memory from device.

 @Input     isSecure      : TRUE if memory is secure (i.e. ui32Id is valid)
 @Input     ui32Id        : Id of secure memory to be updated
  
 @Return    This function returns either IMG_SUCCESS or an
                              error code.

******************************************************************************/
IMG_RESULT
SECMEM_MemoryDeviceToCpu(
    IMG_BOOL        isSecure,
    IMG_PHYSADDR    paPhysAddr
);


/*!
******************************************************************************

 @Function              SECMEM_MapSecureDeviceMemory

 @Description

 Maps secure device memory into the TEE.
 
 NOTE: This function assumes that physical memory is contiguous therefore 
 the page size of the allocation is not required to remap.

 @Input     ui32Id        : Id of secure memory to be mapped.

 @Output    ppvCpuVirt    : Pointer to TEE virtual address pointer.
 
 @Return    This function returns either IMG_SUCCESS or an
                              error code.

******************************************************************************/
IMG_RESULT 
SECMEM_MapSecureMemory(
    IMG_PHYSADDR    paPhysAddr,
    IMG_UINT32      ui32Size,
    IMG_VOID     ** ppvCpuVirt
);

IMG_VOID
SECMEM_UnmapSecureMemory(
    IMG_VOID     * ppvCpuVirt
);


#if defined(__cplusplus)
}
#endif

#endif /* __SECUREMEM_H__ */
