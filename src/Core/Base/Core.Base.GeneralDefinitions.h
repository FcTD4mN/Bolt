#pragma once

#include "Core.Base.Utilities.h"


namespace nCore {
namespace nBase {


typedef     size_t  tHash;


enum eFormat
{
    kTop    = 1 << 0,
    kBottom = 1 << 1,
    kLeft   = 1 << 2,
    kRight  = 1 << 3,
    kCenter = 1 << 4,
};


enum  eDirection
{
    kHorizontal = 0,
    kVertical
};


} // namespace nBase
} // namespace nCore

