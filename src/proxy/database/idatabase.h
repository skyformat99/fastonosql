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

#pragma once

#include <string>

#include "core/connection_types.h"  // for core::connectionTypes
#include "core/database/idatabase_info.h"

#include "proxy/proxy_fwd.h"

namespace fastonosql {
namespace proxy {
namespace events_info {
struct ExecuteInfoRequest;
}
}  // namespace proxy
}  // namespace fastonosql
namespace fastonosql {
namespace proxy {
namespace events_info {
struct LoadDatabaseContentRequest;
}
}  // namespace proxy
}  // namespace fastonosql

namespace fastonosql {
namespace proxy {

class IDatabase {
 public:
  virtual ~IDatabase();

  IServerSPtr Server() const;
  core::IDataBaseInfoSPtr Info() const;

  core::connectionTypes Type() const;
  bool IsDefault() const;
  std::string Name() const;

  void LoadContent(const events_info::LoadDatabaseContentRequest& req);
  void Execute(const events_info::ExecuteInfoRequest& req);

 protected:
  IDatabase(IServerSPtr server, core::IDataBaseInfoSPtr info);

 private:
  const core::IDataBaseInfoSPtr info_;
  const IServerSPtr server_;
};

}  // namespace proxy
}  // namespace fastonosql
