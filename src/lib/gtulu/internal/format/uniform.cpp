/**
 * @file
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE or copy at http://www.boost.org/LICENSE
 */
#include "gtulu_opengl_pch.hpp"

#include "gtulu/namespaces.hpp"
#include "gtulu/opengl.hpp"

#include "gtulu/internal/format/uniform.hpp"

namespace gtulu {
  namespace internal {

    namespace format {
      namespace uniform {

        namespace format {
          bool is_uniform(std::uint32_t value) {
            return static_cast< std::uint64_t >(get(value)) != cst::invalid_constant::value;
          }

          cst::gl_constant_base const get(std::uint32_t value) {
            switch (value) {
              case gl_float::value:
                return gl_float();
              case gl_float_vec2::value:
                return gl_float_vec2();
              case gl_float_vec3::value:
                return gl_float_vec3();
              case gl_float_vec4::value:
                return gl_float_vec4();
              case gl_int::value:
                return gl_int();
              case gl_int_vec2::value:
                return gl_int_vec2();
              case gl_int_vec3::value:
                return gl_int_vec3();
              case gl_int_vec4::value:
                return gl_int_vec4();
              case gl_unsigned_int::value:
                return gl_unsigned_int();
              case gl_unsigned_int_vec2::value:
                return gl_unsigned_int_vec2();
              case gl_unsigned_int_vec3::value:
                return gl_unsigned_int_vec3();
              case gl_unsigned_int_vec4::value:
                return gl_unsigned_int_vec4();
              case gl_bool::value:
                return gl_bool();
              case gl_bool_vec2::value:
                return gl_bool_vec2();
              case gl_bool_vec3::value:
                return gl_bool_vec3();
              case gl_bool_vec4::value:
                return gl_bool_vec4();
              case gl_float_mat2::value:
                return gl_float_mat2();
              case gl_float_mat3::value:
                return gl_float_mat3();
              case gl_float_mat4::value:
                return gl_float_mat4();
              case gl_float_mat2x3::value:
                return gl_float_mat2x3();
              case gl_float_mat2x4::value:
                return gl_float_mat2x4();
              case gl_float_mat3x2::value:
                return gl_float_mat3x2();
              case gl_float_mat3x4::value:
                return gl_float_mat3x4();
              case gl_float_mat4x2::value:
                return gl_float_mat4x2();
              case gl_float_mat4x3::value:
                return gl_float_mat4x3();
              default:
                return cst::invalid_constant();
            }
          }
        } // namespace format

      } // namespace uniform
    } // namespace format

  } // namespace internal
} // namespace gtulu
