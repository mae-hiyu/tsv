/*!
 \file renderer_base.cpp
 \author takemura
 */

#include "renderer_base.hpp"
// Standard C++ library
#include <chrono>
#include <cstdint>
#include <utility>
#include <sstream>
#include <string>
// Qt
#include <QFile>
#include <QSettings>
#include <QString>
#include <QTextStream>
// Zisc
#include "zisc/algorithm.hpp"
#include "zisc/error.hpp"
#include "zisc/stopwatch.hpp"
// Reflect
#include "keyword.hpp"
#include "renderer_manager.hpp"
#include "renderer_system.hpp"
#include "Utility/size.hpp"
#include "Utility/value.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
RendererBase::RendererBase(const QSettings& settings)
{
  initializeBase(settings);
}

/*!
  \details
  No detailed.
  */
RendererBase::~RendererBase()
{
}

/*!
  \details
  No detailed.
  */
std::size_t RendererBase::printMemberData()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(manager_);
  size += PRINT_VARIABLE_DATA(system_);
  size += PRINT_VARIABLE_DATA(color_system_);
  size += PRINT_VARIABLE_DATA(ldr_image_format_);
  return size;
}

/*!
  \details
  No detailed.
  */
QString RendererBase::getCurrentTime()
{
  using Clock = std::chrono::system_clock;
  auto t = Clock::to_time_t(Clock::now());
  std::istringstream time{std::ctime(&t)};

  std::ostringstream current_time;

  // Throw week information
  std::string weekday;
  std::getline(time, weekday, ' ');

  // Get month information
  std::string month;
  std::getline(time, month, ' ');
  std::map<std::string, std::string> kMonthList{
      {"Jan", "01"}, {"Feb", "02"}, {"Mar", "03"}, {"Apr", "04"},
      {"May", "05"}, {"Jun", "06"}, {"Jul", "07"}, {"Aug", "08"},
      {"Sep", "09"}, {"Oct", "10"}, {"Nov", "11"}, {"Dec", "12"}};

  // Get day information
  std::string day;
  while (day.empty())
    std::getline(time, day, ' ');

  // Get time information
  std::string hours;
  std::getline(time, hours, ':');
  std::string minutes;
  std::getline(time, minutes, ':');
  std::string seconds;
  std::getline(time, seconds, ' ');

  // Get year information
  std::string years;
  std::getline(time, years);

  current_time << years << "_" << kMonthList[month] << "_" << day << "_"
               << hours << "_" << minutes << "_" << seconds;
  return QString{current_time.str().c_str()};
}

/*!
  \details
  No detailed.
  */
QString RendererBase::getTimeText(const std::int64_t milli_time) const
{
  std::int64_t rest_time = 0;
  const auto text = QStringLiteral("%1");
  const QChar zero{'0'};
  const auto hour = text.arg(zisc::Hour::time(milli_time,&rest_time),3,10,zero);
  const auto minute = text.arg(zisc::Minute::time(rest_time,&rest_time),2,10,zero);
  const auto second = text.arg(zisc::Second::time(rest_time,&rest_time),2,10,zero);
  const auto milli = text.arg(rest_time,3,10,zero);
  const auto time = (((QStringLiteral("%1h %2m %3.%4s")
      .arg(hour)).arg(minute)).arg(second)).arg(milli);
  return time;
};

/*!
  \details
  No detailed.
  */
auto RendererBase::makeLogText(const QString& file_name) const -> LogText
{
  LogText log;
  log.first = new QFile{manager_.renderingDirectory() + "/" + file_name};
  log.first->open(QIODevice::WriteOnly | QIODevice::Text);
  log.second = new QTextStream{log.first.get()};

  return log;
}

/*!
  \details
  No detailed.
  */
void RendererBase::initializeBase(const QSettings& settings)
{
  system_ = new RendererSystem{settings};
  color_system_ = new ColorSystem{settings};

  setLdrImageFormat(settings);
}

/*!
  \details
  No detailed.
  */
void RendererBase::setLdrImageFormat(const QSettings& settings)
{
  auto key = QString{keyword::system_group} + "/" + keyword::ldr_image_format;
  const auto format = value<QString>(settings, key);
  switch (zisc::toHash32(format.toStdString().c_str())) {
   case zisc::toHash32(keyword::png_format):
    ldr_image_format_ = ".png";
    break;
   case zisc::toHash32(keyword::bmp_format):
    ldr_image_format_ = ".bmp";
    break;
   case zisc::toHash32(keyword::ppm_format):
    ldr_image_format_ = ".ppm";
    break;
   default:
    zisc::raiseError("SystemError: Unsupported LDR image format is specified.");
    break;
  }
}

} // namespace reflect
