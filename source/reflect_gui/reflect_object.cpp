/*!
  \file reflect_object.cpp
  \author takemura
  */

#include "reflect_object.hpp"
// Qt
#include <QHash>
#include <QRegularExpression>
#include <QSettings>
#include <QString>
#include <QStringList>
// ReflectCore
#include "reflect_config.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
ReflectObject::~ReflectObject()
{
  resetConnection();
}

/*!
  \details
  No detailed.
  */
void ReflectObject::activate()
{
}

/*!
  \details
  No detailed.
  */
void ReflectObject::deactivate()
{
}

/*!
  \details
  No detailed.
  */
void ReflectObject::readData(const QString& prefix, const QSettings& settings)
{
  readTableData(prefix, settings);
}

/*!
  \details
  No detailed.
  */
void ReflectObject::validateData(QStringList* /* error_message_list */) const
{
}

/*!
  \details
  No detailed.
  */
void ReflectObject::writeData(const QString& prefix, QSettings* settings) const
{
  writeTableData(prefix, settings);
}

/*!
  \details
  No detailed.
  */
void ReflectObject::readTableData(const QString& prefix, const QSettings& settings)
{
  // Get child keys
  const QRegularExpression regex{QStringLiteral("^") + prefix + "/\\w+$"};
  QStringList child_keys;
  for (const auto& key : settings.allKeys()) {
    const auto match = regex.match(key);
    if (match.hasMatch())
      child_keys << key;
  }

  // Read data
  for (const auto& key : child_keys)
    table_[key] = settings.value(key);
}

/*!
  \details
  No detailed.
  */
void ReflectObject::resetConnection()
{
  for (auto& connection : connection_list_)
    QObject::disconnect(connection);
  connection_list_.clear();
}

/*!
  \details
  No detailed.
  */
void ReflectObject::writeTableData(const QString& prefix,
                                   QSettings* settings) const
{
  for (const auto& key : table_.keys())
    settings->setValue(prefix + "/" + key, table_[key]);
}

} // namespace reflect
