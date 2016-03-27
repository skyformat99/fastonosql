/*  Copyright (C) 2014-2016 FastoGT. All right reserved.

    This file is part of FastoNoSQL.

    FastoNoSQL is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    FastoNoSQL is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FastoNoSQL.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "core/redis/redis_cluster_settings.h"

#include <string>

namespace fastonosql {
namespace core {
namespace redis {

RedisClusterSettings::RedisClusterSettings(const std::string& connectionName)
  : IClusterSettingsBase(connectionName, REDIS) {
}

RedisClusterSettings* RedisClusterSettings::clone() const {
  RedisClusterSettings* red = new RedisClusterSettings(*this);
  return red;
}

}  // namespace redis
}  // namespace core
}  // namespace fastonosql
