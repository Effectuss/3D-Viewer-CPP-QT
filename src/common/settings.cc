#include "settings.h"

Settings::Settings() {
  QString config = QDir::homePath() + "/settings_3dviewer.conf";
  qsettings_ = new QSettings(config, QSettings::IniFormat);
}

Settings::~Settings() { delete qsettings_; }

int Settings::Value(const QString &key) const {
  return qsettings_->value(key, default_settings_[key]).toInt();
}

void Settings::SetDefaultAllValues() {
  foreach (const QString &key, default_settings_.keys()) {
    qsettings_->setValue(key, default_settings_.value(key));
  }
}

void Settings::SetValue(const QString &key, const int &value) {
  qsettings_->setValue(key, QVariant::fromValue(value));
}
