/*!
 *****************************************************************************
 *
 * @File       secure_defs.h
 * @Title      Secure Definitions
 * @Description    This file contains the definition required for using a secure API
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

#if !defined (__SECURE_DEFS_H__)
#define __SECURE_DEFS_H__

#if defined(__cplusplus)
extern "C" {
#endif

typedef enum _MEM_REGIONS_
{
    // Register spaces.
    REGION_VXDSYS_REGSPACE = 0,
    REGION_VXDMTX_REGSPACE,
    REGION_VEC_REGSPACE,
    REGION_DMAC_REGSPACE,
    REGION_VDMC_REGSPACE,
    REGION_VDEB_REGSPACE,
    REGION_VLR_REGSPACE,
    REGION_VLRFE_REGSPACE,          //!< Vec Local Ram register space (FE Context).
    REGION_VLRBE_REGSPACE,          //!< Vec Local Ram register space (BE Context).
    REGION_VXDTEST_REGSPACE,
    REGION_VXDTEST_3_REGSPACE,
    REGION_VXDPINTEST_REGSPACE,

    // Memory spaces.
    REGION_VXDSYS_MEMSPACE,         //!< VXD system memory space.
    REGION_VXDMTX_MEMSPACE,

    REGION_REGSPACE,
    /*
    REGION_VXECOREREGS
    REGION_VXEMTX_REGSPACE
    */

    REGION_MAX,
} MEM_REGIONS;

typedef enum _IMG_CORE_
{
	VXD_CORE0=0x01,
	VXD_CORE1=0x02,
	BITSTREAM_SCAN=0x4,
	VXE0=0x08,
	FELIX=0x10,

    SECURE_CORE_MAX

}IMG_VIDEO_CORE;

typedef enum _MSG_ENDPOINT_
{
	ENDPOINT_VXD_INPUT=0,

	ENDPOINT_BSPP_STREAM_CREATE,
	ENDPOINT_BSPP_STREAM_DESTROY,
	ENDPOINT_BSPP_SUBMIT_PICTURE_DECODED,
	ENDPOINT_BSPP_STREAM_SUBMIT_BUFFER,
	ENDPOINT_BSPP_STREAM_PREPARSE_BUFFERS,

    ENDPOINT_VXD_INITIALISE,
    ENDPOINT_VXD_DEINITIALISE,
    ENDPOINT_VXD_RESET,
    ENDPOINT_VXD_HANDLE_INTERRUPTS,
    ENDPOINT_VXD_GET_STATE,
	ENDPOINT_VXD_PREPARE_FIRMWARE,
	ENDPOINT_VXD_LOAD_CORE_FW,
	ENDPOINT_VXD_READN_REGS,

}MSG_ENDPOINT;

#if defined(__cplusplus)
}
#endif

#endif /* __SECURE_DEFS_H__ */
