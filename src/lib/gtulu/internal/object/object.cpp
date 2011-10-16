/**
 * @file
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE or copy at http://www.boost.org/LICENSE
 */
#include "gtulu_opengl_pch.hpp"

#include "gtulu/namespaces.hpp"
#include "gtulu/opengl.hpp"

#include "gtulu/internal/object/object.hpp"

namespace gtulu {
  namespace internal {

    namespace object {
      object_base::object_base() :
          handle_(0) {
      }

      object_base::object_base(const std::uint32_t handle_in) :
          handle_(handle_in) {
      }

      std::uint32_t object_base::operator *() const {
        return handle_;
      }

      template< >
      object< texture_base >::object() {
        fct::gl_gen_textures::call(1, &handle_);
      }
      template< >
      object< texture_base >::~object() {
        fct::gl_delete_textures::call(1, &handle_);
      }

      template< >
      object< buffer_base >::object() {
        fct::gl_gen_buffers::call(1, &handle_);
      }
      template< >
      object< buffer_base >::~object() {
        fct::gl_delete_buffers::call(1, &handle_);
      }

      template< >
      object< renderbuffer_base >::object() {
        fct::gl_gen_renderbuffers::call(1, &handle_);
      }
      template< >
      object< renderbuffer_base >::~object() {
        fct::gl_delete_renderbuffers::call(1, &handle_);
      }

      template< >
      object< framebuffer_base >::object() {
        fct::gl_gen_framebuffers::call(1, &handle_);
      }
      template< >
      object< framebuffer_base >::~object() {
        fct::gl_delete_framebuffers::call(1, &handle_);
      }

      template< >
      object< vertexarray_base >::object() {
        fct::gl_gen_vertex_arrays::call(1, &handle_);
      }
      template< >
      object< vertexarray_base >::~object() {
        fct::gl_delete_vertex_arrays::call(1, &handle_);
      }

      template< >
      object< query_base >::object() {
        fct::gl_gen_queries::call(1, &handle_);
      }
      template< >
      object< query_base >::~object() {
        fct::gl_delete_queries::call(1, &handle_);
      }

      template< >
      object< program_base >::object() {
        handle_ = fct::gl_create_program::call();

      }
      template< >
      object< program_base >::~object() {
        fct::gl_delete_program::call(handle_);
      }

      template< >
      object< shader_base >::object() {
      }
      template< >
      object< shader_base >::~object() {
        fct::gl_delete_shader::call(handle_);
      }
    } // namespace object

  } // namespace internal
} // namespace gtulu