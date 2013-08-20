#ifndef SCNET2_BASE_TYPE_H
#define SCNET2_BASE_TYPE_H

namespace scnet2 {

template <typename To, typename From>
inline To implicit_cast(From const &from) {
  return from;
}

}
#endif
