#ifndef ZM_MEMORY_INPUT_H
#define ZM_MEMORY_INPUT_H

#include "../zmFeedProvider.h"
#include "../zmMemoryIO.h"
#include "../libgen/libgenThread.h"

class Image;

///
/// Class representing video provider which access frames written to shared memory by
/// MemoryOutput class. Can be used reproduce traditional ZoneMinder zmc/zma relationship
/// and behaviour.
///
class MemoryInput : public VideoProvider, public MemoryIO, public Thread
{
CLASSID(MemoryInput);

protected:
    PixelFormat mImageFormat;
    uint16_t    mImageWidth;
    uint16_t    mImageHeight;

protected:
    int run();
    const FeedFrame *loadFrame();

public:
    MemoryInput( const std::string &name, const std::string &location, int memoryKey );
    ~MemoryInput();

public:
    PixelFormat pixelFormat() const { return( mImageFormat ); }
    uint16_t width() const { return( mImageWidth ); }
    uint16_t height() const { return( mImageHeight ); }
};

#endif // ZM_MEMORY_INPUT_H
