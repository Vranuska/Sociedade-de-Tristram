#include "stdafx.h"
#include "../include/Diagnostics.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>

namespace {
    enum { CAPACITY = 128, TEXT_SIZE = 240 };
    struct Entry {
        DWORD tick;
        DWORD thread;
        char category[32];
        char message[TEXT_SIZE];
    };
    Entry entries[CAPACITY] = {};
    volatile LONG sequence = 0;
    volatile LONG writer = 0;
    void Copy(char* dest, size_t capacity, const char* src) {
        if (!src) src = "(null)";
        strncpy_s(dest, capacity, src, _TRUNCATE);
    }
}

void Diagnostics::Record(const char* category, const char* message) {
    // Nonblocking: diagnostics must never stall the game or recurse.
    if (InterlockedCompareExchange(&writer, 1, 0) != 0) return;
    const LONG index = InterlockedIncrement(&sequence) - 1;
    Entry& e = entries[static_cast<unsigned long>(index) % CAPACITY];
    e.tick = GetTickCount();
    e.thread = GetCurrentThreadId();
    Copy(e.category, sizeof(e.category), category);
    Copy(e.message, sizeof(e.message), message);
    InterlockedExchange(&writer, 0);
}

void Diagnostics::RecordFile(const char* operation, const char* path) {
    char line[TEXT_SIZE];
    _snprintf_s(line, sizeof(line), _TRUNCATE, "%s: %s",
        operation ? operation : "file", path ? path : "(null)");
    Record("RESOURCE", line);
}

void Diagnostics::Snapshot() {
    // Only call outside an exception handler; disk IO is not crash-safe.
    if (InterlockedCompareExchange(&writer, 1, 0) != 0) return;
    CreateDirectoryA("Diagnostics", NULL);
    FILE* file = NULL;
    if (fopen_s(&file, "Diagnostics\\Session.log", "w") == 0 && file) {
        const LONG end = sequence;
        const LONG start = end > CAPACITY ? end - CAPACITY : 0;
        fprintf(file, "Sociedade de Tristram - diagnostic events\n");
        for (LONG i = start; i < end; ++i) {
            const Entry& e = entries[static_cast<unsigned long>(i) % CAPACITY];
            fprintf(file, "[%lu] [thread %lu] [%s] %s\n",
                static_cast<unsigned long>(e.tick),
                static_cast<unsigned long>(e.thread), e.category, e.message);
        }
        fclose(file);
    }
    InterlockedExchange(&writer, 0);
}
