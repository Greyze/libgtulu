/**
 * @file
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE or copy at http://www.boost.org/LICENSE
 */

#ifndef GTULU_INTERNAL_FORMAT_CONVERSION_COMMON_HPP_
#define GTULU_INTERNAL_FORMAT_CONVERSION_COMMON_HPP_

#include "gtulu/namespaces.hpp"
#include "gtulu/internal/format/common.hpp"
#include "gtulu/internal/format/conversion/numeric.hpp"

namespace gtulu {
  namespace internal {

    namespace format {
      namespace common {

        template< typename Format >
        struct to_value_type {
            typedef typename fnum::to_value_type< typename fcmn::get_numeric< Format >::type >::type type;
        };

        template< typename Format >
        struct size_of {
            static std::uint8_t const value = fnum::size_of<
                typename fnum::get_width< typename fcmn::get_numeric< Format >::type >::type >::value;
        };

        namespace cardinality {
          template< typename Cardinality >
          struct get_literal {
              typedef bm::int_< 1 > type;
          };

          template< >
          struct get_literal< fcmn::cardinality::one > {
              typedef bm::int_< 1 > type;
          };
          template< >
          struct get_literal< fcmn::cardinality::two > {
              typedef bm::int_< 2 > type;
          };
          template< >
          struct get_literal< fcmn::cardinality::three > {
              typedef bm::int_< 3 > type;
          };
          template< >
          struct get_literal< fcmn::cardinality::four > {
              typedef bm::int_< 4 > type;
          };

        } // namespace cardinality

        template< typename Format >
        struct get_cardinality_literal {
            typedef typename fcmn::cardinality::get_literal< typename fcmn::get_cardinality< Format >::type >::type type;
        };

      } // namespace common
    } // namespace format

  } // namespace internal
} // namespace gtulu

#endif /* GTULU_INTERNAL_FORMAT_CONVERSION_COMMON_HPP_ */
