#ifndef DP_MACROS_H
#define DP_MACROS_H

#include <QObject>
#include <QVariant>

#define GENERATE_PROPERTY(name, value_type, default_value)                     \
private:                                                                       \
  QVariant name##_;                                                            \
  Q_PROPERTY(value_type name MEMBER name##_ READ name WRITE set_##name RESET   \
                 reset_##name)                                                 \
public:                                                                        \
  value_type name() const {                                                    \
    /*    if (name##_.isNull()) {                                              \
          return default_##name();                                             \
          \                                                                    \
        }   */                                                                 \
    return name##_.value<value_type>();                                        \
  };                                                                           \
  void set##_name(const value_type &val) {                                     \
    name##_ = QVariant::fromValue(val);                                        \
  }                                                                            \
  value_type default_##name() const { return value_type(default_value); }      \
  void reset_##name() { name##_ = QVariant(); }

#endif // DP_MACROS_H
