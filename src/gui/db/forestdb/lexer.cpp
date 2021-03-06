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

#include "gui/db/forestdb/lexer.h"

#include "core/db/forestdb/db_connection.h"

namespace fastonosql {
namespace gui {
namespace forestdb {

ForestDBApi::ForestDBApi(QsciLexer* lexer)
    : BaseQsciApiCommandHolder(core::forestdb::DBConnection::Commands(), lexer) {}

Lexer::Lexer(QObject* parent) : BaseQsciLexerCommandHolder(core::forestdb::DBConnection::Commands(), parent) {
  setAPIs(new ForestDBApi(this));
}

const char* Lexer::language() const {
  return core::forestdb::DBConnection::GetConnectionTypeName();
}

const char* Lexer::version() const {
  return core::forestdb::DBConnection::VersionApi();
}

const char* Lexer::basedOn() const {
  return core::forestdb::DBConnection::BasedOn();
}

}  // namespace forestdb
}  // namespace gui
}  // namespace fastonosql
