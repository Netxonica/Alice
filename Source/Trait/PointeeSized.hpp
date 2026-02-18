// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_pointee_sized
#define alice_header_guard_trait_pointee_sized
#include "Trait/Pointer.hpp"
#include "Trait/Function.hpp"
#include "Meta/RemovePointer.hpp"

namespace Alice::Trait
{
    template<class Self> concept PointeeSized = Pointer<Self> and not Function<Meta::RemovePointer<
    Self>> and requires(Meta::RemovePointer<Self> pointee)
    {
        sizeof(pointee);
    };
}

#endif
#endif