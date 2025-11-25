// Diagnostics for double-free behavior
// SPDX-License-Identifier: MIT

#include <compartment.h>
#include <debug.hh>
#include <unwind.h>
#include <fail-simulator-on-error.h>

using Debug = ConditionalDebug<true, "Double Compartment">;


__cheri_compartment("double-free") int vuln1(void)
{
    Debug::log("Testing Double Free...");

    int *ptr = (int*)malloc(sizeof(int));
    if (!ptr) { Debug::log( "malloc returned NULL"); return 0; }
    *ptr = 42;

    free(ptr);
    Debug::log("After first free");

    free(ptr);
    Debug::log("After second free");

    return 0;
}