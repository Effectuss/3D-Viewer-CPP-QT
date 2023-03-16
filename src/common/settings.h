#ifndef SRC_MODEL_SETTINGS_H_
#define SRC_MODEL_SETTINGS_H_

#include <QDir>
#include <QHash>
#include <QSettings>

class Settings {
 public:
  Settings(const Settings &) = delete;
  void operator=(const Settings &) = delete;
  void operator=(Settings &&) = delete;
  Settings(Settings &&) = delete;

  static Settings &GetInstance() {
    static Settings instance;
    return instance;
  }

  int Value(const QString &key) const;
  void SetDefaultAllValues();
  void SetValue(const QString &key, const int &value);

 private:
  ~Settings();
  explicit Settings();

  QSettings *qsettings_;
  const QHash<QString, int> default_settings_{
      {"vertex_color_r", 76}, {"vertex_color_g", 194}, {"vertex_color_b", 255},
      {"edge_color_r", 76},   {"edge_color_g", 194},   {"edge_color_b", 255},
      {"bg_color_r", 39},     {"bg_color_g", 39},      {"bg_color_b", 39},
      {"vertex_size", 1},     {"edge_width", 1},       {"vertex_shape", 0},
      {"edge_type", 1},       {"projection_type", 1},  {"grid_on", 0}};
};

#endif  // SRC_MODEL_SETTINGS_H_
