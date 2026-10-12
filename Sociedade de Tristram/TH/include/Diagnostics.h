#pragma once

// Lightweight, allocation-free diagnostic event recorder.
// Designed to be callable before risky resource and map operations.
// Snapshot writes a bounded text report to Diagnostics/Session.log.
namespace Diagnostics {
    void Record(const char* category, const char* message);
    void RecordFile(const char* operation, const char* path);
    void Snapshot();
}
