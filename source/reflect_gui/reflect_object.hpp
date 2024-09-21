/*!
  \file reflect_object.hpp
  \author takemura
  */

#ifndef _REFLECT_REFLECT_OBJECT_HPP_
#define _REFLECT_REFLECT_OBJECT_HPP_

// Qt
#include <QList>
#include <QMetaObject>
// ReflectCore
#include "reflect_config.hpp"

// Forward declaration
class QSettings;
class QString;
class QStringList;

namespace reflect {

/*!
  \details
  No detailed.
  */
class ReflectObject
{
 public:
  virtual ~ReflectObject();


  //! Activate the object
  virtual void activate();

  //! Deactivate the object
  virtual void deactivate();

  //! Read data from a setting file
  virtual void readData(const QString& prefix, const QSettings& settings);

  //! Varidate data
  virtual void validateData(QStringList* error_message_list) const;

  //! Write data into a setting file
  virtual void writeData(const QString& prefix, QSettings* settings) const;

 protected:
  //! Read table data from a setting file
  void readTableData(const QString& prefix, const QSettings& settings);

  //! Reset all connection
  void resetConnection();

  //! Write table data into a setting file
  void writeTableData(const QString& prefix, QSettings* settings) const;


  QList<QMetaObject::Connection> connection_list_;
  ReflectTable table_;
};

} // namespace reflect

#endif // _REFLECT_REFLECT_OBJECT_HPP_
