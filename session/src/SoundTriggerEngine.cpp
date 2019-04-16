/*
 * Copyright (c) 2019, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of The Linux Foundation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define LOG_TAG "SoundTriggerEngine"

#include "SoundTriggerEngine.h"
#include "SoundTriggerEngineGsl.h"
#include "Session.h"
#include "Stream.h"

SoundTriggerEngine* SoundTriggerEngine::create(Stream *s, uint32_t id, uint32_t stage_id, QalRingBufferReader **reader, std::shared_ptr<QalRingBuffer> buffer)
{
    SoundTriggerEngine *stEngine = NULL;

    if (!s)
    {
        QAL_ERR(LOG_TAG,"%s: Invalid stream handle", __func__);
        goto exit;
    }
    // TODO: decide which engine should be used by checking sound
    // model params, existing engines can be found by querying RM
    stEngine = new SoundTriggerEngineGsl(s, id, stage_id, reader, buffer);

    // TODO: register engine to RM if it is newly created
exit:
    if (!stEngine)
    {
        QAL_ERR(LOG_TAG,"%s: SoundTriggerEngine creation failed", __func__);
    }
    else
    {
        QAL_VERBOSE(LOG_TAG,"%s: SoundTriggerEngine creation success", __func__);
    }

    return stEngine;
}

