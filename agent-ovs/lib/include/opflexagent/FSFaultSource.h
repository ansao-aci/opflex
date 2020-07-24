#pragma once
#ifndef OPFLEXAGENT_FSFAULTSOURCE_H
#define OPFLEXAGENT_FSFAULTSOURCE_H

#include <opflexagent/FSWatcher.h>
#include <opflexagent/FaultSource.h>
#include <opflexagent/Agent.h>
#include <boost/filesystem.hpp>
#include <string>
#include <unordered_map>

namespace opflexagent {

/**
 * A fault source that gets information about faults from JSON
 * files on the filesystem.  If supported, it will set an inotify
 * watch on the directory
 */

class Agent;

class FSFaultSource
    : public FaultSource, public FSWatcher::Watcher {
public:
   FSFaultSource(FaultManager* manager_,
                 FSWatcher& listener,
                 const std::string& faultSourceDir, Agent& agent_);

   virtual ~FSFaultSource() {}; 


   // See Watcher
   virtual void updated(const boost::filesystem::path& filePath);
   // See Watcher
   virtual void deleted(const boost::filesystem::path& filePath);
  
   string getFaultUUID (const string pathstr);

   Agent& agent;
   FaultManager* faultManager;
   typedef std::unordered_map<std::string, std::string> fault_map_t;
   fault_map_t knownFaults;
};
}

#endif /* OPFLEXAGENT_FSFAULTSOURCE_H */
