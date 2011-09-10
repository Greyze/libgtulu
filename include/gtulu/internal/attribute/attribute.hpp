/**
 * @file
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE or copy at http://www.boost.org/LICENSE
 */

#ifndef IN_GTULU_INTERNAL_ATTRIBUTE_HPP_
#error "gtulu/internal/attribute/attribute.hpp should not be included directly, please include gtulu/internal/attribute.hpp instead."
#endif /* IN_GTULU_INTERNAL_ATTRIBUTE_HPP_ */

#ifndef GTULU_INTERNAL_ATTRIBUTE_ATTRIBUTE_HPP_
#define GTULU_INTERNAL_ATTRIBUTE_ATTRIBUTE_HPP_

namespace gtulu {
  namespace internal {

    namespace attribute {

      namespace detail {
        template< typename Cardinality >
        struct cardinality_binder;

#define DECLARE_BINDER(count_m, cardinality_m)                                                          \
    template< >                                                                                         \
    struct cardinality_binder< fc::cardinality::cardinality_m > {                                       \
      template< typename Integral > struct attribute_binder;                                            \
    };                                                                                                  \
    template< > template< >                                                                             \
    struct cardinality_binder< fc::cardinality::cardinality_m >                                         \
         ::attribute_binder< fn::integral::floating > {                                                 \
         template< typename DataFormat >                                                                \
         inline static void bind(location_t const location_in,                                          \
                                 BOOST_PP_ENUM_PARAMS(count_m,                                          \
                                   typename fc::to_value_type< DataFormat >::type const value_in)) {    \
             fnc::gl_vertex_attrib_##count_m ::call(location_in,                                        \
                                                    BOOST_PP_ENUM_PARAMS(count_m, value_in));           \
             fnc::gl_disable_vertex_attrib_array::call(location_in);                                    \
         }                                                                                              \
         template< typename DataFormat >                                                                \
         inline static void bind(location_t const location_in, ::std::uint32_t const number_in,         \
                                 typename fc::to_value_type< DataFormat >::type const* values_in) {     \
           fnc::gl_vertex_attrib_##count_m ::call(location_in, values_in);                              \
           fnc::gl_disable_vertex_attrib_array::call(location_in);                                      \
         }                                                                                              \
    };                                                                                                  \
    template< > template< >                                                                             \
    struct cardinality_binder< fc::cardinality::cardinality_m >                                         \
         ::attribute_binder< fn::integral::integral > {                                                 \
        template< typename DataFormat >                                                                 \
        inline static void bind(location_t const location_in,                                           \
                                BOOST_PP_ENUM_PARAMS(count_m,                                           \
                                  typename fc::to_value_type< DataFormat >::type const value_in)) {     \
           fnc::gl_vertex_attrib_##count_m##_integer ::call(location_in,                                \
                                                            BOOST_PP_ENUM_PARAMS(count_m, value_in));   \
           fnc::gl_disable_vertex_attrib_array::call(location_in);                                      \
         }                                                                                              \
         template< typename DataFormat >                                                                \
         inline static void bind(location_t const location_in, ::std::uint32_t const number_in,         \
                                 typename fc::to_value_type< DataFormat >::type const* values_in) {     \
           fnc::gl_vertex_attrib_##count_m##_integer ::call(location_in, values_in);                    \
           fnc::gl_disable_vertex_attrib_array::call(location_in);                                      \
         }                                                                                              \
    };

        DECLARE_BINDER(1, one)
        DECLARE_BINDER(2, two)
        DECLARE_BINDER(3, three)
        DECLARE_BINDER(4, four)

#undef DECLARE_BINDER

      } // namespace detail

      template< typename AttributeFormat >
      struct attribute_binder: detail::cardinality_binder< typename fc::get_cardinality< AttributeFormat >::type >::template attribute_binder<
          typename fn::get_integral< typename fc::get_numeric< AttributeFormat >::type >::type > {
      };

      template< typename Format, typename BinderType = attribute_binder< Format >,
          typename BufferBinderType = attribute_buffer_binder< Format > >
//      , typename ValueType = typename fc::to_value_type< Format >::type >
      struct attribute {
          typedef Format format;
//          typedef ValueType value_type;
          typedef BinderType binder;
          typedef BufferBinderType buffer_binder;
      };

#define DECLARE_ATTRIBUTE(format_m) \
  typedef attribute< fa::format_m > format_m;

      DECLARE_ATTRIBUTE(gl_float)
      DECLARE_ATTRIBUTE(gl_int)
      DECLARE_ATTRIBUTE(gl_unsigned_int)

      DECLARE_ATTRIBUTE(gl_float_vec2)
      DECLARE_ATTRIBUTE(gl_float_vec3)
      DECLARE_ATTRIBUTE(gl_float_vec4)
      DECLARE_ATTRIBUTE(gl_int_vec2)
      DECLARE_ATTRIBUTE(gl_int_vec3)
      DECLARE_ATTRIBUTE(gl_int_vec4)
      DECLARE_ATTRIBUTE(gl_unsigned_int_vec2)
      DECLARE_ATTRIBUTE(gl_unsigned_int_vec3)
      DECLARE_ATTRIBUTE(gl_unsigned_int_vec4)

#undef DECLARE_ATTRIBUTE

    } // namespace attribute

    namespace gia = ::gtulu::internal::attribute;

  } // namespace internal
} // namespace gtulu

#endif /* GTULU_INTERNAL_ATTRIBUTE_ATTRIBUTE_HPP_ */
