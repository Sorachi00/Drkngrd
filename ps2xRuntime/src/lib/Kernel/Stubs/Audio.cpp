#include "Common.h"
#include "Audio.h"
#include "runtime/ps2_audio_engine.h"

namespace ps2_stubs
{
    void resetAudioStubState()
    {
    }

    void sceSdCallBack(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSdCallBack", rdram, ctx, runtime);
    }

    void sceSdRemote(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {

        (void)rdram;
        (void)runtime;
        const uint32_t command = getRegU32(ctx, 5);
        uint32_t args[5];
        for (uint32_t i = 0; i < 5u; ++i)
            args[i] = getRegU32(ctx, 6u + i);
        const uint32_t result = PS2AudioEngine::instance().sdrCommand(command, args, 5u);
        PS2_IF_AGRESSIVE_LOGS({
            std::cerr << "[Audio:sceSdRemote] cmd=0x" << std::hex << command
                      << " a=" << args[0] << "," << args[1] << "," << args[2]
                      << "," << args[3] << "," << args[4]
                      << " -> 0x" << result << std::dec << std::endl;
        });
        setReturnU32(ctx, result);
    }

    void sceSdRemoteInit(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        (void)rdram;
        (void)runtime;
        setReturnS32(ctx, 0);
    }

    void sceSdTransToIOP(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSdTransToIOP", rdram, ctx, runtime);
    }

    void sceSSyn_BreakAtick(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSSyn_BreakAtick", rdram, ctx, runtime);
    }

    void sceSSyn_ClearBreakAtick(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSSyn_ClearBreakAtick", rdram, ctx, runtime);
    }

    void sceSSyn_SendExcMsg(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSSyn_SendExcMsg", rdram, ctx, runtime);
    }

    void sceSSyn_SendNrpnMsg(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSSyn_SendNrpnMsg", rdram, ctx, runtime);
    }

    void sceSSyn_SendRpnMsg(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSSyn_SendRpnMsg", rdram, ctx, runtime);
    }

    void sceSSyn_SendShortMsg(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSSyn_SendShortMsg", rdram, ctx, runtime);
    }

    void sceSSyn_SetChPriority(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSSyn_SetChPriority", rdram, ctx, runtime);
    }

    void sceSSyn_SetMasterVolume(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSSyn_SetMasterVolume", rdram, ctx, runtime);
    }

    void sceSSyn_SetOutPortVolume(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSSyn_SetOutPortVolume", rdram, ctx, runtime);
    }

    void sceSSyn_SetOutputAssign(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSSyn_SetOutputAssign", rdram, ctx, runtime);
    }

    void sceSSyn_SetOutputMode(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        setReturnS32(ctx, 0);
    }

    void sceSSyn_SetPortMaxPoly(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSSyn_SetPortMaxPoly", rdram, ctx, runtime);
    }

    void sceSSyn_SetPortVolume(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSSyn_SetPortVolume", rdram, ctx, runtime);
    }

    void sceSSyn_SetTvaEnvMode(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSSyn_SetTvaEnvMode", rdram, ctx, runtime);
    }

    void sceSynthesizerAmpProcI(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerAmpProcI", rdram, ctx, runtime);
    }

    void sceSynthesizerAmpProcNI(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerAmpProcNI", rdram, ctx, runtime);
    }

    void sceSynthesizerAssignAllNoteOff(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerAssignAllNoteOff", rdram, ctx, runtime);
    }

    void sceSynthesizerAssignAllSoundOff(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerAssignAllSoundOff", rdram, ctx, runtime);
    }

    void sceSynthesizerAssignHoldChange(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerAssignHoldChange", rdram, ctx, runtime);
    }

    void sceSynthesizerAssignNoteOff(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerAssignNoteOff", rdram, ctx, runtime);
    }

    void sceSynthesizerAssignNoteOn(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerAssignNoteOn", rdram, ctx, runtime);
    }

    void sceSynthesizerCalcEnv(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerCalcEnv", rdram, ctx, runtime);
    }

    void sceSynthesizerCalcPortamentPitch(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerCalcPortamentPitch", rdram, ctx, runtime);
    }

    void sceSynthesizerCalcTvfCoefAll(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerCalcTvfCoefAll", rdram, ctx, runtime);
    }

    void sceSynthesizerCalcTvfCoefF0(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerCalcTvfCoefF0", rdram, ctx, runtime);
    }

    void sceSynthesizerCent2PhaseInc(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerCent2PhaseInc", rdram, ctx, runtime);
    }

    void sceSynthesizerChangeEffectSend(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerChangeEffectSend", rdram, ctx, runtime);
    }

    void sceSynthesizerChangeHsPanpot(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerChangeHsPanpot", rdram, ctx, runtime);
    }

    void sceSynthesizerChangeNrpnCutOff(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerChangeNrpnCutOff", rdram, ctx, runtime);
    }

    void sceSynthesizerChangeNrpnLfoDepth(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerChangeNrpnLfoDepth", rdram, ctx, runtime);
    }

    void sceSynthesizerChangeNrpnLfoRate(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerChangeNrpnLfoRate", rdram, ctx, runtime);
    }

    void sceSynthesizerChangeOutAttrib(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerChangeOutAttrib", rdram, ctx, runtime);
    }

    void sceSynthesizerChangeOutVol(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerChangeOutVol", rdram, ctx, runtime);
    }

    void sceSynthesizerChangePanpot(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerChangePanpot", rdram, ctx, runtime);
    }

    void sceSynthesizerChangePartBendSens(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerChangePartBendSens", rdram, ctx, runtime);
    }

    void sceSynthesizerChangePartExpression(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerChangePartExpression", rdram, ctx, runtime);
    }

    void sceSynthesizerChangePartHsExpression(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerChangePartHsExpression", rdram, ctx, runtime);
    }

    void sceSynthesizerChangePartHsPitchBend(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerChangePartHsPitchBend", rdram, ctx, runtime);
    }

    void sceSynthesizerChangePartModuration(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerChangePartModuration", rdram, ctx, runtime);
    }

    void sceSynthesizerChangePartPitchBend(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerChangePartPitchBend", rdram, ctx, runtime);
    }

    void sceSynthesizerChangePartVolume(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerChangePartVolume", rdram, ctx, runtime);
    }

    void sceSynthesizerChangePortamento(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerChangePortamento", rdram, ctx, runtime);
    }

    void sceSynthesizerChangePortamentoTime(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerChangePortamentoTime", rdram, ctx, runtime);
    }

    void sceSynthesizerClearKeyMap(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerClearKeyMap", rdram, ctx, runtime);
    }

    void sceSynthesizerClearSpr(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerClearSpr", rdram, ctx, runtime);
    }

    void sceSynthesizerCopyOutput(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerCopyOutput", rdram, ctx, runtime);
    }

    void sceSynthesizerDmaFromSPR(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerDmaFromSPR", rdram, ctx, runtime);
    }

    void sceSynthesizerDmaSpr(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerDmaSpr", rdram, ctx, runtime);
    }

    void sceSynthesizerDmaToSPR(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerDmaToSPR", rdram, ctx, runtime);
    }

    void sceSynthesizerGetPartial(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerGetPartial", rdram, ctx, runtime);
    }

    void sceSynthesizerGetPartOutLevel(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerGetPartOutLevel", rdram, ctx, runtime);
    }

    void sceSynthesizerGetSampleParam(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerGetSampleParam", rdram, ctx, runtime);
    }

    void sceSynthesizerHsMessage(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerHsMessage", rdram, ctx, runtime);
    }

    void sceSynthesizerLfoNone(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerLfoNone", rdram, ctx, runtime);
    }

    void sceSynthesizerLfoProc(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerLfoProc", rdram, ctx, runtime);
    }

    void sceSynthesizerLfoSawDown(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerLfoSawDown", rdram, ctx, runtime);
    }

    void sceSynthesizerLfoSawUp(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerLfoSawUp", rdram, ctx, runtime);
    }

    void sceSynthesizerLfoSquare(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerLfoSquare", rdram, ctx, runtime);
    }

    void sceSynthesizerReadNoise(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerReadNoise", rdram, ctx, runtime);
    }

    void sceSynthesizerReadNoiseAdd(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerReadNoiseAdd", rdram, ctx, runtime);
    }

    void sceSynthesizerReadSample16(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerReadSample16", rdram, ctx, runtime);
    }

    void sceSynthesizerReadSample16Add(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerReadSample16Add", rdram, ctx, runtime);
    }

    void sceSynthesizerReadSample8(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerReadSample8", rdram, ctx, runtime);
    }

    void sceSynthesizerReadSample8Add(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerReadSample8Add", rdram, ctx, runtime);
    }

    void sceSynthesizerResetPart(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerResetPart", rdram, ctx, runtime);
    }

    void sceSynthesizerRestorDma(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerRestorDma", rdram, ctx, runtime);
    }

    void sceSynthesizerSelectPatch(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerSelectPatch", rdram, ctx, runtime);
    }

    void sceSynthesizerSendShortMessage(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerSendShortMessage", rdram, ctx, runtime);
    }

    void sceSynthesizerSetMasterVolume(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerSetMasterVolume", rdram, ctx, runtime);
    }

    void sceSynthesizerSetRVoice(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerSetRVoice", rdram, ctx, runtime);
    }

    void sceSynthesizerSetupDma(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerSetupDma", rdram, ctx, runtime);
    }

    void sceSynthesizerSetupLfo(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerSetupLfo", rdram, ctx, runtime);
    }

    void sceSynthesizerSetupMidiModuration(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerSetupMidiModuration", rdram, ctx, runtime);
    }

    void sceSynthesizerSetupMidiPanpot(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerSetupMidiPanpot", rdram, ctx, runtime);
    }

    void sceSynthesizerSetupNewNoise(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerSetupNewNoise", rdram, ctx, runtime);
    }

    void sceSynthesizerSetupReleaseEnv(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerSetupReleaseEnv", rdram, ctx, runtime);
    }

    void sceSynthesizerSetuptEnv(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerSetuptEnv", rdram, ctx, runtime);
    }

    void sceSynthesizerSetupTruncateTvaEnv(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerSetupTruncateTvaEnv", rdram, ctx, runtime);
    }

    void sceSynthesizerSetupTruncateTvfPitchEnv(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerSetupTruncateTvfPitchEnv", rdram, ctx, runtime);
    }

    void sceSynthesizerTonegenerator(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerTonegenerator", rdram, ctx, runtime);
    }

    void sceSynthesizerTransposeMatrix(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerTransposeMatrix", rdram, ctx, runtime);
    }

    void sceSynthesizerTvfProcI(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerTvfProcI", rdram, ctx, runtime);
    }

    void sceSynthesizerTvfProcNI(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerTvfProcNI", rdram, ctx, runtime);
    }

    void sceSynthesizerWaitDmaFromSPR(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerWaitDmaFromSPR", rdram, ctx, runtime);
    }

    void sceSynthesizerWaitDmaToSPR(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthesizerWaitDmaToSPR", rdram, ctx, runtime);
    }

    void sceSynthsizerGetDrumPatch(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthsizerGetDrumPatch", rdram, ctx, runtime);
    }

    void sceSynthsizerGetMeloPatch(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthsizerGetMeloPatch", rdram, ctx, runtime);
    }

    void sceSynthsizerLfoNoise(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthsizerLfoNoise", rdram, ctx, runtime);
    }

    void sceSynthSizerLfoTriangle(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceSynthSizerLfoTriangle", rdram, ctx, runtime);
    }
}
