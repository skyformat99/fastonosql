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

#include "gui/action_cell_delegate.h"

#include <QApplication>
#include <QMouseEvent>
#include <QPainter>

#include <common/macros.h>
#include <common/qt/utils_qt.h>

#include "gui/key_value_table_item.h"

#include "gui/gui_factory.h"

namespace fastonosql {
namespace gui {

ActionDelegate::ActionDelegate(QObject* parent) : QStyledItemDelegate(parent), current_index_() {}

QSize ActionDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const {
  UNUSED(option);
  UNUSED(index);

  return QSize(16, 16);
}

void ActionDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
  if (!index.isValid()) {
    return;
  }

  KeyValueTableItem* node = common::qt::item<common::qt::gui::TableItem*, KeyValueTableItem*>(index);
  QStyleOptionViewItem opt = option;
  initStyleOption(&opt, index);

  QWidget* widget = qobject_cast<QWidget*>(parent());
  QStyle* style = widget ? widget->style() : QApplication::style();

  QStyleOptionButton pb_Style;
  pb_Style.state |= QStyle::State_Enabled | option.state;
  pb_Style.rect = option.rect;
  pb_Style.features |= QStyleOptionButton::Flat;
  pb_Style.text = QString();
  pb_Style.iconSize = QSize(16, 16);
  pb_Style.icon = node->actionState() == KeyValueTableItem::AddAction ? GuiFactory::Instance().addIcon()
                                                                      : GuiFactory::Instance().removeIcon();
  if (current_index_.row() == index.row()) {
    pb_Style.state |= QStyle::State_Sunken;
  } else {
    pb_Style.state |= QStyle::State_Raised;
  }
  style->drawControl(QStyle::CE_PushButton, &pb_Style, painter, widget);
}

bool ActionDelegate::editorEvent(QEvent* event,
                                 QAbstractItemModel* model,
                                 const QStyleOptionViewItem& option,
                                 const QModelIndex& index) {
  UNUSED(model);
  if (!index.isValid()) {
    return QStyledItemDelegate::editorEvent(event, model, option, index);
  }

  if (event->type() != QEvent::MouseButtonPress && event->type() != QEvent::MouseButtonRelease) {
    return QStyledItemDelegate::editorEvent(event, model, option, index);
  }

  if (event->type() == QEvent::MouseButtonPress) {
    current_index_ = index;
  } else if (event->type() == QEvent::MouseButtonRelease) {
    KeyValueTableItem* node = common::qt::item<common::qt::gui::TableItem*, KeyValueTableItem*>(index);
    if (node->actionState() == KeyValueTableItem::AddAction) {
      emit addClicked(index);
    } else {
      emit removeClicked(index);
    }
    current_index_ = QModelIndex();
  }

  return QStyledItemDelegate::editorEvent(event, model, option, index);
}

}  // namespace gui
}  // namespace fastonosql
