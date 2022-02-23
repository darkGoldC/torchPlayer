#pragma once
#include "ITPDecoder.h"
#include "TP_CoreDefine.h"

class TPCORESHARED_EXPORT TPDecoder : public ITPDecoder
{
public:

protected:
    es_format_t     InFormat;
    es_format_t     outFormat;
    //允许是否掉帧
    bool            bFrameDropAllowed;
};

