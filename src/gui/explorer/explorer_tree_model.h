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

#include "fasto/qt/gui/base/tree_model.h"

#include "core/core_fwd.h"
#include "core/types.h"

namespace fastonosql {
namespace gui {

struct IExplorerTreeItem
  : public fasto::qt::gui::TreeItem {
  enum eColumn {
    eName = 0,
    eCountColumns
  };

  enum eType {
    eCluster,
    eServer,
    eDatabase,
    eKey
  };

  explicit IExplorerTreeItem(TreeItem* parent);

  virtual QString name() const = 0;
  virtual core::IServerSPtr server() const = 0;
  virtual eType type() const = 0;
};

struct ExplorerServerItem
  : public IExplorerTreeItem {
  ExplorerServerItem(core::IServerSPtr server, TreeItem* parent);

  virtual QString name() const;
  virtual core::IServerSPtr server() const;
  virtual eType type() const;

  void loadDatabases();

 private:
  const core::IServerSPtr server_;
};

struct ExplorerClusterItem
  : public IExplorerTreeItem {
  ExplorerClusterItem(core::IClusterSPtr cluster, TreeItem* parent);

  virtual QString name() const;
  virtual core::IServerSPtr server() const;
  virtual eType type() const;

  core::IClusterSPtr cluster() const;

 private:
  const core::IClusterSPtr cluster_;
};

struct ExplorerDatabaseItem
  : public IExplorerTreeItem {
  ExplorerDatabaseItem(core::IDatabaseSPtr db, ExplorerServerItem* parent);

  ExplorerServerItem* parent() const;

  virtual QString name() const;
  virtual eType type() const;
  bool isDefault() const;
  size_t sizeDB() const;
  size_t loadedSize() const;

  virtual core::IServerSPtr server() const;
  core::IDatabaseSPtr db() const;

  void loadContent(const std::string& pattern, uint32_t countKeys);
  void setDefault();

  core::IDataBaseInfoSPtr info() const;

  void removeKey(const core::NDbKValue& key);
  void loadValue(const core::NDbKValue& key);
  void createKey(const core::NDbKValue& key);

  void removeAllKeys();
 private:
  const core::IDatabaseSPtr db_;
};

struct ExplorerKeyItem
  : public IExplorerTreeItem {
  ExplorerKeyItem(const core::NDbKValue& key, ExplorerDatabaseItem* parent);

  ExplorerDatabaseItem* parent() const;

  core::NDbKValue key() const;

  virtual QString name() const;
  virtual core::IServerSPtr server() const;
  virtual eType type() const;

  void removeFromDb();
  void loadValueFromDb();

 private:
  core::NDbKValue key_;
};

class ExplorerTreeModel
  : public fasto::qt::gui::TreeModel {
  Q_OBJECT
 public:
  explicit ExplorerTreeModel(QObject* parent = 0);

  virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
  virtual Qt::ItemFlags flags(const QModelIndex& index) const;
  virtual QVariant headerData(int section, Qt::Orientation orientation,
                              int role = Qt::DisplayRole) const;
  virtual int columnCount(const QModelIndex &parent) const;

  void addCluster(core::IClusterSPtr cluster);
  void removeCluster(core::IClusterSPtr cluster);

  void addServer(core::IServerSPtr server);
  void removeServer(core::IServerSPtr server);

  void addDatabase(core::IServer* server, core::IDataBaseInfoSPtr db);
  void removeDatabase(core::IServer* server, core::IDataBaseInfoSPtr db);
  void setDefaultDb(core::IServer* server, core::IDataBaseInfoSPtr db);
  void updateDb(core::IServer* server, core::IDataBaseInfoSPtr db);

  void addKey(core::IServer* server, core::IDataBaseInfoSPtr db, const core::NDbKValue &dbv);
  void removeKey(core::IServer* server, core::IDataBaseInfoSPtr db, const core::NDbKValue &key);
  void removeAllKeys(core::IServer* server, core::IDataBaseInfoSPtr db);

 private:
  ExplorerClusterItem* findClusterItem(core::IClusterSPtr cl);
  ExplorerServerItem* findServerItem(core::IServer* server) const;
  ExplorerDatabaseItem* findDatabaseItem(ExplorerServerItem* server, core::IDataBaseInfoSPtr db) const;
  ExplorerKeyItem* findKeyItem(ExplorerDatabaseItem* db, const core::NDbKValue &key) const;
};

}  // namespace gui
}  // namespace fastonosql
