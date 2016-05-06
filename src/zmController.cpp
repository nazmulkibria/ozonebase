#include "zm.h"
#include "zmController.h"

#include "zmFeedProvider.h"

void Controller::addStream( const std::string &streamName, const std::string &streamClass )
{
    Info( "Adding stream %s with class %s", streamName.c_str(), streamClass.c_str() );
    std::pair<ApplicationClassMap::iterator,bool> result = mApplicationClasses.insert( ApplicationClassMap::value_type( streamName, streamClass ) );
    if ( !result.second )
        Fatal( "Unable to add stream %s with class %s", streamName.c_str(), streamClass.c_str() );
}

void Controller::addStream( const std::string &streamName, FeedProvider &streamProvider )
{
    const std::string streamPath = makePath( streamName, streamProvider.name() );
    Info( "Adding stream %s with provider %s (%s)", streamName.c_str(), streamProvider.cidentity(), streamPath.c_str() );
    std::pair<ApplicationInstanceMap::iterator,bool> result = mApplicationInstances.insert( ApplicationInstanceMap::value_type( streamPath, &streamProvider ) );
    if ( !result.second )
        Fatal( "Unable to add stream %s with provider %s", streamPath.c_str(), streamProvider.cidentity() );
}

void Controller::removeStream( const std::string &streamTag )
{
    Info( "Removing stream %s", streamTag.c_str() );
    bool result = ( mApplicationClasses.erase( streamTag ) == 1 );
    if ( result )
        return;
    result = ( mApplicationInstances.erase( streamTag ) == 1 );
        if ( result )
            return;
    Fatal( "Unable to remove stream %s", streamTag.c_str() );
}

// Check if stream name exists, does not check instances so if any exists err on the positive side
bool Controller::verifyStreamName( const std::string &streamName )
{
    Info( "Verifying stream %s", streamName.c_str() );
    ApplicationClassMap::iterator instanceIter = mApplicationClasses.find( streamName );
    if ( instanceIter != mApplicationClasses.end() )
        return( true );
    return( mApplicationInstances.empty() ? false : true );
}

FeedProvider *Controller::findStream( const std::string &streamName, const std::string &streamSource )
{
    Info( "Find stream %s with source %s", streamName.c_str(), streamSource.c_str() );
    ApplicationInstanceMap::iterator classIter = mApplicationInstances.find( makePath( streamName, streamSource ) );
    if ( classIter != mApplicationInstances.end() )
        return( classIter->second );
    ApplicationClassMap::iterator instanceIter = mApplicationClasses.find( streamName );
    if ( instanceIter != mApplicationClasses.end() )
    {
        std::string feedId = FeedProvider::makeIdentity( instanceIter->second, streamSource );
        Info( "Looking for feed %s", feedId.c_str() );
        return( FeedProvider::find( feedId ) );
    }
    Info( "Failed" );
    return( NULL );
}
