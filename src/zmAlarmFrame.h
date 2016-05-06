#ifndef ZM_ALARM_FRAME_H
#define ZM_ALARM_FRAME_H

#include "zmFeedFrame.h"

///
/// Specialised video frame that includes an indication of whether this frame is alarmed or not.
///
class AlarmFrame : public VideoFrame
{
protected:
    bool mAlarmed;      ///< Indicates whether this frame represents an alarmed frame.

public:
    AlarmFrame( VideoProvider *provider, uint64_t id, uint64_t timestamp, const ByteBuffer &buffer, bool alarmed ) :
        VideoFrame( provider, id, timestamp, buffer ),
        mAlarmed( alarmed )
    {
    }
    //AlarmFrame( VideoProvider *provider, uint64_t id, uint64_t timestamp, const uint8_t *buffer, size_t size );
    AlarmFrame( VideoProvider *provider, FramePtr parent, uint64_t id, uint64_t timestamp, const ByteBuffer &buffer, bool alarmed ) :
        VideoFrame( provider, parent, id, timestamp, buffer ),
        mAlarmed( alarmed )
    {
    }
    //AlarmFrame( VideoProvider *provider, FramePtr parent, uint64_t id, uint64_t timestamp, const uint8_t *buffer, size_t size );
    AlarmFrame( VideoProvider *provider, FramePtr parent, bool alarmed ) :
        VideoFrame( provider, parent ),
        mAlarmed( alarmed )
    {
    }

    bool alarmed() const { return( mAlarmed ); }
};

#endif // ZM_ALARM_FRAME_H
