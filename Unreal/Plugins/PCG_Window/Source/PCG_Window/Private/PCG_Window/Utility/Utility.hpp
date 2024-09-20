#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

template<typename Enum>
FString GetEnumAsString(Enum value)
{
    // Strip the namespace from the name.
    FString EnumNameString = UEnum::GetValueAsString(value);
    int32 ScopeIndex = EnumNameString.Find(TEXT("::"), ESearchCase::CaseSensitive);
    if (ScopeIndex != INDEX_NONE)
    {
        return EnumNameString.Mid(ScopeIndex + 2);
    }

    return FString();
}
