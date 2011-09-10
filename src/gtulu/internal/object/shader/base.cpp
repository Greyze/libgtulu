/**
 * @file
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
 *
 * @date 27 juil. 2010
 * @todo comment
 */
#include "gtulu_opengl_pch.hpp"

#include "gtulu/opengl.hpp"
#include "gtulu/internal/constants.hpp"
#include "gtulu/internal/functions.hpp"

#include "gtulu/internal/object/shader/base.hpp"

namespace gtulu {
  namespace internal {

    namespace object {
      void shader_base::compile() {
        fnc::gl_compile_shader::call(handle_);
      }

      void shader_base::set_source(char const* code) {
        fnc::gl_shader_source::call(handle_, 1, static_cast< GLchar const** >(&code), NULL);
      }
    } // namespace object

  } // namespace internal
} // namespace gtulu