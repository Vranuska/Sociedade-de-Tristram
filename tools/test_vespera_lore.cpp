// Standalone regression test: g++ -std=c++11 -Wall -Wextra -pedantic
// -I "Sociedade de Tristram/TH/src" tools/test_vespera_lore.cpp -o vespera_lore_test
#include "../Sociedade de Tristram/TH/src/VesperaLoreQuest.h"
#include <cassert>
using namespace VesperaLore;

int main() {
    State s;
    assert(Deduce(s) == NoConclusion);
    assert(!ChooseEnding(s, CainCustody));
    assert(RecordEvidence(s, DeathRegister));
    assert(RecordEvidence(s, OrenNote));
    assert(!RecordEvidence(s, OrenNote)); // no double reward/event
    assert(RecordEvidence(s, LeafScraped)); // arbitrary order
    assert((Deduce(s) & ForgeryProven) != 0);
    assert((Deduce(s) & SeparateIntermediaries) == 0);
    assert(RecordEvidence(s, WaxSeal));
    assert(RecordEvidence(s, GillianBinding));
    assert((Deduce(s) & SeparateIntermediaries) != 0);
    assert(ChooseEnding(s, CainCustody));
    assert(!ChooseEnding(s, PublicExposure));
    assert(!RecordEvidence(s, CaravanLedger));
    uint8_t data[3];
    Encode(s, data);
    State restored;
    assert(Decode(restored, data));
    assert(restored.evidence == s.evidence);
    assert(restored.ending == CainCustody);
    const uint8_t invalid[3] = { 0xff, 0xff, 2 };
    assert(!Decode(restored, invalid));
    assert(restored.ending == CainCustody); // failed decode is atomic
    State alt;
    assert(RecordEvidence(alt, LeafScraped | PrayersCompared | DeathRegister));
    assert((Deduce(alt) & ForgeryProven) != 0);
    assert(ChooseEnding(alt, DestroyRecord));
    State noProof;
    assert(RecordEvidence(noProof, WaxSeal | CaravanLedger));
    assert((Deduce(noProof) & SeparateIntermediaries) != 0);
    assert(!ChooseEnding(noProof, CainCustody));
    return 0;
}
