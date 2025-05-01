#ifndef ANTI_CHEAT_COMMON_STATUS_MACROS_H
#define ANTI_CHEAT_COMMON_STATUS_MACROS_H

#include <absl/status/status.h>
#include <absl/status/statusor.h>

#define INTERNAL_CONCAT_INNER(x, y) x##y
#define INTERNAL_CONCAT(x, y) INTERNAL_CONCAT_INNER(x, y)

#define RETURN_IF_ERROR(expr) \
  RETURN_IF_ERROR_IMPL(expr, INTERNAL_CONCAT(_status, __LINE__))

#define RETURN_IF_ERROR_IMPL(expr, unique_name) \
  auto unique_name = (expr);                    \
  if (!unique_name.ok()) return unique_name

#define ASSIGN_OR_RETURN(lhs, expr) \
  ASSIGN_OR_RETURN_IMPL(lhs, expr, INTERNAL_CONCAT(_status_or_value, __LINE__))

#define ASSIGN_OR_RETURN_IMPL(lhs, expr, unique_name) \
  auto unique_name = (expr);                          \
  if (!unique_name.ok()) return unique_name.status(); \
  lhs = std::move(unique_name).value()

#endif  // ANTI_CHEAT_COMMON_STATUS_MACROS_H
