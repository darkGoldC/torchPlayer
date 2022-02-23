#ifndef ITPDecoder_H
#define ITPDecoder_H
#include <iostream>
#include "ITPEs_out.h"
#include "BlockData.h"

class ITPDecoder
{
public:
    virtual bool        init() = 0;
    virtual int         decode(Block_t *p_block) = 0;
};

#endif
