#pragma once
// Sociedade de Tristram — motor de deducao narrativa independente.
// Sem alocacao dinamica, RNG, I/O, flags globais ou acesso a saves.
// Integracao ao jogo SOMENTE depois de inventario de IDs e persistencia.
#include <stdint.h>

namespace VesperaLore {

enum Evidence : uint16_t {
    LeafScraped       = 1u << 0, // L01
    CaravanLedger     = 1u << 1, // L02
    GillianBinding    = 1u << 2, // L03
    PrayersCompared   = 1u << 3, // L04
    WaxSeal           = 1u << 4, // L05
    OrenNote          = 1u << 5, // L06
    DeathRegister     = 1u << 6  // L07
};

enum Conclusion : uint8_t {
    NoConclusion = 0,
    TextAltered = 1u << 0,
    ForgeryProven = 1u << 1,
    SeparateIntermediaries = 1u << 2
};

enum Ending : uint8_t {
    Undecided = 0,
    CainCustody = 1,
    PublicExposure = 2,
    DestroyRecord = 3
};

struct State {
    uint16_t evidence;
    uint8_t ending;
    State() : evidence(0), ending(Undecided) {}
};

// Evidence is monotonic and order-independent. Unknown bits are discarded.
static inline uint16_t KnownEvidenceMask() {
    return LeafScraped | CaravanLedger | GillianBinding |
           PrayersCompared | WaxSeal | OrenNote | DeathRegister;
}

static inline bool RecordEvidence(State& state, uint16_t evidence) {
    if (state.ending != Undecided) return false;
    const uint16_t next = static_cast<uint16_t>(
        state.evidence | (evidence & KnownEvidenceMask()));
    if (next == state.evidence) return false;
    state.evidence = next;
    return true;
}

static inline uint8_t Deduce(const State& state) {
    const uint16_t e = state.evidence & KnownEvidenceMask();
    uint8_t result = NoConclusion;
    if (e & LeafScraped) result |= TextAltered;
    if ((e & LeafScraped) && (e & (PrayersCompared | OrenNote)) &&
        (e & DeathRegister)) result |= ForgeryProven;
    if ((e & WaxSeal) && (e & (CaravanLedger | GillianBinding)))
        result |= SeparateIntermediaries;
    return result;
}

static inline bool ChooseEnding(State& state, Ending ending) {
    if (state.ending != Undecided) return false;
    if (ending < CainCustody || ending > DestroyRecord) return false;
    // The basic conclusion is needed to close the investigation.
    if (!(Deduce(state) & ForgeryProven)) return false;
    state.ending = static_cast<uint8_t>(ending);
    return true;
}

// Wire format is explicit, independent of C++ padding; caller owns persistence.
static inline void Encode(const State& state, uint8_t out[3]) {
    const uint16_t evidence = state.evidence & KnownEvidenceMask();
    out[0] = static_cast<uint8_t>(evidence & 0xffu);
    out[1] = static_cast<uint8_t>(evidence >> 8);
    out[2] = state.ending <= DestroyRecord ? state.ending : Undecided;
}

static inline bool Decode(State& state, const uint8_t in[3]) {
    const uint16_t evidence = static_cast<uint16_t>(in[0] | (uint16_t(in[1]) << 8));
    if ((evidence & ~KnownEvidenceMask()) != 0 || in[2] > DestroyRecord)
        return false;
    State candidate;
    candidate.evidence = evidence;
    candidate.ending = in[2];
    if (candidate.ending != Undecided &&
        !(Deduce(candidate) & ForgeryProven)) return false;
    state = candidate;
    return true;
}

} // namespace VesperaLore
