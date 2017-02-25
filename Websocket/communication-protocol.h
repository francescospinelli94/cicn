/*
 * Copyright (c) 2017 Cisco and/or its affiliates.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef COMMUNICATION_PROTOCOL_HPP
#define COMMUNICATION_PROTOCOL_HPP

#include <string>
#include <map>
#include <set>
#include "query.h"
#include "../UI/GraphDataSource.h"
#include "websocket-server.h"

enum ProtocolVersion
{
  CONTROL_PROTOCOL_V1 = 1,
  CONTROL_PROTOCOL_V2 = 2
};

typedef struct ProtocolDetails {
  static std::set<std::string> AllowedObjectName;
  static std::set<std::string> AllowedFields;
  static std::set<std::string> AllowedActions;
//  static std::list<std::string> AllowedParameters; // Per action
  static std::set<std::string> AllowedFilters;
  static std::set<std::string> AllowedOperands; // Per filter
} ProtocolDetails;

class CommunicationProtocol
{
public:
  CommunicationProtocol(ProtocolVersion version = ProtocolVersion::CONTROL_PROTOCOL_V1);

  bool
  checkFilter(const std::vector<std::string> &filter);

  bool
  checkFields(const std::string &field);

  bool
  checkObjectName(const std::string &objectName);

  bool
  checkParameters(const std::string &parameter);

  bool
  checkAction(const std::string &action);

  std::string
  evaluateFilters(const std::list<std::vector<std::string>> &filters);

  void
  processQuery(Server *s, websocketpp::connection_hdl hdl, message_ptr msg,
               Query query);

  Query
  makeReplyQuery(const Query &request);

  void
  setGraphDataSource(GraphDataSource *graphDataSource);

  static std::function<void(const boost::system::error_code&)> timerCallback;


private:
  GraphDataSource *graphDataSource;
  ProtocolVersion  version;

  std::shared_ptr<boost::asio::deadline_timer> subscribeTimer;
};


#endif //COMMUNICATION_PROTOCOL_HPP
