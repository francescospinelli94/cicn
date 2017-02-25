/*
 * SegmentListStream.cpp
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "SegmentListStream.h"

using namespace dash::mpd;
using namespace libdash::framework::mpd;

SegmentListStream::SegmentListStream(IMPD *mpd, IPeriod *period, IAdaptationSet *adaptationSet, IRepresentation *representation) :
                   AbstractRepresentationStream (mpd, period, adaptationSet, representation)
{
    this->baseUrls      = BaseUrlResolver::resolveBaseUrl(mpd, period, adaptationSet, 0, 0, 0);
    this->segmentList   = findSegmentList();
}

SegmentListStream::~SegmentListStream()
{
}

ISegment* SegmentListStream::getInitializationSegment()
{
    if (this->segmentList->GetInitialization())
        return this->segmentList->GetInitialization()->ToSegment(this->baseUrls);

    return NULL;
}

ISegment* SegmentListStream::getIndexSegment(size_t segmentNumber)
{
    if (this->segmentList->GetSegmentURLs().size() > segmentNumber)
        return this->segmentList->GetSegmentURLs().at(segmentNumber)->ToIndexSegment(this->baseUrls);

    return NULL;
}

ISegment* SegmentListStream::getMediaSegment(size_t segmentNumber)
{
    if (this->segmentList->GetSegmentURLs().size() > segmentNumber)
        return this->segmentList->GetSegmentURLs().at(segmentNumber)->ToMediaSegment(this->baseUrls);

    return NULL;
}

ISegment* SegmentListStream::getBitstreamSwitchingSegment ()
{
    if (this->segmentList->GetBitstreamSwitching())
        return this->segmentList->GetBitstreamSwitching()->ToSegment(baseUrls);

    return NULL;
}

RepresentationStreamType SegmentListStream::getStreamType()
{
    return SegmentList;
}

uint32_t SegmentListStream::getSize()
{
    return this->segmentList->GetSegmentURLs().size();
}

ISegmentList* SegmentListStream::findSegmentList()
{
    if (this->representation->GetSegmentList())
        return this->representation->GetSegmentList();

    if (this->adaptationSet->GetSegmentList())
        return this->adaptationSet->GetSegmentList();

    if (this->period->GetSegmentList())
        return this->period->GetSegmentList();

    return NULL;
}

uint32_t SegmentListStream::getAverageSegmentDuration()
{
    /* TODO calculate average segment durations for SegmentTimeline */
    return this->segmentList->GetDuration();
}
